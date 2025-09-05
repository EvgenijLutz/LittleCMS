//
//  LCMS2C.hpp
//  LCMS2
//
//  Created by Evgenij Lutz on 22.08.25.
//

#ifndef LCMS2C_hpp
#define LCMS2C_hpp

#if defined __cplusplus

#include <atomic>
#include <swift/bridging>


#if !defined nullable
#define nullable __nullable
#endif

#if !defined nonnull
#define nonnull __nonnull
#endif


class ImageContainer {
private:
    std::atomic<size_t> _referenceCounter;
    
    char* nonnull _data;
    long _width;
    long _height;
    long _numComponents;
    long _componentSize;
    bool _isHDR;
    
    char* nullable _iccpData;
    long _iccpLength;
    
    friend ImageContainer* nullable ImageContainerRetain(ImageContainer* nullable container) SWIFT_RETURNS_UNRETAINED;
    friend void ImageContainerRelease(ImageContainer* nullable container);
    
    ImageContainer(char* nonnull data, long width, long height, long numComponents, long componentSize, bool isHDR, char* nullable iccpData, long iccpLength);
    ~ImageContainer();
    
public:
    static ImageContainer* nullable create(const char* nonnull data, long width, long height, long numComponents, long componentSize, bool isHDR, char* nullable iccpData = nullptr, long iccpLength = 0) SWIFT_RETURNS_RETAINED;
    
    char* nonnull getData() SWIFT_COMPUTED_PROPERTY { return _data; }
    long getDataSize() SWIFT_COMPUTED_PROPERTY { return _width * _height * _numComponents * _componentSize; }
    long getWidth() const SWIFT_COMPUTED_PROPERTY { return _width; }
    long getHeight() const SWIFT_COMPUTED_PROPERTY { return _height; }
    long getNumComponents() const SWIFT_COMPUTED_PROPERTY { return _numComponents; }
    long getComponentSize() const SWIFT_COMPUTED_PROPERTY { return _componentSize; }
    long getIsHDR() const SWIFT_COMPUTED_PROPERTY { return _isHDR; }
    
    const char* nullable getICCData() SWIFT_COMPUTED_PROPERTY { return _iccpData; }
    long getICCDataLength() SWIFT_COMPUTED_PROPERTY { return _iccpLength; }
} SWIFT_SHARED_REFERENCE(ImageContainerRetain, ImageContainerRelease);


ImageContainer* nullable convertToLinearDCIP3(const char* nonnull sourceData,
                                              long width, long height,
                                              long numComponents, long componentSize,
                                              bool isHDR,
                                              const char* nullable iccpData, long iccpLength
                                              ) SWIFT_RETURNS_RETAINED;

#endif // __cplusplus

#endif // LCMS2C_hpp
