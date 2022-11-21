//
//  SLYLog.m
//  SillyLog
//
//  Created by Eddie Hillenbrand on 10/15/20.
//  Copyright © 2020 Silly Utility LLC. All rights reserved.
//

#import "SLYLog.h"
#import "Config.h"

@implementation SLYLogItem
@end

@implementation SLYLogManager
@end

#if USE_FPRINTF
#elif USE_SYSLOG
#include <syslog.h>
#elif USE_OS_LOG
#include <os/log.h>
#elif USE_NSLOG
#import <Foundation/Foundation.h>
#else
#error "No primitive log or print procedure selected"
#endif

enum {
    SLYLevelLog = 0,
    SLYLevelCall,
    SLYLevelTrace,
    SLYLevelInfo,
    SLYLevelWarn,
    SLYLevelError,
    SLYLevelFatal,
};

char * const SLYLevelStr[] = {
    "", /* no tag for generic log */
    "[CALL] ",
    "[TRACE] ",
    "[INFO] ",
    "[WARN] ",
    "[ERROR] ",
    "[FATAL] ",
};

#if USE_SYSLOG
int SLYSysLogLevel[] = {
    LOG_INFO,                   /* generic */
    LOG_DEBUG,                  /* call */
    LOG_DEBUG,                  /* trace */
    LOG_INFO,                   /* info */
    LOG_WARNING,                /* warn */
    LOG_ERR,                    /* error */
    LOG_CRIT,                   /* fatal */
};
#endif

char SLYLogPrefix[] = "SLY ";

void _SLYLogv(int lvl, NSString *fmt, va_list args)
{
    const char *fmtCStr = NULL;
    NSString *formatted;
    formatted = [[NSString alloc] initWithFormat:fmt arguments:args];
    fmtCStr = formatted.UTF8String;

#if USE_FPRINTF
    fprintf(stderr, "%s%s%s", SLYLogPrefix, SLYLevelStr[lvl], fmtCStr);
#elif USE_SYSLOG
    syslog(SLYSysLogLevel[lvl], "%s%s%s", SLYLogPrefix, SLYLevelStr[lvl], fmtCStr);
#elif USE_OS_LOG
    switch (lvl) {
    SLYLevelLog:
        os_log(OS_LOG_DEFAULT, "%s%s%s", SLYLogPrefix, SLYLevelStr[lvl], fmtCStr);
        break;
    SLYLevelCall:
        os_log_debug(OS_LOG_DEFAULT, "%s%s%s", SLYLogPrefix, SLYLevelStr[lvl], fmtCStr);
        break;
    SLYLevelTrace:
        os_log_debug(OS_LOG_DEFAULT, "%s%s%s", SLYLogPrefix, SLYLevelStr[lvl], fmtCStr);
        break;
    SLYLevelInfo:
        os_log_info(OS_LOG_DEFAULT, "%s%s%s", SLYLogPrefix, SLYLevelStr[lvl], fmtCStr);
        break;
    SLYLevelWarn:
        os_log_info(OS_LOG_DEFAULT, "%s%s%s", SLYLogPrefix, SLYLevelStr[lvl], fmtCStr);
        break;
    SLYLevelError:
        os_log_error(OS_LOG_DEFAULT, "%s%s%s", SLYLogPrefix, SLYLevelStr[lvl], fmtCStr);
        break;
    SLYLevelFatal:
        os_log_fatal(OS_LOG_DEFAULT, "%s%s%s", SLYLogPrefix, SLYLevelStr[lvl], fmtCStr);
        break;
    default:
        os_log(OS_LOG_DEFAULT, "%s%s%s", SLYLogPrefix, SLYLevelStr[lvl], fmtCStr);
    }
#elif USE_NSLOG
    NSLog(@"%s%s%s", SLYLogPrefix, SLYLevelStr[lvl], fmtCStr);
#endif
}

void _SLYLog(int lvl, NSString *format, ...)
{
    va_list args;
    va_start(args, format);
    _SLYLogv(lvl, format, args);
    va_end(args);
}

void SLYLog(NSString *format, ...)
{
    va_list args;
    va_start(args, format);
    _SLYLogv(SLYLevelLog, format, args);
    va_end(args);
}

void SLYFatal(NSString *format, ...)
{
    va_list args;
    va_start(args, format);
    _SLYLogv(SLYLevelLog, format, args);
    va_end(args);
}

void SLYError(NSString *format, ...)
{
    va_list args;
    va_start(args, format);
    _SLYLogv(SLYLevelLog, format, args);
    va_end(args);
}

void SLYWarn(NSString *format, ...)
{
    va_list args;
    va_start(args, format);
    _SLYLogv(SLYLevelLog, format, args);
    va_end(args);
}

void SLYInfo(NSString *format, ...)
{
    va_list args;
    va_start(args, format);
    _SLYLogv(SLYLevelLog, format, args);
    va_end(args);
}

void SLYTrace(NSString *format, ...)
{
    va_list args;
    va_start(args, format);
    _SLYLogv(SLYLevelLog, format, args);
    va_end(args);
}

void _SLYTraceCall(
    const char *filename,
    const char *func,
    const int line,
    int argc,
    ...)
{
    va_list args;
    NSString *format, *formatted;
    if (argc > 0) {
        va_start(args, argc);
        // consume first arg, must be a format string
        format = va_arg(args, NSString *);
        formatted = [[NSString alloc] initWithFormat:format arguments:args];
        va_end(args);
    }

    if (formatted)
        _SLYLog(SLYLevelCall, @"%s %s %d %@", filename, func, line, formatted);
    else
        _SLYLog(SLYLevelCall, @"%s %s %d", filename, func, line);
}
