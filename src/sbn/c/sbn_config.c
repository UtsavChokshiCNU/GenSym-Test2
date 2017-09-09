#include "sbn.h"
#include <assert.h>

#define SBN_LOAD_CFG_ERR "Error loading G2 SBN config."
#define MAX_CFG_LINE 256

sbn_status_t process_param(sbn_t* SBN, char *name, char *value_str);
int is_space_str(char *str);

sbn_status_t SBN_LoadConfig(sbn_t* SBN, const char *file_name)
{
    char line[MAX_CFG_LINE];
    char name[MAX_CFG_LINE];
    char value_str[MAX_CFG_LINE];
    int i;
    char *ret;

    if ((SBN == NULL) || (file_name == NULL)) {
        return SBN_ERROR;
    }

    FILE *file = fopen(file_name, "rt");
    if (file == NULL) {
        printf("Can not open configuration file: %s\n", file_name);
        return SBN_ERROR;
    }

    for (i = 1; ; ++i) {
        ret = fgets(line, sizeof(line), file);
        if (!ret) {
            break;
        }

        if (sscanf(line, " %s = %s\n", name, value_str) == 2) {
            if (process_param(SBN, name, value_str) == SBN_ERROR) {
                return SBN_ERROR;
            }
        } else if (strlen(line) > 1 && line[0] == '#') {
            //Comment line in the config
            continue;
        } else if (is_space_str(line)) {
            //Empty line or spaces
            continue;
        } else {
            fprintf(stderr, SBN_LOAD_CFG_ERR " Unable to parse line %d: %s\n", i, line);
            return SBN_ERROR;
        }
    }

    printf("Settings: LogMode = %d, LogRollingPeriod = %d seconds, LogToScreen = %d\n",
           SBN->log.mode, SBN->log.maxFileDuration * SBN->log.maxFileDurationScale, SBN->log.printToScreen);

    return SBN_OK;
}

sbn_status_t process_param(sbn_t* SBN, char *name, char *value_str)
{   
    int value;
    if ( (SBN == NULL) || (name == NULL) || (value_str == NULL)) {
        return SBN_ERROR;
    }

    if (strcmp(name, "G2SBN_Logging") == 0) {
        value = atoi(value_str);
        if (value < SBN_NO_LOG_LEVEL || value > SBN_PROTODBG_LEVEL) {
            fprintf(stderr, SBN_LOAD_CFG_ERR " Wrong G2SBN_Logging value: %s\n", value_str);
            return SBN_ERROR;
        }
        SBN->log.mode = value;
    } else if (strcmp(name, "Rolling_Log_frequency") == 0) {
        value = atoi(value_str);
        if (value <= 0) {
            fprintf(stderr, SBN_LOAD_CFG_ERR " Wrong Rolling_Log_frequency value: %s\n", value_str);
            return SBN_ERROR;
        }
        SBN->log.maxFileDuration = value;
   } else if (strcmp(name, "Rolling_Log_duration") == 0) {
        if (strcmp(value_str, "M") == 0) {
            value = 60;
        } else if (strcmp(value_str, "H") == 0) {
            value = 60 * 60;
        } else if (strcmp(value_str, "D") == 0) {
            value = 60 * 60 * 24;
        } else {
            fprintf(stderr, SBN_LOAD_CFG_ERR " Wrong Rolling_Log_duration value: %s\n", value_str);
            return SBN_ERROR;
        }
        SBN->log.maxFileDurationScale = value;
    } else if (strcmp(name, "LogToScreen") == 0) {
        if (strcmp(value_str, "true") == 0) {
            SBN->log.printToScreen = true;
        } else if (strcmp(value_str, "false") == 0) {
            SBN->log.printToScreen = false;
        } else {
            fprintf(stderr, SBN_LOAD_CFG_ERR " Wrong LogToScreen setting: %s\n", value_str);
            return SBN_ERROR;
        }
    } else {
        fprintf(stderr, SBN_LOAD_CFG_ERR " Unexpected setting: %s\n", name);
        return SBN_ERROR;
    }

    return SBN_OK;
}

int is_space_str(char *str)
{
    unsigned i;
    assert(str != NULL);

    unsigned len = strlen(str);
    for(i = 0; i < len; ++i) {
        if (!isspace(str[i])) {
            return 0;
        }
    }

    return 1;
}
