;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module DIALOGS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Fred White, John Valente, Allan Scott



;;;; Introduction

;;; This file is part of Telewindows and G2, and contains code which is shared
;;; between them to implement various (though not necessarily all) sorts of
;;; dialogs.  Note that most of the real (i.e., G2-side) implementation of
;;; custom dialogs is in CONTROLS.  This file mostly defines ICP messages,
;;; Gensym C functions, and other things of that nature.


;;;; Forward References

(declare-forward-references
  (process-view-init-plist function)
  (encode-dock-and-neighbor function)
  (image-plane-of-workspace function workstation)
  (serve-text-of-attribute function roles))


;;;; Telewindows Deferred Actions


;;; The variable `tw-deferred-actions' is queue of actions to perform at the
;;; next opportunity in tw-event-loop, outside of an ICP message handling
;;; context.  Each action is an ICP-LIST of function . args.

(def-system-variable tw-deferred-actions DIALOGS (:funcall make-queue))


;;; The macro `with-deferred-execution-in-tw' defers applying function to args
;;; until the next time around the tw-event-loop, outside of ICP message
;;; handling.  The function owns the arguments and is responsible ensuring they
;;; are still valid when the function is called, and for reclaiming them as
;;; needed.

;;; You must carefully consider each deferred function to decide whether
;;; plucking it out of the ICP message stream and executing it at a later time,
;;; out of its usual order, works.

(defmacro with-deferred-execution-in-tw (options (function &rest args))
  (declare (ignore options))
  `(progn
     #+development (when nil (,function ,@args)) ; For compile-time checks.
     (queue-insert tw-deferred-actions (icp-list ',function ,@args))))

;; TODO: Check that function is declared funcallable.


;;; The function `tw-execute-deferred-actions' runs every deferred TW action in
;;; the queue.

(defun tw-execute-deferred-actions ()
  (loop for action = (queue-pop tw-deferred-actions)
        while action
        doing
    (apply (car action) (cdr action))
    (reclaim-icp-list action)))


;;; The function `discard-queued-modal-dialogs' discards all of the deferred TW
;;; actions which post any sort of modal dialog. We do this on KB reset, since
;;; the actions generally will make no sense to G2 at that point.

;;; At the moment, and probably in the future, all deferred TW actions are modal
;;; dialogs, since that is why they exist.

(defun discard-queued-modal-dialogs ()
  (loop for action = (queue-pop tw-deferred-actions)
        while action
        doing
    (dwarn "Discarding queued TW action ~s" action)
    (reclaim-icp-list action)))




;;;; Native Simple Dialogs


;;; A `simple dialog' or `native simple dialog' handles the simple case of a
;;; dialog with a message line (possibly wordwrapped as a paragraph) and either
;;; two or three buttons, implemented in the new UI (Windows) as a native
;;; dialog.  This corresponds with, and is called via, the dialogs created with
;;; enter-dialog, q.v.
;;;
;;; The buttons corresponding to arguments ok-string, cancel-string, and
;;; additional-string are optionally present. If an argument is the empty string
;;; (""), the button will not appear.
;;;
;;; The generated sender function `send-icp-simple-dialog' is always run on the
;;; G2 side only. It takes text-string arguments but will not be reclaim or
;;; incorporate them.
;;;
;;; The generated handler function `handle-icp-simple-dialog' is always run on
;;; the Telewindows side only.  It first hangs waiting for the (modal) dialog to
;;; end.  Then it enqueues a local event back to G2 through gensym-window with
;;; information about the result. The event will contain in its plist an
;;; indicator DIALOG-HANDLE whose value is the ICP argument value dialog-handle.
;;; The key code of the event be the key code for one of the following symbols
;;; based on one of the three possible outcomes of the dialog:
;;;
;;;   (1) SIMPLE-DIALOG-OK, if OK;
;;;   (2) SIMPLE-DIALOG-ADDITIONAL, if the additional choice is made; otherwise
;;;   (3) SIMPLE-DIALOG-CANCEL, if the cancel button is pressed or the
;;;       dialog is closed with the close box, or aborted with the ESC key)
;;;
;;; Which-to-make-default-button? may be OK, nil (the default, meaning OK),
;;; CANCEL, ADDITIONAL, or NONE.  Note: the which-to-make-default? argument is
;;; interpreted the same way as enter-dialog, q.v.
;;;
;;; The argument flags currently has no specified use. It's reserved for future
;;; use. By convention, zero should be passed in as its value.

(def-concept simple-dialog)


;;; The function `remove-unicode-line-breaks' removes unicode line breaks
;;; (#u2028) from string and reclaims it, returning a new string.

(defun remove-unicode-line-breaks (wide-string)
  (prog1
      (twith-output-to-wide-string
	(loop for i from 0 below (lengthw wide-string)
	      as ch = (charw wide-string i)
	      unless (eql ch #.%line-separator)
		do (twrite-char ch)))
    (reclaim-wide-string wide-string)))


(def-icp-message-type simple-dialog
    ((gensym-window gensym-window)
     (fixnum dialog-handle)		; G2 handle on dialog object. TW sends this back to G2.
     (wide-string caption)		; wide-string instead of text-string because
     (wide-string message-string)	; wide-string is not automatically reclaimed.
     (wide-string ok-string)
     (wide-string cancel-string)
     (wide-string additional-string)
     (symbol which-to-make-default?)
     (unsigned-integer flags))
  (declare (ignore flags))
  (with-deferred-execution-in-tw ()
    (simple-dialog-1 gensym-window (gensym-window-serial-number gensym-window)
                     'simple dialog-handle
                     caption message-string ok-string cancel-string additional-string
                     which-to-make-default? nil)))

(def-icp-message-type simple-dialog-ex
    ((gensym-window gensym-window)	; Same signature as ICP basic-dialog
     (symbol type)
     (fixnum handle)
     (wide-string caption)
     (wide-string message)
     (icp-tree plist))
  (with-deferred-execution-in-tw ()
    (simple-dialog-1 gensym-window (gensym-window-serial-number gensym-window)
                     type handle caption message
		     (copy-wide-string (getf plist 'ok-string #w""))
		     (copy-wide-string (getf plist 'cancel-string  #w""))
		     (copy-wide-string (getf plist 'additional-string  #w""))
		     (getf plist 'default-button)
		     plist)))

(defun simple-dialog-1
    (gensym-window serial type
                   dialog-handle caption
		   message-string ok-string cancel-string additional-string
		   which-to-make-default? plist)
  (when (gensym-window-has-not-been-reprocessed-p gensym-window serial)
    ;; Fix up string. Optimization: only needed for pre-8.1 G2s.
    (setq message-string (remove-unicode-line-breaks message-string))
    (let* ((native-window (native-window? gensym-window))
           (ok-id (key-code-for-key-symbol 'simple-dialog-ok))
           (cancel-id (key-code-for-key-symbol 'simple-dialog-cancel))
           (additional-id (key-code-for-key-symbol 'simple-dialog-additional))
	   (icon (dialog-icon-handle (getf plist 'icon 'question)))
           (checked-list?)
           (checkable? (getf plist 'checkable))
           (choice?
	     (case type
	       (simple
		(c-simple-dialog
		  native-window caption message-string
		  ok-string
		  (if (string=w ok-string #w"") 0 ok-id)
		  cancel-string
		  (if (string=w cancel-string #w"") 0 cancel-id)
		  additional-string
		  (if (string=w additional-string #w"") 0 additional-id)
		  (case which-to-make-default?
		    ((nil ok) ok-id)
		    (cancel cancel-id)
		    (additional additional-id)
		    (none 0))))
	       (listbox			; Actually a listbox + text + buttons.
		(let* ((rows (list-to-double-nul-string (getf plist 'rows)))
		       (columns (list-to-double-nul-string (getf plist 'columns)))
		       (buffer-size?
		         (if checkable? (getf plist 'row-count 0) 0))
		       (state-buffer?
		         (if (>f buffer-size? 0)
		           (obtain-simple-gensym-string buffer-size?)))
		       (rc
			 (c-list-box caption message-string rows columns icon
			             checkable? state-buffer? buffer-size?)))
		  
		  (when (=f rc 1)
		    (setf checked-list?
		      (loop for i from 0 below buffer-size?
		          as ch? = (char state-buffer? i)
		          when (eq ch? #\1)
		          collect i using gensym-cons)))
		  
		  (when state-buffer?
		    (reclaim-gensym-string state-buffer?))
		  (reclaim-wide-string rows)
		  (reclaim-wide-string columns)
		  (if (=f rc 1) ok-id cancel-id))))))
      (when choice?
	(enqueue-local-event
	  (native-window? gensym-window)
	  choice?
	  (c-x11-last-mouse-x-position native-window)
	  (c-x11-last-mouse-y-position native-window)
	  (c-x11-last-event-time native-window)
	  (gensym-list
	    'dialog-handle dialog-handle
	    'checkable checkable?
	    'checked-items checked-list?)))))
  (reclaim-wide-string caption)
  (reclaim-wide-string message-string)
  (reclaim-wide-string ok-string)
  (reclaim-wide-string cancel-string)
  (reclaim-wide-string additional-string)
  (reclaim-icp-tree-with-text-strings plist))

;; Some thoughts on how flags may be used in the future: for specifying an icon
;; resource and/or indicating whether a dialog is modal or not.  Note that it's
;; either impossible or a quite a big hassle to change an ICP message type
;; signature once it's been released. (MHD 2/13/02)

;;; `c-simple-dialog' pops up the dialog, tracks modally, and returns the ID of
;;; of the choice or 0 if cancelled.  Note that all string arguments are text
;;; strings (Unicode wide strings).

(def-gensym-c-function c-simple-dialog
    (:fixnum-int "g2ext_simple_dialog")
  ((:pointer window)
   (:wide-string caption)
   (:wide-string message-string)
   (:wide-string ok-string)
   (:fixnum-int ok-id)
   (:wide-string cancel-string)
   (:fixnum-int cancel-id)
   (:wide-string additional-string)
   (:fixnum-int additional-id-or-zero)
   (:fixnum-int id-of-default)))


;;; The gensym-c-function `c-list-box' posts a resizable OK/Cancel dialog with a
;;; message and a multicolumn list-view of arbitrary strings. Returns 1 if OKed
;;; or 0 if cancelled.

(def-gensym-c-function c-list-box
    (:fixnum-int "g2ext_list_box")
  ((:wide-string caption)
   (:wide-string message)
   (:wide-string rows)
   (:wide-string columns)
   (:fixnum-int icon)
   (:fixnum-int checkable)
   (:string checked-buffer)
   (:fixnum-int buffer-size)))


;;;; Native Basic Dialogs


;;; A `basic dialog' is one of these uncomplicated, modal, native, built-in
;;; dialogs. To get some code sharing, they share a single ICP message and event
;;; keycode.

;;; Unlike simple dialogs, they are posted in FIFO order, and do not push a
;;; workstation context on the G2 side. They don't need to, since Windows takes
;;; care of modal restrictions (eg, you can't access the menu bar)

(def-concept basic-dialog)
;; Matches IDOK, etc in winuser.h
(defconstant win32-choice-symbols #(UNKNOWN OK CANCEL ABORT RETRY IGNORE YES NO CLOSE HELP))

(defconstant known-basic-dialog-types
  '(message confirmation yes-no yes-no-cancel retry-cancel query))

(defconstant known-basic-dialog-icons '(question information warning error))



(defun post-basic-dialog (gensym-window handle type message &optional caption? icon-name?)
  (with-icp-window (gensym-window)
    (send-icp-basic-dialog gensym-window type handle
                            (or caption? #w"")
                            message
                            (dialog-icon-handle icon-name?)
                            ())))

(defun dialog-icon-handle (name)
  (case name
    (question dlg-icon-question)
    (information dlg-icon-information)
    (warning dlg-icon-warning)
    (error dlg-icon-error)
    (t dlg-icon-question)))

(def-icp-message-type basic-dialog
    ((gensym-window gensym-window)
     (symbol type)                        ; message, confirmation, query, ...
     (fixnum handle)                        ; G2 handle on dialog object. TW sends this back to G2.
     (wide-string caption)                ; The title for the dialog window. "" means default.
     (wide-string message)
     (fixnum icon)
     (icp-tree plist))
  (with-deferred-execution-in-tw ()
    (basic-dialog-1 gensym-window (gensym-window-serial-number gensym-window)
                     type handle caption message icon plist)))

(defun basic-dialog-1 (gensym-window serial type handle caption message icon plist)
  (when (gensym-window-has-not-been-reprocessed-p gensym-window serial)
    (let ((native-window (native-window? gensym-window))
          (font-size (or (getf plist 'font-size) 0)) ; Defaulted down in twpro.c
          (caption (if (>f (lengthw caption) 0)
                       caption
                       (copy-as-wide-string (system-window-title-string current-system-name))))
          (choice? nil)
          (response? nil))
      ;; Fix up string. Optimization: only needed for pre-8.1 G2s.
      (setq message (remove-unicode-line-breaks message))
      (case type
        (message
         (setq choice? (c-message-box native-window caption message mb-ok icon)))
        (confirmation
         (setq choice? (c-message-box native-window caption message mb-okcancel icon)))
        (yes-no
         (setq choice? (c-message-box native-window caption message mb-yesno icon)))
        (yes-no-cancel
         (setq choice? (c-message-box native-window caption message mb-yesnocancel icon)))
        (retry-cancel
         (setq choice? (c-message-box native-window caption message mb-retrycancel icon)))
        (query
         (let* ((buflen 1024)                        ; Size of dialog_text_result[] in twpro.c
                (buffer (obtain-text-string buflen)))
           (setq choice? (c-query-box native-window caption message font-size icon buffer buflen)
                 response? (and (>f choice? 0)
                                (copy-null-terminated-text-string buffer)))
           (reclaim-text-string buffer)))
        (t
         (setq choice? 'unsupported)
         (dwarn "Dialog type ~s not supported." type)))
      (when choice?
        (enqueue-local-event
          native-window
          (key-code-for-key-symbol 'basic-dialog)
          (c-x11-last-mouse-x-position native-window)
          (c-x11-last-mouse-y-position native-window)
          (c-x11-last-event-time native-window)
          (nconc (gensym-list 'type type 'handle handle)
                 (if (eq choice? 'unsupported)
                     (gensym-list 'error
                                  (twith-output-to-wide-string
                                    (tformat #w"Dialog type ~a not supported on this Telewindow."
                                             type))))
                 (if (<f 0 choice? (length win32-choice-symbols))
                     (gensym-list 'choice (svref win32-choice-symbols choice?)))
                 (if response?
                     (gensym-list 'response response?)))))))
  (reclaim-wide-string caption)
  (reclaim-wide-string message)
  (reclaim-icp-tree-with-text-strings plist))

;;; The gensym-c-function `c-message-box' posts a Win32 MessageBox, which has a
;;; fixed set of possible button and icon choices.

(def-gensym-c-function c-message-box
    (:fixnum-int "g2ext_message_box")
  ((:pointer window)
   (:wide-string caption)
   (:wide-string message)
   (:fixnum-int style)
   (:fixnum-int icon)))                        ; 0=Question, 1=Inform, 2=Warning, 3=Error

;;; The gensym-c-function `c-query-box' posts a modal "query box", which
;;; contains an icon, a message, a text input field, an OK button, and a Cancel
;;; button.

(def-gensym-c-function c-query-box
    (:fixnum-int "g2ext_query_box")
  ((:pointer window)
   (:wide-string caption)
   (:wide-string message)
   (:fixnum-int fontSize)
   (:fixnum-int icon)
   (:wide-string response)
   (:fixnum-int buflen)))





;;;; Telewindows About Box


;; See make-text-for-type-of-g2-license
(defun twrite-long-system-version-string ()
  (twrite-system-version (system-version current-system-name))
  (tformat " (~a)" build-identification-string))

(defun handle-about-box-event (workstation local-event)
  (declare (ignore local-event))
  (let ((gensym-window (window-for-workstation workstation)))
    (with-deferred-execution-in-tw ()
      (about-box-1 gensym-window (gensym-window-serial-number gensym-window)))))

(defun about-box-1 (gensym-window serial)
  (when (gensym-window-has-not-been-reprocessed-p gensym-window serial)
    (let ((version (twith-output-to-wide-string
                     (twrite-long-system-version-string)))
          (comments
            (twith-output-to-wide-string
              (cond ((<f release-quality-of-current-gensym-product-line release-quality)
                     (tformat "This is unreleased, ~a-quality software."
                             (case release-quality-of-current-gensym-product-line
                               (#.alpha-release-quality #w"Alpha")
                               (#.beta-release-quality #w"Beta")
                               (t #w"Prototype")))
                     (tformat " (~a)" build-identification-string))
                    (t
                     (tformat "Build: ~a" build-identification-string))))))
          (c-about-box (native-window? gensym-window) version comments)
      (reclaim-wide-string comments)
      (reclaim-wide-string version))))

(def-gensym-c-function c-about-box
    (:fixnum-int "g2ext_about_box")
  ((:pointer window)
   (:wide-string version)		; Eg: #w"7.0 Beta Rev. 0"
   (:wide-string comments)))		; Eg: #w"This is unreleased, Beta-quality software."




;;;; Native File Open/Save Dialog




;;; The function `obtain-pathname-buffer' returns a newly allocated,
;;; NUL-terminated wide string large enough for the longest pathname. Optionally
;;; initialized from initial-contents.

(defun obtain-pathname-buffer (&optional initial-contents)
  (let* ((len maximum-number-of-characters-in-pathname)
	 (buf (make-stringw len :initial-element (code-wide-character 0))))
    (when initial-contents
      (copy-portion-of-wide-string-into-wide-string
	initial-contents 0 (minf (wide-string-length initial-contents) len)
	buf 0))
    buf))


;;; The `file-dialog' ICP message provides fully general access to the native
;;; file open/save dialog on the given window (if supported). The dialog-handle
;;; fixnum and operation symbol are simply sent back to G2 uninterpreted and can
;;; be used by G2 to rendezvous the dialog result with its caller.

;;; For 7.0 alpha, the only caller is KB load/merge/save, which simply provides
;;; 0 for the handle and the desired KB function for the operation.

(def-icp-message-type file-dialog
    ((gensym-window gensym-window)
     (fixnum dialog-handle)		; Random fixnum to send back to G2.
     (symbol operation)			; Random symbol to send back to G2.
     (unsigned-integer flags)		; Bit0=Save/Open, Bit1=Server/client, Bits2-4=encoded os
     (wide-string title)
     (wide-string initial-pathname)
     (wide-string default-extension)
     (icp-tree filter)			; List of (label . wildcards)
     (icp-tree buttons))                ; List of (name type label . data).
  (with-deferred-execution-in-tw ()
    (file-dialog-1 gensym-window (gensym-window-serial-number gensym-window)
                   dialog-handle operation
                   flags
                   title
                   initial-pathname
                   default-extension
                   filter buttons nil)))

;;; The icp-message-type `file-dialog-ex' adds a plist of additional arguments,
;;; which may include a list of interesting directories, initial directory
;;; contents, etc.

(def-icp-message-type file-dialog-ex
    ((gensym-window gensym-window)
     (fixnum dialog-handle)		; Random fixnum to send back to G2.
     (symbol operation)			; Random symbol to send back to G2.
     (unsigned-integer flags)		; Bit0=Save/Open, Bit1=Server/client, Bits2-4=encoded os
     (wide-string title)
     (wide-string initial-pathname)
     (wide-string default-extension)
     (icp-tree filter)			; List of (label . wildcards)
     (icp-tree buttons)			; List of (name type label . data).
     (icp-tree plist))			; Additional arguments (places, listing, etc).
  (with-deferred-execution-in-tw ()
    (file-dialog-1 gensym-window (gensym-window-serial-number gensym-window)
                   dialog-handle operation
                   flags
                   title
                   initial-pathname
                   default-extension
                   filter buttons plist)))


;;; The function `file-dialog-1' posts a native file dialog, possibly with extra
;;; controls, and enqueues a local event with plist containing the chosen
;;; pathname and values from the controls.

(def-gensym-c-function c-file-dialog
    (:fixnum-int "g2ext_file_dialog")
  ((:pointer window)
   (:fixnum-int flags)                        ; Bit0=Save/Open, Bit1=Server/client
   (:wide-string title)
   (:wide-string initial-filename)                ; Just name.ext portion, or an empty string,
   (:wide-string initial-directory)
   (:wide-string default-extension)                ; Without the period.
   (:wide-string filter)
   (:wide-string drives)                           ; Local drives
   (:wide-string places)                        ; Places bar
   (:wide-string message)                ; Optional message
   (:wide-string checkboxes)                ; Optional checkboxes
   (:wide-string combobox)                ; Optional combo box
   (:string special)                        ; filename filled-in by special checkbox
   (:wide-string ok-button-label)        ; Alternate label for OK button. Default is Save or Open.
   (:wide-string cancel-button-label)
   (:wide-string response)                ; Initial/final checks[0], combo choice[1]
   (:wide-string buffer)                        ; Returned pathname
   (:fixnum-int buflen)))

(defun file-dialog-1
    (gensym-window gensym-window-serial-number
                   dialog-handle operation ; Simply passed back to G2.
                   flags                ; Bit0=Save/Open, Bit1=Server/client, Bits2-4=encoded os
                   title                ; Title of the dialog window
                   initial-pathname        ; initial directory and initial filename
                   default-extension        ; Supplied if user does not enter one.
                   filter                ; List of (label . wildcards)
                   buttons                ; List of (name type label . data)
                   plist)                ; icp-plist of other arguments.
  (when (gensym-window-has-not-been-reprocessed-p gensym-window
                                                  gensym-window-serial-number)
    (multiple-value-bind (message combobox combo-name combo-choices
                                  checkboxes checks special-string?
                                  ok-label cancel-label)
        (compute-file-dialog-extra-controls operation buttons)
      (let* ((native-window (native-window? gensym-window))
             (buffer-length maximum-number-of-characters-in-pathname)
             (buffer (make-wide-string-function buffer-length))
             (filter-as-string (compute-file-dialog-filter-string filter))
	     (drives-as-string (list-to-double-nul-string (getf plist 'drives)))
             (places-as-string (list-to-double-nul-string (getf plist 'places)))
             (os (decode-pathname-os (logandf #x7 (ashf flags -2))))
             (initial-filename (os-pathname-nondirectory initial-pathname os))
             (initial-directory (os-pathname-directory initial-pathname os))
             (response (allocate-byte-vector-16 2))
             (choice (progn
                       (setf (byte-vector-16-aref response 0) checks)
                       (c-file-dialog
                         native-window flags title
                         initial-filename initial-directory
                         default-extension filter-as-string 
			 drives-as-string places-as-string
                         message checkboxes combobox (or special-string? "")
                         ok-label cancel-label
                         response buffer buffer-length)))
             (pathname?
               (when (>f choice 0)        ; TODO: Distinguish error vs cancelled, and get error msg.
                 (copy-null-terminated-text-string buffer))))
        (reclaim-wide-string cancel-label)
        (reclaim-wide-string ok-label)
        (reclaim-wide-string buffer)
        (reclaim-wide-string filter-as-string)
	(reclaim-text-string drives-as-string)
        (reclaim-text-string places-as-string)
        (reclaim-text-string initial-filename)
        (reclaim-text-string initial-directory)
        (reclaim-wide-string checkboxes)
        (reclaim-wide-string combobox)
        (reclaim-wide-string message)
        (enqueue-local-event
          native-window
          (key-code-for-key-symbol 'file-dialog)
          (c-x11-last-mouse-x-position native-window)
          (c-x11-last-mouse-y-position native-window)
          (c-x11-last-event-time native-window)
          (nconc (gensym-list 'dialog-handle dialog-handle
                              'operation operation
                              'pathname pathname?)
                 (compute-file-dialog-final-checks buttons (byte-vector-16-aref response 0))
                 (when (<f (byte-vector-16-aref response 1) 32768)
                   (gensym-list combo-name (nth (byte-vector-16-aref response 1)
                                                combo-choices)))))
        (when special-string?
          (reclaim-gensym-string special-string?))
        (reclaim-byte-vector-16 response))))
  (reclaim-wide-string title)
  (reclaim-wide-string initial-pathname)
  (reclaim-wide-string default-extension)
  (reclaim-icp-tree-with-text-strings filter)
  (reclaim-icp-tree-with-text-strings buttons)
  (reclaim-icp-tree-with-text-strings plist))

;; Cf handle-file-dialog-message


;;; The C function `c-file-dialog' pops up a file open or file save dialog,
;;; tracks modally, and returns 1 if a pathname was chosen and 0 if
;;; cancelled. The pathname, if any, is returned in buffer. Info from added
;;; controls is provided and returned in response.

                ; Buffer size

;; copy-foreign-string-arg-if-appropriate


;;; The function `compute-file-dialog-filter-string' computes a newly consed
;;; gensym-string from an alist of (label . wildcards).  The filter string is a
;;; string of all of the elements of the alist, separated by NULs, and
;;; terminated an extra NUL. Wildcards are semicolon-separated.

;;; Example:
;;;   ((#w"Knowledge Bases" #w"*.kb" #w"*.kl") (#w"All" #w"*.*"))  -->
;;;   "Knowledge Bases\0*.kb;*.kl\0All\*.*\0\0"

(defun compute-file-dialog-filter-string (filter)
  (let* ((length (+f 1 (loop for element in filter
                             summing (loop for string in element
                                           summing (+f (lengthw string) 1)))))
         (buffer (make-wide-string length))
         (pos 0)
         (nul (code-charw 0)))
    (macrolet ((concat (stringw)
                 `(progn
                    (copy-portion-of-wide-string-into-wide-string
                      ,stringw 0 (lengthw ,stringw) buffer pos)
                    (incff pos (lengthw ,stringw))))
               (concat-char (charw)
                 `(progn (setf (scharw buffer pos) ,charw)
                         (incff pos))))
      (loop for (label . wildcards) in filter doing
        (concat label)
        (concat-char nul)
        (loop for (wildcard . more) on wildcards doing
          (concat wildcard)
          (if more (concat #w";") (concat-char nul))))
      (concat-char nul)
      buffer)))

(defun twrite-string-and-nul (string)
  (twrite-string string)
  (twrite-char (code-wide-character 0)))

(defun twrite-double-nul-strings (strings)
  (loop for string in strings
	do (twrite-string string)
	   (twrite-char #.%Null)
	finally (twrite-char #.%Null)))

(defun list-to-double-nul-string (strings)
  (twith-output-to-wide-string
    (twrite-double-nul-strings strings)))

(defun double-nul-string-to-list (wide-string)
  (loop with i = 0
        for j below (wide-string-length wide-string)
        when (and (char=w (charw wide-string j) #.%Null) (>f j i))
          collect (wide-string-substring wide-string i j) using gensym-cons and
          do (setq i (1+f j))))

;;; The function `compute-file-dialog-extra-controls' translates the list of
;;; buttons into a form convenient for the C routine to use to add extra
;;; controls to the file dialog box. Each button is a list of the form:
;;; (name type label . data), where type is TEXT, COMBOBOX, or CHECKBOX.

(defun compute-file-dialog-extra-controls (operation buttons)
  (let* ((nul (code-wide-character 0))
         (message (twith-output-to-wide-string
                    (loop for (name type label) in buttons doing
                      (when (eq type 'text)
                        (twrite-string-and-nul label)))
                    (twrite-char nul)))
         (combo-name nil)
         (combo-choices nil)
         (combobox (twith-output-to-wide-string
                     (loop for (name type label . symbols) in buttons doing
                       (when (eq type 'combobox)
                         (setq combo-name name ; Actually allow only one combobox.
                               combo-choices symbols)
                         (twrite-string label)
                         (twrite-char nul)
                         (loop for symbol in symbols doing
                           (twrite-symbol symbol)
                           (twrite-char nul))))
                     (twrite-char nul)))
         (special-string? nil)
         (checkboxes (twith-output-to-wide-string
                       (loop for (name type label checked magic?) in buttons doing
                         (when (eq type 'checkbox)
                           (when magic?                 ; Special checkbox.
                             (twrite-string #w"*")        ; Marks special checkbox for C code.
                             (setq special-string?
                                   (twith-output-to-gensym-string
                                     (twrite-string magic?))))
                           (twrite-string-and-nul label)))
                       (twrite-char nul)))
         (checks (loop with mask = 0
                       with bit = 1
                       for (name type label checked) in buttons
                       doing (when (eq type 'checkbox)
                               (when (or (eq checked t)
                                         (eq checked operation)) ; A little bit of eval.
                                 (setq mask (logior mask bit)))
                               (setq bit (ashf bit 1)))
                       finally (return mask)))
         (ok-label (twith-output-to-wide-string
                     (loop for (name type label) in buttons doing
                       (when (eq type 'ok)
                         (twrite-string-and-nul label)))
                     (twrite-char nul)))
         (cancel-label (twith-output-to-wide-string
                         (loop for (name type label) in buttons doing
                           (when (eq type 'cancel)
                             (twrite-string-and-nul label)))
                         (twrite-char nul))))
    (values message combobox combo-name combo-choices checkboxes checks
            special-string? ok-label cancel-label)))


;;; The function `compute-file-dialog-final-checks' computes a gensym plist with
;;; the final results from checkboxes checked in mask.

(defun compute-file-dialog-final-checks (buttons mask)
  (loop with bit = 1
        for (name type) in buttons
        when (and (eq type 'checkbox) (/=f (logandf bit mask) 0))
          collect name using gensym-cons
          and collect t using gensym-cons
        when (eq type 'checkbox)
          do (setq bit (ashf bit 1))))


;;;; Choose Directory Dialog

;; Access to SHBrowseForFolder()

(defconstant-for-case cd-post-client-dialog 0)	; Opcodes for ICP choose-directory
(defconstant-for-case cd-post-server-dialog 2)


(def-icp-message-type choose-directory
    ((gensym-window gensym-window)
     (fixnum handle)			; Random fixnum to send back to G2.
     (symbol operation)			; Random symbol to send back to G2.
     (unsigned-integer opcode)
     (wide-string pathname)		; Initial (directory) pathname
     (icp-tree options))
  (case opcode
    ((#.cd-post-client-dialog #.cd-post-server-dialog)
     (with-deferred-execution-in-tw ()
       (choose-directory-1 gensym-window (gensym-window-serial-number gensym-window)
			   handle operation opcode pathname options)))
    (t
     (let ((tree (pack-tree-for-choose-directory (getf options 'tree))))
       (c-choose-directory opcode #w"" #w"" #w"" tree #w"" #w"" #w"")
       (reclaim-wide-string tree)
       (reclaim-wide-string pathname)
       (reclaim-icp-tree-with-text-strings options)))))
     
(defun choose-directory-1 (gensym-window gensym-window-serial-number
					 handle operation opcode pathname options)
  (when (gensym-window-has-not-been-reprocessed-p gensym-window gensym-window-serial-number)
    (let* ((native-window (native-window? gensym-window))
	   (caption (getf options 'caption #w""))
	   (ok-label (getf options 'ok-button-label #w""))
	   (cancel-label (getf options 'cancel-button-label #w""))
	   (root (getf options 'root #w""))
	   (separator (getf options 'separator #w"/"))
	   (tree (pack-tree-for-choose-directory (getf options 'tree)))
	   (buffer (obtain-pathname-buffer pathname))
	   (result (c-choose-directory opcode caption buffer root tree separator ok-label cancel-label))
	   (pathname?
	     (when (>f result 0)
	       (copy-null-terminated-text-string buffer))))
      (reclaim-wide-string tree)
      (reclaim-wide-string buffer)
      (enqueue-local-event
	native-window
	(key-code-for-key-symbol 'file-dialog)
	(c-x11-last-mouse-x-position native-window)
	(c-x11-last-mouse-y-position native-window)
	(c-x11-last-event-time native-window)
	(gensym-list 'dialog-handle handle 'operation operation 'pathname pathname?))))
  (reclaim-wide-string pathname)
  (reclaim-icp-tree-with-text-strings options))

;; Pack a list of strings, or list of lists of strings into double/triple-nul
;; terminated wide string.
(defun pack-tree-for-choose-directory (tree)
  (twith-output-to-wide-string
    (loop for thing in tree doing
      (cond ((wide-string-p thing)
	     (twrite-string-and-nul thing))
	    ((consp thing)
	     (twrite-double-nul-strings thing))))
    (twrite-char #.%Null)))

(def-gensym-c-function c-choose-directory
    (:fixnum-int "g2ext_choose_directory")
  ((:fixnum-int opcode)			; Post dialog, add node, etc
   (:wide-string caption)
   (:wide-string pathname)		; Pathname buffer (I/O)
   (:wide-string root)			; Root directory
   (:wide-string tree)			; For server-dialog, initial tree contents
   (:wide-string separator)		; Separator char, as one-element string.
   (:wide-string ok-label)
   (:wide-string cancel-label)))


;;;; Native Debugger Dialog


(defconstant-for-case debugger-dialog-create 1)	; Opcodes. Keep in sync with ext/c/editor.c

(defun debugger-dialog-unpack-return-value (return-value)
  (let ((source-stepping-p (/=f 0 (logandf return-value debugger-source-stepping-flag)))
	(button (case (logandf return-value #xF)
		  (1 'continue)
		  (2 'disable-debugging)
		  (3 'pause))))
    (values button source-stepping-p)))

(defun manage-debugger-dialog (gensym-window opcode &optional
					     (line 0)
                                             (title #w"") (label #w"")
					     (source-code #w"") (environment #w"")
					     options)
  (with-icp-window (gensym-window)
    (send-icp-debugger-dialog
      gensym-window opcode title label source-code environment line options)))

(def-gensym-c-function c-add-debug-info
    (:pointer "g2ext_add_debug_info")
	((:pointer info-pointer)
	 (:wide-string proc-name)
     (:wide-string args)
     (:wide-string env)))
	 
(defun add-debug-info (info-pointer proc-name args env)
  (c-add-debug-info info-pointer proc-name args env))

(def-gensym-c-function c-debug-info-received
    (:fixnum-int "g2ext_debug_info_received")
	((:pointer info-pointer)))

(defun send-info (stack-list)
  (let ((info-pointer nil))
    (loop for element in stack-list do
	  (setq info-pointer (add-debug-info
                           info-pointer 
						   (first element)
  	                       (second element)
                           (third element))))
	(c-debug-info-received info-pointer)))

;;; The evaluator bundles up all of the interesting information about a system
;;; halt into this `halt-info' structure. The MESSAGE slot is the suggested
;;; message to print.
;;; Moved from RUN.LISP for Gensym-668 project
(def-structure (halt-info (:reclaimer reclaim-halt-info-1))
  halt-info-type		; halt-instruction, source-stepping, or dynamic-breakpoint
  halt-info-procedure		; Procedure and arguments as string
  halt-info-stack?		; Stack as string, one entry per line.
  halt-info-environment		; Local vars as string, one per line.
  halt-info-instruction		; Program counter as fixnum
  halt-info-line?		; Line number in unwrapped source code.
  halt-info-user-message?	; Optional user-supplied string
  halt-info-message)		; Suggested complete message as string

(defun reclaim-halt-info (hi)
  (setf-text (halt-info-procedure hi) nil)
  (setf-text (halt-info-stack? hi) nil)
  (setf-text (halt-info-environment hi) nil)
  (setf-text (halt-info-user-message? hi) nil)
  (setf-text (halt-info-message hi) nil)
  (reclaim-halt-info-1 hi))


;;; The function `fixup-debugger-environment-string' converts an environment
;;; string as sent by old G2's, of the form " var: type = parseable-value;\n ..."
;;; into a nice a double-nul-terminated sequence of var, type, value to pass to
;;; C.  Wide-string is reclaimed and a new one is returned.

(defun fixup-debugger-environment-string (wide-string)
  (macrolet ((token (string &optional parseably)
	       `(let ((end? (search-wide-string ,string wide-string i nil ,parseably)))
		  (twrite-portion-of-wide-string-unparsably wide-string i end?)
		  (twrite-char #.%Null)
		  (if end?
		      (setq i (+f end? (wide-string-length ,string)))
		      (return))))
	     (whitespace ()
	       `(loop while (and (<f i len)
				 (or (char=w (charw wide-string i) #.%space)
				     (char=w (charw wide-string i) #.%line-separator)))
		      doing (incff i))))
    (let ((i 0)
	  (len (wide-string-length wide-string)))
      (twith-output-to-wide-string
	(loop while (<f i len) doing
	  (whitespace)
	  (token #w": ")
	  (token #w" = ")
	  (token #w";" t))
	(twrite-char #.%Null)))))

(def-icp-message-type debugger-dialog
    ((gensym-window gensym-window)
     (fixnum opcode)
     (wide-string title)
     (wide-string label)
     (wide-string source-code)
     (wide-string environment)		; String of "var: type = value \u2028 ..."
     (fixnum line-number)
     (icp-tree options))
  (case opcode
    (#.debugger-dialog-create
     (let ((breakpoints (copy-list-using-gensym-conses (getf options 'breakpoints)))
	   (source-stepping-p (getf options 'source-stepping))
	   (environment (fixup-debugger-environment-string environment))
	   (tab-width (getf options 'tab-width 4)))
       (with-deferred-execution-in-tw ()
	 (create-debugger-dialog-1
	   gensym-window (gensym-window-serial-number gensym-window)
	   title label source-code
	   environment source-stepping-p line-number breakpoints tab-width))))
    (t					; Don't queue these operations!
     (c-debugger-dialog opcode title label source-code environment 0 line-number -1 #w"")))
  (reclaim-icp-tree-with-text-strings options))

(defun create-debugger-dialog-1 (gensym-window serial title label
					       source-code environment
					       source-stepping-p line-number breakpoints
					       tab-width)
  (when (gensym-window-has-not-been-reprocessed-p gensym-window serial)
    (let* ((native-label (export-text-string label 'cf-unicode-text)) ; Assume Win32
	   (bkpts (fixnum-list-to-word-vector breakpoints))
	   (source-stepping (if source-stepping-p 1 0))
	   (result (c-debugger-dialog debugger-dialog-create
				      title native-label
				      source-code environment
				      source-stepping line-number tab-width bkpts))
           (native-window (native-window? gensym-window)))
      (reclaim-byte-vector-16 bkpts)
      (reclaim-wide-string native-label)
      (multiple-value-bind (button? source-stepping-p)
	  (debugger-dialog-unpack-return-value result)
	(when button?
	  (enqueue-local-event native-window
			       (key-code-for-key-symbol 'debugger-dialog)
			       (c-x11-last-mouse-x-position native-window)
			       (c-x11-last-mouse-y-position native-window)
			       (c-x11-last-event-time native-window)
			       (gensym-list 'button button?
					    'source-stepping source-stepping-p))))))
  (reclaim-wide-string title)
  (reclaim-wide-string label)
  (reclaim-wide-string source-code)
  (reclaim-wide-string environment)
  (reclaim-gensym-list breakpoints))

(def-gensym-c-function c-debugger-dialog
    (:fixnum-int "g2ext_debugger_dialog")
  ((:fixnum-int opcode)
   (:wide-string title)
   (:wide-string label)
   (:wide-string procedure)
   (:wide-string env)
   (:fixnum-int flags)
   (:fixnum-int line)
   (:fixnum-int tab-width)
   (:wide-string bkpts)))




;;;; Custom Dialog Boxes

;;; Custom, or User-Defined, Dialog Boxes are arbitrarily complex.




(def-concept custom-dialog)



;;; `alist-of-dialog-mappings' is only used in those processes where the
;;; g2-window supports native dialogs, which for the forseeable future means
;;; TW-only.  Using an alist for this is slow.  This should be improved.  This
;;; is just a first pass.

(defvar alist-of-dialog-mappings '())








;;; `Component Types'

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar supported-dialog-component-types '())
)


;;; `def-dialog-component-type'
;; Note this macros is not hygienic, but it's intended to be used only at the
;; top-level with constant arguments, so it should not be a problem.
;; -dkuznick, 10/27/05 

(defmacro def-dialog-component-type (control-symbol corresponding-number
						    &optional ellipsis-number)
  `(let ((already-used
	   ;; Need to check for ellipsis-number also.
           (cdr (assoc ,corresponding-number supported-dialog-component-types))))
     (if already-used
         (cerror "Ignore the new component"
                 "the dialog component ~s wants to use id ~s, but ~s is already in use by ~s"
                 ',control-symbol ,corresponding-number ,corresponding-number
                 already-used)
         (push (list ,corresponding-number ',control-symbol ,ellipsis-number)
               supported-dialog-component-types))))


(def-dialog-component-type tab-frame     32)

(def-dialog-component-type progress-bar  40)
(def-dialog-component-type track-bar     50)
(def-dialog-component-type slider        51)

;; (def-dialog-component-type g2-80-combo-box  64)
(def-dialog-component-type tree-view-combo-box 65)
;; (def-dialog-component-type g2-80-list-box      66)
(def-dialog-component-type combo-box     67)
(def-dialog-component-type image         68) ;called icon in the C code
(def-dialog-component-type list-box      70)
(def-dialog-component-type checkable-list-box 71)
(def-dialog-component-type color-picker  80)
(def-dialog-component-type full-color-picker  81)

(def-dialog-component-type text-box     128 642)
(def-dialog-component-type masked-edit  129)
(def-dialog-component-type label        130)
;; (def-dialog-component-type up-down      132)
(def-dialog-component-type spinner      133)
(def-dialog-component-type duration     134)
(def-dialog-component-type short-duration     135)
(def-dialog-component-type calendar     136)
(def-dialog-component-type time-of-day  137)

(def-dialog-component-type workspace    146)

(def-dialog-component-type group        256)
(def-dialog-component-type radio-button 258)
(def-dialog-component-type check-box    260)
(def-dialog-component-type push-button  262)
(def-dialog-component-type toggle-button 263)

(def-dialog-component-type tabular-view 512)

(def-dialog-component-type grid-view 641)


;; not valid "top-level" control types; only available in the grid-view
(def-dialog-component-type integer      131)
(def-dialog-component-type quantity     132)

;; define this macro later
;; (def-dialog-component-synonym rich-grid grid-view)


;;; `map-control-type-fixnum-to-symbol'
;; Note: used only by G2, not TW.

(defun map-control-type-symbol-to-fixnum (type-symbol &optional ellipsis-button-p)
  (loop for (control-type-fixnum control-type-symbol ellipsis-fixnum?)
	    in supported-dialog-component-types
        when (eql type-symbol control-type-symbol)
          return (if ellipsis-button-p
		     ;; ellipsis-fixnum? if we get here.
		     ellipsis-fixnum?
		     control-type-fixnum)))


;;; `map-control-type-fixnum-to-symbol'
;; Note: used only by G2, not TW.
;; Note: currently, no caller supplies ellipsis-button-p.

(defun map-control-type-fixnum-to-symbol (type-fixnum &optional ellipsis-button-p)
  (loop for (control-type-fixnum control-type-symbol ellipsis-fixnum?)
	    in supported-dialog-component-types
        when (eql type-fixnum (if ellipsis-button-p
				  ellipsis-fixnum?
				  control-type-fixnum))
          return control-type-symbol))



;;; `callback (response) types' -- must be kept in synch with ext/c/dyndlgs.h




;;; `response-code-says-accept-changes-p' - uses the bitwise flags to see if the
;;; response indicates to "accept" the data (in other words, "ok" or "apply").
;;; If for some reason we had to abondon the bitwise flags in favor of arbitrary
;;; constants, this could be changed to a (member ...) check.

(defun response-code-says-accept-changes-p (respcode)
  (/=f 0 (logand respcode dialog-response-apply)))


;;; `response-code-says-dismiss-p' - uses the bitwise flags to see if the
;;; response indicates to "dismiss" the dialog (in other words, "ok" or "cancel").

(defun response-code-says-dismiss-p (respcode)
  (/=f 0 (logand respcode dialog-response-close)))


;;; The function `response-code-says-no-callback-p' returns true if a component
;;; with given respcode does not want a user-level callback. As of 8.3b0, TWNG
;;; may send updates even when not requested, in order to incrementally update
;;; grid-views.

(defun response-code-says-no-callback-p (respcode)
  (or (=f respcode dialog-response-no-action)
      ;; I think this bit is actually never used.
      (/=f 0 (logandf respcode dialog-response-dont-invoke-callback))))


;;; `response-code-indicates-client-side-problem-p' - uses the bitwise flags to
;;; see if the response indicates there was a client-side problem.  Actually, in
;;; such a case, it's very likely that that would be the only bit set in the
;;; response, and so we could just do (=f respcode), but do this in case we
;;; have more clever ideas later.  -jv, 8/21/06

(defun response-code-indicates-client-side-problem-p (respcode)
  (/=f 0 (logand respcode dialog-response-client-side-problem)))


;;; `c-start-dialog' -- calls into C, which allocates space for the structure,
;;; and returns a g2pointer to Lisp.

(def-gensym-c-function c-start-dialog
    (:fixnum-int "g2ext_start_dialog")
  ((:fixnum-int g2-id)
   (:fixnum-int guess-ncontrols)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int modal?)
   (:wide-string title)))


;;; `c-add-component-to-dialog' -- components are complicated.  This takes 13
;;; parameters now and may take more in the future.

(def-gensym-c-function c-add-component-to-dialog
    (:fixnum-int "g2ext_add_to_dialog")
  ((:fixnum-int dialog-handle)
   (:fixnum-int control-id)
   (:fixnum-int parent-control-id)
   (:wide-string parent-text)
   (:fixnum-int height)
   (:fixnum-int width)
   (:fixnum-int left)
   (:fixnum-int top)
   (:wide-string font)
   (:fixnum-int font-sizes)
   (:wide-string font-color)
   (:wide-string control-background-color)
   (:fixnum-int control-type)
   (:wide-string text)
   (:fixnum-int style-hi)
   (:fixnum-int style-lo)
   (:fixnum-int g2-style)
   (:fixnum-int response?)))


;;; `c-show-dialog' -- called after all the components are added to finally put
;;; the dialog up on the screen.  Note none of these functions takes a window
;;; argument; the window is the main window of whatever process this is
;;; executing in. Returns g2pointer to dialog's frame HWND or -1 on error.

(def-gensym-c-function c-show-dialog
    (:fixnum-int "g2ext_show_dialog")
  ((:fixnum-int dialog-handle)
   (:fixnum-int x-position)
   (:fixnum-int y-position)
   (:fixnum-int mdi-child-p)
   (:fixnum-int dock)			; Neighbor is used only if dock is nonzero
   (:fixnum-int neighbor)
   (:fixnum-int icon)
   (:fixnum-int resizable-p)
   (:fixnum-int monitor-preference)))


(def-gensym-c-function c-set-dialog-background-property
    (:fixnum-int "g2ext_set_dialog_background_property")
  ((:fixnum-int dialog-handle)
   (:wide-string background-color)))

;;; `c-lock-dialog' --

(def-gensym-c-function c-lock-dialog
    (:void "g2ext_lock_dialog")
  ((:fixnum-int dialog-handle)
   (:fixnum-int locked-p)))

;;; `c-abort-dialog' --

(def-gensym-c-function c-abort-dialog
    (:void "g2ext_abort_dialog")
  ((:fixnum-int dialog-handle)))


;;; `c-accept-dialog' --

(def-gensym-c-function c-accept-dialog
    (:void "g2ext_accept_dialog")
  ((:fixnum-int dialog-handle)))


;;; `add-dialog-id-mapping'

(defun add-dialog-id-mapping (global-dialog-id client-dialog-id)
  (gensym-push (gensym-cons global-dialog-id client-dialog-id)
               alist-of-dialog-mappings))


;;; `map-global-dialog-id-to-client-dialog-id'

(defun map-global-dialog-id-to-client-dialog-id (g2-id)
  (cdr (assoc g2-id alist-of-dialog-mappings)))


;;; `map-client-dialog-id-to-global-dialog-id'

(defun map-client-dialog-id-to-global-dialog-id (window-id)
  (loop for (global-id . client-id) in alist-of-dialog-mappings
        when (=f window-id client-id)
          return global-id))


;;; `remove-dialog-given-client-id' returns the g2-id.

(defun remove-dialog-given-client-id (window-id)
  (let* ((handle (remove-dialog-given-client-id-1 window-id))
	 (gensym-window system-window)
	 (native-window? (find-native-window-by-handle gensym-window handle)))
    (when native-window?
      (reclaim-native-window native-window?))
    ;; GENSYMCID-867: TWNG dialog callback problem
    ;; Decache g2pointer `windows-id' here. (used in `cleanup_dialog_structures' (win32_dyndlg.cpp))
    (c-decache-g2-pointer window-id)
    handle))

(defun remove-dialog-given-client-id-1 (window-id)
  (cond
    ((=f window-id (cdar alist-of-dialog-mappings))
     (let* ((old-mapping alist-of-dialog-mappings)
            (rval (caar alist-of-dialog-mappings)))
       (setq alist-of-dialog-mappings (cdr alist-of-dialog-mappings))
       (setf (cdr old-mapping) nil)
       (reclaim-gensym-cons (car old-mapping))
       (reclaim-gensym-cons old-mapping)
       rval))
    (t
     (loop for rest on alist-of-dialog-mappings
           while (cdr rest)
           when (=f window-id (cdadr rest))
             do
               (let* ((old-mapping (cdr rest))
                      (rval (caadr rest)))
                 (setf (cdr rest) (cddr rest))
                 (setf (cdr old-mapping) nil)
                 (reclaim-gensym-cons (car old-mapping))
                 (reclaim-gensym-cons old-mapping)
                 (return rval))))))






;;; `start-custom-dialog-1'

(defun start-custom-dialog-1 (g2-id guess-ncontrols
				    width height modal-p title)
  (let ((handle (c-start-dialog g2-id guess-ncontrols
                                width height
                                (if modal-p
                                    dialog-is-modal
                                    dialog-is-modeless)
                                title)))
    (add-dialog-id-mapping g2-id handle)
    handle))


;;; `add-dialog-component-1'
(defun add-dialog-component-1 (g2-id
                                control-id
                                parent-control-id
                                parent-text
                                height width
                                left top font 
                                font-size font-color
                                control-background-color 
                                control-type
                                text
                                style-hi style-lo
                                g2-style
                                response-code)
  (let ((handle (map-global-dialog-id-to-client-dialog-id g2-id)))
    (cond
      (handle
       (c-add-component-to-dialog handle control-id parent-control-id parent-text
                                  height width left top font font-size font-color
                                  control-background-color control-type
                                  text style-hi style-lo
                                  g2-style
                                  response-code)))))


;;; `note-dialog-launch-failure' -- this occurs in Telewindows.  What we really
;;; want to do here is send a message to G2 that the dialog has failed.
;;; Additionally, maybe we should print something to the TW console/logfile.  At
;;; this point, however, it is just a stub which prints a message in Lisp, and
;;; does absolutely nothing otherwise.  -jv, 5/28/04

(defun note-dialog-launch-failure (g2-side-handle)
  #-development
  (declare (ignore g2-side-handle))
  #+development
  (format t "Failed to launch dialog ~d!!!~%" g2-side-handle)
  )




;;; The function `get-dock-code' translates a docking position symbol into a
;;; fixnum used by the C code. Runs only on TW.

(defun get-dock-code (dock-name)
  (case dock-name
    (top dock-code-top)
    (bottom dock-code-bottom)
    (left dock-code-left)
    (right dock-code-right)
    (float dock-code-float)
    (within dock-code-within)
    (t 0)))

;;; `show-custom-dialog-1' returns a native-window object or NIL on
;;; failure. Runs only on the TW side.

(defun show-custom-dialog-1 (gensym-window g2-id x-pos y-pos container dock? neighbor? icon?
                                           resizable-p monitor-preference)
  (let ((client-id? (map-global-dialog-id-to-client-dialog-id g2-id)))
    (when client-id?
      (multiple-value-bind (dock neighbor)
	  (encode-dock-and-neighbor container dock? neighbor?)
	(let ((window-index
		(c-show-dialog client-id? x-pos y-pos
			       (if (eq container 'mdi-child) 1 0)
			       (if (or (=f dock dock-code-mdi-child)
				       (=f dock dock-code-top-level))
				   0 dock) ; c-show-dialog expects 0 unless really docking or embedding.
			       neighbor
			       (or icon? -2) ; -2 means use default
			       (if resizable-p 1 0)
			       monitor-preference)))
	  
	 (cond ((<f window-index 0)
		 (note-dialog-launch-failure g2-id)
		 nil)
		(t
		 ;; Keep track of the dialog HWND. -fmw, 8/25/05
		 (make-basic-native-window
		   gensym-window g2-id window-index 'g2-dialog-view container))))))))


;;; `set-custom-dialog-background-1' 
;;; Runs only on the TW side.

(defun set-custom-dialog-background-1 (gensym-window g2-id background-color)
  (let ((client-id? (map-global-dialog-id-to-client-dialog-id g2-id)))
    (when client-id?
      (multiple-value-bind (dock neighbor)
	  (encode-dock-and-neighbor container dock? neighbor?)
	(let ((window-index
	       (c-set-dialog-background-property client-id? background-color))))))))


;;; `abort-custom-dialog-1'

(defun abort-custom-dialog-1 (g2-id)
  (let ((handle (map-global-dialog-id-to-client-dialog-id g2-id)))
    (cond
      (handle
       (c-abort-dialog handle)
       t))))


;;; `accept-custom-dialog-1'

(defun accept-custom-dialog-1 (g2-id)
  (let ((handle (map-global-dialog-id-to-client-dialog-id g2-id)))
    (cond
      (handle
       (c-accept-dialog handle)
       t))))


;;; `start-custom-dialog' ICP message type.  Defines, among other things,
;;; function `send-icp-start-custom-dialog'

(def-icp-message-type start-custom-dialog
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id)
     (unsigned-integer guess-ncontrols)
     (unsigned-integer width)
     (unsigned-integer height)
     (boolean modal-p)
     (text-string title))
  (declare (ignore gensym-window))
  (start-custom-dialog-1
    g2-dialog-id
    guess-ncontrols width height modal-p
    title))

;;; `set-dialog-locked' ICP message type.
(def-icp-message-type set-dialog-locked
    ((gensym-window gensym-window)
     (unsigned-integer dialog-id)
     (boolean locked-p))
  (declare (ignore gensym-window))
  (set-dialog-locked-1 dialog-id locked-p))

(defun set-dialog-locked-1 (dialog-id locked-p)
  (c-lock-dialog dialog-id locked-p)
  t)

;;; `add-dialog-component' ICP message type.  Defines, among other things,
;;; function `send-icp-add-dialog-component'

(def-icp-message-type add-dialog-component
    ((gensym-window gensym-window)
     (integer g2-dialog-id)
     (integer control-id)
     (integer parent-control-id)
     (text-string parent-text)
     (integer height)
     (integer width)
     (integer left)
     (integer top)
     (integer control-type)
     (text-string text)
     (integer style-hi)
     (integer style-lo)
     (integer g2-style)
     (integer response-code))
  (declare (ignore gensym-window))
  (add-dialog-component-1
    g2-dialog-id
    control-id
    parent-control-id
    parent-text
    height width
    left top "" 
    0 "" ""
    control-type
    text
    style-hi style-lo
    g2-style
    response-code))

(defvar supports-dialog-component-with-font 1) ; see icp-version-info-alist

(defun remote-side-supports-dialog-component-with-font-p (icp-socket)
  (=f 1 (get-remote-icp-version-info-value
          icp-socket 'supports-dialog-component-with-font 0)))

;;; GENSYMCID-1525: new g2 release font color/size/type is not working for grid-view control

(defvar supports-font-in-grid-view 1)
(defun remote-side-supports-font-in-grid-view-p (icp-socket)
  (=f 1 (get-remote-icp-version-info-value
          icp-socket 'supports-font-in-grid-view 0)))

(defvar supports-update-color-in-push-button 1)
(defun remote-side-supports-update-color-in-push-button-p (icp-socket)
  (=f 1 (get-remote-icp-version-info-value
          icp-socket 'supports-update-color-in-push-button 0)))

(defvar supports-background-color-in-custom-dialogs 1)
(defun remote-side-supports-background-color-in-custom-dialogs-p (icp-socket)
  (=f 1 (get-remote-icp-version-info-value
          icp-socket 'supports-background-color-in-custom-dialogs 0)))

(defvar supports-border-settings-in-label 1)
(defun remote-side-supports-border-settings-in-label-p (icp-socket)
  (=f 1 (get-remote-icp-version-info-value
          icp-socket 'supports-border-settings-in-label 0)))

(defvar supports-color-settings-in-toggle-button 1)
(defun remote-side-supports-color-settings-in-toggle-button-p (icp-socket)
  (=f 1 (get-remote-icp-version-info-value
          icp-socket 'supports-color-settings-in-toggle-button 0)))

(defvar supports-update-color-in-list-box 1)
(defun remote-side-supports-update-color-in-list-box-p (icp-socket)
  (=f 1 (get-remote-icp-version-info-value
          icp-socket 'supports-update-color-in-list-box 0)))

(defvar supports-update-color-in-label 1)
(defun remote-side-supports-update-color-in-label-p (icp-socket)
  (=f 1 (get-remote-icp-version-info-value
         icp-socket 'supports-update-color-in-label 0)))

(defvar supoorts-get-and-set-scroll-position-in-grid-view 1)
(defun remote-side-supoorts-get-and-set-scroll-position-in-grid-view-p (icp-socket)
  (=f 1 (get-remote-icp-version-info-value
         icp-socket 'supoorts-get-and-set-scroll-position-in-grid-view 0)))

(def-icp-message-type add-dialog-component-with-font
    ((gensym-window gensym-window)
     (integer g2-dialog-id)
     (integer control-id)
     (integer parent-control-id)
     (text-string parent-text)
     (integer height)
     (integer width)
     (integer left)
     (integer top)
     (text-string font)
     (integer font-size)
     (text-string font-color)
     (text-string control-background-color)
     (integer control-type)
     (text-string text)
     (integer style-hi)
     (integer style-lo)
     (integer g2-style)
     (integer response-code))
  (declare (ignore gensym-window))
  (add-dialog-component-1
    g2-dialog-id
    control-id
    parent-control-id
    parent-text
    height width
    left top font 
    font-size font-color
    control-background-color 
    control-type
    text
    style-hi style-lo
    g2-style
    response-code))

;;; `show-custom-dialog' ICP message type.  Defines, among other things,
;;; function `send-icp-show-custom-dialog'

(def-icp-message-type show-custom-dialog
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id)
     (integer x-position)
     (integer y-position)
     (unsigned-integer options))
  (show-custom-dialog-1
    gensym-window g2-dialog-id x-position y-position
    (if (logbitpf 0 options) 'mdi-child 'top-level)
    nil nil nil nil (default-monitor-preference-code)))

;;; The icp-message `show-custom-dialog-ex' adds support for dialog panes, via
;;; an options plist.  Defines, among other things,
;;; function `send-icp-show-custom-dialog-ex'

(defconstant default-monitor-preference-for-dialog 'nearest-monitor)
(defconstant monitor-preference-settings '(primary-monitor 0 nearest-monitor 1))
(defconstant valid-monitor-preference-symbols
            (loop for symbol in monitor-preference-settings by 'cddr
                  collect symbol))

(defun map-monitor-preference-symbol-to-code (monitor-preference)
  (or (getf monitor-preference-settings monitor-preference nil)
      (getf monitor-preference-settings default-monitor-preference-for-dialog)))

(defun default-monitor-preference-code ()
  (map-monitor-preference-symbol-to-code default-monitor-preference-for-dialog))

(def-icp-message-type show-custom-dialog-ex
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id)
     (integer x-position)
     (integer y-position)
     (icp-tree plist))
  (let* ((mdi-child-p (getf plist 'mdi-child))
         (dock? (getf plist 'dock))
         (neighbor? (getf plist 'neighbor))
         (container (getf plist 'container
                      (cond (mdi-child-p 'mdi-child)
                            (dock? 'pane)
                            (t 'top-level))))
         (icon? (getf plist 'icon))
         (resizable-p (getf plist 'resizable))
         (monitor-preference (map-monitor-preference-symbol-to-code
                               (getf plist 'monitor-preference)))
         (native-window?
           (show-custom-dialog-1
             gensym-window g2-dialog-id x-position y-position container dock?
             neighbor? icon? resizable-p monitor-preference)))

    (when native-window?
      (process-view-init-plist native-window? plist '(title icon))) ; Already handled title and icon.
    (reclaim-icp-tree-with-text-strings plist)))


(def-icp-message-type set-custom-dialog-background
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id)
     (text-string background-color))
  (set-custom-dialog-background-1
    gensym-window g2-dialog-id background-color))


;;; `abort-custom-dialog' ICP message type.  Defines, among other things,
;;; function `send-icp-abort-custom-dialog'

(def-icp-message-type abort-custom-dialog
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id))
  (declare (ignore gensym-window))
  (abort-custom-dialog-1
    g2-dialog-id))


;;; `accept-custom-dialog' ICP message type.  Defines, among other things,
;;; function `send-icp-accept-custom-dialog'

(def-icp-message-type accept-custom-dialog
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id))
  (declare (ignore gensym-window))
  (accept-custom-dialog-1
    g2-dialog-id))


;;; `c-send-dialog-control-update' --

(def-gensym-c-function c-send-dialog-control-update
    (:fixnum-int "g2ext_send_dialog_control_update")
  ((:fixnum-int dialog-handle)
   (:fixnum-int control-id)))





;;; `c-start-dialog-query'

(def-gensym-c-function c-start-dialog-query
    (:fixnum-int "g2ext_start_dialog_query")
  ((:fixnum-int dialog-handle)
   (:fixnum-int query-handle)
   (:fixnum-int options)))


;;; `c-add-to-dialog-query'

(def-gensym-c-function c-add-to-dialog-query
    (:fixnum-int "g2ext_add_to_dialog_query")
  ((:fixnum-int dialog-handle)
   (:fixnum-int query-handle)
   (:fixnum-int control-id)))


;;; `c-finish-dialog-query'

(def-gensym-c-function c-finish-dialog-query
    (:fixnum-int "g2ext_finish_dialog_query")
  ((:fixnum-int dialog-handle)
   (:fixnum-int query-handle)))


;;; `c-abort-dialog-query'

(def-gensym-c-function c-abort-dialog-query
    (:void "g2ext_abort_dialog_query")
  ((:fixnum-int dialog-handle)
   (:fixnum-int query-handle)))


;;; `start-dialog-query-1'

(defun start-dialog-query-1 (g2-dialog-id
                              g2-dialog-query-id
                              options-fixnum)
  (let ((handle (map-global-dialog-id-to-client-dialog-id g2-dialog-id)))
    (cond
      (handle
       (c-start-dialog-query handle g2-dialog-query-id options-fixnum)))))


;;; `add-to-dialog-query-1'

(defun add-to-dialog-query-1 (g2-dialog-id
                               g2-dialog-query-id
                               internal-control-id)
  (let ((handle (map-global-dialog-id-to-client-dialog-id g2-dialog-id)))
    (cond
      (handle
       (c-add-to-dialog-query handle g2-dialog-query-id
                              internal-control-id)))))


;;; `finish-dialog-query-1'

(defun finish-dialog-query-1 (g2-dialog-id query-id)
  (let ((handle (map-global-dialog-id-to-client-dialog-id g2-dialog-id)))
    (cond
      (handle
       (c-finish-dialog-query handle query-id)))))


;;; `abort-dialog-query-1'

(defun abort-dialog-query-1 (g2-dialog-id query-id)
  (let ((handle (map-global-dialog-id-to-client-dialog-id g2-dialog-id)))
    (cond
      (handle
       (c-abort-dialog-query handle query-id)
       t))))


;;; `start-dialog-query' ICP message type.  Defines, among other things,
;;; function `send-icp-start-dialog-query'

(def-icp-message-type start-dialog-query
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id)
     (unsigned-integer g2-query-id)
     (unsigned-integer query-options))
  (declare (ignore gensym-window))
  (start-dialog-query-1
    g2-dialog-id g2-query-id query-options))


;;; `add-to-dialog-query' ICP message type.  Defines, among other things,
;;; function `send-icp-add-to-dialog-query'

(def-icp-message-type add-to-dialog-query
    ((gensym-window gensym-window)
     (integer g2-dialog-id)
     (integer query-id)
     (integer control-id))
  (declare (ignore gensym-window))
  (add-to-dialog-query-1
    g2-dialog-id
    query-id
    control-id))


;;; `finish-dialog-query' ICP message type.  Defines, among other things,
;;; function `send-icp-finish-dialog-query'

(def-icp-message-type finish-dialog-query
    ((gensym-window gensym-window)
     (integer g2-dialog-id)
     (integer query-id))
  (declare (ignore gensym-window))
  (finish-dialog-query-1
    g2-dialog-id query-id))


;;; `abort-dialog-query' ICP message type.  Defines, among other things,
;;; function `send-icp-abort-dialog-query'

(def-icp-message-type abort-dialog-query
    ((gensym-window gensym-window)
     (integer g2-dialog-id)
     (integer query-id))
  (declare (ignore gensym-window))
  (abort-dialog-query-1
    g2-dialog-id query-id))



;;; Dialog Updates

;;; `c-start-dialog-update'

(def-gensym-c-function c-start-dialog-update
    (:fixnum-int "g2ext_start_dialog_update")
  ((:fixnum-int dialog-handle)))

;;; `c-dialog-component-update'

(def-gensym-c-function c-dialog-component-update
    (:fixnum-int "g2ext_dialog_component_update")
  ((:fixnum-int dialog-handle)
   (:fixnum-int control-id)
   (:wide-string control-value)
   (:fixnum-int update-type)))


;;; `c-abort-dialog-update'

(def-gensym-c-function c-abort-dialog-update
    (:fixnum-int "g2ext_abort_dialog_update")
  ((:fixnum-int dialog-handle)))

;;; `c-end-dialog-update'

(def-gensym-c-function c-end-dialog-update
    (:fixnum-int "g2ext_end_dialog_update")
  ((:fixnum-int dialog-handle)))


;;; `start-dialog-update-1'

(defun start-dialog-update-1 (g2-id)
  (let ((handle (map-global-dialog-id-to-client-dialog-id g2-id)))
    (cond
      (handle
       (c-start-dialog-update handle)
       t))))


;;; `dialog-component-update-1'

(defun dialog-component-update-1 (g2-id
                                   control-id
                                   control-value
                                   update-type)
  (let ((handle (map-global-dialog-id-to-client-dialog-id g2-id)))
    (cond
      (handle
       (c-dialog-component-update
         handle
         control-id
         control-value
         update-type))
      (t t))))

;;; `end-dialog-update-1'

(defun end-dialog-update-1 (g2-id)
  (let ((handle (map-global-dialog-id-to-client-dialog-id g2-id)))
    (cond
      (handle
       (c-end-dialog-update handle)
       t))))

;;; `abort-dialog-update-1'

(defun abort-dialog-update-1 (g2-id)
  (let ((handle (map-global-dialog-id-to-client-dialog-id g2-id)))
    (cond
      (handle
       (c-abort-dialog-update handle)
       t))))


;;; `start-dialog-update' ICP message type.  Defines, among other things,
;;; function `send-icp-abort-dialog-update'

(def-icp-message-type start-dialog-update
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id))
  (declare (ignore gensym-window))
  (start-dialog-update-1
    g2-dialog-id))

;;; `dialog-component-update' ICP message type.  Defines, among other things,
;;; function `send-icp-dialog-component-update'

(def-icp-message-type dialog-component-update
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id)
     (unsigned-integer control-id)
     (text-string control-value)
     (unsigned-integer update-type))
  (declare (ignore gensym-window))
  (dialog-component-update-1
    g2-dialog-id
    control-id
    control-value
    update-type))


;;; `end-dialog-update' ICP message type.  Defines, among other things,
;;; function `send-icp-end-dialog-update'

(def-icp-message-type end-dialog-update
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id))
  (declare (ignore gensym-window))
  (end-dialog-update-1
    g2-dialog-id))


;;; `abort-dialog-update' ICP message type.  Defines, among other things,
;;; function `send-icp-abort-dialog-update'

(def-icp-message-type abort-dialog-update
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id))
  (declare (ignore gensym-window))
  (abort-dialog-update-1
    g2-dialog-id))


;;;; Tabular Views (Obsolete API)

(defmacro def-obsolete-tabular-view-message (name args)
  `(def-icp-message-type ,name ,args
     ,@(mapcar 'cadr args)
     (notify-user-at-console "Tabular views are not supported by this Telewindows version.")))

(def-obsolete-tabular-view-message start-add-tabular-view
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id)
     (unsigned-integer control-id)
     (fixnum row-height)
     (fixnum text-color)
     (fixnum background-color)))

(def-obsolete-tabular-view-message add-tabular-view-column
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id)
     (unsigned-integer control-id)
     (unsigned-integer index)
     (fixnum width)
     (text-string column-title)))

(def-obsolete-tabular-view-message start-add-tabular-view-row
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id)
     (unsigned-integer control-id)
     (unsigned-integer logical-id)
     (fixnum fg-color)
     (fixnum bg-color)))

(def-obsolete-tabular-view-message add-tabular-view-cell
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id)
     (unsigned-integer control-id)
     (unsigned-integer logical-id)
     (unsigned-integer index)
     (fixnum fg-color)
     (fixnum bg-color)
     (text-string value)))

(def-obsolete-tabular-view-message end-add-tabular-view-row
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id)
     (unsigned-integer control-id)
     (unsigned-integer logical-id)))

(def-obsolete-tabular-view-message start-replace-tabular-view-row
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id)
     (unsigned-integer control-id)
     (unsigned-integer logical-id)
     (fixnum fg-color)
     (fixnum bg-color)))

(def-obsolete-tabular-view-message replace-tabular-view-cell
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id)
     (unsigned-integer control-id)
     (unsigned-integer logical-id)
     (unsigned-integer index)
     (fixnum fg-color)
     (fixnum bg-color)
     (text-string value)))

(def-obsolete-tabular-view-message end-replace-tabular-view-row
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id)
     (unsigned-integer control-id)
     (unsigned-integer logical-id)))

(def-obsolete-tabular-view-message delete-tabular-view-row
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id)
     (unsigned-integer control-id)
     (unsigned-integer logical-id)))

(def-obsolete-tabular-view-message select-tabular-view-rows
    ((gensym-window gensym-window)
     (unsigned-integer g2-dialog-id)
     (unsigned-integer control-id)
     (text-string logical-ids)))


;;;; Grid Views


(def-tree-reclaimer reclaim-icp-tree-of-values (list) :cons-pool icp)

;; Keep in sync with widgets/richeditgrid/GridExtras.cpp, beginning of
;; section FUNCTION GROUP - Modifying Existing Grid-Views.
(defconstant grid-view-refresh 0)
(defconstant grid-view-delete-row 1)
(defconstant grid-view-insert-row 2)
(defconstant grid-view-background-color 3)
(defconstant grid-view-text-color 4)
(defconstant grid-view-cell-value 5)
(defconstant grid-view-cell-type 6)
(defconstant grid-view-read-only 7)
(defconstant grid-view-row-height 8)
(defconstant grid-view-column-width 9)
(defconstant grid-view-count-rows 10)
(defconstant grid-view-count-columns 11)
(defconstant grid-view-cell-alignment 12)
(defconstant grid-view-cell-selected 13)
(defconstant grid-view-delete-column 14)
(defconstant grid-view-insert-column 15)
(defconstant grid-view-cell-bold 16)
(defconstant grid-view-cell-is-multiline 17)
(defconstant grid-view-insert-row-with-integer-label 18)
(defconstant grid-view-get-hscroll-position 19)
(defconstant grid-view-set-hscroll-position 20)
(defconstant grid-view-get-vscroll-position 21)
(defconstant grid-view-set-vscroll-position 22)

(def-icp-message-type manage-grid-view
    ((fixnum dialog-id)
     (fixnum control-id)
     (icp-tree actions))
  (manage-grid-view-1 dialog-id control-id actions)
  (reclaim-icp-tree-of-values actions))

(def-icp-message-type manage-grid-view-get-value
    ((fixnum dialog-id)
     (fixnum control-id)
     (icp-tree actions)
     (symbol var-name))
  (writing-icp-message-group ((icp-output-port current-icp-socket))
    (send-icp-manage-grid-view-get-value-reply
     var-name (manage-grid-view-1 dialog-id control-id actions)))
  (reclaim-icp-tree-of-values actions))

(def-icp-message-type manage-grid-view-get-value-reply
    ((symbol var-name)
     (fixnum value))
  (let* ((var (get-instance-with-name-if-any 'variable-or-parameter var-name))
         (*current-computation-frame* var))
    (put-current-evaluation-value var value 'never nil nil)))

(defun to-fixnum (thing)
  (if (fixnump thing) thing -1))

(defun to-string (thing)
  (cond ((null thing)
	 #w"")
	((symbolp thing)
	 (stringw thing))
	((stringpw thing)
	 thing)
	(t
	 #w"")))

(defmacro grid-view-op (opname &optional arg)
  (avoiding-variable-capture (arg)
    (let ((opcode (build-ab-symbol "GRID-VIEW" opname)))
      `(c-manage-grid-view ,opcode g2pointer control-id row col
			   (to-fixnum ,arg) (to-string ,arg)))))

(defun grid-view-insert-row (g2pointer control-id row data)
  (when (plistp data)
    (let ((height? (getf data 'height))
	  (label (getf data 'text-value #w""))
	  (cells (getf data 'cell-settings))
	  (integer-label (getf data 'integer-label))
	  (col -1))
	  (if (null integer-label)
      (grid-view-op insert-row label)
		(grid-view-op insert-row-with-integer-label integer-label))
      (when height?
	(grid-view-op row-height height?))
      (when (listp cells)
	(loop for cell in cells
	      as col from 0
	      doing
	  (when (plistp cell)
	    (grid-view-modify-cell-1 g2pointer control-id row col cell)))))))

(defun grid-view-insert-column (g2pointer control-id col data)
  (when (plistp data)
    (let ((width? (getf data 'width))
	  (label (getf data 'text-value #w""))
	  (cells (getf data 'cell-settings))
	  (row -1))
      (grid-view-op insert-column label)
      (when width?
	(grid-view-op column-width width?))
      (when (listp cells)
	(loop for cell in cells
	      as row from 0
	      doing
	  (when (plistp cell)
	    (grid-view-modify-cell-1 g2pointer control-id row col cell)))))))

(defun grid-view-modify-cell-1 (g2pointer control-id row col plist)
  (loop for (p v) on plist by #'cddr doing
    (case p
      (cell-type
       (grid-view-op cell-type v))
      (cell-value
       (grid-view-op cell-value v))
      (background-color
       (grid-view-op background-color v))
      (text-color
       (grid-view-op text-color v))
      (read-only
       (grid-view-op read-only v))
      (is-multiline
       (grid-view-op cell-is-multiline v))
      (alignment
       (grid-view-op cell-alignment v))
      (bold
       (grid-view-op cell-bold v))
      (selected
       (grid-view-op cell-selected v)))))

(defun manage-grid-view-1 (dialog-id control-id actions)
  (let ((g2pointer (map-global-dialog-id-to-client-dialog-id dialog-id))
        ret-val)
    (when (and g2pointer (listp actions))
      (loop with row = -1
	    with col = -1
	    for element in actions
	    as action = (car-or-atom element)
	    as arg = (cdr-or-atom element)
	    doing
	(when (plistp arg)
	  (let ((row (getf arg 'row -1))
		(col (getf arg 'col -1))
		(string (getf arg 'string)) ; These may not be needed.
		(param (getf arg 'param))
		(color (getf arg 'color))) ; A color-value.
	    (case action
	      (refresh
	       (grid-view-op refresh))

	      (insert-row
	       (grid-view-insert-row g2pointer control-id row arg))

	      (delete-row
	       (grid-view-op delete-row))

	      (insert-column
	       (grid-view-insert-column g2pointer control-id col arg))

	      (delete-column
	       (grid-view-op delete-column))

	      (modify-cell
	       (grid-view-modify-cell-1 g2pointer control-id row col arg))
	       
	      (row-height
	       (grid-view-op row-height param))

	      (column-width
	       (grid-view-op column-width param))

	      ;; Are these variations used?
	      (background-color
	       (grid-view-op background-color color))

	      (text-color
	       (grid-view-op text-color color))

	      (cell-value
	       (grid-view-op cell-value string))

	      (cell-type
	       (grid-view-op cell-type string))

	      (read-only
	       (grid-view-op read-only param))

	      (is-multiline
	       (grid-view-op cell-is-multiline param))

	      (alignment
	       (grid-view-op cell-alignment param))

	      (bold
	       (grid-view-op cell-bold param))

	      (selected
	       (grid-view-op cell-selected param))

              (get-hscroll-position
               (setf ret-val (grid-view-op get-hscroll-position)))

              (set-hscroll-position
               (grid-view-op set-hscroll-position param))

              (get-vscroll-position
               (setf ret-val (grid-view-op get-vscroll-position)))

              (set-vscroll-position
               (grid-view-op set-vscroll-position param)))))

	    finally
	      (grid-view-op refresh)))
    ret-val))

(def-gensym-c-function c-manage-grid-view
    (:fixnum-int "g2ext_manage_grid_view")
  ((:fixnum-int opcode)
   (:fixnum-int dialog-id)
   (:fixnum-int control-id)
   (:fixnum-int row)
   (:fixnum-int col)
   (:fixnum-int int-param)
   (:wide-string string-param)))


;;; `c-specify-grid-view-cells'

(def-gensym-c-function c-specify-grid-view-cells
    (:fixnum-int "g2ext_specify_grid_view_cells")
  ((:fixnum-int dialog-id)
   (:fixnum-int control-id)
   (:wide-string cell-spec)))


;;; `specify-grid-view-cells-1'

(defun specify-grid-view-cells-1 (dialog-id control-id cell-spec)
  (let ((dialog-handle (map-global-dialog-id-to-client-dialog-id dialog-id)))
    (cond
      (dialog-handle
       (c-specify-grid-view-cells dialog-handle control-id cell-spec))
      (t
       nil))))


;;; `specify-grid-view-cells' ICP message type.  Defines, among other things,
;;; function `send-icp-specify-grid-view-cells'

(def-icp-message-type specify-grid-view-cells
    ((fixnum dialog-id)
     (fixnum control-id)
     (text-string cell-spec))
  (specify-grid-view-cells-1 dialog-id control-id cell-spec))


;;; `c-specify-text-box-extensions'

(def-gensym-c-function c-specify-text-box-extensions
    (:void "g2ext_specify_text_box_extensions")
  ((:fixnum-int dialog-id)))


;;; `specify-text-box-extensions-1'

(defun specify-text-box-extensions-1 (dialog-id)
  (let ((dialog-handle (map-global-dialog-id-to-client-dialog-id dialog-id)))
    (cond
      (dialog-handle
       (c-specify-text-box-extensions dialog-handle)
       t)
      (t
       nil))))


;;; `specify-text-box-extensions' ICP message type.  Defines, among other things,
;;; function `send-icp-specify-text-box-extensions'

(def-icp-message-type specify-text-box-extensions
    ((fixnum dialog-id))
  (specify-text-box-extensions-1 dialog-id))
