/*****************************************************************************
: 
:  filetest.c  --  Sample GSI Bridge Code for use with gsi_exam.kb
:
:  This file contains the standard GSI toolkit functions required for any GSI
:  application.  These functions have been coded to support the sample
:  knowledge base `gsi_exam.kb' provided with G2.  This file is linked
:  with `rpcfuncs.o' to create the executable `filetest'.
:
:  This file along with `rpcfuncs.c' contains code that supports three
:  separate example uses of GSI demonstrated from G2 in `gsi_exam.kb'.
:  Most of the code in this file supports an example of GSI passing object
:  attribute values up to G2.  The function `gsi_send_message' in this file
:  supports an example of GSI calling a procedure in G2 via RPC.  All of the
:  functions in `rpcfuncs.c' support an example demonstrating G2 calls
:  to C functions in written in the GSI user code.  Note, some of the 
:  functions in this file simultaneously support all of the examples.
:
:  Although this software has been extensively tested, Gensym cannot
:  guarantee error-free performance in all applications.  Accordingly,
:  use of the software is at the customer's sole risk.
:
:  28jul93 by paf! -- Upgraded to GSI 3.1
:  25jul94 by paf! -- Upgraded to GSI 4.0
:  11oct97 by rh   -- Upgraded to GSI 5.0.1
:..........................................................................*/

#include <string.h>
#include <stdio.h>
#include "gsi_main.h"

#define MAX_FPTRS             32
#define FILE_FREE           NULL
#define ERR_MSG_SZ           128
#define MAX_NUM_ATTR_PARTS     8
#define MAX_FNAME             25
#define OPEN                   0
#define CLOSED                 1
#define GOOD_SYMBOL        "GOOD"
#define EOF_SYMBOL          "EOF"
#define TYPE_SYMBOL        "TYPE"
#define MAX_NUM_ATTRS          5
#define MAX_NUM_ITEMS         10
#define TCPIP_PORT_NUMBER  22040
#define STRSZ                256
#define MAX_CONTEXTS          50  /* I choose to support up to 50 */

char                 error_msg[ERR_MSG_SZ];
char                 file_name[MAX_CONTEXTS][MAX_FNAME];
FILE                *file_id[MAX_CONTEXTS] = {NULL};
gsi_int              file_status[MAX_CONTEXTS];
char                *attr_names[MAX_NUM_ATTRS] =
                             {"STARTX","ENDX","STARTY","ENDY"};
function_handle_type g2_test_procedure[MAX_CONTEXTS];
gsi_attr            *my_attr_array;
gsi_item            *my_item_array;
gsi_registered_item *registered_return_item_ptr;

extern declare_gsi_rpc_local_fn(rpc_fopen);
extern declare_gsi_rpc_local_fn(rpc_fclose);
extern declare_gsi_rpc_local_fn(rpc_fread);
extern declare_gsi_rpc_local_fn(rpc_fwrite);
extern declare_gsi_rpc_local_fn(force_gsi_exit);

extern declare_gsi_rpc_receiver_fn(generic_return_value_receiver);

extern FILE *f_ptrs[];



main(argc, argv)
    int   argc;
    char *argv[];
{
    GSI_SET_OPTIONS_FROM_COMPILE();

/*
 *  Initialize GSI and enter the event handler loop.
 */
    gsi_start(argc, argv);

    return 0;

} /* end main */


void gsi_set_up()
{
/*
 *  Declare those local functions that are to be made available
 *  to G2 such that G2 may call them as remote procedures.
 */
    gsi_rpc_declare_local(rpc_fopen,"OPEN");
    gsi_rpc_declare_local(rpc_fclose,"CLOSE");
    gsi_rpc_declare_local(rpc_fread,"READ");
    gsi_rpc_declare_local(rpc_fwrite,"WRITE");
    gsi_rpc_declare_local(force_gsi_exit,"FORCE-GSI-EXIT");

/*
 *  Allocate data structures that will be needed to support this program's 
 *  features.  Note, that these are never explicitly reclaimed because they
 *  are needed for the entire life of the process and are implicitly 
 *  reclaimed upon exit of the process.
 */
    my_attr_array = gsi_make_attrs_with_items(MAX_NUM_ATTRS);
    my_item_array = gsi_make_items(MAX_NUM_ITEMS);
    registered_return_item_ptr = gsi_make_registered_items(1);

/*
 *  The following lines only have relevance on VAX systems
 *  where more than one floating point format are supported.
 */
#ifdef vax
#   if CC$gfloat
        gsi_set_option(GSI_USE_GFLOATS);
#   endif
#endif

} /* end gsi_set_up */


void generic_return_value_receiver(arg_array, count)
    gsi_item  arg_array[];
    gsi_int   count;
{
    long      i;

    printf("\nReceiving values from G2 return call\n ");

    for (i=0; i<count; i++)
        switch (type_of(arg_array[i])) {
            case INTEGER_TAG:
                printf("\narg %d is %d", i, int_of(arg_array[i]));
                break;
            case FLOAT64_TAG:
                printf("\narg %d is %f", i, flt_of(arg_array[i]));
                break;
            case SYMBOL_TAG:
                printf("\narg %d is %s", i, sym_of(arg_array[i]));
                break;
            case STRING_TAG:
                printf("\narg %d is %s", i, str_of(arg_array[i]));
                break;
            case LOGICAL_TAG:
                printf("\narg %d is %d", i, log_of(arg_array[i]));
                break;
            default:
	        printf("\n Unknown Arg type");
        } /* end switch */

    printf("\nEnd of return call \n");

} /* end generic_return_value_receiver */


gsi_int gsi_get_tcp_port()
{
    return(TCPIP_PORT_NUMBER);
}


gsi_int gsi_initialize_context(remote_process_init_string, length)
    char    *remote_process_init_string;
    gsi_int  length;
{
    gsi_int  i;

/*
 *  Reset the file pointers used by the remotely
 *  called functions in `rpc_functions.c'.
 */
    for(i=0; i<MAX_FPTRS; i++)
        f_ptrs[i] = FILE_FREE;

/*
 *  Open a file for reading specified by G2.
 */
    strcpy(file_name[current_context],remote_process_init_string);
    printf("\nInitializing data server, file = %s for #%hd\n",
	   remote_process_init_string, current_context);
    file_id[current_context] = fopen(remote_process_init_string, "r");
    printf ("\nFile open state = %ld\n", (gsi_int) file_id[current_context]);
    if (file_id[current_context] == NULL) {
        printf ("\nCannot open file %s in gsi_init().\n", 
		remote_process_init_string);
        file_status[current_context] = CLOSED;
        return(GSI_REJECT); }
    else
        file_status[current_context] = OPEN;

/*
 *  Declare a G2 procedure so that it may be called from GSI.
 */
    gsi_rpc_declare_remote(&g2_test_procedure[current_context],"G2-TEST-PROCEDURE",
			   generic_return_value_receiver, 3,3, current_context);

    return (GSI_ACCEPT);

} /* end gsi_initialize_context */


void gsi_receive_registration(item_registration)
    gsi_item  item_registration;
{}

void gsi_get_data(registered_item_array, count)
    gsi_registered_item  registered_item_array[];
    gsi_int              count;
{
    long        i, j;
    char        object_type[STRSZ];
    gsi_int     vals[MAX_NUM_ATTRS];

/*
 *  Iterate over the array of items sent from G2, and for each...
 */
    for (i=0; i<count; i++) {

    /*
     *  Set up the return item.
     */
        set_handle(*registered_return_item_ptr,
                       handle_of(registered_item_array[i]));
        set_status(*registered_return_item_ptr,NO_ERR);

    /*
     *  If necessary, open the file for this context.  Exit loop on failure.
     */
        if (file_status[current_context] == CLOSED) {
            file_id[current_context] = fopen(file_name[current_context],"r");
            if (file_id[current_context] == NULL) {
                set_sym(*registered_return_item_ptr,EOF_SYMBOL);
                gsi_return_values(registered_return_item_ptr,1,current_context);
                continue; }
            else
                file_status[current_context] = OPEN;
        } /* end if */

    /*
     *  Set the default value for the return item, read a
     *  line from the file, and if EOF is reached, exit loop.
     */
        set_sym(*registered_return_item_ptr,GOOD_SYMBOL);
        if (fscanf(file_id[current_context], "%ld %ld %ld %ld %s",
              &vals[0], &vals[1], &vals[2], &vals[3], object_type) == EOF) {
            fclose(file_id[current_context]);
            file_status[current_context] = CLOSED;
            set_sym(*registered_return_item_ptr,EOF_SYMBOL);
            gsi_return_values(registered_return_item_ptr,1,current_context);
            continue;
        } /* end if */

    /*
     *  Fill the first four attributes with the integer values
     *  from the file, and the fifth attribute with the text value.
     */
        for (j=0; j<(MAX_NUM_ATTRS - 1); j++) {
            set_attr_name(my_attr_array[j],attr_names[j]);
            set_int(my_attr_array[j],vals[j]);
        } /* end for */
        set_attr_name(my_attr_array[j],TYPE_SYMBOL);
        set_sym(my_attr_array[j],object_type);
        gsi_return_attrs(*registered_return_item_ptr,
                         my_attr_array,
                         MAX_NUM_ATTRS,
                         current_context);
    } /* end for */

} /* end gsi_get_data */


void gsi_set_data(registered_item_array, count)
    gsi_registered_item  registered_item_array[];
    gsi_int              count;
{}


void gsi_pause_context()
{}


void gsi_resume_context()
{}


void gsi_shutdown_context()
{
    if (file_status[current_context] != CLOSED) {
        fclose(file_id[current_context]);
        file_status[current_context] = CLOSED; }
}


void gsi_g2_poll()
{}


void gsi_receive_deregistrations(registered_item_array, count)
    gsi_registered_item  registered_item_array[];
    gsi_int              count;
{
    printf ("gsi_receive_deregistrations\n");
}


void gsi_receive_message(message, length)
    char     *message;
    gsi_int   length;
{
/*
 *  Prepare RPC arguments using arguments received from G2, and invoke RPC.
 */
    set_int(my_item_array[0],strlen(message));
    set_str(my_item_array[1],message);
    set_sym(my_item_array[2],"GENSYM_INTELLIGENT_ON_LINE_SYSTEMS");
    gsi_rpc_call(g2_test_procedure[current_context],
                 my_item_array,
                 current_context);

} /* end gsi_send_message */
