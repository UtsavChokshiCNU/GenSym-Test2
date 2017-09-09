#ifndef G2SBN_H
#define G2SBN_H

#include "gsi_main.h"
#include "sbn.h"

extern sbn_t SBN; /* global for GSI callbacks */

/**
 * Application message callback
 * @param message id
 * @param payload
 * @param payload size
 */
sbn_status_t app_message_callback(SBN_MsgId_t id, void *payload, int size);

#endif
