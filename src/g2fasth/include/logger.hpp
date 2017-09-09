#pragma once
#ifndef INC_LIBG2FASTH_LOGGER_H
#define INC_LIBG2FASTH_LOGGER_H

#include <iostream>
#include <vector>
#include "tinythread.h"
#include "g2fasth_enums.hpp"

namespace g2 {
namespace fasth {
/**
* This class is responsible for logging to collection of streams.
* The amount of data logged depends on log level set through the constructor.
*/
class logger {
private:
    struct stream_info {
        std::ostream* pStream;
        g2::fasth::log_level level;
        stream_info(std::ostream* pStream, log_level level)
            : pStream(pStream), level(level) {
        }
    };
    void internal_log(log_level, std::string);
public:
    /**
    * Accepts log level of application.
    */
    logger(g2::fasth::log_level);
    /**
    * This method accepts reference output stream instance and log level associated with it.
    */
    void add_output_stream(std::ostream &, log_level);
    /**
    * This method accepts address of output stream instance and log level associated with it.
    */
    void add_output_stream(std::ostream*, log_level);
    /**
    * This method logs data with desired log level.
    */
    void log(log_level, std::string);
    void log_formatted(log_level log_level, const std::string fmt_str, ...);
private:
    tthread::mutex d_mutex;
    log_level d_loglevel;
    std::vector<stream_info> d_outputStreams;
    bool write(const char* data, bool written, std::ostream* stream);
};
}
}

#ifndef FUNCLOG
#ifndef WIN32
#include <sys/time.h>
inline unsigned GetTickCount()
{
        struct timeval tv;
        if(gettimeofday(&tv, NULL) != 0)
                return 0;

        return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
#endif

//#define ENABLE_FUNCLOG

class ScopeLog
{
    std::string name;
    std::string suffix;
public:
    ScopeLog(const std::string& name, const std::string& suffix=""): name(name), suffix(suffix)
    {
        printf("%08u ENTER %s-%s\n", GetTickCount(), this->name.c_str(), this->suffix.c_str());
    }
    ~ScopeLog()
    {
        printf("%08u LEAVE %s-%s\n", GetTickCount(), this->name.c_str(), this->suffix.c_str());
    }
};
#ifdef ENABLE_FUNCLOG
#   define FUNCLOG ScopeLog __func_log__(__FUNCTION__)
#   define FUNCLOG2(suffix) ScopeLog __func_log__(__FUNCTION__,suffix)
#   define SCOPELOG(name) ScopeLog __scope_log__(name)
#else
#   define FUNCLOG
#   define FUNCLOG2(suffix)
#   define SCOPELOG(name)
#endif
#endif


#endif // !INC_LIBG2FASTH_LOGGER_H