;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module INT0

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson, Mark H. David, et al.

;; jh, 12/29/94.  Split from INT1 as part of the GSI-trimming project.








;;;; Forward References in INT0

(declare-forward-references (:suppress-module-checks-for gsi)
  ;; The following references to SEQUENCES2 are necessary because Lucid/Sun4
  ;; doesn't do the right thing with an eval-when embedded in a progn.
  (run-gsi-for-recursive-descent                   function SEQUENCES2)
  (run-gspan-for-recursive-descent                 function SEQUENCES2)
  (run-icp-for-recursive-descent                   function SEQUENCES2)
  (run-gfi-for-recursive-descent                   function SEQUENCES2)
  (run-kfep-for-recursive-descent                  function SEQUENCES2)
  (run-runtime-option-for-recursive-descent        function SEQUENCES2)
  (run-restricted-use-option-for-recursive-descent function SEQUENCES2)
  (run-embedded-option-for-recursive-descent       function SEQUENCES2)
  (run-chinese-for-recursive-descent              function SEQUENCES2)
  (run-japanese-for-recursive-descent              function SEQUENCES2)
  (run-korean-for-recursive-descent                function SEQUENCES2)
  (run-nupec-for-recursive-descent                 function SEQUENCES2)
  (run-g1-for-recursive-descent                    function SEQUENCES2)
  (run-jl-for-recursive-descent                    function SEQUENCES2)
  (run-jp-for-recursive-descent                    function SEQUENCES2)
  (run-al-for-recursive-descent                    function SEQUENCES2)
  (run-ent-for-recursive-descent                   function SEQUENCES2))






;;;; PRINCIPLES of the Security System

;; Moved here from SEQUENCES2.  -pto 01mar90


;;; Any G2 system is either `secure' or `open'. This is determined at the time the
;;; G2 process authorizes itself (except for the "site manager password" as noted
;;; below). Being open or secure is a G2 image specific condition as is
;;; authorization, and is not window specific. (Note that these are process specific
;;; for any non-Lisp machine, but pertain to the whole machine for a Lisp machine.)

;;; In an open system, any person may log in without needing to supply a password,
;;; and any user may enter any mode.

;;; In a secure system, login is restricted to previously authorized users
;;; (except for the "site manager" noted below). A user must have a password and
;;; supply it to log in, and may not enter a mode unless previously authorized.

;;; The security information rests in authorized-user frames which are described
;;; below.  Each such contains the name(s) of a user, a derived version of the
;;; user's password, and a list of authorized modes for the user. These generally
;;; reside in the ok file, but there are exceptions for on-line extension of
;;; privileges.

;;; The focal point of security is that only a person trusted with site management
;;; privileges is permitted to see or modify the security data.  This is only
;;; accomplished by using the site manager login method.  

;;; When a secure G2 comes up and authorizes itself, all workstations are initially
;;; in the logged-out state.  They are therefore put into modal context which the
;;; only option is to log in.  This can only be done by an authorized user who supplies
;;; his password and a user mode for which he is authorized.  During this modal
;;; context, the user mode is conceptually "undefined" and should not be looked at.
;;; And while this is true, the workstation is in the logging-in state.

;;; Logout puts the workstation again into logged-out state, and hides (or deletes if
;;; temporary) all workspaces that are visible.

;;; Login when not logged out changes the user, changes the mode to the user's
;;; default, and does not hide or delete workspaces.

;;; Only when (1) a user has logged in using the site manager password, and (2) G2
;;; is secure, may that user
;;;
;;;   (1) create a new authorized-user from a menu choice;
;;;   (2) get a table for an authorized-user; and
;;;   (3) have the make-g2-secure? slot displayed on any new attribute tables
;;;       created to represent an OK object

;;; The `site manager password' (aka the `backdoor password') is a password
;;; furnished by Gensym which is a function of the local machine ID. It is supplied
;;; to the authorized `site manager' at the same time that the authorizing codes are
;;; supplied. While the site manager may wish to make the codes known to many people,
;;; this password should be kept private.

;;; When the correct site manager password is used to log into a G2, the immediate
;;; effect is to make the G2 secure and to enter a special quasi-mode (orthogonal
;;; to user mode) is entered in which the user may do the security modifying things
;;; mentioned above as 1-3.  This user is then free to edit the ok file in any way
;;; he wishes, controlling the privileges of users.  The first thing he should do
;;; is to make an authorized-user for himself, make up a password, and authorize
;;; himself to be an administrator.

;;; The site manager may create users, assign or change their passwords, change
;;; their modes, etc.  These changes take place immediately while editing, and
;;; on any future load of the OK file.  Note that an authorized user may have
;;; several names.  A name should not be used for more than one authorized user.
;;; If this is done, the usual warning is placed on the frame, and the password
;;; and modes associated with that name may depend on the last authorized-user
;;; edited or loaded.

;;; The login should have the password be typed without echoing.

;; Review "blob" echoing method!  Note that it may reveal the length of passwords
;; on the screen.  Consider requiring passwords of a certain minimum length or
;; allowing administrators to require that of them.  Consider similarly having
;; various other requirements of passwords for security, e.g. min. length, all
;; diff. chars, different from user name, etc.  See HP-UX, which does some of
;; this, for inspiration.  (MHD 2/26/90)

;;; The only way to change the password of a user is for the site manager to do
;;; it.  Note that the slot writer produces a blank field, and that the stored
;;; content is encoded in a non-obvious way, but that the password is visible in
;;; the editor at the moment of editing the slot.  Note that there is currently
;;; no way to recover the password once it has been entered because its only
;;; stored representation is via a function that we do not know how to invert
;;; readily.
;; [I SUGGEST ADDING THE FOLLOWING. -mhd]
;; It is, in fact, designed to be uninvertible, but, lacking a
;; mathematical proof to that effect, we cannot absolutely say that it is; if
;; a method to invert this function (or even the possibility of one) were
;; discovered, we would be obliged to change the scheme and probably to notify
;; users of such a development.

;;; The site manager may change permission for a user:
;;;   (1) By modifying the ok, and saving it out. This affects each machine using
;;;       that KB at the time G2 is created. (It is also possible to load an OK
;;;       while running, but may not be desirable.)
;;;   (2) The site manager may enter may create an authorized-user and edit it
;;;       even while on-line. This is a temporary expedient.  Clearly, the
;;;       future should have some network solution.
;; [I did not quite understand the point of (2) above; could ML clarify? -mhd]

;; For KB developers, toggling between two modes is a pain in the ass. Perhaps we
;; should implement a simple toggle (keystroke) to go back and forth between the
;; last two modes (assuming them to be authorized).





;;;; Authorization

;;; All Authorization Material previously in FORMATS follows:





(eval-when (:compile-toplevel :load-toplevel :execute)

(defparameter format-structure-description
                                     (list nil nil nil nil nil nil
					   nil nil nil nil (list 0)
					   nil (list nil) 0
					   nil   ; added (MHD 1/31/95)
					   nil)) ; ddm 7/15/98

(defparameter format-redefinition-list '(structure description))

;; Note by Ml to self. 1/10/91 This is a poor way of referencing 
;; format-structure-description. Better to have a merged list, and 
;; not call intern-text-string which pointed C Marcant directly to
;; the more secret portions of the code.

;; The variable format-structure-description needs to have its symbol retained for
;; runtime use in Chestnut.  Note that the translation techniques for Lisp
;; variables used by Chestnut does a pretty good job of "hiding" the variable,
;; since the translation contains no Lisp symbol at all for the variable, unless
;; explicitly asked for.  Given this, it would probably be better for us to get
;; rid of the "intern and symbol-value" method of referencing the variable, and
;; just use it in-line.  This will give a C variable (which is difficult to detect
;; in optimized C code), and will not produce a Lisp variable (which can be easy
;; to detect.) Please review this, Michael!  -jra 3/17/91

;; jh, 10/6/91.  Changed the default number of processes in
;; format-structure-description to be 0.  Having the default be nil (which equates
;; to unlimited processes after authorization) was considered too dangerous.

(declare-symbol-value-preservation format-structure-description)



(defparameter end-of-recovery-list
	(cons nil (cons nil (nthcdr 10 format-structure-description))))

(defparameter local-recovery-list
	(cons nil (cons nil (nthcdr 12 format-structure-description))))



)

(defparameter within-side-limits (list 34))










(defvar unevaluated-expression
	#+unrestricted t
	#-unrestricted within-side-limits)





(def-system-variable control-sequence-record sequences2 nil nil t)




;;; g2-authorized-p is true if the g2 process has ever been authorized. (On
;;; Lisp Machines, if the machine has been authorized since the last boot.)
;;; It controls the menu choice save-kb, and service-workstations. It also
;;; controls the menu choices for start, restart, and resume, BUT NOT the
;;; execution of these commands.

(defmacro g2-authorized-p ()
  '(neq unevaluated-expression within-side-limits))



;;; g2-still-authorized-p is true if G2 has been authorized, and that
;;; authorization has not expired. It controls the menu choices for
;;; creating new workspaces, and many menu picks for new items.

(defmacro g2-still-authorized-p ()
  '(and (g2-authorized-p)
	(let ((expiration? (fourth end-of-recovery-list)))
	  (if (and expiration? (typep expiration? 'fixnum))
	      (>=f expiration? (get-universal-date))
	      t))))


;;; ok-to-run-g2? controls the execution of start, restart and resume. If
;;; it rejects the execution, then warn-upon-start-or-resume is called.

(defmacro ok-to-run-g2? ()
  '(and (g2-still-authorized-p)	
	(loop with authorized-package-list = (third local-recovery-list)
	      with today = (get-universal-date)
	      for (existing-package . nil) in control-sequence-record
	      for (package-name nil nil nil start-date? end-date?) =
		  (assq existing-package authorized-package-list)
	      always
		(and package-name
		     (if start-date?
			 (<=f start-date? today end-date?)
			 t)))))

;; jh, 10/14/94.  Changed g2-authorized-p call to g2-still-authorized-p in
;; ok-to-run-g2?, since otherwise, users can start, pause, and restart G2 after
;; a temporary license has expired.







;; Is t if start has been done since loading G2 into process or LISPM world.
;; When authorization is done in world saves, this will need to be reset after
;; loading the world save, and until start has been selected. Its purpose is
;; to prevent bombout before g2 has its authorization. ML, 8 Aug, 89

(defvar g2-has-been-started? nil)


(defun run-g2-initializations ()		; this could be moved elsewhere
  (progn
    #-unrestricted
    (setq unevaluated-expression within-side-limits)
;    (setq ok-to-run-g2? nil)
    ;; other things to do?
    ))


;; Devious name. Used only in this file.
(eval-when (:compile-toplevel :load-toplevel :execute)
  (defparameter old-eval-cons-list (list nil nil)))




;;; hide-constant-string produces code that results in a simple text string
;;; which is unique and contains the same elements to constant-string.  The compiled
;;; code should not contain any constant strings.  If evaluating previous-string?
;;; returns a non-nil value, then that value is returned.  Otherwise, this produces
;;; an unshared text string which the caller is responsible for reclaiming.

(defmacro hide-constant-string (constant-string &optional (previous-string? nil))
  ;; don't allow constant string to become a lisp-world constant:
  (let* ((length (length constant-string))
	 (elements
	   (concatenate
	     'list
	     (loop for i from 0 below length
		   collect (char-code (char constant-string i)))))
	 (gensym (gensym)))
    `(loop with string = (obtain-simple-text-string ,length)
	   with ,gensym = ,previous-string?
	   for i from 0 below ',length
	   as j in ',elements
	   when ,gensym
	     do (reclaim-simple-text-string string)
		(return ,gensym)
	   do (setf (schar string i) (code-char j))
	   finally (return string))))


;; This is used in CYCLES.  Should this be used in similar cases below where
;; we do intern-text-string?





;;; `Def-optional-module' is used to declare the existence of a module, e.g. GSI.

;;; The numeric codes (aka bits) are assigned here in this file and in the
;;; licensing server.  A G2 process will have some number of these bits
;;; set in it's license.  These settings will turn ON AND OFF features in the
;;; process.

;;; The effects are as follows:

;;; (1) the variable `optional-modules-map' is maintained to corelate module
;;;     names and bit encodings.  (see the licensing server for scary detail).

;;; (2) Grammar for the optional module (ought to be) created, but due to module
;;;     loading reasons it is actually done by when sequences2 is loaded.

;;; (3) <Module-name>-AUTHORIZED-P (a macro) is defined.
;;;     Its expansion is devious so that it is difficult to correlate places
;;;     where the authorization occurs, and where it is tested. This requires
;;;     a deviously named variable which points into format-structure-description.
;;;     These names are supplied by the writer of def-optional-module.
;;;     Note this macro only indicates if the bit is set, not if it is enabling
;;;     or disabling a feature.

;;; (4) <Module-name>-NOT-AUTHORIZED-WARNING-MESSAGE expands to a call to
;;;     warning-message with the appropriate warning message.  The call is a forward
;;;     reference to the macro warning-message and should be expanded only after
;;;     warning-message has been defined.

;;; (5) EXECUTE-BODY-IF-module-name-IS-AUTHORIZED, with a syntax like progn,
;;;     will generate a log book message if the user isn't sufficently authorized.
;;;     In that situation the form happens to return a NIL.

;;; (6) EXECUTE-BODY-IF-module-name-IS-AUTHORIZED-OR-PREDICATE-TRUE is like (5)
;;;     but is used in senarios where the functionality being guarded is let
;;;     thru in a few cases.  For example some strange ICP connections are allowed
;;;     even when ICP in general isn't.

;;; It is assumed that the optional modules all follow SEQUENCES2 in compilation
;;; order. module-name-AUTHORIZED-P should be used several times within the module
;;; so as to disable the functionality if not authorized. It should be done
;;; in such a way that no inconsistent states occur regardless of whether the value
;;; is true or NIL at any given evaluation. The imbedding should not be so obvious
;;; that it can easily be found.
;;;
;;; The wrappers EXECUTE-BODY-IF-xxx-IS-AUTHORIZED and EXECUTE-BODY-IF-xxx-IS-AUTHORIZED
;;; -OR-PREDICATE-IS-TRUE will always return NIL if the user is not authorized
;;; to use module xxx.  The body is wrapped around a progn, so only one value will
;;; be returned through it if the body is executed.

;; Note that the "xxx-not-authorized-warning-message" macro inside a
;; def-optional-module-form expands into a forward reference to the macro
;; "warning-message".  There is another forward reference as well, to
;; add-grammar-rule.  To avoid circularity, we complete the references in the
;; sequences2 module after everything necessary has been defined.  
;; (pto & jh, 3/8/90)

;;; The fifth (and optional) argument internal-authorized-p-macro-name? is used
;;; to specify a name for the macro that would otherwise be named
;;; module-AUTHORIZED-P. However the latter name is still used by further macros
;;; generated by def-optional-module. This feature should be used only as a
;;; basis for defining a macro with the original name which makes use of the
;;; internally named macro and adds more stuff to it.

;;; There are MANDITORY activities that must be done when ever a new
;;; def-optional-module form is added.  These include:
;;;   1. Add a forward reference to the list at the top of this module.
;;;      (see run-nupec-for-recursive-descent for example)
;;;   2. Touch sequences2, so the form that defines that function recompiles.
;;;      (see defun-strange-names-for-optional-modules)
;;;   3. Add a dummy implementation of that function in tw-patches.
;;;      (see run-nupec-for-recursive-descent for example)
;;;   4. Add a dummy implementation of that function in gsi-patches.
;;;      (see run-nupec-for-recursive-descent for example)
;;;   5. Add an entry in the licensing server's version of the data structure
;;;      sorted in user::optional-modules-map.
;;;   6. Rebuild, encrypt, etc. the licensing server, so you can generate
;;;      codes.



(eval-when (:compile-toplevel :load-toplevel :execute)

(defvar optional-modules-map nil)

(defparameter proce-eval-invoked-list nil)

(defun-for-macro make-strange-name-for-optional-module (module-name)
  (intern (format nil "RUN-~a-FOR-RECURSIVE-DESCENT" module-name) 'ab))


;; Devious name. Used only in this file.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defparameter left-recursion-limit-list (cons nil (cdr old-eval-cons-list))))

(defun-for-macro make-warning-message-macro-name-for-optional-module
    (module-name)
  (intern (format nil "~a-NOT-AUTHORIZED-WARNING-MESSAGE" module-name) 'ab))


(defmacro defun-strange-names-for-optional-modules ()
  `(progn
     (declare-forward-reference notify-engineer function)
     (declare-forward-reference break-out-of-debug-messages function)
     ,@(loop for (module-name nil devious-p) in optional-modules-map 
	     when devious-p
	       collect
		 `(defun ,(make-strange-name-for-optional-module module-name) (x y)
		    (,(make-warning-message-macro-name-for-optional-module module-name))
		    (+f x y)))))


;;; See def-optional-module documentation above the enclosing eval-when.

(defmacro def-optional-module (module-name numeric-code 
			       &key
			       (devious-name nil)
			       (invisible-module-p nil)
			       (internal-authorized-p-macro-name? nil)
			       (free-p nil))
  (let* ((authorized-p-macro-name
	   (intern (format nil "~a-AUTHORIZED-P" module-name) 'ab))
	 (tw-authorized-p-macro-name
	   (intern (format nil "TW-~a-AUTHORIZED-P" module-name) 'ab))
	 (tw-authorized-code-p-name
	   (intern (format nil "TW-~a-AUTHORIZED-CODE-P" module-name) 'ab))
	 (warning-message-macro-name
	   (make-warning-message-macro-name-for-optional-module module-name))
	 (wrapper-macro-name
	   (intern (format nil "EXECUTE-BODY-IF-~a-IS-AUTHORIZED" module-name) 'ab))
	 (disjunctive-wrapper-macro-name
	   (intern (format nil "EXECUTE-BODY-IF-~a-IS-AUTHORIZED-OR-PREDICATE-TRUE"
			   module-name) 'ab))
	 (strange-name-1
	   (make-strange-name-for-optional-module module-name))
	 (strange-name-2
	   (intern (format nil "PARSE-~a-SCHEDULE-TREE" module-name) 'ab))
	 (strange-name-for-simulation
	   (intern (format nil "CACHE-~a-SEMANTICS-GRAPH" module-name) 'ab))
	 (pushnew-statement
	   `(pushnew '(,module-name
		       ,numeric-code
		       ,(and devious-name t)
		       ,(and invisible-module-p t))
		     optional-modules-map :test 'equal))
	 (really-authorized-p-macro-name
	   (intern (format nil "~a-REALLY-AUTHORIZED-P" module-name) 'ab)))
    (if devious-name
	`(progn
	   ,pushnew-statement
	   ;; The following line is commented out because add-grammar-rule is not
	   ;; defined yet. The make up code is performed in sequences2.
;      (add-grammar-rule '(product ',module-name))
	   
	   (defvar ,devious-name)
	   (setq ,devious-name  (cons (random 20) (nth 10 format-structure-description)))

	   (defvar ,strange-name-for-simulation)
	   (let ((xxx (cons (random 999) nil)))
	     (setf (get ',module-name 'simulation-state)
		   (cons (random 99) xxx))
	     (setf ,strange-name-for-simulation
		   (cons (random 99) xxx)))
	   
	   (defmacro ,(or internal-authorized-p-macro-name?
			  authorized-p-macro-name) ()
	     '(,(if free-p 'or 'and)
	       (let ((code (second-of-long-enough-list ,devious-name)))
		 (and (fixnump code)
		      (/=f (logandf code ,numeric-code) 0)))
	       (second-of-long-enough-list ,strange-name-for-simulation)))

	   (defmacro ,really-authorized-p-macro-name ()
	     '(let ((code (second-of-long-enough-list ,devious-name)))
	        (and (fixnump code)
		     (/=f (logandf code ,numeric-code) 0))))
	   
	   (def-substitution-macro ,tw-authorized-code-p-name (code)
	     (and (fixnump code)
		  (/=f (logandf code ,numeric-code) 0)))

	   (defmacro ,tw-authorized-p-macro-name ()
	     '(let ((code (ninth (secret-get-telewindows-authorization-info))))
		(,tw-authorized-code-p-name code)))
	   
	   (defmacro ,warning-message-macro-name ()
	     '(progn
		(warning-message
		  1
		  ,(format nil "An attempt has been made to use ~a.  ~a has not been authorized ~
		        to run on this machine."
			   module-name module-name))
		nil))
	   
	   (declare-forward-reference ,strange-name-1 function)

	   (defun ,strange-name-2 ()
	     (,strange-name-1 (random 99) (random 999)))

	   (defmacro ,wrapper-macro-name
		     (&body body)
	     `(if (,',authorized-p-macro-name)
		  (progn
		    ,@body)
		  (,',strange-name-2)))

	   (defmacro ,disjunctive-wrapper-macro-name (predicate &body body)
	     `(if (or ,predicate
		      (,',authorized-p-macro-name))
		  (progn
		    ,@body)
		  (progn
		    (,',strange-name-2)
		    nil)))
	   
	   )
	pushnew-statement)))

;; jh, 7/14/94.  Added really-authorized-p-macro-name, of the form
;; <product>-really-authorized-p for those products that need to know whether or
;; not they are authorized before the kb-restrictions system table gets around
;; to properly initializing the simulated authorization data.  Currently, the
;; only product that needs this is NUPEC, because it has to set up some
;; machinery in reformat-line-from-left.


;;; `Invisible-optional-module-p' is true if product-module-name is true and has
;;; the invisible-module-p declaration.  This keeps it from appearing in the
;;; title block, even if it's authorized.

(defun invisible-optional-module-p (product-module-name)
  (fourth (assq product-module-name optional-modules-map)))



;;; The set of all optional modules.

(def-optional-module gsi                     1 :devious-name overflow-byte-count)
(def-optional-module gspan                   2 :devious-name bignum-overflow-count
		     :invisible-module-p t) ; obsolete, per Helpdesk Bug HQ-910673 "Remove GSPAN 
					    ;   from the G2 title block" (MHD 12/12/96)

(def-optional-module icp                     4 :devious-name listed-continuation-servers)
(def-optional-module gfi                     8 :devious-name gfi-list-of-converters)
(def-optional-module kfep                   16 :devious-name ring-buffer-queue-for-kfep
		     :invisible-module-p t) ;; obsolete

(def-optional-module chinese                32 :devious-name reclaim-fonts-stack) ; ddm 4/8/99

(def-optional-module runtime-option         64 :devious-name redo-saved-changes 
		     :invisible-module-p t
		     :free-p t
		     :internal-authorized-p-macro-name? runtime-option-authorized-p-internal)
(def-optional-module japanese              128 :devious-name pop-fonts-stack)
(def-optional-module nupec                 256 :devious-name journal-shutout-scan-p)
(def-optional-module restricted-use-option 512 :devious-name sparse-known-pathnames-list 
		     :free-p t
		     :invisible-module-p t) 
(def-optional-module embedded-option      1024 :devious-name learned-list-to-expedite-ui
		     :free-p t
		     :invisible-module-p t)
(def-optional-module korean               2048 :devious-name get-object-on-kb-workspace-for-item)

(def-optional-module g1 #B00000001000000000000   ; 4096
  :devious-name edit-type-alias-mapping
  :free-p t)



;;; The choice of devious name is somewhat coordinated with the 'types'
;;; used in the rpc g2-confirm-available-handles-by-type where the
;;; X-authorized-p macros for these modules are deployed.

(def-optional-module jl                   8192   ; for JavaLink (ddm 6/9/98)
  :devious-name index-of-open-windows)

(def-optional-module jp                  16384   ; for JavaLink Pro (ddm 6/9/98)
  :devious-name popup-frames-available)

(def-optional-module al                  32768   ; for ActiveXLink (ddm 6/9/98)
  :devious-name radio-button-status-flags)

(def-optional-module ent                 65536   ; for Enterprise (boris.yakovito July 2011)
  :devious-name radio-button-status-flags-1)


;; Read the doc for def-optional-module carefully when adding an additional
;; entry there, there are other actions that MUST be done in synch.


;; Packages                                   GSI ICP GFI <other>
(def-optional-module offline        #.(logior   0   0   0    0))
(def-optional-module online         #.(logior   1   4   8    0))
(def-optional-module runtime        #.(logior   1   4   8   64)) ;; runtime-option
(def-optional-module restricted-use #.(logior   1   4   8  512)) ;; restricted-use-option
(def-optional-module embedded       #.(logior   1   4   8 1024)) ;; embedded-option

)  ; end of EVAL-WHEN


;; See above, these exist so meta dot gets you here.
(def-concept gsi-authorized-p)
(def-concept gspan-authorized-p)
(def-concept icp-authorized-p)
(def-concept gfi-authorized-p)
(def-concept kfep-authorized-p)
(def-concept runtime-option-authorized-p)
(def-concept japanese-authorized-p)
(def-concept nupec-authorized-p)
(def-concept restricted-use-option-authorized-p)
(def-concept embedded-option-authorized-p)
(def-concept korean-authorized-p)
(def-concept g1-authorized-p)
(def-concept offline-authorized-p)
(def-concept online-authorized-p)
(def-concept runtime-authorized-p)
(def-concept restricted-use-authorized-p)
(def-concept embedded-authorized-p)
(def-concept jl-authorized-p)
(def-concept jp-authorized-p)
(def-concept al-authorized-p)
(def-concept chinese-authorized-p)
(def-concept ent-authorized-p)


;;; `G2-limited-to-this-license-level-or-more' is used in code that want's to
;;; fire when the license level is restricting some function.  It's easier to
;;; use correctly than direct calls on the FOO-option-authorized-p macros.

(defmacro g2-limited-to-this-license-level-or-more (kind)
  (case kind
    ;; development isn't a useful quetion to ask.
    (restricted-use
     `(or (restricted-use-option-authorized-p)
	  (runtime-option-authorized-p)
	  (embedded-option-authorized-p)))
    (runtime
     `(or (runtime-option-authorized-p)
	  (embedded-option-authorized-p)))
    (embedded
     `(embedded-option-authorized-p))
    (otherwise
     (error "Unknown G2 license level."))))


(defmacro module-authorized-p (module-var)
  (loop with case-body = nil
	for (module-name nil devious-p invisible-module-p) in optional-modules-map
	doing
    (when devious-p
      (when (not invisible-module-p)
	(push `(,module-name (,(intern (format nil "~a-AUTHORIZED-P" module-name) 'ab)))
	      case-body)))
	finally
	  (return
	    `(case ,module-var
	       ,@case-body))))



;;; `Initialize-optional-modules' is used to mark all of the products as
;;; 'not currently being simulated'. It is called from run-ab immediately
;;; after the G2 has been authorized. If we don't do this and try to do any
;;; test for what has been authorized before the first time that
;;; setup-atomic-products-for-simulation happens to be called (which will
;;; be at the end of the first call to install-system-table), then the
;;; authorization information such as restricted-use-option-authorized-p
;;; will return its initial, meaningless value. See HQ-3238536.

(defun initialize-optional-modules ()
  (loop for (product . ignore) in optional-modules-map
	as simulated-state? = (get product 'simulation-state)
	when simulated-state? do
	    (setf (second simulated-state?) nil)))


(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar right-recursion-limit-list (cons nil left-recursion-limit-list))
)

(defmacro runtime-option-authorized-p ()
  '(or (runtime-option-authorized-p-internal)
       (second old-eval-cons-list)))


#+pre-g2-v5-licensing
(defmacro temporarily-make-runtime-only ()
  `(setf (second left-recursion-limit-list) 4))

#+pre-g2-v5-licensing
(defmacro restore-authorization-if-temporary ()
  '(setf (second left-recursion-limit-list) nil))

#+pre-g2-v5-licensing
(defmacro runtime-option-is-temporary-p ()
  '(third right-recursion-limit-list))





;; There is no automatic way to convey the value of optional-modules-map into
;; authorization functions that are not part of G2, e.g. NUMBERS.

;; End file with CR

