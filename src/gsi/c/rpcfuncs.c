/*****************************************************************************
: 
:  rpcfuncs.c  --  Sample GSI Bridge Code for use with gsi_exam.kb
:
:  This file contains the functions that my be called via remote procedure
:  call from G2 in the example knowledge base `gsi_exam.kb'.  It is linked
:  with `filetest.o' to create the executable `filetest'.
:
:  Only one of the four example uses presented in `gsi_exam.kb' makes use
:  of the functions herein.  The example is labelled G2 to GSI RPC Test.
:
:  Note, the functions below are declared for external use in main() in
:  `filetest.c', and the file pointers used below are initialized in 
:  gsi_initialize_context(), also found in `filetest.c'.
:
:  Although this software has been extensively tested, Gensym cannot
:  guarantee error-free performance in all applications.  Accordingly,
:  use of the software is at the customer's sole risk.
:
:  28jul93 by paf! -- Upgraded to GSI 3.1
:  25jul94 by paf! -- Upgraded to GSI 4.0
:  11oct97 by rh   -- Upgraded to GSI 5.0.1
:...........................................................................*/

#include <stdio.h>
#include <string.h>
#include "gsi_main.h"

/* Functions included in this file:                                         */

extern declare_gsi_rpc_local_fn(rpc_fopen);
extern declare_gsi_rpc_local_fn(rpc_fclose);
extern declare_gsi_rpc_local_fn(rpc_fread);
extern declare_gsi_rpc_local_fn(rpc_fwrite);
extern declare_gsi_rpc_local_fn(force_gsi_exit);

gsi_int get_next_file();

#define MAX_FPTRS       32
#define BAD_OPEN         0
#define OPEN_FAILED     -1
#define FILE_FREE      NULL
#define STRSZ           256

extern gsi_item *my_item_array;

FILE      *f_ptrs[MAX_FPTRS];


void rpc_fopen(item_array, count,call_index)
    gsi_item  item_array[];
    gsi_int   count;
    call_identifier_type   call_index;
{
    char         *fname;
    char         *mode;
    gsi_int       f_index;
    FILE         *fd;

    fname = (char *) str_of(item_array[0]);
    mode = (char *) str_of(item_array[1]);

    printf("filename:: %s\n", fname);
    printf("    mode:: %s\n", mode);

    fflush(stdout);
    fd = fopen(fname,mode);
    if (fd == BAD_OPEN)
        set_int(my_item_array[0],OPEN_FAILED);
    else {
        f_index = get_next_file();
        if (f_index == MAX_FPTRS) 
            set_int(my_item_array[0],OPEN_FAILED);
        else {
            f_ptrs[f_index] = fd;
            set_int(my_item_array[0],f_index); }
    } /* end else */

    gsi_rpc_return_values(my_item_array,1,call_index,current_context);
  
} /* end rpc_fopen */


void rpc_fclose(item_array, count,call_index)
    gsi_item  item_array[];
    gsi_int   count;
    call_identifier_type   call_index;
{
    gsi_int   f_index;

    f_index = int_of(item_array[0]);
    fclose(f_ptrs[f_index]);
    f_ptrs[f_index] = FILE_FREE;

    set_int(my_item_array[0],0);
    gsi_rpc_return_values(my_item_array,1,call_index,current_context);

} /* end rpc_fclose */


void rpc_fread(item_array, count,call_index)
    gsi_item  item_array[];
    gsi_int   count;
    call_identifier_type   call_index;
{
    gsi_int       i;
    FILE         *fd;
    gsi_int       int_reads, string_reads, int_value = 0;
    gsi_int       status = 1;
    char          str_value[STRSZ];

    fd = f_ptrs[int_of(item_array[0])];
    int_reads = int_of(item_array[1]);
    string_reads = int_of(item_array[2]);

    for(i=1; i<=int_reads; i++) {
        if (status == 1) {
            status = fscanf(fd,"%ld", &int_value);
            set_int(my_item_array[i],int_value); }
        if (status != 1)
	    set_int(my_item_array[i],0);
    } /* end for */

    for(; i<=(int_reads+string_reads); i++) {
        if (status == 1) {
            status = fscanf(fd,"%s", str_value);
            set_sym(my_item_array[i],str_value); }
        if (status != 1)
	    set_sym(my_item_array[i],"EOF");
    } /* end for */

    set_int(my_item_array[0],status);
    gsi_rpc_return_values(my_item_array,
                          (int_reads+string_reads+1),
                          call_index,
                          current_context);

} /* end rpc_fread */


void rpc_fwrite(item_array, count,call_index)
    gsi_item  item_array[];
    gsi_int   count;
    call_identifier_type   call_index;
{
    gsi_int       i;
    FILE         *fd;
    gsi_int       status = 1, int_writes, string_writes;

    fd = f_ptrs[int_of(item_array[0])];
    int_writes = int_of(item_array[1]);
    string_writes = int_of(item_array[2]);

    for(i=1; (status != EOF) && (i <= int_writes); i++)
        status = fprintf(fd,"%ld ", int_of(item_array[i+2]));
    for(; (status != EOF) && (i <= (int_writes+string_writes)); i++)
        status = fprintf(fd,"%s\n", sym_of(item_array[i+2]));

    set_int(my_item_array[0],status);
    gsi_rpc_return_values(my_item_array,1,call_index,current_context);

} /* end rpc_fwrite */


gsi_int get_next_file()
{
    gsi_int i;

    for (i=1; i<MAX_FPTRS; i++) {
        if (f_ptrs[i] == FILE_FREE)
            return(i); }

    printf("\n Too Many files Opened ");
    return(MAX_FPTRS);

} /* end get_next_file */

void force_gsi_exit(item_array, count, call_index)
    gsi_item  item_array[];
    gsi_int   count;
    call_identifier_type   call_index;
{
    exit(0);
}
