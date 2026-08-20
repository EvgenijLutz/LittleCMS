//
//  Swift_CMSColorProfile.swift
//  LCMS2
//
//  Created by Evgenij Lutz on 20.08.26.
//

import Foundation
import liblcms2_c


@safe enum CMSError: Error, Sendable {
    case cannotOpenProfile
    case unsupportedComponentType
    case unsupportedNumberOfChannels
}


/// LittleCMS colour profile.
@available(macOS 13.3, iOS 16.4, tvOS 16.4, watchOS 9.4, visionOS 1.0, *)
@safe final class Swift_CMSColorProfile: Sendable {
    @safe private struct cmsHPROFILEWrapper: @unchecked Sendable {
        let profile: cmsHPROFILE
    }
    private let profile: cmsHPROFILEWrapper
    
    private let name: String?
    
    
    @safe private init(profile: cmsHPROFILE) {
        self.profile = unsafe .init(profile: profile)
        name = nil
    }
    
    
    /// Open colour profile from contents of a raw buffer.
    public convenience init(_ data: Data) throws {
        let profile: cmsHPROFILE? = unsafe data.withUnsafeBytes { pointer in
            guard let baseAddress = pointer.baseAddress else {
                return nil
            }
            
            return unsafe cmsOpenProfileFromMem(baseAddress, .init(data.count))
        }
        guard let profile = unsafe profile else {
            throw CMSError.cannotOpenProfile
        }
        
        self.init(profile: profile)
    }
    
    
    /// Open colour profile from a file.
    public convenience init(url: URL) throws {
        let path = url.path(percentEncoded: false)
        try self.init(path: path)
    }
    
    
    /// Open colour profile from a file.
    public convenience init(path: String) throws {
        let profile = unsafe path.withCString { cPath in
            unsafe "r".withCString { cMode in
                unsafe cmsOpenProfileFromFile(cPath, cMode)
            }
        }

        guard let profile = unsafe profile else {
            throw CMSError.cannotOpenProfile
        }
        
        self.init(profile: profile)
    }
    
    
    deinit {
        unsafe cmsCloseProfile(profile.profile)
    }
    
    
    enum ComponentType {
        case uint8
        
        case uint16
        case float16
        
        case float32
        
        var stride: Int {
            switch self {
            case .uint8: 1
            
            case .uint16: 2
            case .float16: 2
                
            case .float32: 4
            }
        }
    }
    
    
    static func convert(from sourceProfile: Swift_CMSColorProfile, to destinationProfile: Swift_CMSColorProfile,
                        data: Data,
                        width: Int, height: Int, depth: Int = 1,
                        numComponents: Int, componentType: ComponentType,
                        strideBytes: Int? = nil,
                        copyAlpha: Bool = false,
                        progress: @escaping (_ progress: Float) -> Void) async throws -> Data {
        var destination = Data(data)
        try await convert(from: sourceProfile, to: destinationProfile, source: data, destination: &destination, width: width, height: height, depth: depth, numComponents: numComponents, componentType: componentType, strideBytes: strideBytes, copyAlpha: copyAlpha, progress: progress)
        return destination
    }
    
    
    @safe static func convert(from sourceProfile: Swift_CMSColorProfile, to destinationProfile: Swift_CMSColorProfile,
                              contents: UnsafeMutableRawPointer,
                              count: Int,
                              width: Int, height: Int, depth: Int = 1,
                              numComponents: Int, componentType: ComponentType,
                              strideBytes: Int? = nil,
                              copyAlpha: Bool = false,
                              progress: @escaping (_ progress: Float) -> Void) async throws {
        var buffer = unsafe Data(bytesNoCopy: contents, count: count, deallocator: .none)
        try await convert(from: sourceProfile, to: destinationProfile, source: buffer, destination: &buffer, width: width, height: height, depth: depth, numComponents: numComponents, componentType: componentType, strideBytes: strideBytes, copyAlpha: copyAlpha, progress: progress)
    }
    
    
    static func convert(from sourceProfile: Swift_CMSColorProfile, to destinationProfile: Swift_CMSColorProfile,
                        source: Data, destination: inout Data,
                        width: Int, height: Int, depth: Int = 1,
                        numComponents: Int, componentType: ComponentType,
                        strideBytes: Int? = nil,
                        copyAlpha: Bool = false,
                        progress: @escaping (_ progress: Float) -> Void) async throws {
        // Do nothing if the profiles are the same
        if sourceProfile === destinationProfile {
            return
        }
        
        // Some processing flags
        var flags: cmsUInt32Number = .init(cmsFLAGS_NOCACHE) |
            .init(cmsFLAGS_NOOPTIMIZE) |
            .init(cmsFLAGS_HIGHRESPRECALC) |
            .init(cmsFLAGS_GAMUTCHECK) |
            .init(cmsFLAGS_NOWHITEONWHITEFIXUP) |
            .init(cmsFLAGS_NONEGATIVES)
        if copyAlpha {
            flags = flags | .init(cmsFLAGS_COPY_ALPHA)
        }
        
        // Input/output pixel format
        let format: cmsUInt32Number
        switch numComponents {
        case 1:
            switch componentType {
            case .uint8: format = liblcms2_TYPE_GRAY_8
            case .uint16: format = liblcms2_TYPE_GRAY_16
            case .float16: format = liblcms2_TYPE_GRAY_HALF_FLT
            case .float32: format = liblcms2_TYPE_GRAY_FLT
            }
            
        case 2:
            switch componentType {
            case .uint8: format = liblcms2_TYPE_GRAYA_8
            case .uint16: format = liblcms2_TYPE_GRAYA_16
            case .float16: throw CMSError.unsupportedComponentType
            case .float32: format = liblcms2_TYPE_GRAYA_FLT
            }
            
        case 3:
            switch componentType {
            case .uint8: format = liblcms2_TYPE_RGB_8
            case .uint16: format = liblcms2_TYPE_RGB_16
            case .float16: format = liblcms2_TYPE_RGB_HALF_FLT
            case .float32: format = liblcms2_TYPE_RGB_FLT
            }
            
        case 4:
            switch componentType {
            case .uint8: format = liblcms2_TYPE_RGBA_8
            case .uint16: format = liblcms2_TYPE_RGBA_16
            case .float16: format = liblcms2_TYPE_RGBA_HALF_FLT
            case .float32: format = liblcms2_TYPE_RGBA_FLT
            }
            
        default:
            throw CMSError.unsupportedNumberOfChannels
        }
        
        // Transform, wrap it into a class to ensure proper lifetime
        let transform: cmsHTRANSFORM = unsafe cmsCreateTransform(sourceProfile.profile.profile, format,
                                                                 destinationProfile.profile.profile, format,
                                                                 .init(INTENT_ABSOLUTE_COLORIMETRIC),
                                                                 flags);
        @safe class TransformWrapper: @unchecked Sendable {
            let transform: cmsHTRANSFORM
            
            init(transform: cmsHTRANSFORM) {
                unsafe self.transform = transform
            }
            
            deinit {
                unsafe cmsDeleteTransform(transform)
            }
        }
        let transformWrapper = unsafe TransformWrapper(transform: transform)
        
        // Prepare often used constants
        let stride = strideBytes ?? (componentType.stride * numComponents)
        let rowSize = width * stride
        
        struct TaskResult: Sendable {
            let data: Data
            let offset: Int
        }
        
        // Parallelise processing of each row
        try await withThrowingTaskGroup { group in
            // Populate tasks that return processed rows
            for y in 0 ..< height {
                let offset = y * rowSize
                group.addTask {
                    try Task.checkCancellation()
                    
                    var data = Data(count: rowSize)
                    
                    unsafe source.withUnsafeBytes { _source in
                        unsafe data.withUnsafeMutableBytes { _data in
                            if let sourceBaseAddress = unsafe _source.baseAddress?.advanced(by: offset), let destinationBaseAddress = _data.baseAddress {
                                unsafe cmsDoTransform(transformWrapper.transform, sourceBaseAddress, destinationBaseAddress.advanced(by: offset), .init(rowSize))
                            }
                        }
                    }
                    
                    return TaskResult(data: data, offset: offset)
                }
            }
            
            // Accumulate processed rows in the output buffer
            var groupsFinished = 0
            for try await result in group {
                destination.replaceSubrange(result.offset ... (result.offset + result.data.count), with: result.data)
                
                // Report progress
                groupsFinished += 1
                progress(Float(groupsFinished) / Float(height))
            }
        }
        
        // Report progress
        progress(1)
    }
    
}
