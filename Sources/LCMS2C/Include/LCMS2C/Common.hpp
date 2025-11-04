//
//  Common.hpp
//  LCMS2
//
//  Created by Evgenij Lutz on 03.11.25.
//

#pragma once

#include <atomic>
#include <swift/bridging>


#if !defined fn_nullable
#define fn_nullable __nullable
#endif

#if !defined fn_nonnull
#define fn_nonnull __nonnull
#endif

#ifndef fn_noescape
#define fn_noescape _LIBCPP_NOESCAPE
#endif


enum class LCMSErrorCode: long {
    unknown = 0,
    notImplemented
};


static inline const char* fn_nonnull lcmsErrorCodeDescription(LCMSErrorCode code) {
    const char* messages[] = {
        "Unknown error",
        "Not implemented"
    };
    
    return messages[static_cast<long>(code)];
}


#define LCMS_ERROR_LENGTH 128

struct LCMSError {
    /// Error code.
    ///
    /// Call ``lcmsErrorCodeDescription`` to see the error description. The `message` property contains additional information.
    LCMSErrorCode code;
    
    /// Additional information.
    char message[LCMS_ERROR_LENGTH];
    
    LCMSError();
};


void lcmsSetError(LCMSError* fn_nullable error fn_noescape, LCMSErrorCode code);
void lcmsSetError(LCMSError* fn_nullable error fn_noescape, LCMSErrorCode code, const char* fn_nonnull __restrict format, ...) __printflike(3, 4);
