;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module NATIVE-TW

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Fred White






;;;; Forward References


(declare-forward-references
  (partial-command-p-function function) ; NEW-MENUS
  (reclaim-partial-command function))   ; NEW-MENUS

(declare-forward-reference ui-stack-error-1 function VIEWS)

;;;; Native Menu Protocol


;; These keep track of all the native menus we've created, so that we can
;; reclaim and destroy them.  native-menu-table is just an array of all the
;; c-pointers we've allocated for the current post-native-menu invocation.

(defvar native-menu-counter)
(defvar native-menu-table)

;; These take care of mapping a Win32 menu item ID, as returned from a
;; choose-from-item-menu, back to a G2 menu handle and item number.

(defvar native-menu-unique-id-counter)
(defvar native-menu-id-to-handle-and-item-number-table)


;;; The ICP message type `post-native-menu' is sent by G2 to TW to post a native
;;; (win32) menu at x,y with the given items.

(def-icp-message-type post-native-menu
    ((gensym-window gensym-window)
      (fixnum menu-handle)                ; G2 handle on menu object.  TW sends this back to G2.
      (coordinate x)                      ; x,y in G2 window coordinates.
      (coordinate y)
      (icp-tree menu-items))              ; ICP-CONS tree of string, (submenu string ...), etc.
  (with-deferred-execution-in-tw ()
    (post-native-menu gensym-window (gensym-window-serial-number gensym-window)
                      menu-handle x y menu-items)))

(defun post-native-menu (gensym-window serial menu-handle x y menu-items)
  (when (gensym-window-has-not-been-reprocessed-p gensym-window serial)
    (let ((native-menu-counter 0)
          (native-menu-table (allocate-managed-array 1024))
          (native-menu-unique-id-counter 1)
          (native-menu-id-to-handle-and-item-number-table (allocate-managed-array 1024)))
      (on-window-without-drawing (gensym-window) ; Just for map-to-color-value
        (let* ((native-window (native-window? gensym-window))
               (native-menu? (create-native-menu menu-handle menu-items (twng-p gensym-window)))
               (choice (if native-menu?
                           (choose-from-item-menu native-window native-menu? x y)
                           0)))

          (enqueue-native-menu-choice gensym-window menu-handle choice)
          (when native-menu?
            (reclaim-native-menus native-menu? native-menu-table native-menu-counter))
          (reclaim-managed-array native-menu-table)
          (reclaim-managed-array native-menu-id-to-handle-and-item-number-table)))))
  (reclaim-icp-tree-with-text-strings menu-items))

;; Those 1024's have to go, of course.

(defun reclaim-native-menus (top-level-native-menu array count)
  (loop for i below count
        as native-menu = (managed-svref array i)
        unless (eql native-menu top-level-native-menu)
          do (reclaim-item-menu native-menu 0))
  (reclaim-item-menu top-level-native-menu 1))

;; Records this native-menu (a C-pointer) so that we can reclaim it later.
(defun record-native-menu-c-pointer (native-menu)
  (when (>=f native-menu-counter (managed-array-length native-menu-table))
    (setq native-menu-table (adjust-managed-array native-menu-table (*f native-menu-counter 2))))
  (setf (managed-svref native-menu-table native-menu-counter) native-menu)
  (incff native-menu-counter))

;;; The defconstant `menu-break-marker' marks the beginning of a new column in a
;;; native menu.

(defconstant menu-break-marker '|mEnUbReAk|)

;;; The recursive function `create-native-menu' creates a tree of native menus
;;; containing the given items and a unique Windows menu item ID for each item
;;; in the tree.  Returns a C pointer to the top-level menu, or NIL on failure.
;;; Requires current-color-map to be bound.

(defun create-native-menu (menu-handle items twng?)
  (let ((menu-c-pointer (begin-item-menu)))
    (when (>=f menu-c-pointer 0)
      (record-native-menu-c-pointer menu-c-pointer)
      (loop with flags = 0
            with item-number = 1
            for item in items
            doing
        (cond ((eq item menu-break-marker) ; flags influence the next real menu item.
               (setq flags 1))
              (t
               (let ((string (if (atom item) item (second item)))
                     (id? (create-unique-native-menu-item-id menu-handle item-number)))

                 (cond ((null id?))                ; Out of menu item IDs.
                       ((and (consp item)        ; (SUBMENU string [handle . items])
                             (eq (first item) 'submenu)
                             (third item))
                        (let* ((submenu-handle (third item))
                               (submenu-items (cdddr item))
                               (submenu-c-pointer? (create-native-menu submenu-handle submenu-items twng?)))
                          (when submenu-c-pointer?
                            (if twng?
                              (add-submenu-to-menu menu-c-pointer string submenu-c-pointer? flags)
                              (nms-c-append-menu menu-c-pointer 16 0 submenu-c-pointer? 0 string -1 -1)))))

                       ((and (consp item)                ; (COLOR string fg bg)
                             (eq (first item) 'color))
                        (let ((fg (map-to-color-value (third item)))
                              (bg (map-to-color-value (fourth item))))
                          (add-color-string-to-menu menu-c-pointer string id? flags fg bg)))

                       (t                                ; string
                        (if twng?
                          (add-string-to-menu menu-c-pointer string id? flags)
                          (add-string-to-menu menu-c-pointer string id? (+f flags 2)))))
                 (setq flags 0)
                 (incff item-number)))))
      menu-c-pointer)))



;;; The function `create-unique-native-menu-item-id' returns a windows menu item
;;; ID, if possible, which encodes the given G2 menu-handle and the item-number,
;;; each 10-bit fixnums, or NIL on failure. Windows menu item IDs are limited to
;;; 16 bits, and further limited to a maximum of 0xE000 to ensure that we do not
;;; collide with random built-in Win32 IDs (this is not strictly necessary since
;;; we use these menus only as modal popups -- a WM_COMMAND message is never
;;; sent with the item ID.)

(defun create-unique-native-menu-item-id (menu-handle item-number)
  ;; Maybe this should print warnings to the console on failure.
  (cond ((>=f menu-handle 1024)
         nil)
        ((>=f item-number 1024)
         nil)
        ((>=f native-menu-unique-id-counter #xE000) ; Could permit 0xFFFF, I think.
         nil)
        (t
         (let ((i native-menu-unique-id-counter))
           (incff native-menu-unique-id-counter)
           (when (>=f i (managed-array-length native-menu-id-to-handle-and-item-number-table))
             (setq native-menu-id-to-handle-and-item-number-table
                   (adjust-managed-array native-menu-id-to-handle-and-item-number-table
                                         (*f i 2))))
           (setf (managed-svref native-menu-id-to-handle-and-item-number-table i)
                 (logiorf (ashf menu-handle 10) item-number))
           i))))


(defun menu-handle-given-item-id (id)
  (let ((bits (managed-svref native-menu-id-to-handle-and-item-number-table id)))
    (logandf 1023 (ashf bits -10))))

(defun item-number-given-item-id (id)
  (let ((bits (managed-svref native-menu-id-to-handle-and-item-number-table id)))
    (logandf 1023 bits)))


;; To execute a menu choice, TW enqueues a key event with the keycode in a special
;; range, encoding the handle to the menu and the number of item chosen.
(defun enqueue-native-menu-choice (gensym-window top-level-menu-handle id)
  (let* ((native-window (native-window? gensym-window))
         (menu-handle (if (=f id 0)        ; For a cancelled menu.
                          top-level-menu-handle
                          (menu-handle-given-item-id id)))
         (item-number (if (=f id 0)
                          0
                          (item-number-given-item-id id)))
         (plist (gensym-list 'menu-handle menu-handle 'item-number item-number)))

    (gensym-assert (<= 0 menu-handle 1023)) ; 1023 menus (0 is invalid)
    (gensym-assert (<= 0 item-number 1023)) ; 1023 items (0 mean no choice made)

    (enqueue-local-event
      native-window
      (key-code-for-key-symbol 'pre-nms-menu-choice)
;      (logiorf menu-bit (ashf menu-handle 10) item-number)
      (c-x11-last-mouse-x-position native-window)
      (c-x11-last-mouse-y-position native-window)
      (c-x11-last-event-time native-window)
      plist)))


;; Returns a fixnum handle to a Windows popup menu.
(def-gensym-c-function begin-item-menu
    (:fixnum-int "g2ext_begin_item_menu")
  ())

(def-gensym-c-function add-string-to-menu
    (:fixnum-int "g2ext_add_string_to_item_menu")
  ((:pointer menu)
   (:wide-string string)
   (:fixnum-int id)
   (:fixnum-int options)))

;; We'll also want to add icons to menu items.
(def-gensym-c-function add-color-string-to-menu
    (:fixnum-int "g2ext_add_color_string_to_item_menu")
  ((:pointer menu)
   (:wide-string string)
   (:fixnum-int id)
   (:fixnum-int options)
   (:fixnum-int foreground)
   (:fixnum-int background)))

(def-gensym-c-function add-submenu-to-menu
    (:fixnum-int "g2ext_add_submenu_to_item_menu")
  ((:pointer menu)
   (:wide-string string)
   (:pointer submenu)
   (:fixnum-int options)))

;;; `Choose-from-item-menu' pops up the menu, tracks modally, and returns ID of
;;; choice or 0 if cancelled.

(def-gensym-c-function choose-from-item-menu
    (:fixnum-int "g2ext_choose_from_item_menu")
  ((:pointer window)
   (:pointer menu)
   (:fixnum-int x)
   (:fixnum-int y)))

(def-gensym-c-function reclaim-item-menu
    (:fixnum-int "g2ext_reclaim_item_menu")
  ((:pointer menu)
   (:fixnum-int top-level-p)))




;;;; Native Notification Control


;;; A `notification-control' is a native version of the GUIDE "notification"
;;; dialog, which is a persistent dialog with a message and icon but no
;;; buttons. At most one of these is allowed to exist per TW process. Attempting
;;; to create a second merely updates the first.
;SS_ERROR
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter notification-control-handle -1)
)

(defmacro make-icp-args (&rest names)
  `(nconc
     ,@(loop for name in names
             collect `(when ,name
                        (icp-list (quote ,name) ,name)))))

(defun manage-notification (gensym-window operation &optional caption message icon font-size)
  (when (native-animation-control-p gensym-window) ; Sufficient condition.
    (let* ((args ())
           (icon (dialog-icon-handle icon))
           (opcode? (case operation
                      (post (setq args (make-icp-args caption message font-size icon))
                            0)
                      (remove 1)
                      (update (setq args (make-icp-args message))
                              2))))
      (when opcode?
        (with-icp-window (gensym-window)
          (send-icp-manage-native-control
            gensym-window notification-control-handle opcode? args))
        (reclaim-icp-list args)))))

(defun manage-notification-1 (opcode args)
  (c-manage-notification opcode
                         (getf args 'caption #w"Notification")
                         (getf args 'message #w"")
                         (getf args 'font-size 0)
                         (getf args 'icon 0)))

(def-gensym-c-function c-manage-notification
    (:fixnum-int "g2ext_manage_notification")
  ((:fixnum-int opcode)
   (:wide-string caption)
   (:wide-string message)
   (:fixnum-int font-size)
   (:fixnum-int icon)))




;;;; Native Animation Control


;;; An `animation-control' is a native version of the GUIDE "delay-notification"
;;; dialog, which is a little animation plus message. At most one of these is
;;; allowed to exist per TW process. Attempting to create a second merely
;;; updates the first.

(def-concept animation-control)
;SS_ERROR
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter animation-control-handle -2)
)

(defun manage-animation
    (gensym-window operation &optional caption message media font-size)
  (when (native-animation-control-p gensym-window)
    (let* ((args ())
           (opcode? (case operation
                      ;; Opcodes match those in g2ext_manage_animation
                      (post (setq args (make-icp-args caption message media font-size))
                            0)
                      (remove 1)
                      (update (setq args (make-icp-args message))
                              2)
                      (stop 3)
                      (start 4)
                      (seek
                       ;; Squeeze frame number into opcode.
                       (logiorf (ashf (or font-size 0) 8) 5))
                      (step 6))))
      (when opcode?
        (with-icp-window (gensym-window)
          (send-icp-manage-native-control
            gensym-window animation-control-handle opcode? args)))
      (reclaim-icp-tree args))))

(defun manage-animation-1 (opcode args)
  (c-manage-animation opcode
                      (getf args 'caption #w"Please wait...")
                      (getf args 'message #w"")
                      (getf args 'font-size 0)
                      (getf args 'media #w"")))

(def-gensym-c-function c-manage-animation
    (:fixnum-int "g2ext_manage_animation")
  ((:fixnum-int opcode)
   (:wide-string caption)
   (:wide-string message)
   (:fixnum-int font-size)
   (:wide-string media)))


;;;; Modeless Native Controls


;;; The icp-message-type `manage-native-control' is a general-purpose ICP
;;; message for managing modeless controls; that is, those which do not need to
;;; enter a modal event loop inside their ICP message handler. They don't need
;;; the with-deferred-execution-in-tw, for example.

;;; It was created in an attempt to reduce the amount of repetitive code
;;; required for each new native control added to Telewindows.

;;; Each native control instance has a unique handle, managed by G2. As a
;;; special case, controls which permit at most one per process have permanently
;;; allocated handles, which are negative. Currently, those are the only
;;; controls we have.

;;; Other examples of at-most-one-per-process controls are the menu bar, status
;;; bar, and progress bar. They have their own API, but we might add extensions
;;; through this interface.

;;; We'll need another general message for the reverse direction, so that the
;;; control can send notifications back to G2. It would also be nice to have a
;;; general mechanism for caching control attributes on the G2 side. The cache
;;; could be a G2 item, but that's a little awkward since native controls are
;;; window-specific. All this was done in an ad-hoc way for NMS.

;;; We want to be smart about which control notifications can be handled locally
;;; and which need to be sent to G2.

;;; This is trying to become a remote Win32 funcall. The fixnum opcode could,
;;; for example, be a Windows message value for the control. We would still need
;;; routines to unpack the arguments plist into Win32 structures.

;;; The overhead of a keyword arguments might be a burden for control messages
;;; which are sent frequently or rapidly. We can always add special ICP messages
;;; and C routines for those cases.

;; TODO: Factor out opcodes common to all controls: create, destroy, ...

(def-icp-message-type manage-native-control
    ((gensym-window gensym-window)
     (fixnum handle)                        ; Control handle
     (fixnum opcode)                        ; Function to perform.
     (icp-tree args))                        ; Additional arguments
  (declare (ignore gensym-window))
  ;; Later, this will look up the handle in a TW-side table to retrieve the hwnd
  ;; and the manager function. For now, we just have two hardwired handles. All
  ;; we care about getting right in this pass is the format of the ICP message.
  (case handle
    (#.notification-control-handle (manage-notification-1 opcode args))
    (#.animation-control-handle   (manage-animation-1 opcode args)))
  (reclaim-icp-tree-with-text-strings args))



;;;; Reset Native Controls


;;; The function `reset-native-controls' cancels all transient native controls,
;;; meaning popup menus and dialogs, and exits any modal event loops. This
;;; should be done on reset-kb, which means it happens on clear-kb, too.
;; Maybe only on clear-kb?

(defun reset-native-controls (gensym-window)
  (when (native-animation-control-p gensym-window) ; Suffices
    (with-icp-window (gensym-window)
      (send-icp-reset-native-controls))))

(def-icp-message-type reset-native-controls ()
  (c-cancel-modal-dialogs-and-menus)
  (c-note-progress #w"" -1)
  ;; TODO: Later this will loop over a table of control handles.
  (c-manage-animation 1 #w"" #w"" 0 #w"")
  (c-manage-notification 1 #w"" #w"" 0 0)
  ;; Be sure to nuke any waiting in TW's queue, too.
  (discard-queued-modal-dialogs))

;;; The gensym-c-function `c-cancel-modal-dialogs-and-menus' sends a WM_CANCEL
;;; to all of our windows, and calls EndDialog on all of our dialogs.

(def-gensym-c-function c-cancel-modal-dialogs-and-menus
    (:fixnum-int "g2ext_cancel_modal_dialogs_and_menus")
  ())


;;;; Server File Browsing

;;; The gensym-c-function `c-list-directory-response' is used to feed the files
;;; in a directory listing to C, one-by-one, since our FFI does not support
;;; arrays.

(def-gensym-c-function c-list-directory-response
    (:fixnum-int "g2ext_list_directory_response")
  ((:fixnum-int opcode)                        ; 0=begin, 1=next file, 2=end, 3=error
   (:fixnum-int type)
   (:fixnum-int size)                        ; Assuming <512MB
   (:fixnum-int time-high)
   (:fixnum-int time-low)
   (:wide-string name)))

(def-icp-message-type list-directory-response
    ((fixnum handle)                        ; Requester (ignored)
     (icp-tree listing))                ; List of file info or error string.
  handle
  (cond ((listp listing)
         (c-list-directory-response 0 (length listing) 0 0 0 #w"")
         (loop for (filename time size?) in listing
               as type = (if size? 0 1) ; NIL size means a directory
               doing
           (multiple-value-bind (time-high time-low)
               (float-to-words time)
             (c-list-directory-response 1 type (or size? 0) time-high time-low filename)))
         (c-list-directory-response 2 0 0 0 0 #w""))
        (t
         ;; Otherwise, there was an error. We must call c-list-directory-response in all
         ;; cases because the modal file dialog is waiting for us.
         (c-list-directory-response 3 0 0 0 0 (if (text-string-p listing) listing #w""))))
  (reclaim-icp-tree-value listing))

(def-gensym-c-function c-list-sys-drives-response
    (:void "g2ext_list_sys_drives_response")
  ((:string name)))

(def-icp-message-type list-sys-drives-response
    ((wide-string arg))                

         (c-list-sys-drives-response arg)
)





(defun float-to-words (float)
  (with-temporary-gensym-float-creation float-to-words
    (with-temporary-bignum-creation
      (let ((bignum (round (if (managed-float-p float) (managed-float-value float) float))))
        (values (logand (ash bignum -16) #xFFFF)
                (logand bignum #xFFFF))))))




#+development
(defun test-list-directory (gensym-window)
  (when (current-window-supports-list-directory gensym-window)
    (let ((native-window (native-window? gensym-window)))
      (enqueue-local-event
        native-window
        (key-code-for-key-symbol 'list-directory)
        (c-x11-last-mouse-x-position native-window)
        (c-x11-last-mouse-y-position native-window)
        (c-x11-last-event-time native-window)
        (gensym-list 'handle 1234        ; Simply sent back to TW.
                     'directory (copy-text-string #w"/home/fmw/"))))))




;;;; Telewindows-local Bitmap Printing


(defun handle-print-window-event (workstation local-event)
  (declare (ignore local-event))
  (let ((gensym-window (window-for-workstation workstation)))
    (with-deferred-execution-in-tw ()
      (print-window-1 gensym-window (gensym-window-serial-number gensym-window) nil))))

(defun print-window-1 (gensym-window serial use-default-printer)
  (let ((flags (if use-default-printer 1 0)))
    (when (gensym-window-has-not-been-reprocessed-p gensym-window serial)
    (c-print-window (native-window? gensym-window) #w"" flags))))

(def-gensym-c-function c-print-window
    (:fixnum-int "g2ext_print_window")
  ((:pointer window)
   (:wide-string jobname)
   (:fixnum-int flags)))                  ; 1=use default printer (no dialog)

(def-icp-message-type print-native-window
    ((gensym-window gensym-window)
     (boolean is-print-dlg-showed))
  (print-window-1 gensym-window (gensym-window-serial-number gensym-window) (not is-print-dlg-showed)))


;;;; Native Printing


(def-icp-message-type native-printing-dialog
    ((gensym-window gensym-window)
     (wide-string item-uuid)
     (wide-string jobname))
  (with-deferred-execution-in-tw ()
    (print-dialog-1 gensym-window (gensym-window-serial-number gensym-window)
                    item-uuid jobname)))

(def-icp-message-type native-printing-ex
    ((gensym-window gensym-window)
     (wide-string item-uuid)
     (wide-string jobname)
     (icp-tree options))
  (let ((use-default-printer (getf options 'use-default-printer)))
    (with-deferred-execution-in-tw ()
      (print-dialog-1 gensym-window (gensym-window-serial-number gensym-window)
                      item-uuid jobname use-default-printer))
    (reclaim-icp-tree-with-text-strings options)))


;;; The function `print-dialog-1' posts the Windows print dialog, and if not
;;; cancelled, sends an extended event back to G2 with all of the information
;;; for the chosen printer, and the given uuid and jobname.

(def-gensym-c-function c-print-dialog
    (:fixnum-int "g2ext_print_dialog")
  ((:pointer window)
   (:wide-string jobname)                ; input
   (:fixnum-int flags)                        ; 1=use default printer (no dialog)
   (:string printer)                        ; output
   (:fixnum-int buflen)                        ; length of printer string
   (:wide-string results)))                ; other dialog results.

(defun print-dialog-1 (gensym-window gensym-window-serial-number
                                     uuid jobname &optional use-default-printer)
  (when (gensym-window-has-not-been-reprocessed-p gensym-window gensym-window-serial-number)
    (let* ((native-window (native-window? gensym-window))
           (printer-name (obtain-simple-gensym-string 100))
           (results (allocate-byte-vector-16 16))
           (flags (if use-default-printer 1 0))
           (job (c-print-dialog native-window jobname
                                flags
                                printer-name 100
                                results)))
      (when (>f job 0)
        (enqueue-local-event
          native-window
          (key-code-for-key-symbol 'print-dialog)
          (c-x11-last-mouse-x-position native-window)
          (c-x11-last-mouse-y-position native-window)
          (c-x11-last-event-time native-window)
          (gensym-list 'printer (copy-null-terminated-string-as-text-string printer-name)
                       'uuid uuid        ; Send it back
                       'jobname jobname        ; Send it back
                       'width (byte-vector-16-aref results 0) ; See g2ext_print_dialog
                       'height (byte-vector-16-aref results 1)
                       'x-dpi (byte-vector-16-aref results 2)
                       'y-dpi (byte-vector-16-aref results 3)
                       'physical-width (byte-vector-16-aref results 4)
                       'physical-height (byte-vector-16-aref results 5)
                       'x-offset (byte-vector-16-aref results 6)
                       'y-offset (byte-vector-16-aref results 7)
                       'from-page (byte-vector-16-aref results 8)
                       'to-page (byte-vector-16-aref results 9))))
      (reclaim-byte-vector-16 results)
      (reclaim-gensym-string printer-name))))




(defun send-icp-message (fun gensym-window &optional (arg-1 no-arg) (arg-2 no-arg) (arg-3 no-arg)
                             (arg-4 no-arg) (arg-5 no-arg) (arg-6 no-arg) (arg-7 no-arg)
                             (arg-8 no-arg) (arg-9 no-arg))
  (if current-icp-port
      (call-per-number-of-actual-args funcall 1 fun arg-1 arg-2 arg-3 arg-4 arg-5
                                      arg-6 arg-7 arg-8 arg-9)
      (with-icp-window (gensym-window)
        (call-per-number-of-actual-args funcall 1 fun arg-1 arg-2 arg-3 arg-4 arg-5
                                        arg-6 arg-7 arg-8 arg-9))))

(defun native-printing-start-doc (gensym-window)
  (send-icp-message 'send-icp-native-printing-control gensym-window gensym-window 1))

(defun native-printing-start-page (gensym-window page-number nrows ncolumns
                                                 left-margin top-margin
                                                 right-margin bottom-margin
                                                 scale multipage-legend-p)
  (send-icp-message 'send-icp-native-printing-start-page
                    gensym-window page-number nrows ncolumns
                    left-margin top-margin
                    right-margin bottom-margin
                    scale (logiorf (if multipage-legend-p 1 0))))

(defun native-printing-end-page (gensym-window)
  (send-icp-message 'send-icp-native-printing-control gensym-window gensym-window 3))

(defun native-printing-end-doc (gensym-window)
  (send-icp-message 'send-icp-native-printing-control gensym-window gensym-window 4))

(defun native-printing-begin (gensym-window)
  (send-icp-message 'send-icp-native-printing-control gensym-window gensym-window 5))

(defun native-printing-end (gensym-window)
  (send-icp-message 'send-icp-native-printing-control gensym-window gensym-window 6))

(defun native-printing-abort-printing (gensym-window)
  (send-icp-message 'send-icp-native-printing-control gensym-window gensym-window 7))


;;; The variable `drawing-to-printer-p' is bound to T on the Telewindows side
;;; while we are drawing to a printer DC. Various TW-side drawing code can use
;;; this to handle printing specially.

(defvar drawing-to-printer-p nil)

(def-icp-message-type native-printing-control
    ((gensym-window gensym-window)
     (unsigned-integer opcode))
  (let ((native-window (native-window? gensym-window)))
    (fixnum-case opcode
      (1                                ; Not currently used.
        (c-start-doc native-window #w"G2-printjob"))
;      (2
;        (c-start-page))
      (3
        (c-end-page))
      (4
        (c-end-doc))
      (5
        (c-draw-to-printer native-window 1)
        (setq drawing-to-printer-p t))
      (6
        (c-draw-to-printer native-window 0)
        (setq drawing-to-printer-p nil))
      (7
        (c-abort-printing)))))

(def-gensym-c-function c-draw-to-printer
    (:fixnum-int "g2ext_draw_to_printer")
  ((:pointer window)
   (:fixnum-int enable)))

(def-gensym-c-function c-start-doc (:fixnum-int "g2ext_start_doc")
  ((:pointer window)
   (:wide-string jobname)))

(def-icp-message-type native-printing-start-page
    ((fixnum page-number)
     (fixnum nrows)
     (fixnum ncolumns)
     (fixnum left-margin)
     (fixnum top-margin)
     (fixnum right-margin)
     (fixnum bottom-margin)
     (fixnum scale)
     (fixnum flags))
  (let ((label (twith-output-to-wide-string
                 (tformat "~a " (system-alias current-system-name))
                 (twrite-long-system-version-string))))
    (c-start-page page-number label nrows ncolumns
                  left-margin top-margin
                  right-margin bottom-margin
                  scale flags)
    (reclaim-wide-string label)))

(def-gensym-c-function c-start-page (:fixnum-int "g2ext_start_page")
  ((:fixnum-int page-number)
   (:wide-string label)                        ; Goes on bottom left of page.
   (:fixnum-int nrows)
   (:fixnum-int ncolumns)
   (:fixnum-int left-margin)                ; In tenths of inches
   (:fixnum-int top-margin)
   (:fixnum-int right-margin)
   (:fixnum-int bottom-margin)
   (:fixnum-int workspace-units-per-ten-inches)
   (:fixnum-int flags)))                ; 1=multipage-legend, etc.


(def-gensym-c-function c-end-page (:fixnum-int "g2ext_end_page")
  ())

(def-gensym-c-function c-end-doc (:fixnum-int "g2ext_end_doc")
  ())

(def-gensym-c-function c-abort-printing (:fixnum-int "g2ext_abort_printing")
  ())

;;; The gensym-c-function `c-set-icon-offsets' sets the offset and clip region
;;; for following scratchpad drawing calls. Applies only when drawing to the
;;; native printer.

(def-gensym-c-function c-set-icon-offsets (:fixnum-int "g2ext_set_icon_offsets")
  ((:fixnum-int left)
   (:fixnum-int top)
   (:fixnum-int clip-left)
   (:fixnum-int clip-top)
   (:fixnum-int clip-right)
   (:fixnum-int clip-bottom)))

(defvar icon-offset-left 0)
(defvar icon-offset-top 0)
(defvar icon-offset-clip-left 0)
(defvar icon-offset-clip-top 0)
(defvar icon-offset-clip-right 0)
(defvar icon-offset-clip-bottom 0)

;; kind-of with-virtual-scratchpad-raster
(defmacro with-icon-offsets ((left top clip-left clip-top clip-right clip-bottom) &body body)
  `(progn
     (let ((icon-offset-left ,left)
           (icon-offset-top ,top)
           (icon-offset-clip-left ,clip-left)
           (icon-offset-clip-top ,clip-top)
           (icon-offset-clip-right ,clip-right)
           (icon-offset-clip-bottom ,clip-bottom))
       (c-set-icon-offsets icon-offset-left icon-offset-top
                           icon-offset-clip-left icon-offset-clip-top
                           icon-offset-clip-right icon-offset-clip-bottom)
       ,@body)
     (c-set-icon-offsets icon-offset-left icon-offset-top
                         icon-offset-clip-left icon-offset-clip-top
                         icon-offset-clip-right icon-offset-clip-bottom)))


;;; The ICP message `paint-icon-in-current-window' enters a context on TW where
;;; for the next N message groups the pixmap drawing routines are redirected to
;;; the printer, clipped and translated by an offset. Used for graphs as well as
;;; icons.

(def-icp-message-functions paint-icon-in-current-window
    ((coordinate left)
     (coordinate top)
     (coordinate clip-left)
     (coordinate clip-top)
     (coordinate clip-right)
     (coordinate clip-bottom)
     (fixnum number-of-message-groups))
  (case type-of-current-window
    (x11-window
     (let ((current-scratchpad-raster current-native-window?) ; ??? Not a native window !!!
           (current-scratchpad-raster-type 'x11-pixmap)
           (on-monochrome-raster-list-p nil)
           (current-scratchpad-raster-tiled-p nil)
           (current-x-offset-for-stored-raster? nil)
           (current-y-offset-for-stored-raster? nil)
           (current-x-max-for-stored-raster? nil)
           (current-y-max-for-stored-raster? nil))
       (with-icon-offsets (left top clip-left clip-top clip-right clip-bottom)
         (loop repeat number-of-message-groups doing
           (handle-icp-messages t)))))))


;;; The icp-message-functions `paint-line-of-text-in-current-window' draws a
;;; line of Unicode text using native fonts.

(def-icp-message-functions paint-line-of-text-in-current-window
    ((coordinate clipped-left-edge) (coordinate clipped-top-edge)
     (coordinate clipped-right-edge) (coordinate clipped-bottom-edge)
     text-line word-spacing
     (symbol ab-font-name)
     color-value
     (fixnum angle)                        ; Angle in tenths of a degree
     (fixnum flags)                        ; Flags: bit-0 = reflect-left-right-p
     x-scale y-scale
     (coordinate left-edge-of-line-of-text-in-window)
     (coordinate baseline-in-window))
  (case type-of-current-window
    (x11-window
     (let ((font-map (gensym-list ab-font-name)))
       (c-x11-draw-string current-native-window?
                          clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge
                          left-edge-of-line-of-text-in-window baseline-in-window
                          color-value
                          (ab-font-point-size (ab-font ab-font-name))
                          angle flags
                          x-scale y-scale
                          (compute-width-of-text-line text-line nil nil font-map word-spacing)
                          text-line (text-line-length text-line))
       (reclaim-gensym-list font-map)))))



;;;; Native Help


(def-gensym-c-function c-html-help
    (:fixnum-int "g2ext_html_help")
  ((:fixnum-int cmd)
   (:string directory)
   (:string file)
   (:string string)
   (:fixnum-int id)
   (:fixnum-int x)                        ; Screen coor for popup help.
   (:fixnum-int y)
   (:fixnum-int flags)))

(defun %html-help (cmd &optional (dir #w"") (file #w"") (string #w"") (id 0) (x 0) (y 0) (flags 0))
  (c-html-help cmd dir file string id x y flags))



(defun html-help-ex (cmd plist &optional reclaim-p)
  (let* ((dir (getf plist 'help-file-directory #w""))
         (file (getf plist 'help-file-name #w"Master.chm"))
         (topic? (getf plist 'topic))
         (string (if (stringpw topic?) topic? #w""))
         (id (if (fixnump topic?) topic? 0))
         (sync? (getf plist 'sync))
         (stemmed? (getf plist 'match-similar-words))
         (titles? (getf plist 'search-titles-only))
         (x (getf plist 'x -1))                ; Pos of top-center of popup help.
         (y  (getf plist 'y -1))
         (flags (logiorf (if sync? 1 0)
                         (if stemmed? 2 0)
                         (if titles? 4 0))))
    (prog1
        (%html-help cmd dir file string id x y flags)
      (when reclaim-p
        (reclaim-icp-tree-with-text-strings plist)))))

(def-icp-message-type html-help-ex        ; New message
    ((fixnum cmd)
     (icp-tree plist))
  (with-deferred-execution-in-tw ()        ; Because it may popup a message box.
    (html-help-ex cmd plist t)))

(def-icp-message-type html-help                ; Old message, uses PATH or envar to find helpfile.
    ((gensym-window gensym-window)
     (wide-string pathname)
     (fixnum topic))
  (declare (ignore gensym-window topic))
  (with-deferred-execution-in-tw ()
    (%html-help hh-display-envar-topic))
  (reclaim-text-string pathname))







;;;; Native Titles



;;; The function `set-window-title' sets the title of the gensym-window to
;;; string. This affects only the top-level, application window's title bar.

;;; GENSYMCID-1417: if option -netinfo was added, network information should be
;;; added into the title of window.

(defun set-to-default-window-title ()
  (multiple-value-bind (host-name port-list)
    (get-raw-network-info)
    (add-network-info-to-title-if-appropriate host-name port-list)
    (reclaim-raw-network-info host-name port-list)))

(defun set-window-title (gensym-window string?)
  (let ((string (or string? #w"")))
    (case (type-of-gensym-window gensym-window)
      (icp (with-icp-window (gensym-window)
             (send-icp-set-window-title gensym-window string)))
      (x11-window
       (if string?
         (c-x11-set-window-title (native-window? gensym-window) string)
         (set-to-default-window-title))))))

;;; The icp-message-type `set-window-title' sets the window's title to the given
;;; string.

(def-icp-message-type set-window-title
    ((gensym-window gensym-window)
     (text-string title))
  (let ((new-title
         (if (string=w #w"" title)
             (copy-as-wide-string
               (system-window-title-string current-system-name))
           title)))
    (c-x11-set-window-title (native-window? gensym-window) new-title)
    (when (string=w #w"" title)
      (reclaim-text-string new-title))))

;;; The gensym-c-function `c-x11-set-window-title' sets the title of the given
;;; window, normally a MDI child window.  Unicode is permitted.  Maps to Win32
;;; SetWindowText.  On X it would be a window manager call.

(def-gensym-c-function c-x11-set-window-title
    (:fixnum-int "g2ext_x11_set_window_title")
  ((:pointer native-window)
   (:wide-string title)))


;;;; Native Icons


(def-concept native-icons)                ; Also in COMMANDS2

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defconstant begin-drawing-to-icon-buffer 1)
  (defconstant begin-drawing-to-icon-mask 2)
  (defconstant save-native-icon 3)
  (defconstant destroy-native-icons 4)
  (defconstant stop-drawing-to-icon 5)
  (defconstant refresh-native-icon 6))

(defun icon-polychrome-pixmap (gensym-window width height)
  (setf (icon-polychrome-pixmap? gensym-window)
        (ensure-pixmap-of-size
          gensym-window
          (icon-polychrome-pixmap? gensym-window)
          width height (window-screen-depth gensym-window))))

(defun icon-mask-pixmap (gensym-window width height)
  (setf (icon-mask-pixmap? gensym-window)
        (ensure-pixmap-of-size
          gensym-window (icon-mask-pixmap? gensym-window) width height 1)))


;;; The function `ensure-pixmap-of-size' ensure that pixmap is non-NIL and of
;;; the desired dimensions. It is recreated as needed. Can return NIL if we run
;;; out of memory.

(defun ensure-pixmap-of-size (gensym-window pixmap? width height depth)
  (cond ((and pixmap?
              (=f (pixmap-width pixmap?) width)
              (=f (pixmap-height pixmap?) height)
              (=f (pixmap-depth pixmap?) depth))
         pixmap?)
        (t
         (when pixmap?
           (reclaim-pixmap pixmap?))
         (setq pixmap?
               (allocate-offscreen-pixmap
                 gensym-window width height depth)))))


;;; The ICP message `manage-native-icons' does all things related to creating
;;; native icons. Must NOT be called during double buffering!!

(def-icp-message-type manage-native-icons
    ((gensym-window gensym-window)
     (fixnum opcode)
     (fixnum handle)
     (fixnum width)
     (fixnum height))
  (case opcode
    (#.begin-drawing-to-icon-buffer
     (setf is-icon-mask-drawing nil)
     (let ((pixmap? (icon-polychrome-pixmap gensym-window width height)))
       (when pixmap?
         (c-x11-draw-offscreen (native-window? gensym-window)
                               (pixmap-pointer pixmap?)
                               1))))
    (#.begin-drawing-to-icon-mask
     (let ((pixmap? (icon-mask-pixmap gensym-window width height)))
       (when pixmap?
         (c-x11-draw-offscreen (native-window? gensym-window)
                               (pixmap-pointer pixmap?)
                               1)
     (setf is-icon-mask-drawing t))))

    (#.stop-drawing-to-icon
     (setf is-icon-mask-drawing nil)
     (c-x11-draw-offscreen (native-window? gensym-window) -1 0))

    (#.save-native-icon
     (when (and (icon-polychrome-pixmap? gensym-window)
                (icon-mask-pixmap? gensym-window))
       (c-x11-manage-native-icons (native-window? gensym-window)
                                  opcode
                                  handle
                                  (pixmap-width (icon-polychrome-pixmap? gensym-window))
                                  (pixmap-height (icon-polychrome-pixmap? gensym-window))
                                  (pixmap-pointer (icon-polychrome-pixmap? gensym-window))
                                  (pixmap-pointer (icon-mask-pixmap? gensym-window)))))
    (#.destroy-native-icons
     (c-x11-manage-native-icons (native-window? gensym-window) opcode 0 0 0 0 0))

    (#.refresh-native-icon
     (c-x11-manage-native-icons (native-window? gensym-window) opcode handle width 0 0 0))

    (t
     (dwarn "Bogus opcode ~s in manage-native-icons." opcode))))

(defun begin-drawing-to-icon-buffer (gensym-window width height)
  (send-icp-manage-native-icons
    gensym-window begin-drawing-to-icon-buffer 0 width height))

(defun begin-drawing-to-icon-mask (gensym-window width height)
  (send-icp-manage-native-icons
    gensym-window begin-drawing-to-icon-mask 0 width height))

(defun end-drawing-to-icon (gensym-window)
  (send-icp-manage-native-icons
    gensym-window stop-drawing-to-icon 0 0 0))

(defun save-native-icon (gensym-window handle width height)
  (send-icp-manage-native-icons
    gensym-window save-native-icon handle width height))

(defun destroy-native-icons (gensym-window)
  (send-icp-manage-native-icons
    gensym-window destroy-native-icons 0 0 0))

;; "Where" is a bitmask of things to redraw.
(defun refresh-native-icon (gensym-window icon-handle where)
  (send-icp-manage-native-icons
    gensym-window refresh-native-icon icon-handle where 0))

(def-gensym-c-function c-x11-manage-native-icons
    (:fixnum-int "g2ext_x11_manage_native_icons")
  ((:pointer native-window)
   (:fixnum-int opcode)
   (:fixnum-int handle)
   (:fixnum-int width)
   (:fixnum-int height)
   (:pointer color-pixmap)
   (:pointer mask-pixmap)))


;;;; UI Properties (mouse cursor, etc)


(def-icp-message-type manage-ui-properties
    ((gensym-window gensym-window)
     (fixnum property-id)                ; Later, may also be an opcode.
     (icp-tree icp-value))
  (manage-ui-properties-1 gensym-window property-id icp-value)
  (reclaim-icp-tree-with-text-strings icp-value))

(defun manage-ui-properties-1 (gensym-window property-id icp-value)
  (cond ((icp-window-p gensym-window)
         (with-icp-window (gensym-window)
           (send-icp-manage-ui-properties gensym-window property-id icp-value)))
        (t
         (when (fixnump icp-value)
           (c-set-ui-property (native-window? gensym-window) property-id icp-value)))))

(def-gensym-c-function c-set-ui-property
    (:fixnum-int "g2ext_set_ui_property")
  ((:fixnum-int window)
   (:fixnum-int property-id)
   (:fixnum-int value)))


;;;; Tabbed MDI Mode


(def-icp-message-type tabbed-mdi-mode
    ((gensym-window gensym-window)
     (fixnum mode)
     (icp-tree options))
  (tabbed-mdi-mode-1 gensym-window mode options)
  (reclaim-icp-tree-with-text-strings options))

(defun tabbed-mdi-mode-1 (gensym-window mode options)
  (cond ((icp-window-p gensym-window)
         (with-icp-window (gensym-window)
           (send-icp-tabbed-mdi-mode gensym-window mode options)))
        (t
         (c-tabbed-mdi-mode mode 0)
         (when (plistp options)                ; Paranoia
           (loop for (property value) on options doing
             (when (and (fixnump property) (fixnump value)) ; Paranoia
               (c-tabbed-mdi-mode property value)))))))


(def-gensym-c-function c-tabbed-mdi-mode
    (:fixnum-int "g2ext_tabbed_mdi_mode")
  ((:fixnum-int opcode)
   (:fixnum-int arg)))


;;;; Containers, Docking, and Neighbors


;;; The function `encode-dock-and-neighbor' computes the DOCK and NEIGHBOR
;;; arguments to supply to the C routines that create native views. We do some
;;; screwy bit-packing to encode the various possibilities. The packing is
;;; interpreted by CMainFrame::WrapWnd() in twng/c/MainFrm.cpp.

;;; return (values dock-arg neighbor-arg)
(defun encode-dock-and-neighbor (container dock neighbor)
  (case container
    (mdi-child                                ; Create a MDI Child window
     (values dock-code-mdi-child 0))
    (top-level                                ; Create a top-level window (NYI)
     (values dock-code-top-level 0))
    (pane                                ; Create a docking pane
     (values (get-dock-code dock) neighbor))
    (t
     (cond ((fixnump container)                ; Container is a view handle, neighbor is ctrlID
            ;; Pack the ctrlID into dock, since ctrlID's are small integers, and
            ;; put the container view handle into neighbor.
            (values (logiorf (ashf (logandf neighbor #xFFFF) 4) dock-code-embedded)
                    container))
           (t
            (values 0 0))))))

(defmacro with-decoded-view-options ((arg &key (title #w"") (container 'pane) (dock 'left)
                                          (title-property 'title)
                                          (width cw-usedefault)
                                          (height cw-usedefault)
                                          (min-width 0)
                                          (min-height 0))
                                     &body body)
  `(when (plistp ,arg)                        ; paranoia
     (let* ((title (getf ,arg ',title-property ',title))
            (left (getf ,arg 'left cw-usedefault))
            (top (getf ,arg 'top cw-usedefault))
            (sort-column (getf ,arg 'sort-column sort-column-default))
            (sorting-order (getf ,arg 'sorting-order sorting-order-default))
            (width (getf ,arg 'width ,width))
            (height (getf ,arg 'height ,height))
            (container (getf ,arg 'container ',container))
            (min-width (getf ,arg 'min-width ,min-width))
            (min-height (getf ,arg 'min-height ,min-height)))
       (declare (ignorable title left top sort-column sorting-order
                           width height container min-width min-height))
       (multiple-value-bind (dock neighbor)
           (encode-dock-and-neighbor
             container (getf ,arg 'dock ',dock) (getf ,arg 'neighbor 0))
         dock neighbor
         ,@body))))


(defmacro with-decoded-message-options ((arg &key (message #w"")
                                                  (message-type 'error)
                                                  (workspace-uuid #w"")
                                                  (workspace-name #w"")
                                                  (object-name #w"")
                                                  (object-type #w"")
                                                  (object-uuid #w"")
                                                  (line-number -1))
                                             &body body)
  `(when (plistp ,arg) ; paranoia
     (let* ((message (getf ,arg 'message ,message))
            (message-type (getf ,arg 'message-type ',message-type))
            (workspace-uuid (getf ,arg 'workspace-uuid ,workspace-uuid))
            (workspace-name (getf ,arg 'workspace-name ,workspace-name))
            (object-name (getf ,arg 'object-name ,object-name))
            (object-type (getf ,arg 'object-type ,object-type))
            (object-uuid (getf ,arg 'object-uuid ,object-uuid))
            (line-number (getf ,arg 'line-number ,line-number)))
       ,@body)))

;;;; Native Logbook


(defconstant-for-case logbook-create 1)                ; Sync with twng/c/LogBook.h
(defconstant-for-case logbook-append-extended-message 17)


(defconstant logbook-message-board-code 0)
(defconstant logbook-operator-logbook-code 1)

(defun encode-logbook-type (logbook-type)
  (cond
    ((eq logbook-type 'message-board)
     logbook-message-board-code)
    ((eq logbook-type 'operator-logbook)
     logbook-operator-logbook-code)
    (t
     #+development
     (cerror "Continue" "logbook-type is not 'message-board or 'operator-logbook")
     -1)))

(def-gensym-c-function c-is-operator-logbook-enabled
                       (:fixnum-int "g2ext_is_operator_logbook_enabled")
  ())

(def-gensym-c-function c-is-message-board-enabled
                       (:fixnum-int "g2ext_is_message_board_enabled")
  ())

(defvar operator-logbook-enabled
  #+chestnut-trans (c-is-operator-logbook-enabled)
  #-chestnut-trans 1)

(defvar message-board-enabled
  #+chestnut-trans (c-is-message-board-enabled)
  #-chestnut-trans 1)

(def-icp-message-type manage-logbook
    ((gensym-window gensym-window)
     (fixnum opcode)
     (fixnum handle)
     (fixnum msg)                        ; message number
     (fixnum date)                        ; message date (encoded per simple-encode-date)
     (icp-tree arg))
  (case opcode
    (#.logbook-create
     (with-decoded-view-options (arg :dock right)
       (let* ((logbook-type (encode-logbook-type (getf arg 'logbook-type)))
              (window-index
                (c-create-logbook handle title left top width height dock neighbor logbook-type))
              (native-window
                (make-basic-native-window gensym-window handle window-index 'g2-output-view container)))
         (process-view-init-plist native-window arg '(title)))))
    (t
     (manage-logbook-1 gensym-window opcode handle msg date arg)))
  (reclaim-icp-tree-with-text-strings arg))

(defun manage-logbook-1 (gensym-window opcode handle msg &optional date arg)
  (cond ((icp-window-p gensym-window)
         (with-icp-window (gensym-window)
           (send-icp-manage-logbook gensym-window opcode handle msg (or date 0) arg)))
        (t
         (c-manage-logbook opcode handle msg (or date 0) (if (stringpw arg) arg #w"")))))

(def-gensym-c-function c-create-logbook
    (:fixnum-int "g2ext_create_logbook")
  ((:fixnum-int handle)
   (:wide-string title)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int dock)
   (:fixnum-int neighbor)
   (:fixnum-int logbook-type)))

(def-gensym-c-function c-manage-logbook
    (:fixnum-int "g2ext_manage_logbook")
  ((:fixnum-int opcode)
   (:fixnum-int handle)
   (:fixnum-int msg)
   (:fixnum-int date)
   (:wide-string string)))


;;;; Native Progress Bar


;;; The native progress bar lives inside the status bar. Someday it might be
;;; useful to put it into a popup dialog instead.

;;; The function `note-progress' displays note in the status bar and shows or
;;; updates the progress bar on all connected windows to indicate (/ pos max)
;;; fractionally complete. If pos is NIL, then the progress bar is hidden
;;; (presumably because the operation finished).

(defun note-progress (&optional (note #w"") pos (max 100))
  #+development (when current-icp-port
                  (warn "note-progress encountered nested with-icp-window!"))
  (loop with percent = (if pos (compute-percentage pos max) -1)
        for workstation in workstations-in-service
        as gensym-window = (window-for-workstation workstation)
        doing
    (when (native-progress-bar-p gensym-window)
      (note-progress-on-window gensym-window note percent)))
  (flush-icp-output-ports))

;;; The function `note-progress-on-window' updates the progress bar on just one
;;; specific window.

(defun note-progress-on-window (gensym-window message doneness)
  (current-system-case
    (ab
      (when (native-progress-bar-p gensym-window)
        (with-icp-window (gensym-window)
          (send-icp-manage-progress-bar gensym-window 0 message doneness))))
    (t
      gensym-window
      (c-note-progress message doneness))))

;;; The icp-message `manage-progress-bar' does all things for managing the
;;; progress bar, based on the opcode. For 7.1, the only opcode is 0, which
;;; means to update or hide it.

(def-icp-message-type manage-progress-bar
    ((gensym-window gensym-window)
     (fixnum opcode)                        ; Update, show, hide, resize, put-in-dialog, ...
     (wide-string message)
     (fixnum doneness))                        ; negative to hide progress bar
  (declare (ignore gensym-window))
  (case (logandf opcode 255)                ; Allows for parms in the high bits.
    (0 (c-note-progress message doneness)))
  (reclaim-wide-string message))

(def-gensym-c-function c-note-progress
    (:fixnum-int "g2ext_note_progress")
  ((:wide-string message)
   (:fixnum-int doneness)))





;;;; Native Menu System (NMS)


;;; This is a separate native menu protocol to support persistent menus such as
;;; a menu bar, and to support a system procedure interface for GMS.  It will be
;;; merged with the previous protocol post-GUS.  At the moment, I don't want to
;;; risk breaking the existing native popup menus code. -fmw, 3/13/02

;;; This protocol is a pretty straightforward mapping of Win32 menu system calls
;;; to ICP messages and sysprocs.

;;; The sysproc versions of these calls all take in addition a G2-Window argument.

;;; For each NMS function, there are actually 8 functions!

;;;  The KB-level sysproc           g2-nms-create-menu
;;;  The LISP sysproc               nms-create-menu
;;;  The LISP internal function     nms-create-menu-1
;;;  The ICP message sender         send-icp-nms-create-menu
;;;  The ICP message receiver       handle-icp-nms-create-menu
;;;  The C function interface       nms-c-create-menu
;;;  The C function                 g2ext_nms_create_menu
;;;  Finally, the Win32 function    CreateMenu

(def-concept nms)

;;; Bits for flags.  We might as well just copy the Win32 bit assignments.  From
;;; winuser.h

(defconstant mf-grayed       #x0001)
(defconstant mf-disabled     #x0002)
(defconstant mf-checked      #x0008)
(defconstant mf-popup        #x0010)
(defconstant mf-menubarbreak #x0020)
(defconstant mf-menubreak    #x0040)
(defconstant mf-ownerdraw    #x0100)
(defconstant mf-byposition   #x0400)
(defconstant mf-separator    #x0800)
(defconstant mf-rightjustify #x4000)
(defconstant mf-win32-flags-mask #x7FFF)

;; These are our own flags, beyond Win32's. Keep in sync with ext/c/graphics.h

(defconstant mf-builtin      #x8000)             ; Built-in menu or item => not deletable sysprocs.
(defconstant mf-dynamic      #x10000)        ; Dynamic NMS menu (posting callbacks)
(defconstant mf-wide         #x20000)        ; Use wide geometry (set if any item in menu has an icon)
(defconstant mf-menuselect   #x40000)        ; Wants selection callbacks
(defconstant mf-unpost       #x80000)        ; Wants unposting callbacks


;;; The parameter `nms-maximum-permitted-handle' is determined by Win32's limit
;;; on the range of a user menu item ID, and the fact that we pack handles into
;;; 15 bits for nms-enable-items, below.

(defparameter nms-maximum-permitted-handle 32000) ; Strict limit is #xE000-1 = 57343





;;; The variable `nms-constructing-built-in-menus-p' can be bound to T (on the
;;; G2 side) to cause any nms menu or menu item to be created with the
;;; mf-builtin flag set.

(defvar nms-constructing-built-in-menus-p nil)


(defun reclaim-gensym-cons? (cons?)
  #+development (unless cons? (dwarn "cons is NIL"))
  (when cons?
    (reclaim-gensym-cons cons?)))

;;; The hash-table `nms-menu-for-hmenu' maps a 32-bit Windows menu handle, in
;;; the form of a gensym-cons of the high and low 16 bits, to an NMS-MENU
;;; structure.

(def-hash-table nms-menu-for-hmenu
    :key-comparitor equal
    :key-reclaimer reclaim-gensym-cons?
    :use-binary-tree t)

(defvar nms-menu-hash-table (make-nms-menu-for-hmenu))


;;; The structure `nms-menu' has its first few slots in common with
;;; nms-menu-item, and we make use of that fact with various operations on
;;; menu-or-item's (mot's).

;;; The gensym-window keeps a table (as an array) mapping handles to nms-menu or
;;; nms-menu-item structures.

(def-structure (nms-menu (:reclaimer nms-reclaim-menu-1)
                         #+development (:print-function nms-print-menu-or-item))
  (nms-menu-handle nil)                        ; User-visible handle
  (nms-menu-parent nil)                        ; Handle of parent menu (if any)
  (nms-menu-label nil)                        ; Wide string Optional title or header
  (nms-menu-help nil)                        ; Doc string for status line.
  (nms-menu-flags 0)                        ; Win32 item flags (mf-grayed, etc)
  (nms-menu-command nil)                ; Partial command for parameter menus.
  (nms-menu-callback nil)                ; Name of activation callback procedure.
  (nms-menu-key nil)                        ; User-supplied fixnum, symbol, string, or frame.
  (nms-menu-fsn nil)                        ; FSN protecting key (if it is a frame)
  (nms-menu-position 0)                        ; zero-based position in parent menu, if any.
  (nms-menu-icon nil)                        ; Icon (16x16)
  (nms-menu-fg nil)                        ; Foreground color
  (nms-menu-bg nil)                        ; Background color
  (nms-menu-type 'popup)                ; menu-bar, popup, command, parameter, or toolbar
  (nms-menu-g2pointer -1)                ; g2pointer for Win32 HMENU (used only on TW side)
  (nms-menu-options nil)

  (nms-menu-argument nil)                ; Which-argument for command.
  (nms-menu-g2-menu nil)                ; Name of G2 menu, as defined with defmenu.
  (nms-menu-docking-position nil)        ; If a toolbar, it's initial docking position
  (nms-menu-posting-callback nil)        ; Name of posting callback procedure.
  (nms-menu-unposting-callback nil)        ; Name of unposting callback procedure.
  (nms-menu-selection-callback nil)        ; Name of selection callback procedure.
  (nms-menu-hmenu-high 0)                ; 32-bit Windows HMENU handle. Ugh.
  (nms-menu-hmenu-low 0)
  (nms-menu-item-count 0)                ; Number of items
  (nms-menu-items ()))                        ; gensym-list of nms-menu-item, LAST first.

(defun nms-reclaim-menu (menu)
  (nms-reclaim-key menu)
  (setf-text (nms-menu-label menu) nil)
  (setf-text (nms-menu-help menu) nil)
  (reclaim-gensym-list (nms-menu-items menu)) ; Just the spine
  (setf (nms-menu-items menu) nil)
  (cond ((consp (nms-menu-command menu))
         (reclaim-gensym-list (nms-menu-command menu)))
        ((partial-command-p-function (nms-menu-command menu))
         (reclaim-partial-command (nms-menu-command menu))))
  (setf (nms-menu-command menu) nil)
  (when (or (/=f (nms-menu-hmenu-high menu) 0)
            (/=f (nms-menu-hmenu-low menu) 0))
    (nms-discard-win32-handle menu))
  (when (nms-menu-options menu)
    (current-system-case
      (ab (reclaim-if-evaluation-value (nms-menu-options menu)))))
  (setf (nms-menu-options menu) nil)
  (nms-reclaim-menu-1 menu))


(def-structure (nms-menu-item (:reclaimer nms-reclaim-menu-item-1)
                              #+development (:print-function nms-print-menu-or-item))
  (nms-menu-item-handle nil)                ; User-visible handle
  (nms-menu-item-parent nil)                ; Handle of parent menu
  (nms-menu-item-label nil)                ; Wide string
  (nms-menu-item-help nil)                ; Doc string for status line.
  (nms-menu-item-flags 0)                ; Win32 item flags (mf-grayed, etc)
  (nms-menu-item-command nil)                ; UI command name, integer, gensym-list, or NIL
  (nms-menu-item-callback nil)                ; Name of choice callback procedure.
  (nms-menu-item-key nil)                ; User-supplied fixnum, symbol, string, or frame.
  (nms-menu-item-fsn nil)                ; FSN protecting key (if it is a frame)
  (nms-menu-item-position 0)                ; zero-based position in parent menu, if any.
  (nms-menu-item-icon nil)                ; Icon (16x16)
  (nms-menu-item-fg nil)                ; Foreground color
  (nms-menu-item-bg nil)                ; Background color
  (nms-menu-item-type nil)                ; NIL for button, edit-box, combo-box
  (nms-menu-item-g2pointer -1)          ; g2pointer for NMS control, if any.
  (nms-menu-item-options nil))                

(defun nms-reclaim-menu-item (item)
  (nms-reclaim-key item)
  (setf-text (nms-menu-item-label item) nil)
  (setf-text (nms-menu-item-help item) nil)
  (when (consp (nms-menu-item-command item))
    (reclaim-gensym-list (nms-menu-item-command item)))
  (when (nms-menu-item-options item)
    (current-system-case
      (ab (reclaim-if-evaluation-value (nms-menu-item-options item)))))
  (setf (nms-menu-item-options item) nil)
  (nms-reclaim-menu-item-1 item))

(defun nms-reclaim-key (menu-or-item)
  (reclaim-frame-serial-number (nms-menu-fsn menu-or-item))
  (reclaim-if-text-string (nms-menu-key menu-or-item))
  (setf (nms-menu-key menu-or-item) nil
        (nms-menu-fsn menu-or-item) nil))

#+development
(defun nms-print-menu-or-item (mot stream depth)
  (declare (ignore depth))
  (printing-random-object (mot stream)
    (format stream "~a~@[ ~a~]"
            (name-of-type-description (type-description-of mot))
            (cond ((/= 0 (logandf (nms-menu-flags mot) mf-separator))
                   '----)
                  (t
                   (or (nms-menu-label mot)
                       (if (nms-menu-p mot) (nms-menu-type mot))))))))

(defun nms-reclaim-menu-or-item (object?)
  (cond ((null object?))
        ((nms-menu-p object?)
         (nms-reclaim-menu object?))
        ((nms-menu-item-p object?)
         (nms-reclaim-menu-item object?))
        (t
         (dwarn "Junk in nms-menu-table: ~s" object?))))

(defmacro nms-fill-pointer (table)
  `(managed-svref ,table 0))

(defun nms-menu-table (gensym-window)
  (or (nms-menu-table-slot gensym-window)
      (let ((array (allocate-managed-array 256)))
        (setf (nms-menu-table-slot gensym-window) array
              (nms-fill-pointer array) 0)
        array)))

(defun nms-menu-bar-menu-p (mot)
  (and (nms-menu-p mot)
       (nms-menu-bar-menu-type (nms-menu-type mot))))

(defun nms-toolbar-p (mot)
  (and (nms-menu-p mot)
       (eq (nms-menu-type mot) 'toolbar)))

(defun nms-control-type-code (type)
  (case type
    ((menubar menu-bar) 0)
    ((popup pop-up parameter) 1)
    ((toolbar) 2)
    (t -1)))

(defun nms-menu-bar-menu-type (type)
  (memq type '(menubar menu-bar)))

(defun nms-pop-up-menu-type (type)
  (memq type '(popup pop-up parameter)))

(defun nms-pop-up-menu-p (mot)
  (and (nms-menu-p mot)
       (nms-pop-up-menu-type (nms-menu-type mot))))

(defun nms-parameter-menu-p (mot)
  (and (nms-menu-p mot)
       (eq (nms-menu-type mot) 'parameter)))

(defun nms-built-in-menu-p (mot)
  (/= 0 (logandf (nms-menu-flags mot) mf-builtin)))

#+unused
(defun nms-dynamic-menu-p (mot)
  (/= 0 (logandf (nms-menu-flags mot) mf-dynamic)))

(defun nms-wide-menu-p (mot)
  (/= 0 (logandf (nms-menu-flags mot) mf-wide)))

#+unused
(defun nms-selection-callbacks-p (mot)
  (/= 0 (logandf (nms-menu-flags mot) mf-menuselect)))

#+unused
(defun nms-unposting-callbacks-p (mot)
  (/= 0 (logandf (nms-menu-flags mot) mf-unpost)))

(defun nms-set-bit (mot mask torf)
  (setf (nms-menu-flags mot)
        (if torf
            (logiorf (nms-menu-flags mot) mask)
            (logandf (nms-menu-flags mot) (lognotf mask)))))

(defmacro do-nms-items ((mot gensym-window) &body body)
  (avoiding-variable-capture (&aux i array)
    `(loop with ,array = (nms-menu-table ,gensym-window)
           for ,i from 1 to (nms-fill-pointer ,array)
           as ,mot = (managed-svref ,array ,i)
           when ,mot
             do (progn ,@body))))

;;; The function `nms-next-handle' is careful to skip over reserved handles.

(defun nms-next-handle (gensym-window)
  (let* ((array (nms-menu-table gensym-window))
         (length (managed-array-length array))
         (handle (1+f (nms-fill-pointer array)))) ; nms-fill-pointer is max assigned handle.
    (cond ((<f handle nms-handle-gap-low)
           handle)
          ((<=f handle nms-handle-gap-high)
           (1+f nms-handle-gap-high))
          ((<=f handle nms-maximum-permitted-handle)
           handle)
          (t
           ;; TODO: avoid this linear search.
           (or (loop for i from 1 below (minf length nms-handle-gap-low)
                     when (null (managed-svref array i))
                       return i)
               (loop for i from (1+f nms-handle-gap-high) below length
                     when (null (managed-svref array i))
                       return i))))))

;;; The function `nms-allocate-handle' returns an unused handle (a small
;;; positive integer).  Optionally, caller can provide a preassigned handle and
;;; we will make sure the array length and fill-pointer accomodate it.  Returns
;;; NIL if we run out of handles.

(defun nms-allocate-handle (gensym-window &optional handle?)
  (let ((handle (or handle? (nms-next-handle gensym-window))))
    (cond ((or (null handle)
               (>f handle nms-maximum-permitted-handle))
           (dwarn "Maximum number of NMS handles exceeded (~d)." handle)
           nil)
          (t
           (let* ((array (nms-menu-table gensym-window))
                  (nslots (1-f (managed-array-length array))))

             ;; Grow array if chosen handle is beyond the end.
             (when (>f handle nslots)
               (let ((new-length (*f 2 (managed-array-length array))))
                 (setf array (adjust-managed-array array new-length)
                       (nms-menu-table-slot gensym-window) array)))

             ;; Update fill-pointer to be max assigned handle.
             (setf (nms-fill-pointer array) (maxf (nms-fill-pointer array) handle))

             #+development
             (when (managed-svref array handle)
               (dwarn "nms-allocate-handle: something is already at ~d: ~s"
                      handle (managed-svref array handle)))

           handle)))))

;;; The function `nms-deallocate-handle' deallocates a menu or item handle.

(defun nms-deallocate-handle (gensym-window handle?)
  (let ((table? (nms-menu-table-slot gensym-window)))
    (when (and table? handle?)
      ;; TODO: reset fill-pointer if possible.
      (setf (managed-svref table? handle?) nil))))

;; TODO: Ought to use a hash table, at least for allocation, if not lookup.


;;; The function `nms-lookup-handle' returns the object, if any, referenced by
;;; handle.

(defun nms-lookup-handle (gensym-window handle?)
  (when (nms-menu-table-slot gensym-window) ; Don't create a table
    (let* ((array (nms-menu-table gensym-window))
           (count (nms-fill-pointer array)))
      (cond ((null handle?) nil)
            ((<=f handle? 0) nil)
            ((>f handle? count) nil)
            (t
             (managed-svref array handle?))))))


(defun nms-record-win32-handle (nms-menu hmenu-high hmenu-low)
  (let ((key (gensym-cons hmenu-high hmenu-low)))
    (setf (nms-menu-hmenu-high nms-menu) hmenu-high
          (nms-menu-hmenu-low nms-menu) hmenu-low
          (get-nms-menu-for-hmenu key nms-menu-hash-table) nms-menu)
    nms-menu))

(defun nms-discard-win32-handle (nms-menu)
  (let ((key (gensym-cons (nms-menu-hmenu-high nms-menu)
                          (nms-menu-hmenu-low nms-menu))))
    (when (get-nms-menu-for-hmenu key nms-menu-hash-table)
      (delete-nms-menu-for-hmenu key nms-menu-hash-table))
    (setf (nms-menu-hmenu-high nms-menu) 0
          (nms-menu-hmenu-low nms-menu) 0)
    (reclaim-gensym-cons key)))

(defun find-nms-menu-for-hmenu (hmenu-high hmenu-low)
  (let* ((key (gensym-cons hmenu-high hmenu-low))
         (menu? (get-nms-menu-for-hmenu key nms-menu-hash-table)))
    (reclaim-gensym-cons key)
    (unless menu?
      (dwarn "No NMS-MENU found for HMENU ~x ~x~%" hmenu-high hmenu-low))
    menu?))


(defun stock-command-id-p (id)
  (<f (-f nms-stock-command-min-id 1) id nms-no-choice))

(defun nms-menu-handle-to-id (handle)
  (+f handle nms-no-choice))


;;; The function `nms-menu-id-to-handle' returns the NMS menu-item with given
;;; ID.  Normally, this is just a subtract since, normally, the id is simply
;;; (+ handle nms-no-choice).  This differs for stock commands, which have a
;;; predefined ID unrelated to their handle.  Stock command IDs are in a
;;; different range so that we can distinguish the two cases.

(defun nms-menu-id-to-handle (gensym-window id)
  (cond ((stock-command-id-p id)
         (let ((array? (nms-menu-table-slot gensym-window)))
           (or
             (when array?
               (block search
                 ;; TODO: Avoid this linear search.
                 (loop for i from 1 to (nms-fill-pointer array?)
                       as item = (managed-svref array? i)
                       doing
                   (when (and (nms-menu-item-p item)
                              (eql (nms-menu-item-command item) id))
                     (return-from search (nms-menu-item-handle item))))))
             0)))
        (t
         (-f id nms-no-choice))))


;;; The function `nms-menu-item-id' returns the unique Win32 command ID for this
;;; menu item.  It is unique over all menu items created for a window.  The ID
;;; is always >= nms-no-choice+1.  We reserve nms-no-choice for the "no choice"
;;; choice.

(defun nms-menu-item-id (item)
  (cond ((fixnump (nms-menu-item-command item))        ; Stock command has special ID.
         (nms-menu-item-command item))
        (t
         (nms-menu-handle-to-id (nms-menu-item-handle item)))))


(defun nms-lookup-id (gensym-window id)
  (nms-lookup-handle gensym-window (nms-menu-id-to-handle gensym-window id)))

(defun nms-menu-item-command-id (item)
  (cond ((fixnump (nms-menu-item-command item))        ; Stock command has special ID.
         (nms-menu-item-command item))
        (t
         nil)))                                ; FIXME?

(defun nms-allocate-menu (gensym-window type &optional handle?)
  (let ((handle? (nms-allocate-handle gensym-window handle?)))
    (when handle?
      (let ((nms-menu (make-nms-menu))
            (array (nms-menu-table gensym-window)))
        (setf (managed-svref array handle?) nms-menu)
        (setf (nms-menu-handle nms-menu) handle?
              (nms-menu-type nms-menu) type)
        (when nms-constructing-built-in-menus-p
          (setf (nms-menu-flags nms-menu) mf-builtin))
        nms-menu))))

(defun nms-allocate-menu-item (gensym-window &optional handle?)
  (let ((handle? (nms-allocate-handle gensym-window handle?)))
    (when handle?
      (let ((nms-menu-item (make-nms-menu-item))
            (array (nms-menu-table gensym-window)))
        (setf (managed-svref array handle?) nms-menu-item)
        (setf (nms-menu-item-handle nms-menu-item) handle?)
        (when nms-constructing-built-in-menus-p
          (setf (nms-menu-item-flags nms-menu-item) mf-builtin))
        nms-menu-item))))



;;; The function `reclaim-contents-of-nms-menu-table' reclaims all of the
;;; nms-menu and nms-menu-item objects in the table, and resets the fill pointer
;;; to 0.

(defun reclaim-contents-of-nms-menu-table (table)
  (loop for i from 1 to (nms-fill-pointer table)
        as object? = (managed-svref table i)
        doing
    (nms-reclaim-menu-or-item object?)
    (setf (managed-svref table i) nil))
  (setf (nms-fill-pointer table) 0)
  table)


;;; The function `nms-supported-on-gensym-window-p' is true if NMS in general is
;;; supported on the given window. This means it is safe to send the messages,
;;; although possibly not all NMS features work (eg, popup menus but not menubar
;;; menus). The UI must not be classic, etc.

(defun nms-supported-on-gensym-window-p (gensym-window)
  (and (icp-window-p gensym-window)
       (current-window-supports-nms-menus gensym-window)
       (native-pop-up-menus-p gensym-window)))

;;; The function `nms-menu-bars-supported-p' is true if NMS menu bars are
;;; supported on the given window.

(defun nms-menu-bars-supported-p (gensym-window)
  (native-menu-bar-p gensym-window))

(defun nms-popup-menus-supported-p (gensym-window)
  (nms-supported-on-gensym-window-p gensym-window))

(defun nms-push-item (menu item)
  (setf (nms-menu-item-parent item) (nms-menu-handle menu)
        (nms-menu-item-position item) (nms-menu-item-count menu))
  (gensym-push item (nms-menu-items menu))
  (incff (nms-menu-item-count menu)))

(defun nms-delete-item (menu item)
  (setf (nms-menu-items menu) (delete-gensym-element item (nms-menu-items menu)))
  (nms-renumber-items menu)
  (setf (nms-menu-item-parent item) nil)
  item)

;;; The function `nms-remove-menu-item-locally' removes item from menu, if it is
;;; present. Item is not reclaimed.

(defun nms-remove-menu-item-locally (gensym-window menu item)
  (declare (ignore gensym-window))
  (nms-delete-item menu item)
  (let ((g2pointer? (nms-menu-g2pointer menu))
        (item-id (cond ((nms-menu-p item)
                        (nms-menu-g2pointer item))
                       (t
                        (nms-menu-item-id item)))))
    (when g2pointer?
      (nms-c-remove-menu-item g2pointer? item-id))))


(defun nms-renumber-items (menu)
  (let ((count (length (nms-menu-items menu))))
    (setf (nms-menu-item-count menu) count)
    (loop for item in (nms-menu-items menu)
          as position from (-f count 1) by -1
          doing
      (setf (nms-menu-item-position item) position))))


;;; The function `nms-delete-menu-locally' reclaims the nms-menu structure menu
;;; and all of its items, and removes it from its parent menu, if any.
;;; Optionally, we recurse to submenus of menu. The deletion of actual native
;;; HMENU handles is done elsewhere. Optionally, the topmost-level menu is
;;; preserved, although now with no items.

(defun nms-delete-menu-locally (gensym-window menu recurse-p &optional keep-toplevel-menu-p)
  (let ((parent? (nms-lookup-handle gensym-window (nms-menu-parent menu))))
    ;; TODO: Permit more than one parent.
    (when (and parent? (not recurse-p))
      (nms-remove-menu-item-locally gensym-window parent? menu)
      (setf (nms-menu-parent menu) nil))

    (loop for item in (nms-menu-items menu) doing
      (cond ((nms-menu-item-p item)
             (nms-deallocate-handle gensym-window (nms-menu-item-handle item))
             (nms-reclaim-menu-item item))
            ((nms-menu-p item)
             (when recurse-p
               (nms-delete-menu-locally gensym-window item recurse-p))
             (setf (nms-menu-item-parent item) nil))
            (t
             (dwarn "Junk in nms-menu-items for ~s" menu))))

    (reclaim-gensym-list (nms-menu-items menu))
    (setf (nms-menu-items menu) nil
          (nms-menu-item-count menu) 0)
    (unless keep-toplevel-menu-p
      (nms-note-menu-deletion gensym-window (nms-menu-handle menu))
      (nms-deallocate-handle gensym-window (nms-menu-handle menu))
      (nms-reclaim-menu menu))))



;;; The function `nms-reset-locally' runs on both the G2 and TW sides. On each
;;; side it reclaims nms-menu and nms-menu-item structures and reclaims
;;; handles. Only on the TW side, it also calls nms-c-delete-menu to actually
;;; delete the Win32 HMENU objects.

;;; A hard-reset deletes all menus and items. A soft reset deletes only menus
;;; and items created by the user at KB level (via the NMS system procedures).

(defun nms-reset-locally (gensym-window hard-reset-p)
  (if hard-reset-p
      (nms-hard-reset-locally gensym-window)
      (nms-soft-reset-locally gensym-window)))


;;; The function `nms-hard-reset-locally' deletes ALL menus and items, both
;;; built-in ones and those created by the user at KB level, for the given
;;; window.  The intent is bring NMS back to the state it had at G2 startup.
;;; Used only by KB Clear.

;;; Since we are deleting all menus and items, we gain some efficiency and can
;;; reset the table of handles so that it begins counting again from 1 and has
;;; no holes.

;;; We have to be careful to call Win32 DestroyMenu only on top-level menus,
;;; since that function recurses to submenus.

(defun nms-hard-reset-locally (gensym-window)
  (let ((table? (nms-menu-table-slot gensym-window)))
    (when table?
      (loop for i from 1 to (nms-fill-pointer table?)
            as object? = (managed-svref table? i)
            doing
        (when (and object? (nms-menu-p object?)
                   ;; If has no parent, safe to destroy it.
                   (null (nms-menu-parent object?)))
          (nms-delete-native-menu gensym-window object? t)))
      (reclaim-contents-of-nms-menu-table table?))
    (nms-note-menu-deletion gensym-window t)))



;;; The function `nms-soft-reset-locally' deletes only user-created menus and
;;; items. It doesn't reset the fill-pointer in the table of handles, so the
;;; table may still contain holes.

(defun nms-soft-reset-locally (gensym-window)
  (let ((table? (nms-menu-table-slot gensym-window)))
    (when table?
      (loop for i from 1 to (nms-fill-pointer table?)
            as object? = (managed-svref table? i)
            doing
        (when (and object? (nms-menu-p object?)
                   (not (nms-built-in-menu-p object?))
                   ;; If has no parent, safe to destroy it.
                   (null (nms-menu-parent object?)))
          (nms-delete-menu-locally gensym-window object? t)
          (nms-delete-native-menu gensym-window object? t))))))


;;; The function `nms-delete-native-menu' deletes the Win32 HMENU object
;;; associated with menu, if any, or just its items.

(defun nms-delete-native-menu (gensym-window menu recurse-p &optional keep-toplevel-menu-p)
  (let ((g2pointer (nms-menu-g2pointer menu)))
    (cond ((<f g2pointer 0))                ; Always true on G2 side.
          (keep-toplevel-menu-p
           (nms-c-delete-menu-items (native-window? gensym-window) g2pointer))
          (t
           (nms-c-delete-menu (native-window? gensym-window) g2pointer (if recurse-p 1 0))
           (nms-discard-win32-handle menu)
           (setf (nms-menu-g2pointer menu) -1)))))


;;;; NMS ICP Messages


;;; The icp-message-type `nms-create-menu' creates a menu and assigns it the
;;; supplied handle.  Runs on the TW side.

(def-icp-message-type nms-create-menu
    ((gensym-window window)
     (fixnum menu-handle)                ; Pre-assigned menu handle
     (symbol type)                        ; menu-bar, popup, etc.
     (fixnum flags))                        ; mf-builtin
  (let* ((hmenu (allocate-byte-vector-16 2))
         (g2pointer (nms-c-create-menu (if (memq type '(popup pop-up parameter)) 1 0)
                                       hmenu)))
    (when (>=f g2pointer 0)
      (let ((menu (nms-allocate-menu window type menu-handle)))
        (setf (nms-menu-g2pointer menu) g2pointer
              (nms-menu-item-flags menu) flags)
        (nms-record-win32-handle menu (byte-vector-16-aref hmenu 0)
                                 (byte-vector-16-aref hmenu 1))))
    (reclaim-byte-vector-16 hmenu)))

;;; The icp-message-type `nms-append-menu-item' adds an item to the end of a menu.

(def-icp-message-type nms-append-menu-item
    ((gensym-window window)
     (fixnum menu-handle)
     (fixnum item-or-menu-handle)        ; Preexisting submenu-handle or new item-handle
     (wide-string label)
     (wide-string help)
     (fixnum flags)
     (unsigned-integer? id?))                ; Stock command ID or NIL
  (nms-append-internal window menu-handle item-or-menu-handle label help flags id? nil nil))


;;; The icp-message-type `nms-append-special' adds a special item to a menu. For
;;; now, the only special item is one with custom fg/bg colors.

(def-icp-message-type nms-append-special
    ((gensym-window window)
     (fixnum menu-handle)
     (fixnum item-or-menu-handle)        ; Preexisting submenu-handle or new item-handle
     (wide-string label)
     (wide-string help)
     (fixnum flags)
     (unsigned-integer? id?)                ; Stock command ID or NIL
     (fixnum fg)
     (fixnum bg))
  (nms-append-internal window menu-handle item-or-menu-handle label help flags id?
                       (if (eql fg -1) nil fg)
                       (if (eql bg -1) nil bg)))

;; Runs on the TW side.
(defun nms-append-internal (window menu-handle item-or-menu-handle label help
                                   flags id? fg? bg?)
  (let* ((menu? (nms-lookup-handle window menu-handle))
         (submenu? (nms-lookup-handle window item-or-menu-handle))
         (mot (or submenu? (nms-allocate-menu-item window item-or-menu-handle))))
    #+development (or menu? (dwarn "nms-append-menu: menu-handle ~d not found" menu-handle))
    (when menu?
      ;; I think we only really need to cache the help strings on the TW side.
      (setf (nms-menu-item-label mot) label ; Need to copy?
            (nms-menu-item-flags mot) flags
            (nms-menu-item-help mot) help
            (nms-menu-item-command mot) id? ; Holds stock command ID on TW, or NIL.
            (nms-menu-item-fg mot) fg?
            (nms-menu-item-bg mot) bg?)
      (nms-push-item menu? mot)
      (nms-c-append-menu (nms-menu-g2pointer menu?)
                         (logandf flags mf-win32-flags-mask)
                         (nms-menu-item-id mot)
                         (if submenu? (nms-menu-g2pointer submenu?) -1)
                         (if (nms-wide-menu-p menu?) 1 0)
                         label
                         (or fg? -1)
                         (or bg? -1)))))

;;; The icp-message-type `nms-delete-menu' deletes the given menu's items,
;;; optionally all of its submenus, and normally the menu itself. It both
;;; reclaims local NMS structures and destroys native menu HMENU handles.  If
;;; the menu is the current menu bar, then the menu bar is reset to the default.
;;; If the menu is currently an active popup, then the popup is dismissed
;;; (TODO).

(def-icp-message-type nms-delete-menu
    ((gensym-window window)
     (fixnum menu-handle)
     (fixnum options))                        ; bit1=keep-toplevel-menu-p, bit0=recurse
  (let ((menu? (nms-lookup-handle window menu-handle))
        (recurse-p (logbitpf 0 options))
        (keep-toplevel-menu-p (logbitpf 1 options)))
    (when menu?
      (nms-delete-menu-locally window menu? recurse-p keep-toplevel-menu-p)
      (nms-delete-native-menu window menu? recurse-p keep-toplevel-menu-p))))

(def-icp-message-type nms-reset
    ((gensym-window window)
     (fixnum options))                        ; bit0=hard-reset-p
  (let ((hard-reset-p (logbitpf 0 options)))
    (nms-reset-locally window hard-reset-p)))



;;; The icp-message-type `nms-dismiss' pops-down any popup menus on window.

(def-icp-message-type nms-dismiss
    ((gensym-window window))
  (nms-c-dismiss (native-window? window)))


(def-icp-message-type nms-check-menu-item
  ((gensym-window window)
   (fixnum menu-handle)
   (fixnum item)                        ; Command ID
   (fixnum flags))                        ; mf-checked or 0
  (let ((menu? (nms-lookup-handle window menu-handle)))
    (when menu?
      (nms-c-check-menu-item (nms-menu-g2pointer menu?) item flags))))

(def-icp-message-type nms-check-radio-item
  ((gensym-window window)
   (fixnum menu-handle)
   (fixnum first)                        ; Command IDs
   (fixnum last)
   (fixnum check)
   (fixnum flags))
  (let ((menu? (nms-lookup-handle window menu-handle)))
    (when menu?
      ;; TODO: Pass item ID instead of position (or both, for TW and TWNG)
      (nms-c-check-radio-item (nms-menu-g2pointer menu?) first last check flags))))

(def-icp-message-type nms-enable-menu-item
  ((gensym-window window)
   (fixnum menu-handle)
   (fixnum item)                        ; Command ID or position
   (fixnum flags))                        ; mf-grayed or mf-disabled or 0
  (let ((menu? (nms-lookup-handle window menu-handle)))
    (when menu?
      ;; TODO: Pass item ID instead of position (or both, for TW and TWNG)
      (nms-c-enable-menu-item (nms-menu-g2pointer menu?) item flags))))

(def-icp-message-type nms-set-menu-flags
  ((gensym-window window)
   (fixnum menu-or-item-handle)
   (fixnum flags)
   (fixnum mask))
  (let ((menu-or-item? (nms-lookup-handle window menu-or-item-handle)))
    (when menu-or-item?
      (setf (nms-menu-flags menu-or-item?)
            (logiorf (logandf (nms-menu-flags menu-or-item?)
                              (lognotf mask))
                     (logandf flags mask))))))


;;; The icp-message-type `nms-modify-menu-item' is a catch-all message for
;;; setting a bunch of random properties of a menu item at once.

(def-icp-message-type nms-modify-menu-item
    ((gensym-window window)
     (fixnum menu-handle)
     (fixnum item-handle)
     (icp-tree plist))                        ; label, icon, foreground, background, help
  (let ((menu? (nms-lookup-handle window menu-handle))
        (item? (nms-lookup-handle window item-handle)))
    (when (and menu? item?)
      (let ((help? (getf plist 'help))
            (label? (getf plist 'label))
            (fg? (getf plist 'foreground))
            (bg? (getf plist 'background))
            (icon? (getf plist 'icon)))
        (when help?
          (setf-text (nms-menu-item-help item?) (copy-text-string help?))
          (nms-c-set-help (nms-menu-g2pointer menu?) ; XTP wants help string explicitly.
                          (nms-menu-item-id item?)
                          (nms-menu-item-help item?)))
        (when label?
          (setf-text (nms-menu-item-label item?) (copy-text-string label?)))
        (when fg?
          (setf (nms-menu-item-fg item?) (if (eql fg? -1) nil fg?)))
        (when bg?
          (setf (nms-menu-item-bg item?) (if (eql bg? -1) nil bg?)))
        (when icon?
          (setf (nms-menu-item-icon item?) (if (eql icon? -1) nil icon?)))
        (when (or label? fg? bg? icon?)
          (nms-set-bit item? mf-wide (nms-wide-menu-p menu?))
          (nms-c-modify-menu-item (nms-menu-g2pointer menu?)
                                  (nms-menu-item-id item?)
                                  (nms-menu-item-position item?)
                                  (if (nms-wide-menu-p menu?) 1 0)
                                  (if label? 1 0)
                                  (nms-menu-item-label item?)
                                  (or (nms-menu-item-fg item?) -1)
                                  (or (nms-menu-item-bg item?) -1)
                                  (or (nms-menu-item-icon item?) -1))
          ;; Menu's geometry potentially changing?
          (when (or (and (nms-wide-menu-p menu?) (null (nms-menu-item-icon item?)))
                    (and (not (nms-wide-menu-p menu?)) (nms-menu-item-icon item?)))
            (nms-ensure-consistent-menu-geometry menu?)))))
    (reclaim-icp-tree-with-text-strings plist)))


;;; The function `nms-ensure-consistent-menu-geometry' ensures either all items
;;; in the menu are wide, or all are not. A given item is wide iff it has an
;;; icon. Exception: menubars never need to become wide.

(defun nms-ensure-consistent-menu-geometry (menu)
  (unless (or (nms-menu-bar-menu-p menu)
              (=f (nms-c-width-maintenance) 0))        ; Width adjustments unnecessary (eg, codejock)
    (let ((wide-p (loop for item in (nms-menu-items menu)
                        thereis (nms-menu-item-icon item))))
      (nms-set-bit menu mf-wide wide-p)
      (loop for item in (nms-menu-items menu) doing
        (nms-set-bit item mf-wide wide-p)
        (nms-c-modify-menu-item (nms-menu-g2pointer menu)
                                (nms-menu-item-id item)
                                (nms-menu-item-position item)
                                (if wide-p 1 0)            ; Change only the wide bit.
                                0                           ; new-label-p
                                (nms-menu-item-label item)
                                (or (nms-menu-item-fg item) -1)
                                (or (nms-menu-item-bg item) -1)
                                (or (nms-menu-item-icon item) -1))))))

(defun nms-revert-to-unconnected-menu-bar (gensym-window)
  (when (native-window? gensym-window)
    (nms-c-set-menu (native-window? gensym-window) -1 0)))

(defun nms-hide-menu-bar (gensym-window)
  (when (native-window? gensym-window)
    (nms-c-set-menu (native-window? gensym-window) -2 -1)))


;;; The icp-message-type `nms-set-menu-bar' sets the menu bar of window to be
;;; menu.  If menu-handle is 0, reverts to the default (an unconnected TW
;;; menu bar).  If menu-handle is -1, it removes the menu bar entirely.

(def-icp-message-type nms-set-menu-bar
    ((gensym-window window)
     (fixnum menu-handle))
  (cond ((=f menu-handle 0)                ; Zero means revert to default
         (nms-revert-to-unconnected-menu-bar window))
        ((=f menu-handle -1)                ; -1 means hide menu bar
         (nms-hide-menu-bar window))
        (t
         (let ((menu? (nms-lookup-handle window menu-handle)))
           (when menu?
             (let ((g2pointer (nms-menu-g2pointer menu?)))
               (when (>=f g2pointer 0)
                 (nms-c-set-menu (native-window? window) g2pointer menu-handle))))))))

;; TODO: There are at least three default menu bars: the one TW has before it
;; connects, the standard G2 menu bar, and the empty menu bar.


;;; The icp-message-type `nms-pop-up-menu' pops up the menu at x,y in window
;;; coordinates.

(def-icp-message-type nms-pop-up-menu
    ((gensym-window gensym-window)
     (fixnum menu-handle)
     (fixnum x)
     (fixnum y))
  (with-deferred-execution-in-tw ()
    (nms-pop-up-menu-deferred gensym-window (gensym-window-serial-number gensym-window)
                             menu-handle x y)))

(defun nms-pop-up-menu-deferred (gensym-window serial menu-handle x y)
  (when (gensym-window-has-not-been-reprocessed-p gensym-window serial)
    (let ((menu? (nms-lookup-handle gensym-window menu-handle)))
      ;; FIXME: The menu handle could have been deleted and resuscitated here.
      ;; For now, just don't worry about. Effect would be to pop-up the wrong
      ;; menu.
      (when menu?
        (let ((menu-g2pointer (nms-menu-g2pointer menu?)))
          (when (>=f menu-g2pointer 0)
            (nms-c-pop-up-menu (native-window? gensym-window)
                              menu-handle menu-g2pointer x y)))))))


;;; The icp-message-type `nms-enable-items' is a compact way to change the
;;; mf-gray bit in a bunch of menu items with one ICP message.

(def-icp-message-type nms-enable-items
    ((gensym-window gensym-window)
     (list-of-unsigned-integers values)) ; Packed handle[15] flag[1] into 16 bits
  (loop for value in values
        as flag = (logandf value 1)        ; 1=gray, 0=enable
        as handle = (logandf (ashf value -1) 32767)
        as item? = (nms-lookup-handle gensym-window handle)
        doing
    (when item?
      (let ((menu? (nms-lookup-handle gensym-window (nms-menu-item-parent item?))))
        (when menu?
          (nms-c-enable-menu-item (nms-menu-g2pointer menu?)
                                  (nms-menu-item-position item?)
                                  ;; Do we need to add mf-disabled?
                                  (logiorf mf-byposition flag))))))
  ;; Finally, clear a flag to let the C code know that we are done.  TW is
  ;; normally in a modal event loop when nms-enable-items is received, and will
  ;; exit the loop when the flag becomes 0.
  (nms-c-set-flag 0))








;;;; NMS C Functions



;;; The gensym-c-function `nms-c-create-menu' maps to either Win32 CreateMenu or
;;; CreatePopupMenu.  Returns a G2pointer as an integer, as well as the 32-bit
;;; Windows menu handle (HMENU) as a pair of 16-bit integers.

(def-gensym-c-function nms-c-create-menu
    (:fixnum-int "g2ext_nms_create_menu")
  ((:fixnum-int popup-p)
   (:wide-string hmenu)))


;;; The gensym-c-function `nms-c-delete-menu' maps to Win32 DestroyMenu, which
;;; destroys the menu and optionally and all of its submenus, recursively.
;;; Optionally, the top-level menu is not deleted (only its items).

(def-gensym-c-function nms-c-delete-menu
    (:fixnum-int "g2ext_nms_destroy_menu")
  ((:pointer window)
   (:pointer menu)
   (:fixnum-int recurse-p)))


;;; The gensym-c-function `nms-c-delete-menu-items' removes all of menu's items,
;;; recuring to submenus as needed, leaving menu valid, but an empty husk with
;;; no items.

(def-gensym-c-function nms-c-delete-menu-items
    (:fixnum-int "g2ext_nms_delete_menu_items")
  ((:pointer window)
   (:pointer menu)))


(def-gensym-c-function nms-c-dismiss
    (:fixnum-int "g2ext_nms_dismiss")
  ((:pointer window)))


;;; The gensym-c-function `nms-c-append-menu' maps to Win32 AppendMenu.

(def-gensym-c-function nms-c-append-menu
    (:fixnum-int "g2ext_nms_append_menu")
  ((:pointer menu)
   (:fixnum-int flags)                        ; mf-break, etc
   (:fixnum-int id)                        ; ID
   (:fixnum-int submenu)                ; submenu_index (-1 if none)
   (:fixnum-int wide-p)                        ; Use wide format
   (:wide-string label)
   (:fixnum-int fg)                        ; fg/bg colors. Later: icon, etc.
   (:fixnum-int bg)))


(def-gensym-c-function nms-c-check-menu-item
    (:fixnum-int "g2ext_nms_check_menu_item")
  ((:pointer menu)
   (:fixnum-int item)
   (:fixnum-int flags)))

(def-gensym-c-function nms-c-check-radio-item
    (:fixnum-int "g2ext_nms_check_radio_item")
  ((:pointer menu)
   (:fixnum-int first)
   (:fixnum-int last)
   (:fixnum-int check)
   (:fixnum-int flags)))

(def-gensym-c-function nms-c-enable-menu-item
    (:fixnum-int "g2ext_nms_enable_menu_item")
  ((:pointer menu)
   (:fixnum-int item)
   (:fixnum-int flags)))

(def-gensym-c-function nms-c-remove-menu-item
    (:fixnum-int "g2ext_nms_remove_menu_item")
  ((:pointer menu)
   (:fixnum-int item)))

;;; The gensym-c-function `nms-c-width-maintenance' returns true (1) if menus on
;;; the current platform require "width maintenance", ie, whether the wide-p
;;; argument to nms-c-width-maintenance-p does anything.

(def-gensym-c-function nms-c-width-maintenance
    (:fixnum-int "g2ext_nms_width_maintainance_p")
  ())

;;; The gensym-c-function `nms-c-modify-menu-item' changes an item's label,
;;; which may be include a TAB and a shortcut key string.  Maybe other stuff
;;; later.

(def-gensym-c-function nms-c-modify-menu-item
    (:fixnum-int "g2ext_nms_modify_menu_item")
  ((:pointer menu)
   (:fixnum-int id)                        ; ID of the item
   (:fixnum-int pos)                        ; Position of item in menu.
   (:fixnum-int wide-p)                        ; Use wide geometry.
   (:fixnum-int new-label-p)
   (:wide-string new-label)
   (:fixnum-int new-fg)
   (:fixnum-int new-bg)
   (:fixnum-int new-icon)))


;;; The gensym-c-function `nms-c-set-menu' makes menu be the menu bar.  Maps to
;;; Win32 SetMenu.  If menu is -1, reverts to default menu bar. If -2, removes
;;; the menu bar entirely.

(def-gensym-c-function nms-c-set-menu
    (:fixnum-int "g2ext_nms_set_menu")
  ((:pointer window)
   (:pointer menu)
   (:fixnum-int nms-menu-handle)))


;;; The gensym-c-function `nms-c-pop-up-menu' pops up a menu at x,y in window,
;;; tracks it modally, and enqueues a MENU-CHOICE control event with the ID of
;;; the chosen item or 0 for none.

(def-gensym-c-function nms-c-pop-up-menu
    (:fixnum-int "g2ext_nms_pop_up_menu")
  ((:pointer window)
   (:pointer menu-handle)                ; The NMS menu handle
   (:pointer menu)                        ; The g2pointer to the Win32 HMENU
   (:fixnum-int x)
   (:fixnum-int y)))

(def-gensym-c-function nms-c-set-help
    (:fixnum-int "g2ext_nms_set_help")
  ((:pointer menu)
   (:fixnum-int id)                        ; ID of the item
   (:wide-string string)))

;;; The lisp-api-function `nms-fetch-help-string' looks up the (wide) help
;;; string, if any, for the NMS item with the given unique ID, and returns it to
;;; C by calling nms-fetch-help-string-result with the buffer.  Done this way
;;; since I don't know how to return strings from lisp to C any other way. -fmw,
;;; 3/29/02

(eval-when (:compile-toplevel)
  (defmacro nms-fetch-help-string-macro ()
    `(let* ((gensym-window? (get-gensym-window-of-native-window native-window))
            (string (or (and gensym-window?
                             (let ((item? (nms-lookup-id gensym-window? item-id)))
                               (when item?
                                 (nms-menu-item-help item?))))
                        #w"")))
       (nms-c-fetch-help-string-result string)
       (wide-string-length string))))

#+chestnut-3
(def-lisp-api-function (nms-fetch-help-string (:return-type :fixnum))
    ((native-window :fixnum)                ; g2pointer of gensym-window
     (item-id :fixnum))
  (nms-fetch-help-string-macro))

#+(and sbcl (not chestnut-3))
(progn
  (sb-alien:define-alien-routine nms-fetch-help-string-init-call-handle
      sb-alien:void
    (ptr (function sb-alien:int sb-alien:int sb-alien:int)))

  (sb-alien::define-alien-callback nms-fetch-help-string
      sb-alien:int
      ((native-window sb-alien:int)
       (item-id sb-alien:int))
    (nms-fetch-help-string-macro)))

#+(and lispworks (not chestnut-3))
(progn
  (fli:define-foreign-function (nms-fetch-help-string-init-call-handle
                                "nms_fetch_help_string_init_call_handle")
      ((ptr :pointer))
    :result-type :void)

  (fli:define-foreign-callable ("nms_fetch_help_string" :result-type :long)
      ((native-window :long)
       (item-id :long))
    (nms-fetch-help-string-macro))

  (defvar nms-fetch-help-string
    (fli:make-pointer :symbol-name "nms_fetch_help_string")))

#+(and clozure (not chestnut-3))
(progn
  (defun nms-fetch-help-string-init-call-handle (handler)
    (declare (type ccl:macptr handler))
    (ccl:external-call "nms_fetch_help_string_init_call_handle"
                       :address handler
                       :void))

  (ccl:defcallback nms-fetch-help-string (:signed-fullword native-window
                                          :signed-fullword item-id
                                          :signed-fullword)
    (nms-fetch-help-string-macro)))

;;; The gensym-c-function `nms-c-fetch-help-string-result' is called only by
;;; nms-fetch-help-string to supply the result string to the C code.

(def-gensym-c-function nms-c-fetch-help-string-result
    (:fixnum-int "g2ext_nms_fetch_help_string_result")
  ((:wide-string result)))


;;; The gensym-c-function `nms-c-set-flag' sets a global integer flag and
;;; returns the old value.  The C code uses the flag as a sign that a particular
;;; ICP message has been received and processed.

(def-gensym-c-function nms-c-set-flag
    (:fixnum-int "g2ext_nms_set_flag")
  ((:fixnum-int flag)))


;;; The lisp-api-function `nms-handle-if-flag-bit' returns the NMS handle of a
;;; menu, given its Win2 HMENU handle, if the NMS menu has the given flag bit
;;; set., else 0.  Called from the WM_INITMENUPOPUP, WM_UNINITMENUPOPUP, and
;;; WM_MENUSELECT handlers in menus.c.

(eval-when (:compile-toplevel)
  (defmacro nms-handle-if-flag-bit-macro ()
    `(let ((nms-menu? (find-nms-menu-for-hmenu hmenu-high hmenu-low)))
       (if (and nms-menu? (/= 0 (logandf (nms-menu-flags nms-menu?) flag)))
           (nms-menu-handle nms-menu?)
         0))))

#+chestnut-3
(def-lisp-api-function (nms-handle-if-flag-bit (:return-type :fixnum))
    ((hmenu-high :fixnum)
     (hmenu-low :fixnum)
     (flag :fixnum))
  (nms-handle-if-flag-bit-macro))

#+(and sbcl (not chestnut-3))
(progn
  (sb-alien:define-alien-routine nms-handle-if-flag-bit-init-call-handle
      sb-alien:void
    (ptr (function sb-alien:int sb-alien:int sb-alien:int sb-alien:int)))
  
  (sb-alien::define-alien-callback nms-handle-if-flag-bit
      sb-alien:int
      ((hmenu-high sb-alien:int)
       (hmenu-low sb-alien:int)
       (flag sb-alien:int))
    (nms-handle-if-flag-bit-macro)))

#+(and lispworks (not chestnut-3))
(progn
  (fli:define-foreign-function (nms-handle-if-flag-bit-init-call-handle
                                "nms_handle_if_flag_bit_init_call_handle")
      ((ptr :pointer))
    :result-type :void)

  (fli:define-foreign-callable ("nms_handle_if_flag_bit" :result-type :long)
      ((hmenu-high :long)
       (hmenu-low :long)
       (flag :long))
    (nms-handle-if-flag-bit-macro))

  (defvar nms-handle-if-flag-bit
    (fli:make-pointer :symbol-name "nms_handle_if_flag_bit")))

#+(and clozure (not chestnut-3))
(progn
  (defun nms-handle-if-flag-bit-init-call-handle (handler)
    (declare (type ccl:macptr handler))
    (ccl:external-call "nms_handle_if_flag_bit_init_call_handle"
                       :address handler
                       :void))

  (ccl:defcallback nms-handle-if-flag-bit (:signed-fullword hmenu-high
                                           :signed-fullword hmenu-low
                                           :signed-fullword flag
                                           :signed-fullword)
    (nms-handle-if-flag-bit-macro)))

;;; The lisp-api-function `nms-id-for-menu' returns the command ID for an HMENU,
;;; or 0 if unknown. Windows stored command IDs for menu items, but not menus
;;; themselves, so the C code looks them up here.

(eval-when (:compile-toplevel)
  (defmacro nms-id-for-menu-macro ()
    `(let ((nms-menu? (find-nms-menu-for-hmenu hmenu-high hmenu-low)))
       (if nms-menu? (nms-menu-item-id nms-menu?) 0))))

#+chestnut-3
(def-lisp-api-function (nms-id-for-menu (:return-type :fixnum))
    ((hmenu-high :fixnum)
     (hmenu-low :fixnum))
  (nms-id-for-menu-macro))

#+(and sbcl (not chestnut-3))
(progn
  (sb-alien:define-alien-routine nms-id-for-menu-init-call-handle
      sb-alien:void
    (ptr (function sb-alien:int sb-alien:int sb-alien:int)))

  (sb-alien::define-alien-callback nms-id-for-menu
      sb-alien:int
      ((hmenu-high sb-alien:int)
       (hmenu-low sb-alien:int))
    (nms-id-for-menu-macro)))

#+(and lispworks (not chestnut-3))
(progn
  (fli:define-foreign-function (nms-id-for-menu-init-call-handle
                                "nms_id_for_menu_init_call_handle")
      ((ptr :pointer))
    :result-type :void)

  (fli:define-foreign-callable ("nms_id_for_menu" :result-type :long)
      ((hmenu-high :long)
       (hmenu-low :long))
    (nms-id-for-menu-macro))

  (defvar nms-id-for-menu
    (fli:make-pointer :symbol-name "nms_id_for_menu")))

#+(and clozure (not chestnut-3))
(progn
  (defun nms-id-for-menu-init-call-handle (handler)
    (declare (type ccl:macptr handler))
    (ccl:external-call "nms_id_for_menu_init_call_handle"
                       :address handler
                       :void))

  (ccl:defcallback nms-id-for-menu (:signed-fullword hmenu-high
                                    :signed-fullword hmenu-low
                                    :signed-fullword)
    (nms-id-for-menu-macro)))

;;;; UI Features


; FIXME: Ought to return list of supported features, instead.

;;; The function `get-local-ui-toolkit-name' returns the name of the UI toolkit
;;; in use in this process. This gives an indication of what features are
;;; available.

(defun get-local-ui-toolkit-name ()
  (case (nms-c-get-toolkit)
    (0 'x11)
    (1 'win32)
    (2 'xtp)
    (3 'genflex) ; unused
    ))

(def-gensym-c-function nms-c-get-toolkit
    (:fixnum-int "g2ext_nms_get_toolkit")
  ())

(def-gensym-c-function c-native-icons-limit
    (:fixnum-int "g2ext_native_icons_limit")
  ())


;;;; UI Themes


(defun nms-set-theme-1 (gensym-window theme)
  (case (type-of-gensym-window gensym-window)
    (icp
     (with-icp-window (gensym-window)
       (send-icp-nms-set-theme gensym-window theme)))
    (t
     (nms-c-set-theme theme))))

(def-icp-message-type nms-set-theme
    ((gensym-window gensym-window)
     (fixnum theme))
  (nms-set-theme-1 gensym-window theme))

(def-gensym-c-function nms-c-set-theme
    (:fixnum-int "g2ext_nms_set_theme")
  ((:fixnum-int theme)))

;;; change the icon size of the NMS menu bar and tool bar, the maximum size is 96x96

(def-icp-message-type nms-set-iconsize
    ((fixnum iconsize))
  (nms-c-set-iconsize iconsize))

(def-gensym-c-function nms-c-set-iconsize
  (:fixnum-int "g2ext_nms_set_iconsize")
  ((:fixnum-int iconsize)))

;;;; NMS Controls


;;; An `NMS control' is a native control managed by NMS (meaning that it has an
;;; NMS structure and a handle in NMS handle-space). It generalizes NMS menus
;;; and items to include toolbars, edit boxes, combo boxes, etc.

(def-concept nms-control)

(defun nms-allocate-control (window handle? type label)
  (let ((mot? (case type
                (toolbar                ; Menu-like NMS controls
                 (nms-allocate-menu window type handle?))
                (t
                 (nms-allocate-menu-item window handle?)))))
    (when mot?
      (setf (nms-menu-item-type mot?) type
            (nms-menu-item-label mot?) (copy-as-wide-string label))
      mot?)))

(defun get-button-style (button-style-name)
  (case button-style-name                ; Sync with enum XTPButtonStyle
    (automatic 0)
    (caption-only 1)
    (icon-only 2)
    (icon-and-caption 3)
    (t -1)))

(defun get-neighbor-id (gensym-window neighbor?)
  (cond ((null neighbor?)
         -1)
        ((nms-toolbar-p (nms-lookup-handle gensym-window neighbor?))
         (nms-menu-handle-to-id neighbor?))
        (t
         -1)))

;;; The icp-message-type `nms-create-control' creates an NMS control of the
;;; given type. Current types allowed are toolbar, edit-box, and combo-box.

(def-icp-message-type nms-create-control
    ((gensym-window window)
     (fixnum handle)
     (symbol type)
     (wide-string label)
     (icp-tree plist))
  (let* ((id (nms-menu-handle-to-id handle))
         (g2pointer?
           (case type
             (toolbar (nms-c-create-toolbar id label
                                            ;; Default docking for toolbars is
                                            ;; TOP, For panes, LEFT. FIXME: G2
                                            ;; should decide this, not TW!
                                            (get-dock-code (getf plist 'dock 'top))
                                            (get-neighbor-id window (getf plist 'neighbor))
                                            (logiorf
                                             (if (getf plist 'enable-tooltips) 1 0)
                                             (if (getf plist 'visible t) 2 0))
                                            (get-button-style (getf plist 'button-style))))
             (edit-box (nms-create-edit-box-2 id label
                                              (getf plist 'width 0)
                                              (getf plist 'initial #w"")))
             (combo-box (nms-create-combo-box-2 id label
                                                (getf plist 'width 0)
                                                (getf plist 'initial #w"")
                                                (getf plist 'choices)
                                                (getf plist 'drop-down-width 0)
                                                (getf plist 'allow-any))))))
    (when (and g2pointer? (>=f g2pointer? 0))
      (let ((mot? (nms-allocate-control window handle type label)))
        (when mot?
          (setf (nms-menu-item-g2pointer mot?) g2pointer?)))))
  (reclaim-wide-string label)
  (reclaim-icp-tree-with-text-strings plist))

(def-icp-message-type nms-append-control
    ((gensym-window window)
     (fixnum menu-handle)
     (fixnum control-handle))
  (nms-append-control-1 window menu-handle control-handle 0))

(def-icp-message-type nms-append-control-ex
    ((gensym-window gensym-window)
     (fixnum menu-handle)
     (fixnum control-handle)
     (fixnum flags)
     (icp-tree options))
  (nms-append-control-1 gensym-window menu-handle control-handle flags)
  (reclaim-icp-tree-with-text-strings options))

(defun nms-append-control-1 (gensym-window menu-handle control-handle flags)
  (let* ((menu? (nms-lookup-handle gensym-window menu-handle))
         (control? (nms-lookup-handle gensym-window control-handle)))
    (when (and menu? control?)
      (nms-push-item menu? control?)
      (nms-c-append-control (nms-menu-g2pointer menu?) (nms-menu-item-g2pointer control?) flags))))




(def-icp-message-type nms-modify-control
    ((gensym-window window)
     (fixnum control-handle)
     (symbol action)
     (icp-tree arg))
  (let* ((control? (nms-lookup-handle window control-handle))
         (g2pointer? (and control? (nms-menu-item-g2pointer control?)))
         (opcode? (case action
                    (show nmsc-show)        ; New for 82r1
                    (hide nmsc-hide)        ; ditto
                    (add-text nmsc-addtext)        ; added in Gensym-267
                    (delete-text nmsc-deletetext)        ; added in Gensym-267
                    (set-choice nmsc-setcursel)
                    (set-text nmsc-settext))))
    (when (and g2pointer? opcode?)
      (nms-c-manage-control g2pointer? opcode?
                            (if (fixnump arg) arg 0)
                            (if (wide-string-p arg) arg #w""))))
  (reclaim-icp-tree-with-text-strings arg))

(def-icp-message-type nms-delete-control
    ((gensym-window window)
     (fixnum menu-handle)                ; Optional (?)
     (fixnum control-handle))
  (let* ((control? (nms-lookup-handle window control-handle))
         (menu? (or (nms-lookup-handle window menu-handle)
                    (and control?
                         (nms-lookup-handle window (nms-menu-item-parent control?))))))
    (when control?
      (nms-c-delete-control (if menu? (nms-menu-g2pointer menu?) -1)
                            (nms-menu-item-g2pointer control?))
      (when menu?
        (nms-delete-item menu? control?))
      (nms-deallocate-handle window (nms-menu-item-handle control?))
      (nms-reclaim-menu-item control?))))

(defun nms-create-edit-box-2 (handle name width initial-contents)
  (nms-c-create-edit-box handle name width initial-contents))

(defun nms-create-combo-box-2 (handle name width initial-contents choices drop-down-width allow-any-p)
  (let ((packed-choices (twith-output-to-wide-string
                          (loop for choice in choices doing
                            (twrite-string-and-nul choice))
                          (twrite-char (code-wide-character 0)))))
    (prog1
        (nms-c-create-combo-box handle name width initial-contents
                                packed-choices (if allow-any-p 1 0) drop-down-width)
      (reclaim-wide-string packed-choices))))


(def-gensym-c-function nms-c-append-control
    (:fixnum-int "g2ext_nms_append_control")
  ((:fixnum-int menu-handle)
   (:fixnum-int control-handle)
   (:fixnum-int flags)))

(def-gensym-c-function nms-c-manage-control
    (:fixnum-int "g2ext_nms_manage_control")
  ((:fixnum-int control-handle)
   (:fixnum-int opcode)
   (:fixnum-int int-arg)
   (:wide-string string-arg)))

(def-gensym-c-function nms-c-delete-control
    (:fixnum-int "g2ext_nms_delete_control")
  ((:fixnum-int menu-handle)
   (:fixnum-int control-handle)))

(def-gensym-c-function nms-c-create-toolbar
    (:fixnum-int "g2ext_nms_create_toolbar")
  ((:fixnum-int handle)
   (:wide-string name)
   (:fixnum-int dock)
   (:fixnum-int neighbor)
   (:fixnum-int flags)
   (:fixnum-int default-button-style)))

(def-gensym-c-function nms-c-create-edit-box
    (:fixnum-int "g2ext_nms_create_edit_box")
  ((:fixnum-int handle)
   (:wide-string name)
   (:fixnum-int width)
   (:wide-string initial)))

(def-gensym-c-function nms-c-create-combo-box
    (:fixnum-int "g2ext_nms_create_combo_box")
  ((:fixnum-int handle)
   (:wide-string name)
   (:fixnum-int width)
   (:wide-string initial)
   (:wide-string choices)                ; \0-packed strings
   (:fixnum-int flags)                        ; bit0 = permit any string
   (:fixnum-int dropdown-width)))



;;;; Native Status Bar



(def-icp-message-type manage-status-bar
    ((gensym-window gensym-window)
     (symbol action)
     (icp-tree arg))
  (declare (ignore gensym-window))
  (manage-status-bar-1 action arg)
  (reclaim-icp-tree-with-text-strings arg))

(defun sb-fixnum (thing)
  (cond ((fixnump thing) thing)
        ((null thing) 0)
        ((eq thing t) 1)
        (t -1)))

(defmacro %manage-status-bar (opcode &optional (pane 0) string number)
  `(c-manage-status-bar ,opcode (sb-fixnum ,pane) (to-string ,string) (sb-fixnum ,number)))

(defun manage-status-bar-1 (action arg)
  (case action
    (hide (%manage-status-bar sb-hide))
    (show (%manage-status-bar sb-show))
    ((text set-text)
     (when (wide-string-p arg)
       (%manage-status-bar sb-text 0 arg)))
    (set-min-height
     (when (fixnump arg)
       (%manage-status-bar sb-minheight nil nil arg)))
    (reset
     (%manage-status-bar sb-reset))
    (add-pane
     (when (plistp arg)                        ; Paranoia
       (let ((pane-id (getf arg 'id 0)))
         (when (fixnump pane-id)
           (%manage-status-bar sb-add-pane pane-id (getf arg 'text) (getf arg 'position -1))
           (modify-status-bar-pane-1 pane-id arg)
           (%manage-status-bar sb-update)))))
    (modify-pane
     (when (plistp arg)                        ; Paranoia
       (let ((pane-id (getf arg 'id 0)))
         (when (fixnump pane-id)
           (modify-status-bar-pane-1 pane-id arg)
           (%manage-status-bar sb-update)))))

    (remove-pane
     (when (fixnump arg)                ; Paranois
       (%manage-status-bar sb-remove-pane arg)))))


(defun modify-status-bar-pane-1 (pane plist)
  (loop for (property value) on plist by #'cddr
        as propcode? = (case property
                         (text sb-pane-text)
                         (width sb-pane-width)
                         (visible sb-pane-visible)
                         (foreground-color sb-pane-foreground)
                         (background-color sb-pane-background)
                         (icon sb-pane-icon)
                         (alignment sb-pane-alignment)
                         (tooltip sb-pane-tooltip)
                         (enabled sb-pane-enabled)
                         (borders sb-pane-borders))
        when propcode?
          do (%manage-status-bar propcode? pane value value)))

(def-gensym-c-function c-manage-status-bar
    (:fixnum-int "g2ext_manage_status_bar")
  ((:fixnum-int opcode)
   (:fixnum-int pane-id)
   (:wide-string string)
   (:fixnum-int number)))


;;;; Native Panes




(def-icp-message-type manage-pane
    ((gensym-window gensym-window)
     (symbol action)
     (fixnum handle)
     (icp-tree arg))
  (let ((native-window? (find-native-window-by-handle gensym-window handle)))
    (when native-window?
      (manage-pane-locally native-window? action arg)))
  (reclaim-icp-tree-with-text-strings arg))

(defun manage-pane-1 (native-window action arg)
  (let ((gensym-window (native-window-gensym-window native-window))
        (handle (native-window-handle native-window)))
    (case (type-of-gensym-window gensym-window)
      (icp
       (with-icp-window (gensym-window)
         (send-icp-manage-pane gensym-window action handle arg)))
      (x11-window
       (manage-pane-locally native-window action arg)))))

(defmacro manage-pane-0 (opcode handle &optional (x 0) (y 0) (width 0) (height 0) (string #w""))
  `(c-manage-pane ,opcode ,handle ,x ,y ,width ,height ,string))

(defun destroy-pane-locally (gensym-window handle)
  (let ((native-window? (find-native-window-by-handle gensym-window handle)))
    (when native-window?
      (manage-pane-0 pane-destroy handle)
      (reclaim-native-window native-window?))))

(defun locally-initable-pane-property-p (name)
  (memq name '(title closeable autohideable floatable draggable visible-caption icon state close-action)))

(defun locally-initable-view-property-p (name)
  (memq name '(title closeable icon state)))

;;; The function `process-view-init-plist' runs on the TW side to pick out and
;;; apply view options from a control's init-plist. Some view options are
;;; handled separately in all cases, such as DOCK and NEIGHBOR, so they are not
;;; considered "initable". Other options may have been handled already, in which
;;; case the caller supplies some keys (option names) to skip.

(defun process-view-init-plist (native-window plist &optional keys-to-skip)
  (case (native-window-type native-window)
    (pane
     (loop for (property value) on plist by #'cddr
           when (and (locally-initable-pane-property-p property)
                     (or (null keys-to-skip)
                         (not (memq property keys-to-skip))))
             do (manage-pane-locally native-window property value)))
    ((mdi-child top-level)
     (loop for (property value) on plist by #'cddr
           when (and (locally-initable-view-property-p property)
                     (or (null keys-to-skip)
                         (not (memq property keys-to-skip))))
             do (manage-native-window-locally native-window property value)))))

(defun set-pane-state-locally (gensym-window handle new-state)
  (case new-state
    (normal (manage-pane-0 pane-show handle))
    (floating (manage-pane-0 pane-float handle))
    (docked (manage-pane-0 pane-redock handle))
    (autohidden (manage-pane-0 pane-hide handle))
    (hidden (manage-pane-0 pane-close handle))
    (closed (destroy-pane-locally gensym-window handle))))

;;; The function `manage-pane-locally' handles both actions and initialization
;;; options for native panes. TW side only.

(defun manage-pane-locally (native-window action arg)
  (let ((gensym-window (native-window-gensym-window native-window))
        (handle (native-window-handle native-window)))
    (case action
      (destroy  (destroy-pane-locally gensym-window handle))
      (hide     (manage-pane-0 pane-hide handle))    ; Autohide (down to a tab)
      (show     (manage-pane-0 pane-show handle))
      (select   (manage-pane-0 pane-select handle))
      (close    (manage-pane-0 pane-close handle))   ; Completely hide

      ((state set-state)
       (when (symbolp arg)
         (set-pane-state-locally gensym-window handle arg)))

      (float
       (when (plistp arg)
         (let ((left (getf arg 'left cw-usedefault))
               (top (getf arg 'top cw-usedefault))
               (width (getf arg 'width cw-usedefault))
               (height (getf arg 'height cw-usedefault)))
           (manage-pane-0 pane-float handle left top width height))))

      (dock
       (when (plistp arg)
         (multiple-value-bind (dock neighbor)
             (encode-dock-and-neighbor 'pane (getf arg 'dock) (getf arg 'neighbor))
           (manage-pane-0 pane-dock handle dock neighbor))))

      (redock                                ; Dock to last position (only if floating).
       (manage-pane-0 pane-redock handle))

      ((fill set-fill)                        ; FIXME: Unpredictable which pane fills.
       (manage-pane-0 pane-fill handle (if arg 1 0)))

      (toggle-docking
       (manage-pane-0 pane-toggle-docking handle))

      ((title set-title)
       (when (wide-string-p arg)
         (manage-pane-0 pane-set-title handle 0 0 0 0 arg)))

      ((closeable set-closeable)
       (manage-pane-0 pane-set-closeable handle (if arg 1 0)))

      ((hideable set-hideable autohideable set-autohideable)
       (manage-pane-0 pane-set-autohideable handle (if arg 1 0)))

      ((floatable set-floatable)
       (manage-pane-0 pane-set-floatable handle (if arg 1 0)))

      ((draggable set-draggable)
       (manage-pane-0 pane-set-draggable handle (if arg 1 0)))

      ((visible-caption set-visible-caption) ; FIXME: Not yet implemented for panes.
       (manage-pane-0 pane-set-visible-caption handle (if arg 1 0)))

      ((close-action set-close-action)
       (manage-pane-0 pane-set-close-action handle (case arg (hide 1) (t 0))))

      ((icon set-icon)
       (when (fixnump arg)                ; Native icon handle.
         (manage-pane-0 pane-set-icon handle arg))))))

(def-gensym-c-function c-manage-pane
    (:fixnum-int "g2ext_manage_pane")
  ((:fixnum-int opcode)
   (:fixnum-int handle)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:wide-string string)))


;;;; Tree Views


(defmacro manage-tree-view-1 (treeview opcode &optional (lparam 0) (string #w"")
                                       (flags 0) (icon 0) (selected-icon 0) (parent 0))
  `(c-manage-tree-view ,opcode ,treeview ,lparam ,string ,flags ,icon ,selected-icon ,parent))

;;; The function `populate-tree-view' recursively populates a tree view given a
;;; tree as created by create-tree-from-structure-hierarchy, ie:
;;;    leaf = symbol | string
;;;    tree = leaf | (leaf handle (tree ... tree) icons flags tooltip)

(defun populate-tree-view (treeview tree parent position)
  (multiple-value-bind (label handle children icons flags? tooltip?)
      (cond ((atom tree)                ; label
             (values tree 0 nil nil))
            (t                                ; (label handle children icons flags tooltip)
             (values (first tree) (second tree) (third tree) (fourth tree) (fifth tree) (sixth tree))))
    (let* ((label (cond ((stringpw label) label)
                        ((symbolp label) (stringw label))
                        (t #w"?")))
           (flags (logiorf (or flags? 0)
                           (if children tvf-children 0)
                           (if (eq position 'first) tvf-first 0)
                           (if (eq position 'after) tvf-after 0)))
           (icon (or (car-or-atom icons) -1))
           (selected-icon (or (cdr-or-atom icons) icon)))

      (if (=f handle -1)
          (setq handle 0)
        (c-manage-tree-view tree-view-insert-item
                            treeview handle label flags icon selected-icon parent))

      (when tooltip?
        (manage-tree-view-1 treeview tree-view-set-item-tooltip handle tooltip?))

      ;; Recurse.
      (loop for child in children doing
        (populate-tree-view treeview child handle nil))
      handle)))

(defun tree-view-modify-node-1 (treeview node property value)
  (case property
    (label
     (when (stringpw value)
       (manage-tree-view-1 treeview tree-view-set-item-label node value)))
    (tooltip
     (when (stringpw value)
       (manage-tree-view-1 treeview tree-view-set-item-tooltip node value)))
    (icon
     (when (fixnump value)
       (manage-tree-view-1 treeview tree-view-set-item-icons node #w"" 0 value value)))
    (selected-icon
     (when (fixnump value)
       (manage-tree-view-1 treeview tree-view-set-item-icons node #w"" 0 -1 value)))
    (bold
     (manage-tree-view-1 treeview tree-view-set-item-bold node #w"" (if value 1 0)))
    (expand
     (manage-tree-view-1 treeview (if value tree-view-expand-item tree-view-collapse-item)
                         node))))

(def-icp-message-type manage-tree-view
    ((gensym-window gensym-window)
     (symbol action)
     (fixnum handle)
     (icp-tree arg))
  (case action
    (create
     (with-decoded-view-options (arg :dock left :title-property label)
       (let* ((window-index
                (c-create-tree-view handle title left top width height dock neighbor min-width min-height))
              (native-window
                (make-basic-native-window gensym-window handle window-index 'g2-tree-view container)))
         (process-view-init-plist native-window arg '(title))
         (process-tree-init-plist native-window arg))))

    (destroy
     (manage-tree-view-1 handle tree-view-destroy)
     (reclaim-native-window-by-handle gensym-window handle))

    ;; Pane operations.
    (hide    (manage-pane-0 pane-hide handle))
    (show    (manage-pane-0 pane-show handle))
    (select  (manage-pane-0 pane-select handle))
    (close   (manage-pane-0 pane-close handle))

    ;; Tree-view operations.
    (populate                                ; Insert at root
     (when arg
        (manage-tree-view-1 handle tree-view-redraw 0 #w"" 0)
        (populate-tree-view handle arg 0 'last)
        (manage-tree-view-1 handle tree-view-redraw 0 #w"" 1)))

    (insert                                ; Insert at arbitrary location.
     (when (plistp arg)
       (let ((tree (getf arg 'tree))
             (parent (getf arg 'parent 0))
             (position (getf arg 'position 'last)))
         (manage-tree-view-1 handle tree-view-redraw 0 #w"" 0)
         (populate-tree-view handle tree parent position)
         (manage-tree-view-1 handle tree-view-redraw 0 #w"" 1))))

    (clear                                ; Remove all items
     (manage-tree-view-1 handle tree-view-clear))

    ;; Node operations.
    (select-item                        ; By label (old way)
     (when (stringpw arg)
       (manage-tree-view-1 handle tree-view-select-item-by-name 0 arg)))

    (select-node
     (when (fixnump arg)                ; By handle
       (manage-tree-view-1 handle tree-view-select-item arg)))

    (delete-node
     (when (fixnump arg)
       (manage-tree-view-1 handle tree-view-delete-item arg)))

    (edit-node
     (when (fixnump arg)
       (manage-tree-view-1 handle tree-view-edit-item arg)))

    (expand-node
     (when (fixnump arg)
       (manage-tree-view-1 handle tree-view-expand-item arg)))

    (collapse-node
     (when (fixnump arg)
       (manage-tree-view-1 handle tree-view-collapse-item arg)))

    (modify-node
     (when (plistp arg)
       (let ((node? (getf arg 'node)))
         (when (fixnump node?)
           (loop for (property value) on arg by #'cddr doing
             (tree-view-modify-node-1 handle node? property value))))))

    (t
     (let ((native-window? (find-native-window-by-handle gensym-window handle)))
       (when native-window?
         (manage-tree-view-locally native-window? action arg)))))
  (reclaim-icp-tree-with-text-strings arg))

;;; The function `process-tree-init-plist' runs on TW to process
;;; tree-view-specific options in the control's init-plist.

(defun process-tree-init-plist (native-window plist)
  (loop for (property value) on plist by #'cddr doing
    (manage-tree-view-locally native-window property value)))

(defun manage-tree-view-locally (native-window action arg)
  (let ((handle (native-window-handle native-window)))
    (case action
      ((indent set-indent)
       (when (fixnump arg)
         (manage-tree-view-1 handle tree-view-set-indent arg)))

      ((item-height set-item-height)
       (when (fixnump arg)
         (manage-tree-view-1 handle tree-view-set-item-height arg)))

      ((background-color set-background-color)
       (when (fixnump arg)
         (manage-tree-view-1 handle tree-view-set-bgcolor arg)))

      ((foreground-color set-foreground-color)
       (when (fixnump arg)
         (manage-tree-view-1 handle tree-view-set-text-color arg)))

      ((insert-mark-color set-insert-mark-color)
       (when (fixnump arg)
         (manage-tree-view-1 handle tree-view-set-insert-mark-color arg)))

      (expand-all
       (when (fixnump arg)
         (manage-tree-view-1 handle tree-view-expand-all arg)))

      (collapse-all
       (when (fixnump arg)
         (manage-tree-view-1 handle tree-view-collapse-all arg)))

      ((right-click-selects-node set-right-click-selects-node)
       (manage-tree-view-1 handle tree-view-set-right-click-selects-node (if arg 1 0))))))

(def-gensym-c-function c-create-tree-view
    (:fixnum-int "g2ext_create_tree_view")
  ((:fixnum-int handle)
   (:wide-string title)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int dock)
   (:fixnum-int neighbor)
   (:fixnum-int min-width)
   (:fixnum-int min-height)))

(def-gensym-c-function c-manage-tree-view
    (:fixnum-int "g2ext_manage_tree_view")
  ((:fixnum-int opcode)
   (:fixnum-int handle)
   (:fixnum-int lparam)
   (:wide-string string)
   (:fixnum-int has-children)
   (:fixnum-int icon-handle)
   (:fixnum-int icon-handle-sel)
   (:fixnum-int parent)))


;;;; Property Grid

(defparameter property-grid-opcodes
  '((create . 10)
    (destroy . 11)
    (populate . 12)
    (add-item . 13)
    (modify . 14)
    (clear . 15)
    (refresh . 16)
    (reset-colors . 17)
    (foreground-color . 18)
    (background-color . 19)
    (line-color . 20)
    (help-foreground-color . 21)
    (help-background-color . 22)
    (category-foreground-color . 23)
    (readonly-foreground-color . 24)
    (sort . 25)
    (show-toolbar . 26)
    (show-help . 27)
    (help-height . 28)
    (view-divider . 29)
    (font . 30)
    (verbs . 31)
    (verbs-height . 32)

    (modify-node . 100)                        ; NODE opcodes
    (select-node . 101)
    (delete-node . 102)
    (expand-node . 103)
    (collapse-node . 104)
    (property . 105)
    (category . 106)
    (type . 107)
    (label . 108)
    (description . 109)
    (current-value . 110)
    (possible-values . 111)
    (value-format . 112)
    (icon . 113)
    (mask . 114)
    (readonly . 115)
    (ellipsis . 116)
    (edit-in-place . 117)
    (expand . 118)
    (select . 119)
    (expand-all . 120)
    (collapse-all . 121)
    ;; unused: (edit-standalone . 122)
    ))

(defparameter prop-grid-node-type '(member category text integer boolean color date float))
(defparameter prop-grid-sort-type '(member none alphabetical categorized))
(defparameter prop-grid-events '(select right-click key-pressed closed
                                 node-expanded node-collapsed
                                 edited edit double-click sorted
                                 verb on-enter))

(defun prop-grid-opcode (name)
  (cdr (assq name property-grid-opcodes)))

(defun prop-grid-node-opcode (name)
  (let ((opcode? (prop-grid-opcode name)))
    (and opcode? (>=f opcode? 100) opcode?)))

(defun prop-grid-type-code (type-symbol)
  (or (position type-symbol (cdr prop-grid-node-type)) -1))

(defun prop-grid-sort-code (sort-symbol)
  (or (position sort-symbol (cdr prop-grid-sort-type)) -1))

(defun prop-grid-sort-symbol (sort-code)
  (if (<=f 0 sort-code 2)
      (nth sort-code (cdr prop-grid-sort-type))))

(defun prop-grid-event-name (event-code)
  (if (<=f 0 event-code (1-f (length prop-grid-events)))
      (nth event-code prop-grid-events)
      (dwarn "Unknown property grid event code ~s" event-code)))

(def-icp-message-type manage-property-grid
    ((gensym-window gensym-window)
     (symbol action)
     (fixnum handle)
     (fixnum node)
     (icp-tree arg))
  (manage-property-grid-1 gensym-window action handle node arg)
  (reclaim-icp-tree-value arg))

;;; The function `populate-property-grid' creates a property item for each
;;; node-spec, as created by prop-grid-create-node-spec.

(defun populate-property-grid (pg node-specs)
  (loop with handle = (native-window-handle pg)
        with category-type-code = (prop-grid-type-code 'category)
        for (caption id parent? type-code? value? . plist?) in node-specs
        doing
    (%manage-property-grid 'add-item
                           handle
                           id
                           value?
                           (or type-code? category-type-code)
                           (or parent? 0)
                           caption)
    (when plist?
      (process-property-grid-init-plist pg plist? id))))

(def-gensym-c-function c-create-property-grid
    (:fixnum-int "g2ext_create_property_grid")
  ((:fixnum-int handle)
   (:wide-string title)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int dock)
   (:fixnum-int neighbor)))

(def-gensym-c-function c-manage-property-grid
    (:fixnum-int "g2ext_manage_property_grid")
  ((:fixnum-int opcode)
   (:fixnum-int handle)
   (:fixnum-int node)
   (:fixnum-int type)                        ; Or index
   (:fixnum-int parent)                        ; Or count
   (:wide-string caption)
   (:wide-string string-value)
   (:fixnum-int integer-value)
   (:double-float double-value)))


;; NOTE: This could be a generic routine for all native controls.
(defun %manage-property-grid (action handle &optional
                                     (node 0) (value nil) (type 0)
                                     (parent 0) (caption #w""))
  (macrolet ((call (opcode handle node type parent caption value)
               `(c-manage-property-grid
                  ,opcode ,handle ,node ,type ,parent ,caption
                  (if (wide-string-p ,value) ,value #w"")
                  (cond ((fixnump ,value) ,value)
                        ((eq ,value t) 1)
                        (t 0))
                  (if (managed-float-p ,value) (managed-float-value ,value) 0.0))))
    (let ((opcode (prop-grid-opcode action)))
      #+development (unless opcode
                      (dwarn "Unknown view or property-grid action ~s" action))
      (when opcode
        (with-temporary-gensym-float-creation %manage-property-grid
          ;; This is how we pass a list to C, by invoking the opcode once for each
          ;; element, passing the element's index and total count on each call.  If
          ;; value is NIL, then this is ambiguous with a boolean false, but it works
          ;; out since index=count=0 in that case.
          (cond ((consp value)
                 (loop with count = (length value)
                       for elem in value
                       as index from 0
                       doing (call opcode handle node index count caption elem)))
                (t
                 (call opcode handle node type parent caption value))))))))

(defun process-property-grid-init-plist (pg plist &optional (node 0))
  (loop with gensym-window = (native-window-gensym-window pg)
        with handle = (native-window-handle pg)
        for (action arg) on plist by #'cddr
        do (manage-property-grid-1 gensym-window action handle node arg)))

(defun manage-property-grid-1 (gensym-window action handle node arg)
  (let ((prop-grid? (find-native-window-by-handle gensym-window handle)))
    (case action
      (create
       (with-decoded-view-options (arg :title #w"Property Grid" :dock right)
         (let* ((window-index
                  (c-create-property-grid handle title left top width height dock neighbor))
                (prop-grid
                  (make-basic-native-window
                    gensym-window handle window-index 'g2-property-grid container)))
           (process-view-init-plist prop-grid arg '(title))
           (process-property-grid-init-plist prop-grid arg))))

      ((contents populate)
       (when (and (consp arg) prop-grid?)                ; Arg = node-specs, Node = ignored
         (populate-property-grid prop-grid? arg)))

      (destroy
       (%manage-property-grid action handle)
       (reclaim-native-window-by-handle gensym-window handle))

      ((modify modify-node)
       (when (and prop-grid? (plistp arg))
         (process-property-grid-init-plist prop-grid? arg node)))

      (t
       (when prop-grid?
         (%manage-property-grid action handle node arg))))))

(def-substitution-macro prop-grid-create-node-spec (caption id type? parent? value? plist?)
  (nconc
    (gensym-list caption)
    (gensym-list id)
    (if (or parent? type? value? plist?)
        (gensym-list parent?))
    (if (or type? value? plist?)
        (gensym-list (if type? (prop-grid-type-code type?))))
    (if (or value? plist?)
        (gensym-list value?))
    plist?))




;;;; HTML Views




(defmacro manage-html-view-0 (opcode handle &optional (string #w""))
  `(c-manage-html-view ,opcode ,handle ,string))

(def-icp-message-type manage-html-view
    ((gensym-window gensym-window)
     (symbol action)
     (fixnum handle)
     (icp-tree arg))
  (case action
    (create
     (with-decoded-view-options (arg :container mdi-child :dock left)
       (let* ((url (getf arg 'url #w""))
              (window-index
                (c-create-html-view handle title url left top width height dock neighbor min-width min-height))
              (native-window
                (make-basic-native-window gensym-window handle window-index 'g2-html-view container)))
         (process-view-init-plist native-window arg))))

    (destroy (manage-html-view-0 html-view-destroy handle)
             (reclaim-native-window-by-handle gensym-window handle))
    (back    (manage-html-view-0 html-view-back handle))
    (forward (manage-html-view-0 html-view-forward handle))
    (home    (manage-html-view-0 html-view-home handle))
    (stop    (manage-html-view-0 html-view-stop handle))
    (refresh (manage-html-view-0 html-view-refresh handle))
    (goto    (when (wide-string-p arg)        ; paranoia
               (manage-html-view-0 html-view-goto handle arg)))
    (print   (manage-html-view-0 html-view-print handle)))
  (reclaim-icp-tree-with-text-strings arg))


(def-gensym-c-function c-create-html-view
    (:fixnum-int "g2ext_create_html_view")
  ((:fixnum-int handle)
   (:wide-string title)
   (:wide-string url)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int dock)
   (:fixnum-int neighbor)
   (:fixnum-int min-width)
   (:fixnum-int min-height)))

(def-gensym-c-function c-manage-html-view
    (:fixnum-int "g2ext_manage_html_view")
  ((:fixnum-int opcode)
   (:fixnum-int handle)
   (:wide-string url)))



(defmacro %manage-shortcut-bar (handle opcode &optional (folder 0) (icon 0) (tooltip #w""))
  `(c-manage-shortcut-bar ,opcode ,handle #w"" ,folder ,icon ,tooltip))

(def-icp-message-type manage-shortcut-bar
    ((gensym-window gensym-window)
     (symbol action)
     (fixnum handle)
     (icp-tree arg))
  (manage-shortcut-bar-1 gensym-window handle action arg)
  (reclaim-icp-tree-with-text-strings arg))

(defun process-shortcut-bar-init-plist (native-window plist)
  (loop for (p v) on plist by #'cddr doing
    (manage-shortcut-bar-1 (native-window-gensym-window native-window)
                           (native-window-handle native-window)
                           p v)))

(defun manage-shortcut-bar-1 (gensym-window handle action arg)
  (case action
    (create
     (with-decoded-view-options (arg :title #w"Shortcut Bar" :width 150)
       (let* ((style (getf arg 'style shortcut-bar-style-outlook))
              (obstyle (logiorf obs-default-style
                                (if (getf arg 'allow-drag-item) obs-xt-dragitems 0)
                                (if (getf arg 'allow-rename-item) obs-xt-edititems 0)))
              (window-index
                (c-create-shortcut-bar handle style obstyle title left top width height dock neighbor min-width min-height))
              (native-window
                (make-basic-native-window gensym-window handle window-index 'g2-shortcut-bar container)))
         (process-view-init-plist native-window arg '(title))
         (process-shortcut-bar-init-plist native-window arg))))

    (destroy
     (%manage-shortcut-bar handle shortcut-bar-destroy)
     (reclaim-native-window-by-handle gensym-window handle))

    ;; Pane operations.
    (hide    (manage-pane-0 pane-hide handle))
    (show    (manage-pane-0 pane-show handle))
    (select  (manage-pane-0 pane-select handle))
    (close   (manage-pane-0 pane-close handle))

    ;; Shortcut bar operations
    (populate
     (when (listp arg)                        ; Paranoia.
       (shbar-populate handle arg)))

    (add-folder
     (when (plistp arg)
       (shbar-add-folder handle
                         (getf arg 'label)
                         (getf arg 'icon)
                         (getf arg 'tooltip))))
    (add-item
     (when (plistp arg)
       (shbar-add-item handle
                       (getf arg 'folder)
                       (getf arg 'label)
                       (getf arg 'icon)
                       (getf arg 'tooltip))))
    (clear (shbar-clear handle))
    (small-icons (%manage-shortcut-bar handle shortcut-bar-small-icons))
    (large-icons (%manage-shortcut-bar handle shortcut-bar-large-icons))

    (background-color
     (when (fixnump arg)
       (%manage-shortcut-bar handle shortcut-bar-background-color arg)))
    (foreground-color
     (when (fixnump arg)
       (%manage-shortcut-bar handle shortcut-bar-foreground-color arg)))

    (select-folder
     (when (fixnump arg)
       (%manage-shortcut-bar handle shortcut-bar-select-folder arg)))
    (enable-folder
     (when (fixnump arg)
       (%manage-shortcut-bar handle shortcut-bar-enable-folder arg)))
    (disable-folder
     (when (fixnump arg)
       (%manage-shortcut-bar handle shortcut-bar-disable-folder arg)))

    (select-item
     (when (plistp arg)
       (%manage-shortcut-bar handle shortcut-bar-select-item
                             (getf arg 'folder 0) (getf arg 'item 0))))
    (enable-item
     (when (plistp arg)
       (%manage-shortcut-bar handle shortcut-bar-enable-item
                             (getf arg 'folder 0) (getf arg 'item 0))))
    (disable-item
     (when (plistp arg)
       (%manage-shortcut-bar handle shortcut-bar-disable-item
                             (getf arg 'folder 0) (getf arg 'item 0))))))


;; TODO: folder options for large/small icons, etc, + global options.
(defun shbar-populate (handle folders)
  (loop for folder in folders
        as label? = (getf folder 'label)
        as icon? = (getf folder 'icon)
        as tooltip? = (getf folder 'tooltip)
        as items = (getf folder 'items)
        as nfolder = (shbar-add-folder handle label? icon? tooltip?)
        doing
    (loop for item in items
          as label? = (getf item 'label)
          as icon? = (getf item 'icon)
          as tooltip? = (getf item 'tooltip)
          doing
      (shbar-add-item handle nfolder label? icon? tooltip?))))

(defun shbar-clear (handle)
  (%manage-shortcut-bar handle shortcut-bar-clear))

;; Returns index of added folder.
(defun shbar-add-folder (handle label? icon? tooltip?)
  (let* ((label (if (stringpw label?) label? #w""))
         (tooltip (if (stringpw tooltip?) tooltip? label))
         (icon (or icon? -1)))
    (c-manage-shortcut-bar shortcut-bar-add-folder handle label 0 icon tooltip)))

(defun shbar-add-item (handle folder? label? icon? tooltip?)
  (let* ((label (if (stringpw label?) label? #w""))
         (tooltip (if (stringpw tooltip?) tooltip? #w""))
         (icon (or icon? -1))
         (folder (if (fixnump folder?) folder? 0)))
    (c-manage-shortcut-bar shortcut-bar-add-item handle label folder icon tooltip)))


(def-gensym-c-function c-create-shortcut-bar
    (:fixnum-int "g2ext_create_shortcut_bar")
  ((:fixnum-int handle)
   (:fixnum-int style)                        ; 1=outlook2000, 2=outlook2003, etc.
   (:fixnum-int obstyle)
   (:wide-string title)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int dock)
   (:fixnum-int neighbor)
   (:fixnum-int min-width)
   (:fixnum-int min-height)))

(def-gensym-c-function c-manage-shortcut-bar
    (:fixnum-int "g2ext_manage_shortcut_bar")
  ((:fixnum-int opcode)
   (:fixnum-int handle)
   (:wide-string string)
   (:fixnum-int folder)
   (:fixnum-int icon)
   (:wide-string tooltip)))


;;;; Built-In Dialogs


(defconstant-for-case dlg-post-modal 1)                ; Opcodes, sync with ext/c/twpro.c
(defconstant-for-case dlg-cancel-modal 2)



(defconstant-for-case dlgt-short 1)                ; Types for packed result value.
(defconstant-for-case dlgt-string 2)

(def-icp-message-type manage-dialog
    ((gensym-window gensym-window)
     (fixnum opcode)
     (fixnum handle)
     (icp-tree arg))
  (case opcode
    (#.dlg-post-modal
     (with-deferred-execution-in-tw ()
       (manage-dialog-icp gensym-window (gensym-window-serial-number gensym-window)
                          opcode handle arg)))
    (t
     (manage-dialog-1 gensym-window opcode handle arg)
     (reclaim-icp-tree-with-text-strings arg))))

(defun manage-dialog (gensym-window opcode handle arg)
  (cond ((icp-window-p gensym-window)
         (with-icp-window (gensym-window)
           (send-icp-manage-dialog gensym-window opcode handle arg)))
        (t
         (manage-dialog-1 gensym-window opcode handle arg))))

(defun manage-dialog-icp (gensym-window serial opcode handle arg)
  (when (gensym-window-has-not-been-reprocessed-p gensym-window serial)
    (manage-dialog-1 gensym-window opcode handle arg))
  (reclaim-icp-tree-with-text-strings arg))

(defun manage-dialog-1 (gensym-window opcode handle arg)
  (case opcode
    (#.dlg-post-modal
     (when (plistp arg)
       (let ((beep (getf arg 'beep 0))
             (spec (getf arg 'spec))
             (data (getf arg 'data))
             (buflen (getf arg 'buflen 1024))
             (key-code (getf arg 'key-code (key-code-for-key-symbol 'login-dialog))))
         (post-modal-dialog-1 gensym-window handle key-code beep spec data buflen))))
    (#.dlg-cancel-modal
     (c-post-dialog -1 0 #w"" 0)))) ; Hack

(defun post-modal-dialog-1 (gensym-window handle key-code beep spec data buflen)
  (let* ((window-index (native-window? gensym-window))
         (controls nil)
         (control-names nil)                ; Alist of (id . name)
         (dialog-index
           (gensym-dstruct-bind ((caption x y width height style exstyle flags font font-size ctrls)
                                (cdr spec))
             (setq controls ctrls)
             (let ((size (+f 256 (loop for (nil nil caption) in controls
                                       sum 128
                                       if (wide-string-p caption)
                                         sum (*f 2 (lengthw caption))))))
               (c-make-dialog caption size (length controls) x y width height
                              (32bit-integer-high-part style)
                              (32bit-integer-low-part style)
                              (32bit-integer-high-part exstyle)
                              (32bit-integer-low-part exstyle)
                              flags font font-size)))))

    (loop for (class name caption? x y width height style exstyle flags data?) in controls
          as control-id from 1000
          as id = (if (fixnump name) name control-id)
          as lisp-data = (or (and (symbolp name) (getf data name))
                             data?)
          as packed-data = (dlg-pack-init-data class lisp-data)
          doing
      (when (and name (symbolp name))
        (gensym-push (gensym-cons id name) control-names))
      (c-add-control dialog-index
                     (if (stringpw class) class (symbol-namew class))
                     (or caption? #w"")
                     id x y width height
                     (32bit-integer-high-part style)
                     (32bit-integer-low-part style)
                     (32bit-integer-high-part exstyle)
                     (32bit-integer-low-part exstyle)
                     flags packed-data))

    (let* ((buffer (obtain-text-string buflen))
           (rc (c-post-dialog dialog-index beep buffer buflen)) ; Modal loop here.
           (choice (or (win32-choice-symbol rc)
                       (cdr (assq rc control-names))
                       'cancel))
           (results (dlg-unpack-result-data control-names buffer))
           (event-plist (nconc (gensym-list 'g2pvt-handle handle 'g2pvt-choice choice)
                               results)))
      (reclaim-wide-string buffer)
      (reclaim-gensym-tree control-names)
      (enqueue-local-event window-index
                           key-code
                           (c-x11-last-mouse-x-position window-index)
                           (c-x11-last-mouse-y-position window-index)
                           (c-x11-last-event-time window-index)
                           event-plist))))

(defun dlg-pack-init-data (class data)
  ;; Format [method] [count] ...words...
  (macrolet ((putwords (&rest words)
               `(progn
                  ,@(loop for word in words
                          collect `(twrite-wide-character (code-charw ,word))))))
    class
    (twith-output-to-wide-string
      (cond ((null data))
            ((symbolp data)
             (putwords dlgm-settext 0)
             (twrite-string-and-nul (stringw data)))
            ((stringpw data)
             (putwords dlgm-settext 0)
             (twrite-string-and-nul data))
            ((listp data)
             (putwords dlgm-addstrings 0)
             (loop with write-symbols-in-lower-case? = t
                   for element in data
                   do (twrite element)
                      (twrite-char #.%Null)
                   finally (twrite-char #.%Null)))))))

(defun dlg-unpack-result-data (control-names buffer)
  ;; Buffer format: [id] [type] [type-dependent-data], ..., [0] [0]
  (macrolet ((getword () `(prog1
                              (if (<f i length) (charw-bv16 buffer i) 0)
                            (incff i))))
    (loop with length = (wide-string-length buffer)
          with i = 0
          as id = (getword)
          until (=f id 0)
          as type = (getword)
          as name? = (cdr (assq id control-names))
          as value? = (case type
                        (#.dlgt-short
                         (getword))
                        (#.dlgt-string
                         (loop with len = (getword)
                               with string = (obtain-text-string len)
                               for j below len
                               do (setf (charw-bv16 string j) (getword))
                               finally (return string)))
                        (t
                         (dwarn "Unknown type ~d in dlg-unpack-results." type)
                         (loop-finish)))
          when (and name? value?)
            collect name? using gensym-cons
            and collect value? using gensym-cons)))

(defun win32-choice-symbol (retcode)
  (when (<f 0 retcode (length win32-choice-symbols))
    (svref win32-choice-symbols retcode)))

(def-gensym-c-function c-make-dialog
    (:fixnum-int "g2ext_make_dialog")
  ((:wide-string caption)
   (:fixnum-int size)
   (:fixnum-int number-of-controls)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int styleHi)
   (:fixnum-int styleLo)
   (:fixnum-int exstyleHi)
   (:fixnum-int exstyleLo)
   (:fixnum-int flags)
   (:wide-string font)
   (:fixnum-int font-size)))

(def-gensym-c-function c-add-control
    (:fixnum-int "g2ext_add_control")
  ((:fixnum-int dlg)
   (:wide-string class)
   (:wide-string text)
   (:fixnum-int id)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int styleHi)
   (:fixnum-int styleLo)
   (:fixnum-int exstyleHi)
   (:fixnum-int exstyleLo)
   (:fixnum-int flags)
   (:wide-string data)))

(def-gensym-c-function c-post-dialog
    (:fixnum-int "g2ext_post_dialog")
  ((:fixnum-int dlg)
   (:fixnum-int beep)
   (:wide-string results)
   (:fixnum-int buflen)))


;;;; Chart Views



(defconstant-for-case chart-inappropriate-property 2)
(defconstant-for-case chart-invalid-array-property 3)
(defconstant-for-case chart-invalid-float-property 4)
(defconstant-for-case chart-set-failed 5)

(defvar charting-library-version? 'unknown)

;; GENSYMCID-1054: Gigasoft Charts Issue causes TWNG to crash and exit without
;;                 warning when using TWNG 2011 with 8.3r1
;;
;; The 5th argument `charting-library-to-use' was wrongly added in early 2011.
;; It broke the ICP compatibility between TWNG 2011 and G2 8.3r1. The correct
;; way to support more arguments, is to put them into exist `args' plist and
;; then use GETF to retrieve from TW side.
;;
;; However, simply remove the 5th argument is NOT an acceptable solution,
;; because that will cause TWNG 2011 starting from June relases fail to work
;; with old G2 2011 server. To save all the compatibilities, now we implemented
;; following strategies:
;;
;; 1. The argument `charting-library-to-use' is obsoleted: new G2 server start
;;    from June 2013 will send NIL for it. Instead, the real argument will be
;;    put into `args' plist for CREATE action only.
;;
;; 2. TWNG 2011, when receiving this message from new G2 2011 server, it will
;;    check `args' for the chart-library to use.
;;
;; 3. TWNG 2011, when receiving this message from old G2 2011 server, since
;;    `args' doesn't provide the value, the argument `charting-library-to-use'
;;    will still be used.
;;
;; 4. TWNG 2011, when receiving this message from G2 8.3r1, the 5th argument
;;    doesn't exist in ICP buffer at all. In this case we modified ICP handler
;;    code to handle this case and bypassed the argument receiving process, in
;;    this case we use GIGASOFT. For ICP change details, please take a look at
;;    the NOTE of macro `body-of-read-icp-unsigned-integer'.
;;
;; -- Chun Tian (binghe), 2013/06/19

(def-icp-message-type manage-chart-view
    ((gensym-window gensym-window)
     (symbol action)
     (fixnum handle)
     (icp-tree arg)
     (symbol charting-library-to-use = 'gigasoft))
  (manage-chart-view-1 gensym-window action handle arg charting-library-to-use)
  (reclaim-icp-tree-of-values arg))

(defmacro %manage-chart-view (handle opcode &optional (width 0) (height 0) (format 0) (filename #w""))
  `(c-manage-chart-view ,handle ,opcode ,width ,height ,format ,filename))

;; TODO: other view opcodes: move, size, min, max, dock, float, reparent, etc.
(defun manage-chart-view-1 (gensym-window action handle arg charting-library-to-use)
  (case action
    (create
     (with-decoded-view-options (arg :title #w"Chart View" :container mdi-child)
       (let* ((style (case container
                       (mdi-child (process-window-style-options default-mdi-child-style arg))
                       (t (logiorf ws-child ws-clipsiblings))))
              (chart-type (pechart-type-code (getf arg 'type)))
              (charting-library (or (getf arg 'charting-library-to-use)
                                    charting-library-to-use))
              (window-index
                (c-create-chart-view handle title chart-type style left top width height dock neighbor
                                     (cajole-into-string charting-library) min-width min-height))
              (native-window
                (make-basic-native-window gensym-window handle window-index 'g2-chart-view container)))
         (process-view-init-plist native-window arg '(title))
         (set-chart-properties handle arg))))

    (destroy
     (%manage-chart-view handle chart-destroy)
     (reclaim-native-window-by-handle gensym-window handle))

    (print   (%manage-chart-view handle chart-print))
    (update  (%manage-chart-view handle chart-update))
    (partial-update
     (when (plistp arg)
       (let ((start (getf arg 'start 0))
             (count (getf arg 'count 1)))
         (%manage-chart-view handle chart-partial-update start count))))
    (copy (%manage-chart-view handle chart-copy))
    (export (export-chart-view handle arg)) ; Export to client-side file
    (set
     (when (plistp arg)                        ; paranoia
       (set-chart-properties handle arg)))))

(defun export-chart-view (handle arg)
  (let ((pathname? nil)
        (format? nil)
        (width 0)
        (height 0))
    (cond ((wide-string-p arg)
           (setq pathname? arg))
          ((plistp arg)
           (setq pathname? (getf arg 'pathname)
                 format? (getf arg 'format)
                 width (getf arg 'width 0)
                 height (getf arg 'height 0))))
    (when pathname?
      (let ((code (chart-export-format (or format?
                                           (pathname-type-as-symbol pathname?)))))
        (%manage-chart-view handle chart-export width height code pathname?)))))

(defun chart-export-format (symbol)
  (case symbol
    ((jpg jpeg) chart-format-jpeg)
    (png chart-format-png)
    (bmp chart-format-bmp)
    ((wmf emf) chart-format-wmf)
    (svg chart-format-svg)
    (t chart-format-png)))

(defun pathname-type-as-symbol (pathname)
  (loop with limit = (1-f (wide-string-length pathname))
        for i from limit downto 0
        as ch = (charw pathname i)
        when (char=w (charw pathname i) %\.)
          return (if (<f i limit)
                     (intern-wide-string
                       (nstring-upcasew
                         (wide-string-substring pathname (1+f i) nil))))))


;; TODO: Error check chart type names, too.
(defun pechart-type-code (type &optional (default 300))
  (case type
    (graph 300)
    (pie 302)
    ((sgraph scigraph) 304)
    ((pgraph polar) 308)
    (3d 312)                                ; pecontrol-3d
    ((pechart-enum-value type))                ;???
    (t default)))

(defun %set-chart-property (handle name prop type i j v)
  name
  (case type
    ((nil)
     (dwarn "Unknown property name: ~s" name))

    ((n b)                                ; integer, bool
     (c-chart-set-int handle prop -1 -1 (cajole-into-fixnum name v)))

    (dw                                        ; dword. These are always RGB colors.
     (c-chart-set-int handle prop -1 -1 (cajole-into-fixnum name v)))

    (sz                                        ; string
     (c-chart-set-string handle prop -1 -1 (cajole-into-string v)))

    (f                                        ; float
     (with-temporary-gensym-float-creation set-chart-properties
       (c-chart-set-double handle prop -1 -1 (cajole-into-float v))))

    ((na dwa)                                ; Integer or dword array
     (chart-set-int-array handle name prop i j v))

    (sza                                ; String array
     (chart-set-string-array handle name prop i j v))

    (fa                                        ; Float array
     (chart-set-double-array handle name prop i j v))

    ;; GENSYMCID-1225: Chart-view Gigasoft and SetSpringDayLight property
    (struct				; C struct
     (when (and v (plistp v))
       (macrolet ((%add-str (data)
		    `(c-chart-add-str-to-struct 
		      (if (wide-string-p ,data)
			,data
			#w"")))
		  (%add-long (data)
		    `(c-chart-add-long-to-struct (if (fixnump ,data)
						   ,data
						   0)))
		  (%add-double (data)
		    `(c-chart-add-double-to-struct (cajole-into-float ,data))))
	 (with-temporary-gensym-float-creation set-chart-struct
	   (case name
	     ((spring-daylight fall-daylight)
	      (%add-long (getf v 'nMonth))
	      (%add-long (getf v 'nDay))
	      (%add-long (getf v 'nHour)))
	     (custom-grid-numbers
	      (%add-long (getf v 'nAxisType))
	      (%add-long (getf v 'nAxisIndex))
	      (%add-double (getf v 'dNumber))
	      (%add-str (getf v 'szData)))
	     ((extra-axis-tx extra-axisx)
	      (%add-long (getf v 'nSize))
	      (%add-double (getf v 'fMin))
	      (%add-double (getf v 'fMax))
	      (%add-str (getf v 'szLabel))
	      (%add-double (getf v 'fManualLine))
	      (%add-double (getf v 'fManualTick))
	      (%add-str (getf v 'szFormat))
	      (%add-long (getf v 'nShowAxis))
	      (%add-long (getf v 'nShowTickMark))
	      (%add-long (getf v 'bInvertedAxis))
	      (%add-long (getf v 'bLogScale))
	      (%add-long (getf v 'dwColor)))
	     (graph-loc
	      (%add-long (getf v 'nAxis))
	      (%add-double (getf v 'fXval))
	      (%add-double (getf v 'fYval)))
	     (hot-spot-data
	      (let ((rect (getf v 'rectHotSpot)))
		(cond ((and rect (plistp rect))
		       (%add-long (getf rect 'left))
		       (%add-long (getf rect 'top))
		       (%add-long (getf rect 'right))
		       (%add-long (getf rect 'bottom)))
		      (t
		       (loop repeat 4 do (%add-long 0)))))
	      (%add-long (getf v 'nHotSpotType))
	      (%add-long (getf v 'w1))
	      (%add-long (getf v 'w2)))
	     (keydown-data
	      (%add-long (getf v 'nChar))
	      (%add-long (getf v 'nRepCnt))
	      (%add-long (getf v 'nFlags)))
	     (poly-data
	      (let ((vertices (getf v 'Vertices)))
		(cond ((and vertices (listp vertices))
		       (loop for i from 0 below 4
			     for data in vertices 
			     do (cond ((and data (plistp data))
				       (%add-double (getf data 'X)) 
				       (%add-double (getf data 'Y)) 
				       (%add-double (getf data 'Z)))
				      (t
				       (loop repeat 3 do (c-chart-add-double-to-struct 0.0d0))))
			     finally (loop repeat (*f 3 (-f 4 i))
					   do (c-chart-add-double-to-struct 0.0d0))))
		      (t (loop repeat 12 do (c-chart-add-double-to-struct 0.0d0)))))
	      (%add-long (getf v 'NumberOfVertices))
	      (%add-long (getf v 'PolyColor))
	      (%add-long (getf v 'dwReserved1))
	      (%add-long (getf v 'dwReserved2)))))
	 (c-chart-set-struct handle prop))))
    (t
     (dwarn "Unknown property type ~s for ~s" type name))))

(defun set-chart-properties (handle plist)
  (loop for (name value) on plist by #'cddr
        as prop = (pechart-property-code name)
        as type = (pechart-property-type name)
        as i = 0
        as j = -1
        as v = value
        when (and (plistp value)        ; A heuristic to distinguish a plist representing
                  (getf value 'v))        ; a point, and a list of symbols (eg, colors).
          do (setq i (getf value 'i 0)
                   j (getf value 'j -1)
                   v (getf value 'v))
        as rc = (%set-chart-property handle name prop type i j v)
        do (pechart-print-error rc handle name i j v))
  (when (getf plist 'update t)                ; Redraw the chart, unless told not to.
    (%manage-chart-view handle chart-update)))

(defun pechart-print-error (rc handle name i j v)
  (case rc
    (#.chart-inappropriate-property
     (notify-user-at-console "Chart view [~d]: Inappropriate property ~s~%" handle name))
    (#.chart-invalid-array-property
     (notify-user-at-console "Chart view [~d]: Invalid array property ~s~%" handle name))
    (#.chart-invalid-float-property
     (notify-user-at-console "Chart view [~d]: Invalid float property ~s~%" handle name))
    (#.chart-set-failed
     (notify-user-at-console "Chart view [~d]: Error setting property ~s (~d,~d) to ~s~%"
                             handle name i j v))))

;;; The function `charting-library-version?' returns the version of the PE
;;; charting library as a dotted string (1.2.3.4), or NIL if the library was not
;;; found.

(defun charting-library-version? ()
  (when (eq charting-library-version? 'unknown)
    (let* ((buf (obtain-simple-gensym-string 16))
           (rc (c-get-charting-library-version buf 16)))
      (setq charting-library-version?
            (if (>f rc 0)
                (copy-null-terminated-string-as-text-string buf)))
      (reclaim-simple-gensym-string buf)))
  charting-library-version?)


;; `Cajoling' is like coercing, except it always succeeds.

(defun cajole-into-fixnum (property value)
  (cond ((fixnump value) value)
        ((eq value nil) 0)
        ((eq value t) 1)
        ((not (symbolp value)) 0)
        ((gensym-color-p value)
         (multiple-value-bind (r g b)
             (rgb-from-color value)
           (rgb r g b)))
        ((rgb-color-p value) (rgb-color-value value)) ; TODO: RGBA colors
        ((pechart-enum-value value))
        (t
         (notify-user-at-console "Unknown value for chart view property ~A: ~A~%" property value)
         0)))

;; Must be called in temporary float context.
(defun cajole-into-float (value)
  (cond ((fixnump value)
         (coerce-fixnum-to-gensym-float value))
        ((managed-float-p value)
         (managed-float-value value))
        (t
         0.0)))

(defun cajole-into-string (value)
  (cond ((wide-string-p value) value)
        ((symbolp value) (stringw value))
        (t #w"")))


(defun chart-set-int-array (handle name prop i j value)
  (cond ((atom value)
         (c-chart-set-int handle prop i j (cajole-into-fixnum name value)))
        (t
         (loop for e in value
               for k from i
               as rc = (c-chart-set-int handle prop k j (cajole-into-fixnum name e))
               do (pechart-print-error rc handle name k j e)))))

(defun chart-set-string-array (handle name prop i j value)
  (cond ((atom value)
         (c-chart-set-string handle prop i j (cajole-into-string value)))
        (t
         (loop for e in value
               for k from i
               as rc = (c-chart-set-string handle prop k j (cajole-into-string e))
               do (pechart-print-error rc handle name k j e)))))

(defun chart-set-double-array (handle name prop i j value)
  name
  (with-temporary-gensym-float-creation chart-set-double-array
    (cond ((float-vector-p value)
           (c-chart-set-double-array handle prop i (float-vector-length value) value))
          ((atom value)
           (c-chart-set-double handle prop i j (cajole-into-float value)))
          ((listp value)
           (let ((n (length value)))
             (cond ((>f n maximum-oversized-managed-simple-float-array-size)
                    (loop for e in value
                          for k from i
                          do (c-chart-set-double handle prop k j (cajole-into-float e))))
                   (t
                    ;; NOTE: This loop is hardly any faster than the
                    ;; previous. Consider removing it.
                    (loop with arr = (allocate-managed-simple-float-array n)
                          for e in value
                          for k from 0
                          do (setf (float-vector-aref arr k) (cajole-into-float e))
                          finally
                            (return (prog1
                                        (c-chart-set-double-array handle prop i n arr)
                                      (reclaim-managed-simple-float-array arr)))))))))))


(def-gensym-c-function c-get-charting-library-version
    (:fixnum-int "g2ext_get_charting_library_version")
  ((:string buf)
   (:fixnum-int buflen)))

(def-gensym-c-function c-create-chart-view
    (:fixnum-int "g2ext_create_chart_view")
  ((:fixnum-int handle)
   (:wide-string title)
   (:fixnum-int chart-type)
   (:fixnum-int style16)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int dock)
   (:fixnum-int neighbor)
   (:wide-string lib)
   (:fixnum-int min-width)
   (:fixnum-int min-height)))

(def-gensym-c-function c-manage-chart-view
    (:fixnum-int "g2ext_manage_chart_view")
  ((:fixnum-int handle)
   (:fixnum-int opcode)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int format)
   (:wide-string pathname)))

(def-gensym-c-function c-chart-set-int
    (:fixnum-int "g2ext_chart_set_int")
  ((:fixnum-int handle)
   (:fixnum-int prop)
   (:fixnum-int i)
   (:fixnum-int j)
   (:fixnum-int value)))

(def-gensym-c-function c-chart-set-string
    (:fixnum-int "g2ext_chart_set_string")
  ((:fixnum-int handle)
   (:fixnum-int prop)
   (:fixnum-int i)
   (:fixnum-int j)
   (:wide-string string)))

(def-gensym-c-function c-chart-set-double
    (:fixnum-int "g2ext_chart_set_double")
  ((:fixnum-int handle)
   (:fixnum-int prop)
   (:fixnum-int i)
   (:fixnum-int j)
   (:double-float value)))

(def-gensym-c-function c-chart-set-double-array
    (:fixnum-int "g2ext_chart_set_double_array")
  ((:fixnum-int handle)
   (:fixnum-int prop)
   (:fixnum-int start)
   (:fixnum-int count)
   (:double-float-array value)))

(def-gensym-c-function c-chart-add-long-to-struct
    (:void "g2ext_chart_add_long_to_struct")
  ((:fixnum-int value)))
(def-gensym-c-function c-chart-add-str-to-struct
    (:void "g2ext_chart_add_str_to_struct")
  ((:wide-string string)))
(def-gensym-c-function c-chart-add-double-to-struct
    (:void "g2ext_chart_add_double_to_struct")
  ((:double-float value)))
(def-gensym-c-function c-chart-set-struct
    (:fixnum-int "g2ext_chart_set_struct")
  ((:fixnum-int handle)
   (:fixnum-int prop)))


;;;; Chart View Properties and Enums


;; TODO: All these symbols need to be available as completions for the G2
;; programmer. And probably should be sent over by TW on request.

;; Made with ~fmw/projects/gigasoft/getprops.pl

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter pechart-types #(b n f dw sz na fa dwa sza pt h rect struct hwnd ?? ??)))

(defun chart-property-p (symbol)
  (not (null (pechart-property-code symbol))))

(defun pechart-property-code (name)
  (let ((info? (get name 'pechart-property-info)))
    (and info?
         (logandf #xFFFF info?))))

(defun pechart-property-type (name)
  (let ((info? (get name 'pechart-property-info)))
    (and info?
         (svref pechart-types (ashf (logandf #xF0000 info?) -16)))))

(defun pechart-enum-value (name)
  (get name 'pechart-enum-info))


(defmacro def-chart-properties (name &body properties)
  `(progn
     ,@(loop for (name type value) in properties
             as type-code = (position type pechart-types)
             as packed = (logiorf (ash type-code 16) value)
             collect `(setf (get ',name 'pechart-property-info) ,packed))
     ',name))

(defmacro def-chart-enums (name &body enums)
  `(progn
     ,@(loop for (name value) in enums
             collect `(setf (get ',name 'pechart-enum-info) ,value))
     ',name))


;; --- Start of autogenerated code ---
(def-chart-properties pechart
  (3d-dialogs b 2160)
  (3d-threshold n 3076)
  (add-skirts b 4012)
  (allow-annotation-control b 2623)
  (allow-area b 3254)
  (allow-axis-hot-spots b 3084)
  (allow-axis-label-hot-spots b 3083)
  (allow-axis-page b 2937)
  (allow-bar b 3022)
  (allow-best-fit-curve b 3272)
  (allow-best-fit-curve-ii b 3414)
  (allow-best-fit-line b 3281)
  (allow-best-fit-line-ii b 3413)
  (allow-bottom-title-hot-spots b 2926)
  (allow-bubble b 3640)
  (allow-color-page b 2935)
  (allow-contour-colors b 3681)
  (allow-contour-control b 4025)
  (allow-contour-lines b 3680)
  (allow-coord-prompting b 3200)
  (allow-customization b 2165)
  (allow-data-hot-spots b 3210)
  (allow-data-labels n 3642)
  (allow-debug-output b 2629)
  (allow-exporting b 2170)
  (allow-svg-export b 2025)
  (allow-emf-export b 2026)
  (allow-wmf-export b 2027)
  (allow-font-page b 2934)
  (allow-graph-annot-hot-spots b 3229)
  (allow-graph-hot-spots b 3205)
  (allow-grid-number-hot-spots-x b 3692)
  (allow-grid-number-hot-spots-y b 3122)
  (allow-grid-number-hot-spots-z b 4057)
  (allow-histogram b 3401)
  (allow-horizontal-bar b 3416)
  (allow-horz-bar-stacked b 3419)
  (allow-horz-line-annot-hot-spots b 3233)
  (allow-horz-scroll-bar b 4006)
  (allow-jpeg-output b 2928)
  (allow-line b 3279)
  (allow-maximization b 2175)
  (allow-ole-export b 2638)
  (allow-page1 b 2930)
  (allow-page2 b 2931)
  (allow-plot-customization b 3260)
  (allow-point b 3280)
  (allow-point-hot-spots b 2605)
  (allow-points-page b 2933)
  (allow-points-plus-line b 3287)
  (allow-points-plus-spline b 3288)
  (allow-popup b 2180)
  (allow-ribbon b 3091)
  (allow-rotation b 4002)
  (allow-spline b 3274)
  (allow-step b 3067)
  (allow-stick b 3648)
  (allow-style-page b 2936)
  (allow-subset-hot-spots b 2600)
  (allow-subsets-page b 2932)
  (allow-subtitle-hot-spots b 2925)
  (allow-surface b 4043)
  (allow-surface-contour b 4045)
  (allow-surface-pixel b 4046)
  (allow-surface-shading b 4044)
  (allow-table b 3422)
  (allow-table-hot-spots b 3400)
  (allow-title-hot-spots b 2924)
  (allow-titlesdialog b 2616)
  (allow-user-interface b 2185)
  (allow-vert-line-annot-hot-spots b 3234)
  (allow-vert-scroll-bar b 4007)
  (allow-wire-frame b 4042)
  (allow-x-axis-annot-hot-spots b 3231)
  (allow-y-axis-annot-hot-spots b 3232)
  (allow-zooming n 3282)
  (alt-freq-threshold n 3405)
  (alt-frequencies na 3403)
  (annotation-color dw 3203)
  (annotations-in-front b 3208)
  (annotations-on-surfaces b 4041)
  (antialias-text b 2154)
  (antialias-graphics b 2156)
  (append-point-colors dwa 3132)
  (append-point-label-data sza 3277)
  (append-to-end b 3415)
  (append-with-no-update b 3086)
  (append-xdata fa 3658)
;  (append-xdata-ii fa 3659)
  (append-ydata fa 3276)
;  (append-ydata-ii fa 3024)
  (append-zdata fa 4049)
;  (append-zdata-ii fa 4053)
  (arrow-cursor h 2917)
  (assumes-eqdata b 3657)
  (auto-explode n 3920)
  (auto-image-reset b 2615)
  (auto-min-max-padding n 3063)
  (auto-rotation b 4003)
  (auto-scale-data b 3057)
  (auto-stat-subsets na 3300)
  (auto-xdata n 3423)
  (axes-annotation-text-size n 3243)
  (axis rect 3051)
  (axis-format-ry sz 3072)
  (axis-format-tx sz 3679)
  (axis-format-x sz 3678)
  (axis-format-y sz 3071)
  (axis-location-ry n 3146)
  (axis-location-y n 3144)
  (axis-number-spacing f 3119)
  (axis-size-ry n 3145)
  (axis-size-y n 3143)
  (axis-tick-spacing f 3171)
  (bar-border-color dw 3116)
  (bar-width f 3019)
  (best-fit-coeffs fa 3058)
  (best-fit-degree n 3273)
  (best-fit-fix b 3087)
  (bitmap-gradient-menu n 2702)
  (bitmap-gradient-mode b 2703)
  (border-type-menu n 2659)
  (border-types n 2943)
  (bottom-margin sz 3056)
  (box-plot-color dw 3088)
  (bubble-size n 3641)
  (cachebmp b 2574)

; These are deprecated "custom properties"
;  (cannotation-color dw 3204)
;  (cdata-label-type n 3915)
;  (cdata-precision n 2430)
;  (cdata-shadows b 2245)
;  (cdesk-color dw 2355)
;  (cfontsize n 2440)
;  (cforce-vertical-points n 3350)
;  (cgraph-back-color dw 2375)
;  (cgraph-data-labels b 3635)
;  (cgraph-fore-color dw 2370)
;  (cgraphplustable n 3360)
;  (cgrid-in-front b 3115)
;  (cgrid-line-control n 3105)
;  (cgrouping-percent n 3905)

  (char-set n 2927)

; These are deprecated "custom properties"
;  (clabel-bold b 2550)
;  (clabel-font sz 2545)
;  (clabel-italic b 2555)
;  (clabel-underline b 2560)
;  (cmain-title-bold b 2470)
;  (cmain-title-font sz 2465)
;  (cmain-title-italic b 2475)
;  (cmain-title-underline b 2480)
;  (cmark-data-points b 3220)
;  (cmono-desk-color dw 2285)
;  (cmono-graph-back-color dw 2305)
;  (cmono-graph-fore-color dw 2300)
;  (cmono-shadow-color dw 2295)
;  (cmono-text-color dw 2290)
;  (cmonotable-back-color dw 2315)
;  (cmonotable-fore-color dw 2310)

  (comparison-subsets n 3130)
  (contour-labels sza 3691)
  (contour-legend-precision n 3318)
  (contour-lines-colored b 3317)
  (contour-line-label-density n 3686)
  (contour-menu n 4060)
  (contour-style-legend b 3690)
  (control-belongs-to-max-dlg b 2704)

; These are deprecated "custom properties"
;  (cplotting-method n 3095)
;  (cplotting-method-ii n 3012)
;  (cpoints-to-graph n 3330)
;  (cpoints-to-graph-version n 3320)
;  (crandom-points-to-graph na 3340)
;  (crandom-subsets-to-graph na 3085)
;  (cscrollingsubsets n 3075)
;  (cshadow-color dw 2365)
;  (cshow-annotations b 3202)
;  (csubtitle-font sz 2505)
;  (csubtitlebold b 2510)
;  (csubtitleitalic b 2515)
;  (csubtitleunder-line b 2520)
;  (ctable-back-color dw 2385)
;  (ctable-font sz 2570)
;  (ctable-fore-color dw 2380)
;  (ctable-what n 3370)
;  (ctext-color dw 2360)
;  (ctreat-comps-as-normal b 3125)

  (cursor-mode n 2617)
  (cursor-page-amount n 3211)
  (cursor-point n 2619)
  (cursor-prompt-location n 3152)
  (cursor-prompt-style n 2620)
  (cursor-prompt-tracking b 2621)
  (cursor-subset n 2618)
  (curve-granularity n 3275)
  (custom b 2225)
  (custom-grid-numbers struct 3162)
  (custom-grid-numbers-ry b 3161)
  (custom-grid-numbers-tx b 3695)
  (custom-grid-numbers-x b 3163)
  (custom-grid-numbers-y b 3160)
  (custom-grid-numbers-z b 4055)
  (custom-menu na 2667)
  (custom-menu-location na 2669)
  (custom-menu-state na 2668)
  (custom-menu-text sza 2670)
  (customize-dialog-menu n 2656)

; Deprecated "custom properties"
;  (cviewing-style n 2235)

  (darktextinset b 2123)
  (dash-linethickness f 3142)
  (data-hot-spot-limit n 3251)
  (data-label-type n 3910)
  (data-point-labels sza 3643)
  (data-precision n 2425)
  (data-precision-menu n 2642)
  (data-shadow-menu n 2643)
  (data-shadows b 2240)
  (data-shadows-translucent b 2157)
  (date-time-mode n 3018)
  (date-time-show-seconds b 3129)
  (day-label-type n 3135)
  (day-light-savings b 3112)
  (de-limiter n 2950)
  (def-orientation n 2150)
  (degree-of-rotation n 4001)
  (degree-prompting b 4054)
  (delta-x n 3096)
  (deltas-per-day n 3097)
  (desk-bmp-filename sz 2690)
  (desk-bmp-handle h 2117)
  (desk-bmp-style n 2691)
  (desk-color dw 2320)
  (desk-gradient-end dw 2688)
  (desk-gradient-start dw 2687)
  (desk-gradient-style n 2689)
  (dialog-result n 2981)
  (dialog-shown b 2220)
  (dirty b 2215)
  (disable-clipping b 2944)
  (disable-3d-shadow b 3927)
  (disable-sort-plot-methods b 3147)
  (disable-symbol-fix b 2972)
  (drop-shadow-off-set-x n 2679)
  (drop-shadow-off-set-y n 2680)
  (drop-shadow-steps n 2681)
  (drop-shadow-width n 2682)

  (emf-bitmap-gradients b 2031)                ; 6.0.0.60
  (emf-type n 2029)                        ; 6.0.0.60

  (end-time f 3099)
  (eng-station-format b 3655)
  (export-dest-def n 2109)
  (export-dialog-menu n 2657)
  (export-file-def sz 2111)
  (export-size-def n 2112)
  (export-image-dpi n 2022)
  (export-image-large-font b 2024)
  (export-type-def n 2108)
  (export-unit-xdef sz 2113)
  (export-unit-ydef sz 2114)
  (extra-axis-tx struct 3694)
  (extra-axisx struct 3693)
  (fall-daylight struct 3128)
  (first-pt-label-offset n 3417)
  (fixed-font-menu n 2664)
  (fixed-fonts b 2938)
  (fixed-line-thickness b 3140)
  (fixed-spmwidth b 3141)
  (floating-bars b 3151)
  (floating-stacked-bars b 3424)
  (focal-rect b 2632)
  (font-size n 2435)
  (font-size-alcntl f 2949)
  (font-size-axis-cntl f 3041)
  (font-size-cpcntl f 2948)
  (font-size-global-cntl f 2634)
  (font-size-gncntl f 2947)
  (font-size-legend-cntl f 3042)
  (font-size-mbcntl f 2946)
  (font-size-menu n 2641)
  (font-size-mscntl f 2945)
  (font-size-tbcntl f 2121)
  (font-size-title-cntl f 2635)
  (force-right-y-axis b 3286)
  (force-top-x-axis b 3672)
  (force-vert-points-menu n 3431)
  (force-vertical-points n 3345)
  (format-table b 3421)
  (gradient-bars n 3178)
  (graph rect 3049)
  (graph-annot-back-color dw 3176)
  (graph-annotation-axis na 3002)
  (graph-annotation-color dwa 3236)
  (graph-annotation-hot-spot na 3089)
  (graph-annotation-shadow na 3322)
  (graph-annotation-shadows b 3321)
  (graph-annotation-text sza 3293)
  (graph-annotation-text-size n 3242)
  (graph-annotation-type na 3246)
  (graph-annotation-x fa 3291)
  (graph-annotation-y fa 3292)
  (graph-annotation-z fa 4040)
  (graph-annotationsizecntl f 3174)
  (graph-annotmoveable n 2324)
  (graph-annottextdodge n 2322)
  (graph-annottextlocation na 2321)
  (graph-annot-min-symbol-size n 2028)
  (graph-back-color dw 2340)
  (graph-bmp-filename sz 2695)
  (graph-bmp-handle h 2118)
  (graph-bmp-style n 2696)
  (graph-data-labels b 3630)
  (graph-fore-color dw 2335)
  (graph-gradient-end dw 2693)
  (graph-gradient-start dw 2692)
  (graph-gradient-style n 2694)
  (graph-loc struct 3023)
  (graph-plus-table n 3355)
  (graph-plus-table-menu n 3430)
  (grid-aspect f 3124)
  (grid-hot-spot-value fa 3123)
  (grid-in-front b 3110)
  (grid-in-front-menu n 3166)
  (grid-line-control n 3100)
  (grid-line-menu n 3164)
  (grid-style n 3032)
  (group-percent-menu n 3926)
  (grouping-percent n 3900)
  (hand-cursor h 2919)
  (hatch-back-color dw 2941)
  (help-file-name sz 2923)
  (help-menu n 2658)
  (hide-intersecting-text n 2678)
  (hide-export-image-dpi b 2023)
  (hide-print-dpi b 2020)
  (horz-line-annot-hot-spot na 3138)
  (horz-line-annotation fa 3213)
  (horz-line-annotation-axis na 3003)
  (horz-line-annotation-color dwa 3217)
  (horz-line-annotation-text sza 3214)
  (horz-line-annotation-type na 3216)
  (horz-scroll-pos n 3253)
  (hot-spot-data struct 2610)
  (hot-spot-size n 3081)
  (hour-glass-threshold n 3252)
  (hscroll-style n 3331)
  (image-adjust-bottom n 2985)
  (image-adjust-left n 2982)
  (image-adjust-right n 2983)
  (image-adjust-top n 2984)
  (image-map-ellips rect 2126)
  (image-map-polys rect 2124)
  (include-data-labels-menu n 3696)
  (initial-scale-for-rydata n 3235)
  (initial-scale-for-txdata n 3663)
  (initial-scale-for-xdata n 3600)
  (initial-scale-for-ydata n 3035)
  (initial-scale-for-zdata n 4051)
  (invalid b 2905)
  (inverted-ry-axis b 3034)
  (inverted-tx-axis b 3675)
  (inverted-x-axis b 3674)
  (inverted-y-axis b 3033)
  (inverted-z-axis b 4023)
  (jpg-quality n 2686)
  (keydown-data struct 2612)
  (label-bold b 2530)
  (label-font sz 2525)
  (label-italic b 2535)
  (label-underline b 2540)
  (last-menu-index n 2675)
  (last-mouse-move pt 2637)
  (last-sub-menu-index n 2676)
  (left-edge-spacing f 3117)
  (left-margin sz 3052)
  (legend-annotation-axis na 3008)
  (legend-annotation-color dwa 2627)
  (legend-annotation-text sza 2626)
  (legend-annotation-type na 2625)
  (legend-location n 3082)
  (legend-location-menu n 2661)
  (legend-style n 2975)
  (line-annotation-text-size n 3244)
  (line-gap-threshold f 3212)
  (line-shadows b 3177)
  (log-scale-exp-labels b 3009)
  (log-tick-threshold n 3101)
  (logical-limit n 3064)
  (logical-loc rect 2210)
  (long-x-axis-tick-menu n 2674)
  (long-y-axis-tick-menu n 2673)
  (lower-bound-text sz 3030)
  (lower-bound-value f 3020)
  (main-title sz 2105)
  (main-title-bold b 2450)
  (main-title-font sz 2445)
  (main-title-italic b 2455)
  (main-title-underline b 2460)
  (manual-contour-line f 4027)
  (manual-contour-max f 4029)
  (manual-contour-min f 4028)
  (manual-contour-scale-control n 4030)
  (manual-max-data-string sz 3410)
  (manual-max-point-label sz 3409)
  (manual-max-ry f 3250)
  (manual-max-tx f 3666)
  (manual-max-x f 3625)
  (manual-max-y f 3060)
  (manual-max-z f 3683)
  (manual-min-ry f 3245)
  (manual-min-tx f 3665)
  (manual-min-x f 3620)
  (manual-min-y f 3055)
  (manual-min-z f 3682)
  (manual-ry-axis-line f 3267)
  (manual-ry-axis-tick f 3266)
  (manual-ry-axis-tickn-line b 3265)
  (manual-scale-control-ry n 3240)
  (manual-scale-control-tx n 3664)
  (manual-scale-control-z n 3684)
  (manual-scale-controlx n 3615)
  (manual-scale-controly n 3050)
  (manual-stacked-max-y f 3406)
  (manual-stacked-min-y f 3418)
  (manual-tx-axis-line f 3671)
  (manual-tx-axis-tick f 3670)
  (manual-tx-axis-tickn-line b 3669)
  (manual-x-axis-line f 3646)
  (manual-x-axis-tick f 3645)
  (manual-x-axis-tickn-line b 3644)
  (manual-y-axis-line f 3264)
  (manual-y-axis-tick f 3263)
  (manual-y-axis-tickn-line b 3262)
  (manual-z-axis-line f 3685)
  (manual-z-axis-tick f 4020)
  (manual-z-axis-tickn-line b 4019)
  (manualslice-labellength n 3928)
  (mark-data-points b 3215)
  (mark-data-points-menu n 3168)
  (max-axis-annotation-cluster n 3296)
  (max-data-precision n 2431)
  (max-points-to-graph n 3407)
  (maximize-menu n 2655)
  (mem-bitmap h 2575)
  (mem-dc h 2580)
  (minimum-point-size n 3102)
  (mintable-fontsize n 2116)
  (modal-dialogs b 2978)
  (modeless-auto-close b 2980)
  (modeless-on-top b 2979)
  (mono-desk-color dw 2250)
  (mono-graph-back-color dw 2270)
  (mono-graph-fore-color dw 2265)
  (mono-shadow-color dw 2260)
  (mono-table-back-color dw 2280)
  (mono-table-fore-color dw 2275)
  (mono-text-color dw 2255)
  (mono-with-symbols b 2145)
  (month-label-type n 3136)
  (mouse-cursor-control b 2622)
  (mouse-wheel-function n 2127)
  (multi-axes-proportions fa 3007)
  (multi-axes-separators n 3046)
  (multi-axes-sizing n 3111)
  (multi-axes-subsets na 3001)
  (multi-axis-separator-size n 3153)
  (multi-axis-style n 3149)
  (multi-axis-style-menu n 2663)
  (multi-bottom-titles sza 2631)
  (multi-subtitles sza 2630)
  (negative-from-x-axis b 3261)
  (no-custom-parms b 2921)
  (no-drop-cursor h 2920)
  (no-grid-line-multiples b 3092)
  (no-help b 2922)
  (no-hidden-lines-in-area b 3061)
  (no-random-points-to-export b 3653)
  (no-random-points-to-graph b 3408)
  (no-scrolling-subset-control b 3065)
  (no-stacked-data b 3305)
  (no-surface-polygon-borders b 4009)
  (nosmarttableplacement b 2976)
  (null-data-gaps b 3066)
  (null-data-value f 3268)
  (null-data-value-x f 3656)
  (null-data-value-z f 4050)
  (object-in-server b 2910)
  (object-type n 2100)
  (ohlc-min-width n 3109)
  (old-scaling-logic b 2942)
  (one-legend-per-line b 2167)
  (overlap-multi-axes na 3059)
  (page-height n 2205)
  (page-width n 2200)
  (painting b 2916)
  (parental-control hwnd 2915)
  (percent-or-value-menu n 3925)
  (plot-method-menu n 3165)
  (plotting-method n 3090)
  (plotting-method-ii n 3011)
  (plotting-methods na 3103)                ; Added -fmw, 5/11/05
  (png-is-interlaced b 2685)
  (png-is-transparent b 2683)
  (png-transparent-color dw 2684)
  (point-colors dwa 3258)
  (point-hatch na 3114)
  (point-label-rows n 3433)
  (point-labels sza 2130)
  (point-padding f 3427)
  (point-padding-area f 3428)
  (point-padding-bar f 3429)
  (point-size n 3269)
  (point-types na 3156)
  (points n 2120)
  (points-to-graph n 3325)
  (points-to-graph-init n 3310)
  (points-to-graph-version n 3315)
  (polar-line-threshold f 3805)
  (polar-tick-threshold f 3804)
  (polar30-deg-threshold f 3806)
  (poly-data struct 4014)
  (poly-mode n 4013)
  (prepare-images b 2155)
  (print-dpi n 2019)
  (print-style-control n 2705)
  (print-technology n 2021)
  (quick-style n 2672)
  (quick-style-menu n 2671)
  (random-points-to-graph na 3335)
  (random-subsets-to-graph na 3080)
  (render-engine n 2153)
  (reset-gdicache b 4032)
  (right-edge-spacing f 3118)
  (right-margin sz 3054)
  (rotation-detail n 4005)
  (rotation-increment n 4004)
  (rotation-menu n 4059)
  (rotation-speed n 4011)
  (ry-axis-color dw 3037)
  (ry-axis-comparison-subsets n 3225)
  (ry-axis-label sz 3255)
  (ry-axis-line-limit n 3184)
  (ry-axis-long-ticks b 3044)
  (ry-axis-scale-control n 3230)
  (ry-axis-whole-numbers b 3180)
  (sb-code n 2106)
  (sb-pos n 2107)
  (scale-for-rydata n 3256)
  (scale-for-txdata n 3668)
  (scale-for-xdata n 3605)
  (scale-for-ydata n 3040)
  (scale-for-zdata n 4052)
  (scale-symbols sz 2986)
  (scrolling-factor n 3426)
  (scrolling-horz-zoom b 3652)
  (scrolling-range n 3425)
  (scrolling-scale-control b 3175)
  (scrolling-subsets n 3070)
  (scrolling-vert-zoom b 3069)
  (separator-menu b 2654)
  (shadedpolygon-borders b 4056)
  (shading-style n 4031)
  (shadow-color dw 2330)
  (show-all-table-annotations b 2665)
  (show-annotations b 3290)
  (show-annotations-menu n 3169)
  (show-bounding-box n 4010)
  (show-bounding-box-menu n 4058)
  (show-contour n 4024)
  (show-contour-legends b 4026)
  (show-graph-annotations b 3223)
  (show-horz-line-annotations b 3227)
  (show-legend b 2666)
  (show-legend-menu n 2660)
  (show-margins n 3316)
  (show-pie-labels n 3921)  
  (show-pie-legend b 3922)  
  (show-polar-grid n 3802)
  (show-ry-axis n 3028)
  (show-table-annotation b 2968)
  (show-table-annotations-menu n 2662)
  (show-tick-mark-ry n 3107)
  (show-tick-mark-tx n 3689)
  (show-tick-mark-x n 3108)
  (show-tick-mark-y n 3106)
  (show-tx-axis n 3676)
  (show-vert-line-annotations b 3228)
  (show-x-axis n 3029)
  (show-x-axis-annotations b 3224)
  (show-y-axis n 3027)
  (show-y-axis-annotations b 3226)
  (show-z-axis n 4018)
  (show-z-axis-line-annotations b 4035)
  (simple-line-legend b 2973)
  (simple-point-legend b 2974)
  (size-ns-cursor h 2939)
  (slice-hatching n 3923)
  (slice-start-location n 3924)
  (smart-grid b 3801)
  (smith-chart n 3800)
  (special-date-time-mode b 3687)
  (special-scaling-ry n 3094)
  (special-scaling-y n 3093)
  (specific-plot-mode n 3021)
  (specific-plot-mode-color b 3062)
  (speed-boost n 3104)
  (spring-daylight struct 3127)
  (start-time f 3098)
  (stop b 2677)
  (subset-by-point b 2636)
  (subset-colors dwa 2190)
  (subset-degree na 3068)
  (subset-for-point-colors na 3155)
  (subset-for-point-types na 3157)
  (subset-hatch na 2940)
  (subset-labels sza 2125)
  (subset-line-types na 3271)
  (subset-obstacles na 2323)
  (subset-point-types na 3270)
  (subset-shades dwa 2195)
  (subsets n 2115)
  (subsets-to-legend na 2624)
  (subtitle sz 2110)
  (subtitle-bold b 2490)
  (subtitle-font sz 2485)
  (subtitle-italic b 2495)
  (subtitle-underline b 2500)
  (surface-polygon-borders b 4009)
  (symbol-frequency n 3289)
  (ta-border n 2962)
  (ta-grid-line-control n 2967)
  (taaxis-location n 2966)
  (taback-color dw 2963)
  (table-back-color dw 2350)
  (table-bmp-filename sz 2700)
  (table-bmp-handle h 2119)
  (table-bmp-style n 2701)
  (table-comparison-subsets b 3420)
  (table-font sz 2565)
  (table-fore-color dw 2345)
  (table-gradient-end dw 2698)
  (table-gradient-start dw 2697)
  (table-gradient-style n 2699)
  (table-what n 3365)
  (table-what-menu n 3432)
  (tacolor dwa 2955)
  (tacolumn-width na 2959)
  (tacolumns n 2952)
  (tafont sz 2970)
  (tafonts sza 2971)
  (tafore-color dw 2964)
  (taheader-column b 2958)
  (taheader-orientation n 2960)
  (taheader-rows n 2957)
  (tahot-spot na 2956)
  (tajustification na 2969)
  (talocation n 2961)
  (target-points-to-table n 3404)
  (tarows n 2951)
  (tatext sza 2954)
  (tatext-size n 2965)
  (tatype na 2953)
  (text-color dw 2325)
  (text-rendering-hint n 2033)                ; 6.0.0.60
  (text-shadows n 2122)
  (tick-color dw 3159)
  (tick-style n 3158)
  (time-label-type n 3134)
  (top-margin sz 3053)
  (treat-comparisons-menu n 3167)
  (treat-comps-as-normal b 3120)
  (triangle-annotation-adj b 3126)
  (tx-axis-color dw 3677)
  (tx-axis-comparison-subsets n 3661)
  (tx-axis-label sz 3667)
  (tx-axis-line-limit n 3186)
  (tx-axis-long-ticks b 3079)
  (tx-axis-scale-control n 3662)
  (tx-axis-whole-numbers b 3182)
  (undo-zoom-menu n 3170)
  (upper-bound-text sz 3025)
  (upper-bound-value f 3015)
; Don't let user change these settings
;  (using-xdata-ii b 3016)
;  (using-ydata-ii b 3017)
;  (using-zdata-ii b 4047)
  (vboundary-types n 3010)
  (vert-line-annot-hot-spot na 3139)
  (vert-line-annotation fa 3218)
  (vert-line-annotation-color dwa 3222)
  (vert-line-annotation-text sza 3219)
  (vert-line-annotation-type na 3221)
  (vert-orient90-degrees b 3257)
  (vert-scroll-pos n 2628)
  (vgnaxis-label-location b 3121)
  (viewing-height n 4008)
  (viewing-style n 2230)
  (viewing-style-menu n 2640)
  (wdesk-color dw 2390)
  (wgraph-back-color dw 2410)
  (wgraph-fore-color dw 2405)
  (working-axes-proportions fa 3131)
  (working-axis n 3006)
  (working-table n 2977)
  (wshadow-color dw 2400)
  (wtable-back-color dw 2420)
  (wtable-fore-color dw 2415)
  (wtext-color dw 2395)
  (x-axis-annotation fa 3297)
  (x-axis-annotation-color dwa 3237)
  (x-axis-annotation-text sza 3298)
  (x-axis-color dw 3038)
  (x-axis-label sz 3000)
  (x-axis-line-limit n 3185)
  (x-axis-long-ticks b 3078)
  (x-axis-number-spacing f 3172)
  (x-axis-on-top b 3673)
  (x-axis-scale-control n 3610)
  (x-axis-tick-spacing f 3173)
  (x-axis-vert-numbering b 3654)
  (x-axis-whole-numbers b 3181)
  (xdata fa 2135)
;  (xdata-ii fa 3013)
  (xzback-color dw 4015)
  (y-axis-annotation fa 3299)
  (y-axis-annotation-axis na 3004)
  (y-axis-annotation-color dwa 3238)
  (y-axis-annotation-text sza 3201)
  (y-axis-color dw 3036)
  (y-axis-label sz 3005)
  (y-axis-line-limit n 3183)
  (y-axis-long-ticks b 3043)
  (y-axis-on-right b 3026)
  (y-axis-scale-control n 3045)
  (y-axis-vert-grid-numbers b 3113)
  (y-axis-whole-numbers b 3179)
  (yback-color dw 4016)
  (ydata fa 2140)
;  (ydata-ii fa 3014)
  (year-label-type n 3137)
  (year-month-day-prompt n 3133)
  (z-axis-color dw 4017)
  (z-axis-label sz 4000)
  (z-axis-line-annotation fa 4036)
  (z-axis-line-annotation-color dwa 4039)
  (z-axis-line-annotation-text sza 4037)
  (z-axis-line-annotation-type na 4038)
  (z-axis-long-ticks b 4021)
  (z-axis-whole-numbers b 4061)
  (zdata fa 2900)
;  (zdata-ii fa 4048)
  (zdistance f 4022)
  (zero-degree-offset n 3803)
  (zoom-cursor h 2918)
  (zoom-interface-only n 3247)
  (zoom-limits n 3319)
  (zoom-max-axis n 3048)
  (zoom-max-ry f 3074)
  (zoom-max-tx f 3698)
  (zoom-max-x f 3249)
  (zoom-max-y f 3285)
  (zoom-min-axis n 3047)
  (zoom-min-ry f 3073)
  (zoom-min-tx f 3697)
  (zoom-min-x f 3248)
  (zoom-min-y f 3284)
  (zoom-mode b 3283)
  (zoom-style n 3154)
  
  ;; New chart properties. Are not supported by GigaSoft PE chart lib.
  ;; Used only by JChart lib.
  (enable-pie-tooltips b 10000)
  (show-pie-labels-inside b 10001)
  (show-pie-zero-data b 10002))

(def-chart-enums pechart
  (first-default-tab 0)
  (idexportbutton 1015)
  (idmaximizebutton 1016)
  (idoriginalbutton 1109)
  (peac-auto 0)
  (peac-log 2)
  (peac-normal 1)
  (peadl-datapointlabels 3)
  (peadl-datavalues 1)
  (peadl-none 0)
  (peadl-pointlabels 2)
  (peae-allsubsets 1)
  (peae-indsubsets 2)
  (peae-none 0)
  (peas-avgap 3)
  (peas-avgpp 54)
  (peas-m1sdap 7)
  (peas-m1sdpp 58)
  (peas-m2sdap 8)
  (peas-m2sdpp 59)
  (peas-m3sdap 9)
  (peas-m3sdpp 60)
  (peas-maxap 2)
  (peas-maxpp 53)
  (peas-minap 1)
  (peas-minpp 52)
  (peas-p1sdap 4)
  (peas-p1sdpp 55)
  (peas-p2sdap 5)
  (peas-p2sdpp 56)
  (peas-p3sdap 6)
  (peas-p3sdpp 57)
  (peas-pareto-asc 90)
  (peas-pareto-dec 91)
  (peas-sumpp 51)
  (peaui-all 1)
  (peaui-disablekeyboard 2)
  (peaui-disablemouse 3)
  (peaui-none 0)
  (peaxd-include-sat-sun 0)
  (peaxd-no-weekends 1)
  (peaz-horizontal 1)
  (peaz-horzandvert 3)
  (peaz-none 0)
  (peaz-vertical 2)
  (pebfd-2nd 0)
  (pebfd-3rd 1)
  (pebfd-4th 2)
  (pebg-transparent 1)
  (pebs-bitblt-bottom-center 7)
  (pebs-bitblt-bottom-left 6)
  (pebs-bitblt-bottom-right 8)
  (pebs-bitblt-center 9)
  (pebs-bitblt-top-center 4)
  (pebs-bitblt-top-left 3)
  (pebs-bitblt-top-right 5)
  (pebs-large 2)
  (pebs-medium 1)
  (pebs-no-bmp 0)
  (pebs-small 0)
  (pebs-stretchblt 1)
  (pebs-tiled-bitblt 2)
  (pecg-coarse 0)
  (pecg-fine 2)
  (pecg-medium 1)
  (pecm-datacross 2)
  (pecm-datasquare 3)
  (pecm-floatingxonly 6)
  (pecm-floatingxy 5)
  (pecm-floatingy 4)
  (pecm-floatingyonly 7)
  (pecm-grayed 1)
  (pecm-hide 2)
  (pecm-nocursor 0)
  (pecm-point 1)
  (pecm-show 0)
  (pecml-above-separator 1)
  (pecml-below-separator 2)
  (pecml-bottom 3)
  (pecml-top 0)
  (pecms-checked 1)
  (pecms-unchecked 0)
  (pecontrol-3d 312)
  (pecontrol-graph 300)
  (pecontrol-pgraph 308)
  (pecontrol-pie 302)
  (pecontrol-sgraph 304)
  (pecpl-top-left 0)
  (pecpl-top-right 1)
  (pecps-none 0)
  (pecps-xvalue 1)
  (pecps-xyvalues 3)
  (pecps-yvalue 2)
  (pedlt-1-char 1)
  (pedlt-3-char 0)
  (pedlt-no-day-number 3)
  (pedlt-no-day-prompt 2)
  (pedlt-percentage 0)
  (pedlt-value 1)
  (pedo-driverdefault 0)
  (pedo-landscape 1)
  (pedo-portrait 2)
  (pedp-disabled 1)
  (pedp-enabled 0)
  (pedp-inside-top 2)
  (peds-3d 2)
  (peds-none 0)
  (peds-shadows 1)
  (pedtm-delphi 2)
  (pedtm-none 0)
  (pedtm-vb 1)
  (peedd-clipboard 0)
  (peedd-file 1)
  (peedd-printer 2)
  (peesd-inches 2)
  (peesd-millimeters 1)
  (peesd-no-size-or-pixel 0)
  (peesd-points 3)

  (peet-emf-gdi 0)                        ; 6.0.0.60 emf-type values
  (peet-emf-gdiplus 1)
  (peet-emf-plusdual 2)
  (peet-emf-plusonly 3)

  (peetd-bmp 1)
  (peetd-jpeg 2)
  (peetd-metafile 0)
  (peetd-png 3)
  (peetd-text 4)
  (pefs-large 0)
  (pefs-medium 1)
  (pefs-small 2)
  (pefvp-auto 0)
  (pefvp-horz 2)
  (pefvp-slanted 3)
  (pefvp-vert 1)
  (pegam-not-moveable 0)
  (pegam-pointer 1)
  (pegat-addpolypoint 75)
  (pegat-addtext 85)
  (pegat-arrow-e 94)
  (pegat-arrow-n 92)
  (pegat-arrow-ne 93)
  (pegat-arrow-nw 99)
  (pegat-arrow-s 96)
  (pegat-arrow-se 95)
  (pegat-arrow-sw 97)
  (pegat-arrow-w 98)
  (pegat-bottomright 47)
  (pegat-cross 2)
  (pegat-dash 72)
  (pegat-dashdotdotline 42)
  (pegat-dashdotline 41)
  (pegat-dashline 39)
  (pegat-diamond 7)
  (pegat-diamondsolid 8)
  (pegat-dot 3)
  (pegat-dotline 40)
  (pegat-dotsolid 4)
  (pegat-downtriangle 11)
  (pegat-downtrianglesolid 12)
  (pegat-ellipse-dash 65)
  (pegat-ellipse-dashdot 67)
  (pegat-ellipse-dashdotdot 68)
  (pegat-ellipse-dot 66)
  (pegat-ellipse-fill 71)
  (pegat-ellipse-medium 69)
  (pegat-ellipse-thick 70)
  (pegat-ellipse-thin 64)
  (pegat-endpolygon 76)
  (pegat-endpolyline-dash 80)
  (pegat-endpolyline-dashdot 82)
  (pegat-endpolyline-dashdotdot 83)
  (pegat-endpolyline-dot 81)
  (pegat-endpolyline-medium 78)
  (pegat-endpolyline-thick 79)
  (pegat-endpolyline-thin 77)
  (pegat-extraextrathinsolid 91)
  (pegat-extrathicksolid 89)
  (pegat-extrathinsolid 90)
  (pegat-large-obstacle 102)
  (pegat-largecross 26)
  (pegat-largediamond 31)
  (pegat-largediamondsolid 32)
  (pegat-largedot 27)
  (pegat-largedotsolid 28)
  (pegat-largedowntriangle 35)
  (pegat-largedowntrianglesolid 36)
  (pegat-largeplus 25)
  (pegat-largesquare 29)
  (pegat-largesquaresolid 30)
  (pegat-largeuptriangle 33)
  (pegat-largeuptrianglesolid 34)
  (pegat-linecontinue 45)
  (pegat-medium-obstacle 101)
  (pegat-mediumsolidline 43)
  (pegat-mediumthicksolid 88)
  (pegat-mediumthinsolid 87)
  (pegat-nosymbol 0)
  (pegat-nosymbol-movable 104)
  (pegat-paragraph 86)
  (pegat-pixel 73)
  (pegat-plus 1)
  (pegat-pointer 37)
  (pegat-rect-dash 49)
  (pegat-rect-dashdot 51)
  (pegat-rect-dashdotdot 52)
  (pegat-rect-dot 50)
  (pegat-rect-fill 55)
  (pegat-rect-medium 53)
  (pegat-rect-obstacle 103)
  (pegat-rect-thick 54)
  (pegat-rect-thin 48)
  (pegat-roundrect-dash 57)
  (pegat-roundrect-dashdot 59)
  (pegat-roundrect-dashdotdot 60)
  (pegat-roundrect-dot 58)
  (pegat-roundrect-fill 63)
  (pegat-roundrect-medium 61)
  (pegat-roundrect-thick 62)
  (pegat-roundrect-thin 56)
  (pegat-small-obstacle 100)
  (pegat-smallcross 14)
  (pegat-smalldiamond 19)
  (pegat-smalldiamondsolid 20)
  (pegat-smalldot 15)
  (pegat-smalldotsolid 16)
  (pegat-smalldowntriangle 23)
  (pegat-smalldowntrianglesolid 24)
  (pegat-smallplus 13)
  (pegat-smallsquare 17)
  (pegat-smallsquaresolid 18)
  (pegat-smalluptriangle 21)
  (pegat-smalluptrianglesolid 22)
  (pegat-square 5)
  (pegat-squaresolid 6)
  (pegat-startpoly 74)
  (pegat-starttext 84)
  (pegat-thicksolidline 44)
  (pegat-thinsolidline 38)
  (pegat-topleft 46)
  (pegat-uptriangle 9)
  (pegat-uptrianglesolid 10)

  (pegat-vector-small 181)                ; New annotation types for 6.0.0.58
  (pegat-vector-medium 182)
  (pegat-vector-large 183)
  (pegat-arrow-small 184)
  (pegat-arrow-medium 185)
  (pegat-arrow-large 186)
  (pegat-pointer-vector-small 187)
  (pegat-pointer-vector-medium 188)
  (pegat-pointer-vector-large 189)
  (pegat-pointer-arrow-small 190)
  (pegat-pointer-arrow-medium 191)
  (pegat-pointer-arrow-large 192)

  (pept-gdi 0)                                ; Some new enums for 6.0.0.58
  (pept-gdiplus 1)
  (pezl-none 0)
  (pezl-axis 1)
  (pezl-axis-horizontal 2)
  (pezl-axis-vertical 3)
  (pezl-axis-shape 4)
  (pezl-axis-square 5)
  (pesm-show-annotations 0)
  (pesm-always 1)
  (pesm-never 2)

  (pere-gdi 0)                                ; Expose render-engine to users
  (pere-hybrid 1)
  (pere-gdiplus 2)

  (peglc-both 0)
  (peglc-none 3)
  (peglc-xaxis 2)
  (peglc-yaxis 1)
  (pegpm-area 3)
  (pegpm-areastacked 4)
  (pegpm-areastackedpercent 5)
  (pegpm-bar 1)
  (pegpm-barstacked 6)
  (pegpm-barstackedpercent 7)
  (pegpm-boxplot 29)
  (pegpm-bubble 12)
  (pegpm-contourcolors 24)
  (pegpm-contourlines 23)
  (pegpm-demographicpyramid 32)                ; 6.0.0.60
  (pegpm-highlowarea 33)                ; 6.0.0.60
  (pegpm-highlowbar 25)
  (pegpm-highlowclose 27)
  (pegpm-highlowline 26)
  (pegpm-histogram 10)
  (pegpm-horizontalbar 18)
  (pegpm-horzbarstacked 19)
  (pegpm-horzbarstackedpercent 20)
  (pegpm-line 0)
  (pegpm-openhighlowclose 28)
  (pegpm-point 2)
  (pegpm-pointsplusbfc 13)
  (pegpm-pointsplusbfcgraphed 14)
  (pegpm-pointsplusbfl 8)
  (pegpm-pointsplusbflgraphed 9)
  (pegpm-pointsplusline 17)
  (pegpm-pointsplusspline 15)
  (pegpm-ribbon 22)
  (pegpm-specificplotmode 11)
  (pegpm-spline 16)
  (pegpm-step 21)
  (pegpm-stick 4)
  (pegpt-both 2)
  (pegpt-graph 0)
  (pegpt-table 1)
  (pegs-dash 3)
  (pegs-dot 2)
  (pegs-onepixel 4)
  (pegs-thick 1)
  (pegs-thin 0)

  (pegs-no-gradient 0)
  (pegs-vertical 1)
  (pegs-horizontal 2)
  (pegs-linear-bar-vertical 3)
  (pegs-linear-bar-horizontal 4)
  (pegs-linear-bar-down 5)
  (pegs-linear-bar-up 6)
  (pegs-linear-diagonal-down 7)
  (pegs-linear-diagonal-up 8)
  (pegs-rectangle-cross 9)
  (pegs-rectangle-plus 10)
  (pegs-radial-centered 11)
  (pegs-radial-bottom-right 12)
  (pegs-radial-top-right 13)
  (pegs-radial-bottom-left 14)
  (pegs-radial-top-left 15)

  (pehs-annotation 6)
  (pehs-bdiagonal 3)
  (pehs-cross 4)
  (pehs-datapoint 5)
  (pehs-diagcross 5)
  (pehs-fdiagonal 2)
  (pehs-graph 3)
  (pehs-horizontal 0)
  (pehs-horzlineannotation 9)
  (pehs-maintitle 11)
  (pehs-multibottomtitle 14)
  (pehs-multisubtitle 13)
  (pehs-none 0)
  (pehs-point 2)
  (pehs-ryaxisgridnumber 20)
  (pehs-subset 1)
  (pehs-subtitle 12)
  (pehs-table 4)
  (pehs-tableannotation 23)
  (pehs-tableannotation19 42)
  (pehs-txaxisgridnumber 22)
  (pehs-vertical 1)
  (pehs-vertlineannotation 10)
  (pehs-xaxis 18)
  (pehs-xaxisannotation 7)
  (pehs-xaxisgridnumber 21)
  (pehs-xaxislabel 16)
  (pehs-yaxis 17)
  (pehs-yaxisannotation 8)
  (pehs-yaxisgridnumber 19)
  (pehs-yaxislabel 15)
  (pehs-zaxisgridnumber 43)
  (pehss-large 2)
  (pehss-medium 1)
  (pehss-scrolling-pointlabels 0)
  (pehss-small 0)
  (pehss-stationary-pointlabels 1)
  (pelat-gridline 8)
  (pelat-gridlineii 15)
  (pelat-gridtick 7)
  (pelat-gridtickii 14)
  (pell-bottom 1)
  (pell-left 2)
  (pell-right 3)
  (pell-top 0)
  (pels-1-line 1)
  (pels-1-line-inside-axis 2)
  (pels-1-line-inside-overlap 4)
  (pels-1-line-top-of-axis 3)
  (pels-2-line 0)
  (pelt-dash 1)
  (pelt-dashdot 3)
  (pelt-dashdotdot 4)
  (pelt-dot 2)
  (pelt-extraextrathinsolid 13)
  (pelt-extrathicksolid 11)
  (pelt-extrathinsolid 12)
  (pelt-mediumsolid 5)
  (pelt-mediumthicksolid 10)
  (pelt-mediumthinsolid 9)
  (pelt-thicksolid 6)
  (pelt-thinsolid 0)
  (pemas-group-all-axes 0)
  (pemas-medium 2)
  (pemas-none 0)
  (pemas-separate-axes 1)
  (pemas-thick 3)
  (pemas-thickplustick 4)
  (pemas-thin 1)
  (pemc-grayed 2)
  (pemc-hide 0)
  (pemc-show 1)
  (pemlt-1-char 1)
  (pemlt-3-char 0)
  (pemlt-no-month-prompt 2)
  (pemps-large 3)
  (pemps-medium 2)
  (pemps-none 0)
  (pemps-small 1)
  (pemsc-max 2)
  (pemsc-min 1)
  (pemsc-minmax 3)
  (pemsc-none 0)
  (pemwf-horz-scroll 1)
  (pemwf-no-scroll 2)
  (pemwf-vert-scroll 0)
  (peplm-lines 1)
  (peplm-points 0)
  (peplm-points-and-lines 2)
  (peplm-surface 1)
  (peplm-surface-w-contour 4)
  (peplm-surface-w-pixels 3)
  (peplm-surface-w-shading 2)
  (peplm-wireframe 0)
  (pepm-3dbar 2)
  (pepm-polygondata 3)
  (pepm-scatter 4)
  (pepm-surfacepolygons 1)
  (peps-large 2)
  (peps-medium 1)
  (peps-micro 3)
  (peps-small 0)
  (pepsc-current-style 1)
  (pepsc-default-mono 2)
  (pepsc-none 0)
  (pept-arrow-e 94)
  (pept-arrow-n 92)
  (pept-arrow-ne 93)
  (pept-arrow-nw 99)
  (pept-arrow-s 96)
  (pept-arrow-se 95)
  (pept-arrow-sw 97)
  (pept-arrow-w 98)
  (pept-cross 1)
  (pept-dash 72)
  (pept-diamond 6)
  (pept-diamondsolid 7)
  (pept-dot 2)
  (pept-dotsolid 3)
  (pept-downtriangle 10)
  (pept-downtrianglesolid 11)
  (pept-pixel 73)
  (pept-plus 0)
  (pept-square 4)
  (pept-squaresolid 5)
  (pept-uptriangle 8)
  (pept-uptrianglesolid 9)
  (peptgi-firstpoints 0)
  (peptgi-lastpoints 1)
  (peptgv-random 1)
  (peptgv-sequential 0)
  (peqs-dark-inset 9)
  (peqs-dark-line 11)
  (peqs-dark-no-border 12)
  (peqs-dark-shadow 10)
  (peqs-light-inset 1)
  (peqs-light-line 3)
  (peqs-light-no-border 4)
  (peqs-light-shadow 2)
  (peqs-medium-inset 5)
  (peqs-medium-line 7)
  (peqs-medium-no-border 8)
  (peqs-medium-shadow 6)
  (peqs-no-style 0)
  (perd-fulldetail 2)
  (perd-plottingmethod 1)
  (perd-wireframe 0)
  (peri-decby1 5)
  (peri-decby10 8)
  (peri-decby15 9)
  (peri-decby2 6)
  (peri-decby5 7)
  (peri-incby1 4)
  (peri-incby10 1)
  (peri-incby15 0)
  (peri-incby2 3)
  (peri-incby5 2)
  (pesa-all 0)
  (pesa-axislabels 1)
  (pesa-empty 5)
  (pesa-gridnumbers 2)
  (pesa-labelonly 4)
  (pesa-none 3)
  (pesb-mouse-wheel-down 101)
  (pesb-mouse-wheel-up 100)
  (pesbb-always 1)
  (pesbb-never 2)
  (pesbb-whilerotating 0)
  (pesc-admittance 3)
  (pesc-bottomcolors 4)
  (pesc-bottomlines 2)
  (pesc-none 0)
  (pesc-polar 0)
  (pesc-rose 2)
  (pesc-smith 1)
  (pesc-topcolors 3)
  (pesc-toplines 1)
  (pesh-both 1)
  (pesh-monochrome 0)
  (pespl-label 2)
  (pespl-none 3)
  (pespl-percent 1)
  (pespl-percentpluslabel 0)
  (pespm-boxplot 5)
  (pespm-highlowbar 1)
  (pespm-highlowclose 3)
  (pespm-highlowline 2)
  (pespm-none 0)
  (pespm-openhighlowclose 4)
  (pespm-highlowarea 6 )                ; 6.0.0.60
  (pess-colorshading 1)
  (pess-financial 1)
  (pess-none 0)
  (pess-whiteshading 0)
  (pesta-center 0)
  (pesta-left 1)
  (pesta-right 2)
  (pestm-ticks-hide 2)
  (pestm-ticks-inside 0)
  (pestm-ticks-outside 1)
  (petaal-bottom-center 6)
  (petaal-bottom-full-width 4)
  (petaal-bottom-left 5)
  (petaal-bottom-right 7)
  (petaal-bottom-table-spaced 9)
  (petaal-new-row 100)
  (petaal-top-center 2)
  (petaal-top-full-width 0)
  (petaal-top-left 1)
  (petaal-top-right 3)
  (petaal-top-table-spaced 8)
  (petab-drop-shadow 0)
  (petab-inset 3)
  (petab-no-border 2)
  (petab-single-line 1)
  (petaho-270 2)
  (petaho-90 1)
  (petaho-horz 0)
  (petaj-center 1)
  (petaj-left 0)
  (petaj-right 2)
  (petal-bottom-center 4)
  (petal-bottom-left 3)
  (petal-bottom-right 5)
  (petal-inside-axis 100)
  (petal-inside-axis-0 100)
  (petal-inside-axis-1 101)
  (petal-inside-axis-2 102)
  (petal-inside-axis-3 103)
  (petal-inside-axis-4 104)
  (petal-inside-axis-5 105)
  (petal-inside-bottom-center 12)
  (petal-inside-bottom-left 11)
  (petal-inside-bottom-right 13)
  (petal-inside-left-center 10)
  (petal-inside-right-center 14)
  (petal-inside-table 300)
  (petal-inside-top-center 8)
  (petal-inside-top-left 9)
  (petal-inside-top-right 15)
  (petal-left-center 2)
  (petal-outside-axis 200)
  (petal-outside-axis-0 200)
  (petal-outside-axis-1 201)
  (petal-outside-axis-2 202)
  (petal-outside-axis-3 203)
  (petal-outside-axis-4 204)
  (petal-outside-axis-5 205)
  (petal-overlap-axis 400)
  (petal-overlap-axis-0 400)
  (petal-overlap-axis-1 401)
  (petal-overlap-axis-2 402)
  (petal-overlap-axis-3 403)
  (petal-overlap-axis-4 404)
  (petal-overlap-axis-5 405)
  (petal-right-center 6)
  (petal-top-center 0)
  (petal-top-left 1)
  (petal-top-right 7)
  (petlt-12hr-am-pm 0)
  (petlt-12hr-no-am-pm 1)
  (petlt-24hr 2)

  (petrh-default 0)                        ; 6.0.0.60 text-rendering-hint values
  (petrh-single-bit-per-pixel-gridfit 1)
  (petrh-single-bit-per-pixel 2)
  (petrh-antialias-gridfit 3)
  (petrh-antialias 4)
  (petrh-clear-type-gridfit 5)

  (pets-1unit 4)
  (pets-all-text 2)
  (pets-bold-text 1)
  (pets-dash 3)
  (pets-dot 2)
  (pets-gridstyle 0)
  (pets-no-text 0)
  (pets-thick 1)
  (pets-thin 5)
  (petw-allsubsets 1)
  (petw-graphed 0)
  (pevb-bottom 2)
  (pevb-none 0)
  (pevb-top 1)
  (pevb-topandbottom 3)
  (pevs-color 0)
  (pevs-mono 1)
  (pevs-monowithsymbols 2)
  (pezio-line 2)
  (pezio-normal 0)
  (pezio-rect 1)
  (pezs-framed-rect 0)
  (pezs-ro2-not 1)
  (solid-surface-color 32001)
  (wire-frame-color 32000))
;; --- End of autogenerated code ---


;;;; Tabular Views

;; New implementation for 83b0 -fmw, 11/1/06
;;;Modified by SoftServe. Added 'font-size-change'
(defparameter tabular-view-opcodes
  '((destroy . 1)
    (insert-column . 2)
    (insert-row . 3)
    (cell-text . 4)
    (cell-icon . 5)
    (column-text . 6)
    (column-alignment . 7)
    (column-width . 8)
    (column-icon . 9)
    (setredraw . 10)
    (background-color . 11)
    (text-color . 12)
    (row-height . 13)
    (gridlines . 14)
    (sortable . 15)
    (single-selection . 16)
    (row-background-color . 17)
    (row-text-color . 18)
    (remove-column . 19)
    (select-row . 20)
    (deselect-row . 21)
    (deselect-all-rows . 22)
    (remove-row . 23)
    (remove-all-rows . 24)
    (remove-all-columns . 25)
    (check-selection-changed . 26)
    (sort-rows . 27)
    (insert-row-to-top . 28) ;added by SoftServe
    (font-size-change . 29) ;added by SoftServe
    (change-sort . 30)
    (gridline-color . 31)
    )) 

#+development
(defun print-tbv-defines ()
  (loop for (name . value) in tabular-view-opcodes doing
    (assert (fixnump value))
    (format t "#define TBV_~:@(~a~) ~d~%" (substitute #\_ #\- (string name)) value))
  (values))



(def-icp-message-type manage-tabular-view
    ((gensym-window gensym-window)
     (symbol action)
     (fixnum handle)
     (icp-tree arg))
  (manage-tabular-view-1 gensym-window action handle arg)
  (reclaim-icp-tree-with-text-strings arg))

(defun tabular-view-opcode (name)
  (cdr (assq name tabular-view-opcodes)))

(defun tbv-fixnum (thing)
  (cond ((null thing)
         -1)
        ((fixnump thing)
         thing)
        (t
         (case thing
           (left lvcfmt-left)
           (right lvcfmt-right)
           (center lvcfmt-center)
           (text-width lvscw-autosize)
           (header-width lvscw-autosize-useheader)
           ((t) 1)
           (t
            -1)))))

(defmacro %manage-tabular-view (opcode handle &optional row-id string a b c)
  `(c-manage-tabular-view ,(if (constantp opcode) `(tabular-view-opcode ,opcode) opcode)
                          ,handle
                          ,(if (null row-id) -1 `(tbv-fixnum ,row-id))
                          ,(if (null string) #w"" `(to-string ,string))
                          ,(if (null a) -1 `(tbv-fixnum ,a))
                          ,(if (null b) -1 `(tbv-fixnum ,b))
                          ,(if (null c) -1 `(tbv-fixnum ,c))))

(defun tabular-view-add-columns-1 (handle column-specs &optional clear-p)
  (when clear-p
    (%manage-tabular-view 'remove-all-columns handle))
  (loop for spec in column-specs doing
    (cond ((wide-string-p spec)
           (%manage-tabular-view 'insert-column handle nil spec))
          ((plistp spec)
           (let ((text (getf spec 'text-value))
                 (alignment (getf spec 'alignment))
                 (width (getf spec 'width 'header-width)) ; NOTE: Default is header-width.
                 (icon (getf spec 'icon -1))
                 (column (getf spec 'column -1))
                 (cells (getf spec 'cells)))
             (%manage-tabular-view 'insert-column handle column text alignment width icon)
             (when cells                ; Initial contents for new cells
               (tabular-view-modify-cells-1 handle nil column cells)))))))

(defun tabular-view-modify-columns-1 (handle column-specs &optional force-p)
  (loop for spec in column-specs
        as index from 0
        as plistp = (plistp spec)
        as text? = (if plistp (getf spec 'text-value) spec)
        as alignment? = (if plistp (getf spec 'alignment))
        as width? = (if plistp (getf spec 'width))
        as icon? = (if plistp (getf spec 'icon))
        as column = (or (if plistp (getf spec 'column)) index)
        doing
    (when (or text? force-p)
      (%manage-tabular-view 'column-text handle column text?))
    (when (or alignment? force-p)
      (%manage-tabular-view 'column-alignment handle column nil alignment?))
    (when (or width? force-p)
      (%manage-tabular-view 'column-width handle column nil width?))
    (when (or icon? force-p)
      (%manage-tabular-view 'column-icon handle column nil icon?))))

;; Spec is generated by `preprocess-tabular-view-row'. Modified by SoftServe
(defun tabular-view-add-rows-1 (handle row-specs &optional clear-p (add-to-top? nil))
  (when clear-p
    (%manage-tabular-view 'remove-all-rows handle))
  (loop for spec in row-specs
        as (row-id cells . plist) = spec
        as pos = (getf plist 'position) ; Insert position, as a row ID.
        as fg = (getf plist 'text-color)
        as bg = (getf plist 'background-color)
        doing
    (if add-to-top? 
        (%manage-tabular-view 'insert-row-to-top handle row-id nil pos fg bg)
        (%manage-tabular-view 'insert-row handle row-id nil pos fg bg))
    (tabular-view-modify-cells-1 handle row-id nil cells)))

;;; sort-column value preprocessor
(defun sort-column-value-or-stack-error (value)
  (cond ((null value)
          -1)
         ((<f value -1)
	  (current-system-case
	    (ab (ui-stack-error-1 "~A is not a valid sort column." value))))
         (t
          value)))
          
;;; sorting-order value preprocessor
(defun sorting-order-value-or-stack-error (value)
  (valid-sorting-order-or-stack-error value)
  (case value
    (ascending 1)
    (descending 0)
    (t 1)))

;;; sorting-order value validator
(defun valid-sorting-order-or-stack-error (value)
  (unless (and (symbolp value)
               (memq-p-macro value '(ascending descending)))
    (current-system-case
      (ab (ui-stack-error-1 "~A is not a valid sorting order." value)))))

;;; Update sorting action processor imlementation
(defun tabular-view-change-sort-1 (handle sort-specs)
  (loop for spec in sort-specs
        as order = (getf spec 'sorting-order)
        as column = (getf spec 'sort-column)
        doing
    (%manage-tabular-view 'change-sort
                          handle
                          (if (or (eq order 'ascending) (eq order 'descending)) column -1)
                          nil
                          (eq order 'ascending))))
  
(defun tabular-view-modify-rows-1 (handle row-specs &optional force-p)
  (loop for spec in row-specs
        as (row-id cells . plist) = spec
        as fg? = (getf plist 'text-color)
        as bg? = (getf plist 'background-color)
        doing
    (when fg?
      (%manage-tabular-view 'row-text-color handle row-id nil fg?))
    (when bg?
      (%manage-tabular-view 'row-background-color handle row-id nil bg?))
    (tabular-view-modify-cells-1 handle row-id nil cells force-p)))

;; Modifies cells along a row or a column. Row-id? and column? are the default
;; values if not specified within a cell.
(defun tabular-view-modify-cells-1 (handle row-id? column? cells &optional force-p)
  (loop for cell in cells
        for i from 0
        as text? = (if (wide-string-p cell) cell (getf cell 'text-value))
        as icon? = (if (wide-string-p cell) nil (getf cell 'icon))
        as row-id = (or (if (consp cell) (getf cell 'row-id))
                        row-id?
                        i)
        as column = (or (if (consp cell) (getf cell 'column))
                        column?
                        i)
        doing
    (when (or text? force-p)
      (%manage-tabular-view 'cell-text handle row-id text? column))
    (when icon?
      (%manage-tabular-view 'cell-icon handle row-id nil column icon?))))

(defun process-tabular-view-init-plist (native-window plist)
  (loop for (property value) on plist by #'cddr doing
    (manage-tabular-view-1 (native-window-gensym-window native-window)
                           property
                           (native-window-handle native-window)
                           value)))
;Modified by SoftServe. Added 'add-rows-to-top' option handling.
;Modified by SoftServe. Added 'font-size-change' option handling.
(defun manage-tabular-view-1 (gensym-window action handle arg)
  (case action
    (create
     (with-decoded-view-options (arg :container mdi-child) ; TODO: default container = PANE?
       (let* ((window-index
                (c-create-tabular-view handle title left top width height dock neighbor sort-column sorting-order))
              (native-window
                (make-basic-native-window gensym-window handle window-index 'g2-tabular-view container)))
         (process-view-init-plist native-window arg '(title))
         (prog1 (process-tabular-view-init-plist native-window arg)
                (reclaim-native-window native-window)))))

    (destroy
     (%manage-tabular-view 'destroy handle)
     (reclaim-native-window-by-handle gensym-window handle))

    ((add-rows rows)
     (tabular-view-add-rows-1 handle arg (eq action 'rows) nil))

    (add-rows-to-top
     (tabular-view-add-rows-1 handle arg (eq action 'rows) t))    

    (font-size-change
          (loop for elem in arg doing
       (%manage-tabular-view 'font-size-change handle nil elem)));Modified by SoftServe 

        
    ((modify-rows replace-rows)
     (tabular-view-modify-rows-1 handle arg (eq action 'replace-rows)))
    (change-sort
     (tabular-view-change-sort-1 handle arg))

    ((modify-cells replace-cells)
     (tabular-view-modify-cells-1 handle nil nil arg (eq action 'replace-cells)))

    ((add-columns columns)
     (tabular-view-add-columns-1 handle arg (eq action 'columns)))

    ((modify-columns replace-columns)
     (tabular-view-modify-columns-1 handle arg (eq action 'replace-columns)))

    (deselect-rows
     (loop for elem in arg doing
       (%manage-tabular-view 'deselect-row handle elem))
     (%manage-tabular-view 'check-selection-changed handle))

    (selected-rows
     (%manage-tabular-view 'deselect-all-rows handle)
     (loop for elem in arg doing
       (%manage-tabular-view 'select-row handle elem))
     (%manage-tabular-view 'check-selection-changed handle))

    ((container neighbor))

    (t
     (let ((opcode? (tabular-view-opcode action)))
       (cond ((null opcode?)
              ;; This is normal: all view attributes will appear here.
              #+ignore (notify-user-at-console "Unknown tabular-view action ~S~%" action))
             ((atom arg)
              (%manage-tabular-view opcode? handle arg arg arg))
             (t
              (loop for elem in arg doing
                (%manage-tabular-view opcode? handle elem elem elem))))))))

(def-gensym-c-function c-create-tabular-view
    (:fixnum-int "g2ext_create_tabular_view")
  ((:fixnum-int handle)
   (:wide-string title)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int dock)
   (:fixnum-int neighbor)
   (:fixnum-int sortColumn)
   (:fixnum-int sortAscending)))

(def-gensym-c-function c-manage-tabular-view
    (:fixnum-int "g2ext_manage_tabular_view")
  ((:fixnum-int opcode)
   (:fixnum-int handle)
   (:fixnum-int row-id)
   (:wide-string string)
   (:fixnum-int a)
   (:fixnum-int b)
   (:fixnum-int c)))
