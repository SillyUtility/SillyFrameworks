//
//  SLYLog.m
//  SillyLog
//
//  Created by Eddie Hillenbrand on 10/15/20.
//  Copyright © 2020 Silly Utility LLC. All rights reserved.
//

#import "SLYLog.h"

@implementation SLYLog

@end

//void _SLYLog(NSString *level, NSString *format, va_list args) NS_FORMAT_FUNCTION(1,0);

void _SLYLog(NSString *level, NSString *format, va_list args)
{
    NSLog(@"[%@] %@", level,
        [[NSString alloc] initWithFormat:format arguments:args]);
}

void SLYFatal(NSString *format, ...)
{
    va_list args;
    va_start(args, format);
    _SLYLog(@"fatal", format, args);
    va_end(args);
}

void SLYError(NSString *format, ...)
{
    va_list args;
    va_start(args, format);
    _SLYLog(@"error", format, args);
    va_end(args);
}

void SLYWarn(NSString *format, ...)
{
    va_list args;
    va_start(args, format);
    _SLYLog(@"warn", format, args);
    va_end(args);
}

void SLYInfo(NSString *format, ...)
{
    va_list args;
    va_start(args, format);
    _SLYLog(@"info", format, args);
    va_end(args);
}

void SLYTrace(NSString *format, ...)
{
    va_list args;
    va_start(args, format);
    _SLYLog(@"trace", format, args);
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
        SLYTrace(@"%s %s %d %@", filename, func, line, formatted);
    else
        SLYTrace(@"%s %s %d", filename, func, line);
}
