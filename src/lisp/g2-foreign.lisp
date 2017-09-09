;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module G2-FOREIGN

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; John Hodgkinson

;;; This module is a redesign of a previous foreign function mechanism, which
;;; involved dynamically linking to the G2 image.  The old code is currently
;;; (6/17/91) in MA:>AB>OLD-FOREIGN.LISP.

;; This module is not to be confused with the module OS-FOREIGN, which allows a G2
;; developer (as opposed to a G2 end-user) to call functions written in other
;; languages.



;;;; Foreign Functions

;;; The `foreign function declaration' is available under DEFINITIONS on the
;;; workspace menu.  An example is
;;;    declare foreign function xyz(real, integer, symbol, text) = integer

;;; The foreign function interface has been redesigned to decouple the G2 image
;;; from user-written foreign code.  Previously, foreign functions would
;;; dynamically link G2 with user-written code.  If this code crashed, so did G2.

;;; In the old implementation, foreign functions were collected into an object
;;; file.  The user would issue a "load foreign file" command for a given
;;; pathname.  This would link G2 with the object file so that G2 could call
;;; foreign functions there.  To call a foreign function with a given name, G2
;;; would form a symbol from the name, and follow the function cell of that symbol
;;; to some vendor-specific foreign-function interface code.

;;; In the new implementation, foreign functions are collected into a "foreign
;;; image", which currently (6/18/91) is a stripped-down GSI process linked to the
;;; original foreign object file.  The user issues a "connect to foreign image"
;;; command for a given pathname.  This causes G2 to spawn a process to run the
;;; foreign image if one doesn't already exist for that pathname.  G2 then asks
;;; the foreign image for a list of the functions it has available.  G2 stores
;;; this information in several data structures designed to make calling a foreign
;;; function as fast as possible, while still allowing foreign function
;;; declarations to be edited and type-checked on the fly.  We describe these data
;;; structures in more detail below.

;;; The central registry for all foreign functions known to G2 is a global hash
;;; table named foreign-function-registry.  This table is keyed by the string
;;; that the foreign image uses to name the function.  It is not presently
;;; (6/18/91) keyed by ICP socket.  Foreign function names are matched with the
;;; name-in-foreign-image attribute of an instance of the
;;; foreign-function-declaration class.  The matching is case sensitive.

;;; Each entry in foreign-function-registry is a foreign-function-entry structure.
;;; A foreign-function-entry contains the following slots:
;;;   (1) Foreign-function-name, a text-string.  This permits dynamic edits of
;;;       foreign function declarations.
;;;   (2) Foreign-function-id, a fixnum.  The foreign-function-id is an index
;;;       used by the foreign image to access the foreign function in O(1) time.
;;;   (3) Foreign-function-argument-count, a fixnum.  For error checking.
;;;   (4) Foreign-function-type-list, an icp-list of symbols (each is one of
;;;       integer, real, symbol, or text).  For error checking.
;;;   (5) Foreign-function-return-type, a symbol (one of integer, real, symbol, or
;;;       text).  For error checking.
;;;   (6) Foreign-function-declarations-with-this-name, a list of
;;;       foreign-function-declaration frames whose name-in-foreign-image attribute is
;;;       foreign-function-name.  These are collected here to speed up disconnecting
;;;       from a foreign image.
;;;   (7) Foreign-image-info, a foreign-function-image-info structure.  This
;;;       structure holds pointers to the pathname and the ICP socket associated
;;;       with the foreign image.  It also contains a list of all
;;;       foreign-function-entries contained in the image, for proper cleanup when
;;;       disconnecting from a foreign image.

;;; The user connects to a foreign image by issuing the command "connect to
;;; foreign image".  G2 will spawn a foreign image, then send the ICP message
;;; request-foreign-function-registry to it.  The image responds with a
;;; provide-foreign-function-registry message.  This message provides the values
;;; for slots slots (1) through (5) of the foreign-function-entry.

;;; Slot (6) is filled by walking through all foreign-function-declaration
;;; instances.  This makes connecting to a new foreign image an expensive
;;; operation.  If this turns out to be a problem, we can keep an inverse table
;;; updated by the slot-putter for name-in-foreign-image.

;;; For speed in foreign function calls, each foreign-function-declaration frame
;;; caches the foreign-function-entry directly, instead of using its
;;; name-in-foreign-image attribute as a key into foreign-function-registry each
;;; time a foreign function is called.  This caching is kept consistent every time
;;; a foreign-function-declaration is created, deleted, enabled, or disabled.

;;; The command "disconnect from foreign image" is also available.  This causes
;;; the foreign image to exit and cleans up the various data-structures associated
;;; with that image.  

;;; To keep the foreign function entries consistent during shutdown and
;;; reconnection, G2 maintains a global list called
;;; all-foreign-function-images?.  Each element in this list is a
;;; foreign-function-image-info structure.  The slots of a
;;; foreign-function-image-info structure are:
;;;   (1) foreign-function-entries-for-image
;;;   (2) pathname-of-foreign-image?
;;;   (3) namestring-of-foreign-image
;;;   (4) icp-socket-connecting-to-foreign-image

;;; The foreign-function-entries-for-image slot of the
;;; foreign-function-image-structure permits proper memory management when a
;;; foreign image is shut down.  Each entry on the list is decached from its
;;; associated foreign-function-declaration to avoid corruption.  G2 uses
;;; pathname-of-foreign-image? to determine when a foreign image is being
;;; reconnected to, to avoid spawning the same process over again.
;;; Namestring-in-foreign-image is used in messages to the user.  G2 needs
;;; icp-socket-connecting-to-foreign-image so it can transmit the icp message
;;; kill-foreign-function-server, which does the actual shutdown.

;;; There are tools available to help a user build a foreign image from existing
;;; foreign object files.  Given a bare-bones specification of foreign argument
;;; and return types, users would like to produce extension code that can be
;;; linked with their old foreign object files to form a foreign image.  The
;;; utility foreign_overlay does this.  The C source is in
;;; ma:>ab>foreign_overlay.c, along with more documentation.




;; To do:

;; Use frame notes instead of notifying the user?  Or use both?
;; Frame notes added.  jh, 6/24/91.

;; Should slot value writers do "default" or "use default" ?  The issue is
;; consistency with GSI.
;; "Use default" added.  jh, 6/23/91.

;; Don't forget to check absent slot putters loading old KBs and looking at both
;; foreign function declarations and at the timing-parameters system table.

;; We should consider implementing a smarter linking strategy than we have at
;; present.  Currently, we always overwrite an identically-named foreign function
;; with a link to the newest image, even if there turns out to be an arglist or
;; return type mismatch with the new image and there wasn't with the old image.
;; For now, we'll hope that users won't be doing too many tricks with
;; identically-named foreign functions.



;;;; G2 Data Structures

;;; The foreign-function-registry hash table

(def-hash-table foreign-function-registry-internal
		:constructor     make-foreign-function-registry
		:accessor        get-foreign-function-entry
		:key-deleter     delete-foreign-function-key
		:key-comparitor  string=w
		:size            131 ; use a prime number
		)

(def-system-variable foreign-function-registry G2-FOREIGN
  (:funcall make-foreign-function-registry))


;; The element-of-foreign-linking-info structure is for various doubly-linked
;; lists that are O(1) when a foreign image or a foreign-function-declaration
;; gets deleted.  This was added for efficiency.  jh, 9/6/91.

(def-structure (element-of-foreign-linking-info
		 (:constructor make-element-of-foreign-linking-info
		   (frame-or-structure-in-foreign-linking-info
		    enclosing-frame-or-structure-in-foreign-linking-info?)))
  (frame-or-structure-in-foreign-linking-info nil)
  (enclosing-frame-or-structure-in-foreign-linking-info? nil)
  (next-element-of-foreign-linking-info nil)
  (previous-element-of-foreign-linking-info nil))

(defun splice-element-into-foreign-linking-info 
       (new-element-of-foreign-linking-info
	beginning-of-foreign-linking-info)
  (let ((old-first-element
	  (next-element-of-foreign-linking-info
	    beginning-of-foreign-linking-info)))
    (setf (next-element-of-foreign-linking-info
	    beginning-of-foreign-linking-info)
	  new-element-of-foreign-linking-info)
    (setf (previous-element-of-foreign-linking-info
	    new-element-of-foreign-linking-info)
	  beginning-of-foreign-linking-info)
    (setf (next-element-of-foreign-linking-info
	    new-element-of-foreign-linking-info)
	  old-first-element)
    (setf (previous-element-of-foreign-linking-info
	    old-first-element)
	  new-element-of-foreign-linking-info)))

(defun splice-element-out-of-foreign-linking-info 
       (element-of-foreign-linking-info)
  (let ((next-element?
	  (next-element-of-foreign-linking-info
	    element-of-foreign-linking-info))
	(previous-element?
	  (previous-element-of-foreign-linking-info
	    element-of-foreign-linking-info)))
    (when previous-element?
      (setf (next-element-of-foreign-linking-info previous-element?)
	    next-element?))
    (when next-element?
      (setf (previous-element-of-foreign-linking-info next-element?)
	    previous-element?))
    (reclaim-element-of-foreign-linking-info
      element-of-foreign-linking-info)))


(defconstant starting-element-marker-for-foreign-linking-info 'starting-element)
(defconstant final-element-marker-for-foreign-linking-info 'final-element)

(defun make-empty-foreign-linking-info ()
  (let ((starting-element
	  (make-element-of-foreign-linking-info
	    starting-element-marker-for-foreign-linking-info
	    nil))
	(final-element
	  (make-element-of-foreign-linking-info
	    final-element-marker-for-foreign-linking-info
	    nil)))
    (setf (next-element-of-foreign-linking-info starting-element)
	  final-element)
    (setf (previous-element-of-foreign-linking-info final-element)
	  starting-element)))

(defun reclaim-empty-foreign-linking-info
       (empty-foreign-linking-info)
  (let ((final-element
	  (next-element-of-foreign-linking-info
	    empty-foreign-linking-info)))
    (reclaim-element-of-foreign-linking-info
      empty-foreign-linking-info)
    (reclaim-element-of-foreign-linking-info
      final-element)))


				  
(defun end-of-foreign-linking-info-p (element-of-foreign-linking-info)
  (eq (frame-or-structure-in-foreign-linking-info
	element-of-foreign-linking-info)
      final-element-marker-for-foreign-linking-info))



;;; The foreign-function-entry structure in foreign-function-registry




(def-structure (foreign-function-entry
		 (:constructor make-foreign-function-entry
			       (foreign-function-name
				 foreign-function-id
				 foreign-function-argument-count
				 foreign-function-type-list
				 foreign-function-return-type))
 	 (:reclaimer reclaim-foreign-function-entry-internal))
  (foreign-function-name nil)                        ;text-string
  (foreign-function-id nil)                          ;fixnum
  (foreign-function-argument-count nil)              ;fixnum
  (foreign-function-type-list nil)                   ;icp-list of
                                                     ; 'integer, 'real, 'symbol, or 'text
  (foreign-function-return-type nil)                 ;'integer, 'real, 'symbol, or 'text
  (foreign-image-info nil)                           ;foreign-image-info structure 
  (foreign-function-declarations-with-this-name nil) ;icp-list of frames
  (foreign-function-declaration-serial-numbers nil)  ;icp-list of frame serial numbers
  )



(defun reclaim-foreign-function-entry (entry)
  (when (foreign-function-name entry)
    (reclaim-text-string (foreign-function-name entry))
    (setf (foreign-function-name entry) nil))
  (when (foreign-function-type-list entry)
    (reclaim-icp-list (foreign-function-type-list entry))
    (setf (foreign-function-type-list entry) nil))
  (when (foreign-function-declarations-with-this-name entry)
    (reclaim-icp-list (foreign-function-declarations-with-this-name entry))
    (setf (foreign-function-declarations-with-this-name entry) nil))
  (let ((serial-numbers (foreign-function-declaration-serial-numbers entry)))
    (when serial-numbers
      (loop for serial-number in serial-numbers
	    do (reclaim-frame-serial-number serial-number))
      (reclaim-icp-list serial-numbers)
      (setf (foreign-function-declaration-serial-numbers entry) nil)))
  (reclaim-foreign-function-entry-internal entry))



;;; The function `get-or-make-foreign-function-entry' returns two values: a
;;; foreign function entry and, if a foreign-function-entry already exists for
;;; that name, the foreign-function-image-info of the old entry.  (The second
;;; value is a foreign-function-image-info instead of a simple boolean to make
;;; it easier to notify the user when we relink to a new foreign image.)  If
;;; this function gets an existing foreign function entry (as oppsed to creating
;;; a new one), it reclaims the icp-conses in its foreign-function-type-list
;;; argument.

(defun get-or-make-foreign-function-entry
       (foreign-function-name
	foreign-function-id
	foreign-function-argument-count
	foreign-function-type-list
	foreign-function-return-type
	foreign-image-info)
  (let ((old-entry? 
	  (get-foreign-function-entry 
	    foreign-function-name
	    foreign-function-registry)))
    (cond
      (old-entry?
       (reclaim-icp-list foreign-function-type-list)
       (values old-entry?
	       (foreign-image-info old-entry?)))
      (t (let ((new-entry 
		 (make-foreign-function-entry
		   foreign-function-name
		   foreign-function-id
		   foreign-function-argument-count
		   foreign-function-type-list
		   foreign-function-return-type)))
	   (setf (foreign-image-info new-entry) foreign-image-info)
	   (setf (get-foreign-function-entry 
		   foreign-function-name 
		   foreign-function-registry)
		 new-entry)
	   (values new-entry nil))))))



;;; The foreign-function-image-info structure

(def-structure (foreign-function-image-info
		 (:constructor make-foreign-function-image-info ())
		 (:reclaimer reclaim-foreign-image-info-internal))
  (foreign-function-entries-for-image nil)        ;icp-list
                                                  ; of foreign-function-entry structures
  (unlinked-foreign-declarations                  ;element-of-foreign-linking-info
    (make-empty-foreign-linking-info))             
  (pathname-of-foreign-image? nil)                 ;gensym-pathname
  (namestring-of-foreign-image nil)               ;text-string
  (icp-socket-connecting-to-foreign-image nil)    ;icp-socket
  (connection-specification-to-foreign-image nil) ;icp-list
  (foreign-image-port-or-task nil)                ;third connection-specification (shared)
  (foreign-image-port-or-task-index nil)          ;fixnum
  (pathname-of-overlay-comfile? nil)              ;nil or gensym-pathname on VMS
  (id-of-foreign-process? nil)                    ;nil or managed-float
  (task-to-kill-foreign-process nil)              ;used by schedule-task
  (foreign-connection-retry-count 1)              ;fixnum
  (unused-foreign-image-indices nil)              ;icp-list of fixnums
  (external-foreign-image-p nil)                  ;t or nil
  )

(defun-simple connection-specification-to-foreign-image-function
    (foreign-function-image-info)
  (connection-specification-to-foreign-image foreign-function-image-info))

;; jh, 2/20/92.  Added id-of-foreign-process?  and
;; task-to-kill-foreign-process slots to the def-structure for
;; foreign-function-image-info.  These will help us get rid of overly
;; persistent foreign images.



(def-system-variable unused-foreign-image-indices G2-FOREIGN nil)
(def-system-variable highest-foreign-image-index G2-FOREIGN -1)




(defun get-foreign-image-info-from-icp-socket (foreign-image-icp-socket)
  (or (loop for image in all-foreign-function-images?
	    thereis 
	    (and (eq (icp-socket-connecting-to-foreign-image image)
		     foreign-image-icp-socket)
		 image))
      (loop for image in all-external-foreign-function-images?
	    thereis 
	    (and (eq (icp-socket-connecting-to-foreign-image image)
		     foreign-image-icp-socket)
		 image))))

(defun pathname-of-a-connected-foreign-image-p (pathname)
  (loop for image in all-foreign-function-images?
	thereis (gensym-pathnames-equal-enough-p
		  pathname
		  (pathname-of-foreign-image? image))))

(defun-allowing-unwind get-foreign-image-info-from-pathname (pathname)
  (protected-let ((probed-pathname?
		    (gensym-probe-file pathname) ;includes version if there
		    (reclaim-gensym-pathname probed-pathname?)))
    (if probed-pathname?
	(loop for image in all-foreign-function-images?
	      thereis 
	      (and (gensym-pathnames-equal-enough-p 
		     (pathname-of-foreign-image? image) ;has version if fs does
		     probed-pathname?)
		   image))
	nil)))

;; jh, 11/18/96.  Definitely not the right place for gensym-equal, but it is not
;; ready for general use yet.

(defun-simple gensym-equal (thing1 thing2)
  (cond-with-temporaries
    ((and (null thing1) (null thing2)) t)
    ((or (null thing1) (null thing2)) nil)
    ((and (consp thing1) (consp thing2))
     (and (gensym-equal (car-of-cons thing1) (car-of-cons thing2))
	  (gensym-equal (cdr-of-cons thing1) (cdr-of-cons thing2))))
    ((or (consp thing1) (consp thing2)) nil)
    ((and (gensym-string-p thing1) (gensym-string-p thing2))
     (string= thing1 thing2))
    ((or (gensym-string-p thing1) (gensym-string-p thing2)) nil)
    ((and (text-string-p thing1) (text-string-p thing2))
     (string=w thing1 thing2))
    ((or (text-string-p thing1) (text-string-p thing2)) nil)
    (t (eql thing1 thing2))))

(defun-allowing-unwind get-foreign-image-info-from-connection-spec
    (connection-spec)
  (loop for image in all-external-foreign-function-images?
	thereis 
	(and (gensym-equal
	       connection-spec
	       (connection-specification-to-foreign-image image))
	     image)))

(defun remove-foreign-image-info-from-all-foreign-function-images
       (info-to-remove)
  (block removed-image-info
    (when (eq (car all-foreign-function-images?) info-to-remove)
      (return-from removed-image-info (icp-pop all-foreign-function-images?)))
    (loop for info-in-list in (cdr all-foreign-function-images?)
	  for cons-in-list on all-foreign-function-images?
	  when (eq info-to-remove info-in-list)
	    do
	      (setf (cdr cons-in-list) (cddr cons-in-list))
	      (return-from removed-image-info info-to-remove))
    (when (eq (car all-external-foreign-function-images?) info-to-remove)
      (return-from removed-image-info
	(icp-pop all-external-foreign-function-images?)))
    (loop for info-in-list in (cdr all-external-foreign-function-images?)
	  for cons-in-list on all-external-foreign-function-images?
	  when (eq info-to-remove info-in-list)
	    do
	      (setf (cdr cons-in-list) (cddr cons-in-list))
	      (return-from removed-image-info info-to-remove))
    info-to-remove))



;;; The foreign-function-call-info structure

;;; We only need one place to store information about the foreign call currently
;;; underweigh, since we don't do multitasking.  Remote procedure calls are
;;; available for the user who needs this.

(def-structure (foreign-function-call-info
		 (:constructor make-foreign-function-call-info ()))
  (image-for-foreign-function-call nil)
  (entry-for-foreign-function-call nil)
  (type-of-foreign-function-call? nil)
  (result-of-foreign-function-call? nil))

(def-system-variable current-foreign-function-call-info G2-FOREIGN
  (:funcall initialize-current-foreign-function-call-info))

(defun initialize-current-foreign-function-call-info ()
  (make-foreign-function-call-info))



;;;; New Class Internals for Foreign-function-declaration

;;; The class definition for foreign-function-declaration

(def-class (foreign-function-declaration
	     statement
	     (foundation-class foreign-function-declaration) define-predicate)
  ;; Frame-status-and-notes now inherits initialization of nil, and
  ;; is set up by the initialize method.  (MHD 7/18/94)
;  (frame-status-and-notes
;    (:funcall slot-value-cons-function incomplete nil))
  (frame-author-or-authors nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))
  (name-or-names-for-frame
    nil system (type nil) do-not-save)
  (box-translation-and-text
    nil vector-slot system (type foreign-function-declaration text)
    select-changes)
  (name-furnished-by-user? nil vector-slot system save)

  ;; name changed from name-in-foreign-language
  (name-in-foreign-image ;was name-in-foreign-language
    nil vector-slot system (type foreign-function-name)
    (attribute-export-comment "export as string"))

  ;; foreign-function-linked-p is not needed in the new design
; (foreign-function-linked-p 
;   nil vector-slot system (type nil) do-not-save)

  ;; Added the following three slots for foreign function server.  jh, 6/4/91.
  ;; Added unlinkable-foreign-image-info?.  jh, 6/23/91.
  (foreign-function-image-entry? ;cached info about foreign function
    nil vector-slot system do-not-save)
  (unlinkable-foreign-image-info? ;when name matches, but args or value don't
    nil vector-slot system do-not-save) 
  (timeout-interval              ;'default or an integer
    default vector-slot system user-overridable
    (type foreign-function-timeout-interval)
    save
    (attribute-export-comment "export as time-interval"))

  ;; Added declared-arglist and declared-return-type for more accurate updating of
  ;; the name-in-foreign-image slot.  (For details, see the
  ;; def-slot-value-compiler for foreign-function-declaration later in this file.)
  ;; jh, 9/3/91.
  (declared-arglist nil
   (type foreign-function-argument-description)
   vector-slot system do-not-put-in-attribute-tables save) ;do-not-save is wrong!
  (declared-return-type nil
   (type foreign-function-result-type)
   vector-slot system do-not-put-in-attribute-tables save) ;do-not-save is wrong!
  )

(define-category-evaluator-interface (foreign-function-name
				       :access read-write)
    (or (no-item) (named whole-string))
  ((set-form (evaluation-value?))
   (if evaluation-value?
       (call-category-setter 'whole-string evaluation-value? nil nil nil)
       nil))
  ((get-form (slot-value?))
   (if slot-value?
       (call-category-getter 'whole-string slot-value? nil nil)
       nil)))

(define-category-evaluator-interface (foreign-function-argument-description
				       :access read)
    (sequence symbol 0)
  ((get-form (slot-value))
   (with-list-to-evaluation-sequence-mapping
       (slot-value argument-description)
     (case argument-description
       (real 'float)
       (otherwise argument-description)))))
				       

(define-category-evaluator-interface (foreign-function-result-type
				       :access read)
    (or (no-item) symbol)
  ((get-form (slot-value))
   (case slot-value
     (real 'float)
     (otherwise slot-value))))

(define-category-evaluator-interface (foreign-function-timeout-interval
				       :access read-write)
    (or (member use-default) integer)
  ((set-form (evaluation-value))
   (cond ((integerp evaluation-value)
	  (phrase-cons evaluation-value 'seconds))
	 ((eq evaluation-value 'use-default)
	  'default)
	 (t nil)))
  ((get-form (slot-value))
   (if slot-value
       (if (eq slot-value 'default)
	   'use-default
	   slot-value)
       nil)))

(define-category-evaluator-interface (default-foreign-function-timeout-interval
				       :access read-write)
    (or (member use-default) integer)
  ((set-form (evaluation-value))
   (cond ((integerp evaluation-value)
	  (phrase-cons evaluation-value 'seconds))
	 ((eq evaluation-value 'use-default)
	  'default)
	 (t nil)))
  ((get-form (slot-value))
   (if slot-value
       (if (eq slot-value 'default)
	   'use-default
	   slot-value)
       nil)))

(def-absent-slot-putter wait-strategy
    (foreign-function-declaration new-wait-strategy)
  (declare (ignore foreign-function-declaration new-wait-strategy))
  nil)

;; jh, 3/30/92.  Extracted kill-foreign-image-unconditionally from
;; reclaim-foreign-function-image-info because this functionality occurs in
;; three places.  The first place is in the top-level wrapper
;; with-protected-listeners (defined in PRIMITIVES and used in PLATFORMS), where
;; we kill any foreign images that are still connected when G2 shuts down.  The
;; second place is in initialize-foreign-function-image (in this file), where we
;; kill the foreign image if for some reason we are unable to make an ICP
;; connection to it.  The third place is in kill-foreign-image (also in this
;; file) where we kill the foreign image unconditionally as defensive
;; programming, in case the ICP message kill-foreign-function-server somehow
;; fails.
;; --
;; jh, 3/31/92.  Extracted kill-foreign-image-process-unconditionally for the
;; deferred task in kill-foreign-image that kills the process in case the normal
;; mechansim fails.  This task needs to be a separate function that takes as
;; argument the process id instead of the surrounding
;; foreign-function-image-structure, because this structure has been reclaimed
;; by the time the function is called.


;;; The `initialize method for foreign-function-declaration' makes the frame
;;; incomplete iff its box-translation-and-text slot is nil.  Note that nothing
;;; can currently change the slot back to nil once it's been changed to nil.

(def-class-method initialize (foreign-function-declaration)
  (funcall-superior-method foreign-function-declaration)
  (unless (box-translation-and-text foreign-function-declaration)
    (update-frame-status foreign-function-declaration 'incomplete nil)))



(defun-simple kill-foreign-image-process-unconditionally (foreign-image-id?)
  (when foreign-image-id? ;defensive
    (c-kill_spawned_command_line ;may fail without signaling an error
      (managed-float-value foreign-image-id?))
    (reclaim-managed-float foreign-image-id?)))

(defun close-foreign-image-socket (image-info)
  (let ((foreign-socket?
	  (icp-socket-connecting-to-foreign-image image-info)))
    (when (icp-socket-p foreign-socket?)
      (shutdown-icp-socket-connection foreign-socket?))
    (setf (icp-socket-connecting-to-foreign-image image-info) nil)))
    
(defun kill-foreign-image-unconditionally (image-info)

  ;; jh, 2/20/92.  Immediately break the ICP connection to the foreign
  ;; image, if it isn't gone already.  This is only done if we are
  ;; exiting G2.  Under normal circumstances, kill-foreign-image marks
  ;; the ICP socket for closing and process-icp-sockets closes it
  ;; somewhat later.
  (close-foreign-image-socket image-info)

  ;; jh, 2/20/92.  Kill the foreign image unconditionally (as opposed to sending
  ;; a message requesting it to exit).  This is only useful if we are exiting G2
  ;; or have failed to connected during foreign image initialization.  Under
  ;; normal circumstances, the foreign image exits on its own after receiving a
  ;; shutdown message, and c-kill_spawned_command_line is a no-op.
  (let ((foreign-image-id?
	  (if (external-foreign-image-p image-info)
	      nil
	      (id-of-foreign-process? image-info))))
    (when foreign-image-id?
      (kill-foreign-image-process-unconditionally foreign-image-id?)
      (setf (id-of-foreign-process? image-info) nil))))


;; The following function was moved here to pick up the definition of the macro
;; foreign-function-image-entry?.  -jra 9/5/91

(defun-allowing-unwind reclaim-foreign-function-image-info (image-info)

  ;; jh, 2/20/92.  Now that we kill foreign images as well as ask them
  ;; to exit, it is possible that a race condition could give a
  ;; reclaimed foreign-image-info structure to
  ;; reclaim-foreign-function-image-info.  The following form prevents
  ;; this.
  (unless (foreign-function-image-info-p image-info)
    (return-from reclaim-foreign-function-image-info))

  ;; Remove the structure from the global list of all image info structures.
  ;; This must happen before we update the name-in-foreign-image of any allied
  ;; foreign-function-declarations, whether linked or unlinked.
  (remove-foreign-image-info-from-all-foreign-function-images image-info)

  ;; decache and reclaim foreign-function-entries for this image
  ;; (not sure this should go in reclaimer)
  (let ((entry-list (foreign-function-entries-for-image image-info)))
    (loop for entry in entry-list
	  do
	  (loop for connected-frame 
		    in (foreign-function-declarations-with-this-name entry)
		for serial-number 
		    in (foreign-function-declaration-serial-numbers entry)
		when (frame-serial-number-equal (frame-serial-number connected-frame) 
						serial-number)
		  do
		  (setf (foreign-function-image-entry? connected-frame)
			nil)
		  (add-frame-note
		    'unlinked-to-unconnected-foreign-image
		    connected-frame
		    nil
		    t
		    nil))
	  (delete-foreign-function-key 
	    (foreign-function-name entry)
	    foreign-function-registry)
	  (reclaim-foreign-function-entry entry)
	  finally
	  (reclaim-icp-list entry-list)
	  (setf (foreign-function-entries-for-image image-info) nil)))

  ;; decache information about link failure
  ;; (not sure this should go in reclaimer)
  (loop for unlinked-element 
	    = (next-element-of-foreign-linking-info
		(unlinked-foreign-declarations image-info))
	    ;; Update-foreign-function-linking reclaims unlinked-element and
	    ;; splices it out of the unlinked-foreign-declarations slot of
	    ;; image-info, so we don't do it in a prog1 here.
	    then (next-element-of-foreign-linking-info unlinked-element)
	until (end-of-foreign-linking-info-p unlinked-element)
	do
	(let ((unlinked-declaration
		(frame-or-structure-in-foreign-linking-info
		  unlinked-element)))
	  (update-foreign-function-linking 
	    unlinked-declaration
	    (get-foreign-function-entry 
	      (name-in-foreign-image unlinked-declaration)
	      foreign-function-registry)
	    t)) ;update-declaration-with-no-entry-p
	finally
	;; reclaim "end-of-list" marker
	(reclaim-empty-foreign-linking-info
	  (unlinked-foreign-declarations image-info))
	(setf (unlinked-foreign-declarations image-info) nil))


  ;; Reclaim connection specification.
  (let ((connection-spec?
	  (connection-specification-to-foreign-image image-info)))
    (when connection-spec?
      (loop for item in connection-spec?
	    when (text-string-p item)
	      do (reclaim-text-string item))
      (reclaim-icp-list connection-spec?)
      (setf (foreign-image-port-or-task image-info) nil)
      (setf (connection-specification-to-foreign-image image-info) nil)))

  ;; reuse indexes for icp connection
  (setq unused-foreign-image-indices
	(nconc unused-foreign-image-indices
	       (unused-foreign-image-indices image-info)))
  (setf (unused-foreign-image-indices image-info) nil)
  (let ((index? (foreign-image-port-or-task-index image-info)))
    (when (and index?
	       (not (member index? unused-foreign-image-indices)))
      (setq unused-foreign-image-indices
	    (nconc unused-foreign-image-indices (icp-list index?)))))

  ;; get rid of overlay comfile if any (VMS only as of 6/7/91)
  ;; (not sure this should go in reclaimer)
  (let ((overlay-pathname? (pathname-of-overlay-comfile? image-info)))
    (when overlay-pathname?
      (protected-let
	  ((overlay-truename
	     (gensym-probe-file overlay-pathname?)
	     (reclaim-gensym-pathname overlay-truename)))
	(gensym-delete-file overlay-truename))
      (reclaim-gensym-pathname overlay-pathname?)))

  ;; Reclaim the stored pathname of the foreign image.  Note that this
  ;; gensym-pathname structure is distinct from the one that is remembered by
  ;; store-current-pathname.
  (let ((image-pathname? (pathname-of-foreign-image? image-info)))
    (when (gensym-pathname-p image-pathname?)
      (reclaim-gensym-pathname image-pathname?)))
  (setf (pathname-of-foreign-image? image-info) nil)

  ;; reclaim namestring of pathname from which image is spawned
  (let ((image-namestring? (namestring-of-foreign-image image-info)))
    (when image-namestring?
      (reclaim-text-string image-namestring?))
    (setf (namestring-of-foreign-image image-info) nil))

  ;; reclaim the structure itself
  (reclaim-foreign-image-info-internal image-info))



;;; Grammar rules for the new class definition

(add-grammar-rules
  '(
    (foreign-function-declaration ('declare foreign-declaration) (1 . 2))

    (foreign-declaration ('foreign 'function 
			  new-function-name
			  '\( foreign-argument-spec '\) 
			  '= foreign-value-type)
			 (1 8 2 3 5))
    (foreign-declaration ('foreign 
			  'function new-function-name '\( '\) 
			  '= foreign-value-type)
			 (1 7 2 3 nil))

    (foreign-argument-spec foreign-type)
    (foreign-argument-spec (foreign-type '\, foreign-argument-spec)
		     (2 1 3) simplify-associative-operation)
    
    (new-function-name unreserved-symbol)

    (foreign-type 'integer)
    (foreign-type 'float)
    (foreign-type 'symbol)
    (foreign-type 'text)

    (foreign-value-type 'integer)
    (foreign-value-type 'float)
    (foreign-value-type 'symbol)
    (foreign-value-type 'text)

    (foreign-function-name whole-string)
    (foreign-function-name 'none)
    (foreign-function-name ('derived 'from 'declaration 'text) none)))


(add-grammar-rules
  '(
    (foreign-function-timeout-interval ('use 'default) 2)
    (foreign-function-timeout-interval interval)

    (default-foreign-function-timeout-interval interval)
    ))



;;; New slot-value-compilers

(def-slot-value-compiler foreign-function-declaration (parse-result declaration)
  (let* ((cons-of-parameters (cddr (cdddr parse-result)))
	 (name (fifth parse-result)))

    ;; If there are no arguments, do nothing.  If there is a single argument,
    ;; place it in a list.  If there is more than one argument, it is already in a
    ;; list.  In that case, get rid of the comma from parsing.
    (cond ((null (car cons-of-parameters)))
	  ((not (consp (car cons-of-parameters)))
	   (setf (car cons-of-parameters) 
		 (phrase-list (car cons-of-parameters))))
	  ((eq (caar cons-of-parameters) '\,)
	   (setf (car cons-of-parameters) (cdar cons-of-parameters))))

    ;; Change "float" (the G2 type name) to "real" (the internal type name,
    ;; retained as legacy for now).
    (loop for parameter-cons on (car cons-of-parameters)
	  when (eq (car parameter-cons) 'float)
	    do (setf (car parameter-cons) 'real))
    (when (eq (third parse-result) 'float)
      (setf (third parse-result) 'real))

    ;;-rdf, 9/30/94
    (reclaim-slot-value (declared-arglist declaration))

    ;; jh, 9/3/91.  Added the following two forms so that the slot-putter for
    ;; name-in-foreign-image can do up-to-date type-checking.  Previously it used
    ;; the box-translation-and-text of the declaration, and as a result was always
    ;; one edit behind.
    (setf (declared-arglist declaration)
	  (copy-for-slot-value (car cons-of-parameters)))
    (setf (declared-return-type declaration)
	  (third parse-result))

    ;; Unless user has specified name, derive it from the LISP symbol.
    (unless (name-furnished-by-user? declaration)
      (change-slot-value ;needs to call slot-putter
	declaration
	'name-in-foreign-image
	(tformat-text-string "~(~a~)" name)))

    ;; Put in name-or-names-for-frame slot so Inspect can find it
    (setf (name-or-names-for-frame declaration) name))

  parse-result)


(def-slot-value-compiler foreign-function-name (parse-result declaration)
  (cond
    ((eq parse-result 'none)
     (let* ((box-translation-and-text
	      (box-translation-and-text declaration))
	    (translation?
	      (unless (eq box-translation-and-text no-value)
		(car box-translation-and-text)))
	    (name (fifth translation?)))
       
       (setf (name-furnished-by-user? declaration) nil)
       (if name
	   (tformat-text-string "~(~A~)" name)
	   nil)))    
    (t
     (setf (name-furnished-by-user? declaration) t)
     parse-result)))



;;; `timeout intervals' - the timeout interval is a fixnum, which represents
;;; the number of seconds before we should time out.  However, we do timeouts
;;; based on fixnum-time-units-per-second, which may be 60 or 1000 or some
;;; other value.  So, although we can hold a timeout of 2^29 seconds, we cannot
;;; execute it, because that turns into 1000 * 2^29 milliseconds, which we
;;; obviously can't keep in a fixnum.   We could say the maximum timeout
;;; interval is most-positive-fixnum / fixnum-time-units-per-second, but
;;; we obviously want a kb developed on one platform to work on all others
;;; wherever possible, so it's better to use the smallest known gradation.
;;;
;;; Note that even (2 ^ 29) milliseconds is still very nearly a week:
;;; 6 days, 5 hours, 7 minutes, and 50 seconds.   The default foreign-
;;; function timeout is 30 seconds.  These changes are to fix bug
;;; HQ-3049161, "G2 allows foreign function timeout interval to be specified
;;; larger than works," which is the solver for issue HQ-3036415 from CTC.
;;; CTC has a customer who wants to use timeouts of one week, and if they
;;; can't, they want G2 to at least prevent them from overflowing.  The
;;; second part of their request seems reasonable.  - jv, 9/16/99

(progn 

  ;; Franz ACL compile complained constants were being redefined when this progn
  ;; was (eval-when (:compile-toplevel :load-toplevel :execute) ...).  It looks like it needn't be,
  ;; which is why I've changed it to a progn. -mhd, 6/17/00
  

(defconstant largest-allowable-foreign-function-timeout-interval
  (floorf most-positive-fixnum largest-known-fixnum-time-units-per-second))
(defconstant too-long-timeout-error-text
  (tformat-text-string
    "The largest allowable foreign-function timeout interval is ~d seconds."
    largest-allowable-foreign-function-timeout-interval))
)

(def-slot-value-compiler foreign-function-timeout-interval 
			 (parse-result)
  (if (eq parse-result 'default) 
      'default
      (let ((nseconds (car parse-result)))
	(if (>f nseconds largest-allowable-foreign-function-timeout-interval)
	    (values bad-phrase (copy-wide-string too-long-timeout-error-text))
	    nseconds))))
	      

(def-slot-value-compiler default-foreign-function-timeout-interval 
			 (parse-result)
  (let ((nseconds (car parse-result)))
	(if (>f nseconds largest-allowable-foreign-function-timeout-interval)
	    (values bad-phrase (copy-wide-string too-long-timeout-error-text))
	    nseconds)))



;;; New slot-value writers

(def-slot-value-writer foreign-function-name (value)
  (tprin (or value "none") value))

(def-slot-value-writer foreign-function-timeout-interval (value)
  (if (numberp value)
      (print-constant value 'seconds)
      (twrite "use default")))

(def-slot-value-writer default-foreign-function-timeout-interval (value)
  (print-constant value 'seconds))



;;; Absent slot putters for the new foreign-function-declaration class
    
(def-absent-slot-putter name-in-foreign-language
			(foreign-function-declaration new-name)
  (setf (name-in-foreign-image foreign-function-declaration)
	new-name))


(def-absent-slot-putter foreign-function-linked-p
			(foreign-function-declaration linked-p)
  (declare (ignore foreign-function-declaration linked-p)))




;;; Slot putter for name-in-foreign-image

(defun check-foreign-function-for-argcount-agreement
       (foreign-function-declaration
	entry-for-foreign-function)
  (let* ((declaration-type-list
	   (declared-arglist foreign-function-declaration))
	 (declaration-argcount
	   (length declaration-type-list))
	 (image-argcount
	   (foreign-function-argument-count
	     entry-for-foreign-function)))
    (cond ((/=f image-argcount declaration-argcount)
	   (notify-user
	     "Foreign function \"~a\" has a mismatch in argument count.  ~
              The declaration for this function takes ~a arguments but ~
              the foreign image \"~a\" takes ~a arguments.  ~
              G2 is unable to link the declaration to the foreign image."
	     (or (name-in-foreign-image foreign-function-declaration)
		 (get-or-make-up-designation-for-block 
		   foreign-function-declaration))
	     declaration-argcount
	     (namestring-of-foreign-image
	       (foreign-image-info
		 entry-for-foreign-function))
	     image-argcount)
	   (add-to-frame-note-particulars-list-if-necessary
	     (slot-value-list 'argcount-mismatch
			      declaration-argcount
			      image-argcount)
	     'unlinked-to-connected-foreign-image
	     foreign-function-declaration)
	   nil) ;return value important
	  (t t))))



(defun check-foreign-function-for-argtype-agreement
	 (foreign-function-declaration
	  entry-for-foreign-function)
  (let* ((declaration-type-list
	  (declared-arglist foreign-function-declaration))
	 (mismatch-spec?
	   (loop for declared-type in declaration-type-list
		 for image-type 
		     in (foreign-function-type-list
			  entry-for-foreign-function)
		 for index from 1
		 unless (if (consp declared-type)
			    (eq (car declared-type) image-type) ;old style
			    (eq declared-type image-type))      ;new style
		   collect (slot-value-list index declared-type image-type)
			   using slot-value-cons)))
      (cond (mismatch-spec?
	     (notify-user
	       "Foreign function declaration \"~a\" disagrees with ~
                foreign image \"~a\" on argument type~a:~%~a ~
                G2 is unable to link the declaration to the foreign image."
	       (or (name-in-foreign-image foreign-function-declaration)
		   (get-or-make-up-designation-for-block 
		     foreign-function-declaration))
	       (namestring-of-foreign-image
		 (foreign-image-info
		   entry-for-foreign-function))
	       (if (cdr mismatch-spec?)
		   "s"
		   "")
	       (twith-output-to-text-string
		 (loop for mismatch-item in mismatch-spec?
		       do
		       (tformat "arg ~a is declared as type ~a but ~
                                 image expects type ~a.~%"
				(first mismatch-item)
				(second mismatch-item)
				(third mismatch-item)))))
	     (add-to-frame-note-particulars-list-if-necessary
	       (slot-value-cons 'argtype-mismatch
				mismatch-spec?)
	       'unlinked-to-connected-foreign-image
	       foreign-function-declaration)
	     nil) ;return value important
	    (t t))))

;; jh, 8/21/91.  Added a test in check-foreign-function-for-argtype-agreement for
;; the old style declaration-type-lists.  These contained a list of sublists,
;; where each sublist represented an argument of the foreign function.  The first
;; element of each sublist was a symbol naming the argument type, and the second
;; element was a dummy variable representing the argument for no apparent purpose.
;; The new way dispenses with the dummy variable and simply uses a symbol naming
;; the argument type.  So if we notice that a piece of the declaration-type-list
;; is a cons rather than a symbol, we look at the car of the cons when we are type
;; checking against the foreign image.


(defun check-foreign-function-for-return-type-agreement
       (foreign-function-declaration
	entry-for-foreign-function)
  (let* ((declaration-return-type
	   (declared-return-type foreign-function-declaration))
	 (image-return-type
	   (foreign-function-return-type
	     entry-for-foreign-function)))
    (cond ((eq declaration-return-type image-return-type)
	   t) ;return value important
	  (t (notify-user
	       "Foreign function \"~a\" has a mismatch in return type.  ~
                The declaration for this function expects a return type ~
                of ~a but the foreign image \"~a\" will return type ~a. ~
                G2 is unable to link the declaration to the foreign image."
	       (or (name-in-foreign-image foreign-function-declaration)
		   (get-or-make-up-designation-for-block 
		     foreign-function-declaration))
	       declaration-return-type
	       (namestring-of-foreign-image
		 (foreign-image-info
		   entry-for-foreign-function))
	       image-return-type)
	     (add-to-frame-note-particulars-list-if-necessary
	       (slot-value-list 'return-type-mismatch
				declaration-return-type
				image-return-type)
	       'unlinked-to-connected-foreign-image
	       foreign-function-declaration)
	     nil)))) ;return value important



(defun check-foreign-function-for-type-and-count-agreement
       (foreign-function-declaration
	entry-for-foreign-function)
  ;; jh, 9/4/91.  Do as many checks as we can, minimizing the chance that the user must
  ;; make corrections to a foreign-function-declaration in several passes.
  (cond ((check-foreign-function-for-argcount-agreement
	   foreign-function-declaration
	   entry-for-foreign-function)
	 (let* ((argtype-agreement-p
		  (check-foreign-function-for-argtype-agreement
		    foreign-function-declaration
		    entry-for-foreign-function))
		(return-type-agreement-p
		  (check-foreign-function-for-return-type-agreement
		    foreign-function-declaration
		    entry-for-foreign-function)))
	   (and argtype-agreement-p 
		return-type-agreement-p)))
	(t (check-foreign-function-for-return-type-agreement
		    foreign-function-declaration
		    entry-for-foreign-function)
	   nil)))

;; jh, 9/3/91.  Changed the three subfunctions of
;; check-foreign-function-for-type-and-count-agreement to fix a circularity that
;; happens because we call the slot-putter for name-in-foreign-image before the
;; text makes it into the foreign-function-declaration.  The fix was to
;; introduce two new slots in foreign-function-definition, declared-arglist and
;; declared-return-type, and fill them before the slot-putter is called.



;; jh, 9/5/91.  Abstracted the following function because unlinkability info
;; needs updating at two times: when we change the name-in-foreign-image slot
;; and when we update the foreign image registry.
;; jh, 9/6/91.  There is no need for this abstraction now, but keep it around for
;; a while.

(defun remove-unlinkability-info-from-foreign-function-declaration
       (foreign-function-declaration)
  (delete-frame-note-if-any
    'unlinked-to-unconnected-foreign-image
    foreign-function-declaration)
  (delete-frame-note-if-any
    'unlinked-to-connected-foreign-image
    foreign-function-declaration)
  (let ((unlinkable-image?
	  (unlinkable-foreign-image-info? foreign-function-declaration)))
    (when unlinkable-image?
      (setf (unlinkable-foreign-image-info? foreign-function-declaration) nil)
      (splice-element-out-of-foreign-linking-info unlinkable-image?))))


;; jh, 9/5/91.  Abstracted update-foreign-function-linking because this
;; functionality is needed in several places, including the slot-putter for
;; name-in-foreign-image and in the machinery that disconnects from a foreign
;; image.

;; jh, 9/9/91.  Modified update-foreign-function-linking to set up the unlinkable
;; foreign image information before adding frame notes, so that the user will
;; always see the name of the foreign image in the frame notes, even if the frame
;; notes are visisble at the moment the link occurs (see the notes inside the
;; def-frame-writer form for unlinked-to-connected-foreign-image).

(defun update-foreign-function-linking 
       (foreign-function-declaration
	entry-for-foreign-function?
	update-declaration-with-no-entry-p)

  ;; Remove frame notes and back pointers from previous foreign-image-info
  ;; structures.
  (when (or update-declaration-with-no-entry-p
	    entry-for-foreign-function?)
    (remove-unlinkability-info-from-foreign-function-declaration
      foreign-function-declaration))
  
  ;; Set up new backpointer structures if appropriate
  (let ((image-info nil)
	(unlinked-element nil))
    (when entry-for-foreign-function?
      (setq image-info
	    (foreign-image-info entry-for-foreign-function?))
      (setq unlinked-element
	    (make-element-of-foreign-linking-info
	      foreign-function-declaration
	      image-info))
      (setf (unlinkable-foreign-image-info? foreign-function-declaration)
	    unlinked-element))

    ;; Finally, do the relinking with the new backpointer structures
    (cond ((and entry-for-foreign-function?
		(check-foreign-function-for-type-and-count-agreement
		  foreign-function-declaration
		  entry-for-foreign-function?))
	 
	   (setf (unlinkable-foreign-image-info? foreign-function-declaration)
		 nil)
	   (reclaim-element-of-foreign-linking-info unlinked-element)
	   (setf (foreign-function-image-entry? foreign-function-declaration)
		 entry-for-foreign-function?)
	   (icp-push
	     foreign-function-declaration
	     (foreign-function-declarations-with-this-name 
	       entry-for-foreign-function?))
	   (icp-push
	     (copy-frame-serial-number
	       (frame-serial-number foreign-function-declaration))
	     (foreign-function-declaration-serial-numbers
	       entry-for-foreign-function?)))

	  ;; Check-foreign-function-for-type-and-count-agreement (in the previous
	  ;; cond-clause) notifies the user and deposits frame notes so we needn't
	  ;; do that here.
	  (entry-for-foreign-function?
	   (setf (foreign-function-image-entry? foreign-function-declaration)
		 nil)
	   (splice-element-into-foreign-linking-info
	     unlinked-element
	     (unlinked-foreign-declarations image-info)))
	  
	  (update-declaration-with-no-entry-p
	   (add-frame-note
	     'unlinked-to-unconnected-foreign-image
	     foreign-function-declaration
	     nil
	     t
	     nil)
	   (setf (foreign-function-image-entry? foreign-function-declaration)
		 nil)))))



(def-slot-putter name-in-foreign-image (foreign-function-declaration value)
  (unless reading-kb-p
    (update-foreign-function-linking 
      foreign-function-declaration
      (get-foreign-function-entry 
	value
	foreign-function-registry)
      t)) ;update-declaration-with-no-entry-p
  (setf (name-in-foreign-image foreign-function-declaration) 
	value))

;; jh, 2/20/92.  Added a post-loading function for instances of class
;; foreign-function-declaration.  This will ensure that we don't attempt
;; to link to existing foreign images until we have all the necessary
;; information in the slots.  Accordingly, changed the slot-putter for
;; name-in-foreign-image to attempt a link only if we are not reading a
;; KB.

(def-post-loading-function link-completed-foreign-function-declarations
  (loop for foreign-function-declaration
	being class-instance of 'foreign-function-declaration
	do
    (update-foreign-function-linking 
      foreign-function-declaration
      (get-foreign-function-entry 
	(name-in-foreign-image foreign-function-declaration)
	foreign-function-registry)
      t)))

;;; New frame note writers for the foreign-function-declaration class

(def-frame-note-writer unlinked-to-unconnected-foreign-image
		       (particulars)
  (declare (ignore particulars))
  (tformat
    "this declaration is not linked to any foreign image"))

    


(def-frame-note-writer unlinked-to-connected-foreign-image
		       (unlinkable-reasons declaration)
  (let ((first-reason (first unlinkable-reasons)))
    (tformat 
      "this foreign function declaration cannot link to the foreign image ")
    ;; jh, 9/4/91.  The following form is defensive programming -- we never expect
    ;; a declaration without something in its unlinkable-foreign-image-info? slot
    ;; to get this far.
    ;; jh, 9/9/91.  Actually, this form used to be necessary when a table or
    ;; attribute display was visible for a foreign function at the time an image
    ;; was connected.  The problem is that the unlinkable-foreign-image-info?
    ;; slot was not yet filled by the time the frame writer is called upon to
    ;; write, so we were unable to write the namestring-of-foreign-image.  This
    ;; was fixed in update-foreign-function-linking, so the following form again
    ;; exists solely for defensive programming.
    (let ((unlinkable-element?
	    (unlinkable-foreign-image-info? declaration)))
      (when unlinkable-element?
	(let ((image-info?
		(enclosing-frame-or-structure-in-foreign-linking-info?
		  unlinkable-element?)))
	  (when image-info?
	    (tformat "\"~a\" "
	      (namestring-of-foreign-image image-info?))))))
    (tformat "because")

    (let ((enumerate-p 
	    (or (cdr unlinkable-reasons)
		(and (eq 'argtype-mismatch (first first-reason))
		     (cddr first-reason)))))
      (if enumerate-p
	  (tformat ":~%")
	  (tformat " "))
      (loop for (reason-type . particulars-spec) in unlinkable-reasons
	    for unlinkable-cons on unlinkable-reasons
	    for final-outer-entry-p = (null (cdr unlinkable-cons))
	    with index = (1-f frame-note-index)
	    for number-of-notes-written from 0
	    do
	    (case reason-type
	      (argcount-mismatch
	       (gensym-dstruct-bind 
		   ((declaration-argcount image-argcount) particulars-spec)
		 (when enumerate-p
		   (tformat "(~a) " (incff index)))
		 (tformat 
		   "the declaration has ~a arguments ~
                    but the image expects ~a arguments"
		   declaration-argcount
		   image-argcount)
		 (unless final-outer-entry-p
		   (tformat ";~%"))))
	      (argtype-mismatch
	       (loop for (argument-number declaration-type image-type)
			 in particulars-spec
		     for particulars-cons on particulars-spec
		     for final-inner-entry-p = (null (cdr particulars-cons))
		     do
		     (when enumerate-p
		       (tformat "(~a) " (incff index)))
		     (tformat
		       "the declaration argument #~a is of type ~a ~
                        but the image expects type ~a"
		       argument-number
		       declaration-type
		       image-type)
		     (unless (and final-outer-entry-p final-inner-entry-p)
		       (tformat ";~%"))))
	      (return-type-mismatch
	       (gensym-dstruct-bind 
		 ((declaration-return-type image-return-type)
		  particulars-spec)
		 (when enumerate-p
		   (tformat "(~a) " (incff index)))
		 (tformat 
		   "the declaration specifies a return type of ~a ~
                    but the image will return type ~a"
		   declaration-return-type 
		   image-return-type)
		 (unless final-outer-entry-p
		   (tformat ";~%")))))
	    finally
	    (incff frame-note-index-skip number-of-notes-written)))))




;;; New methods for the foreign-function-declaration class

(def-class-method put-box-translation-and-text-slot-value
    (foreign-function-declaration new-value initializing?)
  (let* ((name (fifth
		 (unless (eq new-value no-value)
		   (car new-value))))
	 (old-box-translation-and-text
	   (box-translation-and-text foreign-function-declaration))
	 (old-name?
	   (if (neq (car old-box-translation-and-text) no-value)
	       (fifth (car old-box-translation-and-text)))))
    
    (when old-name?
      (delete-as-frame-with-name foreign-function-declaration old-name?))
    (when name 
      (add-as-frame-with-name foreign-function-declaration name)))
  (setf (box-translation-and-text foreign-function-declaration) new-value)
  (unless initializing?
    (update-frame-status foreign-function-declaration nil nil))
  (values new-value nil))


(def-class-method cleanup (foreign-function-declaration)
  (funcall-superior-method foreign-function-declaration)
  (setf (foreign-function-image-entry? foreign-function-declaration)
	nil)
  (let ((unlinkable-info?
	  (unlinkable-foreign-image-info? foreign-function-declaration)))
    (when unlinkable-info?
      (splice-element-out-of-foreign-linking-info unlinkable-info?)
      (setf (unlinkable-foreign-image-info? foreign-function-declaration) nil)))
  (let* ((old-box-translation-and-text
	   (box-translation-and-text foreign-function-declaration))
	 (old-name?
	   (if (neq (car old-box-translation-and-text) no-value)
	       (fifth (car old-box-translation-and-text)))))
    (when old-name? 
      (delete-as-frame-with-name foreign-function-declaration old-name?))))





;;;; ICP Data Structures for Foreign Function Server



;;; ICP reader and writer for list-of-foreign-function-registrations?

;;; The ICP value type list-of-foreign-function-registrations? is an icp-list of
;;; data coming from the foreign image.  This data is used to fill
;;; foreign-function-entry structures.  There is no need to maintain a
;;; corresponding icp structure for this value type.

;;; Note the distinction between foreign-function-registration-xxx accessors and
;;; foreign-function-entry-xxx ones.  The registration is an icp-list that is
;;; built by the handler for the ICP message provide-foreign-function-registry.
;;; This list is reclaimed as soon as it is stored in a foreign-function-entry
;;; structure.  The foreign-function-entry structure, on the other hand, persists
;;; for the life of the connection to the foreign image.

(defmacro foreign-function-registration-name (x)        `(first ,x))
(defmacro foreign-function-registration-id (x)          `(second ,x))
(defmacro foreign-function-registration-argcount (x)    `(third ,x))
(defmacro foreign-function-registration-typelist (x)    `(fourth ,x))
(defmacro foreign-function-registration-return-type (x) `(fifth ,x))

(defun-void reclaim-list-of-foreign-function-registrations
    (list-of-foreign-function-registrations)
  (loop for (foreign-name)
	    in list-of-foreign-function-registrations
	do (reclaim-text-string foreign-name))
  (reclaim-icp-tree list-of-foreign-function-registrations))

(def-icp-value-reader list-of-foreign-function-registrations?
  ;; needs error handling!
  (loop for index from 1 to (read-icp-integer)
	collect
	(let* ((raw-foreign-name (read-icp-text-string))
	       (foreign-name
		 (prog1
		   (copy-text-string raw-foreign-name)
		   (reclaim-text-string raw-foreign-name)))
	       (foreign-id (read-icp-integer))
	       (argument-count (read-icp-integer))
	       (type-list
		 (loop for index 
			   from 1 to argument-count
		       collect (read-icp-integer)
			   using icp-cons))
	       (return-type (read-icp-integer)))
	  (icp-list 
	    foreign-name foreign-id argument-count type-list return-type))
	using icp-cons))

;; A value writer for list-of-foreign-function-entries is not currently (5/31/91)
;; needed in G2.

(def-icp-value-writer list-of-foreign-function-registrations?
  nil)



;;; ICP reader and writer for foreign-function-argument

(def-icp-value-writer foreign-function-argument
  (evaluation-typecase foreign-function-argument
    (evaluation-integer 
      (write-icp-byte foreign-function-integer-type-tag)
      (write-icp-integer evaluation-integer))
    (evaluation-float
      (write-icp-byte foreign-function-real-type-tag)
      (write-icp-double-float-1 evaluation-float))
    (evaluation-text
      (write-icp-byte foreign-function-text-type-tag)
      (write-icp-text-string evaluation-text))
    (evaluation-symbol
      (write-icp-byte foreign-function-symbol-type-tag)
      (write-icp-text-string (symbol-name-text-string evaluation-symbol)))))

;; A value reader for foreign-function-argument is not currently (6/4/91) needed
;; in G2.

(def-icp-value-reader foreign-function-argument
  nil)




;;; ICP reader and writer for foreign-function-value

;; Consider calling this foreign-function-result or foreign-function-return-value.

    
(def-icp-value-reader foreign-function-value
  (let ((type-tag (read-icp-byte)))
    ;; we can get away with the following form because foreign function calls
    ;; are single-threaded
    (setf (type-of-foreign-function-call?
	    current-foreign-function-call-info)
	  type-tag)
    (case type-tag
      (#.foreign-function-integer-type-tag
       (make-evaluation-integer (read-icp-fixnum)))
      (#.foreign-function-real-type-tag
       (make-evaluation-float (read-icp-double-float-1)))
      (#.foreign-function-symbol-type-tag
       (make-evaluation-symbol 
	 (intern-text-string 
	   (read-icp-text-string))))
      (#.foreign-function-text-type-tag
       ;; jh, 9/21/93.  The old call to make-evaluation-text would leak the
       ;; result of read-icp-text-string.  Unlike the ICP value type
       ;; text-string, there is no icp-value-reclaimer for
       ;; foreign-function-value.
       (make-evaluation-text-reclaiming-argument
	 (read-icp-text-string)))
      ;; user is notified at a higher level, namely, the
      ;; ICP message handler for return-foreign-function-value, so
      ;; we can return nil here
      (otherwise nil))))

;; jh, 2/18/93.  Changed read-icp-integer to read-icp-fixnum to handle the case
;; where a foreign image returns a long larger than the bignum threshhold.  This
;; corresponds to the call already in place in the value reader for
;; gsi-data-value in GSI-COMMON.


;; A value writer for foreign-function-value is not currently (6/4/91) needed in
;; G2.

(def-icp-value-writer foreign-function-value
  nil)






;;;; Connecting to Foreign Images

(defun get-or-create-foreign-function-image-index ()
  (or (icp-pop unused-foreign-image-indices)
      (incf highest-foreign-image-index)))

(def-system-variable tcp-ip-port-offset-for-foreign-images G2-FOREIGN 2222)

;; Note we have to determine the value of foreign-image-connection-mode at
;; runtime, since we Lisp-compile all platforms on the Sparc.  jh, 8/16/91.

(def-system-variable foreign-image-connection-mode G2-FOREIGN
  (:funcall initialize-foreign-image-connection-mode))

(defun initialize-foreign-image-connection-mode ()
  'tcp-ip)


(defvar cached-tcpip-listener-address?  :uncached)

(defmacro get-cached-listener-address-if-any
    (cached-var? transport-string return-function)
  `(if (eq ,cached-var? :uncached)
       (let* ((all-network-addresses (get-local-host-addresses))
	      (this-transport-address?
		(loop for (transport address) in all-network-addresses
		      thereis (and (equalw transport ,transport-string)
				   address))))
	 (prog1
	     (setq ,cached-var?
		   (if this-transport-address?
		       (,return-function this-transport-address?)
		       nil))
	   (reclaim-network-addresses all-network-addresses)))
       ,cached-var?))

(defmacro get-tcpip-listener-address-if-any ()
  `(get-cached-listener-address-if-any
     cached-tcpip-listener-address?
     "TCP_IP"
     text-string-parse-integer))

(defun get-next-unused-foreign-image-port-or-task ()
  (let ((unused-index (get-or-create-foreign-function-image-index)))
    (case foreign-image-connection-mode
      (tcp-ip
       (let ((proposed-port
	       (+ tcp-ip-port-offset-for-foreign-images unused-index)))
	 (if (equal (get-tcpip-listener-address-if-any) proposed-port)
	     (let ((better-index (get-or-create-foreign-function-image-index)))
	       (values (+ tcp-ip-port-offset-for-foreign-images better-index)
		       better-index))
	     (values proposed-port unused-index))))
      #+development
      (otherwise (error "GET-NEXT-UNUSED-FOREIGN-IMAGE-PORT-OR-TASK: ~
                         Unknown connect mode ~a"
			foreign-image-connection-mode)))))

;; jh, 11/4/94.  Modified get-next-unused-foreign-image-port-or-task not to
;; supply the same port or task for G2 as the port or task used by its listener.


;;; Spawn-foreign-function-image returns nil if it was definitely unable to
;;; spawn a foreign image.  If it returns non-nil, the system call to spawn the
;;; foreign image succeeded.  There is still the possibility of a system error
;;; after the spawn operation that prevented the creation of the process to run
;;; the foreign image.  Spawn-foreign-function-image is unable to detect this,
;;; but calls to foreign function inside such failed processes will eventually
;;; time out and notify the user.

(defvar spawn-command-line-process-failure -1.0)

(defun-allowing-unwind spawn-foreign-function-image 
		       (image-info port-or-task port-or-task-index) 
  (progn
    (setf (foreign-image-port-or-task image-info)
	  port-or-task)
    (setf (foreign-image-port-or-task-index image-info) 
	  port-or-task-index)
    (case foreign-image-connection-mode
      (tcp-ip 
       (protected-let 
           ((ascii-namestring-of-foreign-image
	      (convert-text-string-to-ascii-filename-as-much-as-possible
		(namestring-of-foreign-image image-info))
	      (reclaim-text-string ascii-namestring-of-foreign-image))
	    (command-line
	      (tformat-text-string 
		(if (eq local-file-system 'win32)
		    "~s ~a" ;;~s quotes the string, needed on win32.
		    "~a ~a")
		ascii-namestring-of-foreign-image
		(foreign-image-port-or-task image-info))
	      (reclaim-text-string command-line)))
	 (with-temporary-gensym-float-creation 
	   spawn-foreign-function-image-tcp
	   (let ((process-id-or-failure-flag
		   (c-spawn_command_line_process command-line)))
	     (cond 
	       ((= process-id-or-failure-flag
		   spawn-command-line-process-failure)
		nil)
	       (t (setf (id-of-foreign-process? image-info)
			(allocate-managed-float process-id-or-failure-flag))
		  t))))))

      (otherwise (error "SPAWN-FOREIGN-FUNCTION-IMAGE: ~
                       Unknown connect mode ~a"
			foreign-image-connection-mode))))
  )



;; Create-foreign-image-connection returns nil if it was unable to create an ICP
;; connection to the foreign image, non-nil otherwise.

;; jh, 8/13/95.  With the new ICP finalization machinery, it is possible to get
;; a non-nil icp-connection?, yet not have a completely valid socket.  At
;; present, the foreign image machinery (and not process-icp-sockets) maintains
;; the ICP socket connected to the foreign image.  So we need to check for
;; complete validity by hand here, bypassing the finalization protocol
;; maintained by process-icp-sockets.  This approach will fix a bug in foreign
;; images on the NT platforms for 4.0 rev 1.  Afterwards, we should consider
;; either merging with the protocol in process-icp-sockets, or abstracting this
;; protocol to allow ICP sockets to be manitained by individual facilities yet
;; obey the same finalization protocol.

(defvar foreign-image-connection-checkup-interval-in-ms 100)

(defvar total-foreign-image-connection-checkup-interval-in-ms 5000)

(defvar ff-connect-finalized)

(defun-void ff-connect-callback (icp-socket)
  (declare (ignore icp-socket))
  (setf ff-connect-finalized 'success))

(defun-void handle-ff-connect-failure (icp-socket clean?)
  (declare (ignore icp-socket clean?))
  (setf ff-connect-finalized 'failure))

(defun-allowing-unwind make-icp-connection-to-foreign-image (connection-specification)
  (with-scheduler-disabled
    (let* ((ff-connect-finalized nil)
	   (initial-icp-version-info-enabled-p nil)
	   (icp-connection? (make-icp-connection connection-specification)))
      (when icp-connection?
	(register-icp-connection-loss-callback
	  'handle-ff-connect-failure icp-connection?)
	(setup-network-connection-for-connect
	  icp-connection? 'ff-connect-callback)
	(loop until ff-connect-finalized
	      do (g2-event-cycle-handling-windows-quit))
	(cond ((eq ff-connect-finalized 'failure)
	       nil)
	      (t
	       (deregister-all-icp-connection-loss-callbacks icp-connection?)
	       icp-connection?))))))

(defun-void handle-internal-foreign-image-connection-failure
    (icp-socket-to-foreign-image clean?)
  (declare (ignore clean?))
  (loop for internal-image-info in all-foreign-function-images?
	do    
    (when (eq (icp-socket-connecting-to-foreign-image internal-image-info)
	      icp-socket-to-foreign-image)
      (setf (icp-socket-connecting-to-foreign-image internal-image-info) nil)
      (kill-foreign-image internal-image-info)
      (loop-finish))))

(def-substitution-macro create-foreign-image-connection-given-host
    (host-name image-info)
  (let* ((port-or-task
	   (foreign-image-port-or-task image-info))
	 (connection-specification
	   (case foreign-image-connection-mode
	     ;;HQ-5495099: last arg is secure-p
	     (tcp-ip (icp-list 'tcp-ip host-name port-or-task nil))
	     #+development
	     (otherwise 
	      (error "CREATE-FOREIGN-IMAGE-CONNECTION:  ~
                      Unknown connect mode ~a"
		     foreign-image-connection-mode))))
	 (icp-connection?
	   (make-icp-connection-to-foreign-image connection-specification))) 
    (cond (icp-connection?
	   (setf (icp-socket-connecting-to-foreign-image image-info)
		 icp-connection?)
	   (setf (connection-specification-to-foreign-image image-info)
		 connection-specification)
	   (register-icp-callback 'icp-connection-loss
	     'handle-internal-foreign-image-connection-failure
	     icp-connection?)
	   icp-connection?)
	  (t (when (text-string-p host-name)
	       (reclaim-text-string host-name))
	     (reclaim-icp-list connection-specification)
	     nil))))

(defun-simple create-foreign-image-connection (image-info)
  (create-foreign-image-connection-given-host
    (copy-text-string (get-local-host-name))
    image-info))

(defun-void handle-external-foreign-image-connection-failure
    (icp-socket-to-foreign-image clean?)
  (declare (ignore clean?))
  (loop for external-image-info in all-external-foreign-function-images?
	do    
    (when (eq (icp-socket-connecting-to-foreign-image external-image-info)
	      icp-socket-to-foreign-image)
      (setf (icp-socket-connecting-to-foreign-image external-image-info) nil)
      (kill-foreign-image external-image-info)
      (loop-finish))))
	    
(defun-simple create-external-foreign-image-connection
    (image-info connection-spec)
  (let ((icp-connection?
	  (make-icp-connection-to-foreign-image connection-spec)))
    (cond (icp-connection?
	   (setf (icp-socket-connecting-to-foreign-image image-info)
		 icp-connection?)
	   (setf (connection-specification-to-foreign-image image-info)
		 connection-spec)
	   (register-icp-callback 'icp-connection-loss
	     'handle-external-foreign-image-connection-failure
	     icp-connection?)
	   icp-connection?)
	  (t nil))))
  

;; jh, 3/8/93.  Michael Grey informs me that some UNIX machines (like the HPs)
;; have trouble making a network connection to themselves when running
;; standalone.  A "standalone" machine is one that is not on a network connected
;; to other machines, and may even lack an Ethernet card.  Still, one would
;; expect that such a machine would be able to connect to itself.  In any event,
;; we should consider replacing the call to get-local-host-name in
;; create-foreign-image-connection with the hard-wired string "localnet" on UNIX
;; machines.  Michael Grey further informs me that the workaround of adding the
;; machine name to the /etc/hosts file sometimes works, though it may not if the
;; machine entirely lacks an Ethernet card.



(defvar maximum-retries-for-foreign-image-connection 10)
(defvar milliseconds-between-retries-for-foreign-image-connection 1000)
(defvar milliseconds-to-sleep-before-connecting-to-foreign-image
  (if (windows-platform-p)
      6000
      3000))
(defvar milliseconds-to-sleep-after-connection-on-pc-platforms 2000)
	    


;; jh, 3/30/92.  Changed initialize-foreign-function-image to sleep before
;; attempting an ICP connection to the foreign image.  This was causing multiple
;; foreign images to be spawned, of which only the last was connected.  This in
;; turn was causing problems when G2 shut down, since it had no way to kill
;; these extra child processes.  Also, to make things even safer,
;; initialize-foreign-function-image now kills immediately any foreign image
;; that it fails to connect to.

(defun-simple initialize-foreign-function-image (image-info)
  (loop for retry-count
	from (foreign-connection-retry-count image-info)
	    to maximum-retries-for-foreign-image-connection
	with connection-succeeded-p = nil
	with spawn-succeeded-p = nil
	with failed-socket-indices = nil
	do
    (incff (foreign-connection-retry-count image-info))
    (multiple-value-bind (port-or-task unused-index)
	(get-next-unused-foreign-image-port-or-task)
      (setq spawn-succeeded-p
	    (spawn-foreign-function-image
	      image-info
	      port-or-task
	      unused-index))
      (when spawn-succeeded-p
	(c-uninterruptible-sleep milliseconds-between-retries-for-foreign-image-connection)	
	(when (create-foreign-image-connection image-info)
	  (setq connection-succeeded-p t)
	  (loop-finish))
	(kill-foreign-image-unconditionally image-info))
      (icp-push unused-index failed-socket-indices)
      (c-uninterruptible-sleep
	milliseconds-between-retries-for-foreign-image-connection))
	finally
	  (cond
	    (connection-succeeded-p
	     (setf (unused-foreign-image-indices image-info)
		   (nconc (unused-foreign-image-indices image-info)
			  failed-socket-indices))
	     (when (windows-platform-p)
	       (c-uninterruptible-sleep
		 milliseconds-to-sleep-after-connection-on-pc-platforms))
	     ;; Success message emitted in the ICP handler for
	     ;; provide-foreign-function-registry.
	     )
	    (t (setq unused-foreign-image-indices
		     (nconc unused-foreign-image-indices 
			    failed-socket-indices))
	       (if spawn-succeeded-p
		   (notify-user
		     "G2 could not connect to foreign image \"~a\"."
		     (namestring-of-foreign-image image-info))
		   (notify-user
		     "G2 could not create a process for foreign image \"~a\"."
		     (namestring-of-foreign-image image-info)))))
	  (return connection-succeeded-p)))

;; jh, 1/29/92.  Modified initialize-foreign-function-image to retry foreign-image
;; connections at different addresses each time.  It previously would retry on the
;; same address.  This modification makes it more likely that G2 will be able to
;; connect to a foreign image, given the fact that closed sockets take a while to
;; vanish on some platforms.  Note that the true fix for this problem is to find
;; out the proper socket options on all platforms to make a socket vanish as soon
;; as it is closed.  Likely candidates are SO_DONTLINGER and SO_KEEPALIVE.

;; jh, 11/2/93.  Modified initialize-foreign-function-image to store retry-count
;; and failed-socket-indices inside image-info if it successfully connected.
;; This is so we can clean up properly if the foreign image refuses to provide a
;; foreign registry.  Such a refusal happens when more than one G2 running on
;; the same machine attempts to connect to the same foreign image, and is
;; fallout from the fact that foreign images use a GSI-like listener.  Since
;; this refusal happens at an indeterminate time after the successful spawn and
;; connect, we can't report success here, as we do failure.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar tcpip-external-foreign-image-prologue
  #w"tcp-ip host ")
)

(defmacro body-of-external-foreign-image-disconnection-spec-p (choice)
  (let ((tcpip-prologue-length
	  (length tcpip-external-foreign-image-prologue)))
    (avoiding-variable-capture (choice)
      `(let ((length (length ,choice)))
	 (and (>=f length ,tcpip-prologue-length)
	      (gensym-search
		,tcpip-external-foreign-image-prologue
		,choice
		:start2 0
		:end2 ,tcpip-prologue-length))))))
	      
(defun-simple external-foreign-image-disconnection-spec-p (choice)
  (body-of-external-foreign-image-disconnection-spec-p choice))

(defun-void twrite-icp-connection-spec (connection-spec?)
  (if connection-spec?
      (let ((transport-type (first connection-spec?)))
	(case transport-type
	  (tcp-ip (twrite-string tcpip-external-foreign-image-prologue)
		  (twrite-char #.%\")
		  (twrite-string (second connection-spec?))
		  (twrite-char #.%\")
		  (twrite-string " port-number ")
		  (twrite-fixnum (third connection-spec?)))
	  (localnet (twrite-string "local emulator"))
	  #+development
	  (otherwise
	   (error "TWRITE-ICP-CONNECTION-SPEC: unknown transport type ~s"
		  transport-type))))
      (twrite-string "none")))

(defun-void twrite-foreign-image-connection-spec (connection-spec)
  (twrite-icp-connection-spec connection-spec))

(defun-simple initialize-external-foreign-function-image
    (image-info connection-spec)
  (loop for retry-count
	from (foreign-connection-retry-count image-info)
	    to maximum-retries-for-foreign-image-connection
	with connection-succeeded-p = nil
	do
    (when (create-external-foreign-image-connection
	    image-info
	    connection-spec)
      (setq connection-succeeded-p t)
      (loop-finish))
    (kill-foreign-image-unconditionally image-info)
    (c-uninterruptible-sleep milliseconds-between-retries-for-foreign-image-connection)
	finally
	  (cond
	    (connection-succeeded-p
	     (setf (foreign-connection-retry-count image-info)
		   retry-count)
	     ;; Success message emitted in the ICP handler for
	     ;; provide-foreign-function-registry.
	     )
	    (t (let ((connection-spec-text
		       (twith-output-to-text-string
			 (twrite-foreign-image-connection-spec
			   connection-spec))))
		 (notify-user
		   "G2 could not connect to external foreign image `~a'."
		   connection-spec-text)
		 (reclaim-text-string connection-spec-text))))
	  (return connection-succeeded-p)))

(defun initialize-foreign-function-image-if-possible
    (image-truename? &optional retry-count?)
  (let ((image-info (make-foreign-function-image-info)))
    (setf (pathname-of-foreign-image? image-info) image-truename?)
    (setf (namestring-of-foreign-image image-info) 
	  (gensym-namestring-as-text-string image-truename?))
    (when retry-count?
      (setf (foreign-connection-retry-count image-info) retry-count?))
    (cond
      ((initialize-foreign-function-image image-info)
       (icp-push image-info all-foreign-function-images?)
       (writing-icp-message-group 
	   ((icp-output-port 
	      (icp-socket-connecting-to-foreign-image image-info)))
	 (send-icp-request-foreign-function-registry 0 #.(stringw ""))))
      ;; In case of failure, the user is notified during the
      ;; appropriate subtask in initialize-foreign-function-image,
      ;; so we needn't do it here.
      (t (reclaim-foreign-function-image-info image-info)))))
  
(defun-allowing-unwind connect-to-foreign-image
		       (image-pathname) ;a gensym-pathname
  (protected-let ((image-truename?
		    (gensym-probe-file image-pathname) ;includes version if there
		    ;; do not reclaim - stored in image info!
		    )
		  (namestring-of-connection-attempt
		    (gensym-namestring-as-text-string image-pathname)
		    (reclaim-text-string namestring-of-connection-attempt)))

    (store-current-pathname current-foreign-image-pathname? image-pathname)

    ;; Have to check for executability of the foreign function server somehow.
    ;; Maybe fstat will work on both platforms.

    (if image-truename?
	(let ((extant-image? 
		(get-foreign-image-info-from-pathname image-truename?)))
	  (if extant-image?
	      (notify-user
		"G2 is already connected to foreign image \"~a\".  ~
                 To overwrite existing foreign functions, you must ~
                 disconnect from this image and then re-connect to it."
		(namestring-of-foreign-image extant-image?))

	      ;; When the image comes up, it will send the ICP message
	      ;; foreign-image-ready, which will cause G2 to query the image for
	      ;; the foreign functions it contains.
	      (initialize-foreign-function-image-if-possible image-truename?)))
	(notify-user
	  "Attempt to connect to foreign image  \"~a\".  ~
           This file does not exist."
	  namestring-of-connection-attempt))))

(defun-allowing-unwind connect-to-external-foreign-image (connection-spec)
  (let ((extant-image? 
	  (get-foreign-image-info-from-connection-spec connection-spec)))
    (if extant-image?
	(let ((connection-spec-text
		(twith-output-to-text-string
		  (twrite-foreign-image-connection-spec connection-spec))))
	  (notify-user
	    "G2 is already connected to external foreign image `~a'.  ~
             To overwrite existing foreign functions, you must ~
             disconnect from this image and then re-connect to it."
	    connection-spec-text)
	  (reclaim-text-string connection-spec-text))
	(let ((image-info (make-foreign-function-image-info)))
	  (setf (external-foreign-image-p image-info) t)
	  (setf (connection-specification-to-foreign-image image-info)
		connection-spec)
	  (setf (namestring-of-foreign-image image-info) 
		(twith-output-to-text-string
		  (twrite-foreign-image-connection-spec connection-spec)))
	  (cond ((initialize-external-foreign-function-image
		   image-info
		   connection-spec)
		 (icp-push image-info all-external-foreign-function-images?)
		 (writing-icp-message-group 
		     ((icp-output-port 
			(icp-socket-connecting-to-foreign-image
			  image-info)))
		   (send-icp-request-foreign-function-registry 0 #.(stringw ""))))

		;; In case of failure, the user is notified during the
		;; appropriate subtask in
		;; initialize-external-foreign-function-image, so we needn't do
		;; it here.
		(t (reclaim-foreign-function-image-info image-info)))))))



;;;; Disconnecting from Foreign Images

;; jh, 9/3/91.  Abstracted kill-foreign-image from disconnect-from-foreign-image
;; so we can call it in the protected forms of with-protected-listeners.
;; --
;; jh, 2/20/92.  Modified kill-foreign-image to schedule a task to
;; reclaim the corresponding foreign-function-image-info structure.
;; This is to give the shutdown message time to allow the foreign image
;; to exit on its own.  Note that the protected forms of
;; with-protected-listeners no longer call kill-foreign-image, but call
;; reclaim-foreign-function-image-info instead.
;; --
;; jh, 3/30/92.  Kill-foreign-image is no longer the shared code that is used by
;; with-protected-listeners.  Kill-foreign-image-unconditionally, extracted from
;; reclaim-foreign-function-image-info above, now serves this purpose.  Made the
;; necessary changes in kill-foreign-image.

(defvar wait-interval-before-killing-foreign-process 5)



(defun-allowing-unwind kill-foreign-image (foreign-image-info)
  (let* ((image-socket?
	   (icp-socket-connecting-to-foreign-image foreign-image-info))
	 (external-p (external-foreign-image-p foreign-image-info))
	 (foreign-process-id?
	   (if external-p
	       nil
	       (id-of-foreign-process? foreign-image-info))))
    (when image-socket?
      (let ((shutdown-context-flag
	      (if external-p
		  shutdown-context-only-flag-set
		  shutdown-context-only-flag-clear)))
	(writing-icp-message-group 
	    ((icp-output-port image-socket?))
	  (send-icp-kill-foreign-function-server shutdown-context-flag #.(stringw "")))
	(flush-and-shutdown-icp-socket image-socket?)
	(setf (icp-socket-connecting-to-foreign-image foreign-image-info)
	      nil)))
    (when foreign-process-id?
      (with-future-scheduling
	  ((task-to-kill-foreign-process foreign-image-info)
	   1
	   (g2-future-interval
	     wait-interval-before-killing-foreign-process))
	(kill-foreign-image-process-unconditionally foreign-process-id?)))
    (reclaim-foreign-function-image-info foreign-image-info)))


(defun-allowing-unwind disconnect-from-foreign-image 
		       (image-pathname) ;a gensym-pathname
  (protected-let ((image-truename?
		    (gensym-probe-file image-pathname) ;includes version if there
		    (reclaim-gensym-pathname image-truename?))
		  (namestring-of-disconnection-attempt
		    (gensym-namestring-as-text-string image-pathname)
		    (reclaim-text-string namestring-of-disconnection-attempt)))

    (store-current-pathname current-foreign-image-pathname? image-pathname)

    (cond (image-truename?

	   (let ((extant-image? 
		   (get-foreign-image-info-from-pathname image-truename?)))
	     (cond (extant-image?
		    (kill-foreign-image extant-image?)
		    (notify-user "Disconnected from foreign image \"~a\"."
				 namestring-of-disconnection-attempt)
		    t)
		   (t (notify-user
			"Attempt to disconnect from foreign image \"~a\".  ~
                         G2 was not connected to this image."
			namestring-of-disconnection-attempt)
		      nil))))

	(t (notify-user
	     "Attempt to disconnect from foreign image \"~a\".  ~
              This file does not exist."
	     namestring-of-disconnection-attempt)
	   nil)))
  )

(defun-simple disconnect-from-external-foreign-image (connection-spec)
  (let ((extant-image? 
	  (get-foreign-image-info-from-connection-spec connection-spec))
	(connections-spec-text
	  (twith-output-to-text-string
	    (twrite-foreign-image-connection-spec connection-spec))))
    (prog1
	(cond
	  (extant-image?
	   (kill-foreign-image extant-image?)
	   (notify-user "Disconnected from external foreign image `~a'."
			connections-spec-text)
	   t)
	  (t (notify-user
	       "Attempt to disconnect from external foreign image `~a'.  ~
                G2 was not connected to this image."
	       connections-spec-text)
	     nil))
      (reclaim-text-string connections-spec-text))))
      
;; jh, 2/9/92.  Added a disconnect-from-all-foreign-images, in case pathname
;; matching or the kill-foreign-function-server message fails.  (We currently
;; have an intermittant bug that might be due to such things.) The grammar
;; giving users access to this is defined in KB-LOAD1.

(defun-void disconnect-from-foreign-images-in-list (list-of-foreign-images)
  (let ((copy-of-list-of-foreign-images
	  (copy-list-using-icp-conses list-of-foreign-images)))
    (loop for image in copy-of-list-of-foreign-images
	  do (kill-foreign-image image)
	     (notify-user "Disconnecting from foreign image \"~a\"."
			  (namestring-of-foreign-image image))
	  finally
	    (reclaim-icp-list copy-of-list-of-foreign-images))))

(defun-void disconnect-from-all-foreign-images ()
  (disconnect-from-foreign-images-in-list all-foreign-function-images?)
  (disconnect-from-foreign-images-in-list
    all-external-foreign-function-images?)
  (notify-user "Disconnected from all foreign images."))




;;;; Icp Messages to the Foreign Image

(def-icp-message-type request-foreign-function-registry
		      ((integer spare-code)
		       (text-string out-of-band-message))
  spare-code
  (writing-icp-message-group ((icp-output-port current-icp-socket))
    (send-icp-provide-foreign-function-registry nil 0 out-of-band-message)))


;; Note that the ICP message type call-foreign-function begins the foreign call
;; but doesn't pass the foreign argument list.  This is an optimization that
;; by-passes assembling the arguments into a list before transmitting them.
;; This extra list is unnecessary because we can read the arguments directly
;; from the evaluator's stack, which is passed to call-foreign-function by the
;; evaluator.

(def-icp-message-type call-foreign-function ((integer foreign-function-id))
  ;;
  ;; G2 does not receive call-foreign-function messages,
  ;; hence there is no ICP handler body here.
  )

;;; If the shutdown-context-only-flag argument to the ICP message type
;;; kill-foreign-function-server is the constant
;;; shutdown-context-only-flag-clear (jh, 6/28/94, currently 0), the image will
;;; exit upon receipt.  If this argument is the constant
;;; shutdown-context-only-flag-set (currently 1), the image will shut down the
;;; connection but keep listening for new connections.  Any other value for this
;;; argument causes undefined results.

(def-icp-message-type kill-foreign-function-server
    ((integer shutdown-context-only-flag)
     (text-string out-of-band-message))
  ;;
  ;; G2 does not receive kill-foreign-function-server messages,
  ;; hence there is no ICP handler body here.
  )

(def-icp-message-type shut-down-foreign-server-context ()
  ;;
  ;; G2 does not receive shut-down-foreign-server-context messages,
  ;; hence there is no ICP handler body here.
  )







;;;; ICP Messages from the Foreign Image

;;; ICP handler for signal-foreign-function-error



(def-icp-message-type signal-foreign-function-error
		      ((integer local-foreign-function-error)
		       (integer signal-caught-if-any)
		       (integer errno-if-applicable)
		       (text-string error-string)
		       (integer spare-code)
		       (text-string out-of-band-message))
  spare-code out-of-band-message
  (let ((foreign-function-name
	  (let ((foreign-entry?
		  (entry-for-foreign-function-call
		    current-foreign-function-call-info)))
	    (if foreign-entry?
		(foreign-function-name foreign-entry?)
		"(no function)")))
	(foreign-function-image
	  (let ((image-info?
		  (image-for-foreign-function-call
		    current-foreign-function-call-info)))
	    (if image-info?
		(namestring-of-foreign-image image-info?)
		"(no image)"))))
    (case local-foreign-function-error
      (FFS_CONNECTION_OPEN_ALREADY
       (notify-user
	 "Connection open already for foreign image \"~a\"."
	 foreign-function-image))
      (FFS_SIGNAL_CAUGHT_DURING_CALL
       (stack-error
	 cached-top-of-stack
	 "Error in call to foreign function \"~a\" in image \"~a\"  ~
          Signal ~a (\"~a\") caught."
	 foreign-function-name
	 foreign-function-image
	 signal-caught-if-any
	 error-string))
      (FFS_UNKNOWN_FUNCTION
       (stack-error
	 cached-top-of-stack
	 "Foreign function \"~a\" is not present in foreign image \"~a\"."
	 foreign-function-name
	 foreign-function-image))
      (FFS_UNKNOWN_RETURN_TYPE
       (stack-error
	 cached-top-of-stack
	 "Unknown return type ~a from foreign function \"~a\" in image \"~a\""
	 errno-if-applicable
	 foreign-function-name
	 foreign-function-image))
      (FFS_UNSPECIFIED_ERROR
       (notify-user
	 "Unspecified problem in foreign function \"~a\" in image \"~a\"~%~
          Code: ~a~%Signal: ~a~%Errno: ~a~%Errno string: \"~a\""
	 foreign-function-name
	 foreign-function-image
	 local-foreign-function-error
	 signal-caught-if-any
	 errno-if-applicable
	 error-string)))))

;; jh per jra & cpm, 9/5/91.  Stack error optimization.  After a foreign
;; function is called, G2 hangs, waiting for the foreign image to return a
;; value.  If a error condition occurs in the foreign image, it will send the
;; ICP message signal-foreign-function-error.  The handler for this message
;; dispatches on the type of error.  For those error types that are guaranteed
;; always to occur during the wait for a return value, we can call stack-error
;; and pass it cached-top-of-stack, which is bound by
;; call-connected-foreign-function throughout the dynamic extent of the wait.
;; Otherwise, we have to call notify-user, because the condition is not properly
;; a stack error if it can occur even when no stack is active.  There are also
;; notes in the foreign image code foreign.c which enjoin developers to observe
;; this constraint.




;;; ICP handler for provide-foreign-function-registry

;;; Sometimes the user wants to "overwrite" the association between a
;;; foreign-function-declaration and a foreign image.  This can be done by
;;; disconnecting the old foreign and connecting to the new foreign image.

(def-substitution-macro convert-foreign-type-tag-to-symbol (type-tag) ;fixnum
  (case type-tag
    (#.foreign-function-integer-type-tag  'integer)
    (#.foreign-function-real-type-tag     'real)
    (#.foreign-function-symbol-type-tag   'symbol)
    (#.foreign-function-text-type-tag     'text)))
  
(defun-allowing-unwind update-foreign-function-registry 
       (list-of-foreign-function-registrations icp-socket-of-foreign-image)
  (let ((image-info
	  (get-foreign-image-info-from-icp-socket icp-socket-of-foreign-image))
	(entries-to-connect nil))

    ;; collect new foreign function entries
    (loop for registration in list-of-foreign-function-registrations
	  do
	  (let ((name 
		  (foreign-function-registration-name registration))
		(id 
		  (foreign-function-registration-id registration))
		(argcount 
		  (foreign-function-registration-argcount registration))
		(typelist 
		  (loop for type-tag
			in (foreign-function-registration-typelist 
			     registration)
			collect
			(convert-foreign-type-tag-to-symbol type-tag)
			using icp-cons
			finally 
			(reclaim-icp-list 
			  (foreign-function-registration-typelist 
			    registration))))
		(return-type
		  (convert-foreign-type-tag-to-symbol 
		    (foreign-function-registration-return-type 
		      registration))))

	    (multiple-value-bind (entry old-image-info?)
		(get-or-make-foreign-function-entry 
		  name id argcount typelist return-type image-info)

	      ;; jh, 9/6/91.  Per the release notes, we now relink a foreign
	      ;; function when its name is present in a newly-connected image.  If
	      ;; the new image has the wrong arglist or return type, the link will
	      ;; ultimately fail, but there is currently no way to get the old,
	      ;; working definition back.  We might consider making the foreign
	      ;; function linker more intelligent, so that it always links a
	      ;; declaration to the most recently connected foreign image for
	      ;; which there is an arglist and return type match.
	      (when old-image-info?
		(notify-user
		  "Relinking function \"~a\" to foreign image \"~a\".  ~
                   This replaces the link to foreign image \"~a\"."
		  name
		  (namestring-of-foreign-image image-info)
		  (namestring-of-foreign-image old-image-info?))
		(setf (foreign-function-entries-for-image old-image-info?)
		      (delete-icp-element
			entry
			(foreign-function-entries-for-image old-image-info?)))
		(reclaim-text-string name))
	      
	      (setf (foreign-image-info entry) image-info)
	      (icp-push entry entries-to-connect)))
	  finally
	  (reclaim-icp-list registration))

    ;; find foreign-function-declaration frames to connect to
    (protected-let ((names-of-entries
		      (loop for entry in entries-to-connect
			    collect (foreign-function-name entry)
				      using icp-cons)
		      (reclaim-icp-list names-of-entries)))
      (loop for declaration 
		being each class-instance of 'foreign-function-declaration
	    for declaration-name? = 
		(name-in-foreign-image declaration)
	    for entry-to-connect? =
		;; jh, 8/15/91.  Declaration-name?  may be nil, since we may be
		;; passed an Incomplete yet active foreign-function-declaration.
		;; (This is part of the transient statements enhancement.)
	        (and declaration-name?
		     (loop for possible-entry in entries-to-connect
			   for name-of-entry in names-of-entries
			   thereis 
			   (and (string=w declaration-name? name-of-entry)
				possible-entry)))
	    do
	    (update-foreign-function-linking
	      declaration
	      entry-to-connect?
	      nil))) ;update-declaration-with-no-entry-p

    ;; store foreign function entries together to handle disconnection 
    (setf (foreign-function-entries-for-image image-info) 
	  entries-to-connect)
    ))

(def-icp-message-type provide-foreign-function-registry
    (list-of-foreign-function-registrations?
      (integer spare-code)
      (text-string out-of-band-message))
  spare-code out-of-band-message
  (let* ((image-info
	   (get-foreign-image-info-from-icp-socket current-icp-socket))
	 (image-pathname? (pathname-of-foreign-image? image-info))
	 (namestring-of-connection-attempt
	   (if image-pathname?
	       (gensym-namestring-as-text-string image-pathname?)
	       (twith-output-to-text-string
		 (twrite-foreign-image-connection-spec
		   (connection-specification-to-foreign-image image-info))))))
    (cond
      (list-of-foreign-function-registrations?
       (notify-user "Successfully connected to foreign image ~s."
		    namestring-of-connection-attempt)
       (setq unused-foreign-image-indices
	     (nconc unused-foreign-image-indices
		    (unused-foreign-image-indices image-info)))
       (setf (unused-foreign-image-indices image-info) nil)
       (update-foreign-function-registry 
	 list-of-foreign-function-registrations?
	 current-icp-socket))
      (t (writing-icp-message-group
	     ((icp-output-port current-icp-socket))
	   (send-icp-shut-down-foreign-server-context))
	 ;; Registration failed probably because another
	 ;; G2 or program is using this port. Assuming
	 ;; it will remain in use for some time, don't use
	 ;; it again, since it hangs G2 for about a second
	 ;; while trying each port.
	 (setf (foreign-image-port-or-task-index image-info) nil)
	 (flush-and-shutdown-icp-socket current-icp-socket)
	 
	 (cond ((or (external-foreign-image-p image-info)
		    (>=f (foreign-connection-retry-count image-info)
			maximum-retries-for-foreign-image-connection))
		(setq unused-foreign-image-indices
		      (nconc unused-foreign-image-indices
			     (unused-foreign-image-indices image-info)))
		(setf (unused-foreign-image-indices image-info) nil)
		(notify-user
		  "Can't acquire lock in foreign image ~s."
		  namestring-of-connection-attempt))
	       (t (initialize-foreign-function-image-if-possible
		    (let ((extant-pathname?
			    (pathname-of-foreign-image? image-info)))
		      (and extant-pathname?
			   (copy-gensym-pathname extant-pathname?)))
		    (foreign-connection-retry-count image-info))))))
    (reclaim-text-string namestring-of-connection-attempt)))

;; jh, 11/2/93.  Modified the ICP handler for provide-foreign-function-registry
;; to announce successfully connected foreign image, or retry the connection
;; Only when we have received a non-nil foreign function registry do we know
;; that the foreign image is actually the one that belongs to this G2 process.


;;; ICP handler for return-foreign-function-value

(def-icp-message-type return-foreign-function-value
		      (foreign-function-value)
  (unless foreign-function-value
    (stack-error ;jh per jra & cpm, 9/5/91.  Stack error optimization.
      cached-top-of-stack
      "Bad value returned from foreign function \"~a\" in image \"~a\"."
      (let ((foreign-entry?
	      (entry-for-foreign-function-call
		current-foreign-function-call-info)))
	(if foreign-entry?
	    (foreign-function-name foreign-entry?)
	    "(no function)"))
      (namestring-of-foreign-image
	(image-for-foreign-function-call
	  current-foreign-function-call-info))))
	    
  (setf (result-of-foreign-function-call?
	  current-foreign-function-call-info)
	foreign-function-value))






;;;; Toplevel Foreign Function Calling Machinery

;;; The G2 evaluator calls foreign functions using new-call-foreign-function.
;;; This function takes four arguments, an instance of the class
;;; foreign-function-declaration, the evaluation stack, a location in the stack,
;;; and an argument count.  This function performs some consistency checks and
;;; then transmits the ICP message call-foreign-function to the foreign image.
;;; The image returns a result using the ICP message
;;; return-foreign-function-value.

;;; New-call-foreign-function consults a single system table parameter,
;;; foreign-function-timeout-interval.  This determines how long G2 will wait
;;; for the return value from a foreign function.  This defaults to 30 seconds
;;; of real time.  This parameter may be overridden by attributes in individual
;;; foreign-function-declarations.

;; jh per jra & cpm, 9/5/91.  Stack error optimization.  Changed many calls of
;; stack-error to stack-error-new.  This enables us to pass back the
;; top-of-stack explicitly on error, which in turn helps with a project to
;; restrict the occurrence of setjmps (and concomitant loss of register
;; optimization) in the translated code.  In place of the error-level argument
;; taken by stack-error, stack-error-new takes the top of the evaluator stack.
;; This is passed into new-call-foreign-function by the call-function
;; instruction (#94) in STACK-INST.  The ICP handlers that wait for the return
;; value of a foreign function must refer to the special variable
;; cached-top-of-stack.  This is bound by call-connected-foreign-function before
;; the wait begins for the return value.  Another wrinkle is handling error
;; signals from the foreign image.  For details, see the comments after
;; signal-foreign-function-error, earlier in this file.

(def-system-variable cached-timed-out-foreign-function-name? G2-FOREIGN nil)

;; jh, 9/6/91.  Added the following reconnect attempt per the release notes.  We
;; disconnect the foreign image and then try to reconnect to it if there was a
;; timeout.  Note that we notify the user of the reconnect in
;; connect-to-foreign-image, so the user has a way of checking the system table
;; setting.

;; jh, 12/20/92.  We now enter a permanent consing area in
;; kill-foreign-image-and-possibly-reconnect so that frame notes work properly
;; when they are updated to reflect the fact that the image has been killed..

(defun kill-foreign-image-and-possibly-reconnect (foreign-image-info)
  (let ((reconnect-p
	  (reconnect-to-foreign-image-after-timeout? timing-parameters)))
    (cond
      ((and reconnect-p (external-foreign-image-p foreign-image-info))
       (let ((saved-connection-spec
	       (loop for component
			 in (connection-specification-to-foreign-image foreign-image-info)
		     collect (if (stringp component)
				 (copy-text-string component)
				 component)
		     using icp-cons)))
	 (with-permanent-gensym-float-creation 
	   (kill-foreign-image foreign-image-info)
	   (connect-to-external-foreign-image saved-connection-spec))))
      (reconnect-p
       (let ((saved-pathname
	       (copy-gensym-pathname
		 (pathname-of-foreign-image? foreign-image-info))))
	 (with-permanent-gensym-float-creation 
	   (kill-foreign-image foreign-image-info)
	   (connect-to-foreign-image saved-pathname))))
      (t (with-permanent-gensym-float-creation
	   (kill-foreign-image foreign-image-info))))))


(defun-allowing-unwind call-connected-foreign-function
    (foreign-function-entry?
      foreign-image-info
      foreign-function-declaration
      stack
      stack-location
      argument-count
      top-of-stack)
  (protected-let 
      ((foreign-image-socket ;never nil at this point
	 (icp-socket-connecting-to-foreign-image
	   foreign-image-info)
	 ;; Undo for foreign-image-socket:
	 (unless (icp-socket-p foreign-image-socket) ;i.e., reclaimed
	   ;; jh, 5/4/95.  If our embedded process-icp-sockets had to reclaim
	   ;; foreign-image-socket, it will reappear in active-icp-sockets and
	   ;; be doubly reclaimed unless we eradicate it here.
	   (if (eq (car active-icp-sockets) foreign-image-socket)
	       (icp-pop active-icp-sockets)
	       (loop for previous-cons on active-icp-sockets
		     for maybe-foreign-image-socket? = (cadr previous-cons)
		     while maybe-foreign-image-socket?
		     when (eq maybe-foreign-image-socket? foreign-image-socket)
		       do (reclaim-icp-cons (cdr previous-cons))
			  (setf (cdr previous-cons) (cddr previous-cons))
			  (loop-finish)))
	   ;; jh, 12/20/92.  Note that we have to kill the foreign image
	   ;; completely if process-icp-sockets ended up reclaiming
	   ;; foreign-image-socket.  Previously, we violated the "never nil"
	   ;; assertion above by simply setting the
	   ;; icp-socket-connecting-to-foreign-image of foreign-image-info to
	   ;; nil without removing foreign-function-info from
	   ;; all-foreign-function-images?.
	   (kill-foreign-image-and-possibly-reconnect foreign-image-info))))
    (let ((timeout-interval
	    (fixnum-time-interval
	      (*f fixnum-time-units-per-second
		  (let ((local-timeout-interval
			  (timeout-interval foreign-function-declaration)))
		    (if (eql 'default local-timeout-interval)
			(foreign-function-timeout-interval 
			  timing-parameters)
			local-timeout-interval))))))
      
      ;; call the foreign function in the image
      (writing-icp-message-group 
	  ((icp-output-port foreign-image-socket))

	(send-icp-call-foreign-function 
	  (foreign-function-id foreign-function-entry?))
	(loop for arg-offset from 0 below argument-count
	      for argument = (svref stack (+f stack-location arg-offset))
	      do
	  (write-icp-foreign-function-argument argument)))
      (when icp-output-ports-to-flush
	(flush-icp-output-ports))
      
      ;; Result-of-foreign-function-call?  is returned to the evaluator and
      ;; reclaimed there, so we can overwrite it here.  This slot is set in the
      ;; ICP reader for return-foreign-value.
      (setf (result-of-foreign-function-call?
	      current-foreign-function-call-info) nil)
      
      ;; wait for a value from the foreign image
      (protected-let
	  ((active-icp-sockets 
	     (icp-list foreign-image-socket)
	     (when (icp-socket-p foreign-image-socket) ;i.e., not reclaimed
	       ;; jh, 5/4/95.  Only do this if the process-icp-sockets call
	       ;; below didn't.
	       (reclaim-icp-list active-icp-sockets)))
	   (during-ffi-call? t))	; force event-cycle to handle messages directly, avoiding scheduler.

	(setq cached-top-of-stack top-of-stack) ;binding is slow

	(with-scheduler-disabled	; stop event loop from invoking the scheduler, which would be bad.
	    (ne-set-next-timer-event 500)
	  
	  (when cached-timed-out-foreign-function-name?
	    (reclaim-text-string 
	      cached-timed-out-foreign-function-name?))
	  (setq cached-timed-out-foreign-function-name?
		(copy-text-string
		  (foreign-function-name
		    (entry-for-foreign-function-call
		      current-foreign-function-call-info))))		   
	  
	  (loop with start-time = (get-fixnum-time)
		;; handle network and display events, no scheduling can happen here.
		do (g2-event-cycle-handling-windows-quit)
		until (result-of-foreign-function-call?
			current-foreign-function-call-info)
		until (>f (fixnum-time-difference 
			    (get-fixnum-time t) ;i.e., don't cache
			    start-time)
			  timeout-interval)
		do (ne-set-next-timer-event 500)  ;sleep for at most 1/2 second... 

		finally
		  (return
		    (let ((foreign-result?
			    (result-of-foreign-function-call?
			      current-foreign-function-call-info)))
		      (cond 
			(foreign-result?
			 foreign-result?)
			((icp-socket-connecting-to-foreign-image foreign-image-info)
			 ;; ncc, 12 Aug 1996. only do this if FFL still
			 ;; connected -- otherwise, the bridge is no longer
			 ;; there and the function did not, strictly speaking,
			 ;; time out.
			 ;;
			 ;;jh, 12/20/92.  Save the name of the
			 ;; foreign function, since it will be lost if we
			 ;; call kill-foreign-image.  The name will be
			 ;; reclaimed the next time a foreign function times
			 ;; out.
			 (when cached-timed-out-foreign-function-name?
			   (reclaim-text-string 
			     cached-timed-out-foreign-function-name?))
			 (setq cached-timed-out-foreign-function-name?
			       (copy-text-string
				 (foreign-function-name
				   (entry-for-foreign-function-call
				     current-foreign-function-call-info))))

			 (kill-foreign-image-and-possibly-reconnect
			   foreign-image-info)

			 ;; Finally, report a stack error.
			 (return-from call-connected-foreign-function
			   (values
			     nil
			     (tformat-stack-error-text-string
			       "Foreign function \"~a\" timed out after ~a seconds."
			       cached-timed-out-foreign-function-name?
			       (convert-fixnum-time-difference-to-seconds
				 timeout-interval)))))

			(t
			 (kill-foreign-image-and-possibly-reconnect
			   foreign-image-info)

			 ;; Finally, report a stack error.
			 (return-from call-connected-foreign-function
			   (values
			     nil
			     (tformat-stack-error-text-string
			       "Connection lost to Foreign function library -- call aborted.")))))))))))))

(defun new-call-foreign-function 
    (foreign-function-declaration
      stack
      stack-location
      argument-count
      top-of-stack)

  ;; jh, 8/15/91.  This is part of the transient statements enhancement.
  (when (frame-status foreign-function-declaration)
    (return-from new-call-foreign-function
      (values
	nil
	(tformat-stack-error-text-string
	  "The declaration for foreign function \"~a\" is not OK.  ~
           This function cannot be called."
	  (or (name-in-foreign-image foreign-function-declaration)
	      (get-or-make-up-designation-for-block 
		foreign-function-declaration))))))
  
  (let ((foreign-function-entry?
	  (foreign-function-image-entry? 
	    foreign-function-declaration)))
    
    (cond ((null foreign-function-entry?)
	   (return-from new-call-foreign-function
	     (values
	       nil
	       (tformat-stack-error-text-string
		 "Cannot locate foreign function \"~a\"."
		 (or (name-in-foreign-image foreign-function-declaration)
		     (get-or-make-up-designation-for-block 
		       foreign-function-declaration))))))

	  ((/=f (foreign-function-argument-count foreign-function-entry?)
		argument-count)
	   (return-from new-call-foreign-function
	     (values
	       nil
	       (tformat-stack-error-text-string
		 "Wrong number of arguments passed to foreign function \"~a\"."
		 (or (name-in-foreign-image foreign-function-declaration)
		     (get-or-make-up-designation-for-block 
		       foreign-function-declaration))))))
	  
	  (t (let ((foreign-image-info?
		     (foreign-image-info foreign-function-entry?)))
	       (cond ((null foreign-image-info?)
		      (return-from new-call-foreign-function
			(values
			  nil
			  (tformat-stack-error-text-string
			    "Cannot locate foreign image for function \"~a\"."
			    (or (name-in-foreign-image foreign-function-declaration)
				(get-or-make-up-designation-for-block 
				  foreign-function-declaration))))))
		     (t (setf (entry-for-foreign-function-call
				current-foreign-function-call-info)
			      foreign-function-entry?)
			(setf (image-for-foreign-function-call
				current-foreign-function-call-info)
			      foreign-image-info?)
			(call-connected-foreign-function
			  foreign-function-entry?
			  foreign-image-info?
			  foreign-function-declaration
			  stack
			  stack-location
			  argument-count
			  top-of-stack))))))))

;; jh, 8/15/91.  Added get-or-make-up-designation-for-block in several notify-user
;; forms in this module.  This is because it is now possible to be passed a
;; foreign function declaration that has status Incomplete but is active, and
;; referring to a foreign function as NIL is bound to alienate users.  (This is
;; part of the transient statements enhancement.)



;; jh per ac, 6/19/91.  Added call-foreign-function as a stub until its callers
;; (in SIMULATE3, EVAL, and PROC-EVAL) can eradicate it.

(defun call-foreign-function (name arguments)
  (declare (ignore arguments))
  (notify-user
    "Attempt to call an old-style foreign function ~a.  ~
     These foreign functions are no longer implemented."
    name)
  (abort))



;;;; Menu Choice and Init File Machinery

;;; See FACILITIES and KB-LOAD1.




;;;; Testing

;; Test-generate-registration-list exists so that we can test reclaimation of the
;; foreign registry components after they are transmitted by ICP.

;; A simple test KB is in ma:>jh>kb>foreign.kb.  Files for the foreign image are
;; ma:>jh>c>foreign_test.c, ma:>jh>kb>foreign.kb, and an overlay file called
;; glue.c should be generated from ma:>jh>c>glue.template with the foreign_overlay
;; utility.  The foreign image wa:/usr/jh/foreign/FFS is created using
;; ma:>jh>c>MakeFFS.make on Washington.

#+development
(defun test-generate-foreign-registration-list ()
  (icp-list
    (icp-list (copy-constant-wide-string #w"g2_function1") ;name
	      0                                 ;id
	      2                                 ;argcount
	      (icp-list                         ;typelist
		foreign-function-text-type-tag
		foreign-function-integer-type-tag))
    (icp-list (copy-constant-wide-string #w"g2_function2")
	      1
	      0
	      nil)))


;; Test-generate-foreign-icp-socket wants to connect to a spawned process on
;; New Jersey, namely /usr/jh/foreign/FFS.fgn.

#+development
(defun test-generate-foreign-icp-socket ()
  (setq all-foreign-function-images? nil) ;dropped!
  (let (;(socket (make-icp-socket-structure nil nil nil))
	(image-info (make-foreign-function-image-info)))
    (setf (pathname-of-foreign-image? image-info)
	  (gensym-pathname "nj:/usr/jh/foreign/FFS.fgn"))
    (setf (namestring-of-foreign-image image-info)
	  (gensym-namestring-as-text-string
	    (pathname-of-foreign-image? image-info)))
    (multiple-value-bind (port-or-task unused-index)
	(get-next-unused-foreign-image-port-or-task)
      (setf (foreign-image-port-or-task image-info)
	    port-or-task)
      (setf (foreign-image-port-or-task-index image-info) 
	    unused-index))
    (setf (icp-socket-connecting-to-foreign-image image-info)
	  (create-foreign-image-connection-given-host "nj" image-info))
    (icp-push image-info all-foreign-function-images?)
    (icp-socket-connecting-to-foreign-image image-info)))


#+development
(defun test-update-foreign-registry (&optional overwriting-p)
  ;; overwriting will notify the user
  (unless overwriting-p
    (clear-foreign-function-registry-internal foreign-function-registry))
  (update-foreign-function-registry 
    (test-generate-foreign-registration-list)
    (test-generate-foreign-icp-socket)))



;; Test-provide-foreign-registry is incompatable with
;; test-update-foreign-registry.  You have to clean up active-icp-sockets and
;; reclaim the single foreign-image-info structure in all-foreign-images.

#+development
(defun-allowing-unwind test-provide-foreign-registry ()
  ;; spawn FFS, then ...
  (test-generate-foreign-icp-socket)
  (writing-icp-message-group 
      ((icp-output-port 
	 (icp-socket-connecting-to-foreign-image
	   (first all-foreign-function-images?))))
    (send-icp-request-foreign-function-registry 0 #.(stringw ""))))



#+development
(defun print-foreign-function-registry ()
  (if all-foreign-function-images?
      (loop for image-info in all-foreign-function-images?
	    do
	    (format t "~&Foreign image: \"~a\"~%"
		    (namestring-of-foreign-image image-info))
	    (loop for entry in (foreign-function-entries-for-image image-info)
		  do
		  ;; e.g. "function1(integer, text, symbol) = real"
		  (apply (lisp-format)
			 "~&~2t~a~*(~#[~;~a~:;~@{~a~^, ~}~]) = ~1@*~a~%"
			 (foreign-function-name entry)
			 (foreign-function-return-type entry)
			 (foreign-function-type-list entry)))
	    (format t "~%"))
      (format t "~&empty foreign function registry~%")))


#+development
(defun-allowing-unwind test-new-call-foreign-function ()
  ;; successfully call test-provide-foreign-function-registry, then ...
  (let* ((foreign-function-declaration
	  (first
	    (foreign-function-declarations-with-this-name
	      (second ;first
		(foreign-function-entries-for-image
		  (first all-foreign-function-images?))))))
;	 (argument-1 (make-evaluation-text "ONE"))
;	 (argument-2 (make-evaluation-integer 1))
	 (argument-list nil) ;(list argument-1 argument-2))
	 (argument-count (length argument-list))
	 (stack (make-array argument-count
			    :initial-contents argument-list))
	 (stack-location 0)
	 (top-of-stack 0))
    (multiple-value-bind (result-or-error-level message?)
	(catch :procedure-error
	  (new-call-foreign-function
	    foreign-function-declaration
	    stack
	    stack-location
	    argument-count
	    top-of-stack))
      (if message?
	  (notify-user message?)
	  result-or-error-level))))




#+development
(defun test-connected-foreign-image-frame-note (frame)

  (let ((fake-image-info (make-foreign-function-image-info)))
    (setf (namestring-of-foreign-image fake-image-info)
	  "/usr/jh/FFS")
    (set-slot-value ;now a doubly linked list!
      frame
      'unlinkable-foreign-image-info?
      fake-image-info))

  (delete-frame-note-if-any
    'unlinked-to-unconnected-foreign-image
    frame)

  (add-frame-note 
    'unlinked-to-connected-foreign-image
    frame
    (slot-value-list
;      (slot-value-list 'argcount-mismatch 3 4)
      (slot-value-cons 'argtype-mismatch
		       (slot-value-list
			 (slot-value-list 2 'real 'integer)
			 (slot-value-list 4 'symbol 'text)))
      (slot-value-list 'return-type-mismatch 'integer 'real)
      )
    t
    nil))


#+development
(defvar foreign-image-with-bad-declaration nil)


#+development
(defun test-update-registry-on-bad-declaration ()
  ;; needs a declaration that doesn't have 2 args, or where both args aren't
  ;; integers, or where an integer isn't returned
  (let ((fake-image-info (make-foreign-function-image-info)))
    (setq foreign-image-with-bad-declaration fake-image-info)
    (setf (icp-socket-connecting-to-foreign-image fake-image-info) 1)
    (setf (namestring-of-foreign-image fake-image-info) 
	  (copy-constant-wide-string #w"/usr/jh/FFS"))
    (let ((all-foreign-function-images? 
	    (cons fake-image-info all-foreign-function-images?))
	  (registry-list
	    (icp-list
	      (icp-list (copy-constant-wide-string #w"noop_latency_test") ;name
			0                                      ;id
			2                                      ;argcount
			(icp-list                              ;typelist
			  foreign-function-integer-type-tag
			  foreign-function-integer-type-tag)
			foreign-function-integer-type-tag      ;return type
			))))
      (update-foreign-function-registry
	registry-list
	1))))


;; To test per-directory menu for foreign images, there are four fake image
;; files on ma:>jh>, named deletable-image<n>.fgn, where n ranges from 1 to four
;; inclusive.  The test pretends that images 1 and 2 are connected (by setting
;; all-foreign-function-images? to be a list two partially-filled
;; foreign-image-info structures) and 3 and 4 are not connected.  Thus
;; test-foreign-connect-per-directory-menu should describe the pathnames of
;; images 3 and 4 (since they are connectable) and
;; test-foreign-disconnect-per-directory-menu should describe 1 and 2 (since
;; they are not connectable).

#+development
(defun set-up-foreign-per-directory-test ()
  (setq all-foreign-function-images? nil)
  (let ((new-info
	  (make-foreign-function-image-info)))
    (setf (pathname-of-foreign-image? new-info)
	  (gensym-probe-file "ma:>jh>deletable-image1.fgn"))
    (push new-info all-foreign-function-images?))
  (let ((new-info
	  (make-foreign-function-image-info)))
    (setf (pathname-of-foreign-image? new-info)
	  (gensym-probe-file "ma:>jh>deletable-image2.fgn"))
    (push new-info all-foreign-function-images?)))

#+development
(defun test-foreign-connect-per-directory-menu ()
  (mapcar #'describe
	  (get-directory-for-non-kb-file-type
	    (gensym-pathname "ma:>jh>default")
	    'foreign-image
	    'connect-to-foreign-image
	    (gensym-pathname "ma:>jh>"))))

#+development
(defun test-foreign-disconnect-per-directory-menu ()
  (mapcar #'describe
	  (get-directory-for-non-kb-file-type
	    (gensym-pathname "ma:>jh>default")
	    'foreign-image
	    'disconnect-from-foreign-image
	    (gensym-pathname "ma:>jh>"))))


