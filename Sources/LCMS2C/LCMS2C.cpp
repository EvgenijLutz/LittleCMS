//
//  LCMS2C.cpp
//  LCMS2
//
//  Created by Evgenij Lutz on 22.08.25.
//

#include <LCMS2C.hpp>
#include <lcms2.h>
#include <algorithm>


ImageContainer::ImageContainer(char* nonnull data, long width, long height, long numComponents, long componentSize, bool isHDR, char* nullable iccpData, long iccpLength):
_referenceCounter(1),
_data(data),
_width(width),
_height(height),
_numComponents(numComponents),
_componentSize(componentSize),
_isHDR(isHDR),
_iccpData(iccpData),
_iccpLength(iccpLength) {
    //
}

ImageContainer::~ImageContainer() {
    printf("Destroy ImageContainer\n");
    delete [] _data;
    delete [] _iccpData;
}


ImageContainer* nullable ImageContainer::create(const char* nonnull data, long width, long height, long numComponents, long componentSize, bool isHDR, char* nullable iccpData, long iccpLength) {
    auto dataSize = width * height * numComponents * componentSize;
    auto dataCopy = new char[dataSize];
    memcpy(dataCopy, data, dataSize);
    
    char* iccpDataCopy = nullptr;
    if (iccpData) {
        iccpDataCopy = new char[iccpLength];
        memcpy(iccpDataCopy, iccpData, iccpLength);
    }
    
    return new ImageContainer(dataCopy, width, height, numComponents, componentSize, isHDR, iccpDataCopy, iccpLength);
}


ImageContainer* nullable ImageContainerRetain(ImageContainer* nullable container) {
    if (container) {
        container->_referenceCounter.fetch_add(1);
    }
    return container;
}


void ImageContainerRelease(ImageContainer* nullable container) {
    if (container && container->_referenceCounter.fetch_sub(1) == 1) {
        delete container;
    }
}


ImageContainer* nullable convertToLinearDCIP3(const char* nonnull sourceData,
                                              long width, long height,
                                              long numComponents, long componentSize,
                                              bool isHDR,
                                              const char* nullable iccData, long iccLength
                                              ) {
    if (width < 1) {
        printf("Invalid width: %ld\n", width);
        return nullptr;
    }
    
    if (height < 1) {
        printf("Invalid height: %ld\n", height);
        return nullptr;
    }
    
    if (numComponents < 1 || numComponents > 4) {
        printf("Invalid number of components: %ld\n", numComponents);
        return nullptr;
    }
    
    if (componentSize != 1 && componentSize != 2 && componentSize != 4) {
        printf("Invalid component size: %ld\n", componentSize);
        return nullptr;
    }
    
    cmsSetLogErrorHandler([](struct _cmsContext_struct *, unsigned int, const char * message) {
        if (message) {
            printf("Error: %s\n", message);
        }
        else {
            printf("Unknown error\n");
        }
    });
    
    // Create source profile from the source image if presented
    cmsHPROFILE srcProfile = nullptr;
    // Import profile from the png iCCP chunk if presented
    if (iccData != nullptr) {
        srcProfile = cmsOpenProfileFromMem(iccData, static_cast<cmsUInt32Number>(iccLength));
    }
    // Or assume that it's sRGB
    if (srcProfile == nullptr) {
        srcProfile = cmsCreate_sRGBProfile();
    }
    
    
    // Create linear DCI-P3 profile
#if 1
    // D65 white point
    cmsCIExyY D65;
    cmsWhitePointFromTemp(&D65, 6504);
    
    // ChatGPT
#if 0
    cmsCIExyYTRIPLE primaries = {
        { 0.680, 0.32, 1.0 },  // Red
        { 0.265, 0.69, 1.0 },  // Green
        { 0.150, 0.06, 1.0 }   // Blue
    };
#else
    cmsCIExyYTRIPLE primaries = {
        { 0.680, 0.32, 0.0   },  // Red
        { 0.265, 0.69, 0.045 },  // Green
        { 0.150, 0.06, 0.79  }   // Blue
    };
#endif
    
    // Linear transfer function
    cmsToneCurve* linear = cmsBuildGamma(nullptr, 1.0);
    cmsToneCurve* transferFunction[3] = { linear, linear, linear };
    
    cmsHPROFILE dstProfile = cmsCreateRGBProfile(&D65, &primaries, transferFunction);
    //cmsHPROFILE dstProfile = cmsCreate_sRGBProfile();
#else
    cmsToneCurve* linear = cmsBuildGamma(nullptr, 1.0);
    
    // DCI-P3-D65.icc profile at
    // https://www.color.org/chardata/rgb/DCIP3.xalter
    unsigned char dciP3D65[] = { 0x00, 0x00, 0x02, 0x5C, 0x00, 0x00, 0x00, 0x00, 0x04, 0x30, 0x00, 0x00, 0x6D, 0x6E, 0x74, 0x72, 0x52, 0x47, 0x42, 0x20, 0x58, 0x59, 0x5A, 0x20, 0x07, 0xE1, 0x00, 0x06, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x63, 0x73, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0xF6, 0xD6, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xD3, 0x2D, 0x43, 0x49, 0x47, 0x4C, 0x87, 0x78, 0x27, 0x40, 0xF3, 0xE3, 0xD1, 0x78, 0x46, 0x4D, 0x70, 0x67, 0xE9, 0xA2, 0x71, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x63, 0x70, 0x72, 0x74, 0x00, 0x00, 0x01, 0x08, 0x00, 0x00, 0x00, 0x64, 0x64, 0x65, 0x73, 0x63, 0x00, 0x00, 0x01, 0x6C, 0x00, 0x00, 0x00, 0x30, 0x77, 0x74, 0x70, 0x74, 0x00, 0x00, 0x01, 0x9C, 0x00, 0x00, 0x00, 0x14, 0x63, 0x68, 0x61, 0x64, 0x00, 0x00, 0x01, 0xB0, 0x00, 0x00, 0x00, 0x2C, 0x72, 0x54, 0x52, 0x43, 0x00, 0x00, 0x01, 0xDC, 0x00, 0x00, 0x00, 0x10, 0x67, 0x54, 0x52, 0x43, 0x00, 0x00, 0x01, 0xEC, 0x00, 0x00, 0x00, 0x10, 0x62, 0x54, 0x52, 0x43, 0x00, 0x00, 0x01, 0xFC, 0x00, 0x00, 0x00, 0x10, 0x72, 0x58, 0x59, 0x5A, 0x00, 0x00, 0x02, 0x0C, 0x00, 0x00, 0x00, 0x14, 0x67, 0x58, 0x59, 0x5A, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x00, 0x14, 0x62, 0x58, 0x59, 0x5A, 0x00, 0x00, 0x02, 0x34, 0x00, 0x00, 0x00, 0x14, 0x6C, 0x75, 0x6D, 0x69, 0x00, 0x00, 0x02, 0x48, 0x00, 0x00, 0x00, 0x14, 0x6D, 0x6C, 0x75, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0C, 0x65, 0x6E, 0x55, 0x4B, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x49, 0x00, 0x6E, 0x00, 0x74, 0x00, 0x65, 0x00, 0x72, 0x00, 0x6E, 0x00, 0x61, 0x00, 0x74, 0x00, 0x69, 0x00, 0x6F, 0x00, 0x6E, 0x00, 0x61, 0x00, 0x6C, 0x00, 0x20, 0x00, 0x43, 0x00, 0x6F, 0x00, 0x6C, 0x00, 0x6F, 0x00, 0x72, 0x00, 0x20, 0x00, 0x43, 0x00, 0x6F, 0x00, 0x6E, 0x00, 0x73, 0x00, 0x6F, 0x00, 0x72, 0x00, 0x74, 0x00, 0x69, 0x00, 0x75, 0x00, 0x6D, 0x00, 0x2C, 0x00, 0x20, 0x00, 0x32, 0x00, 0x30, 0x00, 0x31, 0x00, 0x37, 0x6D, 0x6C, 0x75, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0C, 0x65, 0x6E, 0x55, 0x4B, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x44, 0x00, 0x43, 0x00, 0x49, 0x00, 0x20, 0x00, 0x50, 0x00, 0x33, 0x00, 0x20, 0x00, 0x44, 0x00, 0x36, 0x00, 0x35, 0x58, 0x59, 0x5A, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF6, 0xD5, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xD3, 0x2D, 0x73, 0x66, 0x33, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0C, 0x44, 0x00, 0x00, 0x05, 0xDF, 0xFF, 0xFF, 0xF3, 0x26, 0x00, 0x00, 0x07, 0x94, 0x00, 0x00, 0xFD, 0x8F, 0xFF, 0xFF, 0xFB, 0xA1, 0xFF, 0xFF, 0xFD, 0xA2, 0x00, 0x00, 0x03, 0xDB, 0x00, 0x00, 0xC0, 0x75, 0x63, 0x75, 0x72, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x9A, 0x00, 0x00, 0x63, 0x75, 0x72, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x9A, 0x00, 0x00, 0x63, 0x75, 0x72, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x9A, 0x00, 0x00, 0x58, 0x59, 0x5A, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0xDF, 0x00, 0x00, 0x3D, 0xBF, 0xFF, 0xFF, 0xFF, 0xBB, 0x58, 0x59, 0x5A, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4A, 0xBF, 0x00, 0x00, 0xB1, 0x37, 0x00, 0x00, 0x0A, 0xB9, 0x58, 0x59, 0x5A, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x38, 0x00, 0x00, 0x11, 0x0B, 0x00, 0x00, 0xC8, 0xB9, 0x58, 0x59, 0x5A, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    cmsHPROFILE dstProfile = cmsOpenProfileFromMem(dciP3D65, static_cast<cmsUInt32Number>(sizeof(dciP3D65)));
    if (dstProfile == nullptr) {
        dstProfile = cmsCreate_sRGBProfile();
    }
#endif
    
    
    // Determine output component size
    auto outputComponentSize = componentSize;
#if 0
    switch (componentSize) {
        case 1:
        case 2:
            outputComponentSize = 2;
            break;
            
        case 4:
            outputComponentSize = 4;
            break;
            
        default:
            break;
    }
    //outputComponentSize = 1;
    if (outputComponentSize == 0) {
        return nullptr;
    }
#endif
    
    
    // Determine input and output pixel formats
    cmsUInt32Number inputFormat = 0;
    cmsUInt32Number outputFormat = 0;
    struct ComponentConverter {
        static cmsUInt32Number C1(long componentSize) {
            switch (componentSize) {
                case 1: return TYPE_GRAY_8;
                case 2: return TYPE_GRAY_16_SE;
                case 4: return TYPE_GRAY_FLT;
                default: return 0;
            }
        }
        
        static cmsUInt32Number C2(long componentSize) {
            switch (componentSize) {
                case 1: return TYPE_GRAYA_8;
                case 2: return TYPE_GRAYA_16_SE;
                case 4: return TYPE_GRAYA_FLT;
                default: return 0;
            }
        }
        
        static cmsUInt32Number C3(long componentSize) {
            switch (componentSize) {
                case 1: return TYPE_RGB_8;
                case 2: return TYPE_RGB_16_SE;
                case 4: return TYPE_RGB_FLT;
                default: return 0;
            }
        }
        
        static cmsUInt32Number C4(long componentSize) {
            switch (componentSize) {
                case 1: return TYPE_RGBA_8;
                case 2: return TYPE_RGBA_16_SE;
                case 4: return TYPE_RGBA_FLT;
                default: return 0;
            }
        }
    };
    switch (numComponents) {
        case 1:
            inputFormat = ComponentConverter::C1(componentSize);
            outputFormat = ComponentConverter::C1(outputComponentSize);
            break;
            
        case 2:
            inputFormat = ComponentConverter::C2(componentSize);
            outputFormat = ComponentConverter::C2(outputComponentSize);
            break;
            
        case 3:
            inputFormat = ComponentConverter::C3(componentSize);
            outputFormat = ComponentConverter::C3(outputComponentSize);
            break;
            
        case 4:
            inputFormat = ComponentConverter::C4(componentSize);
            outputFormat = ComponentConverter::C4(outputComponentSize);
            break;
            
        default:
            break;
    }
    
    
    // Create transform from source to the destination profile
    cmsHTRANSFORM transform = cmsCreateTransform(srcProfile, inputFormat,
                                                 dstProfile, outputFormat,
                                                 //srcProfile, inputFormat,
                                                 INTENT_ABSOLUTE_COLORIMETRIC,
                                                 0 |
                                                 cmsFLAGS_HIGHRESPRECALC |
                                                 cmsFLAGS_GAMUTCHECK |
                                                 cmsFLAGS_NOOPTIMIZE |
                                                 cmsFLAGS_NONEGATIVES |
                                                 cmsFLAGS_COPY_ALPHA
                                                 );
    
    
    // Apply transformation
    char* linearP3 = new char[width * height * numComponents * outputComponentSize];
    for (int y = 0; y < height; y++) {
        cmsDoTransform(transform, sourceData + width * componentSize * numComponents * y,
                       linearP3 + width * outputComponentSize * numComponents * y,
                       static_cast<cmsUInt32Number>(width));
    }
    
    
    cmsUInt32Number iccProfileSize = 0;
    char* iccProfileData = nullptr;
    if (cmsSaveProfileToMem(dstProfile, nullptr, &iccProfileSize)) {
        iccProfileData = new char[iccProfileSize];
        
        cmsSaveProfileToMem(dstProfile, iccProfileData, &iccProfileSize);
    }
    
    
    // Cleanup
    cmsDeleteTransform(transform);
    cmsCloseProfile(srcProfile);
    cmsCloseProfile(dstProfile);
    cmsFreeToneCurve(linear);
    
    auto image = ImageContainer::create(linearP3, width, height, numComponents, outputComponentSize, isHDR, iccProfileData, iccProfileSize);
    
    delete [] iccProfileData;
    delete [] linearP3;
    
#if 0
    // Compare data
    auto oldDataSize = width * height * numComponents * componentSize;
    auto newDataSize = width * height * numComponents * outputComponentSize;
    
    auto count = std::min(oldDataSize / 2, newDataSize / 2);
    auto buf1 = reinterpret_cast<const unsigned short*>(sourceData);
    auto buf2 = reinterpret_cast<const unsigned short*>(linearP3);
    for (auto i = 0; i < count; i++) {
        auto val1 = buf1[i];
        auto val2 = buf2[i];
        
        if (val1 != val2) {
            printf("First difference at %d: %d~%d\n", i, val1, val2);
            break;
        }
    }
#endif
    
    return image;
}
