;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module PRINTING

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author(s): Ben Hyde 







;;;; Introduction For Printing




;;; The printing module works by intercepting the ICP message traffic that
;;; happens when a workspace is drawn.  The intercepted traffic is then
;;; translated into a stream of postscript.  That postscript is placed into a
;;; file.  We then give up and expect the user to determine some scheme that
;;; gets this spooled print file to his postscript printer.

;;; The workspace is actually drawn in two modes/passes, and it is drawn a total
;;; of N+1 times where N is the number of pages we need to print.  The first
;;; time the workspace is drawn, known as pass one, we emit definitions that the
;;; N other drawing passes, known collectively as pass 2, will depend upon.
;;; Pass 1 is actually only necessary to build, define and install kanji (read
;;; non-Latin) fonts before they are used, but it is also used to define icon
;;; renderings and all fonts.



;;;; Intermodule References

;;; Printing depends on the file abstractions in STREAMS.  Printing is utilized
;;; by INT, to implement the printing bottleneck in that redirects rendering to
;;; the printiner rather than to a workspace.  Printing is utilized by
;;; FACILITIES to implement the workspace menu command that invokes printing.
;;; PRINTING-P and PRINTING-P-MACRO is used in misc. places throughout G2 to
;;; decide if we are printing and then to modify drawing behavor when we are.

(declare-forward-reference paint-graph-on-scratchpad-raster function)
(declare-forward-reference bogus-preflight-from-printing-to-graphs function)
(declare-forward-reference current-workstation variable)
(declare-forward-reference servicing-workstation? variable)       ;; WORKSTATION
(declare-forward-reference current-computation-component-particulars variable)
(declare-forward-reference maybe-schedule-service-workstations-final function)

;; To TELESTUBS:
(declare-forward-reference get-current-user-name function)

(declare-forward-reference native-printing-start-doc function)
(declare-forward-reference native-printing-start-page function)
(declare-forward-reference native-printing-end-page function)
(declare-forward-reference native-printing-end-doc function)
(declare-forward-reference native-printing-begin function)
(declare-forward-reference native-printing-end function)
(declare-forward-reference paint-icon-in-current-window function) ; New ICP message
(declare-forward-reference paint-line-of-text-in-current-window function) ; New ICP message

;; To TABLES
(declare-forward-reference get-or-make-up-designation-for-block function)

;; To CONNECT3A
(declare-forward-reference image-plane-has-drawing-in-window-p function)

;; To CHARTS
(declare-forward-reference decache-all-graph-renderings-on-window function)

;; To CONTROLS
(declare-forward-reference map-g2-window-to-gensym-window function)

;; To NATIVE-TW
(declare-forward-reference send-icp-print-native-window function)


;;;; Utilities To Be Moved Later



;;; `Update-frame-status-and-notes' a method defined on some blocks will
;;; recompute entirely the frame notes of the block it is invoked upon.
;;; Refinements to this should be defined as after methods.

(def-generic-method update-frame-status-and-notes (block))



;;; `Update-frame-status-and-notes on block' is currently a noop.  It is
;;; refined by defining after methods.

(def-class-method update-frame-status-and-notes (block)
  (declare (ignore block)))



;;; `Assert-frame-notes' and `retract-frame-notes' are methods defined upon some
;;; blocks.  they maybe used to remove and restore the frame notes of the block.

(def-generic-method assert-frame-notes (block))

(def-generic-method retract-frame-notes (block))





;;;; System Table For Printer Setup



;;; The many details of exactly how the printing should behave are specified in
;;; the printer-setup, system table.  These include: how to translate the output
;;; for the printer, ie.  "Printing Details", how the pages are configured, ie.
;;; "Page Layout", and how to handle the spooled file, ie.  "Print Spooling."

;;; `Printing Details' states how to scale the workspace, and how to do the
;;; color mapping.

;;; `Page Layout' specifies the paper size, orientation, and margins.

;;; `Print Spooling' provides specifics of how to spool the file; includes where
;;; G2 should create the spooled output file, should the file created be spooled
;;; to the printer once it has been created, and host specific details that
;;; describe which printer we should spool the file to.

;;; All slots of the printer-setup are internally represented as an alist.

;;; These are the keys and type of the CDR of the alist entry:
;;;  printing-details, who's grammar type is printer-translation-details
;;;     workspace-scaling   scale-to-fit-single-page | 
;;;                            (<number/workspace unit> <linear-measure/symbol>)
;;;                            -- limited to lower limit of 5/inch (tbd)
;;;                            -- limited to upper limit of 20,000/inch (tbd)
;;;     color-conversion     black-and-white | grays | full-color
;;;  page-layout, who's grammar type is printer-page-layout,
;;;      paper-size    letter | TBD
;;;      paper-orientation   portrait | landscape
;;;      left-margin   <linear-distance>
;;;      top-margin   <linear-distance>
;;;      right-margin   <linear-distance>
;;;      bottom-margin   <linear-distance>
;;;  print-spooling, who's grammar type is printer-spooling-details,
;;;      spooled-filename-template    string
;;;      spool-file-to-printer       <boolean>
;;;      printer-identification       string

;;; The grammar requires they appear in the order shown, and none of the entries
;;; are optional.  The writter's implementation is simplified by making the text
;;; shown the user for each entry the same as the internal key, except the
;;; hyphens are changed to spaces.

;;; All slots are save, so all slots contents are implemented using slot values.


;;; `do-typical-category-setter-calling'
;;; Helpful macro for calling many category setters. The typical slot-value
;;; should have the form ((name1 . value1)(name2 . value2) ...)
;;; Must be called from within a with-safe-category-setter-calling block.
;;; Returns a phrase-list as the result.

(defmacro do-typical-category-setter-calling
    (name-ev-and-category-list)
  `(phrase-list
     ,@(loop for (name ev category) in  name-ev-and-category-list
	     collect
	     `(phrase-cons
		',name
		,(if category
		     `(call-category-setter-safely ',category ,ev)
		     `,ev)))))

;;; `do-typical-category-getter-calling'
;;; Expands into setf forms whose rhs is a call to a category-getter,
;;; if one exists, value otherwise.  Assumes that all var's have a local
;;; binding.

(defmacro do-typical-category-getter-calling
    (var-value-category-list)
  (loop with setfs = nil
	for (var value category) in var-value-category-list
	 do
    (cond (category
	   (push `(setf ,var (call-category-getter ',category ,value nil nil)) setfs))
	  (t (push `(setf ,var ,value) setfs)))
	finally
	  (return
	    (cons 'progn (nreverse setfs)))))

(define-category-evaluator-interface (yes-or-no
				       :access read-write)
    truth-value
  ((set-form (evaluation-value))
   (evaluation-truth-value-is-true-p evaluation-value))
  ((get-form (slot-value))
   (make-evaluation-boolean-value slot-value)))
	 
(define-category-evaluator-interface (linear-unit-of-length
				       :access read-write)
   (member inch inches centimeter centimeters 
	   cm foot feet millimeter millimeters mm)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))

(define-category-evaluator-interface (linear-distance
				       :access read-write)
    (structure linear-distance
	       ((number number)
		(units (named linear-unit-of-length)))
	       (and number units))
  ((set-form (evaluation-value))
   (with-structure (evaluation-value linear-distance)
     (phrase-list
       (evaluation-quantity-to-phrase-quantity number)
       units)))
  ((get-form (slot-value))
   (cond
     (slot-value
      (with-new-structure (linear-distance)
	(setf number
	      (slot-value-number-to-evaluation-quantity (car slot-value)))
	(setf units (cadr slot-value))))
     (t nil))))

(define-category-evaluator-interface (paper-size-kind
				       :access read-write)
    (or
      (member . #.(mapcar #'car postscript-paper-sizes))
      (structure
	paper-area
	((width (named linear-distance))
	 (height (named linear-distance)))
	(and width height)))

  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (evaluation-etypecase
	 evaluation-value
	 ((structure)
	  (with-structure (evaluation-value paper-area)
	    (phrase-list
	      'custom
	      (call-category-setter-safely 'linear-distance width)
	      (call-category-setter-safely 'linear-distance height))))
	 (symbol
	   evaluation-value))))
  ((get-form (slot-value))
   (cond ((symbolp slot-value)
	   slot-value)
	 (t
	  (with-new-structure (paper-area)
	    (setf width (call-category-getter 'linear-distance
					      (cadr slot-value) nil nil))
	    (setf height (call-category-getter 'linear-distance
					       (caddr slot-value) nil nil)))))))



(define-category-evaluator-interface (printer-page-layout
				       :access read-write)
    (structure
      page-layout
      ((paper-size (named paper-size-kind))
       (paper-orientation (member portrait landscape))
       (left-margin (named linear-distance))
       (top-margin  (named linear-distance)) 
       (right-margin (named linear-distance))
       (bottom-margin (named linear-distance)))
      (and paper-size paper-orientation
	   left-margin top-margin
	   right-margin bottom-margin))
  ((set-form (evaluation-value))
   (evaluation-etypecase
     evaluation-value
     ((structure)
      (with-structure (evaluation-value page-layout)
	(with-safe-category-setter-calling
	    (do-typical-category-setter-calling
		((paper-size paper-size paper-size-kind)
		 (paper-orientation paper-orientation)
		 (left-margin left-margin linear-distance)
		 (top-margin top-margin linear-distance)
		 (right-margin right-margin linear-distance)
		 (bottom-margin bottom-margin linear-distance))))))))
  ((get-form (slot-value))
   (cond
     (slot-value
      (with-new-structure (page-layout)
	(do-typical-category-getter-calling
	    ((paper-size (cdr (assq 'paper-size slot-value)) paper-size-kind)
	     (paper-orientation (cdr (assq 'paper-orientation slot-value)))
	     (left-margin (cdr (assq 'left-margin slot-value)) linear-distance)
	     (top-margin (cdr (assq 'top-margin slot-value)) linear-distance)
	     (right-margin (cdr (assq 'right-margin slot-value)) linear-distance)
	     (bottom-margin (cdr (assq 'bottom-margin slot-value)) linear-distance)))))
     (t
      nil))))

(define-category-evaluator-interface (kind-of-scaling
				       :access read-write)
    (or (member scale-to-fit-single-page)
	(named linear-distance))
  
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (evaluation-etypecase
	 evaluation-value
	 ((structure)
	  (call-category-setter-safely 'linear-distance evaluation-value))
	 (symbol
	   evaluation-value))))
  ((get-form (slot-value))
   (cond ((symbolp slot-value)
	  slot-value)
	 (t
	  (call-category-getter 'linear-distance slot-value nil nil)))))
  
(define-category-evaluator-interface (printer-translation-details
				       :access read-write)
    (structure printing-details
      ((workspace-scaling (named kind-of-scaling))
     
       (color-conversion (member black-and-white grays full-color)))
      (and workspace-scaling color-conversion)) ; required(minimum)-contents
  
  ((set-form (evaluation-value))
   (evaluation-etypecase
     evaluation-value
     ((structure)
      (with-structure (evaluation-value printing-details)
	(with-safe-category-setter-calling
	    (phrase-list
	      (phrase-cons
		'workspace-scaling
		(call-category-setter-safely 'kind-of-scaling workspace-scaling))
	      (phrase-cons 'color-conversion color-conversion)))))))
  ((get-form (slot-value))
   (cond
     (slot-value
      (with-new-structure (printing-details)
	(setf workspace-scaling
	      (call-category-getter 'kind-of-scaling
				    (cdr (assq 'workspace-scaling slot-value))
				    nil nil))
	(setf color-conversion
	      (cdr (assq 'color-conversion slot-value)))))
     (t
      nil))))


(define-category-evaluator-interface (printer-spooling-details
				       :access read-write)
    (structure
      print-spooling
      ((spooled-filename-template text)
       (spool-file-to-printer (named yes-or-no))
       (printer-identification text))
      (and spooled-filename-template
	   spool-file-to-printer
	   printer-identification))
  ((set-form (evaluation-value))
   (evaluation-etypecase
     evaluation-value
     ((structure)
      (with-safe-category-setter-calling
      (with-structure (evaluation-value print-spooling)
	(phrase-list
	  (phrase-cons
	    'spooled-filename-template
	    (copy-for-phrase spooled-filename-template))
	  (phrase-cons
	    'spool-file-to-printer
	    (call-category-setter-safely 'yes-or-no spool-file-to-printer))
	  (phrase-cons
	    'printer-identification
	    (copy-for-phrase printer-identification))))))))
  ((get-form (slot-value))
   (cond
     (slot-value
      (with-new-structure (print-spooling)
	(setf spooled-filename-template
	      (copy-evaluation-value
		 (cdr (assq 'spooled-filename-template slot-value))))
	(setf spool-file-to-printer
	      (call-category-getter
		'yes-or-no
		(cdr (assq 'spool-file-to-printer slot-value))
		nil nil))
	(setf printer-identification
	      (copy-evaluation-value
		(cdr (assq 'printer-identification slot-value))))))
     (t
      nil))))
	    
(define-category-evaluator-interface (printing-file-format
				       :access read-write)
    (member encapsulated-postscript postscript jpeg)
  
  ((set-form (evaluation-value))
   (cond ((eq evaluation-value 'encapsulated-postscript)
	  'eps)
	 (t evaluation-value)))
  ((get-form (slot-value))
   (cond ((eq slot-value 'eps)
	  'encapsulated-postscript)
	 (t slot-value))))


(def-system-frame printer-setup printing 
  (printing-details
    ((workspace-scaling . (100 inch))
     (color-conversion . black-and-white))
    vector-slot system (type printer-translation-details))
  (page-layout 
    ((paper-size . letter)
     (paper-orientation . portrait)
     (left-margin . (0.5 inch))
     (top-margin . (0.5 inch))
     (right-margin . (0.5 inch))	  
     (bottom-margin . (0.5 inch)))
    vector-slot system (type printer-page-layout))
  (print-spooling
    ((spooled-filename-template . "print-*.ps")
     (spool-file-to-printer . nil)
     (printer-identification . "unknown"))
    vector-slot system (type printer-spooling-details))
  (printing-priority 8	    ; User name is "priority for printing"
    vector-slot system (type priority))
  (printing-file-format postscript
    vector-slot system (type printing-file-format))

  ;; If page-economy-mode is true, then (a) printing of borders is suppressed if
  ;; there is no frame style for the workspace; (b) multipage legends are
  ;; suppressed on otherwise blank pages; and (c) blank pages are not printed.
  ;; This feature was added for G2 6.2, based on suggestion HQ-4080268 "Allow
  ;; option not to print workspace border line". --MHD, with much help from FMW,
  ;; 6/14/02
  (page-economy-mode nil
    vector-slot system (type yes-or-no)))

;; I'm first of all glad that now every slot has constant list structure
;; as its default.  This saves a that much space when defaults are kept
;; that way, which makes having a few dozen of these around (in the modules
;; case) that much easier to swallow.  The first two slots were set to
;; go.
;;
;; The final slot needed a bit of decision-making:
;;
;; (1) Whether to continue to support a TI-only dependency.  NO.
;;
;; (2) Whether to generate an absolute pathname at the time of initializing the
;; slot.  NO.  The default filename template should be relative.  It might make
;; sense to store an absolute pathname that is the "default pathname" the day
;; you create your system tables.  It's especially bad in an nfs environment,
;; where the name could contain temporary mount points. Using a relative name is
;; handling this similar to file names in log file parameters and module
;; parameters.

;; This is also in line with the way other slots that are initially list
;; structure work.  E.g., the object-configuration (user-restrictions) of
;; the kb-restrictions system table.

;; Note that to do rplaca's and rplacd's on parts of the list now requires
;; a copy-for-slot-value when the slot is still EQ to its init form.  That
;; isn't needed yet, and should not be a problem when the time comes.
;;
;; (MHD 11/18/93)


;; Show it to the user as "priority-for-printing"
(define-slot-alias priority-for-printing printing-priority
  printing-parameters)


(def-class-method initialize (printer-setup)
  (funcall-superior-method printer-setup)
  (funcall-method-if-any 'update-frame-status-and-notes printer-setup))

(def-slot-putter printing-details (printer-setup-instance new-value)
  (setf (printing-details printer-setup-instance) new-value)
  (when (system-table-installed-p printer-setup-instance)
    (funcall-method-if-any 'update-frame-status-and-notes printer-setup-instance))
  new-value)

(def-slot-putter page-layout (printer-setup-instance new-value)
  (setf (page-layout printer-setup-instance) new-value)
  (when (system-table-installed-p printer-setup-instance)
    (funcall-method-if-any 'update-frame-status-and-notes printer-setup-instance))
  new-value)

(def-slot-putter print-spooling (printer-setup-instance new-value)
  (setf (print-spooling printer-setup-instance) new-value)
  (when (system-table-installed-p printer-setup-instance)
    (funcall-method-if-any 'update-frame-status-and-notes printer-setup-instance))
  new-value)



(def-class-method install-system-table (printer-setup)
  (when (system-table-installed-p printer-setup)
    (funcall-method-if-any 'update-frame-status-and-notes printer-setup)))


(def-class-method deinstall-system-table (printer-setup))

;; I fixed printer-setup slot putters above not to update their frame status
;; and notes if they're not the installed system table.  Also, they do the
;; update now upon installation.  Nothing needs to happen as far as I could
;; tell upon deinstallation.
;;
;; Also: I found that the putters above were of the form
;;
;;   (def-slot-putter <printer slot name> (FRAME ...) ...)
;;
;; I assumed this was a bug, leading to items of every class having the
;; givent <printer slot name> method, and changed them to be of the form
;;
;;   (def-slot-putter <printer slot name> (PRINTER-SETUP ...) ...)
;;
;; BAH should review.  (MHD 10/15/91)
;; -- The above bogus comment -- by me -- is interesting.  The name of the
;; first formal parameter does not make the putter specific to that class.
;; We do not have class-specific slot putters at all.  The comment reveals my
;; lack of understanding  at the time of def-slot-putter, and also, possibly,
;; of the potential of this change for breaking the functionality of
;; system-table-installed-p.  I have now gone through and changed the
;; formal parameter to PRINTER-SETUP-INSTANCE everywhere.  See discussion
;; in BOOKS with this stamp: (MHD 6/30/93)


;;; `printer-setup-particular' it is the only accessor used in the printing code
;;; below. If printing natively, we get the information mostly from the
;;; native-printer-information special variable, which is a plist. Otherwise,
;;; from the printer-setup table.

(defun printer-setup-particular (key)
  (declare (special native-printer-information)) ; fwd ref.
  (cdr (or (assq key (printing-details printer-setup))
	   (assq key native-printer-information)
	   (assq key (page-layout printer-setup))
	   (assq key (print-spooling printer-setup)))))

;;; The function `compute-native-printer-information' computes a slot-value
;;; alist of information about a native printer, based on plist, in the form
;;; needed by printer-setup-particular. The plist originates in print-dialog-1
;;; in TELESTUBS.

(defun compute-native-printer-information (plist)
  (let* ((x-dpi (coerce-to-gensym-float (getf plist 'x-dpi)))
	 (y-dpi (coerce-to-gensym-float (getf plist 'y-dpi)))
	 (physical-width (getf plist 'physical-width))
	 (physical-height (getf plist 'physical-height))
	 (width (getf plist 'width))
	 (height (getf plist 'height))
	 (x-offset (getf plist 'x-offset))
	 (y-offset (getf plist 'y-offset))
	 (printer (getf plist 'printer))
	 (quality (getf plist 'quality))
	 (from-page (getf plist 'from-page))
	 (to-page (getf plist 'to-page))
	 (requested-margins
	   (loop for margin in '(left-margin top-margin right-margin bottom-margin)
		 as value? = (getf plist margin) ; Eg, (0 inch)
		 when value?
		   collect (slot-value-cons margin (copy-list-using-slot-value-conses value?))
		     using slot-value-cons))
	 (pathname? (getf plist 'pathname)))
    (nconc
      (slot-value-list
	(slot-value-cons 'paper-orientation 'portrait) ; Windows takes care of this.
	(slot-value-cons 'color-conversion 'full-color)
	(slot-value-cons 'quality quality)
	(slot-value-cons 'printer-identification (copy-if-text-string printer))
	(slot-value-cons 'from-page from-page)
	(slot-value-cons 'to-page to-page)
	(let ((physical-width-inches (/e (coerce-to-gensym-float physical-width) x-dpi))
	      (physical-height-inches (/e (coerce-to-gensym-float physical-height) y-dpi)))
	  (slot-value-cons
	    'paper-size
	    ;; Eg, (CUSTOM (8.5 INCH) (11.0 INCH))
	    (slot-value-list 'custom
			     (slot-value-list (allocate-managed-float physical-width-inches)
					      'inch)
			     (slot-value-list (allocate-managed-float physical-height-inches)
					      'inch))))
	;; Compute margins relative to edges of paper, in inches.
	(let ((lm (allocate-managed-float (/e (coerce-to-gensym-float x-offset)
					      x-dpi)))
	      (tm (allocate-managed-float (/e (coerce-to-gensym-float y-offset) y-dpi)))
	      (rm (allocate-managed-float (/e (coerce-to-gensym-float
						(-f physical-width width x-offset))
					      x-dpi)))
	      (bm (allocate-managed-float (/e (coerce-to-gensym-float
						(-f physical-height height y-offset))
					      y-dpi))))
	  (slot-value-cons 'paper-margins
			   (slot-value-list (slot-value-list lm 'inch)
					    (slot-value-list tm 'inch)
					    (slot-value-list rm 'inch)
					    (slot-value-list bm 'inch)))))
      (if pathname?
	  (slot-value-list (slot-value-cons 'pathname (copy-text-string pathname?))))
      requested-margins)))


(defun generate-eps-p ()
  (eq (printing-file-format printer-setup) 'eps))

(defun generate-bitmap-p (&optional plist)
  (if plist
      (eq (getf plist 'printer) 'jpeg)
    (eq (printing-file-format printer-setup) 'jpeg)))

(defun printer-workspace-scaling ()
  (printer-setup-particular 'workspace-scaling))

    
       

;;;; Frame Notes In The Printer Setup


;;; Frame notes are placed in the printer setup to report to the user
;;; notable things about the settings he requested.  These include:
;;;   - printer-file-template-is-misformed
;;;   - printer-is-not-default-printer
;;;   - printer-no-printer-specified
;;;   - printer-is-unknown

;;; They are all recomputed from scratch by the initialize method and the
;;; slot putters.  Their particulars are always the symbol T.

(def-frame-note-writer printer-file-template-is-misformed (particulars)
  (declare (ignore particulars))
  (tformat "the filename template for the spooled file is not in a valid format"))

(def-frame-note-writer printer-is-not-default-printer (particulars)
  (declare (ignore particulars))
  (tformat "the requested printer is not the default printer for this machine"))

(def-frame-note-writer printer-no-printer-specified (particulars)
  (declare (ignore particulars))
  (tformat "since the printer identification is unknown, printed output will be left in the spooled output file"))

(def-frame-note-writer printer-is-unknown (particulars)
  (declare (ignore particulars))
  (tformat "the requested printer is not one of the known printers for this host"))

(def-frame-note-writer printer-small-margin-are-ignored (particulars)
  (declare (ignore particulars))
  (tformat "small margins are often not supported by printers"))

(def-frame-note-writer printer-paper-size-is-unreasonable (particulars)
  (declare (ignore particulars))
  (tformat
    "the requested paper size is out of range or otherwise unattainable e.g. due to too wide margins"))

;; This frame-note should no longer appear. But, it might be in some saved kbs.
(def-frame-note-writer printer-only-black-and-white-is-supported (particulars)
  (declare (ignore particulars))
  (tformat ""))
;;  (tformat "in this release the only color conversions supported are black-and-white or full-color")

;; This frame note name is somewhat misleading.

(def-frame-note-writer printer-unimplemented-page-layout-settings (particulars)
  (declare (ignore particulars))
  (tformat ""))
;; Obsolete frame note.

(def-frame-note-writer printer-g2-can-not-spool-output-on-this-platform (particulars)
  (declare (ignore particulars))
  (tformat "unable to spool output directly to the printer on this machine, ~
            you will have to transmit the file to the printer by some means outside of G2"))

(def-class-method update-frame-status-and-notes (printer-setup)
  ;; Clear out all the notes this frame gets.
  (loop for frame-note-kind in '(printer-file-template-is-misformed
				 printer-is-not-default-printer
				 printer-no-printer-specified
				 printer-is-unknown
				 printer-only-black-and-white-is-supported
				 printer-unimplemented-page-layout-settings
				 printer-small-margin-are-ignored
				 printer-paper-size-is-unreasonable
				 printer-unimplemented	; Obsolete note
				 printer-g2-can-not-spool-output-on-this-platform)
	do (delete-frame-note-if-any frame-note-kind printer-setup))
  ;; Check out the printing details.
  (when (printing-details printer-setup)

    ;; We now allow GRAYS conversion, which means that BG images are rendered w/o using
    ;; the colorimage operator.
;    (unless (memq (printer-setup-particular 'color-conversion)
;		  '(black-and-white full-color))
;      (add-frame-note 'printer-only-black-and-white-is-supported printer-setup t t nil))

    )
  
  ;; Check out the page-layout
  (when (page-layout printer-setup)

    (when (with-temporary-gensym-float-creation printing
	    (let* ((small-margin-mf (postscript-convert-linear-distance-to-postscript-units-mf '(0.25 inch)))
		   (result
		     (loop for particular-margin-name in '(left-margin top-margin
							   right-margin bottom-margin)
			   do
		       (let* ((particular-margin-value-mf
				(postscript-convert-linear-distance-to-postscript-units-mf
				  (printer-setup-particular particular-margin-name)))
			      (flag
				(<e (managed-float-value particular-margin-value-mf)
				    (managed-float-value small-margin-mf))))
			 (reclaim-managed-float particular-margin-value-mf)
			 (when flag (return t))))))
	      (reclaim-managed-float small-margin-mf)
	      result))
      (add-frame-note 'printer-small-margin-are-ignored printer-setup t t nil))

    ;; Check out the paper size.
    (when (with-temporary-gensym-float-creation printing
	    (let ((paper-size (printer-setup-particular 'paper-size)))
	      (or (when (consp paper-size)
		    ;; Check out the paper size in absolute terms:
		    (let ((small-mf
			    (postscript-convert-linear-distance-to-postscript-units-mf
			      '(1.0 inch)))
			  (large-mf
			    (postscript-convert-linear-distance-to-postscript-units-mf
			      '(50 feet)))
			  (dimension-1-mf
			    (postscript-convert-linear-distance-to-postscript-units-mf
			      (slot-value-number-value (second paper-size))))
			  (dimension-2-mf
			    (postscript-convert-linear-distance-to-postscript-units-mf
			      (slot-value-number-value (third paper-size)))))
		      (prog1
			  (not (and (<e (managed-float-value small-mf)
					(managed-float-value dimension-1-mf)
					(managed-float-value large-mf))
				    (<e (managed-float-value small-mf)
					(managed-float-value dimension-2-mf)
					(managed-float-value large-mf))))
			(reclaim-managed-float small-mf)
			(reclaim-managed-float large-mf)
			(reclaim-managed-float dimension-1-mf)
			(reclaim-managed-float dimension-2-mf))))
		  
		  ;; Check out the paper size relative to margins:
		  (let* ((paper-orientation-is-portrait
			   (eq (printer-setup-particular 'paper-orientation) 'portrait))
			 (paper-size-info
			   (postscript-paper-size-info paper-size))
			 (actual-paper-width-mf
			   (postscript-convert-linear-distance-to-postscript-units-mf
			     (first paper-size-info)))
			 (actual-paper-height-mf
			   (postscript-convert-linear-distance-to-postscript-units-mf
			     (second paper-size-info)))
			 (paper-width-mf (if paper-orientation-is-portrait
					     actual-paper-width-mf
					     actual-paper-height-mf))
			 (paper-height-mf (if paper-orientation-is-portrait
					      actual-paper-height-mf
					      actual-paper-width-mf))
			 (left-margin-mf
			   (postscript-convert-linear-distance-to-postscript-units-mf
			     (printer-setup-particular 'left-margin)))
			 (top-margin-mf
			   (postscript-convert-linear-distance-to-postscript-units-mf
			     (printer-setup-particular 'top-margin)))
			 (right-margin-mf
			   (postscript-convert-linear-distance-to-postscript-units-mf
			     (printer-setup-particular 'right-margin)))
			 (bottom-margin-mf
			   (postscript-convert-linear-distance-to-postscript-units-mf
			     (printer-setup-particular 'bottom-margin)))
			 (page-width-mf (postscript-remove-margins-from-dimension
					  paper-width-mf left-margin-mf right-margin-mf))
			 (page-height-mf (postscript-remove-margins-from-dimension
					   paper-height-mf top-margin-mf bottom-margin-mf))
			 (one-inch-mf 
			   (postscript-convert-linear-distance-to-postscript-units-mf
			     '(1.0 inch))))
		    (prog1
			;; Usable print area must be at least one inch in the
			;; horizontal and vertical dimensions. - jpg 7/18/00
			(or (<e (managed-float-value page-width-mf)
				(managed-float-value one-inch-mf))
			    (<e (managed-float-value page-height-mf)
				(managed-float-value one-inch-mf)))
		      (reclaim-managed-float actual-paper-width-mf)
		      (reclaim-managed-float actual-paper-height-mf)
		      (reclaim-managed-float left-margin-mf)
		      (reclaim-managed-float top-margin-mf)
		      (reclaim-managed-float right-margin-mf)
		      (reclaim-managed-float bottom-margin-mf)
		      (reclaim-managed-float page-width-mf)
		      (reclaim-managed-float page-height-mf)
		      (reclaim-managed-float one-inch-mf))))))

      (add-frame-note 'printer-paper-size-is-unreasonable printer-setup t t nil)))
  
  ;; Check out the print-spooling
  (when (print-spooling printer-setup)
    (semantic-check-spooling-parameters)))



;;;; Paper sizes

(defun postscript-paper-size-name (paper-size)
  (cond ((atom paper-size)
	 paper-size)
	(t
	 (first paper-size))))

;;; postscript-paper-size-info returns a list of (width height)

(defun postscript-paper-size-info (paper-size)
  (or 
   (cond ((symbolp paper-size)
	  (cdr (assq paper-size postscript-paper-sizes)))
	 ((consp paper-size)
	  ;; The first dimension is not necessarily the smallest; rather, it
	  ;; is the dimension which is considered "X" in the printer's default CTM.
	  (cdr paper-size)))
   (cdr (first postscript-paper-sizes))))


;;; postscript-paper-margins is a list of (left-margin top-margin right-margin bottom-margin),

(defparameter postscript-paper-margins
  '((0.25 inch) (0.1875 inch) (0.25 inch) (0.1876 inch)))

;; While page 285 of the PS Red book says one thing,
;; experiment indicates 4/16th off the sides and 3/16th off the top & bottom
;; Also, the margin sizes differ between printers. For example, the printable is
;; significantly smaller on the HP laserwriter.


(defun postscript-paper-margins-info (paper-size)
  (declare (ignore paper-size))
  (declare (special native-printer-information)) ; fwd ref.
  (or (cdr (assq 'paper-margins native-printer-information))
      postscript-paper-margins))

;; Here we pretend that the paper margins really depend on the printer,
;; or something; in any case, not on the paper size.






;;;; Grammar Used In The Printer Setup




;;; `Linear-distance' is a grammar nonterminal for phrases that describe a real world
;;; linear distance (eg "3.4 inches", "12.7 centimeters").  Since G2 screen displays live
;;; in a synthetic world of workspace units this is actually used very rarely.  Some
;;; current users are the margins of print outs and the paper size.

(add-grammar-rules
  '((linear-distance (number linear-unit-of-length))
    (linear-unit-of-length 'inch)
    (linear-unit-of-length 'inches)
    (linear-unit-of-length 'centimeter)
    (linear-unit-of-length 'centimeters)
    (linear-unit-of-length 'cm)
    (linear-unit-of-length 'foot)
    (linear-unit-of-length 'feet)
    (linear-unit-of-length 'millimeter)
    (linear-unit-of-length 'millimeters)
    (linear-unit-of-length 'mm)
    ))

;; Inches, etc.?


;;; postscript-correct-grammar-of-linear-distance
;;; makes the units value and name agree in number.

(defun postscript-correct-grammar-of-linear-distance (value units)
  (let ((names '((inch inches)
		 (centimeter centimeters)
		 (foot feet)
		 (meter meters)
		 (millimeter millimeters)))
	(singular-p (= 1 value)))
    (loop for (singular plural) in names
	  when (or (eq units singular) (eq units plural))
	  do (return (if singular-p singular plural))
	  finally (return units))))


(def-grammar-category printer-translation-details ()
  ((workspace-scaling '\; color-conversion) (1 3)))

(def-grammar-category workspace-scaling ()
  (('workspace 'scaling '\: kind-of-scaling) (workspace-scaling . 4)))

(def-grammar-category color-conversion ()
  (('color 'conversion '\: kind-of-color-conversion) (color-conversion . 4)))

(def-grammar-category kind-of-scaling ()
  scale-to-fit-single-page
  ((number 'workspace 'units 'per linear-unit-of-length) (1 5)))

;; Did this allow only integers in Rel 3?

(def-grammar-category kind-of-color-conversion ()
  black-and-white grays full-color)

(def-grammar-category printing-file-format ()
  ('postscript postscript)
  (('encapsulated 'postscript) eps)
  ('jpeg jpeg))


(def-slot-value-compiler printer-translation-details (parse)
  (let* ((workspace-scaling (assq 'workspace-scaling parse))
	 (scale-as-phrase-number?
	   (if (consp (cdr workspace-scaling))
	       (second workspace-scaling)
	       nil))
	 (error-message?
	   nil))
    (when scale-as-phrase-number?
      (with-temporary-gensym-float-creation check-parse-for-workspace-scalling
	(let ((scale-as-lisp-number
	       (phrase-number-value scale-as-phrase-number?)))
	  (unless (or (and (integerp scale-as-lisp-number)
			   (<=f 5 scale-as-lisp-number 25000))
		      (and (gensym-float-p scale-as-lisp-number)
			   (<=e 5.0 scale-as-lisp-number 25000.0)))
	    (setf error-message?
		  (copy-text-string
		    "Workspace scale must be between 5 and 25000."))))))
    (if error-message?
	(values bad-phrase error-message?)
	parse)))

(add-grammar-rules
  '((printer-page-layout (paper-size '\;
			  paper-orientation '\;
			  left-margin '\;
			  top-margin '\;
			  right-margin '\;
			  bottom-margin ) ; Allow a trailing semicolon here? 
			 (1 3 5 7 9 11))
    
    (paper-size ('paper 'size '\: paper-size-kind) (paper-size . 4))

    (paper-size-kind (linear-distance 'by linear-distance) (custom 1 3))
    ;; The order is width by height, assuming portrait orientation.
    
    (paper-orientation ('paper 'orientation '\: paper-orientation-kind)
		       (paper-orientation . 4))
    (paper-orientation-kind 'portrait)
    (paper-orientation-kind 'landscape)
    
    (left-margin   ('left margin-tail)   (left-margin . 2))
    (top-margin    ('top margin-tail)    (top-margin . 2))
    (right-margin  ('right margin-tail)  (right-margin . 2))
    (bottom-margin ('bottom margin-tail) (bottom-margin . 2))
    (margin-tail ('margin '\: linear-distance) 3)
    ))


(defmacro add-grammar-rules-for-paper-sizes ()
  `(add-grammar-rules
    ',(loop for (name) in postscript-paper-sizes
	   collect `(paper-size-kind ',name))))

(add-grammar-rules-for-paper-sizes)


(add-grammar-rules
    '((printer-spooling-details
	(spooled-filename-template '\;
	 spool-file-to-printer '\;
	 printer-identification)
       (1 3 5))
      (spooled-filename-template ('spooled 'filename 'template '\: whole-string)
				 (spooled-filename-template . 5))
      (spool-file-to-printer ('spool 'file 'to 'printer '\: yes-or-no)
			      (spool-file-to-printer . 6))
      (printer-identification ('printer 'identification '\: whole-string)
			      (printer-identification . 4))))


  
(defun write-printer-setup-slot (slot-value-alist)
  (loop for (key . value) in slot-value-alist
	as wrote-initial-statement = nil then t
	do
    (when wrote-initial-statement
      (tformat ";~%"))
    (let ((key-string (copy-symbol-name key :first t)))
      (tformat "~A:" key-string)
      (reclaim-text-string key-string))
    (case (getf 
	    '( 
	      ;;  printing-details/printer-translation-details
	      workspace-scaling workspace-scaling ;;  scale-to-fit-single-page
	      ;; (<number/workspace unit> <linear-measure/symbol>)
	      color-conversion symbol
	      ;;  page-layout/printer-page-layout
	      paper-size paper-size
	      paper-orientation symbol
	      left-margin linear-measure
	      top-margin linear-measure
	      right-margin linear-measure
	      bottom-margin linear-measure
	      ;;  print-spooling/printer-spooling-details
	      spooled-filename-template string
	      spool-file-to-printer yes-or-no
	      printer-identification string
	      )
	    key)
      (symbol
       (tformat "~( ~S~)" value))
      (paper-size		; ---- Now either a symbol or a cons of (CUSTOM linear-dist linear-dist).
       (if (symbolp value)
	   (tformat "~( ~S~)" value)
	   (gensym-dstruct-bind ((nil (n1 d1) (n2 d2)) value) ; Should I normalize unit names?
	     (setq d1 (postscript-correct-grammar-of-linear-distance (slot-value-number-value n1) d1))
	     (setq d2 (postscript-correct-grammar-of-linear-distance (slot-value-number-value n2) d2))
	     (tformat "~( ~d ~s by ~d ~s~)" n1 d1 n2 d2))))
      (string
       (tformat " ~S" value))
      (yes-or-no
       (tformat (if value " yes" " no")))
      (linear-measure
       (with-temporary-gensym-float-creation write-printer-setup-slot-for-linear-measure
	 (tformat " ~(~S ~S~)" (slot-value-number-value (first value)) (second value))))
      (workspace-scaling
       (typecase value
	 (symbol
	  (tformat "~( ~S~)" value))
	 (list
	  (with-temporary-gensym-float-creation write-printer-setup-slot-for-workspace-scaling
	    (tformat "~( ~S workspace units per ~S~)" 
		     (slot-value-number-value (first value))
		     (second value)))))))))


(defun postscript-convert-linear-distance-to-postscript-units-mf (linear-distance &optional inverse)
  (with-temporary-gensym-float-creation printing
    (gensym-dstruct-bind ((x units) linear-distance)
      (let ((x (coerce-to-gensym-float (slot-value-number-value x)))
	    (units-multiplier
	      (case units
		((inch inches in) 1.0)
		((foot feet ft) 12.0)
		((meter meters) 39.37)
		((centimeter centimeters cm) .3937)
		((millimeter millimeters mm) .03937)
		(t 1.0))))		; Ought to be a cerror here.
	(if inverse
	    (allocate-managed-float
	      (*e 72.0 (/e 1.0 x) units-multiplier))
	    (allocate-managed-float
	      (*e 72.0 x units-multiplier)))))))


;; Fix the number writing to 

(def-slot-value-writer printer-translation-details (slot-value)
  (write-printer-setup-slot slot-value))

(def-slot-value-writer printer-page-layout (slot-value)
  (write-printer-setup-slot slot-value))

(def-slot-value-writer printer-spooling-details (slot-value)
  (write-printer-setup-slot slot-value))

(def-slot-value-writer printing-file-format (slot-value)
  (case slot-value
    (postscript (twrite-string "postscript"))
    (eps (twrite-string "encapsulated postscript"))
    (jpeg (twrite-string "jpeg"))))






;;;; Dynamic Scope Within Printing




;;; The dynamic extent `print-spooling' is established by the implementation of
;;; the workspace print menu command.  It creates a output stream for printing
;;; to as well as the gensym window into which that printing is performed.

;;; Print-spooling does not have on-image-plane as a dynamic superior.  That is
;;; established latter by the routine called to do the actual drawing.

;;; Printing-in-progress-p-1 is globally bound to nil.  It shouldn't be accessed
;;; directly use (printing-p) or (printing-p-macro) instead.  See below
;;; for more information about printing-p.

;;; The `printing-stream' is the file stream to which the postscript output is
;;; emitted.  It is created into a fresh file with the name provided by the user
;;; in the printing system table.

;;; The `gensym-window-for-printing' and a gensym-window structure upon which
;;; the drawing system will hang its hat and coat.  The color map, pane,
;;; image-pane, and empty (I hope) graphic element memory.  When we exit the
;;; print-spooling extent we reclaim this along with all this substructure.

;;; The `output-window-for-printing?' is bound for native and bitmap printing.

;;; The `postscript-composite-object-mapping' is a plist, used to associate
;;; objects (via eq) with integers.  For example an icon's line drawing
;;; description might map to the number 12.  These numbers are used to form the
;;; names of postscript name objects (ie.  g12).  If those name objects are
;;; evaluated in the postscript program the postscript equivalent of the object
;;; is left on the postscript stack or the current page.

;;; `Last-postscript-composite-object-index' used to generate these numbers.

;;; `Fonts-used-in-print-job' is a printing list of font names.  This list is
;;; accumulated during pass 1 and then used to guide the definition of each of
;;; them during the epilog of pass 1.

;;; `Kanji-fonts-used-in-print-job' is a (possibly big) data structure that
;;; records which G2 kanji fonts where used in this print job.  It is entirely
;;; made from printing conses.  The backbone is a property list, keyed by kanji
;;; font names.  The values are sets of characters in that font which were
;;; actually used in this print job.  A non-nil value can be considered a flag
;;; that kanji fonts were used at all.
;;;
;;; Note that in the context of printing, `kanji' generally means non-Latin.  In
;;; some cases it further means non-Latin and non-Cyrillic, i.e., Korean or
;;; Japanese, but in other cases cyrillic characters are included in the
;;; designation "kanji".  Originally, this meant just Japanese characters, but
;;; that has not been true since Korean was added.  (See below for higher
;;; level documentation of non-Latin font handling).

;;; `Fonts-needing-corresponding-kanji-font' Is a list of gensym font names.  It
;;; is accumulated during pass 1 and used during the epilog of pass 2 to create
;;; the equivalent of the corresponding-kanji-font-name-and-magnification
;;; property on that font.

;;; It is trivial to generate postscript definitions that are too large for the
;;; postscript interpreter to handle.  To avoid this happening we break long
;;; definitions into parts, where the Nth part's last operator is a call to N+1
;;; part's definition.  When emiting a definition we decide to break up the
;;; definition when ever few dozen operations have been emitted.
;;; `Postscript-emitting-definition' provides the boolean flag that this
;;; breaking up is enabled, while `postscript-definition-operation-counter'
;;; provides the ascending trigger to insert the breaks.

;;; The global variable printing-icon-current-region-index? is used to enable
;;; printing to emit icon descriptions that have the color parameterized.
;;; Recall that one of the parameters to
;;; add-from-icon-rendering-to-current-window is a list of the colors for each
;;; region of the icon.  ...

(def-named-dynamic-extent print-spooling
  (module printing))
(defvar-of-named-dynamic-extent printing-in-progress-p                  print-spooling 
  (global-binding nil))
(defvar-of-named-dynamic-extent printing-format                         print-spooling)
(defvar-of-named-dynamic-extent printing-stream                         print-spooling)
(defvar-of-named-dynamic-extent emit-postscript-line-length             print-spooling)
(defvar-of-named-dynamic-extent gensym-window-for-printing              print-spooling)
(defvar-of-named-dynamic-extent output-window-for-printing?             print-spooling)
(defvar-of-named-dynamic-extent bitmap-for-printing?                    print-spooling)
(defvar-of-named-dynamic-extent native-printer-information              print-spooling
  (global-binding nil))
(defvar-of-named-dynamic-extent printing-pass-number                    print-spooling)

(defvar-of-named-dynamic-extent last-postscript-composite-object-index  print-spooling)
(defvar-of-named-dynamic-extent postscript-composite-object-mapping     print-spooling)
(defvar-of-named-dynamic-extent fonts-used-in-print-job                 print-spooling)
(defvar-of-named-dynamic-extent kanji-fonts-used-in-print-job           print-spooling)
(defvar-of-named-dynamic-extent fonts-needing-corresponding-kanji-font  print-spooling)
(defvar-of-named-dynamic-extent postscript-object-mapping-for-graph-renderings
                                                                        print-spooling)
(defvar-of-named-dynamic-extent postscript-object-mapping-for-icon-renderings
                                                                        print-spooling)
(defvar-of-named-dynamic-extent postscript-computed-variables-mapping   print-spooling)

(defvar-of-named-dynamic-extent postscript-printing-icon-renderings     print-spooling)
(defvar-of-named-dynamic-extent postscript-current-graph-line-drawing-index
                                                                        print-spooling)
(defvar-of-named-dynamic-extent postscript-emitting-definition          print-spooling)
(defvar-of-named-dynamic-extent postscript-definition-operation-counter print-spooling)
(defvar-of-named-dynamic-extent printing-icon-current-region-index?     print-spooling
  (global-binding nil))
(defvar-of-named-dynamic-extent printing-graph-rendering-color-list?    print-spooling
  (global-binding nil))


;;; `Printing-p' is a function used to sense that we are in the dynamic extent
;;; of executing a print job.  Generally this requires no special behavior.
;;; But there are a few exceptions!

;;; Color rasters must be rendered as if we had N deep bit maps using the same
;;; color map as the window they will be rendered in.  This effects the
;;; rendering of color rasters so they are rendered in one pass for all N
;;; colors, not one pass for each color.  This creates a very unique control
;;; flow when printing and creates oportunities for GOTCHA behaviors.

;;; Rasters that might be incrementally updated must not be updated during
;;; the second pass (i.e. the emit N pages) of printing.  Their draw methods
;;; musts decline to update the rasters even if updates are pending.  Of
;;; course the raster should be updated entirely during the first pass (i.e.
;;; when the header is emited).  This amounts to supressing raster updates
;;; when printing-p and the raster already exists.

(defun printing-p ()
  printing-in-progress-p)

(defun polychrome-rasters-for-graphs-p (gensym-window)
  (and (printing-p)
       (printing-window-p gensym-window)
       (neq printing-format 'bitmap)))

      
;; Would like a new format code, ~P, which prints its argument as a compressed
;; postscript operator.
;; For now, let's not call this macro.

#+unused
(defmacro pformat-macro (format-string &rest args)
  (macrolet ((emit (form) `(push ,form result))
	     (emit-string ()
			  `(cond
			     ((=f start end) nil)
			     ((=f (1+f start) end)
			      (emit `(twrite-char ,(charw format-string start))))
			     (t
			      (emit `(twrite-string ,(text-string-substring format-string start end)))))))
    (loop with start = 0
	  with result = nil
	  with contour = nil
	  for end from 0 below (text-string-length format-string)
	  as c = (charw format-string end)
	  when (char=w #.%\~ c)
	    do
	      (emit-string)
	      (incf end)
	      (wide-character-case (charw format-string end)
		((#.%\A #.%\a)  (emit `(twrite ,(pop args))))
		((#.%\D #.%\d)  (emit `(twrite ,(pop args))))
		((#.%\S #.%\s)  (emit `(twrite-parsably ,(pop args))))
		(#.%\%        (emit `(twrite-char #.%newline)))
		((#.%\C #.%\c)  (emit `(twrite-char ,(pop args))))
		(#.%\(        (push (shiftf result nil) contour))
		(#.%\)   (let ((stm
			       `(let ((write-symbols-in-lower-case? t))
				  ,@result)))
			 (setf result (pop contour))
			 (emit stm)))
		(t (error "Bad case: ~c" (charw format-string end))))
	      (setf start (1+ end))
	  finally 
	    (emit-string)
	    (return `(progn ,@(nreverse result))))))



;;; The function `pformat' bottlenecks most output to the printing stream.
;;; There are a few functions, notably those which write image bytes, which
;;; call g2-stream-write-string directly.  The formatted string is assumed to
;;; be in the G2 character set, so @, ~, and \ are interpreted as escapes.
;;; Careful!

(defun pformat (format-string &optional arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9)
  (let* ((text-string
	  (tformat-text-string format-string arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9))
	(ascii-string
	  (export-text-string text-string 'pformat)))

    (g2-stream-write-string ascii-string printing-stream)

    (reclaim-text-string text-string)
    (reclaim-text-string ascii-string)
    nil))


(def-substitution-macro postscript-emit-ascii-string (ascii-string)
  (g2-stream-write-string ascii-string printing-stream))

(def-substitution-macro postscript-emit-ascii-character (ascii-character)
  (g2-stream-write-char ascii-character printing-stream))



;;; `Emit-postscript-reserve-space' takes an integer and a gensym
;;; stream.  It assures there is room for N characters on the current
;;; line.  Only if it inserts a newline it returns a non NIL value.

(defun emit-postscript-reserve-space (length stream)
  (when (<f 80 (+f emit-postscript-line-length length))
    (g2-stream-terpri stream)
    (setf emit-postscript-line-length 0)
    t))

(defmacro emit-postscript-consume-space (length)
  `(incf emit-postscript-line-length ,length))


(defmacro postscript-emit-operator (symbol)
  (cond ((and (consp symbol)
	      (eq (first symbol) 'quote)
	      (symbolp (second symbol)))
	 (let* ((actual-symbol (second symbol))
		(short-name (postscript-compress-operator-name actual-symbol)))
	   (if short-name
	       `(postscript-emit-operator-1 ',short-name)
	       `(postscript-emit-operator-1 ',(string-downcase (string actual-symbol))))))
	(t
	 (warn "POSTSCRIPT-EMIT-OPERATOR is now a macro, and prefers a quoted symbol as its argument.")
	 `(postscript-emit-operator-1 ,symbol))))

;; This is a macro because we know how to compress operators
;; only at compile-time.


(defun postscript-emit-operator-1 (operator-name)
  (pformat " ~a" operator-name)
  (postscript-emit-line-break)
  (incf postscript-definition-operation-counter)
  (when (and postscript-emitting-definition
	     (<f 32 postscript-definition-operation-counter))
    (setf postscript-definition-operation-counter 0)
    (let ((subfunction-index (incff last-postscript-composite-object-index)))
      (pformat "~%g~D}def /g~D {~%"
	       subfunction-index subfunction-index))))





;;;; Composite Object Mechinism




;;; Icon renderings are a good example of a composite object.  Composite objects are
;;; encoded into a postscript procedure and sent over the wire references to the object
;;; then execute that procedure to create a rendering of the object, or to create an
;;; instance of the object.

;;; Icon renderings, graph renderings, font lists, all utilize the composite object
;;; mechinism.


(defconser printing printing)

(defmacro lookup-postscript-index-for-object (object)
  `(getf postscript-composite-object-mapping ,object))
      

(defvar postscript-emit-integers-as-color-differences nil)
(defvar postscript-emit-composite-object-without-name nil)

(defun postscript-emit-composite-object (object)
  (typecase object
    (list
     (loop for element in object
	   do
       (typecase element
	 (symbol (postscript-emit-symbol element))
	 (fixnum 
	  (if postscript-emit-integers-as-color-differences
	      (postscript-emit-color-difference element)
	      (postscript-emit-atom element)))
	 (list (postscript-emit-composite-object element)))))
    (symbol
     (postscript-emit-symbol object))
    (fixnum 
     (if postscript-emit-integers-as-color-differences
	 (postscript-emit-color-difference object)
	 (postscript-emit-atom object)))))

;;; list is prior to symbol to assure nil is printed as a list


;;; `reserve-composite-object-index' is provided to allow allow "recursive"
;;; composite object definition without creating recursive postscript routines.
;;; A composite-object-def can call this in lieu of
;;; postscript-emit-composite-object-definition while emitting its body,
;;; accumulating composite object specs to emit for each of the indices it
;;; reserved.  After emitting the main composite definition, the list of indices
;;; and composite object specs is processed.

(defun reserve-composite-object-index ()
  (incff last-postscript-composite-object-index))


;;; `Postscript-emit-composite-object-definition' ...

(defun postscript-emit-composite-object-definition (object 
						    brackets
						    body-function
						    &optional
						    previously-reserved-index?)
  (let (;; Dynamic scope...
	(postscript-emitting-definition t)
	(postscript-definition-operation-counter 0))
    (let ((object-index
	    (or previously-reserved-index?
		(unless postscript-emit-composite-object-without-name
		  (incff last-postscript-composite-object-index)))))
      (postscript-emit-line-break)
      (unless postscript-emit-composite-object-without-name
	(pformat " /g~D" object-index))
      (pformat "~C" (charw brackets 0))
      (funcall body-function object)
      (pformat "~C" (charw brackets 1))
      (unless postscript-emit-composite-object-without-name
	(pformat "def"))
      (cond
	((eql body-function 'postscript-emit-icon-rendering-inner)
	 (printing-push object-index postscript-object-mapping-for-icon-renderings)
	 (let ((computed-values-plist-copy
		 (copy-tree-including-leaves-using-printing-conses 
		   (computed-values-plist object))))
	   (when computed-values-plist-copy
	     (printing-push
	       computed-values-plist-copy postscript-computed-variables-mapping))
	   (printing-push (printing-list
			    (x-scale-of-rendering object)
			    (y-scale-of-rendering object)
			    (reflection-and-rotation-of-rendering object)
			    (line-drawing-description-for-rendering? object)
			    (width-of-rendered-icon object)
			    (height-of-rendered-icon object)
			    computed-values-plist-copy)
			  postscript-object-mapping-for-icon-renderings)))
	(t
	 (printing-push object-index postscript-composite-object-mapping)
	 (printing-push object postscript-composite-object-mapping)))
      object-index)))


(defun postscript-emit-composite-object-or-lookup (object)
  (pformat " g~D"
	   (or (lookup-postscript-index-for-object object)
	       (postscript-emit-composite-object-definition object #w"[]" 'postscript-emit-composite-object))))



;;; `Icon-rendering' is done by four routines conspire to emit icon renderings.
;;;  - postscript-emit-icon-rendering-inner, actually emits the body of the icon rendering.
;;;  - postscript-emit-line-drawing, emits the line drawing description.
;;;  - postscript-emit-icon-rendering, ties it all together appling
;;;  - postscript-emit-composite-object-definition to the first two routines.

;;; The index used to name the line drawing is entered in the composite object mapping.
;;; The index used to name the icon rendering is entered into an object mapping specialized
;;; for icon renderings.  This second mapping has complex keys consisting of these
;;; features of the icon rendering:
;;;   - x-scale-of-rendering y-scale-of-rendering
;;;   - reflection-and-rotation-of-rendering
;;;   - line-drawing-description-for-rendering
;;;   - computed-values-plist
;;; This complexity is necessary to handle the possible recycling of the icon rendering
;;; structures.

(defun reclaim-postscript-object-mapping-for-icon-renderings (object-mapping)
  (loop for (key nil) on object-mapping by #'cddr doing
    (reclaim-printing-list key))
  (reclaim-printing-list object-mapping)
  nil)

(defun reclaim-postscript-computed-variables-mapping (mapping)
  (reclaim-tree-including-leaves-for-printing-conses mapping)
  nil)

(defun lookup-postscript-icon-rendering-index (icon-rendering)
  (let ((x-scale-of-rendering (x-scale-of-rendering icon-rendering))
	(y-scale-of-rendering (y-scale-of-rendering icon-rendering))
	(reflection-and-rotation-of-rendering (reflection-and-rotation-of-rendering icon-rendering))
	(line-drawing-description-for-rendering? (line-drawing-description-for-rendering? icon-rendering))
	(width-of-rendered-icon (width-of-rendered-icon icon-rendering))
	(height-of-rendered-icon (height-of-rendered-icon icon-rendering))
	(variable-overrides (computed-values-plist icon-rendering)))
    (loop for ((a b c d e f g) index) 
	      on postscript-object-mapping-for-icon-renderings 
		  by #'cddr
	  when (and (eql a x-scale-of-rendering)
		    (eql b y-scale-of-rendering)
		    (eql c reflection-and-rotation-of-rendering)
		    (eql d line-drawing-description-for-rendering?)
		    (eql e width-of-rendered-icon)
		    (eql f height-of-rendered-icon)
		    (sorted-plist-match-p g variable-overrides))
	    do (return index)
	  finally
	    (return nil))))

(def-structure (line-drawing-for-printing
		 (:constructor
		   make-line-drawing-for-printing
		   (line-drawing-description-for-printing
		     width-of-line-drawing-for-printing
		     height-of-line-drawing-for-printing
		     computed-values-plist-for-printing)))
  line-drawing-description-for-printing
  width-of-line-drawing-for-printing
  height-of-line-drawing-for-printing
  (computed-values-plist-for-printing
    nil :reclaimer reclaim-computed-values-plist-for-printing))

(def-copy-tree-including-leaves-using-x-conses printing)
(def-reclaim-tree-including-leaves-for-x-conses printing)

(defun reclaim-computed-values-plist-for-printing (computed-values-plist)
  (reclaim-tree-including-leaves-for-printing-conses
    computed-values-plist))


(defun reclaim-postscript-printing-icon-renderings (renderings)
  (loop for line-drawing-for-printing in renderings
	do (reclaim-line-drawing-for-printing line-drawing-for-printing))
  (reclaim-printing-list renderings)
  (setq postscript-printing-icon-renderings nil))


(defun look-up-line-drawing-for-printing (line-drawing width height computed-values-plist)
  (loop for line-drawing-for-printing in postscript-printing-icon-renderings
	when (and (eq (line-drawing-description-for-printing
			line-drawing-for-printing)
		      line-drawing)
		  (=f (width-of-line-drawing-for-printing
			line-drawing-for-printing)
		      width)
		  (=f (height-of-line-drawing-for-printing
			line-drawing-for-printing)
		      height)
		  (sorted-plist-match-p
		    (computed-values-plist-for-printing
		      line-drawing-for-printing)
		    computed-values-plist))
	  return line-drawing-for-printing
	finally
	  (return
	    (let ((line-drawing-for-printing
		    (make-line-drawing-for-printing
		      line-drawing width height
		      (copy-tree-including-leaves-using-printing-conses 
			computed-values-plist))))
	      (printing-push
		line-drawing-for-printing
		postscript-printing-icon-renderings)
	      line-drawing-for-printing))))
	    
(defun postscript-emit-icon-rendering (icon-rendering)
  (pformat " /g~D"
	   (or
	     (lookup-postscript-icon-rendering-index icon-rendering)
	     (progn
	       (let ((line-drawing-for-printing
		       (look-up-line-drawing-for-printing
			 (line-drawing-description-for-rendering? icon-rendering)
			 (width-of-rendered-icon icon-rendering)
			 (height-of-rendered-icon icon-rendering)
			 (computed-values-plist icon-rendering))))

		 (unless (lookup-postscript-index-for-object line-drawing-for-printing)
		   (postscript-emit-composite-object-definition
		     line-drawing-for-printing
		     #w"{}"
		     'postscript-emit-line-drawing)))
	       (postscript-emit-composite-object-definition
		 icon-rendering
		 #w"{}"
		 'postscript-emit-icon-rendering-inner)))))

(defun postscript-emit-icon-rendering-inner (icon-rendering)
  (let ((x-scale-of-rendering (x-scale-of-rendering icon-rendering))
	(y-scale-of-rendering (y-scale-of-rendering icon-rendering))
	(width (width-of-rendered-icon icon-rendering))
	(height (height-of-rendered-icon icon-rendering))
	(rotation-info					    ; list of (reflection clockwise-rotation).
	  (or
	    (assq (reflection-and-rotation-of-rendering icon-rendering)
		  '((nil           0 0)  ;; Where are the keys of this list documented? ??
		    (normal        0 0)	;; Added. -fmw  7Jun93
		    (clockwise-90  0 90)
		    (clockwise-180 0 180)
		    (clockwise-270 0 270)
		    (reflected               1 0)
		    (reflected-clockwise-90  1 -90)
		    (reflected-clockwise-180 1 -180)
		    (reflected-clockwise-270 1 -270)))
	    #-development
	    '(nil 0 0)
	    )))
    (postscript-emit-line-break)
    #+development
    (unless rotation-info
      (cerror "Assume no reflection and no rotation" "Unknown reflection-and-rotation type: ~S"
	      (reflection-and-rotation-of-rendering icon-rendering))
      (setq rotation-info '(nil 0 0)))
    (when (or (/=f x-scale-of-rendering (normalized-scale))
	      (/=f y-scale-of-rendering (normalized-scale))
	      (first rotation-info))
      (pformat "~% ~D ~D " width height)
      (pformat "~D ~D " x-scale-of-rendering y-scale-of-rendering)
      (pformat "~D ~D" (second rotation-info) (third rotation-info))
      (postscript-emit-operator 'set-icon-scale-and-rotation))

    (pformat
      "~% g~D"
      (lookup-postscript-index-for-object	
	(look-up-line-drawing-for-printing
	  (line-drawing-description-for-rendering? icon-rendering)
	  (width-of-rendered-icon icon-rendering)
	  (height-of-rendered-icon icon-rendering)
	  (computed-values-plist icon-rendering))))))




;;; The function `postscript-emit-line-drawing' emits the postscript to render
;;; the given line drawing.  This code becomes the body of a procedure which
;;; is the icon-rendering.  The procedure is run with the variable
;;; list-of-color-differences bound to the list of color values, one for each
;;; layer of the icon, if polychrome-header? is T.  Otherwise, we should
;;; draw in whatever the current color is.

(defun postscript-emit-line-drawing (line-drawing-for-printing)
  (let* ((line-drawing (line-drawing-description-for-printing line-drawing-for-printing))
	 (width (width-of-line-drawing-for-printing line-drawing-for-printing))
	 (height (height-of-line-drawing-for-printing line-drawing-for-printing))
	 (variable-overrides
	   (computed-values-plist-for-printing line-drawing-for-printing))
	 (polychrome-header?
	   (get-polychrome-header-if-any line-drawing))
	 (icon-color-pattern
	   (or (rest polychrome-header?)
	       '((foreground . foreground))))
	 (printing-icon-current-region-index?
	   nil)
	 (line-drawing-description-following-header
	   (if polychrome-header?
	       (cdr line-drawing)
	       line-drawing)))
    (paint-one-bitmap-for-icon-on-scratchpad-raster
      icon-color-pattern
      line-drawing-description-following-header
      width ; 10000 10000
      height
      (normalized-scale) (normalized-scale)
      (map-color-or-metacolor-to-color-value 'foreground)
      nil
      variable-overrides
      width height
      nil)))				; stipple feature not yet implemented!



;;; `Graph-rendering' is done in a manner directly analogous to icon rendering.  We do not
;;; bother to install the graph line drawing in the object mapping table since it is never
;;; refered to more than this once (and since the all chart line drawings are eq).

;;; Graph renderings can be refered to multiple times due to pagination, and due to
;;; update-ring-raster-for-graph-given-color-values.  We key the graph rendering in the
;;; object mapping by the graph object being rendered, not by the rendering structure
;;; (which may be recycled during printing).

;;;   `postscript-emit-graph-rendering-inner' emits the body of the graph rendering.
;;;   `postscript-emit-graph-line-drawing' emits the body of the routine to draw the graph.
;;;   `postscript-emit-graph-rendering' glues it all together.

(defvar current-graph-rendering-embedded-icons)

(defun postscript-emit-graph-rendering (graph-rendering)
  (let ((graph-rendering-index
	  (or 
	    (getf postscript-object-mapping-for-graph-renderings
		  (corresponding-graph-grid-or-chart? graph-rendering))
	    (let* ((current-graph-rendering-embedded-icons nil)
		   (postscript-current-graph-line-drawing-index
		     (prog1
			 (postscript-emit-composite-object-definition 
			   (line-drawing-description-for-graph-rendering?
			     graph-rendering)
			   #w"{}"
			   'postscript-emit-graph-line-drawing)
		       (postscript-emit-graph-rendering-embedded-icons))))
	      (let ((index 
		      (postscript-emit-composite-object-definition 
			graph-rendering
			#w"{}"
			'postscript-emit-graph-rendering-inner)))
		(printing-push 
		  index 
		  postscript-object-mapping-for-graph-renderings)
		(printing-push
		  (corresponding-graph-grid-or-chart? graph-rendering)
		  postscript-object-mapping-for-graph-renderings)
		index)))))
    ;; Now put another layer into the call tree that will offset
    ;; the rendering to graph-rendering-erase-date-line
    (pformat " /g~Da{g~D" graph-rendering-index graph-rendering-index)
    (postscript-emit-operator 'cleanup-after-graph-rendering)
    (pformat "} def /g~Da" graph-rendering-index)))

(defun postscript-emit-graph-line-drawing (graph-line-drawing)
  (paint-graph-on-scratchpad-raster
    t ; first-time?
    1      
    graph-line-drawing
    10000 10000  ; width & height
    (normalized-scale) (normalized-scale)))

(defun postscript-emit-graph-rendering-embedded-icons ()
  (loop for triple in current-graph-rendering-embedded-icons
	as (index . color-value&line-drawing-description)
	= triple
	do
    (emit-embedded-icon-layer-definition
      index color-value&line-drawing-description)
    (reclaim-printing-list triple)
	finally
	  (reclaim-printing-list
	    current-graph-rendering-embedded-icons)))

(defun postscript-emit-graph-rendering-inner (graph-rendering)
  (declare (ignore graph-rendering))
  (pformat "~% g~D" postscript-current-graph-line-drawing-index))






;;;; Kanji and Text Handling Substrate



;;; We assume only a Level One Postscript interpreter.  To support Kanji Fonts we
;;; download those characters that are needed in this print job.  We create some
;;; number of fonts, each with 250 characters, until we have enough total
;;; characters.  These fonts are emitted into the output stream during pass one
;;; of the printing.

;;; Vanilla text is placed on the paper using either add-from-line-of-text-to-current-window,
;;; or paint-from-line-of-text-to-current-scratchpad-raster.  Text that contains Kanji
;;; is placed on the paper using these the two routines kanji-add-from-line-of-text-to-current-window
;;; or kanji-paint-from-line-of-text-to-current-scratchpad-raster.  These latter two expect
;;; the text to be encoded.

;;; Kanji text strings are encoded with a single escape character prefixing every
;;; kanji character.  Unescaped characters are in the font given in the font map.
;;; The escape character is followed by two bytes.  The first byte indicates which
;;; kanji microfont to use, the second byte indicates the character within that
;;; kanji microfont to use.  The structure of kanji microfonts is documented in
;;; the module PS-HEADER.

;;; "Kanji" refers to all non-Latin characters, e.g., those that are encoded in
;;; slavic14, slavic18, slavic24, kanji16, kanji24, and, e.g., those NOT encoded
;;; in the ab fonts HM14, HM18, HM24.  Cyrillic characters are mostly handled
;;; the same as Japanese and Korean character, except that they are pulled out
;;; of a different AB font (one of the slavic fonts).  The cyrillic characters
;;; end up being defined in one of the "Kanji microfonts", so to the PostScript
;;; code they do not look to be of any different than the Korean and Jananese
;;; characters fonts.




;;; `Number-of-kanji-characters-per-microfont', a parameter, is usually
;;; bound to 250, but sometimes when debugging you might want to set it
;;; lower to force multiple microfonts to be created.

(defparameter number-of-kanji-characters-per-microfont 256) ; 250 => 256 for Latin-1 (MHD 9/10/96)


;;; If the parameter `use-substitute-for-non-latin-text-p' is true, then
;;; substitute-character-for-non-latin-text, which is by default the character
;;; # and must always be an ASCII character, is used in place of non-Latin
;;; characters in text.  This is initially to be used in development for debugging,
;;; but it may become user visible in some form later. (MHD 1/18/99)

(defparameter use-substitute-for-non-latin-text-p nil)
(defparameter substitute-character-for-non-latin-text #.%\#)  ; #u0023 = #





;;; `Printing-pass-1-define-for-text' is called during pass one of printing for
;;; all text that will appear in the print job.  It takes a font-map and a
;;; text-line.  These are used to define the necessary fonts.  In the case of
;;; Kanji the bitmaps are emitted to create the characters.

(defun printing-pass-1-define-for-text (font-map text-line)
  (let ((font-used (first font-map)))

    ;; Define this font if necessary
    (unless (memq font-used fonts-used-in-print-job)
      (printing-push font-used fonts-used-in-print-job))

    ;; Add Kanji characters, if we find any.
    (unless use-substitute-for-non-latin-text-p
      (loop with non-latin-used-so-far? = nil
	  with character-index = 0
	  with length = (lengthw text-line)
	  while (<f character-index length)
	  as character
	     = (read-character-from-text-string text-line character-index)
	  as code = (wide-character-code character)
	  when (and (or (=f 0 (map-unicode-to-ab-latin-font-code-or-zero code))
			(gensym-non-adobe-standard-encoded-latin-code-p code))
		    (or (eq (classify-character-for-text-line-drawing character)
			    'mark)
			(eq (classify-character-for-text-line-drawing character)
			    'non-spacing-mark)))
	    ;; Generalized and simplified matters so this always applies in the
	    ;; non-Latin case, and also even for some obscure Latin characters.
	    ;; (MHD 4/9/99)
	    do (setq non-latin-used-so-far? t)
	       (note-use-of-kanji-character font-used character)
	  finally
	    (when non-latin-used-so-far?
	      (printing-pushnew font-used fonts-needing-corresponding-kanji-font))))))



;;; `Note-use-of-kanji-character' is called for every Kanji character
;;; encountered during pass 1 of printing.  Accumulates the set of such
;;; characters into the values of the plist kanji-fonts-used-in-print-job.
;;;
;;; Here, non-latin-wide-character should be a wide character for a non-latin
;;; character, i.e., one that is stored in the associated "kanji font" as
;;; opposed to the base font.

(defun note-use-of-kanji-character (base-font non-latin-wide-character)
  (let ((kanji-code (wide-character-code non-latin-wide-character)))
    ;; Now index non-Latin by Unicode, but keep traditional variable name kanji-code
    ;; to simplify diffs (and for tradition, I guess). (MHD 4/9/99)
    ;; Note use of font, if not there already.
    (unless (getf kanji-fonts-used-in-print-job base-font)
      (setf kanji-fonts-used-in-print-job
	    (printing-cons
	      base-font
	      (printing-cons
		nil
		kanji-fonts-used-in-print-job))))
    (let* ((code 0)
	   (tail-of-font-list nil)
	   (printing-font-code?
	     (loop for code-and-assignment-used-in-kanji-font-tail
		   on (getf kanji-fonts-used-in-print-job base-font)
		   as code-and-assignment-used-in-kanji-font
		      = (car code-and-assignment-used-in-kanji-font-tail)
		   do
	       (cond ((eql (car code-and-assignment-used-in-kanji-font) kanji-code)
		      (return code))
		     (t
		      (setf tail-of-font-list
			    code-and-assignment-used-in-kanji-font-tail)
		      (incff code))))))
      (cond
	(printing-font-code?
	 printing-font-code?)
	(tail-of-font-list
	 (multiple-value-bind (microfont-number char-code)
	     (floorf code number-of-kanji-characters-per-microfont)
	   (setq code (logiorf (ashf microfont-number 10) char-code)))
	 (setf (cdr tail-of-font-list)
	       (printing-list (printing-cons kanji-code code)))
	 code)
	(t
	 (let ((tail (memq base-font kanji-fonts-used-in-print-job)))
	   (setf (cadr tail) (printing-list (printing-cons kanji-code 0)))
	   0))))))


;;; Convert-text-width-to-postscript-scaleable-points ... returns a fixnum, in units
;;; of 1/1000 point.

(defun convert-text-width-to-postscript-scaleable-points (text-width point-size)
  (with-temporary-gensym-float-creation  scaling-character-widths
    (round  ; is there no "rounde"?! (MHD)
     (*e 1000.0 (coerce-to-gensym-float text-width))
     (*e 
      (coerce-to-gensym-float point-size)
      (coerce-to-gensym-float scaling-factor-for-text-widths)))))

;; Used below for roman fonts, and further below for Kanji fonts.


;; OBSOLETE: we now define an encoding 1:1 with G2's encoding. (MHD 9/10/96)
;; ;;; Compute at compile time an array mapping ps-code --> g2-code.

#+OBSOLETE
(defmacro compute-postscript-to-g2-character-code-mappings ()
  `',(make-array
      256 :initial-contents
      (loop for ps-code below 256
	    as g2-code =
	    (cond ((<=f #o40 ps-code #o176)
		   ps-code)
		  (t
		   (let* ((adobe-name?
			    (svref gensym-postscript-font-encoding-vector
				   ps-code))
			  (special-character?
			    (loop for info in special-character-alist
				  as key = (symbol-name (sixth info))
				  when (string= key adobe-name?)
				    return info)))
		     (if special-character?
			 (second special-character?)
			 ps-code))))
	    collect g2-code)))

#+OBSOLETE
(defparameter postscript-to-g2-character-code-mappings (compute-postscript-to-g2-character-code-mappings))

(defun g2-character-code-for-postscript-character-code (ps-code)
  #+obsolete
  (svref postscript-to-g2-character-code-mappings ps-code)
  #-obsolete
  ps-code
  )


;;; Emit a Postscript array of character widths, in the same order as the
;;; Postscript encodings array, where widths are in 1000ths of a point.
;;; This array is plopped directly into the Metrics slot of G2 fonts.

(defun postscript-emit-ab-font-character-widths (font-name)
  (let* ((font (ab-font font-name))
	 (character-description-table (ab-font-character-description-table font))
	 (font-size (ab-font-size font)))
    (pformat "[")
    ;; We want the array to always have 256 elements.
    (loop for i below 256
	  as g2-character-code = (g2-character-code-for-postscript-character-code i)
	  as character-description? = (get-non-kanji-character-description-if-any
				       g2-character-code
				       character-description-table)
	  as width = (text-width-for-character character-description? font)
	  as points = (convert-text-width-to-postscript-scaleable-points width font-size)
	  doing
      (pformat "~d" points)
      (cond ((and (>f i 0) (=f (modf i 16) 0))
	     (pformat "~%"))
	    ((<f i 255)
	     (pformat " "))))
    (pformat "]")))

;; Although this array could be computed at compile-time, we want to allow for
;; character widths changing at run-time (for example, if a new font is
;; dynamically loaded).


	    

;;; `Emit-print-job-specific-font-definitions' is called in the epilog of pass 1 of
;;; printing.  It emits definitions for each of the built in fonts used in the
;;; print job.  It emits all the junk necessary to emit the Kanji fonts.

(defun emit-print-job-specific-font-definitions ()
  ;; For each nonkanji ab-font we utilized emit code to define the font.
  (loop initially
	  (pformat "~%% Define Fonts.~%")
	for font in fonts-used-in-print-job
	as ab-font = (ab-font font) 
	as ab-font-size = (ab-font-size ab-font)
	as ab-font-type = (ab-font-type ab-font)
	do
    (postscript-emit-symbol font)
    (postscript-emit-integer ab-font-size)
    (cond
      ((eql font 'blob18)
       (postscript-emit-operator 'define-blob-font))
      ((eq 'roman ab-font-type)

       ;;       (postscript-emit-integer (ab-font-unique-id-for-postscript ab-font))
       (postscript-emit-ab-font-character-widths font)

       ;; Assume that the font is based on Helvetica.
       (postscript-emit-operator 'define-helvetica-font))
      (T
       (postscript-emit-operator 'define-unknown-font))))

  ;; When we have Kanji fonts to do, get to work on them.
  (when kanji-fonts-used-in-print-job
    ;; Define the encoding vector for kanji fonts
    ;; (The following loop uses number-of-kanji-characters-per-microfont;
    ;; the previous version hardwired 250, the usual value. (MHD 6/5/93))
    (loop for character-code
	  from 0 below number-of-kanji-characters-per-microfont
	  initially (pformat "~%/microfont-encoding-vector[")
	  when (=f (modf character-code 24) 0)
	    do (pformat "~%")
	  do (pformat "/c~D" character-code)
	  finally (pformat "]def"))
    ;; Create kanji-dictionary, of appropriate size.
    (let ((kanji-dictionary-size
	    (+f
	      ;; Space for the locals of all the routines
	      ;; that build these things.
	      30
	      ;; One entry for each kanji font vector
	      (truncatef (length kanji-fonts-used-in-print-job) 2)
	      ;; One entry for each micro font.
	      (loop for (nil kanji-codes) on kanji-fonts-used-in-print-job by #'cddr
		    sum (ceiling (length kanji-codes) number-of-kanji-characters-per-microfont))
	      ;; One entry for each corresponding kanji font vector
	      ;; One entry for each correspondence.
	      (length fonts-needing-corresponding-kanji-font))))
      (pformat "~%/kanji-dictionary ~D dict def" kanji-dictionary-size))

    ;; First define the kanji font vectors and micro fonts.
    (loop initially (pformat "~%% Setup Kanji Fonts")
		    (pformat "~%kanji-dictionary begin")
	  finally (pformat "~%end")
	  for (base-font kanji-codes-etc-used) on kanji-fonts-used-in-print-job by #'cddr
	  as ab-font = (ab-font base-font)
	  as corresponding-font-name = (tformat-text-string "EXTRA~a" base-font)
	  do
      (loop with microfont-number = 0
	    initially 
	      #+development  ; --mhd
	      (assert (>f number-of-kanji-characters-per-microfont 0))
	      (pformat "~%~(/~A~) begin-kanji-font" corresponding-font-name)
	      (pformat "~%~(  /k~D ~D begin-kanji-microfont" microfont-number microfont-number)
	    finally 
	      (pformat "~%~(  /k~D ~D end-kanji-microfont" microfont-number microfont-number)
	      (pformat "~%~(/~A~) end-kanji-font" corresponding-font-name)
	    for code-and-assignment-used-in-kanji-font in kanji-codes-etc-used
	    as (kanji-code) = code-and-assignment-used-in-kanji-font
	    ;; rearranged the logic around this slightly -- there had
	    ;; been a fencepost bug at wraparound time.  This code now
	    ;; should be correct. (MHD 6/5/93)
	    as count from 0
	    as microfont-character-code
	       = (modf count number-of-kanji-characters-per-microfont)
	    do
	(postscript-emit-kanji-character-description
	  kanji-code
	  ab-font
	  microfont-character-code)
	(pformat "  % ~D" kanji-code)
	(when (=f microfont-character-code
		  (-f number-of-kanji-characters-per-microfont 1))
	  (pformat "~%  /k~D ~D end-kanji-microfont" microfont-number microfont-number)
	  (incff microfont-number)
	  (pformat "~%  /k~D ~D begin-kanji-microfont" microfont-number microfont-number))))
    ;; Now define the corresponding font vectors and font correspondences
    (loop initially 
	    (pformat "~%/corresponding-kanji-font ~D dict def" (length fonts-needing-corresponding-kanji-font))
	  for font in fonts-needing-corresponding-kanji-font
	  as corresponding-font-name = (tformat-text-string "EXTRA~a" font)
	  do
      (pformat "~%~(/~S /~A~)" font corresponding-font-name)
      (pformat " ~D ~D def-kanji-correspondence"
	       (ab-font-size (ab-font font))
	       (or (cdr			; this will be wrong for Russian; fix later!
		     (corresponding-kanji-font-name-and-magnification font))
		   256)))))





;;; `Round-up-to-multiple-of-8' returns the integer that is greater than
;;; or equal to the fixnum n and is a multiple of 8.

(defmacro round-up-to-multiple-of-8 (n)
  `(logandc2f (+f ,n 7) 7))

;; Should move to a more primitive module! (MHD)




;;; `Postscript-emit-kanji-character-description' ... Character-description may
;;; not be nil.  Note that, although a character description for a given code
;;; may not be present (may be nil) in a given font, you can always find the
;;; character description for the code 0, which is the code reserved for
;;; "the missing character", and this should be supplied in such cases.
;;;
;;; AB-font here is the name of a the base font.
;;;
;;; Note that [as of the release pending 4/9/99], "Kanji-code" here refers to a
;;; unicode, but is called kanji-code for historical reasons. (MHD 4/9/99)

(defun postscript-emit-kanji-character-description
    (kanji-code base-ab-font micro-font-character-code)
  (let* ((ab-font-name (ab-font-name base-ab-font))
	 (corresponding-font-name-and-magnification?
	   (if (/=f (map-unicode-to-ab-latin-font-code-or-zero
		      kanji-code)		; just handles non-adobe chars
		    0)
	       nil
	       (if (cyrillic-unicode-p kanji-code)
		   (get-corresponding-cyrillic-font-name-and-magnification ab-font-name)
		   (if (hebrew-unicode-p kanji-code)
		       (get-corresponding-hebrew-font-name-and-magnification ab-font-name)
		       (if (thai-unicode-p kanji-code)
			   (get-corresponding-thai-font-name-and-magnification ab-font-name)
			   (get-corresponding-kanji-font-name-and-magnification ab-font-name))))))
	 (ab-font
	   (or (if corresponding-font-name-and-magnification?
		   (ab-font (first corresponding-font-name-and-magnification?)))
	       base-ab-font)))
    (multiple-value-bind
	(character-bitmap temporary-p
			  bounding-box-x-offset bounding-box-y-offset
			  bounding-box-width bounding-box-height
			  character-set-width text-width-for-character)
	(get-character-bitmap-of-font-character kanji-code ab-font)
      (declare (ignore text-width-for-character))	; some precision lost!
      (pformat "~%   /c~D" micro-font-character-code)
      (pformat " ~D" character-set-width)
      (pformat " ~D ~D"
	       (round-up-to-multiple-of-8 bounding-box-width)
	       (round-up-to-multiple-of-8 bounding-box-height))
      (pformat " ~D ~D"
	       bounding-box-x-offset
	       (+f bounding-box-height
		   bounding-box-y-offset))
      (let ((postscript-bitmap-encoding-string
	      (twith-output-to-text-string
		(twrite-postscript-bitmap-encoding
		  character-bitmap
		  bounding-box-width
		  bounding-box-height))))
	(pformat "~a" postscript-bitmap-encoding-string)
	(reclaim-text-string postscript-bitmap-encoding-string))
      (pformat " def-kanji-character")
      (when temporary-p
	(reclaim-temporary-character-bitmap character-bitmap)))))

;; This no longer accepts nil so the arg was renamed character-description,
;; i.e., without the "?".  This no longer uses def-unknown-kanji-character,
;; which didn't work anyway.  It was not saving much room in the output anyway,
;; and is only really needed for degenerate cases (usually missing fonts), and
;; so seems unworthy of optimizing.  The caller was changed to pass in the
;; missing character's character description when a character is missing.
;; (MHD 7/21/93)




;;; `Twrite-postscript-bitmap-encoding' encodes character-bitmap as a postscript
;;; hex-encoded array, emitting its characters as gensym text using twrite-char,
;;; etc.  This should be called within a twith-output-to-text-string context.

(defun twrite-postscript-bitmap-encoding
    (character-bitmap bounding-box-width bounding-box-height)
  (loop with width = (round-up-to-multiple-of-8 bounding-box-width)
	with height = (round-up-to-multiple-of-8 bounding-box-height)
	with characters-per-row = (truncatef (*f 8 (ceiling width 8)) 4)
	with character-in-hex = (obtain-simple-text-string 
				  (*f characters-per-row height))
	with character-index = -1
	for row from 0 below height
	do (loop for column from 0 below width by 4
		 do (setf (charw character-in-hex (incf character-index))
			  (charw #w"0123456789abcdef"
				 (macrolet ((ref (cbm x y)
					      `(if (and (<f ,x bounding-box-width)
							(<f ,y bounding-box-height))
						   (character-bitmap-value ,cbm ,x ,y)
						   0))
					    (g (x y)
					      `(ashf (ref
						       character-bitmap
						       (+f column ,x)
						       row)
						     ,y)))
				   (+f
				     (g 0 3)
				     (g 1 2)
				     (g 2 1)
				     (g 3 0))))))
	finally
	  (loop with i = -1
		initially (tformat "<")
		finally (tformat ">")
		repeat height
		do
	    (loop initially (unless (minusp i) (tformat ""))
		  for j from 0 below characters-per-row
		  do
	      (tformat "~C" (charw character-in-hex (incf i)))))
	  (reclaim-simple-text-string character-in-hex)))



  ;; 'Fill-ones-into-postscript-character-image' takes a the hex string into which we are
;; accumulating the description of a single character's bitmap.  Given three fixnums
;; (offset, start, and end); it modifies the string so that a contigous chunk of one bits
;; appears from offset+start to offset+end.

;(defun fill-ones-into-postscript-character-image (string offset start end)
;  (loop with first-character = (+f offset (truncatef start 4))
;	with last-character  = (+f offset (truncatef end 4))
;	with first-character-remainder = (modf start 4)
;	with last-character-remainder  = (modf end 4)
;	with useful-characters = "0123456789abcdef"
;	with useful-bits-1 = #( #B1111 #B0111 #B0011 #B0001)
;	with useful-bits-2 = #( #B1000 #B1100 #B1110 #B1111)
;	initially
;	  (cond
;	    ((=f first-character last-character)
;	     (setf (charw string first-character)
;		   (charw useful-characters
;			 (logandf (svref useful-bits-1 first-character-remainder)
;				  (svref useful-bits-2 last-character-remainder))))
;	     (return nil))
;	    (T
;	     (setf (charw string first-character)
;		   (charw useful-characters
;			 (svref useful-bits-1 first-character-remainder)))
;	     (setf (charw string last-character)
;		   (charw useful-characters
;			 (svref useful-bits-2 last-character-remainder)))
;	     ))
;	  for i from (1+f first-character) below last-character
;	do
;    (print i)
;    (setf (charw string i) #.%\F)))

;; This sure is clever, it treats the first and last character modified
;; specially and then just loops to fill #.%\F into the characters between.
;; Another case arises when the first and last character are the same.






;;;; Substrate For The Postscript Output Stream




;;; All postscript output is emitted thru a small number of routines.
;;; These routines are organized into layers.

;;; The most primitive layer of these routines emit text, assuring that lines do not get
;;; too long.  The second layer provides routines that emit various types of data, eg.
;;; points, rectangles, colors, etc.  The last layer consists of one routine for each type
;;; of ICP message.

;;; This section contains the first two layers, but first we define some foundation work
;;; to support the handling of tilde escaped characters.



;;; `Postscript-encoding-for-tilde-escape-characters' is used when printing to handle the
;;; tilde escaped characters found in text strings full of gensym characters.  It maps
;;; from the escaped character to a character encoding as defined in
;;; gensym-postscript-font-encoding-vector.  The macro
;;; `build-postscript-encoding-for-tilde-escape-characters-initial-value' creates the
;;; initial value of this array

(defmacro build-postscript-encoding-for-tilde-escape-characters-initial-value ()
  `',(concatenate'list
       (loop with encoding = (make-array (1+ #o377) :initial-element #o220)
	     with table-of-gensym-tilde-escape-characters
	       = (loop with table = (make-hash-table :test #'equal)
		       for  (tilde-quoted-char	; character-following-\~-in-gensym-character
			      nil		; roman-font-special-character-code
			      nil		; character-following-\~-in-lower-case-equivalent?
			      nil		; equivalent-unaccented-character?
			      nil		; character-or-characters-following-\~-for-input
			      adobe-name) in special-character-alist
		       ;; changed to reflect the fact that adobe-name is now a
		       ;; symbol, rather than a string. (MHD 2/10/94)
		       do (setf (gethash (symbol-name adobe-name) table)
				(char-code tilde-quoted-char))
		       finally (return table))
	     for char-code from 0 below (length gensym-postscript-font-encoding-vector)
	     as adobe-name = (svref gensym-postscript-font-encoding-vector char-code)
	     as tilde-quoted-char? = (gethash adobe-name table-of-gensym-tilde-escape-characters)
	     when tilde-quoted-char?
	       do
		 (setf (svref encoding tilde-quoted-char?) char-code)
	     finally
	       (return encoding))))

(defparameter postscript-encoding-for-tilde-escape-characters
	      (make-array (1+ #o377) 
		    :initial-contents
		    (build-postscript-encoding-for-tilde-escape-characters-initial-value)))


(defun postscript-emit-atom (atom)
  (pformat " ~A" atom))

(defun postscript-emit-line-break ()
  (pformat "~%"))


(defun lookup-current-postscript-encoding-for-kanji (kanji-font kanji-code)
  (loop for (cantidate-kanji-code . kanji-microfont-encoding)
	in (getf kanji-fonts-used-in-print-job kanji-font)
	when (eql cantidate-kanji-code kanji-code)
	  do
	    (return (values (ashf kanji-microfont-encoding -10)
			    (logandf #x1FF kanji-microfont-encoding)))))

;; Note that the number here must match the other call to ASH above.


(defun postscript-emit-text-string (font text-string)
  (loop with non-latin-used-so-far? = nil
	with wide-character
	with wide-character-code
	with character-or-character-code
	with escape-character?
	with font-code
	with character-index = 0
	with length = (text-string-length text-string)
	initially (pformat "~%(")
	for non-adobe-latin-p = nil	; may be (rarely) setq'd below
	while (<f character-index length)
	do

    (progn
      ;; Similar shortcut as in FONTS -- try handling all/more of Unicode some
      ;; day!  (MHD 3/5/96)
      
      (setq wide-character 
            ((lambda (character)
               (if (or 
                   (eq character (line-feed-code))
                   (eq character (return-code))) 
                 (unicode-line-separator) 
                 character))
             (read-character-from-text-string text-string character-index)))
      (setq wide-character-code (wide-character-code wide-character)))

    (cond
      ((or (and (/=f (setq font-code
			   (map-unicode-to-ab-latin-font-code-or-zero
			    wide-character-code))
		     0)
		;; These won't be handled in a PostScript printer: (e.g., U+0170,
		;; font code 20, named LATIN CAPITAL LETTER U WITH DOUBLE ACUTE)
		;; (MHD 5/14/99)
		(not
		 (setq non-adobe-latin-p
		       (gensym-non-adobe-standard-encoded-latin-code-p
			wide-character-code))))
	   (if use-substitute-for-non-latin-text-p
	       (setq font-code
		     (map-unicode-to-ab-latin-font-code-or-zero
		      (wide-character-code substitute-character-for-non-latin-text)))))
       ;; this clause makes it be the case that we never get into the ~ or otherwise
       ;; case below:
       (postscript-emit-string-character-code font-code))
      (non-adobe-latin-p
       (setq non-latin-used-so-far? t)	; misnomer in this case!
       (multiple-value-bind (kanji-postscript-font-number kanji-postscript-character-code)
	   (lookup-current-postscript-encoding-for-kanji font wide-character-code)
	 (postscript-emit-string-character-code #o33)
	 (postscript-emit-string-character-code kanji-postscript-font-number)
	 (postscript-emit-string-character-code kanji-postscript-character-code)))      
      (t

       (multiple-value-setq (character-or-character-code escape-character?)
	 (unicode-wide-character-to-gensym-pair-for-fonts
	   wide-character))
       
       (case escape-character?
	 ;; Translate the G2 escape characters.
	 (#\~
	  ;; changed to use code-emiting function below (see other use/comment) (MHD 6/5/93)
	  (postscript-emit-string-character-code
	    (svref postscript-encoding-for-tilde-escape-characters
		   (char-code character-or-character-code))))
	 (#\\
	  (setq non-latin-used-so-far? t)
	  (multiple-value-bind (kanji-postscript-font-number kanji-postscript-character-code)
	      (lookup-current-postscript-encoding-for-kanji
		font wide-character-code) ; (MHD 4/9/99)
	    
	    ;; these have been changed to use the new code emiting function below; it
	    ;; feels safer to leave them as codes before translating them into codes,
	    ;; rather than passing them through char-code when they're known to
	    ;; not be simple Common Lisp characters. (MHD 6/5/93)
	    ;;
	    ;; Consider writing these out with slightly fewer characters,
	    ;; exploiting the fact that 1, 2, or 3 digits may follow
	    ;; the \, to save a few bytes.  E.g.,  (\33\1\ddd) for ESCAPE,
	    ;; 1, three octal digits.  The last one has to be three digits,
	    ;; since it is not known if another octal digit might follow,
	    ;; thus confusing the reader.  OR you could do even better
	    ;; by having a 1-character lookahead (aound this whole loop),
	    ;; and then only write as many digits as needed in the third
	    ;; position as well.  Just adds some complexity. (MHD 6/5/93)
	    (postscript-emit-string-character-code #o33)
	    (postscript-emit-string-character-code kanji-postscript-font-number)
	    (postscript-emit-string-character-code kanji-postscript-character-code)))
	 (#\@
	  ;; TBD
	  )
	 (otherwise
	  (postscript-emit-string-character character-or-character-code)))))

    
	finally
	  (pformat ")")
	  (return non-latin-used-so-far?)))



;;; The function `postscript-emit-string-character' emits a Common Lisp
;;; string character to the printing-stream, quoting PostScript delimiters
;;; as needed.

(defun postscript-emit-string-character (c)
  (let ((char-code (char-code c))
	c2)
    (cond
      ((member c '( #\( #\) #\\ ))                 ; memq => member (eq not valid for chars!) (MHD 6/5/93)
       (postscript-emit-ascii-character #\\)
       (postscript-emit-ascii-character c))
      ((setq c2 (getf '(#.char-linefeed  #\n 
			#.char-return    #\r
			#.char-tab       #\t
			#.char-backspace #\b
			#.char-page      #\f) 
		      c))
       (postscript-emit-ascii-character #\\)
       (postscript-emit-ascii-character c2))
      ((<=f #o40 char-code #o176)
       (postscript-emit-ascii-character c))
      (t
       (postscript-emit-ascii-character #\\)
       (postscript-emit-octal-digit char-code #o100)))))

;; The contract only allows "string characters" now, but the code retains its
;; historical all-purposefullness.  (But don't use it this way.  In particular,
;; it's not clean to give a "byte" that happens be be, say, 10 the "linefeed"
;; semantics.  -- see postscript-emit-string-character-code.) (MHD 6/5/93)



;;; The function `postscript-emit-string-character-code' emits char-code, which
;;; may be any 8-bit integer, to be encoded into a string.

(defun postscript-emit-string-character-code (char-code)
  (cond
    ((eq char-code nil))
    ((<=f #o40 char-code #o176)
     (postscript-emit-string-character (code-char char-code)))
    ((<=f 0 char-code 255)
     (postscript-emit-ascii-character #\\)
     (postscript-emit-octal-digit char-code #o100))
    (t
     #+development
     (cerror "Proceed (use '?')" "~d is an illegal character code here." char-code)
     (postscript-emit-ascii-character #\?))))



(defun postscript-emit-octal-digit (small-octal-number octal-decade)
  (cond
    ((=f octal-decade 0)
     )
    ((<f small-octal-number octal-decade)
     (postscript-emit-ascii-string "0")
     (postscript-emit-octal-digit small-octal-number (truncatef octal-decade #o10)))
    (t
     (multiple-value-bind (quotient remainder)
	 (floorf small-octal-number #o10)
       (postscript-emit-octal-digit quotient (truncatef octal-decade #o10))
       (pformat "~C" (digit-charw remainder 8))))))



(defconstant write-hex-table #w"0123456789abcdef")

(defmacro write-hex-to-string (value number-of-nibbles string &optional (offset-in-string 0))
  (unless (symbolp value)
    (error "The first argument to write-hex-to-string, VALUE, must be a symbol."))
  `(progn
     ,@(loop for i from (1- number-of-nibbles) downto 0
	     collect `(setf (scharw ,string
				    (+f ,offset-in-string ,i))
			    (scharw  write-hex-table (logandf ,value 15)))
	     unless (zerop i)
	       collect `(setf ,value (ash ,value -4)))))



(defparameter postscript-emit-hex-byte-string (make-string 2))
    
(def-substitution-macro postscript-emit-hex-byte (byte)
  (write-hex-to-string byte 2 postscript-emit-hex-byte-string)
  (g2-stream-write-string postscript-emit-hex-byte-string printing-stream))



;;; The substitution-macro `postscript-emit-packed-rgb' emits the packed rgb
;;; value as 3 hex bytes.

(defparameter postscript-emit-rgb-string (make-string 6))

(def-substitution-macro postscript-emit-packed-rgb (rgb)
  (write-hex-to-string rgb 6 postscript-emit-rgb-string)
  (g2-stream-write-string postscript-emit-rgb-string printing-stream))




(defun postscript-emit-managed-float (managed-float)
  (pformat " ~D" (managed-float-value managed-float))) 

(defun postscript-emit-symbol (symbol)
  (pformat "~( /~a~)" symbol))


(defun postscript-emit-rectangle (left top right bottom)
  (postscript-emit-atom left)
  (postscript-emit-atom top)
  (postscript-emit-atom right)
  (postscript-emit-atom bottom))


(defun postscript-emit-color-value (color-value)
  (postscript-emit-atom color-value))


(defvar adding-from-graph-rendering-p nil)

;;; The function `postscript-emit-scratchpad-color' writes during pass 1,
;;; the postscript expression, which when evaluated during printing, returns
;;; the desired color value for the current icon region.  If the icon has
;;; multiple regions (printing-icon-current-region-index? non-NIL), then we
;;; want the color which is the i-th element of the color list.  If the icon
;;; has only one region, then we simply want the current color, set to
;;; color-value by add-from-icon-rendering

(defun postscript-emit-scratchpad-color (color-value)
  ;; During pass one, color-value is always just black for icon renderings.
  (cond
    (printing-icon-current-region-index?
     (postscript-emit-atom printing-icon-current-region-index?)
     (postscript-emit-operator 'fetch-from-color-list))

    (adding-from-graph-rendering-p
     ;; For some reason, graphs want the literal color value here, not the name
     ;; 'color-value.  This was attempting to use (=f printing-pass-number 2)
     ;; as a test for add-from-graph-rendering, not noticing that
     ;; add-from-icon-rendering binds it too. Foo.
     (postscript-emit-atom color-value))
    (t
     (postscript-emit-operator 'color-value))))

;; This depends on the arguments named in add-from-icon-rendering!!




(defun postscript-emit-integer (integer)
  (postscript-emit-atom integer))

(defun postscript-emit-color-difference (color-difference)
  (postscript-emit-atom 
    (if (color-difference-is-transparent-p color-difference)
	postscript-transparent-color-value
	(color-difference color-difference current-background-color-value))))

(defun postscript-emit-scalling (x-scale y-scale)
  (postscript-emit-atom x-scale)
  (postscript-emit-atom y-scale))

(defun postscript-emit-point (x y)
  (postscript-emit-atom x)
  (postscript-emit-atom y))

(defun postscript-emit-boolean (boolean)
  (postscript-emit-atom (if boolean 1 0))) 

(defun postscript-emit-unsigned-integer (unsigned-integer)
  #+development (assert (integerp unsigned-integer))
  (postscript-emit-atom unsigned-integer))

(defun postscript-emit-font-map (font-map)
  (let ((postscript-emit-composite-object-without-name t))
    (postscript-emit-composite-object-definition
      font-map
      #w"[]"
      'postscript-emit-composite-object)))

(defun postscript-emit-list-of-colors (list-of-colors use-differences-p)
  (let ((postscript-emit-composite-object-without-name t)
	(postscript-emit-integers-as-color-differences use-differences-p))
    (postscript-emit-composite-object-definition
      list-of-colors
      #w"[]"
      'postscript-emit-composite-object)))

(defun postscript-emit-color-map (color-map)  ;; Not to be confused with emit-printing-color-map.
  (declare (ignore color-map))
  (error "Unimplemented"))

(defun postscript-emit-gensym-window (window)
  (declare (ignore window))
  (error "Unimplemented"))



;;; `make-printing-color-description-plist' creates the equivalent plist which
;;; is used when we create the window.  It is a tree of new gensym conses.

(defun make-printing-color-description-plist ()
  (nconc
    (gensym-list
      'black (gensym-list 0)
      'white (gensym-list 1))

    (loop with last-color-number = 1
	  for (color) in standard-gensym-color-alist
	  unless (memq color '(black white))
	    collect color using gensym-cons and
	    collect (gensym-list (incff last-color-number))
	      using gensym-cons)))

;; The window setup functions now want gensym conses.

(defun make-true-color-description-plist ()
  (loop for (color r g b) in standard-gensym-color-alist
	collect color using gensym-cons
	collect (gensym-list (rgb r g b)) using gensym-cons))

(defun make-gray-true-color-description-plist ()
  (loop for (color r g b) in standard-gensym-color-alist
	collect color using gensym-cons
	collect (gensym-list (rgb (rgb2gray r g b) (rgb2gray r g b) (rgb2gray r g b))) using gensym-cons))

;;; `Emit-printing-color-map' inserts a color map into the job header.

(defun emit-printing-color-map ()
  (loop initially (pformat "~%/full-color-map[")
	finally   (pformat "~%]def")
        for color-value from 0 below (length standard-gensym-color-alist)
	for color? = (map-to-color color-value)
	for alist-entry? = (assq color? standard-gensym-color-alist)
	do
    (emit-printing-color-map-1 color-value alist-entry?))
  (let ((standard-gensym-color-alist gray-gensym-color-alist))
    (loop initially (pformat "~%/gray-color-map[")
	  finally   (pformat "~%]def")
	  for color-value from 0 below (length standard-gensym-color-alist)
	  for color? = (map-to-color color-value)
	  for alist-entry? = (assq color? standard-gensym-color-alist)
	  do
       (emit-printing-color-map-1 color-value alist-entry?))))

;;  This is O(N*N)!  See the comment after map-to-color.

(defun emit-printing-color-map-1 (index alist-entry?)
  (if alist-entry?
      (gensym-dstruct-bind ((color red green blue) alist-entry?)
	(pformat "~%[")
	(pformat "~D"  red)
	(pformat " ~D" green)
	(pformat " ~D" blue)
	(pformat "]% ~D ~(~S~)" index color))
      (pformat "~%[255 255 255]% ~D none" index)))









;;;; Printing Handlers For All ICP Messages




;;; When printing all ICP messages are dispatched through icp-printing-message-handler-array,
;;; which contains symbols.  The symbol-functions of all entries in that array are defined in
;;; this section.  All functions defined in this section are declared to be funcallable

;;; These functions fall into four broad catagories.
;;;   1. icp-messages that should never be generated when printing.
;;;   2. icp-messages happen during printing, but are ignored.
;;;   3. icp-messages that happen during printing and generate postscript.
;;;   4. other.

;;; Routines in the other catagory are handled by placing a default
;;; value for every element in the dispatch vector.  These entries would
;;; be accessed in practice if a new ICP message type were introduced
;;; and no entry made for it in this section.

;;; The first three cases the default dispatch vector entry is replaced
;;; by def-icp-message-functions.  The replacements are
;;; symbols of the form "PRINT-HANDLER-FOR-<icp-message-type>."



;;; For each ICP message type defined by def-icp-message-functions one
;;; handler is defined in this file to translate the message into
;;; postscript.  These are defined with one of two macros, i.e.
;;; `def-handler-for-printing' or `def-handler-for-inappropriate-printing'.  The
;;; second of these is provided to define handlers for ICP messages that
;;; should never be emitted when printing a workspace.

;;; For the many cases where printing wants to ignore an ICP message the
;;; body of the def-handler-for-printing will contain nothing more than
;;; declare ignore.

(defmacro def-handler-for-printing (icp-message-type argument-list &body body)
  (multiple-value-bind (declarations statements)
      (parse-body-declarations body)
    (let ((name (build-ab-symbol 'handler-for-printing icp-message-type))
	  (argument-names (loop for argument in argument-list
				collect (if (consp argument) (second argument) argument))))
      `(defun ,name ,argument-names
	 ,@declarations
	 (within-named-dynamic-extent print-spooling
	   (when (=f printing-pass-number 2)
	     ,@statements))))))


(defmacro def-handler-for-printing-in-all-passes (icp-message-type argument-list &body body)
  (multiple-value-bind (declarations statements)
      (parse-body-declarations body)
    (let ((name (build-ab-symbol 'handler-for-printing icp-message-type)))
      `(defun ,name ,argument-list
	 ,@declarations
	 (within-named-dynamic-extent print-spooling
	   ,@statements)))))


(defmacro def-handler-for-inappropriate-printing (icp-message-type argument-list)
  (let ((name (build-ab-symbol 'handler-for-printing icp-message-type)))
    `(defun ,name ,argument-list
       (declare (ignore ,@argument-list))
       #+development
       (error "Inappropriate ICP message generated when printing."))))




;;; `Default-print-handler-for-icp-messages' is the symbol used for the initial-element of
;;; the printing dispatch vector.  It would be bad if this function is ever called.
;;; Def-icp-message-type and def-icp-message-functions replace the element with a print
;;; handler for each kind of icp message.  

(defun default-print-handler-for-icp-messages (&optional a b c d e f g h i j k l m n o p)
  (declare (ignore  a b c d e f g h i j k l m n o p))
  #+development
  (error "During printing, an icp-message was generated for which no handler has been defined."))



;;; The remainder of this section was automatically generated by the function
;;; (write-draft-functions) which is commented out above.  meta-control-B
;;; meta-control-E

;;; The handler for the `i-am-alive' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing i-am-alive
				       (message-group-id	; i.e. an unsigned-integer
					 ))



;;; The handler for printing the `enlarge-corresponding-icp-object-index-space'
;;; ICP message does nothing.

(def-handler-for-printing enlarge-corresponding-icp-object-index-space
         (name-of-corresponding-icp-object-index-space ; i.e. a symbol
          new-index-limit-plus-one ; i.e. an unsigned-integer
            )
  (declare (ignore name-of-corresponding-icp-object-index-space new-index-limit-plus-one))
  ;; Ignore.
  )



(def-handler-for-printing nop
         (number-of-icp-bytes-of-fill ; i.e. a number-of-icp-bytes-of-fill
            )
  (declare (ignore number-of-icp-bytes-of-fill))
  ;; Ignore.
  )



(def-handler-for-inappropriate-printing define-dummy-object
         (corresponding-icp-object-index ; i.e. a corresponding-icp-object-index
            ))



(def-handler-for-inappropriate-printing initialize-telewindows-workstation
         (workstation         ; i.e. a workstation
          gensym-window       ; i.e. a gensym-window
            ))



(def-handler-for-printing begin-window-update
         (gensym-window       ; i.e. a gensym-window
          left-edge-of-update-area ; i.e. a coordinate
          top-edge-of-update-area ; i.e. a coordinate
          right-edge-of-update-area ; i.e. a coordinate
          bottom-edge-of-update-area ; i.e. a coordinate
            )
  (postscript-emit-gensym-window gensym-window)
  (postscript-emit-rectangle 
      left-edge-of-update-area
      top-edge-of-update-area
      right-edge-of-update-area
      bottom-edge-of-update-area)
  (postscript-emit-operator 'begin-window-update))


;;; `Scroll-rectangle-in-current-window' is not used with rendering a window
;;; from scratch.

(def-handler-for-inappropriate-printing scroll-rectangle-in-current-window
    (source-left source-top
		 width height
		 destination-left destination-top))
  


(def-handler-for-printing set-up-palette
         (gensym-window       ; i.e. a gensym-window
          color-map           ; i.e. a color-map
            )
  (postscript-emit-gensym-window gensym-window)
  (postscript-emit-color-map color-map)
  (postscript-emit-operator 'set-up-palette))



(def-handler-for-inappropriate-printing telewindows-workstation-event
         (workstation         ; i.e. a workstation
          event-code          ; i.e. an event-code
          x                   ; i.e. a coordinate
          y                   ; i.e. a coordinate
          timestamp           ; i.e. an unsigned-integer
            ))

(def-handler-for-inappropriate-printing extended-telewindows-workstation-event
         (workstation         ; i.e. a workstation
          event-code          ; i.e. an event-code
          x                   ; i.e. a coordinate
          y                   ; i.e. a coordinate
          timestamp           ; i.e. an unsigned-integer
	  plist	 ; new: i.e., a local event plist (see: local-event) (MHD 2/5/02)
            ))



(def-handler-for-inappropriate-printing define-telewindows-workstation
         (corresponding-icp-object-index ; i.e. a corresponding-icp-object-index
            ))



(def-handler-for-inappropriate-printing set-position-of-mouse
         (x                   ; i.e. a coordinate
          y                   ; i.e. a coordinate
            ))



(def-handler-for-inappropriate-printing define-gensym-window
         (corresponding-icp-object-index ; i.e. a corresponding-icp-object-index
          left-edge-in-window ; i.e. a coordinate
          top-edge-in-window  ; i.e. a coordinate
          right-edge-in-window ; i.e. a coordinate
          bottom-edge-in-window ; i.e. a coordinate
          window-parameters-plist ; i.e. a list
          corresponding-icp-object-index-on-other-side? ; i.e. an unsigned-integer?
            ))



(def-handler-for-printing initialize-scratchpad-raster
         (gensym-window       ; i.e. a gensym-window
          minimum-width       ; i.e. an unsigned-integer
          minimum-height      ; i.e. an unsigned-integer
          bits-per-pixel      ; i.e. an unsigned-integer
          make-exact-size-p   ; i.e. a boolean
            )
  (postscript-emit-gensym-window gensym-window)
  (postscript-emit-unsigned-integer minimum-width)
  (postscript-emit-unsigned-integer minimum-height)
  (postscript-emit-unsigned-integer bits-per-pixel)
  (postscript-emit-boolean make-exact-size-p)
  (postscript-emit-operator 'initialize-scratchpad-raster))



(def-handler-for-printing paint-solid-rectangle-in-current-scratchpad-raster
    (clipped-left-edge   ; i.e. a coordinate
      clipped-top-edge    ; i.e. a coordinate
      clipped-right-edge  ; i.e. a coordinate
      clipped-bottom-edge ; i.e. a coordinate
      color-value)         ; i.e. a color-value
  (postscript-emit-rectangle 
    clipped-left-edge
    clipped-top-edge
    clipped-right-edge
    clipped-bottom-edge)
  (postscript-emit-scratchpad-color color-value)
  (postscript-emit-operator 'paint-solid-rectangle-in-current-scratchpad-raster))



(def-handler-for-printing paint-line-in-current-scratchpad-raster
    (x1                  ; i.e. a coordinate
      y1                  ; i.e. a coordinate
      x2                  ; i.e. a coordinate
      y2                  ; i.e. a coordinate
      color-value         ; i.e. a color-value
      paint-last-point?)   ; i.e. a boolean
  (postscript-emit-point x1 y1)
  (postscript-emit-point x2 y2)
  (postscript-emit-scratchpad-color color-value)
  (postscript-emit-boolean paint-last-point?)
  (postscript-emit-operator 'paint-line-in-current-scratchpad-raster))



(def-handler-for-printing paint-arc-or-circle-in-current-scratchpad-raster
    (x1                  ; i.e. a coordinate
      y1                  ; i.e. a coordinate
      x2                  ; i.e. a coordinate
      y2                  ; i.e. a coordinate
      x3                  ; i.e. a coordinate
      y3                  ; i.e. a coordinate
      x-scale             ; i.e. an unsigned-integer
      y-scale             ; i.e. an unsigned-integer
      color-value         ; i.e. a color-value
      circle?             ; i.e. a boolean
      filled?)             ; i.e. a boolean
  (postscript-emit-point x3 y3)
  (postscript-emit-point x2 y2)
  (postscript-emit-point x1 y1)
  (postscript-emit-scalling x-scale y-scale)
  (postscript-emit-scratchpad-color color-value)
  (postscript-emit-boolean circle?)
  (postscript-emit-boolean filled?)
  (postscript-emit-operator 'paint-arc-or-circle-in-current-scratchpad-raster))



(def-handler-for-printing paint-filled-triangle-in-current-scratchpad-raster
         (x1                  ; i.e. a coordinate
          y1                  ; i.e. a coordinate
          x2                  ; i.e. a coordinate
          y2                  ; i.e. a coordinate
          x3                  ; i.e. a coordinate
          y3                  ; i.e. a coordinate
          color-value)         ; i.e. a color-value
  (postscript-emit-point x1 y1)
  (postscript-emit-point x2 y2)
  (postscript-emit-point x3 y3)
  (postscript-emit-scratchpad-color color-value)
  (postscript-emit-operator 'paint-filled-triangle-in-current-scratchpad-raster))



(def-handler-for-printing paint-filled-polygon-in-current-scratchpad-raster
    (unsigned-polygon-point-list ; i.e. list of x and y points
      color-value)               ; i.e. a color-value
  (declare (ignore unsigned-polygon-point-list color-value))
  ;; pbk to fix soon
  ;;(loop for (x y) on unsigned-polygon-point-list by 'cddr
  ;;	do
  ;;(postscript-emit-point x y))
  ;;(postscript-emit-scratchpad-color color-value)
  ;;(postscript-emit-operator 'paint-filled-triangle-in-current-scratchpad-raster)
  )

;; This is unused because, for printing windows, polygons are decomposed into
;; triangles and drawn with paint-filled-triangle-in-current-scratchpad-raster
;; See orient-and-scale-and-paint-filled-polygon in ICONS. -fmw, 2/5/02



(def-handler-for-printing paint-wide-line-in-current-scratchpad-raster
         (x1                  ; i.e. a coordinate
          y1                  ; i.e. a coordinate
          x2                  ; i.e. a coordinate
          y2                  ; i.e. a coordinate
          color-value         ; i.e. a color-value
          paint-last-point?   ; i.e. a boolean
          line-width)          ; i.e. an unsigned-integer
  (postscript-emit-point x1 y1)
  (postscript-emit-point x2 y2)
  (postscript-emit-scratchpad-color color-value)
  (postscript-emit-boolean paint-last-point?)
  (postscript-emit-unsigned-integer line-width)
  (postscript-emit-operator 'paint-wide-line-in-current-scratchpad-raster))



(def-handler-for-printing paint-point-in-current-scratchpad-raster
         (x                   ; i.e. a coordinate
          y                   ; i.e. a coordinate
          color-value)         ; i.e. a color-value
  (postscript-emit-point x y)
  (postscript-emit-scratchpad-color color-value)
  (postscript-emit-operator 'paint-point-in-current-scratchpad-raster))

(def-handler-for-printing paint-icon-onto-graph-raster 
    (icon-rendering
     clip-left
     clip-top
     clip-right
     clip-bottom
     origin-left
     origin-top
     color-value)
  (let* ((line-drawing (line-drawing-description-for-rendering?
			 icon-rendering))
	 (polychrome-header?
	   (get-polychrome-header-if-any line-drawing))
	 (printing-icon-current-region-index?
	   nil)
	 (line-drawing-description-following-header
	   (if polychrome-header?
	       (cdr line-drawing)
	       line-drawing)))
;    (postscript-emit-operator 'newpath)
;    (postscript-emit-atom origin-left)
;    (postscript-emit-atom origin-top)
;    (postscript-emit-operator 'moveto)
    (postscript-emit-operator 'gsave)
    (postscript-emit-operator 'savectm)
    (postscript-emit-atom clip-left)
    (postscript-emit-atom clip-top)
    (postscript-emit-atom clip-right)
    (postscript-emit-atom clip-bottom)
    (postscript-emit-operator 'clip-to-rectangle)
    (postscript-emit-atom origin-left)
    (postscript-emit-atom origin-top)
    (postscript-emit-operator 'translate)
    (pformat "g~D"
	     (get-embedded-icon-layer-index
	       color-value
	       line-drawing-description-following-header))
    (postscript-emit-operator 'restorectm)
    (postscript-emit-operator 'grestore)
    ))

(defun get-embedded-icon-layer-index (color-value line-drawing-description)
  (loop for (index indexed-color-value
		   indexed-line-drawing-description)
	    in current-graph-rendering-embedded-icons
	when (and (eql color-value indexed-color-value)
		  (eq line-drawing-description
		      indexed-line-drawing-description))
	  do
	    (return index)
	finally
	  (let ((triple
		  (printing-list (reserve-composite-object-index)
				 color-value
				 line-drawing-description)))
	    (printing-push triple
			   current-graph-rendering-embedded-icons)
	    (return (car triple)))))

(defun emit-embedded-icon-layer-definition (index
					    color&line-drawing-description)
  (postscript-emit-composite-object-definition
    color&line-drawing-description
    #w"{}"
    'emit-embedded-icon-layer-definition-1
    index))
  
(defun emit-embedded-icon-layer-definition-1 (color&line-drawing-description)
  (let ((color-value (car color&line-drawing-description))
	(line-drawing-description (cadr color&line-drawing-description))
	(width 10000)
	(height 10000))
    (paint-one-bitmap-for-icon-on-scratchpad-raster
      'foreground
      line-drawing-description
      width height
      (normalized-scale) (normalized-scale)
      color-value
      nil
      nil ;sorted-computed-variables
      width height
      nil)))				; stipple feature not yet implemented!


;;; The following is stubbed just to prevent crashes when
;;; printing NUPEC graphs.

(def-handler-for-printing paint-marker-onto-graph-raster 
    (icon-rendering 
      x-in-graph-raster
      y-in-graph-raster
      color-value)
  (declare (ignore icon-rendering x-in-graph-raster
		   y-in-graph-raster color-value))
  )
 

;;;; Image operators.

(defun convert-rotation-to-degrees (rotation-and-reflection)
  (case rotation-and-reflection
    (normal 0)
    (clockwise-90 90)
    (clockwise-180 180)
    (clockwise-270 270)
    (reflected  0)
    (reflected-clockwise-90 90)
    (reflected-clockwise-180 180)
    (reflected-clockwise-270 280)
    (t 0)))


;;; The handler-for-printing `paint-icon-background-image-in-current-window' is
;;; used for painting an icon background image.

(def-handler-for-printing paint-icon-background-image-in-current-window
    ((image-data image-data)
     (coordinate x-in-window)		; Where to put image origin.
     (coordinate y-in-window)
     (coordinate left)			; draw-area-left Window coordinates into which we paint.
     (coordinate top)			; draw-area-top
     (coordinate right) 		; draw-area-right
     (coordinate bottom)		; draw-area-bottom
     (coordinate x-scale)
     (coordinate y-scale)
     (symbol rotation)			; Unused
     (symbol quality)			; Unused
     (unsigned-integer foreground-color) ; For bitmaps.
     (unsigned-integer background-color)
     (coordinate image-left-offset-in-ws)
     (coordinate image-top-offset-in-ws)
     (unsigned-integer rotated-width-in-ws)    ;entity-width-in-ws is declared special !
     (unsigned-integer rotated-height-in-ws))
  (declare (ignore rotated-width-in-ws rotated-height-in-ws))

  ;; I think this is always true in printing -- icon rotation is handled later
  ;; when the icon is rendered. -fmw, 1/2/02

  ;; Not true. Printing of rotated icon background images simply doesn't work.
  ;; -fmw, 8/22/04
  (when (or (null rotation) (eq rotation 'normal))
    (with-temporary-gensym-float-creation paint-icon-background-image-in-current-window
      (let* ((ps-x-scale (/e (coerce-to-gensym-float x-scale) 4096.0))
	     (ps-y-scale (/e (coerce-to-gensym-float y-scale) 4096.0))
	     (scaled-image-left-offset-in-ws
	       (round (* ps-x-scale image-left-offset-in-ws)))
	     (scaled-image-top-offset-in-ws
	       (round (* ps-y-scale image-top-offset-in-ws))))

	;; Images in icons may have an additional offset.
	(paint-image-in-postscript image-data
				   (+f x-in-window scaled-image-left-offset-in-ws)
				   (+f y-in-window scaled-image-top-offset-in-ws)
				   left top right bottom
				   x-scale y-scale
				   rotation quality
				   foreground-color
				   background-color)))))


;;; The handler-for-printing `paint-image-in-current-window' is used for
;;; painting workspace background images.

(def-handler-for-printing paint-image-in-current-window
    ((image-data image-data)
     (coordinate x-in-window)				    ; Where to put image origin.
     (coordinate y-in-window)
     (coordinate left)					    ; Window coordinates
     (coordinate top)
     (coordinate right)
     (coordinate bottom)
     (coordinate x-scale)
     (coordinate y-scale)
     (symbol rotation)
     (symbol quality)
     (unsigned-integer foreground-color)		    ; For bitmaps.
     (unsigned-integer background-color))
  (paint-image-in-postscript image-data x-in-window y-in-window
			     left top right bottom
			     x-scale y-scale
			     rotation quality
			     foreground-color
			     background-color))


;;; The function `paint-image-in-postscript' paints the given image-data using
;;; either the image or the colorimage postscript operators.  Colorimage, which
;;; is not available in all Level I implementations, is only used when the image
;;; is truely color and the user has requested full-color conversion.  This
;;; function is currently used for workspace backgrounds and icon background
;;; layers.

(defun paint-image-in-postscript
    (image-data				; Image to "paint"
      x-in-window			; Where to put image origin in window coor.
      y-in-window
      left				; Clipping rectangle in window coor.
      top
      right
      bottom
      x-scale				; Always 4096 in printing ?
      y-scale
      rotation				; Ignored
      quality				; Ignored
      foreground-color			; Colors for 1 and 0 in bitmaps.
      background-color)
  (declare (ignore rotation quality))			    ; *** Handle rotation?
  (declare (ignore foreground-color background-color))
  (when (ensure-image-data-pixels image-data) ; Just do nothing if no data.
    (let* ((width (image-data-width image-data))
	   (height (image-data-height image-data))
	   (depth (image-data-depth image-data))
	   (bytes-per-line (unaligned-bytes-per-scan-line width depth))
	   (color-map (image-data-color-map image-data))
	   (gray-map (create-gray-map-from-color-map color-map))
	   (raster? (image-data-cache? image-data))
	   (in-color-p (and (eq (printer-setup-particular 'color-conversion) 'full-color)
			    (not (image-data-is-gray-scale-p image-data))))
	   ;; Postscript wants 0=black, 1=white.  If the image has the opposite convention,
	   ;; then this local is T.
	   (flipped-one-bit-image-p
	     (and (=f depth 1)
		  (=f (managed-array-length gray-map) 2)
		  (>f (managed-svref gray-map 0) (managed-svref gray-map 1))))
	   (bits-per-component (cond (in-color-p 8) ((>f depth 8) 8) (t depth)))
	   (characters-per-line (cond (in-color-p
				       (*f width 6)) ; 6 hex chars per RGB pixel
				      ((<f depth 8)  ; 2 hex chars per packed byte
				       (*f bytes-per-line 2))
				      (t
				       (*f width 2)))) ; 2 hex chars per pixel
	   
	   (output-buffer (obtain-simple-text-string characters-per-line)))
      (gensym-assert (member depth '(1 2 4 8 24)))
      (when raster?
	;; imagestring is the buffer for reading.  Its length must be exactly the
	;; number of binary bytes per scan, as opposed hex characters per scan.
	(pformat "/imagestring ~d string def~%" (halff characters-per-line))

	;; Set up transform.
	(postscript-emit-operator 'gsave)
	(postscript-emit-atom left)
	(postscript-emit-atom top)
	(postscript-emit-atom right)
	(postscript-emit-atom bottom)
	(postscript-emit-operator 'clip-to-rectangle)

	(postscript-emit-atom x-in-window)
	(postscript-emit-atom y-in-window)
	(postscript-emit-operator 'translate)

	(postscript-emit-atom x-scale)
	(postscript-emit-atom 4096)
	(postscript-emit-operator 'div)
	(postscript-emit-atom width)
	(postscript-emit-operator 'mul)

	(postscript-emit-atom y-scale)
	(postscript-emit-atom 4096)
	(postscript-emit-operator 'div)
	(postscript-emit-atom height)
	(postscript-emit-operator 'mul)
	(postscript-emit-operator 'scale)

	;; Args to the IMAGE operator: (width, height, bits/comp, xform-matrix, procedure)
	;; See: http://www.adobe.com/products/postscript/pdfs/PLRM.pdf
	(postscript-emit-atom width)
	(postscript-emit-atom height)
	(postscript-emit-atom bits-per-component)
	(pformat " [~d 0 0 ~d 0 0]~%" width height)	    ; Workspace scaling takes care of flipping us.
	(pformat " {currentfile imagestring readhexstring pop}~%")
	(cond (in-color-p
	       (postscript-emit-operator 'false)              ; Single data source
	       (postscript-emit-atom 3)			    ; Number of components (rgb)
	       (postscript-emit-operator 'colorimage)         ; Color image
	       (do-raster-rows (raster?)
		 (let ((i 0))
		   (declare (type fixnum i))
		   (do-row-pixels (pixel rgb)
		     (write-hex-to-string rgb 6 output-buffer i)
		     (incff i 6)))
		 (g2-stream-write-string output-buffer printing-stream)
		 (pformat "~%~%")))
	      (t
	       ;; TODO: we should be using imagemask for 1-bit images, so
	       ;; that the workspace background shows through.
	       (postscript-emit-operator 'image)              ; Grayscale image
	       (case depth
		 ((1 2 4)		; Someday we may see 2 and 4 bit images.
		  (do-raster-rows (raster?)
		    (loop for x below bytes-per-line
			  as i from 0 by 2
			  as byte = (reverse-bits-in-byte
				      (if flipped-one-bit-image-p
					  (-f 255 (byte-vector-aref buffer x))
					  (byte-vector-aref buffer x)))
			  doing
		      (write-hex-to-string byte 2 output-buffer i))
		    (g2-stream-write-string output-buffer printing-stream)
		    (pformat "~%~%")))
		 (t			; Anything else is color, convert to gray.
		  ;; TODO: convert to black-and-white if requested!
		  (do-raster-rows (raster?)
		    (let ((i 0))
		      (declare (type fixnum i))
		      (do-row-pixels (pixel rgb)
			(let ((byte (if (=f depth 8)
					(managed-svref gray-map pixel)
					(rgb-to-gray rgb)))) ; An expensive computation
			  (write-hex-to-string byte 2 output-buffer i)
			  (incff i 2))))
		    (g2-stream-write-string output-buffer printing-stream)
		    (pformat "~%~%"))))))

	(postscript-emit-operator 'grestore))

      (reclaim-managed-array gray-map)
      (reclaim-simple-text-string output-buffer))))

;; We could do some compression here, if we cared.
;; Mostly, reduce 8bit images to 4bit or 2bit.
;; Should define a PostScript procedure which draws an image directly.




;;; The macro `copy-raster-bits-to-postscript' exists just so that it can be
;;; instantiated for 8 and 24 bit rasters.  Not intended to be a general purpose
;;; macro.  See similar code in `copy-raster-bits-into-buffer'.

(defmacro copy-raster-bits-to-postscript (raster-pixel-black-p)
  `(loop for y below image-height
	 as mask = 1
	 as byte = 0
	 as index = 0
	 doing
     (loop for x below image-width
	   doing
       (when (,raster-pixel-black-p raster? x y x y gray-map)
	 (setq byte (logiorf byte mask)))
       (setq mask (ashf mask 1))
       (when (>=f mask 256)
	 (setq byte (reverse-bits-in-byte byte))
	 (write-hex-to-string byte 2 output-buffer index)
	 (setq byte 0
	       mask 1)
	 (incff index 2)))
     (when (>f mask 1)
       (setq byte (reverse-bits-in-byte byte))
       (write-hex-to-string byte 2 output-buffer index)
       (incff index))
     (g2-stream-write-string output-buffer printing-stream)
     (pformat "~%")))

;;; The handler-for-printing `paint-image-in-current-scratchpad-raster' draws
;;; from the image into the scratchpad raster.  The scratchpad is always one bit
;;; deep, and icon layer images are defined to have tranparency, so we must use
;;; the imagemask operator.  Also, the code is cached in an "icon rendering" in
;;; postscript, and is not executed at top-level.  Therefore, we can't use the
;;; inline hex bytes for the image, and have to a postscript hex string.

;; Note that inline hex bytes means large images in icons may be too big for the
;; postscript interpreter!  Already true. For example, try printing the
;; cadet-blue workspace in /home/fmw/Bugs/images-with-image-info.kb .  We might
;; fix that particular bug by only dumping the image bytes which are visible in
;; the icon.  If there is a way to do that. -fmw, 1/7/02

(def-handler-for-printing paint-image-in-current-scratchpad-raster
    ((image-data image-data)
     (coordinate x-in-icon)		; Destination x,y w/in icon. (unscaled)
     (coordinate y-in-icon)
     (coordinate x-scale)		; Always 4096 in printing.
     (coordinate y-scale)
     (coordinate width)			; Original dimensions of the icon.
     (coordinate height)		; Always 10000 in printing.
     (symbol rotation)			; Always NIL in printing.
     (symbol quality)			; Some indication of rendering quality. Unused.
     (unsigned-integer color-value))	; Always foreground in printing.
  (declare (ignore rotation quality))
  (when (ensure-image-data-pixels image-data) ; Just do nothing if no data.
    (let* ((image-width (image-data-width image-data))
	   (image-height (image-data-height image-data))
	   (depth (image-data-depth image-data))
	   ;; The bytes per scan-line of the output image mask, always 1-bit deep.
	   (bytes-per-line (unaligned-bytes-per-scan-line image-width 1))
	   (color-map (image-data-color-map image-data))
	   (gray-map (create-gray-map-from-color-map color-map))
	   (output-buffer (obtain-simple-text-string (*f bytes-per-line 2)))
	   (raster? (image-data-cache? image-data)))
      (cond ((null raster?))
	    ((not (or (=f depth 1) (=f depth 8) (=f depth 24)))
	     (dwarn "Image data ~s of depth of ~d is not handled by printing" image-data depth))
	    (t
	     (postscript-emit-atom x-in-icon)
	     (postscript-emit-atom y-in-icon)
	     (postscript-emit-atom width)
	     (postscript-emit-atom height)
	     (postscript-emit-atom image-width)
	     (postscript-emit-atom image-height)
	     (postscript-emit-atom x-scale)
	     (postscript-emit-atom y-scale)
	     (postscript-emit-scratchpad-color color-value)
	     (pformat "{<")
	     (case depth
	       (1
		(loop for y below image-height
		      for buffer = (shredded-raster-buffer raster? y)
		      doing
		  (loop for x below bytes-per-line
			as i from 0 by 2
			as byte = (reverse-bits-in-byte (byte-vector-aref buffer x))
			doing
		    (write-hex-to-string byte 2 output-buffer i))
		  (g2-stream-write-string output-buffer printing-stream)
		  (pformat "~%")))
	       (8  (copy-raster-bits-to-postscript shredded-raster-ref-8-black-p))
	       (24 (copy-raster-bits-to-postscript shredded-raster-ref-24-black-p)))
	     (pformat ">}~%")
	     (postscript-emit-operator 'paint-image-in-current-scratchpad-raster)))

      (reclaim-managed-array gray-map)
    (reclaim-simple-text-string output-buffer))))

;; printing calls us only with normalized scale and rotation.
;; See `postscript-emit-line-drawing'




;;; The handler-for-printing `change-image-palette-of-window' is
;;; ignored by printing.  Instead, we look at another value in the
;;; printer-setup table.

(def-handler-for-printing change-image-palette-of-window
    ((gensym-window window)
     (symbol palette-name)
     (array-of-unsigned-integers? color-map?))
  (declare (ignore window palette-name color-map?)))





;;;; Current window operators.




(def-handler-for-printing paint-solid-rectangle-in-current-window
    (clipped-left-edge
      clipped-top-edge
      clipped-right-edge
      clipped-bottom-edge
      color-value)
  (postscript-emit-rectangle 
    clipped-left-edge
    clipped-top-edge
    clipped-right-edge
    clipped-bottom-edge)
  (postscript-emit-color-value color-value)
  (postscript-emit-operator 'paint-solid-rectangle-in-current-window))



(def-handler-for-printing add-solid-rectangle-to-current-window
    (subtract-instead?
      clipped-left-edge
      clipped-top-edge
      clipped-right-edge
      clipped-bottom-edge
      color-difference)
  (declare (ignore subtract-instead?))
  (unless (color-difference-is-transparent-p color-difference) ; Used to be zerop.
    (postscript-emit-rectangle 
      clipped-left-edge
      clipped-top-edge
      clipped-right-edge
      clipped-bottom-edge)
    (postscript-emit-color-difference color-difference)
    (postscript-emit-operator 'add-solid-rectangle-to-current-window)))




(def-handler-for-printing-in-all-passes add-from-icon-rendering-to-current-window
    (subtract-instead?					    ; i.e. a subtract-instead?
      clipped-left-edge					    ; i.e. a coordinate
      clipped-top-edge					    ; i.e. a coordinate
      clipped-right-edge				    ; i.e. a coordinate
      clipped-bottom-edge				    ; i.e. a coordinate
      color-difference					    ; i.e. a color-difference
      icon-rendering					    ; i.e. an icon-rendering
      left-edge-in-icon-rendering			    ; i.e. a coordinate
      top-edge-in-icon-rendering			    ; i.e. a coordinate
      list-of-color-differences)			    ; i.e. a list-of-unsigned-integers
  (declare (ignore subtract-instead?))
  (cond
    ((=f printing-pass-number 1)
     (let ((printing-pass-number 2))
       (unless (lookup-postscript-icon-rendering-index icon-rendering)
	 (postscript-emit-icon-rendering icon-rendering)
	 (postscript-emit-operator 'pop))))
    ((=f printing-pass-number 2)

     ;; This is just an optimization for the case where the icon is monochrome
     ;; and transparent, For polychrome icons, each layer must be considered
     ;; indepentantly for transpareny, hence happens down in the postscript
     ;; code.  See `unless-transparent'.
     (unless (and (null list-of-color-differences)
		  (color-difference-is-transparent-p color-difference))
       (postscript-emit-rectangle 
	 clipped-left-edge
	 clipped-top-edge
	 clipped-right-edge
	 clipped-bottom-edge)
       ;; See the real handler in windows3.
       (postscript-emit-color-difference (if (consp list-of-color-differences)
					     (first list-of-color-differences)
					     color-difference))
       (postscript-emit-icon-rendering icon-rendering)
       (postscript-emit-point
	 left-edge-in-icon-rendering
	 top-edge-in-icon-rendering)
       (postscript-emit-list-of-colors list-of-color-differences t)
       (postscript-emit-operator 'add-from-icon-rendering-to-current-window)))))


(def-handler-for-printing add-upward-sloping-line-to-current-window
    (subtract-instead?   ; i.e. a subtract-instead?
      clipped-left-edge   ; i.e. a coordinate
      clipped-top-edge    ; i.e. a coordinate
      clipped-right-edge  ; i.e. a coordinate
      clipped-bottom-edge ; i.e. a coordinate
      color-difference    ; i.e. a color-difference
      left-end-x          ; i.e. a coordinate
      right-end-y         ; i.e. a coordinate
      right-end-x         ; i.e. a coordinate
      left-end-y)	  ; i.e. a coordinate
  (declare (ignore subtract-instead? clipped-left-edge clipped-top-edge
		   clipped-right-edge clipped-bottom-edge))
  (unless (color-difference-is-transparent-p color-difference)
    (postscript-emit-color-difference color-difference)
    (postscript-emit-rectangle 
      left-end-x
      right-end-y
      right-end-x
      left-end-y)
    (postscript-emit-operator 'add-upward-sloping-line-to-current-window)))




(def-handler-for-printing add-downward-sloping-line-to-current-window
    (subtract-instead?   ; i.e. a subtract-instead?
      clipped-left-edge   ; i.e. a coordinate
      clipped-top-edge    ; i.e. a coordinate
      clipped-right-edge  ; i.e. a coordinate
      clipped-bottom-edge ; i.e. a coordinate
      color-difference    ; i.e. a color-difference
      left-end-x          ; i.e. a coordinate
      left-end-y          ; i.e. a coordinate
      right-end-x         ; i.e. a coordinate
      right-end-y         ; i.e. a coordinate
      )
  (declare (ignore subtract-instead? clipped-left-edge clipped-top-edge
		   clipped-right-edge clipped-bottom-edge))
  (unless (color-difference-is-transparent-p color-difference)
    (postscript-emit-color-difference color-difference)
    (postscript-emit-rectangle 
      left-end-x
      left-end-y
      right-end-x
      right-end-y)
    (postscript-emit-operator 'add-downward-sloping-line-to-current-window)))


(def-handler-for-printing add-wide-polyline-to-current-window
    ((coordinate clipped-left-edge)
     (coordinate clipped-top-edge)
     (coordinate clipped-right-edge)
     (coordinate clipped-bottom-edge)
     (unsigned-integer color-difference)
     (unsigned-integer width)
     (unsigned-integer style)		; PS-SOLID, maybe other style bits.
     (list-of-unsigned-integers dashes) ; dot/dash pattern. NIL means solid.
     (list-of-integers vertices))	; Alternating x and y.
  (declare (ignore clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge))
  (unless (color-difference-is-transparent-p color-difference)
    (postscript-emit-color-difference color-difference)
    (postscript-emit-atom width)

    (postscript-emit-atom
      (case (logandf style #x0F00)
	(#.ps-endcap-round 1)
	(#.ps-endcap-square 2)		; Projecting
	(#.ps-endcap-flat 0)		; Butt
	(t 0)))
    
    (postscript-emit-atom
      (case (logandf style #xF000)
	(#.ps-join-round 1)
	(#.ps-join-bevel 2)
	(#.ps-join-miter 0)
	(t 0)))

    (let ((dot (*f width 1))		; Matches graphics.c, which matches Win32.
	  (dash (*f width 3)))
      (case (logandf style #x000F)
	(#.ps-solid (pformat "[]"))
	(#.ps-dash (pformat "[~a ~a]" dash dot))
	(#.ps-dot (pformat "[~a ~a]" dot dot))
	(#.ps-dashdot (pformat "[~a ~a ~a ~a]" dash dot dot dot))
	(#.ps-dashdotdot (pformat "[~a ~a ~a ~a ~a ~a]" dash dot dot dot dot dot))
	(#.ps-userstyle
	 (postscript-emit-atom "[")
	 (loop for dash in dashes doing
	   (postscript-emit-atom dash)) 
	 (postscript-emit-atom "]"))
	(t
	 (dwarn "Unknown line-style ~a during printing." style)
	 (postscript-emit-atom "[]"))))

    (postscript-emit-atom "[")
    (loop for xy in vertices doing
      (postscript-emit-atom xy))
    (postscript-emit-atom "]")
    (postscript-emit-operator 'add-wide-polyline-to-current-window)))


(def-handler-for-printing add-polygon-to-current-window
    ((coordinate clipped-left-edge)
     (coordinate clipped-top-edge)
     (coordinate clipped-right-edge)
     (coordinate clipped-bottom-edge)
     (unsigned-integer line-color-difference)
     (unsigned-integer line-width)
     (unsigned-integer fill-color-difference)
     (unsigned-integer fill-pattern)
     (list-of-integers vertices))
  ;; FIXME
  clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge
  line-color-difference line-width fill-color-difference fill-pattern vertices)

(def-handler-for-printing add-ellipse-to-current-window
    ((coordinate clipped-left-edge)
     (coordinate clipped-top-edge)
     (coordinate clipped-right-edge)
     (coordinate clipped-bottom-edge)
     (unsigned-integer line-color-difference)
     (unsigned-integer line-width)
     (unsigned-integer fill-color-difference)
     (unsigned-integer fill-pattern)
     (coordinate x1) (coordinate y1)
     (coordinate x2) (coordinate y2))
  ;; FIXME
  clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge
  line-color-difference line-width fill-color-difference fill-pattern
  x1 y1 x2 y2)


;;; `Copy-from-tiling-pattern-to-current-window' is called only because
;;; when we hide the workspace, while tiling it onto multiple sheets of
;;; paper the drawing mechinisms then fill the window in with the
;;; background tiling pattern.  We ignore these calls. 

(def-handler-for-printing copy-from-tiling-pattern-to-current-window
         (left-edge           ; i.e. a coordinate
          top-edge            ; i.e. a coordinate
          right-edge          ; i.e. a coordinate
          bottom-edge         ; i.e. a coordinate
          tiling-pattern      ; i.e. a tiling-pattern
            )
  (declare (ignore left-edge top-edge right-edge bottom-edge tiling-pattern)))




(def-handler-for-printing-in-all-passes add-from-line-of-text-to-current-window
    (subtract-instead?	; i.e. a subtract-instead?
      clipped-left-edge	; i.e. a coordinate
      clipped-top-edge	; i.e. a coordinate
      clipped-right-edge	; i.e. a coordinate
      clipped-bottom-edge	; i.e. a coordinate
      text-line	; i.e. a text-line
      word-spacing	; i.e. a word-spacing
      font-map	; i.e. a font-map
      color-difference	; i.e. a color-difference
      x-scale	; i.e. a x-scale
      y-scale	; i.e. a y-scale
      left-edge-of-line-of-text-in-window	; i.e. a coordinate
      baseline-in-window	; i.e. a coordinate
      )
  (declare (ignore subtract-instead?))
  (cond
    ((eql printing-pass-number 1)
     (printing-pass-1-define-for-text font-map text-line))
    ((eql printing-pass-number 2)
     (let ((kanji-appeared-in-text nil))
       (postscript-emit-rectangle 
	 clipped-left-edge
	 clipped-top-edge
	 clipped-right-edge
	 clipped-bottom-edge)
       (setq kanji-appeared-in-text
	     (postscript-emit-text-string (car font-map) text-line))
       (postscript-emit-unsigned-integer word-spacing)
       (postscript-emit-font-map font-map)
       (postscript-emit-color-difference color-difference)
       (postscript-emit-atom x-scale)
       (postscript-emit-atom 4096)
       (postscript-emit-operator 'div)
       (postscript-emit-atom y-scale)
       (postscript-emit-atom 4096)
       (postscript-emit-operator 'div)
       (postscript-emit-atom -1)	   
       (postscript-emit-operator 'mul)
       (postscript-emit-unsigned-integer left-edge-of-line-of-text-in-window)
       (postscript-emit-unsigned-integer baseline-in-window)
       (if kanji-appeared-in-text
	   (postscript-emit-operator 'kanji-add-from-line-of-text-to-current-window)
	   (postscript-emit-operator 'add-from-line-of-text-to-current-window))))))



;;; The handler for the `beep-in-window' ICP message should never be called by
;;; printing.

(def-handler-for-inappropriate-printing beep-in-window
    (gensym-window       ; i.e. a gensym-window
      ))



;;; The handler for the `modify-gsi-sensor-definition' ICP message should never
;;; be called by printing.

(def-handler-for-inappropriate-printing modify-gsi-sensor-definition
    (corresponding-icp-object-index ; i.e. a corresponding-icp-object-index
      update-interval     ; i.e. an integer
      value-type          ; i.e. an unsigned-integer
      reserve-1           ; i.e. a gsi-parameter
      reserve-2           ; i.e. a gsi-parameter
      ))



;;; The handler for the `load-sensor-list-element' ICP message should never be
;;; called by printing.

(def-handler-for-inappropriate-printing load-sensor-list-element
    (gsi-sensor          ; i.e. a gsi-sensor
      collection-interval? ; i.e. an integer
      value-to-set?       ; i.e. a gsi-data-value
      ))



;;; The handler for the `write-user-message-string' ICP message should never be
;;; called by printing.

(def-handler-for-inappropriate-printing write-user-message-string
    (user-message        ; i.e. a text-string
      urgency?            ; i.e. an unsigned-integer-or-nil
      duration?           ; i.e. an unsigned-integer-or-nil
      ))



;;; The handler for the `return-gsi-extension-version' ICP message should never
;;; be called by printing.

(def-handler-for-inappropriate-printing return-gsi-extension-version
    (major-version-number ; i.e. an unsigned-integer
      minor-version-number ; i.e. an unsigned-integer
      ))



;;; The handler for the `receive-value-for-ping-request' ICP message should
;;; never be called by printing.

(def-handler-for-inappropriate-printing receive-value-for-ping-request
    (gsi-interface       ; i.e. a returned-gsi-interface
      year                ; i.e. an integer
      month               ; i.e. an integer
      day                 ; i.e. an integer
      hour                ; i.e. an integer
      minute              ; i.e. an integer
      second              ; i.e. an integer
      status              ; i.e. an integer
      ))



;;; The handler for the `receive-value-for-gsi-sensor' ICP message should never
;;; be called by printing.

(def-handler-for-inappropriate-printing receive-value-for-gsi-sensor
    (gsi-sensor          ; i.e. a returned-gsi-sensor
      error-code          ; i.e. a gsi-value-error-code
      value               ; i.e. a gsi-data-value
      ))



(def-handler-for-inappropriate-printing initialize-gsi-interface
    (interface-name ;symbol or nil
     class-name ; symbol or nil
     listener-network-type ; symbol or nil
     listener-host-name ; string
     listener-port-name ; string
     remote-process-initialization-string ; text-string
     ))

(def-handler-for-inappropriate-printing return-initialize-gsi-interface-status
    (error-information ;string
      ))


;;; The handler for the `initialize-data-server' ICP message should never be
;;; called by printing.

(def-handler-for-inappropriate-printing initialize-data-server
    (text-string         ; i.e. a text-string
      ))



;;; The handler for the `send-data-values-if-any' ICP message should never be
;;; called by printing.

(def-handler-for-inappropriate-printing send-data-values-if-any
    (gsi-interface       ; i.e. a gsi-interface
      year                ; i.e. an integer
      month               ; i.e. an integer
      day                 ; i.e. an integer
      hour                ; i.e. an integer
      minute              ; i.e. an integer
      second              ; i.e. an integer
      ))



;;; The handler for the `define-gsi-sensor' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing define-gsi-sensor
         (corresponding-icp-object-index ; i.e. a corresponding-icp-object-index
          parameter1          ; i.e. a gsi-parameter
          parameter2          ; i.e. a gsi-parameter
          parameter3          ; i.e. a gsi-parameter
          parameter4          ; i.e. a gsi-parameter
          parameter5          ; i.e. a gsi-parameter
          parameter6          ; i.e. a gsi-parameter
            ))



;;; The handler for the `receive-value-for-gsi-sensor-with-timestamp' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing receive-value-for-gsi-sensor-with-timestamp
         (gsi-sensor          ; i.e. a returned-gsi-sensor
          error-code          ; i.e. a gsi-value-error-code
          value               ; i.e. a gsi-data-value
          year                ; i.e. an integer
          month               ; i.e. an integer
          day                 ; i.e. an integer
          hour                ; i.e. an integer
          minute              ; i.e. an integer
          second              ; i.e. an integer
            ))



;;; The handler for the `define-gsi-interface' ICP message should never be
;;; called by printing.

(def-handler-for-inappropriate-printing define-gsi-interface
    (corresponding-icp-object-index ; i.e. a corresponding-icp-object-index
      ))



;;; The handler for the `receive-gsi-sensor-value-vector' ICP message should
;;; never be called by printing.

(def-handler-for-inappropriate-printing receive-gsi-sensor-value-vector
    (gsi-sensor          ; i.e. a returned-gsi-sensor
      error-code          ; i.e. a gsi-value-error-code
      value               ; i.e. a gsi-data-value
      vector              ; i.e. a gsi-value-vector
      ))



;;; The handler for the `receive-timestamped-gsi-sensor-value-vector' ICP
;;; message should never be called by printing.

(def-handler-for-inappropriate-printing receive-timestamped-gsi-sensor-value-vector
    (gsi-sensor          ; i.e. a returned-gsi-sensor
      error-code          ; i.e. a gsi-value-error-code
      value               ; i.e. a gsi-data-value
      year                ; i.e. an integer
      month               ; i.e. an integer
      day                 ; i.e. an integer
      hour                ; i.e. an integer
      minute              ; i.e. an integer
      second              ; i.e. an integer
      timestamped-vector  ; i.e. a gsi-value-vector
      ))



;;; The handler for the `intern' ICP message should never be called by
;;; printing.

(def-handler-for-inappropriate-printing intern
    (corresponding-icp-object-index ; i.e. a corresponding-icp-object-index
      text-string         ; i.e. a text-string
      ))



;;; The handler for the `add-to-list-of-symbols' ICP message should never be
;;; called by printing.

(def-handler-for-inappropriate-printing add-to-list-of-symbols
    (corresponding-icp-object-index ; i.e. a corresponding-icp-object-index
      symbol              ; i.e. a symbol
      first-element?      ; i.e. a boolean
      ))



;;; The handler for the `make-tiling-pattern' ICP message should never be
;;; called by printing.

(def-handler-for-inappropriate-printing make-tiling-pattern
    (corresponding-icp-object-index			    ; i.e. a corresponding-icp-object-index
      gensym-window					    ; i.e. a gensym-window
      tiling-pattern-rows-with-color-values		    ; i.e. a tiling-pattern-rows-with-color-values
      ))



(def-handler-for-printing begin-making-icon-rendering
         (corresponding-icp-object-index ; i.e. a corresponding-icp-object-index
          x-scale-of-rendering ; i.e. an unsigned-integer
          y-scale-of-rendering ; i.e. an unsigned-integer
          reflection-and-rotation-of-rendering ; i.e. a symbol
          width-of-rendering-structure ; i.e. an unsigned-integer
          height-of-rendering-structure ; i.e. an unsigned-integer
          width-of-rendered-icon ; i.e. an unsigned-integer
          height-of-rendered-icon ; i.e. an unsigned-integer
          number-of-rendering-structure-elements ; i.e. an unsigned-integer
            )
  (postscript-emit-unsigned-integer corresponding-icp-object-index)
  (postscript-emit-scalling x-scale-of-rendering y-scale-of-rendering)
  (postscript-emit-symbol reflection-and-rotation-of-rendering)
  (postscript-emit-unsigned-integer width-of-rendering-structure)
  (postscript-emit-unsigned-integer height-of-rendering-structure)
  (postscript-emit-unsigned-integer width-of-rendered-icon)
  (postscript-emit-unsigned-integer height-of-rendered-icon)
  (postscript-emit-unsigned-integer number-of-rendering-structure-elements)
  (postscript-emit-operator 'begin-making-icon-rendering))



(def-handler-for-printing region-extrema-for-stored-raster
    (x-offset            ; i.e. an unsigned-integer
      y-offset            ; i.e. an unsigned-integer
      x-max               ; i.e. an unsigned-integer
      y-max               ; i.e. an unsigned-integer
      )
  (postscript-emit-unsigned-integer x-offset)
  (postscript-emit-unsigned-integer y-offset)
  (postscript-emit-unsigned-integer x-max)
  (postscript-emit-unsigned-integer y-max)
  (postscript-emit-operator 'region-extrema-for-stored-raster))



;;; The handler for the `request-to-refresh-window' ICP message should never be
;;; called by printing.

(def-handler-for-inappropriate-printing request-to-refresh-window
    (gensym-window       ; i.e. a gensym-window
      refresh-graphic-element-memory-too? ; i.e. a boolean
      edges-supplied?     ; i.e. a boolean
      left-edge-of-update-area-or-or-arbitrary-coordinate ; i.e. a coordinate
      top-edge-of-update-area-or-or-arbitrary-coordinate ; i.e. a coordinate
      right-edge-of-update-area-or-or-arbitrary-coordinate ; i.e. a coordinate
      bottom-edge-of-update-area-or-or-arbitrary-coordinate ; i.e. a coordinate
      ))



;;; The handler for the `request-to-reshape-window' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing request-to-reshape-window
         (gensym-window       ; i.e. a gensym-window
          new-left-edge       ; i.e. a coordinate
          new-top-edge        ; i.e. a coordinate
          new-right-edge      ; i.e. a coordinate
          new-bottom-edge     ; i.e. a coordinate
            ))



;;; The handler for the `request-to-reshape-native-window' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing request-to-reshape-native-window
         (gensym-window       ; i.e. a gensym-window
          new-left-edge       ; i.e. a coordinate
          new-top-edge        ; i.e. a coordinate
          new-right-edge      ; i.e. a coordinate
          new-bottom-edge     ; i.e. a coordinate
            ))



;;; The handler for the `shift-position-of-mouse' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing shift-position-of-mouse
         (delta-x             ; i.e. an integer
          delta-y             ; i.e. an integer
            ))



;;; The handler for the `request-to-close-telewindows-connection' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing request-to-close-telewindows-connection
         (gensym-window       ; i.e. a gensym-window
            ))



;;; The handler for the `g2ds-load-variable-list-element' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing g2ds-load-variable-list-element
         (g2ds-variable       ; i.e. a g2ds-variable
          collection-interval ; i.e. an integer
          data-type           ; i.e. a symbol
          data-value          ; i.e. a g2ds-data-value
            ))



;;; The handler for the `g2ds-user-message-string' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing g2ds-user-message-string
         (user-message        ; i.e. a text-string
          urgency?            ; i.e. an unsigned-integer-or-nil
          duration?           ; i.e. an unsigned-integer-or-nil
            ))



;;; The handler for the `g2ds-variable-value' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing g2ds-variable-value
         (g2ds-variable-structure ; i.e. a returned-g2ds-variable
          error-code          ; i.e. an unsigned-integer
          data-type           ; i.e. a symbol
          value               ; i.e. a g2ds-data-value
            ))



;;; The handler for the `g2ds-define-variable' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing g2ds-define-variable
         (corresponding-icp-object-index ; i.e. a corresponding-icp-object-index
          data-request-expression ; i.e. a g2ds-expression
            ))



;;; The handler for the `new-externally-simulated-object' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing new-externally-simulated-object
         (external-simulation-object ; i.e. an external-simulation-object
            ))



;;; The handler for the `define-external-simulation-object' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing define-external-simulation-object
         (icp-object-index    ; i.e. an integer
          object-class        ; i.e. a text-string
            ))



;;; The handler for the `simulation-initialization-value' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing simulation-initialization-value
         (initialization-value ; i.e. a float
            ))



;;; The handler for the `begin-simulation-input-vector-for-object' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing begin-simulation-input-vector-for-object
         (external-simulation-object ; i.e. an external-simulation-object
            ))



;;; The handler for the `g2ds-configure-variable' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing g2ds-configure-variable
         (g2ds-variable       ; i.e. a g2ds-variable
          data-request-expression ; i.e. a g2ds-expression
            ))



;;; The handler for the `simulation-keyword' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing simulation-keyword
         (keyword             ; i.e. a text-string
            ))



;;; The handler for the `simulation-input-value' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing simulation-input-value
         (input-value         ; i.e. a float
            ))



;;; The handler for the `g2ds-server-status' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing g2ds-server-status
         (g2ds-server-status  ; i.e. a symbol
            ))



;;; The handler for the `begin-simulation-output-vector-for-object' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing begin-simulation-output-vector-for-object
         (external-simulation-object ; i.e. a returned-external-simulation-object
            ))



;;; The handler for the `simulation-output-value' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing simulation-output-value
         (output-value        ; i.e. a float
            ))



;;; The handler for the `connection-info' ICP message should never be called by printing.

(def-handler-for-inappropriate-printing connection-info
         (input-end-object    ; i.e. an external-simulation-object
          output-end-object   ; i.e. an external-simulation-object
          directional?        ; i.e. an unsigned-integer
          port-name-for-input-end-object ; i.e. a text-string
          port-name-for-output-end-object ; i.e. a text-string
          externally-simulated-connection ; i.e. an external-simulation-object
          number-of-connections-left-in-path ; i.e. an unsigned-integer
            ))


(def-handler-for-printing begin-making-graph-rendering
    (corresponding-icp-object-index			    ; i.e. a corresponding-icp-object-index
      format-of-graph-rendering-structure		    ; i.e. a symbol
      x-scale-of-graph-rendering			    ; i.e. an unsigned-integer
      y-scale-of-graph-rendering			    ; i.e. an unsigned-integer
      grid-border-width					    ; i.e. an unsigned-integer
      width-of-graph-rendering-structure		    ; i.e. an unsigned-integer
      height-of-graph-rendering-structure		    ; i.e. an unsigned-integer
      width-of-rendered-graph				    ; i.e. an unsigned-integer
      height-of-rendered-graph)				    ; i.e. an unsigned-integer
  (postscript-emit-unsigned-integer corresponding-icp-object-index)
  (postscript-emit-symbol format-of-graph-rendering-structure)
  (postscript-emit-scalling x-scale-of-graph-rendering y-scale-of-graph-rendering)
  (postscript-emit-unsigned-integer grid-border-width)
  (postscript-emit-unsigned-integer width-of-graph-rendering-structure)
  (postscript-emit-unsigned-integer height-of-graph-rendering-structure)
  (postscript-emit-unsigned-integer width-of-rendered-graph)
  (postscript-emit-unsigned-integer height-of-rendered-graph)
  (postscript-emit-operator 'begin-making-graph-rendering))



(def-handler-for-printing-in-all-passes add-from-graph-rendering-to-current-window
    (subtract-instead?					    ; i.e. a subtract-instead?
      clipped-left-edge					    ; i.e. a coordinate
      clipped-top-edge					    ; i.e. a coordinate
      clipped-right-edge				    ; i.e. a coordinate
      clipped-bottom-edge				    ; i.e. a coordinate
      grid-background-color-value			    ; i.e. a color-value
      graph-rendering					    ; i.e. a graph-rendering
      left-edge-in-graph-rendering			    ; i.e. a coordinate
      top-edge-in-graph-rendering			    ; i.e. a coordinate
      color-value					    ; i.e. a color-value
      color-values-for-rasters?)			    ; i.e. a list-of-unsigned-integers
  (declare (ignore subtract-instead?))
  (cond
    ((=f printing-pass-number 1)
     (let ((printing-pass-number 2)
	   (printing-graph-rendering-color-list? color-values-for-rasters?) ; Unused?
	   (adding-from-graph-rendering-p t))
       (unless (getf postscript-object-mapping-for-graph-renderings
		     (corresponding-graph-grid-or-chart? graph-rendering))
	 (postscript-emit-graph-rendering graph-rendering)
	 (postscript-emit-operator 'pop))))
    ((=f printing-pass-number 2)
     (postscript-emit-rectangle 
       clipped-left-edge
       clipped-top-edge
       clipped-right-edge
       clipped-bottom-edge)
     (postscript-emit-unsigned-integer grid-background-color-value)
     (postscript-emit-graph-rendering graph-rendering)
     (postscript-emit-unsigned-integer left-edge-in-graph-rendering)	; modified by hand
     (postscript-emit-unsigned-integer top-edge-in-graph-rendering)	;  ditto
     (postscript-emit-color-value color-value)	;  ditto
     (postscript-emit-list-of-colors color-values-for-rasters? nil)
     (postscript-emit-operator 'add-from-graph-rendering-to-current-window))))



(def-handler-for-printing update-graph-dateline
    (dateline            ; i.e. a coordinate
      erase-dateline      ; i.e. a coordinate
      graph-rendering)     ; i.e. a graph-rendering
  (declare (ignore graph-rendering))
  (postscript-emit-integer dateline)
  (postscript-emit-integer erase-dateline)
;   (postscript-emit-graph-rendering graph-rendering) ;; in the dynamic state.
  (postscript-emit-operator 'update-graph-dateline))



(def-handler-for-printing update-graph-data-extrema
    (left-edge top-edge right-edge bottom-edge)
  (postscript-emit-rectangle 
    left-edge
    top-edge
    right-edge
    bottom-edge)
  (postscript-emit-operator 'update-graph-data-extrema))




(def-handler-for-printing update-ring-raster-for-graph-given-color-values
    (graph-rendering
      number-of-rasters-needed)
  (postscript-emit-graph-rendering graph-rendering)
  (postscript-emit-unsigned-integer number-of-rasters-needed)
  (postscript-emit-operator 'update-ring-raster-for-graph-given-color-values))



(def-handler-for-printing prepare-for-painting-graph
    (graph-rendering)
  (postscript-emit-graph-rendering graph-rendering)
  (postscript-emit-operator 'prepare-for-painting-graph))


(def-handler-for-printing clear-data-clipping-rectangles ()
  )


;;; The handler for the `delete-icp-object-for-process' ICP message should
;;; never be called by printing.

(def-handler-for-inappropriate-printing delete-icp-object-for-process
    (corresponding-icp-object-index
      name-of-corresponding-icp-object-index-space))



;;; The handler for the `return-g2ds-version' ICP message should never be
;;; called by printing.

(def-handler-for-inappropriate-printing return-g2ds-version
    (major-version-number ; i.e. an unsigned-integer
      minor-version-number)) ; i.e. an unsigned-integer




(def-handler-for-printing message-group-id
    (message-group-id
      number-of-icp-bytes)
  (postscript-emit-unsigned-integer message-group-id)
  (postscript-emit-unsigned-integer number-of-icp-bytes)
  (postscript-emit-operator 'message-group-id))



;;; The handler for the `define-remote-procedure-name' ICP message should never
;;; be called by printing.

(def-handler-for-inappropriate-printing define-remote-procedure-name
    (corresponding-icp-object-index ; i.e. a corresponding-icp-object-index
      remote-procedure-name-symbol)) ; i.e. a symbol



;;; The handler for the `define-remote-procedure-identifier' ICP message should
;;; never be called by printing.

(def-handler-for-inappropriate-printing define-remote-procedure-identifier
    (corresponding-icp-object-index ; i.e. a corresponding-icp-object-index
      remote-procedure-identifier-tag ; i.e. an unsigned-integer
      list-of-included-return-attributes
      list-of-excluded-return-attributes))



;;; The handler for the `rpc-start' ICP message should never be called by
;;; printing.

(def-handler-for-inappropriate-printing rpc-start
    (remote-procedure-name ; i.e. a remote-procedure-name
      remote-values-list))  ; i.e. a remote-values-list



;;; The handler for the `rpc-call' ICP message should never be called by
;;; printing.

(def-handler-for-inappropriate-printing rpc-call
    (remote-procedure-name ; i.e. a remote-procedure-name
      remote-procedure-identifier ; i.e. a remote-procedure-identifier
      remote-values-list))  ; i.e. a remote-values-list



;;; The handler for the `rpc-error' ICP message should never be called by
;;; printing.

(def-handler-for-inappropriate-printing rpc-error
    (error-name          ; i.e. a symbol
      error-level         ; i.e. an unsigned-integer
      error-description   ; i.e. a text-string
      error-argument-list)) ; i.e. a remote-values-list



;;; The handler for the `rpc-error-to-caller' ICP message should never be
;;; called by printing.

(def-handler-for-inappropriate-printing rpc-error-to-caller
    (remote-caller-index ; i.e. an unsigned-integer
      signaller?          ; i.e. an unsigned-integer-or-nil
      error-name          ; i.e. a symbol
      error-level         ; i.e. an unsigned-integer
      error-description   ; i.e. a text-string
      error-argument-list)) ; i.e. a remote-values-list



;;; The handler for the `rpc-asynchronous-abort' ICP message should never be
;;; called by printing.

(def-handler-for-inappropriate-printing rpc-asynchronous-abort
    (procedure-to-abort))  ; i.e. a remote-procedure-identifier



;;; The handler for the `rpc-return-values' ICP message should never be called
;;; by printing.

(def-handler-for-inappropriate-printing rpc-return-values
    (calling-procedure-index ; i.e. an unsigned-integer
      return-values-list))  ; i.e. a remote-values-list



;;; The handler for the `rpc-acknowledge-abort' ICP message should never be
;;; called by printing.

(def-handler-for-inappropriate-printing rpc-acknowledge-abort
    (aborted-procedure-index)) ; i.e. an unsigned-integer



;;; The handler for the `speedup-input-or-output-tagnames' ICP message should
;;; never be called by printing.

(def-handler-for-inappropriate-printing speedup-input-or-output-tagnames
    (input-or-output-tagnames)) ; i.e. a text-string



;;; The handler for the `speedup-tagname' ICP message should never be called by
;;; printing.

(def-handler-for-inappropriate-printing speedup-tagname
    (tagname))             ; i.e. a text-string



;;; The handler for the `speedup-value' ICP message should never be called by
;;; printing.

(def-handler-for-inappropriate-printing speedup-value
    (value))               ; i.e. a float



(def-handler-for-printing paint-from-line-of-text-to-current-scratchpad-raster
    (clipped-left-edge	; i.e. a coordinate
      clipped-top-edge	; i.e. a coordinate
      clipped-right-edge	; i.e. a coordinate
      clipped-bottom-edge	; i.e. a coordinate
      text-line		; i.e. a text-line
      word-spacing	; i.e. a word-spacing
      font-map		; i.e. a font-map
      color-value		; i.e. a color-value
      x-scale		; i.e. a x-scale
      y-scale		; i.e. a y-scale
      left-edge-of-line-of-text-in-window	; i.e. a coordinate
      baseline-in-window)	; i.e. a coordinate
  (printing-pass-1-define-for-text font-map text-line)
  (let ((kanji-appeared-in-text nil))
    (postscript-emit-rectangle 
      clipped-left-edge
      clipped-top-edge
      clipped-right-edge
      clipped-bottom-edge)
    (setq kanji-appeared-in-text (postscript-emit-text-string (car font-map) text-line))
    (postscript-emit-unsigned-integer word-spacing)
    (postscript-emit-font-map font-map)
    (postscript-emit-scratchpad-color color-value)
    (postscript-emit-scalling x-scale y-scale)
    (postscript-emit-unsigned-integer left-edge-of-line-of-text-in-window)	; Hand modified
    (postscript-emit-unsigned-integer baseline-in-window)	;    ditto
    (if kanji-appeared-in-text
	(postscript-emit-operator 'kanji-paint-from-line-of-text-to-current-scratchpad-raster)
        (postscript-emit-operator 'paint-from-line-of-text-to-current-scratchpad-raster))))


(def-handler-for-printing  orient-and-paint-line-of-text-to-current-scratchpad-raster
    (clipped-left-edge	; i.e. a coordinate
      clipped-top-edge	; i.e. a coordinate
      clipped-right-edge	; i.e. a coordinate
      clipped-bottom-edge	; i.e. a coordinate
      width
      height
      text-line		; i.e. a text-line
      text-orientation
      icon-orientation
      word-spacing	; i.e. a word-spacing
      font-map		; i.e. a font-map
      color-value		; i.e. a color-value
      x-scale		; i.e. a x-scale
      y-scale		; i.e. a y-scale
      left-edge-of-line-of-text-in-window	; i.e. a coordinate
      baseline-in-window)	; i.e. a coordinate
  (declare (ignore width height text-orientation icon-orientation))
  (printing-pass-1-define-for-text font-map text-line)
  (let ((kanji-appeared-in-text nil))
    (postscript-emit-rectangle 
      clipped-left-edge
      clipped-top-edge
      clipped-right-edge
      clipped-bottom-edge)
    (setq kanji-appeared-in-text (postscript-emit-text-string (car font-map) text-line))
    (postscript-emit-unsigned-integer word-spacing)
    (postscript-emit-font-map font-map)
    (postscript-emit-scratchpad-color color-value)
    (postscript-emit-scalling x-scale y-scale)
    (postscript-emit-unsigned-integer left-edge-of-line-of-text-in-window)	; Hand modified
    (postscript-emit-unsigned-integer baseline-in-window)	;    ditto
    (if kanji-appeared-in-text
	;(postscript-emit-operator 'kanji-add-from-line-of-text-to-current-window)
	;(postscript-emit-operator 'add-from-line-of-text-to-current-window))))
	(postscript-emit-operator 'kanji-paint-from-line-of-text-to-current-scratchpad-raster)
	(postscript-emit-operator 'paint-from-line-of-text-to-current-scratchpad-raster))))



;;; The handler for the `remote-eval' ICP message should never be called by
;;; printing.

(def-handler-for-inappropriate-printing remote-eval
    (s-expression-for-remote-eval))



;;; The handler for the `connection-shutdown-imminent' ICP message should never
;;; be called by printing.

(def-handler-for-inappropriate-printing connection-shutdown-imminent
    (time-until-shutdown)) ; i.e. an unsigned-integer







;;;;  Host Print File Handling Interface



;;; Printing a file on a given host is controled by parameters stored in 
;;; the XXX slot of the printing system table.  The routines in this
;;; section provide the abstractions for handling these.

;;;  - Get-host-printing-particulars           -- sets initial values
;;;  - Spool-file-to-printer-for-this-platform -- does just that.
;;;  - semantic-check-spooling-parameters      -- Generates any printer-setup frame notes.
;;;  - semantic-check-file-template            -- Reviews the template for ovious errors.


;;; `Semantic-check-file-template' takes a text-string and returns a boolean.
;;; It attempts to prove that the string can be used on this host as a template
;;; for a filename.

(defun semantic-check-file-template (file-template)
  (let* ((number-of-star 0)
	 (example-instance-as-text
	   (twith-output-to-text-string
	     (loop for i from 0 below (lengthw file-template)
		   as c = (charw file-template i)
		   do
	       (cond
		 ((char=w #.%\* c)
		  (twrite-char #.%\1)
		  (incf number-of-star))
		 (t
		  (twrite-char c))))))
	 (example-instance
	   (convert-text-string-to-ascii-filename-as-much-as-possible
	     example-instance-as-text)))
    (prog1
      (and (<=f 0 number-of-star 1)
	   (valid-pathname-p example-instance))
      (reclaim-text-string example-instance-as-text)
      (reclaim-text-string example-instance))))

(def-kb-specific-variable file-template-instance-counter printing 0)


;;; The function `normalize-printing-pathname-type' changes the filetype for
;;; pathname to the usual type for the given print format, if it currently has a
;;; known type. In other words, if the template filename in printer-setup has a
;;; filetype of "ps" or "jpg", then we feel free to change it to suit the print
;;; format. If the user has entered some other filetype or none, then we assume
;;; he knows what he wants. The upshot is that all KBs which have kept the usual
;;; "print-*.ps" template will automatically get "print-*.jpg" files when
;;; printing in JPEG format, which I think is what users would want.

(defun normalize-printing-pathname-type (pathname format)
  (let* ((gp (gensym-pathname pathname))
	 (old-type (gensym-pathname-type gp))
	 (canonical-type (filetype-for-print-format format))
	 (new-type (if (and old-type (member old-type '(#w"ps" #w"jpg") :test #'string-equalw))
		       canonical-type
		       old-type)))
    (prog1
	(gensym-make-pathname
	  :host (gensym-pathname-host gp)
	  :device (gensym-pathname-device gp)
	  :directory (gensym-pathname-directory gp)
	  :name (gensym-pathname-name gp)
	  :type new-type
	  :version nil)
      (reclaim-gensym-pathname gp))))


;;; `Instantiate-file-template' takes a text-string for which 
;;; semantic-check-file-template returns true.  It returns a new
;;; text-string (which the caller then owns) which can be used as
;;; a file name on the current host.

(defun instantiate-file-template (file-template format)
  (loop as i from 0 to 10
	as candidate-filename-as-text =
	(twith-output-to-text-string
	  (loop for i from 0 below (text-string-length file-template)
		as c = (charw file-template i)
		do
	    (cond
	      ((eqlw #.%\* c)
	       (tformat "~D" (incf file-template-instance-counter)))
	      (T
	       (twrite-char c)))))
	as candidate-filename = (prog1
				    (export-text-string ; Is this export really needed?
				      candidate-filename-as-text
				      'instantiate-file-template-for-printing)
				  (reclaim-text-string candidate-filename-as-text))
	as pathname? = (and (valid-pathname-p candidate-filename)
			    (normalize-printing-pathname-type candidate-filename format))
	do
    (reclaim-text-string candidate-filename)
    (cond ((and pathname?
		(not (gensym-probe-file pathname?)))
	   (return (prog1 (gensym-namestring-as-text-string pathname?)
		     (reclaim-gensym-pathname pathname?))))
	  (pathname?
	   (reclaim-gensym-pathname pathname?)))))

;; Will fail as soon as the user has the first ten in his file system.



;;; `Get-host-printing-particulars' is called when a fresh KB is created.
;;; It returns three values that quide how print files are handled on this
;;; platforms, these are:
;;;  - spooled-filename-template, a string
;;;  - spool-file-to-printer,  a boolean
;;;  - printer-identification, a string

(defun get-host-printing-particulars ()
  (let* ((spooled-filename-template-pathname
	   (gensym-make-pathname
	     :name     "print-*"
	     :type     "ps"
	     :version  :newest
	     :defaults process-specific-system-pathname))
	 (spooled-filename-template
	   (gensym-namestring-as-text-string
	     spooled-filename-template-pathname)))
    (reclaim-gensym-pathname spooled-filename-template-pathname)
    (values 
      spooled-filename-template
      nil
      (copy-constant-wide-string #w"unknown"))))



;;; `Spool-file-to-printer-for-this-platform' is called on as the last step in
;;; generating printed output.  Using the printer-setup settings, it submits
;;; the file to the printer requested by the user.  It reclaims that
;;; gensym-pathname.  The routine is very host specific.

;;; While this currently never happens, on a host that suports streams
;;; directly to the printer, this routine would close the stream.

(defvar platform-independent-print-spool-command-file-name "g2print")

(defun-allowing-unwind spool-file-to-printer-for-this-platform
    (pathname-of-actual-spooled-file)
  (let ((namestring 
	  (gensym-namestring-as-text-string pathname-of-actual-spooled-file)))

    #+someday
    (let ((spooled-output-flag nil)
	  (spawn-failed-flag nil)
	  (discarded-output-file nil)
	  (printer-identification 
	    (printer-setup-particular 'printer-identification))
	  (delete-file-after-printing 
	    #+development t ;; <-- Change if you want to study the spooled output.
	    #-development t))

      (when (and (printer-setup-particular 'spool-file-to-printer)
		 (not (or (get-particulars-of-frame-note-if-any
			    'printer-no-printer-specified
			    printer-setup)
			  (get-particulars-of-frame-note-if-any
			    'printer-is-unknown
			    printer-setup)
			  (get-particulars-of-frame-note-if-any
			    'printer-file-template-is-misformed
			    printer-setup))))
	(protected-let*
	    ((setup-particular 
	       (printer-setup-particular 'printer-identification))
	     (delete-file-after-printing-string
	       (if delete-file-after-printing "yes" "no"))
	     (command-namestring
	       (if (eq g2-operating-system 'vms)
		   (tformat-text-string
		     "@~a \"~a\" \"~a\" \"~a\""
		     platform-independent-print-spool-command-file-name
		     setup-particular
		     namestring
		     delete-file-after-printing-string)
		   (tformat-text-string
		     "~a \"~a\" \"~a\" \"~a\""
		     platform-independent-print-spool-command-file-name
		     setup-particular
		     namestring
		     delete-file-after-printing-string))
	       (reclaim-text-string command-namestring)))
	  (setf spooled-output-flag t)
	  (setf discarded-output-file delete-file-after-printing)
	  (with-temporary-gensym-float-creation spawn-command-to-spool-printing
	    (let ((process-id
		    (c-spawn_command_line_process command-namestring)))
	      (when (= process-id -1.0)
		(setq spawn-failed-flag t)))))

	(if spawn-failed-flag
	    (notify-user "Spooling to printer ~S failed." printer-identification)
	    (if discarded-output-file
		(if spooled-output-flag
		    (notify-user "Spooled printing to the printer ~S." printer-identification)
		    );; this never happens.
		(if spooled-output-flag
		    (notify-user "Spooled printing to the printer ~S, and did not delete the print file ~S"
				 printer-identification
				 namestring)
		    (notify-user "Spooled print out to the file ~S." namestring))))))

    (reclaim-text-string namestring)))

;; jh, 11/17/91.  Fleshed out spooling for non-Lispm platforms in
;; spool-file-to-printer-for-this-platform.

;; On VMS, this function will run a command line that looks like
;;   @g2print "printer-name" "spool-file" "delete-afterwards"
;; The file should be named g2print.com for this to work.

;; On UNIX, the command line looks like
;;   g2print "printer-name" "spool-file" "delete-afterwards"
;; The file g2print should have execution privileges for this to work.

;; In the above command lines, printer-name names the printer, spool-file names
;; the file to be spooled, and delete-afterwards is yes if the file is to be
;; deleted after printing and no otherwise.  The surrounding double-quotes will
;; appear in the actual spawned command line, since they deter the operating
;; system readers from their well-meaning but insidious expansion of command-line
;; arguments.

;; We intend to have platform experts write the spooling scripts on each platform.
;; Here are skeletons for them to start with.  Remove the first semicolon on each
;; line and these scripts will be ready for elaboration.

;; VMS:

;$ ! Tests passing string parameters to a spawned VMS command line.
;$ !
;$ ! The ultimate aim is to fill this in with machine-specific print-spooling
;$ ! commands.
;$ !
;$ printername = P1
;$ spoolfile = P2
;$ deleteafter = P3
;$ !
;$ write sys$output "spooling G2 print job"
;$ write sys$output "  printer: " + printername
;$ write sys$output "  spool file: " + spoolfile
;$ write sys$output ""
;$ !
;$ if deleteafter .eqs. "yes" -
;  then write sys$output "pool file will be deleted after printing"
;$ if deleteafter .eqs. "no" -
;  then write sys$output "spool file will not be deleted after printing"

;; UNIX (Bourne shell)

;# Tests passing string parameters to a spawned UNIX Bourne shell command line.
;
;# The ultimate aim is to fill this in with machine-specific print-spooling
;# commands.
;
;echo "spooling G2 print job"
;echo "  printer: $1"
;echo "  spool file: $2"
;echo ""
;
;case $3 in 
;yes) echo "spool file will be deleted after printing" ;;
;no) echo "spool file will not be deleted after printing" ;;
;esac

;; UNIX (C shell)

;# Tests passing string parameters to a spawned UNIX C shell command line.
;
;# The ultimate aim is to fill this in with machine-specific print-spooling
;# commands.
;
;setenv printername $1
;setenv spoolfile $2
;setenv deleteafter $3
;
;echo "spooling G2 print job"
;echo "  printer: $printername"
;echo "  spool file: $spoolfile"
;echo ""
;
;if $deleteafter == yes then
;   echo "spool file will be deleted after printing"
;endif
;
;if $deleteafter == no then
;   echo "spool file will not be deleted after printing"
;endif


;;; The function `semantic-check-spooling-parameters' is called by the frame
;;; note method of printer-setup to check if the specified settings make sense
;;; of this host.  This routine is very host specific.

(defun semantic-check-spooling-parameters ()
  (let* ((printer-identification 
	   (printer-setup-particular 'printer-identification))
	 (spool-file-to-printer 
	   (printer-setup-particular 'spool-file-to-printer))
	 (we-really-have-a-printer-identification-p
	   (not (string-equalw #w"unknown"
			       printer-identification))))

    ;; Check the spooled-filename-template
    (let ((spooled-filename-template (printer-setup-particular 'spooled-filename-template)))
      (unless (semantic-check-file-template spooled-filename-template)
	(add-frame-note 'printer-file-template-is-misformed printer-setup t t nil)))
    
    ;; Check the printer-identification (can't).

    
    ;; Check the spool file to printer flag.
    ;; Is this a platform where we don't know how to spool output to the printer.
    (when (and spool-file-to-printer
	       we-really-have-a-printer-identification-p)
      (add-frame-note 'printer-g2-can-not-spool-output-on-this-platform printer-setup t t nil))))



;;;; External Interface Exported to FACILITIES by PRINTING.



;;; The defparameter `postscript-enable-multipage-legends' enables the little
;;; legends on each page of a multipage printout.

(defparameter postscript-enable-multipage-legends t)


;;; The function `emit-postscript-job-header' emits a standard postscript header,
;;; including the date, job name, etc.  Also, we compute the EPS bounding-box.

(defun emit-postscript-job-header (workspace
				    paper-size
				    npages
				    eps?
				    workspace-width
				    workspace-height
				    postscript-units-per-workspace-unit-mf
				    paper-orientation
				    paper-width-mf
				    paper-height-mf
				    left-margin-mf
				    top-margin-mf
				    right-margin-mf
				    bottom-margin-mf
				    paper-left-margin-mf
				    paper-top-margin-mf
				    paper-right-margin-mf
				    paper-bottom-margin-mf)
  ;; Do not generate an EPS header if we span multiple pages.
  ;; But, we still supply a bound-box anyways.
  (pformat "%!PS-Adobe-3.0~a" (if eps?  " EPSF-3.0" ""))
  (pformat "~%%%Pages: ~d" npages)
  (pformat "~%%%Title: Workspace ~a"
	   (get-or-make-up-designation-for-block workspace))

  (let ((version (twith-output-to-text-string
		   (twrite-system-version current-system-version))))
    (pformat "~%%%Creator: G2 ~a" version)
    (reclaim-text-string version))

  (pformat "~%%%For: ~a" (get-current-user-name))
  (let ((date (twith-output-to-text-string
		(multiple-value-bind (seconds minutes hours day month year)
		    (get-decoded-real-time)
		  (print-decoded-time seconds minutes hours day month year)))))
    (pformat "~%%%CreationDate: ~a" date)
    (reclaim-text-string date))

  (pformat "~%%%Orientation: ~(~a~)" paper-orientation)

  (unless eps?
    ;; Should we skip this if paper size is 'custom?
    (pformat "~%%%DocumentPaperSizes: ~(~a~)" paper-size))
  
  ;; Compute EPS bounding box if needed.  We have to duplicate some of the
  ;; computations which happen in define-paper & global-layout. Sigh.
  (when eps?
    (with-temporary-gensym-float-creation emit-postscript-job-header
      (when (eq paper-orientation 'landscape)
	;; Chestnut release 3 maybe can't handle this, let see about shiftf
	;;  (rotatef bottom-margin-mf right-margin-mf top-margin-mf left-margin-mf)
	(setf left-margin-mf
	      (shiftf bottom-margin-mf right-margin-mf top-margin-mf left-margin-mf)))

      ;; At this point, paper-height, paper-width, paper-bottom-margin, bottom-margin-mf, etc,
      ;; all reflect the numbers wrt the unrotated (portrait) PS coordinate system.
      (let* ((left-margin (maxe (managed-float-value left-margin-mf)
				(managed-float-value paper-left-margin-mf)))
	     (top-margin (maxe (managed-float-value top-margin-mf)
			       (managed-float-value paper-top-margin-mf)))
	     (right-margin (maxe (managed-float-value right-margin-mf)
				 (managed-float-value paper-right-margin-mf)))
	     (bottom-margin (maxe (managed-float-value bottom-margin-mf)
				  (managed-float-value paper-bottom-margin-mf)))
	     (paper-height (managed-float-value paper-height-mf))
	     (paper-width (managed-float-value paper-width-mf))
	     (scale (managed-float-value postscript-units-per-workspace-unit-mf))
	     (image-width (*e scale (coerce-to-gensym-float workspace-width)))
	     (image-height (*e scale (coerce-to-gensym-float workspace-height))))

	(multiple-value-bind (xmin ymin xmax ymax)
	    (cond ((>f npages 1)
		   ;; Hmm. If the multipage legend is present, then it takes more space.
		   (values left-margin
			   bottom-margin
			   (-e paper-width right-margin)
			   (-e paper-height top-margin)))
		  ((eq paper-orientation 'portrait)
		   (values left-margin
			   (-e paper-height top-margin image-height)
			   (+e left-margin image-width)
			   (-e paper-height top-margin)))
		  (t
		   (values (-e paper-width right-margin image-width)
			   (-e paper-height top-margin image-height)
			   (-e paper-width right-margin)
			   (-e paper-height top-margin))))
	  ;; EPS requires these to be integers.
	  (pformat "~%%%BoundingBox: ~a ~a ~a ~a"
		   (floore-first xmin)
		   (floore-first ymin)
		   (ceilinge-first xmax)
		   (ceilinge-first ymax))))))
  
  (pformat "~%%%EndComments"))

;; We output an EPS file iff the job fits on one page.
;; It would be nice to output an EPS preview, too.


(defun emit-postscript-page-layout (paper-size-name
				     postscript-units-per-workspace-unit-mf
				     paper-orientation
				     actual-paper-width-mf
				     actual-paper-height-mf
				     left-margin-mf
				     top-margin-mf
				     right-margin-mf
				     bottom-margin-mf
				     paper-left-margin-mf
				     paper-top-margin-mf
				     paper-right-margin-mf
				     paper-bottom-margin-mf)
  (pformat "~%% Define paper size.~%")
  ;; emit-paper-tray ought to be here, but it is in emit-postscript-prolog instead.
  (postscript-emit-symbol paper-size-name)
  (postscript-emit-symbol paper-orientation)
  (postscript-emit-managed-float actual-paper-width-mf)
  (postscript-emit-managed-float actual-paper-height-mf)
  (postscript-emit-managed-float paper-left-margin-mf)
  (postscript-emit-managed-float paper-top-margin-mf)
  (postscript-emit-managed-float paper-right-margin-mf)
  (postscript-emit-managed-float paper-bottom-margin-mf)
  (postscript-emit-operator 'define-paper)
  
  (postscript-emit-managed-float postscript-units-per-workspace-unit-mf)
  (postscript-emit-managed-float left-margin-mf)
  (postscript-emit-managed-float top-margin-mf)
  (postscript-emit-managed-float right-margin-mf)
  (postscript-emit-managed-float bottom-margin-mf)
  (postscript-emit-symbol (printer-setup-particular 'color-conversion))
  (postscript-emit-operator 'global-layout)
  (pformat "~%%%EndSetup"))


;;; The function `postscript-start-page' prepares postscript for a new page of
;;; output, setting up the coordinate transformation so that the window
;;; coordinates rectangle given by the x and y offset and step size will fill
;;; the page.

(defun postscript-start-page (page-number nrows ncolumns
					  x-tile-offset y-tile-offset x-tile-step y-tile-step
					  multipage-legends-p blank-page-p)
  (pformat "~%~%%%Page: ~D ~D~%" page-number page-number)
  (postscript-emit-operator 'set-up-page)
  ;; (postscript-emit-operator 'outline-page-margins) ;; Debugging.
  (when (and multipage-legends-p
	     (or (not (page-economy-mode printer-setup))
		 (not blank-page-p)))
    (pformat " ~d ~d ~d draw-multipage-legend~%" nrows ncolumns page-number))
  (postscript-emit-unsigned-integer x-tile-offset)
  (postscript-emit-unsigned-integer y-tile-offset)
  (postscript-emit-unsigned-integer x-tile-step)
  (postscript-emit-unsigned-integer y-tile-step)
  (postscript-emit-operator 'set-up-ctm))

(defun postscript-end-document (last-page-number) ; emit-postscript-epilog 
  (pformat "~%end~%")   	; Of ab-dict begin.
  (pformat "~%~%%%Trailer")
  (pformat "~%~%%%Pages: ~D" (1-f last-page-number))
  (pformat "~%~%%%EOF")
  (pformat "~%~%"))


(defun postscript-remove-margins-from-dimension (width margin1 margin2)
  (allocate-managed-float
    (-e (managed-float-value width)
	(managed-float-value margin1)
	(managed-float-value margin2))))

(defun postscript-compute-scaling-to-fit
    (top bottom left right page-width-mf page-height-mf)
  (let* ((fudge (if native-printer-information 0 -15))                        ; 15??
	 (workspace-height-e (coerce-to-gensym-float (-w bottom top fudge)))
	 (workspace-width-e (coerce-to-gensym-float (-w right left fudge))))
    (allocate-managed-float
      (mine (/e (managed-float-value page-width-mf)
		workspace-width-e)
	    (/e (managed-float-value page-height-mf)
		workspace-height-e)))))


(defun postscript-compute-page-count
    (scale-mf page-width-mf page-height-mf workspace-width workspace-height window-frame-width)
  ;; Duplicates code in background-print-workspace
  (let* ((x-tile-step (truncate (managed-float-value page-width-mf) 
				(managed-float-value scale-mf)))
	 (y-tile-step (truncate (managed-float-value page-height-mf) 
				(managed-float-value scale-mf)))
	 (initial-tile-offset (-f window-frame-width))
	 (ncolumns
	   ;; If the left and right margins overwhelm the usable print area 
	   ;; x-tile-step will be 0 . - jpg 7/31/00
	   (if (/=f x-tile-step 0)
	       (ceiling (- workspace-width initial-tile-offset) x-tile-step)
	       0))
	 (nrows
	   ;; If the top and bottom margins overwhelm the usable print area 
	   ;; y-tile-step will be 0 . - jpg 7/31/00
	   (if (/=f y-tile-step 0)
	       (ceiling (- workspace-height initial-tile-offset) y-tile-step)
	       0)))
    (*f nrows ncolumns)))



;;; The function `postscript-compute-workspace-scaling' returns the postscript
;;; units/workspace unit scale factor, as a managed float, for the given
;;; workspace and paper sizes.  If the user has request EPS, then we ensure
;;; that the output fits on a single page.

(defun postscript-compute-workspace-scaling
    (top bottom left right page-width-mf page-height-mf
	 workspace-width workspace-height window-frame-width)
  (let ((scale-mf
	  (case (printer-workspace-scaling)
	    (scale-to-fit-single-page
	     (postscript-compute-scaling-to-fit
	       top bottom left right page-width-mf page-height-mf))
	    (t
	     (postscript-convert-linear-distance-to-postscript-units-mf
	       (printer-workspace-scaling) t)))))

    (cond ((null (generate-eps-p))
	   scale-mf)
	  ((=f 1 (postscript-compute-page-count scale-mf page-width-mf page-height-mf
						workspace-width workspace-height
						window-frame-width))
	   scale-mf)
	  (t
	   (reclaim-managed-float scale-mf)
	   (postscript-compute-scaling-to-fit
	     top bottom left right page-width-mf page-height-mf)))))


;;; The function `suppress-printing-border-p' is true if the argument
;;; image-plane should not have its border (frame) printed.  This is done if the
;;; page-economy-mode of printing-parameters is true and image-plane has a
;;; default frame style.  (Note that when printing, at present, the border of
;;; the image plane of the workspace is always the classic default black border,
;;; and not necessarily the same as that shown in the window.)

(defun suppress-printing-border-p (image-plane)
  (if (page-economy-mode printer-setup)
      (image-plane-has-default-frame-p image-plane)
      nil))

;; This is to be called from DRAW to implement the page-economy-mode feature,
;; which is new for G2 6.2. (MHD 6/14/02)


;;;; Generic Document/Page Hooks


(defun start-document (workspace left top right bottom)
  (declare (ignore workspace left top right bottom))
  (case printing-format
    (bitmap)
    (native)
    (postscript)))

(defun start-page (page-number nrows ncolumns
			       left-margin-mf top-margin-mf right-margin-mf bottom-margin-mf
			       paper-left-margin-mf paper-top-margin-mf
			       paper-right-margin-mf paper-bottom-margin-mf
			       postscript-units-per-workspace-unit-mf
			       x-tile-offset y-tile-offset x-tile-step y-tile-step
			       multipage-legends-p blank-page-p)
  (with-drawing-trace (printing)
    (format t "Printing page ~d of ~d.~%" page-number (* nrows ncolumns)))
  (case printing-format
    (bitmap)
    (native
     (native-start-page page-number nrows ncolumns left-margin-mf top-margin-mf
			right-margin-mf bottom-margin-mf
			paper-left-margin-mf paper-top-margin-mf
			paper-right-margin-mf paper-bottom-margin-mf
			postscript-units-per-workspace-unit-mf multipage-legends-p))
    (postscript
     (postscript-start-page page-number nrows ncolumns
			    x-tile-offset y-tile-offset
			    x-tile-step y-tile-step
			    multipage-legends-p
			    blank-page-p))))

(defun end-page ()
  (case printing-format
    (bitmap)				; TODO: Would dump one band to the compressor here.
    (native (native-printing-end-page output-window-for-printing?))
    (postscript (pformat "showpage~%"))))

(defun end-document (last-page-number)
  ;; TODO: Signal semaphore if requested. Return error, if any.
  ;; Actually, error returns have to happen elsewhere.
  (case printing-format
    (bitmap
     (when bitmap-for-printing?		; TODO: Never nil here, I think.
       (c-x11-compress-image (g2-stream-handle printing-stream)
			     (pixmap-pointer bitmap-for-printing?)
			     (pixmap-width bitmap-for-printing?)
			     (pixmap-height bitmap-for-printing?)
			     (or (printer-setup-particular 'quality) -1))
       (reclaim-pixmap bitmap-for-printing?)))
    (native (native-printing-end-doc output-window-for-printing?))
    (postscript (postscript-end-document last-page-number))))


(defun native-start-page
    (page-number nrows ncolumns
		 left-margin-mf top-margin-mf right-margin-mf bottom-margin-mf
		 paper-left-margin-mf paper-top-margin-mf paper-right-margin-mf paper-bottom-margin-mf
		 postscript-units-per-workspace-unit-mf
		 multipage-legends-p)
  (let (scale left-margin top-margin right-margin bottom-margin)
    (with-temporary-gensym-float-creation native-start-page
      ;; Compute margins relative to edges of physical page, in units of
      ;; tenths of inches. Compute scale in integer workspace units per
      ;; 10 inches.
      (setq left-margin (round (maxe (managed-float-value left-margin-mf)
				     (managed-float-value paper-left-margin-mf))
			       7.2)
	    top-margin  (round (maxe (managed-float-value top-margin-mf)
				     (managed-float-value paper-top-margin-mf))
			       7.2)
	    right-margin (round (maxe (managed-float-value right-margin-mf)
				      (managed-float-value paper-right-margin-mf))
				7.2)
	    bottom-margin  (round (maxe (managed-float-value bottom-margin-mf)
					(managed-float-value paper-bottom-margin-mf))
				  7.2)
	    scale (round 720.0
			 (managed-float-value postscript-units-per-workspace-unit-mf))))
    (native-printing-start-page output-window-for-printing? page-number nrows ncolumns
				left-margin top-margin
				right-margin bottom-margin
				scale multipage-legends-p)))


;;;; To Do List For Printing

;;; - Details
;;;   - a progress indicator!
;;;   - The font hb72 font is Helvetica-Black, not Helvetica-Bold, but I don't want
;;;     to figure out how to down load Helvetica-Black.
;;;   - The hm fonts are not helvetica, but are helvetica medium.  This looks ok, but
;;;     the font spacing isn't exact.

;;; - Modularity
;;;   - Create a with-printing form and then facilities can use it.
;;;   - all print-handlers should be declared funcallable?
;;;     - no, because they appear as quoted constants in INT's tables.
;;;     - but I shoule probably do something to declare them "simple."

;;; - The ICP cut point.
;;;   - Do I really know that all def-icp-message-type icp-messages are
;;;     of no interest to printing?

;;; - Bugs that maynot be reproducable.
;;;   - The call upon paint-one-bitmap-for-icon-on-scratchpad-raster
;;;     sends a very bogus width and height, that can't be healthy.
;;; - Postscript operations equivalents for ICP messages that are missing.
;;;   - necessary?  (I believe all these are unused when drawing usage)
;;;     - update-graph-dateline
;;;     - update-graph-data-extrema
;;;     - update-ring-raster-for-graph-given-color-values
;;;     - set-up-palette
;;;     - begin-window-update
;;;     - initialize-scratchpad-raster
;;;     - begin-making-icon-rendering
;;;     - region-extrema-for-stored-raster
;;;     - begin-making-graph-rendering
;;;     - prepare-for-painting-graph
;;;     - message-group-id




;;;; Background processes


;;; A `background-process' is a long-running operation, consisting of a
;;; function and a block of state variables.  The function is repeatedly called by
;;; service-workstations, with the state block as an argument, until the
;;; process status becomes DEAD.  On LISP machines, these sorts of things were
;;; known as simple processes.


;;; The defvar `background-processes' is a gensym-list of running processes.
;;; The first one on the list is run to completion before the next one
;;; gets any quanta.
;; Is that strictly true? See service-background-processes.

(def-system-variable background-processes printing nil)

;; TODO: These will need to be cleaned-up on kb-clear!


;;; The system-variable `background-processes-task' is a scheduler task
;;; which works on our heavy-weight background processes.

(def-system-variable background-processes-task printing nil)


(defvar current-background-process nil)

;; The static description of a type of process.
(def-global-property-name description-of-process)

(define-structure process-description ()
  (:constructor make-process-description-1)
  (:conc-name t)
  name
  function
  initializer
  reclaimer)

(defun make-process-description (name function initializer reclaimer)
  (let ((process-description (make-process-description-1)))
    (setf (process-description-name process-description) name
	  (process-description-function process-description) function
	  (process-description-initializer process-description) initializer
	  (process-description-reclaimer process-description) reclaimer
	  (description-of-process name) process-description)
    process-description))



;; A process instance.

(define-structure process ()
  (:constructor make-process-1)
  (:managed t)
  (:conc-name t)
  name
  function				; A function on the state-block.
  status				; Waiting, Running, Dead.
  (priority 0)
  (time-of-last-tick 0)			; Time when process last got a quantum.
  (progress 0)				; An integer 0-100.
  state-block)






;; Create initial state block. Does not call the process.

(defun make-background-process (name &optional (arg-1 no-arg) (arg-2 no-arg) (arg-3 no-arg))
  (let ((process-description? (description-of-process name)))
    (cond (process-description?
	   (let* ((function (process-description-function process-description?))
		  (initializer (process-description-initializer process-description?))
		  (state-block (call-per-number-of-actual-args
				 funcall 1 initializer arg-1 arg-2 arg-3))
		  (process (make-process-1)))
	     (setf (process-name process) name
		   (process-function process) function
		   (process-status process) 'waiting
		   (process-state-block process) state-block)
	     (setq background-processes (nconc background-processes
					       (gensym-list process)))
	     (maybe-schedule-service-workstations-final)
	     process))
	  (t
	   #+development (warn "There is no process description for ~s" name)))))


 
;;; The function `call-background-process' gives the process one quantum of
;;; runtime.  We do not handle abnormal exits from the process bodies, so kill
;;; any process which tries to do so.  Presumably, in production code, we'll
;;; never unwind through here (except due a G2 abort, for which there are no
;;; guarentees, anyways).

(defun call-background-process (process)
  (when (eq (process-status process) 'waiting)
    (setf (process-status process) 'running)

    ;; We assume that the process function does not throw.
    (let ((naughty-process t))
      (unwind-protect-for-development call-background-process
	  (with-simple-restart (abort "Kill this background process ~a" process)
	    (let ((current-background-process process))

	      (funcall-simple-compiled-function
		(process-function process)
		process
		(process-state-block process))

	      (setq naughty-process nil)
	      (case (process-status process)
		(running
		 (setf (process-status process) 'waiting))
		(done
		 (kill-background-process process)))))

	(when naughty-process
	  #+development
	  (warn "Killing background process ~s.  We simply cannot allow throws through here."
		(process-name process))
	  (kill-background-process process))))))



;;; The function `schedule-task-for-background-processes' schedules a task
;;; to work on background processes, if there are any processes and there is
;;; not already a task.

(defun schedule-task-for-background-processes ()
  (when (and background-processes
	     (null background-processes-task))
    (let ((task-priority
	    (printing-priority printer-setup))
	  (task-start-time
	    (g2-future-interval 0)))			    ; Random.
       (with-future-scheduling
	   (background-processes-task task-priority task-start-time nil nil t)
	 (service-background-processes)))))



;;; The function `service-background-processes' gives cycles to heavy-weight
;;; background processes until the current time-slice expires.  It's called
;;; both from the task (at some priority) AND from service-workstations.

(defun-simple service-background-processes ()
  ;; Service them until time slice expires.
  (loop for process in background-processes
	do (call-background-process process)
    	until (time-slice-expired-p))

  ;; Schedule a new task.
  (when background-processes-task
    ;; Is this the right way to do this?
    (cancel-task background-processes-task)
    (setq background-processes-task nil))
  
  (when background-processes
    (schedule-task-for-background-processes)))



;;; The function `kill-background-process' removes the process from the active list,
;;; and reclaims the process object and its state-block.

(defun kill-background-process (process)
  (setf (process-status process) 'dead)
  (setq background-processes (delete-gensym-element process background-processes))
  (funcall-simple-compiled-function
    (process-description-reclaimer (description-of-process (process-name process)))
    (process-state-block process))
  (reclaim-process process)
  nil)



(defun-for-macro heuristicate-variable-type (variable-name)
  (let* ((string (string variable-name))
	 (length (length string)))
    (cond ((and (> length 3)
		(string-search "-MF" string :start2 (- length 3)))
	   'managed-float)
	  (t
	   nil))))

(defun-for-macro reclaimer-for-variable-type (name type)
  (let ((type (or type (heuristicate-variable-type name))))
    (case type
      (managed-float 'reclaim-managed-float)
      (printing-list 'reclaim-printing-list)
      (slot-value 'reclaim-slot-value)
      (slot-value-list 'reclaim-slot-value-list)
      (block 'reclaim-snapshot-of-block)
      (readonly nil)
      (copied nil)					    ; Eq to something else which IS reclaimed.
      (t
       ;; Else, the type is the reclaimer.
       type))))





;;; The macro `define-process' defines the state variables and "continuation"
;;; for a named type of process.  Within the body of the continuation, you can
;;; use the macros `allow-other-processing', `return-from-processing', and
;;; `exit-process'.

;; We could allow any predicate within allow-other-proc. For example,
;; (or (time-slice-expired-p) pending user-notifications)

(defmacro define-process (name-and-options lambda-list state &body body)
  (let* ((name (car-or-atom name-and-options))
	 (options (cdr-or-atom name-and-options))
	 (exit-hook (getf options :exit-hook))
	 (function-name (build-ab-symbol 'work 'on name))
	 (state-name  (build-ab-symbol name 'process 'state 'block))
	 (constructor-name (build-ab-symbol 'make state-name))
	 (shallow-reclaimer-name (build-ab-symbol 'reclaim state-name "1"))
	 (reclaimer-name (build-ab-symbol 'reclaim state-name))
	 (initializer-name (build-ab-symbol 'initialize state-name))
	 (state-variables (loop for (name value type) in state
				unless (eq type 'temporary)
				  collect (list name type (build-ab-symbol state-name name))))
	 (state-variable-names (loop for (name) in state-variables
				     collect name))
	 (block-valued-state-variables (loop for (name type accessor) in state-variables
					     when (eq type 'block)
					       collect (list name type accessor))))
    `(progn
       (define-structure ,state-name ()
	 (:constructor ,constructor-name)
	 (:reclaimer ,shallow-reclaimer-name)
	 (:managed t)
	 (:conc-name t)
	 ,@state-variable-names)

       ;; defvar (some) of the state variables?
       ;; Or, user can defvar them by hand.  We just bind them.
       
       (defun-simple ,initializer-name ,lambda-list
	 (with-temporary-gensym-float-creation process-printing 
	   (let* ((state-block (,constructor-name))
		  ,@(loop for (name value type) in state
			  when (eq type 'block)		    ; Snapshot blocks.
			    do (setq value `(make-snapshot-of-block ,value))
			  collect `(,name ,value)))
	     (setf ,@(loop for (name type accessor) in state-variables
			   collect `(,accessor state-block)
			   collect name))
	     state-block)))
       
       (defun-simple ,reclaimer-name (state-block)
	 ,@(loop for (name type accessor) in state-variables
		 as reclaimer = (reclaimer-for-variable-type name type)
		 when reclaimer
		   collect `(,reclaimer (,accessor state-block)))
	 ;; Reclaim each state var, then the block itself.
	 (,shallow-reclaimer-name state-block))
       
       (defun ,function-name (process state-block)
	 (declare simple allowing-unwind)
	 (let (,@(loop for (name type accessor) in state-variables
		       if (eq type 'block)
			 collect `(,name (block-of-snapshot (,accessor state-block)))
		       else
			 collect `(,name (,accessor state-block)))
		 (background-process-return-status 'exit))
	   
	   ;; Validate frame serial numbers.
	   (cond ((not (and ,@(loop for (name type accessor) in block-valued-state-variables
				    collect `(snapshot-of-block-valid-p (,accessor state-block)))))
		  (setq background-process-return-status 'invalid-blocks))
		 (t
		  ,@body))

	   (case background-process-return-status
	     (return
	       (setf ,@(loop for (name type accessor) in state-variables
			     unless (eq type 'block)	    ; Assume block-valued state-vars do not change!!
			       collect `(,accessor state-block) and
			       collect name)))
	     ((invalid-blocks exit)
	      ;; The state block is reclaimed by our caller.
	      ,@(when exit-hook `(,exit-hook background-process-return-status))
	      (setf (process-status process) 'done)))))

       #+development
       (make-process-description ',name ',function-name ',initializer-name ',reclaimer-name)
       #-development
       (make-process-description ',name #',function-name #',initializer-name #',reclaimer-name))))



;;; The macro `with-other-processing-allowed' locally defines the macros
;;; allow-other-processing and friends.  It is separate from define-process
;;; just so that the user can control the scope of exit-process.

(defmacro with-other-processing-allowed (options &body body)
  (declare (ignore options))
  `(macrolet ((return-from-process ()
		`(progn (setq background-process-return-status 'return)
			(return-from background-process)))
	      (exit-process ()
		`(progn (setq background-process-return-status 'exit)
			(return-from background-process)))
	      (allow-other-processing ()
		`(when (time-slice-expired-p)		    ; Note A.
		   (return-from-process))))
     (block background-process
       ,@body)))

;; Note A: this was testing drawing-time-slice-expired-p, but since that macro depends
;; on current-drawing-priority, and that variable is not always bound at the time we
;; are asking if the time slice is expired, we have to use this other function.


;;;; Utilities for print-workspace

;;; The actual menu command that prints a workspace is simple, except
;;; for all the mechinism that needs to be set up before you can
;;; actually print.  There are three aspects that make it complex.
;;; First, setting up the gensym window data structures necessary
;;; to do the printing.  Second setting up the output stream that
;;; is then spooled to the printer. Fourth the pagination issues.
;;; Finally all the little variations caused by the the settings
;;; the user is provided in the page setup system table.

;;; The routines, and macros, in this section implement all this
;;; mechinism.



;;; `make-printing-stream' binds the output stream for the printer, and upon exit
;;; it sends that file to the printer to be printed.  Upon entry it decides what
;;; namestring use for the printed output.   Spool-file-to-printer-for-this-platform 
;;; is used to do the spooling.  Instantiate-file-template is used to select the
;;; namestring.

(defun make-printing-stream (format)
  (unless (eq format 'native)
    (let* ((requested-filename? (printer-setup-particular 'pathname))
	   (filename?
	     (if requested-filename?
		 (copy-text-string requested-filename?)
		 (generate-output-filename-for-printing format)))
	   (printing-stream?
	     (when filename?
	       (case format
		 (postscript (g2-stream-open-for-output filename?))
		 (bitmap (g2-stream-open-for-binary-output filename?))))))
      (when (and filename? (null printing-stream?))
	(notify-user "Unable to print because opening the output file (~S) failed." filename?))
      (when filename?
	(reclaim-text-string filename?))
      printing-stream?)))


;;; The function `generate-output-filename-for-printing' returns the pathname of
;;; a new file generated from the spooled-filename-template.

(defun generate-output-filename-for-printing (format)
  (let ((spooled-filename-template (printer-setup-particular 'spooled-filename-template))
	(filename? nil))
    (cond ((get-particulars-of-frame-note-if-any
	     'printer-file-template-is-misformed
	     printer-setup)
	   (notify-user "Unable to print because the print file template was bad."))
	  ((get-particulars-of-frame-note-if-any
	     'printer-paper-size-is-unreasonable
	     printer-setup)
	   (notify-user "Unable to print because the paper size in the printer-setup system table is invalid."))

	  ((not (setq filename? (instantiate-file-template spooled-filename-template format)))
	   (notify-user 
	     "Unable to print.  ~
                No available file name was found after trying ten variations ~
                   of the filename suggested in the printer-setup system table.  ~
                You may need to delete old print files.  ~
                If you try again ten more names will be tried.")))
    filename?))



(defun close-printing-stream (printing-stream)
  (let ((true-pathname-of-spooled-file
	  ;; Gensym-truename is warrentied to always work
	  ;; on an open stream.
	  (gensym-truename printing-stream)))
    (g2-stream-close printing-stream)
    (when (eq printing-format 'postscript)
      (spool-file-to-printer-for-this-platform true-pathname-of-spooled-file))
    (reclaim-gensym-pathname true-pathname-of-spooled-file)))

;; This is not designed to handle platforms that would prefer you stream your printing
;; output straight to the printer.




;;; `make-gensym-window-for-printing' creates the gensym window thru which the printing
;;; will take place.  It is here that we implement the color mapping the user
;;; requested.

;;; The window created is marked up so that the dispatching in ICP message handlers
;;; will pass all drawing thru to the routines defined in the printing handler section
;;; above.

(defun make-gensym-window-for-printing (window-width window-height)
  (let ((window-parameters-plist
	  (make-window-parameters-plist nil)))
    (mutate-gensym-plist window-parameters-plist 'stored-raster-type-for-window 'printer)
    (mutate-gensym-plist window-parameters-plist 'scratchpad-raster-type-for-window 'printer)
    (mutate-gensym-plist window-parameters-plist 'type-of-gensym-window 'printer)

    ;; For multipage printing, it is important that we can draw right up to the window edges.
    (mutate-gensym-plist window-parameters-plist 'width-of-window-border 0)

    (let ((pane-layout 
	    (getfq-macro window-parameters-plist 'pane-layout))
	  (color-description-plist?
	    (getfq-macro window-parameters-plist 'color-description-plist?)))
      
      ;; Smash the pane layout.   Was (DETAIL-PANE) Becomes (DETAIL-PANE 0 0)
      (when (consp pane-layout)
        (setf (cdr pane-layout) (gensym-list 0 0)))

      (when color-description-plist?
	(reclaim-gensym-tree color-description-plist?))

      ;; This used to include some permanent conses.
      (mutate-gensym-plist window-parameters-plist 'color-description-plist?
	(let ((color-conv (printer-setup-particular 'color-conversion)))
	  (cond ((or (eq printing-format 'native)
		     (eq printing-format 'bitmap))
		 (cond ((eql 'black-and-white color-conv)
			(make-monochrome-color-description-plist 0 (rgb 255 255 255)))
		       ((eql 'grays color-conv)
			(make-gray-true-color-description-plist))
		       (t
			(make-true-color-description-plist))))
		((eql 'black-and-white color-conv)
		 (make-monochrome-color-description-plist 1 0))
		(t
		 (make-printing-color-description-plist)))))

      (let ((gensym-window-for-printing
	      (make-or-revise-window
		nil          
		0				; left-edge-in-window          
		0				; top-edge-in-window          
		window-width			; right-edge-in-window
		window-height		        ; bottom-edge-in-window 
		nil				; native-window?          
		nil				; raster-for-native-window?          
		window-parameters-plist)))
	;; Wedge it into this workstation. This seems racy?
	(setf (workstation-this-is-on gensym-window-for-printing) 
	      (if servicing-workstation?
		  current-workstation
		  (car workstations-in-service)))
	(lay-out-window gensym-window-for-printing)

	;; Paint mode please!
	(setf (drawing-transfer-mode-of-gensym-window gensym-window-for-printing)
	      :paint-infered-from-xor)

	gensym-window-for-printing))))


(defun reclaim-gensym-window-for-printing (printing-window)
  (setf (workstation-this-is-on printing-window) nil)
  (reclaim-window-for-workstation printing-window))



(def-substitution-macro get-image-plane-for-printing (workspace gensym-window)
  (let ((pane (detail-pane gensym-window)))
    (for-workstation ((workstation-this-is-on gensym-window)) ; see note
      (get-available-image-plane pane
				 (lookup-frame-description-reference-of-block? workspace)
				 nil))))

;; Note: needed the for-workstation here for the first time now because
;; default-frame-style-of-block?, called indirectly from here, now uses
;; for-workstation variable new-g2-classic-ui-p. (MHD 10/6/99)


;;; The function `setup-image-plane-for-printing' creates or modifies an image
;;; plane for the workspace on the printing window, and enqueues a request to
;;; draw a workspace, offset by the given amount from the workspace origin.  It
;;; returns the image-plane.

(defun setup-image-plane-for-printing (workspace x-offset y-offset)
  (let ((image-plane (get-image-plane-for-printing workspace gensym-window-for-printing)))

    ;; A minimal subset of the stuff done by show-or-hide-1.
    (associate-workspace-and-image-plane workspace image-plane)
    (setf (image-x-scale image-plane) (normalized-scale)
	  (image-y-scale image-plane) (normalized-scale))
    (setf (x-origin-of-workspace-in-window-of-image-plane image-plane)
	  (-r (left-edge-of-window gensym-window-for-printing)
	      (+r (left-edge-of-block workspace) x-offset)))
    (setf (y-origin-of-workspace-in-window-of-image-plane image-plane)
	  (-r (top-edge-of-window gensym-window-for-printing)
	      (+r (top-edge-of-block workspace) y-offset)))
    (set-up-edges-for-image-plane image-plane)
    (recompute-visible-regions-for-pane (pane-for-image-plane image-plane))

    ;; Decache all graph renderings for the printing window, so that they will
    ;; be recreated for each page. This means that a graph, chart, or
    ;; trend-chart which is split across pages and is updating may look
    ;; different on each page! This is the cost of doing native printing in one
    ;; pass.
    (when (native-printing-p)
      (decache-all-graph-renderings-on-window gensym-window-for-printing))

    ;; Ordinarily, printing image-planes are not allowed to receive any drawing
    ;; tasks.  Bind the flag to T to allow this one in.
    (let ((allow-invalidate-on-printing-window-p t))
      (invalidate-image-plane image-plane))
    
    image-plane))



(defmacro with-output-to-printing-window (options &body body)
  (declare (ignore options))
  `(with-raw-window-transform-and-draw-area (gensym-window-for-printing)
     (on-window-without-drawing (gensym-window-for-printing)

       ;; Printing always paints
       (let ((current-drawing-transfer-mode :paint-infered-from-xor))

	 ;; Printing always uses scheduled drawing.
	 (with-deferred-drawing ()
	   (let ((current-scratchpad-raster-type 'printer) ; Effectively do on-scratchpad.
		 (current-draw-paper-p nil)) ; Suppress all ASAP bg clears for printing.
	     ,@body))))))


;;;; Native Printing


;;; Native printing works by running the usual postscript printing code, with a
;;; few changes, but with a new icp-message-handler-array, which directs drawing
;;; calls to new handlers defined with `def-for-native-printing'. G2 thinks that
;;; it is drawing to the usual printing window until the last possible moment,
;;; capture a drawing call and redirect it to the `output-window-for-printing?'
;;; (via `on-native-printer-with-drawing').

;;; As a result of this slight deception, during native printing G2 is usually in a
;;; context where the current-window is the printer window, but current-icp-port
;;; and friends are bound to the output window port (if it is ICP).

;;; Native printing uses just one pass instead of the two passes used by postscript
;;; printing. The main reason we do this, besides efficiency, is because there is
;;; not a convenient way to capture icons in a scalable, replayable way on Windows,
;;; as postscript printing did with postscript procedures. Although we could cache
;;; in-memory EMFs for icons, we need to be able to replay them with various layer
;;; colors rebound, and it is not immediate how to do that with EMFs (maybe
;;; palettes would help). So, while we print in one pass, we play the drawing for
;;; every instance of every icon over the wire, with no caching on the TW side.

;;; Printing in one pass also requires us to hook into some drawing functions
;;; before one of our native handlers get called, to capture information. So,
;;; native printing is a little bit more invasive into the rest of G2 than
;;; postscript printing was. Grep for calls to `native-printing-p'. It also
;;; required us to decache graph renderings for each page of the printout.

;;; Todo list for native printing:
;;;  Icon caching on TW side. Use EMFs or send over the icon line drawing
;;;  Transparent GIFs (postscript printing doesn't support them either)
;;;  More accurate native text alignment and spacing
;;;  Use bitmap fonts when Arial Unicode MS is not present
;;;  Native printing for G2 (only issue is the Win32 dialogs, not printing itself)
;;;  UI for customizing the header and footer stuff on each page
;;;  Add workspace scaling and margins to the native printer dialog.
;;;  Save choice of printer with KB somehow.

(def-concept native-printing)

;; These specials are used to pass an icon's or graph's position down to the
;; scratchpad drawing routines, so that they can draw to the window in the
;; correct position.

(defvar native-printing-icon-x-in-window nil)
(defvar native-printing-icon-y-in-window nil)
(defvar native-printing-color-differences)

(defparameter native-printing-icp-message-handler-array
  (make-array #.(icp-message-handler-array-size)
	      :initial-element 'native-printing-default-icp-handler))

(defun native-printing-default-icp-handler (&optional a b c d e f g h i j k l m n o p)
  (declare (ignore a b c d e f g h i j k l m n o p)))

;;; The function `native-printing-p' is true only when are truely doing native
;;; printing, that is, printing at full resolution to a vector graphics device.
;;; It is false when printing to a bitmap, even though that uses some of the
;;; same machinery.

(defun native-printing-p ()
  (and (printing-p) (eq printing-format 'native)))

(defun postscript-printing-p ()
  (and (printing-p) (eq printing-format 'postscript)))

(defun bitmap-printing-p ()
  (and (printing-p) (eq printing-format 'bitmap)))

;;; The macro `def-for-native-printing' defines a native printing handler for a
;;; drawing-related ICP message.

(defmacro def-for-native-printing (name lambda-list &body body)
  (let ((fname (build-ab-symbol 'native-printing name)))
    `(progn
       (defun ,fname ,lambda-list ,@body)
       (setf (svref native-printing-icp-message-handler-array ',(icp-message-type-code name))
	     ',fname))))

;;; The macro `on-native-printer' runs body in a funny context where G2 continues
;;; to draw to a printer window, but we've also done a `with-icp-window' on the
;;; given gensym-window. So the body runs in sort of hybrid context. As far as G2
;;; knows, it is drawing to the usual printer window. The only difference is that
;;; current-icp-port and friends are bound. It is conceivable that some G2 code may
;;; get confused by this, but I have not found problems so far.

;;; The macro also rebinds the icp-printing-message-handler-array on the G2 side
;;; to call our native-printing handlers, and tell the output-window TW, via
;;; native-printing-begin, to redirect it's output to the native printer
;;; previously opened via native-printing-dialog.

(defmacro on-native-printer ((gensym-window) &body body)
  (avoiding-variable-capture (gensym-window)
    `(let ((icp-printing-message-handler-array native-printing-icp-message-handler-array))
       (case (type-of-gensym-window ,gensym-window)
	 (x11-window
	  ;; If it's a local window, then we're doing bitmap printing.
	  (unwind-protect-for-development on-native-printer
	      (progn
		(c-x11-draw-offscreen (native-window? ,gensym-window)
				      (pixmap-pointer bitmap-for-printing?)
				      1)
		,@body)
	    (c-x11-draw-offscreen (native-window? ,gensym-window) -1 0)))

	 (icp
	  (with-icp-window (,gensym-window)
	    (let ((current-window ,gensym-window))
	      (synchronize-icp-on-window-with-drawing ; Cf `on-window-with-drawing'
		current-window
		left-edge-of-draw-area top-edge-of-draw-area
		right-edge-of-draw-area bottom-edge-of-draw-area))
	    (unwind-protect-for-development on-native-printer ; TODO: needed in release?
		(progn
		  (native-printing-begin ,gensym-window)
		  ,@body)
	      (native-printing-end ,gensym-window))))))))


;;; The macro `on-native-printer-with-drawing' redirects graphics output to the ICP
;;; window output-window-for-printing?.  As a convenience, it also can take care of
;;; retrieving the correct color-value for drawing icon layers (in which case the
;;; passed-in color-value is ignored).

(defmacro on-native-printer-with-drawing ((&key convert) &body body)
  (when convert
    ;; If CONVERT is supplied, it must be a symbol naming a variable. We lookup the
    ;; current color-difference for the current icon region, and setq the variable
    ;; to the inferred color-value. The body is then run only if the
    ;; color-difference was not transparent.
    (setq body
	  `((when (and printing-icon-current-region-index?
		       ;; Paranoid code copied from fetch-from-color-list
		       (>=f printing-icon-current-region-index? 0)
		       (<f printing-icon-current-region-index?
			   (length native-printing-color-differences)))
	      (let ((color-difference
		      (nth printing-icon-current-region-index?
			   native-printing-color-differences)))
		(setq ,convert
		      (if (color-difference-is-transparent-p color-difference)
			  color-difference
			  (infer-color-value-from-color-difference color-difference)))))
	    (unless (color-difference-is-transparent-p ,convert)
	      ,@body))))
  `(when (=f printing-pass-number 2)
     (let* ((current-window output-window-for-printing?)
	    (type-of-current-window (type-of-gensym-window current-window))
	    ;; current-scratchpad-raster-type gets bound in TW by
	    ;; make-region-raster-for-icon called by
	    ;; make-region-raster-according-to-messages, called by
	    ;; begin-making-icon-rendering.
	    (current-native-window?
	      (native-window? current-window))
	    (current-scratchpad-raster-type
	      (scratchpad-raster-type-for-window current-window)))
       ;; G2 has done this synchronize already but for the printing-window. Now
       ;; we need to do it for real for the output window.
       (synchronize-background-color-value)
       ,@body)))


;;;; Native Printing Draw-to-Scratchpad Handlers


;;; When drawing icon layers, color-value is always 1, so we have to pick it up
;;; from the special infer-color-value-from-color-differences. The
;;; on-native-printer-with-drawing macro does this.

(def-for-native-printing paint-solid-rectangle-in-current-scratchpad-raster
    (left top right bottom color-value)
  (on-native-printer-with-drawing (:convert color-value)
    (paint-solid-rectangle-in-current-scratchpad-raster
      left top right bottom color-value)))

(def-for-native-printing paint-line-in-current-scratchpad-raster
    (x1 y1 x2 y2 color-value paint-last-point?)
  (on-native-printer-with-drawing (:convert color-value)
    (paint-line-in-current-scratchpad-raster x1 y1 x2 y2 color-value paint-last-point?)))

(def-for-native-printing paint-arc-or-circle-in-current-scratchpad-raster
    (x1 y1 x2 y2 x3 y3 x-scale y-scale color-value circle? filled?)
  (on-native-printer-with-drawing (:convert color-value)
    (paint-arc-or-circle-in-current-scratchpad-raster
      x1 y1 x2 y2 x3 y3 x-scale y-scale color-value circle? filled?)))

(def-for-native-printing paint-filled-triangle-in-current-scratchpad-raster
    (x1 y1 x2 y2 x3 y3 color-value)
  (on-native-printer-with-drawing (:convert color-value)
    (paint-filled-triangle-in-current-scratchpad-raster
      x1 y1 x2 y2 x3 y3 color-value)))

(def-for-native-printing paint-filled-polygon-in-current-scratchpad-raster
    (unsigned-polygon-point-list color-value)
  (on-native-printer-with-drawing (:convert color-value)
    (paint-filled-polygon-in-current-scratchpad-raster
      unsigned-polygon-point-list color-value)))

(def-for-native-printing paint-wide-line-in-current-scratchpad-raster
    (x1 y1 x2 y2 color-value paint-last-point? line-width)
  (on-native-printer-with-drawing (:convert color-value)
    (paint-wide-line-in-current-scratchpad-raster
      x1 y1 x2 y2 color-value paint-last-point? line-width)))

(def-for-native-printing paint-point-in-current-scratchpad-raster (x y color-value)
  (on-native-printer-with-drawing (:convert color-value)
    (paint-point-in-current-scratchpad-raster
      x y color-value)))

(def-for-native-printing paint-image-in-current-scratchpad-raster
    (image-data x-in-icon y-in-icon x-scale y-scale
		width height rotation quality draw-or-burn)
  (on-native-printer-with-drawing (:convert draw-or-burn)
    (paint-image-in-current-scratchpad-raster
      image-data x-in-icon y-in-icon x-scale y-scale width height rotation
      quality draw-or-burn)))

(def-for-native-printing orient-and-paint-line-of-text-to-current-scratchpad-raster
    (clipped-left-edge clipped-top-edge	; Clip rectangle within raster, unit-scale.
		       clipped-right-edge clipped-bottom-edge
		       normalized-width normalized-height ; Size of icon, unit scale
		       text-line text-orientation
		       icon-orientation
		       word-spacing
		       font-map color-value
		       normalized-x-scale normalized-y-scale
		       ;; Notice these args are misnamed in other versions of
		       ;; this function. These are in *scaled* scratchpad
		       ;; coordinates.
		       left-edge-of-line-of-text-in-scratchpad-raster
		       baseline-in-scratchpad-raster)
  (cond ((eq printing-format 'native)
	 (unless (eq icon-orientation 'normal)	; Copied from render-character-image
	   (orient-points-for-icon
	       icon-orientation
	       (delta-x-in-window normalized-width normalized-x-scale)
	       (delta-y-in-window normalized-height normalized-y-scale)
	     clipped-left-edge
	     clipped-top-edge
	     clipped-right-edge
	     clipped-bottom-edge
	     left-edge-of-line-of-text-in-scratchpad-raster
	     baseline-in-scratchpad-raster)
	   (psetf clipped-left-edge (minr clipped-left-edge clipped-right-edge)
		  clipped-right-edge (maxr  clipped-left-edge clipped-right-edge)
		  clipped-top-edge (minr clipped-top-edge clipped-bottom-edge)
		  clipped-bottom-edge (maxr clipped-top-edge clipped-bottom-edge)))
	 (multiple-value-bind (angle reflect)
	     (case icon-orientation
	       ((nil normal) (values 0 0))
	       (clockwise-90 (values -90 0))
	       (clockwise-180 (values 180 0))
	       (clockwise-270 (values 90 0))
	       (reflected (values 00 1))
	       (reflected-clockwise-90 (values -90 1))
	       (reflected-clockwise-180 (values 180 1))
	       (reflected-clockwise-270 (values 90 1))
	       (t (dwarn "Unknown reflection and rotation: ~s" icon-orientation)
		  (values 0 0)))
	   (on-native-printer-with-drawing (:convert color-value)
	     (paint-line-of-text-in-current-window	; New ICP message.
	       (+r native-printing-icon-x-in-window clipped-left-edge)
	       (+r native-printing-icon-y-in-window clipped-top-edge)
	       (+r native-printing-icon-x-in-window clipped-right-edge)
	       (+r native-printing-icon-y-in-window clipped-bottom-edge)
	       text-line word-spacing
	       (car font-map)
	       color-value
	       (*f angle 10)
	       reflect				; Flags bit-0 = reflect-left-right-p
	       normalized-x-scale normalized-y-scale
	       (+r native-printing-icon-x-in-window left-edge-of-line-of-text-in-scratchpad-raster)
	       (+r native-printing-icon-y-in-window baseline-in-scratchpad-raster)))))
	(t
	 (on-native-printer-with-drawing (:convert color-value)
	   (orient-and-paint-line-of-text-to-current-scratchpad-raster
	     clipped-left-edge clipped-top-edge
	     clipped-right-edge clipped-bottom-edge
	     normalized-width normalized-height
	     text-line text-orientation
	     icon-orientation
	     word-spacing
	     font-map color-value
	     normalized-x-scale normalized-y-scale
	     left-edge-of-line-of-text-in-scratchpad-raster
	     baseline-in-scratchpad-raster)))))


(def-for-native-printing paint-from-line-of-text-to-current-scratchpad-raster
    (clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge
		       text-line word-spacing font-map
		       color-value
		       x-scale y-scale
		       left-edge-of-line-of-text-in-window baseline-in-window)
  (cond ((eq printing-format 'native)
	 (on-native-printer-with-drawing ()		; Not used by icons, so don't do convert.
	   (paint-line-of-text-in-current-window	; New ICP message.
	     (+r native-printing-icon-x-in-window clipped-left-edge)
	     (+r native-printing-icon-y-in-window clipped-top-edge)
	     (+r native-printing-icon-x-in-window clipped-right-edge)
	     (+r native-printing-icon-y-in-window clipped-bottom-edge)
	     text-line word-spacing
	     (car font-map)
	     color-value
	     0					; Angle
	     0					; Flags
	     x-scale y-scale
	     (+r native-printing-icon-x-in-window left-edge-of-line-of-text-in-window)
	     (+r native-printing-icon-y-in-window baseline-in-window))))
	(t
	 (on-native-printer-with-drawing ()
	   (paint-from-line-of-text-to-current-scratchpad-raster
	     clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge
	     text-line word-spacing font-map
	     color-value
	     x-scale y-scale
	     left-edge-of-line-of-text-in-window baseline-in-window)))))



;;;; Native Printing Draw-to-Window Handlers


(def-for-native-printing add-from-icon-rendering-to-current-window
    (subtract-instead? clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge
		       color-difference icon-rendering
		       left-edge-in-icon-rendering top-edge-in-icon-rendering
		       list-of-color-differences)
  (cond ((eq printing-format 'native)
	 (add-from-icon-rendering-to-current-window-2
	   subtract-instead? clipped-left-edge clipped-top-edge
	   clipped-right-edge clipped-bottom-edge
	   color-difference icon-rendering
	   left-edge-in-icon-rendering top-edge-in-icon-rendering
	   list-of-color-differences))
	(t
	 (on-native-printer-with-drawing ()
	   (add-from-icon-rendering-to-current-window
	     subtract-instead? clipped-left-edge clipped-top-edge
	     clipped-right-edge clipped-bottom-edge
	     color-difference icon-rendering
	     left-edge-in-icon-rendering top-edge-in-icon-rendering
	     list-of-color-differences)))))

;; Used only for when we're actually printing to a native printer, and not to a
;; bitmap.
(defun add-from-icon-rendering-to-current-window-2
    (subtract-instead? clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge
		       color-difference icon-rendering
		       left-edge-in-icon-rendering top-edge-in-icon-rendering
		       list-of-color-differences)
  (declare (ignore subtract-instead?))
  (let* ((line-drawing (line-drawing-description-for-rendering? icon-rendering))
	 (width (width-of-rendered-icon icon-rendering))
	 (height (height-of-rendered-icon icon-rendering))
	 (variable-overrides (computed-values-plist icon-rendering))
	 (polychrome-header? (get-polychrome-header-if-any line-drawing))
	 (icon-color-pattern
	   (or (rest polychrome-header?)
	       '((foreground . foreground))))
	 (line-drawing-description-following-header
	   (if polychrome-header?
	       (cdr line-drawing)
	       line-drawing))
	 (native-printing-icon-x-in-window (-f clipped-left-edge left-edge-in-icon-rendering))
	 (native-printing-icon-y-in-window (-f clipped-top-edge top-edge-in-icon-rendering))
	 (native-printing-color-differences list-of-color-differences)
	 (printing-icon-current-region-index? nil))

    ;; The new ICP message paint-icon-in-current-window enters a context on TW
    ;; where the pixmap drawing routines are redirected to the printer,
    ;; translated by some offset and clipped. G2 takes care scaling and
    ;; rotation.

    (on-native-printer-with-drawing ()
      (paint-icon-in-current-window	; New ICP message.
	native-printing-icon-x-in-window native-printing-icon-y-in-window
	clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge
	1))
    (paint-one-bitmap-for-icon-on-scratchpad-raster ; Actually paints all bitmaps
      icon-color-pattern
      line-drawing-description-following-header
      width height
      (x-scale-of-rendering icon-rendering)
      (y-scale-of-rendering icon-rendering)
      (infer-color-value-from-color-difference color-difference)
      (reflection-and-rotation-of-rendering icon-rendering)
      variable-overrides
      width height
      nil)				; stipple
    (send-icp-end-message-block)))	; TODO: Assuming ICP window

(def-for-native-printing add-from-line-of-text-to-current-window
    (subtract-instead?
      clipped-left-edge clipped-top-edge
      clipped-right-edge clipped-bottom-edge
      text-line word-spacing font-map
      color-difference x-scale y-scale
      left-edge-of-line-of-text-in-window
      baseline-in-window)
  (cond ((eq printing-format 'native)
	 (on-native-printer-with-drawing ()
	   (paint-line-of-text-in-current-window	; New ICP message.
	     clipped-left-edge clipped-top-edge
	     clipped-right-edge clipped-bottom-edge
	     text-line word-spacing
	     (car font-map)			; font name
	     (infer-color-value-from-color-difference color-difference)
	     0					; angle
	     0					; charset/etc.
	     x-scale y-scale
	     left-edge-of-line-of-text-in-window baseline-in-window)))
	(t
	 ;; Bitmap printing comes here. Draw text the usual way using G2 fonts
	 ;; and cached bitmaps.
	 (on-native-printer-with-drawing ()
	   (add-from-line-of-text-to-current-window
	     subtract-instead?
	     clipped-left-edge clipped-top-edge
	     clipped-right-edge clipped-bottom-edge
	     text-line word-spacing font-map
	     color-difference x-scale y-scale
	     left-edge-of-line-of-text-in-window
	     baseline-in-window)))))

(def-for-native-printing paint-solid-rectangle-in-current-window
    (clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge color-value)
  (on-native-printer-with-drawing ()
    (paint-solid-rectangle-in-current-window
      clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge color-value)))

(def-for-native-printing add-solid-rectangle-to-current-window
    (subtract-instead? clipped-left-edge
		       clipped-top-edge clipped-right-edge
		       clipped-bottom-edge color-difference)
  (on-native-printer-with-drawing ()
    (add-solid-rectangle-to-current-window
      subtract-instead?
      clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge
      color-difference)))

(def-for-native-printing add-upward-sloping-line-to-current-window
    (subtract-instead? clipped-left-edge
		       clipped-top-edge clipped-right-edge
		       clipped-bottom-edge color-difference
		       left-end-x right-end-y right-end-x left-end-y)
  (on-native-printer-with-drawing ()
    (add-upward-sloping-line-to-current-window
      subtract-instead?
      clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge
      color-difference
      left-end-x right-end-y right-end-x left-end-y)))

(def-for-native-printing add-downward-sloping-line-to-current-window
    (subtract-instead? clipped-left-edge
		       clipped-top-edge clipped-right-edge
		       clipped-bottom-edge color-difference
		       left-end-x left-end-y right-end-x right-end-y)
  (on-native-printer-with-drawing ()
    (add-downward-sloping-line-to-current-window
      subtract-instead?
      clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge
      color-difference
      left-end-x left-end-y right-end-x right-end-y)))

(def-for-native-printing add-wide-polyline-to-current-window
    (clipped-left-edge clipped-top-edge
		       clipped-right-edge clipped-bottom-edge
		       color-difference width style dashes vertices)
  (on-native-printer-with-drawing ()
    (add-wide-polyline-to-current-window
      clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge
      color-difference
      width style dashes vertices)))

(def-for-native-printing add-polygon-to-current-window
    (clipped-left-edge clipped-top-edge
		       clipped-right-edge clipped-bottom-edge
		       line-color-difference line-width fill-color-difference fill-pattern
		       vertices)
  (on-native-printer-with-drawing ()
    (add-polygon-to-current-window
      clipped-left-edge clipped-top-edge
      clipped-right-edge clipped-bottom-edge
      line-color-difference line-width fill-color-difference fill-pattern
      vertices)))

(def-for-native-printing add-ellipse-to-current-window
    (clipped-left-edge clipped-top-edge
		       clipped-right-edge clipped-bottom-edge
		       line-color-difference line-width fill-color-difference fill-pattern
		       x1 y1 x2 y2)
  (on-native-printer-with-drawing ()
    (add-ellipse-to-current-window
      clipped-left-edge clipped-top-edge
      clipped-right-edge clipped-bottom-edge
      line-color-difference line-width fill-color-difference fill-pattern
      x1 y1 x2 y2)))

;; Only needed if we allow native printing of entire G2 window.
(def-for-native-printing copy-from-tiling-pattern-to-current-window
    (left-edge top-edge right-edge bottom-edge tiling-pattern)
  (on-native-printer-with-drawing ()
    (copy-from-tiling-pattern-to-current-window
      left-edge top-edge right-edge bottom-edge tiling-pattern)))

(def-for-native-printing paint-image-in-current-window
    (image-data x-in-window y-in-window	; Position of UL corner of image, window coor.
		left top right bottom	; Clipping rectangle (window coor)
		x-scale y-scale
		rotation		; Unused
		quality			; NIL or TILED
		foreground-color background-color) ; Only for bitmaps
  (on-native-printer-with-drawing ()
    (paint-image-in-current-window	; -> draw-valid-image-on-window, draw-tiled-image-on-window
      image-data x-in-window y-in-window
      left top right bottom
      x-scale y-scale rotation quality
      foreground-color background-color)))

(def-for-native-printing paint-icon-background-image-in-current-window
    (image-data x-in-window y-in-window
		draw-area-left draw-area-top draw-area-right draw-area-bottom
		x-scale y-scale
		rotation
		quality
		foreground-color background-color
		image-left-offset-in-ws image-top-offset-in-ws
		rotated-width-in-ws rotated-height-in-ws)
  (on-native-printer-with-drawing ()
    (paint-icon-background-image-in-current-window
      image-data x-in-window y-in-window
      draw-area-left draw-area-top draw-area-right draw-area-bottom
      x-scale y-scale rotation quality
      foreground-color background-color
      image-left-offset-in-ws image-top-offset-in-ws
      rotated-width-in-ws rotated-height-in-ws)))

(def-for-native-printing update-graph-dateline (dateline erase-dateline graph-rendering)
  (on-native-printer-with-drawing ()
    (update-graph-dateline dateline erase-dateline graph-rendering)))

(def-for-native-printing clear-data-clipping-rectangles ()
  (on-native-printer-with-drawing ()
    (clear-data-clipping-rectangles)))

(def-for-native-printing update-graph-data-extrema
    (left-edge top-edge right-edge bottom-edge)
  (on-native-printer-with-drawing ()
    (update-graph-data-extrema left-edge top-edge right-edge bottom-edge)))

(def-for-native-printing update-ring-raster-for-graph-given-color-values
    (graph-rendering number-of-rasters-needed)
  (on-native-printer-with-drawing ()
    (update-ring-raster-for-graph-given-color-values
      graph-rendering
      number-of-rasters-needed)))

(def-for-native-printing add-from-graph-rendering-to-current-window
    (subtract-instead? clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge
		       grid-background-color-value graph-rendering
		       left-edge-in-graph-rendering top-edge-in-graph-rendering
		       color-value color-values-for-rasters?)
  (when (bitmap-printing-p)		; Native printing handles this via vector drawing.
    (on-native-printer-with-drawing ()
      (add-from-graph-rendering-to-current-window
	subtract-instead? clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge
	grid-background-color-value graph-rendering
	left-edge-in-graph-rendering top-edge-in-graph-rendering
	color-value color-values-for-rasters?))))

(def-for-native-printing paint-icon-onto-graph-raster
    (icon-rendering clip-left clip-top clip-right
		    clip-bottom origin-left origin-top
		    color-value)
  (let ((current-background-color-value 0)
	;; Only monochrome icons are allowed as plot markers. See
	;; paint-icon-as-plot-marker
	(native-printing-color-differences (gensym-list color-value)))
    (add-from-icon-rendering-to-current-window
      nil
      (+r clip-left native-printing-icon-x-in-window)
      (+r clip-top native-printing-icon-y-in-window)
      (+r clip-right native-printing-icon-x-in-window)
      (+r clip-bottom native-printing-icon-y-in-window)
      color-value
      icon-rendering
      (-r clip-left origin-left)	; A guess.
      (-r clip-top origin-top)
      native-printing-color-differences)
    (reclaim-gensym-list native-printing-color-differences)))


;;;; Bitmap Printing

;;; The function `print-workspace-as-image' starts a background printing process
;;; to print the given workspace as a bitmap of the given format to the given
;;; (server-side) pathname.

(defun get-dpi-value-from-user-settings () ; Added by SoftServe
  (let* ((scaling (printer-workspace-scaling))
         (dpi (coerce-fixnum-to-gensym-float (car scaling)))
         (k (case (nth 1 scaling)
              (inch 1.0d0)
              (inches 1.0d0)
              (millimeter 25.4d0)
              (millimeters 25.4d0)
              (mm 25.4d0)
              (centimeter 2.54d0)
              (centimeters 2.54d0)
              (cm 2.54d0)
              (feet 0.083d0)
              (foot 0.083d0)
              (t 1.0d0))))
    #+development  
    (format t "Print-scaling-unit: ~S ~%" (nth 1 scaling))
    (round (*e dpi k))))

(defun-simple get-property-for-printing (workspace property)
  (let* ((frame-description-reference
	  (lookup-frame-description-reference-of-block? workspace))
	 (frame-border-width 0))
    (loop for instruction in (frame-description-of-frame-description-reference frame-description-reference)
	  when (eq 'border (first instruction))
	    do (loop for (kind nil size) in (rest instruction)
		     when (eq kind 'frame)
		       do (incff frame-border-width size)))
    (if (and (page-economy-mode printer-setup)
	     (or (null (frame-style workspace))
		 (eq frame-description-reference
		     (get-default-workspace-frame-description-reference))))
      (case property
	(border-width frame-border-width)
	(width (width-of-block workspace))
	(height (height-of-block workspace)))
      (case property
	(border-width frame-border-width)
	(width (+f (width-of-block workspace) frame-border-width frame-border-width))
	(height (+f (height-of-block workspace) frame-border-width frame-border-width))))))

(defun print-workspace-as-image (workspace pathname? format quality)
  (let* ((gensym-window system-window)	; Want local window in all cases.
	 (width (get-property-for-printing workspace 'width))
	 (height (get-property-for-printing workspace 'height))
         (dpi (get-dpi-value-from-user-settings))
         (plist (nconc
		  (gensym-list 'x-dpi dpi 'y-dpi dpi
			       ;; Addressable and printable area in dots
			       'physical-width width 'physical-height height
			       'width width 'height height
			       'x-offset 0 'y-offset 0
			       'left-margin (gensym-list 0 'inch)
			       'top-margin (gensym-list 0 'inch)
			       'right-margin (gensym-list 0 'inch)
			       'bottom-margin (gensym-list 0 'inch)
			       'printer format           ; Random
			       'quality quality
			       'from-page 1 'to-page 1)
		  (if pathname?
		      (gensym-list 'pathname (copy-text-string pathname?))))))
    (print-workspace workspace gensym-window plist)
    (reclaim-gensym-tree-with-text-strings plist)))


;;; The function `create-bitmap-for-printing' returns a PIXMAP structure, or NIL
;;; on failure. It is a special bitmap not used for any other purpose, which we
;;; get by calling c-x11-create-bigmap. The reason for this is simply because
;;; the bitmap may be quite large, so we want to use a DIB Section on Windows.

(defun create-bitmap-for-printing (gensym-window width height)
  (let* ((depth
	   (if (or (win32-window-p gensym-window)
		   (>f (window-screen-depth gensym-window) 8))
	       24 8))
	 (raster
	   (c-x11-create-bigmap (native-window? gensym-window) width height depth)))
    (cond ((>=f raster 0)
	   (let ((pixmap? (make-pixmap width height depth raster)))
	     ;; GENSYMCID-1171 Print workspace makes the whole image black
	     ;;   Clear the pixmap background to white,so when `page-economy-mode' is true,
	     ;;   G2 will not print the image with weird black background.
	     (when pixmap?
	       (with-raw-window-transform-and-draw-area (gensym-window)
		 (on-window-without-drawing (gensym-window)
		   (setq current-background-color-value (color-value-for-black))
		   (setq current-drawing-transfer-mode :paint-infered-from-xor) ; Force paint mode.
		   (on-window-with-drawing (gensym-window)
		     (c-x11-draw-offscreen current-native-window? (pixmap-pointer pixmap?) 1)
		     (draw-solid-rectangle 0 0 (pixmap-width pixmap?) (pixmap-height pixmap?)
					   (color-value-for-white))
		     (c-x11-draw-offscreen current-native-window? 0 0)))))
	     pixmap?))
	  (t
	   (notify-user-at-console "Unable to allocate ~dx~dx~d bitmap."
				   width height depth)
	   nil))))

;; TODO: If we implement banding, then we don't need a huge bitmap.

(defun filetype-for-print-format (format)
  (case format
    (postscript #w"ps")
    (bitmap #w"jpg")))			; TODO: assuming bitmap => JPEG

;;; The gensym-c-function `c-x11-create-bigmap' is used to create pixmaps in
;;; user-space memory. Only for bitmap printing.

(def-gensym-c-function c-x11-create-bigmap
    (:pointer "g2ext_create_bigmap")
  ((:pointer gensym-x-window)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int depth)))

;;; The gensym-c-function `c-x11-compress-image' writes pixmap to stream as a
;;; JPEG/JFIF compressed image.

(def-gensym-c-function c-x11-compress-image
    (:fixnum-int "g2ext_compress_image")
  ((:pointer stream)			; Stream handle
   (:pointer bigmap)			; Something created by c-x11-create-bigmap
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int quality)))		; JPEG compression quality. -1 => default


;;;; Print Workspace


;;; The substitution-macro `draw-image-plane-for-printing-a-little' draws
;;; blocks from the workspace until done or until the current time slice
;;; expires.  It returns T iff it completes.

(defun-allowing-unwind draw-image-plane-for-printing-a-little (image-plane)
  (with-output-to-printing-window ()
    (with-named-dynamic-extent* on-window-with-drawing ; Effectively do on-window-with-drawing
	((drawing-on-window t))
      (case printing-format
	((native bitmap)
	 (on-native-printer (output-window-for-printing?)
	   (work-on-drawing-current-window)))
	(t
	 (work-on-drawing-current-window)))))
  (image-plane-drawing-is-completely-finished? image-plane))

;; Checks that the drawing queue is empty.  Since nothing outside the printing
;; module can enqueue tasks onto a printing-window, we know that the queue will
;; eventually become empty.

;; Changed to image-plane-drawing-is-completely-finished?, which demands that
;; the image-plane's drawing queue is empty.




;;; The function `print-workspace' starts a background process which prints the
;;; given workspace. If an output window is supplied, then we print on the host
;;; associated with than window. For a Win32 ICP window, that's to the
;;; (previously selected) native printer on that machine.

(defun print-workspace (workspace &optional output-window? plist)
  (let ((process? (make-background-process 'background-print-workspace
					   workspace output-window? plist)))
    (when process?
      (call-background-process process?)
      (schedule-task-for-background-processes))))

;; Run one cycle now, to incur any file error messages, and, to guarentee that
;; print filenames are generated in order. Also, this might be the entire job.
;; Should we limit the number of active print jobs? 


(defun are-there-graphs-on-this-workspace? (workspace)
  (loop for frame being each subblock of workspace
	thereis (frame-of-class-p frame 'graph)))



;;; The macro `enable-printing-notifications' enables messages to the logbook
;;; when scheduled printing begins or ends.

(def-substitution-macro enable-printing-notifications ()
  (not (time-slice-unlimited-p)))


(defun get-true-pathname-namestring-for-printing-stream (printing-stream?)
  (when printing-stream?
    (let ((truename (gensym-truename printing-stream)))
      (prog1 (gensym-namestring-as-text-string truename)
	(reclaim-gensym-pathname truename)))))


(def-substitution-macro truncate-mf (a-mf b-mf)
  (if (/=e (managed-float-value b-mf) 0.0)
      (truncate (managed-float-value a-mf) (managed-float-value b-mf))
      0))


(def-substitution-macro safe-ceiling (number divisor)
  (if (=f divisor 0) 0 (ceiling number divisor)))




;;;; Schedulable Print Workspace


;;; The process `background-print-workspace' starts a background process to
;;; print the given workspace. If output-window? is non-NIL, then plist is a
;;; plist of various printer properties, and instead of printing to the usual
;;; postscript file, we print "to the window". "Printing to the window" means
;;; native printing for Win32 ICP windows, and bitmap printing for local
;;; windows.

(define-process background-print-workspace (workspace output-window? plist)
  ((workspace workspace readonly)
   (workspace-serial-number (copy-frame-serial-number
			      (frame-serial-number workspace))
			    reclaim-frame-serial-number)
   (output-window-for-printing? (or output-window? system-window))
   (native-printer-information (and output-window? plist
				    (compute-native-printer-information plist))
			       reclaim-slot-value)
   (paper-size (printer-setup-particular 'paper-size))
   (paper-orientation (printer-setup-particular 'paper-orientation))
   (paper-orientation-is-portrait (eq paper-orientation 'portrait))
   (paper-size-name (postscript-paper-size-name paper-size))
   (paper-size-info (postscript-paper-size-info paper-size))
   (paper-margins (postscript-paper-margins-info paper-size))
   (actual-paper-width-mf (postscript-convert-linear-distance-to-postscript-units-mf
			    (first paper-size-info)))
   (actual-paper-height-mf (postscript-convert-linear-distance-to-postscript-units-mf
			     (second paper-size-info)))
   (paper-width-mf (if paper-orientation-is-portrait
		       actual-paper-width-mf
		       actual-paper-height-mf) copied)
   (paper-height-mf (if paper-orientation-is-portrait
			actual-paper-height-mf
			actual-paper-width-mf) copied)
   (paper-left-margin-mf (postscript-convert-linear-distance-to-postscript-units-mf
			   (first paper-margins)))
   (paper-top-margin-mf (postscript-convert-linear-distance-to-postscript-units-mf
			  (second paper-margins)))
   (paper-right-margin-mf (postscript-convert-linear-distance-to-postscript-units-mf
			    (third paper-margins)))
   (paper-bottom-margin-mf (postscript-convert-linear-distance-to-postscript-units-mf
			     (fourth paper-margins)))
   (left-margin-mf   (postscript-convert-linear-distance-to-postscript-units-mf
		       (printer-setup-particular 'left-margin)))
   (top-margin-mf    (postscript-convert-linear-distance-to-postscript-units-mf
		       (printer-setup-particular 'top-margin)))
   (right-margin-mf  (postscript-convert-linear-distance-to-postscript-units-mf
		       (printer-setup-particular 'right-margin)))
   (bottom-margin-mf (postscript-convert-linear-distance-to-postscript-units-mf
		       (printer-setup-particular 'bottom-margin)))
   (left (left-edge-of-block workspace))
   (top (top-edge-of-block workspace))
   (right (right-edge-of-block workspace))
   (bottom (bottom-edge-of-block workspace))
   (workspace-width (-w right left 6))			    ; 6?
   (workspace-height (-w bottom top 6))			    ; 6?
   (window-frame-width (get-property-for-printing workspace 'border-width))

   ;; These want to be wrapped in with-temporary-gensym-float-creation.
   (page-width-mf (postscript-remove-margins-from-dimension
		    paper-width-mf left-margin-mf right-margin-mf))
   (page-height-mf (postscript-remove-margins-from-dimension
		     paper-height-mf top-margin-mf bottom-margin-mf))

   (postscript-units-per-workspace-unit-mf
     (postscript-compute-workspace-scaling
       top bottom left right page-width-mf page-height-mf
       workspace-width workspace-height window-frame-width))
   
   (x-tile-step (truncate-mf page-width-mf postscript-units-per-workspace-unit-mf))
   (y-tile-step (truncate-mf page-height-mf postscript-units-per-workspace-unit-mf))

   ;; The three sorts of printing we can do at the moment.
   (printing-format (cond ((icp-window-p output-window-for-printing?) 'native)
			  ((generate-bitmap-p plist) 'bitmap)
			  (t 'postscript)))
   
   (gensym-window-for-printing				    ; This is a special variable.
     (make-gensym-window-for-printing
       (+f x-tile-step window-frame-width window-frame-width)
       (+f y-tile-step window-frame-width window-frame-width))
     reclaim-gensym-window-for-printing)

   (printing-stream (make-printing-stream printing-format))
					; May be nil, but printing-stream is
					; special so we won't change its name. - jpg 7/13/00
   (image-plane nil)			; On the printing window.
   (blank-page-p nil)			; Support for page-economy-mode
   (pathname (get-true-pathname-namestring-for-printing-stream printing-stream)
	     reclaim-if-text-string)

   (bitmap-for-printing? (and (eq printing-format 'bitmap)
			      ;; Q: Any reason to use a remote window here?
			      ;; A: Because this function runs inside G2 server and the bitmap creation depends
			      ;;    on the DC of a native window. Therefore `system-window' here is NOT a remote
			      ;;    window at all.  -- Chun Tian (binghe), Apr 25, 2013
			      (create-bitmap-for-printing system-window
							  (get-property-for-printing workspace 'width)
							  (get-property-for-printing workspace 'height))))
   
   ;; Dynamic variables
   (last-postscript-composite-object-index 0)
   (postscript-composite-object-mapping () printing-list)
   (postscript-object-mapping-for-icon-renderings () reclaim-postscript-object-mapping-for-icon-renderings)
   (postscript-computed-variables-mapping () reclaim-postscript-computed-variables-mapping)
   (postscript-printing-icon-renderings () reclaim-postscript-printing-icon-renderings)
   (postscript-object-mapping-for-graph-renderings () printing-list)
   (fonts-used-in-print-job () printing-list)
   (kanji-fonts-used-in-print-job () printing-list)
   (fonts-needing-corresponding-kanji-font () printing-list)
   (postscript-emitting-definition nil)
   (postscript-definition-operation-counter 0)
   (printing-icon-current-region-index? nil)
   (printing-pass-number 1)
   (printing-pass-is-for-header nil)
   (emit-postscript-line-length 0)			    ; Current column in output line.
   
   ;; Read-only state vars.
   ;; Duplicates code in `postscript-compute-page-count'.
   (initial-tile-offset (-f window-frame-width))
   (ncolumns (safe-ceiling (- workspace-width initial-tile-offset) x-tile-step))
   (nrows    (safe-ceiling (- workspace-height initial-tile-offset) y-tile-step))
   (npages (*f nrows ncolumns))
   (eps? (and (=f npages 1) (generate-eps-p)))
   (multipage-legends-p (and postscript-enable-multipage-legends (>f npages 1) (not eps?)))

   ;; Loop variables.
   (page-number 1)
   (x-tile-offset initial-tile-offset)
   (y-tile-offset initial-tile-offset)

   ;; Program counter
   (state 0)
   (substate 0))
  
  ;; Function body
  (let ((printing-in-progress-p t))
    (with-named-dynamic-extent print-spooling ()
      (with-other-processing-allowed ()
	;; Check whether we could open the output file and/or create bitmap.
	(when (case printing-format
		(postscript (null printing-stream))
		(bitmap (or (null printing-stream)
			    (null bitmap-for-printing?))))
	  (printing-notification 'error workspace pathname)
	  (exit-process))

	;; Validate the workspace.
	(when (frame-has-been-reprocessed-p workspace workspace-serial-number)
	  (printing-notification 'deleted workspace pathname)
	  (setq workspace nil)
	  (if printing-stream
	      (setq state 5)
	      (exit-process)))

	;; Pass 0: Emit job header. Resize printing window.
	(when (=f state 0)
	  (printing-notification 'begin workspace pathname)
	  ;; Header for Job. Magic 15 is taken from postscript-compute-scaling-to-fit, below.
	  ;; If we are not scaling-to-fit, then maybe 15 should be some other number.
	  (with-output-to-printing-window ()
	    (when (eq printing-format 'postscript)
	      (emit-postscript-job-header
		workspace
		paper-size-name
		npages eps? (-w right left -15) (-w bottom top -15)
		postscript-units-per-workspace-unit-mf
		paper-orientation
		actual-paper-width-mf actual-paper-height-mf
		left-margin-mf top-margin-mf
		right-margin-mf bottom-margin-mf
		paper-left-margin-mf paper-top-margin-mf
		paper-right-margin-mf paper-bottom-margin-mf)
	      
	      ;; Prolog for G2 jobs.
	      (emit-postscript-prolog paper-size eps?))

	    ;; Setup for Job.
	    (make-or-revise-window gensym-window-for-printing 
				   0 0
				   (+f workspace-width window-frame-width window-frame-width)
				   (+f workspace-height window-frame-width window-frame-width)
				   nil nil nil)
	    (lay-out-window gensym-window-for-printing))
	  (incff state)
	  (allow-other-processing))
	
	;; Pass 1: Create the image plane and queue drawing there-on
	(when (=f state 1)
	  (with-drawing-trace (printing)
	    (format t "Begin printing ~s~%" workspace))
	  (when (eq printing-format 'postscript) ; Only if we need pass-1 output
	    (with-output-to-printing-window ()
	      (setq image-plane (setup-image-plane-for-printing
				  workspace x-tile-offset y-tile-offset))))
	  (incff state)
	  (allow-other-processing))

	;; Pass 2: Cache renderings as postscript procedures.
	(when (=f state 2)
	  (cond ((neq printing-format 'postscript) ; Pass 1 not needed for native or bitmap printing.
		 (when (are-there-graphs-on-this-workspace? workspace)
		   (bogus-preflight-from-printing-to-graphs workspace))
		 (incff state))
		;; If there are graphs, preflight, and run this pass to completion.
		((are-there-graphs-on-this-workspace? workspace)
		 (bogus-preflight-from-printing-to-graphs workspace)
		 (with-unlimited-time-slice
		   (draw-image-plane-for-printing-a-little image-plane) 
		   (incff state)))
		(t
		 (loop while (=f state 2) doing
		   (when (draw-image-plane-for-printing-a-little image-plane)
		     (incff state))
		   (allow-other-processing)))))
	
	;; Pass 3: Layout the paper.
	(when (=f state 3)
	  (with-output-to-printing-window ()
	    (make-or-revise-window gensym-window-for-printing 
				   0 0
				   (+f x-tile-step window-frame-width window-frame-width)
				   (+f y-tile-step window-frame-width window-frame-width)
				   nil nil nil)
	    (lay-out-window gensym-window-for-printing))
	  (start-document workspace left top right bottom)
	  (when (eq printing-format 'postscript) ; Only if we need pass-1 output
	    (emit-print-job-specific-font-definitions)
	    (emit-postscript-page-layout paper-size-name
					 postscript-units-per-workspace-unit-mf
					 paper-orientation
					 actual-paper-width-mf
					 actual-paper-height-mf
					 left-margin-mf
					 top-margin-mf
					 right-margin-mf
					 bottom-margin-mf
					 paper-left-margin-mf
					 paper-top-margin-mf
					 paper-right-margin-mf
					 paper-bottom-margin-mf))
	  (setq printing-pass-number 2)
	  (incff state)
	  (allow-other-processing))

	;; Pass 4: Loop over pages.
	(when (=f state 4)
	  (loop while (=f state 4) doing
	    (when (=f substate 0)
	      ;; Enqueue drawing, check for blank page.
	      (with-output-to-printing-window ()
		(setq image-plane (setup-image-plane-for-printing
				    workspace x-tile-offset y-tile-offset)))
	      ;; If in page-economy-mode and page is blank, skip to next page. [Note A]
	      (cond ((and (page-economy-mode printer-setup)
			  (setq blank-page-p (not (image-plane-has-drawing-in-window-p image-plane))))
		     (setq substate 3))	; Skip to next page
		    (t
		     (incff substate))))
	    
	    ;; Set up coordinate transformation for this page.
	    (when (=f substate 1)
	      (start-page page-number nrows ncolumns
			  left-margin-mf
			  top-margin-mf
			  right-margin-mf
			  bottom-margin-mf
			  paper-left-margin-mf
			  paper-top-margin-mf
			  paper-right-margin-mf
			  paper-bottom-margin-mf
			  postscript-units-per-workspace-unit-mf
			  x-tile-offset y-tile-offset
			  x-tile-step y-tile-step
			  multipage-legends-p
			  blank-page-p)
	      (incff substate)
	      (allow-other-processing))

	    ;; Continue drawing until done.
	    (when (=f substate 2)
	      (loop while (=f substate 2) doing
		(when (draw-image-plane-for-printing-a-little image-plane)
		  (end-page)
		  (incff substate))
		(allow-other-processing)))

	    ;; Advance to next page, exiting if done.
	    (when (=f substate 3)
	      (incff page-number)
	      (incff x-tile-offset x-tile-step)
	      (setq y-tile-offset (cond ((<r workspace-width x-tile-offset)
					 (setq x-tile-offset initial-tile-offset)
					 (+r y-tile-offset y-tile-step))
					(t y-tile-offset)))

	      (when (>f y-tile-offset workspace-height)
		(incff state))
	      (setq substate 0)			    ; goto next page
	      (allow-other-processing))))

	;; Pass 5: Finish printing.
	(when (=f state 5)
	  (end-document page-number)
	  (when printing-stream
	    (close-printing-stream printing-stream))
	  (printing-notification 'end workspace pathname))))))

;; Does the defun need to allow unwind-protect?

;; Note A: The use of with-output-to-printing-window guarantees that no drawing
;; will happen, so it's known to be "safe" to call here.  If the setup could do
;; drawing, the following test image-plane-has-drawing-in-window-p would not be
;; reliable.



(defun printing-notification (which workspace pathname?)
  (let ((priority (printing-priority printer-setup))
	(njobs (length background-processes))
	;; Possibly.
	;; (printing-in-progress-p nil)
	(destination
	  (twith-output-to-text-string
	    (case printing-format
	      (native
	       (tformat "~a on ~a"
			(printer-setup-particular 'printer-identification)
			(gensym-window-host-name output-window-for-printing?)))
	      (t
	       (tformat "~s" pathname?))))))
    (case which
      (begin
       (cond ((=f njobs 1)
	      (notify-user "Begin printing ~NF to ~a at priority ~d."
			   workspace destination priority))
	     (t
	      (notify-user "Begin printing ~NF to ~a at priority ~d.  ~a ~a ahead in queue."
			   workspace destination priority
			   (-f njobs 1)
			   (if (>f njobs 2) "jobs" "job")))))

      (error
       (notify-user "Printing workspace ~NF failed." workspace))
      
      (deleted
       (notify-user "The workspace being printed to ~a has been deleted."
		    destination))

      (end
       (with-drawing-trace (printing)
	 (format t "Finished printing ~s~%" workspace))
       (cond ((null workspace))
	     ((=f njobs 1)
	      (notify-user "Finished printing ~NF to ~a." workspace destination))
	     (t
	      (notify-user "Finished printing ~NF to ~a.   ~a ~a remaining."
			   workspace destination
			   (-f njobs 1)
			   (if (>f njobs 2) "jobs" "job"))))))
    (reclaim-text-string destination)))




;;; The function `print-workspace-from-action' implements the "PRINT
;;; <workspace>" action.

(defun print-workspace-from-action (workspace)
  (print-workspace workspace))

;; This used to call print-workspace with an infinite time slice.
;; Was that the desired behavior?  Probably not.




;;; The function `workspace-of-printing-process' returns the workspace
;;; on which a printing process is operating, if the process is indeed
;;; a printing process.

(defun workspace-of-printing-process (process)
  (when (and (eq (process-name process) 'BACKGROUND-PRINT-WORKSPACE)
	     (process-state-block process))
    (background-print-workspace-process-state-block-workspace
      (process-state-block process))))



;;; The function `service-print-jobs' runs print jobs for the given workspace
;;; until the current time slice expires.  A null workspace means all
;;; workspaces.

(defun service-print-jobs (workspace?)
  (loop for process in background-processes
	as printing-workspace? = (workspace-of-printing-process process)
	doing (when (and printing-workspace?
			 (or (null workspace?)
			     (eq workspace? printing-workspace?)))
		(call-background-process process))

    	until (time-slice-expired-p)))

;; Check the time slice at the end, so that we always make some progress.


(defun pending-print-jobs-p (workspace?)
  (loop for process in background-processes
	as printing-workspace? = (workspace-of-printing-process process)
	thereis (and printing-workspace?
		     (or (null workspace?)
			 (eq workspace? printing-workspace?)))))

#+development
(defun list-printing-processes ()
  (fresh-line)
  (loop for process in background-processes
	as state = (process-state-block process)
	doing
    (format t "~s~30t ~s state: ~s/~s  pathname: ~a~%"
	    (process-name process)
	    (process-status process)
	    ;; Assume printing.
	    (background-print-workspace-process-state-block-state state)
	    (background-print-workspace-process-state-block-substate state)
	    (background-print-workspace-process-state-block-pathname state)))
  (values))

;;; KB API procedure for local printing 
(defun-for-system-procedure g2-ui-print-window ( g2-window is-print-dlg-showed )
  (let ((gensym-window (map-g2-window-to-gensym-window g2-window))
        (is-print-dlg-showed-p (evaluation-truth-value-is-true-p is-print-dlg-showed)))
    (with-icp-window (gensym-window)
      (send-icp-print-native-window gensym-window is-print-dlg-showed-p))))
