/* *************************************************************
   
   File : foreign_to_rpc.c
	  foreign_overlay.c
          overlay.c

          Recall that the old foreign function mechanism allows the user to link
          with G2 dynamically, and the new way calls across ICP to a separate
          process, contsining statically linked foreign functions.  Even though
          the old way is more convenient to the user, the new way is much more
          robust, as G2 no longer runs the risk of crashing when it links with
          possibly faulty user code.

          To make the statically linked image, the user links existing foreign
          object files with a Gensym-supplied object file, foreign.o, and an
          overlay file which depends on the particular foreign functions to be
          called.  To make things as painless as possble, we need automatic way of
          generating an overlay file for the foreign function images which the
          user makes.

	  For the record, RFC is an abbreviation for "remote function call".

jh, 5/29/91.  Adapted from foreign_to_rpc.  
*******************************************************************/






/* 
 * first argument is a file name specifying the forign code to convert.
 * each line of the file is of the form
 *   <return-type> <c-function-name> <g2-function-name> <arg-type> <arg-type> ...
 * each <type> must be one of the following foreign types (taken from G2 nomenclature):
 *  integer
 *  real
 *  symbol
 *  text
 * they map to gsi integer, float64, symbol, and string types, respectively.
 */

 /* all names should be case-insensitive. (they aren't in foreign_to_rpc). */


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "cprim.h"

#define OVERLAY_FACILITY_NAME   "foreign_overlay"

#define MAX_SPEC_LINE     1000
#define MAX_TYPE           100
#define MAX_FUNCTION_NAME  200
#define MAX_RFC_ARGS       100
#define MAX_RFC_SPECS     1000

#define INTEGER 0
#define REAL    1
#define SYMBOL  2
#define TEXT    3
#define UNKNOWN_TYPE 4

#define INTEGER_TAG "integer"
#define REAL_TAG    "real"
#define REAL_TAG2   "float"
#define SYMBOL_TAG  "symbol"
#define TEXT_TAG    "text"

#define GSI_INTEGER_TAG "INTEGER_TAG"
#define GSI_REAL_TAG    "FLOAT64_TAG"
#define GSI_SYMBOL_TAG  "SYMBOL_TAG"
#define GSI_TEXT_TAG    "STRING_TAG"


#define INTEGER_DECLARATION "int            "
#define REAL_DECLARATION    "double         "
#define SYMBOL_DECLARATION  "char          *"
#define TEXT_DECLARATION    "char          *"


#define INTEGER_GSI_MACRO "G2_INTEGER_TO_FOREIGN"
#define REAL_GSI_MACRO    "G2_REAL_TO_FOREIGN"
#define SYMBOL_GSI_MACRO  "G2_SYMBOL_TO_FOREIGN"
#define TEXT_GSI_MACRO    "G2_TEXT_TO_FOREIGN"

#define INTEGER_G2_MACRO "FOREIGN_TO_G2_INTEGER"
#define REAL_G2_MACRO    "FOREIGN_TO_G2_REAL"
#define SYMBOL_G2_MACRO  "FOREIGN_TO_G2_SYMBOL"
#define TEXT_G2_MACRO    "FOREIGN_TO_G2_TEXT"

#ifdef FILE_NAME
static char file_name[80] = {"foreign_overlay.c v1.0"};
#endif

struct rfc_spec
 {
  char foreign_name[MAX_FUNCTION_NAME];
  char g2_name[MAX_FUNCTION_NAME];
  int  return_type;
  int  number_of_args;
  int  arg_types[MAX_RFC_ARGS];
 };

struct rfc_spec      rfc_specs[MAX_RFC_SPECS];
int                  spec_count = 0;

char     spec_buffer[MAX_SPEC_LINE];

int
get_rfc_type_from_tag(type_tag)
char     *type_tag;
{
 if (!strcmp(type_tag, INTEGER_TAG))
    return INTEGER;
   else 
   if (!strcmp(type_tag, REAL_TAG) || !strcmp(type_tag, REAL_TAG2))
      return REAL;
   else 
   if (!strcmp(type_tag, SYMBOL_TAG))
      return SYMBOL;
   else 
   if (!strcmp(type_tag, TEXT_TAG))
      return TEXT;
   else
   return UNKNOWN_TYPE;
}


char *
get_gsi_type_from_tag(type_tag)
int     type_tag;
{
  switch (type_tag)
   {
    case INTEGER: return GSI_INTEGER_TAG;
    case REAL:    return GSI_REAL_TAG;
    case SYMBOL:  return GSI_SYMBOL_TAG;
    case TEXT:    return GSI_TEXT_TAG;
    default:      return NULL;
   }
}


char *
get_gsi_macro_from_rfc_type(type_tag)
int     type_tag;
 {
  switch (type_tag)
   {
    case INTEGER: return INTEGER_GSI_MACRO;
    case REAL:    return REAL_GSI_MACRO;
    case SYMBOL:  return SYMBOL_GSI_MACRO;
    case TEXT:    return TEXT_GSI_MACRO;
    default:      return NULL;
   }
 }


char *
get_g2_macro_from_rfc_type(type_tag)
int     type_tag;
 {
  switch (type_tag)
   {
    case INTEGER: return INTEGER_G2_MACRO;
    case REAL:    return REAL_G2_MACRO;
    case SYMBOL:  return SYMBOL_G2_MACRO;
    case TEXT:    return TEXT_G2_MACRO;
    default:      return NULL;
   }
 }




char *
get_declaration_from_rfc_type(type_tag)
int     type_tag;
 {
  switch (type_tag)
   {
    case INTEGER: return INTEGER_DECLARATION;
    case REAL:    return REAL_DECLARATION;
    case SYMBOL:  return SYMBOL_DECLARATION;
    case TEXT:    return TEXT_DECLARATION;
    default:      return NULL;
   }
 }





int
parse_specs_file(specs_file_name)
char     *specs_file_name;
{
 FILE   *specs_file;
 char   *fgets_result; 
 char   *spec_line;
 char    return_type[MAX_TYPE];
 char    arg_type[MAX_TYPE];
 char    foreign_name[MAX_FUNCTION_NAME];
 char    g2_name[MAX_FUNCTION_NAME];
 int     sscanf_result, rfc_type, arg_index;

 specs_file = fopen(specs_file_name, "r");

 if (specs_file == NULL)
  {
   printf("couldn't open specs file\n");
   return 0;
  }

#define CLOSE_AND_FAIL() \
  fclose(specs_file); \
  return 0

 while (!feof(specs_file))
  {
   spec_line = spec_buffer;

   fgets_result = fgets(spec_line, MAX_SPEC_LINE, specs_file);
   if (fgets_result == NULL)
     break; 

   while(*spec_line == ' ') spec_line++;

   sscanf_result = sscanf(spec_line, "%s", return_type);
   if (sscanf_result < 1)
      break;

   rfc_type = get_rfc_type_from_tag(return_type);
   if (rfc_type == UNKNOWN_TYPE)
    {
     printf("unknown return type %s\n", return_type);
     CLOSE_AND_FAIL();
    }

   rfc_specs[spec_count].return_type = rfc_type;

   while(*spec_line != ' ') spec_line++;
   while(*spec_line == ' ') spec_line++;

   sscanf_result = sscanf(spec_line, "%s", foreign_name);
   if (sscanf_result < 1)
    {
     printf("incomplete spec: no foreign function name found on line %d\n", spec_count);     
     CLOSE_AND_FAIL();
    }
   strcpy(rfc_specs[spec_count].foreign_name, foreign_name);

   while(*spec_line != ' ') spec_line++;
   while(*spec_line == ' ') spec_line++;

   sscanf_result = sscanf(spec_line, "%s", g2_name);
   if (sscanf_result < 1)
    {
     printf("incomplete spec: no G2 function name found on line %d\n", spec_count);     
     CLOSE_AND_FAIL();
    }
   strcpy(rfc_specs[spec_count].g2_name, g2_name);
   
   while(*spec_line != ' ' && *spec_line != '\n') spec_line++;
   while(*spec_line == ' ') spec_line++;

   arg_index = 0;

   while (1)
    {
     while(*spec_line == ' ') spec_line++;

     if (*spec_line == '\n' || spec_line == '\0')
        break;

     sscanf_result = sscanf(spec_line, "%s", arg_type);

     rfc_type = get_rfc_type_from_tag(arg_type);
     if (rfc_type == UNKNOWN_TYPE)
      {
       printf("unknown arg#%d type \"%s\"\n", arg_index, arg_type);
       CLOSE_AND_FAIL();
      }

     rfc_specs[spec_count].arg_types[arg_index] = rfc_type;

     arg_index++;

     while(*spec_line != ' ' && *spec_line != '\0') 
          spec_line++;
     if (*spec_line == '\0')
        break;
    }

   rfc_specs[spec_count].number_of_args = arg_index;
   spec_count++;
  }
#undef CLOSE_AND_FAIL
 fclose(specs_file);
 return 1;
}






int
emit_overlay_header(output_file, facility_name, template_filename, output_filename)
FILE     *output_file;
char     *facility_name;
char     *template_filename, *output_filename;
{
 long    now;

 fprintf(output_file, "/*\n");

 fprintf(output_file, " * G2 Foreign Function Overlay\n *\n");

 fprintf(output_file, " * this file: \"%s\"\n * (template file: \"%s\")\n *\n", 
                     output_filename, template_filename);

 now = time(NULL);
 fprintf(output_file, " * Automatically generated on %s", ctime(&now)); 
 /* ctime output includes \n */

 fprintf(output_file, " * by the command \"%s %s %s\".\n *\n", 
                    facility_name, template_filename, output_filename);

 fprintf(output_file, " */\n\n");

 return 1;
}



int
emit_includes(output_file)
FILE     *output_file;
{
 fprintf(output_file, "#include <string.h>\n");
/* fprintf(output_file, "#include \"gsi_icp.h\"\n"); */
 fprintf(output_file, "#include \"foreign.h\"\n");

 fprintf(output_file, "\n");

 return 1;
}



int
emit_defines(output_file)
FILE     *output_file;
{
 fprintf(output_file, "#define CATCH_FFS_SIGNALS 1\n");
 fprintf(output_file, "#define FFS_CHECKING_ON 1\n");

 fprintf(output_file, "\n");

 fprintf(output_file, "#ifndef NULL\n#define NULL 0\n#endif\n");

 fprintf(output_file, "\n");

 return 1;
}




int insert_section_comment(output_file, comment)
FILE     *output_file;
char     *comment;
{
 int     i, star_count;

 star_count = 4 + strlen(comment);

 fprintf(output_file, "\n\n\n\n");

 fprintf(output_file, "/");
 for(i = 0; i < star_count; i++)
    fprintf(output_file, "*");
 fprintf(output_file, "\n");

 fprintf(output_file, " * %s *\n ", comment);

 for(i = 0; i < star_count; i++)
    fprintf(output_file, "*");
 fprintf(output_file, "/\n\n");
 return 0;
}


int
emit_original_template_file(output_file, template_filename)
FILE     *output_file;
char     *template_filename;
{
 FILE   *specs_file;
 char   *fgets_result; 
 char   *spec_line;

 insert_section_comment(output_file, "original template file");

 specs_file = fopen(template_filename, "r");

 if (specs_file == NULL)
  {
   printf("Couldn't open template file\n");
   return 0;
  }

 fprintf(output_file, "/*\n");

 while (!feof(specs_file))
  {
   spec_line = spec_buffer;

   fgets_result = fgets(spec_line, MAX_SPEC_LINE, specs_file);

   if (fgets_result == NULL)
     break; 

   fprintf(output_file, "%s", spec_line);
  }

 fprintf(output_file, " */\n\n");

 fclose(specs_file);
 return 1;
}





int
emit_foreign_externs(output_file)
FILE     *output_file;
{
 int     spec_index;

 /* emit helpful comments */
 insert_section_comment(output_file, "externs for actual foreign functions");

 /* forward declarations for foreign code */
 for (spec_index = 0; spec_index < spec_count; spec_index++)
     fprintf(output_file, 
             "extern %s%s();\n",
             get_declaration_from_rfc_type(rfc_specs[spec_index].return_type),
             rfc_specs[spec_index].foreign_name);
 return 1;
}





int
emit_overlay_code(output_file)
FILE     *output_file;
{
 int     arg_index, spec_index;

 insert_section_comment(output_file, "overlay functions to call actual foreign functions");

 /* emit global return buffer */
 fprintf(output_file, "TEMP_PARAM     global_return_value;\n\n");

 /* for each function */
 for (spec_index = 0; spec_index < spec_count; spec_index++)
  {
   /* emit the function header */
   fprintf(output_file, "TEMP_PARAM *\n"); 
   fprintf(output_file, 
           "%s_overlay(arg_list, count)\n", 
           rfc_specs[spec_index].foreign_name);
   fprintf(output_file, "TEMP_PARAM        *arg_list;\n");
   fprintf(output_file, "int                count;\n");
   fprintf(output_file, "{\n");

   /* declare temps to hold RFC arguments */
   for (arg_index = 0; arg_index < rfc_specs[spec_index].number_of_args; arg_index++)
    {
     fprintf(output_file, 
             " %sfunction_arg%d;\n",
             get_declaration_from_rfc_type(rfc_specs[spec_index].arg_types[arg_index]),
             arg_index);
    }

   /* declare temp to hold return value from foreign function */
   fprintf(output_file, 
           " %sfunction_return;\n\n",
           get_declaration_from_rfc_type(rfc_specs[spec_index].return_type));

   /* code to set up RFC arguments */
   for (arg_index = 0; arg_index < rfc_specs[spec_index].number_of_args; arg_index++)
    {
     fprintf(output_file, 
             " function_arg%d = %s(arg_list[%d]);\n",
             arg_index,
             get_gsi_macro_from_rfc_type(rfc_specs[spec_index].arg_types[arg_index]),
             arg_index);
    }

   /* emit code to call foreign function */
   fprintf(output_file, " function_return = %s(",
          rfc_specs[spec_index].foreign_name);

   for (arg_index = 0; arg_index < rfc_specs[spec_index].number_of_args - 1; arg_index++)
    {
     fprintf(output_file, "function_arg%d, ", arg_index);
    }
   if (rfc_specs[spec_index].number_of_args > 0)
      fprintf(output_file, 
              "function_arg%d);\n\n", 
              rfc_specs[spec_index].number_of_args - 1);
   else
      fprintf(output_file, ");\n\n");

   /* emit code to load GSI parameter for RFC return */
   fprintf(output_file, 
           " %s(function_return, global_return_value);\n",
           get_g2_macro_from_rfc_type(rfc_specs[spec_index].return_type));

   /* emit code to return RFC value */
   fprintf(output_file, " return(&global_return_value);\n");

   /* close it up */ 
   fprintf(output_file, "}\n\n");
  }

 return 1;
}


int
emit_type_lists(output_file)
FILE     *output_file;
{
 int     spec_index, arg_index;

 insert_section_comment(output_file, "type tags for foreign functions");

 for (spec_index = 0; spec_index < spec_count; spec_index++)
  {
   if (rfc_specs[spec_index].number_of_args != 0)
    {
     fprintf(output_file, 
             "ffe_int\n%s_typelist[] =\n",
              rfc_specs[spec_index].foreign_name);
     fprintf(output_file, "{\n");

     for (arg_index = 0; 
          arg_index < rfc_specs[spec_index].number_of_args;
          arg_index++)
      {
       fprintf(output_file, 
               " %s",
               get_gsi_type_from_tag(rfc_specs[spec_index].arg_types[arg_index]));

       if (arg_index != rfc_specs[spec_index].number_of_args - 1)
          fprintf(output_file, ",");
       fprintf(output_file, "\n");
      }
     fprintf(output_file, "};\n\n");           
    }
  }

 return 1;
}




int emit_main_function(output_file)
FILE     *output_file;
{
 int      spec_index;

 insert_section_comment(output_file, "main function");

 fprintf(output_file, "main(argc, argv)\n");
 fprintf(output_file, "int     argc;\n");
 fprintf(output_file, "char   *argv[];\n");
 fprintf(output_file, "{\n");

 /* check argv for safety's sake */
 fprintf(output_file, " if (argc < 2)\n");
 fprintf(output_file, "    {\n");
 fprintf(output_file, "     printf(\"missing port number\\n\");\n");
 fprintf(output_file, "     return;\n");
 fprintf(output_file, "    }\n\n");

 /* compatibility with new network layer */
 fprintf(output_file, " ne_initialize_event_handling();\n");
 fprintf(output_file, " flush_point = 0;\n\n");

 for (spec_index = 0; spec_index < spec_count; spec_index++)
  {

   fprintf(output_file, 
           " register_foreign_function(\n");

   fprintf(output_file, "                           \"%s\",\n ",
           rfc_specs[spec_index].g2_name);

   fprintf(output_file, "                          %s_overlay,\n",
           rfc_specs[spec_index].foreign_name);

   fprintf(output_file, "                           %d,\n",
           rfc_specs[spec_index].number_of_args);

   if (rfc_specs[spec_index].number_of_args == 0)
      fprintf(output_file, "                           NULL, \n");
   else
      fprintf(output_file, "                           %s_typelist, \n",
              rfc_specs[spec_index].foreign_name);

   fprintf(output_file, "                           %s\n",
           get_gsi_type_from_tag(rfc_specs[spec_index].return_type));

   fprintf(output_file, "                          );\n");
  }
 fprintf(output_file, "\n");

 fprintf(output_file, "#if CATCH_FFS_SIGNALS\n");
 fprintf(output_file, " catch_signals_in_foreign_calls();\n");
 fprintf(output_file, "#endif\n\n");

 fprintf(output_file, "#if FFS_CHECKING_ON\n");
 fprintf(output_file, " error_check_around_foreign_calls();\n");
 fprintf(output_file, "#endif\n\n");

/*
 * jh, 10/7/94.  Emit code that will set the version control variables to the
 * values defined in foreign.h and icp.h using paf!'s get_version_info()
 * mechanism.  This will prevent customers from building foreign images with old
 * (or otherwise inappropriate) #include files.
 */
 fprintf(output_file, 
         " ffe_include_file_major_version = FFE_INCLUDE_MAJ_VER_NUM;\n");
 fprintf(output_file, 
         " ffe_include_file_minor_version = FFE_INCLUDE_MIN_VER_NUM;\n");
 fprintf(output_file, 
         " icp_include_file_major_version = ICP_INCLUDE_MAJ_VER_NUM;\n");
 fprintf(output_file, 
         " icp_include_file_minor_version = ICP_INCLUDE_MIN_VER_NUM;\n\n");

 fprintf(output_file, " icp_set_option(ICP_USE_OLD_SLEEP);\n\n");

 fprintf(output_file, " wait_for_foreign_calls(argc, argv);\n");
 fprintf(output_file, "}\n\n");

 return 1;
}

int emit_patches(output_file)
FILE     *output_file;
{
 fprintf(output_file, "void g2int_close_fd_callback () { return; }\n");
 fprintf(output_file, "void g2int_open_fd_callback  () { return; }\n");
 fprintf(output_file, "void g2int_writing_fd_callback  () { return; }\n");
 fprintf(output_file, "void g2int_not_writing_fd_callback  () { return; }\n");

 return 1;
}

int main(argc, argv)
int      argc;
char    *argv[];
{
 FILE     *output_file = NULL;
 int       overlay_status = 1;
 int       final_status = 0;

 if (argc < 3)
  {
   printf("usage:\n  foreign_overlay <specs-file> <output-file>\n");
   printf("  each line in specs-file is of the form:\n");
   printf("  <return-type> <foreign-name> <G2-name> <argtype> <argtype> ...\n");
   printf("where <return-type> and <argtype> are one of: integer, float, symbol, text.\n");
   return 0;
  }

 if (!parse_specs_file(argv[1]))
    {
     printf("Problem parsing template file.\n");
     goto finished_processing;
    }

 output_file = fopen (argv[2], "w");
 if (output_file == NULL)
  {
   overlay_status = 0;
   printf("Cannot open output file \"%s\".\n", argv[2]);
   goto finished_processing_no_stream;
  }

 /* 
  * Passing argv[0] to emit_overlay_header would give a more accurate picture of
  * where the overlay file came from, but doing this causes
  * emit_original_template_file to emit garbage (reason unknown) on the Sparcs.
  * So instead we define OVERLAY_FACILITY_NAME.  This must be kept up-to-date with
  * the name under which we actually release this facility.
  *
  * jh, 1/31/92. The above comment is obsolete.  We now pass argv[0] to
  * emit_overlay_header as we should.  The problem was that the EMIT_BLOCK macro
  * happened to do the right thing even though emit_original_template_file took
  * two args, not the one arg that EMIT_BLOCK passed to it.  Passing the extra
  * argv[0] to emit_overlay_header disturbed this precarious balance.
  */
 if (!(overlay_status = emit_overlay_header(output_file, argv[0], argv[1], argv[2])))
    {
     printf("Problem emitting overlay header.\n");
    }

#define INCLUDE_ERROR  -1
#define DEFINE_ERROR   -2
#define TEMPLATE_ERROR -3
#define EXTERN_ERROR   -4
#define OVERLAY_ERROR  -5
#define TYPELIST_ERROR -6
#define MAIN_ERROR     -7
#define PATCH_ERROR    -8

#define EMIT_BLOCK(emit_function, description, error_code) \
 if (!(overlay_status = emit_function(output_file))) \
    { \
     printf("Problem emitting %s.\n", description); \
     final_status = (error_code); \
     goto finished_processing; \
    }

 EMIT_BLOCK(emit_includes, "include directives", INCLUDE_ERROR);

 EMIT_BLOCK(emit_defines, "define directives", DEFINE_ERROR);

 if (!(overlay_status = emit_original_template_file(output_file, argv[1])))
    {
     printf("Problem emitting original template file.\n");
     final_status = TEMPLATE_ERROR;
     goto finished_processing;
    }

 EMIT_BLOCK(emit_foreign_externs, "foreign externs,\n", EXTERN_ERROR);

 EMIT_BLOCK(emit_overlay_code, "overlay code", OVERLAY_ERROR);

 EMIT_BLOCK(emit_type_lists, "type lists", TYPELIST_ERROR);

 EMIT_BLOCK(emit_main_function, "main function", MAIN_ERROR);

 EMIT_BLOCK(emit_patches, "patches", PATCH_ERROR);

 finished_processing:
 if (output_file != NULL)
  fclose(output_file);
 finished_processing_no_stream:

/* AC 1/31/92. This program is executed from inside make. It needs to return 0
 * on UNIX and 1 on VMS to indicate success. Otherwise make will abort.
 */

 return final_status;
}
