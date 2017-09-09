;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module SAX

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; John Valente



(declare-forward-reference report-text-indices-error function)



;;;; SAX Parsing in G2


;;; The actual API, irrespective of application.


;;; `c-xml-get-event-callback-type'

(def-gensym-c-function c-xml-get-event-callback-type
    (:fixnum-int "g2xml_get_event_callback_type")
  ((:pointer event-index)))


;;; `c-xml-events-ready'

(def-gensym-c-function c-xml-events-ready
    (:fixnum-int "g2xml_events_ready")
  ((:pointer sax-parser-index)))


;;; `c-xml-get-event-callback-data'

(def-gensym-c-function c-xml-get-event-callback-data
    (:pointer "g2xml_get_event_callback_data")
  ((:pointer event-index)))

;;; `c-xml-dispose-event-callback-data'

(def-gensym-c-function c-xml-dispose-event-callback-data
    (:void "g2xml_dispose_event_callback_data")
  ((:pointer callback-data)))


;;; `c-xml-dispose-event'

(def-gensym-c-function c-xml-dispose-event
    (:void "g2xml_dispose_event")
  ((:pointer callback-event)))


;;; `c-xml-size-element-name'

(def-gensym-c-function c-xml-size-element-name
    (:fixnum-int "g2xml_element_name_size")
  ((:pointer callback-data-index)))


;;; `c-xml-fill-element-name-buffer'

(def-gensym-c-function c-xml-fill-element-name-buffer
    (:fixnum-int "g2xml_fill_element_name_buffer")
  ((:pointer callback-data-index)
   (:string buffer)
   (:fixnum-int length)
   (:fixnum-int start)))


;;; `c-xml-start-element-atts-num'

(def-gensym-c-function c-xml-start-element-atts-num
    (:fixnum-int "g2xml_start_element_atts_num")
  ((:pointer callback-data-index)))


;;; `c-xml-size-start-element-att'

(def-gensym-c-function c-xml-size-start-element-att
    (:fixnum-int "g2xml_start_element_att_size")
  ((:pointer callback-data-index)
   (:fixnum-int att-number)))


;;; `c-xml-fill-start-element-att-buffer'

(def-gensym-c-function c-xml-fill-start-element-att-buffer
    (:void "g2xml_fill_start_element_att_buffer")
  ((:pointer callback-data-index)
   (:string buffer)
   (:fixnum-int length)
   (:fixnum-int att-num)))


;;; `c-xml-size-characters-or-comment'

(def-gensym-c-function c-xml-size-characters-or-comment
    (:fixnum-int "g2xml_characters_or_comment_size")
  ((:pointer callback-data-index)))


;;; `c-xml-fill-characters-or-comment-buffer'

(def-gensym-c-function c-xml-fill-characters-or-comment-buffer
    (:fixnum-int "g2xml_fill_characters_or_comment_buffer")
  ((:pointer callback-data-index)
   (:string buffer)
   (:fixnum-int length)
   (:fixnum-int start)))


;;; `c-xml-size-warning-or-error'

(def-gensym-c-function c-xml-size-warning-or-error
    (:fixnum-int "g2xml_error_size")
  ((:pointer callback-data-index)))


;;; `c-xml-fill-error-buffer'

(def-gensym-c-function c-xml-fill-error-buffer
    (:fixnum-int "g2xml_fill_error_buffer")
  ((:pointer callback-data-index)
   (:string buffer)
   (:fixnum-int length)))


;;; `c-xml-init-sax'

(def-gensym-c-function c-xml-init-sax
    (:void "g2xml_init_sax")
  ())


;;; `c-xml-make-sax-parser'

(def-gensym-c-function c-xml-make-sax-parser
    (:pointer "g2xml_make_parser_context")
  ())


;;; `c-xml-parse-chunk'

(def-gensym-c-function c-xml-parse-chunk
    (:fixnum-int "g2xml_parse_chunk")
  ((:pointer sax-parser-index)
   (:string buffer)
   (:fixnum-int size)
   (:fixnum-int terminate)))


;;; `c-xml-parse-file'

(def-gensym-c-function c-xml-parse-file
    (:fixnum-int "g2xml_parse_file")
  ((:pointer sax-parser-index)
   (:string path)))


;;; `c-xml-first-sax-event'

(def-gensym-c-function c-xml-first-sax-event
    (:pointer "g2xml_first_sax_event")
  ((:pointer queue-index)))


;;; `c-xml-next-sax-event'

(def-gensym-c-function c-xml-next-sax-event
    (:pointer "g2xml_next_sax_event")
  ((:pointer event-index)))


;;; `c-xml-cleanup-parser'

(def-gensym-c-function c-xml-cleanup-parser
    (:void "g2xml_cleanup_parser")
  ((:pointer sax-parser-index)))



;;;; Lisp Wrappers for SAX C Functions


;; The following eight functions exist because we want to call the "size" and
;; "fill" functions using funcall, and that simply doesn't work with gensym-
;; c-functions.  The translator doesn't support it.  One other advantage of
;; using wrappers is that we are able to unify the function signatures, without
;; passing unnecesary arguments to C.  These functions could become defun-
;; simple's and defun-void's at some point soon.  -jv, 1/17/03

;;; `lisp-xml-size-start-element-att'

(defun lisp-xml-size-start-element-att (callback-data att-num)
  (c-xml-size-start-element-att callback-data att-num))


;;; `lisp-xml-size-element-name'

(defun lisp-xml-size-element-name (callback-data ignorable)
  (declare (ignore ignorable))
  (c-xml-size-element-name callback-data))


;;; `lisp-xml-size-characters-or-comment'

(defun lisp-xml-size-characters-or-comment (callback-data ignorable)
  (declare (ignore ignorable))
  (c-xml-size-characters-or-comment callback-data))


;;; `lisp-xml-size-warning-or-error'

(defun lisp-xml-size-warning-or-error (callback-data ignorable)
  (declare (ignore ignorable))
  (c-xml-size-warning-or-error callback-data))


;;; `lisp-xml-fill-start-element-att-buffer'

(defun lisp-xml-fill-start-element-att-buffer (callback-data buffer length att-num)
  (c-xml-fill-start-element-att-buffer callback-data buffer length att-num))


;;; `lisp-xml-fill-element-name-buffer'

(defun lisp-xml-fill-element-name-buffer (callback-data buffer length ignorable)
  (declare (ignore ignorable))
  (c-xml-fill-element-name-buffer callback-data buffer length 0))


;;; `lisp-xml-fill-characters-or-comment-buffer'

(defun lisp-xml-fill-characters-or-comment-buffer (callback-data buffer length ignorable)
  (declare (ignore ignorable))
  (c-xml-fill-characters-or-comment-buffer callback-data buffer length 0))


;;; `lisp-xml-fill-error-buffer'

(defun lisp-xml-fill-error-buffer (callback-data buffer length ignorable)
  (declare (ignore ignorable))
  (c-xml-fill-error-buffer callback-data buffer length))







;;; `sax-callback-type' -- returns an appropriate symbol given the fixnum
;;; returned from lisp.

(defun sax-callback-type (event)
  (let ((callback-type
	  (c-xml-get-event-callback-type event)))
    (case callback-type
      (#.xml-callback-start-document
       'start-document-procedure)
      (#.xml-callback-end-document
       'end-document-procedure)
      (#.xml-callback-start-element
       'start-element-procedure)
      (#.xml-callback-end-element
       'end-element-procedure)
      (#.xml-callback-characters
       'characters-procedure)
      (#.xml-callback-comment
       'comment-procedure)
      (#.xml-callback-warning
       'warning-procedure)
      (#.xml-callback-error
       'error-procedure)
      (#.xml-callback-fatal-error
       'fatal-error-procedure)
      (t
       'none))))



;;;; SAX Parser Object


(def-class (sax-parser
	     object
	     (foundation-class sax-parser)
	     (class-export-comment
	       "SAX parsers provide an interface to libxml2"))
  (frame-author-or-authors
    nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      50 50
      ((polychrome (g2-icon-outline . foreground)
		   (g2-icon-background . light-gray)
		   (g2-icon-light-shading . smoke)
		   (g2-icon-dark-shading . dark-gray)
		   (text-region . foreground))
       (variables)
       (background-layer)
       g2-icon-background (solid-rectangle (0 0) (50 50))
       g2-icon-light-shading (filled-polygon ((0 0) (50 0) (47 3) (3 3) (3 47) (0 50))
					     ((0 0) (50 0) (47 3))
					     ((3 3) (3 47) (0 50))
					     ((0 0) (47 3) (3 3))
					     ((3 3) (0 50) (0 0)))
       (lines (5 45) (44 45) (44 5))
       g2-icon-dark-shading
       (filled-polygon ((47 3) (50 0) (50 50) (0 50) (3 47) (47 47))
		       ((47 3) (50 0) (50 50)) ((50 50) (0 50) (3 47))
		       ((47 47) (47 3) (50 50)) ((50 50) (3 47) (47 47)))
       g2-icon-outline (outline (0 0) (0 50) (50 50) (50 0))
       g2-icon-outline (lines (44 5) (5 5) (5 45))
       text-region (text #w"X" (30 43) large)
       text-region (text #w"A" (18 32) large)
       text-region (text #w"S" ( 8 21) large))
      nil nil nil nil nil
      ((g2-icon-outline 27 26 43 42)
       (g2-icon-background 0 0 50 50)
       (g2-icon-light-shading 0 0 50 50)
       (g2-icon-dark-shading 0 0 50 50)
       (g2-icon-outline 0 0 50 50)
       (text-region 8 6 20 26))))
  (parser-context-handle nil do-not-save do-not-clone system)
  (last-parser-event nil do-not-save do-not-clone system)
  (number-of-pending-callbacks 0 (type integer) do-not-save do-not-clone system
			    not-user-editable)
  (start-document-procedure nil (type procedure-name?) vector-slot system)
  (end-document-procedure nil (type procedure-name?) vector-slot system)
  (start-element-procedure nil (type procedure-name?) vector-slot system)
  (end-element-procedure nil (type procedure-name?) vector-slot system)
  (characters-procedure nil (type procedure-name?) vector-slot system)
  (comment-procedure nil (type procedure-name?) vector-slot system)
  (warning-procedure nil (type procedure-name?) vector-slot system)
  (error-procedure nil (type procedure-name?) vector-slot system)
  (fatal-error-procedure nil (type procedure-name?) vector-slot system))


;;; `reset-sax-parser'

(defun reset-sax-parser (the-parser)
  (let ((parsing-context (parser-context-handle the-parser)))

    (when parsing-context
      (c-xml-cleanup-parser parsing-context))
	
    (setf (parser-context-handle the-parser) nil)
    (setf (last-parser-event the-parser) nil)
    (change-slot-value the-parser 'number-of-pending-callbacks 0)))


;;; `cleanup-for-sax-parser' - note, we call reset-sax-parser, which clears the
;;; values of several slots.  This is a bit pointless since we're just about to
;;; completely delete the sax-parser, but it keeps things consistent at all
;;; times.  We should not clean up the C queue without resetting the other slots

(def-class-method cleanup (sax-parser)
  (funcall-superior-method sax-parser)
  (reset-sax-parser sax-parser))


;;; `deactivate-subclass-of-entity-for-sax-parser' - adding this primarily for
;;; when G2 is reset.  It's not entirely clear we want to reset the parser just
;;; because it is deactivated.  However, this is the behavior of a g2-parameter,
;;; which changes its last recorded value to its initial value when it is
;;; deactivated, and that was the closest parallel I could find.  -jv, 1/17/03

(def-class-method deactivate-subclass-of-entity (sax-parser)
  (reset-sax-parser sax-parser))



;;; `maximum-length-for-sax-strings' should be the same as maximum-length-for-
;;; user-text-strings, but can set it much smaller for testing.

(defvar maximum-length-for-sax-strings maximum-length-for-user-text-strings)


;;; `sax-fill-in-string-buffer' -- probably want to switch to using
;;; funcall-simple-compiled-function in the very near future, but make things
;;; as straightforward as possible for the first pass.

(defun sax-fill-in-string-buffer (size-function fill-in-function
						callback-data attribute-number?)
  (let* ((true-size-required
	   (funcall size-function callback-data attribute-number?))
	 (size-to-use
	   (minf true-size-required maximum-length-for-sax-strings))
	 (string-buffer
	   (obtain-simple-gensym-string size-to-use))
	 (wide-string-value nil))
    (funcall fill-in-function callback-data string-buffer size-to-use attribute-number?)
    (let* ((translated-string (import-text-string string-buffer 'utf-8-string)))
         (setq wide-string-value (copy-as-wide-string translated-string))
         (reclaim-gensym-string-or-wide-string translated-string))
    (reclaim-simple-gensym-string string-buffer)
    (values wide-string-value
	    (>f true-size-required maximum-length-for-sax-strings))))



(defconstant sax-id-callback-type 'callback-type)
(defconstant sax-id-element-name 'element-name)
(defconstant sax-id-attributes 'attributes)
(defconstant sax-id-attribute-name 'attribute-name)
(defconstant sax-id-attribute-value 'attribute-value)
(defconstant sax-id-comment 'comment)
(defconstant sax-id-characters 'string)
(defconstant sax-id-error-message 'error-message)


;;; `sax-start-or-end-document-data'

(defun sax-start-or-end-document-data (callback-type)
  (allocate-evaluation-structure-inline
    sax-id-callback-type callback-type))


;;; `sax-get-element-name'

(defun sax-get-element-name (callback-data sax-parser)
  (multiple-value-bind
      (element-name oversize-element-name-p)
      (sax-fill-in-string-buffer #'lisp-xml-size-element-name
				 #'lisp-xml-fill-element-name-buffer
				 callback-data nil)	 
    (when oversize-element-name-p
      (let ((beginning-of-truncated-string
	      (text-string-substring element-name 0 20)))
	(notify-user
	  "Warning: Sax-parser ~NF read an element name longer than ~
           the maximum allowed length of ~a bytes. ~
           The string beginning ~s will be truncated to the maximum ~
           allowed length."
	  sax-parser
	  maximum-length-for-sax-strings
	  beginning-of-truncated-string)
	(reclaim-text-string beginning-of-truncated-string)))
    element-name))


;;; `sax-get-next-start-element-attribute'

(defun sax-get-next-start-element-attribute (callback-data att-num sax-parser)
  (multiple-value-bind
      (attribute-string oversize-attribute-p)
      (sax-fill-in-string-buffer #'lisp-xml-size-start-element-att
				 #'lisp-xml-fill-start-element-att-buffer
				 callback-data att-num)
    (when oversize-attribute-p
      (let ((beginning-of-truncated-string
	      (text-string-substring attribute-string 0 20)))
	(notify-user
	  "Warning: Sax-parser ~NF read an attribute name (number ~NA) ~
           longer than the maximum allowed length of ~a bytes. ~
           The string beginning ~s will be truncated to the maximum ~
           allowed length."
	  sax-parser att-num
	  maximum-length-for-sax-strings
	  beginning-of-truncated-string)
	(reclaim-text-string beginning-of-truncated-string)))
    attribute-string))
  


;;; `sax-start-element-data'

(defun sax-start-element-data (callback-data sax-parser)
  (allocate-evaluation-structure-inline
    sax-id-callback-type 'start-element
    sax-id-element-name (sax-get-element-name callback-data sax-parser)
    sax-id-attributes
    (allocate-evaluation-sequence
      (loop with num-atts = (c-xml-start-element-atts-num callback-data)
	    with fill-in-value-p = (oddp num-atts)
	    for j = (1-f num-atts)
		  then (-f j 2)
	    with result = '()
	    while (>=f j 0)
	    do
	(eval-push
	  (allocate-evaluation-structure-inline
	    sax-id-attribute-name
	    (make-evaluation-text-reclaiming-argument
	      (sax-get-next-start-element-attribute callback-data (1-f j) sax-parser))
	    sax-id-attribute-value
	    (make-evaluation-text-reclaiming-argument
	      (cond
		(fill-in-value-p			; Note A
		 #+development
		 (format t "~a:~% ~a: ~%  ~a~%"
			 "sax-start-element-data"
			 "lexer.lisp"
			 "number of attributes should always be even")
		 (setq fill-in-value-p nil)
		 (make-wide-string 0))
		(t
		 (sax-get-next-start-element-attribute callback-data j sax-parser)))))
	  result)
	    finally
	      (return result)))))

;; Note A: there should always be an even number of attributes.  Elements are
;; of the form <element-name name1=value1 name2=value2 name3=value3>, and these
;; names and values come to us in an undifferentiated stream of "attributes."
;; I really don't know what to make of an odd number of attributes, but since
;; I'm not sure I can say with certainty that it can never happen, I'll try
;; to do something reasonable should it ever come up.  I'll just assume that
;; the first n attributes are name-value pairs, with the last attribute being
;; a name, and fill in its value with an empty string.  I'll also print a
;; message in development.  -jv, 12/30/02


;;; `sax-end-element-data'

(defun sax-end-element-data (callback-data sax-parser)
  (allocate-evaluation-structure-inline
    sax-id-callback-type 'end-element
    sax-id-element-name (sax-get-element-name callback-data sax-parser)))


;;; `sax-characters-or-comment-data'

(defun sax-characters-or-comment-data (callback-data callback-type sax-parser)
  (multiple-value-bind
      (text-to-return oversize-comment-p)
      (sax-fill-in-string-buffer #'lisp-xml-size-characters-or-comment
				 #'lisp-xml-fill-characters-or-comment-buffer
				 callback-data nil)
    (when oversize-comment-p
      (notify-user "Warning: Sax-parser ~NF truncated ~NA: ~NA"
		   sax-parser
		   (if (eq callback-type sax-id-comment)
		       #w"Comment"
		       #w"Characters")
		   text-to-return))
    (allocate-evaluation-structure-inline
      sax-id-callback-type callback-type
      (if (eq callback-type sax-id-comment)
	  sax-id-comment
	  sax-id-characters)
      text-to-return)))


;;; `sax-warning-or-error-data'

(defun sax-warning-or-error-data (callback-data callback-type sax-parser)
  (multiple-value-bind
      (text-to-return oversize-error-message-p)
      (sax-fill-in-string-buffer #'lisp-xml-size-warning-or-error
				 #'lisp-xml-fill-error-buffer
				 callback-data nil)
    (when oversize-error-message-p
      (notify-user "Warning: Sax-parser ~NF truncated the ~NA being reported: ~NA"
		   sax-parser
		   (case callback-type
		     (warning #w"warning")
		     (error #w"error")
		     (fatal-error #w"fatal error"))
		   text-to-return))
    (allocate-evaluation-structure-inline
      sax-id-callback-type callback-type
      sax-id-error-message text-to-return)))



;;; `get-sax-callback-data'

(defun get-sax-callback-data (callback-type callback-data sax-parser)
  (case callback-type
    ((start-document-procedure end-document-procedure)
     (sax-start-or-end-document-data callback-type))
    (start-element-procedure
     (sax-start-element-data callback-data sax-parser))
    (end-element-procedure
     (sax-end-element-data callback-data sax-parser))
    (characters-procedure
     (sax-characters-or-comment-data callback-data 'characters sax-parser))
    (comment-procedure
     (sax-characters-or-comment-data callback-data 'comment sax-parser))
    (warning-procedure
     (sax-warning-or-error-data callback-data 'warning sax-parser))
    (error-procedure
     (sax-warning-or-error-data callback-data 'error sax-parser))
    (fatal-error-procedure
     (sax-warning-or-error-data callback-data 'fatal-error sax-parser))
    (t
     #+development
     (format t "Not-yet-supported callback (~s).~%" callback-type)
     ;; Temp hack; give some sort of default value
     (allocate-evaluation-structure-inline
       sax-id-callback-type 'unsupported))))



;;; `g2-sax-execute-next-callback'

(def-concept g2-sax-execute-next-callback
  "A system procedure which is not just a straightforward cap.")


;;; `g2-sax-events-ready'

(defun-for-system-procedure g2-sax-events-ready ((sax-parser item))
  (declare (values integer)
           (keeps-g2-local-variables-valid t))
  (let* ((parser-context (parser-context-handle sax-parser))
	 (number-of-events
	   (if (null parser-context)
	       0
	       (c-xml-events-ready parser-context))))
    (change-slot-value sax-parser 'number-of-pending-callbacks
		       number-of-events)
    number-of-events))




;;; `g2-sax-parse-file' parses a complete file given its path, enqueueing all
;;; SAX events and returning the new total number of events in the queue.

(defun-for-system-procedure g2-sax-parse-file ((sax-parser item) (path text))
  (declare (values integer))
  (let ((parser-context (parser-context-handle sax-parser)))
    (when (null parser-context)
      (setq parser-context (c-xml-make-sax-parser))
      (setf (last-parser-event sax-parser) nil)
      (setf (parser-context-handle sax-parser) parser-context))
    (c-xml-parse-file parser-context path)
    (g2-sax-events-ready sax-parser)))



;;; `g2-sax-parse-chunk-internal' - always parses from the beginning of the
;;; text, and intended to always parse until the end of the text, although
;;; it takes the length of the text as a parameter, rather than computing
;;; it by itself.

;; Note this function is more complex that it seems it should be.  This is due
;; to a bug/feature of the libxml2 C library we are using which doesn't do the
;; right thing when given an entire document to parse in one shot.  It might be
;; better to hide this complexity in the C layer in lispxml.c rather than expose
;; it here. -dkuznick, 3/4/03



(defun-void g2-sax-parse-chunk-internal (sax-parser text-chunk length)
  (let ((parser-context (parser-context-handle sax-parser))
	(checked-encoding-this-call nil))
    (when (null parser-context)
      ;; Make a parser but don't do the parse yet.
      (setq parser-context (c-xml-make-sax-parser))
      (setf (last-parser-event sax-parser) nil)
      (setf (parser-context-handle sax-parser) parser-context)
      ;; Check the encoding.  This has the side benefit of not parsing the
      ;; entire document in one go, which the libxml2 parser doesn't handle
      ;; well. -dkuznick, 3/3/03
      (when (>=f length xml-encoding-length)
	(let ((encoding-piece (copy-portion-of-wide-string
				(evaluation-text-value text-chunk)
				0
				xml-encoding-length)))
	  (c-xml-parse-chunk parser-context encoding-piece xml-encoding-length 0)
	  (setq checked-encoding-this-call t)
	  (reclaim-wide-string encoding-piece))))
    (if checked-encoding-this-call
	;; If we've already parsed a bit to check the encoding, don't parse that
	;; part again	
	(let* ((length-of-rest (-f length xml-encoding-length))
	       (rest-of-chunk (copy-portion-of-wide-string
				(evaluation-text-value text-chunk)
				xml-encoding-length
				length)))
	  (c-xml-parse-chunk parser-context rest-of-chunk length-of-rest 0)
	  (reclaim-wide-string rest-of-chunk))
	(c-xml-parse-chunk parser-context text-chunk length 0))))



;;; `g2-sax-parse-chunk'

(defun-for-system-procedure g2-sax-parse-chunk ((sax-parser item)
                                                (input-text text)
                                                (start-index integer)
                                                (end-index integer))
  (multiple-value-bind
    (g2-text-start-index g2-text-end-index)
      (convert-user-g2-text-indices-to-internal-indices
        input-text start-index end-index)
    (cond
      ((null g2-text-start-index)
        (report-text-indices-error input-text start-index end-index 'g2-sax-parse-chunk))
      (t
        (let* ((chunk-to-parse (export-text-string
                                 (evaluation-text-value input-text)
                                 'utf-8-string
                                  g2-text-start-index
                                  g2-text-end-index))
               (text-length
                 (if (gensym-string-p chunk-to-parse)
                   (gensym-string-length chunk-to-parse)
                   (text-string-length chunk-to-parse))))

          (g2-sax-parse-chunk-internal sax-parser chunk-to-parse text-length)
          (reclaim-gensym-string-or-wide-string chunk-to-parse)))))
  nil)




;;; The system procedure function `g2-sax-next-callback-type' returns two symbol
;;; values, the type of the callback and the name of the callback procedure (or
;;; NONE if the sax-parser has no callback procedure for the type).

(defun-for-system-procedure g2-sax-next-callback-type ((sax-parser item))
  (declare (values symbol symbol)
           (keeps-g2-local-variables-valid t))
  (unless (>f (number-of-pending-callbacks sax-parser) 0)
    (stack-error cached-top-of-stack
                 "Attempted to execute the next SAX callback on ~NF, but it ~
                  has no callbacks pending." sax-parser))
  (let* ((parser-context (parser-context-handle sax-parser))
         (next-event nil))
    (cond
      ((null parser-context)
       (values (make-evaluation-symbol 'none) (make-evaluation-symbol 'none)))
      (t
       (setq next-event (c-xml-first-sax-event parser-context))
       (setf (last-parser-event sax-parser) next-event)
       (let ((type (sax-callback-type next-event)))
	 (values
	   (make-evaluation-symbol type)
	   (make-evaluation-symbol
	     (or (get-slot-value-if-any sax-parser type) 'none))))))))


;;; `g2-sax-callback-data'

(defun-for-system-procedure g2-sax-callback-data ((sax-parser item)
						  (callback-type symbol))
  (declare (values structure)
           (keeps-g2-local-variables-valid t))
  (let* ((last-event (last-parser-event sax-parser))
	 callback-data-handle real-callback-data)
    (setq callback-data-handle (c-xml-get-event-callback-data last-event))
    (setq real-callback-data
	  (get-sax-callback-data callback-type callback-data-handle sax-parser))
    (c-xml-dispose-event-callback-data callback-data-handle)
    real-callback-data))


;;; `g2-executed-sax-callback' - one of several internal functions called from
;;; the system procedure g2-sax-execute-next-callback

(defun-for-system-procedure g2-executed-sax-callback ((sax-parser item))
  (let ((last-event (last-parser-event sax-parser)))
    (when last-event
      (c-xml-dispose-event last-event)
      (setf (last-parser-event sax-parser) nil)))
  (when (>f (number-of-pending-callbacks sax-parser) 0)
    (change-slot-value sax-parser 'number-of-pending-callbacks
                       (1-f (number-of-pending-callbacks sax-parser)))))


;;; `g2-sax-reset-parser'

(def-concept g2-sax-reset-parser
  "A system procedure whose name varies internally.")


;;; `g2-reset-sax-parser' -- should (re-)initialize the parser object, and
;;; clean up any existing datat structures, and make the parser ready to
;;; start parsing from scratch.  Cap name is g2-sax-reset-parser.

(defun-for-system-procedure g2-reset-sax-parser ((sax-parser item))
  (reset-sax-parser sax-parser))



;;; `g2-sax-finish-parsing'

(def-concept g2-sax-finish-parsing
  "A system procedure whose name varies internally.")


;;; `g2-finish-sax-parsing' -- must be called to get an end-document event


(defun-for-system-procedure g2-finish-sax-parsing ((sax-parser item))
  (let ((parser-context (parser-context-handle sax-parser)))
    (cond
      ((null parser-context)
       #+development
       (cerror "Continue"
	       "parser-context nil in g2-finish-sax-parsing")
       )
      (t
       (let ((empty-string (make-wide-string 0)))
	 (c-xml-parse-chunk parser-context empty-string 0 1)
	 (reclaim-wide-string empty-string))))))
