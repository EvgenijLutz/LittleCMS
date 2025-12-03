//
//  ColorProfile.hpp
//  LCMS2
//
//  Created by Evgenij Lutz on 03.11.25.
//

#pragma once

#include <LCMS2C/Common.hpp>


/// Colour profile.
///
/// Contains `International Color Consortium`'s colour profile data.
///
/// - Seealso: [International Color Consortium](https://www.color.org/index.xalter)
class LCMSColorProfile final {
private:
    std::atomic<size_t> _referenceCounter;
    const char* fn_nonnull _data;
    long _size;
    
    LCMSColorProfile(const char* fn_nonnull data fn_noescape, long size);
    ~LCMSColorProfile();
    
    friend LCMSColorProfile* fn_nullable LCMSColorProfileRetain(LCMSColorProfile* fn_nullable value) SWIFT_RETURNS_UNRETAINED;
    friend void LCMSColorProfileRelease(LCMSColorProfile* fn_nullable value);
    
public:
    static LCMSColorProfile* fn_nonnull create(const void* fn_nonnull data fn_noescape, long size) SWIFT_RETURNS_RETAINED;
    
    /// sRGB color profile.
    ///
    /// - Seealso: [sRGB profiles](https://www.color.org/srgbprofiles.xalter)
    static LCMSColorProfile* fn_nonnull createSRGB() SWIFT_RETURNS_RETAINED;
    
    /// Rec. 709 Reference Display - the ITU-R Recommendation 709 standard.
    ///
    /// - Seealso: [Rec. 709 Reference Display](https://www.color.org/rec709.xalter)
    static LCMSColorProfile* fn_nonnull createRec709() SWIFT_RETURNS_RETAINED;
    
    /// Rec. 2020 or BT.2020
    ///
    /// - Seealso: [BT.2020](https://www.color.org/chardata/rgb/BT2020.xalter)
    static LCMSColorProfile* fn_nonnull createRec2020() SWIFT_RETURNS_RETAINED;
    
    static LCMSColorProfile* fn_nonnull createDCIP3() SWIFT_RETURNS_RETAINED;
    static LCMSColorProfile* fn_nonnull createDCIP3D65() SWIFT_RETURNS_RETAINED;
    
    LCMSColorProfile* fn_nullable createLinear(bool force = true) SWIFT_RETURNS_RETAINED SWIFT_NAME(createLinear(force:));
    
    const char* fn_nonnull getData() SWIFT_COMPUTED_PROPERTY { return _data; }
    long getSize() SWIFT_COMPUTED_PROPERTY { return _size; }
    
    bool checkIsLinear();
    bool checkIsSRGB();
}
SWIFT_SHARED_REFERENCE(LCMSColorProfileRetain, LCMSColorProfileRelease)
SWIFT_UNCHECKED_SENDABLE;
