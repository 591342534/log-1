
#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

namespace wz
{

/* log level : higher than this level will persistence to log file */
#define LOG_LEVEL log::LEVEL::ERROR
/* log file path size */
#define LOG_FILE_PATH_SIZE (100)
/* log file persistence directory */
#define LOG_DIR "./log"
/* log file max size */
#define LOG_FILE_MAX_SIZE (10485760) /* unit: b , default is 10mb */
/* log pre buffer size */
#define LOG_PRE_SIZE (35)
/* log content buffer size */
#define LOG_CONTENT_SIZE (256)
 
class log
{
public:
    enum LEVEL
    {
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

public:
    static void info(const char *format, ...);
    static void debug(const char *format, ...);
    static void warn(const char *format, ...);
    static void error(const char *format, ...);
    static void fatal(const char *format, ...);

private:
    static void log_gen(const char *format,
                        va_list &ap,
                        const unsigned char &level);

    static long file_size(const char *filename);

private:
    /* higher than this level will persistence to log file */
    static unsigned char level;

    /* log file path */
    static char file_path[LOG_FILE_PATH_SIZE];
    static unsigned short current_file_index;

    /* log pre buffer */
    static char pre_buffer[LOG_PRE_SIZE];

    /* log content buffer */
    static char buffer[LOG_CONTENT_SIZE];

    /* today */
    static int year;
    static int month;
    static int day;

    /* current time */
    static time_t time_stamp;
    static tm *current_time;
};

} // namespace BZL

#endif