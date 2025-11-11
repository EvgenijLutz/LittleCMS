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


public extension LCMSColorProfile {
    var colorSpace: CGColorSpace? {        
        guard size > 0 else {
            return nil
        }
        
        let iccProfileData = Data(bytes: data, count: size)
        guard let colorProfile = CGColorSpace(iccData: iccProfileData as CFData) else {
            return nil
        }
        
        //if hdr {
        //    if let extendedColorProfile = CGColorSpaceCreateExtended(colorProfile) {
        //        return extendedColorProfile
        //    }
        //}
        
        return colorProfile
    }
}


public extension LCMSImage {
    var cgImage: CGImage  {
        get throws {
            let contents = Data(bytes: data, count: dataSize)
            guard let dataProvider = CGDataProvider(data: contents as CFData) else {
                throw LittleCMSError.other("No data provider :(")
            }
            
            let colorSpace: CGColorSpace? = {
#if false
                // Create color space from ImageContainer's ICC profile info
                if let iccData {
                    let iccContents = Data(bytes: iccData, count: iccDataLength)
                    let iccData = iccContents as CFData
                    return CGColorSpace(iccData: iccData)
                }
#endif
                
                //return CGColorSpace(name: CGColorSpace.sRGB)
                //return CGColorSpace(name: CGColorSpace.linearDisplayP3)
                //return CGColorSpace(name: CGColorSpace.extendedDisplayP3)
                return CGColorSpace(name: CGColorSpace.extendedLinearDisplayP3)
            }()
            guard let colorSpace = colorSpace else {
                throw LittleCMSError.other("No color space :(")
            }
            do {
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
