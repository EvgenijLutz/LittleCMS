// swift-tools-version: 6.2
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "LCMS2",
    // See the "Minimum Deployment Version for Reference Types Imported from C++":
    // https://www.swift.org/documentation/cxx-interop/status/
    platforms: [
        .macOS(.v14),
        .iOS(.v17),
        .tvOS(.v17),
        .watchOS(.v10),
        .visionOS(.v1)
    ],
    products: [
        .library(
            name: "LittleCMS",
            targets: ["LittleCMS"]
        ),
        .library(
            name: "LCMS2C",
            targets: ["LCMS2C"]
        ),
        .library(
            name: "liblcms2",
            targets: ["liblcms2"]
        ),
    ],
    targets: [
        .binaryTarget(
            name: "liblcms2",
            path: "Binaries/liblcms2.xcframework"
        ),
        .target(
            name: "LCMS2C",
            dependencies: [
                .target(name: "liblcms2")
            ],
            cxxSettings: [
                .enableWarning("all")
            ]
        ),
        .target(
            name: "LittleCMS",
            dependencies: [
                .target(name: "LCMS2C")
            ],
            swiftSettings: [
                .interoperabilityMode(.Cxx)
            ]
        ),
    ],
    // The lcms2 library was compiled using c17, so set it also here
    cLanguageStandard: .c17,
    // Also use c++20, we don't live in the stone age, but still not ready to accept c++23
    cxxLanguageStandard: .cxx20
)
