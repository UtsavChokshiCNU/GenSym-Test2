/*******************************************************************************

File name:               icp.c
Owner:                   Peter Fandel

Purpose:                 To hold any code common to more than one of the ICP
                         extension products.

Contents:                ICP Reader Functions - Functions that read ICP message
                         elements of types integer, unsigned integer, float, and
                         string.

                         ICP Writer Functions - Functions that write ICP message
                         elements of types integer, unsigned integer, float, and
                         string.

                         Note, these functions read from and write to read and
                         write buffers, NOT the network.  These functions read
                         data that has already been sucked off the network by
                         read_message_groups() in extensn.c, or write data that
                         will subsequently be written out to the network by 
                         write_message_group() in extensn.c.

                         Supporting Functions - Functions that support the 
                         above categories of function, and longstrings.

                         Access functions for manipulating the data structures
                         used to store data before sending across ICP and after
                         receiving across ICP.

This file depends on:    pools.c, extensn.c and the include files listed
                         below.

Dependent files:         Any GSI or GSPAN bridge application, foreign functions, 
                         gsi, extensn, grpc, and gspan.

Legal Notice:            Copyright (C) 1986-2017 Gensym Corporation.,
                         125 CambridgePark Drive, Cambridge MA 02140
                         All rights reserved.

History:                 See individual function headers.

Header files:            The following are include files required by this file.
                         The constant EXTERN_DEFINED is set to TRUE so as to
                         prevent some externs from being defined twice.       */

#include "cprim.h"

#define                  EXTERNS_DEFINED TRUE  /* Turn off part of icp.h.     */
#include                "gensym-features.h"    /* Machine dependent stuff.    */
#include                "icp.h"              /* Stuff required by all ICP
                                                  extension code.             */
#include                "icp_pvt.h"          /* Stuff required by all ICP
                                                  extensions internal code. 

Functions by category:   Reader Functions           Writer Functions
                         ----------------           ----------------          */
                      icp_int  rd_icp_int();        void  wr_icp_int();
                      icp_int  rd_large_int();      void  wr_large_int();
                       double  rd_icp_64float();    void  wr_icp_64float();
                      icp_int  rd_icp_str();        void  wr_icp_str();
                      icp_int  rd_icp_int_array();  void  wr_icp_int_array();
                      icp_int  rd_icp_flt_array();  void  wr_icp_flt_array();
                      icp_int  rd_icp_str_array();  void  wr_icp_str_array();
                      icp_int  rd_icp_val_array();  void  wr_icp_val_array();
                      icp_int  allocate_and_rd_icp_chars();
                      icp_int  rd_icp_chars();        void  wr_icp_usint();

/*                       Other Functions
                         ---------------                                      */
                      icp_int  read_object_value();
                      icp_int  write_object_value();
                      icp_int  gensym_to_ascii();
                      icp_int  ascii_to_gensym();
                      icp_int  value_array_read_recurse();
                      icp_int  value_array_write_recurse();

/* The following extern is to allow me access to a function
   in the network layer which I need to translate ICP floats.
-------------------------------------------------------------*/
extern double g2ext_foreign_reconstruct_float(/* long, long, long, long */);

/* 
 * jh, 7/8/94.  Need an explicit extern now that foreign_partion_float() returns
 * a long instead of an int.  See my note this date in /bt/ab/rtl/c/gensym.h for
 * further details.
 */
extern long g2ext_foreign_partition_float(/* double, unsigned char *, long */);
extern icp_int allocate_blob(icp_int array_size, char **ptr_ptr);
extern icp_int reclaim_used_blobs(void);
extern void ext_error(icp_int error, char *circumstance, icp_int data, icp_int send);




/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION rd_icp_int:                       Copyright (C) 1986-2017 Gensym Corporation
:
:  This function reads an integer element from an ICP message in the read buffer
:  for the current context.  An integer occupying one 16-bit ICP byte may range
:  from -31,500 to 31,500.  Integers outside of this range are sent in two or
:  more ICP bytes.  Theoretically this code will support integers of any size.
:  However, I believe G2 never sends anything larger than 30 bits and other GSI
:  processes never send anything bigger than 31-bits.
:
:  Integers are sent with an offset of 31,500.  Thus the value of MAX_ICP_US_INT
:  is twice the offset.
:
:  Arguments:        None.
:  Return Behavior:  An integer is always returned.
:  Users:            ??
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int rd_icp_int()
{
    icp_int first_byte;
    icp_int temp;

#ifdef DEBUG
    strcpy(where_in_extension,"rd_icp_int");
    printf("        %s\n",where_in_extension);
#endif

/*  Read one 16-bit ICP byte.  If it is outside the "regular"
    range, call a routine that reads in the rest of the number.
    Otherwise, take out the offset put in when it was written.
    -----------------------------------------------------------*/
    first_byte = rdicpbyte();
    if (first_byte > MAX_ICP_US_INT)
        temp = rd_large_int(first_byte);             /* range unspecified */
    else
        temp = first_byte - (MAX_ICP_US_INT >> 1);   /* -31,500 to 31,500 */

    return(temp);

} /* end rd_icp_int */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION rd_large_int:                     Copyright (C) 1986-2017 Gensym Corporation
:
:  This function will read in a large integer, the first part having already
:  been read by rd_icp_int() and passed here as an argument.  The first byte,
:  passed in as an argument, indicates a negative number if greater than 63,500,
:  and the number of ICP bytes that must be read is calculated by subtracting
:  63,000 (or 63,500 if integer is determined to be negative) from the first
:  byte.
:
:  ICP can handle huge integers that require 500 16-bit bytes to represent.
:  However, this code can only handle 32-bit integers.
:
:  Arguments:        icp_byte  Indicates the sign of the integer and the number
:                              of ICP bytes required to represent it.
:  Return Behavior:  An integer is always returned.
:  Users:            local:  rd_icp_int(), rd_icp_usint()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int rd_large_int(integer_part)
    icp_int integer_part;
{
    icp_int  byte_count, negative = FALSE;
    icp_int  result;
    icp_int  i;

#ifdef DEBUG
    strcpy(where_in_extension,"rd_large_int");
    printf("        %s\n",where_in_extension);
#endif

/*  Use first byte read to calculate sign of integer and length in ICP bytes
    -------------------------------------------------------------------------*/
    if (integer_part > (MAX_ICP_US_INT + MAX_ICP_INT_LEN)) {
        negative = TRUE;
        byte_count= integer_part - (MAX_ICP_US_INT + MAX_ICP_INT_LEN); }
    else 
        byte_count = integer_part - MAX_ICP_US_INT;

/*  Read in the remaining parts of the integer
    which represent its absolute value.
    I don't know why it is shifted 15 bits and not 16.
    --------------------------------------------------*/
    for (i=0, result=0; i<byte_count; i++)
        result = (result << 15) + rdicpbyte();

    if (negative) 
        return(-result);
    else 
        return(result);

} /* end rd_large_int */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION rd_icp_64float:                   Copyright (C) 1986-2017 Gensym Corporation
:
:  This function reads a double-float element from an ICP message in the read 
:  buffer for the current context.
:
:  Arguments:        None.
:  Return Behavior:  A double float is always returned.
:  Users:            ??
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
double rd_icp_64float()
{
    icp_int        part1, part2, part3, part4;
    double         result;

#ifdef DEBUG
    strcpy(where_in_extension,"rd_icp_64float");
    printf("        %s\n",where_in_extension);
#endif

/*  Read in the pieces parts.
    ----------------------------*/
    part1 = rdicpbyte();
    part2 = rdicpbyte();
    part3 = rdicpbyte();
    part4 = rdicpbyte();

/*  Put-em together.
    -----------------*/
    result = g2ext_foreign_reconstruct_float(part1, part2, part3, part4);
    return(result);

} /* end rd_icp_64float */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION rd_icp_str:                       Copyright (C) 1986-2017 Gensym Corporation
:
:  This function reads a string element from an ICP message out of the read 
:  buffer for the current context.
:
:  Arguments:        value_ptr  Pointer to an obj_value_type (TEMP_PARAM).
:  Return Behavior:  ICP_FAILURE if rd_icp_chars() or allocate_and_read_icp_
:                    chars() fail.  Otherwise, ICP_SUCCESS is returned.
:  Users:            local:     read_object_value()
:                    foreign.c: handle_kill_server(),
:                               handle_req_foreign_registry()
:                    gsi.c:     init_rcvr(), read_text_rcvr(),
:                               read_obj_def_value()
:                    gspan.c:   def_xs_obj(), sim_keyword(), connection_info()
:                    rpc.c:     intern_symbol_rcvr(), rpc_error1_rcvr(),
:                               rpc_error1_rcvr()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int rd_icp_str(value_ptr)
    obj_value_type *value_ptr;
{
#ifdef DEBUG
    strcpy(where_in_extension,"rd_icp_str");
    printf("        %s\n",where_in_extension);
#endif

/*  Read in the string length in 8-bit
    bytes and call the appropriate reader
    ---------------------------------------*/
    value_ptr->count = rdicpbyte();
    if (allocate_and_rd_icp_chars(&value_ptr->count,&value_ptr->p_value.string_p)
                                                                 != ICP_SUCCESS)
        return(ICP_FAILURE);

    return(ICP_SUCCESS);

} /* end rd_icp_str */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION allocate_and_rd_icp_chars:        Copyright (C) 1986-2017 Gensym Corporation
:
:  This function allocates space for, and reads a string.
:
:  Arguments:        length_ptr  Pointer to length of string to read.
:                    string_ptr Address of pointer that will refer to new space.
:  Return Behavior:  ICP_FAILURE if rd_icp_chars() or allocate_blob() fail. 
:                    Otherwise, ICP_SUCCESS is returned.
:  Users:            local: rd_icp_str()
:  Memory Impact:    Indirect -- allocate_blob() may call malloc twice.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int allocate_and_rd_icp_chars(length_ptr,string_ptr)
    icp_int  *length_ptr;
    char    **string_ptr;
{
#ifdef DEBUG
    strcpy(where_in_extension,"allocate_and_rd_icp_chars");
    printf("        %s\n",where_in_extension);
#endif

/*  Allocate space for the string and read it in to the space.
    -----------------------------------------------------------*/
    if (allocate_blob(*length_ptr,string_ptr) != ICP_SUCCESS)
        return(ICP_FAILURE);
    if (rd_icp_chars(length_ptr,string_ptr) != ICP_SUCCESS)
        return(ICP_FAILURE);

    return(ICP_SUCCESS);

} /* end allocate_and_rd_icp_chars */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION rd_icp_chars:                     Copyright (C) 1986-2017 Gensym Corporation
:
:  This function reads a series of characters from an ICP message into a space
:  designated by the contents of the string_ptr argument.
:
:  Arguments:        length_ptr Pointer to length of string to read.
:                    string_ptr Pointer to a char pointer for characters.
:  Return Behavior:  ICP_FAILURE is blob alloc fails, otherwise ICP_SUCCESS.
:  Users:            local: rd_icp_str(), allocate_and_rd_icp_chars() 
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int rd_icp_chars(length_ptr,string_ptr)
    icp_int *length_ptr;
    char   **string_ptr;
{
    icp_int  length_16, char_pair;
    icp_int  i;
    char    *char_ptr, *filtered;

#ifdef DEBUG
    strcpy(where_in_extension,"rd_icp_chars");
    printf("        %s\n",where_in_extension);
#endif

/*  Calculate the length in 16-bit ICP bytes.
    -----------------------------------------*/
    length_16 = *length_ptr >> 1;

/*  Read all the characters of the string into the destination
    (if there are an odd number of characters, last one must
    be read outside of loop), and terminate the string.
    -------------------------------------------------------*/
    char_ptr = *string_ptr;
    for (i=0; i<length_16; i++) {
        char_pair = rdicpbyte();
        *char_ptr++ = (char) (char_pair >> 8);
        *char_ptr++ = (char) (char_pair & 0xFF); }
    if (*length_ptr & 0x01) {
        char_pair = rdicpbyte();
        *char_ptr++= (char) (char_pair & 0xFF); }
    *char_ptr++ = NULL_CHAR;

/*  If string filtering is on, we will need a second buffer.  Allocate
    another blob, filter the string and reassign the char_ptr argument.
    -------------------------------------------------------------------*/
    if (icp_option_is_set(ICP_STRING_CHECK)) {
        if (allocate_blob(*length_ptr,&filtered) != ICP_SUCCESS)
            return(ICP_FAILURE);
        *length_ptr = gensym_to_ascii(*string_ptr, filtered);
        *string_ptr = filtered; }

    return(ICP_SUCCESS);

} /* end rd_icp_chars */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION rd_icp_int_array:                 Copyright (C) 1986-2017 Gensym Corporation
:
:  This function reads an array of integers (or logicals) from an ICP message in
:  the read buffer for the current context.  Integers are placed in temporarily
:  allocated memory.
:
:  Arguments:        int_array_ptr  Pointer to an integer array.
:                    count_ptr      Pointer to count (array size).
:  Return Behavior:  ICP_FAILURE if allocate_blob() fails.  Otherwise, ICP_SUCCESS
:                    is returned.
:  Users:            gsi.c: read_object_value()
:                    rpc.c: ??
:                    local: ???recurse()
:  Memory Impact:    Indirect -- allocate_blob() may call malloc.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int rd_icp_int_array(int_array_ptr,count_ptr)
    icp_int **int_array_ptr;
    icp_int  *count_ptr;
{
    icp_int *integer_ptr;
    icp_int  i;

#ifdef DEBUG
    strcpy(where_in_extension,"rd_icp_int_array");
    printf("        %s\n",where_in_extension);
#endif

/*  Read the size of the integer array off of the ICP message,
    allocate space for the array, and attach to int array pointer.
    ---------------------------------------------------------------*/
    *count_ptr = rdicpbyte();
    if (allocate_blob((*count_ptr * sizeof(icp_int)), (char**) int_array_ptr) != ICP_SUCCESS)
        return(ICP_FAILURE);

/*  Read the integers into the array.
    ----------------------------------*/
    integer_ptr = *int_array_ptr;
    for (i=0; i<*count_ptr; i++, integer_ptr++)
        *integer_ptr = rd_icp_int();

    return(ICP_SUCCESS);

} /* end rd_icp_int_array */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION rd_icp_flt_array:                 Copyright (C) 1986-2017 Gensym Corporation
:
:  This function reads an array of floats from an ICP message in the read
:  buffer for the current context.  Floats are placed in temporarily allocated
:  memory.
:
:  Arguments:        int_array_ptr  Pointer to an integer array.
:                    count_ptr      Pointer to count (array size).
:  Return Behavior:  ICP_FAILURE if allocate_blob() fails.  Otherwise, ICP_SUCCESS
:                    is returned.
:  Users:            gsi.c: read_object_value()
:                    rpc.c: ??
:                    local: ???recurse()
:  Memory Impact:    Indirect -- allocate_blob() may call malloc.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int rd_icp_flt_array(flt_array_ptr,count_ptr)
    double  **flt_array_ptr;
    icp_int  *count_ptr;
{
    double  *float_ptr;
    icp_int  i;

#ifdef DEBUG
    strcpy(where_in_extension,"rd_icp_flt_array");
    printf("        %s\n",where_in_extension);
#endif

/*  Read the size of the float array off of the ICP message,
    allocate space for the array, and attach to flt array ptr.
    -------------------------------------------------------------*/
    *count_ptr = rdicpbyte();
    if (allocate_blob((*count_ptr * sizeof(double)), (char**) flt_array_ptr)
                                                                 != ICP_SUCCESS)
        return(ICP_FAILURE);

/*  Read the floats into the array.
    ----------------------------------*/
    float_ptr = *flt_array_ptr;
    for (i=0; i<*count_ptr; i++, float_ptr++)
        *float_ptr = rd_icp_64float();

    return(ICP_SUCCESS);

} /* end rd_icp_flt_array */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION rd_icp_str_array:                 Copyright (C) 1986-2017 Gensym Corporation
:
:  This function reads an array of strings (or symbols) from an ICP message in
:  the read buffer for the current context.  Strings are placed in temporarily
:  allocated memory.
:
:  Arguments:        str_array_ptr  Pointer to a string array.
:                    count_ptr      Pointer to count (array size).
:  Return Behavior:  ICP_FAILURE if allocate_blob() fails.  Otherwise,
:                    ICP_SUCCESS is returned.
:  Users:            gsi.c: read_object_value()
:                    rpc.c: ??
:                    local: ???recurse()
:  Memory Impact:    Indirect -- allocate_blob() may call malloc.
:                                allocate_and_rd_icp_chars() calls
:                                allocate_blob().
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int rd_icp_str_array(str_array_ptr,count_ptr)
    char   ***str_array_ptr;              /*  Yeeeoweeeeeeeee! */
    icp_int  *count_ptr;
{
    icp_int  length;
    char   **string_ptr;
    icp_int  i;

#ifdef DEBUG
    strcpy(where_in_extension,"rd_icp_str_array");
    printf("        %s\n",where_in_extension);
#endif

/*  Read the size of the string array (the number of
    separate strings) off of the ICP message, allocate
    space for the array, and attach to string pointer array.
    ---------------------------------------------------------*/
    *count_ptr = rdicpbyte();
    if (allocate_blob((*count_ptr * sizeof(char *)), (char**)str_array_ptr)
                                                                 != ICP_SUCCESS)
        return(ICP_FAILURE);

/*  Read in the strings.  The string array will occupy the blob just
    allocated and will contain string pointers.  The actual strings will
    be stored in individual blobs allocated by allocate_and_rd_icp_chars().
    -----------------------------------------------------------------------*/
    string_ptr = *str_array_ptr;
    for (i=0; i<*count_ptr; i++, string_ptr++) {
        length = rdicpbyte();
        if (allocate_and_rd_icp_chars(&length,string_ptr) != ICP_SUCCESS)
            return(ICP_FAILURE);
    } /* end for */

    return(ICP_SUCCESS);

} /* end rd_icp_str_array */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION rd_icp_val_array:                 Copyright (C) 1986-2017 Gensym Corporation
:
:  This function reads an array of values from an ICP message in the read buffer
:  for the current context.  Each value may be any of the valid values (integer,
:  integer array, float, float array, string, string array et cetera - including
:  value array).
:
:  Arguments:        val_array_ptr  Pointer to a value array.
:                    count_ptr      Pointer to count (array size).
:  Return Behavior:  ICP_FAILURE if allocate_blob() fails.  Otherwise, ICP_SUCCESS
:                    is returned.
:  Users:            gsi.c: read_object_value()
:                    rpc.c: ??
:                    local: ???recurse()
:  Memory Impact:    Indirect -- allocate_blob() may call malloc.
:                                value_array_read_recurse() may indirectly call
:                                allocate_blob().
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int rd_icp_val_array(val_array_ptr,count_ptr)
    array_value_type **val_array_ptr;
    icp_int           *count_ptr;
{
    array_value_type *value_ptr;
    icp_int           i;

#ifdef DEBUG
    strcpy(where_in_extension,"rd_icp_val_array");
    printf("        %s\n",where_in_extension);
#endif

/*  Read the size of the value array (the number of
    separate values) off of the ICP message, allocate
    space for the array, and attach to value array pointer.
    --------------------------------------------------------*/
    *count_ptr = rdicpbyte();
    if (allocate_blob((*count_ptr * sizeof(array_value_type)), (char**)val_array_ptr)
                                                                 != ICP_SUCCESS)
        return(ICP_FAILURE);

/*  Read in the values.  The value array will occupy the blob just
    allocated and will contain array value types.  For those values which
    are strings, symbols, or arrays, the actual value will be stored
    in individual blobs allocated indirectly by value_array_recurse().
    --------------------------------------------------------------------*/
    value_ptr = *val_array_ptr;
    for (i=0; i<*count_ptr; i++, value_ptr++)
        if (value_array_read_recurse(value_ptr) != ICP_SUCCESS)
            return(ICP_FAILURE);

    return(ICP_SUCCESS);

} /* end rd_icp_val_array */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION wr_icp_int:                       Copyright (C) 1986-2017 Gensym Corporation
:
:  This function will write an integer element of an ICP message into the ICP
:  write buffer.
:
:  Arguments:        value   An integer to send.
:  Return Behavior:  None (void function).
:  Users:            ??
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
void wr_icp_int(value)
    icp_int value;
{
    icp_int negative = FALSE;

#ifdef DEBUG
    strcpy(where_in_extension,"wr_icp_int");
    printf("        %s\n",where_in_extension);
#endif

/*  If outside of "regular" range (-31,500 to 31,500), call
    wr_large_int() with the absolute value of the value and
    a flag indicating whether or not the value is negative.
    ----------------------------------------------------------*/
    if ((value < MIN_ICP_INT) || (value > MAX_ICP_INT)) {
        if (value < 0) {
            negative = TRUE;
            value = -value; }
        wr_large_int(value, negative); }

/*  If inside "regular" range, cast to short and add MAX
    as an offset, giving a range "in transit" of 0 to 63000.
    ----------------------------------------------------------*/
    else {
        wricpbyte(value + MAX_ICP_INT); }

} /* end wr_icp_int */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION wr_large_int:                     Copyright (C) 1986-2017 Gensym Corporation
:
:  This function will write a large integer element of an ICP message into the
:  ICP write buffer.  Although translated directly from the lisp version which
:  handles 1000-byte integers, this function can only send 32-bit integers.
:
:  Arguments:        value     An integer to send.
:                    negative  A flag, TRUE or FLASE indicating value's sign.
:  Return Behavior:  None (void function).
:  Users:            local: wr_icp_int()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
void wr_large_int(value, negative)
    icp_int value;
    icp_int negative;
{
    icp_int upper;
    icp_int lower;
    icp_int sign_and_length;
  
#ifdef DEBUG
    strcpy(where_in_extension,"wr_large_int");
    printf("        %s\n",where_in_extension);
#endif

/*  Mask lower to be the least significant 16 bits.
    ------------------------------------------------*/
    lower = value & 0xffff;

/*  Mask upper to be the most significant
    16 bits with the sign bit lopped off.
    --------------------------------------*/
    upper = (value & 0x7fff0000) >> 15;      /*) & 0x0000ffff;*/

/*  Prepare the first byte which will indicate sign
    and the number of bytes taken to send the integer.
    -------------------------------------------------*/
    if (negative)
        sign_and_length = MAX_ICP_US_INT + MAX_ICP_INT_LEN;
    else
        sign_and_length = MAX_ICP_US_INT;

/*  Send first byte, and high order byte if appropriate.
    -----------------------------------------------------*/
    if (upper == 0)
        wricpbyte(sign_and_length+1);
    else {
        wricpbyte(sign_and_length+2);
        wricpbyte(upper); }

/*  In any case send the low order ICP byte.
    -----------------------------------------*/
    wricpbyte(lower);

}  /* end wr_large_int */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION wr_icp_usint:                     Copyright (C) 1986-2017 Gensym Corporation
:
:  This function will write an unsigned integer element of an ICP message into
:  the ICP write buffer.
:
:  Arguments:        value   An unsigned integer to send.
:  Return Behavior:  None (void function).
:  Users:            used for writing the variable status only (aka error_cd).
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
void wr_icp_usint(value)
    icp_int value;
{
#ifdef DEBUG
    strcpy(where_in_extension,"wr_icp_usint");
    printf("        %s\n",where_in_extension);
#endif

/*  If value is greater than the maximum for an unsigned
    short, send it in two parts using wr_large_int().
    ------------------------------------------------------*/
    if (value > MAX_ICP_US_INT)
        wr_large_int(value, FALSE);

/*  otherwise, send value without any modifications.
    -------------------------------------------------*/
    else
        wricpbyte(value);

} /* end wr_icp_usint */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION wr_icp_64float:                   Copyright (C) 1986-2017 Gensym Corporation
:
:  This function writes a double-float element of an ICP message to the write 
:  buffer for the current context.
:
:  Arguments:        value A double floating point number.
:  Return Behavior:  None (void function).
:  Users:            ??
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
void wr_icp_64float(value)
    double value;
{
    icp_byte      float_parts[4];

#ifdef DEBUG
    strcpy(where_in_extension,"wr_icp_64float");
    printf("        %s\n",where_in_extension);
#endif

/*  Call a function to break the float into pieces parts.
    ------------------------------------------------------*/
    g2ext_foreign_partition_float(value, float_parts, 0);

/*  Write the pieces parts out to the write buffer.
    -------------------------------------------------*/
    wricpbyte( (icp_int) float_parts[0]);
    wricpbyte( (icp_int) float_parts[1]);
    wricpbyte( (icp_int) float_parts[2]);
    wricpbyte( (icp_int) float_parts[3]);

} /* end wr_icp_64float */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION wr_icp_str:                       Copyright (C) 1986-2017 Gensym Corporation
:
:  This function will write a string element of an ICP message into the ICP
:  write buffer.
:
:  Arguments:        string   A pointer to characters to send.
:  Return Behavior:  None (void function).
:  Users:            ??
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
void wr_icp_str(string)
    char    *string;
{  
    char    *source, *filtered;
    icp_int  length, length_16;
    icp_byte char_pair;
    icp_int  i;

#ifdef DEBUG
    strcpy(where_in_extension,"wr_icp_str");
    printf("        %s\n",where_in_extension);
#endif

/*  If string checking is on we will need another buffer twice the size of
    (200%) of the source string and we will need to recalculate the length.
    Note, the oversized allocation is to accomodate the worst case (e.g. if 
    someone sends a string of all line feeds where each '\n' (1 char) will
    get converted to '@L' (2 chars)).
    ------------------------------------------------------------------------*/
    length = strlen(string);
    if (icp_option_is_set(ICP_STRING_CHECK)) {
        if (allocate_blob(length * 2,&filtered) != ICP_SUCCESS)
            return;
        ascii_to_gensym(string, filtered);
        length = strlen(filtered);
        source = filtered; }
    else
        source = string;

/*  Calculate the length in 16-bit ICP bytes, and send the length
    in 8-bit bytes followed by the string in 16-bit chunks.
    --------------------------------------------------------------*/
    length_16 = (length >> 1) ;
    wricpbyte(length);
    for (i=0; i<length_16; i++) {

    /*  Take one character into the char pair, move the character
        to the left by one byte, and increment the source pointer.
        -------------------------------------------------------------*/
        char_pair = ((icp_byte) *source) << 8;
        source++;

    /*  Take another character and add it into the low
        order byte, and increment the source pointer.
        -----------------------------------------------*/
        char_pair = char_pair + ((icp_byte) *source);
        source++;

    /*  Write the ICP byte out to the write buffer.
        --------------------------------------------*/
        wricpbyte((icp_int) char_pair);

      } /* end for */

/*  If there are an odd number of characters in the string,
    the last character gets sent in an ICP byte unaccompanied.
    -----------------------------------------------------------*/
    if (length & 0x01) {
        char_pair = *source; 
        wricpbyte((icp_int) char_pair); }

/*  If string checking is on and we are in one-cycle mode, reclaim all blobs
    just in case the customer never calls the main run loop (which is the
    only other place blobs are reclaimed).
    -----------------------------------------------------------------------*/
    if (icp_option_is_set(ICP_STRING_CHECK) && 
        icp_option_is_set(ICP_ONE_CYCLE))
      reclaim_used_blobs();

} /* end wr_icp_str */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION wr_icp_int_array:                 Copyright (C) 1986-2017 Gensym Corporation
:
:  This function will write an integer array element of an ICP message into the
:  write buffer.  An integer array element in ICP consists of a count, followed
:  by 'count' integers.
:
:  Arguments:        int_array  Integer array.
:                    count      Count of integers in the array.
:  Return Behavior:  None (void function).
:  Users:            gsi.c:  write_object_value()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
void wr_icp_int_array(int_array,count)
    icp_int *int_array;
    icp_int  count;
{
    icp_int  *integer_ptr;
    icp_int   i;

#ifdef DEBUG
    strcpy(where_in_extension,"wr_icp_int_array");
    printf("        %s\n",where_in_extension);
#endif

/*  Write the array size into the ICP message in the write buffer.
    ----------------------------------------------------------------*/
    wricpbyte(count);

/*  Write the integers into the ICP message in the write buffer.
    -------------------------------------------------------------*/
    integer_ptr = int_array;
    for (i=0; i<count; i++, integer_ptr++)
        wr_icp_int(*integer_ptr);

} /* end wr_icp_int_array */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION wr_icp_flt_array:                 Copyright (C) 1986-2017 Gensym Corporation
:
:  This function will write a float array element of an ICP message into the
:  write buffer.  An float array element in ICP consists of a count, followed
:  by 'count' floats.
:
:  Arguments:        flt_array  Float array.
:                    count      Count of floats in the array.
:  Return Behavior:  None (void function).
:  Users:            gsi.c:  write_object_value()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
void wr_icp_flt_array(flt_array,count)
    double  *flt_array;
    icp_int  count;
{
    double  *float_ptr;
    icp_int  i;

#ifdef DEBUG
    strcpy(where_in_extension,"wr_icp_flt_array");
    printf("        %s\n",where_in_extension);
#endif

/*  Write the array size into the ICP message in the write buffer.
    ----------------------------------------------------------------*/
    wricpbyte(count);

/*  Write the floats into the ICP message in the write buffer.
    -------------------------------------------------------------*/
    float_ptr = flt_array;
    for (i=0; i<count; i++, float_ptr++)
        wr_icp_64float(*float_ptr);

} /* end wr_icp_flt_array */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION wr_icp_str_array:                 Copyright (C) 1986-2017 Gensym Corporation
:
:  This function will write a string array element of an ICP message into the
:  write buffer.  A string array element in ICP consists of a count, followed
:  by 'count' strings, each of which is a length followed by 'length' characters.
:
:  Arguments:        str_array  String array.
:                    count      Count of floats in the array.
:  Return Behavior:  None (void function).
:  Users:            gsi.c:  write_object_value()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
void wr_icp_str_array(str_array,count)
    char   **str_array;
    icp_int  count;
{
    char  **string_ptr;
    icp_int i;

#ifdef DEBUG
    strcpy(where_in_extension,"wr_icp_str_array");
    printf("        %s\n",where_in_extension);
#endif

/*  Write the array size into the ICP message in the write buffer.
    ----------------------------------------------------------------*/
    wricpbyte(count);

/*  Write the strings into the ICP message in the write buffer.
    -------------------------------------------------------------*/
    string_ptr = str_array;
    for (i=0; i<count; i++, string_ptr++)
        wr_icp_str(*string_ptr);

} /* end wr_icp_str_array */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION wr_icp_val_array:                 Copyright (C) 1986-2017 Gensym Corporation
:
:  This function will write a value array element of an ICP message into the
:  write buffer.  A value array element in ICP consists of a count, followed
:  by 'count' values, each of which is a type/value combination.  Nested arrays
:  are supported.
:
:  Arguments:        val_array  Value array.
:                    count      Count of values in the array.
:  Return Behavior:  None (void function).
:  Users:            gsi.c:  write_object_value()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
void wr_icp_val_array(val_array,count)
    array_value_type *val_array;
    icp_int           count;
{
    array_value_type *value_ptr;
    icp_int           i;

#ifdef DEBUG
    strcpy(where_in_extension,"wr_icp_val_array");
    printf("        %s\n",where_in_extension);
#endif

/*  Write the array size into the ICP message in the write buffer.
    ----------------------------------------------------------------*/
    wricpbyte(count);

/*  Write the values into the ICP message in the write buffer.
    -------------------------------------------------------------*/
    value_ptr = val_array;
    for (i=0; i<count; i++, value_ptr++)
        value_array_write_recurse(value_ptr);

} /* end wr_icp_val_array */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION read_object_value:                Copyright (C) 1986-2017 Gensym Corporation
:
:  This function receives a pointer to an obj_value_type (TEMP_PARAM), and reads
:  data off of an incoming ICP message to fill structure to which the pointer
:  points.
:
:  Arguments:        value_ptr  Pointer to an object value structure.
:  Return Behavior:  ICP_SUCCESS is always returned.
:  Users:            local:    load_object_rcvr()
:                    rpc.c: rpc_start_rcvr(), rpc_call_rcvr(),
:                              rpc_ret_vals_rcvr()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int read_object_value(value_ptr)
    obj_value_type *value_ptr;
{
#ifdef DEBUG
    strcpy(where_in_extension,"read_object_value");
    printf("    %s\n",where_in_extension);
#endif

/*  Read in the type of the object value.
    ---------------------------------------*/
    value_ptr->p_type = rdicpbyte();

/*  Read in the value in accordance with the type.
    -----------------------------------------------*/
    switch(value_ptr->p_type) {
        case NULL_TAG:
    	    break;
        case INTEGER_TAG:
        case LOGICAL_TAG:
    	    value_ptr->p_value.integer_p = rd_icp_int();
            value_ptr->count = sizeof(icp_int);
            break;    
        case SYMBOL_TAG:
        case STRING_TAG: 
    	    if (rd_icp_str(value_ptr) != ICP_SUCCESS)
                return(ICP_FAILURE);
            break;
        case FLOAT64_TAG:
    	    value_ptr->p_value.float_p = rd_icp_64float();
            value_ptr->count = sizeof(double);
            break;
/*	case INTEGER_ARRAY_TAG:
	case LOGICAL_ARRAY_TAG:
            if (rd_icp_int_array(&value_ptr->p_value.int_array,
                                 &value_ptr->count) != ICP_SUCCESS)
                return(ICP_FAILURE);
            break;
	case SYMBOL_ARRAY_TAG:
	case STRING_ARRAY_TAG:
            if (rd_icp_str_array(&value_ptr->p_value.str_array,
                                 &value_ptr->count) != ICP_SUCCESS)
                return(ICP_FAILURE);
            break;
	case FLOAT64_ARRAY_TAG:
            if (rd_icp_flt_array(&value_ptr->p_value.flt_array,
                                 &value_ptr->count) != ICP_SUCCESS)
                return(ICP_FAILURE);
            break;
	case VALUE_ARRAY_TAG:
            if (rd_icp_val_array(&value_ptr->p_value.val_array,
                                 &value_ptr->count) != ICP_SUCCESS)
                return(ICP_FAILURE);
            break;   */
	default:
            ext_error(INTERNAL_INCONSISTENCY,"read_object_value, type",
                      value_ptr->p_type,SEND);
            return(ICP_FAILURE);

    } /* end switch */

    return(ICP_SUCCESS);

} /* end read_object_value */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION write_object_value:               Copyright (C) 1986-2017 Gensym Corporation
:
:  This function receives a pointer to an obj_value_type (TEMP_PARAM), and
:  writes the contents on to an outgoing ICP message.
:
:  Arguments:        value_ptr  Pointer to an object value structure.
:  Return Behavior:  ICP_FAILURE is returned on bad type.  Otherwise,
:                    ICP_SUCCESS is returned.
:  Users:            gsi.c: gsi_return_values(), gsi_return_timed_values(),
:                           gsi_return_attributes(), gsi_return_timed_attributes()
:                    rpc.c: rpc_call_in_ctx(), rpc_start_in_ctx(),
:                           rpc_return_values()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int write_object_value(value_ptr)
     obj_value_type *value_ptr;
{
#ifdef DEBUG
    strcpy(where_in_extension,"write_object_value");
    printf("    %s\n",where_in_extension);
#endif

/*  Send the value and type in accordance with the type.
    ------------------------------------------------------*/
    switch(value_ptr->p_type) {
        case NULL_TAG:
            wricpbyte(value_ptr->p_type);
            break;
        case INTEGER_TAG:
        case LOGICAL_TAG:
            wricpbyte(value_ptr->p_type);
    	    wr_icp_int(value_ptr->p_value.integer_p);
            break;
        case SYMBOL_TAG: 
        case STRING_TAG: 
            wricpbyte(value_ptr->p_type);
            wr_icp_str(value_ptr->p_value.string_p);
            break;
        case FLOAT64_TAG:
            wricpbyte(value_ptr->p_type);
    	    wr_icp_64float(value_ptr->p_value.float_p);
            break;
/*	case INTEGER_ARRAY_TAG:
	case LOGICAL_ARRAY_TAG:
            wricpbyte(value_ptr->p_type);
            wr_icp_int_array(value_ptr->p_value.int_array,value_ptr->count);
            break;
        case SYMBOL_ARRAY_TAG: 
        case STRING_ARRAY_TAG: 
            wricpbyte(value_ptr->p_type);
            wr_icp_str_array(value_ptr->p_value.str_array,value_ptr->count);
            break;
        case FLOAT64_ARRAY_TAG:
            wricpbyte(value_ptr->p_type);
            wr_icp_flt_array(value_ptr->p_value.flt_array,value_ptr->count);
            break;
        case VALUE_ARRAY_TAG:
            wricpbyte(value_ptr->p_type);
            wr_icp_val_array(value_ptr->p_value.val_array,value_ptr->count);
            break;  */
        default:
            ext_error(INVALID_TYPE_TAG,"write_object_value, type",
                      value_ptr->p_type,NO_SEND);
            return(ICP_FAILURE);

    } /* end switch */

    return(ICP_SUCCESS);

} /* end write_object_value */



/*******************************************************************
 * GensymToAscii performs the following conversions:
 *   ~@   -->  @
 *   ~\   -->  \
 *   ~~   -->  ~
 *   @L   -->  LF
 ********************************************************************/

icp_int gensym_to_ascii(gensym_text, ascii_string_buffer)
    unsigned char *gensym_text;
    unsigned char *ascii_string_buffer;
{
    unsigned char gensym_char;
    icp_int gensym_index = 0;
    icp_int ascii_index = 0;

    gensym_char = gensym_text[gensym_index++];
    while ( gensym_char != '\0' ) {

      switch (gensym_char) {

	case '~':  /* TILDE */
	  gensym_char = gensym_text[gensym_index++];
	  switch (gensym_char) {
	    case '\0':
	      ascii_string_buffer[ascii_index++] = '~';
	      gensym_index--;
	      break;
	    case '@':		/* TILDE-AT-SIGN */
	    case '~':		/* TILDE-TILDE */
	    case '\\':		/* TILDE-BACKSLASH */
	      ascii_string_buffer[ascii_index++] = gensym_char;
	      break;
	    default:		/* TILDE-default */
	      ascii_string_buffer[ascii_index++] = '~';
	      ascii_string_buffer[ascii_index++] = gensym_char;
	      break;
	  } /* end switch */
	  break;

	case '@':  /* AT-SIGN */
	  gensym_char = gensym_text[gensym_index++];
	  switch (gensym_char) {
	    case '\0':
	      ascii_string_buffer[ascii_index++] = '@';
	      gensym_index--;
	      break;
	    case 'L':		/* AT-SIGN-L */
	      ascii_string_buffer[ascii_index++] = (char)0x0A; /*LF*/
	      break;
	    default:		/* AT-SIGN-default */
	      ascii_string_buffer[ascii_index++] = '@';
	      ascii_string_buffer[ascii_index++] = gensym_char;
	      break;
          } /* end switch */
	  break;

	default:  /* UNQUOTED CHARCTER */
	  ascii_string_buffer[ascii_index++] = gensym_char;
	  break;

      } /* end switch */

      gensym_char = gensym_text[gensym_index++];

    } /* end while */
    ascii_string_buffer[ascii_index] = gensym_char;  /* = '\0' */
    return(ascii_index);
}


/**********************************************************************
 *  AsciiToGensym performs the following conversions:
 *   @ (0x64)  -->  ~@
 *   \ (0x5c)  -->  ~\
 *   ~ (0x7e)  -->  ~~
 *   LF (0x0A) -->  @L
 * The length of the Gensym text is returned.
 *
 */

icp_int ascii_to_gensym(ascii_string, gensym_text_buffer)
    unsigned char *ascii_string;
    unsigned char *gensym_text_buffer;
{
    icp_int       gensym_index = 0;
    unsigned char ascii_char;
    icp_int       ascii_index = 0;


    ascii_char = ascii_string[ascii_index++];
    while ( ascii_char != '\0' ) {

      switch (ascii_char) {

        case '@':
	  gensym_text_buffer[gensym_index++] = '~';
	  gensym_text_buffer[gensym_index++] = '@';
	  break;
        case '\\':
	  gensym_text_buffer[gensym_index++] = '~';
	  gensym_text_buffer[gensym_index++] = '\\';
	  break;
        case '~':
	  gensym_text_buffer[gensym_index++] = '~';
          gensym_text_buffer[gensym_index++] = '~';
	  break;
        case '\12':                      /* "\n" */
	  gensym_text_buffer[gensym_index++] = '@';
	  gensym_text_buffer[gensym_index++] = 'L';
	  break;
        default:
          gensym_text_buffer[gensym_index++] = ascii_char;

      } /* end switch */

      ascii_char = ascii_string[ascii_index++];

    } /* end while */

    gensym_text_buffer[gensym_index] = ascii_char;  /* = '\0' */
    return (gensym_index);
}


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION value_array_read_recurse:         Copyright (C) 1986-2017 Gensym Corporation
:
:  Not directly recursive, this function may call itself, via rd_icp_val_array()
:  for those cases where a value array contains, among its value elements,
:  another value array.
:
:  Arguments:        array_value_ptr  Pointer to an array_value_type to be set
:                                     according to the data in the ICP message.
:  Return Behavior:  Always returns ICP_SUCCESS.
:  Users:            local:  rd_icp_val_array()
:  Memory Impact:    Indirect -- if any of the values are arrays, malloc may be
:                                called indirectly by one of the array readers.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int value_array_read_recurse(array_value_ptr)
    array_value_type  *array_value_ptr;
{
    icp_int length;

#ifdef DEBUG
    strcpy(where_in_extension,"value_array_read_recurse");
    printf("        %s\n",where_in_extension);
#endif

/*  Read the value type and then read the value according to the type.
    -------------------------------------------------------------------*/
    array_value_ptr->p_type = rdicpbyte();
    switch(array_value_ptr->p_type) {
        case NULL_TAG:
    	    break;
        case INTEGER_TAG:
        case LOGICAL_TAG:
    	    array_value_ptr->p_value.integer_p = rd_icp_int();
            break;    
        case SYMBOL_TAG:
        case STRING_TAG:
            length = rdicpbyte();
            if (allocate_and_rd_icp_chars(&length,
                                          &array_value_ptr->p_value.string_p)
                                                                 != ICP_SUCCESS)
                return(ICP_FAILURE);
            break;
        case FLOAT64_TAG:
    	    array_value_ptr->p_value.float_p = rd_icp_64float();
            break;
/*	case INTEGER_ARRAY_TAG:
	case LOGICAL_ARRAY_TAG:
            if (rd_icp_int_array(&array_value_ptr->p_value.int_array,
                                 &array_value_ptr->count) != ICP_SUCCESS)
                return(ICP_FAILURE);
            break;
	case SYMBOL_ARRAY_TAG:
	case STRING_ARRAY_TAG:
            if (rd_icp_str_array(&array_value_ptr->p_value.str_array,
                                 &array_value_ptr->count) != ICP_SUCCESS)
                return(ICP_FAILURE);
            break;
	case FLOAT64_ARRAY_TAG:
            if (rd_icp_flt_array(&array_value_ptr->p_value.flt_array,
                                 &array_value_ptr->count) != ICP_SUCCESS)
                return(ICP_FAILURE);
            break;
	case VALUE_ARRAY_TAG:
            if (rd_icp_val_array(&array_value_ptr->p_value.val_array,
                                 &array_value_ptr->count) != ICP_SUCCESS)
                return(ICP_FAILURE);
            break; */
	default:
            ext_error(INTERNAL_INCONSISTENCY,"value_array_read_recurse, type",
                      array_value_ptr->p_type,SEND);
            return(ICP_FAILURE);

    } /* end switch */

    return(ICP_SUCCESS);

} /* end value_array_read_recurse */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION value_array_write_recurse:        Copyright (C) 1986-2017 Gensym Corporation
:
:  Not truly recursive, this function may call itself, via wr_icp_val_array()
:  for those cases where a value array contains, among its value elements,
:  another value array.
:
:  Arguments:        array_value_ptr  Pointer to an array_value_type.
:  Return Behavior:  Always returns ICP_SUCCESS.
:  Users:            local:wr_icp_val_array()
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int value_array_write_recurse(array_value_ptr)
     array_value_type  *array_value_ptr;
{
#ifdef DEBUG
    strcpy(where_in_extension,"value_array_write_recurse");
    printf("        %s\n",where_in_extension);
#endif

/*  Send the value and type in accordance with the type.
    ------------------------------------------------------*/
    switch(array_value_ptr->p_type) {
        case NULL_TAG:
            wricpbyte(array_value_ptr->p_type);
            break;
        case INTEGER_TAG:
        case LOGICAL_TAG:
            wricpbyte(array_value_ptr->p_type);
    	    wr_icp_int(array_value_ptr->p_value.integer_p);
            break;
        case SYMBOL_TAG: 
        case STRING_TAG: 
            wricpbyte(array_value_ptr->p_type);
            wr_icp_str(array_value_ptr->p_value.string_p);
            break;
        case FLOAT64_TAG:
            wricpbyte(array_value_ptr->p_type);
    	    wr_icp_64float(array_value_ptr->p_value.float_p);
            break;
/*	case INTEGER_ARRAY_TAG:
	case LOGICAL_ARRAY_TAG:
            wricpbyte(array_value_ptr->p_type);
            wr_icp_int_array(array_value_ptr->p_value.int_array,
                             array_value_ptr->count);
            break;
        case SYMBOL_ARRAY_TAG: 
        case STRING_ARRAY_TAG: 
            wricpbyte(array_value_ptr->p_type);
            wr_icp_str_array(array_value_ptr->p_value.str_array,
                             array_value_ptr->count);
            break;
        case FLOAT64_ARRAY_TAG:
            wricpbyte(array_value_ptr->p_type);
            wr_icp_flt_array(array_value_ptr->p_value.flt_array,
                             array_value_ptr->count);
            break;
        case VALUE_ARRAY_TAG:
            wricpbyte(array_value_ptr->p_type);
            wr_icp_val_array(array_value_ptr->p_value.val_array,
                             array_value_ptr->count);
            break; */
        default:
            ext_error(INVALID_TYPE_TAG,"value_array_write_recurse, type",
                      array_value_ptr->p_type,NO_SEND);
            return(ICP_FAILURE);

    } /* end switch */

    return(ICP_SUCCESS);

} /* end value_array_write_recurse */


/*  ---------------------------------------------------------------------------

The following 40 or so functions are designed to act as layer on top of the
standard GSI toolkit routines.  This layer provides succinct, clear, and full
access to the GSI data structures used by GSI application programmers while
effectively removing from the user the burden of learning these structure by
heart.

In creating this layer, the opportunity presented itself to rethink the names of
these structures to better match the naming conventions of G2 and common sense.
To wit, aliases (via typedefs) have also been defined which replace all
occurances of structure type names such as TEMP_ARG_TYPE and USER_ARG_TYPE.

----------------------------------------------------------------------------  */

tag_type gsi_type_of ( x )
    obj_value_type* x;
{
    return (x->p_type);
}

G2int_type gsi_length_of ( x )
    obj_value_type* x;
{
    return (x->count);
}

void gsi_set_type ( x, to )
    obj_value_type* x;
    tag_type        to;
{
    x->p_type = to;
}

G2int_type gsi_int_of ( x )
    obj_value_type* x;
{
    return (x->p_value.integer_p);
}

G2log_type gsi_log_of ( x )
    obj_value_type* x;
{
    return (x->p_value.logical_p);
}

G2flt_type gsi_flt_of ( x )
    obj_value_type* x;
{
    return (x->p_value.float_p);
}

G2sym_type* gsi_sym_of ( x )
    obj_value_type* x;
{
    return (x->p_value.symbol_p);
}

G2str_type* gsi_str_of ( x )
    obj_value_type* x;
{
    return (x->p_value.string_p);
}

void gsi_set_int ( x, to )
    obj_value_type* x;
    G2int_type      to;
{
    if (integer_is_out_of_range(to)) {
      ext_error(G2_INTEGER_OVERFLOW,
               "gsi_set_int, value",to,NO_SEND);
      x->p_type = NULL_TAG; }
    else {
      x->p_type = INTEGER_TAG;
      x->p_value.integer_p = to;
      x->count = sizeof(icp_int); }
}

void gsi_set_log ( x, to )
    obj_value_type* x;
    G2log_type      to;
{
    if (logical_is_out_of_range(to)) {
      ext_error(LOGICAL_OUT_OF_RANGE,
               "gsi_set_log, value",to,NO_SEND);
      x->p_type = NULL_TAG; }
    else {
      x->p_type = LOGICAL_TAG;
      x->p_value.logical_p = to;
      x->count = sizeof(icp_int); }
}

void gsi_set_flt ( x, to )
    obj_value_type* x;
    G2flt_type      to;
{
    x->p_type = FLOAT64_TAG;
    x->p_value.float_p = to;
    x->count = sizeof(double);
}

void gsi_set_sym ( x, to )
    obj_value_type* x;
    G2sym_type*     to;
{
    x->p_type = SYMBOL_TAG;
    x->p_value.symbol_p = to;
    x->count = strlen(to);
}

void gsi_set_str ( x, to )
    obj_value_type* x;
    G2str_type*     to;
{            
    x->p_type = STRING_TAG;
    x->p_value.string_p = to;
    x->count = strlen(to);
}

obj_index_type gsi_obj_index_of ( x )
    obj_with_index_type* x;
{
    return x->obj_index;
}

void gsi_set_obj_index ( x, to )
    obj_with_index_type* x;
    obj_index_type       to;
{
    x->obj_index = to;
}

status_type gsi_status_of ( x )
    obj_type* x;
{
    return x->error_cd;
}

void gsi_set_status ( x, to )
    obj_type*   x;
    status_type to;
{
    x->error_cd = to;
}

interval_type gsi_interval_of(x)
    obj_def_type* x;
{
    obj_type *y;

    if (x->type == ICP_OBJ_DEF)
        return (x->interval);
    y = (obj_type *) x;
    return (y->interval);
}

void gsi_set_interval(x,to)
    obj_def_type*   x;
    interval_type to;
{
    obj_type *y;

    if (x->type == ICP_OBJ_DEF)
        x->interval = to;
    else {
        y = (obj_type *) x;
        y->interval = to; }
}
char *gsi_name_of ( x )
    obj_def_type *x;
{
  if (x->type == ICP_OBJ_DEF)
    return (x->name);
  else {
    ext_error(EXPECTED_OBJ_DEF_TYPE,"name_of",NO_DATA,NO_SEND);
    return (0); }
}

char *gsi_class_of ( x )
    obj_def_type *x;
{
  if (x->type == ICP_OBJ_DEF)
    return (x->class);
  else {
    ext_error(EXPECTED_OBJ_DEF_TYPE,"class_of",NO_DATA,NO_SEND);
    return (0); }
}

obj_value_type* gsi_def_attr1_of ( x )
    obj_def_type *x;
{
    return (&(x->param_1));
}

obj_value_type* gsi_def_attr2_of ( x )
    obj_def_type *x;
{
    return (&(x->param_2));
}

obj_value_type* gsi_def_attr3_of ( x )
    obj_def_type *x;
{
    return (&(x->param_3));
}

obj_value_type* gsi_def_attr4_of ( x )
    obj_def_type *x;
{
    return (&(x->param_4));
}

obj_value_type* gsi_def_attr5_of ( x )
    obj_def_type *x;
{
    return (&(x->param_5));
}

obj_value_type* gsi_def_attr6_of ( x )
    obj_def_type *x;
{
    return (&(x->param_6));
}

obj_value_type* gsi_obj_of ( x )
    obj_def_type *x;
{
    return (&(x->value));
}

obj_value_type* gsi_value_of ( x )
    obj_type* x;
{
    return (&(x->value));
}

void gsi_set_value ( x, to )
    obj_type*       x;
    obj_value_type* to;
{
    memcpy((void *)&x->value, (void *)to, sizeof(obj_value_type));
}

attr_value_type* gsi_attr_of ( x )
    attr_type* x;
{
    return (&(x->value));
}

void gsi_set_attr ( x, to )
    attr_type*       x;
    attr_value_type* to;
{
    memcpy((void *)&x->value, (void *)to, sizeof(attr_value_type));
}

attr_name_type* gsi_attr_name_of ( x )
    attr_type* x;
{
    return ((attr_name_type*) (x->attribute));
}

void gsi_set_attr_name ( x, to )
    attr_type*      x;
    attr_name_type* to;
{
    strcpy(x->attribute, to);
}

icp_timestamp_type* gsi_time_of ( x )
    timed_obj_type* x;
{
    return (&(x->date));
}

void gsi_set_time ( x, to )
    timed_obj_type*     x;
    icp_timestamp_type* to;
{
    memcpy((void *)&x->date, (void *)to, sizeof(icp_timestamp_type));
}

icp_timestamp_type* gsi_attr_time_of ( x )
    timed_attr_type* x;
{
    return (&(x->date));
}

void gsi_set_attr_time ( x, to )
    timed_attr_type*    x;
    icp_timestamp_type* to;
{
    memcpy((void *)&x->date, (void *)to, sizeof(icp_timestamp_type));
}

boolean is_timed ( x )
    timed_attr_type* x;
{
    return (x->is_timed);
}

void gsi_set_is_timed ( x, to )
    timed_attr_type* x;
    boolean          to;
{
    x->is_timed = to;
}

obj_def_ptr_type gsi_def_of(x,context)
    obj_index_type x;
    icp_int context;
{
    return(icp_context_table[context].export_tbl[x].obj_ptr);
}

user_ptr_type gsi_user_ptr_of(x,context)
    obj_index_type x;
    icp_int        context;
{
    return(icp_context_table[context].export_tbl[x].user_def.user_ptr);
}

void gsi_set_user_ptr(x,to,context)
    obj_index_type x;
    user_ptr_type  to;
    icp_int        context;
{
    icp_context_table[context].export_tbl[x].user_def.user_ptr = to;
}

icp_int gsi_user_int_of(x,context)
    obj_index_type x;
    icp_int        context;
{
    return(icp_context_table[context].export_tbl[x].user_def.user_long);
}

void gsi_set_user_int(x,to,context)
    obj_index_type x;
    icp_int        to;
    icp_int        context;
{
    icp_context_table[context].export_tbl[x].user_def.user_long = to;
}

