;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module TW-PATCHES

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; John Hodgkinson






;;; The following provides stubs for all of those variables and functions
;;; referenced by Telewindows, but not actually used by Telewindows.  For
;;; example the event handling checks the "player-state" to see if the player
;;; wants to feed events into the event stream, but Telewindows has no player.
;;;
;;; The functions here should NEVER be called from Telewindows.  Therefore, it
;;; is invalid to define for them any return value or side effect.  Furthermore,
;;; they are only defined when, i.e., in non-development compiles where it
;;; necessary to define even functions that cannot be called; in development,
;;; these are not normally be defined.
;;;
;;; It is good practice, therefore, to define initial values of variables
;;; defined here as the value of `value-undefined-in-telewindows', and to define
;;; functions to call
;;; `signal-error-for-undefined-function-called-from-telewindows'
;;; as their only action.
;;;
#+(or chestnut chestnut-3 just-telewindows) ;Chestnut3.1
(progn


;;;; Macros
  
;;; Note that macros should never be defined here.  (The few exceptions are
;;; mistakes, and will be cleaned up at the next convenient time. -mhd, 7/27/95)

;; WARNING-MESSAGE                                      INT0

(defmacro warning-message (level format-string &body format-args)
  (declare (ignore level format-string format-args))
  (signal-error-for-undefined-function-called-from-telewindows))




;;;; Infrastructure

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


  
(defun signal-error-for-undefined-function-called-from-telewindows ()
  (error
    "a function not defined for Telewindows has been called in Telewindows"))

(defvar value-undefined-in-telewindows
  #+development #C(1.2 3.4)		; should never be seen by the code
  #-development 'bogus-value)		; see also the value of bogus-value




;;;; Variables and Parameters


(defvar timing-parameters value-undefined-in-telewindows)

(defvar warmboot-simulated-time value-undefined-in-telewindows)
(defvar dequeuing-time value-undefined-in-telewindows)

;;                                                      KB-LOAD1
(defvar warmbooting? value-undefined-in-telewindows)

(defvar current-kb-pathname? value-undefined-in-telewindows)

;; WARMBOOTING-WITH-CATCH-UP?
(defvar warmbooting-with-catch-up? value-undefined-in-telewindows)

;; WARMBOOT-CURRENT-TIME                                KB-LOAD2
(defvar warmboot-current-time value-undefined-in-telewindows)

;; ALL-FOREIGN-FUNCTION-IMAGES                          PLATFORMS

(defvar all-foreign-function-images value-undefined-in-telewindows)

;; KNOWN-PROCESS-IDS                                    FILE-IO

(defvar known-process-ids value-undefined-in-telewindows)

;; PLAYER-STATE						TELESTUBS

(defvar player-state value-undefined-in-telewindows)

;; SAVED-INITIAL-STATUS                                  INT2

(defvar saved-initial-status value-undefined-in-telewindows)


;; GLOBAL-GRAMMAR					UTILITIES3

(defvar global-grammar value-undefined-in-telewindows)


;; BAD-PHRASE						SEQUENCES1

(defvar bad-phrase value-undefined-in-telewindows)


;; LOG-FILE-OUTPUTTING?					PLATFORMS

(defvar log-file-outputting? value-undefined-in-telewindows)

;; NOTING-CHANGES-TO-KB-P                               PRIMITIVES

(defvar noting-changes-to-kb-p value-undefined-in-telewindows)

;; GSI-COMMON

(defvar gsi-suppress-output value-undefined-in-telewindows)

(defparameter DEFAULT-WORKSPACE-FRAME-DESCRIPTION value-undefined-in-telewindows)




;;;; Functions


;; write-name-denotation-components                     UTILITIES1

(defun write-name-denotation-components (name defining-class?)
  (declare (ignore name defining-class?))
  (signal-error-for-undefined-function-called-from-telewindows))


;; write-name-denotation                                UTILITIES1

(defun write-name-denotation (name-denotation)
  (declare (ignore name-denotation))
  (signal-error-for-undefined-function-called-from-telewindows))


;; BLOCK-P-FUNCTION                                     UTILITIES1
(defun block-p-function (x)
  (declare (ignore x))
  (signal-error-for-undefined-function-called-from-telewindows))

(defun twrite-designation-for-item (x)
  (declare (ignore x))
  (signal-error-for-undefined-function-called-from-telewindows))

;; BLOCK-P-FUNCTION                                     UTILITIES1
(defun framep-function (x)
  (declare (ignore x))
  (signal-error-for-undefined-function-called-from-telewindows))

;; GET-OR-MAKE-UP-DESIGNATION-FOR-BLOCK			UTILITIES1

(defun get-or-make-up-designation-for-block (block) 
  (declare (ignore block))
  (signal-error-for-undefined-function-called-from-telewindows))

;; PRINT-DESIGNATION					UTILITIES1

(defun print-designation (designation) 
  (declare (ignore designation))
  (signal-error-for-undefined-function-called-from-telewindows))


;; WRITE-EXPRESSION					UTILITIES1

(defun write-expression (exp) 
  (declare (ignore exp))
  (signal-error-for-undefined-function-called-from-telewindows))

(defun write-evaluation-value (value) 
  (declare (ignore value))
  (signal-error-for-undefined-function-called-from-telewindows))


;; PRINT-CONSTANT					UTILITIES1

(defun print-constant (constant-value constant-type) 
  (declare (ignore constant-value constant-type))
  (signal-error-for-undefined-function-called-from-telewindows))


;; WARN-OF-BIG-BIGNUM					UTILITIES3

(defun warn-of-big-bignum (negative?) 
  (declare (ignore negative?))
  (signal-error-for-undefined-function-called-from-telewindows))


;; MAKE-CALL-HASH-FUNCTION                         UTILITIES3

(defun make-call-hash-function ()
  (signal-error-for-undefined-function-called-from-telewindows))


;; LAY-OUT-WINDOW					PLATFORMS

(defun lay-out-window (gensym-window) 
  (declare (ignore gensym-window))
  (signal-error-for-undefined-function-called-from-telewindows))


;; REFRESH-WINDOW					PLATFORMS

(defun refresh-window (gensym-window)
  (declare (ignore gensym-window))
  (signal-error-for-undefined-function-called-from-telewindows))


;; G2-GLOBAL-PAINT-MODE-P                                WORKSTATIONS

(defun g2-global-paint-mode-p ()
  (signal-error-for-undefined-function-called-from-telewindows))


;; NOTIFY-USER						PATHNAMES

(defun notify-user (notification-as-format-string &optional 
		    (arg1 nil)
		    (arg2 nil)
		    (arg3 nil)
		    (arg4 nil)
		    (arg5 nil)
		    (arg6 nil)
		    (arg7 nil)
		    (arg8 nil)
		    (arg9 nil))
  (declare (ignore notification-as-format-string
		   arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9))
  (signal-error-for-undefined-function-called-from-telewindows))


;; RUN-GSI-FOR-RECURSIVE-DESCENT			INT1

(defun run-gsi-for-recursive-descent (x y) 
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))


;; RUN-GSPAN-FOR-RECURSIVE-DESCENT			INT1

(defun run-gspan-for-recursive-descent (x y) 
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))


;; RUN-ICP-FOR-RECURSIVE-DESCENT			INT1

(defun run-icp-for-recursive-descent (x y) 
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))


;; RUN-GFI-FOR-RECURSIVE-DESCENT			INT1

(defun run-gfi-for-recursive-descent (x y)
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))


;; RUN-KFEP-FOR-RECURSIVE-DESCENT			INT1

(defun run-kfep-for-recursive-descent (x y) 
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))


;; RUN-RUNTIME-OPTION-FOR-RECURSIVE-DESCENT		INT1

(defun run-runtime-option-for-recursive-descent (x y) 
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))


;; RUN-RESTRICTED-USE-OPTION-FOR-RECURSIVE-DESCENT      INT1

(defun run-restricted-use-option-for-recursive-descent (x y) 
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))

;; RUN-EMBEDDED-OPTION-FOR-RECURSIVE-DESCENT      INT1

(defun run-embedded-option-for-recursive-descent (x y) 
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))

;; RUN-CHINESE-FOR-RECURSIVE-DESCENT			INT1

(defun run-chinese-for-recursive-descent (x y) 
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))

;; RUN-JAPANESE-FOR-RECURSIVE-DESCENT			INT1

(defun run-japanese-for-recursive-descent (x y) 
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))

;; RUN-KOREAN-FOR-RECURSIVE-DESCENT			INT1

(defun run-korean-for-recursive-descent (x y) 
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))

;; RUN-NUPEC-FOR-RECURSIVE-DESCENT			INT1

(defun run-nupec-for-recursive-descent (x y) 
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))

;; RUN-G1-FOR-RECURSIVE-DESCENT			INT1

(defun run-g1-for-recursive-descent (x y) 
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))

;; RUN-JL-FOR-RECURSIVE-DESCENT             INT1

(defun run-jl-for-recursive-descent (x y)
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))

;; RUN-JP-FOR-RECURSIVE-DESCENT             INT1

(defun run-jp-for-recursive-descent (x y)
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))

;; RUN-AL-FOR-RECURSIVE-DESCENT             INT1

(defun run-al-for-recursive-descent (x y)
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))

;; RUN-ENT-FOR-RECURSIVE-DESCENT             INT1

(defun run-ent-for-recursive-descent (x y)
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))


;; KILL-POSSIBLY-LEFTOVER-SPAWNED-PROCESS               FILE-IO

(defun kill-possibly-leftover-spawned-process (process-id)
  (declare (ignore process-id))
  (signal-error-for-undefined-function-called-from-telewindows))

;; RECLAIM-SYSPROC-LIST-FUNCTION                        FILE-IO

(defun reclaim-sysproc-list-function (sysproc-list)
  (declare (ignore sysproc-list))
  (signal-error-for-undefined-function-called-from-telewindows))

;; REPLACE-FORMAT-USING-EQUIVALENT-FONT	INT2

(defun replace-format-using-equivalent-font (class) 
  (declare (ignore class))
  (signal-error-for-undefined-function-called-from-telewindows))


;; REMOVE-GRAPH-RENDERING-FROM-GRAPH-GRID		WINDOWS3

(defun remove-graph-rendering-from-graph-grid
       (graph-rendering graph-grid-or-chart) 
  (declare (ignore graph-rendering 
		   graph-grid-or-chart))
  (signal-error-for-undefined-function-called-from-telewindows))


;; SIGNAL-FLOATING-POINT-EXCEPTION-STACK-ERROR          PRIMITIVES

(defun signal-floating-point-exception-stack-error ()   
  (signal-error-for-undefined-function-called-from-telewindows))



;; POLL-PLAYER						TELESTUBS

(defun poll-player () (signal-error-for-undefined-function-called-from-telewindows))

(defun write-error-text (x)
  (declare (ignore x))
  (signal-error-for-undefined-function-called-from-telewindows))

(defun absorb-local-event-ab-side (local-event) ; WORKSTATION
  (declare (ignore local-event))
  (signal-error-for-undefined-function-called-from-telewindows))

(defun absorb-local-event-ab-side-1 (workstation key-code x y timestamp plist) ; WORKSTATION
  (declare (ignore workstation key-code x y timestamp plist))
  (signal-error-for-undefined-function-called-from-telewindows))


;; GET-G2-WINDOW-GIVEN-ICP-SOCKET			TELESTUBS

(defun get-g2-window-given-icp-socket (icp-socket) 
  (declare (ignore icp-socket))
  (signal-error-for-undefined-function-called-from-telewindows))


;; GET-GENSYM-WINDOW-FOR-G2-WINDOW			TELESTUBS

(defun get-gensym-window-for-g2-window (window) 
  (declare (ignore window))
  (signal-error-for-undefined-function-called-from-telewindows))


;; NOTIFY-ENGINEER                                       BOOKS

(defun notify-engineer
       (notification-as-format-string 
	 &optional arg1 arg2 arg3
	 arg4 arg5 arg6 arg7 arg8 arg9)
  (declare (ignore notification-as-format-string 
	 arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8
	 arg9))
  (signal-error-for-undefined-function-called-from-telewindows))


(defun copy-gensym-window-attributes-into-g2-window (gensym-window)
  (declare (ignore gensym-window))
  (signal-error-for-undefined-function-called-from-telewindows))


;; FILTERS
(defun g2-identification-for-write-locks ()
  (signal-error-for-undefined-function-called-from-telewindows))

(defun equal-rule-context (x y)
  (declare (ignore x y))
  (signal-error-for-undefined-function-called-from-telewindows))

(defun get-g2-license-level ()
  (signal-error-for-undefined-function-called-from-telewindows))

(defun g2-handle-spawn-remote-process-reply
    (index-of-result-parameter process-id)
  (declare (ignore index-of-result-parameter process-id))
  (signal-error-for-undefined-function-called-from-telewindows))

(defun g2-handle-remote-process-exists-p-reply
    (index-of-result-parameter result-code)
  (declare (ignore index-of-result-parameter result-code))
  (signal-error-for-undefined-function-called-from-telewindows))

(defun g2-handle-kill-remote-process-reply
    (index-of-result-parameter result-code)
  (declare (ignore index-of-result-parameter result-code))
  (signal-error-for-undefined-function-called-from-telewindows))

;; handle-paste-availability-event-in-g2			Telestubs
(defun handle-paste-availability-event-in-g2 (gensym-window status timestamp?)
  (declare (ignore gensym-window status timestamp?))
  (signal-error-for-undefined-function-called-from-telewindows))
 
;; handle-paste-event-in-g2					Telestubs
(defun handle-paste-event-in-g2 (gensym-window text-string request-id timestamp?)
  (declare (ignore gensym-window text-string request-id timestamp?))
  (signal-error-for-undefined-function-called-from-telewindows))
 

(defun pause-for-internal-error (message)
  (declare (ignore message))
  (signal-error-for-undefined-function-called-from-telewindows))


;; G2-METERS

(defun report-simple-string-allocation (string)
  (declare (ignore string))
  (signal-error-for-undefined-function-called-from-telewindows))

(defun report-simple-string-reclamation (string length)
  (declare (ignore string length))
  (signal-error-for-undefined-function-called-from-telewindows))
  

;; TYPES
(defun reclaim-if-evaluation-item-reference (thing)
  (declare (ignore thing))
  (signal-error-for-undefined-function-called-from-telewindows))

) ; end of progn


