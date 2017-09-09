#include <iostream>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <memory>
#include "logger.hpp"

using namespace std;
using namespace g2::fasth;

logger::logger(g2::fasth::log_level logLevel)
    :d_loglevel(logLevel)
{
}

void logger::add_output_stream(std::ostream &output_stream, log_level level)
{
    add_output_stream(&output_stream, level);
}

void logger::add_output_stream(std::ostream *output_stream, log_level level)
{
    stream_info stream_info(output_stream, level);
    tthread::lock_guard<tthread::mutex> lg(d_mutex);
    d_outputStreams.push_back(stream_info);
}

void logger::internal_log(log_level log_level, std::string text)
{
    // If the log level passed is greater then permissible log level of suite, quit.
    if (log_level > d_loglevel)
    {
        return;
    }

    for (auto iter = d_outputStreams.begin(); iter < d_outputStreams.end(); ++iter)
    {
        // If log level of iterator is greater then permissible log level of suite, quit.
        if (iter->level > d_loglevel)
        {
            continue;
        }
        // If log level passed is greater then permissible log level of iterator, quit.
        else if (log_level > iter->level)
        {
            continue;
        }
        auto ptr_stream = iter->pStream;
        auto written = write(text.c_str(), false, ptr_stream);
        if (written)
        {
            (*ptr_stream) << endl;
            ptr_stream->flush();
        }
    }
}

void logger::log(log_level log_level, std::string text)
{
    tthread::lock_guard<tthread::mutex> lg(d_mutex);
    internal_log(log_level, text);
}

bool logger::write(const char* data, bool written, std::ostream* stream)
{
    if (written == true)
    {
        (*stream) << " ";
    }
    (*stream) << data;
    return true;
}

void logger::log_formatted(log_level log_level, const std::string fmt_str, ...)
{
    tthread::lock_guard<tthread::mutex> lg(d_mutex);
    // If the log level passed is greater then permissible log level of suite, quit.
    if (log_level > d_loglevel)
    {
        return;
    }

    int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while(true)
    {
        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
        strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }

    internal_log(log_level, std::string(formatted.get()));
}