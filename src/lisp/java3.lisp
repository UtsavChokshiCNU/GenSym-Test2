;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-

;;;; Module JAVA3

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; John Hodgkinson

(in-package "AB")

;;;; Overview

;;; The idea is to emit Java that allow calls into G2 from JavaLink, and to do
;;; so dynamically.  This work is paralleled by other efforts that emit class
;;; files directly from Java, but all are necessary in the current (jh per jed,
;;; 8/5/97) plan.  So the intent is to have as similar a "look-and-feel" between
;;; the APIs as possible.

;;; Hence, we start with the assumption that the most canonical way of
;;; representing a Java class file is Java source code.  So we transform
;;; syntax-trees of the sort built from the parser in JAVA2 into a Java source
;;; file containing methods specified in the "as interface" type of
;;; export-definition created by JAVA1.  JavaLink then loads the corresponding
;;; class file on the fly, invokes the init() method to declare the method
;;; remotely, and is then able to invoke G2 procedures or methods directly from
;;; Java code.

;;; The next step is to emit class files directly.  For users who want to retain
;;; the generated sources, there will be an arrangement like rmic's
;;; "keepgenerated" flag.

;;; An advantage of starting from syntax-trees is that it opens the door to
;;; emitting class files specified as template, that is, incomplete but valid
;;; syntax-tree patterns that are later filled with specific data.  This could
;;; eventually allow us to do many "macro-like" things with Java code.

;;; The Java Remote Method Invocation spec defines `stub' as a client-side
;;; marshalling wrapper for a remote method, and `skeleton' as the server-side
;;; wrapper.  For the present, there is no need to implement skeletons, since
;;; remote procedure invocation is handled by the GSI/ICP substrate, nor is
;;; there any need to use all the structure offered by the spec for Java class
;;; files.

;;; But we do need to:
;;;   (1) emit a Java file for a stub class (source, later class)
;;;   (2) whose constructor (indirectly) uses GSI's declare_remote() on methods
;;;   (3) that can wrap internal methods
;;;   (4) whose arguments and return type are marshalled into JavaLink types
;;;   (5) whose throw semantics are expressed in JavaLink terms
;;;   (6) and that implements minimal reflection

;;; Other issues:
;;;   > Network security
;;;   > We are creating yet another IDL - do we want to formalize it for furture
;;;     use in facilities more complex than stubs?
;;;   > Use Ben's J-Lisp stuff to make APIs converge even more?

;;;; Internal Class-Export Structures

;;; The `external-class-info' structure is maintained in the
;;; visible-class-export-information? attribute of the export-definition frame.

;;; Note we also sometimes need to store the data that goes into an
;;; export-definition before the user creates one explicitly.  For instance,
;;; get-class-info should cache export-definition data for efficiency reasons.
;;; (It is necessary while gathering this data to parse each instance method,
;;; and that takes time.)  We handle such circumstances this by storing a dummy
;;; export-definition in the implicit-class-export-information? slot of the
;;; class-description structure.  We need to use an export-definition frame
;;; rather an external-class-info structure because we need to do consistency
;;; analysis against changes in the class methods, and consistency analysis is
;;; based on frames, not structures.  Should the end-user create an
;;; export-definition item for a class that has been cached in this way, the
;;; information is tranferred from the dummy, which is then deleted.

(def-structure (external-class-info
		 (:constructor
		   make-external-class-info
		   (external-class-name
		     external-static-methods
		     external-instance-methods)))
  external-class-name
  (external-static-methods nil   
   :reclaimer reclaim-list-of-external-methods)
  (external-instance-methods nil 
   :reclaimer reclaim-list-of-external-methods)
  )

(defun-void reclaim-external-class-info-list (external-class-info-list)
  (loop for external-class-info in external-class-info-list
	do
    (reclaim-external-class-info external-class-info))
  (reclaim-slot-value-list external-class-info-list))    

(defun-void delete-export-frame-if-any (frame?)
  (when frame?
    (let ((analyzing-export-definition-for-consistency-p t))
      (delete-frame frame?))))

(def-structure (external-method-info
		 (:constructor
		   make-external-method-info-internal
		   (cached-external-method-class
		     cached-external-method-name
		     external-method-static-p
		     instance-method-declaration-frame
		     instance-method-frame?
		     external-method-signature)))
  cached-external-method-class
  cached-external-method-name
  cached-g2-qualified-method-name
  ;; Substructure shared with procedure frame, only reclaim spine.
  (external-method-signature nil :reclaimer reclaim-gensym-list)
  ;; Substructure shared with procedure frame, only reclaim spine.
  (external-method-result-type nil :reclaimer reclaim-gensym-list)
  ;; No substructure.
  (external-method-signalled-classes? nil :reclaimer reclaim-gensym-list)
  external-method-static-p
  (instance-method-declaration-frame nil :reclaimer delete-export-frame-if-any)
  (instance-method-frame? nil :reclaimer delete-export-frame-if-any)
  (instance-method-frame-note? nil
   :reclaimer reclaim-text-or-gensym-string-if-any)
  )

(defun-void reclaim-class-export-information-if-any (export-info)
  (when (framep export-info)
    (delete-frame export-info)))

(defun-simple make-external-method-info
    (method-class
      method-name
      g2-procedure
      external-method-static-p
      method-declaration-frame?
      method-frame?)
  (let ((external-method-info
	  (make-external-method-info-internal
	    method-class
	    method-name
	    external-method-static-p
	    method-declaration-frame?
	    method-frame?
	    (collect-types-into-list-using-gensym-conses
	      (argument-list-description g2-procedure)))))
    (setf (cached-g2-qualified-method-name external-method-info)
	  (if external-method-static-p
	      method-name
	      (intern-text-string
		(twith-output-to-text-string
		  (tformat "~A::~A" method-class method-name))
		"KEYWORD")))
    external-method-info))

(defun-void reclaim-list-of-external-methods (external-methods)
  (loop for external-method in external-methods
	do (reclaim-external-method-info external-method))
  (reclaim-slot-value-list external-methods))


;;;; Filling Internal Class-Export Structures

;; jh, 8/7/97.  We need to do exceptions.  We are exporting multiple class files
;; anyway (one for the interface and one for the implementation) and this would
;; increase the generality of the exporting mechanism to a par with RMI.

(defun-simple walk-for-signaled-designations (parsed-definition accum)
  (cond
    ((not (consp parsed-definition)) accum)
    ((eq (car parsed-definition) 'signal-statement-new)
     (gensym-cons (cadr parsed-definition) accum))
    (t (walk-for-signaled-designations
	 (car parsed-definition)
	 (walk-for-signaled-designations (cdr parsed-definition) accum)))))

;;; The simple function `chase-signaled-class-if-any' uses a few obvious
;;; heuristics to track down the class mentioned in a "signal" statement, namely
;;; the class of an argument, local variable, or global variable.

(defun-simple chase-signaled-class-if-any (designation parsed-definition)
  (if (symbolp designation)
      (or (loop for (local-name local-type) in (fourth parsed-definition)
		thereis
		(and (eq local-name designation)
		     (consp local-type)
		     (eq (car local-type) 'class)
		     (second local-type)))
	  (loop for (arg-name arg-type) in (second parsed-definition)
		thereis
		(and (eq arg-name designation)
		     (consp arg-type)
		     (eq (car arg-type) 'class)
		     (second arg-type)))
	  (let ((global?
		  (get-instance-with-name-if-any 'item designation)))
	    (and global? (class global?))))
      ;; jh, 8/7/97.  There is no doubt vast type-inference mechanism that would
      ;; let us do better here, so this branch should be revisited.
      'error))

(defun-simple collect-classes-signaled-in-procedure (g2-procedure)
  (let ((signaled-classes nil)
	(procedure-text? (cdr (procedure-definition g2-procedure))))
    (when procedure-text?
      (with-phrase-conses
	(let* ((definition-as-text-string
		   (convert-text-to-text-string procedure-text?))
	       (parsed-definition
		 (parse-text-string
		   definition-as-text-string
		   'procedure-definition))
	       (signaled-designations
		 (walk-for-signaled-designations parsed-definition nil)))
	  (reclaim-text-string definition-as-text-string)
	  (loop for designation in signaled-designations
		do
	    (let ((known-class?
		    (chase-signaled-class-if-any
		      designation
		      parsed-definition)))
	      (when known-class?
		(gensym-pushnew known-class? signaled-classes))))
	  (reclaim-gensym-list signaled-designations))))
    (nreverse signaled-classes)))

;;; The function `collect-export-info-for-all-classes' takes a single argument,
;;; an instance of the export-definition class, and returns a slot-value-list of
;;; external-class-info structures, suitable for placement by an
;;; analyze-for-consistency method in the visible-class-export-information?
;;; attribute of an export-definition class.  Each static method named in the
;;; export-definition corresponds to a G2 procedure.  Instance methods come from
;;; each G2 method in the KB that dispatches on the class named by the
;;; export-definition.

(defun-simple collect-export-info-for-all-classes (export-definition)
  (let* ((definition-spec (export-definition-specification export-definition))
	 (language (export-definition-language-symbol definition-spec))
	 (export-specs (export-definition-class-specs definition-spec)))
    (case language
      (java
       (loop for (export-class export-type options) in export-specs
	     with classes-encountered = nil
	     do (java-push export-class classes-encountered)
	     when (and (memq export-type '(interface code nil))
		       (not (memq export-class (cdr classes-encountered))))
	       collect
	       (make-export-info-for-one-class export-class options)
		 using slot-value-cons
	     finally (reclaim-java-list classes-encountered))))))

(defun-simple make-export-info-for-one-class (export-class options)
  (let ((static-methods
	  (collect-static-method-export-info
	    export-class
	    (cadr (assq 'static-methods options))))
	(instance-methods
	  (collect-instance-method-export-info export-class options)))
    (make-external-class-info
      export-class
      static-methods
      instance-methods)))  

(defun-simple collect-static-method-export-info (export-class procedure-names)
  (loop for procedure-name in procedure-names
	for g2-procedure?
	;; Notification of non-existent procedures is by frame note, so it's OK
	;; to ignore such procedures here.
	    = (get-instance-with-name-if-any 'procedure procedure-name)
	when g2-procedure?
	  collect
	  (make-external-method-info-for-g2-method
	    export-class
	    g2-procedure?
	    t
	    t)
	    using slot-value-cons))

(defun-simple make-external-method-info-for-g2-method
    (export-class g2-method static-p try-parse-p)
  (let ((declaration-frame (make-frame 'external-method-declaration))
	(method-frame (if static-p
			  (make-frame 'external-procedure)
			  (make-frame 'external-method)))
	(method-name (if static-p
			 (name-or-names-for-frame g2-method)
			 (procedure-method-name g2-method))))
    ;; Do not use change-slot-value, as it injects spurious non-unique-names
    ;; frame notes into the G2 procedures and methods we're exporting.
    (setf (name-or-names-for-frame declaration-frame) method-name)
    (let ((external-method-info
	    (make-external-method-info
	      export-class
	      method-name
	      g2-method
	      static-p
	      declaration-frame
	      method-frame)))
      (when try-parse-p
	(try-to-parse-external-method-definition
	  external-method-info
	  method-frame
	  (copy-text (cdr (procedure-definition g2-method)))
	  static-p))
      external-method-info)))  

(defun collect-instance-method-export-info
    (export-class options &optional (try-parse-p t))
  (multiple-value-bind (cached-instance-info cache-existed-p)
      (decache-implicit-external-instance-method-info-if-any
	export-class)
    (if cache-existed-p
	cached-instance-info
	(loop with included-instance-methods?
		= (cdr (assq 'included-instance-methods options))
	      with excluded-instance-methods?
		= (cdr (assq 'excluded-instance-methods options))
	      for g2-method being each class-instance of 'method
	      for method-name = (procedure-method-name g2-method)
	      when (and (eq (procedure-method-class g2-method) export-class)
			(cond
			  (included-instance-methods?
			   (memq method-name included-instance-methods?))
			  (included-instance-methods?
			   (not (memq method-name excluded-instance-methods?)))
			  (t t)))
		collect
		(make-external-method-info-for-g2-method
		  export-class
		  g2-method
		  nil
		  try-parse-p)
		  using slot-value-cons))))

;;;; Using the Parser to Intersect G2 and Java Semantics

;; jh, 9/20/97.  Scaffolding note: analyze-export-info-for-parsability needs to
;; happen after (1) the procedure-method-class and -name are filled by the
;; slot-value-compiler for procedure-definition then (2) the
;; analyze-for-consistency method of the govening export-definition is called.
;; The slot-putter for procedure-definition should be a convenient place to call
;; this function, modulo some obscure aspect of the slot mutation protocol.

(defun-void analyze-export-info-for-parsability
    (g2-method-or-procedure definition-text)
  (cond
      ((frame-of-class-p g2-method-or-procedure 'method)
       (analyze-export-methods-for-parsability
	 g2-method-or-procedure
	 definition-text))
      (t (analyze-export-procedures-for-parsability
	   g2-method-or-procedure
	   definition-text))))

;; jh, 10/17/97.  Remove after 5.1 ships.
(defvar bypass-fix-for-exported-method-overloading-p nil)
(defun-for-system-procedure g2-switch-fix-for-exported-method-overloading
    (bypass)
  (setq bypass-fix-for-exported-method-overloading-p
	(>=f (evaluation-truth-value-value bypass)
	     (truth-threshold inference-engine-parameters)))
  bypass)

(defun-simple matching-instance-method-info-p (method-info g2-method)
  (and ;; Same class.
       (eq (cached-external-method-class method-info)
	   (procedure-method-class g2-method))
       ;; Same name.
       (eq (cached-external-method-name method-info)
	   (procedure-method-name g2-method))
       ;; Same arglist.
       (let* ((arg-description (argument-list-description g2-method))
	      (arg-description-as-tree
		(collect-types-into-list-using-gensym-conses
		  arg-description)))
	 (prog1
	     (equal arg-description-as-tree
		    (external-method-signature method-info))
	   (reclaim-gensym-list ;Yes, reclaim a list, not a tree.
	     arg-description-as-tree)))))

;; jh, 9/30/97.  Note that analyze-export-methods-for-parsability punts on
;; whether or not a G2 method can be exported as static, i.e., with an explicit
;; "self" argument.

(defun-void analyze-export-methods-for-parsability
    (g2-method g2-method-definition-text)
  (cond
    ;; jh, 10/17/97.  Remove after 5.1 ships.
    (bypass-fix-for-exported-method-overloading-p
     (old-analyze-export-methods-for-parsability
       g2-method
       g2-method-definition-text))
    (t (let ((class-name (procedure-method-class g2-method)))
	 (loop for export-definition
		   being each class-instance of 'export-definition
	       do
	   (loop for class-info
		     in (visible-class-export-information? export-definition)
		 do
	     (when (eq class-name (external-class-name class-info))
	       (let ((method-info?
		       (loop for method-info
				 in (external-instance-methods class-info)
			     thereis
			     (and (matching-instance-method-info-p
				    method-info
				    g2-method)
				  method-info))))
		 (unless method-info?
		   (setq method-info?
			 (make-external-method-info-for-g2-method
			   class-name
			   g2-method
			   nil
			   t))
		   (slot-value-push method-info?
				    (external-instance-methods class-info)))
		 (clear-problem-mapping-g2-to-java-source-particulars
		   export-definition
		   class-name)
		 (analyze-exported-executable-for-parsability
		   export-definition
		   method-info?
		   g2-method-definition-text
		   nil)
		 (loop-finish)))))))))

(defun-void old-analyze-export-methods-for-parsability
    (g2-method g2-method-definition-text)
  (let ((class-name (procedure-method-class g2-method)))
    (loop for export-definition
	      being each class-instance of 'export-definition
	  do
      (loop for class-info
		in (visible-class-export-information? export-definition)
	    do
	(when (eq class-name (external-class-name class-info))
	  (let* ((g2-method-name (procedure-method-name g2-method))
		 (method-info?
		   (loop for method-info
			     in (external-instance-methods class-info)
			 thereis
			 (and (eq (cached-external-method-name method-info)
				  g2-method-name)
			      method-info))))
	    (unless method-info?
	      (setq method-info?
		    (make-external-method-info-for-g2-method
		      class-name
		      g2-method
		      nil
		      t))
	      (slot-value-push method-info?
			       (external-instance-methods class-info)))
	    (clear-problem-mapping-g2-to-java-source-particulars
	      export-definition
	      class-name)
	    (analyze-exported-executable-for-parsability
	      export-definition
	      method-info?
	      g2-method-definition-text
	      nil)
	    (loop-finish)))))))

(defun-void analyze-exported-executable-for-parsability
    (export-definition method-info-struct definition-text static-p)
  (try-to-parse-external-method-definition
    method-info-struct
    (instance-method-frame? method-info-struct)
    (copy-text (cdr definition-text))
    static-p)
  (update-unexportable-external-method-frame-note-if-appropriate
    export-definition
    method-info-struct)
  (unless static-p
    (update-instance-methods-attribute export-definition))
  (let ((qualified-name
	  (cached-g2-qualified-method-name method-info-struct))
	(method-name
	  (cached-external-method-name method-info-struct)))
    ;; Need to catch edits to the method itself.  This is done outside of
    ;; consistency analysis because we need some fields only filled in by the
    ;; slot-putter.
    (add-to-set 
      (compiled-items-referring-to-this-name qualified-name)
      export-definition
      installation)
    ;; Need to catch edits to method-declaration of an instance method.
    (unless (eq qualified-name method-name) ;i.e., unless method is static
      (add-to-set 
	(compiled-items-referring-to-this-name
	  (cached-external-method-name method-info-struct))
	export-definition
	installation))))

(defun-void analyze-export-procedures-for-parsability
    (g2-procedure g2-procedure-definition-text)
  (let ((g2-procedure-name (name-or-names-for-frame g2-procedure)))
    (loop for export-definition
	      being each class-instance of 'export-definition
	  do
      (add-newborn-external-static-methods-as-appropriate
	g2-procedure-name
	export-definition)
      (loop for class-info
		in (visible-class-export-information? export-definition)
	    do
	(loop for method-info in (external-static-methods class-info)
	      do
	  (let ((method-info?
		  (and (eq (cached-g2-qualified-method-name method-info)
			   g2-procedure-name)
		       method-info)))
	    (when method-info?
	      (clear-problem-mapping-g2-to-java-source-particulars
		export-definition
		(external-class-name class-info))
	      (analyze-exported-executable-for-parsability
		export-definition
		method-info?
		g2-procedure-definition-text
		t)
	      (loop-finish))))))))

(defun-void add-newborn-external-static-methods-as-appropriate
    (g2-procedure-name export-definition)
  (loop with export-specs
	  = (export-definition-specification export-definition)
	for class-info
	    in (visible-class-export-information? export-definition)
	as class-name = (external-class-name class-info)
	do
    (let* ((options
	     (export-definition-options-for-class-if-any
	       class-name
	       export-specs))
	   (desired-static-names
	     (cadr (assq 'static-methods options))))
      (when (and (memq g2-procedure-name desired-static-names)
		 (loop for method-info
			   in (external-static-methods class-info)
		       never
		       (eq (cached-external-method-name method-info)
			   g2-procedure-name)))
	(update-external-static-method-info
	  class-info
	  class-name
	  options
	  nil)))))

(defun-void clear-unexportable-external-method-frame-note
    (export-definition method-info)
  (let ((particular-key (cached-g2-qualified-method-name method-info))
	(particulars
	  (get-particulars-of-frame-note-if-any
	    'unexportable-external-method
	    export-definition)))
    (loop for (flawed-method) in particulars
	  for particular in particulars
	  do
      (when (eq particular-key flawed-method)
	(delete-from-frame-note-particulars-list
	  particular
	  'unexportable-external-method
	  export-definition)
	(loop-finish)))))

(defun-simple nstring-downcasew-outside-double-quotes (wide-string)
  (loop for i from 0 below (wide-string-length wide-string)
	as this-char = (charw wide-string i)
	with inside-double-quote-p = nil
	do
    (when (char=w this-char #.%\")
      (setq inside-double-quote-p (not inside-double-quote-p)))
    (setf (charw wide-string i) 
	  (if inside-double-quote-p
	      this-char
	      (char-downcasew this-char))))
  wide-string)

(defun-void update-unexportable-external-method-frame-note-if-appropriate
    (export-definition method-info)
  (clear-unexportable-external-method-frame-note
    export-definition
    method-info)
  (let ((frame-note? (instance-method-frame-note? method-info)))
    (when frame-note?
      (let ((particular-key (cached-g2-qualified-method-name method-info)))
	(add-to-frame-note-particulars-list-if-necessary
	  (slot-value-list
	    particular-key
	    (nstring-downcasew ;-outside-double-quotes not quite right
	      (copy-text-string-without-newlines frame-note? nil)))
	  'unexportable-external-method
	  export-definition)))))

(defun-void try-to-parse-external-method-definition
    (external-method-info
      external-method-frame
      method-definition-text
      static-p)
  (let* ((method-name?
	   (if static-p
	       nil
	       (cached-external-method-name external-method-info)))
	 (method-declaration?
	   (and method-name?
		(get-instance-with-name-if-any
		  'method-declaration
		  method-name?)))
	 (reason-for-failure? nil))
    (cond
      ((or static-p method-declaration?)
       (setq reason-for-failure?
	     (nth-value 1
	       (parse-text-for-slot
		 method-definition-text
		 external-method-frame
		 (get-slot-description-of-frame
		   'external-procedure-definition
		   external-method-frame)
		 t      ;runtime-change? 
		 nil    ;type-of-slot?
		 nil    ;slot-component-name?
		 nil    ;slot-component-indicator?
		 t))))  ;make-reason-for-failure-p
      (method-name? 
       (setq reason-for-failure?
	     (twith-output-to-text-string
	       (tformat
		 "there is no method-declaration named ~A" method-name?)))))
    (reclaim-text-or-gensym-string-if-any
      (instance-method-frame-note? external-method-info))
    (setf (instance-method-frame-note? external-method-info)
	  reason-for-failure?)))



;;;; Consistency of External Instance Methods

;;; The void function `check-exported-classes' is one of several called during
;;; the consistency analysis of an instance of export-definition.  This
;;; functaion checks for other export-definitions that mention the same class.
;;; It makes a lot more sense to complain here than to try to figure out what
;;; the user meant by doing that.  It also makes sense to side-step calling
;;; analyze-compiled-items-for-consistency here, since it will do a lot of work
;;; extraneous to the task of adjusting frame notes.

(defun-void check-exported-classes (export-definition exported-class)
  (add-or-delete-as-item-referring-to-name exported-class)
  (cond
    ;; In the following clause, we are removing an export named by
    ;; exported-class, so we remove frame notes from the appropriate instances.
    (delete-as-item-referring-to-name?
     (let ((duplicates?
	     (loop for this-export-definition
		       being each class-instance of 'export-definition
		   when
		     (and (not (eq this-export-definition export-definition))
			  (loop for (this-exported-class)
				    in (export-definition-class-specs
					 (export-definition-specification
					   this-export-definition))
				thereis
				(eq this-exported-class exported-class)))
		     collect this-export-definition using java-cons)))
       (cond
	 ;; More than one conflict - retain the frame notes in this case.
	 ((cdr duplicates?) (reclaim-java-list duplicates?))
	 ;; Remove the frame note if there's only one conflict.
	 (duplicates?
	  (delete-from-frame-note-particulars-list
	    exported-class
	    'duplicate-class-export
	    (java-pop duplicates?))))))
    (t ;; Check for the existence of exported classes.
       (unless (get-instance-with-name-if-any 'class-definition exported-class)
	 (add-to-frame-note-particulars-list-if-necessary
	   exported-class
	   'nonexistent-classes-for-export
	   export-definition))

       ;; Here we are adding an export named by exported-class, so we add frame
       ;; notes to the appropriate instances.
       (loop for this-export-definition
		 being each class-instance of 'export-definition
	     with noted-here-p = nil
	     do
	 (unless (eq this-export-definition export-definition)
	   (loop for (this-exported-class)
		     in (export-definition-class-specs
			  (export-definition-specification
			    this-export-definition))
		 do
	     (when (eq this-exported-class exported-class)
	       (unless noted-here-p
		 (add-to-frame-note-particulars-list-if-necessary
		   exported-class
		   'duplicate-class-export
		   export-definition)
		 (setq noted-here-p t))
	       (add-to-frame-note-particulars-list-if-necessary
		 this-exported-class
		 'duplicate-class-export
		 this-export-definition))))))))

;;; The void function `check-external-static-methods' is one of several called
;;; during the consistency analysis of an instance of export-definition.  This
;;; function is only resposible for updating frame notes; the function
;;; check-external-static-method-info, also called by the top-level consistency
;;; analyzer analyze-export-definition-for-consistency, is in charge of updating
;;; the internall-maintained external-method-info structure.

(defun-void check-external-static-methods
    (export-definition exported-class options)
  (let ((static-methods (cadr (assq 'static-methods options))))
    (cond
      (delete-as-item-referring-to-name?
       (loop for static-method in static-methods
	     unless (get-instance-with-name-if-any 'procedure static-method)
	       do (add-or-delete-as-item-referring-to-name static-method)))
      (t (let ((nonexistent-static-methods? nil))
	   (loop for static-method in static-methods
		 do
	     (add-or-delete-as-item-referring-to-name static-method)
	     (unless (get-instance-with-name-if-any 'procedure static-method)
	       (slot-value-push static-method nonexistent-static-methods?)))
	   (when nonexistent-static-methods?
	     (nreversef nonexistent-static-methods?)
	     (add-to-frame-note-particulars-list-if-necessary
	       (slot-value-cons exported-class nonexistent-static-methods?)
	       'nonexistent-static-methods-for-export
	       export-definition)))))))

;;; The void function `check-external-instance-method-info' is one of several
;;; called during the consistency analysis of an instance of export-definition.
;;; This function is designed to run after an edit to an export-definition is
;;; committed.  It is only responsible for adding and removing consistency
;;; notification as appropriate.  This function is not responsible for checking
;;; that the body of a method being added is suitable for emission as Java code.
;;; This check is performed elsewhere, by the various callers of
;;; try-to-parse-external-method-definition.

(defun-void check-external-instance-method-info (export-definition)
  (shared-check-external-method-info export-definition nil)
  (update-instance-methods-attribute export-definition))

(defun-void shared-check-external-method-info (export-definition static-p)
  (cond
    ;; jh, 10/17/97.  Remove after 5.1 ships.
    (bypass-fix-for-exported-method-overloading-p
     (old-shared-check-external-method-info export-definition static-p))
    (t (new-shared-check-external-method-info export-definition static-p))))

(defun-void old-shared-check-external-method-info (export-definition static-p)
  (cond
    (add-as-item-referring-to-name?
     (loop for class-info
		 in (visible-class-export-information? export-definition)
	     do
       (loop for method-info in (if static-p
				    (external-static-methods class-info)
				    (external-instance-methods class-info))
	     do
	 (add-or-delete-as-item-referring-to-name
	   (cached-g2-qualified-method-name method-info))
	 (update-unexportable-external-method-frame-note-if-appropriate
	   export-definition
	   method-info))))
    (t (loop for class-info
		 in (visible-class-export-information? export-definition)
	     for class-name = (external-class-name class-info)
	     do
	 (let* ((old-method-info-list
		  (if static-p
		      (external-static-methods class-info)
		      (external-instance-methods class-info)))
		(new-method-info-list
		  (loop for method-info in old-method-info-list
			for qualified-name
			    = (cached-g2-qualified-method-name method-info)
			for g2-procedure?
			    = (get-instance-with-name-if-any
				'procedure
				qualified-name)
			nconc
			(make-listed-external-method-info-if-valid
			  g2-procedure?
			  export-definition
			  class-name
			  qualified-name
			  method-info
			  static-p))))
	   (reclaim-slot-value-list old-method-info-list)
	   (if static-p
	       (setf (external-static-methods class-info)
		     new-method-info-list)
	       (setf (external-instance-methods class-info)
		     new-method-info-list)))))))

(defun-simple get-instance-or-instances-with-name-if-any (class name)
  (let ((frame-or-frames-with-this-name
	  (frame-or-frames-with-this-name-macro name)))
    (if frame-or-frames-with-this-name
	(if (atom frame-or-frames-with-this-name)
	    (if (frame-of-class-p frame-or-frames-with-this-name class)
		(slot-value-list frame-or-frames-with-this-name)
		nil)
	    (loop for frame in frame-or-frames-with-this-name
		  when (frame-of-class-p frame class)
		    collect frame using slot-value-cons))
	nil)))

(defun-simple get-matching-g2-procedure-if-any (method-info static-p)
  (let ((qualified-name (cached-g2-qualified-method-name method-info)))
    (if static-p
	(get-instance-with-name-if-any
	  'procedure
	  qualified-name)
      (let* ((g2-methods?
	       (get-instance-or-instances-with-name-if-any
		 'method
		 qualified-name))
	     (matching-method-if-any
	       (loop for g2-method in g2-methods?
		     thereis
		     (and (matching-instance-method-info-p
			    method-info
			    g2-method)
			  g2-method))))
	(reclaim-slot-value-list g2-methods?)
	matching-method-if-any))))

(defun-void new-shared-check-external-method-info (export-definition static-p)
  (cond
    (add-as-item-referring-to-name?
     (loop for class-info
		 in (visible-class-export-information? export-definition)
	     do
       (loop for method-info in (if static-p
				    (external-static-methods class-info)
				    (external-instance-methods class-info))
	     do
	 (add-or-delete-as-item-referring-to-name
	   (cached-g2-qualified-method-name method-info))
	 (update-unexportable-external-method-frame-note-if-appropriate
	   export-definition
	   method-info))))
    (t (loop for class-info
		 in (visible-class-export-information? export-definition)
	     for class-name = (external-class-name class-info)
	     do
	 (let* ((old-method-info-list
		  (if static-p
		      (external-static-methods class-info)
		      (external-instance-methods class-info)))
		(new-method-info-list
		  (loop for method-info in old-method-info-list
			for qualified-name
			    = (cached-g2-qualified-method-name method-info)
			for g2-procedure?
			    = (get-matching-g2-procedure-if-any
				method-info
				static-p)
			nconc
			(make-listed-external-method-info-if-valid
			  g2-procedure?
			  export-definition
			  class-name
			  qualified-name
			  method-info
			  static-p))))
	   (reclaim-slot-value-list old-method-info-list)
	   (if static-p
	       (setf (external-static-methods class-info)
		     new-method-info-list)
	       (setf (external-instance-methods class-info)
		     new-method-info-list)))))))

(defun-simple make-listed-external-method-info-if-valid
    (g2-procedure?
      export-definition
      class-name
      qualified-name
      method-info
      static-p)
  (let (definition-text)
    (cond
      ((and g2-procedure?
	    (not (same-definition-text-p
		   (setq definition-text (procedure-definition g2-procedure?))
		   method-info)))
       (let ((new-method-info
	       (make-external-method-info-for-g2-method
		 class-name
		 g2-procedure?
		 static-p
		 nil)))
	 (analyze-exported-executable-for-parsability
	   export-definition
	   new-method-info
	   definition-text
	   static-p)
	 (reclaim-external-method-info method-info)
	 (slot-value-list new-method-info)))
      (g2-procedure? (slot-value-list method-info))
      (t (clear-unexportable-external-method-frame-note
	   export-definition
	   method-info)
	 (add-or-delete-as-item-referring-to-name qualified-name)
	 (reclaim-external-method-info method-info)
	 nil))))

(defun-simple same-definition-text-p (g2-procedure-definition-text method-info)
  (equalw
    g2-procedure-definition-text
    (external-procedure-definition (instance-method-frame? method-info))))

;;; The void function `check-external-static-method-info' is one of several
;;; called during the consistency analysis of an instance of export-definition.
;;; This function is designed to run after an edit to an export-definition is
;;; committed.  It is only responsible for adding and removing consistency
;;; notification as appropriate.  This function is not responsible for checking
;;; that the body of a method being added is suitable for emission as Java code.
;;; This check is performed elsewhere, by the various callers of
;;; try-to-parse-external-method-definition.

(defun-void check-external-static-method-info (export-definition)
  (shared-check-external-method-info export-definition t))

(def-frame-note-writer unexportable-external-method (particulars)
  (let ((enumerate-p (cdr particulars)))
    (loop for (method-name note) in particulars
	  for particulars-cons on particulars
	  for index from 0
	  do
      (when enumerate-p
	(tformat "(~A) " (+f index frame-note-index)))
      (tformat "method ~A could not be exported: ~A;"
	       method-name
	       note)
      (when enumerate-p
	(when (cdr particulars-cons)
	  (twrite-string ";")
	  (twrite-line-separator)))
	  finally (when enumerate-p
		    (setq frame-note-index-skip (1-f index))))))

(defun-void update-instance-methods-attribute (export-definition)
  (cond
    ;; jh, 10/17/97.  Remove after 5.1 ships.
    (bypass-fix-for-exported-method-overloading-p
     (old-update-instance-methods-attribute export-definition))
    (t (reclaim-slot-value (g2-instance-methods export-definition))
       (setf (g2-instance-methods export-definition)
	     (loop for class-info
		       in (visible-class-export-information? export-definition)
		   nconc
		   (let ((methods-for-this-class nil))
		     (loop for method-info
			       in (external-instance-methods class-info)
			   do
		       (slot-value-pushnew
			 (cached-g2-qualified-method-name method-info)
			 methods-for-this-class))
		     methods-for-this-class))))))

(defun-void old-update-instance-methods-attribute (export-definition)
  (reclaim-slot-value (g2-instance-methods export-definition))
  (setf (g2-instance-methods export-definition)
	(loop for class-info
		  in (visible-class-export-information? export-definition)
	      nconc
	      (loop for method-info
			in (external-instance-methods class-info)
		    collect (cached-g2-qualified-method-name method-info)
		      using slot-value-cons))))

;;;; Maintaining Internal Export Information

;;; The void function `update-all-external-instance-method-info' is the one-stop
;;; shop for coordinating the various slots slaved to the
;;; export-definition-specification slot in an export-definition.  It is called
;;; in the slot-putter for export-definition-specification, immediately after
;;; the raw setf itself.

(defun-void update-all-external-method-info (export-definition)
  (let* ((definition-spec (export-definition-specification export-definition))
	 (language (export-definition-language-symbol definition-spec))
	 (export-specs (export-definition-class-specs definition-spec)))
    
    ;; Coordinate with the visible-class-export-information? slot.  This
    ;; includes gathering the appropriate instance methods for each class being
    ;; exported.
    (case language
      (java
       (reconcile-exported-classes export-definition export-specs)
       (loop for (exported-class export-type options) in export-specs
	     do
	 (clear-problem-mapping-g2-to-java-source-particulars
	   export-definition
	   exported-class)
	 (case export-type
	   ((interface code nil)
	    (update-external-method-info
	      export-definition
	      exported-class
	      options))))))

    ;; Now that we have an accurate picture of the exported instance methods,
    ;; we can update the read-only, non-attribute-exported instance-methods
    ;; slot.
    (update-instance-methods-attribute export-definition)))

;;; The void function `reconcile-exported-classes' removes info for classes no
;;; longer in the export-definition-specification attribute from the
;;; visible-class-export-information? attribute and adds blank info for
;;; newly-mentioned classes.  In order to avoid re-parsing instance methods,
;;; this function re-uses class-export-information structures when possible, at
;;; the cost of some quadratic behavior.

(defun-void reconcile-exported-classes (export-definition export-specs)
  (let* ((old-class-info
	   (visible-class-export-information? export-definition))
	 (new-class-info
	   (loop for (exported-class nil options) in export-specs
		 for extant-class-struct?
		     = (loop for external-class-struct in old-class-info
			     thereis
			 (and (eq (external-class-name external-class-struct)
				  exported-class)
			      external-class-struct))
		 collect (or extant-class-struct?
			     (make-export-info-for-one-class
			       exported-class
			       options))
		   using slot-value-cons)))
    (loop for external-class-struct in old-class-info
	  do
      (unless (memq external-class-struct new-class-info)
	(reclaim-external-class-info external-class-struct)))
    (reclaim-slot-value-list old-class-info)
    (setf (visible-class-export-information? export-definition)
	  new-class-info)))

;;; The void function `update-external-method-info' is a helper for
;;; update-all-external-method-info that handles a single exported class.  It
;;; takes care not to re-parse method bodies any more than necessary, at the
;;; cost of some quadratic behavior.

(defun-void update-external-method-info
    (export-definition export-class options)
  (let* ((all-class-export-information?
	   (visible-class-export-information? export-definition))
	 (export-info-for-this-class?
	   (and all-class-export-information?
		(loop for export-info in all-class-export-information?
		      thereis
		      (and (eq (external-class-name export-info) export-class)
			   export-info)))))
    (cond
      ((null all-class-export-information?)
       (setf (visible-class-export-information? export-definition)
	     (collect-export-info-for-all-classes export-definition)))

      ((null export-info-for-this-class?)
       (setq export-info-for-this-class?
	     (make-export-info-for-one-class export-class options))
       (slot-value-push export-info-for-this-class?
			(visible-class-export-information? export-definition)))

      (t (update-external-static-method-info
	   export-info-for-this-class?
	   export-class
	   options
	   t)
	 (update-external-instance-method-info
	   export-info-for-this-class?
	   export-class
	   options)))))

(defun-void update-external-static-method-info
    (export-info-for-this-class export-class options try-parse-p)
  (let* ((old-static-method-info-list
	   (external-static-methods export-info-for-this-class))
	 (new-static-method-info-list
	   (loop for g2-procedure-name in (cadr (assq 'static-methods options))
		 for g2-procedure?
		     = (get-instance-with-name-if-any
			 'procedure
			 g2-procedure-name)
		 for old-method-info?
		     = (and g2-procedure?
			    (loop for old-method-info
				      in old-static-method-info-list
				  thereis
				  (and (eq (cached-g2-qualified-method-name
					     old-method-info)
					   g2-procedure-name)
				       old-method-info)))
		 when g2-procedure?
		   collect (or old-method-info?
			       (make-external-method-info-for-g2-method
				 export-class
				 g2-procedure?
				 t
				 try-parse-p))
		     using slot-value-cons)))
    (loop for old-method-info in old-static-method-info-list
	  unless (memq old-method-info new-static-method-info-list)
	    do (reclaim-external-method-info old-method-info))
    (reclaim-slot-value-list old-static-method-info-list)
    (setf (external-static-methods export-info-for-this-class)
	  new-static-method-info-list)))

(defun-void update-external-instance-method-info
    (export-info-for-this-class export-class options)
  (cond
    ;; jh, 10/17/97.  Remove after 5.1 ships.
    (bypass-fix-for-exported-method-overloading-p
     (old-update-external-instance-method-info
       export-info-for-this-class
       export-class options))
    (t (new-update-external-instance-method-info
	 export-info-for-this-class
	 export-class options))))

(defun-void old-update-external-instance-method-info
    (export-info-for-this-class export-class options)
  ;; Get rid of non-existent instance methods
  (let* ((old-methods (external-instance-methods export-info-for-this-class))
	 (gleaned-methods
	   (loop for external-method-struct in old-methods
		 if (get-instance-with-name-if-any
		      'method 
		      (cached-g2-qualified-method-name
			external-method-struct))
		   collect external-method-struct
		     using slot-value-cons
		 else (reclaim-external-method-info
			external-method-struct))))
    (reclaim-slot-value-list old-methods)
    (setf (external-instance-methods export-info-for-this-class)
	  gleaned-methods))
  ;; Add new instance methods.
  (let ((old-methods? (external-instance-methods export-info-for-this-class)))
    (multiple-value-bind (cached-instance-info cache-existed-p)
	(decache-implicit-external-instance-method-info-if-any export-class)
      (cond
	(cache-existed-p
	 (reclaim-list-of-external-methods old-methods?)
	 (setf (external-instance-methods export-info-for-this-class)
	       cached-instance-info))
	(old-methods?
	 (setf (cdr (last old-methods?))
	       (maybe-get-more-external-instance-methods-for-class
		 export-info-for-this-class
		 export-class
		 options)))
	(t (setf (external-instance-methods export-info-for-this-class)
		 (maybe-get-more-external-instance-methods-for-class
		   export-info-for-this-class
		   export-class
		   options)))))))

(defun-void new-update-external-instance-method-info
    (export-info-for-this-class export-class options)
  ;; Get rid of non-existent instance methods
  (let* ((old-methods (external-instance-methods export-info-for-this-class))
	 (gleaned-methods
	   (loop for external-method-struct in old-methods
		 if (get-matching-g2-procedure-if-any
		      external-method-struct
		      nil)
		   collect external-method-struct
		     using slot-value-cons
		 else (reclaim-external-method-info
			external-method-struct))))
    (reclaim-slot-value-list old-methods)
    (setf (external-instance-methods export-info-for-this-class)
	  gleaned-methods))
  ;; Add new instance methods.
  (let ((old-methods? (external-instance-methods export-info-for-this-class)))
    (multiple-value-bind (cached-instance-info cache-existed-p)
	(decache-implicit-external-instance-method-info-if-any export-class)
      (cond
	(cache-existed-p
	 (reclaim-list-of-external-methods old-methods?)
	 (setf (external-instance-methods export-info-for-this-class)
	       cached-instance-info))
	(old-methods?
	 (setf (cdr (last old-methods?))
	       (maybe-get-more-external-instance-methods-for-class
		 export-info-for-this-class
		 export-class
		 options)))
	(t (setf (external-instance-methods export-info-for-this-class)
		 (maybe-get-more-external-instance-methods-for-class
		   export-info-for-this-class
		   export-class
		   options)))))))

(defun-simple maybe-get-more-external-instance-methods-for-class
    (export-info-for-this-class export-class options)
  (cond
    ;; jh, 10/17/97.  Remove after 5.1 ships.
    (bypass-fix-for-exported-method-overloading-p
     (old-maybe-get-more-external-instance-methods-for-class
       export-info-for-this-class
       export-class options))
    (t (loop with included-instance-methods?
	       = (cdr (assq 'included-instance-methods options))
	     with excluded-instance-methods?
	       = (cdr (assq 'excluded-instance-methods options))
	     for g2-method being each class-instance of 'method
	     for method-name = (procedure-method-name g2-method)
	     when (and (eq (procedure-method-class g2-method) export-class)
		       (cond
			 (included-instance-methods?
			  (memq method-name included-instance-methods?))
			 (included-instance-methods?
			  (not (memq method-name excluded-instance-methods?)))
			 (t t))
		       (loop for external-method-struct
				 in (external-instance-methods
				      export-info-for-this-class)
			     never
			     (matching-instance-method-info-p
			       external-method-struct
			       g2-method)))
	       collect (make-external-method-info-for-g2-method
			 export-class
			 g2-method
			 nil
			 t)
		 using slot-value-cons))))

(defun-simple old-maybe-get-more-external-instance-methods-for-class
    (export-info-for-this-class export-class options)
  (loop with included-instance-methods?
	  = (cdr (assq 'included-instance-methods options))
        with excluded-instance-methods?
	  = (cdr (assq 'excluded-instance-methods options))
        for g2-method being each class-instance of 'method
	for method-name = (procedure-method-name g2-method)
	when (and (eq (procedure-method-class g2-method) export-class)
		  (cond
		    (included-instance-methods?
		     (memq method-name included-instance-methods?))
		    (included-instance-methods?
		     (not (memq method-name excluded-instance-methods?)))
		    (t t))
		  (loop for external-method-struct
			    in (external-instance-methods
				 export-info-for-this-class)
			never
			(eq (name-or-names-for-frame g2-method)
			    (cached-g2-qualified-method-name
			      external-method-struct))))
	  collect (make-external-method-info-for-g2-method
		    export-class
		    g2-method
		    nil
		    t)
	    using slot-value-cons))

;;;; Adding Export Info to Get-Class-Info

;;; The function `add-class-export-info-attributes' is the hook into
;;; get-class-info that exports non-attribute information about the class that
;;; is being queried.  This information is provided from an instance of
;;; export-definition, whether defined by the user or created internally, and
;;; includes static methods, instance methods, and Java source that corresponds
;;; to the method body, as long as that body was written in the subset of G2
;;; procedure language recognized by the gesture-definition parsing category.

;;; This function assumes that its class-name argument names a valid class.

(defmacro with-push-one-field-available ((push-place) &body body)
  `(macrolet ((push-one-field (field contents)
		`(progn (eval-push ,field ,',push-place)
			(eval-push ,contents ,',push-place))))
     ,@body))

;; jh, 10/17/97.  Remove after 5.1 ships.
(defvar bypass-add-class-export-info-attributes-p nil)
(defun-for-system-procedure g2-add-class-export-info-attributes
    (bypass)
  (setq bypass-add-class-export-info-attributes-p
	(>=f (evaluation-truth-value-value bypass)
	     (truth-threshold inference-engine-parameters)))
  bypass)

(defun-simple add-class-export-info-attributes
    (class-name class-info-attributes)
  (unless bypass-add-class-export-info-attributes-p
    (when (class-description class-name)
      (multiple-value-bind (export-definition? class-info)
	  (get-export-definition-and-info-for-class-if-any class-name)
	(with-push-one-field-available (class-info-attributes)
	  (cond
	    (export-definition?
	     (let ((hand-coded-methods?
		     (get-hand-coded-methods-for-class-if-any
		       export-definition?)))
	       (collecting-exported-method-text
	           (exported-source?
		     (get-exported-source-for-class-if-possible
		       export-definition?
		       class-name
		       hand-coded-methods?))
		 (let ((static-method-info
			 (get-external-static-method-info-for-class
			   class-info))
		       (instance-method-info
			 (get-external-instance-method-info-for-class
			   class-info)))
		   (push-one-field 'static-methods static-method-info)
		   (push-one-field 'instance-methods instance-method-info)
		   (when exported-source?
		     (push-one-field 'exported-source exported-source?))
		   (when hand-coded-methods?
		     (push-one-field
		       'hand-coded-methods hand-coded-methods?))))))
	    ;; jh, 9/29/97.  Could cache the following, but Mike G assures me
	    ;; that get-class-info is most likely called just once on a class
	    ;; that lacks an export-definition.
	    (t (let* ((method-info-list
			(collect-instance-method-export-info
			  class-name
			  nil   ;no export-definition, therefore no options
			  nil)) ;don't parse method bodies
		      (instance-method-info
			(get-evaluation-sequence-from-external-method-info-list
			  method-info-list)))
		 (push-one-field 'instance-methods instance-method-info)
		 (reclaim-list-of-external-methods method-info-list))))))))
  class-info-attributes)

(defun get-export-definition-and-info-for-class-if-any (class-name)
  (multiple-value-bind (export-definition? class-info)
      (get-user-visible-export-definition-and-info-for-class-if-any
	class-name)
    (if export-definition?
	(values export-definition? class-info)
	(multiple-value-bind (export-definition? class-info)
	    (get-implicit-export-definition-and-info-for-class-if-possible
	      class-name)
	  (values export-definition? class-info)))))

(defun-simple get-evaluation-structure-for-one-external-method
    (method-info method-text?)
  (let* ((method-info-attributes nil)
	 (method-name
	   (make-evaluation-symbol
	     (cached-external-method-name method-info)))
	 (static-p (external-method-static-p method-info))
	 (is-static
	   (if static-p
	       (copy-evaluation-truth-value evaluation-true-value)
	       (copy-evaluation-truth-value evaluation-false-value)))
	 (g2-internal-method?
	   (get-matching-g2-procedure-if-any
	     method-info
	     static-p)))
    (cond
      ((null g2-internal-method?)
       #+development
       (cerror "Give up exporting this method"
	 "ADD-CLASS-EXPORT-INFO-ATTRIBUTES: couldn't find method named ~S"
	 (cached-g2-qualified-method-name method-info))
       (reclaim-evaluation-symbol method-name)
       (reclaim-evaluation-truth-value is-static))
      (t (let* ((argument-types
		  (export-types-in-arguments-or-results-as-sequence
		    (argument-list-description g2-internal-method?)))
		(result-types
		  (export-types-in-arguments-or-results-as-sequence
		    (returned-values-description g2-internal-method?)))
		(interface-frame?
		  (when current-system-rpc-icp-socket?
		    (enclosing-interface-frame?
		      current-system-rpc-icp-socket?)))		  
		(include-method-text-p
		  (and (framep interface-frame?)
		       (frame-has-not-been-reprocessed-p
			 interface-frame?
			 (enclosing-interface-frame-serial-number current-system-rpc-icp-socket?))
		       (include-method-text-in-class-export
			 interface-frame?))))
	   (with-push-one-field-available (method-info-attributes)
	     (push-one-field  'method-name method-name)
	     (push-one-field  'is-static is-static)
	     (push-one-field  'argument-types argument-types)
	     (push-one-field  'result-types result-types)
	     (when include-method-text-p
	       (push-one-field  'g2-method-text (get-text-of-attribute
						  g2-internal-method?
						  'text
						  (class g2-internal-method?))))
	     (when method-text?
	       (push-one-field 'method-source method-text?))))))
    (allocate-evaluation-structure (nreverse method-info-attributes))))

(defun-simple export-types-in-arguments-or-results-as-sequence
    (arguments-or-results)
  (let* ((gensym-list-of-types
	  (collect-types-into-list-using-gensym-conses arguments-or-results))
	 (eval-list-of-java-types
	   (loop for type in gensym-list-of-types
		 collect
		 (case type
		   ((truth-value integer float symbol text)
		    (copy-evaluation-symbol type))
		   (number (copy-evaluation-symbol 'quantity))
		   (datum (copy-evaluation-symbol 'value))
		   (item-or-datum (copy-evaluation-symbol 'item-or-value))
		   (otherwise
		    (cond
		      ((consp type)
		       (let ((tag (car type)))
			 (case tag
			   ((sequence structure)
			    (copy-evaluation-symbol tag))
			   (class
			    (allocate-evaluation-structure
			      (eval-list
				'class
				(copy-evaluation-symbol (cadr type)))))
			   (otherwise
			    (cerror "use ITEM-OR-VALUE"
				    "ADD-CLASS-EXPORT-INFO-ATTRIBUTES: ~
                                     unknown compound type ~S"
				    type)
			    (copy-evaluation-symbol 'item-or-value)))))
		      (t (cerror "use ITEM-OR-VALUE"
				 "ADD-CLASS-EXPORT-INFO-ATTRIBUTES: ~
                                  refractory type spec ~S"
				 type)
			 (copy-evaluation-symbol 'item-or-value)))))
		 using eval-cons)))
    (reclaim-gensym-list gensym-list-of-types)
    (allocate-evaluation-sequence eval-list-of-java-types)))

(defun-simple get-external-static-method-info-for-class (class-info)
  (let ((eval-list-of-sequence-elements
	  (loop for method-info in (external-static-methods class-info)
		for method-text?
		    = (slot-value-pop list-of-exported-method-texts)
		collect
		(get-evaluation-structure-for-one-external-method
		  method-info
		  method-text?)
		using eval-cons)))
    (allocate-evaluation-sequence (nreverse eval-list-of-sequence-elements))))

(defun-simple get-external-instance-method-info-for-class (class-info)
  (get-evaluation-sequence-from-external-method-info-list
    (external-instance-methods class-info)))

(defun-simple get-evaluation-sequence-from-external-method-info-list
    (method-info-list)
  (let ((eval-list-of-sequence-elements
	  (loop for method-info in method-info-list
		for method-text?
		    = (slot-value-pop list-of-exported-method-texts)
		collect
		(get-evaluation-structure-for-one-external-method
		  method-info
		  method-text?)
		using eval-cons)))
    (allocate-evaluation-sequence (nreverse eval-list-of-sequence-elements))))

(defun-simple get-exported-static-methods-if-any
    (export-definition class-name)
  (let*-while-true
      ((class-info?
	 (loop for class-info
		   in (visible-class-export-information? export-definition)
	       thereis
	       (and (eq (external-class-name class-info) class-name)
		    class-info)))
       (extant-static-methods-list
	 (loop for method-info in (external-static-methods class-info?)
	       unless (instance-method-frame-note? method-info)
		 collect (instance-method-frame? method-info)
		   using slot-value-cons)))
    extant-static-methods-list))

(defun-simple get-external-class-specific-methods (class-name)
  (block got-methods
    (loop for export-definition
	      being each class-instance of 'export-definition
	  do
      (loop for class-info
		in (visible-class-export-information? export-definition)
	    do
	(when (eq (external-class-name class-info) class-name)
	  (return-from got-methods
	    (loop for method-info
		      in (external-instance-methods class-info)
		  collect (instance-method-frame? method-info)
		    using gensym-cons)))))
    nil))

(defun-allowing-unwind get-exported-source-for-class-if-possible
    (export-definition class-name additional-methods?)
  (let* ((class-export-specs
	   (export-definition-class-specs
	     (export-definition-specification export-definition)))
	 (class-export-tree
	   (loop for (export-class) in class-export-specs
		 for class-export-spec in class-export-specs
		 thereis
		 (and (eq export-class class-name)
		      class-export-spec))))
    (gensym-dstruct-bind ((class-name nil options) class-export-tree)
      (cond
	((class-description class-name) ;defensive
	 (let ((extant-static-methods-list
		 (get-exported-static-methods-if-any
		   export-definition
		   class-name))
	       (imports? (cadr (assq 'imports options)))
	       (package? (cadr (assq 'package options)))
	       (superior-class-override?
		 (cadr (assq 'superior-class-override options)))
	       error-string? valid-string?)
	   (collecting-frame-notes-for-export-definition
	       (export-definition class-name)
	     (multiple-value-setq (valid-string? error-string?)
	       (jwith-output-to-text-string (text-string-stream)
		 (jemit-class-to-stream
		   class-name
		   extant-static-methods-list
		   package?
		   imports?
		   nil ;ignore class-path?
		   nil ;ignore unzipped-directory
		   superior-class-override?
		   additional-methods?
		   text-string-stream)))
	     error-string?)
	   (reclaim-slot-value-list extant-static-methods-list)
	   valid-string?))
	(t nil)))))

(defun-void update-mapping-problem-frame-notes-if-necessary
    (export-definition class-name error-string?)
  ;; Don't erase mapping-problem notes for other classes, only the one we are
  ;; reviewing in the following cond form.
  (clear-problem-mapping-g2-to-java-source-particulars
    export-definition
    class-name)
  (when (or error-string? collected-frame-notes-for-class-export?)
    (nreversef collected-frame-notes-for-class-export?)
    (add-to-frame-note-particulars-list-if-necessary
      (managed-backquote slot-value-cons
	( \,class-name
	  \,@(if error-string?
		 (slot-value-list error-string?)
		 nil)
	  \,@collected-frame-notes-for-class-export?))
      'problem-mapping-g2-to-java-source
      export-definition)))

(defun-void clear-problem-mapping-g2-to-java-source-particulars
    (export-definition class-name)
  (let ((particulars
	  (get-particulars-of-frame-note-if-any
	    'problem-mapping-g2-to-java-source
	    export-definition)))
    (loop for (flawed-class) in particulars
	  for particular in particulars
	  do
      (when (eq class-name flawed-class)
	(delete-from-frame-note-particulars-list
	  particular
	  'problem-mapping-g2-to-java-source
	  export-definition)
	(loop-finish)))))

(def-frame-note-writer problem-mapping-g2-to-java-source (particulars)
  (let ((enumerate-p
	  (or (cdr particulars)        ;more than one flawed class or
	      (cddr (car particulars)) ; more than one flaw
	      )))
    (loop for (flawed-class . flaws-in-class) in particulars
	  for particulars-cons on particulars
	  with index = 0
	  do
      (loop for flaw-in-class in flaws-in-class
	    for flaw-in-class-cons on flaws-in-class
	    do
	(when enumerate-p
	  (tformat "(~A) " (+f index frame-note-index)))
	(tformat
	  "a problem was encountered mapping the G2 class ~A to Java: ~A"
	  flawed-class
	  flaw-in-class)
	(incff index)
	(when enumerate-p
	  (when (or (cdr particulars-cons) (cdr flaw-in-class-cons))
	    (twrite-string ";")
	    (twrite-line-separator)))
	    finally (setq frame-note-index-skip (1-f index))))))

(defun-simple get-hand-coded-methods-for-class-if-any (export-definition)
  (let ((translation-and-text?
	  (get-slot-value-if-any export-definition 'additional-java-methods)))
    (and translation-and-text?
	 (not (eq (car translation-and-text?) 'none))
	 (convert-text-to-text-string (cdr translation-and-text?)))))

(defun get-user-visible-export-definition-and-info-for-class-if-any
    (class-name)
  (loop for export-definition being each class-instance of 'export-definition
	do
    (let ((class-info?
	    (loop for class-info
		      in (visible-class-export-information? export-definition)
		  thereis
		  (and (eq (external-class-name class-info) class-name)
		       class-info))))
      (when class-info?
	(return (values export-definition class-info?))))
    finally (return (values nil nil))))

(defun decache-implicit-external-instance-method-info-if-any (class-name)
  (let* ((description? (class-description class-name))
	 (export-definition?
	   (and description?
		(implicit-class-export-information? description?))))
    (cond
      (export-definition?
       (let* ((external-class-info
		(slot-value-pop
		  (visible-class-export-information? export-definition?)))
	      (external-instance-method-info
		(external-instance-methods external-class-info)))
	 (setf (external-instance-methods external-class-info) nil)
	 (reclaim-external-class-info external-class-info)
	 (setf (visible-class-export-information? export-definition?) nil)
	 (delete-frame export-definition?)
	 (setf (implicit-class-export-information? description?) nil)
	 (values external-instance-method-info t)))
      (t (values nil nil)))))

(defparameter cache-implicit-class-export-info-p nil)

(defun get-implicit-export-definition-and-info-for-class-if-possible
    (class-name)
  (if cache-implicit-class-export-info-p
      (let* ((description? (class-description class-name))
	     (export-definition?
	       (and description?
		    (implicit-class-export-information? description?))))
	(cond
	  (export-definition?
	   (values
	     export-definition?
	     (car (visible-class-export-information? export-definition?))))
	  (t (make-implicit-export-definition-and-class-info class-name))))
      (values nil nil)))

(defun make-implicit-export-definition-and-class-info (class-name)
  (let* ((export-definition (make-frame 'export-definition))
	 (description? (class-description class-name))
	 (external-method-info
	   (collect-instance-method-export-info class-name nil))
	 (class-info
	   (make-external-class-info class-name nil external-method-info)))

    ;; Fake a tree structure for the export-definition-specification attribute
    ;; that matches class-info, since no user has created an export-definition
    ;; for this class.
    (setf (export-definition-specification export-definition)
	  (managed-backquote slot-value-cons
	    (java nil (( \,class-name)))))

    (cond
      (description? ;defensive
       (setf (implicit-class-export-information? description?)
	     (slot-value-list class-info)))
      #+development
      (t (cerror "Leak an export-definition-frame and proceed"
	   "ADD-CLASS-EXPORT-INFO-ATTRIBUTES: couldn't find class named ~S"
	   class-name)))
    (values export-definition class-info)))

;;;; Syntax-Tree Template Registry

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter syntax-tree-template-registry nil)

(defmacro make-syntax-tree-template-registry-entry ()
  `(make-list 6))

(defmacro syntax-tree-template-name (registry-entry)
  `(first ,registry-entry))

(defmacro syntax-tree-template-category (registry-entry)
  `(second ,registry-entry))

(defmacro syntax-tree-template-dynamic-spec-names (registry-entry)
  `(third ,registry-entry))

(defmacro syntax-tree-template-expandable-bindings (registry-entry)
  `(fourth ,registry-entry))

(defmacro syntax-tree-template-packages-used (registry-entry)
  `(fifth ,registry-entry))

(defmacro syntax-tree-template-tokenized-lines (registry-entry)
  `(sixth ,registry-entry))

(defun push-new-syntax-tree-template-entry (name new-entry)
  (cond
    ((null syntax-tree-template-registry)
     (setq syntax-tree-template-registry (list new-entry)))
    ((eq name
	 (syntax-tree-template-name (first syntax-tree-template-registry)))
     (pop syntax-tree-template-registry)
     (push new-entry syntax-tree-template-registry))
    (t (let ((extant-entry?
	       (assoc name syntax-tree-template-registry)))
	 (if extant-entry?
	     (setf (cdr extant-entry?) (cdr new-entry))
	     (push new-entry syntax-tree-template-registry))))))
)

;;;; Defining Syntax-Tree Templates

;;; The macro `def-syntax-tree-template' uses the following syntax for binding
;;; specs.

;;;   binding spec      meaning
;;;   ------------      -------
;;;   <xxx>             insert specific string to which <xxx> is bound
;;;   <xxx>...          replicate lines, successively inserting each string from list
;;;   <<xxx>...>...     in each replicated line, comma-delimit each string from sublist
;;;   [xxx]             if [xxx] is nil don't emit & splice out previous matching literal
;;;   [xxx]...          replicated lines, don't emit a line if [xxx] is bound to nil
;;;   [~xxx]            emit instead of [xxx] if [xxx] is bound to nil
;;;   (xxx aaa.bbb.xxx) add package aaa.bbb to import list if xxx is seen

;;; The following patterns are used in the code template:
;;;   pattern           meaning
;;;   -------           -------
;;;   <xxx>             as above
;;;   [xxx]             as above
;;;   [~xxx]            as above
;;;   ...               replicate this line
;;;   <xxx>,...         insert a comma series
;;;   ^xxx^             embed subsidiary (maybe multi-line) template named xxx
;;;   ^xxx^...          repeatedly embed subsidiary (maybe multi-line) template named xxx
;;;   <i>               insert integers counting up from 0 in each replicated line
;;;   Java word         insert as is
;;;   any other word    package qualifiers from declaration added to import list
;;;   -anything else-   insert in source code as is

(defmacro def-syntax-tree-template
    (name (category &rest binding-specs) template-string)
  (let ((dynamic-spec-names
	  (get-syntax-tree-template-dynamic-spec-names binding-specs))
	(tokenized-template-lines
	  (tokenize-syntax-tree-template name template-string))
	(expandable-bindings
	  (get-syntax-tree-template-expandable-specs binding-specs)))
    (check-for-unbound-variables-in-def-syntax-template
      dynamic-spec-names
      tokenized-template-lines)
    (let ((registry-entry (make-syntax-tree-template-registry-entry)))
      (setf (syntax-tree-template-name registry-entry) name)
      (setf (syntax-tree-template-category registry-entry) category)
      (setf (syntax-tree-template-dynamic-spec-names registry-entry)
	    dynamic-spec-names)
      (setf (syntax-tree-template-expandable-bindings registry-entry)
	    expandable-bindings)
      (setf (syntax-tree-template-packages-used registry-entry)
	    (get-syntax-tree-template-packages-used
	      tokenized-template-lines
	      expandable-bindings))
      (setf (syntax-tree-template-tokenized-lines registry-entry)
	    tokenized-template-lines)
      `(eval-when (:compile-toplevel :load-toplevel :execute)
	 (push-new-syntax-tree-template-entry ',name ',registry-entry)
	 ',name))))

(defun-for-macro get-syntax-tree-template-dynamic-spec-names
    (binding-specs)
  (loop for binding-spec in binding-specs
	when (symbolp binding-spec)
	  collect binding-spec))

(defun-for-macro get-syntax-tree-template-expandable-specs
    (binding-specs)
  (loop for binding-spec in binding-specs
	when (consp binding-spec)
	  collect binding-spec))

(defun-for-macro get-syntax-tree-template-packages-used
    (tokenized-template-lines expandable-bindings)
  (loop for (nil ;sugar
	      nil ;subtree-to-insert?
	      nil ;skip-line-unless-true?)
	      nil ;optional-alternative-line-p
	      nil ;replicate-lines-p
	      nil ;needs-index-binding-p
	      nil ;entirely-whitespace-p
	      . tokens-in-line)
	    in tokenized-template-lines
	with bindings-used = nil
	do
    (loop for (type key) in tokens-in-line
	  for binding? = (and (eq type 'expandable)
			      (cadr (assoc key expandable-bindings)))
	    do
      (when binding?
	(let ((symbol-name (symbol-name binding?)))
	  (pushnew (subseq
		     symbol-name
		     0 
		     (position #\. symbol-name :from-end t))
		   bindings-used
		   :test #'equal))))
	finally (return bindings-used)))

;;;; Internal Format of Syntax-Template Binding Spec

(defun-for-macro get-internal-spec-for-simple-syntax-tree-binding?
    (external-binding-spec value-form)
  (and (symbolp external-binding-spec)
       (let* ((symbol-name (symbol-name external-binding-spec)))
	 (and (eql (char symbol-name 0) #\<)
	      (let* ((symbol-length (length symbol-name))
		     (last-index (1- symbol-length)))
		(and (eql (char symbol-name last-index) #\>)
		     (let ((root (intern (string-downcase symbol-name))))
		       `(,root simple \, ,value-form))))))))

(defun-for-macro get-internal-spec-for-list-syntax-tree-binding?
    (external-binding-spec value-form)
  (and (symbolp external-binding-spec)
       (let* ((symbol-name (symbol-name external-binding-spec)))
	 (and (eql (char symbol-name 0) #\<)
	      (not (eql (char symbol-name 1) #\<))
	      (let ((reversed-symbol (reverse symbol-name)))
		(and (search #.(reverse ">...") reversed-symbol :end2 4)
		     (let* ((symbol-length (length symbol-name))
			    (root
			      (intern
				(string-downcase
				  (subseq symbol-name
				    0
				    (- symbol-length 3))))))
		       `(,root list \, ,value-form))))))))

(defun-for-macro get-internal-spec-for-list-of-lists-syntax-tree-binding?
    (external-binding-spec value-form)
  (and (symbolp external-binding-spec)
       (let* ((symbol-name (symbol-name external-binding-spec)))
	 (and (eql (char symbol-name 0) #\<)
	      (eql (char symbol-name 1) #\<)
	      (let* ((symbol-length (length symbol-name))
		     (reversed-symbol (reverse symbol-name)))
		(and (search #.(reverse ">...>...") reversed-symbol :end2 8)
		     (let ((root
			     (intern
			       (string-downcase
				 (subseq symbol-name 1 (- symbol-length 7))))))
		       `(,root list-of-lists \, ,value-form))))))))

(defun-for-macro get-internal-spec-for-optional-syntax-tree-binding?
    (external-binding-spec value-form)
  (and (symbolp external-binding-spec)
       (let* ((symbol-name (symbol-name external-binding-spec)))
	 (and (eql (char symbol-name 0) #\[)
	      (let* ((symbol-length (length symbol-name))
		     (last-index (1- symbol-length)))
		(and (eql (char symbol-name last-index) #\])
		     (let ((root (intern (string-downcase symbol-name))))
		       `(,root optional \, ,value-form))))))))

(defun-for-macro get-internal-spec-for-optional-alternative-binding?
    (external-binding-spec value-form)
  (and (symbolp external-binding-spec)
       (let* ((symbol-name (symbol-name external-binding-spec)))
	 (and (eql (char symbol-name 0) #\[)
	      (eql (char symbol-name 1) #\~)
	      (let* ((symbol-length (length symbol-name))
		     (last-index (1- symbol-length)))
		(and (eql (char symbol-name last-index) #\])
		     (let ((root (intern (string-downcase symbol-name))))
		       `(,root optional-alternative \, ,value-form))))))))

(defun-for-macro get-internal-spec-for-alternatives-list-syntax-tree-binding?
    (external-binding-spec value-form)
  (and (symbolp external-binding-spec)
       (let* ((symbol-name (symbol-name external-binding-spec)))
	 (and (eql (char symbol-name 0) #\[)
	      (eql (char symbol-name 1) #\~)
	      (let ((reversed-symbol (reverse symbol-name)))
		(and (search #.(reverse "]...") reversed-symbol :end2 4)
		     (let* ((symbol-length (length symbol-name))
			    (root
			      (intern
				(string-downcase
				  (subseq symbol-name
				    0
				    (- symbol-length 3))))))
		       `(,root alternatives-list \, ,value-form))))))))

(defun-for-macro get-internal-spec-for-optionals-list-syntax-tree-binding?
    (external-binding-spec value-form)
  (and (symbolp external-binding-spec)
       (let* ((symbol-name (symbol-name external-binding-spec)))
	 (and (eql (char symbol-name 0) #\[)
	      (let ((reversed-symbol (reverse symbol-name)))
		(and (search #.(reverse "]...") reversed-symbol :end2 4)
		     (let* ((symbol-length (length symbol-name))
			    (root
			      (intern
				(string-downcase
				  (subseq symbol-name
				    0
				    (- symbol-length 3))))))
		       `(,root optionals-list \, ,value-form))))))))

(defun-for-macro get-internal-binding-from-dynamic-syntax-spec
    (dynamic-spec-name &optional value-form)
  (or (get-internal-spec-for-simple-syntax-tree-binding?
	dynamic-spec-name
	value-form)
      (get-internal-spec-for-list-syntax-tree-binding?
	dynamic-spec-name
	value-form)
      (get-internal-spec-for-list-of-lists-syntax-tree-binding?
	dynamic-spec-name
	value-form)
      (get-internal-spec-for-optional-syntax-tree-binding?
	dynamic-spec-name
	value-form)
      (get-internal-spec-for-optional-alternative-binding?
	dynamic-spec-name
	value-form)
      (get-internal-spec-for-alternatives-list-syntax-tree-binding?
	dynamic-spec-name
	value-form)
      (get-internal-spec-for-optionals-list-syntax-tree-binding?
	dynamic-spec-name
	value-form)))

(defun-for-macro get-root-names-from-dynamic-syntax-spec
    (dynamic-spec-names)
  (loop for dynamic-spec-name in dynamic-spec-names
	collect
	(car
	  (get-internal-binding-from-dynamic-syntax-spec
	    dynamic-spec-name
	    nil))))

;;;; Representing Each Line in a Syntax-Template


(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro syntax-tree-line-insert-subtree? (tokenized-line)
  `(second ,tokenized-line))

(defmacro syntax-tree-line-splice-out-unless-true? (tokenized-line)
  `(third ,tokenized-line))

(defmacro syntax-tree-line-optional-alternative-line-p (tokenized-line)
  `(fourth ,tokenized-line))

(defmacro syntax-tree-line-replicate-lines-p (tokenized-line)
  `(fifth ,tokenized-line))

(defmacro syntax-tree-line-needs-index-binding-p (tokenized-line)
  `(sixth ,tokenized-line))

(defmacro syntax-tree-line-entirely-whitespace-p (tokenized-line)
  `(seventh ,tokenized-line))

(defmacro syntax-tree-line-tokens-in-line (tokenized-line)
  `(nthcdr 7 ,tokenized-line))
)

;;;; Compile-time Checking of Syntax-Template Definitions

;;; Note that `check-for-unbound-variables-in-def-syntax-template' only checks
;;; for discrepancies between the declared bindings and the bindings used in the
;;; syntax template string.  There also need to be a check in
;;; expand-syntax-tree-template that all declared bindings are provided,
;;; including those bindings declared in nested templates (for further details
;;; on the latter, grep around insert-subtree).

(defun-for-macro check-for-unbound-variables-in-def-syntax-template
    (dynamic-spec-names tokenized-template-lines)
  (let* ((should-be-bound
	   (loop for line-info in tokenized-template-lines
		 for tokenized-template-line
		     = (syntax-tree-line-tokens-in-line line-info)
		 append
	     (loop for (token-type root-for-lookup) in tokenized-template-line
		   when (member token-type '(substitute
					     midst-of-comma-series
					     last-of-comma-series
					     splice-out-unless-true
					     skip-line-unless-true
					     optional-alternative))
		     collect root-for-lookup)))
	 (are-bound
	   (get-root-names-from-dynamic-syntax-spec dynamic-spec-names))
	 (unbound?
	   (set-difference should-be-bound (cons '|<i>| are-bound))))
    (when unbound?
      (error "DEF-SYNTAX-TREE-TEMPLATE: unbound variables: ~S" unbound?))))

;;;; Forming Individual Tokens from a Syntax-Template

(defparameter-for-macro known-literals-in-syntax-tree-template
  (append java-reserved-words-as-string
	  java-reserved-expressions-as-string
	  java-separators-as-string
	  java-operators-as-string))

(defun-for-macro make-token-from-syntax-tree-template (token tokens-so-far)
  (let* ((reversed-token (reverse token))
	 (token-length (length token))
	 (pushback-token nil)
	 (pushback-char nil)
	 (possible-pattern-token?
	   (case (char token 0)
	     (#\<
	      (cond
		((and (>= token-length 5)
		      (search #.(reverse ">,...") reversed-token :end2 5))
		 (loop for (type ptoken) in tokens-so-far
		       for previous-token in tokens-so-far
		       for substitute-p = (eq type 'substitute)
		       while (or substitute-p
				 (and (eq type 'literal)
				      (equal (string-trim ptoken " ") "")))
		       do
		   (when substitute-p
		     (setf (car previous-token) 'midst-of-comma-series)))
		 `(last-of-comma-series ,(subseq token 0 (- token-length 4))))
		((eql (char reversed-token 0) #\>)
		 `(substitute ,token))
		((and (>= token-length 2) (eql (char reversed-token 1) #\>))
		 (setq pushback-char (char reversed-token 0))
		 `(substitute ,(subseq token 0 (1- token-length))))
		(t nil)))
	     (#\^
	      (cond
		((and (>= token-length 4)
		      (search #.(reverse "^...") reversed-token :end2 4))
		 (setq pushback-token '(replicate-in-lines))
		 `(insert-subtree
		    ,(string-upcase (subseq token 1 (- token-length 4)))))
		((and (>= token-length 2) (eql (char reversed-token 0) #\^))
		 `(insert-subtree
		    ,(string-upcase (subseq token 1 (- token-length 2)))))
		(t nil)))
	     (#\[
	      (cond
		((eql (char reversed-token 0) #\])
		 (cond
		   ((and (>= token-length 2) (eql (char token 1) #\~))
		    `(optional-alternative ,token))
		   ((or (= token-length 2) (eql (char token 1) #\Space))
		    `(literal ,token))
		   (t `(skip-line-unless-true ,token))))
		(t nil)))
	     (otherwise nil)))
	 (token-to-return
	   (cond
	     (possible-pattern-token?)
	     ((equal token "...") `(replicate-in-lines))
	     ((member token known-literals-in-syntax-tree-template
		      :test #'equal)
	      `(literal ,token))
	     ((eql (char reversed-token 0) #\,)
	      (setq pushback-char #\,)
	      `(expandable ,(subseq token 0 (1- token-length))))
	     (t `(expandable ,token)))))
    (unless (equal token-to-return '(replicate-in-lines))
      (when (or (every #'(lambda (x) (or (digit-char-p x) (eql x #\.)))
		       (cadr token-to-return))
		(and (eq (car token-to-return) 'expandable)
		     (find #\. (cadr token-to-return))))
	(setf (car token-to-return) 'literal)))
    (unless (member (car token-to-return) '(literal replicate-in-lines))
      (setf (cadr token-to-return) (intern (cadr token-to-return))))
    (values token-to-return pushback-token pushback-char)))

;;;; Tokenizing Each Line in a Syntax-Template

;;; The result of the compile-time function `scan-syntax-tree-template-line' is
;;; a list of tokens.  Each token is a lists of two elements.  The first is a
;;; tag indicating the sort of token.  The cdr is the binding or bindings, to be
;;; destructively modified as the output string is built.  Here is a list of
;;; tags:

;;;   token tag              meaning
;;;   ---------              -------
;;;   literal                insert in source code as is
;;;   expandable             add package qualifiers from external alist
;;;   substitute             plug in info from specific exported G2 class
;;;   midst-of-comma-series  binding is a list, pop and use within commas
;;;   last-of-comma-series   binding is a list, pop and terminate with comma
;;;   replicate-in-lines     other bindings are lists, repeat line for each element
;;    insert-subtree         embed a subsidiary template
;;;   skip-line-unless-true  optional pattern: don't emit line if binding is nil
;;;   optional-alternative   use if preceeding line skipped by skip-line-unless-true
;;;   splice-out-unless-true optional pattern: insert in comma series if non-nil,
;;;                          don't emit literal matching var name if nil
;;;                            (e.g. "throws")
;;;   splicable-literal      remove previous literal matching
;;;                            non-nil splice-out-unless-true var

;;; A loose description of the tokenizing algorithm:
;;;
;;;   collection mode         initiated by             terminated by
;;;   ---------------         ------------             -------------
;;;   substitute pattern var  <                        > or >,...
;;    insert-subtree var      ^                        ^ or ^...
;;;   optional pattern var    [                        ] or ]...
;;;   literal                 Space Tab Newline ( ) ;  -anything else-
;;;   within string           "                        "
;;;   expandable pattern var  -any non-pattern char-   Space Tab Newline ( ) ;
;;;
;;; Additionally, literals are concatenated with known Java keywords,
;;; separators, and operators.  Strings may contain substitute or optional
;;; patterns (i.e., <xxx> [xxx] sequences).

(defun-for-macro scan-syntax-tree-template-line (template-line)
  (flet ((collect-token (these-chars)
	   (let* ((string-length (length these-chars))
		  (token-string (make-string string-length)))
	     (loop for index from (1- string-length) downto 0
		   do
	       (setf (char token-string index) (pop these-chars)))
	     token-string)))
    (macrolet
	((token-push (token-form)
	   (avoiding-variable-capture
	       (&aux token literal-pushback-char?)
	     `(multiple-value-bind
		  (,token pushback-token? ,literal-pushback-char?)
		  ,token-form
		(cond
		  ((and (eq (car ,token) 'literal)
			(eq (caar these-tokens) 'literal))
		   (setf (car these-tokens)
			 `(literal ,(concatenate
				      'string
				      (cadar these-tokens)
				      (cadr ,token)))))
		  (t (push ,token these-tokens)))
		(when pushback-token?
		  (push pushback-token? these-tokens))
		(when ,literal-pushback-char?
		  (push ,literal-pushback-char? known-literal-chars?)))))
	 (tokenize-collected-chars ()
	   `(progn
	      (cond
		(known-literal-chars?
		 (token-push `(literal ,(collect-token known-literal-chars?)))
		 (setq known-literal-chars? nil))
		(known-pattern-chars?
		 (token-push
		   (make-token-from-syntax-tree-template
		     (collect-token known-pattern-chars?)
		     these-tokens))
		 (setq known-pattern-chars? nil)))
	      (setq collecting-optional-token-p nil))))
      (loop for index from 0 below (length template-line)
	    for this-char = (char template-line index)
	    for double-quote-p = (eql this-char #\")
	    for known-literal-char-p
		= (or (member this-char
			      '(#\Space #\Tab #\Newline #\( #\) #\{ #\} #\;))
		      (if collecting-optional-token-p
			  nil
			  (eql this-char #\])))
	    for beginning-pattern-char-p = (member this-char '(#\< #\[))
	    with known-pattern-chars? = nil
	    with known-literal-chars? = nil
	    with these-tokens = nil
	    with inside-string-p = nil
	    with collecting-optional-token-p = nil
	    with resume-inside-string-after-pattern-p = nil
	    do
	(cond
	  ;; If we encounter a double-quote, enter or exit "inside string" mode.
	  (double-quote-p
	   (when resume-inside-string-after-pattern-p
	     (setq inside-string-p t)
	     (setq resume-inside-string-after-pattern-p nil))
	   (when inside-string-p
	     (tokenize-collected-chars))
	   (push this-char known-literal-chars?)
	   (setq inside-string-p (not inside-string-p))
	   (unless inside-string-p 
	     (token-push `(literal ,(collect-token known-literal-chars?)))
	     (setq known-literal-chars? nil)))
	  ;; If we know we are starting a "substitute" pattern variable, make a
	  ;; token out of the previously collected chars.  Record if we were in
	  ;; the midst of "inside string" mode so we can resume this mode
	  ;; afterwards.
	  (beginning-pattern-char-p
	   (tokenize-collected-chars)
	   (when inside-string-p
	     (setq resume-inside-string-after-pattern-p t)
	     (setq inside-string-p nil))
	   (when (eql this-char #\[)
	     (setq collecting-optional-token-p t))
	   (push this-char known-pattern-chars?))
	  ;; If we are in "inside string" mode and haven't encountered a pattern
	  ;; variable, the character is always literal.
	  (inside-string-p
	   (push this-char known-literal-chars?))
	  ;; If we were collecting a pattern variable and we encounter a known
	  ;; literal chararcter, make a token for the variable we were
	  ;; collecting and store the new character as the beginning of a
	  ;; sequence of literals.
	  ((and known-literal-char-p known-pattern-chars?)
	   (tokenize-collected-chars)
	   (when resume-inside-string-after-pattern-p
	     (setq inside-string-p t)
	     (setq resume-inside-string-after-pattern-p nil))
	   ;; Token-push may have placed a character in known-literal-chars?, so
	   ;; we push, instead of setq'ing to a list of one.
	   (push this-char known-literal-chars?))
	  ;; If we were not collecting a pattern variable and we encounter a
	  ;; known literal character, store it.
	  (known-literal-char-p
	   (push this-char known-literal-chars?))
	  ;; If we have collected some literal characters and the current
	  ;; character is not known to be literal, make a token from the
	  ;; collected characters and store the current character as the
	  ;; beginning of a pattern variable.
	  (known-literal-chars?
	   (token-push `(literal ,(collect-token known-literal-chars?)))
	   (setq known-literal-chars? nil)
	   (setq known-pattern-chars? (list this-char)))
	  ;; At this point, we are sure the current character is part of a
	  ;; pattern variable (either substitute, optional, or expandable),
	  ;; subject to post-processing in make-token-from-syntax-tree-template
	  ;; that turns Java reserved words (which initially look like
	  ;; expandable variables) into sequences of literals.
	  (t (push this-char known-pattern-chars?)))
      finally
      (tokenize-collected-chars)
      (when (member 'replicate-in-lines these-tokens :key #'car)
	;; following form may side-effect local variable "these-tokens".
	(preprocess-splicable-syntax-tree-lines these-tokens))
      (return (reverse these-tokens))))))

(defun-for-macro preprocess-splicable-syntax-tree-lines (these-tokens)
  (loop with token-cons? = these-tokens
	while token-cons?
	for token = (car token-cons?)
	do
    (cond
      ((eq (car token) 'skip-line-unless-true)
       (setf (car token) 'splice-out-unless-true)
       (let ((previous-token (cadr token-cons?)))
	 (when (eq (car previous-token) 'literal)
	   (let* ((var-name (symbol-name (cadr token)))
		  (splicable-end (1- (length var-name)))
		  (splicing-string (subseq var-name 1 splicable-end))
		  (splicable-string (cadr previous-token))
		  (search-index? (search splicing-string splicable-string)))
	     (when search-index?
	       (let* ((splice-index
		       (loop for index downfrom (1- search-index?) to 0
			     do
			 (unless (eql (char splicable-string index) #\Space)
			   (return (1+ index)))
			     finally (return 0)))
		      (before (subseq splicable-string 0 splice-index))
		      (retain-index (+ search-index? (1- splicable-end)))
		      (during
			(subseq splicable-string splice-index retain-index))
		      (after (subseq splicable-string retain-index))
		      (tokens-to-insert
			(append
			  (if (equal after "")
			      nil
			      `((literal ,after)))
			  `((splicable-literal ,during))
			  (if (equal before "")
			      nil
			      `((literal ,before)))))
		      (new-cdr (cddr token-cons?)))
		 (setf (cdr token-cons?) tokens-to-insert)
		 (setf (cdr (last tokens-to-insert)) new-cdr)
		 (setq token-cons? new-cdr)))))))
      (t (setq token-cons? (cdr token-cons?))))))

;;;; Testing the Syntax-Template Tokenizer

#+development
(defparameter test-suite-for-scan-syntax-tree-template-line
  '(
    ;; Vanilla test.
    ("interface <interface> extends Remote {"
     ((LITERAL "interface ")
      (SUBSTITUTE |<interface>|)
      (LITERAL " extends ")
      (EXPANDABLE |Remote|)
      (LITERAL " {")))

    ;; Should distinguish expandables from literals correctly.
    ("public class <class> extends G2RMIready implements <interface> {"
     ((LITERAL "public class ")
      (SUBSTITUTE |<class>|)
      (LITERAL " extends ")
      (EXPANDABLE |G2RMIready|)
      (LITERAL " implements ")
      (SUBSTITUTE |<interface>|)
      (LITERAL " {")))

    ;; Comma series should tokenize correctly.
    ("<result-type> <method>(<arg-type> <arg-name>,...) throws [throws]; ..."
     ((SUBSTITUTE |<result-type>|)
      (LITERAL " ")
      (SUBSTITUTE |<method>|)
      (LITERAL "(")
      (MIDST-OF-COMMA-SERIES |<arg-type>|)
      (LITERAL " ")
      (LAST-OF-COMMA-SERIES |<arg-name>|)
      (LITERAL ")")
      (SPLICABLE-LITERAL " throws")
      (LITERAL " ")
      (SPLICE-OUT-UNLESS-TRUE |[throws]|)
      (LITERAL "; ")
      (REPLICATE-IN-LINES)))

     ;; Optional alternative should tokenize correctly.
     ("       return [~throws];"
      ((LITERAL "       return ")
       (OPTIONAL-ALTERNATIVE |[~throws]|)
       (LITERAL ";")))

    ;; Contents of double-quote should be literal, except for pattern vars.
    ("       throw new [throws](\"no connection to G2 - run <init-name>\");"
     ((LITERAL "       throw new ")
      (SKIP-LINE-UNLESS-TRUE |[throws]|)
      (LITERAL "(\"no connection to G2 - run ")
      (SUBSTITUTE |<init-name>|)
      (LITERAL "\");")))

    ;; Need to differentiate pattern vars array contents from optional markers.
    ("myArgArray[<i>] = (<rpc-arg-type>) convertJavatoG2(<arg-name>); ..."
     ((EXPANDABLE |myArgArray|)
      (LITERAL "[")
      (SUBSTITUTE |<i>|)
      (LITERAL "] = (")
      (SUBSTITUTE |<rpc-arg-type>|)
      (LITERAL ") ")
      (EXPANDABLE |convertJavatoG2|)
      (LITERAL "(")
      (SUBSTITUTE |<arg-name>|)
      (LITERAL "); ")
      (REPLICATE-IN-LINES)))

    ;; Differentiating arrays in source from optional token.
    ("     private Object[] myArgArray = new Object[<max-arg-count>];"
     ((LITERAL "     private ")
      (EXPANDABLE |Object|)
      (LITERAL "[] ")
      (EXPANDABLE |myArgArray|)
      (LITERAL " = new ")
      (EXPANDABLE |Object|)
      (LITERAL "[")
      (SUBSTITUTE |<max-arg-count>|)
      (LITERAL "];")))

    ;; Terminate out of contiguous literal comma.
    ("           myConnection.callRPC(<method-symbol>, myArgArray);"
     ((LITERAL "           myConnection.callRPC(")
      (SUBSTITUTE |<method-symbol>|)
      (LITERAL ", ")
      (EXPANDABLE |myArgArray|)
      (LITERAL ");")))

    ;; Tokenize numbers as literals.
    ("connection.declareRemoteRPC(<method-symbol>, 1, 1, \"\", 1000); ..."
     ((LITERAL "connection.declareRemoteRPC(")
      (SUBSTITUTE |<method-symbol>|)
      (LITERAL ", 1, 1, \"\", 1000); ")
      (REPLICATE-IN-LINES)))

    ;; Need not expand tokens with embedded dots.
    ("       throw new [throws](e.toString());"
     ((LITERAL "       throw new ")
      (SKIP-LINE-UNLESS-TRUE |[throws]|)
      (LITERAL "(e.toString());")))

    ;; Something for package expansion.
    ("private static Symbol <method-symbol> = Symbol.intern(<method-string>); ..."
     ((LITERAL "private static ")
      (EXPANDABLE |Symbol|)
      (LITERAL " ")
      (SUBSTITUTE |<method-symbol>|)
      (LITERAL " = Symbol.intern(")
      (SUBSTITUTE |<method-string>|)
      (LITERAL "); ")
      (REPLICATE-IN-LINES)))

    ;; Sub-trees.
    ("     ^java-exported-method-implementation^..."
     ((LITERAL "     ")
      (INSERT-SUBTREE java-exported-method-implementation)
      (REPLICATE-IN-LINES)))

    ;; Abutting braces.
    ("public class <exception> extends Exception {}"
     ((LITERAL "public class ")
      (SUBSTITUTE |<exception>|)
      (LITERAL " extends ")
      (EXPANDABLE |Exception|)
      (LITERAL " {}")))
    ))

#+development
(defun validate-scan-syntax-tree-template-line ()
  (loop for (arg expected) in test-suite-for-scan-syntax-tree-template-line
	with passed-p = t
	do
    (let ((result (scan-syntax-tree-template-line arg)))
      (unless (equal result expected)
	(setq passed-p nil)
	(format t "~&!!! unexpected result !!!~%arg:~% ~S~%" arg)
	(format t "~&expected:~%  (~S~%~{   ~S~%~}   ~S)~%"
	  (car expected)
	  (butlast (cdr expected))
	  (car (last expected)))
	(format t "~&result:~%  (~S~%~{   ~S~%~}   ~S)~%"
	  (car result)
	  (butlast (cdr result))
	  (car (last result)))))
    finally (return passed-p)))

;;;; Tokenizing an Entire Syntax-Template

(defun-for-macro tokenize-syntax-tree-template (name template-string)
  (with-input-from-string (template-stream template-string)
    (loop for line? = (read-line template-stream nil nil)
	  for line-number from 1
	  while line?
	  for scanned-line
	      = `(template-line
		   nil ;insert-subtree?
		   nil ;splice-out-unless-true?
		   nil ;optional-alternative-line-p
		   nil ;replicate-lines-p
		   nil ;needs-index-binding-p
		   nil ;entirely-whitespace-p
		   ,@(scan-syntax-tree-template-line line?))
	  do (check-and-decorate-syntax-tree-template-line
	       name
	       line-number
	       scanned-line)
	  collect scanned-line)))

;;; The function `check-and-decorate-syntax-tree-template-line' is structured as
;;; a nest of loops, each one inside the finally clause of the previous one.

(defun-for-macro check-and-decorate-syntax-tree-template-line
    (name line-number line-info)

  ;; Check if this line specifies a valid nested subtree.
  (loop with insert-subtree-token? = nil
	with scanned-line = (syntax-tree-line-tokens-in-line line-info)
	for (token-type) in scanned-line
	for token in scanned-line
	with other-than-literal-found-p = nil
	with replicate-in-lines-found-p = nil
	do
    (cond
      ((and (eq token-type 'insert-subtree) insert-subtree-token?)
       (warn "DEF-SYNTAX-TREE-TEMPLATE of ~S~%  line number ~S~
              ~%  ignoring duplicate insert-subtree token ~S"
	     name
	     line-number
	     token))
      ((eq token-type 'insert-subtree) (setq insert-subtree-token? token))
      ((and (eq token-type 'replicate-in-lines) replicate-in-lines-found-p)
       (warn "DEF-SYNTAX-TREE-TEMPLATE of ~S~%  line number ~S~
              duplicate replicate-in-lines token - check whitespace use"
	     name
	     line-number))
      ((eq token-type 'replicate-in-lines)
       (setf (syntax-tree-line-replicate-lines-p line-info) t)
       (setq replicate-in-lines-found-p t))
      ((eq token-type 'literal))
      (t (setq other-than-literal-found-p t)))
	finally
    (when (and insert-subtree-token? other-than-literal-found-p)
      (warn "DEF-SYNTAX-TREE-TEMPLATE of ~S~%  line number ~S~
             ~%  ignoring unexpected token ~S~%~
             appearing on same line as insert-subtree token"
	    name
	    line-number
	    token))
    (setf (syntax-tree-line-insert-subtree? line-info) insert-subtree-token?)
    (unless insert-subtree-token?

      ;; Check if this line is to be emitted conditionally.
      (loop with skip-line-token? = nil
	    for (token-type) in scanned-line
	    for token in scanned-line
	    do
	(cond
	  ((and (eq token-type 'skip-line-unless-true) skip-line-token?)
	   (warn "DEF-SYNTAX-TREE-TEMPLATE of ~S~%  line number ~S~
                  ~%  ignoring duplicate skip-line-token ~S"
		 name
		 line-number
		 token))
	  ((eq token-type 'skip-line-unless-true)
	   (setq skip-line-token? token)))
	    finally
	(setf (syntax-tree-line-splice-out-unless-true? line-info)
	      skip-line-token?)

	;; Check if this line is to be replicated.
	(loop with replicate-lines-p = nil
	      for (token-type) in scanned-line
	      do
	  (cond
	    ((and (eq token-type 'replicate-in-lines) replicate-lines-p)
	     (warn "DEF-SYNTAX-TREE-TEMPLATE of ~S~%  line number ~S~
                    duplicate replicate-in-lines token - check whitespace use"
		   name
		   line-number))
	    ((eq token-type 'replicate-in-lines) (setq replicate-lines-p t)))
	      finally
	  (setf (syntax-tree-line-replicate-lines-p line-info)
		replicate-lines-p)

	  ;; Record if we need to bind index variables (the <i> thingees).
	  (loop for (token-type key) in scanned-line
		do
	    (cond
	      ((eq token-type 'optional-alternative)
	       (setf (syntax-tree-line-optional-alternative-line-p line-info)
		     t))
	      ((and (eq token-type 'substitute) (eq key '|<i>|))
	       (setf (syntax-tree-line-needs-index-binding-p line-info) t)))
		finally

	    ;; Record if the line is entirely whitespace - we skip these
	    ;; sometimes.
	    (setf (syntax-tree-line-entirely-whitespace-p line-info)
		  (loop for (token-type maybe-literal) in scanned-line
			always
			(and (eq token-type 'literal)
			     (every #'(lambda (x)
					(member x '(#\Space #\Tab #\Newline)
						:test #'eql))
				    maybe-literal))))))))))

;;;; Specific Syntax-Tree Templates

(def-syntax-tree-template java-exported-class-interface
    (java-interface-declaration
      <interface>
      <result-type>...
      <init-name>
      <method>...
      <<arg-type>...>...
      <<arg-name>...>...
      [throws]...
      (|G2Connection| |COM.gensym.jgi.G2Connection|))
  "interface <interface> extends Remote {
     void <init-name>(G2Connection connection);

     <result-type> <method>(<arg-type> <arg-name>,...) throws [throws]; ...
   }")

(def-syntax-tree-template java-exported-class-implementation
    (java-class-declaration
      <class>
      <interface>
      <method-symbol>...
      <method-string>...
      <max-arg-count>
      <init-name>
      (|Symbol|       |COM.gensym.util.Symbol|)
      (|G2Connection| |COM.gensym.jgi.G2Connection|)
      (|G2RMIready|   |COM.gensym.jgi.G2RMIready|)
      )
  "public class <class> extends G2RMIready implements <interface> {
     private static Symbol <method-symbol> = Symbol.intern(<method-string>); ...

     private G2Connection myConnection = null;

     private Object[] myArgArray = new Object[<max-arg-count>];

     public void <init-name>(G2Connection connection) {
       myConnection = connection;

       connection.declareRemoteRPC(<method-symbol>, 1, 1, null, 1000); ...
     }

     ^java-exported-method-implementation^...
   }")

(def-syntax-tree-template java-exported-method-implementation
    (java-method-declaration
      <result-type>
      <method>
      <arg-type>...
      <arg-name>...
      [throws] [~throws]
      <init-name>
      <rpc-arg-type>...
      <rpc-result-type>
      <method-symbol>
      <converted-result>
      (|G2AccessException| |COM.gensym.jgi.G2AccessException|))
  "public <result-type> <method>(<arg-type> <arg-name>,...)
       throws [throws]
   {
     if (myConnection == null) {
       throw new [throws](\"no connection to G2 - run <init-name>\");
       return [~throws];
     }

     myArgArray[<i>] = (<rpc-arg-type>) convertJavatoG2(<arg-name>); ...

     <rpc-result-type> result;
     try {
       result
         = (<rpc-result-type>)
           myConnection.callRPC(<method-symbol>, myArgArray);
     } catch (G2AccessException e) {
       throw new [throws](e.toString());
       return [~throws];
     }
     return (<result-type>) <converted-result>;
   }")

(def-syntax-tree-template java-exported-exception
    (java-class-declaration
      <exception>)
  "public class <exception> extends Exception {}")

;;;; Expanding Syntax-Tree Templates

;;; The macro `expand-syntax-tree-template' expands at runtime a template
;;; defined by def-syntax-tree-template.  It does some compile-time work to make
;;; this happen smoothly.  This macro returns two values:

;;;   (1) a new gensym-string representing the Java source code that is the
;;;       expansion of the named template with the given bindings and

;;;   (2) a java-list of gensym-strings representing the import statements
;;;       required for the emitted source code to compile.  This is returned as
;;;       a separate value from the source code proper, in case several
;;;       expansions are to be merged into a single compilation unit with a
;;;       single set of import statements.

;;; Reclamation of the memory occupied by the returned values is the
;;; responsibility of the caller of this macro.

;;; The bindings must include all those declared in the def-syntax-tree-template
;;; form of the same name, as well as all bindings in any sub-templates
;;; specified in the template (for further details, grep around insert-subtree).
;;; All these bindings must "match", in the sense that some sorts of binding
;;; expect lists, others gensym-strings.

;;; Finally, expand-syntax-tree-template expects its bindings to be a tree of
;;; slot-value-conses whose leaves are symbols or gensym-strings.  The cons-tree
;;; value will be reclaimed on exit from this form, but the leaves will not
;;; (i.e., reclaim-slot-value-tree will be used rather than reclaim-slot-value).

(defmacro expand-syntax-tree-template (name supplied-bindings)
  (let ((registry-entry? (assoc name syntax-tree-template-registry)))
    (unless registry-entry?
      (error "EXPAND-SYNTAX-TREE-TEMPLATE: no entry for ~S" name))
    (check-for-unbound-variables-in-expand-syntax-template
      name
      supplied-bindings)
    (let ((expandable-bindings
	    (syntax-tree-template-expandable-bindings registry-entry?)))
      `(let ((bindings
	       ,(convert-syntax-tree-binding-specs-to-internal-format
		  supplied-bindings
		  expandable-bindings)))
	 (retain-listed-bindings bindings)
	 (let ((result-string
		 (expand-syntax-template-given-bindings
		   ',name
		   bindings)))
	   (reclaim-slot-value-tree bindings)
	   result-string)))))

;;;; Compile-time Checking of Syntax-Template Expansion

(defun-for-macro check-for-unbound-variables-in-expand-syntax-template
    (template-name bindings)
  (let* ((should-be-bound
	   (collect-variables-within-syntax-template template-name))
	 (are-bound
	   (get-root-names-from-dynamic-syntax-spec (mapcar #'car bindings)))
	 (unbound? (set-difference should-be-bound (cons '|<i>| are-bound))))
    (when unbound?
      (error "EXPAND-SYNTAX-TREE-TEMPLATE: unbound variables: ~S" unbound?))))

(defun-for-macro collect-variables-within-syntax-template (template-name)
  (let ((registry-entry? (assoc template-name syntax-tree-template-registry)))
    (unless registry-entry?
      (error "EXPAND-SYNTAX-TREE-TEMPLATE: no entry for ~S" template-name))
    (let* ((template-lines
	     (syntax-tree-template-tokenized-lines registry-entry?))
	   (nested-variables
	     (loop for line-info in template-lines
		   for template-line
		       = (syntax-tree-line-tokens-in-line line-info)
		   append
	       (loop for (token-type token-root) in template-line
		     when (eq token-type 'insert-subtree)
		       append
		       (collect-variables-within-syntax-template
			 token-root)))))
      (append
	(get-root-names-from-dynamic-syntax-spec
	  (syntax-tree-template-dynamic-spec-names registry-entry?))
	nested-variables))))

;;;; Testing the Syntax-Template Expander

#+testing
(expand-syntax-tree-template java-exported-class-implementation
  ((<class>                 "JhThing")
   (<interface>             "JhThingInterface")
   (<method>...             (slot-value-list "jhMethod1" "jhMethod2"))
   (<method-symbol>...
     (slot-value-list "jhMethod1Symbol" "jhMethod2Symbol"))
   (<method-string>...
     (slot-value-list "\"JH-METHOD-1\"" "\"JH-METHOD-2\""))
   (<max-arg-count>         "2")
   (<init-name>             "initJhThing")
   ;; bindings for embedded java-exported-method-implementation templates
   (<result-type>...        (slot-value-list "int" "jhThing2[]"))
   ;; see above for <method> binding
   (<<arg-type>...>...
     (managed-backquote slot-value-cons (("JhThing2" "double") ())))
   (<<arg-name>...>...
     (managed-backquote slot-value-cons
       (("jhMethod1arg1" "jhMethod1arg2") ())))
   ([throws]...             (slot-value-list "JhError" nil))
   ([~throws]...            (slot-value-list nil "new JhThing2[0]"))
   (<<rpc-arg-type>...>...
     (managed-backquote slot-value-cons (("G2ItemProxy" "Double") ())))
   (<rpc-result-type>...    (slot-value-list "Integer" "Sequence"))
   (<converted-result>...
     (slot-value-list "Integer.intValue(result)" "ConvertG2toJava(result)"))
   ))

#+testing
(defparameter *bindings* nil)

#+testing
(defun restore-bindings-for-test ()
  (setq *bindings*
	;; I.e., the list that results from calling retain-listed-bindings on
	;; the result of evaluating the managed-backquote form in the
	;; macroexpansion of the above expand-syntax-template form
	(copy-tree-using-slot-value-conses
	  '((|<class>| SIMPLE "JhThing")
	    (|<interface>| SIMPLE "JhThingInterface")
	    (|<method>| LIST ("jhMethod1" "jhMethod2")
	     ("jhMethod1" "jhMethod2"))
	    (|<method-symbol>| LIST ("jhMethod1Symbol" "jhMethod2Symbol")
	     ("jhMethod1Symbol" "jhMethod2Symbol"))
	    (|<method-string>| LIST ("\"JH-METHOD-1\"" "\"JH-METHOD-2\"")
	     ("\"JH-METHOD-1\"" "\"JH-METHOD-2\""))
	    (|<max-arg-count>| SIMPLE "2") (|<init-name>| SIMPLE "initJhThing")
	    (|<result-type>| LIST ("int" "jhThing2[]") ("int" "jhThing2[]"))
	    (|<arg-type>| LIST-OF-LISTS (("JhThing2" "double") NIL)
	     (("JhThing2" "double") NIL))
	    (|<arg-name>| LIST-OF-LISTS (("jhMethod1arg1" "jhMethod1arg2") NIL)
	     (("jhMethod1arg1" "jhMethod1arg2") NIL))
	    (|[throws]| OPTIONALS-LIST ("JhError" NIL))
	    (|[~throws]| ALTERNATIVES-LIST (NIL "new JhThing2[0]"))
	    (|<rpc-arg-type>| LIST-OF-LISTS (("G2ItemProxy" "Double") NIL)
	     (("G2ItemProxy" "Double") NIL))
	    (|<rpc-result-type>| LIST ("Integer" "Sequence")
	     ("Integer" "Sequence"))
	    (|<converted-result>| LIST
	     ("Integer.intValue(result)" "ConvertG2toJava(result)")
	     ("Integer.intValue(result)" "ConvertG2toJava(result)"))
	    (|Symbol| EXPANDABLE "COM.gensym.util.Symbol")
	    (|G2Connection| EXPANDABLE "COM.gensym.jgi.G2Connection")
	    (|G2RMIready| EXPANDABLE "COM.gensym.jgi.G2RMIready"))))
  t)

#+testing
(expand-syntax-template-given-bindings
  'java-exported-class-implementation
  *bindings*)

;;;; Top-level Expansion of Syntax-Template

(defvar global-output-stream-for-expand-syntax-template nil)

(defun-allowing-unwind expand-syntax-template-given-bindings
    (template-name bindings filename)
  (jwith-output-to-file
    (filename global-output-stream-for-expand-syntax-template)
    ;; emit package here, using export-definition
    ;; emit imports here, unioning syntax-tree-template-packages-used with
    ;;   those in export-definition
    (expand-syntax-template-within-output-to-java-source-file
      template-name
      bindings
      2)))

;;;; Internal Format of Syntax-Template Expansion Spec

;;; Internal binding tags from
;;; `convert-syntax-tree-binding-specs-to-internal-format':
;;;   simple
;;;   list
;;;   list-of-lists
;;;   optional
;;;   optional-alternative
;;;   optionals-list
;;;   alternatives-list
;;;   expandable

(defun-for-macro get-internal-spec-for-expandable-syntax-tree-binding?
    (external-binding-spec)
  (and (consp external-binding-spec)
       `(,(first external-binding-spec)
	  expandable
	  ,(symbol-name (second external-binding-spec)))))

(defun-for-macro convert-syntax-tree-binding-specs-to-internal-format
    (binding-specs expandable-binding-specs)
  `(managed-backquote slot-value-cons
     ,(append
	(loop for (binding-spec value-form) in binding-specs
	      collect
	      (or (get-internal-binding-from-dynamic-syntax-spec
		    binding-spec
		    value-form)
		  (error "EXPAND-SYNTAX-TREE-TEMPLATE: bad binding spec ~S"
		    binding-spec)))
	(loop for expandable-binding-spec in expandable-binding-specs
	      collect
	      (get-internal-spec-for-expandable-syntax-tree-binding?
		expandable-binding-spec)))))

#+testing
(eval
  (convert-syntax-tree-binding-specs-to-internal-format
    '((<interface> "G2Thing")
      (<result-type>... (slot-value-list "Symbol" "int"))
      (<init-name> "initG2Thing")
      (<method>... (slot-value-list "G2method1" "G2method2" "G2method3"))
      (<<arg-type>...>...
       (managed-backquote slot-value-cons
	 (("int" "double") ("G2argThing") ())))
      (<<arg-name>...>...
       (managed-backquote slot-value-cons
	 (("intArg" "doubleArg") ("G2argThingArg") ())))
      ([throws]...
       (slot-value-list "G2method1Exception"
			"G2method2Exception"
			"G2method3Exception")))
    '((|G2Connection| |COM.gensym.jgi.G2Connection|))))

;;;; Looking up Bindings in Syntax-Template Expansion

(defun-simple look-up-raw-syntax-tree-binding (key bindings)
  (assq key bindings))

(defun-simple look-up-atomic-syntax-tree-binding (key bindings)
  (let ((result (third (look-up-raw-syntax-tree-binding key bindings))))
    #+development
    (when (consp result)
      (cerror "Take the first element"
	"EXPAND-SYNTAX-TREE-TEMPLATE: didn't expect ~S to be bound to a list"
	key)	      
      (setq result (car result)))
    result))

(defun-simple look-up-atomic-syntax-tree-binding-if-any (key bindings)
  (let ((result (third (look-up-raw-syntax-tree-binding key bindings))))
    (if (consp result)
	nil
	result)))

(defparameter syntax-tree-no-binding-tag '(no-binding))

(defun-simple look-up-listed-syntax-tree-binding
    (key bindings expected-list-structure destructive-p)
  (let* ((correct-list-structure-p t)
	 (raw-binding (look-up-raw-syntax-tree-binding key bindings))
	 (raw-contents (third raw-binding))
	 (result
	   (case expected-list-structure
	     (list-expected
	      (cond
		((null raw-contents) syntax-tree-no-binding-tag)
		((consp raw-contents)
		 (if destructive-p
		     (slot-value-pop (caddr raw-binding))
		     (car raw-contents)))
		(t (setq correct-list-structure-p nil) raw-contents)))
	     (list-of-lists-expected
	      (if (null raw-contents)
		  syntax-tree-no-binding-tag
		  (let ((maybe-nested-list (car raw-contents)))
		    (cond
		      ((null maybe-nested-list)
		       (when destructive-p
			 (slot-value-pop (caddr raw-binding)))
		       syntax-tree-no-binding-tag)
		      ((consp maybe-nested-list)
		       (if destructive-p
			   (slot-value-pop (caaddr raw-binding))
			   (car maybe-nested-list)))
		      (t (setq correct-list-structure-p nil)
			 maybe-nested-list))))))))
    (unless correct-list-structure-p
      #+development
      (cerror "Return first atomic result reached"
	"EXPAND-SYNTAX-TREE-TEMPLATE: expected ~S to be bound within a list~A"
	key
	(if (eq expected-list-structure 'lists-of-lists-expected)
	    " of lists"
	    "")))
    result))

(defun-simple look-up-number-of-listed-bindings (key bindings)
  (let* ((raw-binding (look-up-raw-syntax-tree-binding key bindings))
	 (raw-contents (third raw-binding))
	 (result (length raw-contents)))
    result))

(defun-simple pop-listed-syntax-tree-binding-layer (key bindings)
  (let ((raw-binding (look-up-raw-syntax-tree-binding key bindings)))
    (gensym-dstruct-bind ((key type raw-contents) raw-binding)
      (let ((demoted-contents
	      (and (consp raw-contents)
		   (slot-value-pop (caddr raw-binding)))))
	(slot-value-list
	  key
	  (case type
	    (list 'simple)
	    (optionals-list 'optional)
	    (alternatives-list 'optional-alternative)
	    (list-of-lists 'list))
	  demoted-contents
	  (copy-tree-using-slot-value-conses demoted-contents))))))

(defun-simple last-listed-syntax-tree-binding-p
    (key bindings expected-list-structure)
  (let* ((raw-binding (look-up-raw-syntax-tree-binding key bindings))
	 (raw-contents (third raw-binding)))
    (case expected-list-structure
      (list-expected
       (null (cdr raw-contents)))
      (list-of-lists-expected
       (null (cdar raw-contents))))))    

(defun-simple ensured-look-up-listed-syntax-tree-binding
    (key bindings expected-list-structure destructive-p)
  (let ((binding
	  (look-up-listed-syntax-tree-binding
	    key
	    bindings
	    expected-list-structure
	    destructive-p)))
    (cond
      ((eq binding syntax-tree-no-binding-tag)
       #+development
       (cerror "Proceed using NIL"
	 "EXPAND-SYNTAX-TREE-TEMPLATE: unbound token ~S" key)
       nil)
      (t binding))))

;;;; Handling Recursion in Syntax-Template Bindings

(defun-void retain-listed-bindings (bindings)
  (loop for (key type ephemeral-binding original-binding) in bindings
	for binding in bindings
	when (memq type '(list list-of-lists))
	  do (setf (cdr (last binding))
		   (slot-value-list
		     (copy-tree-using-slot-value-conses ephemeral-binding)))))

(defun-void restore-listed-bindings (bindings)
  (loop for (key type exhausted-binding original-binding) in bindings
	for binding in bindings
	when (memq type '(list list-of-lists))
	  do (reclaim-slot-value-tree exhausted-binding)
	     (setf (third binding)
		   (copy-tree-using-slot-value-conses original-binding))))

;;;; Writing Bound Values into a Syntax-Template Expansion
	  
(defun-simple twrite-syntax-tree-binding-if-found (key bindings lookup-mode)
  (let ((binding?
	  (case lookup-mode
	    (atom-expected (look-up-atomic-syntax-tree-binding key bindings))
	    (otherwise
	     (or (look-up-atomic-syntax-tree-binding-if-any key bindings)
		 (ensured-look-up-listed-syntax-tree-binding
		   key
		   bindings
		   lookup-mode
		   t)))))) ;Beware - destructive lookup!
    (cond
      (binding?
       (twrite-string binding?)
       t)
      (t nil))))

(defmacro with-twrite-available-for-syntax-tree-binding
    ((twrite-if-found bindings) &body body)
  `(macrolet ((,twrite-if-found (key lookup-mode)
		`(twrite-syntax-tree-binding-if-found
		   ,key
		   ,',bindings
		   ,(case lookup-mode
		      (maybe-replicate
		       `(if replicating-lines-p
			    'list-expected
			    'atom-expected))
		      (maybe-replicate-list
		       `(if replicating-lines-p
			    'list-of-lists-expected
			    'list-expected))
		      (otherwise `',lookup-mode)))))
     (jwith-output-to-text-line
         (global-output-stream-for-expand-syntax-template)
       ,@body)))

;;;; Expanding a Single Line of a Syntax-Template

(defun-void expand-syntax-template-line
    (tokens-in-line bindings replicating-lines-p indentation)
  (with-twrite-available-for-syntax-tree-binding (twrite-if-found bindings)
    (loop for i from 1 to indentation do (twrite-char #\Space))
    (loop for token-cons? on tokens-in-line
	  while token-cons?
	  for (token-type key-or-literal) = (car token-cons?)
	  with first-token-cons-in-comma-series? = nil
	  with splicable-literal-cons? = nil
	  do
      (case token-type
	(literal
	 (unless (or first-token-cons-in-comma-series?
		     splicable-literal-cons?)
	   (twrite-string key-or-literal)))
	(expandable
	 (twrite-string (symbol-name-text-string key-or-literal)))
	(substitute (twrite-if-found key-or-literal maybe-replicate))
	(midst-of-comma-series
	 (unless first-token-cons-in-comma-series?
	   (setq first-token-cons-in-comma-series? token-cons?)))
	(last-of-comma-series
	 (expand-comma-series-in-syntax-template-line
	   bindings
	   replicating-lines-p
	   first-token-cons-in-comma-series?
	   token-cons?)
	 (unless replicating-lines-p
	   (restore-listed-bindings bindings))
	 (setq first-token-cons-in-comma-series? nil))
	(skip-line-unless-true ;known true at this point
	 (twrite-if-found key-or-literal maybe-replicate))
	(optional-alternative ;mutually exclusive with preceding clause
	 (twrite-if-found key-or-literal maybe-replicate))
	(splice-out-unless-true
	 (expand-splicable-syntax-template-line
	   key-or-literal
	   bindings
	   replicating-lines-p
	   splicable-literal-cons?
	   token-cons?)
	 (setq splicable-literal-cons? nil))
	(splicable-literal (setq splicable-literal-cons? token-cons?))
	(replicate-in-lines nil)
	#+development
	(otherwise (cerror "Ignore"
		     "EXPAND-SYNTAX-TREE-TEMPLATE: ~
                      unexpected token (~S ~S) encountered"
		     token-type key-or-literal)))
	  finally (twrite-line-separator))))

(defun-void expand-comma-series-in-syntax-template-line
    (bindings
      replicating-lines-p
      first-token-cons-in-comma-series?
      token-cons?)
  (with-twrite-available-for-syntax-tree-binding (twrite-if-found bindings)
    (let* ((initial-series-cons
	     (or first-token-cons-in-comma-series? token-cons?))
	   (first-token (car initial-series-cons))
	   (key (second first-token))
	   (expected-list-structure
	     (if replicating-lines-p
		 'list-of-lists-expected
		 'list-expected)))
      (loop for typical-binding
		= (look-up-listed-syntax-tree-binding
		    key
		    bindings
		    expected-list-structure
		    nil)
	    until (eq typical-binding syntax-tree-no-binding-tag)
	    for last-series-p
		= (last-listed-syntax-tree-binding-p
		    key
		    bindings
		    expected-list-structure)
	    do
	(loop for series-cons on initial-series-cons
	      for (token-type key-or-literal) = (car series-cons)
	      do
	  (case token-type
	    (last-of-comma-series
	     (twrite-if-found key-or-literal maybe-replicate-list)
	     (loop-finish))
	    (midst-of-comma-series
	     (twrite-if-found key-or-literal maybe-replicate-list))
	    (literal (twrite-string key-or-literal))
	    #+development
	    (otherwise (cerror
			 "Ignore"
			 "EXPAND-SYNTAX-TREE-TEMPLATE: ~
                          unexpected token (~S ~S) in comma series"
			 token-type
			 key-or-literal))))
	(unless last-series-p
	  (twrite-string ", "))))))

(defun-void expand-splicable-syntax-template-line
    (key
      bindings
      replicating-lines-p
      splicable-literal-cons?
      token-cons?)
  (with-twrite-available-for-syntax-tree-binding (twrite-if-found bindings)
    (let ((binding?
	    (if replicating-lines-p
		(ensured-look-up-listed-syntax-tree-binding
		  key
		  bindings
		  'list-expected
		  nil) ;non-destructive - twrite-if-found does the side-effect
		(look-up-atomic-syntax-tree-binding key bindings))))
      (cond
	(binding?
	 (loop for not-spliced-cons
	       on (or splicable-literal-cons? token-cons?)
	       for (token-type key-or-literal) = (car not-spliced-cons)
	       do
	   (case token-type
	     (splice-out-unless-true
	      (twrite-if-found key-or-literal maybe-replicate)
	      (loop-finish))
	     ((splicable-literal literal) (twrite-string key-or-literal))
	     #+development
	     (otherwise (cerror
			  "Ignore"
			  "EXPAND-SYNTAX-TREE-TEMPLATE: ~
                           unexpected token (~S ~S) in splicable series"
			  token-type
			  key-or-literal)))))
	;; Discard nil binding here because twrite-if-found was not called in
	;; this branch, and so could not do its destructive stuff.
	(replicating-lines-p 
	 (ensured-look-up-listed-syntax-tree-binding
	   key
	   bindings
	   'list-expected
	   t))))))

;;;; Index Variable in Syntax-Template Expansion

(defmacro with-index-binding-for-syntax-template
    ((needed-p bindings-place bump-index-binding) &body body)
  (avoiding-variable-capture (&aux index index-binding?)
    `(let ((,index 0)
	   (,index-binding?
	      (and ,needed-p
		   (slot-value-list '|<i>| 'simple (copy-gensym-string "")))))
       (macrolet ((,bump-index-binding ()
		    `(when ,',index-binding?
		       (reclaim-gensym-string (third ,',index-binding?))
		       (setf (third ,',index-binding?)
			     (twith-output-to-gensym-string
			       (twrite-fixnum ,',index)))
		       (incff ,',index))))
	 (when ,index-binding?
	   (slot-value-push ,index-binding? ,bindings-place))
	 ,@body
	 (when ,index-binding?
	   (slot-value-pop ,bindings-place)
	   (reclaim-slot-value ,index-binding?))))))

;;;; Replication While Expanding a Syntax-Template

;;; If the look-outside-line-p argument of
;;; `look-up-typical-replicated-binding-if-any' is non-nil, this function will
;;; search in all bindings, not just those associated with the tokens mentioned
;;; in the tokens-in-line argument.

(defun look-up-typical-replicated-binding-if-any
    (tokens-in-line bindings line-number &optional (look-outside-line-p nil))
  #-development (declare (ignore line-number))
  (let* ((actual-list-structure nil)
	 (key?
	   (if look-outside-line-p
	       (loop for (key type) in bindings
		     thereis
		     (and (member type '(list list-of-lists))
			  (setq actual-list-structure type)
			  key))
	       (loop for (token-type key) in tokens-in-line
		     for token in tokens-in-line
		     thereis
		     (and (eq token-type 'substitute)
			  (gensym-dstruct-bind
			      ((key? type) 
			       (look-up-raw-syntax-tree-binding key bindings))
			    (and key?
				 (member type '(list list-of-lists))
				 (setq actual-list-structure type)
				 key?)))))))
    #+development
    (unless key?
      (cerror "ignore the template for this line"
	      "EXPAND-SYNTAX-TREE-TEMPLATE: ~
               expected a substitute token in line number ~S~%~S"
	      line-number
	      tokens-in-line))
    (values key? actual-list-structure)))

(defmacro with-replication-for-syntax-template
    ((tokens-in-line bindings line-number &optional look-outside-line-p)
     (binding-var) &body body)
  (avoiding-variable-capture
      (bindings
	&aux i listed-binding? expected-list-structure actual-list-structure)
    `(multiple-value-bind (,listed-binding? ,actual-list-structure)
	 (look-up-typical-replicated-binding-if-any
	   ,tokens-in-line
	   ,bindings
	   ,line-number
	   ,look-outside-line-p)
       (when ,listed-binding?
	 (loop with ,expected-list-structure
		 = (case ,actual-list-structure
		     (list 'list-expected)
		     (list-of-lists 'list-of-lists-expected))
	       for ,i from 1 to (look-up-number-of-listed-bindings
				  ,listed-binding?
				  ,bindings)
	       for ,binding-var = (look-up-listed-syntax-tree-binding
				    ,listed-binding?
				    ,bindings
				    ,expected-list-structure
				    nil) ;non-destructive lookup
	       until (eq ,binding-var syntax-tree-no-binding-tag)
	       do
	   ,@body)))))

(defun-void expand-replicated-syntax-subtree
    (subtree-to-insert tokens-in-line bindings line-number indentation)
  (let ((multi-line-p (multi-line-syntax-template-p subtree-to-insert)))
    (with-replication-for-syntax-template
	(tokens-in-line bindings line-number t) (ignore)
      (let ((bindings-for-one-iteration
	      (loop for (key type value) in bindings
		    for binding in bindings
		    collect
		    (case type
		      ((list list-of-lists optionals-list alternatives-list)
		       (pop-listed-syntax-tree-binding-layer key bindings))
		      (otherwise
		       (copy-list-using-slot-value-conses binding)))
		      using slot-value-cons)))
	(expand-syntax-template-within-output-to-java-source-file
	  subtree-to-insert
	  bindings-for-one-iteration
	  (if multi-line-p (+f indentation 2) indentation))
	(when multi-line-p
	  (jwith-output-to-text-line
	    (global-output-stream-for-expand-syntax-template)))
	(reclaim-slot-value-tree bindings-for-one-iteration)))))

;;;; Expanding Optional Lines of a Syntax-Template

(defun-void expand-optional-syntax-tree-lines
    (controlling-key
      cons-holding-this-line
      tokens-in-line
      bindings
      line-number
      indentation
      replicate-lines-p
      needs-index-binding-p)
  (cond
    (replicate-lines-p
     (with-index-binding-for-syntax-template
	 (needs-index-binding-p bindings bump-index-binding)
       (with-replication-for-syntax-template
	   (tokens-in-line bindings line-number) (binding?)
	 (bump-index-binding)
	 (cond
	   (binding?
	    (expand-syntax-template-line
	      tokens-in-line
	      bindings
	      t
	      indentation))
	   (t (let ((next-line (cadr cons-holding-this-line)))
		(when (syntax-tree-line-optional-alternative-line-p next-line)
		  (expand-syntax-template-line
		    (syntax-tree-line-tokens-in-line next-line)
		    bindings
		    t
		    indentation))))))))
    (t (let ((binding?
	       (look-up-atomic-syntax-tree-binding controlling-key bindings)))
	 (cond
	   (binding?
	    (expand-syntax-template-line
	      tokens-in-line
	      bindings
	      nil
	      indentation))
	   (t (let ((next-line (cadr cons-holding-this-line)))
		(when (syntax-tree-line-optional-alternative-line-p next-line)
		  (expand-syntax-template-line
		    (syntax-tree-line-tokens-in-line next-line)
		    bindings
		    nil
		    indentation)))))))))

;;;; Recursion Point for Syntax-Template Expansion

(defun-void expand-syntax-template-within-output-to-java-source-file
    (template-name bindings indentation)
  (let ((registry-entry? (assq template-name syntax-tree-template-registry)))
    (when registry-entry?
      (let ((tokenized-template
	      (syntax-tree-template-tokenized-lines registry-entry?)))
	(loop for (nil ;nils are sugar
		    (nil subtree-to-insert?)
		    (nil skip-line-unless-true?)
		    optional-alternative-line-p
		    replicate-lines-p
		    needs-index-binding-p ;need to bind <i>
		    entirely-whitespace-p
		    . tokens-in-line)
		  in tokenized-template
	      for cons-holding-this-line on tokenized-template
	      for line-number from 1
	      with suppress-next-whitespace-line-p = nil
	      do
	  (cond
	    ((and replicate-lines-p subtree-to-insert?)
	     (expand-replicated-syntax-subtree
	       subtree-to-insert?
	       tokens-in-line
	       bindings
	       line-number
	       indentation)
	     (restore-listed-bindings bindings))
	    (subtree-to-insert?
	     (expand-syntax-template-within-output-to-java-source-file
	       subtree-to-insert?
	       bindings
	       (if (multi-line-syntax-template-p subtree-to-insert?)
		   (+f indentation 2)
		   indentation)))
	    (skip-line-unless-true?
	     (expand-optional-syntax-tree-lines
	       skip-line-unless-true?
	       cons-holding-this-line
	       tokens-in-line
	       bindings
	       line-number
	       indentation
	       replicate-lines-p
	       needs-index-binding-p))
	    (optional-alternative-line-p) ;consumed by preceding template line
	    (replicate-lines-p
	     (setq suppress-next-whitespace-line-p t)
	     (with-index-binding-for-syntax-template
		 (needs-index-binding-p bindings bump-index-binding)
	       (with-replication-for-syntax-template
		   (tokens-in-line bindings line-number) (ignore)
		 ;; I.e., eval the following if at least one line written.
		 (setq suppress-next-whitespace-line-p nil)
		 (bump-index-binding)
		 (expand-syntax-template-line
		   tokens-in-line
		   bindings
		   t
		   indentation)))
	     (restore-listed-bindings bindings))
	    (t (unless (and entirely-whitespace-p
			    suppress-next-whitespace-line-p)
		 (expand-syntax-template-line
		   tokens-in-line
		   bindings
		   nil
		   indentation))
	       (when suppress-next-whitespace-line-p
		 (setq suppress-next-whitespace-line-p nil)))))))))

(defun-simple multi-line-syntax-template-p (template-name)
  (let ((registry-entry? (assq template-name syntax-tree-template-registry)))
    (and registry-entry?
	 (let ((tokenized-template
		 (syntax-tree-template-tokenized-lines registry-entry?)))
	   (and (cdr (syntax-tree-line-tokens-in-line tokenized-template)) t)))))

;;;; To Do

;; put helpers into JavaLink: G2RMIReady.convertG2toJava(), convertJavatoG2()
;;   array conversion to java (both arg and result)
;;     get class name Symbol from G2ItemProxy.getClassName()
;;     use Class.forname() to get Class object from Symbol.toString()
;;     use Class.newInstance() to make Object of more specific type
;;     use java.lang.reflect.Array.newInstance() to make arrays
;;   array conversion from java (both arg and result)
;;     use getClass() -> toString()
;;     use appropriate JavaLink constructor, then getContents()
;; Put G2RMIready into JavaLink, extends RemoteObject or some subclass,
;;   this cuts the tether to ICP

;; restrictions:
;;   G2 method can only signal one object type
;;     need new frame note?
