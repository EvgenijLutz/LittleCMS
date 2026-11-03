# bash build-apple.sh

# Little-CMS

source common.sh

# Define some global variables
developer_path="/Applications/Xcode.app/Contents/Developer"
# Your signing identity to sign the xcframework. Execute "security find-identity -v -p codesigning" and select one from the list
signing_identity=070BA25D98F2A17A61E3E27E31BE64C06F901016

# Android NDK path
ndk_path="/Users/evgenij/Library/Android/sdk/ndk/29.0.14206865"

# Little-CMS source code folder
source_name="lcms2-2.20"


# Check if Xcode Developer, Android NDK and freetype folders exist
assert_path $developer_path
assert_path $ndk_path
assert_path $source_name


build_library() {
  local platform=$1
  local arch=$2
  local target_os=$3

  # Reset variables
  export LT_SYS_LIBRARY_PATH=""
  export AR=""
  export CC=""
  export AS=""
  export CXX=""
  export LD=""
  export RANLIB=""
  export STRIP=""
  export CPPFLAGS=""
  export CFLAGS=""

  # Determine host based on platform and architecture
  # Apple
  if [[ "$platform" == "MacOSX" ]] || \
    [[ "$platform" == "iPhoneOS" ]] || [[ "$platform" == "iPhoneSimulator" ]] || \
    [[ "$platform" == "AppleTVOS" ]] || [[ "$platform" == "AppleTVSimulator" ]] || \
    [[ "$platform" == "WatchOS" ]] || [[ "$platform" == "WatchSimulator" ]] || \
    [[ "$platform" == "XROS" ]] || [[ "$platform" == "XRSimulator" ]]; then
    # Determine the host
    if   [[ "$arch" == "arm64" ]];  then local host="arm-apple-darwin"
    elif [[ "$arch" == "x86_64" ]]; then local host="x86_64-apple-darwin"
    fi

    # Get the xcframework target name
    if [[ "$platform" == "MacOSX" ]]; then
      local framework_target="macos-arm64_x86_64"
    elif [[ "$platform" == "iPhoneOS" ]]; then
      local framework_target="ios-$arch"
    elif [[ "$platform" == "iPhoneSimulator" ]]; then
      local framework_target="ios-arm64_x86_64-simulator"
    elif [[ "$platform" == "AppleTVOS" ]]; then
      local framework_target="tvos-$arch"
    elif [[ "$platform" == "AppleTVSimulator" ]]; then
      local framework_target="tvos-arm64_x86_64-simulator"
    elif [[ "$platform" == "WatchOS" ]]; then
      local framework_target="watchos-$arch"
    elif [[ "$platform" == "WatchSimulator" ]]; then
      local framework_target="watchos-arm64_x86_64-simulator"
    elif [[ "$platform" == "XROS" ]]; then
      local framework_target="xros-$arch"
    elif [[ "$platform" == "XRSimulator" ]]; then
      local framework_target="xros-arm64_x86_64-simulator"
    else
      echo "Unknown platform $platform"
      exit 1
    fi

    # Target sdk path
    local sysroot="$developer_path/Platforms/$platform.platform/Developer/SDKs/$platform.sdk"

    local arch_flags="-arch $arch"
    local target_os_flags="-mtargetos=$target_os"
    export CC="$developer_path/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang"
    export LT_SYS_LIBRARY_PATH="-isysroot $sysroot/usr/include"
    export CPPFLAGS="-I$sysroot/usr/include"
    export CFLAGS="-isysroot $sysroot $arch_flags -std=c17 $target_os_flags -O2"
  # Android
  elif [[ "$platform" == "Android" ]]; then
    # Determine the host
    if   [[ "$arch" == "aarch64" ]];  then local host="aarch64-linux-android"
    elif [[ "$arch" == "arm" ]];      then local host="arm-linux-androideabi"
    elif [[ "$arch" == "i686" ]];     then local host="i686-linux-android"
    elif [[ "$arch" == "riscv64" ]];  then local host="riscv64-linux-android"
    elif [[ "$arch" == "x86_64" ]];   then local host="x86_64-linux-android"
    fi

    # Target sdk path
    local sysroot="$ndk_path/toolchains/llvm/prebuilt/darwin-x86_64/sysroot"

    local arch_flags=""
    local target_os_flags="--target=$host$target_os"
    export LT_SYS_LIBRARY_PATH=""

    local toolchain="$ndk_path/toolchains/llvm/prebuilt/darwin-x86_64"
    export AR=$toolchain/bin/llvm-ar
    export CC="$toolchain/bin/clang $target_os_flags"
    export AS=$CC
    export CXX="$toolchain/bin/clang++ $target_os_flags"
    export LD=$toolchain/bin/ld
    export RANLIB=$toolchain/bin/llvm-ranlib
    export STRIP=$toolchain/bin/llvm-strip

    export CPPFLAGS=""
    export CFLAGS="-std=c17 -O2"
  else
    echo "Unknown platform $platform"
    exit 1
  fi

  prefix=$(pwd)/build/$platform/$arch/install
  
  # Create the build directory if not exists
  mkdir -p build/$platform/$arch/tmp
  exit_if_error

  cd build/$platform/$arch/tmp
  exit_if_error

  if false; then
    sh ./../$source_name/configure -h -n
    return
  fi

  TO_IMPLEMENT=no
  sh ./../../../../$source_name/configure \
  --host=$host \
  --prefix $prefix \
  --enable-shared=no \
  --enable-static=yes \
  --without-tiff \
  --without-jpeg
  exit_if_error

  make
  exit_if_error

  make install
  exit_if_error

  # Go back to origin
  cd ../../../..

  # Remove temporary files
  rm -rf build/$platform/$arch/tmp

  exit_if_error
}


# Build for Apple systems
build_library MacOSX           arm64  macos12
build_library MacOSX           x86_64 macos12
build_library iPhoneOS         arm64  ios15
build_library iPhoneSimulator  arm64  ios15-simulator
build_library iPhoneSimulator  x86_64 ios15-simulator
build_library AppleTVOS        arm64  tvos15
build_library AppleTVSimulator arm64  tvos15-simulator
build_library AppleTVSimulator x86_64 tvos15-simulator
build_library WatchOS          arm64  watchos9
build_library WatchSimulator   arm64  watchos9-simulator
build_library WatchSimulator   x86_64 watchos9-simulator
build_library XROS             arm64  xros1
build_library XRSimulator      arm64  xros1-simulator
build_library XRSimulator      x86_64 xros1-simulator

# # Build for Android
# build_library Android aarch64 21
# build_library Android arm     21
# build_library Android i686    21
# build_library Android riscv64 35
# build_library Android x86_64  21


# Xcode Framework for all Apple platforms
create_xcframework() {
  # Remove previously created framework if exists
  rm -rf build/liblcms2.xcframework
  exit_if_error

  # Merge macOS arm and x86 binaries
  mkdir -p build/MacOSX
  exit_if_error
  lipo -create -output build/MacOSX/liblcms2.a \
    build/MacOSX/arm64/install/lib/liblcms2.a \
    build/MacOSX/x86_64/install/lib/liblcms2.a
  exit_if_error

  # Merge iOS simulator arm and x86 binaries
  mkdir -p build/iPhoneSimulator
  exit_if_error
  lipo -create -output build/iPhoneSimulator/liblcms2.a \
    build/iPhoneSimulator/arm64/install/lib/liblcms2.a \
    build/iPhoneSimulator/x86_64/install/lib/liblcms2.a
  exit_if_error

  # Merge tvOS simulator arm and x86 binaries
  mkdir -p build/AppleTVSimulator
  exit_if_error
  lipo -create -output build/AppleTVSimulator/liblcms2.a \
    build/AppleTVSimulator/arm64/install/lib/liblcms2.a \
    build/AppleTVSimulator/x86_64/install/lib/liblcms2.a
  exit_if_error

  # Merge watchOS simulator arm and x86 binaries
  mkdir -p build/WatchSimulator
  exit_if_error
  lipo -create -output build/WatchSimulator/liblcms2.a \
    build/WatchSimulator/arm64/install/lib/liblcms2.a \
    build/WatchSimulator/x86_64/install/lib/liblcms2.a
  exit_if_error

  # Merge visionOS simulator arm and x86 binaries
  mkdir -p build/XRSimulator
  exit_if_error
  lipo -create -output build/XRSimulator/liblcms2.a \
    build/XRSimulator/arm64/install/lib/liblcms2.a \
    build/XRSimulator/x86_64/install/lib/liblcms2.a
  exit_if_error

  # Create the framework with multiple platforms
  xcodebuild -create-xcframework \
    -library build/MacOSX/liblcms2.a                      -headers build/MacOSX/arm64/install/include \
    -library build/iPhoneOS/arm64/install/lib/liblcms2.a  -headers build/iPhoneOS/arm64/install/include \
    -library build/iPhoneSimulator/liblcms2.a             -headers build/iPhoneSimulator/arm64/install/include \
    -library build/AppleTVOS/arm64/install/lib/liblcms2.a -headers build/AppleTVOS/arm64/install/include \
    -library build/AppleTVSimulator/liblcms2.a            -headers build/AppleTVSimulator/arm64/install/include \
    -library build/WatchOS/arm64/install/lib/liblcms2.a   -headers build/WatchOS/arm64/install/include \
    -library build/WatchSimulator/liblcms2.a              -headers build/WatchSimulator/arm64/install/include \
    -library build/XROS/arm64/install/lib/liblcms2.a      -headers build/XROS/arm64/install/include \
    -library build/XRSimulator/liblcms2.a                 -headers build/XRSimulator/arm64/install/include \
    -output build/liblcms2.xcframework
  exit_if_error

  # And sign the framework
  codesign --timestamp -s $signing_identity build/liblcms2.xcframework
  exit_if_error
}
create_xcframework


# Artifact bundle for Android
create_artifactbundle() {
  # Remove previously created artifact if exists
  rm -rf build/liblcms2.artifactbundle
  exit_if_error

  # Create the artifact bundle folder
  mkdir -p build/liblcms2.artifactbundle
  exit_if_error

  # info.json
  cp Contents/info.json build/liblcms2.artifactbundle/info.json
  exit_if_error

  # Headers
  cp -r build/Android/aarch64/install/include/freetype2 build/liblcms2.artifactbundle/include
  exit_if_error

  # aarch64-linux-android
  mkdir -p build/liblcms2.artifactbundle/aarch64-linux-android
  exit_if_error
  cp build/Android/aarch64/install/lib/liblcms2.a build/liblcms2.artifactbundle/aarch64-linux-android/liblcms2.a
  exit_if_error

  # arm-linux-androideabi
  mkdir -p build/liblcms2.artifactbundle/arm-linux-androideabi
  exit_if_error
  cp build/Android/arm/install/lib/liblcms2.a build/liblcms2.artifactbundle/arm-linux-androideabi/liblcms2.a
  exit_if_error

  # i686-linux-android
  mkdir -p build/liblcms2.artifactbundle/i686-linux-android
  exit_if_error
  cp build/Android/i686/install/lib/liblcms2.a build/liblcms2.artifactbundle/i686-linux-android/liblcms2.a
  exit_if_error

  # riscv64-linux-android
  mkdir -p build/liblcms2.artifactbundle/riscv64-linux-android
  exit_if_error
  cp build/Android/riscv64/install/lib/liblcms2.a build/liblcms2.artifactbundle/riscv64-linux-android/liblcms2.a
  exit_if_error

  # x86_64-linux-android
  mkdir -p build/liblcms2.artifactbundle/x86_64-linux-android
  exit_if_error
  cp build/Android/x86_64/install/lib/liblcms2.a build/liblcms2.artifactbundle/x86_64-linux-android/liblcms2.a
  exit_if_error
}
#create_artifactbundle




# fin