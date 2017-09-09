;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module FILE-SYSPROC

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved

;;; John Hodgkinson, Mark H. David

;; 20 March 1991




;;;; Forward References

(declare-forward-reference make-transient-item function STACK-ACTS)

(declare-forward-reference icp-socket-of-interface-object function G2-RPC1)

(declare-forward-reference make-full-pathname function QUERIES)

;;;; File Operations for the G2 User

;;; This module provides tools to allow the user to perform file-related
;;; operations from inside G2.  Each operation takes the form of a system
;;; procedure, which is similar to a user-written procedure, except that its text
;;; is hidden from the user and it permits calls to Lisp functions.

;;; A new class of item, the G2-stream, is introduced to contain information
;;; about file access.  Many of the file-related system procedures accept or
;;; return instances of this class.

;;; Supported operations:

;;;   File Access Procedures
;;;   ---- ------ ----------
;;; open-file-for-read             (filestring: text)        => g2-stream
;;; open-file-for-write            (filestring: text)        => g2-stream
;;; open-file-for-append           (filestring: text)        => g2-stream
;;; open-file-for-read-and-write   (filestring: text)        => g2-stream
;;; close-file                     (stream: class g2-stream) => truth-value
;;; close-all-open-g2-streams      ()                        => truth-value
;;; set-file-position              (stream: class g2-stream,
;;;                                 new-position: integer
;;;                                 extend-file-if-necessary: truth-value)  => truth-value
;;; rename-file                    (old-filestring: text,
;;;                                 new-filestring: text)        => truth-value
;;; delete-file                    (filestring: text)        => truth-value
;;;
;;;   File Reading and Writing Procedures
;;;   ---- ------- --- ------- ----------
;;; read-line                      (stream: class g2-stream) => text-string      
;;; read-byte                      (stream: class-g2-stream) => integer
;;;
;;; [Note: the following three procedures (write-line, write-string, and
;;; write-text) have their argument order reversed on the Lisp side.  The
;;; following order describes how the system procedures will look in G2.]
;;;
;;; write-line                     
;;;                                (stream: class g2-stream,
;;;                                 line: text)              => truth-value
;;; write-string                   (stream: class g2-stream,
;;;                                 string: text)            => truth-value
;;; write-byte                     (stream: class g2-stream,
;;;                                 byte: integer)           => truth-value
;;; write-bytes                    (stream: class g2-stream,
;;;                                 bytes: sequence)         => truth-value
;;; float-to-bytes                 (n: float)                => 8 integer values
;;; bytes-to-float                 (b1 through b8: integer)  => float
;;;
;;;   Filestring Parsing Procedures
;;;   ---------- ------- ----------
;;; file-host-string               (filestring: text)        => text
;;; file-device-string             (filestring: text)        => text
;;; file-directory-string          (filestring: text)        => text
;;; file-directory-string-to-list  (filestring: text)        => class text-list
;;; file-directory-list-to-string  (directory-list: class text-list) => text
;;; file-base-name-string          (filestring: text)        => text
;;; file-extension-string          (filestring: text)        => text
;;; file-version-string            (filestring: text)        => text
;;; collect-into-filestring        (host:      text,
;;;                                 device:    text,
;;;                                 directory: text,
;;;                                 base-name: text,
;;;                                 extension: text,
;;;                                 version:   text)         => text
;;; partition-filestring           (filestring: text)        => 6 text values 
;;;
;;;   File Attribute Procedures
;;;   ---- --------- ----------
;;; type-of-file-system            ()                        => symbol
;;; file-exists                    (filestring: text)        => truth-value
;;; file-names-are-identical       (filestring1: text,
;;;                                 filestring2: text)       => truth-value
;;; length-of-file                 (stream: class g2-stream) => integer
;;; latest-date-file-was-modified  (filestring: text)        => float
;;; latest-date-file-was-accessed  (filestring: text)        => float
;;; latest-date-file-attributes-were-changed (filestring: text) => float
;;;
;;;   File-related Error Handling
;;;   ------------ ----- --------
;;;  [last-status-message-for-file is obsolescent, since we now return error
;;;   strings directly to G2, which signals them inside the system procedure on its
;;;   side.]

;;; 
;;;   Directory-related Procedures
;;;   ----------------- ----------
;;; directory-exists                  (directory: text)      => truth-value
;;; files-in-directory                (directory: text)      => class text-list
;;; subdirectories-in-directory       (directory: text)      => class text-list
;;; default-directory                 (directory: text)      => text
;;; change-default-directory          (directory: text)      => truth-value
;;; disk-space-available-in-directory (directory: text)      => integer
;;; devices-on-machine                ()                     => class text-list
;;;
;;;   Process-related Procedures
;;;   --------------- ----------
;;; spawn-process-to-run-command-line     (command: text)           => float-process-id
;;; spawn-process-with-arguments          (command: text)           => float-process-id
;;; process-exists                        (process-id: float)       => truth-value
;;; kill-process                          (process-id: float)       => truth-value
;;; spawn-remote-process                  (command: text,
;;;                                        window: class g2-window) => float-process-id
;;; spawn-remote-process-to-run-command-line
;;;                                       (command: text,
;;;                                        window: class g2-window) => float-process-id
;;; remote-process-exists                 (process-id: float,
;;;                                        window: class g2-window) => truth-value
;;; kill-remote-process                   (process-id: float,
;;;                                        window: class g2-window) => truth-value
;;; get-command-line-argument-from-launch (n: integer)              => text
;;;
;;;   Network Information
;;;   ------- -----------
;;; get-host-name                        ()                     => text
;;; get-port-number-or-name              ()                     => text
;;; get-network-type                     ()                     => text
;;; get-port-number-or-name-given-index  (index: integer)       => text ;>= 4.0
;;; get-network-type-given-index         (index: integer)       => text ;>= 4.0
;;;
;;;   Version Information
;;;   ------- -----------
;;; get-software-version                 ()                     => text
;;;
;;;   Time-related Procedures
;;;   ------------ ----------
;;; unix-time                        ()                             => float
;;; unix-time-at-start               ()                             =>float
;;; unix-time-to-text                (time: float,
;;;                                   include-seconds: truth-value) => text
;;;   Miscellaneous Utilities
;;;   ------------- ---------
;;; beep [defined in CONTROLS]       ()                     => truth-value

;;; [nyi] = not yet implemented

;;;; Conser for System Procedures

;; Also note that file-related system procedures use path-conses and
;; network-related system procedures use icp-conses.

(defconser sysproc FILE-SYSPROC)

(defun reclaim-sysproc-list-function (sysproc-list)
  (reclaim-sysproc-list sysproc-list))

#+unused
(defun copy-list-using-sysproc-conses-function (sysproc-list)
  (copy-list-using-sysproc-conses sysproc-list))



;; Text Conversion Style section moved past section with the g2-stream class
;; definition, below. (MHD 5/4/00)





;;;; G2-stream item class

;; Never use define-predicate on the def-class for g2-stream .  G2-stream-p
;; already exists and refers to the internal streams, not to the external frame.

(def-class (g2-stream (item entity) not-user-instantiable do-not-put-in-menus)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      100 50 
      ((outline (40 9) (40 40) (67 40) (67 9)) 
       (lines (46 17) (62 17))
       (lines (48 21) (55 21))
       (lines (47 25) (63 25))
       (lines (47 31) (61 31))
       (lines (49 35) (62 35)) 
       (filled-polygon ((20 29) (20 33) (12 33) (12 29)) 
		       ((20 29) (20 33) (12 33)) 
		       ((12 33) (12 29) (20 29)))
       (filled-polygon ((32 29) (32 33) (24 33) (24 29)) 
		       ((32 29) (32 33) (24 33)) 
		       ((24 33) (24 29) (32 29)))
       (filled-polygon ((45 31) (36 37) (36 25))
		       ((45 31) (36 37) (36 25)))
       (filled-polygon ((70 15) (70 19) (62 19) (62 15))
		       ((70 15) (70 19) (62 19))
		       ((62 19) (62 15) (70 15)))
       (filled-polygon ((82 15) (82 19) (74 19) (74 15))
		       ((82 15) (82 19) (74 19))
		       ((74 19) (74 15) (82 15)))
       (filled-polygon ((95 17) (86 23) (86 11))
		       ((95 17) (86 23) (86 11))))))
  (name-of-file 
    nil vector-slot not-user-editable (type attribute) do-not-save)
  (file-system
    nil vector-slot not-user-editable (type attribute) do-not-save)
  (access-direction 
    closed vector-slot not-user-editable (type attribute) do-not-save)
  (position-in-file
    nil vector-slot not-user-editable (type attribute) do-not-save)
  (g2-stream-status
    newly-created vector-slot not-user-editable (type attribute) do-not-save)
  (internal-status-code ;optimizes last-status-message-for-file for open files
    nil vector-slot system do-not-save)
  (internal-stream-representation 
    nil vector-slot system do-not-save)
  (internal-input-stream-buffer?
    nil vector-slot system do-not-save)
  (internal-input-stream-buffer-position
    0 vector-slot system do-not-save)
  (internal-available-characters-in-input-buffer
    0 vector-slot system do-not-save)
  (internal-input-stream-file-position-offset
    0 vector-slot system do-not-save)
  (text-conversion-style    ; - defaults to the default-text-conversion-style of language-parameters
			    ; - changeable up until anything read/written -- not really enforced
			    ;     or taken advantage of until 6.0 -- (MHD 5/2/00)
			    ; - note: overloaded name -- use no-accessor, and must be lookup 
    nil			    ;   slot everywhere
    (type text-conversion-style-name?)
    no-accessor
    lookup-slot system do-not-save)
  
  (internal-stream-text-conversion-established-p ; nil or true; set up get-text-conversion-style-structure-
    nil vector-slot system do-not-save)	         ;   for-stream, after which the next 4 are set up.
  (internal-stream-external-character-set
    nil vector-slot system do-not-save)
  (internal-stream-n-octets-per-character
    nil vector-slot system do-not-save)
  (internal-stream-2-octet-byte-swapped-p
    nil vector-slot system do-not-save)
  (internal-stream-preimported-text-lines-p
    nil vector-slot system do-not-save))

;; Made the attribute type slots be vector slots; there had been a restriction
;; on having attribute slots be vector slots, but that went away in 4.0. (MHD
;; 5/5/00)


	    

(def-slot-value-writer name-of-file (namestring)
  (let ((namestring-as-text
	  (import-text-string		; Previously: convert-ascii-filename-to-text-string-as-much-as-possible
	    namestring			; Q: Why did this store a non-text-string in a slot, and
	    'G2-DIRECTORY-PATHNAME)))	;   then have to keep "importing" it to present to users?! (MHD 5/20/96)
    (twrite-string namestring-as-text)
    (reclaim-text-string namestring-as-text)))


;;; The macro `g2-stream-readable-p' takes a g2-stream-frame and returns
;;; whether or not that stream has been opened such that it can be read from.

(def-substitution-macro g2-stream-readable-p (g2-stream-frame)
  (or (eq (access-direction g2-stream-frame) 'input)
      (eq (access-direction g2-stream-frame) 'input-and-output)))




;;; The function `g2-stream-frame-get-file-position' returns the computed
;;; current file position of a g2-stream frame opened for input or for input
;;; and output.

(defun-substitution-macro g2-stream-frame-get-file-position (g2-stream-frame)
  (+f (internal-input-stream-file-position-offset g2-stream-frame)
      (internal-input-stream-buffer-position g2-stream-frame)))

(defconstant size-of-g2-stream-frame-input-buffer 512)

;; increased size from 128 to 512. (MHD 5/4/00)


(def-class-method cleanup (g2-stream)
  (funcall-superior-method g2-stream)
  (let ((internal-g2-stream? (internal-stream-representation g2-stream)))
    (when internal-g2-stream?
      (g2-stream-close internal-g2-stream?)
      (setf (internal-stream-representation g2-stream) nil))
    (let ((buffer? (internal-input-stream-buffer? g2-stream)))
      (when buffer?
	(reclaim-text-string buffer?))
      (setf (internal-input-stream-buffer? g2-stream) nil))))

;; May need a method for deactivation too!


;;; `Defun-for-file-io' is used to define the file-io family of system
;;; procedures.  This is much like defun-for-system-procedure, but the
;;; resulting function is allowed to unwind.

(defmacro defun-for-file-io (name arglist &body body)
  `(defun-allowing-unwind-for-system-procedure ,name ,arglist ,@body))


;;; `Set-up-g2-stream-update-slots' and its call immediately below result in the
;;; creation of def-system-variable forms for variables in
;;; `g2-stream-update-slots' (a defvar-for-macro).  Each such variable holds the
;;; slot description of the corresponding slot.  The slots are the following:
;;;
;;;    g2-stream-status, name-of-file, access-direction,
;;;    position-in-file, file-system
;;;
;;; Each variable name is of the form <slot-name>-slot-description.  This allows
;;; the slightly faster change-slot-description-value function to be applied,
;;; i.e., by update-g2-stream-slots, as opposed to change-slot-value.

(defvar-for-macro g2-stream-update-slots
  '(g2-stream-status name-of-file access-direction
    position-in-file file-system))

(defmacro set-up-g2-stream-update-slots ()
  `(progn
     . ,(loop for slot-name in g2-stream-update-slots
	      collect `(def-system-variable ,(build-ab-symbol slot-name 'slot-description) file-sysproc
			 (:funcall get-slot-description-from-class g2-stream ,slot-name)))))

(set-up-g2-stream-update-slots)





;;; `Update-g2-stream-slots' ....

(defmacro update-g2-stream-slots 
	  (g2-stream internal-stream?
	   &key 
	   (status nil status-supplied-p)
	   (filename nil filename-supplied-p)
	   (direction nil direction-supplied-p)
	   (position nil position-supplied-p)
	   (stream nil stream-supplied-p)
	   (filesystem nil filesystem-supplied-p))
  (avoiding-variable-capture
      (g2-stream internal-stream? status filename direction position stream filesystem)
    `(progn 
       ,@(if status-supplied-p
	     `((progn
		 ;; For the g2-stream-status slot, which is called the most
		 ;; often, but which rarely changes, we explicitly check, and
		 ;; don't bother doing the change if there's no change in
		 ;; status, just as an optimization.  (MHD 5/5/00)
		 (unless (eq ,status (g2-stream-status ,g2-stream)) ; opt.
		   (change-slot-description-value
		     ,g2-stream g2-stream-status-slot-description ,status))
		 (when ,internal-stream?
		   (setf (internal-status-code ,g2-stream) (g2-stream-get-error-flag))))))
       ,@(if filename-supplied-p
	     `((change-slot-description-value
		 ,g2-stream name-of-file-slot-description ,filename)))
       ,@(if direction-supplied-p
	     `((change-slot-description-value
		 ,g2-stream access-direction-slot-description ,direction)))
       ,@(if position-supplied-p
	     `((change-slot-description-value
		 ,g2-stream position-in-file-slot-description ,position)))
       ,@(if stream-supplied-p
	     `((setf (internal-stream-representation ,g2-stream) ,stream)))
       ,@(if filesystem-supplied-p
	     `((change-slot-description-value
		 ,g2-stream file-system-slot-description ,filesystem))))))

;; Changed today as follows: (1) slots internal-stream-representation and
;; internal-status-code (with no table representation or attribute export
;; definition) are changed via SETF; (2) internal-stream? was made the second,
;; required argument, and all callers were visited to pass in the proper
;; argument; (3) change-slot-value's were changed to
;; change-slot-description-value as an optimization; (4) don't do
;; change-slot-value operation on the g2-stream-status slot if it's not
;; changing, which it usually isn't, since it's too expensive.  Change (2) was
;; easy: all callers were in this module, and had the value handy; previously,
;; it was gotten here from the slot.  Change (4) is possibly a minor problem for
;; T2, since it previously would have updated a subscription for every such
;; nonchange to a T2 client, but users can live with this limitation, I'm sure;
;; note whenever rules would not have been invoked for non-changing cases ever.
;; (MHD 5/2/00)




;; General Thoughts On Documentation

;; Have to explain defaulting better.  This is going to be an especial problem
;; when we have to tell users that the defaults used for kb-saving are not picked
;; up by the file i/o system procedures.

;; More generally, we might want to consider a system table for file i/o, which
;; makes the defaulting more explicit, assuming its complexity doesn't cause more
;; problems than it solves.  Candidates for slots in this table are default
;; save-kb path, default load-kb path, and number of filestrings for which to keep
;; messages.  (If this last is not bounded, users can blithely attempt faulty file
;; operations, with G2 merrily saving error messages in the background, until a
;; mysterious crash occurs.)

;; Users should also be told that the file modification and attribute-change times
;; may change mysteriously if another process has an open stream to the given
;; file.

;; In all of what follows, a "filestring" is a text-string which is supposed to
;; name a file.

;; We should emphasize that parsing a filestring can be done even if the file
;; involved does not exist.

;; We should document to the user that a failed attempt to open does not leave a
;; g2-stream item around.  The system procedure deletes the g2-stream instance and
;; then signals an error.  We should also document that closing a g2-stream is the
;; same as deleting it.

;; We should probably think more about where we provide default file components.
;; Some might argue that it is more intuitive for the user to have the various
;; file-xxx-string destructurers to provide defaults even when there were none in
;; the original namestring.  On the other hand, the user can get defaults from the
;; default-directory system procedure and work with those directly, instead of
;; trusting the namestring-parsers to do the right thing.

;; A special case of the above is deciding what to do about UNIX devices.  UNIX
;; device mount points are not used when G2 parses UNIX namestrings.  UNIX-based
;; users will no doubt find it confusing that the system procedure
;; file-device-string returns an empty string when there is obviously a device on
;; which the file resides.  The main reason is that the file-xxx-string utilities
;; only process strings, and do not access the disk to do their work.  In UNIX,
;; there is no syntactic difference between the "device" part of the path and the
;; "directory" part -- they are each a bunch of tokens separated by slashes.
;; Another reason is that the name of the device is not needed in any G2 file
;; operation.  The only occasion where it might come up is in getting the amount
;; of available disk space, and all that is needed there is the name of the
;; directory (see the system procedure disk-space-available-in-directory).  Maybe
;; we should change the name of the slot, but we can't dispense with it
;; altogether, since it's used in parsing VMS namestrings.

;; Error reporting is done through the errno-like mechanism in STREAMS.  Most
;; system procedures return a second value, an error string.  This string is as
;; detailed as the underlying file system gets about the cause of the error.  In
;; the interest of efficiency, however, the system procedures read-byte,
;; read-line, and write-byte do not return multiple values, but instead affect the
;; g2-stream object directly.  If there is an outcry about the lack of a specific
;; error message for these system procedures, something can be arranged.



;;;; Text Conversion Style

(def-class (text-conversion-style (item entity))
  (frame-author-or-authors nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))
  (external-character-set
    gensym (type character-set))
  (unconvertible-character-spec		; nil or a character code or a text (string)
    nil (type unconvertible-character-spec))
  (external-line-separator
    per-platform (type line-separator))
  (han-unification-mode
    japanese (type han-unification-mode))
  (internal-structure-for-text-conversion-style	; internal structure
    nil ; initialized upon creation, clone, and recreation (reading)
    do-not-save not-user-editable))

(def-slot-value-reclaimer internal-structure-for-text-conversion-style (text-conversion-style)
  (reclaim-transcode-text-conversion-style text-conversion-style))

(define-slot-alias replacement-character unconvertible-character-spec
  text-conversion-style)


(def-class-method initialize-after-reading (text-conversion-style)
  (funcall-superior-method text-conversion-style)
  (update-internal-structure-for-text-conversion-style
    text-conversion-style))

(def-class-method initialize (text-conversion-style)
  (funcall-superior-method text-conversion-style)
  (update-internal-structure-for-text-conversion-style
    text-conversion-style))






(define-category-evaluator-interface (text-conversion-style-name?
				       :access read-write)
    (or (no-item) symbol)
  ((set-form (evaluation-value))
   (if evaluation-value
       evaluation-value
       'none))
  ((get-form (slot-value))
   slot-value))

(def-grammar-category text-conversion-style-name? ()
  ('none)
  (text-conversion-style-name))

(def-grammar-category text-conversion-style-name ()
  (unreserved-symbol))

(def-registered-directory-of-names text-conversion-style-name)

(def-slot-putter text-conversion-style
    (language-parameters text-conversion-style-name?)
  (without-consistency-analysis (language-parameters)
    (setf (text-conversion-style language-parameters) text-conversion-style-name?))
  text-conversion-style-name?)


(def-slot-value-compiler text-conversion-style-name? (parse-result)
  (if (eq parse-result 'none) nil parse-result))

(def-slot-value-writer text-conversion-style-name? (style-name?)
  (cond
    (style-name?
     (write-name-for-frame style-name?))
    (t (twrite-string "none"))))





(defun-simple get-text-conversion-style-structure-per-name (style-name)
  (let ((named-style-frame?
	  (get-instance-with-name-if-any
	    'text-conversion-style
	    style-name)))
    (if named-style-frame?
	(internal-structure-for-text-conversion-style
	  named-style-frame?))))


(defmacro get-text-conversion-style-structure-for-stream
    (g2-stream &optional utf-g-ascii-as-much-as-possible-option?)
  `(come-up-with-text-conversion-style-structure
     (text-conversion-style ,g2-stream)
     ,utf-g-ascii-as-much-as-possible-option?))


;;; `Come-up-with-text-conversion-style-structure' is to be used to create get
;;; or create a text conversion style structure for use at runtime... Normally,
;;; if there is no explicit conversion style, then the default is to use UTF-G.
;;; If export-ascii-as-much-as-possible-option?, then, if there is no explicit
;;; conversion style specified in the stream, the default is to use the "ascii
;;; as much as possible" style, which converts ascii to ascii, and anything else
;;; to the Gensym encoding.  Note that this option should ONLY be used for
;;; output, never for input.

(defun-simple come-up-with-text-conversion-style-structure
    (name? utf-g-ascii-as-much-as-possible-option?)
  (or (if name?
	  (get-text-conversion-style-structure-per-name name?))
      (if (text-conversion-style language-parameters)
	  (get-text-conversion-style-structure-per-name
	    (text-conversion-style language-parameters)))
      (if utf-g-ascii-as-much-as-possible-option?
	  utf-g-ascii-as-much-as-possible-conversion-style)
      default-text-conversion-style))



(defun create-internal-structure-for-text-conversion-style ()
  (make-transcode-text-conversion-style))

(defun update-internal-structure-for-text-conversion-style
    (text-conversion-style)
  (let* ((f text-conversion-style)	; F(rame) & S(tructure)
	 (s (internal-structure-for-text-conversion-style
	      text-conversion-style)))
    (when (null (internal-structure-for-text-conversion-style f))
      (setf s
	    (setf (internal-structure-for-text-conversion-style f)
		  (make-transcode-text-conversion-style))))
    (setf (transcode-external-character-set s)
	  (external-character-set f))
    (setf (transcode-unconvertible-character-spec s)
	  (if (unconvertible-character-spec f)
	      (code-wide-character
		(unconvertible-character-spec f))))
    (setf (transcode-unicode-line-separator-export-translation s)
	  (external-line-separator f))
    (setf (transcode-han-unification-mode s)
	  (han-unification-mode f))))





(def-slot-putter external-character-set (text-conversion-style value)
  (prog1 (setf (external-character-set text-conversion-style) value)
    (update-internal-structure-for-text-conversion-style
      text-conversion-style)))

(def-slot-putter unconvertible-character-spec (text-conversion-style value)
  (prog1 (setf (unconvertible-character-spec text-conversion-style) value)
    (update-internal-structure-for-text-conversion-style
      text-conversion-style)))

(def-slot-putter external-line-separator (text-conversion-style value)
  (prog1 (setf (external-line-separator text-conversion-style) value)
    (update-internal-structure-for-text-conversion-style
      text-conversion-style)))

(def-slot-putter han-unification-mode (text-conversion-style value)
  (prog1 (setf (han-unification-mode text-conversion-style) value)
    (update-internal-structure-for-text-conversion-style
      text-conversion-style)))




(def-grammar-category unconvertible-character-spec ()
    (integer?)				; a character code
    (whole-string))

;;; Store a wide character code or nil.

(def-slot-value-compiler unconvertible-character-spec (parse-result)
  (cond
    ((text-string-p parse-result)
     (if (not (=f (lengthw parse-result) 1))
	 (values
	   bad-phrase
	   (tformat-text-string
	     "Text must contain a single character"))
	 (wide-character-code (charw parse-result 0))))
    ((fixnump parse-result)
     (if (not (<=f 0 parse-result 65535))
	 (values
	   bad-phrase
	   (tformat-text-string
	     "Character code must be an integer between 0 and 65535"))
	 parse-result))
    ((eq parse-result 'none)
     nil)
    (t #+development
       (warn "Unknown parse result for unconvertible-character-spec: ~a" parse-result))))
     
(def-slot-value-writer unconvertible-character-spec (slot-value)
  (cond
    ((null slot-value)
     (tformat "none"))			; add comment {drop unconvertible characters}?
    (t
     (let ((temp-string (tformat-text-string "~c" slot-value)))
       (twrite-parsably temp-string)
       (reclaim-text-string temp-string)))))




(def-grammar-category line-separator ()
  per-platform
  CR
  LF
  CRLF
  unicode-line-separator
  unicode-paragraph-separator )


(def-slot-value-writer line-separator (slot-value)
  (case slot-value
    ((cr lf crlf)
     (twrite-symbol slot-value t))
    (t 
     (twrite-symbol slot-value))))   ; downcased



(def-grammar-category han-unification-mode ()
  japanese
  korean
  chinese-simplified
  chinese-traditional)

(def-grammar-category character-set ()
  
  ;; 7-bit, single byte character sets:

  US-ASCII


  ;; 8-bit, single byte character sets:
					; -- Parts 1-10 of ISO 8859
  latin-1				; iso-8859-1
  latin-2				; iso-8859-2
  latin-3				; iso-8859-3
  latin-4				; iso-8859-4
  latin-cyrillic			; iso-8859-5
  latin-arabic				; iso-8859-6
  latin-greek				; iso-8859-7
  latin-hebrew				; iso-8859-8
  latin-5				; iso-8859-9
  latin-6				; iso-8859-10 

  ;; 7- and 8-bit, double byte character sets:

  JIS					; -- 7-bit, ISO 2022 encoded JIS X 0208 (Japanese)
  JIS-EUC				; -- 8-bit, escapeless ISO 2022 encoded JIS X 0208
  Shift-JIS				; -- Shift-jis encoded JIS X 0208, aka MS Kanji

  KSC					; -- 7-bit, ISO 2022 encoded KS C 5601 (Korean)
  KSC-EUC				; -- 8-bit, escapeless ISO 2022 encoded KS C 5601

  GB-2312				; -- 7-bit, ISO 2022 encoded GB 2312 (Chinese - PRC)
  GB-2312-EUC				; -- 8-bit, escapeless ISO 2022 encoded GB 2312

  

		
  ;; Unicode:

  Unicode				; -- 16-bit stream; Unicode in UCS-2 format ("Pure Unicode", MSB|LSB)
  Unicode-byte-swapped			; -- 16-bit stream; same as above, but LSB|MSB
  Unicode-ucs-2				; -- 8-bit stream; disfunctional/broken for read-line
  Unicode-ucs-2-byte-swapped
  Unicode-UTF-7
  Unicode-UTF-8


  ;; Special Multibyte:

  Gensym				; -- UTF-G
  X-Compound-Text			; -- X compound text with subset of 2022 escapes
  )


(def-global-property-name preferred-spelling-for-character-set)

(setf (preferred-spelling-for-character-set 'gensym)
      #w"Gensym")

(setf (preferred-spelling-for-character-set 'unicode-byte-swapped)
      #w"Unicode-byte-swapped")

(setf (preferred-spelling-for-character-set 'unicode-utf-7)
      #w"Unicode-UTF-7")

(setf (preferred-spelling-for-character-set 'unicode-utf-8)
      #w"Unicode-UTF-8")

(setf (preferred-spelling-for-character-set 'x-compound-text)
      #w"X-Compound-Text")

(setf (preferred-spelling-for-character-set 'latin-1)
      #w"Latin-1")

(setf (preferred-spelling-for-character-set 'latin-2)
      #w"Latin-2")

(setf (preferred-spelling-for-character-set 'latin-3)
      #w"Latin-3")

(setf (preferred-spelling-for-character-set 'latin-4)
      #w"Latin-4")

(setf (preferred-spelling-for-character-set 'latin-greek)
      #w"Latin-Greek")

(setf (preferred-spelling-for-character-set 'latin-arabic)
      #w"Latin-Arabic")

(setf (preferred-spelling-for-character-set 'latin-greek)
      #w"Latin-Greek")

(setf (preferred-spelling-for-character-set 'latin-hebrew)
      #w"Latin-hebrew")

(setf (preferred-spelling-for-character-set 'latin-5)
      #w"Latin-5")

(setf (preferred-spelling-for-character-set 'latin-6)
      #w"Latin-6")



(def-slot-value-writer character-set (slot-value)
  (cond
    ((null slot-value)
     (tformat "unknown"))		; ?? allow this?
    (t
     (tformat
       "~a"
       (or (preferred-spelling-for-character-set slot-value)
	   slot-value)))))		; symbol that gets upcased

(def-slot-value-writer han-unification-mode (slot-value)
  (cond
    ((null slot-value)
     (tformat "unknown"))		; ?? allow this?
    (t
     (twrite-symbol-into-text-string
       slot-value			; Japanese, Chinese, etc.
       :first-of-each-word))))





;;; `Init-text-conversion-style-for-stream' gets the internal text conversion
;;; style, setting up the slot and associated text-conversion-style-related
;;; slots the first time it's used on a stream if necessary.  Note that this
;;; should be called before directly accessing the following slots:
;;;
;;; Note that it's an error for a text conversion style to be changed by the
;;; user on a closed stream, or on an open stream after I/O operations (reading,
;;; writing, or setting file position) have been done the first time.  This
;;; means that the right time to change the text conversion style is just after
;;; opening a file and just before commencing with I/O operations.

;;; `Get-conversion-charset-and-init-if-necessary' is similar, but instead
;;; returns the charset (e.g., GENSYM, US-ASCII, LATIN-1) symbol, which is
;;; usually a more useful value.

(defmacro init-text-conversion-style-for-stream
    (g2-stream &optional utf-g-ascii-as-much-as-possible-option?)
  (avoiding-variable-capture (g2-stream utf-g-ascii-as-much-as-possible-option? &aux style)
    `(unless (internal-stream-text-conversion-established-p ,g2-stream)
       (let ((,style
		(come-up-with-text-conversion-style-structure
		  (text-conversion-style ,g2-stream)
		  ,utf-g-ascii-as-much-as-possible-option?)))
	 (setf (internal-stream-text-conversion-established-p ,g2-stream) t)
	 (setf (internal-stream-external-character-set ,g2-stream)
	       (transcode-external-character-set ,style))
	 (setf (internal-stream-n-octets-per-character ,g2-stream)
	       (n-octets-per-character ,style))
	 (setf (internal-stream-2-octet-byte-swapped-p ,g2-stream)
	       (2-octet-byte-swapped-p ,style))
	 (setf (internal-stream-preimported-text-lines-p ,g2-stream)
	       (preimported-text-lines-p ,style))
	 ,style))))

(defun-substitution-macro get-conversion-charset-and-init-if-necessary (g2-stream)
  (init-text-conversion-style-for-stream g2-stream)
  (internal-stream-external-character-set g2-stream))

;; Doesn't support &optional utf-g-ascii-as-much-as-possible-option? now.  This
;; may make it unsuitable for output! (MHD 5/4/00)
	   








;;;; File Access Procedures


;;; OPEN-FILE-FOR-READ system procedure

;;; Takes as argument a filestring and always returns a g2-stream frame, even if
;;; the attempt failed.  Returns the error string to G2 as a second value.  G2
;;; will signal the user if an error occurred.

;; Probably need a corresponding open-file-for-exclusive-read system procedure
;; which locks the file against any other process wanting to use it.  See F_SETLK
;; in the man entry for fcntl for a lead on how to do this.

(defun-simple get-filesystem-from-g2-stream-for-user (g2-stream)
  (let* ((pathname (g2-stream-find-active-pathname g2-stream))
	 (internal-file-system-name
	  (gensym-pathname-file-system pathname)))
    (case internal-file-system-name
      (generalized-dos   (case g2-operating-system
			   (dos         'dos)
			   (win32       'win32)))
      (otherwise internal-file-system-name))))


;; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
(defun export-filename-from-g2-string (g2-filestring)
  (export-text-string
   (evaluation-text-value g2-filestring)
   (if (use-unicode-for-filenames)
     'G2-DIRECTORY-PATHNAME-W
     'G2-DIRECTORY-PATHNAME)))

(defun-for-file-io open-file-for-read-lisp-side (g2-filestring)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((filestring (export-filename-from-g2-string g2-filestring))
	 (g2-stream-frame (make-transient-item 'g2-stream))
	 (internal-stream?
	  (case local-file-system
	    ((win32 dos)
	     (g2-stream-open-for-random-access-binary-input filestring))
	    (otherwise (g2-stream-open-for-input filestring)))))
    (cond
      (internal-stream?
       (update-g2-stream-slots g2-stream-frame internal-stream?
	 :filename   g2-filestring
	 :direction  'input
	 :status     'open-for-read
	 :position   (g2-stream-get-file-position internal-stream?)
	 :stream     internal-stream?
	 :filesystem (get-filesystem-from-g2-stream-for-user internal-stream?))
       (setf (internal-input-stream-buffer? g2-stream-frame)
	     (obtain-simple-text-string size-of-g2-stream-frame-input-buffer)))
      (t (update-g2-stream-slots g2-stream-frame internal-stream?
	   :filename  g2-filestring
	   :direction 'closed
	   :status    'failed-to-open-for-read)))
    (reclaim-text-string filestring)
    (values g2-stream-frame
	    (if internal-stream?
		(make-evaluation-text "")
		(most-recent-file-operation-status-as-text)))))



;;; OPEN-FILE-FOR-WRITE system procedure

;;; Takes as argument a filestring and always returns a g2-stream frame, even if
;;; the attempt failed.  Returns the error string to G2 as a second value.  G2
;;; will signal the user if an error occurred.

;; Probably need a corresponding open-file-for-exclusive-write system procedure
;; which locks the file against any other process wanting to use it.  See F_SETLK
;; in the man entry for fcntl for a lead on how to do this.


(defun-for-file-io open-file-for-write-lisp-side (g2-filestring)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((filestring (export-filename-from-g2-string g2-filestring))
	 (g2-stream-frame
	  (make-transient-item 'g2-stream))
	 (internal-stream?
	  (case local-file-system
	    ((win32 dos)
	     (g2-stream-open-for-binary-output filestring))
	    (otherwise (g2-stream-open-for-output filestring)))))
    (cond
      (internal-stream?
       (update-g2-stream-slots g2-stream-frame internal-stream?
	 :filename  g2-filestring
	 :direction 'output
	 :status    'open-for-write
	 :position  (g2-stream-get-file-position internal-stream?)
	 :stream    internal-stream?
	 :filesystem (get-filesystem-from-g2-stream-for-user internal-stream?)))
      (t (update-g2-stream-slots g2-stream-frame internal-stream?
	   :filename  g2-filestring
	   :direction 'closed
	   :status    'failed-to-open-for-write)))
    (reclaim-text-string filestring)
    (values g2-stream-frame
	    (if internal-stream?
		(make-evaluation-text "")
		(most-recent-file-operation-status-as-text)))))





;;; OPEN-FILE-FOR-APPEND system procedure

;;; Takes as argument a filestring and always returns a g2-stream frame, even if
;;; the attempt failed.  Returns the error string to G2 as a second value.  G2
;;; will signal the user if an error occurred.

;; Probably need a corresponding open-file-for-exclusive-append system procedure
;; which locks the file against any other process wanting to use it.  See F_SETLK
;; in the man entry for fcntl for a lead on how to do this.


(defun-for-file-io open-file-for-append-lisp-side (g2-filestring create-it)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((filestring (export-filename-from-g2-string g2-filestring))
	 (g2-stream-frame (make-transient-item 'g2-stream))
	 (create-if-does-not-exist-p
	  (prog1 (>=f (evaluation-truth-value-value create-it)
		      (truth-threshold inference-engine-parameters))
	    (reclaim-evaluation-truth-value create-it)))
	 (internal-stream?
	   (case local-file-system
	     ((win32 dos)
	      (g2-stream-open-for-binary-appending
		filestring
		create-if-does-not-exist-p))
	     (otherwise (g2-stream-open-for-appending 
			  filestring
			  create-if-does-not-exist-p)))))
    (cond
      (internal-stream?
       (update-g2-stream-slots g2-stream-frame internal-stream?
	 :filename  g2-filestring
	 :direction 'output
	 :status    'open-for-append
	 :position  (g2-stream-get-file-position internal-stream?)
	 :stream    internal-stream?
	 :filesystem (get-filesystem-from-g2-stream-for-user internal-stream?)))
      (t (update-g2-stream-slots g2-stream-frame internal-stream?
	   :filename  g2-filestring
	   :direction 'closed
	   :status    'failed-to-open-for-append)))
    (reclaim-text-string filestring)
    (values g2-stream-frame
	    (if internal-stream?
		(make-evaluation-text "")
		(most-recent-file-operation-status-as-text)))))





;;; OPEN-FILE-FOR-READ-AND-WRITE system procedure

;;; Takes as argument a filestring and always returns a g2-stream frame, even if
;;; the attempt failed.  Returns the error string to G2 as a second value.  G2
;;; will signal the user if an error occurred.

;; Probably need a corresponding open-file-for-exclusive-read-and-write system
;; procedure which locks the file against any other process wanting to use it.
;; See F_SETLK in the man entry for fcntl for a lead on how to do this.

;; Lisp machines don't support this!  

(defun-for-file-io open-file-for-read-and-write-lisp-side (g2-filestring)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((filestring (export-filename-from-g2-string g2-filestring))
	 (g2-stream-frame (make-transient-item 'g2-stream))
	 (internal-stream?
	  (case local-file-system
	    ((win32 dos)
	     (g2-stream-open-for-random-access-binary-io filestring))
	    (otherwise (g2-stream-open-for-random-access-io filestring)))))
    (cond
      (internal-stream?
       (update-g2-stream-slots g2-stream-frame internal-stream?
	 :filename   g2-filestring
	 :direction  'input-and-output
	 :status     'open-for-read-and-write
	 :position   (g2-stream-get-file-position internal-stream?)
	 :stream     internal-stream?
	 :filesystem (get-filesystem-from-g2-stream-for-user internal-stream?))
       (setf (internal-input-stream-buffer? g2-stream-frame)
	     (obtain-simple-text-string size-of-g2-stream-frame-input-buffer)))
      (t (update-g2-stream-slots g2-stream-frame internal-stream?
	   :filename  g2-filestring
	   :direction 'closed
	   :status    'failed-to-open-for-read-and-write)))
    (reclaim-text-string filestring)
    (values g2-stream-frame
	    (if internal-stream?
		(make-evaluation-text "")
		(most-recent-file-operation-status-as-text)))))







;;; CLOSE-FILE system procedure

;;; The system procedure close-file takes as argument a g2-stream and returns true
;;; if the close was successful, nil otherwise.

(defmacro g2-stream-frame-open-p (g2-stream-frame)
  `(internal-stream-representation ,g2-stream-frame))


;; Delete-frame will close the internal stream if it is open, acting through the
;; cleanup method of g2-stream-frame.

(defun close-file-lisp-side-unwrapped (g2-stream-frame)
  (delete-frame g2-stream-frame)
  t)



(defun-for-file-io close-file-lisp-side (g2-stream-frame)
  (declare (keeps-g2-local-variables-valid nil)) ; NIL because the frame is
					       ; deleted.  - cpm, 5/29/95
  (let ((status (close-file-lisp-side-unwrapped g2-stream-frame)))
    (cond (status
	   (values (copy-evaluation-truth-value evaluation-true-value)
		   (make-evaluation-text "")))
	  (t (values (copy-evaluation-truth-value evaluation-false-value)
		     (most-recent-file-operation-status-as-text))))))


;; We might need close-file-leaving-stream someday, if we decide to educate users
;; about the difference between a closed stream and a deleted one.

(defun close-file-leaving-stream-lisp-side-unwrapped (g2-stream-frame)
  (let ((internal-g2-stream?
	  (internal-stream-representation g2-stream-frame)))
    (cond (internal-g2-stream?
	   (cond ((g2-stream-close internal-g2-stream?)
		  (update-g2-stream-slots g2-stream-frame internal-g2-stream?
		    :status     'successfully-closed
		    :filesystem nil
		    :direction  'closed
		    :position   nil
		    :stream     nil)
		  t)
		 (t (update-g2-stream-slots g2-stream-frame internal-g2-stream?
		      :status     'failed-to-close
		      :filesystem nil
		      :direction  nil
		      :position   nil
		      :stream     nil)
		    nil)))
	(t (update-g2-stream-slots g2-stream-frame internal-g2-stream?
	     :status 'tried-to-close-when-already-closed)
	   nil))))

(defun-for-file-io close-file-leaving-stream-lisp-side (g2-stream-frame)
  (let ((status (close-file-lisp-side-unwrapped g2-stream-frame)))
    (if status
	(copy-evaluation-truth-value evaluation-true-value)
	(copy-evaluation-truth-value evaluation-false-value))))





;;; CLOSE-ALL-OPEN-G2-STREAMS system procedure

;;; Takes no argument and returns true if every open stream was closed (even if
;;; there were no open streams), false otherwise.

(defun-for-file-io close-all-open-g2-streams-lisp-side ()
  (declare (keeps-g2-local-variables-valid nil)) ; Check if always valid.  Being
					       ; careful, for now. - cpm,5/29/95
  (loop for g2-stream-frame being each class-instance of 'g2-stream
	with cumulative-result = t
	when (g2-stream-frame-open-p g2-stream-frame)
	  do
	  (let ((this-result
		  (close-file-lisp-side-unwrapped g2-stream-frame)))
	    (setq cumulative-result (and cumulative-result this-result)))
	finally
	(return (if cumulative-result
		    (copy-evaluation-truth-value evaluation-true-value)
		    (copy-evaluation-truth-value evaluation-false-value)))))

;; jh, 10/29/91.  Chestnut #defines a macro named "result", causing an obscure bug
;; in any loop which uses a variable of this name.  Changed this occurrence to
;; cumulative-result and AC will map the symbol result to something else in the
;; Chestnut translator.


;;; SET-FILE-POSITION system procedure

;;; Takes as argument a g2-stream and an integer returns true if the absolute file
;;; position was changed to that integer, false otherwise.

;; SET-RELATIVE-FILE-POSITION is not used, because its behavior is
;; counter-intuitive on some systems (for example, it occasionally refuses to
;; extend past the end-of-file).

;; Lisp machines don't support this!

(defun-for-file-io set-file-position-lisp-side 
		   (g2-stream-frame g2-new-position extend-file-if-necessary)
  (declare (keeps-g2-local-variables-valid t))
  (let ((internal-g2-stream?
	  (internal-stream-representation g2-stream-frame))
	(extend-file-if-necessary-p
	  (prog1 (evaluation-truth-value-is-true-p extend-file-if-necessary)
		 (reclaim-evaluation-truth-value extend-file-if-necessary))))
      (cond 
	(internal-g2-stream?
	 (let ((new-position
		 (prog1 (evaluation-integer-value g2-new-position)
			(reclaim-evaluation-integer g2-new-position)))
	       (position-at-eof?
		 (g2-stream-file-length internal-g2-stream?))
	       (successful-p nil))
	   (when position-at-eof?
	     (cond 
	       ((and (>f new-position position-at-eof?)
		     extend-file-if-necessary-p)
		(setq successful-p
		      ;; jra & jh, 5/7/93.  Note that we could fail midway
		      ;; through the following AND form, or even midway through
		      ;; the LOOP that is its second clause.  This could make
		      ;; the position as read from the g2-stream frame
		      ;; inconsistant with the position in the actual file.
		      ;; (Also note that this problem would happen whether or
		      ;; not we buffer the input stream).
		      (and (g2-stream-set-file-position 
			     internal-g2-stream?
			     position-at-eof?
			     (g2-stream-seek-from-beginning))
			   (loop for index 
				     from 0 
				     below (-f new-position position-at-eof?)
				 always 
				   (g2-stream-write-char 
				     #\Space
				     internal-g2-stream?)))))
	       ((>f new-position position-at-eof?)
		(return-from set-file-position-lisp-side
		  (values (copy-evaluation-truth-value evaluation-false-value)
			  (make-evaluation-text 
			    "Tried to set file position past end-of-file"))))
	       (t (setq successful-p
			(g2-stream-set-file-position 
			  internal-g2-stream?
			  new-position
			  (g2-stream-seek-from-beginning))))))
	   (cond
	    (successful-p
	     (setf (internal-input-stream-file-position-offset g2-stream-frame)
		   new-position)
	     (setf (internal-input-stream-buffer-position g2-stream-frame) 0)
	     (setf (internal-available-characters-in-input-buffer g2-stream-frame) 0)
	     (update-g2-stream-slots g2-stream-frame internal-g2-stream?
	       :status   'successfully-updated-position
	       :position new-position)
	     (values (make-evaluation-truth-value truth)
		     (make-evaluation-text "")))
	    (t (update-g2-stream-slots g2-stream-frame internal-g2-stream?
		 :status 'failed-to-update-position)
	       (values 
		 (make-evaluation-truth-value falsity)
		 (most-recent-file-operation-status-as-text))))))
	(t (update-g2-stream-slots g2-stream-frame internal-g2-stream?
	     :status 'tried-to-update-position-when-closed)
	   (values (make-evaluation-truth-value falsity)
		   (make-evaluation-text 
		     "Cannot update position of closed stream"))))))


;;; RENAME-FILE system procedure

;;; Takes as argument two filestrings and returns true if the file named by the
;;; first was successfully renamed to the second, false otherwise.

(defun-for-file-io rename-file-lisp-side 
		   (g2-old-filestring g2-new-filestring)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((old-filestring (export-filename-from-g2-string g2-old-filestring))
	 (new-filestring (export-filename-from-g2-string g2-new-filestring))
	 (successful-p (g2-stream-rename-file old-filestring new-filestring)))
    (reclaim-evaluation-text g2-old-filestring)
    (reclaim-evaluation-text g2-new-filestring)
    (reclaim-text-string old-filestring)
    (reclaim-text-string new-filestring)
    (if successful-p
	(values (copy-evaluation-truth-value evaluation-true-value)
		(make-evaluation-text ""))
	(values (copy-evaluation-truth-value evaluation-false-value)
		(most-recent-file-operation-status-as-text)))))


;;; COPY-FILE system procedure

;;; Takes as argument two filestrings and returns true if the file named by the
;;; first was successfully renamed to the second, false otherwise.

(defun-for-file-io copy-file-lisp-side 
		   (g2-old-filestring g2-new-filestring)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((old-filestring (export-filename-from-g2-string g2-old-filestring))
	 (new-filestring (export-filename-from-g2-string g2-new-filestring))
	 (successful-p
	   (g2-stream-copy-file old-filestring new-filestring)))
    (reclaim-evaluation-text g2-old-filestring)
    (reclaim-evaluation-text g2-new-filestring)
    (reclaim-text-string old-filestring)
    (reclaim-text-string new-filestring)
    (if successful-p
	(values (copy-evaluation-truth-value evaluation-true-value)
		(make-evaluation-text ""))
	(values (copy-evaluation-truth-value evaluation-false-value)
		(most-recent-file-operation-status-as-text)))))



;;; DELETE-FILE system procedure

;;; Takes as argument a filestring and returns true if the file was successfully
;;; deleted, false otherwise.

(defun-for-file-io delete-file-lisp-side (g2-filestring)
  ;; Check if always valid. Being careful, for now. - cpm, 5/29/95
  (declare (keeps-g2-local-variables-valid nil)) 
  (let* ((filestring (export-filename-from-g2-string g2-filestring))
	 (successful-p (g2-stream-delete-file filestring)))
    (reclaim-evaluation-text g2-filestring)
    (reclaim-text-string filestring)
    (if successful-p
	(values (copy-evaluation-truth-value evaluation-true-value)
		(make-evaluation-text ""))
	(values (copy-evaluation-truth-value evaluation-false-value)
		(most-recent-file-operation-status-as-text)))))


;;;; File Reading and Writing Procedures


;;; `G2-READ-LINE' is a system procedure defined in SYS-MOD.KB.

;;; The function `read-line-lisp-side' implements the Lisp side of this system
;;; procedure.

;;; It takes as argument a g2-stream and always returns two values: (1) a text
;;; evaluation value, and (2) the status slot of the g2-stream frame.  If an
;;; error or eof is encountered, an empty text evaluation value is returned and
;;; the status slot of the g2-stream frame is modified, and its value returned,
;;; accordingly.

;;; Note that the second value, status, was not returned as a value until 6.0,
;;; which meant that the user had to check the status slot after every read-line
;;; operation, which has higher overhead, and is often less convenient, than
;;; simply checking the value of a second return argument.

;;; Note that the text character set translation style is fixed the first time
;;; I/O is done on the stream, which may be via the call to this function.

;;; Note that, when G2 reads from a file, a `line' is delimited by a linefeed
;;; (LF), a return (CR), or a return-linefeed (CRLF) pair, or either of the
;;; Unicode line-separator or paragraph-separator characters when in 2-octet
;;; mode, i.e., the external character set either Unicode or
;;; Unicode-byte-swapped.  Even with the CRLF paired line terminators, the file
;;; position given by the sum of internal-input-stream-file-position-offset and
;;; internal-input-stream-buffer-position accurately reflects the true position,
;;; as the number of "bytes" (octets) in the actual file.


;;; The macros `read-char-idiom-for-g2-stream-frame-reading',
;;; `read-available-char-idiom-for-g2-stream-frame-reading', and
;;; `read-line-idiom-for-g2-stream-frame-reading' read characters out of local
;;; variables holding slots copied from a g2-stream frame, for use of the system
;;; procedure g2-read-line.
;;;
;;; These macros must be called in the context established by the macro
;;; `for-g2-stream-read-char-idiom'.  This macro establishes bindings for
;;; several local variables available for this macro to modify, and also
;;; performs some maintenance on the g2-stream structure.  It allows just one
;;; value to be returned from body.

(defmacro for-g2-stream-read-char-idiom
    ((g2-stream-frame input-stream-structure) &body body)
  (avoiding-variable-capture (g2-stream-frame input-stream-structure)
    `(let* ((g2-input-stream ,input-stream-structure)
	    (position (internal-input-stream-buffer-position ,g2-stream-frame))
	    (available-characters
	      (internal-available-characters-in-input-buffer ,g2-stream-frame))
	    (buffer (internal-input-stream-buffer? ,g2-stream-frame))
	    (offset
	      (internal-input-stream-file-position-offset ,g2-stream-frame))
	    (initial-file-position (+f offset position))
	    (string-length-exceeded-p nil)
	    (charset
	      (get-conversion-charset-and-init-if-necessary ,g2-stream-frame))
	    (n-octets-per-character
	      (internal-stream-n-octets-per-character ,g2-stream-frame))
	    (2-octet-byte-swapped-p
	      (internal-stream-2-octet-byte-swapped-p ,g2-stream-frame))
	    (preimported-p
	      (internal-stream-preimported-text-lines-p ,g2-stream-frame)))
       (declare (type fixnum
		      position available-characters offset initial-file-position))
       (prog1 (macrolet ((g2-stream-frame-get-file-position (x)
			   (declare (ignore x))
			   (error  "You can't use g2-stream-frame-get-file-position inside~%~
                                              for-g2-stream-read-char-idiom unless you are SURE you know~%~
                                              what you are doing.  If you think you do, tell dkuznick he~%~
                                              was wrong.")))
		. ,body)
	 (setf (internal-input-stream-buffer-position g2-stream-frame) position)
	 (setf (internal-available-characters-in-input-buffer g2-stream-frame) available-characters)
	 (setf (internal-input-stream-file-position-offset g2-stream-frame) offset)))))



(defmacro read-available-char-idiom-for-g2-stream-frame-reading ()
  `(let* ((char (charw buffer position))
	  (char-2 #u0000))
     (declare (type wide-character char char-2))
     (when (=f n-octets-per-character 2)
       (setq char-2 (charw buffer (+f position 1)))
       (setq char
	     (if 2-octet-byte-swapped-p
		 (wide-character-octets-to-wide-character char-2 char)
		 (wide-character-octets-to-wide-character char char-2))))
     (incff position n-octets-per-character)
     char))



(defmacro read-char-idiom-for-g2-stream-frame-reading ()
  `(if (or (<f position (-f available-characters (if (=f n-octets-per-character 2) 1 0)))
	   (let* ((count-of-characters-read?
		    (g2-stream-read-octets-into-wide-string-buffer
		      buffer
		      size-of-g2-stream-frame-input-buffer
		      g2-input-stream)))
	     (setq available-characters (or count-of-characters-read? 0))
	     (incff offset position)
	     (setq position 0)
	     (>f available-characters (if (=f n-octets-per-character 2) 1 0))))
       (read-available-char-idiom-for-g2-stream-frame-reading)))





;;; `Read-line-idiom-for-g2-stream-frame-reading' is called by
;;; read-line-lisp-side with for-g2-stream-read-char-idiom wrapped around it.
;;; Usage-case is evaluated at macroexpansion time.  It can be :any, to detect
;;; handle all possible cases at runtime, :wide-character for 16-bit characters,
;;; :utf-8 for the Gensym character set (our proprietary multibyte universal
;;; character set and Unicode transformation format), or :traditional for
;;; US-ASCII, Latin-1, and all the other single- or double-byte character sets.

(defmacro read-line-idiom-for-g2-stream-frame-reading (usage-case)
  `(loop with character?
	 ,@(if (memq usage-case '(:any :utf-g))
	       '(with utf-g-uninteresting-so-far-p = (or (eq charset 'utf-g) (eq charset 'gensym))))
	 do (setq character? (read-char-idiom-for-g2-stream-frame-reading))
	    (cond
	      ;; EOF, LF, ULS, UPS
	      ((or (null character?)
		   (char=w character? #.%Linefeed)
		   ,@(if (memq usage-case '(:any :wide-character))
			 '((char=w character? #.%line-separator)
			   (char=w character? #.%paragraph-separator))))
	       (loop-finish))
	      ;; CR, CRLF
	      ((char=w character? #.%Return)
	       (let ((peeked-character?
		       (read-char-idiom-for-g2-stream-frame-reading)))
		 (unless (and peeked-character?
			      (char=w peeked-character? #.%Linefeed))
		   (decff position n-octets-per-character))
		 (loop-finish)))
	      (t
	       (when (>=f fill-pointer-for-current-wide-string
			  maximum-length-for-user-text-strings)
		 (setq string-length-exceeded-p t)
		 (loop-finish))
	       ,@(if (memq usage-case '(:any :utf-g))
		     '((when (and utf-g-uninteresting-so-far-p
				  (or (char=w character? #.%\~)
				      (char=w character? #.%\@)
				      (char=w character? #.%\\)))
			 (setq utf-g-uninteresting-so-far-p nil))))
	       (twrite-wide-character-macro character?)))
	 finally
	   ,@(if (memq usage-case '(:any :utf-g))
		 `((when (and utf-g-uninteresting-so-far-p
			      (or (eq charset 'utf-g) (eq charset 'gensym)))
		    (setq preimported-p t))))))

;; Consider detecting if 8-bit characters are ever seen; if not, preimported
;; might also be able to be set in the _some_ subcases of the :traditional case.
;; (E.g., for Latin-2 or EUC-JIS, say, but not for 7-bit JIS!) (MHD 5/5/00)





(defun-for-file-io read-line-lisp-side (g2-stream-frame)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((internal-g2-stream? (internal-stream-representation g2-stream-frame))
	 (result-text-string? nil)
	 (status-symbol
	   (cond
	     ((not (g2-stream-readable-p g2-stream-frame))
	      'tried-read-line-on-stream-not-opened-for-read)
	     (internal-g2-stream?
	      (for-g2-stream-read-char-idiom
		(g2-stream-frame internal-g2-stream?)
		(twith-output-to-then-use-of-wide-string
		  (cond
		    ((=f n-octets-per-character 2)
		     (read-line-idiom-for-g2-stream-frame-reading :wide-character))
		    ((or (eq charset 'utf-g) (eq charset 'gensym))
		     (read-line-idiom-for-g2-stream-frame-reading :utf-g))
		    (t
		     (read-line-idiom-for-g2-stream-frame-reading :traditional)))
		  (cond
		    ((not (>f (+f offset position) initial-file-position))
		     (cond 
		       ((g2-stream-eof-p internal-g2-stream?)
			'end-of-file-reached)
		       (t 'error-during-read-line)))
		    (t
		     ;; Can't use g2-stream-frame-get-file-position to give as
		     ;; :position here because we're inside
		     ;; for-g2-stream-read-char-idiom and the internal slots of the
		     ;; g2-stream-frame have not been set correctly until we
		     ;; leave it.
		     (update-g2-stream-slots
		       g2-stream-frame g2-input-stream? :position (+f offset position))
		     (setq result-text-string?
			   (cond
			     (preimported-p
			      (copy-current-wide-string))
			     (t
			      (import-text-string-per-text-conversion-style
				current-wide-string
				(get-text-conversion-style-structure-for-stream g2-stream-frame)
				0 fill-pointer-for-current-wide-string))))
		     (if string-length-exceeded-p
			 'line-truncated-during-read
			 'successfully-read-line))))))
	     (t 'tried-read-line-when-closed))))
    (update-g2-stream-slots
      g2-stream-frame internal-g2-stream? :status status-symbol)
    (values
      (make-evaluation-text-reclaiming-argument
	(or result-text-string? (make-wide-string 0)))
      (make-evaluation-symbol status-symbol))))

;; Note that in 4.0, this translated as follows:
;;
;;  CRLF, LFCR, LF => <line end>
;;  CR => CR
;;
;; vs. now
;;
;;  CRLF, CR, LF => <line end>
;;
;; The new way is (more) standard.  The old way was not at all standard.  In
;; particular, it didn't interpret CR as line-end, which would fail to handle
;; Macintosh plain text files, for example, but it did handle LFCR as a single
;; line-end, which conforms to no standard at all. (MHD 8/9/96)



#+development
(defun create-test-files-for-buffered-input ()
  (flet ((create-with-terminators (n terminate-final-line-p &rest terminators)
	   (with-open-file (s (format nil "/home/jra/tmp/deletable~s.text" n) 
			      :direction :output
			      :element-type '(unsigned-byte 8))
	     (loop for i from 1 to 10
		   for line = (format nil "~s: hello there" i)
		   do
	       (loop for index from 0 below (length line) do
		 (write-byte (char-int (char line index)) s))
	       (unless (and (= i 10) (not terminate-final-line-p))
		 (loop for terminator in terminators
		       do
		   (write-byte (char-int terminator) s)))))))
    (create-with-terminators 1   t #\Linefeed)
    (create-with-terminators 2   t #\Return)
    (create-with-terminators 3   t #\Linefeed #\Return)
    (create-with-terminators 4   t #\Return #\Linefeed)
    (create-with-terminators 5 nil #\Linefeed)
    (create-with-terminators 6 nil #\Return)
    (create-with-terminators 7 nil #\Linefeed #\Return)
    (create-with-terminators 8 nil #\Return #\Linefeed)
    (create-with-terminators 9   t #\Linefeed #\Linefeed)
    (create-with-terminators 10  t #\Return #\Return)
    (create-with-terminators 11  t #\Linefeed #\Return #\Linefeed #\Return)
    (create-with-terminators 12  t #\Return #\Linefeed #\Return #\Linefeed)
    ))



;;; READ-BYTE system procedure

;;; Takes as argument a g2-stream and always returns an integer.  If an error or
;;; eof is encountered, -1 is returned and the status slot of the g2-stream frame
;;; is modified accordingly.  The status is also returned as a second value.

;; The function read-next-char-for-g2-stream-frame is another user of the hack
;; inlining of read-char-idiom-for-g2-stream-frame-reading, along with read line
;; and read bytes.

(defun-simple read-next-char-for-g2-stream-frame
    (g2-stream-frame g2-input-stream)
  (for-g2-stream-read-char-idiom (g2-stream-frame g2-input-stream)
    preimported-p charset string-length-exceeded-p initial-file-position ; unused
    (read-char-idiom-for-g2-stream-frame-reading)))

;;; The constant `byte-range-0-255-mask' is used to convert all bytes read from
;;; the operating system to the range 0-255 inclusive.  This includes bytes read
;;; from files (cf. read-byte-lisp-side) and those that result from partitioning
;;; IEEE floats (cf. float-to-bytes-lisp-side and bytes-to-float-lisp-side).

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defconstant byte-range-0-255-mask #.(1- (ash 1 8))))

(defun-for-file-io read-byte-lisp-side (g2-stream-frame)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((internal-g2-stream? (internal-stream-representation g2-stream-frame))
	 (byte-value? nil)
	 (status-symbol
	   (cond
	     ((not (g2-stream-readable-p g2-stream-frame))
	      'tried-read-byte-on-stream-not-opened-for-read)
	     (internal-g2-stream?
	      (let ((ascii-char?
		      (read-next-char-for-g2-stream-frame
			g2-stream-frame
			internal-g2-stream?)))
		(cond (ascii-char?
		       (update-g2-stream-slots
			 g2-stream-frame internal-g2-stream?
			 :position (g2-stream-frame-get-file-position g2-stream-frame))
		       (setq byte-value?
			     (logandf (wide-character-code ascii-char?)
				      byte-range-0-255-mask))
		       'successfully-read-byte)
		      ((g2-stream-eof-p internal-g2-stream?)
		       'end-of-file-reached)
		      (t 'error-during-read-byte))))
	     (t 'tried-read-byte-when-closed))))
    (update-g2-stream-slots
      g2-stream-frame internal-g2-stream? :status status-symbol)
    (values
      (make-evaluation-integer (or byte-value? -1))
      (make-evaluation-symbol status-symbol))))
    


;;; READ-BYTES-AS-TEXT system procedure.  Returns a string of the bytes read,
;;; and updates the stream slots accordingly.

(defun-for-file-io read-bytes-as-text-lisp-side (n g2-stream-frame)
  (declare (keeps-g2-local-variables-valid t))
  (if (>f n maximum-length-for-user-text-strings)
      (stack-error cached-top-of-stack
                   "Request to read ~d bytes which exceeds the ~
                    maximum G2 text length, ~d"
                   n maximum-length-for-user-text-strings))
  (let* ((internal-g2-stream? (internal-stream-representation g2-stream-frame))
         (result-text-string? nil)
         status-symbol)
    (cond
      ((not (g2-stream-readable-p g2-stream-frame))
       (setq status-symbol 'tried-read-bytes-on-stream-not-opened-for-read))
      (internal-g2-stream?
       (for-g2-stream-read-char-idiom (g2-stream-frame internal-g2-stream?)
        preimported-p charset string-length-exceeded-p initial-file-position ; unused
        (twith-output-to-then-use-of-wide-string
          (loop repeat n
                for ascii-char? = (read-char-idiom-for-g2-stream-frame-reading)
                while ascii-char?
                do (twrite-wide-character-macro
                     (code-wide-character
                       (logandf (wide-character-code ascii-char?)
                                byte-range-0-255-mask)))
                   (when (>=f fill-pointer-for-current-wide-string
                              maximum-length-for-user-text-strings)
                     (setq string-length-exceeded-p t)
                     (loop-finish))
                finally
                  (update-g2-stream-slots
                    g2-stream-frame internal-g2-stream?
                    :position (+f offset position))
                  (setq result-text-string? (copy-current-wide-string))
                  (cond (string-length-exceeded-p
                         (setq status-symbol 'text-truncated-during-read))
                        (ascii-char?
                         (setq status-symbol 'successfully-read-bytes))
                        ((g2-stream-eof-p internal-g2-stream?)
                         (setq status-symbol 'end-of-file-reached))
                        (t (setq status-symbol 'error-during-read-bytes)))))))
      (t (setq status-symbol 'tried-read-bytes-when-closed)))
    (update-g2-stream-slots
      g2-stream-frame internal-g2-stream? :status status-symbol)
    (values
      (make-evaluation-text-reclaiming-argument
        (or result-text-string? (make-wide-string 0)))
      (make-evaluation-symbol status-symbol))))



;;; WRITE-LINE system procedure

;;; Takes two arguments, a g2-stream and a text-string, and returns true if the
;;; line was successfully written, false otherwise.
;;;
;;; Character encodings are converted per the stream's text-conversion-style.
;;; Prior to G2 5.0 this emitted "ascii as much as possible", meaning ASCII
;;; characters as ASCII, and other characters in the Gensym encoding,
;;; potentially resulting in ambiguous output.

;; Write-line-lisp-side has its argument order reversed from that of the G2 system
;; procedure write-line.  This may change someday.

(defun-for-file-io write-line-lisp-side (g2-new-line g2-stream-frame)
  (declare (keeps-g2-local-variables-valid t))
  (write-string-or-line-lisp-side-internal
    (evaluation-text-value g2-new-line)
    g2-stream-frame
    t
    (get-text-conversion-style-structure-for-stream
      g2-stream-frame t)))



;;; WRITE-STRING system procedure

;;; Resembles the system procedure write-line except that it doesn't insert a
;;; linefeed at the end of the string.  Returns true if the line was successfully
;;; written, false otherwise.
;;;
;;; Characters are translated into ASCII as much as possible.

;; Write-string-lisp-side has its argument order reversed from that of the G2
;; system procedure write-string.  This may change someday.

(defun-for-file-io write-string-lisp-side (g2-new-string g2-stream-frame)
  (declare (keeps-g2-local-variables-valid t))
  (write-string-or-line-lisp-side-internal
    (evaluation-text-value g2-new-string)
    g2-stream-frame
    nil
    (get-text-conversion-style-structure-for-stream
      g2-stream-frame t)))



;;; WRITE-LINE-IN-GENSYM-CHARSET system procedure

;;; Takes two arguments, a g2-stream and a text-string, and returns true if the
;;; line was successfully written, false otherwise.
;;;
;;; Characters are left in Gensym Charset format, i.e., not translated into
;;; ASCII or any other charset.  Note that for 5.0, this function and its
;;; write-line variant continue to always emit text in the Gensym character
;;; encoding, i.e., ignoring any text conversion style in the stream.

;; Write-line-lisp-side has its argument order reversed from that of the G2 system
;; procedure write-line.  This may change someday.

(defun-for-file-io write-line-in-gensym-charset-lisp-side
    (g2-new-line g2-stream-frame)
  (declare (keeps-g2-local-variables-valid t))
  (write-string-or-line-lisp-side-internal
    (evaluation-text-value g2-new-line)
    g2-stream-frame
    t
    (text-conversion-style-for-purpose 'utf-g-string)))


;;; WRITE-STRING system procedure

;;; Resembles the system procedure write-line except that it doesn't insert a
;;; linefeed at the end of the string.  Returns true if the line was successfully
;;; written, false otherwise.
;;;
;;; Characters are left in Gensym Charset format, i.e., not translated into
;;; ASCII or any other charset.

(defun-for-file-io write-string-in-gensym-charset-lisp-side
    (g2-new-string g2-stream-frame)
  (declare (keeps-g2-local-variables-valid t))
  (write-string-or-line-lisp-side-internal
    (evaluation-text-value g2-new-string)
    g2-stream-frame
    nil
    (text-conversion-style-for-purpose 'utf-g-string)))



;;; `Write-string-or-line-lisp-side-internal' ... reclaims string.

(defun-for-file-io write-string-or-line-lisp-side-internal
    (string g2-stream-frame line-case? transcode-text-conversion-style)
  (protected-let*
      ((internal-g2-stream?
	 (internal-stream-representation g2-stream-frame)))
    (cond (internal-g2-stream?
	   (let* ((successful-p
		    (prog1
			(cond
			  (line-case?
			   (export-and-emit-text-line
			     string
			     transcode-text-conversion-style
			     internal-g2-stream?))
			  (t
			   (export-and-emit-text-string
			     string
			     transcode-text-conversion-style
			     internal-g2-stream?)))
		      (reclaim-text-string string)))
		  (position?
		    (if successful-p
			(g2-stream-get-file-position internal-g2-stream?)
			nil)))
	     ;; Clear any read buffer.
	     (when (internal-input-stream-buffer? g2-stream-frame)
	       (setf (internal-input-stream-buffer-position g2-stream-frame) 0)
	       (setf (internal-available-characters-in-input-buffer g2-stream-frame) 0))
	     (cond (successful-p
		    (update-g2-stream-slots g2-stream-frame internal-g2-stream?
		      :position position?
		      :status (if line-case?
				  'successfully-wrote-line
				  'successfully-wrote-string))
		    ;; When we know the new offset, copy it into the reading side
		    (when (internal-input-stream-buffer? g2-stream-frame)
		      (setf (internal-input-stream-file-position-offset g2-stream-frame)
			    position?))
		    (values (copy-evaluation-truth-value 
			      evaluation-true-value)
			    (make-evaluation-text "")))
		   (t (update-g2-stream-slots g2-stream-frame internal-g2-stream?
			:status (if line-case?
				    'error-during-write-line
				    'error-during-write-string))
		      (values 
			(copy-evaluation-truth-value 
			  evaluation-false-value)
			(most-recent-file-operation-status-as-text))))))
	  (t (update-g2-stream-slots g2-stream-frame internal-g2-stream?
	       :status (if line-case?
			   'tried-write-line-when-closed
			   'tried-write-string-when-closed))
	     (values (copy-evaluation-truth-value 
		       evaluation-false-value)
		     (make-evaluation-text
		       (if line-case?
			   "Cannot write-line to closed stream"
			   "Cannot write-string to closed stream")))))))






;;; WRITE-BYTE(S) system procedure

;;; WRITE-BYTE takes as argument a g2-stream and a quantity representing a byte.
;;; WRITE-BYTES takes a g2-stream and an evaluation sequence representing 8-bit
;;; bytes to write.  Returns true if the byte(s) were successfully written,
;;; false otherwise.

;;;This unhygienic macro excises many lines of otherwise duplicated code solely
;;;to update pointers and status.  Body is required to return T or NIL to
;;;indicate whether the underlying C stream function was successful, and should
;;;use the bound variable internal-g2-stream? for writing.
(defmacro def-write-byte-function (name arglist reclaimer &body body)
  `(defun-for-file-io ,name ,arglist
     (declare (keeps-g2-local-variables-valid t))
     (prog1 
	 (let ((internal-g2-stream?
		 (internal-stream-representation g2-stream-frame)))
	   (cond (internal-g2-stream?
		  (let* ((successful-p
			   (progn
			     ,@body))
			 (position?
			   (if successful-p
			       (g2-stream-get-file-position internal-g2-stream?)
			       nil)))
		    ;; Clear any read buffer.
		    (when (internal-input-stream-buffer? g2-stream-frame)
		      (setf (internal-input-stream-buffer-position g2-stream-frame) 0)
		      (setf (internal-available-characters-in-input-buffer g2-stream-frame) 0))
		    (cond (successful-p
			   (update-g2-stream-slots g2-stream-frame internal-g2-stream?
						   :position (g2-stream-get-file-position 
							       internal-g2-stream?)
						   :status 'successfully-wrote-byte)
			   ;; When we know the new offset, copy it into the reading side
			   (when (internal-input-stream-buffer? g2-stream-frame)
			     (setf (internal-input-stream-file-position-offset g2-stream-frame)
				   position?))
			   (copy-evaluation-truth-value 
			     evaluation-true-value))
			  (t (update-g2-stream-slots g2-stream-frame internal-g2-stream?
						     :status 'error-during-write-byte)
			     (copy-evaluation-truth-value 
			       evaluation-false-value)))))
		 (t (update-g2-stream-slots g2-stream-frame internal-g2-stream?
					    :status 'tried-write-byte-when-closed)
		    (copy-evaluation-truth-value evaluation-false-value))))
       ,reclaimer)))

       

;; Write-byte-lisp-side has its argument order reversed from that of the G2 system
;; procedure write-byte.  This may change someday (but it seems unlikely).

(def-write-byte-function write-byte-lisp-side (g2-new-byte g2-stream-frame)
  (reclaim-evaluation-integer g2-new-byte)
  (let ((new-byte
	  (evaluation-integer-value g2-new-byte)))
    (g2-stream-write-ascii-byte new-byte internal-g2-stream?)))



(def-write-byte-function write-bytes-lisp-side (sequence g2-stream-frame)
  nil ;;We don't reclaim sequences, that's up to callers.
  (unless (evaluation-sequence-p sequence)
    (stack-error cached-top-of-stack
		 "Request to write bytes of non-sequence value ~a" sequence))
  (let ((buffer (obtain-simple-gensym-string (evaluation-sequence-length sequence))))

    (loop for byte being each evaluation-sequence-element of sequence 
	  as index from 0 do
      (setf (schar buffer index) (code-char (logandf #xff byte))))
    (prog1 
	(g2-stream-write-from-buffer
	  buffer (glength buffer t) internal-g2-stream?)
      (reclaim-simple-gensym-string buffer))))


;;; FLOAT-TO-BYTES

;;; Takes as argument a G2 float and returns eight components as 8-bit bytes.

;; jh, 4/30/91.  Added at request of sf.  Not yet tested.
;; jh, 7/1/91.  Tested.

(defun-for-file-io float-to-bytes-lisp-side (g2-float)
  (declare (keeps-g2-local-variables-valid t))
  (let (bytes-1-and-2 bytes-3-and-4 bytes-5-and-6 bytes-7-and-8)
    (with-temporary-gensym-float-creation float-to-bytes
      (let ((g2-float-value
	      (evaluation-float-value g2-float)))
      (multiple-value-setq
	(bytes-1-and-2 bytes-3-and-4 bytes-5-and-6 bytes-7-and-8)
	(partition-float g2-float-value)))) ;uses 16-bit bytes (from ICP)
    (reclaim-evaluation-float g2-float)
    (macrolet ((get-most-significant-byte (double-byte)
		 `(copy-evaluation-integer
		    (logandf (ashf ,double-byte -8) byte-range-0-255-mask)))
	       (get-least-significant-byte (double-byte)
		 `(copy-evaluation-integer
		    (logandf ,double-byte byte-range-0-255-mask))))
      (values (get-most-significant-byte bytes-1-and-2)
	      (get-least-significant-byte bytes-1-and-2)
	      (get-most-significant-byte bytes-3-and-4)
	      (get-least-significant-byte bytes-3-and-4)
	      (get-most-significant-byte bytes-5-and-6)
	      (get-least-significant-byte bytes-5-and-6)
	      (get-most-significant-byte bytes-7-and-8)
	      (get-least-significant-byte bytes-7-and-8)))))




;;; BYTES-TO-FLOAT

;;; Takes as argument eight 8-bit bytes and returns a float with these bytes as
;;; components.

;; jh, 4/30/91.  Added at request of sf.  Not yet tested.
;; jh, 7/1/91.  Tested.

;; jh, 9/27/93.  Fixed bytes-to-float-lisp-side to ensure that the bytes it
;; passes to reconstruct-byte are unsigned and never longer than 16 bits.  This
;; fixes a bug when users store floats in implementations that represent some
;; characters as negative integers.

(defun-for-file-io bytes-to-float-lisp-side
		   (byte1 byte2 byte3 byte4 byte5 byte6 byte7 byte8)
  (declare (keeps-g2-local-variables-valid t))
  (with-temporary-gensym-float-creation bytes-to-float
    (macrolet ((merge-bytes (most-significant-byte least-significant-byte)
		 `(logiorf
		    (ashf (logandf
			    (evaluation-integer-value ,most-significant-byte)
			    byte-range-0-255-mask)
			  8)
		    (logandf
		      (evaluation-integer-value ,least-significant-byte)
		      byte-range-0-255-mask))))
      (let* ((bytes-1-and-2 (merge-bytes byte1 byte2))
	     (bytes-3-and-4 (merge-bytes byte3 byte4))
	     (bytes-5-and-6 (merge-bytes byte5 byte6))
	     (bytes-7-and-8 (merge-bytes byte7 byte8))
	     (g2-float-value
	       (reconstruct-float ;uses 16-bit bytes (from ICP machinery)
		 bytes-1-and-2
		 bytes-3-and-4
		 bytes-5-and-6
		 bytes-7-and-8)))
	(reclaim-evaluation-integer byte1)
	(reclaim-evaluation-integer byte2)
	(reclaim-evaluation-integer byte3)
	(reclaim-evaluation-integer byte4)
	(reclaim-evaluation-integer byte5)
	(reclaim-evaluation-integer byte6)
	(reclaim-evaluation-integer byte7)
	(reclaim-evaluation-integer byte8)
	(make-evaluation-float g2-float-value)))))


;;;; Filestring Parsing Procedures

;; jh, 11/9/91.  Added the def-filename-partition-system-procedure abstraction, so
;; we don't have to repeat any change in the gensym-namestring interface six
;; times.

(defmacro def-filename-partition-system-procedure (name accessor)
  `(defun-for-file-io ,name (g2-filestring)
     (declare (keeps-g2-local-variables-valid t))
     (let* ((filestring 
	      (export-text-string	; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
		(evaluation-text-value g2-filestring)
		'G2-DIRECTORY-PATHNAME))
	    (raw-component-string
	      (,accessor filestring))
	    (component-string
	      (import-text-string	; Previously: convert-ascii-filename-to-text-string-as-much-as-possible
		raw-component-string
		'G2-DIRECTORY-PATHNAME)))
       (reclaim-evaluation-text g2-filestring)
       (reclaim-text-string filestring)
       (reclaim-text-string raw-component-string)
       component-string)))


;; jh, 11/9/91.  Added reconversion back to ascii for the gensym-xxx-namestring
;; operations.  Previously, a file namestring signifying previous version on UNIX
;; wasn't getting partitioned correctly, because the ascii tilde wasn't converted
;; to the double-tilde sequence that G2 needs.



;;; FILE-HOST-STRING system procedure

;;; Takes as argument a filestring and returns the host component as a
;;; text-string.  If the argument cannot be parsed, or if it has no host component
;;; when parsed, file-host-string returns an empty text-string.

;; Consider making errors here disembodied file errors like in rename, delete, and
;; the like.

(def-filename-partition-system-procedure file-host-string-lisp-side
					 gensym-host-namestring)




;;; FILE-DEVICE-STRING system procedure

;;; Takes as argument a filestring and returns the device component as a
;;; text-string.  If the filestring cannot be parsed, or if it has no device
;;; component when parsed, file-device-string returns an empty text-string.

;; Consider making errors here disembodied file errors like in rename, delete, and
;; the like.

;; The debate here is whether or not to return the actual UNIX device name.  This
;; would be much more useful than the common lisp device, which is always null for
;; UNIX filesystems.

(def-filename-partition-system-procedure file-device-string-lisp-side
					 gensym-device-namestring)




;;; FILE-DIRECTORY-STRING system procedure

;;; Takes as argument a filestring and returns the directory component as a
;;; text-string.  If the filestring cannot be parsed, or if it has no directory
;;; component when parsed, file-directory-string returns an empty text-string.

;; Consider making errors here disembodied file errors like in rename, delete, and
;; the like.

(def-filename-partition-system-procedure file-directory-string-lisp-side
					 gensym-directory-namestring)




;;; FILE-DIRECTORY-STRING-TO-LIST

;;; Takes as argument a filestring and returns its directory components in a
;;; text-list.  If the filestring cannot be parsed as a directory,
;;; file-directory-string-to-list returns an empty text-list.  Note that this is
;;; indistinguishable from the root directory.  If this distinction is necessary,
;;; the user can call file-exists.

(defun-for-file-io file-directory-string-to-list-lisp-side (g2-filestring)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((filestring 
	   (export-text-string		; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
	     (evaluation-text-value g2-filestring)
	     'G2-DIRECTORY-PATHNAME))
	 (pathname?
	   (gensym-pathname filestring))
	 (list-frame
	   (make-transient-item 'text-list)))
    (when pathname?
      (loop for directory-component in (gensym-pathname-directory pathname?)
	    do
	    (cond 
	      ((eq directory-component :absolute))
	      ((eq directory-component :relative)) 
	      ((eq directory-component :up)
	       (g2-list-remove-first list-frame))
	      #+development
	      ((symbolp directory-component)
	       (error "FILE-DIRECTORY-STRING-TO-LIST: ~
                       unknown directory component ~a"
		      directory-component))
	      (t (let ((converted-component
			 (import-text-string ; Previously: convert-ascii-filename-to-text-string-as-much-as-possible
			   directory-component
			   'G2-DIRECTORY-PATHNAME)))
		   (g2-list-insert-at-end
		     (make-evaluation-text-reclaiming-argument
		       converted-component)
		     list-frame)
		   )))))
    (reclaim-evaluation-text g2-filestring)
    (reclaim-text-string filestring)
    (when pathname?
      (reclaim-gensym-pathname pathname?))
    list-frame))



;;; FILE-DIRECTORY-LIST-TO-STRING

;;; Takes as argument a text-list and returns a text-string with the components of
;;; that list assembled into a directory string which gives a path relative to the
;;; current directory.  Note that this function always uses the default file
;;; system, which might cause problems for development on Lisp Machines.

(defun-for-file-io file-directory-list-to-string-lisp-side (text-list-frame)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((directory-components
	   (path-cons
	     :absolute
	     (loop for element being each g2-list-element in text-list-frame
		   collect
		   ;; These elements should not be reclaimed.  They are the
		   ;; actual g2-list element values.  Only reclaim the list
		   ;; below.
		   (evaluation-text-value element)
		     using path-cons)))
	 (directory-pathname
	   (gensym-make-pathname
	     :directory directory-components))
	 (raw-directory-namestring
	   (gensym-namestring directory-pathname))
	 (directory-namestring
	   (import-text-string ; Previously: convert-ascii-filename-to-text-string-as-much-as-possible
	     raw-directory-namestring
	     'G2-DIRECTORY-PATHNAME)))
    (prog1 directory-namestring
           (reclaim-path-list directory-components) ;Reclaim list only, not text.
	   (reclaim-text-string raw-directory-namestring)
	   (reclaim-gensym-pathname directory-pathname))))




;;; FILE-BASE-NAME-STRING system procedure

;;; Takes as argument a filestring and returns its basic name component as a
;;; text-string.  If the filestring cannot be parsed, or if it has no directory
;;; component when parsed, file-root-name-string returns an empty text-string.

;; The word "root" instead of "base" could cause confusion with the UNIX root.

;; Consider making errors here disembodied file errors like in rename, delete, and
;; the like.

(def-filename-partition-system-procedure file-base-name-string-lisp-side
					 gensym-base-namestring)




;;; FILE-EXTENSION-STRING system procedure

;;; Takes as argument a filestring and returns its extension component (called
;;; "type" in Common Lisp) as a text-string.  If the filestring cannot be parsed,
;;; or if it has no extension component when parsed, file-extension-string returns
;;; an empty text-string.

;; Consider making errors here disembodied file errors like in rename, delete, and
;; the like.

(def-filename-partition-system-procedure file-extension-string-lisp-side
					 gensym-type-namestring)




;;; FILE-VERSION-STRING system procedure

;;; Takes as argument a filestring and returns version type component as a
;;; text-string.  If the filestring cannot be parsed, or if it has no version
;;; component when parsed, file-type-string returns an empty text-string.

;; Consider making errors here disembodied file errors like in rename, delete, and
;; the like.

(def-filename-partition-system-procedure file-version-string-lisp-side
					 gensym-version-namestring)





;;; COLLECT-INTO-FILESTRING system procedure

;;; Takes six arguments, text-strings naming host, device, directory, root name,
;;; type, and version components.  Returns a filestring containing these
;;; components.  If any component is ill-formed, an empty string is returned.

;; This should at least add terminating slashes for UNIX directories.

(defun-for-file-io collect-into-filestring-lisp-side 
		   (g2-host-string
		     g2-device-string
		     g2-directory-string
		     g2-root-name-string
		     g2-type-string
		     g2-version-string)
  (declare (keeps-g2-local-variables-valid t))
  (protected-let* 
      ((host-string
	 (export-text-string		; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
	   (evaluation-text-value g2-host-string)
	   'G2-DIRECTORY-PATHNAME)
	 (reclaim-text-string host-string))
       (device-string
	 (export-text-string		; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
	   (evaluation-text-value g2-device-string)
	   'G2-DIRECTORY-PATHNAME)
	 (reclaim-text-string device-string))
       (directory-string
	 (export-text-string		; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
	   (evaluation-text-value g2-directory-string)
	   'G2-DIRECTORY-PATHNAME)
	 (reclaim-text-string directory-string))
       (root-name-string
	 (export-text-string		; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
	   (evaluation-text-value g2-root-name-string)
	   'G2-DIRECTORY-PATHNAME)
	 (reclaim-text-string root-name-string))
       (type-string
	 (export-text-string		; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
	   (evaluation-text-value g2-type-string)
	   'G2-DIRECTORY-PATHNAME)
	 (reclaim-text-string type-string))
       (version-string
	 (export-text-string		; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
	   (evaluation-text-value g2-version-string)
	   'G2-DIRECTORY-PATHNAME)
	 (reclaim-text-string version-string))
       (raw-collected-string
	 (tformat-text-string "~a~a~a~a~a~a" 
			      host-string
			      device-string
			      directory-string
			      root-name-string
			      type-string
			      version-string)
	 (reclaim-text-string raw-collected-string))
       (collected-string 
	 (import-text-string		; Previously: convert-ascii-filename-to-text-string-as-much-as-possible
	   raw-collected-string
	   'G2-DIRECTORY-PATHNAME))
       (pathname-from-collected-string?
	 (gensym-pathname collected-string)
	 (reclaim-gensym-pathname pathname-from-collected-string?)))
    (prog1 
      (if pathname-from-collected-string?
	  collected-string
	  (make-evaluation-text ""))
      (reclaim-evaluation-text g2-host-string)
      (reclaim-evaluation-text g2-device-string)
      (reclaim-evaluation-text g2-directory-string)
      (reclaim-evaluation-text g2-root-name-string)
      (reclaim-evaluation-text g2-type-string)
      (reclaim-evaluation-text g2-version-string))))





;;; PARTITION-FILESTRING system procedure

;;; Takes as argument a filestring and returns six values, text-strings naming
;;; host, device, directory, root name, type, and version components.  If any
;;; component is ill-formed, six empty strings are returned.


(defun-for-file-io partition-filestring-lisp-side (g2-filestring)
  (declare (keeps-g2-local-variables-valid t))
  (protected-let*
      ((filestring 
	 (prog1 (export-text-string		; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
		  (evaluation-text-value g2-filestring)
		  'G2-DIRECTORY-PATHNAME)
		(reclaim-evaluation-text g2-filestring))
	 (reclaim-text-string filestring))
       (pathname?
	 (gensym-pathname filestring)
	 (reclaim-gensym-pathname pathname?)))
    (if pathname?
	(macrolet 
	    ((back-from-ascii (accessor)
	       `(let ((namestring (,accessor pathname?)))
		  (prog1
		    (import-text-string ; Previously: convert-ascii-filename-to-text-string-as-much-as-possible
		      namestring
		      'G2-DIRECTORY-PATHNAME)
		    (reclaim-text-string namestring)))))
	  (let ((host-string (back-from-ascii gensym-host-namestring))
		(device-string (back-from-ascii gensym-device-namestring))
		(directory-string (back-from-ascii gensym-directory-namestring))
		(base-string (back-from-ascii gensym-base-namestring))
		(type-string (back-from-ascii gensym-type-namestring))
		(version-string (back-from-ascii gensym-version-namestring)))
	    (values host-string
		    device-string
		    directory-string
		    base-string
		    type-string
		    version-string)))
	(values (make-evaluation-text "")
		(make-evaluation-text "")
		(make-evaluation-text "")
		(make-evaluation-text "")
		(make-evaluation-text "")
		(make-evaluation-text "")))))



;;;; File Attribute Procedures


;;; TYPE-OF-FILE-SYSTEM

;;; Takes no arguments and returns a symbol indicating the default file system used
;;; on this platform.  Its simplicity belies the amount it will help the
;;; user trying to develop kbs which use file i/o in a platform-independent way.

;; Eventually it will be more complicated, when we introduce a multi-filesystem
;; server.

(defun-for-file-io type-of-file-system-lisp-side ()
  (declare (keeps-g2-local-variables-valid t))
  (make-evaluation-symbol (local-file-system)))




;;; FILE-EXISTS system procedure

;;; Takes as argument a text-string naming a file and returns true if the named
;;; file exists, false otherwise.  Does not affect last-status-mesage-for-file,
;;; since it never should cause an error.

(defun-for-file-io file-exists-lisp-side (g2-filestring)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((filestring (export-filename-from-g2-string (evaluation-text-value g2-filestring)))
	 (exists-p (g2-stream-probe-file-for-exist filestring)))
    (prog1
      (if exists-p
	  (copy-evaluation-truth-value evaluation-true-value)
	  (copy-evaluation-truth-value evaluation-false-value))
      (reclaim-evaluation-text g2-filestring)
      (reclaim-text-string filestring))))

  

;;; FILE-NAMES-ARE-IDENTICAL system procedure

;;; Takes as argument two filestrings returns true if the they denote the same
;;; file, false otherwise.  Does not affect last-status-mesage-for-file, since it
;;; never should cause an error.

;; Needs more accuracy when one filename gives a version and the other gives
;; :newest.  Currently (3/20/91, jh) these are never considered equal.  Actually,
;; this is a problem with gensym-pathnames-equal-enough-p as it is used in save-kb
;; too.

(defun-for-file-io file-names-are-identical-lisp-side
		   (g2-filestring-1 g2-filestring-2)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((filestring-1
	   (export-text-string		; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
	     (evaluation-text-value g2-filestring-1)
	     'G2-DIRECTORY-PATHNAME))
	 (filestring-2
	   (export-text-string		; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
	     (evaluation-text-value g2-filestring-2)
	     'G2-DIRECTORY-PATHNAME))
	 (pathname-1?
	   (gensym-pathname filestring-1))
	 (pathname-2?
	   (gensym-pathname filestring-2)))
    (prog1
      (if (and pathname-1?
	       pathname-2?
	       (gensym-pathnames-equal-enough-p pathname-1? pathname-2?))
	  (copy-evaluation-truth-value evaluation-true-value)
	  (copy-evaluation-truth-value evaluation-false-value))
      (reclaim-evaluation-value g2-filestring-1)
      (reclaim-evaluation-value g2-filestring-2)
      (reclaim-text-string filestring-1)
      (reclaim-text-string filestring-2)
      (when pathname-1?
	(reclaim-gensym-pathname pathname-1?))
      (when pathname-2?
	(reclaim-gensym-pathname pathname-2?)))))




;;; LENGTH-OF-FILE system procedure

;;; Returns the length of the file in bytes.  If an error occurs, modifies the
;;; status slot of the stream and returns -1.  Note that it is only possible to
;;; determine the length of an open file, ie, by using an instance of the
;;; g2-stream class, not by using a text-string.

;; Need error-checking on the types passed by "lisp call".  It is quite easy to
;; pass a frame to something expecting a text-string and crash G2 thereby.

(defun-for-file-io length-of-file-lisp-side (g2-stream-frame)
  (declare (keeps-g2-local-variables-valid t))
  (let ((internal-g2-stream?
	  (internal-stream-representation g2-stream-frame)))
    (cond (internal-g2-stream?
	   (let ((file-length?
		   (g2-stream-file-length internal-g2-stream?)))
	     (cond (file-length?
		    (update-g2-stream-slots g2-stream-frame internal-g2-stream?
		      :status 'successfully-obtained-file-length)
		    (values (make-evaluation-integer file-length?)
			    (make-evaluation-text "")))
		   (t (update-g2-stream-slots g2-stream-frame internal-g2-stream?
			:status 'error-getting-file-length)
		      (values (make-evaluation-integer -1)
			      (most-recent-file-operation-status-as-text))))))
	  (t (update-g2-stream-slots g2-stream-frame internal-g2-stream?
	       :status 'tried-to-get-length-when-closed)
	     (values (make-evaluation-integer -1)
		     (make-evaluation-text
		       "Cannot get length of closed stream"))))))




;;; LATEST-DATE-FILE-WAS-MODIFIED system procedure

;;; Takes as argument a filestring and returns a float giving the most recent time
;;; the named file was opened, read, or written.  This time is represented as a
;;; number of seconds since January 1, 1970 GMT, and is a standard of sorts.  If
;;; it is not possible to determine when the file was most recently modified, -1.0
;;; will be returned.  In this case, a text-string describing the error can be
;;; obtained from the system procedure last-status-message-for-file.

;;; The reason we return a float is for compatability with the new representation
;;; of absolute time as a double-precision float.  Thus we allow the user to
;;; reason about files the same way she reasons about eveything else, albeit with
;;; less accuracy.

;;; UNIX systems typically store the file timestamp as a long integer, which means
;;; it will wrap sometime after the year 2106 AD.  On the UNIX systems of today,
;;; users desiring microsecond accuracy for file creation times are out of luck.

;;; G2 uses the unix model of file timestamping.  This comprises three timestamps:
;;;   modification:  last time the file was opened or written 
;;;   access:        last time the file was opened, read, or written 
;;;   status change: last time the file was opened, written, renamed, or had its 
;;;                  permissions changed.  

;;; The user will have to infer the answer to more common queries about file
;;; timestamps.  For example, a good guess is that the creation date of a closed
;;; file is the same as its last modification date.  There is some question that
;;; this model is only partially adhered to in Vax C, because of the inopportune
;;; description of the st_ctime field as "creation time".  It is actually "change
;;; time", so we need to test the VMS platforms with special care.

;;; Note that it doesn't matter whether or not there is an open stream to this
;;; file, so a modification date may quickly become inaccurate.  Also note that
;;; operating system calls exist which permit the user to change timestamps on
;;; files.  If there is user interest, these could be provided, though these tools
;;; can lead to great confusion.

(defun-for-file-io latest-date-file-was-modified-lisp-side
		   (g2-filestring)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((filestring
	   (export-text-string		; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
	     (evaluation-text-value g2-filestring)
	     'G2-DIRECTORY-PATHNAME))
	 (modification-date? ;a managed float or nil
	   (g2-stream-file-modification-date filestring)))
    (reclaim-evaluation-text g2-filestring)
    (reclaim-text-string filestring)
    (cond (modification-date?
	   (values modification-date?
		   (make-evaluation-text "")))
	  (t (values (make-evaluation-float -1.0)
		     (most-recent-file-operation-status-as-text))))))





;;; LATEST-DATE-FILE-WAS-ACCESSED system-procedure

;;; Takes as argument a filestring and returns a float giving the most recent time
;;; the named file was opened or written.

;;; Details are the same as for the system procedure
;;; latest-date-file-was-modified.  See the notes attached to that function.

(defun-for-file-io latest-date-file-was-accessed-lisp-side
		   (g2-filestring)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((filestring
	   (export-text-string		; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
	     (evaluation-text-value g2-filestring)
	     'G2-DIRECTORY-PATHNAME))
	 (access-date? ;a managed float or nil
	   (case local-file-system
	     ((win32 dos) (g2-stream-file-modification-date filestring))
	     (otherwise (g2-stream-file-access-date filestring)))))
    (reclaim-evaluation-text g2-filestring)
    (reclaim-text-string filestring)
    (cond (access-date?
	   (values access-date?
		   (make-evaluation-text "")))
	  (t (values (make-evaluation-float -1.0)
		     (most-recent-file-operation-status-as-text))))))

;; jh, 1/19/95.  Added a HACK to work around a bug in how the NT implementation
;; of stat() fills the st_atime slot.  Currently, we get a randomly increasing
;; number that has nothing to do with when the file was accessed.  Until we get
;; a patch from Microsoft, or until we otherwise resolve bug HQ-176007 "NT file
;; access date skewed", this is the best we can do.  One weak rationale is that
;; file access time and file modification time appear to be the same on many
;; UNIX systems.


;;; LATEST-DATE-FILE-ATTRIBUTES-WERE-CHANGED system-procedure

;;; Takes as argument a filestring and returns a float giving the most recent time
;;; the named file was opened, written, renamed, or had its permissions changed.

;;; Details are the same as for the system procedure
;;; latest-date-file-was-modified.  See the notes attached to that function.

(defun-for-file-io latest-date-file-attributes-were-changed-lisp-side
		   (g2-filestring)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((filestring
	   (export-text-string		; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
	     (evaluation-text-value g2-filestring)
	     'G2-DIRECTORY-PATHNAME))
	 (change-date? ;a managed float or nil
	   (g2-stream-file-status-change-date filestring)))
    (reclaim-evaluation-text g2-filestring)
    (reclaim-text-string filestring)
    (cond (change-date?
	   (values change-date?
		   (make-evaluation-text "")))
	  (t (values (make-evaluation-float -1.0)
		     (most-recent-file-operation-status-as-text))))))




;;;; Directory-related Procedures


;;; DIRECTORY-EXISTS system procedure

;;; Takes as argument a text-string naming a directory and returns true if the
;;; named directory exists, false otherwise.  Does not affect
;;; last-status-mesage-for-file, since it never should cause an error.

;; Have to take into account that VMS can specify a directory as an incomplete
;; pathname, (eg "[jh.subdir]") as well as a filename (eg "[jh]subdir.dir").  Only
;; the latter will currently (jh, 3/20/91) work with the underlying g2-streams
;; implementation.
;; jh, 10/30/91.  Improved directory-exists-lisp-side to allow most incomplete
;; pathnames to be specified as directories.  The only pathname which can't be
;; specified now is (:relative), which requires going out to the file system to
;; get its parent directory.

(defun-for-file-io directory-exists-lisp-side (g2-filestring)
  (declare (keeps-g2-local-variables-valid t))
  (protected-let* 
      ((filestring
	 (export-text-string		; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
	   (evaluation-text-value g2-filestring)
	   'G2-DIRECTORY-PATHNAME)
	 (reclaim-text-string filestring))
       (directory-as-file?
	 (or (gensym-directory-as-file filestring)
	     ;; yduj: can't use gensym-pathname below, because it will never return nil
	     ;; and the resulting empty pathname might name a valid file
	     (with-pathname-conversion 
		  ((filestring pathname?))
		pathname?))
	 (when directory-as-file? (reclaim-gensym-pathname directory-as-file?))))
    (prog1 
	(if directory-as-file?
	    (protected-let* 
		((directory-as-namestring
		   (gensym-namestring directory-as-file?)
		   (reclaim-text-string directory-as-namestring))
		 (exists-p
		   ;; jh, 2/10/94.  Not sure why the probe-file, and it is
		   ;; breaking the NT, where directories are not files nohow.
		   ;; (q.v. make-canonical-wild-directory-pathname-if-possible
		   ;; in PATHNAMES).
		   (and ;(g2-stream-probe-file directory-as-namestring)
		        (g2-stream-directory-p directory-as-namestring))))
	      (if exists-p 
		  (copy-evaluation-truth-value evaluation-true-value)
		  (copy-evaluation-truth-value evaluation-false-value)))
	    (copy-evaluation-truth-value evaluation-false-value))
      (reclaim-evaluation-text g2-filestring))))





;;; FILES-IN-DIRECTORY system procedure

;;; Takes as argument a text-string representing a directory to be searched.
;;; Returns a text-list of strings naming the files in the directory (including
;;; subdirectories).

;; Notifying the user of an error is hard.  For now, we should suggest that
;; directory-exists be called on a potential directory to anticipate errors.
;; There is no other easy way to tell the differency between an empty directory
;; list and an error.

;; We have to decide whether a directory listed by the subdirectories-in-directory
;; system procedure can also show up in a files-in-directory list.

;; jh, 10/31/91.  Changed files-in-directory-lisp-side and
;; subdirectories-in-directory-lisp-side to get the entire directory contents if
;; the pathname is devoid of name, type, and version.  The user probably doesn't
;; expect to have to type in the final "*.*", although that format would be more
;; consistent with what is done for partial directory contents like "*.kb".  Note
;; that we only get the newest version of each file.  To get all versions, the
;; user must explicitly type "*.*.*" (or "*" on UNIX systems).  Again, this is
;; less consistent but probably more convenient.

(defun-for-file-io files-in-directory-lisp-side (g2-directory-string)
  (declare (keeps-g2-local-variables-valid t))
  (protected-let*
      ((directory-string
	 (export-text-string		; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
	   (evaluation-text-value g2-directory-string)
	   'G2-DIRECTORY-PATHNAME)
	 (reclaim-text-string directory-string))
       (directory-pathname?
	 (let ((accept-any-version-component-p t)) ;for wildcarding versions
	   (gensym-pathname directory-string))
	 (reclaim-gensym-pathname directory-pathname?)))

    (when directory-pathname?
      (let ((canonical-wild-directory-pathname?
	      (make-canonical-wild-directory-pathname-if-possible 
		directory-pathname?
		directory-string)))
	(when canonical-wild-directory-pathname?
	  (reclaim-gensym-pathname directory-pathname?)
	  (setq directory-pathname? canonical-wild-directory-pathname?))))

    (protected-let*
        ((pathnames-in-directory
	   (gensym-directory directory-pathname?)
	   (reclaim-path-list pathnames-in-directory))
	 (list-frame
	   (make-transient-item 'text-list)))
      (loop for pathname-in-directory in pathnames-in-directory
	    when (gensym-pathname-name pathname-in-directory)
	      do
	      (protected-let*
	          ((filestring-in-directory
		     (gensym-file-namestring pathname-in-directory)
		     (reclaim-text-string filestring-in-directory))
		   (converted-filestring
		     ;; Doesn't need reclaiming.  It's inserted into the g2-list.
		     (import-text-string ; Previously: convert-ascii-filename-to-text-string-as-much-as-possible
		       filestring-in-directory
			'G2-DIRECTORY-PATHNAME)))
		(g2-list-insert-at-beginning
		  (make-evaluation-text-reclaiming-argument converted-filestring)
		  list-frame))
	    do
	(reclaim-gensym-pathname pathname-in-directory)
	    finally
	      (reclaim-evaluation-text g2-directory-string)
	      (return 
		(values list-frame
			(if (g2-stream-error-flag-set-p)
			    (most-recent-file-operation-status-as-text)
			    (make-evaluation-text ""))))))))


;;; SUBDIRECTORIES-IN-DIRECTORY system procedure

;;; Takes as argument a text-string representing a directory to be searched.
;;; Returns a text-list of strings naming the subdirectories in the directory.

;; For details of error handling, see note under the files-in-directory system
;; procedure.

;; We have to decide whether a directory listed by the subdirectories-in-directory
;; system procedure can also show up in a files-in-directory list.

(defun-for-file-io subdirectories-in-directory-lisp-side 
		   (g2-directory-string)
  (declare (keeps-g2-local-variables-valid t))
  (protected-let* 
   ((directory-string
      (export-text-string		; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
	(evaluation-text-value g2-directory-string)
	'G2-DIRECTORY-PATHNAME)
      (reclaim-text-string directory-string))
    (subdirectories-in-directory
     (all-subdirectories-in-directory directory-string)
     (reclaim-path-list subdirectories-in-directory))
    (list-frame
     (make-transient-item 'text-list)))
   (loop for subdirectory-in-directory in subdirectories-in-directory
	 when (gensym-pathname-name subdirectory-in-directory)
	   do
	   (protected-let*
	       ((filestring-in-directory
		  (gensym-file-namestring subdirectory-in-directory)
		  (reclaim-text-string filestring-in-directory))
		(converted-filestring
		  ;; Doesn't need reclaiming.  It's put in the g2-list below.
		  (import-text-string	; convert-ascii-filename-to-text-string-as-much-as-possible
		    filestring-in-directory
		    'G2-DIRECTORY-PATHNAME)))
	     (g2-list-insert-at-beginning
	       (make-evaluation-text-reclaiming-argument converted-filestring)
	       list-frame))
	 do
     (reclaim-gensym-pathname subdirectory-in-directory)
	 finally
	 (reclaim-evaluation-text g2-directory-string)
	 (return 
	   (values list-frame
		   (if (g2-stream-error-flag-set-p)
		       (most-recent-file-operation-status-as-text)
		       (make-evaluation-text "")))))))




;;; DEFAULT-DIRECTORY system procedure

;;; Takes no arguments and returns the current directory as a text-string.  If
;;; unable to do so, returns an empty text-string.

;; Use getwd in UNIX and getcwd in Vax C.

(defun-for-file-io default-directory-lisp-side ()
  (declare (keeps-g2-local-variables-valid t))
  (protected-let ((raw-default-directory?
		    (g2-stream-get-default-directory)
		    (reclaim-text-string raw-default-directory?)))
    (if raw-default-directory?
	(values
	  (import-text-string
	    raw-default-directory?
	    'G2-DIRECTORY-PATHNAME)
	  (make-evaluation-text ""))
	(values 
	  (make-evaluation-text "")
	  (most-recent-file-operation-status-as-text)))))




;;; CHANGE-DEFAULT-DIRECTORY system procedure

;;; Given a namestring, returns true if it was able to successfully change the
;;; default directory appropriately, false otherwise.

;; Use chdir in UNIX and Vax C.

;; jh, 8/29/91.  Changed change-default-directory to alter the various default
;; pathnames kept by G2 as a record of the most recent "load" operations.  This is
;; only done if we were able to change the default directory in the operating
;; system as well.

;; jh, 11/12/91.  Improved change-default-directory to do the same defaulting that
;; happens in execute-file command.  Previously, we defaulted to exactly what the
;; user supplied, which was confusing the next time a KB was loaded, for example.


(defun-for-file-io change-default-directory-lisp-side (g2-new-directory-string)
  (declare (keeps-g2-local-variables-valid t))
  (protected-let* 
      ((new-directory-string
	 (export-text-string		; Previously: convert-text-string-to-ascii-filename-as-much-as-possible
	   (evaluation-text-value g2-new-directory-string)
	   'G2-DIRECTORY-PATHNAME)
	 (reclaim-text-string new-directory-string))
       (new-directory-pathname?
	 (get-new-directory-pathname-dwim new-directory-string)
	 (reclaim-gensym-pathname new-directory-pathname?))
       (changed-p nil))
    (when new-directory-pathname?
      (protected-let ((dwim-directory-string
			(gensym-namestring new-directory-pathname?)
			(reclaim-text-string dwim-directory-string)))
	(when (g2-stream-change-default-directory dwim-directory-string)
	  (macrolet 
	      ((replace-default (default-var symbolic-file-type)
		 `(if ,default-var
		      (store-current-pathname
			,default-var
			(gensym-merge-pathnames 
			  new-directory-pathname?
			  ,default-var))
		      (setq ,default-var
			    (make-first-time-default-pathname 
			      ,symbolic-file-type)))))
	    (replace-default current-foreign-image-pathname?   'foreign-image)
	    (replace-default current-attribute-file-pathname?  'attribute)
	    (replace-default current-statistics-file-pathname? 'statistics)
	    (replace-default current-kb-pathname?              'kb)
	    (unless (directory-for-log-files log-file-parameters)
	      (replace-default log-file-default-pathname?      'log)))
	  (setq changed-p t))))
    (reclaim-evaluation-value g2-new-directory-string)
    (if changed-p
	(values (copy-evaluation-truth-value evaluation-true-value)
		(make-evaluation-text ""))
	(values (copy-evaluation-truth-value evaluation-false-value)
		(most-recent-file-operation-status-as-text)))))


(defun-for-file-io get-temporary-filename-lisp-side ()
  (declare (keeps-g2-local-variables-valid t))
  (let ((val (make-unique-file-name "g2")))
    (unless val
      (stack-error cached-top-of-stack
		   "Unable to obtain temporary filename from operating system."))
    (values (make-evaluation-text val))))



;;; DISK-SPACE-AVAILABLE-IN-DIRECTORY system procedure

;;; Given a directory as a text-string, returns the number of blocks of disk space
;;; available for writing into that directory.  If that number cannot be
;;; determined, or if an invalid directory was specified, -1 is returned.  In this
;;; case, a text-string describing the error can be obtained from the system
;;; procedure last-status-message-for-file.  On both UNIX and VMS file systems, a
;;; block is typically 512 bytes.  We should consider supplying this in bytes,
;;; once we get a handle on the bignum problems that may result.

(defun-for-file-io disk-space-available-in-directory-lisp-side
		   (g2-directory-filestring)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((directory-filestring
	   (export-text-string
	     ;; was convert-text-string-to-ascii-filename-as-much-as-possible
	     (evaluation-text-value g2-directory-filestring)
	     'G2-DIRECTORY-PATHNAME))
	 (space-available?
	   (g2-stream-available-disk-space-in-device directory-filestring)))
    (reclaim-evaluation-text g2-directory-filestring)
    (reclaim-text-string directory-filestring)
    (cond (space-available?
	   (values (make-evaluation-integer space-available?)
		   (make-evaluation-text "")))
	  (t (values (make-evaluation-integer -1)
		     (most-recent-file-operation-status-as-text))))))


;;; DEVICES-ON-MACHINE system procedure

;;; Returns a text-list of the names of the available devices on this machine.
;;; Currently (jh, 10/3/96) this can only return a non-empty text-list on
;;; Window/NT.  UNIX has does not use a separate namespace for devices, and a
;;; VMS implementation does not yet exist.

(defun-for-file-io devices-on-machine-lisp-side ()
  (let ((device-names (g2-stream-devices))
	(list-frame (make-transient-item 'text-list)))
    (loop for device-name in device-names
	  do
      (g2-list-insert-at-beginning
	(make-evaluation-text-reclaiming-argument device-name)
	list-frame)
	  finally (reclaim-path-list device-names))
    list-frame))


(defun-for-file-io create-directory-lisp-side (g2-filestring create-parents-tv mask)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((filestring
	   (export-text-string
	     (evaluation-text-value g2-filestring)
	     'G2-DIRECTORY-PATHNAME))
	 (do-create-parent
	   (if (evaluation-truth-value-is-true-p create-parents-tv)
	       1
	       0))
	 (success?
	   (c-g2_create_directory filestring do-create-parent mask)))
    (prog1
      (if (eql success? 1)
	  (copy-evaluation-truth-value evaluation-true-value)
	  (copy-evaluation-truth-value evaluation-false-value))
      (reclaim-evaluation-text g2-filestring)
      (reclaim-evaluation-text mask)
      (reclaim-text-string filestring))))

(declare-system-procedure-function g2-version-of-kb-file t)
(defun g2-version-of-kb-file (pathname)
  (let* ((full-pathname (make-full-pathname pathname))
	 (plist (read-initial-plist full-pathname nil nil)))
    (prog1
	(if (null plist)
	    ;; In this case a "not a KB or lacks a proper KB header"
	    ;; message has been printed to the Operator Logbook. - jpg 3/14/05
	    (allocate-evaluation-structure
	      (eval-list
		'version-text (make-evaluation-text "")))
	    (let* ((system-version (getf plist 'system-version))
		   (major (first system-version))
		   (minor (multiple-value-bind (floor rem)
			      (floorf (second system-version) 10)
			    (if (=f rem 0) floor (second system-version))))
		   (string (fourth system-version)))
	      (allocate-evaluation-structure
		(eval-list
		  'version-text
		  (tformat-text-string "G2 ~d.~d ~a" major minor string)
		  'major-version-number major 
		  'minor-version-number minor 
		  'revision-text (copy-as-wide-string string)))))
      (reclaim-gensym-pathname full-pathname)
      (reclaim-slot-value plist)
      (reclaim-evaluation-text pathname))))



;;;; Process-related Procedures



;;; SPAWN-PROCESS-TO-RUN-COMMAND-LINE system procedure

;;; Takes as argument a command line, spawns a process to execute it in the host
;;; operating system, and returns immediately.  If the process was successfully
;;; spawned, spawn-process-to-run-command-line returns the process ID as a float,
;;; -1.0 otherwise.  The process ID may be used by the kill-process system
;;; procedure to halt the spawned process before it completes.

;; Consider returning an error string as a second value or consider using some
;; technique like last-status-message-for-file to store the error message from the
;; most recent attempt to spawn.

;; Defun-for-file-io is a misnomer -- perhaps we need something more general.

;; jh, 11/9/91.  Changed spawn-process-to-run-command-line to return a float,
;; since process IDs on VMS are too big for our fixnums.  This involves a
;; corresponding change in kill-process.

;; jh, 10/23/92.  Added ability to G2 to kill old spawned processes before the
;; G2 image exits.  Failure to do so was leaving a G2 window around when
;; processes spawned by the system procedure
;; g2-spawn-process-to-run-command-line were not killed.  Since this is
;; something novices are likely to do, we will provide this extra layer of
;; protection.

;;; jh, 12/28/95.  Moved the process-managing foreign functions to PRIMITIVES,
;;; where Telewindows can use them.

;;; The function `kill-possibly-leftover-spawned-process' must be called within
;;; a with-temporary-gensym-float-creation scope.

(defun kill-possibly-leftover-spawned-process (process-id)
  (when (or (not (eq g2-operating-system 'vms))
	    (=f (c-process_exists (managed-float-value process-id)) 1))
    (c-kill_spawned_command_line (managed-float-value process-id)))
  (reclaim-managed-float process-id))

(defmacro spawn-process-to-run-command-line-lisp-side-1
    (g2-process-namestring spawn-as-command-line-p)
  (let ((spawner
	  (if spawn-as-command-line-p
	      'c-spawn_command_line_process
	      'c-spawn_executable_process)))
    (avoiding-variable-capture (g2-process-namestring)
      `(let ((process-namestring
	       (convert-text-string-to-ascii-as-much-as-possible
		 (evaluation-text-value ,g2-process-namestring))))
	 ;; jh, 10/21/92.  The following form needs to be better abstracted (see
	 ;; intern-text-string in UTILITIES3 for a similar one), but the actual
	 ;; bug is that the foreign function interface can only pass simple
	 ;; strings to C.  Indeed, a comment in c-argument-types in OS-FOREIGN
	 ;; says that we don't know what will happen with strings that are not
	 ;; simple.  OS-FOREIGN should be cleaned up, but it is a waste of time
	 ;; to do this before we know what Lisp we will be using for
	 ;; development.
	 (with-temporary-gensym-float-creation spawn-process-to-run-command-line
	   (let ((process-id (,spawner process-namestring)))
	     (reclaim-evaluation-text ,g2-process-namestring)
	     (reclaim-text-string process-namestring)
	     (unless (=e -1.0 process-id)
	       (sysproc-push (allocate-managed-float process-id)
			     known-process-ids?))
	     (make-evaluation-float process-id)))))))
      
(defun-for-file-io spawn-process-to-run-command-line-lisp-side
		   (g2-process-namestring)
  (declare (keeps-g2-local-variables-valid nil)) ; Locals always valid?  Playing
					         ; it safe for now. - cpm, 5/29/95
  (spawn-process-to-run-command-line-lisp-side-1 g2-process-namestring t))

(defun-for-file-io spawn-process-with-arguments-lisp-side
		   (g2-process-namestring)
  (declare (keeps-g2-local-variables-valid nil)) ; Locals always valid?  Playing
					         ; it safe for now. - cpm, 5/29/95
  (spawn-process-to-run-command-line-lisp-side-1 g2-process-namestring nil))




;;; SPAWN-REMOTE-PROCESS system procedure

;;; The functions `spawn-remote-process-lisp-side' and
;;; `g2-handle-spawn-remote-process-reply' together implement the system
;;; procedure spawn-remote-process.  Both are necessary because getting the
;;; status of the spawn attempt requires a round trip.
;;; Spawn-remote-process-lisp-side sends an ICP message to the remote process
;;; requesting the spawn, and returns a transient float-parameter that will hold
;;; the process ID.  On the G2 side, the system procedure waits for the
;;; parameter to receive a value, which is placed there by
;;; g2-handle-spawn-remote-process-reply when it handles the ICP message that
;;; transmits the process ID of the spawned process.  A non-positive process ID
;;; means that the attempt failed.

(def-hash-table sysproc-continuation-hashtable
    :constructor    make-sysproc-continuation-hashtable
    :accessor       get-sysproc-continuation
    :key-comparitor eql
    :size           131 ; use a prime number
    :use-binary-tree t
    )

(defvar sysproc-continuation-table (make-sysproc-continuation-hashtable))

(defvar highest-remote-spawn-index 0)

(defvar used-remote-spawn-indices? nil)

(defun-simple get-new-remote-spawn-index ()
  (if used-remote-spawn-indices?
      (sysproc-pop used-remote-spawn-indices?)
      (incff highest-remote-spawn-index)))

(defun-simple get-remote-process-problem-symbol-if-any
    (g2-window spawn-as-executable-p)
  (let ((gensym-window? (get-gensym-window-for-g2-window g2-window)))
    (unless gensym-window?
      (return-from get-remote-process-problem-symbol-if-any
	'no-internal-window))
    (unless (if spawn-as-executable-p
		(window-supports-this-icp-window-protocol-p
		  icp-window-protocol-supports-remote-executables
		  gensym-window?)
		(window-supports-this-icp-window-protocol-p
		  icp-window-protocol-supports-remote-processes
		  gensym-window?))
      (return-from get-remote-process-problem-symbol-if-any
	'remote-processes-unsupported)))
  (let ((icp-socket-of-window? (get-icp-socket-for-g2-window g2-window)))
    (unless icp-socket-of-window?
      (return-from get-remote-process-problem-symbol-if-any
	'not-a-remote-process)))
  (return-from get-remote-process-problem-symbol-if-any nil))

(defun-simple clean-up-sysproc-continuation (completion-form)
  (let ((remote-spawn-index (second completion-form)))
    (setf (get-sysproc-continuation
	    remote-spawn-index
	    sysproc-continuation-table)
	  nil)
    (sysproc-push remote-spawn-index used-remote-spawn-indices?)
    (reclaim-sysproc-list completion-form)))

(defmacro spawn-remote-process-lisp-side-1
    (g2-process-namestring g2-window spawn-as-command-line-p)
  (let ((message-to-spawn
	  (if spawn-as-command-line-p
	      'send-icp-spawn-remote-process
	      'send-icp-spawn-remote-executable))
	(check-executable-version-p (not spawn-as-command-line-p)))
    (avoiding-variable-capture (g2-process-namestring g2-window)
      `(let ((problem-symbol?
	       (or (and (not (of-class-p ,g2-window 'g2-window))
			'remote-process-procedure-requires-g2-window)
		   (get-remote-process-problem-symbol-if-any
		     ,g2-window
		     ,check-executable-version-p))))
	 (cond
	   (problem-symbol?
	    (reclaim-evaluation-text ,g2-process-namestring)
	    (make-evaluation-symbol problem-symbol?))
	   (t (let ((code-body-invocation-to-receive-spawn-status
		      current-computation-instance)
		    (icp-socket-of-window ;known non-nil from above
		      (get-icp-socket-for-g2-window ,g2-window))
		    (process-namestring
		      (prog1 (convert-text-string-to-ascii-as-much-as-possible
			       (evaluation-text-value ,g2-process-namestring))
			(reclaim-evaluation-text ,g2-process-namestring)))   
		    (remote-spawn-index (get-new-remote-spawn-index)))
		(setf (get-sysproc-continuation
			remote-spawn-index
			sysproc-continuation-table)
		      code-body-invocation-to-receive-spawn-status)
		(install-code-body-invocation-completion-form
		  code-body-invocation-to-receive-spawn-status
		  (sysproc-list
		    'clean-up-sysproc-continuation
		    remote-spawn-index))
		(writing-icp-message-group
		    ((icp-output-port icp-socket-of-window))
		  (,message-to-spawn
		     remote-spawn-index
		     process-namestring))
		(reclaim-text-string process-namestring)
		(make-evaluation-symbol 'remote-spawn-initiated))))))))

(defun-for-file-io spawn-remote-process-lisp-side
    (g2-process-namestring g2-window)
  (declare (keeps-g2-local-variables-valid nil)) ; Locals always valid?  Playing
					         ; it safe for now. - cpm, 5/29/95
  (spawn-remote-process-lisp-side-1 g2-process-namestring g2-window t))

;;; The system procedure `g2-spawn-remote-process-to-run-command-line' is simply
;;; an alias for g2-spawn-remote-process, with a less concise but more
;;; informative name.

(defun-for-file-io g2-spawn-remote-process-to-run-command-line-lisp-side
    (g2-process-namestring g2-window)
  (declare (keeps-g2-local-variables-valid nil)) ; Locals always valid?  Playing
					         ; it safe for now. - cpm, 5/29/95
  (spawn-remote-process-lisp-side-1 g2-process-namestring g2-window t))

(defun-for-file-io spawn-remote-process-with-arguments-lisp-side
    (g2-process-namestring g2-window)
  (declare (keeps-g2-local-variables-valid nil)) ; Locals always valid?  Playing
					         ; it safe for now. - cpm, 5/29/95
  (spawn-remote-process-lisp-side-1 g2-process-namestring g2-window nil))

(defun-void g2-handle-spawn-remote-process-reply
    (remote-spawn-index process-id)
  (let ((sysproc-continuation?
	  (get-sysproc-continuation
	    remote-spawn-index
	    sysproc-continuation-table)))
    (when sysproc-continuation?
      (setf (code-body-invocation-local-name-value
	      sysproc-continuation?
	      'process-id)
	    process-id)
      (wake-up-code-body-invocation sysproc-continuation?))))





;;; PROCESS-EXISTS system procedure

;;; Given a float representing process ID (such as that produced by the
;;; spawn-process-to-run-command-line system procedure), returns an integer
;;; status code.  This code is 1 if the process exists, 0 if the process does
;;; not exist, or -1 if an error occurred during the attempt to determine
;;; whether or not the process exists.

(defun-for-file-io process-exists-lisp-side (g2-process-id)
  (with-temporary-gensym-float-creation process-exists
    (let ((process-id (evaluation-float-value g2-process-id)))
      (reclaim-evaluation-float g2-process-id)
      (let ((return-status (c-process_exists process-id)))
	(case return-status
	  (0 (make-evaluation-integer 0))
	  (1 (make-evaluation-integer 1))
	  (otherwise (make-evaluation-integer -1)))))))





;;; REMOTE-PROCESS-EXISTS system procedure

;;; The functions `remote-process-exists-p-lisp-side' and
;;; `g2-handle-remote-process-exists-p-reply' together implement the system
;;; procedure remote-process-exists.  Both are necessary because getting the
;;; status of the attempt requires a round trip.
;;; Remote-process-exists-lisp-side sends an ICP message to the remote process
;;; requesting the test, and returns a transient integer-parameter representing
;;; the status of the attempt.  On the G2 side, the system procedure waits for
;;; the parameter to receive a value, which is placed there by
;;; g2-handle-remote-process-exists-p-reply when it handles ICP message that
;;; transmits the status of the existence test.  A status of 1 means the process
;;; definitely exists, a status of 0 means the process definitely does not
;;; exist, and a negative status means that the attempt failed.
  
(defun-for-file-io remote-process-exists-lisp-side (g2-process-id g2-window)
  (declare (keeps-g2-local-variables-valid nil)) ; Locals always valid?  Playing
					         ; it safe for now. - cpm, 5/29/95
  (let ((problem-symbol?
	  (or (and (not (of-class-p g2-window 'g2-window))
		   'remote-process-procedure-requires-g2-window)
	      (get-remote-process-problem-symbol-if-any g2-window nil))))
    (cond
      (problem-symbol?
       (reclaim-evaluation-float g2-process-id)
       (make-evaluation-symbol problem-symbol?))
      (t (let ((code-body-invocation-to-receive-query-status
		 current-computation-instance)
	       (icp-socket-of-window ;known non-nil from above
		 (get-icp-socket-for-g2-window g2-window))
	       (remote-query-index (get-new-remote-spawn-index)))
	   (setf (get-sysproc-continuation
		   remote-query-index
		   sysproc-continuation-table)
		 code-body-invocation-to-receive-query-status)
	   (install-code-body-invocation-completion-form
	     code-body-invocation-to-receive-query-status
	     (sysproc-list
	       'clean-up-sysproc-continuation
	       remote-query-index))
	   (writing-icp-message-group ((icp-output-port icp-socket-of-window))
	     (send-icp-remote-process-exists-p
	       remote-query-index
	       g2-process-id))
	   (reclaim-evaluation-float g2-process-id)
	   (make-evaluation-symbol 'remote-query-initiated))))))

(defun-void g2-handle-remote-process-exists-p-reply
    (remote-query-index process-status)
  (let ((sysproc-continuation?
	  (get-sysproc-continuation
	    remote-query-index
	    sysproc-continuation-table)))
    (when sysproc-continuation?
      (setf (code-body-invocation-local-name-value
	      sysproc-continuation?
	      'query-status)
	    process-status)
      (wake-up-code-body-invocation sysproc-continuation?))))





;;; KILL-PROCESS system procedure

;;; Given a float representing process ID (such as that produced by the
;;; spawn-process-to-run-command-line system procedure), terminates that process
;;; and its children.  Returns true if the kill signal was issued successfully,
;;; false otherwise.

;;; Note that successfully issuing a kill signal may or may not result in the
;;; process actually disappearing.  We should consider providing the users with
;;; some way to check the process table to be sure the process is really gone.
;;; The most elegant solution would be to represent processes as transient
;;; objects, much like g2-streams.  In the meantime, a workaround might be to
;;; spawn a command line to dump ps to a file and then parsing the file using the
;;; file I/O system procedures.

;; Defun-for-file-io is a misnomer -- perhaps we need something more general.

;; jh, 11/9/91.  Changed kill-process to return a float, since process IDs on VMS
;; are too big for our fixnums.  This involves a corresponding change in
;; spawn-process-to-run-command-line.

;; jh, 10/23/92.  Modified kill-process-lisp-side to remove the process ID from
;; known-process-ids?.  For further details, see
;; spawn-process-to-run-command-line-lisp-side above.

;; lgibson, 3/4/98. The reclaim of the pid from
;; known-process-ids? should occur whether or not the kill
;; was successful. For example, a process could already have
;; terminated, unknown to G2 until this point. Users are
;; told to run the g2-kill-process system procedure to
;; reclaim the memory.

(declare-system-procedure-function kill-process-lisp-side nil)

(defun kill-process-lisp-side (g2-process-id)
  (with-temporary-gensym-float-creation kill-process
    (let ((process-id
	    (evaluation-float-value g2-process-id)))
      (reclaim-evaluation-float g2-process-id)
      (if (=e process-id 0.0)
	  (copy-evaluation-truth-value evaluation-false-value)
	  (let ((return-status
		  (c-kill_spawned_command_line process-id)))
	    (let ((first-known-process-id? (first known-process-ids?)))
	      ;; jh, 3/25/93.  First-known-process-id?  could be NIL when
	      ;; c-kill_spawned_command_line() returns a success status
	      ;; despite the fact that the process does not exist.  This
	      ;; happens on the VAX, since no error checking is available
	      ;; there.
	      (when first-known-process-id?
		(cond ((=e (managed-float-value first-known-process-id?)
			   process-id)
		       (reclaim-managed-float first-known-process-id?)
		       (sysproc-pop known-process-ids?))
		      (t (loop for process-id-cons on known-process-ids?
			       for known-process-id in (rest known-process-ids?)
			       when (=e (managed-float-value known-process-id)
					process-id)
			       do (reclaim-managed-float known-process-id)
			       (setf (cdr process-id-cons)
				     (cddr process-id-cons))
			       (loop-finish))))))
	    (cond 
	      ((=f return-status 0)
	       (copy-evaluation-truth-value evaluation-true-value))
	      (t (copy-evaluation-truth-value evaluation-false-value)))))))
      )

;; jh, 11/13/92.  Can't use defun-for-file-io for kill-process-lisp-side in
;; Chestnut because this abstraction uses defun-allowing-unwind.  This conflicts
;; with the use of managed-float-value, which creates a C raw double, which it
;; is forbidden to temp.  (Temps must be of Chestnut Lisp type Object, not C
;; type double.) So, changed defun-for-file-io to a combination of
;; declare-funcallable-symbol and regular defun.




;;; KILL-REMOTE-PROCESS system procedure

;;; The functions `kill-remote-process-lisp-side' and
;;; `g2-handle-kill-remote-process-reply' together implement the system
;;; procedure kill-remote-process.  Both are necessary because getting the
;;; status of the attempt requires a round trip.
;;; Kill-remote-process-lisp-side sends an ICP message to the remote process
;;; requesting the kill, and returns a transient integer-parameter representing
;;; the status of the attempt.  On the G2 side, the system procedure waits for
;;; the parameter to receive a value, which is placed there by
;;; g2-handle-kill-remote-process-reply when it handles ICP message that
;;; transmits the status of the kill attempt.  A status of 1 means the process
;;; definitely exists, a status of 0 means the process definitely does not
;;; exist, and a negative status means that the attempt failed.
  
(defun-for-file-io kill-remote-process-lisp-side
    (g2-process-id g2-window)
  (declare (keeps-g2-local-variables-valid nil)) ; Locals always valid?  Playing
					         ; it safe for now. - cpm, 5/29/95
  (let ((problem-symbol?
	  (or (and (not (of-class-p g2-window 'g2-window))
		   'remote-process-procedure-requires-g2-window)
	      (get-remote-process-problem-symbol-if-any g2-window nil))))
    (cond
      (problem-symbol?
       (reclaim-evaluation-float g2-process-id)
       (make-evaluation-symbol problem-symbol?))
      (t (let ((code-body-invocation-to-receive-kill-status
		 current-computation-instance)
	       (icp-socket-of-window ;known non-nil from above
		 (get-icp-socket-for-g2-window g2-window))
	       (remote-kill-index (get-new-remote-spawn-index)))
	   (setf (get-sysproc-continuation
		   remote-kill-index
		   sysproc-continuation-table)
		 code-body-invocation-to-receive-kill-status)
	   (install-code-body-invocation-completion-form
	     code-body-invocation-to-receive-kill-status
	     (sysproc-list
	       'clean-up-sysproc-continuation
	       remote-kill-index))
	   (writing-icp-message-group ((icp-output-port icp-socket-of-window))
	     (send-icp-kill-remote-process
	       remote-kill-index
	       g2-process-id))
	   (reclaim-evaluation-float g2-process-id)
	   (make-evaluation-symbol 'remote-kill-initiated))))))

(defun-void g2-handle-kill-remote-process-reply
    (remote-kill-index process-status)
  (let ((sysproc-continuation?
	  (get-sysproc-continuation
	    remote-kill-index
	    sysproc-continuation-table)))
    (when sysproc-continuation?
      (setf (code-body-invocation-local-name-value
	      sysproc-continuation?
	      'kill-status)
	    process-status)
      (wake-up-code-body-invocation sysproc-continuation?))))




;;; GET-COMMAND-LINE-ARGUMENT-FROM-LAUNCH

;;; Given an integer, returns the 0-indexed element at that position in the
;;; command line that launched G2.  If this element does not exist, or if there
;;; was any other problem, get-command-line-argument-from-launch returns the empty
;;; string.

;;; filters the string, removing any non-gensym characters, via
;;; copy-string-filtering-out-non-gensym-characters.  This is to prevent
;;; customers from crashing G2 by entering, e.g., Kanji characters as the
;;; '-name' command line argument.  Such characters should still be passed to
;;; the window system for use as the title of the window, but they will be
;;; elided from the string returned by get-command-line-argument-from-launch.
;;; -ncc, 17 Jan 1995 

(defun-for-file-io get-command-line-argument-from-launch-lisp-side 
		   (g2-argument-index)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((argument-index 
	   (evaluation-integer-value g2-argument-index))
	 (command-line-argument? ;cached, not reclaimable.
	   (and (>=f argument-index 0)
		(get-gensym-command-line-argument argument-index))))
    (reclaim-evaluation-integer g2-argument-index)
    (if command-line-argument?
	(let* ((filtered-command-line-argument
		 (import-text-string
		   command-line-argument? 'USER-COMMAND-LINE-ARGUMENT)
		 ;; Now goes through the text import facility, which better
		 ;; parameterizes the translation behavior. (MHD 2/27/96)
;		 (copy-string-filtering-out-non-gensym-characters command-line-argument?)
		 )
	       (result (make-evaluation-text filtered-command-line-argument)))
	  (reclaim-text-string filtered-command-line-argument)
	  (prog1 (make-evaluation-text result) ; extra copy, but fixed to use 
	    (reclaim-text-string result)))     ;   the proper interface
	(make-evaluation-text ""))))





;;; GET-HOST-NAME

;;; Returns the host name as a text-string, or the empty text string if
;;; any problem occurred.

(defun-for-file-io get-host-name-lisp-side ()
  (declare (keeps-g2-local-variables-valid t))
  (let ((host-name? (get-local-host-name))) ;cached, not reclaimable
    (if host-name?
	(make-evaluation-text host-name?)
	(make-evaluation-text ""))))




;;; GET-PORT-NUMBER-OR-NAME
;;; GET-PORT-NUMBER-OR-NAME-GIVEN-INDEX

;;; Get-port-number-or-name-given-index returns the port number or name of the
;;; index'th transport as a text-string, or the empty text-string if any problem
;;; occurred.  Index is 1-based.  Note that on UNIX systems the
;;; port-number-or-name looks like an integer, and on VMS systems it looks like
;;; a symbol, but that on either platform a text-string is returned.

;;; Get-port-number-or-name is like get-port-number-or-name-given-index, but
;;; takes no arguments and always returns the port number or name of the first
;;; transport.  It exists for backwards compatibility with G2 releases before
;;; 4.0.

(defun-for-file-io get-port-number-or-name-lisp-side ()
  (declare (keeps-g2-local-variables-valid t))
  (get-port-number-or-name-given-index-lisp-side (make-evaluation-integer 1)))

(defun-for-file-io get-port-number-or-name-given-index-lisp-side (index)
  (declare (keeps-g2-local-variables-valid t))
  (if generic-listener-initialized?
      (protected-let*
          ((index-value
	     (1-f (evaluation-integer-value index)))
	   (network-addresses?
	     (get-local-host-addresses)
	     (reclaim-network-addresses network-addresses?))
	   (network-address?
	     (and (>=f index-value 0) (nth index-value network-addresses?))))
	(reclaim-evaluation-integer index-value)
	(if network-address? 
	    (make-evaluation-text (second network-address?))
	    (make-evaluation-text "")))
      (make-evaluation-text "")))


(defun-for-file-io get-network-addresses-lisp-side ()
  (declare (keeps-g2-local-variables-valid t))
  (let* ((buffer-size 300)
	 (buffer
	   (obtain-simple-gensym-string buffer-size))
	 (address-list
	   (loop for i from 0
		 as len = (get-nth-network-address i buffer buffer-size)
		 while (>=f len 0)
		 as address = (copy-partial-text-string buffer len)
		 collect address into addresses using eval-cons 
		 finally
		   (return (allocate-evaluation-sequence addresses)))))
    (reclaim-gensym-string buffer)
    address-list))



;;; GET-NETWORK-TYPE-GIVEN-INDEX
;;; GET-NETWORK-TYPE

;;; Get-network-type-given-index returns the network type of the index'th
;;; transport as a text-string, or the empty text-string if any problem
;;; occurred.  Index is 1-based.  Network type must be "TCP-IP" as of 10/4/05.

;;; Get-network-type is like get-network-type-given-index but takes no arguments
;;; and always returns the network type of the first transport.  It exists for
;;; backwards compatibility with G2 releases before 4.0.


(defun-for-file-io get-network-type-lisp-side ()
  (declare (keeps-g2-local-variables-valid t))
  (get-network-type-given-index-lisp-side (make-evaluation-integer 1)))

(defun-for-file-io get-network-type-given-index-lisp-side (index)
  (declare (keeps-g2-local-variables-valid t))
  (if generic-listener-initialized?
      (protected-let*	  
          ((index-value
	     (1-f (evaluation-integer-value index)))
	   (network-addresses?
	     (get-local-host-addresses)
	     (reclaim-network-addresses network-addresses?))
	   (network-address?
	     (nth index-value network-addresses?)))
	(reclaim-evaluation-integer index-value)
	(if network-address?
	    (copy-with-underscores-changed-to-hyphens
	      (first network-address?))
	    (make-evaluation-text "")))
      (make-evaluation-text "")))




;;; GET-SOFTWARE-VERSION

;;; Returns the software version as a text-string, or the empty text string if
;;; any problem occurred.  The software version is the same as that appearing in
;;; the title block.

(defun-for-file-io get-software-version-lisp-side ()
  (declare (keeps-g2-local-variables-valid t))
  (twith-output-to-text-string
    (twrite-system-version
      (system-version current-system-name))))

;;; Returns the software version including the build identification string
;;; This is necessary to track changes in the same version of G2.

(defun-for-file-io g2-get-build-version ()
  (declare (keeps-g2-local-variables-valid t))
  (twith-output-to-text-string
    (twrite-system-version (system-version 'ab))
    (tformat " ~a" build-identification-string)))




;;; `System-version-information-as-structure' is an alternative to string-
;;; based ways of getting access to this data such as twrite-system-version.
;;; It provides a structure over strings and integers, eliminating the need
;;; to write a parser to extract the information.
;;;
;;; The information is taken directly from the constants in Delta, and it
;;; does not take a version object as a parameter, which is a departure
;;; from earlier treatments, but avoids involving a parser to extract the
;;; revision and quality information which is folded into a string in
;;; version objects. (ddm 7/21/99)

(defun system-version-information-as-structure ()
  (let ((level
	  (if patch-number-of-current-gensym-product-line?
	      (make-evaluation-symbol 'patch)
	      (case release-quality-of-current-gensym-product-line
		(#.prototype-release-quality
		 (make-evaluation-symbol 'prototype))
		(#.alpha-release-quality
		 (make-evaluation-symbol 'alpha))
		(#.beta-release-quality
		 (make-evaluation-symbol 'beta))
		(#.release-quality
		 (make-evaluation-symbol 'released))
		(otherwise
		 #+development (cerror "continue"
				       "Unexpected value for release-quality: ~a"
				       release-quality-of-current-gensym-product-line)
		 (make-evaluation-symbol 'unknown-release-level))))))

    (allocate-evaluation-structure
      (eval-list
	'major-version-number major-version-number-of-current-gensym-product-line
	'minor-version-number
	(let ((minor-version minor-version-number-of-current-gensym-product-line))
	  (multiple-value-bind (floor rem)
	      (floorf minor-version 10)
	    (if (=f rem 0) floor minor-version)))
	'revision revision-number-of-current-gensym-product-line
	'release-level level
	'patch-number (or patch-number-of-current-gensym-product-line?
			  (make-evaluation-boolean-value nil))
	'build-identification (copy-as-wide-string build-identification-string)
	'build-comment (if (null build-comment-string)
			   (make-evaluation-boolean-value nil)
			   (copy-as-wide-string build-comment-string))
	'enterprise (make-evaluation-boolean-value *is-g2-enterprise?*)))))


;;; Returns the software version as a structure rather than a string.
;;; The build identification number is included.

(defun-for-file-io g2-get-version ()
  (declare (values structure)
	   (keeps-g2-local-variables-valid t))
  (system-version-information-as-structure))

(defun-for-system-procedure g2-get-tw-version (g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (icp-window-p gensym-window)
      (stack-error cached-top-of-stack "~NF is not a remote gensym-window" gensym-window))
    (let* ((icp-socket (icp-socket-for-gensym-window? gensym-window))
           (revision (get-remote-icp-version-info-value
                       icp-socket 'revision-number-of-current-gensym-product-line 0))
           (build-identification (copy-as-wide-string
                                   (get-remote-icp-version-info-value
                                     icp-socket 'build-identification-string #w""))))
      (allocate-evaluation-structure
        (eval-list
          'major-version-number (remote-icp-major-version icp-socket)
          'minor-version-number (remote-icp-minor-version icp-socket)
          'revision  revision
          'build-identification build-identification)))))

;;; UNIX-TIME

;;; Supposed to return the current time, in the local time zone, in UNIX format,
;;; i.e., seconds since January 1, 1970 GMT, as a float.  Actually is stubbed
;;; out to always return 0.0.  This system procedure should not be used.

(defun-for-file-io unix-time-lisp-side ()
  (declare (keeps-g2-local-variables-valid t))
  (with-temporary-gensym-float-creation unix-time
    (make-evaluation-float (gensym-get-unix-time))))




;;; UNIX-TIME-AT-START

;;; Returns the latest time G2 was started in UNIX format, i.e., seconds since
;;; January 1, 1970 GMT as a float.

(defun-for-file-io unix-time-at-start-lisp-side ()
  (declare (keeps-g2-local-variables-valid t))
  (with-temporary-gensym-float-creation unix-time-at-start
    (make-evaluation-float 
      (convert-gensym-time-to-unix-time
	(clock-get gensym-time-at-start)))))





;;; LOCAL-TIME

;;; Returns the current time in seconds since January 1, 1970, in the
;;; current time zone.

(defun-for-file-io local-time-lisp-side ()
  (declare (keeps-g2-local-variables-valid t))
  (with-temporary-gensym-float-creation local-time
    (make-evaluation-float (gensym-get-local-time))))

(defun-for-file-io is-dst-used-lisp-side()
  (declare (keeps-g2-local-variables-valid t))
  (if (/=f (c-g2ext-is-dst-used) 0)
	  (make-evaluation-truth-value truth)
          (make-evaluation-truth-value falsity)))

;;; UNIX-TIME-TO-TEXT

;;; Converts a UNIX-format timestamp (a float) to a text-string, as if by the "as
;;; a timestamp" formatter (print-constant in GRAMMAR0).  The argument
;;; use-seconds-p is a truth value and indicates whether or not the formatted text
;;; string will contain seconds after the hour and minute.

;; jh, 9/11/91.  Mark tells me that we no longer adhere to the Chicago Manual of
;; Style as far as "a.m." versus "p.m" versus "M".  We simply follow this
;; consensus:
;;   "a.m" for times in the semi-closed interval [12:00 Midnight, 12:00 Noon)
;;   "p.m" for times in the semi-closed interval [12:00 Noon, 12:00 Midnight)

(defun-for-file-io unix-time-to-text-lisp-side (unix-time use-seconds)
  (declare (keeps-g2-local-variables-valid t))
  (unix-time-to-text-internal unix-time use-seconds nil))


(defun-for-file-io unix-time-to-text-y2k-lisp-side (unix-time use-seconds)
  (declare (keeps-g2-local-variables-valid t))
  (unix-time-to-text-internal unix-time use-seconds t))


(defun unix-time-to-text-internal (unix-time use-seconds use-4-digit-year)
  (with-temporary-gensym-float-creation unix-time-to-text
    (let ((use-seconds-p (evaluation-truth-value-is-true-p use-seconds))
	  (unix-time-float (evaluation-float-value unix-time)))
      (declare (type gensym-float unix-time-float))
      (when (and (windows-platform-p)
		 (<e unix-time-float 0.0d0))
	(stack-error cached-top-of-stack
		     "Currently Windows NT platforms cannot display time values before January 1, 1970 in text form. Unix-time should be no less than 0.0. "))

      (multiple-value-bind (seconds minute hour date month year day-of-week
				    daylight-savings-time-p time-zone)
	  (gensym-decode-unix-time unix-time-float)
	(declare (ignore day-of-week daylight-savings-time-p time-zone))
	(reclaim-evaluation-float unix-time)
	(reclaim-evaluation-truth-value use-seconds)

	;; this needs to be internationalized
	(twith-output-to-text-string
	  (if use-4-digit-year
	      (tformat "~d/~d/~d" month date year)
	      (let ((simple-year (modf-positive year 100)))
		(tformat (if (>f simple-year 9)
			     "~d/~d/~d"
			     "~d/~d/0~d")
			 month date simple-year)))
	  (tformat " ")
	  (tformat "~d:"
		   (case hour
		     ((0 12) 12)
		     (otherwise (modf-positive hour 12))))
	  (when (<f minute 10)
	    (tformat "0"))
	  (tformat "~d" minute)
	  (when use-seconds-p
	    (tformat ":")
	    (when (<f seconds 10)
	      (tformat "0"))
	    (tformat "~d" seconds))
	  (tformat " ")
	  (if (>=f hour 12) 
	      (tformat "p.m.")
	      (tformat "a.m.")))))))



(defun-for-file-io g2-get-environment-variable (variable-name-string)
  (declare (keeps-g2-local-variables-valid t))
  (let ((value
	  (get-gensym-environment-variable variable-name-string)))
    (if value
	(values
	  (make-evaluation-text value)
	  (make-evaluation-boolean-value t))
	(values
	  (make-evaluation-text #w"")
	  (make-evaluation-boolean-value nil)))))
    
(defun-for-system-procedure get-process-identifier ()
  (declare (values float))
  (c-get-process-identifier))




;;;; Undocumented or Development-only System Procedures

;; jh, 6/3/96.  Comment in filestring-names-real-directory-p-lisp-side and
;; translate to resolve certain platform-specific file I/O problems.

;(defun-for-system-procedure filestring-names-real-directory-p-lisp-side
;    (g2-filestring)
;  (prog1 (if (filestring-names-real-directory-p g2-filestring)
;	     (copy-evaluation-truth-value evaluation-true-value)
;	     (copy-evaluation-truth-value evaluation-false-value))
;    (reclaim-text-string g2-filestring)))

#+development
(defun-for-system-procedure test-icp-tree (g2-to-g2-interface)
  (let* ((icp-socket (icp-socket-of-interface-object g2-to-g2-interface))
	 (icp-port (icp-output-port icp-socket)))
    (writing-icp-message-group (icp-port)
      (send-icp-test-icp-tree icp-tree-for-test icp-tree-for-test-2))))

