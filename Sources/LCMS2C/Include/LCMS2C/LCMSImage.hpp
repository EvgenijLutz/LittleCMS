//
//  LCMSImage.hpp
//  LCMS2
//
//  Created by Evgenij Lutz on 03.11.25.
//

#pragma once

#include <LCMS2C/Common.hpp>


class LCMSColorProfile;


class LCMSImage final {
private:
    std::atomic<size_t> _referenceCounter;
    
    char* fn_nonnull _data;
    long _width;
    long _height;
    long _numComponents;
    long _componentSize;
    
    /// Supplementary parameter for hinting if the image is hdr.
    bool _isHDR;
    
    /// If no color profile is specified, it's assumed to be `sRGB`.
    LCMSColorProfile* fn_nullable _colorProfile;
    
    friend LCMSImage* fn_nullable LCMSImageRetain(LCMSImage* fn_nullable container) SWIFT_RETURNS_UNRETAINED;
    friend void LCMSImageRelease(LCMSImage* fn_nullable container);
    
    LCMSImage(char* fn_nonnull data, long width, long height, long numComponents, long componentSize, bool isHDR, LCMSColorProfile* fn_nullable colorProfile);
    ~LCMSImage();
    
public:
    static LCMSImage* fn_nullable create(const char* fn_nonnull data, long width, long height, long numComponents, long componentSize, bool isHDR, LCMSColorProfile* fn_nullable colorProfile = nullptr) SWIFT_RETURNS_RETAINED;
    
    /// If no target color profile is specified, it's assumed to be `sRGB`.
    bool convertColorProfile(LCMSColorProfile* fn_nullable targetColorProfile);
    
    char* fn_nonnull getData() SWIFT_COMPUTED_PROPERTY { return _data; }
    long getDataSize() SWIFT_COMPUTED_PROPERTY { return _width * _height * _numComponents * _componentSize; }
    long getWidth() const SWIFT_COMPUTED_PROPERTY { return _width; }
    long getHeight() const SWIFT_COMPUTED_PROPERTY { return _height; }
    long getNumComponents() const SWIFT_COMPUTED_PROPERTY { return _numComponents; }
    long getComponentSize() const SWIFT_COMPUTED_PROPERTY { return _componentSize; }
    bool getIsHDR() const SWIFT_COMPUTED_PROPERTY { return _isHDR; }
    LCMSColorProfile* fn_nullable getColorProfile() SWIFT_COMPUTED_PROPERTY SWIFT_RETURNS_UNRETAINED { return _colorProfile; }
} SWIFT_SHARED_REFERENCE(LCMSImageRetain, LCMSImageRelease);


LCMSImage* fn_nullable convertToLinearDCIP3(const char* fn_nonnull sourceData,
                                            long width, long height,
                                            long numComponents, long componentSize,
                                            bool isHDR,
                                            const char* fn_nullable iccpData, long iccpLength
                                            ) SWIFT_RETURNS_RETAINED;
