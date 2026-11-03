//
//  Error.hpp
//  LCMS2
//
//  Created by Evgenij Lutz on 11.11.25.
//

#pragma once

#include <LCMS2C/Common.hpp>


enum class LCMSErrorCode: long {
    unknown = 0,
    notImplemented
};


const char* fn_nonnull lcmsErrorCodeDescription(LCMSErrorCode code);


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
void lcmsSetError(LCMSError* fn_nullable error fn_noescape, LCMSErrorCode code, const char* fn_nonnull __restrict format, ...) __attribute__((format(printf, 3, 4)));
