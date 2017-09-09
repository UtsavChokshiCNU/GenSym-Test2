;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module UTILITIES0

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark David, Lowell Hawkinson, Michael Levin, Stephen DeVoy, and Jim Allard





;;;; General Constraints on Recycled Objects



;;; (1) Never maintain any reference to objects that have been released.
;;; Otherwise data corruption will occur.
;;;
;;; (2) Do not release objects that were not obtained from the resource recycler
;;; for that object.  Otherwise, the recycler will pile up objects that even the
;;; static garbage collector cannot recycle.
;;; 
;;; (3) If you obtain objects from the resource recycler and just drop them, you
;;; do not get the benefit of the recycler, but the garbage collector might
;;; eventually get them.  This is the least sinful of these three violations.









;;;; Avoiding Variable Capture in Macros


;; (jh, 6/5/90)

;;; avoiding-variable-capture
;;;   <forms> 
;;;   <expansion-using-forms-with-impunity>

;;; Avoiding-variable-capture is designed for use inside macros where there is a
;;; danger of variable capture.  Variable capture occurs when an enclosing scope
;;; happens to use the same variable as a macroexpansion, causing unintended
;;; shadowing.  A related problem is multiple evaluation of subforms.  Wrapping an
;;; avoiding-variable-capture form around a backquoted form will solve both
;;; problems.  This wrapper will place a let-binding around the expansion only
;;; when needed to protect against variable capture.  This reduces the size of the
;;; G2 image and tends to make macro code more perspicuous.

;;; The syntax of avoiding-variable-capture is as follows.  <Forms> is a list of
;;; variables in the macro which are to be protected against capture.  If <forms>
;;; contains a &rest variable, all subforms in that variable are protected too.
;;; If <forms> contains some &aux variables, avoiding-variable-capture protects
;;; them by substituting uninterned symbols with the same printname.

;;; Arguments in the &optional section are of the form
;;;   (<variable> <default>)
;;; If <variable> is non-nil, avoiding-variable-capture will place it in the
;;; macroexpansion code, otherwise <default> will go there.  As with normal
;;; variables, avoiding-variable-capture will only generate let-bindings as
;;; they are needed, i.e., to prevent multiple evaluations of a single form.

;;; While the symbols provided by avoiding-variable-capture are unique, their
;;; printnames are not.  This may pose a readability problem for a nested
;;; macroexpansion.  Thus, a macoexpansion provided by avoiding-variable-capture
;;; will contain symbols whose printnames are made unique by suffixing a number to
;;; the printname given in <forms>.  Unlike the gensym facility, this number is
;;; incremented for each distinct printname rather than globally.

;;; <Expansion-using-forms-with-impunity> evaluates to a backquoted expression
;;; where any variable in <forms> can be unquoted without the risk of variable
;;; capture or multiple evaluation.  Note that
;;; <expansion-using-forms-with-impunity> is not an implicit progn, since that may
;;; not be what the backquoted expression wants to do at macroexpansion time.

;;; Note that avoiding-variable-capture operates at compile-time, and thus can
;;; cons all it pleases.  

;;; Also note the relationship between avoiding-variable-capture and
;;; def-substitution-macro.  The form
;;;  (def-substitution-macro my-function (arg1 arg2) 
;;;    (do-something arg1) 
;;;    (do-something 'else arg2))
;;; is equivalent to
;;;  (defmacro my-function (arg1 arg2)
;;;    (avoiding-variable-capture (arg1 arg2)
;;;      `(progn 
;;;         (do-something ,arg1)
;;;         (do-something 'else ,arg2)))))
;;; and is often clearer in this simple case.

;;; Here are some examples of the use of avoiding-variable-capture.  (We check our
;;; expansions with macroexpand-1 rather than macroexpand for readability in Lisps
;;; which implement LET as a macro.  Also note that the generated printnames lack
;;; unique numeric tags.  This is simply for clarity in understanding the
;;; examples.)

;;; (defmacro test (major-version minor-version &rest keys)
;;;   (avoiding-variable-capture 
;;;         (major-version minor-version &rest keys)
;;;     `(list ,major-version ,minor-version ,@keys)))
;;; TEST

;;; (macroexpand-1 '(test (+ default-major-version 1) 2))
;;; (LET ((#:MAJOR-VERSION (+ DEFAULT-MAJOR-VERSION 1)))
;;;   (LIST #:MAJOR-VERSION 2))

;;; (macroexpand-1 '(test 1 2 'remote-gsi-extension))
;;; (LIST 1 2 'REMOTE-GSI-EXTENSION)

;;; (macroexpand-1 '(test 1 (current-minor-version) 3 (get-key 'aux)))
;;; (LET ((#:MINOR-VERSION (CURRENT-MINOR-VERSION))
;;;       (#:KEYS-0 (GET-KEY 'AUX)))
;;;   (LIST 1 #:MINOR-VERSION 3 #:KEYS-0))

;;; (defmacro test2 (major-version minor-version &rest keys)
;;;   (avoiding-variable-capture 
;;;         (major-version minor-version &rest keys &aux month)
;;;     `(let ((,month (derive-month ,major-version ,@keys)))
;;;        (list ,major-version ,minor-version ,@keys ,month))))
;;; TEST2

;;; (macroexpand-1 '(test2 1 2 'remote-gsi-extension))
;;; (LET ((#:MONTH (DERIVE-MONTH 1 'REMOTE-GSI-EXTENSION)))
;;;   (LIST 1 2 'REMOTE-GSI-EXTENSION #:MONTH))

;;; (macroexpand-1 '(test2 1 (incf old-minor-version) (get-key)))
;;; (LET ((#:MINOR-VERSION (INCF OLD-MINOR-VERSION))
;;;       (#:KEYS-0 (GET-KEY)))
;;;   (LET ((#:MONTH (DERIVE-MONTH #:MINOR-VERSION #:KEYS-0)))
;;;     (LIST 1 #:MINOR-VERSION #:KEYS-0 #:MONTH)))

;;;(defmacro subsearch 
;;;          (search-for-string in-string 
;;;           &key start-in-string end-in-string)
;;;  (avoiding-variable-capture (search-for-string in-string
;;;			      &optional (start-in-string 0)
;;;					(end-in-string `(length ,in-string)))
;;;    `(loop for index from ,start-in-string below ,end-in-string
;;;	   always (eql (char ,search-for-string index)
;;;		       (char ,in-string index)))))
;;; SUBSEARCH

;;;(macroexpand 
;;;  '(subsearch "lo" "Hello there" 
;;;              :start-in-string 3 :end-in-string (+ 2 3))
;;;(LET ((#:END-IN-STRING (+ 2 3)))
;;;  (LOOP FOR INDEX FROM 3 BELOW #:END-IN-STRING
;;;	ALWAYS (EQL (CHAR "lo" INDEX) (CHAR "Hello there" INDEX))))

;;; IMPORTANT CAVEATS for using avoiding-variable-capture

;;; Caveat #1: Avoiding-variable-capture violates strict left-to-right evaluation.
;;; If a macro-call form has a subform which is side-effected by another subform
;;; to the right, avoiding-variable-capture will not follow that intent.  Example:

;;;(defmacro convoluted (a b)
;;;  (avoiding-variable-capture (a b)
;;;    `(list ,a ,b)))
;;;CONVOLUTED

;;;(macroexpand-1 '(convoluted a (setq a 'changed)))
;;;(LET ((#:B (SETQ A 'CHANGED)))
;;;  (LIST A #:B))

;;;(let ((a 'should-not-change)
;;;  (convoluted a (setq a 'changed)))
;;;(CHANGED CHANGED)

;;; Strict left-to-right evaluation would require the above form to return
;;; (SHOULD-NOT-CHANGE CHANGED).  Thus there is a trade-off between unnecessary
;;; binding of gensyms and obedience to order-of-evaluation constraints.  Macros
;;; that plan never to let their arguments side-effect each other (probably a
;;; large majority) can use avoiding-variable-capture freely.  Those that do plan
;;; on strict left-to-right evaluation should use only the &aux feature and set up
;;; the let-bindings by hand.  This is still an improvement over the old method,
;;; since the temporary variables have mnemonic names, unlike the old gensyms.

;;; Caveat #2: Avoiding-variable-capture should only be used when a form is to be
;;; evaluated, never when the form is not to be evaluated.  If this caveat is not
;;; met, some unpredictable behavior will occur.

;;; Example:

;;; (defmacro misuse (x y)
;;;   (avoiding-variable-capture (x y)
;;;     `(list ,x ',y)))
;;; MISUSE

;;; (macroexpand-1 '(misuse (evaluate this) (dont evaluate that)))
;;; (LET ((#:X (EVALUATE THIS))
;;;       (#:Y (DONT EVALUATE THAT)))
;;;   `(LIST #:X '#:Y))

;;; (misuse 'hello there)
;;; ERROR: Unbound variable THAT

;;; The correct definition would be

;;; (defmacro useful (x y)
;;;   (avoiding-variable-capture (x)
;;;     `(list ,x ',y)))

;;; Caveat #3: all bets are off if one of the <forms> is a symbol that has been
;;; bound by symbol-macrolet.  This is probably moot, since Gensym style bans
;;; macrolet, and probably looks equally askance upon symbol-macrolet.






(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro form-has-side-effects-p (form)
  (and (consp form)
       (not (eq (car form) 'quote))))
)

;; On some compilers (say TI Lisp), quoted functional arguments (say to notany)
;; are not recognized, even when the function's definition was surrounded by an
;; eval-when.  Rather than write a loop for each such form in the
;; avoiding-variable-capture macro below, it seems the simpler course to funquote
;; such arguments.  Thus we change each 'form-has-side-effects-p to
;; #'form-has-side-effects-p.  This deviation from Gensym style only happens at
;; compile time, and has no effect on G2 runtime code, which always uses symbols
;; as functional arguments.  (mhd & jh, 6/13/90)

;; Moved avoiding-variable-capture from UTILITIES3 because of a bug in macrolet in
;; TI Lisp.  A local macroexpander generated by macrolet cannot use a global macro
;; defined in the same file as the macrolet to perform its macroexpansion.  Global
;; macros have no trouble seeing each other.  jh, 10/18/90.

;; jh, 1/25/91.  Fixed bug in &rest variables for avoiding-variable-capture.  It
;; previously side-effected the actual argument form of the macro, a bad idea
;; since the system also uses this.  Now it copies the list before it munges it.

;; jh, 6/3/91.  Added &uniquify keyword to make printnames unique for nested
;; macroexpansions (see documentation above for details).  Currently everything is
;; uniquified, until we can figure out a way to do it only when we are doing
;; nested expansions.  
;; jh, 6/4/91.  Removed &uniquify keyword after protests.  It would still be nice
;; to uniquify only when we have to, i.e., only when we encounter nested
;; expansions using the same symbol names.

(defun-for-macro make-symbol-for-avoiding-variable-capture
		 (printname uniquify-p)
  #-development
  (declare (ignore uniquify-p))
  #+development
  (if uniquify-p
      (make-symbol
	(format nil "~a-~a"
		printname
		(incf (get (intern printname "AB")
			   'avoiding-variable-capture-counter
			   0))))
      (make-symbol printname))
  #-development
  (make-symbol printname))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro avoiding-variable-capture
          (forms &body expansion-not-progn-using-forms-with-impunity)

  ;; protect the variables in the avoiding-variable-capture form by hand
  (let* ((expansion-using-forms-with-impunity 
	   (car expansion-not-progn-using-forms-with-impunity))
	 (form-specs '#:form-specs)
	 (side-effecting-form-specs '#:side-effecting-form-specs)
	 (side-effecting-temp-vars '#:side-effecting-temp-vars)
	 (side-effecting-forms '#:side-effecting-forms)
	 (rest-specs '#:rest-specs)
	 (side-effecting-rest-specs '#:side-effecting-rest-specs)
	 (side-effecting-rest-temps '#:side-efecting-rest-temps)
	 (side-effecting-rest-subforms '#:side-effecting-rest-subforms)
	 rest-variable aux-variables optional-specs 
	 (uniquify-p t))

    ;; parse the &optional, &rest, and &aux variables
    (loop with required-segment = nil
	  with optional-segment = nil
	  with rest-segment = nil 
	  with aux-segment = nil
	  with mode = 'required
	  for form in forms
	  do (case form
	       (&rest (setq mode '&rest))
	       (&optional (setq mode '&optional))
	       (&aux (setq mode '&aux)))
	     (case mode
	       (required (push form required-segment))
	       (&rest (push form rest-segment))
	       (&optional (push form optional-segment))
	       (&aux (push form aux-segment)))
	  finally
	  (setq forms (nreverse required-segment)
		rest-variable (cadr (nreverse rest-segment))
		aux-variables (cdr (nreverse aux-segment))
		optional-specs (cdr (nreverse optional-segment))))

      `(if (and ;; no required form or subform has side effects
		(notany #'form-has-side-effects-p (list ,@forms))
		;; no optional form or subform has side effects
		,@(loop for (optional-form default-form) in optional-specs
			append
			(if (form-has-side-effects-p default-form)
			    `(,optional-form
			      (not (form-has-side-effects-p ,optional-form)))
			    `((or (null ,optional-form)
				  (not (form-has-side-effects-p ,optional-form))))))
		;; the rest form or subform has side effects
		(notany #'form-has-side-effects-p ,rest-variable))

           ;; if nothing has side effects
	   (let ,(loop for aux-variable in aux-variables
		       collecting
		       `(,aux-variable 
			 (make-symbol-for-avoiding-variable-capture
			   ,(symbol-name aux-variable)
			   ,uniquify-p)))
	     ,@(loop for (optional-form default-form) in optional-specs
		     unless (form-has-side-effects-p default-form)
		       collect
		       `(unless ,optional-form
			  (setq ,optional-form ,default-form)))
	     ,expansion-using-forms-with-impunity)

           ;; if at least one form or subform has side effects
	   (let* ((,form-specs
		   (list 
		     ,@(loop for form in forms
			     collecting 
			     `(list (make-symbol-for-avoiding-variable-capture
				      ,(symbol-name form)
				      ,uniquify-p) 
				    ,form))
		     ,@(loop for (optional-variable default-form) 
				 in optional-specs
			     collecting
			     `(list (make-symbol-for-avoiding-variable-capture
				      ,(symbol-name optional-variable)
				      ,uniquify-p)
				    (or ,optional-variable ,default-form)))))
		  (,side-effecting-form-specs
		   (remove-if-not #'form-has-side-effects-p 
				  ,form-specs :key #'second))
		  (,side-effecting-temp-vars
		     (mapcar #'first ,side-effecting-form-specs))
		  (,side-effecting-forms
		     (mapcar #'second ,side-effecting-form-specs))
		  (,rest-specs
		     (loop with index = 0 
			   for subform in ,rest-variable
			   collecting 
			   (list 
			     (make-symbol-for-avoiding-variable-capture
			       (format nil "ELT-~a-OF-~a" index ',rest-variable)
			       ,uniquify-p)
			     subform)
			   do (incf index)))
		  (,side-effecting-rest-specs
		     (remove-if-not #'form-has-side-effects-p 
				    ,rest-specs :key #'second))
		  (,side-effecting-rest-temps
		     (mapcar #'first ,side-effecting-rest-specs))
		  (,side-effecting-rest-subforms
		     (mapcar #'second ,side-effecting-rest-specs))

		  ;; protect the aux variables
		  ,@(loop for aux-variable in aux-variables
			  collecting
			  `(,aux-variable 
			    (make-symbol-for-avoiding-variable-capture
			      ,(symbol-name aux-variable)
			      ,uniquify-p))))

	     ;; protect the required and optional forms
	     ,@(let ((index 0))
		 (append
		   ;; required forms
		   (loop for form in forms
			 collect
			 `(when (form-has-side-effects-p ,form)
			    (setq ,form (first (elt ,form-specs ,index))))
			 do (incf index))
		   ;; optional forms
		   (loop for (optional-form default-form) in optional-specs
			 collect
			 (if (form-has-side-effects-p default-form)
			     `(when (or (null ,optional-form)
					(form-has-side-effects-p 
					  ,optional-form))
				(setq ,optional-form 
				      (first (elt ,form-specs ,index))))
			     `(cond ((and ,optional-form 
					  (form-has-side-effects-p 
					    ,optional-form))
				     (setq ,optional-form 
					   (first (elt ,form-specs ,index))))
				    ((null ,optional-form)
				     (setq ,optional-form ,default-form))))
			 do (incf index))))

	     ;; protect the &rest form - copy it first so we don't mess up any
	     ;; internal facility using the &rest form passed to the macro
	     ,@(when rest-variable
		 `((setq ,rest-variable (copy-list ,rest-variable))
		   (loop for index from 0 below (length ,rest-variable)
			 do 
			 (when (form-has-side-effects-p (elt ,rest-variable index))
			   (setf (elt ,rest-variable index) 
				 (first (elt ,rest-specs index)))))))

	     ;; the enhanced backquoted form
	     `(let (,@(mapcar #'list
			      ,side-effecting-temp-vars
			      ,side-effecting-forms)
		    ,@(mapcar #'list
			      ,side-effecting-rest-temps
			      ,side-effecting-rest-subforms))
		,,expansion-using-forms-with-impunity)))))
)


;;;; Queues



;;; Def-queue defines a set of queuing operations for a queue of linked "elements".
;;; The operations are:
;;;
;;;    (ENQUEUE-name element [structure-holding-queue-and-pool]),
;;;
;;;    (DEQUEUE-name-IF-ANY [structure-holding-queue-and-pool]),
;;;
;;;    (OBTAIN-name [structure-holding-queue-and-pool]), and
;;;
;;;    (RECLAIM-name element [structure-holding-queue-and-pool])....
;;;
;;; RECLAIM-name is assumed not to be called before the first call to OBTAIN-name.

;;; Available-elements-maker takes no arguments and returns one or more unfilled-in
;;; elements, suitably linked via element-link-accessor links, with nil at the end.
;;; Thus it may make a "batch" of new elements at a time.

;;; For most purposes, where auto-reclaim-on-next-dequeue? has been specified and where the
;;; queue and pool are kept in system variables, the following two operations are all
;;; that are needed to use this facility:
;;;
;;;    (FILLING-IN-ELEMENT-FOR-QUEUE (name-for-queue-as-element-variable)
;;;      {form-to-fill-in-element}) and
;;;
;;;    (DEQUEUE-name-IF-ANY).
;;;
;;; Note that where auto-reclaim-on-next-dequeue? has been specified, all information
;;; must be extracted from a dequeued element before an attempt is made to dequeue the
;;; next element.

;;; If the queue (and pool) are to be kept in system variables, the optional accessors
;;; should not be specified.  If they are to be kept in a structure, however, all four
;;; accessors (for the head and tail of the queue and pool) must be specified.  In this
;;; latter case, every operation defined by def-queue takes an additional structure-
;;; holding-queue-and-pool final argument, to which the accessors are applied.

;;; This facility is especially valuable for communication between two asynchronous
;;; processes or between a main process and its (atomic) interrupt handlers.  As long
;;; as a particular queue is used only by the pair of processes (or the main process and
;;; its interrupt handlers) in such a way that one side exclusively enqueues and the other
;;; exclusively dequeues, the enqueuing and dequeuing can be safely done without locks.
;;; (Note that once a process has dequeued something, it cannot "put it back".  Instead,
;;; it must use another holding variable or a separate queue.)

;(defmacro def-queue
;	  (name module-name
;	   available-elements-maker element-link-accessor
;	   auto-reclaim-on-next-dequeue?
;	   &optional
;	   accessor-for-head-of-queue? accessor-for-tail-of-queue?
;	   accessor-for-head-of-pool? accessor-for-tail-of-pool?)

;  (let* ((enqueuer (format-symbol "ENQUEUE-~A" name))
;	 (dequeuer (format-symbol "DEQUEUE-~A-IF-ANY" name))
;	 (obtainer (format-symbol "OBTAIN-~A" name))
;	 (reclaimer (format-symbol "RECLAIM-~A" name))
;;	 (linked-element-enqueuer (format-symbol "ENQUEUE-LINKED-~AS" name))   ; later!
;;	 (linked-element-reclaimer (format-symbol "RECLAIM-LINKED-~AS" name))  ; later!
;	 (structure-holds-queue-and-pool?	; verify all or none!
;	   accessor-for-head-of-queue?)
;	 (place-for-head-of-queue
;	   (if structure-holds-queue-and-pool?
;	       `(,accessor-for-head-of-queue? structure-holding-queue-and-pool)
;	       (format-symbol "HEAD-OF-~A-QUEUE" name)))
;	 (place-for-tail-of-queue
;	   (if structure-holds-queue-and-pool?
;	       `(,accessor-for-tail-of-queue? structure-holding-queue-and-pool)
;	       (format-symbol "TAIL-OF-~A-QUEUE" name)))
;	 (place-for-head-of-pool
;	   (if structure-holds-queue-and-pool?
;	       `(,accessor-for-head-of-pool? structure-holding-queue-and-pool)
;	       (format-symbol "HEAD-OF-~A-POOL" name)))
;	 (place-for-tail-of-pool
;	   (if structure-holds-queue-and-pool?
;	       `(,accessor-for-tail-of-pool? structure-holding-queue-and-pool)
;	       (format-symbol "TAIL-OF-~A-POOL" name)))
;	 (extra-args
;	   (if structure-holds-queue-and-pool? '(structure-holding-queue-and-pool)))
;	 (initializer (format-symbol "INITIALIZE-~A-QUEUE-AND-POOL" name)))

;    `(progn

;     ,@(if (not structure-holds-queue-and-pool?)
;	   `((def-system-variable ,place-for-tail-of-queue ,module-name nil)
;	     (def-system-variable ,place-for-head-of-queue ,module-name nil)
;	     (def-system-variable ,place-for-tail-of-pool ,module-name nil)
;	     (def-system-variable ,place-for-head-of-pool ,module-name
;	       (:funcall ,initializer))))

;     ,(if (not structure-holds-queue-and-pool?)
;	  `(defmacro ,enqueuer (element)
;	     `(setq ,',place-for-tail-of-queue
;		    (setq (,',element-link-accessor ,',place-for-tail-of-queue)
;			  ,element)))		; assume element's link is nil
;	  `(def-substitution-macro ,enqueuer (element . ,extra-args)
;	     (setf ,place-for-tail-of-queue
;		   (setf (,element-link-accessor
;			  (or ,place-for-tail-of-queue
;			      (setf ,place-for-head-of-queue        ; needed only to
;				    (setf ,place-for-tail-of-queue  ;   initialize the queue
;					  (,obtainer . ,extra-args)))))
;			 element))))		; assume element's link is nil

;     (def-substitution-macro ,dequeuer ,extra-args
;       (let ((head-of-queue ,place-for-head-of-queue))
;	 (if (and (not (eq head-of-queue ,place-for-tail-of-queue))
;		  ,@(if structure-holds-queue-and-pool? '(head-of-queue)))	; see above
;	     (prog1
;	       (setf ,place-for-head-of-queue
;		     (,element-link-accessor head-of-queue))
;	       ,@(if auto-reclaim-on-next-dequeue?
;		     `((,reclaimer head-of-queue . ,extra-args)))))))

;     (def-substitution-macro ,obtainer ,extra-args
;       (let ((head-of-pool ,place-for-head-of-pool))
;	 (if (or (eq head-of-pool ,place-for-tail-of-pool)
;		 ,@(if structure-holds-queue-and-pool? '((null head-of-pool))))
;	     (let* ((available-elements (,available-elements-maker . ,extra-args))
;		    (last-available-element available-elements))
;	       (loop while (,element-link-accessor last-available-element)
;		     do (setq last-available-element
;			      (,element-link-accessor last-available-element)))
;	       (setf (,element-link-accessor last-available-element) head-of-pool)
;	       ,@(if structure-holds-queue-and-pool?
;		     `((if (null head-of-pool)
;			   (setf ,place-for-tail-of-pool last-available-element))))
;	       (setq head-of-pool available-elements)))
;	 (setf ,place-for-head-of-pool
;	       (,element-link-accessor head-of-pool))
;	 head-of-pool))

;     (def-substitution-macro ,reclaimer              ; subst. unnec. if assume link
;			     (element . ,extra-args) ;   nil and no extra args
;       (setf (,element-link-accessor element) nil)   ; assume link is nil?
;       (setf ,place-for-tail-of-pool		     ; assume pool has been initialized
;	     (setf (,element-link-accessor ,place-for-tail-of-pool)
;		   element)))

;     ,@(if (not structure-holds-queue-and-pool?)
;	   `((defun ,initializer ()
;	       (let* ((available-element-for-queue (,available-elements-maker))
;		      (available-elements-for-pool
;			(or (,element-link-accessor available-element-for-queue)
;			    (,available-elements-maker)))
;		      (last-available-element-for-pool available-elements-for-pool))
;		 (loop while (,element-link-accessor last-available-element-for-pool)
;		       do (setq last-available-element-for-pool
;				(,element-link-accessor
;				 last-available-element-for-pool)))
;		 (setf (,element-link-accessor available-element-for-queue) nil)
;		 (setq ,place-for-head-of-queue
;		       (setq ,place-for-tail-of-queue available-element-for-queue))
;		 (setq ,place-for-tail-of-pool last-available-element-for-pool)
;		 available-elements-for-pool))))

;     ',name)))

;; Consider having all pools used in Gensym software be queues of this type.

;; Note that only enqueuers (and reclaimers) change tail variables, at least once they have
;; been initialized.  Similarly, note that only dequeuers (and obtainers) change head
;; variables, at least once they have been initialized.  This is essential to having
;; enqueueing and dequeuing work properly between asynchronous processes without locking.

;; Consider initializing queues and pools in structures in advance, rather than on the first
;; enqueue and reclaim.



;;; Filling-in-element-for-queue ...

;(defmacro filling-in-element-for-queue
;	  ((name-for-queue-as-element-variable &optional structure-holding-queue-and-pool?)
;	   &body body-to-fill-in-element)
;  `(let ((,name-for-queue-as-element-variable
;	  (,(format-symbol "OBTAIN-~A" name-for-queue-as-element-variable)
;	   . ,(if structure-holding-queue-and-pool?
;		  `(,structure-holding-queue-and-pool?)))))
;     (progn . ,body-to-fill-in-element)
;     (,(format-symbol "ENQUEUE-~A" name-for-queue-as-element-variable)
;      ,name-for-queue-as-element-variable
;      . ,(if structure-holding-queue-and-pool?	; bind var to this?
;	     `(,structure-holding-queue-and-pool?)))))
(progn) ; end of section




;;;; Queues, II


;;; Non-consing queues with efficiency O(1) -- unrelated to the above.



;;; A queue is a list of items. An item can be any Lisp object. The queue is based
;;; from two pointers called the head and the tail. An empty queue has both of these 
;;; set to nil. If a queue is not empty, head points to the entire list, and tail
;;; points to the last cons of the list. The queues are built with recycled conses.
;;; There will be no data coruption if head and tail are modified only by the following
;;; macros.

;;; Both queueing and dequeueing are O(1) because the tail pointer is maintained.

;;; To enqueue an item use (enqueue item tail head). The value is the item enqueued.

;;; To enqueue a non-empty list of items use (enqueue-list list-of-items tail head).
;;; The value is the new value of tail.


;;; To dequeue an item, use (dequeue head tail). The value is the first item of
;;; the queue which will have been dequeued, or if the queue is empty, NIL.

;;; To obtain the first item without dequeueing it, use (examine-head-of-queue
;;; head) The value will be the first item on the queue or NIL for an empty
;;; queue.

;;; The value of dequeue or examine-head-of-queue does not distinquish an empty
;;; queue from a queue whose first item is NIL.

;;; THESE ARE LOCATION MODIFYING MACROS. It is guaranteed that no argument will
;;; be evaluated for value more than once, but certain arguments may be
;;; evaluated once and setf'd once. For example, enqueue will evaluate head, and
;;; if null, will also setf it. So if the formal parameter 'head' is (aref
;;; array-x (fn h)), then (fn h) will get evaluated twice. Better to write (let
;;; ((array-index (fn h))) ...  (aref array-x array-index).

;;; Enqueue and dequeue have an optional argument to specify the obtain and
;;; release function for the cons. The argument should be the unquoted name of
;;; the function to use. This feature is not dynamic.

;; Consider generating this facility as part of defconser, perhaps optionally!!
;; Variants of can probably be used in at least the modules SCHEDULE, ICP, and
;; WORKSTATIONS.  Note also that if this is revived, it will have to use some
;; other conser than obtain- cons.  The only current users of this facility are
;; the "def-action inform" in ACTIONS and the "def-action invoke-procedure" in
;; PROCEDURES.

(defmacro enqueue-1 (item head tail obtain-cons-function)
  (let ((value-of-item (gensym))
	(new-cons (gensym)))
    `(let* ((,value-of-item ,item)
	    (,new-cons (,obtain-cons-function ,value-of-item nil)))
       (if ,head
	   (progn
	     ;; NOTE: in product mode, if HEAD is non-null but TAIL is null, fix
	     ;; TAIL automatically using the LAST of HEAD.
	     #-development
	     (when (null ,tail)
	       (setf ,tail (last ,head)))
	     (setf (cdr ,tail) ,new-cons))
	   (setf ,head ,new-cons))
       (setf ,tail ,new-cons)
       ,value-of-item)))

#-SymScale
(defmacro enqueue (item head tail obtain-cons-function)
  `(enqueue-1 ,item ,head ,tail ,obtain-cons-function))

;;; The non-blocking queue algorithm used by SymScale version of ENQUEUE and
;;; DEQUEUE is based on following paper:
;;;
;;; M. M. Michael and M. L. Scott. Simple, fast and practical non-blocking and
;;; blocking concurrent queue algorithms. In Proc. of the Fifteenth Annual ACM
;;; Symposium on Principles of Distributed Computing, pp. 267-275, 1996, ACM
;;; Press.

#+SymScale
(defmacro enqueue (item head tail obtain-cons-function)
  (let ((value-of-item (gensym))
	(new-cons (gensym))
	(first (make-symbol "FIRST"))
	(last (make-symbol "LAST"))
	(next (make-symbol "NEXT")))
    `(let* ((,value-of-item ,item) ; value
	    (,new-cons (,obtain-cons-function ,value-of-item nil))) ; node
       (loop
	 (let* ((,first ,head)
		(,last ,tail)
		(,next (cdr ,tail)))
	   (if (null ,first) ; empty queue
	       (when (compare-and-swap ,head ,first ,new-cons)
		 (compare-and-swap ,tail ,last ,new-cons)
		 (return ,new-cons))
	     (when (eq ,last ,tail)
	       (if (null ,next)
		   (when (compare-and-swap (cdr ,last) ,next ,new-cons)
		     (compare-and-swap ,tail ,last ,new-cons)
		     (return ,new-cons))
		 (compare-and-swap ,tail ,last ,next)))))))))

;; The new enqueue/dequeue macros below written by JH below work fine --
;; I am installing them.  We can update the documentation a little
;; later.  (MHD 1/17/92)
;; --- UPDATE: the Chestnut compiler can't well handle the define-setf-method, so
;; we're going to put this on hold, and I'm uncommenting out the old enqueue
;; and dequeue. (MHD 1/17/92)

(defmacro enqueue-list (non-empty-list-of-items head tail)
  (let ((value-of-non-empty-list-of-items (gensym)))
    `(let ((,value-of-non-empty-list-of-items ,non-empty-list-of-items))
       (if ,head
	   (setf (cdr ,tail) ,value-of-non-empty-list-of-items)
	   (setf ,head ,value-of-non-empty-list-of-items))
       (setf ,tail (last ,value-of-non-empty-list-of-items)))))

;; The above is still unhygenic!!  Ask JH to look at it.  (MHD 1/17/92)

;; UPDATE: it's not used anywhere, therefore the SymScale version is not
;; implemented. (binghe 12/12/2013)

(defmacro dequeue-1 (head tail release-cons-function)
  (let ((value-of-head (gensym))
	(value-of-next-item (gensym)))
    `(let ((,value-of-head ,head) ,value-of-next-item)
       (if ,value-of-head
	   (prog1 (car ,value-of-head)
		  (setq ,value-of-next-item (cdr ,value-of-head))
		  (setf ,head ,value-of-next-item)
		  (unless ,value-of-next-item (setf ,tail nil))
		  (,release-cons-function ,value-of-head))
	   nil))))

#-SymScale
(defmacro dequeue (head tail release-cons-function)
  `(dequeue-1 ,head ,tail ,release-cons-function))

#+SymScale
(defmacro dequeue (head tail release-cons-function)
  (let ((value-of-head (gensym))
	(first (make-symbol "FIRST"))
	(last (make-symbol "LAST"))
	(next (make-symbol "NEXT")))
    `(loop
       (let* ((,first ,head)
	      (,last ,tail)
	      (,next (cdr ,first)))
	 (if (null ,first) ; null queue
	     (return nil)
	   (when (eq ,first ,head)
	     (if (eq ,first ,last) ; null queue, one node left, or tail pointer is delayed
		 (compare-and-swap ,tail ,last ,next)
	       (let ((,value-of-head (car ,first)))
		 (when (compare-and-swap ,head ,first ,next)
		   (,release-cons-function ,first)
		   (return ,value-of-head))))))))))

(defmacro examine-head-of-queue (head)
  `(car ,head))					; works even when head is nil

;; Enqueue and dequeue should be defined using define-modify-macro (see
;; replace-value above, for example), to avoid multiple evaluation of place
;; ("location") arguments!






;;;; Managed Float Unique Marker




;;; The global variable `managed-float-unique-marker' contains a value used to
;;; uniquely mark the CDRs of conses representing managed-floats.

;; Moved to UTILITIES0 to help in development error checking.  -jra 3/25/91

(defvar-of-special-global managed-float-unique-marker (make-symbol "MANAGED-FLOAT-MARKER"))






;;;; Defining Consers



;;; Defconser defines a standard suite of consing related functions and
;;; variables (a `consing facility') whose names are derived from a given `root
;;; name' (root-name).  This macro takes an unquoted symbol as the root name
;;; and has several other optional arguments, which should only be used in
;;; unusual circumstances.

;;; If module-name? is non-nil, it should be the "home module" of the consing
;;; facility being defined.  This is needed only to tell defconser what module
;;; the system variables it defines belong to.  If no module name is provided,
;;; the module UTILITIES1 is used.

;;; The fully-checked? optional argument is a development feature which causes
;;; defconser to emit consing and reclaiming code which fully checks that every
;;; cons given back was given out from this conser, and that it is not already
;;; in the pool of reclaimed conses.  It is extremely inefficient, and only
;;; works in the development environment.

;;; NOTE: it's NOT available on SymScale because conses are in multiple threads'
;;; memory pools, no way to walk them all.  -- Chun Tian (binghe), Feb 20, 2014.

;;; The dont-coalesce? argument will suppress this conser being folded in with
;;; the gensym-cons pool in distribution images.  You may want to keep a conser
;;; separate in order to find leaks, or to improve locality of reference amongst
;;; the conses in that pool.  This option should only rarely be used, since we
;;; get memory reuse benefits from coalescing all the consing pools.

;;; The specific list of names generated given, say, the conser name X is the
;;; following (described in greater detail below):
;;;
;;;    x-cons, x-cons-macro, x-list, copy-tree-using-x-conses,
;;;    copy-list-using-x-conses, reclaim-x-cons, reclaim-x-cons-macro,
;;;    reclaim-x-list, reclaim-x-list-macro, reclaim-x-list*, reclaim-x-tree,
;;;    delete-x-cons, delete-x-element, and report-outstanding-x-conses

;;; The following lisp symbols are generated given, say X, a particular conser
;;; name:
;;;
;;;    x-conses                     ; system object pool reporting this conser's
;;;                                 ;   memory usage
;;;
;;;    x-cons                       ; analog of CONS (a function)
;;;
;;;    x-cons-macro                 ; analog of CONS (a macro)
;;;
;;;    x-list                       ; analog of LIST
;;;
;;;    make-x-list-macro 	    ; analog of MAKE-LIST, but the contents of the
;;;    				    ;   returned list are undefined rather than NILs
;;;
;;;    make-x-list                  ; analog of MAKE-LIST, but the contents of
;;;    				    ;   the returned list are undefined rather
;;;    				    ;   than NILs
;;;
;;;    x-list-macro		    ; optimized analog of LIST
;;;
;;;    copy-tree-using-x-conses     ; returns a copy of x-tree made up of x-conses
;;;
;;;    copy-list-using-x-conses     ; returns a copy of the spine of x-list using x-conses
;;;
;;;    reclaim-x-cons               ; returns x-cons to available-x-conses
;;;
;;;    reclaim-x-cons-macro         ; a macro returning x-cons to available-x-conses
;;;
;;;    reclaim-x-list               ; returns top-level conses of x-list to available-
;;;                                 ;   x-conses
;;;
;;;    reclaim-x-list-macro         ; a macro which returns the top level conses of a
;;;                                 ;   list to available-x-conses
;;;
;;;    reclaim-x-list-given-tail    ; A macro which, given the head and tail of
;;;                                 ;   a list, returns its top level conses to
;;;                                 ;   available-x-conses
;;;
;;;    reclaim-x-list*              ; returns top-level conses of x-list to available-
;;;                                 ;   x-conses, correctly handling dotted-lists
;;;
;;;    reclaim-x-tree               ; returns all the conses in x-tree to available-conses
;;;
;;;    delete-x-element             ; deletes and reclaims the first cons of x-list
;;;                                 ;   whose car EQ to element, if any, and returns the
;;;                                 ;   resultant list.
;;;
;;;
;;;    delete-x-cons                ; deletes x-cons from x-list and returns the
;;;                                 ;   resultant list.  X-cons must be one of the
;;;                                 ;   conses constituting x-list.
;;;
;;;    report-outstanding-x-conses  ; Calls FORMAT with the format string
;;;                                 ;   "~%The number of outstanding X conses is ~D"
;;;                                 ;   and the appropriate value for ~D.  Available
;;;                                 ;   in development only.

;; Added x-push, x-pushnew, and x-pop to the macros created by a defconser form. 
;; (jra & jh, 3/23/90)

;;;    x-push                       ; Pushes its first subform onto the place given
;;;                                 ;   by its second subform, using x-cons.
;;;
;;;    x-pushnew                    ; Pushes its first subform onto the place given
;;;                                 ;  by its second subform unless it passes :test.
;;;                                 ;  Keywords :test-not and :key are also supported.
;;;
;;;    x-pop                        ; Returns the first element of the place,
;;;                                 ;   sets the place to the rest of the list,
;;;                                 ;   and reclaims the first cons in the list.

;; To explain the technical problem with implementing the modify macro x-pop we
;; need some terminology.  The "place form" of a modify macro is the location it
;; is supposed to mutate.  The "conceptual setf result" of a define-modify-macro
;; is the result returned after the mutation has occurred.  Pop differs from
;; normal modify macros in that it must return a result other than the conceptual
;; setf result.  The implementation problem arises because define-modify-macro
;; makes no arrangements to return a value different from its conceptual setf
;; result.  In particular, it provides no means to "freeze" the place form (which
;; may have side effects.  This can cause evaluation of the place form more than
;; once, which is forbidden.  The canonical example of this problem is
;;
;;   (x-pop (svref (pop *arrays*) (incf *indices*))) 
;;
;; It is essential that x-pop evaluate its place form only once because the inner
;; pop and incf should only be executed once.  The solution is to have a special
;; variable return a result from the modify macro, which then, as contracted,
;; evaluates the place form only once during its execution.  Note also that this
;; special variable must be different for each incarnation of G2, lest
;; process-switching mix pop results from two processes which happen to be popping
;; from pools of the same name.  The solution is to use a system-variable, defined
;; in expansion-for-x-pop.



;; The following added by ML on 7/26/91 to track down a particular cons
;; that was being reclaimed, and shouldn't have been. To use it, setq
;; stange-cons to some cons. If it is reclaimed, a error results.


;; defconser has been modified to set the cons's to the car-marker when
;; reclaimed (in development). the specific reclaimers effected are x-pop,
;; x-reclaim-list and x-reclaim-list given tail -rdf, 9/1/94

(defvar strange-cons (list 'strange-cons))

(defmacro note-allocate-cons (cons pool)
  `(inline-note-allocate-cons ,cons ,pool))

(defmacro note-reclaim-cons (cons pool)
  `(inline-note-reclaim-cons ,cons ,pool))

(def-inlined-pseudo-function-with-side-effects (inline-note-allocate-cons :void) (cons pool)
  (declare (ignore cons pool))
  nil)

(def-inlined-pseudo-function-with-side-effects (inline-note-reclaim-cons :void) (cons pool)
  (declare (ignore cons pool))
  nil)

#+cons-checking
(cons-checking-start-common-part t)

(defvar debugging-consing nil)

(defmacro debugging-consing-p ()
  `(not (=f 0 (inline-debugging-consing))))

(def-side-effect-free-inlined-pseudo-function (inline-debugging-consing :long) ()
  (if debugging-consing 1 0))

(defvar-for-macro dont-coalesce-cons-pools? nil)

(defmacro defconser (root-name &optional module-name? fully-checked? dont-coalesce?)
  #+SymScale ; forcely disable `fully-checked?' support.
  (when fully-checked?
    (setq fully-checked? nil))
  (if (not (or (eval-feature :development)
	       fully-checked?
	       ;; NOTE: replace with T to enable special build.
	       #+(or mtg2 SymScale) t ; disable pseudo-consers
	       #-SymScale (eq root-name 'gensym)
	       dont-coalesce?
	       dont-coalesce-cons-pools?))
    `(def-pseudo-conser ,root-name gensym)
    (let* ((available-x-conses
	     (intern (format nil "AVAILABLE-~a-CONSES" root-name)))
	   (available-x-conses-tail
	     (intern (format nil "AVAILABLE-~a-CONSES-TAIL" root-name)))
	   #+mtg2
	   (x-cons-lock
	     (intern (format nil "~a-CONS-LOCK" root-name)))
	   #+SymScale
	   (available-x-conses-vector
	     (intern (format nil "AVAILABLE-~a-CONSES-VECTOR" root-name)))
	   #+SymScale
	   (available-x-conses-tail-vector
	     (intern (format nil "AVAILABLE-~a-CONSES-TAIL-VECTOR" root-name)))
	   (conses-from-this-pool?
	     (if fully-checked?
		 (intern (format nil "CONSES-FROM-THE-~a-POOL" root-name))
		 nil))
	   #+development
	   (x-car-marker
	     (intern (format nil "~a-CAR-MARKER" root-name)))
	   #+development
	   (x-error-message
	     (format nil "Data corruption in ~A cons pool" root-name))
	   #+development
	   (x-float-marker-message
	     (format nil "Reclaiming the managed-float marker as a ~a cons."
		     root-name))
	   #+development
	   (x-strange-cons-message
	     (format nil "Reclaiming strange-cons as a ~a cons." root-name))
	   (replenish-x-cons-pool
	     (intern (format nil "REPLENISH-~a-CONS-POOL" root-name)))
	   (replenish-x-list-pool
	     (intern (format nil "REPLENISH-~a-LIST-POOL" root-name)))
	   (x-cons-counter
	     (intern (format nil "~a-CONS-COUNTER" root-name)))
	   #+SymScale
	   (x-cons-counter-vector
	     (intern (format nil "~a-CONS-COUNTER-VECTOR" root-name)))
	   (outstanding-x-cons-counter-function
	     (intern (format nil "OUTSTANDING-~a-CONSES" root-name)))
	   (x-memory-usage
	     (intern (format nil "~a-CONS-MEMORY-USAGE" root-name)))
	   (x-pool-name (intern (format nil "~a-CONSES" root-name)))
	   (x-cons-macro
	     (intern (format nil "~a-CONS-MACRO" root-name)))
	   (actual-x-cons-macro
	     (intern (format nil "ACTUAL-~a-CONS-MACRO" root-name)))
	   (x-cons-function
	     (intern (format nil "~a-CONS" root-name)))
	   (actual-x-cons-function
	     (intern (format nil "~a-1" x-cons-function)))
	   (x-cons-variable
	     (intern (format nil "~a-CONS" root-name)))
	   (make-x-list-macro
	     (intern (format nil "MAKE-~a-LIST-MACRO" root-name)))
	   (make-x-list
	     (intern (format nil "MAKE-~a-LIST" root-name)))
	   (actual-make-x-list
	     (intern (format nil "~a-1" make-x-list)))
	   (x-list-function
	     (intern (format nil "~a-LIST" root-name)))
	   (x-list-trace-hook
	     (intern (format nil "~a-LIST-TRACE-HOOK" root-name)))
	   (x-list-macro
	     (intern (format nil "~a-LIST-MACRO" root-name)))
	   (x-list-variable
	     (intern (format nil "~a-LIST" root-name)))
	   (x-list-2-function
	     (intern (format nil "~a-2" x-list-function)))
	   (x-list-3-function
	     (intern (format nil "~a-3" x-list-function)))
	   (x-list-4-function
	     (intern (format nil "~a-4" x-list-function)))
	   (x-tail-variable
	     (intern (format nil "~a-LIST-TAIL" root-name)))
	   (copy-tree-using-x-conses
	     (intern (format nil "COPY-TREE-USING-~a-CONSES" root-name)))
	   (actual-copy-tree-using-x-conses
	     (intern (format nil "~a-1" copy-tree-using-x-conses)))
	   (copy-list-using-x-conses
	     (intern (format nil "COPY-LIST-USING-~a-CONSES" root-name)))
	   (actual-copy-list-using-x-conses
	     (intern (format nil "~a-1" copy-list-using-x-conses)))
	   (reclaim-x-cons
	     (intern (format nil "RECLAIM-~a-CONS" root-name)))
	   #+development
	   (x-cons-checker
	     (intern (format nil "~a-CONS-CHECKER" root-name)))
	   #+development
	   (x-list-checker
	     (intern (format nil "~a-LIST-CHECKER" root-name)))
	   #+development
	   (x-list-checker-given-tail
	     (intern (format nil "~a-LIST-TAILED-CHECKER" root-name)))
	   (actual-reclaim-x-cons
	     (intern (format nil "~a-1" reclaim-x-cons)))
	   (reclaim-x-cons-macro
	     (intern (format nil "RECLAIM-~a-CONS-MACRO" root-name)))
	   (reclaim-x-list
	     (intern (format nil "RECLAIM-~a-LIST" root-name)))
	   (actual-reclaim-x-list
	     (intern (format nil "~a-1" reclaim-x-list)))
	   (reclaim-x-list-macro
	     (intern (format nil "RECLAIM-~a-LIST-MACRO" root-name)))
	   (reclaim-x-list-given-tail
	     (intern (format nil "RECLAIM-~a-LIST-GIVEN-TAIL" root-name)))
	   (reclaim-x-list*
	     (intern (format nil "RECLAIM-~a-LIST*" root-name)))
	   (actual-reclaim-x-list*
	     (intern (format nil "~a-1" reclaim-x-list*)))
	   (reclaim-x-tree
	     (intern (format nil "RECLAIM-~a-TREE" root-name)))
	   (actual-reclaim-x-tree
	     (intern (format nil "~a-1" reclaim-x-tree)))
	   (delete-x-element
	     (intern (format nil "DELETE-~a-ELEMENT" root-name)))
	   (actual-delete-x-element
	     (intern (format nil "~a-1" delete-x-element)))
	   (delete-x-cons
	     (intern (format nil "DELETE-~a-CONS" root-name)))
	   (actual-delete-x-cons
	     (intern (format nil "~a-1" delete-x-cons)))
	   #+development
	   (report-outstanding-x-conses
	     (intern (format nil "REPORT-OUTSTANDING-~a-CONSES" root-name)))
	   
	   ;; The following bindings are for the implementation of x-push.
	   (x-car-variable
	     (intern (format nil "~a-CAR" root-name)))
	   (x-cdr-variable
	     (intern (format nil "~a-CDR" root-name)))
	   (x-push-variable
	     (intern (format nil "~a-PUSH" root-name)))
	   (x-cons-function-with-reversed-arguments
	     (intern (format nil "~a-CONS-WITH-REVERSED-ARGUMENTS" root-name)))
	   (modify-macro-for-x-push
	     (intern (format nil "~a-PUSH-MODIFY-MACRO" root-name)))
	   (x-push
	     (intern (format nil "~a-PUSH" root-name)))
	   #+SymScale
	   (x-push-atomic
	     (intern (format nil "~a-PUSH-ATOMIC" root-name)))
	   
	   ;; The following bindings are for the implementation of  x-pushnew.
	   (x-pushnew-variable
	     (intern (format nil "~a-PUSHNEW" root-name)))
	   (x-pushnew-test-variable
	     (intern (format nil "~a-PUSHNEW-TEST" root-name)))
	   (x-pushnew-key-variable
	     (intern (format nil "~a-PUSHNEW-KEY" root-name)))
	   (x-pushnew-key-result-variable
	     (intern (format nil "~a-PUSHNEW-KEY-RESULT" root-name)))
	   (x-pushnew-function-using-test 
	     (intern (format nil "~a-PUSHNEW-FUNCTION-USING-TEST" root-name)))
	   (x-pushnew-function-using-test-not
	     (intern (format nil "~a-PUSHNEW-FUNCTION-USING-TEST-NOT" root-name)))
	   (modify-macro-for-x-pushnew-using-test 
	     (intern (format nil "~a-MODIFY-MACRO-USING-TEST" root-name)))
	   (modify-macro-for-x-pushnew-using-test-not
	     (intern (format nil "~a-MODIFY-MACRO-USING-TEST-NOT" root-name)))
	   (x-pushnew
	     (intern (format nil "~a-PUSHNEW" root-name)))
	   
	   ;; The following bindings are for the implementation of x-pop.
	   (x-pop-variable			  
	     (intern
	       (format nil "~a-POP-STORE" root-name)))
	   (mutate-place-and-return-cdr
	     (intern (format nil "MUTATE-PLACE-AND-RETURN-~a-CDR" root-name)))
	   (modify-macro-for-x-pop
	     (intern (format nil "~a-POP-MODIFY-MACRO" root-name)))
	   (x-pop
	     (intern (format nil "~a-POP" root-name)))
	   #+SymScale
	   (x-pop-atomic
	     (intern (format nil "~a-POP-ATOMIC" root-name)))
	   
	   (module-name (or module-name? 'utilities1))
	   (x-cons-p (format-symbol "~a-CONS-P" root-name)))
      ;; The following declare notinline keeps the C compiler from blowing its
      ;; stack while trying to compile our huge backquote here.  This makes the
      ;; defconser macro a little slower, but who cares.  -jra 12/22/88
      `(progn

	 #+mtg2
	 (defvar ,x-cons-lock
	   (tx:make-recursive-lock :name (symbol-name ',x-cons-lock)))
	 
	 ;; The following lines are declarations of function types and
	 ;; side-effect free functions.  Note that all of the side-effect free
	 ;; declarations below are made under the special case where allocation
	 ;; functions can be declared side-effect free if the memory metering
	 ;; functions are left undeclared.  See documentation for
	 ;; declare-side-effect-free-function for more information about this
	 ;; special case.

	 (declare-simple-functions
	   ,actual-x-cons-function 2
	   ,actual-make-x-list 1
	   ,x-list-2-function 2
	   ,x-list-3-function 3
	   ,x-list-4-function 4
	   ,actual-copy-tree-using-x-conses 1
	   ,actual-copy-list-using-x-conses 1
	   ,actual-reclaim-x-cons 1
	   ,actual-reclaim-x-list 1
	   ,actual-reclaim-x-list* 1
	   ,actual-reclaim-x-tree 1
	   ,actual-delete-x-element 2
	   ,actual-delete-x-cons 2)

	 (declare-side-effect-free-functions
	   ,actual-x-cons-function
	   ,actual-make-x-list
	   ,x-list-2-function
	   ,x-list-3-function
	   ,x-list-4-function
	   ,actual-copy-tree-using-x-conses
	   ,actual-copy-list-using-x-conses)

	 #+SymScale
	 (declare-special-global ,available-x-conses-vector
				 ,available-x-conses-tail-vector
				 ,x-cons-counter-vector)

	 (def-system-variable ,available-x-conses ,module-name
	   nil nil t)
	 (def-system-variable ,available-x-conses-tail ,module-name
	   nil nil t)

	 #+SymScale ; per-thread memory pools with counter
	 (progn
	   (def-system-variable ,available-x-conses-vector ,module-name
	     (:funcall make-thread-array nil)
	     nil t)
	   (def-system-variable ,available-x-conses-tail-vector ,module-name
	     (:funcall make-thread-array nil)
	     nil t)
	   (def-system-variable ,x-cons-counter-vector ,module-name
	     (:funcall make-thread-array 0)
	     nil t))

	 ;; this is a global list to point to all conses allocated by current conser,
	 ;; it's not used normally, but how SymScale handle it?
	 ,@(if fully-checked?
	       `((def-system-variable ,conses-from-this-pool? ,module-name
		   nil nil t))
	       nil)

	 #+development
	 (declare-special-global ,x-car-marker)
	 #+development
	 (def-system-variable ,x-car-marker ,module-name
	   (:funcall make-cons-marker ,root-name)
	   nil t)
	 #+cons-checking
	 (cl:defmethod car-marker-by-pool-name ((pool (eql ',root-name))) ,x-car-marker)

	 ;; Note that none of the memory metering functions can be made
	 ;; side-effect free, since we allow the allocation functions to be
	 ;; side-effect free.

	 (def-system-variable ,x-cons-counter ,module-name
	   0 nil t)

	 (defun-simple ,outstanding-x-cons-counter-function ()
	   (#+mtg2 tx:with-lock-held #+mtg2 (,x-cons-lock) #-mtg2 progn
	   (-f ,x-cons-counter (length (the list ,available-x-conses)))))

	 (defun-simple ,x-memory-usage ()
	   (*f ,x-cons-counter (bytes-per-cons)))

	 (def-system-object-pool ,x-pool-name cons
	   ,x-cons-counter nil ,outstanding-x-cons-counter-function
	   ,x-memory-usage)

	 #-SymScale
	 (defun-simple ,replenish-x-cons-pool ()
	   (let ((new-conses (make-permanent-list-macro
			       cons-pool-conses-to-make-at-a-time)))
	     #+cons-checking
	     (loop for z on new-conses do (setf (car z) ,x-car-marker))
	     (incff ,x-cons-counter cons-pool-conses-to-make-at-a-time)
	     (if ,available-x-conses
		 (setf ,available-x-conses
		       (nconc (cdr new-conses)
			      ,available-x-conses))
		 (progn
		   (setf ,available-x-conses (cdr new-conses))
		   (setf ,available-x-conses-tail (last new-conses))))
	     new-conses))

	 #+SymScale
	 (defun-simple ,replenish-x-cons-pool ()
	   (let ((new-conses (make-permanent-list-macro
			       cons-pool-conses-to-make-at-a-time)))
	     (atomic-incff ,x-cons-counter cons-pool-conses-to-make-at-a-time)
	     (if (t-svref ,available-x-conses-vector)
		 (setf (t-svref ,available-x-conses-vector)
		       (nconc (cdr new-conses)
			      (t-svref ,available-x-conses-vector)))
		 (progn
		   (setf (t-svref ,available-x-conses-vector)
			 (cdr new-conses))
		   (setf (t-svref ,available-x-conses-tail-vector)
			 (last new-conses))))
	     ;; Update per-thread pool counter (no need to use atomic-incff)
	     (incff (t-svref ,x-cons-counter-vector)
		    (1-f cons-pool-conses-to-make-at-a-time))
	     new-conses))
	 
	 ,@(unless (eval-feature :no-macros)
	     `((note-non-resumable-function-call-macro
		 ',x-cons-macro ',actual-x-cons-macro ',x-cons-function
		 ',make-x-list ',x-list-macro ',x-list-function
		 ',copy-tree-using-x-conses ',copy-list-using-x-conses
		 ',reclaim-x-cons ',reclaim-x-list ',reclaim-x-tree
		 ',delete-x-element)))
	 
	 (defmacro ,x-cons-macro (car cdr)
	   #+development
	   `(,',x-cons-function ,car ,cdr)
	   #-development
	   `(,',actual-x-cons-macro ,car ,cdr))

	 (defmacro ,actual-x-cons-macro (car cdr)
	   (let ((,x-cons-variable (gensym)))
	     `(#+mtg2 tx:with-lock-held #+mtg2 (,',x-cons-lock) #-mtg2 progn
	     (let ((,,x-cons-variable (allocate-reclaimed-cons-internal
					 ,',available-x-conses
					 ,',available-x-conses-tail
					 #+SymScale
					 ,',available-x-conses-vector
					 #+SymScale
					 ,',available-x-conses-tail-vector)))
		(unless ,,x-cons-variable
		  (setq ,,x-cons-variable
			,',(if fully-checked?
			       `(replenish-checked-cons-pool
				  ',available-x-conses
				  ',available-x-conses-tail
				  ',x-cons-counter
				  ',conses-from-this-pool?)
			       `(,replenish-x-cons-pool))))
		(setf (car ,,x-cons-variable) ,car
		      (cdr ,,x-cons-variable) ,cdr)
		(note-allocate-cons ,,x-cons-variable ',',root-name)
		,,x-cons-variable))))

	 (defmacro ,x-cons-function (car cdr)
	   `(,',actual-x-cons-function ,car ,cdr))

	 ;; The following three groups of definitions implement pool-specific push
	 ;; and pop.  They are separate from the body of defconser lest we
	 ;; encounter space problems in ibuki.  (jh, 3/25/90, per 2/7/89 jra comment)

	 ,@(expansion-for-x-push
	     x-cons-function-with-reversed-arguments
	     x-car-variable
	     x-cdr-variable
	     actual-x-cons-function
	     modify-macro-for-x-push
	     x-push-variable
	     x-push
	     #+SymScale x-push-atomic
	     #+mtg2 x-cons-lock)

	 ,@(expansion-for-x-pushnew
	     x-pushnew-function-using-test
	     x-car-variable
	     x-cdr-variable
	     x-pushnew-test-variable
	     x-pushnew-key-variable
	     x-pushnew-key-result-variable
	     actual-x-cons-function
	     x-pushnew-function-using-test-not
	     modify-macro-for-x-pushnew-using-test
	     x-pushnew-variable
	     modify-macro-for-x-pushnew-using-test-not
	     x-pushnew
	     #+mtg2 x-cons-lock)

	 ,@(expansion-for-x-pop
	     mutate-place-and-return-cdr
	     x-cons-variable
	     x-pop-variable
	     reclaim-x-cons-macro
	     modify-macro-for-x-pop
	     x-pop
	     #+SymScale x-pop-atomic
	     #+mtg2 x-cons-lock)

	 (defun-simple ,actual-x-cons-function (car cdr)
	   (,actual-x-cons-macro car cdr))

	 ,@(expand-make-x-list-macro-and-replenish-list-pool
	     root-name
	     make-x-list-macro
	     replenish-x-list-pool
	     available-x-conses
	     #+SymScale available-x-conses-vector
	     available-x-conses-tail
	     #+SymScale available-x-conses-tail-vector
	     x-cons-counter
	     #+SymScale x-cons-counter-vector
	     conses-from-this-pool?
	     fully-checked?
	     #+cons-checking x-car-marker\
	     #+mtg2 x-cons-lock)

	 (defmacro ,make-x-list (count)
	   `(,',actual-make-x-list ,count))

	 (defun-simple ,actual-make-x-list (count)
	   (,make-x-list-macro count))
	 (defmacro ,x-list-macro (&rest elements)
	   (cond ((null elements)
		  nil)
		 ((null (cdr elements))
		  `(,',actual-x-cons-macro ,(car elements) nil))
		 (t
		  `(set-list-contents
		     (,',make-x-list-macro ,(length elements))
		     ,@elements))))

	 (defun-simple ,x-list-2-function (first second)
	   (set-list-contents (,make-x-list-macro 2)
			      first second))

	 (defun-simple ,x-list-3-function (first second third)
	   (set-list-contents (,make-x-list-macro 3)
			      first second third))

	 (defun-simple ,x-list-4-function (first second third fourth)
	   (set-list-contents (,make-x-list-macro 4)
			      first second third fourth))
	 (defun-simple ,x-list-trace-hook (a-list)
	   a-list)
	 #+development
	 (defmacro ,x-list-function (&rest elements)
	   (let ((result-name (gensym)))
	     `(let (,result-name)
		(setq ,result-name
		      ,(cond ((null elements)
			     nil)
			    ((null (cdr elements))
			     `(,',x-cons-function ,(car elements) nil))
			    ((null (cddr elements))
			     `(,',x-list-2-function
				   ,(first elements) ,(second elements)))
			    ((null (cdddr elements))
			     `(,',x-list-3-function
				   ,(first elements) ,(second elements) ,(third elements)))
			    ((null (cdr (cdddr elements)))
			    `(,',x-list-4-function
				   ,(first elements) ,(second elements) ,(third elements)
				   ,(fourth elements)))
			    (t
			     `(set-list-contents
				(,',make-x-list ,(length elements))
				,@elements))))
		(,',x-list-trace-hook ,result-name))))
	 #-development
	 (defmacro ,x-list-function (&rest elements)
	   (cond ((null elements)
		  nil)
		 ((null (cdr elements))
		  `(,',x-cons-function ,(car elements) nil))
		 ((null (cddr elements))
		  `(,',x-list-2-function
		    ,(first elements) ,(second elements)))
		 ((null (cdddr elements))
		  `(,',x-list-3-function
		    ,(first elements) ,(second elements) ,(third elements)))
		 ((null (cdr (cdddr elements)))
		  `(,',x-list-4-function
		    ,(first elements) ,(second elements) ,(third elements)
		    ,(fourth elements)))
		 (t
		  `(set-list-contents
		     (,',make-x-list ,(length elements))
		     ,@elements))))

	 (defmacro ,copy-tree-using-x-conses (tree?)
	   `(,',actual-copy-tree-using-x-conses ,tree?))

	 (defun-simple ,actual-copy-tree-using-x-conses (tree?)
	   (#+mtg2 tx:with-lock-held #+mtg2 (,x-cons-lock) #-mtg2 progn
	   (if (not (consp tree?))
	       tree?
	       (loop with new-list = (,actual-x-cons-macro
				      (,copy-tree-using-x-conses (car tree?))
				      (cdr tree?))
		     with last-new-cons = new-list
		     with current-copy-position = (cdr tree?)
		     until (atom current-copy-position)
		     do (setf (cdr last-new-cons)
			      (,actual-x-cons-macro
			       (,copy-tree-using-x-conses
				(car current-copy-position))
			       (cdr current-copy-position)))
			(setf last-new-cons (cdr last-new-cons))
			(setf current-copy-position
			      (cdr current-copy-position))
		     finally (return new-list)))))

	 (defmacro ,copy-list-using-x-conses (list?)
	   `(,',actual-copy-list-using-x-conses ,list?))

	 (defun-simple ,actual-copy-list-using-x-conses (list?)
	   (#+mtg2 tx:with-lock-held #+mtg2 (,x-cons-lock) #-mtg2 progn
	   (if (not (consp list?))
	       list?
	       (loop with new-list = (,actual-x-cons-macro (car list?) (cdr list?))
		     with last-new-cons = new-list
		     with current-copy-position = (cdr list?)
		     until (atom current-copy-position)
		     do (setf (cdr last-new-cons)
			      (,actual-x-cons-macro
			       (car current-copy-position)
			       (cdr current-copy-position)))
			(setf last-new-cons (cdr last-new-cons))
			(setf current-copy-position (cdr current-copy-position))
		     finally (return new-list)))))

	 ;; Consider making this more efficient and less prone to stack
	 ;; overflow by looping in the cdr direction.

	 #+development
	 (defun ,x-cons-checker (,x-cons-variable)
	   (if (eq (car ,x-cons-variable) ,x-car-marker)
	       (error ,x-error-message))
	   (if (eq ,x-cons-variable managed-float-unique-marker)
	       (error ,x-float-marker-message))
	   (if (eq ,x-cons-variable strange-cons)
	       (error ,x-strange-cons-message))
	   (setf (car ,x-cons-variable) ,x-car-marker)
	   nil)

	 (def-substitution-macro ,reclaim-x-cons-macro (,x-cons-variable)
	   (#+mtg2 tx:with-lock-held #+mtg2 (,x-cons-lock) #-mtg2 progn
	   ,@(if fully-checked?
		 `((cond ((loop for reclaimed-cons on ,available-x-conses
				for fast-cons = (cdr ,available-x-conses)
					      then (cddr fast-cons)
				do
			    (if (eq reclaimed-cons fast-cons)
				(error "~a contains an infinite list."
				       ',available-x-conses))
			    (if (eq reclaimed-cons ,x-cons-variable)
				(return t)))
			  (error "Cons being doubly reclaimed into the ~a pool."
				 ',root-name))
			 ((not (memq ,x-cons-variable ,conses-from-this-pool?))
			  (cerror "go on"
				  "Cons being given back to ~a pool which didn't come from here."
				  ',root-name))))
		 nil)
	   (note-reclaim-cons ,x-cons-variable ',root-name)
	   #+development
	   (,x-cons-checker ,x-cons-variable)
	   #+development
	   (setf (car ,x-cons-variable) ,x-car-marker)
	   (reclaim-list-internal ,x-cons-variable ,x-cons-variable
				  ,available-x-conses
				  ,available-x-conses-tail
				  #+SymScale ,available-x-conses-vector
				  #+SymScale ,available-x-conses-tail-vector
				  #+SymScale ,x-cons-counter-vector)
	   nil))

	 (defmacro ,reclaim-x-cons (,x-cons-variable)
	   `(,',actual-reclaim-x-cons ,,x-cons-variable))

	 (defun-simple ,actual-reclaim-x-cons (,x-cons-variable)
	   (,reclaim-x-cons-macro ,x-cons-variable))

	 #+development
	 (defun ,x-list-checker (list-to-check)
	   (loop for cons-to-check = list-to-check then (cdr cons-to-check)
		 until (endp cons-to-check)
		 do
	     (if (eq cons-to-check managed-float-unique-marker)
		 (error ,x-float-marker-message))
	     (if (eq (car cons-to-check) ,x-car-marker)
		 (error ,x-error-message))
	     (if (eq cons-to-check strange-cons)
		 (error ,x-strange-cons-message))
	     (setf (car cons-to-check) ,x-car-marker))
	   nil)

	 ,(expand-reclaim-x-list-macro
	    root-name
	    reclaim-x-list-macro
	    x-list-variable
	    available-x-conses
	    #+SymScale available-x-conses-vector
	    available-x-conses-tail
	    #+SymScale available-x-conses-tail-vector
	    conses-from-this-pool?
	    fully-checked?
	    #+SymScale x-cons-counter-vector
	    #+development x-list-checker
	    #+development x-car-marker
	    #+mtg2 x-cons-lock)

	 ,@(expand-reclaim-x-list-given-tail
	     root-name
	     reclaim-x-list-given-tail
	     x-list-variable x-tail-variable
	     available-x-conses
	     #+SymScale available-x-conses-vector
	     available-x-conses-tail
	     #+SymScale available-x-conses-tail-vector
	     conses-from-this-pool?
	     fully-checked?
	     x-cons-variable
	     #+SymScale
	     x-cons-counter-vector
	     #+development x-list-checker-given-tail
	     #+development x-float-marker-message
	     #+development x-error-message
	     #+development x-car-marker
	     #+mtg2 x-cons-lock)

	 (defmacro ,reclaim-x-list (,x-list-variable)
	   `(,',actual-reclaim-x-list ,,x-list-variable))
	 (defun-simple ,actual-reclaim-x-list (,x-list-variable)
	   (,reclaim-x-list-macro ,x-list-variable))

	 (defmacro ,reclaim-x-list* (,x-list-variable)
	   `(,',actual-reclaim-x-list* ,,x-list-variable))

	 (defun-simple ,actual-reclaim-x-list* (,x-list-variable)
	   (#+mtg2 tx:with-lock-held #+mtg2 (,x-cons-lock) #-mtg2 progn
	   (when (consp ,x-list-variable)
	     (setf (cdr (last ,x-list-variable)) nil)
	     (,reclaim-x-list-macro ,x-list-variable))))
	 (defmacro ,reclaim-x-tree (tree)
	   `(,',actual-reclaim-x-tree ,tree))

	 (defun-simple ,actual-reclaim-x-tree (tree)
	   (#+mtg2 tx:with-lock-held #+mtg2 (,x-cons-lock) #-mtg2 progn
	   (when (consp tree)
	     (loop with e = tree
		   do (,actual-reclaim-x-tree (car-of-cons e))
		      (let ((e2 (cdr-of-cons e)))
			(if (consp e2)
			    (setq e e2)
			    (progn (,reclaim-x-list-given-tail tree e) (loop-finish))))))))

	 (defmacro ,delete-x-element (element ,x-list-variable)
	   `(,',actual-delete-x-element ,element ,,x-list-variable))

	 (defun-simple ,actual-delete-x-element (element ,x-list-variable)
	   (#+mtg2 tx:with-lock-held #+mtg2 (,x-cons-lock) #-mtg2 progn
	   (if ,x-list-variable
	       (if (eq element (car-of-cons ,x-list-variable))
		   (prog1
		     (cdr ,x-list-variable)
		     (,reclaim-x-cons-macro ,x-list-variable))		 
		   (loop as l-trailer? = nil then l
			 as l on ,x-list-variable
			 when (eq element (car-of-cons l))
			   do (setf (cdr l-trailer?) (cdr-of-cons l))
			      (,reclaim-x-cons-macro l)
			      (loop-finish)
			 finally
			   (return ,x-list-variable)))
	       nil)))

	 (defmacro ,delete-x-cons (,x-cons-variable ,x-list-variable)
	   `(,',actual-delete-x-cons ,,x-cons-variable ,,x-list-variable))

	 (defun-simple ,actual-delete-x-cons (,x-cons-variable ,x-list-variable)
	   (#+mtg2 tx:with-lock-held #+mtg2 (,x-cons-lock) #-mtg2 progn
	   (prog1
	     (if (eq ,x-cons-variable ,x-list-variable)
		 (cdr ,x-list-variable)
		 (loop as l-trailer? = nil then l
		       as l on ,x-list-variable
		       when (eq l ,x-cons-variable)
			 do (setf (cdr l-trailer?) (cdr l))
			    (return ,x-list-variable)))
	     (,reclaim-x-cons ,x-cons-variable))))


	 #+development
	 (defun ,report-outstanding-x-conses ()
	   (format t "~%The number of outstanding ~a conses is ~D."
		   ',root-name
		   (,outstanding-x-cons-counter-function)))

	 ,(if fully-checked?
	      `(defun ,x-cons-p (cons)
		 (if (memq cons ,conses-from-this-pool?)
		     t)))

	 ,(if fully-checked?
	      `(pushnew ',conses-from-this-pool? all-cons-pools))

	 #+cons-checking
	 (cons-checking-enable-for-a-new-pool ',root-name ',x-pool-name 'cons nil)         

	 ',root-name))))

;; NOTE: SymScale must enable this feature to prevent ABA problem as much as possible:
;; newly reclaimed conses do not get re-used immediately, so it's pushed at the end of
;; local memory pool. And if current thread need to move some conses back to main memory
;; pool, won't be the current reclaimed one.

#+SymScale
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :use-queue-allocation-for-consing *features*))

(defmacro #+SymScale
	  reclaim-list-internal-1
	  #-SymScale
	  reclaim-list-internal (x-list-variable x-tail-variable
				 available-x-conses
				 available-x-conses-tail)
  #-use-queue-allocation-for-consing
  (declare (ignore available-x-conses-tail))
  #-use-queue-allocation-for-consing
  `(progn
     (setf (cdr ,x-tail-variable) ,available-x-conses)
     (setf ,available-x-conses ,x-list-variable)
     nil)
  #+use-queue-allocation-for-consing
  `(progn
     (cond (,available-x-conses-tail
	    (setf (cdr ,available-x-conses-tail) ,x-list-variable)
	    (setf ,available-x-conses-tail ,x-tail-variable))
	   (t
	    (setf ,available-x-conses ,x-list-variable)
	    (setf ,available-x-conses-tail ,x-tail-variable)))
     (setf (cdr ,x-tail-variable) nil)))

;;; (also see `allocate-reclaimed-cons-internal')

;;; Also see `allocate-reclaimed-cons-internal' (SymScale).
  ;; SS NOTES: reclaimed conses should be collected into per-thread pools first,
  ;; and increase related counter.
  ;;
  ;; TODO: Then check the counter, if too big, current
  ;; thread should move some (or all) conses back to global pool for used by other threads.
#|
1. count the number of conses between x-list-variable and x-tail-variable.
   use length-of-x-list directly if it's not zero.
2. if x-cons-counter-vector of current thread is greater than 2*1024, move them back to main pool.
   and clear the counter of current thread pool.  CAS is involved here.
3. reclaim x-list-variable into local thread pool (using unmodified code below, no CAS) and
   increase the counter with length-of-x-list.
|#

#+SymScale
(defmacro reclaim-list-internal (x-list-variable x-tail-variable
				 available-x-conses		; global pool head
				 available-x-conses-tail	; global pool tail
				 available-x-conses-vector	; thread-local pool head
				 available-x-conses-tail-vector ; thread-local pool tail
				 x-cons-counter-vector)		; thread-local pool counter
  (declare (ignore available-x-conses
		   available-x-conses-tail
		   x-cons-counter-vector))
  `(reclaim-list-internal-1 ,x-list-variable
			    ,x-tail-variable
			    (t-svref ,available-x-conses-vector)
			    (t-svref ,available-x-conses-tail-vector)))

(eval-when (:compile-toplevel :load-toplevel :execute)
;(pushnew :keep-reserve-of-conses *features*)
)

(defmacro #+SymScale
	  allocate-reclaimed-cons-internal-1
	  #-SymScale
	  allocate-reclaimed-cons-internal (available-x-conses
					    available-x-conses-tail)
  #-use-queue-allocation-for-consing
  (declare (ignore available-x-conses-tail))
  `(let ((new-cons ,available-x-conses))
     (when (progn
	     #-keep-reserve-of-conses new-cons
	     #+keep-reserve-of-conses (nthcdr cons-pool-conses-to-make-at-a-time new-cons))
       (setf ,available-x-conses (cdr-of-cons new-cons))
       #+use-queue-allocation-for-consing
       (unless ,available-x-conses
	 (setf ,available-x-conses-tail nil))
       new-cons)))

;;; (also see `reclaim-list-internal')
;;;
;;; 1. allocate from thread-local pool first. (no need CAS)
;;; 2. if no cons from thread local pool, steal some from main pool (1024 each time) (CAS here)
;;; 3. allocate from thread local pool. again, or return nil..

#+SymScale
(defmacro allocate-reclaimed-cons-internal (available-x-conses
					    available-x-conses-tail
					    available-x-conses-vector
					    available-x-conses-tail-vector)
  (declare (ignore available-x-conses available-x-conses-tail))
  (let ((new-cons (gensym)))
    `(let ((,new-cons (allocate-reclaimed-cons-internal-1
			(t-svref ,available-x-conses-vector)
			(t-svref ,available-x-conses-tail-vector))))
       ,new-cons)))

(defmacro #+SymScale
	  allocate-reclaimed-list-internal-1
	  #-SymScale
	  allocate-reclaimed-list-internal (x-tail-variable
					    available-x-conses
					    available-x-conses-tail)
  #-use-queue-allocation-for-consing
  (declare (ignore available-x-conses-tail))
  `(prog1 ,available-x-conses
     (setf ,available-x-conses (cdr ,x-tail-variable))
     #+use-queue-allocation-for-consing
     (unless ,available-x-conses
       (setf ,available-x-conses-tail nil))
     (setf (cdr ,x-tail-variable) nil)))

#+SymScale
(defmacro allocate-reclaimed-list-internal (x-tail-variable
					    available-x-conses
					    available-x-conses-vector
					    available-x-conses-tail
					    available-x-conses-tail-vector)
  (declare (ignore available-x-conses
		   available-x-conses-tail))
  `(allocate-reclaimed-list-internal-1 ,x-tail-variable
				       (t-svref ,available-x-conses-vector)
				       (t-svref ,available-x-conses-tail-vector)))

(defmacro with-reclaimed-list-internal
    ((last-cons length-minus-one
		available-x-conses
		#+SymScale available-x-conses-vector
		available-x-conses-tail
		#+SymScale available-x-conses-tail-vector
		replenish-x-list-pool)
     &body body)
  (declare (ignore available-x-conses-tail
		   #+SymScale available-x-conses
		   #+SymScale available-x-conses-tail-vector))
  `(loop for ,last-cons = (nthcdr-macro ,length-minus-one
					#-SymScale ,available-x-conses
					#+SymScale (t-svref ,available-x-conses-vector))
	 until (progn
		 #-keep-reserve-of-conses ,last-cons
		 #+keep-reserve-of-conses (nthcdr cons-pool-conses-to-make-at-a-time ,last-cons))
	 do (,replenish-x-list-pool ,length-minus-one)
	 finally (return (progn ,@body))))



;; The expansions for x-push, x-pushnew, and x-pop were extracted from the body of
;; defconser so as to have minimal impact on its size.  This precaution was taken
;; after reading the 2/7/89 comment from jra.  (jh, 3/25/90)

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro expansion-for-x-push
		 (x-cons-function-with-reversed-arguments
		   x-car-variable
		   x-cdr-variable
		   actual-x-cons-function
		   modify-macro-for-x-push
		   x-push-variable
		   x-push
		   #+SymScale x-push-atomic
		   #+mtg2 x-cons-lock)
  `((defmacro ,x-cons-function-with-reversed-arguments (new-cdr new-car)
      (let ((,x-car-variable (make-symbol "CAR"))
	    (,x-cdr-variable (make-symbol "CDR")))
	`(let ((,,x-car-variable ,new-car)	       ;ensures correct order
	       (,,x-cdr-variable ,new-cdr))	       ; of evaluation
	   (,',actual-x-cons-function ,,x-car-variable ,,x-cdr-variable))))

    (define-modify-macro ,modify-macro-for-x-push (,x-push-variable)
      ,x-cons-function-with-reversed-arguments)
    
    (defmacro ,x-push (thing place)
      (if (symbolp place)
	  `(setq ,place (,',actual-x-cons-function ,thing ,place))
	  `(#+mtg2 tx:with-lock-held #+mtg2 (,',x-cons-lock) #-mtg2 progn
	  (,',modify-macro-for-x-push ,place ,thing))))

    ;; This simple version cannot deal with places with side-effects
    #+SymScale
    (defmacro ,x-push-atomic (thing place)
      (let ((old (make-symbol "OLD-VALUE"))
	    (new (make-symbol "NEW-VALUE")))
	`(let* ((,new (,',actual-x-cons-function ,thing nil)))
	   (loop for ,old = ,place
		 do (setf (cdr ,new) ,old)
		 until (compare-and-swap ,place ,old ,new)
		 finally (return ,new)))))))
) ;end of eval-when




(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro expansion-for-x-pushnew
		 (x-pushnew-function-using-test
		   x-car-variable
		   x-cdr-variable
		   x-pushnew-test-variable
		   x-pushnew-key-variable
                   x-pushnew-key-result-variable
		   actual-x-cons-function
		   x-pushnew-function-using-test-not
		   modify-macro-for-x-pushnew-using-test
		   x-pushnew-variable
		   modify-macro-for-x-pushnew-using-test-not
		   x-pushnew
		   #+mtg2 x-cons-lock)
  `((defmacro ,x-pushnew-function-using-test 
	      (cdr car test-function key-function)
      (let ((,x-car-variable (make-symbol "CAR"))
	    (,x-cdr-variable (make-symbol "CDR"))
	    (,x-pushnew-test-variable (make-symbol "TEST"))
	    (,x-pushnew-key-variable (make-symbol "KEY"))
	    (,x-pushnew-key-result-variable (make-symbol "KEY-RESULT")))
	`(let* ((,,x-car-variable ,car)	       ;use the let binding to
		(,,x-cdr-variable ,cdr)	       ; ensure correct order
		,@(unless (constantp test-function)
		    `((,,x-pushnew-test-variable      ; of evaluation
			  ,test-function)))
		,@(unless (constantp key-function)
		    `((,,x-pushnew-key-variable
			  ,key-function)))
		(,,x-pushnew-key-result-variable
		    ,(cond ((null key-function)
			    ,x-car-variable)
			   ((constantp key-function)
			    `(,(eval key-function) ,,x-car-variable))
			   (t
			    `(funcall ,,x-pushnew-key-variable
				      ,,x-car-variable)))))
	   (if (loop for x-element 
			 in ,,x-cdr-variable
		     thereis
		     (,@(if (constantp test-function)
			    `(,(eval test-function))
			    `(funcall ,,x-pushnew-test-variable))
			,,x-pushnew-key-result-variable
			,(cond ((null key-function)
				`x-element)
			       ((constantp key-function)
				`(,(eval key-function) x-element))
			       (t
				`(funcall ,,x-pushnew-key-variable
					  x-element)))))
	       ,,x-cdr-variable
	       (,',actual-x-cons-function
		    ,,x-car-variable
		    ,,x-cdr-variable)))))

    (defmacro ,x-pushnew-function-using-test-not
	      (cdr car test-not-function key-function)
      (let ((,x-car-variable (make-symbol "CAR"))
	    (,x-cdr-variable (make-symbol "CDR"))
	    (,x-pushnew-test-variable (make-symbol "TEST"))
	    (,x-pushnew-key-variable (make-symbol "KEY"))
	    (,x-pushnew-key-result-variable (make-symbol "KEY-RESULT")))
	`(let* ((,,x-car-variable ,car)	       ;use the let binding to
		(,,x-cdr-variable ,cdr)	       ; ensure correct order
		,@(unless (constantp test-not-function)
		    `((,,x-pushnew-test-variable      ; of evaluation
			  ,test-not-function)))
		,@(unless (constantp key-function)
		    `((,,x-pushnew-key-variable
			  ,key-function)))
		(,,x-pushnew-key-result-variable
		    ,(cond ((null key-function)
			    ,x-car-variable)
			   ((constantp key-function)
			    `(,(eval key-function) ,,x-car-variable))
			   (t
			    `(funcall ,,x-pushnew-key-variable
				      ,,x-car-variable)))))
	   (if (loop for x-element 
			 in ,,x-cdr-variable
		     thereis
		       (not (,@(if (constantp test-not-function)
				   `(,(eval test-not-function))
				   `(funcall ,,x-pushnew-test-variable))
			       ,,x-pushnew-key-result-variable
			       ,(cond ((null key-function)
				       `x-element)
				      ((constantp key-function)
				       `(,(eval key-function) x-element))
				      (t
				       `(funcall ,,x-pushnew-key-variable
					  x-element))))))
	       ,,x-cdr-variable
	       (,',actual-x-cons-function
		,,x-car-variable
		,,x-cdr-variable)))))

    (define-modify-macro ,modify-macro-for-x-pushnew-using-test
			 (,x-pushnew-variable             
			  ,x-pushnew-test-variable 
			  ,x-pushnew-key-variable)
      ,x-pushnew-function-using-test)

    (define-modify-macro ,modify-macro-for-x-pushnew-using-test-not
			 (,x-pushnew-variable 
			  ,x-pushnew-test-variable	       ;[sic, jh, 3/25/90]
			  ,x-pushnew-key-variable)
      ,x-pushnew-function-using-test-not)

    (defmacro ,x-pushnew (thing place
			  &key (test ''eql test-supplied-p) test-not key)
      (cond (test-not
	     (when test-supplied-p
	       (cerror "Use value provided for :TEST-NOT."
		       "Can't use both :TEST and :TEST-NOT in ~a"
		       ',x-pushnew))
	     `(#+mtg2 tx:with-lock-held #+mtg2 (,',x-cons-lock) #-mtg2 progn
	     (,',modify-macro-for-x-pushnew-using-test-not
	       ,place
	       ,thing
	       ,test-not
	       ,key)))
	    (t 
	     `(#+mtg2 tx:with-lock-held #+mtg2 (,',x-cons-lock) #-mtg2 progn
	     (,',modify-macro-for-x-pushnew-using-test
	       ,place
	       ,thing
	       ,test
	       ,key)))))))
) ; end of eval-when


(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro expansion-for-x-pop
		 (mutate-place-and-return-cdr
		   x-cons-variable
		   x-pop-variable
		   reclaim-x-cons-macro
		   modify-macro-for-x-pop
		   x-pop
		   #+SymScale x-pop-atomic
		   #+mtg2 x-cons-lock)
  `((defmacro ,mutate-place-and-return-cdr (place)
      (let ((,x-cons-variable (make-symbol "CONS"))
	    (next-cons-variable (make-symbol "NEXT-CONS")))
	`(let ((,,x-cons-variable ,place))
	   (when ,,x-cons-variable
	     (setq ,',x-pop-variable (car-of-cons ,,x-cons-variable))
	     (let ((,next-cons-variable (cdr-of-cons ,,x-cons-variable)))
	       (,',reclaim-x-cons-macro ,,x-cons-variable)
	       ,next-cons-variable)))))

    (define-modify-macro ,modify-macro-for-x-pop ()
      ,mutate-place-and-return-cdr)

    (defmacro ,x-pop (place)
      `(#+mtg2 tx:with-lock-held #+mtg2 (,',x-cons-lock) #-mtg2 progn
      (let ((,',x-pop-variable nil))
	 (,',modify-macro-for-x-pop ,place)
	 ,',x-pop-variable)))

    ;; This simple version cannot deal with places with side-effects, it's taken from
    ;; SBCL source code, but enhanced to support NIL places.
    #+SymScale
    (defmacro ,x-pop-atomic (place)
      (let ((old (make-symbol "OLD-VALUE"))
	    (new (make-symbol "NEW-VALUE")))
	`(loop for ,old = ,place
	       while ,old
	       for ,new = (cdr-of-cons ,old)
	       until (compare-and-swap ,place ,old ,new)
	       finally (return (when ,old
				 (prog1 (car-of-cons ,old)
				   (,',reclaim-x-cons-macro ,old)))))))))
) ;end of eval-when

;; Today we changed the macro above to not require that x-pop-variable be
;; special.  Since the modify macro's third argument can name a macro, we can
;; be sure that the expansion of mutate-place-and-return-cdr is within the
;; lexical scope of the binding of x-pop-variable in the expansion of x-pop.
;; At first we thought that the mutate-place-and-return-cdr had to be a
;; function, which led us down the garden path.  -jra 5/11/92




;;; The function for macro `expand-make-x-list-macro-and-replenish-list-pool' has
;;; been split out of defconser to make it smaller.  -jra 3/27/91

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro expand-make-x-list-macro-and-replenish-list-pool
    (root-name
      make-x-list-macro
      replenish-x-list-pool
      available-x-conses
      #+SymScale available-x-conses-vector
      available-x-conses-tail
      #+SymScale available-x-conses-tail-vector
      x-cons-counter
      #+SymScale x-cons-counter-vector
      conses-from-this-pool?
      fully-checked?
      #+cons-checking x-cons-marker
      #+mtg2 x-cons-lock)
  #+SymScale
  (declare (ignore x-cons-counter-vector))
  `((defun-simple ,replenish-x-list-pool (conses-needed-minus-one)
      ,(if fully-checked?
	   `(replenish-checked-cons-pool-list
	      ',available-x-conses
	      ',available-x-conses-tail
	      ',x-cons-counter
	      ',conses-from-this-pool?
	      conses-needed-minus-one)
	   `(let* ((conses-needed (+f conses-needed-minus-one 1))
		   (new-conses-count
		     (ceilingf-positive
		       conses-needed
		       cons-pool-conses-to-make-at-a-time))
		   (new-conses (make-permanent-list-macro
				 new-conses-count)))
	      #+cons-checking
	      (loop for z on new-conses do (setf (car z) ,x-cons-marker))
	      (declare (type fixnum conses-needed new-conses-count))
	      (if #-SymScale ,available-x-conses
		  #+SymScale (t-svref ,available-x-conses-vector)
		  (setf #-SymScale ,available-x-conses
			#+SymScale (t-svref ,available-x-conses-vector)
			(nconc new-conses
			       #-SymScale ,available-x-conses
			       #+SymScale (t-svref ,available-x-conses-vector)))
		  (progn
		    (setf #-SymScale ,available-x-conses
			  #+SymScale (t-svref ,available-x-conses-vector)
			  new-conses)
		    #+use-queue-allocation-for-consing
		    (setf #-SymScale ,available-x-conses-tail
			  #+SymScale (t-svref ,available-x-conses-tail-vector)
			  (last new-conses))))
	      (atomic-incff ,x-cons-counter new-conses-count)
	      nil)))
    
    (defmacro ,make-x-list-macro (count)
      (let* ((last-cons (gensym))
	     (length-minus-one (gensym))
	     (new-cons (gensym))
	     (length-constant? (if (constantp count)
				   (eval count)
				   nil)))
	(when length-constant?
	  (setq length-minus-one (- length-constant? 1)))
	(cond
	  ((or (null length-constant?)
	       (> length-constant? 0))
	   `(#+mtg2 tx:with-lock-held #+mtg2 (,',x-cons-lock) #-mtg2 progn
	   (let (,@(when (not length-constant?)
		      `((,length-minus-one (-f ,count 1)))))
	      (,@(if length-constant?
		     '(progn)
		     `(when (>=f ,length-minus-one 0)))
		 (with-reclaimed-list-internal
		     (,last-cons ,length-minus-one
				 ,',available-x-conses
				 #+SymScale ,',available-x-conses-vector
				 ,',available-x-conses-tail
				 #+SymScale ,',available-x-conses-tail-vector
				 ,',replenish-x-list-pool)
		   (when (and #-development (debugging-consing-p))
		     (loop for ,new-cons = #-SymScale ,',available-x-conses
					   #+SymScale (t-svref ,',available-x-conses-vector)
					 then (cdr ,new-cons)
			   do
		       (note-allocate-cons ,new-cons ',',root-name)
		       ;; In development, clear the cars so we don't get
		       ;; spurious cons corruption messages.

		       ;; but under test, put cons-marker there intentionally
		       #+development
		       (setf (car ,new-cons)
			     #-cons-checking nil
			     #+cons-checking ,',x-cons-marker)
			   until (eq ,new-cons ,last-cons)))
		   (allocate-reclaimed-list-internal
		     ,last-cons
		     ,',available-x-conses
		     #+SymScale ,',available-x-conses-vector
		     ,',available-x-conses-tail
		     #+SymScale ,',available-x-conses-tail-vector))))))
	  ;; Else, there is a length-constant, and it is less than or equal
	  ;; to zero, so this macro need return nil.
	  (t nil)))) )))




;;; The function for macro expand-reclaim-x-list has been split out of the body
;;; of defconser to make defconser smaller.  It could not be compiled in some
;;; Lisps.  -jra 2/7/89

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro expand-reclaim-x-list-macro
    (root-name
      reclaim-x-list-macro
      x-list-variable
      available-x-conses
      #+SymScale available-x-conses-vector
      available-x-conses-tail
      #+SymScale available-x-conses-tail-vector
      conses-from-this-pool?
      fully-checked?
      #+SymScale x-cons-counter-vector
      #+development x-list-checker
      #+development x-car-marker
      #+mtg2 x-cons-lock)
  `(defun-substitution-macro ,reclaim-x-list-macro (,x-list-variable)
     (#+mtg2 tx:with-lock-held #+mtg2 (,x-cons-lock) #-mtg2 progn
     ,@(if fully-checked?
	   `((cond ((loop named double-reclaim-checker
			  for reclaimed-cons on ,available-x-conses
			  for fast-reclaimed = (cdr ,available-x-conses)
					     then (cddr fast-reclaimed)
			  do
		      (if (eq reclaimed-cons fast-reclaimed)
			  (error "~a contains a circular list."
				 ',available-x-conses))
		      (loop for cons-in-list on ,x-list-variable
			    for fast-cons-in-list = (cdr ,x-list-variable)
						  then (cddr fast-cons-in-list)
			    do
			(if (eq cons-in-list fast-cons-in-list)
			    (error "~a called on a circular list."
				   ',reclaim-x-list-macro))
			(if (eq cons-in-list reclaimed-cons)
			    (return-from double-reclaim-checker t))))
		    (error "Cons being doubly reclaimed into the ~a pool."
			   ',root-name))
		   ((loop for cons-in-list on ,x-list-variable
			  do
		      (if (not (memq cons-in-list ,conses-from-this-pool?))
			  (return t)))
		    (cerror "go on"
			    "Cons being given back to ~a pool which didn't come from here."
			    ',root-name))))
	   nil)

     #+development
     (,x-list-checker ,x-list-variable)

     (when ,x-list-variable
       (loop for last = ,x-list-variable then next?
	     for next? = (cdr-of-cons last)
	     until (null next?)
	     do
	 (note-reclaim-cons last ',root-name)
	 #+development
	 (setf (car last) ,x-car-marker)
	     finally
	       (note-reclaim-cons last ',root-name)
	       #+development
	       (setf (car last) ,x-car-marker)
	       (reclaim-list-internal ,x-list-variable last
				      ,available-x-conses
				      ,available-x-conses-tail
				      #+SymScale ,available-x-conses-vector
				      #+SymScale ,available-x-conses-tail-vector
				      #+SymScale ,x-cons-counter-vector))
       nil)))))


;;; The function for macro expand-reclaim-x-list-given-tail has been split out
;;; of the body of defconser to make defconser small enough for Ibuki to
;;; compile.  -jra 2/7/89

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro expand-reclaim-x-list-given-tail
    (root-name
      reclaim-x-list-given-tail
      x-list-variable x-tail-variable
      available-x-conses
      #+SymScale available-x-conses-vector
      available-x-conses-tail
      #+SymScale available-x-conses-tail-vector
      conses-from-this-pool?
      fully-checked?
      x-cons-variable
      #+SymScale x-cons-counter-vector
      #+development x-list-checker-given-tail
      #+development x-float-marker-message
      #+development x-error-message
      #+development x-car-marker
      #+mtg2 x-cons-lock)
  `(#+development
      (defun ,x-list-checker-given-tail (,x-list-variable ,x-tail-variable)
	(loop with ,x-cons-variable = ,x-list-variable
	      do
	  (if (eq ,x-cons-variable managed-float-unique-marker)
	      (error ,x-float-marker-message))
	  (if (eq (car ,x-cons-variable) ,x-car-marker)
	      (error ,x-error-message))
	  (setf (car ,x-cons-variable) ,x-car-marker)
	  (cond ((eq ,x-cons-variable ,x-tail-variable)
		 (return nil))
		((null ,x-cons-variable)
		 (error "~a with a tail not eq to a cdr of the head of the ~
                          given list.~%~
                          Head = ~s~%~
                          Tail = ~s"
			',reclaim-x-list-given-tail
			,x-list-variable
			,x-tail-variable))
		(t
		 (setq ,x-cons-variable (cdr ,x-cons-variable))))))

      (defun-substitution-macro ,reclaim-x-list-given-tail
	  (,x-list-variable ,x-tail-variable)
	(#+mtg2 tx:with-lock-held #+mtg2 (,x-cons-lock) #-mtg2 progn
			    
	,@(if fully-checked?
	      `((cond ((loop named double-reclaim-checker
			     for reclaimed-cons on ,available-x-conses
			     for fast-reclaimed = (cdr ,available-x-conses)
						then (cddr fast-reclaimed)
			     do
			 (if (eq reclaimed-cons fast-reclaimed)
			     (error "~a contains a circular list."
				    ',available-x-conses))
			 (loop for cons-in-list = ,x-list-variable
						then (cdr cons-in-list)
			       for fast-cons-in-list
				   = (if (neq cons-in-list ,x-tail-variable)
					 (cdr cons-in-list)
					 nil)
				   then (if (neq fast-cons-in-list
						 ,x-tail-variable)
					    (if (neq (cdr fast-cons-in-list)
						     ,x-tail-variable)
						(cddr fast-cons-in-list)
						nil)
					    nil)
			       do
			   (if (eq cons-in-list fast-cons-in-list)
			       (error "~a called on a circular list."
				      ',reclaim-x-list-given-tail))
			   (if (eq cons-in-list reclaimed-cons)
			       (return-from double-reclaim-checker t))
			       until (eq cons-in-list ,x-tail-variable)))
		       (error "Cons being doubly reclaimed into the ~a pool."
			      ',root-name))
		      ((loop for cons-in-list = ,x-list-variable
					      then (cdr cons-in-list)
			     do
			 (if (not (memq cons-in-list ,conses-from-this-pool?))
			     (return t))
			     until (eq cons-in-list ,x-tail-variable))
		       (cerror "go on"
			       "Cons being given back to ~a pool which didn't come from here."
			       ',root-name))))
	      nil)

	#+development
	(,x-list-checker-given-tail ,x-list-variable ,x-tail-variable)
	(when (and ,x-list-variable #-development (debugging-consing-p))
	  (loop with ,x-cons-variable = ,x-list-variable
		do
	    (note-reclaim-cons ,x-cons-variable ',root-name)
	    #+development
	    (setf (car ,x-cons-variable) ,x-car-marker)
	    (cond ((eq ,x-cons-variable ,x-tail-variable)
		   (return nil))
		  ((null ,x-cons-variable)
		   #-development
		   (return nil)
		   #+development
		   (error "~a with a tail not eq to a cdr of the head of the ~
                          given list.~%~
                          Head = ~s~%~
                          Tail = ~s"
			  ',reclaim-x-list-given-tail
			  ,x-list-variable
			  ,x-tail-variable))
		  (t
		   (setq ,x-cons-variable (cdr ,x-cons-variable))))))
	(reclaim-list-internal ,x-list-variable ,x-tail-variable
			       ,available-x-conses
			       ,available-x-conses-tail
			       #+SymScale ,available-x-conses-vector
			       #+SymScale ,available-x-conses-tail-vector
			       #+SymScale ,x-cons-counter-vector)
	nil)))))

;; under test, we make an especially inconvinient entry for cons marker so that
;; increase the probability of type errors in case we access it erroneously
;; - budden73
#+cons-checking
(defstruct cons-marker-structure root-name)

#+development
(defun make-cons-marker (root-name)		; only used to initialize car markers
  (declare (special last-assigned-global-kb-number))	; defvar'd below
  #+cons-checking
  (make-cons-marker-structure :root-name root-name)
  #-cons-checking
  (make-symbol
    (format
      nil "KB-~D-~A-CONS"
      (if (boundp 'last-assigned-global-kb-number)
	  last-assigned-global-kb-number
	  0)
      root-name)))





(defmacro defvar-for-development (name value)
  `(#+development
    defvar
    #-development
    defvar ,name ,value)) ; cannot understand why used DEFCONSTANT here,
			  ; any way, change it to DEFVAR should be noharmful.
			  ; -- binghe, 2009/6/5




;;; The parameter `cons-pool-conses-to-make-at-a-time' controls how many conses
;;; are made in a batch by defconser facilities when more conses are needed in a
;;; pool.
; changed to `defvar' to make LW api-tests happy
(defvar cons-pool-conses-to-make-at-a-time 1024)




;;; The macro `replenish-checked-cons-pool' is used to replenish cons
;;; pool which are checking for all errors.  It keeps a list of all conses
;;; which have been allocated for each pool.

(defmacro replenish-checked-cons-pool
	  (available-conses
	   available-conses-tail
	   cons-count
	   conses-we-own)
  #-use-queue-allocation-for-consing
  (declare (ignore available-conses-tail))
  `(let ((new-conses (make-permanent-list-macro
		      cons-pool-conses-to-make-at-a-time))
	 (owned-list (make-permanent-list-macro
		      cons-pool-conses-to-make-at-a-time)))
     (loop for new on new-conses
	   for owned on owned-list
	   do
       (setf (car owned) new))
     (setf ,conses-we-own
	   (nconc owned-list ,conses-we-own))
     (atomic-incff ,cons-count
		   cons-pool-conses-to-make-at-a-time)
     (setf ,available-conses
	   (nconc ,available-conses (cdr new-conses)))
     #+use-queue-allocation-for-consing
     (setf ,available-conses-tail (last new-conses))
     new-conses))

;;; The macro `replenish-checked-cons-pool-list' is used to replenish cons
;;; pool which are checking for all errors.  It keeps a list of all conses which
;;; have been allocated for each pool.

(defmacro replenish-checked-cons-pool-list
	  (available-conses
	   available-conses-tail
	   cons-count
	   conses-we-own
	   conses-needed-minus-one)
  #-use-queue-allocation-for-consing
  (declare (ignore available-conses-tail))
  `(let* ((conses-needed (maxf (1+ ,conses-needed-minus-one)
			       cons-pool-conses-to-make-at-a-time))
	  (new-conses (make-permanent-list-macro conses-needed))
	  (owned-list (make-permanent-list-macro conses-needed)))
     (loop for new on new-conses
	   for owned on owned-list
	   do
       (setf (car owned) new))
     (setf ,conses-we-own
	   (nconc owned-list ,conses-we-own))
     (setf ,cons-count
	   (+f ,cons-count conses-needed))
     (setf ,available-conses
	   (nconc ,available-conses new-conses))
     #+use-queue-allocation-for-consing
     (setf ,available-conses-tail
	   (last new-conses))
     nil))

(defvar all-cons-pools nil)

#+development
(defun cons-origin? (cons)
  (loop for cons-pool in all-cons-pools
	when (memq cons (symbol-value cons-pool))
	  return cons-pool))




;;; The macro `def-pseudo-conser' takes a root name of a new pseudo-conser to be
;;; defined, and the root name of an existing real conser.  It will define the
;;; suite of consing macros and functions for the pseudo-conser so that they
;;; actually invoke the macros and functions for the real conser.  This is done
;;; only in the distribution compiles and is done to avoid the redundant code of
;;; more that one conser and to collapse all the cons pools together to get the
;;; best use of already allocated conses.

;;; At the moment this facility defines the new functions by performing a setf
;;; on the symbol-function of the pseudo-conser symbols.  This is defined to be
;;; conforming way of defining functions in Common Lisp, but this does not
;;; necessarily allow the most efficient dispatches to it, as can be done in
;;; Ibuki (an obsolete platform) and Lucid.  When we know how to declare
;;; information to these implementations to get these efficient function calls
;;; we should do so.

;; Added pseudo-consers for x-push, x-pushnew, and x-pop.  (jh, 3/25/90)

(defmacro def-pseudo-conser (pseudo-root-name base-conser-name)
  (let* ((x-cons-macro-pseudonym
	   (intern (format nil "~a-CONS-MACRO" pseudo-root-name)))
	 (x-cons-macro
	   (intern (format nil "~a-CONS-MACRO" base-conser-name)))
	 (x-cons-function-pseudonym
	   (intern (format nil "~a-CONS" pseudo-root-name)))
	 (x-cons-function
	   (intern (format nil "~a-CONS" base-conser-name)))
	 (x-cons-variable
	   (intern (format nil "~a-CONS" pseudo-root-name)))
	 (make-x-list-macro-pseudonym
	   (intern (format nil "MAKE-~a-LIST-MACRO" pseudo-root-name)))
	 (make-x-list-macro
	   (intern (format nil "MAKE-~a-LIST-MACRO" base-conser-name)))
	 (make-x-list-pseudonym
	   (intern (format nil "MAKE-~a-LIST" pseudo-root-name)))
	 (make-x-list
	   (intern (format nil "MAKE-~a-LIST" base-conser-name)))
	 (x-list-function-pseudonym
	   (intern (format nil "~a-LIST" pseudo-root-name)))
	 (x-list-function
	   (intern (format nil "~a-LIST" base-conser-name)))
	 (x-list-macro-pseudonym
	   (intern (format nil "~a-LIST-MACRO" pseudo-root-name)))
	 (x-list-macro
	   (intern (format nil "~a-LIST-MACRO" base-conser-name)))
	 (x-list-variable
	   (intern (format nil "~a-LIST" pseudo-root-name)))
	 (x-tail-variable
	   (intern (format nil "~a-LIST-TAIL" pseudo-root-name)))
	 (copy-tree-using-x-conses-pseudonym
	   (intern (format nil "COPY-TREE-USING-~a-CONSES" pseudo-root-name)))
	 (copy-tree-using-x-conses
	   (intern (format nil "COPY-TREE-USING-~a-CONSES" base-conser-name)))
	 (copy-list-using-x-conses-pseudonym
	   (intern (format nil "COPY-LIST-USING-~a-CONSES" pseudo-root-name)))
	 (copy-list-using-x-conses
	   (intern (format nil "COPY-LIST-USING-~a-CONSES" base-conser-name)))
	 (reclaim-x-cons-pseudonym
	   (intern (format nil "RECLAIM-~a-CONS" pseudo-root-name)))
	 (reclaim-x-cons
	   (intern (format nil "RECLAIM-~a-CONS" base-conser-name)))
	 (reclaim-x-cons-macro-pseudonym
	   (intern (format nil "RECLAIM-~a-CONS-MACRO" pseudo-root-name)))
	 (reclaim-x-cons-macro
	   (intern (format nil "RECLAIM-~a-CONS-MACRO" base-conser-name)))
	 (reclaim-x-list-pseudonym
	   (intern (format nil "RECLAIM-~a-LIST" pseudo-root-name)))
	 (reclaim-x-list
	   (intern (format nil "RECLAIM-~a-LIST" base-conser-name)))
	 (reclaim-x-list-macro-pseudonym
	   (intern (format nil "RECLAIM-~a-LIST-MACRO" pseudo-root-name)))
	 (reclaim-x-list-macro
	   (intern (format nil "RECLAIM-~a-LIST-MACRO" base-conser-name)))
	 (reclaim-x-list-given-tail-pseudonym
	   (intern (format nil "RECLAIM-~a-LIST-GIVEN-TAIL" pseudo-root-name)))
	 (reclaim-x-list-given-tail
	   (intern (format nil "RECLAIM-~a-LIST-GIVEN-TAIL" base-conser-name)))
	 (reclaim-x-list*-pseudonym
	   (intern (format nil "RECLAIM-~a-LIST*" pseudo-root-name)))
	 (reclaim-x-list*
	   (intern (format nil "RECLAIM-~a-LIST*" base-conser-name)))
	 (reclaim-x-tree-pseudonym
	   (intern (format nil "RECLAIM-~a-TREE" pseudo-root-name)))
	 (reclaim-x-tree
	   (intern (format nil "RECLAIM-~a-TREE" base-conser-name)))
	 (delete-x-element-pseudonym
	   (intern (format nil "DELETE-~a-ELEMENT" pseudo-root-name)))
	 (delete-x-element
	   (intern (format nil "DELETE-~a-ELEMENT" base-conser-name)))
	 (delete-x-cons-pseudonym
	   (intern (format nil "DELETE-~a-CONS" pseudo-root-name)))
	 (delete-x-cons
	   (intern (format nil "DELETE-~a-CONS" base-conser-name)))
	 (x-push-pseudonym
	   (intern (format nil "~a-PUSH" pseudo-root-name)))
	 (x-push
	   (intern (format nil "~a-PUSH" base-conser-name)))
	 (x-pushnew-pseudonym
	   (intern (format nil "~a-PUSHNEW" pseudo-root-name)))
	 (x-pushnew
	   (intern (format nil "~a-PUSHNEW" base-conser-name)))
	 (x-pop-pseudonym
	   (intern (format nil "~a-POP" pseudo-root-name)))
	 (x-pop
	   (intern (format nil "~a-POP" base-conser-name))))

    `(progn       

       (defmacro ,x-cons-macro-pseudonym (car cdr)
	 `(,',x-cons-macro ,car ,cdr))
       (defmacro ,x-cons-function-pseudonym (car cdr)
	 `(,',x-cons-function ,car ,cdr))
       (defmacro ,make-x-list-macro-pseudonym (count)
	 `(,',make-x-list-macro ,count))
       (defmacro ,make-x-list-pseudonym (count)
	 `(,',make-x-list ,count))
       (defmacro ,x-list-macro-pseudonym (&rest elements)
	 `(,',x-list-macro ,@elements))
       (defmacro ,x-list-function-pseudonym (&rest args)
	 `(,',x-list-function ,@args))
       (defmacro ,copy-tree-using-x-conses-pseudonym (tree?)
	 `(,',copy-tree-using-x-conses ,tree?))
       (defmacro ,copy-list-using-x-conses-pseudonym (list?)
	 `(,',copy-list-using-x-conses ,list?))
       (defmacro ,reclaim-x-cons-macro-pseudonym (,x-cons-variable)
	 `(,',reclaim-x-cons-macro ,,x-cons-variable))
       (defmacro ,reclaim-x-cons-pseudonym (,x-cons-variable)
	 `(,',reclaim-x-cons ,,x-cons-variable))
       (defmacro ,reclaim-x-list-macro-pseudonym (,x-list-variable)
	 `(,',reclaim-x-list-macro ,,x-list-variable))
       (defmacro ,reclaim-x-list-given-tail-pseudonym
		 (,x-list-variable ,x-tail-variable)
	 `(,',reclaim-x-list-given-tail ,,x-list-variable ,,x-tail-variable))
       (defmacro ,reclaim-x-list-pseudonym (,x-list-variable)
	 `(,',reclaim-x-list ,,x-list-variable))
       (defmacro ,reclaim-x-list*-pseudonym (,x-list-variable)
	 `(,',reclaim-x-list* ,,x-list-variable))
       (defmacro ,reclaim-x-tree-pseudonym (tree)
	 `(,',reclaim-x-tree ,tree))
       (defmacro ,delete-x-element-pseudonym (element ,x-list-variable)
	 `(,',delete-x-element ,element ,,x-list-variable))
       (defmacro ,delete-x-cons-pseudonym (,x-cons-variable ,x-list-variable)
	 `(,',delete-x-cons ,,x-cons-variable ,,x-list-variable))
       (defmacro ,x-push-pseudonym (thing ,x-cons-variable)
	 `(,',x-push ,thing ,,x-cons-variable))
       (defmacro ,x-pushnew-pseudonym (thing ,x-cons-variable &rest keys)
	 `(,',x-pushnew ,thing ,,x-cons-variable ,@keys))
       (defmacro ,x-pop-pseudonym (,x-cons-variable)
	 `(,',x-pop ,,x-cons-variable))

       ,@(unless (eval-feature :no-macros)
	   `((note-non-resumable-function-call-macro
	       ',x-cons-macro-pseudonym ',x-cons-function-pseudonym ',make-x-list-macro-pseudonym
	       ',make-x-list-pseudonym ',x-list-macro-pseudonym ',x-list-function-pseudonym
	       ',copy-tree-using-x-conses-pseudonym ',copy-list-using-x-conses-pseudonym
	       ',reclaim-x-cons-macro-pseudonym ',reclaim-x-cons-pseudonym
	       ',reclaim-x-list-macro-pseudonym ',reclaim-x-list-given-tail-pseudonym
	       ',reclaim-x-list-pseudonym ',reclaim-x-list*-pseudonym ',reclaim-x-tree-pseudonym
	       ',delete-x-element-pseudonym ',delete-x-cons-pseudonym)))
	       
       ',pseudo-root-name)))



;;; The `gensym-cons' consing pool is defined for all those little consing jobs
;;; too small for their own conser.  In distribution compiles, this is also the
;;; actual root conser which all others collapse into.

(defconser gensym utilities0)


;;; The functions copy-tree-using-gensym-conses and  gensym-cons-function are
;;; needed in PRIMITIVES.  The function reclaim-gensym-list-function is needed
;;; in MENUS.  The function reclaim-gensym-tree-function is needed in FILES.

;;; Gensym-cons-function and copy-tree-using-gensym-conses-function can be
;;; declared side-effect free as long as the memory meters are not declared
;;; side-effect free.

(declare-side-effect-free-function gensym-cons-function)

(defun-simple gensym-cons-function (car cdr)
  (gensym-cons-macro car cdr))

(defun-simple copy-tree-using-gensym-conses-function (tree?)
  (copy-tree-using-gensym-conses tree?))

(defun-simple reclaim-gensym-list-function (list)
  (reclaim-gensym-list-macro list))

(defun-simple reclaim-gensym-tree-function (tree)
  (reclaim-gensym-tree tree))


;;; Reverse-list-using-gensym-conses creates of a copy of list and destructively
;;; reverses the copy, or at least seems to do the equivalent.

(defun-simple reverse-list-using-gensym-conses (list)
  (loop with reversed-list = nil
	for l on list
	do (setq reversed-list
		 (gensym-cons (car l) reversed-list))
	finally (return reversed-list)))

;;; The function reclaim-gensym-list-if-list calls reclaim-gensym-list on
;;; atom-or-gensym-list provided if it's a cons.

(defun-void reclaim-gensym-list-if-list (atom-or-gensym-list)
  (if (consp atom-or-gensym-list) (reclaim-gensym-list atom-or-gensym-list)))






;;;; Scoped Consing



;;; In some cases, there is no opportunity to call a reclaiming function for
;;; consing within a scope.  In cases like this, scope-cons can be used.  If you
;;; bind the variable `scope-conses' to itself, then you can call `scope-cons',
;;; `scope-list', and `copy-list-using-scope-conses' freely within that scope,
;;; and those conses will be reclaimed on exit from the scope of the global
;;; variable binding of scope-conses.  For example:

;;; (defun find-chaining (symbol)
;;;   (let* ((scope-conses scope-conses)    ; Bind global variable to itself
;;;          (links-to-check
;;;            (loop for link in (forward-chaining-links symbol)
;;;                  when (valid-link-p link)
;;;                    collect link using scope-cons))) ; Use scope-cons
;;;     (loop for link in links-to-check
;;;           when (link-applies-p link)
;;;             return link)))              ; Return without worry

;;; This ginned up example could be written to not need this list of course, but
;;; it shows the usage.  This facility is required in some places where you
;;; cannot get a cleanup form to reclaim a list, or where a non-local exit might
;;; occur before you can reclaim.  This happens particularly in loop-path
;;; expansion macros.

(defvar scope-conses (list (list nil)))

(defun-simple scope-cons (car cdr)
  (let* ((cons-holder scope-conses)
         (cons-to-give (car-of-cons cons-holder))
         (next-cons-holder? (cdr-of-cons cons-holder)))
    (unless next-cons-holder?
      (setq next-cons-holder? (gensym-list (gensym-list nil)))
      (setf (cdr cons-holder) next-cons-holder?))
    (setq scope-conses next-cons-holder?)
    (setf (car cons-to-give) car)
    (setf (cdr cons-to-give) cdr)
    cons-to-give))




;;; The function make-scope-list takes a length and returns a list of conses
;;; that long.  It's not fast, but it's simple.

(defun-simple make-scope-list (count)
  (when (>f count 0)
    (loop repeat count
          for next-cons = (scope-cons nil nil)
                        then (scope-cons nil next-cons)
          finally (return next-cons))))




;;; The macro `scope-list' makes and returns a list of scope conses with the
;;; given contents.

(defmacro scope-list (&rest list-elements)
  (case (length list-elements)
    ((0)
     nil)
    ((1)
     `(scope-cons ,(car list-elements) nil))
    (t
     `(set-list-contents
	(make-scope-list ,(length list-elements))
	,@list-elements))))




;;; The function `copy-list-using-scope-conses' makes a copy of the top-level
;;; conses in given list using scope-conses.

(defun-simple copy-list-using-scope-conses (list-to-copy)
  (loop for element in list-to-copy collect element using scope-cons))






;;;; Sorting




;;; The Common Lisp sorting functions cons in some implementations, and so two
;;; sorting facilies similar to CLtL sort are presented here.  The first is
;;; `sort-list' and the second is `sort-array'.  They perform stable sorts on
;;; these two types, similar to sort, but they are guaranteed to not cons.

;;; They both use the most trivial of sinking rock sorting algorithms and mutate
;;; their given sequences so that they are ordered least to greatest as
;;; indicated by the less-than-predicate function.

(defun sort-array (array less-than-predicate key)
  (declare (eliminate-for-gsi))
  (loop for end-point from (-f (length array) 1) downto 1
	do
    (loop for lesser-index from 0 below end-point
	  for lesser-elt = (aref array lesser-index)
	  for greater-index fixnum = (+f lesser-index 1)
	  for greater-elt = (aref array greater-index)
	  do
      (when (if key
		(funcall less-than-predicate
			 (funcall key greater-elt)
			 (funcall key lesser-elt))
		(funcall less-than-predicate greater-elt lesser-elt))
	(setf (aref array greater-index) lesser-elt
	      (aref array lesser-index) greater-elt))))
  array)

;; The version of sort-list above was implemented as a quick fix to consing
;; sorts.  Lowell has implemented a better sort which has n log n performance,
;; and it is written below.  When it has been used for a while (a week) the
;; above function can be deleted.  A better version of sort-array should be
;; written above as well.  -jra 2/6/89




;;; Sort-list is like the Common Lisp function sort for the list case, but is
;;; guaranteed not to cons.  It destructively sorts the list l per predicate, which
;;; should take two arguments and return non-nil if and only if the first argument
;;; is strictly less than the second (in some appropriate sense).  Sort-list has
;;; n log n speed, is stable, and does not cons.

(defun sort-list (list predicate key)
  ; (declare (eliminate-for-gsi)) ; de-eliminated, now used in ISO2022 (MHD 12/16/96)
  (sort-list-1 list (length list) predicate key))

(defun sort-list-1 (l n predicate key)
  ; (declare (eliminate-for-gsi)) ; de-eliminated, now used in ISO2022 (MHD 12/16/96)  
  (declare (type fixnum n))
  (if (>f n 1)
      (let* ((half-n (halff n))			; split list and sort each half
	     (l-tail (nthcdr (-f half-n 1) l))
	     (l2 (sort-list-1 (cdr l-tail) (-f n half-n) predicate key))
	     (l1 (progn (setf (cdr l-tail) nil)
			(sort-list-1 l half-n predicate key))))
	(declare (type fixnum half-n))
	(setq l nil)
	(loop until				; merge the sorted halves
		(cond
		  ((if key
		       (not (funcall predicate
				     (funcall key (car l2))
				     (funcall key (car l1))))
		       (not (funcall predicate (car l2) (car l1))))
		   (setq l-tail
			 (if (null l)
			     (setq l l1)
			     (setf (cdr l-tail) l1)))
		   (if (null (setq l1 (cdr l1)))
		       (setf (cdr l-tail) l2)))
		  (t
		   (setq l-tail (if (null l)
				    (setq l l2)
				    (setf (cdr l-tail) l2)))
		   (if (null (setq l2 (cdr l2)))
		       (setf (cdr l-tail) l1)))))))
  l)

;; Consider optimizing short list cases more.






;;; Delete-duplicates-from-list removes duplicates from list destructively.  The
;;; test function used to detect duplicates is test-function?, if that is
;;; non-nil, and otherwise EQ.  Note that test-function?  may not be a macro.
;;; If cons-reclaimer?  is non-nil, it should be the name of a function of one
;;; argument to be called with each cons that are snipped out of the list and
;;; may need to be reclaimed; if it is nil, nothing is done with these conses.

(defun delete-duplicates-from-list (list &optional cons-reclaimer? test-function?)
  (declare (eliminate-for-gsi))
  (loop for l on list
	as element = (car l)
	do (loop with m-trailer = l
		 as m = (cdr m-trailer)
		 while m
		 do (if (if test-function?	; test outside of loop for speed?
			    (funcall test-function? (car m) element)
			    (eq (car m) element))
			(progn
			  (setf (cdr m-trailer) (cdr m))
			  (if cons-reclaimer?
			      (funcall cons-reclaimer? m)))
			(setq m-trailer m)))
	finally
	  (return list)))

(defun delete-item-from-list-and-reclaim-cons-cells
    (list item cons-reclaimer retain-first-value?)
  (declare (eliminate-for-gsi))
  (let ((result-list NIL)
	(first-value-retained? nil))
    (cond ((eq item (car list))
	   (cond (retain-first-value?
		  (setq first-value-retained? t)
		  (setq result-list list))
		 (t
		  (setq result-list (cdr list))
		  (funcall cons-reclaimer list))))
	  (t
	   (setq result-list list)))
    (loop for l on (if first-value-retained?
		       (cdr result-list)
		       result-list)
	  do
      (loop with m-trailer = l
	    as m = (cdr m-trailer)
	    while m
	    do
	(if
	  (eq (car m) item)
	  (cond ((and retain-first-value?
		      (null first-value-retained?))
		 (setq first-value-retained? t))
		(t
		 (setf (cdr m-trailer) (cdr m))
		 (funcall cons-reclaimer m)))
	  (setq m-trailer m)))
	  )
    result-list))

;; Added here today.  Only callers now in FRAMES5 and KB-MERGE.  (MHD 12/19/91)




;;; `Nreverse-canonically' is like nreverse, but is guaranteed not to cons or to
;;; change the cars of any conses.  Common Lisp's nreverse is guaranteed not to
;;; cons.  However, it's not guaranteed to leave the car's of each cons alone.
;;; So the reason to use this is if you need to make sure the car's of each cons
;;; cannot change, e.g., if you have other pointers to the car's.

(defun nreverse-canonically (list)
  (declare (eliminate-for-gsi))
  (loop with reversed-list = nil
	with next-cons
	while list
	do (setq next-cons (cdr list))
	   (setf (cdr list) reversed-list)
	   (setq reversed-list list)
	   (setq list next-cons)
	finally
	  (return reversed-list)))		; changes arg

;; Moved here from PARSE today.  There are callers in numerous modules now. (MHD 12/19/91)



;;; The function `list-prefix-p' is true iff list-a is a prefix of list-b.

(defun list-prefix-p (list-a list-b)
  (loop for element in list-a
	always (and list-b (eq element (pop list-b)))))



;;;; Simple Vector Pool

;;; The Simple Vector Pool manages simple vectors of lengths from 1 through
;;; `maximum-managed-simple-vector-size' (which is currently 1024).  Above that
;;; managed-simple-vectors are allocated in 1K lengths up to
;;; `maximum-oversized-managed-simple-vector-size' (currently 1Meg, 1048576).

(defconstant maximum-managed-simple-vector-size 1024)




;;; The function `allocate-managed-simple-vector' allocates vectors and the
;;; function `reclaim-managed-simple-vector' returns vectors to the pool.  The
;;; pool is metered under the name `managed-simple-vectors'.



;; Note that the oversized limit must be the square of the normal size limit.
;; -jra 11/29/94

(def-concept simple-vector)




;;; The system variable `vector-of-simple-vector-pools' contains a simple vector
;;; whose elements are the pools of simple vectors.  Element N of this vector
;;; contains the pool of vectors of length N.  Element 0 of each vector is used
;;; to chain together the reclaimed vectors.  The system variable
;;; `simple-vector-pool-counts' is used to hold counts of the number of vectors
;;; allocated for each pool of simple vectors.

(defun allocate-initial-managed-simple-vector-pool-array (initial-element)
  (make-array (+f maximum-managed-simple-vector-size 1)
	      :initial-element initial-element))

(def-system-variable vector-of-simple-vector-pools utilities0
  (:funcall allocate-initial-managed-simple-vector-pool-array nil) nil t)

(def-system-variable simple-vector-pool-counts utilities0
  (:funcall allocate-initial-managed-simple-vector-pool-array 0) nil t)

#|
(def-system-variable vector-of-simple-vector-pools-for-array utilities0
  (:funcall allocate-initial-managed-simple-vector-pool-array nil))

(def-system-variable simple-vector-pool-counts-for-array utilities0
  (:funcall allocate-initial-managed-simple-vector-pool-array 0))

(def-system-variable vector-of-simple-vector-pools-for-float-array utilities0
  (:funcall allocate-initial-managed-simple-vector-pool-array nil))

(def-system-variable simple-vector-pool-counts-for-float-array utilities0
  (:funcall allocate-initial-managed-simple-vector-pool-array 0))

(def-system-variable vector-of-simple-vector-pools-for-skip-list utilities0
  (:funcall allocate-initial-managed-simple-vector-pool-array nil)
  nil t) ; bind-globally?

(def-system-variable simple-vector-pool-counts-for-skip-list utilities0
  (:funcall allocate-initial-managed-simple-vector-pool-array 0)
  nil t) ; bind-globally?
|#

;;; The system variable `vector-of-oversized-simple-vector-pools' contains a
;;; simple vector whose elements are the pools of simple vectors.  Element N of
;;; this vector contains the pool of vectors of length N * 1024.  Element 0 of
;;; each vector is used to chain together the reclaimed vectors.  The system
;;; variable `oversized-simple-vector-pool-counts' is used to hold counts of the
;;; number of vectors allocated for each pool of simple vectors.

(def-system-variable vector-of-oversized-simple-vector-pools utilities0
  (:funcall allocate-initial-managed-simple-vector-pool-array nil))

(def-system-variable oversized-simple-vector-pool-counts utilities0
  (:funcall allocate-initial-managed-simple-vector-pool-array 0))




;;; The variable `created-simple-vector-pool-vectors' contains the integer count
;;; of the number of simple vectors created in this pool.  The function
;;; `outstanding-simple-vector-pool-vectors' returns the count of the number of
;;; simple vectors which have been created but not yet returned.  It does this
;;; by subtracting the count of all of the vectors in the pool from the created
;;; count.  The function `svp-memory-usage' returns the number of words used by
;;; all of the created simple vectors for this pool.

(def-system-variable created-simple-vector-pool-vectors utilities0 0
  nil t) ; also-bind-globally?

(defun outstanding-simple-vector-pool-vectors ()
  (let ((vectors-in-pools 0))
    (declare (type fixnum vectors-in-pools))
    (loop for index from 1 to maximum-managed-simple-vector-size
	  do
      (loop for vector = (svref vector-of-simple-vector-pools index)
		       then (svref vector 0)
	    while vector do (incff vectors-in-pools)))
    (loop for index from 1 to maximum-managed-simple-vector-size
	  do
      (loop for vector = (svref vector-of-oversized-simple-vector-pools index)
		       then (svref vector 0)
	    while vector do (incff vectors-in-pools)))
    (-f created-simple-vector-pool-vectors vectors-in-pools)))

(def-system-variable simple-vector-pool-memory-usage utilities0 0
  nil t) ; also-bind-globally?

(defun svp-memory-usage ()
  simple-vector-pool-memory-usage)

(def-system-object-pool managed-simple-vectors
    simple-vector created-simple-vector-pool-vectors
  nil outstanding-simple-vector-pool-vectors svp-memory-usage)

(defparameter replenished-simple-vector-size-limit 10)
(defparameter replenished-simple-vectors-to-make-at-a-time 10)


;;; The function `allocate-managed-simple-vector' takes a size and allocates and
;;; returns a simple vector.  The contents of this vector are undefined on
;;; allocation.  Note that when the length of the requested vector is more than
;;; the maximum-managed-simple-vector-size but below the
;;; maximum-oversized-managed-simple-vector-size, then the length of the
;;; returned vector will be rounded up to the next multiple of 1024.

(defun-simple allocate-managed-simple-vector (length)
  (declare (type fixnum length))
  #+development
  (when (or (<=f length 0)
	    (>f length maximum-oversized-managed-simple-vector-size))
    (error "Requested managed simple vector size, ~a, exceeds limits." length))
  (let ((local-vector-of-simple-vector-pools vector-of-simple-vector-pools)
	(local-simple-vector-pool-counts simple-vector-pool-counts)
	(index length)
	(available-vector? nil))
    (declare (type fixnum index))
    (when (>f length maximum-managed-simple-vector-size)
      ;; The following is a quick and slick way to round up to the next 1K length.
      (when (/=f (logandf length 1023) 0)
	(setq length (+f (logandf length -1024) 1024)))
      (setq local-vector-of-simple-vector-pools
	    vector-of-oversized-simple-vector-pools)
      (setq local-simple-vector-pool-counts
	    oversized-simple-vector-pool-counts)
      (setq index (ashf length -10)))
    (setq available-vector?
	  (svref local-vector-of-simple-vector-pools index))
    (let ((a (cond (available-vector?
		    #-SymScale
		    (setf (svref local-vector-of-simple-vector-pools index)
			  (svref available-vector? 0))
		    #+SymScale
		    (setf (svref local-vector-of-simple-vector-pools index)
			  (cdr-of-cons available-vector?))
		    #-SymScale
		    available-vector?
		    #+SymScale
		    (let ((array (car-of-cons available-vector?)))
		      (reclaim-gensym-cons-macro available-vector?)
		      array)))))
      (unless a
	(setq a
	     (cond ((<=f length replenished-simple-vector-size-limit)
		    (with-permanent-array-creation
		      #-SymScale
		      (loop with vectors-made-so-far = nil
			    repeat (-f replenished-simple-vectors-to-make-at-a-time 1)
			    for new-vector = (make-array length)
			    do
			(setf (svref new-vector 0) vectors-made-so-far)
			(setq vectors-made-so-far new-vector)
			    finally
			      (setf (svref local-vector-of-simple-vector-pools index)
				    vectors-made-so-far))
		      #+SymScale
		      (loop with vectors-made-so-far = nil
			    repeat (-f replenished-simple-vectors-to-make-at-a-time 1)
			    for new-vector = (make-array length)
			    collect new-vector into vectors-made-so-far using gensym-cons
			    finally
			      (setf (svref local-vector-of-simple-vector-pools index)
				    vectors-made-so-far))
		      (atomic-incff created-simple-vector-pool-vectors
			     replenished-simple-vectors-to-make-at-a-time)
		      (atomic-incff (svref local-simple-vector-pool-counts index)
			     replenished-simple-vectors-to-make-at-a-time)
		      (atomic-incff simple-vector-pool-memory-usage
			     (*f replenished-simple-vectors-to-make-at-a-time
				 (bytes-per-simple-vector length)))
		      (make-array length)))
		   (t
		    (atomic-incff created-simple-vector-pool-vectors)
		    (atomic-incff (svref local-simple-vector-pool-counts index))
		    (atomic-incff simple-vector-pool-memory-usage
			   (bytes-per-simple-vector length))
		    (with-permanent-array-creation
		      (make-array length))))))
      (note-allocate-cons a nil)
      a)))

(defun-simple allocate-managed-simple-vector-for-array (length)
  (allocate-managed-simple-vector length))

(defun-simple allocate-managed-simple-vector-for-float-array (length)
  (allocate-managed-simple-vector length))

(defun-simple allocate-managed-simple-vector-for-skip-list (length)
  (allocate-managed-simple-vector length))

;;; The function `reclaim-managed-simple-vector' takes a managed simple vector,
;;; and returns it to the pool.

(defun-simple reclaim-managed-simple-vector (managed-simple-vector)
  (let ((length (length-of-simple-vector managed-simple-vector)))
    (declare (type fixnum length))
    #+development
    (when (or (<=f length 0)
	      (>f length maximum-oversized-managed-simple-vector-size))
      (error "Reclaimed managed simple vector size, ~a, exceeds limits."
	     length))
    #+development
    (when (and (>f length maximum-managed-simple-vector-size)
	       (/=f (logandf length 1023) 0))
      (error "Reclaimed managed oversized simple vector length, ~a, is not a multiple of 1024."
	     length))
    (note-reclaim-cons managed-simple-vector nil)
    (barrier)
    (cond ((>f length maximum-managed-simple-vector-size)
	   (let ((index (ashf length -10)))
	     (declare (type fixnum index))
	     #-SymScale
	     (setf (svref managed-simple-vector 0)
		   (svref vector-of-oversized-simple-vector-pools index))
	     #-SymScale
	     (setf (svref vector-of-oversized-simple-vector-pools index)
		   managed-simple-vector)
	     #+SymScale
	     (setf (svref vector-of-oversized-simple-vector-pools index)
		   (gensym-cons-macro managed-simple-vector
				      (svref vector-of-oversized-simple-vector-pools index)))))
	  (t
	   #-SymScale
	   (setf (svref managed-simple-vector 0)
		 (svref vector-of-simple-vector-pools length))
	   #-SymScale
	   (setf (svref vector-of-simple-vector-pools length)
		 managed-simple-vector)
	   #+SymScale
	   (setf (svref vector-of-simple-vector-pools length)
		 (gensym-cons-macro managed-simple-vector
				    (svref vector-of-simple-vector-pools length)))))
    nil))

(defun-simple reclaim-managed-simple-vector-for-array (managed-simple-vector)
  (reclaim-managed-simple-vector managed-simple-vector))

(defun-simple reclaim-managed-simple-vector-for-float-array (managed-simple-vector)
  (reclaim-managed-simple-vector managed-simple-vector))

(defun-simple reclaim-managed-simple-vector-for-skip-list (managed-simple-vector)
  (reclaim-managed-simple-vector managed-simple-vector))

;;; `Fill-managed-simple-vector' places value into each element of
;;; managed-simple-vector from start to end.

(defun-void fill-managed-simple-vector (managed-simple-vector value start end)
  (declare (type fixnum start end))
  (loop for i from start below end
	do (setf (svref managed-simple-vector i) value))
  (barrier))

;; This should ideally be implemented at a lower level if possible, i.e., as a
;; "memset"! (MHD 12/17/99)





;;;; Managed Array Specification




;;; Within G2 there is a need for managed arrays of arbitrary length.  This
;;; facility is provided by the Managed Array Pool.  Arrays of arbitrary lengths
;;; up to 64K long can be created and reclaimed.  These arrays can be grown and
;;; shrunk, and portions of these arrays can be efficiently copied.  The main
;;; advantage of this facility over using Lisp adjustable arrays is that large
;;; vectors are split into reusable 256 element buffers, and that all consing is
;;; controlling by G2 in terms of simple arrays and conses.  The allocation
;;; scheme for buffers smaller than 256 elements ensures either less than 4
;;; words wasted, or a minimum of 75% memory utilization.  The function
;;; `allocate-managed-array' gives out managed arrays, and the function
;;; `reclaim-managed-array' returns them to the pool.  The macro `managed-svref'
;;; is used to access and SETF their contents.  This facility contains other
;;; tools for adjusting array sizes, copying array contents, and rotating
;;; managed arrays which are used as ring buffers.

(def-concept managed-array)

;;; This facility uses the pool of simple vectors as the source for its vectors.

;;; Memory utilization of managed arrays is computed with the following formula.

;;;  elements / (elements + wasted-words + buffer-count + spine-wasted-words + 3)

;;; In the formula above, elements is the number of elements in the array,
;;; wasted words is the number of unused elements in the last buffer of the
;;; array, buffer-count is the one data tag word per buffer array,
;;; spine-wasted-words is the number of unused words in the spine array, and the
;;; constant 3 comes from the spine data tag, the marker for managed-array-p,
;;; and the stored length.

;;; The current allocation buffering works as follows.  For buffers less than or
;;; equal to 8 elements long, it allocates the actual size of the buffer.  For
;;; buffers less than or equal to 32 elements long, it will allocate the smallest
;;; multiple of four large enough to hold the array.  For buffers from 33 through
;;; 64, the smallest multiple of 8.  For buffers from 65 through 256 elements
;;; long, it will allocate the smallest multiple of 16 large enough to hold the
;;; array.  This allocation scheme wastes either less than 4 words per buffer, or
;;; achieves at least a 75% utilization.

;;; The parameter `managed-array-allocation-schemes' is a list of allocation
;;; schemes for the buffer sizes of managed array buffers.  

(defmacro partial-buffer-max-size (info)
  `(svref ,info 0))

(defmacro partial-buffer-grouping-factor (info)
  `(svref ,info 1))

(defmacro partial-buffer-pool-offset (info)
  `(svref ,info 2))

(defmacro partial-buffer-group-shift (info)
  `(svref ,info 3))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-simple make-partial-buffer-info (max-size grouping-factor pool-offset group-shift)
  (let ((array (make-array 4)))
    (setf (partial-buffer-max-size array) max-size)
    (setf (partial-buffer-grouping-factor array) grouping-factor)
    (setf (partial-buffer-pool-offset array) pool-offset)
    (setf (partial-buffer-group-shift array) group-shift)
    array))
)

(defmacro def-memory-allocation-schemes (name &rest clauses)
  `(defparameter ,name
     (list
       ,@(loop for (start-max-size start-grouping-factor count) in clauses
	       nconc (loop for i from 1 to count
			   for pool = 0 then (+f pool pool-size)
			   for previous-max-size = 0 then max-size
			   for max-size = start-max-size then (*f 2 max-size)
			   for grouping-factor = start-grouping-factor then (*f 2 grouping-factor)
			   for group-shift = (integer-length (1-f grouping-factor))
			   for size = (-f max-size previous-max-size)
			   for pool-size = (floorf size grouping-factor)
			   for pool-offset = (-f pool (if (=f previous-max-size 0)
							  0
							  (right-shiftf (1-f previous-max-size) group-shift)))
			   collect `(make-partial-buffer-info
				      ,max-size ,grouping-factor ,pool-offset ,group-shift))))))

(defmacro buffer-size-for-partial-buffer-given-allocation-scheme (needed-size info)
  `(1+f (logiorf (1-f ,needed-size) (1-f (partial-buffer-grouping-factor ,info)))))

(defmacro pool-for-partial-buffer-given-allocation-scheme (needed-size info)
  `(+f (partial-buffer-pool-offset ,info)
       (right-shiftf (1-f ,needed-size) (partial-buffer-group-shift ,info))))

;(=f 0 (modf-positive needed-size grouping-factor))
;; (=f 0 (logandf needed-size group-mask))
;(+f needed-size (-f grouping-factor (modf-positive needed-size grouping-factor)))
;; (1+f (logiorf (1-f needed-size) group-mask))
;sum of (ceilingf-positive (-f maximum-scheme-size previous-scheme-size) grouping-factor)
;; pool-start-index
;(ceilingf-positive (-f needed-size previous-scheme-size) grouping-factor)
;; (right-shiftf (-f needed-size previous-scheme-size) grouping-shift)

;managed-array-allocation-schemes                   8  1  1,  32  4  6
;environment-allocation-schemes                    64  8  1, 128 32  5
;frame-lookup-structure-vector-allocation-schemes  16  1  1,  32  4  6
;string-allocation-schemes                        128 32 14
;byte-vector-allocation-schemes                   128 16 11
;byte-vector-16-allocation-schemes                 64  8 14

(def-memory-allocation-schemes managed-array-allocation-schemes
    (8 1 1) (32 4 6))



;;; The function `buffer-size-for-partial-buffer' takes a the number of elements
;;; needed for a buffer and an allocation-scheme alist, and returns the actual
;;; size of the buffer that should be allocated.  The function `buffer-size-and-
;;; pool-for-partial-buffer' is similar to buffer-size-for-partial-buffer, but
;;; returns as a second value the pool this vector should fall into.

(declare-side-effect-free-function buffer-size-for-partial-buffer)

(defun-simple buffer-size-for-partial-buffer (needed-size allocation-schemes)
  (declare (type fixnum needed-size))
  (when (=f 0 needed-size) (setq needed-size 1))
  (loop for allocation-scheme in allocation-schemes
	when (<=f needed-size (partial-buffer-max-size allocation-scheme))
	  return (buffer-size-for-partial-buffer-given-allocation-scheme
		   needed-size
		   allocation-scheme)
	finally
	  (progn
	    #+development
	    (cerror "Use the needed size."
		    "Allocation scheme failure, seems to be no scheme for the ~
                   given size.")
	    (return needed-size))))

(declare-side-effect-free-function buffer-size-and-pool-for-partial-buffer)

(defun buffer-size-and-pool-for-partial-buffer (needed-size allocation-schemes)
  (when (=f 0 needed-size) (setq needed-size 1))
  (loop	for allocation-scheme in allocation-schemes
	for maximum-scheme-size fixnum = (partial-buffer-max-size allocation-scheme)
	when (<=f needed-size maximum-scheme-size)
	  return (values
		   (buffer-size-for-partial-buffer-given-allocation-scheme
		     needed-size
		     allocation-scheme)
		   (pool-for-partial-buffer-given-allocation-scheme
		     needed-size
		     allocation-scheme))
	finally
	  (progn
	    #+development
	    (cerror "Use the needed size."
		    "Allocation scheme failure, seems to be no scheme for the ~
                   given size.")
	    (return-from buffer-size-and-pool-for-partial-buffer
	      (values
		needed-size
		0)))))




;;; The function `partial-buffer-pool-index-given-length' takes an integer and
;;; an alist of memory allocation schemes, and returns the index of the pool
;;; which would hold a vector of that length after it had been rounded up to the
;;; allocation scheme's size for that vector.

(declare-side-effect-free-function partial-buffer-pool-index-given-length)

(defun-simple partial-buffer-pool-index-given-length
    (vector-length array-allocation-schemes)
  (declare (type fixnum vector-length))
  (loop for scheme in array-allocation-schemes
	for maximum-scheme-size fixnum = (partial-buffer-max-size scheme)
	when (<=f vector-length maximum-scheme-size)
	  return (pool-for-partial-buffer-given-allocation-scheme
		   vector-length scheme)
	finally
	  (progn
	    #+development
	    (error "The vector-length ~a is larger than the biggest ~
                      allocation scheme, ~a."
		   vector-length
		   maximum-scheme-size)
	    (return 0))))




;;; The function `gensym-list-maximum-buffer-sizes' takes an allocation scheme
;;; and returns a list of the maximum buffer sizes each element of a vector
;;; holding pools of arrays allocated according to the given allocation scheme.
;;; That is to say, the nth element of the returned list is the largest vector
;;; one would find the nth element of an array holding pools of vectors,
;;; assuming the given allocation scheme.  This function is used when printing
;;; out reports of memory usage per element in such a pool.

(defun-simple gensym-list-maximum-buffer-sizes (allocation-schemes)
  (let ((size-so-far 0)
	(maximum-sizes (gensym-list 0)))
    (declare (type fixnum size-so-far))
    (loop for scheme in allocation-schemes
	  for scheme-size fixnum = (partial-buffer-max-size scheme)
	  for grouping-factor fixnum = (partial-buffer-grouping-factor scheme)
	  do
      (loop for next-size fixnum = (+f size-so-far grouping-factor)
	    while (<=f next-size scheme-size)
	    do
	(setq size-so-far next-size)
        (gensym-push size-so-far maximum-sizes)))
    (nreverse maximum-sizes)))




;;; The macro `managed-array-identity-marker' takes a vector at least one
;;; element long, and returns the contents of the identity marker spot in that
;;; vector.

(defmacro managed-array-identity-marker (non-empty-vector)
  `(svref ,non-empty-vector 0))




;;; The macro `managed-array-length' takes a managed array and returns its
;;; allocated length.

(defmacro managed-array-length (managed-array)
  `(the fixnum (svref ,managed-array 1)))




;;; The macro `managed-array-buffer' takes a managed-array and a zero based
;;; index to a buffer in that array, and returns the buffer.

(defmacro managed-array-buffer (managed-array buffer-index)
  (if (constantp buffer-index)
      `(svref ,managed-array ,(+ (eval buffer-index) 2))
      `(svref ,managed-array (+f ,buffer-index 2))))




;;; The object stored in `managed-array-unique-marker' is placed in element zero
;;; of managed-arrays and is queried by managed-array-p.

(defvar-of-special-global managed-array-unique-marker (cons 'managed-array nil))




;;; The macro `managed-array-p' returns whether or not this object is an
;;; allocated managed-array.

(def-substitution-macro managed-array-p (thing)
  (and (simple-vector-p thing)
;       (>f (length (the simple-vector thing)) 0)
       (eq (managed-array-identity-marker thing)
	   managed-array-unique-marker)))

;; We don't allocate zero length simple vectors in anything I know, and this is
;; becoming a performance concern after looking at profiling.  Commenting out
;; the length test.  -jra 1/22/92





(defconstant maximum-managed-array-size
	      (*f (-f maximum-managed-array-buffer-size 2)
		  maximum-managed-array-buffer-size))

(defconstant maximum-in-place-array-size
  (-f maximum-managed-array-buffer-size 2))

;;; The function `allocate-managed-array' takes a number from 0 through 1046528
;;; (1Meg - 2K) and returns a managed-array of that length.

;;; As a feature for use in future run time versions of G2, it takes an optional
;;; second argument called make-exactly which can be used when this vector is
;;; very unlikely to be reclaimed.  If this is true, then the returned managed
;;; array will have buffer sizes which are exactly as long as is requested.  This
;;; should only be used in run-time versions of G2 where different knowledge
;;; bases will not be loaded over one another, and then only for code bodies or
;;; history buffers.  Since we don't have those now, this feature should not
;;; currently be used.

;;; The optional argument dont-initialize can be used to stop this function from
;;; initializing the new managed array to contain NILs.



(defun allocate-managed-array (length
				&optional (dont-initialize nil)
				(make-exactly nil))
  (declare (type fixnum length))
  #+development
  (when (or (<f length 0) (>f length maximum-managed-array-size))
    (error "Can't make a managed array ~a elements long." length))
  (let (spine-vector)
    (cond ((<=f length maximum-in-place-array-size)
	   (setq spine-vector
		 (allocate-managed-simple-vector-for-array
		   (if make-exactly
		       (+f length managed-array-index-offset)
		       (buffer-size-for-partial-buffer
			 (+f length managed-array-index-offset)
			 managed-array-allocation-schemes)))))
	  (t
	   (let* ((full-size-buffers
		    (floorf-positive length maximum-managed-array-buffer-size))
		  (size-of-partial-buffer
		    (modf-positive length maximum-managed-array-buffer-size))
		  (total-buffers (if (>f size-of-partial-buffer 0)
				     (+f full-size-buffers 1)
				     full-size-buffers)))
	     (declare (type fixnum
			    full-size-buffers size-of-partial-buffer total-buffers))
	     (setq spine-vector
		   (allocate-managed-simple-vector-for-array
		     (if make-exactly
			 (+f total-buffers managed-array-index-offset)
			 (buffer-size-for-partial-buffer
			   (+f total-buffers managed-array-index-offset)
			   managed-array-allocation-schemes))))

	     (loop for full-buffer-index from 0 below full-size-buffers
		   do
	       (setf (managed-array-buffer spine-vector full-buffer-index)
		     (allocate-managed-simple-vector-for-array
		       maximum-managed-array-buffer-size)))
	     (when (>f size-of-partial-buffer 0)
	       (setf (managed-array-buffer spine-vector (-f total-buffers 1))
		     (allocate-managed-simple-vector-for-array
		       (if make-exactly
			   size-of-partial-buffer
			 (buffer-size-for-partial-buffer
			   size-of-partial-buffer
			   managed-array-allocation-schemes))))))))
    (setf (managed-array-identity-marker spine-vector)
	  managed-array-unique-marker)
    (setf (managed-array-length spine-vector) length)
    (unless dont-initialize
      (fill-managed-array spine-vector nil))
    spine-vector))


;;; The macro `managed-svref' takes a managed array and an index, and returns
;;; that element of the given array.  This form can be used with SETF to mutate
;;; a value in the array.  In development this form will do bounds checking on
;;; the given index, but in distribution code it performs direct svrefs on the
;;; internal structures of the managed array.


(defmacro managed-svref (managed-array index)
  (if (constantp index)
      (multiple-value-bind (spine-index buffer-index)
	  (floor (eval index) maximum-managed-array-buffer-size)
	`(cond ((<=f (managed-array-length ,managed-array)
		     maximum-in-place-array-size)
		(svref ,managed-array (+f ,index managed-array-index-offset)))
	       (t (svref (managed-array-buffer ,managed-array ,spine-index)
			 ,buffer-index))))
      (let ((array-var (if (or (symbolp managed-array)
			       (symbolp index))
			   managed-array
			   (gensym)))
	    (index-var (if (symbolp index)
			   index
			   (gensym)))
	    (index-shift
	      (+f (-f (integer-length maximum-managed-array-buffer-size)) 1))
	    (index-mask (-f maximum-managed-array-buffer-size 1)))
	(if (and (eq array-var managed-array)
		 (eq index-var index)
		 (not (eval-feature :development)))
	    `(cond ((<=f (managed-array-length ,managed-array)
			maximum-in-place-array-size)
		    (svref ,managed-array (+f ,index-var managed-array-index-offset)))
		   (t
		    (svref (managed-array-buffer ,array-var
						 (ashf ,index-var ,index-shift))
			   (logandf ,index-var
				    ,index-mask))))
	    `(let* (,@(if (neq array-var managed-array)
			  `((,array-var ,managed-array))
			  nil)
		      ,@(if (neq index-var index)
			    `((,index-var ,index))
			    nil))
	       (assert-for-development
		 (<f ,index-var (managed-array-length ,array-var))
                 "Managed svref out of range.  Array = ~a, Length = ~a, Index = ~a"
		 ,array-var (managed-array-length ,array-var) ,index-var)
	       (cond ((<=f (managed-array-length ,managed-array)
			   maximum-in-place-array-size)
		      (svref ,managed-array (+f ,index-var managed-array-index-offset)))
		     (t
		      (svref (managed-array-buffer ,array-var
						   (ashf ,index-var ,index-shift))
			     (logandf ,index-var
				      ,index-mask)))))))))







#+development
(defmacro managed-svref-bounds-error (managed-array index)
  `(progn-for-development
     (error "Managed svref out of range.  Array = ~a, Length = ~a, Index = ~a"
	    ,managed-array (managed-array-length ,managed-array) ,index)))

#+development
(defmacro managed-svset-bounds-error (managed-array index)
  `(progn-for-development
     (error
       "Setf of managed-svref out of range.  Array = ~a, Length ~a, Index = ~a"
       ,managed-array (managed-array-length ,managed-array) ,index)))

(defmacro managed-svset (managed-array index value)
  (if (constantp index)
      (multiple-value-bind (spine-index buffer-index)
	  (floor (eval index) maximum-managed-array-buffer-size)
	`(cond ((<=f (managed-array-length ,managed-array)
		     maximum-in-place-array-size)
		(setf (svref ,managed-array ,(+f index managed-array-index-offset)) ,value))
	       (t
		(setf (svref (managed-array-buffer ,managed-array ,spine-index)
			     ,buffer-index) ,value))))
      (let ((array-var (if (or (symbolp managed-array)
			       (symbolp index))
			   managed-array
			   (gensym)))
	    (index-var (if (symbolp index)
			   index
			   (gensym)))
	    (index-shift
	      (+ (- (integer-length maximum-managed-array-buffer-size)) 1))
	    (index-mask (- maximum-managed-array-buffer-size 1)))
	(if (and (eq array-var managed-array)
		 (eq index-var index)
		 (not (eval-feature :development)))
	    `(cond ((<=f (managed-array-length ,managed-array)
			 maximum-in-place-array-size)
		    (setf (svref ,managed-array (+f ,index-var managed-array-index-offset)) ,value))
		   (t
		    (setf (svref (managed-array-buffer ,array-var
						       (ashf ,index-var ,index-shift))
				 (logandf ,index-var
					  ,index-mask)) ,value)))
	    `(let* (,@(if (neq array-var managed-array)
			  `((,array-var ,managed-array))
			  nil)
		      ,@(if (neq index-var index)
			    `((,index-var ,index))
			    nil))
	       #+development
	       (when (>=f ,index-var (managed-array-length ,array-var))
		 (managed-svset-bounds-error ,array-var ,index-var))
	       (cond ((<=f (managed-array-length ,managed-array)
			  maximum-in-place-array-size)
		      (setf (svref ,managed-array (+f ,index-var managed-array-index-offset)) ,value))
		     (t
		      (setf (svref (managed-array-buffer ,array-var
						   (ashf ,index-var ,index-shift))
			     (logandf ,index-var
				      ,index-mask))
			    ,value))))))))


(defsetf managed-svref managed-svset)

;;; The function `reclaim-managed-array' takes a managed array and reclaims it.

(defun-void reclaim-managed-array (managed-array)
  #+development
  (unless (managed-array-p managed-array)
    (error "Attempted to reclaim ~a as a managed-array." managed-array))
  (when (>f (managed-array-length managed-array) maximum-in-place-array-size)
    (loop for buffer-index
	  from 0
	      below (ceilingf-positive (managed-array-length managed-array)
				       maximum-managed-array-buffer-size)
	  do
      (reclaim-managed-simple-vector-for-array
	(managed-array-buffer managed-array buffer-index))))
  (atomic-exchange (managed-array-identity-marker managed-array) nil)
  (reclaim-managed-simple-vector-for-array managed-array))

(defun reclaim-if-managed-array (managed-array?)
  (when (managed-array-p managed-array?)
    (reclaim-managed-array managed-array?)))




;;; The function `gsi-allocate-managed-array' takes a number and returns a
;;; managed simple vector created with allocate-manged-simple-vector.
;;; Please see allocate-manged-simple-vector for bounds limitations.

;;; The reason GSI doesn't use regular managed arrays is cuz GSI programmers
;;; (read C programmers) 'need' to perform address arithmetic on arrays given
;;; them by GSI.

;;; ... AND the reason GSI designers chose to create these aliases for
;;; allocate/reclaim-managed-vector is so that it will be simple to replace
;;; the implementation (read: allocate/reclaim-managed-simple-vector) if it turns
;;; we made a mistake...  :-|  (and we did, but Jim has saved us!)

;;; Since jra added support for managed-simple-vectors larger than 1024, and did
;;; so with an allocation strategy of rounding requests up to the next nearest
;;; multiple of 1024, these functions must adapt.  When vectors larger than 1024
;;; are ordered by gsi-allocate-managed-array, it places the vector-size requested
;;; by the user in the last element of the new vector.  gsi-managed-array-length
;;; is adapted by having it test the actual length - if greater than 1024, it
;;; returns the value found in the last element as the length, otherwise it
;;; returns the actual length. -paf! 23may95 

(defmacro gsi-managed-svref (v ref)
  `(svref ,v ,ref))

(defsetf gsi-managed-svref gsi-managed-svset)

(defmacro gsi-managed-svset (gsi-managed-array index value)
  `(setf (svref ,gsi-managed-array ,index) ,value))

(defun-simple gsi-allocate-managed-array (requested-length)
  (let* ((modified-requested-length
	   (cond
	     ((>f requested-length maximum-managed-array-buffer-size)
	      (+f requested-length 1)) ; extra slot to hold requested length.
	     ((=f requested-length 0)
	      (1+f maximum-managed-array-buffer-size))
	     (t requested-length)))
	 (vector (allocate-managed-simple-vector modified-requested-length))
	 (actual-length (length vector)))
    (when (>f actual-length maximum-managed-array-buffer-size)
      (setf (gsi-managed-svref vector (-f actual-length 1))
	    requested-length))
    vector))

(defun-simple gsi-managed-array-length (gsi-managed-array)
  (let* ((actual-length (length gsi-managed-array)))
    (if (>f actual-length maximum-managed-array-buffer-size)
	(gsi-managed-svref gsi-managed-array (-f actual-length 1))
	actual-length)))

;;; The function `gsi-reclaim-managed-array' takes a GSI managed array (managed
;;; simple vector)and reclaims it.

(defun-void gsi-reclaim-managed-array (managed-array)
  (reclaim-managed-simple-vector managed-array))





;;; The macros `gsi-allocate-integer-vector', `gsi-reclaim-integer-vector' and
;;; `integer-vector-aref' are hacks to allow GSI to build arrays holding longs.  It
;;; is utterly unprincipled in its fooling Chestnut to perform unnatural acts at
;;; run-time.  In the future when we get religion (a.k.a. never) we will rewrite
;;; this to use true arrays of longs as implemented by Chestnut.  For the time
;;; being, we will slam longs into elements of simple vectors using setf of
;;; integer-vector-aref, and woe to those that confuse this in the implementation.

;;; This implementation is based on the managed-simple-vector pool for
;;; allocation and reclaiming, and Chestnut's translation of aref of simple
;;; arrays of (signed-byte 32) into something that looks like arrays of type
;;; long in C.  Note that the (signed-byte 32) stuff is only used to get
;;; Chestnut to translate to type long, but in fact in compilations on Alphas or
;;; other 64 bit long machines, this will be an array of 64 bit entities.

;;; Note that in Lisp, this will confuse the hell out of anything that attempts
;;; to determine the types of the elements of this array, for example the
;;; bytes-in-item system procedures for computing memory usage.  Arrays that
;;; have these operations performed on them will break such data structure
;;; walkers, so once again, take care.  -jra  5/11/94

(defmacro gsi-allocate-integer-vector (length)
  `(gsi-allocate-managed-array ,length))

(defmacro gsi-reclaim-integer-vector (simple-integer-vector)
  `(gsi-reclaim-managed-array ,simple-integer-vector))




;;; The macro `integer-vector-aref' is used to access and set longs into elements
;;; of simple-long-arrays.  Note that it is the implementors responsibility to
;;; recognize when a simple-long-array is full of longs, since on the Lisp side
;;; of things these longs might masquerade as any type of Lisp object, fixnums,
;;; pointers, conses, whatever.  Use with care!

(defmacro integer-vector-aref (gsi-managed-array index)
  (if (eval-feature :chestnut-trans)
      `(aref (the (simple-array (signed-byte 32) (*)) ,gsi-managed-array)
	     (the fixnum ,index))
      `(svref ,gsi-managed-array ,index)))




;;; The macro `copy-simple-vector-portion' takes a source simple vector, a
;;; source start index, an element count, a destination simple vector, and a
;;; destination start index.  It then copies element count elements of the
;;; source array starting at source index into the destination array starting at
;;; destination-index.  This operation should be optimized for each system as
;;; much as is possible.

(defmacro copy-simple-vector-portion
    (source-simple-vector source-index element-count
			  destination-simple-vector destination-index)
  (let ((vector1 (gensym))
	(index1 (gensym))
	(index1-limit (gensym))
	(vector2 (gensym))
	(index2 (gensym)))
    `(let* ((,vector1 ,source-simple-vector)
	    (,index1 ,source-index)
	    (,index1-limit (+f ,index1 ,element-count))
	    (,vector2 ,destination-simple-vector)
	    (,index2 ,destination-index))
       (declare (type fixnum ,index1 ,index1-limit ,index2)
		(type simple-vector ,vector1 ,vector2))
       #+development
       (when (or (>f ,index1-limit (length ,vector1))
		 (>f (+f ,index2 (-f ,index1-limit ,index1))
		     (length ,vector2)))
	 (error "Copy simple vector portion out of bounds"))
       (loop while (<f ,index1 ,index1-limit)
	     do
	 (setf (svref ,vector2 ,index2) (svref ,vector1 ,index1))
	 (incff ,index1)
	 (incff ,index2)))))

(defun copy-simple-vector-portion-function
	  (source-simple-vector source-index element-count
	   destination-simple-vector destination-index)
  (copy-simple-vector-portion
    source-simple-vector source-index element-count
    destination-simple-vector destination-index))




;;; The function `adjust-managed-array' takes a managed array, and a new length,
;;; and returns a managed array of the requested length.  Note that the returned
;;; managed array may or may not be EQ to the managed array passed in, so you
;;; must receive the new value and replace old pointers to the managed array
;;; with pointers to the new array.  By default the new array contains all of
;;; the elements of the old array which are still in bounds.  The first optional
;;; argument, dont-copy, controls whether this function will make any effort to
;;; copy old contents from the buffers of the old array to any buffers of the
;;; new array.  The second optional argument, dont-initialize, controls whether
;;; the new portion of a grown array will be initialized to contain NILs.

(defun adjust-managed-array
    (managed-array new-length
		   &optional (dont-copy nil) (dont-initialize nil))
  (let ((old-length (managed-array-length managed-array))
	(rounded-new-length 0))
    (declare (type fixnum old-length rounded-new-length))
    (when (=f new-length old-length)
      (return-from adjust-managed-array managed-array))
    (cond
      ((and (>f old-length maximum-in-place-array-size)
	    (>f new-length maximum-in-place-array-size))
       (multiple-value-bind (old-full-buffers old-remainder)
	   (floorf old-length maximum-managed-array-buffer-size)
	 (let ((new-full-buffers
		 (floorf-positive new-length maximum-managed-array-buffer-size))
	       (new-remainder
		 (modf-positive new-length maximum-managed-array-buffer-size)))
	   (declare (type fixnum new-full-buffers new-remainder))
	   (let ((old-total-buffers
		   (if (>f old-remainder 0)
		       (+f old-full-buffers 1)
		       old-full-buffers))
		 (new-total-buffers
		   (if (>f new-remainder 0)
		       (+f new-full-buffers 1)
		       new-full-buffers)))
	     (setq managed-array
		   (cond
		     ((=f new-total-buffers old-total-buffers)
		      (adjust-final-buffer-of-managed-array
			managed-array dont-copy dont-initialize new-total-buffers
			(if (=f old-remainder 0)
			    maximum-managed-array-buffer-size
			    old-remainder)
			(if (=f new-remainder 0)
			    maximum-managed-array-buffer-size
			    new-remainder))
		      (setf (managed-array-length managed-array) new-length)
		      managed-array)
		     ((>f new-total-buffers old-total-buffers)
		      (grow-managed-array
			managed-array dont-copy dont-initialize
			old-full-buffers old-remainder old-total-buffers
			new-length new-full-buffers new-remainder new-total-buffers))
		     (t
		      (shrink-managed-array
			managed-array dont-copy
			old-total-buffers
			new-length new-full-buffers new-remainder new-total-buffers))
	       ))))))

      ;; When changing an in-place array within an allocation scheme boundary,
      ;; just reset the length and potentially initialize the new elements.
      ((and (<=f old-length maximum-in-place-array-size)
	    (<=f new-length maximum-in-place-array-size)
	    (progn
	      (setq rounded-new-length
		    (buffer-size-for-partial-buffer
		      (+f new-length managed-array-index-offset)
		      managed-array-allocation-schemes))
	      (=f (length-of-simple-vector managed-array)
		  rounded-new-length)))
       (setf (managed-array-length managed-array) new-length)
       (when (and (>f new-length old-length)
		  (not dont-initialize))
	 (loop for index from (+f managed-array-index-offset old-length)
			 below (+f managed-array-index-offset new-length)
	       do
	   (setf (svref managed-array index) nil))))

      ((>f new-length old-length)
       (setq managed-array
	     (grow-managed-array
	       managed-array dont-copy dont-initialize
	       nil nil nil new-length nil nil nil)))
      (t
       (setq managed-array
	     (shrink-managed-array
	       managed-array dont-copy nil new-length nil nil nil))))

    managed-array))





;;; The function adjust-final-buffer-of-managed-array is called when the size of
;;; an existing buffer within the managed array changes.  This function attempts
;;; to continue using the old buffer in that location, but if the buffer vector
;;; must be replaced, this function will do that.  If the buffer is replaced and
;;; dont-copy is nil, then the elements shared by the old and new buffers are
;;; copied into the new buffer.  If the new buffer is longer and dont-initialize
;;; is nil, then the new elements of the longer final buffer will be initialized
;;; to nil.  This is an internal function to adjust-managed-array,
;;; grow-managed-array, and shrink-managed-array.

(defun adjust-final-buffer-of-managed-array
       (managed-array dont-copy dont-initialize
	total-buffers old-final-buffer-length new-final-buffer-length)
  (let* ((old-buffer (managed-array-buffer managed-array (-f total-buffers 1)))
	 (old-actual-buffer-length (length old-buffer))
	 (new-actual-buffer-length
	   (buffer-size-for-partial-buffer
	     new-final-buffer-length
	     managed-array-allocation-schemes)))
    (when (/=f new-actual-buffer-length old-actual-buffer-length)
      (let ((new-buffer (allocate-managed-simple-vector
			  new-actual-buffer-length)))
	(unless dont-copy
	  (copy-simple-vector-portion-function
	    old-buffer 0
	    (minf new-final-buffer-length old-final-buffer-length)
	    new-buffer 0))
	(setf (managed-array-buffer managed-array (-f total-buffers 1))
	      new-buffer)
	(reclaim-managed-simple-vector old-buffer)
	(setq old-buffer new-buffer)))
    (when (and (not dont-initialize)
	       (>f new-final-buffer-length old-final-buffer-length))
      (loop for index from old-final-buffer-length
		      below new-final-buffer-length
	    do
        (setf (svref old-buffer index) nil)))))




;;; The function grow-managed-array is called when a managed array is adjusted
;;; so that it now will contain additional buffers.  This function first adjusts
;;; the last buffer of the old array to be maximum size, replaces the spine
;;; array if necessary, resets the managed-array-length, allocates as many new
;;; full buffers as are necessary, and then allocates any partially filled
;;; buffer required.  This is an internal function to adjust-managed-array.

(defun grow-managed-array
       (managed-array dont-copy dont-initialize
	old-full-buffers old-remainder old-total-buffers
	new-length new-full-buffers new-remainder new-total-buffers)
  (cond 
    ((<=f (managed-array-length managed-array) maximum-in-place-array-size)
     (let ((old-managed-array managed-array))
       (setq managed-array (allocate-managed-array new-length))
       (copy-managed-array-portion
	 old-managed-array 0 (managed-array-length old-managed-array)
	 managed-array 0)
       (reclaim-managed-array old-managed-array)))
    (t
     (when (/=f old-full-buffers old-total-buffers)
       (adjust-final-buffer-of-managed-array
	 managed-array dont-copy dont-initialize old-total-buffers
	 old-remainder maximum-managed-array-buffer-size))
     (let ((new-spine-length
	     (buffer-size-for-partial-buffer
	       (+f new-total-buffers 2)
	       managed-array-allocation-schemes)))
       (when (/=f (length managed-array) new-spine-length)
	 (let ((new-spine (allocate-managed-simple-vector-for-array new-spine-length)))
	   (copy-simple-vector-portion-function
	     managed-array 2 old-total-buffers new-spine 2)
	   (atomic-exchange (managed-array-identity-marker managed-array) nil)
	   (reclaim-managed-simple-vector-for-array managed-array)
	   (atomic-exchange (managed-array-identity-marker new-spine)
		 managed-array-unique-marker)
	   (setq managed-array new-spine)))
       (setf (managed-array-length managed-array) new-length)
       (loop for spine-index from old-total-buffers below new-full-buffers
	     for new-buffer = (allocate-managed-simple-vector-for-array
				maximum-managed-array-buffer-size)
	     do
	 (unless dont-initialize
	   (loop for buffer-index from 0 below maximum-managed-array-buffer-size do
	     (atomic-exchange (svref new-buffer buffer-index) nil)))
	 (atomic-exchange (managed-array-buffer managed-array spine-index)
			  new-buffer))
       (when (/=f new-full-buffers new-total-buffers)
	 (let ((new-buffer (allocate-managed-simple-vector
			     (buffer-size-for-partial-buffer
			       new-remainder
			       managed-array-allocation-schemes))))
	   (unless dont-initialize
	     (loop for buffer-index from 0 below new-remainder do
	       (atomic-exchange (svref new-buffer buffer-index) nil)))
	   (atomic-exchange (managed-array-buffer managed-array (-f new-total-buffers 1))
			    new-buffer))))))
  managed-array)




;;; The function shrink-managed-array is called when a managed array is adjusted
;;; such that it requires fewer total buffers.  First this function reclaims any
;;; buffers which are being discarded.  If the final buffer of the newly sized
;;; array does not need to be full sized, it is adjusted to its new partial
;;; size.  If the buffer count has decreased enough that a smaller spine array
;;; is needed, the old spine is replaced.  Finally, the managed-array-length is
;;; reset to the new length.

(defun shrink-managed-array
       (managed-array dont-copy old-total-buffers
	new-length new-full-buffers new-remainder new-total-buffers)
  (cond ((<=f new-length maximum-in-place-array-size)
	 (let ((old-managed-array managed-array))
	   (setq managed-array (allocate-managed-array new-length))
	   (copy-managed-array-portion
	     old-managed-array 0 (managed-array-length managed-array)
	     managed-array 0)
	   (reclaim-managed-array old-managed-array)))
	(t
	 (loop for buffer-index from new-total-buffers below old-total-buffers
	       do
	   (reclaim-managed-simple-vector-for-array
	     (managed-array-buffer managed-array buffer-index)))
	 (when (/=f new-full-buffers new-total-buffers)
	   (adjust-final-buffer-of-managed-array
	     managed-array dont-copy t new-total-buffers
	     maximum-managed-array-buffer-size new-remainder))
	 (let ((new-spine-length
		 (buffer-size-for-partial-buffer
		   (+f new-total-buffers 2)
		   managed-array-allocation-schemes)))
	   (when (/=f new-spine-length (length managed-array))
	     (let ((new-spine (allocate-managed-simple-vector-for-array new-spine-length)))
	       (copy-simple-vector-portion-function
		 managed-array 2 new-total-buffers new-spine 2)
	       (atomic-exchange (managed-array-identity-marker managed-array) nil)
	       (reclaim-managed-simple-vector managed-array)
	       (atomic-exchange (managed-array-identity-marker new-spine)
		     managed-array-unique-marker)
	       (setq managed-array new-spine))))
	 (setf (managed-array-length managed-array) new-length)))
  managed-array)



;;; The function `shrink-or-delete-managed-array-null-elements' is used to
;;; adjust the size of or completely delete managed arrays after elements have
;;; been removed from them.  This function takes a managed-array and adjusts its
;;; size to remove from its tail end any elements which contain NIL.  If the
;;; entire array contains NILs, it is deleted, and NIL is returned.  Any users
;;; of this function should replace their previous pointers to the managed array
;;; with whatever is returned by this function.

(defun shrink-or-delete-managed-array-null-elements (managed-array)
  (loop with array-length fixnum = (managed-array-length managed-array)
	for index from (-f array-length 1) downto 0
	do
    (when (managed-svref managed-array index)
      (let ((new-length (+f index 1)))
	(return 
	  (if (=f new-length array-length)
	      managed-array
	      (adjust-managed-array managed-array new-length)))))
	finally
	  ;; Array is empty.
	  (reclaim-managed-array managed-array)
	  (return nil)))



;;; The function `copy-from-simple-vector-into-managed-array' takes a
;;; simple-vector, an index into the simple vector, a count of the elements to
;;; copy, a managed array, and an index into the managed array at which to begin
;;; the copy.  Note that this function does not perform bounds checks on either
;;; the simple vector or the managed array, and so it must be handed valid
;;; copying instructions.

(defun copy-from-simple-vector-into-managed-array
    (simple-vector vector-index count managed-array array-index)
  (declare (type fixnum vector-index count array-index)
	   (type simple-vector simple-vector managed-array))
  #+development
  (when (or (>f (+f vector-index count) (length simple-vector))
	    (>f (+f array-index count) (managed-array-length managed-array)))
    (error "Copy-from-simple-vector-into-managed-array out of bounds."))
  (cond ((<=f (managed-array-length managed-array)
	      maximum-in-place-array-size)
	 (copy-simple-vector-portion-function
	   simple-vector vector-index count
	   managed-array (+f array-index managed-array-index-offset)))
	(t
	 (multiple-value-bind (managed-buffer-number buffer-index)
	     (floorf array-index maximum-managed-array-buffer-size)
	   (declare (type fixnum managed-buffer-number buffer-index))
	   (loop while (>f count 0)
		 for elements-to-copy fixnum
				      = (minf (-f maximum-managed-array-buffer-size buffer-index)
					      count)
		 do
	     (copy-simple-vector-portion-function
	       simple-vector vector-index elements-to-copy
	       (managed-array-buffer managed-array managed-buffer-number) buffer-index)
	     (decff count elements-to-copy)
	     (incff vector-index elements-to-copy)
	     (incff managed-buffer-number)
	     (setq buffer-index 0))))))




;;; The function `copy-from-managed-array-into-simple-vector' takes a managed
;;; array, and index into the managed array, a count of the elements to copy, a
;;; simple vector, and an index into the simple vector at which to begin the
;;; copy.  Note that this function does not perform bounds checks on either the
;;; simple vector or the managed array, and so it must be handed valid copying
;;; instructions.

(defun copy-from-managed-array-into-simple-vector
    (managed-array array-index count simple-vector vector-index)
  (declare (type fixnum array-index count vector-index)
	   (type simple-vector managed-array simple-vector))
  #+development
  (when (or (>f (+f array-index count) (managed-array-length managed-array))
	    (>f (+f vector-index count) (length simple-vector)))
    (error "Copy-from-managed-array-into-simple-vector out of bounds."))
  (cond ((<f (managed-array-length managed-array) maximum-in-place-array-size)
	 (copy-simple-vector-portion-function
	   managed-array (+f array-index managed-array-index-offset)
	   count simple-vector vector-index))
	(t
	 (multiple-value-bind (managed-buffer-number buffer-index)
	     (floorf array-index maximum-managed-array-buffer-size)
	   (declare (type fixnum managed-buffer-number buffer-index))
	   (loop while (>f count 0)
		 for elements-to-copy fixnum
				      = (minf (-f maximum-managed-array-buffer-size buffer-index)
					      count)
		 do
	     (copy-simple-vector-portion-function
	       (managed-array-buffer managed-array managed-buffer-number) buffer-index
	       elements-to-copy simple-vector vector-index)
	     (decff count elements-to-copy)
	     (incff vector-index elements-to-copy)
	     (incff managed-buffer-number)
	     (setq buffer-index 0))))))




;;; The function `copy-managed-array-portion' takes a source managed array, a
;;; start point, an element count, a destination managed array, and a to point.
;;; The function will copy those elements of the source managed array starting
;;; at start point and copy element count elements into the destination array,
;;; starting at the to point.  This function is more efficient than performing
;;; the iteration yourself using managed-svref, because of the utilization of
;;; implementation specific optimizations and the internals of managed arrays.

;;; At the top level this function works by organizing copy operations out of
;;; the source array.  These copies out of source arrays will turn a copy into
;;; either one or two of the destination arrays buffers.

(defun copy-managed-array-portion
    (source-array source-index element-count
		  destination-array destination-index)
  (declare (type fixnum source-index element-count destination-index)
	   (type simple-vector source-array destination-array))
  #+development
  (when (or (>f (+f source-index element-count)
		(managed-array-length source-array))
	    (>f (+f destination-index element-count)
		(managed-array-length destination-array)))
    (error "Copy-managed-array-portion referencing more elements than the ~
            arrays have."))
  (when (>f element-count 0)
    (multiple-value-bind (source-buffer-number source-buffer-index)
	(floorf source-index maximum-managed-array-buffer-size)
      (declare (type fixnum source-buffer-number source-buffer-index))
      ;;trapdoor
      (cond ((<=f (managed-array-length source-array)
		  maximum-in-place-array-size)
	     (copy-from-simple-vector-into-managed-array
	       source-array (+f source-index managed-array-index-offset)
	       element-count
	       destination-array destination-index))
	    (t
	     (loop while (>f element-count 0)
		   for elements-to-copy fixnum
					= (minf (-f maximum-managed-array-buffer-size
						    source-buffer-index)
						element-count)
					then (minf maximum-managed-array-buffer-size element-count)
		   do
	       (copy-from-simple-vector-into-managed-array
		 (managed-array-buffer source-array source-buffer-number)
		 source-buffer-index elements-to-copy
		 destination-array destination-index)
	       (decff element-count elements-to-copy)
	       (incff destination-index elements-to-copy)
	       (incff source-buffer-number)
	       (setq source-buffer-index 0)))))))




;;; The function `fill-managed-array' takes a managed array and some Lisp
;;; object, and will set all elements of the given managed array to the given
;;; value.

(defun fill-managed-array (managed-array thing)
  (declare (type simple-vector managed-array))
  (let* ((length (managed-array-length managed-array)))
    (declare (type fixnum length))
    (cond ((<=f length maximum-in-place-array-size)
	   (loop for index from managed-array-index-offset below
		 (+f length managed-array-index-offset)
		 do
	     (atomic-exchange (svref managed-array index) thing)))
	  (t
	   (multiple-value-bind (full-buffers partial-buffer)
	       (floorf length maximum-managed-array-buffer-size)
	     (declare (type fixnum full-buffers partial-buffer))
	     (loop for buffer-index from 0 below full-buffers
		   for full-buffer = (managed-array-buffer managed-array buffer-index)
		   do
	       (loop for index from 0 below maximum-managed-array-buffer-size
		     do
		 (atomic-exchange (svref full-buffer index) thing)))
	     (when (/=f partial-buffer 0)
	       (loop with last-buffer = (managed-array-buffer managed-array full-buffers)
		     for index from 0 below partial-buffer
		     do
		 (atomic-exchange (svref last-buffer index) thing)))
	     managed-array)))))




;;; The function `rotate-managed-array' performs rotations of the values inside
;;; a managed array, such that the value in a given index is moved to index 0,
;;; and all other values are rotated such that they are in the same relative
;;; position in terms of the new value in zero.  This operation is provided so
;;; that managed arrays being used as ring buffers and efficiently move the date
;;; line back to element zero before adding new elements onto the end of the
;;; array.

(defun rotate-managed-array (managed-array index-to-rotate)
  (when (/=f index-to-rotate 0)
    (let* ((length (managed-array-length managed-array))
	   new-array-or-vector
	   (high-shift-size (-f length index-to-rotate)))
      (declare (type fixnum length high-shift-size))
      (cond ((<=f length maximum-in-place-array-size)
	     (setq new-array-or-vector
		   (allocate-managed-simple-vector index-to-rotate))
	      ;;first get the values out of the beginning part of the array
	      (loop for copy-index fixnum from 0 below index-to-rotate
		    do
		(atomic-exchange (svref new-array-or-vector copy-index)
				 (svref managed-array
					(+f copy-index managed-array-index-offset))))
	      ;; move the high part down
	      (loop for from-index fixnum from
		    (+f index-to-rotate managed-array-index-offset)
				   below (+f length managed-array-index-offset)
		    for to-index from managed-array-index-offset
		    do
		(atomic-exchange (svref managed-array to-index)
				 (svref managed-array from-index)))
	      ;; copy from scratch area
	      (loop for to-index fixnum from
		    (+f high-shift-size managed-array-index-offset)
				 below (+f length managed-array-index-offset)
		    for from-index from 0
		    do
		(atomic-exchange (svref managed-array to-index)
				 (svref new-array-or-vector from-index)))
	      (reclaim-managed-simple-vector-for-array new-array-or-vector))
	    (t
	     (setq new-array-or-vector (allocate-managed-array length))
	     (copy-managed-array-portion
	       managed-array index-to-rotate high-shift-size
	       new-array-or-vector 0)
	     (copy-managed-array-portion
	       managed-array 0 index-to-rotate
	       new-array-or-vector high-shift-size)
	     (loop for buffer-index
		   from 0 below (ceilingf-positive
				  length maximum-managed-array-buffer-size)
		   do
	       (reclaim-managed-simple-vector-for-array
		 (managed-array-buffer managed-array buffer-index))
	       (atomic-exchange (managed-array-buffer managed-array buffer-index)
				(managed-array-buffer new-array-or-vector buffer-index)))
	     (reclaim-managed-simple-vector-for-array new-array-or-vector)))))
  managed-array)


;;; The function `insert-into-managed-array' inserts new-element into given
;;; position of managed array, growing the array and moving all following
;;; elements over one. A possibly new managed-array is returned.

(defun insert-into-managed-array (managed-array position new-element)
  (declare (type simple-vector managed-array))
  (let ((length (managed-array-length managed-array)))
    (declare (type fixnum length))
    (assert-for-development (<=f 0 position length))
    (setq managed-array (adjust-managed-array managed-array (1+f length)))
    (loop for index from length downto (1+f position) doing
      (setf (managed-svref managed-array index) (managed-svref managed-array (1-f index))))
    (setf (managed-svref managed-array position) new-element)
    managed-array))


;;; The function `delete-managed-array-element' removes the position-th element
;;; from the managed-array, moving all following elements back one.  A possibly
;;; new managed-array is returned.

(defun delete-managed-array-element (managed-array position)
  (declare (type simple-vector managed-array))
  (let ((length (managed-array-length managed-array)))
    (declare (type fixnum length))
    (assert-for-development (<f -1 position length))
    (loop for index from (1+f position) below length doing
      (setf (managed-svref managed-array (1-f index)) (managed-svref managed-array index)))
    (adjust-managed-array managed-array (1-f length))))


#+development
(defun test-managed-array-insert-delete (&optional (n 3))
  (loop for position below (+ n 1)
	doing
    (let ((x (allocate-managed-array n)))
      (loop for i below (managed-array-length x)
	    do (setf (managed-svref x i) i))
      (setq x (insert-into-managed-array x position 'new))
      (format t "Inserted at ~d ~s~%" position x)
      (describe-managed-array x)
      (setq x (delete-managed-array-element x position))
      (describe-managed-array x)))
  (values))


;;; The function `print-managed-array' takes a managed array and prints out its
;;; contents.  This is a development only function.

#+development
(defun print-managed-array (managed-array)
  (loop with length = (managed-array-length managed-array)
	with buffer-count =
	(if (<= length maximum-in-place-array-size)
	    0
	    (ceiling length maximum-managed-array-buffer-size))
	for index from 0 below length
	initially
	  (format t "~%~a is ~a elements long, ~a buffers."
		  managed-array length buffer-count)
	do
    (format t "~%~2d : ~s" index (managed-svref managed-array index))))




#+development
(defun careful-managed-array-p (thing)
  (and (simple-vector-p thing)
       (> (length thing) 0)
       (managed-array-p thing)))

;; Managed-array-p assumes length > 0.



#+Development
(def-development-printer managed-array-printer (managed-array stream)
  (when (careful-managed-array-p managed-array)
    (printing-random-object (managed-array stream)
      (format stream "Managed-Array ~d" (managed-array-length managed-array)))
    managed-array))



#+Development
(def-development-describer describe-managed-array (managed-array)
  (when (careful-managed-array-p managed-array)
    (let* ((length (managed-array-length managed-array))
	   (buffer-count
	     (if (<= length maximum-in-place-array-size)
		 0
		 (ceiling length maximum-managed-array-buffer-size))))
      (format t "~s is ~a element~:p long, ~a buffer~:p.~%" managed-array length buffer-count)
      (when (< length 30)
	(loop for i from 0 below length doing
	  (format t "~&[~d] ~s~%" i (managed-svref managed-array i))))
      managed-array)))






;;;; Byte Vector Pool




;;; The following facility defines a pool for allocating and reclaiming 8-bit
;;; byte, one dimensional arrays.  It is used by the stack instruction
;;; allocation facilities, but is a generally available tool.  Given a desired
;;; number of elements in the array, this facility will round the length up to
;;; the nearest size of array that it manages and then return a Lisp vector of
;;; that length with element-type (unsigned-byte 8).

;;; This facility also provides an accessor macro for these vectors which
;;; contains the correct type declarations to optimize it as much as possible.
;;; It also contains a length macro, correctly type-declared for best
;;; performance.

(def-concept byte-vector)




;;; The parameter `maximum-byte-vector-length' contains the maximum size of a
;;; byte vector.

(defparameter maximum-byte-vector-length 131072)




;;; The parameter `byte-vector-allocation-schemes' contains an allocation scheme
;;; alist for use in determining appropriate rounding for byte vector sizes.
;;; See the documentation around managed-array-allocation-schemes for a further
;;; description of allocation schemes.  Note that this allocation scheme always
;;; rounds up by multiples of four, since four bytes fit into a word.

;;; This allocation scheme is tuned for Lucid.  Lucid will only allocate
;;; different sized vectors on 8 byte boundaries, starting at 4, then 12, etc.
;;; byte lengths (i.e.  odd multiples of 4).  Our allocation scheme will mirror
;;; this.  Like the allocation scheme for managed arrays, this scheme obtains
;;; either a 75% utilitization of memory or at most 4 words of waste.  -jra
;;; 10/30/90

(def-memory-allocation-schemes byte-vector-allocation-schemes
    (128 16 11))




;;; The cons pool `byte-vector-conses' is used to allocate conses for stringing
;;; together reclaimed byte vectors.

(defconser byte-vector utilities0)




;;; The system variable `byte-vector-pools' contains a simple vector holding
;;; lists of reclaimed byte vectors.  The system-variable `allocated-byte-
;;; vectors' contains a count of the number of byte vectors that have ever been
;;; created.  The function `outstanding-byte-vectors' returns the number of byte
;;; vectors which have been allocated but not yet reclaimed.  The function
;;; `byte-vector-memory-usage' returns the number of bytes of memory used by all
;;; allocated byte vectors.

(defun make-byte-vector-pools (initial-elt)
  (with-permanent-array-creation
    (make-array
      (+f (partial-buffer-pool-index-given-length
	    maximum-byte-vector-length
	    byte-vector-allocation-schemes)
	  1)
      :initial-element initial-elt)))

(declare-special-global byte-vector-pools
			byte-vector-pool-counts
			allocated-byte-vectors
			bytes-in-allocated-byte-vectors)

(def-system-variable byte-vector-pools utilities0
  (:funcall make-byte-vector-pools nil)
  nil t)

(def-system-variable byte-vector-pool-counts utilities0
  (:funcall make-byte-vector-pools 0)
  nil t)

(def-system-variable allocated-byte-vectors utilities0 0 nil t)

(defun outstanding-byte-vectors ()
  (loop with outstanding fixnum = allocated-byte-vectors
	for pool-index from 0 below (length byte-vector-pools)
	do
    (decff outstanding (length (svref byte-vector-pools pool-index)))
	finally
	  (return outstanding)))

(def-system-variable bytes-in-allocated-byte-vectors utilities0 0 nil t)

(defun byte-vector-memory-usage ()
  bytes-in-allocated-byte-vectors)

 


;;; The system object pool `byte-vector-pool' represents the memory usage of
;;; byte vectors.

(def-system-object-pool byte-vector-pool
  (vector (unsigned-byte 8))
  allocated-byte-vectors
  nil
  outstanding-byte-vectors
  byte-vector-memory-usage)




;;; The macro `bytes-needed-for-byte-vector' returns the number of bytes needed
;;; to allocate a byte vector, given its length.  This will vary from platform
;;; to platform.

(defmacro bytes-needed-for-byte-vector (vector-length)
  `(bytes-per-unsigned-byte-8-simple-array ,vector-length))




;;; The substitution-macro `allocate-byte-vector-internal' has been broken out
;;; to allow the allocation of one large byte vector for images.

(def-substitution-macro allocate-byte-vector-internal (length pool-index?)
  (atomic-incff allocated-byte-vectors)
  (atomic-incff bytes-in-allocated-byte-vectors
	 (bytes-needed-for-byte-vector length))
  (when pool-index?
    (atomic-incff (svref byte-vector-pool-counts pool-index?)))
  (with-permanent-array-creation
    (make-array length :element-type '(unsigned-byte 8))))



;;; The function `allocate-byte-vector' takes a desired array size and returns
;;; an 8-bit byte per element array which is at least as long as is requested.

;;; Implementation Note: All of our implementations implement an immediate array
;;; element-type of (UNSIGNED-BYTE 8).  

(defun allocate-byte-vector (required-size)
;  (declare (eliminate-for-gsi))
  (when (>f required-size maximum-byte-vector-length)
    (error "Attempted to make a byte vector ~a elements long.  Maximum is ~a."
	   required-size maximum-byte-vector-length))
  (multiple-value-bind (rounded-up-length pool-index)
      (buffer-size-and-pool-for-partial-buffer
	required-size
	byte-vector-allocation-schemes)
    (declare (type fixnum rounded-up-length))
    (let ((pool-list (svref byte-vector-pools pool-index)))
      (if pool-list
	  (let ((vector (car pool-list)))
	    (setf (svref byte-vector-pools pool-index) (cdr pool-list))
	    (reclaim-byte-vector-cons-macro pool-list)
	    vector)
	  (allocate-byte-vector-internal rounded-up-length pool-index)))))




;;; The macro `byte-vector-length' takes a vector allocated by the byte-vector
;;; facility and returns the byte length of that vector.  Note that this is not
;;; necessarily the same as the Lisp vector length, since we have to store more
;;; than one byte per element in some Lisp implementations.

(defmacro byte-vector-length (vector)
  `(length (the (simple-array (unsigned-byte 8) (*)) ,vector)))


#+development
(defun development-byte-vector-p (thing)
  (typep thing '(vector (unsigned-byte 8))))




;;; The function `reclaim-byte-vector' takes byte vector which was allocated by
;;; allocate-byte-vector, and reclaims it into the pool for its length.

(defun reclaim-byte-vector (byte-vector)
;  (declare (eliminate-for-gsi))
  #+development
  (unless (development-byte-vector-p byte-vector)
    (cerror "Skip it" "Attempt to reclaim ~s, which is not a byte-vector."
	    byte-vector)
    (return-from reclaim-byte-vector nil))
  (let* ((array-length (byte-vector-length byte-vector))
	 (pool-index
	   (partial-buffer-pool-index-given-length
	     array-length
	     byte-vector-allocation-schemes)))
    (declare (type fixnum array-length pool-index))
    (setf (svref byte-vector-pools pool-index)
	  (byte-vector-cons byte-vector
			    (svref byte-vector-pools pool-index)))
    nil))




;;; The macro `byte-vector-aref' is can be used to access elements of byte
;;; vectors, and can be used with setf to mutate values in the vector.  This
;;; macro includes all declarations to optimize access as much as possible, and
;;; declares the result of this operation to be a fixnum.

(defmacro byte-vector-aref (byte-vector index)
  `(the (unsigned-byte 8)
	(aref (the (simple-array (unsigned-byte 8) (*)) ,byte-vector)
	      (the fixnum ,index))))

(defmacro byte-vector-aset (byte-vector index byte)
  `(setf (the (unsigned-byte 8)
	      (aref (the (simple-array (unsigned-byte 8) (*)) ,byte-vector)
		    (the fixnum ,index)))
	 ,byte))

(defsetf byte-vector-aref byte-vector-aset)




;;; The function `copy-byte-vector-portion' copies bytes from one byte vector to
;;; another.  The function takes the source vector, source index, target vector,
;;; target index, and the number of bytes to copy.  Note that no error checking
;;; is done in this function to guarantee that copying does not proceed past the
;;; end of either byte-vector.  This function always returns NIL.

(defun copy-byte-vector-portion (source-byte-vector source-index
				 target-byte-vector target-index byte-count)
  (declare (eliminate-for-gsi))
  (if (=f source-index target-index)
      (loop for copy-index from source-index below (+f source-index byte-count)
	    do
	(setf (byte-vector-aref target-byte-vector copy-index)
	      (byte-vector-aref source-byte-vector copy-index)))
      (loop for copy-source-index from source-index
				  below (+f source-index byte-count)
	    for copy-target-index from target-index
	    do
	(setf (byte-vector-aref target-byte-vector copy-target-index)
	      (byte-vector-aref source-byte-vector copy-source-index))))
  nil)






;;;; Unsigned Byte 16 Vectors




;;; The following facility defines a pool for allocating and reclaiming 16-bit
;;; byte, one dimensional arrays.  It is used as the implementation type for
;;; wide-strings.  Given a desired number of elements in the array, this
;;; facility will round the length up to the nearest size of array that it
;;; manages and return a (simple-array (unsigned-byte 16)) Lisp vector of that
;;; length.

(def-concept byte-vector-16)

(def-concept unsigned-byte-16-vector)




;;; The parameter `maximum-byte-vector-16-length' contains the maximum size this
;;; tool will allocate and manage.
;;;
;;; Note that it is currently at the point where text strings of length
;;; 1,000,000 can be created.  Users of G2 are limited to creating strings no
;;; longer than 65536 (**), but Gensym system internal software is at present
;;; required to create strings at least 1 million (16-bit) characters long,
;;; since that was allowed in previous versions of G2 at least through version
;;; 4.1.  The current setting meets and exceeds that requirement.
;;;
;;; ** We are changing this limit so that user-strings can be as long as 1MB,
;;; but this is for testing purposes at this point.  We may revert back to
;;; 64K.  - jv, 9/24/99
;;;
;;; ** SoftServe. We are changing this limit so that user-strings can be 
;;; as long as 100MB 10/17/08

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter maximum-byte-vector-16-length
  ; modified by SoftServe 10/17/08;
  #.(expt 2 28))			; = 268,435,456
  ; end of SoftServe changes
)  





;;; The parameter `maximum-wide-string-length' contains the maximum number of
;;; characters available in a wide string.  This is tied to the maximum size of
;;; a byte-vector-16 array, taking into account the bytes used to store the
;;; wide-string fill pointer.  It is a little less than 2MB.  However, note that
;;; the for most purposes you should use the constant
;;; maximum-length-for-user-gensym-strings, q.v., below.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter maximum-wide-string-length
  (-f maximum-byte-vector-16-length extra-wide-string-bv16-elements))
)




;; See maximum-length-for-user-gensym-strings.

;; make sure the user limit is at most 1/2 the hard limit:
#+development
(test-assertion
  (<= (* maximum-length-for-user-text-strings 2) maximum-wide-string-length))






;;; The parameter `byte-vector-16-allocation-schemes' contains an allocation
;;; scheme alist for selecting sizes of byte-vector-16 arrays.  See
;;; managed-array-allocation-schemes for details of what an allocation scheme
;;; is.  The scheme used obtains at least 75% utilization of the allocated space
;;; or at most 4 words of waste.

(def-memory-allocation-schemes byte-vector-16-allocation-schemes
    ; modified by SoftServe
    (64 8 23))  ;23 = 1 + (log2(2**28) - log2(64)) ;See Note (SoftServe 10/17/08)
    ; end of SoftServe changes
        
;; Note: SoftServe 10/17/08
;; Before: 16 = 1 + (log2(2**21) - log2(64))   ; See Note (MHD 3/22/00)
;;
;; Note: Lisp version of above expression:
;;
;;   (+ 1 (- (log (expt 2 21) 2) (log 64 2)))
;;
;; We now use 15 instead of 16 above, since the spec is now based on a 2MB limit
;; whereas previously it was based on a 1MB limit.  The old comment was: 15 = 1
;; + (log2(2**20) - log2(64))   (MHD 3/22/00)




;;; The system variable `byte-vector-16-pools' contains a simple vector holding
;;; lists of reclaimed byte vectors.  The system variable
;;; `allocated-byte-vector-16-vectors' contains a count of the number of
;;; byte-vector-16 vectors ever created.  The function
;;; `outstanding-byte-vector-16-vectors' returns the number of byte-vector-16
;;; vectors which have been allocated but not yet reclaimed.  The function
;;; `byte-vector-16-memory-usage' returns the number of bytes of memory used by
;;; all created byte-vector-16 vectors.

(defun make-byte-vector-16-pools (initial-elt)
  (with-permanent-array-creation
    (make-array
      (+f (partial-buffer-pool-index-given-length
	    maximum-byte-vector-16-length
	    byte-vector-16-allocation-schemes)
	  1)
      :initial-element initial-elt)))

(def-system-variable byte-vector-16-pools utilities0
  (:funcall make-byte-vector-16-pools nil)
  nil t)

(def-system-variable byte-vector-16-pool-counts utilities0
  (:funcall make-byte-vector-16-pools 0)
  nil t)

(def-system-variable allocated-byte-vector-16-vectors utilities0 0 nil t)

(defun outstanding-byte-vector-16-vectors ()
  (loop with outstanding fixnum = allocated-byte-vector-16-vectors
	for pool-index from 0 below (length byte-vector-16-pools)
	do
    (decff outstanding (length (svref byte-vector-16-pools pool-index)))
	finally (return outstanding)))

(def-system-variable bytes-in-allocated-byte-vector-16-vectors
    utilities0 0 nil t)

(defun byte-vector-16-memory-usage ()
  bytes-in-allocated-byte-vector-16-vectors)




;;; The system object pool `byte-vector-16-pool' represents the memory usage of
;;; byte-vector-16 vectors.

(def-system-object-pool byte-vector-16-pool (vector (unsigned-byte 16))
  allocated-byte-vector-16-vectors
  nil
  outstanding-byte-vector-16-vectors
  byte-vector-16-memory-usage)




;;; The macro `allocate-byte-vector-16-internal' creates a
;;; permanent unsigned-byte 16 array, incrementing the variables that keep track
;;; of total allocated memory and total allocated counts.

(defvar free-malloced-arrays t)

(defvar largest-non-malloced-byte-vector-16-pool-index -1)

;;; The variable `byte-vector-16-pool-number-to-malloc' determines which byte-vector-16s
;;; are heap allocated and which ones are malloced. Byte-vectors
;;; in this pool and larger ones are malloced. Set value to -1 to cause
;;; all byte-vector-16's to be heap allocated (current setting)
;;; Currently set not to malloc anything. To malloc strings of length
;;; greater than (for example) 100, change this to
;;; (defvar byte-vector-16-pool-number-to-malloc
;;;    (partial-buffer-pool-index-given-length
;;;       100 byte-vector-16-allocation-schemes))
;;; Note that this length will be rounded up to the next pool boundary.

(defvar byte-vector-16-pool-number-to-malloc -1)

;;; Once a byte-vector-16 of a given length has been allocated, it's too late to
;;; switch whether vectors of that length are malloced, since we have no way
;;; to distinguish a malloc'ed one from an unmalloced one. So this
;;; Returns nil if it's too late to change the allocation as requested, and the minimum length
;;; of string that will now be malloc'ed if it succeeds.
;;; All strings of length greater than the specified length, rounded up to
;;; a pool boundary, will be subsequently malloced.
;;; As a special case, a length argument of -1 will turn off all
;;; malloc'ing of byte-vector-16's..
(defun set-malloced-byte-vector-16-threshhold (length)
  (if (=f length -1)
      (setf byte-vector-16-pool-number-to-malloc -1)
      (multiple-value-bind (rounded-up-length pool-index)
	  (buffer-size-and-pool-for-partial-buffer
	    length
	    byte-vector-16-allocation-schemes)
	(when (>f pool-index largest-non-malloced-byte-vector-16-pool-index)
	  (setq byte-vector-16-pool-number-to-malloc pool-index))
	rounded-up-length)))

#+translator
(defun free-malloced-byte-vector-16s ()
  (when (>=f byte-vector-16-pool-number-to-malloc 0)
    (loop for pool-index from byte-vector-16-pool-number-to-malloc below (length byte-vector-16-pools)
	  do
      (let ((array-list (svref byte-vector-16-pools pool-index)))
	(loop for array in array-list do
	  (free-malloced-byte-vector-16 array))
	(reclaim-byte-vector-list array-list))
      (setf (svref byte-vector-16-pools pool-index) nil))))

(defmacro allocate-byte-vector-16-internal (length pool-index)
  `(let ((length ,length)
	 (pool-index ,pool-index))
     (atomic-incff allocated-byte-vector-16-vectors)
     (incff (svref byte-vector-16-pool-counts pool-index))
     (atomic-incff bytes-in-allocated-byte-vector-16-vectors
	    (bytes-per-unsigned-byte-16-simple-array length))
     ,(feature-case
	(translator
	  `(if (or
		 (=f byte-vector-16-pool-number-to-malloc -1)
		 (<f pool-index byte-vector-16-pool-number-to-malloc))
	       (with-permanent-array-creation
		 (make-array length :element-type '(unsigned-byte 16)))
	       (make-malloced-array length)))
	(t
	  `(with-permanent-array-creation
	    ;; SBCL will fill an array with `0' by default, which make Chestnut outputs constant C codes.
	    ;; here we enable this feature on other lisp platforms. -- jingtao 2013.11.20
	    (make-array length :initial-element 0 :element-type '(unsigned-byte 16)))))))

;;; The function `allocate-byte-vector-16' takes a desired array length and
;;; returns a (simple-array (unsigned-byte 16)) containing at least that many
;;; elements.

(defun-simple allocate-byte-vector-16 (required-size)
  #+development
  (when (>f required-size maximum-byte-vector-16-length)
    (error "Attempted to make byte-vector-16 ~a elements long.  Maximum is ~a."
	   required-size maximum-byte-vector-16-length))
  (multiple-value-bind (rounded-up-length pool-index)
      (buffer-size-and-pool-for-partial-buffer
	required-size
	byte-vector-16-allocation-schemes)
    (declare (type fixnum rounded-up-length pool-index))
    (when (or (=f byte-vector-16-pool-number-to-malloc -1)
	      (<f pool-index byte-vector-16-pool-number-to-malloc))
      (setf largest-non-malloced-byte-vector-16-pool-index
	    (maxf largest-non-malloced-byte-vector-16-pool-index pool-index)))
    (let* ((pool-list (svref byte-vector-16-pools pool-index))
	   (bv16 (if pool-list
		     (let ((vector (car-of-cons pool-list)))
		       (setf (svref byte-vector-16-pools pool-index)
			     (cdr-of-cons pool-list))
		       (reclaim-byte-vector-cons-macro pool-list)
		       vector)
		     (allocate-byte-vector-16-internal rounded-up-length pool-index))))
      (note-allocate-cons bv16 nil)
      bv16)))

;;; The macro `byte-vector-16-length' takes a vector allocated by the
;;; byte-vector facility and returns its length.  Note that this version is
;;; properly type declared to get the best speed possible.  The macro
;;; `byte-vector-16-p' takes a thing and checks its type in the most efficient
;;; way available.

(defmacro byte-vector-16-length (byte-vector-16)
  `(the fixnum (length (the (simple-array (unsigned-byte 16) (*))
			    ,byte-vector-16))))

(defmacro byte-vector-16-p (thing)
  `(unsigned-byte-16-vector-p ,thing))

;;; The macro `reclaim-byte-vector-16' takes and reclaims a byte-vector-16.

;;; I want to make this a substitution macro, but it gives me incomprehensible
;;; error messages when I do.
(defun return-byte-vector-16-to-pool (byte-vector-16)
  (let ((pool-index (partial-buffer-pool-index-given-length
		      (byte-vector-16-length byte-vector-16)
		      byte-vector-16-allocation-schemes)))
    (declare (type fixnum pool-index))
    (setf (svref byte-vector-16-pools pool-index)
	  (byte-vector-cons byte-vector-16
			    (svref byte-vector-16-pools pool-index)))
    nil))

(defun-simple reclaim-byte-vector-16 (byte-vector-16)
  #+development
  (unless (byte-vector-16-p byte-vector-16)
    (cerror "Skip reclaiming it." "Can't reclaim ~A, its not a byte-vector-16."
	    byte-vector-16)
    (return-from reclaim-byte-vector-16 nil))
  (note-reclaim-cons byte-vector-16 nil)
  #+translator
  (if free-malloced-arrays
      (free-malloced-byte-vector-16 byte-vector-16)
      (return-byte-vector-16-to-pool byte-vector-16))
  #-translator
  (return-byte-vector-16-to-pool byte-vector-16))

#+translator
(defun free-malloced-byte-vector-16 (byte-vector-16)
  ;; No need to call `buffer-size-and-pool-for-partial-buffer' if
  ;; byte-vector-16-pool-number-to-mallo is -1
  (when (=f byte-vector-16-pool-number-to-malloc -1)
    (return-from  free-malloced-byte-vector-16
      (return-byte-vector-16-to-pool byte-vector-16)))

  (multiple-value-bind (rounded-up-length pool-index)
      (buffer-size-and-pool-for-partial-buffer
	(length byte-vector-16)
	byte-vector-16-allocation-schemes)
    (if (<f pool-index byte-vector-16-pool-number-to-malloc)
	(return-byte-vector-16-to-pool byte-vector-16)
	(progn
	  (atomic-decff (svref byte-vector-16-pool-counts pool-index))
	  (atomic-decff allocated-byte-vector-16-vectors)
	  (atomic-decff bytes-in-allocated-byte-vector-16-vectors
		 (bytes-per-unsigned-byte-16-simple-array rounded-up-length))
	  (free-malloced-array-internal byte-vector-16)))
    t))

;;; The macro `byte-vector-16-aref' is can be used to access elements of 16-bit
;;; byte vectors, and can be used with setf to mutate values in the vector.
;;; This macro includes all declarations to optimize access as much as possible,
;;; and declares the result of this operation to be a fixnum.

(defmacro byte-vector-16-aref (byte-vector index)
  `(the (unsigned-byte 16)
	(aref (the (simple-array (unsigned-byte 16) (*))
		   ,byte-vector)
	      (the fixnum ,index))))

(defmacro byte-vector-16-aset (byte-vector index byte)
  `(setf (the (unsigned-byte 16)
	      (aref (the (simple-array (unsigned-byte 16) (*)) ,byte-vector)
		    (the fixnum ,index)))
	 ,byte))

(defsetf byte-vector-16-aref byte-vector-16-aset)




;;; The macro `copy-byte-vector-16-portion' takes two byte-vector-16 vectors,
;;; two start indices, and a number of 16-bit elements to copy from the source
;;; to the target.  The function returns NIL.  Note that if the copy regions
;;; overlap, then this could produce bad values in the target location.

;; The intent is to optimize this into a memcpy.  -jra 5/24/96

(defmacro copy-byte-vector-16-portion
    (source-vector-16 source-elt-index target-vector-16 target-elt-index
		      element-count)
  (let ((source-vector (gensym))
	(source-index (gensym))
	(target-vector (gensym))
	(target-index (gensym))
	(count (gensym)))
    `(let ((,source-vector ,source-vector-16)
	   (,source-index ,source-elt-index)
	   (,target-vector ,target-vector-16)
	   (,target-index ,target-elt-index)
	   (,count ,element-count))
       (declare (type (simple-array (unsigned-byte 16))
		      ,source-vector ,target-vector)
		(fixnum ,source-index ,target-index ,count))
       ,(if (eval-feature :translator)
	    `(inline-copy-byte-vector-16-portion
	       ,source-vector ,source-index ,target-vector ,target-index ,count)
	    `(loop for copy-index fixnum from ,source-index
				  below (+f ,source-index ,count)
		   for modify-index fixnum from ,target-index
		   do
	       (setf (byte-vector-16-aref ,target-vector modify-index)
		     (byte-vector-16-aref ,source-vector copy-index))))
       nil)))

(declare-side-effect-free-function inline-unsigned-byte-16-vector-p)

#+translator
(tx::def-foreign-function
    (inline-copy-byte-vector-16-portion
      (:name "INLINE_COPY_BYTE_VECTOR_16_PORTION")
      (:return-type :void))
    (source :16-bit-unsigned-array)
  (source-index :fixnum-long)
  (target :16-bit-unsigned-array)
  (target-index :fixnum-long)
  (count :fixnum-long))

#-translator
(defun inline-copy-byte-vector-16-portion
    (source source-index target target-index count)
  (loop for copy-index fixnum from source-index
		       below (+f source-index count)
	for modify-index fixnum from target-index
	do
    (setf (byte-vector-16-aref target modify-index)
	  (byte-vector-16-aref source copy-index)))
  nil)




;;; The void function `copy-byte-vector-16-portion-carefully' will copy contents
;;; of a byte-vector-16 when they might contain overlaps.

;; Eventually change this to an inlined call to memmove.  -jra 6/12/96

(defun-void copy-byte-vector-16-portion-carefully
    (source-vector-16 source-elt-index target-vector-16 target-elt-index
		      element-count)
  (declare (type fixnum source-elt-index target-elt-index element-count))
  (if (and (eq source-vector-16 target-vector-16)
	   (<f source-elt-index target-elt-index))
      ;; In this overlap, copy in the appropriate order
      (loop for source-index downfrom (-f (+f source-elt-index element-count) 1)
			     to source-elt-index
	    for target-index downfrom (-f (+f target-elt-index element-count) 1)
	    do
	(setf (byte-vector-16-aref target-vector-16 target-index)
	      (byte-vector-16-aref source-vector-16 source-index)))
      (loop for source-index from source-elt-index
			     below (+f source-elt-index element-count)
	    for target-index from target-elt-index
	    do
	(setf (byte-vector-16-aref target-vector-16 target-index)
	      (byte-vector-16-aref source-vector-16 source-index)))))

;;; The macro `compare-byte-vector-16-portion' takes two byte-vector-16 vectors,
;;; two start indices, and a number of 16-bit elements to compare from the
;;; source to the target.  The function returns an integer less than, equal to,
;;; or greater than 0, according as the first arg is lexicographically less
;;; than, equal to, or greater than s2.

(defmacro compare-byte-vector-16-portion
    (source-vector-16 source-elt-index target-vector-16 target-elt-index element-count
		      &optional only-zero-or-non-zero-result-matters-p)
  (let ((source-vector (gensym))
	(source-index (gensym))
	(target-vector (gensym))
	(target-index (gensym))
	(count (gensym)))
    `(let ((,source-vector ,source-vector-16)
	   (,source-index ,source-elt-index)
	   (,target-vector ,target-vector-16)
	   (,target-index ,target-elt-index)
	   (,count ,element-count))
       (declare (type (simple-array (unsigned-byte 16))
		      ,source-vector ,target-vector)
		(fixnum ,source-index ,target-index ,count)
                (ignorable ,source-index ,target-index))
       ,(cond
	  ((and (eval-feature :translator)
                (eql source-elt-index 0) (eql target-elt-index 0)
		only-zero-or-non-zero-result-matters-p)
	   ;; byte ordering issues can cause it to get the sign of the result wrong
	   `(c-memcmp ,source-vector ,target-vector (left-shiftf ,count 1)))
	  ((and (eval-feature :translator)
		only-zero-or-non-zero-result-matters-p)
	   ;; byte ordering issues can cause it to get the sign of the result wrong
	   `(inline-compare-byte-vector-16-portion
	     ,source-vector ,source-index ,target-vector ,target-index ,count))
	  (t
	   `(loop for compare-index fixnum from ,source-index
				    below (+f ,source-index ,count)
		  for target-index fixnum from ,target-index
		  as source-byte = (byte-vector-16-aref ,source-vector compare-index)
		  as target-byte = (byte-vector-16-aref ,target-vector target-index)
		  unless (=f source-byte target-byte)
		    return (if (<f source-byte target-byte) -1 1)
		  finally
		    (return 0)))))))

#+translator
(tx::def-foreign-function
    (inline-compare-byte-vector-16-portion
     (:name "INLINE_COMPARE_BYTE_VECTOR_16_PORTION")
     (:return-type :fixnum-long))
  (source :16-bit-unsigned-array)
  (source-index :fixnum-long)
  (target :16-bit-unsigned-array)
  (target-index :fixnum-long)
  (count :fixnum-long))

#+translator
(tx::def-foreign-function (c-memcmp (:name "memcmp")
                                    (:return-type :fixnum-long))
  (source :16-bit-unsigned-array)
  (target :16-bit-unsigned-array)
  (count :fixnum-long))





;;;; Character Byte-Vectors





;;; A `character byte-vector' is a simple (unsigned-byte 8) integer vector used
;;; within some of the font utilities.  These are allocated only at startup and
;;; never reclaimed.  There are functions for allocating new ones, and
;;; efficiently accessing the length and elements.  The element accessor is
;;; setfable.

(defun allocate-character-byte-vector (length)
  (declare (eliminate-for-gsi))
  (with-permanent-array-creation
    (make-array length :initial-element 0 :element-type '(unsigned-byte 8))))

(defmacro character-byte-vector-length (character-byte-vector)
  `(length (the (simple-array (unsigned-byte 8) (*)) ,character-byte-vector)))

(defmacro character-byte-vector-ref (character-byte-vector index)
  `(the (unsigned-byte 8)
	(aref (the (simple-array (unsigned-byte 8) (*)) ,character-byte-vector)
	      (the fixnum ,index))))





;;;; Bit Vectors



;; A Quick Bit-vector Facility. (MHD 8/20/96)


;;; A `bit vector' is a data abstraction for an object that sets and stores bits
;;; at a given index.  At present, bit vectors are implemented on top of byte
;;; vectors, but relying on this fact is discouraged, and is not guaranteed to
;;; be "portable".
;;;
;;; `Allocate-bit-vector' creates a new bit vector with at least minimum-length
;;; bits.  `Reclaim-bit-vector' reclaims bit-vector.  `Bit-vector-length'
;;; returns the actual number of bits in bit-vector.  Note that the initial bit
;;; values are undefined.  `Bit-vector-aref' returns the bit in bit-vector at
;;; index.  `Setf bit-vector-aref', the setf method for bit-vector-aref, sets
;;; the bit in bit-vector at index to bit-value, and returns bit-value.

(defmacro allocate-bit-vector (minimum-length)
  `(allocate-byte-vector (ceilingf ,minimum-length 8)))

(defmacro bit-vector-length (bit-vector)
  `(*f (byte-vector-length ,bit-vector) 8))

(defmacro bit-vector-aref (bit-vector index)
  (avoiding-variable-capture (bit-vector index &aux byte-index bit-index)
    `(multiple-value-bind (,byte-index ,bit-index)
	 (floorf ,index 8)
       (if (logbitpf ,bit-index (byte-vector-aref ,bit-vector ,byte-index))
	   1
	   0))))

(defmacro bit-vector-aset (bit-vector index bit-value)
  (avoiding-variable-capture (bit-vector index bit-value &aux byte-index bit-index byte)
    `(multiple-value-bind (,byte-index ,bit-index)
	 (floorf ,index 8)
       (setf (byte-vector-aref ,bit-vector ,byte-index)
	     (let ((,byte (byte-vector-aref ,bit-vector ,byte-index)))
	       (if (=f ,bit-value 1)
		   (logiorf ,byte
			    (svref '#(#b1 #b10 #b100 #b1000
				      #b10000 #b100000 #b1000000 #b10000000)
				   ,bit-index))
		   (logandf ,byte
			    (svref '#(#b11111110 #b11111101 #b11111011 #b11110111
				      #b11101111 #b11011111 #b10111111 #b01111111)
				   ,bit-index)))))
       ,bit-value)))

(defsetf bit-vector-aref bit-vector-aset)

(defmacro reclaim-bit-vector (bit-vector)
  `(reclaim-byte-vector ,bit-vector))





;;;; Augmented Let Forms




;;; The following section contains macros that are used in ways similar to let,
;;; but that provide additional performance or semantics.





;;; The macro `let*-sim' simulates bindings via let, without the unwind protect
;;; cleanups implied by bindings global variables.  This is needed to keep
;;; Chestnut from killing performance.  This macro returns the first value from
;;; the body.  

;;; It assumes that the variables being bound are already bound.  It is not clever enough
;;; to lexically bind things that are not proclaimed special.

;; When Chestnut fixes their global variable binding implementation to not call
;; setjmp, then this macro and calls to it should all be removed.  -jra 6/22/92

(defmacro let*-sim (bindings &body body)
  (loop with let-bindings = nil
	with init-forms = nil
	with clean-up-forms = nil
	with body-value = (gensym)
	for binding in bindings
	for var = (if (consp binding) (car binding) binding)
	for init-form = (if (consp binding) (second binding) nil)
	for clean-up-var = (intern (format nil "OLD-~a" var))
	do
    (push `(,clean-up-var ,var) let-bindings)
    (push `(setq ,var ,init-form) init-forms)
    (push `(setq ,var ,clean-up-var) clean-up-forms)
	finally
	  (return
	    `(let ,(cons body-value (reverse let-bindings))
	       ,@(reverse init-forms)
	       (setq ,body-value (progn ,@body))
	       ,@(reverse clean-up-forms)
	       ,body-value))))





;;;; Protected-let

;; jh, 11/14/90.  Moved to UTILITIES0, 2/11/92.

;;; protected-let <specs> &rest <body>
;;; <specs> are of the form ( var bind-form undo-form )
;;; <body> is an implicit progn

;;; The analogy is to let, in that the specs control variable binding.
;;; Protected-let sets each var to the result of bind-form.  It then executes the
;;; body forms and returns a single value from the last such form.  Finally, each
;;; var which ended up bound to a non-nil form has its corresponding undo-form
;;; executed as part of an unwind-protect context.  Note that this excludes vars
;;; that did not get bound at all because a return or non-local exit happened
;;; before or during their binding.  

;;; An example of using of protected-let is in g2-stream-with-open-stream.

(defun-for-macro expander-for-protected-let 
		 (specs body &optional disallowed-test? disallowed-spec
			(unwind-protect 'unwind-protect))
  `(let ,(loop for (var) in specs
	       collecting `(,var 'unbound-in-protected-let))
     (,unwind-protect
       (progn
	 ,@(loop for (var bind-form) in specs
		 collecting
		   `(setq ,var ,bind-form))
	 ,@body)
       ,@(loop for (var nil undo-form) in (reverse specs)
	       for index from 0
	       with reverse-disallowed-spec
		 = (reverse disallowed-spec)
	       do (when (and disallowed-test?
			     (funcall disallowed-test?
				      undo-form
				      (elt reverse-disallowed-spec index)))
		    (warn "PROTECTED-LET: ~
                           possible ordering problem in undo-form ~a"
			  undo-form))
	       when undo-form
		 collect
		   `(when ,var
		      (unless (eq ,var 'unbound-in-protected-let)
			,undo-form))))))

(defmacro protected-let (specs &body body)
  (let ((protection-needed-p 
	  (loop for (nil nil undo-form) in specs
		thereis undo-form)))
    (cond
      ;; There is more than one spec, so we need to check for ordering
      ;; violations.
      ((and protection-needed-p (cdr specs))
       (let ((disallowed-identifiers-in-undo-form
	       (loop for (var) in (reverse specs)
		     with current-list-of-disallowed-identifiers = nil
		     with accumulator-for-disallowed-identifiers = nil
		     do (push current-list-of-disallowed-identifiers
			      accumulator-for-disallowed-identifiers)
			(push var current-list-of-disallowed-identifiers)
		     finally (return 
			       accumulator-for-disallowed-identifiers))))
	 (labels ((questionable-undo-form-p (undo-form disallowed-identifiers)
		    (cond
		      ((null undo-form) nil)
		      ((and (symbolp undo-form)
			    (memq undo-form disallowed-identifiers))
		       t)
		      ((not (listp undo-form)) nil)
		      (t (loop for subform in (cdr undo-form)
			       thereis (questionable-undo-form-p 
					 subform
					 disallowed-identifiers))))))
	   (expander-for-protected-let 
	     specs 
	     body 
	     #'questionable-undo-form-p 
	     disallowed-identifiers-in-undo-form))))

	;; There is only a single spec, so we don't have to check for ordering
	;; violations.
	(protection-needed-p
	 (expander-for-protected-let specs body))

	;; We don't have to protect anything.
	(t `(let ,specs ,@body)))))


#+development
(defparameter validation-suite-for-protected-let
	      '(((protected-let ((a b (reclaim a c)) 
				 (c d (reclaim c)) 
				 (e f (reclaim e))) 
		   (list a c e))
		 t) ;should generate warning
		((protected-let ((a b (reclaim a)) 
				 (c d (reclaim c)) 
				 (e f (reclaim a e))) 
		   (list a c e))
		 nil) ;should not generate warning
		((protected-let ((a b (reclaim a (process c)))
				 (c d (reclaim c)) 
				 (e f (reclaim e))) 
		   (list a c e))
		 t)
		((protected-let ((a b (reclaim a)) 
				 (c d (reclaim c)) 
				 (e f (reclaim a (process e))))
		   (list a c e))
		 nil)))

#+development
(defun validate-protected-let ()
  (loop for (form produces-warning-p) 
	    in validation-suite-for-protected-let
	do
    (format t "~&A warning should ~:[not ~;~]follow~:*~:[.~;:~]~%"
	    produces-warning-p)
    (macroexpand form)
    (format t "~2%")))


(defmacro protected-let* (specs &body body)
  (let ((protection-needed-p 
	  (loop for (nil nil undo-form) in specs
		thereis undo-form)))
    (if protection-needed-p
	`(protected-let ,specs ,@body)
	`(let* ,specs ,@body))))



;;; `Protected-let*-for-development' is a variant of protected let which
;;; uses unwind-protect-for-development rather than unwind to do the
;;; cleanup.

(defmacro protected-let*-for-development (specs &body body)
  (expander-for-protected-let
    specs body nil nil
    'unwind-protect-for-development-using-most-recent-defun-name))

;; jh, 10/7/91.  Added the tag unbound-in-protected-let to help find problems when
;; a protected-let binding form contains a forward reference.  This previously
;; went undetected because the initial binding was nil, which could work well
;; enough to conceal the problem.
;; ---
;; NOTE: And that meant that your cleanup forms would be called on variables
;; that were never bound to their intended value if you did a return or a
;; non-local exit from within a binding form, e.g.,
;; 
;;    (protected-let ((var (... (return... )) (clean-up... )))
;;      ...)
;;
;; so I changed (when ,var ...) above to
;;
;;    (when (not (eq ,var 'unbound-in-protected-let))
;;       ...)
;;
;; The protected-let in read-kb-or-group-thereof-1 is an example.
;; (MHD 10/10/91)
;; ----------------------
;; Note: I realized I had to change this to checking both for nil and for
;; the preinitial binding, i.e.,
;;
;;     ... (and ,var
;;              (not (eq ,var 'unbound-in-protected-let)))
;;
;; because it's documented not to call the "undo form" on var if it's nil.
;; Also, today I'm thinking I'm not sure that we shouldn't document the
;; new behavior.  (MHD 10/11/91)

;; jh, 12/12/91.  Moved protected-let and protected-let* from PATHNAMES, since it
;; appears they are of more general utility.

;; jh, 4/9/92.  Fixed protected-let* to undo things in reverse order, so that a
;; later spec can make use of the not-yet-undone value of an earlier spec.



;; jh, 5/11/92.  Added with-flattened-protected-let-forms.  This macro collects
;; all the undo-forms for every protected-let and protected-let* form within its
;; lexical scope, and executes them within a single unwind-protect.  We need
;; this macro because there is an inefficiency in Chestnut unwind-protect (it
;; uses C setjmp, which is slow since it has to store all registers).  We don't
;; abstract this macro any further because we hope Chestnut will make
;; unwind-protect more efficient in the future.  Note that this macro does not
;; check for shadowed names, names re-used after an inner protected-let form is
;; exited, or protected-let forms within an outer protected-let spec.

(defmacro with-flattened-protected-let-forms (&body body)
  (let ((all-protected-let-specs? nil))
    (labels ((walk-for-protected-let-specs (form)
	       (cond 
		 ((not (consp form)))
		 ((memq (first form) '(protected-let protected-let*))
		  (setq all-protected-let-specs?
			(append all-protected-let-specs? (second form)))
		  (loop for subform in (cddr form)
			do (walk-for-protected-let-specs subform)))
		 (t (loop for subform in form
			  do (walk-for-protected-let-specs subform))))))
      (walk-for-protected-let-specs body)
      (if all-protected-let-specs?
	  `(macrolet ((protected-let (specs &body body)
			`(progn ,@(loop for (var initform) in specs
					collect `(setq ,var ,initform))
				,@body))
		      (protected-let* (specs &body body)
			`(progn ,@(loop for (var initform) in specs
					collect `(setq ,var ,initform))
				,@body)))
	       (let ,(loop for (var) in all-protected-let-specs?
			   collect `(,var 'unbound-in-protected-let))
		 (unwind-protect 
		   (progn ,@body)
		   (progn 
		     ,@(loop for (var nil undo-form?) 
				 in (reverse all-protected-let-specs?)
			     when undo-form?
			       collect
				 `(when ,var
				    (unless (eq ,var 'unbound-in-protected-let)
				      ,undo-form?)))))))
	  `(progn ,@body)))))




(defmacro funcall-simple-case (function nargs args &rest arg-accessors)
  `(fixnum-case ,nargs
     ,@(reverse
	 (loop for accessors-reverse on (reverse (cons nil arg-accessors))
	       for accessors = (cdr (reverse accessors-reverse))
	       collect `(,(length accessors)
			 (funcall-simple-compiled-function
			   ,function
			   ,@(loop for accessor in accessors
				   collect `(,accessor ,args))))))
     #+development
     (t
       (error "More than ~D arguments were supplied"
	      ,(length arg-accessors)))))

(defmacro funcall-simple-case-list (function argument-list)
  `(funcall-simple-case
     ,function (length ,argument-list) ,argument-list
     first second third fourth fifth sixth seventh eighth ninth tenth))




;;;; Activity Lists


;;; An `activity' is a list of gensym conses, who's first element is a
;;; simple compiled function, and who's remainder is a set of arguments
;;; for that function.  

;;; An `activity list' is a list of activities, constructed from gensym
;;; conses.

;;; These provide a useful, and very light wieght, abstraction for enqueing
;;; activities.  The  patterns of use vary, but one tool is provided for
;;; adding an activity to an activity list.



;;; `Do-activity' takes an activity and invokes the value, if any of the
;;; activity is returned.

(defun do-activity (activity)
  (declare (eliminate-for-gsi))
  (let ((simple-compiled-function (car activity)))
    (funcall-simple-case
      simple-compiled-function (1-f (length activity)) activity
      second third fourth)))



;;; `Do-activities' takes a list of activities and invokes them all.

(defun do-activities (activity-list)
  (declare (eliminate-for-gsi))
  (loop for activity in activity-list do (do-activity activity)))



;;; `Reclaim-activitis' takes a list of activities and reclaims them
;;; and the list.  It returns NIL, a good thing to store back into
;;; the place from whence the list came.

(defun reclaim-activities (activity-list)
  (declare (eliminate-for-gsi))
  (loop for activity in activity-list
	do (reclaim-gensym-list activity)
	finally (reclaim-gensym-list activity-list)))

;;; `with-activity-enqueing' ... the queue must be a place form
;;; that maybe evaluated N times.

(defmacro with-activity-enqueing ((queue) (function &rest args))
  (assert (< (length args) 3))
  `(let ((listed-activity
	   (gensym-list
	     (gensym-list (symbol-function ',function) ,@args))))
     (setf ,queue
	   (if ,queue
	       (nconc ,queue listed-activity)
	       listed-activity))))





;;;; Random useful functions



(defun-substitution-macro singleton? (list)
  (and (consp list) (null (cdr list))))


(defun plistp (thing)
  (and (listp thing)
       (null (cdr (last thing)))
       ;; Workaround for HQ-4977216, "chestnut macros should 'return' simple
       ;;                             types, not Objects"; -jv, 3/10/05
       (neq nil (evenp (length thing)))
       (loop for (p) on thing by #'cddr
 	     always (and p (symbolp p)))))


;;; The function `order-in-front' moves element-1 in the list to ensure that it
;;; precedes element-2. If this is not already true, then element-1 is dragged
;;; back (destructively) until it is just in front of the element-2.  We return
;;; two values: the new list and the changed-something? flag.

(defun order-in-front (element-1 element-2 list)
  (declare (eliminate-for-gsi))
  (let ((cons-before-1 nil)
	(cons-before-2 nil)
	(changed-something? nil))

    (when (loop for sublist on list
		as element = (first sublist)
		doing
	    (cond ((eq element element-1)
		   (return nil))
		  ((eq element element-2)
		   (return t)))
	    (setq cons-before-2 sublist))

      (loop for sublist on (if cons-before-2 (cdr cons-before-2) list)
	    as element = (first sublist)
	    doing
	(when (eq element element-1)
	  (loop-finish))
	(setq cons-before-1 sublist))

      ;; Pull element-1 to just in front of element-2.
      (cond ((and cons-before-2 (cdr cons-before-1))
	     ;; (rotatef (cdr cons-before-2) (cdr cons-before-1) (cdr (cdr cons-before-1)))
	     (let ((temp-a (cdr cons-before-2))
		   (temp-b (cdr cons-before-1))
		   (temp-c (cdr (cdr cons-before-1))))
	       (setf (cdr cons-before-2) temp-b
		     (cdr cons-before-1) temp-c
		     (cdr temp-b) temp-a))
	     (setq changed-something? t))
	    ((cdr cons-before-1)
	     ;; (rotatef list (cdr cons-before-1) (cdr (cdr cons-before-1)))
	     (let ((temp-a list)
		   (temp-b (cdr cons-before-1))
		   (temp-c (cdr (cdr cons-before-1))))
	       (setf list temp-b
		     (cdr cons-before-1) temp-c
		     (cdr temp-b) temp-a))
	     (setq changed-something? t))))

    (values list changed-something?)))

;;; The function `order-in-back' is equivalent to order-in-front on the
;;; reversed list.

(defun order-in-back (element-1 element-2 list)
  (declare (eliminate-for-gsi))
  (multiple-value-bind (new-list changed?)
      (order-in-front element-1 element-2 (nreverse list))
    (values (nreverse new-list) changed?)))
  
#+development
(defun test-orderings ()
  (loop with input = '(A B C D E)
	with bugs = 0
	for (element-1 element-2 answer back-p) in
	'((a b (A B C D E))
	  (b a (B A C D E))
	  (d e (A B C D E))
	  (e d (A B C E D))
	  (b e (A B C D E))
	  (e b (A E B C D))
	  (d b (A D B C E))
	  (c b (A C B D E))
	  (a b (A B C D E))
	  (e a (E A B C D))
	  (e b (A E B C D))
	  (e c (A B E C D))
	  (e d (A B C E D))
	  (e e (A B C D E))
	  (a f (A B C D E))
	  (f a (A B C D E))

	  (a b (B A C D E) t)
	  (b a (A B C D E) t)
	  (d e (A B C E D) t)
	  (e d (A B C D E) t)
	  (b e (A C D E B) t)
	  (e b (A B C D E) t)
	  (d b (A B C D E) t)
	  (c b (A B C D E) t)
	  (b c (A C B D E) t)
	  (a b (B A C D E) t)
	  (e a (A B C D E) t)
	  (a e (B C D E A) t)
	  (b e (A C D E B) t)
	  (c e (A B D E C) t)
	  (d e (A B C E D) t)
	  (e e (A B C D E) t)
	  (a f (A B C D E) t)
	  (f a (A B C D E) t))
	  
	as list = (copy-list input)
	as should-change = (not (equal list answer))
	as fun = (if back-p 'order-in-back 'order-in-front)
	doing
    (multiple-value-bind (new-list changed)
	(funcall fun element-1 element-2 list)
      (unless (and (equal new-list answer)
		   (equal should-change changed))
	(incf bugs)
	(format t "Bug: (~a '~s '~s '~s) /= ~s~%"
		fun element-1 element-2 input answer)))
	finally
	  (return (if (zerop bugs) "Passed" "Failed"))))




;;; The function `parse-body-declarations' returns the declarations,
;;; body, and doc string for the given function body, as three values.
;; cf: split-declarations-and-documentation-from-statements

(defun-for-macro parse-body-declarations (body)
  (let* ((declarations (loop while (or (and (consp (car body))
					    (eq (caar body) 'declare))
				       (and (stringp (car body))
					    (cdr body)))
			     collect (pop body)))
	 (documentation (if (stringp (car declarations)) (pop declarations))))
    (values declarations body documentation)))




;;; The macro `do-until-time-interval-expires' executes the body repeatedly,
;;; without any sleeping, until the given time interval has elapsed.  The
;;; interval is in milliseconds.

(defmacro do-until-time-interval-expires ((time-interval) &body body)
  (avoiding-variable-capture (time-interval &aux initial-fixnum-time fixnum-time-interval)
    `(loop with ,initial-fixnum-time = (get-fixnum-time)
	   with ,fixnum-time-interval = (fixnum-time-interval ,time-interval)
	   do (progn ,@body)
	   until (>f (fixnum-time-difference
		       (get-fixnum-time) ,initial-fixnum-time)
		     ,fixnum-time-interval))))


(def-substitution-macro squaref (n)
  (*f n n))


;;; The macro `nconc-macro' inlines tests for NIL on either arg.

(defmacro nconc-macro (list-1 list-2)
  (avoiding-variable-capture (list-1 list-2)
    `(cond ((null ,list-1) ,list-2)
	   ((null ,list-2) ,list-1)
	   (t (nconc ,list-1 ,list-2)))))


(defun circular-list-p (list)
  (declare (eliminate-for-gsi))
  (null (list-length list)))


(defmacro identity-macro (thing)
  `,thing)


;;; The macro `delete-macro' deletes every element of the list which satifies
;;; (test element (key list-element)), and returns the new list.  Deleted cons
;;; cells are handed to the reclaimer.  This macro is intended to be an in-line
;;; version of CL `delete' function.  The key, test, and reclaimer arguments
;;; must be symbols which name functions (or macros), not functions themselves
;;; (eg, a lambda expression will not work).

(defmacro delete-macro (element list &key
				(key 'identity-macro)
				(test 'eq)
				(reclaimer 'identity-macro))
  (avoiding-variable-capture (element list &aux head previous? this next)
    `(when ,list
       (loop with ,head = ,list
	     with ,previous?
	     for ,this = ,list then ,next
	     while ,this
	     as ,next = (cdr ,this)
	     doing
	 (cond ((null (,test ,element (,key (car ,this))))
		(setq ,previous? ,this))
	       ((null ,previous?)
		(setq ,head (cdr ,head))
		(,reclaimer ,this))
	       (t
		(setf (cdr ,previous?) ,next)
		(,reclaimer ,this)))

	     finally (return ,head)))))


#+development
(defun test-delete-macro (&key verbose)
  (let ((bugs 0)
	(stream (if verbose *standard-output* nil)))
    (labels ((reclaimer (e)
	       (format stream "  Reclaim ~s~%" e)
	       (setf (car e) 'xx
		     (cdr e) 'xx))
	     (d (e list)
	       (delete-macro e list :reclaimer reclaimer)))
      (macrolet ((test (list answer)
		   `(let* ((list (copy-list ',list))
			   (original (copy-list list))
			   (answer ',answer))
		      (format stream "List: ~s~%" original)
		      (setq list (d 1 list))
		      (format stream "  Result: ~s ~a~%" list
			      (cond ((equal answer list)
				     "")
				    (t
				     (incf bugs)
				     "***Bug***"))))))
	(test () ())
	(test (2) (2))
	(test (2 3) (2 3))
	(test (1) ())

	(test (1 2 3) (2 3))
	(test (2 1 3) (2 3))
	(test (2 3 1) (2 3))
	
	(test (1 1 2 3) (2 3))
	(test (2 1 1 3) (2 3))
	(test (2 3 1 1) (2 3))

	(test (1 2 1 3) (2 3))
	(test (1 2 3 1) (2 3))
	(test (2 1 3 1) (2 3))

	(test (1 1 1 1 1 2 1 3) (2 3))
	(test (1 1 1 1 1 2 1 3 1 1) (2 3))
	(test (1 1 4 1 1 2 1 3 1 1) (4 2 3))
	(format t "~&~d errors" bugs)
	(values)))))




;;; The macro `remove-property-macro' remprops the given property from the
;;; plist, returning the new plist.  Reclaimer is called on each discarded
;;; cons.

(defmacro remove-property-macro (plist indicator reclaimer)
  (avoiding-variable-capture
      (plist indicator &aux previous-cons head property value rest)
    `(loop as ,previous-cons = nil then (cdr ,head)
	   for ,head on ,plist by 'cddr
	   as (,property ,value . ,rest) = ,head
	   doing
       (when (eq ,property ,indicator)
	 (if ,previous-cons
	     (setf (cdr ,previous-cons) ,rest))

	 (,reclaimer (cdr ,head))
	 (,reclaimer ,head)
	 (if ,previous-cons
	     (return ,plist)
	     (return ,rest)))

	   finally
	     (return ,plist))))

(defmacro get-property-macro (plist indicator &optional default)
  (avoiding-variable-capture
      (plist indicator default &aux property value)
    `(loop for (,property ,value) on ,plist by 'cddr
	   doing
       (when (eq ,property ,indicator)
	 (return ,value))
	   finally
	     (return ,default))))

(defmacro set-property-macro (plist indicator conser new-value)
  (avoiding-variable-capture
      (plist indicator new-value &aux head property value)
    `(loop for ,head on ,plist by 'cddr
	   as (,property ,value) = ,head
	   doing
       (when (eq ,property ,indicator)
	 (setf (cadr ,head) ,new-value)
	 (return ,plist))

	   finally
	     (return (,conser ,indicator
			      (,conser ,new-value
				       ,plist))))))





;;; `Atom-or-list-of-atoms' is a data structure used
;;; in G2 because we are so thrifty.  It is used in
;;; places were we expect lists of one element to be
;;; so common that we should optimize the storage of
;;; a one element list to eliminate the cons.  The
;;; following few routines can make the code that works on
;;; these lists slightly more readable.

(def-concept atom-or-list-of-atoms)

;;; `Symbol-or-list-of-symbols' see atom-or-list-of-atoms

(def-concept symbol-or-list-of-symbols)


;;; The functions `ca/dr-or-atom' define a CAR and CDR which
;;; treat atoms like lists of one element.

(defun car-or-atom (thing)
  (if (consp thing) (car thing) thing))

(defun cdr-or-atom (thing)
  (if (consp thing) (cdr thing) nil))

(def-substitution-macro gensym-cons-or-atom (car cdr)
  (if (and (atom car) (null cdr)) car (gensym-cons car cdr)))

;;; `Do-atom-or-list-of-atoms' loop over the atoms in the
;;; atom-or-list-of-atoms given.

(defmacro do-atom-or-list-of-atoms ((v tiny-list) &body body)
  `(loop as #1=#:names-sic = ,tiny-list
			then (if (consp #1#) (cdr #1#) nil)
	 as ,v = (if (consp #1#) (car #1#) #1#)
	 while ,v
	 do ,@body))



;;; The function `quoted-form-p' returns t for lists whose
;;; car is quote.

(defun-for-macro quoted-form-p (form)
  (declare (eliminate-for-gsi))
  (and (consp form)
       (eq (car form) 'quote)))


;;; The function `unquote' returns the cadr of quoted forms,
;;; and is an identity for others.

(defun-for-macro unquote (form)
  (declare (eliminate-for-gsi))
  (if (quoted-form-p form)
      (cadr form)
      form))


(defmacro apply-simple-compiled-function
    (function arguments &optional (maximum-number-of-arguments 10))
  (avoiding-variable-capture (function arguments)
    `(case (length ,arguments)
       ,@(loop for i below maximum-number-of-arguments
	       as args = () then (cons `(pop ,arguments) args)
	       collect `(,i (funcall-simple-compiled-function ,function ,@args)))
       #+development
       (t
	(error "Too many arguments to apply-simple-compiled-function.")))))




(defmacro first-of-cons (the-cons)
  `(car-of-cons ,the-cons))

(defmacro second-of-cons (the-cons)
  `(car-of-cons (cdr-of-cons ,the-cons)))

(defmacro third-of-cons (the-cons)
  `(car-of-cons (cdr-of-cons (cdr-of-cons ,the-cons))))

(defmacro fourth-of-cons (the-cons)
  `(car-of-cons (cdr-of-cons (cdr-of-cons (cdr-of-cons ,the-cons)))))

(defmacro fifth-of-cons (the-cons)
  `(car-of-cons
     (cdr-of-cons (cdr-of-cons (cdr-of-cons (cdr-of-cons ,the-cons))))))

(defmacro cadr-of-cons (the-cons)
  `(car-of-cons (cdr-of-cons ,the-cons)))

(defmacro cddr-of-cons (the-cons)
  `(cdr-of-cons (cdr-of-cons ,the-cons)))

(defmacro caar-of-cons (the-cons)
  `(car-of-cons (car-of-cons ,the-cons)))

(defmacro caadr-of-cons (the-cons)
  `(car-of-cons (car-of-cons (cdr-of-cons ,the-cons))))






;;; The macro `alist-to-plist' desctructively modifies alist, an association
;;; list of the form
;;;
;;;    ( { (indicator . value) } )
;;;
;;; and creates plist, a property list of the form
;;;
;;;    ( { indicator value } )
;;;
;;; and returns plist.
;;;
;;; The macro `alist-to-plist-macro' is just an inline macro variant of the the
;;; same function.

(defmacro alist-to-plist-macro (alist)
  `(loop with l = ,alist
	 with cdr-l
	 with result = l
	 with cons-cell
	 with indicator
	 with value
	 while l
	 do (setf cdr-l (cdr-of-cons l))
	    (setq cons-cell (car-of-cons l))
	    (setq indicator (car-of-cons cons-cell))
	    (setq value (cdr-of-cons cons-cell))
	    (setf (cdr-of-cons l) cons-cell)
	    (setf (cdr-of-cons cons-cell) cdr-l)
	    (setf (first l) indicator)
	    (setf (second l) value)
	    (setq l cdr-l)
	 finally (return result)))

(defun-simple alist-to-plist (alist)
  (alist-to-plist-macro alist))


;;; These three are used only at load-time, so they cons in permanent stg.
;;; Moved here from NEW-MENUS -fmw, 11/29/04

(defmacro push-onto-end (thing place)
  `(setf ,place (nconc ,place (list ,thing))))

(defmacro pushnew-onto-end (thing place)
  `(unless (memq ,thing ,place)
     (setf ,place (nconc ,place (list ,thing)))))

;;; The macro `push-update' replaces the named item in the list
;;; if it is already there, else it adds it to the front of the list.
;;; KEY is not evaluated, and must a symbol naming a function.

(defmacro push-update (item list &key (key 'identity))
  `(loop for sublist on ,list
	 for key = (,key (car sublist))
	 if (eq key (,key ,item))
	   do (setf (car sublist) ,item)
	      (return ,item)
	 finally
	   (setf ,list (cons ,item ,list))))
