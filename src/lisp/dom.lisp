;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module DOM - Document Object Model (DOM) Lisp utility

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Allan Scott, Doug Orleans

;;;; Forward References


;;;; About DOM

;;; The Document Object Model (DOM) is a standard for representing XML documents
;;; in a tree form in memory.  DOM is a platform and language neutral interface
;;; that allows programs and scrips to dynamically access an update the content
;;; and structure of documents.
;;;
;;; This module is an attempt to provide a Gensym Lisp binding for the DOM Level 2
;;; Core Specification which is specified at the following URL:
;;;
;;; http://www.w3.org/TR/DOM-Level-2-Core/
;;;
;;; DOM is very useful when processing XML documents - particularly for applications
;;; that wish to store an XML document in memory and perform modifications to an
;;; XML document.
;;;
;;; Below is a brief description of the structures in DOM that is taken from
;;; page 15 of the DOM Level 2 Core specification (13 November 2000):
;;;
;;; Document -- Element (max of 1), ProcessInstruction, Comment, DocumentType
;;; (max of 1)
;;; DocumentFragment -- Element, ProcessingInstruction, Comment, CDataSection,
;;; EntityReference
;;; DocumentType -- no children
;;; EntityReference -- Element, ProcessingInstruction, Comment, Text, CDataSection,
;;; EntityReference
;;; Attr -- Text, EntityReferenc
;;; ProcessingInstruction -- no children
;;; Comment -- no children
;;; Text -- no children
;;; CDataSection -- no children
;;; Entity -- Element, ProcessingInstruction, Comment, Text, CDataSection, EntityReference
;;; Notation -- no children
;;;

;;;; Implementation Notes
;;;
;;; All structures in DOM are represented by Lisp structures.
;;; The actual DOM tree is stored entirely in libxml2 internal C representation.
;;; The Lisp structures exist only to serve as wrappers to the underlying
;;; internal C representation.
;;;
;;; All methods in DOM are represented by Lisp functions.
;;; The implementation of each of these functions always calls
;;; into the internal libxml C representation.
;;;
;;; Only the aspects of DOM that are supported by libxml2 will be supported
;;; in the Lisp bindings.
;;;
;;; Note that the names of all the structures used in the Lisp bindings
;;; of Dom are preceded with the prefix xml- in order to avoid naming
;;; confusion with other structures used in the Gensym Lisp.
;;;
;;; Note that Lisp naming conventions of separating names with - rather
;;; than be capitalization is used.
;;;


;;;; Code organization
;;;
;;; xml/c/lispdom.c - C to Lisp interface for libxml2 DOM features
;;; lisp/dom.lisp - Lisp bindings for DOM API
;;; lisp/g2-bpel.lisp - initial user of Lisp DOM bindings


;;;; Lisp Example
;;;
;;; A test of functions to access the parse result of the
;;; following very simple document
;;;
;;; <?xml version="1.0"?>
;;;
;;; <root>
;;;   <element1 attr1="attr1-val"  attr2="attr2-val">
;;; 	<element2>The contents of element2</element2>
;;;    </element1>
;;; </root>
;;;
;;; > (xml-read-file "/home/ajs/xml/test.xml")
;;; #<XML-NODE type=XML-DOCUMENT-NODE @2122>
;;;
;;; > (xml-document-root-element *)
;;; #<XML-NODE type=XML-ELEMENT-NODE @2123>
;;;
;;; > (xml-node-child-nodes *)
;;; #<XML-NODE-LIST length=3 @2124>
;;;
;;; > (xml-node-list-item * 1)
;;; #<XML-NODE type=XML-ELEMENT-NODE @2125>
;;
;;; >  (xml-node-local-name *)
;;; #w"element1"
;;;
;;; > (xml-element-get-attribute (@ 2125) "attr1")
;;; #w"attr1-val"
;;;
;;;
;;; A test of functions to build and write out an xml
;;; document
;;;
;;; > (xml-create-document)
;;; #<XML-NODE type=XML-DOCUMENT-NODE @2121>
;;;
;;; > (xml-node-new-child * "root")
;;; #<XML-NODE type=XML-ELEMENT-NODE @2122>
;;;
;;; > (xml-node-new-child * "element1")
;;; #<XML-NODE type=XML-ELEMENT-NODE @2123>
;;;
;;; > (xml-node-new-child * "element2" "The contents of element2")
;;; #<XML-NODE type=XML-ELEMENT-NODE @2124>
;;;
;;; > (xml-write-file (@ 2121) "/home/ajs/xml/test-output.xml")
;;; 102
;;;
;;; Note that all strings that are results are widestrings.
 
;;;; DOM Lisp bindings 

;;;; xml-structure
;;;
;;; All XML data is stored in C structures that are managed
;;; by libXML.
;;;
;;; The xml-structure in Lisp has a single
;;; slot native-pointer which contains the G2pointer that
;;; can be used in the C code to decache the underlying libXML
;;; C structure.
;;;

(def-structure xml-structure 
  (native-pointer nil))

(def-gensym-c-function c-xml-dispose-pointer
     (:void "g2xml_dispose_pointer")
  ((:pointer native-pointer)))




;;;; xml-structures-extent

;;; The xml-structures-extent is used to do automatic
;;; reclamation of xml-structures in a defined scope.
;;;
;;; The xml-structures-extent is used by the macro
;;; reclaiming-xml-structures which is defined below.
;;;
;;; All xml-structures are actually just a

(def-named-dynamic-extent xml-structures-extent
  (module dom)
  (unwind? nil))

;;; The `current-xml-structures' variable is used in the xml-structures-extent
;;; to keep a track of the list of xml-structures that have been
;;; allocated in that extent.

(defvar-of-named-dynamic-extent current-xml-structures xml-structures-extent) 

;;; `add-xml-structure-to-current-xml-structures' appends to the current-xml-structures
;;; dynamically scoped variable an structure.  If this function is called
;;; outside of the xml-structures-extent then it will do nothing.

(defun add-xml-structure-to-current-xml-structures (xml-structure)
  (when (boundp 'current-xml-structures)
    (setf current-xml-structures
	  (nconc current-xml-structures (gensym-list xml-structure)))))

  
;;;; XML Nodes

;;; The xml-node structure is used to represent all the DOM nodes in an
;;; xml document.

(def-structure (xml-node
		 (:include xml-structure)
		 (:reclaimer reclaim-xml-node-internal)
		 (:print-function print-xml-node)))

;;; The xml-node structure is used to represent a list of xml-nodes
;;; (usually either a list of child nodes or attributes).

(def-structure (xml-node-list
		 (:include xml-structure)
		 (:reclaimer reclaim-xml-node-list-internal)
		 (:print-function print-xml-node-list)))


;;; Create a new xml-node from a G2pointer

(defun create-xml-node (native-pointer)
  (let ((result
	 (make-xml-node)))
    (setf (native-pointer result) native-pointer)
    (add-xml-structure-to-current-xml-structures result)
    result))

;;; Create a new xml-node list from a G2pointer

(defun create-xml-node-list (native-pointer)
  (let ((result
	 (make-xml-node-list)))
    (setf (native-pointer result) native-pointer)
    (add-xml-structure-to-current-xml-structures result)
    result))


;;; Native function for disposing an xml-document.  Note that this
;;; will actually dispose of all the structures in the tree of the
;;; document internally so this should generally not be called if
;;; you are intending to continue to use any node which was retrieved
;;; from the document.

(def-gensym-c-function c-xml-dispose-document
     (:void "g2xml_dispose_document")
  ((:pointer doc)))


;;; Native function for getting the type code of an xml-node.
;;; See the Node Types section above for the list of possible type
;;; codes

(def-gensym-c-function c-xml-node-type
    (:fixnum-int "g2xml_node_type")
  ((:pointer node)))   

;;; Reclaim an xml-node.
;;;
;;; If the node is a document this will call c-xml-dispose-document and
;;; it will reclaim all the C structures associated with the document.
;;;
;;; If the node being reclaimed is not a document then this disposes of
;;; the G2pointer and the Lisp structure itself.  It does nothing to the
;;; underlying C structure.

(defun reclaim-xml-node (node)
  (cond ((=f (c-xml-node-type (native-pointer node)) xml-document-node)
	 (c-xml-dispose-document (native-pointer node)))
	(t 
	 (c-xml-dispose-pointer (native-pointer node))))
  (reclaim-xml-node-internal node)
  ;; note: the following nil must be there to avoid chestnut-translated code's
  ;; problem having the returning value of a C void function as the value of a
  ;; general defun.
  nil)


;;; Reclaim an xml-node-list
;;;
;;; This disposes of the G2pointer and the Lisp structure
;;; itself.  It does nothing to the underlying C structure.

(defun reclaim-xml-node-list (node-list)
  (c-xml-dispose-pointer (native-pointer node-list))
  (reclaim-xml-node-list-internal node-list))

;;; Print in short form an xml-node. This includes information about
;;; the type of node.

(defun print-xml-node (xml-node stream depth)
  (declare (ignore depth) (eliminate-for-gsi))
  (let ((node-type-symbol
	  (xml-node-type-symbol xml-node)))
    (printing-random-object (xml-node stream)
      (format stream "XML-NODE type=~a"
	      node-type-symbol))))

;;; Print in short form an xml-node-list. This includes the
;;; length of the node-list.

(defun print-xml-node-list (xml-node-list stream depth)
  (declare (ignore depth) (eliminate-for-gsi))
  (let ((node-list-length
	  (xml-node-list-length xml-node-list)))
    (printing-random-object (xml-node-list stream)
      (format stream "XML-NODE-LIST length=~a"
        node-list-length))))


;;;; String handling.

;;; All strings that are retrieved from C code are filled in
;;; by:
;;; - asking the size of the string by calling a C function;
;;; - allocating a simple gensym string for that size;
;;; - Filling the simple string by calling a C function;
;;; - copying the simple gensym string into a wide string
;;; - reclaiming the old string
;;;
;;; If the size function returns a negative number this will return nil.

(defmacro dom-fill-in-string-buffer-from-native-pointer
    (size-function
      fill-in-function
      native-pointer
      &rest args)
  `(let* ((true-size-required
	    (funcall #',size-function ,native-pointer ,@args))
	  (size-to-use
	    (minf true-size-required maximum-length-for-sax-strings)))
     (cond ((>=f size-to-use 0)
	    (let ((string-buffer
		    (obtain-simple-gensym-string size-to-use))
		  (wide-string-value nil))
	      (funcall #',fill-in-function ,native-pointer
		       ,@args string-buffer size-to-use 0)
	      (setq wide-string-value (import-text-string string-buffer 'utf-8-string))
	      (reclaim-simple-gensym-string string-buffer)
	      wide-string-value)))))
	      
(defmacro dom-fill-in-string-buffer
    (size-function
      fill-in-function
      xml-structure
      &rest args)
  `(dom-fill-in-string-buffer-from-native-pointer
     ,size-function ,fill-in-function (native-pointer ,xml-structure) ,@args))


;;;; XML Namespaces
;;;

;;; The xml-namespace structure is used to represent
;;; an individual xml-namespace

(def-structure (xml-namespace
		 (:include xml-structure)
		 (:reclaimer reclaim-xml-namespace-internal)))

;;; The xml-namespace-list structure is used to represent
;;; a list of xml-namespaces.

(def-structure (xml-namespace-list
		 (:include xml-structure)
		 (:reclaimer reclaim-xml-namespace-list-internal)
		 (:print-function print-xml-namespace-list)))

;;; Create a new xml-namespace from a G2pointer

(defun create-xml-namespace (native-pointer)
  (let ((result
	 (make-xml-namespace)))
    (setf (native-pointer result) native-pointer)
    (add-xml-structure-to-current-xml-structures result)
    result))

;;; Reclaim an xml-namespace.
;;;
;;; This disposes of the G2pointer and the Lisp structure
;;; itself.  It does nothing to the underlying C structure.

(defun reclaim-xml-namespace (xml-namespace)
  (c-xml-dispose-pointer (native-pointer xml-namespace))
  (reclaim-xml-namespace-internal xml-namespace))

;;; Create a new xml-namespace-list from a G2pointer

(defun create-xml-namespace-list (native-pointer)
  (let ((result
	 (make-xml-namespace-list)))
    (setf (native-pointer result) native-pointer)
    (add-xml-structure-to-current-xml-structures result)
    result))

;;; Reclaim an xml-namespace-list
;;;
;;; This disposes of the G2pointer and the Lisp structure
;;; itself.  It does nothing to the underlying C structure.

(defun reclaim-xml-namespace-list (xml-namespace)
  (c-xml-dispose-pointer (native-pointer xml-namespace))
  (reclaim-xml-namespace-list-internal xml-namespace))


;;; Print in short form an xml-namespace-list. This includes the
;;; length of the node-list.

(defun print-xml-namespace-list (xml-namespace-list stream depth)
  (declare (ignore depth) (eliminate-for-gsi))
  (let ((namespace-list-length
	  (xml-namespace-list-length xml-namespace-list)))
    (printing-random-object (xml-namespace-list stream)
      (format stream "XML-NAMESPACE-LIST length=~a"
        namespace-list-length))))


;;;; Memory Management Utilities
;;;

;;; Reclaim a list of xml-structures.  Does not reclaim the
;;; list itself
;;;
;;; The ignore-documents option which is nil by default will
;;; cause this function to skip over documents when it is
;;; reclaiming xml-structures.

(defun reclaim-xml-structures (xml-structures &optional (ignore-documents nil))
  (loop for xml-structure in xml-structures
	with xml-documents = nil
	do
    (cond ((xml-node-p xml-structure)
	   (if (=f (c-xml-node-type (native-pointer xml-structure))
		   xml-document-node)
	       (unless ignore-documents
		 (gensym-push xml-structure xml-documents))
	       (reclaim-xml-node xml-structure)))
	  ((xml-node-list-p xml-structure)
	   (reclaim-xml-node-list xml-structure))
	  ((xml-namespace-p xml-structure)
	   (reclaim-xml-namespace xml-structure))
	  ((xml-namespace-list-p xml-structure)
	   (reclaim-xml-namespace-list xml-structure))
	  (t
	   #+development
	   (cerror "Continue" "Attempt to reclaim unknown xml structure: ~A"
		   xml-structure)))
	finally
	  ;; Reclaim documents last, since that reclaims all the underlying C
	  ;; structures.
	  (loop for doc in xml-documents do (reclaim-xml-node doc))
	  (reclaim-gensym-list xml-documents)))

;;; `reclaiming-xml-structures'
;;;
;;; A scope in which all xml-node, xml-node-list, xml-namespace
;;; and xml-namespace-list structures are reclaimed automatically
;;;
;;; This is very useful when working with functions in the DOM
;;; module because calling functions causes the DOM module to create
;;; xml structures frequently.

(defmacro reclaiming-xml-structures (&body forms)
  `(with-named-dynamic-extent xml-structures-extent
       ((current-xml-structures (gensym-list)))
     (multiple-value-prog1
	 (progn ,@forms)
       (reclaim-xml-structures current-xml-structures)
       (reclaim-gensym-list current-xml-structures))))

;;; Use the reclaiming-xml-structures-except-documents
;;; instead of reclaiming-xml-structures if you wish any
;;; document nodes not to not be reclaimed.

(defmacro reclaiming-xml-structures-except-documents (&body forms)
  `(with-named-dynamic-extent xml-structures-extent
       ((current-xml-structures (gensym-list)))
     (multiple-value-prog1
	 (progn ,@forms)
       (reclaim-xml-structures current-xml-structures t)
       (reclaim-gensym-list current-xml-structures))))

;;;; Parsing Functions

;;; Note that the parsing utilities are quite primitive right now.
;;; Parsing from buffers and streams are not yet supported and
;;; validation is not yet supported.

;;; Native function for parsing an XML file

(def-gensym-c-function c-xml-read-file
     (:pointer "g2xml_read_file")
  ((:string path)))

;;; Read an XML document from a file.

(defun xml-read-file (path)
  (let ((native-pointer
	  (c-xml-read-file path)))
    (cond ((>=f native-pointer 0)
	   (create-xml-node native-pointer)))))


;;; Read an XML document from a text string.

(def-gensym-c-function c-xml-read-string
    (:pointer "g2xml_read_string")
  ((:string string)
   (:fixnum-int len)))

(defun xml-read-string (text-string)
  (let ((native-pointer
	  (c-xml-read-string text-string (text-string-length text-string))))
    (when (>=f native-pointer 0)
      (create-xml-node native-pointer))))

;;; The function `xml-read-string-or-stack-error' reads an XML document from a
;;; text string, raising a stack error if parse errors are encountered.

(defun-simple xml-read-string-or-stack-error (text-string)
  (let ((document (xml-read-string text-string)))
    (or document
	(let ((errors (xml-get-errors)))
	  (write-stack-error cached-top-of-stack
	    (loop for error in errors do (twrite-string error))
	    (reclaim-gensym-tree-with-text-strings errors))))))


(def-gensym-c-function c-xml-next-error
    (:pointer "g2xml_next_error")
  ())

(def-gensym-c-function c-xml-error-get-message-size
    (:fixnum-int "g2xml_error_get_message_size")
  ((:pointer error)))

(def-gensym-c-function c-xml-error-get-message-in-buffer
    (:void "g2xml_error_get_message_in_buffer")
  ((:pointer error)
   (:string buffer)
   (:fixnum-int size)
   (:fixnum-int start)))

(def-gensym-c-function c-xml-error-get-filename-size
    (:fixnum-int "g2xml_error_get_filename_size")
  ((:pointer error)))

(def-gensym-c-function c-xml-error-get-filename-in-buffer
    (:void "g2xml_error_get_filename_in_buffer")
  ((:pointer error)
   (:string buffer)
   (:fixnum-int size)
   (:fixnum-int start)))

(def-gensym-c-function c-xml-error-get-line-number
    (:fixnum-int "g2xml_error_get_line_number")
  ((:pointer error)))

(def-gensym-c-function c-xml-error-get-column-number
    (:fixnum-int "g2xml_error_get_column_number")
  ((:pointer error)))

(def-gensym-c-function c-xml-dispose-error
    (:void "g2xml_dispose_error")
  ((:pointer error)))


;;; Collect warnings and errors from the most recent parse into a gensym list of
;;; text strings.

(defun xml-get-errors ()
  (loop for error = (c-xml-next-error)
	while (>=f error 0)
	collect (twith-output-to-text-string (twrite-xml-error error))
	  using gensym-cons
	do (c-xml-dispose-error error)))

(defun twrite-xml-error (error)
  (let ((message (dom-fill-in-string-buffer-from-native-pointer
		   c-xml-error-get-message-size
		   c-xml-error-get-message-in-buffer
		   error)))
    (when message
      (let ((filename (dom-fill-in-string-buffer-from-native-pointer
			c-xml-error-get-filename-size
			c-xml-error-get-filename-in-buffer
			error))
	    (line-number (c-xml-error-get-line-number error))
	    (column-number (c-xml-error-get-column-number error)))
	(cond (filename
	       (tformat "~a:~a:" filename line-number)
	       (reclaim-text-string filename))
	      (t
	       (tformat "Line ~a:" line-number)))
	(when (>=f column-number 0)
	  (tformat "~a:" column-number))
	(tformat " ~a" message)
	(reclaim-text-string message)))))


;;; Native functions for writing XML documents.

(def-gensym-c-function c-xml-write-file
     (:fixnum-int "g2xml_write_file")
  ((:pointer document)
   (:string path)))

(def-gensym-c-function c-xml-write-buffer
    (:pointer "g2xml_write_buffer")
  ((:pointer document)))

(def-gensym-c-function c-xml-buffer-get-content-size
    (:fixnum-int "g2xml_buffer_get_content_size")
  ((:pointer xml-buffer)))

(def-gensym-c-function c-xml-buffer-get-content-in-buffer
    (:void "g2xml_buffer_get_content_in_buffer")
  ((:pointer xml-buffer)
   (:string buffer)
   (:fixnum-int size)
   (:fixnum-int start)))

(def-gensym-c-function c-xml-dispose-buffer
    (:void "g2xml_dispose_buffer")
  ((:pointer xml-buffer)))


;;; Pretty-print an XML document to a file.

(defun xml-write-file (document path)
  (c-xml-write-file (native-pointer document) path))

;;; Pretty-print an XML document to a text string.

(defun xml-write-text-string (document)
  (let ((buffer (c-xml-write-buffer (native-pointer document))))
    (prog1 (dom-fill-in-string-buffer-from-native-pointer
	     c-xml-buffer-get-content-size
	     c-xml-buffer-get-content-in-buffer
	     buffer)
      (c-xml-dispose-buffer buffer))))



;;;; XML name conversion

;;; The functions below convert between XML names (e.g. element names and
;;; attribute names) and G2 symbols.  Because both XML names and G2 symbols may
;;; be created arbitrarily outside of this conversion process, the conversion
;;; needs to be a bijection (one-to-one and onto): every XML name must
;;; correspond to a unique G2 symbol and vice versa.
;;; 
;;; XML names are case-sensitive.  G2 symbols are sort of case-insensitive:
;;; letters are converted to uppercase when creating a symbol, but you can quote
;;; lowercase letters (with at-signs) to preserve them.  In other words,
;;; the symbol foo = the symbol FOO, but the symbol foo != the symbol @f@o@o.
;;;
;;; When converting XML names to G2 symbols, we could just preserve lowercase
;;; letters by quoting them, but it's kind of a pain (and ugly) to refer to
;;; symbols with lots of at-signs in them.  So instead we convert lowercase
;;; letters in the XML name to uppercase letters in the G2 symbol, and remember
;;; uppercase letters in the XML name by inserting hyphens before them in the G2
;;; symbol:
;;;
;;;   foobar -> FOOBAR
;;;   fooBar -> FOO-BAR
;;;   FooBar -> -FOO-BAR
;;;   FOOBAR -> -F-O-O-B-A-R
;;;
;;; For uppercase XML names, this isn't any better than using at-signs to quote
;;; lowercase letters, but XML names are more likely to be lowercase or
;;; mixedCase than Capitalized or UPPERCASE so it's generally better to do it
;;; this way.  In particular, this gives a natural mapping between the usual
;;; mixedCase convention and the hyphenated-name convention in G2 (and Lisp).
;;;
;;; In order to make this a one-to-one mapping, however, we need to do something
;;; about hyphens in the XML name, otherwise both fooBar and foo-bar will be
;;; converted to FOO-BAR.  To solve this, we convert each hyphen into a
;;; double-hyphen:
;;;
;;;   foo-bar  -> FOO--BAR
;;;   foo-Bar  -> FOO---BAR
;;;   foo--bar -> FOO----BAR
;;;   foo--Bar -> FOO-----BAR
;;;
;;; We still have a problem, though: this mapping is one-to-one, but not onto.
;;; There are three classes of G2 symbols that are not covered by this mapping:
;;;
;;; 1. Symbols containing trailing hyphens, or hyphens before non-alphabetic
;;;    characters: FOO--, FOO-123
;;; 2. Symbols containing lowercase letters: F@o@o-B@a@r
;;; 3. Symbols which are invalid XML names.  An XML name must start with a
;;;    letter, underscore, or colon, and may only contain letters, digits,
;;;    periods, hyphens, underscores, and colons (as well as Unicode extenders
;;;    and combining characters, such as diacritics).  In addition, colons are
;;;    reserved for separating a namespace prefix from a local name, so we
;;;    should consider them invalid as well.  In other words, "XML name"
;;;    corresponds to "NCName" in the XML namespaces specification:
;;;    http://www.w3.org/TR/REC-xml-names/
;;;
;;; We can solve the first case by only converting hyphens to double-hyphens
;;; if they precede a letter, and otherwise leaving them alone:
;;;
;;;   foo-     -> FOO-
;;;   foo---   -> FOO---
;;;   foo-123  -> FOO-123
;;;   foo--123 -> FOO--123
;;;
;;; For now I'm going to punt on the second and third cases.  I don't see an
;;; easy solution.  It might be best to simply regard these situations as
;;; errors, i.e. you're just not allowed to convert a G2 symbol containing a
;;; lowercase letter or an invalid NCName character into an XML name.
;;;
;;; In the meantime, I think it's okay to just do nothing special for these
;;; cases: lowercase letters and invalid NCName characters in a G2 symbol just
;;; stay that way when converted to an XML name.  This will either result in a
;;; name mismatch, when a lowercase letter turns into uppercase after a round
;;; trip from G2 symbol to an XML name and back to a G2 symbol, or an XML parse
;;; error, when an invalid XML name appears in an exported XML document.  Either
;;; way, it will be clear that something went wrong, so this is basically
;;; equivalent to regarding these cases as errors, but of course it would be
;;; better to signal that up front.  But right now it's not clear to me whether
;;; that should be the responsibility of these low-level functions or their
;;; higher-level callers.  -dougo, 2/23/06


;;; The macro `twrite-hyphens' twrites 0 or more hyphens.

(defmacro twrite-hyphens (n)
  `(loop for i below ,n do (twrite-char #\-)))


;;; The function `convert-xml-name-to-symbol' converts an XML name text string
;;; to a G2 symbol.  In addition to the conversion rules discussed above, the
;;; text-string "nil" is converted to :NIL, because NIL is not a G2 symbol.  The
;;; argument may also just be NIL, in which case NIL is returned.

(defun convert-xml-name-to-symbol (xml-name-text-string?)
  (unless xml-name-text-string?
    (return-from convert-xml-name-to-symbol nil))
  (let ((symbol-text-string
	  (twith-output-to-text-string
	    (loop with num-hyphens = 0
		  for i below (text-string-length xml-name-text-string?)
		  for char = (charw xml-name-text-string? i)
		  when (char=w char #.%\-) do (incff num-hyphens)
		  else do (cond
			    ((unicode-uppercase-p (wide-character-code char))
			     (twrite-hyphens (1+f (twicef num-hyphens)))
			     (twrite-char char))
			    ((unicode-lowercase-p (wide-character-code char))
			     (twrite-hyphens (twicef num-hyphens))
			     (twrite-char (char-upcasew char)))
			    (t
			     (twrite-hyphens num-hyphens)
			     (twrite-char char)))
			  (setq num-hyphens 0)
		  finally (twrite-hyphens num-hyphens)))))
    (or (intern-text-string symbol-text-string)
	:nil)))

(defun convert-xml-name-to-symbol-and-reclaim (name)
  (prog1 (convert-xml-name-to-symbol name)
    (when name (reclaim-text-string name))))



;;; The function `convert-symbol-to-xml-name' converts a G2 symbol (or NIL) to
;;; an XML name text string (newly allocated).  This is the inverse of
;;; `convert-xml-name-to-symbol', with the exceptions noted in the discussion
;;; above, and also both NIL and :NIL are converted to "nil".

(defun convert-symbol-to-xml-name (symbol)
  (twith-output-to-text-string
    (loop with symbol-text-string = (symbol-name-text-string symbol)
	  with num-hyphens = 0
	  for i below (text-string-length symbol-text-string)
	  for char = (charw symbol-text-string i)
	  when (char=w char #.%\-) do (incff num-hyphens)
	  else do (cond ((or (unicode-uppercase-p (wide-character-code char))
			     (unicode-lowercase-p (wide-character-code char)))
			 (twrite-hyphens (halff num-hyphens))
			 (if (oddp num-hyphens)
			     (twrite-char char)
			     (twrite-char (char-downcasew char))))
			(t
			 (twrite-hyphens num-hyphens)
			 (twrite-char char)))
		  (setq num-hyphens 0)
	  finally (twrite-hyphens num-hyphens))))


;;; Convert a whitespace-separated string of XML names to a slot-value list of
;;; symbols (using the hyphen replacement rules above).

(defun convert-xml-names-to-symbols (names-string)
  (when names-string
    (loop with names = (parse-text-line-into-list-of-text-strings
			 names-string
			 whitespace-wide-characters
			 whitespace-wide-characters)
	  for name in names
	  collect (convert-xml-name-to-symbol-and-reclaim name)
	    using slot-value-cons
	  finally (reclaim-gensym-list names))))

(defun convert-xml-names-to-symbols-and-reclaim (names)
  (prog1 (convert-xml-names-to-symbols names)
    (when names (reclaim-text-string names))))


;;; The macro `xml-node-name-symbol-case' is a two-level case statement that
;;; first matches on the namespace URI of an XML node to a text string (or nil),
;;; then the local name to a symbol.  As in a regular case statement, the test
;;; condition of each clause can be a list or t or OTHERWISE.  Note that the
;;; namespaces in each clause are evaluated as expressions, while the local
;;; names must be literal symbols.  For example:
;;;
;;;   (xml-node-name-symbol-case node
;;;     (bpel-xml-namespace-uri
;;;       ((catch catch-all) ...)
;;;       (compensation-handler ...)
;;;       (t ...))
;;;     ((xsd-datatypes-xml-namespace-uri #w"http://www.w3.org/2001/XMLSchema")
;;;       (string ...))
;;;     (nil                 ; no namespace URI
;;;       (comment ...)))    ; xml-node-type-symbol = XML-COMMENT-NODE

(defmacro xml-node-name-symbol-case (node &body clauses)
  (let ((local-name (gensym))
	(prefix (gensym))
	(ns-uri (gensym)))
  `(multiple-value-bind (,local-name ,prefix ,ns-uri)
       (xml-node-name-symbols ,node)
     (declare (ignore ,prefix))
     (multiple-value-prog1
	 (cond
	   ,@(loop for clause in clauses
		   for uri-or-uris = (car clause)
		   for body = `(case ,local-name
				 ,@(cdr clause))
		   collect (cond ((not (atom uri-or-uris))
				  `((or ,@(loop for uri in uri-or-uris collect
						`(equalw ,ns-uri ,uri)))
				    ,body))
				 ((not (memq uri-or-uris '(t otherwise)))
				  `((equalw ,ns-uri ,uri-or-uris)
				    ,body))
				 (t
				  `(t ,body)))))
       (when ,ns-uri
	 (reclaim-text-string ,ns-uri))))))



;;; Convert a list of symbols to a space-separated string of XML names (using
;;; the hyphen replacement rules above).

(defun convert-symbols-to-xml-names (symbols)
  (twith-output-to-text-string
    (loop for symbol in symbols
	  for xml-name = (convert-symbol-to-xml-name symbol)
	  for space-p = nil then t
	  when space-p do (twrite " ")
	  do (twrite xml-name)
	     (reclaim-text-string xml-name))))



;;;; DOM API Functions

;;; Note that this implementation is only a partial implementation of DOM.
;;; Much more work would be added to make this a complete DOM implementation.
;;;
;;; Note that interspersed amongst the DOM functions are some functions
;;; that are specific to LibXML.  These are added for ease of use purposes
;;; because LibXML is often less verbose to use than DOM.
;;;
;;; - ajs 12/12/2004


;;;; xml-node functions


(def-gensym-c-function c-xml-get-line
     (:fixnum-int "g2xml_get_line")
  ((:pointer node)))

(defun xml-node-get-line (node)
  (c-xml-get-line (native-pointer node)))

(def-gensym-c-function c-xml-get-content-size
    (:fixnum-int "g2xml_get_content_size")
  ((:pointer node)))

(def-gensym-c-function c-xml-get-content-in-buffer
    (:void "g2xml_get_content_in_buffer")
  ((:pointer node)
   (:string result)
   (:fixnum-int size)
   (:fixnum-int start)))

(defun xml-node-get-content (node)
  (dom-fill-in-string-buffer c-xml-get-content-size
			     c-xml-get-content-in-buffer
			     node))
  
(defun xml-node-type (xml-node)
  (c-xml-node-type (native-pointer xml-node)))

(defun xml-node-type-symbol (xml-node)
  (case (c-xml-node-type (native-pointer xml-node))
    (#.xml-element-node 'xml-element-node)
    (#.xml-attribute-node 'xml-attribute-node)
    (#.xml-text-node 'xml-text-node)
    (#.xml-cdata-section-node 'xml-cdata-section-node)
    (#.xml-entity-reference-node 'xml-entity-reference-node)
    (#.xml-entity-node 'xml-entity-node)
    (#.xml-processing-instruction-node 'xml-processing-instruction-node)
    (#.xml-comment-node 'xml-comment-node)
    (#.xml-document-node 'xml-document-node)
    (#.xml-document-type-node 'xml-document-type-node)
    (#.xml-document-fragment-node 'xml-document-fragment-node)
    (#.xml-notation-node 'xml-notation-node)))

(defun xml-element-p (xml-node)
  (eq (xml-node-type-symbol xml-node) 'xml-element-node))

(def-gensym-c-function c-xml-node-new-child
    (:pointer "g2xml_node_new_child")
  ((:pointer node)
   (:pointer namespace)
   (:string name)
   (:string value)))


;;; The function `xml-node-new-child' creates a new XML element and returns it.
;;; The new element is added as the last child of the XML node `node' (which
;;; should be an element or document).  The local name of the new element is
;;; `tagname' (a string).  The `namespace' argument is an XML namespace
;;; structure whose namespace prefix will be used for the new element.  If
;;; `namespace' is not provided, the namespace of `node' is inherited.  The
;;; `text-content' argument (a string) is used (if provided) as the text content
;;; of the new element.

(defun xml-node-new-child (node tagname &optional namespace text-content)
  (let ((result-pointer
	  (c-xml-node-new-child
	    (native-pointer node)
	    (if namespace (native-pointer namespace) -1)
	    tagname (or text-content ""))))
    (cond ((>=f result-pointer 0)
	   (create-xml-node result-pointer)))))

(def-gensym-c-function c-xml-node-add-content
    (:void "g2xml_node_add_content")
  ((:pointer node)
   (:string value)))

(defun xml-node-add-content (node textvalue)
  (c-xml-node-add-content
    (native-pointer node)
    textvalue))


;;; Add a new comment node with the given text to the given node.

(def-gensym-c-function c-xml-node-add-comment
    (:void "g2xml_node_add_comment")
  ((:pointer node)
   (:string text)))

(defun xml-node-add-comment (node text)
  (c-xml-node-add-comment (native-pointer node) text))



(def-gensym-c-function c-xml-node-parent-node
    (:pointer "g2xml_node_parent_node")
  ((:pointer node)))

(defun xml-node-parent-node (xml-node)
  (let ((result-pointer
	  (c-xml-node-parent-node (native-pointer xml-node))))
    (cond ((>=f result-pointer 0)
	   (create-xml-node result-pointer)))))	 

(def-gensym-c-function c-xml-node-child-nodes
    (:pointer "g2xml_node_child_nodes")
  ((:pointer node)))

(defun xml-node-child-nodes (xml-node)
    (let ((result-pointer
	    (c-xml-node-child-nodes (native-pointer xml-node))))
    (cond ((>=f result-pointer 0)
	   (create-xml-node-list result-pointer)))))

(defun xml-node-first-child (xml-node)
  (let ((result-pointer
	  (c-xml-node-child-nodes (native-pointer xml-node))))
    (cond ((>=f result-pointer 0)
	   (create-xml-node result-pointer)))))

(def-gensym-c-function c-xml-node-last-child
    (:pointer "g2xml_node_last_child")
  ((:pointer node)))

(defun xml-node-last-child (xml-node)
  (let ((result-pointer
	  (c-xml-node-last-child (native-pointer xml-node))))
    (cond ((>=f result-pointer 0)
	   (create-xml-node result-pointer)))))


;;; Get the first child element of a node whose local name and namespace URI are
;;; equal to the given text strings, or nil if there is no such child.

(defun xml-node-get-child-by-name (node local-name &optional ns-uri)
  (xml-node-list-item-by-name (xml-node-child-nodes node) local-name ns-uri))

;;; Get a node's child whose local name is a symbol.

(defun xml-node-get-child-by-name-symbol (node name &optional ns-uri)
  (let ((name-string (convert-symbol-to-xml-name name)))
    (prog1 (xml-node-get-child-by-name node name-string ns-uri)
      (reclaim-text-string name-string))))


(def-gensym-c-function c-xml-node-previous-sibling
    (:pointer "g2xml_node_previous_sibling")
  ((:pointer node)))

(defun xml-node-previous-sibling (xml-node)
  (let ((result-pointer
	  (c-xml-node-previous-sibling (native-pointer xml-node))))
    (cond ((>=f result-pointer 0)
	   (create-xml-node result-pointer)))))

(def-gensym-c-function c-xml-node-next-sibling
    (:pointer "g2xml_node_next_sibling")
  ((:pointer node)))

(defun xml-node-next-sibling (xml-node)
  (let ((result-pointer
	  (c-xml-node-next-sibling (native-pointer xml-node))))
    (cond ((>=f result-pointer 0)
	   (create-xml-node result-pointer)))))

(def-gensym-c-function c-xml-node-attributes
    (:pointer "g2xml_node_attributes")
  ((:pointer node)))

(defun xml-node-attributes (xml-node)
  (let ((result-pointer
	  (c-xml-node-attributes (native-pointer xml-node))))
    (cond ((>=f result-pointer 0)
	   (create-xml-node-list result-pointer)))))


(def-gensym-c-function c-xml-node-namespace
    (:pointer "g2xml_node_namespace")
  ((:pointer node)))
   
(defun xml-node-namespace (xml-node)
  (let ((result-pointer
	  (c-xml-node-namespace
	    (native-pointer xml-node))))
    (cond ((>=f result-pointer 0)
	   (create-xml-namespace result-pointer)))))


(def-gensym-c-function c-xml-node-set-namespace
    (:void "g2xml_node_set_namespace")
  ((:pointer node)
   (:pointer namespace)))

;;; Set or remove the namespace of a node.

(defun xml-node-set-namespace (xml-node xml-namespace?)
  (c-xml-node-set-namespace
    (native-pointer xml-node)
    (if xml-namespace? (native-pointer xml-namespace?) -1))
  nil)


;;; The namespace URI of an XML node as a text string, or nil if the node has no
;;; namespace assignment.

(defun xml-node-namespace-uri (node)
  (let ((namespace (xml-node-namespace node)))
    (when namespace
      (xml-namespace-get-uri namespace))))


;;; Is the namespace URI of an XML node equal to a text string, or nil if ns-uri
;;; is nil?

(defun xml-node-namespace-uri-equals-p (node ns-uri)
  (let ((ns-uri-of-node (xml-node-namespace-uri node)))
    (prog1 (equalw ns-uri ns-uri-of-node)
      (when ns-uri-of-node
	(reclaim-text-string ns-uri-of-node)))))


;;; The local name of an XML node, or nil if it has no name (e.g. if it is not
;;; an element or attribute).  The local name is not the same as an element tag
;;; name or an attribute name; in particular, the namespace prefix is not
;;; included, i.e., it is an NCName.

(defun xml-node-local-name (node)
  (dom-fill-in-string-buffer
    c-xml-node-local-name-size
    c-xml-node-local-name-in-buffer
    node))

(def-gensym-c-function c-xml-node-local-name-size
    (:fixnum-int "g2xml_node_local_name_size")
  ((:pointer node)))

(def-gensym-c-function c-xml-node-local-name-in-buffer
    (:void "g2xml_node_local_name_in_buffer")
  ((:pointer node)
   (:string buffer)
   (:fixnum-int size)
   (:fixnum-int start)))


(defun xml-node-local-name-symbol (node)
  (convert-xml-name-to-symbol-and-reclaim
    (xml-node-local-name node)))



;;; Is the local name of an XML node equal to a given text string?

(defun xml-node-local-name-equals-p (node local-name)
  (let ((local-name-of-node (xml-node-local-name node)))
    (prog1 (equalw local-name local-name-of-node)
      (when local-name-of-node
	(reclaim-text-string local-name-of-node)))))


;;; The namespace prefix of an XML node as a text string, or nil if the node has
;;; no name, e.g. if the node is not an element or attribute, or if the node
;;; name has no prefix, e.g. if the node is an element in the default namespace
;;; or is a local attribute.

(defun xml-node-prefix (node)
  (let ((namespace (xml-node-namespace node)))
    (when namespace
      (xml-namespace-get-prefix namespace))))


;;; The name of an XML node consists of its local name, prefix, and namespace
;;; URI (returned as multiple text-string values).  The local name is nil if the
;;; node has no name, e.g. if the node is not an element or attribute.  The
;;; prefix is nil if the node name has no prefix, e.g. if the node has no name
;;; or is an element in the default namespace or is a local attribute.  The
;;; namespace URI is nil if the prefix is nil and there is no default namespace,
;;; or if the prefix is not defined (or has been undefined) in the scope of the
;;; node.

;; The current version of libxml2 does not support undefining a prefix
;; (i.e. xmlns:foo=""), nor does it keep around undefined prefixes.  In both
;; cases, both the prefix and namespace URI will be nil.  -dougo, 5/17/05

(defun xml-node-name (node)
  (values (xml-node-local-name node)
	  (xml-node-prefix node)
	  (xml-node-namespace-uri node)))

(defun xml-node-name-symbols (node)
  (multiple-value-bind (local-name prefix ns-uri)
      (xml-node-name node)
    (values (convert-xml-name-to-symbol-and-reclaim local-name)
	    (convert-xml-name-to-symbol-and-reclaim prefix)
	    ns-uri)))


;;; Are the local name and namespace URI of an XML node equal to the given
;;; text strings?  Or, if ns-uri is nil or not provided, does the node have no
;;; namespace assignment?  (Note that the prefix of the node is ignored.)

(defun xml-node-name-equals-p (node local-name &optional ns-uri)
  (and (xml-node-namespace-uri-equals-p node ns-uri)
       (xml-node-local-name-equals-p node local-name)))

;;; Compare a node's local name to a symbol.

(defun xml-node-name-symbol-equals-p (node name &optional ns-uri)
  (let ((name-string (convert-symbol-to-xml-name name)))
    (prog1 (xml-node-name-equals-p node name-string ns-uri)
      (reclaim-text-string name-string))))


(def-gensym-c-function c-xml-node-lookup-namespace
    (:pointer "g2xml_node_lookup_namespace")
  ((:pointer node)
   (:string prefix)))

;;; Lookup the namespace associated with the given prefix starting at the given
;;; node and going up its parent hierarchy.  Use a null prefix to find the
;;; default namespace.

(defun xml-node-lookup-namespace (xml-node prefix?)
  (let ((result-pointer
	  (c-xml-node-lookup-namespace
	    (native-pointer xml-node) (or prefix? ""))))
    (when (>=f result-pointer 0)
      (create-xml-namespace result-pointer))))


;;; Lookup a namespace by prefix symbol.

(defun xml-node-lookup-namespace-symbol (node prefix?)
  (let ((prefix-string? (convert-symbol-to-xml-name prefix?)))
    (prog1 (xml-node-lookup-namespace node prefix-string?)
      (when prefix-string? (reclaim-text-string prefix-string?)))))


;;; Expand a qualified name into a local name and a prefix (returned as
;;; multiple values).  If the prefix is nil, the local name is the qualified
;;; name, otherwise the qualified name is reclaimed.

(defun xml-qname-expand (qname)
  (let ((colon-pos? (position-in-text-string #.%\: qname)))
    (if colon-pos?
	(multiple-value-prog1
	    (values (text-string-substring qname (1+f colon-pos?) nil)
		    (text-string-substring qname 0 colon-pos?))
	  (reclaim-text-string qname))
	(values qname nil))))

;;; Expand a qualified name into a local name, prefix, and namespace (returned
;;; as multiple values), using the namespace declarations whose scopes include
;;; the given node.  The namespace is nil if the namespace is not found.  If the
;;; prefix is nil, the local name is the qualified name, otherwise the qualified
;;; name is reclaimed.

(defun xml-node-expand-qname (node qname)
  (multiple-value-bind (local-name prefix?) (xml-qname-expand qname)
    (values local-name prefix? (xml-node-lookup-namespace node prefix?))))

(defun xml-node-expand-qname-symbols (node qname)
  (multiple-value-bind (local-name prefix? namespace?)
      (xml-node-expand-qname node qname)
    (values (convert-xml-name-to-symbol-and-reclaim local-name)
	    (convert-xml-name-to-symbol-and-reclaim prefix?)
	    namespace?)))


(def-gensym-c-function c-xml-node-has-child-nodes-p
    (:fixnum-int "g2xml_node_has_child_nodes_p")
  ((:pointer node)))

(defun xml-node-has-child-nodes-p  (xml-node)
  (/=f (c-xml-node-has-child-nodes-p (native-pointer xml-node)) 0))

(def-gensym-c-function c-xml-node-has-attributes-p
    (:fixnum-int "g2xml_node_has_attributes_p")
  ((:pointer node)))

(defun xml-node-has-attributes-p (xml-node)
  (/=f (c-xml-node-has-attributes-p (native-pointer xml-node)) 0))


;;;; xml-node-list functions

(def-gensym-c-function c-xml-node-list-length 
    (:fixnum-int "g2xml_node_list_length")
  ((:pointer xml-node-list)))

(defun xml-node-list-length (xml-node-list)
  (c-xml-node-list-length (native-pointer xml-node-list)))


(def-gensym-c-function c-xml-node-list-item 
    (:pointer "g2xml_node_list_item")
  ((:pointer xml-node-list)
   (:fixnum-int index)))

(defun xml-node-list-item (xml-node-list index)
  (let ((result-pointer
	  (c-xml-node-list-item
	    (native-pointer xml-node-list)
	    index)))
    (cond ((>=f result-pointer 0)
	   (create-xml-node result-pointer)))))


;;; This allows loop expressions of the form
;;;   (loop for x being each [xml-node | xml-element] of y ...)
;;; where y is an xml-node-list (or nil).

(define-loop-path (xml-node xml-element) xml-node-list-path (of))


;;; This will turn loops of the form
;;;   (loop for x being each xml-node of y do body ...)
;;; into something like
;;;   (let ((x nil) (list y))
;;;     (loop-tagbody (when (not list) (go end-loop))
;;;                   (setq x (xml-node-list-item list 0))
;;;                  next-loop
;;;                   (when (not x) (go end-loop))
;;;                   body ...
;;;                   (setq x (xml-node-next-sibling next))
;;;                   (go next-loop)
;;;                  end-loop))
;;; If the path name is xml-element instead of xml-node, non-element nodes will
;;; be skipped.

(defun-for-macro xml-node-list-path
    (path-name var data-type? prep-phrases inclusive-p preps data)
  (declare (ignore data-type? inclusive-p preps data))
  (let* ((elements-only-p (eq path-name 'xml-element))
	 (list (loop-gentemp 'list-))
	 (first `(xml-node-list-item ,list 0))
	 (next `(xml-node-next-sibling ,var)))
    `(;init-bindings
      ((,var nil) (,list ,(second (assq 'of prep-phrases))))
      ;prologue-forms
      nil
      ;pre-step-tests
      nil
      ;steppings
      (,var ,(if elements-only-p (xml-node-to-element next) next))
      ;post-step-tests
      (not ,var)
      ;post-step-settings
      nil
      ;prologue-pre-step-tests
      (not ,list)
      ;prologue-steppings
      (,var ,(if elements-only-p (xml-node-to-element first) first))
      ;prologue-post-step-tetss
      (not ,var)
      ;prologue-post-step-settings
      nil
      )))

(defun-for-macro xml-node-to-element (node)
  (let ((var (loop-gentemp 'node-)))
    `(loop for ,var = ,node then (xml-node-next-sibling ,var)
	   while ,var until (xml-element-p ,var)
	   finally (return ,var))))


;;; Get the first node of a node list whose local name and namespace URI are
;;; equal to the given text strings, or nil if there is no such node.

(defun xml-node-list-item-by-name (node-list local-name &optional ns-uri)
  (loop for node being each xml-node of node-list
	when (xml-node-name-equals-p node local-name ns-uri)
	  return node))



;;;; xml-document functions

(def-gensym-c-function c-xml-create-document
    (:pointer "g2xml_create_document")
  ())

(defun xml-create-document ()
  (let ((result-pointer
	  (c-xml-create-document)))
    (cond ((>=f result-pointer 0)
	   (create-xml-node result-pointer)))))

(defun xml-document-root-element (xml-document)
  ;; Return the first child that is an element.
  (loop for child being each xml-element of
	(xml-node-child-nodes xml-document)
	return child))


;;; Validate an XML document using an XML Schema document.

(def-gensym-c-function c-xml-document-validate
    (:fixnum-int "g2xml_document_validate")
  ((:pointer document)
   (:pointer schema-document)))

(defun xml-document-is-valid-p (xml-document xml-schema-document)
  (=f 0 (c-xml-document-validate
	  (native-pointer xml-document)
	  (native-pointer xml-schema-document))))

(defun-for-system-procedure xml-validate-file (path-to-file)
  (let ((xml-doc (xml-read-file path-to-file)))
      (if (xml-validate-document xml-doc)
        (make-evaluation-truth-value truth)
        (make-evaluation-truth-value falsity))))
      
(defun-for-system-procedure xml-validate-text (document-text)
  (let ((xml-doc (xml-read-string document-text)))
      (if (xml-validate-document xml-doc)
        (make-evaluation-truth-value truth)
        (make-evaluation-truth-value falsity))))

(defun-for-system-procedure xml-validate-file2 (path-to-file path-to-schema)
  (let ((xml-doc (xml-read-file path-to-file))
        (schema-doc (xml-read-file path-to-schema)))
      (if (xml-validate-document2 xml-doc schema-doc)
        (make-evaluation-truth-value truth)
        (make-evaluation-truth-value falsity))))
      
(defun-for-system-procedure xml-validate-text2 (document-text schema-text)
  (let ((xml-doc (xml-read-string document-text))
        (schema-doc (xml-read-string schema-text)))
      (if (xml-validate-document2 xml-doc schema-doc)
        (make-evaluation-truth-value truth)
        (make-evaluation-truth-value falsity))))

(defun xml-validate-document2 (xml-document schema-document)
(let ((errors nil))
    (unless (and xml-document
	             schema-document
	             (xml-document-is-valid-p xml-document schema-document))
    (setq errors (xml-get-errors))
    (with-user-notification ()
      (loop for error in errors do (twrite-string error))
      (reclaim-gensym-tree-with-text-strings errors))
    (return-from xml-validate-document2 nil))
    t))
	
(defun xml-validate-document (xml-document)
  (let ((errors nil))
    (unless (and xml-document
	             (=f 0 (c-xml-validate (native-pointer xml-document))))
    (setq errors (xml-get-errors))
    (with-user-notification ()
      (loop for error in errors do (twrite-string error))
      (reclaim-gensym-tree-with-text-strings errors))
    (return-from xml-validate-document nil))
    t))
	
(def-gensym-c-function c-xml-validate
    (:fixnum-int "g2xml_validate")
  ((:pointer document)))

;;;; xml-named-node-map functions


;;;; xml-attr functions


(def-gensym-c-function c-xml-attr-get-name-size
    (:fixnum-int "g2xml_attr_get_name_size")
  ((:pointer node)))

(def-gensym-c-function c-xml-attr-get-name-in-buffer
    (:void "g2xml_attr_get_name_in_buffer")
  ((:pointer node)
   (:string result)
   (:fixnum-int size)
   (:fixnum-int start)))

(defun xml-attr-get-name (xml-attr)
  (dom-fill-in-string-buffer
    c-xml-attr-get-name-size
    c-xml-attr-get-name-in-buffer
    xml-attr))


;;;; xml-element functions


(def-gensym-c-function c-xml-element-get-attribute-size
    (:fixnum-int "g2xml_element_get_attribute_size")
  ((:pointer xml-element)
   (:string name)
   (:string namespace)))


(def-gensym-c-function c-xml-element-get-attribute-in-buffer
    (:void "g2xml_element_get_attribute_in_buffer")
  ((:pointer xml-element)
   (:string name)
   (:string namespace)
   (:string buffer)
   (:fixnum-int size)
   (:fixnum-int start)))


;; A null namespace-uri means that the attribute is local to the element,
;; i.e. its qualified name has no prefix.  Note that this is different from
;; having a namespace equal to the element's namespace: If xml-element is
;; <foo:bar foo:baz="1" baz="2" xmlns:foo="foo" /> then
;; (xml-element-get-attribute xml-element "baz") = "2" and
;; (xml-element-get-attribute xml-element "baz" "foo") = "1".

(defun xml-element-get-attribute (xml-element name &optional namespace-uri)
  (dom-fill-in-string-buffer
    c-xml-element-get-attribute-size
    c-xml-element-get-attribute-in-buffer
    xml-element
    name
    (or namespace-uri "")))
  
(defun xml-element-get-attribute-symbol (element name &optional ns-uri)
  (convert-xml-name-to-symbol-and-reclaim
    (xml-element-get-attribute element name ns-uri)))

(defun xml-element-get-attribute-symbols (element name &optional ns-uri)
  (convert-xml-names-to-symbols-and-reclaim
    (xml-element-get-attribute element name ns-uri)))


;;; The function `xml-element-get-attribute-qname' looks up an attribute by name
;;; and namespace URI whose value is a QName, returning its local name,
;;; namespace prefix (if any), and namespace (if found).  The local name and
;;; namespace prefix are text strings.

(defun xml-element-get-attribute-qname (element name &optional ns-uri)
  (let ((qname (xml-element-get-attribute element name ns-uri)))
    (if qname
	(xml-node-expand-qname element qname)
	(values nil nil nil))))


(defun xml-namespace-get-prefix-symbol (namespace)
  (convert-xml-name-to-symbol-and-reclaim
    (xml-namespace-get-prefix namespace)))


(def-gensym-c-function c-xml-element-set-attribute
    (:void "g2xml_element_set_attribute")
  ((:pointer element)
   (:pointer namespace)
   (:string name)
   (:string value)))

(defun xml-element-set-attribute (xml-element name value &optional namespace)
  (c-xml-element-set-attribute
    (native-pointer xml-element)
    (if namespace (native-pointer namespace) -1)
    name
    value)
  t)

;;; Set an attribute value from a symbol, unless it's nil.

(defun xml-element-set-attribute-symbol (element name value &optional namespace)
  (when value
    (let ((value-string (convert-symbol-to-xml-name value)))
      (xml-element-set-attribute element name value-string namespace)
      (reclaim-text-string value-string))))

;;; Set an attribute value from a list of symbols.

(defun xml-element-set-attribute-symbols (element name vals &optional namespace)
  (let ((value-string (convert-symbols-to-xml-names vals)))
    (xml-element-set-attribute element name value-string namespace)
    (reclaim-text-string value-string)))

;;; Set an attribute value from a text slot value, unless it's nil.

(defun xml-element-set-attribute-from-text-slot-value
    (element name slot-value &optional namespace)
  (when slot-value
    (let ((value-string (convert-text-to-text-string (cdr slot-value))))
      (xml-element-set-attribute element name value-string namespace)
      (reclaim-text-string value-string))))


(def-gensym-c-function c-xml-element-get-attribute-node
    (:pointer "g2xml_element_get_attribute_node")
  ((:pointer xml-element)
   (:string name)
   (:string namespace)))

(defun xml-element-get-attribute-node (xml-element name &optional namespace-uri)
  (let ((result-pointer
	  (c-xml-element-get-attribute-node
	    (native-pointer xml-element)
	    name (or namespace-uri ""))))
    (cond ((>=f result-pointer 0)
	   (create-xml-node result-pointer)))))

(def-gensym-c-function c-xml-element-has-attribute-p
     (:fixnum-int "g2xml_element_has_attribute_p")
  ((:pointer xml-element)
   (:string name)
   (:string namespace)))

(defun xml-element-has-attribute-p (xml-element name &optional namespace-uri)
  (/=f (c-xml-element-has-attribute-p
	 (native-pointer xml-element) name (or namespace-uri ""))
       0))


;;; Search the ancestor list until an attribute value is found.

(defun xml-element-get-inherited-attribute (xml-element name
					    &optional namespace-uri)
  (or (xml-element-get-attribute xml-element name namespace-uri)
      (let ((parent (xml-node-parent-node xml-element)))
	(and parent (xml-element-get-inherited-attribute
		      parent name namespace-uri)))))


;;; Add a namespace declaration to an element.  If prefix is not provided, the
;;; default namespace will be set, i.e. the "xmlns" attribute.

(def-gensym-c-function c-xml-element-new-namespace
    (:pointer "g2xml_element_new_namespace")
  ((:pointer xml-element)
   (:string uri)
   (:string prefix)))

(defun xml-element-new-namespace (xml-element uri &optional prefix)
  (let ((result-pointer
	  (c-xml-element-new-namespace
	    (native-pointer xml-element) uri (or prefix ""))))
    (when (>=f result-pointer 0)
      (create-xml-namespace result-pointer))))


;;; The function `set-frame-name-from-xml-element' sets the name of a frame to
;;; the value of the "name" attribute of an XML element, or NIL if there is no
;;; such attribute.

(defun set-frame-name-from-xml-element (frame element)
  (let ((allow-name-box-creation-without-workspace t))
    (change-slot-value
      frame 'name-or-names-for-frame
      (xml-element-get-attribute-symbol element "name"))))




;;;; xml-character-data functions

;;;; xml-text functions

;;;; xml-namespace functions


(def-gensym-c-function c-xml-element-get-namespace-list
    (:pointer "g2xml_element_get_namespace_list")
  ((:pointer xml-document)
   (:pointer xml-element)))
   
(defun xml-element-get-namespace-list (xml-document xml-element)
  (let ((result-pointer
	  (c-xml-element-get-namespace-list
	    (native-pointer xml-document)
	    (native-pointer xml-element))))
    (cond ((>=f result-pointer 0)
	   (create-xml-namespace-list result-pointer)))))


(def-gensym-c-function c-xml-namespace-list-length
    (:fixnum-int "g2xml_namespace_list_length")
  ((:pointer xml-namespace-list)))

(defun xml-namespace-list-length (xml-namespace-list)
  (c-xml-namespace-list-length (native-pointer xml-namespace-list)))


(def-gensym-c-function c-xml-namespace-list-item
    (:pointer "g2xml_namespace_list_item")
  ((:pointer xml-namespace-list)
   (:fixnum-int index))) 

(defun xml-namespace-list-item (xml-namespace-list index)
  (let ((result-pointer
	  (c-xml-namespace-list-item
	    (native-pointer xml-namespace-list)
	    index)))
    (cond ((>=f result-pointer 0)
	   (create-xml-namespace result-pointer)))))

(def-gensym-c-function c-xml-namespace-get-uri-size
    (:fixnum-int "g2xml_namespace_get_uri_size")
  ((:pointer node)))

(def-gensym-c-function c-xml-namespace-get-uri-in-buffer
    (:void "g2xml_namespace_get_uri_in_buffer")
  ((:pointer node)
   (:string buffer)
   (:fixnum-int size)
   (:fixnum-int start)))

(defun xml-namespace-get-uri (xml-namespace)
  (dom-fill-in-string-buffer
    c-xml-namespace-get-uri-size
    c-xml-namespace-get-uri-in-buffer
    xml-namespace))
  
(def-gensym-c-function c-xml-namespace-get-prefix-size
    (:fixnum-int "g2xml_namespace_get_prefix_size")
  ((:pointer node)))

(def-gensym-c-function c-xml-namespace-get-prefix-in-buffer
    (:void "g2xml_namespace_get_prefix_in_buffer")
  ((:pointer node)
   (:string buffer)
   (:fixnum-int size)
   (:fixnum-int start)))

(defun xml-namespace-get-prefix (xml-namespace)
  (dom-fill-in-string-buffer
    c-xml-namespace-get-prefix-size
    c-xml-namespace-get-prefix-in-buffer
    xml-namespace))
