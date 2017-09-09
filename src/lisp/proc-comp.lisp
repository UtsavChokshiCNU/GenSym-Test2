;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module PROC-COMP

;;; Copyright (c) 1986 - 2017 Gensym Corporation.

;;; All rights reserved.

;;; Jim Allard






;;;; Forward References




;;; References to GRAMMAR2

(declare-forward-reference write-expression function)

;;; References to STACK-UTILS

(declare-forward-reference resolve-procedure-byte-code-addresses function)

;;; References to STACK-COMP

(declare-forward-reference compile-stack-expression-into-nodes function)
(declare-forward-reference compiler-warning-if-superseded-attribute function)


;;; References to INSTALL

(declare-forward-reference analyze-compiled-items-for-consistency function)

;;; References to G2-RPC1

(declare-forward-reference remote-procedure-returned-values-description-function function)

(declare-forward-reference set-remote-procedure-returned-values-description-function function)

(declare-forward-reference remote-procedure-argument-description-function function)

(declare-forward-reference set-remote-procedure-argument-description-function function)

(declare-forward-reference remote-procedure-return-value-types-function function)

;;; in STACK-UTILS
#+development
(declare-forward-reference known-stack-instruction-name? function)



;;; in FILTERS
(declare-forward-reference block-is-optimizable-p function)
(declare-forward-reference set-remote-procedure-argument-description-function function)

;;defined below 
(declare-forward-reference no-inlining? variable)
(declare-forward-reference block-can-be-inlined-p function)
(declare-forward-reference block-has-stable-heirarchy-p function)
(declare-forward-reference block-is-unstable-p function)








;;;; Procedures Compiler




;;; The PROC-COMP module contains the compiler for procedures.  This compiler
;;; currently produces only pseudo-code for a procedures interpreter, but it is
;;; designed so that a second back-end, a Lisp code emitter, can be added when
;;; the time comes to produce machine code compilations.

;;; The main function of this module is compile-procedure.  It is called from
;;; the slot value compiler for procedures when a procedure is edited.  It needs
;;; to produce a set of outputs to be stored into a procedure definition
;;; frame.

;;; The first is an ordered list of code-bodies.  For each of these code bodies
;;; there are two components: an environment description and an instruction
;;; vector.  There are three portions to any procedure environment.  The first
;;; is the segment which accepts arguments for the procedure.  In environments
;;; for code bodies which are not the base code body, this will always be empty.
;;; Next is the segment of the environment which receives returned values from
;;; other procedure invocations.  This must be long enough to receive the
;;; maximum number of values asked for within any CALL in the code body.  Next
;;; are the local variables for this code body.  Note that one of the local
;;; variables may be a pointer to the environment of a surrounding code body
;;; within this procedure.  The instruction vector of a code body is a managed
;;; array of instructions suitable for interpretation within execute-code-body-
;;; invocation.

;;; The remainder of the elements produced by the compiler are for user
;;; debugging purposes only.  They will not be implemented in the first pass at
;;; the compiler.

;;; The second is a list of the designations of other procedures called by this
;;; procedure, the names of frames, the classes referenced, and the
;;; attribute/class pairs referenced.





;;;; The Instant Compiler




;;; It is now 5:30 pm on 4/13/89.  This compiler I'm about to describe is going
;;; to be completed by this time tomorrow, or my name is Mud. -jra

;;; I'm a little muddy.  It was working at 8:30 pm on 4/14/89.

;;; The slots of a procedure instance which need to be set by a compiler are as
;;; follows:  code-bodies, argument-count, returned-values-description, and
;;; argument-list-description.  The slots of the code-body which need to be set
;;; are:  procedure-definition-of-code-body, code-body-argument-count,
;;; return-value-position, maximum-received-value-count, environment-length,
;;; environment-description, p-code-array, and procedure-free-references.  Below
;;; is a description of what each of these are.






;;;; Procedure Slots Set by the Compiler




;;; Code-bodies : a slot value list of the one code body.  This is not saved
;;; currently (since we can't write def-structures out in KB's), so the compiler
;;; will work in the slot putter for the procedure definition.

;;; Argument-count : integer number of args

;;; Returned-values-description : a slot value cons property list containing at
;;; least the property :type giving the type for that return value.  There are
;;; no other properties at this time. THIS CONVERTS TO A VECTOR AT THE END OF
;;; COMPILATION.  

;;; Argument-list-description : a slot value that during compilation is a
;;; cons entry whose car is the name (if any) of the local-name of this spot,
;;; and whose cdr is a slot value cons property list of the properties for this
;;; spot.  THIS CONVERTS TO A VECTOR AT THE END OF COMPILATION. See the
;;; description of the environment-description slot of a code body for this list
;;; of possible properties and detail.

;;; Procedure-free-references : a slot value cons entry whose elements are
;;; themselves lists.  The first element of each of these lists is a designation
;;; which was referenced inside of the procedure, but which depends on objects
;;; outside of the procedure.  These dependencies are to named objects, class
;;; names, and attributes of defined classes.  The rest of the list is reserved
;;; for type constraint information which will be added in a later version of
;;; this compiler.




;;;; Code Body Slots Set by the Compiler




;;; Procedure-definition-of-code-body : a pointer to the procedure

;;; Code-body-argument-count : number of args to procedure

;;; Return-value-position : integer position of first spot for returned values.

;;; Maximum-received-value-count : count of number of environment spots after
;;; the return-value-position reserved for receiving returned values.

;;; Environment-length : integer length of environment

;;; Environment-description : a slot value cons entry whose car is the name of
;;; the variable spot (or nil), and whose cdr is a slot value cons property list
;;; describing this variable.  The available properties are: :environment
;;; property is t if this is a pointer to another argument, :type property
;;; containing the type-specification of this spot, and finally a :return-value
;;; property containing the 1 based count of which return value position this
;;; is.

;;; P-code-array : a managed array containing slot value conses of instructions.






;;;; Procedure Return




;;; Returning from procedures works as follows.  When a return is executed from
;;; the main code body, the expressions giving the values are evaluated, and the
;;; values are directly inserted into the environment of the calling code body
;;; invocation of the procedure invocation which initiated the call.  This is
;;; performed by the return-values instruction.  However, if a return statement
;;; is compiled within a code body which is not the base, then the following
;;; happens.  A set of variable spots are generated within the environment of
;;; the base code body, one for each return value.  These are bound into the
;;; variable generated-var-spots-for-base-code-body-return.  A set of
;;; instructions are emitted into the code body containing the return statement
;;; which will assign the values to be returned into those spots.  A jump is
;;; then emitted back to the tag bound in the variable
;;; base-code-body-return-tag.  he reference to this tag will cause code to be
;;; emitted into the base code body after the base-code-body-return-tag which
;;; will execute a return statement, sending the bound values back.  Note that
;;; the jump back into the base code body will abort all of the other called
;;; code bodies of the procedure, correctly shutting parallel code bodies of the
;;; the procedure down before returning.

;;; The variable `generated-var-spots-for-base-code-body-return' is bound by the
;;; procedure compiler and is used to store variable spots generated to hold
;;; returned values.

(defvar generated-var-spots-for-base-code-body-return nil)




;;; The variable `returned-values-description' holds the current description of
;;; the return values for a procedure during the compile.

(defvar returned-values-description nil)



;;; The variable `return-statement-processed?' is set whenever a return-stament is
;;; hit in the code body. This allows us to error if the procedure indicates that
;;; it should return values but it has absolutely no way of doing so.

(defvar return-statement-processed? nil)


;;; The variable `call-statement-processed?' is set whenever a call-statement is
;;; hit in the code body. This is only used for actions that have been
;;; methodized to warn the user that the procedure may (unexpectedly) not bottom
;;; out with the system call.

(defvar call-statement-processed? nil)


;;; The special variable `expression-bound-local-names' contains an alist of
;;; designations to var-spots.  These bindings are established by expressions
;;; whose iterpreters need to keep values in environment bindings which will
;;; then be further referenced by evaluated expressions.  Aggregators are
;;; currently the only users of this facility.

(defvar expression-bound-local-names nil)




;;; The function `write-procedure-statement' takes a parsed procedure statement
;;; and will twrite a formatted output of that statement.

(defun write-procedure-statement (statement-to-write)
  (let ((writer (procedure-statement-writer (car statement-to-write))))
    (if writer
	(funcall-compiled-function writer statement-to-write)
	(tformat "~a" statement-to-write))
    nil))




;;; The global variable `procedure-branch-short-cuts' is defined for the
;;; tag replacer and the optimizer which short cuts branch statements whose
;;; targets are other branch statements.  See documentation for
;;; instruction-address-for-tag (just below) and short-cut-branch-to-branch-
;;; procedure-instructions for further documentation.

(defvar procedure-branch-short-cuts nil)




;;; The function `instruction-address-for-tag' takes a tag and an indication if
;;; this is an address for a JUMP and returns the replacement for that
;;; tag.  This function is called from two different contexts.  The first
;;; is the optimizer for branch-to-branch short-cuts.  The second is during
;;; actual back-end code emitting.

;;; During the optimization pass some branch tags will be replaced with others.
;;; If this function is called from within that context, then the special
;;; variable `procedure-branch-short-cuts' will be bound to an alist of source
;;; and target replacement tags.  This variable will be NIL outside of that
;;; context.  During this context this function should map from the given tag to
;;; tags found in the alist.  If there is no alist entry for a given tag, then
;;; the original tag should be returned.  Also note that there are no jump-tag
;;; references, so if this is a jump-reference then the original tag should be
;;; immediately returned.

;;; During back-end code emitting (i.e.  procedure-branch-short-cuts is NIL),
;;; the instruction address for the given tag is returned.  If the passed tag is
;;; not defined a procedure compiler error message is issued, and the address 0
;;; is returned.

(defun instruction-address-for-tag (tag-name jump-reference?)
  (if procedure-branch-short-cuts
      (if jump-reference?
	  tag-name
	  (or (cdr (assoc tag-name procedure-branch-short-cuts))
	      tag-name))
      (let ((goto-tag-entry?
	      (goto-tag-entry-with-name
		tag-name goto-tags-in-compilation))
	    (address? nil))
	(if goto-tag-entry?
	    (if jump-reference?
		(if (goto-tag-jump-referenced? goto-tag-entry?)
		    (setq address?
			  (goto-tag-jump-address goto-tag-entry?))
		    (progn
		      (compiler-bug
			"instruction address lookup"
			"The tag ~a was referenced via a JUMP instruction, but ~
                         no such reference had been noted."
			tag-name)
		      (setq address? 0)))
		(setq address? (goto-tag-address goto-tag-entry?)))
	    (progn
	      (compiler-error
		"The tag ~a was referenced, but no such tag is declared for ~
                 this procedure."
		tag-name)
	      (setq address? 0)))
	(unless address?
	  (compiler-bug
	    "address resolver"
	    "The tag ~a did not have a registered address at address ~
             resolution time."
	    tag-name)
	  (setq address? 0))
	address?)))

;;; The special variable `base-code-body-return-tag' is used to hold the tag for
;;; jumps to a return statement within the base code body.

(defvar base-code-body-return-tag nil)




;;; The function `goto-tag-entry-with-name' takes a tag name and a list of
;;; procedure tag entries.  It returns the entry with the given name or NIL.

(defun goto-tag-entry-with-name (tag-name tag-entries)
  (loop with tag-name-is-fixnum? = (fixnump tag-name)
	for entry in tag-entries
	for entry-tag-name = (goto-tag-name entry)
	do
    (when (if tag-name-is-fixnum?
	      (and (fixnump entry-tag-name)
		   (=f tag-name entry-tag-name))
	      (and (not (fixnump entry-tag-name))
		   (eq tag-name entry-tag-name)))
      (return entry))))




;;; The function `emit-byte-code-vector-for-procedure' takes a byte-code-stream and a list
;;; of pseudo instructions emitted from a procedure, emits byte codes to
;;; implement those instructions.

(defun emit-byte-code-vector-for-procedure (byte-code-stream instructions)
  (loop for compiler-instruction in instructions
	for instruction-name = (if (consp compiler-instruction)
				   (car-of-cons compiler-instruction))
	for emitter-function? =
	    (if instruction-name
		(pseudo-instruction-byte-code-emitter instruction-name))
	do
    (cond
      (emitter-function?
       (funcall-simple-compiled-function
	 emitter-function? byte-code-stream compiler-instruction))
      (t
       (compiler-bug
	 "byte code emitter"
	 "The pseudo instruction ~a had no byte code emitter function."
	 instruction-name))))
  (coalesce-lookup-structures (byte-code-stream-text-position-information?
				byte-code-stream)
			      byte-code-stream))

;;




;;; The global property `goto-tag-replacer' takes the name of an
;;; instruction and returns the name of the tag replacer function for that
;;; instruction, if any.

(def-global-property-name goto-tag-replacer)




;;; The macro `def-goto-tag-replacer' takes the name of an instruction and
;;; a body of forms as its arguments.  It causes a replacer function to be
;;; defined for this instruction which is called with the variable INSTRUCTION
;;; bound to an instruction of this type.  Addresses for tags should be looked
;;; up with the function instruction-address-for-tag.  Note that this function
;;; will always return an address, and takes care of noting undefined tag errors
;;; itself.  The body forms of this replacer function should return the
;;; instruction with tags replaced by instruction addresses.  The top level
;;; conses of these instructions will always be made of phrase conses, so the
;;; body forms are allowed to mutate the top level conses of the given
;;; instruction and to insert the instruction addresses.  However, this function
;;; may instead return a new phrase cons copy with the correct instruction
;;; addresses if that is more convenient.

(defmacro def-goto-tag-replacer (instruction-name &body forms)
  (let ((replacer-function
	  (intern (format nil "~a-TAG-REPLACER" instruction-name))))
    `(progn
       (defun-simple ,replacer-function (instruction)
	 ,@forms)
       (setf (goto-tag-replacer ',instruction-name) #',replacer-function)
       ',instruction-name)))




;;; The global property `goto-tag-references' associates the name of an
;;; instruction with the name of the function which can be called to collect a
;;; phrase cons list of the tags which this instruction references.

(def-global-property-name goto-tag-references)




;;; The macro `def-goto-tag-references' takes the name of an instruction
;;; and a body of forms as its arguments.  It causes a tag reference accessor to
;;; be defined for this instruction.  This tag referencer will be called with
;;; the variable INSTRUCTION bound to an instruction of this type.  The body of
;;; forms should then return a phrase cons list of the tags which this function
;;; accesses.

(defmacro def-goto-tag-references (instruction-name &body forms)
  (let ((referencer-function
	  (intern (format nil "~a-TAG-REFERENCER" instruction-name))))
    `(progn
       (defun-simple ,referencer-function (instruction)
	 ,@forms)
       (setf (goto-tag-references ',instruction-name)
	     #',referencer-function))))




;;; The macro `tag-references-in-instruction' takes a procedure instruction
;;; and returns a phrase cons list of the tags which the instruction references
;;; as targets of branches.  This is used when optimizing code and finding
;;; unreachable tag statements.

(def-substitution-macro tag-references-in-instruction (instruction)
  (let ((referencer-function? (goto-tag-references (car-of-cons instruction))))
    (when referencer-function?
      (when (not (goto-tag-replacer (car-of-cons instruction)))
	(compiler-bug
	  "tag replacers"
	  "No goto tag replacer function exists for ~a."
	  (car-of-cons instruction)))
      (funcall-simple-compiled-function referencer-function? instruction))))






;;;; Procedure Compiler Top Level

;;; The function `compile-procedure-definition' takes a procedure frame and an
;;; already parsed procedure definition and mutates that procedure to produce a
;;; compilation for the procedure definition.  There are four parts to procedure
;;; compilation.  The first is generation of the environment description.  The
;;; second is traversing the procedure definition statement and emitting
;;; compiler internal code instructions.  The third is optimizing the set of
;;; compiler internal code instructions through dead code analysis and the like.
;;; And the fourth is code generation, emitting pseudo-code instructions into a
;;; p-code-array while resolving branch tags into instruction addresses.  The
;;; implementation of a compiler into Lisp will involve writing an alternate
;;; fourth part which emits Lisp instead of pseudo-code.

;;; Modified to handle method compilation because methods are a subclass of
;;; procedure.  Only specific-methods should be compiled here because generic
;;; methods do not have a procedure-definition.  The main change for method
;;; compilation is that the specific method does not receive its name from the
;;; procedure-definition.  The specific method renames unnamed and cannot be
;;; named.

(defvar current-return-values-position nil)

(defun list-to-managed-array (list)
  (let* ((length (length list))
	 (array (allocate-managed-array length)))
    (loop for i from 0 below length
	  for item in list
	  do
      (setf (managed-svref array i) item))
    array))

;;;
;;; The function procedure-has-empty-code-body-p takes procedure 
;;; and checks for case when that procedure does not contain any code 
;;; in such case it returns t otherwise nil
;;;

(defun procedure-has-empty-code-body-p (proc-def)
    (let* ((body (nth 4 proc-def))
            (body-length (length body))
            (first-operator (car body)))
        (if (and (eq first-operator 'begin-statement)
                 (eq body-length 1))
            t
            nil)))    
    
(defun-allowing-unwind compile-procedure-definition
    (procedure procedure-definition)
  (delete-frame-note-if-any 'compile-procedure-note procedure)
  (setf (has-empty-code-body? procedure) 
       (procedure-has-empty-code-body-p procedure-definition))    
  (incff (n-compiles-this-session procedure))
  (gensym-dstruct-bind ((name args return-types local-vars body-statement)
		       procedure-definition)
    (let* ((*current-computation-frame* procedure)
	   (current-computation-component-particulars nil)
	   (missing-local-names-already-reported nil)
	   (duplicate-local-names-already-reported nil)
	   (base-environment nil)
   (returned-values-description nil)
	   (return-statement-processed? nil) ;any return-statements at all in the body?
	   (call-statement-processed? nil)
	   (argument-list-description nil)
	   (variable-initializations nil)
	   (code-body-frames nil)
	   (warning-string nil)
	   ;; I have seen the procedure-definition get mutated during
	   ;; compilation, so it's copied here and reclaimed later if necessary
	   (inlineable? (block-can-be-inlined-p procedure))
	   (incoming-parse-result
	     (when inlineable?
	       (copy-for-slot-value procedure-definition)))
	   (specific-method-p?
	     (frame-of-class-p procedure 'method)))
      (unwind-protect-for-development compile-procedure-definition
	  (without-consistency-analysis (procedure)
	    (with-updates-to-representations-supressed
		(procedure 'frame-status-and-notes)
	      ;; Delay the update until both the method name and class are set.
	      ;; Note that this delays the update of all procedure slots.
	      (with-compiler-environment-and-phrase-conses

		;; Note that specific methods are now named.  The name-or-names-for
		;; frame slot is set in specific-method code below.
		;; name as a free-reference.
		(if (not specific-method-p?)
		    (if (eq name (name-or-names-for-frame procedure))
			(let ((suppress-updates-to-name-boxes t))
			  (change-slot-value
			    procedure 'name-or-names-for-frame name))
			(change-slot-value procedure 'name-or-names-for-frame name))
		    ;; Record the reference here before consistency-analysis is
		    ;; started below.  This method itself needs to be analyzed to see
		    ;; if it conflicts with other specific methods.
		    (record-free-reference 'name name))

		;; Clear any compilation flags.
		(clear-procedure-compilation-frame-flags *current-computation-frame*)
		
		;; Generate the environment descriptions.
		(multiple-value-setq (argument-list-description
				       base-environment
				       returned-values-description 
				       variable-initializations)
		  (generate-environment-descriptions args return-types local-vars))

		;; Install the argument and return type descriptions and the
		;; argument count into the procedure frame so that if any recursive
		;; calls are made to this procedure, then the appropriate types will
		;; be available.  At the bottom of this function these are cleared
		;; if there are compilation errors.
		(setf (argument-count procedure) (length
						   argument-list-description))

		(change-slot-value
		  procedure 'argument-list-description
		  (convert-description-list-to-managed-array argument-list-description))
		(change-slot-value
		  procedure 'returned-values-description
		  (convert-description-list-to-managed-array returned-values-description t))

		;; Check the first argument of specific methods and register the
		;; method if the arguments are valid.  Issue a compiler error if the
		;; method is not valid.  Unregister the old method, if defined.
		;; Also analyze items referring to the old method name, if it is
		;; changing.
		(when specific-method-p?
		  (let* ((first-argument-type?
			   (and argument-list-description
				(getfq (cdr (car argument-list-description)) :type)))
			 (first-argument-class?
			   (and (class-type-specification-p first-argument-type?)
				(type-specification-class first-argument-type?)))
			 (old-method-name? (procedure-method-name procedure))
			 (old-method-class? (procedure-method-class procedure)))
		    (when first-argument-class?
		      (if (and (eq name old-method-name?)
			       (eq first-argument-class? old-method-class?))
			  (let ((suppress-updates-to-name-boxes t))
			    (change-slot-value
			      procedure 'name-or-names-for-frame
			      (make-unique-slot-name-symbol first-argument-class? name)))
			  (change-slot-value
			    procedure 'name-or-names-for-frame
			    (make-unique-slot-name-symbol first-argument-class? name))))
		    ;; Unregister the old method name and class, even if the new
		    ;; method gets a compiler error.
		    (when old-method-name?
		      (when old-method-class?
			(unregister-method-declaration
			  old-method-name? procedure old-method-class?))
		      (when (not (eq name old-method-name?))
			;; Analyze items referring to the old name because the method
			;; name is changing.  This is needed because the method item
			;; is not named and so the analysis does not happen
			;; automatically, as when named items are renamed.
			(analyze-compiled-items-for-consistency old-method-name?)))
		    (cond
		      ((null argument-list-description)
		       (change-slot-value procedure 'procedure-method-class nil)
		       (compiler-error
			 "the procedure method must have at least one argument"))
		      ((null first-argument-class?)
		       (change-slot-value procedure 'procedure-method-class nil)
		       (compiler-error
			 "the first argument of a procedure method must be of type item"))
		      (t
		       ;; Note that during initialization, the method registration is
		       ;; done in the slot-putters for the method name and class.
		       ;; Otherwise, the registration is done here after the new
		       ;; method name and class have been been modified.

		       ;; Note that display updates for this slots are delayed.  The
		       ;; macro with-updates-to-representations-supressed is wrapping
		       ;; this form.
		       ;; Also, note that if the update was not delayed, the method
		       ;; class should be changed before the method name.  The
		       ;; slot-value-writer for the method name writes the qualified
		       ;; method name and so references both the name and the class.
		       (if (eq first-argument-class? old-method-class?)
			   (let ((suppress-updates-to-name-boxes t))
			     (change-slot-value
			       procedure 'procedure-method-class first-argument-class?))
			   (change-slot-value
			     procedure 'procedure-method-class first-argument-class?))
		       (if (eq name old-method-name?)
			   (let ((suppress-updates-to-name-boxes t))
			     (change-slot-value procedure 'procedure-method-name name))
			   (change-slot-value procedure 'procedure-method-name name))
		       (register-method-declaration
			 name procedure first-argument-class?)))))
		
		;; If there are initialization statements to be carried out, add them
		;; into the existing statement.
		(when variable-initializations
		  (setf (cdr (last variable-initializations))
			(phrase-list body-statement))
		  (setq body-statement
			(phrase-cons 'begin-statement variable-initializations)))
		;; Generate the base code body and emit compiled instructions.
		(enter-new-code-body base-environment
		  (setf (compiler-code-body-argument-descriptions? (base-code-body))
			argument-list-description)
		  (setf (compiler-code-body-local-variable-info (base-code-body))
			local-vars)
		  (let ((generated-var-spots-for-base-code-body-return nil)
			(base-code-body-return-tag (generate-new-goto-tag)))
		    (record-goto-tags body-statement)
		    (compile-procedure-statement body-statement)
		    ;; If this procedure requires return values, emit an error
		    ;; instruction in case execution falls off the end of the body.
		    (when returned-values-description
		      (unless return-statement-processed?
			(compiler-warning
			  "Procedure body completed without a return statement.  This procedure must use a return statement since it is declared to return values."))
		      (setq warning-string
			    (twith-output-to-text-string
			      (tformat 
				"Procedure body for ~a completed without a return statement.  This procedure must use a return statement since it is declared to return values."
				name)))
		      ;; this is only reached if the procedure does not exit via
		      ;; a return.
		      (emit-instruction
			'signal-error
			(compile-stack-expression
			  '(quote no-return-statement) 'symbol)
			(compile-stack-expression
			  warning-string
			  'text))
		      (reclaim-text-string warning-string))

		    ;; If there has been a reference to the jumped return tag, or if
		    ;; we need a default return statement for a procedure which
		    ;; returns no values, emit instructions for returning.
		    (when (or (null returned-values-description)
			      (goto-tag-jump-referenced?
				(goto-tag-entry-with-name
				  base-code-body-return-tag
				  goto-tags-in-compilation)))
		      (emit-instruction 'tag-statement base-code-body-return-tag)
		      (loop for description in returned-values-description
			    for var-spot-name in
			    generated-var-spots-for-base-code-body-return
			    for var-spot = (variable-spot-and-description-for-local-name
					     var-spot-name)
			    for type = (getfq description :type)
			    collect
			    (compile-procedure-var-spot var-spot type)
			      into return-expressions using phrase-cons
			    finally
			      (emit-instruction 'return-values return-expressions)))))
		
		;; Warn of any defined but unreferenced tags.
		(warn-of-unreferenced-goto-tags)
		
		;; Iterate over the code-body-entries-in-compilation and perform
		;; optimizations and back end code output for each of the code bodies.
		
		;; When there are already procedure errors, do not execute the loop
		;; across the code-body-entries.  When there are no errors yet,
		;; iterate over all of the code body entries, producing the code
		;; bodies, but still be ready to reclaim the generated code bodies if
		;; errors do occur while performing address resolution.
		
		(unless compiler-errors
		  (setq code-body-frames
			(loop repeat (length code-body-entries-in-compilation)
			      collect (make-frame 'code-body)
				using slot-value-cons))
		  (loop for code-body in code-body-frames
			for code-body-entry in code-body-entries-in-compilation
			for lexically-visible-code-bodies
			    = (generate-list-of-lexically-visible-code-bodies
				code-body-entry)
			do

		    ;; Install a back pointer from the entry to the code body frame.
		    (setf (compiler-code-body-frame code-body-entry) code-body)
		    
		    ;; Reverse the instructions so far and convert tag-statements
		    ;; which are targets of JUMP instructions into JUMP tags and
		    ;; ABORT-CALLED-CODE-BODY-INVOCATIONS instructions.
		    (setf (compiler-code-body-final-instructions code-body-entry)
			  (expand-jump-targets
			    (nreverse
			      (compiler-code-body-instructions-so-far
				code-body-entry))))

		    ;; Perform optimizations on the final set of instructions.
		    (when (null compiler-errors)
		      (setf (compiler-code-body-final-instructions code-body-entry)
			    (optimize-procedure-instructions
			      (compiler-code-body-final-instructions code-body-entry)
			      code-body-entry)))

		    ;; Add extra environment descriptors for return value positions.
		    (setf (compiler-code-body-environment-description code-body-entry)
			  (nconc
			    (compiler-code-body-environment-description
			      code-body-entry)
			    (loop for return-index from 1 to
				  (compiler-code-body-maximum-received-value-count
				    code-body-entry)
				  collect (phrase-list nil :return-value return-index)
				    using phrase-cons))))
		  
		  ;; Begin back end code emitting.  When an emitter into Lisp or C is
		  ;; written, it should be installed here.  Currently, we have one
		  ;; emitter for the stack eval interpreter.
		  (loop with base-code-body-entry
			  = (first code-body-entries-in-compilation)
			for code-body-entry in code-body-entries-in-compilation
			for lexically-visible-code-bodies
			    = (generate-list-of-lexically-visible-code-bodies
				code-body-entry)
			for byte-code-stream
			    = (make-byte-code-stream)
			    then (make-byte-code-stream-given-base-stream
				   (compiler-code-body-byte-code-stream
				     base-code-body-entry))
			do
		    (let ((current-return-values-position
			    (-f (length
				  (compiler-code-body-environment-description
				    code-body-entry))
				(compiler-code-body-maximum-received-value-count
				    code-body-entry))))
		    (setf (compiler-code-body-byte-code-stream code-body-entry)
			  byte-code-stream)
		    (when (null compiler-errors)
		      (emit-byte-code-vector-for-procedure
			byte-code-stream
			(compiler-code-body-final-instructions code-body-entry)))))
		  (loop for code-body in code-body-frames
			for code-body-entry in code-body-entries-in-compilation
			for byte-code-stream
			    = (compiler-code-body-byte-code-stream code-body-entry)
			for maximum-received-values
			    = (compiler-code-body-maximum-received-value-count
				code-body-entry)
			for byte-code-vector = nil
			for byte-codes-count fixnum = 0
			for byte-code-constants = nil
			for activity-position = nil
			do
		    (when (null compiler-errors)
		      (multiple-value-setq (byte-code-vector byte-codes-count)
			(resolve-procedure-byte-code-addresses
			  byte-code-stream code-body-entry))
		      (setq activity-position
			    (byte-code-stream-activity-information?
			      byte-code-stream)))
		    (when (null compiler-errors)
		      (setq byte-code-constants
			    (make-procedure-byte-code-constants byte-code-stream)))
		    (reclaim-byte-code-stream byte-code-stream)
		    
		    ;; Set the slots of the code body.
		    (when (null compiler-errors)
		      ;; Until the final change-slot-value for the code bodies
		      ;; slot of the procedure, these code bodies being created
		      ;; have no owner.
		      (let* ((current-block-of-dependent-frame
			       'dependent-frame-has-no-owner)
			     (environment
			       (compiler-code-body-environment-description
				 code-body-entry))
			     (environment-length (length environment)))
			;; Set the procedure slot, the return value position, maximum
			;; received value count, environment length, and envronment
			;; description of the code body.
			(setf (procedure-definition-of-code-body code-body) procedure)
			(setf (return-value-position code-body)
			      (-f environment-length maximum-received-values))
			(setf (maximum-received-value-count code-body)
			      maximum-received-values)
			(setf (environment-length code-body) environment-length)
			(change-slot-value
			  code-body 'environment-description
			  (convert-description-list-to-managed-array environment)
					;(copy-for-slot-value environment)
			  )
			(setf (surrounding-code-body-number? code-body)
			      (compiler-code-body-surrounding-body-number?
				code-body-entry))
			(setf (code-body-byte-code-body code-body)
			      (make-byte-code-body
				byte-codes-count
				byte-code-vector
				byte-code-constants
				(convert-description-list-to-managed-array environment)
				nil))
			(setf (byte-code-body-activity-description
				(code-body-byte-code-body code-body))
			      activity-position)
			(setf (code-body-error-handler-spec? code-body)
			      (copy-for-slot-value
				(compiler-code-body-error-handler-spec?
				  code-body-entry))))))
		  (let ((current-block-of-dependent-frame
			  'dependent-frame-has-no-owner))
		    (loop for code-body in code-body-frames
			  for code-body-entry in code-body-entries-in-compilation
			  do
		      (when (compiler-code-body-entry-points code-body-entry)
			(setf (code-body-entry-points code-body)
			      (list-to-managed-array
				(compiler-code-body-entry-points code-body-entry)))))))

		;; For procedures with a 'bad status, we want to put up frame notes
		;; for any unresolved free references collected in the global
		;; variable compiler-free-references before the compiler detected
		;; the error.  The consistency analysis code needs one code-body to
		;; evaluate free references and put up frame notes.
		(when compiler-errors
		  (when code-body-frames
		    (loop for code-body in code-body-frames
			  do (delete-frame code-body))
		    (reclaim-slot-value-list code-body-frames)
		    (setq code-body-frames nil))
		  (when compiler-free-references
		    (setq code-body-frames
			  (slot-value-list (make-frame 'code-body)))
		    (let ((current-block-of-dependent-frame
			    'dependent-frame-has-no-owner))
		      (setf (code-body-byte-code-body (car code-body-frames))
			    (make-byte-code-body
			      0 (allocate-byte-vector 4) nil nil nil)))))
		
		;; Put the free references into byte code body zero if it was
		;; produced.
		(let* ((first-code-body? (car code-body-frames))
		       (byte-code-body-zero?
			 (if first-code-body?
			     (code-body-byte-code-body first-code-body?))))
		  (when byte-code-body-zero?
		    (install-free-references-in-byte-code-body
		      byte-code-body-zero?
		      compiler-free-references)
		    (setq compiler-free-references nil)))

		(change-slot-value
		  procedure procedure-code-bodies-slot-name code-body-frames)

		;; Finally, if there are no errors, install the compilation into the
		;; procedure.  If there are errors, clear argument and return type
		;; information and set the frame status of the procedure to bad.
		;; In all cases install any warnings.
		(cond (compiler-errors
		       (update-frame-status procedure 'bad nil)
		       (setf (argument-count procedure) 0)
		       (change-slot-value procedure 'argument-list-description nil)
		       (change-slot-value procedure 'returned-values-description
					  nil)
		       (remove-md5-identifier procedure)
		       (change-slot-value procedure 'parse-results? nil)
		       (reclaim-slot-value incoming-parse-result))
		      (t
		       (cond (inlineable?
			      (add-md5-identifier procedure)
			      (change-slot-value procedure 'parse-results?
						 incoming-parse-result))
			     (t
			      (reclaim-slot-value incoming-parse-result)
			      (remove-md5-identifier procedure)
			      (change-slot-value procedure 'parse-results? nil)))
		       (update-frame-status procedure nil nil)))))
	    ;; Note that methods, as well as non-method
	    ;; procedures, can cause analysis of the procedure name.

	    ;; This is necessary for specific methods, even though they are not
	    ;; named, because other specific-methods of this procedure name need to
	    ;; be analyzed.  For example, there may be conflicts among methods
	    ;; defined for the same class.
	    (analyze-compiled-items-for-consistency name))
	(clear-inlining-data))
	)))






;;;; Procedure Environment Compiler




;;; The function `generate-environment-descriptions' takes the argument list,
;;; return types list, and local variable declarations lists from the procedure
;;; definition and returns the argument list description, environment
;;; description, returned values description, and the variable initialization
;;; statements for a procedure.  The returned values will be constructed from
;;; conses out of the input lists and from new phrase conses.

;; Modified to test for duplicate declarations among arguments and
;; local-variables.  - cpm, 12/31/91.

(defun generate-environment-descriptions (args return-types
					       local-vars)
  (let ((argument-list-description nil)
	(environment-description nil)
	(returned-values-description nil)
	(variable-initializations nil))
    ;; Make argument list and environment descriptions for the arguments, and
    ;; check that the types are all defined and that there are no duplicate
    ;; argument declarations.
    (loop for (arg-name type) in args
	  for remaining-args = (cdr args) then (cdr remaining-args)
	  do
      (when (member arg-name remaining-args :test #'car-eq)
	(procedure-compiler-duplicate-local-name-error arg-name))
      (setq type (convert-procedure-type-if-necessary type arg-name))
      (let ((new-description (phrase-list arg-name :type type)))
	(setq argument-list-description
	      (phrase-cons new-description argument-list-description))
	(setq environment-description
	      (phrase-cons new-description environment-description))))
    ;; Make the returned-values-description, checking that the types are
    ;; defined.
    (loop for type in return-types
	  for return-value-count from 1
	  do
      (setq type (convert-procedure-type-if-necessary type "<returned value>"))
      (setq returned-values-description
	    (phrase-cons (phrase-list :type type)
			 returned-values-description)))
    ;; Add the declared local variables to the environment description, and hang
    ;; on to a list of the initializations that need to be done as the first
    ;; statements of the procedure.  Check that the local variables do not
    ;; duplicate other local variables or arguments.
    (loop for (local-name type initialization?) in local-vars
	  for remaining-local-vars
	      = (cdr local-vars) then (cdr remaining-local-vars)
	  do
      (when (or (member local-name remaining-local-vars :test #'car-eq)
		(member local-name args :test #'car-eq))
	(procedure-compiler-duplicate-local-name-error local-name))
      (setq type (convert-procedure-type-if-necessary type local-name))
      (setq environment-description
	    (phrase-cons (phrase-list local-name :type type)
			 environment-description))
      (when initialization?
	(setq variable-initializations
	      (phrase-cons
		(phrase-list
		  'assignment-statement local-name initialization?)
		variable-initializations))))

    (values (nreverse argument-list-description)
	    (nreverse environment-description)
	    (nreverse returned-values-description)
	    (nreverse variable-initializations))))


(defvar new-descriptions nil)

(defun print-description (vector)
  (loop for index from 0
	with i = 0
	while (< i  (length vector))
	with val and desc and return-value? 
	do
    (setq val (svref vector i))
    (incff i)
    (setq desc (svref vector i))
    (incff i)
    (when (and (consp desc)
	       (eq (car desc) ':return-value))
      (setq return-value? t)
      (setq desc (cdr desc)))
    (format t "~% [~a] ~a,~a return? ~a"
	    index val desc return-value?)))




;;; The post-loading-function `convert-frame-internals-to-vectors-as-necessary',
;;; when the kb-flags qualify, converts the value of the following slots from
;;; lists to vectors:
;;;
;;;    the byte-code-body-environment-description components of byte-code-body
;;;       structures
;;;
;;;    the augment-list-description and returned-values-description slots on
;;;       procedures
;;;
;;;    the remote-procedure-returned-values-description and remote-procedure-
;;;       argument-description slots on remote-procedure-declarations
;;;
;;;    the return-value types of the box-translation-and-text slot of 
;;;	  remote-procedure-declarations
;;;
;;;    Also the argument descriptions and declarations of remote-procedure-
;;;    declarations are converted.

;;;  The macro `convert-byte-code-body-environment-description' is expanded
;;;  only in this post-loading function.

(defmacro convert-description-list-location-to-managed-array (location)
  (let ((old-value (make-symbol "OLD-VALUE")))
    `(let ((,old-value ,location))
       (when (consp ,old-value)
	 (setf ,location (convert-description-list-to-managed-array ,old-value))
	 (reclaim-slot-value ,old-value)))))

(defmacro convert-byte-code-body-environment-description (byte-code-body)
  (let ((byte-code-body-arg (gensym-make-symbol "BYTE-CODE-BODY-")))
    `(let ((,byte-code-body-arg ,byte-code-body))
       (when (byte-code-body-p ,byte-code-body-arg)
	 (convert-description-list-location-to-managed-array
	   (byte-code-body-environment-description ,byte-code-body-arg))))))

(defsetf remote-procedure-argument-description-function
    set-remote-procedure-argument-description-function)

(defsetf remote-procedure-returned-values-description-function
    set-remote-procedure-returned-values-description-function)

(def-post-loading-function convert-frame-internals-to-vectors-as-necessary
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (vectorized-procedure-environments-attributes-p)
      ;; This loop converts the value of the byte-code-body-environment-
      ;; description component of the g2-expression-cell-byte-code-body slot
      ;; of g2-expression-cell frames which can be nested within the value of
      ;; the cell-array slot of any block.
      (loop for block being each class-instance of 'block
	    for g2-cell-array? = (cell-array block)
	    do
	(when g2-cell-array?
	  (let* ((g2-cell-array-managed-array?
		   (g2-cell-array-managed-array-function g2-cell-array?))
		 (g2-expression-cell?
		   (when g2-cell-array-managed-array?
		     (managed-svref g2-cell-array-managed-array? 0))))
	    (when g2-expression-cell?
	      (convert-byte-code-body-environment-description
		(g2-expression-cell-byte-code-body-function g2-expression-cell?)))))
	;; This used to do a (case (class block) ...) which naturally was losing
	;; for methods (and would lose for any subclassing a user might do).  It
	;; would be nice if we could collapse the clauses better. Obviously a
	;; nice way of returning the "correct" code-body is needed (like for
	;; starters using a mixin for the code-body slot, or at the very least
	;; losing the conc-name in front). This whole mechanism should probably
	;; be handled by methods.  -dkuznick, 8/13/98
	(frame-class-case block
	  (procedure
	   (convert-description-list-location-to-managed-array
	     (argument-list-description block))
	   (convert-description-list-location-to-managed-array
	     (returned-values-description block))
	   (loop for code-body in (get-slot-value block procedure-code-bodies-slot-name)
		 do
	     (convert-description-list-location-to-managed-array
	       (environment-description code-body))))
	  ;; The code for remote-procedure-declarations is taken from
	  ;; the post-loading function, reformat-remote-procedure-declaration-
	  ;; descriptions, which is now wrapped with a #+rdf.
	  (remote-procedure-declaration
	   (convert-description-list-location-to-managed-array
	     (remote-procedure-returned-values-description-function block))
	   (convert-description-list-location-to-managed-array
	     (remote-procedure-argument-description-function block)))
	  ;; The remaining forms convert the values of the byte-code-body-
	  ;; environment-description components of body-code-body structures
	  ;; in rules, function-defintions, simulation-subtables, generic-
	  ;; simulation-formulas, and image-definitons.
	  (rule
	   (convert-byte-code-body-environment-description
	     (get-slot-value block 'rule-byte-code-body)))
	  (function-definition
	   (convert-byte-code-body-environment-description
	     (get-slot-value block 'function-definition-byte-code-body)))
	  (simulation-subtable
	   (convert-byte-code-body-environment-description
	     (get-slot-value block 'simulation-subtable-byte-code-body))
	   (convert-byte-code-body-environment-description
	     (get-slot-value block 'simulation-subtable-initial-value-byte-code-body)))
	  (generic-simulation-formula
	   (convert-byte-code-body-environment-description
	     (get-slot-value block 'generic-simulation-formula-byte-code-body))
	   (convert-byte-code-body-environment-description
	     (get-slot-value block 'generic-simulation-initial-value-byte-code-body)))
	  (image-definition
	   (convert-byte-code-body-environment-description
	     (get-slot-value block 'image-definition-saveable-image-info))))))))






;;; `convert-description-list-to-managed-array' converts a description list to a vector
;;; in the specified format. There needs to be special handling of return-values-lists
;;; since they do not necesssarily have an id per se

(defun convert-description-list-to-managed-array (description-as-list
						   &optional (return-values-list? nil)
						   (static-p nil))
  (declare (ignore return-values-list?))
  (when description-as-list
    (let* ((vector-length (*f 2 (length description-as-list)))
	   (description-vector
	     (if static-p
		 (allocate-managed-array-static vector-length)
		 (allocate-managed-array vector-length))))
      (loop for description in description-as-list
	    with id and keyword and value
	    for description-length = (if (consp description)
					 (length description)
					 0)

	    with index = 0
	    do
	(cond ((consp description)
	       (setq id (pop description))
	       (setq value (second description))
	       (cond ((keywordp id)
		      (setq keyword id)
		      (setq value (car description))
		      (setq id nil)
		      (setf (managed-svref description-vector index)
			    (copy-for-slot-value id)))
		     (t
		      (setf (managed-svref description-vector index) (copy-for-slot-value id))
		      (setq keyword (car description)))))
	      (t
	       (setq value description)
	       (setq keyword ':type)))
	(incff index) 
	(cond ((and (eq keyword ':type)
		    (> description-length 2))
	       (setf (managed-svref description-vector index)
		     (slot-value-cons ':general-description
				      (slot-value-cons
					keyword
					(if (eq (car description) ':type)
					    (copy-for-slot-value (cdr description))
					    (copy-for-slot-value description))))))
	      ((eq keyword ':type)
	       (setf (managed-svref description-vector index) (copy-for-slot-value value)))
	      
	      (t
	       (setf (managed-svref description-vector index)
		     (slot-value-cons ':general-description (copy-for-slot-value description))
		     ))) 
	(incff index))
      description-vector)))

(defun allocate-managed-array-static (length
				       &optional (dont-initialize nil))
  (declare (type fixnum length))
  #+development
  (when (> length maximum-in-place-array-size)
    (error "Can't make a static managed array ~a elements long." length))
  (let ((spine-vector
	  (with-permanent-array-creation
	    (make-array
	      (+f length managed-array-index-offset)))))
    (setf (managed-array-identity-marker spine-vector)
	  managed-array-unique-marker)
    (setf (managed-array-length spine-vector) length)
    (unless dont-initialize
      (fill-managed-array spine-vector nil))
    spine-vector))

(defun convert-procedure-type-if-necessary (type &optional local-name)
  (cond ((and (valid-type-specification-p type)
	      (type-specification-subtype-p type 'item-or-datum))
	 (when (class-type-specification-p type)
	   (record-free-reference
	     'class (type-specification-class type)))
	 type)
	;; The following transform is needed because the parser can
	;; sometimes let the symbol quantity through instead of accurately
	;; transforming it into number.  -jra 3/29/91
	((eq type 'quantity)
	 'number)
	((eq type 'time-stamp)
	 (warn-of-obsolete-time-stamp-type local-name)
	 'number)
	(t
	 (unknown-type-compiler-error local-name type)
	 'item-or-datum)))

(defun warn-of-obsolete-time-stamp-type (local-name)
  (write-compiler-warning
    (tformat
      "The type TIME-STAMP for the argument ~a is being phased out.  This ~
       type should be replaced with quantity, integer, or float.  Quantity ~
       will be used for now."
      local-name)))

(defun unknown-type-compiler-error (local-name type)
  (compiler-bug
    "local-name declarations"
    "The type ~a was given for the local-name ~a, but is not a valid type."
    type local-name))






;;;; Procedure Statement, Expression, and Designation Compilers


(defun get-class-and-type-of-variable-designation (variable-designation)
  (let ((code-body? (car code-body-entries-in-compilation))
	(type? nil)
	(class? nil))
    (when code-body?
      (when (and (consp variable-designation)
		 (eq (car-of-cons variable-designation) 'var-spot))
	(setq type? (var-spot-type variable-designation
				   lexically-visible-code-bodies))
	(when (and (consp type?) (eq (car type?) 'class))
	  (setq class? (second type?))))
      (unless type?
	(loop for var-designation in (compiler-code-body-local-variable-info
				       code-body?)
	      until type?
	      do
	  (when (eq (car var-designation) variable-designation)
	    (setq type? (second var-designation)))
	  (when (and (consp type?) (eq (car type?) 'class))
	    (setq class? (second type?)))))
      (unless type?
	(loop for var-designation in (compiler-code-body-argument-descriptions?
				       code-body?)
	      until type?
	      do
	  (when (eq (car var-designation) variable-designation)
	    (setq type? (getfq  (cdr var-designation )':type  nil))
	    (when (and (consp type?) (eq (car type?) 'class))
	      (setq class? (second type?))))
	      ))
      (unless type?
	(loop for var-designation in (compiler-code-body-environment-description
				       code-body?)
	      until type?
	      do
	  (when (eq (car var-designation) variable-designation)
	    (setq type? (getfq  (cdr var-designation )':type  nil))
	    (when (and (consp type?) (eq (car type?) 'class))
	      (setq class? (second type?))))
	      )))
    (values class? type?)))

(defun get-type-of-variable-designation (variable-designation)
  (multiple-value-bind (ignore type?)
      (get-class-and-type-of-variable-designation variable-designation)
    (declare (ignore ignore))
    type?))


;;; If you have problemns with inlining change this to t

(defparameter no-inlining? nil)

(declare-system-procedure-function g2-disable-inlining t)

(defun-funcallable g2-disable-inlining ()
  (setq no-inlining? t))

(declare-system-procedure-function g2-enable-inlining t)

(defun-funcallable g2-enable-inlining ()
  (setq no-inlining? nil))
  
;;; `destructure-statement-designation-locals-args-across?' is a utility for use
;;; by the inlining facility. It prevents each caller from having to worry about
;;; whether the statement is a "call" or a "call-assignment"

(defun destructure-statement-designation-locals-args-across? (statement)
  (let ((designation nil)
	(locals nil)
	(args nil)
	(across? nil))
    (when (consp statement)
      (cond ((eq (car statement) 'call-action)
	     (gensym-dstruct-bind
		 ((nil statement-designation statement-args statement-across?) statement)
	       (setq designation statement-designation)
	       (setq args statement-args )
	       (setq across? statement-across?)))
	    ((or (eq (car statement) 'call-assignment-statement)
		 (eq (car statement) 'call-assignment-action))
	     (gensym-dstruct-bind
		 ((nil statement-local-names statement-designation statement-args statement-across?) 
		  statement)
	       (setq locals statement-local-names)
	       (setq designation statement-designation)
	       (setq args statement-args )
	       (setq across? statement-across?)))))
    (values designation locals args across? nil)))


;;; `call-statements' is a list of all statements which would satisfy our
;;; call-next-method requirement.

(defparameter call-statements `(call-assignment-statement
				 call-next-method-assignment-statement
				 call-next-method-statement
				 call-action
				 call-assignment-action))




;;; `add-md5-identifier' adds the md5 identifer using the text-being-edited
;;; of the current-edit-state. This is a little on the evil side.  We cannot
;;; use the definition of the item currently undergoing compilation because it
;;; does not get set


(defun add-md5-identifier (item)
  (let ((text text-of-definition-being-compiled))
    (cond ((of-class-p item 'procedure)
	   (change-slot-value item 'md5-identifier?
			      (md5-id-string text)))
	  (t
	   #+development
	   (break "add-md5-identifier called on non procedure")))))

(defun remove-md5-identifier (item)
  (cond ((of-class-p item 'procedure)
	 (change-slot-value item 'md5-identifier? nil))
	(t
	 #+development
	 (break "remove-md5-identifier called on non procedure"))))




;;; The function `md5-id-string' takes a text (the slot-value structure which
;;; has lists of strings) this function will generate and return a wide string
;;; containing a MD5 digest of the given text.  (Basically, MD5 identifiers are
;;; a really good checksums.  See the RFCs for it at InterNIC for details.)

(defun md5-id-string (definition-text)
  (let* ((digest (obtain-simple-gensym-string 16))
	 (result (obtain-text-string 8))
	 (definition-text-as-text-string
	     (convert-text-to-text-string definition-text))
	 (definition-text-as-gensym-string
	     (wide-string-to-gensym-string definition-text-as-text-string)))
    (init-MD5-context)	
    (update-MD5-context definition-text-as-gensym-string)
    (finalize-MD5-context digest)
    (loop for index from 0 below 8
	  for digest-index = (ashf index 1)
	  do
      (setf (charw result index)
	    (code-charw
	      (+f (ashf (char-code (schar digest digest-index)) 8)
		  (char-code (schar digest (1+f digest-index)))))))
    (reclaim-simple-gensym-string digest)
    (reclaim-text-string definition-text-as-text-string)
    (reclaim-gensym-string definition-text-as-gensym-string)
    result))




;;; The macro `enter-new-inlining-data-context' pushes a new context onto
;;; inlining-data.  Note that there is only ONE inlining data structure ever
;;; allocated the outermost caller of the inlining facility is expected to have
;;; an unwind protect form that clears this structure on exit. If it does not,
;;; old context will still be in the strucutre (with reclaimed conses no less)
;;; and life won't be pleasant. -rdf, 2/27/96

(defmacro enter-new-inlining-data-context (item return-receiver-compilations code-body &body forms)
  (let ((receivers (gensym))
	(the-code-body (gensym))
	(the-item (gensym)))

    `(let ((,the-item ,item)
	   (,receivers ,return-receiver-compilations)
	   (,the-code-body ,code-body))
       ;; GENSYMCID-1257: After editing some procedures that can be compiled and
       ;; editing some properties, these procedures can no longer be compiled (bug report)
       (phrase-push
	 ,the-code-body (inlining-data-calling-code-body inlining-data))
       (phrase-push
	 ,the-item (inlining-data-context-stack inlining-data))
       (phrase-push
	 ,receivers (inlining-data-recieved-value-compilations inlining-data))
       (phrase-push (length (compiler-code-body-environment-description
			      ,the-code-body))
		    (inlining-data-environment-context-start-points inlining-data))
       (phrase-push (length (compiler-code-body-local-variable-info
			      ,the-code-body))
		    (inlining-data-local-var-context-start-points
		      inlining-data))
       ;; Defeasible switches
       (unless (block-is-optimizable-p ,the-item)
	 (setf (inlining-data-optimizable-p-context inlining-data) nil))
       ,@forms
       #+development
       (unless (eq (car (inlining-data-context-stack inlining-data))
		   ,the-item)
	 (break "inlining context ~a not what expected ~a"
		(car (inlining-data-context-stack inlining-data))
		,the-item))
       ;; First take care of keeping track of already inlined contexts slot.
       ;; This is used for tag mangling for multiple inlining of the same
       ;; procedure -dkuznick, 8/3/98
       (let* ((most-recent-inlined-context (car (inlining-data-context-stack
						  inlining-data)))
	      (already-inlined-context?
		(assq most-recent-inlined-context
		      (inlining-data-contexts-inlined-already inlining-data))))
	 (if already-inlined-context?
	     (incff (cdr-of-cons already-inlined-context?))
	     (phrase-push (phrase-cons most-recent-inlined-context 1)
			  (inlining-data-contexts-inlined-already inlining-data))))
       (setf (inlining-data-calling-code-body inlining-data)
	     (cdr (inlining-data-calling-code-body inlining-data)))
       (setf (inlining-data-context-stack inlining-data)
	     (cdr (inlining-data-context-stack inlining-data)))
       (setf (inlining-data-environment-context-start-points inlining-data)
	     (cdr (inlining-data-environment-context-start-points inlining-data)))
       (setf (inlining-data-local-var-context-start-points inlining-data)
	     (cdr (inlining-data-local-var-context-start-points inlining-data)))
       (setf (inlining-data-recieved-value-compilations inlining-data)
	     (cdr (inlining-data-recieved-value-compilations inlining-data)))
       )))





;;; `in-inlining-context?' is designed to just return a truth-value, while
;;; `inlining-context?' returns the actual context.

(defun in-inlining-context? ()
  (if  (inlining-data-context-stack inlining-data)
       t
       nil))

(defun inlining-context? ()
  (if  (inlining-data-context-stack inlining-data)
       t
       nil))


(defun inlining-data-recieved-value-compilations? ()
  (if  (inlining-data-recieved-value-compilations inlining-data)
       (car (inlining-data-recieved-value-compilations inlining-data))
       nil))


;;; `get-procedure-method-name-in-context',
;;; `get-procedure-method-class-in-context' and
;;; `environment-index-ok-in-this-context?' shadow items appropriately
;;; through multiple nested calls to the inlining facility

(defun get-procedure-method-name-in-context ()
  (let ((context? (inlining-data-context-stack inlining-data)))
    (cond
      (context?
       (procedure-method-name (car context?)))
      (t
       (procedure-method-name *current-computation-frame*)))))

(defun environment-index-ok-in-this-context? (index)
  (if (inlining-data-environment-context-start-points inlining-data)
      (> index
	 (- (car (inlining-data-environment-context-start-points inlining-data)) 1))
      ;; we're not in an inlining context
      t))

(defun get-procedure-method-class-in-context ()
  (let ((context? (inlining-data-context-stack inlining-data)))
    (cond
      (context?
       (procedure-method-class (car context?)))
      (t
       (procedure-method-class *current-computation-frame*)))))


(defun get-procedure-argument-descriptions-in-context ()
  (let ((context? (inlining-data-context-stack inlining-data)))
    (cond
      (context?
       (collect-description-into-list-using-phrase-conses
	 (argument-list-description (car context?))))

      (t
       (compiler-code-body-argument-descriptions? (base-code-body))))))

(defun get-procedure-in-context ()
  (let ((context? (inlining-data-context-stack inlining-data)))
    (if context?
	(car context?)
	*current-computation-frame*)))

;;; `mangle-symbol-using' will return a symbol mangled by
;;; "{procedure-name}symbol" or "{class::method}symbol" as apropriate.  The
;;; inline-call-number argument is an optional argument to stick on right before the
;;; "}".  This is currently used by inlining tags so multiple inlining of a single
;;; procedure/method works properly.

(defun mangle-symbol-using (symbol-to-mangle item-for-mangling-prefix
					     &optional inline-call-number)
  (intern-text-string
    (if (method-p item-for-mangling-prefix)
	(tformat-text-string
	  "{~a::~a~@[~a~]}~a"
	  (procedure-method-class item-for-mangling-prefix)
	  (procedure-method-name item-for-mangling-prefix)
	  inline-call-number
	  symbol-to-mangle)
	(tformat-text-string
	  "{~a~@[~a~]}~a"
	  (name-or-names-for-frame item-for-mangling-prefix)
	  inline-call-number
	  symbol-to-mangle))))

;;; `mangle-tag-in-context' mangles a tag correctly depending on the current
;;; context.

(defun mangle-tag-in-context (tag-name)
  (if (fixnump tag-name)
      tag-name				;the special tags don't need mangling
      (let ((procedure-in-context (get-procedure-in-context)))
	(mangle-symbol-using tag-name
			     procedure-in-context
			     (get-inline-call-number procedure-in-context)))))


;;; The function `compile-inline-substitution' is designed to take a function
;;; or procedure parse and compile in a way that assures that the inilining is
;;; hygenic.

(defun compile-inline-substitution
    (parsed-statements code-body original-statement item-being-inlined)
  (let (argument-list-description
	 base-environment
	 returned-values-description 
	 variable-initializations
	 (added-environment-length 0) 
	 arg-compilations
	 (return-local-compilations nil)
	 (inlining-method? (method-p item-being-inlined)))
    (record-free-reference 'inline
			   (phrase-list
			     (if inlining-method?
				 (procedure-method-class item-being-inlined)
				 nil)
			     (if inlining-method?
				 (procedure-method-name item-being-inlined)
				 (name-or-names-for-frame item-being-inlined))
			     (argument-count item-being-inlined)
			     (copy-for-phrase
			       (md5-identifier? item-being-inlined))))
    (multiple-value-bind (calling-designation calling-locals calling-args
					      calling-across?)
	(destructure-statement-designation-locals-args-across?
	  original-statement)
      (declare (ignore calling-designation calling-across?))
      (when (memq (car original-statement) call-statements)
	(setq call-statement-processed? t))

      (gensym-dstruct-bind ((nil args return-types local-vars body-statement)
			   parsed-statements)
	;; Note that these two compilations MUST be done prior to entering the
	;; new inlining-data-context
	(setq arg-compilations
	      (loop for arg in calling-args
		    for type in (collect-types-into-list-using-phrase-conses
				  (argument-list-description item-being-inlined))
		    collect (compile-stack-expression arg type)
		      using phrase-cons))
	;; This was partially copied from how procedures fill results:
	;; see (def-procedure-statement-compiler (call-assignment-statement ...))
	(loop with var-spot with description
	      for var-spot-name in calling-locals
	      do
	  (multiple-value-setq (var-spot description)
	    (variable-spot-and-description-for-local-name var-spot-name))
	  (when (null var-spot)
	    (setq var-spot (generate-new-variable-spot 'item-or-datum))
	    (procedure-compiler-missing-local-name-error var-spot-name))
	  (phrase-push var-spot return-local-compilations))
	(setq return-local-compilations (nreverse return-local-compilations))

	(enter-separate-lexical-tag-layer ; to not see outer tags -dkuznick, 7/30/98
	  (enter-new-inlining-data-context
	    item-being-inlined return-local-compilations code-body
	    ;; Generate the environment descriptions.
	    (multiple-value-setq (argument-list-description
				   base-environment
				   returned-values-description 
				   variable-initializations)
	      (generate-environment-descriptions args return-types local-vars))

	    (setq added-environment-length (length base-environment))
	    
	    
	    (setf (compiler-code-body-environment-description
		    code-body)
		  (nconc (compiler-code-body-environment-description
			   code-body)
			 base-environment))
	    (setf (compiler-code-body-local-variable-info code-body)
		  (nconc (compiler-code-body-local-variable-info code-body)
			 (copy-list-using-phrase-conses local-vars)))
	    (loop for description in argument-list-description
		  for name? = (car description)
		  for arg-compilation in arg-compilations
		  for arg-spot = (variable-spot-and-description-for-local-name name?)
		  do
	      (emit-instruction 'assign-local-var arg-spot arg-compilation))
	    
	    ;; Also need to add the variable initializations.
	    (when variable-initializations
	      (setf (cdr (last variable-initializations))
		    (phrase-list body-statement))
	      (setq body-statement
		    (phrase-cons 'begin-statement variable-initializations)))
	    (let ((base-code-body-return-tag (generate-new-goto-tag)))
	      (record-goto-tags body-statement)
	      (compile-procedure-statement body-statement)
	      (emit-instruction 'tag-statement base-code-body-return-tag))
	    
	    (loop for description in  (compiler-code-body-environment-description
					code-body)
		  for index from 0
		  with start-index = (car (inlining-data-environment-context-start-points inlining-data))
		  while (<f index (+f start-index added-environment-length))
		  do
	      (when (and (car description)
			 (>=f index start-index))
		(setf (car description)
		      (mangle-symbol-using (car description)
					   item-being-inlined))))))))))


;;; The function `compile-procedure-statement' takes a procedure statement and
;;; compiles it by looking up the procedure-statement-compiler for that
;;; statement and executes it.

;;; We should consider adding some support here for better error and warning
;;; messages.  If this function could bind something useful about what statement
;;; is being compiled, and where that could be found in the user's big procedure
;;; definition.

(defun compile-procedure-statement (statement)
  (let* ((current-computation-component-particulars
	   (phrase-list
	     'procedure-statement
	     statement
	     '*current-computation-frame*))
	 (statement-name (if (consp statement) (car statement)))
	 (statement-compiler nil)
	 (action-compiler nil))
    ;;if we can inline this beast we do it here
    (when (symbolp statement-name)
      (setq action-compiler
	    (action-compiler statement-name))
      (when (null action-compiler)
	(setq statement-compiler
	      (procedure-statement-compiler statement-name))))
    (cond (action-compiler
	   (let ((prolog-stream (make-pseudo-instruction-stream))
		 (epilog-stream (make-pseudo-instruction-stream)))
	     (funcall-simple-compiled-function
	       action-compiler statement nil t prolog-stream epilog-stream)
	     (merge-pseudo-instruction-stream prolog-stream)
	     (merge-pseudo-instruction-stream epilog-stream)))
	  (statement-compiler
	   (funcall-simple-compiled-function statement-compiler statement))
	  ((and (symbolp statement-name) statement-name)
	   (compiler-bug
	     "statement compiler"
	     "The statement ~A is not defined." statement-name))
	  (t
	   (compiler-bug
	     "statement compiler"
	     "The statement ~a is not in the correct format."
	     statement)))
;    #+development
;    (emit-instruction 'check-stack)
    ))




;;; The function `compile-procedure-var-spot' takes a var-spot and compiles it
;;; into a stack node tree referencing the value in the var-spot.  This function
;;; is only available in the stack-eval implementation of procedures.

;;; Note that at this time, var spots can be handed to
;;; compile-stack-expression-into-nodes, though this causes the symbol VAR-SPOT
;;; to no longer be a valid user-defined function name.  -jra 4/4/91

(defun compile-procedure-var-spot (var-spot required-type)
  (compile-stack-expression-into-nodes var-spot required-type))
  
  
  

;;; The function `compile-procedure-expression' takes a procedure expression and
;;; and the desired return value type of the expression, and returns two values.
;;; The first is a phrase-cons expression which is the compiled version of the
;;; given expression.  The second value is the actual type which the expression
;;; will return.  The expression will have all local names replaced with
;;; references to var spot positions in the environment.

(defun compile-procedure-expression (expression &optional required-type)
  (let ((expression-bound-local-names expression-bound-local-names))
    (compile-stack-expression-into-nodes expression required-type)))

(defun compile-stack-expression (expression required-type)
  (let ((expression-bound-local-names expression-bound-local-names))
    (compile-stack-expression-into-nodes expression required-type)))



;;; The function `record-free-references-of-role' takes a role and
;;; will record any free references produced by that role.  One example of this
;;; is the name of a dynamic relation used in the role.  Note that this function
;;; will record no free references for atomic (symbol) roles, since the presence
;;; or absence of a domain determines whether that role is an attribute or a
;;; class.

(defun record-free-references-of-role (role &optional domain-type-list?)
  (let ((simple-role (simple-role-of-role role)))
    (when (consp simple-role)
      (let ((type? (type-specification-of-role simple-role)))
	(when (class-type-specification-p type?)
	  (record-free-reference
	    'class (type-specification-class type?))))
      (cond ((eq (car simple-role) 'related)
	     (record-free-reference 'relation (second simple-role)))
	    ((eq (car simple-role) 'at-port)
	     (record-free-reference
	       'port-name (phrase-cons (second simple-role) nil)))
	    ((eq (car simple-role) 'class-qualified-method)
	     (record-free-reference
	       'class-qualified-method
	       (phrase-list (third simple-role)(second simple-role))))
	    ((eq (car simple-role) 'text-of-attribute)
	     (compiler-warning-if-superseded-attribute (second simple-role))
	     (let ((attribute-role (second simple-role)))
	       (if (and (=f (length domain-type-list?) 1)
			(class-type-specification-p (car domain-type-list?)))
		   (if (and (consp attribute-role)
			    (eq (car-of-cons attribute-role)
				'class-qualified-name))
		       (record-free-reference
			 'class-qualified-attribute-of-class
			 (phrase-list
			   (third attribute-role)
			   (second attribute-role)
			   (type-specification-class (car domain-type-list?))))
		       (record-free-reference
			 'attribute-of-class
			 (phrase-cons
			   attribute-role
			   (type-specification-class (car domain-type-list?)))))
		   (record-free-reference 'attribute attribute-role))))
	     (t nil)))))






;;;; Procedure Instruction Optimizations




;;; The function `optimize-procedure-instructions' is called with the set of
;;; procedure instructions after all code has been emitted.  This function
;;; should perform whatever optimizations is can at the instruction level.  The
;;; one optimization implemented so far is dead code removal.

(defun optimize-procedure-instructions (procedure-instructions code-body-entry)
  (let ((optimized-procedure-instructions procedure-instructions))
    (when optimized-procedure-instructions 
      (setq optimized-procedure-instructions
	    (short-cut-branch-to-branch-procedure-instructions
	      optimized-procedure-instructions))
      (setq optimized-procedure-instructions
	    (remove-dead-procedure-instructions
	      optimized-procedure-instructions code-body-entry)))
    optimized-procedure-instructions))




;;; The function `short-cut-branch-to-branch-procedure-instructions' takes a
;;; list of procedure instructions and performs an optimization which finds all
;;; tag statements which immediately preceed unconditional branch statements.
;;; Branches to this tag should then be given a "short cut" to the target of the
;;; branch following the tag.  Note that this forwarding may proceed through
;;; further levels, but that if a circular path is found, then all forwarding
;;; should stop for those tags.  If any tag statements are found which can be
;;; forwarded, then the instruction set is traversed, replacing tags with their
;;; short cut tags.  This will leave the forwarded tag statements without any
;;; branches referencing them, and they will be removed by the dead code
;;; analyzer.

(defun short-cut-branch-to-branch-procedure-instructions (procedure-instructions)
  (let ((tags-to-forward-alist (collect-forwardable-goto-tags
				 procedure-instructions)))
    (when tags-to-forward-alist
      (let ((procedure-branch-short-cuts tags-to-forward-alist))
	(replace-goto-tags-with-instruction-addresses
	  procedure-instructions)))
    procedure-instructions))




;;; The function `collect-forwardable-goto-tags' takes a list of procedure
;;; instructions and searches them for tag-statements which are immediately
;;; followed by unconditional branches.  This function forms an alist of the
;;; tags in the tag-statements (sources) and the tags in branch statements
;;; (targets) following the tag-statement.  This is the alist of the
;;; "short-cuts" which may be taken, from the source to the target.  This list
;;; is further analyzed by checking if any of the targets of short cuts are
;;; themselves sources of further short cuts.  If this is possible, a further
;;; short-cut is taken.  A test is made for circular short-cuts while doing the
;;; second layer analysis.  If a pathway is circular, then short-cuts are made
;;; from all source tags to one of the target tags.  This approach allows the
;;; dead code analyzer to find and eliminate dead code which contains a circular
;;; set of branches.

;;; This function returns a phase-cons alist of source to target tag short-cuts.

(defun collect-forwardable-goto-tags (procedure-instructions)
  (let ((short-cuts nil)
	(combined-sources-to-target nil))
    (loop for instruction-cons on procedure-instructions
	  do
      (when (and (eq (caar instruction-cons) 'tag-statement)
		 (eq (caadr instruction-cons) 'branch))
	;; Found a short cut.
        (let ((source (second (first instruction-cons)))
	      (target (second (second instruction-cons))))
	  (loop named combine
		for cs-to-t-cons in combined-sources-to-target
		for combined-sources = (car cs-to-t-cons)
		for combined-target = (cdr cs-to-t-cons)
		do
	    ;; If shared targets or if current target is in the combined
	    ;; sources, add source to combined-sources.
	    (cond ((or (eq target combined-target)
		       (memq target combined-sources))
		   (setf (car cs-to-t-cons)
			 (phrase-cons source combined-sources))
		   (return-from combine nil))
		  ;; If short-cut source is the combined-target, change the
		  ;; combined-target to the short-cut target, and add the
		  ;; current source to the combined-sources.
		  ((eq source combined-target)
		   (setf (cdr cs-to-t-cons) target)
		   (setf (car cs-to-t-cons)
			 (phrase-cons source combined-sources))
		   (return-from combine nil)))
	    finally
	      (setq combined-sources-to-target
		    (phrase-cons (phrase-cons (phrase-cons source nil) target)
				 combined-sources-to-target))))))
    (loop for combined-cons in combined-sources-to-target
	  for sources = (car combined-cons)
	  for target = (cdr combined-cons)
	  do
      (loop for source-cons = sources then next-source-cons
	    for next-source-cons = (cdr source-cons)
	    while source-cons
	    do
	;; If this is the last source tag for this target, then re-use the
	;; combined-cons in the short-cuts list.  Most often there will be only
	;; one source per target.
	(cond ((null next-source-cons)
	       (setf (cdr combined-cons) short-cuts)
	       (setq short-cuts combined-cons)
	       (setf (car combined-cons) source-cons)
	       (setf (cdr source-cons) target))
	      (t
	       (setf (cdr source-cons) target)
	       (setq short-cuts
		     (phrase-cons source-cons short-cuts))))))
    short-cuts))




;;; The function `remove-dead-procedure-instructions' takes a list of procedure
;;; instructions for a code body and removes those instructions which cannot be
;;; reached.  The analysis proceeds as follows.  After every unconditional
;;; branch instruction, all instructions up to but not including the next
;;; tag-statement should be removed.  Since the train of execution certainly
;;; stops at a close or branch, and execution can only resume again at a tag,
;;; then then all code inbetween is certainly unreachable.  Tags which are not
;;; reachable are removed and the optimization retried after each pass in which
;;; tags are removed.

;;; Note that jump-tags are never removed, even if the jump instruction that
;;; transformed this tag into a jump-tag has itself been removed.  This is true
;;; since dead-code elimination occurs only within the confines of a single
;;; code-body, and does not extend and reachability proofs for tags across
;;; code-body boundaries.  Therefore, we have no information about the
;;; reachability of jump tags and must assume that all of them are reachable.
;;; Note that this is used by error handling, in that it makes its targets into
;;; jump instructions so that they will not be eliminated.  If we attempt
;;; cross-code-body dead code elimination, we will have to use these error-specs
;;; are further roots of these proofs.  -jra 7/3/96

(defun remove-dead-procedure-instructions
    (procedure-instructions code-body-entry)
  (declare (ignore code-body-entry))
  (let ((unconditional-branches
	  '(branch jump return-values signal-error close-code-body
	    case-dispatch pause execute-antecedent))
	(entry-points '(tag-statement jump-tag-statement))
	(tags-to-eliminate nil)
	(leading-cons (phrase-cons nil procedure-instructions)))
    (loop for code-eliminated? = nil
	  for referenced-tags = nil
	  for existing-tags = nil
	  do
      (loop with cons-trailer = leading-cons
	    with instruction-cons = (cdr leading-cons)
	    while instruction-cons
	    for instruction = (car instruction-cons)
	    for instruction-name = (car instruction)
	    do
	(loop for tag in (tag-references-in-instruction instruction) do
	  (if (or (fixnump tag) (symbolp tag))
	      (add-to-set referenced-tags tag phrase)
	      (compiler-bug
		"dead code optimizer"
		"Malformed tag ~a in ~a instruction."
		tag (car instruction))))
	(cond ((and (eq instruction-name 'branch)
		    (eq (car (second instruction-cons)) 'tag-statement)
		    (eql (second instruction)
			 (second (second instruction-cons))))
	       ;; Eliminate this branch to the immediately following
	       ;; tag-statement.
	       (setq code-eliminated? t)
	       (setq instruction-cons (cdr instruction-cons))
	       (setf (cdr cons-trailer) instruction-cons))
	      ((memq instruction-name unconditional-branches)
	       (let ((restart-point-or-end
		       (loop for restart-cons on (cdr instruction-cons) do
			 (when
			     (and (memq (caar restart-cons) entry-points)
				  (or (neq (caar restart-cons) 'tag-statement)
				      (not (member (second (car restart-cons))
						   tags-to-eliminate))))
			   (return restart-cons))
			     finally (return nil))))
		 (when (neq (cdr instruction-cons) restart-point-or-end)
		   (setq code-eliminated? t)
		   (setf (cdr instruction-cons) restart-point-or-end))
		 (setq cons-trailer instruction-cons)
		 (setq instruction-cons (cdr instruction-cons))))
	      ((eq instruction-name 'tag-statement)
	       (cond ((member (second instruction) tags-to-eliminate)
		      (setq code-eliminated? t)
		      (setq instruction-cons (cdr instruction-cons))
		      (setf (cdr cons-trailer) instruction-cons))
		     (t
		      (setq existing-tags
			    (phrase-cons
			      (second instruction) existing-tags))
		      (setq cons-trailer instruction-cons)
		      (setq instruction-cons (cdr instruction-cons)))))
	      (t
	       (setq cons-trailer instruction-cons)
	       (setq instruction-cons (cdr instruction-cons)))))
      (setq tags-to-eliminate nil)
      (loop for tag in existing-tags
	    do
	(when (not (member tag referenced-tags))
	  (setq tags-to-eliminate (phrase-cons tag tags-to-eliminate))))
	  while (or code-eliminated? tags-to-eliminate))
    (cdr leading-cons)))






;;;; Procedure Tag Collection





;;; The function `warn-of-unreferenced-goto-tags' simply loops across the
;;; passed list of procedure tag entries and warns of any of them which were
;;; declared by the user and not referenced.  Note that it is a usual situation
;;; for a tag generated by the compiler (i.e. a negative integer tag name) to
;;; not be referenced.

(defun warn-of-unreferenced-goto-tags ()
  (loop for entry in goto-tags-in-compilation
	for name = (goto-tag-name entry)
	do
    (when (not (or (goto-tag-referenced? entry)
		   (goto-tag-jump-referenced? entry)
		   (and (typep name 'fixnum)
			(<f name 0))))
      (write-compiler-warning
	(tformat "The tag ~a was declared but not referenced."
		 name)))))




;;; The function `expand-jump-targets' takes a list of instructions and a list
;;; of procedure tag entries.  It loops over the instructions, expanding those
;;; tag-statements which are referenced as targets of jump instructions.  The
;;; expansion involves inserting instructions for receiving the jump and
;;; aborting called code body invocations, and also a pair of instructions which
;;; branch themselves around the abort when flow of control passes naturally
;;; into this section of code.

;;; This branch around is accomplished by having two addresses for tags; the
;;; first is the normal address which will be used by branches to this tag from
;;; within the same code body, and the second is the address to be used by
;;; "jump" references to this tag.  Only "jump referenced" tags will have both
;;; addresses.

(defun expand-jump-targets (instructions)
  (loop with head-of-instructions = (phrase-cons nil instructions)
	for list-trailer = head-of-instructions then instruction-cons
	for instruction-cons = (cdr-of-cons list-trailer)
	while instruction-cons
	do
    (when (eq (car-of-cons (car-of-cons instruction-cons)) 'tag-statement)
      (let* ((tag-name (car-of-cons (cdr-of-cons (car-of-cons instruction-cons))))
	     (entry (goto-tag-entry-with-name
		      tag-name goto-tags-in-compilation)))
	(cond ((null entry)
	       (compiler-bug
		 "tags directory"
		 "The tag ~a was in instructions, but not in the directory ~
                  of tags at jump expansion time."
		 tag-name))
	      ((goto-tag-jump-referenced? entry)
	       (let ((new-instructions
		       (phrase-list
			 (phrase-list 'branch tag-name)
			 (phrase-list 'jump-tag-statement tag-name)
			 (phrase-list 'abort-called-code-bodies))))
		 (setf (cdr list-trailer) new-instructions)
		 (setf (cdr (last new-instructions)) instruction-cons))))))
	finally
	  (return (cdr head-of-instructions))))




;;; The function `collect-goto-tag-addresses' takes the list of
;;; procedure instructions and a list of procedure tag entries, and mutates the
;;; tag entries to set the addresses for branches and jumps to those tags.

(defun collect-goto-tag-addresses (instructions)
  (let ((leading-cons (phrase-cons nil instructions)))
    (loop with tag
	  with entry
	  with instruction-address fixnum = 0
	  with trailer = leading-cons
	  with instruction-cons = instructions
	  while instruction-cons
	  for instruction-name = (caar instruction-cons)
	  do
      (cond ((eq instruction-name 'tag-statement)
	     (setq tag (second (car instruction-cons)))
	     (setq entry (goto-tag-entry-with-name
			   tag goto-tags-in-compilation))
	     (if (null entry)
		 (compiler-bug
		   "address resolver"
		   "The tag ~a had no entry at address generation time."
		   tag)
		 (setf (goto-tag-address entry) instruction-address))
	     (setq instruction-cons (cdr instruction-cons))
	     (setf (cdr trailer) instruction-cons))
	    ((eq instruction-name 'jump-tag-statement)
	     (setq tag (second (car instruction-cons)))
	     (setq entry (goto-tag-entry-with-name
			   tag goto-tags-in-compilation))
	     (if (null entry)
		 (compiler-bug
		   "address resolver"
		   "The JUMP tag ~a had no entry at address generation time."
		   tag)
		 (setf (goto-tag-jump-address entry) instruction-address))
	     (setq instruction-cons (cdr instruction-cons))
	     (setf (cdr trailer) instruction-cons))
	    (t
	     (incff instruction-address)
	     (setq trailer instruction-cons)
	     (setq instruction-cons (cdr instruction-cons)))))
    (cdr leading-cons)))




;;; The function `register-goto-tag-address' takes a procedure tag, an
;;; address fixnum, and a flag indicating if this is a jump tag.  This function
;;; will register the address in the corresponding procedure tag entry,
;;; signalling a procedure compiler error if no tag with the given name can be
;;; found.

(defun register-goto-tag-address (tag address jump-tag?)
  (let ((entry (goto-tag-entry-with-name tag goto-tags-in-compilation)))
    (cond ((null entry)
	   (compiler-bug
	     "address registrar" "The tag ~a had no entry." tag))
	  ((null jump-tag?)
	   (when (goto-tag-address entry)
	     (compiler-error
	       "The tag ~a is registered at multiple addresses."
	       tag))
	   (setf (goto-tag-address entry) address))
	  (t
	   (when (goto-tag-jump-address entry)
	     (compiler-error
	       "The tag ~a is registered at multiple addresses."
	       tag))
	   (setf (goto-tag-jump-address entry) address)))
    nil))






;;;; Procedure Tag Replacement




;;; The function `replace-goto-tags-with-instruction-addresses' takes the
;;; list of instructions and an alist of defined tags to instruction addresses.
;;; This function loops across instructions, calling a procedure tag replacer
;;; function for a statement if it is defined.  The replacer should return the
;;; instruction with all tags replaced with instruction addresses.  The replacer
;;; is allowed to mutate the instruction if the conses of that instruction were
;;; generated by the compiler.

;;; Note that this function is called during branch-to-branch-short-cut optimizing.

(defun replace-goto-tags-with-instruction-addresses (instructions)
  (loop for instruction-cons on instructions
	for replacer-function? = (goto-tag-replacer
				   (car-of-cons
				     (car-of-cons instruction-cons)))
	do
    (when replacer-function?
      (setf (car instruction-cons)
	    (funcall-simple-compiled-function
	      replacer-function? (car-of-cons instruction-cons))))))






;;;; Branch or Jump Emitting




;;; Anytime that control is transfered to another tag, the resulting instruction
;;; may be either a branch or a jump.  The function `emit-branch-or-jump' takes
;;; a tag and emits the instructions to cause a branch to that instruction, or a
;;; jump to the instruction in the right code body for the given tag.
;;; `Emit-branch-or-jump-if-true' and `emit-branch-or-jump-if-not-true' emit the
;;; corresponding branch or jump instructions for conditionalized branches.

(defun emit-branch-or-jump (tag)
  (let ((jump-depth? (jump-depth-for-tag? tag)))
    (if (null jump-depth?)
	(emit-instruction 'branch tag)
	(emit-instruction 'jump jump-depth? tag))))

(defun emit-branch-or-jump-if-true (compiled-expression tag)
  (let ((jump-depth? (jump-depth-for-tag? tag)))
    (cond ((null jump-depth?)
	   (emit-instruction 'branch-if-true compiled-expression tag))
	  (t
	   (let ((new-tag (generate-new-goto-tag)))
	     (emit-branch-or-jump-if-not-true compiled-expression new-tag)
	     (emit-instruction 'jump jump-depth? tag)
	     (emit-instruction 'tag-statement new-tag))))))

(defun emit-branch-or-jump-if-not-true (compiled-expression tag)
  (let ((jump-depth? (jump-depth-for-tag? tag)))
    (cond ((null jump-depth?)
	   (emit-instruction 'branch-if-not-true compiled-expression tag))
	  (t
	   (let ((new-tag (generate-new-goto-tag)))
	     (emit-branch-or-jump-if-true compiled-expression new-tag)
	     (emit-instruction 'jump jump-depth? tag)
	     (emit-instruction 'tag-statement new-tag))))))






;;;; Procedure Statement Printers




;;; The definitions for all printer functions for procedure statements must
;;; preceed the definition of the compiler for the statment.  Therefore, all
;;; printer functions will be grouped here, before the definitions of the
;;; compiler functions.

(defun print-assignment-statement (statement)
  (tformat "~a = " (second statement))
  (write-expression (third statement)))

(defun write-return-statement (statement)
  (twrite-string "RETURN ")
  (loop for expression in (cdr statement)
	for first-time? = t then nil
	do
    (unless first-time?
      (twrite-string ", ")
      (write-expression expression))))

(defun write-if-then-statement (statement)
  (twrite-string "IF ")
  (write-expression (second statement))
  (twrite-string " THEN ")
  (write-procedure-statement (third statement)))

(defun write-if-then-else-statement (statement)
  (twrite-string "IF ")
  (write-expression (second statement))
  (twrite-string " THEN ")
  (write-procedure-statement (third statement))
  (twrite-string " ELSE ")
  (write-procedure-statement (fourth statement)))

(defun print-case-statement (statement)
  (let ((expression (second statement))
	(case-choices (cddr statement)))
    (twrite-string "CASE (")
    (write-expression expression)
    (tformat ")~%  ")
    (loop for case-choice in case-choices
	  for values = (first case-choice)
	  for case-statement = (second case-choice)
	  for first-choice? = t then nil do
      (unless first-choice? (tformat ";~%  "))
      (if (eq values 'otherwise)
	  (twrite-string "OTHERWISE")
	  (loop for value in values
		for first-value? = t then nil do
	    (unless first-value? (twrite-string ", "))
	    (print-constant value (data-type-of-non-logical-datum value))))
      (twrite-string " : ")
      (write-procedure-statement case-statement))
    (tformat "~%  END")))

(defun write-repeat-statement (statement)
  (twrite-string "REPEAT ")
  (loop for sub-statement in (cdr statement)
	for first-time? = t then nil
	do
    (unless first-time? (twrite-string "; "))
    (write-procedure-statement sub-statement))
  (twrite-string " END"))

(defun write-exit-if-statement (statement)
  (twrite-string "EXIT IF ")
  (write-expression (second statement)))

(defun write-for-each-statement (statement)
  (gensym-dstruct-bind ((statement-name (local-name designation) . statements)
		       statement)
    (tformat "FOR ~a = EACH " local-name)
    (let ((role (role-of-designation designation))
	  (domain (domain-of-designation designation)))
      (if domain
	  (progn
	    (print-role role)
	    (twrite-string #w" ") 
	    (print-designation domain))
	  (if (atom role)
	      (twrite-symbol role)
	      (print-role role))))
    (twrite-string
      (case statement-name
	(for-each-statement " DO")
	(for-each-in-parallel-statement " DO IN PARALLEL")
	(for-each-in-parallel-race-statement
	  " DO IN PARALLEL UNTIL ONE COMPLETES")))
    (loop for sub-statement in statements
	  for first-time? = t then nil
	  do
      (unless first-time? (twrite-string "; "))
      (tformat "~%  ")
      (write-procedure-statement sub-statement))
    (twrite-string " END")))

(defun print-for-numeric-statement (statement)
  (gensym-dstruct-bind ((nil (local-name to-or-down-to init final by?)
			    execution-specifier . statements)
		       statement)
    (tformat "FOR ~a = " local-name)
    (write-expression init)
    (twrite-string (if (eq to-or-down-to 'to) " TO " " DOWN TO "))
    (write-expression final)
    (when by?
      (twrite-string " BY ")
      (write-expression by?))
    (twrite-string (case execution-specifier
		     ((do) " DO")
		     ((do-in-parallel) " DO IN PARALLEL")
		     (t " DO IN PARALLEL UNTIL ONE COMPLETES")))
    (loop for sub-statement in statements
	  for first-time? = t then nil
	  do
      (unless first-time? (twrite-string "; "))
      (tformat "~%  ")
      (write-procedure-statement sub-statement))
    (tformat "~% END")))

(defun write-go-to-statement (statement)
  (tformat "GO TO ~a" (second statement)))

(defun write-tag-statement (statement)
  (tformat "~a :" (second statement)))

(defun write-begin-statement (statement)
  (twrite-string "BEGIN ")
  (loop for sub-statement in (cdr statement)
	for first-time? = t then nil
	do
    (unless first-time? (twrite-string "; "))
    (write-procedure-statement sub-statement))
  (twrite-string " END"))

(defun write-call-statement (statement)
  (let ((new-statement (nconc (gensym-list 'call-assignment-statement nil)
			      (cdr statement))))
    (write-call-assignment-statement new-statement)
    (reclaim-gensym-list-given-tail
      new-statement (cdr new-statement))))

(defun write-call-assignment-statement (statement)
  (gensym-dstruct-bind ((nil local-names designation args across?)
		       statement)
    (when local-names
      (loop for name in local-names
	    for first-time? = t then nil
	    do
	(unless first-time? (twrite-string ", "))
	(tformat "~a" name))
      (twrite-string " = "))
    (twrite-string "CALL ")
    (print-designation designation)
    (twrite-string " (")
    (loop for arg in args
	  for first-time? = t then nil
	  do
      (unless first-time? (twrite-string ", "))
      (write-expression arg))
    (twrite-string ")")
    (when across?
      (twrite-string " ACROSS ")
      (print-designation across?))))

(defun write-call-next-method-assignment-statement (statement)
  (let ((local-names (car-of-cons (cdr-of-cons statement))))
    (loop for name in local-names
	  for first-time? = t then nil
	  do
      (unless first-time? (twrite-string ", "))
      (tformat "~a" name))
    (twrite-string " = CALL NEXT METHOD")))

(defun write-system-call-assignment-statement (statement)
  (gensym-dstruct-bind ((nil local-names lisp-function-name args)
		       statement)
    (loop for name in local-names
	  for first-time? = t then nil
	  do
      (unless first-time? (twrite-string ", "))
      (tformat "~a" name))
    (twrite-string " = ")
    (twrite-string "SYSTEM CALL ")
    (twrite lisp-function-name)
    (twrite-string " (")
    (loop for arg in args
	  for first-time? = t then nil
	  do
      (unless first-time? (twrite-string ", "))
      (write-expression arg))
    (twrite-string ")")))

(defun write-call-next-method-statement (statement)
  (declare (ignore statement))
  (twrite-string "CALL NEXT METHOD"))

(defun write-system-call-statement (statement)
  (gensym-dstruct-bind ((nil lisp-function-name args) statement)
    (twrite-string "SYSTEM CALL ")
    (twrite lisp-function-name)
    (twrite-string " (")
    (loop for arg in args
	  for first-time? = t then nil
	  do
      (unless first-time? (twrite-string ", "))
      (write-expression arg))
    (twrite-string ")")))

(defun write-conclude-that-statement (statement)
  (gensym-dstruct-bind ((nil designation expression expiration? collection?
			 old-value? local-name?)
		       statement)
    (twrite-string "CONCLUDE THAT ")
    (print-designation designation)
    (twrite-string " = ")
    (write-expression expression)
    (when expiration?
      (twrite-string " WITH EXPIRATION ")
      (write-expression expiration?))
    (when collection?
      (twrite-string " WITH COLLECTION TIME ")
      (write-expression collection?))
    (when old-value?
      (twrite-string " COMPARE ")
      (write-expression old-value?))
    (when local-name?
      (twrite-string " RESULTING ")
      (tformat "~a " local-name?))))

(defun write-allow-other-processing-statement (ignored-statement)
  (declare (ignore ignored-statement))
  (twrite-string "ALLOW OTHER PROCESSING"))

(defun write-collect-data-statement (statement)
  (gensym-dstruct-bind ((nil name-expression-pairs timeout? timeout-statement?)
		       statement)
    (twrite-string "COLLECT DATA ")
    (when timeout?
      (twrite-string " (TIMING OUT AFTER ")
      (write-expression timeout?)
      (twrite-string ")"))
    (loop for (name expression) in name-expression-pairs do
      (tformat "~%  ~a = " name)
      (write-expression expression)
      (twrite-string ";"))
    (when timeout-statement?
      (tformat "~%  IF TIMEOUT THEN ")
      (write-procedure-statement timeout-statement?)
      (twrite-string ";"))
    (tformat "~%END")))

(defun write-do-in-parallel-statement (statement)
  (twrite-string "DO IN PARALLEL")
  (loop for parallel-statement in (cdr statement)
	do
    (tformat "~%  ")
    (write-procedure-statement parallel-statement)
    (twrite-string ";"))
  (tformat "~%END"))

(defun write-do-in-parallel-until-one-completes-statement (statement)
  (twrite-string "DO IN PARALLEL UNTIL ONE COMPLETES")
  (loop for parallel-statement in (cdr statement)
	do
    (tformat "~%  ")
    (write-procedure-statement parallel-statement)
    (twrite-string ";"))
  (tformat "~%END"))

(defun write-wait-for-statement (statement)
  (twrite-string "WAIT FOR ")
  (write-expression (second statement)))

(defun write-wait-until-statement (statement)
  (twrite-string "WAIT UNTIL ")
  (write-expression (second statement))
  (twrite-string "CHECKING EVERY ")
  (write-expression (third statement)))

(defun write-wait-until-event-statement (statement)
  (twrite-string "WAIT UNTIL ")
  (write-expression (second statement)))

(defun write-system-wait-statement (statement)
  (declare (ignore statement))
  (twrite-string "SYSTEM WAIT"))

(defun print-create-statement (statement)
  (gensym-dstruct-bind ((nil class-expression local-name?) statement)
    (cond
      ((and (consp class-expression) (cdr class-expression)
	    (eq (car class-expression) 'quote))

       (if local-name?
	   (tformat "CREATE A(N) ~NE ~a " (second class-expression) local-name?)
	   (tformat "CREATE A(N) ~NE " (second class-expression))))
      (t
       (twrite-string "CREATE AN INSTANCE ")
       (when local-name?
	 (tformat "~a " local-name?))
       (twrite-string "OF THE CLASS NAMED BY ")
       (write-expression class-expression)))))

(defun print-create-connection-statement (statement)
  (gensym-dstruct-bind 
    ((nil class-expression connection-specification local-name?) statement)
    connection-specification
    (twrite-string "CREATE AN INSTANCE ")
    (when local-name?
      (tformat "~a " local-name?))
    (twrite-string "OF THE CLASS NAMED BY ")
    (write-expression class-expression)))

(defun print-create-explanation-statement (statement)
  (gensym-dstruct-bind
    ((nil variable-or-parameter-designation local-name?) statement)
    (twrite-string "CREATE AN EXPLANATION ")
    (when local-name?
      (tformat "~a " local-name?))
    (twrite-string "FOR ")
    (print-designation variable-or-parameter-designation)))

(defun print-on-error-statement (statement)
  (gensym-dstruct-bind ((nil protected-statement local1 local2 error-statement)
		       statement)
    (write-procedure-statement protected-statement)
    (tformat " ON ERROR (~a, ~a) " local1 local2)
    (write-procedure-statement error-statement)))

(defun print-signal-statement (statement)
  (tformat "SIGNAL ~NE, ~NE" (second statement) (third statement)))


;; Printers for one argument versions of on-error and signal
;; ajs (5/29/96)

(defun print-on-error-statement-new (statement)
  (gensym-dstruct-bind ((nil protected-statement local1 error-statement)
		       statement)
    (write-procedure-statement protected-statement)
    (tformat " ON ERROR (~a) " local1)
    (write-procedure-statement error-statement)))
				  
(defun print-signal-statement-new (statement)
  (tformat "SIGNAL ~NE" (second statement)))

;;;






;;;; Procedure Statement Compilers




;;; Besides the explicit dependency on the statement and instruction name
;;; TAG-STATEMENT in the the tag replacement code, this following definitions
;;; are the only things which define new compilations for statements.  The
;;; definition of a compiler for a statement consists of a
;;; def-procedure-statement-compiler and possibly a def-goto-tag-replacer,
;;; if the emitted instructions from a statement contain tags.

;;; The `assignment-statement' is an assignment to a local variable.  It is
;;; emitted as an assign-local-var instruction.

;;; There is one optimization for this statement.  If the local variable being
;;; assigned into is mentioned once and only once in the expression generating
;;; the new value, and if that reference is suitably nested only inside of
;;; stack-evaluators or specially allowed stack-instructions, then the one
;;; reference to the local variable will move that value onto the stack instead
;;; of copying the value onto the stack.  When this statement is implementing an
;;; accumulation into a growing data structure, such as appending to a text,
;;; adding elements to the end of a sequence, or adding slots into a structure,
;;; this "move" will eliminate the copy of the growing data structure.  This
;;; turns the most common kinds of accumulation into linear order operations
;;; instead of polynomial order operations.  The other optimizations that make
;;; this all work out are: format-form will fill in new strings between the
;;; fill-pointer and array-dimension if the first argument is a string; and the
;;; modifying operations for sequences and structures will directly modify their
;;; arguments if there is only one reference in their reference counts.
;;; -jallard 6/15/97

;;;   (ASSIGNMENT-STATEMENT local-name designation-or-expression)

(def-procedure-statement-compiler (assignment-statement print-assignment-statement)
  (emit-instruction
    'begin-activity (activity-index "assign local variable statement"))
  (let* ((local-name (second statement))
	 (expression (third statement))
	 var-spot description)
    (multiple-value-setq (var-spot description)
      (variable-spot-and-description-for-local-name local-name))
    (with-procedure-stack-frame-variables-environment
      (if var-spot
	  (let* ((stack-node
		   (compile-stack-expression
		     expression (getfq (cdr description) :type)))
		 (single-read-reference?
		   (and (=f (stack-node-references-to-var-spot
			      stack-node var-spot)
			    1)
			(stack-node-first-reference-to-var-spot
			  stack-node var-spot))))
	    ;; When there is a single, suitable reference to the var-spot being
	    ;; modified, change it into a move-from-surrounding-local-var
	    ;; instead of a push.  (See above for a description of what suitable
	    ;; means.)
	    (when single-read-reference?
	      (setf (stack-node-operation single-read-reference?)
		    'move-from-surrounding-local-var))
	    (emit-instruction
	      'assign-local-var var-spot stack-node))
	  (procedure-compiler-missing-local-name-error local-name)))))

(defun-simple stack-node-references-to-var-spot (stack-node var-spot)
  (+f (if (and (stack-node-instruction-p stack-node)
	       (memq (stack-node-operation stack-node)
		     '(push-from-surrounding-local-var
		       move-from-surrounding-local-var
		       copy-into-surrounding-local-var
		       evaluate-role-implicit-scope))
	       (equal-var-spots
		 (stack-node-instruction-extra-info stack-node)
		 var-spot))
	  1
	  0)
      (let ((args (stack-node-argument-nodes stack-node)))
	(if args
	    (loop with sum fixnum = 0
		  for arg in args do
	      (incff sum (stack-node-references-to-var-spot arg var-spot))
		  finally (return sum))
	    0))))

(defun-simple stack-node-first-reference-to-var-spot (stack-node var-spot)
  (let ((stack-node-inst? (stack-node-instruction-p stack-node))
	(operation (stack-node-operation stack-node)))
    (cond
      ((and stack-node-inst?
	    (eq operation 'push-from-surrounding-local-var)
	    (equal-var-spots 
	      (stack-node-instruction-extra-info stack-node)
	      var-spot))
       stack-node)
      ((or (not stack-node-inst?)
	   (memq operation
		 '(evaluate-role
		   coerce-to-datum
		   coerce-no-item-to-unknown
		   ensure-type
		   call-function
		   format-form)))
       (loop for arg in (stack-node-argument-nodes stack-node)
	     thereis (stack-node-first-reference-to-var-spot arg var-spot)))
      (t nil))))
      



;;; The `return-statement' turns into two instructions, one to evaluate the
;;; expressions and return their values, and the next to close the procedure
;;; invocation.  The number of expressions must match the declared number.  When
;;; a return statement happens within a code body which is not the base, this
;;; instruction will generate a set of var spots in which to cache the values
;;; being returned, branch out to the end of the base code body, and execute the
;;; return instruction from there.  A side-effect of this emitted branch is to
;;; abort all of the other ongoing code-bodies from within this procedure.

;;; FUNCTIONALITY CHANGE!  Prior to the rewrite for the stack-compiler, there
;;; was a bug in the generation of local variables for the return-from non-base
;;; code body case.  It was generating a new set of variables for each return
;;; emitted into a non-base code body, though in the base, only one set of
;;; variables was ever looked at.  This bug would only exhibit, therefore, in
;;; procedures with more than one return statement nested in non-base code
;;; bodies.  -jra 4/4/91

;;;   (RETURN-STATEMENT . list-of-expressions-and-designations)

(def-procedure-statement-compiler (return-statement write-return-statement)
  (unless (in-inlining-context?)
    (emit-instruction 'begin-activity (activity-index "return statement")))
  (setq return-statement-processed? t)
  (let ((expressions (cdr statement)))
    (when (/=f (length expressions) (length returned-values-description))
      (compiler-error
	"Returning ~a values, but the procedure is declared to return ~a ~
         values."
	(length expressions)
	(length returned-values-description)))
    (cond ((and (within-base-code-body-p)
		(null (in-inlining-context?)))
	   (emit-instruction
	     'return-values
	     (loop for expression in expressions
		   for description in returned-values-description
		   for type = (getfq description :type)
		   collect
		     (compile-stack-expression expression type)
			    using phrase-cons)))
	  ((in-inlining-context?)
	   ;; Note that in this loop, if there are more expressions than
	   ;; inling-data-received-value-compilations, then we will not compile
	   ;; or evaluate the expressions for the discarded return values of
	   ;; this inlined procedure.  That is OK, as long as expressions are
	   ;; side-effect-free, which they are (today).  -jallard 10/3/97
	   (loop for expression in expressions
		 for description in returned-values-description
		 for var-spot in (inlining-data-recieved-value-compilations?)
		 for return-type = (getfq description :type)
		 for var-spot-type = (var-spot-type
				       var-spot lexically-visible-code-bodies)
		 for type = (make-type-specification-intersection
			      return-type var-spot-type)
		 do
	     (cond
	       ((not (type-specifications-could-intersect-p
		       return-type var-spot-type))
		(compiler-error
		  "A returned value from the inlined procedure ~NF of type ~NT ~
                   could not be assigned into a local-name of type ~NT."
		  (get-procedure-in-context) return-type var-spot-type))
	       (t
		(emit-instruction
		  'assign-local-var var-spot
		  (compile-stack-expression expression type))))
		 finally
		   (emit-branch-or-jump base-code-body-return-tag)))
	  (t
	   (unless generated-var-spots-for-base-code-body-return
	     (generate-var-spots-for-base-code-body-return))
	   (loop for expression in expressions
		 for description in returned-values-description
		 for type = (getfq description :type)
		 for var-spot-name
		     in generated-var-spots-for-base-code-body-return
		 for var-spot = (variable-spot-and-description-for-local-name
				  var-spot-name)
		 do
	     (emit-instruction
	       'assign-local-var var-spot
	       (compile-stack-expression expression type))
		 finally
		   (emit-branch-or-jump base-code-body-return-tag))))))

(defun generate-var-spots-for-base-code-body-return ()
  (setq generated-var-spots-for-base-code-body-return
	(loop for description in returned-values-description
	      for type = (getfq description :type)
	      for new-name = (phrase-list 'return-value)
	      do
	  (generate-new-variable-spot
	    type new-name (base-code-body))
	      collect new-name using phrase-cons)))




;;; The `if-then-statement' generates a branch-if-not-true of the first argument
;;; to a newly generated tag which is emitted immediately after the instructions
;;; for the statement.

;;;   (IF-THEN-STATEMENT logical-expression statement)

(def-procedure-statement-compiler (if-then-statement write-if-then-statement)
  (emit-instruction 'begin-activity (activity-index "if-then statement"))
  (let ((new-tag (generate-new-goto-tag)))
    (with-procedure-stack-frame-variables-environment
      (emit-branch-or-jump-if-not-true
	(compile-stack-expression (second statement) 'truth-value)
	new-tag))
    (compile-procedure-statement (third statement))
    (emit-instruction 'tag-statement new-tag)))

(def-goto-tag-recorder if-then-statement
  (record-goto-tags (third statement)))




;;; The `if-then-else-statement' generates an else tag and a tag for the end of
;;; the entire if statement.  It emits an instruction to branch if not true to
;;; the else statement, emits the then statements, emits a branch to the end
;;; tag, emits the else tag, emits the else statements, then then emits a tag
;;; for the end of the if.
;;;
;;;   (IF-THEN-ELSE-STATEMENT logical-expression then-statement else-statement)

(def-procedure-statement-compiler (if-then-else-statement
				    write-if-then-else-statement)
  (emit-instruction 'begin-activity (activity-index "if-then-else statement"))
  (gensym-dstruct-bind ((nil logical-expression then-statement else-statement)
		       statement)
    (let ((else-tag (generate-new-goto-tag))
	  (end-of-if-tag (generate-new-goto-tag)))
      (with-procedure-stack-frame-variables-environment
	(emit-branch-or-jump-if-not-true
	  (compile-stack-expression logical-expression 'truth-value)
	  else-tag))
      (compile-procedure-statement then-statement)
      (emit-branch-or-jump end-of-if-tag)
      (emit-instruction 'tag-statement else-tag)
      (compile-procedure-statement else-statement)
      (emit-instruction 'tag-statement end-of-if-tag))))

(def-goto-tag-recorder if-then-else-statement
  (gensym-dstruct-bind ((nil nil then else) statement)
    (record-goto-tags then)
    (record-goto-tags else)))




;;; The `case-statement' is a mutually exclusive, collectively exhaustive
;;; dispatch to one of a set of statements, based on a single key value.  There
;;; is a case-dispatch instruction for optimizing case statements where the key
;;; is an integer, and the values are a set of integers spanning a small range.
;;; In the default case, however, this turns into a set of conditional branches.

;;; FUNCTIONALITY CHANGE!  In 3.0 the optimization for integers here is being
;;; implemented.  The criteria for use of the integer clause is that the
;;; expression must be of type integer, every clause must contain integers or be
;;; an otherwise, and the count of clause values must be at least one half of
;;; the difference between the highest and lowest clause values.  This last
;;; criteria is to avoid using tons of memory in cases where there are only two
;;; values, negative one million and positive one million (or something
;;; similarly outrageous).  -jra 4/4/91

;;; FUNCTIONALITY CHANGE!  In 2.0 this compiler would not catch multiple data
;;; types in the case choices, since it was always testing the type of the first
;;; case choice instead of each one in turn.  It now tests each one in turn.
;;; -jra 4/4/91

;;; DOCUMENTATION BUG!  In the G2 reference manual, it says that if no clause is
;;; found then a level one error message is displayed and execution continues
;;; past the end of the case statement.  In reality, if none is found then an
;;; error is signalled, and the error handling mechanism determines what (if
;;; any) code gets executed next.  -jra 4/4/91

;;;   (CASE-STATEMENT expression . ((key-values) statement))

(def-procedure-statement-compiler (case-statement print-case-statement)
  (emit-instruction 'begin-activity (activity-index "case statement"))
  (gensym-dstruct-bind ((nil key . case-choices) statement)
    (let* ((first-key (caaar case-choices))
	   (compiled-key (compile-stack-expression key 'datum))
	   (first-type (stack-node-value-type compiled-key)))
      ;; Check for duplicate tags and type mismatching.
      (cond
	((null first-type)
	 (compiler-error
	   "First CASE value, ~a, was not of a known type!"
	   first-key))
	((and (type-specification-subtype-p first-type 'integer)
	      (case-choices-can-be-integer-optimized-p case-choices))
	 (compile-integer-optimized-case-statement
	   compiled-key case-choices))
	(t
	 (compile-unoptimized-case-statement
	   compiled-key first-type case-choices))))))

(def-goto-tag-recorder case-statement
  (loop for case-choice in (cddr statement)
	for case-statement = (second case-choice)
	do
    (record-goto-tags case-statement)))




;;; The function `case-choices-can-be-integer-optimized-p' takes a list of
;;; case-choices and determines whether the values in the choices are all
;;; integers, and that the count of choices is at least half of the difference
;;; between the max and min.

(defun case-choices-can-be-integer-optimized-p (case-choices)
  (and (loop for (value-list-or-otherwise) in case-choices
	     always
	       (or (eq value-list-or-otherwise 'otherwise)
		   (loop for value in value-list-or-otherwise
			 always
			   (type-specification-subtype-p
			     (data-type-of-non-logical-datum value)
			     'integer))))
       (loop with max-case-value = most-negative-fixnum
	     with min-case-value = most-positive-fixnum
	     with count = 0
	     for (value-list-or-otherwise) in case-choices
	     do
	 (unless (eq value-list-or-otherwise 'otherwise)
	   (loop for value in value-list-or-otherwise
		 do
	     (setq max-case-value (maxf max-case-value value))
	     (setq min-case-value (minf min-case-value value))
	     (incff count)))
	     finally
	       (return (>f (*f count 2)
			   (-f max-case-value min-case-value))))))




;;; The function `compile-integer-optimized-case-statement' compiles the body of
;;; a case statement which is optimized to dispatch to code based on an integer
;;; value.

(defun compile-integer-optimized-case-statement (compiled-key case-choices)
  (let ((max-choice most-negative-fixnum)
	(min-choice most-positive-fixnum)
	(count 0)
	(tag-list nil)
	(tag-and-forms-list nil)
	(else-tag nil)
	(error-tag nil)
	(end-of-case-tag (generate-new-goto-tag)))
    (loop for (value-list-or-otherwise) in case-choices do
      (unless (eq value-list-or-otherwise 'otherwise)
	(loop for value in value-list-or-otherwise do
	  (setq max-choice (maxf max-choice value))
	  (setq min-choice (minf min-choice value))
	  (incff count))))
    (when (=f count 0)
      (compiler-error
	"This CASE statement had no values to dispatch upon."))
    (setq tag-list (make-phrase-list (+f (-f max-choice min-choice) 1)))
    (fill tag-list nil)
    (loop for case-choice-cons on case-choices
	  for case-choice = (car case-choice-cons)
	  for value-list-or-otherwise = (car case-choice)
	  for value-statement = (second case-choice)
	  for case-choice-tag = (generate-new-goto-tag)
	  do
      (cond ((null value-list-or-otherwise)
	     (compiler-error
	       "A CASE clause had no values associated with it."))
	    ((eq value-list-or-otherwise 'otherwise)
	     (when (cdr case-choice-cons)
	       (compiler-error
		 "The CASE key value OTHERWISE was the key for a clause ~
                  other than the last one in the CASE statement."))
	     (setq else-tag case-choice-tag))
	    (t
	     (loop for value in value-list-or-otherwise do
	       (setf (car (nthcdr (-f value min-choice) tag-list))
		     case-choice-tag))))
      (setq tag-and-forms-list
	    (phrase-cons (phrase-cons case-choice-tag value-statement)
			 tag-and-forms-list)))
    (when (null else-tag)
      (setq error-tag (generate-new-goto-tag))
      (setq else-tag error-tag))
    (loop for tag-cons on tag-list do
      (when (null (car tag-cons))
	(setf (car tag-cons) else-tag)))
    (emit-instruction
      'case-dispatch compiled-key min-choice (+f (-f max-choice min-choice) 1)
      else-tag tag-list)
    (loop for (tag . statement) in (nreverse tag-and-forms-list)
	  do
      (emit-instruction 'tag-statement tag)
      (compile-procedure-statement statement)
      (emit-branch-or-jump end-of-case-tag))
    (when error-tag
      (emit-instruction 'tag-statement error-tag)
      (emit-instruction
	'signal-error
	(compile-stack-expression
	  '(quote no-case-choice)
	  'symbol)
	(compile-stack-expression
	  "CASE key value did not match any of the CASE statement choices."
	  'text)))
    (emit-instruction 'tag-statement end-of-case-tag)))




;;; The function  compiles the body of a case statement which is not optimized
;;; into the integer dispatching code.

(defun compile-unoptimized-case-statement (compiled-key first-type case-choices)
  (let ((key-spot (generate-new-variable-spot first-type))
	(end-of-case-tag (generate-new-goto-tag)))
    (emit-instruction 'assign-local-var key-spot compiled-key)
    (loop for choice-cons on case-choices
	  for case-choice = (car choice-cons)
	  for value-list-or-otherwise = (car case-choice)
	  for value-statement = (second case-choice)
	  for next-tag = (generate-new-goto-tag)
	  for equal-clauses
	      = (if (eq value-list-or-otherwise 'otherwise)
		    value-list-or-otherwise
		    (loop for value in value-list-or-otherwise
			  for evalable-value =
			      (if (symbolp value)
				  (phrase-list 'quote value)
				  value)
			  for type = (data-type-of-non-logical-datum value)
			  collect (phrase-list '= key-spot evalable-value)
				   using phrase-cons
			  do
		      (cond ((null type)
			     (compiler-error
			       "Unknown CASE value type for ~a"
			       value))
			    ((not (type-specifications-could-intersect-p
				    type first-type))
			     (compiler-error
			       "The data type of the CASE value ~NC, ~NT, ~
                              was not compatible with the type ~NT of the ~
                              key expression for the CASE statement."
			       value type type first-type)))))
	  do
      (cond ((null equal-clauses)
	     (compiler-error "No values in CASE clause."))
	    ((eq equal-clauses 'otherwise)
	     (when (cdr choice-cons)
	       (compiler-error
		 "The CASE key value OTHERWISE was the key for a clause ~
                  other than the last one in the CASE statement.")))
	    (t
	     (emit-branch-or-jump-if-not-true
	       (compile-stack-expression
		 (if (null (cdr equal-clauses))
		     (car equal-clauses)
		     (phrase-cons 'or equal-clauses))
		 'truth-value)
	       next-tag)))
      (compile-procedure-statement value-statement)
      (emit-branch-or-jump end-of-case-tag)
      (emit-instruction 'tag-statement next-tag))
    (emit-instruction
      'signal-error
      (compile-stack-expression
	'(quote no-case-choice)
	'symbol)
      (compile-stack-expression
	"CASE key value did not match any of the CASE statement choices."
	'text))
    (emit-instruction 'tag-statement end-of-case-tag)))




;;; The special variable `tightest-end-of-loop-tag' is bound globally to NIL,
;;; and within compilers for looping expressions, to the tag which will be
;;; emitted at the end of the looping instructions.  It is used by the
;;; exit-if-statement to determine the target of its branch if true.

(defvar tightest-end-of-loop-tag nil)




;;; The `repeat-statement' generates a start of loop tag, binds an end of loop
;;; tag into tightest-end-of-loop-tag, emits the start tag, emits the statements
;;; in its body, emits a branch back to the start of the loop, and then emits
;;; the end of loop tag.  If no branches are actually executed to the end of
;;; loop tag, it will be removed by the dead code analyzer before pseudo-code
;;; generation.  Note that this iteration statement establishes a new lexical
;;; tag layer.
;;;
;;;   (REPEAT-STATEMENT . statements)

(def-procedure-statement-compiler (repeat-statement write-repeat-statement)
  (emit-instruction 'begin-activity (activity-index "repeat statement"))
  (enter-new-lexical-tag-layer
    (loop for iteration-statement in (cdr statement)
	  do
      (record-goto-tags iteration-statement))
    (let ((start-of-loop-tag (generate-new-goto-tag))
	  (tightest-end-of-loop-tag (generate-new-goto-tag)))
      (emit-instruction 'tag-statement start-of-loop-tag)
      (loop for sub-statement in (cdr statement)
	    do
	(compile-procedure-statement sub-statement))
      (emit-branch-or-jump start-of-loop-tag)
      (emit-instruction 'tag-statement tightest-end-of-loop-tag))))




;;; The `exit-if-statement' takes a logical-expression, and causes a branch if
;;; true statement to be emitted to the end tag of the tightest loop.  There
;;; must be a surrounding loop.
;;;
;;;   (EXIT-IF-STATEMENT logical-expression)

(def-procedure-statement-compiler (exit-if-statement write-exit-if-statement)
  (emit-instruction 'begin-activity (activity-index "exit if statement"))
  (cond ((null tightest-end-of-loop-tag)
	 (compiler-error
	   "Exit if statement was not within an iteration form.")
	 ;; Compile the expression anyway to get its warning messages.
	 (compile-stack-expression (second statement) 'truth-value))
	(t
	 (emit-branch-or-jump-if-true
	   (compile-stack-expression (second statement) 'truth-value)
	   tightest-end-of-loop-tag))))




;;; The `for-each-statement' generates an end of loop tag and binds it in
;;; tightest-end-of-loop-tag, and generates a next-loop tag.  It also generates
;;; a new var spot for an iteration state variable.  It emits an
;;; open-item-iteration or open-datum-iteration instruction, it emits the
;;; next-loop tag, it emits the body of statements, it emits a
;;; serve-next-item-iteration or serve-next-datum-iteration statement, a branch
;;; back to next-loop, the end loop tag, and a close-iteration statement.  Note
;;; that this iteration statement establishes a new lexical tag layer.

;;;   (FOR-EACH-STATEMENT (local-name designation) . statements)

(def-procedure-statement-compiler (for-each-statement write-for-each-statement)
  (emit-instruction 'begin-activity (activity-index "for statement"))
  (gensym-dstruct-bind ((nil (local-name designation) . statements)
		       statement)
    (enter-new-lexical-tag-layer
      (loop for iteration-statement in statements
	    do
	(record-goto-tags iteration-statement))
      (let ((tightest-end-of-loop-tag (generate-new-goto-tag))
	    (next-loop-tag (generate-new-goto-tag))
	    (continuation-spot
	      (generate-new-variable-spot
		(make-type-specification-for-iteration-state)))
	    (designation-type? (type-specification-of-designation designation))
	    (role (role-of-designation designation))
	    (domain-list (domain-list-of-designation designation))
	    (required-domain-types nil)
	    (local-var-type nil))
	(multiple-value-bind (value-spot description)
	    (variable-spot-and-description-for-local-name local-name)
	  (cond ((null value-spot)
		 (procedure-compiler-missing-local-name-error local-name)
		 (setq local-var-type 'item-or-datum))
		(t
		 (setq local-var-type (getfq (cdr description) :type))
		 (when (and designation-type?
			    (not (type-specifications-could-intersect-p
				   designation-type?
				   local-var-type)))
		   (compiler-error
		     "The local name ~a is declared to be of type ~NT but the ~
                     iteration reference returns values of type ~NT."
		     local-name local-var-type designation-type?))))

	  (when (not (simple-role-p role))
	    (compiler-error
	      "All local names for procedures must be declared at the top of ~
               the procedure definition.  This designation could not be ~
               compiled: ~ND."
	      designation)
	    (setq role (simple-role-of-role role)))

	  (setq required-domain-types
		(if (not (symbolp role))
		    (required-domain-types-of-role
		      (role-name-of-non-atomic-role
			role))))

	  (when (/=f (length required-domain-types) (length domain-list))
	    (write-compiler-error
	      (twrite-string "The number of arguments to ")
	      (print-role role)
	      (tformat ", ~a, did not match the required count, ~a"
		       (length domain-list)
		       (length required-domain-types))))

	  (cond ((null domain-list)
		 (emit-instruction
		   'open-role-iteration-no-domain
		   role continuation-spot value-spot
		   local-var-type designation-type?
		   tightest-end-of-loop-tag))
		(t
		 (emit-already-consed-instruction
		   (nconc
		     (phrase-list
		       'open-role-iteration
		       role continuation-spot value-spot
		       local-var-type designation-type?
		       tightest-end-of-loop-tag)
		     (loop for domain in domain-list
			   for type-cons = required-domain-types
					 then (cdr type-cons)
			   for type = (or (car type-cons)
					  'item-or-datum)
			   collect
			     (compile-stack-expression
			       domain type)
				    using phrase-cons)))))

	  (emit-instruction 'tag-statement next-loop-tag)
	  (loop for sub-statement in statements do
	    (compile-procedure-statement sub-statement))
	  (emit-instruction
	    'serve-next-iteration-value
	    continuation-spot value-spot
	    local-var-type designation-type?
	    tightest-end-of-loop-tag)
	  (emit-branch-or-jump next-loop-tag)
	  (emit-instruction 'tag-statement tightest-end-of-loop-tag)
	  (emit-instruction 'close-iteration continuation-spot))))))




;;; The `for-each-in-parallel-statement' executes a generic iteration, where the
;;; bodies of the iterated loops execute in parallel as called code body
;;; invocations.  It generates an end of loop tag and binds it in
;;; tightest-end-of-loop-tag, and a next-loop tag used while launching the
;;; parallel bodies.  It it enters a new code body layer, in which the body of
;;; the iteration if compiled and emitted.

;;; If the iteration is a parallel race (i.e.  do in parallel until one
;;; completes) then the body is completed with a jump to the
;;; tightest-end-of-loop-tag.  If the iteration is not a race, then the body is
;;; completed with a close-code-body instruction.

;;; Next a loop is emitted into the base code body for this statement which
;;; iterates across the items denoted by the designation, calling the generated
;;; code body with each of the items.  An allow other processing statement is
;;; included in the middle of this launching loop for the benefit of large
;;; parallel iterations.  Note that in a parallel race, a winning code body may
;;; execute during this wait state and branch to the tightest-end-of-loop-tag.

;;; After all code bodies have been launched a wait state is entered.  If it is
;;; a race iteration, the wait state is a pause-if-called-code-bodies.  In the
;;; race iteration, the winner of the race will branch to the tightest end of
;;; loop tag, leaving this stranded wait state.  If it is a synchronous
;;; iteration, the wait state is a wait-for-called-code-bodies, which will wait
;;; until all called code bodies complete for continuing.  The
;;; tightest-end-of-loop-tag is emitted right after the called code body wait
;;; statement.  Finally, the continuation is closed, after the
;;; tightest-end-of-loop-tag.

;;; CHANGE IN 3.0 BEHAVIOR!!!  In 2.0 there was a bug where empty race condition
;;; iterations could wait forever in the pause for a called code body to wake it
;;; up again.  The pause-if-called-code-bodies instruction fixes this problem.
;;; The race condition case has also been simplified by having it complete by
;;; branching to the end-of-loop-tag, instead of emitting a different
;;; abort-called-code-bodies.  A further change is that the code bodies are
;;; started with a call-scheduled-code-bodies, and there is an
;;; allow-other-processing in the middle of the loop.  In 2.0, the code bodies
;;; were launched and entered without wait state, causing some large parallel
;;; iterations to time out before entering all of the parallel bodies.  In 3.0,
;;; the loop itself and the bodies have wait states before them.  This can cause
;;; some bodies to begin execution before the loop has fully launched all its
;;; bodies.  This is not a problem, though, since in the race case the branch
;;; out to the end of loop tag can reliably stop any further launchings, and in
;;; the synchronous loop case its no problem to have some get a head start.
;;; -jra 4/16/91


;;; (FOR-EACH-IN-PARALLEL-STATEMENT (local-name designation) .  statements)

(def-procedure-statement-compiler
  (for-each-in-parallel-statement write-for-each-statement)
  (compile-for-each-parallel statement))

(defun compile-for-each-parallel (statement)
  (emit-instruction
    'begin-activity (activity-index "for in parallel statement"))
  (gensym-dstruct-bind ((statement-name (local-name designation) . statements)
		       statement)
    (when (procedure-p *current-computation-frame*)
      (set-procedure-contains-wait-state *current-computation-frame*))
    (enter-new-lexical-tag-layer
      (let* ((tightest-end-of-loop-tag (generate-new-goto-tag))
	     (end-of-launch-tag (generate-new-goto-tag))
	     (next-loop-tag (generate-new-goto-tag))
	     (continuation-spot
	       (generate-new-variable-spot
		 (make-type-specification-for-iteration-state)))
	     (until-one-completes?
	       (eq statement-name 'for-each-in-parallel-race-statement))
	     (code-body-number-for-iteration 0)
	     (iteration-launch-var-spot nil)
	     (local-var-type nil)
	     (designation-type?
	       (type-specification-of-designation designation))
	     (domain-list (domain-list-of-designation designation))
	     (role (role-of-designation designation))
	     (required-domain-list nil))
	(multiple-value-bind (value-spot description)
	    (variable-spot-and-description-for-local-name local-name)
	  (cond ((null value-spot)
		 (procedure-compiler-missing-local-name-error local-name)
		 (setq local-var-type 'item-or-datum))
		(t
		 (setq local-var-type (getfq (cdr description) :type))
		 (when (and designation-type?
			    (not (type-specifications-could-intersect-p
				   designation-type?
				   local-var-type)))
		   (compiler-error
		     "The local name ~a is declared to be of type ~NT but the ~
                     iteration reference returns values of type ~NT."
		     local-name local-var-type designation-type?))))
	  (enter-new-code-body (phrase-list
				 (phrase-list
				   local-name
				   :type
				   local-var-type))
	    (setq code-body-number-for-iteration
		  (compiler-code-body-entry-number (current-compiler-code-body)))
	    (loop for iteration-statement in statements
		  do
	      (record-goto-tags iteration-statement))
	    (loop for iteration-statement in statements
		  do
	      (compile-procedure-statement iteration-statement))
	    (if until-one-completes?
		(emit-branch-or-jump tightest-end-of-loop-tag)
		(emit-instruction 'close-code-body)))
	  (setq iteration-launch-var-spot
		(generate-new-variable-spot local-var-type))
	  (when (not (simple-role-p role))
	    (compiler-error
	      "All local names for procedures must be declared at the top of ~
               the procedure definition.  This designation could not be ~
               compiled: ~ND."
	      designation)
	    (setq role (simple-role-of-role role)))

	  (setq required-domain-list
		(if (not (symbolp role))
		    (required-domain-types-of-role
		      (role-name-of-non-atomic-role
			role))))

	  (when (/=f (length required-domain-list) (length domain-list))
	    (write-compiler-error
	      (twrite-string "The number of arguments to ")
	      (print-role role)
	      (tformat ", ~a, did not match the required count, ~a"
		       (length domain-list)
		       (length required-domain-list))))

	  (cond ((null domain-list)
		 (emit-instruction
		   'open-role-iteration-no-domain
		   role continuation-spot iteration-launch-var-spot
		   local-var-type designation-type?
		   tightest-end-of-loop-tag))
		(t
		 (emit-already-consed-instruction
		   (nconc
		     (phrase-list
		       'open-role-iteration
		       role continuation-spot iteration-launch-var-spot
		       local-var-type designation-type?
		       tightest-end-of-loop-tag)
		     (loop for domain in domain-list
			   for type-cons = required-domain-list
					 then (cdr type-cons)
			   for type = (or (car type-cons)
					  'item-or-datum)
			   collect
			     (compile-stack-expression
			       domain type)
				    using phrase-cons)))))
		   
	  (emit-instruction 'tag-statement next-loop-tag)
	  (emit-instruction
	    'call-scheduled-code-body
	    code-body-number-for-iteration
	    (compile-stack-expression
	      iteration-launch-var-spot local-var-type))
	  (emit-instruction 'allow-other-processing)
	  (emit-instruction
	    'serve-next-iteration-value
	    continuation-spot iteration-launch-var-spot
	    local-var-type designation-type?
	    end-of-launch-tag)
	  (emit-branch-or-jump next-loop-tag)
	  (emit-instruction 'tag-statement end-of-launch-tag)
	  (if until-one-completes?
	      (emit-instruction 'pause-if-called-code-bodies)
	      (emit-instruction 'wait-for-called-code-bodies))
	  (emit-instruction 'tag-statement tightest-end-of-loop-tag)
	  (emit-instruction 'close-iteration continuation-spot))))))




;;; The `for-each-in-parallel-race-statement' executes a generic iteration, where
;;; the bodies of the iterated loops execute in parallel as called code body
;;; invocations in a race condition.  It emits code exactly as the
;;; for-each-in-parallel-statement, except that pause and
;;; abort-called-code-bodies instructions are emitted, instead of a wait for the
;;; called code bodies.
;;;
;;;   (FOR-EACH-IN-PARALLEL-RACE-STATEMENT
;;;     (local-name designation) . statements)

(def-procedure-statement-compiler
  (for-each-in-parallel-race-statement write-for-each-statement)
  (when (procedure-p *current-computation-frame*)
    (set-procedure-contains-wait-state *current-computation-frame*))
  (emit-instruction
    'begin-activity
    (activity-index "for in parallel until one completes statement"))
  (compile-for-each-parallel statement))




;;; The `for-numeric-statement' executes a numeric iteration.  This one parsed
;;; statement covers the cases of to or down-to iterations, as well as the
;;; sequential vs. parallel vs. parallel racing executions.  The compiler
;;; function dispatches to one function which compiles sequential executions, or
;;; another function which compiles parallel executions.
;;;
;;;   (FOR-NUMERIC-STATEMENT
;;;     (local-name TO || DOWN-TO
;;;       initial-expression final-expression by-expression?)
;;;     DO || DO-IN-PARALLEL || DO-IN-PARALLEL-UNTIL-ONE-COMPLETES
;;;     . statements)

(def-procedure-statement-compiler
  (for-numeric-statement print-for-numeric-statement)
  (cond 
    ((eq (third statement) 'do)
     (emit-instruction
       'begin-activity (activity-index "for statement"))
     (compile-sequential-for-numeric-statement statement))
    (t
     (emit-instruction
       'begin-activity (activity-index "for in parallel statement"))
     (compile-parallel-for-numeric-statement statement))))




;;; The function `compile-sequential-for-numeric-statement' takes a sequential
;;; numeric iteration statement as its argument, and compiles it into
;;; instructions.  It generates a new tag for tightest-end-of-loop-tag and it
;;; generates a next-loop tag.  It generates a var spot of the same type as the
;;; iteration variable to hold the termination value, and if a by expression is
;;; given it generates a var spot to hold the stepping value.  It emits
;;; instructions to initialize the iteration value, the termination value, and
;;; if there is one, the stepping value.  It then emits the next loop tag, and
;;; the branch if not true termination predicate.  It emits the body statements.
;;; Next it emits the stepping assignment and a branch back up to the next loop.
;;; Finally it emits the end of loop tag.  Note that this iteration statement
;;; establishes a new lexical tag layer.

(defun compile-sequential-for-numeric-statement (statement)
  (gensym-dstruct-bind ((nil (local-name to-or-down-to init final by?)
			    nil . statements)
		       statement)
    (enter-new-lexical-tag-layer
      (loop for iteration-statement in statements do
	(record-goto-tags iteration-statement))
      (let ((tightest-end-of-loop-tag (generate-new-goto-tag))
	    (next-loop-tag (generate-new-goto-tag))
	    type final-spot step-value)
	(multiple-value-bind (iter-spot description)
	    (variable-spot-and-description-for-local-name local-name)
	  (cond ((null iter-spot)
		 (procedure-compiler-missing-local-name-error local-name)
		 (setq type 'number)
		 (setq iter-spot (generate-new-variable-spot type)))
		(t
		 (setq type (getfq (cdr description) :type))))
	  (unless (type-specification-subtype-p type 'number)
	    (unless (or (eq type 'datum) (eq type 'item-or-datum))
	      (compiler-error
		"The iteration variable ~a was of type ~NT instead of being ~
                 of type ~NT."
		local-name type 'number))
	    (setq type 'number))
	  (setq final-spot (generate-new-variable-spot type))
	  (cond (by?
		 (setq step-value (generate-new-variable-spot type)))
		((eq to-or-down-to 'to)
		 (setq step-value 1))
		(t
		 (setq step-value -1)))
	  (emit-instruction 'assign-local-var iter-spot
			    (compile-stack-expression init type))
	  (emit-instruction 'assign-local-var final-spot
			    (compile-stack-expression final type))
	  (when by?
	    (emit-instruction 'assign-local-var step-value
			      (compile-stack-expression by? type)))
	  (emit-instruction 'tag-statement next-loop-tag)
	  (emit-branch-or-jump-if-not-true
	    (compile-stack-expression
	      (phrase-list
		(if (eq to-or-down-to 'to)
		    '<=
		    '>=)
		iter-spot
		final-spot)
	      'truth-value)
	    tightest-end-of-loop-tag)
	  (loop for iteration-statement in statements do
	    (compile-procedure-statement iteration-statement))
	  (emit-instruction
	    'assign-local-var iter-spot
	    (compile-stack-expression
	      (phrase-list '+ iter-spot step-value)
	      type))
	  (emit-branch-or-jump next-loop-tag)
	  (emit-instruction 'tag-statement tightest-end-of-loop-tag))))))




;;; The function `compile-parallel-for-numeric-statement' receives a
;;; for-numeric-statement which is to be run either in parallel, or in a
;;; parallel race condition.  This function compiles that statement emitting
;;; instructions.  It first compiles the body of the iteration inside of a newly
;;; created code body environment.  It then generates code inside the code body
;;; of the iteration statement which will perform the requested numeric
;;; iteration, launching parallel calls to the generated code body.  After all
;;; code bodies are launched, a wait state is entered.  If this a racing
;;; parallel invocation, the wait state is a pause instruction followed by a
;;; call to abort all called code bodies.  If it is a normal in parallel, then
;;; an instruction is emitted which waits for all code bodies to complete.
;;; Finally, the end of loop tag is emitted.

(defun compile-parallel-for-numeric-statement (statement)
  (gensym-dstruct-bind ((nil (local-name to-or-down-to init final by?)
			    execution-specifier . statements)
		       statement)
    (when (procedure-p *current-computation-frame*)
      (set-procedure-contains-wait-state *current-computation-frame*))
    (enter-new-lexical-tag-layer
      (let ((tightest-end-of-loop-tag (generate-new-goto-tag))
	    (end-of-launch-tag (generate-new-goto-tag))
	    (next-loop-tag (generate-new-goto-tag))
	    (until-one-completes?
	      (eq execution-specifier 'do-in-parallel-until-one-completes))
	    (code-body-number-for-iteration 0)
	    type iteration-launch-var-spot final-spot step-value)
	(multiple-value-bind (value-spot description)
	    (variable-spot-and-description-for-local-name local-name)
	  (cond ((null value-spot)
		 (procedure-compiler-missing-local-name-error local-name)
		 (setq type 'number))
		(t
		 (setq type (getfq (cdr description) :type))))
	  (unless (type-specification-subtype-p type 'number)
	    (unless (or (eq type 'datum) (eq type 'item-or-datum))
	      (compiler-error
		"The iteration variable ~a was of type ~NT instead of being ~
                 of type ~NF."
		local-name type 'number))
	    (setq type 'number))
	  
	  (enter-new-code-body (phrase-list
				 (phrase-list local-name :type type))
	    (setq code-body-number-for-iteration
		  (compiler-code-body-entry-number (current-compiler-code-body)))
	    (loop for iteration-statement in statements do
	      (record-goto-tags iteration-statement))
	    (loop for iteration-statement in statements do
	      (compile-procedure-statement iteration-statement))
	    (if until-one-completes?
		(emit-branch-or-jump tightest-end-of-loop-tag)
		(emit-instruction 'close-code-body)))
	  
	  (setq iteration-launch-var-spot (generate-new-variable-spot type))
	  (setq final-spot (generate-new-variable-spot type))
	  (cond (by?
		 (setq step-value (generate-new-variable-spot type)))
		((eq to-or-down-to 'to)
		 (setq step-value 1))
		(t
		 (setq step-value -1)))
	  
	  (emit-instruction
	    'assign-local-var iteration-launch-var-spot
	    (compile-stack-expression init type))
	  (emit-instruction
	    'assign-local-var final-spot
	    (compile-stack-expression final type))
	  (when by?
	    (emit-instruction
	      'assign-local-var step-value
	      (compile-stack-expression by? type)))
	  (emit-branch-or-jump-if-not-true
	    (compile-stack-expression
	      (phrase-list (if (eq to-or-down-to 'to) '<= '>=)
			   iteration-launch-var-spot
			   final-spot)
	      'truth-value)
	    tightest-end-of-loop-tag)
	  (emit-instruction 'tag-statement next-loop-tag)
	  (emit-instruction
	    'call-scheduled-code-body
	    code-body-number-for-iteration
	    (compile-stack-expression iteration-launch-var-spot type))
	  (emit-instruction 'allow-other-processing)
	  (emit-instruction
	    'assign-local-var iteration-launch-var-spot
	    (compile-stack-expression
	      (phrase-list '+  iteration-launch-var-spot step-value)
	      type))
	  (emit-branch-or-jump-if-not-true
	    (compile-stack-expression
	      (phrase-list (if (eq to-or-down-to 'to) '<= '>=)
			   iteration-launch-var-spot
			   final-spot)
	      'truth-value)
	    end-of-launch-tag)
	  (emit-branch-or-jump next-loop-tag)
	  (emit-instruction 'tag-statement end-of-launch-tag)
	  (if until-one-completes?
	      (emit-instruction 'pause-if-called-code-bodies)
	      (emit-instruction 'wait-for-called-code-bodies))
	  (emit-instruction 'tag-statement tightest-end-of-loop-tag))))))




;;; The `go-to-statement' takes a tag and turns directly into a branch.
;;;
;;;   (GO-TO-STATEMENT tag)

(def-procedure-statement-compiler (go-to-statement write-go-to-statement)
  ;; Have to make sure we mangle tag correctly. -dkuznick, 8/3/98
  (emit-branch-or-jump (mangle-tag-in-context (second statement))))




;;; The `tag-statement' is emitted verbatim as a compiler instruction.
;;; Except now the tag-name gets mangled. -dkuznick, 8/3/98
;;;
;;;   (TAG-STATEMENT tag)

(def-procedure-statement-compiler (tag-statement write-tag-statement)
  (emit-instruction (first statement)
		    (mangle-tag-in-context (second statement))))

(def-goto-tag-recorder tag-statement
  (record-new-goto-tag (second statement)))




;;; The `begin-statement' is the basic compound statement and emits the
;;; instructions for each of its statements in turn.
;;;
;;;   (BEGIN-STATEMENT . statements)

(def-procedure-statement-compiler (begin-statement write-begin-statement)
  (loop for sub-statement in (cdr statement) do
    (compile-procedure-statement sub-statement)))

(def-goto-tag-recorder begin-statement
  (loop for sequential-statement in (cdr statement) do
    (record-goto-tags sequential-statement)))




;;; The function `compile-time-selected-method-p' takes a method-name, the class
;;; of the first argument, and an argument count and returns an instance of
;;; method that is the stable selected method for this dispatch, or it returns
;;; NIL if no guaranteed choice can be made or if no such method exists.

(defun compile-time-selected-method-p
    (global-name? first-arg-class-description arg-count)
  (let ((stable-procedure?
	  (get-specific-method
	    global-name? first-arg-class-description
	    arg-count nil t nil)))
    (cond
      ((and stable-procedure?
	    (not (text-string-p stable-procedure?))
	    (not (block-is-unstable-p stable-procedure?))
	    (or (block-has-stable-heirarchy-p stable-procedure?)
		(let ((declaration? 
		  (get-instance-with-name-if-any
		    'method-declaration global-name?)))
		  (and declaration?
		       (block-has-stable-heirarchy-p declaration?))))
	    (loop with first-arg-class?
		    = (class-name-of-class-description
			first-arg-class-description)
		  for subclass being each subclass of first-arg-class?
		  never (and (not (eq subclass first-arg-class?))
			     (loop for method in
				   (cdr (get-named-procedure-methods-for-class
					  global-name? subclass))
				   thereis (=f (argument-count method)
					       arg-count)))))
       stable-procedure?)
      (t nil))))




;;; The `call-assignment-statement' is emitted as a pair of instructions, a call
;;; and a receive-values.  All local names to be bound must be defined.

;;; Note that this compiler needs to register free references to the procedures
;;; and remote-procedure-declarations that it references, along with the types
;;; of the arguments and return values.

;;;   (CALL-ASSIGNMENT-STATEMENT local-names proc-designation arg-expressions)

(def-procedure-statement-compiler (call-assignment-statement
				    write-call-assignment-statement)
  (emit-instruction 'begin-activity (activity-index "call statement"))
  (setq call-statement-processed? t)
  (gensym-dstruct-bind ((nil local-names designation args across?)
		       statement)
    (let ((return-spots nil)
	  (return-types nil)
	  (desired-return-types nil)
	  (argument-stack-nodes nil)
	  (stable-procedure? nil)
	  (stable-proc-arg-types? nil)
	  (stable-proc-return-types? nil)
	  (stable-compile-time-selected-method-name? nil)
	  (stable-compile-time-selected-method-class? nil)
	  (stable-compile-time-selected-method-first-arg-class? nil)
	  (recorded-procedure-call-free-reference? nil)
	  (compiled-procedure-or-rpd
	    (if (null across?)
		(compile-procedure-expression designation '(class procedure))
		(compile-procedure-expression
		  designation '(class remote-procedure-declaration))))
	  (global-name? nil)
	  (compiler-error? nil))
      (setf (compiler-code-body-maximum-received-value-count
	      (current-compiler-code-body))
	    (maxf (compiler-code-body-maximum-received-value-count
		    (current-compiler-code-body))
		  (length local-names)))

      (loop with var-spot with description with type
	    for local-name in local-names
	    do
	(multiple-value-setq (var-spot description)
	  (variable-spot-and-description-for-local-name local-name))
	(setq type (getfq (cdr description) :type))
	(when (null var-spot)
	  (procedure-compiler-missing-local-name-error local-name)
	  (setq compiler-error? t))
	(setq return-spots (phrase-cons var-spot return-spots))
	(setq return-types (phrase-cons type return-types)))
      (setq return-spots (nreverse return-spots))
      (setq return-types (nreverse return-types))

      (when (procedure-p *current-computation-frame*)
	(when (indirectly-denoted-item-p compiled-procedure-or-rpd)
	  (set-procedure-contains-indirect-procedure-call
	    *current-computation-frame*)))

      (when (and (null compiler-error?) (dependent-compilation-p))
	(setq stable-procedure?
	      (stable-denoted-procedure-p compiled-procedure-or-rpd))
	(when (and (or (null stable-procedure?)
		       (frame-of-class-p stable-procedure? 'method-declaration))
		   (not (null args)))
	  (setq stable-procedure? nil)
	  (setq global-name?
		(denoted-name-of-type-p
		  compiled-procedure-or-rpd '(class method-declaration)))
	  (when (get-instance-with-name-if-any 'method-declaration global-name?)
	    (let* ((first-argument
		     (compile-stack-expression (car args) 'item-or-datum))
		   (first-arg-type (stack-node-value-type first-argument))
		   (first-arg-class?
		     (and (class-type-specification-p first-arg-type)
			  (type-specification-class first-arg-type)))
		   (first-arg-class-description?
		     (and first-arg-class?
			  (class-description first-arg-class?))))
	      (when first-arg-class-description?
		(setq stable-procedure?
		      (compile-time-selected-method-p
			global-name? first-arg-class-description?
			(length args)))
		(cond
		  (stable-procedure?
		   ;; When we have selected a method at compile time, then if
		   ;; the method has a unique name we will modify the
		   ;; designation to directly name the selected method.  If
		   ;; there are multiple implementations of a method on a class
		   ;; with differing argument lengths, then we won't have a
		   ;; unique name, but we can still get inlining and dependent
		   ;; calls.
		   (let ((unique-name?
			   (get-unique-name-for-frame-if-any stable-procedure?)))
		     (when unique-name?
		       (setq designation unique-name?)
		       (setq compiled-procedure-or-rpd
			     (compile-stack-expression
			       unique-name? '(class procedure)))))
		   (setq stable-compile-time-selected-method-name? global-name?)
		   (setq stable-compile-time-selected-method-class?
			 (procedure-method-class stable-procedure?))
		   (setq stable-compile-time-selected-method-first-arg-class?
			 first-arg-class?))
		  ;; If we fail any of the tests for compile time method
		  ;; selection, then set stable-procedure? back to NIL.
		  (t
		   (setq stable-procedure? nil)))))))

	(when stable-procedure?
	  (setq stable-proc-arg-types?
		(collect-types-into-list-using-phrase-conses
		  (argument-list-description stable-procedure?)))
	  (setq stable-proc-return-types?
		(collect-types-into-list-using-phrase-conses
		  (returned-values-description stable-procedure?)))
	  (cond
	    ((/=f (length stable-proc-arg-types?) (length args))
	     (compiler-dependence-warning
	       "Because of an argument count mismatch for ~ND, a call to it ~
                could not be optimized."
	       designation)
	     (setq stable-proc-arg-types? nil)
	     (setq stable-proc-return-types? nil)
	     (setq stable-procedure? nil))
	    ((<f (length stable-proc-return-types?) (length local-names))
	     (compiler-dependence-warning
	       "Because of a return value count mismatch for ~ND, a call to ~
                it could not be optimized."
	       designation)
	     (setq stable-proc-arg-types? nil)
	     (setq stable-proc-return-types? nil)
	     (setq stable-procedure? nil))

	    ((loop for return-type in return-types
		   for stable-proc-return-type in stable-proc-return-types?
		   thereis (not (type-specifications-could-intersect-p
				  stable-proc-return-type return-type)))
	     (compiler-dependence-warning
	       "Because of a return type mismatch for ~ND, a call to it could ~
                not be optimized."
	       designation)
	     (setq stable-proc-arg-types? nil)
	     (setq stable-proc-return-types? nil)
	     (setq stable-procedure? nil))

	    (stable-compile-time-selected-method-name?
	     (setq recorded-procedure-call-free-reference? t)
	     (record-free-reference
	       'stable-compile-time-selected-method
	       (phrase-list
		 stable-compile-time-selected-method-class?
		 stable-compile-time-selected-method-name?
		 stable-compile-time-selected-method-first-arg-class?
		 stable-proc-arg-types?
		 stable-proc-return-types?)))
		  
	    (t
	     ;; Everythings OK.
	     (setq recorded-procedure-call-free-reference? t)
	     ;; Record the defined procedure argument and return types.  Note
	     ;; that this differs from the [remote-]procedure-call
	     ;; free-reference.
	     (record-free-reference
	       (if across? 'stable-remote-procedure-call 'stable-procedure-call)
	       (phrase-list
		 designation stable-proc-arg-types?
		 ;; Truncate the return type list to only those elements that we
		 ;; actually use.
		 (loop repeat (length return-types)
		       for stable-type in 
		       stable-proc-return-types?
		       collect stable-type using phrase-cons)))))))

      (cond (stable-proc-return-types?
	     (setq desired-return-types
		   (copy-list-using-phrase-conses return-types))
	     (loop for stable-type in stable-proc-return-types?
		   for desired-type-cons on desired-return-types
		   do
	       (when (type-specification-subtype-p
		       stable-type (car-of-cons desired-type-cons))
		 (setf (car desired-type-cons) nil))))
	    (t
	     (setq desired-return-types return-types)))

      (cond ((and stable-procedure?
		  (not (inner-block-cant-be-inlined-in-outer-block?
			 stable-procedure?
			 *current-computation-frame*))
		  (md5-identifier? stable-procedure?)
		  (parse-results? stable-procedure?)
		  ;; prevent infinite compile loops
		  (not (memq stable-procedure?
			     (inlining-data-context-stack inlining-data))))
	     (compile-inline-substitution
	       (copy-tree-using-phrase-conses
		 (parse-results? stable-procedure?))
	       (car code-body-entries-in-compilation)
	       statement 
	       stable-procedure?))

	    ((null across?)
	     (when (procedure-p *current-computation-frame*)
	       ;; Work remains to be done on trees of calls that are always
	       ;; valid.  Is this a stability issue?  No recompile is needed if
	       ;; the call tree changes such that environments can be
	       ;; invalidated, all that's needed is a change in the runtime
	       ;; behavior in return-stack-values-to-caller where it checks
	       ;; procedure-environment-always-valid-p.  Hmmmm.  -jra & cpm
	       ;; 4/5/93
	       (set-procedure-call-without-validated-environment
		 *current-computation-frame*))
	     (emit-instruction
	       (if stable-procedure? 'dependent-call 'call)
	       compiled-procedure-or-rpd
	       (setq argument-stack-nodes
		     (loop for arg in args
			   for type-cons? = stable-proc-arg-types?
					  then (cdr type-cons?)
			   collect
			     (compile-stack-expression
			       arg (or (car type-cons?) 'item-or-datum))
				   using phrase-cons))
	       (length local-names))
	     (when return-spots
	       (emit-instruction
		 'receive-values return-spots desired-return-types)))
	    (t
	     (when (procedure-p *current-computation-frame*)
	       (set-procedure-call-without-validated-environment
		 *current-computation-frame*))

	     ;; Note that dependent-call-rpc won't happen until we have a
	     ;; stable-rpd-p function, not stable-procedure-p used above.  -jra
	     ;; 1/12/93
	     (emit-instruction
	       (if stable-procedure? 'dependent-call-rpc 'call-rpc)
	       compiled-procedure-or-rpd
	       (compile-procedure-expression
		 across?
		 '(class item))
	       (setq argument-stack-nodes
		     (loop for arg in args
			   for type-cons? = stable-proc-arg-types?
					  then (cdr type-cons?)
			   collect
			     (compile-stack-expression
			       arg (or (car type-cons?) 'item-or-datum))
				   using phrase-cons))
	       (length local-names))
	     (when return-spots
	       (emit-instruction
		 'receive-values return-spots desired-return-types))))
      (when (and (null recorded-procedure-call-free-reference?)
		 ;; Don't record a possible bad free-reference.
		 (null compiler-error?)
		 (symbolp designation)
		 (not (indirectly-denoted-item-p compiled-procedure-or-rpd)))
	(record-free-reference
	  (if across? 'remote-procedure-call 'procedure-call)
	  (phrase-list
	    designation
	    (loop for argument-node in argument-stack-nodes
		  collect (type-specification-minus-type 
			    (type-specification-minus-type
			      (stack-node-value-type argument-node)
			      '(unknown-datum))
			    '(no-item))
		  using phrase-cons)
	    return-types))))))




;;; The `call-next-method-assignment-statement' procedure statement emits code
;;; to check if there is a next method, to call it and receive values if there
;;; is one, and to signal an error if none exists.  This differs from
;;; call-next-method-statement which does not signal an error if there is no
;;; next method.

;;; Similar to the call-assignment-statement emits the instructions to call and
;;; receive-values.  All local names to be bound must be defined.

;;;   (CALL-NEXT-METHOD-ASSIGNMENT-STATEMENT local-names)

(def-procedure-statement-compiler (call-next-method-assignment-statement
				    write-call-next-method-assignment-statement)
  (emit-instruction
    'begin-activity (activity-index "call next method statement"))
  (setq call-statement-processed? t)
  (let* ((local-names (car-of-cons (cdr-of-cons statement)))
	 (local-var
	   (generate-new-variable-spot '(class method)))
	 (argument-descriptions
	   (get-procedure-argument-descriptions-in-context))
	 (first-arg-description (car argument-descriptions))
	 (first-arg-name (car first-arg-description))
	 ;;;propagate this
	 (method-class? (get-procedure-method-class-in-context))
	 (method-name? (get-procedure-method-name-in-context))
	 (argument-count (length argument-descriptions))
	 (call-tag (generate-new-goto-tag)))
    (emit-instruction
      'assign-local-var
      local-var
      (compile-stack-expression
	(phrase-list
	  'the
	  (phrase-list
	    'next-procedure-method method-name? method-class? argument-count)
	  first-arg-name)
	'(or (class method) (no-item))))
    (emit-branch-or-jump-if-not-true
      (compile-stack-expression
	(phrase-list 'not (phrase-list 'exists local-var))
	'boolean)
      call-tag)
    (emit-instruction
      'signal-error
      (compile-stack-expression
	'(quote no-next-method)
	'symbol)
      (compile-stack-expression
	"There is no next method defined for this method and arguments."
	'text))
    (emit-instruction 'tag-statement call-tag)
    (compile-procedure-statement
      (phrase-list
	'call-assignment-statement local-names local-var
	(loop for argument in argument-descriptions
	      collect (car argument) using phrase-cons)))))





(defmacro lisp-call-argument-count-ok-p (argument-list)
  `(<=f (length ,argument-list) maximum-number-of-lisp-call-arguments))

(defmacro lisp-call-return-value-count-ok-p (return-argument-list)
  `(<=f (length ,return-argument-list) 
	maximum-number-of-lisp-call-return-values))




;;; The `system-call-assignment-statement' is an instruction that calls the
;;; named lisp function and places the return values in local-names.  All local
;;; names to be bound must be defined.  This statement is similar to the
;;; call-assignment statement, except that it funcalls a lisp function named by
;;; the symbol argument, and compiles to only 1 instruction.  The maximum number
;;; of arguments and return values are maximum-number-of-lisp-call-arguments and
;;; maximum-number-of-lisp-call-return-values.  This statement can only be
;;; compiled in DEVELOPMENT and is for use in system procedures.

;; Note that the name of this statement was changed from called
;; lisp-call-assignment since it is only used in system procedures and the term
;; "lisp" should not become part of G2 grammar that may become visible to the
;; user.  (System procedures are currently not visible to the user.)

;;;   (SYSTEM-CALL-ASSIGNMENT-STATEMENT local-names symbol arg-expressions)

(def-procedure-statement-compiler (system-call-assignment-statement
				    write-system-call-assignment-statement)
  (compile-system-call-assignment-statement statement))


(defun compile-system-call-assignment-statement (statement)
  (emit-instruction 'begin-activity (activity-index "system call statement"))
  (gensym-dstruct-bind ((nil local-names lisp-function-name args)
		       statement)
    ;; Indicate if the function can invalidate the environment of the
    ;; system-procedure.  NOTE for this to be accurate, the lisp function must
    ;; already be declared with declare-system-procedure-function before the
    ;; system-procedure is compiled in G2!
    (unless (function-keeps-procedure-environment-valid? lisp-function-name)
      (set-procedure-call-without-validated-environment
	*current-computation-frame*))
    ;; Test the number of arguments and return values.
    (when args
      (unless (lisp-call-argument-count-ok-p args)
	(compiler-error
	  "The System-Call statement can not accept more than ~a arguments."
	  maximum-number-of-lisp-call-arguments)))
    (when local-names
      (unless (lisp-call-return-value-count-ok-p local-names)
	(compiler-error
	  "The System-Call statement can not return more than ~a values."
	  maximum-number-of-lisp-call-return-values)))

    (let ((return-spots nil)
	  (return-types nil))
      (loop with var-spot with description with type
	    for local-name in local-names
	    do
	(multiple-value-setq (var-spot description)
	  (variable-spot-and-description-for-local-name local-name))
	(setq type (getfq (cdr description) :type))
	(when (null var-spot)
	  (procedure-compiler-missing-local-name-error local-name))
	(setq return-spots (phrase-cons var-spot return-spots))
	(setq return-types (phrase-cons type return-types)))
      (setq return-spots (nreverse return-spots))
      (setq return-types (nreverse return-types))
      ;; New return-types argument for system-call stack-instruction.
      (emit-instruction
	'system-call return-spots return-types lisp-function-name
	(loop for arg in args
	      collect (compile-stack-expression arg 'item-or-datum)
		      using phrase-cons)))))



;;; The `call-statement' emits a single instruction which executes a call to the
;;; given procedure, receiving no values.  It does this by calling through to
;;; the call-assignment-statement compiler.

;;; Note that the parser no longer produces this statement, but that parses
;;; saved by the inlinging code prior to 5.0 Rev. 1 may still have references to
;;; it.  -jallard 10/3/97

;;;   (CALL-STATEMENT designation argument-expressions)

(def-procedure-statement-compiler (call-statement write-call-statement)
  (compile-procedure-statement
    (phrase-cons
      'call-assignment-statement
      (phrase-cons nil (cdr statement)))))




;;; The `call-next-method-statement' procedure statement emits code to check if
;;; there is a next method, to call it if there is one, and to do nothing if
;;; none exists.

;;; This statement is implemented by establishing a var-spot, dumping the value
;;; of the next-method role into it, then emitting code to check if the
;;; evaluation returned a value.  If so, then code is emitted to call the
;;; returned method, passing all the arguments to the
;;; current method.

;;;   (CALL-NEXT-METHOD-STATEMENT)

(def-procedure-statement-compiler (call-next-method-statement
				    write-call-next-method-statement)
  (emit-instruction
    'begin-activity (activity-index "call next method statement"))
  (setq call-statement-processed? t)
  (let* ((local-var
	   (generate-new-variable-spot '(class method)))
	 (argument-descriptions
	   (get-procedure-argument-descriptions-in-context))
	 (first-arg-description (car argument-descriptions))
	 (first-arg-name (car first-arg-description))
	 (method-class? (get-procedure-method-class-in-context))
	 (method-name? (get-procedure-method-name-in-context))
	 (argument-count (length argument-descriptions))
	 (dont-call-tag (generate-new-goto-tag)))
    (emit-instruction
      'assign-local-var
      local-var
      (compile-stack-expression
	(phrase-list
	  'the
	  (phrase-list 'next-procedure-method method-name? method-class? argument-count)
	  first-arg-name)
	'(or (class method) (no-item))))
    (emit-branch-or-jump-if-not-true
      (compile-stack-expression
	(phrase-list 'exists local-var)
	'boolean)
      dont-call-tag)
    (compile-procedure-statement
      (phrase-list
	'call-statement local-var
	(loop for argument in argument-descriptions
	      collect (car argument) using phrase-cons)))
    (emit-instruction 'tag-statement dont-call-tag)))
    






;;; The `system-call-statement' emits a single instruction which executes a call
;;; to the given lisp-function, receiving no values.  This statement is similar
;;; to the call statement, except that it funcalls a lisp function named by the
;;; symbol argument.  The maximum number of arguments is restricted to
;;; maximum-number-of-lisp-call-arguments.  This statement is only available in
;;; DEVELOPMENT and is for use in system procedures.

;; Note that the name of this statement was changed from called
;; lisp-call-assignment since it is only used in system procedures and the term
;; "lisp" should not become part of G2 grammar that may become visible to the
;; user.  (System procedures are currently not visible to the user.)

;;;   (SYSTEM-CALL-STATEMENT lisp-function-name argument-expressions)

(def-procedure-statement-compiler (system-call-statement write-system-call-statement)
  (compile-system-call-statement statement))

(defun compile-system-call-statement (statement)
  (emit-instruction 'begin-activity (activity-index "system call statement"))
  (gensym-dstruct-bind ((nil lisp-function-name args) statement)
    ;; Indicate if the function can invalidate the environment of the
    ;; system-procedure.  NOTE for this to be accurate, the lisp function must
    ;; already be declared with declare-system-procedure-function before the
    ;; system-procedure is compiled in G2!
    (unless (function-keeps-procedure-environment-valid? lisp-function-name)
      (set-procedure-call-without-validated-environment
	*current-computation-frame*))
    ;; Test the number of arguments.
    (when (and args (not (lisp-call-argument-count-ok-p args)))
      (compiler-error
	"The System-Call statement can not accept more than ~a arguments."
	maximum-number-of-lisp-call-arguments))
    (emit-instruction
      'system-call
      nil					; No return values.
      nil					; No return value types.
      lisp-function-name			; Not evaluated.
      (loop for arg in args
	    collect (compile-stack-expression arg 'item-or-datum)
		    using phrase-cons))))


;;; The `system-action' emits a single instruction which executes a call
;;; to the given the lisp-function, receiving no values. This was developed for
;;; methodized action to provide the interface to the lowest level function


(def-procedure-statement-compiler (system-action-statement write-system-call-statement)
  (compile-system-action-statement statement))

(defun compile-system-action-statement (statement)
  (emit-instruction 'begin-activity (activity-index "system call statement"))
  (gensym-dstruct-bind ((nil lisp-function-name args) statement)
    ;; Indicate if the function can invalidate the environment of the
    ;; system-procedure.  NOTE for this to be accurate, the lisp function must
    ;; already be declared with declare-system-procedure-function before the
    ;; system-procedure is compiled in G2!
    (unless (function-keeps-procedure-environment-valid? lisp-function-name)
      (set-procedure-call-without-validated-environment
	*current-computation-frame*))
    ;; Test the number of arguments.
    (when (and args (not (lisp-call-argument-count-ok-p args)))
      (compiler-error
	"The System-Call statement can not accept more than ~a arguments."
	maximum-number-of-lisp-call-arguments))
    (emit-instruction
      'system-call
      nil					; No return values.
      nil					; No return value types.
      lisp-function-name			; Not evaluated.
      (loop for arg in args
	    collect (compile-stack-expression arg 'item-or-datum)
		    using phrase-cons))))



(defun write-show-statement (statement)
  (twrite-string "System show")
  (write-expression (second statement))
  (when (> (length statement) 2)
    (write-expression (third statement))))

(def-procedure-statement-compiler (show-statement write-show-statement)
  (gensym-dstruct-bind ((nil item show-details?) statement)
    (emit-instruction
      'show-new
      (compile-stack-expression
	item '(class item))
      (compile-stack-expression
	show-details?
	(maybe-add-unknown '(structure) t)))))



(defun write-create-statement (statement)
  (twrite-string "System Create ")
  (write-expression (second statement)))

(def-procedure-statement-compiler (create-statement write-create-statement)
  (gensym-dstruct-bind ((nil class-expression local-name?) statement)
    (let ((var-spot? nil)
	  (var-spot-description? nil)
	  (var-spot-type? nil)
	  (compiler-error? nil)
	  (check-created-type? nil)
	  (created-type
	    (make-class-type-specification
	      (if (and (consp class-expression)
		       (eq (car class-expression) 'quote))
		  (second class-expression)
		  'item))))
      (when local-name?
	(multiple-value-setq (var-spot? var-spot-description?)
	  (variable-spot-and-description-for-local-name local-name?))
	(cond
	  ((null var-spot?)
	   (setq compiler-error? t)
	   (procedure-compiler-missing-local-name-error local-name?))
	  (t
	   (setq var-spot-type? (getfq (cdr var-spot-description?) :type))
	   (when (not (type-specification-subtype-p created-type var-spot-type?))
	     (cond ((type-specifications-could-intersect-p
		      created-type var-spot-type?)
		    (setq check-created-type? var-spot-type?))
		   (t
		    (compiler-error
		      "In the create action, the local name ~a is declared to ~
                       hold ~NT, not ~NT."
		      local-name? var-spot-type? created-type)))))))
	;; only use first value

      (unless compiler-error?
	(emit-instruction
	  'create
	  (compile-stack-expression
	    class-expression 'symbol)
	  var-spot?
	  check-created-type?)))))

(defun write-create-by-cloning-statement (statement)
  (twrite-string "System Create By Cloning ")
  (write-expression (second statement)))




;;; `delete-statement' added to allow delete to be methodized.
;;;  It can only be called from a system action in a procedure.

(defun write-delete-statement (statement)
  (twrite-string "System delete")
  (write-expression (second statement))
  (when (> (length statement) 2)
    (write-expression (third statement))))

(def-procedure-statement-compiler (delete-statement write-delete-statement)
  (gensym-dstruct-bind ((nil item delete-details?) statement)
    (when (procedure-p *current-computation-frame*)
	(set-procedure-can-invalidate-environment *current-computation-frame*))
    (emit-instruction
      'delete
      (compile-stack-expression
	item '(class item))
      (compile-stack-expression
	delete-details?
	(maybe-add-unknown '(structure) t)))))


;;; `activate-statement' added to allow activate to be methodized.
;;;  It can only be called from a system action in a procedure.

(defun write-activate-statement (statement)
  (twrite-string "System activate")
  (write-expression (second statement)))

(def-procedure-statement-compiler (activate-statement write-activate-statement)
  (gensym-dstruct-bind ((nil the-item details seq-var-name) statement)
    (let ((seq-var-spot? nil)
	  (seq-var-spot-description? nil)
          (compiler-error? nil))
      (when (procedure-p *current-computation-frame*)
	(set-procedure-can-invalidate-environment *current-computation-frame*))      
      (when seq-var-name
	(multiple-value-setq (seq-var-spot? seq-var-spot-description?)
	  (variable-spot-and-description-for-local-name seq-var-name))
	(cond
	  ((null seq-var-spot?)
	   (setq compiler-error? t)
	   (procedure-compiler-missing-local-name-error seq-var-name))))
      (emit-instruction
	'activate
	(compile-stack-expression
	  the-item
	  '(class item))	
	(compile-stack-expression
	  details
	  (maybe-add-unknown '(structure) t))
	seq-var-spot?))))

;;; `deactivate-statement' added to allow deactivate to be methodized.
;;;  It can only be called from a system action in a procedure.

(defun write-deactivate-statement (statement)
  (twrite-string "System deactivate")
  (write-expression (second statement)))

(def-procedure-statement-compiler (deactivate-statement write-deactivate-statement)
  (gensym-dstruct-bind ((nil item details) statement)
    (when (procedure-p *current-computation-frame*)
	(set-procedure-can-invalidate-environment *current-computation-frame*))
    (emit-instruction
      'deactivate
      (compile-stack-expression
	item '(class item))
      (compile-stack-expression
	  details
	  (maybe-add-unknown '(structure) t)))))


;;; `hide-statement' added to allow hide to be methodized.
;;;  It can only be called from a system action in a procedure.

(defun write-hide-statement (statement)
  (twrite-string "System hide")
  (write-expression (second statement))
  (write-expression (third statement)))

(def-procedure-statement-compiler (hide-statement write-hide-statement)
  (gensym-dstruct-bind ((nil workspace window?) statement)
    (emit-instruction
      'hide
      (compile-stack-expression
	workspace '(class item))
      (compile-stack-expression
	window? 'item-or-datum))))


;;; `start-kb-statement' added to allow start-kb to be methodized.
;;; It can only be called from a system action in a procedure.

(defun write-start-kb-statement (statement)
  (declare (ignore statement))
  (twrite-string "Sytem start knowledge-base"))

(def-procedure-statement-compiler (start-kb-statement write-start-kb-statement)
   (gensym-dstruct-bind ((nil) statement)
    (when (procedure-p *current-computation-frame*)
      (set-procedure-can-invalidate-environment *current-computation-frame*))
     (emit-instruction
      'start-kb-epilog)))

;;; `start-kb-statement' added to allow start-kb to be methodized.
;;; It can only be called from a system action in a procedure.

(defun write-reset-kb-statement (statement)
  (declare (ignore statement))
  (twrite-string "Sytem reset knowledge-base"))

(def-procedure-statement-compiler (reset-kb-statement write-start-kb-statement)
   (gensym-dstruct-bind ((nil) statement)
  (when (procedure-p *current-computation-frame*)
	(set-procedure-can-invalidate-environment *current-computation-frame*))
     (emit-instruction
      'reset-kb-epilog)))

;;; `enable-statement' added to allow enable to be methodized.
;;;  It can only be called from a system action in a procedure.

(defun write-enable-statement (statement)
  (twrite-string "System enable")
  (write-expression (second statement)))

(def-procedure-statement-compiler (enable-statement write-enable-statement)
   (gensym-dstruct-bind ((nil item seq-var-name) statement)
     (let ((seq-var-spot? nil)
	  (seq-var-spot-description? nil)
          (compiler-error? nil))
    (when (procedure-p *current-computation-frame*)
	(set-procedure-can-invalidate-environment *current-computation-frame*))   
    (when seq-var-name
	(multiple-value-setq (seq-var-spot? seq-var-spot-description?)
	  (variable-spot-and-description-for-local-name seq-var-name))
	(cond
	  ((null seq-var-spot?)
	   (setq compiler-error? t)
	   (procedure-compiler-missing-local-name-error seq-var-name))))
    (emit-instruction
      'enable
      (compile-stack-expression
	item '(class item))
      seq-var-spot?))))


;;; `disable-statement' added to allow disable to be methodized.
;;;  It can only be called from a system action in a procedure.

(defun write-disable-statement (statement)
  (twrite-string "System disable")
  (write-expression (second statement)))

(def-procedure-statement-compiler (disable-statement write-disable-statement)
   (gensym-dstruct-bind ((nil item) statement)
    (when (procedure-p *current-computation-frame*)
       (set-procedure-can-invalidate-environment *current-computation-frame*))
     (emit-instruction
      'disable
      (compile-stack-expression
	item '(class item)))))

;;; `print-statement' added to allow print to be methodized.
;;;  It can only be called from a system action in a procedure.

(defun write-print-statement (statement)
  (twrite-string "System print")
  (write-expression (second statement)))

(def-procedure-statement-compiler (print-statement write-print-statement)
  (gensym-dstruct-bind ((nil the-item) statement)
    (emit-instruction
      'print
      (compile-stack-expression
	the-item
       '(class workspace)))))

;;; The `allow-other-processing-statement' emits itself verbatim.

;;;   (ALLOW-OTHER-PROCESSING)

(def-procedure-statement-compiler (allow-other-processing-statement
				    write-allow-other-processing-statement)
  (when (procedure-p *current-computation-frame*)
    (set-procedure-contains-wait-state *current-computation-frame*))
  (emit-instruction
    'begin-activity (activity-index "allow other processing statement"))
  (emit-instruction 'allow-other-processing))




;;; The `collect-data-statement' emits a call to the collect-data instruction.
;;; If a timeout has been specified, generate a var spot to hold the expiration
;;; time, and emit a statement to set that var spot before the collect data
;;; instruction.  If a timeout statement has also been specified, emit it
;;; immediately after the collect data instruction, and give the collect data
;;; instruction the tags entering the timeout statement as the failure address,
;;; and the tag just after the timeout statement as the success address.

;;; This instruction must be changed to manage its own stack frame variables.
;;; This must be done by changing the pseudo-instruction emitter to allocate and
;;; deallocate then, and to reallocate them after any wait states.  -jra 9/5/91

;;;   (COLLECT-DATA-STATEMENT 
;;;     local-name-expression-pairs timeout? timeout-statement?)

(def-procedure-statement-compiler
  (collect-data-statement write-collect-data-statement)
  (when (procedure-p *current-computation-frame*)
    (set-procedure-contains-wait-state *current-computation-frame*))
  (emit-instruction 'begin-activity (activity-index "collect data statement"))
  (gensym-dstruct-bind ((nil name-expression-pairs timeout? timeout-statement?)
		       statement)
    (let* ((evals-succeeded-spot (generate-new-variable-spot 'truth-value))
	   (timeout-spot? nil)
	   (timeout-predicate? nil)
	   (time-remaining-expression? nil)
	   (success-tag? (generate-new-goto-tag))
	   (timeout-tag? (if timeout-statement?
			     (generate-new-goto-tag)
			     success-tag?)))
      (when timeout?
	(let ((timeout-time-compiled
		(compile-stack-expression
		  (phrase-list '+ '(current-subsecond-time) timeout?)
		  'float)))
	  (setq timeout-spot?
		(generate-new-variable-spot 'float))
	  (emit-instruction
	    'assign-local-var
	    timeout-spot?
	    timeout-time-compiled)
	  (setq timeout-predicate?
		(compile-stack-expression
		  (phrase-list '>= '(current-subsecond-time) timeout-spot?)
		  'truth-value))
	  (setq time-remaining-expression?
		(compile-stack-expression
		  (phrase-list '- timeout-spot? '(current-subsecond-time))
		  'float))))
      (loop with result-pairs = nil
	    with var-spot
	    with description
	    with type
	    for (local-name expression) in name-expression-pairs
	    do
	(multiple-value-setq (var-spot description)
	  (variable-spot-and-description-for-local-name local-name))
	(setq type (getfq (cdr description) :type))
	(when (null var-spot)
	  (procedure-compiler-missing-local-name-error local-name)
	  (setq type 'item-or-datum))
	(setq result-pairs
	      (phrase-cons
		(phrase-list
		  var-spot
		  (compile-stack-expression
		    expression
		    (make-type-specification-union
		      type '(unknown-datum))))
		result-pairs))
	    finally
	  (emit-instruction
	    'collect-data  (nreverse result-pairs) timeout-spot? success-tag?
	    timeout-tag? timeout-predicate? evals-succeeded-spot
	    time-remaining-expression?))
      (when timeout-statement?
	(emit-instruction 'tag-statement timeout-tag?)
	(compile-procedure-statement timeout-statement?))
      (emit-instruction 'tag-statement success-tag?))))




;;; The `do-in-parallel' statement enters a new code body lexical layer for each
;;; of the statements given to it and compiles those statements within those
;;; layers.  Each of these code bodies is completed with a close-code-body
;;; instruction.  Within the code body which called this statement, instructions
;;; are emitted which launch each of the generated code bodies in turn.  After
;;; each of these is emitted, an instruction is emitted which will wait until
;;; there are no more called code bodies left for this code body before
;;; proceeding.
;;;
;;;   (DO-IN-PARALLEL-STATEMENT . statements)

(def-procedure-statement-compiler
  (do-in-parallel-statement write-do-in-parallel-statement)
  (when (procedure-p *current-computation-frame*)
    (set-procedure-contains-wait-state *current-computation-frame*))
  (emit-instruction 'begin-activity (activity-index "do in parallel statement"))
  (let ((code-bodies-to-launch nil))
    (loop for parallel-statement in (cdr statement)
	  do
      (enter-new-code-body nil
	(setq code-bodies-to-launch
	      (phrase-cons (compiler-code-body-entry-number
			     (current-compiler-code-body))
			   code-bodies-to-launch))
	(record-goto-tags parallel-statement)
	(compile-procedure-statement parallel-statement)
	(emit-instruction 'close-code-body)))
    (loop for code-body-number in (nreverse code-bodies-to-launch)
	  do
      (emit-instruction 'call-code-body code-body-number))
    (emit-instruction 'wait-for-called-code-bodies)))




;;; The `do-in-parallel-until-one-completes' statement enters a new code body
;;; lexical layer for each of the statements given to it and compiles those
;;; statements within those layers.  Each of these code bodies is completed with
;;; a jump to a tag generated for the end of the statement.  Within the code
;;; body which called this statement, instructions are emitted which launch each
;;; of the generated code bodies in turn.  After each of these is emitted, a
;;; pause instruction is emitted which cause the surrounding code body to enter
;;; a wait state, giving the launched code bodies a chance to run.  The winner
;;; of the race will branch to the tag at the end of this statement in the
;;; surrounding code body, which causes it in turn to abort the remaining code
;;; body invocations.

;;;   (DO-IN-PARALLEL-UNTIL-ONE-COMPLETES-STATEMENT . statements)

(def-procedure-statement-compiler
  (do-in-parallel-until-one-completes-statement
    write-do-in-parallel-until-one-completes-statement)
  (when (procedure-p *current-computation-frame*)
    (set-procedure-contains-wait-state *current-computation-frame*))
  (emit-instruction
    'begin-activity
    (activity-index "do in parallel until one completes statement"))
  (let ((statements (cdr statement)))
    (when statements
      (let ((code-bodies-to-launch nil)
	    (winner-tag (generate-new-goto-tag)))
	(loop for parallel-statement in (cdr statement)
	      do
	  (enter-new-code-body nil
	    (setq code-bodies-to-launch
		  (phrase-cons (compiler-code-body-entry-number
				 (current-compiler-code-body))
			       code-bodies-to-launch))
	    (record-goto-tags parallel-statement)
	    (compile-procedure-statement parallel-statement)
	    (emit-branch-or-jump winner-tag)))
	(loop for code-body-number in (nreverse code-bodies-to-launch)
	      do
	  (emit-instruction 'call-code-body code-body-number))
	(emit-instruction 'pause)
	(emit-instruction 'tag-statement winner-tag)))))




;;; The `wait-for-statement' emits a call to the wait-for instruction, with the
;;; wait-interval expression compiled.
;;;
;;;   (WAIT-FOR-STATEMENT interval-expression)

(def-procedure-statement-compiler (wait-for-statement write-wait-for-statement)
  (when (procedure-p *current-computation-frame*)
    (set-procedure-contains-wait-state *current-computation-frame*))
  (emit-instruction
    'begin-activity (activity-index "wait for interval statement"))
  (emit-instruction
    'wait-for-interval
    (compile-stack-expression (second statement) 'number)))



;;; The `wait-until-statement' compiler emits a call to the polled-wait
;;; instruction, with the logical continue expression and the wait interval
;;; expression compiled.
;;;
;;;   (WAIT-UNTIL-STATEMENT
;;;     inferred-logical-expression cycle-interval-expression)

(def-procedure-statement-compiler (wait-until-statement
				    write-wait-until-statement)
  (when (procedure-p *current-computation-frame*)
    (set-procedure-contains-wait-state *current-computation-frame*))
  (emit-instruction 'begin-activity (activity-index "wait until statement"))
  (emit-instruction
    `polled-wait
    (compile-stack-expression
      (second statement) '(or truth-value (unknown-datum)))
    (compile-stack-expression (third statement) 'number)
    (generate-new-variable-spot 'number)))




;;; The `wait-until-event-statement' compiler receives an event antecedent.
;;; These expressions are either event expressions, or an AND of an event
;;; expression and a logical expression.  This statement compiles into a set of
;;; expressions for installing event detectors on frames, a pause statement,
;;; statements for removing event detectors, and then if there is a logical
;;; expression, a collect data statement for the logical value, and a branch if
;;; false back to the top of this set of instructions.

;;; Note that at this time, the only event that can be detected in receiving a
;;; value, and there is no and-when clause.

;;;   (WAIT-UNTIL-EVENT-STATEMENT event-predicate)

(def-procedure-statement-compiler
  (wait-until-event-statement write-wait-until-event-statement)
  (when (procedure-p *current-computation-frame*)
    (set-procedure-contains-wait-state *current-computation-frame*))
  (emit-instruction
    'begin-activity (activity-index "wait until event statement"))
  (let* ((event-antecedent (second statement))
	 (events (if (and (consp event-antecedent)
			  (eq (car event-antecedent) 'or))
		     (cdr event-antecedent)
		     (phrase-list event-antecedent))))
    (loop for event in events
	  for event-type = (if (consp event)
			       (car-of-cons event))
	  do
      (case event-type
	((receives-a-value)
	 (let ((designation (second event)))
	   (emit-instruction
	     'install-event-detector
	     (compile-stack-expression
	       designation
	       '(or (class variable-or-parameter) (place-reference)))
	     (compile-stack-expression
	       '(quote receives-a-value)
	       'symbol))))
	(otherwise
	 (compiler-bug
	   "wait until event statement"
	   "The malformed event ~a was received."
	   event))))
    (emit-instruction 'wait)
    (emit-instruction 'clear-event-detectors)))




;;; The `system wait statement' compiler emits an instruction which enters a
;;; wait state.  This should be used within system procedures which will wake up
;;; the code body invocation based on some other asynchronous event

(def-procedure-statement-compiler
  (system-wait-statement write-system-wait-statement)
  (when (procedure-p *current-computation-frame*)
    (set-procedure-contains-wait-state *current-computation-frame*))
  (emit-instruction 'wait))




;;; The `on error statement' provides error handling features for a protected
;;; set of forms.  The first argument is a statement which should be within the
;;; protected scope.  The second and third arguments are local names for the
;;; error name symbol and the error description as a text.  The fourth argument
;;; is a statement which is executed when an error occurs within the protected
;;; scope.

;;; This is implemented by emitting two new code bodies, the handler code body
;;; and the protected code body.  The error handler code body is called from the
;;; original code body.  The initial code within the error handler code body
;;; should call the protected code body, and if execution normally proceeds to
;;; the end of the protected body, then the protected code body should jump to
;;; the end of the on-error-statement within the original code body.

;;; However if an error occurs, a throw is done from raw-stack-error, and the
;;; resulting code searches for an error handler spec, finding it in the error
;;; handler code body.  Once found, it sets the local vars to the error name and
;;; description, and executes a jump to an instruction within the error handling
;;; code body.  This code in turn immediately jumps to the error handler
;;; statement, which is compiled into the original code body.  The contents of
;;; the error handler spec slot should be a list of an address to branch to
;;; within the error handler code body, and the var spots for the error name and
;;; error description variables.

;; Note that the handler code body could be eliminated, if the error handler
;; spec were instead put onto the protected code body, but contained a program
;; counter for the original code body.  An earlier implementation which had bugs
;; required the intermediate code body, and we are too close to beta now to try
;; and rewrite the compiler code which would handle this stuff.  -jra 1/14/92

;; Eliminated the handler code body.  The error handler spec is now on the
;; protected code body and will contain a program counter for the original
;; code body.  ajs (7/3/96)

(def-procedure-statement-compiler (on-error-statement print-on-error-statement)
  (emit-instruction 'begin-activity (activity-index "on error statement"))
  (gensym-dstruct-bind ((nil protected-statement
			    error-name error-text handler-statement)
		       statement)
    (let ((protected-code-body nil)
	  (cleanup-code-tag nil)
	  (no-error-tag nil))
      (enter-new-lexical-tag-layer
	(setq cleanup-code-tag (generate-new-goto-tag))
	(setq no-error-tag (generate-new-goto-tag))
	(record-goto-tags handler-statement)
	(multiple-value-bind
	    (error-name-var-spot error-name-description)
	    (variable-spot-and-description-for-local-name error-name)
	  (ensure-var-spot-receives-type
	    error-name error-name-var-spot error-name-description 'symbol)
	  (multiple-value-bind
	      (error-text-var-spot error-text-description)
	      (variable-spot-and-description-for-local-name error-text)
	    (ensure-var-spot-receives-type
	      error-text error-text-var-spot error-text-description 'text)
	    (enter-new-code-body nil
	      (setq protected-code-body
		    (compiler-code-body-entry-number
		      (current-compiler-code-body)))
	      (record-goto-tags protected-statement)
	      (compile-procedure-statement protected-statement)
	      (emit-branch-or-jump no-error-tag)
	      (register-error-handler-spec
		(phrase-list
		  cleanup-code-tag
		  (var-spot-index-of-var-spot error-name-var-spot)
		  (var-spot-index-of-var-spot error-text-var-spot)))
	      ;; The following line will set the flag on the tag-entry that
	      ;; marks this tag as the target of a jump statements.  This
	      ;; prevents this tag from being eliminated by dead-code
	      ;; elimination.  -jra&ajs 7/3/96
	      (jump-depth-for-tag? cleanup-code-tag)
	      )))
	;; Within the original code body, call the protected code body,
	;; then pause.
	(emit-instruction 'call-code-body protected-code-body)
	;;handler-code-body)
	(emit-instruction 'pause)
	;; If there is an error, a jump will be done to the clean up code.
	(emit-instruction 'tag-statement cleanup-code-tag)
	(compile-procedure-statement handler-statement)
	;; After the handler, control falls off the end of this statement.  In
	;; case of normal execution of the protected code, a jump is done to the
	;; no-error-tag.
	(emit-instruction 'tag-statement no-error-tag)))))


;;; The `on-error-statement-new' procedure statement provides the functionality
;;; of on-error-statement with the difference that it compiles a one
;;; argument version of on-error.  The error handling spec created by this
;;; compiler will contain three elements; (i) a program counter,
;;; (ii) the var spot for the error object, and (iii) a class description
;;; of the error variable.  - ajs (5/24/96)

(def-procedure-statement-compiler (on-error-statement-new print-on-error-statement-new)
  (emit-instruction 'begin-activity (activity-index "on error statement"))
  (gensym-dstruct-bind ((nil protected-statement
			    error handler-statement)
		       statement)
    (let ((protected-code-body nil)
	  (cleanup-code-tag nil)
	  (no-error-tag nil))
      (enter-new-lexical-tag-layer
	(setq cleanup-code-tag (generate-new-goto-tag))
	(setq no-error-tag (generate-new-goto-tag))
	(record-goto-tags handler-statement)
	(multiple-value-bind
	    (error-var-spot error-description)
	    (variable-spot-and-description-for-local-name error)
	  (enter-new-code-body nil
	    (setq protected-code-body
		  (compiler-code-body-entry-number (current-compiler-code-body)))
	    (record-goto-tags protected-statement)
	    (compile-procedure-statement protected-statement)
	    (emit-branch-or-jump no-error-tag)
	    (ensure-var-spot-receives-type
	      error error-var-spot error-description '(class error))
	    (register-error-handler-spec
	      (phrase-list 
		cleanup-code-tag
		(var-spot-index-of-var-spot error-var-spot)
		(getfq (cdr error-description) :type)))
	  ;; The following line will set the flag on the tag-entry that
	  ;; marks this tag as the target of a jump statement.  This
	  ;; prevents this tag from being eliminated by dead-code
	  ;; elimination.  -jra&ajs 7/3/96
	  (jump-depth-for-tag? cleanup-code-tag)
	  ))
	;; Within the original code body, call the protected code body,
	;; then pause.
	(emit-instruction 'call-code-body protected-code-body)
	(emit-instruction 'pause)
	;; If there is an error, a jump will be done to the clean up code.
	(emit-instruction 'tag-statement cleanup-code-tag)
	(compile-procedure-statement handler-statement)
	;; After the handler, control falls off the end of this statement.  In
	;; case of normal execution of the protected code, a jump is done to the
	;; no-error-tag.
	(emit-instruction 'tag-statement no-error-tag)))))


(defun ensure-var-spot-receives-type (var-name var-spot? description? type)
  (if (null var-spot?)
      (procedure-compiler-missing-local-name-error var-name)
      (let ((var-spot-type? (getfq (cdr description?) :type)))
	(cond ((null var-spot-type?)
	       (compiler-error
		 "No type could be determined for the local varible ~a."
		 var-name))
	      ((not (type-specifications-could-intersect-p var-spot-type? type))
	       (compiler-error
		 "The type of ~a, ~NT does not allow it to receive values of ~
                  type ~NT."
		 var-name var-spot-type? type)))))
  nil)

(defun register-error-handler-spec (spec)
  (setf (compiler-code-body-error-handler-spec? (current-compiler-code-body))
	spec)
  nil)



;;; The signal statement signals an error given an error name symbol and an
;;; error string text.  The error proceeds through the normal error handling
;;; mechanism like any error in a procedure.

(def-procedure-statement-compiler (signal-statement print-signal-statement)
  (emit-instruction 'begin-activity (activity-index "signal error statement"))
  (emit-instruction
    'signal-error
    (compile-stack-expression (second statement) 'symbol)
    (compile-stack-expression (third statement) 'text)))

 
;;; The signal-statement-new signals an error statement given an error
;;; object. ajs (5/28/96)

(def-procedure-statement-compiler (signal-statement-new print-signal-statement-new)
  (emit-instruction 'begin-activity (activity-index "signal error statement"))
  (emit-instruction
    'signal-error-new
    (compile-stack-expression (second statement) '(class error))))


;;; The `create' action is used to instantiate new transient objects in
;;; procedures.  Normally this action would be compile with the procedure action
;;; compilers below, but since this action requires a local name as the optional
;;; designation, and since we have no action template form type for local-names,
;;; a specific compiler must be used.
;;;
;;;   (CREATE class-expression local-name?)




;;; The `create-connection' action is used to instantiate new transient
;;; connections in procedures.
;;;
;;;   (CREATE-CONNECTION class-expression connection-specification local-name?)

;; The procedure statement compiler for Create-Connection is now in PROC-INST.




;;; The macro `procedure-explanation-type-p' is used in the procedure
;;; statement compiler to test for an explanation description-type.

(def-substitution-macro procedure-explanation-type-p (type)
  (and (consp type)
       (eq (first type) 'class)
       (eq (second type) 'explanation)))




;;; The `create-explanation' action is used to instantiate new
;;; explanations (transient objects) in procedures.  Normally this action
;;; would be compiled with the procedure action compilers below, but since this
;;; action requires a local name as the optional designation, and since we have
;;; no action template form type for local-names, a specific compiler must be
;;; used.
;;;
;;;   (CREATE-EXPLANATION designation local-name?)

;; The procedure statement compiler for Create-Explanation is now in
;; PROC-INST.






;;;; Procedure Instruction Tag Replacers




;;; For every pseudo-code instruction in the system which holds tags there
;;; should be a definition here for a goto-tag-replacer and an accessor for
;;; the referenced procedure tags.  The tag replacer will be called when
;;; emitting code so that tags can be replaced with accurate instruction
;;; addresses.  The referenced tag accessor will be called when optimizing code
;;; to determine those tags which are declared but no longer referenced.

;;; (BRANCH instruction-index)

(def-goto-tag-references branch
  (cdr-of-cons instruction))

(def-goto-tag-replacer branch
  (setf (second instruction)
	(instruction-address-for-tag (second instruction) nil))
  instruction)



;;; (BRANCH-IF-KNOWN instruction-index)

(def-goto-tag-references branch-if-known
  (cdr-of-cons instruction))

(def-goto-tag-replacer branch-if-known
  (setf (second instruction)
	(instruction-address-for-tag (second instruction) nil))
  instruction)

;;;   (RESTORE-FROM-ACTION-CACHE-OR-BRANCH
;;;     action-cache? var-spot-block action-cache-empty-tag?)

(def-goto-tag-references restore-from-action-cache-or-branch
  (cdr-of-cons (cdr-of-cons (cdr-of-cons instruction))))

(def-goto-tag-replacer restore-from-action-cache-or-branch
  (setf (fourth instruction)
	(instruction-address-for-tag (fourth instruction) nil))
  instruction)


;;; (BRANCH-IF-TRUE logical-expression target-address)

(def-goto-tag-references branch-if-true
  (cdr-of-cons (cdr-of-cons instruction)))

(def-goto-tag-replacer branch-if-true
  (setf (third instruction)
	(instruction-address-for-tag (third instruction) nil))
  instruction)




;;; (BRANCH-IF-NOT-TRUE logical-expression target-address)

(def-goto-tag-references branch-if-not-true
  (cdr-of-cons (cdr-of-cons instruction)))

(def-goto-tag-replacer branch-if-not-true
  (setf (third instruction)
	(instruction-address-for-tag (third instruction) nil))
  instruction)




;;; (CASE-DISPATCH expression table-base table-length else-tag tag-table)

(def-goto-tag-references case-dispatch
  (gensym-dstruct-bind ((nil nil nil nil else-tag tag-table) instruction)
    (phrase-cons else-tag tag-table)))

(def-goto-tag-replacer case-dispatch
  (gensym-dstruct-bind ((nil nil nil nil else-tag tag-table) instruction)
    (setf (fifth instruction)
	  (instruction-address-for-tag else-tag nil))
    (loop for tag-cons on tag-table do
      (setf (car-of-cons tag-cons)
	    (instruction-address-for-tag (car-of-cons tag-cons) nil)))
    instruction))




;;;   (OPEN-ROLE-ITERATION
;;;      role continuation-spot value-spot value-type role-type?
;;;      no-value-tag domain-designation)

;;;   (OPEN-ROLE-ITERATION-NO-DOMAIN
;;;      role continuation-spot value-spot value-type role-type?
;;;      no-value-tag)

(def-goto-tag-references open-role-iteration
  (phrase-list (seventh instruction)))

(def-goto-tag-replacer open-role-iteration
  (setf (seventh instruction)
	(instruction-address-for-tag (seventh instruction) nil))
  instruction)

(def-goto-tag-references open-role-iteration-no-domain
  (nthcdr 6 instruction))

(def-goto-tag-replacer open-role-iteration-no-domain
  (setf (seventh instruction)
	(instruction-address-for-tag (seventh instruction) nil))
  instruction)




;;;   (SERVE-NEXT-ITERATION-VALUE
;;;     continuation-spot value-spot required-type iteration-type?
;;;     no-values-tag)

(def-goto-tag-references serve-next-iteration-value
  (cdr-of-cons (cdr-of-cons (cdr-of-cons (cdr-of-cons (cdr-of-cons instruction))))))

(def-goto-tag-replacer serve-next-iteration-value
  (setf (sixth instruction)
	(instruction-address-for-tag (sixth instruction) nil))
  instruction)




;;; (JUMP levels-to-jump-out instruction)

(def-goto-tag-replacer jump
  (setf (third instruction)
	(instruction-address-for-tag (third instruction) t))
  instruction)

(def-goto-tag-references jump
  (cdr-of-cons (cdr-of-cons instruction)))




;;; (COLLECT-DATA name-expression-pairs var-spot success-tag? failure-tag?)

(def-goto-tag-replacer collect-data
  (gensym-dstruct-bind ((nil nil nil success-tag? failure-tag?) instruction)
    (when success-tag?
      (setf (fourth instruction)
	    (instruction-address-for-tag success-tag? nil)))
    (when failure-tag?
      (setf (fifth instruction)
	    (instruction-address-for-tag failure-tag? nil)))
    instruction))


(def-goto-tag-references collect-data
  (gensym-dstruct-bind ((nil nil nil success-tag? failure-tag?) instruction)
    (cond ((and success-tag? failure-tag?)
	   (phrase-list success-tag? failure-tag?))
	  (success-tag?
	   (phrase-list success-tag?))
	  (failure-tag?
	   (phrase-list failure-tag?))
	  (t nil))))




;;; The referencer for execute-antecedent is unusual, in that it may decline to
;;; return some tags if it can determine that they are unreachable through
;;; analysis of the antecedent expression.  

;;;   (EXECUTE-ANTECENDENT
;;;     logical-expression certainty-cache? expiration-cache?
;;;     true-tag false-tag unknown-tag?)

(def-goto-tag-replacer execute-antecedent
  (setf (fifth instruction)
	(instruction-address-for-tag (fifth instruction) nil))
  (setf (sixth instruction)
	(instruction-address-for-tag (sixth instruction) nil))
  (when (seventh instruction)
    (setf (seventh instruction)
	  (instruction-address-for-tag (seventh instruction) nil)))
  instruction)

(def-goto-tag-references execute-antecedent
  (cdr-of-cons (cdr-of-cons (cdr-of-cons (cdr-of-cons instruction)))))




;;; (EXECUTE-SIMULATION-FORMULA expression result-var-spot unknown-tag)

(def-goto-tag-replacer execute-simulation-formula
  (setf (fourth instruction)
	(instruction-address-for-tag (fourth instruction) nil))
  instruction)

(def-goto-tag-references execute-simulation-formula
  (cdr-of-cons (cdr-of-cons (cdr-of-cons instruction))))
