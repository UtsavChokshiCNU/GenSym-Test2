;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module WINDOWS1 -- Fundamentals of the Gensym Window System

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson, Brian Matthews, Mark David, Andreas Hofmann,
;;; Ong, Peng Tsin, and Ben Hyde






;;;; Forward References From WINDOWS1


(declare-forward-reference twng-window-p function) ; WINDOWS4

(declare-forward-reference reclaim-panes-in-window-if-g2 function)       ; PANES
(declare-forward-reference clear-stored-raster function) 		 ; WINDOWS2
(declare-forward-reference reclaim-default-pane-background-color-or-tiling-pattern function)
(declare-forward-reference transfer-region-to-smaller-raster function)	 ; WINDOWS2
(declare-forward-reference make-or-revise-window function)		 ; WINDOWS3
(declare-forward-reference send-icp-begin-window-update function)	 ; WINDOWS3
(declare-forward-reference send-icp-set-transfer-mode function)    	 ; WINDOWS4
(declare-forward-reference send-icp-set-window-protocol-version function)
(declare-forward-reference negotiate-telewindows-licensing function)
(declare-forward-reference send-icp-set-window-license-level function)
(declare-forward-reference send-icp-set-telewindows-connection-license-info
			   function)
(declare-forward-reference send-icp-set-background-color-value function telestubs)
(declare-forward-reference reclaim-cached-structures-for-window function); WINDOWS3
(declare-forward-reference initialize-image-palette-of-new-gensym-window function)   ; workstations or tw-patches
(declare-forward-reference get-g2-license-level function)   ; filters or tw-patches
(declare-forward-reference sync-graphics-on-native-window-maybe-with-tracing function)
(declare-forward-reference global-paint-mode-p function)    ; workstation or tw-patches
(declare-forward-reference reclaim-contents-of-native-menu-table function) ; new-menus or tw-patches
(declare-forward-reference reclaim-contents-of-nms-menu-table function) ; telestubs
(declare-forward-reference reclaim-offscreen-pixmap function)		 ; WINDOWS3
(declare-forward-reference reclaim-native-icons-table function)          ; commands2 or tw-patches
(declare-forward-reference reclaim-frame-serial-number function) ; UTILITIES4
(declare-forward-reference clear-all-image-renderings-for-window function) ; IMAGES
(declare-forward-reference reclaim-native-windows function)    	 ; WINDOWS4
(declare-forward-reference reclaim-all-scaled-fonts function)    ; FONTS

(defvar defer-notifications? nil) ; Moved here from DEBUG


;;;; Primitive Operations and Constants



;;; `Icon-Overflow' is a macro returning 1 workspace unit.  This is the
;;; amount that the icon rendering extends beyond the block's bounds.
;;; When computing the extent of a block that is being rendered via an
;;; icon this must be added to the right and bottom of the icon.

;;  - ben 6/26/93

(defmacro icon-overflow () `1)

;; Fact is, that since we don't scale lines right, this causes the
;; extreme edges to be too larger than necessary when mapped into
;; image-plane bounds at greater than full scale.



;;; `bleeding-overflow' is a macro returning the bleeding size in raster units.
;;; This is the amount that a drawing routine may exceed it's extreme edges
;;; when drawing at less then full scale.  This arises in the scenario where two
;;; different workspace coordinates map to the same raster coordinate,
;;; meanwhile the drawing code decides to render one pixel anyway.  When this
;;; happens on the right or bottom of the block extreme edges then the one
;;; pixel may `bleed' outside bounds implied by mapping the extreme edges of
;;; the block into the image-plane.

;;; The bleeding overflow is a problem when attempting to compute if two
;;; objects overlap when drawing.  If the object is currently appearing
;;; at an extremely small scale the `bleeding extreme edges' implied by
;;; mapping the extreme edges into the image-plane, adding the bleeding,
;;; and then mapping back into the workspace can become much larger
;;; than the vanilla extreme edges.

;;  - ben 6/26/93



(defmacro bleeding-overflow () '1)





;;;; Gensym Processes and Foreign and Domestic Things



;;; [WARNING: Much of what appears in this section is not true,
;;; not yet true, or in the middle of being completely designed/implemented.
;;; -MHD, 2/6/91]



;; Consider moving this section.  It refers ahead to gensym windows.





;;; In general, a `foreign' thing is a thing managed by (belonging to) a
;;; foreign gensym process, whereas a `domestic' thing is a thing managed by
;;; the current gensym process.  Thus, there are, in addition to foreign and
;;; domestic processes, foreign and domestic (gensym) windows, panes, image
;;; planes, workspaces, etc.



;;; A `workstation' has a gensym window that provides both user input and
;;; graphic output capability, though there can be gensym windows that do not
;;; correspond to workstations (because they provide no input).  User input
;;; consists of keyboard and `mouse' (pointing device) events.  Graphic output
;;; ...

;;; A `native window' is a Common Lisp supported window that implements a
;;; domestic (gensym) window.  A particular Common Lisp may have more than one
;;; type of native window.

;;; The type of a window may be ICP (for a foreign window), X11, LISPM, LUCID,
;;; NULL (for temporary use where window functionality has not yet been
;;; fully implemented), etc.  Note that the type of a domestic window is the
;;; type of its native window.  

;;; Editors note: we only have x11, icp and printer windows as of version 4.





;;;; Gensym Windows



;;; Graphics Conses

(defconser graphics WINDOWS1)

;; For tiling pattern rows, stacks of image planes, panes-in-window, operation-
;; specific-arg-for-graphic-element, listed graphic elements, deferred
;; updates (a capability of questionable utility), etc., in modules WINDOWS,
;; PANES, and DRAW.


;;; `g2-has-v5-mode-windows-p' should be true if g2 has taken
;;; any connections from telewindows running in version 5 mode.

(def-system-variable g2-has-v5-mode-windows-p windows1 (:funcall initialize-v5-mode))

(defun initialize-v5-mode ()
  (set-v5-mode-state
    (v5-mode-option-specified-p)))
   
(defun-simple v5-mode-option-specified-p ()
  (if (get-command-line-flag-argument #w"v5mode")
      t
      nil))

(defun set-v5-mode-state (state)
  (setf g2-has-v5-mode-windows-p state))



(defvar trace-image-planes-p nil)

;;; `bitmap-memory-used' takes the dimensions in bits (as
;;; given to the operating system) and computes the memory
;;; usage in bytes. The bitmap takes up more spaces than
;;; just the sum of all its pixels: so a constant is
;;; added. Assumption: 8 pixels in a byte.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun bitmap-memory-used (width height depth)
  (+ 16						        ;; arbitrary overhead for each bitmap
     (ceilingf-positive (* width depth height) 8)))     ;; convert bits to bytes

;; icons are always square and of depth 1

(defun icon-bitmap-memory-used (size)
  (bitmap-memory-used size size 1))

(defun convert-raster-sizes-to-memory-used (raster-sizes)
  (mapcar #'icon-bitmap-memory-used raster-sizes))
)

;;; The constant `list-of-regular-raster-sizes' is a list
;;; of widths or heights, in pixels (bits),
;;; in ascending order, that are available in the pools of raster.  All rasters
;;; with widths or heights greater than the biggest number in
;;; list-of-regular-raster-sizes and rasters of sizes not equal to one of the
;;; specified regular sizes (created with the make-exact-size-p option) form
;;; another pool. This constant is only available when macros are present.

;SS_ERROR
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter list-of-regular-raster-sizes '(4 8 12 16 24 32 56 64 104 128 152 200 256 400))
(defparameter list-of-regular-raster-memory-usage (convert-raster-sizes-to-memory-used
						   list-of-regular-raster-sizes))
(defparameter number-of-regular-raster-sizes (length list-of-regular-raster-sizes))
(defparameter largest-regular-raster-size (car (last list-of-regular-raster-sizes)))
(defparameter largest-regular-raster-size-index (-f (length list-of-regular-raster-sizes) 1))
(defparameter deepest-depth 32)
(defparameter minimum-tile-size-for-icons 32)
(defparameter minimum-index-for-icons (position minimum-tile-size-for-icons
					       list-of-regular-raster-sizes)))


;; I modified this list to make all large sizes be a multiple of 8 bits. -fmw
;; NOTE:  the above list can't have more than 16 elements without changing
;; the small-2d-array facility.  -pto 19jun89



;;; `default-maximum-icon-bitmaps' and
;;; `default-maximum-icon-bitmap-memory' limit the size of
;;; the icon rendering cache and thus the number of bitmaps
;;; G2/TW use for icon rendering. Created to handle hard
;;; limits on Microsoft platforms:
;;; NT 4.0: max of 12,288 bitmaps handles per process (16,000 per machine).
;;;         Reasonable limit: 4000.
;;; Win95: limit of 8192 "selectors" per machine, which are
;;; used for many things beside bitmaps.
;;;         Reasonable limit: 1000 (? needs testing)
;;; Unix: limit can be much higher.

(def-system-variable default-maximum-icon-bitmaps WINDOWS1 1000)
(def-system-variable default-maximum-icon-bitmap-memory WINDOWS1 2000000) ; arbitrary (big)



;;; The constant `default-image-palette' is used here and in the
;;; drawing-parameters system table.  It must be a symbol, and is not
;;; allowed to be the (custom-colors <image-name>) form.  It is used
;;; ONLY for the initial system-window and the value in drawing
;;; parameters for a clear kb.  New windows have their image-palette
;;; set explicitly by an ICP function.

(defparameter default-image-palette 'standard-colors)


;;; The function `default-value-for-image-palette' works around
;;; the fact that we sometimes lose symbol-values in Chestnut.

(defun default-value-for-image-palette ()
  default-image-palette)


;;; An AB system may make use of any number of rectangular `gensym windows'
;;; located on any number of distinct `graphic devices', typically screens and
;;; printers.  A window is divided up into any number of non-overlapping,
;;; rectangular `panes'.  If a window has a raster, the window's coordinate
;;; system must be the same as the raster's coordinate system.

;;; In any given implementation, several distinct types of gensym windows may
;;; be supported.  A gensym window may simultaneously be a window (or portion
;;; thereof) in some other window system.  For example, it might be the
;;; interior of a Microsoft or X Windows window.

;;; Raster-for-native-window?, for a native window, is the actual raster
;;; memory, if any, for the window.  Note that a gensym window's coordinate
;;; system need not be the same as the coordinate system of the native window's
;;; raster.

;;; Color-map-for-window should be a color map.  Color maps are discussed below.



;;; `Copy-gensym-window-parameters-plist' and
;;; `reclaim-gensym-window-parameters-plist' are the copy and reclaimer
;;; functions, respectively, for a gensym window's window parameter plist.

(defun copy-gensym-window-parameters-plist (plist)
  (copy-gensym-tree-with-text-strings plist))

(defun reclaim-gensym-window-parameters-plist (plist)
  (reclaim-gensym-tree-with-text-strings plist))





(def-structure (gensym-window
		 (:reclaimer reclaim-gensym-window-internal)
		 (:constructor make-gensym-window-internal (native-window?))
		 #+development
		 (:print-function print-gensym-window))


  (type-of-gensym-window 'native)		; X11, ICP, PRINTER, and formerly, NATIVE.

  ;; Linkages in the Display Hierarchy
  workstation-this-is-on
  (panes-in-window				; nil only transiently
    nil :reclaimer reclaim-panes-in-window-if-g2)
  (panes-available-for-reuse-in-window
    nil :reclaimer reclaim-panes-in-window-if-g2)


  ;; Relationship to native parent window system: new in 7.1
  ;; BUG: These are not kept up-to-date for local windows!
  (window-x-in-parent 0)
  (window-y-in-parent 0)

  ;; Graphic 
  left-edge-of-window				; 0 if the window has a raster
  top-edge-of-window				; 0 if the window has a raster
  right-edge-of-window
  bottom-edge-of-window

  ;; ICP relationships.
  (icp-window-protocol-version original-icp-window-protocol-version)
  (icp-output-port-for-window? nil)		; for windows of type ICP, ...
  (icp-output-port-to-master-for-window? nil)	; for non-ICP (with corresponding
						;   ICP windows on the master side)
  (corresponding-icp-object-map-for-window nil)
  (icp-object-index-for-window-on-other-side? nil)


  ;; Misc. Slots
  #+unused (gensym-window-is-not-mine? nil)
  (telewindows-license-level-of-gensym-window 3) ; -2..3 = corresponds to
					;   unknown/unauthorized, FLOATING,
					;   EMBEDDED, RUNTIME, RESTRICTED-USE,
					;   DEVELOPMENT/not Telewindows; this is
					;   for the remote (client) window of a
					;   G2; note that 2 should be replaced
					;   for any window serving as a
					;   Telewindow; however, a local
					;   (native) window is development and
					;   never gets a replacement for the 3
  native-window?				; nil for type ICP
  minimum-line-height-of-text-to-draw		; in window units -- 6 recommended
  (window-parameters-plist nil			; a tree made of
     :reclaimer                                 ;   unshared gensym conses
     reclaim-gensym-tree-with-text-strings)     ;   with some text-string leaves
  (color-map-for-window				; a color map
     nil :reclaimer reclaim-color-map-if-any)	; maybe get rid of "-if-any"
  (default-pane-background-color-or-tiling-pattern
    nil						; nil only transiently
    :reclaimer
      reclaim-default-pane-background-color-or-tiling-pattern)	; in WINDOWS2


  ;; Rasters
  (raster-for-native-window? nil)		; Unused, always NIL.

  (scratchpad-raster-type-for-window 'native)	; NATIVE, ICP, ...
  (stored-raster-type-for-window 'native)	; NATIVE, ICP, ...
  (regular-size-bitmap-raster-pools (allocate-small-2d-array
				      #.(length list-of-regular-raster-sizes))
				    :reclaimer reclaim-small-2d-array)
  (regular-size-pixmap-raster-pools (allocate-small-2d-array
				      #.(length list-of-regular-raster-sizes))
				    :reclaimer reclaim-small-2d-array)
  (irregular-size-bitmap-raster-pool nil :reclaimer reclaim-graphics-list)
  (irregular-size-pixmap-raster-pool nil :reclaimer reclaim-graphics-list)

  ;; Drawing Schedule, see `drawing-schedule'
  (count-of-enqueued-drawing 0)
  (drawing-transfer-mode-of-gensym-window :xor)

  ;; This holds just the palette name, not the list.
  (image-palette-of-gensym-window default-image-palette)

  ;; A list of (pixel-value red green blue), for use by background images.
  (additional-colors-allocated-for-window ())

  (window-is-in-v5-mode-p nil)

   ;; See section of same name
  (identified-drawing-activities-of-gensym-window
    nil :reclaimer cancel-list-of-pending-activity)
;  (representations-on-this-window nil)	; Unused. -fmw, 2/18/02
;  (window-output-inhibited-p nil)	; Unused  -fmw, 6/6/02
  (window-screen-depth 8)

  (icon-bitmap-count-for-window 0)
  (icon-bitmap-memory-for-window 0)	; In bytes (from bitmap-memory-used)

  (window-remote-drawing-not-synchronized-p nil)
  (window-remote-background-color 'unknown)
  
  (window-desired-left-edge-of-draw-area 'unknown)
  (window-desired-top-edge-of-draw-area 'unknown)
  (window-desired-right-edge-of-draw-area 'unknown)
  (window-desired-bottom-edge-of-draw-area 'unknown)
  (window-desired-transfer-mode 'unknown)
  (window-desired-background-color 'unknown)

  ;; Full-window pixmap used for buffered drawing.
  (offscreen-pixmap? nil :reclaimer reclaim-pixmap)
  
  ;; Local event queue's are used for the native-window case, but they are
  ;; instantiated in all cases, since there's very little overhead to having
  ;; them if they're not used. Added for G2 7.0, when we started having multiple
  ;; gensym windows per G2/TW. (MHD 1/22/02)
  (event-queue (make-queue) :reclaimer reclaim-local-event-queue)
  (reshape-event-queue (make-queue) :reclaimer reclaim-local-event-queue)
  (paste-event-queue (make-queue) :reclaimer reclaim-local-event-queue)

  ;; native-menu-table is managed array mapping from a menu-handle to a
  ;; gensym-list of the menu, the handle to the top-level menu, and the
  ;; top-level-item-list.  Each menu is kept in a snapshot-of-block structure to
  ;; protect against reclamation.  A temporary hack until native menus are
  ;; fleshed out.  Used only on the G2 side.  -fmw, 1/28/02
  (native-menu-table (allocate-managed-array 1024) :reclaimer reclaim-native-menu-table)

  (gensym-window-serial-number -1)	; Also used for session ID.
  
  ;; Native menu system slots.
  ;; A growable array of handle -> nms-menu or nms-menu-item.  This is used by
  ;; both G2 and TW.  We use entry 0 as a fill-pointer. -fmw, 3/20/02
  (nms-menu-table-slot nil :reclaimer nms-reclaim-menu-table)
  (nms-developer-menu-bar? nil)		; Cached developer menu bar. NIL or a handle
  (nms-current-menu-bar? nil)		; NIL or a handle
  (nms-saved-menu-bar? nil)		; Menu bar saved during system pause.
  (nms-dynamic-menu-modification-tick 0) ; Value of dynamic-menus-modification-tick on last update.

  ;; Native icons (for menus and, later, toolbars) -fmw, 7/16/03

  ;; These slots are used only by G2.
  (native-icons-table? nil	; Table from icon designation to fixnum handle
		       :reclaimer reclaim-native-icons-table)
  (free-icon-handles nil		; Gensym list of free handles
		     :reclaimer reclaim-gensym-list)
  (next-icon-handle 0)			; Maximum allocated handle + 1

  ;; These slots are used only by TW.
  (icon-polychrome-pixmap? nil :reclaimer reclaim-pixmap) ; Color scratchpad
  (icon-mask-pixmap? nil :reclaimer reclaim-pixmap)      ; Monochrome scratchpad

  ;; Native windows
  (next-native-window-handle 1)
  (native-windows-on-gensym-window nil :reclaimer reclaim-native-windows)

  ;; Infrequently used Native UI Properties
  (gensym-window-ui-properties nil :reclaimer reclaim-gensym-tree-with-text-strings)

  ;; Native logbook and message-board, if present.
  (native-logbook? nil)
  (native-message-board? nil)

  ;; Native status bar, created lazily.
  (native-status-bar? nil)

  ;; Cached value from drawing-parameters, needed only for mode changes.
  (show-selection-handles-of-gensym-window 'unknown)
  
  ;; Disconnect callbacks
  (twng-disconnect-callbacks nil :reclaimer reclaim-gensym-list))
  
;;
;; Disconnect callbacks
;;
  
;; add disconnect callback
(defun-simple add-twng-disconnect-callback (gensym-window callback)
  (let ((callback? (current-system-case ; NOTE: the whole function is G2 only.
		     (ab (stored-callback-procedure callback)))))
   (unless (or (null callback?)
               (find callback? (twng-disconnect-callbacks gensym-window)))
      (setf (twng-disconnect-callbacks gensym-window)
        (nconc (twng-disconnect-callbacks gensym-window)
               (gensym-list callback?))))))

;; Remove disconnect callback
;; Actually it needs to use something like (remove callback? (twng-disconnect-callbacks gensym-window))
;;  instread loop, but it does not work with gensym-lists and there is produced AV
(defun-simple remove-twng-disconnect-callback (gensym-window callback)
  (let* ((callback? (current-system-case ; NOTE: the whole function is G2 only.
		      (ab (stored-callback-procedure callback))))
         (new-callbacks
           (loop for cb in (twng-disconnect-callbacks gensym-window)
             unless (eql cb callback?) collect cb using gensym-cons)))
    ;; update callbacks list
    (reclaim-gensym-list (twng-disconnect-callbacks gensym-window))
    (setf (twng-disconnect-callbacks gensym-window) new-callbacks)))

;; clear disconnect callbacks
(defun-simple clear-twng-disconnect-callbacks (gensym-window)
  (unless (null (twng-disconnect-callbacks gensym-window))
    (reclaim-gensym-list (twng-disconnect-callbacks gensym-window))
    (setf (twng-disconnect-callbacks gensym-window) nil)))

;;;


(def-system-variable current-gensym-window-serial-number windows1 0)

;; Although it is possible that a gensym-window could be resuscitated with the
;; same serial number, it is so unlikely that I'm not worrying about it.
(defun-simple increment-current-gensym-window-serial-number ()
  (setf current-gensym-window-serial-number
	(if (=f current-gensym-window-serial-number most-positive-fixnum)
	    0
	    (1+f current-gensym-window-serial-number))))

(defun-simple make-gensym-window (native-window?)
  (let ((gensym-window (make-gensym-window-internal native-window?)))
    (setf (gensym-window-serial-number gensym-window)
	  (increment-current-gensym-window-serial-number))
    gensym-window))

(defun gensym-window-has-not-been-reprocessed-p (gensym-window serial)
  (and (=f (gensym-window-serial-number gensym-window) serial)
       (/=f (gensym-window-serial-number gensym-window) -1)))

;; Reclaimer for the old-style native popups (pre-NMS).
(defun reclaim-native-menu-table (native-menu-table)
  (current-system-case
    ;; reclaimer defined in new-menus or tw-patches.  Only called for G2.
    (ab (reclaim-contents-of-native-menu-table native-menu-table)))
  (reclaim-managed-array native-menu-table))

(defun nms-reclaim-menu-table (table?)
  (when table?
    (reclaim-contents-of-nms-menu-table table?)
    (reclaim-managed-array table?)))

;;; The function `nms-note-menu-deletion' is called when a native menu is
;;; deleted. T is a wildcard for all menus.

(defun nms-note-menu-deletion (gensym-window menu-handle-being-deleted)
  (macrolet ((check (slot)
	       `(when (or (eq menu-handle-being-deleted t)
			  (eql menu-handle-being-deleted (,slot gensym-window)))
		  (setf (,slot gensym-window) nil))))
    (check nms-developer-menu-bar?)
    (check nms-current-menu-bar?)
    (check nms-saved-menu-bar?)))


;;; Telewindows Sessions

(defun gensym-window-session-id (gensym-window)
  (gensym-window-serial-number gensym-window))

(defun find-gensym-window-with-session-id (session-id)
  (loop for workstation in workstations-in-service
	as gensym-window = (window-for-workstation workstation)
	when (equal session-id (gensym-window-session-id gensym-window))
	  return gensym-window))



;;; The function `get-gensym-window-event-queue',
;;; `get-gensym-window-reshape-event-queue', and
;;; `get-gensym-window-paste-event-queue' access the event-queue,
;;; reshape-event-queue, and paste-event-queue slots, respectively, of a
;;; gensym-window structure.
;;;
;;; The slots can also be accessed directly. However, the functions may be
;;; needed if forward referencing the slots from an earlier module.

#+unused
(defun get-gensym-window-event-queue (gensym-window)
  (event-queue gensym-window))

(defun get-gensym-window-reshape-event-queue (gensym-window)
  (reshape-event-queue gensym-window))

#+unused
(defun get-gensym-window-paste-event-queue (gensym-window)
  (paste-event-queue gensym-window))

;; Consider moving this structure definition or this entire section to
;; PLATFORMS, where the practically all of the forward referencing code
;; currently resides! (MHD 1/22/02)





;;; The function `get-gensym-window-of-native-window' returns the gensym-window
;;; structure of a Gensym window for a workstation in workstations-in-service
;;; whose native window matches the argument native-window?.  If there is no
;;; such window, it returns nil.  Note that if native-window? is nil, this
;;; matches the first gensym window whose native-window? slot is nil.
;;;
;;; The functions `get-event-queue-of-native-window',
;;; `get-reshape-event-queue-of-native-window', and
;;; `get-paste-event-queue-of-native-window' are similar, but rather than
;;; returning the gensym window, they return the event-queue,
;;; reshape-event-queue, and paste-event-queue slot value of the gensym window
;;; corresponding to native-window?

(defun get-gensym-window-of-native-window (native-window?)
  (loop for workstation in workstations-in-service
	when (eql native-window?
		  (native-window? (window-for-workstation workstation)))
	  return (window-for-workstation workstation)))

(defun get-event-queue-of-native-window (native-window?)
  (loop for workstation in workstations-in-service
	when (eql native-window?
		  (native-window? (window-for-workstation workstation)))
	  return (event-queue (window-for-workstation workstation))))

(defun get-reshape-event-queue-of-native-window (native-window?)
  (loop for workstation in workstations-in-service
	when (eql native-window?
		  (native-window? (window-for-workstation workstation)))
	  return (reshape-event-queue (window-for-workstation workstation))))

(defun get-paste-event-queue-of-native-window (native-window?)
  (loop for workstation in workstations-in-service
	when (eql native-window?
		  (native-window? (window-for-workstation workstation)))
	  return (paste-event-queue (window-for-workstation workstation))))

;; Looping over a relatively small number of workstations, say 50 to 100, is
;; probably negligeable overhead compared with, say, a hashtable lookup.  If the
;; the number of Gensym windows per G2 or per TW could reasonably be expected to
;; exceed 100 in practice, this should probably be changed to a faster
;; lookup!  Not now, but probably soon! (MHD 1/22/02)








(defun time-to-decache-p (gensym-window)
  (or (>f (icon-bitmap-count-for-window gensym-window)
 	  default-maximum-icon-bitmaps)
      (>f (icon-bitmap-memory-for-window gensym-window)
	  default-maximum-icon-bitmap-memory)))



;; This function defined to avoid forward reference problems with
;; icp-window-protocol-version

(defun window-supports-request-for-paste-availability-function (gensym-window)
  (window-supports-request-for-paste-availability gensym-window))

#+development
(defun pretty-type-of-gensym-window (gensym-window)
  (let ((type (type-of-gensym-window
		gensym-window)))
    (case type
      (x11-window 'x11)
      (t type))))
    

#+development
(defun print-gensym-window (gensym-window stream depth)
  (declare (ignore depth))
  (printing-random-object (gensym-window stream)
    (format stream "GENSYM-WINDOW ~a (~a)"
	    (pretty-type-of-gensym-window gensym-window)
	    (if (eq (drawing-transfer-mode-of-gensym-window gensym-window) ':xor)
		'xor 'paint))))

#+development
(defun-simple workstation-this-is-on-function (gensym-window)
  (workstation-this-is-on gensym-window))



;;; Close-native-window closes all the native windows in service.  (The lack of
;;; a plural ending is a historical misnomer.)

(defun-void close-native-window ()
  (loop for workstation in workstations-in-service
	as native-window? = (native-window? (window-for-workstation workstation))
	when native-window?
	  do (c-x11-close native-window?)))

;; This previously closed just the native window of system-window, which
;; is not consistent with the fully general architecture. (MHD 3/1/01)



;; An important assumption here is that there only two different
;; depths are used for stored rasters:  depth 1 (bitmaps) and screen-depth
;; (pixmaps).  I think it's unlikely that we'll need rasters of other depths.
;; -pto 13jun89

;; The default-pane-background-color-or-tiling-pattern slot's value
;; is always at present shared with the pane-background-color-or-tiling-pattern
;; slot in each of its panes; that slot has no reclaimer.  If it were to ever
;; have unique structure in it, a solution to the recycling problem would have
;; be engineered. (MHD 11/21/89)

;;; The `icp-window-protocol-version slot of gensym-window' holds is discussed
;;; in the section "ICP Window Protocol Version" of platforms.  It contains
;;; the maximum protocol-version acceptible to both sides of the connection.
;;; It maybe less than that "requested" in the parameters plist.
;; - ben 7/14/93

;;; The `drawing-transfer-mode-of-gensym-window slot of gensym-window' is used
;;; to bind current-drawing transfer mode when we go on-window.  See the
;;; documentation of current-drawing transfer mode for discussion it's values.
;;; This slot defaults to the lowest common denominator, i.e. :XOR.  During the
;;; process of setting up a window it maybe promoted to :PAINT-INFERED-FROM-XOR.
;;; This happens if both sides of the icp window protocol can handle it, and if
;;; the KB hasn't overridden it.  Currently there is no UI for the KB to
;;; override it.
;; - ben 7/14/93

;;; The `image-palette-of-gensym-window' slot is a copy of the value in
;;; drawing-parameters.  The possible values are listed there in the grammar
;;; category.
;; -fmw, 4/20/94




;;; The function `slave-gensym-window?' returns true if the given window is a
;;; "slave" window on the telewindows side of a connection.  If we are
;;; telewindows, then any window is a slave.

(defun slave-gensym-window? (gensym-window)
  (or (memq current-system-name '(telewindows))
      (icp-output-port-to-master-for-window? gensym-window)))


(defun icp-socket-for-gensym-window? (gensym-window)
  (let ((icp-output-port? (icp-output-port-for-window? gensym-window)))
    (when icp-output-port?
      (parent-icp-socket icp-output-port?))))
   


(def-substitution-macro x11-window-p (gensym-window)
  (eq (type-of-gensym-window gensym-window) 'x11-window))


(def-substitution-macro icp-window-p (gensym-window)
  (eq (type-of-gensym-window gensym-window) 'icp))


;;; `Printing-window-p' is used to guard places that manipulate rasters or do
;;; N-window updates so that they do not side effect the printing window.  This
;;; is needed since printing may be spread over time.  See also
;;; `drawing-for-eyes-of-player-p', `printing-p', and `printing-p-macro'.

(defun printing-window-p (gensym-window)
  (eq (type-of-gensym-window gensym-window) 'printer))

;; This one needs to be a function.


(defvar x-debugging-on nil)

(defun debug-x11 ()
  (cond ((setq x-debugging-on (not x-debugging-on))
	 (c-x11-set-debugging-mode (native-window? system-window)))
	(t
	 (c-x11-clear-debugging-mode (native-window? system-window))))
  x-debugging-on)


;; Caveats: May return NIL. Not the fully-qualified unique host name, just the
;; name part. Can be set by the user with $HOSTNAME.
(defun gensym-window-host-name (gensym-window)
  (or (getf (window-parameters-plist gensym-window) 'network-host-name)
      (get-local-host-name)))

(defun gensym-window-os-type (gensym-window)
  (or (getf (window-parameters-plist gensym-window) 'os-type)
      g2-operating-system))

;; The local calls must match code in get-telewindows-miscellaneous-info.



;;;; On-window-without-drawing



;;; `On-window-without-drawing' provides the facilities to do coordinate
;;; transforms, clipping, and compute color values as if we had focused the
;;; drawing on a particular window.  This is useful when doing mouse
;;; tracking, computing drawing bounds, or rehearsing a color change.

;;; The persistent state underlying this dynamic extent is stored in the
;;; gensym-window data structure.

;;; This is necessary since when actually draw to the window we must do a number
;;; of expensive things.  Two examples: in some cases we must start and end an
;;; ICP message group, and in some cases we must hide the window's cursor.

;;; Going on window without drawing is a precondition of drawing.

;;; These four dynamic extents are established, one after another.
;;;   1. on-window-without-drawing
;;;   2. on-window-with-drawing
;;;   3. on-image-plane
;;;   4. with-block-transform
;;; The second one maybe skipped, if you are not actually drawing.  The
;;; third and fourth are create the coordinate transformations to map
;;; coordinates in the given block into the screen coordinates.

;;; Draw area and coordinate transformation maybe altered locally using the
;;; these wrappers:
;;;   1. with-draw-area
;;;   2. with-nested-draw-area?
;;;   3. with-scalling

(def-named-dynamic-extent on-window-without-drawing
  (module windows1))


;;; `Current-window in on-window-without-drawing' is the gensym-window we are
;;; on.  Windows have a device specific coordinate system, and a device specific
;;; color map.  Specific windows may have defering behaviors for queuing drawing,
;;; for example a local window may draw synchronizely, while a remote one may
;;; not.  In G2 at present only one local window ever exists.

(defvar-of-named-dynamic-extent current-window on-window-without-drawing)



;;; `Drawing-on-window' is a boolean indicating if we are actually drawing,
;;; i.e.  if it is acceptable to put ink on the paper.  It is NIL when we are
;;; only simulating drawing, for example to do mouse tracking.

(defvar-of-named-dynamic-extent drawing-on-window on-window-without-drawing) ; boolean


;;; The substitution-macro `within-window-drawing-context-p' is true if we are
;;; currently in an on-window-WITH-drawing context.

(def-substitution-macro within-window-drawing-context-p ()
  (and (boundp 'drawing-on-window) drawing-on-window))



;;; The `draw-area' is a rectangular area within which drawing is clipped.  The
;;; draw area is intially bound as part of establishing the
;;; on-window-without-drawing extent.  It is held in the four edges
;;; `left-edge-of-draw-area', `top-edge-of-draw-area',
;;; `right-edge-of-draw-area', and `bottom-edge-of-draw-area'.

;;; The draw area is always established prior to going
;;; on-window-without-drawing, usually just before.  The draw area is always
;;; first established with the macro `with-draw-area'.  It often rebound with
;;; the macro `with-nested-draw-area?'.

;;; Most layers of the drawing protocol stack implement some clipping or focus
;;; using the draw area.  This is good since often deeper layers lack the
;;; knowledge to do better clipping.  For example text drawing isn't smart
;;; enough to be able to tell if a piece of text will overlap the draw area, it
;;; can only tell if the text is entirely or partially below the draw area.

;;; Because of this you must be extremely careful when you set the draw area.
;;; The safest thing is always refine the draw area using with-nested-draw-area?
;;; It is almost never safe to set it, since you may widen the draw area by
;;; mistake.


;;; The draw area is drawn in tightly for some drawing, for example to clip text
;;; when doing incremental updates.  Sadly, it is not drawn in tightly prior to
;;; calling the block's draw method since the block may have subblocks that make
;;; it difficult to compute the approprate draw area to bind.

;;; See also `draw-area-macros' for abstractions usefule for managing the draw
;;; area.  See `bleeding', `bleeding-hack', and `quick-clipping' for tools for
;;; dealing with the slop that arises around scalling.  See
;;; `gensym-window-geometry' for a discussion of how the window's display
;;; hierarchy creates clipped draw areas.

(def-concept draw-area)

(defvar-of-named-dynamic-extent left-edge-of-draw-area   on-window-without-drawing)
(defvar-of-named-dynamic-extent top-edge-of-draw-area    on-window-without-drawing)
(defvar-of-named-dynamic-extent right-edge-of-draw-area  on-window-without-drawing)
(defvar-of-named-dynamic-extent bottom-edge-of-draw-area on-window-without-drawing)


;;; The `drawing-transform' is used to map from coordinate values stored in the
;;; KB into actual screen coordinates.  This transform, which includes no
;;; rotation, is implemented in the usual manner involving four values.  The
;;; horizontal transform uses `current-image-x-scale' and
;;; `x-origin-of-workspace-in-window'.  While `current-image-y-scale' and
;;; `y-origin-of-workspace-in-window' manage the horizontal scalling.

;;; These names are a historical artifact.  Originally only the workspaces were
;;; scaled into image-planes.  Direct access to these values is discouraged.

;;; The scaling uses scaled arithmetic.  See scales, or `normalized-scale'.

;;; There is no constraint on the aspect ratio.  

(def-concept drawing-tranform)

(defvar-of-named-dynamic-extent current-image-x-scale on-window-without-drawing)
(defvar-of-named-dynamic-extent current-image-y-scale on-window-without-drawing)
(defvar-of-named-dynamic-extent current-x-origin-of-drawing on-window-without-drawing)
(defvar-of-named-dynamic-extent current-y-origin-of-drawing on-window-without-drawing)






;;; `Type-of-current-window' is bound to a symbol.  `ICP' indicates that the
;;; window is implemented by using the Telewindow ICP protocol.  `X11' indicates
;;; that the window is local, and that the X11 drawing operations, or a simulation
;;; of them are in use.

;;; `Printer' indicates that the window is implemented using the printer drawing
;;; operations.  These are implemented by dispatching thru the ICP message
;;; functions and diverting to functions that emit postscript.

;;; In the pass this took on additional values, these are now obsolete.  `Native'
;;; used to implement the Lispm drawing routines.

;;; There is a significant portion of the code that contains expressions of the
;;; for (case type-of-current-window (t ...)).  Code like this is rewritten by
;;; the inclosing macro to insert clauses for the printer, and icp cases.  See
;;; def-icp-message-functions for additional details.

;;; This is read-only and taken directly from the gensym-window data structure.

(defvar-of-named-dynamic-extent type-of-current-window on-window-without-drawing)



;;; `Current-native-window?' is bound to the native window data structure or
;;; handle when the window is of type `x11' or `native'.  In the X11 case it is
;;; bound to the handle of the x11 stream, i.e. it often has the value zero.

;;; See also system-window.

;;; This is read-only and taken directly from the gensym-window data structure.

(defvar-of-named-dynamic-extent current-native-window? on-window-without-drawing)




;;; `Current-color-map' is bound to assist the acceleration of mapping symbolic
;;; color names to actual color values.  Of course, color values are per window.
;;; A fact that can be easily overlooked since they tend to be same across unix
;;; platforms.

;;; This is read-only and taken directly from the gensym-window data structure.

(defvar-of-named-dynamic-extent current-color-map on-window-without-drawing)



;;; `Current-drawing-transfer-mode' broadcasts the transfer mode in use for all
;;; drawing.  It is always bound to one of two values, either `:xor' or
;;; `:paint-infered-from-xor.'

;;; Outside of on-window it is used to announce what transfer mode is in use by
;;; updating, with a default of :paint-infered-from-xor.  It is rebound to :XOR
;;; when the object occassionally.  When updating an object, overlapping objects
;;; will be redrawn if current-drawing-transfer-mode is :paint-infered-from-xor,
;;; but not otherwise.

;;; Inside of on-window it is bound to the transfer mode actually used do the
;;; drawing.  This may be less than that requested by updating when the
;;; window are in is not capable of painting.  Any rebinding of when
;;; on-window must take care to synchronize the connected telewindows,
;;; the macro `with-transfer-mode-when-drawing' is used to implement that.

;;; The ICP drawing functions transfer mode used in the native graphics engine
;;; and adjust the color values on the basis of current-drawing-transfer-mode.


;;; The prefered transfer mode of each window is stored in the slot
;;; drawing-transfer-mode-of-gensym-window for the gensym-window.  The prefered
;;; transfer mode of G2 at large is bound here as the initial value for the
;;; process binding.

(defvar-of-named-dynamic-extent current-drawing-transfer-mode   on-window-without-drawing
  (process-binding :paint-infered-from-xor))

(defmacro paint-mode-p ()
  `(eq current-drawing-transfer-mode :paint-infered-from-xor))

(defmacro xor-mode-p ()
  `(eq current-drawing-transfer-mode :xor))


;;; The macro `drawing-transfer-mode-of-current-window' returns the top-level
;;; value for the transfer mode, as opposed to the the above macros, which
;;; are based on the current binding.

(defmacro drawing-transfer-mode-of-current-window ()
  `(drawing-transfer-mode-of-gensym-window current-window))



;;; `Current-foreground-color-value' and `Current-background-color-value' hold
;;; the color value in which the current drawing should be done.  From these it
;;; is possible to infer the color-difference when doing XOR drawing.  Note that
;;; many of the drawing routines take a color difference, and when painting the
;;; color color value is infered by undoing the color difference using the
;;; background color value.

(defvar-of-named-dynamic-extent current-background-color-value on-window-without-drawing)

(defvar-of-named-dynamic-extent current-foreground-color-value on-window-without-drawing)



;;; `Current-pane' is the pane within which drawing is taking place.  This
;;; pane's pane cursors are overlay any drawing that takes place.

(defvar-of-named-dynamic-extent current-pane on-window-without-drawing)



;;; `Current-drawing-priority' states which of an enumerated set of
;;; behaviors should be used for handling fresh drawing tasks as they
;;; are inserted into the drawing queue.

;;; This is what enables scheduled drawing, ie, enqueueing drawing tasks to be
;;; performed at some more convenient time.  The value of
;;; `enable-scheduled-drawing?' slot in drawing parameters is copied into this
;;; variable.

;;; This configures the behavior of the input side of the drawing queues.

(defvar-of-named-dynamic-extent current-drawing-priority
    on-window-without-drawing
  (process-binding :draw-as-late-as-possible))

;; This variable has defaulted to :draw-as-soon-as-possible since the beginning,
;; which is odd since the value in the drawing-parameters system table defaults
;; to :draw-as-late-as-possible.  Code is not supposed to ever see this
;; top-level binding, but some does, and gets the old, deprecated behavior of
;; unscheduled drawing.  Changing the default here papers over the problem for
;; HQ-4081890. -fmw, 1/18/02


(defun-substitution-macro draw-as-soon-as-possible? ()
  (eq current-drawing-priority :draw-as-soon-as-possible))


;;; `Drawing-is-scheduled?' is the opposite of draw-as-soon-as-possible?.

(defun-substitution-macro drawing-is-scheduled? ()
  (eq current-drawing-priority :draw-as-late-as-possible))


;;; `Draw-as-soon-as-possible' is the setting used to configure G2 to mimic the
;;; behavior of a 3.0 G2.  I.e. that drawing drags down even simple slot
;;; assignment by happening sychcronized.  This is not equivalent to XOR drawing
;;; persay since we may rewrite the individual KB drawing tasks as are mapped
;;; into the window hierarchy.  Also called ASAP mode.

(def-concept :draw-as-soon-as-possible)


;;; `:Draw-as-late-as-possible' is bound to current-drawing-priority to signal
;;; the drawing queues that it will be better if they defer the drawing
;;; in progress.  This use may trigger this via his drawing-parameters, and
;;; G2 may internally bind it over dynamic extents to reduce flicker.

(def-concept :draw-as-late-as-possible)



;;; These curious variables control the behavior of region invalidations.
;;; `current-draw-paper-p' turns on the asap clear (or sketch).

(defvar-of-named-dynamic-extent current-draw-paper-p
    on-window-without-drawing
  (process-binding t))

(defvar-of-named-dynamic-extent current-draw-document-p
    on-window-without-drawing
  (process-binding t))

(defvar-of-named-dynamic-extent workspace-for-current-draw-document?
    on-window-without-drawing
  (process-binding nil))




;;;; Wrappers Draw Area and Transform



;;; The draw area and transform must be established before establishing the rest
;;; of on-window-without-drawing.  Why? you ask, I can't recall.  Then, once you
;;; are on window, you may refine the draw area or transform as you proceed with
;;; the drawing.

;;; - Scaling and Framing -

;;; Whenever the scaling transform is refined the draw area must be refined.
;;; All things that refine the transform (e.g. the window, and blocks with
;;; frames (today that is workspaces and edit-boxes) have strick clipping.
;;; Because workspaces are so damn different from framed blocks the protocol has
;;; different wrappers for these two cases.  Note that the frame around these
;;; things is drawn at the scaling of the enclosing context.  Each of these
;;; things has two rectangles, it's edges, and the content rectangle.  The
;;; content rectangle is the one that clips it's contents.  The frame fills
;;; the region between the two.

;;; - Nest but never set draw area -

;;; Once you are on window you should never set the draw area, only refine
;;; it via nesting.  This rule arises because the patterns that invoke draw
;;; routines, what with scheduling, transfer modes, and XOR overlays are must
;;; to complex to allow anybody to be sure that they know the caller's
;;; clipping behavior.  Just one example: if we got the exposed area from the
;;; window system we would assure that the draw area was refined to that when
;;; we go on-window.

;;; There is currently one exception to this.  When we discover it is necessary
;;; to force drawing (i.e. drain the drawing Qs) for some poorly implemented
;;; draw-function, then we pop the drawing area open around the forcing.

;;; - Empty draw areas -

;;; When refining the draw area it may become empty.  The macro
;;; with-nested-draw-area? is used to prevent any drawing when this happens.
;;; See draw-function for a discussion of the limited side effects that
;;; draw-functions are allowed to have.

;;; - Initial Binding -

;;; Establishing the initial binding for draw area and transform is called
;;; creating the raw-draw-area.  The rarely use macro with-draw-area encapsulates
;;; this.  The most common way abstraction for this operation is provided by
;;; `with-raw-window-transform-and-draw-area.'  Telewindows (which doesn't
;;; do scaling) uses with-draw-area in it's handler for the update message.


;; See the concept `draw-area' and `drawing-transform'.

(def-concept draw-area-macros)


;;; `Left-edge-within-area' clips left-edge into the area whose left edge is
;;; left-edge-of-area.  `Top-edge-within-area', `right-edge-within-area', and
;;; `bottom-edge-within-area' are similar.  They may be used for edges in both
;;; window and workspace coordinate systems.

(defmacro left-edge-within-area (left-edge left-edge-of-area)
  `(maxr ,left-edge ,left-edge-of-area))

(defmacro top-edge-within-area (top-edge top-edge-of-area)
  `(maxr ,top-edge ,top-edge-of-area))

(defmacro right-edge-within-area (right-edge right-edge-of-area)
  `(minr ,right-edge ,right-edge-of-area))

(defmacro bottom-edge-within-area (bottom-edge bottom-edge-of-area)
  `(minr ,bottom-edge ,bottom-edge-of-area))

;; Note that these use maxr and minr, even though they are advertised for use
;; with both window and workspace coordinate systems.



;;; `Left-edge-within-draw-area' does precise `clipping' for the left of some
;;; object to the left edge of the draw area.  The result is guaranteed to be
;;; within the current draw area.  `Top-edge-within-draw-area',
;;; `right-edge-within-draw-area', and `bottom-edge- within-draw-area' are
;;; similar.

(defmacro left-edge-within-draw-area (left-edge-in-window)
  `(left-edge-within-area ,left-edge-in-window left-edge-of-draw-area))

(defmacro top-edge-within-draw-area (top-edge-in-window)
  `(top-edge-within-area ,top-edge-in-window top-edge-of-draw-area))

(defmacro right-edge-within-draw-area (right-edge-in-window)
  `(right-edge-within-area ,right-edge-in-window right-edge-of-draw-area))

(defmacro bottom-edge-within-draw-area (bottom-edge-in-window)
  `(bottom-edge-within-area ,bottom-edge-in-window bottom-edge-of-draw-area))


#+development
(defvar drawing-portal-explaination-serial 0)

#+development
(defvar drawing-portal-explaination-frame-size 3)

#+development
(defvar-of-special-global drawing-portal-explaination (make-array 60))

#+development
(defvar drawing-portal-explaination-index (- drawing-portal-explaination-frame-size))

(defmacro set-drawing-portal-explaination (who why)
  #+development
  `(set-drawing-portal-explaination-1 ,who ,why)
  #-development (progn who why))

#+development
(defun set-drawing-portal-explaination-1 (who why)
  (setf (svref drawing-portal-explaination (+ 0 drawing-portal-explaination-index))
	(incf drawing-portal-explaination-serial))
  (when (<= 9999 drawing-portal-explaination-serial)
    (setf drawing-portal-explaination-serial 0))
  (setf (svref drawing-portal-explaination (+ 1 drawing-portal-explaination-index))
	who)
  (setf (svref drawing-portal-explaination (+ 2 drawing-portal-explaination-index))
	why))

#+development
(defun show-drawing-portal ()
  (loop for i from 0 by 3 upto drawing-portal-explaination-index
	do
    (format t "~&~4D: ~(~A~) of ~S"
	    (svref drawing-portal-explaination (+ 0 i))
	    (svref drawing-portal-explaination (+ 2 i))
	    (svref drawing-portal-explaination (+ 1 i)))))



;;; `When-non-empty-draw-area?' executes it's body only if the draw area is non
;;; empty.  Since `draw-functions' (see concept) must have very limited side
;;; effects this can be used extensively.

(defmacro when-non-empty-draw-area? (&body body)
  `(when (rectangle-not-empty-p left-edge-of-draw-area
				top-edge-of-draw-area
				right-edge-of-draw-area
				bottom-edge-of-draw-area)
     ,@body))


;;; `With-draw-area-contour' does just that.  It does not change the current
;;; bindings.  This is used in wrappers that create the correct dynamic extent
;;; as necessary, i.e.  those who's callers may or may not have already
;;; established it.

(defmacro with-draw-area-contour ((&optional who why) &body body)
  `(let (#+development (drawing-portal-explaination-index
			 (+ drawing-portal-explaination-frame-size
			    drawing-portal-explaination-index))
	   (left-edge-of-draw-area
	   #+development (+f left-edge-of-draw-area 0)
	   #-development left-edge-of-draw-area)
	 (top-edge-of-draw-area top-edge-of-draw-area)
	 (right-edge-of-draw-area right-edge-of-draw-area)
	 (bottom-edge-of-draw-area bottom-edge-of-draw-area))
     (set-drawing-portal-explaination ,who ,why)
     ,@body))



;;; `Set-nested-draw-area' should be used only within a with-draw-area-contour
;;; and completes the rebinds of the edges.

(defmacro set-nested-draw-area (left-edge-in-window
				 top-edge-in-window
				 right-edge-in-window
				 bottom-edge-in-window
				 &optional who why)
  `(progn
     (set-drawing-portal-explaination ,who ,why)
     (setf left-edge-of-draw-area
	   (left-edge-within-draw-area ,left-edge-in-window))
     (setf top-edge-of-draw-area
	   (top-edge-within-draw-area ,top-edge-in-window))
     (setf right-edge-of-draw-area
	   (right-edge-within-draw-area ,right-edge-in-window))
     (setf bottom-edge-of-draw-area
	   (bottom-edge-within-draw-area ,bottom-edge-in-window))))



;;; `With-nested-draw-area?' rebinds the draw area of the current window to the
;;; intersection of the draw area and the rectangle given by the four arguments.
;;; The body is executed only if the resulting draw area is non-empty.  This may
;;; only be executed within the on-window-without-drawing extent.

(defmacro with-nested-draw-area? ((left-edge-in-window
				    top-edge-in-window
				    right-edge-in-window
				    bottom-edge-in-window
				    &optional who why)
				  &body body)
  `(with-draw-area-contour (:optional-contour :optional-contour)
     (set-nested-draw-area ,left-edge-in-window
			   ,top-edge-in-window
			   ,right-edge-in-window
			   ,bottom-edge-in-window
			   ,who ,why)
     (when-non-empty-draw-area?
       ,@body)))


;;; `With-nested-draw-area' is the same, except that the body always executes,
;;; even if the resulting draw area is empty.

(defmacro with-nested-draw-area ((left-edge-in-window
				   top-edge-in-window
				   right-edge-in-window
				   bottom-edge-in-window
				   &optional who why)
				 &body body)
  `(with-draw-area-contour (:optional-contour :optional-contour)
     (set-nested-draw-area ,left-edge-in-window
			   ,top-edge-in-window
			   ,right-edge-in-window
			   ,bottom-edge-in-window
			   ,who ,why)
     ,@body))




;;; `currently-jump-out-of-drawing-image-plane-when-empty-rectangle-p' is a
;;; global variable used to control a fix for HQ-1354005, "G2 hangs in drawing
;;; loop".  The following sequence of events produce the bug:
;;;   - create a user-menu-choice which moves the workspace of the object
;;;     to the center of the screen.
;;;   - create an object of the applicable class for the user-menu-choice and
;;;     place it on a workspace far from the center of the screen.
;;;   - bring up the menu of the object, and select the user-menu-choice.
;;;   - three areas become invalidated by this action: (a) the area where
;;;     the workspace was, (b) the area it's being moved to, and (c) the
;;;     area under the menu.  [Area (c) is contained within area (a), but
;;;     these two parts of G2 aren't communicating well enough to know
;;;     that.  (a) is added because the workspace is being moved by the
;;;     user-menu-choice, and (c) is added simply because the menu went
;;;     away.]
;;;   - the area under where the workspace used to be is redrawn
;;;   - the area of the image plane which had been obscured by the menu is
;;;     redrawn.  However, the time slice expires before it is finished,
;;;     and refresh-region-of-image-plane "allows-other-processing" by
;;;     returning, believing that it has accurately captured the state
;;;     of the drawing inside the drawing-task structure.
;;;   - now the image-plane is moved.  The region inside of the image-plane
;;;     structure is modified.
;;;   - we get back to finishing redrawing the invalid regions.  The menu
;;;     area is on the top of the drawing queue for the image plane.  We
;;;     call refresh-region-of-image-plane with that task.
;;;   - the image plane has been shifted already, so the two areas are
;;;     disjoint.  "with-nested-draw-area?" sees that the areas are disjoint 
;;;     and so doesn't execute the body of refresh-region-of-image-plane.
;;;   - since the body of refresh-region-of-image-plane isn't getting run,
;;;     the state of the drawing task does not get advanced to nil.  Therefore,
;;;     it does not get popped off the queue.  When "work-on-drawing-schedule"
;;;     gets called with this image plane, it will try to execute the top task
;;;     which will return without doing any work, but without indicating that
;;;     it is finished.  We are now in an infinite loop.
;;;
;;; However, it is not easy to reproduce.  Drawing the menu is fairly quick,
;;; and usually completes within one drawing time slice.
;;;
;;; The point of the following variable and system-procedure is that I'm
;;; touching something very low-level, and any drawing bugs which are found
;;; after this (and most that have been found already) will be blamed on
;;; this fix.  By making the fix dependent on a global variable, we can
;;; easily turn it off in a distribution image and restore the old behavior.
;;;
;;; Update: It's been a year, and I don't believe it has caused any
;;; problems, and the cerror to detect the problem in with-nested-draw-area-
;;; for-image-plane? has only been reported to me four or five times, so
;;; I think we can say that this was a situation very hard to get into, and
;;; that the fix is appropriate when we do.  Making this variable obsolete.
;;; jv, 5/9/98

(defvar currently-jump-out-of-drawing-image-plane-when-empty-rectangle-p t)



;;; `with-nested-draw-area-for-image-plane?' is like with-nested-draw-area?
;;; but it requires the state of the drawing-task to be passed, and will
;;; modify that state if the draw-area rectangle is "empty".  The logic
;;; is that this is only called when we are presuming there is work to
;;; be done, so to simply exit without doing any work cannot be the
;;; right thing to do.  If there is no actual work to be done in this
;;; task, then we should set the task so that it will be removed from
;;; the queue and G2 can get around to doing some other work for a change.
;;;
;;; This fix used to be dependent on the global variable above.  When
;;; currently-jump-out-of-drawing-image-plane-when-empty-rectangle-p was nil,
;;; this macro behaved exactly as "with-nested-draw-area?".
;;;
;;; Since the one way to reproduce this bug is fairly obscure and very
;;; timing dependent, I wanted to know if anyone else happens to run into
;;; it.  That's why I put a #+development cerror there.  I've given it
;;; ten months (roughly), and it's only come up a few times, never
;;; reproducibly, so I'm repealing the code that makes the fix conditional.
;;; - jv 5/9/98

(defmacro with-nested-draw-area-for-image-plane?
    ((left-edge-in-window
       top-edge-in-window
       right-edge-in-window
       bottom-edge-in-window
       state
       &optional who why)
     &body body)
  `(with-draw-area-contour (:optional-contour :optional-contour)
     (set-nested-draw-area ,left-edge-in-window
			   ,top-edge-in-window
			   ,right-edge-in-window
			   ,bottom-edge-in-window
			   ,who ,why)
     (cond
       ((rectangle-not-empty-p left-edge-of-draw-area
			       top-edge-of-draw-area
			       right-edge-of-draw-area
			       bottom-edge-of-draw-area)
	;; the above test is what "when-non-empty-draw-area?" expands into
	,@body)
       (,state
	(setf ,state nil)))))



;;; `With-draw-area' is binds the edges of the draw area.  It is rarely used, in
;;; most cases the maro with-nested-draw-area? is prefered.  It is used when
;;; first establishing the on-window-without-drawing extent, or moving the focus
;;; form one image-plane to another.  See the concept `draw-area' in panes for
;;; additional discussion.

;;; This is used in with-raw-window-transform-and-draw-area, and in
;;; with-raw-window-transform-and-draw-area.

(defmacro with-draw-area ((left-edge-in-window
			   top-edge-in-window
			   right-edge-in-window
			   bottom-edge-in-window &key who why)
			  &body body)
  `(let (#+development (drawing-portal-explaination-index
			 (+ drawing-portal-explaination-frame-size
			    drawing-portal-explaination-index))
		       (left-edge-of-draw-area ,left-edge-in-window)
		       (top-edge-of-draw-area ,top-edge-in-window)
		       (right-edge-of-draw-area ,right-edge-in-window)
		       (bottom-edge-of-draw-area ,bottom-edge-in-window))
     (set-drawing-portal-explaination ,who ,why)
     ,@body))



;;; `With-null-drawing-transform' creates an initial drawing transform consisting
;;; of the identity transform.

(defmacro with-null-drawing-transform (&body body)
  `(let ((current-image-x-scale #.(normalized-scale))
	 (current-image-y-scale #.(normalized-scale))
	 (current-x-origin-of-drawing 0)
	 (current-y-origin-of-drawing 0))
     ,@body))

;; This routine is often used to undo the transform created by on-image-plane
;; and friends when we actually want to work on the frame as well. Ugh.



;;; `With-raw-window-transform-and-draw-area' establishes the outermost
;;; binding for the draw area and transformation of this window.  Note
;;; Note that the scaling is set to 1, inspite of the setting for
;;; `default-x-scale' in the gensym-window because that is the default
;;; for image-planes, not for the entire window.  This is why the frames
;;; on image-planes don't scale up when you set the -magnification switch
;;; on the command line.

;;; This routine one of the ONLY ways to get a top level binding for the
;;; draw area.

(defmacro with-raw-window-transform-and-draw-area ((gensym-window) &body body)
  (avoiding-variable-capture (gensym-window)
    `(with-draw-area ((left-edge-of-window ,gensym-window)
		      (top-edge-of-window ,gensym-window)
		      (right-edge-of-window ,gensym-window)
		      (bottom-edge-of-window ,gensym-window)
		      :who ,gensym-window
		      :why :exterior)
       (with-null-drawing-transform
	 ,@body))))



;;; `With-draw-area-for-mouse-tracking' is used to establish a small draw area,
;;; presumably around the current mouse location.  This is used in some mouse
;;; tracking routines.

(defmacro with-draw-area-for-mouse-tracking ((x-in-workspace y-in-workspace) &body body)
  (avoiding-variable-capture (x-in-workspace y-in-workspace)
    `(with-draw-area ((x-in-window (-w ,x-in-workspace 4))
		      (y-in-window (-w ,y-in-workspace 4))
		      (x-in-window (+w ,x-in-workspace 4))
		      (y-in-window (+w ,y-in-workspace 4))
		      :who current-workstation
		      :why :mouse)
       ,@body)))



;;; The macro `with-draw-area-as-region' creates a temporary region object
;;; which represents the current drawing area.

(defmacro with-draw-area-as-region ((region) &body body)
  `(with-region-from-rectangle-void (,region left-edge-of-draw-area
					     top-edge-of-draw-area
					     right-edge-of-draw-area
					     bottom-edge-of-draw-area)
     ,@body))




;;; `With-nested-draw-area-of-pane?' does just that, but due to the
;;; `pane-area-hack' this takes a image-plane rather than a pane.  This uses
;;; `with-nested-draw-area?'.

;;; Note that panes do not have a frame, or transformation.

(defmacro with-nested-draw-area-of-pane? ((image-plane) &body body)
  (avoiding-variable-capture (image-plane)
    `(with-nested-draw-area? ;; Focus draw area into PANE.
	 ((left-edge-of-pane-in-window ,image-plane)
	  (top-edge-of-pane-in-window ,image-plane)
	  (right-edge-of-pane-in-window ,image-plane)
	  (bottom-edge-of-pane-in-window ,image-plane)
	  (pane-for-image-plane ,image-plane)
	  :interior)
       ,@body)))



;;; The macro `with-pane-draw-area' binds the draw area to be the the interior
;;; of the pane for the given image-plane.

(defmacro with-pane-draw-area ((image-plane) &body body)
  (avoiding-variable-capture (image-plane)
    `(with-draw-area
	 ((left-edge-of-pane-in-window ,image-plane)	    ; Joke. Pane slots are in the image-plane.
	  (top-edge-of-pane-in-window ,image-plane)
	  (right-edge-of-pane-in-window ,image-plane)
	  (bottom-edge-of-pane-in-window ,image-plane)
	  :who (pane-for-image-plane ,image-plane)
	  :why :interior)
       ,@body)))



;;; The macro `with-nested-image-plane-draw-area?' focuses the draw area onto
;;; the exterior edges of the image-plane, clipped by its pane.

(defmacro with-nested-image-plane-draw-area?
    ((image-plane) &body body)
  `(with-nested-draw-area-of-pane? (,image-plane)
     (with-nested-draw-area?
	 ((left-edge-of-image-in-window ,image-plane)
	  (top-edge-of-image-in-window ,image-plane)
	  (right-edge-of-image-in-window ,image-plane)
	  (bottom-edge-of-image-in-window ,image-plane)
	  ,image-plane :exterior)
       ,@body)))



;;; The macro `with-image-plane-draw-area?' binds the draw area to the exterior
;;; of the given image plane, within its pane.

(defmacro with-image-plane-draw-area?
    ((image-plane) &body body)
  `(with-pane-draw-area (,image-plane)
     (with-nested-draw-area?
	 ((left-edge-of-image-in-window ,image-plane)
	  (top-edge-of-image-in-window ,image-plane)
	  (right-edge-of-image-in-window ,image-plane)
	  (bottom-edge-of-image-in-window ,image-plane)
	  ,image-plane :exterior)
       ,@body)))



;;; The macro `with-nested-image-plane-interior-draw-area' focuses the draw
;;; area to the interior of the given image plane.

(defmacro with-nested-image-plane-interior-draw-area
    ((image-plane) &body body)
  `(with-nested-draw-area
       ((left-edge-of-workspace-area-in-window ,image-plane)
	(top-edge-of-workspace-area-in-window ,image-plane)
	(right-edge-of-workspace-area-in-window ,image-plane)
	(bottom-edge-of-workspace-area-in-window ,image-plane)
	,image-plane :interior)
     ,@body))



;;; The macro `with-nested-image-plane-interior-draw-area?' focuses the
;;; draw area onto the interior of the image-plane.

(defmacro with-nested-image-plane-interior-draw-area?
    ((image-plane) &body body)
  `(with-nested-image-plane-interior-draw-area (,image-plane)
     (when-non-empty-draw-area?
       ,@body)))



;;; The macro `set-draw-area-from-image-plane-interior' sets the draw area
;;; from the image-plane interior.  Intended to be used if the image-plane has
;;; been mutated while the draw area is active.

(def-substitution-macro set-draw-area-from-image-plane-interior (image-plane)
  (setq left-edge-of-draw-area (left-edge-of-workspace-area-in-window image-plane)
	top-edge-of-draw-area (top-edge-of-workspace-area-in-window image-plane)
	right-edge-of-draw-area (right-edge-of-workspace-area-in-window image-plane)
	bottom-edge-of-draw-area (bottom-edge-of-workspace-area-in-window image-plane)))



;;; `With-draw-area-of-image-plane-contents?' does just that.  This nests first
;;; into the enclosing pane, and then into the image-plane's contents.  It uses
;;; rectangle cached in the image-plane recording the content area, in window.
;;; Finally it establishes the transform for the content area.  This is just:
;;; with-nested-draw-area-of-pane, with-nested-draw-area? and
;;; with-image-plane-transform.

(defmacro with-nested-transform-and-draw-area-of-image-plane-contents?
    ((image-plane) &body body)
  `(with-nested-draw-area-of-pane? (,image-plane)
     (with-nested-draw-area?
	 ((left-edge-of-workspace-area-in-window ,image-plane)
	  (top-edge-of-workspace-area-in-window ,image-plane)
	  (right-edge-of-workspace-area-in-window ,image-plane)
	  (bottom-edge-of-workspace-area-in-window ,image-plane)
	  ,image-plane :interior)
       (with-image-plane-transform (,image-plane)
	 ,@body))))








;;; `With-magnification' rebinds the drawing-transform using x and y
;;; magnification and folds them into the current scaling.  The values maybe
;;; NIL, in which case nothing is done.

(defmacro with-magnification ((x-magnification? y-magnification?) &body body)
  `(let ((current-image-x-scale current-image-x-scale)
	 (current-image-y-scale current-image-y-scale))
     (let (magnification)
       (when (setf magnification ,x-magnification?)
	 (setf current-image-x-scale (magnify current-image-x-scale magnification)))
       (when (setf magnification ,y-magnification?)
	 (setf current-image-y-scale (magnify current-image-y-scale magnification))))
     ,@body))


;;; `With-cached-transform' creates a drawing transform from scratch.
;;; Presumably you give it one you computed previously and stored.  This is used
;;; most commonly to establish the transform for drawing on a particular
;;; image-plane.

(defmacro with-cached-transform ((frame-transform? x-scale y-scale x-origin y-origin) &body body)
  `(let ((current-frame-transform? ,frame-transform?)
	 (current-image-x-scale ,x-scale)
	 (current-image-y-scale ,y-scale)
	 (current-x-origin-of-drawing ,x-origin)
	 (current-y-origin-of-drawing ,y-origin))
     ,@body))



;;; `With-shifted-origin' rebinds the drawing transform so that drawing at the
;;; given point in the workspace will draw exactly at the given poin in the
;;; window.  This is useful when dragging a KB object attached to the mouse,
;;; prior to actually rebinding the location of the object.

(defmacro with-shifted-origin
	  ((x-in-workspace
	     y-in-workspace
	     x-in-window
	     y-in-window)
	   &body body)
  (avoiding-variable-capture (x-in-workspace y-in-workspace x-in-window y-in-window)
    `(let* ((current-x-origin-of-drawing
	      (-r current-x-origin-of-drawing
		  (delta-x-in-window
		    (-w ,x-in-workspace (x-in-workspace ,x-in-window))
		    current-image-x-scale)))
	    (current-y-origin-of-drawing
	      (-r current-y-origin-of-drawing
		  (delta-y-in-window
		    (-w ,y-in-workspace (y-in-workspace ,y-in-window))
		    current-image-y-scale))))
       ,@body)))






;;;; Reclaim Window For Workstation


;;; `Reclaim-window-for-workstation' is the reclaimer for the window-for-
;;; workstation slot in workstation structures.  It always expects as its
;;; value a gensym window.

;;; It also executes the following cleanup code: ...

;;; Note that currently, this is the only way in which gensym windows are
;;; reclaimed; they are always reclaimed when the corresponding workstation is
;;; reclaimed.  Thus, this function is not a general reclamation function for
;;; gensym windows and is therefore not called reclaim-gensym-window.

;;; The special variable dont-reclaim-corresponding-object?  is bound to t around
;;; the calls to reclaim-icp-object-map-for-gensym-window, and
;;; reclaim-cached-structures-for-window, and also
;;; reclaim-icp-object-map-for-workstation in reclaim-workstation.  This prevents
;;; messages from being sent to reclaim corresponding icp objects.  It is
;;; unnecessary to do this since the connection is being shutdown.  Reclamation of
;;; corresponding icp objects could be taken care of independently by the
;;; connection loss callback function for the remote ICP socket.  However, since
;;; the Telewindows process is just shut down, there is no need to do this.

(defun reclaim-window-for-workstation (gensym-window)
  (let ((current-window gensym-window)
    (delete-corresponding-object? nil)
    (workstation? (workstation-this-is-on gensym-window)))

    ;; Remove the associated workstation (if any) from the list
    ;; workstation-in-service (if present).
    (setq workstations-in-service (delq workstation? workstations-in-service))
    
    (reclaim-icp-object-map-for-gensym-window gensym-window)
    (reclaim-panes-in-window-if-g2 (panes-in-window gensym-window))
    (setf (panes-in-window gensym-window) nil)
    (reclaim-cached-structures-for-window gensym-window)
    (clear-all-image-renderings-for-window gensym-window)
    (hard-reclaim-all-reclaimed-stored-rasters gensym-window))

  ;; Mark the output port as invalid.  ICP takes care of reclaiming.
  (setf (icp-output-port-for-window? gensym-window) nil)

  ;; Mark as reclaimed.
  (setf (gensym-window-serial-number gensym-window) -1)

  ;; ok, now call internal reclaimer, which calls reclaimers for slots:
  (reclaim-gensym-window-internal gensym-window))


;; It is necessary to reclaim-panes-in-window before doing
;; reclaim-cached-structures-for-window because renderings (icon, graph)
;; exist in graphic element memory.  Thus, if the pane were reclaimed
;; via the usual mechanism (as part of reclaim-gensym-window-internal),
;; after reclaim-cached-structures-for-window, it would be encountering
;; reclaimed renderings in graphic element memory.

;; It is necessary to establish current-window so that when drawing schedules
;; are reclaimed they can decrement the count in the window.







;;;; Dynamic Extents for on-window-with-drawing




;;; Establishing the `on-window-with-drawing' dynamic extent provides sufficent
;;; context to allow drawing to the window.  Usage of this context is nothing
;;; but troubles: It may not be established recursivly, since ICP message groups
;;; can not nest.  The macro on-window-with-drawing is always used to establish
;;; this extent, that macro is lexically expensive (for example it inlines it's
;;; body multiple times), and dynamicly expensive (for example it sometimes must
;;; hide the cursor).

(def-named-dynamic-extent on-window-with-drawing
  (module windows1)
  (dynamic-superior on-window-without-drawing)
  (excluded-dynamic-superiors on-window-with-drawing))



;;; The macro `with-icp-window' must be wrapped around all attempts to send
;;; bytes to the given ICP window.  It allows for an unplanned close of the ICP
;;; connection, which sets the port to NIL.

(defmacro with-icp-window ((gensym-window) &body body)
  (avoiding-variable-capture (gensym-window &aux icp-output-port?)
    `(let ((,icp-output-port?
	      (icp-output-port-for-window? ,gensym-window)))
       (when (and ,icp-output-port?
		  (icp-connection-open-p
		    (parent-icp-socket ,icp-output-port?)))
	 (writing-icp-message-group (,icp-output-port?)
	   ,@body)))))

(defmacro with-icp-window-if-needed ((gensym-window) &body body)
  `(cond ((>f writing-icp-message-group 0)
	  ,@body)
	 (t
	  (with-icp-window (,gensym-window)
	    ,@body))))


;;; The function `workstation-dead-p' is true when the workstations's ICP
;;; connection, if any, has closed unexpectedly, and the workstation is waiting
;;; to be deleted.

(defun workstation-dead-p (workstation)
  (let ((gensym-window? (window-for-workstation workstation)))
    (and gensym-window?
	 (icp-window-p gensym-window?)
	 (null (icp-output-port-for-window? gensym-window?)))))




;;; `Get-gensym-window-parameter' returns the window parameter named parameter-name
;;; for gensym-window.  See the section entitled "Gensym Window Parameters" in
;;; module PLATFORMS.

(defun get-gensym-window-parameter (gensym-window parameter-name)
  (getfq-macro (window-parameters-plist gensym-window) parameter-name))


(defun set-gensym-window-parameter (gensym-window parameter-name new-value)
  (setf (window-parameters-plist gensym-window)
	(mutate-gensym-plist (window-parameters-plist gensym-window)
			     parameter-name
			     new-value)))

(defun get-system-metric (gensym-window index &optional default)
  (let ((system-metrics? (get-gensym-window-parameter gensym-window 'system-metrics)))
    (or (if (and system-metrics? (>=f index 0))
	    (nth index system-metrics?))
	default)))


;;; The functions `get/set-ui-property' manage another window plist used for
;;; global UI properties, such as the theme. Note that the set function takes
;;; ownership of the value.

(defun get-ui-property (gensym-window property &optional default)
  (getfq-macro (gensym-window-ui-properties gensym-window) property default))

(defun set-ui-property (gensym-window property %value)
  (setf (gensym-window-ui-properties gensym-window)
	(mutate-gensym-plist (gensym-window-ui-properties gensym-window)
			     property %value)))

(defun remove-ui-property (gensym-window property)
  (setf (gensym-window-ui-properties gensym-window)
	(remove-property-macro (gensym-window-ui-properties gensym-window)
			       property reclaim-gensym-cons)))


;;; The functions `maximum-window-width/height' return the maximum permitted
;;; size of the client area of a native window on the given TW, assuming default
;;; native framing and no scroll bars. If unknown, somewhat arbitrarily returns
;;; the size of the G2 window.

(defun maximum-window-width (gensym-window)
  (let ((cxmaxtrack? (get-system-metric gensym-window sm-cxmaxtrack))
	(cxframe? (get-system-metric gensym-window sm-cxframe)))
    (cond ((and cxmaxtrack? cxframe?)
	   (-f cxmaxtrack? (*f cxframe? 2)))
	  (t				; Should never need this default case.
	   (-f (right-edge-of-window gensym-window)
	       (left-edge-of-window gensym-window))))))

(defun maximum-window-height (gensym-window)
  (let ((cymaxtrack? (get-system-metric gensym-window sm-cymaxtrack))
	(cyframe? (get-system-metric gensym-window sm-cyframe))
	(cycaption? (get-system-metric gensym-window sm-cycaption)))
    (cond ((and cymaxtrack? cyframe? cycaption?)
	   (-f cymaxtrack? cycaption? (*f cyframe? 2)))
	  (t				; Should never need this default case.
	   (-f (bottom-edge-of-window gensym-window)
	       (top-edge-of-window gensym-window))))))


(def-icp-value-type-equivalence coordinate integer)	; usually unsigned!!!


;;; The function `dialog-units-to-pixels' converts Windows "dialog units" to
;;; pixels, assuming the default GUI font. Only 8.2a0 or later TW's send us the
;;; needed metrics, so we have a default taken from Win2K.

(defun dialog-units-to-pixels (gensym-window dialog-units axis)
  (case axis
    (x (roundf (*f dialog-units (get-system-metric gensym-window sm-cxdialog 150))
	       100))
    (y (roundf (*f dialog-units (get-system-metric gensym-window sm-cydialog 163))
	       100))))



(eval-when (:compile-toplevel :load-toplevel :execute)

(def-icp-message-type-code define-telewindows-workstation 28)
(def-icp-message-type-code set-position-of-mouse 29)
(def-icp-message-type-code set-window-protocol-version 22)
(def-icp-message-type-code request-to-refresh-window 90)
(def-icp-message-type-code request-to-reshape-window 91)
(def-icp-message-type-code request-to-reshape-native-window 92)
(def-icp-message-type-code shift-position-of-mouse 94)
(def-icp-message-type-code request-to-close-telewindows-connection 95)
(def-icp-message-type-code set-transfer-mode 96)
(def-icp-message-type-code set-background-color-value 97)


;; The message pair request-to-move-window and request-to-move-native-window (98
;; & 99) was introduced in G2/TW 7.1.  It's patterned after the message pair
;; request-to-reshape-window and request-to-reshape-native-window. The predicate
;; move-telewindow-supported-p is used on the TW side to see if the G2 knows
;; about it. (MHD 6/12/03)

(def-icp-message-type-code request-to-move-window 98)
(def-icp-message-type-code request-to-move-native-window 99)

; (def-icp-message-type-code telewindows-shutdown 93)  ; obsolete

)

;; 28 is assigned to define-telewindows-workstation in telestubs.
;; It should be moved back here eventually, but is included there
;; in order to patch release 1.11b!! (MHD 3/38/89)



;;; `Gensym window' is an icp object type ...

(def-icp-object-type gensym-window
		     (standard-icp-object-index-space
		       (corresponding-icp-object-map-for-window gensym-window))
  (let ((temporary-window-parameters-plist
	  (copy-tree-using-gensym-conses
	    (window-parameters-plist gensym-window))))
    ;; make a copy of this window's parameters plist, and substitute ICP-specific
    ;;   elements as necessary; recycle this tree after sending it across ICP
    (mutate-gensym-plist			; defined in ICP right now!
      temporary-window-parameters-plist 'type-of-gensym-window 'icp)

    ;; A bug fixed in the following two forms today: the wrong plist indicator
    ;; was given, causing the proper indicator (now shown) not to be changed to
    ;; ICP.  This bug was being masked by the apparent fact that no code
    ;; referred to this value (as it ended up in the gensym window) on the G2
    ;; side where it was wrong, i.e. the G2 side of the connection.  For what
    ;; it's worth, it's now all better.  (MHD 10/26/94)
    (mutate-gensym-plist
      temporary-window-parameters-plist 'scratchpad-raster-type-for-window 'icp)
    (mutate-gensym-plist
      temporary-window-parameters-plist 'stored-raster-type-for-window 'icp)
    

    ;; Add this property, OK?
;    (mutate-gensym-plist
;      temporary-window-parameters-plist 'default-image-palette
;      default-image-palette)

;    (setf (icp-socket-window current-icp-socket) gensym-window) ; OBSOLETE! (MHD 8/8/02)
    
    (send-icp-define-gensym-window
      corresponding-icp-object-index
      (left-edge-of-window gensym-window)
      (top-edge-of-window gensym-window)
      (right-edge-of-window gensym-window)
      (bottom-edge-of-window gensym-window)
      temporary-window-parameters-plist
      (icp-object-index-for-window-on-other-side? gensym-window))
    
    (reclaim-gensym-tree temporary-window-parameters-plist)))



;;; `Define-gensym-window' ...

;;; Left-edge-in-window, top-edge-in-window, right-edge-in-window, and
;;; bottom-edge-in-window, specify the edges of the gensym window (in the
;;; window coordinate system).

(def-icp-message-type define-gensym-window
		      (corresponding-icp-object-index
			(coordinate left-edge-in-window)
			(coordinate top-edge-in-window)
			(coordinate right-edge-in-window)
			(coordinate bottom-edge-in-window)
			(list window-parameters-plist)
			(unsigned-integer?
			  corresponding-icp-object-index-on-other-side?))
  (store-corresponding-icp-object
    corresponding-icp-object-index
    (if corresponding-icp-object-index-on-other-side?
	(prog1 (get-gensym-window-from-icp-port	; abstract? ?? ???
		 (icp-output-port current-icp-socket)
		 corresponding-icp-object-index-on-other-side?)
	  (reclaim-gensym-tree-with-text-strings window-parameters-plist))
	(let ((gensym-window
		(make-or-revise-window
		  nil          
		  left-edge-in-window
		  top-edge-in-window
		  right-edge-in-window	
		  bottom-edge-in-window
		  nil				; native-window?          
		  nil				; raster-for-native-window?          
		  window-parameters-plist)))
;	  (setf (icp-socket-window current-icp-socket) ; OBSOLETE! (MHD 8/8/02)
;		gensym-window)
	  (setf (icp-output-port-for-window? gensym-window)
		(icp-output-port current-icp-socket))
	  (setf (icp-object-index-for-window-on-other-side? gensym-window)
		corresponding-icp-object-index)
	  (obtain-max-window-protocol gensym-window)
	  (establish-telewindows-license-level gensym-window)
	  (multiple-value-bind (major-version minor-version)
	      (decode-icp-window-protocol-version
		(getf window-parameters-plist 'icp-window-protocol-version))
	    (maybe-update-remote-icp-version-info-for-version
	      current-icp-socket major-version minor-version))
	  gensym-window))))

;; Instead of the icp-object-index-for-window-on-other-side? slot in a gensym window,
;; it would be better to store this information in the corresponding-icp-object-map-
;; for-window, under the icp input port!



;;; `decode-icp-window-protocol-version' returns two
;;; values, major revision and minor revision.

;; The following numbers are one less than what is actually sent.
;;icp-window-protocol-supports-remote-executables (195) 12 1996/10/8 4.1r0
;;icp-window-protocol-supports-slavic-font (189) 10 4.0R0

(defun decode-icp-window-protocol-version (icp-window-protocol-version)
  (case icp-window-protocol-version
    ((3)
     (values 3 1))
    ((4 5 6 7 8 9 10 11)
     (values 4 0))
    ((12 13)
     (values 4 1))
    (t
     (if icp-window-protocol-version
	 (values 5 0) ; this case doesn't matter, our caller won't care
	 (values 3 0)))))






;;;; Graphics flushing and syncing



#+development
(defvar trace-xsync nil)


;; Local (native) window versions.

(defun sync-graphics-on-native-window (native-window?)
  (when native-window?
    (current-system-case
      (ab			; AB
	(sync-graphics-on-native-window-maybe-with-tracing native-window?))
      ((telewindows)
	(sync-graphics-on-native-window-1 native-window?))))
  nil)

(defun-void sync-graphics-on-native-window-1 (native-window)
  #+development
  (when trace-xsync
    (trace-time "----------------------------Sync----------------------------------"))
  (c-x11-sync native-window))


(defun flush-graphics-on-native-window (native-window?)
  (when native-window?
    #+development
    (when trace-xsync
      (trace-time "----------------------------Flush----------------------------------"))
    (c-x11-flush native-window?))
  nil)


;;; The icp-message-type `force-graphics-on-window' tells a telewindow
;;; to either sync or fluch graphics.

(def-icp-value-type-equivalence flush-or-sync unsigned-integer)

(def-icp-message-functions force-graphics-on-window (flush-or-sync)
  (case type-of-current-window
    (x11-window
     (case flush-or-sync
       (0 (flush-graphics-on-native-window current-native-window?))
       (1 (sync-graphics-on-native-window current-native-window?))))))



;;; The function `flush-graphics-on-current-window' flushes drawing operations
;;; buffered by ICP or by the local window system.  For a local window, we call
;;; the native flush function.. For an ICP window, we have to send a new ICP
;;; message;

(defun flush-graphics-on-current-window ()
  (force-graphics-on-window 1))




;;; The function `sync-graphics-current-window' is similar, but syncs rather
;;; than flushes.  Sync means to flush and wait for the window server to finish
;;; all of the drawing.

(defun sync-graphics-on-current-window ()
  (force-graphics-on-window 1))





;;;; Identified Drawing Activity

;;; An identified-drawing-activity is a tuple stored in the gensym-window
;;; consiting of an integer ID, and a pending-activity.  They represent
;;; some amount of drawing that is in progress for which it was desirable
;;; to maintain a unique identifier.  Two examples follow.

;;; An identified drawing activity is started when ever a ping-drawing message
;;; is sent and finished when the ping-drawing-reply is returned.

;;; An identified drawing activity is started when ever we wish to know when
;;; a batch of drawing is finished.  The activity is created, and then pending
;;; activities are created in each drawing Q effected by the batch.  When
;;; these all finish (via the ping-drawing-mechinism) the root activity will
;;; finish.

(def-structure (identified-drawing-activity
		 (:include pending-activity)
		 (:reclaimer reclaim-identified-drawing-activity-1)
		 (:constructor
		   make-identified-drawing-activity-1
		   (gensym-window-of-identified-drawing-activity
		     id-of-identified-drawing-activity
		     parent-of-pending-activity?
		     name-of-pending-activity
		     continuation-of-pending-activity?
		     arg-of-identified-drawing-activity)))
  gensym-window-of-identified-drawing-activity
  id-of-identified-drawing-activity
  arg-of-identified-drawing-activity)

(defun make-identified-drawing-activity
    (gensym-window-of-identified-drawing-activity
      id-of-identified-drawing-activity
      parent-of-pending-activity?
      name-of-pending-activity
      continuation-of-pending-activity?
      arg-of-identified-drawing-activity)
  (let ((identified-drawing-activity
	  (make-identified-drawing-activity-1
	    gensym-window-of-identified-drawing-activity
	    id-of-identified-drawing-activity
	    parent-of-pending-activity?
	    name-of-pending-activity
	    continuation-of-pending-activity?
	    arg-of-identified-drawing-activity)))
    (when parent-of-pending-activity?
      (block-pending-activity parent-of-pending-activity?
			      identified-drawing-activity))
    identified-drawing-activity))





(defun start-identified-drawing-activity
    (gensym-window parent? continuation-function
		   &optional arg1)
  (let* ((fresh-id
	   (+f 1 (loop with max = 0 finally (return max)
		       for x in (identified-drawing-activities-of-gensym-window
				  gensym-window)
		       for id = (id-of-identified-drawing-activity x)
		       if (<f max id) do (setf max id))))
	 (identified-drawing-activity
	   (make-identified-drawing-activity
	     gensym-window
	     fresh-id
	     parent?
	     'continue-after-drawing
	     continuation-function
	     arg1)))
    (gensym-push
      identified-drawing-activity
      (identified-drawing-activities-of-gensym-window gensym-window))
    identified-drawing-activity))

(defun find-identified-drawing-activity (gensym-window id)
  (loop
    for tuple in (identified-drawing-activities-of-gensym-window gensym-window)
    when (=f id
	     (id-of-identified-drawing-activity tuple))
      do (return tuple)))


;;; `Remove-identified-drawing-activity' must be called from the continuation
;;; for an identified drawing activity.  It removes it from the window.  Of
;;; course it could be the continuation when the only function of the activity
;;; is to block some parent activity.

(defun-void remove-identified-drawing-activity
    (identified-drawing-activity kind-of-continuation)
  (case kind-of-continuation
    ((:finished :canceled)
     (let* ((gensym-window
	      (gensym-window-of-identified-drawing-activity
		identified-drawing-activity)))
       (setf
	 (identified-drawing-activities-of-gensym-window gensym-window)
	 (delete-gensym-element
	   identified-drawing-activity
	   (identified-drawing-activities-of-gensym-window gensym-window)))))
    #+development
    (t (error "error #3009124927"))))







;;;; Ping Drawing


;;; `Identified-drawing-activity-id' are the values found in
;;; the identified-drawing-activity structures.

(def-icp-value-type-equivalence id-of-identified-drawing-activity unsigned-integer)



;;; `Ping-drawing' is sent from G2 to the client's drawing process.  That
;;; process must then do a synch, i.e. force all it's Q's.  It then should
;;; reply to G2 to indicate it's done via the ping-drawing-reply.

(def-icp-message-functions ping-drawing (id-of-identified-drawing-activity)
  (case type-of-current-window
    (x11-window
     (sync-graphics-on-native-window current-native-window?)
     (if (slave-gensym-window? current-window)
	 (send-ping-drawing-reply
	   current-window id-of-identified-drawing-activity)
	 (handle-ping-drawing-reply-1
	   current-window id-of-identified-drawing-activity)))))


(defun-allowing-unwind send-ping-drawing-reply
    (gensym-window id-of-identified-drawing-activity)
  (writing-icp-message-group
      ((icp-output-port-to-master-for-window? gensym-window))
    (send-icp-ping-drawing-reply gensym-window id-of-identified-drawing-activity)))




;;; `Ping-drawing-reply' is sent from the client's drawing process to G2
;;; in response to a ping-drawing message.  It then looks up the identified
;;; drawing activity and finishs it.  It does not presume that the task
;;; will exist since it may have been torn down after the request was
;;; sent off to the client.

(def-icp-message-type ping-drawing-reply
    (gensym-window id-of-identified-drawing-activity)
  (handle-ping-drawing-reply-1 gensym-window id-of-identified-drawing-activity))

(defun handle-ping-drawing-reply-1 (gensym-window id-of-identified-drawing-activity)
  (let ((identified-drawing-activity?
	  (find-identified-drawing-activity
	    gensym-window
	    id-of-identified-drawing-activity)))
    (when identified-drawing-activity?
      (finish-pending-activity identified-drawing-activity?))))







;;;; Macros for On Window With and Without Drawing




;;; `on-window-without-drawing' establishs the dynamic extent on-window-without-drawing
;;; it assumes that a draw area has already been established.  It is a precondition
;;; of on-window-with-drawing.  See the documenation above for this dynamic extent.

(defmacro on-window-without-drawing ((gensym-window) &body body)
  `(with-named-dynamic-extent* on-window-without-drawing
       ((current-window ,gensym-window)
	(drawing-on-window nil)
	(current-drawing-transfer-mode
	  (if (xor-mode-p)				    ; Curious.
	      current-drawing-transfer-mode
	      (drawing-transfer-mode-of-gensym-window current-window)))
	(type-of-current-window
	  (type-of-gensym-window current-window))
	(current-native-window?
	  (native-window? current-window))
	(current-color-map
	  (color-map-for-window current-window))
	(current-background-color-value
	  (color-value-for-white))
	(current-foreground-color-value
	  (color-value-for-black)))
     ,@body))


(defun icp-socket-number-of-outstanding-bytes (icp-socket)
  (if (i-am-alive-info? icp-socket)
      (number-of-outstanding-icp-bytes
	(i-am-alive-info? icp-socket))
      -1))



;;; The defvar `flush-graphics-immediately?', when bound to T, restores the 3.0
;;; behavior of flushing graphics after each on-window-with-drawing.

(defvar flush-graphics-immediately? nil)

;; Actually, 3.0 did a Sync here, rather than a Flush.  But that was much too
;; expensive.




;;; The macro `on-window-with-drawing' executes body with gensym-window
;;; established as the `current window'.  on-window-with-drawing must be used
;;; to enclose any code that updates or copies from the contents of
;;; gensym-window.  on-window-with-drawing ensures that there is `access' to
;;; the update area of gensym-window during the execution of body.  Also, if
;;; gensym-window is on a screen, on-window-with-drawing ensures that no part
;;; of a mouse cursor is drawn in the update area of the current window during
;;; the execution of body.

;;; The body of on-window-with-drawing returns only a single value.

;;; The body appears multiple times in the expansion.  The function
;;; update-window is the prefered interface for to this routine in most cases.

;;; When the window's type is ICP, and the ICP connection is clogged, the
;;; body is not executed!  Note that the i-am-alive mechanism will do something
;;; when the channel is unclogged, see `i-am-alive-info'.

(defmacro on-window-with-drawing ((gensym-window) &body body)
  #-development (declare (ignore gensym-window))
  `(let ((defer-notifications? t))
     #+development
     (unless (eq ,gensym-window current-window)
       (error "attempting to get with-drawing for other than current-window"))
     (with-named-dynamic-extent* on-window-with-drawing
	 ((drawing-on-window t))
       (case type-of-current-window
	 (x11-window
	  (prog1 (progn ,@body)
	    (when flush-graphics-immediately?
	      (sync-graphics-on-current-window))))

	 (icp
	  (let* ((icp-output-port?
		   (icp-output-port-for-window? current-window))
		 (icp-socket?
		   (and icp-output-port?
			(parent-icp-socket icp-output-port?))))

	    #+development
	    (when (and icp-socket?
		       (null (icp-connection-unclogged-for-socket? icp-socket?)))
	      (dwarn "ICP socket ~s clogged with ~d bytes. Ignoring window-update!!"
		     icp-socket?
		     (icp-socket-number-of-outstanding-bytes icp-socket?)))

	    (when (and icp-socket?
		       (icp-connection-unclogged-for-socket? icp-socket?))
	      (with-icp-window (current-window)
		(synchronize-icp-on-window-with-drawing
		  current-window
		  left-edge-of-draw-area top-edge-of-draw-area
		  right-edge-of-draw-area bottom-edge-of-draw-area)
		(prog1 (progn ,@body)
		  (when (and flush-graphics-immediately?
			     (/=f (icp-connection-state current-icp-socket) icp-connection-closed))
		    (sync-graphics-on-current-window)))))))

	 (printer
	  ,@body)

	 #+development
	 (t
	  (warn "Unknown window type ~s in on-window-with-drawing"
		type-of-current-window))))))

(defun synchronize-icp-on-window-with-drawing (current-window
					       left-edge-of-draw-area top-edge-of-draw-area
					       right-edge-of-draw-area bottom-edge-of-draw-area)  
  (setf (window-remote-drawing-not-synchronized-p current-window) t)
  (setf (window-remote-background-color current-window) 'unknown)
  
  (setf (window-desired-left-edge-of-draw-area current-window) left-edge-of-draw-area)
  (setf (window-desired-top-edge-of-draw-area current-window) top-edge-of-draw-area)
  (setf (window-desired-right-edge-of-draw-area current-window) right-edge-of-draw-area)
  (setf (window-desired-bottom-edge-of-draw-area current-window) bottom-edge-of-draw-area)

  (let ((icp-supports-transparent-copy-p
	 (and (eql (type-of-gensym-window current-window) 'icp)
	      (current-window-supports-this-icp-window-protocol-p
	       icp-window-protocol-supports-transparent-copy))))
    (setf (window-desired-transfer-mode current-window)
	  (if icp-supports-transparent-copy-p
	      (if (eq :xor current-drawing-transfer-mode) 0 1)
	      'none))
    (setf (window-desired-background-color current-window)
	  (if icp-supports-transparent-copy-p
	      current-background-color-value
	      'none))))

;;; The function `icp-message-functions-icp-prologue' is run for all icp message
;;; types defined via def-icp-message-functions.  This must be called within an
;;; on-window-with-drawing context.  In particular, this refers to
;;; current-window, which must be appropriately bound.

(defun-void icp-message-functions-icp-prologue (message-name)
  (declare (ignore message-name))
  (assert-that-within-named-dynamic-extent 'on-window-with-drawing)  
  (when (window-remote-drawing-not-synchronized-p current-window)
    (setf (window-remote-drawing-not-synchronized-p current-window) nil)
    (icp-prologue-send-begin-window-update current-window)
    (icp-prologue-set-transfer-mode current-window))
  (icp-prologue-set-background-color-value current-window))



(defun-void icp-prologue-send-begin-window-update (window)
  (send-icp-begin-window-update
   window
   (window-desired-left-edge-of-draw-area window)
   (window-desired-top-edge-of-draw-area window)
   (window-desired-right-edge-of-draw-area window)
   (window-desired-bottom-edge-of-draw-area window)))

(defun-void icp-prologue-set-transfer-mode (window)
  (let ((desired-transfer-mode (window-desired-transfer-mode window)))
    (unless (eq desired-transfer-mode 'none)
      (send-icp-set-transfer-mode desired-transfer-mode))))

(defun-void icp-prologue-set-background-color-value (window)
  (let ((desired (window-desired-background-color window)))
    (unless (or (eq desired 'none)
		(eq desired (window-remote-background-color window)))
      (setf (window-remote-background-color window) desired)
      (send-icp-set-background-color-value desired))))

;;; `With-transfer-mode-when-drawing' is used within an on-window-with-drawing
;;; extent to establish a dynamic extent during which the transfer mode has
;;; been changed.  This must be used to keep the remote telewindows in synch.
;;; This form returns no values, and must not be unwinded thru.

(defmacro with-transfer-mode-when-drawing ((transfer-mode) &body body)
  (avoiding-variable-capture (transfer-mode)
    `(let ((already-in-synch (eql current-drawing-transfer-mode ,transfer-mode)))
       (unwind-protect-for-development with-transfer-mode-on-window-with-drawing
	   (let ((current-drawing-transfer-mode current-drawing-transfer-mode))
	     (unless already-in-synch
	       (setf current-drawing-transfer-mode ,transfer-mode)
	       (synchronize-transfer-mode))
	     ,@body)
	 (unless already-in-synch
	   (synchronize-transfer-mode))))))

;; Synchronize-transfer-mode is now a no-op when not drawing, so this macro
;; actually works in both cases.


(defmacro with-paint-mode (() &body body)
  `(with-transfer-mode-when-drawing (:paint-infered-from-xor)
     ,@body))


(defmacro with-xor-mode (() &body body)
  `(with-transfer-mode-when-drawing (:xor)
     ,@body))



;;; `Synchronize-transfer-mode' notifies the connected Telewindows what
;;; transfer mode we are currently using.  It is rarely called directly, the
;;; routine with-transfer-mode-on-window-with-drawing, is the prefered
;;; interface.

(defun synchronize-transfer-mode ()
  (when (and (within-window-drawing-context-p)		    ; Added. -fmw, 6/22/95
	     (eql type-of-current-window 'icp)
	     (current-window-supports-this-icp-window-protocol-p
	       icp-window-protocol-supports-transparent-copy))
    (setf (window-desired-transfer-mode current-window)
	  (if (eq :xor current-drawing-transfer-mode) 0 1))
    (send-icp-set-transfer-mode
      ;; Another bit in the transfer mode to indicate immediate flushing?
      (if (eq :xor current-drawing-transfer-mode) 0 1))))



;;; `With-background-color-value' is used by on-window-with-drawing to
;;; establish a binding for the current color value and if necessary to keep a
;;; remote window in synch.  It is ok to rebind the background color in the
;;; dynamic extent of this macro via set-background-color-value.

(defmacro with-background-color-value (color-value &body body)
  (avoiding-variable-capture (color-value)
    `(let ((old-color-value current-background-color-value))
       (let ((current-background-color-value current-background-color-value))
	 (unwind-protect-for-development with-background-color-value-on-window-with-drawing
	     (progn
	       (set-current-background-color-value ,color-value)
	       ,@body)
	   (set-current-background-color-value old-color-value))))))

(defun synchronize-background-color-value ()
  (when (and (eql type-of-current-window 'icp)
	     (current-window-supports-this-icp-window-protocol-p
	      icp-window-protocol-supports-transparent-copy))
    (setf (window-desired-background-color current-window) current-background-color-value)))

(defun set-current-background-color-value (new-color-value)
  (unless (=f current-background-color-value new-color-value)
    (setf current-background-color-value new-color-value)
    (synchronize-background-color-value)))











;;;; Colors



;;; A `color' is a symbol (e.g. RED, WHITE, etc.).  Gensym software provides a
;;; standard suite of colors.  Right now, the set of colors corresponds to the
;;; X Windows standard Color Database, which provides a diverse and industry-
;;; standard selection of colors.  However, no software particularly depends on
;;; this fact, and it would be desirable in the future to allow users to define
;;; their own colors. 

;;; A `color value' is a pixel value, an unsigned integer that represents a
;;; color in a screen image in memory.  Thus, color values are display-monitor-
;;; specific.  Each distinct color (gray and grey are not different) should
;;; ideally have a distinct color value.  And each distinct color value should
;;; ideally have a distinct appearance on all display monitors (insofar as
;;; colors are available).

;;; A `color difference' is an integer that represents the difference between
;;; two color values, where zero represents a non-difference.  `Adding' a
;;; color difference to a color value means combining the color value and
;;; color difference in a way that can be reversed by `subtracting' that same
;;; color difference, as abstracted by the operation +color-difference.
;;; Ideally, the combining operation is addition mod the-number-of-color-values,
;;; in which case the corresponding subtraction can be used for erasing.  If
;;; addition cannot be used, bit-wise exclusive-or (logxor) may be used.  (Note
;;; that when there is one bit per pixel, addition, subtraction, and logxor are
;;; all equivalent.)

;;; `Color arithmetic' refers to color addition and subtraction operations with
;;; color values and color differences.

;;; A `false color' is the result of adding to or subtracting from a color value
;;; an unrelated color difference.  False colors arise in G2 in two situations:
;;;
;;;    (1) in highlighting, where a graphic element (e.g., text in a highlighted
;;;        text box or cell or in a highlight bar) could be rendered in its true
;;;        color only at the expense of some "snappiness" of the graphics; and
;;;
;;;    (2) in "uncontrolled" superposition of graphic objects (e.g., an object
;;;        being dragged across a workspace, or an outline of a workspace that
;;;        is being moved, or two overlapping objects on a workspace that might
;;;        later be moved apart), where true colors could be shown only if one
;;;        object were to occlude the other, which is too computationally
;;;        expensive, in general.
;;;
;;; Distinct color values should ideally have distinct false colors, when the same
;;; color difference is added to, or subtracted from, them.

;;; To support false colors, it is best to have 2^n distinct color values.

;; Note: Revise the above.  Talk about unpredictability of false colors, etc!






;; standard-gensym-color-alist was moved to platfoms.  -pto 26aug90


;; On California, Gensym's Sun 3, the X color database file is
;; /usr/lib/X11/rgb.txt.

;; Color value vectors are used only locally in this module.

;; Prior to 2.0, the standard colors were white, red, orange, yellow, green, blue,
;; purple, black, and brown.  Aquamarine and various grays were used for the title
;; block and pane background.  Light-gray, gray, and dark-gray were introduced in
;; the beta1 version of 2.0.



;;; The substitution-macro `intensity-of-color' computes the intensity or
;;; equivalent gray-scale brightness of a color, according to a formula given
;;; in the Xlib Programming Manual, section 7.7.1.

(def-substitution-macro intensity-of-color (red green blue)
  (floorf-positive					    ; Roundf is very slow in Chestnut.
    (+f (*f 30 red)
	(*f 59 green)
	(*f 11 blue))
    100))



;;; The `color-value-vector-index-and-intensity' property of a symbol is of the form
;;;
;;;    (color-value-vector-index . color-intensity),
;;;
;;; where the color intensity is computed by a formula given in the Xlib Programming
;;; Manual, section 7.7.1. 

(def-global-property-name color-value-vector-index-and-intensity)

(def-global-property-name new-pastel-color?)

(defun derive-standard-gensym-color-data ()
  (loop for (color r g b alternative-name?
		   nil
		   new-pastel-color?)			    ; NEW. For 3.1. Colors under
							    ;  review! (MHD 12/17/92)
	    in standard-gensym-color-alist
	as color-value-vector-index from 0
	as color-value-vector-index-and-intensity = (cons color-value-vector-index
							  (intensity-of-color r g b))
	do
    (setf (new-pastel-color? color) new-pastel-color?)

    ;; Set this property last, so that it's at the head of the plist.
    (setf (color-value-vector-index-and-intensity color)
	  color-value-vector-index-and-intensity)
    (when alternative-name?
      (setf (color-value-vector-index-and-intensity alternative-name?)
	    color-value-vector-index-and-intensity))))

(derive-standard-gensym-color-data)







;;; `hue-saturation-value' takes three 8 bit values:  red, green, and blue.  It
;;; returns a number corresponding to a weighted value of hue saturation value and
;;; the saturation value.

(defmacro factor-and-add (factum factor addum)
  `(+f (*f ,factum ,factor) ,addum))

;SS_ERROR
#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter saturation-limit 100)
(defparameter hue-limit 600)
)

(defun hue-saturation-value (red green blue)
  (declare (type fixnum red green blue))
  (let* ((maximum (maxf red green blue))
	 (minimum (minf red green blue))	; [0, 255]
	 (max-less-min (-f maximum minimum))
	 (saturation				; [0, 99]
	   (if (/=f maximum 0)
	       (roundf (*f #.saturation-limit max-less-min)
		       maximum)
	       0))
	 (hue 0))
    (setq hue					; [0, 599]
	  (if (=f saturation 0)
	      0
	      (let* ((red-distance
		       (roundf (*f #.(round hue-limit 6) (-f maximum red))
			       max-less-min))
		     (green-distance
		       (roundf (*f #.(round hue-limit 6) (-f maximum green))
			       max-less-min))
		     (blue-distance
		       (roundf (*f #.(round hue-limit 6) (-f maximum blue))
			       max-less-min)))
		(cond
		  ((=f red maximum)
		   (-f blue-distance green-distance))
		  ((=f green maximum)
		   (+f #.(round hue-limit 3)
		       (-f red-distance blue-distance)))
		  (t				; (=f blue maximum)
		   (+f #.(* (round hue-limit 3) 2)
		       (-f green-distance red-distance)))))))
    (if (<f hue 0) (setq hue (+f hue #.hue-limit)))	; modulo
    (let* ((result
	     (factor-and-add 
	       (factor-and-add
		 hue #.saturation-limit saturation) 256 maximum)))
      #-development
      result
      #+development 
      (values result hue saturation maximum))))




#+development
(defun hsv-of-color (color)
  (multiple-value-bind (red? green? blue?)
      (rgb-from-color color)
    (when red?
      (hue-saturation-value red? green? blue?))))


#+development
(defun hue (color)
  (multiple-value-bind (red? green? blue?)
      (rgb-from-color color)
    (when red?
      (multiple-value-bind (weight hue saturation value)
	  (hue-saturation-value red? green? blue?)
	weight hue saturation value
	hue))))

#+development
(defun saturation (color)
  (multiple-value-bind (red? green? blue?)
      (rgb-from-color color)
    (when red?
      (multiple-value-bind (weight hue saturation value)
	  (hue-saturation-value red? green? blue?)
	weight hue saturation value
	saturation))))






;;; `Hue-less-p' takes two colors and returns t if the first color has a hue
;;; "less than" the second.  Otherwise, nil is returned.

(defun hue-less-p (color-1 color-2)
  (multiple-value-bind (red-1? green-1? blue-1?)
      (rgb-from-color color-1)
    (if red-1?
	(multiple-value-bind (red-2? green-2? blue-2?)
	    (rgb-from-color color-2)
	  (if red-2?
	      (<f (hue-saturation-value red-1? green-1? blue-1?)
		  (hue-saturation-value red-2? green-2? blue-2?))
	      nil))
	nil)))

#+development
(defun hsv (color)
  (multiple-value-bind (red? green? blue?)
      (rgb-from-color color)
    (when red?
      (multiple-value-bind (weight hue saturation value)
	  (hue-saturation-value red? green? blue?)
	(format t "~%~20a:(~3@a:~3@a:~3@a) ~9@a: ~4@a : ~3@a : ~3@a"
		color
		red? green? blue?
		weight hue saturation value)))))

#+development
(defun hsvs (list-of-colors)
  (loop for color in list-of-colors
	do (hsv color)))

#+development
(defun hues (list-of-colors)
  (loop for color in list-of-colors
	do (format t "~%~20a:~7@a" color (hue color))))





;;; `Compute-standard-gensym-colors' ... Ordering? defaults to INTENSITY.  It
;;; can also be ALPHABETIC or HUE.

(defun compute-standard-gensym-colors (for-color-menu? &optional ordering?)
  (let ((colors-with-hue-numbers
	  (loop for (color r g b alternative-name?)
		    in standard-gensym-color-alist
		as hue-number
		   = (+f (*f 4 r)		; formula for hue number; FIX!
			 (*f 2 g)
			 (*f 1 b))
		collect (gensym-cons color hue-number)
			using gensym-cons
		when (and alternative-name? (not for-color-menu?))
		  collect (gensym-cons alternative-name? hue-number)
			using gensym-cons)))
    (setq colors-with-hue-numbers
	  (case ordering?
	    ((nil intensity)
	     (sort colors-with-hue-numbers #'< :key #'cdr))
	    (alphabetic
	     (sort colors-with-hue-numbers #'string-lessp :key #'car))
	    (hue
	     (sort colors-with-hue-numbers #'hue-less-p :key #'car))))
    (prog1
      (loop for (color) in colors-with-hue-numbers
	    collect color using gensym-cons)
      (reclaim-gensym-tree colors-with-hue-numbers))))

;; Have black, white, red, blue, and other common colors come out first!



;;; The variable `all-metacolors' is a list of all of the metacolors in G2.
;;;
;;; `All-colors' is a list of all of the colors in G2.  Colors sometimes have
;;; alternate names, e.g., "grey" is an alternate name for "gray".  "Gray" may
;;; be called a `standard color name', where grey is an `alternate color name'.
;;; This list includes both the standard and alternate names.
;;;
;;; Both of these lists never change within a G2 process, and are the same
;;; from one G2 to the next.  That is, they don't change dynamically, 
;;; they aren't platform-specific, and new ones cannot be defined.
;; Then why are they system variables?
;;;
;;; New colors (or metacolors) could be added between releases.  New colors
;;; have in fact been added for 4.0 -- a set of light ("pastel") colors.
;;;
;;; Once a color is defined, it can never be taken away, since user code may
;;; depend on it.  A color that is not in all-colors should never be passed to
;;; map-to-color-value or map-color-or-metacolor-to-color-value.  A metacolor
;;; that is not in all-metacolors should never be passed in to
;;; map-color-or-metacolor-to-color-value.

;;; `Menu-colors' contains the set of standard color names found in all-colors
;;; as a list sorted by intensity.
;;;
;;; `Menu-colors-sorted-alphabetically' contains the set of standard color names
;;; found in all-colors as a list sorted by intensity.
;;;
;;; `Menu-colors-sorted-by-hue' contains the set of standard color names found
;;; in all-colors as a list sorted by intensity.

(defparameter all-metacolors '(transparent foreground))
;; Update gensym-metacolor-p if you change this.

(def-system-variable all-colors windows1
  (:funcall compute-standard-gensym-colors nil))

(def-system-variable menu-colors windows1	; sorted by intensity
  (:funcall compute-standard-gensym-colors t))

(def-system-variable menu-colors-sorted-alphabetically windows1
  (:funcall compute-standard-gensym-colors t alphabetic))

(def-system-variable menu-colors-sorted-by-hue windows1
  (:funcall compute-standard-gensym-colors t hue))

;; All-colors and all-metacolors are referred to in ENTITIES, FACILITIES,
;; and GRAMMAR1.
;;
;; See, and review, color-or-metacolor-p and relevant calls to
;; semi-open-category-p; they are also used giving our UI to colors.  They need
;; better doc.  This should be less spread out! (MHD 5/20/94)




;;; A `color map' is a structure used for mapping colors into color values.

(def-structure (color-map
		 (:constructor
		   make-color-map-structure
		   (color-map-true-color-p color-value-plist color-value-vector
		    color-value-for-black? color-value-for-white?)))
  color-map-true-color-p

  (color-value-plist				; a gensym list
    nil :reclaimer reclaim-gensym-list)

  (color-value-vector
    nil :reclaimer reclaim-managed-array)

  color-value-for-black?
  color-value-for-white?

  color-map-last-color?					    ; Caches the last lookup, for speed
  color-map-last-color-value?)

;; The color-value-for-black? and color-value-for-white? slots are redundant.  They
;; are intended to make map-to-color-value a little faster, on the average.

;; Color-value-for-{black,white}? shouldn't be ? variables, but proving that all
;; color-description-plist contain an entry for black and white is left for
;; another day.  - ben 7/12/93



;;; `Make-color-map' makes a color map...

;;; A `color description plist' is of the form (color (color-value . whatever) ...).
;;; See make-window-parameters-plist in module PLATFORMS for standard color
;;; description plists.

(defun make-color-map (screen-depth color-description-plist)
  (loop with color-value-vector
	  = (allocate-managed-array (length standard-gensym-color-alist))
	with color-value-for-black? = nil
	with color-value-for-white? = nil
	as (color (color-value)) on color-description-plist by 'cddr
	as color-value-vector-index-and-intensity?
	   = (color-value-vector-index-and-intensity color)
	when color-value-vector-index-and-intensity?
	  do (setf (managed-svref
		     color-value-vector
		     (car color-value-vector-index-and-intensity?))
		   color-value)
	     (case color
	       (black (setq color-value-for-black? color-value))
	       (white (setq color-value-for-white? color-value)))
	when (null color-value-vector-index-and-intensity?)
	  nconc (gensym-list color color-value)
	    into color-value-plist
	finally
	  (return
	    (make-color-map-structure
	      (if (>=f screen-depth 16) t nil) ; true-color-p
	      color-value-plist color-value-vector
	      color-value-for-black? color-value-for-white?))))

;; Consider adding RGB values, etc. to color descriptions.



;;; `Reclaim-color-map-if-any' is the reclaimer for the color-map-for-window
;;; slot of gensym windows.  Color-map-for-window should be either a color
;;; map structure or nil.

(defun reclaim-color-map-if-any (color-map-for-window)
  (if color-map-for-window
      (reclaim-color-map color-map-for-window)))

;; Get rid of the nil case?



;; This is a start on a kb facility for defining colors!

;; `Define-color-for-kb' ...

;(defun define-color-for-kb (color r g b)
;  (unless (memq color all-colors)
;    (setq all-colors (gensym-cons color all-colors))
;    (loop for workstation in workstations-in-service
;	  as gensym-window = (window-for-workstation workstation)
;	  do (define-color-for-window gensym-window color r g b))
;    (setq menu-colors (nconc menu-colors (gensym-list color)))
;    (add-to-directory-of-names color 'color)))	; is this directory going to be used?

;; `Define-color-for-window' ...

;; When gensym-window is a Telewindows window, the color definition is conveyed to the
;; Telewindows server incrementally by means of a define-or-undefine-color-for-kb
;; message, with the Telewindows server returning a corresponding color description.

;; Whenever a Telewindows link is established or re-established, this should be called
;; for all colors previously defined for the kb.

;(defun define-color-for-window (gensym-window color r g b)
;  (let ((color-map-for-window (color-map-for-window gensym-window)))
;     (setf (color-value-plist color-map-for-window)
;	    (gensym-cons
;	      color
;	      (genysm-cons
;		0				; GET COLOR VALUE!
;		(color-value-plist color-map-for-window))))))

;; When a kb is released, its colors should be undefined for all Telewindows!  This
;; must be done carefully when more than one kb exists in a G2 process.



(def-substitution-macro gensym-metacolor-p (color)
  (memq-p-macro color '(foreground background transparent)))
  
(def-substitution-macro gensym-color-p (color)
  (or (gensym-metacolor-p color)
      (color-value-vector-index-and-intensity color)
      (rgb-color-p color)))

;; This was written to replace the dumb and slow MEMQ's on the list of
;; all-colors.


;;;; Nearest Color


(def-substitution-macro color-distance (r1 g1 b1 r2 g2 b2)
  (+f (absf (-f r1 r2)) (absf (-f g1 g2)) (absf (-f b1 b2))))

;;; The function `find-nearest-color' finds the color in the alist of (color r
;;; g b) nearest to the given color.  Nearness is defined by a Manhatten
;;; metric.  We return the best alist entry and the minimum distance thereto.
;;; Optionally, search only the pure-gray colors in the alist.

(defun find-nearest-color (color-alist red green blue search-gray-only-p)
  (let ((best-entry nil)
	(best-distance most-positive-fixnum))
    (loop for entry in color-alist
	  as (color r g b) = entry
	  doing
      (when (if search-gray-only-p (=f r g b) t)
	(let ((distance (color-distance r g b red green blue)))
	  (when (<f distance best-distance)
	    (setq best-entry entry
		  best-distance distance)))))
    (values best-entry best-distance)))

;; Using standard colors, we get only 8 shades of gray. And they aren't even
;; distributed evenly.


;;;; RGB (24-bit) Colors


;;; An `RGB color' is a symbol of the form RGBrrggbb, where rr, gg, bb, are the
;;; 8-bit hex values for the red, green, and blue components of the color. It's
;;; cached pixel value is actually stored as a fixnum in the order BGR, since
;;; that's what Windows and X11 want.

(def-concept rgb-color)

(def-global-property-name rgb-color-value-cache)
(def-global-property-name rgb-color-intensity-cache)
(def-global-property-name rgb-color-nearest-standard-color-cache)

(defun-simple rgb-color-p (thing)
  (and (symbolp thing)
       (or (not (null (rgb-color-value-cache thing)))
	   (let ((value? (rgb-color-value? thing)))
	     (when value?
	       (setf (rgb-color-value-cache thing) value?)
	       t)))))

(defun-simple rgb-color-value (rgb-color)
  (or (rgb-color-value-cache rgb-color)
      (setf (rgb-color-value-cache rgb-color) (rgb-color-value? rgb-color))))


;;; The substitution-macro `rgb' returns a packed BGR value.

(def-substitution-macro rgb (r g b)
  (logiorf (ashf (logandf b #xFF) 16)
	   (ashf (logandf g #xFF) 8)
	   (logandf r #xFF)))

(defun-simple rgb-color-value? (symbol)
  (let ((str (symbol-name symbol)))		; Avoid consing wide strings.
    (when (and (=f (length str) 9)
	       (char= (char str 0) #\R)
	       (char= (char str 1) #\G)
	       (char= (char str 2) #\B))
      (loop with value = 0
	    for i from 3 below 9
	    as weight? = (digit-char-p (schar str i) 16)
	    always weight?
	    do (setq value (logiorf (ashf value 4) weight?))
	    finally
	      ;; Return value as packed BGR.
	      (return (rgb (ashf value -16) (ashf value -8) value))))))

(def-substitution-macro rgb-color-components (rgb-color)
  (let ((value (rgb-color-value rgb-color)))	 ; BGR
    (values (logandf value #xFF)	         ; R
	    (logandf (ashf value -8) #xFF)	 ; G
	    (logandf (ashf value -16) #xFF))))	 ; B

(defun-simple rgb-color-intensity (rgb-color)
  (or (rgb-color-intensity-cache rgb-color)
      (setf (rgb-color-intensity-cache rgb-color)
	    (multiple-value-bind (red green blue)
		(rgb-color-components rgb-color)
	      (intensity-of-color red green blue)))))

(defun-simple rgb-color-nearest-standard-color (rgb-color)
  (or (rgb-color-nearest-standard-color-cache rgb-color)
      (setf (rgb-color-nearest-standard-color-cache rgb-color)
	    (multiple-value-bind (red green blue)
		(rgb-color-components rgb-color)
	      (car (find-nearest-color standard-gensym-color-alist red green blue nil))))))


;;; `canonical-color-name' - canonical in the sense of avoiding rgb-color
;;; symbols when possible.  There's also the idea of our vastly superior
;;; American spellings :-) but I don't consider "grey" to be noncanonical.
;;; Although, "grey" will never be the result of passing in an RGB color,
;;; so, in that sense, it isn't considered canonical.  -jv, 3/9/06
;;;   (canonical-color-name 'GRAY)      ==> GRAY
;;;   (canonical-color-name 'GREY)      ==> GREY
;;;   (canonical-color-name 'RGBA9A9A9) ==> GRAY

(defun-simple canonical-color-name (color)
  (cond
    ((gensym-metacolor-p color)
     color)
    ((color-value-vector-index-and-intensity color)
     color)
    ((rgb-color-p color)
     (multiple-value-bind (red green blue)
         (rgb-color-components color)
       (multiple-value-bind (closest-match distance)
           (find-nearest-color standard-gensym-color-alist red green blue nil)
         (if (=f 0 distance)
             (car closest-match)
             color))))
    (t
     #+development
     (cerror "return nil"
             "argument to CANONICAL-COLOR-NAME not a color of any sort")
     nil)))
       

(defun-simple twrite-color (color)
  (if (rgb-color-p color)
      (twrite-symbol color t)		; Looks better in upper-case?
      (twrite-symbol color)))


;;;; Operations with Colors



;;; This section implements the operations for mapping between colors, and color
;;; values.  It implments the mapping of colors used for monochrome screens.  It
;;; implements the fundamental operation `color-difference' as well as the
;;; operations for infering color-values given color-differences when painting.

;; - ben 5/11/93


;;; `rgb-from-color' takes a standard color (a symbol) and converts it
;;; into its RGB values (from 0 to 255). Nil is returned if it can't find
;;; an RGB value for the symbol.

(defun rgb-from-color (color)
  (loop for entry in standard-gensym-color-alist
	when (or (eq (first entry) color)	; color
		 (eq (fifth entry) color))	; alias?
	  return (values (second entry) (third entry) (fourth entry))
	finally (if (rgb-color-p color)
		    (return (rgb-color-components color)))))
	       
(defun rgb-value-of-gensym-color (color)
  (cond ((gensym-color-p color)
	 (multiple-value-bind (r g b)
	     (rgb-from-color color)
	   (rgb r g b)))
	((rgb-color-p color)
	 (rgb-color-value color))
	(t 0)))

;;; `Map-to-black-or-white' maps a color into black or white.  For a color in
;;; standard-gensym-color-alist, the mapping is done by thresholding the intensity
;;; of the color against minimum-intensity-for-white.  A color not in
;;; standard-gensym-color-alist is mapped to black.

;;; A `light color' is a color whose intensity is greater than or equal to 192.
;;; A `dark color' is a non-light color.



(defun-simple map-to-black-or-white (color)
  (let ((color-value-vector-index-and-intensity?
	  (color-value-vector-index-and-intensity color)))
    (cond (color-value-vector-index-and-intensity?
	   (if (>=f (cdr color-value-vector-index-and-intensity?)
		    minimum-intensity-for-white)
	       'white
	       'black))
	  ((rgb-color-p color)
	   (if (>=f (rgb-color-intensity color)
		    minimum-intensity-for-white)
	       'white
	       'black))
	  (t
	   'black))))

;; This might be used for deciding whether to use black or white as a foreground
;; (e.g. text) color.

;; Try this in map-to-color-value!  If users avoid using light colors for icons (or
;; at least for icon outlines), then the icons should show up, against a light background,
;; on a black and white monitor.  The icon editor could give warnings.



;;; `Map-to-color-value' returns the color value that represents color, according
;;; to current-color-map.

;;; If current-color-map does not give a mapping for color, color is mapped into the
;;; color value for black (or to 0 if even that fails), except that in a #+development
;;; version, a continuable error is signalled.

(def-substitution-macro map-to-standard-color-value? (color)
  (let ((color-value-vector-index-and-intensity?
	  (color-value-vector-index-and-intensity color)))
    (if color-value-vector-index-and-intensity?
	(managed-svref
	  (color-value-vector current-color-map)
	  (car color-value-vector-index-and-intensity?)))))

(defun map-to-color-value-1 (color)
  (let ((color-value
	  (or (case color
		(black (color-value-for-black? current-color-map))
		(white (color-value-for-white? current-color-map)))

	      (map-to-standard-color-value? color)

	      ;; 24-bit color
	      (if (rgb-color-p color)
		  (if (color-map-true-color-p current-color-map)
		      (rgb-color-value color)
		      (map-to-standard-color-value?
			(rgb-color-nearest-standard-color color))))

	      (getfq (color-value-plist current-color-map) color)

	      (cond
		((new-pastel-color? color)
		 ;; This development check is not applied here because if it's
		 ;; a new pastel color that's missing, chances are we're just
		 ;; using an old (pre-3.1) version of Telewindows.  Here the
		 ;; right thing to do is just to map to white.  (MHD 12/17/92)
		 (color-value-for-white? current-color-map))
		(t
		 (dwarn "No mapping for ~A in ~A" color current-color-map)
		 (color-value-for-black? current-color-map)))
	      0)))

    (setf (color-map-last-color? current-color-map) color
	  (color-map-last-color-value? current-color-map) color-value)

    color-value))

(def-substitution-macro map-to-color-value-macro (color)
  (cond
    ;; One-element cache for speed.
    ((eq color (color-map-last-color? current-color-map))
     (color-map-last-color-value? current-color-map))
    (t
     (map-to-color-value-1 color))))


(def-substitution-macro color-value-for-white ()
  (or (color-value-for-white? current-color-map)
      (map-to-color-value-1 'white)))

(def-substitution-macro color-value-for-black ()
  (or (color-value-for-black? current-color-map)
      (map-to-color-value-1 'black)))


(defun map-to-color-value (color)
  (map-to-color-value-macro color))

;; See also map-color-or-metacolor-to-color-value.


;; If there were a way to define new colors via Telewindows, you might solve the
;; most or all of such future versioning problems as the one above!  (MHD
;; 12/17/92)

;; Consider having a substitution macro version of this, for speed critical
;; calls, as in draw functions.

;; Consider always signalling an error, once G2 is cleaned up to never allow
;; illegal colors.  Now you can get illegal colors into the system by changing
;; the icon color to "the value of" some variable.  The culprit is
;; change-color-of-icon (or some caller thereof); they do not check for
;; "illegal" colors, and there is no official way of doing so.  FIX
;; CHANGE-COLOR-OF-ICON!!!  (MHD 2/2/89)



;;; `Map-to-color' returns the color, a symbol, that is represented by a color
;;; value in the current-color-map.  This is the inverse of MAP-TO-COLOR-VALUE.
;;; This isn't a common operation in AB.  It is used, for example, in building
;;; the postscript print job header's mapping from color-value to RGB values.

(defun map-to-color (color-value)
  (loop for (color) in standard-gensym-color-alist
	when (=f color-value (map-to-color-value color))
	  return color))

;; This is a foolish algorithum but the topology of the color map is
;; undocumented and so I'm reduced to doing a search for now.  - ben 3/25/92.




;;;; Color differences


;; ICP Value Type Equivalences for Color:

(def-icp-value-type-equivalence color-value unsigned-integer)

(def-icp-value-type-equivalence color-value? unsigned-integer?)

(def-icp-value-type-equivalence color-difference unsigned-integer)

(def-icp-value-type-equivalence color-difference? unsigned-integer?)

(def-icp-value-type-equivalence subtract-instead? boolean)







;;; `Color-difference' yields the difference of color-value-1 and color-value-2,
;;; for the current window.  

;;; Sadly we lose some readability by using this one operation for all these
;;; operations.
;;;     value - value -> difference
;;;     value + difference -> value
;;;     difference + value -> value
;;;     difference + difference -> difference

(defmacro color-difference (color-value-1 color-value-2)
  (avoiding-variable-capture (color-value-1 color-value-2)
    `(logxorf ,color-value-1 ,color-value-2)))

(defmacro color-sum (color-value color-difference)
  (avoiding-variable-capture (color-value color-difference)
    `(logxorf ,color-value ,color-difference)))

;; Chestnut did not pick up the fixnum declarations when the arguments were
;; expressions.  As a result, we were calling the fat and slow LOGXOR.
;; -fmw, 1/6/95


(def-substitution-macro color-eq (color-1 color-2)
  (eq color-1 color-2))


(defun-substitution-macro color-difference-is-transparent-p (color-difference)
  (cond ((paint-mode-p)
	 (=f color-difference transparent-color-value))
	(t
	 (or (=f color-difference 0)
	     ;; This case is just paranoia.
	     (=f color-difference transparent-color-value)))))


(defun-substitution-macro color-difference-is-zero-p (color-difference)
  (=f color-difference 0))



;;; `Infer-color-value-from-color-difference' will compute a color value
;;; given a color difference using the current binding of 
;;; background-color-value.  This routine lies at the heart of the
;;; machinery that allows code written in an XOR drawing model to 
;;; refresh the screen using a painting drawing model.

(defun-substitution-macro infer-color-value-from-color-difference (color-difference-arg)
  (color-sum color-difference-arg current-background-color-value))



;;; `Infer-color-value-from-color-difference-and-transfer-mode' is used
;;; to compute the color value to send to the rendering substrate.
;;; In the primitive drawing operations.  It is called in tandem with
;;; a routine to infer the transfer mode to utilize.

(defun-substitution-macro infer-color-value-from-color-difference-and-transfer-mode
    (generalized-color-difference)
  (cond ((xor-mode-p)
	 generalized-color-difference)
	((=f generalized-color-difference transparent-color-value)
	 current-background-color-value)
	(t
	 (infer-color-value-from-color-difference generalized-color-difference))))







;;;; Platform Independent Color and Transfer Mode Handling


;;; For each rendering system implement a few platform specific operations to
;;; handle colors.

;;; Routines are provided to select the transfer mode to use when rendering
;;; bitmaps, and for other rendering.  They are implemented in the sections that
;;; follow.

;;; Bitmap drawing may require a different transfer mode to handle transparency.
;;; For example we have a 1 deep bitmap, and we desire to have the 1 bits go to
;;; the screen in color, while the zero bits leave the screen unchanged.  In XOR
;;; this is easy, but when painting this may require an unusual transfer mode.

;;; On the Lispm this is the transfer mode screen::alu-transp.

;;; Under X11 there is no transfer mode correct for this, and so have
;;; implemented a pseudo transfer mode to achieve the desired effect (i.e.
;;; x11-transparent-copy).



;;; With-local-color provides the platform with a chance to avoid unnecessary
;;; operations to set the color.  For example on the TI these are used to
;;; avoid calling the color setting methods by caching a memory of the
;;; most recent color value setting made in this window.

(defmacro with-local-color (&body body)
  `(progn ,@body))




;;;; X11 Color and Transfer Mode Handling



;;; The general design of the platform specific color operations are discussed
;;; in the previous section.  In X11 no additional operations are implemented.

(defun-substitution-macro current-transfer-mode-for-x11-windows ()
  (case current-drawing-transfer-mode
    (:paint-infered-from-xor x11-copy)
    (:xor                    x11-xor)
    #+development
    (otherwise (error "Unknown transfer mode"))
    #-development
    (otherwise               x11-xor)))

(defun-substitution-macro current-transfer-mode-for-bitmaps-in-x11-windows ()
  (case current-drawing-transfer-mode
    (:paint-infered-from-xor x11-stippled)
    (:xor                    x11-xor)
    #+development
    (otherwise (error "Unknown transfer mode"))
    #-development
    (otherwise               x11-xor)))





;;;; Color Palettes (Obsolete)




;; The following is an obsolete nop, but it may be sent to Telewindows by
;; G2's older than 12/27/89.

(def-icp-value-reader-substitution-macro color-map
  (read-icp-unsigned-integer))

(def-icp-value-writer-substitution-macro color-map
  color-map
  (write-icp-unsigned-integer 0))

(def-icp-message-functions set-up-palette (gensym-window color-map)
  (case type-of-current-window))







;;;; Select Best Protocol to Use with Telewindows




;;; `Obtain-max-window-protocol' is called by G2 on every window it makes.  It
;;; implements the negotiation over protocol level, setting the window to the
;;; maximum protocol between what this G2 can support and what the
;;; window-parameters-plist requests.

;;; Having made the choice if the protocol level is high enough it notifies
;;; the other end of the connection if it is a Telewindows, and switches over
;;; to :paint-infered-from-xor as it's prefered transfer mode.

(defun-allowing-unwind obtain-max-window-protocol (gensym-window)

  ;; Negotiate and commit the best protocol we can.
  (change-icp-window-protocol-version
    gensym-window
    (minf latest-icp-window-protocol-version
	  (or (getf (window-parameters-plist gensym-window)
		    'icp-window-protocol-version)
	      original-icp-window-protocol-version)))

  ;; If it is a TeleWindows, and it can hear this message, tell it what we decided.

  (when (window-supports-this-icp-window-protocol-p
	  icp-window-protocol-supports-setting-protocol-level
	  gensym-window)

    ;; Only for ICP Windows currently (i.e., Telewindows) 
    (with-icp-window (gensym-window)
      (send-icp-set-window-protocol-version
	gensym-window
	(icp-window-protocol-version gensym-window))))

  ;; Pass over initial values for some window attributes.
  ;; This function is a stub in telewindows.
  
  (initialize-image-palette-of-new-gensym-window gensym-window)

  )

;; Changed not to use on-window via update-window.  That's got probably several
;; problems, e.g., it's a kludge, and it's ineffecient, but the fact that the
;; body may not get executed makes it, I think, unusable for this purpose.  For
;; similar reasons, I chose not to use it below, in
;; establish-telewindows-license-level.  (MHD 2/1/95)



;;; The function `change-icp-window-protocol-version' changes the protocol
;;; version stored in the given gensym-window structure.  If the version is
;;; high enough, we also upgrade the transfer mode to paint.

;;; Note that this function is called by both G2 and TW.  In G2,
;;; global-paint-mode-p returns the transfer mode for the entire KB, from
;;; drawing-parameters, and we upgrade to paint mode only if the KB is in paint
;;; mode.  In TW, global-paint-mode-p simply returns T, so we will upgrade in
;;; all cases.  Fortunately, in TW the setting stored in the window structure
;;; is ignored -- G2 always sets the mode before drawing.

(defun-void change-icp-window-protocol-version (gensym-window icp-window-protocol-version)
  ;; Slam it.
  (setf (icp-window-protocol-version gensym-window)
	icp-window-protocol-version)

  ;; Upgrade window to paint-mode if the KB is in paint mode, and the remote
  ;; telewindow is capable of paint mode.  The KB test fixes HQ-392336.
  ;; -fmw, 7/20/95
  (when (and (global-paint-mode-p)
	     (window-supports-this-icp-window-protocol-p
	       icp-window-protocol-supports-transparent-copy
	       gensym-window))
    
    (setf (drawing-transfer-mode-of-gensym-window gensym-window)
	  :paint-infered-from-xor))

  ;; I'm sticking this here, unable to find a more elegant spot.  This is
  ;; just for handling a kind of initialization that has to happen for X11
  ;; windows handled as local windows, i.e., not via Telewindows.  The
  ;; Telewindows case is handled by telewindows-check-version-of-remote-g2
  ;; in TELEWINDOWS, q.v. Note: the test for type x11-window is not needed
  ;; in practice, but should be done for modularity's sake.  However, for
  ;; now I'm omitting it -- it's a macro forward reference. (MHD 12/21/99)
  (unless (slave-gensym-window? gensym-window)
    (initialize-gensym-window-after-connection gensym-window)))


(def-system-variable initialize-gensym-window-after-connection-done WINDOWS1 nil)

(defun initialize-gensym-window-after-connection (gensym-window)
  (when (eq (type-of-gensym-window gensym-window) 'x11-window)
    (unless initialize-gensym-window-after-connection-done
      (c-x11-initialize-after-connection
	(native-window? gensym-window)
	(icp-window-protocol-version gensym-window)
	(if (window-supports-unicode-character-events gensym-window)
	    1
	    0)
	(if (getf command-line-arguments 'xclip)
	    1
	    0))
      (setq initialize-gensym-window-after-connection-done t))))




;;;; Establishing License Levels for a Telewindows Connection



;;; `Establish-telewindows-license-level' establishes a license level for
;;; gensym-window, presumably a Telewindows window, and sends the ICP message to
;;; the remote (telewindows) client giving its license level.  If this is not a
;;; Telewindows window, or it does not support the ICP message (because it's
;;; an older version than 4.0 Beta Phase 2, then nothing actually happens.
;;;
;;; This uses negotiate-telewindows-licensing, found in sequences2, to obtain
;;; the permission.  See that function for details.

(defun-allowing-unwind establish-telewindows-license-level (gensym-window)
  (when (current-window-supports-this-icp-window-protocol-p
	  icp-window-protocol-supports-floating-telewindows
	  gensym-window)

    (let ((license-level? (negotiate-telewindows-licensing gensym-window)))

      ;; Only for ICP Windows currently (i.e., Telewindows) 
      (with-icp-window (gensym-window)
	(cond
	  ((window-supports-this-icp-window-protocol-p
	     icp-window-protocol-supports-telewindows-connection-license-info
	     gensym-window)
	   (let ((info (gensym-list
			 'telewindows-connection-license-level license-level?
			 'g2-license-level (get-g2-license-level)
			 'g2-authorized-optional-modules
			   (loop for (module-name) in optional-modules-map
				 when (module-authorized-p module-name)
				   collect module-name using gensym-cons))))
	     (send-icp-set-telewindows-connection-license-info gensym-window info)
	     (reclaim-gensym-tree info)))
	  (t
	   ;; obsolete, and just used for Beta II (plus inhouse versions before
	   ;; rev. 56) (MHd 5/20/95)
	   (send-icp-set-window-license-level gensym-window license-level?)))))))





;;;; Rasters



;;; A `raster' is a structure that represents a two-dimensional array of
;;; `pixels'.  A `pixel value' is a color value, a color difference, or a bit
;;; that distinguishes `foreground' (1) from `background' (0).  An `area' of a
;;; raster is an arbitrary rectangular window of that raster.  `Painting' in a
;;; raster means making a subset of its pixels all the same color.

;;; Two types of raster are distinguished: scratchpad rasters and stored
;;; rasters.  This distinction is fully explained below.

;;; There are no constraints on the types of structures that may be used to
;;; implement the two types of raster.  For example, either or both of them may
;;; be implemented as lists that describe the location and size of structures
;;; located within the memory of some remote processor or device.  They both
;;; may be implemented identically, where that is possible; in other words, the
;;; different types need not be distinguishable.

;;; At any one moment, there is at most one scratchpad raster (per AB process).
;;; Note that there should be no upper limit on the size of scratchpad and
;;; stored rasters, but in certain implementations, it may be impractical to
;;; have such rasters exceed the standard screen or window dimensions.

;; Consider enforcing a limit on the size of scratchpad and stored rasters.







;;;; Scratchpad Rasters



;;; `On-scratchpad-raster' does the following:
;;;
;;;    (1) initializes a scratchpad raster, which becomes the `current
;;;    scratchpad raster';
;;;
;;;    (2) executes scratchpad-raster-painting-body; and
;;;
;;;    (3) converts the current scratchpad raster to a new stored raster that
;;;    has the  painted contents of the scratchpad raster, and returns
;;;    that stored raster.

;;; A `scratchpad raster' is a raster used for the production of icons from
;;; line drawing descriptions, characters from character descriptions, tiling
;;; patterns from tiling pattern rows, etc.  When the production of such an
;;; icon, character, or whatever has been completed, the scratchpad raster is
;;; converted to a "stored raster" (see below).

;;; The gensym-window, minimum-width, and minimum-height arguments are all
;;; evaluated.  Executions of on-scratchpad-raster forms cannot be nested.
;;; 
;;; IMPORTANT NOTE: Executions of on-scratchpad-raster can in practice be
;;; be nested, and they are in fact now being nested in 3.0, e.g. for charts,
;;; graphs, and text in icons.  This issue is being reviewed, and this facility
;;; will likely change to reflect the new practice -- probably either by allowing
;;; at most n (probably with n = 2) levels of recursion, or by getting rid of
;;; the notion of a "scratchpad", which is not really needed for any of the
;;; base window systems we currently use.  (It was only needed for Gold Hill's
;;; window system, which never was part of the product and hasn't been supported
;;; for several years.)  (MHD 11/16/90)

;;; `On-prepared-scratchpad-raster' wraps around on-scratchpad-raster. In some 
;;; implementations, it serves to create an environment in which on-scratchpad-
;;; raster can be run.


(def-named-dynamic-extent scratchpad-raster
  (module windows1))

(defvar-of-named-dynamic-extent current-scratchpad-raster-type scratchpad-raster)

(defvar-of-named-dynamic-extent current-scratchpad-raster scratchpad-raster)

(defvar-of-named-dynamic-extent current-scratchpad-raster-width scratchpad-raster)

(defvar-of-named-dynamic-extent current-scratchpad-raster-height scratchpad-raster)

(defvar-of-named-dynamic-extent current-scratchpad-raster-depth scratchpad-raster)

(defvar-of-named-dynamic-extent current-scratchpad-raster-tiled-p scratchpad-raster)

(defvar-of-named-dynamic-extent current-x-offset-for-stored-raster? scratchpad-raster)

(defvar-of-named-dynamic-extent current-y-offset-for-stored-raster? scratchpad-raster)

(defvar-of-named-dynamic-extent current-x-max-for-stored-raster? scratchpad-raster)

(defvar-of-named-dynamic-extent current-y-max-for-stored-raster? scratchpad-raster)

                                                                                

(defmacro on-prepared-scratchpad-raster (&body body)
  `(progn . ,body))

(defmacro on-scratchpad-raster-with-depth
	  ((gensym-window minimum-width minimum-height depth make-exact-size-p
	    x-offset-for-stored-raster? y-offset-for-stored-raster?
	    x-max-for-stored-raster? y-max-for-stored-raster? make-tiled-p)
	   &body scratchpad-raster-painting-body)
  (avoiding-variable-capture
      (gensym-window minimum-width minimum-height depth make-exact-size-p)
    `(on-prepared-scratchpad-raster
       (with-named-dynamic-extent* scratchpad-raster
	   ((current-scratchpad-raster-type
	      (scratchpad-raster-type-for-window ,gensym-window))
	    (current-scratchpad-raster-tiled-p ,make-tiled-p)
	    (current-scratchpad-raster-width ,minimum-width)
	    (current-scratchpad-raster-height ,minimum-height)
	    (current-scratchpad-raster-depth ,depth)
	    (on-monochrome-raster-list-p nil)
	    (current-x-offset-for-stored-raster? ,x-offset-for-stored-raster?)
	    (current-y-offset-for-stored-raster? ,y-offset-for-stored-raster?)
	    (current-x-max-for-stored-raster? ,x-max-for-stored-raster?)
	    (current-y-max-for-stored-raster? ,y-max-for-stored-raster?)
	    current-scratchpad-raster)
	 (initialize-scratchpad-raster	; sets current-scratchpad-raster 
	   ,gensym-window		;   in non-icp case
	   ,minimum-width ,minimum-height
	   ,depth ,make-exact-size-p)
	 (progn . ,scratchpad-raster-painting-body)
	 (convert-current-scratchpad-raster-to-stored-raster
	   ,gensym-window
	   ,minimum-width ,minimum-height
	   ,depth ,make-exact-size-p)))))

(defmacro on-scratchpad-raster
	  ((gensym-window minimum-width minimum-height 
	    &optional make-exact-size-p
	    x-offset-for-stored-raster? y-offset-for-stored-raster?
	    x-max-for-stored-raster? y-max-for-stored-raster?
	    make-tiled-p)
	   &body scratchpad-raster-painting-body)
  `(on-scratchpad-raster-with-depth
     (,gensym-window ,minimum-width ,minimum-height 1 ,make-exact-size-p
      ,x-offset-for-stored-raster? ,y-offset-for-stored-raster?
      ,x-max-for-stored-raster? ,y-max-for-stored-raster? ,make-tiled-p)
     ,@scratchpad-raster-painting-body))

; unused
(defmacro on-polychrome-scratchpad-raster
	  ((gensym-window minimum-width minimum-height minimum-depth
			  &optional make-exact-size-p)
	   &body scratchpad-raster-painting-body)
  (let ((gensym-window-var (gensym)))
    `(let ((,gensym-window-var ,gensym-window))
       (on-scratchpad-raster-with-depth
	 (,gensym-window-var ,minimum-width ,minimum-height
	  ,minimum-depth
	  ,make-exact-size-p nil nil nil nil nil)
	 ,@scratchpad-raster-painting-body))))

;; On-polychrome-scratchpad-raster is used when polychrome rasters are used
;; for graphs (see graphs1).  - agh 4/10/89 



;;; `On-scratchpad-raster-for-font-character-image' is a special-purpose version
;;; of on-scratchpad-raster intended for use for AB-font rasterization.  The
;;; raster desired must be non-tiled, bitmaps (depth = 1-bit), not of type
;;; ICP, not requiring an exact sized bitmap (may be larger).  The
;;; callback-function-to-gc-if-allocation-failure should evaluate at runtime to
;;; the name of a function to call in case there is a problem allocating a
;;; raster.  This function's job is to reclaim as many character bitmaps as
;;; possible, thus making it likely that the next attempt to obtain a raster
;;; will succeed.  If the GC function still fails, the macro tries still other
;;; means to get a large enough bitmap.

(defmacro on-scratchpad-raster-for-font-character-image
	  ((gensym-window minimum-width minimum-height)
	   (callback-function-to-gc-if-allocation-failure)
	   &body scratchpad-raster-painting-body)
  (avoiding-variable-capture
       (gensym-window minimum-width minimum-height)
     `(on-prepared-scratchpad-raster
	(with-named-dynamic-extent* scratchpad-raster
	    ((current-scratchpad-raster-type
	       (scratchpad-raster-type-for-window ,gensym-window))
	     (current-scratchpad-raster-tiled-p nil)
	     (current-scratchpad-raster-width ,minimum-width)
	     (current-scratchpad-raster-height ,minimum-height)
	     (current-scratchpad-raster-depth 1)
	     (on-monochrome-raster-list-p nil)
	     (current-x-offset-for-stored-raster? nil)
	     (current-y-offset-for-stored-raster? nil)
	     (current-x-max-for-stored-raster? nil)
	     (current-y-max-for-stored-raster? nil)
	     current-scratchpad-raster)
	  #+development
	  (check-constraints-on-use-of-local-scratchpad-raster-with-gc)
	  (setq current-scratchpad-raster
		(allocate-scratchpad-raster
		  ,gensym-window ,minimum-width ,minimum-height
		  ,callback-function-to-gc-if-allocation-failure))
	  (progn . ,scratchpad-raster-painting-body)
	  (convert-current-scratchpad-raster-to-stored-raster
	    ,gensym-window
	    ,minimum-width ,minimum-height
	    1 nil)))))



;;; `Stored-raster-error-result-p' ... 

(defmacro stored-raster-error-result-p (r)
  `(<f ,r 0))


;;; `Allocate-scratchpad-raster' tries to
;;; create a new raster for fonts. It first tries
;;; allocate-stored-raster-1, which will try to find a
;;; suitable raster from the pools, then will try the OS. If
;;; that fails, it "gc's" (garbage collects), that is, reclaims
;;; all rasters of a certain type via the
;;; callback-function. Next it hard reclaims, which means it
;;; gives back to the OS "all reclaimed stored rasters". Next,
;;; it tries allocate-stored-raster-1 again, which should work
;;; if the gc reclaimed anything at all. If that fails,
;;; however, a bigger size raster is tried. If nothing works,
;;; call handle-no-solution.

;;; 1. sets do-not-error-in-x11-create-pixmap-on-failed-allocation to t
;;; 2. calls allocate-stored-raster-1 (tries pool first, then 
;;;      create-stored-raster, which can call create_pixmap)
;;; 3. gc's:  reclaim-all-scaled-fonts 
;;; 4. calls hard-reclaim-all-reclaimed-stored-rasters
;;;	(all rasters in pools on gensym-window)
;;; 5. calls allocate-stored-raster-1 again
;;; 6. if that fails, tries larger size from font pool 
;;; 7. if that fails, calls handle-no-solution


(defun-simple allocate-scratchpad-raster
    (gensym-window minimum-width minimum-height
		   callback-function-to-gc-if-allocation-failure)
  (let* ((do-not-error-in-x11-create-pixmap-on-failed-allocation t)
	 (raster (allocate-stored-raster-1
		   gensym-window minimum-width minimum-height 1 nil)))
    (when (stored-raster-error-result-p raster)
      (notify-user-at-console
	"~%Unable to allocate a ~dx~d pixmap! Will retry ....~%"
	minimum-width minimum-height)
      (funcall callback-function-to-gc-if-allocation-failure)
      (hard-reclaim-all-reclaimed-stored-rasters gensym-window)
      (setq raster (allocate-stored-raster-1
		     gensym-window minimum-width minimum-height 1 nil))
      (when (stored-raster-error-result-p raster)
	(notify-user-at-console
	  "~%Still unable to allocate a ~dx~d pixmap! Will try larger size ....~%"
	  minimum-width minimum-height)
	(setq raster (allocate-bigger-stored-raster
		       gensym-window minimum-width minimum-height 1))
	(when (stored-raster-error-result-p raster)
	  (handle-no-solution-to-raster-allocation-failure
	    gensym-window minimum-width minimum-height))))
    raster))





#+development
(defun check-constraints-on-use-of-local-scratchpad-raster-with-gc ()
  (when (eq current-scratchpad-raster-type 'icp)
    (cerror "Continue, as in production."
	    "This form, on-scratchpad-raster-for-font-character-image,~
             may not be used over ICP!"))
  (unless (eq current-scratchpad-raster-type 'x11-pixmap)
    (cerror "Continue, as in production."
	    "This form, on-scratchpad-raster-for-font-character-image,~
             may only be used with rasters of type X11-PIXMAP!"))
  (unless (=f current-scratchpad-raster-depth 1)
    (cerror "Continue, as in production."
	    "This form, on-scratchpad-raster-for-font-character-image,~
             may only be used with bitmap (depth=1) rasters!"))
  (when current-scratchpad-raster-tiled-p 
    (cerror "Continue, as in production."
	    "This form, on-scratchpad-raster-for-font-character-image,~
             may not be for tiled rasters!")))
  







	 
;;; `Initialize-scratchpad-raster' sets current-scratchpad-raster to an
;;; initialized scratchpad raster.  It can either create and return a new
;;; structure or just reinitialize some structure that is either unique to the
;;; AB process or to the window.
;;;
;;; The scratchpad raster will be at least minimum-width by minimum-height in
;;; size and will have the specified number of bits-per-pixel.  All pixels in a
;;; scratchpad raster will initially be zero (which represents transparency in a
;;; raster of color differences).
;;;
;;; Note that this function should be invoked only by on-scratchpad-raster.  The
;;; caller of this function is responsible for binding
;;; current-scratchpad-raster, although it need not be bound to any particular
;;; value.  This returns no value.

(def-icp-message-functions initialize-scratchpad-raster
			   ((gensym-window gensym-window)
			    (unsigned-integer minimum-width)
			    (unsigned-integer minimum-height)
			    (unsigned-integer bits-per-pixel)
			    (boolean make-exact-size-p))
  (case current-scratchpad-raster-type
    (t
     (setq current-scratchpad-raster
	   (allocate-stored-raster
	     gensym-window minimum-width minimum-height
	     bits-per-pixel make-exact-size-p)))))

;; NOTE: previously, this function just returned a scratchpad raster, which was
;; to be bound by the caller, and it did not setq current-scratchpad-raster
;; itself.  Its contract was changed, 11/15/93, as part of converting all ICP
;; message functions into non-value-returning functions (defun-voids).  This has
;; no impact on ICP compatibility, since it only affects local callers, i.e.,
;; non-ICP, PRINTER cases.  This has been done in conjunction with changes in
;; on-scratchpad-raster-with-depth.  (MHD/BAH 11/15/93)









;;;; Stored Rasters



;;; A `stored raster' is a raster that can be retained indefinitely, with its
;;; contents being copied or added into windows (see below) as appropriate.
;;; (In certain implementations, a scratchpad raster may already be suitable
;;; for use as a stored raster or stored raster array.)

;;; A `monochrome raster' is a one-bit-pixel stored raster, where pixel value 1
;;; means `foreground' and pixel value 0 means `background'.

;;; A `color difference raster' is a stored raster of color differences.



;;; `Convert-current-scratchpad-raster-to-stored-raster' returns a stored raster
;;; with the same contents as the current scratchpad raster.  Minimum-width,
;;; minimum-height, and bits-per-pixel should be the same as were used when the
;;; current scratchpad raster was initialized.  Note that this function should
;;; be invoked only by on-scratchpad-raster.

;; This must always make and return a (local) stored raster.  If the current
;; scratchpad raster is remote, it should also make a corresponding stored
;; raster with a raster array.  If the current scratchpad raster is local, this
;; may store the pixels locally and make the corresponding stored raster later,
;; shipping the pixels then, or it may make the corresponding stored raster
;; immediately, shipping the pixels from the local scratchpad without storing
;; them locally.  This is further complicated by the question of whether to
;; have a local stored raster with more than one corresponding one!



;; Stored-raster-width returns the actual width of stored-raster, which should
;; be the same as the actual width of the scratchpad raster from which it was
;; made.  Stored-raster-height is similar.

;; Orphan: who eliminated the definitions?

(defvar on-monochrome-raster-list-p)		; documented below, but forward-
						;   referenced by the following fn.

;;; `paint-only-target-monochrome-raster-p' is part of an experiment
;;; to see if independent layer drawing can be possible for graph-renderings
;;; and, eventually, icon-renderings.  The current painting primitives
;;; "cut out holes" in all other layers from the color layers that is
;;; currently being painted.

(defvar paint-only-target-monochrome-raster-p nil)

;;; The function `convert-current-scratchpad-raster-to-stored-raster' ...

(defun convert-current-scratchpad-raster-to-stored-raster
       (gensym-window minimum-width minimum-height
	bits-per-pixel make-exact-size-p)
  (case current-scratchpad-raster-type  
    (t 
     (cond 
       ((and (not current-scratchpad-raster-tiled-p)
	     current-x-offset-for-stored-raster?)
	(let* ((scratchpad-raster-containing-region current-scratchpad-raster)
	       (stored-raster-width
		 (-r current-x-max-for-stored-raster? 
		     current-x-offset-for-stored-raster?))
	       (stored-raster-height
		 (-r current-y-max-for-stored-raster? 
		     current-y-offset-for-stored-raster?))
	       (x-offset current-x-offset-for-stored-raster?)
	       (y-offset current-y-offset-for-stored-raster?)
	       (new-stored-raster
		 (on-scratchpad-raster
		   (gensym-window stored-raster-width stored-raster-height)
		   (transfer-region-to-smaller-raster
		     0 0 stored-raster-width stored-raster-height
		     scratchpad-raster-containing-region
		     x-offset y-offset
		     1))))
	  (reclaim-stored-raster
	    scratchpad-raster-containing-region gensym-window
	    minimum-width minimum-height bits-per-pixel make-exact-size-p)
	  new-stored-raster))
       (t
	current-scratchpad-raster)))))

;; ;; Fix this to produce different types of stored raster!
;;
;; (MHD 7/24/89)




;;;; Raster Support for Graphs

;;; In order to update graphs (see update-graph-rendering), it is necessary to
;;; load stored rasters into a scratchpad raster and vice-versa.  These
;;; capabilities are provided by the following macros and functions.



(def-substitution-macro load-stored-raster-into-current-scratchpad-raster
			(stored-raster minimum-width minimum-height)
  minimum-width minimum-height	  ; unused
  stored-raster)

;; Load-stored-raster-into-current-scratchpad-raster currently just returns
;; stored raster in all cases.  (It was thought at one time to be necessary 
;; on the MX to copy the stored raster, but it turned out not to be.)


(def-substitution-macro load-current-scratchpad-raster-into-stored-raster
			(stored-raster minimum-width minimum-height)
  stored-raster minimum-width minimum-height	  ; unused
  nil)

;; Currently a no-op in all cases.  Like the previous function, it was at
;; first thought to be needed for the MX, but turned out not to be.



;;; On-scratchpad-raster-given-stored-raster is similar to on-scratchpad-raster
;;; in that both bind current-scratchpad-raster, call a body to paint the
;;; scratchpad raster, then load the raster back into a stored raster.
;;; Unlike on-scratchpad-raster however, on-scratchpad-raster-given-stored-raster
;;; does not allocate a new stored raster.

(defmacro on-scratchpad-raster-given-stored-raster
	  ((gensym-window stored-raster minimum-width minimum-height minimum-depth)
	   &body scratchpad-raster-painting-body)
  (avoiding-variable-capture
    (gensym-window stored-raster minimum-width minimum-height minimum-depth)
    `(on-prepared-scratchpad-raster
       (with-named-dynamic-extent*
	 scratchpad-raster
	 ((current-scratchpad-raster-type
	    (scratchpad-raster-type-for-window ,gensym-window))
	  (current-scratchpad-raster 
	    (load-stored-raster-into-current-scratchpad-raster
	      ,stored-raster ,minimum-width ,minimum-height))
	  (current-scratchpad-raster-tiled-p nil)
	  (current-scratchpad-raster-width ,minimum-width)
	  (current-scratchpad-raster-height ,minimum-height)
	  (current-scratchpad-raster-depth ,minimum-depth)
	  (on-monochrome-raster-list-p nil))
	 (progn . ,scratchpad-raster-painting-body)
	 (load-current-scratchpad-raster-into-stored-raster
	   ,stored-raster ,minimum-width ,minimum-height)))))



;;; `On-scratchpad-raster-list-given-stored-raster-list' ... binds current-scratchpad-
;;; raster-list and current-scratchpad-color-value-list, in addition to binding current-
;;; scratchpad-raster to an undefined value, so that it can be set.

;;; The variable `on-monochrome-raster-list-p' is normally bound to nil around scratchpad
;;; raster operation bodies by their respective macros.  But while in the body of
;;; on-scratchpad-raster-list-given-stored-raster-list, it is bound to true.

;;; `iterate-over-monochrome-raster-list-if-appropriate' must be wrapped around the body
;;; of raster painting operations.  This macro checks if on-monochrome-raster-list-p is
;;; true, and, if it is, uses the special variables current-scratchpad-raster-list and
;;; current-scratchpad-color-value-list, and binds current-scratchpad-raster appropriately
;;; around body.

;;; It also evaluates body as many times as there are rasters (only once for the non-list
;;; case).  Its color-value-variable argument must both give the value of the color value
;;; to use, as well as be a symbol that may be bound to the reinterpreted (on/off for
;;; monochrome) value, which in turn must be used to determine whether to draw 1s or 0s
;;; in the underlying monochrome raster(s).

(defvar current-scratchpad-raster-list)
(defvar current-scratchpad-color-value-list)

;(defvar on-monochrome-raster-list-p)

(defmacro on-scratchpad-raster-list-given-stored-raster-list
	  ((gensym-window list-of-stored-rasters
			  color-value-list
			  minimum-width minimum-height)
	   &body scratchpad-raster-painting-body)
  (avoiding-variable-capture
    (gensym-window list-of-stored-rasters color-value-list minimum-width minimum-height)
    `(on-prepared-scratchpad-raster
       (with-named-dynamic-extent*
	 scratchpad-raster
	 ((current-scratchpad-raster-type
	    (scratchpad-raster-type-for-window ,gensym-window))
	  (current-scratchpad-raster-tiled-p nil)
	  (current-scratchpad-raster-width ,minimum-width)
	  (current-scratchpad-raster-height ,minimum-height)
	  (current-scratchpad-raster-depth 1)
	  
	  (on-monochrome-raster-list-p t)	; activates special handing in
						;   scratchpad raster operation
	  (current-scratchpad-raster-list ,list-of-stored-rasters)
	  (current-scratchpad-color-value-list ,color-value-list)
	  current-scratchpad-raster)
	 (progn . ,scratchpad-raster-painting-body)))))

;; I'm skipping the load-stored-raster-.../load-current-... abstraction used above,
;; since I think it's on the way out.  It's kind of a local abstraction of a noop
;; anyway, which seems increasingly useless.  Note, however, that getting rid of
;; it completely would call into question the use of the "scratchpad" terminology.
;; Sigh.  (MHD 2/9/93)


(defmacro iterate-over-monochrome-raster-list-if-appropriate
	  ((color-value-variable) &body body)
  (avoiding-variable-capture
    (&aux goal-color-value scratchpad-raster color-value-for-this-raster)
    `(loop with ,goal-color-value = ,color-value-variable
	   with ,color-value-variable = ,color-value-variable
;	   with ,color-value-for-this-raster
	   for ,scratchpad-raster
	       in (if on-monochrome-raster-list-p	; list case?
		      current-scratchpad-raster-list
		      '(nil))
	   as ,color-value-for-this-raster	; only used for list case
	      in (if on-monochrome-raster-list-p
		     current-scratchpad-color-value-list
		     '(nil))
	   do (let ((foreground-layer-p
		      (and on-monochrome-raster-list-p
			   (=f ,goal-color-value ,color-value-for-this-raster))))
		(when on-monochrome-raster-list-p
		  (setq ,color-value-variable (if foreground-layer-p 1 0))
		  (setq current-scratchpad-raster ,scratchpad-raster))
		(when (or (not on-monochrome-raster-list-p)
			  (not paint-only-target-monochrome-raster-p)
			  foreground-layer-p)
		  . ,body)))))


;;;; Stored Raster Management



;;; The two hooks into raster pool management are the functions
;;; `allocate-stored-raster' and `reclaim-stored-raster'.



(def-structure (tiled-raster
		 (:reclaimer reclaim-tiled-raster-internal))
  (tile-arrays nil)
  (tile-size nil)
  (tile-size-index nil)
  (gensym-window-for-tiled-raster nil)
  (bits-per-pixel-for-tiled-raster nil))

;; See Raster Tiling section below for documentation.





#+development
(defvar trace-create-stored-raster-p nil)

#+development
(def-system-variable stored-raster-counter WINDOWS1 0)

#+development
(def-system-variable stored-raster-bits-counter WINDOWS1 0)

#+development
(def-system-variable number-of-stored-rasters-allocated WINDOWS1 0)

#+development
(def-system-variable list-of-all-stored-rasters WINDOWS1 nil)

#+development
(defun trace-stored-raster-creation (raster width height depth)
  (incf stored-raster-counter)
  (incf stored-raster-bits-counter (* width height depth))
  (push (list raster width height depth) list-of-all-stored-rasters)
  
  (locally
      (declare (special check-memory-enabled-p))
    (when (or trace-create-stored-raster-p
	      check-memory-enabled-p)
      (format t "Create-stored-raster: ~ax~ax~a is ~d, ~d rasters, ~d bytes in use.~%"
	      width height depth
	      stored-raster-counter
	      number-of-stored-rasters-allocated
	      (roundf stored-raster-bits-counter 8))
      (force-output))))

#+development
(defun describe-stored-rasters ()
  (let ((total-rasters 0)
	(total-bits 0))
    (labels ((K (table)
	       (let (list)
		 (maphash #'(lambda (key value) value (push key list)) table)
		 (sort
		   (remove-duplicates list :test #'equal)
		   #'< :key #'(lambda (s) (* (car s) (cdr s))))))
	     (P (table dept)
	       (loop for size in (K table)
		     as (w . h) = size
		     as cnt = (gethash size table)
		     doing
		 (format t "~10@a ~10@a ~10@a~%"
			 (format nil "~dx~d" w h)
			 cnt
			 (roundf (* cnt w h dept) 8))))
	     (D (depth)
	       (format t "~%Depth = ~d~%" depth)
	       (format t "~10@a ~10@a ~10@a~%" "Size" "Count" "Bytes")
	       (loop with table = (make-hash-table :Test #'equal)
		     for raster in list-of-all-stored-rasters
		     as (ident width height dep) = raster
		     as size = (cons width height)
		     if (=f depth dep)
		       sum 1 into num and
		       sum (* width height depth) into bits and
		       do (incf (gethash size table 0))
		     finally
		       (P table depth)
		       (format t "~10@a ~10@a ~10@a~%" "-----" "-----" "-----")
		       (format t "~10@a ~10@a ~10@a~%" "Total" num (roundf bits 8))
		       (incf total-rasters num)
		       (incf total-bits bits))))
      (D 1)
      (D 8)
      (D 24)
      (format t "~%All Depths~%")
      (format t "~10@a ~10@a ~10@a" "Total" total-rasters (roundf total-bits 8))
    (values))))


;;; The function `create-stored-raster' returns a "stored raster" from the
;;; native window system.  In the case of X windows, a stored raster is simply
;;; a fixnum handle.

(defun-simple create-stored-raster (gensym-window width height depth irregular-size-p)
  (let ((raster
	  (case (stored-raster-type-for-window gensym-window)
	    (x11-pixmap
	     (let ((the-raster
		      (let*
			  ((do-not-error-in-x11-create-pixmap-on-failed-allocation t))
			(x11-create-pixmap
			  (native-window? gensym-window) width height depth irregular-size-p))))
	       (cond
		 ((stored-raster-error-result-p the-raster)
		  (notify-user-at-console
		    "~%Unable to allocate a ~dx~d pixmap; will attempt to return stored rasters to OS."
		    width height)
		  (let ((count-of-rasters
			  (hard-reclaim-all-reclaimed-stored-rasters gensym-window)))
		    (notify-user-at-console "~%~d stored rasters returned to OS.~%"
					    count-of-rasters))
		  (x11-create-pixmap
		    (native-window? gensym-window) width height depth irregular-size-p))
		 (t the-raster)))))))
    #+development
    (trace-stored-raster-creation raster width height depth)
    raster))


;;; The macro `find-smallest-regular-size-macro' expands to a binary tree of IF
;;; statements which will execute and return the forms corresponding to the
;;; regular sizes.  A specified size corresponds to the smallest regular size
;;; that is bigger than it.  This macro executes the form (and returns the
;;; result) if the specified size is smaller or equal to the largest regular
;;; size, and the result of executing form-for-sizes-out-of-bound (bound refers
;;; to the largest regular size) if the largest regular size is smaller than
;;; the specified.

(defmacro find-smallest-regular-size-macro
	  (specified-size list-of-regular-sizes
	   corresponding-forms form-for-size-out-of-bound)  
  (let ((size-var
	  (if (symbolp specified-size)      
	      specified-size
	      (gensym-make-symbol "SPECIFIED-SIZE-"))))
    (generate-binary-search-code
      size-var list-of-regular-sizes corresponding-forms
      form-for-size-out-of-bound)))




;;; The macro `multiple-setq-to-regular-size-and-index' expands to a tree of IF
;;; statements which sets the symbol values of regular-size-var and index-for-
;;; regular-size-var to the appropriate values as determined by specified-size
;;; using the macro find-smallest-regular-size-macro.  If specified-size is so
;;; large that it requires an irregular raster, the symbol value of index-for-
;;; regular-size-var will be set to -1.

(defmacro multiple-setq-to-regular-size-and-index
	  ((regular-size-var index-for-regular-size-var) specified-size)
  (loop for index from 0
	as size in list-of-regular-raster-sizes
	collect
	  `(setq ,regular-size-var ,size
		 ,index-for-regular-size-var ,index)
	  into corresponding-forms
	finally
	  (return
	    `(find-smallest-regular-size-macro
	       ,specified-size
	       #.list-of-regular-raster-sizes
	       ,corresponding-forms
	       (setq ,index-for-regular-size-var -1)))))



;;; The macro `with-regular-stored-raster-size' is a wrapper which binds
;;; current-regular-raster-width, current-regular-raster-width-index,
;;; current-regular-raster-height, and current-regular-raster-height-index
;;; to appropriate values as specified by minimum-width and minimum-height.

(defmacro with-regular-stored-raster-size ((minimum-width minimum-height) &body body)
  `(let* ((current-regular-raster-width 0)
	  (current-regular-raster-height 0)
	  (current-regular-raster-width-index 0)
	  (current-regular-raster-height-index 0))
     (multiple-setq-to-regular-size-and-index
       (current-regular-raster-width current-regular-raster-width-index)
       ,minimum-width)
     (multiple-setq-to-regular-size-and-index
       (current-regular-raster-height current-regular-raster-height-index)
       ,minimum-height)
     ,@body))







;;; The structure `raster-info' is a list structure (but can be reimplemented
;;; as a def-structure) which contains the width, height, and depth of a raster
;;; and a pointer to that raster.

(defmacro make-raster-info (width height raster depth)
  `(graphics-list ,width ,height ,raster ,depth))

(def-substitution-macro reclaim-raster-info (raster-info)
  (reclaim-graphics-list raster-info))

(defmacro raster-info-width (raster-info)
  `(first ,raster-info))

(defmacro raster-info-height (raster-info)
  `(second ,raster-info))

(defmacro raster-info-raster (raster-info)
  `(third ,raster-info))

(defmacro raster-info-depth (raster-info)
  `(fourth ,raster-info))


;;; The structure `pixmap' wraps around a raw pixmap index as returned by the C
;;; routines, so that we can remember its width, height, and depth.

(def-structure (pixmap
		 (:constructor make-pixmap
			       (pixmap-width pixmap-height pixmap-depth pixmap-pointer))
		 (:reclaimer reclaim-pixmap-1))
  pixmap-width
  pixmap-height
  pixmap-depth
  pixmap-pointer)

;; I know, it duplicates raster-info.


;;; The function `reclaim-pixmap' reclaims the structure and the underlying
;;; raster.

(defun reclaim-pixmap (pixmap?)
  (when pixmap?
    (c-x11-reclaim-pixmap (pixmap-pointer pixmap?))
    (reclaim-pixmap-1 pixmap?)))

#+development
(def-development-printer print-pixmap (pixmap &optional (stream *standard-output*))
  (when (pixmap-p pixmap)
    (printing-random-object (pixmap stream)
	(format stream "PIXMAP ~dx~dx~d"
		(pixmap-width pixmap)
		(pixmap-height pixmap)
		(pixmap-depth pixmap)))
    pixmap))


;;; `Hard-reclaim-all-reclaimed-stored-rasters' gives all
;;; rasters in the reclaimed raster pools back to the
;;; operating system.  This is only rarely called in case
;;; of allocation failure, but is also called at the end of any
;;; printing operation.

(defun hard-reclaim-all-reclaimed-stored-rasters (gensym-window)
  (+f
    (hard-reclaim-all-regular-size-reclaimed-stored-rasters gensym-window)
    (hard-reclaim-all-irregular-size-reclaimed-stored-rasters gensym-window)))

(defun hard-reclaim-all-regular-size-reclaimed-stored-rasters (gensym-window)  
  (loop with count = 0
	with max-index		; per 2d-array doc (& code)
	  = maximum-managed-simple-vector-size
	repeat 2
	for pool-vector
	    = (regular-size-bitmap-raster-pools gensym-window)
	    then (regular-size-pixmap-raster-pools gensym-window)
	do (loop for index from 0 below max-index
		 do (loop for stored-raster?
			      = (graphics-pop (svref pool-vector index))
			  while stored-raster?
			  do (incff count)
			     (c-x11-reclaim-pixmap stored-raster?)))
	finally (return count)))


;;; `hard-reclaim-all-irregular-size-reclaimed-stored-rasters'
;;; reclaims all rasters in irregular raster pools, and
;;; reclaims the pools themselves.

;; hard-reclaim-all-rasters-in-pool is written only for use
;; in this function in order to take some shortcuts and not
;; use avoiding-variable-capture. Note that there are
;; variables in this macro that could be shadowed,
;; arguments are being multiply-evaluated, and that
;; irregular-raster-pool must be a symbol because it is
;; never fully evaluated.

(defun hard-reclaim-all-irregular-size-reclaimed-stored-rasters (gensym-window)
  (macrolet ((hard-reclaim-all-rasters-in-pool (irregular-raster-pool g-window)
	       `(let ((count 0)
		      (pool-vector (,irregular-raster-pool ,g-window)))
		  (loop for raster-info? =
			(graphics-pop pool-vector)
			while raster-info?
			do (incff count)
			   (c-x11-reclaim-pixmap (raster-info-raster raster-info?))
			   (reclaim-raster-info raster-info?)
			finally (reclaim-graphics-list pool-vector))
		  (setf (,irregular-raster-pool ,g-window) nil)
		  count)))
    (+f (hard-reclaim-all-rasters-in-pool
	  irregular-size-bitmap-raster-pool gensym-window)
	(hard-reclaim-all-rasters-in-pool
	  irregular-size-pixmap-raster-pool gensym-window))))




;;; Depth-for-bitmap-raster-p is true if bits-per-pixel is the right number for
;;; a bitmap raster, as opposed to a pixmap raster.  (This should be used in
;;; preference to the usual "(=f bits-per-pixel 1)" test.)

(defmacro depth-for-bitmap-raster-p (bits-per-pixel)
  `(<=f ,bits-per-pixel 1))

;; We assume that all rasters with depth greater than one are of depth equal
;; to the screen depth.





;;; The function `find-irregular-size-stored-raster' loops through the list of
;;; irregular size rasters and attempts to find a raster which will match the
;;; requested size.  This function is slow, but it is ok because the raster
;;; that it is allocating is large, and operations on the raster are expected
;;; to be slow as well.  Thus, the search will not take up a big percentage of
;;; the time spent on the raster.

(defun find-irregular-size-stored-raster
    (gensym-window minimum-width minimum-height bits-per-pixel)
  (let* ((irregular-size-raster-pool
	   (if (depth-for-bitmap-raster-p bits-per-pixel)
	       (irregular-size-bitmap-raster-pool gensym-window)
	       (irregular-size-pixmap-raster-pool gensym-window)))
	 (the-stored-raster? nil))
    (when irregular-size-raster-pool
      (loop with trailer? = nil
	    with rest-of-pool = irregular-size-raster-pool
	    as raster-info = (car rest-of-pool)
	    do (when (and (=f (raster-info-width raster-info) minimum-width)
			  (=f (raster-info-height raster-info) minimum-height))
		 (setq the-stored-raster?
		       (raster-info-raster raster-info))
		 (reclaim-raster-info raster-info)
		 (loop-finish))
	       (setq trailer? rest-of-pool)
	       (setq rest-of-pool (cdr rest-of-pool))
	    while rest-of-pool
	    finally
	      (when the-stored-raster?
		(if trailer?
		    (setf (cdr trailer?) (cdr rest-of-pool))
		    (if (depth-for-bitmap-raster-p bits-per-pixel)
			(setf (irregular-size-bitmap-raster-pool gensym-window)
			      (cdr irregular-size-raster-pool))
			(setf (irregular-size-pixmap-raster-pool gensym-window)
			      (cdr irregular-size-raster-pool))))
		(reclaim-graphics-cons rest-of-pool))))
    (cond (the-stored-raster?
	   (clear-stored-raster
	     the-stored-raster?
	     (stored-raster-type-for-window gensym-window)
	     minimum-width minimum-height))
	  (t
	   (values (create-stored-raster
		     gensym-window minimum-width minimum-height
		     bits-per-pixel t)
		   t)))))

;; We could optimize retrieval from the irregular pool by keeping the pool
;; sorted in some order.







;;; The substitution macro `allocate-irregular-size-stored-raster' allocates
;;; an irregular raster for a gensym window, with the minimum width, height, and
;;; depth specified.  An irregular raster is a raster that has width or
;;; height greater than those in list-of-regular-raster-sizes.

(def-substitution-macro allocate-irregular-size-stored-raster
			(gensym-window minimum-width minimum-height bits-per-pixel)
  (find-irregular-size-stored-raster
    gensym-window minimum-width minimum-height bits-per-pixel))




(defun allocate-stored-raster
       (gensym-window minimum-width minimum-height
	bits-per-pixel make-exact-size-p)
  (if current-scratchpad-raster-tiled-p
      (multiple-value-bind (width height)
	  (raster-dimensions-given-max-and-offset
	    minimum-width
	    minimum-height
	    current-x-max-for-stored-raster?
	    current-x-offset-for-stored-raster?
	    current-y-max-for-stored-raster?
	    current-y-offset-for-stored-raster?)
	(allocate-tiled-raster
	    gensym-window 
	    width
	    height
	    bits-per-pixel))
      (allocate-stored-raster-1
	gensym-window minimum-width minimum-height
	bits-per-pixel make-exact-size-p)))



;;; `raster-dimensions-given-max-and-offset' mirrors the
;;; computation of icon width and height in
;;; allocate-stored-raster. 

(defun raster-dimensions-given-max-and-offset
    (width height
     x-max-for-stored-raster? x-offset-for-stored-raster?
     y-max-for-stored-raster? y-offset-for-stored-raster?)
  (if x-offset-for-stored-raster?  ; if region defined
      (values (-r x-max-for-stored-raster? 
		  x-offset-for-stored-raster?)
	      (-r y-max-for-stored-raster? 
		  y-offset-for-stored-raster?))
      (values width height)))

;; I don't know how to tell whether a raster on G2 is
;; tiled or not. Punting for now. 



;;; The function `allocate-stored-raster-1' allocates a stored raster of the
;;; minimum width, height, and depth.  It either obtains the stored raster from
;;; the pool of rasters available if there is a match, or it will allocate a
;;; raster from the lisp and/or the OS.  If make-exact-size-p is true, then
;;; this tries to come as close as possible to the exact size specified.  (In
;;; some implementations this may not be strictly possible.  On Lisp machines,
;;; for example, raster widths must be a multiple of 32.)
;;;  The second returned value is T iff the raster was newly allocated.

(defun allocate-stored-raster-1
    (gensym-window minimum-width minimum-height
		   bits-per-pixel make-exact-size-p)
  #+development
  (incff number-of-stored-rasters-allocated)
  (with-regular-stored-raster-size (minimum-width minimum-height)
    (if (or (<f current-regular-raster-width-index 0)
	    (<f current-regular-raster-height-index 0)
	    (and make-exact-size-p
		 (not
		   (and (=f minimum-width current-regular-raster-width)
			(=f minimum-height current-regular-raster-height)))))
        (let ((do-not-error-in-x11-create-pixmap-on-failed-allocation
		(or (< minimum-width 0) (< minimum-height 0))))
	  (allocate-irregular-size-stored-raster
	    gensym-window minimum-width minimum-height bits-per-pixel))
	;; exact size not required:
	(let* ((pool
		 (if (depth-for-bitmap-raster-p bits-per-pixel)
		     (regular-size-bitmap-raster-pools gensym-window)
		     (regular-size-pixmap-raster-pools gensym-window)))
	       (stored-raster?
		 (graphics-pop
		   (small-2d-aref pool
				  current-regular-raster-width-index
				  current-regular-raster-height-index))))
	  (cond (stored-raster?
		 ;; Why not clear the whole thing?
		 (clear-stored-raster
		   stored-raster?
		   (stored-raster-type-for-window gensym-window)
		   minimum-width minimum-height))
		(t
		 (values (create-stored-raster
			   gensym-window
			   current-regular-raster-width
			   current-regular-raster-height
			   bits-per-pixel nil)
			 t)))))))


;;; The function `allocate-bigger-stored-raster' tries to find a regular or
;;; irregular-sized raster that's bigger than would be found by
;;; allocate-stored-raster-1 when called with the same arguments.  Presumably
;;; this is called because allocate-stored-raster-1 failed hard to allocate a
;;; raster.  Its result is the same as that of allocate-stored-raster-1 except
;;; that a returned raster result will be bigger than minimum-width and
;;; minimum-height, and it will try not to allocate a new raster unless it is
;;; absolutely unavoidable because there are no larger rasters in any of the
;;; pools.

(defun allocate-bigger-stored-raster
    (gensym-window minimum-width minimum-height bits-per-pixel)
  (loop with pool-vector
	  = (if (depth-for-bitmap-raster-p bits-per-pixel)
		(regular-size-bitmap-raster-pools gensym-window)
		(regular-size-pixmap-raster-pools gensym-window))
	with max-index		; per 2d-array doc (& code)
	  = maximum-managed-simple-vector-size
	for bigger-index
	from (+f (with-regular-stored-raster-size
		     (minimum-width minimum-height)
		   (convert-2d-array-indexes-to-index
		     current-regular-raster-width-index
		     current-regular-raster-height-index))
		 1)
	    below max-index
	as bigger-stored-raster?
	   = (graphics-pop (svref pool-vector bigger-index))
	when bigger-stored-raster?
	  do (clear-stored-raster
	       bigger-stored-raster?
	       (stored-raster-type-for-window gensym-window)
	       minimum-width minimum-height)
	     (return bigger-stored-raster?)
	finally
	  ;; can't find regular size; now try to get an irregular-sized stored
	  ;; raster.  Note: if it fails to find one in pools, it will try one
	  ;; more time to create it, which we expect to fail, but we can't do
	  ;; anything better anyway.
	  (return
	    (find-irregular-size-stored-raster
	      gensym-window minimum-width minimum-height bits-per-pixel))))



;;; The function `stored-raster-in-regular-pool?' returns T if there is a
;;; regular-sized stored raster in the pool of the given width, height, and
;;; depth.

(defun stored-raster-in-regular-pool? (gensym-window width height depth)
  (with-regular-stored-raster-size (width height)
    (when (and (>=f current-regular-raster-width-index 0)
	       (>=f current-regular-raster-height-index 0))
      (let* ((pool
	       (if (depth-for-bitmap-raster-p depth)
		   (regular-size-bitmap-raster-pools gensym-window)
		   (regular-size-pixmap-raster-pools gensym-window)))
	     (list
	       (small-2d-aref
		 pool
		 current-regular-raster-width-index
		 current-regular-raster-height-index)))
	(not (null list))))))




;;; `Hard-reclaiming' refers to getting down to the process
;;; that actually stores the memory for the raster, and
;;; telling it to reclaim the raster.  The layer below this
;;; (typically X11-window) cannot always hard-reclaim
;;; rasters.  But when it can, and the parameter
;;; `prefer-to-hard-reclaim-irregular-sized-rasters-p' is
;;; true, then irregular sized stored rasters are reclaimed
;;; in this way.  Note that the memory may be quite
;;; separate from the virtual memory of the TW (or G2)
;;; process, even on a separate computer, e.g., in the X
;;; Window System in the case where an X display is on a
;;; physically different computer running an X server ("tw
;;; -display my-remote-host:0.0").  Note also that
;;; hard-reclaiming may be expected to be quite slow, and
;;; may conceivably, in fact, HANG the system for a
;;; noticeable length of time in some unlikely cases.  On
;;; X, for example, a round-trip is needed to and from the
;;; G2/TW process to the X server process.

(defparameter prefer-to-hard-reclaim-irregular-sized-rasters-p nil)

;; Even if this turns out to be a good ticket for some customers, consider
;; making this be off by default but a command line option.  G2 has run quite
;; acceptably without hard-reclaiming during at least 1997-1998 for the
;; overwhelming majority.  Reread the note on HANGING above.  This is not tested
;; (in the "on" mode) as of this writing.  Note that irregular sized rasters
;; are very rarely used in G2.  (MHD 8/16/98)



;;; The function `reclaim-irregular-size-stored-raster' reclaims
;;; a raster that does not have one of the standard sizes as specified in
;;; list-of-regular-raster-sizes.  The width, height, and depth given
;;; to it must be exactly those given to allocate-irregular-size-stored-raster
;;; when the stored raster was allocated.

(defun-simple reclaim-irregular-size-stored-raster
    (stored-raster-to-be-reclaimed
      gensym-window
      minimum-width minimum-height bits-per-pixel)
  (or
    (if prefer-to-hard-reclaim-irregular-sized-rasters-p
	(case (type-of-gensym-window gensym-window)
	  (x11-window
	   (c-x11-reclaim-pixmap stored-raster-to-be-reclaimed)
	   t)))
    (let* ((raster-info
	     (make-raster-info
	       minimum-width minimum-height
	       stored-raster-to-be-reclaimed bits-per-pixel)))
      (if (depth-for-bitmap-raster-p bits-per-pixel)
	  (setf (irregular-size-bitmap-raster-pool gensym-window)
		(graphics-cons
		  raster-info
		  (irregular-size-bitmap-raster-pool gensym-window)))
	  (setf (irregular-size-pixmap-raster-pool gensym-window)
		(graphics-cons
		  raster-info
		  (irregular-size-pixmap-raster-pool gensym-window)))))))



;;; The function `reclaim-stored-raster' reclaims a stored raster.  The width,
;;; height, and depth given to it must be exactly those given to allocate-
;;; stored-raster when the stored raster was allocated.

(defun-simple reclaim-stored-raster
       (stored-raster-to-be-reclaimed
	gensym-window minimum-width minimum-height
	bits-per-pixel made-exact-size-p)
  (if (tiled-raster-p stored-raster-to-be-reclaimed)
      (reclaim-tiled-raster stored-raster-to-be-reclaimed)
      (reclaim-stored-raster-1
	stored-raster-to-be-reclaimed
	gensym-window minimum-width minimum-height
	bits-per-pixel made-exact-size-p)))

(defun-simple reclaim-stored-raster-1
       (stored-raster-to-be-reclaimed
	gensym-window minimum-width minimum-height
	bits-per-pixel made-exact-size-p)
  #+development
  (decff number-of-stored-rasters-allocated)  
  (with-regular-stored-raster-size (minimum-width minimum-height)
    (if (or (<f current-regular-raster-width-index 0)
	    (<f current-regular-raster-height-index 0)
	    (and made-exact-size-p
		 (not
		   (and (=f minimum-width current-regular-raster-width)
			(=f minimum-height current-regular-raster-height)))))
	(reclaim-irregular-size-stored-raster
	  stored-raster-to-be-reclaimed
	  gensym-window minimum-width minimum-height bits-per-pixel)
	(let* ((raster-pools
		 (if (depth-for-bitmap-raster-p bits-per-pixel)
		     (regular-size-bitmap-raster-pools gensym-window)
		     (regular-size-pixmap-raster-pools gensym-window)))
	       (result
		 (graphics-cons
		   stored-raster-to-be-reclaimed
		   (small-2d-aref
		     raster-pools
		     current-regular-raster-width-index
		     current-regular-raster-height-index))))
	  (setf (small-2d-aref				    ; graphics-push
		  raster-pools
		  current-regular-raster-width-index
		  current-regular-raster-height-index)
		result)
	  result))))








;;; `Make-n-rasters-then-reclaim' is useful for testing whether raster
;;; allocation is slowing down.

#+development
(defun make-n-rasters-then-reclaim (n)
  (let (begin-time end-time raster-list)
    (setq begin-time (get-fixnum-time))
    (setq raster-list
	  (loop for i from 1 to n
		collect (create-stored-raster system-window 10 10 1 nil)))
    (loop for raster in raster-list
	  do (reclaim-stored-raster raster system-window 10 10 1 nil))
    (setq end-time (get-fixnum-time))
    (format t "seconds elapsed = ~s~%" 
	    (/ (fixnum-time-difference end-time begin-time)
			  fixnum-time-units-per-second-as-a-float))))




;;;; Raster Tiling

;;; Raster tiling is a technique for improving memory efficiency related to raster 
;;; allocation.  It can, and should, be used for all things that use rasters
;;; including icons, graphs, charts, and fonts.  

;;; The basic idea is to limit the number of different sizes for rasters to a
;;; small number.  This allows for a small number of pools which will tend to be
;;; well utilized.  This is far better because the statistical likelihood that a
;;; raster can be used again after it is reclaimed diminishes as the number of
;;; sizes grows.  Thus, with a large number of pools, rasters tend to fester in
;;; the pools which typically grow larger and larger as G2 is used resulting
;;; eventually in running out of memory.

;;; If the area required is larger than the largest standard-sized raster, several
;;; rasters (or tiles) are used to fulfill the requirement.  

;;; The drawback of fewer pools is that there will typically be more wasted space;
;;; rasters will typically fit the required area less closely than when there are
;;; more pools.  This can be mitigated by wisely choosing the sizes of the tiles to
;;; use in a particular case.  The approach taken here is to choose a combination
;;; that is optimal, subject to some constraints (tiles must be the same size 
;;; for example).  The constraints simplify the algorithm which chooses the tiles,
;;; and they also allow for efficient methods of deciding which tiles need to be
;;; painted.  While it is tempting to develop more sophisticated algorithms 
;;; which determine an absolutely optimum combination of tiles, this is probably not
;;; worth it as the approach taken here works well (provides a big improvement
;;; over using many pools) while keeping a reasonable bound on the worst case
;;; waste of pixels. 



;;; Allocation of Tiles

;;; Many factors can be used to decide which tiles to allocate to cover a required
;;; raster area, including, number of pixels wasted, number of tiles needed (the
;;; fewer the better), and tiles available in pools.

;;; The following scheme makes some simplifying assumptions.  First, there is no
;;; consideration of tiles available in pools.  This has the advantage in that a
;;; required area will always be allocated the same combination of tiles.  Since
;;; there are fewer pools anyway, it is likely that tiles of the needed sizes will
;;; be available, or, if they are not available, it is worthwhile to allocate them
;;; since they will probably be reused after they are reclaimed.  The second
;;; simplifying assumption is that the tiles are all square.  This is simply the
;;; statistical optimum given that there are few pools and that there is no known
;;; bias for rasters of a particular size or shape.  Finally, it is assumed that
;;; the tile edge size increment is a factor of 2.  Thus, the pools could be
;;; allocated to contain the following tile edge sizes: 16, 32, 64, 128, 256, 512.

;;; A final simplifying assumption is made now, for purposes of discussion: all
;;; tiles allocated for a particular raster are of the same size.  This final
;;; assumption greatly simplifies the rules for allocating the tiles.  It also
;;; simplifies the computation for identifying tiles involved when painting
;;; graphics primitives (see below).  The formula for computing the area occupied
;;; by the tiles is

;;; (* (ceiling width-required d) d (ceiling height-required d) d)

;;; where d is the size of tiles used.  This can be compared with the area
;;; required (* width-required height-required) to determine the area (number of
;;; pixels) wasted.

;;; Given the above simplifying assumptions, the rules for deciding which tile
;;; size to use are as follows:

;;; 1.  choose the smaller of width and height as the "minimum required size";
;;; 2.  use the smallest tile size which is just larger than the minimum required;
;;; 3.  if the minimum required size > the largest tile size, use the largest;

;;; It is now useful to analyze the pixel utilization for this scheme.  Due to the
;;; above rules, there is actually a small number of ways that tiles can be
;;; allocated (given that the required raster fits within the largest tile).
;;; Thus, rectangles where one dimension is within double the size of the other
;;; will always be covered by a single tile.  Rectangles where one dimension is
;;; more than double the other will require more than one tile.  The possible
;;; cases are enumerated below (d is the tile size).

;;; Square (single tile) 
;;;
;;;    -----
;;;    |   |
;;;    |   |
;;;    -----
;;;
;;; 0.5 * d < w, h <= d 
;;; avg. for w, h = 0.75 * d
;;; avg. area = 0.5625 * d ^ 2
;;; tile area = d ^ 2
;;; utilization = 0.5625

;;; Rectangular (two tiles, horizontally or vertically stacked)
;;;
;;;    ---------
;;;    |   |   | 
;;;    |   |   |
;;;    ---------
;;;
;;; 0.5 * d < h <= d, d < w <= 2 * d  
;;; avg. for h = 0.75 * d, avg. for w = 1.5 * d
;;; avg. area = 1.125 * d ^ 2
;;; tile area = 2 * d ^ 2
;;; utilization = 0.5625

;;; Rectangular (three tiles)
;;;
;;;    -------------
;;;    |   |   |   |
;;;    |   |   |   |
;;;    -------------
;;;
;;; 0.5 * d < h <= d, 2 * d < w <= 3 * d  
;;; avg. for h = 0.75 * d, avg. for w = 2.5 * d
;;; avg. area = 1.875 * d ^ 2
;;; tile area = 3 * d ^ 2
;;; utilization = 0.625

;;; Rectangular (n tiles)
;;;
;;;    -------------
;;;    |   |   |   |  ... 
;;;    |   |   |   |
;;;    -------------
;;;
;;; 0.5 * d < h <= d, (n - 1) * d < w <= n * d  
;;; avg. for h = 0.75 * d, avg. for w = (n - 0.5) * d
;;; avg. area = (0.75 * n - 0.375) * d ^ 2
;;; tile area = n * d ^ 2
;;; utilization = 0.75 - 0.375 / n

;;; Thus, utilization is about between 1/2 and 3/4.  The averages could also be
;;; computed using calculus double integrals, but since everything here is simple
;;; rectangles, the averages can be computed just by inspection.



;;; Identifying Tiles Involved when Painting Graphics Primitives

;;; Tiles are painted by painting a graphic primitive directly onto the tile, just
;;; as for any ordinary raster.  Clipping is done if the graphic primitive crosses
;;; a border of a tile (just as in the icon editor).  This approach was chosen
;;; over the approach of using the scratchpad raster mechanism for speed
;;; efficiency reasons.  The scratchpad raster approach involves first painting a
;;; scratchpad raster, then bitblting regions of the raster into stored tiles.
;;; This would mean that an extra set of bitblts (beyond bitblting to the screen)
;;; would be necessary for icons and charts, and two extra sets of bitblts would
;;; be necessary for scrolling graph updates (one to load the tiles into the
;;; scratchpad raster, one to store them out again).  In addition to these
;;; efficiency issues, there is a problem in that a single raster has a fixed size
;;; limit on some machines.  Therefore, it is better not to use a scratchpad
;;; raster and paint directly into the tiles.

;;; For any graphic primitive except for circles and arcs, it is easy to compute a
;;; "bounding rectangle" which can be used to possibly reduce the number of tiles
;;; that have to be painted; any tile upon which the bounding rectangle lies must
;;; be painted (see Fig.  1 below).  For example, when painting a vertical line,
;;; it will often be the case that only one of the tiles need be painted.  For
;;; circles and arcs, the painting is done for all the tiles, even though many of
;;; them may not be affected at all (consider improving this by somehow noting
;;; boundaries the first time the circle or arc is drawn, if this is possible).



;;; ----------------
;;; |    |    |    |
;;; |  bbbb   |    |
;;; ---bbbb---------
;;; |  bbbb   |    |
;;; |    |    |    |
;;; ----------------
;;; |    |    |    |
;;; |    |    |    |
;;; ----------------

;;; Fig.  1 - The four tiles in the upper left corner need to be painted (b's
;;; indicate the bounding rectangle).



;;; No attempt is made to identify "holes" in the bounding rectangle, in order to
;;; optimize for polygons that have interiors which do not affect some tiles.
;;; Also, no attempt is made to be completely optimal about diagonal lines; the
;;; bounding rectangle is based on the endpoints.  Thus, this can result in the
;;; bounding rectangle lying on some tile which is not crossed by the line itself.

;;; The computation for indentifying tiles to be painted should be fast,
;;; especially since it is desireable to eventually allow for change of icon size
;;; and orientation under rule control.  The key to speed efficiency in
;;; identifying tiles is to avoid having to test each individual tile to see if
;;; the bounding rectangle crosses it.  This is accomplished most easily if the
;;; tiles are all the same size.  Thus, to find the column of tiles upon which the
;;; left edge of a bounding rectangle lies, simply divide the left edge by the
;;; width of the tiles used and round up.  Note that the restriction on fixed size
;;; tiles can be relaxed, while maintaining this basic technique, if it is assumed
;;; that only tiles in the final column (and row) are of a different size than all
;;; the other tiles.  Thus, the function determine-tiles-to-paint, which takes the
;;; edges of the bounding rectangle as arguments and returns a gensym list of
;;; raster tiles, is straightforward.

;;; The restriction on using tiles all of the same size leads to inefficiencies
;;; both due to the fact that more pixels are usually wasted due to less of an
;;; exact fit, and due to the fact that new rasters may have to be allocated,
;;; rather than using existing rasters of a different size in some pool.  However,
;;; these efficiencies are relatively minor and are outweighed by the benefits of
;;; using homogeneous sized tiles.

;;; Tiled Rasters

;;; A `tiled-raster' is a structure containing: 1) a managed array of
;;; managed arrays which holds the rasters, and 2) a fixnum indicating
;;; the tile size.  This could be extended eventually, if desired, so
;;; that the managed arrays hold "raster tiles" rather than rasters,
;;; where a raster tile is a structure containing the raster and the
;;; raster's width and height.


(defun allocate-tiled-raster
    (gensym-window required-width required-height bits-per-pixel)
  (let ((tiled-raster (make-tiled-raster)))
    (setf (gensym-window-for-tiled-raster tiled-raster) gensym-window
	  (bits-per-pixel-for-tiled-raster tiled-raster) bits-per-pixel
	  (tile-arrays tiled-raster) (make-tile-arrays 
				       tiled-raster gensym-window
				       required-width required-height
				       bits-per-pixel t))
    tiled-raster))


;;; The function `allocate-just-tiled-raster' allocate a tiled-raster
;;; array but not any of the individual tiles.  It used by image renderings,
;;; which store their own things into the tiles.

(defun allocate-just-tiled-raster
    (gensym-window required-width required-height bits-per-pixel singleton-p)
  (let ((tiled-raster (make-tiled-raster)))
    (setf (gensym-window-for-tiled-raster tiled-raster) gensym-window
	  (bits-per-pixel-for-tiled-raster tiled-raster) bits-per-pixel
	  (tile-arrays tiled-raster) (if singleton-p
					 (make-singleton-tile-array tiled-raster required-width)
					 (make-tile-arrays
					   tiled-raster gensym-window
					   required-width required-height
					   bits-per-pixel nil)))
    tiled-raster))


;;; The function `make-singleton-tile-array' creates a tiled-raster with just
;;; one tile.  It is needed for tiled workspace backgrounds.

(defun make-singleton-tile-array (tiled-raster size)
  (let ((row-array (allocate-managed-array 1))
	(row (allocate-managed-array 1)))
    (setf (managed-svref row-array 0) row
	  (managed-svref row 0) nil
	  (tile-size tiled-raster) size
	  (tile-size-index tiled-raster) 0) ; Never used.
    row-array))


(defun make-tile-arrays
    (tiled-raster gensym-window required-width required-height
		  bits-per-pixel allocate-rasters?)
  (declare (ignore bits-per-pixel)) ; See note 1
  (let (tile-size tile-size-index number-of-rows number-of-columns
		  row-array)
    (multiple-value-setq (tile-size tile-size-index)
      (compute-tile-size-given-required-area required-width required-height))

    (setf (tile-size tiled-raster) tile-size
	  (tile-size-index tiled-raster) tile-size-index)
    (multiple-value-setq (number-of-rows number-of-columns)
      (compute-rows-columns-given-tile-size
	tile-size required-width required-height))
    (setq row-array (allocate-managed-array number-of-rows))

    (loop for i from 0 below number-of-rows 
	  as row = (allocate-managed-array number-of-columns)
	  do
      (setf (managed-svref row-array i) row)
      (loop for j from 0 below number-of-columns do
	(setf (managed-svref row j)
	      (if allocate-rasters?
		  ;used to call allocate-stored-raster-1.
		  (allocate-scratchpad-raster
		    gensym-window tile-size tile-size
		    #'reclaim-all-scaled-fonts))))) ; See note 2
    row-array))

;; Note 1: It seems that all images use bitmaps of depth
;; one in G2, so its safe to ignore bits-per-pixel for now,
;; but we could fix
;; allocate-scratchpad-raster to take
;; bits-per-pixel. lgibson 10/17/98

;; Note 2: reclaim-all-scaled-fonts is the procedure to use
;; when the OS has run out of bitmaps. The reason we
;; reclaim fonts when failing to allocate an icon bitmap is
;; that this code runs on TW, and fonts are available to
;; reclaim from TW. Icons can only be reclaimed from G2
;; (and appropriate commands sent to TW). G2 decaches icon
;; renderings (which sends icon bitmaps to the window
;; pool), then TW can give back all reclaimed bitmaps to
;; the OS.

;; This could be made more efficient by separating out the code in
;; allocate-stored-raster which allocates from pools into a separate
;; function.  This function could be called directly here, thus
;; by-passing the preliminary code in allocate-stored-raster.



(defun compute-rows-columns-given-tile-size
    (tile-edge-size-in-pixels required-width required-height)
  (values (ceilingr required-height tile-edge-size-in-pixels)
	  (ceilingr required-width tile-edge-size-in-pixels)))



(defmacro tiled-raster-tile (tiled-raster x y)
  `(managed-svref (managed-svref (tile-arrays ,tiled-raster) ,y) ,x))


;;; The macro `tiled-raster-width' returns the number of TILES wide
;;; the raster is, NOT pixels.

(defmacro tiled-raster-width (tiled-raster)
  `(let ((row (tile-arrays ,tiled-raster)))
     (cond ((>f (managed-array-length row) 0)
	    (managed-array-length (managed-svref row 0)))
	   (t
	    0))))

(defmacro tiled-raster-height (tiled-raster)
  `(managed-array-length (tile-arrays ,tiled-raster)))


(defmacro do-raster-tiles ((tile x y tiled-raster) &body body)
  (let ((tiled-raster-var (make-symbol "TILED-RASTER")))
    `(let* ((,tiled-raster-var ,tiled-raster))
       (loop for ,x below (tiled-raster-width ,tiled-raster-var)
	     doing
	 (loop for ,y below (tiled-raster-height ,tiled-raster-var)
	       for ,tile = (tiled-raster-tile ,tiled-raster-var ,x ,y)
	       doing
	   ,@body)))))


(defun-simple reclaim-tiled-raster (tiled-raster)
  (let* ((tile-arrays (tile-arrays tiled-raster))
	 (number-of-rows (tiled-raster-height tiled-raster))
	 (number-of-columns (tiled-raster-width tiled-raster))
	 (gensym-window (gensym-window-for-tiled-raster tiled-raster))
	 (bits-per-pixel (bits-per-pixel-for-tiled-raster tiled-raster))
	 (tile-size (tile-size tiled-raster)))
    (loop for i from 0 below number-of-rows 
	  as row = (managed-svref tile-arrays i) 
	  do
      (loop for j from 0 below number-of-columns
	    as stored-raster? = (managed-svref row j)
	    do
	(when stored-raster?
	  (reclaim-stored-raster-1 stored-raster?
				   gensym-window
				   tile-size tile-size bits-per-pixel nil)))
      (reclaim-managed-array row))
    (reclaim-managed-array tile-arrays))
  (reclaim-tiled-raster-internal tiled-raster))


;;; `compute-tile-size-given-required-area' takes width and
;;; height in pixels. Tiles are drawn using rasters which
;;; come in a fixed number of sizes (see
;;; list-of-regular-raster-sizes). The tile size is based
;;; on the min of width and height: many tiles may be used
;;; to draw this one area. Tiles are square, so the
;;; returned size is the length of the edge in pixels. 

(defun compute-tile-size-given-required-area (required-width required-height)
  (let (larger-dimension smaller-dimension minimum-required-size
	size index)
    (if (>r required-width required-height)
	(setq larger-dimension required-width
	      smaller-dimension required-height)
	(setq larger-dimension required-height
	      smaller-dimension required-width))
    (setq minimum-required-size
	  (maxr (ceiling larger-dimension 4)
		smaller-dimension
		#.minimum-tile-size-for-icons))
    (multiple-setq-to-regular-size-and-index 
      (size index) minimum-required-size)
    (when (<f index 0)
      (setq size #.largest-regular-raster-size
	    index #.largest-regular-raster-size-index))
    (values size index)))

;; The (ceiling larger-dimension 4) limit is used to avoid allocations
;; of many small tiles when one dimension is much larger than the other.
;; Many small tiles can be inefficient since this can cause graphic
;; elements to be painted many times (if they span a significant number
;; of the tiles).



;;; The macro `iterate-over-tiles-to-be-painted' claims a bunch of
;;; local variable names: tile-size, tile-arrays, etc.

(defmacro iterate-over-tiles-to-be-painted
	  ((left-edge-of-paint top-edge-of-paint 
	    right-edge-of-paint bottom-edge-of-paint tiled-raster)
	   &body paint-body)
  (let ((tiled-raster-var (gensym)))
    `(let* ((,tiled-raster-var ,tiled-raster)
	    (tile-size (tile-size ,tiled-raster-var))
	    (tile-arrays (tile-arrays ,tiled-raster-var))
	    (number-of-rows-1
	      (-f (managed-array-length tile-arrays) 1))
	    (number-of-columns-1 
	      (-f (managed-array-length 
		    (managed-svref tile-arrays 0)) 1))
	    (left-edge-column
	      (minr
		(maxr (floorf-positive,left-edge-of-paint tile-size) 0)
		number-of-columns-1))
	    (top-edge-column 
	      (minr 
		(maxr (floorf-positive ,top-edge-of-paint tile-size) 0)
		number-of-rows-1))
	    (right-edge-column 
	      (minr
		(maxr
		  (floorf-positive (-r ,right-edge-of-paint 1) tile-size)
		  left-edge-column)
		number-of-columns-1))
	    (bottom-edge-column 
	      (minr
		(maxr
		  (floorf-positive (-r ,bottom-edge-of-paint 1) tile-size)
		  top-edge-column)
		number-of-rows-1))
	    tile-to-paint)
       (loop for i from top-edge-column to bottom-edge-column do
	 (loop for j from left-edge-column to right-edge-column do
	   (setq tile-to-paint
		 (managed-svref 
		   (managed-svref tile-arrays i) j))
	   ,@paint-body)))))

;; Changed floorf to floorf-positive, -fmw, 12/14/94.

;; Note that it is crucial that array bounds be checked (using
;; managed-array-length).  When making the rendering structure for icons
;; with many regions, it is possible for "large" graphic elements to be
;; painted onto "small" regions for "burning".  The coordinates of the
;; graphic elements can easily exceed the limits of the region.



;(defmacro iterate-over-all-tiles
;	  ((tiled-raster)
;	   &body paint-body)
;  (let ((tiled-raster-var (gensym)))
;    `(let* ((,tiled-raster-var ,tiled-raster)
;	    (tile-arrays (tile-arrays ,tiled-raster-var))
;	    tile-to-paint)
;       (loop for i from 0 below (managed-array-length tile-arrays)
;	     as row = (managed-svref tile-arrays i)
;	     do
;	 (loop for j from 0 below (managed-array-length row) do
;	   (setq tile-to-paint (managed-svref row j))
;	   ,@paint-body)))))
;; Not currently used.

(defmacro with-coordinates-adjusted-for-region
	  (x-coordinates y-coordinates &body body)
  (avoiding-variable-capture (&aux temp)
    `(let ((,temp current-x-offset-for-stored-raster?))
       (when current-x-offset-for-stored-raster?	; if region is defined
	 ,@(loop for x-coordinate in x-coordinates 
		 collect
		 (if (symbolp x-coordinate)
		     `(decfr ,x-coordinate ,temp)
		     `(loop for list on ,(cadr x-coordinate)
			    do
			(setf (car list) (decff (car list) ,temp)))))
	 ,@(loop for y-coordinate in y-coordinates 
		 collect
		 (if (symbolp y-coordinate)
		     `(decfr ,y-coordinate current-y-offset-for-stored-raster?)
		     `(loop for list on ,(cadr y-coordinate)
			    do
			(setf (car list) (decf (car list) current-y-offset-for-stored-raster?)))))
	 (setq current-x-offset-for-stored-raster? nil))	; to inhibit further adjusting
       ,@body
       (setq current-x-offset-for-stored-raster? ,temp))))



;; The coordinates are set here rather than rebound, since they don't have to be
;; rebound.

;; The paint functions can call each other recursively so it is important to
;; inhibit further adjusting by binding current-x-offset-for-stored-raster?  to
;; nil.  Note that the convention is to check only the X variable, so binding the y
;; counterpart is unnecessary.  Note also that the variable is actually set on
;; and entry and restored upon exit; that's just to work around the inefficiency
;; of special variable binding in Chestnut (!).

;; X-coordinates and y-coordinates must be lists of symbols.


(defmacro with-coordinates-adjusted-for-tile
	  (x-coordinates y-coordinates i j tile-size &body body)
  `(let* ((x-offset (*r ,j ,tile-size))
	  (y-offset (*r ,i ,tile-size))
	  ,@(loop for x-coordinate in x-coordinates 
		  collect
		  (if (symbolp x-coordinate)
		      `(,x-coordinate (-r ,x-coordinate x-offset))
		      `(,(cadr x-coordinate)
			 (loop for x in ,(cadr x-coordinate)
			       collect (-r x x-offset)
				 using graphics-cons))))
	  ,@(loop for y-coordinate in y-coordinates 
		  collect
		  (if (symbolp y-coordinate)
		    `(,y-coordinate (-r ,y-coordinate y-offset))
		    `(,(cadr y-coordinate)
		       (loop for y in ,(cadr y-coordinate)
			     collect (-r y y-offset)
			     using graphics-cons)))))
     ,@body
     ,@(loop for x-coordinate in x-coordinates 
	     unless (symbolp x-coordinate)
	       collect
	       `(reclaim-graphics-list
		  ,(cadr x-coordinate)))
     ,@(loop for y-coordinate in y-coordinates 
	     unless (symbolp y-coordinate)
	       collect
	       `(reclaim-graphics-list
		  ,(cadr y-coordinate)))))


;; i, j, and tile-size are always assumed to by symbols.



(def-system-variable region-and-tile-x-offset WINDOWS1 0)
(def-system-variable region-and-tile-y-offset WINDOWS1 0)

(defmacro with-offsets-for-region-and-tile
	  (i j tile-size &body body)
  `(let ((region-and-tile-x-offset (*r ,j ,tile-size))
	 (region-and-tile-y-offset (*r ,i ,tile-size)))
     (when current-x-offset-for-stored-raster?
       (setq region-and-tile-x-offset 
	     (+r region-and-tile-x-offset
		 current-x-offset-for-stored-raster?)
	     region-and-tile-y-offset 
	     (+r region-and-tile-y-offset
		 current-y-offset-for-stored-raster?)))
     ,@body))

(defmacro x-with-region-and-tile-offset (x)
  `(-r ,x region-and-tile-x-offset))

(defmacro y-with-region-and-tile-offset (y)
  `(-r ,y region-and-tile-y-offset))





;; Raster Tiling To Do and Notes

;; Calling sequence is as follows (see also bottom of graphs1 for
;; a good summary to telewindows stuff, see also windows3 for
;; doc on decaching).

;; -> draw-icon
;; -> draw-icon-rendering
;; -> draw-graphic-element
;; -> project-graphic-element
;; -> project-graphic-element-per-stack-of-image-planes
;; -> project-graphic-element-without-image-plane-occlusion
;; -> project-graphic-element-to-current-window
;; -> add-from-icon-rendering-to-current-window
;; -> make-rendering-structure
;; -> make-region-raster-for-icon
;; -> on-scratchpad-raster
;; -> on-scratchpad-raster-with-depth
;; -> initialize-scratchpad-raster
;; -> allocate-stored-raster
;; -> with-regular-stored-raster-size
;; -> multiple-setq-to-regular-size-and-index 
;;      (accesses list-of-regular-raster-sizes)



;; Allocation - switch is in - for icons, call on-scratchpad-raster
;; with make-tiled-p arg set in make-region-raster-for-icon

;; Painting
;; Look at ICP functions in WINDOWS2.
;; Work should be done on handler side (within these functions, 
;; not outside of them).
;; Look at the following 
;; (called from paint-one-bitmap-for-icon-on-scratchpad-raster)
;; paint-line-in-current-scratchpad-raster,
;; paint-arc-or-circle-in-current-scratchpad-raster,
;; paint-solid-rectangle-in-current-scratchpad-raster,
;; paint-filled-triangle-in-current-scratchpad-raster,
;; paint-point-in-current-scratchpad-raster.
;; Then include code which takes tiling into account.
;; - Done -

;; For the native window case, there are some inefficiencies in some of
;; the paint functions.  Iteration over tiles is done too early; defer
;; until doing the actual paint primitives.  Test to see if this makes a
;; significant difference.

;; Bitblting tiles to screen.
;; add-from-icon-rendering-to-current-window
;; add-from-region-bounds-and-raster
;; add-from-raster-tiles-to-current-window
;; add-from-stored-raster-to-current-window
;; - Done -

;; Make sure that the rasters allocated are actually square, or at least
;; are allocated from the square pools (should be ok).

;; Remove 4 from list of tile sizes.  The memory required to hold the
;; icon rendering far outweighs the 16 pixels.

;; Raster caching doesn't seem to be caching very much for icons.
;; Resurrect test kbs and make players for them.  Put into official test
;; set.

;; Hook up graphs, charts, maybe fonts.  Review
;; on-scratchpad-raster-given-stored-raster.

;; Convert-current-scratchpad-raster-to-stored-raster - the code in this
;; will soon be obsolete.  Comment out.  Actually, consider keeping this
;; around and using the scratchpad raster mechanism for circles and arcs
;; when there are several tiles, but the entire circle can be painted
;; onto a single scratchpad raster.

;; Currently, have not changed list-of-regular-raster-sizes from 2.1
;; value, even though the tile sizes do not increment by a factor of 2.
;; Quick determination of tiles to paint will not be compromised as long
;; as all sizes are same (except, possibly, the last).  These increments
;; could also yield better utilization (do analysis).  Anyway, it would
;; be nice to be able to keep existing pools and use just a subset of
;; them.  Pool sizes could be adjusted later.

;; Check if efficiency of orient-and-scale-and-paint-rounded-rectangle
;; can be improved.  Action buttons are currently very slow to paint.

;; The icon editor currently calls create-icon-description for each
;; little edit move.  This means that during editing, a great number of
;; region rasters can get allocated (most are then reclaimed).  Tiling
;; will improve utilization of these rasters considerably.

;; When on-scratchpad-raster changes, recompile fonts, graphs1, entities,
;; windows1, 2, 3.

;; Test kb is "ma:>agh>raster-tiling-test".



;;;; Sounds, Beeps, etc.


;;; Beep-in-window-1 is a subfunction of the icp message handler for beep-at-
;;; user which should be the only function that uses it. (See TELESTUBS.)  

(defun beep-in-window-1 (gensym-window)
  (case (type-of-gensym-window gensym-window)
    (x11-window
     (c-x11-bell (native-window? gensym-window) 100))))

;; This subsection was moved here from PLATFORMS today because it now depends
;; on gensym-window structure accessors defined in this module, which is later
;; in the loading sequence. (MHD 3/15/90)




;;;; Updating Windows




;;; `Update-window' provides a replacement for using on-window-with-drawing
;;; directly, since on-window-with-drawing is expensive.  This takes a window, a
;;; desired draw area, a function of up to 11 arguments.  It establishes an
;;; on-window-with-drawing and calls ala call-per-number-of-actual-args the
;;; funtion on the arguments.  Note that if the draw area is empty the function
;;; is not called.

(defun-allowing-unwind update-window
    (gensym-window
      left-edge-of-update-area top-edge-of-update-area
      right-edge-of-update-area bottom-edge-of-update-area
      function
      &optional
      (arg1 no-arg) (arg2 no-arg) (arg3 no-arg)
      (arg4 no-arg) (arg5 no-arg) (arg6 no-arg)
      (arg7 no-arg) (arg8 no-arg) (arg9 no-arg)
      (arg10 no-arg) (arg11 no-arg))
  (with-raw-window-transform-and-draw-area (gensym-window)
    (with-nested-draw-area? (left-edge-of-update-area
			      top-edge-of-update-area
			      right-edge-of-update-area
			      bottom-edge-of-update-area
			      function :update-area)
      (on-window-without-drawing (gensym-window)
	(on-window-with-drawing (gensym-window)
	  (call-per-number-of-actual-args
	    funcall-symbol 1 function
	    arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9 arg10 arg11))))))

;;; `update-window-macro'

(defmacro update-window-macro
    (gensym-window-arg
      left-edge-of-update-area top-edge-of-update-area
      right-edge-of-update-area bottom-edge-of-update-area
      function
      &body args)
  (let ((gensym-window (gensym)))
    `(let ((,gensym-window ,gensym-window-arg))
       (with-raw-window-transform-and-draw-area (,gensym-window)
	 (with-nested-draw-area? (,left-edge-of-update-area
				    ,top-edge-of-update-area
				    ,right-edge-of-update-area
				    ,bottom-edge-of-update-area
				    ',function :update-area)
	   (on-window-without-drawing (,gensym-window)
	     (on-window-with-drawing (,gensym-window)
	       (,function ,@args))))))))



;;;; Making Windows Visible



;;; `Make-window-visible' makes a window "visible" if it is not so already, and
;;; if such a concept applies for the particular type of window that
;;; gensym-window is.
;;;
;;; This is only to be used on local input/output windows, i.e., not windows
;;; of type PRINTER or ICP.
;;;
;;; It guarantees that a full refresh event will be generated to get the gensym
;;; window come back and totally refresh the screen.  In this way, one can
;;; reliably change underlying data structures without incremental screen
;;; updates and know that this refresh event will refresh any "invalid" portions
;;; of the screen.
;;;
;;; This must be called for a Gensym window (on all platforms) once and only
;;; once at the beginning of the process, either Telewindows or G2 (AB).
;;;
;;; The strong implementation of this should leave the window invisible until
;;; we're really ready to let the user use it, or we're at least able to animate
;;; it enough to show that we're alive.  At present, the only strong
;;; implementation is for X Window System type windows.  (Note that this is the
;;; only type of system we have: the Windows(tm) version of or products run on
;;; top of a sort of x-windows emulator.)
;;;
;;; The weak implementation of this (for non-X systems) simply calls for the
;;; entire window to be refreshed, on the assumption that it is already visible.
;;;
;;; This can be used to keep a window unexposed until other initializations have
;;; been performed and it's actually ready to display and service the window
;;; interface.

(defun-void make-window-visible (gensym-window)
  (case (type-of-gensym-window gensym-window)
    ((icp printer)			; N/A
     )
    (x11-window
     (c-x11-make-xwindow-visible (native-window? gensym-window)))
    (t					; never happens in practice:
     (when (native-window? gensym-window)
       (enqueue-window-reshape-event
	 (native-window? gensym-window)
	 0
	 (key-code 'window-refresh))))))


;;;; Bitmap debug code



;; Note that G2/TW do not currently (4.1/5/1) use any
;; bitmaps of depth other than 1.


#+development
(defvar all-bitmaps-created
  (make-array maximum-managed-simple-vector-size))

#+development
(defvar all-pixmaps-created
  (make-array maximum-managed-simple-vector-size))


#+development
(defun-simple convert-size-to-index-for-list-of-regular-raster-sizes (size)
  (loop for x in list-of-regular-raster-sizes
	as i from 0
	if (=f x size) return i
	if (>f x size) do
;	    (format t "warning: non-exact size requested: ~d~%" size)
	    (return i)))

;; I think the warning is completely bogus.  Any time you create a raster with
;; exact-size-p, and size is not one of the approved sizes, you get this
;; warning.  This is all just some debugging or metering code anyways, in
;; support of the single function print-decached-bitmaps-for-window, and it
;; appears it has never handled the case of exact-size-p rasters. -fmw, 7/9/02

;; Note: I'm quite sure the warning is not too serious, but I'm not that clear
;; on the importance of the above "non-exact" warning coming up.  (There should
;; be some doc here about it.)
;;
;; Meanwhile, if a KB for which the warning comes up at least in 5.1r5 and
;; 6.0a3, here is one: /gensym/bugkbs/g2-40r3/hq-3430210.kb
;;
;; Simply load it, and when the graphs in it get rendered on the (local) window,
;; you should see the warning.  (MHD 7/27/00)


#+development
(defun-void print-pool-sizes-available (bitmap-pool)
  (loop for x from 0 below 14 do
    (loop for y from 0 below 14 do
      (let ((pool-size (length (small-2d-aref bitmap-pool x y))))
	(if (> pool-size 0)
	    (format t "(~3d, ~3d): ~d~%"
		    (nth x list-of-regular-raster-sizes)
		    (nth y list-of-regular-raster-sizes)
		    pool-size))))))


#+development
(defun print-pools (gensym-window)
  (print-pool-sizes-available (regular-size-bitmap-raster-pools gensym-window)))

;; We should perhaps update all-bitmaps-created when we
;; give back bitmaps to OS so we have a more accurate
;; count.

#+development
(defun-void print-decached-bitmaps-for-window (gensym-window)
  (format t "Bitmaps: allocated, free:~%")
  (loop for x from 0 below 14
	with total-allocated fixnum = 0
	with total-free fixnum = 0
	do
    (loop for y from 0 below 14 do
      (let ((allocated
	      (length (small-2d-aref all-bitmaps-created x y)))
	    (free
	      (length (small-2d-aref (regular-size-bitmap-raster-pools
				       gensym-window) x y))))
	(when (or (>f allocated 0)
		  (>f free 0))
	  (incff total-allocated allocated)
	  (incff total-free free)
	  (format t "(~3d, ~3d): ~4d ~4d~%"
		  (nth x list-of-regular-raster-sizes)
		  (nth y list-of-regular-raster-sizes)
		  allocated
		  free))))
	finally
	  (format t "Totals: ~8d ~4d~%" total-allocated total-free)
	)
  (format t "~%Pixmaps: allocated, free:~%")
  (loop for x from 0 below 14 do
    (loop for y from 0 below 14 do
      (let ((allocated
	      (length (small-2d-aref all-pixmaps-created x y)))
	    (free
	      (length (small-2d-aref (regular-size-pixmap-raster-pools
				       gensym-window) x y))))
	(when (or (>f allocated 0)
		  (>f free 0))
	  (format t "(~3d, ~3d): ~4d ~4d~%"
		  (nth x list-of-regular-raster-sizes)
		  (nth y list-of-regular-raster-sizes)
		  allocated
		  free))))))

#+development
(defun-void note-use-of-pixmap (pixmap-index width height depth)
;  (format nil "creating ~A: (~3d, ~3d)~%"
;	  (if (>f depth 1) "pixmap" "bitmap")
;	  width height)
  (let ((bitmap-index-width		;
	  (convert-size-to-index-for-list-of-regular-raster-sizes width))
	(bitmap-index-depth
	  (convert-size-to-index-for-list-of-regular-raster-sizes height)))
    (if (and bitmap-index-width bitmap-index-depth)
	(gensym-push pixmap-index
		     (small-2d-aref
		       (if (=f depth 1)
			   all-bitmaps-created
			   all-pixmaps-created)
		       bitmap-index-width
		       bitmap-index-depth)))))



;;;; MD5 access
;;; These functions allow access to the RSA MD5 algorithm
;;; One may legitimately ask what MD5 has to do with windows. The answer is
;;; that both are required by both g2 and telewindows and not required by
;;; gsi

(def-gensym-c-function init-indexed-MD5-context
    (:void "g2ext_init_g2_MD5_context")
  ((:fixnum-int index)))

(defmacro init-MD5-context ()
  `(init-indexed-MD5-context 0))

(def-gensym-c-function update-indexed-MD5-context
    (:void "g2ext_update_g2_MD5_context")
  ((:fixnum-int index)
   (:string data-string)))

(def-gensym-c-function update-indexed-MD5-context-wide-internal
    (:void "g2ext_update_g2_MD5_context_wide")
  ((:fixnum-int index)
   (:byte-vector-16 data-string)
   (:fixnum-int length)))

(defmacro update-indexed-MD5-context-wide (index data-string)
  `(update-indexed-MD5-context-wide-internal ,index ,data-string (lengthw ,data-string)))

(defmacro update-MD5-context (data-string)
  `(update-indexed-MD5-context 0 ,data-string))

(defmacro update-MD5-context-wide (data-string)
  `(update-indexed-MD5-context-wide 0 ,data-string))

(def-gensym-c-function finalize-indexed-MD5-context
    (:void "g2ext_finalize_g2_MD5_context")
  ((:fixnum-int index)
   (:string result-string)))

(defmacro finalize-MD5-context (result-string)
  `(finalize-indexed-MD5-context 0 ,result-string))



#+development
(defun print-md5-result (result-string)
  (format t "~% RESULT~%")
  (loop for i from 0 below 16
	with value
	do
    (setq value (char-code (char result-string i)))
    (format t "~2,'0x" value)))

#+development
(defun test-md5 ()
  (let ((test-string "123456789")
	(c-result (make-string 16)))
    (init-MD5-context)
    (update-MD5-context test-string)
    (format t "test with ~a" test-string)
    (finalize-MD5-context c-result)
    (print-md5-result c-result)))
