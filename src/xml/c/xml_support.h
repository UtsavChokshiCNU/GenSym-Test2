#ifndef _XMLSAXSUPPORT_H
#define _XMLSAXSUPPORT_H

#include <libxml/parser.h>
#include <libxml/xmlschemas.h>
#include <stdarg.h>
#include <string.h>
#include "cprim.h"		/* Cpointer stuff */


#if defined(WIN32)
#  ifndef vsnprintf
#    define vsnprintf _vsnprintf
#  endif
#endif


/* Callback constants -- these constants must be kept in sync with the values
 * in lisp/sax.lisp.  Note that they also are consistent with the positions
 * in the structure of functions used by libxml2.  This really doesn't serve
 * any particular purpose, but it would be nice to keep them coordinated.
 *   - jv, 1/12/03
 */
#define XML_CALLBACK_NONE            -1
#define XML_CALLBACK_START_DOCUMENT  12
#define XML_CALLBACK_END_DOCUMENT    13
#define XML_CALLBACK_START_ELEMENT   14
#define XML_CALLBACK_END_ELEMENT     15
#define XML_CALLBACK_CHARACTERS      17
#define XML_CALLBACK_COMMENT         20
#define XML_CALLBACK_WARNING         21
#define XML_CALLBACK_ERROR           22
#define XML_CALLBACK_FATAL_ERROR     23


/* For reference, here are the callbacks supported by the version of the SAX
 * parser we are using.
  0   internalSubsetSAXFunc internalSubset;
  1   isStandaloneSAXFunc isStandalone;
  2   hasInternalSubsetSAXFunc hasInternalSubset;
  3   hasExternalSubsetSAXFunc hasExternalSubset;
  4   resolveEntitySAXFunc resolveEntity;
  5   getEntitySAXFunc getEntity;
  6   entityDeclSAXFunc entityDecl;
  7   notationDeclSAXFunc notationDecl;
  8   attributeDeclSAXFunc attributeDecl;
  9   elementDeclSAXFunc elementDecl;
 10   unparsedEntityDeclSAXFunc unparsedEntityDecl;
 11   setDocumentLocatorSAXFunc setDocumentLocator;
 12   startDocumentSAXFunc startDocument;
 13   endDocumentSAXFunc endDocument;
 14   startElementSAXFunc startElement;
 15   endElementSAXFunc endElement;
 16   referenceSAXFunc reference;
 17   charactersSAXFunc characters;
 18   ignorableWhitespaceSAXFunc ignorableWhitespace;
 19   processingInstructionSAXFunc processingInstruction;
 20   commentSAXFunc comment;
 21   warningSAXFunc warning;
 22   errorSAXFunc error;
 23   fatalErrorSAXFunc fatalError;
 24   getParameterEntitySAXFunc getParameterEntity;
 25   cdataBlockSAXFunc cdataBlock;
 26   externalSubsetSAXFunc externalSubset;
*/

typedef long xmlSAXCallbackType;

typedef union 
{
  struct {
    xmlChar *name; /* startElement and endElement (no atts for endElement) */
    xmlChar **atts;
  } element;
  struct {
    xmlChar *ch;	/* characters and comment callback */
    int len;
  } characters;
  struct {
    char *msg;   /* warning or error message */
    int msg_size;
    /* Note at some point we may want to expose these data in a finer grained
     * manner; we could add members to this struct if we so choose.  That's one
     * reason to have this be a separate union than we have for characters/
     * comment, even though their data are essentially the same.  -jv, 1/15/03
     */
  } error;
  /* add more structs here as more callbacks implemented */
} xmlSAXDataType;


typedef struct _xmlSAXEventDetail
{
  struct _xmlSAXEventDetail *next;
  xmlSAXCallbackType callbackType;
  xmlSAXDataType callbackData;
} xmlSAXEventDetail;

typedef struct _xmlParserCtxtWrapper
{
  xmlParserCtxtPtr parserContext;
  struct _xmlParserCtxtWrapper* next;
  xmlSAXEventDetail *head;
  xmlSAXEventDetail *tail;
} xmlParserCtxtWrapper;

typedef struct _xmlErrorQueueNode
{
  xmlErrorPtr error;
  struct _xmlErrorQueueNode *next;
} xmlErrorQueueNode;

typedef struct _xmlErrorQueue
{
  xmlErrorQueueNode *head;
  xmlErrorQueueNode *tail;
} xmlErrorQueue;

#endif
