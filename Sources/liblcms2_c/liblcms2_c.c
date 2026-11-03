//
//  liblcms2_c.c
//  LCMS2
//
//  Created by Evgenij Lutz on 06.07.26.
//

#define _LIBCPP_REMOVE_TRANSITIVE_INCLUDES
#include <liblcms2_c/liblcms2_c.h>


const cmsUInt32Number liblcms2_TYPE_GRAY_8 = TYPE_GRAY_8;
const cmsUInt32Number liblcms2_TYPE_GRAY_8_REV = TYPE_GRAY_8_REV;
const cmsUInt32Number liblcms2_TYPE_GRAY_16 = TYPE_GRAY_16;
const cmsUInt32Number liblcms2_TYPE_GRAY_16_REV = TYPE_GRAY_16_REV;
const cmsUInt32Number liblcms2_TYPE_GRAY_16_SE = TYPE_GRAY_16_SE;
const cmsUInt32Number liblcms2_TYPE_GRAYA_8 = TYPE_GRAYA_8;
const cmsUInt32Number liblcms2_TYPE_GRAYA_8_PREMUL = TYPE_GRAYA_8_PREMUL;
const cmsUInt32Number liblcms2_TYPE_GRAYA_16 = TYPE_GRAYA_16;
const cmsUInt32Number liblcms2_TYPE_GRAYA_16_PREMUL = TYPE_GRAYA_16_PREMUL;
const cmsUInt32Number liblcms2_TYPE_GRAYA_16_SE = TYPE_GRAYA_16_SE;
const cmsUInt32Number liblcms2_TYPE_GRAYA_8_PLANAR = TYPE_GRAYA_8_PLANAR;
const cmsUInt32Number liblcms2_TYPE_GRAYA_16_PLANAR = TYPE_GRAYA_16_PLANAR;

const cmsUInt32Number liblcms2_TYPE_RGB_8 = TYPE_RGB_8;
const cmsUInt32Number liblcms2_TYPE_RGB_8_PLANAR = TYPE_RGB_8_PLANAR;
const cmsUInt32Number liblcms2_TYPE_BGR_8 = TYPE_BGR_8;
const cmsUInt32Number liblcms2_TYPE_BGR_8_PLANAR = TYPE_BGR_8_PLANAR;
const cmsUInt32Number liblcms2_TYPE_RGB_16 = TYPE_RGB_16;
const cmsUInt32Number liblcms2_TYPE_RGB_16_PLANAR = TYPE_RGB_16_PLANAR;
const cmsUInt32Number liblcms2_TYPE_RGB_16_SE = TYPE_RGB_16_SE;
const cmsUInt32Number liblcms2_TYPE_BGR_16 = TYPE_BGR_16;
const cmsUInt32Number liblcms2_TYPE_BGR_16_PLANAR = TYPE_BGR_16_PLANAR;
const cmsUInt32Number liblcms2_TYPE_BGR_16_SE = TYPE_BGR_16_SE;

const cmsUInt32Number liblcms2_TYPE_RGBA_8 = TYPE_RGBA_8;
const cmsUInt32Number liblcms2_TYPE_RGBA_8_PREMUL = TYPE_RGBA_8_PREMUL;
const cmsUInt32Number liblcms2_TYPE_RGBA_8_PLANAR = TYPE_RGBA_8_PLANAR;
const cmsUInt32Number liblcms2_TYPE_RGBA_16 = TYPE_RGBA_16;
const cmsUInt32Number liblcms2_TYPE_RGBA_16_PREMUL = TYPE_RGBA_16_PREMUL;
const cmsUInt32Number liblcms2_TYPE_RGBA_16_PLANAR = TYPE_RGBA_16_PLANAR;
const cmsUInt32Number liblcms2_TYPE_RGBA_16_SE = TYPE_RGBA_16_SE;

const cmsUInt32Number liblcms2_TYPE_ARGB_8 = TYPE_ARGB_8;
const cmsUInt32Number liblcms2_TYPE_ARGB_8_PREMUL = TYPE_ARGB_8_PREMUL;
const cmsUInt32Number liblcms2_TYPE_ARGB_8_PLANAR = TYPE_ARGB_8_PLANAR;
const cmsUInt32Number liblcms2_TYPE_ARGB_16 = TYPE_ARGB_16;
const cmsUInt32Number liblcms2_TYPE_ARGB_16_PREMUL = TYPE_ARGB_16_PREMUL;

const cmsUInt32Number liblcms2_TYPE_ABGR_8 = TYPE_ABGR_8;
const cmsUInt32Number liblcms2_TYPE_ABGR_8_PREMUL = TYPE_ABGR_8_PREMUL;
const cmsUInt32Number liblcms2_TYPE_ABGR_8_PLANAR = TYPE_ABGR_8_PLANAR;
const cmsUInt32Number liblcms2_TYPE_ABGR_16 = TYPE_ABGR_16;
const cmsUInt32Number liblcms2_TYPE_ABGR_16_PREMUL = TYPE_ABGR_16_PREMUL;
const cmsUInt32Number liblcms2_TYPE_ABGR_16_PLANAR = TYPE_ABGR_16_PLANAR;
const cmsUInt32Number liblcms2_TYPE_ABGR_16_SE = TYPE_ABGR_16_SE;

const cmsUInt32Number liblcms2_TYPE_BGRA_8 = TYPE_BGRA_8;
const cmsUInt32Number liblcms2_TYPE_BGRA_8_PREMUL = TYPE_BGRA_8_PREMUL;
const cmsUInt32Number liblcms2_TYPE_BGRA_8_PLANAR = TYPE_BGRA_8_PLANAR;
const cmsUInt32Number liblcms2_TYPE_BGRA_16 = TYPE_BGRA_16;
const cmsUInt32Number liblcms2_TYPE_BGRA_16_PREMUL = TYPE_BGRA_16_PREMUL;
const cmsUInt32Number liblcms2_TYPE_BGRA_16_SE = TYPE_BGRA_16_SE;

const cmsUInt32Number liblcms2_TYPE_CMY_8 = TYPE_CMY_8;
const cmsUInt32Number liblcms2_TYPE_CMY_8_PLANAR = TYPE_CMY_8_PLANAR;
const cmsUInt32Number liblcms2_TYPE_CMY_16 = TYPE_CMY_16;
const cmsUInt32Number liblcms2_TYPE_CMY_16_PLANAR = TYPE_CMY_16_PLANAR;
const cmsUInt32Number liblcms2_TYPE_CMY_16_SE = TYPE_CMY_16_SE;

const cmsUInt32Number liblcms2_TYPE_CMYK_8 = TYPE_CMYK_8;
const cmsUInt32Number liblcms2_TYPE_CMYKA_8 = TYPE_CMYKA_8;
const cmsUInt32Number liblcms2_TYPE_CMYK_8_REV = TYPE_CMYK_8_REV;
const cmsUInt32Number liblcms2_TYPE_YUVK_8 = TYPE_YUVK_8;
const cmsUInt32Number liblcms2_TYPE_CMYK_8_PLANAR = TYPE_CMYK_8_PLANAR;
const cmsUInt32Number liblcms2_TYPE_CMYK_16 = TYPE_CMYK_16;
const cmsUInt32Number liblcms2_TYPE_CMYK_16_REV = TYPE_CMYK_16_REV;
const cmsUInt32Number liblcms2_TYPE_YUVK_16 = TYPE_YUVK_16;
const cmsUInt32Number liblcms2_TYPE_CMYK_16_PLANAR = TYPE_CMYK_16_PLANAR;
const cmsUInt32Number liblcms2_TYPE_CMYK_16_SE = TYPE_CMYK_16_SE;

const cmsUInt32Number liblcms2_TYPE_KYMC_8 = TYPE_KYMC_8;
const cmsUInt32Number liblcms2_TYPE_KYMC_16 = TYPE_KYMC_16;
const cmsUInt32Number liblcms2_TYPE_KYMC_16_SE = TYPE_KYMC_16_SE;

const cmsUInt32Number liblcms2_TYPE_KCMY_8 = TYPE_KCMY_8;
const cmsUInt32Number liblcms2_TYPE_KCMY_8_REV = TYPE_KCMY_8_REV;
const cmsUInt32Number liblcms2_TYPE_KCMY_16 = TYPE_KCMY_16;
const cmsUInt32Number liblcms2_TYPE_KCMY_16_REV = TYPE_KCMY_16_REV;
const cmsUInt32Number liblcms2_TYPE_KCMY_16_SE = TYPE_KCMY_16_SE;

const cmsUInt32Number liblcms2_TYPE_CMYK5_8 = TYPE_CMYK5_8;
const cmsUInt32Number liblcms2_TYPE_CMYK5_16 = TYPE_CMYK5_16;
const cmsUInt32Number liblcms2_TYPE_CMYK5_16_SE = TYPE_CMYK5_16_SE;
const cmsUInt32Number liblcms2_TYPE_KYMC5_8 = TYPE_KYMC5_8;
const cmsUInt32Number liblcms2_TYPE_KYMC5_16 = TYPE_KYMC5_16;
const cmsUInt32Number liblcms2_TYPE_KYMC5_16_SE = TYPE_KYMC5_16_SE;
const cmsUInt32Number liblcms2_TYPE_CMYK6_8 = TYPE_CMYK6_8;
const cmsUInt32Number liblcms2_TYPE_CMYK6_8_PLANAR = TYPE_CMYK6_8_PLANAR;
const cmsUInt32Number liblcms2_TYPE_CMYK6_16 = TYPE_CMYK6_16;
const cmsUInt32Number liblcms2_TYPE_CMYK6_16_PLANAR = TYPE_CMYK6_16_PLANAR;
const cmsUInt32Number liblcms2_TYPE_CMYK6_16_SE = TYPE_CMYK6_16_SE;
const cmsUInt32Number liblcms2_TYPE_CMYK7_8 = TYPE_CMYK7_8;
const cmsUInt32Number liblcms2_TYPE_CMYK7_16 = TYPE_CMYK7_16;
const cmsUInt32Number liblcms2_TYPE_CMYK7_16_SE = TYPE_CMYK7_16_SE;
const cmsUInt32Number liblcms2_TYPE_KYMC7_8 = TYPE_KYMC7_8;
const cmsUInt32Number liblcms2_TYPE_KYMC7_16 = TYPE_KYMC7_16;
const cmsUInt32Number liblcms2_TYPE_KYMC7_16_SE = TYPE_KYMC7_16_SE;
const cmsUInt32Number liblcms2_TYPE_CMYK8_8 = TYPE_CMYK8_8;
const cmsUInt32Number liblcms2_TYPE_CMYK8_16 = TYPE_CMYK8_16;
const cmsUInt32Number liblcms2_TYPE_CMYK8_16_SE = TYPE_CMYK8_16_SE;
const cmsUInt32Number liblcms2_TYPE_KYMC8_8 = TYPE_KYMC8_8;
const cmsUInt32Number liblcms2_TYPE_KYMC8_16 = TYPE_KYMC8_16;
const cmsUInt32Number liblcms2_TYPE_KYMC8_16_SE = TYPE_KYMC8_16_SE;
const cmsUInt32Number liblcms2_TYPE_CMYK9_8 = TYPE_CMYK9_8;
const cmsUInt32Number liblcms2_TYPE_CMYK9_16 = TYPE_CMYK9_16;
const cmsUInt32Number liblcms2_TYPE_CMYK9_16_SE = TYPE_CMYK9_16_SE;
const cmsUInt32Number liblcms2_TYPE_KYMC9_8 = TYPE_KYMC9_8;
const cmsUInt32Number liblcms2_TYPE_KYMC9_16 = TYPE_KYMC9_16;
const cmsUInt32Number liblcms2_TYPE_KYMC9_16_SE = TYPE_KYMC9_16_SE;
const cmsUInt32Number liblcms2_TYPE_CMYK10_8 = TYPE_CMYK10_8;
const cmsUInt32Number liblcms2_TYPE_CMYK10_16 = TYPE_CMYK10_16;
const cmsUInt32Number liblcms2_TYPE_CMYK10_16_SE = TYPE_CMYK10_16_SE;
const cmsUInt32Number liblcms2_TYPE_KYMC10_8 = TYPE_KYMC10_8;
const cmsUInt32Number liblcms2_TYPE_KYMC10_16 = TYPE_KYMC10_16;
const cmsUInt32Number liblcms2_TYPE_KYMC10_16_SE = TYPE_KYMC10_16_SE;
const cmsUInt32Number liblcms2_TYPE_CMYK11_8 = TYPE_CMYK11_8;
const cmsUInt32Number liblcms2_TYPE_CMYK11_16 = TYPE_CMYK11_16;
const cmsUInt32Number liblcms2_TYPE_CMYK11_16_SE = TYPE_CMYK11_16_SE;
const cmsUInt32Number liblcms2_TYPE_KYMC11_8 = TYPE_KYMC11_8;
const cmsUInt32Number liblcms2_TYPE_KYMC11_16 = TYPE_KYMC11_16;
const cmsUInt32Number liblcms2_TYPE_KYMC11_16_SE = TYPE_KYMC11_16_SE;
const cmsUInt32Number liblcms2_TYPE_CMYK12_8 = TYPE_CMYK12_8;
const cmsUInt32Number liblcms2_TYPE_CMYK12_16 = TYPE_CMYK12_16;
const cmsUInt32Number liblcms2_TYPE_CMYK12_16_SE = TYPE_CMYK12_16_SE;
const cmsUInt32Number liblcms2_TYPE_KYMC12_8 = TYPE_KYMC12_8;
const cmsUInt32Number liblcms2_TYPE_KYMC12_16 = TYPE_KYMC12_16;
const cmsUInt32Number liblcms2_TYPE_KYMC12_16_SE = TYPE_KYMC12_16_SE;

// Colorimetric
const cmsUInt32Number liblcms2_TYPE_XYZ_16 = TYPE_XYZ_16;
const cmsUInt32Number liblcms2_TYPE_Lab_8 = TYPE_Lab_8;
const cmsUInt32Number liblcms2_TYPE_LabV2_8 = TYPE_LabV2_8;

const cmsUInt32Number liblcms2_TYPE_ALab_8 = TYPE_ALab_8;
const cmsUInt32Number liblcms2_TYPE_ALabV2_8 = TYPE_ALabV2_8;
const cmsUInt32Number liblcms2_TYPE_Lab_16 = TYPE_Lab_16;
const cmsUInt32Number liblcms2_TYPE_LabV2_16 = TYPE_LabV2_16;
const cmsUInt32Number liblcms2_TYPE_Yxy_16 = TYPE_Yxy_16;

// YCbCr
const cmsUInt32Number liblcms2_TYPE_YCbCr_8 = TYPE_YCbCr_8;
const cmsUInt32Number liblcms2_TYPE_YCbCr_8_PLANAR = TYPE_YCbCr_8_PLANAR;
const cmsUInt32Number liblcms2_TYPE_YCbCr_16 = TYPE_YCbCr_16;
const cmsUInt32Number liblcms2_TYPE_YCbCr_16_PLANAR = TYPE_YCbCr_16_PLANAR;
const cmsUInt32Number liblcms2_TYPE_YCbCr_16_SE = TYPE_YCbCr_16_SE;

// YUV
const cmsUInt32Number liblcms2_TYPE_YUV_8 = TYPE_YUV_8;
const cmsUInt32Number liblcms2_TYPE_YUV_8_PLANAR = TYPE_YUV_8_PLANAR;
const cmsUInt32Number liblcms2_TYPE_YUV_16 = TYPE_YUV_16;
const cmsUInt32Number liblcms2_TYPE_YUV_16_PLANAR = TYPE_YUV_16_PLANAR;
const cmsUInt32Number liblcms2_TYPE_YUV_16_SE = TYPE_YUV_16_SE;

// HLS
const cmsUInt32Number liblcms2_TYPE_HLS_8 = TYPE_HLS_8;
const cmsUInt32Number liblcms2_TYPE_HLS_8_PLANAR = TYPE_HLS_8_PLANAR;
const cmsUInt32Number liblcms2_TYPE_HLS_16 = TYPE_HLS_16;
const cmsUInt32Number liblcms2_TYPE_HLS_16_PLANAR = TYPE_HLS_16_PLANAR;
const cmsUInt32Number liblcms2_TYPE_HLS_16_SE = TYPE_HLS_16_SE;

// HSV
const cmsUInt32Number liblcms2_TYPE_HSV_8 = TYPE_HSV_8;
const cmsUInt32Number liblcms2_TYPE_HSV_8_PLANAR = TYPE_HSV_8_PLANAR;
const cmsUInt32Number liblcms2_TYPE_HSV_16 = TYPE_HSV_16;
const cmsUInt32Number liblcms2_TYPE_HSV_16_PLANAR = TYPE_HSV_16_PLANAR;
const cmsUInt32Number liblcms2_TYPE_HSV_16_SE = TYPE_HSV_16_SE;

// Named color index. Only 16 bits is allowed (don't check colorspace)
const cmsUInt32Number liblcms2_TYPE_NAMED_COLOR_INDEX = TYPE_NAMED_COLOR_INDEX;

// Float formatters.
const cmsUInt32Number liblcms2_TYPE_XYZ_FLT = TYPE_XYZ_FLT;
const cmsUInt32Number liblcms2_TYPE_Lab_FLT = TYPE_Lab_FLT;
const cmsUInt32Number liblcms2_TYPE_LabA_FLT = TYPE_LabA_FLT;
const cmsUInt32Number liblcms2_TYPE_GRAY_FLT = TYPE_GRAY_FLT;
const cmsUInt32Number liblcms2_TYPE_GRAYA_FLT = TYPE_GRAYA_FLT;
const cmsUInt32Number liblcms2_TYPE_GRAYA_FLT_PREMUL = TYPE_GRAYA_FLT_PREMUL;
const cmsUInt32Number liblcms2_TYPE_RGB_FLT = TYPE_RGB_FLT;

const cmsUInt32Number liblcms2_TYPE_RGBA_FLT = TYPE_RGBA_FLT;
const cmsUInt32Number liblcms2_TYPE_RGBA_FLT_PREMUL = TYPE_RGBA_FLT_PREMUL;
const cmsUInt32Number liblcms2_TYPE_ARGB_FLT = TYPE_ARGB_FLT;
const cmsUInt32Number liblcms2_TYPE_ARGB_FLT_PREMUL = TYPE_ARGB_FLT_PREMUL;
const cmsUInt32Number liblcms2_TYPE_BGR_FLT = TYPE_BGR_FLT;
const cmsUInt32Number liblcms2_TYPE_BGRA_FLT = TYPE_BGRA_FLT;
const cmsUInt32Number liblcms2_TYPE_BGRA_FLT_PREMUL = TYPE_BGRA_FLT_PREMUL;
const cmsUInt32Number liblcms2_TYPE_ABGR_FLT = TYPE_ABGR_FLT;
const cmsUInt32Number liblcms2_TYPE_ABGR_FLT_PREMUL = TYPE_ABGR_FLT_PREMUL;

const cmsUInt32Number liblcms2_TYPE_CMYK_FLT = TYPE_CMYK_FLT;

// Floating point formatters.
// NOTE THAT 'BYTES' FIELD IS SET TO ZERO ON DLB because 8 bytes overflows the bitfield
const cmsUInt32Number liblcms2_TYPE_XYZ_DBL = TYPE_XYZ_DBL;
const cmsUInt32Number liblcms2_TYPE_Lab_DBL = TYPE_Lab_DBL;
const cmsUInt32Number liblcms2_TYPE_GRAY_DBL = TYPE_GRAY_DBL;
const cmsUInt32Number liblcms2_TYPE_RGB_DBL = TYPE_RGB_DBL;
const cmsUInt32Number liblcms2_TYPE_BGR_DBL = TYPE_BGR_DBL;
const cmsUInt32Number liblcms2_TYPE_CMYK_DBL = TYPE_CMYK_DBL;
const cmsUInt32Number liblcms2_TYPE_OKLAB_DBL = TYPE_OKLAB_DBL;

// IEEE 754-2008 "half"
const cmsUInt32Number liblcms2_TYPE_GRAY_HALF_FLT = TYPE_GRAY_HALF_FLT;
const cmsUInt32Number liblcms2_TYPE_RGB_HALF_FLT = TYPE_RGB_HALF_FLT;
const cmsUInt32Number liblcms2_TYPE_CMYK_HALF_FLT = TYPE_CMYK_HALF_FLT;

const cmsUInt32Number liblcms2_TYPE_RGBA_HALF_FLT = TYPE_RGBA_HALF_FLT;
const cmsUInt32Number liblcms2_TYPE_ARGB_HALF_FLT = TYPE_ARGB_HALF_FLT;
const cmsUInt32Number liblcms2_TYPE_BGR_HALF_FLT = TYPE_BGR_HALF_FLT;
const cmsUInt32Number liblcms2_TYPE_BGRA_HALF_FLT = TYPE_BGRA_HALF_FLT;
const cmsUInt32Number liblcms2_TYPE_ABGR_HALF_FLT = TYPE_ABGR_HALF_FLT;
