#ifndef SBN_H
#define SBN_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <assert.h>
#include <ctype.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
  SBN API
 */

#define SBN_CPU_NAME "CPU2" /* Our "hostname", used in SBN "DNS" */
#define SBN_PEER_FILENAME "/g2/src/sbn/SbnPeerData.dat" /* SBN "/etc/hosts" */
#define SBN_CONFIG_FILENAME "/g2/src/sbn/g2sbn.cfg" /* SBN config file */
#define SBN_MAIN_LOOP_DELAY 100 /* Main Loop delay, in milliseconds */
#define SBN_TIMEOUT_CYCLES  2 /* How many cycles to wait for heartbeat */
#define SBN_PEER_FILE_LINE_SIZE       128
#define SBN_MAX_NETWORK_PEERS         6
#define SBN_MAX_MSG_SIZE              1400
#define SBN_MAX_SUBSCRIPTIONS_COUNT   256
#define SBN_MAX_PEERNAME_LENGTH       8 /* with trailing NUL */
#define SBN_MAX_API_NAME              20
#define SBN_ITEMS_PER_FILE_LINE       6
#define SBN_IPv4                      1

#define CTASTR2(pre,post) pre ## post
#define CTASTR(pre,post) CTASTR2(pre,post)

/** Compile-time ("static") assert.
    The "msg" parameter must be a valid identifier, _not_ a string.
    Must be at most one per line.
 */
#define STATIC_ASSERT(cond,msg) \
    typedef struct { int CTASTR(static_assertion_failed_,msg) : !!(cond); } \
        CTASTR(static_assertion_failed_,__LINE__)

#ifdef __linux__
#   define G2_FUNCTION_NAME __FUNCTION__
#   define G2_SOURCE_LINE __LINE__

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define LINE_STRING STRINGIZE(__LINE__)

#define SBN_MODULE "G2SBN "__FILE__":" LINE_STRING
#endif

typedef uint16_t SBN_MsgId_t;

typedef enum {
    SBN_INIT, /* not used */
    SBN_ANNOUNCING, /* We send ANNOUNCE to this peer, waiting for ACK */
    SBN_PEER_SYNC, /* not used */
    SBN_HEARTBEATING /* Peer is alive, messages may be sent to it */
} sbn_state_t;

typedef enum {
    SBN_OK ,
    SBN_ERROR,
    SBN_SKIP
} sbn_status_t;

typedef enum {
    SBN_NO_MSG = 0,
    SBN_ANNOUNCE_MSG =            0x0010,
    SBN_ANNOUNCE_ACK_MSG =        0x0011,
    SBN_HEARTBEAT_MSG =           0x0020,
    SBN_HEARTBEAT_ACK_MSG =       0x0021,
    SBN_SUBSCRIBE_MSG =           0x0030,
    SBN_UN_SUBSCRIBE_MSG =        0x0040,
    SBN_APP_MSG =                 0x0050
} sbn_msg_type_t;

typedef enum {
    CCSDS_TLM, /* Telemetry message */
    CCSDS_CMD  /* Command message */
} ccsds_packet_type_t;

typedef enum {
    CFE_SB_TIME_32_16_SUBS = 1, /* 32 bits seconds + 16 bits subseconds (units = 2^^-16)  */
    CFE_SB_TIME_32_32_SUBS = 2, /* 32 bits seconds + 32 bits subseconds (units = 2^^-32)  */
    CFE_SB_TIME_32_32_M_20 = 3  /* 32 bits seconds + 20 bits microsecs + 12 bits reserved */
} CFE_SB_Packet_Time_Format_t;

typedef enum {
    SBN_NO_LOG_LEVEL,
    SBN_ERROR_LEVEL,
    SBN_WARNING_LEVEL,
    SBN_INFO_LEVEL,
    SBN_DEBUG_LEVEL,
    SBN_PROTODBG_LEVEL
} sbn_log_level;

typedef enum {
    SBN_NULL_POINTER_EID =          0,
    SBN_INIT_EID =                  1,
    SBN_MSGID_ERR_EID =             2,
    SBN_FILE_ERR_EID =              3,
    SBN_PROTO_INIT_ERR_EID =        4,
    SBN_VOL_FAILED_EID =            5,
    SBN_NONVOL_FAILED_EID =         6,
    SBN_INV_LINE_EID =              7,
    SBN_FILE_OPENED_EID =           8,
    SBN_CPY_ERR_EID =               9,
    SBN_PEERPIPE_CR_ERR_EID =       10,

    SBN_SOCK_FAIL_EID =             12,
    SBN_BIND_FAIL_EID =             13,
    SBN_PEERPIPE_CR_EID =           14,
    SBN_SND_APPMSG_ERR_EID =        15,
    SBN_APPMSG_SENT_EID =           16,
    SBN_PEER_ALIVE_EID =            17,
    SBN_HB_LOST_EID =               18,
    SBN_STATE_ERR_EID =             19,

    SBN_MSG_TRUNCATED_EID =         21,
    SBN_LSC_ERR1_EID =              22,
    SBN_SUBTYPE_ERR_EID =           23,
    SBN_NET_RCV_PROTO_ERR_EID =     24,
    SBN_SRCNAME_ERR_EID =           25,
    SBN_ANN_RCVD_EID =              26,
    SBN_ANN_ACK_RCVD_EID =          27,
    SBN_HB_RCVD_EID =               28,
    SBN_HB_ACK_RCVD_EID =           29,
    SBN_SUB_RCVD_EID =              30,
    SBN_UNSUB_RCVD_EID =            31,
    SBN_PEERIDX_ERR1_EID =          32,
    SBN_SUB_ERR_EID =               33,
    SBN_DUP_SUB_EID =               34,
    SBN_PEERIDX_ERR2_EID =          35,
    SBN_NO_SUBS_EID =               36,
    SBN_SUB_NOT_FOUND_EID =         37,
    SBN_SOCK_RCV_APP_ERR_EID =      38,
    SBN_SB_SEND_ERR_EID =           39,
    SBN_MSGTYPE_ERR_EID =           40,
    SBN_LSC_ERR2_EID =              41,
    SBN_ENTRY_ERR_EID =             42,
    SBN_PEERIDX_ERR3_EID =          43,
    SBN_UNSUB_CNT_EID =             44,
    SBN_PROTO_SENT_EID =            45,
    SBN_PROTO_SEND_ERR_EID =        46,

    SBN_PIPE_ERR_EID =              47,

    SBN_PROTO_MSG_EID =             48,
    SBN_PAYLOAD_MSG_EID =           49,
    SBN_CMD_EID =                   50,
    SBN_MISC_ERROR_EID =            51
} sbn_event;

typedef  struct {
    uint8_t         Priority; /** currently unused */
    uint8_t         Reliability; /** currently unused */
} SBN_QoS_t;

typedef struct {
    int       ProcessorId; /* Processor Id from which the message was sent */
    char      AppName[SBN_MAX_API_NAME]; /* Application that sent the message */
} SBN_SenderId_t;

typedef struct {
  uint32_t       Type;
  char           SrcCpuName[SBN_MAX_PEERNAME_LENGTH]; /* Originator */
  SBN_SenderId_t MsgSender; /* This is the SB message originator metadata */
} SBN_NetMsgHeader_t;

/* SBN Network message for Announce and Heartbeat */
typedef struct {
  SBN_NetMsgHeader_t  Hdr;
} SBN_NetCommonMsg_t;

typedef struct {
  SBN_MsgId_t    MsgId;
  SBN_QoS_t      Qos;
} SBN_NetSubscriptionPayload_t;

typedef struct {
  SBN_NetMsgHeader_t           Hdr;
  SBN_NetSubscriptionPayload_t payload;
} SBN_NetSubscriptionMsg_t;

typedef struct {
    uint32_t     RefCounter;
    SBN_NetSubscriptionPayload_t payload;
} SBN_SubscriptionCacheEntry_t;

/**********************************************************************
** Structure definitions for CCSDS headers.  All items in the structure
** must be aligned on 16-bit words.  Bitfields must be avoided since
** some compilers (such as gcc) force them into 32-bit alignment.
**********************************************************************/

/*----- CCSDS packet primary header. -----*/

typedef struct {
    uint8_t StreamId[2];  /* packet identifier word (stream ID) */
    /*  bits  shift   ------------ description ---------------- */
    /* 0x07FF    0  : application ID                            */
    /* 0x0800   11  : secondary header: 0 = absent, 1 = present */
    /* 0x1000   12  : packet type:      0 = TLM, 1 = CMD        */
    /* 0xE000   13  : CCSDS version, always set to 0            */
    
    uint8_t Sequence[2];  /* packet sequence word */
    /*  bits  shift   ------------ description ---------------- */
    /* 0x3FFF    0  : sequence count                            */
    /* 0xC000   14  : segmentation flags:  3 = complete packet  */
    
    uint8_t Length[2];     /* packet length word */
    /*  bits  shift   ------------ description ---------------- */
    /* 0xFFFF    0  : (total packet length) - 7                 */
} CCSDS_PriHdr_t;

/*----- CCSDS command secondary header. -----*/

typedef struct {
   uint16_t Command;      /* command secondary header */
      /*  bits  shift   ------------ description ---------------- */
      /* 0x00FF    0  : checksum, calculated by ground system     */
      /* 0x7F00    8  : command function code                     */
      /* 0x8000   15  : reserved, set to 0                        */
} CCSDS_CmdSecHdr_t;

/*----- CCSDS telemetry secondary header. -----*/

typedef struct {
    uint8_t Time[6]; /* timestamp */
} CCSDS_TlmSecHdr6_t;

typedef struct {
    uint8_t Time[8]; /* timestamp */
} CCSDS_TlmSecHdr8_t;

/*----- Generic combined command header. -----*/

typedef struct {
    CCSDS_PriHdr_t       PriHdr;
    CCSDS_CmdSecHdr_t    SecHdr;
} CCSDS_CmdPkt_t;

/*----- Generic combined telemetry header. -----*/

typedef struct {
    CCSDS_PriHdr_t       PriHdr;
    CCSDS_TlmSecHdr6_t   SecHdr;
} CCSDS_TlmPkt6_t;

typedef struct {
   CCSDS_PriHdr_t       PriHdr;
   CCSDS_TlmSecHdr8_t   SecHdr;
} CCSDS_TlmPkt8_t;

/* Remote peers state */
typedef struct {
    char            Name[SBN_MAX_PEERNAME_LENGTH+1];
    struct sockaddr_in DataAddr;
    struct sockaddr_in ProtoAddr;
    int             ProcessorId;
    sbn_state_t     State;
    bool            AnnounceAckReceived;
    bool            HeartbeatAckReceived;
    int             SubscriptionCount;
    /* Subscrptions from remote to local peer*/
    SBN_SubscriptionCacheEntry_t SubscriptionCache[SBN_MAX_SUBSCRIPTIONS_COUNT];
} SBN_PeerData_t;

typedef struct {
    /* Log verbosity
     * Config setting: G2SBN_Logging: 0 - disabled, 1 - errors,
     * 2 - errors and warnings, 3 - errors, warnings and messages */
    sbn_log_level mode;
    /* Maximum duration of log file before rotation.
    /* Config setting: Rolling_Log_frequency (number) */
    int maxFileDuration;
    /* Units for maximum duration of log file, converted to seconds.
     * Config setting: Rolling_Log_duration (M, H, D). */
    int maxFileDurationScale;
    /* Print log message also on stdout.
     * Config setting: LogToScreen. */
    bool printToScreen;
    FILE *fileHandle;
    time_t startTime;
} SBN_Log_t;

/* SBN state */
typedef struct {
    struct timespec Timer;
    int             MainLoopDelay;
    int             TimeoutCycles;
    int             DataSocket;
    int             ProtoSocket;
    int             SelfIndex;
    int             PeerCount;
    SBN_PeerData_t  Peer[SBN_MAX_NETWORK_PEERS];
    SBN_Log_t       log;
    int             AppId;
    char*           NodeName;
    int             SubscriptionCount;
    /* Subscrptions from the peer to remotes */
    SBN_SubscriptionCacheEntry_t SubscriptionCache[SBN_MAX_SUBSCRIPTIONS_COUNT];
    sbn_status_t (*AppMsgCallback)(SBN_MsgId_t id, void *payload, int size);
} sbn_t;

extern bool sbn_debug;
extern bool sbn_debug_protocol;

/**
 * parses an entry in SBN Peer file and fills peer data structure
 * @param SBN a SBN data structure
 * @param name our "hostname"
 * @param buf a peer entry
 * @return SBN_OK on success, SBN_ERROR on error
 */
sbn_status_t SBN_ParseFileEntry(sbn_t* SBN, const char* name, const char* buf);

/**
 * slurps SBN Peer file and fills peer data structures
 * @param SBN a SBN data structure
 * @param name our "hostname", if NULL, SBN_CPU_NAME env var is used, if present, otherwise, the value of SBN_CPU_NAME define
 * @param peers Peer file path, if NULL, SBN_PEER_FILENAME env var is used, if present, otherwise, the value of SBN_PEER_FILENAME define
 * @return SBN_OK on success, SBN_ERROR on error
 */
sbn_status_t SBN_GetPeerFileData(sbn_t* SBN, const char* name, const char *peers);

/**
 * initializes SBN protocol
 * @param SBN a SBN data structure
 * @param name our "hostname", if NULL, SBN_CPU_NAME env var is used, if present, otherwise, the value of SBN_CPU_NAME define
 * @param peers Peer file path, if NULL, SBN_PEER_FILENAME env var is used, if present, otherwise, the value of SBN_PEER_FILENAME define
 * @param config Config file path, if NULL, SBN_CONFIG_FILENAME env var is used, if present, otherwise, the value of SBN_CONFIG_FILENAME define
 * @return SBN_OK on success, SBN_ERROR on error
 */
sbn_status_t SBN_Init(sbn_t* SBN, char* name, char *peers, char* config);

/**
 * closes SBN sockets and performs other clean-up
 * @param SBN a SBN data structure
 * @return SBN_OK on success, SBN_ERROR on error
 */
sbn_status_t SBN_Close(sbn_t* SBN);

/**
 * executes one cycle of SBN protocol
 * @param SBN a SBN data structure
 * @return SBN_OK on success, SBN_ERROR on error
 */
sbn_status_t SBN_Poll(sbn_t* SBN);

/**
 * finds peer by name
 * @param SBN a SBN data structure
 * @return peer index if found, -1 otherwise
 */
int SBN_FindPeerByName(sbn_t* SBN, const char* name);

/**
 * given a proto message, finds the peer who sent it
 * @param SBN a SBN data structure
 * @param tag a tag for error messages
 * @param msg SBN protocol message
 * @return peer index if found, -1 otherwise
 */
int SBN_GetPeerIdxFromProtoMessage(sbn_t* SBN, const char* tag, SBN_NetCommonMsg_t *msg);

/**
 * handles ANNOUNCE message
 * @param SBN a SBN data structure
 * @param msg SBN protocol message
 * @return SBN_OK on success, SBN_ERROR on error
 */
sbn_status_t SBN_HandleAnnounce(sbn_t* SBN, SBN_NetCommonMsg_t *msg);

/**
 * handles ANNOUNCE ACK message
 * @param SBN a SBN data structure
 * @param msg SBN protocol message
 * @return SBN_OK on success, SBN_ERROR on error
 */
sbn_status_t SBN_HandleAnnounceAck(sbn_t* SBN, SBN_NetCommonMsg_t *msg);

/**
 * handles HEARTBEAT message
 * @param SBN a SBN data structure
 * @param msg SBN protocol message
 * @return SBN_OK on success, SBN_ERROR on error
 */
sbn_status_t SBN_HandleHeartbeat(sbn_t* SBN, SBN_NetCommonMsg_t *msg);

/**
 * handles HEARTBEAT ACK message
 * @param SBN a SBN data structure
 * @param msg SBN protocol message
 * @return SBN_OK on success, SBN_ERROR on error
 */
sbn_status_t SBN_HandleHeartbeatAck(sbn_t* SBN, SBN_NetCommonMsg_t *msg);

/**
 * checks for incoming protocol messages
 * @param SBN a SBN data structure
 * @return SBN_OK on success, SBN_ERROR on error
 */
sbn_status_t SBN_ReceiveServiceMessages(sbn_t* SBN);

/**
 * checks for incoming messages with payload
 * @param SBN a SBN data structure
 * @return SBN_OK on success, SBN_ERROR on error
 */
sbn_status_t SBN_ReceivePayloadMessages(sbn_t* SBN);

/**
 * subscribes to remote peers messages
 * @param SBN a SBN data structure
 * @param msg_id is a message Id to subscribe
 * @return SBN_OK on success, SBN_ERROR on error
*/
sbn_status_t SBN_Subscribe(sbn_t* SBN, uint16_t msg_id);

/**
 * unsubscribes to remote peers messages
 * @param SBN a SBN data structure
 * @param msg_id is the message Id to unsubscribe
 * @return SBN_OK on success, SBN_ERROR on error
*/
sbn_status_t SBN_Unsubscribe(sbn_t* SBN, uint16_t msg_id);

/**
 * sends an App Message
 * @param SBN a SBN data structure
 * @param id Message Id; packet type (Command or Telemetry) and presence of a secondary header are encoded in it
 * @param command command code
 * @param payload the message payload
 * @param payload_size payload size
 * @return SBN_OK on success, SBN_ERROR on error
*/
sbn_status_t SBN_SendAppMessage(sbn_t* SBN, 
                                SBN_MsgId_t id, uint16_t command,
                                void *payload, int payload_size);
/**
 * Load settings from file
 * @param SBN a SBN data structure
 * @param file_name is a configuration file name.
 * @return SBN_OK on success, SBN_ERROR on error
*/
sbn_status_t SBN_LoadConfig(sbn_t* SBN, const char *file_name);

/**
 * Log a message to file
 * @param module - application module name
 * @param SBN a SBN data structure
 * @param level: 1 - error, 2 - warning, 3 - info
 * @param code - message code
 * @param format - format string of the message
 * @return SBN_OK on success, SBN_ERROR on error, SBN_SKIP if logging on that level is disabled
*/
sbn_status_t SBN_Log(char *module, sbn_t *SBN, sbn_log_level level, int code, char *format, ...);

/** Helper functions **/

/* returns SBN_OK if it's time to check peers' state, SBN_SKIP if it's early to check peers' state, and SBN_ERROR if an error occured */
sbn_status_t SBN_CheckInterval(sbn_t* SBN);

/* reads UDP packet from socket, returns size of packet, 0 if there was no messages, -1 if an error occured */
ssize_t SBN_ReceiveFromSocket(sbn_t *SBN, int socket, unsigned char *buf, int size);

/* Subscriptions CRUD */
SBN_SubscriptionCacheEntry_t *SBN_FindSubscriptionToRemote(sbn_t *SBN, uint16_t msg_id);
SBN_SubscriptionCacheEntry_t *SBN_AddSubscriptionToRemote(sbn_t *SBN, uint16_t msg_id);
sbn_status_t SBN_RemoveSubscriptionToRemote(sbn_t* SBN, uint16_t msg_id);
SBN_SubscriptionCacheEntry_t *SBN_FindSubscriptionFromRemote(sbn_t *SBN, int peer_idx, uint16_t msg_id);
SBN_SubscriptionCacheEntry_t *SBN_AddSubscriptionFromRemote(sbn_t* SBN, int peer_idx,
                                  SBN_NetSubscriptionPayload_t *payload);
sbn_status_t SBN_RemoveSubscriptionFromRemote(sbn_t *SBN, int peer_idx, uint16_t msg_id);

/* send and receive SUBSCRIBE and UNSUBSCRIBE messages */
sbn_status_t SBN_SendSubscribeMsg(sbn_t* SBN, int peer_idx, SBN_NetSubscriptionPayload_t *payload, bool subscribe);
sbn_status_t SBN_HandleSubscribe(sbn_t* SBN, SBN_NetSubscriptionMsg_t *msg);
sbn_status_t SBN_HandleUnsubscribe(sbn_t *SBN, SBN_NetSubscriptionMsg_t *msg);
sbn_status_t SBN_SendAllSubscribeToRemote(sbn_t *SBN, int peer_idx);

/* returns 0 if there is no CCSDS header, -1 on error, actual size otherwise */
int CCSDS_Header_Size(sbn_msg_type_t sbn_type, SBN_MsgId_t id);

/* fills in SBN message; returns message size, or -1 on error */
int SBN_PrepareNetworkMsg(sbn_t* SBN, unsigned char *msg_buf,
                          sbn_msg_type_t sbn_type,
                          SBN_MsgId_t id, uint16_t command,
                          void *payload, int payload_size);

/* fills in App Message header */
sbn_status_t SBN_PrepareAppMsgHeader(sbn_t* SBN, void* buf, int length,
                                     SBN_MsgId_t id, uint16_t command);

/* maps message type enum to string */
char *SBN_GetMsgName(sbn_msg_type_t MsgType);

/**
**  Packet Timestamp Format Selection
**
**  Defines the size, format and contents of the telemetry packet timestamp.
**
**  Must be defined as one of the supported formats listed above
*/
#define CFE_SB_PACKET_TIME_FORMAT  CFE_SB_TIME_32_16_SUBS

/* Initial value of the sequence flags. */
#define CCSDS_INIT_SEQFLG   3 /* taken from cFE */

/**********************************************************************
** Functions for reading and writing bit fields in a 16-bit integer.
** These are used to implement the read and write functions below.
**********************************************************************/

/* Read bits specified by 'mask' from 'word' and shift down by 'shift'. */
uint16_t CCSDS_RD_BITS(uint16_t word, int mask, int shift);

/* Shift 'value' up by 'shift' and write to those bits in 'word' that
** are specified by 'mask'.  Other bits in 'word' are unchanged.   */
void CCSDS_WR_BITS(uint16_t *word, int mask, int shift, uint16_t value);

/**********************************************************************
** Functions for clearing a CCSDS header to a standard initial state.  All
** of the functions are used in a similar way:
**   CCSDS_CLR_xxx_HDR(header)      -- Clear header of type xxx.
**********************************************************************/

/* Clear primary header. */
void CCSDS_CLR_PRI_HDR(CCSDS_PriHdr_t *phdr);

/**********************************************************************
** Functions for reading and writing the fields in a CCSDS header.  All
** of the functions are used in a similar way:
**
**   CCSDS_RD_xxx(header)        -- Read field xxx from header.
**   CCSDS_WR_xxx(header,value)  -- Write value to field xxx of header.
**
**********************************************************************/

/* Read entire stream ID from primary header. */
uint16_t CCSDS_RD_SID(CCSDS_PriHdr_t *phdr);

/* Write entire stream ID to primary header. */
void CCSDS_WR_SID(CCSDS_PriHdr_t *phdr, uint16_t value);

/* Read secondary header flag from primary header. */
uint16_t CCSDS_RD_SHDR(CCSDS_PriHdr_t *phdr);

/* Write secondary header flag to primary header. */
void CCSDS_WR_SHDR(CCSDS_PriHdr_t *phdr, uint16_t value);

/* Read packet type (0=TLM,1=CMD) from primary header. */
uint16_t CCSDS_RD_TYPE(CCSDS_PriHdr_t *phdr);

/* Write packet type (0=TLM,1=CMD) to primary header. */
void CCSDS_WR_TYPE(CCSDS_PriHdr_t *phdr, uint16_t value);

/* Read CCSDS version from primary header. */
uint16_t CCSDS_RD_VERS(CCSDS_PriHdr_t *phdr);

/* Write CCSDS version to primary header. */
void CCSDS_WR_VERS(CCSDS_PriHdr_t *phdr, uint16_t value);

/* Read sequence count from primary header. */
uint16_t CCSDS_RD_SEQ(CCSDS_PriHdr_t *phdr);

/* Write sequence count to primary header. */
void CCSDS_WR_SEQ(CCSDS_PriHdr_t *phdr, uint16_t value);

/* Read sequence flags from primary header. */
uint16_t CCSDS_RD_SEQFLG(CCSDS_PriHdr_t *phdr);

/* Write sequence flags to primary header. */
void CCSDS_WR_SEQFLG(CCSDS_PriHdr_t *phdr, uint16_t value);

/* Read total packet length from primary header. */
uint16_t CCSDS_RD_LEN(CCSDS_PriHdr_t *phdr);

/* Write total packet length to primary header. */
void CCSDS_WR_LEN(CCSDS_PriHdr_t *phdr, uint16_t value);

/* Read function code from command secondary header. */
uint16_t CCSDS_RD_FC(CCSDS_CmdSecHdr_t *shdr);

/* Write function code to command secondary header. */
void CCSDS_WR_FC(CCSDS_CmdSecHdr_t *shdr, uint16_t value);

/* Read checksum from command secondary header. */
uint16_t CCSDS_RD_CHECKSUM(CCSDS_CmdSecHdr_t *shdr);

/* Write checksum to command secondary header. */
void CCSDS_WR_CHECKSUM(CCSDS_CmdSecHdr_t *shdr, uint16_t val);

#endif
