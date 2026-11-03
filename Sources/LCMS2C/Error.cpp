//
//  Error.cpp
//  LCMS2
//
//  Created by Evgenij Lutz on 11.11.25.
//

#define _LIBCPP_REMOVE_TRANSITIVE_INCLUDES
#include <LCMS2C/Error.hpp>
#include <stdarg.h>
#include <print>


const char* fn_nonnull lcmsErrorCodeDescription(LCMSErrorCode code) {
    const char* messages[] = {
        "Unknown error",
        "Not implemented"
    };
    
    return messages[static_cast<long>(code)];
}


LCMSError::LCMSError() {
    code = LCMSErrorCode::unknown;
    message[0] = 0;
}


void lcmsSetError(LCMSError* fn_nullable error fn_noescape, LCMSErrorCode code) {
    if (error == nullptr) {
        return;
    }
    
    error->code = code;
    error->message[0] = 0;
}


void lcmsSetError(LCMSError* fn_nullable error fn_noescape, LCMSErrorCode code, const char* fn_nonnull __restrict format, ...) {
    if (error == nullptr) {
        return;
    }
    
    error->code = code;
    
    // Build a message string
    va_list args;
    va_start(args, format);
    vsnprintf(error->message, LCMS_ERROR_LENGTH - 1, format, args);
    va_end(args);
}
