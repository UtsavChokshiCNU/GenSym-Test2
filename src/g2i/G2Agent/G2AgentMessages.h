//+----------------------------------------------------------------------------
//
//  Copyright (C) 1986-2017 Gensym Corporation.
//
//  File:      G2AgentMessages.mc 
//
//  Contents:  Events and Errors for G2 Agent
//
//-----------------------------------------------------------------------------
//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: G2_BAD_OPERATION
//
// MessageText:
//
//  Incorrect operation or command.
//
#define G2_BAD_OPERATION                 0xC0000001L

//
// MessageId: G2_SYSTEM_ERROR
//
// MessageText:
//
//  G2 Error: %1. Description: %2
//
#define G2_SYSTEM_ERROR                  0xC0000002L

//
// MessageId: G2_ERROR
//
// MessageText:
//
//  %1
//
#define G2_ERROR                         0xC0020003L

//
// MessageId: G2_WARNING
//
// MessageText:
//
//  %1
//
#define G2_WARNING                       0x80020004L

//
// MessageId: G2_INFORMATION
//
// MessageText:
//
//  %1
//
#define G2_INFORMATION                   0x40020005L

