/*******************************************************************************
:
:  gw_main.c  --  The main for gw.
:
:  This is linked with modules translated from Lisp in a branch based on GSI 4.
:  This file is only used in the C version of gw; when gw runs in Lisp, this
:  file is not loaded in.
:
:.............................................................................*/

#include <stdio.h>
#include "gw_main.h"


long gw_suppress_allocation_messages ()
{
  GC_SILENCE = (void *)1; /* Lisp 0, (non-NIL, so supresses allocation messages) */
  return 0L;
}


long gw_allow_allocation_messages ()
{
  GC_SILENCE = (void *)0; /* Lisp NIL, (NIL, so allows allocation messages) */
  return 0L;
}


void gsi_set_up()
{
    GSI_INSTALL_ERROR_HANDLER(&GW_ERROR_HANDLER);
    gsi_clear_last_error();

    GSI_RPC_DECLARE_LOCAL(zgw_configure_bridge,
			  "ZGW-CONFIGURE-BRIDGE");
    GSI_RPC_DECLARE_LOCAL(zgw_ping,
			  "ZGW-PING");
    GSI_RPC_DECLARE_LOCAL(zgw_kill_bridge,
			  "ZGW-KILL-BRIDGE");
    GSI_RPC_DECLARE_LOCAL(zgw_decline_to_serve_url,
			  "ZGW-DECLINE-TO-SERVE-URL");
    GSI_RPC_DECLARE_LOCAL(zgw_set_url_reply_charset,
			  "ZGW-SET-URL-REPLY-CHARSET");
    GSI_RPC_DECLARE_LOCAL(zgw_add_to_url_reply,
			  "ZGW-ADD-TO-URL-REPLY");
    GSI_RPC_DECLARE_LOCAL(zgw_finish_url_reply,
			  "ZGW-FINISH-URL-REPLY");
    GSI_RPC_DECLARE_LOCAL(zgw_get_attribute_of_request,
			  "ZGW-GET-ATTRIBUTE-OF-REQUEST");
    GSI_RPC_DECLARE_LOCAL(zgw_start_http_server,
			  "ZGW-START-HTTP-SERVER");
    GSI_RPC_DECLARE_LOCAL(zgw_tender_resources, 
			  "ZGW-TENDER-RESOURCES");
    GSI_RPC_DECLARE_LOCAL(zgw_make_base64_encoded, 
			  "ZGW-MAKE-BASE64-ENCODED");
    GSI_RPC_DECLARE_LOCAL(zgw_set_header_field, 
			  "ZGW-SET-HEADER-FIELD");
}

/*-----  Define Glue for RPC from Bridge to G2   -----*/

/* rpc_start_for_gw_request_for_url */
gsi_int info_for_gw_request_for_url;

void rpc_start_for_gw_request_for_url(arg_array)
gsi_rpc_arg   arg_array[];
{
  gsi_rpc_start(info_for_gw_request_for_url,
		arg_array,
		current_context);
}


/*----- initialize_context installs each Bridge->G2 RPC info -----*/

gsi_int gsi_initialize_context(remote_process_init_string, length)
    char    *remote_process_init_string;
    gsi_int  length;
{
  { /* a good time to recheck authorization */
    if ( !periodic() ) SHUTDOWN_REQUESTED = 2;
  }
  

  { /* Give Lisp a chance. */
    INNER_INITIALIZE_CONTEXT();
  }

  return(GSI_ACCEPT);
}



/* Return the letter to go in I.JxK for release quality. */
char release_quality_char (release_quality)
   gsi_int release_quality;
{
  switch (release_quality) {
  case GSI_PROTOTYPE_RELEASE_QUALITY:
    return 'p';
  case GSI_ALPHA_RELEASE_QUALITY:
    return 'a';
  case GSI_BETA_RELEASE_QUALITY:
    return 'b';
  }
  /* default to "customer release quality" */
  return 'r';
}


int main(argc, argv)
    int   argc;
    char *argv[];
{
  int result = 0;
  int authorized;
  gsi_version_id v_id;

  char version_string[100];

  fclose(stdin); /* See note a */

  /* Mimic the example code */
  GSI_SET_OPTIONS_FROM_COMPILE();

  gw_flush_console_streams();

  /* Initialize GSI */
  gsi_set_option(GSI_ONE_CYCLE);
  gsi_start(argc, argv);
  if (gsi_last_error() != 0) {
    return 1;
  }

  /* get and format version as I.JxK.  This has to go after gsi_start. */
  gsi_version_information(&v_id);
  sprintf(version_string, "V%d.%d%c%d", v_id.major_version, v_id.minor_version, release_quality_char(v_id.release_quality), v_id.revision_number);

  /* Check authorization */
  authorized = stage1( "G2-WebLink", version_string);

  if (authorized) {
    authorized = stage2();
  }

  if (!authorized) {
    exit(1);
  }

  /* Initialize the bridge */
  STARTUP_BRIDGE();
      
  /*  Main Loop */
  SHUTDOWN_REQUESTED = 0;
  while (SHUTDOWN_REQUESTED == 0 && result == 0) {
    gsi_clear_last_error();
    gsi_run_loop();
    /* Ignore errors? */
    if(result = gsi_last_error()){
      printf("\nIgnoring error %d?\n",result);
      gw_flush_console_streams();
      result = 0;
    }
    /* Feed threads */
    KICK_BRIDGE_TASKS();
    /* Sleep a second or take an I/O event */
    gsi_pause();
  } /* end while */

  /* Bridge Shutdown */
  gw_flush_console_streams();
  SHUTDOWN_BRIDGE();
  if (SHUTDOWN_REQUESTED == 2) {
    printf("\nShutdown: lost authorization\n");
  } else {
    printf("\nShutdown\n");
  }
  gw_flush_console_streams();
  return result;

} /* end main */


/* Note a: Close stdin! Guard against select spining on it.
 * we don't read from it. */

/* Note b: Force all files to be opened in raw binary mode,
 * so control z and line terminator rewrites don't happen. */


/* Support routines in C for Bridge authors writing in Lisp, i.e. lgsi */

/* g2int_gsi_rpc_declare_remote_1 returns the handle used to call this later.
   It disregards any errors, but I don't see how any can occur.
   */

void lgsi_rpc_declare_remote_1(function_name, number_of_args, number_of_return_values)
	char * function_name;
	int number_of_args;
	int number_of_return_values;
{
  int *handle_of_remote_procedure;
  extern /* Object */ int * G2int_temp_for_declare_remote;

  gsi_rpc_declare_remote((void *)&handle_of_remote_procedure,
			 function_name,
			 NULL, /* return handler... */
			 number_of_args,
			 number_of_return_values,
			 current_context);
  G2int_temp_for_declare_remote = (/* Object */ int*)handle_of_remote_procedure;
}

#ifdef WIN32
/* HQ-4951692 "GSI on Win32 should not start if not initialized"
   Turns out GSI initialization is not the same in GW and GSI.
   So stub this out for now.  Perhaps we should make them the same
   sometime in the future.   yduJ, 5/6/05 */

int g2pvt_win32_initialized_p = 0;

DLLEXPORT void gsi_initialize_for_win32(hInstance, lpCmdLine)
HANDLE hInstance;
char * lpCmdLine;
{
  g2pvt_win32_initialized_p = 1;
}

#endif

/*************************************************************
 * gsi_init_standard_callbacks
 *
 * This function is a copied directly from gsi/c/stdcbs.c.  That file provides
 * only this one function, and exists only because in order to make the function
 * a no-op when building the dll.  (stdcbs.obj is not part of gsi.dll.)  We
 * could check in stdcbs.c into gw/c, but since we only want to link statically,
 * I see no reason to add another file here.  When part of GSI, this function
 * would normally go in gsiannex.c; in fact, its only caller and its only callee
 * are both in gsiannex.c.  I could insert it there for gw, but I want
 * gsiannex.c to be as similar as possible in both gsi and gw.  
 * -jv, 10/20/03, yduJ 3/25/04
 *************************************************************/

void gsi_init_standard_callbacks()
{GSI_INITIALIZE_STANDARD_CALLBACKS;}
