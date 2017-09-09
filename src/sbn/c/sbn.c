#include "sbn.h"

bool sbn_debug = false;
bool sbn_debug_protocol = false;
SBN_QoS_t defaultQoS;

sbn_status_t SBN_ParseFileEntry(sbn_t *SBN, const char* name, const char *buf)
{
    int res;
    int protid;
    char fmt[256];
    char addr[17];
    int dport;
    int pport;
    SBN_PeerData_t* peer;

    if (SBN == NULL) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_NULL_POINTER_EID,
                "SBN is NULL");
        return SBN_ERROR;
    }
    
    if (buf == NULL) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_NULL_POINTER_EID,
                "Entry is NULL");
        return SBN_ERROR;
    }
    
    sprintf(fmt, "%%%ds %%d %%d %%16s %%d %%d", SBN_MAX_PEERNAME_LENGTH - 1);

    peer = &SBN->Peer[SBN->PeerCount];

    res = sscanf(buf, fmt, peer->Name,
                 &peer->ProcessorId, &protid, addr, &dport, &pport);

    if (res != SBN_ITEMS_PER_FILE_LINE) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_INV_LINE_EID,
                "Invalid SBN peer file line,exp %d items,found %d",
                SBN_ITEMS_PER_FILE_LINE, res);
        return SBN_ERROR;                        
    }

    if (protid != SBN_IPv4) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_INV_LINE_EID,
                "Invalid SBN protocol Id,exp %d,found %d",
                SBN_IPv4, protid);
        return SBN_ERROR;                        
    }

    memset(&peer->DataAddr,0,sizeof(struct sockaddr_in));
    peer->DataAddr.sin_family = AF_INET;
    peer->DataAddr.sin_port = htons(dport);
    if (!inet_aton(addr, &peer->DataAddr.sin_addr)) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID,
                "Invalid IP address: %s", addr);
        return SBN_ERROR;
    }

    peer->ProtoAddr = peer->DataAddr;
    peer->ProtoAddr.sin_port = htons(pport);

    peer->SubscriptionCount = 0;
    peer->State = SBN_ANNOUNCING;
    peer->AnnounceAckReceived = false;
    peer->HeartbeatAckReceived = false; 

    if (name &&
        (strncmp(peer->Name, name, SBN_MAX_PEERNAME_LENGTH) == 0)) {
        SBN->SelfIndex = SBN->PeerCount;
    }
    
    return SBN_OK;
}

sbn_status_t SBN_GetPeerFileData(sbn_t* SBN, const char* name, const char *peers)
{
    const char *fname = SBN_PEER_FILENAME;
    char buf[SBN_PEER_FILE_LINE_SIZE];
    int len = 0;
    int fd;
    char c;
    ssize_t r;

    if (SBN == NULL) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_NULL_POINTER_EID,
                "SBN is NULL");
        return SBN_ERROR;
    }
    
    if (peers) {
        fname = peers;
    } else if (getenv("SBN_PEER_FILENAME")) {
        fname = getenv("SBN_PEER_FILENAME");
    }

    fd = open(fname, O_RDONLY, 0);

    if (fd == -1) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_NONVOL_FAILED_EID,
                "Peer file %s failed to open", fname);
        return SBN_ERROR;
    }

    SBN_Log(SBN_MODULE, SBN, SBN_INFO_LEVEL, SBN_FILE_OPENED_EID,
	    "Opened SBN Peer Data file %s", fname);

    SBN->PeerCount = 0;
    SBN->SelfIndex = -1;
    memset(buf, 0x0, SBN_PEER_FILE_LINE_SIZE);

    for (r = read(fd, &c, 1); r; r = read(fd, &c, 1)) {

        if (r == -1) {
            SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID,
                    "%s", strerror(errno));
            close(fd);
            return SBN_ERROR;
        }

        if (c == '!') { break; }

        if (c == '\n' || c == ' ' || c == '\t') {
            /*
             ** Skip all white space in the file
             */
            ;
        } else if (c == ',') {
            /*
             ** replace the field delimiter with a space
             ** This is used for the sscanf string parsing
             */
            buf[len] = ' ';
            if (len < (SBN_PEER_FILE_LINE_SIZE - 1)) {
                len++;
            }
        } else if (c != ';') {
            /*
             ** Regular data gets copied in
             */
            buf[len] = c;
            if (len < (SBN_PEER_FILE_LINE_SIZE - 1)) {
                len++;
            }
        } else {
            /*
             ** Send the line to the file parser
             */
            if(SBN->PeerCount < SBN_MAX_NETWORK_PEERS) {
                if (SBN_ParseFileEntry(SBN, name, buf) == SBN_ERROR) {
                    close(fd);
                    return SBN_ERROR;
                }
                memset(buf, 0x0, SBN_PEER_FILE_LINE_SIZE);
                len = 0;
                SBN->PeerCount++;
            } else {
                SBN_Log(SBN_MODULE, SBN, SBN_WARNING_LEVEL, SBN_MISC_ERROR_EID,
                        "More lines available, but stopped parsing after first %d peers", SBN_MAX_NETWORK_PEERS);
                break;
            }
        }
    }

    close(fd);

    if (SBN->SelfIndex == -1) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID,
                "No data for our CPU name %s found", name);
        return SBN_ERROR;
    }

    return SBN_OK;
}

sbn_status_t SBN_InitNetwork(sbn_t *SBN)
{

    if (SBN == NULL) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_NULL_POINTER_EID,
                "SBN is NULL");
        return SBN_ERROR;
    }

    SBN->DataSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (SBN->DataSocket == -1) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_SOCK_FAIL_EID,
                "%s", strerror(errno));
        return SBN_ERROR;
    }

    if (bind(SBN->DataSocket,
             (struct sockaddr*)&SBN->Peer[SBN->SelfIndex].DataAddr,
             sizeof(struct sockaddr_in))) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_SOCK_FAIL_EID,
                "%s", strerror(errno));
        close(SBN->DataSocket);
        return SBN_ERROR;
    }
    
    SBN->ProtoSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (SBN->ProtoSocket == -1) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_SOCK_FAIL_EID,
                "%s", strerror(errno));
        close(SBN->DataSocket);
        return SBN_ERROR;
    }

    if (bind(SBN->ProtoSocket,
             (struct sockaddr*)&SBN->Peer[SBN->SelfIndex].ProtoAddr,
             sizeof(struct sockaddr_in))) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_SOCK_FAIL_EID,
                "%s", strerror(errno));
        close(SBN->DataSocket);
        close(SBN->ProtoSocket); /* goto-style "dctor"? */
        return SBN_ERROR;
    }

    return SBN_OK;
}

sbn_status_t SBN_Init(sbn_t* SBN, char* name, char *peers, char* config)
{
    char* sbn_config_name;
    
    if (SBN == NULL) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_NULL_POINTER_EID,
                "SBN is NULL");
        return SBN_ERROR;
    }

    SBN->AppId = 0;

    if (name) {
	SBN->NodeName = name;
    } else if (getenv("SBN_CPU_NAME")) {
        SBN->NodeName = getenv("SBN_CPU_NAME");
    } else {
        SBN->NodeName = SBN_CPU_NAME;
    }

    if (config) {
	sbn_config_name = config;
    } else if (getenv("SBN_CONFIG_FILENAME")) {
        sbn_config_name = getenv("SBN_CONFIG_FILENAME");
    } else {
        sbn_config_name = SBN_CONFIG_FILENAME;
    }

    defaultQoS.Priority = 0;
    defaultQoS.Reliability = 0;

    SBN->log.fileHandle = 0;

    if (SBN_LoadConfig(SBN, sbn_config_name) == SBN_ERROR) {
        return SBN_ERROR;
    }
    
    if (SBN_GetPeerFileData(SBN, SBN->NodeName, peers) == SBN_ERROR) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_FILE_ERR_EID,
                "SBN APP Will Terminate, Peer File Not Found or Data Invalid!");
        return SBN_ERROR;
    }

    if (clock_gettime(CLOCK_REALTIME, &SBN->Timer)) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID,
                "%s", strerror(errno));
        return SBN_ERROR;
    }

    if (SBN_InitNetwork(SBN) == SBN_ERROR) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_PROTO_INIT_ERR_EID,
                "SBN APP Will Terminate, Error Creating Interfaces!");
    }

    SBN->MainLoopDelay = SBN_MAIN_LOOP_DELAY;
    SBN->TimeoutCycles = SBN_TIMEOUT_CYCLES;
    SBN->AppMsgCallback = NULL;

    SBN_Log(SBN_MODULE, SBN, SBN_INFO_LEVEL, SBN_PROTO_INIT_ERR_EID,
            "SBN APP Initialized V1.0, AppId=%d", SBN->AppId);
    
    return SBN_OK;
}

sbn_status_t SBN_Close(sbn_t* SBN)
{
    sbn_status_t status = SBN_OK;

    if (SBN == NULL) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_NULL_POINTER_EID,
                "SBN is NULL");
        return SBN_ERROR;
    }
    
    if (close(SBN->DataSocket)) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID,
                "%s", strerror(errno));
        status = SBN_ERROR;
    }
    if (close(SBN->ProtoSocket)) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID,
                "%s", strerror(errno));
        status = SBN_ERROR;
    }
    return status;
}

int SBN_FindPeerByName(sbn_t* SBN, const char *name)
{
    int i;

    if (SBN == NULL) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_NULL_POINTER_EID,
                "SBN is NULL");
        return -1;
    }
    
    if (name) {
        for (i = 0; i < SBN->PeerCount; i++) {
            if (strncmp(SBN->Peer[i].Name, name, SBN_MAX_PEERNAME_LENGTH)==0) {
                return i;
            }
        }
    }
    return -1;
}

int CCSDS_Header_Size(sbn_msg_type_t sbn_type, SBN_MsgId_t id)
{
    int ccsds_header_size = 0;
    
    if (sbn_type == SBN_APP_MSG) {
        CCSDS_PriHdr_t placeholder;
        ccsds_packet_type_t ccsds_type;
        bool has_ccsds_secondary_header;
        int version;
        
        CCSDS_WR_SID(&placeholder, id); /* to account for endianness */
        version = CCSDS_RD_VERS(&placeholder);
        if (version != 0) {
            return -1;
        } 
        ccsds_type = CCSDS_RD_TYPE(&placeholder);
        has_ccsds_secondary_header = CCSDS_RD_SHDR(&placeholder);
        if (!has_ccsds_secondary_header) {
            ccsds_header_size = sizeof(CCSDS_PriHdr_t);
        } else {
            switch (ccsds_type) {
            case CCSDS_CMD:
                ccsds_header_size = sizeof(CCSDS_CmdPkt_t);
                break;
            case CCSDS_TLM:
                if (CFE_SB_PACKET_TIME_FORMAT == CFE_SB_TIME_32_16_SUBS) {
                    ccsds_header_size = sizeof(CCSDS_TlmPkt6_t);
                } else {
                    ccsds_header_size = sizeof(CCSDS_TlmPkt8_t);
                }
            }
        }
    }
    
    return ccsds_header_size;
}

void CCSDS_InitPkt (CCSDS_PriHdr_t  *PktPtr,
                    uint16_t         StreamId,
                    uint16_t         Length)
{
   /* Clear the primary header. */
   CCSDS_CLR_PRI_HDR(PktPtr);

   /* Set the stream ID and length fields in the primary header. */
   CCSDS_WR_SID(PktPtr, StreamId);
   CCSDS_WR_LEN(PktPtr, Length);
}

uint8_t CCSDS_ComputeCheckSum (CCSDS_CmdPkt_t *PktPtr)
{
   uint16_t   PktLen   = CCSDS_RD_LEN(&PktPtr->PriHdr);
   uint8_t   *BytePtr  = (uint8_t *)PktPtr;
   uint8_t    CheckSum;

   CheckSum = 0xFF;
   while (PktLen--) CheckSum ^= *(BytePtr++);

   return CheckSum;

}

uint32_t SBN_Micro2SubSecs(uint32_t MicroSeconds)
{
    uint32_t SubSeconds;

    /*
    ** Conversion amount must be less than one second
    */
    if (MicroSeconds > 999999)
    {
        SubSeconds = 0xFFFFFFFF;
    }
    else
    {
    /*
    **  Convert micro-seconds count to sub-seconds (1/2^32) count
    **
    **  Conversion factor is  ( ( 10 ** -6 ) / ( 2 ** -20 ).
    **
    **  Logic is as follows:
    **    x * ( ( 10 ** -6 ) / ( 2 ** -32 ) )
    **  = x * ( ( 2 ** 32 ) / ( 10 ** 6 ) )
    **  = x * ( ( ( 2 ** 26 ) ( 2 ** 6) ) / ( ( 5 ** 6 ) ( 2 ** 6 ) ) )
    **  = x * ( ( 2 ** 26 ) / ( 5 ** 6 ) )
    **  = x * ( ( ( 2 ** 11) ( 2 ** 3) (2 ** 12) ) / ( 5( 5 ** 5 ) ) )
    **  = x * ( ( ( ( ( 2 ** 11 ) / 5 ) * ( 2 ** 3 ) ) / ( 5 ** 5 ) ) * (2 ** 12
) )
    **  
    **  C code equivalent:
    **  = ( ( ( ( ( x << 11 ) / 5 ) << 3 ) / 3125 ) << 12 )
    **  
    **  Conversion factor was reduced and factored accordingly
    **  to minimize precision loss and register overflow.
    */
        SubSeconds = ( ( ( ( MicroSeconds << 11 ) / 5 ) << 3 ) / 3125 ) << 12;
    
        /* To get the SubSeconds to "bump up" against 0xFFFFF000 when
         * MicroSeconds = 9999999, we add in another anomaly to the
         * conversion at the half-way point  (500000 us). This will bump
         * all of the subseconds up by 0x1000, so 999999 us == 0xFFFFF00,
         * 999998 == 0xFFFFE000, etc. This extra anomaly is accounted for
         * in the Sub2MicroSecs conversion as well.
         */

        if (SubSeconds > 0x80001000)
        {
           SubSeconds += 0x1000;
        }
           
    }
           
    return(SubSeconds);
}

sbn_status_t CCSDS_SetMsgTime(sbn_t* SBN, uint8_t* TimeBuf)
{
    uint16_t LocalSubs16;
    uint32_t LocalSubs32, Subseconds;
    struct timespec now;

    if (TimeBuf == NULL) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_NULL_POINTER_EID,
                "TimeBuf is NULL");
        return SBN_ERROR;
    }
    
    if (clock_gettime(CLOCK_REALTIME, &now)) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID,
                "%s", strerror(errno));
        return SBN_ERROR;
    }

    Subseconds = SBN_Micro2SubSecs(now.tv_nsec * 1000);
    
    memcpy(&TimeBuf[0], &now.tv_sec, 4); /* endianness? */
    
    switch (CFE_SB_PACKET_TIME_FORMAT) {
    case CFE_SB_TIME_32_16_SUBS:
        LocalSubs16 = (uint16_t) (Subseconds >> 16);
        memcpy(&TimeBuf[4], &LocalSubs16, 2);
        break;
    case CFE_SB_TIME_32_32_SUBS:
        memcpy(&TimeBuf[4], &Subseconds, 4);
        break;
    case CFE_SB_TIME_32_32_M_20:
        LocalSubs32 = (now.tv_nsec * 1000) << 12;
        memcpy(&TimeBuf[4], &LocalSubs32, 4);
        break;
    default:
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID,
                "Unknown CFE SB time format %d", CFE_SB_PACKET_TIME_FORMAT);
        return SBN_ERROR;
    }
    
    return SBN_OK;
}

sbn_status_t SBN_PrepareAppMsgHeader(sbn_t* SBN, void* buf, int length,
                                     SBN_MsgId_t id, uint16_t command)
{
    ccsds_packet_type_t ccsds_type;
    bool has_ccsds_secondary_header;
    CCSDS_PriHdr_t *pri = (CCSDS_PriHdr_t *)buf;

    if (buf == NULL) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_NULL_POINTER_EID,
                "buf is NULL");
        return SBN_ERROR;
    }

    STATIC_ASSERT(offsetof(CCSDS_PriHdr_t, StreamId) == 0,StreamID);
    STATIC_ASSERT(offsetof(CCSDS_PriHdr_t, Sequence) == 2,Sequence);
    STATIC_ASSERT(offsetof(CCSDS_PriHdr_t, Length) == 4,Length);
    
    CCSDS_InitPkt(pri, id, length);
    ccsds_type = CCSDS_RD_TYPE(pri);
    has_ccsds_secondary_header = CCSDS_RD_SHDR(pri);
    if (has_ccsds_secondary_header) {
        if (ccsds_type == CCSDS_CMD) {
            CCSDS_CmdPkt_t *CmdHdrPtr = (CCSDS_CmdPkt_t *)buf;
            uint8_t checksum = CCSDS_ComputeCheckSum(CmdHdrPtr);
            CCSDS_WR_FC(&CmdHdrPtr->SecHdr, command);
            CCSDS_WR_CHECKSUM(&CmdHdrPtr->SecHdr, checksum);
        } else {
            CCSDS_TlmPkt6_t *TlmHdrPtr = (CCSDS_TlmPkt6_t *)buf;
            return CCSDS_SetMsgTime(SBN, TlmHdrPtr->SecHdr.Time);
        }
    }
    return SBN_OK;
}

int SBN_PrepareNetworkMsg(sbn_t* SBN, unsigned char *msg_buf,
                          sbn_msg_type_t sbn_type,
                          SBN_MsgId_t id, uint16_t command,
                          void *payload, int payload_size)
{
    int header_size = sizeof(SBN_NetCommonMsg_t);
    int ccsds_header_size = CCSDS_Header_Size(sbn_type, id);
    int msg_size;
    SBN_NetCommonMsg_t *msg;
    
    if (SBN == NULL) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_NULL_POINTER_EID,
                "SBN is NULL");
        return -1;
    }
    
    if (msg_buf == NULL) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_NULL_POINTER_EID,
                "Destination buffer is NULL");
        return -1;
    }

    if (ccsds_header_size < 0) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID,
                "Can't calculate CCSDS header size for type %d and id %d",
                sbn_type, id);
        return -1;
    }
    
    msg_size = header_size + ccsds_header_size + payload_size;
    
    if (msg_size >= SBN_MAX_MSG_SIZE) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID,
                "Message size > %d", SBN_MAX_MSG_SIZE);
        return -1;
    }
    
    msg = (SBN_NetCommonMsg_t *)msg_buf;
    msg->Hdr.Type = sbn_type;
    strncpy(msg->Hdr.SrcCpuName,
            SBN->Peer[SBN->SelfIndex].Name,
            sizeof(msg->Hdr.SrcCpuName));
    msg->Hdr.SrcCpuName[sizeof(msg->Hdr.SrcCpuName) - 1] = 0;

    if(payload && payload_size) {
        memcpy(msg_buf + header_size + ccsds_header_size, 
               payload, payload_size);
    }

    if (sbn_type == SBN_APP_MSG) {
        if (SBN_PrepareAppMsgHeader(SBN, msg_buf + header_size,
                                    ccsds_header_size + payload_size,
                                    id, command) != SBN_OK) {
            return -1;
        }
    }
    
    return msg_size;
}

sbn_status_t SBN_SendNetworkMsg(sbn_t* SBN, int peer_idx, sbn_msg_type_t type,
                                void *payload, int payload_size)
{
    unsigned char msg_buf[SBN_MAX_MSG_SIZE];
    int msg_size = SBN_PrepareNetworkMsg(SBN, msg_buf, type,
                                         0, 0, payload, payload_size);
    int socket_handle, status;
    struct sockaddr *addr;
    SBN_PeerData_t* peer;
    
    if (msg_size < sizeof(SBN_NetCommonMsg_t)) {
        return SBN_ERROR;
    }

    peer = &SBN->Peer[peer_idx];
    
    switch (type) {
    case SBN_SUBSCRIBE_MSG:
    case SBN_UN_SUBSCRIBE_MSG:
    case SBN_APP_MSG:
        socket_handle = SBN->DataSocket;
        addr = (struct sockaddr *)&peer->DataAddr;
        break;
    default:
        socket_handle = SBN->ProtoSocket;
        addr = (struct sockaddr *)&peer->ProtoAddr;
    }

    status = sendto(socket_handle, msg_buf, msg_size,
                   0, addr, sizeof(struct sockaddr_in));

    if (status == -1) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_PROTO_SEND_ERR_EID,
                 "Error sending %s to %s stat=%d",
                 SBN_GetMsgName(type), peer->Name, status);
        return SBN_ERROR;
    }

    return SBN_OK;
}

int SBN_GetPeerIdxFromProtoMessage(sbn_t* SBN, const char* tag, SBN_NetCommonMsg_t *msg)
{
    int index;

    if (SBN == NULL) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_NULL_POINTER_EID,
                "SBN is NULL");
        return -1;
    }

    if (msg == NULL) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_NULL_POINTER_EID, "%s: msg is NULL", tag);
        return -1;
    }

    index = SBN_FindPeerByName(SBN, msg->Hdr.SrcCpuName);

    if (index == -1) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID, "%s: No peer found", tag);
        return -1;
    }
    
    if (index == SBN->SelfIndex) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID, "%s: won't handle message from self", tag);
        return -1;
    }

    return index;
}

sbn_status_t SBN_HandleAnnounce(sbn_t* SBN, SBN_NetCommonMsg_t *msg)
{
    sbn_status_t ret;
    int index = SBN_GetPeerIdxFromProtoMessage(SBN, G2_FUNCTION_NAME, msg);
    if (index == -1) {
        return SBN_ERROR;
    }

    SBN_Log(SBN_MODULE, SBN, SBN_PROTODBG_LEVEL, SBN_PROTO_MSG_EID, "ANNOUNCE received from peer=%d", index);
    ret = SBN_SendNetworkMsg(SBN, index, SBN_ANNOUNCE_ACK_MSG, 0, 0);
    if (ret == SBN_OK) {
        SBN_Log(SBN_MODULE, SBN, SBN_PROTODBG_LEVEL, SBN_PROTO_MSG_EID,
                "ANNOUNCE_ACK sent to peer=%d", index);
    }
    ret = SBN_SendAllSubscribeToRemote(SBN, index);
    if (ret == SBN_OK) {
        SBN_Log(SBN_MODULE, SBN, SBN_PROTODBG_LEVEL, SBN_PROTO_MSG_EID,
                "subscriptions sent to peer=%d", index);
    }

    return ret;
}

sbn_status_t SBN_HandleAnnounceAck(sbn_t* SBN, SBN_NetCommonMsg_t *msg)
{
    int index = SBN_GetPeerIdxFromProtoMessage(SBN, G2_FUNCTION_NAME, msg);
    if (index == -1) {
        return SBN_ERROR;
    }
    
    SBN->Peer[index].AnnounceAckReceived = true;
    SBN_Log(SBN_MODULE, SBN, SBN_PROTODBG_LEVEL, SBN_PROTO_MSG_EID, "ANNOUNCE_ACK received from peer=%d", index);

    return SBN_OK;
}

sbn_status_t SBN_HandleHeartbeat(sbn_t* SBN, SBN_NetCommonMsg_t *msg)
{
    sbn_status_t ret;
    int index = SBN_GetPeerIdxFromProtoMessage(SBN, G2_FUNCTION_NAME, msg);
    if (index == -1) {
        return SBN_ERROR;
    }

    SBN->Peer[index].HeartbeatAckReceived = true;
    SBN_Log(SBN_MODULE, SBN, SBN_PROTODBG_LEVEL, SBN_PROTO_MSG_EID, "HEARTBEAT received from peer=%d", index);

    ret = SBN_SendNetworkMsg(SBN, index, SBN_HEARTBEAT_ACK_MSG, 0, 0);
    if (ret == SBN_OK) {
        SBN_Log(SBN_MODULE, SBN, SBN_PROTODBG_LEVEL, SBN_PROTO_MSG_EID, "HEARTBEAT_ACK sent to peer=%d", index);
    }
    
    return ret;
}

sbn_status_t SBN_HandleHeartbeatAck(sbn_t* SBN, SBN_NetCommonMsg_t *msg)
{
    int index = SBN_GetPeerIdxFromProtoMessage(SBN, G2_FUNCTION_NAME, msg);
    if (index == -1) {
        return SBN_ERROR;
    }

    SBN->Peer[index].HeartbeatAckReceived = true;
    SBN_Log(SBN_MODULE, SBN, SBN_PROTODBG_LEVEL, SBN_PROTO_MSG_EID, "HEARTBEAT_ACK received from peer=%d", index);
    return SBN_OK;
}

sbn_status_t SBN_HandleAppMsg(sbn_t* SBN, unsigned char *buf, int size)
{
    if (SBN == NULL) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_NULL_POINTER_EID,
                "SBN is NULL");
        return SBN_ERROR;
    }

    if (buf == NULL) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_NULL_POINTER_EID,
                "buf is NULL");
        return SBN_ERROR;
    }

    if (size < (sizeof(SBN_NetMsgHeader_t) + sizeof(CCSDS_PriHdr_t))) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID,
                "message size is %d, which is smaller than min %ld", size,
                (sizeof(SBN_NetMsgHeader_t) + sizeof(CCSDS_PriHdr_t)));
        return SBN_ERROR;
    }

    if (SBN->AppMsgCallback) {
        CCSDS_PriHdr_t *primary =
            (CCSDS_PriHdr_t*)(buf + sizeof(SBN_NetMsgHeader_t));
        SBN->AppMsgCallback(CCSDS_RD_SID(primary), primary,
                            size - sizeof(SBN_NetMsgHeader_t));
    }
    
    return SBN_OK;
}

ssize_t SBN_ReceiveFromSocket(sbn_t* SBN, int socket, unsigned char *buf, int size)
{
    ssize_t received = recvfrom(socket, buf, size, MSG_DONTWAIT, NULL, NULL);
    if (received > 0) {
        return received;
    } else if (received < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
        return 0;
    }

    SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID, "Error receiveing from socket: %s", strerror(errno));
    return -1;
}

/* Processes incoming service messages */
sbn_status_t SBN_ReceiveServiceMessages(sbn_t* SBN)
{
    ssize_t size;
    unsigned char msg_buf[SBN_MAX_MSG_SIZE];
    SBN_NetCommonMsg_t *msg = (SBN_NetCommonMsg_t *)msg_buf;

    if (SBN == NULL) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_NULL_POINTER_EID,
                "SBN is NULL");
        return SBN_ERROR;
    }

    while (1) {
        size = SBN_ReceiveFromSocket(SBN, SBN->ProtoSocket, msg_buf,
                                     sizeof(SBN_NetCommonMsg_t));

        if (size == 0) {
            return SBN_OK;
        }

        if (size == -1) {
            return SBN_ERROR;
        }

        if (size != sizeof(SBN_NetCommonMsg_t)) {
            return SBN_ERROR;
        }

        switch (msg->Hdr.Type) {
        case SBN_HEARTBEAT_MSG:
            SBN_HandleHeartbeat(SBN, msg);
            break;
        case SBN_HEARTBEAT_ACK_MSG:
            SBN_HandleHeartbeatAck(SBN, msg);
            break;
        case SBN_ANNOUNCE_MSG:
            SBN_HandleAnnounce(SBN, msg);
            break;
        case SBN_ANNOUNCE_ACK_MSG:
            SBN_HandleAnnounceAck(SBN, msg);
            break;
        }
    }

    return SBN_OK;
}

/* Processes incoming payload messages */
sbn_status_t SBN_ReceivePayloadMessages(sbn_t* SBN)
{
    ssize_t size;
    unsigned char msg_buf[SBN_MAX_MSG_SIZE];
    SBN_NetCommonMsg_t *msg = (SBN_NetCommonMsg_t *)msg_buf;

    while (1) {
        size = SBN_ReceiveFromSocket(SBN,
                                     SBN->DataSocket,msg_buf,SBN_MAX_MSG_SIZE);

        if (size == 0) {
            return SBN_OK;
        }

        if (size == -1) {
            return SBN_ERROR;
        }

        switch (msg->Hdr.Type) {
        case SBN_SUBSCRIBE_MSG:
            if (size != sizeof(SBN_NetSubscriptionMsg_t)) {
                return SBN_ERROR;
            }
            SBN_HandleSubscribe(SBN, (SBN_NetSubscriptionMsg_t*)msg);
            break;
        case SBN_UN_SUBSCRIBE_MSG:
            if (size != sizeof(SBN_NetSubscriptionMsg_t)) {
                return SBN_ERROR;
            }
            SBN_HandleUnsubscribe(SBN, (SBN_NetSubscriptionMsg_t*)msg);
            break;
        case SBN_APP_MSG:
            SBN_HandleAppMsg(SBN, msg_buf, size);
            break;
        default:
            SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID, "Unknown SBN message type");
            return SBN_ERROR;
        }
    }

    return SBN_OK;
}

sbn_status_t SBN_CheckInterval(sbn_t *SBN)
{
    struct timespec now;
    int wait_interval_ms = SBN->MainLoopDelay * SBN->TimeoutCycles;
    int time_elapsed_ns;
    
    if (clock_gettime(CLOCK_REALTIME, &now)) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID,
                "%s", strerror(errno));
        return SBN_ERROR;
    }

    time_elapsed_ns = (now.tv_sec - SBN->Timer.tv_sec) * 1000000000
            + now.tv_nsec - SBN->Timer.tv_nsec;

    if (time_elapsed_ns < wait_interval_ms * 1000000)
        return SBN_SKIP;

    SBN->Timer = now;

    return SBN_OK;
}

sbn_status_t SBN_Poll(sbn_t* SBN)
{
    int peer_idx;
    sbn_status_t ret;

    if (SBN_ReceiveServiceMessages(SBN) == SBN_ERROR) {
        return SBN_ERROR;
    }

    if (SBN_ReceivePayloadMessages(SBN) == SBN_ERROR) {
        return SBN_ERROR;
    }
    
    switch(SBN_CheckInterval(SBN)) {
        case SBN_ERROR: return SBN_ERROR;
        case SBN_SKIP: return SBN_OK;
    }

    SBN_Log(SBN_MODULE, SBN, SBN_PROTODBG_LEVEL, SBN_PROTO_MSG_EID, "Checking peers state");

    for (peer_idx = 0; peer_idx < SBN->PeerCount; peer_idx++) {
        SBN_PeerData_t* peer = &SBN->Peer[peer_idx];
            
        if (peer_idx == SBN->SelfIndex)
            continue;

        switch (peer->State) {
        case SBN_ANNOUNCING:
            if (peer->AnnounceAckReceived || peer->HeartbeatAckReceived) {
                /* The peer became up */
                SBN_Log(SBN_MODULE, SBN, SBN_INFO_LEVEL, SBN_PEER_ALIVE_EID,
                        "%s Alive, changing state to SBN_HEARTBEATING",
                        peer->Name);
                peer->State = SBN_HEARTBEATING;
                /* Reset flag until next heartbeat */
                peer->HeartbeatAckReceived = false;
                /* Send first heartbeat to the peer */
                ret = SBN_SendNetworkMsg(SBN, peer_idx, SBN_HEARTBEAT_MSG,0,0);
                if (ret != SBN_OK)
                    continue;
                SBN_Log(SBN_MODULE, SBN, SBN_PROTODBG_LEVEL, SBN_PROTO_MSG_EID,
                        "HEARTBEAT sent to peer=%d", peer_idx);
                /* Send all cached subscrpition requests */
                ret = SBN_SendAllSubscribeToRemote(SBN, peer_idx);
                if (ret != SBN_OK)
                    continue;
             } else {
                ret = SBN_SendNetworkMsg(SBN, peer_idx, SBN_ANNOUNCE_MSG, 0, 0);
                if (ret != SBN_OK)
                    continue;
                SBN_Log(SBN_MODULE, SBN, SBN_PROTODBG_LEVEL, SBN_PROTO_MSG_EID,
                        "ANNOUNCE sent to peer=%d", peer_idx);
             }
             break;
        case SBN_HEARTBEATING:
            if (peer->HeartbeatAckReceived) {
                peer->HeartbeatAckReceived = false;
                ret = SBN_SendNetworkMsg(SBN, peer_idx, SBN_HEARTBEAT_MSG,0,0);
                if (ret != SBN_OK)
                    continue;
                SBN_Log(SBN_MODULE, SBN, SBN_PROTODBG_LEVEL, SBN_PROTO_MSG_EID,
                        "HEARTBEAT sent to peer=%d", peer_idx);
            } else {
                /* The peer became down */
                SBN_Log(SBN_MODULE, SBN, SBN_INFO_LEVEL, SBN_HB_LOST_EID,
                        "%s Heartbeat lost, changing state to SBN_ANNOUNCING",
                        peer->Name);
                peer->State = SBN_ANNOUNCING;
                /* Clear all inward subscriptions from the peer */
                SBN_Log(SBN_MODULE, SBN, SBN_INFO_LEVEL, SBN_UNSUB_CNT_EID,
                        "UnSubscribed %d MsgIds from %s",
                        peer->SubscriptionCount, peer->Name);
                peer->SubscriptionCount = 0;
                /* Reset flag until next announce */
                peer->AnnounceAckReceived = false;
                /* Send announce to the peer */
                ret = SBN_SendNetworkMsg(SBN, peer_idx, SBN_ANNOUNCE_MSG, 0, 0);
                if (ret != SBN_OK)
                    continue;
                SBN_Log(SBN_MODULE, SBN, SBN_PROTODBG_LEVEL, SBN_PROTO_MSG_EID,
                        "ANNOUNCE sent to peer=%d", peer_idx);
            }
            break;
        default:
            SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_STATE_ERR_EID,
                    "Unexpected state(%d) in SBN_RunProtocol for %s",
                    peer->State, peer->Name);
        }
    }

    return SBN_OK;
}

sbn_status_t SBN_HandleSubscribe(sbn_t* SBN, SBN_NetSubscriptionMsg_t *msg)
{
    SBN_SubscriptionCacheEntry_t *entry;
    int peer_idx = SBN_GetPeerIdxFromProtoMessage(SBN, G2_FUNCTION_NAME, (SBN_NetCommonMsg_t*)msg);

    SBN_Log(SBN_MODULE, SBN, SBN_DEBUG_LEVEL, SBN_PAYLOAD_MSG_EID, "SUBSCRIBE from remote peer received: msg_id=0x%x", msg->payload.MsgId);
    if (peer_idx == -1) {
        return SBN_ERROR;
    }

    entry = SBN_FindSubscriptionFromRemote(
                                          SBN, peer_idx, msg->payload.MsgId);
    if (entry) {
        entry->RefCounter++;
        SBN_Log(SBN_MODULE, SBN, SBN_DEBUG_LEVEL, SBN_PAYLOAD_MSG_EID, "Subscription from remote repeated: count=%d", entry->RefCounter);
        return SBN_OK;
    }

    entry = SBN_AddSubscriptionFromRemote(SBN, peer_idx, &msg->payload);
    if (!entry)
        return SBN_ERROR;

    return SBN_OK;
}

sbn_status_t SBN_HandleUnsubscribe(sbn_t* SBN, SBN_NetSubscriptionMsg_t *msg)
{
    int peer_idx;
    SBN_Log(SBN_MODULE, SBN, SBN_DEBUG_LEVEL, SBN_PAYLOAD_MSG_EID, "UNSUBSCRIBE from remote peer received: msg_id=0x%x", msg->payload.MsgId);

    peer_idx = SBN_GetPeerIdxFromProtoMessage(SBN, G2_FUNCTION_NAME, (SBN_NetCommonMsg_t*)msg);
    if (peer_idx == -1) {
        return SBN_ERROR;
    }

    SBN_SubscriptionCacheEntry_t *entry = SBN_FindSubscriptionFromRemote(
                                        SBN, peer_idx, msg->payload.MsgId);
    if (!entry) {
        SBN_Log(SBN_MODULE, SBN, SBN_DEBUG_LEVEL, SBN_PAYLOAD_MSG_EID, "Unpaired unsibscribe request received: msg_id=0x%x", msg->payload.MsgId);
        return SBN_OK;
    }

    entry->RefCounter--;

    if (entry->RefCounter > 0) {
        return SBN_OK;
    }

    if (SBN_RemoveSubscriptionFromRemote(SBN, peer_idx, msg->payload.MsgId) != SBN_OK)
        return SBN_ERROR;

    return SBN_OK;
}

sbn_status_t SBN_SendSubscribeMsg(sbn_t* SBN, int peer_idx,
                  SBN_NetSubscriptionPayload_t *payload, bool subscribe)
{
    sbn_msg_type_t type;

    if (peer_idx == SBN->SelfIndex)
        return SBN_OK;

    if (SBN->Peer[peer_idx].State != SBN_HEARTBEATING)
        return SBN_OK;

    if (subscribe) {
        type = SBN_SUBSCRIBE_MSG;
        SBN_Log(SBN_MODULE, SBN, SBN_DEBUG_LEVEL, SBN_PAYLOAD_MSG_EID, "Sending Subscribe msg to peer=%d", peer_idx);
    } else {
        type = SBN_UN_SUBSCRIBE_MSG;
        SBN_Log(SBN_MODULE, SBN, SBN_DEBUG_LEVEL, SBN_PAYLOAD_MSG_EID, "Sending Unsubscribe msg to peer=%d", peer_idx);
    }

    return SBN_SendNetworkMsg(SBN, peer_idx, type,
                       payload, sizeof(SBN_NetSubscriptionPayload_t));
}

sbn_status_t SBN_SendAllSubscribeToRemote(sbn_t* SBN, int peer_idx)
{
    int i = 0;
    for (i = 0; i < SBN->SubscriptionCount; i++) {
        if (SBN_SendSubscribeMsg(SBN, peer_idx,
                &SBN->SubscriptionCache[i].payload, true) != SBN_OK) {
            return SBN_ERROR;
        }
    }
}

SBN_SubscriptionCacheEntry_t *SBN_FindSubscriptionToRemote(sbn_t* SBN, uint16_t msg_id)
{
    int i = 0;
    for (i = 0; i < SBN->SubscriptionCount; i++) {
        if (SBN->SubscriptionCache[i].payload.MsgId == msg_id)
            return &SBN->SubscriptionCache[i];
    }

    return 0;
}

SBN_SubscriptionCacheEntry_t *SBN_AddSubscriptionToRemote(sbn_t* SBN, uint16_t msg_id)
{
    int insertIdx;
    if (SBN->SubscriptionCount >= SBN_MAX_SUBSCRIPTIONS_COUNT) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_SUB_ERR_EID,
                 "Cannot process subscription to msgId %d - max(%d) met.",
                 msg_id, SBN_MAX_SUBSCRIPTIONS_COUNT);
        return 0;
    }

    insertIdx = SBN->SubscriptionCount;
    ++SBN->SubscriptionCount;

    SBN->SubscriptionCache[insertIdx].RefCounter = 1;
    SBN->SubscriptionCache[insertIdx].payload.MsgId = msg_id;
    SBN->SubscriptionCache[insertIdx].payload.Qos = defaultQoS;

    return &(SBN->SubscriptionCache[insertIdx]);
}

sbn_status_t SBN_RemoveSubscriptionToRemote(sbn_t* SBN, uint16_t msg_id)
{
    bool removed = false;
    int i = 0;
    for (i = 0; i < SBN->SubscriptionCount; i++) {
        if (SBN->SubscriptionCache[i].payload.MsgId == msg_id) {
            if (i < SBN->SubscriptionCount - 1) {
                memcpy(&SBN->SubscriptionCache[i], &SBN->SubscriptionCache[i+1],
                    sizeof(SBN_SubscriptionCacheEntry_t) * (SBN->SubscriptionCount - 1 - i));
            }
            removed = true;
            break;
        }
    }

    if (!removed)
        return SBN_ERROR;

    --SBN->SubscriptionCount;

    return SBN_OK;
}

sbn_status_t SBN_Subscribe(sbn_t* SBN, uint16_t msg_id)
{
    int peer_idx = 0;
    SBN_SubscriptionCacheEntry_t *entry = SBN_FindSubscriptionToRemote(SBN, msg_id);
    if (entry) {
        SBN_Log(SBN_MODULE, SBN, SBN_DEBUG_LEVEL, SBN_PAYLOAD_MSG_EID, "Subscription exists: msg_id=%d", msg_id);
        entry->RefCounter++;
        return SBN_OK;
    }

    entry = SBN_AddSubscriptionToRemote(SBN, msg_id);
    if (!entry)
        return SBN_ERROR;

    SBN_Log(SBN_MODULE, SBN, SBN_DEBUG_LEVEL, SBN_PAYLOAD_MSG_EID, "Subscription added: msg_id=%d", msg_id);

    for (peer_idx = 0; peer_idx < SBN->PeerCount; peer_idx++) {
        SBN_SendSubscribeMsg(SBN, peer_idx, &(entry->payload), true);
    }

    return SBN_OK;
}

sbn_status_t SBN_Unsubscribe(sbn_t* SBN, uint16_t msg_id)
{
    int peer_idx = 0;
    SBN_SubscriptionCacheEntry_t *entry = SBN_FindSubscriptionToRemote(SBN, msg_id);
    if (!entry) {
        SBN_Log(SBN_MODULE, SBN, SBN_DEBUG_LEVEL, SBN_PAYLOAD_MSG_EID, "Unpaired unsubscribing request to msg_id=%d", msg_id);
        return SBN_OK;
    }

    entry->RefCounter--;

    if (entry->RefCounter > 0)
        return SBN_OK;

    SBN_Log(SBN_MODULE, SBN, SBN_DEBUG_LEVEL, SBN_PAYLOAD_MSG_EID, "Unsubscribing to msg_id=%d", msg_id);

    if (SBN_RemoveSubscriptionToRemote(SBN, msg_id) != SBN_OK)
        return SBN_ERROR;

    SBN_Log(SBN_MODULE, SBN, SBN_DEBUG_LEVEL, SBN_PAYLOAD_MSG_EID, "Subscription removed: msg_id=%d", msg_id);

    for (peer_idx = 0; peer_idx < SBN->PeerCount; peer_idx++) {
        SBN_SendSubscribeMsg(SBN, peer_idx, &(entry->payload), false);
    }

    return SBN_OK;
}

SBN_SubscriptionCacheEntry_t *SBN_FindSubscriptionFromRemote(sbn_t* SBN, int peer_idx, uint16_t msg_id)
{
    int i = 0;
    SBN_PeerData_t* peer = &SBN->Peer[peer_idx];
    int count = peer->SubscriptionCount;
    for (i = 0; i < count; i++) {
        if (peer->SubscriptionCache[i].payload.MsgId == msg_id)
            return &peer->SubscriptionCache[i];
    }

    return 0;
}

SBN_SubscriptionCacheEntry_t *SBN_AddSubscriptionFromRemote(sbn_t* SBN, int peer_idx,
                                  SBN_NetSubscriptionPayload_t *payload)
{
    int insert_idx;

    SBN_PeerData_t* peer = &SBN->Peer[peer_idx];
    
    if (peer->SubscriptionCount >= SBN_MAX_SUBSCRIPTIONS_COUNT) {
        SBN_Log(SBN_MODULE, SBN, SBN_ERROR_LEVEL, SBN_SUB_ERR_EID,
                 "Cannot process subscription from %s,max(%d)met.",
                 peer->Name, SBN_MAX_SUBSCRIPTIONS_COUNT);
        return 0;
    }

    insert_idx = peer->SubscriptionCount;
    ++peer->SubscriptionCount;

    peer->SubscriptionCache[insert_idx].RefCounter = 1;
    peer->SubscriptionCache[insert_idx].payload = *payload;
    SBN_Log(SBN_MODULE, SBN, SBN_DEBUG_LEVEL, SBN_PAYLOAD_MSG_EID, "Subscription from remote added: msg_id=0x%x", payload->MsgId);

    return &peer->SubscriptionCache[insert_idx];
}

sbn_status_t SBN_RemoveSubscriptionFromRemote(sbn_t* SBN, int peer_idx, uint16_t msg_id)
{
    int i = 0;
    bool removed = false;
    SBN_PeerData_t *peerData = &SBN->Peer[peer_idx];
    int count = peerData->SubscriptionCount;
    for (i = 0; i < count; i++) {
        if (peerData->SubscriptionCache[i].payload.MsgId == msg_id) {
            if (i < count - 1) {
                memcpy(&peerData->SubscriptionCache[i], &peerData->SubscriptionCache[i],
                       sizeof(SBN_SubscriptionCacheEntry_t) * (count - 1 - i));
            }
            removed = true;
            break;
        }
    }

    if (!removed)
        return SBN_ERROR;

    --peerData->SubscriptionCount;

    return SBN_OK;
}

sbn_status_t SBN_SendAppMessage(sbn_t* SBN, 
                                SBN_MsgId_t msg_id, uint16_t command,
                                void *payload, int payload_size)
{
    unsigned char msg_buf[SBN_MAX_MSG_SIZE];
    int msg_size = SBN_PrepareNetworkMsg(SBN, msg_buf, SBN_APP_MSG,
                                         msg_id, command,
                                         payload, payload_size);
    int socket_handle;
    int peer_idx, send_count = 0;
    struct sockaddr *addr;
    
    if (msg_size < (sizeof(SBN_NetMsgHeader_t) + sizeof(CCSDS_PriHdr_t))) {
        return SBN_ERROR;
    }

    socket_handle = SBN->DataSocket;

    for (peer_idx = 0; peer_idx < SBN->PeerCount; peer_idx++) {
        SBN_PeerData_t* peer = &SBN->Peer[peer_idx];
        
        if (peer_idx == SBN->SelfIndex)
            continue;

        if (peer->State == SBN_HEARTBEATING) {
            int i;
            bool subscribed = false;
            addr = (struct sockaddr *)&peer->DataAddr;
            int count = peer->SubscriptionCount;
            for (i = 0; i < count; i++) {
                if (peer->SubscriptionCache[i].payload.MsgId
                    == msg_id) {
                    subscribed = true;
                    break;
                }
            }
            if (subscribed) {
                if (sendto(socket_handle, msg_buf, msg_size,
                           0, addr, sizeof(struct sockaddr_in)) == -1) {
                    SBN_Log(SBN_MODULE,SBN,SBN_ERROR_LEVEL,SBN_MISC_ERROR_EID,
                            "%s", strerror(errno));
                    continue;
                }
                send_count++;
                SBN_Log(SBN_MODULE, SBN, SBN_PROTODBG_LEVEL, SBN_PROTO_MSG_EID,
                        "APP MSG sent to peer=%d", peer_idx);
            }
        }
    }

    return (send_count > 0) ? SBN_OK : SBN_SKIP;
}

uint16_t CCSDS_RD_BITS(uint16_t word, int mask, int shift)
{
    return (((word) & mask) >> shift);
}

void CCSDS_WR_BITS(uint16_t *word, int mask, int shift, uint16_t value)
{
    (*word) = (uint16_t)(((*word) & ~mask) | (((value) & (mask >> shift)) << shift));
}

void CCSDS_CLR_PRI_HDR(CCSDS_PriHdr_t *phdr)
{
    phdr->StreamId[0] = 0;
    phdr->StreamId[1] = 0;
    phdr->Sequence[0] = (CCSDS_INIT_SEQFLG << 6);
    phdr->Sequence[1] = 0;
    phdr->Length[0] = 0;
    phdr->Length[1] = 0;
}

/* Read entire stream ID from primary header. */
uint16_t CCSDS_RD_SID(CCSDS_PriHdr_t *phdr)
{
    return ((phdr->StreamId[0] << 8) + (phdr->StreamId[1]));
}
/* Write entire stream ID to primary header. */
void CCSDS_WR_SID(CCSDS_PriHdr_t *phdr, uint16_t value)
{
    phdr->StreamId[0] = (value >> 8);
    phdr->StreamId[1] = (value & 0xff);
}

/* Read secondary header flag from primary header. */
uint16_t CCSDS_RD_SHDR(CCSDS_PriHdr_t *phdr)
{
    return ((phdr->StreamId[0] & 0x08) >> 3);
}
/* Write secondary header flag to primary header. */
void CCSDS_WR_SHDR(CCSDS_PriHdr_t *phdr, uint16_t value)
{
    phdr->StreamId[0] = (phdr->StreamId[0] & 0xf7) | ((value << 3) & 0x08);
}

/* Read packet type (0=TLM,1=CMD) from primary header. */
uint16_t CCSDS_RD_TYPE(CCSDS_PriHdr_t *phdr)
{
    return ((phdr->StreamId[0] & 0x10) >> 4);
}
/* Write packet type (0=TLM,1=CMD) to primary header. */
void CCSDS_WR_TYPE(CCSDS_PriHdr_t *phdr, uint16_t value)
{
    phdr->StreamId[0] = (phdr->StreamId[0] & 0xEF) | ((value << 4) & 0x10);
}

/* Read CCSDS version from primary header. */
uint16_t CCSDS_RD_VERS(CCSDS_PriHdr_t *phdr)
{
    return ((phdr->StreamId[0] & 0xE0) >> 5);
}
/* Write CCSDS version to primary header. */
void CCSDS_WR_VERS(CCSDS_PriHdr_t *phdr, uint16_t value)
{
    phdr->StreamId[0] = (phdr->StreamId[0] & 0x1F) | ((value << 5) & 0xE0);
}

/* Read sequence count from primary header. */
uint16_t CCSDS_RD_SEQ(CCSDS_PriHdr_t *phdr)
{
    return (((phdr->Sequence[0] & 0x3F) << 8) + (phdr->Sequence[1]));
}
/* Write sequence count to primary header. */
void CCSDS_WR_SEQ(CCSDS_PriHdr_t *phdr, uint16_t value)
{
    phdr->Sequence[0] = (phdr->Sequence[0] & 0xC0) | ((value >> 8) & 0x3f); 
    phdr->Sequence[1]  = ((value)) & 0xff;
}

/* Read sequence flags from primary header. */
uint16_t CCSDS_RD_SEQFLG(CCSDS_PriHdr_t *phdr)
{
    return ((phdr->Sequence[0] & 0xC0) >> 6);
}
/* Write sequence flags to primary header. */
void CCSDS_WR_SEQFLG(CCSDS_PriHdr_t *phdr, uint16_t value)
{
    phdr->Sequence[0] = (phdr->Sequence[0] & 0x3F) | ((value << 6) & 0xC0);
}

/* Read total packet length from primary header. */
uint16_t CCSDS_RD_LEN(CCSDS_PriHdr_t *phdr)
{
    return ( ( phdr->Length[0] << 8) + phdr->Length[1] + 7);
}
/* Write total packet length to primary header. */
void CCSDS_WR_LEN(CCSDS_PriHdr_t *phdr, uint16_t value)
{
    phdr->Length[0] = ((value) - 7) >> 8;
    phdr->Length[1] = ((value) - 7) & 0xff;
};

/* Read function code from command secondary header. */
uint16_t CCSDS_RD_FC(CCSDS_CmdSecHdr_t *shdr)
{
    return CCSDS_RD_BITS(shdr->Command, 0x7F00, 8);
}
/* Write function code to command secondary header. */
void CCSDS_WR_FC(CCSDS_CmdSecHdr_t *shdr, uint16_t value)
{
    CCSDS_WR_BITS(&shdr->Command, 0x7F00, 8, value);
}

/* Read checksum from command secondary header. */
uint16_t CCSDS_RD_CHECKSUM(CCSDS_CmdSecHdr_t *shdr)
{
    return CCSDS_RD_BITS(shdr->Command, 0x00FF, 0);
}
/* Write checksum to command secondary header. */
void CCSDS_WR_CHECKSUM(CCSDS_CmdSecHdr_t *shdr, uint16_t val)
{
    CCSDS_WR_BITS(&shdr->Command, 0x00FF, 0, val);
}
    
char *SBN_GetMsgName(sbn_msg_type_t MsgType)
{
    switch (MsgType)
    {
        case SBN_ANNOUNCE_MSG:
            return "Announce";
            break;
        case SBN_ANNOUNCE_ACK_MSG:
            return "Announce Ack";
            break;
        case SBN_HEARTBEAT_MSG:
            return "Heartbeat";
            break;
        case SBN_HEARTBEAT_ACK_MSG:
            return "Heartbeat Ack";
            break;
        case SBN_SUBSCRIBE_MSG:
            return "Subscribe";
            break;
        case SBN_UN_SUBSCRIBE_MSG:
            return "UnSubscribe";
            break;
        case SBN_APP_MSG:
            return "App Msg";
            break;
        default:
            return "Unknown";
            break;
    }
}
