#include "sbn.h"

#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdarg.h>

#ifdef __linux__
#include <unistd.h>

int getPID()
{
    pid_t pid = getpid();
    return (int)pid;
}
#endif

#define LOG_LEVEL_PADDING "8"

const char *LogPrefix = "SBNPeer";
const char *LogVersion = "1";
const char *LogExtension = ".log";
const char *LogNameFormat = "%s_%s_v%s%s";
const char *LogHistoryNameFormat = "%s_%s_v%s_%d%s";
const int LogHistoryCount = 1;

char *getLogFileName(sbn_t *SBN, unsigned index)
{
    const char *format;
    char *buf;
    int size;

    if (SBN == NULL) {
        return NULL;
    }

    size = strlen(LogNameFormat) + strlen(LogPrefix) +
	SBN_MAX_PEERNAME_LENGTH + 1
	+ strlen(LogVersion) + strlen(LogExtension);

    if(index) {
        size += floor(log10(abs(index))) + 1; // size of string representation
        format = LogHistoryNameFormat;
        buf = malloc(size);
        snprintf(buf, size, format, LogPrefix, SBN->NodeName, LogVersion, index, LogExtension);
    } else {
        format = LogNameFormat;
        buf = malloc(size);
        snprintf(buf, size, format, LogPrefix, SBN->NodeName, LogVersion, LogExtension);
    }

    return buf;
}

FILE *getLogFile(sbn_t *SBN)
{
    char *fileName;
    time_t now = time(0);
    bool reopenFile = false;
    char *prevFileName;
    char *newFileName;
    int i;

    if (SBN == NULL) {
        return NULL;
    }

    if (!SBN->log.fileHandle) {
        reopenFile = true;
        fileName = getLogFileName(SBN, 0);
        if (fileName == NULL) {
            return NULL;
        }
    } else if (now - SBN->log.startTime >= SBN->log.maxFileDuration * SBN->log.maxFileDurationScale) {
        reopenFile = true;
        fclose(SBN->log.fileHandle);
        fileName = getLogFileName(SBN, 0);
        if (fileName == NULL) {
            return NULL;
        }

        if (!SBN->log.maxFileDuration) {
            //If history is disabled, just remove current log
            remove(fileName);
        } else {
            //Delete oldest file
            prevFileName = getLogFileName(SBN, LogHistoryCount);
            if (fileName == NULL) {
                return NULL;
            }
            remove(prevFileName);
            free(prevFileName);

            //Roll history files
            for(i = LogHistoryCount - 1; i >= 0; --i) {
                prevFileName = getLogFileName(SBN, i);
                newFileName = getLogFileName(SBN, i + 1);
                if ((prevFileName == NULL) || (newFileName == NULL)) {
                    return NULL;
                }
                rename(prevFileName, newFileName);
                free(prevFileName);
                free(newFileName);
            }
        }
    }

    if (!reopenFile) {
        return SBN->log.fileHandle;
    }

    SBN->log.fileHandle = fopen(fileName, "a");
    free(fileName);
    SBN->log.startTime = now;
    return SBN->log.fileHandle;
}

char *getLogLevelName(sbn_log_level level)
{
    switch(level) {
    case SBN_ERROR_LEVEL:
        return "ERROR";
    case SBN_WARNING_LEVEL:
        return "WARNING";
    case SBN_INFO_LEVEL:
        return "INFO";
    case SBN_DEBUG_LEVEL:
        return "DEBUG";
    case SBN_PROTODBG_LEVEL:
        return "PROTODBG";
    }

    return "UNKNOWN";
}

sbn_status_t SBN_Log(char *module, sbn_t *SBN, sbn_log_level level, int code, char *format, ...)
{
    va_list args;
    char *levelName = getLogLevelName(level);
    time_t now = time(0);
    char timeBuf[sizeof("2000-01-01 00:00:00") + 1];
    int pid = getPID();
    FILE *file;

    if ((module == NULL) || (SBN == NULL) || (format == NULL) || (levelName == NULL)) {
        return SBN_ERROR;
    }

    if (SBN->log.mode == SBN_NO_LOG_LEVEL || level > SBN->log.mode)
        return SBN_SKIP;

    strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", localtime(&now));

    if(SBN->log.printToScreen) {
        printf("%s %d %s %-" LOG_LEVEL_PADDING "s %d ", timeBuf, pid, module, levelName, code);
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
        printf("\n");
    }

    file = getLogFile(SBN);
    if (file == NULL) {
        return SBN_ERROR;
    }

    fprintf(file, "%s %d %s %-" LOG_LEVEL_PADDING "s %d ", timeBuf, pid, module, levelName, code);
    va_start(args, format);
    vfprintf(file, format, args);
    va_end(args);
    fprintf(file, "\n");
    fflush(file);

    return SBN_OK;
}
