//
//  SLYLog.h
//  SillyLog
//
//  Created by Eddie Hillenbrand on 10/15/20.
//  Copyright © 2020 Silly Utility LLC. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SLYLogItem : NSObject
@end

@interface SLYLogManager : NSObject
@end

void SLYLog(NSString *format, ...) NS_FORMAT_FUNCTION(1,2) NS_NO_TAIL_CALL;
void SLYFatal(NSString *format, ...) NS_FORMAT_FUNCTION(1,2) NS_NO_TAIL_CALL;
void SLYError(NSString *format, ...) NS_FORMAT_FUNCTION(1,2) NS_NO_TAIL_CALL;
void SLYWarn(NSString *format, ...) NS_FORMAT_FUNCTION(1,2) NS_NO_TAIL_CALL;
void SLYInfo(NSString *format, ...) NS_FORMAT_FUNCTION(1,2) NS_NO_TAIL_CALL;
void SLYTrace(NSString *format, ...) NS_FORMAT_FUNCTION(1,2) NS_NO_TAIL_CALL;

#define VA_ARG_COUNT(...) _VA_ARG_COUNT(, ##__VA_ARGS__, 127, 126,  \
    125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114,     \
    113, 112,111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, \
    100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86,    \
    85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, \
    69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, \
    53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, \
    37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, \
    21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5,  \
    4, 3, 2, 1, 0)

#define _VA_ARG_COUNT(arg0, arg1, arg2, arg3, arg4, arg5, arg6,     \
    arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15,     \
    arg16, arg17, arg18, arg19, arg20, arg21, arg22, arg23, arg24,  \
    arg25, arg26, arg27, arg28, arg29, arg30, arg31, arg32, arg33,  \
    arg34, arg35, arg36, arg37, arg38, arg39, arg40, arg41, arg42,  \
    arg43, arg44, arg45, arg46, arg47, arg48, arg49, arg50, arg51,  \
    arg52, arg53, arg54, arg55, arg56, arg57, arg58, arg59, arg60,  \
    arg61, arg62, arg63, arg64, arg65, arg66, arg67, arg68, arg69,  \
    arg70, arg71, arg72, arg73, arg74, arg75, arg76, arg77, arg78,  \
    arg79, arg80, arg81, arg82, arg83, arg84, arg85, arg86, arg87,  \
    arg88, arg89, arg90, arg91, arg92, arg93, arg94, arg95, arg96,  \
    arg97, arg98, arg99, arg100, arg101, arg102, arg103, arg104,    \
    arg105, arg106, arg107, arg108, arg109, arg110, arg111, arg112, \
    arg113, arg114, arg115, arg116, arg117, arg118, arg119, arg120, \
    arg121, arg122, arg123, arg124, arg125, arg126, arg127,         \
    argN, ...) argN

#define SLYTraceCall(...) _SLYTraceCall(__FILE_NAME__, __func__, \
    __LINE__, VA_ARG_COUNT(__VA_ARGS__), ##__VA_ARGS__)

void _SLYTraceCall(
    const char *filename,
    const char *func,
    const int line,
    int argc,
    ...
);

NS_ASSUME_NONNULL_END
