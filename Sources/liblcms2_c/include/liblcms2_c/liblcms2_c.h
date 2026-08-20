//
//  liblcms2_c.h
//  LCMS2
//
//  Created by Evgenij Lutz on 06.07.26.
//

#pragma once

#include <lcms2.h>

#if defined __cplusplus
extern "C" {
#endif

extern const cmsUInt32Number liblcms2_TYPE_GRAY_8;
extern const cmsUInt32Number liblcms2_TYPE_GRAY_8_REV;
extern const cmsUInt32Number liblcms2_TYPE_GRAY_16;
extern const cmsUInt32Number liblcms2_TYPE_GRAY_16_REV;
extern const cmsUInt32Number liblcms2_TYPE_GRAY_16_SE;
extern const cmsUInt32Number liblcms2_TYPE_GRAYA_8;
extern const cmsUInt32Number liblcms2_TYPE_GRAYA_8_PREMUL;
extern const cmsUInt32Number liblcms2_TYPE_GRAYA_16;
extern const cmsUInt32Number liblcms2_TYPE_GRAYA_16_PREMUL;
extern const cmsUInt32Number liblcms2_TYPE_GRAYA_16_SE;
extern const cmsUInt32Number liblcms2_TYPE_GRAYA_8_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_GRAYA_16_PLANAR;

extern const cmsUInt32Number liblcms2_TYPE_RGB_8;
extern const cmsUInt32Number liblcms2_TYPE_RGB_8_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_BGR_8;
extern const cmsUInt32Number liblcms2_TYPE_BGR_8_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_RGB_16;
extern const cmsUInt32Number liblcms2_TYPE_RGB_16_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_RGB_16_SE;
extern const cmsUInt32Number liblcms2_TYPE_BGR_16;
extern const cmsUInt32Number liblcms2_TYPE_BGR_16_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_BGR_16_SE;

extern const cmsUInt32Number liblcms2_TYPE_RGBA_8;
extern const cmsUInt32Number liblcms2_TYPE_RGBA_8_PREMUL;
extern const cmsUInt32Number liblcms2_TYPE_RGBA_8_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_RGBA_16;
extern const cmsUInt32Number liblcms2_TYPE_RGBA_16_PREMUL;
extern const cmsUInt32Number liblcms2_TYPE_RGBA_16_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_RGBA_16_SE;

extern const cmsUInt32Number liblcms2_TYPE_ARGB_8;
extern const cmsUInt32Number liblcms2_TYPE_ARGB_8_PREMUL;
extern const cmsUInt32Number liblcms2_TYPE_ARGB_8_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_ARGB_16;
extern const cmsUInt32Number liblcms2_TYPE_ARGB_16_PREMUL;

extern const cmsUInt32Number liblcms2_TYPE_ABGR_8;
extern const cmsUInt32Number liblcms2_TYPE_ABGR_8_PREMUL;
extern const cmsUInt32Number liblcms2_TYPE_ABGR_8_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_ABGR_16;
extern const cmsUInt32Number liblcms2_TYPE_ABGR_16_PREMUL;
extern const cmsUInt32Number liblcms2_TYPE_ABGR_16_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_ABGR_16_SE;

extern const cmsUInt32Number liblcms2_TYPE_BGRA_8;
extern const cmsUInt32Number liblcms2_TYPE_BGRA_8_PREMUL;
extern const cmsUInt32Number liblcms2_TYPE_BGRA_8_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_BGRA_16;
extern const cmsUInt32Number liblcms2_TYPE_BGRA_16_PREMUL;
extern const cmsUInt32Number liblcms2_TYPE_BGRA_16_SE;

extern const cmsUInt32Number liblcms2_TYPE_CMY_8;
extern const cmsUInt32Number liblcms2_TYPE_CMY_8_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_CMY_16;
extern const cmsUInt32Number liblcms2_TYPE_CMY_16_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_CMY_16_SE;

extern const cmsUInt32Number liblcms2_TYPE_CMYK_8;
extern const cmsUInt32Number liblcms2_TYPE_CMYKA_8;
extern const cmsUInt32Number liblcms2_TYPE_CMYK_8_REV;
extern const cmsUInt32Number liblcms2_TYPE_YUVK_8;
extern const cmsUInt32Number liblcms2_TYPE_CMYK_8_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_CMYK_16;
extern const cmsUInt32Number liblcms2_TYPE_CMYK_16_REV;
extern const cmsUInt32Number liblcms2_TYPE_YUVK_16;
extern const cmsUInt32Number liblcms2_TYPE_CMYK_16_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_CMYK_16_SE;

extern const cmsUInt32Number liblcms2_TYPE_KYMC_8;
extern const cmsUInt32Number liblcms2_TYPE_KYMC_16;
extern const cmsUInt32Number liblcms2_TYPE_KYMC_16_SE;

extern const cmsUInt32Number liblcms2_TYPE_KCMY_8;
extern const cmsUInt32Number liblcms2_TYPE_KCMY_8_REV;
extern const cmsUInt32Number liblcms2_TYPE_KCMY_16;
extern const cmsUInt32Number liblcms2_TYPE_KCMY_16_REV;
extern const cmsUInt32Number liblcms2_TYPE_KCMY_16_SE;

extern const cmsUInt32Number liblcms2_TYPE_CMYK5_8;
extern const cmsUInt32Number liblcms2_TYPE_CMYK5_16;
extern const cmsUInt32Number liblcms2_TYPE_CMYK5_16_SE;
extern const cmsUInt32Number liblcms2_TYPE_KYMC5_8;
extern const cmsUInt32Number liblcms2_TYPE_KYMC5_16;
extern const cmsUInt32Number liblcms2_TYPE_KYMC5_16_SE;
extern const cmsUInt32Number liblcms2_TYPE_CMYK6_8;
extern const cmsUInt32Number liblcms2_TYPE_CMYK6_8_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_CMYK6_16;
extern const cmsUInt32Number liblcms2_TYPE_CMYK6_16_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_CMYK6_16_SE;
extern const cmsUInt32Number liblcms2_TYPE_CMYK7_8;
extern const cmsUInt32Number liblcms2_TYPE_CMYK7_16;
extern const cmsUInt32Number liblcms2_TYPE_CMYK7_16_SE;
extern const cmsUInt32Number liblcms2_TYPE_KYMC7_8;
extern const cmsUInt32Number liblcms2_TYPE_KYMC7_16;
extern const cmsUInt32Number liblcms2_TYPE_KYMC7_16_SE;
extern const cmsUInt32Number liblcms2_TYPE_CMYK8_8;
extern const cmsUInt32Number liblcms2_TYPE_CMYK8_16;
extern const cmsUInt32Number liblcms2_TYPE_CMYK8_16_SE;
extern const cmsUInt32Number liblcms2_TYPE_KYMC8_8;
extern const cmsUInt32Number liblcms2_TYPE_KYMC8_16;
extern const cmsUInt32Number liblcms2_TYPE_KYMC8_16_SE;
extern const cmsUInt32Number liblcms2_TYPE_CMYK9_8;
extern const cmsUInt32Number liblcms2_TYPE_CMYK9_16;
extern const cmsUInt32Number liblcms2_TYPE_CMYK9_16_SE;
extern const cmsUInt32Number liblcms2_TYPE_KYMC9_8;
extern const cmsUInt32Number liblcms2_TYPE_KYMC9_16;
extern const cmsUInt32Number liblcms2_TYPE_KYMC9_16_SE;
extern const cmsUInt32Number liblcms2_TYPE_CMYK10_8;
extern const cmsUInt32Number liblcms2_TYPE_CMYK10_16;
extern const cmsUInt32Number liblcms2_TYPE_CMYK10_16_SE;
extern const cmsUInt32Number liblcms2_TYPE_KYMC10_8;
extern const cmsUInt32Number liblcms2_TYPE_KYMC10_16;
extern const cmsUInt32Number liblcms2_TYPE_KYMC10_16_SE;
extern const cmsUInt32Number liblcms2_TYPE_CMYK11_8;
extern const cmsUInt32Number liblcms2_TYPE_CMYK11_16;
extern const cmsUInt32Number liblcms2_TYPE_CMYK11_16_SE;
extern const cmsUInt32Number liblcms2_TYPE_KYMC11_8;
extern const cmsUInt32Number liblcms2_TYPE_KYMC11_16;
extern const cmsUInt32Number liblcms2_TYPE_KYMC11_16_SE;
extern const cmsUInt32Number liblcms2_TYPE_CMYK12_8;
extern const cmsUInt32Number liblcms2_TYPE_CMYK12_16;
extern const cmsUInt32Number liblcms2_TYPE_CMYK12_16_SE;
extern const cmsUInt32Number liblcms2_TYPE_KYMC12_8;
extern const cmsUInt32Number liblcms2_TYPE_KYMC12_16;
extern const cmsUInt32Number liblcms2_TYPE_KYMC12_16_SE;

// Colorimetric
extern const cmsUInt32Number liblcms2_TYPE_XYZ_16;
extern const cmsUInt32Number liblcms2_TYPE_Lab_8;
extern const cmsUInt32Number liblcms2_TYPE_LabV2_8;

extern const cmsUInt32Number liblcms2_TYPE_ALab_8;
extern const cmsUInt32Number liblcms2_TYPE_ALabV2_8;
extern const cmsUInt32Number liblcms2_TYPE_Lab_16;
extern const cmsUInt32Number liblcms2_TYPE_LabV2_16;
extern const cmsUInt32Number liblcms2_TYPE_Yxy_16;

// YCbCr
extern const cmsUInt32Number liblcms2_TYPE_YCbCr_8;
extern const cmsUInt32Number liblcms2_TYPE_YCbCr_8_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_YCbCr_16;
extern const cmsUInt32Number liblcms2_TYPE_YCbCr_16_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_YCbCr_16_SE;

// YUV
extern const cmsUInt32Number liblcms2_TYPE_YUV_8;
extern const cmsUInt32Number liblcms2_TYPE_YUV_8_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_YUV_16;
extern const cmsUInt32Number liblcms2_TYPE_YUV_16_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_YUV_16_SE;

// HLS
extern const cmsUInt32Number liblcms2_TYPE_HLS_8;
extern const cmsUInt32Number liblcms2_TYPE_HLS_8_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_HLS_16;
extern const cmsUInt32Number liblcms2_TYPE_HLS_16_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_HLS_16_SE;

// HSV
extern const cmsUInt32Number liblcms2_TYPE_HSV_8;
extern const cmsUInt32Number liblcms2_TYPE_HSV_8_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_HSV_16;
extern const cmsUInt32Number liblcms2_TYPE_HSV_16_PLANAR;
extern const cmsUInt32Number liblcms2_TYPE_HSV_16_SE;

// Named color index. Only 16 bits is allowed (don't check colorspace)
extern const cmsUInt32Number liblcms2_TYPE_NAMED_COLOR_INDEX;

// Float formatters.
extern const cmsUInt32Number liblcms2_TYPE_XYZ_FLT;
extern const cmsUInt32Number liblcms2_TYPE_Lab_FLT;
extern const cmsUInt32Number liblcms2_TYPE_LabA_FLT;
extern const cmsUInt32Number liblcms2_TYPE_GRAY_FLT;
extern const cmsUInt32Number liblcms2_TYPE_GRAYA_FLT;
extern const cmsUInt32Number liblcms2_TYPE_GRAYA_FLT_PREMUL;
extern const cmsUInt32Number liblcms2_TYPE_RGB_FLT;

extern const cmsUInt32Number liblcms2_TYPE_RGBA_FLT;
extern const cmsUInt32Number liblcms2_TYPE_RGBA_FLT_PREMUL;
extern const cmsUInt32Number liblcms2_TYPE_ARGB_FLT;
extern const cmsUInt32Number liblcms2_TYPE_ARGB_FLT_PREMUL;
extern const cmsUInt32Number liblcms2_TYPE_BGR_FLT;
extern const cmsUInt32Number liblcms2_TYPE_BGRA_FLT;
extern const cmsUInt32Number liblcms2_TYPE_BGRA_FLT_PREMUL;
extern const cmsUInt32Number liblcms2_TYPE_ABGR_FLT;
extern const cmsUInt32Number liblcms2_TYPE_ABGR_FLT_PREMUL;

extern const cmsUInt32Number liblcms2_TYPE_CMYK_FLT;

// Floating point formatters.
// NOTE THAT 'BYTES' FIELD IS SET TO ZERO ON DLB because 8 bytes overflows the bitfield
extern const cmsUInt32Number liblcms2_TYPE_XYZ_DBL;
extern const cmsUInt32Number liblcms2_TYPE_Lab_DBL;
extern const cmsUInt32Number liblcms2_TYPE_GRAY_DBL;
extern const cmsUInt32Number liblcms2_TYPE_RGB_DBL;
extern const cmsUInt32Number liblcms2_TYPE_BGR_DBL;
extern const cmsUInt32Number liblcms2_TYPE_CMYK_DBL;
extern const cmsUInt32Number liblcms2_TYPE_OKLAB_DBL;

// IEEE 754-2008 "half"
extern const cmsUInt32Number liblcms2_TYPE_GRAY_HALF_FLT;
extern const cmsUInt32Number liblcms2_TYPE_RGB_HALF_FLT;
extern const cmsUInt32Number liblcms2_TYPE_CMYK_HALF_FLT;

extern const cmsUInt32Number liblcms2_TYPE_RGBA_HALF_FLT;
extern const cmsUInt32Number liblcms2_TYPE_ARGB_HALF_FLT;
extern const cmsUInt32Number liblcms2_TYPE_BGR_HALF_FLT;
extern const cmsUInt32Number liblcms2_TYPE_BGRA_HALF_FLT;
extern const cmsUInt32Number liblcms2_TYPE_ABGR_HALF_FLT;

#if defined __cplusplus
}
#endif
