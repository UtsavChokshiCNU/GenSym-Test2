/* -*- Mode: C -*-
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Filename:      lispxml.c
 +
 + Gensym module: xml/c
 +
 + File Summmary: Wrapper functions to use libxml2 from Lisp
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +               2002 - ...    jv, dbk, ajs
 +
 + Description:  This file contains the function entry points for a using
 +               the third-party libxml2 library from Lisp (and from G2,
 +               in general).  We do maintain a copy of the sources for
 +               libxml2 (cvs co libxml2), but generally we use it as a
 +               static piece of functionality, no different from libc.
 +               
 + Key:          (obsolete)
 +
 + File Organization:
 +   Section:      INCLUDE FILES 
 +   Section:      DEFINES
 +   Section:      GLOBALS
 +   Section:      FUNCTION GROUP - XML API Functions
 +
 +      
 + External Interface:
 +
 +
 + Dependencies:
 +      Requires the libxml2 library; requires the associated header files,
 +      which presently are checked in to libxml2, but may be checked in here
 +      additionally at some point.
 +
 + Notes:
 +      Many parameters in this file are called context_index.  Because they
 +      are G2pointers, they are completely opaque, and because they are called
 +      "context", they may seem to be xmlParserCtxtPtr's.  In fact, they are
 +      wrappers around such pointers -- they are xmlParserCtxtWrapper's.
 +      Perhaps some variable name changing would be in order at some point.
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
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#define ERROR_WITHIN_AN_ERROR_TEXT "could not obtain error text"

/* vsnprintf, when given too small a buffer, is supposed to return "the number
 * of characters formatted, that is, the number of characters that would have
 * been written to the buffer if it were large enough."  Therefore, one can
 * obtain the required buffer size by calling vsnprintf first with a buffer
 * known to be too small.
 *
 * Platforms that define BROKEN_VSNPRINTF do not support this.  Therefore,
 * on those platforms, just statically allocate a buffer expected to be large
 * enough.  If *anything* goes wrong, we'll just post a default error message.
 * We will not risk going into an infinite loop or allocating a buffer
 * that's 100MB.
 *
 * Actually, it turns out more of our platforms are "broken" than not.
 * vsnprintf only behaves the way I expected on Solaris and Linux.  Oh well.
 */
#if defined(WIN32) || defined(__osf__) || defined(_IBMR2) || defined(__hpux)
#  define BROKEN_VSNPRINTF
#endif

#ifdef BROKEN_VSNPRINTF
#  define SIZE_OF_DUMMY_STRING 1024
#else
#  define SIZE_OF_DUMMY_STRING    1
#endif

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

static int called_xml_init_sax = 0;
static char dummy_format_string[SIZE_OF_DUMMY_STRING];


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - SAX Internal Functions
 %
 % Description:
 %   
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
*  xmlSAXEventDetail *allocAndInitXmlSAXEventDetail ()
*
*  PURPOSE: 
*
*  COMMENTS:
*    Might return NULL if an out of memory error.  Callers need to be prepared
*    to handle that.
*  
****************************************************************************/
static xmlSAXEventDetail *alloc_and_init_xml_sax_event_detail ()
{
  xmlSAXEventDetail *newEvent;

  newEvent = (xmlSAXEventDetail*)malloc(sizeof (xmlSAXEventDetail));
  
  if (newEvent == NULL) {
    fprintf(stderr, "\n  Out of memory in alloc_and_init_xml_sax_event_detail\n");
    return(NULL);
  }

  newEvent->next = NULL;
  return(newEvent);
}


/***************************************************************************\
*  void enqueue_xml_sax_event (xmlSAXEventDetail *, xmlParserCtxtPtr)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
static void enqueue_xml_sax_event (xmlSAXEventDetail *event,
                                   xmlParserCtxtPtr context)
{
  xmlParserCtxtWrapper *qWrapper;

  qWrapper = (xmlParserCtxtWrapper *) (context->_private);
  if (qWrapper->tail == NULL) {
    qWrapper->head = event;
    qWrapper->tail = event;
  } else {
    qWrapper->tail->next = event;
    qWrapper->tail = event;
  }
}


/***************************************************************************\
*  G2pointer *get_event_detail_from_wrapper (G2pointer, short)
*
*  PURPOSE: 
*    This is a helper function and is not part of the external API
*
*  COMMENTS:
*  
****************************************************************************/
static G2pointer get_event_detail_from_wrapper (G2pointer wrapper_index,
                                                short andPop)
{
  xmlParserCtxtWrapper *wrapper;
  xmlSAXEventDetail *event = NULL;

  wrapper = (xmlParserCtxtWrapper *) g2ext_map_g2pointer_to_cpointer(wrapper_index);
  
  if (wrapper != NULL) {
    event = wrapper->head;
    if ((event != NULL) && (andPop != 0)) {
      /* Splice out detail */
      wrapper->head = event->next;
      /* This is now out of the queue, it shouldn't point anywhere. */
      event->next = NULL;
      /* The tail never changes except when the whole queue is empty. */
      if (wrapper->head == NULL) {
        wrapper->tail = NULL;
      }
    }
  }
  return(g2ext_cache_cpointer(event));
}


/***************************************************************************\
*  void dispose_xml_sax_event_detail_atts (xmlChar **)
*
*  PURPOSE: 
*    Utility function to dispose atts
*
*  COMMENTS:
*  
*
****************************************************************************/
static void dispose_xml_sax_event_detail_atts (xmlChar **atts)
{
  xmlChar *att;
  int i = 0;

  if (atts != NULL) {
    for (att = atts[0]; att != NULL; att = atts[++i]) {
      xmlFree(att);
    }
    xmlFree(atts);
  }
}


/***************************************************************************\
*  void dispose_xml_sax_event_detail (xmlSAXEventDetail *)
*
*  PURPOSE: 
*
*  COMMENTS:
*    I really don't think we need the null checks.  I think "xmlFree" does a
*    null check before doing anything.  However, I put quotes around xmlFree
*    because it might be a function or a macro, depending on what symbols are
*    defined, and when it is a macro, it may call various specific free
*    functions, and it's hard to be sure that they all would do the right thing,
*    so better safe than sorry, I guess.
*  
****************************************************************************/
static void dispose_xml_sax_event_detail (xmlSAXEventDetail *event)
{
  switch (event->callbackType) {
  case XML_CALLBACK_START_DOCUMENT:
  case XML_CALLBACK_END_DOCUMENT: {
    break;
  }
  case XML_CALLBACK_START_ELEMENT: {
    if (event->callbackData.element.name != NULL) {
      xmlFree(event->callbackData.element.name);
    }
    dispose_xml_sax_event_detail_atts(event->callbackData.element.atts);
    break;
  }
  case XML_CALLBACK_END_ELEMENT: {
    if (event->callbackData.element.name != NULL) {
      xmlFree(event->callbackData.element.name);
    }
    break;
  }
  case XML_CALLBACK_CHARACTERS:
  case XML_CALLBACK_COMMENT: {
    if (event->callbackData.error.msg != NULL) {
      xmlFree(event->callbackData.characters.ch);
    }
    break;
  }
  case XML_CALLBACK_WARNING:
  case XML_CALLBACK_ERROR:
  case XML_CALLBACK_FATAL_ERROR: {
    if (event->callbackData.error.msg != NULL) {
      free(event->callbackData.error.msg);
    }
    break;
  }
  default: {
#ifdef DEBUG
    fprintf(stderr, "Attempting to dispose event with unknown callbackType: %d\n",
            (int) event->callbackType);
#endif
    break;
  }
  }
  event->next = NULL;                /* to help catch use-after-free bugs */
  free (event);
}


/***************************************************************************\
*  long fill_element_name_buffer_helper (G2pointer, char *, long, long)
*
*  PURPOSE: 
*    Utility function for filling buffers
*
*  COMMENTS:
*    The functions to fill the passed in buffer.  Not dealing with truncation
*    issues (if buffer to be filled wants to get more than a Lisp fixnum amount
*    of data.  How is this dealt with elsewhere?)  NOTE: We are passing a length
*    in even though we can figure the length out.  This way we can't get buffer
*    overflow, but we may truncate some data.  To be dealt with later.  We could
*    have these functions return a value indicating whether they got all the
*    data or if not, how much more there is to get so it can be called again.
*    In fact we probably need to do this so the caller can figure out whether
*    its time to pop the eventDetail off the queue.
*
****************************************************************************/
static long fill_element_name_buffer_helper (xmlChar *source,
                                       char *destination,
                                       long nbytes,
                                       long start)
{
  /* Would maybe like to use xmlStrndup, but it doesn't support filling a given
   * buffer... it wants to always do the malloc for you.  So, peek at its source
   * code and try to emulate it.
   *
   * However, xmlStrndup wants to do len * sizeof(xmlChar), which makes sense,
   * but when we allocate the buffer from Lisp, we can't do a sizeof(xmlChar).
   * Therefore, call our parameter "nbytes", not "len", because that's exactly
   * the number of bytes we need to copy.  Then, the start parameter also needs
   * to be given in absolute bytes; but if we want to do pointer arithmetic with
   * it, we need it to be in xmlChars, not bytes, so need to DIVIDE start by the
   * size of an xmlChar.  If we find problems because somehow char or xmlChar
   * are greater than 1 byte, we'll deal with it when we allocate the buffer and
   * continue to pass the size of the buffer in bytes.  -jv, 12/19/02
   */
  memcpy(destination, (source + (start / sizeof(xmlChar))), nbytes);
  destination[nbytes] = '\0';

  return(nbytes);
}


/***************************************************************************\
*  void gensym_callback_startDocument (void *)
*
*  PURPOSE: 
*
* COMMENTS:
*    The true SAX libxml callbacks begin here.  They all simply enqueue an event
*    for themselves, and copying the data.  For now, each callback calls the
*    internal callback in SAX.c because some of them rely on others being called
*    (in particular, startDocument sets the myDoc pointer in the SAX handler,
*    which the comment callback relys on being there (maybe this is a bug in
*    libXML as the documentation doesn't say anything about which callbacks need
*    to have what set.  They probably are not written as defensively as they
*    could be).  Alternatively, we can simply NULL out all fields we don't need
*    in the SAX Handler rather than relying on the defaults.  This is probably
*    better as it ensures no more work is done than necessary.
****************************************************************************/
static void gensym_callback_startDocument (void *ctxt)
{
  xmlSAXEventDetail *event;

  event = alloc_and_init_xml_sax_event_detail();
  if (event != NULL) {
    event->callbackType = XML_CALLBACK_START_DOCUMENT;
    enqueue_xml_sax_event(event, (xmlParserCtxtPtr)ctxt);
  }
}


/***************************************************************************\
*  void gensym_callback_endDocument (void *)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
static void gensym_callback_endDocument (void *ctxt)
{
  xmlSAXEventDetail *event;

  event = alloc_and_init_xml_sax_event_detail();
  if (event != NULL) {
    event->callbackType = XML_CALLBACK_END_DOCUMENT;
    enqueue_xml_sax_event(event, (xmlParserCtxtPtr)ctxt);
  }
}


/***************************************************************************\
*  void gensym_callback_startElement (void *, const xmlChar *, const xmlChar **)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
static void gensym_callback_startElement (void *ctxt, const xmlChar *name,
                                          const xmlChar **atts)
{
  xmlSAXEventDetail *event;
  int i = 0, n_atts = 0;

  event = alloc_and_init_xml_sax_event_detail();
  if (event != NULL) {
    event->callbackType = XML_CALLBACK_START_ELEMENT;
    event->callbackData.element.name = xmlStrndup(name, xmlStrlen(name));
    /* If we run out of memory, xmlStrndup could return NULL.  Users need to be
     * aware that element.name might be NULL.  -jv, 12/11/02
     */
    if (atts != NULL) {
      /* Get a count of the number of attributes for allocation. */
      while (atts[n_atts] != NULL) {
        n_atts++;
      }
      /* We want to copy the NULL pointer as well, so we need to allocate
       * space for it and then "copy" it.  xmlStrndup and xmlStrlen handle
       * NULL pointers, and return the values that we want.
       */
      n_atts++;
      event->callbackData.element.atts =
        (xmlChar **)xmlMalloc(n_atts * sizeof(xmlChar *));
      for (i=0; i<n_atts; i++) {
        event->callbackData.element.atts[i] =
          xmlStrndup(atts[i], xmlStrlen(atts[i]));
      }
    } else {
      event->callbackData.element.atts = NULL;
    }
    enqueue_xml_sax_event(event, (xmlParserCtxtPtr)ctxt);
  }
}


/***************************************************************************\
*  void gensym_callback_endElement (void *, const xmlChar *)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
static void gensym_callback_endElement (void *ctxt, const xmlChar *name)
{
  xmlSAXEventDetail *event;

  event = alloc_and_init_xml_sax_event_detail();
  if (event != NULL) {
    event->callbackType = XML_CALLBACK_END_ELEMENT;
    event->callbackData.element.name = xmlStrndup(name, xmlStrlen(name));
    enqueue_xml_sax_event(event, (xmlParserCtxtPtr)ctxt);
  }
}


/***************************************************************************\
*  void gensym_callback_characters (void *, const xmlChar *, int)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
static void gensym_callback_characters (void *ctxt, const xmlChar *ch, int len)
{
  xmlSAXEventDetail *event;
  
  event = alloc_and_init_xml_sax_event_detail();
  if (event != NULL) {
    event->callbackType = XML_CALLBACK_CHARACTERS;
    event->callbackData.characters.ch = xmlStrndup(ch, len);
    event->callbackData.characters.len = len;
    enqueue_xml_sax_event(event, (xmlParserCtxtPtr)ctxt);
  }
}


/***************************************************************************\
*  void gensym_callback_comment (void *, const xmlChar *)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
static void gensym_callback_comment (void *ctxt, const xmlChar *ch)
{
  xmlSAXEventDetail *event;
  int len;

  event = alloc_and_init_xml_sax_event_detail();
  if (event != NULL) {
    event->callbackType = XML_CALLBACK_COMMENT;
    len = xmlStrlen(ch);
    /* We'll store the length, because Lisp needs to know it so it can create
     * the string buffer, even though it won't be part of the structure.
     */
    event->callbackData.characters.len = len;
    event->callbackData.characters.ch = xmlStrndup(ch, len);
    enqueue_xml_sax_event(event, (xmlParserCtxtPtr)ctxt);
  }
}



/***************************************************************************\
*  xmlSAXEventDetail *generic_error_function (void *, const char *, va_list)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
* It seems like the value returned is one larger than it needs to be.
* However, I don't want to completely count on that, since I don't find
* it documented.  Therefore, we'll fill in the string, and then set the
* length again by calling strlen on it.  This way we avoid passing extra
* NUL characters into Lisp, which are not handled well.  -jv, 1/15/03
****************************************************************************/
static xmlSAXEventDetail *generic_error_function (void *ctxt,
						  const char *msg,
						  va_list args)
{
  xmlSAXEventDetail *event;
  int nchars;
  char *formatted_string;

  event = alloc_and_init_xml_sax_event_detail();
  if (event == NULL) {
    return NULL;
  }
  nchars = vsnprintf(dummy_format_string, SIZE_OF_DUMMY_STRING - 1, msg, args);
  if (nchars < 0) {
    /* This code is only reached if libxml2 screws up. */
    nchars = (int)strlen(ERROR_WITHIN_AN_ERROR_TEXT);
    /* Add 1 to make room for the terminating NULL character */
    formatted_string = (char *) malloc((1 + nchars) * sizeof(char));
    strncpy(formatted_string, ERROR_WITHIN_AN_ERROR_TEXT, nchars);
  } else {
    /* Add 1 to make room for the terminating NULL character */
    formatted_string = (char *) malloc((1 + nchars) * sizeof(char));
#ifdef BROKEN_VSNPRINTF
    strncpy_s(formatted_string, nchars + 1, dummy_format_string, nchars);
#else
    vsnprintf(formatted_string, nchars + 1, msg, args);
#endif
  }

  formatted_string[nchars] = '\0';
  event->callbackData.error.msg = formatted_string;
  event->callbackData.error.msg_size = (int)strlen(formatted_string);
  return event;
}


/***************************************************************************\
*  void gensym_callback_warning (void *, const char *)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
static void gensym_callback_warning (void *ctxt, const char *msg, ...)
{
  va_list args;
  xmlSAXEventDetail *event;

  va_start(args, msg);
  event = generic_error_function(ctxt, msg, args);
  if (event) {
    event->callbackType = XML_CALLBACK_WARNING;
    enqueue_xml_sax_event(event, (xmlParserCtxtPtr)ctxt);
  }
  va_end(args);
}


/***************************************************************************\
*  void gensym_callback_error (void *, const char *)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
static void gensym_callback_error (void *ctxt, const char *msg, ...)
{
  va_list args;
  xmlSAXEventDetail *event;

  va_start(args, msg);
  event = generic_error_function(ctxt, msg, args);
  if (event) {
    event->callbackType = XML_CALLBACK_ERROR;
    enqueue_xml_sax_event(event, (xmlParserCtxtPtr)ctxt);
  }
  va_end(args);
}


/***************************************************************************\
*  void gensym_callback_fatal_error (void *, const char *)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
static void gensym_callback_fatal_error (void *ctxt, const char *msg, ...)
{
  va_list args;
  xmlSAXEventDetail *event;

  va_start(args, msg);
  event = generic_error_function(ctxt, msg, args);
  if (event) {
    event->callbackType = XML_CALLBACK_FATAL_ERROR;
    enqueue_xml_sax_event(event, (xmlParserCtxtPtr)ctxt);
  }
  va_end(args);
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - SAX API Functions
 %
 % Description:
 %   
 %   
 % Notes:
 %    The following are the layers between G2 and this facility.  They handle
 %    the converting of C pointers to Lisp fixnums.
 %
 %  ISSUES:
 %    When to call xmlInitParser?
 %    When to free the libXML structures (parserContext and SAXHandle)?
 %    When to free eventDetails?  Has to be Lisp's job to let us know it's done.
 %    When to call xmlCleanupParser?
 %  
 %  COMMENTS:
 %    Lisp needs
 %    1) call to see if there is an event for a parserContext yet. DONE
 %    2) call to see how much space is required for each piece associated with
 %       callback DONE
 %    3) call to fill buffer with data
 %    4) Call to free queue DONE
 %    5) Call to free parserContext (call xmlFreeParserCtxt)
 %    6) Call to free handler (special free like above?)
 %
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/***************************************************************************\
*  long g2xml_get_event_callback_type (G2pointer)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
long g2xml_get_event_callback_type (G2pointer event_index)
{
  xmlSAXEventDetail *event;

  event = (xmlSAXEventDetail *) g2ext_map_g2pointer_to_cpointer(event_index);

  return((long)(event ? event->callbackType : XML_CALLBACK_NONE));
}


/***************************************************************************\
*  long g2xml_events_ready (G2pointer)
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_events_ready (G2pointer context_index)
{
  long counter = 0L;
  xmlParserCtxtWrapper *wrapper;
  xmlSAXEventDetail *the_detail = NULL;

  wrapper = (xmlParserCtxtWrapper *) g2ext_map_g2pointer_to_cpointer(context_index);
  
  if (wrapper != NULL) {
    the_detail = wrapper->head;
  }
  while (the_detail != NULL) {
    counter++;
    the_detail = the_detail->next;
  }

  return(counter);
}


/***************************************************************************\
*  G2pointer g2xml_get_event_callback_data (G2pointer)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
G2pointer g2xml_get_event_callback_data (G2pointer event_index)
{
  xmlSAXEventDetail *event;

  event = (xmlSAXEventDetail *) g2ext_map_g2pointer_to_cpointer(event_index);
  
  return(g2ext_cache_cpointer(&(event->callbackData)));
}


/***************************************************************************\
*  G2pointer g2xml_dispose_event_callback_data (G2pointer)
*
*  PURPOSE: Reclaim SAX event callback data.
*
*  COMMENTS: Since the data is part of the event struct, the memory actually
*            holding the data isn't reclaimed until the event is reclaimed (by
*            g2xml_dispose_event).  This just decaches the pointer itself.
*  
****************************************************************************/
void g2xml_dispose_event_callback_data(G2pointer callback_data)
{
  g2ext_decache_g2pointer(callback_data);
}


/***************************************************************************\
*  G2pointer g2xml_dispose_event (G2pointer)
*
*  PURPOSE: Reclaim a SAX event.
*
*  COMMENTS:
*  
****************************************************************************/
void g2xml_dispose_event(G2pointer event_index)
{
  xmlSAXEventDetail *event;

  event = (xmlSAXEventDetail *) g2ext_map_g2pointer_to_cpointer(event_index);
  if (event != NULL) dispose_xml_sax_event_detail(event);
  
  g2ext_decache_g2pointer(event_index);
}


/***************************************************************************\
*  long g2xml_element_name_size (G2pointer)
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_element_name_size (G2pointer callback_index)
{
  xmlSAXDataType *callback_data;

  callback_data = (xmlSAXDataType *) g2ext_map_g2pointer_to_cpointer(callback_index);

  /* xmlStrlen handles NULL, so we don't need to check here. */
  return(xmlStrlen(callback_data->element.name));
}


/***************************************************************************\
*  long g2xml_start_element_atts_num (G2pointer)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
long g2xml_start_element_atts_num (G2pointer callback_index)
{
  int counter;
  xmlSAXDataType *callback_data;

  callback_data = (xmlSAXDataType *) g2ext_map_g2pointer_to_cpointer(callback_index);

  if (callback_data->element.atts == NULL) {
    return 0L;
  }

  for (counter = 0; callback_data->element.atts[counter] != NULL; counter++) {
    counter++;
    if (callback_data->element.atts[counter] == NULL) {
      break;
    }
  }
  return(counter);
}


/***************************************************************************\
*  long g2xml_start_element_att_size (G2pointer, long)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
long g2xml_start_element_att_size (G2pointer callback_index, long n_att)
{
  xmlSAXDataType *callback_data;

  callback_data = (xmlSAXDataType *) g2ext_map_g2pointer_to_cpointer(callback_index);

  return(xmlStrlen(callback_data->element.atts[n_att]));
}


/***************************************************************************\
*  long g2xml_fill_element_name_buffer (G2pointer, char *, long, long)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
long g2xml_fill_element_name_buffer (G2pointer callback_index,
                                     char *buf,
                                     long nbytes,
                                     long start)
{
  xmlSAXDataType *callback_data;
  xmlChar *element_name;

  callback_data = (xmlSAXDataType *) g2ext_map_g2pointer_to_cpointer(callback_index);
  element_name = callback_data->element.name;
  
  return(fill_element_name_buffer_helper(element_name, buf, nbytes, start));
}


/***************************************************************************\
*  long g2xml_fill_start_element_att_buffer (G2pointer, char *, long, long)
*
*  PURPOSE: 
*
*  COMMENTS:
*    This could be made more efficient by sending multiple atts at once,
*    essentially passing a char ** rather than a char *, but that's an
*    exercise for later.
*
*    I guess for now we're always going to assume that we can create a
*    big enough buffer from Lisp to hold an attribute, which is likely
*    to be small.  This function doesn't (yet?) take a start index.
*
****************************************************************************/
long g2xml_fill_start_element_att_buffer (G2pointer callback_index,
                                          char *buf,
                                          long nbytes,
                                          long att_num)
{
  xmlSAXDataType *callback_data;
  xmlChar *element_name;

  callback_data = (xmlSAXDataType *) g2ext_map_g2pointer_to_cpointer(callback_index);
  element_name = callback_data->element.atts[att_num];

  return(fill_element_name_buffer_helper(element_name, buf, nbytes, 0));
}


/***************************************************************************\
*  long g2xml_characters_or_comment_size (G2pointer)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
long g2xml_characters_or_comment_size (G2pointer callback_index)
{
  xmlSAXDataType *callback_data;

  callback_data = (xmlSAXDataType *) g2ext_map_g2pointer_to_cpointer(callback_index);

  return(callback_data->characters.len);
}


/***************************************************************************\
*  long g2xml_fill_characters_or_comment_buffer (G2pointer, char *, long, long)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
long g2xml_fill_characters_or_comment_buffer (G2pointer callback_index,
                                   char *buf,
                                   long nbytes,
                                   long start)
{
  xmlSAXDataType *callback_data;
  xmlChar *element_name;

  callback_data = (xmlSAXDataType *) g2ext_map_g2pointer_to_cpointer(callback_index);

  element_name = callback_data->characters.ch;
  
  return(fill_element_name_buffer_helper(element_name, buf, nbytes, start));
}



/***************************************************************************\
*  long g2xml_error_size (G2pointer)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
long g2xml_error_size (G2pointer callback_index)
{
  xmlSAXDataType *callback_data;

  callback_data = (xmlSAXDataType *) g2ext_map_g2pointer_to_cpointer(callback_index);

  return(callback_data->error.msg_size);
}


/***************************************************************************\
*  long g2xml_fill_error_buffer (G2pointer, char *, long, long)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
long g2xml_fill_error_buffer (G2pointer callback_index,
			      char *buf,
			      long nbytes)
{
  xmlSAXDataType *callback_data;
  xmlChar *element_name;

  callback_data = (xmlSAXDataType *) g2ext_map_g2pointer_to_cpointer(callback_index);

  element_name = callback_data->error.msg;
  
  return(fill_element_name_buffer_helper(element_name, buf, nbytes, 0));
}



/***************************************************************************\
*  void g2xml_init_sax ()
*
*  PURPOSE:  provides a standard-named API to the libxml2 function,
*    xmlInitParser
*
*  COMMENTS:
*    Having this API is probably a mistake.  From the XML doc: 
*    "xmlInitParser is not reentrant. Call once before processing in case of
*    use in multithreaded programs."  We're not multithreaded, and even if
*    we become so, it might make more sense to call xmlInitParser directly
*    from some C init function, instead of exposing it to Lisp.
*  
****************************************************************************/
void g2xml_init_sax ()
{
  if (called_xml_init_sax == 0) {
    xmlInitParser();
    called_xml_init_sax = 1;
  }
}


/***************************************************************************\
*  void g2xml_test_version ()
*
*  PURPOSE: 
*
*  COMMENTS:
*  
*   -- NOT YET USED --
****************************************************************************/
void g2xml_test_version ()
{
  /* COMPAT: Do not generate nodes for formatting spaces */
  LIBXML_TEST_VERSION
    ;
}


/***************************************************************************\
*  void g2xml_keep_blanks_default (long)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
*   -- NOT YET USED --
****************************************************************************/
void g2xml_keep_blanks_default (long x)
{
  xmlKeepBlanksDefault(x);
}


/***************************************************************************\
*  void gensym_init_sax_handler (xmlSAXHandler *)
*
*  PURPOSE: 
*
*  COMMENTS:
*  
****************************************************************************/
static void gensym_init_sax_handler(xmlSAXHandler *hdlr)
{
    hdlr->internalSubset = NULL;
    hdlr->externalSubset = NULL;
    hdlr->isStandalone = NULL;
    hdlr->hasInternalSubset = NULL;
    hdlr->hasExternalSubset = NULL;
    hdlr->resolveEntity = NULL;
    hdlr->getEntity = NULL;
    hdlr->getParameterEntity = NULL;
    hdlr->entityDecl = NULL;
    hdlr->attributeDecl = NULL;
    hdlr->elementDecl = NULL;
    hdlr->notationDecl = NULL;
    hdlr->unparsedEntityDecl = NULL;
    hdlr->setDocumentLocator = NULL;
    hdlr->startDocument = NULL;
    hdlr->endDocument = NULL;
    hdlr->startElement = NULL;
    hdlr->endElement = NULL;
    hdlr->reference = NULL;
    hdlr->characters = NULL;
    hdlr->cdataBlock = NULL;
    hdlr->ignorableWhitespace = NULL;
    hdlr->processingInstruction = NULL;
    hdlr->comment = NULL;
    hdlr->warning = NULL;
    hdlr->error = NULL;
    hdlr->fatalError = NULL;

    hdlr->initialized = 1;
}



/***************************************************************************\
*  G2pointer g2xml_make_parser_context ()
*
*  PURPOSE:
*    Returns the handle that callers will need to use the SAX parser, which
*    they will pass to g2xml_parse_chunk and g2xml_first_sax_event.
*
*  COMMENTS:
*    The handle users receive refers to an xmlParserCtxtWrapper, which is our
*    internal data structure containing a true xmlParserCtxtPtr and an event
*    queue.  Despite the name of this function, callers do not receive the
*    "real" parser context.  C callers can obtain the true parser context using
*    the parserContext field of the xmlParserCtxtWrapper structure.  Lisp
*    callers cannot access the xmlParserCtxtPtr.
*
*    Can't call exit() from this function... we don't want to exit G2!  I really
*    don't anticipate any trouble returning NULL to Lisp; it will just send the
*    NULL back to C later, and we can detect the NULL and do something smarter.
*    All of this is very unlikely to happen, but I still don't think we should
*    exit G2 if we get an out of memory problem here.  Of course, it means the
*    XML parsing will be all screwed up.  If we're really out of memory, G2 will
*    have, and will notice, more serious problems.
*
****************************************************************************/
G2pointer g2xml_make_parser_context ()
{
  xmlSAXHandlerPtr sax;
  xmlParserCtxtPtr context;
  xmlParserCtxtWrapper *wrapper;

  sax = (xmlSAXHandlerPtr)xmlMalloc(sizeof(xmlSAXHandler));
  if (sax == NULL) {
    fprintf(stderr, "\n  Out of memory in g2xml_make_parser_context.\n");
    return(g2ext_cache_cpointer(NULL));
  }

  gensym_init_sax_handler(sax);
  /* Add to this as more callbacks implemented */
  sax->startDocument = gensym_callback_startDocument;
  sax->endDocument = gensym_callback_endDocument;
  sax->startElement = gensym_callback_startElement;
  sax->endElement = gensym_callback_endElement;
  sax->characters = gensym_callback_characters;
  sax->comment = gensym_callback_comment;
  sax->warning = gensym_callback_warning;
  sax->error = gensym_callback_error;
  sax->fatalError = gensym_callback_fatal_error;

  context = xmlCreatePushParserCtxt(sax, NULL, NULL, 0, NULL);
  xmlFree(sax); /* the above function copies sax, we don't need it anymore */

  if (context == NULL) {
    fprintf(stderr, "\n  Out of memory in g2xml_make_parser_context.\n");
    return(g2ext_cache_cpointer(NULL));
  }

  wrapper = (xmlParserCtxtWrapper*)malloc(sizeof (xmlParserCtxtWrapper));

  if (wrapper == NULL) {
    fprintf(stderr, "\n  Out of memory in g2xml_make_parser_context.\n");
    xmlFreeParserCtxt(context);
    return(g2ext_cache_cpointer(NULL));
  }

  wrapper->parserContext = context;
  context->_private = (void *) wrapper;

  wrapper->next = NULL;		/* unused */

  wrapper->head = NULL;
  wrapper->tail = NULL;

  return(g2ext_cache_cpointer(wrapper));
}


/***************************************************************************\
*  long g2xml_parse_chunk (G2pointer, char *, long, long)
*
*  PURPOSE: provides a standard-named API to the libxml2 function,
*    xmlParseChunk
*
*  COMMENTS:
*  
****************************************************************************/
long g2xml_parse_chunk (G2pointer context_index, char *chunk, long size,
                        long terminate)
{
  xmlParserCtxtWrapper *wrapper;
  xmlParserCtxtPtr context;


  wrapper = (xmlParserCtxtWrapper *) g2ext_map_g2pointer_to_cpointer(context_index);
  context = wrapper->parserContext;
  return (long) xmlParseChunk(context, (const char *) chunk, (int) size,
                              (int) terminate);
}


/***************************************************************************\
*  long g2xml_parse_file (G2pointer context_index, const char *filename)
*
*  PURPOSE: provides a standard-named API to the libxml2 function,
*    xmlSAXUserParseFile
*
*  COMMENTS:
*  
****************************************************************************/
long g2xml_parse_file (G2pointer context_index, const char *filename)
{
  xmlParserCtxtWrapper *wrapper;
  xmlParserCtxtPtr context;

  wrapper = (xmlParserCtxtWrapper *) g2ext_map_g2pointer_to_cpointer(context_index);
  context = wrapper->parserContext;
  return (long) xmlSAXUserParseFile(context->sax, context, filename);
}


/***************************************************************************\
*  G2pointer g2xml_first_sax_event (G2pointer wrapper_index)
*
*  PURPOSE: provides a standard-named API to the get a pointer to the "detail"
*    field of the object pointed to by the pointer corresponding to the given
*    G2pointer index.
*
*                                  +-----------------------------+
*  G2pointer --->  Cpointer --->  | xmlParserCtxtWrapper object |
*                                |                             |
*                               |    detail ------------------+----+
*                              |                             |     +--> *this*
*                             +-----------------------------+
*
*  COMMENTS:
*    Even though we do a NULL check here to not SEGV, users should not pass
*    G2pointers which correspond to NULL.  They should do a valid_c_pointer
*    check first.
*  
****************************************************************************/
G2pointer g2xml_first_sax_event (G2pointer wrapper_index)
{
  return(get_event_detail_from_wrapper(wrapper_index, 1));
}


/***************************************************************************\
*  G2pointer g2xml_peek_first_sax_event (G2pointer wrapper_index)
*
*  PURPOSE: returns the first event on the queue, like g2xml_first_sax_event
*    also does, but this function does not remove it from the queue.
*
*  COMMENTS:
*    The same comment about NULL pointers from g2xml_first_sax_event applies
*    here as well.
*  
****************************************************************************/
G2pointer g2xml_peek_first_sax_event (G2pointer wrapper_index)
{
  return(get_event_detail_from_wrapper(wrapper_index, 0));
}


/***************************************************************************\
*  G2pointer g2xml_next_sax_event (G2pointer)
*
*  PURPOSE: provides a standard-named API to the get a pointer to the "next"
*    field of the object pointed to by the pointer corresponding to the given
*    G2pointer index.
*
*                                  +-----------------------------+
*  G2pointer --->  Cpointer --->  | xmlSAXEventDetail object    |
*                                |                             |
*                               |    next  -------------------+----+
*                              |                             |     +--> *this*
*                             +-----------------------------+  
*
*  COMMENTS:
*    Even though we do a NULL check here to not SEGV, users should not pass
*    G2pointers which correspond to NULL.  They should do a valid_c_pointer
*    check first.
*
*    Note there is no "andPop" notion here.  You can only pop the top of
*    the queue, although it's ok to "peek" into the middle if you want to.
*
****************************************************************************/
G2pointer g2xml_next_sax_event (G2pointer event_index)
{
  xmlSAXEventDetail *detail, *next_detail = NULL;

  detail = (xmlSAXEventDetail *) g2ext_map_g2pointer_to_cpointer(event_index);
  if (detail != NULL) {
    next_detail = detail->next;
  }
  return(g2ext_cache_cpointer(next_detail));
}


/***************************************************************************\
*  void g2xml_cleanup_parser (G2pointer)
*
*  PURPOSE: provides a standard-named API to the libxml2 function,
*    xmlFreeParserCtxt, and reclaims the memory used by its wrapper
*
*  COMMENTS:
*  
****************************************************************************/
void g2xml_cleanup_parser (G2pointer context_index)
{
  xmlParserCtxtWrapper *wrapper;
  xmlParserCtxtPtr context;
  xmlSAXEventDetail *cur;

  wrapper = (xmlParserCtxtWrapper *) g2ext_map_g2pointer_to_cpointer(context_index);

  cur = wrapper->head;
  while (cur != NULL) {
    wrapper->head = cur->next;
    dispose_xml_sax_event_detail(cur);
    cur = wrapper->head;
  }
  wrapper->head = NULL;
  wrapper->tail = NULL;

  context = wrapper->parserContext;
  xmlFreeParserCtxt(context);

  free(wrapper);
  g2ext_decache_g2pointer(context_index);
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - LIBXML Specific Functions
 %
 % Description:
 %
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

static xmlErrorQueue errorQueue;

/***************************************************************************\
*  static void enqueue_xml_error(void *userData, xmlErrorPtr error)
*
*  PURPOSE: Enqueue an XML error structure.
*
*  COMMENTS:
*    The userData argument is ignored; it's required by the
*    xmlStructuredErrorFunc function type (used by xmlSetStructuredErrorFunc).
*    There is only one global error queue, i.e. this assumes
*    single-threadedness.
*  
****************************************************************************/
static void enqueue_xml_error(void *userData, xmlErrorPtr error)
{
  xmlErrorQueueNode *node = 
    (xmlErrorQueueNode *) malloc(sizeof(xmlErrorQueueNode));

  /* The error structure is reused by libxml2, so copy it before putting it onto
   * the queue.  Also, initialize the memory to 0 with calloc, because otherwise
   * xmlCopyError will try to free any non-NULL fields it finds.
   */
  node->error = (xmlErrorPtr) calloc(1, sizeof(xmlError));
  xmlCopyError(error, node->error);
  node->next = NULL;
  
  if (errorQueue.head == NULL)
    errorQueue.head = node;
  else
    errorQueue.tail->next = node;

  errorQueue.tail = node;
}


/***************************************************************************\
*  G2pointer g2xml_read_file(char *path)
*
*  PURPOSE: Read an XML document from a file.
*
*  COMMENTS:
*    Returns the document pointer, or -1 if there are errors.  Warnings and
*    errors are enqueued and should be retrieved with g2xml_next_error.
*
****************************************************************************/
G2pointer g2xml_read_file (char *path)
{
  xmlDocPtr doc;

  xmlSetStructuredErrorFunc(NULL, enqueue_xml_error);
  xmlLineNumbersDefault(1);
  doc = xmlParseFile(path);

  if (doc) {
    return g2ext_cache_cpointer(doc);
  } else {
    return -1;
  }
}


/***************************************************************************\
*  G2pointer g2xml_read_string(char *string, int len)
*
*  PURPOSE: Read an XML document from a string buffer.
*
*  COMMENTS:
*    Returns the document pointer, or -1 if there are errors.  Warnings and
*    errors are enqueued and should be retrieved with g2xml_next_error.
*
****************************************************************************/
G2pointer g2xml_read_string(char *string, int len)
{
  xmlDocPtr doc;

  xmlSetStructuredErrorFunc(NULL, enqueue_xml_error);
  xmlLineNumbersDefault(1);
  doc = xmlParseMemory(string, len);

  return doc ? g2ext_cache_cpointer(doc) : -1;
}


/***************************************************************************\
*  G2pointer g2xml_next_error()
*
*  PURPOSE: Pop the next XML error from the queue and return it.
*
*  COMMENTS: Returns -1 if the queue is empty.
*
****************************************************************************/
G2pointer g2xml_next_error() {
  xmlErrorPtr error = NULL;
  xmlErrorQueueNode *node = errorQueue.head;

  if (node == NULL) return -1;
  error = node->error;
  errorQueue.head = node->next;
  free(node);

  return g2ext_cache_cpointer(error);
}


/***************************************************************************\
*  long g2xml_error_get_message_size(G2pointer error)
*
*  PURPOSE: Get the length of the message string of an XML error.
*
*  COMMENTS: Returns -1 if the error message is NULL.
*
****************************************************************************/
long g2xml_error_get_message_size(G2pointer error)
{
  xmlErrorPtr errorPtr = (xmlErrorPtr) g2ext_map_g2pointer_to_cpointer(error);
  return errorPtr->message == NULL ? -1 : xmlStrlen(errorPtr->message);
}


/***************************************************************************\
*  void g2xml_error_get_message_in_buffer(G2pointer error, char *buffer,
*                                         long size, long start)
*
*  PURPOSE: Copy the message string of an XML error into a buffer.
*
*  COMMENTS:
*
****************************************************************************/
void g2xml_error_get_message_in_buffer (G2pointer error, char *buffer,
					long size, long start)
{
  xmlErrorPtr errorPtr = (xmlErrorPtr) g2ext_map_g2pointer_to_cpointer(error);
  memcpy(buffer, errorPtr->message + start, size);
  buffer[size] = '\0';
}


/***************************************************************************\
*  long g2xml_error_get_filename_size(G2pointer error)
*
*  PURPOSE: Get the length of the filename string of an XML error.
*
*  COMMENTS: Returns -1 if the error filename is NULL.
*
****************************************************************************/
long g2xml_error_get_filename_size(G2pointer error)
{
  xmlErrorPtr errorPtr = (xmlErrorPtr) g2ext_map_g2pointer_to_cpointer(error);
  return errorPtr->file == NULL ? -1 : xmlStrlen(errorPtr->file);
}


/***************************************************************************\
*  void g2xml_error_get_filename_in_buffer(G2pointer error, char *buffer,
*                                         long size, long start)
*
*  PURPOSE: Copy the filename string of an XML error into a buffer.
*
*  COMMENTS:
*
****************************************************************************/
void g2xml_error_get_filename_in_buffer (G2pointer error, char *buffer,
					long size, long start)
{
  xmlErrorPtr errorPtr = (xmlErrorPtr) g2ext_map_g2pointer_to_cpointer(error);
  memcpy(buffer, errorPtr->file + start, size);
  buffer[size] = '\0';
}


/***************************************************************************\
*  long g2xml_error_get_line_number(G2pointer error)
*
*  PURPOSE: Get the line number of an XML error.
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_error_get_line_number(G2pointer error)
{
  xmlErrorPtr errorPtr = (xmlErrorPtr) g2ext_map_g2pointer_to_cpointer(error);
  return (long) errorPtr->line;
}


/***************************************************************************\
*  long g2xml_error_get_column_number(G2pointer error)
*
*  PURPOSE: Get the column number of an XML error.
*
*  COMMENTS: Returns 0 if N/A.
*
****************************************************************************/
long g2xml_error_get_column_number(G2pointer error)
{
  xmlErrorPtr errorPtr = (xmlErrorPtr) g2ext_map_g2pointer_to_cpointer(error);
  return (long) errorPtr->int2;
}


/***************************************************************************\
*  void g2xml_dispose_error(G2pointer error)
*
*  PURPOSE: Reclaim an XML error.
*
*  COMMENTS:
*  
****************************************************************************/
void g2xml_dispose_error(G2pointer error)
{
  xmlErrorPtr errorPtr = (xmlErrorPtr) g2ext_map_g2pointer_to_cpointer(error);
  if (errorPtr != NULL) {
    xmlResetError(errorPtr);
    free(errorPtr);
  }
  g2ext_decache_g2pointer(error);
}


/***************************************************************************\
*  long g2xml_write_file(G2pointer doc, char *path)
*
*  PURPOSE: Pretty-print an XML document to a file.
*
*  COMMENTS: Returns the number of bytes written or -1 in case of failure.
*
****************************************************************************/
long g2xml_write_file (G2pointer doc, char *path)
{
  xmlDocPtr docPtr =
    (xmlDocPtr) g2ext_map_g2pointer_to_cpointer(doc);
  xmlIndentTreeOutput = 1;
  return xmlSaveFormatFile(path, docPtr, 1);
}


/***************************************************************************\
*  G2pointer g2xml_write_buffer(G2pointer doc)
*
*  PURPOSE: Pretty-print an XML document to a newly allocated buffer.
*
*  COMMENTS: The returned buffer should be disposed when done.
*
****************************************************************************/
G2pointer g2xml_write_buffer(G2pointer doc)
{
  xmlDocPtr docPtr =
    (xmlDocPtr) g2ext_map_g2pointer_to_cpointer(doc);
  xmlChar *mem;
  int size;
  xmlBufferPtr buf;

  xmlIndentTreeOutput = 1;
  xmlDocDumpFormatMemory(docPtr, &mem, &size, 1);
  buf = xmlBufferCreateStatic(mem, size);
  return g2ext_cache_cpointer(buf);
}


/***************************************************************************\
*  long g2xml_buffer_get_content_size(G2pointer buf)
*
*  PURPOSE: Get the length of the content of an XML buffer.
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_buffer_get_content_size(G2pointer buf)
{
  xmlBufferPtr bufPtr = (xmlBufferPtr) g2ext_map_g2pointer_to_cpointer(buf);
  return bufPtr->size;
}


/***************************************************************************\
*  void g2xml_buffer_get_content_in_buffer(G2pointer buf, char *buffer,
*                                          long size, long start)
*
*  PURPOSE: Copy the content of an XML buffer into a buffer.
*
*  COMMENTS:
*
****************************************************************************/
void g2xml_buffer_get_content_in_buffer(G2pointer buf, char *buffer,
					long size, long start)
{
  xmlBufferPtr bufPtr = (xmlBufferPtr) g2ext_map_g2pointer_to_cpointer(buf);
  memcpy(buffer, bufPtr->content + start, size);
  buffer[size] = '\0';
}


/***************************************************************************\
*  void g2xml_dispose_buffer(G2pointer buf)
*
*  PURPOSE: Reclaim an XML buffer.
*
*  COMMENTS:
*  
****************************************************************************/
void g2xml_dispose_buffer(G2pointer buf)
{
  xmlBufferPtr bufPtr = (xmlBufferPtr) g2ext_map_g2pointer_to_cpointer(buf);
  if (bufPtr != NULL) {
    xmlFree(bufPtr->content);
    bufPtr->content = NULL;
    xmlBufferFree(bufPtr);
  }
  g2ext_decache_g2pointer(buf);
}


/***************************************************************************\
*  void g2xml_create_document
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
G2pointer g2xml_create_document ()
{
  xmlDocPtr doc = xmlNewDoc("1.0");
  if (doc) {
    return g2ext_cache_cpointer(doc);
  } else {
    return -1;
  }
}


/***************************************************************************\
*  void g2xml_dispose_document
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
void g2xml_dispose_document (G2pointer doc)
{
  xmlDocPtr docPtr =
    (xmlDocPtr) g2ext_map_g2pointer_to_cpointer(doc);

  xmlFreeDoc(docPtr);
  g2ext_decache_g2pointer(doc);
}


/***************************************************************************\
*  void g2xml_dispose_pointer
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
void g2xml_dispose_pointer (G2pointer pointer)
{
  g2ext_decache_g2pointer(pointer);
}


/***************************************************************************\
*  long g2xml_get_line
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_get_line (G2pointer node)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node);

  return XML_GET_LINE(nodePtr);
}


/***************************************************************************\
*  xmlChar *g2xml_get_content
*
*  PURPOSE: 
*    Get the text content of a node (or its children if it's not a TEXT node).
*
*  COMMENTS:
*
****************************************************************************/
xmlChar *g2xml_get_content (G2pointer node)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node);

  return xmlNodeGetContent(nodePtr);
}


/***************************************************************************\
*  long g2xml_get_content_size
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_get_content_size (G2pointer node)
{
  xmlChar *content = g2xml_get_content(node);

  if (content) {
    return xmlStrlen(content);
  } else {
    return -1;
  }
}


/***************************************************************************\
*  void g2xml_get_content_in_buffer
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
void g2xml_get_content_in_buffer (G2pointer node, char *destination,
                                  long nbytes,
                                  long start)
{
  xmlChar *source = g2xml_get_content (node);

  memcpy(destination, (source + (start / sizeof(xmlChar))), nbytes);
  destination[nbytes] = '\0';
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - DOM API Functions
 %
 % Description:
 %
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
*  long g2xml_node_type(G2pointer node)
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_node_type (G2pointer node)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node);
  return nodePtr->type;
}


/***************************************************************************\
*  G2pointer g2xml_node_parent_node(G2pointer node)
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_node_parent_node (G2pointer node)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node);
  xmlNodePtr parent = nodePtr->parent;
  if (parent &&
      /* Don't return the document node, because dom.lisp will try to reclaim it
       * twice.  This should probably be fixed some other way.  -dougo, 5/2/05
       */
      parent->type != XML_DOCUMENT_NODE)
  {
    return g2ext_cache_cpointer(parent);
  } else {
    return -1;
  }
}


/***************************************************************************\
*  G2pointer g2xml_node_child_nodes(G2pointer node)
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_node_child_nodes (G2pointer node)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node);

  xmlNodePtr children =
    nodePtr->children;

  if (children) {
    return g2ext_cache_cpointer(children);
  } else {
    return -1;
  }
}


/***************************************************************************\
*  G2pointer g2xml_node_last_child(G2pointer node)
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_node_last_child (G2pointer node)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node);

  xmlNodePtr last =
    nodePtr->last;

  if (last) {
    return g2ext_cache_cpointer(last);
  } else {
    return -1;
  }
}


/***************************************************************************\
*  G2pointer g2xml_node_previous_sibling(G2pointer node)
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_node_previous_sibling (G2pointer node)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node);

  xmlNodePtr prev =
    nodePtr->prev;

  if (prev) {
    return g2ext_cache_cpointer(prev);
  } else {
    return -1;
  }
}


/***************************************************************************\
*  G2pointer g2xml_node_next_sibling(G2pointer node)
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_node_next_sibling (G2pointer node)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node);

  xmlNodePtr next =
    nodePtr->next;

  if (next) {
    return g2ext_cache_cpointer(next);
  } else {
    return -1;
  }
}


/***************************************************************************\
*  G2pointer g2xml_node_new_child(G2pointer parent, G2pointer namespace, char *name, char *content)
*
*  PURPOSE:
*    Create a new child element with the given namespace, local name, and text
*    content.
*
*  COMMENTS:
*    Use namespace = -1 to use the parent's current namespace (if any).
*    Use content = "" or NULL for an empty element.
*
*    If creating the root element of a document, i.e. parent is a document node,
*    there's a chicken-and-egg problem: to create a namespace, you need an
*    element to attach it to, so you can't specify the namespace of the root
*    element before it's created.  In this case, use namespace = -1 to create
*    the root element with no namespace, then create the namespace, then use
*    g2xml_node_set_namespace to set the root element's namespace.
*
****************************************************************************/
G2pointer g2xml_node_new_child (G2pointer parent,
                                G2pointer namespace,
                                char *name,
                                char *content)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(parent);

  xmlNsPtr nsPtr = (namespace == -1
                    ? (xmlNsPtr) NULL
                    : (xmlNsPtr) g2ext_map_g2pointer_to_cpointer(namespace));

  xmlNodePtr child =
    xmlNewChild(nodePtr, nsPtr, name,
                /* Convert an empty content string to NULL to make the new child
                 * be an empty element, as opposed to an element with a single
                 * empty TEXT node child. */
                content && content[0] == '\0' ? NULL : content);

  if (child) {
    return g2ext_cache_cpointer(child);
  } else {
    return -1;
  }
}


/***************************************************************************
* void g2xml_node_add_content(G2pointer node, char *value)
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
void g2xml_node_add_content (G2pointer node,
                             char *value)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node);

  xmlNodeAddContent(nodePtr, value);
}


/***************************************************************************\
*  G2pointer g2xml_node_add_comment(G2pointer node, char *text)
*
*  PURPOSE:
*    Add a new comment node with the given text to the given node.
*
*  COMMENTS:
*
****************************************************************************/
void g2xml_node_add_comment (G2pointer node, char *text)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node);

  xmlAddChild(nodePtr, xmlNewDocComment(nodePtr->doc, text));
}


/***************************************************************************\
*  G2pointer g2xml_node_attributes(G2pointer node)
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
G2pointer g2xml_node_attributes (G2pointer node)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node);

  xmlElementType type =
    nodePtr->type;

  switch (type) {
  case XML_ELEMENT_NODE: {
    xmlAttrPtr attributes = nodePtr->properties;

    if (attributes) {
      return g2ext_cache_cpointer(attributes);
    } else {
      return -1;
    }
    break;;
  }
  default: {
    return -1;
  }
  }
}


/***************************************************************************\
*  long g2xml_node_has_child_nodes_p(G2pointer node)
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_node_has_child_nodes_p (G2pointer node)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node);

  xmlNodePtr children =
    nodePtr->children;

  return (long) children;
}


/***************************************************************************\
*  long g2xml_node_namespace
*
*  PURPOSE: Get the namespace of an element or attribute, if any.
*
*  COMMENTS: Returns -1 if none.
*
****************************************************************************/
G2pointer g2xml_node_namespace (G2pointer node)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node);

  xmlElementType type =
    nodePtr->type;

  switch (type) {
  case XML_ELEMENT_NODE:
  case XML_ATTRIBUTE_NODE: {
    if (nodePtr->ns) {
      return g2ext_cache_cpointer(nodePtr->ns);
    } else {
      return -1;
    }
  }
  default: {
    return -1;
  }
  }
}
  

/***************************************************************************\
*  void g2xml_node_set_namespace(G2pointer node, G2pointer namespace)
*
*  PURPOSE:
*    Set the namespace of an element or attribute.
*
*  COMMENTS:
*    Use namespace = -1 to remove the namespace.  For an attribute, this means
*    it is a local attribute.  For an element, this means it's in the default
*    namespace AND that there is no default namespace, which had better be
*    true about the document!  Note that this does not change any of the child
*    element namespaces.
*
****************************************************************************/
void g2xml_node_set_namespace(G2pointer node, G2pointer namespace)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node);

  xmlNsPtr nsPtr = (namespace == -1
                    ? (xmlNsPtr) NULL
                    : (xmlNsPtr) g2ext_map_g2pointer_to_cpointer(namespace));

  xmlSetNs(nodePtr, nsPtr);
}


/***************************************************************************\
*  G2pointer g2xml_node_lookup_namespace(G2pointer node, const xmlChar *prefix)
*
*  PURPOSE:
*    Lookup the namespace associated with the given prefix, starting with the
*    given node and going up its parent hierarchy.
*
*  COMMENTS:
*    Returns -1 if there is no such namespace.
*    Use prefix == "" or NULL for the default namespace.
*
*    This corresponds roughly with the DOM Level 3 method lookupNamespaceURI on
*    the Node interface, except it returns the namespace structure instead of
*    just the URI.
*
****************************************************************************/
G2pointer g2xml_node_lookup_namespace(G2pointer node, const xmlChar *prefix)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node);

  xmlNsPtr nsPtr =
    xmlSearchNs(nodePtr->doc, nodePtr,
                prefix && prefix[0] == '\0' ? NULL : prefix);

  return nsPtr ? g2ext_cache_cpointer(nsPtr) : -1;
}


/***************************************************************************\
*  long g2xml_node_has_attributes_p(G2pointer node)
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_node_has_attributes_p (G2pointer node)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node);

  xmlElementType type =
    nodePtr->type;

  switch (type) {
  case XML_ELEMENT_NODE: {
    return (long) nodePtr->properties;
  }
  default: {
    return 0;
  }
  }
}


/***************************************************************************\
*  long g2xml_node_list_length
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_node_list_length (G2pointer node_list)
{
  xmlNodePtr nodePtr;
  int i=0;
  for (nodePtr = (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node_list);
       nodePtr; nodePtr = nodePtr->next, i++) {
  }
  return i;
}


/***************************************************************************\
*  G2pointer g2xml_node_list_item
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
G2pointer g2xml_node_list_item (G2pointer node_list, long index)
{
  xmlNodePtr nodePtr;
  int i=0;
  for (nodePtr = (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node_list);
       nodePtr; nodePtr = nodePtr->next, i++) {
    if (i == index) {
      return g2ext_cache_cpointer(nodePtr);
    }
  }
  return -1;
}


/***************************************************************************\
*  xmlChar *g2xml_attr_get_name
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
const xmlChar *g2xml_attr_get_name (G2pointer attr)
{
  xmlAttrPtr attrPtr =
    (xmlAttrPtr) g2ext_map_g2pointer_to_cpointer(attr);

  return attrPtr->name;
}


/***************************************************************************\
*  long g2xml_attr_get_name_size
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_attr_get_name_size (G2pointer attr)
{
  const xmlChar *name = g2xml_attr_get_name(attr);

  if (name) {
    return xmlStrlen(name);
  } else {
    return -1;
  }
}


/***************************************************************************\
*  void g2xml_attr_get_name_in_buffer
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
void g2xml_attr_get_name_in_buffer (G2pointer attr, char *destination,
                                    long nbytes,
                                    long start)
{
  const xmlChar *source = g2xml_attr_get_name(attr);

  memcpy(destination, (source + (start / sizeof(xmlChar))), nbytes);
  destination[nbytes] = '\0';
}


/***************************************************************************\
*  char *g2xml_node_local_name
*
*  PURPOSE:
*    Get the local name of a node.
*
*  COMMENTS:
*    Note that this is not the same as an element tag name or attribute
*    name, which libxml2 does not provide (although it could be reconstructed
*    from the local name and namespace structure).  In particular, the namespace
*    prefix is not included in the local name, i.e., it is an NCName.
*
****************************************************************************/
const xmlChar *g2xml_node_local_name (G2pointer node)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(node);

  return nodePtr->name;
}


/***************************************************************************\
*  long g2xml_node_local_name_size
*
*  PURPOSE: 
*    Get the length of the local name of a node.
*
*  COMMENTS:
*    Returns -1 if the node has no name, e.g. if it is not an element or
*    attribute.
*
****************************************************************************/
long g2xml_node_local_name_size (G2pointer node)
{
  const xmlChar *name = g2xml_node_local_name(node);

  if (name) {
    return xmlStrlen(name);
  } else {
    return -1;
  }
}


/***************************************************************************\
*  void g2xml_node_local_name_in_buffer
*
*  PURPOSE: 
*    Copy the local name of a node into a string buffer.
*
*  COMMENTS:
*
****************************************************************************/
void g2xml_node_local_name_in_buffer (G2pointer node, char *destination,
                                      long nbytes,
                                      long start)
{
  const xmlChar *source = g2xml_node_local_name(node);

  memcpy(destination, (source + (start / sizeof(xmlChar))), nbytes);
  destination[nbytes] = '\0';
}


/***************************************************************************\
*  G2pointer g2xml_element_set_attribute
*
*  PURPOSE: Set or add an attribute.
*
*  COMMENTS: Use namespace = -1 for a local attribute.
*
****************************************************************************/
void g2xml_element_set_attribute (G2pointer element,
				  G2pointer namespace,
                                  char *attrname,
                                  char *attrvalue)
{
  xmlNodePtr node =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(element);
  xmlNsPtr ns = (namespace == -1
		 ? (xmlNsPtr) NULL
		 : (xmlNsPtr) g2ext_map_g2pointer_to_cpointer(namespace));

  xmlSetNsProp(node, ns, attrname, attrvalue);
}


/***************************************************************************\
*  xmlChar * g2xml_element_get_attribute
*
*  PURPOSE: Get the value of an attribute, or -1 if no such attribute exists.
*
*  COMMENTS: Use namespace = "" or NULL for a local attribute.
*
****************************************************************************/
const xmlChar *g2xml_element_get_attribute (G2pointer element,
					    char *name, char *namespace)
{
  xmlNodePtr nodePtr =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(element);

  return (namespace && namespace[0] != '\0'
	  ? xmlGetNsProp(nodePtr, name, namespace)
	  : xmlGetNoNsProp(nodePtr, name));
}


/***************************************************************************\
*  long g2xml_element_get_attribute_size
*
*  PURPOSE: Get the size of the value of an attribute, or -1 if no such
*           attribute exists.
*
*  COMMENTS: Use namespace = "" or NULL for a local attribute.
*
****************************************************************************/
long g2xml_element_get_attribute_size (G2pointer element,
				       char *name, char *namespace)
{
  const xmlChar *attr =
    g2xml_element_get_attribute(element, name, namespace);

  if (attr) {
    return xmlStrlen(attr);
  } else {
    return -1;
  }
}


/***************************************************************************\
*  void g2xml_element_get_attribute_in_buffer
*
*  PURPOSE: Copy the value of an attribute into a buffer.
*
*  COMMENTS: Use namespace = "" or NULL for a local attribute.
*
****************************************************************************/
void g2xml_element_get_attribute_in_buffer (G2pointer element,
                                            char *name,
					    char *namespace,
                                            char *destination,
                                            long nbytes,
                                            long start)
{
  const char *source =
    g2xml_element_get_attribute(element, name, namespace);

  memcpy(destination, (source + (start / sizeof(char))), nbytes);
  destination[nbytes] = '\0';
}


/***************************************************************************\
*  G2pointer g2xml_element_get_attribute_node
*
*  PURPOSE: Get an attribute, or -1 if no such attribute exists.
*
*  COMMENTS: Use namespace = "" or NULL for a local attribute.
*
****************************************************************************/
G2pointer g2xml_element_get_attribute_node (G2pointer element,
					    char *name, char *namespace)
{
  xmlNodePtr node =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(element);

  xmlAttrPtr attr;

  if (namespace && namespace[0] == '\0') namespace = NULL;

  attr = xmlHasNsProp(node, name, namespace);

  if (attr) {
    return g2ext_cache_cpointer(attr);
  } else {
    return -1;
  }
}


/***************************************************************************\
*  long g2xml_element_has_attribute_p
*
*  PURPOSE: Check if an attribute exists.
*
*  COMMENTS: Use namespace = "" or NULL for a local attribute.
*
****************************************************************************/
long g2xml_element_has_attribute_p (G2pointer element,
				    char *name, char *namespace)
{
  xmlNodePtr node =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(element);

  if (namespace && namespace[0] == '\0') namespace = NULL;

  return (long) xmlHasNsProp(node, name, namespace);
}


/***************************************************************************\
*  G2pointer g2xml_element_new_namespace
*
*  PURPOSE:
*    Add a new namespace declaration to an element.
*
*  COMMENTS:
*    Use prefix == "" or NULL for the default namespace.  The new namespace is
*    returned.
*
****************************************************************************/
G2pointer g2xml_element_new_namespace (G2pointer element,
				       xmlChar *uri,
				       xmlChar *prefix)
{
  xmlNodePtr node =
    (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(element);

  xmlNsPtr ns =
    xmlNewNs(node, uri, prefix && prefix[0] == '\0' ? NULL : prefix);

  if (ns) {
    return g2ext_cache_cpointer(ns);
  } else {
    return -1;
  }
}


/***************************************************************************\
*  long g2xml_element_get_namespace_list
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
G2pointer g2xml_element_get_namespace_list (G2pointer document,
					    G2pointer element)
{
  xmlDocPtr docPtr;
  xmlNodePtr nodePtr;
  xmlNsPtr *list;

  docPtr = (xmlDocPtr) g2ext_map_g2pointer_to_cpointer(document);
  nodePtr = (xmlNodePtr) g2ext_map_g2pointer_to_cpointer(element);

  list = xmlGetNsList(docPtr, nodePtr);

  if (list) {
    return g2ext_cache_cpointer(*list);
  } else {
    return -1;
  }
}


/***************************************************************************\
*  long g2xml_namespace_list_length
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_namespace_list_length (G2pointer namespace_list)
{
  xmlNsPtr nsPtr;
  int i=0;

  for (nsPtr = (xmlNsPtr) g2ext_map_g2pointer_to_cpointer(namespace_list);
       nsPtr != NULL;
       nsPtr = nsPtr->next, i++) {
  }
  return i;
}


/***************************************************************************\
*  G2pointer g2xml_namespace_list_item
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
G2pointer g2xml_namespace_list_item (G2pointer namespace_list, long index)
{
  xmlNsPtr nsPtr;
  int i=0;

  for (nsPtr = (xmlNsPtr) g2ext_map_g2pointer_to_cpointer(namespace_list);
       nsPtr; nsPtr = nsPtr->next, i++) {
    if (i == index) {
      return g2ext_cache_cpointer(nsPtr);
    }
  }
  return -1;
}


/***************************************************************************\
*  xmlChar *g2xml_namespace_get_uri
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
const xmlChar *g2xml_namespace_get_uri (G2pointer xml_namespace)
{
  xmlNsPtr ns = (xmlNsPtr) g2ext_map_g2pointer_to_cpointer(xml_namespace);
  return ns->href;
}


/***************************************************************************\
*  long g2xml_get_namespace_uri_size
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_namespace_get_uri_size (G2pointer xml_namespace)
{
  const xmlChar *uri = g2xml_namespace_get_uri(xml_namespace);

  if (uri) {
    return xmlStrlen(uri);
  } else {
    return -1;
  }
}


/***************************************************************************\
*  void g2xml_namespace_get_uri_in_buffer (G2pointer xml_namespace)
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
void g2xml_namespace_get_uri_in_buffer (G2pointer node, char *destination,
                                        long nbytes,
                                        long start)

{
  const xmlChar *source = g2xml_namespace_get_uri(node);

  memcpy(destination, (source + (start / sizeof(xmlChar))), nbytes);
  destination[nbytes] = '\0';
}


/***************************************************************************\
*  char *g2xml_namespace_get_prefix
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
const char *g2xml_namespace_get_prefix (G2pointer xml_namespace)
{
  xmlNsPtr ns = (xmlNsPtr) g2ext_map_g2pointer_to_cpointer(xml_namespace);
  return ns->prefix;
}


/***************************************************************************\
*  long g2xml_get_namespace_prefix_size
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
long g2xml_namespace_get_prefix_size (G2pointer xml_namespace)
{
  const xmlChar *prefix = g2xml_namespace_get_prefix(xml_namespace);

  if (prefix) {
    return xmlStrlen(prefix);
  } else {
    return -1;
  }
}


/***************************************************************************\
*  void g2xml_namespace_get_prefix_in_buffer (G2pointer xml_namespace)
*
*  PURPOSE: 
*
*  COMMENTS:
*
****************************************************************************/
void g2xml_namespace_get_prefix_in_buffer (G2pointer node, char *destination,
                                           long nbytes,
                                           long start)
{
  const xmlChar *source = g2xml_namespace_get_prefix(node);

  memcpy(destination, (source + (start / sizeof(xmlChar))), nbytes);
  destination[nbytes] = '\0';
}


/***************************************************************************\
*  long g2xml_document_validate (G2pointer xml_document,
*                                G2pointer xml_schema_document)
*
*  PURPOSE: Validate an XML document using an XML Schema document.
*
*  COMMENTS: Returns 0 iff valid, a nonzero error code otherwise.
*
****************************************************************************/
long g2xml_document_validate (G2pointer xml_document,
			      G2pointer xml_schema_document)
{
  xmlDocPtr schema_doc =
    (xmlDocPtr) g2ext_map_g2pointer_to_cpointer(xml_schema_document);
  xmlSchemaParserCtxtPtr parser_ctxt =
    xmlSchemaNewDocParserCtxt(schema_doc);
  xmlSchemaPtr schema =
    xmlSchemaParse(parser_ctxt);
  xmlSchemaValidCtxtPtr valid_ctxt =
    xmlSchemaNewValidCtxt(schema);
  xmlDocPtr doc =
    (xmlDocPtr) g2ext_map_g2pointer_to_cpointer(xml_document);
  int err =
    xmlSchemaValidateDoc(valid_ctxt, doc);

  xmlSchemaFreeParserCtxt(parser_ctxt);
  xmlSchemaFree(schema);
  xmlSchemaFreeValidCtxt(valid_ctxt);

  return (long) err;
}


long g2xml_validate (G2pointer xml_document)
{
  xmlSchemaValidCtxtPtr valid_ctxt = xmlSchemaNewValidCtxt(NULL);
  xmlDocPtr doc = (xmlDocPtr) g2ext_map_g2pointer_to_cpointer(xml_document);
  int err = xmlSchemaValidateDoc(valid_ctxt, doc);

  xmlSchemaFreeValidCtxt(valid_ctxt);
  return (long) err;
}