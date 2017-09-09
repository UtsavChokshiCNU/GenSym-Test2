;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GFI-STUBS:  Stubs for GFI

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Jim Allard, Chris Morel, and Ong, Peng Tsin






;;;; GFI Input and Output Classes and Grammar Rules






;;;; Common Grammar and Slot Info for GFI Output and Input Interfaces




;;; Grammar used for both GFI Output and Input Interfaces

(add-grammar-rules
  '((gfi-yes-or-no? yes-or-no)  ;; had been yes-or-no?. see Tables

    (gfi-time-stamp-format ('explicit 'time-stamp) explicit)
    (gfi-time-stamp-format ('relative 'time-stamp) relative)

    (gfi-file-format ('event 'log) event-log)
    (gfi-file-format 'spreadsheet)
    
;    #+NUPEC
;    (gfi-file-format ('NUPEC 'snapshot) nupec-snapshot)
;    #+NUPEC
;    (gfi-file-format ('NUPEC 'snapshot 'with 'restart 'time)
;		     nupec-snapshot-with-restart-time)

    (gfi-file-pathname 'none)
    ;; The following was e-designation before G2 4.0.  - cpm, 4/18/95
    (gfi-file-pathname constant-designation)
    (gfi-file-pathname whole-string)))


;; Edits to the gfi-yes-or-no? category is done with a "yes/no" menu choice.
(pushnew 'gfi-yes-or-no? grammar-categories-getting-yes-no-feature)


;;; Slot value compilers used for both GFI Output and Input Interfaces

(def-slot-value-compiler gfi-file-format (parse-result)
  (if (eq parse-result 'none)
      nil
      parse-result))


     
	     

(def-slot-value-compiler gfi-file-pathname (parse-result)
  (if (eq parse-result 'none)
      nil
      parse-result))



;;; Slot value writers used for both GFI Output and Input Interfaces

(def-slot-value-writer gfi-yes-or-no? (value?)
  (twrite-string (if value? "yes" "no")))

(def-substitution-macro gfi-time-stamp-format-slot-value-writer-macro (value)
  (cond ((eq value 'relative) (twrite-string "relative time-stamp"))
	((eq value 'explicit) (twrite-string "explicit time-stamp"))
	(t (warning-message
	     2
	     "The slot value writer for gfi-time-stamp-format ~
              received an illegal value: ~a."
	     value))))



(def-slot-value-writer gfi-time-stamp-format (value)
  (gfi-time-stamp-format-slot-value-writer-macro value))

(def-substitution-macro gfi-file-format-slot-value-writer-macro (value)
  (cond ((eq value 'event-log) (twrite-string "event log"))
	((eq value 'spreadsheet) (twrite-string "spreadsheet"))
	((eq value 'nupec-snapshot) (twrite-string "NUPEC snapshot"))
	((eq value 'nupec-snapshot-with-restart-time)
	 (twrite-string "NUPEC snapshot with restart time"))
	(t (warning-message
	     2
	     "The slot value writer for gfi-file-format ~
              received an illegal value: ~a."
	     value))))

(def-slot-value-writer gfi-file-format (format)
  (gfi-file-format-slot-value-writer-macro format))

(def-slot-value-writer gfi-file-pathname (file-pathname)
  (cond ((text-string-p file-pathname) (tprin file-pathname t))
	((designation-p file-pathname) (print-designation file-pathname))
	((null file-pathname) (twrite 'none))
	(t
	 (warning-message
	     2
	     "The slot value writer for gfi-file-pathname ~
              received an illegal value ~a."
	   file-pathname))))






;;;; GFI Output and Input Interface Frame Note Writers




;;; GFI-output-interface frame notes

(def-frame-note-writer no-gfi-output-values (particulars)
  (declare (ignore particulars))
  (twrite-string "no GFI output values are specified"))

(def-frame-note-writer no-gfi-output-update-frequency (particulars)
  (declare (ignore particulars))
  (twrite-string "no GFI output update frequency is specified"))

(def-frame-note-writer no-gfi-output-file-pathname (particulars)
  (declare (ignore particulars))
  (twrite-string "no GFI output file pathname is specified"))



;;; GFI-input-interface frame notes

(def-frame-note-writer no-gfi-input-file-pathname (particulars)
  (declare (ignore particulars))
  (twrite-string "no GFI input file pathname is specified"))

(def-frame-note-writer no-gfi-input-variables-update-mode (particulars)
  (declare (ignore particulars))
  (twrite-string "no GFI input variables update mode is specified"))






;;;; GFI-OUTPUT-INTERFACE CLASS




;;; GFI Output Interface Slots:
;;;
;;;   maximum-number-of-output-lines
;;;      stored as:  nil | <positive-integer>
;;;      printed as: none | <positive-integer>
;;;
;;;   gfi-output-values
;;;      stored as:  (<list-of-designations?> . text) | NIL
;;;      printed as: (eg.  foo, bar, the fiz of frap-1)
;;;
;;;   gfi-output-file-update-frequency
;;;      stored as:  nil | when-received-value
;;;                      | (write-interval (<number> . seconds))
;;;			 | output-one-shot-when-activated
;;;			 | output-one-shot-when-activated-without-interruption
;;;      printed as: ""
;;;                  | write to file when variables receive new values
;;;                  | write to file every <positive-integer> seconds
;;;                  | write to file when activated
;;;                  | write to file when activated, without interruption
;;;
;;;   gfi-output-priority	;;; DO THIS LATER IF DESIRED
;;;      stored as:  <priority>
;;;      printed as: <priority>
;;;
;;;   gfi-output-time-stamp-format
;;;      stored as:  explicit | relative
;;;      printed as: explicit time-stamp | relative time-stamp
;;;
;;;   gfi-output-file-format
;;;      stored as:  event-log | spreadsheet
;;;      printed as: event log | spreadsheet
;;;
;;;   gfi-output-file-pathname
;;;      stored as:  nil| <string>
;;;      printed as: <null> | <string>
;;;   gfi-output-when-active:
;;;      stored as:  t|nil
;;;      printed as: yes/no
;;       NOTE: The above slot is new to version 5.0 and controls whether the
;;       object is started upon activation.  -cpm, 7/12/96

;;; NOTE: non foundation-classes, if it's also user-instantiable, must NOT contain any
;;; vector-slot, because the computation of `frame-vector-length' is only based on the
;;; `foundation-class' of current user-defined class. (see `add-class-to-environment').
;;; This broke March 2015 release. -- Chun Tian (binghe), Apr 2015.

(def-class (gfi-output-interface
	     object
	     (foundation-class object)
	     (disjoint-from gsi-interface g2-to-g2-data-interface
			    gfi-input-interface)
	     define-predicate)
  (file-system
    nil					; set by initialize method
    (lookup-slot) (type read-only-attribute) (not-user-editable) (do-not-save)
    (system) no-accessor)
  (file-status
    ready-to-open
    (lookup-slot) (type read-only-attribute) (not-user-editable) (do-not-save)
    (system) no-accessor)
  (maximum-number-of-output-lines
    nil (lookup-slot) (type positive-integer?) (system)
    user-overridable (save))
  (gfi-output-values			; See note 1, below.
    nil (lookup-slot) (type gfi-output-values text) (system) (save))
  (gfi-output-file-update-frequency
    nil (lookup-slot) (type gfi-output-file-update-frequency)
    user-overridable (system) (save))
  (gfi-output-time-stamp-format
    relative (lookup-slot)
    (type gfi-time-stamp-format) (system)  user-overridable (save))
  (gfi-output-file-format
    event-log (lookup-slot) (type gfi-file-format) (system)
    user-overridable (save))
  (renamed-gfi-output-file-pathname?
    nil (lookup-slot) (type gfi-file-pathname) user-overridable
    (system) (save))
  (gfi-output-file-pathname
    nil (lookup-slot) (type gfi-file-pathname) (system)
    user-overridable (save))
  (gfi-output-when-active
    t (lookup-slot) (type gfi-yes-or-no?) (system)
    user-overridable (save))
  (gfi-outputting?
    nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
  (gfi-output-file-stream
    nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
   (gfi-output-base-time
     nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
   (gfi-output-scheduled-task
     nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
   (gfi-output-scheduled-task-start-time
     nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
   (number-of-lines-output-so-far
     nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
   (new-gfi-output-values-this-cycle?
     nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
   (gfi-list-of-new-spreadsheet-output-values
     nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
   (gfi-queue-of-new-output-values
     nil (lookup-slot) (do-not-put-in-attribute-tables)
     (do-not-save))
   (number-of-periodic-specified-designation-handled
     nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
   (gfi-output-without-interruption?
     nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
   (gfi-output-pathname-string-of-stream?
     nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
   (gfi-output-spreadsheet-field-index-hash
     nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
   (gfi-output-not-unique-designation-p-results
     nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
   (gfi-output-unique-designations
     nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
  (text-conversion-style    ; - defaults to the default-text-conversion-style of language-parameters
			    ; - changeable up until anything read/written
			    ; - note: overloaded name -- use no-accessor, and must be lookup 
    nil			    ;   slot everywhere
    (type text-conversion-style-name?)
    no-accessor
    lookup-slot system do-not-save))

;; NOTE #1 (see above): I don't think that the gfi-output-values slot needs to
;; be a text slot.  The slot could instead contain just the list of designations
;; (e-designations), which could be written from a slot-value-writer, as needed.
;; If this change is made, we would need to fixup the gfi-output-values in any
;; existing KB's.  - cpm, 4/19/95



(define-slot-alias renamed-gfi-output-file-pathname renamed-gfi-output-file-pathname?)




;; Implementation note:  try to keep the slot gfi-list-of-output-value-queues at
;; the end of the def-capability; this way, it will be the last slot displayed
;; by describe-frame, and the self-referring cons cells it might contain will
;; not cause the lisp printer to go into an infinite loop.  -pto 06oct88



;;; Grammar for GFI-OUTPUT-INTERFACE slots

(add-grammar-rules-for-list
  'gfi-output-value-list 'e-designation '\, nil 'none nil)

(add-grammar-rules
  '((gfi-output-values gfi-output-value-list)

    (gfi-output-file-update-frequency 'none)
    (gfi-output-file-update-frequency
      ('write 'to 'file 'every interval) (write-interval 5))
    (gfi-output-file-update-frequency
      ('write 'to 'file 'when 'variables 'receive 'values) when-received-value)
    (gfi-output-file-update-frequency
      ('write 'to 'file 'when 'activated) output-one-shot-when-activated)
    (gfi-output-file-update-frequency
      ('write 'to 'file 'when 'activated '\, 'without 'interruption)
      output-one-shot-when-activated-without-interruption)))

;; IMPORTANT note for users of the GFI-OUTPUT-VALUE-LIST category: Note that the
;; resulting parse of this category does not have a simplify-associative-
;; operation automatically done on it.  This needs to be done in the
;; corresponding slot-value-compiler.  For an example see gfi-output-values
;; slot-value-compiler.  This is necessary to fix a problem with excessive
;; consing while attempting the simplify-associative-operation transformation.
;; - cpm, 10/19/94




;;; Slot value compilers for GFI-OUTPUT-INTERFACE slots

(def-simplifying-slot-value-compiler gfi-output-values (parse-result)
  (cond ((null parse-result) nil)
	((eq parse-result 'none) nil)
	((symbolp parse-result) (phrase-cons parse-result nil))
	((eq (car parse-result) '\,) (cdr parse-result))
	(t (phrase-cons parse-result nil))))

(def-slot-value-compiler gfi-output-file-update-frequency (parse-result)
  (cond ((null parse-result) nil)
	((eq parse-result 'none) nil)
	(t parse-result)))





;;; Slot value writers for GFI-OUTPUT-INTERFACE slots


(def-slot-value-writer renamed-gfi-output-file-pathname (value)
  (cond ((text-string-p value) (tprin value t))
	((designation-p value) (print-designation value))
	((null value) (twrite 'none))))


(def-slot-value-writer gfi-output-values (value)
  (cond ((null value)
	 (twrite 'none))
	((listp value)
	 (cond ((null (first value))
		(twrite 'none))
		((listp (first value))
		 (print-designation-list (first value)))
		(t
		 #+development
		 (twrite-string "[unknown-output-value-format]"))))
	(t
	 #+development
	 (twrite-string "[unknown-output-value-format]"))))

;; Needed really for the "no value" (none) case.  Otherwise, the
;; gfi-output-value slot is written as text slot (text-slot-type-p is T),
;; without using the slot-value-writer.  For example, see make-text-
;; representation-for-slot-value-itself.  - cpm, 4/18/95


(def-substitution-macro gfi-write-interval-p (value)
  (and (listp value)
       (eq (car value) 'write-interval)
       (consp (second value))))


(def-slot-value-writer gfi-output-file-update-frequency (value)
  (cond ((null value) (twrite 'none))
	((eq value 'none) (twrite 'none))
	((eq value 'when-received-value)
	 (tformat "write to file when variables receive values"))
	((eq value 'output-one-shot-when-activated)
	 (tformat "write to file when activated"))
	((eq value 'output-one-shot-when-activated-without-interruption)
	 (tformat "write to file when activated, without interruption"))
	((gfi-write-interval-p value)
	 (tformat "write to file every ")
	 (print-constant (car (second value)) 'seconds))
	(t (warning-message
             2
	     "The slot value writer for gfi-output-file-update-frequency ~
              received an illegal value: ~a."
	     value))))


(defmacro interrupt-driven-gfi-file-update-frequency-p (update-frequency)
  `(memq ,update-frequency '(when-received-value)))






;;;; GFI-INPUT-INTERFACE CLASS

(def-class (gfi-input-interface
	     object
	     (foundation-class object)
	     (disjoint-from gsi-interface g2-to-g2-data-interface
			    gfi-output-interface)
	     define-predicate)
  (file-system
    nil					; set by initialize method
    (lookup-slot) (type read-only-attribute) (not-user-editable) (do-not-save)
    (system) no-accessor)
  (file-status
    ready-to-open
    (lookup-slot) (type read-only-attribute) (not-user-editable) (do-not-save)
    (system) no-accessor)
  (ignore-gfi-input-base-time?
    t (lookup-slot) (type gfi-yes-or-no?) (system)
    user-overridable (save))
  (gfi-input-variables-update-mode
    nil (lookup-slot)
    (type gfi-input-variables-update-mode) user-overridable
    (system) (save))
  (gfi-input-time-stamp-format
    relative (lookup-slot) (type gfi-time-stamp-format) user-overridable
    (system) (save))
  (gfi-input-file-format
    event-log (lookup-slot) (type gfi-file-format)
    user-overridable (system) (save))
  (gfi-input-file-pathname
    nil (lookup-slot) (type gfi-file-pathname)
    user-overridable (system) (save))
  (gfi-input-when-active
    t (lookup-slot) (type gfi-yes-or-no?) (system)
    user-overridable (save))
  (gfi-current-input-designation
    nil (lookup-slot) (type e-designation)
    (do-not-put-in-attribute-tables)
    (do-not-save))
  (gfi-inputting?
    nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
  (gfi-input-file-stream
    nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
  (gfi-input-base-time
    nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
  ;; In version 4.0, gfi-input-gensym-time-at-start was renamed to
  ;; gfi-input-g2-time-at-start.  - cpm, 7/1/94
  (gfi-input-g2-time-at-start
    nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
  (gfi-input-line
    nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
  ;; In version 4.0, gfi-input-line-gensym-time was renamed to
  ;; gfi-input-line-g2-time.  - cpm, 7/1/94
  (gfi-input-line-g2-time
    nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
  (gfi-input-line-length
    0 (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
  (gfi-input-line-current-index
    0 (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
  (gfi-input-spreadsheet-designations
    nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
  (gfi-queue-of-variables-that-need-values
    nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
  (gfi-input-file-synchronized?
    nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
  (gfi-input-without-interruption?
    nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
  (gfi-input-pathname-string-of-stream?
    nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
  (gfi-input-ignore-data-server?
    nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
  (text-conversion-style
    nil
    (type text-conversion-style-name?)
    no-accessor
    lookup-slot system)

  ;; This group of 4 slots is managed by the creator and reclaimer for this
  ;; class, by open-gfi-input-interface, which opens the stream, and by
  ;; gfi-read-line, the sole input getting operation.
  (gfi-input-file-buffer
    (:funcall obtain-simple-gensym-string
	      #.size-of-g2-stream-frame-input-buffer)
    (lookup-slot) do-not-save)
  (gfi-input-file-buffer-available-characters 0 (lookup-slot) do-not-save)
  (gfi-input-file-buffer-position 0 (lookup-slot) do-not-save)
  (gfi-input-file-buffer-offset 0 (lookup-slot) do-not-save))

(def-slot-value-reclaimer gfi-input-file-buffer (value)
  (reclaim-simple-gensym-string value))



(define-slot-alias ignore-gfi-input-base-time ignore-gfi-input-base-time?)




;;; Grammar for GFI-INPUT-INTERFACE slots:


(add-grammar-rules
  `((gfi-input-variables-update-mode 'none)
    (gfi-input-variables-update-mode ('asynchronous 'input) asynchronous)
    (gfi-input-variables-update-mode
      ('asynchronous 'input '\, 'ignoring 'the 'data 'server)
      asynchronous-ignoring-data-server)
    (gfi-input-variables-update-mode
      ('input 'on 'request 'preserving 'time-stamps)
      on-request)
    (gfi-input-variables-update-mode
      ('input 'on 'request 'sample-and-hold)
      on-request-sample-and-hold)
    (gfi-input-variables-update-mode
      ('input 'when 'activated) input-one-shot-when-activated)
    (gfi-input-variables-update-mode
      ('input 'when 'activated '\, 'without 'interruption)
      input-one-shot-when-activated-without-interruption)))



;;; The defun-substitution-macro `ignore-data-server-in-gfi-input-interface?'
;;; is the predicate that decides if the variables update mode allows
;;; the data server of the variable or parameter to be ignored.

(defun-substitution-macro ignore-data-server-in-gfi-input-interface?
			  (variables-update-mode)
  (let ((result?
	  (memq 
	    variables-update-mode
	    '(asynchronous-ignoring-data-server
	       input-one-shot-when-activated
	       input-one-shot-when-activated-without-interruption))))
    (if result?	t nil)))

(defun-substitution-macro set-gfi-input-ignore-data-server?-flag
			  (variables-update-mode gfi-input-frame)
  (setf (gfi-input-ignore-data-server? gfi-input-frame)
	(ignore-data-server-in-gfi-input-interface?
	  variables-update-mode)))






;;; Slot value writers for GFI-INPUT-INTERFACE slots:

(def-slot-value-writer ignore-gfi-input-base-time? (value?)
  (twrite-string (if value? "yes" "no")))

(def-slot-value-writer gfi-input-variables-update-mode (value gfi-input-frame)
  (when (of-class-p gfi-input-frame 'gfi-input-interface)
    (set-gfi-input-ignore-data-server?-flag value gfi-input-frame))
  (cond ((null value)
	 (twrite-string "none"))
	((eq value 'asynchronous)
	 (twrite-string "asynchronous input"))
	((eq value 'asynchronous-ignoring-data-server)
	 (twrite-string "asynchronous input, ignoring the data server"))
	((eq value 'on-request)
	 (twrite-string "input on request preserving time-stamps"))
	((eq value 'on-request-sample-and-hold)
	 (twrite-string "input on request sample-and-hold"))
	((eq value 'input-one-shot-when-activated)
	 (twrite-string "input when activated"))
	((eq value 'input-one-shot-when-activated-without-interruption)
	 (twrite-string "input when activated, without interruption"))
	(t (warning-message
	     2 "The attribute gfi-input-variables-update-mode contains ~
                an illegal value ~a." value))))



(def-slot-value-compiler gfi-input-variables-update-mode (parse-result)
  (cond ((null parse-result) nil)
	  ((eq parse-result 'none) nil)
	  (t parse-result)))






;;;; GFI-DATA-SERVICE CLASS

(def-class (gfi-data-service variable define-predicate
			     (only-compatible-with variable)
			     (foundation-class variable)
			     not-solely-instantiable
			     not-user-instantiable do-not-put-in-menus)
  (data-server-map
    gfi-data-server (vector-slot) (system) (type data-server-map))
  (gfi-input-interface-object
    nil (lookup-slot) (type gfi-interface-object) user-overridable
    (system) (save))
  (gfi-last-value
    nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save))
  (gfi-time-of-last-value-update
    nil (lookup-slot) (do-not-put-in-attribute-tables) (do-not-save)))


;(defmacro gfi-input-interface-object (variable)
;  `(get-slot-value ,variable 'gfi-input-interface-object))

;(defmacro gfi-last-value (variable)
;  `(get-slot-value ,variable 'gfi-last-value))

;(defmacro gfi-time-of-last-value-update (variable)
;  `(get-slot-value ,variable 'gfi-time-of-last-value-update))


;; Note that the setf method of get-slot-value handles the setf case for these
;; accessors.  -jra 10/25/88



;; This absent-slot-putter should be removed after 1.2 is out.  -pto 08nov88

(def-absent-slot-putter gfi-interface-object (frame-var new-value)
  (change-slot-value frame-var 'gfi-input-interface-object new-value))



(add-grammar-rules
  '((gfi-interface-object 'none)
    (gfi-interface-object constant-designation)))

(def-slot-value-compiler gfi-interface-object (parse-result)
  (if (eq parse-result 'none)
      nil
      parse-result))

(def-slot-value-writer gfi-interface-object (value)
  (cond ((null value) (twrite-string "none"))
	(t (print-designation value))))

(def-data-server-pretty-printer 'gfi-data-server "GFI data server")

