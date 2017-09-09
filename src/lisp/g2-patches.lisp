;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module G2-PATCHES for GSI and Telewindows

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David, Ben Hyde and Peter Fandel

;;; The following provides stubs for all of those variables and
;;; functions which are only applicable to the gsi or telewindows
;;; system but which are referenced in modules included in the ab
;;; system.  In the past declare-forward-reference handled these
;;; cases but with Chestnut declare-forward-reference expands to
;;; nil and  these functions are left undefined.





;;;; Telewindows



;;; The following provides stubs for all of those variables and
;;; functions which are only applicable to the telewindows system
;;; but which are referenced in modules included in the ab system.
;;; In the past declare-forward-reference handled these cases but
;;; with Chestnut declare-forward-reference expands to nil and 
;;; these functions are left undefined.

;;; Please go though the following and if possible modify the code
;;; to omit calls to functions which are TW specific.  After doing
;;; so please comment out the stub function in this file and initial
;;; the entry. ac 1/23/91

#+(or chestnut chestnut-3) ;Chestnut3.1
(progn

(defvar compilations-were-removed-in-this-kb-module? nil)

;; VARIABLES								FILE
;; ________________________________________             		_________

(defvar current-telewindows-workstation nil)				;TELESTUBS


;; FUNCTIONS 								FILE
;; ________________________________________             		_________



(defun run-one-tw-scheduler-cycle ())	                                ;TELEWINDOWS

(defun get-telewindows-command-line-args-if-valid ())			;BOOTSTRAP

(defun send-telewindows-workstation-event (workstation event)		;TELESTUBS
  (declare (ignore workstation event)))

(defun accept-telewindows-connection-license-level ;TELESTUBS
    (gensym-window license-level)
  (declare (ignore gensym-window license-level)))

(defun accept-telewindows-connection-license-info ;TELESTUBS
    (gensym-window info)
  (declare (ignore gensym-window info)))

(defun accept-saved-user-settings-for-telewindows ;TELESTUBS
    (gensym-window user-settings-plist)
  (declare (ignore gensym-window user-settings-plist)))

(defun reroute-telewindows-connection (gensym-window protocol host port init-string) ;TELESTUBS  
  (declare (ignore gensym-window protocol host port init-string)))

(defun write-list-of-text-lines-to-gensym-window	; TELEWINDOWS  (MHD 11/10/92)
       (gensym-window list-of-text-lines font-size clear-window? new-paragraph?)
  (declare (ignore
	     gensym-window list-of-text-lines font-size
	     clear-window? new-paragraph?)))

(defun paste-for-telewindows (gensym-window text-string request-id) ; TELEWINDOWS
  (declare (ignore gensym-window text-string request-id)))          ; (LGIBSON 4/9/97)
    
(defun update-paste-availability-status-for-telewindows ; TELEWINDOWS
    (gensym-window status)
  (declare (ignore gensym-window status)))

(defun refresh-telewindow						;WINDOWS3
       (gensym-window native-window
	&optional
	left-edge-of-update-area?
	top-edge-of-update-area?
	right-edge-of-update-area?
	bottom-edge-of-update-area?)
  (declare (ignore gensym-window
		   native-window
		   left-edge-of-update-area?
		   top-edge-of-update-area?
		   right-edge-of-update-area?
		   bottom-edge-of-update-area?)))

(defun reshape-telewindow (gensym-window native-window)			;WINDOWS3
  (declare (ignore gensym-window native-window)))

(defun telewindows-check-version-of-remote-g2 (gensym-window)	    ; TELEWINDOWS
  (declare (ignore gensym-window))
  )


(defun abort-telewindows-for-protocol-out-of-synch-case-6 ())
(defun abort-telewindows-top-level (reason)
  (declare (ignore reason)))

(defun telewindows-authorized-for-japanese-p (gensym-window)
  (declare (ignore gensym-window)))
(defun telewindows-authorized-for-korean-p (gensym-window)
  (declare (ignore gensym-window)))
(defun telewindows-authorized-for-chinese-p (gensym-window)
  (declare (ignore gensym-window)))

(defun telewindows-icp-socket?-function (telewindows-workstation)
  (declare (ignore telewindows-workstation))
  nil)

#-gsi-in-g2
(defun gsi-priority-of-data-service-function ())
(defun tw-priority-of-data-service-function ())


; ;;; FILES
; (defun load-japanese-translations-file (pathname)
;   (declare (ignore pathname)))
; Removed.  (MHD 5/9/91)

)

#-(or chestnut chestnut-3)
(progn
  (defun stub-g2-patches-function (&rest args)
    (error "A stub function defined in G2 patches has been called with args: ~a" args))

  (defmacro stub-function-if-necessary (function-symbol)
    `(unless (fboundp ',function-symbol)
       (setf (symbol-function ',function-symbol)
	     (symbol-function 'stub-g2-patches-function))))

  (stub-function-if-necessary get-telewindows-command-line-args-if-valid)

  (stub-function-if-necessary refresh-telewindow)

  (stub-function-if-necessary reshape-telewindow)

  (stub-function-if-necessary send-telewindows-workstation-event)

  (stub-function-if-necessary write-list-of-text-lines-to-gensym-window)

  (stub-function-if-necessary telewindows-check-version-of-remote-g2)

  (stub-function-if-necessary abort-telewindows-for-protocol-out-of-synch-case-6)

  (stub-function-if-necessary abort-telewindows-top-level)

  (stub-function-if-necessary reroute-telewindows-connection)

  (stub-function-if-necessary telewindows-authorized-for-japanese-p)

  (stub-function-if-necessary telewindows-authorized-for-korean-p)

  (stub-function-if-necessary telewindows-authorized-for-chinese-p))






;;;; GSI


;;;; Stubbing Tools

;; jh, 9/14/94.  Copied from GSI-PATCHES.  Consider unifying these with stubs
;; for other products someday, but not now because: (1) different products have
;; different needs (there is nothing like def-gsi-toolkit-stub anywhere else,
;; for example) and (2) different developers have different ideas about what
;; module information is useful to store during stubbing (a.k.a. "the
;; declare-forward-reference flap").

(defmacro declare-stub-defun ((module-name name) arglist
                      &optional (constant-return-value nil))
  (declare (ignore module-name))
  (let ((ignorable-args? nil))
    (do* ((args arglist (cdr args))
	  (arg (car args) (car args)))
	 ((null args)
	  (setq ignorable-args? (nreverse ignorable-args?)))
      (unless (member arg lambda-list-keywords)
	(push arg ignorable-args?)))
    `(progn
       (defun ,name ,arglist
	 ,@(if ignorable-args?
	       `((declare (ignore ,@ignorable-args?)))
	       nil)
	 ,constant-return-value))))

(defmacro declare-stub-defvar (module-name name)
    (declare (ignore module-name))
  `(progn
     (defvar ,name nil)))

(defmacro def-gsi-toolkit-stub
    ((module-name function-name c-name) &rest arg-specs)
  (declare (ignore module-name))
  (if (and (eval-feature :chestnut-3)
	   (eval-feature :chestnut-trans))
      (with-package-specific-symbols (tx |::| def-foreign-callable)
	`(def-foreign-callable (,function-name
				  (:name ,c-name)
				  (:return-type :fixnum-long))
	     ,arg-specs
	   0))
      ;; AB::LOOP is not defined yet, must use AB-LISP:LOOP here.
      (let ((args (ab-lisp::loop for (arg) in arg-specs collect arg)))
	`(defun ,function-name ,args
	   (declare (ignore ,@args))
	   nil))))

#-gsi-in-g2
(progn

(defun entering-signal-handler-function ()
  nil)

;; VARIABLES AND PARAMETERS

(declare-stub-defvar GSI derived-icp-input-port)
(declare-stub-defvar GSI derived-icp-output-port)
(declare-stub-defvar GSI gsi-maximum-contexts-exceeded)	; a constant, actually.

;; FUNCTIONS

(declare-stub-defun (GSI run-one-gsi-scheduler-cycle) ())
(declare-stub-defun (GSI signal-gsi-network-error) (x y))
(declare-stub-defun (GSI gsi-check-if-all-items-are-built) (x))
(declare-stub-defun (GSI get-icp-socket-from-context) (x y))
(declare-stub-defun (GSI gsi-warning) (x y &optional a1 a2 a3 a4 a5 a6))
(declare-stub-defun (GSI gsi-error) (x y &optional a1 a2 a3 a4 a5 a6))
(declare-stub-defun (GSI gsi-connection-error) (x y &optional a1 a2 a3 a4 a5 a6))
(declare-stub-defun (GSI gsi-fatal-error) (x y &optional a1 a2 a3 a4 a5 a6))
(declare-stub-defun (GSI resolve-gsi-context) (context function-name))
(declare-stub-defun (GSI gsi-maybe-initiate-delayed-connection) (icp-socket))
(declare-stub-defun (GSI gsi-failure-p) (value))
(declare-stub-defun (GSI find-new-gsi-context) ())
(declare-stub-defun (GSI gsi-message) (message &optional arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9))
(declare-stub-defun (GSI reclaim-gsi-remote-procedures) (list))
(declare-stub-defun (GSI reclaim-gsi-transfer-wrapper-array) (transfer-wrapper-array))
(declare-stub-defun (GSI reclaim-gsi-sensor-attribute-list)
  (sensor-attribute-list))
(declare-stub-defun (GSI filter-text-for-gsi-p) ())
(declare-stub-defun (GSI maybe-call-gsi-shutdown-context-callback) (icp-socket))
(declare-stub-defun (GSI convert-value-to-gsi-value) (value))
(declare-stub-defun (GSI convert-gsi-value-to-value) (value))
(declare-stub-defun (GSI reclaim-gsi-instance) (x user-or-gsi))
(declare-stub-defun (GSI write-icp-gsi-value-vector) (x))
(declare-stub-defun (GSI write-icp-gsi-values) (x))
(declare-stub-defun (GSI current-gsi-string-conversion-style) ())
(declare-stub-defun (GSI gsi-make-appropriate-array) (gsi-type-tag element-count &optional gsi-instance?))
(declare-stub-defun (GSI gsi-push-onto-appropriate-list) (new-thing &optional gsi-instance?))
(declare-stub-defun (GSI gsi-simple-content-copy-internal) (dst src))
(declare-stub-defun (GSI text-conversion-style-for-gsi) (style-code wide-string-p))
(declare-stub-defun (GSI gsi-intern) (string))
(declare-stub-defun (GSI gsi-make-attributes-for-user-or-gsi) (count user-or-gsi))
(declare-stub-defun (GSI make-gsi-structure) (list))
(declare-stub-defun (GSI make-gsi-sequence) (list))
(declare-stub-defun (GSI make-gsi-history)
  (gsi-instance length &optional values? timestamps? base-time? max-count?
   max-age? granularity?))
(declare-stub-defun (GSI add-vectors-to-gsi-history) (length history gsi-instance?))
(declare-stub-defun (GSI gsi-get-item-of-attribute-named) (instance symbol))
(declare-stub-defun (GSI register-gsi-connection-callbacks) (listener-socket? nascent-socket))
(declare-stub-defun (GSI set-gsi-attribute-name) (attribute attribute-name))
(declare-stub-defun (GSI make-gsi-attribute-for-user-or-gsi) (user-or-gsi))
(declare-stub-defun (GSI gsi-attribute-qualified-name) (gsi-attribute))
(declare-stub-defun (GSI gsi-make-array-for-user-or-gsi) (count user-or-gsi))

(declare-stub-defun (GSI make-gsi-instance)
  (&optional instance-type
	     instance-value
	     instance-attributes
	     instance-class
	     instance-name
	     instance-owner
	     sensor-collection-interval))
(declare-stub-defun (GSI make-gsi-history-from-specification) (max-count? max-age? granularity?))

(declare-stub-defun (GSI signal-gsi-icp-message-too-long-error) ())
(declare-stub-defun (GSI signal-gsi-icp-message-out-of-synch-case-2-error) ())

(declare-stub-defun (GSI signal-gsi-maximum-gensym-string-length-error)
  (length maximum-length))
(declare-stub-defun (GSI signal-gsi-maximum-text-string-length-error)
  (length maximum-length))

(declare-stub-defun (GSI signal-gsi-extend-current-gensym-string-error) ())
(declare-stub-defun (GSI signal-gsi-extend-current-text-string-error) ())

(declare-stub-defun (GSI signal-gsi-undefined-structure-method-error) ())
(declare-stub-defun (GSI signal-gsi-index-space-full-error) ())

(declare-stub-defun (GSI-RPC1 gsi-start-or-call-local-function-or-handle-return-values)
  (invocation-type remote-procedure-name remote-procedure-identifier rpc-argument-list))

(declare-stub-defun (GSI-RPC2 gsi-reclaim-contents) (reclaim-list? user-or-gsi))
(declare-stub-defun (GSI-RPC2 gsi-prepare-for-recursive-descent) ())
(declare-stub-defun (GSI-RPC2 gsi-type-from-g2-element-type) (g2-element-type))
(declare-stub-defun (GSI-RPC2 gsi-type-from-leaf-type) (leaf-type))
(declare-stub-defun (GSI-RPC2 gsi-preflight-item) (item junk))
(declare-stub-defun (GSI-RPC2 gsi-send-item) (item attribute-spec?))

(declare-stub-defun (GSI-RPC2 gsi-build-item-instance)
  (attribute-type
    attribute-qualifier?
    attribute-name-or-index
    class-name
    gsi-type-tag
    vector-length
    symbolic-attribute-count))

(declare-stub-defun (GSI-RPC2 gsi-receive-add-homogeneous-history-range)
  (timestamps-use-floats? element-type number-of-elements))

(declare-stub-defun (GSI-RPC2 gsi-add-resumable-circularity)
  (corresponding-index))

(declare-stub-defun (GSI-RPC2 gsi-receive-add-history-range)
  (timestamps-use-float-array-p values-use-float-array-p number-of-elements))

(declare-stub-defun (GSI-RPC2 gsi-array-type-from-g2-element-type)
  (g2-element-type))

(declare-stub-defun (GSI-RPC2 simple-text-string-copy-from-attribute-name)
  (base-name class-qualifier?))

(declare-stub-defun (GSI-RPC2 gsi-list-type-from-g2-element-type)
  (g2-element-type))

(declare-stub-defun (GSI-RPC2 gsi-add-leaf-to-item-instance)
  (current-subobject
    attribute-type
    attribute-qualifier?
    attribute-name-or-index
    leaf-value
    leaf-type))

(declare-stub-defun (GSI-RPC1 gsi-handle-define-remote-procedure-name)
  (new-remote-procedure-name))

(declare-stub-defun (GSI gsi-option-is-set-p)
  (option-index))

(declare-stub-defun (GSI gsi-deregister-items-wrapper-for-known-sensor)
  (gsi-sensor index))

(declare-stub-defun (GSI call-gsi-callback)
  (callback-index &optional arg1 arg2 arg3))

(declare-stub-defun (GSI call-gsi-close-fd-callback)
  (fd))

(declare-stub-defun (GSI call-gsi-open-fd-callback)
  (fd))

(declare-stub-defun (GSI call-gsi-not-writing-fd-callback)
  (fd))

(declare-stub-defun (GSI call-gsi-writing-fd-callback)
  (fd))

(declare-stub-defun (GSI default-owner-for-gsi-objects)
  ())

(declare-stub-defun (GSI find-or-load-gsi-application)
  (name))

(declare-stub-defun (GSI gsi-current-context-number)
  ())

)

(declare-stub-defun (TELEWINDOWS tw-handle-spawn-remote-command-line-process)
  (index-of-result-parameter command-line))

(declare-stub-defun (TELEWINDOWS tw-handle-spawn-remote-executable-process)
  (index-of-result-parameter command-line))

(declare-stub-defun (TELEWINDOWS tw-handle-remote-process-exists-p)
  (index-of-result-parameter process-id))

(declare-stub-defun (TELEWINDOWS tw-handle-kill-remote-process)
  (index-of-result-parameter process-id))

(declare-stub-defun (TELEWINDOWS reclaim-telewindows-workstation-function)
  (workstation))


				 
;; End file with CR

