;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module VIEWS - Native Views and the Views API

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author(s): Fred White


;;;; Introduction

;;; This module contains definitions for most kinds of native views, including
;;; structures as well as system procedures and event handlers.

;;; This file was split off from COMMANDS2 on 8/23/06, when the latter's
;;; translated C code exceeded 2^16 lines. You'll have to refer to that file for
;;; prior history.


;;;; Forward References in VIEWS

(declare-forward-references
  (get-callback-procedure function COMMANDS0)
  (apply-kb-procedure function COMMANDS0)
  (gensym-window-point-to-user-window-point function COMMANDS1)
  (update-att-tables function COMMANDS1)
  (send-native-icon function COMMANDS2)
  (valid-icon-designation-or-stack-error function COMMANDS2)
  (synthesize-mouse-pointer function COMMANDS2)
  (valid-icon-designation-p function COMMANDS2)
  (preprocess-icon-options function COMMANDS2)
  (preprocess-container-options function COMMANDS2)
  (preprocess-view-options function COMMANDS2)
  (call-dialog-update-callback-if-any function COMMANDS2)
  (call-dialog-gesture-callback-if-any function COMMANDS2))


;;;; Utilities


;; Convenience macro.
(defmacro ui-stack-error (message &rest args)
  `(stack-error cached-top-of-stack ,message ,@args))

(defun-simple ui-stack-error-1 (message value)
  (stack-error cached-top-of-stack message value))

(defun find-native-view-or-stack-error (gensym-window handle &optional class?)
  (or (find-native-window gensym-window handle class?)
      (ui-stack-error "No ~a found for handle ~s."
		      (pretty-name-of-view-class class?)
		      handle)))

;; TODO: Eliminate this function.
(defun pretty-name-of-view-class (view-class)
  (case view-class
    (g2-workspace-view "Workspace View")
    (g2-tree-view "Tree View")
    (g2-html-view "HTML View")
    (g2-shortcut-bar "Shortcut Bar")
    (g2-chart-view "Chart View")
    (g2-dialog-view "Dialog View")
    (g2-property-grid "Property Grid")
    (g2-status-bar "Status Bar")
    (g2-tabular-view "Tabular View")
    ((nil) "Native View")
    (t (dwarn "Unknown class of view: ~s" view-class)
       "View")))


;;; The function `stored-callback-procedure' returns something safe to store in
;;; a callback procedure slot given a lisp value. It is simply either NIL or the
;;; procedure name.

(defun stored-callback-procedure (value)
  (cond ((eq value 'none)
	 nil)
	((symbolp value)
	 value)
	((and (framep value)
	      (procedure-p value))
	 (get-primary-name-for-frame-if-any value))))



;;;; Type Checkers


(defun valid-color-designation-or-stack-error (value)
  (unless (and (symbolp value)
	       (or (gensym-color-p value)
		   (null value)
		   (eq value 'none)
		   (rgb-color-p value)))
    (ui-stack-error "~A is not a valid color name." value)))

(defun rgb-color-value-or-stack-error (color)
  (valid-color-designation-or-stack-error color)
  (case color
    (foreground (rgb-value-of-gensym-color 'black))
    (background (rgb-value-of-gensym-color 'white))
    ((none transparent nil) -1)		; As used by the XTP library.
    (t
     (rgb-value-of-gensym-color color))))

(defun native-icon-handle-or-stack-error (gensym-window value)
  (cond ((or (null value) (eq value 'none))
	 -1)
	(t
	 (valid-icon-designation-or-stack-error value)
	 (send-native-icon gensym-window value))))

(defun secure-telewindows-connection-p (gensym-window)
  (and (icp-output-port-for-window? gensym-window)
       (=f (c-secure-socket-p (icp-connection-handle (icp-output-port-for-window? gensym-window)))
	   1)))


;;;; View Callbacks


(defun get-view-callback-if-any (view)
  (when (native-view-callback? view)
    (get-view-callback (native-view-callback? view)
		       (pretty-name-of-view-class (native-window-class view)))))

(defun get-view-callback (name-or-frame description)
  (get-callback-procedure name-or-frame
			  description
			  '(symbol (class g2-window) integer datum (structure) datum)))

;;; The macro `invoke-view-callback' starts the KB-level callback procedure for
;;; given view, if any, on given args. Event should be a symbol, and info an
;;; eval-plist. Event, item, info, and user-data are NOT evaluated if there is
;;; no callback.

(defmacro invoke-view-callback (view event item info user-data)
  (avoiding-variable-capture (view &aux procedure)
    `(let ((,procedure (get-view-callback-if-any ,view)))
       (when ,procedure
	 (invoke-view-callback-1 ,view ,procedure ,event ,item ,info ,user-data)))))

(defun invoke-view-callback-1 (view procedure event item info user-data?)
  ;; The user-data argument of view callbacks is declared to take a value
  ;; (datum), which a bare item-reference is not. In that case, somewhat
  ;; arbitrarily wrap the bare item in an evaluation structure with key
  ;; ITEM. For HQ-5185816. Someday, allow view callbacks to take an
  ;; item-or-value for the user-data. -fmw, 3/8/06
  (let ((user-data-ev (cond ((null user-data?)
			     (make-evaluation-symbol 'none))
			    ((not (evaluation-item-reference-p user-data?))
			     (copy-if-evaluation-value user-data?))
			    ((get-item-if-item-reference user-data?)
			     (allocate-evaluation-structure-inline
			       'item (get-item-if-item-reference user-data?))))))
    (call-kb-procedure procedure
		       event
		       (g2-window-for-gensym-window? (native-window-gensym-window view))
		       (native-window-handle view)
		       (or (copy-if-text-string item) 'none) ; FIXME?
		       (allocate-evaluation-structure info)
		       user-data-ev)))


;;;; Item-Or-Name Hash

;;; An `item-or-name-hash' maps an item-reference, wide-string, or symbol to a
;;; fixnum or gensym-list of fixnums.

(def-hash-table item-or-name-hash
    :hash-function-or-macro hash-item-or-name
    :key-comparitor equalw
    :key-reclaimer reclaim-item-or-name
    :entry-reclaimer reclaim-gensym-list-if-list)

(defun hash-item-or-name (item-or-name)
  (cond ((evaluation-item-reference-p item-or-name)
	 (hash-item-reference item-or-name))
	((framep item-or-name)
	 (hash-item-reference (uuid item-or-name)))
	(t
	 (sxhashw item-or-name))))

(defun reclaim-item-or-name (item-or-name)
  (cond ((wide-string-p item-or-name)
	 (reclaim-wide-string item-or-name))
	((evaluation-item-reference-p item-or-name)
	 (reclaim-evaluation-item-reference item-or-name))))

;; Also converts items to item-references
(defun copy-item-or-name (item-or-name)
  (cond ((framep item-or-name)
	 (get-reference-to-item-if-item item-or-name))
	((evaluation-item-reference-p item-or-name)
	 (copy-evaluation-item-reference item-or-name))
	((wide-string-p item-or-name)
	 (copy-wide-string item-or-name))
	(t
	 item-or-name)))

(defun item-or-name-hash-get (item-or-name hash-table)
  (let ((key (copy-item-or-name item-or-name)))
    (prog1 (get-item-or-name-hash key hash-table)
      (reclaim-item-or-name key))))

(defun item-or-name-hash-put (item-or-name handle hash-table)
  (let* ((key (copy-item-or-name item-or-name))
	 (entry (get-item-or-name-hash key hash-table)))
    (setf (get-item-or-name-hash key hash-table)
	  (cond ((null entry)
		 handle)
		((atom entry)
		 (gensym-list handle entry))
		((consp entry)
		 (gensym-cons handle (copy-list-using-gensym-conses entry)))))))

(defun item-or-name-hash-remove (item-or-name handle hash-table)
  (let* ((key (copy-item-or-name item-or-name))
	 (entry (get-item-or-name-hash key hash-table)))
    (cond ((null entry)
	   (reclaim-item-or-name key))
	  ((atom entry)
	   (when (eql handle entry)
	     (delete-item-or-name-hash key hash-table))
	   (reclaim-item-or-name key))
	  ((null (cdr entry))
	   (when (eql handle (car entry))
	     (delete-item-or-name-hash key hash-table))
	   (reclaim-item-or-name key))
	  ((null (cddr entry))
	   (cond ((eql handle (car entry))
		  (setf (get-item-or-name-hash key hash-table) (cadr entry)))
		 ((eql handle (cadr entry))
		  (setf (get-item-or-name-hash key hash-table) (car entry)))
		 (t
		  (reclaim-item-or-name key))))		  
	  (t
	   (setf (get-item-or-name-hash key hash-table)
		 (loop for x in entry
		       unless (eql x handle)
			 collect x using gensym-cons))))))


;;;; Status Bar View




(def-type-parameter status-bar-action-type
    (member hide show set-text set-min-height set-callback
	    configure add-pane modify-pane remove-pane))

(def-type-parameter status-bar-configure-type
    (structure ((visible truth-value)
		(callback (or symbol (class procedure)))
		(user-data item-or-datum)
		(min-height integer)
		(panes (sequence (structure))))))

(def-type-parameter status-bar-remove-pane-type
    (or integer symbol text
	(structure ((id (or integer symbol text))))))

(def-type-parameter status-bar-pane-options-type
    (structure ((id (or integer symbol text))              ; I'd use NAME, but not an allowed structure key!
		(position (or integer symbol text))
		(text text)
		(icon item-or-datum)
		(width (or integer (member fit)))          ; FIT = fit to current icon+text width
		(background-color (or symbol truth-value)) ; false indicates NONE or TRANSPARENT
		(foreground-color (or symbol truth-value))
		(alignment (member left center right))
		(tooltip text)
		(visible truth-value)
		(enabled truth-value)
		(borders truth-value)
		(user-data item-or-datum))))

(def-structure (status-bar
		 (:include native-view)
		 (:reclaimer reclaim-status-bar-1)
		 #+development (:print-function print-native-window))
  (status-bar-next-handle 1)		; Next pane handle
  (status-bar-free-handles nil)		; Gensym list
  (status-bar-panes nil))		; Gensym list of status-bar-panes

(def-structure-method clean-up-structure (status-bar)
  (let ((gensym-window (native-window-gensym-window status-bar)))
    (setf (native-status-bar? gensym-window) nil)
    (status-bar-reset-locally status-bar t)
    (funcall-superior-method status-bar)))

(defun reclaim-status-bar (status-bar)
  (reclaim-native-window status-bar))

;; A component of a status-bar.
(def-structure (status-bar-pane
		 (:reclaimer reclaim-status-bar-pane-1)
		 (:constructor make-status-bar-pane (status-bar-pane-handle
						      status-bar-pane-id
						      status-bar-pane-user-data)))
  (status-bar-pane-handle nil)		; unique integer handle. Maps to Win32 nID.
  (status-bar-pane-id nil)		; user-supplied integer, symbol, or string
  (status-bar-pane-user-data nil))

(defun reclaim-status-bar-pane (pane)
  (reclaim-if-text-string (status-bar-pane-id pane))
  (reclaim-if-evaluation-value (status-bar-pane-user-data pane))
  (reclaim-status-bar-pane-1 pane))

(defun get-status-bar (gensym-window)
  (or (native-status-bar? gensym-window)
      (let ((status-bar (make-status-bar)))
	(setf (native-window-gensym-window status-bar) gensym-window
	      (native-window-class status-bar) 'g2-status-bar
	      (native-status-bar? gensym-window) status-bar)
	(status-bar-create-initial-panes status-bar)
	status-bar)))

;; Note that we don't create one for the progress bar since it is only exists
;; when it's being used. That may change.
(defun status-bar-create-initial-panes (status-bar)
  (let ((gensym-window (native-window-gensym-window status-bar)))
    (status-bar-add-pane-1 status-bar 0 'g2-documentation-line nil)
    (when (secure-telewindows-connection-p gensym-window)
      (status-bar-add-pane-1 status-bar -1 'g2-security-icon nil))))

(defun status-bar-reset-locally (status-bar &optional reclaiming)
  (loop for pane in (status-bar-panes status-bar)
	doing (reclaim-status-bar-pane pane))
  (reclaim-gensym-list (status-bar-panes status-bar))
  (reclaim-gensym-list (status-bar-free-handles status-bar))
  (setf (status-bar-next-handle status-bar) 1
	(status-bar-free-handles status-bar) nil
	(status-bar-panes status-bar) nil)
  (unless reclaiming
    (status-bar-create-initial-panes status-bar)))

(defun status-bar-find-pane (status-bar pane-designation)
  (loop for pane in (status-bar-panes status-bar)
	when (cond ((eql pane-designation 0)
		    (eq (status-bar-pane-id pane) 'g2-documentation-line))
		   ((eql (status-bar-pane-id pane) pane-designation)
		    t)
		   ((and (wide-string-p (status-bar-pane-id pane))
			 (wide-string-p pane-designation))
		    (string=w (status-bar-pane-id pane) pane-designation)))
	  return pane))

(defun status-bar-find-pane-by-handle (status-bar handle)
  (loop for pane in (status-bar-panes status-bar)
	when (eql (status-bar-pane-handle pane) handle)
	  return pane))

(defun status-bar-find-pane-or-stack-error (status-bar pane-designation)
  (or (status-bar-find-pane status-bar pane-designation)
      (ui-stack-error "Status-bar pane ~NV not found." pane-designation)))

(defun status-bar-allocate-pane-handle (status-bar)
  (cond ((<f (status-bar-next-handle status-bar)
	     status-bar-maximum-pane-count)
	 (prog1 (status-bar-next-handle status-bar)
	   (incff (status-bar-next-handle status-bar))))
	(t
	 (gensym-pop (status-bar-free-handles status-bar)))))

;; TODO: We don't bother to keep our list in any order.
(defun status-bar-add-pane-locally (status-bar id user-data)
  (let ((handle? (status-bar-allocate-pane-handle status-bar)))
    (when handle?
      (status-bar-add-pane-1 status-bar handle? id user-data))))

(defun status-bar-add-pane-1 (status-bar handle id user-data)
  (let ((pane (make-status-bar-pane handle
				    (copy-if-text-string id)
				    (copy-if-evaluation-value user-data))))
    (gensym-push pane (status-bar-panes status-bar))
    pane))

(defun status-bar-remove-pane-locally (status-bar pane)
  (setf (status-bar-panes status-bar)
	(delete-gensym-element pane (status-bar-panes status-bar)))
  (setf (status-bar-free-handles status-bar)
	(nconc (status-bar-free-handles status-bar)
	       (gensym-list (status-bar-pane-handle pane))))
  (reclaim-status-bar-pane pane))

(defun note-kb-reset-for-native-status-bars ()
  (loop for workstation in workstations-in-service
	as gensym-window = (window-for-workstation workstation)
	as status-bar? = (native-status-bar? gensym-window)
	doing
    (when status-bar?
      (status-bar-reset-locally status-bar?)
      (when (window-supports-manage-status-bar-ex gensym-window)
	(manage-status-bar gensym-window 'reset nil)))))

(defun preprocess-status-bar-pane-options (gensym-window status-bar arg)
  (when (plistp arg)
    (loop for sublist on arg by #'cddr
	  as (property value) = sublist
	  doing
      (case property
	((id position)
	 (let ((pane? (status-bar-find-pane status-bar value)))
	   (when (text-string-p value)
	     (reclaim-text-string value))
	   (setf (cadr sublist) (if pane? (status-bar-pane-handle pane?) -1))))
	(icon
	 (setf (cadr sublist) (native-icon-handle-or-stack-error gensym-window value)))
	((background-color foreground-color)
	 (setf (cadr sublist) (rgb-color-value-or-stack-error value)))
	(width
	 (when (eq value 'fit)
	   (setf (cadr sublist) -1)))
	(alignment
	 (setf (cadr sublist) (encode-text-alignment value)))))))

(defun manage-status-bar (gensym-window action arg)
  (cond ((icp-window-p gensym-window)
	 (with-icp-window (gensym-window)
	   (send-icp-manage-status-bar gensym-window action arg)))
	(t
	 (manage-status-bar-1 action arg))))

;;; Commands

(defun status-bar-reset (status-bar)
  (let ((gensym-window (native-window-gensym-window status-bar)))
    (status-bar-reset-locally status-bar)
    (when (window-supports-manage-status-bar-ex gensym-window)
      (manage-status-bar gensym-window 'reset nil))))

(defun status-bar-configure (status-bar plist user-data? panes-ev?)
  (let ((gensym-window (native-window-gensym-window status-bar)))
    (status-bar-reset status-bar)
    user-data?				; TODO: Set user-data for entire pane.
    (loop for (property value) on plist by #'cddr doing
      (case property
	(visible
	 (if (not value) (manage-status-bar gensym-window 'hide nil)))
	(callback
	 (setf (native-view-callback? status-bar) (stored-callback-procedure value)))
	(min-height
	 (manage-status-bar gensym-window 'set-min-height value))))
    (when panes-ev?
      (loop for pane-ev being each evaluation-sequence-element of panes-ev?
	    doing
	(check-type-or-stack-error pane-ev status-bar-pane-options-type)	
	(let* ((pane-user-data? (and (evaluation-structure-p pane-ev)
				     (evaluation-structure-slot pane-ev 'user-data)))
	       (plist (unbox-evaluation-value pane-ev '(user-data))))
	  (status-bar-add-pane status-bar plist pane-user-data?)
	  (reclaim-unboxed-evaluation-value plist))))))

(defun status-bar-add-pane (status-bar plist user-data?)
  (let ((gensym-window (native-window-gensym-window status-bar))
	(id (or (getf plist 'id)
		(getf plist 'text)))	; FIXME: default default id?
	(position? (getf plist 'position)))
    (when position?
      (status-bar-find-pane-or-stack-error status-bar position?))
    (unless (status-bar-add-pane-locally status-bar id user-data?)
      (ui-stack-error "Maximum of ~D status-bar panes exceeded." status-bar-maximum-pane-count))
    (preprocess-status-bar-pane-options gensym-window status-bar plist)
    (manage-status-bar gensym-window 'add-pane plist)))

(defun status-bar-modify-pane (status-bar plist user-data?)
  (let* ((gensym-window (native-window-gensym-window status-bar))
	 (id (getf plist 'id))
	 (pane (status-bar-find-pane-or-stack-error status-bar id)))
    (when user-data?
      (reclaim-if-evaluation-value (status-bar-pane-user-data pane))
      (setf (status-bar-pane-user-data pane) (copy-evaluation-value user-data?)))
    (preprocess-status-bar-pane-options gensym-window status-bar plist)
    (manage-status-bar gensym-window 'modify-pane plist)))

(defun status-bar-remove-pane (status-bar arg)
  (let* ((gensym-window (native-window-gensym-window status-bar))
	 (id (cond ((plistp arg)
		    (getf arg 'id))
		   ((atom arg)
		    arg)))
	 (pane (status-bar-find-pane-or-stack-error status-bar id)))
    (status-bar-remove-pane-locally status-bar pane)
    (preprocess-status-bar-pane-options gensym-window status-bar arg)
    (manage-status-bar gensym-window 'remove-pane (status-bar-pane-handle pane))))

(defun status-bar-api-p (gensym-window)
  (and (twng-window-p gensym-window)
       (window-supports-manage-status-bar-ex gensym-window)))

;;; The sysproc `g2-ui-manage-status-bar' has existed for some time, but was not
;;; exposed to users until 8.3a0. Note that unlike other UI sysprocs, this does
;;; not take a handle argument, since there is at most one status-bar per
;;; g2-window. In the unlikely event that we someday support multiple top-level
;;; frames, each with a distinct status bar, we can define an "ex" version of
;;; this routine.

(defun-for-system-procedure g2-ui-manage-status-bar (action ev-arg g2-window)
  (check-type-or-stack-error action status-bar-action-type)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (native-menu-bar-p gensym-window) ; Status bars go with menu bars.
      (ui-stack-error "Status bars are not supported on ~NF" g2-window))

    (unless (current-window-supports-manage-status-bar gensym-window)
      (ui-stack-error "Modifying the status bar is not supported on ~NF" g2-window))

    (unless (or (memq action '(hide show set-text)) ; pre-8.3 actions
		(status-bar-api-p gensym-window))
      (ui-stack-error "The status-bar action ~A is not supported on ~NF" action g2-window))

    (let* ((user-data? (and (evaluation-structure-p ev-arg)
			    (evaluation-structure-slot ev-arg 'user-data)))
	   (panes? (and (evaluation-structure-p ev-arg)
			(evaluation-structure-slot ev-arg 'panes)))
	   (arg (unbox-evaluation-value ev-arg '(user-data panes)))
	   (status-bar (get-status-bar gensym-window)))

      ;; Perform action locally and remotely.
      (case action
	(set-callback			; Local only
	 (check-type-or-stack-error ev-arg '(or symbol (class procedure)))
	 (setf (native-view-callback? status-bar) (stored-callback-procedure arg)))

	(configure
	 (check-type-or-stack-error ev-arg status-bar-configure-type)
	 (status-bar-configure status-bar arg user-data? panes?))

	(reset
	 (status-bar-reset status-bar))

	(add-pane
	 (check-type-or-stack-error ev-arg status-bar-pane-options-type)
	 (status-bar-add-pane status-bar arg user-data?))

	(modify-pane
	 (check-type-or-stack-error ev-arg status-bar-pane-options-type)
	 (status-bar-modify-pane status-bar arg user-data?))
	
	(remove-pane
	 (check-type-or-stack-error ev-arg status-bar-remove-pane-type)
	 (status-bar-remove-pane status-bar arg))

	(t
	 (manage-status-bar gensym-window action arg)))

      (reclaim-unboxed-evaluation-value arg)
      (reclaim-evaluation-value ev-arg)
      (copy-evaluation-boolean evaluation-false-value))))

;; Yuck. Yet another convention for event names.
(defun status-bar-event-name (event-code modifier-bits)
  (let ((click?
	  (case event-code
	    (1 'left-click)
	    (2 'middle-click)
	    (3 'right-click))))
    (mouse-click-event-name click? modifier-bits)))

(defun mouse-click-event-name (click? modifier-bits)
  (when click?
    (let ((write-symbols-parsably? t))
      (intern-text-string
	(nstring-upcasew
	  (twith-output-to-text-string
	    (twrite-key-modifier-bits (logiorf (key-code 'mouse-down) modifier-bits) nil)
	    (twrite-symbol click?)))))))

(define-event-handler handle-status-bar-message ((gensym-window window) event-plist x-in-window y-in-window)
  (let* ((status-bar (get-status-bar gensym-window))
	 (bits (getf event-plist 'bits 0))
	 (event? (status-bar-event-name (getf event-plist 'event) bits))
	 (pane? (status-bar-find-pane-by-handle status-bar (getf event-plist 'pane))))
    (when event?
      (multiple-value-bind (user-window-x user-window-y)
	  (gensym-window-point-to-user-window-point gensym-window x-in-window y-in-window)
	(invoke-view-callback status-bar event?
			      (if pane? (status-bar-pane-id pane?))
			      (eval-list 'x user-window-x 'y user-window-y)
			      (if pane? (status-bar-pane-user-data pane?)))))))


;;;; Logbook Views


;;; What I'm calling a `logbook-view' here might better be called something more
;;; generic, like `output-window' or `messages-window'. It has nothing to do
;;; with the G2 logbook per-say, except that it is used by it.  A `logbook-view'
;;; is simply a stream of messages, each time-tagged and uniquely
;;; numbered. Messages can be added, removed, highlighted, etc.

(def-concept logbook-view)



(def-structure (logbook-view
		 (:include native-view)
		 (:constructor make-logbook-view-1)
		 (:reclaimer reclaim-logbook-view-1)
		 #+development (:print-function print-native-window))
  (logbook-view-next-message-number 1))

(defun make-logbook-view (gensym-window callback container options)
  (let ((lbv (make-logbook-view-1)))
    (initialize-native-view lbv gensym-window 'g2-output-view container options callback)
    lbv))

(def-structure-method clean-up-structure (logbook-view)
  (let ((gensym-window (native-window-gensym-window logbook-view)))
    (when (eq logbook-view (native-logbook? gensym-window))
      (setf (native-logbook? gensym-window) nil))
    (when (eq logbook-view (native-message-board? gensym-window))
      (setf (native-message-board? gensym-window) nil)))
  (funcall-superior-method logbook-view))

(defun reclaim-logbook-view (lbv)
  (reclaim-native-window lbv))

(defun logbook-views-p (gensym-window)
  (and (twng-window-p gensym-window)
       (window-supports-manage-logbook gensym-window)))

#+not-released
(defun-for-system-procedure g2-ui-create-logbook-view (title options g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (logbook-views-p gensym-window)
      (ui-stack-error "Logbook Views are not supported on ~NF" g2-window))
    (let* ((options* (unbox-evaluation-value options))
	   (container (getf options* 'container 'pane))
	   (callback (getf options* 'callback 'none)))
      (setq options* (mutate-gensym-plist options* 'title title))
      ;; FIXME: Leaking options?
      (let ((lbv (make-logbook-view gensym-window callback container options*)))
	(preprocess-view-options lbv options*)
	(manage-logbook-1 gensym-window #.logbook-create (native-window-handle lbv)
			  0 0 options*)
	(reclaim-unboxed-evaluation-value options*)
	(native-window-handle lbv)))))

#+not-released
(defun-for-system-procedure g2-ui-manage-logbook-view (action handle ev-arg g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (logbook-views-p gensym-window)
      (ui-stack-error "Logbook Views are not supported on ~NF" g2-window))
    (let ((lbv (find-native-view-or-stack-error gensym-window handle 'g2-output-view))
	  (arg (unbox-evaluation-value ev-arg)))
      (reclaim-if-evaluation-value handle)
      (reclaim-if-evaluation-value ev-arg)
      (manage-logbook-view lbv action arg t)
      (reclaim-unboxed-evaluation-value arg)
      handle)))

(defun manage-logbook-view (lbv action &optional (arg 0) stack-error?)
  (let ((gensym-window (native-window-gensym-window lbv))
	(handle (native-window-handle lbv)))
    (when (logbook-views-p gensym-window)
      (case action
	(destroy
	 (manage-logbook-1 gensym-window #.logbook-destroy handle 0))

	(append-message
	 (when (stringpw arg)
	   (manage-logbook-1 gensym-window #.logbook-append-message handle
			     (logbook-view-next-message-number lbv)
			     nil	; message date
			     arg)
	   (incff (logbook-view-next-message-number lbv))))

	(delete-message
	 (when (fixnump arg)
	   (manage-logbook-1 gensym-window #.logbook-delete-message handle arg)))

	(normal-message
	 (when (fixnump arg)
	   (manage-logbook-1 gensym-window #.logbook-normal-message handle arg)))

	(fade-message
	 (when (fixnump arg)
	   (manage-logbook-1 gensym-window #.logbook-fade-message handle arg)))

	(highlight-message
	 (when (fixnump arg)
	   (manage-logbook-1 gensym-window #.logbook-highlight-message handle arg)))

	(set-line-wrap
	 (manage-logbook-1 gensym-window #.logbook-set-line-wrap handle (if arg 1 0)))

	(set-include-date-in-title
	 (manage-logbook-1 gensym-window #.logbook-set-include-date-in-title handle (if arg 1 0)))

	(t
	 (when stack-error?
	   (ui-stack-error "Unknown action ~a on logbook views." action)))))))

(defun logbook-view-event-name (event-code)
  (case event-code
    (1 'select)				; Sync with twng/c/LogBook.h
    (2 'right-click)
    (3 'key-pressed)
    (t nil)))

(define-event-handler handle-logbook-view-event ((gensym-window window) event-plist &optional g2-window)
  (let* ((handle (getf event-plist 'window -1))
	 (lbv? (find-native-window gensym-window handle 'g2-output-view))
	 (event? (logbook-view-event-name (getf event-plist 'event)))
	 (message-serial-number? (getf event-plist 'msg))
	 (x-in-window (getf event-plist 'x))
	 (y-in-window (getf event-plist 'y))
	 (message? (cond ((native-logbook-p lbv?)
			  (find-logbook-message message-serial-number?))
			 ((native-message-board-p lbv?)
			  (find-message-board-message message-serial-number?)))))
    (cond ((null lbv?))
	  (message?
	   (handle-logbook-view-event-1 lbv? event? message? x-in-window y-in-window g2-window))
	  (t
	   ;; TODO: Pass mouse x,y, user-data to callback.
	   (invoke-view-callback lbv? event? message-serial-number? nil 'no-user-data)))))

(defun handle-logbook-view-event-1 (lbv event message x-in-window y-in-window &optional g2-window)
  (let ((workstation (workstation-this-is-on (native-window-gensym-window lbv))))
    (update-att-tables message g2-window)
    (case event
      (select)   ; ACK!! Can't make it the selected object!
      (right-click
       (let ((mouse-pointer (synthesize-mouse-pointer workstation message (key-code 'non-event))))
         (post-command-menu 'text-box mouse-pointer x-in-window y-in-window message)
         (release-mouse-pointer-if-any mouse-pointer)))
      (key-pressed			; Delete, Menu, Shift+F10
       ))))

(defun create-logbook-view (gensym-window title width height logbook-type &optional dock? neighbor? hidden?)
  (let* ((container 'pane)
         (options (nconc
                    (gensym-list 'title title 'width width 'height height 'container container
                                 'logbook-type logbook-type 'close-action 'hide)
                    (if dock? (gensym-list 'dock dock?))
                    (if neighbor? (gensym-list 'neighbor neighbor?))
                    (if hidden? (gensym-list 'state (if dock? 'autohidden 'hidden)))))
         (lbv (make-logbook-view gensym-window nil container options)))
    (manage-logbook-1 gensym-window #.logbook-create (native-window-handle lbv) 0 0 options)
    (reclaim-gensym-list options)
    lbv))

(defun populate-logbook-view (lbv messages)
  (loop with gensym-window = (native-window-gensym-window lbv)
	with handle = (native-window-handle lbv)
	for message in messages
	as string = (convert-text-to-text-string (cdr (box-translation-and-text message)))
	as number = (or (message-serial-number? message) ; Should never be NIL.
			(incff (logbook-view-next-message-number lbv)))
	as date = (or (message-encoded-date? message) 0)
	do
    (manage-logbook-1 gensym-window #.logbook-append-message handle number date string)
    (reclaim-text-string string)))

(defun append-message-to-logbook-view (lbv message-number date string)
  (manage-logbook-1 (native-window-gensym-window lbv)
		    #.logbook-append-message
		    (native-window-handle lbv)
		    message-number date string))

(defun append-message-to-all-logbook-views (message autoshow type)
  (let ((string? nil)
	(message-number (or (message-serial-number? message) 0))
	(message-date (or (message-encoded-date? message) 0)))
    (loop for workstation in workstations-in-service
	  as gensym-window = (window-for-workstation workstation)
	  doing
      (unless (workstation-dead-p (workstation-this-is-on gensym-window))
	(when (case type
		(message-board (use-native-message-board-p gensym-window))
		(logbook (use-native-logbook-p gensym-window)))
	  (unless string?
	    (setq string? (convert-text-to-text-string (cdr (box-translation-and-text message)))))
	  (multiple-value-bind (lbv? newly-created?)
	      (case type
		(message-board (ensure-native-message-board gensym-window))
		(logbook (ensure-native-logbook gensym-window)))
	    (when lbv?
	      (when autoshow
		(%set-native-window-state lbv? 'autoshown))
	      (unless newly-created?
		(append-message-to-logbook-view lbv? message-number message-date string?)))))))
    (when string?
      (reclaim-text-string string?))))

(defun destroy-native-logbook-views (logbook-p)
  (loop for workstation in workstations-in-service
	as gensym-window = (window-for-workstation workstation)
	as lbv? = (if logbook-p
		      (native-logbook? gensym-window)
		      (native-message-board? gensym-window))
	doing
    (when lbv?
      (manage-logbook-1 gensym-window #.logbook-destroy
			(native-window-handle lbv?) 0))))

;; TODO: tree-view items
(defun remove-block-from-native-views (block)
  ;; We have to pick these up at the workspace level because
  ;; reclaim-subblocks-value has already nulled superblock pointers by the time
  ;; the messages are deleted.
  (cond ((eq block (current-message-board?))
	 (destroy-native-logbook-views nil))

	((frame-of-class-p block 'logbook-page)
	 (cond ((and (current-logbook?) 	; If removing last page, destroy the view.
		     (null (cdr (stack-of-pages current-logbook?)))
		     (eq block (car (stack-of-pages current-logbook?))))
		(destroy-native-logbook-views t))
	       (t
		(remove-messages-on-page block t))))

	((frame-of-class-p block 'message)
	 (let ((logbook-p (message-on-logbook-p block))
	       (board-p (message-on-message-board-p block)))
	   (when (or logbook-p board-p)
	     (let ((messages (gensym-list block)))
	       (remove-messages-from-native-books messages logbook-p)
	       (reclaim-gensym-list messages)))))))

(defun remove-messages-on-page (workspace logbook-p)
  (let ((messages (loop for block being each subblock of workspace
			when (frame-of-class-p block 'message)
			  collect block using gensym-cons)))
    (remove-messages-from-native-books messages logbook-p)
    (reclaim-gensym-list messages)))

(defun remove-messages-from-native-books (messages logbook-p)
  (when messages
    (loop for workstation in workstations-in-service
	  as gensym-window = (window-for-workstation workstation)
	  as lbv? = (if logbook-p
			(native-logbook? gensym-window)
			(native-message-board? gensym-window))
	  doing
      (when lbv?
	(when (icp-window-p gensym-window)
	  (with-icp-window (gensym-window)
	    (loop for message in messages doing
	      (when (message-serial-number? message)
		(send-icp-manage-logbook gensym-window 
					 #.logbook-delete-message
					 (native-window-handle lbv?)
					 (message-serial-number? message) 0 0)
		(setf (message-serial-number? message) nil)))))))))


;;;; Native Logbook


(defun use-native-logbook-p (gensym-window)
  (and (prefer-native-logbook logbook-parameters)
       (logbook-views-p gensym-window)
       (g2-window-for-gensym-window? gensym-window)
       (show-operator-logbook-in-this-window? (g2-window-for-gensym-window? gensym-window))))

(defun native-logbook-p (native-window)
  (eq native-window (native-logbook? (native-window-gensym-window native-window))))

(defmacro do-logbook-messages ((message) &body body)
  (let ((page (gensym)))
    `(when (current-logbook?)
       (loop for ,page in (stack-of-pages current-logbook?) doing
	 (loop for ,message being each subblock of ,page doing
	   (when (frame-of-class-p ,message 'message)
	     ,@body))))))

(defun find-logbook-message (serial-number?)
  (when serial-number?
    (do-logbook-messages (message)
      (when (eql serial-number? (message-serial-number? message))
	(return-from find-logbook-message message)))))

(defun ensure-native-logbook (gensym-window)
  (or (native-logbook? gensym-window)
      (unless (workstation-dead-p (workstation-this-is-on gensym-window))
	(values (setf (native-logbook? gensym-window) (create-native-logbook gensym-window))
		t))))

(defun create-native-logbook (gensym-window)
  ;; TODO: Initially autohidden if classic positioning if off-screen.  Maybe
  ;; adjust docking position, too.
  (let* ((dock (default-docking-position logbook-parameters)) 
         (neighbor nil)
         (hide? (not (lift-logbook-to-top-when-new-pages-are-added? logbook-parameters)))
         (lbv (create-logbook-view gensym-window
                #w"Operator Logbook"
                (width-for-pages logbook-parameters)
                (height-for-pages logbook-parameters)
                'operator-logbook dock neighbor hide?)))
    (when (current-logbook?)
      (when (include-date-in-logbook-messages logbook-parameters)
        (manage-logbook-view lbv 'set-include-date-in-title nil))
      (let ((messages nil))
        (do-logbook-messages (message)
          (gensym-push message messages))
        (populate-logbook-view lbv messages)
        (reclaim-gensym-list messages)))
    lbv))

(defun show-native-logbook (gensym-window)
  (cond ((native-logbook? gensym-window)
	 (%set-native-window-state (native-logbook? gensym-window) 'autoshown))
	(t
	 (ensure-native-logbook gensym-window))))

(defun hide-native-logbook (gensym-window) ; TODO: Autohidden?
  (when (native-logbook? gensym-window)
    (%set-native-window-state (native-logbook? gensym-window) 'hidden)))

(defun append-message-to-all-native-logbooks (message)
  (append-message-to-all-logbook-views
    message
    (lift-logbook-to-top-when-new-pages-are-added? logbook-parameters)
    'logbook))

(defun note-native-logbook-preference-changed (preference new-value)
  (loop for workstation in workstations-in-service
	as gensym-window = (window-for-workstation workstation)
	as g2-window? = (g2-window-for-gensym-window? gensym-window)
	doing
    (cond ((null g2-window?))
	  ((not (logbook-views-p gensym-window)))
	  (t
	   (case preference
	     (prefer-native
	      (cond ((and new-value (use-native-logbook-p gensym-window))
		     (hide-logbook-in-g2-window g2-window?)
		     (show-native-logbook gensym-window))
		    ((native-logbook? gensym-window)
		     (manage-logbook-view (native-logbook? gensym-window) 'destroy)
		     (show-logbook-in-g2-window g2-window?))))
	     (include-date
	      (when (native-logbook? gensym-window)
		(manage-logbook-view (native-logbook? gensym-window)
				     'set-include-date-in-title (not new-value)))))))))


;;;; Native Message Board


(defun use-native-message-board-p (gensym-window)
  (and (prefer-native-message-board message-board-parameters)
       (logbook-views-p gensym-window)))
    
(defun native-message-board-p (native-window)
  (eq native-window (native-message-board? (native-window-gensym-window native-window))))

(defun fixnum-lessp (a b)
  (<f a b))

(defmacro do-message-board-messages ((message) &body body)
  `(when (current-message-board?)
     (loop for ,message being each subblock of current-message-board?
	   doing
       (when (and (frame-of-class-p ,message 'message)
		  (message-serial-number? ,message)) ; Should always be true.
	 ,@body))))

(defun find-message-board-message (serial-number?)
  (when serial-number?
    (do-message-board-messages (message)
      (when (eql serial-number? (message-serial-number? message))
	(return-from find-message-board-message message)))))

(defun get-message-board-messages ()
  (let ((messages ()))
    (do-message-board-messages (message)
      (gensym-push message messages))
    (sort-list messages #'fixnum-lessp #'message-serial-number-function)))

(defun ensure-native-message-board (gensym-window)
  (or (native-message-board? gensym-window)
      (values (setf (native-message-board? gensym-window) (create-native-message-board gensym-window))
	      t)))

(defun create-native-message-board (gensym-window)
  (let* ((dock? 'right)
         (neighbor? nil)
         (lbv (create-logbook-view gensym-window #w"Message Board"
                                   (initial-width-of-message-board message-board-parameters)
                                   (initial-height-of-message-board message-board-parameters)
                                   'message-board dock? neighbor?))
         (messages (get-message-board-messages)))

    (when (include-date-in-messages message-board-parameters)
      (manage-logbook-view lbv 'set-include-date-in-title nil))

    (populate-logbook-view lbv messages)
    (reclaim-gensym-list messages)
    lbv))

(defun show-native-message-board (gensym-window)
  (cond ((native-message-board? gensym-window)
	 (%set-native-window-state (native-message-board? gensym-window) 'autoshown))
	(t
	 (ensure-native-message-board gensym-window))))

(defun hide-native-message-board (gensym-window) ; TODO: Autohidden?
  (when (native-message-board? gensym-window)
    (%set-native-window-state (native-message-board? gensym-window) 'hidden)))

(defun append-message-to-all-native-message-boards (message)
  (append-message-to-all-logbook-views message nil 'message-board))

(defun note-native-message-board-preference-changed (preference new-value)
  (when (current-message-board?)
    (loop for workstation in workstations-in-service
	  as gensym-window = (window-for-workstation workstation)
	  as image-plane? = (image-plane-of-workspace-on-window
			      gensym-window current-message-board?)
	  as showable? = (workspaces-can-be-shown-at-this-kb-level-p
			   current-message-board? workstation)
	  doing
      (when (logbook-views-p gensym-window)
	(case preference
	  (prefer-native
	   (cond (new-value
		  (when image-plane?
		    (delete-image-plane image-plane?))
		  (when showable?
		    (show-native-message-board gensym-window)))
		 ((native-message-board? gensym-window)
		  (manage-logbook-view (native-message-board? gensym-window) 'destroy)
		  (when showable?
		    (show-message-board-in-window gensym-window)))))
	  (include-date
	   (when (native-message-board? gensym-window)
	     (manage-logbook-view (native-message-board? gensym-window)
				  'set-include-date-in-title (not new-value)))))))))


;;;; Tabular Views

;; New implementation for 83b0 -fmw, 11/1/06

;;; The special variable `tabular-view-action' is bound during argument
;;; preprocessing to the top-level action being processed.  It affects the exact
;;; types allowed for various attributes.

(defvar tabular-view-action nil)

(def-type-parameter tabular-view-options-type
    (structure
      #.(append
	  (cadr view-properties-type)
	  '((background-color symbol)
	    (text-color symbol)
	    (gridlines truth-value)
	    (gridline-color symbol)
	    (sortable truth-value)	; Old name: allow-sort-rows
	    (row-height integer)	; TODO: pixels or dialog units
	    (single-selection truth-value)
	    (columns (sequence))
	    (rows (sequence))
	    (selected-rows (sequence))
	    (sort-column integer)
	    (sorting-order symbol)
	    (user-data item-or-datum)))))

(def-type-parameter tabular-view-action-type
    (member destroy
	    add-row add-rows rows
	    modify-row modify-rows replace-row replace-rows
	    replace-cells modify-cells
	    select-row deselect-row selected-rows deselect-all-rows
	    remove-row remove-rows remove-all-rows remove-selected-rows
	    add-column add-columns columns
	    modify-column modify-columns
	    remove-column remove-columns remove-all-columns
	    gridlines gridline-color sortable single-selection
	    background-color text-color
	    row-height
	    sort-rows
            add-rows-to-top
	    font-size-change ;;;added by SoftServe
	    change-sort
            ))

(def-type-parameter tabular-view-column-designation-type
    integer)				; TODO: Maybe allow text

(def-type-parameter tabular-view-column-type
    (or text
        (structure ((text-value text)
                    (width (or integer (member header-width text-width)))
                    (icon item-or-datum)
                    (alignment (member left center right))))))

(def-type-parameter tabular-view-add-column-type
    (or text
        (structure ((text-value text)
                    (width (or integer (member header-width text-width)))
                    (icon item-or-datum)
                    (alignment (member left center right))
		    (column integer)	; Insert position
		    (cells (sequence))	; Initial contents of column
                    (row-values (sequence))))))	; Old name

(def-type-parameter tabular-view-logical-id-type
    (or number symbol text))

(defmacro tabular-view-logical-id-equal-p (logical-id-1 logical-id-2)
  `(equalw ,logical-id-1 ,logical-id-2)) ; Works for managed floats!
		 
(def-type-parameter tabular-view-row-type
    (or text
	(sequence)
	(structure
	  ((logical-id #.tabular-view-logical-id-type)
	   (position #.tabular-view-logical-id-type) ; Logical ID of insert position
	   (text-color symbol)
	   (background-color symbol)
	   (row-values (sequence))	; Old name
	   (cells (sequence))))))

;; Type for an existing row. Logical-id is required, and so it has to be a structure.
(def-type-parameter tabular-view-replace-row-type
    (structure
      ((logical-id #.tabular-view-logical-id-type)
       (text-color symbol)
       (background-color symbol)
       (row-values (sequence))		; Old name
       (cells (sequence)))
      (and logical-id)))

(def-type-parameter tabular-view-cell-type
    (or text
	(structure
	  ((text-value text)
	   (icon item-or-datum)))))

;; A cell in a column
(def-type-parameter tabular-view-column-cell-type
    (or text
	(structure
	  ((logical-id #.tabular-view-logical-id-type)
	   (text-value text)
	   (icon item-or-datum)))))

;; A cell with row&column indicies.
(def-type-parameter tabular-view-replace-cell-type
    (structure
      ((logical-id #.tabular-view-logical-id-type)
       (column integer)
       (index integer)			; Old name
       (text-value text)
       (text-color symbol)		; FIXME: Undocumented??
       (background-color symbol)	; FIXME: Undocumented??
       (icon item-or-datum))
      (and logical-id (or column index))))

(defun tabular-view-column-type ()
  (case tabular-view-action
    ((add-column add-columns)
     tabular-view-add-column-type)
    (t
     tabular-view-column-type)))

(defun tabular-view-cell-type ()
  (case tabular-view-action
    ((add-column add-columns)
     tabular-view-column-cell-type)
    (replace-cells
     tabular-view-replace-cell-type)
    (t
     tabular-view-cell-type)))

(def-structure (tabular-view
		 (:include native-view)
		 (:constructor make-tabular-view-1)
		 (:reclaimer reclaim-tabular-view-1)
		 #+development (:print-function print-native-window))
  (tabular-view-next-row-id 0)
  (tabular-view-rows nil)		; Gensym alist of (logical-id . row-id)
  (tabular-view-selected-row-ids nil)	; Gensym list of row-id's
  (tabular-view-user-data nil))

(defun make-tabular-view (gensym-window)
  (let ((tbv (make-tabular-view-1)))
    (setf (native-window-gensym-window tbv) gensym-window)
    tbv))

(defun initialize-tabular-view (tbv callback container user-data options)
  (initialize-native-view tbv (native-window-gensym-window tbv)
			  'g2-tabular-view container options callback)
  (setf (tabular-view-user-data tbv) (get-reference-to-item-if-item
				       (copy-if-evaluation-value user-data)))
  tbv)

(def-structure-method clean-up-structure (tabular-view)
  (tabular-view-delete-all-rows tabular-view)
  (reclaim-if-evaluation-value (tabular-view-user-data tabular-view))
  (setf (tabular-view-user-data tabular-view) nil)
  (funcall-superior-method tabular-view))

(defun reclaim-tabular-view (tbv)
  (reclaim-native-window tbv))

(defun tabular-views-p (gensym-window)
  (and (nms-controls-p gensym-window) ; TWNG
       (window-supports-tabular-views gensym-window)))

(defun tabular-views-window-or-stack-error (g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (tabular-views-p gensym-window)
      (ui-stack-error "Tabular views are not supported on ~NF" g2-window))
    gensym-window))


;; Map logical ID <-> row ID (unique)

(defun %tabular-view-find-row (tbv logical-id? row-id?)
  (loop for cell in (tabular-view-rows tbv)
	as (logical-id . row-id) = cell
	when (or (tabular-view-logical-id-equal-p logical-id? logical-id)
		 (eql row-id? row-id))
	  return cell))

(defun %tabular-view-reclaim-cell (cell)
  (reclaim-unboxed-evaluation-value (car cell))
  (reclaim-gensym-cons cell))

(defun tabular-view-add-logical-id (tbv logical-id row-id)
  (gensym-push (gensym-cons (unbox-evaluation-value logical-id)
			    row-id)
	       (tabular-view-rows tbv)))

(defun tabular-view-delete-all-rows (tbv)
  (reclaim-gensym-list (tabular-view-selected-row-ids tbv))
  (setf (tabular-view-selected-row-ids tbv) nil)
  (tabular-view-reclaim-rows tbv))

(defun tabular-view-reclaim-rows (tbv)
  (loop for cell in (tabular-view-rows tbv) doing
    (%tabular-view-reclaim-cell cell))
  (reclaim-gensym-list (tabular-view-rows tbv))
  (setf (tabular-view-rows tbv) nil))

(defun tabular-view-get-logical-id (tbv row-id)
  (car (%tabular-view-find-row tbv nil row-id)))

(defun tabular-view-get-row-id (tbv logical-id)	; NOTE: This may be non-unique
  (cdr (%tabular-view-find-row tbv logical-id nil)))

(defun tabular-view-delete-rows (tbv row-ids)
  (loop for row-id in row-ids doing
    (tabular-view-delete-row tbv row-id)))

(defun tabular-view-delete-row (tbv row-id)
  (let ((cell? (%tabular-view-find-row tbv nil row-id)))
    (when cell?
      (tabular-view-update-selected-rows tbv 'deselect row-id)
      (setf (tabular-view-rows tbv) (delete-gensym-element cell? (tabular-view-rows tbv)))
      (%tabular-view-reclaim-cell cell?))))

(defun tabular-view-update-selected-rows (tbv event row-id)
  (case event
    (select
     (gensym-pushnew row-id (tabular-view-selected-row-ids tbv)))
    (deselect
     (setf (tabular-view-selected-row-ids tbv)
	   (delete-gensym-element row-id (tabular-view-selected-row-ids tbv)))))
  (tabular-view-selected-row-ids tbv))

(defun tabular-view-selected-rows-as-sequence (tbv)
  (allocate-evaluation-sequence
    (loop for row-id in (tabular-view-selected-row-ids tbv)
	  as logical-id? = (tabular-view-get-logical-id tbv row-id)
	  if logical-id?		; Should always be true.
	    collect (copy-if-evaluation-value logical-id?) using eval-cons)))

(defun tabular-view-find-row-or-stack-error (tbv logical-id-ev)
  (or (tabular-view-get-row-id tbv logical-id-ev) ; TODO: Assuming evalue == lisp value
      (ui-stack-error "Tabular-view row with logical-id ~NV not found." logical-id-ev)))

(defun tabular-view-cells-evalue (estructure)
  (or (evaluation-structure-slot estructure 'cells)
      (evaluation-structure-slot estructure 'row-values))) ; Backwards-compat

(defun preprocess-tabular-view-rows (tbv evalue?)
  (when evalue?
    (loop for row being each evaluation-sequence-element of evalue?
	  collect (preprocess-tabular-view-row tbv row)
	    using gensym-cons)))

(defun preprocess-tabular-view-replace-rows (tbv evalue?)
  (when evalue?
    (loop for row being each evaluation-sequence-element of evalue?
	  collect (preprocess-tabular-view-replace-row tbv row)
	    using gensym-cons)))

(defun preprocess-tabular-view-columns (tbv evalue?)
  (when evalue?
    (loop for column being each evaluation-sequence-element of evalue?
	  collect (preprocess-tabular-view-column tbv column)
	    using gensym-cons)))

(defun preprocess-tabular-view-cells (tbv evalue?)
  (when evalue?
    (loop for cell being each evaluation-sequence-element of evalue?
	  collect (preprocess-tabular-view-cell tbv cell)
	    using gensym-cons)))

(defun preprocess-tabular-view-logical-ids (tbv evalue?)
  (when evalue?
    (loop for logical-id being each evaluation-sequence-element of evalue?
	  collect (tabular-view-find-row-or-stack-error tbv logical-id)
	    using gensym-cons)))

;; Returns (row-id cells . plist), processed by TWNG in tabular-view-add-rows-1
(defun preprocess-tabular-view-row (tbv evalue)
  (check-type-or-stack-error evalue tabular-view-row-type)
  (multiple-value-bind (cells plist logical-id?)
      (cond ((evaluation-text-p evalue)
	     (gensym-list (unbox-evaluation-value evalue)))
	    ((evaluation-sequence-p evalue)
	     (preprocess-tabular-view-cells tbv evalue))
	    ((evaluation-structure-p evalue)
	     (values (preprocess-tabular-view-cells tbv (tabular-view-cells-evalue evalue))
		     (preprocess-tabular-view-structure tbv evalue '(logical-id cells row-values))
		     (evaluation-structure-slot evalue 'logical-id))))
    (let* ((row-id (prog1 (tabular-view-next-row-id tbv)
		     (incff (tabular-view-next-row-id tbv))))
	   (logical-id (or logical-id? row-id)))  ; Default logical-id = counter.
      (tabular-view-add-logical-id tbv logical-id row-id)
      (gensym-cons row-id (gensym-cons cells plist)))))

;; Similar, but logical-id is required.
(defun preprocess-tabular-view-replace-row (tbv evalue)
  (check-type-or-stack-error evalue tabular-view-replace-row-type)
  (let ((row-id (tabular-view-find-row-or-stack-error tbv (evaluation-structure-slot evalue 'logical-id)))
	(cells (preprocess-tabular-view-cells tbv (tabular-view-cells-evalue evalue)))
	(plist (preprocess-tabular-view-structure tbv evalue '(logical-id cells))))
    (gensym-cons row-id (gensym-cons cells plist))))

(defun preprocess-tabular-view-column (tbv evalue)
  (check-type-or-stack-error evalue (tabular-view-column-type))
  (cond ((evaluation-text-p evalue)
	 (unbox-evaluation-value evalue))
	((evaluation-structure-p evalue)
	 (preprocess-tabular-view-structure tbv evalue))))

(defun preprocess-tabular-view-cell (tbv evalue)
  (check-type-or-stack-error evalue (tabular-view-cell-type))
  (cond ((evaluation-text-p evalue)
	 (unbox-evaluation-value evalue))
	((not (evaluation-structure-p evalue))
	 nil)				; Can't happen
	((and (=f 1 (evaluation-structure-length evalue)) ; Optimize solitary text-value
	      (evaluation-structure-slot evalue 'text-value))
	 (copy-evaluation-value (evaluation-structure-slot evalue 'text-value)))
	((evaluation-structure-p evalue)
	 (preprocess-tabular-view-structure tbv evalue))))

;; `Option' here can be a property or action name. Second return value is new
;; option name to use, if changed.
(defun preprocess-tabular-view-option (tbv option evalue)
  (case option
    (sort-column
      (sort-column-value-or-stack-error evalue))
    (sorting-order
      (sorting-order-value-or-stack-error evalue))
    ((background-color text-color gridline-color)
     (rgb-color-value-or-stack-error evalue)) ; NOTE: wants lisp not evalue
    (icon
     (native-icon-handle-or-stack-error
       (native-window-gensym-window tbv) evalue)) ; NOTE: ditto
    ((rows add-rows add-rows-to-top) ;Modified by SoftServe
     (preprocess-tabular-view-rows tbv evalue))
    (add-row
     (values (gensym-list (preprocess-tabular-view-row tbv evalue))
	     'add-rows))
    ((replace-rows modify-rows)
     (preprocess-tabular-view-replace-rows tbv evalue))
    (replace-row
     (values (gensym-list (preprocess-tabular-view-replace-row tbv evalue))
	     'replace-rows))
    (modify-row
     (values (gensym-list (preprocess-tabular-view-replace-row tbv evalue))
	     'modify-rows))
    (remove-row
     (let ((row-id (tabular-view-find-row-or-stack-error tbv evalue)))
       (tabular-view-delete-row tbv row-id)
       row-id))

    (remove-rows
     (let ((row-ids (preprocess-tabular-view-logical-ids tbv evalue)))
       (tabular-view-delete-rows tbv row-ids)
       (values row-ids 'remove-row)))
    (remove-selected-rows
     (let ((row-ids (copy-list-using-gensym-conses (tabular-view-selected-row-ids tbv))))
       (tabular-view-delete-rows tbv row-ids)
       (values row-ids 'remove-row)))
    (remove-all-rows
     (tabular-view-delete-all-rows tbv))

    ((select-rows selected-rows deselect-rows)
     (preprocess-tabular-view-logical-ids tbv evalue))
    (logical-id
     (values (tabular-view-find-row-or-stack-error tbv evalue)
	     'row-id))
    ((select-row deselect-row position)
     (tabular-view-find-row-or-stack-error tbv evalue))

    ;; Column operations.
    ((columns add-columns modify-columns)
     (preprocess-tabular-view-columns tbv evalue))
    (add-column
     (values (gensym-list (preprocess-tabular-view-column tbv evalue))
	     'add-columns))
    (remove-column
     (check-type-or-stack-error evalue tabular-view-column-designation-type)
     (unbox-evaluation-value evalue))
    (remove-columns
     (check-type-or-stack-error evalue '(sequence integer)) ; TODO: Column-designations
     (values (unbox-evaluation-value evalue)
	     'remove-column))		; NOTE: Remove-column accepts either an atom or a list
    (modify-column
     (values (gensym-list (preprocess-tabular-view-column tbv evalue))
	     'modify-columns))

    ((cells row-values) ; Old name
     (values (preprocess-tabular-view-cells tbv evalue)
	     'cells))
    ((replace-cells modify-cells)
     (preprocess-tabular-view-cells tbv evalue))
    ((column index)			; Old name
     (values (unbox-evaluation-value evalue)
	     'column))
    (t
     (unbox-evaluation-value evalue))))

(defun preprocess-tabular-view-structure (tbv evalue &optional skip)
  (loop with (slot* value*)
	for (slot . ev) being each evaluation-structure-pair of evalue
	unless (memq slot skip)
	  do (multiple-value-setq (value* slot*)
	       (preprocess-tabular-view-option tbv slot ev)) and
	  collect (or slot* slot) using gensym-cons and
	  collect value* using gensym-cons))

(defun-for-system-procedure g2-ui-create-tabular-view (title callback options g2-window)
  (check-type-or-stack-error options tabular-view-options-type)
  (let* ((gensym-window (tabular-views-window-or-stack-error g2-window))
	 (container (evaluation-structure-slot options 'container 'mdi-child))
	 (user-data (evaluation-structure-slot options 'user-data))
	 (tbv (make-tabular-view gensym-window))
	 (options* (preprocess-tabular-view-structure tbv options '(container user-data))))
    
    ;; Options* is an unboxed evaluation value, so we can now post-process it
    ;; for view options, which may also incur stack errors.
    (setq options* (preprocess-icon-options gensym-window options*))
    (setq options* (preprocess-container-options gensym-window options* 'g2-tabular-view))

    ;; Unfortunately, we have to cram the title into the options plist.
    (setq options* (mutate-gensym-plist options* 'title (copy-text-string (evaluation-text-value title))))

    ;; Finally, now that we are safe from stack errors, finalize the view structure.
    (initialize-tabular-view tbv callback container user-data options*)
    (manage-tabular-view tbv 'create options*)
    (reclaim-unboxed-evaluation-value options*)
    (reclaim-if-evaluation-value title)
    (reclaim-if-evaluation-value callback)
    (reclaim-if-evaluation-value options)
    (native-window-handle tbv)))

(defun-for-system-procedure g2-ui-manage-tabular-view (action handle ev-arg g2-window)
  (check-type-or-stack-error action tabular-view-action-type)
  (let* ((gensym-window (tabular-views-window-or-stack-error g2-window))
	 (tbv (find-native-view-or-stack-error gensym-window handle 'g2-tabular-view))
	 (tabular-view-action action))
    (case action
      (destroy
       (manage-tabular-view tbv action nil)
       (reclaim-tabular-view tbv))
      (t
       (multiple-value-bind (arg* action*)
	   (preprocess-tabular-view-option tbv action ev-arg)
	 (manage-tabular-view tbv (or action* action) arg*)
	 (reclaim-unboxed-evaluation-value arg*))))
    (reclaim-if-evaluation-value ev-arg)
    (reclaim-if-evaluation-value handle)))

(defun manage-tabular-view (tbv action arg)
  (let ((gensym-window (native-window-gensym-window tbv))
	(handle (native-window-handle tbv)))
    (cond ((icp-window-p gensym-window)
	   (with-icp-window-if-needed (gensym-window)
	     (send-icp-manage-tabular-view gensym-window action handle arg)))
	  (t
	   (manage-tabular-view-1 gensym-window action handle arg)))))

(defun tabular-view-event-name (event-code keycode)
  (case event-code
    (1 'select)				; Sync with twng/c/TabularView.h
    (2 'deselect)
    (3 (mouse-click-event-name 'left-click keycode))
    (4 (mouse-click-event-name 'middle-click keycode))
    (5 (mouse-click-event-name 'right-click keycode))
    (6 'key-pressed)
    (7 'selection-changed)
    (t nil)))

(define-event-handler handle-tabular-view-message ((gensym-window window) event-plist x-in-window y-in-window)
  (let* ((handle (getf event-plist 'window -1))
	 (tbv? (find-native-window gensym-window handle 'g2-tabular-view))
	 (event? (getf event-plist 'event))
	 (keycode (getf event-plist 'key 0))
	 (row-id? (getf event-plist 'row))
	 (column? (getf event-plist 'column))
	 (label? (getf event-plist 'value)) ; Text of column 0 of row (optional?)
	 (event-name? (tabular-view-event-name event? keycode)))
    (when (and tbv? event-name?)
      ;; TODO: Share this code with tree-views, etc.
      (multiple-value-bind (user-window-x user-window-y)
	  (gensym-window-point-to-user-window-point gensym-window x-in-window y-in-window)
	(let ((keysym?
		(if (>f keycode 0)
		    (parseable-symbol-from-key-code (canonicalize-key-code keycode))))
	      (logical-id?
		(tabular-view-get-logical-id tbv? row-id?))
	      (update-selection?
		(memq event-name? '(select deselect))))
	  
	  ;; Update G2's cache of selected rows.
	  (when (and row-id? update-selection?)
	    (tabular-view-update-selected-rows tbv? event-name? row-id?))

	  (invoke-view-callback tbv? event-name?
				logical-id?
				(nconc
				  (if label? (eval-list 'label (copy-if-text-string label?)))
				  (if column? (eval-list 'column column?))
				  (if keysym? (eval-list 'key keysym?))
				  (gensym-list 'selected-rows
					       (tabular-view-selected-rows-as-sequence tbv?))
				  (gensym-list 'x user-window-x 'y user-window-y))
				(tabular-view-user-data tbv?))

	  ;; If we're part of a custom dialog, then call its update or gesture
	  ;; callback.
	  (let ((component? (native-view-dialog-component? tbv?)))
	    (when component?
	      (case event-name?
		((select deselect selection-changed)
		 (when (or (not (window-supports-tabular-view-selection-changed-events gensym-window))
			   (eq event-name? 'selection-changed))
		   (call-dialog-update-callback-if-any component? gensym-window)))
		(t
		 (call-dialog-gesture-callback-if-any
		   component? keycode
		   (or logical-id? -1)
		   (or column? -1)
		   x-in-window y-in-window))))))))))


;;;; Dialog API Adapters for Tabular Views


;; Called from add-tabular-view-to-dialog (CONTROLS)
(defun create-tabular-view-in-dialog (gensym-window dialog-handle component-id
						    columns rows selected-rows
                                                    sort-column sorting-order
						    row-height text-color background-color
						    gridlines gridline-color allow-sort-rows single-selection)
  (let* ((tbv (make-tabular-view gensym-window))
	 (plist
	   (nconc
	     (gensym-list
	       'container dialog-handle
	       'neighbor component-id)
	     (when columns
	       (gensym-list 'columns (preprocess-tabular-view-columns tbv columns)))
	     (when rows
	       (gensym-list 'rows (preprocess-tabular-view-rows tbv rows)))
	     (when selected-rows
	       (gensym-list 'selected-rows (preprocess-tabular-view-logical-ids tbv selected-rows)))
	     (when sort-column
	       (gensym-list 'sort-column (preprocess-tabular-view-option tbv 'sort-column sort-column)))
	     (when sorting-order
	       (gensym-list 'sorting-order (preprocess-tabular-view-option tbv 'sorting-order sorting-order)))
	     (when row-height
	       (gensym-list 'row-height (preprocess-tabular-view-option tbv 'row-height row-height)))
	     (when text-color
	       (gensym-list 'text-color (preprocess-tabular-view-option tbv 'text-color text-color)))
	     (when background-color
	       (gensym-list 'background-color
			    (preprocess-tabular-view-option tbv 'background-color background-color)))
	     (when gridlines
	       (gensym-list 'gridlines (preprocess-tabular-view-option tbv 'gridlines gridlines)))
	     (when gridline-color
	       (gensym-list 'gridline-color (preprocess-tabular-view-option tbv 'gridline-color gridline-color)))
	     (when allow-sort-rows
	       (gensym-list 'sortable (preprocess-tabular-view-option tbv 'sortable allow-sort-rows)))
	     (when single-selection
	       (gensym-list 'single-selection
			    (preprocess-tabular-view-option tbv 'single-selection single-selection))))))
    (initialize-tabular-view tbv nil dialog-handle nil plist)
    (manage-tabular-view tbv 'create plist)
    (reclaim-unboxed-evaluation-value plist)
    tbv))

;; Can stack-error
(defun manage-tabular-view-in-dialog (tbv action ev-arg)
  (case action				; Adjust some action names.
    (remove-all-selected-rows (setq action 'remove-selected-rows)))
  (let ((tabular-view-action action))
    (multiple-value-bind (arg* action*)
	(preprocess-tabular-view-option tbv action ev-arg)
      (manage-tabular-view tbv (or action* action) arg*)
      (reclaim-unboxed-evaluation-value arg*))))

(def-gensym-c-function c-get-hbu
    (:fixnum-int "g2ext_get_hbu")
  ())

(def-gensym-c-function c-get-vbu
    (:fixnum-int "g2ext_get_vbu")
  ())

(defun-for-system-procedure g2-ui-get-dialog-base-units (g2-window)
  (if (g2-enterprise-p)
    (let ((gensym-window? (map-to-gensym-window-or-stack-error g2-window)))
      (if (twng-p gensym-window?)
        (let ((hbu (c-get-hbu))
              (vbu (c-get-vbu)))
          (values hbu vbu))
        (ui-stack-error
          "Get dialog base units is not supported on ~NF" g2-window)))
    (stack-error
      cached-top-of-stack
      "g2-ui-get-dialog-base-units is only supported in Enterprise edition")))
