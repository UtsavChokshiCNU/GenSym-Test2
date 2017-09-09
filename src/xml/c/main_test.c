/* -*- Mode: C -*-
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Filename:      main_test.c
 +
 + Gensym module: xml/c
 +
 + File Summmary: Test main() function for liblsxml
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +               2002 - ...    jv
 +
 + Description:  This file contains a main function to verify liblsxml
 +               
 + Key:          (obsolete)
 +
 + File Organization:
 +   Section:      INCLUDE FILES 
 +   Section:      DEFINES
 +   Section:      GLOBALS
 +   Section:      FUNCTION GROUP - XML main() function
 +
 +      
 + External Interface:
 +
 +
 + Dependencies:
 +      Requires the libxml2 library and depends on lispxml.c
 +
 + Notes:
 +
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      INCLUDE FILES
 %
 % Description:  All required include files are referenced here.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include "xml_support.h"


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      DEFINES
 %
 % Description:  Module specific macros defined in this section. 
 %
 % Notes:
 %
 % Modifications:
 %   jv, 12/13/02, add SUCCESS and FAILURE from cstreams.c functionality.
 %     If these values are really to mean something, maybe they should be
 %     moved to cprim.h or something.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#define SUCCESS  0L
#define FAILURE -1L


#define XML_STRING_BUFFER_SIZE     128


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      GLOBALS
 %
 % Description:  Module specific typedefs, variables, & externs defined here
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


extern long g2xml_get_event_callback_type(G2pointer);
extern long g2xml_events_ready(G2pointer);
extern G2pointer g2xml_get_event_callback_data(G2pointer);
extern long g2xml_element_name_size(G2pointer);
extern long g2xml_start_element_atts_num(G2pointer);
extern long g2xml_start_element_att_size(G2pointer, long);
extern long g2xml_fill_element_name_buffer(G2pointer, char *, long, long);
extern long g2xml_fill_start_element_att_buffer(G2pointer, char *, long, long);
extern long g2xml_characters_or_comment_size(G2pointer);
extern long g2xml_fill_characters_or_comment_buffer(G2pointer, char *, long, long);
extern long g2xml_error_size(G2pointer);
extern long g2xml_fill_error_buffer(G2pointer, char *, long);

extern void g2xml_init_sax();

extern G2pointer g2xml_make_parser_context();
extern long g2xml_parse_chunk(G2pointer, char *, long, long);
extern G2pointer g2xml_first_sax_event(G2pointer);
extern G2pointer g2xml_next_sax_event(G2pointer);

extern void g2xml_cleanup_parser(G2pointer);


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - G2pointer Stubs
 %
 % Description:
 %   To test liblsxml, we don't really want to bother linking in libcprim
 %   and going through all the real pointer caching and decaching.  These
 %   stubs allow us to use pointers directly while maintaining the same
 %   code as we would use if we were being called from Lisp.
 %   
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/***************************************************************************\
*  
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
void g2ext_initialize_g2pointers ()
{
}

void g2ext_decache_g2pointer (G2pointer g2ptr)
{
}

G2pointer g2ext_cache_cpointer (Cpointer cptr)
{
  return (G2pointer) cptr;
}

Cpointer g2ext_map_g2pointer_to_cpointer (G2pointer g2ptr)
{
  return (Cpointer) g2ptr;
}

/***************************************************************************\
*  long g2ext_cpointer_of_g2pointer_is_null (G2pointer)
*
*  PURPOSE: 
*    Performs a NULL check on the C pointer corresponding to the given G2pointer
*
*  COMMENTS:
*    I like my version better, because it's a lot more explicit than the one
*    in g2ptrs.c, but I'm sure they'll work the same.
*  
****************************************************************************/
long cprim_cpointer_of_g2pointer_is_null (G2pointer g2pointer)
{
  Cpointer corresponding;
  long rval;

  corresponding = g2ext_map_g2pointer_to_cpointer(g2pointer);
  rval = (corresponding == (Cpointer) NULL);
  if (rval) {
    fprintf(stderr, "found null pointer (%ld is 0x%x)\n",
            (long) g2pointer, (unsigned int) corresponding);
  } else {
    fprintf(stderr, "valid pointer (%ld is 0x%x)\n",
            (long) g2pointer, (unsigned int) corresponding);
  }
  fflush(stderr);
  return rval;
}

long g2ext_cpointer_of_g2pointer_is_null (G2pointer pointer_index)
{
  if (g2ext_map_g2pointer_to_cpointer(pointer_index) == (Cpointer) NULL) {
    return 1L;
  } else {
    return 0L;
  }
}

/*****************************************************************************
 * long g2ext_g2_stream_open (pathname_string, open_mode)
 *
 *   Description:
 *     Opens a file in the specified mode.
 *   Input Arguments:
 *     pathname_string:  A vaild file pathname
 *     open_mode:        0 - Read, 1 - Write, 2 - Append, 3 - Read/Write
 *   Returns: 
 *     return value: (long) valid stream pointer or FAILURE
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_g2_stream_open (char *pathname_string, long open_mode)
{
  FILE        *stream;
  char  *fopen_mode = 0;

  switch (open_mode) {
  case 0: fopen_mode = "r"; break;
  case 1: fopen_mode = "w"; break;
  case 2: fopen_mode = "a"; break;
  case 3: fopen_mode = "r+"; break;
#if defined(WIN32) || defined(__WATCOMC__)
  case 4: fopen_mode = "rb"; break;
  case 5: fopen_mode = "wb"; break;
  case 6: fopen_mode = "ab"; break;
  case 7: fopen_mode = "r+b"; break;
#else
  case 4: fopen_mode = "r"; break;
  case 5: fopen_mode = "w"; break;
  case 6: fopen_mode = "a"; break;
  case 7: fopen_mode = "r+"; break;
#endif
  }

  stream = fopen(pathname_string, fopen_mode);
  if (stream == NULL) {
    return(FAILURE);
  }
  return(g2ext_cache_cpointer((long) stream));
}


/*****************************************************************************
 * long g2ext_g2_stream_read_string (stream_index, string,
 *                             number_of_characters, start_index)
 *
 *   Description:
 *     Read chars from stream into buffer.
 *   Input Arguments:
 *     stream_index:         A valid stream pointer
 *     string:               Buffer to read into
 *     number_of_characters: Number of chars to read from stream
 *     start_index:          Index in string buffer to place characters
 *   Returns: 
 *     string:        If success, will place number_of_characters at buffer
 *                     location start_index.
 *     return value: (long) number of characters read, 0 on EOF or error.
 *   Notes:
 *     Assumes that EOF is not a readable character.
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_g2_stream_read_string (long stream_index, char *string,
                                  long number_of_characters, long start_index)
{
  FILE *stream;

  stream = (FILE *)g2ext_map_g2pointer_to_cpointer(stream_index);

  return((long)(fread(&string[start_index], 1, number_of_characters, stream)));
}


/*****************************************************************************
 * long g2ext_str_close (stream_index)
 *
 *   Description:
 *     Close a specified stream.
 *   Input Arguments:
 *     stream_index:  A valid stream pointer
 *   Returns: 
 *     return value: (long) 0 on success, EOF if any error was detected
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/
long g2ext_str_close (long stream_index)
{
  FILE *stream = (FILE *) g2ext_map_g2pointer_to_cpointer(stream_index);

  g2ext_decache_g2pointer(stream_index);
  return fclose(stream);
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - XML Testing
 %
 % Description:
 %   Contains a main function to produce an executable to test liblsxml
 %   
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/***************************************************************************\
*  void parse_test_do_start_document ()
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
static void parse_test_do_start_document ()
{
  fprintf(stdout, "\n    START_DOCUMENT\n");
}


/***************************************************************************\
*  void parse_test_do_end_document ()
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
static void parse_test_do_end_document ()
{
  fprintf(stdout, "\n    END_DOCUMENT\n");
}


/***************************************************************************\
*  void parse_test_do_start_element (G2pointer)
*
*  PURPOSE: 
*
*  COMMENTS:
*    Note A: we do not do (len * sizeof()), because Lisp cannot really do that.
*      We pass in the size of the buffer in bytes, not in chars or xmlChars.
*      We very much hope and believe that bytes, chars, and xmlChars will be
*      the same size; if they're not, we'll need to do more work.  But if
*      they're not, and until we do that more work, it's far better to get
*      truncated strings than memory corruption.
*  
****************************************************************************/
static void parse_test_do_start_element (G2pointer callback_index)
{
  int j, atts_num;
  long string_length;
  char *element_buffer = NULL;

  fprintf(stdout, "\n    START_ELEMENT\n");
  fprintf(stdout, "      Name: ");
  string_length = g2xml_element_name_size(callback_index);
  if (string_length == 0) {
    fprintf(stdout, "<NULL> ");
  } else {
    element_buffer = (char *) malloc(string_length);  /* Note A */
    g2xml_fill_element_name_buffer(callback_index, element_buffer,
                                   string_length, 0L);
    fprintf(stdout, "%s ", element_buffer);
    free(element_buffer);
    element_buffer = NULL;
  }
  atts_num = g2xml_start_element_atts_num(callback_index);
  for (j = 0; j < atts_num; j++) {
    string_length = g2xml_start_element_att_size(callback_index, j);
    element_buffer = (char *) malloc(string_length);  /* Note A */
    g2xml_fill_start_element_att_buffer(callback_index, element_buffer,
                                        string_length, j);
    fprintf(stdout, "\n      Att: %s='", element_buffer);
    free(element_buffer);
    element_buffer = NULL;
    j++;
    if (j < atts_num) {
      string_length = g2xml_start_element_att_size(callback_index, j);
      element_buffer = (char *) malloc(string_length);  /* Note A */
      g2xml_fill_start_element_att_buffer(callback_index, element_buffer,
                                          string_length, j);
      fprintf(stdout, "%s' (len = %d)", element_buffer, string_length);
      free(element_buffer);
      element_buffer = NULL;
    }
  }
  fprintf(stdout, "\n");
}


/***************************************************************************\
*  void parse_test_do_end_element (G2pointer)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
static void parse_test_do_end_element (G2pointer callback_index)
{
  long string_length;
  char *element_buffer = NULL;

  fprintf(stdout, "\n    END_ELEMENT\n");
  fprintf(stdout, "      Name: ");
  string_length = g2xml_element_name_size(callback_index);
  if (string_length == 0) {
    fprintf(stdout, "<NULL> ");
  } else {
    element_buffer = (char *) malloc(string_length);  /* Note A */
    g2xml_fill_element_name_buffer(callback_index, element_buffer,
                                       string_length, 0L);
    fprintf(stdout, "%s ", element_buffer);
    free(element_buffer);
  }
  fprintf(stdout, "\n");
}


/***************************************************************************\
*  void parse_test_do_characters (G2pointer)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
static void parse_test_do_characters (G2pointer callback_index)
{
  long string_length;
  char *element_buffer = NULL;

  fprintf(stdout, "\n    CHARACTERS\n");
  string_length = g2xml_characters_or_comment_size(callback_index);
  if (string_length == 0) {
    fprintf(stdout, "      ch: <NULL>\n      len: %d", (int) string_length);
  } else {
    element_buffer = (char *) malloc(string_length);  /* Note A */
    g2xml_fill_characters_or_comment_buffer(callback_index, element_buffer,
                                            string_length, 0L);
    fprintf(stdout, "      ch: \"%s\"\n      len: %d",
            element_buffer, (int) string_length);
    free(element_buffer);
  }
  fprintf(stdout, "\n");
}


/***************************************************************************\
*  void parse_test_do_comment (G2pointer)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
static void parse_test_do_comment (G2pointer callback_index)
{
  long string_length;
  char *element_buffer = NULL;

  fprintf(stdout, "\n    COMMENT\n");
  string_length = g2xml_characters_or_comment_size(callback_index);
  if (string_length == 0) {
    fprintf(stdout, "      ch: <NULL>\n      len: %d", (int) string_length);
  } else {
    element_buffer = (char *) malloc(string_length);  /* Note A */
    g2xml_fill_characters_or_comment_buffer(callback_index, element_buffer,
                                            string_length, 0L);
    fprintf(stdout, "      ch: \"%s\"\n      len: %d",
            element_buffer, (int) string_length);
    free(element_buffer);
  }
  fprintf(stdout, "\n");
}

/***************************************************************************\
*  void parse_test_do_error (G2pointer)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
static void parse_test_do_error (G2pointer callback_index)
{
  long string_length;
  char *element_buffer = NULL;

  fprintf(stdout, "\n    ERROR\n");
  string_length = g2xml_error_size(callback_index);
  if (string_length == 0) {
    fprintf(stdout, "      msg: <NULL>\n      len: %d", (int) string_length);
  } else {
    element_buffer = (char *) malloc(string_length);  /* Note A */
    g2xml_fill_error_buffer(callback_index, element_buffer, string_length);
    fprintf(stdout, "      msg: \"%s\"\n      len: %d (%d)",
            element_buffer, (int) string_length, strlen(element_buffer));
    free(element_buffer);
  }
  fprintf(stdout, "\n");
}


/**
 * setDocumentLocatorDebug:
 * @ctxt:  An XML parser context
 * @loc: A SAX Locator
 *
 * Receive the document locator at startup, actually xmlDefaultSAXLocator
 * Everything is available on the context, so this is useless in our case.
 */
static void
setDocumentLocatorDebug(void *ctx ATTRIBUTE_UNUSED, xmlSAXLocatorPtr loc ATTRIBUTE_UNUSED)
{
    fprintf(stdout, "SAX.setDocumentLocator()\n");
}

/**
 * startDocumentDebug:
 * @ctxt:  An XML parser context
 *
 * called when the document start being processed.
 */
static void
startDocumentDebug(void *ctx ATTRIBUTE_UNUSED)
{
    fprintf(stdout, "SAX.startDocument()\n");
}

/**
 * endDocumentDebug:
 * @ctxt:  An XML parser context
 *
 * called when the document end has been detected.
 */
static void
endDocumentDebug(void *ctx ATTRIBUTE_UNUSED)
{
    fprintf(stdout, "SAX.endDocument()\n");
}

/**
 * startElementDebug:
 * @ctxt:  An XML parser context
 * @name:  The element name
 *
 * called when an opening tag has been processed.
 */
static void
startElementDebug(void *ctx ATTRIBUTE_UNUSED, const xmlChar *name, const xmlChar **atts)
{
    int i;

    fprintf(stdout, "SAX.startElement(%s", (char *) name);
    if (atts != NULL) {
        for (i = 0;(atts[i] != NULL);i++) {
            fprintf(stdout, ", %s='", atts[i++]);
            if (atts[i] != NULL)
                fprintf(stdout, "%s'", atts[i]);
        }
    }
    fprintf(stdout, ")\n");
}

/**
 * endElementDebug:
 * @ctxt:  An XML parser context
 * @name:  The element name
 *
 * called when the end of an element has been detected.
 */
static void
endElementDebug(void *ctx ATTRIBUTE_UNUSED, const xmlChar *name)
{
    fprintf(stdout, "SAX.endElement(%s)\n", (char *) name);
}

/**
 * charactersDebug:
 * @ctxt:  An XML parser context
 * @ch:  a xmlChar string
 * @len: the number of xmlChar
 *
 * receiving some chars from the parser.
 * Question: how much at a time ???
 */
static void
charactersDebug(void *ctx ATTRIBUTE_UNUSED, const xmlChar *ch, int len)
{
    char output[40];
    int i;

    for (i = 0;(i<len) && (i < 30);i++)
        output[i] = ch[i];
    output[i] = 0;

    fprintf(stdout, "SAX.characters(%s, %d)\n", output, len);
}

/**
 * commentDebug:
 * @ctxt:  An XML parser context
 * @value:  the comment content
 *
 * A comment has been parsed.
 */
static void
commentDebug(void *ctx ATTRIBUTE_UNUSED, const xmlChar *value)
{
    fprintf(stdout, "SAX.comment(%s)\n", value);
}

xmlSAXHandler debugSAXHandlerStruct = {
  NULL, /* internalSubset */
  NULL, /* isStandalone */
  NULL, /* hasInternalSubset */
  NULL, /* hasExternalSubset */
  NULL, /* resolveEntity */
  NULL, /* getEntity */
  NULL, /* entityDecl */
  NULL, /* notationDecl */
  NULL, /* attributeDecl */
  NULL, /* elementDecl */
  NULL, /* unparsedEntityDecl */
  setDocumentLocatorDebug,
  startDocumentDebug,
  endDocumentDebug,
  startElementDebug,
  endElementDebug,
  NULL, /* reference */
  charactersDebug,
  NULL, /* ignorableWhitespace */
  NULL, /* processingInstruction */
  commentDebug,
  NULL, /* xmlParserWarning */
  NULL, /* xmlParserError */
  NULL, /* xmlParserError */
  NULL, /* getParameterEntity */
  NULL, /* cdataBlock; */
  NULL,  /* externalSubset; */
  1
};

xmlSAXHandlerPtr debugSAXHandler = &debugSAXHandlerStruct;


/***************************************************************************\
*  long c_sax_parse_file_1 (G2pointer)
*
*  PURPOSE: 
*
*  COMMENTS:
*    Maybe implement fake Lisp calls here to test.
*  
****************************************************************************/
static long c_sax_parse_file_1 (G2pointer file_index)
{
  char buff[XML_STRING_BUFFER_SIZE];
  long nchars;
  G2pointer context_index, event_index, callback_index, temp_index;
  long callback_type, number_of_chunks = 0;

  nchars = g2ext_g2_stream_read_string(file_index, buff,
                                       XML_STRING_BUFFER_SIZE, 0);
  if (nchars > 0) {
    context_index = g2xml_make_parser_context();
    while (nchars > 0) {
      /* fprintf(stderr, "currently %d events ready\n", (int) g2xml_events_ready(context_index)); */
      g2xml_parse_chunk(context_index, buff, nchars, 0);
      number_of_chunks++;
      nchars = g2ext_g2_stream_read_string(file_index, buff,
					   XML_STRING_BUFFER_SIZE, 0);
    }
    g2xml_parse_chunk(context_index, buff, 0, 1);  /* to finish */
    number_of_chunks++;

    fprintf(stdout, "QUEUE:\n   ParserContext\n");
    fflush(stdout);
    event_index = g2xml_first_sax_event(context_index);
    while (!g2ext_cpointer_of_g2pointer_is_null(event_index)) {
      callback_type = g2xml_get_event_callback_type(event_index);
      callback_index = g2xml_get_event_callback_data(event_index);

      switch (callback_type) {
      case XML_CALLBACK_START_DOCUMENT:
        parse_test_do_start_document();
        break;
      case XML_CALLBACK_END_DOCUMENT:
        parse_test_do_end_document();
        break;
      case XML_CALLBACK_START_ELEMENT:
        parse_test_do_start_element(callback_index);
        break;
      case XML_CALLBACK_END_ELEMENT:
        parse_test_do_end_element(callback_index);
        break;
      case XML_CALLBACK_CHARACTERS:
        parse_test_do_characters(callback_index);
        break;
      case XML_CALLBACK_COMMENT:
        parse_test_do_comment(callback_index);
        break;
      case XML_CALLBACK_ERROR:
	parse_test_do_error(callback_index);
	break;
      default:
        fprintf(stdout, "Unknown callbackType: %d\n", (int) callback_type);
        break;
      }
      g2ext_decache_g2pointer(callback_index);

      temp_index = g2xml_first_sax_event(context_index);
      g2ext_decache_g2pointer(event_index);
      event_index = temp_index;
    }
    g2ext_decache_g2pointer(event_index);
    g2xml_cleanup_parser(context_index);
    g2ext_decache_g2pointer(context_index);
  }
  return(number_of_chunks);
}

/***************************************************************************\
*  long c_sax_parse_file (char *filename)
*
*  PURPOSE: 
*    Opens up the file, makes sure everythings ok, calls the parsing engine,
*    and cleans up the file.
*
*  COMMENTS:
*    
*  
****************************************************************************/
static long c_sax_parse_file (char *filename)
{
  G2pointer file_index;    
  long number_of_chunks = 0;

  if (filename == NULL) {
    fprintf(stderr, "Error: no filename supplied to g2xml_sax_parse_file.\n");
    return(-1);
  }

  /* The 4 is documented to mean open for reading, binary.  I figure we should
   * use binary because the file might be Unicode.  It only actually makes a
   * difference on Windows systems.  -jv, 12/13/02
   */
  file_index = g2ext_g2_stream_open(filename, 4);
  if (file_index == FAILURE) {
    fprintf(stderr, "Unable to open file %s\n", filename);
    return(-3);
  }

  number_of_chunks = c_sax_parse_file_1(file_index);

  g2ext_str_close(file_index);
  return(number_of_chunks);
}

/***************************************************************************\
*  void parseAndPrintFile (char *filename)
*
*  PURPOSE: 
*
*  COMMENTS:
*    
*  
****************************************************************************/
static int parseAndPrintFile (char *filename) 
{
  FILE *f;
  int nchunks = 0;

  /*
   * Debug callback
   */
  f = fopen(filename, "r");
  if (f != NULL) {
    int ret;
    char chars[10];
    xmlParserCtxtPtr ctxt;

    ret = fread(chars, 1, 4, f);
    if (ret > 0) {
      ctxt = xmlCreatePushParserCtxt(debugSAXHandler, NULL,
                                     chars, ret, filename);
      while ((ret = fread(chars, 1, 3, f)) > 0) {
        xmlParseChunk(ctxt, chars, ret, 0);
        nchunks++;
      }
      ret = xmlParseChunk(ctxt, chars, 0, 1);
      xmlFreeParserCtxt(ctxt);
      if (ret != 0) {
        fprintf(stdout,
                "xmlSAXUserParseFile returned error %d\n", ret);
      } else {
        nchunks++;
      }
    }
    fclose(f);
  }
  return(nchunks);
}


/***************************************************************************\
*  int main (int, char **)
*
*  PURPOSE: 
*    Take command line arguments, assume the first one is a filename and ignore
*    any others, and call the SAX engine with the file.
*
*  COMMENTS:
*  
****************************************************************************/

int main (int argc, char **argv)
{
  char *filename;
  int chunks;
  int use_gensym=1;

  g2ext_initialize_g2pointers();
  filename = argv[1];
  if (strcmp(filename, "-gensym") == 0) {
    use_gensym=1;
    filename = argv[2];
  } else if (strcmp(filename, "-testsax") == 0) {
    use_gensym=0;
    filename = argv[2];
  }
  g2xml_init_sax();
  if (use_gensym) {
    fprintf(stderr, "calling c_sax_parse_file with %s\n", filename);
    chunks = c_sax_parse_file(filename);
  } else {
    fprintf(stderr, "calling parseAndPrintFile with %s\n", filename);
    chunks = parseAndPrintFile(filename);
    xmlCleanupParser();
    xmlMemoryDump();
  }
  return(chunks);
}
