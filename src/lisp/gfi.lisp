;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GFI -- G2 File Interface Data Server

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Jim Allard, Chris Morel, and Ong, Peng Tsin



#+translator
(if (not (string-or-symbol-member 'gfi (optional-modules 'ab)))
    (push 'gfi (optional-modules 'ab)))



;;; The class definitions and grammars for GFI-OUTPUT-INTERFACE,
;;; GFI-INPUT-INTERFACE, and GFI-DATA-SERVICE are given in the module STUBS.






;;; GFI is intended to allow users to output information to disk files and use
;;; input information from GFI data files to data serve variables.  For example,
;;; if the user has a simulator which has generated a series of results in the
;;; GFI data file format, the file can be used to determined the value of
;;; G2-variables within G2 using GFI in the input mode.  Using GFI in the output
;;; mode will allow allow all types of information to be written out from G2
;;; during run time.
;;;
;;; Possible Uses:
;;; 1. Archiving
;;; 2. Warm booting	- very important!!!  -pto 07oct88
;;; 3. Batch G2 processing of data
;;; 4. Simulation replay
;;; 5. Simulation archiving
;;; 6. Off-line testing
;;;
;;; The present hinderance to a memory leak-free GFI is the lack of non-leaking
;;; file operation functions (such as read-line, write-line, open-file, and
;;; close-file).  These functions are not only needed by GFI, but also by:
;;;  1. G2-to-G2 communication (network i/o leaks, consider using files), and,
;;;  2. the save, load, and merge functions in G2.




;;; DESIGN NOTES:
;;;
;;; The issues are:
;;;   1. GFI-MODE:  read  VS  write
;;;   2. GFI-FILE-FORMAT:  spreadsheet  VS  event log
;;;   3. GFI-DATA-SERVICE-MODE:  data driven  VS  request/response (polled)
;;;   4. GFI-DATA-SOURCE-MODE:  internal  VS  external  (via ICP)
;;;   5. single file  VS  series of files
;;;   6. incremental file opreation  VS  all-at-once file operation
;;;           	(whether you read in all the data at once or little by little)
;;;   7. incrementally add to history  VS  all-at-once creation of history
;;;   8. Ascii  VS  binary
;;;   9. GFI-RUN-OPTION:  synchronized ???
;;;   10. Transactional  VS  non-transactional
;;;
;;; We will not worry about 5., 6., 7., and 8. for the moment.  (21sep88)
;;;
;;; Circular List of Files:  Have a list of files, and a limit of how much to
;;; write to each file, and cycle through the list of files.  This will result
;;; in a set of histories.




;;; TIME-STAMPS:  
;;;
;;; A time-stamp can be either explicit of relative.  An explicit time-stamp is
;;; in the form "dd Mmm yyyy hh:mm:ss".  A relative time-stamp is an integer
;;; which is the temporal difference, in seconds, between the base time (of the
;;; GFI file) and the time at which the time-stamp was made.




;;; GFI-FILE-FORMAT:
;;;
;;; 1. event-log
;;;    File format:
;;;	 <time-stamp> <designation> <value>
;;;           :             :          :
;;;           :             :          :
;;;
;;; For relative time-stamped GFI files, the first line should look like:
;;;	<absolute-time-stamp> <tab> the current time <tab> 0
;;; This indicates that the start time is set to 0.
;;;
;;; In either relative or explicit time-stamp modes, the time-stamp of the first
;;; entry in the GFI must be an explicit time stamp.
;;;
;;; 2. spreadsheet
;;;    File format:
;;;      BASE TIME: <time-stamp>         <designation-1> <designation-2> ...
;;;      <time-stamp> 		        <value-1>       <value-2>       ...
;;;           :                              :              :           ...
;;;
;;; If relative time-stamping is specified in a GFI file, the first entry in the
;;; first line of the file should be:  BASE TIME: dd Mmm yyyy hh:mm:ss <tab>.
;;; If explicit time-stampping is sspecified, the first entry must be a <null>
;;; (i.e. the first character in the file must be a <tab> or <white-spaces>).




;;; THE USERS' PERSPECTIVE:
;;;
;;; To Create GFI a File from G2:
;;; We need to create an instance of GFI-OUTPUT-INTERFACE and an output data
;;; server instance of the definition related to the output file.  The values to
;;; be output and the output frequency are also defined in the data server
;;; instance's table.
;;;
;;; The values to be output are defined by a list of constant-designations in
;;; the gfi-output-values attribute of the output data server instance.  (We
;;; should consider extending this list to handle designations that refer to
;;; more than one entity.)
;;;
;;;
;;; To Read in to G2 from a GFI File:
;;; We need to create at least two object definitions:
;;;
;;; 1. An instance of GFI-INPUT-INTERFACE and an input data server instance
;;; related to the input file.  Name the instance.
;;;
;;; 2. For each subclass of g2-variable that is to be served by the data server
;;;    instance,
;;;    a. Create an object definition of the subclass of g2-variable and give
;;;       it a GFI-DATA-SERVICE superior class.
;;;    b. Create an instance of the gfi variable class for each variable which
;;;       is to served by GFI data service.
;;;    c. Indicate the GFI data server instance by name in the table of each of
;;;       the newly created variables.
;;;
;;; 3. If the variables that are to be data served from GFI have already been
;;; defined, add GFI-DATA-SERVICE as a superior class to their class definitions
;;; and go to each instance to be served and indicate the input data server
;;; instance to be used to serve the variables.






;;; LOG OF MAJOR CHANGES TO GFI:

;; July 89, cpm:
;;
;; 1. Two new "GFI input variables update mode" were introduced:
;;      "input when activated"
;;	"input when activated, without interruption"
;;    These modes allow users to read in all the specified current values 
;;    when the GFI Input Interface is activated.  The "without interruption"
;;    allows GFI to hang G2 until the entire file has been read in.
;;
;; 2. Two new "GFI output file update frequency" options were introduced:
;;      "write to a file when activated"
;;      "write to a file when activated, without interruption"
;;    These modes allow users to write out all the specified current values 
;;    when the GFI Output Interface is activated.  The "without interruption"
;;    allows GFI to hang G2 until all the apropriate values have been written
;;    out.

;; Oct 89, pto:
;;
;; 1. The user can specify either a file name as a string or a constant designation
;;    to a text variable or parameter which gives the file name in a string.
;;    This applies to both the output file name and the file to rename to upon
;;    closing.  Of course if parameters or variables are specified, they
;;    must have values when they are referenced:  the output file name is referenced
;;    when the GFI interface is activated, and the renamed file name when the
;;    GFI Output Interface is closing the output file.
;;    NOTE:  Don't use special characters in file names.
;;
;; 2. New user visible slots for GFI Interface objects:
;;    . file system (possible values are:  symbolics, explorer, microexplorer,
;;		     			   unix, vms, and macintosh)
;;    . file status (possible values are:  ready-to-open, failed-to-open,
;;		     			   open, and closed)
;;    They can be referenced as "the file-system of <foo>" and
;;    "the file-status of <foo>".
;;
;; 3. A new "GFI input variables update mode" was introduced:
;;      "asynchronous input, ignoring the data server"
;;    This new mode is the same as the "asynchronous input" mode, except that
;;    it does not require that the variable or parameter have GFI data service;
;;    i.e. GFI will just perform a set-current-value on the variable.
;;
;; 4. E-designations (generic) were allowed in "Gfi output values".
;;    For event logs:
;;	All variables with names that match the designations, and
;;	for which we can obtain a designation from generate-designation-for-block,
;;	will have their values logged.
;;    For spreadsheets:
;;  	GFI determines the variables for each column by serving the designations
;;	when it is first activated.  Only variables which matched the designations
;;      at the activation time of the GFI Output Interface will have their values
;;	logged.
;;

;; Jan 90, cpm:
;;
;; 1. Added the NUPEC Snapshot/Restart feature which depends and builds on GFI.
;;    This feature allows the user to save and restore the state (i.e., current
;;    value and history) of particular G2 variables and parameters.  NUPEC
;;    Snapshot/Restart is describe more fully below.

;; 1994/1995, GHW, for G2 version 4.0:
;;
;; 1. GFI-output-interface and GFI-input-interface are now instantiable
;; system-defined classes.  They were previously implemented as capabilities,
;; but capabilities have been removed in version 4.0, now that we have multiple
;; inheritance of classes.
;; 2. GFI-data-service is now a user-defined class, instead of a capability.
;; This class can be used as one of the superiors in a user-defined class, when
;; defining a subclass of variable.

;; February 1996, mhd:
;;
;; 1. Converted to use new Text Strings (Unicode Wide Strings) instead of
;;    old Text Strings (now called gensym strings).  Except at the lowest
;;    level, this now does all string/text processing in Unicode wide
;;    strings and Unicode wide characters.  At the lowest level this still
;;    expects running text to be encoded as in UTF-G, the historic 7-bit
;;    interchange format for Gensym text.
;;
;; 2. Several macros were made into functions.  They had no business being
;;    macros, but were made so in the late 80's by certain overzealous
;;    people in fear of function calling overhead.  

;; July 1996, cpm, for G2 5.0:
;;
;; 1. Remove restriction on GFI interface object attribute edits.  Previously,
;;    these attributes could only be modified when G2 was reset.
;;    Note that active, started GFI objects are stopped and restarted as
;;    necessary, based on the type of edit.
;; 2. Add category-evaluator getters and setters for GFI attributes.
;; 3. Added the user-visible slots gfi-input-when-active and
;;    gfi-output-when-active, to GFI input and output interface objects
;;    respectively.  This slot must be set to "yes" (i.e., T), for an
;;    active GFI object to be started.  The user can toggle this attribute
;;    to start and stop active GFI objects.




;; Possible Future Work (01nov89):
;;
;;  1. Option to append instead of overriding output files.
;;  2. File version numbers and/or rule settable filename
;;  3. Access to simulated values
;;  4. Write frequency determined by predicate
;;  5. Read/write by rule control (by action or otherwise)
;;     NOTE in 5.0, the new gfi-output-when-active and gfi-input-when-active
;;     slot control if an interface object is started when active.
;;     See above note, in change log, above.
;;  6. Circular files
;;  7. Log messages to files.
;;  8. Frame notes


;; At the present, the g2-stream-write functions are not checked for errors
;; after they are returned.  In the general case, this should be ok.  But there
;; is no guarantee that all write operations will be successful.  Thus, we
;; should implement some checking to ensure that writes are successful before
;; proceeding.  -pto 24oct88.






;;;; NUPEC Snapshot/Restart
;;;
;;; The NUPEC software development was funded by NUPEC.
;;;
;;; The snapshot/restart facility is used to save the state of the values and
;;; histories of the parameters and variables in a G2 knowledge base, for future
;;; possible reloading into a freshly started copy of that knowledge base at a
;;; later time.
;;;
;;; A snapshot is created by writing the current time and the history of
;;; specific variables and parameters to a file.  When a snapshot is restarted
;;; in real-time mode, values and histories are read from the snapshot file and
;;; added to the values and histories that already exist in the system, rather
;;; than replacing them.  When a snapshot is restarted in catch-up mode, values
;;; and histories are read also from the snapshot file, but the these replace
;;; values and histories which are currently in the knowledge base.  Also, when
;;; only in catch-up mode, the current time of the knowledge base will be reset
;;; to be the time at which the snapshot was taken.
;;;
;;; The time-stamps written into snapshots can be in relative or explicit
;;; format. 
;;;
;;; The snapshot/restart feature is provided through enhanced facilities in GFI
;;; output and input routines.  There is one new GFI file output format and two
;;; new GFI input formats.  The output format writes out each variable or
;;; parameters current value and history, and the time at which the snapshot was
;;; taken.  Both of the two new input formats will read the values and histories
;;; form the file, installing them into variables and parameters.  They differ
;;; in that one is intended to be used when the knowledge base is executing in
;;; real-time mode, and the other for when the knowledge base is executing in
;;; catch-up mode.
;;;
;;; NOTE THAT RESTARTING A SNAPSHOT DOES NOT CAUSE FORWARD CHAINING!  Therefore,
;;; be sure that the snapshot is made during a "stable state" (i.e., chaining
;;; has stopped).  To do this, create the snapshot (i.e., activate the GFI
;;; output interface object) through a rule or procedure that has a low
;;; priority!






;;;; GFI Constants



(progn

  ;; Franz ACL compile complained constants were being redefined when this progn
  ;; was (eval-when (:compile-toplevel :load-toplevel :execute) ...).  It looks like it needn't be,
  ;; which is why I've changed it to a progn. -mhd, 6/17/00

;;; The constant `gfi-delimitter' is character used to separate fields in GFI
;;; files.  It is a <tab> character.

(defconstant gfi-delimitter #.%tab)


;;; The constant `gfi-designation-for-base-time' is a text string designating
;;; the base time in an event-log file.
;;; `Gfi-designation-for-base-time-string-length' gives its its length in
;;; characters.

(defconstant gfi-designation-for-base-time #w"the current time")
(defconstant gfi-designation-for-base-time-string-length
  (text-string-length gfi-designation-for-base-time))


;;; The constant `gfi-title-for-base-time' is a text string used for the base
;;; time in an spreadsheet file.  `gfi-title-for-base-time-string-length' gives
;;; its length in characters.

(defconstant gfi-title-for-base-time #w"BASE TIME:")
(defconstant gfi-title-for-base-time-string-length
  (text-string-length gfi-title-for-base-time))






;;; `Attribute-input-white-space' is a list of legal white-space in the
;;; attributes input-file, that is ignored.

(defconstant gfi-input-white-space '(#.%space #.%tab #.%return))

;; What's with Return being here and not Linefeed (or newline, if that's the
;; same)?! (MHD 2/23/96) -- See comment by attribute-input-white-space in
;; ATTRIBUTES. (MHD 6/17/00)

) ; closes progn & comment about change from (eval-when ...)






;;;; GFI Cons Pool:

(defconser gfi)






;;;; Structures for GFI:




;;; The structure `gfi-queue-item' is used to in queues of values for file
;;; output by the GFI Output Interface

(def-structure (gfi-queue-item)
  (gfi-queue-item-value nil :reclaimer reclaim-managed-number-or-value)
  (gfi-queue-item-g2-time nil :reclaimer reclaim-managed-number-or-value)
  gfi-queue-item-data-type
  (gfi-queue-item-designation? nil :reclaimer reclaim-gfi-tree)
  gfi-queue-item-position?
  (gfi-queue-item-variable nil)
  (gfi-queue-item-variable-name nil :reclaimer reclaim-if-text-string)
  (gfi-queue-item-variable-designation? nil :reclaimer reclaim-eval-tree)
  (gfi-queue-item-counter most-negative-fixnum))




;; The structure `gfi-time-structure' is used to store an absolute time in
;; terms of fixnums for day, month, year, hours, minutes, seconds.  It is used
;; to store time stamps when the time might be out of range of a fixnum.

;(def-structure (gfi-time-structure)
;  gfi-time-structure-seconds
;  gfi-time-structure-minutes
;  gfi-time-structure-hours
;  gfi-time-structure-day
;  gfi-time-structure-month
;  gfi-time-structure-year)

;; The above structure is obsolete in version 4.0.  - cpm, 7/5/94



;;; The hash table `gfi-spreadsheet-field-index' maps a frame
;;; serial number to an index number corresponding to the
;;; field for which GFI will output the variable.

(def-hash-table gfi-spreadsheet-field-index
		:hash-function-or-macro frame-hash-function
		:size 131) ; use a prime number






;;;; GFI System Variables




;;; The system variable `queue-of-active-gfi-output-interface-objects' is a
;;; queue-pair (i.e.  a cons of a list and and pointer to the tail of the list)
;;; of frames of active GFI Output Interface objects.  This queue is cycled
;;; through as each interface object is processed.

(def-system-variable queue-of-active-gfi-output-interface-objects gfi nil)


;;; The system variable `queue-of-active-gfi-input-interface-objects' is a
;;; queue-pair (i.e.  a cons of a list and and pointer to the tail of the list)
;;; of frames of active GFI Input Interface objects.  This queue is cycled
;;; through as each interface object is processed.

(def-system-variable queue-of-active-gfi-input-interface-objects gfi nil)


;;; The system variable
;;; `queue-of-active-uninterruptable-gfi-output-interface-objects' is a
;;; queue-pair (i.e.  a cons of a list and and pointer to the tail of the list)
;;; of frames of active GFI Output Interface objects.  Each object is processed
;;; until completion, without yielding for a time-slice expiration.  The
;;; uninterruptable queues (output and input) are processed before the other
;;; (interruptable) queues.  Unlike these other queues, all objects of this
;;; queue are processed once any time the queue is processed.

(def-system-variable
  queue-of-active-uninterruptable-gfi-output-interface-objects gfi nil)


;;; The system variable
;;; `queue-of-active-uninterruptable-gfi-input-interface-objects' is a
;;; queue-pair (i.e.  a cons of a list and and pointer to the tail of the list)
;;; of frames of active GFI Input Interface objects.  Each object is processed
;;; until completion, without yielding for a time-slice expiration.  The
;;; uninterruptable queues (input and output) are processed before the other
;;; (interruptable) queues.  Unlike these other queues, all objects of this
;;; queue are processed once any time the queue is processed.

(def-system-variable
  queue-of-active-uninterruptable-gfi-input-interface-objects gfi nil)


;;; The special variable `time-slice-expired-p' is the latest value of the macro
;;; (time-slice-expired-p) called within GFI.

(defvar time-slice-expired-p)






;;;; Queue Pairs And Queue Pairs Handling Functions And Macros




;;; A queue-pair is defined (within our context) as a cons of a queue-list and a
;;; pointer to the tail (last) of the queue-list.

(defmacro queue-list-of-queue-pair (queue-pair)
  `(car ,queue-pair))

(defmacro queue-tail-cons-of-queue-pair (queue-pair)
  `(cdr ,queue-pair))



;;; The macro `gfi-enqueue-in-pair' takes an item and puts it into the end of
;;; the queue in the queue-list of the queue-pair (ie. (<queue-list> .
;;; <pointer-to-tail-of-queue-list>)), and then updates the tail-pointer of the
;;; queue-pair to the new tail.

#-SymScale
(defmacro gfi-enqueue-in-pair (item queue-pair)
  (let ((queue-pair-name (gensym-make-symbol "QUEUE-PAIR-"))
	(new-cons (gensym-make-symbol "NEW-CONS-")))
    `(let* ((,new-cons (gfi-cons-macro ,item nil))
	    (,queue-pair-name ,queue-pair))
       (if (car-of-cons ,queue-pair-name)
	   (setf (cdr (cdr-of-cons ,queue-pair-name)) ,new-cons)
	   (setf (car ,queue-pair-name) ,new-cons))
       (setf (cdr ,queue-pair-name) ,new-cons))))

#+SymScale
(def-substitution-macro gfi-enqueue-in-pair (item queue-pair)
  (enqueue item (car queue-pair) (cdr queue-pair)
	   gfi-cons-macro))

;;; The macro `gfi-dequeue-from-pair' takes a queue-pair and returns the item at
;;; the front of the queue, and shortens the queue-pair list accordingly.

(def-substitution-macro gfi-dequeue-from-pair (queue-pair)
  ;; previous use of car-of-cons and cdr-of-cons cannot work with CAS
  (dequeue (car queue-pair) (cdr queue-pair)
	   reclaim-gfi-cons-macro))



;;; The macro `gfi-head-of-queue' takes a queue-pair and returns the item at the
;;; front of the queue without dequeueing it.

(defmacro gfi-head-of-queue (queue-pair)
  `(car (queue-list-of-queue-pair ,queue-pair)))



;;; The macro `gfi-tail-of-queue' takes a queue-pair and returns the item at the
;;; last item on the queue without dequeueing it.

(defmacro gfi-tail-of-queue (queue-pair)
  `(car (queue-tail-cons-of-queue-pair ,queue-pair)))




;;; The macro `gfi-tail-of-queue-if-any' takes a queue-pair and returns the item
;;; at the end of the queue, if there are items in the queue.  Note that the
;;; macro gfi-tail-of-queue is not necessarily accurate, since the tail pointer
;;; might still point to an entry, even though the head pointer has been cleared
;;; back to NIL.

(def-substitution-macro gfi-tail-of-queue-if-any (queue-pair)
  (if (queue-list-of-queue-pair queue-pair)
      (gfi-tail-of-queue queue-pair)
      nil))




;;; The macro `gfi-delete-from-queue' takes a key and a queue-pair and
;;; destructively deletes the first (front most) occurence of an item on the
;;; queue that is eq key.  NB: Only the first matching element is deleted.

(defun gfi-delete-from-queue (key queue-pair)
  (let* ((queue-list (queue-list-of-queue-pair queue-pair))
	 (delete-cons nil)
	 (cons-in-front-of-delete-cons nil))
    (if (eq key (car queue-list))
	(progn
	  (setq delete-cons queue-list)
	  (setf (car queue-pair) (cdr queue-list)))
	(loop with next-cons
	      with rest-of-list = queue-list
	      while rest-of-list
	      do
	  (when (setq next-cons (cdr rest-of-list)) ;if (not tail of queue-list)
	    (when (eq key (car next-cons))	    ;then check for match
	      (setq cons-in-front-of-delete-cons rest-of-list)
	      (setq delete-cons next-cons)
	      (setf (cdr rest-of-list) (cdr next-cons))
	      (return)))
	  (setq rest-of-list next-cons)))
    (when delete-cons				;If there's something to delete
      (if (eq (queue-tail-cons-of-queue-pair queue-pair) delete-cons)
	  (setf (cdr queue-pair) cons-in-front-of-delete-cons))
      (reclaim-gfi-cons-macro delete-cons)))
  queue-pair)






;;;; Gfi-output-interface




;;; Note on provisions for outputing binary files: To output binary files, we
;;; might want to examine the possiblily of encoding the designation so that it
;;; does not have to be repeated for each event-log entry.  The following
;;; functions are the places where writes occur:
;;;   accept-data-from-gfi-data-service,
;;;   gfi-output-spreadsheet-values-periodically, and
;;;   gfi-output-event-log-values-periodically.


;;; The user-accessible slots for GFI-OUTPUT-INTERFACE objects are:
;;; 	gfi-output-file-pathname     	::= nil | <string>
;;;     gfi-output-file-format		::= event-log | spreadsheet
;;;	gfi-output-time-stamp-format	::= explicit | relative
;;;	gfi-output-file-update-frequency ::= nil | when-received-value
;;;		    | (write-interval (<number> . seconds))
;;;		    | output-one-shot-when-activated
;;;		    | output-one-shot-when-activated-without-interruption
;;; 	gfi-output-values		::= nil |
;;;                                        (<list-of-designations?> . <text>)
;;;	maximum-number-of-output-lines	::= nil | number
;;;
;;; The unsaved (runtime) slots for GFI-OUTPUT-INTERFACE objects are:
;;;	gfi-outputting?         	::= nil | <non-nil>
;;; 	gfi-output-file-stream		::= nil | <IO-stream>
;;;	gfi-output-base-time		::= nil | <g2-time>, a managed-float
;;; 	gfi-output-scheduled-task	::= nil | <scheduled-task>
;;;     number-of-lines-output-so-far	::= nil | integer
;;;	new-gfi-output-values-this-cycle? ::= nil | <non-nil>
;;;	gfi-list-new-spreadsheet-output-values ::= nil | <list>
;;;	gfi-queue-of-new-output-values  ::= <queue-pair>
;;;     number-of-periodic-specified-designation-handled ::= nil | integer
;;;     gfi-output-without-interruption? ::= nil | t
;;;
;;; The new-gfi-output-values-this-cycle? can be <non-nil> only when
;;; gfi-output-file-update-frequency is 'when-received-value.
;;;
;;; A <queue-pair> is of the form:  ((item-1-1 item-1-2 ...) . tail-1).  In the
;;; gfi-queue-of-new-output-values, each item in the queue is a
;;; `gfi-queue-item', which is a def-structure.






;;;; GFI Queue Reclaimers




;;; The macro `reclaim-gfi-list-of-gfi-queue-items-macro' reclaims a list of
;;; gfi-queue-items.  It does not, however, reclaim the spine of the list it is
;;; given.
;;
;;; (reclaim-gfi-list-of-gfi-queue-items-macro list)

(defmacro reclaim-gfi-list-of-gfi-queue-items-macro (list)
  (let ((rest-of-list (gensym-make-symbol "REST-OF-LIST-"))
	(item (gensym-make-symbol "ITEM-")))
    `(loop with ,item
	   for ,rest-of-list on ,list
	   do
       (setq ,item (car ,rest-of-list))
       (if ,item (reclaim-gfi-queue-item ,item))
       (setf (car ,rest-of-list) nil))))



;;; The function `reclaim-gfi-queue-of-new-output-values-contents' flushes the
;;; given queue in the given queue-pair and reclaims all the managed values, or
;;; gfi-trees in the queue.

(defun reclaim-gfi-queue-of-new-output-values-contents (queue-pair)
  (let ((queue-list (queue-list-of-queue-pair queue-pair)))
    (when queue-pair
      (reclaim-gfi-list-of-gfi-queue-items-macro queue-list)
      (reclaim-gfi-list-macro queue-list)
      (setf (car queue-pair) nil)
      (setf (cdr queue-pair) nil))))



;;; The function `reclaim-gfi-queue-of-new-output-values' reclaims all the
;;; entries in the queue, and the queue itself.  Its arguments are the same as
;;; those of reclaim-gfi-queue-of-new-output-values-contents.

(defmacro reclaim-gfi-queue-of-new-output-values (queue-pair)
  (let ((pair (gensym-make-symbol "QUEUE-PAIR-")))
    `(let ((,pair ,queue-pair))
       (when ,pair
	 (reclaim-gfi-queue-of-new-output-values-contents ,pair)
	 (reclaim-gfi-cons-macro ,pair)))))






;;;; Slot Putters




;;; Slot putters: to prevent changing of slots when GFI-OUTPUT-INTERFACE
;;; is active.
;;;
;;; A slot putter:
;;;
;;;    (1) must set the slot, though it may complain (via frame notes or
;;;    notifications);
;;;
;;;    (2) must return what it actually stores, which may differ from the
;;;    argument it is given;
;;;
;;;    (3) may have various (non-cyclic) side effects, including the updating of
;;;    other  slots and of frame representation, which side effects are often
;;;    conditional on  whether or not this is an initialization case;
;;;
;;;    (4) may use and return the old value of the slot as a whole, but
;;;    otherwise should  not use any recyclable part of the old value for the
;;;    slot, unless it returns  a non-nil second value (which tells the
;;;    invoker not to reclaim the old value);
;;;
;;;    (5) should reclaim, as appropriate, any unused recyclable parts of the
;;;    value it  is given.  (Documentation abstracted from FRAMES1.)




;;; The macros `gfi-output-slot-putter-wrapper' and
;;; `gfi-input-slot-putter-wrapper' are used to wrap the body of some gfi-output
;;; and gfi-input slot-putters, which can affect the status of the gfi interface
;;; object.

;;; Changes to these slots may cause one or both of the following:
;;; - close a currently active, output object that is data-serving values
;;; - open an active, output object, if necessary, after the edit is made.

;;; Note that previous to 5.0, changes could not made to these slots
;;; unless G2 was reset.

;;; This macro returns the values required of a slot putter.

(defmacro gfi-output-slot-putter-wrapper
    ((frame new-value slot-name) &body body)
  (let ((frame-var (gensym))
	(new-value-var (gensym))
	(slot-name-var (gensym)))
    `(let* ((,frame-var ,frame)
	    (,new-value-var ,new-value)
	    (,slot-name-var ,slot-name))
       (when (and (active-p ,frame-var)
		  (gfi-output-when-active ,frame-var)
		  (gfi-outputting? ,frame-var))
	 ;; Close the output interface object.
	 (close-gfi-output-interface ,frame-var t))
       (set-slot-value ,frame-var ,slot-name-var ,new-value-var)
       ,@body
       (when (and (active-p ,frame-var)
		  (gfi-output-when-active ,frame-var)
		  (frame-ok-p, frame-var))
	 ;; Prepare to open the output interface object.  Note that the
	 ;; open-gfi-output-interface is then called in the function
	 ;; accept-data-from-gfi-data-service.
	 (prepare-gfi-output-interface-to-open ,frame-var))
       (values ,new-value-var nil))))

(defmacro gfi-input-slot-putter-wrapper
    ((frame new-value slot-name) &body body)
  (let ((frame-var (gensym))
	(new-value-var (gensym))
	(slot-name-var (gensym)))
    `(let* ((,frame-var ,frame)
	    (,new-value-var ,new-value)
	    (,slot-name-var ,slot-name))
       (when (and (active-p ,frame-var)
		  (gfi-input-when-active ,frame-var)
		  (gfi-inputting? ,frame-var))
	 ;; Close the input interface object, if open.
	 (close-gfi-input-interface ,frame-var))
       (set-slot-value ,frame-var ,slot-name-var ,new-value-var)
       ,@body
       (when (and (active-p ,frame-var)
		  (gfi-input-when-active ,frame-var)
		  (frame-ok-p, frame-var))
	 ;; Prepare to open the input interface object.  Note that the
	 ;; open-gfi-intput-interface is then called in the function
	 ;; accept-data-from-gfi-data-service.
	 (prepare-gfi-input-interface-to-open ,frame-var))
       (values ,new-value-var nil))))



(def-slot-putter gfi-output-file-pathname (frame new-value)
  (gfi-output-slot-putter-wrapper
    (frame new-value 'gfi-output-file-pathname)
    ;; Update the frame status and notes, if the value is set.
    (cond
      ((null new-value)
       (add-frame-note 'no-gfi-output-file-pathname frame)
       (update-frame-status frame 'incomplete nil))
      (t
       (delete-frame-note-if-any 'no-gfi-output-file-pathname frame)
       (when (gfi-output-interface-non-default-slots-set-p frame)
	 (update-frame-status frame nil nil))))))

(def-slot-putter renamed-gfi-output-file-pathname (frame new-value)
  (gfi-output-slot-putter-wrapper
    (frame new-value 'renamed-gfi-output-file-pathname) nil))

(def-slot-putter gfi-output-file-format (frame new-value)
  (gfi-output-slot-putter-wrapper
    (frame new-value 'gfi-output-file-format) nil))

(def-slot-putter gfi-output-time-stamp-format (frame new-value)
  (gfi-output-slot-putter-wrapper
    (frame new-value 'gfi-output-time-stamp-format) nil))


(def-slot-putter gfi-output-file-update-frequency (frame new-value)
  (gfi-output-slot-putter-wrapper
    (frame new-value 'gfi-output-file-update-frequency)
    ;; Update the frame status and notes, if the value is set.
    (cond
      ((null new-value)
       (add-frame-note 'no-gfi-output-update-frequency frame)
       (update-frame-status frame 'incomplete nil))
      (t
       (delete-frame-note-if-any 'no-gfi-output-update-frequency frame)
       (when (gfi-output-interface-non-default-slots-set-p frame)
	 (update-frame-status frame nil nil))
       (if (eq new-value
	       'output-one-shot-when-activated-without-interruption)
	   (change-slot-value frame 'gfi-output-without-interruption? t)
	   (change-slot-value frame 'gfi-output-without-interruption? nil))))))


(defun-substitution-macro
  reclaim-gfi-output-not-unique-designation-p-results-if-any (gfi-output-frame)
  (when (gfi-output-not-unique-designation-p-results gfi-output-frame)
    (reclaim-gfi-list
      (gfi-output-not-unique-designation-p-results gfi-output-frame))
    (setf (gfi-output-not-unique-designation-p-results gfi-output-frame) nil)))



;;; The defun-substitution-macro `recompute-not-unique-designation-p-results'
;;; takes a GFI Output Interface and a list of new output value designations and
;;; replace the old list of results with the new one.

(defun-substitution-macro recompute-not-unique-designation-p-results
			  (gfi-output-frame designations)
  (reclaim-gfi-output-not-unique-designation-p-results-if-any
    gfi-output-frame)
  (loop with new-not-unique-designation-p-results = nil
	with tail-of-not-unique-designation-p-results = nil
	for designation in designations
	do
    (enqueue-1 (not (unique-designation-p designation))
	     new-not-unique-designation-p-results
	     tail-of-not-unique-designation-p-results
	     gfi-cons)
	finally
	  (setf (gfi-output-not-unique-designation-p-results gfi-output-frame)
		new-not-unique-designation-p-results)))


(def-slot-putter gfi-output-values (frame new-value)
  (gfi-output-slot-putter-wrapper
    (frame new-value 'gfi-output-values)
    (recompute-not-unique-designation-p-results frame (car new-value))
    ;; Update the frame status and notes, if the value is set.
    (cond
      ((or (null new-value)
	   ;; Text slot, where the first value is the list of values and should
	   ;; be non-NULL.
	   (and (listp new-value)
		(null (first new-value))))
       (add-frame-note 'no-gfi-output-values frame)
       (update-frame-status frame 'incomplete nil))
      (t
       (delete-frame-note-if-any 'no-gfi-output-values frame)
       (when (gfi-output-interface-non-default-slots-set-p frame)
	 (update-frame-status frame nil nil))))))


(def-slot-putter gfi-output-when-active (frame new-value)
  (gfi-output-slot-putter-wrapper
    (frame new-value 'gfi-output-when-active) nil))


;;; The `file-status slot putter' is used by GFI output and input interface
;;; objects to invoke forward chaining.  This system attribute can be
;;; referenced, but not set, by the user in rules.

(def-slot-putter file-status (interface-object status-symbol initializing?)
  (declare (ignore initializing?))
  (let ((old-status (get-slot-value interface-object 'file-status)))
    (set-slot-value interface-object 'file-status status-symbol)
    (invoke-rules-for-attribute-change-chaining
      interface-object 'file-status old-status nil)
    (values status-symbol nil)))






;;;; GFI Output Slot Value Reclaimers


(def-slot-value-reclaimer gfi-output-values (slot-value frame)
  (setf (gfi-output-values frame) nil)
  (reclaim-slot-value slot-value))



(def-slot-value-reclaimer gfi-list-of-new-spreadsheet-output-values
			  (slot-value frame)
  (setf (gfi-list-of-new-spreadsheet-output-values frame) nil)
  (when (listp slot-value)
    (loop for managed-value? in slot-value
	  do
      (if managed-value?
	  (reclaim-managed-number-or-value managed-value?)))
    (reclaim-gfi-list slot-value)))



(def-slot-value-reclaimer gfi-output-not-unique-designation-p-results
    (value? frame)
  (setf (gfi-output-not-unique-designation-p-results frame) nil)
  (when value?
    (reclaim-gfi-list value?)))

(def-slot-value-reclaimer gfi-output-spreadsheet-field-index-hash (value? frame)
  (setf (gfi-output-spreadsheet-field-index-hash frame) nil)
  (when value?
    (reclaim-gfi-spreadsheet-field-index value?)))

(def-slot-value-reclaimer gfi-output-unique-designations
    (value gfi-output-frame)
  (setf (gfi-output-unique-designations gfi-output-frame) nil)
  (when value
    (reclaim-eval-tree value)))













;;;; Variables Updating Code




;;; The function `warning-message-for-wrong-reference-for-gfi-designation'
;;; prints a warning message on the Logbook informing the user that a reference
;;; was made to a non-variable (where thing-that-should-be-variable is returned
;;; by the place-evaluate of the designation-that-should-refer-to-variable).

(defun warning-message-for-wrong-reference-for-gfi-designation
       (gfi-output-frame
	designation-that-should-refer-to-variable
	thing-that-should-be-variable)
  (if (framep thing-that-should-be-variable)
      (warning-message
	2
	"~ND is not a variable or parameter, but it was specified ~
	 as an output value for the GFI Output Interface ~NF."
	designation-that-should-refer-to-variable
	gfi-output-frame)
      (warning-message
	2
	"Could not find the value of ~ND in the GFI Output Interface ~NF."
	designation-that-should-refer-to-variable
	gfi-output-frame)))

;; Shouldn't this print thing-that-should-be-variable (using ~NF)?  That
;; would let users see what the designation designates!  (MHD 2/6/92)



(defun warning-message-for-unnameable-variable
       (gfi-output-frame name-or-variable-or-parameter designation?)
  (let ((designation-or-substitute-string
	  (tformat-text-string
	    (if designation? "\"~ND\"" "a designation in the GFI interface")
	    designation?)))
    (warning-message
      2
      "The GFI Output Interface ~NF found a variable or parameter, ~
       ~NF, which matches ~A.  However, the variable cannot be ~
       referenced with respect to a named item, and thus will be ~
       ignored by GFI."
      gfi-output-frame
      name-or-variable-or-parameter
      designation-or-substitute-string)
    (reclaim-text-string designation-or-substitute-string)))

;; Review enclosing of designation in double quotes above; it is not a standard,
;; although I believe we do need something like that.  Also review use of the
;; term "Designation"! (MHD 2/5/92)

;; Review capitalization in "GFI Output Interface". (MHD 2/5/92)



(defun warning-message-for-non-frame-reference-for-gfi-designation
       (gfi-output-frame temporary-constant?)
  (if (temporary-constant-p temporary-constant?)
      (warning-message*
	2
	"~NC is not a variable or parameter.  This output value for the ~
         GFI Output Interface, ~NF, cannot be written."
	(cached-constant-value temporary-constant?)
	(constant-type temporary-constant?)
	gfi-output-frame)
      (warning-message*
	2
	"The GFI Output Interface, ~NF, cannot write a value.  The output ~
         value was not a variable or parameter."
	gfi-output-frame)))



;;; The function `install-gfi-true-value-update' calls install-true-value-update
;;; to either enable or disable the list of designations it is given for the
;;; specified GFI Output frame.  When an installation occurs (as opposed to a
;;; deinstallation), an eval list of designations is returned.  This list
;;; corresponds to the unique designations corresponding to the columns of the
;;; spreadsheet, if it is used.
;;;
;;; This function also modifies the argument not-unique-designation-results so
;;; as to give the number of unique designations which match the generic
;;; designations for each position in not-unique-designation-results.

(defun install-gfi-true-value-update
       (gfi-output-frame e-designations not-unique-designation-results)
  (let* ((number-of-unique-designations 0)
	 (install?
	   (interrupt-driven-gfi-file-update-frequency-p
             (gfi-output-file-update-frequency gfi-output-frame)))
	 (hash-table?
	   (gfi-output-spreadsheet-field-index-hash gfi-output-frame))
	 (eval-list-of-designations-for-installing nil)
	 (tail-of-eval-list-of-designations-for-installing nil))
    (declare (type fixnum number-of-unique-designations))
    (when (not hash-table?)
      (setq hash-table? (make-gfi-spreadsheet-field-index))
      (setf (gfi-output-spreadsheet-field-index-hash gfi-output-frame)
	    hash-table?))
    (clear-gfi-spreadsheet-field-index hash-table?)
    (loop with position = 0
	  with designation-position-pair = (gfi-cons nil nil)
	  for designation in e-designations
	  as rest-of-not-unique-designation-results on not-unique-designation-results
	  as not-unique-designation-p = (car rest-of-not-unique-designation-results)
	  ;; usually, e-designations = (car (gfi-output-values gfi-output-frame))
	  do
      (setf (car designation-position-pair) designation)
      ;; We have to call serve-eval-list-of-designation-values for
      ;; each generic designation and assign each a position number,
      ;; caching the variables in a hash table.  Unique designations
      ;; can be handled similarly, but a distinction should be made between
      ;; generic and unique designation so as to allow us to print the
      ;; designatzion specified by the user for unique designations instead
      ;; of using generate-designation-for-block (which will be required for
      ;; generic designations).
      (cond
	;; If it is a unique designation, the field position (index) is given
	;; in the designation-position-pair,
	(not-unique-designation-p
	 (setf (cdr designation-position-pair) nil)
	 (setq number-of-unique-designations 0)
	 (loop with eval-list-of-designation-values
		 = (let* ((*current-computation-frame* gfi-output-frame))
		     (serve-eval-list-of-designation-values designation))
	       for designation-value in eval-list-of-designation-values
	       do
	   (cond
	     ((and (framep designation-value)
		   (variable-or-parameter-p designation-value))
	      (let* ((generated-designation?
		       (generate-designation-for-block designation-value)))
		(cond
		  (generated-designation?
		   (set-gfi-spreadsheet-field-index-hash-value
		     designation-value
		     hash-table?
		     position)
		   (enqueue-1 generated-designation?
			    eval-list-of-designations-for-installing
			    tail-of-eval-list-of-designations-for-installing
			    eval-cons)
		   (incff number-of-unique-designations)
		   (incff position))
		  (t
		   (warning-message-for-unnameable-variable
		     gfi-output-frame
		     designation-value
		     designation)))))
	     (t
	      (warning-message-for-wrong-reference-for-gfi-designation
		gfi-output-frame designation designation-value)
	      (reclaim-if-temporary-constant-function
		designation-value)))
	       finally
		 (reclaim-eval-list eval-list-of-designation-values))
	 (setf (car rest-of-not-unique-designation-results)
	       number-of-unique-designations))
	;; Otherwise, the designation-position-pair gives nil for the
	;; field index, but the position of each variable or parameter given by the
	;; designation is hashed (using gfi-output-frame serial number) is hashed into the
	;; gfi-output-spreadsheet-field-index-hash.
	(t
	 (setf (cdr designation-position-pair) position)
	 (enqueue-1 (copy-tree-using-eval-conses designation)
		  eval-list-of-designations-for-installing
		  tail-of-eval-list-of-designations-for-installing
		  eval-cons)
	 (incff position)))
      (when install?
;	(format t "~&install: ~A, ~A"
;		designation-position-pair
;		designation)
	(install-true-value-update
	  'handle-gfi-output-interface-new-values
	  gfi-output-frame
	  designation-position-pair    ;install-true-value-update will copy this
	  nil
	  designation))
	  finally
	    (reclaim-gfi-cons designation-position-pair))
    eval-list-of-designations-for-installing))






;;; The function `deinstall-gfi-true-value-update' undoes what
;;; install-gfi-true-value-update does.  This function does nothing
;;; if interrupt-driven-gfi-file-update-frequency-p, when applied to the
;;; GFI Output Interface it is given, returns nil.
;;;
;;; Each entry in the list of the argument not-unique-designation-results must
;;; contain either nil or a number corresponding to the number of matching
;;; variables or parameter (generated by install-gfi-true-value-update).

(defun deinstall-gfi-true-value-update
       (gfi-output-frame e-designations not-unique-designation-results)
  (when (interrupt-driven-gfi-file-update-frequency-p
	  (gfi-output-file-update-frequency gfi-output-frame))
    (loop with position = 0
	  with designation-position-pair = (gfi-cons nil nil)
	  for e-designation in e-designations
	  as not-unique-designation-p in not-unique-designation-results
	  do
      (setf (car designation-position-pair) e-designation)
      (cond
	(not-unique-designation-p
	 (setf (cdr designation-position-pair) nil)
	 (incff position not-unique-designation-p))
	;; Otherwise, the designation-position-pair gives nil for the
	;; field index, but the position of each variable or parameter given by the
	;; designation is hashed (using gfi-output-frame serial number) is hashed into the
	;; gfi-output-spreadsheet-field-index-hash.
	(t
	 (setf (cdr designation-position-pair) position)
	 (incff position)))
;      (format t "~&deinstall: ~A, ~A"
;	      designation-position-pair
;	      e-designation)
      (install-true-value-update
	'handle-gfi-output-interface-new-values
	gfi-output-frame
	designation-position-pair		;install-true-value-update will copy this
	e-designation
	nil)
	  finally
	    (reclaim-gfi-cons designation-position-pair))))







;;; The macro `get-current-value-without-side-effects-wrapper' calls
;;; get-current-value with the appropriate wrappers and variables bound.  The
;;; body of the code is executed and the temporary values are reclaimed.  The
;;; three parameters current-value, expiration-time, and data-type are bounded,
;;; and should be declared as ignored in the body if they are not used.  The
;;; parameter variable should refer to a variable frame, and the three
;;; parameters should be used to refer to the respective values returned by
;;; get-current-value within the wrapper.  Note that an error will occur if the
;;; parameter variable is not a variable.

(defmacro get-current-value-without-side-effects-wrapper
	  ((variable current-value expiration-time data-type) &body body)
  (if (not (and (symbolp current-value)
		(symbolp expiration-time)
		(symbolp data-type)))
      (error "Error:  get-current-value-without-side-effects-wrapper must get ~
              symbols for the current-value, expiration-time, and data-type."))
  `(let* ((*current-computation-frame* ,variable)
	  (current-computation-instance *current-computation-frame*)
	  (current-computation-flags current-computation-flags))
     (setf (force-new-request-for-value) nil)
     (setf (dont-compute-new-variable-values) t)
     (with-wake-up-management (none nil nil)
       (with-temporary-gensym-float-creation
	 get-current-value-without-side-effects-wrapper
	 (multiple-value-bind (,current-value ,expiration-time ,data-type)
	     (get-current-value *current-computation-frame* nil)
	   ,@body
	   (if (and expiration-time (text-string-p ,current-value))
	       (reclaim-text-string ,current-value)))))))




;;; The function `get-pathname-for-gfi-interface' takes a GFI Output Interface
;;; object and returns the pathname in the slot as indicated by the specified
;;; slot name.  If the contents of the slot is a string, then the string is
;;; returned.  If the contents of the slot is a designation, then the value of
;;; the designation is returned if it is a text string.  Nil is returned if no
;;; string can be returned.  The text string that is returned should be
;;; reclaimed.

(defun-allowing-unwind get-pathname-for-gfi-interface
		       (gfi-interface-frame slot-name-for-pathname)
  (let* ((pathname
	   (get-slot-value gfi-interface-frame slot-name-for-pathname)))
    (cond
      ((text-string-p pathname)
       (copy-text-string pathname))	; charset translation here?! (MHD 2/23/96)
      ((designation-p pathname)
       (let* ((*current-computation-frame* gfi-interface-frame)
	      (value-to-return nil))
	 (let* ((parameter-or-variable?
		  (evaluate-designation pathname nil)))
	   (cond
	     (parameter-or-variable?
	      (get-current-value-without-side-effects-wrapper
		(parameter-or-variable? current-value expiration-time data-type)
		(cond
		  ((and expiration-time
			(eq data-type 'text)
			(text-string-p current-value))
		   (if (not (string-equalw current-value #w""))
		       (setq value-to-return
			     (copy-text-string current-value) ; charset translation here?! (MHD 2/23/96)
			     )))
		  ((and expiration-time
			(eq data-type 'symbol)
			(eq current-value 'none))
		   ;; nil will be returned in this case.
		   )
		  (t
		   (warning-message
		     2
		     "The variable or parameter which is supposed to hold a ~
	 	      pathname in the GFI ~A Interface ~NF, ~ND, does not ~
		      have a valid value.  (It should be a string.)"
		     (if (eq slot-name-for-pathname 'gfi-input-file-pathname)
			 #w"Input"
			 #w"Output")
		     gfi-interface-frame pathname)))))
	     (t	      
	      (warning-message
		2
		"The variable or parameter which is supposed to hold a ~
 		 pathname in the GFI ~A Interface ~NF, ~ND, does not exist."
		(if (eq slot-name-for-pathname 'gfi-input-file-pathname)
		    #w"Input"
		    #w"Output")
		gfi-interface-frame pathname))))
	 value-to-return))
      (t
       #+development
       (warning-message
	 2
	 "Tried to open a file with the ~A slot of ~
	  the GFI Output Interface ~NF incorrectly set."
	 slot-name-for-pathname
	 (if (eq slot-name-for-pathname 'gfi-input-file-pathname)
	     #w"Input"
	     #w"Output")
	 gfi-interface-frame)
       nil))))





;;; The function `warning-message-for-limit-reached-in-gfi-output' prints a
;;; warning message to tell the user that gfi-output-frame, a GFI Output
;;; Interface, will no longer output any more data because the
;;; maximum-number-of-output-lines has been reached.

;;; This also closes gfi-output-frame without flushing pending output.

(defun warning-message-for-limit-reached-in-gfi-output (gfi-output-frame)
  (warning-message 2
    "Maximum number of output lines has been reached for GFI Output ~
     Interface ~NF.  No more outputs will be made."
    gfi-output-frame)
  (close-gfi-output-interface gfi-output-frame nil))






;;; The function `prepare-gfi-output-frame' performs the following
;;; initializations to prepare for a gfi output interface frame:  (a) set the
;;; base time, (b) make a blank list of GFI-conses to be filled in by values to
;;; be output, (c) ensures that the GFI scheduled task is nil, and (d) set the
;;; line count to 0.

(defun-substitution-macro prepare-gfi-output-frame (gfi-output-frame)
  ;; Set the base time
  (with-temporary-gensym-float-creation
      prepare-gfi-output-frame
    ;; Keep the phase of the base-time on the second.  Storing as a float, and
    ;; not an integer, because this number could be larger than a fixnum.
    (setf (gfi-output-base-time gfi-output-frame)
	  (allocate-managed-float
	    (ffloore-first (managed-float-value (clock-get current-g2-time))))))

  ;; Ensure that scheduled task is nil.  This is needed because when this frame
  ;; is first used, a nil might be expected.
  (setf (gfi-output-scheduled-task gfi-output-frame) nil)

  ;; Initialize the line count
  (setf (number-of-lines-output-so-far gfi-output-frame) 0)

  ;; No values queued to be output.  New-gfi-output-values-this-cycle? can be
  ;; <non-nil> only when gfi-output-file-update-frequency is
  ;; 'when-received-value.
  (setf (new-gfi-output-values-this-cycle? gfi-output-frame) nil)


  (let* ((list-of-output-designations
	   (install-gfi-true-value-update
	     gfi-output-frame
	     (car (gfi-output-values gfi-output-frame))
	     (gfi-output-not-unique-designation-p-results gfi-output-frame))))
    ;; Set up true value updates:
    (change-slot-value				; need to reclaim old value
      gfi-output-frame
      'gfi-output-unique-designations
      list-of-output-designations)
    
    ;; Set the list or queues of values to be output
    (let ((designations
	    (car (gfi-output-values gfi-output-frame))))
      (when designations
	(setf (gfi-queue-of-new-output-values gfi-output-frame)
	      (gfi-cons nil nil))
	(if (eq (gfi-output-file-format gfi-output-frame) 'spreadsheet)
	    (loop with queue-of-values = nil
		  repeat (length list-of-output-designations)
		  do
	      (setq queue-of-values (gfi-cons nil queue-of-values))
		  finally
		    (setf (gfi-list-of-new-spreadsheet-output-values
			    gfi-output-frame) queue-of-values)
		    (return queue-of-values)))))))







;;; The function `open-gfi-output-interface' takes a GFI output object either
;;; opens the apropriate output file for it, or gives a warning message and
;;; terminate the GFI output.  This function returns nil if it unable to open
;;; the output file or t if it is able.

(defun open-gfi-output-interface (gfi-output-frame)
  (setf (gfi-outputting? gfi-output-frame) nil)
  (execute-body-if-gfi-is-authorized
    (let* ((pathname? (get-pathname-for-gfi-interface
			gfi-output-frame 'gfi-output-file-pathname)))
      (when pathname?
	(setf (gfi-output-pathname-string-of-stream? gfi-output-frame)
	      pathname?)
	(setf (gfi-output-file-stream gfi-output-frame)
	      (g2-stream-open-for-output pathname?)))
      ;; Might want to be smarter with the file pathname above.
      (cond
	((and pathname?
	      (g2-stream-p (gfi-output-file-stream gfi-output-frame)))
	 (setf (gfi-outputting? gfi-output-frame) t)
	 (prepare-gfi-output-frame gfi-output-frame)
	 (write-gfi-output-file-header gfi-output-frame)
	 (schedule-gfi-output-tasks gfi-output-frame)
	 (change-slot-value gfi-output-frame 'file-status 'open)
	 t)
	(t
	 (change-slot-value gfi-output-frame 'file-status 'failed-to-open)
	 (when pathname?
	   (let ((error-text (most-recent-file-operation-status-as-text)))
	     (warning-message
		 2 "Could not open output file ~S for ~NF:  ~A."
	       pathname?
	       gfi-output-frame
	       error-text)
	     (reclaim-text-string error-text)))
	 (close-gfi-output-interface gfi-output-frame nil)
	 nil)))))







;;; The function `handle-gfi-output-interface-new-values' is an update function
;;; passed to install-true-value-update.  Whenever a value which matches the
;;; designation of a variable that receives a new value, handle-gfi-output-
;;; interface-new-values will be called.

;;; If the GFI Output Interface is outputting (the gfi-outputting? slot is t)
;;; and the gfi-output-file-update-frequency is 'when-receive-values, this
;;; function will place the new value on a queue in the gfi-output-frame (in the
;;; gfi-queue-of-new-output-values), and at the end of every clock-tick,
;;; accept-data-from-gfi-data-service will check the queue for new values, and
;;; output the new values.  It is the duty of accept-data-from-gfi-data-service
;;; (the outputing function) to reclaim the queued item.  The
;;; new-gfi-output-values-this-cycle? slot of the GFI Output Interface will be
;;; set to T; accept-data-from-gfi-data-service will have to reset it to nil
;;; when it has output and reclaimed all queued items.  This function has to be
;;; very fast.

;;; A note on the the functions that handle queues for value-time pairs:
;;; prepare-gfi-output-frame initializes the queues,
;;; handle-gfi-output-interface-new-values queues value-time pairs,
;;; accept-data-from-gfi-data-service dequeues value-time pairs, and the
;;; capability-deactivator for gfi-output-interface reclaims queues of
;;; value-time pairs (using the function
;;; reclaim-gfi-queue-of-new-output-values).

#+development
(defvar *last-gfi-queue-item* nil)

(defun-allowing-unwind handle-gfi-output-interface-new-values
    (gfi-output-frame designation-position-pair variable attribute? old-value
		      class-if-specific?)
  (declare (ignore attribute? old-value class-if-specific?))
  (when (gfi-outputting? gfi-output-frame)
    (cond
      ((variable-or-parameter-p variable)
       (get-current-value-without-side-effects-wrapper
	   (variable current-value expiration-time data-type)
	 (when expiration-time
	   (let (managed-current-value
		  (queue-item (make-gfi-queue-item))
		  (position? (cdr designation-position-pair))
		  (spreadsheet-format?
		    (eq (gfi-output-file-format gfi-output-frame) 'spreadsheet)))
	     (store-managed-number-or-value managed-current-value
					    current-value)
	     (setf (gfi-queue-item-value queue-item) managed-current-value)
	     (setf (gfi-queue-item-data-type queue-item) data-type)
	     (setf (gfi-queue-item-g2-time queue-item)
		   (copy-managed-float (clock-get current-g2-time)))
	     (cond
	       (position?
		;; If non-generic designation, then only require
		;; the designation if not a spreadsheet format.
		(when (not spreadsheet-format?)
		  (setf (gfi-queue-item-designation? queue-item)
			(copy-tree-using-gfi-conses
			  (car designation-position-pair)))))
	       (t
		;; If a generic designation, need to generate a designation
		;; for it.
		(setf (gfi-queue-item-variable-designation? queue-item)
		      (generate-designation-for-block variable))))
	     (setf (gfi-queue-item-position? queue-item)
		   position?)
	     (setf (gfi-queue-item-variable queue-item)
		   variable)
	     (let ((user-visible-designation
		     (get-or-make-up-designation-for-block variable)))
	       (when (text-string-p user-visible-designation)
		 (setq user-visible-designation
		       (copy-text-string user-visible-designation)))
	       (setf (gfi-queue-item-variable-name queue-item)
		     user-visible-designation))
	     (let* ((queue-pair (gfi-queue-of-new-output-values
				  gfi-output-frame))
		    (last-queue-item?
		      (gfi-tail-of-queue-if-any queue-pair)))
	       (when last-queue-item?
		 (setf (gfi-queue-item-counter queue-item)
		       (+f (gfi-queue-item-counter last-queue-item?) 1)))
	       (gfi-enqueue-in-pair queue-item queue-pair)
	       (setf (new-gfi-output-values-this-cycle? gfi-output-frame) t)
	       ;; Check if the output queue is overfilling.  If so, perform
	       ;; some work to flush it out to its file.  The output function
	       ;; is guaranteed to flush at least one line.
	       (when (and
		       (>=f (-f (gfi-queue-item-counter
				  (gfi-tail-of-queue queue-pair))
				(gfi-queue-item-counter
				  (gfi-head-of-queue queue-pair)))
			    maximum-gfi-output-queue-count)
		       (or
			 ;; Event file format is written on separate lines, even
			 ;; when they are the same timestamp.  So, this does not
			 ;; need to check the times of the queued values.
			 (not spreadsheet-format?)
			 ;; This keeps "reading" from getting too far ahead
			 ;; of "writing" (without limiting spreadsheet output
			 ;; to a fixed maximum number of columns).
			 ;; Only output "complete" lines of spreadsheet
			 ;; values (after values for next second are being
			 ;; collected and if the usual accept output from
			 ;; accept-data-from-gfi-data-service has not yet
			 ;; occurred).
			 ;; See note 1 below.  - cpm, 5/2/95
			 (with-temporary-gensym-float-creation
			     output-gfi-queued-values-in-spreadsheet-format
			   ;; See note 2 below.
			   (>e (ffloore-first
				 (managed-float-value
				   (gfi-queue-item-g2-time
				     (gfi-tail-of-queue queue-pair))))
			       (ffloore-first
				 (managed-float-value
				   (gfi-queue-item-g2-time
				     (gfi-head-of-queue queue-pair))))))))
	       (output-gfi-queued-values-to-stream
		 gfi-output-frame 1)))
	   #+development (setq *last-gfi-queue-item* queue-item)
	   )))
      #+development
*last-gfi-queue-item*)
      (t
       (warning-message-for-wrong-reference-for-gfi-designation
	 gfi-output-frame (car designation-position-pair) variable)))))

;; Note 1: This test of timestamps was added for the following reason.  A
;; customer ran into a situation where they were trying to output more than 100
;; spreadsheet values, but were only able to do some on multiple lines (with the
;; same timestamp).  This is a problem and defeats the purpose of using
;; spreadsheet format!  A fix was made so that after the spreadsheet values
;; collected reaches this maximum, then the function starts to check if it has
;; all the values for the given second (timestamp).  When it does it then ouputs
;; all the values for that line.  (Previously, it would only output up to the
;; maximum.)  In this way, the spreadsheet output is bounded (i.e., not more
;; than one second of values will be waiting to output), but not based on a
;; fixed number of columns.  - cpm, 5/2/95

;; Note 2: Another approach of testing the time stamps was considered (taking
;; the difference of the two times and comparing it against 1.0).  This may be
;; more efficient, but does not always distinguish between values collected in
;; the next second.  For example, times of 1.9 and 2.1 would not be counted in
;; the next second.  Therefore, the two floor operations are needed.  - cpm,
;; 5/2/95






;;;; Time Stamp Printing Functions:




;;; The function `tprint-gfi-time-stamp' prints a text string containing the
;;; explicit time-stamp corresponding to the explicit g2-time specified.

(defun tprint-gfi-time-stamp (g2-time-to-print)
  (with-temporary-gensym-float-creation
      tprint-gfi-time-stamp
    (let* ((g2-time-float
	     (if (managed-float-p g2-time-to-print)
		 (managed-float-value g2-time-to-print)
		 ;; gensym-float
		 g2-time-to-print))
	   (second-fraction-float
	     (-e g2-time-float (ffloore-first g2-time-float)))
	   (subsecond-time?
	     (if (/=e second-fraction-float 0.0)
		 second-fraction-float)))
      (multiple-value-bind (seconds minutes hours day month year)
	  (gensym-decode-unix-time g2-time-float)
	(if subsecond-time?
	    (setq seconds (+e (coerce-fixnum-to-gensym-float seconds)
			      subsecond-time?)))
	(print-decoded-time seconds minutes hours day month year)))))



;;; The macro `output-gfi-explicit-time-stamp-to-stream-macro' takes a g2-time
;;; time, and an output stream, and outputs the explicit time stamp, dd Mmm yyyy
;;; hh:mm:ss[.x], into the output stream.  (Where "x" is the possible subsecond
;;; part of the time-stamp, which may be 1 or more digits.)  The function
;;; returns result of the g2-stream-write-string operation used to output the
;;; time-stamp.

(defmacro output-gfi-explicit-time-stamp-to-stream-macro
       (g2-time-to-print gfi-output-frame)
  (let ((time (gensym))
	(frame (gensym))
	(time-stamp (gensym)))
    `(let* ((,time ,g2-time-to-print)
	    (,frame ,gfi-output-frame)
	    (,time-stamp
	     (twith-output-to-text-string
	       (tprint-gfi-time-stamp ,time))))
    (prog1
      (gfi-write-string ,time-stamp ,frame)
      (reclaim-text-string ,time-stamp)))))



;;; The function `output-gfi-explicit-time-stamp-to-stream' is simply a macro
;;; version of output-gfi-explicit-time-stame-to-stream-macro.

(defun output-gfi-explicit-time-stamp-to-stream (g2-time-to-print gfi-output-frame)
  (output-gfi-explicit-time-stamp-to-stream-macro
    g2-time-to-print gfi-output-frame))



;;; The function `output-appropriate-gfi-time-stamp' prints either the explicit
;;; time-stamp or a relative time stamp as specified by the gfi output interface
;;; object.  The function returns the result of calling g2-stream-write-string
;;; to output the time-stamp.

(defun output-appropriate-gfi-time-stamp (gfi-output-frame g2-time-to-print)
  (if (eq (gfi-output-time-stamp-format gfi-output-frame) 'explicit)
      (output-gfi-explicit-time-stamp-to-stream-macro
	g2-time-to-print gfi-output-frame)
      (with-temporary-gensym-float-creation
	  output-appropriate-gfi-time-stamp
	(let* ((relative-time
		 (-e (if (managed-float-p g2-time-to-print)
			 (managed-float-value g2-time-to-print)
			 ;; gensym-float
			 g2-time-to-print)
		     (managed-float-value
		       (gfi-output-base-time gfi-output-frame))))
	       (relative-time-stamp
		 (twith-output-to-text-string
		   (if (=e relative-time (ffloore-first relative-time))
		       ;; Write time as "n" if equal to "n.0".  The user may be
		       ;; writing all times on the second.  This would then give
		       ;; the same behavior as version 3.0, which did not have
		       ;; subsecond times.
		       (twrite-fixnum (floore-first relative-time))
		       (twrite-float relative-time)))))
	  (prog1
	      (gfi-write-string
		relative-time-stamp gfi-output-frame)
	    (reclaim-text-string relative-time-stamp))))))






;;;; Gfi-Output-Interface Activation




(def-class-method initialize (gfi-output-interface)
  (funcall-superior-method gfi-output-interface)
  (change-slot-value gfi-output-interface 'file-system g2-operating-system)
  (unless (gfi-output-interface-non-default-slots-set-p gfi-output-interface)
    (add-any-gfi-output-incomplete-frame-notes gfi-output-interface)
    (update-frame-status gfi-output-interface 'incomplete nil)))

(def-class-method initialize-after-reading (gfi-output-interface)
  (funcall-superior-method gfi-output-interface)
  (change-slot-value gfi-output-interface 'file-system g2-operating-system)
  (unless (gfi-output-interface-non-default-slots-set-p gfi-output-interface)
    (add-any-gfi-output-incomplete-frame-notes gfi-output-interface)
    (update-frame-status gfi-output-interface 'incomplete nil))
  (update-representations-of-slot-value gfi-output-interface 'file-status))



;;; The function `gfi-output-interface-non-default-slots-set-p' checks that the
;;; slots of the GFI output interface which are not given default values, have
;;; been set by the user.  If these slots have not been set, then the GFI output
;;; interface is incomplete and will not output on activation.  (Upon
;;; activation, an error is signaled in the logbook.)

(defun-simple gfi-output-interface-non-default-slots-set-p
    (gfi-output-interface)
  (and (gfi-output-values gfi-output-interface)
      ;; Text slot, where the first value is the list of values and should be
      ;; non-NULL.
       (listp (gfi-output-values gfi-output-interface))
       (first (gfi-output-values gfi-output-interface))
       (gfi-output-file-update-frequency gfi-output-interface)
       (gfi-output-file-pathname gfi-output-interface)
       t))



;;; The function `add-any-gfi-output-incomplete-frame-notes' checks if any of
;;; the required GFI output interface slots (which don't receive a default
;;; value) are not set.  If so, a frame not is added.  Note that the
;;; frame-status is not changed here, but should be handled by the caller if
;;; necessary.

(defun-void add-any-gfi-output-incomplete-frame-notes (gfi-output-interface)
  (when (or (null (gfi-output-values gfi-output-interface))
	    ;; text slot, where the first value is the list of values.
	    (and (listp (gfi-output-values gfi-output-interface))
		 (null (first (gfi-output-values gfi-output-interface)))))
    (add-frame-note 'no-gfi-output-values gfi-output-interface))
  (when (null (gfi-output-file-update-frequency gfi-output-interface))
    (add-frame-note 'no-gfi-output-update-frequency gfi-output-interface))
  (when (null (gfi-output-file-pathname gfi-output-interface))
    (add-frame-note 'no-gfi-output-file-pathname gfi-output-interface))
  nil)



;;; The `activate method for gfi-output-interface' is currently the only way of
;;; "starting" GFI output.  (In a future release, this may be changed.)

;; NOTE THAT THIS IS BEING CHANGE FOR RELEASE 5.0!  There are new
;; gfi-input-when-active and gfi-output-when-active slots, which must be set to
;; yes (i.e., t) for an active, interface object to be started.  This means
;; that an interface object is either started when:
;; 1. This new slot is currently T and the object is activated,
;; 2. The object is already active and the slot is edited and set to T,
;; 3. The object is already active and has this slot set (the interface is
;;   currently started), but the object is re-started if an attribute that
;;   that affects the state of the interface object is edited.
;; - cpm, 7/12/96

;;; The method checks to see if the the given GFI Output Interface is fully
;;; specified.  If so, it opens the output file, initializes the GFI Output
;;; Interface frame, writes the file header (if any), and schedules the relevant
;;; tasks to update to the output file.

;;; This method also checks, when necessary for correct use of NUPEC GFI output
;;; file format:
;;;   It is an error if "GFI output file format" slot is "NUPEC snapshot" or
;;;   "NUPEC snapshot with restart time" and "GFI output file update frequency"
;;;   slot is not "write to file when activated [without interruption]"

(def-class-method activate (gfi-output-interface)
  (when (gfi-output-when-active gfi-output-interface)
    (prepare-gfi-output-interface-to-open gfi-output-interface))
  (funcall-superior-method gfi-output-interface))



;;; The function `prepare-gfi-output-interface-to-open' is used both
;;; in the activation and in interface object, before the object is
;;; actually opened.

(defun-simple prepare-gfi-output-interface-to-open (gfi-output-interface)
  (execute-body-if-gfi-is-authorized
    (cond
      ((not (frame-ok-p gfi-output-interface))
       ;; Tests that the item's non-default slots have values.
       (warning-message*
	   2 "While activating ~NF, the GFI output file could not be ~
                opened.  This item is incomplete."
	 gfi-output-interface))
      ((and (or (eq (gfi-output-file-format gfi-output-interface)
		    'nupec-snapshot)
		(eq (gfi-output-file-format gfi-output-interface)
		    'nupec-snapshot-with-restart-time))
	    (not (eq (gfi-output-file-update-frequency gfi-output-interface)
		     'output-one-shot-when-activated))
	    (not (eq (gfi-output-file-update-frequency gfi-output-interface)
		     'output-one-shot-when-activated-without-interruption)))
       (warning-message
	 2
	 "When using a GFI file format of NUPEC snapshot for ~NF, the gfi-~
          output-file-update-frequency must be either \"write to file when ~
          activated\" or \"write to file when activated, without ~
          interruption\"."
	 gfi-output-interface))
      (t
       (if (g2-stream-p (gfi-output-file-stream gfi-output-interface))
	   (close-gfi-output-interface gfi-output-interface t))
       (setf (gfi-list-of-new-spreadsheet-output-values gfi-output-interface)
	     nil)
       (setf (gfi-output-file-stream gfi-output-interface) nil)
       (setf (gfi-outputting? gfi-output-interface) nil) ; not until the stream is open
       (change-slot-value gfi-output-interface 'file-status 'ready-to-open)
       (if (gfi-output-without-interruption? gfi-output-interface)
	   (if queue-of-active-uninterruptable-gfi-output-interface-objects
	       (gfi-enqueue-in-pair
		 gfi-output-interface
		 queue-of-active-uninterruptable-gfi-output-interface-objects)
	       (let ((queue-list (gfi-cons gfi-output-interface nil)))
		 (setq
		   queue-of-active-uninterruptable-gfi-output-interface-objects
		   (gfi-cons queue-list queue-list))))
	   (if queue-of-active-gfi-output-interface-objects
	       (gfi-enqueue-in-pair
		 gfi-output-interface
		 queue-of-active-gfi-output-interface-objects)
	       (let ((queue-list (gfi-cons gfi-output-interface nil)))
		 (setq queue-of-active-gfi-output-interface-objects
		       (gfi-cons queue-list queue-list)))))
       (schedule-data-server-accept-data-calls)))))


;;; The function `write-designation-to-stream' takes a designation and a stream,
;;; reparses the designation into english (with the function print-designation),
;;; and outputs the designation into the stream.

(defun write-designation-to-stream (designation gfi-output-frame)
  (let ((designation-string (twith-output-to-text-string
			      (print-designation designation))))
    (gfi-write-string designation-string gfi-output-frame)
    (reclaim-text-string designation-string)))




;;; The function `write-gfi-output-file-header' writes the appropriate GFI file
;;; header for both relative and explicit time-stampped spreadsheet files, as
;;; well as the time base specifier if GFI file is a relative time-stampped
;;; event logged file.  The header for relative/spreadsheet is:  BASE TIME:  dd
;;; Mmm yyyy hh:mm:ss <tab> <designation-1> <tab> <designation-2> ... .  The
;;; header for explicit/spreadsheet is: <possibly-spaces> <tab> <designation-1>
;;; <tab> <designation-2> ...  . The header for relative/event-log is:  dd Mmm
;;; yyyy hh:mm:ss <tab> the current time <tab> 0.
;;;
;;; NUPEC Modification:
;;; Write NUPEC gfi-output-file-headers.  The header for both
;;; relative/nupec-snapshot and explicit/nupec-snapshot is: 
;;; <timestamp><TAB>the current time<TAB>0<NEWLINE>

;; Change: 3jul90, cpm.  Moved setf of
;; number-of-periodic-specified-designation-handled from the spreadsheet case to
;; the start of the function.  This causes all types of gfi output to start
;; writing the first designation on reset/restart.

(defun write-gfi-output-file-header (gfi-output-frame)
  ;; Reset designation counter so that a re-activation of gfi output will
  ;; always start at the first designation.
  (setf (number-of-periodic-specified-designation-handled
	  gfi-output-frame) 0)
  ;; Reformat later, minimize diffs today! (MHD 6/5/97)
    (case (gfi-output-file-format gfi-output-frame)

      ;; Spreadsheet
      (spreadsheet
	(if (eq (gfi-output-time-stamp-format gfi-output-frame) 'relative)
	    (progn
	      (gfi-write-string gfi-title-for-base-time gfi-output-frame)
	      (gfi-write-string #w"  " gfi-output-frame)
	      (output-gfi-explicit-time-stamp-to-stream
		(gfi-output-base-time gfi-output-frame) gfi-output-frame))
	    (gfi-write-string #w"                        " gfi-output-frame))
	(loop for designation in (gfi-output-unique-designations gfi-output-frame)
	      do
	  (gfi-write-char gfi-delimitter gfi-output-frame)
	  (write-designation-to-stream designation gfi-output-frame)
	      finally
		(gfi-terpri gfi-output-frame))
	(incff (number-of-lines-output-so-far gfi-output-frame)))

      ;; Event Log
      (event-log
	(when (eq (gfi-output-time-stamp-format gfi-output-frame) 'relative)
	  (output-gfi-explicit-time-stamp-to-stream
	    (gfi-output-base-time gfi-output-frame) gfi-output-frame)
	  (gfi-write-char gfi-delimitter gfi-output-frame)
	  (gfi-write-string gfi-designation-for-base-time gfi-output-frame)
	  (gfi-write-char gfi-delimitter gfi-output-frame)
	  (gfi-write-char #\0 gfi-output-frame)
	  (gfi-terpri gfi-output-frame)
	  (incff (number-of-lines-output-so-far gfi-output-frame))))

      ;; NUPEC snapshot and NUPEC snapshot with restart time
      ((nupec-snapshot nupec-snapshot-with-restart-time)
       (output-gfi-explicit-time-stamp-to-stream
	 (gfi-output-base-time gfi-output-frame) gfi-output-frame)
       (gfi-write-char gfi-delimitter gfi-output-frame)
       (gfi-write-string gfi-designation-for-base-time gfi-output-frame)
       (gfi-write-char gfi-delimitter gfi-output-frame)
       (gfi-write-char #\0 gfi-output-frame)
       (gfi-terpri gfi-output-frame)
       (incff (number-of-lines-output-so-far gfi-output-frame)))

      (otherwise
	(warning-message
	  2 "Illegal GFI output file format ~A in ~NF."
	  (gfi-output-file-format gfi-output-frame)
	  gfi-output-frame))))




;;; The function `schedule-gfi-output-tasks' will schedule the appropriate tasks
;;; for updating GFI output files.  If the output file is to be updated
;;; periodically, a periodic task is scheduled to perform the updating

;; Change: 3jul90, cpm.  Modified the periodic gfi spreadsheet and event log
;; output tasks to be scheduled as single-tasks instead of cyclic-tasks.  This
;; was done as part of the fix that reschedules the output task when it is not
;; finished within its time slice.

(defun schedule-gfi-output-tasks (gfi-output-frame)
  (cond
    ((interrupt-driven-gfi-file-update-frequency-p
       (gfi-output-file-update-frequency gfi-output-frame))
     ;; I think there's no real work to be done in this case!  All the work's
     ;; being done in the slot-putter and reclaimer for gfi-output-values, by
     ;; the function handle-gfi-output-interface-new-values, and by the function
     ;; accept-data-from-gfi-data-service.
     nil)
    ((or (eq (gfi-output-file-update-frequency gfi-output-frame)
	     'output-one-shot-when-activated)
	 (eq (gfi-output-file-update-frequency gfi-output-frame)
	     'output-one-shot-when-activated-without-interruption))
     ;; Also, nothing to schedule.  The output is written by the function
     ;; accept-data-from-gfi-data-service.
     nil)
    ((gfi-write-interval-p (gfi-output-file-update-frequency gfi-output-frame))
     (let ((file-format (gfi-output-file-format gfi-output-frame)))
       (cond
	 ((eq file-format 'spreadsheet)
	  (with-current-scheduling ((gfi-output-scheduled-task gfi-output-frame)
				    (get-slot-value data-server-parameters
						    'priority-of-data-service))
	    (gfi-output-spreadsheet-values-periodically-task
	      gfi-output-frame t)))
	 ((eq file-format 'event-log)
	  (with-current-scheduling ((gfi-output-scheduled-task gfi-output-frame)
				    (get-slot-value data-server-parameters
						    'priority-of-data-service))
	    (gfi-output-event-log-values-periodically-task gfi-output-frame t)))
	 ;; when we put in scheduling of functions to output BINARY spreadsheet
	 ;; and event-log formats here, when we decide to incorporate binary GFI
	 ;; files.
	 )))
    (t (warning-message
	 2 "Illegal GFI output file update frequency ~A in ~NF."
	 (gfi-output-file-update-frequency gfi-output-frame)
	 gfi-output-frame))))

;; jh, 5/23/91.  Changed schedule-gfi-output-tasks to replace the calls to
;; priority-of-continued-data-service with calls to priority-of-data-service.
;; See comments under the system table definition in VARIABLES and in
;; take-actions-at-start-of-clock-tick in CYCLES for an explanation of the name
;; change.



;;; The macro `write-floating-point-number-for-gfi' is used to write a
;;; gensym-float into a GFI file, trying to give the full precision of the float
;;; (currently, 15 digits).  This is done by restricting the field, including
;;; the decimal, width to 16.

;;; Note that the precision will be less for floats written in exponential
;;; notation.  In this case, the precision will be between 11 and 13 digits
;;; because the field, restricted to a length of 16, includes also the decimal,
;;; "e", and an exponent of between 1 to 3 digits.

(defmacro write-floating-point-number-for-gfi (gensym-float)
  `(write-floating-point-number
     ,gensym-float
     maximum-significant-decimal-digits-in-gensym-float	; currently 15
     maximum-significant-decimal-digits-in-gensym-float
     maximum-significant-decimal-digits-in-gensym-float
     t nil t nil			; the defaults for this function
     (+f maximum-significant-decimal-digits-in-gensym-float 1))) ; 16



;;; The function `output-gfi-value' outputs the current-value (of specified data
;;; type) to the specified output stream.  In development, the data type is
;;; checked to see if it is defined, valid type.  The call to this function
;;; should be wrapped around a with-temporary-gensym-float-creation.

(defun output-gfi-value (current-value data-type gfi-output-frame)

    #+development
    (if (not (or (eq data-type 'truth-value)
		 (eq data-type 'symbol)
		 (eq data-type 'text)
		 (number-subtype-p data-type)))
	(warning-message 2
	  "Illegal data type ~A in GFI output value." data-type))
    (let ((output-value
	    (twith-output-to-text-string
	      ;; Assumes a float current-value is a gensym-float, not a
	      ;; managed-float.
	      (case data-type
		(float
		 (write-floating-point-number-for-gfi current-value))
		(number
		 (if (fixnump data-type)
		     (twrite-fixnum current-value)
		     (write-floating-point-number-for-gfi current-value)))
		(integer
		 (twrite-fixnum current-value))
		(t
		 (print-constant current-value data-type))))))
      (prog1
	(gfi-write-string output-value gfi-output-frame)
	(reclaim-text-string output-value))))






;;; The functions `gfi-output-spreadsheet-values-periodically' and
;;; `gfi-output-event-log-values-periodically' are scheduled and rescheduled as
;;; single-tasks if the GFI output file is to be output periodically.  These
;;; functions simply find all the frames matching each of the specified
;;; designation and outputs the value returned by get-current-value (without
;;; computing new variable values).  In this (scheduled) case, the optional time
;;; slice argument is t, which causes a yield to to the time-slice.  If
;;; interrupted, another single-task is scheduled with a wait of 0, and the
;;; function will continue output where it left off.  If the output was not
;;; interrupted, another task is scheduled at the appropriate time interval for
;;; periodic output.
;;;
;;; These functions can also be used to "immediately" output the values.  The
;;; optional time slice argument determines if the function is interrupted when
;;; the time slice expires.  If interrupted, the function continues output where
;;; it left off, the next time it is called with the same gfi-output-frame.

;; Change: 3jul90, cpm.  This function was modified to reschedule single-tasks
;; when the output did not complete within the time slice.  It was also modified
;; to reschedule when the output did complete and the next periodic output needs
;; to be scheduled.

(defun-simple gfi-output-spreadsheet-values-periodically-task
    (gfi-output-frame do-not-override-time-slice-p)
  (gfi-output-spreadsheet-values-periodically
    gfi-output-frame do-not-override-time-slice-p))

(defun-allowing-unwind gfi-output-spreadsheet-values-periodically
		       (gfi-output-frame do-not-override-time-slice-p)
  (when (gfi-outputting? gfi-output-frame) ;(ie. active and outputting)
    (let ((time-slice-expired-p nil)
	  (output-stream (gfi-output-file-stream gfi-output-frame))
	  (output-limit (maximum-number-of-output-lines gfi-output-frame))
	  (number-of-designations-already-handled
	    (or (number-of-periodic-specified-designation-handled
		  gfi-output-frame)
		0)))
      (when output-stream
	(if (and output-limit
		 (<=f output-limit
		      (number-of-lines-output-so-far gfi-output-frame)))
	    (progn
	      (warning-message-for-limit-reached-in-gfi-output
		gfi-output-frame)
	      nil)
	    (progn
	      (when (and (gfi-write-interval-p (gfi-output-file-update-frequency
						 gfi-output-frame))
			 (null (gfi-output-scheduled-task-start-time 
				 gfi-output-frame)))
		(setf (gfi-output-scheduled-task-start-time gfi-output-frame)
		      (clock-get gensym-time)))

	      (incff (number-of-lines-output-so-far gfi-output-frame));; Note 1.
	      (if (<=f number-of-designations-already-handled 0)
		  (output-appropriate-gfi-time-stamp
		    gfi-output-frame (clock-get current-g2-time)))
	      (loop with variable? = nil
		    for designation-list on
			(nthcdr number-of-designations-already-handled
				(gfi-output-unique-designations
				  gfi-output-frame))
		    for designation = (car designation-list)
		    count t into value-count
		    do
		(gfi-write-char gfi-delimitter gfi-output-frame)
		(setq variable?
		      (let ((*current-computation-frame* gfi-output-frame))
			(evaluate-designation designation nil)))
		(if (and variable?
			 (not (temporary-constant-p variable?))
			 (variable-or-parameter-p variable?))
		    (get-current-value-without-side-effects-wrapper
		      (variable? current-value expiration-time data-type)
		      (if expiration-time
			  (output-gfi-value
			    current-value data-type gfi-output-frame)))
		    (progn
		      (warning-message-for-wrong-reference-for-gfi-designation
			gfi-output-frame designation variable?)
		      (reclaim-if-temporary-constant-function variable?)))
		    until (and do-not-override-time-slice-p
			       (setq time-slice-expired-p
				     (time-slice-expired-p)))
		    finally
		      (setq number-of-designations-already-handled
			    (if (null (cdr designation-list))
				0		; modulo here
				(+f number-of-designations-already-handled
				    value-count))))
	      
	      ;(format t "~&~A:~A"  do-not-override-time-slice-p time-slice-expired-p)
	      (if (and do-not-override-time-slice-p time-slice-expired-p 
		       (/=f 0 number-of-designations-already-handled))
		  (progn
		    (setf (number-of-periodic-specified-designation-handled
			    gfi-output-frame)
			  number-of-designations-already-handled)
		    (when (gfi-write-interval-p 
			    (gfi-output-file-update-frequency
			      gfi-output-frame))
		      (with-current-scheduling
			  ((gfi-output-scheduled-task gfi-output-frame)
			   (get-slot-value data-server-parameters
					   'priority-of-data-service))
			(gfi-output-spreadsheet-values-periodically-task
			  gfi-output-frame t)))
		    nil)
		  ;; else - finished
		  (progn
		    (setf (number-of-periodic-specified-designation-handled
			    gfi-output-frame)
			  0)
		    (when (gfi-write-interval-p 
			    (gfi-output-file-update-frequency
			      gfi-output-frame))
		      (let ((execution-time
			      (-f (clock-get gensym-time)
				  (gfi-output-scheduled-task-start-time
				    gfi-output-frame))))
			(with-future-scheduling
			    ((gfi-output-scheduled-task gfi-output-frame)
			     (get-slot-value data-server-parameters
					     'priority-of-data-service)
			     (g2-future-interval
			       (if (>=f execution-time 
					(caadr (gfi-output-file-update-frequency
						 gfi-output-frame))) 
				   ;; Schedule the task with no wait time, since
				   ;; the time to write the values was longer
				   ;; than the update-frequency interval.
				   0
				   ;; Schedule the task at the update-frequency
				   ;; interval from this output start time.
				   (-f (caadr (gfi-output-file-update-frequency 
						gfi-output-frame)) 
				       execution-time))))
			  (gfi-output-spreadsheet-values-periodically-task
			    gfi-output-frame t))
			(setf (gfi-output-scheduled-task-start-time
				gfi-output-frame) 
			      nil)))
		    (gfi-terpri gfi-output-frame)
		    t))))))))

;; Note 1: This looks wrong.  The number of lines should be bumped when we do
;; the terpri, this is counting the number of time slices we did output in. -
;; ben 5/26/93

;; Time slicing will cause the values on the tail of the line to from times
;; latter than the line says.  - ben 5/26/93

;; jh, 5/23/91.  Changed gfi-output-spreadsheet-values-periodically to replace
;; the calls to priority-of-continued-data-service with calls to
;; priority-of-data-service.  See comments under the system table definition in
;; VARIABLES and in take-actions-at-start-of-clock-tick in CYCLES for an
;; explanation of the name change.


(defun-simple gfi-output-event-log-values-periodically-task
    (gfi-output-frame do-not-override-time-slice-p)
  (gfi-output-event-log-values-periodically
    gfi-output-frame do-not-override-time-slice-p))

(defun-allowing-unwind gfi-output-event-log-values-periodically
		       (gfi-output-frame do-not-override-time-slice-p)
  (when (gfi-outputting? gfi-output-frame)	;(ie. active and outputting)
    (let ((time-slice-expired-p nil)
	  (output-stream (gfi-output-file-stream gfi-output-frame))
	  (output-limit? (maximum-number-of-output-lines gfi-output-frame))
	  (number-of-designations-already-handled
	    (or (number-of-periodic-specified-designation-handled gfi-output-frame)
		0)))
      (when output-stream
	(when (and (gfi-write-interval-p
		     (gfi-output-file-update-frequency
		       gfi-output-frame))
		   (null (gfi-output-scheduled-task-start-time 
			   gfi-output-frame)))
	  (setf (gfi-output-scheduled-task-start-time gfi-output-frame)
		(clock-get gensym-time)))
	(loop for designation-list on
		  (nthcdr number-of-designations-already-handled
			  (car (gfi-output-values gfi-output-frame)))
	      for designation = (car designation-list)
	      as not-unique-designation-p
		 in (gfi-output-not-unique-designation-p-results gfi-output-frame)
	      as unique-designation-p = (not not-unique-designation-p)
	      count t into value-count
	      do
	  (if (and output-limit?
		   (<=f output-limit?
			(number-of-lines-output-so-far gfi-output-frame)))
	      ;; THEN
	      (progn
		;; shouldn't this return immediately if true ?? cpm 12may89
		(warning-message-for-limit-reached-in-gfi-output gfi-output-frame)
		nil)
	      ;; ELSE
	      (let* ((eval-list-of-designation-values
		       (let ((*current-computation-frame* gfi-output-frame))
			 (serve-eval-list-of-designation-values designation))))
		(when (and (gfi-write-interval-p
			     (gfi-output-file-update-frequency
			       gfi-output-frame))
			   (null (gfi-output-scheduled-task-start-time 
				   gfi-output-frame)))
		  (setf (gfi-output-scheduled-task-start-time gfi-output-frame)
			(clock-get gensym-time)))

		(if eval-list-of-designation-values
		    ;; Then
		    (loop with designation?
			  for variable in eval-list-of-designation-values
			  do
		      (when (and output-limit?
				 (<=f output-limit?
				      (number-of-lines-output-so-far
					gfi-output-frame)))
			(loop-finish))
		      (setq designation?
			    (cond
			      (unique-designation-p
			       (copy-tree-using-eval-conses designation))
			      ((temporary-constant-p variable)
			       nil)
			      (t
			       (generate-designation-for-block variable))))
		      (cond
			(designation?
			 (if (and (not (temporary-constant-p variable))
				  (variable-or-parameter-p variable))
			     (get-current-value-without-side-effects-wrapper
				 (variable current-value expiration-time data-type)
			       (when expiration-time
				 (incff (number-of-lines-output-so-far
					  gfi-output-frame))
				 (output-appropriate-gfi-time-stamp
				   gfi-output-frame (clock-get current-g2-time))
				 (gfi-write-char
				   gfi-delimitter gfi-output-frame)
				 (write-designation-to-stream
				   designation? gfi-output-frame)
				 (gfi-write-char
				   gfi-delimitter gfi-output-frame)
				 (output-gfi-value current-value data-type
						   gfi-output-frame)
				 (gfi-terpri gfi-output-frame)))
			     (progn
			       (reclaim-if-temporary-constant-function variable)
			       (warning-message-for-wrong-reference-for-gfi-designation
				 gfi-output-frame designation? variable))))
			((not (framep variable))
			 (warning-message-for-non-frame-reference-for-gfi-designation
			   gfi-output-frame variable))
			(t
			 (warning-message-for-unnameable-variable
			   gfi-output-frame
			   variable
			   nil)))
		      (when unique-designation-p
			(reclaim-eval-tree designation?))
			  finally
			    (reclaim-eval-tree eval-list-of-designation-values))
		    ;; Else
		    (warning-message-for-wrong-reference-for-gfi-designation
		      gfi-output-frame designation nil))))

		    until (and do-not-override-time-slice-p
			       (setf time-slice-expired-p
				     (time-slice-expired-p)))
		    finally
		      (setq number-of-designations-already-handled
			    (if (null (cdr designation-list))
				0		; modulo here
				(+f number-of-designations-already-handled
				    value-count))))
	      
	      (if (and do-not-override-time-slice-p time-slice-expired-p)
		  (progn
		    (setf (number-of-periodic-specified-designation-handled
			    gfi-output-frame)
			  number-of-designations-already-handled)
		    (when (gfi-write-interval-p 
			    (gfi-output-file-update-frequency
			      gfi-output-frame))
		      (with-current-scheduling
			  ((gfi-output-scheduled-task gfi-output-frame)
			   (get-slot-value data-server-parameters
					   'priority-of-data-service))
			(gfi-output-event-log-values-periodically-task
			  gfi-output-frame t)))
		    nil)
		  ;; else - finished
		  (progn
		    (setf (number-of-periodic-specified-designation-handled
			    gfi-output-frame)
			  0)
		    (when (gfi-write-interval-p 
			    (gfi-output-file-update-frequency
			      gfi-output-frame))
		      (let ((execution-time
			      (-f (clock-get gensym-time)
				  (gfi-output-scheduled-task-start-time
				    gfi-output-frame))))
			(with-future-scheduling
			    ((gfi-output-scheduled-task gfi-output-frame)
			     (get-slot-value data-server-parameters
					     'priority-of-data-service)
			     (g2-future-interval
			       (if (>=f execution-time 
					(caadr (gfi-output-file-update-frequency
						 gfi-output-frame))) 
				   ;; Schedule the task with no wait time, since
				   ;; the time to write the values was longer
				   ;; than the update-frequency interval.
				   0
				   ;; Schedule the task at the update-frequency
				   ;; interval from this output start time.
				   (-f (caadr (gfi-output-file-update-frequency
						gfi-output-frame))
				       execution-time))))
			  (gfi-output-event-log-values-periodically-task
			    gfi-output-frame t))
			(setf (gfi-output-scheduled-task-start-time
				gfi-output-frame) 
			      nil)))
		    t))))))



;; jh, 5/23/91.  Changed gfi-output-event-log-values-periodically to replace the
;; calls to priority-of-continued-data-service with calls to
;; priority-of-data-service.  See comments under the system table definition in
;; VARIABLES and in take-actions-at-start-of-clock-tick in CYCLES for an
;; explanation of the name change.





;;;; Gfi-Output-Interface Deactivation




;;; The function `close-gfi-output-interface' is used to shut down a GFI
;;; Output Interface object.  It performs all the necessary cleanups such as
;;; reclaiming slots, resetting slots, and closing the output file.  The
;;; function makes no assumptions as to the state of the object it is handed and
;;; should not bomb out if it is handled an inactive object.  If
;;; flush-queues-to-file? is true, this function should attempts to output
;;; any remaining queue items to the file before closing.

(defun close-gfi-output-interface (gfi-output-frame flush-queues-to-file?)
  (when (gfi-output-scheduled-task gfi-output-frame)
    ;; NOTE: cannot use `cancel-task' here as `gfi-output-scheduled-task' is not
    ;; vector-slot and it cannot be, see GENSYMCID-1463. -- binghe, 2015/4/17
    #+SymScale
    (cancel-task-internal
      (gfi-output-scheduled-task gfi-output-frame))
    #-SymScale
    (cancel-task (gfi-output-scheduled-task gfi-output-frame))
    (setf (gfi-output-scheduled-task gfi-output-frame) nil))

  ;; If the line limit of the output file has not been exceeded, flush the
  ;; remainder of the output queues to the file.
  (let ((line-limit? (maximum-number-of-output-lines gfi-output-frame)))
    (if (and flush-queues-to-file?
	     (gfi-outputting? gfi-output-frame)
	     (or (null line-limit?)
		 (<f (number-of-lines-output-so-far gfi-output-frame)
		     line-limit?)))
	(output-gfi-queued-values-to-stream gfi-output-frame t)))

  ;; Reclaim the queues and list of values to be output
  (when (eq (gfi-output-file-format gfi-output-frame) 'spreadsheet)
    (loop with value-list = (gfi-list-of-new-spreadsheet-output-values
			      gfi-output-frame)
	  for managed-value? in value-list
	  do
      (reclaim-managed-number-or-value managed-value?)
	  finally
	    (reclaim-gfi-list value-list)))
  (setf (gfi-list-of-new-spreadsheet-output-values gfi-output-frame) nil)
  (reclaim-gfi-queue-of-new-output-values
    (gfi-queue-of-new-output-values gfi-output-frame))
  (setf (gfi-queue-of-new-output-values gfi-output-frame) nil)
  (setf (new-gfi-output-values-this-cycle? gfi-output-frame) nil)

  ;; Take frame out from list of active GFI Output Interface frames
  (if (gfi-output-without-interruption? gfi-output-frame)
      (gfi-delete-from-queue
	gfi-output-frame
	queue-of-active-uninterruptable-gfi-output-interface-objects)
      (gfi-delete-from-queue
	gfi-output-frame
	queue-of-active-gfi-output-interface-objects))

  (setf (gfi-outputting? gfi-output-frame) nil)

  ;; Close the GFI file
  (let ((output-stream (gfi-output-file-stream gfi-output-frame)))
    (cond
      (output-stream
       ;; Deinstall true value updates:
       (deinstall-gfi-true-value-update
	 gfi-output-frame
	 (car (gfi-output-values gfi-output-frame))
	 (gfi-output-not-unique-designation-p-results gfi-output-frame))
       (g2-stream-close output-stream)
       ;; Rename file after it is closed, if desired.
       (when (renamed-gfi-output-file-pathname? gfi-output-frame)
	 (let* ((old-pathname
		  (gfi-output-pathname-string-of-stream? gfi-output-frame))
		(new-pathname?
		  (get-pathname-for-gfi-interface
		    gfi-output-frame 'renamed-gfi-output-file-pathname?)))
	   (cond
	     (new-pathname?
	      (if (null (g2-stream-rename-file old-pathname new-pathname?))
		  (warning-message 2
		    "Error in renaming file ~S to ~S upon close of file."
		    old-pathname new-pathname?))
	      (reclaim-if-text-string new-pathname?))
	     (t
	      (warning-message 2
		"The file ~S for the GFI Output Interface ~NF was not renamed."
		old-pathname gfi-output-frame)))))
       (change-slot-value gfi-output-frame 'file-status 'closed)
       (setf (gfi-output-file-stream gfi-output-frame) nil))
      (t
       (when (neq (get-slot-value gfi-output-frame 'file-status)
		  'failed-to-open)
	 (change-slot-value gfi-output-frame 'file-status 'ready-to-open)))))

  (when (gfi-output-pathname-string-of-stream? gfi-output-frame)
    (reclaim-text-string (gfi-output-pathname-string-of-stream?
			   gfi-output-frame))
    (setf (gfi-output-pathname-string-of-stream? gfi-output-frame) nil)))



(def-class-method deactivate (gfi-output-interface)
  (close-gfi-output-interface gfi-output-interface t)
  (funcall-superior-method gfi-output-interface))












;;;; Gfi-Input-Interface Grammar for Slot Contents:




;;; Inplementation Note:  We should, as far as possible, abstract the file IO
;;; procedures so that we can easily implement binary GFI files input.  -pto
;;; 06oct88

;;; The user-accessible slots for GFI-INPUT-INTERFACE objects are:
;;; 	gfi-input-file-pathname		::= nil | <string>
;;;	gfi-input-file-format		::= event-log | spreadsheet
;;;	gfi-input-time-stamp-format	::= explicit | relative
;;;	gfi-input-variables-update-mode ::= asynchronous | on-request
;;;			   | on-request-sample-and-hold
;;;	                   | input-one-shot-when-activated
;;;	                   | input-one-shot-when-activated-without-interruption
;;;		`on-request = Input on request preserving time stamps
;;;		We are considering the addition of 'on-request-sample-and-hold
;;;		to this slot.  -pto 18oct88
;;;     Ignore-gfi-input-base-time?     ::= nil | t
;;;
;;; The unsaved (runtime) slots for GFI-INPUT-INTERFACE objects are:
;;; 	gfi-current-input-designation	::= nil | <slot-value-tree>
;;; 	gfi-inputting?			::= nil | t
;;; 	gfi-input-file-stream		::= nil | <IO-stream>
;;; 	gfi-input-base-time		::= <g2-time>, a managed-float
;; 	  Note in version 3.0, gfi-ininput-base-time was <gfi-time-structure>
;;;	gfi-input-g2-time-at-start	::= <g2-time>, a managed-float
;;;     gfi-input-line			::= <string>
;;;     gfi-input-line-g2-time     	::= <g2-time>, a managed-float
;;;	gfi-input-line-length		::= <fixnum>
;;;	gfi-input-line-current-index	::= <fixnum>
;;;	gfi-input-spreadsheet-designations ::= <slot-value-list>
;;;	gfi-queue-of-variables-that-need-values ::= <queue-pair>
;;;	gfi-input-file-synchronized?    ::= nil | t
;;;     gfi-input-without-interruption? ::= nil | t






;;; Slot Putters for GFI Input Interfaces:




;; FUTURE WORK:
;; When new output file is specified, we could close the old file, and open the
;; new file for output.  - pto 17oct88

(def-slot-putter gfi-input-file-pathname (frame new-value)
  (gfi-input-slot-putter-wrapper
    (frame new-value 'gfi-input-file-pathname)
    ;; Update the frame status and notes, if the value is set.
    (cond
      ((null new-value)
       (add-frame-note 'no-gfi-input-file-pathname frame)
       (update-frame-status frame 'incomplete nil))
      (t
       (delete-frame-note-if-any 'no-gfi-input-file-pathname frame)
       (when (gfi-input-interface-non-default-slots-set-p frame)
	 (update-frame-status frame nil nil))))))


(def-slot-putter gfi-input-file-format (frame new-value)
  (gfi-input-slot-putter-wrapper
    (frame new-value 'gfi-input-file-format) nil))


(def-slot-putter gfi-input-time-stamp-format (frame new-value)
  (gfi-input-slot-putter-wrapper
    (frame new-value 'gfi-input-time-stamp-format) nil))


(def-slot-putter ignore-gfi-input-base-time? (frame new-value)
  (gfi-input-slot-putter-wrapper
    (frame new-value 'ignore-gfi-input-base-time?) nil))


(def-slot-putter gfi-input-variables-update-mode (frame new-value)
  (gfi-input-slot-putter-wrapper
    (frame new-value 'gfi-input-variables-update-mode)
    ;; Update the frame status and notes, if the value is set.
    (cond
      ((null new-value)
       (add-frame-note 'no-gfi-input-variables-update-mode frame)
       (update-frame-status frame 'incomplete nil))
      (t
       (delete-frame-note-if-any 'no-gfi-input-variables-update-mode frame)
       (when (gfi-input-interface-non-default-slots-set-p frame)
	 (update-frame-status frame nil nil))
       (if (eq new-value
	       'input-one-shot-when-activated-without-interruption)
	   (change-slot-value frame 'gfi-input-without-interruption? t)
	   (change-slot-value frame 'gfi-input-without-interruption? nil))))))


(def-slot-putter gfi-input-when-active (frame new-value)
  (gfi-input-slot-putter-wrapper
    (frame new-value 'gfi-input-when-active) nil))






;;;; Gfi-Input-Interface Activation




(def-class-method initialize (gfi-input-interface)
  (funcall-superior-method gfi-input-interface)
  (change-slot-value gfi-input-interface 'file-system g2-operating-system)
  (unless (gfi-input-interface-non-default-slots-set-p gfi-input-interface)
    (add-any-gfi-input-incomplete-frame-notes gfi-input-interface)
    (update-frame-status gfi-input-interface 'incomplete nil)))

(def-class-method initialize-after-reading (gfi-input-interface)
  (funcall-superior-method gfi-input-interface)
  (change-slot-value gfi-input-interface 'file-system g2-operating-system)
  (unless (gfi-input-interface-non-default-slots-set-p gfi-input-interface)
    (add-any-gfi-input-incomplete-frame-notes gfi-input-interface)
    (update-frame-status gfi-input-interface 'incomplete nil)))



;;; The function `gfi-input-interface-non-default-slots-set-p' checks that the
;;; slots of the GFI input interface which are not given default values, have
;;; been set by the user.  If these slots have not been set, then the GFI input
;;; interface is incomplete and will not start input on activation.  (Upon
;;; activation, an error is signaled in the logbook.)

(defun-simple gfi-input-interface-non-default-slots-set-p
    (gfi-input-interface)
  (and (gfi-input-variables-update-mode gfi-input-interface)
       (gfi-input-file-pathname gfi-input-interface)
       t))



;;; The function `add-any-gfi-input-incomplete-frame-notes' checks if any of
;;; the required GFI input interface slots (which don't receive a default
;;; value) are not set.  If so, a frame not is added.  Note that the
;;; frame-status is not changed here, but should be handled by the caller if
;;; necessary.

(defun-void add-any-gfi-input-incomplete-frame-notes (gfi-input-interface)
  (when (null (gfi-input-variables-update-mode gfi-input-interface))
    (add-frame-note 'no-gfi-input-variables-update-mode gfi-input-interface))
  (when (null (gfi-input-file-pathname gfi-input-interface))
    (add-frame-note 'no-gfi-input-file-pathname gfi-input-interface))
  nil)



;;; The `activate method for GFI Input Inteface' is currently the only way of
;;; starting GFI input.  (This may be changed in a future release).

;;; The method sets up the object for inputting in the following way.  It checks
;;; to see if the slots are ok, and then opens the input file.  If the input
;;; file opens, the header (if any) is read, and the file is synchronized with
;;; gensym time, according to the parameters gfi-input-variables-update-mode and
;;; ignore-gfi-input-bast-time?.

;;; NUPEC Modification (error checking related to NUPEC gfi input file format):
;;;   a. Error if "GFI input file format" slot is "NUPEC snapshot" or "NUPEC
;;;   snapshot with restart time" and "ignore input base time" slot is "yes".
;;;   b. Error if "GFI input file format" slot is "NUPEC snapshot" or "NUPEC
;;;   snapshot with restart time" and "GFI input variables update mode" slot is
;;;   not "input when activated [without interruption]" 
;;;   c. Error if "GFI input file format" slot is "NUPEC snapshot" and the G2
;;;   scheduler mode is NUPEC-catch-up-mode.
;;;   d. Error if "GFI input file format" slot is "NUPEC snapshot with restart"
;;;   and the G2 scheduler mode is not NUPEC-catch-up-mode.

(def-class-method activate (gfi-input-interface)
  (when (gfi-input-when-active gfi-input-interface)
    (prepare-gfi-input-interface-to-open gfi-input-interface))
  (funcall-superior-method gfi-input-interface))



;;; The function `prepare-gfi-input-interface-to-open' is used both in the
;;; activation and in interface object, before the object is actually opened.

(defun-simple prepare-gfi-input-interface-to-open (gfi-input-interface)
  (execute-body-if-gfi-is-authorized
    (let ((update-mode? (gfi-input-variables-update-mode gfi-input-interface))
	  (file-format (gfi-input-file-format gfi-input-interface)))
      (cond
	((not (frame-ok-p gfi-input-interface))
	 ;; Tests that the item's non-default slots have values.
	 (warning-message*
	     2 "While activating ~NF, the GFI input file could not be ~
                opened.  This item is incomplete."
	   gfi-input-interface))
	((and (eq file-format 'nupec-snapshot-with-restart-time)
	      (not (eq (scheduler-mode timing-parameters) 'nupec-catch-up)))
	 (warning-message
	   2
	   "When using a GFI file format of NUPEC snapshot-with-restart-time ~
            for ~NF, the scheduler-mode of timing-parameters must be ~
            NUPEC-catch-up-mode."
	   gfi-input-interface))
	((and (eq file-format 'nupec-snapshot)
	      (eq (scheduler-mode timing-parameters) 'nupec-catch-up))
	 (warning-message
	   2
	   "When using a GFI file format of NUPEC snapshot ~
            for ~NF, the scheduler-mode of timing-parameters must not be ~
            NUPEC-catch-up-mode.  If the scheduler mode is required to be ~
            NUPEC-catch-up-mode, the GFI file format must be NUPEC ~
            snapshot-with-restart-time."
	   gfi-input-interface))
	((and (or (eq file-format 'nupec-snapshot)
		  (eq file-format 'nupec-snapshot-with-restart-time))
	      (not (eq update-mode? 'input-one-shot-when-activated))
	      (not (eq update-mode?
		       'input-one-shot-when-activated-without-interruption)))
	 (warning-message
	   2
	   "When using a GFI file format of NUPEC snapshot for ~NF, the gfi-~
            input-variables-update-mode attribute must be either \"input when ~
            activated\" or \"input when activated, without interruption\"."
	   gfi-input-interface))
	((and (or (eq file-format 'nupec-snapshot)
		  (eq file-format 'nupec-snapshot-with-restart-time))
	      (eq (ignore-gfi-input-base-time? gfi-input-interface) 'yes))
	 (warning-message
	   2
	   "When using a GFI file format of NUPEC snapshot for ~NF, the ~
            ignore-input-base-time attribute must be set to no."
	   gfi-input-interface))
	(t
	 (set-gfi-input-ignore-data-server?-flag
	   update-mode?
	   gfi-input-interface)
	 (close-gfi-input-interface gfi-input-interface)
	 (change-slot-value
	   gfi-input-interface 'file-status 'ready-to-open)
	 ;; Queue the frame
	 (if (gfi-input-without-interruption? gfi-input-interface)
	     (if
	       queue-of-active-uninterruptable-gfi-input-interface-objects
	       (gfi-enqueue-in-pair
		 gfi-input-interface
		 queue-of-active-uninterruptable-gfi-input-interface-objects)
	       (let ((queue-list (gfi-cons gfi-input-interface nil)))
		 (setq queue-of-active-uninterruptable-gfi-input-interface-objects
		       (gfi-cons queue-list queue-list))))
	     
	     (if queue-of-active-gfi-input-interface-objects
		 (gfi-enqueue-in-pair
		   gfi-input-interface
		   queue-of-active-gfi-input-interface-objects)
		 (let ((queue-list (gfi-cons gfi-input-interface nil)))
		   (setq queue-of-active-gfi-input-interface-objects
			 (gfi-cons queue-list queue-list)))))
	 (schedule-data-server-accept-data-calls))))))



;;; The function `open-gfi-input-interface' opens the GFI file for input and
;;; prepares the file for reading.  This function returns t if it successfully
;;; opened the file and nil otherwise.

(defun open-gfi-input-interface (gfi-input-frame)
  (setf (gfi-inputting? gfi-input-frame) nil)
  (execute-body-if-gfi-is-authorized
    (let* ((pathname? (get-pathname-for-gfi-interface
			gfi-input-frame 'gfi-input-file-pathname))
	   (*current-computation-frame* gfi-input-frame))
      (when pathname?
	(setf (gfi-input-pathname-string-of-stream? gfi-input-frame)
	      pathname?)
	(setf (gfi-input-file-stream gfi-input-frame)
	      (g2-stream-open-for-input pathname?))
	(when (gfi-input-file-stream gfi-input-frame)
	  (setf (gfi-input-file-buffer-position gfi-input-frame)
		(g2-stream-get-file-position
		  (gfi-input-file-stream gfi-input-frame)))
	  (setf (gfi-input-file-buffer-available-characters gfi-input-frame) 0)
	  (setf (gfi-input-file-buffer-offset gfi-input-frame) 0)))
      ;; Might want to be smarter with the file pathname above.
      (if (and pathname? (gfi-input-file-stream gfi-input-frame))
	  ;; THEN
	  (progn
	    (setf (gfi-inputting? gfi-input-frame) t)
	    (setf (gfi-input-line gfi-input-frame) (copy-constant-wide-string #w""))
	    ;; Put a "" into the gfi-input-line slot so that the reader
	    ;; read-one-gfi-input-line doesn't have to check form a string.
	    (setf (gfi-queue-of-variables-that-need-values gfi-input-frame)
		  (gfi-cons nil nil))
	    (setf (gfi-input-file-synchronized? gfi-input-frame) nil)
	    ;; Can't synchronize because some variables might not yet be
	    ;; activated.
	    (when (gfi-input-g2-time-at-start gfi-input-frame)
	      (reclaim-managed-number
		(gfi-input-g2-time-at-start gfi-input-frame)))
	    (setf (gfi-input-g2-time-at-start gfi-input-frame)
		  (copy-managed-float (clock-get current-g2-time)))
	    (read-gfi-file-header gfi-input-frame)
	    (change-slot-value gfi-input-frame 'file-status 'open)
	    t)
	  ;; ELSE
	  (progn
	    (change-slot-value gfi-input-frame 'file-status 'failed-to-open)
	    (when pathname?
	      (warning-message
		2 "Couldn't open input file ~S for ~NF."
		pathname? gfi-input-frame))
	    (close-gfi-input-interface gfi-input-frame)
	    nil)))))








;;;; Utilities for GFI Input Interface:




;;; The substitution macro `skip-to-after-gfi-delimitter-in-string' takes a
;;; string, a start-index, and an end-index, and returns the index of the
;;; position after the first gfi-delimitter after start-index.  If no delimitter
;;; was found, or if the delimitter is at the end of the string, nil is
;;; returned.

(defun-simple skip-to-after-gfi-delimitter-in-string
    (string start-index end-index)
  (loop	with current-index = start-index
	while (<f current-index end-index)
	do (if (char=w (charw string current-index) gfi-delimitter)
	       (return (+f current-index 1)))
	   (incff current-index)
	finally
	  (return nil)))



;;; The function `read-one-gfi-input-line' reads one line from the GFI input
;;; file and stores it in the GFI Input Interface object's gfi-input-line slot.
;;; It returns t is the read is successful, or nil if it is not.  If EOF is
;;; reached, nil is returned, else the text-string that is read in is returned.
;;; This function does not check to ensure that the gfi-input-frame it is given
;;; has an active GFI file.  The slot gfi-input-line-length is updated to the
;;; length of the new text string if no errors are encountered.  The
;;; gfi-input-frame is closed upon EOF or an error.  Blank lines (that contain
;;; white space) and comment lines (that begin with ";" are ignored.

(defun read-one-gfi-input-line (gfi-input-frame)
  (loop for line = (gfi-read-line gfi-input-frame)
	with length
	with comment-char-index?
	do
    (cond
      ((null line)
       (cond
	 ((g2-stream-last-error-is-eof-p)
	  (warning-message
	    2
	    "The end of the file has been reached in the GFI input file ~S.  ~
             The GFI Input Interface ~NF will not provide any ~A values."
	    (gfi-input-pathname-string-of-stream? gfi-input-frame)
	    gfi-input-frame
	    (if (eq (gfi-input-variables-update-mode gfi-input-frame)
		    'on-request-sample-and-hold)
		"new"
		"more")))
	 (t (let ((error-text (most-recent-file-operation-status-as-text)))
	      (warning-message
		  2
		  "Can't read from ~S for the GFI Input Interface ~NF:  ~A."
		(gfi-input-pathname-string-of-stream? gfi-input-frame)
		gfi-input-frame
		error-text)
	      (reclaim-text-string error-text))))
       (close-gfi-input-interface gfi-input-frame)
       (return nil))
      ((=f (setq length (text-string-length line)) 0)
       ;; ignore a blank line
       (reclaim-text-string line))
      ;; ignore line with only white space.
      ((not (setf comment-char-index? (gfi-input-find-non-white-space line)))
       (reclaim-text-string line))
      ;; ignore line that begins with a comment char, first non-white-space char
      ((char=w (charw line comment-char-index?) #.%\;)
       (reclaim-text-string line))
      (t
       ;; The gfi-input-line slot is guaranteed to have a string:
       (reclaim-text-string (gfi-input-line gfi-input-frame))
       (setf (gfi-input-line gfi-input-frame) line)
       (setf (gfi-input-line-length gfi-input-frame) length)
       (setf (gfi-input-line-current-index gfi-input-frame) 0)
       (return line)))))




;;; The function `read-gfi-designation-from-string' reads a constant designation
;;; from a text string and stores the parsed designation in the GFI input frame.
;;; Note that any previously read designation is reclaimed.

;;; Designation-text-string must be a legal text string (must be "legal-
;;; test-string-p").  (As of 3.0 this is true; in 2.1, it just mishandled
;;; a non-legal text string.)

;;; Note that this function reclaims the designation text string.

(defun read-gfi-designation-from-string (frame designation-text-string)
  (reclaim-slot-value (gfi-current-input-designation frame))
  (let ((parse? (parse-constant-designation designation-text-string 0)))
    (reclaim-text-string designation-text-string)
    (setf (gfi-current-input-designation frame) parse?)
    parse?))

;; Rewrote read-gfi-designation-from-string to call a new constant-designation
;; parser, instead of parse-text-for-slot.  This parser binds less special
;; variables.  Note that there are still some special variable bindings used.
;; For example, read-from-text-string calls
;; twith-output-to-then-use-of-text-string which binds some specials.  - cpm,
;; 10/8/92
;
;(defun read-gfi-designation-from-string (frame designation-text-string)
;  (reclaim-slot-value (gfi-current-input-designation frame))
;  (setf (gfi-current-input-designation frame) nil)
;  (if (parse-text-for-slot
;	(convert-text-string-to-text designation-text-string)
;	frame 'gfi-current-input-designation)
;      (gfi-current-input-designation frame)
;      nil))



;;; The function `parse-delimitter-then-designation' returns one or two values:
;;; a designation (of slot-value conses) and a second value t if there was an
;;; error.  It reads the designation from the string, starting either from the
;;; gfi-input-line-current-index or after the delimitter after this index,
;;; stopping at the first gfi-delimitter, and stores the constant designation in
;;; the gfi-current-input-designation slot.

(defun parse-delimitter-then-designation (gfi-input-frame &optional do-not-parse-delimitter?)
  (let* ((length (gfi-input-line-length gfi-input-frame)))
    (when (<f (gfi-input-line-current-index gfi-input-frame) length)
      (let* ((line (gfi-input-line gfi-input-frame))
	     (start-index
	       (if do-not-parse-delimitter?
		   (gfi-input-line-current-index gfi-input-frame)
		   (skip-to-after-gfi-delimitter-in-string
		     line
		     (gfi-input-line-current-index gfi-input-frame)
		     length)))
	     end-index)
	(when (and start-index (<f start-index length))
	  (setq end-index (skip-to-after-gfi-delimitter-in-string
			    line start-index length))
	  (if (not end-index)			;want to point to position
	      (setq end-index length)		;  just after the last character
	      (decff end-index))		;  of the designation.
	  (let ((designation-text-string
		  (text-string-substring line start-index end-index)))
	    (setf (gfi-input-line-current-index gfi-input-frame) end-index)
	    (read-gfi-designation-from-string
	      gfi-input-frame designation-text-string)))))))




;;; The function `read-list-of-gfi-designations' searches for the first
;;; gfi-delimitter after the gfi-input-line-current-index of a gfi-input-frame's
;;; gfi-current-line and starts reading a list of designations.  I.e. the
;;; following is being read:
;;; <tab><constant-designation-1><tab><const-designation-2>...<tab><c-d-n>.  The
;;; slot-value list of designations are stored in
;;; gfi-input-spreadsheet-designations.

;;; Return value(s):
;;;   A List of designations.
;;;   NIL - no designation read.  And an optional second value of T, indicating
;;;         that there was an error in reading the designation.

(defun read-list-of-gfi-designations (gfi-input-frame)
  (loop with list-of-designations = (slot-value-cons nil nil)
	with tail = list-of-designations
	and  designation
	and  error-p = nil
	do
    (multiple-value-setq (designation error-p)
      (parse-delimitter-then-designation
	gfi-input-frame))
    (setf (gfi-current-input-designation gfi-input-frame) nil)
    (if (and designation (not error-p))
	(if (car tail)
	    (progn
	      (setf (cdr tail) (slot-value-cons designation nil))
	      (setq tail (cdr tail)))
	    (setf (car tail) designation))
	(loop-finish))
	finally
	  (cond
	    (error-p
	     (reclaim-slot-value list-of-designations)
	     (return (values nil t)))
	    ((car list-of-designations)
	     (reclaim-slot-value (gfi-input-spreadsheet-designations
				   gfi-input-frame))
	     (setf (gfi-input-spreadsheet-designations gfi-input-frame)
		   list-of-designations)
	     (return list-of-designations))
	    (t
	     (reclaim-slot-value-cons list-of-designations)
	     (return nil)))))




;;; The function `read-and-encode-gfi-input-base-time' reads the explicit time
;;; stamp in the gfi-input-line, starting from gfi-input-line-current-index.  If
;;; an error occurs, nil is returned; otherwise, t is returned.

(defun read-and-encode-gfi-input-base-time (gfi-input-frame)
  (multiple-value-bind (seconds? minutes hours day month year
			end-index-of-time-stamp)
      (read-time-stamp-from-string
	(gfi-input-line gfi-input-frame)
	(gfi-input-line-current-index gfi-input-frame)
	(gfi-input-line-length gfi-input-frame))
    (cond
      (seconds?
       (setf (gfi-input-line-current-index gfi-input-frame)
	     end-index-of-time-stamp)
       (with-temporary-gensym-float-creation
	   read-and-encode-gfi-input-base-time
	 (let* ((second-fraction-float?
		  (if (managed-float-p seconds?)
		      (-e (managed-float-value seconds?)
			  (ffloore-first (managed-float-value seconds?)))))
		(subsecond-time?
		  (if (and second-fraction-float?
			   (/=e second-fraction-float? 0.0))
		      second-fraction-float?))
		(seconds-fixnum?
		  (when seconds?
		    (if (managed-float-p seconds?)
			(floore-first (managed-float-value seconds?))
			seconds?)))
		(encoded-time
		  (gensym-encode-unix-time-as-managed-float
		    seconds-fixnum? minutes hours day month year))
		(base-time? (gfi-input-base-time gfi-input-frame)))
	   (when subsecond-time?
	     (store-managed-number
	       encoded-time
	       (+e subsecond-time?
		   (managed-float-value encoded-time))))
	   (when (managed-float-p base-time?)
	     (reclaim-managed-float base-time?))
	   (setf (gfi-input-base-time gfi-input-frame)
		 encoded-time)))

       ;; Note that as of version 4.0, seconds can be a managed-number.
       (reclaim-managed-number seconds?)
       t)
      (t nil))))



;;; The macro `warning-message-for-read-gfi-file-header' takes an index and a
;;; gfi-input-frame and generates the appropriate code to (1) write the warning
;;; message and (2) close gfi-input-frame.

;;; Index should be one of the following symbols.
;;; 
;;;    no-base-time
;;;    cant-parse-first-line
;;;    time-stamp-error
;;;    header-error
;;;    parsing-error-in-spreadsheet
;;;    no-base-time-in-spreadsheet
	
(defmacro warning-message-for-read-gfi-file-header (index gfi-input-frame)
  `(let* ((file-format (gfi-input-file-format gfi-input-frame))
	  (file-format-string 
	   (cond ((eq file-format 'event-log) "event log")
		 ((eq file-format 'spreadsheet) "spreadsheet")
		 ((eq file-format 'nupec-snapshot)
		  ;; Had this before: (twrite-string "NUPEC snapshot")
		  ;; -- bug! fixed! (MHD 2/6/92)
		  "NUPEC snapshot")
		 (t "unknown file format"))))
     file-format-string				       ; not used in all cases.
     ,(case index
	(no-base-time
	 `(warning-message
	    2
	    "The base time was not found in the ~S GFI file ~S ~
             for ~NF, where relative time-stamping was specified."
	    file-format-string
	    (gfi-input-pathname-string-of-stream? ,gfi-input-frame)
	    ,gfi-input-frame))
	(cant-parse-first-line
	 `(warning-message
	    2
	    "Can't parse the first line of the ~S GFI file ~S of the GFI ~
             Input Interface ~NF." 
	    file-format-string
	    (gfi-input-pathname-string-of-stream? ,gfi-input-frame)
	    ,gfi-input-frame))
	(time-stamp-error
	 `(warning-message
	    2
	    "Error in reading the time stamp in the ~S GFI ~
	     file ~S of the GFI Input Interface ~NF.  Note that the first ~
	     line of this file must have an explicit time stamp."
	    file-format-string
	    (gfi-input-pathname-string-of-stream? ,gfi-input-frame)
	    ,gfi-input-frame))
	(header-error-no-item-designation
	 `(warning-message
	    2
	    "Error in parsing the header of the spreadsheet format GFI ~
	     file ~S for the GFI Input Interface ~NF.  Variable or parameter ~
             reference not found."
	    (gfi-input-pathname-string-of-stream? ,gfi-input-frame)
	    ,gfi-input-frame))
	(header-error-bad-item-designation
	 `(warning-message
	    2
	    "Error in parsing the header of the spreadsheet format GFI ~
	     file ~S for the GFI Input Interface ~NF.  Invalid variable or parameter ~
             reference."
	    (gfi-input-pathname-string-of-stream? ,gfi-input-frame)
	    ,gfi-input-frame))
	(parsing-error-in-spreadsheet
	 `(warning-message
	    2
	    "Error in parsing the base time of the spreadsheet format GFI ~
	     file ~S for the GFI Input Interface ~NF."
	    (gfi-input-pathname-string-of-stream? ,gfi-input-frame)
	    ,gfi-input-frame))
	(no-base-time-in-spreadsheet
	 `(warning-message
	    2
	    "The spreadsheet format GFI file ~S for the GFI Input ~
             Interface ~NF should start with ~S."
	    (gfi-input-pathname-string-of-stream? ,gfi-input-frame)
	    ,gfi-input-frame
	    gfi-title-for-base-time)))
     (close-gfi-input-interface ,gfi-input-frame)
     nil))

;; NUPEC Modification: also write error message for NUPEC-gfi-file-header.

;; This macro is simply to make the function read-gfi-file-header more readable.
;; -- I think this should be made a function.  Note, however, that to do that
;; the callers will have to be fixed to quote their first argument. (MHD 2/6/92)




;;; The substitution macro `skip-spaces-and-update-gfi-current-index' takes a
;;; gfi-input-frame, and, starting from the position pointed to be
;;; gfi-input-line-current-index, skips all the spaces until
;;; gfi-input-line-current-index is pointing to the first non-space.

(def-substitution-macro skip-spaces-and-update-gfi-current-index
			(gfi-input-frame)
  (setf (gfi-input-line-current-index gfi-input-frame)
	(skip-spaces-in-string
	  (gfi-input-line gfi-input-frame)
	  (gfi-input-line-current-index gfi-input-frame)
	  (gfi-input-line-length gfi-input-frame))))




;;; The function `gfi-input-find-non-white-space' returns the index
;;; (0-based) of the first non-white-space character between the start and end
;;; of the string.  (A start and end within the string can be optionally be
;;; specified).  If no non-white-space character is found, NIL is returned.

(defun gfi-input-find-non-white-space
       (string &optional (start 0) (end nil))
  (loop for i = start then (+f i 1)
	with end = (if end
		       (minf (text-string-length string) end)
		       (text-string-length string))
	until (or (>=f i end)
		  (not (wide-character-member
			 (charw string i)
			 gfi-input-white-space)))
	finally
	(if (>=f i end)
	    (return nil)
	    (return i))))




;;; The function `match-shorter-substring-p' returns non-nil only if the length
;;; of the specified substring (from start-index-1 to end-index-2) of the longer
;;; string is greater than that of the shorter, and the substrings are
;;; substring-equal.

(defun match-shorter-substring-p
       (string-1 start-index-1 end-index-1
	shorter-string-2 start-index-2 end-index-2)
  (let ((delta-1 (-f end-index-1 start-index-1))
	(delta-2 (-f end-index-2 start-index-2)))
    (if (>=f delta-1 delta-2)
	(substring-equal string-1 start-index-1
			 (+f start-index-1 delta-2)
			 shorter-string-2 start-index-2 end-index-2))))




;;; The function `read-gfi-file-header' reads in the header (if any) of a GFI
;;; file and sets up the following:  (1) the base time of the GFI file is stored
;;; in gfi-input-base-time, and, (2) if the GFI is in the spreadsheet format,
;;; the list of designations is stored in gfi-input-spreadsheet-designations.
;;; Two slot values determine what type of header we read:
;;; gfi-input-file-format and gfi-input-time-stamp-format. Returns nil if error,
;;; non-nil otherwise.  This function also leaves the gfi-input-line with a
;;; fresh string, ready to be read.

;; NUPEC Modification:
;; Nupec-snapshot file header has the same format as event-log/relative.

(defun read-gfi-file-header (gfi-input-frame)
  (if (read-one-gfi-input-line gfi-input-frame)
      (case (gfi-input-file-format gfi-input-frame)
	((event-log nupec-snapshot nupec-snapshot-with-restart-time)
	 ;; Event Log:  The first entry on a line is read as the base time
	 ;; NUPEC snapshot: The first entry on a line is read as the base time. 
	  (if (read-and-encode-gfi-input-base-time gfi-input-frame)
	      (if 
		(or (eq (gfi-input-time-stamp-format gfi-input-frame)
			'relative)		       ;then 1st entry is base
						       ;time 
		    (eq (gfi-input-file-format gfi-input-frame) 'nupec-snapshot)
		    (eq (gfi-input-file-format gfi-input-frame)
			'nupec-snapshot-with-restart-time))
		;; then read the base time
		(let* ((line (gfi-input-line gfi-input-frame))
		       (gfi-current-index
			 (skip-to-after-gfi-delimitter-in-string
			   line
			   (gfi-input-line-current-index gfi-input-frame)
			   (gfi-input-line-length gfi-input-frame))))
		  (if (and gfi-current-index
			   (<f gfi-current-index
			       (gfi-input-line-length gfi-input-frame))
			   (>f (-f (gfi-input-line-length gfi-input-frame)
				   gfi-current-index)
			       gfi-designation-for-base-time-string-length))
		      (if (substring-equal
			    gfi-designation-for-base-time
			    0 gfi-designation-for-base-time-string-length
			    line
			    gfi-current-index
			    (+f gfi-current-index
				gfi-designation-for-base-time-string-length))
			  (read-one-gfi-input-line gfi-input-frame)
			  (warning-message-for-read-gfi-file-header
			    no-base-time gfi-input-frame))
		      (warning-message-for-read-gfi-file-header
			cant-parse-first-line gfi-input-frame)))
		;; Explicit time stamp
		  (setf (gfi-input-line-current-index gfi-input-frame) 0))
	      ;; else - read base time error
	      (warning-message-for-read-gfi-file-header
		time-stamp-error gfi-input-frame)))

	;; Spreadsheet format:
	(spreadsheet
	  (if (eq (gfi-input-time-stamp-format gfi-input-frame) 'relative)
	      (if (match-shorter-substring-p
		    (gfi-input-line gfi-input-frame)
		    0 (gfi-input-line-length gfi-input-frame)
		    gfi-title-for-base-time
		    0 gfi-title-for-base-time-string-length)
		  (progn
		    (setf (gfi-input-line-current-index gfi-input-frame)
			  gfi-title-for-base-time-string-length)
		    (skip-spaces-and-update-gfi-current-index gfi-input-frame)
		    (if (read-and-encode-gfi-input-base-time gfi-input-frame)
			;; okay - now read designations
			(multiple-value-bind (designation-list? error-p?)
			    (read-list-of-gfi-designations gfi-input-frame)
			  (cond
			    (designation-list?
			      ;;okay
			     (read-one-gfi-input-line gfi-input-frame))
			      ;; error - no designations
			    (error-p?
			      (warning-message-for-read-gfi-file-header
				    header-error-bad-item-designation
				    gfi-input-frame))
			    (t
			     (warning-message-for-read-gfi-file-header
			       header-error-no-item-designation
			       gfi-input-frame))))
			;; error - no base time
			(warning-message-for-read-gfi-file-header
			  parsing-error-in-spreadsheet gfi-input-frame)))
		  ;; error - no "BASE TIME:"
		  (warning-message-for-read-gfi-file-header
		    no-base-time-in-spreadsheet gfi-input-frame))
	      (progn				; Explicit
		(skip-spaces-and-update-gfi-current-index gfi-input-frame)
		  (multiple-value-bind (designation-list? error-p?)
		      (read-list-of-gfi-designations gfi-input-frame)
		    (cond
		      (designation-list?
			(if (read-one-gfi-input-line gfi-input-frame)
			    (if (read-and-encode-gfi-input-base-time
				  gfi-input-frame)
				(progn
				  (setf (gfi-input-line-current-index
					  gfi-input-frame) 0)
				  t)
				(warning-message-for-read-gfi-file-header
				  parsing-error-in-spreadsheet gfi-input-frame))
			    nil))
		      (error-p?
			(warning-message-for-read-gfi-file-header
			  header-error-bad-item-designation
			  gfi-input-frame))
		      (t
			(warning-message-for-read-gfi-file-header
			  header-error-no-item-designation
			  gfi-input-frame)))))))
	#+development
	(otherwise
	 (warning-message
	   2
	   "Unknown gfi-input file-format ~S for the GFI Input Interface ~NF."
	   (gfi-input-file-format gfi-input-frame)
	   gfi-input-frame)))
      ;; else read error
      nil))









;;;; Put Current Value Functions For Asynchronous,
;;;;   On-Request-Preserving-Time-Stmp, And On-Request-Sample-And-Hold:





;;; The macro `put-current-gfi-value-with-time-stamp' takes a GFI variable, a
;;; managed value, and a collection g2-time, and performs a put-current-value of
;;; the variable (within a temporary short float creation context).  The managed
;;; value is then reclaimed.  It could be made more efficient if we omit the
;;; temporary context if the number is not a gensym float.  (For asynchronous
;;; operation.)

(defun-substitution-macro put-current-gfi-value-with-time-stamp
			  (gfi-input-frame
			    gfi-variable 
			    managed-value collection-g2-time)
  (let ((*current-computation-frame* gfi-input-frame)
	(current-computation-instance (data-server 'gfi-data-server)))
    (with-temporary-gensym-float-creation put-current-gfi-value-with-time-stamp
      (put-current-value gfi-variable
			 (extract-cached-number-or-value managed-value)
			 (data-type-of-variable-or-parameter-datum
			   (extract-cached-number-or-value managed-value)
			   gfi-variable)
			 nil
			 collection-g2-time)
      (reclaim-managed-number-or-value managed-value))))




;;; The macro `put-current-value-using-and-preserving-gfi-last-value' takes a
;;; GFI variable, and does a put-current-value on the variable using the managed
;;; value in the gfi-last-value slot of the GFI variable, and the time in the
;;; slot gfi-time-of-last-value-update.  The values in these two slots are not
;;; reclaimed.  This function does not check to ensure that the variable is
;;; being data served by GFI.  (For on-request-sample-and-hold.)

(def-substitution-macro put-current-value-using-and-preserving-gfi-last-value
			(gfi-input-frame gfi-variable gfi-last-value)
  (let ((*current-computation-frame* gfi-input-frame)
	(current-computation-instance (data-server 'gfi-data-server)))
    (with-temporary-gensym-float-creation
      put-current-value-using-and-preserving-gfi-last-value
      (put-current-value gfi-variable
			 (extract-cached-number-or-value gfi-last-value)
			 (data-type-of-variable-or-parameter-datum
			   (extract-cached-number-or-value gfi-last-value)
			   gfi-variable)
			 nil
			 (clock-get current-g2-time)))))

;; This macro is not using the gfi-time-of-last-value-update as documented
;; above.  It does match the GFI reference manual doc., which says that it uses
;; the current time.  - cpm, 7/5/94




;;; The macro `put-current-value-using-and-reclaiming-gfi-last-value' takes a
;;; GFI variable, and does a put-current-value on the variable using the managed
;;; value in the gfi-last-value slot of the GFI variable, and the time in the
;;; slot gfi-time-of-last-value-update.  The values in these two slots are then
;;; reclaimed.  This function does not check to ensure that the variable is
;;; being data served by GFI.  (For on-request-preserving-time-stamp.)

(def-substitution-macro put-current-value-using-and-reclaiming-gfi-last-value
			(gfi-input-frame gfi-variable last-value)
  (let ((*current-computation-frame* gfi-input-frame)
	(current-computation-instance (data-server 'gfi-data-server)))
    (with-temporary-gensym-float-creation
      put-current-value-using-and-reclaiming-gfi-last-value
      (put-current-value gfi-variable
			 (extract-cached-number-or-value last-value)
			 (data-type-of-variable-or-parameter-datum
			   (extract-cached-number-or-value last-value)
			   gfi-variable)
			 nil
			 (gfi-time-of-last-value-update gfi-variable))
      (reclaim-managed-number-or-value (gfi-last-value gfi-variable))
      (setf (gfi-last-value gfi-variable) nil))))







;;; The macro `coerce-designation-to-text-string' returns a reclaimable
;;; text-string corresponding to the designation given it.

(defmacro coerce-designation-to-text-string (designation)
  `(twith-output-to-text-string
     (print-designation ,designation)))





;;; The function `read-text-string-with-or-without-quotes-from-string' takes a
;;; string, a start-index and an end-index, reads a text string found in the
;;; string either (i) starting with a double quote (") at start-index, and
;;; ending as a double quote, or (ii) not starting with a double quote and
;;; ending with a <tab>.



;;; The function `read-text-string-with-or-without-quotes-from-string' takes a
;;; string, a start-index and an end-index, reads a text string found in the
;;; string either (i) starting with a double quote (") at start-index, and
;;; ending as a double quote, or (ii) not starting with a double quote and
;;; ending with a <tab>.

(defun read-text-string-with-or-without-quotes-from-string
       (string start-index end-index)
  (if (char=w (charw string start-index) #.%\")
      (read-text-string-from-string string start-index end-index)
      (let (managed-string)
	(multiple-value-bind (text-string current-index)
	    (read-text-string-ending-in-a-delimitter-from-string
	      string start-index end-index gfi-delimitter)
	  (store-managed-number-or-value managed-string text-string)
	  (reclaim-text-string text-string)
	  (values managed-string current-index nil)))))

;; This doesn't work correctly for some valid G2 strings, e.g., the string
;;     "foo
;; which is entered by the user as
;;     @"foo
;; and which is represented internally as
;;     ~@"foo
;; Try entering, in Lisp,
;;     (let ((string "~@\"foo"))
;;       (read-text-string-with-or-without-quotes-from-string
;;          string 0 (length string)))
;; Note that the backslash (\) is there for the benefit of the Lisp reader.
;; Compare the result with
;;     (let ((string "~@\"foo"))
;;        (read-from-text-string string  0 (length string)))
;; NEEDS REVIEW!! (MHD 3/24/93)



;;; The function `put-gfi-value-of-designation-into-appropriate-place' will take
;;; a designation and a gfi-input-frame, place-evaluate the designation, read
;;; the appropriate value (according to the variable referred to by the
;;; designation) from the string in the gfi-input-frame, and put the value in an
;;; appropriate place.

;;; This function will only store the value for the variable if the
;;; data-server-map for the variable is 'gfi-data-server or if no data service
;;; is required (an optional argument).  If gfi-input-variables-update-mode is
;;; asynchronous, input-one-shot-when-activated, or input-one-shot-when-
;;; activated-without-interruption, then put-current-gfi-value-with-time-stamp
;;; is called to put the value into the variable's history.  If gfi-input-
;;; variables-update-mode is 'on-request, then the value is placed into the
;;; variable's gfi-last-value, and the gfi-input-line-g2-time is stored into
;;; gfi-time-of-last-value-update (and the old values there are reclaimed).

;;; If an error occurs, a string will be returned, otherwise a non-string is
;;; returned.  The gfi-input-line-current-index is incremented to point to after
;;; the value in the string gfi-input-line, if the value was successfully read.

(defun put-gfi-value-of-designation-into-appropriate-place
       (designation gfi-input-frame no-data-service-required?)
  (let ((variable-or-parameter
	  (let ((*current-computation-frame* gfi-input-frame))
	    (place-evaluate designation nil)))
	gfi-interface-object-designation)
    (cond
      ((null variable-or-parameter)
       (let ((end-index?
	       (skip-to-after-gfi-delimitter-in-string
		 (gfi-input-line gfi-input-frame)
		 (gfi-input-line-current-index gfi-input-frame)
		 (gfi-input-line-length gfi-input-frame))))
	 (warning-message
	   2
	   "The GFI Input Interface ~NF has received a value for ~ND ~
	    but could not find an appropriate variable to store the value."
	   gfi-input-frame designation)
	 (if end-index?
	     (setf (gfi-input-line-current-index gfi-input-frame) end-index?)
	     (setf (gfi-input-line-current-index gfi-input-frame)
		   (gfi-input-line-length gfi-input-frame)))
	 nil))
      ((and (variable-or-parameter-p variable-or-parameter)
	    (or no-data-service-required?
		(and (variable-p variable-or-parameter)
		     (gfi-data-service-p variable-or-parameter)
		     (eq (get-data-server variable-or-parameter)
			 (data-server 'gfi-data-server))
		     ;; Could save a few function calls if a global was binded
		     ;; to (data-server 'gfi-data-server).  -pto 02dec88
		     (setq gfi-interface-object-designation
			   (gfi-input-interface-object variable-or-parameter))
		     (designation-denotes-item-p
		       gfi-interface-object-designation gfi-input-frame))))
       (let ((string (gfi-input-line gfi-input-frame))
	     (current-index (gfi-input-line-current-index gfi-input-frame))
	     (end-index (gfi-input-line-length gfi-input-frame))
	     (collection-time (gfi-input-line-g2-time gfi-input-frame))
	     (illegal-string-p nil))
	 (multiple-value-bind (managed-value end-index)
	     (let ((data-type
		     (type-specification-of-variable-or-parameter-value
		       variable-or-parameter)))
	       (cond
		 ((number-subtype-p data-type)
		  (read-number-from-string string current-index end-index))
		 ((eq data-type 'truth-value)
		  (read-truth-value-from-string string
						current-index end-index))
		 ((eq data-type 'symbol)
		  (multiple-value-bind (symbol? symbol-end-index)
		      (read-symbol-from-text-string string current-index)
		    (cond
		      ((null symbol?)
		       (values nil symbol-end-index))
		      ;; Not necessary any longer:  (MHD 3/3/96)
;		      ((not (legal-gensym-string-p (symbol-name symbol?)))
;		       (setq illegal-string-p t)
;		       (values nil symbol-end-index))
		      (t
		       (values symbol? symbol-end-index)))))
		 ((eq data-type 'text)
		  (multiple-value-bind (text text-end-index error-message?)
		      (read-text-string-with-or-without-quotes-from-string
			string current-index end-index)
		    (declare (ignore error-message?)) ; <= not sure if this is really ever an 
		    (values text text-end-index)))    ;   error message, but moot! (MHD 4/30/96)
		 (t
		  (values nil current-index))))
	   (setf (gfi-input-line-current-index gfi-input-frame) end-index)
	   (if managed-value
	       (case (gfi-input-variables-update-mode gfi-input-frame)
		 ((on-request-sample-and-hold on-request)
		  (if (gfi-last-value variable-or-parameter)
		      (reclaim-managed-number-or-value
			(gfi-last-value variable-or-parameter)))
		  (setf (gfi-last-value variable-or-parameter) managed-value)
		  (if (gfi-time-of-last-value-update variable-or-parameter)
		      (reclaim-managed-float
			(gfi-time-of-last-value-update variable-or-parameter)))
		  (setf (gfi-time-of-last-value-update variable-or-parameter)
			(copy-managed-float collection-time))
		  nil)
		 (otherwise
;		  (asynchronous 
;		    assynchronous-ignoring-data-server
;		    input-one-shot-when-activated
;		    input-one-shot-when-activated-without-interruption)
		  (put-current-gfi-value-with-time-stamp
		    gfi-input-frame variable-or-parameter managed-value
		    collection-time)
		  nil))
	       (progn
		 (if illegal-string-p
		     (progn
		       (warning-message
			 2
			 "The GFI Input Interface ~NF obtained a line containing an illegal ~
			 string or symbol for the value of ~ND (~A~A).  The input interface ~
			 will be shut down, since the input file is probably corrupted."
			 gfi-input-frame designation
			 (supply-a-or-an
			   (data-type-of-variable-or-parameter variable-or-parameter))
			 (data-type-of-variable-or-parameter variable-or-parameter))
		       (close-gfi-input-interface gfi-input-frame))
		     (let ((legal-text-string
			     (copy-text-string string)
			     ;; Obs.:   (MHD 3/2/96)
;			     (copy-string-filtering-out-non-gensym-characters
;			       string)
			     ))
		       ;; MHD: This crashes G2 now because the line contains tabs
		       ;; and tabs are not legal in a G2 text string.  FIX!!
		       ;; (MHD 2/6/92)
		       ;; -- The above patches this problem somewhat -- as things
		       ;; now stand, for one thing, Tabs will turn into
		       ;; underscores (_); see convert-ascii-string-to-text-string-
		       ;; as-much-as-possible.  (MHD 2/6/92)
		       ;; -- This function was immediately implicated in the bug
		       ;;    in the bug database gfi-invalid-input-line-error.
		       ;;    (MHD 2/6/92)
		       (warning-message
			 2
			 "The GFI Input Interface ~NF could not parse the line ~
                          ~S, starting at character ~A, ~ND (~A~A).  There is ~
                          a data type mismatch or an illegal string or symbol."
			 gfi-input-frame
			 legal-text-string current-index designation
			 (supply-a-or-an
			   (data-type-of-variable-or-parameter variable-or-parameter))
			 (data-type-of-variable-or-parameter variable-or-parameter))
		       (reclaim-text-string legal-text-string)
		       (close-gfi-input-interface gfi-input-frame)))
		 #w"error")))))
      ;; If there was a variable or parameter with this designtion, but its data
      ;; server was not this interface object, just align the current-position
      ;; pointer after the field for this value.
      (t
       (write-warning-message 3
	 (tformat
	   "The GFI input interface object ~NF could not find a variable"
	   gfi-input-frame)
	 (if no-data-service-required?
	     (twrite-string " or a parameter")
	     (tformat
	       " (which has GFI data service and has ~NF as its GFI ~
		input interface object)"
	       gfi-input-frame))
	 (tformat				; See note below.
	   " corresponding to \"~ND\", as specified in the GFI input file ~S."
	   designation
	   (gfi-input-pathname-string-of-stream? gfi-input-frame)))
       (let ((end-index?
	       (skip-to-after-gfi-delimitter-in-string
		 (gfi-input-line gfi-input-frame)
		 (gfi-input-line-current-index gfi-input-frame)
		 (gfi-input-line-length gfi-input-frame))))
	 (if end-index?
	     (setf (gfi-input-line-current-index gfi-input-frame) end-index?)
	     (setf (gfi-input-line-current-index gfi-input-frame)
		   (gfi-input-line-length gfi-input-frame)))
	 nil)))))

;; Review enclosing of designation in double quotes above; it is not a standard,
;; although I believe we do need something like that.  (MHD 2/5/92)



;;; The function `encode-gfi-input-line-g2-time' takes a GFI Input Interface
;;; frame, converts the time stamp (in the string in gfi-input-line) into a
;;; g2-time, and stores the g2-time (a managed-float) in gfi-input-line-g2-time.

;;; If any error is encountered in parsing the time stamp (explicit or relative)
;;; in gfi-input-line, a non-reclaimable string containing an error message is
;;; returned.  If the update is successful, a non-string is returned.  Also,
;;; gfi-line-current-index is set to point to just after the time stamp (before
;;; the gfi-delimitter).
;;;
;;; There are four ways to encode depending on the value in slots
;;; gfi-input-time-stamp-format and ignore-gfi-input-base-time?:
;;;
;;; (format=relative, ignore?=t):  gfi-input-line-g2-time =
;;; relative-time-stamp + g2-time-at-start
;;;
;;; (format=relative, ignore?=nil):  gfi-input-line-g2-time =
;;; relative-time-stamp + encoded-gfi-input-base-time
;;;
;;; (format=explicit, ignore?=t): gfi-input-line-g2-time =
;;; explicit-time-stamp + g2-time-at-start - encoded-gfi-input-base-time
;;;
;;; (format=explicit, ignore?=nil):  gfi-input-line-g2-time =
;;; explicit-time-stamp
;;;
;;; where relative-time-stamp is the fixnum read from the string,
;;; encoded-gfi-input-base-time is the g2-time of the base-time of the GFI file,
;;; g2-time-at-start is the global defined in CLOCKS, explicit-time-stamp is the
;;; g2-time resulting from encoding the explicit time-stamp in gfi-input-line.
;;; Each case is handled separately for higher speed.

(defun encode-gfi-input-line-g2-time (gfi-input-frame)
  (if (eq (gfi-input-time-stamp-format gfi-input-frame) 'relative)
      ;; Relative time stamp:
      (multiple-value-bind (relative-time-stamp end-index)
	  (read-number-from-string
	    (gfi-input-line gfi-input-frame)
	    0 (gfi-input-line-length gfi-input-frame))
	(setf (gfi-input-line-current-index gfi-input-frame) end-index)
	(if relative-time-stamp
	    (with-temporary-gensym-float-creation
		encode-gfi-input-line-g2-time
	      (cond
		((ignore-gfi-input-base-time? gfi-input-frame)
		 (when (gfi-input-line-g2-time gfi-input-frame)
		   (reclaim-managed-number
		     (gfi-input-line-g2-time gfi-input-frame)))
		 (setf (gfi-input-line-g2-time gfi-input-frame)
		       (store-managed-number
			 relative-time-stamp
			 (if (fixnump relative-time-stamp)
			     (+e (coerce-to-gensym-float relative-time-stamp)
				 (managed-float-value
				   (gfi-input-g2-time-at-start
				     gfi-input-frame)))
			     (+e (managed-float-value relative-time-stamp)
				 (managed-float-value
				   (gfi-input-g2-time-at-start
				     gfi-input-frame)))))))
		(t
		 (store-managed-number
		   relative-time-stamp
		   (if (fixnump relative-time-stamp)
		       (+e (coerce-to-gensym-float relative-time-stamp)
			   (managed-float-value
			     (gfi-input-base-time gfi-input-frame)))
		       (+e (managed-float-value relative-time-stamp)
			   (managed-float-value
			     (gfi-input-base-time gfi-input-frame)))))
		 (when (gfi-input-line-g2-time gfi-input-frame)
		   (reclaim-managed-number
		     (gfi-input-line-g2-time gfi-input-frame)))
		 (setf (gfi-input-line-g2-time gfi-input-frame)
		       relative-time-stamp))))
	    (progn
	      (when (gfi-input-line-g2-time gfi-input-frame)
		(reclaim-managed-number
		  (gfi-input-line-g2-time gfi-input-frame)))
	      (setf (gfi-input-line-g2-time gfi-input-frame) nil)
	      #w"couldn't parse the relative time stamp")))
      ;; Exlicit time stamp:
      (multiple-value-bind (seconds? minutes hours day month year
			    end-index)
	  ;; Note that as of version 4.0, seconds can be a managed-number.
	  (read-time-stamp-from-string (gfi-input-line gfi-input-frame)
				       0
				       (gfi-input-line-length gfi-input-frame))
	(setf (gfi-input-line-current-index gfi-input-frame) end-index)
	(if seconds?
	    (with-temporary-gensym-float-creation
		encode-gfi-input-line-g2-time
	      (let* ((second-fraction-float?
		       (if (managed-float-p seconds?)
			   (-e (managed-float-value seconds?)
			       (ffloore-first (managed-float-value seconds?)))))
		     (subsecond-time?
		       (if (and second-fraction-float?
				(/=e second-fraction-float? 0.0))
			   second-fraction-float?))
		     (seconds-fixnum?
		       (when seconds?
			 (if (managed-float-p seconds?)
			     (floore-first (managed-float-value seconds?))
			     seconds?)))
		     (explicit-time-stamp
		       (gensym-encode-unix-time-as-managed-float
			 seconds-fixnum? minutes hours day month year)))
		(when subsecond-time?
		  (mutate-managed-float-value
		    explicit-time-stamp
		    (+e subsecond-time?
			(managed-float-value explicit-time-stamp))))
		(if (ignore-gfi-input-base-time? gfi-input-frame)
		    (store-managed-number
		      explicit-time-stamp
		      (+e (-e (managed-float-value explicit-time-stamp)
			      (managed-float-value
				(gfi-input-base-time gfi-input-frame)))
			  (managed-float-value
			    (gfi-input-g2-time-at-start
			      gfi-input-frame)))))
		;; Note that as of version 4.0, seconds can be a managed-number.
		(reclaim-managed-number seconds?)
		(when (gfi-input-line-g2-time gfi-input-frame)
		  (reclaim-managed-number
		    (gfi-input-line-g2-time gfi-input-frame)))
		(setf (gfi-input-line-g2-time gfi-input-frame)
		      explicit-time-stamp)))
	    (progn
	      (when (gfi-input-line-g2-time gfi-input-frame)
		(reclaim-managed-number
		  (gfi-input-line-g2-time gfi-input-frame)))
	      (setf (gfi-input-line-g2-time gfi-input-frame) nil)
	      #w"couldn't parse the explicit time stamp")))))





;;; The defun-substitution-macro `parse-and-put-event-log-values' takes a
;;; gfi-input-frame, parses its gfi-input line, and puts the obtained value in
;;; the appropriate place.  It returns string if there was an error, non-string
;;; otherwise. The macro takes an argument which determines if the variables
;;; are checked for gfi-data-service.

(defun-substitution-macro parse-and-put-event-log-values
			  (gfi-input-frame no-data-service-required?)
  (loop
    do
    (multiple-value-bind (designation error-p)
	(parse-delimitter-then-designation gfi-input-frame)
      (when (and designation (not error-p))
	(let ((start-index-of-value
		(skip-to-after-gfi-delimitter-in-string
		  (gfi-input-line gfi-input-frame)
		  (gfi-input-line-current-index gfi-input-frame)
		  (gfi-input-line-length gfi-input-frame))))
	  (when (and start-index-of-value
		     (<f start-index-of-value
			 (gfi-input-line-length gfi-input-frame)))
	    (setf (gfi-input-line-current-index gfi-input-frame)
		  start-index-of-value)
	    (return (put-gfi-value-of-designation-into-appropriate-place
		      designation gfi-input-frame no-data-service-required?))))))
    (return (progn
	      (let ((legal-text-string
		      (copy-text-string (gfi-input-line gfi-input-frame))
		      ;; Obs.:   (MHD 3/2/96)
;		      (copy-string-filtering-out-non-gensym-characters
;			(gfi-input-line gfi-input-frame))
		      ))
		;; MHD: This crashes G2 now (probably) because the line contains
		;; tabs (probably) and tabs are not legal in a G2 text string.
		;; FIX!! (MHD 2/6/92)
		;; -- The above patches this problem somewhat -- as things
		;; now stand, for one thing, Tabs will turn into
		;; underscores (_); see convert-ascii-string-to-text-string-
		;; as-much-as-possible.  (MHD 2/6/92)
		(warning-message
		  2
		  "The GFI Input Interface ~NF could not parse an input line of ~
                 event log file ~S.  The line read is ~S."
		  gfi-input-frame
		  (gfi-input-pathname-string-of-stream? gfi-input-frame)
		  legal-text-string)
		(reclaim-text-string legal-text-string))
	      (close-gfi-input-interface gfi-input-frame)
	      #w"error"))))




;;; The substitution-macro `parse-and-put-spreadsheet-values' takes a
;;; gfi-input-frame, parses its gfi-input line, and puts the obtained values in
;;; the appropriate place.  It returns string if there was an error, non-string
;;; otherwise.  The macro takes an argument which determines if the variables
;;; are checked for gfi-data-service.

(defun-substitution-macro parse-and-put-spreadsheet-values
		(gfi-input-frame no-data-service-required?)
  (loop with current-index? = (gfi-input-line-current-index gfi-input-frame)
	and line = (gfi-input-line gfi-input-frame)
	and length = (gfi-input-line-length gfi-input-frame)
	and result = nil
	for designation in (gfi-input-spreadsheet-designations gfi-input-frame)
	do
    (if (=f current-index? length)
	(return
	  (progn
	    (let ((legal-text-string
		    (copy-text-string (gfi-input-line gfi-input-frame))
		    ;; Obs.:   (MHD 3/2/96)
;		    (copy-string-filtering-out-non-gensym-characters
;		      (gfi-input-line gfi-input-frame))
		    ))
	      ;; MHD: This crashes G2 now (probably) because the line contains
	      ;; tabs (probably) and tabs are not legal in a G2 text string.
	      ;; FIX!! (MHD 2/6/92)
	      ;; -- The above patches this problem somewhat -- as things
	      ;; now stand, for one thing, Tabs will turn into
	      ;; underscores (_); see convert-ascii-string-to-text-string-
	      ;; as-much-as-possible.  (MHD 2/6/92)
	      (warning-message
		2
		"An input line of the spreadsheet file ~S ~
                 of the GFI Input Interface ~NF ended unexpectedly.  The ~
                 line read is ~S."
		(gfi-input-pathname-string-of-stream? gfi-input-frame)
		gfi-input-frame
		legal-text-string)
	      (reclaim-text-string legal-text-string))
	    (close-gfi-input-interface gfi-input-frame)
	    #w"error")))

    (if (setq current-index? (skip-to-after-gfi-delimitter-in-string
			       line current-index? length))
	(progn
	  (setf (gfi-input-line-current-index gfi-input-frame) current-index?)
	  (if (and (<f current-index? length)
		   (not (char=w
			  (charw (gfi-input-line gfi-input-frame) current-index?)
			  gfi-delimitter)))
	      (if (text-string-p			;if error string returned
		    (setq result
			  (put-gfi-value-of-designation-into-appropriate-place
			    designation gfi-input-frame no-data-service-required?)))
		  (progn (close-gfi-input-interface gfi-input-frame)
			 (return result)))))
	(return (progn
		  (let ((legal-text-string
			  (copy-text-string (gfi-input-line gfi-input-frame))
			  ;; Obs.:   (MHD 3/2/96)
;			  (copy-string-filtering-out-non-gensym-characters
;			    (gfi-input-line gfi-input-frame))
			  ))
		    ;; MHD: This crashes G2 now (probably) because the line contains
		    ;; tabs (probably) and tabs are not legal in a G2 text string.
		    ;; FIX!! (MHD 2/6/92)
		    ;; -- The above patches this problem somewhat -- as things
		    ;; now stand, for one thing, Tabs will turn into
		    ;; underscores (_); see convert-ascii-string-to-text-string-
		    ;; as-much-as-possible.  (MHD 2/6/92)
		    (warning-message
		      2
		      "Couldn't parse an input line of spreadsheet file ~S ~
                       for the GFI Input Interface ~NF.  The line read ~
                       is ~S."
		      (gfi-input-pathname-string-of-stream? gfi-input-frame)
		      gfi-input-frame
		      legal-text-string)
		    (reclaim-text-string legal-text-string))
		  (close-gfi-input-interface gfi-input-frame)
		  #w"error")))))





;;; The function `synchronize-gfi-input-file' reads the input file of the
;;; gfi-input-frame and until the gfi-input-line-g2-time is greater than the
;;; current g2-time.  All values specified prior to the final line are put
;;; in place using put-gfi-value-of-designation-into-appropriate-place.
;;; Time-slice-expired-p is checked to ensure that there is still time to carry
;;; on synchronizing if override-time-slice-if-necessary-p is set to nil.
;;; Gfi-inputting? of gfi-input-frame must be t when this function is called.
;;; Also the special variable time-slice-expired-p has to be bound when this
;;; function is called.  It returns t if the file has been synchronized, nil if
;;; not.  The function takes an argument which determines if the variables
;;; are checked for gfi-data-service.  Upon error or EOF synchronization,
;;; the gfi-input-frame is closed.

(defun synchronize-gfi-input-file
       (gfi-input-frame do-not-override-time-slice-p no-data-service-required?)
  (loop with lines-read = 0
	with error-message? = nil
	do
    (with-temporary-gensym-float-creation synchronize-gfi-input-file
      (loop while (and (not
			 (text-string-p
			   (setq error-message?	;this also sets current-index
				 (encode-gfi-input-line-g2-time
				   gfi-input-frame))))
		       (<=e (managed-float-value
			      (gfi-input-line-g2-time gfi-input-frame))
			    (managed-float-value (clock-get current-g2-time))))
	    do
	(when (text-string-p
		(if (eq (gfi-input-file-format gfi-input-frame) 'event-log)
		    (parse-and-put-event-log-values
		      gfi-input-frame no-data-service-required?)
		    (parse-and-put-spreadsheet-values
		      gfi-input-frame no-data-service-required?)))
	  ;; If error then assumed warning message has been put out and
	  ;; gfi-input-frame has been deactivated.
	  (setf (gfi-input-file-synchronized? gfi-input-frame) nil)
	  (return-from synchronize-gfi-input-file nil))

	;; if read line does not return the line then EOF - always synchronized.
	;; Read line closes the gfi-input-frame upon EOF or error, and
	;;   returns nil.
	(when (null (read-one-gfi-input-line gfi-input-frame))
	  (setf (gfi-input-file-synchronized? gfi-input-frame) t)
	  (return-from synchronize-gfi-input-file t))

	(incff lines-read)
	    until (or (and do-not-override-time-slice-p
			   (setq time-slice-expired-p (time-slice-expired-p)))
		      ;; Prevent temporary float area overflow.
		      (=f (modf-positive lines-read 500) 0))))
	until (or (and do-not-override-time-slice-p
		       (or time-slice-expired-p
			   (setq time-slice-expired-p (time-slice-expired-p))))
		  (text-string-p error-message?)
		  (>e (managed-float-value
			(gfi-input-line-g2-time gfi-input-frame))
		      (managed-float-value (clock-get current-g2-time))))
	finally
	  (when (text-string-p error-message?)
	    (warning-message
	      2
	      "Error in reading the time stamp from the GFI file ~S for ~
 	       the GFI Input Interface ~NF:  ~A."
	      (gfi-input-pathname-string-of-stream? gfi-input-frame)
	      gfi-input-frame error-message?)
	    (close-gfi-input-interface gfi-input-frame)
	    (setf (gfi-input-file-synchronized? gfi-input-frame) nil)
	    (return nil))
	  (setf (gfi-input-file-synchronized? gfi-input-frame)
		(not time-slice-expired-p))
	  (return (not time-slice-expired-p))))



;;; The substitution macro `process-gfi-queue-of-variables-that-need-values' is
;;; called when the input file of the gfi-input-frame has been synchronized.
;;; The macro takes the list of variables and does the appropriate update
;;; operation on the variable.  The special variable time-slice-expired-p has to
;;; be bounded by the caller.

(defmacro process-gfi-queue-of-variables-that-need-values
	  (gfi-input-frame)
  (let ((queue-pair (gensym))
	(variable (gensym))
	(last-variable? (gensym)))
    `(loop with ,queue-pair
	     = (gfi-queue-of-variables-that-need-values ,gfi-input-frame)
	   with ,last-variable? = (car (queue-tail-cons-of-queue-pair ,queue-pair))
	   while (and (queue-list-of-queue-pair ,queue-pair)
		      (neq ,last-variable? (gfi-head-of-queue ,queue-pair)))
	   for ,variable = (gfi-dequeue-from-pair ,queue-pair)
	   do
       (clear-queued-by-local-data-server ,variable)
       (collect-one-shot-data-for-gfi-data-service ,variable)
	   until
	     (setq time-slice-expired-p (time-slice-expired-p)))))






;;;; GFI Input Interface Deactivation




(defun close-gfi-input-interface (gfi-input-frame)

  ;; If there are variables waiting for values, pretend that the frame is
  ;; still active, and serve the variables:
  (let ((queue (gfi-queue-of-variables-that-need-values gfi-input-frame)))
    (when queue
      (when (queue-list-of-queue-pair queue)
	(when system-is-running
	  (setf (gfi-input-file-synchronized? gfi-input-frame) t)
	  (let ((time-slice-expired-p nil))
	    (process-gfi-queue-of-variables-that-need-values gfi-input-frame)
	    (setq queue (gfi-queue-of-variables-that-need-values gfi-input-frame))
	    (loop for variable in (queue-list-of-queue-pair queue)
		  do
	      (clear-queued-by-local-data-server variable))))
	;; Even if we did process-gfi-queue-of-variables-that-need-values, some
	;; of the variables may have been put back into the queue, and so it
	;; should be reclaimed.
	(reclaim-gfi-list (queue-list-of-queue-pair queue)))
      (reclaim-gfi-cons queue)))
  (setf (gfi-queue-of-variables-that-need-values gfi-input-frame) nil)
  (setf (gfi-input-file-synchronized? gfi-input-frame) nil)

  ;; Take frame out from list of active GFI Input Interface frames
  (if (gfi-input-without-interruption? gfi-input-frame)
      (gfi-delete-from-queue
	gfi-input-frame
	queue-of-active-uninterruptable-gfi-input-interface-objects)
      (gfi-delete-from-queue
	gfi-input-frame
	queue-of-active-gfi-input-interface-objects))

  (when (gfi-current-input-designation gfi-input-frame)
    (reclaim-slot-value (gfi-current-input-designation gfi-input-frame))
    (setf (gfi-current-input-designation gfi-input-frame) nil))

  (setf  (gfi-inputting? gfi-input-frame) nil)

  ;; Close the GFI file
  (let ((input-stream (gfi-input-file-stream gfi-input-frame))
	(*current-computation-frame* gfi-input-frame))
    (if input-stream
	;; THEN
	(progn
	  (g2-stream-close input-stream)
	  (change-slot-value gfi-input-frame 'file-status 'closed)
	  (setf (gfi-input-file-stream gfi-input-frame) nil))
	;; ELSE
	(when (neq (get-slot-value gfi-input-frame 'file-status)
		   'failed-to-open)
	 (change-slot-value gfi-input-frame 'file-status 'ready-to-open))))

  (when (managed-float-p (gfi-input-base-time gfi-input-frame))
    (reclaim-managed-float (gfi-input-base-time gfi-input-frame))
    (setf (gfi-input-base-time gfi-input-frame) nil))

  (when (gfi-input-line gfi-input-frame)
    (reclaim-text-string (gfi-input-line gfi-input-frame))
    (setf (gfi-input-line gfi-input-frame) nil))

  (if (gfi-input-line-g2-time gfi-input-frame)
      (mutate-managed-float-value
	(gfi-input-line-g2-time gfi-input-frame) 0.0)
      (setf (gfi-input-line-g2-time gfi-input-frame)
	    (allocate-managed-float 0.0)))

  (setf (gfi-input-line-length gfi-input-frame) 0)
  (setf (gfi-input-line-current-index gfi-input-frame) 0)

  (when (gfi-input-pathname-string-of-stream? gfi-input-frame)
    (reclaim-text-string (gfi-input-pathname-string-of-stream?
			   gfi-input-frame))
    (setf (gfi-input-pathname-string-of-stream? gfi-input-frame) nil))

  (when (gfi-input-spreadsheet-designations gfi-input-frame)
    (reclaim-slot-value (gfi-input-spreadsheet-designations gfi-input-frame))
    (setf (gfi-input-spreadsheet-designations gfi-input-frame) nil)))



(def-class-method deactivate (gfi-input-interface)
  (close-gfi-input-interface gfi-input-interface)
  (funcall-superior-method gfi-input-interface))



;;;; File closer:



#+development
(defun close-gfi-files ()
  (loop with frame
	while (queue-list-of-queue-pair
		queue-of-active-uninterruptable-gfi-output-interface-objects)
	do
    (setq frame (gfi-dequeue-from-pair
		  queue-of-active-uninterruptable-gfi-output-interface-objects))
    (funcall-method 'deactivate frame))
  (loop with frame
	while (queue-list-of-queue-pair
		queue-of-active-gfi-output-interface-objects)
	do
    (setq frame (gfi-dequeue-from-pair
		   queue-of-active-gfi-output-interface-objects))
    (funcall-method 'deactivate frame))
  (loop with frame
	while (queue-list-of-queue-pair
		queue-of-active-uninterruptable-gfi-input-interface-objects)
	do
    (setq frame (gfi-dequeue-from-pair
		  queue-of-active-uninterruptable-gfi-input-interface-objects))
    (funcall-method 'deactivate frame))
  (loop with frame
	while (queue-list-of-queue-pair
		queue-of-active-gfi-input-interface-objects)
	do
    (setq frame (gfi-dequeue-from-pair
		  queue-of-active-gfi-input-interface-objects))
    (funcall-method 'deactivate frame)))






;;;; GFI DATA SERVICE




;;; Relevant user-accessible slots for GFI-DATA-SERVICE variables:
;;; 	data-server-map			::= gfi-data-server | ...etc...
;;;	gfi-interface-object		::= nil | <object-name>
;;;
;;; The unsaved (runtime) slots for GFI-DATA-SERVICE objects are:
;;;	gfi-last-value			::= nil | <managed-value>
;;;	gfi-time-of-last-value-update	::= nil | <g2-time>, a managed-float






(def-slot-value-reclaimer gfi-last-value (slot-value frame)
  (declare (ignore slot-value))
  (reclaim-managed-number-or-value (gfi-last-value frame)))



(add-grammar-rules
  `((data-server-spec ('gfi 'data 'server) gfi-data-server)
     (data-server-map ('gfi 'data 'server) gfi-data-server)))



(def-data-server
  'gfi-data-server
  'collect-one-shot-data-for-gfi-data-service
  'begin-collecting-data-for-gfi-data-service
  'stop-collecting-data-for-gfi-data-service
  'accept-data-from-gfi-data-service
  nil
  'initialize-gfi-data-server
  'set-external-variable-for-gfi
  'shut-down-gfi-data-server
  'post-on-message-board			;in module BOOKS
  nil
  nil
  'gfi-requests-accept-data-calls)




;;; Data server functions:




(defun-void collect-one-shot-data-for-gfi-data-service (variable)
  (if (gfi-data-service-p variable)
      (when (server-is-in-use (data-server 'gfi-data-server))
	(let ((gfi-input-frame-designation
		(gfi-input-interface-object variable))
	      gfi-input-frame
	      gfi-last-value)
	  (if (and gfi-input-frame-designation
		   (setq gfi-input-frame
			 (let ((*current-computation-frame* variable))
			   (evaluate-designation
			     gfi-input-frame-designation nil)))
		   (not (temporary-constant-p gfi-input-frame)))
	      (if (gfi-input-interface-p gfi-input-frame)
		  (cond
		    ((and (gfi-input-file-synchronized? gfi-input-frame)
			  (setq gfi-last-value (gfi-last-value variable)))
		     (if (eq (gfi-input-variables-update-mode
			       gfi-input-frame)
			     'on-request-sample-and-hold)
			 (put-current-value-using-and-preserving-gfi-last-value
			   gfi-input-frame variable gfi-last-value)
			 (put-current-value-using-and-reclaiming-gfi-last-value
			   gfi-input-frame variable gfi-last-value)))
		    ((and (gfi-inputting? gfi-input-frame)
			  (not (queued-by-local-data-server-p variable)))
		     (gfi-enqueue-in-pair
		       variable
		       (gfi-queue-of-variables-that-need-values
			 gfi-input-frame))
		     (set-queued-by-local-data-server variable))

		    ;; Converted to the following; I think I improved
		    ;; the wording a bit, too.  (MHD 2/6/92)
		    ((not (active-p gfi-input-frame))
		     (warning-message
			 2
			 "The GFI input interface object ~ND is not active ~
                        and thus could not supply a value in response ~
                        to a request by ~NF."
		       gfi-input-frame-designation
		       variable)))
		  
		  (progn
		    (reclaim-if-temporary-constant-function gfi-input-frame)
		    (warning-message
			2
			"The GFI input interface object of ~NF, ~ND, is not a GFI ~
                       Input Interface.  Hence no value could be obtained ~
                       for the variable via the GFI Data Server."
		      variable)))
		  (progn
		    (reclaim-if-temporary-constant-function gfi-input-frame)
		    (if gfi-input-frame-designation
			(warning-message
			    2		      
			    "The GFI input interface object of ~NF, ~ND, does ~
                       not exist.  Hence no value could be ~
		       obtained for it via the GFI Data Server."
			  variable gfi-input-frame-designation)
			(warning-message
			    2
			    "The GFI input interface object of ~NF has not yet ~
 		       been specified.  Hence no value could be obtained ~
                       for it via the GFI Data Server."
			  variable))))))
      (warning-message
	  1
	  "The variable ~NF has not been given the gfi-data-service ~
           superior class and so it may not have GFI as its data server."
	variable))
  nil)



(defun begin-collecting-data-for-gfi-data-service (variable interval)
  (with-temporary-gensym-float-creation gfi-begin-collecting-data
    (if (gfi-data-service-p variable)
	(with-current-scheduling
	    ((task-for-local-data-server? variable)
	     (priority-of-data-service data-server-parameters)
	     (if (fixnump interval)
		 (coerce-fixnum-to-gensym-float interval)
		 (managed-float-value interval)))
	  (collect-one-shot-data-for-gfi-data-service variable))
	(warning-message 2		; this message also appears above!
	    "The variable ~NF has not been given the gfi-data-service ~
             superior class and so it may not have GFI as its data server."
	  variable))))

;; jh, 5/23/91.  Changed begin-collecting-data-for-gfi-data-service to replace
;; the call to priority-of-continued-data-service with one to
;; priority-of-data-service.  See comments under the system table definition in
;; VARIABLES and in take-actions-at-start-of-clock-tick in CYCLES for an
;; explanation of the name change.




(defun stop-collecting-data-for-gfi-data-service (variable)
  (cancel-task (task-for-local-data-server? variable)))







;;; The defun-substitution-macro
;;; `output-and-reclaim-gfi-list-of-new-spreadsheet-output-values'
;;; prints a list of gfi-queue-items as one line in the spreadsheet format, and
;;; reclaims each of the gfi-queue-items as it prints the output line.
;;;
;;; (output-and-reclaim-gfi-list-of-new-spreadsheet-output-values stream list)

(defun-substitution-macro
    output-and-reclaim-gfi-list-of-new-spreadsheet-output-values
    (gfi-output-frame output-list)
  (loop with item
	for rest-of-list on output-list
	do
    (gfi-write-char gfi-delimitter gfi-output-frame)
    (when (setq item (car rest-of-list))
      (with-temporary-gensym-float-creation
	output-and-reclaim-gfi-list-of-new-spreadsheet-output-values
	(output-gfi-value (extract-cached-number-or-value
			    (gfi-queue-item-value item))
			  (gfi-queue-item-data-type item)
			  gfi-output-frame))
      (reclaim-gfi-queue-item item)
      (setf (car rest-of-list) nil))))




;;; The macro `output-gfi-queued-values-in-spreadsheet-format' takes a queue of
;;; gfi-queue-items and outputs them to the GFI output file in the spreadsheet
;;; format.  It returns T if there are no more queued items to output, and NIL
;;; if it needs to be called again for this frame.  If the maximum line limit is
;;; exceeded for the file, the output frame will be deactivated and this macro
;;; will return T.  If the forcibly-flush argument is given a non-nil value,
;;; then the time slice will be ignored and all values will be flushed out to
;;; the file.  If the forcibly-flush argument is given a 1, then just one value
;;; will be flushed.  This macro is guaranteed to output at least one line,
;;; regardless of the time slice.

;;; To output the queue in a spreadsheet format, take a clean list (of the right
;;; length), fill it up from the dequeued gfi-queue-items until the g2-time at
;;; enqueue changes (keeping in mind that we have to reclaim all values that are
;;; over-written, i.e.  designations that receive more than one value in the
;;; same clock tick).  When the time-stamp changes (or when the queue is empty),
;;; we write the time stamp (using the line's g2-time-stamp), output the line,
;;; and increment the line count.

;;; (output-gfi-queued-values-in-spreadsheet-format-macro frame forcibly-flush)

(defun-substitution-macro
  output-gfi-queued-values-in-spreadsheet-format
  (gfi-output-frame forcibly-flush)
  ;; Note that forcibly-flush has got nothing go do with whether
  ;; g2-stream-flush is called.
  (loop with line-limit = (maximum-number-of-output-lines gfi-output-frame)
	and queue = (gfi-queue-of-new-output-values gfi-output-frame)
	and item
	and output-list = (gfi-list-of-new-spreadsheet-output-values
			    gfi-output-frame)
	and pointer
	with head-of-queue? = (gfi-head-of-queue queue)
	with g2-time-of-current-line
	  = (if head-of-queue? (gfi-queue-item-g2-time head-of-queue?))
	while head-of-queue?
	do
    (if (and line-limit
	     (>=f (number-of-lines-output-so-far gfi-output-frame) line-limit))
	(progn
	  (warning-message-for-limit-reached-in-gfi-output gfi-output-frame)
	  ;; the above function will set the new-gfi-output-values-this-cycle?
	  ;; slot to nil and reclaim all the queues
	  (return t))
	;; Fill line up
	(loop with new-line-required? = nil
	      with position? = nil
	      while
	      (with-temporary-gensym-float-creation
		  output-gfi-queued-values-in-spreadsheet-format
		(and head-of-queue?
		     (=e (managed-float-value g2-time-of-current-line)
			 (managed-float-value
			   (gfi-queue-item-g2-time head-of-queue?)))))
	      do (setq item (gfi-dequeue-from-pair queue))
		 (setq head-of-queue? (gfi-head-of-queue queue))
		 (setq position?
		       (or (gfi-queue-item-position? item)
			   (get-gfi-spreadsheet-field-index
			     (gfi-queue-item-variable item)
			     (gfi-output-spreadsheet-field-index-hash
			       gfi-output-frame))))
		 (setq pointer
		       (if position? (nthcdr position? output-list)))
		 (cond
		   ((and position? pointer)	; pointer should never be nil;
		    (setq new-line-required? t)	;   this is a reality check.
		    (if (car pointer)
			(reclaim-gfi-queue-item (car pointer)))
		    (setf (car pointer) item))
		   (t
		    ;; The following code, and the message it produces, looks
		    ;; very similar to those produced by warning-message-for-
		    ;; unnameable-variable; collapse parts of them!  (MHD
		    ;; 2/6/92)
		    (let ((designation-or-substitute-string
			    (tformat-text-string
			      (if (gfi-queue-item-designation? item)
				  "\"~ND\""	; see note below
				  "a designation in the GFI Output Interface")
			      (gfi-queue-item-designation? item))))
		      ;; When position? is nil, gfi-queue-item-designation?
		      ;; should have been assigned a value in
		      ;; handle-gfi-output-interface-new-values.
		      (warning-message
			2
			"The GFI Output Interface ~NF found a variable or ~
                         parameter, ~A, which matches ~A.  However, when the ~
                         GFI Output Interface started ~
			 to output to the file ~S, the variable did not match ~
			 the desgnation.  The value of this variable or ~
			 parameter will be ignored by GFI."
			gfi-output-frame (gfi-queue-item-variable-name item)
			designation-or-substitute-string
			(gfi-output-pathname-string-of-stream?
			  gfi-output-frame)))
		    (reclaim-gfi-queue-item item)))
	      finally
		;; Print Line
		(when new-line-required?
		  (output-appropriate-gfi-time-stamp
		    gfi-output-frame g2-time-of-current-line)
		  (output-and-reclaim-gfi-list-of-new-spreadsheet-output-values
		    gfi-output-frame output-list)
		  (gfi-terpri gfi-output-frame)
		  (incff (number-of-lines-output-so-far gfi-output-frame)))
		(if head-of-queue?
		    (setq g2-time-of-current-line
			  (gfi-queue-item-g2-time head-of-queue?)))))
    
	until (or (and (not forcibly-flush) (time-slice-expired-p))
		  (and (fixnump forcibly-flush) (=f forcibly-flush 1)))
	finally
;	  (g2-stream-flush output-stream)
	  (if head-of-queue?
	      (return nil)
	      (progn
		(setf (new-gfi-output-values-this-cycle? gfi-output-frame) nil)
		(return t)))))

;; Review enclosing of designation in double quotes above; it is not a standard,
;; although I believe we do need something like that.  Also review use of the
;; term "Designation"! (MHD 2/5/92)




;;; The macro `output-gfi-queued-values-in-event-log-format' takes a
;;; gfi-output-frame and outputs its queue of gfi-queue-items to the GFI output
;;; file in the event log format.  This macro returns T if all queued values for
;;; this frame have been output, and NIL if the time slice expired before all
;;; values could be sent.  If the forcibly-flush argument is given a non-nil
;;; value, then the time slice will not be checked and all values will be
;;; flushed.  If the forcibly-flush argument is given a 1, then only one value
;;; will be flushed in this call.  If the maximum line size of the output file
;;; is met or exceeded, this macro will warn the operator and deactivate the
;;; output frame, returning T.  Except for the maximum line count overflow case,
;;; this macro is guaranteed to output at least one line, regardless of the
;;; time-slice.

;;; (output-gfi-queued-values-in-event-log-format-macro frame forcibly-flush)

(defun-substitution-macro output-gfi-queued-values-in-event-log-format
			  (gfi-output-frame forcibly-flush)
  ;; Note that forcibly-flush has got nothing go do with whether
  ;; g2-stream-flush is called.
  (loop with line-limit = (maximum-number-of-output-lines gfi-output-frame)
	and queue = (gfi-queue-of-new-output-values gfi-output-frame)
	and item
	for head-of-queue = (gfi-head-of-queue queue)
	while head-of-queue
	do
    (if (and line-limit
	     (>=f (number-of-lines-output-so-far gfi-output-frame) line-limit))
	;; THEN
	(progn
	  (warning-message-for-limit-reached-in-gfi-output gfi-output-frame)
	  ;; the above function will set the new-gfi-output-values-this-cycle?
	  ;; slot to nil and reclaim all the queues
	  (return t))
	;; ELSE
	(let* (designation?)
	  (setq item (gfi-dequeue-from-pair queue))
	  (setq designation?
		(or (gfi-queue-item-designation? item)
		    (gfi-queue-item-variable-designation? item)))
	  (cond
	    (designation?
	     (output-appropriate-gfi-time-stamp
	       gfi-output-frame (gfi-queue-item-g2-time item))
	     (gfi-write-char gfi-delimitter gfi-output-frame)
	     (write-designation-to-stream designation? gfi-output-frame)
	     (gfi-write-char gfi-delimitter gfi-output-frame)
	     (with-temporary-gensym-float-creation
	       output-gfi-queued-values-in-event-log-format-macro
	       (output-gfi-value (extract-cached-number-or-value
				   (gfi-queue-item-value item))
				 (gfi-queue-item-data-type item)
				 gfi-output-frame))
	     (gfi-terpri gfi-output-frame)
	     (incff (number-of-lines-output-so-far gfi-output-frame)))
	    (t
	     (warning-message-for-unnameable-variable
	       gfi-output-frame (gfi-queue-item-variable-name item)
	       designation?)))
	  (reclaim-gfi-queue-item item)))
    
	until (or (and (not forcibly-flush) (time-slice-expired-p))
		  (and (fixnump forcibly-flush) (=f forcibly-flush 1)))
	finally
;	  (g2-stream-flush output-stream)
	  (if head-of-queue
	      (return nil)
	      (progn
		(setf (new-gfi-output-values-this-cycle? gfi-output-frame) nil)
		(return t)))))




;;; The function `output-gfi-queued-values-to-stream' takes a GFI Output
;;; Interface stream and outputs values that have been queued for this output
;;; frame, reclaiming the output values as they are sent.  Passing a non-nil
;;; forcibly-flush argument will force this function to output all queued values
;;; for the output frame, regardless of the time slice.  Passing a 1 as the
;;; forcibly-flush argument will flush just one value.  Passing NIL for this
;;; argument will allow this function to stop outputting when the slice is
;;; expired.  If all queued values have been output, this function returns T.
;;; If there are still values waiting to be output, it returns NIL.

(defun-simple output-gfi-queued-values-to-stream
	      (gfi-output-frame forcibly-flush)
  ;; Note that forcibly-flush has got nothing go do with whether
  ;; g2-stream-flush is called.
  (case (gfi-output-file-format gfi-output-frame)
	 (spreadsheet
	   (output-gfi-queued-values-in-spreadsheet-format
	     gfi-output-frame forcibly-flush))
	 (event-log
	   (output-gfi-queued-values-in-event-log-format
	     gfi-output-frame forcibly-flush))))




;;; The function `accept-data-from-gfi-data-service' is called at the start of
;;; every clock tick to output to and input from GFI files.  The gfi frames
;;; that are currently or waiting to perform i/o are in four queues.  The first
;;; two queues contain input and output frames, respectively, that are
;;; uninterruptable (i.e., the i/o does not stop upon time slice expiration).
;;; The second two queues contain input and output frames, respectively, that
;;; yield upon time slice expiration.  (Currently, the only uninterruptable
;;; input mode or output frequency is "when activated, without interruption".)
;;; If the gfi-output-file-update-frequency is 'when-received-value, and there
;;; are queued values to output.  It will output as many of the queued value as
;;; possible.  The function returns NIL if all the frames have not been
;;; processed because of time slice expiration. Otherwise, non-nil is returned.
;;;
;;; NUPEC Modification:
;;; Handle input and output of NUPEC-snapshot files.

(defun accept-data-from-gfi-data-service ()
  
  (let ((time-slice-expired-p nil))

    (progn

      ;; Check the queue of Uninterruptable GFI Input Interface objects:
      ;;   Process this queue before the interruptable queues.  Don't check for
      ;;   time-slice expiration.  Process all frames in the queue.
      (when (queue-list-of-queue-pair
	      queue-of-active-uninterruptable-gfi-input-interface-objects)
	(loop with gfi-input-frame
	      and number-of-frames-so-far = 0
	      and initial-number-of-frames	;   are all active frames
		= (length
		    (queue-list-of-queue-pair
		      queue-of-active-uninterruptable-gfi-input-interface-objects))

	      do
	  (when (setq gfi-input-frame
		      (gfi-dequeue-from-pair
			queue-of-active-uninterruptable-gfi-input-interface-objects))
	    (when (not (gfi-input-file-stream gfi-input-frame))
	      (open-gfi-input-interface gfi-input-frame))
	    (when (gfi-inputting? gfi-input-frame)
	      (cond
		((eq (gfi-input-file-format gfi-input-frame) 'nupec-snapshot)
		 (when (gfi-input-nupec-snapshot-values-periodically
			 gfi-input-frame nil nil
			 (gfi-input-ignore-data-server?
			   gfi-input-frame))
		   (warning-message
		     2 "NUPEC Snaphot Input for ~NF has completed."
		     gfi-input-frame)
		   (close-gfi-input-interface gfi-input-frame)))
		((eq (gfi-input-file-format gfi-input-frame)
		     'nupec-snapshot-with-restart-time)
		 (when (gfi-input-nupec-snapshot-values-periodically
			 gfi-input-frame t nil
			 (gfi-input-ignore-data-server?
			   gfi-input-frame))
		   (warning-message
		     2 "NUPEC Snaphot Input for ~NF has completed."
		     gfi-input-frame)
		   (close-gfi-input-interface gfi-input-frame)))
		(t
		 ;; else, event or spread-sheet input file format
		 (when (synchronize-gfi-input-file
			 gfi-input-frame
			 nil
			 (gfi-input-ignore-data-server?
			   gfi-input-frame))
		   ;; test if the file is not at eof (was not closed).
		   (when (gfi-inputting? gfi-input-frame) 
		     (warning-message
		       2
		       "GFI Input Interface for ~NF has completed.  There ~
                        remain unread values with future timestamps in file ~S."
		       gfi-input-frame
		       (gfi-input-pathname-string-of-stream? gfi-input-frame))
		     (close-gfi-input-interface gfi-input-frame)))))
	      
	      ;; Synchronize-gfi-input-file removes the frame from the queue when
	      ;;   an error or eof occurs (by closing the input-interface frame).
	      ;;   Since the second argument specifies "not to check for time
	      ;;   slice" expiration, the function returns only upon success or
	      ;;   error.
	      ;; Currently, only "when activated" input frames are in this queue!!
	      ;;   In future versions, we may need to check for "variables that
	      ;;   need values", if "input on request" can be also
	      ;;   uninterruptable.  In that case, call
	      ;;   (process-gfi-queue-of-variables-that-need-values gfi-input-frame)
	      ))
	  (incff number-of-frames-so-far)

	  
	      until (>=f number-of-frames-so-far initial-number-of-frames)))
      
      
      ;; Check the queue of Uninterruptable GFI Output Interface objects:
      ;;   Process this queue before the interruptable queues.  Don't check for
      ;;   time-slice expiration.  Process all frames in the queue.
      (when (queue-list-of-queue-pair
	      queue-of-active-uninterruptable-gfi-output-interface-objects)
	
	(loop with gfi-output-frame		; in this loop, we assume there
	      and number-of-frames-so-far = 0
	      and initial-number-of-frames	;   are all active frames
		= (length
		    (queue-list-of-queue-pair
		      queue-of-active-uninterruptable-gfi-output-interface-objects))


	      do
	  (when (setq gfi-output-frame
		      (gfi-dequeue-from-pair
			queue-of-active-uninterruptable-gfi-output-interface-objects))
	    (when (not (gfi-output-file-stream gfi-output-frame))
	      (open-gfi-output-interface gfi-output-frame))
	    (when (gfi-outputting? gfi-output-frame)
	      ;; Currently, only "input when activated, without interruption" is on
	      ;;   this queue.  May need to handle other cases, e.g, when "output
	      ;;   to file when variables receive values" can be uninterruptable.
	      
	      (case (gfi-output-file-format gfi-output-frame)
		((nupec-snapshot nupec-snapshot-with-restart-time)
		 (when (gfi-output-nupec-snapshot-values-periodically
			 gfi-output-frame nil)
		   (warning-message
		     2 "NUPEC Snaphot Output for ~NF has completed."
		     gfi-output-frame)
		   (close-gfi-output-interface gfi-output-frame t)))
		
		(spreadsheet
		 ;; The return value of the following gfi-output functions is
		 ;;   nil when there is an error and the output-frame has already
		 ;;   been closed.  
		 (when (gfi-output-spreadsheet-values-periodically gfi-output-frame nil)
		   (warning-message
		     2 "GFI Output Interface for ~NF, using file ~S, has completed."
		     gfi-output-frame
		     (gfi-output-pathname-string-of-stream? gfi-output-frame))
		   (close-gfi-output-interface gfi-output-frame t)))
		(t
		 ;; event-log
		 (when (gfi-output-event-log-values-periodically gfi-output-frame nil)
		   (warning-message
		     2 "GFI Output Interface for ~NF, using file ~S, has completed."
		     gfi-output-frame
		     (gfi-output-pathname-string-of-stream? gfi-output-frame))
		   (close-gfi-output-interface gfi-output-frame t))))))
	  (incff number-of-frames-so-far)

	  
	      until (>=f number-of-frames-so-far initial-number-of-frames)))
      
      
      ;; Check the queue of GFI Input Interface objects:
      ;;
      (when (queue-list-of-queue-pair queue-of-active-gfi-input-interface-objects)
	(loop with gfi-input-frame
	      and number-of-frames-so-far = 0
	      and initial-number-of-frames	;   are all active frames
		= (length
		    (queue-list-of-queue-pair
		      queue-of-active-gfi-input-interface-objects))
	      do
	  (when (setq gfi-input-frame
		      (gfi-dequeue-from-pair
			queue-of-active-gfi-input-interface-objects))
	    (gfi-enqueue-in-pair
	      gfi-input-frame queue-of-active-gfi-input-interface-objects)
	    (when (not (gfi-input-file-stream gfi-input-frame))
	      (open-gfi-input-interface gfi-input-frame))
	    
	    (when (gfi-inputting? gfi-input-frame)
	      (cond
		((eq (gfi-input-file-format gfi-input-frame) 'nupec-snapshot)
		 ;; process "some" snapshot values -yield to time-slice-expired-p
		 (when (gfi-input-nupec-snapshot-values-periodically
			 gfi-input-frame nil t
			 (gfi-input-ignore-data-server?
			   gfi-input-frame))
		   (warning-message
		     2 "NUPEC Snaphot Input for ~NF has completed."
		     gfi-input-frame)
		   (close-gfi-input-interface gfi-input-frame)))
		((eq (gfi-input-file-format gfi-input-frame)
		     'nupec-snapshot-with-restart-time)
		 ;; process "some" snapshot values -yield to time-slice-expired-p
		 (when (gfi-input-nupec-snapshot-values-periodically
			 gfi-input-frame t t
			 (gfi-input-ignore-data-server?
			   gfi-input-frame))
		   (warning-message
		     2 "NUPEC Snaphot Input for ~NF has completed."
		     gfi-input-frame)
		   (close-gfi-input-interface gfi-input-frame)))
		(t
		 ;; else, event or spread-sheet input file format
		 (if (eq (gfi-input-variables-update-mode gfi-input-frame)
			 'input-one-shot-when-activated)
		     ;; Only synchronizes variable values that do not have
		     ;; "future" timestamps.  The special variable
		     ;; time-slice-expired-p is bound when the above function is
		     ;; called.  Synchronize-gfi-input-file removes the frame
		     ;; from queue when an error or eof occurs (by closing the
		     ;; input-interface frame).
		     (if (synchronize-gfi-input-file
			   gfi-input-frame
			   t
			   (gfi-input-ignore-data-server?
			     gfi-input-frame))
			 ;; test if the file is not at eof (was not closed).
			 (when (gfi-inputting? gfi-input-frame) 
			   (warning-message
			     2
			     "GFI Input Interface for ~NF has completed. ~
                              There remain unread values with future timestamps ~
                              in file ~S."
			     gfi-input-frame
			     (gfi-input-pathname-string-of-stream? gfi-input-frame))
			   (close-gfi-input-interface gfi-input-frame)))
		     
		     (when (synchronize-gfi-input-file
			     gfi-input-frame
			     t
			     (gfi-input-ignore-data-server?
			       gfi-input-frame))
		       (process-gfi-queue-of-variables-that-need-values
			 gfi-input-frame)))))))
	  (incff number-of-frames-so-far)
	      until (or (>=f number-of-frames-so-far initial-number-of-frames)
			time-slice-expired-p)))
      
      
      ;; Check the queue of GFI Output Interface objects:
      ;;   We want to try to at least output one item, hence the  
      ;;   time-slice-expired-p variable is only checked after one item is output.
      (when (queue-list-of-queue-pair
	      queue-of-active-gfi-output-interface-objects)
	(loop with gfi-output-frame		; in this loop, we assume there
	      and number-of-frames-so-far = 0
	      and initial-number-of-frames	;   are all active frames
		= (length
		    (queue-list-of-queue-pair
		      queue-of-active-gfi-output-interface-objects))
	      do
	  
	  (when (setq gfi-output-frame
		      (gfi-dequeue-from-pair
			queue-of-active-gfi-output-interface-objects))
	    (gfi-enqueue-in-pair gfi-output-frame
				 queue-of-active-gfi-output-interface-objects)
	    (when (not (gfi-output-file-stream gfi-output-frame))
	      (open-gfi-output-interface gfi-output-frame))
	    (when (gfi-outputting? gfi-output-frame)
	      (cond ((new-gfi-output-values-this-cycle? gfi-output-frame)
		     (setq time-slice-expired-p
			   (not (output-gfi-queued-values-to-stream
				  gfi-output-frame nil))))
		    ((or (eq (gfi-output-file-format gfi-output-frame)
			     'nupec-snapshot)
			 (eq (gfi-output-file-format gfi-output-frame)
			     'nupec-snapshot-with-restart-time))
		     (when (gfi-output-nupec-snapshot-values-periodically
			     gfi-output-frame t)
		       (warning-message
			 2 "NUPEC Snaphot Output for ~NF has completed."
			 gfi-output-frame)
		       (close-gfi-output-interface gfi-output-frame t)))
		    
		    ((eq (gfi-output-file-update-frequency gfi-output-frame)
			 'output-one-shot-when-activated)
		     (if (eq (gfi-output-file-format gfi-output-frame) 'spreadsheet)
			 ;; The return value of the following gfi-output
			 ;;   functions is nil, when the time slice has expired
			 ;;   or when there is an error and the output-frame has
			 ;;   already been closed.  It sets the special variable
			 ;;   time-slice-expired-p.
			 (when (gfi-output-spreadsheet-values-periodically
				 gfi-output-frame t)
			   (warning-message
			     2 "GFI Output Interface for ~NF, using file ~S, has completed."
			     gfi-output-frame
			     (gfi-output-pathname-string-of-stream? gfi-output-frame))
			   (close-gfi-output-interface gfi-output-frame t))
			 (when (gfi-output-event-log-values-periodically
				 gfi-output-frame t)
			   (warning-message
			     2 "GFI Output Interface for ~NF, using file ~S, has completed."
			     gfi-output-frame
			     (gfi-output-pathname-string-of-stream? gfi-output-frame))
			   (close-gfi-output-interface gfi-output-frame t)))))))
	  (incff number-of-frames-so-far)
	      until (or (>=f number-of-frames-so-far initial-number-of-frames)
			time-slice-expired-p)))

      )
    
    ;; Return NIL if we have more to do but the time has expired.
    (not time-slice-expired-p)))




;;; The function `gfi-requests-accept-data-calls' determines whether or not GFI
;;; could need to have accept-data called for it.  Note that if anything changes
;;; the value of this function from NIL to T, then the function
;;; schedule-data-server-accept-data-calls must be called to ensure the restart
;;; of accept data calls in general.

(defun gfi-requests-accept-data-calls ()
  (or (loop for input being each class-instance of 'gfi-input-interface
	    thereis (and (active-p input) (gfi-input-when-active input)))
      (loop for output being each class-instance of 'gfi-output-interface
	    thereis (and (active-p output) (gfi-output-when-active output)))))




(defun initialize-gfi-data-server ()
  (setf (server-is-in-use (data-server 'gfi-data-server)) t)
  nil)




(defun set-external-variable-for-gfi (variable value data-type)
  (warning-message
    2
    "An attempt was made to set the external value of the variable ~NF, ~
     which gets data service through the GFI Data Server, to the value ~
     ~NV.  The set operation is not allowed within this data server."
    variable
    value data-type))




(defun shut-down-gfi-data-server ()
  (setf (server-is-in-use (data-server 'gfi-data-server)) nil)
  nil)






;;;; NUPEC Write Snapshot File




;;; The NUPEC snapshot file is written when a GFI output interface input
;;; object is activated and the "GFI output file format" slot has the value
;;; "NUPEC snapshot [with restart time]".  (It is recommended that the "GFI
;;; output variable frequency"  slot be set to "write to file when activated,
;;; without interruption in order to emit a consistent set of variable and
;;; parameter values.)  
;;;
;;; The snapshot file consists of the time of the snapshot and the current
;;; values and histories of the variables and parameters specified in the GFI
;;; output values slot. 

;;; The format of the snapshot (ascii) file is:
;;; 
;;; <timestamp><TAB>the current time<TAB>0<NEWLINE>
;;; <variable-or-parameter-entry> ...
;;;
;;; Each variable or parameter entry will have the following format.
;;;
;;; <designation><TAB><history-count><TAB><most-recent-value><TAB>
;;; <collection-time>[<TAB><expiration-time-or-symbol>]<NEWLINE>
;;; <TAB><history-timestamp-1><TAB><history-value-1><NEWLINE>
;;; <TAB><history-timestamp-2><TAB><history-value-2><NEWLINE>
;;; etc. ...
;;; <TAB><history-timestamp-n><TAB><history-value-n><NEWLINE>




;;; The function `gfi-output-nupec-snapshot-values-periodically' is called to
;;; write the current value and history of parameters and variables.
;;;
;;; The time slice argument determines if this function is to be interrupted
;;; when the time slice expires.  If interrupted, the function continues output
;;; where it left off, the next time it is called with the same
;;; gfi-output-frame.  (This function only stops after the complete history of a
;;; variable or parameter is written.)
;;;
;;; If the GFI NUPEC snapshot file is to be output periodically, the function
;;; should be scheduled to be called cyclically.  Otherwise, this function can
;;; be called directly to "immediately" output the values.
;;;
;;; This function finds all the frames matching each of the specified
;;; designations and outputs for each variable and parameter the value returned
;;; by get-current-value and its history.

;; ** Note: **
;; Based on gfi-output-event-log-values-periodically - see comments in code (one
;; change).

(defun gfi-output-nupec-snapshot-values-periodically
       (gfi-output-frame do-not-override-time-slice-p)  
  (when (gfi-outputting? gfi-output-frame)	;(ie. active and outputting)
    (let ((*current-computation-frame* gfi-output-frame)
	  (time-slice-expired-p nil)
	  (output-stream (gfi-output-file-stream gfi-output-frame))
	  (output-limit? (maximum-number-of-output-lines gfi-output-frame))
	  (number-of-designations-already-handled
	    (or (number-of-periodic-specified-designation-handled
		  gfi-output-frame)
		0)))
      (when output-stream
	(loop for designation-list on
		  (nthcdr number-of-designations-already-handled
			  (car (gfi-output-values gfi-output-frame)))
	      for designation = (car designation-list)
	      as not-unique-designation-p
		 in (gfi-output-not-unique-designation-p-results
		      gfi-output-frame)
	      as unique-designation-p = (not not-unique-designation-p)
	      count t into value-count
	      do
	  (if (and output-limit?
		   (<=f output-limit?
			(number-of-lines-output-so-far gfi-output-frame)))
	      ;; THEN
	      (progn
		;; shouldn't this return immediately if true ?? cpm 12may89
		(warning-message-for-limit-reached-in-gfi-output
		  gfi-output-frame)
		nil)
	      ;; ELSE
	      (let* ((eval-list-of-designation-values
		       (serve-eval-list-of-designation-values designation)))
		(if eval-list-of-designation-values
		    ;; Then
		    (loop with designation?
			  for variable in eval-list-of-designation-values
			  do
		      (when (and output-limit?
				 (<=f output-limit?
				      (number-of-lines-output-so-far
					gfi-output-frame)))
			(loop-finish))
		      (setq designation?
			    (cond
			      (unique-designation-p
			       (copy-tree-using-eval-conses designation))
			      ((temporary-constant-p variable)
			       nil)
			      (t
			       (generate-designation-for-block variable))))
		      (cond
			(designation?
			 (if (and (not (temporary-constant-p variable))
				  (variable-or-parameter-p variable))

			     ;; *** This is the main change from ***
			     ;; gfi-output-event-log-values-periodically.
			     ;; Abstract the rest of this function at some
			     ;; point!! cpm, 11/21/89
			     (write-gfi-nupec-snapshot-variable-state
			       variable gfi-output-frame)

			     (progn
			       (reclaim-if-temporary-constant-function variable)
			       (warning-message-for-wrong-reference-for-gfi-designation
				 gfi-output-frame designation? variable))))
			((not (framep variable))
			 (warning-message-for-non-frame-reference-for-gfi-designation
			   gfi-output-frame variable))
			(t
			 (warning-message-for-unnameable-variable
			   gfi-output-frame
			   variable
			   nil)))
		      (when unique-designation-p
			(reclaim-eval-tree designation?))
			  finally
			    (reclaim-eval-tree eval-list-of-designation-values))
		    ;; Else
		    (warning-message-for-wrong-reference-for-gfi-designation
		      gfi-output-frame designation nil))))

		    until (and do-not-override-time-slice-p
			       (setf time-slice-expired-p
				     (time-slice-expired-p)))
		    finally
		      (setq number-of-designations-already-handled
			    (if (null (cdr designation-list))
				0		; modulo here
				(+f number-of-designations-already-handled
				    value-count))))
	      
	      (if (and do-not-override-time-slice-p time-slice-expired-p)
		  (progn (setf (number-of-periodic-specified-designation-handled
				 gfi-output-frame)
			       number-of-designations-already-handled)
			 nil)
		  ;; else - finished
		  (progn (setf (number-of-periodic-specified-designation-handled
				 gfi-output-frame)
			       0)
			 t))))))




;;; The function `write-gfi-nupec-snapshot-variable-state' is called to
;;; write the current value and history of a parameter or and variable.
;;;
;;; The format of the output is:
;;; <designation><TAB><history-count><TAB><most-recent-value><TAB>
;;; <collection-time>[<TAB><expiration-time-or-symbol>]<NEWLINE>
;;; <TAB><history-timestamp-1><TAB><history-value-1><NEWLINE>
;;; <TAB><history-timestamp-2><TAB><history-value-2><NEWLINE>
;;; etc. 
;;; <TAB><history-timestamp-n><TAB><history-value-n><NEWLINE>

(defun write-gfi-nupec-snapshot-variable-state (variable gfi-output-frame)
  (let* ((designation? (generate-designation-for-block variable))
	 (history? (variable-or-parameter-stored-histories? variable))
	 (data-type (data-type-of-variable-or-parameter variable))
	 (oldest-index? nil)
	 (newest-index? nil)
	 (history-count 0))

    (when (and history? (not (cascaded-ring-buffer-empty? history?)))
      (setq oldest-index?
	    (get-oldest-active-element-index-for-cascaded-ring-buffer
	      history?)
	    newest-index?
	    (get-newest-active-element-index-for-cascaded-ring-buffer
	      history?)
	    history-count
	    (ring-buffer-length (car oldest-index?))))
    
    (write-designation-to-stream designation? gfi-output-frame)
    (gfi-write-char gfi-delimitter gfi-output-frame)
    (reclaim-eval-tree designation?)

    (output-gfi-value history-count 'number gfi-output-frame)
    (gfi-write-char gfi-delimitter gfi-output-frame)

    (let ((current-value (current-value-of-variable-or-parameter variable))
	  (collection-time (time-of-most-recent-value variable))
	  (expiration-time nil))

      (cond
	((frame-of-class-p variable 'parameter)
	 (with-temporary-gensym-float-creation
	     write-gfi-nupec-snapshot-variable-state
	   (output-gfi-value
	     (extract-cached-number-or-value current-value)
	     data-type gfi-output-frame))
	 (gfi-write-char gfi-delimitter gfi-output-frame)
	 ;; write collection time.
	 (output-appropriate-gfi-time-stamp gfi-output-frame collection-time))

	(t
	 (setq expiration-time (expiration-time-of-current-value variable))
	 (cond ((variable-has-received-no-value expiration-time)
		;; Write the default, since there is no most-recent-value.
		(output-appropriate-nupec-gfi-default-value
		  data-type gfi-output-frame)
		(gfi-write-char gfi-delimitter gfi-output-frame)
		;; Write the deault, since there is no collection time.
		(output-appropriate-nupec-gfi-default-time-stamp
		  gfi-output-frame)
		(gfi-write-char gfi-delimitter gfi-output-frame)
		;; Expiration time of NO-VALUE.
		(gfi-write-string #w"no-value" gfi-output-frame))
	       (t
		(with-temporary-gensym-float-creation
		    write-gfi-nupec-snapshot-variable-state
		  (output-gfi-value
		    (extract-cached-number-or-value current-value)
		    data-type gfi-output-frame))
		(gfi-write-char gfi-delimitter gfi-output-frame)

		;; write collection time.
		(output-appropriate-gfi-time-stamp
		  gfi-output-frame collection-time)

		(gfi-write-char gfi-delimitter gfi-output-frame)
		(if (eq expiration-time 'never)
		    (gfi-write-string #w"never" gfi-output-frame)
		    (with-temporary-gensym-float-creation
			write-gfi-nupec-snapshot-variable-state			
		      (output-appropriate-gfi-time-stamp
			gfi-output-frame
			(convert-gensym-time-to-unix-time
			  expiration-time)))))))))

    (gfi-terpri gfi-output-frame)
    (incff (number-of-lines-output-so-far gfi-output-frame))
    
    (when (>f history-count 0)
	(loop do

	  (with-temporary-gensym-float-creation
	      write-gfi-nupec-snapshot-variable-state
	    (gfi-write-char gfi-delimitter gfi-output-frame)
	    (output-appropriate-gfi-time-stamp
	      gfi-output-frame
	      (get-history-g2-time history? (cdr oldest-index?)))

	    (gfi-write-char gfi-delimitter gfi-output-frame)
	    (output-gfi-value
	      (get-history-value-for-cascaded-ring-buffer
		history?
		oldest-index?)
	      data-type
	      gfi-output-frame))

	  (gfi-terpri gfi-output-frame)
	  (incff (number-of-lines-output-so-far gfi-output-frame))
	  
	      until (cascaded-ring-buffer-indices-same-p
		      oldest-index? newest-index?)
	      do
	  (increment-active-element-index-for-cascaded-ring-buffer
	    oldest-index? history?)
	  finally
      (reclaim-element-index-for-cascaded-ring-buffer oldest-index?)
      (reclaim-element-index-for-cascaded-ring-buffer newest-index?)))))




;;; The function `output-appropriate-nupec-gfi-default-value' is used to write
;;; the default value for a variable that has no "most-recent-value".

(defun output-appropriate-nupec-gfi-default-value
       (data-type gfi-output-frame)
  (let ((default-value?
	  (cond
	    ((eq data-type 'integer)
	     0)
	    ((number-subtype-p data-type)
	     0.0)
	    ((eq data-type 'truth-value)
	     falsity)
	    ((eq data-type 'symbol)
	     'g2)
	    ((eq data-type 'text)
	     #w"")
	    (t
	     #+development
	     (warning-message
	       2 "Unknown gfi-default-value in nupec-snapshot code!")
	     nil))))
    (if default-value?
	(let ((output-value
		(twith-output-to-text-string
		  (print-constant default-value? data-type))))
	  (prog1
	    (gfi-write-string output-value gfi-output-frame)
	    (reclaim-text-string output-value)))
	nil)))



;;; The function `output-appropriate-nupec-gfi-default-time-stamp' is used to
;;; write a default time-stamp (collection-time) for a variable that has no
;;; "most-recent-value".  The gfi-output-base-time is used as the
;;; collection-time.  This value was read from the output file header.

(defun output-appropriate-nupec-gfi-default-time-stamp (gfi-output-frame)
  (output-appropriate-gfi-time-stamp
    gfi-output-frame (gfi-output-base-time gfi-output-frame)))






;;;; NUPEC Restart (Read) Snapshot File




;;; The function `gfi-input-nupec-snapshot-values-periodically' reads and
;;; processes the NUPEC snapshot file of a gfi-input-frame until end-of-file is
;;; reached, an error occurs, or the time slice expires (this is optional).
;;;
;;; If override-time-slice-if-necessary-p is set to nil, time-slice-expired-p is
;;; checked to ensure that there is still time to read another variable or
;;; parameter history. If this function needs to return because of time-slice
;;; expiration, it does so after a complete variable or parameter history is
;;; processed.
;;;
;;; If the file has been completely processed, graphs are updated to reflect the
;;; new values.
;;;
;;; Gfi-inputting? of gfi-input-frame must be t when this function is called.
;;; Also the special variable time-slice-expired-p has to be bound when this
;;; function is called.  
;;;
;;; Current history values are replaced and the time is reset if reset-time? is
;;; non-nil.  (This is only useful when in "catch-up" mode!).  Otherwise, the
;;; current history values are updated with the new values and the time is not
;;; changed.
;;;
;;; The function takes an argument which determines if the variables are checked
;;; for gfi-data-service.  (THIS IS CURRENTLY NOT USED!!)
;;;
;;; If the file has been completely read and processed, this function returns t.
;;; Otherwise, it returns nil.
;;;
;;; Upon error or EOF, the gfi-input-frame is closed.

;; TO DO:
;; Stop input when the time stamps are in the future. (i.e.,
;; gfi-input-line-g2-time is greater than the current g2-time!!)

(defun gfi-input-nupec-snapshot-values-periodically
       (gfi-input-frame reset-time? do-not-override-time-slice-p
	no-data-service-required?)

  (let ((*current-computation-frame* gfi-input-frame))

    ;; If time does not need to be reset or time is reset successfully, then
    ;; read the snapshot.  Otherwise, close gfi-input-object and return nil.
    (if (and reset-time?
	     (null
	      (with-temporary-gensym-float-creation
		  gfi-input-nupec-snapshot-values-periodically
		(let* ((base-time (gfi-input-base-time gfi-input-frame))
		       (gensym-base-time
			 (and base-time
			      (convert-unix-time-to-gensym-time
				(managed-float-value base-time)))))
		  (if (and gensym-base-time
			   (fixnump gensym-base-time)
			   (<=f gensym-base-time (clock-get gensym-time)))
		      (progn (change-current-time-in-nupec-catch-up-mode
			       gensym-base-time)
			     t)
		      (progn
			(write-warning-message*
			  2
			  (tformat
			    "NUPEC Snapshot input has been stopped!  Error ~
                             while resetting the G2 time to the NUPEC snapshot ~
                             time.")
			  (cond
			    ((not (<= gensym-base-time (clock-get gensym-time)))
			     (twrite-string
			       "  G2 time cannot be set to a future time."))
			    ((not (fixnump gensym-base-time))
			     (tformat
			       "  The snapshot time is too far into the past.  ~
                                This value cannot be represented internally as ~
                                an integer."))))
			(close-gfi-input-interface gfi-input-frame)
			(setf (gfi-input-file-synchronized? gfi-input-frame)
			      nil)
			nil))))))
	;; if time-reset error (bad time values), return nil.
	nil

	;; else, load the snapshot.
	(loop
          do
	  (when (text-string-p
		  (parse-and-put-gfi-nupec-snapshot-values
		    gfi-input-frame reset-time? no-data-service-required?))
	    ;; If a string is returned an error has occurred and a message has
	    ;;   already been displayed. 
	    ;; Gfi-input-frame is then deactivated and another message is
	    ;;   displayed.
	    (warning-message 2 "NUPEC Snapshot input has been stopped!")
	    (close-gfi-input-interface gfi-input-frame)
	    (setf (gfi-input-file-synchronized? gfi-input-frame) nil)
	    (return nil))

	until
	  (or 
	    ;; Upon EOF or error, read-line closes the gfi-input-frame and
	    ;;   returns nil instead of the input-line.
	    ;; Don't set time-slice expiration flag, since input is complete.
	    (null (read-one-gfi-input-line gfi-input-frame))
	  
	    ;; Check the time-slice if necessary.
	    (and do-not-override-time-slice-p
		 (setq time-slice-expired-p (time-slice-expired-p))))
	
	finally
	  (setf (gfi-input-file-synchronized? gfi-input-frame)
		(not time-slice-expired-p))

	  ;; Reset any graphs if the snapshot-restart has completed.
	  (when (not time-slice-expired-p)
	    (loop for graph being each class-instance of 'graph
		  do
	      (when (active-p graph)
		(funcall-method
		  'deactivate-and-propagate
		  graph
		  nil)
		(funcall-method
		  'activate-if-possible-and-propagate
		  graph))))

	  (return (not time-slice-expired-p))))))




;;; The function `parse-and-put-gfi-nupec-snapshot-values' reads and processes
;;; one variable or parameter's history from an input file.  (This function is
;;; currently called by gfi-input-nupec-snapshot-values-periodically.)  
;;;
;;; This function takes a gfi-input-frame, parses its gfi-input line to obtain
;;; a designation, history-count, most recent value, collection-time, and
;;; (optionally) an expiration time.  The history of the variable or parameter
;;; is then read and added to or replaces the current history (depending on the
;;; value of replace-history? argument).  The current value of the variable or
;;; parameter is set to be the most recent history value.
;;;
;;; The function returns a string if there was an error and a non-string
;;; otherwise.
;;;
;;; If an error does occur, an error message is displayed.  UPON ERROR, THE
;;; GFI-INPUT OBJECT IS NOT DEACTIVATED AND SHOULD BE DEACTIVATED BY THE CALLER
;;; (IF NECESSARY)!
;;;
;;; An argument, no-data-service-required?, indicates if the variables should be
;;; required to have gfi-data-service to receive any "input".   (THIS IS
;;; CURRENTLY IGNORED!!)
;;;
;;; This function does not check for compatibility between NUPEC snapshot file
;;; format, scheduler mode, etc.  This warning should occur when the gfi-input
;;; object is activated.  (Once this activation occurs, the user should not be
;;; able to change the scheduler mode!)

;; This function is similar in design to parse-and-put-event-log-values.

(defun parse-and-put-gfi-nupec-snapshot-values
       (gfi-input-frame replace-history? no-data-service-required?)
  ;; Ignore no-data-service-required? for now! - cpm, 11-22-89
  (declare (ignore no-data-service-required?))
  (let ((designation?
	  (parse-nupec-snapshot-constant-designation gfi-input-frame))
	(start-index-of-value? nil)
	(variable-or-parameter? nil)
	(history-count? nil)
	(current-value? nil)
	(collection-time? nil)
	(expiration-time? nil)
	(error-flag #w"error")
	(current-value-error? nil)
	(result? nil))
    
    (cond
      ((null designation?)
       (warning-message
	 2
	 "Error while reading the snapshot file ~S for the GFI input ~
          object ~NF.  A variable or parameter reference is missing."
	 (gfi-input-file-pathname gfi-input-frame)
	 gfi-input-frame)
       (setq result? error-flag))
      (t
       (setq variable-or-parameter? (place-evaluate designation? nil))
       (cond
	 ((null variable-or-parameter?)
	  (warning-message
	    2
	    "Error while reading the snapshot file ~S for the GFI input ~
             object ~NF.  The variable or parameter ~ND does not exist."
	    (gfi-input-file-pathname gfi-input-frame)
	    gfi-input-frame designation?)
	  (setq result? error-flag))
	 
	 ((not (variable-or-parameter-p variable-or-parameter?))
	  (warning-message
	    2
	    "Error while reading the snapshot file ~S for the GFI input ~
             object ~NF.  The object ~ND is not a variable or parameter."
	    (gfi-input-file-pathname gfi-input-frame)
	    gfi-input-frame designation?)
	  (setq result? error-flag))
	 (t
	  (setq start-index-of-value?
		(skip-to-after-gfi-delimitter-in-string
		  (gfi-input-line gfi-input-frame)
		  (gfi-input-line-current-index gfi-input-frame)
		  (gfi-input-line-length gfi-input-frame)))
	  
	  ;; read the history count
	  (when start-index-of-value?
	    (setf (gfi-input-line-current-index gfi-input-frame)
		  start-index-of-value?)
	    (multiple-value-setq
	      (history-count? start-index-of-value?)
	      (read-number-from-string
		(gfi-input-line gfi-input-frame)
		(gfi-input-line-current-index
		  gfi-input-frame)
		(gfi-input-line-length gfi-input-frame))))
	  (cond
	    ((or (null start-index-of-value?)
		 (null history-count?)
		 (<f history-count? 0))
	     (warning-message 
	       2 
	       "Error while reading the snapshot file ~S for the GFI input ~
                object ~NF.  Could not locate a valid variable or parameter ~
                history count."
	       (gfi-input-file-pathname gfi-input-frame)
	       gfi-input-frame)
	     (setq result? error-flag))
	    (t
	     (when start-index-of-value?
	       (setf (gfi-input-line-current-index gfi-input-frame)
		     start-index-of-value?))
	     (setq current-value?
		   (parse-nupec-snapshot-gfi-variable-or-parameter-value
		     gfi-input-frame designation? variable-or-parameter?))
	     
	     (cond
	       ((null current-value?)
		(setq current-value-error? t))
	       (t
		(setq collection-time?
		      ;; Could be a managed number.
		      (parse-nupec-snapshot-gfi-time-stamp
			gfi-input-frame designation? t))
		(cond ((null collection-time?)
		       (setq current-value-error? t))
		      (t
		       (when (frame-of-class-p variable-or-parameter? 'variable)
			 (setq expiration-time?
			       ;; Could be a managed number.
			       (parse-nupec-snapshot-gfi-time-stamp
				 gfi-input-frame designation? nil))
			 
			 (when (null expiration-time?)
			   (setq current-value-error? t)))))))
	     (cond
	       (current-value-error?
		(setq result? error-flag))
	       ((eql history-count? 0)
		;; No history values to read in.  When replacing the history,
		;; clear any old history values.
		(when replace-history?
		  (clear-histories variable-or-parameter?))
		t)
	       ((and (>f history-count? 0)
		     (null (read-one-gfi-input-line gfi-input-frame)))
		(warning-message 
		  2
		  "Error while reading the snapshot file ~S for the GFI ~
                   input object ~NF.  There should be ~D history values for ~ND."
		  (gfi-input-file-pathname gfi-input-frame)
		  gfi-input-frame history-count? designation?)
		(setq result? error-flag))
	       (t
		(setq result?
		      (if replace-history?
			  (replace-gfi-nupec-snapshot-values-in-history
			    gfi-input-frame designation?
			    variable-or-parameter? history-count?)
			  (add-gfi-nupec-snapshot-values-to-history
			    gfi-input-frame designation?
			    variable-or-parameter? 
			    history-count?)))))
	     (unless (or current-value-error? 
			 (and (text-string-p result?)
			      (string-equalw result? error-flag))
			 ;; no current value
			 (eql expiration-time? *some-time-ago*))
	       ;; Put (or set) most recent value after the history has been  
	       ;; added (or replaced).
		 (cond 
		   (replace-history?
		    (with-temporary-gensym-float-creation
		      parse-and-put-gfi-nupec-snapshot-values
		      (store-managed-number-or-value
			(current-value-of-variable-or-parameter
			  variable-or-parameter?) 
			(extract-cached-number-or-value current-value?)))
		    
		    (setf (time-of-most-recent-value
			    variable-or-parameter?)
			  (copy-managed-number-or-value collection-time?))
		    
		    (if (frame-of-class-p
			  variable-or-parameter? 'variable)
			(setf (expiration-time-of-current-value
				variable-or-parameter?)
			      (if (managed-float-p expiration-time?)
				  ;; Expiration times are stored as gensym-time.
				  (convert-unix-time-to-gensym-time
				    (managed-float-value expiration-time?))
				  expiration-time?))))
		   (t
		    (with-temporary-gensym-float-creation
		      parse-and-put-gfi-nupec-snapshot-values
		      (put-current-value
			variable-or-parameter?
			(extract-cached-number-or-value current-value?)
			(data-type-of-variable-or-parameter-datum
			  (extract-cached-number-or-value current-value?)
			  variable-or-parameter?)

		      ;; expiration time
		      (if (variable-p variable-or-parameter?)
			  (if (eq (validity-interval variable-or-parameter?)
				  'supplied) 
			      (if (frame-of-class-p variable-or-parameter?
						    'quantitative-variable) 
				  expiration-time?
				  ;; logical, symbolic, or text variable.
				  'never)
			      ;; not supplied
			      nil)
			  ;; parameter
			  nil)
		      collection-time?)))))
	     (reclaim-managed-number-or-value collection-time?)
	     (reclaim-managed-number-or-value expiration-time?)
	     (reclaim-managed-number-or-value current-value?)))))))
    result?))




;;; The function `parse-nupec-snapshot-constant-designation' takes as input a
;;; gfi-input-frame.  It reads the constant designation from the string,
;;; starting from gfi-input-line-current-index, stopping at the first
;;; gfi-delimitter, stores the constant designation in the
;;; gfi-current-input-designation slot, and returns the constant designation.

(defun parse-nupec-snapshot-constant-designation (gfi-input-frame)
  (let ((length (gfi-input-line-length gfi-input-frame))
	(start-index
	  (gfi-input-line-current-index gfi-input-frame))
	(line (gfi-input-line gfi-input-frame))
	end-index)
    (when (and start-index (<f start-index length))
      (setq end-index (skip-to-after-gfi-delimitter-in-string
			line start-index length))
      (if (not end-index)			       ;want to point to position
	  (setq end-index length)		       ;  just after the last character
	  (decff end-index))			       ;  of the designation.
      (setf (gfi-input-line-current-index gfi-input-frame) end-index)
      (let ((substring
	      (text-string-substring line start-index end-index)))
	(read-gfi-designation-from-string
	  gfi-input-frame substring)))))



;; Abstract parse-delimitter-then-designation to be
;; parse-constant-designation with an argument that specifies whether to skip
;; past the first designation!!  cpm, 1-11-90.

;; Fixed.  CPM: please get rid of parse-nupec-snapshot-constant-designation,
;; which does not check for illegal text strings.  -pto 28feb90



;;; The function `parse-nupec-snapshot-gfi-time-stamp' reads a time-stamp from
;;; the gfi-input-line string, starting from gfi-input-line-current-index,
;;; skipping a gfi-delimitter, and stopping at the next gfi-delimitter.  If a
;;; numeric time-stamp is read, it is returned.  Certain symbol time stamps may
;;; be converted to numeric time stamps before being returned.  If an error
;;; occurs (e.g., a bignum time-stamp) a warning message is displayed and nil
;;; is returned.

;; Note that this function calls read-and-encode-nupec-snapshot-time-stamp-or-
;; symbol, which can return a g2-time (a managed float), *some-time-ago* (a
;; gensym-time fixnum), the symbol NEVER, or NIL.  If a managed-float is return
;; this value should be owned/reclaimed by the caller.  - cpm, 7/12/94

(defun parse-nupec-snapshot-gfi-time-stamp
       (gfi-input-frame designation time-stamp-only?)
  (let ((current-index?
	  (skip-to-after-gfi-delimitter-in-string
	    (gfi-input-line gfi-input-frame)
	    (gfi-input-line-current-index gfi-input-frame)
	    (gfi-input-line-length gfi-input-frame))))
    (cond ((null current-index?)
	   (warning-message
	     2
	     "Missing a time-stamp for ~ND while reading from the ~
              file ~S for the GFI input object ~NF."
	     designation
	     (gfi-input-file-pathname gfi-input-frame)
	     gfi-input-frame)
	   nil)
	  (t
	   (setf (gfi-input-line-current-index gfi-input-frame) current-index?)
	   (let ((collection-time? 
		   (read-and-encode-nupec-snapshot-time-stamp-or-symbol
		     gfi-input-frame time-stamp-only?)))
	     (or collection-time?
		 (progn
		   (warning-message
		     2
		     "Incorrect time-stamp for ~ND while reading from the ~
                      file ~S for the GFI input object ~NF."
		     designation
		     (gfi-input-file-pathname gfi-input-frame)
		     gfi-input-frame)
		   nil)))))))




;;; The function `read-and-encode-nupec-snapshot-time-stamp-or-symbol'  reads a
;;; time-stamp from the gfi-input-line string, starting from
;;; gfi-input-line-current-index, and stopping at the next gfi-delimitter.  If a
;;; numeric time-stamp is read, it is returned.  Certain symbol time stamps may
;;; be converted to numeric time stamps before being returned.  (Never is
;;; returned as 'never; no-value is returned as *some-time-ago*.)  The
;;; gfi-input-line current-index is updated.  If an error occurs, nil is
;;; returned.  An encoded-bignum-time is an error.
;;;
;;; Relative time stamps are converted to absolute times using
;;; gfi-input-base-time.

;;; Note that as of version 4.0, this function can return a managed-float (a
;;; g2-time) that is owned by the caller, a fixnum (*some-time-ago*
;;; gensym-time), the symbol NEVER, or NIL.

;; We should eventually come up with a g2-time (float) representation of
;; *some-time-ago* and 'never, something like "big-bang" (start of the universe)
;; and "big-crash".  These numbers would be billions of years (in seconds) into
;; the past and future, respectively - cpm, 7/12/94

(defun read-and-encode-nupec-snapshot-time-stamp-or-symbol
       (gfi-input-frame time-stamp-only?)
  (if (eq (gfi-input-time-stamp-format gfi-input-frame) 'explicit)
      (multiple-value-bind (seconds? minutes hours day month year
			    end-index-of-time-stamp)
	  ;; Note that as of version 4.0, seconds? can be a managed-number.
	  (read-time-stamp-from-string
	    (gfi-input-line gfi-input-frame)
	    (gfi-input-line-current-index gfi-input-frame)
	    (gfi-input-line-length gfi-input-frame))
	(if seconds?
	    (progn
	      (setf (gfi-input-line-current-index gfi-input-frame)
		    end-index-of-time-stamp)
	      (with-temporary-gensym-float-creation
		  read-and-encode-nupec-snapshot-time-stamp-or-symbol
		(let* ((second-fraction-float?
			 (if (managed-float-p seconds?)
			     (-e (managed-float-value seconds?)
				 (ffloore-first
				   (managed-float-value seconds?)))))
		       (subsecond-time?
			 (if (and second-fraction-float?
				  (/=e second-fraction-float? 0.0))
			     second-fraction-float?))
		       (seconds-fixnum?
			 (when seconds?
			   (if (managed-float-p seconds?)
			       (floore-first (managed-float-value seconds?))
			       seconds?)))
		       (encoded-time
			 (gensym-encode-unix-time-as-managed-float
			   seconds-fixnum? minutes hours day month year)))
		  (when subsecond-time?
		    (store-managed-number
		      encoded-time
		      (+e subsecond-time? (managed-float-value encoded-time))))
		  (reclaim-managed-number seconds?)
		  ;; return a managed-float
		  encoded-time)))
	    (if (null time-stamp-only?)
		;; symbol value: e.g., never, no-value.
		(multiple-value-bind (symbol-value? end-index-of-symbol?)
		    (read-symbol-from-text-string
		      (gfi-input-line gfi-input-frame)
		      (gfi-input-line-current-index gfi-input-frame))
		  (if symbol-value?
		      (progn
			(setf (gfi-input-line-current-index gfi-input-frame)
			      end-index-of-symbol?)
			(case symbol-value?
			  (no-value *some-time-ago*)
			  (never 'never)
			  (t nil)))
		      nil))
		nil)))

      ;; else - relative time stamp.
      (multiple-value-bind (relative-time? end-index-of-relative-time?)
	  (read-number-from-string
	    (gfi-input-line gfi-input-frame)
	    (gfi-input-line-current-index gfi-input-frame)
	    (gfi-input-line-length gfi-input-frame))
	(if relative-time?
	    (progn
	      (setf (gfi-input-line-current-index gfi-input-frame)
		    end-index-of-relative-time?)
	      (with-temporary-gensym-float-creation
		  read-and-encode-nupec-snapshot-time-stamp-or-symbol
		(store-managed-number
		  relative-time?
		  (if (fixnump relative-time?)
		      (+e (coerce-to-gensym-float relative-time?)
			  (managed-float-value
			    (gfi-input-base-time gfi-input-frame)))
		      (+e (managed-float-value relative-time?)
			  (managed-float-value
			    (gfi-input-base-time gfi-input-frame)))))
		;; return value
		relative-time?))
	    (if (null time-stamp-only?)
		;; symbol value: e.g., never, no-value.
		(multiple-value-bind (symbol-value? end-index-of-symbol?)
		    (read-symbol-from-text-string
		      (gfi-input-line gfi-input-frame)
		      (gfi-input-line-current-index gfi-input-frame))
		  (if (and symbol-value?
			   (legal-gensym-string-p (symbol-name symbol-value?)))
		      (progn
			(setf (gfi-input-line-current-index gfi-input-frame)
			      end-index-of-symbol?)
			(case symbol-value?
			  (no-value *some-time-ago*)
			  (never 'never)
			  (t nil)))
		      nil))
		nil)))))




;;; The function `parse-nupec-snapshot-gfi-variable-or-parameter-value' reads a
;;; variable or parameter value from the gfi-input-line string, starting from
;;; gfi-input-line-current-index, skipping a gfi-delimitter, and stopping at the
;;; next gfi-delimitter.  If a (possibly managed) value is read that is valid
;;; for that variable or parameter, it is returned.  Otherwise, a warning
;;; message is displayed and nil is returned. 

(defun parse-nupec-snapshot-gfi-variable-or-parameter-value
       (gfi-input-frame designation variable-or-parameter)
  (let ((current-index?
	  (skip-to-after-gfi-delimitter-in-string
	    (gfi-input-line gfi-input-frame)
	    (gfi-input-line-current-index gfi-input-frame)
	    (gfi-input-line-length gfi-input-frame))))
    (cond ((null current-index?)
	   (warning-message
	     2
	     "Error while reading the snapshot file ~S for the GFI ~
              input object ~NF.  A value is missing for ~ND."
	     (gfi-input-file-pathname gfi-input-frame)
	     gfi-input-frame designation)
	   nil)
	  (t
	   (setf (gfi-input-line-current-index gfi-input-frame) current-index?)
	   (let ((managed-value?
		   (read-gfi-nupec-snapshot-value-from-input-line
		     variable-or-parameter
		     gfi-input-frame)))
	     (or managed-value?
		 (progn 
		   (warning-message
		     2
		     "Error while reading the snapshot file ~S for the GFI ~
                      input object ~NF.  Incorrect value for ~ND."
		     (gfi-input-file-pathname gfi-input-frame)
		     gfi-input-frame designation)
		   nil)))))))





;;; The function `read-gfi-nupec-snapshot-value-from-input-line' reads a
;;; variable or parameter value from the gfi-input-line string, starting from
;;; gfi-input-line-current-index and stopping at the next gfi-delimitter.  If a
;;; (possibly managed) value is read that is valid for that variable or
;;; parameter, it is returned.  (The gfi-input-line current-index is updated.)
;;; Otherwise, nil is returned. 

(defun read-gfi-nupec-snapshot-value-from-input-line
       (variable-or-parameter gfi-input-frame)

  (multiple-value-bind (managed-value end-index)
      (let ((data-type (data-type-of-variable-or-parameter
			 variable-or-parameter))
	    (string (gfi-input-line gfi-input-frame))
	    (current-index (gfi-input-line-current-index gfi-input-frame))
	    (max-index (gfi-input-line-length gfi-input-frame)))
	(cond
	  ((number-subtype-p data-type)
	   (read-number-from-string string current-index max-index))
	  ((eq data-type 'truth-value)
	   (read-truth-value-from-string string current-index max-index))
	  ((eq data-type 'symbol)
	   (multiple-value-bind (symbol symbol-end-index)
	       (read-symbol-from-text-string string current-index)
	     (cond
	       ((and symbol (legal-gensym-string-p (symbol-name symbol)))
		(values symbol symbol-end-index))
	       (t (values nil current-index nil)))))
	  ((eq data-type 'text)
	   (multiple-value-bind (text text-end-index error-message?)
	       (read-text-string-with-or-without-quotes-from-string
		 string current-index max-index)
	     (cond
	       ((and string
		     (null error-message?))
		(values text text-end-index))
	       (t (values nil current-index nil)))))
	  (t
	   (values nil current-index nil))))
    (when managed-value
      (setf (gfi-input-line-current-index gfi-input-frame) end-index))
    managed-value))




;;; The function `add-gfi-nupec-snapshot-values-to-history' reads and processes
;;; one variable or parameter's history from an input file.  (This function is
;;; currently called by parse-and-put-gfi-nupec-snapshot-values.)  This function
;;; adds values to the history (i.e., the history is modified, not replaced).
;;;
;;; This function takes a gfi-input-frame and assumes the gfi-input-line has
;;; been parsed to obtain a designation, history-count, most recent value,
;;; collection-time, and (possibly) an expiration time.  The history of the
;;; variable or parameter is then read and added to the current history.
;;;
;;; History-count must be > 0.
;;;
;;; The function returns a string if there was an error and a non-string
;;; otherwise.
;;;
;;; Time stamps that are in the future (i.e., ahead of gensym-time) produce an
;;; error.
;;;
;;; If an error occurs a message is displayed and a string is returned.
;;; UPON ERROR, THE GFI-INPUT OBJECT IS NOT DEACTIVATED AND SHOULD BE
;;; DEACTIVATED BY THE CALLER (IF NECESSARY)!
;;;
;;; This function does not check for compatibility between NUPEC snapshot file
;;; format, scheduler mode, etc.  Also, this function does not test the
;;; variable-or-parameter. 

(defun add-gfi-nupec-snapshot-values-to-history
       (gfi-input-frame designation variable-or-parameter history-length)
  (loop with history-count = 0
	with collection-time? = nil
	with value? = nil
	with error-flag = #w"error"
	do 
    (setq collection-time?
	  (parse-nupec-snapshot-gfi-time-stamp gfi-input-frame designation t))
    (cond ((null collection-time?)
	   ;; error message was already displayed.
	   (return error-flag))
	  ((or (and (fixnump collection-time?)
		    (>f collection-time? (clock-get gensym-time)))
	       (and (managed-float-p collection-time?)
		    (>e (managed-float-value collection-time?)
			(managed-float-value (clock-get current-g2-time)))))
	   (warning-message
	     2
	     "Error while reading from the Snapshot file ~S for the ~
              GFI input object ~NF.  Future time-stamp for ~ND."
	     (gfi-input-file-pathname gfi-input-frame)
	     gfi-input-frame
	     designation)
	   (reclaim-managed-number-or-value collection-time?)
	   (return error-flag))
	  (t
	   (setq value?
		 (parse-nupec-snapshot-gfi-variable-or-parameter-value
		   gfi-input-frame designation variable-or-parameter))
	   (cond (value?
		  (with-temporary-gensym-float-creation
		    add-gfi-nupec-snapshot-values-to-history
		    (put-current-value
		      variable-or-parameter
		      (extract-cached-number-or-value value?)
		      (data-type-of-variable-or-parameter-datum
			(extract-cached-number-or-value value?)
			  variable-or-parameter)
		      ;; expiration time
		      (if (variable-p variable-or-parameter)
			  (if (eq (validity-interval variable-or-parameter)
				  'supplied) 
			      (if (frame-of-class-p variable-or-parameter
						    'quantitative-variable) 
				  collection-time?
				  ;; logical, symbolic, or text variable.
				  'never)
			      ;; not supplied
			      nil)
			  ;; parameter
			  nil)
		      collection-time?)
		    (reclaim-managed-number-or-value collection-time?)
		    (reclaim-managed-number-or-value value?)))
		 (t
		  (reclaim-managed-number-or-value collection-time?)
		  (return error-flag)))))
    (incff history-count)
	while (and (<f history-count history-length)
		   (read-one-gfi-input-line gfi-input-frame))))




;;; The function `replace-gfi-nupec-snapshot-values-in-history' reads and
;;; processes one variable or parameter's history from an input file.  (This
;;; function is currently called by parse-and-put-gfi-nupec-snapshot-values.)
;;; This function replaces the history (i.e., the history is not added to).
;;;
;;; This function takes a gfi-input-frame and assumes the gfi-input-line has
;;; been parsed to obtain a designation, history-count, most recent value,
;;; collection-time, and (possibly) an expiration time.  The history of the
;;; variable or parameter is then read and replaces the current history.
;;;
;;; History-count must be > 0.
;;;
;;; The function returns a string if there was an error and a non-string
;;; otherwise.
;;;
;;; Time stamps that are in the future (i.e., ahead of gensym-time) produce an
;;; error.  (The current variable or parameter history is not replaced!)
;;;
;;; If an error occurs a message is displayed, a string is returned, and the
;;; current history is not replaced!
;;;
;;; UPON ERROR, THE GFI-INPUT OBJECT IS NOT DEACTIVATED AND SHOULD BE
;;; DEACTIVATED BY THE CALLER (IF NECESSARY)!
;;;
;;; This function does not check for compatibility between NUPEC snapshot file
;;; format, scheduler mode, etc.  Also, this function does not test the
;;; variable-or-parameter. 

(defun replace-gfi-nupec-snapshot-values-in-history
       (gfi-input-frame designation variable-or-parameter history-length)

  (let* ((history? nil)
	 (history-spec?
	   (when (and variable-or-parameter (variable-p variable-or-parameter))
	     (variable-or-parameter-history-specification?
	       variable-or-parameter)))
	 (error-flag #w"error")
	 (error? nil))
    
    (cond ((<=f history-length 0)
	   error-flag)
	  (t
	   (loop with history = (make-or-reformat-cascaded-ring-buffer
				  nil
				  (second history-spec?)
				  (third history-spec?)
				  (fourth history-spec?))
		 with history-count = 0
		 with ring-buffer = (get-or-make-smallest-history-ring-buffer)
		 
		 initially
		   (setf (cascaded-ring-buffers history)
			 (history-list ring-buffer))

		 ;; Set the base-time for the new history.  The old base-time is
		 ;; not used because the history is being replaced.  Can use the
		 ;; current-g2-time as the base because we are not storing
		 ;; simulated-histories.
		   (with-temporary-gensym-float-creation
		       replace-gfi-nupec-snapshot-values-in-history
		     (setf (cascaded-ring-buffer-base-time? history)
			   (allocate-managed-float
			     (ffloore-first
			       (managed-float-value (clock-get current-g2-time))))))

		 for time-stamp? =
  		   ;; Could be a managed number.
		   (parse-nupec-snapshot-gfi-time-stamp
		     gfi-input-frame designation t)

		 for value? = 
		     (and time-stamp?
			  (parse-nupec-snapshot-gfi-variable-or-parameter-value
			    gfi-input-frame designation variable-or-parameter))
		 
		 do

	     (with-temporary-gensym-float-creation
		 replace-gfi-nupec-snapshot-values-in-history
	       (cond ((or (null time-stamp?) (null value?))
		      ;; an error message has already been displayed.
		      (setq error? t)
		      (setq history? history)
		      (when time-stamp?
			(reclaim-managed-number-or-value time-stamp?))
		      (return))
		     ((or (and (fixnump time-stamp?)
			       (>f time-stamp? (clock-get gensym-time)))
			  (and (managed-float-p time-stamp?)
			       (>e (managed-float-value time-stamp?)
				   (managed-float-value (clock-get current-g2-time)))))
		      (warning-message
			  2
			  "Error while reading from the Snapshot file ~S for ~
                          the GFI input object ~NF.  Future time-stamp for ~ND."
			(gfi-input-file-pathname gfi-input-frame)
			gfi-input-frame
			designation)
		      (setq error? t)
		      (setq history? history)
		      (reclaim-managed-number-or-value time-stamp?)
		      (return))
		     (t
		      (store-new-element-in-history-ring-buffer
			ring-buffer 'expand-history-ring-buffer
			(extract-cached-number-or-value value?)
			(if (fixnump time-stamp?)
			    (-f time-stamp? (clock-get gensym-time-at-start))
			    ;; Version 4.0 history format stores an offset from
			    ;; the base-time.
			    (-e (managed-float-value time-stamp?)
				(managed-float-value
				  (cascaded-ring-buffer-base-time? history)))))
		      (reclaim-managed-number-or-value time-stamp?)
		      (reclaim-managed-number-or-value value?))))

	     (incff history-count)
		 while (and (<f history-count history-length)
			    (read-one-gfi-input-line gfi-input-frame))
		 finally
		   (setq history? history))

	   (cond (error?
		  (reclaim-history-buffer history?)
		  error-flag)
		 (t
		  (let ((old-history? (variable-or-parameter-stored-histories?
					variable-or-parameter)))
		    (when old-history?
		      (reclaim-history-buffer old-history?))
		    (setf (variable-or-parameter-stored-histories?
			    variable-or-parameter) history?))
		  variable-or-parameter))))))



;;;; G2 Stream Input and Output Operations for GFI



;;; These abstractions keep GFI working as it did before if no text conversion
;;; style is specified.  If one is specified, it is obeyed with the caveat that
;;; stateful encodings (e.g., ISO 2022) cannot survive more than one line.  Otherwise,
;;; GFI has always (at least since G2 4.0) used strict UTF-G (at that time, "Gensym
;;; character set") encoding, not "ASCII as much as possible".  E.g., @'s are ~@,
;;; etc.

(defun-simple gfi-write-string (string gfi-output-interface)
  (export-and-emit-text-string
    string
    (come-up-with-text-conversion-style-structure
      (get-slot-value gfi-output-interface 'text-conversion-style)
      nil)
    (gfi-output-file-stream gfi-output-interface)))
	    

;;; `GFI-write-char' ... Character can be either a Common Lisp character
;;; or a Gensym wide character.  In new code, only wide characters should
;;; be used.

(defun-simple gfi-write-char (character gfi-output-interface)
  (export-and-emit-character
    (coerce-to-wide-character character)
    (come-up-with-text-conversion-style-structure
      (get-slot-value gfi-output-interface 'text-conversion-style)
      nil)
    (gfi-output-file-stream gfi-output-interface)))

(defun-simple gfi-terpri (gfi-output-interface)
  (g2-stream-write-line-terminator-using-text-conversion-style
    (come-up-with-text-conversion-style-structure
      (get-slot-value gfi-output-interface 'text-conversion-style)
      nil)
    (gfi-output-file-stream gfi-output-interface)))




;;; Read-available-char-idiom-for-gfi ... This uses local variable buffer, which
;;; must be a simple gensym string.  This also assumes appropriate local
;;; bindings for position and n-octets-per-character.  This returns the next
;;; wide character read (which might consume one or two 8-bit bytes), and incf's
;;; position by 1 or 2 as n-octets-per-character = 1 or 2.

(defmacro read-available-char-idiom-for-gfi ()
  `(let* ((char (schar buffer position))
	  (char-2 #\null))
     (declare (type character char char-2))
     (incff position)
     (cond
       ((=f n-octets-per-character 2)
	(setq char-2 (schar buffer position))
	(incff position)
	(if 2-octet-byte-swapped-p
	    (octets-to-wide-character
	      (ascii-char-code char-2) (ascii-char-code char))
	    (octets-to-wide-character
	      (ascii-char-code char) (ascii-char-code char-2))))
       (t
	(character-to-wide-character char)))))

(defmacro read-char-idiom-for-gfi ()
  `(if (<f position (-f available-characters octets-per-char-minus-one))
       (read-available-char-idiom-for-gfi)
       (let* ((count-of-characters-read?
		(g2-stream-read-into-buffer
		  buffer #.size-of-g2-stream-frame-input-buffer
		  g2-input-stream)))
	 (setf available-characters (or count-of-characters-read? 0))
	 (incff offset position)
	 (setq position 0)
	 (when (>f available-characters octets-per-char-minus-one)
	   (read-available-char-idiom-for-gfi)))))



;;; ... This uses these slots of a GFI-input-interface object:
;;;
;;;    gfi-input-file-buffer
;;;    gfi-input-file-buffer-available-characters
;;;    gfi-input-file-buffer-position
;;;    gfi-input-file-buffer-offset

(defun-simple gfi-read-line (gfi-input-interface)
  (let* ((g2-input-stream (gfi-input-file-stream gfi-input-interface))
	 (buffer (gfi-input-file-buffer gfi-input-interface))
	 (offset
	   (gfi-input-file-buffer-offset gfi-input-interface))
	 (available-characters
	   (gfi-input-file-buffer-available-characters gfi-input-interface))
	 (position
	   (gfi-input-file-buffer-position gfi-input-interface))
	 (initial-file-position (+f offset position))
	 (text-conversion-style-structure
	   (come-up-with-text-conversion-style-structure
	     (get-slot-value gfi-input-interface 'text-conversion-style)
	     nil))
	 (n-octets-per-character
	   (n-octets-per-character text-conversion-style-structure))
	 (octets-per-char-minus-one (if (=f n-octets-per-character 2) 1 0))
	 (2-octet-byte-swapped-p
	   (2-octet-byte-swapped-p text-conversion-style-structure))
	 (text-line
	   (twith-output-to-text-string
	     (loop for character? = (read-char-idiom-for-gfi)
		   do
	       (cond
		 ;; EOF, LF, ULS, UPS
		 ((or (null character?)
		      (char=w character? #.%Linefeed)
		      (char=w character? #.%line-separator)
		      (char=w character? #.%paragraph-separator))
		  (loop-finish))
		 ;; CR, CRLF
		 ((char=w character? #.%Return)
		  (let ((peeked-character? (read-char-idiom-for-gfi)))
		    (unless (and peeked-character?
				 (char=w peeked-character? #.%Linefeed))
		      (decff position n-octets-per-character))
		    (loop-finish)))
		 (t (twrite-char character?))))
	     (setf (gfi-input-file-buffer-position gfi-input-interface) position)
	     (setf (gfi-input-file-buffer-available-characters gfi-input-interface)
		   available-characters)
	     (setf (gfi-input-file-buffer-offset gfi-input-interface)
		   offset))))
    (declare (type fixnum
		   offset available-characters position initial-file-position
		   n-octets-per-character octets-per-char-minus-one))
    (cond
      ((>f (+f offset position) initial-file-position)
       text-line)
      (t
       (reclaim-text-string text-line)
       nil))))


