//
//  sillylog.c
//  sillylog
//
//  Created by Eddie Hillenbrand on 10/3/22.
//  Copyright © 2022 Silly Utility LLC. All rights reserved.
//

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "config.h"

#if USE_FPRINTF
#elif USE_SYSLOG
#include <syslog.h>
#elif USE_OS_LOG
#include <os/log.h>
#else
#error "No primitive log or print procedure selected"
#endif

enum {
    sly_level_log = 0,
    sly_level_call,
    sly_level_trace,
    sly_level_info,
    sly_level_warn,
    sly_level_error,
    sly_level_fatal
};

char * const sly_level_str[] = {
    "", /* no tag for generic log */
    "[CALL] ",
    "[TRACE] ",
    "[INFO] ",
    "[WARN] ",
    "[ERROR] ",
    "[FATAL] ",
};

#if USE_SYSLOG
int sly_syslog_level[] = {
    LOG_INFO,                   /* generic */
    LOG_DEBUG,                  /* call */
    LOG_DEBUG,                  /* trace */
    LOG_INFO,                   /* info */
    LOG_WARNING,                /* warn */
    LOG_ERR,                    /* error */
    LOG_CRIT,                   /* fatal */
};
#endif

char sly_log_prefix[] = "SLY ";

void _sly_logv(int lvl, const char *fmt, va_list args)
{
    char *formatted = NULL;
    vasprintf(&formatted, fmt, args);

#if USE_FPRINTF
    fprintf(stderr, "%s%s%s", sly_log_prefix, sly_level_str[lvl], formatted);
#elif USE_SYSLOG
    syslog(sly_syslog_level[lvl], "%s%s%s", sly_log_prefix, sly_level_str[lvl], formatted);
#elif USE_OS_LOG
    switch (lvl) {
    sly_level_log:
        os_log(OS_LOG_DEFAULT, "%s%s%s", sly_log_prefix, sly_level_str[lvl], formatted);
        break;
    sly_level_call:
        os_log_debug(OS_LOG_DEFAULT, "%s%s%s", sly_log_prefix, sly_level_str[lvl], formatted);
        break;
    sly_level_trace:
        os_log_debug(OS_LOG_DEFAULT, "%s%s%s", sly_log_prefix, sly_level_str[lvl], formatted);
        break;
    sly_level_info:
        os_log_info(OS_LOG_DEFAULT, "%s%s%s", sly_log_prefix, sly_level_str[lvl], formatted);
        break;
    sly_level_warn:
        os_log_info(OS_LOG_DEFAULT, "%s%s%s", sly_log_prefix, sly_level_str[lvl], formatted);
        break;
    sly_level_error:
        os_log_error(OS_LOG_DEFAULT, "%s%s%s", sly_log_prefix, sly_level_str[lvl], formatted);
        break;
    sly_level_fatal:
        os_log_fatal(OS_LOG_DEFAULT, "%s%s%s", sly_log_prefix, sly_level_str[lvl], formatted);
        break;
    default:
        os_log(OS_LOG_DEFAULT, "%s%s%s", sly_log_prefix, sly_level_str[lvl], formatted);
    }

#endif

    if (formatted)
        free(formatted);
}

void _sly_log(int lvl, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    _sly_logv(lvl, fmt, args);
    va_end(args);
}

void sly_log(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    _sly_logv(sly_level_log, fmt, args);
    va_end(args);
}

void sly_fatal(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    _sly_logv(sly_level_fatal, fmt, args);
    va_end(args);
}

void sly_error(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    _sly_logv(sly_level_error, fmt, args);
    va_end(args);
}

void sly_warn(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    _sly_logv(sly_level_warn, fmt, args);
    va_end(args);
}

void sly_info(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    _sly_logv(sly_level_info, fmt, args);
    va_end(args);
}

void sly_trace(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    _sly_logv(sly_level_trace, fmt, args);
    va_end(args);
}

void _sly_trace_call(
    const char *filename,
    const char *func,
    const int line,
    int argc,
    ...)
{
    va_list args;
    char *format, *formatted = NULL;
    if (argc > 0) {
        va_start(args, argc);
        // consume first arg, must be a format string
        format = va_arg(args, char *);
        vasprintf(&formatted, format, args);
        va_end(args);
    }

    if (formatted)
        _sly_log(sly_level_call, "%s %s %d %s", filename, func, line, formatted);
    else
        _sly_log(sly_level_call, "%s %s %d", filename, func, line);

    if (argc > 0 && formatted)
        free(formatted);
}
