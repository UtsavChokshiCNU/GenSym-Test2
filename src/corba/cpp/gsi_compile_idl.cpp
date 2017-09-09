/*
 * gsi_compile_idl.cpp - Description Here.
 */

#include <iostream_ver.h>
#include <stdlib.h> 
#include <string.h>                          
#include <stdio.h>
#include <setjmp.h>

#if defined( WIN32 )
#	include <windows.h>
#	include <windowsx.h>
#endif

#include "code_tokens.h"

#include "gsi_main_cpp.h"
#include "corba_main.h"
#include "utils.h"
#include "gsi_compile_idl.h"

/* Compiler debug mode flag */
extern "C"
{
#include "yacc_supp.h"
}

/*=============================================================
  g2idl_pre_scan_file() ~~~
 =============================================================*/

void g2idl_pre_scan_file( void *proc_data, gsi_item args[], gsi_int count, void *call_index)
{
#define MAX_NUMBER_INCLUDE_FILES    256
#define MAX_INCLUDE_FILE_NAME_LEN   128
#define MAX_STATUS_MSG_LEN          256

  FILE   *fptr = NULL;
  char   *m_file,*t_file;
  char    status_msg[MAX_STATUS_MSG_LEN] = {""};
  char    finclude[MAX_INCLUDE_FILE_NAME_LEN+1];
  char   *include_files[MAX_NUMBER_INCLUDE_FILES];
  char  **search_path;
  long    mod = 0;
  long    status = GSI_TRUE;
  char    line[128];
  gsi_int acount;
  int     n,total_files = 0;

  if (compiler_debug_state) cout << endl << "=== PRE-SCAN-IDL-FILE ===" << endl;

  m_file = gsi_str_of(gsi_item_of_attr_by_name(args[0],FILE_ATTR));
  int flen = strlen(m_file);

  search_path = gsi_str_list_of(args[1]);
  acount = gsi_element_count_of(args[1]);

  // check for file existence
  if (!file_exists(m_file))
  {
    // need to look for file via supplied search path
    t_file = file_exists_in_path(m_file,search_path,acount);

    if (t_file != (char *)NULL) {
      m_file = t_file;
      if (compiler_debug_state) cout << "+++MAIN-FILE: " << m_file << endl;
    }
    else {
      sprintf(status_msg,"ERROR: Could not find IDL file: '%s'",m_file);
      cout << endl << status_msg << endl;
      status = GSI_FALSE;
      goto done_g2idl_pre_scan_file;
    }
  }

  // IT IS ASSUMED THAT THERE IS ONLY 1 MAIN FILE PER RPC CALL
  // ALL OTHER FILES WILL BE INCLUDE FILES FROM THE MAIN FILE

  // main file found now check file size 
  mod = file_attribs(m_file,F_SIZE);
  if (mod <= 0) {
    sprintf(status_msg,"ERROR: IDL file '%s' is invalid or contains no data (size=%d)",m_file,(long)mod);
    cout << endl << status_msg << endl;
    status = GSI_FALSE;
    goto done_g2idl_pre_scan_file;
  }

  // check file modification time against last compile time in G2
  mod = file_attribs(m_file,F_LAST_MODIFIED);
  if ((mod != gsi_flt_of(gsi_item_of_attr_by_name(args[0],FILE_MTIME_ATTR))) || gsi_log_of(args[2])) {
    // read file, scanning for includes, etc.
    fptr = fopen(m_file,"r");
    while (fgets( line, 128, fptr )  != NULL && status == GSI_TRUE)
    {
      if (strlen(line) < 8)
        continue;

      char *x = strstr( line, "#include" );

      if (x == NULL) {
        if (compiler_debug_state) cout << "." << "    " << line << flush;
      }
      else {  // got an include so extract it from "" or <>
        if (compiler_debug_state) cout << "+" << "    " << line << flush;

        n = 0;
        char *ptr = x+8;
        char *tbuf = finclude;
        while (*ptr != 0 && *ptr != '>' && *ptr != '"' && n < MAX_INCLUDE_FILE_NAME_LEN) {
          ptr++;
          if (*ptr == '<' || *ptr == '"') {
            ptr++;
            while (*ptr != 0 && *ptr != '>' && *ptr != '"' && n < MAX_INCLUDE_FILE_NAME_LEN) {
              *tbuf++ = *ptr++;
              n++;
            }
            *tbuf = 0;
          }
        }

        // verify #include file exists

        include_files[total_files] = file_exists_in_path(finclude,search_path,acount);
        if (include_files[total_files] != NULL) {
          if (compiler_debug_state) cout << "+++INCLUDE: " << include_files[total_files] << endl;
        }
        else {
          include_files[total_files] = (char *)malloc(strlen(finclude)+1);
          strcpy(include_files[total_files],finclude);
          sprintf(status_msg,"ERROR: Could not find IDL file: '%s'",finclude);
          cout << endl << status_msg << endl;
          status = GSI_FALSE;
        }
        total_files++; 

      } // else

    } // while
    if (compiler_debug_state) cout << endl;

    if (fptr != (FILE *)NULL)
      fclose(fptr);

  } // mod

done_g2idl_pre_scan_file:

  gsi_item *ret_item = gsi_make_items(5);
  gsi_set_type( ret_item[4], GSI_SEQUENCE_TAG );
  gsi_set_log(ret_item[0],status);
  gsi_set_str(ret_item[1],status_msg);
  gsi_set_str(ret_item[2],m_file);
  gsi_set_flt(ret_item[3],mod);
  
  // allocate an array of items for this sequence
  gsi_item *iseq = gsi_make_items(total_files);
  for (n=0;n<total_files;n++)
    gsi_set_str(iseq[n],include_files[n]);
    
  // set the array of include files into the sequence item 
  gsi_set_elements(ret_item[4],iseq,total_files,GSI_SEQUENCE_TAG);

	gsi_rpc_return_values(ret_item, 5, call_index, current_context);

	deep_reclaim_items(ret_item, 5);

  // reclaim file buffers
  if (m_file != gsi_str_of(gsi_item_of_attr_by_name(args[0],FILE_ATTR)))
    free((char *)m_file);
  for (n=0;n<total_files;n++) {
    if (include_files[n] != (char *)NULL)
      free((char *)include_files[n]);
  }

}



/*
 * g2idl_compile_idl()
 *
 * This is the rpc call to compile a idl file.  
 *
 * Input arguments:
 *    - Text list of input file names
 * Output arguments
 *    - symbol = success or error
 *    - Text message for error or ""
 *    - Array object 
 */
void g2idl_compile_idl(void *proc_data, gsi_item args[], gsi_int count, void *call_index )     
{

	if (count != 1 || gsi_type_of(args[0]) != GSI_STRING_LIST_TAG) {
		cout << "Error: Invalid arguments to g2idl_compile_idl_rpc" << endl;
	}

	gsi_item *ret_itm = gsi_make_items(3);
	main_control(args[0], ret_itm);
	gsi_rpc_return_values(ret_itm, 3, call_index, current_context);
	deep_reclaim_items(ret_itm, 3);

}


//
// This is the error handling routine.
// It will save the diagnostic info and return it to the caller
//

jmp_buf error_marker;
G2String error_message;

void dispatch_error(char *filename, int line_number, char *mesg)

{
	char buf[1024];

	sprintf(buf, "%s(%d): %s\n", filename, line_number, mesg);
	cout << "ERROR: " << buf << endl;
	error_message = buf;
	longjmp(error_marker, 1);
}

 
