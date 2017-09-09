/*******************************************************************************

File name:               extensn.c
Owner:                   Peter Fandel

Purpose:                 This is the layer of software that interfaces between
                         the application layer, the ICP layer, and the network
                         layer - sort of a mixed bag.

Contents:                Extension Startup Functions - Functions called by GSI
                         and GSPAN application programmers to start and run an
                         interface to other ICP processes.
                         
                         ICP/Network Interface Functions - Functions that make
                         the proper calls into the network layer to support
                         requests from the extension startup functions and from
                         the application and ICP layers.

                         Context Functions - Functions that support the multi-
                         context capability of ICP.

                         Error Handling Functions - Functions that report
                         errors, warnings, and messages.

                         Supporting Functions - Functions that support the 
                         above categories of function.

This file depends on:    icp.c for ICP message receiver functions, networks.c 
                         for network stuff, and other modules particular to
                         individual extensions e.g. gsi.c and rpc.c for GSI.

Dependent files:         Any ICP extension bridge application.

Legal Notice:            Copyright (C) 1986-2017 Gensym Corporation.,
                         125 CambridgePark Drive, Cambridge MA 02140
                         All rights reserved.

History:                 See individual function headers.

Header files:            The following are include files required by this file.
                         The constant EXTERN_DEFINED is set to TRUE so as to
                         prevent some externs from being defined twice.       */

#define                  EXTERNS_DEFINED TRUE  /* Turn off part of icp.h.     */
#include                <string.h>
#ifndef WIN32
#  include                <stdlib.h>
#endif
#include                <errno.h>             /* Required for errno */
#include                "gensym-features.h"  /* Machine dependent stuff.    */
#include                "cprim.h"
#include                "networks.h"         /* Network support stuff.      */
#include                "icp.h"              /* Stuff required by all ICP
                                                  extension code.             */
#include                "icp_pvt.h"          /* Stuff required by all ICP
                                                  extensions internal code. 

Functions in this file:  All Categories
                         --------------                                       */
                         icp_int  extension_start();
                         icp_int  extension_listen();
                         icp_int  extension_run_loop();
                         icp_int  process_allocated_context();
                         icp_int  add_context();
                         icp_int  im_alive();
                         icp_int  msg_pending();
                         icp_int  process_icp_message_group();
                         icp_int  read_message_group();
                         icp_int  write_message_group();
                         icp_int  icp_flush();
                         void     undefine_context();
                         icp_int  ext_switch_context();
                         void     ext_error();
                         void     ext_message();
                         icp_int  ext_return_message();
                         void     ext_sleep();
                         void     ext_pause();
                         icp_int  context_active();
                         icp_int  find_next_context();
                         icp_int  send_icp_nop();
                         icp_int  arg_is_network_token();
                         icp_int  parse_medium();
                         icp_int  guess_medium();
                         void     init_icp_functions();
                         icp_int  null_icp();

/*
 * External function declarations for GSI Toolkit
 * Functions called from this module.
 */

extern gsi_int gsi_get_tcp_port();
extern gsi_int allow_ext_proc();
extern gsi_int InitUsrRpcs();
gsi_int byte_swap_temporary;

extern ffe_int get_version_info(char *version_buffer);
extern void init_icp_functions(void);
extern void load_icp_functions(void);
/* extern void fgn_event_loop (void); */
extern long g2ext_inetwork_listen(LISTENER_DEFAULTS *defaults, long product);
extern icp_int reclaim_used_blobs(void);
extern void wr_icp_str(char *string);
extern char *g2ext_string_to_uppercase(char *str);
extern long g2ext_sys_sleep(/* long */);
extern void g2ext_gensym_pause();
extern long g2_event_cycle (/* long */);


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION extension_start:                  Copyright (C) 1986-2017 Gensym Corporation
:
:  This function is available to ICP extension application programmers as a
:  toolkit function and its purpose is basically one of setup prior to the main
:  run loop being started.  One or two network listeners are opened, the user is
:  informed of the listener(s) opened, the context array is initialized, the ICP
:  message receiver functions are registered, and we segue to the main run loop.
:
:  Arguments:        argc  Count of command line arguments including program
:                          name.
:                    argv  Pointer to an array of char pointers, each pointing
:                          to an argument from the command line.
:  Return Behavior:  ICP_FAILURE if extension_run_loop() or extension_listen()
:                    fail.  Otherwise, return ICP_SUCCESS.
:  Users:            gsi.c:     gsi_start()
:                    gspan.c:   gspan_start()
:                    foreign.c: ffe_start()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  001  23mar95  paf        Added code to zero file descriptors used in the
:                           interruptable sleep mechanism.
:.............................................................................*/
icp_int extension_start(argc, argv)
    int   argc;
    char *argv[];
{
    extern long      g2ext_network_listener_count();
    extern long      g2ext_get_network_listener();
    register icp_int i, count;
    char             message_buffer1[128];

#ifdef DEBUG
    strcpy(where_in_extension,"extension_start");
    printf("%s\n",where_in_extension);
#endif

/*  Inform the operator of the version information for the extension.
    -----------------------------------------------------------------*/
    if (get_version_info(message_buffer1) != ICP_SUCCESS)
        exit(1);
    else
        ext_message(message_buffer1,NO_SEND);

/*  Initialize a linked list.  This is required
    because the network layer is shared.
    ------------------------------------------*/
    g2ext_initialize_g2pointers();

/*  Attempt to create listener(s) as specified by command line arguments.
    If we are unable to create a listener, exit the program entirely.
    ----------------------------------------------------------------------*/
    if (extension_listen(argc,argv) != ICP_SUCCESS)
        exit(1);

/*  Inform operator of the listeners that were opened.
    -----------------------------------------------------------*/
    ext_message("Waiting to accept a connection on:",NO_SEND);
    count = g2ext_network_listener_count();
    for (i=0; i<count; i++)
        if (g2ext_get_network_listener(i,message_buffer1, 128) > 0)
	    ext_message(message_buffer1,NO_SEND);

/*  Initialize the state of all contexts.
    ----------------------------------------*/
    for (i=0; i<MAX_CONTEXTS; i++)
        icp_context_table[i].state = INACTIVE;

/*  Initialize the global GSI function array, and register
    the ICP message receiver functions wityhin the array.
    ------------------------------------------------------*/
    init_icp_functions();
    load_icp_functions();
/*  load_icp_gwin_functions(); >>>>>>>>>>>>>>. Comment in for Gwin */

/*  Call user toolkit function that may be used to
    declare local functions for use by G2 via RPC.
    ----------------------------------------------*/
    InitUsrRpcs();

/*  Initialize the global context indicator,
    and call the main run loop for GSI.
    ---------------------------------------*/
    icp_current_context = 0;

    /* fgn_event_loop(); */
    for (;;) {
        g2_event_cycle(1); /* 1 means "wait allowed" */
    }

    return ICP_SUCCESS;
} /* end extension_start */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION extension_listen:                 Copyright (C) 1986-2017 Gensym Corporation
:
:  This function will parse the command line arguments and if appropriate
:  determine or even guess what listeners the user intended to open.
:
:  Arguments:        argc     Count of command line arguments including program
:                             name.
:                    argv     Pointer to an array of char pointers, each
:                             pointing to an argument from the command line.
:  Return Behavior:  ICP_FAILURE if the command line is invalid or if one of
:                    several subroutines fail.  Otherwise, return ICP_SUCCESS.
:  Users:            local: extension_start().
:  Memory Impact:    Direct -- malloc is called twice.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int extension_listen(argc,argv)
    int   argc;
    char *argv[];
{
    LISTENER_DEFAULTS *listeners;
    char               listener_arg1[30];
    char               listener_arg2[30];
    char              *listener_arg;
    icp_int            medium_arg1 = UNDEFINED;
    icp_int            medium_arg2 = UNDEFINED;
    icp_int           *medium_arg;
    icp_int            medium = ALL;
    icp_int            port_number = 0;
    char               object_name[30];
    char               msg_buff[256];
    icp_int            i, status;

#ifdef DEBUG
    strcpy(where_in_extension,"extension_listen");
    printf("%s\n",where_in_extension);
#endif

/*  Create a structure to hold the specification of the desired listeners,
    initialize argument pointers, and initialize strings as empty.
    ----------------------------------------------------------------------*/
    listeners = (LISTENER_DEFAULTS *) malloc(sizeof(LISTENER_DEFAULTS));
    if (listeners == NULL) {
        ext_error(NO_MORE_MEMORY,"extension_listen(1)",NO_DATA,NO_SEND);
        return(ICP_FAILURE); }
    listener_arg = &listener_arg1[0];
    medium_arg = &medium_arg1;
    listener_arg1[0] = 0;
    listener_arg2[0] = 0;
    object_name[0] = 0;

/*  Iterate through the command line arguments (skipping the program name)
    parsing out up to two listener strings and up to two medium specifiers.
    -----------------------------------------------------------------------*/
    for (i=1; i<argc; i++) {
        if (arg_is_network_token(argv[i])) {
            if (medium_arg == NULL_PTR) {
                ext_error(TOO_MANY_NETWORKS,"extension_listen",
                          NO_DATA,NO_SEND);
                goto PRINT_USAGE_AND_EXIT; }
            if (parse_medium(argv[++i],medium_arg) != ICP_SUCCESS)
                goto PRINT_USAGE_AND_EXIT;
            if (medium_arg == &medium_arg1) {
                medium_arg = &medium_arg2;
                if (listener_arg == &listener_arg1[0])
                    listener_arg = &listener_arg2[0]; }
            else if (medium_arg == &medium_arg2) {
                medium_arg = NULL_PTR;
                if (listener_arg == &listener_arg2[0])
                    listener_arg = NULL_PTR; }
            else {
                ext_error(INTERNAL_INCONSISTENCY,"extension_listen",
                          NO_DATA,NO_SEND);
                goto PRINT_USAGE_AND_EXIT; }
	} /* end if */

        else {
            if (listener_arg == NULL_PTR) {
                ext_error(TOO_MANY_LISTENERS,"extension_listen",
                          NO_DATA,NO_SEND);
                goto PRINT_USAGE_AND_EXIT; }
            strcpy(listener_arg,argv[i]);
            if (listener_arg == &listener_arg1[0])
                listener_arg = &listener_arg2[0];
            else if (listener_arg == &listener_arg2[0]) {
                listener_arg = NULL_PTR;
                if (medium_arg == &medium_arg1)
                    medium_arg = &medium_arg2; }
            else {
                ext_error(INTERNAL_INCONSISTENCY,"extension_listen(2)",
                          NO_DATA,NO_SEND);
                return(ICP_FAILURE); }
	} /* end else */
    } /* end for */

/*  If no network medium information was given, use corresponding
    listener information to guess at the intended medium.  Then,
    set local 'medium' to TCP_IP if no second medium
    was specified.  Note that 'medium' is ALL by default.  Finally,
    if two listeners were specified with the same medium, complain.
    ----------------------------------------------------------------*/
    if (medium_arg1 == UNDEFINED)
        medium_arg1 = guess_medium(listener_arg1);
    if (medium_arg2 == UNDEFINED)
        medium_arg2 = guess_medium(listener_arg2);
    if ((medium_arg2 == UNDEFINED) && (medium_arg1 != UNDEFINED))
        medium = medium_arg1;
    if ((medium_arg1 == medium_arg2) && (medium_arg1 != UNDEFINED)) {
        ext_error(INVALID_NETWORK_COMBO,"extension_listen",
                  NO_DATA,NO_SEND);
        goto PRINT_USAGE_AND_EXIT; }

/*  Set port_number and object_name from
    listener arguments using medium arguments.
    -------------------------------------------*/
    if (medium_arg1 == TCP_IP)
        port_number = atol(listener_arg1);
    if (medium_arg2 == TCP_IP)
        port_number = atol(listener_arg2);

/*  Fill out the listeners structure and return depending on the medium(s).
    ------------------------------------------------------------------------*/
    listeners->protocol = medium;
    switch(medium) {
        case TCP_IP:
            if (port_number == 0)
                port_number = gsi_get_tcp_port();
            if (port_number == 0)
                port_number = INTERNAL_DEFAULT_PORT;
            listeners->tcpip_max_iterations = 1;
	    listeners->exact_tcpip_port_required = 0;
            listeners->default_tcpip_listener = port_number;
            status = g2ext_inetwork_listen(listeners,GSI);
            if (status == NOOP_CODE_ATTEMPTED) {
                sprintf(msg_buff,"This executable wasn't linked to support TCP/IP.");
		ext_message(msg_buff,NO_SEND);
                return(ICP_FAILURE); }
            if (status == NETWORK_FAIL) {
                sprintf(msg_buff,
                      "%s: unable to find listener at %d on TCP/IP.",
                        argv[0], (int)port_number);
                ext_message(msg_buff,NO_SEND);
                return(ICP_FAILURE); }
            return(ICP_SUCCESS);

 	default:
            ext_error(INTERNAL_INCONSISTENCY,"extension_listen(3)",
                      NO_DATA,NO_SEND);
            return(ICP_FAILURE);
    } /* end switch */

PRINT_USAGE_AND_EXIT:

    sprintf(msg_buff,
           "usage:\n  > %s [<listener>] [-network tcpip] ",argv[0]);
    strcat(msg_buff,"[<listener>] [-network tcpip]\n");
    ext_message(msg_buff,NO_SEND);
    return(ICP_FAILURE);

} /* end extension_listen */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION extension_run_loop:               Copyright (C) 1986-2017 Gensym Corporation
:
:  This function is available to GSI application programmers as a toolkit
:  function although, unless the user has set ICP_ONE_CYCLE, the user program
:  never will call it directly.  This function is the main run loop for GSI,
:  managing the overall sequence of events but calling other functions to do
:  the real work.
:
:  Arguments:        None.
:  Return Behavior:  ICP_FAILURE if g2ext_get_next_connection(), add_context(), or
:                    process_icp_message_group() fail, or on internal 
:                    inconsistency.  Otherwise, return ICP_SUCCESS.
:  Users:            Undefined, but usually this is called from main().
:  Memory Impact:    Indirect --  add_context() may call malloc extensively.
:
:  Rev  Date     Author     Notes
:  001  15apr94  P. Fandel  Pulled out code into new function process_allocated
:                           _context().  Added code to support new run-time 
:                           switch, ICP_TRAP_NETWORK_ERRORS.
:.............................................................................*/
icp_int extension_run_loop()            
{
    icp_int           context, request_count, socket;
    register icp_int  i; 
    icp_int           status = ICP_SUCCESS;
    char              message[100];

#ifdef DEBUG
    strcpy(where_in_extension,"extension_run_loop");
    printf("%s\n",where_in_extension);
#endif

/*  Ensure we are not already within the extent of this function.
    --------------------------------------------------------------*/
    if (within_run_loop_extent) {
        ext_error(RUN_LOOP_NESTING,"extension_run_loop",NO_DATA,NO_SEND);
	return(ICP_FAILURE); }
    within_run_loop_extent = TRUE;

/*  Do the following at least once, and repeat while ICP_ONE_CYCLE is off.
    ----------------------------------------------------------------------*/
    do {

        if (icp_active_contexts == 0)

        /*  Sleeping is unconditionally enabled if no contexts are active.
            ---------------------------------------------------------------*/
            icp_sleep_enabled = TRUE;

        else

        /*  Process the allocated contexts.  If a failure occurs in the 
            processing of any context, exit the run loop UNLESS the user
            has set the option to trap network errors and the failure was
            an ICP network error.
            ---------------------------------------------------------------*/
            for (i=0; i<icp_allocated_contexts; i++) {
              status = process_allocated_context(i);
              if (status != ICP_SUCCESS)
                if (!(  ((last_extension_error == ICP_READ_ERROR) ||
                         (last_extension_error == ICP_WRITE_ERROR))
                       &&
                        (icp_option_is_set(ICP_TRAP_NETWORK_ERRORS))))
                  goto EXIT_LOOP;
                else
                  status = ICP_SUCCESS;
            } /* end for */

    /*  Set up for any new connections that were accepted
        ---------------------------------------------------*/
        if((request_count = g2ext_network_accept()) < 0) {
            ext_error(NETWORK_ACCEPT_FAILED,"extension_run_loop, status",
                      request_count,NO_SEND);
            status = ICP_FAILURE; }
        if (request_count > 0)
            for (i=0; i<request_count; i++) {
	        socket = g2ext_get_next_connection();
                if (socket == INVALID_SOCKET) {
                  ext_error(GET_SOCKET_FAILED,"extension_run_loop",
                            NO_DATA,NO_SEND);
                  status = ICP_FAILURE; } /* end if */
                else {
	          if (add_context(socket,&context,CLIENT) != ICP_SUCCESS) {
	            if (g2ext_network_close(socket) == NETWORK_FAIL)
                       ext_error(CLOSE_SOCKET_FAILED,"extension_run_loop",
                                 NO_DATA,NO_SEND);
                    status = ICP_FAILURE; }
	          sprintf(message,
                         "Connection accepted - context %d", (int)context);
	          ext_message(message,NO_SEND); } /* end else */
                if (status != ICP_SUCCESS)
                  goto EXIT_LOOP;
            } /* end for */

    /*  Go to sleep if sleeping is enabled
        and ICP_ONE_CYCLE has not been set.
        -------------------------------------*/
        if (icp_sleep_enabled && (!icp_option_is_set(ICP_ONE_CYCLE)))
            ext_sleep();

    } while ((!icp_option_is_set(ICP_ONE_CYCLE)) && (status == ICP_SUCCESS));

EXIT_LOOP:

/*  Outside of the run loop, context is undefined.  This forces the user to
    explicitly select a context if any return function or RPC related functions
    are called while outside the run loop.  Otherwise icp_current_context would be,
    unpredictably, the last context we were in - sometimes an inactive one.
    -------------------------------------------------------------------------*/
    ext_switch_context(UNDEFINED_CONTEXT);

    within_run_loop_extent = FALSE;
    if (status != ICP_SUCCESS)
        return(ICP_FAILURE);
    else
        return(ICP_SUCCESS);

} /* end extension_run_loop */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION process_allocated_context:        Copyright (C) 1986-2017 Gensym Corporation
:
:  This function, for a context which it determines to be active, switches to 
:  that context, tells G2 I'm alive if it has been a while, calls allow_ext_
:  proc() if the user has mandated thus, processes any pending ICP message
:  group, and reclaims any blobs (managed arrays from one of the pools in the 
:  pool array). Sleeping gets disabled when messages need processing.  Sleeping 
:  is re-enabled when things quiet down.
:
:  Arguments:        context            Context to process.
:  Return Behavior:  ICP_FAILURE upon failure of any sub-parts.  Otherwise, 
:                    return ICP_SUCCESS.
:  Users:            local:    extension_run_loop()
:  Memory Impact:    Indirect -- malloc may be called extensively.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int process_allocated_context(context)
    icp_int  context;
{

#ifdef DEBUG
    strcpy(where_in_extension,"process_allocated_context");
    printf("  %s\n",where_in_extension);
#endif

    if (context_active(context)) {

      if (ext_switch_context(context) != ICP_SUCCESS)
        return(ICP_FAILURE);
      if (im_alive(&icp_context_table[context]) != ICP_SUCCESS)
        return(ICP_FAILURE);
      if (curr_ctx->do_ext_proc == TRUE)
        if (allow_ext_proc() != ICP_SUCCESS)
          return(ICP_FAILURE);
      if (msg_pending(&icp_context_table[context]) == TRUE) {
        icp_sleep_enabled = FALSE;
	icp_context_table[context].received_data = TRUE;
        if (process_icp_message_group(&icp_context_table[context])
                                                            != ICP_SUCCESS)
          return(ICP_FAILURE);
        else
          icp_sleep_enabled = TRUE;
      } /* end if msg_pending */
      else
	icp_context_table[context].received_data = FALSE;

      reclaim_used_blobs();

    } /* end if active context */

    return(ICP_SUCCESS);

} /* end process_allocated_context */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION add_context:                      Copyright (C) 1986-2017 Gensym Corporation
:
:  This function adds a new context either by allocating memory for new a bunch
:  of new structures to support the context, or by re-using structures freed by
:  the previous shutting down of another context.
:
:  Arguments:        socket       The socket handle to which the new context 
:                                 will correspond.
:                    context_ptr  Pointer to a value to contain the new context.
:                    partner_type CLIENT, G2_SERVER, or GSI_SERVER.
:  Return Behavior:  ICP_FAILURE if any memory allocation fails, or if no more
:                    contexts are available.  Otherwise, return ICP_SUCCESS.
:  Users:            local:       extension_run_loop()
:                    rpcstubs.c:  make_icp_connection() (GSI to GSI stuff)
:                    gsig2.c:     gsi_make_g2_connection() (more subversive stuff).
:  Memory Impact:    Direct -- malloc may be called extensively.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int add_context(socket,context_ptr,partner_type)
    icp_int   socket;
    icp_int  *context_ptr;
    icp_int   partner_type;
{
    icp_int new_context;
    char    message[100];

#ifdef DEBUG
    strcpy(where_in_extension,"add_context");
    printf("  %s\n",where_in_extension);
#endif

/*  Determine the next available context, and complain if no more
    are available.  Set contents of context_ptr to new context.
    ---------------------------------------------------------------*/
    new_context = find_next_context();
    if (new_context > MAX_CONTEXTS) {
        ext_error(NO_MORE_CONTEXTS,"add_context, max",MAX_CONTEXTS,NO_SEND);
        return(ICP_FAILURE); }
    *context_ptr = new_context;

/*  If the state of this context is not marked for recycling, no memory has
    been allocated to support it, and we must malloc a mountain of memory.
    -----------------------------------------------------------------------*/
    if (icp_context_table[new_context].state != RE_USE) {

    /*  Allocate memory for the read buffer into which the incoming
        ICP message group is placed to await processing.
        If unable, complain and back out of any commitments.
        --------------------------------------------------------*/
        if ((icp_context_table[new_context].read_buff = (icp_byte *) 
                             malloc(BUFFER_SIZE * ICP_BYTE_SIZE)) == NULL_PTR) {
          ext_error(NO_MORE_MEMORY,"add_context(read_buff)",NO_DATA,NO_SEND);
          icp_context_table[new_context].state = INACTIVE;
          return(ICP_FAILURE); }

    /*  Allocate memory for the write buffer into which the incoming
        ICP message group is placed to await processing.
        If unable, complain and back out of any commitments.
        --------------------------------------------------------*/
        if ((icp_context_table[new_context].write_buff = (icp_byte *) 
                             malloc(BUFFER_SIZE * ICP_BYTE_SIZE)) == NULL_PTR) {
          ext_error(NO_MORE_MEMORY,"add_context(write_buff)",NO_DATA,NO_SEND);
          icp_context_table[new_context].state = INACTIVE;
          free(icp_context_table[new_context].read_buff);
          return(ICP_FAILURE); }


    /*  Allocate memory for the object buffer used by gsi_get_data(),
        gsi_set_data() and gsi_stop_data().  If unable, complain and back
        out of any commitments.  If able, initialize the new structure.
        -----------------------------------------------------------------*/
        if ((icp_context_table[new_context].object_buff = 
            (obj_type *) malloc(OBJ_BUFF_LEN * sizeof(obj_type))) == NULL_PTR) {
          ext_error(NO_MORE_MEMORY,"add_context(object_buff)",NO_DATA,NO_SEND);
          icp_context_table[new_context].state = INACTIVE;
          free(icp_context_table[new_context].read_buff);
          free(icp_context_table[new_context].write_buff);
          return(ICP_FAILURE); }
        else
          memset((void *) icp_context_table[new_context].object_buff,
	         (int)    0,
	         (size_t) (OBJ_BUFF_LEN * sizeof(obj_type)));
    
    /*  Allocate memory for the export table used to store objects
        that correspond to those in another ICP process.  If unable,
        complain and back out of any commitments.  If able, initialize.
        ----------------------------------------------------------------*/
        if ((icp_context_table[new_context].export_tbl = (corr_obj_type *) 
             malloc(icp_max_export_objs * sizeof(corr_obj_type))) == NULL_PTR) {
          ext_error(NO_MORE_MEMORY,"add_context(export_tbl)",NO_DATA,NO_SEND);
	  free(icp_context_table[new_context].read_buff);
	  free(icp_context_table[new_context].write_buff);
	  free(icp_context_table[new_context].object_buff);
	  return(ICP_FAILURE); }
        else
          memset((void *) icp_context_table[new_context].export_tbl,
	         (int)    0,
	         (size_t) (icp_max_export_objs * sizeof(corr_obj_type)));
    
    /*  Allocate memory for the RPC table used to store info regarding
        procedures in other ICP processes accessible by me via RPC.  If unable,
        complain and back out of any commitments.  If able, initialize.
        --------------------------------------------------------------------*/
        if ((icp_context_table[new_context].remote_proc_tbl = (remote_proc *)
                 malloc(MAX_REMOTE_PROCS * sizeof(remote_proc))) == NULL_PTR) {
          ext_error(NO_MORE_MEMORY,"add_context(rpc_tbl)",NO_DATA,NO_SEND);
          free(icp_context_table[new_context].read_buff);
          free(icp_context_table[new_context].write_buff);
          free(icp_context_table[new_context].object_buff);
          free(icp_context_table[new_context].export_tbl);
          return(ICP_FAILURE); }
        else
          memset ((void *) icp_context_table[new_context].remote_proc_tbl,
	          (int)    0,
	          (size_t) (MAX_REMOTE_PROCS * sizeof(remote_proc)));

    /*  Allocate memory for the import table used to store objects
        imported from other ICP processes.  If unable,  complain
        and back out of any commitments.  If able, initialize.
        --------------------------------------------------------------*/
        if ((icp_context_table[new_context].import_tbl = (corr_obj_type *) 
             malloc(icp_max_import_objs * sizeof(corr_obj_type))) == NULL_PTR) {
          ext_error(NO_MORE_MEMORY,"add_context(import_tbl)",NO_DATA,NO_SEND);
          free(icp_context_table[new_context].read_buff);
          free(icp_context_table[new_context].write_buff);
          free(icp_context_table[new_context].object_buff);
          free(icp_context_table[new_context].export_tbl);
          free(icp_context_table[new_context].remote_proc_tbl);
          return(ICP_FAILURE); }
        else
          memset ((void *) icp_context_table[new_context].import_tbl,
	          (int)    0,
	          (size_t) (icp_max_import_objs * sizeof(corr_obj_type)));

    /*  Allocate memory for the RPC return buffer used to pass a receiver
        function arguments returned by a G2 (or other GSI) procedure that
        was called via RPC.  If unable, complain and back out of any
        commitments.  If able, initialize.
        ------------------------------------------------------------------*/
        if ((icp_context_table[new_context].rpc_ret_buff = (rpc_arg_type *)
                      malloc(MAX_NO_ARGS * sizeof(rpc_arg_type))) == NULL_PTR) {
          ext_error(NO_MORE_MEMORY,"add_context(rpc_ret_buff)",NO_DATA,NO_SEND);
          free(icp_context_table[new_context].read_buff);
          free(icp_context_table[new_context].write_buff);
          free(icp_context_table[new_context].object_buff);
          free(icp_context_table[new_context].export_tbl);
          free(icp_context_table[new_context].remote_proc_tbl);
          free(icp_context_table[new_context].import_tbl);
          return(ICP_FAILURE); }
        else
          memset ((void *) icp_context_table[new_context].rpc_ret_buff,
	          (int)    0,
	          (size_t) (MAX_NO_ARGS * sizeof(rpc_arg_type)));
  
    /*  Allocate memory for the RPC name table used to register procedures
        from other ICP processes so that I can call them via RPC.  If unable,
        complain and back out of any commitments.  If able, initialize.
        ------------------------------------------------------------------*/
        if ((icp_context_table[new_context].rp_def_tbl = (rp_def_struct *)
                malloc(MAX_REMOTE_PROCS * sizeof(rp_def_struct))) == NULL_PTR) {
          ext_error(NO_MORE_MEMORY,"add_context(rpc_name_tbl)",NO_DATA,NO_SEND);
          free(icp_context_table[new_context].read_buff);
          free(icp_context_table[new_context].write_buff);
          free(icp_context_table[new_context].object_buff);
          free(icp_context_table[new_context].export_tbl);
          free(icp_context_table[new_context].remote_proc_tbl);
          free(icp_context_table[new_context].import_tbl);
          free(icp_context_table[new_context].rpc_ret_buff);
          return(ICP_FAILURE); }
        else
          memset ((void *) icp_context_table[new_context].rp_def_tbl,
	          (int)    0,
	          (size_t) (MAX_REMOTE_PROCS * sizeof(rp_def_struct)));

    } /* end of `if not recycling' */

/*  ...otherwise, we are recycling a previously shut down context,
    in which case we just initialize the import/export object tables.
    -----------------------------------------------------------------*/
    else {
      memset ((void *) icp_context_table[new_context].import_tbl,
	      (int)    0,
	      (size_t) (icp_max_import_objs * sizeof(corr_obj_type)));
      memset ((void *) icp_context_table[new_context].export_tbl,
	      (int)    0,
	      (size_t) (icp_max_export_objs * sizeof(corr_obj_type))); }

/*  If we were unable to recycle an old context and had to allocate a new
    one, increment the count of contexts for which memory has been alloc-
    ated.  This is not always the same as the number of active contexts.
    ----------------------------------------------------------------------*/
    if (new_context >= icp_allocated_contexts)
        icp_allocated_contexts = new_context + 1;

/*  Initialize the other elements of the context structure.
    --------------------------------------------------------*/
    icp_context_table[new_context].number = new_context; 
    icp_context_table[new_context].state = ACTIVE;
    icp_context_table[new_context].socket = socket;
    icp_context_table[new_context].partner_type = partner_type;
    icp_context_table[new_context].server_status = NONE;
    icp_context_table[new_context].loaded = FALSE;
    icp_context_table[new_context].last_probe_time = time((time_t *) NULL);
    icp_context_table[new_context].read_index = 0;
    icp_context_table[new_context].write_index = INIT_MSG_INDX;
    icp_context_table[new_context].object_index = 0;
    icp_context_table[new_context].export_count = 0;
    icp_context_table[new_context].import_count = 0;
    icp_context_table[new_context].export_tbl_size = icp_max_export_objs;
    icp_context_table[new_context].import_tbl_size = icp_max_import_objs;
    icp_context_table[new_context].max_export_used = 0;
    icp_context_table[new_context].max_import_used = 0;
    icp_context_table[new_context].bytes_read = 0;
    icp_context_table[new_context].do_ext_proc = FALSE;
    icp_context_table[new_context].received_data = FALSE;
    icp_context_table[new_context].peer_major_version = -1; /* -ncc, 11 Sep 1995  */
    icp_context_table[new_context].peer_minor_version = -1; /* -ncc, 11 Sep 1995  */
    
/*  Increment the count of currently active contexts.
    --------------------------------------------------*/
    icp_active_contexts++;

/*  This only happens the first time through and serves to set up global
    pointers to reference the contents of the new context structure.
    ------------------------------------------------------------------*/
    if (icp_current_context == new_context) {
        curr_ctx = &icp_context_table[new_context];
        if (ext_switch_context(new_context) != ICP_SUCCESS) {
            sprintf(message,"Inconsistency in add_context");
	    ext_message(message,NO_SEND);
            return(ICP_FAILURE); }
    } /* end if */

    return(ICP_SUCCESS);

} /* end add_context */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION im_alive:                         Copyright (C) 1986-2017 Gensym Corporation
:
:  This function checks the current time against the last time we checked in
:  with G2, and if it has been longer than the PROBE_FREQUENCY, sends an 
:  "I'm alive" mesage to G2.
:
:  Arguments:        context  Pointer to the current context structure in the 
:                             context table.
:  Return Behavior:  ICP_FAILURE is returned if send_icp_nop fails, else 
:                    ICP_SUCCESS is returned.
:  Users:            local:    extension_run_loop()
:                    rpcstubs: read_until_empty()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int im_alive(context)
    ctx_struct *context;
{
    time_t  g2ext_current_time;

#ifdef DEBUG
    strcpy(where_in_extension,"im_alive");
    printf("  %s\n",where_in_extension);
#endif

/*  Send "I'm alive" if it is time.
    ------------------------------------*/
    g2ext_current_time = time ((time_t *) NULL);
    if ((icp_int) (g2ext_current_time - context->last_probe_time) > PROBE_FREQUENCY) {
        if (send_icp_nop() != ICP_SUCCESS)
            return(ICP_FAILURE);
        context->last_probe_time = g2ext_current_time; }

/*  If this context connects to a G2 server, call polling mechanism.
    -----------------------------------------------------------------
    if (context->partner_type == G2_SERVER)
        poll_g2(context); >>>>>>>>>>>>>>>>>>> Comment in for Gwin */

    return(ICP_SUCCESS);

} /* end im_alive */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION msg_pending:                      Copyright (C) 1986-2017 Gensym Corporation
:
:  This function determines whether or not an ICP message group has arrived and
:  is awaiting processing.  This is done by attempting a read on the socket
:  for the current context.  One 16-bit ICP byte is read.
:
:  Arguments:        context  Pointer to the current context structure in the 
:                             context table.
:  Return Behavior:  TRUE if a message is pending, FALSE otherwise.
:  Users:            local:    extension_run_loop()
:                    rpcstubs: read_until_empty()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int msg_pending(context)
    ctx_struct *context;
{
    icp_int bytes_read, socket, length, status;

#ifdef DEBUG
    strcpy(where_in_extension,"msg_pending");
    printf("  %s\n",where_in_extension);
#endif

/*  Read one ICP byte (two real bytes), and shutdown
    the connection if a negative number is returned.
    -------------------------------------------------*/
    socket = context->socket;
    length = (icp_int) ICP_BYTE_SIZE;
    errno = 0;
    bytes_read = g2ext_network_read(socket,context->read_buff,0,length);
    if (bytes_read < 0) {
        ext_error(ICP_READ_ERROR,"msg_pending, errno",errno,NO_SEND);
        status = (*icp_shutdown_function)(); /* Status ignored - always FALSE */
        undefine_context();
        return(FALSE); }

/*  Log the number of bytes read (always two or zero), and 
    return TRUE if bytes were read, or FALSE if none were read.
    ------------------------------------------------------------*/
    context->bytes_read = bytes_read;
    if (context->bytes_read > 0)
        return(TRUE);
    else
        return(FALSE);

} /* end msg_pending */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION process_icp_message_group:        Copyright (C) 1986-2017 Gensym Corporation
:
:  This function processes one ICP message group which may consist of one or
:  more message series.
:
:  Arguments:        context  Pointer to the current context structure in the 
:                             context table.
:  Return Behavior:  ICP_FALIURE is returned if read_message_group() or any ICP
:                    message handler fails, or if ICP gets out of synch.
:                    Otherwise ICP_SUCCESS is always returned.
:  Users:            local:    extension_run_loop() 
:                    rpcstubs: read_until_empty()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int process_icp_message_group(context)
    ctx_struct *context;
{
    icp_int msg_id;
    icp_int message_series_length;
    icp_int next_series_index = 0;
    icp_int status;
    icp_int func_index = -1;

#ifdef DEBUG
    strcpy(where_in_extension,"process_icp_message_group");
    printf("  %s\n",where_in_extension);
#endif

/*  Attempt to read the message group into
    the read buffer for the current context.
    -----------------------------------------*/
    if (read_message_group(context) != ICP_SUCCESS)
        return(ICP_FAILURE);

/*  ---------------------------------------------------------------------
    NOTE, from now on, when we `read' we are reading from the read buffer.
    The data has already been read into the read buffer from the network.
    ---------------------------------------------------------------------*/

/*  Loop while there are message series remaining.  For each message series,
    set an index to reference the header of the next message series, and
    proceed to process the series.  Message series are processed by reading
    message ids and calling receiver functions for each message in the series.
    We know we are done with a series when the current read index is equal to
    (or greater) than the index of the next series.
    -------------------------------------------------------------------------*/
    while ((message_series_length = rdicpbyte()) != END_OF_GROUP) {
        next_series_index += message_series_length;
        do {
            msg_id = rdicpbyte();
	    if ((msg_id >= ICP_MSG_OFFSET) &&
                                (msg_id < ICP_MSG_OFFSET + ICP_ARRAY_SIZE)) {
                func_index = msg_id - ICP_MSG_OFFSET;
	        if ((*icp_func_array[func_index])() != ICP_SUCCESS)
	            return(ICP_FAILURE); }
	    else {
	        ext_error(ICP_OUT_OF_SYNCH,
                         "process_icp_message_group, index",
                          func_index,NO_SEND);
                status = (*icp_shutdown_function)();
                undefine_context();
	        return(ICP_FAILURE); }
        } while (curr_ctx->read_index < next_series_index);  /* end do while */
    } /* end while */

    return(ICP_SUCCESS);

} /* end process_icp_message_group */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION read_message_group:              Copyright (C) 1986-2017 Gensym Corporation
:
:  This function reads a message group into the read buffer of a context.
:
:  Note, an ICP message group consists of one or more message series.  A message
:  series consists of a header followed by one or more messages.  A message
:  series header is the length of the series in "ICP bytes" which are 16-bit
:  words.  A message series header whose value is one indicates the end of the
:  message group.
:
:  Arguments:        context  Pointer to the current context structure in the 
:                             context table.
:  Return Behavior:  ICP_FAILURE is returned if g2ext_network_read() fails.  Otherwise,
:                    ICP_SUCCESS is returned.
:  Users:            local:    extension_run_loop(), read_until_empty()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int read_message_group(context)
    ctx_struct *context;
{
    icp_int  series_header_index = 0;
    icp_int  buffer_index; 
    icp_int  bytes_read;
    icp_int  bytes_to_read;
    icp_int  status;
    icp_int  i = 0;

#ifdef DEBUG
    strcpy(where_in_extension,"read_message_group");
    printf("  %s\n",where_in_extension);
#endif

/*  Reset the indices for the read buffer
    and object buffer for this context.
    --------------------------------------*/
    context->object_index = 0;
    context->read_index = 0;
  
/*  Get the number of bytes "pre-read" by msg_pending() from the
    current context structure and use this to calculate the current
    index to the read buffer where newly read data should be sent.
    ----------------------------------------------------------------*/
    bytes_read = context->bytes_read;
    if (bytes_read < 0) {
	ext_error(ICP_READ_ERROR,"read_msg_group, bytes_read",
                       bytes_read,NO_SEND);
	return(ICP_FAILURE); }
    buffer_index = bytes_read >> 1;

/*  For each message series in the message group, calculate the number of
    8-bit bytes in the message series, read them into the read buffer, and
    set the series header index to reference the header for the next series.
    ------------------------------------------------------------------------*/
    errno = 0;
    while(BYTE_SWAP_FOR_ICP(context->read_buff[series_header_index]) != END_OF_GROUP) {
        bytes_to_read = BYTE_SWAP_FOR_ICP(context->read_buff[series_header_index]) << 1;
        while (bytes_to_read > 0) {
            bytes_read = g2ext_network_read(context->socket,
					    &context->read_buff[buffer_index],
					    0,
					    bytes_to_read);
            if (bytes_read < 0) {
	      ext_error(ICP_READ_ERROR,"read_msg_group, errno",errno,NO_SEND);
	      status = (*icp_shutdown_function)();
	      undefine_context();
	      return(ICP_FAILURE); }
            else if (bytes_read == 0) {
	      if (icp_option_is_set(ICP_INSTRUMENTATION)) {
		if (i++)
		  printf(".");
		else
		  printf("\nBusy reading on %d", (int)context->number);
		if (i%60 == 0)
		  printf("\n"); }
	      ext_sleep(); }
            else {
	      bytes_to_read -= bytes_read;
	      buffer_index += (bytes_read >> 1); }
	} /* end while */
        series_header_index = buffer_index - 1;
    } /* end while */

    if (icp_option_is_set(ICP_INSTRUMENTATION) && i)
      printf("\n");

    return(ICP_SUCCESS);

} /* end read_message_group */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION write_message_group:              Copyright (C) 1986-2017 Gensym Corporation
:
:  This function writes one ICP message group from the write buffer out over the
:  network.  In ALL cases, outgoing message groups consist of only one message
:  series.
:
:  Arguments:        None.
:  Return Behavior:  ICP_FAILURE is returned on ICP_WRITE_ERROR.  Otherwise, 
:                    ICP_SUCCESS is returned.
:  Users:            local:  icp_flush()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int write_message_group()
{
    icp_int write_buff_index_8 = 0,
            msg_series_length_8, /* in 8-bit bytes */
            bytes_to_write;
    icp_int bytes_written, 
	    socket, status;
    icp_int i = 0;
    char   *write_buff_8;  /* 8-bit based version of the write buffer. */

#ifdef DEBUG
    strcpy(where_in_extension,"write_message_group");
    printf("      %s\n",where_in_extension);
#endif

/*  The first ICP byte is the length of the message series.
    We need a version of the write buffer that is 8-bit based.
    Also, get the write socket for the current context.
    -------------------------------------------------------*/
    msg_series_length_8 = curr_ctx->write_index << 1;
    write_buff_8 = (char *) curr_ctx->write_buff;
    socket = curr_ctx->socket;

/*  While we still have writing to do...
    --------------------------------------*/
    errno = 0;
    while (write_buff_index_8 < msg_series_length_8) {

    /*  Calculate the number of 8-bit bytes remaining to write and
        the length of the packet to send, and send a packet.
        --------------------------------------------------------*/
        bytes_to_write = msg_series_length_8 - write_buff_index_8;
        bytes_written = g2ext_network_write(socket, write_buff_8, write_buff_index_8,
                                      min(bytes_to_write,MAX_WRITE_SIZE));

    /*  Shutdown the context and return if a write error occurred (the
        negative of the error value returned in network layer is propagated).
        Otherwise, increment write buffer index or sleep as appropriate.
        -------------------------------------------------------------------*/
        if (bytes_written < 0) {
	  ext_error(ICP_WRITE_ERROR,"write_message_group, errno",
		    errno,NO_SEND);
	  status = (*icp_shutdown_function)();
	  undefine_context();
	  return(ICP_FAILURE); }
        else
	  if (bytes_written == 0) {
	    if (icp_option_is_set(ICP_INSTRUMENTATION)) {
	      if (i++)
		printf(".");
	      else
		printf("\nBusy writing on %d", (int)current_context);
	      if (i%60 == 0)
		printf("\n"); }
	    ext_sleep(); }
	  else
	    write_buff_index_8 += bytes_written;
	
    } /* end while */

    if (icp_option_is_set(ICP_INSTRUMENTATION) && i)
      printf("\n");

    return(ICP_SUCCESS);

}/* end write_message_group */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION icp_flush:                       Copyright (C) 1986-2017 Gensym Corporation
:
:  If the write buffer for the current context contains any data, this function
:  sends the data over the network, and resets the global write buffer index to
:  the start of the buffer.
:
:  Note, for outgoing data, message series are always individually - one series
:  per message group.  This contrasts with G2 which may send multiple message
:  series in a message group.
:
:  Arguments:        None.
:  Return Behavior:  ICP_FAILURE is returned if write_message_group() fails,
:                    else ICP_SUCCESS is returned.
:  Users:            Wherever an ICP message is created (many places), and in
:                    context switching.
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int icp_flush()
{

#ifdef DEBUG
    strcpy(where_in_extension,"icp_flush");
    printf("      %s\n",where_in_extension);
#endif

/*  Get out if there are no active contexts,
    or if the current context is undefined.
    -----------------------------------------*/
    if ( (!icp_active_contexts) || (icp_current_context == UNDEFINED_CONTEXT) )
        return(ICP_SUCCESS);

/*  If there is a message series in the buffer, put the length
    of the message series (the current write index) into the
    first ICP byte, add a "end of message group" marker,
    write out the message group, and reset the message loaded flag.
    --------------------------------------------------------------*/
    if (curr_ctx->loaded) {
        curr_ctx->write_buff[0] = (icp_byte) BYTE_SWAP_FOR_ICP(curr_ctx->write_index);  
        wricpbyte(END_OF_GROUP);
        if (write_message_group() != ICP_SUCCESS)
            return(ICP_FAILURE);
        curr_ctx->loaded = FALSE; }

    curr_ctx->write_index = INIT_MSG_INDX;

    return(ICP_SUCCESS);

} /* end icp_flush */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION undefine_context:                 Copyright (C) 1986-2017 Gensym Corporation
:
:  This function will set the global varaibles that define a context to 
:  undefined or null values.
:
:  Arguments:        None.
:  Return Behavior:  None.
:  Users:            local: ext_switch_context(), msg_pending(), 
:                           process_icp_message_group(), read_message_group(),
:                           write_message_group()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  000  Initial  P. Fandel  The contents of this function were taken out of 
:                           ext_switch_context() in order to permit the
:                           contents of this function to be called
:                           independently.
:.............................................................................*/
void undefine_context()
{
#ifdef DEBUG
    strcpy(where_in_extension,"undefine_context");
    printf("    %s\n",where_in_extension);
#endif

    icp_current_context = UNDEFINED_CONTEXT;
    GSI_OBJ_PTRS = NULL_PTR;
    do_ext_proc = NULL_PTR;

} /* end undefine_context */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION ext_switch_context:               Copyright (C) 1986-2017 Gensym Corporation
:
:  This function will switch contexts from the current context to a desired
:  context.  Context numbers are used.
:
:  Arguments:        context  The number of a context to which we will switch.
:  Return Behavior:  ICP_FAILURE is returned if the desired context is out of
:                    range or if it is inactive.  Otherwise, ICP_SUCCESS is
:                    returned.
:  Users:            local:    add_context(), extension_run_loop()
:                    gsi.c: the gsi_return_xxx() functions
:                    rpc.c: rpc_declare_remote(), rpc_start(), rpc_call()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int ext_switch_context(context)
    icp_int context;
{
#ifdef DEBUG
    strcpy(where_in_extension,"ext_switch_context");
    printf("    %s\n",where_in_extension);
#endif

/*  If desired context number is undefined we flush (unless there
    are no active contexts), undefine some globals and get out.
    ------------------------------------------------------------*/
    if (context == UNDEFINED_CONTEXT) {
        if (icp_flush() != ICP_SUCCESS) {
            undefine_context();
            return(ICP_FAILURE); }
        undefine_context();
        return(ICP_SUCCESS); }

/*  If the desired context is invalid, return failure.
    --------------------------------------------------*/
    if (context_active(context) != ICP_SUCCESS)
        return(ICP_FAILURE);

/*  If the current context is active,
    flush it before switching to new context.
    ------------------------------------------*/
    if (context_active(icp_current_context))
        if (icp_flush() != ICP_SUCCESS)
            return(ICP_FAILURE);

/*  A context switch is accomplished by setting some
    global variables to reference another context table.
    -----------------------------------------------------*/
    icp_current_context = context;
    curr_ctx = &icp_context_table[context];
    GSI_OBJ_PTRS = curr_ctx->export_tbl;
    do_ext_proc = &curr_ctx->do_ext_proc;

    return (ICP_SUCCESS);

} /* end ext_switch_context */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION ext_error:                        Copyright (C) 1986-2017 Gensym Corporation
:
:  This function will process an error message using the global message table.
:
:  Arguments:        error code    An index into the error table.
:                    circumstance  A string containing the name of the function
:                                  where the error occurred, and the meaning of
:                                  the data argument if there is one.
:                    data          Some integer.
:                    send flag     Indicates whether or not to send message to
:                                  G2.
:  Return Behavior:  None (void function).
:  Users:            Everywhere...
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
void ext_error(error,circumstance,data,send)
    icp_int  error;
    char    *circumstance;
    icp_int  data;
    icp_int  send;
{
    char line1[ICP_USER_MSG_PART_SIZE];
    char line2[ICP_USER_MSG_PART_SIZE];
    char result[TOTAL_ICP_MSG_SIZE];

#ifdef DEBUG
    strcpy(where_in_extension,"ext_error");
    printf("%s\n",where_in_extension);
#endif

/*  Set global error value to the error number and
    return immediately if output suppression is on.
    -----------------------------------------------*/
    last_extension_error = error;
    if (icp_option_is_set(ICP_SUPPRESS_OUTPUT))
        return;

/*  Print error message to standard output.
    -------------------------------------------*/
    printf("\nGSI internal error %d in context %d\n%s\n", (int)error,
	   (int)icp_current_context, icp_user_msg_tbl[error]);
    if (data == NO_DATA)
        printf("Occurred in %s.\n",circumstance);
    else
        printf("Occurred in %s = %d.\n", circumstance, (int)data);

/*  If we are also sending the error to G2, assemble the string and send it.
    ------------------------------------------------------------------------*/
    if (send) {
        sprintf(line1,"*GSI ERROR %d - %s@L", (int) error, icp_user_msg_tbl[error]);
        if (data == NO_DATA)
            sprintf(line2,"Occurred in %s.",circumstance);
        else
            sprintf(line2,"Occurred in %s = %d.", circumstance, (int)data);
        strcpy(result,line1);
        strcat(result,line2);
        ext_return_message(result,icp_current_context); }

} /* end ext_error */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION ext_message:                      Copyright (C) 1986-2017 Gensym Corporation
:
:  This function will process a message whose text is "in-line".
:
:  Arguments:        message    A pointer to a string.
:                    send flag  Indicates whether or not to send message to G2.
:  Return Behavior:  None (void function).
:  Users:            Everywhere...
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
void ext_message(message,send)
    char    *message;
    icp_int  send;
{
#ifdef DEBUG
    strcpy(where_in_extension,"ext_message");
    printf("%s\n",where_in_extension);
#endif

/*  Return immediately if output suppression is on.
    -----------------------------------------------*/
    if (icp_option_is_set(ICP_SUPPRESS_OUTPUT))
        return;

/*  Print message to standard output.
    -------------------------------------------*/
    printf("\n%s\n",message);

/*  If we are also sending the error to G2, assemble the string and send it.
    ------------------------------------------------------------------------*/
    if (send)
        ext_return_message(message,icp_current_context);

} /* end ext_message */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION ext_return_message:               Copyright (C) 1986-2017 Gensym Corporation
:
:  This function is called indirectly by ICP extension application programs.
:  Its purpose is to send a text message to the G2 message board.
:  This purpose is accomplished by sending ICP message #65 (write user message
:  string).
:
:  Arguments:        message  Pointer to a character array containing message.
:                    context  Identifies the destination of the message.
:  ICP Output Args:  message  Message to send.
:                    urgency  Unused.
:                    duration Unused.
:  Return Behavior:  ICP_FAILURE if context is invalid.  Otherwise, ICP_SUCCESS
:                    is always returned.
:  Users:            local: ext_error(), ext_message()
:                    gsi.c: gsi_return_message()
:                    gspan.c:gspan_return_message()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int ext_return_message(message, context)
    char    *message;
    icp_int  context;
{
    icp_int unused = 0;
    icp_int previous_context = UNDEFINED_CONTEXT;
    icp_int context_switched = FALSE;

#ifdef DEBUG
    strcpy(where_in_extension,"ext_return_message");
    printf("    %s\n",where_in_extension);
#endif

/*  If context is valid, save current context
    value, and switch to destination context.
    ------------------------------------------*/
    if (context == UNDEFINED_CONTEXT) {
        ext_error(CONTEXT_UNDEFINED,"ext_return_message",NO_DATA,NO_SEND);
        return(ICP_FAILURE); }
    if (context_active(context) != ICP_SUCCESS) {
        ext_error(CONTEXT_INVALID,"ext_return_message",NO_DATA,NO_SEND);
        return(ICP_FAILURE); }
    if (context != icp_current_context) {
        previous_context = icp_current_context;
        if (ext_switch_context(context) != ICP_SUCCESS)
            return(ICP_FAILURE);
        context_switched = TRUE; }

/*  Send ICP message header.
    --------------------------------------------------------*/
    wricpbyte(WRITE_USER_MESSAGE_STRING + ICP_MSG_OFFSET);

/*  Send ICP arguments.
    --------------------------*/
    wr_icp_str(message);
    wricpbyte(unused);
    wricpbyte(unused);

/*  Mark the write buffer as loaded.  Then, if its
    level has reached the flush point, flush the buffer.
    -----------------------------------------------------*/
    curr_ctx->loaded = TRUE;
    if (curr_ctx->write_index >= icp_flush_point)
        if (icp_flush() != ICP_SUCCESS)
            return(ICP_FAILURE);

/*  If context was switched upon entering,
    switch it back prior to exiting.
    --------------------------------------*/
    if (context_switched)
        if (ext_switch_context(previous_context) != ICP_SUCCESS)
            return(ICP_FAILURE);

    return(ICP_SUCCESS);

}  /* ext_return_message */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION ext_sleep:                        Copyright (C) 1986-2017 Gensym Corporation
:
:  Calls g2ext_sys_sleep() to sleep process.
:
:  Arguments:        None.
:  Return Behavior:  None (void function).
:  Users:            local: extension_run_loop(), write_message_group()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
void ext_sleep()
{
#ifdef DEBUG
    static icp_int i;
    strcpy(where_in_extension,"ext_sleep");
    i++;
    printf(".");
    if (i > 78) {
        i = 0;
        printf("\n"); }
#endif

    ext_pause();

} /* end ext_sleep */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION ext_pause:                        Copyright (C) 1986-2017 Gensym Corporation
:
:  Calls g2ext_gensym_pause() to perform an interruptable sleep.
:
:  Arguments:        None.
:  Return Behavior:  None (void function).
:  Users:            local: ext_sleep()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
void ext_pause()
{
    if (icp_option_is_set(ICP_USE_OLD_SLEEP))
      g2ext_sys_sleep(SLEEP_TIME);
    else
      g2ext_gensym_pause(INTERUPTABLE_INTERVAL,POLLING_INTERVAL);

} /* end ext_pause */

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION context_active:                   Copyright (C) 1986-2017 Gensym Corporation
:
:  Determines if a context is active or not.
:
:  Arguments:        context A context number.
:  Return Behavior:  ICP_FAILURE is returned if the context state is not active.
:                    ICP_SUCCESS is returned if the context state is active.
:  Users:            Everywhere...
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int context_active(context)
    icp_int context;
{
#ifdef DEBUG
    strcpy(where_in_extension,"context_active");
    printf("      %s\n",where_in_extension);
#endif

    if ((context > (icp_allocated_contexts - 1)) || (context < 0))
        return(ICP_FAILURE);

    if (icp_context_table[context].state == ACTIVE)
        return(ICP_SUCCESS);
    else
        return(ICP_FAILURE);

} /* end context_active */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION find_next_context:                Copyright (C) 1986-2017 Gensym Corporation
:
:  Goes through the context table, and returns the index of the first context
:  whose state is either inactive or reuse.
:
:  Arguments:        None.
:  Return Behavior:  The number of an available context, or MAX context + 1.
:  Users:            local: add_context().
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int find_next_context()
{
    register icp_int i;

#ifdef DEBUG
    strcpy(where_in_extension,"find_next_context");
    printf("    %s\n",where_in_extension);
#endif

/*  Search through all possible contexts, return the number
    of the first whose state is either inactive or reusable.
    ----------------------------------------------------------*/
    for (i=0; i<MAX_CONTEXTS; i++)
        if((icp_context_table[i].state == INACTIVE) ||
	   (icp_context_table[i].state == RE_USE))
	    return (i);

    return(MAX_CONTEXTS + 1);

} /* end find_next_context */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION send_icp_nop:                     Copyright (C) 1986-2017 Gensym Corporation
:
:  Sends ICP message #16 (nop).  Used to tell other ICP process that I am alive.
:
:  Arguments:        None.
:  ICP Output Args:  ???
:  Return Behavior:  ICP_FAILURE is returned if icp_flush() fails, else 
:                    ICP_SUCCESS is returned.
:  Users:            local: im_alive().
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int send_icp_nop()
{
#ifdef DEBUG
    strcpy(where_in_extension,"find_next_context");
    printf("  %s\n",where_in_extension);
#endif

    wricpbyte(NOP + ICP_MSG_OFFSET);
    wricpbyte(0);

/*  Mark the write buffer as loaded.  Then, if its
    level has reached the flush point, flush the buffer.
    -----------------------------------------------------*/
    curr_ctx->loaded = TRUE;
    if (curr_ctx->write_index >= icp_flush_point)
        if (icp_flush() != ICP_SUCCESS)
            return(ICP_FAILURE);

    return(ICP_SUCCESS);

} /* end send_icp_nop */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION arg_is_network_token:             Copyright (C) 1986-2017 Gensym Corporation
:
:  This function will determine if a particular argument is the token `-network'
:  insensitive to case.
:
:  Arguments:        arg  An argument from the command line (a string).
:  Return Behavior:  ICP_FAILURE if arg is not `-network'.  ICP_SUCCESS otherwise.
:  Users:            local: extension_listen().
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int arg_is_network_token(arg)
    char  *arg;
{
#ifdef DEBUG
    strcpy(where_in_extension,"arg_is_network_token");
    printf("%s\n",where_in_extension);
#endif

    g2ext_string_to_uppercase(arg);
    if (strcmp(arg,"-NETWORK") == 0)
        return(ICP_SUCCESS);
    return(ICP_FAILURE);

} /* end arg_is_network_token */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION parse_medium:                     Copyright (C) 1986-2017 Gensym Corporation
:
:  This function takes `arg', determines if it is one of the two valid options 
:  for a tranport medium, and if valid, sets `medium' to `arg'.
:
:  Arguments:        arg     An argument from the command line (a string).
:                    medium  Pointer to a icp_int indicating the transport medium.
:  Return Behavior:  ICP_FAILURE if arg is not `tcpip'
:                    Otherwise, ICP_SUCCESS is returned.
:  Users:            local: extension_listen().
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int parse_medium(arg,medium)
    char    *arg;
    icp_int *medium;
{
#ifdef DEBUG
    strcpy(where_in_extension,"parse_medium");
    printf("%s\n",where_in_extension);
#endif

    g2ext_string_to_uppercase(arg);
    if (strcmp(arg,"TCPIP") == 0)
        *medium = TCP_IP;
    else {
        ext_error(INVALID_NETWORK,"parse_medium",NO_DATA,NO_SEND);
        return(ICP_FAILURE); }
    return(ICP_SUCCESS);

} /* end parse_medium */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION guess_medium:                     Copyright (C) 1986-2017 Gensym Corporation
:
:  This function takes listener argument which could represent either a tcp/ip
:  port number (positive integer) and tries to guess which it is by the simple rule:  If its
:  all digits, assume its a port number.
:
:  Arguments:        listener    An argument from the command line.
:  Return Behavior:  The code for the guessed medium is always returned.
:  Users:            local: extension_listen().
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int guess_medium(listener)
    char  *listener;
{
    icp_int   length, i;

#ifdef DEBUG
    strcpy(where_in_extension,"guess_medium");
    printf("%s\n",where_in_extension);
#endif

/*  If no listener was specified, do not try guessing.
    ---------------------------------------------------*/
    if (strcmp(listener,"") == 0)
        return(UNDEFINED);

    return(TCP_IP);

} /* end guess_medium */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION init_icp_functions:               Copyright (C) 1986-2017 Gensym Corporation
:
:  This function initializes the entire icp_func_array used to store pointers
:  to ICP message receiver functions.  All the pointers are initializes here
:  to point to a function which does nothing.
:
:  Arguments:        from Index of beginning of new area of GSI_OBJ_PTRS array.
:                    to   Index of end of new area of GSI_OBJ_PTRS array.
:  Return Behavior:  No explicit return (void function).
:  Users:            local: gsi_server()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
void init_icp_functions()
{
  register icp_int i;

#ifdef DEBUG
    strcpy(where_in_extension,"init_icp_functions");
    printf("  %s\n",where_in_extension);
#endif

/*  For every slot in the icp_func_array, set
    it to point to a do-nothing function.
    ---------------------------------------*/
    for (i=0; i<ICP_ARRAY_SIZE; i++)
        icp_func_array[i] = null_icp;

} /* end init_icp_functions */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION null_icp:                         Copyright (C) 1986-2017 Gensym Corporation
:
:  This function is loaded as the default function into the icp_func_array[] by
:  init_icp_functions(), however this function should never be called.  Thus
:  this function always sends an error.
:
:  Arguments:        None.
:  Return Behavior:  Always returns ICP_FAILURE.
:  Users:            None, I hope.
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int null_icp()
{
#ifdef DEBUG
    strcpy(where_in_extension,"null_icp");
    printf("  %s\n",where_in_extension);
#endif

/*  This function should never be called, thus complain.
    --------------------------------------------------------*/
    ext_error(INVALID_ICP_MESSAGE,"null_icp",NO_DATA,SEND);
    return(ICP_FAILURE);

} /* end null_icp */
