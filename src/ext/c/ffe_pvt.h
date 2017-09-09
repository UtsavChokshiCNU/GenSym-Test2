/*******************************************************************************

File name:               ffe_pvt.h
Owner:                   Peter Fandel

Purpose:                 This include file has defines and typedefs and globals
                         required by FFE (the foreign function extension).

This file depends on:    Nothing.

Dependent files:         foreign.c

Legal Notice:            Copyright (C) 1986-2017 Gensym Corporation.,
                         125 CambridgePark Drive, Cambridge MA 02140
                         All rights reserved.

History:                 19feb93  PAF  Created.


*******************************************************************************/

ffe_int ffe_include_file_major_version = ICP_MAJ_VER_NUM;
ffe_int ffe_include_file_minor_version = ICP_MIN_VER_NUM;

#define FFS_MAX_ERROR_STRING_LENGTH 80
#define FFS_MAX_OOB_MESSAGE_LENGTH  80

#define FFS_UNSPECIFIED_ERROR         1
#define FFS_CONNECTION_OPEN_ALREADY   2
#define FFS_SIGNAL_CAUGHT_DURING_CALL 3
#define FFS_UNKNOWN_FUNCTION          4
#define FFS_UNKNOWN_RETURN_TYPE       5
/* other error codes go here */

#ifndef FFS_DEBUG
#define FFS_DEBUG 0
#endif
#define FFS_DEBUG_VERBOSE (FFS_DEBUG && 1)

/* 
 * the following FFS-specific message codes must be co-ordinated with those in the
 * G2 module INT1.
 */
#define FFS_IMAGE_READY_MESSAGE                310
#define FFS_REQUEST_FOREIGN_REGISTRY_MESSAGE   311
#define FFS_PROVIDE_FOREIGN_REGISTRY_MESSAGE   312
#define FFS_CALL_FOREIGN_FUNCTION_MESSAGE      313
#define FFS_RETURN_FOREIGN_VALUE_MESSAGE       314
#define FFS_SIGNAL_ERROR_MESSAGE               315
#define FFS_KILL_SERVER_MESSAGE                316
#define FFS_SHUT_DOWN_CONTEXT_MESSAGE          317

/* 
 * We must get FFS port from argv, since it must be different for every foreign
 * image.
 */
ffe_int ffs_socket_number = 12345; /* only needed in tcp/ip */
#define DECNET_OBJECT_NAME "FFS01"

/* The following incantation sets up the icp output buffer correctly. */


#define send_ffs_message() \
    curr_ctx->loaded = TRUE; \
    if (curr_ctx->write_index >= icp_flush_point) \
        icp_flush();


/* 
 * Make sure ffs_error_string is written into for every error, 
 * lest we get inappropriate debugging information.
 */
char     ffs_error_string[FFS_MAX_ERROR_STRING_LENGTH];


/* These version tags are set in handle_req_foreign_registry */
ffe_int     g2_major_version = 0;
ffe_int     g2_minor_version = 0;

/* We don't want more than one process connected to the FFS. */
ffe_int     ffs_connection_open_p = FALSE;


/*
 * Note that the function_address slot in the foreign_function_entry struct is not
 * the address of the original foreign function (the one that G2 would dynamically
 * link to in the old scheme).  This slot contains the entry point of an overlay
 * function which takes an array of pointers to TEMP_PARAM structs.
 *
 * Further note that the index field is 1-based, not 0-based.  This is so the the
 * calloc statements which generate foreign_function_registry are more legible.
 * The trade off is we have to subtract 1 to get the proper index into
 * foreign_function_registry.
 */
typedef
struct foreign_function_entry
{
 char                           *name;
 ffe_int                         index;
 obj_value_type                 *(*function_address)(); 
 ffe_int                         argcount;
 obj_value_type                 *arglist;
 ffe_int                        *typelist;
 ffe_int                         return_type;
 struct foreign_function_entry  *next_entry;

} FOREIGN_FUNCTION_ENTRY;

FOREIGN_FUNCTION_ENTRY     *latest_foreign_entry = NULL;

FOREIGN_FUNCTION_ENTRY     *foreign_function_registry;

#ifdef FFS_DEBUG_VERBOSE
char *
foreign_typetag_to_string(typetag)
ffe_int     typetag;
{
 switch (typetag)
 {
  case INTEGER_TAG: return "integer"; 
  case FLOAT64_TAG: return "real"; 
  case SYMBOL_TAG: return "symbol"; 
  case STRING_TAG: return "text"; 
  default: return "UNKNOWN"; 
 }
}

char     value_as_string[255];

char *
foreign_value_to_string(gsi_param)
obj_value_type     *gsi_param;
{
 switch (gsi_param->p_type)
  {
   case INTEGER_TAG: 
        sprintf(value_as_string, "%d", (int) ((gsi_param->p_value).integer_p));
        return value_as_string;
   case FLOAT64_TAG:
        sprintf(value_as_string, "%f", (gsi_param->p_value).float_p); 
        return value_as_string;
   case SYMBOL_TAG: 
        return (gsi_param->p_value).symbol_p;
   case STRING_TAG: 
        sprintf(value_as_string, "\"%s\"", (gsi_param->p_value).string_p);
        return value_as_string;
   default: return "UNKNOWN"; break;
  }
}

int printf_foreign_entry(foreign_entry)
FOREIGN_FUNCTION_ENTRY     *foreign_entry;
{
 ffe_int     j;
 ffe_int     argcount = foreign_entry->argcount;

 printf("  %s(", foreign_entry->name);

 for (j = 0; j < argcount; j++)
  {
   printf("%s", 
   foreign_typetag_to_string(foreign_entry->typelist[j]));
   if (j != argcount -1)
      printf(", "); 
  }

 printf(") = %s\n", 
	foreign_typetag_to_string(foreign_entry->return_type));
 return 0;
}
#endif /* FFS_DEBUG_VERBOSE */
