;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GSI-PATCHES

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; Peter Fandel and John Hodgkinson



;;; The following provides stubs for all of those variables and functions which
;;; are only applicable to the AB system but which are referenced in modules
;;; included in the GSI system.  In the past declare-forward-reference handled
;;; these cases but with Chestnut declare-forward-reference expands to nil and
;;; these functions are left undefined.


;;;; Stubbing Tools

;; jh, 3/16/94.  Changed defun-stub and defvar-stub to declare-stub-defun and
;; declare-stub-defvar respectively, so that etags, which matches "^(def...",
;; does not put these stubs in the tags table.  This should make meta-dot less
;; travail for seekers of the actual functions and variables.

(defvar-for-macro property-naming-module-of-stubbed-out-function
  (intern
    (format nil "FUNCTION-IN-MODULE-STUBBED-OUT-BY-~a-SYSTEM"
	    current-system-being-loaded)))

(defvar-for-macro property-naming-stubbed-out-functions-of-module
  (intern
    (format nil "FUNCTIONS-STUBBED-OUT-BY-~a-SYSTEM"
	    current-system-being-loaded)))

(defvar-for-macro modules-with-gsi-stubs nil)

(defmacro declare-stub-defun ((module-name name) arglist
                      &optional (constant-return-value nil))
  (let ((ignorable-args? nil))
    (do* ((args arglist (cdr args))
	  (arg (car args) (car args)))
	 ((null args)
	  (setq ignorable-args? (nreverse ignorable-args?)))
      (unless (member arg lambda-list-keywords)
	(push arg ignorable-args?)))
    `(progn
       ,@(if (eval-feature :development)
	     `((setf (get ',name
			  ',property-naming-module-of-stubbed-out-function)
		     ',module-name)
	       (pushnew
		 ',name
		 (get ',module-name
		      ',property-naming-stubbed-out-functions-of-module))
	       (pushnew ',module-name modules-with-gsi-stubs))
	     nil)
       (defun ,name ,arglist
	 ,@(if ignorable-args?
	       `((declare (ignore ,@ignorable-args?)))
	       nil)
	 ,constant-return-value))))

;; Added optional return value arg.  --ncc 3/16 or earlier/94.

(defvar-for-macro property-naming-module-of-stubbed-out-variable
  (intern
    (format nil "VARIABLE-IN-MODULE-STUBBED-OUT-BY-~a-SYSTEM"
	    current-system-being-loaded)))

(defvar-for-macro property-naming-stubbed-out-variables-of-module
  (intern
    (format nil "VARIABLES-STUBBED-OUT-BY-~a-SYSTEM"
	    current-system-being-loaded)))

(defmacro declare-stub-defvar (module-name name)
  `(progn
     ,@(if (eval-feature :development)
	   `((setf (get ',name
			',property-naming-module-of-stubbed-out-variable)
		   ',module-name)
	     (pushnew ',name
		      (get ',module-name
			   ',property-naming-stubbed-out-variables-of-module))
	     (pushnew ',module-name modules-with-gsi-stubs))
	   nil)
     (defvar ,name nil)))




;;;; Functions and Variables Stubbed by GSI

(declare-stub-defun (WINDOWS1 get-gensym-window-parameter) (gensym-window parameter-name))
(declare-stub-defun (WINDOWS4 get-frame-window-type) (system))

(declare-stub-defun (INTERFACES local-gensym-x11-display) ())

(declare-stub-defvar IMAGES bytes-allocated-for-image-tiles)
(declare-stub-defun (IMAGES bytes-allocated-for-image-tiles) ())

(declare-stub-defun (IMAGES maximum-bytes-for-image-tiles) ())

(declare-stub-defun (DEBUG install-system-table) (system-table))
(declare-stub-defun (DEBUG write-error-text) (error-text))

(declare-stub-defun (DEBUG notify-user)
  (notification-as-format-string 
    &optional arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9))

(declare-stub-defvar PLATFORMS x11-window)
(declare-stub-defvar PLATFORMS workstations-in-service)

(declare-stub-defun (PLATFORMS x11-display-specified-p) ())
(declare-stub-defun (PLATFORMS no-local-window-p) ())
(declare-stub-defun (PLATFORMS x11-preinitialize-if-necessary) ())
(declare-stub-defun (PLATFORMS c-x11-initialize) (a b c d e f g h i j))
(declare-stub-defun (PLATFORMS get-default-x11-display) ())
(declare-stub-defun (PLATFORMS get-window-name-from-command-line-if-any) ())
(declare-stub-defun (PLATFORMS get-icon-name-from-command-line-if-any) ())
(declare-stub-defun (PLATFORMS c-x11-close) (gensym-x-window-index))
(declare-stub-defun (PLATFORMS x-events-pending?) () 0)
(declare-stub-defun (PLATFORMS print-display-error) ())

(declare-stub-defun (PLATFORMS get-values-from-x11-parse-geometry)
  (parsestring))

(declare-stub-defun (PLATFORMS make-or-revise-window-per-native-window)
  (gensym-window? native-window))

(declare-stub-defvar ARRAYS do-not-initialize-g2-array-elements-p)

(declare-stub-defun (SETS write-type-specification) (type-specification))
(declare-stub-defun (SETS signal-floating-point-exception-stack-error) ())
(declare-stub-defun (SETS exit-current-profiling-context) (current-time))
(declare-stub-defun (SETS posit-profiling-structure)(current-task))

(declare-stub-defun (SETS make-evaluation-truth-value-function)
  (fixnum-truth-value))

#-gsi-web
(declare-stub-defun (STREAMS g2-stream-write-char) (char stream))
#-gsi-web
(declare-stub-defun (STREAMS g2-stream-write-string) (string stream))
#-gsi-web
(declare-stub-defun (STREAMS g2-stream-directory-p) (namestring))
#-gsi-web
(declare-stub-defun (STREAMS g2-stream-p) (thing))
#-gsi-web
(declare-stub-defun (STREAMS gensym-probe-file) (convertible-thing))
#-gsi-web
(declare-stub-defun (STREAMS wild-regular-expression-string-p) (possibly-wild-string))

(declare-stub-defun (TYPES reclaim-evaluation-value)
  (evaluation-value))
(declare-stub-defun (TYPES copy-evaluation-value-1) (x))
#+development
(declare-stub-defun (TYPES evaluation-sequence-elements-of)
		    (path-name variable data-type prep-phrases inclusive?
			       allowed-preps data))
#+development
(declare-stub-defun (TYPES evaluation-structure-pairs-of)
		    (path-name variable-pair data-type prep-phrases inclusive?
			       allowed-preps data))




(declare-stub-defun (TYPES write-block-or-evaluation-value)
  (block-or-evaluation-value))

(declare-stub-defun (TYPES write-evaluation-value)
  (evaluation-value &optional beautifully?))

(declare-stub-defun (SEQUENCES1 shift-rule-ordering-heuristics) ())
(declare-stub-defun (SEQUENCES1 encode-user-password-string-function) (string))

(declare-stub-defun
  (SEQUENCES1 cache-deferred-rule-invocation-indices)
  ())

(declare-stub-defun
  (SEQUENCES1 rule-invocation-updates-needed-p)
  ())

(declare-stub-defvar SEQUENCES2 saved-initial-status)

(declare-stub-defun (SEQUENCES2 replace-format-using-equivalent-font)
  (class))

(declare-stub-defun (G2-FOREIGN kill-foreign-image-unconditionally)
  (image-info))

(declare-stub-defun (FILE-SYSPROC reclaim-sysproc-list-function)
  (sysproc-list))

(declare-stub-defun (FILE-SYSPROC kill-possibly-leftover-spawned-process)
  (process-id))

(declare-stub-defun (ENTITIES make-system-frame) (class))

(declare-stub-defun (FRAMES2A block-p-function) (x))
(declare-stub-defun (FRAMES2A framep-function) (x))
#+development
(declare-stub-defun (FRAMES2A class-instances-path)
		    (path-name variable data-type prep-phrases inclusive?
			       allowed-prepositions data))

(declare-stub-defun (FRAMES4 write-name-denotation) (name-denotation))
(declare-stub-defun (FRAMES4 reclaim-slot-value-tree-function) (tree))

(declare-stub-defun (FRAMES4 write-name-denotation-components)
  (name defining-class?))

(declare-stub-defun (FRAMES4 make-workspace)
  (class &optional name?
	           initial-subblock?
		   non-default-margin?
		   minimum-initial-width?
		   minimum-initial-height?
		   only-workstation-workspace-can-be-on?))

(declare-stub-defun (FRAMES4 write-name-denotation-for-slot)
  (slot-description class-description))

(declare-stub-defun (PROC-UTILS name-and-class-for-computation-instance) (x))

(declare-stub-defun (TABLES get-or-make-up-designation-for-block) (block))
(declare-stub-defun (TABLES twrite-designation-for-item) (block))

(declare-stub-defun (GRAMMAR0 print-constant)
  (constant-value constant-type &optional beautifully?))

(declare-stub-defun (GRAMMAR7 write-expression) (exp))

(declare-stub-defun (EVAL print-designation) (designation))

(declare-stub-defun (EVAL3 warn-of-big-bignum) (negative?))

#-gsi-web
(declare-stub-defvar STREAMS g2-stream-all-open-streams)

#-gsi-web
(declare-stub-defun (STREAMS g2-stream-close) (g2-stream))
#-gsi-web
(declare-stub-defun (STREAMS reclaim-streams-list-function) (streams-list))

#-gsi-web
(declare-stub-defun (STREAMS copy-list-using-streams-conses-function)
  (streams-list))

#-gsi-web
(declare-stub-defun (PATHNAMES write-gensym-pathname) (gensym-pathname))

(declare-stub-defun (RINGS compute-newest-thrashing-ratio)
  (limit-info time-since-last-update))

(declare-stub-defun (RULES equal-rule-context) (rule-context-1 rule-context-2))

;;(declare-stub-defvar SCHEDULE system-is-running)
;;(declare-stub-defvar SCHEDULE system-has-paused)

(declare-stub-defun (DRAW add-to-workspace)
  (block workspace
    left-edge-for-block
    top-edge-for-block
    &optional
    update-images?
    confine-updating-to-block-rectangle?))

(declare-stub-defun (DRAW lookup-frame-description-reference-of-frame-style)
  (frame-style default-frame-style))

(declare-stub-defun (BOXES make-dialog-message) (constant-string))
(declare-stub-defun (BOXES reclaim-text) (text))

(declare-stub-defun (BOXES make-dialog-button)
  (constant-string translation this-is-the-default-button?))

(declare-stub-defun (PANES detail-pane) (gensym-window))

(declare-stub-defun (PANES get-available-image-plane)
  (pane frame-description-reference on-the-bottom?))

(declare-stub-defun (PANES put-image-on-image-plane)
  (image-plane
    workspace
    new-image-x-scale?
    new-image-y-scale?
    fraction-of-image-width-or-height-to-have-within-pane?
    block-to-position-on?
    x-in-workspace?
    y-in-workspace?
    x-in-window?
    y-in-window?))

(declare-stub-defvar BOOKS log-file-outputting?)

(declare-stub-defun (BOOKS close-log-file) ())

(declare-stub-defun (BOOKS notify-engineer)
  (notification-as-format-string
    &optional arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9))

(declare-stub-defun (BOOKS post-on-message-board)
  (text-line
    urgency?
    duration?
    origin-frame?
    destination?
    &optional workspace? target-block? above-target? do-not-reformat?))

(declare-stub-defun (RUN pause-for-internal-error) (message))

(declare-stub-defun (CYCLES system-pause) ())

(declare-stub-defun (INT1 run-embedded-option-for-recursive-descent) (x y))
(declare-stub-defun (INT1 run-gfi-for-recursive-descent) (x y))
(declare-stub-defun (INT1 run-gsi-for-recursive-descent) (x y))
;(declare-stub-defun (INT1 run-gspan-for-recursive-descent) (x y)) 6/9/98 ddm
(declare-stub-defun (INT1 run-icp-for-recursive-descent) (x y))
(declare-stub-defun (INT1 run-chinese-for-recursive-descent) (x y))
(declare-stub-defun (INT1 run-japanese-for-recursive-descent) (x y))
(declare-stub-defun (INT1 run-kfep-for-recursive-descent) (x y))
(declare-stub-defun (INT1 run-korean-for-recursive-descent) (x y))
(declare-stub-defun (INT1 run-nupec-for-recursive-descent) (x y))
(declare-stub-defun (INT1 run-runtime-option-for-recursive-descent) (x y))
(declare-stub-defun (INT1 run-g1-for-recursive-descent) (x y))
(declare-stub-defun (INT1 run-jl-for-recursive-descent) (x y))
(declare-stub-defun (INT1 run-jp-for-recursive-descent) (x y))
(declare-stub-defun (INT1 run-al-for-recursive-descent) (x y))
(declare-stub-defun (INT1 run-ent-for-recursive-descent) (x y))

(declare-stub-defun (INT1 run-restricted-use-option-for-recursive-descent)
  (x y))

(declare-stub-defun (INT2 g2-cancel-flush-of-partial-icp-buffer) ())
(declare-stub-defun (INT2 g2-priority-of-data-service-function) ())
(declare-stub-defun (INT4 item-references-enabled-p) (socket))

(declare-stub-defun (FILTERS network-access-allowed-p)
  (access-agent access-type &optional frame?))
#+gsi-web
(declare-stub-defun (FILTERS g2-identification-for-write-locks) ())



(declare-stub-defun (TELESTUBS handle-unclogged-connection-if-necessary)
  (I-am-alive-info))

(declare-stub-defvar GFI time-slice-expired-p)

(declare-stub-defun (G2-GSI define-or-configure-gsi-sensor)
  (sensor corresponding-icp-object-index gsi-interface))

(declare-stub-defun (G2-GSI get-gsi-interface-for-gsi-sensor-if-any)
  (gsi-sensor))

(declare-stub-defun (G2-GSI gsi-receive-value-for-gsi-sensor)
  (gsi-sensor error-code value? collection-time? value-vector?))

(declare-stub-defun (G2-GSI gsi-receive-value-for-ping-request)
  (gsi-interface year month day hour minute second status))

(declare-stub-defun (G2-RPC1 abort-rpc-call-and-reclaim-identifier)
  (remote-procedure-identifier))

(declare-stub-defun (G2-RPC1 signal-error-to-rpc-caller-and-reclaim-identifier)
  (remote-procedure-identifier))

(declare-stub-defun (G2-RPC2 g2-reclaim-sending-resumable-object)
  (resumable-object))

(declare-stub-defun (G2-RPC2 reclaim-evaluation-value-if-any-function)
  (evaluation-value?))

(declare-stub-defun (WORKSTATION scheduler-mode-function)
                    (timing-parameters))
(declare-stub-defun (WORKSTATION minimum-scheduling-interval-function)
                    (timing-parameters))

(declare-stub-defvar WORKSTATION timing-parameters)

(declare-stub-defvar KB-LOAD1 warmbooting?)
(declare-stub-defvar KB-LOAD1 warmbooting-with-catch-up?)
(declare-stub-defvar KB-LOAD2 warmboot-current-time)
(declare-stub-defvar KB-LOAD2 warmboot-simulated-time)

(declare-stub-defun (CYCLES take-actions-at-start-of-clock-tick)
		    (fixnum-time-length-of-previous-tick))

(declare-stub-defun (HISTORIES add-delta-time-to-variables-and-parameters)
		    (managed-float-delta))

(declare-stub-defun (GRAPHS update-trend-charts-for-clock-discontinuity)
		    (time-delta))

(declare-stub-defun (OLE cache-main-thread-id) ())

(declare-stub-defun (OLE do-all-ole-initialization) (system-window))

(declare-stub-defun (OLE do-all-ole-cleanup) (system-window))

(declare-stub-defun (NETEVENT schedule-g2-legacy-heartbeat-tasks-if-necessary)
		    ())

(declare-stub-defun (G2-METERS report-simple-string-allocation) (string))

(declare-stub-defun (G2-METERS report-simple-string-reclamation) (string length))

;; jh, 12/29/94.  The following is the only G2/TW macro that GSI needs to
;; replace with a stub.  In general, stubbing macros is a bad idea because it
;; can lead to one product's binaries being compiled with another product's
;; macros.

(defmacro execute-body-if-icp-is-authorized-or-predicate-true (&body body)
  `(progn ,@body))


;;;; Switching Between GSI and G2

#+development
(defun replace-product
    (compile-function compile-options make-function modules-to-reload)
  (apply compile-function compile-options)
  (do* ((modules modules-to-reload (cdr modules))
	(module (car modules) (car modules)))
       ((null modules))
    (ab-lisp::funcall make-function
		      :from module :to module
		      :reload :no-process)))

#+development
(defun replace-gsi-with-g2 (&rest options)
  (replace-product
    #'compile-g2
    options
    #'make-g2
    modules-with-gsi-stubs))

#+development
(defun replace-g2-with-gsi (&rest options)
  (replace-product
    #'compile-gsi
    options
    #'make-gsi
    '(gsi gsi-rpc1 gsi-rpc2)))



;; End file with CR

