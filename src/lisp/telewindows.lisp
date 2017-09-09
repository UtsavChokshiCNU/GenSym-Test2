;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module TELEWINDOWS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David, Lowell B. Hawkinson, Brian Matthews, Andreas Hofmann



(pushnew :telewindows *features*)



;;;; The Telewindows Workstation Structure

;SS_ERROR
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter default-tw-tcp-connect-interval-in-ms 10000)
(defparameter default-g2-tcp-port 1111)

;; Note that, under Allegro at least, these defconstants are evaluated more than
;; once, due to the eval-when, and this causes an Allegro warning, since the
;; results of calling tformat-text-string twice in a row will not return two
;; values that are eq, so we're changing the value of a constant.  -jv, 12/25/03
(defparameter default-g2-tcp-port-text-string
  (tformat-text-string "~d" default-g2-tcp-port))
)

(def-structure (telewindows-workstation
		 (:include workstation)
		 (:constructor
		   make-telewindows-workstation (window-for-workstation)))

  ;; The next three are non-recyclable constants, and may be shared with the
  ;; value stored in the window parameters plist or with the element in the
  ;; command line plist or the command line arguments list.
  (telewindows-desired-host? "localhost")
  (telewindows-desired-port? default-g2-tcp-port)	; fixnum integer or a string
  (telewindows-desired-protocol? "TCP-IP") ; currently the only option
  (telewindows-desired-init-string? nil)


  ;; The slot `desired-tw-tcp-connect-interval-in-ms' is a fixnum giving the
  ;; default number of milliseconds a Telewindows will wait to connect to a G2
  ;; over TCPIP.  This value may be changed by using the command-line keyword
  ;; "-tcptimeout".
  ;;
  ;; Note that the current (jh, 5/21/94) default value for
  ;; desired-tw-tcp-connect-interval-in-ms is 10000, no longer the same as the C
  ;; global variable tcp_connect_retry_in_ms in tcp.c.  The distinction between
  ;; the C variable and desired-tw-tcp-connect-interval-in-ms is that the C
  ;; variable gives the default TCPIP connection timeout for all Gensym
  ;; products.

  (desired-tw-tcp-connect-interval-in-ms
    #.default-tw-tcp-connect-interval-in-ms)


  ;; The slot `desired-timeout-in-seconds-for-telewindows-connection' is the
  ;; timeout for the outer loop of connecting.  If an attempt to connect fails,
  ;; then connecting will be retried repeatedly until this time limit has
  ;; expired.  Note that it generally only makes sense for this to be of at
  ;; least as long a duration as the above slot, but it need not be.  If it is
  ;; shorter, it just guarantees that a connection will never be attempted more
  ;; than once.

  (timeout-in-seconds-for-telewindows-connection
    #+development 300
    #-development 40)


  (telewindows-icp-socket? nil)		; knows the connection, host name, etc.

  (telewindows-workstation-connection-state 'disconnected)
					; one of CONNECTED, CONNECTING,
					;   DISCONNECTED, DESIRES-CONNECTION,
					;   FAILED-TO-CONNECT, BEING-REROUTED,
					;   CONNECTED-AND-AWAITING-LICENSE-LEVEL

  (telewindows-network-pathname nil)	; valid iff state is desires-connection or
					;   connected, i.e., this can't be read
					;   when it's nil

  ;; The slot `earliest-time-to-overwrite-credits' is initialized to the
  ;; current time just before making the G2 window visible.
  ;;
  ;; It must be initialized to the fixnum time that is one second later than the
  ;; current fixnum time.  This must be done prior to referring to its value
  ;; later in the start-up process.
  ;;
  ;; The idea is to give Telewindows time to identify itself, the product, i.e.,
  ;; to give copyright info., product versioning info., legal disclaimers and
  ;; restrictions, etc.
  ;;
  ;; In 4.0, we decided to keep it up for at least 1 second, per "the management"
  ;; (SG, LH, RLM, DWR).  We used to (in 2.0 & 3.0) keep it up for 4 seconds plus
  ;; however long connecting and the rest of the stuff below took. (MHD 5/18/94)

  (earliest-time-to-overwrite-credits? nil) ; Telewindows Startup Screen if non-nil
					    ;   (only to be shown on 1st window, 1st time)

  time-of-initial-desire-to-connect	; these 3 are set up when upon entering
  earliest-time-to-time-out-connection-attempt ; the desires-connection state
  number-of-connection-attempts-so-far

  (telewindows-previous-protocol? nil)	; non-nil if this has been rerouted
  (telewindows-previous-host? nil)
  (telewindows-previous-port? nil)
  (telewindows-previous-init-string? nil)

  (telewindows-reroute-protocol? nil)
  (telewindows-reroute-host? nil)
  (telewindows-reroute-port? nil)
  (telewindows-reroute-init-string? nil)
  (telewindows-reroute-problem-report? nil)

  ;; `Telewindows-connection-license-level?' is
  ;;
  ;;  nil (unknown/unauthorized)
  ;;  -2 (unauthorized)
  ;;  -1 (floating)
  ;;   0 (embedded)
  ;;   1 (runtime)
  ;;   2 (restricted-use)
  ;;   3 (development)
  (telewindows-connection-license-level? nil)




  ;; The format of `telewindows-connection-license-info' is that of a plist,
  ;; as follows
  ;;
  ;;    telewindows-connection-license-level <license level/integer>
  ;;    g2-license-level <license level/integer>
  ;;    g2-authorized-optional-modules <list-of-authorized-product-module-names>
  ;;
  ;; Note that telewindows-connection-license-level should always be the same as
  ;; the telewindows-connection-license-level? slot in structure.
  ;;
  ;; These should generally be filled in but any of them can all be nil under
  ;; certain scenarios.  G2-authorized-optional-modules and g2-license-level were
  ;; not sent until 4.0 (Final Release), in-house as of 4.0 Beta Rev. 56.  The
  ;; message telewindows-connection-license-level continues to be sent all G2's
  ;; talking to older 4.0 Telewindows (i.e., 4.0 Beta II), but is obsolete.
  ;;
  ;; New G2's will always send this info to new Telewindows.
  ;;
  ;; One of the uses of this information is to decide if Japanese fonts should
  ;; be usable in a floating Telewindows.
  ;;
  ;; This information may be extended in the future.
  ;;
  ;; This is filled in by accept-telewindows-connection-license-info and its
  ;; icp message caller, q.v.
  (telewindows-connection-license-info nil)


  ;; new slots by NCC

  (service-workstations-task nil
			     :reclaimer cancel-task)
)

(defun-simple telewindows-icp-socket?-function (telewindows-workstation)
  (telewindows-icp-socket? telewindows-workstation))


(defun reclaim-telewindows-workstation-function (telewindows-workstation)
  (reclaim-telewindows-workstation telewindows-workstation))

;; forward ref'd from TELESTUBS






;;;; Mapping from an ICP Socket to a Telewindows Workstation



;;; `Get-telewindows-workstation-for-icp-socket' is for use only within
;;; Telewindows.  It iterates over the list of (Telewindows) workstations in
;;; service, and returns the one whose icp socket matches the argument.  If it
;;; finds none, it returns nil.

(defun get-workstation-for-icp-socket (icp-socket)
  (loop for workstation in workstations-in-service
	when (eq (telewindows-icp-socket? workstation) icp-socket)
	  return workstation))





;;;; Telewindows Splashscreen Time

(defparameter minimum-telewindows-splashscreen-time-in-seconds 0)
(defparameter maximum-telewindows-splashscreen-time-in-seconds 30)
(def-system-variable default-telewindows-splashscreen-time-in-seconds telewindows
  2)
(def-system-variable user-specified-telewindows-splashscreen-time-in-seconds? telewindows
  (:funcall initialize-user-specified-telewindows-splashscreen-time-in-seconds?))

(defun initialize-user-specified-telewindows-splashscreen-time-in-seconds? ()
  (getf command-line-arguments 'splashtime))

(defun get-telewindows-splashscreen-time-as-fixnum-time-interval ()
  (*f fixnum-time-interval-for-one-second
      (cond
	(user-specified-telewindows-splashscreen-time-in-seconds?
	 ;; Assumed to be in the min/max range thanks to command-line argument
	 ;; processing done elsewhere.
	 user-specified-telewindows-splashscreen-time-in-seconds?)
	((and (telewindows-multiwindow-ui-p) ; Default to 0 seconds in multiwindow
	      (telewindows-win32-window-p))  ; mode, until it is capable of
                                             ; displaying a splash screen.
	 0)
	(t default-telewindows-splashscreen-time-in-seconds))))





;; YACLIA (yet another command line interface facility done for Telewindows
;; originally, though general) was just now moved to UTILITIES3, where it can be
;; next to its next lower down facility for getting command line arguments. (MHD 2/27/96)


;;;; Getting Connection Information via Command Line or Dialog


;;; Command Line Arguments for Telewindows
;;;
;;; The basic command line "summary" is
;;;
;;;    tw remote-host remote-port-name-or-number [options...]
;;;
;;; Options are as follows:
;;;
;;;    -user-name x          (x is a user name; overrides the OS user name,
;;;                           if known; substitutes for it if not known)
;;;
;;;    -password x           (x is a password -- not encrypted -- a security
;;;                           problem for some users who must beware)
;;;
;;;    -discard-user-settings
;;;                          (default (in 5.0) is to keep the user settings,
;;;                           i.e., user-name, password, language, and
;;;                           user-mode, stored on the Telewindows side; this
;;;                           flag suppresses that behavior)
;;;
;;;    -language x           (x is the specific language to run in this
;;;                           workstation; if "default" or unspecified, you
;;;                           get the global language)
;;;
;;;    -user-mode x          (the user mode to prefer in the G2 about to be
;;;                           connected to)
;;;
;;;    -init-string x        (x is some arbitrary string)  [size limited --
;;;                           a GOTCHA! -- need option to get this from a
;;;                           file?!]
;;;
;;; The following were unique to Telewindows, and were already there in 3.0.
;;;
;;;    -network x            (currently must be "tcpip")
;;;
;;;    -tcptimeout x         (number a milliseconds ...)
;;;
;;; The following are all common to G2 and Telewindows, and thus are only briefly
;;; summarized here.
;;;
;;;    -geometry x
;;;    -fullscreen
;;;    -ok x                  (same as for G2, but the default name is tw.ok)
;;;    -fonts x
;;;    -{x|y-}res[olution] x  (i.e., one of x-res, y-res, res, x-resolution,
;;;                            y-resolution, or resolution)
;;;    -name x
;;;    ...


;; (It would be nice if it were to have the options before the required
;; arguments.  It would be nice if it were to allow just a host or some kind
;; of pathname to be specified.)
;;
;; How about
;;
;;    isr:1111  or  isr:#1 or [the "network pathname"] "tcp_ip:isr:1111" ...?



(def-command-line-argument remote-host-name ((host-arg? 1 #w"localhost"))
  (if (and host-arg?
	   (loop for i from 0 below (text-string-length host-arg?)
		 always (simple-symbol-character-p (charw host-arg? i))))
      ;; crude "ok-host" test! -- ok for now
      host-arg?))


(def-command-line-argument remote-port-name-or-number
    ((arg? 2 #.default-g2-tcp-port-text-string))
  (if arg?
      (cond
	((loop for i from 0 below (text-string-length arg?)
					; is it probably a number?
	       always (digit-char-pw (charw arg? i)))
	 (let ((node-candidate? (read-fixnum-from-string arg?)))	; trap errors!!
	   (cond
	     ((typep node-candidate? 'fixnum)	; check if reasonable node address!!
	      node-candidate?))))
	((loop for i from 0 below (text-string-length arg?)
					; is it probably a symbol?
	       always (simple-symbol-character-p
			(charw arg? i)))
	 arg?))))


(def-command-line-argument network ((value? :keyword))
  (if value?
      (cond
	((string-equalw value? #w"tcpip")
	 #w"TCP-IP")
	((string-equalw value? #w"decnet")
	 (notify-user-if-possible
	   "~%DECNet no longer supported."
	   nil))
	(t nil))))				; notify?

(def-command-line-argument tcptimeout ((value? :keyword))
  (let ((integer?
	  (if value?
	      (or (read-fixnum-from-string value?)
		  (notify-user-if-possible
		    "~%Bad TCP timeout argument: ~s should be an integer."
		    value?)))))
    (when integer?
      (when (<f integer? 0)
	(notify-user-if-possible
	  "~%Cannot use negative TCP timeout (~d). The default of ~
           ~d ms will be used instead.~%"
	  integer?
	  default-tw-tcp-connect-interval-in-ms)
	(setq integer? default-tw-tcp-connect-interval-in-ms))
      ;; should there be a maximum?!
      integer?)))

(def-command-line-argument splashtime ((value? :keyword))
  (let ((integer?
	  (if value?
	      (or (read-fixnum-from-string value?)
		  (notify-user-if-possible
		    "~%Bad -spashtime argument: ~s should be an integer."
		    value?)))))
    (when integer?
      (cond
	((<f integer? minimum-telewindows-splashscreen-time-in-seconds)
	 (setq integer? minimum-telewindows-splashscreen-time-in-seconds))
	((>f integer? maximum-telewindows-splashscreen-time-in-seconds)
	 (setq integer? maximum-telewindows-splashscreen-time-in-seconds)))
      integer?)))


;;; The command-line-arguments `workspace' and `workspace-uuid' specify a
;;; workspace, by name or by UUID, which Telewindows should initially display.
;;; It overrides any workspaces in remembered-window-position-and-scale.

(def-command-line-argument (workspace (:systems ab telewindows)) (:keyword))
(def-command-line-argument (workspace-uuid (:systems ab telewindows)) (:keyword))



;;;; Providing Messages to Telewindows Users


;; OLD MESSAGE TO GET BACK:  (MHD 10/17/94)
;;
;; [Correct terminology, e.g., node-address, and add "network type"
;; to the information, where applicable.]

;; host/port-name-or-number args:
;;
;; If bad command line args (1st two):
;;       (notify-user-if-possible "~%Usage:~%   tw host [node-address]~%")
;;
;;
;; If good:
;;       (notify-user-if-possible
;;	 "~% [Telewindows: Connecting to host ~s at address ~a] "
;;	 (first parsed-telewindows-command-line-args?)
;;	 (second parsed-telewindows-command-line-args?))
;;
;;
;;
;; if bad network arg:
;;
;;	 (notify-user-if-possible "~&Unknown network type ~s.~%" network?)
;;	 (notify-user-if-possible "~&Using ~a by default.~%" default)
;;
;;
;; if bad tcptimeout arg:
;;
;;      (notify-user-if-possible
;;	  "~&Unable to parse \"-tcptimeout\" command-line keyword.  ~
;;         The default of ~d ms will be used instead."
;;	default-tw-tcp-connect-interval-in-ms)
;;
;;
;;
;; when attempting to connect:
;;
;;
;;    "~& [Telewindows: Connecting~a ... "
;;    (if (>f count 1)
;;	(format nil " (~d~a attempt in ~d second~a)"
;;		count
;;		(supply-ordinal-suffix count)
;;		number-of-seconds-of-attempting
;;		(if (=f number-of-seconds-of-attempting 1) "" "s"))
;;	"")
;;
;;
;; if unable to connect:
;;
;;       (notify-user-if-possible
;;	       "~& [Telewindows: Aborting after ~d attempts ~
;;                       to connect failed in ~d ~a]~%"
;;	       count
;;	       number-of-seconds-of-attempting
;;	       (if (=f number-of-seconds-of-attempting 1)
;;		   "second" "seconds"))











;;;; O/S Information for Telewindows



;;; *** NOTE: *** The following variable, telewindows-session-id, and its use in
;;; the function get-telewindows-miscellaneous-info below, is needed for
;;; compatibility with all versions of G2 7.x that have been released as of
;;; today, Apr. 20, 2006, i.e., 7.0r0 through 7.2r3 (collectively "G2 7.x").
;;; This code is being restored in the current mainline version of G2 8.3, after
;;; having been removed as of 8.0r0.  The value of this variable gets copied as
;;; a text string and included in the telewindows miscellaneous info plist as
;;; the value of telewindows-session-id. Any version of TW 7.0 or later that
;;; supports connections to G2 7.x must include this plist element for floating
;;; TW authorization mechanisms to function correctly.  The function on the G2
;;; server that uses this value is same-telewindows-session-p as used by
;;; count-floating-telewindows-in-service. (Note that other callers of
;;; same-telewindows-session-p are in G2 7.x's obsolete multiwindow-UI code,
;;; which is not reachable in the case of TW 8.x connections.)  This is the TW
;;; 8.x-side fix for bug HQ-5229974 "Maximum floating TW limit bypassed by
;;; multiple TW 8.x on same host to a G2 7.x".  A G2 7.x-side fix (as a patch
;;; initially) is being prepared concurrently.  (MHD 4/20/06)


;;; The system variable `telewindows-session-id' is initialized to a universally
;;; unique identifier for the Telewindows process in the form of a text string
;;; of length 32 consisting of only hex digits.  A copy of this string is passed
;;; along to G2 upon connection so that it can be used to recognize multiple TW
;;; connections from the same Telewindows session or process.  The way it is
;;; passed on to G2 is by including it with the properties
;;; get-telewindows-miscellaneous-info supplies, defined below.

(def-system-variable telewindows-session-id telewindows
  (:funcall make-telewindows-session-id))

(defun make-telewindows-session-id ()
  (let ((uuid (make-uuid)))
    (prog1 (twith-output-to-text-string
	     (twrite-uuid-printed-representation uuid))
      (reclaim-wide-string uuid))))

;; This was first introduced in G2 7.0a2, committed today, but 7.0a0 and 7.0a1
;; were released to customers without this but with the ability to connect
;; multiple windows from the same process.  (MHD 11/6/02)




;;; `Get-telewindows-miscellaneous-info' gives miscellaneous information
;;; in the form of  (gensym-cons) plist.
;;;
;;; The possible indicators at present are
;;;
;;;     network-host-name <OS network host name/string>
;;;
;;;        - where there may be several different host names, and
;;;        perhaps a notion of a "network" host name, this should
;;;        be that "network" host name, i.e., the one to use for
;;;        network connections, presumably following the most
;;;        conservative restrictions on the use of whitespace, etc.
;;;
;;;
;;;     os-user-name <OS user name/string>
;;;
;;;        - this is either a string, case sensitive, or
;;;        nil.  Conceivably the string could be "" (i.e., the
;;;        null string), if that's what the O/S seems to believe
;;;        it to be
;;;
;;;        - note that the G2 version of this differs in that
;;;        (1) it is stored as a symbol; (2) it can't be nil or
;;;        the empty string (||); and (3) if nil or empty here,
;;;        it would be the symbol USER in G2.  This is what's
;;;        used if there is no G2 user name.
;;;
;;;        - note that this may be different than the G2 user
;;;        name -- i.e., that kept on the g2-window panel, that's
;;;        a strictly-G2 piece of data, although it may be
;;;        "informed" by the OS user name in order to derive
;;;        its default.
;;;
;;;
;;;     os-type <OS type/symbol>
;;;
;;;        - this is a symbol naming the operating system type, using
;;;        the conventions around g2-operating-system in BOOTSTRAP.
;;;        Currently (jh, 12/28/95), this means that the symbol is one
;;;        of VMS, UNIX, DOS, or WIN32.
;;;
;;; Note: in some cases the host name cannot be determined.  The parameter
;;; `telewindows-name-for-unknown-host' gives a host name that indicates this
;;; problem, and is extremely unlikely to be used.  It is defined as the
;;; following text string: "no-host-name".  The network-host-name
;;; property would be set to this string if the host name could not be
;;; determined.

(defparameter telewindows-name-for-unknown-host #w"no-host-name")

;; Used in case get-local-host-name returns nil, which it clearly can, though
;; it's not very clearly documented currently!  (MHD 9/29/02)


(defun get-telewindows-miscellaneous-info ()
  (gensym-list
    'network-host-name (copy-text-string
			 (or (get-local-host-name)
			     telewindows-name-for-unknown-host))
    'os-user-name (foreign-get-user-name) ; a case-sensitive string (or nil)
    ;; local-home-directory (foreign-get-user-homedir)  ; add this??

    'os-type g2-operating-system
    'ui-toolkit (get-local-ui-toolkit-name) ; Added for 80a1 -fmw, 4/9/04
    'native-icons-limit (c-native-icons-limit)

    ;; next are license type/authorization level, based on OK file:
    'telewindows-authorized-products telewindows-authorized-products
    'telewindows-license-level telewindows-license-level
 
    ;; The following needed only for connections to G2 7.x; see note above doc
    ;; for telewindows-session-id. (MHD 4/20/06)
    'telewindows-session-id (copy-text-string telewindows-session-id)))





;;;; TCP Connect Interval



;;; `Set-up-telewindows-connection-timeout' sets up the connection timeout
;;; interval, if it is supplied on command line.  Currently (jh, 5/21/95), this
;;; interval defaults to the value of the constant
;;; `default-tw-tcp-connect-interval-in-ms', which happens to currently be 10000
;;; ms.

(defun set-up-telewindows-connection-timeout ()
  (when (normalized-string-equal	; Must allow "TCP-IP", "TCP_IP", "TCPIP"
	  #w"TCP-IP"		;   at least; this allows somewhat more,
					;   but that's ok.  New for 5.0.
					;   (MHD 3/2/96)
	  (telewindows-reroute-protocol? current-workstation))
    (let ((user-specified-timeout? (getf command-line-arguments 'tcptimeout)))
      (when user-specified-timeout?	; QA'd already if here
	(setf (desired-tw-tcp-connect-interval-in-ms current-workstation)
	      user-specified-timeout?)))
    (cond
      ((not (=f (c-set_tcp_connect_retry ; OK iff return status = 1
		  (desired-tw-tcp-connect-interval-in-ms current-workstation))
		1))
       (unless (eq verbosity-level 'silent)
	 (notify-user-if-possible
	   "[Telewindows: Unable to set TCP connect timeout interval.  ~
           The default of ~d ms will be used instead.]"
	   default-tw-tcp-connect-interval-in-ms))
       (setf (desired-tw-tcp-connect-interval-in-ms current-workstation)
	     default-tw-tcp-connect-interval-in-ms))
      ((and (not (=f (desired-tw-tcp-connect-interval-in-ms current-workstation)
		     default-tw-tcp-connect-interval-in-ms))
	    (eq verbosity-level 'verbose))
       (notify-user-if-possible
	 "[Telewindows: Using TCP connect timeout interval of ~d ms]"
	 (desired-tw-tcp-connect-interval-in-ms current-workstation))))))






;;; The foreign function `c-set_tcp_connect_retry' takes a fixnum argument, the
;;; number of milliseconds to wait for subsequent TCPIP connections to be made,
;;; and returns a fixnum status, 1 if successful, 0 if not.

(def-gensym-c-function c-set_tcp_connect_retry
		       (:fixnum-int "g2ext_set_tcp_connect_retry")
  ((:fixnum-int new-value-in-ms)))





;;;; Pasting from Telewindows



;;; `Paste-for-telewindows' ...

(defun-allowing-unwind write-message-group-for-paste-from-telewindows-to-g2
		       (gensym-window text-string request-id)
  (writing-icp-message-group
    ((icp-output-port-to-master-for-window? gensym-window))
    (send-icp-paste-from-telewindows-to-g2
      gensym-window text-string request-id)))

(defun paste-for-telewindows
    (gensym-window text-string request-id)
  (cond
    ((null (icp-output-port-to-master-for-window? gensym-window))
     ;; not connected yet? do nothing in this case
     )
    (t
     ;; Telewindows (connected) case:
     (write-message-group-for-paste-from-telewindows-to-g2
       gensym-window text-string request-id))))



(defun-allowing-unwind write-message-group-for-update-paste-availability-status
		       (gensym-window status)
  (writing-icp-message-group
    ((icp-output-port-to-master-for-window? gensym-window))
    (send-icp-update-paste-availability-status gensym-window status)))

(defun update-paste-availability-status-for-telewindows
    (gensym-window status)
  (cond
    ((null (icp-output-port-to-master-for-window? gensym-window))
     ;; not connected yet? do nothing in this case

     ;; Note: by not setting the status now, this should result in the status
     ;; being adjusted again after we do connect.
     )
    (t
     ;; Telewindows (connected) case:
     (setf (workstation-clipboard-has-text-p
	     (workstation-this-is-on gensym-window))
	   status)
     (write-message-group-for-update-paste-availability-status
       gensym-window status))))





;;;; Refreshing and Reshaping Telewindows




;;; `Refresh-telewindow' ...

(defun-allowing-unwind write-message-group-for-refresh-telewindow
		       (gensym-window
			 left-edge-of-update-area?
			 top-edge-of-update-area?
			 right-edge-of-update-area?
			 bottom-edge-of-update-area?)
  (writing-icp-message-group
    ((icp-output-port-to-master-for-window? gensym-window))
    (send-icp-request-to-refresh-window
      gensym-window
      nil
      (if left-edge-of-update-area? t)
      (or left-edge-of-update-area? 0)
      (or top-edge-of-update-area? 0)
      (or right-edge-of-update-area? 0)
      (or bottom-edge-of-update-area? 0))))

(defun refresh-telewindow
       (gensym-window native-window
	&optional
	left-edge-of-update-area?
	top-edge-of-update-area?
	right-edge-of-update-area?
	bottom-edge-of-update-area?)
  native-window					; not used
  (cond
    ((null					; not connected yet?
       (icp-output-port-to-master-for-window? gensym-window))
     (unless (telewindows-mdi-frame-p)
       (paint-telewindows-window-with-credits gensym-window)))
    (t
      ;; Telewindows (connected) case:
     (write-message-group-for-refresh-telewindow
       gensym-window
       left-edge-of-update-area?
       top-edge-of-update-area?
       right-edge-of-update-area?
       bottom-edge-of-update-area?)
      )))



;;; `Reshape-telewindow' ...

(defun-allowing-unwind write-message-group-for-reshape-telewindow
    (gensym-window)
  (writing-icp-message-group
      ((icp-output-port-to-master-for-window? gensym-window))
    (let* ((native-window (native-window? gensym-window)))
      (send-icp-request-to-reshape-window
	gensym-window
	0 0
	(get-width-of-native-window native-window)
	(get-height-of-native-window native-window))
      ;; This code supports the g2-window-x/y attributes of G2-WINDOW, added in
      ;; 7.1 to support the old multiwindow mode.
      (when (window-supports-move-telewindow gensym-window)
	(let* ((x (get-x-position-of-native-window native-window))
	       (y (get-y-position-of-native-window native-window)))
	  (unless (and (=f x (window-x-in-parent gensym-window))
		       (=f y (window-y-in-parent gensym-window)))
	    (send-icp-request-to-move-window gensym-window x y)))))))



(defun reshape-telewindow (gensym-window native-window)
  (if (null					; not connected yet?
	(icp-output-port-to-master-for-window? gensym-window))
     (unless (telewindows-mdi-frame-p)
       (paint-telewindows-window-with-credits gensym-window)))
  (cond
    ((null					; not connected yet?
       (icp-output-port-to-master-for-window? gensym-window))
     (make-or-revise-window-per-native-window
       gensym-window native-window)
     (refresh-telewindow gensym-window native-window))
    (t
     ;; Telewindows (connected) case:
     (write-message-group-for-reshape-telewindow gensym-window)
     )))



;;; `Idle-telewindows-while-displaying-credits' clears
;;;
;;;    (earliest-time-to-overwrite-credits? workstation)
;;;
;;; Before returning, if it came in with a non-nil value, it finishes waiting
;;; enough time to pass for users to have seen credits display for at least one
;;; second past that value.

(defun idle-telewindows-while-displaying-credits (workstation)
  (let ((earliest-time-to-overwrite?
	  (earliest-time-to-overwrite-credits? workstation)))
    (setf (earliest-time-to-overwrite-credits? workstation) nil)
    (unless (eql user-specified-telewindows-splashscreen-time-in-seconds? 0)
     (unless (telewindows-mdi-frame-p)
       (paint-telewindows-window-with-credits (window-for-workstation workstation))))
    (loop until (or (null earliest-time-to-overwrite?)
		    (>f (get-fixnum-time) earliest-time-to-overwrite?))
	  do
      (idle-telewindows workstation)
      (for-workstation-polling (workstation)
	(get-all-x11-events (native-window? system-window))))))





;;;; Making Telewindows Connections



;;; The function `telewindows-check-version-of-remote-g2' is where we can
;;; decide to which versions of g2 this telewindows is allowed to connect.
;;;
;;; It's called from make-tiling-pattern, which, of all places, seems to be the
;;; earliest point where we (icp-window-protocol-version gensym-window) is valid
;;; for both G2 3.0 and G2 4.0 connections.
;;;
;;; The parameter `allow-talking-to-a-pre-version-4-g2-p' controls this
;;; decision.

(defparameter allow-talking-to-a-pre-version-4-g2-p t)

;; If we didn't allow talking to a pre-version 4.0 G2, it would be an
;; unnecessary screw of users, with little for us to gain.  Let's not do it.
;; Review with management.  (MHD 2/5/95)

;; If parameter changes, review shutdown procedure. Message
;; should be moved to handle-telewindows-shutdown, and
;; reason-for-shutdown? should be set to something other
;; than requested. (lgibson 2/26/98)

(defun-void telewindows-check-version-of-remote-g2 (gensym-window)
  (cond
    ((reason-to-reject-connection-to-g2-p gensym-window)
     ;; Do we want to give the real reason?
     (unless (eq verbosity-level 'silent)
       (notify-user-if-possible
	 "[Telewindows: ~a connection to ~a G2 denied]"
	 (if (this-is-twng-p) "TWNG" "Telewindows")
	 (reason-to-reject-connection-to-g2-p gensym-window)))
     (close-telewindows-connection gensym-window))
    (t
     (initialize-gensym-window-after-connection gensym-window))))


;;; The function `reason-to-reject-connection-to-g2-p' returns a string if we
;;; should prevent TW from connecting to the G2 represented by the given G2
;;; window. Cf `reason-to-reject-telewindows-connection'

(defun reason-to-reject-connection-to-g2-p (gensym-window)
  (cond ((this-is-twng-p)
	 (unless (window-supports-chart-views-in-panes gensym-window)
	   "pre-8.3r0"))
	((talking-to-a-pre-version-4-g2-p gensym-window)
	 (unless allow-talking-to-a-pre-version-4-g2-p
	   "pre-4.0"))))


(defun make-telewindows-network-pathname (protocol host listener)
  (let* ((modified-protocol
	  (copy-with-hyphens-changed-to-underscores protocol)))
    (prog1
      (tformat-text-string "~a:~a:~a" modified-protocol host listener)
      (reclaim-text-string modified-protocol))))

(defun make-telewindows-network-configuration (workstation)
  (icp-list (copy-text-string
	      (telewindows-reroute-protocol? workstation))
	    (telewindows-reroute-host? workstation)
	    (telewindows-reroute-port? workstation)))

(def-system-variable counter-for-throughput-adjustment ;devious name
    TELEWINDOWS nil)
(defmacro place-for-per-process-task ()
  `counter-for-throughput-adjustment)

(defvar legacy-heartbeat-adjustment-priority 1) ;devious name
(defmacro priority-for-per-process-task ()
  `legacy-heartbeat-adjustment-priority)

(defvar legacy-heartbeat-adjustment-interval 2.0) ;devious name
(defmacro interval-for-per-process-task ()
  `legacy-heartbeat-adjustment-interval)

(defun-void do-legacy-heartbeat-adjustments () ;devious name
  (accept-process-license-queries)) ;what it really does

(defun-void schedule-tw-legacy-heartbeat-tasks-if-necessary () ;devious name
  (unless (schedule-task-in-place-p (place-for-per-process-task))
    (with-current-scheduling
      ((place-for-per-process-task)
       (priority-for-per-process-task)
       (interval-for-per-process-task)
       nil
       t)
    (do-legacy-heartbeat-adjustments))))


;;; `Try-to-connect-telewindows-workstation' ....
;;; ...
;;; If there are other problems, they may cause the value of
;;;
;;;    (icp-connection-open-p (telewindows-icp-socket? current-workstation))
;;;
;;; to be nil, and the value of
;;;
;;;    (reason-for-shutdown? (telewindows-icp-socket? current-workstation))
;;;
;;; to be NOT-ESTABLISHED.  If so, these problems will be handled inside the
;;; normal scheduling of telewindows, presumably by doing a shutdown there later
;;; on.

;;; if at first you don't succeed, succ, succ again:

(defun succeed-at-connecting-telewindows-workstation (icp-socket)
  (let* ((workstation (icp-socket-workstation icp-socket))
	 (window (window-for-workstation workstation)))
    (deregister-all-icp-callbacks 'icp-connect icp-socket) ;we're either connected or we're dead.
    (unless (eq (icp-connection-state icp-socket) icp-connection-running)
      (setf (telewindows-workstation-connection-state workstation)
	    'failed-to-connect)
      (return-from succeed-at-connecting-telewindows-workstation nil))
    (setf (telewindows-icp-socket? workstation) icp-socket)
    (initialize-telewindows-process-telewindows-icp-socket icp-socket)
    (when (icp-connection-open-p icp-socket)
      (c-x11-set-window-is-connected (native-window? window))
      (for-workstation-polling (workstation)
	(get-all-x11-events (native-window? window))) ;; Note A
      (setf (icp-output-port-to-master-for-window? window)
	    (icp-output-port icp-socket))
      (writing-icp-message-group	; initialize corresponding workstation
	  ((icp-output-port-to-master-for-window? window))
	(send-icp-initialize-telewindows-workstation;; Note B
	  workstation window))
      (setf (reason-for-shutdown? icp-socket) nil)
      (when (eq window system-window)
	;; splashscreen for first (system) window only
	(for-workstation-polling ((workstation-this-is-on window))
	  (idle-telewindows-while-displaying-credits
	    (workstation-this-is-on window)))) ;; Note A.
      (setf (telewindows-connection-license-level? workstation) nil) ; always reset
      (cond
	((telewindows-licensed-for-product-p 'development)
	 (when (eq verbosity-level 'verbose)
	   (notify-user-if-possible
	     "[Telewindows: authorized for connection to any G2.]"))
	 (handle-licensed-font-initializations-as-appropriate window)
	 (setf (telewindows-workstation-connection-state workstation)
	       'connected))
	(t
	 ;; Note that we can never break out of the
	 ;; connected-and-awaiting-license-level state at all if we are
	 ;; talking to 3.0.  So, unless you're using development (above
	 ;; case), if you're talking to 3.0, this will just hang for a while,
	 ;; and then time out.
	 (when (eq verbosity-level 'verbose)
	   (notify-user-if-possible
	     "[Telewindows: authorized for a ~a license; ~
                 will attempt to obtain a Floating Telewindows license~a.]"
	     (get-telewindows-product-name-from-level telewindows-license-level)
	     (case (get-telewindows-product-name-from-level telewindows-license-level)
	       (floating "")
	       (t " if necessary"))))
	 (setf (telewindows-workstation-connection-state workstation)
	       'connected-and-awaiting-license-level)
	 (setf (earliest-time-to-time-out-connection-attempt workstation)
	       (+f (get-fixnum-time)
		   ;; time out after parameterized number of seconds (ok to use
		   ;; same parameter, I think, as for connection -- it all seems
		   ;; to be part of connecting to the user)
		   (*f fixnum-time-interval-for-one-second
		       (timeout-in-seconds-for-telewindows-connection
			 workstation))))))
      icp-socket)))

(defun-allowing-unwind try-to-connect-telewindows-workstation
    (workstation)
  (check-system-time-against-primeval-time)
  (unless (eq verbosity-level 'silent)
    (notify-user-if-possible
      "[Telewindows: connecting to host ~s at port ~a via protocol ~a~a]"
      (telewindows-reroute-host? workstation)
      (telewindows-reroute-port? workstation)
      (telewindows-reroute-protocol? workstation)
      (secure-icp-string :use-default t)))
  (exit-if-system-time-too-early tw)
  (set-up-telewindows-connection-timeout)
  (let* ((network-config (make-telewindows-network-configuration workstation))
	 (icp-socket? (make-network-connection network-config)))
    (reclaim-icp-list network-config)
    (setf (telewindows-workstation-connection-state workstation)
	  (if icp-socket?
	      'connecting
	      'failed-to-connect))

    (when icp-socket?
      (register-icp-callback 'icp-connection-loss 'handle-telewindows-shutdown icp-socket?)
      (setf (reason-for-shutdown? icp-socket?) 'not-established)
      (setf (icp-socket-workstation icp-socket?) workstation)
      (setup-network-connection-for-connect icp-socket? 'succeed-at-connecting-telewindows-workstation))
    icp-socket?))

;; Note A: A non-nil value for icp-output-port-to-master-for-window?
;; toggles the behavior of the refresh and reshape handlers.  When NIL the
;; print the credit's screen, otherwise they send messages.  Notice that
;; get-all-x11-events and idle-telewindows-while-displaying-credits
;; are just wrappers around these event handlers.  In 3.0 it was possible
;; for messages to be sent before the initialize-telewindows-workstation
;; got sent.  That was pretty racy.  Now we are careful to set this slot,
;; and then immediately get the initialize-telewindows-workstation out the
;; door.  Note that a 3.0 telewindows attempting to connect to a 4.0
;; G2 could still do the racy thing, before it is shotdown as too old fashion.
;; Finally the call upon idle-telewindows-while-displaying-credits isn't
;; doing that at all, it's just enqueing reshape/resize messages to the G2.
;; I decided not to mess with that this late in the 4.0 release. - ben 6/21/95

;; Note B: The icp-socket connection is not considered established until after
;; the send-icp-initialize-telewindows-workstation (this is often the first
;; point at which it is actually possible to detect that the socket is not
;; really connected).  Thus, until this send, the reason-for-shutdown?  slot of
;; the icp-socket is set to 'not-established, and after the send, it is set to
;; nil.  This allows handle-telewindows-shutdown, the connection loss callback
;; function, to distinguish between a broken connection, and one that was never
;; established.  - AGH, 12/11/91





;;; `Try-to-obtain-telewindows-license-level' ...

(defun try-to-obtain-telewindows-license-level (workstation)
  ;; later: time out after waiting too long; could even decide here that
  ;; development versions are exempt from bouncing?!
  (cond
    ((telewindows-connection-license-level? workstation)
     (when (eq verbosity-level 'verbose)
       (notify-user-if-possible
	 "~%[Telewindows: received word back from G2 . . . ~
          Telewindows License Level: ~a]"
	 (get-telewindows-product-name-from-level telewindows-license-level))
       (when (getf (telewindows-connection-license-info workstation)
		   'g2-license-level)
	 (notify-user-if-possible
	   "[Telewindows: the target G2 is authorized for ~a Telewindows connections]"
	   (get-telewindows-product-from-level
	     (getf (telewindows-connection-license-info workstation)
		   'g2-license-level))))
       ;; say if Japanese/Korean is authorized or not?!
       (handle-licensed-font-initializations-as-appropriate
	 (window-for-workstation workstation)))
     (cond
       ((>f (telewindows-connection-license-level? workstation)
	    (telewindows-license-level-from-product 'unauthorized))

	(unless (eq verbosity-level 'silent)
	  (notify-user-if-possible "[Telewindows: Connected.]"))

	(setf (telewindows-workstation-connection-state workstation)
	      'connected))
       (t
	(unless (eq verbosity-level 'silent)
	  (notify-user-if-possible
	    "[Telewindows: Sorry.  Permission has been denied for access via this Telewindows.]"))
	(setf (telewindows-workstation-connection-state workstation)
	      'failed-to-connect))))
    ((>f (get-fixnum-time)
	 (earliest-time-to-time-out-connection-attempt workstation))
     (unless (eq verbosity-level 'silent)
       (notify-user-if-possible
	 "[Telewindows: Sorry.  Telewindows has timed out in its attempt to obtain ~
             permission to connect to G2.]"))
     (setf (telewindows-workstation-connection-state workstation)
	   'failed-to-connect))))




;;; `Set-up-initial-telewindows-routing' ...

(defun set-up-initial-telewindows-routing (telewindows-workstation)

  (macrolet ((s (to-slot from-slot)
	       `(setf (,to-slot telewindows-workstation)
		      (let ((value (,from-slot telewindows-workstation)))
			(if (or (gensym-string-p value)	; <- allow, but just
				(text-string-p value)) ;   for now! (MHD 3/2/96)
			    (copy-text-string value)
			    value)))))
    (s telewindows-reroute-protocol? telewindows-desired-protocol?)
    (s telewindows-reroute-host? telewindows-desired-host?)
    (s telewindows-reroute-port? telewindows-desired-port?)
    (s telewindows-reroute-init-string? telewindows-desired-init-string?))

  (setf (telewindows-workstation-connection-state telewindows-workstation)
	'being-rerouted))




(defun reroute-telewindows-connection (gensym-window protocol host port init-string)
  (let ((telewindows-workstation	; ok to assume it's telewindows
	  (workstation-this-is-on gensym-window)))
    (macrolet ((s (to-slot from-slot)
		 `(progn
		    (when (text-string-p (,to-slot telewindows-workstation))
		      (reclaim-text-string (,to-slot telewindows-workstation)))
		    (setf (,to-slot telewindows-workstation)
			  (,from-slot telewindows-workstation)))))
      (s telewindows-previous-protocol? telewindows-reroute-protocol?)
      (s telewindows-previous-host? telewindows-reroute-host?)
      (s telewindows-previous-port? telewindows-reroute-port?)
      (s telewindows-previous-init-string? telewindows-reroute-init-string?))

    (setf (telewindows-reroute-protocol? telewindows-workstation)
	  protocol)
    (setf (telewindows-reroute-host? telewindows-workstation)
	  host)
    (setf (telewindows-reroute-port? telewindows-workstation)
	  port)
    (setf (telewindows-reroute-init-string? telewindows-workstation)
	  init-string)

    (unless (eq verbosity-level 'silent)
      (notify-user-if-possible
	"[Telewindows: Rerouting to host ~s at address ~a]"
	host port))

    (shutdown-icp-socket-connection
      (telewindows-icp-socket? telewindows-workstation)
      'being-rerouted)))



;;; `Send-telewindows-home' ... called after a failure to connect.... assumes
;;; host, port, protocol, etc., information is non-nil in workstation.

(defun send-telewindows-home (telewindows-workstation)

  (unless (eq verbosity-level 'silent)
    (notify-user-if-possible
      "[Telewindows: Attempting to return to host ~s at address ~a]"
      (telewindows-reroute-host? telewindows-workstation)
      (telewindows-previous-port? telewindows-workstation)))

  (setf (telewindows-reroute-problem-report? telewindows-workstation)
	(tformat-text-string
	  "Unable to connect to host ~s at port ~a via protocol ~a~a"
	  (or (telewindows-previous-host? telewindows-workstation) "(unknown)")
	  (or (telewindows-previous-port? telewindows-workstation) "(unknown)")
	  (or (telewindows-reroute-protocol? telewindows-workstation) "(unknown)")
	  (secure-icp-string :use-default t)))
  (setf (telewindows-reroute-protocol? telewindows-workstation)
	(telewindows-previous-protocol? telewindows-workstation))
  (setf (telewindows-reroute-host? telewindows-workstation)
	(telewindows-previous-host? telewindows-workstation))
  (setf (telewindows-reroute-port? telewindows-workstation)
	(telewindows-previous-port? telewindows-workstation))
  (setf (telewindows-reroute-init-string? telewindows-workstation)
	(telewindows-previous-init-string? telewindows-workstation))

  (setf (telewindows-previous-protocol? telewindows-workstation) nil)
  (setf (telewindows-previous-host? telewindows-workstation) nil)
  (setf (telewindows-previous-port? telewindows-workstation) nil)
  (setf (telewindows-previous-init-string? telewindows-workstation) nil)

  (get-telewindows-workstation-ready-to-connect telewindows-workstation))



;;;; Running Telewindows



;;; Telewindows initialization is accomplished via the icp message types
;;; initialize-telewindows-workstation.  Initialize-telewindows-workstation
;;; performs all initialization required for the workstation on the G2 side so
;;; that the login dialog can proceed.

;;; Telewindows shutdown is accomplished by close-telewindows-connection.  On
;;; the G2 side, this calls log-out-workstation, sends a message to the
;;; Telewindows to have the connection closed, shuts down the connection on
;;; the G2 side, and reclaims the Telewindows workstation.

;;; See log-in-workstation and log-out-workstation for further information.

;;; The ICP connection is initiated by make-telewindows-icp-socket which is called
;;; from run-telewindows (in the telewindows process).  This (indirectly) calls
;;; make-icp-socket and adds the the new icp socket to active-icp-sockets for the
;;; telewindows process.  In the G2 process, process-icp-sockets is called
;;; periodically.  It calls check-for-pending-icp-requests which, if the
;;; telewindows process is making a connection, (indirectly) calls make-icp-socket
;;; and adds the socket to active-icp-sockets for the G2 process.

;;; The ICP connection is shut down by shutdown-icp-socket-connection, which is
;;; called from close-telewindows-connection (in the Telewindows process).  This
;;; marks the icp sockets (in both the Telewindows and G2 processes) as inactive
;;; but does not reclaim them.  The reclamation is done by
;;; purge-inactive-icp-sockets, called by process-icp-sockets, which is called
;;; periodically in both the Telewindows and G2 processes.

;;; The call to authorize-telewindows-if-ok (change-login-box-size) is made
;;; just after the catch-abort for level 0 is established -- at the very beginning
;;; of the run loop.  This check, if it fails, shuts down the entire process non-
;;; locally.

;;; [Much of the above is obsolete.  The following is new. (MHD 11/3/94)]
;;;
;;; Processing ICP Sockets.  No particular dynamic state should be assumed
;;; during the call to process-icp-sockets.  In particular, the special
;;; variables that make up the for-workstation-polling dynamic state should not
;;; be assumed.  The gensym window system is designed to allow any number of
;;; windows simultaneously, and process-icp-sockets must field requests to
;;; update any of them.  In 3.0, however, license was taken with this
;;; architecture, and the fact that we only had one window in practice led to
;;; the binding of these dynamic variables.  Then, certain ICP messages (around
;;; mouse handling, mostly) were built upon this assumption.  These have all
;;; been corrected, as of 4.0 post-Beta Rev. 0.  For compatibility with 3.0 and
;;; even early 4.0 (i.e., Beta Rev. 0), the global bindings are being put in
;;; for now, but will be removed when compatibility is not an issue.





;;; `Run-telewindows' is the top-level run loop for Telewindows.  The function
;;; run-telewindows consults do-error-trapping?  to decide whether or not to
;;; handle errors and then enters the real telewindows run loop, which is the
;;; function run-telewindows-1.
;;;
;;; Currently, errors are never "trapped" in development, and errors are always
;;; handled in distribution (since turning this switch off wouldn't help much,
;;; as Chestnut lacks a debugger).
;;;
;;; Error trapping provides a catcher to throw to, both when we trap a signal
;;; and when ab-lisp:error is called (by Chestnut, for example).

(defun-allowing-unwind run-telewindows (ignore-me)
  (declare (ignore ignore-me))
  #+(and chestnut-3 translator)
  (setq trun::*gc-silence* nil)
  (if do-error-trapping?
      (do-minimal-error-trapping (abort-telewindows-top-level 'error-trapped)
	(run-telewindows-1))
      (run-telewindows-1)))

(defun-for-top-level run-telewindows-1 ()
  (initialize-scheduler)
  (initialize-gensym-time)

  #-chestnut-3 ; Chun Tian (binghe), 2010/8/5
  (initialize-event-cycle-call-handlers)

  ;; jh, 12/22/95.  Unless we comment out the authorization code, the
  ;; "c-uninterruptible-sleep" fix in NETWORKS fails to work in Solaris
  ;; Lucid.
  (change-login-box-size)

  (when (secure-icp-requested-p)
    (set-up-secure-icp 'default))

  (establish-new-telewindows-workstation)
  (catch-abort (0)
    (with-scheduler-enabled
	(service-telewindows-workstations))))

(defun establish-new-telewindows-workstation ()
  (let ((gensym-window (make-or-revise-window-per-native-window
			 nil
			 ;; make-native-window calls c-x11-initialize
			 (make-native-window 'telewindows))))
    (set-up-telewindows-workstation gensym-window)))



;;;; Telewindows Event Loop


(defun-allowing-unwind tw-event-loop ()
  (loop do
    (with-handling-icp-messages t
      (when *scheduler-enabled?*
	(enqueue-scheduler-events-if-necessary nil))
      (loop do
	(g2-event-cycle-handling-windows-quit)
	(tw-execute-deferred-actions)))))



;;;; Running Telewindows (Continued)



;;; `Adjust-password-hash-if-necessary' is called with a windows parameter plist
;;; and the password in the clear, as from the command line.  If
;;; password-in-clear? is nil, or there is no user-name entry in the plist,
;;; nothing is done. Otherwise, (both the password and user name were provided),
;;; the plist gets modified by having an md5-password entry nconced onto the
;;; end.

;;; Note that only G2 5.0 or later can interpret the md5-password
;;; entry. Therefore, the password entry (encrypted in a different,
;;; lighter-weight fashion) is also sent in all cases currently.

(defun adjust-password-hash-if-necessary (window-parameters-plist password-in-clear?)
  (when password-in-clear?
    (let ((user-name? (getf window-parameters-plist 'user-name)))
      (when user-name?
	(nconc
	  window-parameters-plist
	  (gensym-list
	    'md5-password
	    (encode-password-via-md5 user-name? password-in-clear? nil)))))))

;; Note: this does not at present remove the password entry from the plist, but
;; it should do so provided we know the G2 is capable of handling the md5
;; password, which was not true until Telewindows/G2 5.0.  (MHD 4/22/02)




(defun set-up-telewindows-workstation (gensym-window)
  ;; in telewindows
  (let* ((telewindows-workstation
	   (make-telewindows-workstation gensym-window)))
    (setf (workstation-this-is-on gensym-window) telewindows-workstation)
    (gensym-push telewindows-workstation workstations-in-service)

    (unless (telewindows-twaxl-mode-p)
      (make-window-visible gensym-window))
    
    (for-workstation-polling (telewindows-workstation)
      (get-all-x11-events (native-window? gensym-window)))
    
    (when (null system-window)
      ;; For first window, establish system window, and ...
      (setq system-window gensym-window)
      ;; ... render splash screen.
      (refresh-telewindow gensym-window (native-window? gensym-window))
      
      (setf (earliest-time-to-overwrite-credits? telewindows-workstation)
	    (+f (get-fixnum-time)
		(get-telewindows-splashscreen-time-as-fixnum-time-interval)))
      (when (and user-specified-telewindows-splashscreen-time-in-seconds?
		 (eq verbosity-level 'verbose))
	(notify-user-if-possible
	  "[Telewindows: User-specified splashtime: ~d seconds (min/max/default: ~d/~d/~d)]"
	  user-specified-telewindows-splashscreen-time-in-seconds?
	  minimum-telewindows-splashscreen-time-in-seconds
	  maximum-telewindows-splashscreen-time-in-seconds
	  default-telewindows-splashscreen-time-in-seconds)))
    (setf (window-parameters-plist gensym-window)
	  (nconc (window-parameters-plist gensym-window)  
		 ;; copy top level conses and text strings: Note: review whether
		 ;; some extra copying is being done here! (MHD 4/2/02)
		 (copy-gensym-window-parameters-plist (get-command-line-arguments)) ; Note 1.
		 (get-telewindows-miscellaneous-info)))
    ;; default the user-name
    (unless (get-gensym-plist-element (window-parameters-plist gensym-window) 'user-name)
      (setf (get-gensym-plist-element
	      (window-parameters-plist gensym-window)
	      'user-name)
	    (copy-if-text-string	; fixes bug HQ-2775732 (MHD 6/4/99)
	      (get-gensym-plist-element (window-parameters-plist gensym-window) 'os-user-name))))
    ;; New per-TW solid background color (MHD 11/19/00) and pattern tiling feature -css
    (let ((background-color-or-tiling-pattern?
	    (get-background-color-or-tiling-pattern-from-command-line)))
      (when background-color-or-tiling-pattern?
	(setf (get-gensym-plist-element
		(window-parameters-plist gensym-window)
		'default-pane-background-color-or-tiling-pattern-rows)
	      background-color-or-tiling-pattern?)))
    ;; Send the password in two encodings, new and old.
    (adjust-password-hash-if-necessary
      (window-parameters-plist gensym-window)
      (get-command-line-keyword-argument #w"PASSWORD"))
    (macrolet ((s (slot indicator &optional build-symbol?)
		 `(let ((value?
			  (get-gensym-window-parameter
			    gensym-window ,indicator)))
		    (when value?
		      (setf (,slot telewindows-workstation)
			    (if ,build-symbol?
				(intern-text-string
				  (copy-text-string-with-case-conversion
				    value? ':all))
				value?))))))
      ;; two new ones: (MHD 4/9/99)
      (s specific-language-for-this-workstation? 'language t)
      (s cjk-typeface-preference-for-this-workstation? 'cjk-language t)

      (s telewindows-desired-protocol? 'network)
      (s telewindows-desired-host? 'remote-host-name)
      (s telewindows-desired-port? 'remote-port-name-or-number)
      (s telewindows-desired-init-string? 'init-string))
    (set-up-initial-telewindows-routing telewindows-workstation)
    telewindows-workstation))

;; Note 1. Password is still clear at this point.  It will become
;; encrypted, after we get connected and can determine the version
;; of G2 we are trying to speak with.



;; Can't this use set-gensym-window-parameter ?
(defun set-telewindows-window-plist-element (workstation indicator value)
  (loop for (indicator-1 value-1) on (window-parameters-plist (window-for-workstation workstation))
				  by #'cddr
	when (eq indicator-1 indicator)
	  do (when (text-string-p value-1)
	       (reclaim-text-string value-1))
	    (return
	      (setf (get-gensym-plist-element
		      (window-parameters-plist (window-for-workstation workstation)) indicator)
		    value))
	finally
	  (setf (window-parameters-plist (window-for-workstation workstation))
		(nconc (gensym-list indicator value)
		       (window-parameters-plist (window-for-workstation workstation))))))



;;; `Get-telewindows-workstation-ready-to-connect' attempts to transition the
;;; workstation from the state of BEING-REROUTED to DESIRES-CONNECTION. ...

(defun get-telewindows-workstation-ready-to-connect (workstation)

  ;; add problem report, if any, to the plist (for reroute/failure case only):
  (set-telewindows-window-plist-element
    workstation 'reroute-problem-report
    (if (telewindows-reroute-problem-report? workstation)
	(copy-text-string (telewindows-reroute-problem-report? workstation))
	nil))
  ;; init string setup:
  (set-telewindows-window-plist-element
    workstation 'init-string
    (if (telewindows-reroute-init-string? workstation)
	(copy-text-string (telewindows-reroute-init-string? workstation))
	nil))

  (reclaim-icp-list			; if rerouting has bad info in it
    (corresponding-icp-object-map-for-workstation workstation))
  (setf (corresponding-icp-object-map-for-workstation workstation) nil)

  (setf (telewindows-icp-socket? workstation) nil) ; already reclaimed at this point
  (setf (icp-output-port-to-master-for-window?
	  (window-for-workstation workstation))
	nil)
  ;; ajs (4/19/96)
  ;; Now using icp-conses rather than gensym-conses
  (reclaim-icp-tree
  ;;(reclaim-gensym-tree			; ?? questionable? paranoia?
    (prog1
	plist-of-corresponding-icp-object-maps-for-font-maps
      (setq plist-of-corresponding-icp-object-maps-for-font-maps
	    nil)))


  ;; (clear-window (window-for-workstation workstation) 'white)

  (let ((fixnum-time-now (get-fixnum-time)))
    (setf (earliest-time-to-time-out-connection-attempt workstation)
	  (+f fixnum-time-now
	      (timeout-in-seconds-for-telewindows-connection workstation)))
    (setf (number-of-connection-attempts-so-far workstation) 0)
    (setf (telewindows-network-pathname workstation)
	  (make-telewindows-network-pathname
	    (copy-text-string
	      (telewindows-reroute-protocol? workstation))
	    (telewindows-reroute-host? workstation)
	    (telewindows-reroute-port? workstation)))
    (setf (telewindows-workstation-connection-state workstation)
	  'desires-connection)))



(defparameter priority-of-tw-workstation-service 2) ;!!! arbitrarily chosen value -ncc, 1 Nov 1996


;;; `Service-telewindows-workstations' loops forever, calling
;;; schedule-telewindows-workstation-service and tw-event-loop.

(defun-allowing-unwind service-telewindows-workstations ()
  (schedule-telewindows-workstations-service)
  (tw-event-loop))



;;; `Schedule-telewindows-workstations-service' schedules a call to
;;; service-telewindows-workstation-once.  Note that
;;; service-telewindows-workstations-once may call back to
;;; schedule-telewindows-workstations-service to schedule further calls.
;;;
;;; The system variable `telewindows-service-workstations-task?' holds the
;;; scheduler task (or nil) to service telewindows workstations.  Its initial
;;; value is nil at the start of a G2 process.

(def-system-variable telewindows-service-workstations-task? telewindows nil)

(defun schedule-telewindows-workstations-service ()
  (with-current-scheduling
      (telewindows-service-workstations-task?
       priority-of-tw-workstation-service
       nil nil t)
    (service-telewindows-workstations-once)))




;;; `Service-telewindows-workstations-once' runs one top-level scheduling loop
;;; cycle for Telewindows.
;;;
;;; It first calls process-icp-sockets.
;;;
;;; Next, it calls poll-workstation.
;;;
;;; After that, it checks on security-related concerns (Telewindows
;;; authorization stuff entered-v5-mode-p).
;;;
;;; Next, it calls update-memory-limits-if-time-to-check, which adjusts caching
;;; limitations based on recent use.  Finally, it decides to call
;;; idle-telewindows, which lets the process sleep for a small amount of time,
;;; if
;;;
;;;  (1) process-icp-sockets completed its work and
;;;  (2) poll-workstation has no queued events (in need of processing).

(defun service-telewindows-workstations-once ()
  (cancel-task telewindows-service-workstations-task?)
  (let* ((more-events-in-queue? nil))
    ;; This is where all X events are read and transmitted.
    (setq more-events-in-queue? (service-current-telewindows-workstation))
    (let ((fixnum-time-now (get-fixnum-time)))
      (do-secret-destroy-if-necessary)
      (warn-of-tw-expiration-if-necessary fixnum-time-now)
      (update-memory-limits-if-time-to-check fixnum-time-now))
    (when more-events-in-queue?
      (schedule-telewindows-workstations-service))))

(defparameter tw-scheduled-tasks-time-limit (fixnum-time-interval 200))

(defun-simple run-one-tw-scheduler-cycle ()
  (with-temporary-creation run-tw-scheduler-cycle
    (loop with task-scheduling-start-time = (get-fixnum-time)
	  with time-slice-start-time = task-scheduling-start-time
	  for no-tasks-were-executed-this-pass
	      = (with-temporary-gensym-float-creation run-scheduler-task
		  (not (dequeue-and-execute-next-task)))
	  until (or no-tasks-were-executed-this-pass
		    (>=f (fixnum-time-difference
			   (setq time-slice-start-time (get-fixnum-time))
			   task-scheduling-start-time)
			 tw-scheduled-tasks-time-limit))
	  finally
	    ;; Note that service-workstation needs to be here at the bottom for two
	    ;; reasons.  First, the XPending() for keypress events for X11 needs to
	    ;; happen as close to the select() sleeping call as possible, to reduce
	    ;; the window of the race condition between the last call to to XPending()
	    ;; and the call to select().  The select() will not detect key events that
	    ;; happen inbetween these calls, so putting this here reduces the window
	    ;; of opportunity for the race condition.  Also, calls to XPending()
	    ;; implicitly cause an XFlush(), preventing output from lying idle in in
	    ;; Xwindows output queue.  Note that the implementation of get_event for
	    ;; Windows NT explicitly calls GdiFlush() to mimic this behavior.  Thus
	    ;; ends the lame proof that we won't leave output in the queues.  -jra &
	    ;; jed 1/15/97
	    (service-telewindows-workstations-once)
	    (enqueue-scheduler-events-if-necessary (not no-tasks-were-executed-this-pass)))))



;;; `Service-current-telewindows-workstation' services current-workstation, a Telewindows
;;; workstation, and returns true if any work was done.

(defun service-current-telewindows-workstation ()
  (loop with workstation
	with more-to-do = nil
	with copy-of-workstations-in-service
	  = (loop for w in workstations-in-service
		  collect w using gensym-cons-macro)
	while copy-of-workstations-in-service
	do (setq workstation (gensym-pop copy-of-workstations-in-service))
	when (memq workstation workstations-in-service)
	  ;; make sure it hasn't been removed since we started our loop; have
	  ;; more efficient test!!
	  do (for-workstation-polling (workstation)
	       (setq more-to-do (or (service-current-telewindows-workstation-1)
				    more-to-do)))
	finally (return more-to-do)))

;; The above version is extra careful about workstations being deleted from
;; workstations-in-service, new for the New UI/TW Pro. However, this is highly
;; inefficient as the number of workstations grow, though probably not
;; noticeably in practice.  Review soon!  (MHD 3/29/02)

;; This should be renamed -- it services _all_ workstations, not just the "current" workstation!


(defun service-current-telewindows-workstation-1 ()
  (inhibit-secret-checking-if-appropriate)
  (case (telewindows-workstation-connection-state current-workstation)
    (being-rerouted
     (unless (let ((socket (telewindows-icp-socket? current-workstation)))
	       (and socket
		    (or (member socket active-icp-sockets) ; see note A
			(icp-connection-open-p socket))))
       (get-telewindows-workstation-ready-to-connect current-workstation)))
    (desires-connection
     (try-to-connect-telewindows-workstation current-workstation))
    (connected-and-awaiting-license-level
     (try-to-obtain-telewindows-license-level current-workstation))
    (connected
     (poll-workstation))
    (connecting
     ;; allow display events to queue up while we're waiting for
     ;; G2 to get back to us about things.
     (get-all-x11-events current-workstation-native-window?))
    (disconnected
     nil)
    (failed-to-connect
     (unless (eq verbosity-level 'silent)
       (notify-user-if-possible
	 "[Telewindows: Unable to connect to host ~s at port ~a via protocol ~a~a]"
	 (or (telewindows-reroute-host? current-workstation) "(unknown)")
	 (or (telewindows-reroute-port? current-workstation) "(unknown)")
	 (or (telewindows-reroute-protocol? current-workstation) "(unknown)")
	 (secure-icp-string :use-default t)))
     (cond
       ((telewindows-previous-protocol? current-workstation)
	(send-telewindows-home current-workstation))
       (t
	(abort-telewindows-top-level 'failure-to-connect))))))	; for now

;; Now have to wait for the Telewindows workstation to be divorced from its
;; socket.  Consider entering a new state for this.  Consider having
;; a timeout! (MHD 5/24/95)



(defun accept-telewindows-connection-license-level
    (gensym-window license-level)
  (let ((telewindows-workstation (workstation-this-is-on gensym-window)))
    (setf (telewindows-connection-license-level? telewindows-workstation)
	  license-level)))


;;; `Accept-saved-user-settings-for-telewindows' ... Only called from G2 5.0+.

(defun accept-saved-user-settings-for-telewindows
    (gensym-window user-settings-plist)
  (let ((workstation (workstation-this-is-on gensym-window)))
    (loop for (indicator value) on user-settings-plist by #'cddr
	  as value-copy = (if (text-string-p value) (copy-text-string value) value)
	  do (set-telewindows-window-plist-element
	       workstation indicator value-copy))
    ;; Notify parent control (if any) of our session ID and HWND.
    (let ((session-id?
	    (get-gensym-window-parameter gensym-window 'session-id)))
      (when session-id?
	(c-x11-tell-control-our-session-id session-id?)))))



;;; `Accept-telewindows-connection-license-info' puts
;;; telewindows-connection-license-info into the slot of the same name in a
;;; telewindows workstation.
;;;
;;; It also sets telewindows-connection-license-level? slot based on the
;;; telewindows-connection-license-level plist element, which may be redundant
;;; in cases where both accept-telewindows-connection-license-level and
;;; accept-telewindows-connection-license-info are "called" by a newer G2.

(defun accept-telewindows-connection-license-info
    (gensym-window telewindows-connection-license-info)
  (let ((telewindows-workstation (workstation-this-is-on gensym-window)))
    (setf (telewindows-connection-license-level? telewindows-workstation)
	  (getf telewindows-connection-license-info
		'telewindows-connection-license-level))
    (setf (telewindows-connection-license-info telewindows-workstation)
	  telewindows-connection-license-info)))




;;; `Idle-telewindows' relinquishes the procesor, see
;;; native-window-polling-interval for details.

;;; Upon return it sets the flag that enables the generation of a synthetic mouse
;;; event.  See mouse-tracking for additonal details..

(defun idle-telewindows (workstation)
  (g2-event-wait)
  (setf (consider-synthetic-motion-event? workstation) t))



;;; `Tw-priority-of-data-service-function' ... currently returns 4.

(defun-simple tw-priority-of-data-service-function ()
  4)


;;;; System Access Definition for Telewindows


;;; Definition of the Telewindows System.

(define-system-access telewindows)

#+(and lispworks (not translator)) ; Chun Tian (binghe), 2010/8/5
(lw:defadvice (launch-telewindows launch-tw-in-new-thread :around) ()
  "Run G2 in new threads when being called within IDE"
  (if (env:tty-environment-p)
      (lw:call-next-advice)
    (progn
      (format t "Launching TW in new threads ...~%")
      (mp:process-run-function "TW" nil #'launch-telewindows))))

;;;; Spawning Processes from Telewindows

;; jh, 12/28/95.

;;; The void function `tw-handle-spawn-remote-process' is called in Telewindows,
;;; within the handler for the ICP message spawn-remote-process.  The
;;; command-line argument to this function, a text-string, is automatically
;;; reclaimed by the ICP handler, since the ICP value type text-string has an
;;; icp-value-reclaimer property.  Thus the command-line argument should not be
;;; reclaimed in this function.

(defmacro tw-handle-spawn-remote-process-1
    (index-of-result-parameter command-line spawn-as-command-line-p)
  (let ((spawner
	  (if spawn-as-command-line-p
	      'c-spawn_command_line_process
	      'c-spawn_executable_process)))
    (avoiding-variable-capture (command-line)
      `(let* ((argument-simple-p nil)
	      (simple-command-line
		(if argument-simple-p
		    ,command-line
		    (copy-text-string ,command-line))))
	 (with-temporary-gensym-float-creation tw-handle-spawn-remote-process
	   (let ((process-id
		   (allocate-managed-float (,spawner simple-command-line))))
	     (writing-icp-message-group ((icp-output-port current-icp-socket))
	       (send-icp-spawn-remote-process-reply
		 ,index-of-result-parameter
		 process-id))
	     (reclaim-managed-float process-id)))
	 (unless argument-simple-p ;ICP reclaims automatically if argument-simple-p
	   (reclaim-text-string simple-command-line))))))

(defun-allowing-unwind tw-handle-spawn-remote-command-line-process
    (index-of-result-parameter command-line)
  (tw-handle-spawn-remote-process-1
    index-of-result-parameter
    command-line
    t))

(defun-allowing-unwind tw-handle-spawn-remote-executable-process
    (index-of-result-parameter command-line)
  (tw-handle-spawn-remote-process-1
    index-of-result-parameter
    command-line
    nil))

(defun-allowing-unwind tw-handle-remote-process-exists-p
    (index-of-result-parameter process-id)
  (with-temporary-gensym-float-creation tw-handle-remote-process-exists-p
    (let* ((process-id-value (managed-float-value process-id))
	   (existence-status (c-process_exists process-id-value)))
      (reclaim-managed-float process-id)
      (writing-icp-message-group ((icp-output-port current-icp-socket))
	(send-icp-remote-process-exists-p-reply
	  index-of-result-parameter
	  existence-status)))))

(defun-allowing-unwind tw-handle-kill-remote-process
    (index-of-result-parameter process-id)
  (with-temporary-gensym-float-creation tw-handle-kill-remote-process
    (let* ((process-id-value (managed-float-value process-id))
	   (kill-status
	     (if (=e process-id-value  0.0)
		 -1
		 (c-kill_spawned_command_line process-id-value))))
      (reclaim-managed-float process-id)
      (writing-icp-message-group ((icp-output-port current-icp-socket))
	(send-icp-kill-remote-process-reply
	  index-of-result-parameter
	  kill-status)))))




;;;; Shutting Down



;;; `Handle-telewindows-shutdown' is the connection loss callback function for
;;; the Telewindows process.
;;;
;;; It previously simply called `abort-telewindows-top-level', which had, on all
;;; machines for which Telewindows is sold, shut down the process.  However, the
;;; advent of switchable Telewindows has changed matters.
;;;
;;; Namely, if the reason-for-shutdown? of icp-socket is BEING-REROUTED, this
;;; does not shut down the process.
;;;
;;; Thus, this connection loss callback function does not have to worry about
;;; reclaiming gensym-windows and workstations as close-telewindows-callback
;;; (the connection loss callback function for icp sockets used for Telewindows
;;; connections in a G2 process) does unless reason-for-shutdown? is
;;; BEING-REROUTED.
;;;
;;; Note however that it is crucial that abort-telewindows-top-level be called
;;; only from this callback function.  Otherwise, inactive icp sockets could be
;;; left in active-icp-sockets.

;;; Reasons for aborting Telewindows:
;;;
;;; failure-to-connect
;;; authorization-failure
;;; tw-expiration
;;; process-count-exceeded
;;; cannot-register-process
;;; error-trapped
;;; 

(defun abort-telewindows-top-level (reason?)
  (shut-down-ab-process reason?))

(defun-allowing-unwind handle-telewindows-shutdown (icp-socket clean?)
  (declare (ignore clean?))
  (let* ((reason? (reason-for-shutdown? icp-socket))
	 (workstation?
	   (or (get-workstation-for-icp-socket icp-socket) ;rerouting
	       (icp-socket-workstation icp-socket))) ;initial connection
	 (host-name
	   (or (if workstation? (telewindows-reroute-host? workstation?))
	       "(unknown)"))
	 (network
	   (or (if workstation? (telewindows-reroute-protocol? workstation?))
	       "(unknown network type)"))
	 (port
	   (or (if workstation? (telewindows-reroute-port? workstation?))
	       "(unknown)")))
    (case reason?
      (being-rerouted
       (when workstation?		; can't be nil?
	 (setf (telewindows-workstation-connection-state workstation?)
	       reason?)))
      (not-established
       ;; jh, 2/6/92.  Modified the following to complete the
       ;; "[Connecting ..." message.  See note toward the end of
       ;; run-telewindows-1 for further details.
       (unless (eq verbosity-level 'silent)
	 (notify-user-if-possible
	   "~%[Telewindows: no ~a listener at host ~s for port ~s]~%"
	   network host-name port)
	 ;; Improve this soon!!! -jv, 3/25/05
	 (c-message-box 0 #w"Telewindows"
			(tformat-text-string "Unable to connect to G2.  No ~a listener at host ~s for port ~s."
					     network host-name port)
			mb-ok 3))
       (setf (telewindows-workstation-connection-state workstation?)
	    'failed-to-connect))
      (t
       (protected-let
	   ((lead-in-text-string
	      (tformat-text-string
		"~a connection to host ~s at port ~a"
		network host-name port)
	      (reclaim-text-string lead-in-text-string))
	    (extra-text-string-1?
	      nil
	      (reclaim-text-string extra-text-string-1?)))
	 (setf (telewindows-workstation-connection-state workstation?) 'disconnected)
	 (unless (eq verbosity-level 'silent)
	   (notify-user-if-possible
	     "[Telewindows: ~a ~a]"
	     lead-in-text-string
	     (case reason?
	       (requested "closed as requested.")
	       (broken-while-receiving "broken while receiving data.")
	       (broken-while-transmitting "broken while transmitting data.")
	       ((protocol-out-of-synch-1
		  protocol-out-of-synch-2 protocol-out-of-synch-3
		  protocol-out-of-synch-4 protocol-out-of-synch-5)
		(setq extra-text-string-1?
		      (tformat-text-string
			"broken: protocol out of synch (case ~s)."
			(case reason?
			  (protocol-out-of-synch-1 1)
			  (protocol-out-of-synch-2 2)
			  (protocol-out-of-synch-3 3)
			  (protocol-out-of-synch-4 4)
			  (protocol-out-of-synch-5 5)
			  (protocol-out-of-synch-6 6))))
		extra-text-string-1?)
	       (unknown-message
		"broken: received a message of a type that is not known.")
	       (t "broken.")))))))

    ;; Notify ActiveX Control (if any) that we are exiting.
    (unless (memq reason? '(being-rerouted not-established))
      (c-x11-tell-control-our-session-id -1))

    ;; On Windows, there does not seem to be any more network or other events
    ;; forthcoming, so we need to give the scheduler an extra kick here.
    ;; Otherwise, TW doesn't exit until you click on its window. It does no harm
    ;; to call this on Unix also.
    (schedule-telewindows-workstations-service)

    (unless (or (eq reason? 'being-rerouted)
		(eq reason? 'not-established)) ; Because we may bounce back from failed redirect?
      (abort-telewindows-top-level reason?))))

;; Connection loss callback functions are called at the beginning of
;; reclaim-inactive-icp-sockets.  The call to abort-telewindows-top-level causes
;; most of the reclamation in reclaim-inactive-icp-sockets to be skipped.  This is
;; currently ok since, as mentioned above, abort-telewindows-top-level just shuts
;; down the process.  If this changes however, a mechanism would have to be
;; implemented where handle-telewindows-shutdown sets a flag rather than call
;; abort-telewindows-top-level directly.  Process-icp-sockets or something could
;; then call abort-telewindows-top-level.  ((Abort 0) is not a good way
;; to shut down for these reasons.)



;;; `Abort-telewindows-for-protocol-out-of-synch-case-6' is misleadingly named.  This is
;;; called by the security functions if the Telewindows is to be shut down due to an
;;; authorization failure.

(defun abort-telewindows-for-protocol-out-of-synch-case-6 ()
  (when workstations-in-service
    (let ((icp-socket (telewindows-icp-socket? (first workstations-in-service))))
      (setf (reason-for-shutdown? icp-socket) 'protocol-out-of-synch-6)	; misleading
      (handle-telewindows-shutdown icp-socket nil)))
  (setq workstations-in-service nil)	; a bit more permanent damage
  ;; may not even get here, but handle anyway
  (abort-telewindows-top-level 'authorization-failure))

;; Rather than aborting, consider doing more subtle damage such as messing
;; up the icp sockets.






;;;; Sending Telewindows Workstation Events



;;; `Send-telewindows-workstation-event' is called from poll-workstation to
;;; send input events over to our papa G2.  The local-event structure is
;;; owned and reclaimed by the caller, not by this function.
;;;
;;; As of G2 7.0 (as of 2/5/02), the plist slot of a local event may be sent
;;; over, but only in the case where it is non-null and only when talking to a
;;; similarly modern G2. In the case where it is sent over, the
;;; extended-telewindows-workstation-event ICP message type (which is new) is
;;; used; otherwise, the telewindows-workstation-event ICP message type (which
;;; is ancient) is used.

(defun-allowing-unwind send-telewindows-workstation-event (workstation local-event)
  (let ((socket? (telewindows-icp-socket? workstation)))
    (when (and socket?
	       (icp-connection-open-p socket?))
      (let* ((gensym-window (window-for-workstation workstation))
	     (icp-port (icp-output-port-to-master-for-window? gensym-window))
	     (code (local-event-key-code local-event))
	     (x (local-event-cursor-x local-event))
	     (y (local-event-cursor-y local-event))
	     (timestamp (local-event-timestamp local-event))
	     (plist? (local-event-plist local-event)))
	(if (and plist? (current-window-supports-event-plists gensym-window))
	    (writing-icp-message-group (icp-port)	
	      (send-icp-extended-telewindows-workstation-event
		workstation code x y timestamp plist?))
	    (writing-icp-message-group (icp-port)	
	      (send-icp-telewindows-workstation-event
		workstation code x y timestamp)))))))





;;;; Writing Lines of Text to the Telewindows Window








;;; The defvar current-telewindows-baseline is the baseline to be used for the
;;; next line of text to be output by write-list-of-text-lines-to-gensym-window.

(defvar current-telewindows-baseline
	default-telewindows-upper-margin)




;;; `Write-list-of-text-lines-to-gensym-window' writes list-of-text-lines on
;;; gensym-window using a font specified by font-size.  Font-size may be one
;;; of SMALL, LARGE, or EXTRA-LARGE.  If clear-window? is true, this paints
;;; the window white, and resets current-telewindows-baseline to default-
;;; telewindows-upper-margin, thus starting the list of lines at the top of
;;; the window.  If new-paragraph? is true, this adds a bit of vertical
;;; whitespace ahead of the lines of text to be drawn.  Elements of list-of-
;;; text-lines are not recycled by this routine; they are the responsibility
;;; of the caller.

(defun write-list-of-text-lines-to-gensym-window
    (gensym-window list-of-text-lines font-size clear-window? new-paragraph?)
  (let* ((left-edge-of-window (left-edge-of-window gensym-window))
	 (top-edge-of-window (top-edge-of-window gensym-window))
	 (right-edge-of-window (right-edge-of-window gensym-window))
	 (bottom-edge-of-window (bottom-edge-of-window gensym-window)))
    (when clear-window?					    ; Clear-window must happen outside update-window.
      (clear-window gensym-window 'white)
      (setq current-telewindows-baseline default-telewindows-upper-margin))
    (update-window
      gensym-window
      left-edge-of-window top-edge-of-window
      right-edge-of-window bottom-edge-of-window
      'write-list-of-text-lines-in-current-window list-of-text-lines font-size new-paragraph?)))

;; NOTE: this is defined as a stub function in G2-PATCHES, since it needs to
;; be called from FONT-FILES for Telewindows only. (MHD 11/10/92)




(defun write-list-of-text-lines-in-current-window (list-of-text-lines font-size new-paragraph?)
  (let* ((left-edge-of-window (left-edge-of-window current-window))
	 (top-edge-of-window (top-edge-of-window current-window))
	 (right-edge-of-window (right-edge-of-window current-window))
	 (bottom-edge-of-window (bottom-edge-of-window current-window)))
    (let ((color-difference
	    (color-difference
	      (map-to-color-value 'black) (map-to-color-value 'white)))
	  (distance-from-left-edge-of-window 50)
	  (paragraph-spacing 20)
	  (word-spacing
	    (case font-size (small 5) (large 6) (extra-large 6)))
	  (line-spacing
	    (case font-size (small 20) (large 24) (extra-large 32)))
	  (font-map
	    (case font-size (small '(hm14)) (large '(hm18))
		  (extra-large '(hm24)))))

      (when new-paragraph?
	(setq current-telewindows-baseline
	      (+f current-telewindows-baseline paragraph-spacing)))

      (loop for text-line in list-of-text-lines
	    do (setq current-telewindows-baseline
		     (+f current-telewindows-baseline line-spacing))
	       (add-from-line-of-text-to-current-window
		 nil
		 left-edge-of-window top-edge-of-window
		 right-edge-of-window bottom-edge-of-window
		 text-line (convert-to-text-width word-spacing)
		 font-map color-difference (normalized-scale) (normalized-scale)
		 (+r left-edge-of-window distance-from-left-edge-of-window)
		 (+r top-edge-of-window current-telewindows-baseline))))))

;; Ultimately, try to use these abstractions to replace much of the code in the
;; following section!





;;;; The Initial Telewindows Window



;;; `Paint-telewindows-window-with-credits' ...

(defun paint-telewindows-window-with-credits (gensym-window)
  (let* ((left-edge-of-window (left-edge-of-window gensym-window))
	 (top-edge-of-window (top-edge-of-window gensym-window))
	 (right-edge-of-window (right-edge-of-window gensym-window))
	 (bottom-edge-of-window (bottom-edge-of-window gensym-window)))
    (clear-window gensym-window 'white)
    (update-window
      gensym-window
      left-edge-of-window top-edge-of-window
      right-edge-of-window bottom-edge-of-window
      'paint-telewindows-window-with-credits-in-current-window)))


(def-system-variable tw-copyright-boilerplate-lines-of-text telewindows
  (:funcall make-copyright-boilerplate-lines-of-text-for-tw))



(defun paint-telewindows-window-with-credits-in-current-window ()
  (let* ((left-edge-of-window (left-edge-of-window current-window))
	 (top-edge-of-window (top-edge-of-window current-window))
	 (right-edge-of-window (right-edge-of-window current-window))
	 (bottom-edge-of-window (bottom-edge-of-window current-window))
	 (color-difference
	  (color-difference
	    (map-to-color-value 'black) (map-to-color-value 'white)))
	 (monumental-font-map '(HB72))
	 (font-map '(HM18))
	 (fine-print-font-map '(HM14))
	 (word-spacing #.(convert-to-text-width 24)) ; (irrelevant here)
	 (scale (normalized-scale)))

    ;; write product indentification text:
    (add-from-line-of-text-to-current-window
      nil
      left-edge-of-window top-edge-of-window
      right-edge-of-window bottom-edge-of-window
      #w"Telewindows" #.(convert-to-text-width 24)
      monumental-font-map color-difference
      scale scale
      (+r left-edge-of-window 100) (+r top-edge-of-window 150))

    ;; add little "R":
    ;;    Use HM24 font's Registered symbol, and hand-set it
    ;;    because using the same size font's symbol results in the
    ;;    appearance of a monster-sized Registered symbol.  (MHD 9/19/91)
    ;;    (Note: the HM24 font is bigger, but the HM18 font's R looks
    ;;    a bit nicer to me, so I went with it. -mhd)

    (add-from-line-of-text-to-current-window
      nil
      left-edge-of-window top-edge-of-window
      right-edge-of-window bottom-edge-of-window
      #.(stringw #.%trade-mark-sign)	; Changed to Registered, from TM, 8/28/91;
					; see note by in RUN with this date.
					; (MHD 8/28/91)
      word-spacing font-map color-difference
      scale scale
      (+r (+r left-edge-of-window 100)
	  (compute-width-of-text-line
	    #w"Telewindows" nil nil monumental-font-map word-spacing))
      (-r (+r top-edge-of-window 150)
	  41))		; top of R circle aligns with top of
					;   ascenders; derived by experimentation
    (loop with temporary-text-lines-cons
	    = (gensym-cons
		(twith-output-to-text-string
		  (twrite-system-version
		    (system-version current-system-name)))
		nil)
	  with text-lines
	    = (nconc
		temporary-text-lines-cons
		tw-copyright-boilerplate-lines-of-text)
	  as text-line in text-lines
	  as baseline-in-window
	     = (+r top-edge-of-window 200)
	     then (+r baseline-in-window 18)
	  do (add-from-line-of-text-to-current-window
	       nil
	       left-edge-of-window top-edge-of-window
	       right-edge-of-window bottom-edge-of-window
	       text-line
	       #.(convert-to-text-width 4)
	       fine-print-font-map color-difference
	       scale scale
	       (+r left-edge-of-window 150) baseline-in-window)
	  finally
	    (reclaim-text-string (first temporary-text-lines-cons))
	    (reclaim-gensym-cons temporary-text-lines-cons))))

;; This is somewhat temporary.

;; And increase word spacing in G2 credits, and add "TM" there!

;; Note, under add-from-line-of-text-to-current-window in module FONTS, that
;; clipped edges can be arbitrarily "loose".





;;;; Checking for Telewindows Connection Clogging



;;; Telewindows-connection-clogged? is in this file rather than in TELESTUBS
;;; (with the other clog-checking functions) because it is only used in
;;; telewindows, and because it is a convenient place to put secret
;;; authorization functions which can't be put into TELESTUBS.

;;; Note that telewindows-connection-clogged?  has built in hysteresis in that it
;;; uses two different limits:
;;;
;;;   (1) telewindows-max-number-of-message-groups-before-clogged
;;;
;;; to check if the connection is clogged, and
;;;
;;;   (2) telewindows-min-number-of-message-groups-before-unclogged
;;;
;;; to check if the connection is unclogged.

(defun telewindows-connection-clogged? (icp-socket I-am-alive-info)
  (perform-secret-checking)
  (cond
    ((with-bifurcated-version (no-telewindows-clogging-icp-version icp-socket)
       nil
       t)
     nil)
    ((if (not (icp-connection-clogged-p I-am-alive-info))
	 ;; now we use both numbers of message groups and icp bytes, as suggested
	 ;; by comments at the end of the function. --binghe
	 (or (>f (number-of-outstanding-message-groups I-am-alive-info)
		 telewindows-max-number-of-message-groups-before-clogged)
	     (>f (number-of-outstanding-icp-bytes I-am-alive-info)
		 telewindows-max-number-of-icp-bytes-before-clogged))
	 (not
	   (and
	     (<f (number-of-outstanding-message-groups I-am-alive-info)
		 telewindows-min-number-of-message-groups-before-unclogged)
	     (<f (number-of-outstanding-icp-bytes I-am-alive-info)
		 telewindows-min-number-of-icp-bytes-before-unclogged))))
     (let ((workstation?
	     (get-workstation-for-icp-socket icp-socket)))
       (when workstation?
	 ;; use "-verbose" with TWNG command line to unlock this notification:
	 (unless (eq verbosity-level 'silent)
	   (notify-user-if-possible
	     "[Telewindows: connection to ~s ~s is clogged.]"
	     (telewindows-reroute-host? workstation?)
	     (telewindows-reroute-port? workstation?)))))
     t)
    (t nil)))

;; It is better to use number of outstanding icp bytes than number of outstanding
;; message groups.  Consider using both! It may be useful to limit by number of
;; outstanding message groups in order to more strictly control the size of
;; message-group-ids-and-byte-counts alist.







;;;; C Function Loading



;;; Call `load-foreign-libraries-for-ab-when-appropriate' after the last c
;;; function defined in G2.  See its definition for more details.

(load-foreign-libraries-for-ab-when-appropriate)






;;;; Asian Language Support for Telewindows



;;; `Telewindows-authorized-for-japanese-p' returns true if either
;;; (tw-japanese-authorized-p) returns true, which it does iff Telewindows is
;;; authorized for Japanese (i.e., via the tw.ok file) or if evaluating a call
;;; to `floating-telewindows-authorized-for-japanese-p' returns true, which it
;;; does iff the current (Telewindows) workstation is licensed for floating use
;;; with a G2 that is licensed for Japanese.
;;;
;;; These are intended to be called at present from the FONTS module, where they
;;; are used to determine whether outline fonts (which bear royalties) have been
;;; paid for.
;;;
;;; In addition, for 5.0 Rev. ?, this same set has now been added for Korean:
;;; `telewindows-authorized-for-japanese-p' and
;;; `floating-telewindows-authorized-for-japanese-p'.

;;; Note on Korean Truetype font access: whenever we obtain a new license level,
;;; we check if Korean is authorized, and if it is, we load the Hangul font
;;; (hangul.ttf).  Gensym is currently obliged to pay royalties to Monotype on
;;; this font only for G2 or Telewindows that are authorized for Korean.  The
;;; Production and Licensing department at Gensym is instructed and has agreed
;;; (as of G2 4.0) to (a) routinely give authorizations for Japanese and Korean
;;; to customers from Japan and Korea, respectively, and (b) give such
;;; authorizations to any customer upon request.  Gensym must enforce the
;;; restriction to comply with its agreement with the font vendor (Monotype).
;;; (MHD 5.0 3/19/98 For Rev. 3)

;;; When we first obtain a new license level, the function
;;; `handle-licensed-font-initializations-as-appropriate' should be called to
;;; load the Korean font.  (It will be extended to handle other cases, should
;;; the need arise.)

(defun-simple telewindows-authorized-for-japanese-p (gensym-window)
  (let* ((workstation (workstation-this-is-on gensym-window))
	 (level? (telewindows-connection-license-level? workstation)))
    (or (if (and level?
		 (eq (get-telewindows-product-name-from-level level?)
		     'floating))
	    (floating-telewindows-authorized-for-japanese-p workstation))
	(tw-japanese-authorized-p))))

(defun-simple floating-telewindows-authorized-for-japanese-p (workstation)
  ;; floating
  (member 'japanese
	  (getf (telewindows-connection-license-info workstation)
		'g2-authorized-optional-modules)))

;; NOTE: at present, we do not decache Japanese fonts after switching from a
;; floating license authorized for Japanese to one not so authorized.  (MHD
;; 6/6/95)

(defun-simple telewindows-authorized-for-korean-p (gensym-window)
  (let* ((workstation (workstation-this-is-on gensym-window))
	 (level? (telewindows-connection-license-level? workstation)))
    (or (if (and level?
		 (eq (get-telewindows-product-name-from-level level?)
		     'floating))
	    (floating-telewindows-authorized-for-korean-p workstation))
	(tw-korean-authorized-p))))


(defun-simple floating-telewindows-authorized-for-korean-p (workstation)
  ;; floating
  (member 'korean
	  (getf (telewindows-connection-license-info workstation)
		'g2-authorized-optional-modules)))

(defun-simple telewindows-authorized-for-chinese-p (gensym-window)
  (let* ((workstation (workstation-this-is-on gensym-window))
	 (level? (telewindows-connection-license-level? workstation)))
    (or (if (and level?
		 (eq (get-telewindows-product-name-from-level level?)
		     'floating))
	    (floating-telewindows-authorized-for-chinese-p workstation))
	(tw-chinese-authorized-p))))


(defun-simple floating-telewindows-authorized-for-chinese-p (workstation)
  ;; floating
  (member 'chinese
	  (getf (telewindows-connection-license-info workstation)
		'g2-authorized-optional-modules)))

(defun handle-licensed-font-initializations-as-appropriate (gensym-window)
  (when (telewindows-authorized-for-korean-p gensym-window)
    (when (eq verbosity-level 'verbose)
      (notify-user-if-possible
	"[Telewindows: authorized for Korean: loading Hangul Truetype font]"))
    (load-hangul-font))
  (when (telewindows-authorized-for-chinese-p gensym-window)
    (when (eq verbosity-level 'verbose)
      (notify-user-if-possible
	"~%[Telewindows authorized for Chinese: loading Chinese Truetype font]~%"))
    (load-chinese-font)))





;;;; Telewindows Debugging



;;; For future reference while debugging aborts, here is what happens when
;;; Telewindows launches:
;;;
;;;   source      function
;;;   ------      --------
;;;   twmain.c     launch_telewindows_image
;;;   BOOTSTRAP    launch-telewindows-image
;;;   BOOTSTRAP    launch-system 'telewindows
;;;   TELEWINDOWS  (launch-function 'telewindows)                   ;define-system-access
;;;   TELEWINDOWS  launch-telewindows
;;;   LAUNCH       launch-system-process 'telewindows
;;;   PLATFORMS    funcall (system-top-level-function 'telewindows) ;define-system-access
;;;   TELEWINDOWS  run-telewindows-process-top-level
;;;                  <catch 'shutdown>
;;;   LAUNCH       run-system-process 'telewindows 'run-telewindows
;;;   TELEWINDOWS  run-telewindows
;;;                  <do-minimal-error-trapping>
;;;                  <abort-telewindows-top-level>





;;;; Telewindows Testing



;;; The rendering decaching test functions
;;; get-icp-indices-for-renderings-given-telewindow and
;;; check-telewindows-lru-queue are useful for telewindows testing.  Also,
;;; setting notify-when-reclaiming-icp-object? to t is useful for monitoring
;;; reclamation of icp objects.

;;; The following is a list of tests for TELEWINDOWS.

;;; 1.  Load kb with graph.  Show graph on both sides.  Hide.  Make another
;;; graph.  Monitor decaching.

;;; 2.  Load "ma:>agh>graph-decaching-test.kb".  Get one graph workspace.
;;; Hide.  Get three graph workspace.  Hide.  Get five graph workspace.
;;; Hide.  Monitor decaching metering graphs.

;;; 3.  Need to develop icon rendering decaching test.

;;; 4.  Need to develop test to monitor reclamation of workstations and
;;; gensym windows.

;;; 5.  Do all these tests with more than one telewindow hooked up.

;;; 6.  Besides testing reclamation of icp objects, need to test breaking icp
;;; connections.  Eventually, have test functions to make sure that icp index
;;; spaces are reclaimed properly and that they don't have pointers to reclaimed
;;; structures.

;;; See also rendering decaching test functions in module CONTROLS.




;;;; Stub Functions

;;; These functions implement functionality in G2 which is not needed (or
;;; applicable, really) in Telewindows.  For simplicity of the shared code,
;;; sometimes these functions might actually be called inside of Telewindows.
;;; (If there are any functions here which should NEVER be called from TW,
;;; those functions should be moved to tw-patches and be made to call (signal-
;;; error-for-undefined-function-called-from-telewindows) in their bodies.)
;;; All of these functions are defined, in G2, in files which Telewindows
;;; doesn't use.  In the comment lines, the files given name where, in TW,
;;; the function is used (not where the function is actually defined).

;;; Note, this first one returns a non-nil value, which kind of makes it not
;;; really a stub, in my book.  (jv, 2/24/04)


;; NETWORK-ACCESS-ALLOWED-P                             INT2, TELESTUBS

(defun network-access-allowed-p (access-agent access-type &optional frame?)
  (declare (ignore access-agent access-type frame?))
  t)



;;; The rest of the functions always return nil, either implicitly or explicitly


;; RECLAIM-EVALUATION-VALUE                             UTILITIES3

(defun reclaim-evaluation-value (x)
  (declare (ignore x))
  nil)


;; KILL-FOREIGN-IMAGE-UNCONDITIONALLY                   PRIMITIVES

(defun kill-foreign-image-unconditionally (x)
  (declare (ignore x)))


;; WRITE-NAME-DENOTATION-FOR-SLOT                       UTILITIES1

(defun write-name-denotation-for-slot (slot-description class-description)
  (declare (ignore slot-description class-description)))


;; WRITE-TYPE-SPECIFICATION                             UTILITIES1

(defun write-type-specification (system-name)
  (declare (ignore system-name)))


;; WRITE-BLOCK-OR-EVALUATION-VALUE                      UTILITIES1

(defun write-block-or-evaluation-value (x)
  (declare (ignore x)))


;; RECLAIM-FRAME-SERIAL-NUMBER                          INT1, TELESTUBS

(defun reclaim-frame-serial-number (fsn)
  (declare (ignore fsn)))


;; INITIALIZE-IMAGE-PALETTE-OF-NEW-GENSYM-WINDOW        WINDOWS1

(defun initialize-image-palette-of-new-gensym-window (gensym-window)
  (declare (ignore gensym-window)))


;; NEGOTIATE-TELEWINDOWS-LICENSING                      WINDOWS1

(defun negotiate-telewindows-licensing (gensym-window)
  (declare (ignore gensym-window)))


;; RECLAIM-NATIVE-ICONS-TABLE                           WINDOWS1

(defun reclaim-native-icons-table (table)
  (declare (ignore table)))


;; REFRESH-WINDOW-OF-RECTANGLE                          WINDOWS4

(defun refresh-rectangle-of-window
    (gensym-window left? top? right? bottom?)
  (declare (ignore gensym-window left? top? right? bottom?))
  nil)


;; CHECK-SHAPE-OF-WINDOW-FOR-G2                         TELESTUBS

(defun check-shape-of-window-without-lookahead-for-g2
    (gensym-window native-window)
  (declare (ignore gensym-window native-window)))


;; POST-TELEWINDOWS-CONNECTION-CLOGGED                  TELESTUBS

(defun post-telewindows-connection-clogged (g2-window? clogged?)
  (declare (ignore g2-window? clogged?)))


;; SET-UP-WORKSTATION-ON-AB-SIDE                        TELESTUBS

(defun set-up-workstation-on-ab-side
    (workstation gensym-window v5-mode-p)
  (declare (ignore workstation gensym-window v5-mode-p)))


;; RECLAIM-PARTIAL-COMMAND                              TELESTUBS

(defun reclaim-partial-command (pc)
  (declare (ignore pc)))


;; PARTIAL-COMMAND-P-FUNCTION                           TELESTUBS

(defun partial-command-p-function (thing)
  (declare (ignore thing))
  nil)



;;; `handle-extend-current-text-string-error' - called (via funcall) from
;;; UNICODE.  Was made a continuable error during the original implementation
;;; of wide-strings, in unicode.lisp.  Is not really continuable; you'll just
;;; run into a "too large byte-vector-16" error if you try to go on.  But, make
;;; this echo what the old code used to do.  -jv, 10/5/07

(defun handle-extend-current-text-string-error ()
  (cerror
    "Continue"
    #.extend-current-text-string-error-message))

