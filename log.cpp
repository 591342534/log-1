
#include "log.h"

#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#endif

namespace wz
{

unsigned char log::level = LOG_LEVEL;

char log::file_path[LOG_FILE_PATH_SIZE] = {'\0'};
unsigned short log::current_file_index = 0;

char log::pre_buffer[LOG_PRE_SIZE] = {'\0'};
 
char log::buffer[LOG_CONTENT_SIZE] = {'\0'};

int log::year = 0;
int log::month = 0;
int log::day = 0;

time_t log::time_stamp;
tm *log::current_time;

void log::info(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    log_gen(format, ap, log::LEVEL::INFO);
    va_end(ap);
}

void log::debug(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    log_gen(format, ap, log::LEVEL::DEBUG);
    va_end(ap);
}

void log::warn(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    log_gen(format, ap, log::LEVEL::WARN);
    va_end(ap);
}

void log::error(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    log_gen(format, ap, log::LEVEL::ERROR);
    va_end(ap);
}

void log::fatal(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    log_gen(format, ap, log::LEVEL::FATAL);
    va_end(ap);
}

void log::log_gen(const char *format,
                  va_list &ap,
                  const unsigned char &level)
{
    memset(file_path, 0, LOG_FILE_PATH_SIZE);
    memset(pre_buffer, 0, LOG_PRE_SIZE);
    memset(buffer, 0, LOG_CONTENT_SIZE);

    /* pre: [level] [ss:ms] */
    const char *current_level = NULL;
    switch (level)
    {
    case LEVEL::INFO:
        current_level = "INFO";
        break;
    case LEVEL::DEBUG:
        current_level = "DEBUG";
        break;
    case LEVEL::WARN:
        current_level = "WARN";
        break;
    case LEVEL::ERROR:
        current_level = "ERROR";
        break;
    case LEVEL::FATAL:
        current_level = "FATAL";
        break;
    default:
        break;
    }
    time_stamp = time(NULL);
    current_time = localtime(&time_stamp);
    snprintf(pre_buffer,
             LOG_PRE_SIZE,
             "[%s] [%d-%02d-%02d %02d:%02d:%02d] ",
             current_level,
             current_time->tm_year + 1900,
             current_time->tm_mon + 1,
             current_time->tm_mday,
             current_time->tm_hour,
             current_time->tm_min,
             current_time->tm_sec);
    /* content */
    vsnprintf(buffer, LOG_CONTENT_SIZE, format, ap);

    /* pre + content print */
    printf("%s", pre_buffer);
    printf("%s\n", buffer);

    /* persistence to file */
#ifdef _WIN32
    mkdir(LOG_DIR);
#else
    mkdir(LOG_DIR, 0777);
#endif

    if (log::level <= level)
    {
        FILE *fp = NULL;

        if (year != current_time->tm_year + 1900 ||
            month != current_time->tm_mon + 1 ||
            day != current_time->tm_mday)
        {
            year = current_time->tm_year + 1900;
            month = current_time->tm_mon + 1;
            day = current_time->tm_mday;
            current_file_index = 0;
        }

        /* construct log file path */
        snprintf(file_path,
                 LOG_FILE_PATH_SIZE,
                 "%s/%d-%02d-%02d_%d.log",
                 LOG_DIR,
                 current_time->tm_year + 1900,
                 current_time->tm_mon + 1,
                 current_time->tm_mday,
                 current_file_index);
        while (LOG_FILE_MAX_SIZE < file_size(file_path))
        {
            current_file_index++;
            memset(file_path, 0, LOG_FILE_PATH_SIZE);
            snprintf(file_path,
                     LOG_FILE_PATH_SIZE,
                     "%s/%d-%02d-%02d_%d.log",
                     LOG_DIR,
                     current_time->tm_year + 1900,
                     current_time->tm_mon + 1,
                     current_time->tm_mday,
                     current_file_index);
        }

        /* append mode for file && will create if not exist. */
        fp = fopen(file_path, "a+");
        /* append content */
        if (fp != NULL)
        {

            fputs(pre_buffer, fp);
            fputs(buffer, fp);
            fputs("\r\n", fp);

            /* close file */
            fclose(fp);
        }
        else
        {
            printf("log: open or create log file failed.\n");
        }
    }
}

long log::file_size(const char *filename)
{
    long size = -1;
    FILE *fp = fopen(filename, "r");
    if (fp)
    {
        fseek(fp, 0L, SEEK_END);
        size = ftell(fp);
        fclose(fp);
    }
    return size;
}

} // namespace BZL