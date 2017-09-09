

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon Jul 30 17:05:01 2012
 */
/* Compiler settings for ..\..\activex\G2Com\G2Com.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "G2Com.h"

#define TYPE_FORMAT_STRING_SIZE   1219                              
#define PROC_FORMAT_STRING_SIZE   4459                              
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   3            

typedef struct _G2Com_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } G2Com_MIDL_TYPE_FORMAT_STRING;

typedef struct _G2Com_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } G2Com_MIDL_PROC_FORMAT_STRING;

typedef struct _G2Com_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } G2Com_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const G2Com_MIDL_TYPE_FORMAT_STRING G2Com__MIDL_TypeFormatString;
extern const G2Com_MIDL_PROC_FORMAT_STRING G2Com__MIDL_ProcFormatString;
extern const G2Com_MIDL_EXPR_FORMAT_STRING G2Com__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2Gateway_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2Gateway_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2Gateway2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2Gateway2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2Gateway3_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2Gateway3_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2Gateway4_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2Gateway4_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO G2ComObject_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO G2ComObject_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2StructureEntry_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2StructureEntry_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2Structure_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2Structure_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2Item_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2Item_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2Item2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2Item2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2Item3_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2Item3_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2Item4_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2Item4_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2Attribute_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2Attribute_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2ListOrArray_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2ListOrArray_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2LAElement_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2LAElement_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2Symbol_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2Symbol_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2ItemRef_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2ItemRef_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2Workspace_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2Workspace_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2Window_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2Window_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IG2ComConfigurator_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IG2ComConfigurator_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const G2Com_MIDL_PROC_FORMAT_STRING G2Com__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure Connect */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x6 ),	/* 6 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter WaitFlag */

/* 24 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 30 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Disconnect */

/* 36 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 38 */	NdrFcLong( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0x8 ),	/* 8 */
/* 44 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 46 */	NdrFcShort( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0x8 ),	/* 8 */
/* 50 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 52 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 60 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 62 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 64 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Call */

/* 66 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 68 */	NdrFcLong( 0x0 ),	/* 0 */
/* 72 */	NdrFcShort( 0x9 ),	/* 9 */
/* 74 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 76 */	NdrFcShort( 0x0 ),	/* 0 */
/* 78 */	NdrFcShort( 0x8 ),	/* 8 */
/* 80 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 82 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 84 */	NdrFcShort( 0x1 ),	/* 1 */
/* 86 */	NdrFcShort( 0x1 ),	/* 1 */
/* 88 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ProcedureName */

/* 90 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 92 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 94 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Parameter InputArguments */

/* 96 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 98 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 100 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Parameter ReturnArguments */

/* 102 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 104 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 106 */	NdrFcShort( 0x42c ),	/* Type Offset=1068 */

	/* Return value */

/* 108 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 110 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 112 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CallDeferred */

/* 114 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 116 */	NdrFcLong( 0x0 ),	/* 0 */
/* 120 */	NdrFcShort( 0xa ),	/* 10 */
/* 122 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 126 */	NdrFcShort( 0x8 ),	/* 8 */
/* 128 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 130 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 134 */	NdrFcShort( 0x1 ),	/* 1 */
/* 136 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ProcedureName */

/* 138 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 140 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 142 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Parameter DeferredCallIdentifier */

/* 144 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 146 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 148 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Parameter InputArguments */

/* 150 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 152 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 154 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 156 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 158 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 160 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Start */

/* 162 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 164 */	NdrFcLong( 0x0 ),	/* 0 */
/* 168 */	NdrFcShort( 0xb ),	/* 11 */
/* 170 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 172 */	NdrFcShort( 0x0 ),	/* 0 */
/* 174 */	NdrFcShort( 0x8 ),	/* 8 */
/* 176 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 178 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 180 */	NdrFcShort( 0x0 ),	/* 0 */
/* 182 */	NdrFcShort( 0x1 ),	/* 1 */
/* 184 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ProcedureName */

/* 186 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 188 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 190 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Parameter Arguments */

/* 192 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 194 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 196 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 198 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 200 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 202 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetNamedObject */

/* 204 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 206 */	NdrFcLong( 0x0 ),	/* 0 */
/* 210 */	NdrFcShort( 0xc ),	/* 12 */
/* 212 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 216 */	NdrFcShort( 0x8 ),	/* 8 */
/* 218 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 220 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 222 */	NdrFcShort( 0x0 ),	/* 0 */
/* 224 */	NdrFcShort( 0x1 ),	/* 1 */
/* 226 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ObjectName */

/* 228 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 230 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 232 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Parameter ObjectClass */

/* 234 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 236 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 238 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Parameter Obj */

/* 240 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 242 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 244 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Return value */

/* 246 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 248 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 250 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateObjectInstance */

/* 252 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 254 */	NdrFcLong( 0x0 ),	/* 0 */
/* 258 */	NdrFcShort( 0xd ),	/* 13 */
/* 260 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 262 */	NdrFcShort( 0x0 ),	/* 0 */
/* 264 */	NdrFcShort( 0x8 ),	/* 8 */
/* 266 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 268 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 272 */	NdrFcShort( 0x1 ),	/* 1 */
/* 274 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ClassName */

/* 276 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 278 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 280 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Parameter Obj */

/* 282 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 284 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 286 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Return value */

/* 288 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 290 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 292 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_IsG2Connected */

/* 294 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 296 */	NdrFcLong( 0x0 ),	/* 0 */
/* 300 */	NdrFcShort( 0xe ),	/* 14 */
/* 302 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 304 */	NdrFcShort( 0x0 ),	/* 0 */
/* 306 */	NdrFcShort( 0x22 ),	/* 34 */
/* 308 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 310 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 312 */	NdrFcShort( 0x0 ),	/* 0 */
/* 314 */	NdrFcShort( 0x0 ),	/* 0 */
/* 316 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Val */

/* 318 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 320 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 322 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 324 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 326 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 328 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_IsG2Running */

/* 330 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 332 */	NdrFcLong( 0x0 ),	/* 0 */
/* 336 */	NdrFcShort( 0xf ),	/* 15 */
/* 338 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 340 */	NdrFcShort( 0x0 ),	/* 0 */
/* 342 */	NdrFcShort( 0x22 ),	/* 34 */
/* 344 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 346 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 348 */	NdrFcShort( 0x0 ),	/* 0 */
/* 350 */	NdrFcShort( 0x0 ),	/* 0 */
/* 352 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Val */

/* 354 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 356 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 358 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 360 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 362 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 364 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_G2Location */

/* 366 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 368 */	NdrFcLong( 0x0 ),	/* 0 */
/* 372 */	NdrFcShort( 0x10 ),	/* 16 */
/* 374 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 376 */	NdrFcShort( 0x0 ),	/* 0 */
/* 378 */	NdrFcShort( 0x8 ),	/* 8 */
/* 380 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 382 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 384 */	NdrFcShort( 0x1 ),	/* 1 */
/* 386 */	NdrFcShort( 0x0 ),	/* 0 */
/* 388 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Location */

/* 390 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 392 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 394 */	NdrFcShort( 0x458 ),	/* Type Offset=1112 */

	/* Return value */

/* 396 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 398 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 400 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_G2Location */

/* 402 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 404 */	NdrFcLong( 0x0 ),	/* 0 */
/* 408 */	NdrFcShort( 0x11 ),	/* 17 */
/* 410 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 412 */	NdrFcShort( 0x0 ),	/* 0 */
/* 414 */	NdrFcShort( 0x8 ),	/* 8 */
/* 416 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 418 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 420 */	NdrFcShort( 0x0 ),	/* 0 */
/* 422 */	NdrFcShort( 0x1 ),	/* 1 */
/* 424 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Location */

/* 426 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 428 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 430 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 432 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 434 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 436 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_InterfaceClass */

/* 438 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 440 */	NdrFcLong( 0x0 ),	/* 0 */
/* 444 */	NdrFcShort( 0x12 ),	/* 18 */
/* 446 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 448 */	NdrFcShort( 0x0 ),	/* 0 */
/* 450 */	NdrFcShort( 0x8 ),	/* 8 */
/* 452 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 454 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 456 */	NdrFcShort( 0x1 ),	/* 1 */
/* 458 */	NdrFcShort( 0x0 ),	/* 0 */
/* 460 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter InterfaceClassName */

/* 462 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 464 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 466 */	NdrFcShort( 0x458 ),	/* Type Offset=1112 */

	/* Return value */

/* 468 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 470 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 472 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_InterfaceClass */

/* 474 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 476 */	NdrFcLong( 0x0 ),	/* 0 */
/* 480 */	NdrFcShort( 0x13 ),	/* 19 */
/* 482 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 486 */	NdrFcShort( 0x8 ),	/* 8 */
/* 488 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 490 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 492 */	NdrFcShort( 0x0 ),	/* 0 */
/* 494 */	NdrFcShort( 0x1 ),	/* 1 */
/* 496 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter InterfaceClassName */

/* 498 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 500 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 502 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 504 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 506 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 508 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_RemoteInitializationString */

/* 510 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 512 */	NdrFcLong( 0x0 ),	/* 0 */
/* 516 */	NdrFcShort( 0x14 ),	/* 20 */
/* 518 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 522 */	NdrFcShort( 0x8 ),	/* 8 */
/* 524 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 526 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 528 */	NdrFcShort( 0x1 ),	/* 1 */
/* 530 */	NdrFcShort( 0x0 ),	/* 0 */
/* 532 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter InitializationString */

/* 534 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 536 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 538 */	NdrFcShort( 0x458 ),	/* Type Offset=1112 */

	/* Return value */

/* 540 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 542 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 544 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_RemoteInitializationString */

/* 546 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 548 */	NdrFcLong( 0x0 ),	/* 0 */
/* 552 */	NdrFcShort( 0x15 ),	/* 21 */
/* 554 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 556 */	NdrFcShort( 0x0 ),	/* 0 */
/* 558 */	NdrFcShort( 0x8 ),	/* 8 */
/* 560 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 562 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 564 */	NdrFcShort( 0x0 ),	/* 0 */
/* 566 */	NdrFcShort( 0x1 ),	/* 1 */
/* 568 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter InitializationString */

/* 570 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 572 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 574 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 576 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 578 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 580 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CallTimeout */

/* 582 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 584 */	NdrFcLong( 0x0 ),	/* 0 */
/* 588 */	NdrFcShort( 0x16 ),	/* 22 */
/* 590 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 594 */	NdrFcShort( 0x24 ),	/* 36 */
/* 596 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 598 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 602 */	NdrFcShort( 0x0 ),	/* 0 */
/* 604 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter MaxWait */

/* 606 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 608 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 610 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 612 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 614 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 616 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_CallTimeout */

/* 618 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 620 */	NdrFcLong( 0x0 ),	/* 0 */
/* 624 */	NdrFcShort( 0x17 ),	/* 23 */
/* 626 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 628 */	NdrFcShort( 0x8 ),	/* 8 */
/* 630 */	NdrFcShort( 0x8 ),	/* 8 */
/* 632 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 634 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 636 */	NdrFcShort( 0x0 ),	/* 0 */
/* 638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 640 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter MaxWait */

/* 642 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 644 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 646 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 648 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 650 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 652 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure _FireEvents */

/* 654 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 656 */	NdrFcLong( 0x0 ),	/* 0 */
/* 660 */	NdrFcShort( 0x18 ),	/* 24 */
/* 662 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 664 */	NdrFcShort( 0x0 ),	/* 0 */
/* 666 */	NdrFcShort( 0x8 ),	/* 8 */
/* 668 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 670 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 676 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 678 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 680 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 682 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PostMessage */

/* 684 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 686 */	NdrFcLong( 0x0 ),	/* 0 */
/* 690 */	NdrFcShort( 0x19 ),	/* 25 */
/* 692 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 696 */	NdrFcShort( 0x8 ),	/* 8 */
/* 698 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 700 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 704 */	NdrFcShort( 0x1 ),	/* 1 */
/* 706 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Message */

/* 708 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 710 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 712 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Return value */

/* 714 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 716 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 718 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OnStartPage */

/* 720 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 722 */	NdrFcLong( 0x0 ),	/* 0 */
/* 726 */	NdrFcShort( 0x1a ),	/* 26 */
/* 728 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 730 */	NdrFcShort( 0x0 ),	/* 0 */
/* 732 */	NdrFcShort( 0x8 ),	/* 8 */
/* 734 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 736 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 738 */	NdrFcShort( 0x0 ),	/* 0 */
/* 740 */	NdrFcShort( 0x0 ),	/* 0 */
/* 742 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter piUnk */

/* 744 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 746 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 748 */	NdrFcShort( 0xaa ),	/* Type Offset=170 */

	/* Return value */

/* 750 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 752 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 754 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OnEndPage */

/* 756 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 758 */	NdrFcLong( 0x0 ),	/* 0 */
/* 762 */	NdrFcShort( 0x1b ),	/* 27 */
/* 764 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 766 */	NdrFcShort( 0x0 ),	/* 0 */
/* 768 */	NdrFcShort( 0x8 ),	/* 8 */
/* 770 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 772 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 774 */	NdrFcShort( 0x0 ),	/* 0 */
/* 776 */	NdrFcShort( 0x0 ),	/* 0 */
/* 778 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 780 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 782 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 784 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MakeG2ComVariable */

/* 786 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 788 */	NdrFcLong( 0x0 ),	/* 0 */
/* 792 */	NdrFcShort( 0x1c ),	/* 28 */
/* 794 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 796 */	NdrFcShort( 0x6 ),	/* 6 */
/* 798 */	NdrFcShort( 0x8 ),	/* 8 */
/* 800 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 802 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 804 */	NdrFcShort( 0x1 ),	/* 1 */
/* 806 */	NdrFcShort( 0x1 ),	/* 1 */
/* 808 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ComType */

/* 810 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 812 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 814 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter inArgs */

/* 816 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 818 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 820 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Parameter pResult */

/* 822 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 824 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 826 */	NdrFcShort( 0x42c ),	/* Type Offset=1068 */

	/* Return value */

/* 828 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 830 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 832 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure DbgMsg */

/* 834 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 836 */	NdrFcLong( 0x0 ),	/* 0 */
/* 840 */	NdrFcShort( 0x1d ),	/* 29 */
/* 842 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 844 */	NdrFcShort( 0x0 ),	/* 0 */
/* 846 */	NdrFcShort( 0x8 ),	/* 8 */
/* 848 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 850 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 852 */	NdrFcShort( 0x0 ),	/* 0 */
/* 854 */	NdrFcShort( 0x1 ),	/* 1 */
/* 856 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter msg */

/* 858 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 860 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 862 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 864 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 866 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 868 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_G2RunState */

/* 870 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 872 */	NdrFcLong( 0x0 ),	/* 0 */
/* 876 */	NdrFcShort( 0x1e ),	/* 30 */
/* 878 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 880 */	NdrFcShort( 0x0 ),	/* 0 */
/* 882 */	NdrFcShort( 0x22 ),	/* 34 */
/* 884 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 886 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 888 */	NdrFcShort( 0x0 ),	/* 0 */
/* 890 */	NdrFcShort( 0x0 ),	/* 0 */
/* 892 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 894 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 896 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 898 */	NdrFcShort( 0x466 ),	/* Type Offset=1126 */

	/* Return value */

/* 900 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 902 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 904 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_TWHandle */

/* 906 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 908 */	NdrFcLong( 0x0 ),	/* 0 */
/* 912 */	NdrFcShort( 0x1f ),	/* 31 */
/* 914 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 916 */	NdrFcShort( 0x0 ),	/* 0 */
/* 918 */	NdrFcShort( 0x24 ),	/* 36 */
/* 920 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 922 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 924 */	NdrFcShort( 0x0 ),	/* 0 */
/* 926 */	NdrFcShort( 0x0 ),	/* 0 */
/* 928 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter plHWnd */

/* 930 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 932 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 934 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 936 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 938 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 940 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_TWHandle */

/* 942 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 944 */	NdrFcLong( 0x0 ),	/* 0 */
/* 948 */	NdrFcShort( 0x20 ),	/* 32 */
/* 950 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 952 */	NdrFcShort( 0x8 ),	/* 8 */
/* 954 */	NdrFcShort( 0x8 ),	/* 8 */
/* 956 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 958 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 960 */	NdrFcShort( 0x0 ),	/* 0 */
/* 962 */	NdrFcShort( 0x0 ),	/* 0 */
/* 964 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lHWnd */

/* 966 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 968 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 970 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 972 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 974 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 976 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ObtainTWLockIfUnused */

/* 978 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 980 */	NdrFcLong( 0x0 ),	/* 0 */
/* 984 */	NdrFcShort( 0x21 ),	/* 33 */
/* 986 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 988 */	NdrFcShort( 0x0 ),	/* 0 */
/* 990 */	NdrFcShort( 0x22 ),	/* 34 */
/* 992 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 994 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 996 */	NdrFcShort( 0x0 ),	/* 0 */
/* 998 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1000 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pResult */

/* 1002 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1004 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1006 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1008 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1010 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1012 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ClearTWLock */

/* 1014 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1016 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1020 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1022 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1024 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1026 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1028 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1030 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1032 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1034 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1036 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 1038 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1040 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1042 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_G2Symbols */

/* 1044 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1046 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1050 */	NdrFcShort( 0x23 ),	/* 35 */
/* 1052 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1054 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1056 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1058 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1060 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1062 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1064 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1066 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 1068 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1070 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1072 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1074 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1076 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1078 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_G2Symbols */

/* 1080 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1082 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1086 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1088 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1090 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1092 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1094 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1096 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1098 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1100 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1102 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 1104 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1106 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1108 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1110 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1112 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1114 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_DisconnectOnReset */

/* 1116 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1118 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1122 */	NdrFcShort( 0x25 ),	/* 37 */
/* 1124 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1128 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1130 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1132 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1138 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 1140 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1142 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1144 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1146 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1148 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1150 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_DisconnectOnReset */

/* 1152 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1154 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1158 */	NdrFcShort( 0x26 ),	/* 38 */
/* 1160 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1162 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1164 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1166 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1168 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1170 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1172 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1174 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 1176 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1178 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1180 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1182 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1184 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1186 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetContextLimit */

/* 1188 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1190 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1194 */	NdrFcShort( 0x27 ),	/* 39 */
/* 1196 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1198 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1200 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1202 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1204 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1206 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1208 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1210 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter limit */

/* 1212 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1214 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1216 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1218 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1220 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1222 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_WhatAmI */

/* 1224 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1226 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1230 */	NdrFcShort( 0x7 ),	/* 7 */
/* 1232 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1236 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1238 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1240 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1242 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1244 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1246 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 1248 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1250 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1252 */	NdrFcShort( 0x458 ),	/* Type Offset=1112 */

	/* Return value */

/* 1254 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1256 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1258 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Duplicate */

/* 1260 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1262 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1266 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1268 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1272 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1274 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1276 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1278 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1280 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1282 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pNewObj */

/* 1284 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1286 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1288 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 1290 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1292 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1294 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Item */


	/* Procedure get_Name */


	/* Procedure get_Name */

/* 1296 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1298 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1302 */	NdrFcShort( 0x9 ),	/* 9 */
/* 1304 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1306 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1308 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1310 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1312 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1314 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1316 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1318 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pName */


	/* Parameter pVal */

/* 1320 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1322 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1324 */	NdrFcShort( 0x458 ),	/* Type Offset=1112 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 1326 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1328 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1330 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Item */


	/* Procedure put_Name */

/* 1332 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1334 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1338 */	NdrFcShort( 0xa ),	/* 10 */
/* 1340 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1342 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1344 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1346 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1348 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1350 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1352 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1354 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 1356 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1358 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1360 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */


	/* Return value */

/* 1362 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1364 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1366 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Value */


	/* Procedure get_Value */

/* 1368 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1370 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1374 */	NdrFcShort( 0xb ),	/* 11 */
/* 1376 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1378 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1380 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1382 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1384 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1386 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1388 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1390 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 1392 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 1394 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1396 */	NdrFcShort( 0x42c ),	/* Type Offset=1068 */

	/* Return value */


	/* Return value */

/* 1398 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1400 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1402 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Value */

/* 1404 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1406 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1410 */	NdrFcShort( 0xc ),	/* 12 */
/* 1412 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1414 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1416 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1418 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1420 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1422 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1424 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1426 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 1428 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1430 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1432 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Return value */

/* 1434 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1436 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1438 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SubscribeToSelection */


	/* Procedure SubscribeToItemAddition */


	/* Procedure get_Item */


	/* Procedure get_Item */

/* 1440 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1442 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1446 */	NdrFcShort( 0x9 ),	/* 9 */
/* 1448 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1450 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1452 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1454 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1456 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1458 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1460 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1462 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter userData */


	/* Parameter userData */


	/* Parameter Idx */


	/* Parameter index */

/* 1464 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1466 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1468 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Parameter results */


	/* Parameter subHdl */


	/* Parameter pItem */


	/* Parameter pItem */

/* 1470 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 1472 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1474 */	NdrFcShort( 0x42c ),	/* Type Offset=1068 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 1476 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1478 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1480 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Item */


	/* Procedure put_Item */

/* 1482 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1484 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1488 */	NdrFcShort( 0xa ),	/* 10 */
/* 1490 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
/* 1492 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1494 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1496 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1498 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1500 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1502 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1504 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Idx */


	/* Parameter index */

/* 1506 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1508 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1510 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Parameter value */


	/* Parameter value */

/* 1512 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1514 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1516 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Return value */


	/* Return value */

/* 1518 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1520 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 1522 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Count */

/* 1524 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1526 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1530 */	NdrFcShort( 0xb ),	/* 11 */
/* 1532 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1534 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1536 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1538 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1540 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1542 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1544 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1546 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 1548 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1550 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1552 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1554 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1556 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1558 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Add */

/* 1560 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1562 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1566 */	NdrFcShort( 0xc ),	/* 12 */
/* 1568 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1570 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1572 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1574 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1576 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1578 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1580 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1582 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter InputArguments */

/* 1584 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1586 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1588 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 1590 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1592 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1594 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Remove */

/* 1596 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1598 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1602 */	NdrFcShort( 0xd ),	/* 13 */
/* 1604 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1606 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1608 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1610 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1612 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1614 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1616 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1618 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 1620 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1622 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1624 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Return value */

/* 1626 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1628 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1630 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get__NewEnum */

/* 1632 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1634 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1638 */	NdrFcShort( 0xe ),	/* 14 */
/* 1640 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1642 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1644 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1646 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1648 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1650 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1652 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1654 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 1656 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1658 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1660 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 1662 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1664 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1666 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Names */

/* 1668 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1670 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1674 */	NdrFcShort( 0xf ),	/* 15 */
/* 1676 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1680 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1682 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1684 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1686 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1688 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1690 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nameList */

/* 1692 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1694 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1696 */	NdrFcShort( 0x47a ),	/* Type Offset=1146 */

	/* Return value */

/* 1698 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1700 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1702 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Values */

/* 1704 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1706 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1710 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1712 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1714 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1716 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1718 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1720 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1722 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1724 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1726 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter valueList */

/* 1728 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1730 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1732 */	NdrFcShort( 0x47a ),	/* Type Offset=1146 */

	/* Return value */

/* 1734 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1736 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1738 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_g2UserMode */


	/* Procedure get_UUID */


	/* Procedure get_ClassName */

/* 1740 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1742 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1746 */	NdrFcShort( 0xb ),	/* 11 */
/* 1748 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1750 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1752 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1754 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1756 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1758 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1760 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1762 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pClassName */

/* 1764 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1766 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1768 */	NdrFcShort( 0x458 ),	/* Type Offset=1112 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 1770 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1772 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1774 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_g2UserMode */


	/* Procedure put_UUID */


	/* Procedure put_ClassName */

/* 1776 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1778 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1782 */	NdrFcShort( 0xc ),	/* 12 */
/* 1784 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1786 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1788 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1790 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1792 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1794 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1796 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1798 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */


	/* Parameter newVal */


	/* Parameter bstrClassName */

/* 1800 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1802 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1804 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 1806 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1808 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1810 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Name */

/* 1812 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1814 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1818 */	NdrFcShort( 0xd ),	/* 13 */
/* 1820 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1822 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1824 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1826 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1828 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1830 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1832 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1834 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pItemName */

/* 1836 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1838 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1840 */	NdrFcShort( 0x458 ),	/* Type Offset=1112 */

	/* Return value */

/* 1842 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1844 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1846 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Name */

/* 1848 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1850 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1854 */	NdrFcShort( 0xe ),	/* 14 */
/* 1856 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1858 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1860 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1862 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1864 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1866 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1868 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1870 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ItemName */

/* 1872 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1874 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1876 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 1878 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1880 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1882 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Type */

/* 1884 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1886 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1890 */	NdrFcShort( 0xf ),	/* 15 */
/* 1892 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1894 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1896 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1898 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1900 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1902 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1904 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1906 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pGsiType */

/* 1908 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 1910 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1912 */	NdrFcShort( 0x466 ),	/* Type Offset=1126 */

	/* Return value */

/* 1914 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1916 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1918 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Type */

/* 1920 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1922 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1926 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1928 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1930 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1932 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1934 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1936 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1938 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1940 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1942 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter GsiType */

/* 1944 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1946 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1948 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 1950 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1952 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1954 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Value */

/* 1956 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1958 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1962 */	NdrFcShort( 0x11 ),	/* 17 */
/* 1964 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1966 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1968 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1970 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1972 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1974 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1976 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1978 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pGsiType */

/* 1980 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 1982 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1984 */	NdrFcShort( 0x42c ),	/* Type Offset=1068 */

	/* Return value */

/* 1986 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1988 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1990 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Value */

/* 1992 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1994 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1998 */	NdrFcShort( 0x12 ),	/* 18 */
/* 2000 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2004 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2006 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2008 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2010 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2012 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2014 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter GsiType */

/* 2016 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2018 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2020 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Return value */

/* 2022 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2024 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2026 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Count */

/* 2028 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2030 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2034 */	NdrFcShort( 0x13 ),	/* 19 */
/* 2036 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2038 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2040 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2042 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2044 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2046 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2048 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2050 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2052 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2054 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2056 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2058 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2060 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2062 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Add */

/* 2064 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2066 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2070 */	NdrFcShort( 0x14 ),	/* 20 */
/* 2072 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2074 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2076 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2078 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2080 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2082 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2084 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2086 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter atName */

/* 2088 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2090 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2092 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Parameter atVal */

/* 2094 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2096 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2098 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Return value */

/* 2100 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2102 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2104 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Remove */

/* 2106 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2108 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2112 */	NdrFcShort( 0x15 ),	/* 21 */
/* 2114 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2116 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2118 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2120 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2122 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2126 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2128 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter varIdx */

/* 2130 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2132 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2134 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Return value */

/* 2136 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2138 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2140 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get__NewEnum */

/* 2142 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2144 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2148 */	NdrFcShort( 0x16 ),	/* 22 */
/* 2150 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2152 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2154 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2156 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2158 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2160 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2164 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2166 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2168 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2170 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 2172 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2174 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2176 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AttrNames */

/* 2178 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2180 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2184 */	NdrFcShort( 0x17 ),	/* 23 */
/* 2186 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2190 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2192 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2194 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2196 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2200 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter attrNameList */

/* 2202 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2204 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2206 */	NdrFcShort( 0x47a ),	/* Type Offset=1146 */

	/* Return value */

/* 2208 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2210 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2212 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AttrValues */

/* 2214 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2216 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2220 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2222 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2224 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2226 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2228 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2230 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2232 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2236 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter attrValList */

/* 2238 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2240 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2242 */	NdrFcShort( 0x47a ),	/* Type Offset=1146 */

	/* Return value */

/* 2244 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2246 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2248 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AttrTypes */

/* 2250 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2252 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2256 */	NdrFcShort( 0x19 ),	/* 25 */
/* 2258 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2260 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2262 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2264 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2266 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2268 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2272 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter attrTypeList */

/* 2274 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2276 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2278 */	NdrFcShort( 0x47a ),	/* Type Offset=1146 */

	/* Return value */

/* 2280 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2282 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2284 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Symbolize */

/* 2286 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2288 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2292 */	NdrFcShort( 0x1a ),	/* 26 */
/* 2294 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2296 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2298 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2300 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2302 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2304 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2306 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2308 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter idx */

/* 2310 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2312 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2314 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Parameter flgSym */

/* 2316 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2318 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2320 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 2322 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2324 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2326 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Init */

/* 2328 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2330 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2334 */	NdrFcShort( 0x1b ),	/* 27 */
/* 2336 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2338 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2340 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2342 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2344 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2346 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2348 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2350 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pItem */

/* 2352 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2354 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2356 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2358 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2360 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2362 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Git */

/* 2364 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2366 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2370 */	NdrFcShort( 0x1c ),	/* 28 */
/* 2372 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2374 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2376 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2378 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2380 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2382 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2384 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2386 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pGsiItem */

/* 2388 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2390 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2392 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2394 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2396 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2398 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Inix */

/* 2400 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2402 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2406 */	NdrFcShort( 0x1d ),	/* 29 */
/* 2408 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2410 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2412 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2414 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2416 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2418 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2420 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2422 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pItem */

/* 2424 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2426 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2428 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pRef */

/* 2430 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2432 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2434 */	NdrFcShort( 0x484 ),	/* Type Offset=1156 */

	/* Return value */

/* 2436 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2438 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2440 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Refresh */

/* 2442 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2444 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2448 */	NdrFcShort( 0x1e ),	/* 30 */
/* 2450 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2452 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2454 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2456 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2458 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2460 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2464 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2466 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2468 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2470 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Update */

/* 2472 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2474 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2478 */	NdrFcShort( 0x1f ),	/* 31 */
/* 2480 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2482 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2484 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2486 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2488 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2490 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2492 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2494 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2496 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2498 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2500 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Create */

/* 2502 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2504 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2508 */	NdrFcShort( 0x20 ),	/* 32 */
/* 2510 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2512 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2514 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2516 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2518 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2522 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2524 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pAxL */

/* 2526 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2528 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2530 */	NdrFcShort( 0xe2 ),	/* Type Offset=226 */

	/* Return value */

/* 2532 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2534 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2536 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Delete */

/* 2538 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2540 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2544 */	NdrFcShort( 0x21 ),	/* 33 */
/* 2546 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2550 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2552 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2554 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2556 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2558 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2560 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2562 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2564 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2566 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Linked */

/* 2568 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2570 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2574 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2576 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2578 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2580 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2582 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2584 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2586 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2588 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2590 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pflgLinked */

/* 2592 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2594 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2596 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 2598 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2600 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2602 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Link */

/* 2604 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2606 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2610 */	NdrFcShort( 0x23 ),	/* 35 */
/* 2612 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2614 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2616 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2618 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2620 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2622 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2624 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2626 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pItemRef */

/* 2628 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2630 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2632 */	NdrFcShort( 0x484 ),	/* Type Offset=1156 */

	/* Return value */

/* 2634 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2636 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2638 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Unlink */

/* 2640 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2642 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2646 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2648 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2650 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2652 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2654 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2656 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2658 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2660 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2662 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2664 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2666 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2668 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Unhandle */

/* 2670 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2672 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2676 */	NdrFcShort( 0x25 ),	/* 37 */
/* 2678 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2680 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2682 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2684 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2686 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2688 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2690 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2692 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2694 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2696 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2698 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AttrType */

/* 2700 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2702 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2706 */	NdrFcShort( 0x26 ),	/* 38 */
/* 2708 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2710 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2712 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2714 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2716 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2718 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2720 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2722 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter idx */

/* 2724 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2726 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2728 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Parameter pVal */

/* 2730 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 2732 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2734 */	NdrFcShort( 0x466 ),	/* Type Offset=1126 */

	/* Return value */

/* 2736 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2738 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2740 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Reference */

/* 2742 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2744 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2748 */	NdrFcShort( 0x27 ),	/* 39 */
/* 2750 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2752 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2754 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2756 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2758 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2760 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2762 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2764 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2766 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2768 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2770 */	NdrFcShort( 0x496 ),	/* Type Offset=1174 */

	/* Return value */

/* 2772 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2774 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2776 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SubscribeToAttributeModification */

/* 2778 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2780 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2784 */	NdrFcShort( 0x28 ),	/* 40 */
/* 2786 */	NdrFcShort( 0x2c ),	/* x86 Stack size/offset = 44 */
/* 2788 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2790 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2792 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 2794 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2796 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2798 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2800 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter AttrName */

/* 2802 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2804 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2806 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Parameter userData */

/* 2808 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2810 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2812 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Parameter SubscripHndls */

/* 2814 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 2816 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 2818 */	NdrFcShort( 0x42c ),	/* Type Offset=1068 */

	/* Return value */

/* 2820 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2822 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
/* 2824 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SubscribeToDeletion */

/* 2826 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2828 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2832 */	NdrFcShort( 0x29 ),	/* 41 */
/* 2834 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2836 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2838 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2840 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2842 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2844 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2846 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2848 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter userData */

/* 2850 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2852 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2854 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Parameter SubscripHndl */

/* 2856 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 2858 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2860 */	NdrFcShort( 0x42c ),	/* Type Offset=1068 */

	/* Return value */

/* 2862 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2864 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2866 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SubscribeToIconColorChange */

/* 2868 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2870 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2874 */	NdrFcShort( 0x2a ),	/* 42 */
/* 2876 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2878 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2880 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2882 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2884 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2886 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2888 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2890 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter userData */

/* 2892 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2894 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2896 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Parameter SubscripHndl */

/* 2898 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 2900 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2902 */	NdrFcShort( 0x42c ),	/* Type Offset=1068 */

	/* Return value */

/* 2904 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2906 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2908 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SubscribeToCustomEvent */

/* 2910 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2912 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2916 */	NdrFcShort( 0x2b ),	/* 43 */
/* 2918 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 2920 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2922 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2924 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 2926 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2928 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2930 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2932 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter EventName */

/* 2934 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2936 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2938 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Parameter userData */

/* 2940 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2942 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2944 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Parameter SubscripHndl */

/* 2946 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 2948 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2950 */	NdrFcShort( 0x42c ),	/* Type Offset=1068 */

	/* Return value */

/* 2952 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2954 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2956 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SubscribeToValueChange */

/* 2958 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2960 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2964 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2966 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2968 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2970 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2972 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2974 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2976 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2978 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2980 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter userData */

/* 2982 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2984 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2986 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Parameter subscriptionHandle */

/* 2988 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 2990 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2992 */	NdrFcShort( 0x42c ),	/* Type Offset=1068 */

	/* Return value */

/* 2994 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2996 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2998 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnsubscribeFromAttributeModification */

/* 3000 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3002 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3006 */	NdrFcShort( 0x2d ),	/* 45 */
/* 3008 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3010 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3012 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3014 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3016 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3018 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3020 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3022 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter FromWhat */

/* 3024 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3026 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3028 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Return value */

/* 3030 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3032 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3034 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnsubscribeFromDeletion */

/* 3036 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3038 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3042 */	NdrFcShort( 0x2e ),	/* 46 */
/* 3044 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3046 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3048 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3050 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 3052 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3054 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3056 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3058 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 3060 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3062 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3064 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnsubscribeFromIconColorChange */

/* 3066 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3068 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3072 */	NdrFcShort( 0x2f ),	/* 47 */
/* 3074 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3076 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3078 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3080 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 3082 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3084 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3086 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3088 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 3090 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3092 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3094 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnsubscribeFromCustomEvent */

/* 3096 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3098 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3102 */	NdrFcShort( 0x30 ),	/* 48 */
/* 3104 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3106 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3108 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3110 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3112 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3114 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3116 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3118 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter EventNames */

/* 3120 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3122 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3124 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Return value */

/* 3126 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3128 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3130 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnsubscribeFromAll */

/* 3132 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3134 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3138 */	NdrFcShort( 0x31 ),	/* 49 */
/* 3140 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3142 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3144 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3146 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 3148 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3152 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3154 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 3156 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3158 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3160 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnsubscribeFromValueChange */

/* 3162 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3164 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3168 */	NdrFcShort( 0x32 ),	/* 50 */
/* 3170 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3172 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3174 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3176 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 3178 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3180 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3182 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3184 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 3186 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3188 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3190 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Subscriptions */

/* 3192 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3194 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3198 */	NdrFcShort( 0x33 ),	/* 51 */
/* 3200 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3202 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3204 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3206 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3208 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3210 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3212 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3214 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ArrayOfSubscriptions */

/* 3216 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 3218 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3220 */	NdrFcShort( 0x42c ),	/* Type Offset=1068 */

	/* Return value */

/* 3222 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3224 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3226 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Icon */

/* 3228 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3230 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3234 */	NdrFcShort( 0x34 ),	/* 52 */
/* 3236 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3238 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3240 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3242 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 3244 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3248 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3250 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter BackgroundColor */

/* 3252 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3254 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3256 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 3258 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3260 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3262 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */

	/* Return value */

/* 3264 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3266 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3268 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Init2 */

/* 3270 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3272 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3276 */	NdrFcShort( 0x35 ),	/* 53 */
/* 3278 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3280 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3282 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3284 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3286 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3288 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3290 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3292 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pDatum */

/* 3294 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3296 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3298 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3300 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3302 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3304 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Init3 */

/* 3306 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3308 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3312 */	NdrFcShort( 0x36 ),	/* 54 */
/* 3314 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3316 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3318 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3320 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 3322 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3324 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3326 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3328 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pDatum */

/* 3330 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3332 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3334 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pRef */

/* 3336 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 3338 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3340 */	NdrFcShort( 0x484 ),	/* Type Offset=1156 */

	/* Return value */

/* 3342 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3344 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3346 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Git2 */

/* 3348 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3350 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3354 */	NdrFcShort( 0x37 ),	/* 55 */
/* 3356 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3358 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3360 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3362 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3364 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3366 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3368 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3370 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppDatum */

/* 3372 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3374 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3376 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3378 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3380 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3382 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Value */

/* 3384 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3386 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3390 */	NdrFcShort( 0xa ),	/* 10 */
/* 3392 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3394 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3396 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3398 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3400 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3402 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3404 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3406 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter AttrVal */

/* 3408 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3410 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3412 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Return value */

/* 3414 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3416 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3418 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Type */

/* 3420 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3422 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3426 */	NdrFcShort( 0xc ),	/* 12 */
/* 3428 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3430 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3432 */	NdrFcShort( 0x22 ),	/* 34 */
/* 3434 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3436 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3438 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3440 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3442 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pType */

/* 3444 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 3446 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3448 */	NdrFcShort( 0x466 ),	/* Type Offset=1126 */

	/* Return value */

/* 3450 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3452 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3454 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Type */

/* 3456 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3458 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3462 */	NdrFcShort( 0xd ),	/* 13 */
/* 3464 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3466 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3468 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3470 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3472 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3474 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3476 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3478 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nType */

/* 3480 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3482 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3484 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 3486 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3488 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3490 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Init */


	/* Procedure Init */

/* 3492 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3494 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3498 */	NdrFcShort( 0xe ),	/* 14 */
/* 3500 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3502 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3504 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3506 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3508 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3510 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3512 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3514 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pGsiItem */


	/* Parameter pGsiAttr */

/* 3516 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3518 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3520 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 3522 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3524 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3526 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Item */

/* 3528 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3530 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3534 */	NdrFcShort( 0x9 ),	/* 9 */
/* 3536 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3538 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3540 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3542 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 3544 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3546 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3550 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter idx */

/* 3552 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3554 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3556 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 3558 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 3560 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3562 */	NdrFcShort( 0x42c ),	/* Type Offset=1068 */

	/* Return value */

/* 3564 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3566 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3568 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Item */

/* 3570 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3572 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3576 */	NdrFcShort( 0xa ),	/* 10 */
/* 3578 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 3580 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3582 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3584 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 3586 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3588 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3590 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3592 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter idx */

/* 3594 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3596 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3598 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter newVal */

/* 3600 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3602 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3604 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Return value */

/* 3606 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3608 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3610 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Type */

/* 3612 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3614 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3618 */	NdrFcShort( 0xb ),	/* 11 */
/* 3620 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3622 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3624 */	NdrFcShort( 0x22 ),	/* 34 */
/* 3626 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3628 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3630 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3632 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3634 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3636 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 3638 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3640 */	NdrFcShort( 0x466 ),	/* Type Offset=1126 */

	/* Return value */

/* 3642 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3644 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3646 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Type */

/* 3648 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3650 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3654 */	NdrFcShort( 0xc ),	/* 12 */
/* 3656 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3658 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3660 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3662 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3664 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3668 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3670 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3672 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3674 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3676 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 3678 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3680 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3682 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Count */

/* 3684 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3686 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3690 */	NdrFcShort( 0xd ),	/* 13 */
/* 3692 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3696 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3698 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3700 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3704 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3706 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3708 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3710 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3712 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3714 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3716 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3718 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Insert */

/* 3720 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3722 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3726 */	NdrFcShort( 0xf ),	/* 15 */
/* 3728 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 3730 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3732 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3734 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 3736 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3738 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3740 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3742 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter idx */

/* 3744 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3746 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3748 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter varX */

/* 3750 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3752 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3754 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Return value */

/* 3756 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3758 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3760 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Append */

/* 3762 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3764 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3768 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3770 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 3772 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3774 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3776 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 3778 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3782 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3784 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter idx */

/* 3786 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3788 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3790 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter varX */

/* 3792 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3794 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3796 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Return value */

/* 3798 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3800 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3802 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Add */

/* 3804 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3806 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3810 */	NdrFcShort( 0x11 ),	/* 17 */
/* 3812 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3814 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3816 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3818 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3820 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3822 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3824 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3826 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter varX */

/* 3828 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3830 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3832 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Return value */

/* 3834 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3836 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3838 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Remove */

/* 3840 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3842 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3846 */	NdrFcShort( 0x12 ),	/* 18 */
/* 3848 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3850 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3852 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3854 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3856 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3858 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3860 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3862 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter idx */

/* 3864 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3866 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3868 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3870 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3872 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3874 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get__NewEnum */

/* 3876 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3878 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3882 */	NdrFcShort( 0x13 ),	/* 19 */
/* 3884 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3886 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3888 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3890 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3892 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3894 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3896 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3898 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3900 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3902 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3904 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 3906 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3908 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3910 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Item */

/* 3912 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3914 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3918 */	NdrFcShort( 0x9 ),	/* 9 */
/* 3920 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3922 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3924 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3926 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3928 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3930 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3932 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3934 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3936 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 3938 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3940 */	NdrFcShort( 0x42c ),	/* Type Offset=1068 */

	/* Return value */

/* 3942 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3944 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3946 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Value */

/* 3948 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3950 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3954 */	NdrFcShort( 0xa ),	/* 10 */
/* 3956 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3958 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3960 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3962 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3964 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3966 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3968 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3970 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3972 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 3974 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3976 */	NdrFcShort( 0x42c ),	/* Type Offset=1068 */

	/* Return value */

/* 3978 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3980 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3982 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Value */

/* 3984 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3986 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3990 */	NdrFcShort( 0xb ),	/* 11 */
/* 3992 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3994 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3996 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3998 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4000 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4004 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4006 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 4008 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4010 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4012 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Return value */

/* 4014 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4016 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4018 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Init */

/* 4020 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4022 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4026 */	NdrFcShort( 0xc ),	/* 12 */
/* 4028 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4030 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4032 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4034 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 4036 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4038 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4040 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4042 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pLaw */

/* 4044 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 4046 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4048 */	NdrFcShort( 0x49a ),	/* Type Offset=1178 */

	/* Parameter idx */

/* 4050 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4052 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4054 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 4056 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4058 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4060 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_UpperCase */

/* 4062 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4064 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4068 */	NdrFcShort( 0xb ),	/* 11 */
/* 4070 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4072 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4074 */	NdrFcShort( 0x22 ),	/* 34 */
/* 4076 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4078 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4080 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4082 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4084 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 4086 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4088 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4090 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 4092 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4094 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4096 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_UpperCase */

/* 4098 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4100 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4104 */	NdrFcShort( 0xc ),	/* 12 */
/* 4106 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4108 */	NdrFcShort( 0x6 ),	/* 6 */
/* 4110 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4112 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4114 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4116 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4118 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4120 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 4122 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4124 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4126 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 4128 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4130 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4132 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Init */

/* 4134 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4136 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4140 */	NdrFcShort( 0x9 ),	/* 9 */
/* 4142 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4144 */	NdrFcShort( 0x22 ),	/* 34 */
/* 4146 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4148 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 4150 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4152 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4154 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4156 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pUUIDin */

/* 4158 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 4160 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4162 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pCtx */

/* 4164 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4166 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4168 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 4170 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4172 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4174 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Git */

/* 4176 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4178 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4182 */	NdrFcShort( 0xa ),	/* 10 */
/* 4184 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4186 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4188 */	NdrFcShort( 0x3e ),	/* 62 */
/* 4190 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 4192 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4196 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4198 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pUUIDout */

/* 4200 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4202 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4204 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pctx */

/* 4206 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4208 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4210 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 4212 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4214 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4216 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Gateway */

/* 4218 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4220 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4224 */	NdrFcShort( 0xd ),	/* 13 */
/* 4226 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4228 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4230 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4232 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4234 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4236 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4238 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4240 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter gateway */

/* 4242 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 4244 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4246 */	NdrFcShort( 0x4b0 ),	/* Type Offset=1200 */

	/* Return value */

/* 4248 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4250 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4252 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SubscribeToItemRemoval */

/* 4254 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4256 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4260 */	NdrFcShort( 0xa ),	/* 10 */
/* 4262 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 4264 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4266 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4268 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 4270 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 4272 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4274 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4276 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter userData */

/* 4278 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4280 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4282 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Parameter subHdl */

/* 4284 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 4286 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4288 */	NdrFcShort( 0x42c ),	/* Type Offset=1068 */

	/* Return value */

/* 4290 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4292 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 4294 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnsubscribeFromItemAddition */

/* 4296 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4298 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4302 */	NdrFcShort( 0xb ),	/* 11 */
/* 4304 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4306 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4308 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4310 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 4312 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4314 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4316 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4318 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 4320 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4322 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4324 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnsubscribeFromItemRemoval */

/* 4326 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4328 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4332 */	NdrFcShort( 0xc ),	/* 12 */
/* 4334 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4336 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4338 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4340 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 4342 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4344 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4346 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4348 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 4350 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4352 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4354 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnsubscribeFromSelection */

/* 4356 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4358 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4362 */	NdrFcShort( 0xa ),	/* 10 */
/* 4364 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4366 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4368 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4370 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 4372 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4374 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4376 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4378 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 4380 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4382 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4384 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_HighThroughput */

/* 4386 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4388 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4392 */	NdrFcShort( 0x7 ),	/* 7 */
/* 4394 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4396 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4398 */	NdrFcShort( 0x22 ),	/* 34 */
/* 4400 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4402 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4404 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4406 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4408 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 4410 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4412 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4414 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 4416 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4418 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4420 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_HighThroughput */

/* 4422 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4424 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4428 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4430 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4432 */	NdrFcShort( 0x6 ),	/* 6 */
/* 4434 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4436 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4438 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4440 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4442 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4444 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 4446 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4448 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4450 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 4452 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4454 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4456 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const G2Com_MIDL_TYPE_FORMAT_STRING G2Com__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x12, 0x0,	/* FC_UP */
/*  4 */	NdrFcShort( 0xe ),	/* Offset= 14 (18) */
/*  6 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/*  8 */	NdrFcShort( 0x2 ),	/* 2 */
/* 10 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 12 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 14 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 16 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 18 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 20 */	NdrFcShort( 0x8 ),	/* 8 */
/* 22 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (6) */
/* 24 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 26 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 28 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 30 */	NdrFcShort( 0x0 ),	/* 0 */
/* 32 */	NdrFcShort( 0x4 ),	/* 4 */
/* 34 */	NdrFcShort( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0xffde ),	/* Offset= -34 (2) */
/* 38 */	
			0x11, 0x0,	/* FC_RP */
/* 40 */	NdrFcShort( 0x3f2 ),	/* Offset= 1010 (1050) */
/* 42 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 44 */	NdrFcShort( 0x2 ),	/* Offset= 2 (46) */
/* 46 */	
			0x12, 0x0,	/* FC_UP */
/* 48 */	NdrFcShort( 0x3d8 ),	/* Offset= 984 (1032) */
/* 50 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 52 */	NdrFcShort( 0x18 ),	/* 24 */
/* 54 */	NdrFcShort( 0xa ),	/* 10 */
/* 56 */	NdrFcLong( 0x8 ),	/* 8 */
/* 60 */	NdrFcShort( 0x5a ),	/* Offset= 90 (150) */
/* 62 */	NdrFcLong( 0xd ),	/* 13 */
/* 66 */	NdrFcShort( 0x90 ),	/* Offset= 144 (210) */
/* 68 */	NdrFcLong( 0x9 ),	/* 9 */
/* 72 */	NdrFcShort( 0xc2 ),	/* Offset= 194 (266) */
/* 74 */	NdrFcLong( 0xc ),	/* 12 */
/* 78 */	NdrFcShort( 0x2bc ),	/* Offset= 700 (778) */
/* 80 */	NdrFcLong( 0x24 ),	/* 36 */
/* 84 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (826) */
/* 86 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 90 */	NdrFcShort( 0x302 ),	/* Offset= 770 (860) */
/* 92 */	NdrFcLong( 0x10 ),	/* 16 */
/* 96 */	NdrFcShort( 0x31c ),	/* Offset= 796 (892) */
/* 98 */	NdrFcLong( 0x2 ),	/* 2 */
/* 102 */	NdrFcShort( 0x336 ),	/* Offset= 822 (924) */
/* 104 */	NdrFcLong( 0x3 ),	/* 3 */
/* 108 */	NdrFcShort( 0x350 ),	/* Offset= 848 (956) */
/* 110 */	NdrFcLong( 0x14 ),	/* 20 */
/* 114 */	NdrFcShort( 0x36a ),	/* Offset= 874 (988) */
/* 116 */	NdrFcShort( 0xffff ),	/* Offset= -1 (115) */
/* 118 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 120 */	NdrFcShort( 0x4 ),	/* 4 */
/* 122 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 126 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 128 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 130 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 132 */	NdrFcShort( 0x4 ),	/* 4 */
/* 134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 136 */	NdrFcShort( 0x1 ),	/* 1 */
/* 138 */	NdrFcShort( 0x0 ),	/* 0 */
/* 140 */	NdrFcShort( 0x0 ),	/* 0 */
/* 142 */	0x12, 0x0,	/* FC_UP */
/* 144 */	NdrFcShort( 0xff82 ),	/* Offset= -126 (18) */
/* 146 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 148 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 150 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 152 */	NdrFcShort( 0x8 ),	/* 8 */
/* 154 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 156 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 158 */	NdrFcShort( 0x4 ),	/* 4 */
/* 160 */	NdrFcShort( 0x4 ),	/* 4 */
/* 162 */	0x11, 0x0,	/* FC_RP */
/* 164 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (118) */
/* 166 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 168 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 170 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 172 */	NdrFcLong( 0x0 ),	/* 0 */
/* 176 */	NdrFcShort( 0x0 ),	/* 0 */
/* 178 */	NdrFcShort( 0x0 ),	/* 0 */
/* 180 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 182 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 184 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 186 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 188 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 190 */	NdrFcShort( 0x0 ),	/* 0 */
/* 192 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 196 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 198 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 202 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 204 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 206 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (170) */
/* 208 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 210 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 212 */	NdrFcShort( 0x8 ),	/* 8 */
/* 214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 216 */	NdrFcShort( 0x6 ),	/* Offset= 6 (222) */
/* 218 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 220 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 222 */	
			0x11, 0x0,	/* FC_RP */
/* 224 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (188) */
/* 226 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 228 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 232 */	NdrFcShort( 0x0 ),	/* 0 */
/* 234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 236 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 238 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 240 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 242 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 244 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 248 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 252 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 254 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 258 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 260 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 262 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (226) */
/* 264 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 266 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 268 */	NdrFcShort( 0x8 ),	/* 8 */
/* 270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 272 */	NdrFcShort( 0x6 ),	/* Offset= 6 (278) */
/* 274 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 276 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 278 */	
			0x11, 0x0,	/* FC_RP */
/* 280 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (244) */
/* 282 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 284 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 286 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 288 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 290 */	NdrFcShort( 0x2 ),	/* Offset= 2 (292) */
/* 292 */	NdrFcShort( 0x10 ),	/* 16 */
/* 294 */	NdrFcShort( 0x2f ),	/* 47 */
/* 296 */	NdrFcLong( 0x14 ),	/* 20 */
/* 300 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 302 */	NdrFcLong( 0x3 ),	/* 3 */
/* 306 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 308 */	NdrFcLong( 0x11 ),	/* 17 */
/* 312 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 314 */	NdrFcLong( 0x2 ),	/* 2 */
/* 318 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 320 */	NdrFcLong( 0x4 ),	/* 4 */
/* 324 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 326 */	NdrFcLong( 0x5 ),	/* 5 */
/* 330 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 332 */	NdrFcLong( 0xb ),	/* 11 */
/* 336 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 338 */	NdrFcLong( 0xa ),	/* 10 */
/* 342 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 344 */	NdrFcLong( 0x6 ),	/* 6 */
/* 348 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (580) */
/* 350 */	NdrFcLong( 0x7 ),	/* 7 */
/* 354 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 356 */	NdrFcLong( 0x8 ),	/* 8 */
/* 360 */	NdrFcShort( 0xfe9a ),	/* Offset= -358 (2) */
/* 362 */	NdrFcLong( 0xd ),	/* 13 */
/* 366 */	NdrFcShort( 0xff3c ),	/* Offset= -196 (170) */
/* 368 */	NdrFcLong( 0x9 ),	/* 9 */
/* 372 */	NdrFcShort( 0xff6e ),	/* Offset= -146 (226) */
/* 374 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 378 */	NdrFcShort( 0xd0 ),	/* Offset= 208 (586) */
/* 380 */	NdrFcLong( 0x24 ),	/* 36 */
/* 384 */	NdrFcShort( 0xd2 ),	/* Offset= 210 (594) */
/* 386 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 390 */	NdrFcShort( 0xcc ),	/* Offset= 204 (594) */
/* 392 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 396 */	NdrFcShort( 0xfc ),	/* Offset= 252 (648) */
/* 398 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 402 */	NdrFcShort( 0xfa ),	/* Offset= 250 (652) */
/* 404 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 408 */	NdrFcShort( 0xf8 ),	/* Offset= 248 (656) */
/* 410 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 414 */	NdrFcShort( 0xf6 ),	/* Offset= 246 (660) */
/* 416 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 420 */	NdrFcShort( 0xf4 ),	/* Offset= 244 (664) */
/* 422 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 426 */	NdrFcShort( 0xf2 ),	/* Offset= 242 (668) */
/* 428 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 432 */	NdrFcShort( 0xdc ),	/* Offset= 220 (652) */
/* 434 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 438 */	NdrFcShort( 0xda ),	/* Offset= 218 (656) */
/* 440 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 444 */	NdrFcShort( 0xe4 ),	/* Offset= 228 (672) */
/* 446 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 450 */	NdrFcShort( 0xda ),	/* Offset= 218 (668) */
/* 452 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 456 */	NdrFcShort( 0xdc ),	/* Offset= 220 (676) */
/* 458 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 462 */	NdrFcShort( 0xda ),	/* Offset= 218 (680) */
/* 464 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 468 */	NdrFcShort( 0xd8 ),	/* Offset= 216 (684) */
/* 470 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 474 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (688) */
/* 476 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 480 */	NdrFcShort( 0xdc ),	/* Offset= 220 (700) */
/* 482 */	NdrFcLong( 0x10 ),	/* 16 */
/* 486 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 488 */	NdrFcLong( 0x12 ),	/* 18 */
/* 492 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 494 */	NdrFcLong( 0x13 ),	/* 19 */
/* 498 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 500 */	NdrFcLong( 0x15 ),	/* 21 */
/* 504 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 506 */	NdrFcLong( 0x16 ),	/* 22 */
/* 510 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 512 */	NdrFcLong( 0x17 ),	/* 23 */
/* 516 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 518 */	NdrFcLong( 0xe ),	/* 14 */
/* 522 */	NdrFcShort( 0xba ),	/* Offset= 186 (708) */
/* 524 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 528 */	NdrFcShort( 0xbe ),	/* Offset= 190 (718) */
/* 530 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 534 */	NdrFcShort( 0xbc ),	/* Offset= 188 (722) */
/* 536 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 540 */	NdrFcShort( 0x70 ),	/* Offset= 112 (652) */
/* 542 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 546 */	NdrFcShort( 0x6e ),	/* Offset= 110 (656) */
/* 548 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 552 */	NdrFcShort( 0x6c ),	/* Offset= 108 (660) */
/* 554 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 558 */	NdrFcShort( 0x62 ),	/* Offset= 98 (656) */
/* 560 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 564 */	NdrFcShort( 0x5c ),	/* Offset= 92 (656) */
/* 566 */	NdrFcLong( 0x0 ),	/* 0 */
/* 570 */	NdrFcShort( 0x0 ),	/* Offset= 0 (570) */
/* 572 */	NdrFcLong( 0x1 ),	/* 1 */
/* 576 */	NdrFcShort( 0x0 ),	/* Offset= 0 (576) */
/* 578 */	NdrFcShort( 0xffff ),	/* Offset= -1 (577) */
/* 580 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 582 */	NdrFcShort( 0x8 ),	/* 8 */
/* 584 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 586 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 588 */	NdrFcShort( 0x2 ),	/* Offset= 2 (590) */
/* 590 */	
			0x12, 0x0,	/* FC_UP */
/* 592 */	NdrFcShort( 0x1b8 ),	/* Offset= 440 (1032) */
/* 594 */	
			0x12, 0x0,	/* FC_UP */
/* 596 */	NdrFcShort( 0x20 ),	/* Offset= 32 (628) */
/* 598 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 600 */	NdrFcLong( 0x2f ),	/* 47 */
/* 604 */	NdrFcShort( 0x0 ),	/* 0 */
/* 606 */	NdrFcShort( 0x0 ),	/* 0 */
/* 608 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 610 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 612 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 614 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 616 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 618 */	NdrFcShort( 0x1 ),	/* 1 */
/* 620 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 622 */	NdrFcShort( 0x4 ),	/* 4 */
/* 624 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 626 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 628 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 630 */	NdrFcShort( 0x10 ),	/* 16 */
/* 632 */	NdrFcShort( 0x0 ),	/* 0 */
/* 634 */	NdrFcShort( 0xa ),	/* Offset= 10 (644) */
/* 636 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 638 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 640 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (598) */
/* 642 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 644 */	
			0x12, 0x0,	/* FC_UP */
/* 646 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (616) */
/* 648 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 650 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 652 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 654 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 656 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 658 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 660 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 662 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 664 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 666 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 668 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 670 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 672 */	
			0x12, 0x0,	/* FC_UP */
/* 674 */	NdrFcShort( 0xffa2 ),	/* Offset= -94 (580) */
/* 676 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 678 */	NdrFcShort( 0xfd5c ),	/* Offset= -676 (2) */
/* 680 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 682 */	NdrFcShort( 0xfe00 ),	/* Offset= -512 (170) */
/* 684 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 686 */	NdrFcShort( 0xfe34 ),	/* Offset= -460 (226) */
/* 688 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 690 */	NdrFcShort( 0x2 ),	/* Offset= 2 (692) */
/* 692 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 694 */	NdrFcShort( 0x2 ),	/* Offset= 2 (696) */
/* 696 */	
			0x12, 0x0,	/* FC_UP */
/* 698 */	NdrFcShort( 0x14e ),	/* Offset= 334 (1032) */
/* 700 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 702 */	NdrFcShort( 0x2 ),	/* Offset= 2 (704) */
/* 704 */	
			0x12, 0x0,	/* FC_UP */
/* 706 */	NdrFcShort( 0x14 ),	/* Offset= 20 (726) */
/* 708 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 710 */	NdrFcShort( 0x10 ),	/* 16 */
/* 712 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 714 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 716 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 718 */	
			0x12, 0x0,	/* FC_UP */
/* 720 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (708) */
/* 722 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 724 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 726 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 728 */	NdrFcShort( 0x20 ),	/* 32 */
/* 730 */	NdrFcShort( 0x0 ),	/* 0 */
/* 732 */	NdrFcShort( 0x0 ),	/* Offset= 0 (732) */
/* 734 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 736 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 738 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 740 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 742 */	NdrFcShort( 0xfe34 ),	/* Offset= -460 (282) */
/* 744 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 746 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 748 */	NdrFcShort( 0x4 ),	/* 4 */
/* 750 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 752 */	NdrFcShort( 0x0 ),	/* 0 */
/* 754 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 756 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 758 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 760 */	NdrFcShort( 0x4 ),	/* 4 */
/* 762 */	NdrFcShort( 0x0 ),	/* 0 */
/* 764 */	NdrFcShort( 0x1 ),	/* 1 */
/* 766 */	NdrFcShort( 0x0 ),	/* 0 */
/* 768 */	NdrFcShort( 0x0 ),	/* 0 */
/* 770 */	0x12, 0x0,	/* FC_UP */
/* 772 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (726) */
/* 774 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 776 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 778 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 780 */	NdrFcShort( 0x8 ),	/* 8 */
/* 782 */	NdrFcShort( 0x0 ),	/* 0 */
/* 784 */	NdrFcShort( 0x6 ),	/* Offset= 6 (790) */
/* 786 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 788 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 790 */	
			0x11, 0x0,	/* FC_RP */
/* 792 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (746) */
/* 794 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 796 */	NdrFcShort( 0x4 ),	/* 4 */
/* 798 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 800 */	NdrFcShort( 0x0 ),	/* 0 */
/* 802 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 804 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 806 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 808 */	NdrFcShort( 0x4 ),	/* 4 */
/* 810 */	NdrFcShort( 0x0 ),	/* 0 */
/* 812 */	NdrFcShort( 0x1 ),	/* 1 */
/* 814 */	NdrFcShort( 0x0 ),	/* 0 */
/* 816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 818 */	0x12, 0x0,	/* FC_UP */
/* 820 */	NdrFcShort( 0xff40 ),	/* Offset= -192 (628) */
/* 822 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 824 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 826 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 828 */	NdrFcShort( 0x8 ),	/* 8 */
/* 830 */	NdrFcShort( 0x0 ),	/* 0 */
/* 832 */	NdrFcShort( 0x6 ),	/* Offset= 6 (838) */
/* 834 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 836 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 838 */	
			0x11, 0x0,	/* FC_RP */
/* 840 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (794) */
/* 842 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 844 */	NdrFcShort( 0x8 ),	/* 8 */
/* 846 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 848 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 850 */	NdrFcShort( 0x10 ),	/* 16 */
/* 852 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 854 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 856 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (842) */
			0x5b,		/* FC_END */
/* 860 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 862 */	NdrFcShort( 0x18 ),	/* 24 */
/* 864 */	NdrFcShort( 0x0 ),	/* 0 */
/* 866 */	NdrFcShort( 0xa ),	/* Offset= 10 (876) */
/* 868 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 870 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 872 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (848) */
/* 874 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 876 */	
			0x11, 0x0,	/* FC_RP */
/* 878 */	NdrFcShort( 0xfd4e ),	/* Offset= -690 (188) */
/* 880 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 882 */	NdrFcShort( 0x1 ),	/* 1 */
/* 884 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 886 */	NdrFcShort( 0x0 ),	/* 0 */
/* 888 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 890 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 892 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 894 */	NdrFcShort( 0x8 ),	/* 8 */
/* 896 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 898 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 900 */	NdrFcShort( 0x4 ),	/* 4 */
/* 902 */	NdrFcShort( 0x4 ),	/* 4 */
/* 904 */	0x12, 0x0,	/* FC_UP */
/* 906 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (880) */
/* 908 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 910 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 912 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 914 */	NdrFcShort( 0x2 ),	/* 2 */
/* 916 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 918 */	NdrFcShort( 0x0 ),	/* 0 */
/* 920 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 922 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 924 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 926 */	NdrFcShort( 0x8 ),	/* 8 */
/* 928 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 930 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 932 */	NdrFcShort( 0x4 ),	/* 4 */
/* 934 */	NdrFcShort( 0x4 ),	/* 4 */
/* 936 */	0x12, 0x0,	/* FC_UP */
/* 938 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (912) */
/* 940 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 942 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 944 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 946 */	NdrFcShort( 0x4 ),	/* 4 */
/* 948 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 950 */	NdrFcShort( 0x0 ),	/* 0 */
/* 952 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 954 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 956 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 958 */	NdrFcShort( 0x8 ),	/* 8 */
/* 960 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 962 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 964 */	NdrFcShort( 0x4 ),	/* 4 */
/* 966 */	NdrFcShort( 0x4 ),	/* 4 */
/* 968 */	0x12, 0x0,	/* FC_UP */
/* 970 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (944) */
/* 972 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 974 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 976 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 978 */	NdrFcShort( 0x8 ),	/* 8 */
/* 980 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 982 */	NdrFcShort( 0x0 ),	/* 0 */
/* 984 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 986 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 988 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 990 */	NdrFcShort( 0x8 ),	/* 8 */
/* 992 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 994 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 996 */	NdrFcShort( 0x4 ),	/* 4 */
/* 998 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1000 */	0x12, 0x0,	/* FC_UP */
/* 1002 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (976) */
/* 1004 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1006 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 1008 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 1010 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1012 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1014 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1016 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1018 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1020 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 1022 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 1024 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1026 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1028 */	NdrFcShort( 0xffec ),	/* Offset= -20 (1008) */
/* 1030 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1032 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1034 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1036 */	NdrFcShort( 0xffec ),	/* Offset= -20 (1016) */
/* 1038 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1038) */
/* 1040 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1042 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1044 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1046 */	NdrFcShort( 0xfc1c ),	/* Offset= -996 (50) */
/* 1048 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1050 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1052 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1054 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1056 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1058 */	NdrFcShort( 0xfc08 ),	/* Offset= -1016 (42) */
/* 1060 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1062 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1068) */
/* 1064 */	
			0x13, 0x0,	/* FC_OP */
/* 1066 */	NdrFcShort( 0xfeac ),	/* Offset= -340 (726) */
/* 1068 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1070 */	NdrFcShort( 0x2 ),	/* 2 */
/* 1072 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1074 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1076 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1064) */
/* 1078 */	
			0x11, 0x0,	/* FC_RP */
/* 1080 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1086) */
/* 1082 */	
			0x12, 0x0,	/* FC_UP */
/* 1084 */	NdrFcShort( 0xfe9a ),	/* Offset= -358 (726) */
/* 1086 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1088 */	NdrFcShort( 0x2 ),	/* 2 */
/* 1090 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1092 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1094 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1082) */
/* 1096 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1098 */	NdrFcShort( 0xfc98 ),	/* Offset= -872 (226) */
/* 1100 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1102 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 1104 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1106 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1112) */
/* 1108 */	
			0x13, 0x0,	/* FC_OP */
/* 1110 */	NdrFcShort( 0xfbbc ),	/* Offset= -1092 (18) */
/* 1112 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1114 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1116 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1118 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1120 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1108) */
/* 1122 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1124 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 1126 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1128 */	0xd,		/* FC_ENUM16 */
			0x5c,		/* FC_PAD */
/* 1130 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1132 */	NdrFcShort( 0xfc3e ),	/* Offset= -962 (170) */
/* 1134 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1136 */	NdrFcShort( 0xa ),	/* Offset= 10 (1146) */
/* 1138 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1140 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1142) */
/* 1142 */	
			0x13, 0x0,	/* FC_OP */
/* 1144 */	NdrFcShort( 0xff90 ),	/* Offset= -112 (1032) */
/* 1146 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1148 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1150 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1152 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1154 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (1138) */
/* 1156 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1158 */	NdrFcLong( 0x3862dc96 ),	/* 946003094 */
/* 1162 */	NdrFcShort( 0xaf87 ),	/* -20601 */
/* 1164 */	NdrFcShort( 0x48c9 ),	/* 18633 */
/* 1166 */	0x9c,		/* 156 */
			0x14,		/* 20 */
/* 1168 */	0xf,		/* 15 */
			0x2d,		/* 45 */
/* 1170 */	0x5a,		/* 90 */
			0x4b,		/* 75 */
/* 1172 */	0x72,		/* 114 */
			0x50,		/* 80 */
/* 1174 */	0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1176 */	NdrFcShort( 0xffec ),	/* Offset= -20 (1156) */
/* 1178 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1180 */	NdrFcLong( 0x4a80a9fd ),	/* 1249946109 */
/* 1184 */	NdrFcShort( 0x41df ),	/* 16863 */
/* 1186 */	NdrFcShort( 0x4b49 ),	/* 19273 */
/* 1188 */	0x87,		/* 135 */
			0x40,		/* 64 */
/* 1190 */	0x13,		/* 19 */
			0xc4,		/* 196 */
/* 1192 */	0x3e,		/* 62 */
			0x35,		/* 53 */
/* 1194 */	0xf,		/* 15 */
			0x29,		/* 41 */
/* 1196 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 1198 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 1200 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1202 */	NdrFcLong( 0x64bea68 ),	/* 105638504 */
/* 1206 */	NdrFcShort( 0x90c ),	/* 2316 */
/* 1208 */	NdrFcShort( 0x47fe ),	/* 18430 */
/* 1210 */	0x8d,		/* 141 */
			0x43,		/* 67 */
/* 1212 */	0x1b,		/* 27 */
			0xf8,		/* 248 */
/* 1214 */	0x8f,		/* 143 */
			0x5b,		/* 91 */
/* 1216 */	0xc4,		/* 196 */
			0x7d,		/* 125 */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            LPSAFEARRAY_UserSize
            ,LPSAFEARRAY_UserMarshal
            ,LPSAFEARRAY_UserUnmarshal
            ,LPSAFEARRAY_UserFree
            },
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };



/* Standard interface: __MIDL_itf_G2Com_0000_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IG2Gateway, ver. 0.0,
   GUID={0xA71ACD10,0x3B6E,0x11D1,{0x8A,0xB3,0x00,0x60,0x97,0x03,0xE6,0x0F}} */

#pragma code_seg(".orpc")
static const unsigned short IG2Gateway_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    36,
    66,
    114,
    162,
    204,
    252,
    294,
    330,
    366,
    402,
    438,
    474,
    510,
    546,
    582,
    618,
    654,
    684
    };

static const MIDL_STUBLESS_PROXY_INFO IG2Gateway_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Gateway_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2Gateway_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Gateway_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(26) _IG2GatewayProxyVtbl = 
{
    &IG2Gateway_ProxyInfo,
    &IID_IG2Gateway,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::Connect */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::Disconnect */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::Call */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::CallDeferred */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::Start */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::GetNamedObject */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::CreateObjectInstance */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_IsG2Connected */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_IsG2Running */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_G2Location */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::put_G2Location */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_InterfaceClass */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::put_InterfaceClass */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_RemoteInitializationString */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::put_RemoteInitializationString */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_CallTimeout */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::put_CallTimeout */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::_FireEvents */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::PostMessage */
};


static const PRPC_STUB_FUNCTION IG2Gateway_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2GatewayStubVtbl =
{
    &IID_IG2Gateway,
    &IG2Gateway_ServerInfo,
    26,
    &IG2Gateway_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IG2Gateway2, ver. 0.0,
   GUID={0xC18D503E,0xC8A5,0x45c6,{0xA4,0x2F,0x10,0x0F,0x43,0x47,0xB3,0x67}} */

#pragma code_seg(".orpc")
static const unsigned short IG2Gateway2_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    36,
    66,
    114,
    162,
    204,
    252,
    294,
    330,
    366,
    402,
    438,
    474,
    510,
    546,
    582,
    618,
    654,
    684,
    720,
    756
    };

static const MIDL_STUBLESS_PROXY_INFO IG2Gateway2_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Gateway2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2Gateway2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Gateway2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(28) _IG2Gateway2ProxyVtbl = 
{
    &IG2Gateway2_ProxyInfo,
    &IID_IG2Gateway2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::Connect */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::Disconnect */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::Call */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::CallDeferred */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::Start */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::GetNamedObject */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::CreateObjectInstance */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_IsG2Connected */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_IsG2Running */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_G2Location */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::put_G2Location */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_InterfaceClass */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::put_InterfaceClass */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_RemoteInitializationString */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::put_RemoteInitializationString */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_CallTimeout */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::put_CallTimeout */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::_FireEvents */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::PostMessage */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway2::OnStartPage */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway2::OnEndPage */
};


static const PRPC_STUB_FUNCTION IG2Gateway2_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2Gateway2StubVtbl =
{
    &IID_IG2Gateway2,
    &IG2Gateway2_ServerInfo,
    28,
    &IG2Gateway2_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IG2Gateway3, ver. 0.0,
   GUID={0x43DD340A,0x7247,0x416a,{0x9D,0xB0,0x64,0xB1,0x5C,0xD4,0xBD,0x28}} */

#pragma code_seg(".orpc")
static const unsigned short IG2Gateway3_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    36,
    66,
    114,
    162,
    204,
    252,
    294,
    330,
    366,
    402,
    438,
    474,
    510,
    546,
    582,
    618,
    654,
    684,
    720,
    756,
    786,
    834,
    870
    };

static const MIDL_STUBLESS_PROXY_INFO IG2Gateway3_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Gateway3_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2Gateway3_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Gateway3_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(31) _IG2Gateway3ProxyVtbl = 
{
    &IG2Gateway3_ProxyInfo,
    &IID_IG2Gateway3,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::Connect */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::Disconnect */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::Call */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::CallDeferred */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::Start */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::GetNamedObject */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::CreateObjectInstance */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_IsG2Connected */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_IsG2Running */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_G2Location */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::put_G2Location */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_InterfaceClass */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::put_InterfaceClass */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_RemoteInitializationString */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::put_RemoteInitializationString */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_CallTimeout */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::put_CallTimeout */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::_FireEvents */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::PostMessage */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway2::OnStartPage */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway2::OnEndPage */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway3::MakeG2ComVariable */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway3::DbgMsg */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway3::get_G2RunState */
};


static const PRPC_STUB_FUNCTION IG2Gateway3_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2Gateway3StubVtbl =
{
    &IID_IG2Gateway3,
    &IG2Gateway3_ServerInfo,
    31,
    &IG2Gateway3_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IG2Gateway4, ver. 0.0,
   GUID={0x064BEA68,0x090C,0x47fe,{0x8D,0x43,0x1B,0xF8,0x8F,0x5B,0xC4,0x7D}} */

#pragma code_seg(".orpc")
static const unsigned short IG2Gateway4_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    36,
    66,
    114,
    162,
    204,
    252,
    294,
    330,
    366,
    402,
    438,
    474,
    510,
    546,
    582,
    618,
    654,
    684,
    720,
    756,
    786,
    834,
    870,
    906,
    942,
    978,
    1014,
    1044,
    1080,
    1116,
    1152,
    1188
    };

static const MIDL_STUBLESS_PROXY_INFO IG2Gateway4_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Gateway4_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2Gateway4_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Gateway4_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(40) _IG2Gateway4ProxyVtbl = 
{
    &IG2Gateway4_ProxyInfo,
    &IID_IG2Gateway4,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::Connect */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::Disconnect */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::Call */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::CallDeferred */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::Start */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::GetNamedObject */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::CreateObjectInstance */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_IsG2Connected */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_IsG2Running */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_G2Location */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::put_G2Location */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_InterfaceClass */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::put_InterfaceClass */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_RemoteInitializationString */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::put_RemoteInitializationString */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::get_CallTimeout */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::put_CallTimeout */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::_FireEvents */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway::PostMessage */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway2::OnStartPage */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway2::OnEndPage */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway3::MakeG2ComVariable */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway3::DbgMsg */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway3::get_G2RunState */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway4::get_TWHandle */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway4::put_TWHandle */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway4::ObtainTWLockIfUnused */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway4::ClearTWLock */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway4::get_G2Symbols */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway4::put_G2Symbols */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway4::get_DisconnectOnReset */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway4::put_DisconnectOnReset */ ,
    (void *) (INT_PTR) -1 /* IG2Gateway4::SetContextLimit */
};


static const PRPC_STUB_FUNCTION IG2Gateway4_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2Gateway4StubVtbl =
{
    &IID_IG2Gateway4,
    &IG2Gateway4_ServerInfo,
    40,
    &IG2Gateway4_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: G2ComObject, ver. 0.0,
   GUID={0xFCEB8041,0xEF78,0x4be6,{0xAD,0xC8,0x51,0xC1,0x73,0xF6,0x54,0x84}} */

#pragma code_seg(".orpc")
static const unsigned short G2ComObject_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    1224,
    1260
    };

static const MIDL_STUBLESS_PROXY_INFO G2ComObject_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &G2ComObject_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO G2ComObject_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &G2ComObject_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(9) _G2ComObjectProxyVtbl = 
{
    &G2ComObject_ProxyInfo,
    &IID_G2ComObject,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::get_WhatAmI */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::Duplicate */
};


static const PRPC_STUB_FUNCTION G2ComObject_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _G2ComObjectStubVtbl =
{
    &IID_G2ComObject,
    &G2ComObject_ServerInfo,
    9,
    &G2ComObject_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IG2StructureEntry, ver. 0.0,
   GUID={0xC4E20F9C,0x7ECC,0x4EE8,{0x8F,0xEF,0x6A,0xB6,0xD3,0xD8,0x09,0x43}} */

#pragma code_seg(".orpc")
static const unsigned short IG2StructureEntry_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    1224,
    1260,
    1296,
    1332,
    1368,
    1404
    };

static const MIDL_STUBLESS_PROXY_INFO IG2StructureEntry_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2StructureEntry_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2StructureEntry_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2StructureEntry_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(13) _IG2StructureEntryProxyVtbl = 
{
    &IG2StructureEntry_ProxyInfo,
    &IID_IG2StructureEntry,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::get_WhatAmI */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::Duplicate */ ,
    (void *) (INT_PTR) -1 /* IG2StructureEntry::get_Name */ ,
    (void *) (INT_PTR) -1 /* IG2StructureEntry::put_Name */ ,
    (void *) (INT_PTR) -1 /* IG2StructureEntry::get_Value */ ,
    (void *) (INT_PTR) -1 /* IG2StructureEntry::put_Value */
};


static const PRPC_STUB_FUNCTION IG2StructureEntry_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2StructureEntryStubVtbl =
{
    &IID_IG2StructureEntry,
    &IG2StructureEntry_ServerInfo,
    13,
    &IG2StructureEntry_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IG2Structure, ver. 0.0,
   GUID={0xA59A1DFB,0x3711,0x4893,{0xB3,0xF4,0xD9,0xFD,0x0B,0x82,0x4C,0x23}} */

#pragma code_seg(".orpc")
static const unsigned short IG2Structure_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    1224,
    1260,
    1440,
    1482,
    1524,
    1560,
    1596,
    1632,
    1668,
    1704
    };

static const MIDL_STUBLESS_PROXY_INFO IG2Structure_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Structure_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2Structure_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Structure_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(17) _IG2StructureProxyVtbl = 
{
    &IG2Structure_ProxyInfo,
    &IID_IG2Structure,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::get_WhatAmI */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::Duplicate */ ,
    (void *) (INT_PTR) -1 /* IG2Structure::get_Item */ ,
    (void *) (INT_PTR) -1 /* IG2Structure::put_Item */ ,
    (void *) (INT_PTR) -1 /* IG2Structure::get_Count */ ,
    (void *) (INT_PTR) -1 /* IG2Structure::Add */ ,
    (void *) (INT_PTR) -1 /* IG2Structure::Remove */ ,
    (void *) (INT_PTR) -1 /* IG2Structure::get__NewEnum */ ,
    (void *) (INT_PTR) -1 /* IG2Structure::Names */ ,
    (void *) (INT_PTR) -1 /* IG2Structure::Values */
};


static const PRPC_STUB_FUNCTION IG2Structure_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2StructureStubVtbl =
{
    &IID_IG2Structure,
    &IG2Structure_ServerInfo,
    17,
    &IG2Structure_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IG2Item, ver. 0.0,
   GUID={0xD4A49E08,0x2ADA,0x49D2,{0xBB,0xCB,0x7F,0xDD,0x7E,0xBB,0x6D,0x86}} */

#pragma code_seg(".orpc")
static const unsigned short IG2Item_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    1224,
    1260,
    1440,
    1482,
    1740,
    1776,
    1812,
    1848,
    1884,
    1920,
    1956,
    1992,
    2028,
    2064,
    2106,
    2142,
    2178,
    2214,
    2250,
    2286,
    2328,
    2364
    };

static const MIDL_STUBLESS_PROXY_INFO IG2Item_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Item_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2Item_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Item_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(29) _IG2ItemProxyVtbl = 
{
    &IG2Item_ProxyInfo,
    &IID_IG2Item,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::get_WhatAmI */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::Duplicate */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Item */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_Item */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_ClassName */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_ClassName */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Name */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_Name */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Type */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_Type */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Value */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_Value */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Count */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Add */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Remove */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get__NewEnum */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_AttrNames */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_AttrValues */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_AttrTypes */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Symbolize */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Init */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Git */
};


static const PRPC_STUB_FUNCTION IG2Item_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2ItemStubVtbl =
{
    &IID_IG2Item,
    &IG2Item_ServerInfo,
    29,
    &IG2Item_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Standard interface: __MIDL_itf_G2Com_0000_0008, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IG2Item2, ver. 0.0,
   GUID={0x0E22A2CD,0x4E8C,0x4f5d,{0xBE,0x79,0x39,0xD6,0xCC,0xC8,0x04,0xF3}} */

#pragma code_seg(".orpc")
static const unsigned short IG2Item2_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    1224,
    1260,
    1440,
    1482,
    1740,
    1776,
    1812,
    1848,
    1884,
    1920,
    1956,
    1992,
    2028,
    2064,
    2106,
    2142,
    2178,
    2214,
    2250,
    2286,
    2328,
    2364,
    2400,
    2442,
    2472,
    2502,
    2538,
    2568,
    2604,
    2640,
    2670,
    2700,
    2742,
    2778,
    2826,
    2868,
    2910,
    2958,
    3000,
    3036,
    3066,
    3096,
    3132,
    3162,
    3192
    };

static const MIDL_STUBLESS_PROXY_INFO IG2Item2_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Item2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2Item2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Item2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(52) _IG2Item2ProxyVtbl = 
{
    &IG2Item2_ProxyInfo,
    &IID_IG2Item2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::get_WhatAmI */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::Duplicate */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Item */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_Item */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_ClassName */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_ClassName */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Name */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_Name */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Type */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_Type */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Value */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_Value */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Count */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Add */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Remove */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get__NewEnum */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_AttrNames */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_AttrValues */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_AttrTypes */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Symbolize */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Init */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Git */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Inix */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Refresh */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Update */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Create */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Delete */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::get_Linked */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Link */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Unlink */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Unhandle */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::get_AttrType */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::get_Reference */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::SubscribeToAttributeModification */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::SubscribeToDeletion */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::SubscribeToIconColorChange */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::SubscribeToCustomEvent */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::SubscribeToValueChange */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromAttributeModification */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromDeletion */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromIconColorChange */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromCustomEvent */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromAll */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromValueChange */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Subscriptions */
};


static const PRPC_STUB_FUNCTION IG2Item2_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2Item2StubVtbl =
{
    &IID_IG2Item2,
    &IG2Item2_ServerInfo,
    52,
    &IG2Item2_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IG2Item3, ver. 0.0,
   GUID={0x159B27B6,0x6BB3,0x4317,{0xA5,0xE5,0xFD,0x55,0x00,0x1D,0x3E,0x9F}} */

#pragma code_seg(".orpc")
static const unsigned short IG2Item3_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    1224,
    1260,
    1440,
    1482,
    1740,
    1776,
    1812,
    1848,
    1884,
    1920,
    1956,
    1992,
    2028,
    2064,
    2106,
    2142,
    2178,
    2214,
    2250,
    2286,
    2328,
    2364,
    2400,
    2442,
    2472,
    2502,
    2538,
    2568,
    2604,
    2640,
    2670,
    2700,
    2742,
    2778,
    2826,
    2868,
    2910,
    2958,
    3000,
    3036,
    3066,
    3096,
    3132,
    3162,
    3192,
    3228
    };

static const MIDL_STUBLESS_PROXY_INFO IG2Item3_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Item3_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2Item3_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Item3_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(53) _IG2Item3ProxyVtbl = 
{
    &IG2Item3_ProxyInfo,
    &IID_IG2Item3,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::get_WhatAmI */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::Duplicate */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Item */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_Item */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_ClassName */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_ClassName */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Name */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_Name */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Type */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_Type */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Value */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_Value */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Count */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Add */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Remove */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get__NewEnum */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_AttrNames */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_AttrValues */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_AttrTypes */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Symbolize */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Init */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Git */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Inix */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Refresh */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Update */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Create */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Delete */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::get_Linked */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Link */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Unlink */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Unhandle */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::get_AttrType */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::get_Reference */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::SubscribeToAttributeModification */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::SubscribeToDeletion */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::SubscribeToIconColorChange */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::SubscribeToCustomEvent */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::SubscribeToValueChange */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromAttributeModification */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromDeletion */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromIconColorChange */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromCustomEvent */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromAll */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromValueChange */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Subscriptions */ ,
    (void *) (INT_PTR) -1 /* IG2Item3::get_Icon */
};


static const PRPC_STUB_FUNCTION IG2Item3_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2Item3StubVtbl =
{
    &IID_IG2Item3,
    &IG2Item3_ServerInfo,
    53,
    &IG2Item3_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IG2Item4, ver. 0.0,
   GUID={0xD8B90DC4,0x74BB,0x4775,{0x98,0x3C,0x02,0x13,0x7E,0x2E,0x28,0x3B}} */

#pragma code_seg(".orpc")
static const unsigned short IG2Item4_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    1224,
    1260,
    1440,
    1482,
    1740,
    1776,
    1812,
    1848,
    1884,
    1920,
    1956,
    1992,
    2028,
    2064,
    2106,
    2142,
    2178,
    2214,
    2250,
    2286,
    2328,
    2364,
    2400,
    2442,
    2472,
    2502,
    2538,
    2568,
    2604,
    2640,
    2670,
    2700,
    2742,
    2778,
    2826,
    2868,
    2910,
    2958,
    3000,
    3036,
    3066,
    3096,
    3132,
    3162,
    3192,
    3228,
    3270,
    3306,
    3348
    };

static const MIDL_STUBLESS_PROXY_INFO IG2Item4_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Item4_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2Item4_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Item4_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(56) _IG2Item4ProxyVtbl = 
{
    &IG2Item4_ProxyInfo,
    &IID_IG2Item4,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::get_WhatAmI */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::Duplicate */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Item */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_Item */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_ClassName */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_ClassName */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Name */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_Name */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Type */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_Type */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Value */ ,
    (void *) (INT_PTR) -1 /* IG2Item::put_Value */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_Count */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Add */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Remove */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get__NewEnum */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_AttrNames */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_AttrValues */ ,
    (void *) (INT_PTR) -1 /* IG2Item::get_AttrTypes */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Symbolize */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Init */ ,
    (void *) (INT_PTR) -1 /* IG2Item::Git */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Inix */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Refresh */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Update */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Create */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Delete */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::get_Linked */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Link */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Unlink */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Unhandle */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::get_AttrType */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::get_Reference */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::SubscribeToAttributeModification */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::SubscribeToDeletion */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::SubscribeToIconColorChange */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::SubscribeToCustomEvent */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::SubscribeToValueChange */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromAttributeModification */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromDeletion */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromIconColorChange */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromCustomEvent */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromAll */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::UnsubscribeFromValueChange */ ,
    (void *) (INT_PTR) -1 /* IG2Item2::Subscriptions */ ,
    (void *) (INT_PTR) -1 /* IG2Item3::get_Icon */ ,
    (void *) (INT_PTR) -1 /* IG2Item4::Init2 */ ,
    (void *) (INT_PTR) -1 /* IG2Item4::Init3 */ ,
    (void *) (INT_PTR) -1 /* IG2Item4::Git2 */
};


static const PRPC_STUB_FUNCTION IG2Item4_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2Item4StubVtbl =
{
    &IID_IG2Item4,
    &IG2Item4_ServerInfo,
    56,
    &IG2Item4_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IG2Attribute, ver. 0.0,
   GUID={0x45BB4FD7,0x576B,0x4672,{0x92,0x3E,0x15,0xE7,0xC1,0x3D,0x2C,0x76}} */

#pragma code_seg(".orpc")
static const unsigned short IG2Attribute_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    1224,
    1260,
    1296,
    3384,
    1368,
    3420,
    3456,
    3492
    };

static const MIDL_STUBLESS_PROXY_INFO IG2Attribute_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Attribute_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2Attribute_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Attribute_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(15) _IG2AttributeProxyVtbl = 
{
    &IG2Attribute_ProxyInfo,
    &IID_IG2Attribute,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::get_WhatAmI */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::Duplicate */ ,
    (void *) (INT_PTR) -1 /* IG2Attribute::get_Name */ ,
    (void *) (INT_PTR) -1 /* IG2Attribute::put_Value */ ,
    (void *) (INT_PTR) -1 /* IG2Attribute::get_Value */ ,
    (void *) (INT_PTR) -1 /* IG2Attribute::get_Type */ ,
    (void *) (INT_PTR) -1 /* IG2Attribute::put_Type */ ,
    (void *) (INT_PTR) -1 /* IG2Attribute::Init */
};


static const PRPC_STUB_FUNCTION IG2Attribute_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2AttributeStubVtbl =
{
    &IID_IG2Attribute,
    &IG2Attribute_ServerInfo,
    15,
    &IG2Attribute_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IG2ListOrArray, ver. 0.0,
   GUID={0x4A80A9FD,0x41DF,0x4b49,{0x87,0x40,0x13,0xC4,0x3E,0x35,0x0F,0x29}} */

#pragma code_seg(".orpc")
static const unsigned short IG2ListOrArray_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    1224,
    1260,
    3528,
    3570,
    3612,
    3648,
    3684,
    3492,
    3720,
    3762,
    3804,
    3840,
    3876
    };

static const MIDL_STUBLESS_PROXY_INFO IG2ListOrArray_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2ListOrArray_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2ListOrArray_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2ListOrArray_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(20) _IG2ListOrArrayProxyVtbl = 
{
    &IG2ListOrArray_ProxyInfo,
    &IID_IG2ListOrArray,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::get_WhatAmI */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::Duplicate */ ,
    (void *) (INT_PTR) -1 /* IG2ListOrArray::get_Item */ ,
    (void *) (INT_PTR) -1 /* IG2ListOrArray::put_Item */ ,
    (void *) (INT_PTR) -1 /* IG2ListOrArray::get_Type */ ,
    (void *) (INT_PTR) -1 /* IG2ListOrArray::put_Type */ ,
    (void *) (INT_PTR) -1 /* IG2ListOrArray::get_Count */ ,
    (void *) (INT_PTR) -1 /* IG2ListOrArray::Init */ ,
    (void *) (INT_PTR) -1 /* IG2ListOrArray::Insert */ ,
    (void *) (INT_PTR) -1 /* IG2ListOrArray::Append */ ,
    (void *) (INT_PTR) -1 /* IG2ListOrArray::Add */ ,
    (void *) (INT_PTR) -1 /* IG2ListOrArray::Remove */ ,
    (void *) (INT_PTR) -1 /* IG2ListOrArray::get__NewEnum */
};


static const PRPC_STUB_FUNCTION IG2ListOrArray_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2ListOrArrayStubVtbl =
{
    &IID_IG2ListOrArray,
    &IG2ListOrArray_ServerInfo,
    20,
    &IG2ListOrArray_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IG2LAElement, ver. 0.0,
   GUID={0x98A966CA,0x2D0B,0x4952,{0xBD,0x49,0x25,0xB3,0xBB,0xEE,0x91,0xF6}} */

#pragma code_seg(".orpc")
static const unsigned short IG2LAElement_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    1224,
    1260,
    3912,
    3948,
    3984,
    4020
    };

static const MIDL_STUBLESS_PROXY_INFO IG2LAElement_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2LAElement_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2LAElement_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2LAElement_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(13) _IG2LAElementProxyVtbl = 
{
    &IG2LAElement_ProxyInfo,
    &IID_IG2LAElement,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::get_WhatAmI */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::Duplicate */ ,
    (void *) (INT_PTR) -1 /* IG2LAElement::get_Item */ ,
    (void *) (INT_PTR) -1 /* IG2LAElement::get_Value */ ,
    (void *) (INT_PTR) -1 /* IG2LAElement::put_Value */ ,
    (void *) (INT_PTR) -1 /* IG2LAElement::Init */
};


static const PRPC_STUB_FUNCTION IG2LAElement_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2LAElementStubVtbl =
{
    &IID_IG2LAElement,
    &IG2LAElement_ServerInfo,
    13,
    &IG2LAElement_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IG2Symbol, ver. 0.0,
   GUID={0xB2E73BD0,0xB965,0x4456,{0xB9,0xD0,0x8D,0x11,0xEA,0x69,0xD4,0x76}} */

#pragma code_seg(".orpc")
static const unsigned short IG2Symbol_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    1224,
    1260,
    1296,
    1332,
    4062,
    4098
    };

static const MIDL_STUBLESS_PROXY_INFO IG2Symbol_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Symbol_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2Symbol_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Symbol_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(13) _IG2SymbolProxyVtbl = 
{
    &IG2Symbol_ProxyInfo,
    &IID_IG2Symbol,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::get_WhatAmI */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::Duplicate */ ,
    (void *) (INT_PTR) -1 /* IG2Symbol::get_Item */ ,
    (void *) (INT_PTR) -1 /* IG2Symbol::put_Item */ ,
    (void *) (INT_PTR) -1 /* IG2Symbol::get_UpperCase */ ,
    (void *) (INT_PTR) -1 /* IG2Symbol::put_UpperCase */
};


static const PRPC_STUB_FUNCTION IG2Symbol_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2SymbolStubVtbl =
{
    &IID_IG2Symbol,
    &IG2Symbol_ServerInfo,
    13,
    &IG2Symbol_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IG2ItemRef, ver. 0.0,
   GUID={0x3862DC96,0xAF87,0x48C9,{0x9C,0x14,0x0F,0x2D,0x5A,0x4B,0x72,0x50}} */

#pragma code_seg(".orpc")
static const unsigned short IG2ItemRef_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    1224,
    1260,
    4134,
    4176,
    1740,
    1776,
    4218
    };

static const MIDL_STUBLESS_PROXY_INFO IG2ItemRef_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2ItemRef_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2ItemRef_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2ItemRef_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(14) _IG2ItemRefProxyVtbl = 
{
    &IG2ItemRef_ProxyInfo,
    &IID_IG2ItemRef,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::get_WhatAmI */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::Duplicate */ ,
    (void *) (INT_PTR) -1 /* IG2ItemRef::Init */ ,
    (void *) (INT_PTR) -1 /* IG2ItemRef::Git */ ,
    (void *) (INT_PTR) -1 /* IG2ItemRef::get_UUID */ ,
    (void *) (INT_PTR) -1 /* IG2ItemRef::put_UUID */ ,
    (void *) (INT_PTR) -1 /* IG2ItemRef::put_Gateway */
};


static const PRPC_STUB_FUNCTION IG2ItemRef_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2ItemRefStubVtbl =
{
    &IID_IG2ItemRef,
    &IG2ItemRef_ServerInfo,
    14,
    &IG2ItemRef_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IG2Workspace, ver. 0.0,
   GUID={0x986F5307,0x690C,0x4EF3,{0x91,0x73,0x7A,0x2A,0xE4,0x01,0x45,0x90}} */

#pragma code_seg(".orpc")
static const unsigned short IG2Workspace_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    1224,
    1260,
    1440,
    4254,
    4296,
    4326
    };

static const MIDL_STUBLESS_PROXY_INFO IG2Workspace_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Workspace_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2Workspace_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Workspace_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(13) _IG2WorkspaceProxyVtbl = 
{
    &IG2Workspace_ProxyInfo,
    &IID_IG2Workspace,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::get_WhatAmI */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::Duplicate */ ,
    (void *) (INT_PTR) -1 /* IG2Workspace::SubscribeToItemAddition */ ,
    (void *) (INT_PTR) -1 /* IG2Workspace::SubscribeToItemRemoval */ ,
    (void *) (INT_PTR) -1 /* IG2Workspace::UnsubscribeFromItemAddition */ ,
    (void *) (INT_PTR) -1 /* IG2Workspace::UnsubscribeFromItemRemoval */
};


static const PRPC_STUB_FUNCTION IG2Workspace_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2WorkspaceStubVtbl =
{
    &IID_IG2Workspace,
    &IG2Workspace_ServerInfo,
    13,
    &IG2Workspace_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IG2Window, ver. 0.0,
   GUID={0x2488BB94,0x3222,0x4D5D,{0x82,0x57,0x8D,0xD9,0x60,0x05,0x61,0xF5}} */

#pragma code_seg(".orpc")
static const unsigned short IG2Window_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    1224,
    1260,
    1440,
    4356,
    1740,
    1776
    };

static const MIDL_STUBLESS_PROXY_INFO IG2Window_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Window_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2Window_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2Window_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(13) _IG2WindowProxyVtbl = 
{
    &IG2Window_ProxyInfo,
    &IID_IG2Window,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::get_WhatAmI */ ,
    (void *) (INT_PTR) -1 /* G2ComObject::Duplicate */ ,
    (void *) (INT_PTR) -1 /* IG2Window::SubscribeToSelection */ ,
    (void *) (INT_PTR) -1 /* IG2Window::UnsubscribeFromSelection */ ,
    (void *) (INT_PTR) -1 /* IG2Window::get_g2UserMode */ ,
    (void *) (INT_PTR) -1 /* IG2Window::put_g2UserMode */
};


static const PRPC_STUB_FUNCTION IG2Window_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2WindowStubVtbl =
{
    &IID_IG2Window,
    &IG2Window_ServerInfo,
    13,
    &IG2Window_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IG2ComConfigurator, ver. 0.0,
   GUID={0x56E2306B,0x4F30,0x4249,{0x94,0xB0,0xB3,0xB9,0x64,0x7D,0xBC,0x3A}} */

#pragma code_seg(".orpc")
static const unsigned short IG2ComConfigurator_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    4386,
    4422
    };

static const MIDL_STUBLESS_PROXY_INFO IG2ComConfigurator_ProxyInfo =
    {
    &Object_StubDesc,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2ComConfigurator_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IG2ComConfigurator_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    G2Com__MIDL_ProcFormatString.Format,
    &IG2ComConfigurator_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(9) _IG2ComConfiguratorProxyVtbl = 
{
    &IG2ComConfigurator_ProxyInfo,
    &IID_IG2ComConfigurator,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IG2ComConfigurator::get_HighThroughput */ ,
    (void *) (INT_PTR) -1 /* IG2ComConfigurator::put_HighThroughput */
};


static const PRPC_STUB_FUNCTION IG2ComConfigurator_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IG2ComConfiguratorStubVtbl =
{
    &IID_IG2ComConfigurator,
    &IG2ComConfigurator_ServerInfo,
    9,
    &IG2ComConfigurator_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Standard interface: __MIDL_itf_G2Com_0000_0019, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    G2Com__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x700022b, /* MIDL Version 7.0.555 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _G2Com_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IG2WorkspaceProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IG2ItemProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IG2Gateway3ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IG2GatewayProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IG2Gateway2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_G2ComObjectProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IG2Gateway4ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IG2ComConfiguratorProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IG2WindowProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IG2ItemRefProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IG2StructureEntryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IG2Item3ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IG2Item4ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IG2LAElementProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IG2Item2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IG2SymbolProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IG2AttributeProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IG2StructureProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IG2ListOrArrayProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _G2Com_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IG2WorkspaceStubVtbl,
    ( CInterfaceStubVtbl *) &_IG2ItemStubVtbl,
    ( CInterfaceStubVtbl *) &_IG2Gateway3StubVtbl,
    ( CInterfaceStubVtbl *) &_IG2GatewayStubVtbl,
    ( CInterfaceStubVtbl *) &_IG2Gateway2StubVtbl,
    ( CInterfaceStubVtbl *) &_G2ComObjectStubVtbl,
    ( CInterfaceStubVtbl *) &_IG2Gateway4StubVtbl,
    ( CInterfaceStubVtbl *) &_IG2ComConfiguratorStubVtbl,
    ( CInterfaceStubVtbl *) &_IG2WindowStubVtbl,
    ( CInterfaceStubVtbl *) &_IG2ItemRefStubVtbl,
    ( CInterfaceStubVtbl *) &_IG2StructureEntryStubVtbl,
    ( CInterfaceStubVtbl *) &_IG2Item3StubVtbl,
    ( CInterfaceStubVtbl *) &_IG2Item4StubVtbl,
    ( CInterfaceStubVtbl *) &_IG2LAElementStubVtbl,
    ( CInterfaceStubVtbl *) &_IG2Item2StubVtbl,
    ( CInterfaceStubVtbl *) &_IG2SymbolStubVtbl,
    ( CInterfaceStubVtbl *) &_IG2AttributeStubVtbl,
    ( CInterfaceStubVtbl *) &_IG2StructureStubVtbl,
    ( CInterfaceStubVtbl *) &_IG2ListOrArrayStubVtbl,
    0
};

PCInterfaceName const _G2Com_InterfaceNamesList[] = 
{
    "IG2Workspace",
    "IG2Item",
    "IG2Gateway3",
    "IG2Gateway",
    "IG2Gateway2",
    "G2ComObject",
    "IG2Gateway4",
    "IG2ComConfigurator",
    "IG2Window",
    "IG2ItemRef",
    "IG2StructureEntry",
    "IG2Item3",
    "IG2Item4",
    "IG2LAElement",
    "IG2Item2",
    "IG2Symbol",
    "IG2Attribute",
    "IG2Structure",
    "IG2ListOrArray",
    0
};

const IID *  const _G2Com_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _G2Com_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _G2Com, pIID, n)

int __stdcall _G2Com_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _G2Com, 19, 16 )
    IID_BS_LOOKUP_NEXT_TEST( _G2Com, 8 )
    IID_BS_LOOKUP_NEXT_TEST( _G2Com, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _G2Com, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _G2Com, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _G2Com, 19, *pIndex )
    
}

const ExtendedProxyFileInfo G2Com_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _G2Com_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _G2Com_StubVtblList,
    (const PCInterfaceName * ) & _G2Com_InterfaceNamesList,
    (const IID ** ) & _G2Com_BaseIIDList,
    & _G2Com_IID_Lookup, 
    19,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

