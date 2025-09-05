# bash


# If you don't specify the C++ version for the Swift Package:
# Uncomment the "// #define CMS_NO_REGISTER_KEYWORD 1" line in the include/lcms2.h file
# Uncomment the "// #define CMS_USE_CPP_API" line in the include/lcms2.h file


# Define some global variables
platforms_path='/Applications/Xcode.app/Contents/Developer/Platforms'
# Your signing identity to sign the xcframework. Execute "security find-identity -v -p codesigning" and select one from the list
identity=B42A10624E8E06BC95CD03069100C6E67121D61B


# Console output formatting
# https://stackoverflow.com/a/2924755
bold=$(tput bold)
normal=$(tput sgr0)


# Create the build directory if not exists
mkdir -p build-apple


# Remove logs if exist
rm -f "build-apple/log.txt"


exit_if_error() {
  local result=$?
  if [ $result -ne 0 ] ; then
     echo "Received an exit code $result, aborting"
     exit 1
  fi
}


# Compile the library for specific OS and architecture
build_library() {
  local platform_name=$1
  local arch=$2
  local target_os=$3

  # Determine config name
  local config_name="$platform_name/$arch"

  # Determine meson cpu settings
  if [[ "$arch" == "arm64" ]]; then
    local meson_cpu="arm64"
    local meson_cpu_family="aarch64"
  elif [[ "$arch" == "x86_64" ]]; then
    local meson_cpu="x86"
    local meson_cpu_family="x86_64"
  else
    echo "Unknown architecture"
    exit 1
  fi


  # Remove build directory for the current platform if exists
  rm -rf build-apple/$config_name
  exit_if_error

  # Welcome message
  echo "Build for ${bold}$config_name${normal}"
  mkdir -p build-apple/$config_name

  # Remove config file if exists
  rm -f "build-apple/$config_name.txt"
  exit_if_error

  # Generate meson config file for cross-compile
  echo \
"[binaries]
c = 'clang'
cpp = 'clang++'
ar = 'ar'
strip = 'strip'
pkg-config = 'pkg-config'

[host_machine]
system = 'darwin'
cpu_family = '$meson_cpu_family'
cpu = '$meson_cpu'
endian = 'little'

[built-in options]
c_args = ['-isysroot', '$platforms_path/$platform_name.platform/Developer/SDKs/$platform_name.sdk', '-arch', '$arch', '-mtargetos=$target_os', '-O2']
cpp_args = ['-isysroot', '$platforms_path/$platform_name.platform/Developer/SDKs/$platform_name.sdk', '-arch', '$arch', '-mtargetos=$target_os', '-O2']
c_link_args = ['-arch', '$arch', '-mtargetos=$target_os']
cpp_link_args = ['-arch', '$arch', '-mtargetos=$target_os']" \
>> "build-apple/$config_name.txt"
  exit_if_error

  # Setup meson build
  echo "Configure meson"
  meson setup build-apple/$config_name \
    --cross-file build-apple/$config_name.txt \
    --prefix=$(pwd)/build-apple/$config_name/install \
    --strip \
    -Dc_std=c17 \
    -Dcpp_std=c++20 \
    -Ddefault_library=static \
    -Dtests=disabled \
    -Djpeg=disabled \
    -Dtiff=disabled \
    -Dutils=false \
    -Dfastfloat=false \
    -Dthreaded=false \
    -Dbuildtype=minsize #>> build-apple/log.txt
  exit_if_error
  
  # Build
  echo "Build"
  ninja -C build-apple/$config_name #>> build-apple/log.txt
  exit_if_error
  
  # Install compiled libraries and headers into the install folder
  ninja -C build-apple/$config_name install #>> build-apple/log.txt
  exit_if_error
  
  # About modules
  # https://clang.llvm.org/docs/Modules.html
  # Without module.modulemap liblcms2 is not exposed to Swift
  # Copy the module map into the directory with installed header files
  mkdir -p build-apple/$config_name/install/include/liblcms2-Module  
  cp module.modulemap build-apple/$config_name/install/include/liblcms2-Module/module.modulemap
  exit_if_error
  
  # Strip installed library
  strip -S build-apple/$config_name/install/lib/liblcms2.a #>> build-apple/log.txt
  exit_if_error
}


build_library MacOSX           arm64  macos11
build_library MacOSX           x86_64 macos10.13
build_library iPhoneOS         arm64  ios12
build_library iPhoneSimulator  arm64  ios14-simulator
build_library iPhoneSimulator  x86_64 ios12-simulator
build_library AppleTVOS        arm64  tvos12
build_library AppleTVSimulator arm64  tvos12-simulator
build_library AppleTVSimulator x86_64 tvos12-simulator
build_library WatchOS          arm64  watchos8
build_library WatchSimulator   arm64  watchos8-simulator
build_library WatchSimulator   x86_64 watchos8-simulator
build_library XROS             arm64  xros1
build_library XRSimulator      arm64  xros1-simulator
build_library XRSimulator      x86_64 xros1-simulator

# Build for Android
# Not supported at the moment
# build_library Android aarch64 21
# build_library Android arm     21
# build_library Android i686    21
# build_library Android riscv64 35
# build_library Android x86_64  21


create_framework() {
  # Remove previously created framework if exists
  rm -rf build-apple/liblcms2.xcframework
  exit_if_error

  # Merge macOS arm and x86 binaries
  mkdir -p build-apple/MacOSX
  exit_if_error
  lipo -create -output build-apple/MacOSX/liblcms2.a \
    build-apple/MacOSX/arm64/install/lib/liblcms2.a \
    build-apple/MacOSX/x86_64/install/lib/liblcms2.a
  exit_if_error

  # Merge iOS simulator arm and x86 binaries
  mkdir -p build-apple/iPhoneSimulator
  exit_if_error
  lipo -create -output build-apple/iPhoneSimulator/liblcms2.a \
    build-apple/iPhoneSimulator/arm64/install/lib/liblcms2.a \
    build-apple/iPhoneSimulator/x86_64/install/lib/liblcms2.a
  exit_if_error

  # Merge tvOS simulator arm and x86 binaries
  mkdir -p build-apple/AppleTVSimulator
  exit_if_error
  lipo -create -output build-apple/AppleTVSimulator/liblcms2.a \
    build-apple/AppleTVSimulator/arm64/install/lib/liblcms2.a \
    build-apple/AppleTVSimulator/x86_64/install/lib/liblcms2.a
  exit_if_error

  # Merge watchOS simulator arm and x86 binaries
  mkdir -p build-apple/WatchSimulator
  exit_if_error
  lipo -create -output build-apple/WatchSimulator/liblcms2.a \
    build-apple/WatchSimulator/arm64/install/lib/liblcms2.a \
    build-apple/WatchSimulator/x86_64/install/lib/liblcms2.a
  exit_if_error

  # Merge visionOS simulator arm and x86 binaries
  mkdir -p build-apple/XRSimulator
  exit_if_error
  lipo -create -output build-apple/XRSimulator/liblcms2.a \
    build-apple/XRSimulator/arm64/install/lib/liblcms2.a \
    build-apple/XRSimulator/x86_64/install/lib/liblcms2.a
  exit_if_error

  # Create the framework with multiple platforms
  xcodebuild -create-xcframework \
    -library build-apple/MacOSX/liblcms2.a                      -headers build-apple/MacOSX/arm64/install/include \
    -library build-apple/iPhoneOS/arm64/install/lib/liblcms2.a  -headers build-apple/iPhoneOS/arm64/install/include \
    -library build-apple/iPhoneSimulator/liblcms2.a             -headers build-apple/iPhoneSimulator/arm64/install/include \
    -library build-apple/AppleTVOS/arm64/install/lib/liblcms2.a -headers build-apple/AppleTVOS/arm64/install/include \
    -library build-apple/AppleTVSimulator/liblcms2.a            -headers build-apple/AppleTVSimulator/arm64/install/include \
    -library build-apple/WatchOS/arm64/install/lib/liblcms2.a   -headers build-apple/WatchOS/arm64/install/include \
    -library build-apple/WatchSimulator/liblcms2.a              -headers build-apple/WatchSimulator/arm64/install/include \
    -library build-apple/XROS/arm64/install/lib/liblcms2.a      -headers build-apple/XROS/arm64/install/include \
    -library build-apple/XRSimulator/liblcms2.a                 -headers build-apple/XRSimulator/arm64/install/include \
    -output build-apple/liblcms2.xcframework
  exit_if_error

  # And sign the framework
  codesign --timestamp -s $identity build-apple/liblcms2.xcframework
  exit_if_error
}
create_framework







# 8===o