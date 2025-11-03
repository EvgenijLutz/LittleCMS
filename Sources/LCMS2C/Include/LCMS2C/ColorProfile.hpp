//
//  ColorProfile.hpp
//  LCMS2
//
//  Created by Evgenij Lutz on 03.11.25.
//

#pragma once

#include <LCMS2C/Common.hpp>


class LCMSColorProfile final {
private:
    std::atomic<size_t> _referenceCounter;
    const char* lc_nonnull _data;
    long _size;
    
    LCMSColorProfile(const char* lc_nonnull data, long size);
    ~LCMSColorProfile();
    
    friend LCMSColorProfile* lc_nullable LCMSColorProfileRetain(LCMSColorProfile* lc_nullable value) SWIFT_RETURNS_UNRETAINED;
    friend void LCMSColorProfileRelease(LCMSColorProfile* lc_nullable value);
    
public:
    static LCMSColorProfile* lc_nonnull create(const void* lc_nonnull data, long size) SWIFT_RETURNS_RETAINED;
    /// Rec. 709 - the ITU-R Recommendation 709 standard.
    static LCMSColorProfile* lc_nonnull createRec709() SWIFT_RETURNS_RETAINED;
    static LCMSColorProfile* lc_nonnull createDCIP3() SWIFT_RETURNS_RETAINED;
    static LCMSColorProfile* lc_nonnull createDCIP3D65() SWIFT_RETURNS_RETAINED;
    
    LCMSColorProfile* lc_nullable createLinear() SWIFT_RETURNS_RETAINED;
    
    const char* lc_nonnull getData() SWIFT_COMPUTED_PROPERTY { return _data; }
    long getSize() SWIFT_COMPUTED_PROPERTY { return _size; }
}
SWIFT_SHARED_REFERENCE(LCMSColorProfileRetain, LCMSColorProfileRelease)
SWIFT_UNCHECKED_SENDABLE;
