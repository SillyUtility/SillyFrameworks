//
//  SLYError.h
//  SillyLog
//
//  Created by Eddie Hillenbrand on 10/15/20.
//  Copyright © 2020 Silly Utility LLC. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSErrorDomain const SLYErrorDomain;

/*!
    @const SLYErrorFilenameKey

    @abstract The NSError userInfo dictionary key used to store and
    retrieve the filename.
*/
FOUNDATION_EXPORT NSString * const SLYErrorFilenameKey;

/*!
    @const SLYErrorLineKey

    @abstract The NSError userInfo dictionary key used to store and
    retrieve the line number.
*/
FOUNDATION_EXPORT NSString * const SLYErrorLineKey;

/*!
    @const SLYErrorFuncKey

    @abstract The NSError userInfo dictionary key used to store and
    retrieve the function or method.
*/
FOUNDATION_EXPORT NSString * const SLYErrorFuncKey;

//@interface SLYError : NSError
//
//@end

#define SYLErrorUserInfo() \
    _SYLErrorUserInfo(__FILE_NAME__, __LINE__, __func__)

FOUNDATION_STATIC_INLINE
NSDictionary<NSString *, NSString *> *_SYLErrorUserInfo
    (const char *fn, const int ln, const char *f)
{
    return @{
        SLYErrorFilenameKey: [NSString stringWithFormat:@"%s", fn],
        SLYErrorLineKey: [NSString stringWithFormat:@"%d", ln],
        SLYErrorFuncKey: [NSString stringWithFormat:@"%s", f],
    };
}

NS_ASSUME_NONNULL_END
