/************************************************************************************/
/* Startup Code												    					*/
/*																					*/
/* This file contains the startup code.  							            	*/
/************************************************************************************/
#include <iostream_ver.h>
#include <stdlib.h> 
#include <string.h>                          
#include <stdio.h>

#if defined( WIN32 )
#	include <windows.h>
#	include <windowsx.h>
#endif

#include "gsi_main_cpp.h"
#include "corba_main.h"
#include "iiop.h"
#include "error_handler.h"

extern "C" {
#include "yacc_supp.h"	//For compiler debug enable.
/* temp hack used to disable GSI memory messages */
extern void *g2rtl_Gc_silence;
}

#define BRIDGE_NAME     "G2-CORBALink"
#ifndef G2KB_VER
// should be of format "10r4", i.e., -DG2KB_VER=\"10r4\"
#error  Required g2orb.kb version (G2KB_VER) not specified!
#endif

#ifndef G2KB_IDL_VER
// should be of format "10r4", i.e., -DG2KB_IDL_VER=\"10r4\"
#error  Required g2idl.kb version (G2KB_IDL_VER) not specified!
#endif

/* build code (e.g. HJ13) will be determined at runtime */

/* Bridge version must be supplied as a preprocessor definition
in format: 6_0B0 or 6_1R0. Also, a build code may be specified 
e.g. 6_1R0_H07 */
#ifndef CORBALINK_VER
#error  Version (CORBALINK_VER) not specified!
#endif

#ifndef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM ""
#endif
#ifdef mips
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "DECStation/Ultrix"
#endif
#if (defined(sun4) || defined(sparc))
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "Sun SparcStation"
#endif                                                                   
#ifdef sparcsol
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "SparcStation/Solaris"
#endif
#ifdef vms
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "Vax/OpenVMS"
#endif
#ifdef __alpha
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "Alpha/OpenVMS"
#endif
#if defined(hp9000s700) || defined(hp9000s800)
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "HP9000s700"
#ifndef hpux
#define hpux
#endif
#endif
#ifdef _IBMR2
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "IBM RS6000"
#endif
#ifdef alphaosf
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "Alpha/OSF"
#endif
#ifdef linux
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "Linux"
#endif
#if (defined(WIN32) && !defined(__alpha)) || defined(intelnt)
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "Windows"
#endif
#if (defined(WIN32) && defined(__alpha)) || defined(alphant)
#undef BRIDGE_PLATFORM
#define BRIDGE_PLATFORM "Alpha Windows NT"
#endif


G2String hostname;
unsigned hostport = 0;

//  Clean bridge shutdown for profiling

void g2orb_die( void *proc_data, gsi_item args[], gsi_int count, void *call_index)

{
	cout << "Exiting by command from G2" << endl;
	exit(1);
}


//
// Set connection timeout
//
void g2orb_set_conn_timeout(void *proc_data, gsi_item args[], gsi_int count, void *call_index)

{
	idle_timeout = gsi_int_of(args[0]);
	connect_timeout = gsi_int_of(args[1]);
	gsi_rpc_return_values(NULL, 0, call_index, current_context);
}

//
// Set server timeout
//
void g2orb_set_server_req_timeout(void *proc_data, gsi_item args[], gsi_int count, void *call_index)

{
	client_timeout = gsi_int_of(args[0]);
	gsi_rpc_return_values(NULL, 0, call_index, current_context);
}

//
// Set client timeout
//
void g2orb_set_client_req_timeout(void *proc_data, gsi_item args[], gsi_int count, void *call_index)

{
	server_timeout = gsi_int_of(args[0]);
	gsi_rpc_return_values(NULL, 0, call_index, current_context);
}


//
// Get the version of the bridge
//
// NOTE:  NOTE: NOTE: NOTE:
// We will change the way this is done for the next major release
//

void g2orb_get_ver(void *proc_data, gsi_item args[], gsi_int count, void *call_index)

{
	gsi_item *ret = gsi_make_items(1);
	gsi_set_str(ret[0], G2KB_VER);
	gsi_rpc_return_values(ret, 1, call_index, current_context);
//	gsi_reclaim_items(ret);
	deep_reclaim_items(ret, 1);
}

void g2orb_get_idl_ver(void *proc_data, gsi_item args[], gsi_int count, void *call_index)

{
	gsi_item *ret = gsi_make_items(1);
	gsi_set_str(ret[0], G2KB_IDL_VER);
	gsi_rpc_return_values(ret, 1, call_index, current_context);
//	gsi_reclaim_items(ret);
	deep_reclaim_items(ret, 1);
}


//
// Register that this context has a locator
//

void g2orb_set_locator(void *proc_data, gsi_item args[], gsi_int count, void *call_index)

{
	int i = gsi_int_of(args[0]);
	G2OrbContext *cObj = (G2OrbContext *) ContextObjs.FindObj(current_context);
	if (cObj) cObj->has_locator = i;
	gsi_rpc_return_values(args, 0, call_index, current_context);
}

//
// set the principal for this context
//
void g2orb_set_principal(void *proc_data, gsi_item args[], gsi_int count, void *call_index)

{
	char* principal = gsi_str_of(args[0]);

    if (principal != NULL)
    {
	    G2OrbContext *cObj = (G2OrbContext *)ContextObjs.FindObj(
                              current_context);
	    if (cObj != NULL)
            cObj->principal = principal;
    }

	gsi_rpc_return_values(args, 0, call_index, current_context);
}

// Startup GSI

void gsi_set_up()
{
  /* temp hack used to disable GSI memory messages */
	g2rtl_Gc_silence = (void *)0;

  // IDL files & compiler
	gsi_rpc_declare_local( g2idl_pre_scan_file, NULL, "_G2IDL-PRE-SCAN-FILE-RPC");
	gsi_rpc_declare_local( g2idl_compile_idl, NULL, "_G2IDL-COMPILE-IDL-RPC");

  // ORB Object registration
	gsi_rpc_declare_local( g2orb_send_req, NULL, "_G2ORB-SEND-REQ-RPC");
	gsi_rpc_declare_local( g2orb_reg_obj, NULL,"_G2ORB-REG-OBJ-RPC");
	gsi_rpc_declare_local( g2orb_dereg_obj, NULL, "_G2ORB-DEREG-OBJ-RPC");
	gsi_rpc_declare_local( g2orb_reg_proxy, NULL, "_G2ORB-REG-PROXY-RPC");
	gsi_rpc_declare_local( g2orb_dereg_proxy, NULL, "_G2ORB-DEREG-PROXY-RPC");
	gsi_rpc_declare_local( g2orb_download_ir, NULL,"_G2ORB-DOWNLOAD-IR-RPC");
	gsi_rpc_declare_local( g2orb_object_to_string, NULL, "_G2ORB-OBJECT-TO-STRING-RPC");
	gsi_rpc_declare_local( g2orb_decode_user_ref, NULL, "_G2ORB-DECODE-REF-RPC");


  // ORB configuration
	gsi_rpc_declare_local( g2orb_set_client_req_timeout, NULL, "_G2ORB-SET-CTIMEOUT-RPC");
	gsi_rpc_declare_local( g2orb_set_server_req_timeout, NULL, "_G2ORB-SET-STIMEOUT-RPC");
	gsi_rpc_declare_local( g2orb_set_conn_timeout, NULL, "_G2ORB-SET-CONN-TIMEOUT-RPC");
	gsi_rpc_declare_local( g2orb_get_ver, NULL, "_G2ORB-GET-VER-RPC");
    gsi_rpc_declare_local( g2orb_get_idl_ver, NULL, "_G2ORB-GET-IDL-VER-RPC");
	gsi_rpc_declare_local( g2orb_set_principal, NULL, "_G2ORB-SET-PRINCIPAL-RPC");

  // ORB operations
	gsi_rpc_declare_local( g2orb_die, NULL, "_G2ORB-DIE-RPC");
	gsi_rpc_declare_local( g2orb_reg_g2, NULL, "_G2ORB-REG-G2-RPC");
	gsi_rpc_declare_local( g2orb_set_locator, NULL, "_G2ORB-SET-LOC-RPC");
	gsi_rpc_declare_local( g2orb_ping_rpc, NULL, "_G2ORB-PING-RPC");


    // Custom error handler
	gsi_set_option(GSI_SUPPRESS_OUTPUT) ;
	gsi_install_error_handler(error_handler) ;

  return;
} 


#ifdef WIN32
static char *versionInfo = NULL;

char *populate_version_info ()
{
  int len;
  DWORD junk;
  static char buf[128];

  if (versionInfo == NULL) {
    /* first, find out the filename from where we were launched */
    GetModuleFileName(NULL, buf, 128);
    
  /* now figure out about the actual version: first the size of the buffer we need */
    len = GetFileVersionInfoSize(buf, &junk);
    if (len <= 0)
      return NULL;
      
    /* now make the buffer */
    versionInfo = (char*)malloc(len);

    if (versionInfo <= 0)
      return NULL;

    /* and now retrieve the info */
    if (!GetFileVersionInfo(buf, 0, len, versionInfo))
      return NULL;
  }
  return versionInfo;
}
#endif

#ifndef BUILD_CODE
#define BUILD_CODE   "UNKNOWN"
#endif

void determine_build_code(char * build_code, int bufsize)
{
#ifndef WIN32
  strncpy(build_code, BUILD_CODE, bufsize);
#else
  char *versionstring;
  UINT iLen;

  if (populate_version_info()) {
    if (!VerQueryValue(versionInfo, "\\StringFileInfo\\040904b0\\Build ID", (LPVOID*)&versionstring, &iLen)) {
      build_code[0] = '\0';
    }
    else strncpy(build_code, versionstring, bufsize);
  } else build_code[0] = '\0';
#endif
}

/*
 * Main entry point.  This just sets some flags, runs some init code
 * and enters the main loop.
 */

int main(int argc, char **argv)

{
    char    bridge_name[15];
    char    bridge_version[30];
    char   *ptr1,*ptr2;
    char    corbalink_ver[20];
    char    maj_ver[3];
    char    min_ver[3];
    char    mod_ver[4];
    char    mod_char[10];
    char    build_ver[16];
    char    build_code[16];
    int     n;

//  process_common_bridge_argv(&argc, argv);

  if (argc < 3) {
	  cout << "Usage: " << argv[0] << " gsi_port " << " iiop_port" << endl;
	  exit(1);
  }
  if (argc == 4) {
    if (!strcmp(argv[3],"debug")) {
		debug_mode = 1;
		puts("Running in debug mode...");
	}
	else if( !strcmp(argv[3],"compiler_debug") )
		{
		compiler_debug_state = DEBUG_ON;
		cout << "\nCompiler Debug State Enabled...\n" << endl;
		}
  }

#ifdef hpux
  // The G++ compiler on the hp platform does not correctly initialize
  //    global constructors
  // This performs this init
  cout << "Performing HP specific Init" << endl;
  ContextObjs.ExplicitInit(50);
  RequestObjs.ExplicitInit(100);
  ServReqObjs.ExplicitInit(100);
  Sockets.ExplicitInit(100);
  Objects.ExplicitInit(100);
  SocketMaps.ExplicitInit(100);
  LocateReqObjs.ExplicitInit(100);
#endif

  unsigned port_number = atoi(argv[2]);
  if (!port_number) {
	  cout << "Invalid Port Number" << endl;
	  exit(1);
  }

/*
 *  Set the Bridge and version information.
 */
  min_ver[0] = 0;
  mod_ver[0] = 0;
  determine_build_code(build_code, sizeof (build_code) - 1);
  memset(build_ver, 0, sizeof (build_ver));
  if (strcmp(build_code,"") != 0) {
    strncpy(build_ver, build_code, sizeof (build_ver) - 1);
  }
  if (strcmp(CORBALINK_VER,"") != 0) {
    memset(corbalink_ver, 0, sizeof (corbalink_ver));
    strncpy(corbalink_ver,CORBALINK_VER, sizeof (corbalink_ver) - 1);
    ptr1 = corbalink_ver;
  }
  else {
    printf("\n\nBridge Version has not been specified (CORBALINK_VER).\n\n");
    return -1;
  }
  if (*ptr1 == 'V') ptr1++;
  ptr2 = maj_ver;
  n = 0;
  while (*ptr1 != 0) {
    *ptr2++ = *ptr1++;
    if (*ptr1 == '_' || *ptr1 == '-' || *ptr1 == '.') {
      *ptr2 = '\0';
      if (!min_ver[0])
        ptr2 = min_ver;
      else {
        if (!build_ver[0])
          ptr2 = build_ver;
        else
          break;
      }
      ptr1++;  
    }
    if (!mod_ver[0] && (*ptr1 == 'B' || *ptr1 == 'R' || *ptr1 == 'A') ) {
      *ptr2 = 0;
      if (*ptr1 == 'A') strcpy(mod_char,"Alpha Rev");
      if (*ptr1 == 'B') strcpy(mod_char,"Beta Rev");
      if (*ptr1 == 'R') strcpy(mod_char,"Rev");
      ptr1++;
      ptr2 = mod_ver;
    }
  }
  *ptr2 = 0;
  if (build_ver[0] == 0) {
    printf("\n\nBridge Build Code has not been specified.\n\n");
    return -1;
  }

  sprintf(bridge_name,BRIDGE_NAME);  
  sprintf(bridge_version,"%s.%s %s %s (%s)",maj_ver,min_ver,mod_char,mod_ver,build_ver);

  printf("\n--------------------------------------------------------\n");
  printf("Starting %s Bridge   Version %s\n for %s",
          bridge_name, bridge_version, BRIDGE_PLATFORM );
#ifdef PROTOTYPE
  printf("   (Prototype for: %s)",PROTOTYPE);
#endif
  printf("\n");
  printf("--------------------------------------------------------\n");
 
  if (debug_mode) {
	  cout << "Char: " << sizeof(char) << endl;
	  cout << "Short: " << sizeof(short) << endl;
	  cout << "Int: " << sizeof(int) << endl;
	  cout << "Long: " << sizeof(long) << endl;
	  cout << "Float: " << sizeof(float) << endl;
	  cout << "Double: " << sizeof(double) << endl;
#if NATURAL_CODING == G2C_LITTLE_ENDIAN
      cout << "Little Endian" << endl;
#else
      cout << "Big Endian" << endl;
#endif

  }

  gsi_include_file_major_version = GSI_INCLUDE_MAJ_VER_NUM;
  gsi_include_file_minor_version = GSI_INCLUDE_MIN_VER_NUM;
  gsi_include_file_revision_version = GSI_INCLUDE_REV_VER_NUM;
  gsi_set_option(GSI_ONE_CYCLE); /* Run in one cycle mode */
  gsi_set_option(GSI_STRING_CHECK); /* check for gensym special characters and
                                       add an escape character before them */
  gsi_set_option(GSI_USE_REFERENCES); // Ricks new reference api
  gsi_set_option(GSI_USER_DATA_FOR_CALLBACKS);
  if (debug_mode) 
    gsi_set_option(GSI_NO_SIGNAL_HANDLERS);

#ifndef WIN32
  sleep(1);  /* prevent lots of activity if we respawn */
#else
  gsi_initialize_for_win32((HANDLE)NULL, "corbalink") ;
#endif

  gsi_start(argc, argv); 
  create_listener(port_number);
 
  char buf[1024];
  if (gethostname(buf, 1024) != 0) {
	  cout << "Unable to get host name" << endl;
	  exit(1);
  }
  hostname = buf;
  hostport = port_number;
  if (debug_mode) {
	  cout << "Local address is " << (char *) hostname << ":" <<
		  hostport << endl;
  }

  main_loop();

  return 0 ;
}
