// The Swift Programming Language
// https://docs.swift.org/swift-book

import Foundation
@_exported import LCMS2C


public enum LittleCMSError: Error {
    case unknown
    case other(_ message: String)
}


#if canImport(CoreGraphics)

import CoreGraphics


@available(macOS 13.3.0, iOS 16.4.0, tvOS 16.4.0, visionOS 1.0, watchOS 9.4, *)
public extension LCMSColorProfile {
    var colorSpace: CGColorSpace? {        
        guard size > 0 else {
            return nil
        }
        
        let iccProfileData = Data(bytes: data, count: size)
        guard let colorProfile = CGColorSpace(iccData: iccProfileData as CFData) else {
            return nil
        }
        
        return colorProfile
    }
    
    var name: String {
        let _name = __getNameUnsafe()
        let string = String(cString: _name)
        return string
    }
}


@available(macOS 13.3.0, iOS 16.4.0, tvOS 16.4.0, visionOS 1.0, watchOS 9.4, *)
public extension LCMSImage {
    /// CGImage representation.
    ///
    ///
    var cgImage: CGImage  {
        get throws {
            let contents = Data(bytes: data, count: dataSize)
            guard let dataProvider = CGDataProvider(data: contents as CFData) else {
                throw LittleCMSError.other("No data provider :(")
            }
            
            let colorSpace: CGColorSpace? = {
                // Create color space from LCMSImage's ICC profile info
                if let colorProfile, let colorSpace = colorProfile.colorSpace {
                    if ishdr, let hdrColorSpace = CGColorSpaceCreateExtended(colorSpace) {
                        return hdrColorSpace
                    }
                    
                    return colorSpace
                }
                
                // Guess the color profile
                //return CGColorSpace(name: CGColorSpace.sRGB)
                //return CGColorSpace(name: CGColorSpace.linearDisplayP3)
                //return CGColorSpace(name: CGColorSpace.extendedDisplayP3)
                return CGColorSpace(name: CGColorSpace.extendedLinearDisplayP3)
            }()
            
            guard let colorSpace = colorSpace else {
                throw LittleCMSError.other("No color space :(")
            }
            
            let alphaFlag: UInt32
            if numComponents == 2 || numComponents == 4 {
                alphaFlag = CGImageAlphaInfo.premultipliedLast.rawValue
                //alphaFlag = CGImageAlphaInfo.noneSkipLast.rawValue
            }
            else {
                alphaFlag = 0
            }
            
            let image = CGImage(
                width: width,
                height: height,
                bitsPerComponent: componentSize * 8,
                bitsPerPixel: numComponents * componentSize * 8,
                bytesPerRow: width * numComponents * componentSize,
                space: colorSpace,
                bitmapInfo: .init(rawValue: alphaFlag | CGBitmapInfo.byteOrderDefault.rawValue),
                provider: dataProvider,
                decode: nil,
                shouldInterpolate: true,
                intent: .defaultIntent
            )
            guard let image else {
                throw LittleCMSError.other("Could not create CGImage")
            }
            
            return image
        }
    }
}

#endif
