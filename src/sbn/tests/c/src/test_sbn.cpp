#define CATCH_CONFIG_MAIN   //use main of catch framework
#define CATCH_CONFIG_NO_CPP11 //use catch without cpp 11

#include "catch.hpp"

extern "C" {
#include "sbn.h"
}

TEST_CASE("SBN_ParseFileEntry")
{
    sbn_t SBN;

    REQUIRE(SBN_ParseFileEntry(0, "CPU1", "CPU1 1 1 127.0.0.1 15821 5821")
	    == SBN_ERROR);
    REQUIRE(SBN_ParseFileEntry(&SBN, "CPU1", "CPU1 1 1 127.0.0.1 15821 5821")
            == SBN_OK);
    REQUIRE(SBN.SelfIndex == 0);

    std::string buf = "";
    for (int i = 0; i < SBN_MAX_PEERNAME_LENGTH + 1; i++) {
        buf += "a";
    }
    buf += " 1 1 127.0.0.1 15821 5821";
    REQUIRE(SBN_ParseFileEntry(&SBN, "CPU1", buf.c_str()) == SBN_ERROR);

    REQUIRE(SBN_ParseFileEntry(&SBN, "CPU1", "CPU1 1 1 ABC 15821 5821")
            == SBN_ERROR);
    REQUIRE(SBN_ParseFileEntry(&SBN, "CPU1", "CPU1") == SBN_ERROR);
    REQUIRE(SBN_ParseFileEntry(&SBN, 0, "CPU1 1 1 127.0 15821 5821") == SBN_OK);
    REQUIRE(SBN_ParseFileEntry(&SBN, 0, 0) == SBN_ERROR);
}

TEST_CASE("SBN_Poll")
{
    sbn_t SBN;
    REQUIRE(SBN_Init(0, 0, 0, 0) == SBN_ERROR);
    REQUIRE(SBN_Init(&SBN, 0, 0, 0) == SBN_OK);
    REQUIRE(SBN.PeerCount == 2);
    REQUIRE(SBN.SelfIndex == 1);
    REQUIRE(SBN.Peer[0].State == SBN_ANNOUNCING);
    REQUIRE(SBN.Peer[0].AnnounceAckReceived == false);
    REQUIRE(SBN.Peer[0].HeartbeatAckReceived == false);
    REQUIRE(SBN_FindPeerByName(&SBN, "CPU1") == 0);
    REQUIRE(SBN_FindPeerByName(&SBN, "KPU0") == -1);
    REQUIRE(SBN_FindPeerByName(&SBN, 0) == -1);
    REQUIRE(SBN_FindPeerByName(0, 0) == -1);
    REQUIRE(SBN_Poll(0) == SBN_ERROR);
    REQUIRE(SBN_Poll(&SBN) == SBN_OK); // send ANNOUNCE
    for (int i = 0; i < 100; i++) {
        usleep(SBN.MainLoopDelay * SBN.TimeoutCycles * 1000);
        SBN_Poll(&SBN); // receive HEARTBEAT
        if (SBN.Peer[0].State == SBN_HEARTBEATING) {
            break;
        }
    }
    REQUIRE(SBN.Peer[0].AnnounceAckReceived == true);
    SBN.Peer[0].SubscriptionCount = 2; // to simulate subscriptions
    SBN.MainLoopDelay = 0; // to simulate peer death
    SBN_Poll(&SBN); // fail to receive HEARTBEAT
    REQUIRE(SBN.Peer[0].HeartbeatAckReceived == false);
    REQUIRE(SBN.Peer[0].SubscriptionCount == 0);
    REQUIRE(SBN.Peer[0].State == SBN_ANNOUNCING);
    REQUIRE(SBN_Close(0) == SBN_ERROR);
    REQUIRE(SBN_Close(&SBN) == SBN_OK);
}

TEST_CASE("CCSDS")
{
    REQUIRE(CCSDS_Header_Size(SBN_ANNOUNCE_MSG, 1) == 0);
    REQUIRE(CCSDS_Header_Size(SBN_APP_MSG, 0x1801) ==
	    sizeof(CCSDS_CmdPkt_t));
}

TEST_CASE("AppMsg")
{
    sbn_t SBN;
    REQUIRE(SBN_Init(&SBN, 0, 0, 0) == SBN_OK);
    for (int i = 0; i < 100; i++) {
        usleep(SBN.MainLoopDelay * SBN.TimeoutCycles * 1000);
        SBN_Poll(&SBN); // receive HEARTBEAT
        if (SBN.Peer[0].State == SBN_HEARTBEATING) {
            break;
        }
    }
    SBN_NetSubscriptionPayload_t payload;
    payload.MsgId = 0x1882;
    REQUIRE(SBN_AddSubscriptionFromRemote(&SBN, 0, &payload) != 0);
    REQUIRE(SBN.Peer[0].SubscriptionCount > 0);
    REQUIRE(SBN_SendAppMessage(&SBN, payload.MsgId, 1, 0, 0) == SBN_OK);
    REQUIRE(SBN_Close(&SBN) == SBN_OK);
}

