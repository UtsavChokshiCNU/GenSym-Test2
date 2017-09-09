/*
  SBN GSI Bridge
*/

#include <stdlib.h>
#include "g2sbn.h"

enum { RET_OK, RET_FAIL };

int main(int argc, char* argv[])
{   
    GSI_SET_OPTIONS_FROM_COMPILE();

    // Check for debug options, remove them from argument list for gsi_start()
    int i = 0;
    for (; i < argc; ++i) {
        if (strcmp(argv[i], "-debug") == 0) {
            sbn_debug = true;
            printf("Debug level logging enabled\n");
            if (i < argc - 1)
                memcpy(&argv[i], &argv[i+1], sizeof(char*) * argc - 1 - i);
            --argc;
            --i;
        } else if (strcmp(argv[i], "-debug-protocol") == 0) {
            sbn_debug_protocol = true;
            printf("Protocol debug logging enabled\n");
            if (i < argc - 1)
                memcpy(&argv[i], &argv[i+1], sizeof(char*) * argc - 1 - i);
            --argc;
            --i;
        }
    }

    if (SBN_Init(&SBN, NULL, NULL, NULL) != SBN_OK) {
        return RET_FAIL;
    }

    gsi_start(argc, argv);

    gsi_watch_fd(SBN.DataSocket);
    gsi_watch_fd(SBN.ProtoSocket);
    SBN.AppMsgCallback = app_message_callback;

    for (;;) {
        gsi_pause();
        if (SBN_Poll(&SBN) != SBN_OK) {
            return RET_FAIL;
        }
        gsi_run_loop();
    }

    return RET_OK;
}

