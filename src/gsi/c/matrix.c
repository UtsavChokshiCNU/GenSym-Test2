/****************************************************************************
:
:  matrix.c  --  Sample GSI Bridge Code for use with gsi_exam.kb
:
:  Maintains an array of numbers served at whim by G2.
:
:  This file contains the standard GSI toolkit functions required for 
:  any GSI application and several other functions coded to support 
:  part of the sample knowledge base `gsi_exam.kb' provided with G2.
:  This file requires the standard GSI libraries and the sample main
:  module 'gsi_main.c' to create the executable `matrix'.
:
:  This file conforms to GSI 4.0.
:
:  Created 10mar95 by paf!
:  Updated 11oct97 by rh
:...........................................................................*/

#include <stdio.h>
#include "gsi_main.h"

#define TCPIP_PORT_NUMBER   22040

#define FLOAT_MATRIX_SIZE      10

static double  float_matrix[FLOAT_MATRIX_SIZE];
extern declare_gsi_rpc_local_fn(update_remote_matrix);

/*****************************************************************************
:  RPC FUNCTION: update_remote_matrix
:
:  This function, which is declared as RPC-invocable from a G2 process, is
:  responsible for keeping float_matrix up to date with the array FLOAT-MATRIX
:  in G2.
:
:  RPC Arguments (2):
:    [0]  FLOAT_MATRIX       Latest snapshot of FLOAT-MATRIX in G2.
:    [1]  INTEGER_LIST      List of indices indicating which elements of the
:                           float matrix need updating.
:
:  Note, this function does not support being invoked via a 'start', and must
:  be invoked with a 'call' action.
:............................................................................*/
void update_remote_matrix(arg_array, count, call_index)
  gsi_item *arg_array;
  gsi_int count;
  call_identifier_type call_index;
{
  gsi_item  new_matrix_item = arg_array[0];
  gsi_item  index_list_item = arg_array[1];
  double   *new_matrix = flt_array_of(new_matrix_item);
  gsi_int  *indices = int_list_of(index_list_item);
  gsi_int   i, element_index;

  for (i=0; i<element_count_of(index_list_item); i++) {
    element_index = indices[i];
    float_matrix[element_index] = new_matrix[element_index]; }

  printf("\nFloat matrix update\n-------------------\n");
  for (i=0; i<FLOAT_MATRIX_SIZE; i++)
    printf("[%02ld] %10.2f\n",i,float_matrix[i]);

  set_class_name(arg_array[0],NULL_PTR); /* Set the class name to NULL in
                                            order to specify simple value */
  set_sym(arg_array[0],"SUCCESS");
  gsi_rpc_return_values(arg_array,1,call_index,current_context);

} /* end update_remote_matrix */



/********************************************************************************
*
*  The remaining functions are the standard GSI Toolkit functions required of all
*  GSI applications.  Those which are used preceed those which are stubbed out.
*
********************************************************************************/

void gsi_set_up ()
{
/*
 *  Declare local function to be remotely invocable.
 */
  gsi_rpc_declare_local(update_remote_matrix,"UPDATE-REMOTE-MATRIX");
}

gsi_int gsi_get_tcp_port()
{
  return(TCPIP_PORT_NUMBER);
}




/************************************************
*
*  The remaining functions are all empty stubs.
*
*************************************************/

gsi_int gsi_initialize_context (remote_process_init_string, length)
  char *remote_process_init_string;
  gsi_int length;
{
  return (GSI_ACCEPT);
}

void gsi_receive_registration (item_registration)
  gsi_registration item_registration;
{}

void gsi_get_data (registered_items, count)
  gsi_registered_item *registered_items;
  gsi_int count;
{}

void gsi_set_data (registered_items, count)
  gsi_registered_item *registered_items;
  gsi_int count;
{}

void gsi_pause_context()
{}

void gsi_resume_context()
{}

void gsi_shutdown_context()
{}

void gsi_receive_deregistrations (registered_items, count)
  gsi_registered_item *registered_items;
  gsi_int count;
{}

void gsi_g2_poll()
{}

void gsi_receive_message (message,length)
  char     *message;
  gsi_int   length;
{}










