(in-package :AB)

;;; Moved from os-settings.lisp

(defconstant c-argv-n-strlen-failure -1)
  
(defconstant c-environment-var-strlen-failure -1)  
  
  
;;; Moved from keyboards.lisp

;;;; Constants for Keyboards, Key Indexes, and Key Codes





(defconstant number-of-key-index-bits 11) ; increased from 10 to 11 (MHD 3/21/95)

;; keep this and other stuff in this area in synch with ext/c/graphics.h


(defconstant maximum-number-of-key-indexes (ash 1 number-of-key-index-bits))

(defconstant maximum-key-index (1- (ash 1 number-of-key-index-bits)))



(defconstant key-index-bits (1- (ash 1 number-of-key-index-bits)))
  
;;; `Number-of-unicode-character-bits' gives the number of bits that make up the
;;; least significant bits of a key code that are used to represent a `Unicode
;;; character key', which encodes Unicode character input events.  
  
(defconstant number-of-unicode-character-bits 16)
(defconstant unicode-character-bits (1- (ash 1 number-of-unicode-character-bits)))
  
;; -- UPDATE: increased available bits 11 to 16, replacing <spare>, <symbol>,
;; <hyper>, <super>, and <apple>, which had been bits 11, 12, 13, 14, and 15,
;; respectively, and which had all been unused at least since versions 4.0 of
;; G2/TW.  Also changed the label of the heretofore unused (previously
;; "ignored") 25th bit to "Unicode" to indicate that the key code represents a
;; Unicode character input event.  (MHD 5/17/99)




;; If the values of the key modifier bits are changed, we have to
;; touch the following modules:  KEYDEFS, F-KEYS, EDIT,
;; RUN, MENUS, EDIT, CONTROLS, WORKSTATION, PLATFORMS, MOVES,
;; TELESTUBS, WINDOWS3.
;; After the release of G2 2.0, these values will have to
;; remain fixed.  -pto 29aug89

;; graphics.h will also have to be kept up-to-date.

(defconstant menu-bit           (ash 1 25))        ; Hack -fmw, 1/15/02
(defconstant unicode-bit        (ash 1 24))
(defconstant control-bit        (ash 1 23))
(defconstant meta-bit               (ash 1 22))
(defconstant extend-char-bit        (ash 1 21))
(defconstant compose-char-bit          (ash 1 20))
(defconstant alternate-bit          (ash 1 19))
(defconstant shift-bit              (ash 1 18))
(defconstant caps-lock-bit          (ash 1 17))
(defconstant double-bit             (ash 1 16))                    ; For double mouse clicks

(defconstant unicode-mask            (logxor (lognot 0) unicode-bit))
(defconstant control-mask            (logxor (lognot 0) control-bit))
(defconstant meta-mask               (logxor (lognot 0) meta-bit))
(defconstant extend-char-mask   (logxor (lognot 0) extend-char-bit))
(defconstant compose-char-mask        (logxor (lognot 0) compose-char-bit))
(defconstant alternate-mask          (logxor (lognot 0) alternate-bit))
(defconstant shift-mask              (logxor (lognot 0) shift-bit))
(defconstant caps-lock-mask          (logxor (lognot 0) caps-lock-bit))
(defconstant double-mask             (logxor (lognot 0) double-bit))

;; Why aren't these just (lognot control-bit)?  Bignums in Chestnut?


(defconstant key-code-bits (logand (1- (ash 1 25))))        ; 25 bits


(defconstant key-modifier-bits (logior unicode-bit
                                       control-bit
                                       meta-bit
                                       extend-char-bit
                                       compose-char-bit
                                       alternate-bit
                                       shift-bit
                                       caps-lock-bit
                                       double-bit))



#-no-macros
(defconstant largest-key-modifier-bit-combination key-modifier-bits)

#-no-macros
(defconstant smallest-key-modifier-bit-combination 0)


(defconstant illegal-key-code -1)

(defconstant illegal-key-index (logand illegal-key-code key-index-bits))

;;; Moved from utilities0.lisp



(defconstant maximum-oversized-managed-simple-vector-size 1048576)

;;; The parameter `maximum-managed-array-buffer-size' contains the maximum
;;; length of a buffer of a managed array, currently 1024.  The parameter
;;; `maximum-managed-array-size' contains the maximum size of a managed array,
;;; currently 1,046,528.  This number is 2048 less than 1 Meg since one element
;;; of the spine array needs to hold the total size of the managed array and
;;; other element needs to hold the objects which marks the spine vector as a
;;; managed-array.  This leaves two fewer spots for buffers.

(defconstant maximum-managed-array-buffer-size 1024)


;;; `managed-array-index-offset' gives the offset for the first "real" index into
;;; the managed array. This is relevant when the managed array is "in-place" that is,
;;; all of the elements are in the spine

(defconstant managed-array-index-offset 2)

;;; The constant `extra-wide-string-bv16-elements' holds the number of extra
;;; elements stored in a byte-vector-16 that is being used as a wide string.
;;; There are two extra elements at the front to hold the "fill pointer" and one
;;; extra element at the end to hold a null wide-character.

(defconstant extra-wide-string-bv16-elements 3)

;;; The constant `maximum-length-for-user-gensym-strings' specifies the maximum
;;; length allowed for a user text string.  This limit should be used in the
;;; appropriate evaluators, instructions, roles, file i/o system procedures, and
;;; gsi.  This number is four times `maximum-length-for-user-text-strings' in
;;; order to allow for the possibility of maximally large Unicode characters
;;; (four bytes each).

(defconstant maximum-length-for-user-gensym-strings
  ; modified by SoftServe 10/17/08;
  400000000)
  ; end of SoftServe changes




;;; The constant `maximum-length-for-user-text-strings' specifies the maximum
;;; length allowed for a user text string.  This limit should be used in the
;;; appropriate evaluators, instructions, roles, file i/o system procedures, and
;;; gsi.

;;; In G2 5.x, this limit was 65,533, far, far less than
;;; maximum-wide-string-length, which was was exactly 1,048,576. (**) In 6.0, this
;;; limit was upped to 1,000,000, a round number (for humans), which is many
;;; thousands less than maximum-wide-string-length, which has been upped to
;;; 2,097,149 (which is 2^21-3, by the way).
;;;
;;; ** SoftServe. In 8.4, this limit was upped to 100,000,000, a round number (for humans), 
;;; which is many thousands less than maximum-wide-string-length, which has been upped to
;;; 268,435,453 (which is 2^28-3, by the way).

(defconstant maximum-length-for-user-text-strings
  ; modified by SoftServe 10/17/08;
  100000000)
  ; end of SoftServe changes

;;; The constant `maximum-length-for-user-symbols' specifies the maximum length
;;; in wide characters for a user symbol.  Note that due to storage of lisp
;;; symbol names as UTF-G, this could in the worst case baloon into 4X this
;;; number of (ascii) characters in a gensym string.  This limit is set for 6.0
;;; as 65,533 (= 2^16 - 3), the same limit as G2 5.1.

(defconstant maximum-length-for-user-symbols
  #.(- (expt 2 16) 3))  ; 65533


;;; Moved from utilities2.lisp

;;; The constant `sparse-array-layer-order' contains the log base 2 of the size
;;; of the buffers in the sparse array.  Currently it is set at 5, giving 32
;;; element buffers.

(defconstant sparse-array-layer-order 5)

;;; The constant `sparse-array-max-depth' gives the maximum depth of
;;; a sparse array. It is sufficient to hold an array with indices from
;;; 0 through most-positive-fixnum

(defconstant sparse-array-max-depth
  (floor (log most-positive-fixnum 2) sparse-array-layer-order))


;;; Moved from transcode.lisp

(defconstant intern-string-buffer-length 32)

;;; Moved from iso8859.lisp

(defconstant 8859-part-size 128)
(defconstant 8859-code-mask #x7f)
(defconstant first-8859-part-number 1)
(defconstant last-8859-part-number 10)


;;; Moved from token.lisp

;;; `maximum-state-transition-args'
(defconstant maximum-state-transition-args 4)

;;; `state-transition-user-defined-transition-test-sentinel'

(defconstant state-transition-user-defined-transition-test-sentinel -1)

(defconstant no-tokenizer-match-start-index -1)
(defconstant no-tokenizer-match-end-index 0)


;;; Moved from os-error.lisp

(defconstant post-mortem-ring-buffer-default-length 50)
(defconstant size-of-backtrace-stack-for-internal-error 1000)

(defconstant maximum-index-in-backtrace-stack-for-internal-error
  (1- size-of-backtrace-stack-for-internal-error))

;;; The constant `size-of-basic-backtrace-information' gives the minimum number
;;; of entries on the backtrace stack.  For a description of the layout of the
;;; backtrace stack, see the documentation for
;;; backtrace-stack-for-internal-error and
;;; room-for-basic-backtrace-information-p.

(defconstant size-of-basic-backtrace-information 3)
(defconstant gensym-error-buffer-initial-size 1000)

;;; The global variable `gensym-error-message-buffer' is updated whenever a
;;; translated image calls the Lisp functions error or cerror.


;;; Moved from platforms.lisp

;;;; Interface to the native window system


;;; This subsection defines G2's lowest-level interface to the underlying
;;; window system, whether it be X11 or MS Windows.  Although the function
;;; names may lead one to think that they apply only to X windows, they
;;; actually apply to both.  The MS Windows port works by defining, in C,
;;; versions of all these X11 functions.

;;; There are a couple more interface functions in images.lisp...

;;; The X11 ALU Functions: x11-or, x11-copy, x11-xor ...

;; These constants have to be maintained in parallel with those in the module
;; XWINDOWS.C.

(defconstant x11-or 0) ; Unused.
(defconstant x11-copy 1)
(defconstant x11-xor 2)
(defconstant x11-and 3) ; Unused
(defconstant x11-stippled 4)
(defconstant x11-transparent-copy 5) ; Unused.

;;; Gensym X Windows Event Codes

;; These constants have to be maintained in parallel with those in the module
;; GRAPHICS.H

(defconstant x11-number-of-bits-in-event-codes 4)            ; Allow for 15 X event types.
(defconstant x11-event-codes-mask (1- (ash 1 x11-number-of-bits-in-event-codes)))
(defconstant x11-key-code-shift (- x11-number-of-bits-in-event-codes))

(defconstant x11-no-more-events        -1)
(defconstant x11-nullevent        0)
(defconstant x11-keypress        1)                ; KeyPress
(defconstant x11-button-press        2)                ; ButtonPress. The mouse button is encoded in the keycode.
(defconstant x11-button-release        3)                ; ButtonRelease
(defconstant x11-pointer-motion        4)                ; MotionNotify
(defconstant x11-exposure        5)                ; Expose
(defconstant x11-reshape        6)                ; ConfigureNotify
(defconstant x11-enter          7)
(defconstant x11-leave          8)
(defconstant x11-focus-in       9)
(defconstant x11-focus-out     10)
(defconstant x11-control       11)
		 
(defconstant specified-max-clipboard-text-length #.(- (expt 2 16) 1))
(defconstant allocated-clipboard-text-length #.(expt 2 16))

(defconstant clipboard-reading-results-vector-length 3)

(defconstant latin-1-clipboard-read-results-entry 0)
(defconstant x-compound-text-clipboard-read-results-entry 1)
(defconstant unicode-text-clipboard-read-results-entry 2)

(defconstant clipboard-read-results-failure-code #xFFFF)	 

(defconstant gensym-windows-minimum-supported-dpi 36)
                                        ; lowered to support .5 magnification;
                                        ;   was 50 in 4.0 preBeta Phase 2
(defconstant gensym-windows-maximum-supported-dpi 200)
(defconstant gensym-windows-standard-dpi 75)
(defconstant gensym-windows-minimum-supported-scale .50)
(defconstant gensym-windows-maximum-supported-scale 2.66)

(defconstant maximum-polygon-points 500) ; must be in sync with C code

;;; `Original-icp-window-protocol-version' is the classic protocol.  There are
;;; some slight variations within this version number, see the code below for
;;; comments.

(defconstant original-icp-window-protocol-version 0)

;;; `Icp-window-protocol-supports-monochrome-raster-lists' is discussed in
;;; Graphs1.

(defconstant icp-window-protocol-supports-monochrome-raster-lists 2)

;;; `Icp-window-protocol-supports-transparent-copy' added x11-transparent-copy,
;;; x11-and, and x11-or to the x11 transfer modes.  (Some of these were
;;; in the protocol but unimplmented.)

;;; This version of the protocol is necessary and currently sufficent to allow
;;; a gensym-window to use :paint-infered-from-xor as it's transfer mode.

;; Versions with this protocol value were shipped to Intelsat as 3.1p1 so they
;; could play with outline fonts.  - ben 7/13/92

(defconstant icp-window-protocol-supports-transparent-copy 3)

;;; `Icp-window-protocol-supports-setting-protocol-level' indicates that we can
;;; send the message set-window-protocol-version..

(defconstant icp-window-protocol-supports-setting-protocol-level 4)

;;; `Icp-window-protocol-supports-scrolling' indicates that the we can
;;; copy rectangles from one portion of the screen to another, using the
;;; message scroll-rectangle-in-current-window.

(defconstant icp-window-protocol-supports-scrolling 4)

(defconstant icp-window-protocol-supports-v4-mouse-messages 5)

;; This predicate can get by using the previously defined flag/version, since
;; they coincided to within a couple of versions, and were/will be released at
;; the same time.  I don't want to worry about users of the popular 4.0 Beta
;; Phase 1 Telewindows crashing while viewing 4.0 Beta Phase 2 Trend charts.
;; (MHD 2/5/95)

(defconstant icp-window-protocol-supports-floating-telewindows 6) ; (MHD 1/30/95)

;;; Telewindows protocol version 8 supports a new message,
;;; `force-graphics-on-window' which can either do a flush or a sync.

(defconstant icp-window-protocol-supports-force-graphics 7)

;;; Telewindows protocol version 9 supports sending a message to the
;;; client process which will trigger a reply indicating that the
;;; message was recieved.  See `ping-drawing'.

(defconstant icp-window-protocol-supports-ping-drawing 8)

;;; Telewindows protocol version 10 supports sending a new message,
;;; `set-telewindows-connection-license-info', which sends
;;; telewindows-connection-license-info, a richer description of the licensing
;;; capabilities of the G2 and its Telewindows client; see TELEWINDOWS and
;;; TELESTUBS for further info.

(defconstant icp-window-protocol-supports-telewindows-connection-license-info 9)

;; (MHD 5/19/95)

;;; Telewindows protocol version 11 supports using the Cyrillic characters
;;; formatted according to the characters of the Slavic Swiss TrueType font,
;;; aka SLAVIC14, slavic18, slavic24.  Note that no new messages have been
;;; created for this purpose; only a new range of Gensym characters can now
;;; be rendered on the Telewindows side as other than blobs (or whitespace).

(defconstant icp-window-protocol-supports-slavic-font 10)

;; (MHD 7/26/95)

;;; Telewindows protocol version 12 supports the system procedures
;;; g2-spawn-remote-process(), g2-remote-process-exists(), and
;;; g2-kill-remote-process().

(defconstant icp-window-protocol-supports-remote-processes 11) ;jh, 12/29/95

;;; Telewindows protocol version 13 supports the system procedure
;;; g2-spawn-remote-process-with-arguments().

(defconstant icp-window-protocol-supports-remote-executables 12) ;jh, 10/4/96

;;; Telewindow protocol version 14 supports the icp-message-function
;;; orient-and-paint-line-of-text-to-current-scratchpad-raster ie
;;; text in icons. (pbk 1/18/95)

(defconstant icp-window-protocol-supports-oriented-text-in-scratchpad-rasters 13)

;;; Telewindow protocol version 15 supports the icp-message functions
;;; I-will-now-send-and-receive-wide-strings and
;;; I-will-now-send-and-receive-wide-strings.  (MHD 3/2/96)
;;; These message functions have been removed, and replaced by
;;; the icp-version protocol (see int3.lisp).  - rh 8/8/96

(defconstant icp-window-protocol-supports-text-strings-as-wide-strings 14)

;;; Telewindow protocol version 16 passes the user's password (taken off
;;; the command line) as a string.  Older versions passed it via a fixnum.

;;; G2's capable of this protocol level demand it.  In other words an old
;;; TW (preversion 15) can not talk to an new G2 (version 15 or greater).

;;; TW's capable of this protocol can talk to old G2.  They will pass the
;;; encrypted password in the older style when the sense that the channel
;;; is running that way.

(defconstant icp-window-protocol-supports-md5-password-encryption 15)

;;; The macro `ICP-window-protocol-supports-saving-user-settings-p' is used for the
;;; password saving protocol between 5.0 Telewindows and 5.0 G2.  Note that
;;; qualified participants make use of the
;;; set-telewindows-connection-license-info ICP message type code, which is new
;;; in 5.0.

(defconstant icp-window-protocol-supports-saving-user-settings 16)

;;; Telewindows protocol version 17 supports the icp-message-function
;;; paint-filled-polygon-in-current-scratchpad-raster

(defconstant icp-window-protocol-supports-un-decomposed-polygons 18)

;;; Telewindow protocol version 16 supports the icp-message-function
;;; draw-icon-background-image. (pbk 10/8/96)

(defconstant icp-window-protocol-supports-polychrome-icon-images 17)

(defconstant icp-window-protocol-supports-native-cut-and-paste 19)

(defconstant icp-window-protocol-supports-request-for-paste-availability 20)

(defconstant icp-window-protocol-supports-unicode-character-events 21)

(defconstant icp-window-protocol-supports-raster-stipples 22)

(defconstant icp-window-protocol-supports-24bit-image-painting 23)

(defconstant icp-window-protocol-supports-wide-polyline 24)

(defconstant icp-window-protocol-supports-offscreen-drawing 25)

(defconstant icp-window-protocol-supports-event-plists 26)

(defconstant icp-window-protocol-supports-native-widgets 27)

(defconstant icp-window-protocol-supports-image-tiling 28)

(defconstant icp-window-protocol-supports-nms-menus 29)

(defconstant icp-window-protocol-70r0 30)

(defconstant icp-window-protocol-70-prerelease
  (+ icp-window-protocol-supports-offscreen-drawing 1)) ; > highest protocol as of 6.2r2, 3/17/03

(defconstant icp-window-protocol-supports-native-printing 31)  
  
(defconstant icp-window-protocol-supports-nms-posting-callbacks 32)  
  
(defconstant icp-window-protocol-supports-native-icons 33)  
  
(defconstant icp-window-protocol-supports-move-telewindow 34)  
  
(defconstant icp-window-protocol-supports-native-progress-bar 35)  
  
(defconstant icp-window-protocol-supports-basic-dialogs 36)  
  
;; Win32 defined constants
(defconstant sm-cxscreen 0)
(defconstant sm-cyscreen 1)
(defconstant sm-cxvscroll 2)                ; width of vertical scroll bar
(defconstant sm-cyhscroll 3)                ; height of vertical scroll bar
(defconstant sm-cycaption 4)                ; height of a standard caption
(defconstant sm-cxborder 5)
(defconstant sm-cyborder 6)
(defconstant sm-cxdlgframe 7)
(defconstant sm-cydlgframe 8)
(defconstant sm-cyvthumb 9)
(defconstant sm-cxhthumb 10)
(defconstant sm-cxicon 11)
(defconstant sm-cyicon 12)
(defconstant sm-cxcursor 13)
(defconstant sm-cycursor 14)
(defconstant sm-cymenu 15)
(defconstant sm-cxfullscreen 16)
(defconstant sm-cyfullscreen 17)
(defconstant sm-cykanjiwindow 18)
(defconstant sm-mousepresent 19)
(defconstant sm-cyvscroll 20)
(defconstant sm-cxhscroll 21)
(defconstant sm-debug 22)
(defconstant sm-swapbutton 23)
;(defconstant sm-reserved1 24)
;(defconstant sm-reserved2 25)
;(defconstant sm-reserved3 26)
;(defconstant sm-reserved4 27)
(defconstant sm-cxmin 28)
(defconstant sm-cymin 29)
(defconstant sm-cxsize 30)
(defconstant sm-cysize 31)
(defconstant sm-cxframe  32)                ; thickness of sizing border
(defconstant sm-cyframe 33)
(defconstant sm-cxmintrack 34)
(defconstant sm-cymintrack 35)
(defconstant sm-cxdoubleclk 36)
(defconstant sm-cydoubleclk 37)
(defconstant sm-cxiconspacing 38)
(defconstant sm-cyiconspacing 39)
(defconstant sm-menudropalignment 40)
(defconstant sm-penwindows 41)
(defconstant sm-dbcsenabled 42)
(defconstant sm-cmousebuttons 43)
(defconstant sm-secure 44)
(defconstant sm-cxedge 45)
(defconstant sm-cyedge 46)
(defconstant sm-cxminspacing 47)
(defconstant sm-cyminspacing 48)
(defconstant sm-cxsmicon 49)
(defconstant sm-cysmicon 50)
(defconstant sm-cysmcaption 51)
(defconstant sm-cxsmsize 52)
(defconstant sm-cysmsize 53)
(defconstant sm-cxmenusize 54)
(defconstant sm-cymenusize 55)
(defconstant sm-arrange 56)
(defconstant sm-cxminimized 57)
(defconstant sm-cyminimized 58)
(defconstant sm-cxmaxtrack 59)                ; max width of a window (via resize border)
(defconstant sm-cymaxtrack 60)                ; max height ...
(defconstant sm-cxmaximized 61)
(defconstant sm-cymaximized 62)
(defconstant sm-network 63)
(defconstant sm-cleanboot 67)
(defconstant sm-cxdrag 68)
(defconstant sm-cydrag 69)
(defconstant sm-showsounds 70)
(defconstant sm-cxmenucheck 71)
(defconstant sm-cymenucheck 72)
(defconstant sm-slowmachine 73)
(defconstant sm-mideastenabled 74)
(defconstant sm-mousewheelpresent 75)
(defconstant sm-xvirtualscreen 76)
(defconstant sm-yvirtualscreen 77)
(defconstant sm-cxvirtualscreen 78)
(defconstant sm-cyvirtualscreen 79)
(defconstant sm-cmonitors 80)
(defconstant sm-samedisplayformat 81)
(defconstant sm-cxdialog 82)                ; These are our own, which usurp the Win32 defn (none so far).
(defconstant sm-cydialog 83)                ; Each is 100 * pixels/dialog unit in GUI font.
(defconstant number-of-system-metrics 84)
  
(defconstant maximum-interval-between-new-time-for-uuid #.(* 1.0 60 10)) ; 10 minutes

(defconstant uuid-offset-mask 255)

;;; Moved from networks.lisp

(defconstant ne-blocked-value 0)
(defconstant ne-eof-value    -1)
(defconstant ne-error-value  -2)



;;; Moved from int2.lisp

(defconstant minimum-message-series-size-before-suspending 8000)

(defconstant minimum-message-series-size-before-beginning-new-series 20000)

;;; Moved from int4.lisp

;;; The following three constants (use-all-network-protocols,
;;; use-tcpip-protocol-only, and use-no-network-protocols) must agree with their
;;; counterparts in /bt/ab/ext/c/networks.h (ALL, TCP_IP, and UNKNOWN_PROTOCOL,
;;; respectively).

(defconstant use-all-network-protocols 14)
(defconstant use-tcpip-protocol-only   13)
(defconstant use-no-network-protocols  -1)
(defconstant g2-product-tag  1)
(defconstant gsi-product-tag 2)


;;; Moved from windows1.lisp

(defconstant minimum-intensity-for-white 192)		    ; 192? once decided, should never change

;;; The defparameter `transparent-color-value' defines the magic color
;;; value which we use to represent transparency.  It must be a value
;;; which is distinguishable from any color difference, but which also
;;; fits into an ICP unsigned-integer.  Since this value goes over the wire,
;;; it may not be changed lightly.

(defconstant transparent-color-value (ash 1 24))


;;; Moved from windows2.lisp

;;; The constant `no-stipple-value' is used as the value of a stipple when there
;;; should be no stippling (or something that might be called 0% gray, or
;;; white).

(defconstant no-stipple-value 0)


;;; Moved from windows3.lisp

;; These constants are sent over the wire, and so should not be changed.  They
;; currently agree with Win32, and presumably will forever.

(defconstant ps-solid 0)
(defconstant ps-dash 1)
(defconstant ps-dot 2)
(defconstant ps-dashdot 3)
(defconstant ps-dashdotdot 4)
(defconstant ps-userstyle 7)

(defconstant ps-endcap-round #x0000)
(defconstant ps-endcap-square #x0100)
(defconstant ps-endcap-flat #x0200)

(defconstant ps-join-round #x0000)
(defconstant ps-join-bevel #x1000)
(defconstant ps-join-miter #x2000)

;; Opcodes for the omnibus ICP message below.

(defconstant enable-offscreen-drawing 1)
(defconstant disable-offscreen-drawing 2)
(defconstant bitblt-offscreen-pixmap 3)
(defconstant reclaim-offscreen-pixmap 4)


;;; Moved from windows4.lisp

;; Window frame types, for g2ext_x11_initialize
(defconstant frame-type-none 0)		; New TW/AXL/SWV mode
(defconstant frame-type-classic 1)
(defconstant frame-type-child 2)	; Original plugin mode
(defconstant frame-type-sdi 3)
(defconstant frame-type-mdi 4)

(defconstant nip-wintype-classic  0)	; Window types for g2ext_x11_create_window

(defconstant nip-wintype-mask #xF)

(defconstant nip-show-window 1)		; Commands to g2ext_x11_manage_window
(defconstant nip-move-window 2)		; Keep in sync with graphics.h
(defconstant nip-reshape-window 3)
(defconstant nip-raise-window 4)
(defconstant nip-lower-window 5)
(defconstant nip-destroy-window 6)
(defconstant nip-caption-window 7)
(defconstant nip-inflate-window 8)
(defconstant nip-scroll-window 9)	; Unused?
(defconstant nip-cerase-window 10)	; Erase complement of rect region
(defconstant nip-set-max-size 11)
(defconstant nip-restyle-window 12)	; Change window style and exStyle
(defconstant nip-zorder-window 13)	; Set windows layer position (Z-Order)
(defconstant nip-set-icon 14)
(defconstant nip-set-closeable 15)
(defconstant nip-rescale-window 16)	; Reshape, with no client-side refresh needed.
(defconstant nip-set-background-color 17)
(defconstant nip-size-window 18)

(defconstant sw-hide 0)			; Subcommands to nip-show-window (they match Win32)
(defconstant sw-shownormal 1)
(defconstant sw-showminimized 2)
(defconstant sw-maximize 3)
(defconstant sw-shownoactivate 4)
(defconstant sw-show 5)
(defconstant sw-minimize 6)
(defconstant sw-showminnoactive 7)
(defconstant sw-showna 8)
(defconstant sw-restore 9)
(defconstant sw-showdefault 10)

(defconstant ws-overlapped   #x0000)	; High 16 bits of the Win32 styles.
(defconstant ws-popup        #x8000)
(defconstant ws-child        #x4000)
(defconstant ws-minimize     #x2000)
(defconstant ws-visible      #x1000)
(defconstant ws-disabled     #x0800)
(defconstant ws-clipsiblings #x0400)
(defconstant ws-clipchildren #x0200)
(defconstant ws-maximize     #x0100)
(defconstant ws-caption      #x00c0)	; (logiorf ws-border ws-dlgframe)
(defconstant ws-border       #x0080)
(defconstant ws-dlgframe     #x0040)
(defconstant ws-vscroll      #x0020)
(defconstant ws-hscroll      #x0010)
(defconstant ws-sysmenu      #x0008)
(defconstant ws-thickframe   #x0004)
(defconstant ws-group        #x0002)
(defconstant ws-tabstop      #x0001)
(defconstant ws-minimizebox  #x0002)
(defconstant ws-maximizebox  #x0001)

(defconstant ws-ex-dlgmodalframe  #x00001) ; Win32 extended styles.
(defconstant ws-ex-noparentnotify #x00004)
(defconstant ws-ex-topmost        #x00008)
(defconstant ws-ex-acceptfiles    #x00010)
(defconstant ws-ex-transparent    #x00020)
(defconstant ws-ex-mdichild       #x00040)
(defconstant ws-ex-toolwindow     #x00080)
(defconstant ws-ex-windowedge     #x00100)
(defconstant ws-ex-clientedge     #x00200)
(defconstant ws-ex-contexthelp    #x00400)
(defconstant ws-ex-right          #x01000)
(defconstant ws-ex-left           #x00000)
(defconstant ws-ex-rtlreading     #x02000)
(defconstant ws-ex-ltrreading     #x00000)
(defconstant ws-ex-leftscrollbar  #x04000)
(defconstant ws-ex-rightscrollbar #x00000)
(defconstant ws-ex-controlparent  #x10000)
(defconstant ws-ex-staticedge     #x20000)
(defconstant ws-ex-appwindow      #x40000)

;; unused: (defconstant ws-ex-one-line-edit  #x00002)

(defconstant size-restored  0)		; Status codes from WM_SIZE.
(defconstant size-minimized 1)
(defconstant size-maximized 2)
(defconstant size-maxshow 3)
(defconstant size-maxhide 4)
(defconstant status-floated 8)		; Extended codes for XTP. Sync with Twng.h
(defconstant status-docked 9)		; Other bits give side, nextTo info
(defconstant status-autohidden 10)
(defconstant status-unknown 11)
(defconstant status-expanded 12)	; New in XTP 9.51
(defconstant status-collapsed 13)
(defconstant status-closed 14)		; Destroyed
(defconstant status-attached 15)
(defconstant status-docked-left 16)
(defconstant status-docked-top 17)
(defconstant status-docked-right 18)
(defconstant status-docked-bottom 19)
(defconstant status-hidden 20)

(defconstant cw-usedefault -30000)	; Really #x80000000, but that's not a fixnum.

(defconstant sort-column-default -1)    ; For TabularView sort settings
(defconstant sorting-order-default 1)

(defconstant swp-hwnd-top -1)		; Codes for SetWindowPos
(defconstant swp-hwnd-bottom -2)	; Sync with set_window_zorder in ext/c/mdi.c
(defconstant swp-hwnd-topmost -3)
(defconstant swp-hwnd-notopmost -4)

(defconstant dt-left    #x0000)		; Flags for DrawText()
(defconstant dt-center  #x0001)
(defconstant dt-right   #x0002)
(defconstant dt-vcenter #x0004)
(defconstant dt-bottom  #x0008)
(defconstant dt-wordbreak #x0010)
(defconstant dt-singleline #x0020)
(defconstant dt-expandtabs #x0040)
(defconstant dt-editcontrol #x2000)
(defconstant dt-path-ellipsis #x4000)
(defconstant dt-end-ellipsis #x8000)



;;;; Native Editor

;; Keep all these in sync with ext/c/editor.c
(defconstant editor-create 1)		    ; Generic view commands
(defconstant editor-destroy 2)
(defconstant editor-print 3)
(defconstant editor-show 4)
;; Added by SoftServe
(defconstant editor-modal 5)
(defconstant editor-add-toolbar-button 6)
;; End of SoftServe changes
(defconstant editor-cancel 7)
(defconstant editor-clear-breakpoint 20)    ; Breakpoint commands, shared with debugger.
(defconstant editor-disable-breakpoint 21)
(defconstant editor-set-breakpoint 22)

(defconstant editor-clear-breakpoints 24)
(defconstant editor-syntax-repair 28)

(defconstant editor-reset 30)		    ; Reset font and shape (as on KB reset)
(defconstant editor-set-text 31)
(defconstant editor-insert-text 32)
(defconstant editor-syntax 33)
(defconstant editor-completions 34)
(defconstant editor-arglist 35)
(defconstant editor-exit 36)
(defconstant editor-notes 37)
(defconstant editor-apply 38)
(defconstant editor-disable 39)		    ; Disable or enable the editor's dialog window.
(defconstant editor-enable 40)
(defconstant editor-set-grammar 41)	    ; 0=free text, 1=procedure/rule
(defconstant editor-set-options 42)	    ; Bitmask: 0=SingleLineComments, 1=SingleLineEditor

;; 8.2r2
(defconstant editor-set-tabs 43)	    ; Set tab width

;; 8.3a0
(defconstant editor-cursor-moved 44)	    ; TW->G2 notifications
(defconstant editor-text-inserted 45)
(defconstant editor-text-deleted 46)
(defconstant editor-incremental-updates 47) ; Enables new notifications, disables full-text send.
(defconstant editor-exit-new 48)
(defconstant editor-apply-new 49)
(defconstant editor-completions-new 50)
(defconstant editor-clear-output 51)	    ; G2->TW
(defconstant editor-append-output 52)
(defconstant editor-hotspot-clicked 53)	    ; TW->G2
(defconstant editor-replace-text 54)
(defconstant editor-delete-text 55)
(defconstant editor-text-saved 56)	    ; G2->TW

(defconstant editor-goto-item 58)	    ; TW->G2
(defconstant editor-beep 59)		    ; G2->TW
;; Added by SoftServe
(defconstant editor-custom-toolbar 60)
(defconstant editor-undo 61)		    ; GENSYMCID-844
(defconstant editor-maximum-number-of-undos-to-remember 62)

(defconstant editor-grammar-free-text 0)    ; Values for grammar
(defconstant editor-grammar-procedure/rule 1)

(defconstant editor-style-normal 0)
(defconstant editor-style-category 1)
(defconstant editor-style-completion 2)

(defconstant editor-options-single-line-comments 1) ; Bits for editor-set-options
(defconstant editor-options-single-line-editor 2)
(defconstant editor-options-query-on-close 4)


;;; Moved from images.lisp

(defconstant black-threshold-in-color-intensity 128)

(defconstant number-of-bits-of-gray-in-the-extended-gray-palette 6)

(defconstant free-bits-per-icp-byte 15)


(defconstant maximum-background-tile-area #.(* 128 128))


;;; Moved from parse.lisp

(defconstant maximum-size-of-category-set-as-list 8)
  
(defconstant max-instance-rule-chaining 512)  
  

  
;;; Moved from parse2.lisp

(defconstant default-reduction '1)
(defconstant max-number-of-regexps-to-cache 25)  
  
;;; `max-number-of-lexing-tables-to-cache' - is a constant,
;;; because there's currently no way to change it.  Maybe
;;; there should be, though.  It could be a slot in a
;;; system table.

(defconstant max-number-of-lexing-tables-to-cache 100)  
  
;;; Moved from frames2.lisp

;;; `Maximum-number-of-generic-methods' is a constant.  After changing, force a
;;; full recompile  .

(defconstant maximum-number-of-generic-methods 57)


;;; Moved from frames2a.lisp

(defconstant old-mask-for-saved-frame-flags 7531546)


;;; Moved from frames4.lisp

(defconstant use-full-size-of-with-output-wide-string-cutoff 256)


;;; Moved from frames5.lisp

(defconstant maximum-length-of-menu-of-names 10000)


;;; Moved from panes.lisp

(defconstant minimum-image-plane-serial-number #.(- (ash 2 22)))

(defconstant maximum-image-plane-serial-number #.(ash 2 22))
  
(defconstant assumed-standard-image-plane-border-width 2) ; used for heuristic placement only  
  
;;; Moved from debug.lisp

;; Who decided this was how this needed to be implemented??????????  Why all
;; the complexity with lack of documentation?  Just to save a little space?
;; Couldn't an abstraction have been used?
;; Well here's some documentation anyway: -dkuznick, 10/19/04
;;; The following is used to implement a bit field for storing the various
;;; combinations of settings.  Each field could hold values from 0-15, though
;;; currently 0-4 is the highest  The message-filed-mask is 4 1's in binary,
;;; which is the size of mask necessary to ensure marking all values for the
;;; field with 1's. -dkuznick, 10/21/04

(defconstant warning-shift 0)
(defconstant tracing-shift 4)
(defconstant breakpoint-shift 8)
(defconstant source-stepping-shift 12)
(defconstant message-field-mask 15)


;;; Moved from definitions.lisp

(defconstant default-number-of-renderings-for-bulk-delete 10)
(defconstant default-maximum-renderings-for-class 200)

  

;;; Moved from tables.lisp

(defconstant max-subblock-count-with-pop-up-virtual-attributes-table 3)


;;; Moved from dialogs.lisp

(defconstant mb-ok               #x00)        ; Available message box styles. From winuser.h
(defconstant mb-okcancel         #x01)
(defconstant mb-abortretryignore #x02)
(defconstant mb-yesnocancel      #x03)
(defconstant mb-yesno            #x04)
(defconstant mb-retrycancel      #x05)
(defconstant mb-help           #x4000)        ; TODO: Sends async WM_HELP, needs to notify G2

(defconstant dlg-icon-question    0)        ; See get_icon_resource in twpro.c
(defconstant dlg-icon-information 1)
(defconstant dlg-icon-warning     2)
(defconstant dlg-icon-error       3)


(defconstant maximum-number-of-characters-in-pathname 512) ; maximum MAX_PATH (?)


(defconstant cd-add-children 1)
(defconstant cd-refresh 3)

(defconstant debugger-dialog-cancel 2)
(defconstant debugger-source-stepping-flag #x100) ; Flag bit in return value.

;;; `tw-initiated-update' and `g2-initiated-update' - to be kept in synch with
;;; values in ext/c/dyndlgs.h

(defconstant tw-initiated-update   1)
(defconstant g2-initiated-update   2)

(defconstant multi-update-begin    4)
(defconstant multi-update-continue 8)
(defconstant multi-update-finish  16)
(defconstant focus-changed-update 32)

(defconstant tw-multi-update-begin    5)
(defconstant tw-multi-update-continue 9)
(defconstant tw-multi-update-finish  17)

(defconstant g2-multi-update-begin     6)
(defconstant g2-multi-update-continue 10)
(defconstant g2-multi-update-finish   18)


;;; `miscellaneous' dialog message-types.  Also in synch with dyndlgs.h.

(defconstant g2-dialog-user-gesture 1)
(defconstant g2-send-wsv-address    8)

;; bitwise flags
(defconstant dialog-response-unspecified -1)
(defconstant dialog-response-no-action 0)
(defconstant dialog-response-close 1)
(defconstant dialog-response-apply 2)
(defconstant dialog-response-respond 4)
(defconstant dialog-response-send-all-data 8)
(defconstant dialog-response-dont-invoke-callback 16)

;; symbols to be used
(defconstant dialog-response-cancel 1)  ;; same as "close"
(defconstant dialog-response-ok 3)      ;; close & apply
(defconstant dialog-response-just-respond 4)

(defconstant dialog-response-respond-and-ok 7)  ;; respond & ok

(defconstant dialog-response-respond-all 12)  ;; send-all-data & respond
(defconstant dialog-response-respond-all-and-ok 15) ;; ibid & ok

(defconstant dialog-response-cancel-without-callback 17)  ;; close & no-callback

(defconstant dialog-response-client-side-problem 32)
;; dialog failed on client side for some reason

;;; `dialog-is-modal', `dialog-is-modeless' -- must be kept in synch with
;;; ext/c/dyndlgs.h

(defconstant dialog-is-modal 1)
(defconstant dialog-is-modeless 2)
(defconstant dialog-is-mdi-child 4)

(defconstant dock-code-top 1)		       ; Sync with twng/c/Twng.h
(defconstant dock-code-bottom 2)
(defconstant dock-code-left 3)
(defconstant dock-code-right 4)
(defconstant dock-code-float 5)
(defconstant dock-code-within 6)
(defconstant dock-code-mdi-child 7)
(defconstant dock-code-top-level 8)
(defconstant dock-code-embedded 9)

;;; `handle-for-unsuccessful-query'

(defconstant handle-for-unsuccessful-query -1)


;;; Moved from native-tw.lisp


(defconstant hh-display-envar-topic #x80) ; Special Gensym opcode, for pre-8.2 help.

;;;; Native Logbook

(defconstant logbook-message-type-error 1)
(defconstant logbook-message-type-warning 2)

;;; These defconstants must be kept in sync with the #defines in ext/c/msincls.h
(defconstant nms-stock-command-min-id 1001)
(defconstant nms-no-choice 1500)

;;; NMS handles, offset by nms-no-choice, are in the same integer space as Win32
;;; command IDs. The Codejock toolkit and MFC reserve some command IDs for
;;; built-in commands, namely
;;;  Codejock: 9300-9599, 35000-35002  (may change in future releases)
;;;  MFC:     57600-59647
;;; NMS handles are always less than 32000, so we only need to avoid 9300-9599,
;;; in ID space, or 7800-8099 in handle space.

(defconstant codejock-reserved-command-ids '(9300 . 9599))
(defconstant nms-handle-gap-low  (- (car codejock-reserved-command-ids) nms-no-choice))
(defconstant nms-handle-gap-high (- (cdr codejock-reserved-command-ids) nms-no-choice))

(defconstant nmsc-show 1)                ; Sync with twng/c/cjmenu.cpp
(defconstant nmsc-hide 2)
(defconstant nmsc-setcursel 3)
(defconstant nmsc-settext 4)
(defconstant nmsc-addtext 5)
(defconstant nmsc-deletetext 6)

(defconstant sb-hide 0)                        ; Opcodes
(defconstant sb-show 1)
(defconstant sb-text 2)
(defconstant sb-reset 3)
(defconstant sb-minheight 4)
(defconstant sb-update 5)
(defconstant sb-add-pane 6)
(defconstant sb-remove-pane 7)
(defconstant sb-pane-text 8)
(defconstant sb-pane-width 9)
(defconstant sb-pane-visible 10)
(defconstant sb-pane-foreground 11)
(defconstant sb-pane-background 12)
(defconstant sb-pane-icon 13)
(defconstant sb-pane-alignment 14)
(defconstant sb-pane-tooltip 15)
(defconstant sb-pane-enabled 16)
(defconstant sb-pane-borders 17)

(defconstant pane-destroy 2)                ; Generic pane operations
(defconstant pane-hide 3)                ; Keep in sync with twng/c/cjmenu.cpp
(defconstant pane-select 4)
(defconstant pane-float 5)
(defconstant pane-dock 6)
(defconstant pane-show 7)
(defconstant pane-set-title 8)
(defconstant pane-set-icon 9)
(defconstant pane-close 10)
(defconstant pane-redock 11)
(defconstant pane-toggle-docking 12)
(defconstant pane-fill 13)

(defconstant pane-set-closeable 101)
(defconstant pane-set-autohideable 102)
(defconstant pane-set-floatable 103)
(defconstant pane-set-draggable 104)
(defconstant pane-set-visible-caption 105)
(defconstant pane-set-close-action 106)

;; Opcodes
(defconstant tree-view-destroy 6)         ; Sync with twng/c/TreeView.h
(defconstant tree-view-insert-item 10)
(defconstant tree-view-clear 11)
(defconstant tree-view-set-indent 12)
(defconstant tree-view-set-item-height 13)
(defconstant tree-view-set-bgcolor 14)
(defconstant tree-view-set-text-color 15)
(defconstant tree-view-set-insert-mark-color 16)
(defconstant tree-view-select-item-by-name 17)
(defconstant tree-view-ensure-visible 18)
(defconstant tree-view-scroll-to 19)
(defconstant tree-view-set-insert-mark 20)
(defconstant tree-view-edit-item 21)
(defconstant tree-view-expand-item 22)
(defconstant tree-view-collapse-item 23)
(defconstant tree-view-select-item 24)
(defconstant tree-view-set-item-tooltip 25)
(defconstant tree-view-set-item-bold 26)
(defconstant tree-view-set-item-label 27)
(defconstant tree-view-set-item-icons 28)
(defconstant tree-view-set-item-check 29) ; Unused/broken
(defconstant tree-view-delete-item 30)
(defconstant tree-view-toggle-item 31)
(defconstant tree-view-set-right-click-selects-node 32)
(defconstant tree-view-expand-all 33)
(defconstant tree-view-collapse-all 34)
(defconstant tree-view-redraw 35)

;; Flags
(defconstant tvf-children 1)
(defconstant tvf-bold 2)
(defconstant tvf-expand 4)
(defconstant tvf-check 8)
(defconstant tvf-first 16)                ; Use for insert-node position.
(defconstant tvf-after 32)
(defconstant tvf-insert-mark 64)
(defconstant tvf-reclaim-label 128)        ; Used only by G2

(defconstant html-view-destroy 2)
(defconstant html-view-back 3)
(defconstant html-view-forward 4)
(defconstant html-view-home 5)
(defconstant html-view-stop 6)
(defconstant html-view-refresh 7)
(defconstant html-view-goto 8)
(defconstant html-view-print 9)

;;;; Shortcut Bars

(defconstant shortcut-bar-style-outlook 1)      ; Aka "Outlook Bar"
(defconstant shortcut-bar-style-outlook-2003 2)        ; Aka "List Bar"

;; Opcodes. Keep in sync with twng/c/ShortcutBar.h
(defconstant shortcut-bar-destroy 6)
(defconstant shortcut-bar-add-folder 10)
(defconstant shortcut-bar-add-item 11)
(defconstant shortcut-bar-clear 12)

(defconstant shortcut-bar-select-folder 13)
(defconstant shortcut-bar-enable-folder 14)
(defconstant shortcut-bar-disable-folder 15) ; disables each item in folder

(defconstant shortcut-bar-select-item 16)
(defconstant shortcut-bar-enable-item 17)
(defconstant shortcut-bar-disable-item 18)

(defconstant shortcut-bar-small-icons 19)
(defconstant shortcut-bar-large-icons 20)
(defconstant shortcut-bar-background-color 21)
(defconstant shortcut-bar-foreground-color 22)

;; From /bt/fmw3/xtp/include/Controls/Common.Include/XTDefines.h
(defconstant obs-xt-smallicon #x0001)
(defconstant obs-xt-largeicon #x0002)
(defconstant obs-xt-editgroups #x0004)
(defconstant obs-xt-edititems #x0008)
(defconstant obs-xt-removegroups #x0010)
(defconstant obs-xt-removeitems #x0020)
(defconstant obs-xt-addgroups #x0040)
(defconstant obs-xt-dragitems #x0080)
(defconstant obs-xt-animation #x0100)
(defconstant obs-xt-selhighlight #x0200)
(defconstant obs-default-style (logior obs-xt-selhighlight obs-xt-animation obs-xt-largeicon))

(defconstant dlgm-settext 1)                ; Methods for using initialization data
(defconstant dlgm-addstrings 2)
(defconstant dlgm-seticon 3)
(defconstant dlgm-check 4)
(defconstant dlgm-sndmsg 5)

(defconstant chart-create 1)                ; Opcodes
(defconstant chart-destroy 2)
(defconstant chart-print 3)
(defconstant chart-update 4)
(defconstant chart-partial-update 5)
(defconstant chart-copy 6)
(defconstant chart-export 7)

(defconstant chart-format-jpeg 1)        ; Export formats
(defconstant chart-format-png 2)
(defconstant chart-format-bmp 3)
(defconstant chart-format-wmf 4)
(defconstant chart-format-svg 5)

(defconstant chart-success 0)                ; Return codes
(defconstant chart-no-window 1)

(defconstant lvcfmt-left #x0000)
(defconstant lvcfmt-right #x0001)
(defconstant lvcfmt-center #x0002)

(defconstant lvscw-autosize -1)
(defconstant lvscw-autosize-useheader -2)


;;; Moved from workstation.lisp

;;; The defconstant `event-time-mask' defines the wrapping size of event
;;; timestamps.  It must agree with the definition in ext/c/graphics.h.

(defconstant event-time-mask #xFFFFFFF)

(defconstant least-common-multiple-of-stock-line-pattern-lengths (* 3 4 5 7)) ;lookup-stock-line-pattern-element

(defconstant minimum-minimum-fixnum-scheduling-interval 2)
(defconstant minimum-minimum-float-scheduling-interval 0.002)

;; These constants were previously inline in the code of
;; adjust-scheduling-interval (i.e., not defined as named defconstants). For G2
;; 8.1, this is now 2 milliseconds (0.002 seconds), scaled by 1/25 from 50
;; milliseconds (0.050 seconds), the constant used by at least G2 4.0 (mid
;; 1990's). (MHD 1/10/05)

;; Note that these minimum-... constants cannot be 0.001 or less without
;; adjusting the rounding logic, and the logic to avoid divide-by-zero errors,
;; in the function adjust-scheduling-interval, as described in JRA's 12/11/94
;; comment above. (MHD 1/11/05)


;;; Moved from kfep3.lisp

;;;; KFEP Trace Facilities

(defconstant TMASK_KKA_P_BATKANAKAN        (ash 1 0))
(defconstant TMASK_KKA_HENSAISYO        (ash 1 1))
(defconstant TMASK_KKA_GTANGO                (ash 1 2))
(defconstant TMASK_KKA_GHYOKI                (ash 1 3))
(defconstant TMASK_KKA_GTNUM                (ash 1 4))
(defconstant TMASK_KKA_EVALBUN                (ash 1 5))
(defconstant TMASK_KKA_FIND_BUNPO        (ash 1 6))
(defconstant TMASK_CHKBUNPO                (ash 1 7))
(defconstant TMASK_CHKATTR                (ash 1 8))
(defconstant TMASK_KKA_G_TAIGEN                (ash 1 9))
(defconstant TMASK_KKA_KOFIND                (ash 1 10))
(defconstant TMASK_KKA_ISHOUKI                (ash 1 11))

(defconstant jis-space-character-code #x2121)

(defconstant jis-colon-character-code #x2127)

(defconstant jis-0-digit-character-code #x2330)        ; same as JIS
(defconstant jis-letter-A-character-code #x2341)        ; same as JIS
(defconstant jis-m-dash-character-code #x232d)


;;; Moved from hfep1.lisp

(defconstant hfep-ks-size 2390)			; length of the mapping array


;;; Moved from hfep2.lisp

;;;; Status Flags

;;; Here we are transforming the status flag macros (#defines) in hctbl.h.
;;; They look like, e.g.,
;;;
;;;    #define NONE 0
;;;
;;;
;;; These would seem to transform well into constants.  Still, the names
;;; are way too short to stick our symbol namespace, so we'll tack on the
;;; usual "HFEP-" prefix.

(defconstant hfep-none 0)
(defconstant hfep-go-on 1)
(defconstant hfep-done 2)
(defconstant hfep-wrong 3)
(defconstant hfep-error 4)

;;; We introduce on our own the new constant hfep-null-code to take the place of
;;; hfep-null where a character code is needed, as opposed to a character.

(defconstant hfep-null-code 0)


;;; Moved from edit2.lisp

(defconstant date-month-and-year-of-frame-edit-base-time
  '(1 9 1993))

(defconstant frame-edit-base-timestamp 0) ; a frame edit timestamp

(defconstant additional-time-for-synthetic-paste-event-timestamps 13)


;;; Moved from kb-save4.lisp

;;; The virtual-attribute `default-window-position-and-scale' ....  The
;;; following G2 Window system limits are currently only used for checking the
;;; validity of arguments passed to this virtual attribute's setter.  The
;;; following three functions are just subfunctions of this virtual attribute's
;;; setter, used for checking.

(defconstant most-positive-window-coordinate #.(- (expt 2 16) 1))
(defconstant most-negative-window-coordinate #.(-  (- (expt 2 16) 1)))

;;; Moved from font-files.lisp

#+font-files
(defconstant max-small-font-file-fixnum-integer-length 6)
  
;;; Moved from telewindows.lisp

;;; The constant default-telewindows-upper-margin gives the distance from the
;;; top edge of the telewindows window to the baseline of the first line of
;;; text when drawing a new list of text lines using write-list-of-text-lines-
;;; to-gensym-window.

(defconstant default-telewindows-upper-margin 50)

;;; Moved from sets.lisp

(defconstant default-error-source-line -1)
(defconstant default-error-source-column -1)


;;; Moved from arrays.lisp

;;; The constant `g2-array-length-maximum' limits the maximum size of g2-array.
;;; Currently, this is 1/2 the limit of a managed-array, 1 Meg - 2 K, which is
;;; 511 K.  It is 1/2 of the managed-array limit because item-array and g2-array
;;; use two managed-array slots per element.

(defconstant g2-array-length-maximum (- (expt 2 19) (expt 2 10)))


;;; Moved from hash-tables.lisp

;(defconstant stand-in-marker (gensym-cons 'user-hash-table-stand-in nil))

;;; Moved from histories.lisp

;;; The constant `history-timestamp-epsilon' is used in computing history times,
;;; adjusted for to the history granularity, to prevent rounding error.  This
;;; number is equivalent to 900 nanoseconds.

(defconstant history-timestamp-epsilon 9.0e-7)


;;; Moved from rpc-common2.lisp

(defconstant no-history-spec-value -1)

(defconstant no-resumable-object-index -1)


;;; Moved from proc-utils.lisp

;;; The constant `default-procedure-evaluation-priority' contains the priority
;;; that should be given to procedures when first created.

(defconstant default-procedure-evaluation-priority 6)

(defconstant procedure-can-invalidate-environment-mask 1)

(defconstant procedure-contains-wait-state-mask 2)

(defconstant procedure-contains-indirect-procedure-call-mask 4)

(defconstant procedure-call-without-validated-environment-mask 8)

(defconstant procedure-invalidates-environment-union-mask #.(+ 1 2 4 8))

;;; The constant `maximum-length-for-writing-evaluation-values' defines the
;;; maximum number of characters written when displaying a long text string to
;;; the user.  Currently, this limit is used when writing procedure stack and
;;; local variable environments.  A related constant is maximum-length-for-
;;; user-text-strings which limits the total length of user text strings.

(defconstant maximum-length-for-writing-evaluation-values 300)


;;; Moved from proc-comp.lisp

;;; The variables `maximum-number-of-lisp-call-arguments' and
;;; `maximum-number-of-lisp-call-return-values' limit the number of arguments
;;; passed to and return values from a lisp function called from a
;;; system-procedure using "system call" (previously called "lisp call").  These
;;; constants are used in the predicates lisp-call-argument-count-ok-p and
;;; lisp-call-return-count-ok-p.

;;; Note that when modifying these constants, update the lisp-call and
;;; lisp-call-assignment procedure and/or stack instructions to correctly pass
;;; the arguments and handle the return values.

(defconstant maximum-number-of-lisp-call-arguments 8)

(defconstant maximum-number-of-lisp-call-return-values 8)


;;; Moved from change-log.lisp

;;;; External Diffs
  
;;; `initial-change-log-revision-number' - in theory, could start at 1, like CVS
;;; does.  Hell, it might even be more G2-like to do so.  But computers start at
;;; zero.  Let it be so.

(defconstant initial-change-log-revision-number 0)

;;; Moved from graph-util.lisp

;;; not used in this file. Do not need eval-when for allegro portability
;;; NOTE: This number is converted to float and back, so reducing by
;;; one from the real limit to ensure that we never convert above
;;; most-positive-fixnum.

;(defconstant max-timespan
;  (fixnum-to-time (- most-positive-fixnum 1)))	
	
;;; Moved from graphs.lisp	
	
(defconstant maximum-painting-action-args 10)
(defconstant buffered-plot-painting-minimum-ratio 5)

  
;;; Moved from simulate1.lisp

;; Needed by coerce to gensym float.
(defconstant fraction-modulus-of-compound-fixnum-simulation-time 100000)

;; The modulus of 100000 means that the fraction is stored as an integer with 5
;; decimal digits of precision.  This should provide for sufficient
;; granularity (up to tens of micro-seconds) for all our applications.
;; It should be possible to get more precision than 5 decimal digits
;; by using the negative portions of fixnums as well, assuming fixnums
;; are at least 24 bits.


;;; Moved from sax.lisp

;;;; Callback Constants

;;; These constants must be kept in sync with the values in xml/c/xml_support.h,
;;; which are, as of 1/12/03, at least:
;;;   #define XML_CALLBACK_NONE            -1
;;;   #define XML_CALLBACK_START_DOCUMENT  12
;;;   #define XML_CALLBACK_END_DOCUMENT    13
;;;   #define XML_CALLBACK_START_ELEMENT   14
;;;   #define XML_CALLBACK_END_ELEMENT     15
;;;   #define XML_CALLBACK_CHARACTERS      17
;;;   #define XML_CALLBACK_COMMENT         20
;;;   #define XML_CALLBACK_WARNING         21
;;;   #define XML_CALLBACK_ERROR           22
;;;   #define XML_CALLBACK_FATAL_ERROR     23

(defconstant xml-callback-none            -1)
(defconstant xml-callback-start-document  12)
(defconstant xml-callback-end-document    13)
(defconstant xml-callback-start-element   14)
(defconstant xml-callback-end-element     15)
(defconstant xml-callback-characters      17)
(defconstant xml-callback-comment         20)
(defconstant xml-callback-warning         21)
(defconstant xml-callback-error           22)
(defconstant xml-callback-fatal-error     23)

(defconstant xml-encoding-length 4)	;only used in function below


;;; Moved from dom.lisp

;;; Node Types

(defconstant xml-element-node 1)
(defconstant xml-attribute-node 2)
(defconstant xml-text-node 3)
(defconstant xml-cdata-section-node 4)
(defconstant xml-entity-reference-node 5)
(defconstant xml-entity-node 6)
(defconstant xml-processing-instruction-node 7)
(defconstant xml-comment-node 8)
(defconstant xml-document-node 9)
(defconstant xml-document-type-node 10)
(defconstant xml-document-fragment-node 11)
(defconstant xml-notation-node 12)

;;; Maximum length of strings retrieved from the C code

(defconstant maximum-length-for-dom-strings maximum-length-for-user-text-strings)

;;; Moved from conclude.lisp

(defconstant slot-description-cache-entry-size 4)
(defconstant attribute-value-cache-entry-size 3)  
  
(defconstant denotation-element-overhead-slot-count 2)
(defconstant maximum-denotation-types 50)  
  
(defconstant maximum-denotation-sequence-elements 50)  
  
  ;; hax for now
(defconstant attribute-particular-code 1)
(defconstant aliased-attribute-particular-code 2)
(defconstant element-particular-code 3)
(defconstant virtual-attribute-particular-code 4)
(defconstant variable-value-particular-code 5)

						   
;;; Moved from grammar0.lisp
	
;;; The constant `ten-years' specifies the number of seconds there are in
;;; approximately ten years.  This is precisely the number of seconds in 3650
;;; 24-hour periods, or 3650 days.  We use to limit the size of constant
;;; intervals that can be typed in so that users don't casually overflow fixnums
;;; while playing with these values.  Those who actaully need intervals that
;;; long must enter them without the interval grammar.

(defconstant ten-years #.(* 10 365 24 60 60))
	
;;; Moved from grammar6a.lisp

;; Maximum length of an individual dash/dot element.
;; A limitation of X: dash lengths are stored in a signed char.
(defconstant maximum-connection-dash-length 127)

;; Maximum number of elements in the dash/dot pattern.  Keep in sync
;; with MAX_DASH_COUNT in graphics.c
(defconstant maximum-connection-dash-count 256)
	
(defconstant attribute-nesting-limit 20)	; consider making this a parameter	

	
;;; Moved from grammar6c.lisp	
	
;;; The constant `max-icon-size' determines the maximum width and height for an
;;; icon.  This is checked by the compiler for icon-description? and by the setter
;;; for the icon-variables virtual attribute (in CONTROLS).

;;; NOTE: this is being increased from 1000 to 5000 today to implement
;;; suggestion HQ-3805225; it had been (in effect) 1000 from the first release
;;; of G2 until 6.0; however, during 5.0, checking was not done on power icon
;;; variables, allowing users, at run time, to make icons any width they
;;; desired.

;;; Increased from 5000 to 100000 today for suggestion HQ-4101049.

(defconstant max-icon-size 100000)	;    100,000
(defconstant max-icon-area 2500000)	; 2,500,000	
	
;;; Moved from 	grammar7.lisp

(defconstant float-format-precision-limit 40)

	
;;; Moved from queries.lisp

;;; Frame-Display constants

(defconstant frame-display-workspace-margin 30)
(defconstant frame-display-vertical-spacing 10)
(defconstant frame-display-reformat-after-count-deleted 3)


;;; Moved from g2-foreign.lisp



;; The following four defconstants must match gsi_icp.h.

(defconstant foreign-function-integer-type-tag 1) ;INTEGER_TAG
(defconstant foreign-function-real-type-tag    6) ;FLOAT64_TAG
(defconstant foreign-function-symbol-type-tag  3) ;SYMBOL_TAG
(defconstant foreign-function-text-type-tag    4) ;STRING_TAG

  ;; Franz ACL compile complained constants were being redefined when this progn
  ;; was (eval-when (:compile-toplevel :load-toplevel :execute) ...).  It looks like it needn't be,
  ;; which is why I've changed it to a progn. -mhd, 6/17/00
  
(defconstant largest-known-fixnum-time-units-per-second 1000)

(defconstant shutdown-context-only-flag-clear 0)
(defconstant shutdown-context-only-flag-set   1)

;; The following five defconstants must agree with foreign.c, the
;; foreign function calling machinery on the C side, currently (2/6/92)
;; in /disc/ab/ext/c/work/foreign.c

(defconstant FFS_UNSPECIFIED_ERROR         1)
(defconstant FFS_CONNECTION_OPEN_ALREADY   2)
(defconstant FFS_SIGNAL_CAUGHT_DURING_CALL 3)
(defconstant FFS_UNKNOWN_FUNCTION          4)
(defconstant FFS_UNKNOWN_RETURN_TYPE       5)


;;; Moved from gfi.lisp	
	


;;; The constant `maximum-gfi-output-queue-count' is the largest number of
;;; entries allowed in the GFI output line before it may be forcibly flushed by
;;; the enqueue operation.  (This now applies only to EVENT LOG output.  See my
;;; note below.  - cpm, 5/2/95)

;;; This limit is used to ensure that the output queue will not grow without
;;; bound when the system is heavily overloaded.  This constant is used in
;;; handle-gfi-output-interface-new-values.  Note that this maximum size should
;;; be held fairly low, since on deactivate of a GFI output object, the entire
;;; queue must be flushed without interrupts.  The larger the maximum size, the
;;; longer this delay.

;; Note that I modified how this constant is being used when writing to a
;; spreadsheet file.  A customer had reached the 100 value limit when writing to
;; a spreadsheet file and when GFI was not overloaded!  See the function
;; handle-gfi-output-interface-new-values for information on how the spreadsheet
;; case is now handled.  In this case, it no longer uses this maximum queue
;; limit, but has another means of limiting the queue.  - cpm, 5/2/95

(defconstant maximum-gfi-output-queue-count 100)
	
	
;;; Moved from g2-gsi.lisp

(defconstant iterations-for-gsi-temporary-float-processing 100)


;;; Moved from g2ds.lisp

;;;; [4.2] ICP Data Types for G2-to-G2 Dataservice

(defconstant g2ds-null-type-tag        0)
(defconstant g2ds-integer-type-tag     1)
(defconstant g2ds-float-type-tag       2)
(defconstant g2ds-symbol-type-tag      3)
(defconstant g2ds-string-type-tag      4)
(defconstant g2ds-list-type-tag        5)
(defconstant g2ds-64bit-float-type-tag 6) ;added.  (jh, 5/1/90)
(defconstant g2ds-dotted-list-type-tag 7) ; -jra & jh 7/6/90
(defconstant g2ds-evaluation-sequence-type-tag  8)
(defconstant g2ds-evaluation-structure-type-tag 9)
(defconstant g2ds-logical-type-tag    10) ; used inside sequences and structures

(defconstant g2ds-no-error             0)

(defconstant default-g2ds-interface-countdown-timer-limit 10) ;10 seconds

(defconstant g2ds-server-max-count-in-return-queue 20)

;; These are bound into code at compile time by sharp-dot in the definition of
;; the class method expression-cell-update, in a case expression, so they need
;; to be inside an eval-when form.  Force evaluation everywhen, to be safe.

(defconstant g2ds-read-expression-cell-index 0)
(defconstant g2ds-write-expression-cell-index 1)

(defconstant iterations-for-g2ds-temporary-float-processing 100)


;;; Moved from g2ds-nupec.lisp

(defconstant nupec-synchronize-datum-null-type 0)
(defconstant nupec-synchronize-datum-symbol-type 1)
(defconstant nupec-synchronize-datum-integer-type 2)
(defconstant nupec-synchronize-datum-float-type 3)
(defconstant nupec-synchronize-datum-text-type 4)

(defconstant nupec-designation-null-type-tag 0)
(defconstant nupec-designation-symbol-type-tag 1)
(defconstant nupec-designation-cons-type-tag 2)

;;; Moved from views.lisp

(defconstant status-bar-maximum-pane-count 250)

(defconstant logbook-destroy 2)
(defconstant logbook-append-message 10)
(defconstant logbook-delete-message 11)
(defconstant logbook-normal-message 12)
(defconstant logbook-fade-message 13)
(defconstant logbook-highlight-message 14)
(defconstant logbook-set-line-wrap 15)
(defconstant logbook-set-include-date-in-title 16)

;;; Moved from commands2.lisp  

(defconstant small-native-icon-size 16)
(defconstant large-native-icon-size 32)  
  
(defconstant ld-request-full-listing 0)
(defconstant ld-request-children 1)
(defconstant ld-request-refresh 2)

;;;; HTML Help

(defconstant hh-display-topic #x00)          ; Sync with Windows HtmlHelp.h
(defconstant hh-display-toc #x01)
(defconstant hh-display-index #x02)
(defconstant hh-display-search #x03)
(defconstant hh-sync #x09)
(defconstant hh-keyword-lookup #x0D)
(defconstant hh-display-text-popup #x0E)
(defconstant hh-help-context #x0F)
(defconstant hh-close-all #x12)
(defconstant hh-alink-lookup #x13)  

;;;; Tabbed MDI Mode

(defconstant mdi-normal-mode 1)                 ; Sync with twng/c/MainFrm.cpp
(defconstant mdi-tabbed-mode 2)                 ; Not supported.
(defconstant mdi-grouped-mode 3)
(defconstant mdi-show-icons 4)
(defconstant mdi-tab-position 5)
(defconstant mdi-tab-layout 6)


;;; Moved from rg-report.lisp

(defconstant number-of-gsi-subtests 7)
(defconstant number-of-protocols 1)  ;; TCP/IP

(defconstant tcpip-protocol 0)

;;; Moved from gthread.lisp

;;; `Call-site-minimum-size' is internal to this section, it is the amount of
;;; space we reserve in every call site for the linkage betwix the frames.

(defconstant call-site-minimum-size 5)

;; Currently this could be reduced to 3.

(defconstant Errno-WOULD-BLOCK 35)
(defconstant Errno-AGAIN 11)


;;; Moved from web.lisp

(defconstant ENETRESET	52) ;; Network dropped connection on reset
(defconstant ECONNABORTED 53) ;;  Software caused connection abort


;;; Moved from java1.lisp

(defconstant java-access-flag-public       #x0001) ; C F M
(defconstant java-access-flag-private      #x0002) ;   F M
(defconstant java-access-flag-protected    #x0004) ;   F M
(defconstant java-access-flag-static       #x0008) ;   F M
(defconstant java-access-flag-final        #x0010) ; C F M
(defconstant java-access-flag-super        #x0020) ; C
(defconstant java-access-flag-synchronized #x0020) ;     M
(defconstant java-access-flag-volatile     #x0040) ;   F
(defconstant java-access-flag-transient    #x0080) ;   F
(defconstant java-access-flag-native       #x0100)
(defconstant java-access-flag-interface    #x0200) ; C
(defconstant java-access-flag-abstract     #x0400) ; C

(defconstant java-constant-class 7)
(defconstant java-constant-fieldref 9)
(defconstant java-constant-methodref 10)
(defconstant java-constant-interfacemethodref 11)
(defconstant java-constant-string 8)
(defconstant java-constant-integer 3)
(defconstant java-constant-float 4)
(defconstant java-constant-long 5)
(defconstant java-constant-double 6)
(defconstant java-constant-nameandtype 12)
(defconstant java-constant-utf8 1)
(defconstant java-constant-unicode 2)
