;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; constant -- make constants
;;;
;;; Author : John Gilson
;;; Date   : 21 May 1990
;;;
;;; Copyright (c) 1990, Chestnut Software, Inc.
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/constant.lisp,v $"
 "$Revision: 1.7 $"
 "$Date: 2007/06/22 19:50:28 $")

;;; This implementation uses the ANSI CL model of constant dumping that
;;; assumes that for each constant there is a creation form and 
;;; initialization form that are executed at load-time to build and 
;;; initialize an object that is "similar as a constant" to the original 
;;; compile-time object.  The general idea is that, after we have 
;;; identified all of the constants that are referenced within an
;;; ordinary leaf top-level form, we merge the code to initialize these
;;; constants onto the top-level-form initialization function for the
;;; file just ahead of the code corresponding for the top-level form
;;; that references them.  Things are a little tricky because the
;;; constant creation and initialization code might also recursively
;;; reference other constants.
;;;
;;; As an extension, this implementation also supports "conditional
;;; initializers" in situations where a circular reference appears in
;;; the create form for a constant.  The way this works is that an
;;; arbitrary value appears in place of the circular reference and
;;; some additional code is added to its initialization code to fill in
;;; the reference once the circularly referenced object has been created.
;;; 
;;; Note that all of this handling only applies to "structured" 
;;; constants.  Constants having an immediate representation in the
;;; C code (such as fixnums and characters) are handled completely 
;;; differently.
;;;
;;; The collection of constants referenced in a top-level form is performed
;;; during the gather phase.
;;;
;;; The initial call to do-constant-processing is made from
;;; translate-leaf-toplevel-form-aux, in codewalk.lisp.
;;;
;;; The function merge-initcode (in codewalk.lisp) is used to add things
;;; to the initialization function for the file being translated.
;;;


;;; Define some utilities for keeping track of constants being processed.
;;; Instead of collecting up a list or hash table to record the constants
;;; we are traversing recursively, just set a flag on the variable-records.

(defmacro pending-constant-p (record)
  `(variable-record-pending-constant-p ,record))

(defmacro with-pending-constant (record &body body)
  (let ((temp  (gensym)))
    `(let ((,temp ,record))
       (setf (variable-record-pending-constant-p ,temp) t)
       (unwind-protect (progn ,@body)
	 (setf (variable-record-pending-constant-p ,temp) nil)))))



;;; We don't need to test for sharing of load-time-value expressions.
;;; Just go off and mess with the create-form.

(defun process-load-time-value (construct)
  (multiple-value-bind (record create-form)
      (dump-load-time-value (second construct))
    (setf (fourth construct) record)
    (process-constant-aux record create-form nil nil)))


;;; Actually do the work of recursively processing the create and init
;;; statements for a "new" constant.

(defun process-constant-aux (record create-form init-form
				    conditional-init-forms)
  (let ((c-delayed-inits   nil) ; delayed initializations from create-form
	(r-delayed-inits   nil) ; delayed initializations returned
	(create-statements nil)
	(init-statements   nil))
    ;; Collect delayed initializations for constants referenced in the
    ;; create statements.  It is an error if there are circular references 
    ;; to constants that are not handled by the conditional-init-forms.
    (let ((pregather-info
	   (pregather-info-list
	    (setq create-statements
		  (nreverse
		   (translate-form create-form *environment*
				   (make-target-form 'constant-label
						     record))))
	    nil)))
      (multiple-value-bind (my-delayed-inits my-dependencies)
	  (with-pending-constant record
	    (do-constant-processing
		(pregather-info-local-constants pregather-info)
	      (pregather-info-global-constants pregather-info)))
	(setq c-delayed-inits my-delayed-inits)
	(multiple-value-setq (my-dependencies init-form)
	  (merge-conditional-init-forms
	   my-dependencies init-form conditional-init-forms))
	(if my-dependencies
	    (error "Circular reference in constant creation form.")
	    (merge-initcode create-statements pregather-info))))
    ;; Now collect delayed initializations for constants referenced in
    ;; the init statements.  If these contain circular references to 
    ;; constants whose creation forms are still pending, delay the execution
    ;; of the init form until after all the pending constants in the 
    ;; dependencies list have been created.  Otherwise if there are no 
    ;; dependencies, the initialization form is required to be executed 
    ;; immediately after the creation form.
    (let ((pregather-info
	   (pregather-info-list
	    (setq init-statements
		  (nreverse
		   (translate-form init-form *environment* *ignore-context*)))
	    nil)))
      (multiple-value-bind (my-delayed-inits my-dependencies)
	  (do-constant-processing
	      (pregather-info-local-constants pregather-info)
	    (pregather-info-global-constants pregather-info))
	(setq r-delayed-inits my-delayed-inits)
	;; Continue from here
	(if my-dependencies
	    (push (list my-dependencies init-statements pregather-info)
		  r-delayed-inits)
	    (merge-initcode init-statements pregather-info))))
    ;; Finally, if there were any initializers for constants referenced
    ;; within the create form that were being delayed until this constant 
    ;; was fully created and initialized, go ahead and merge them now.
    ;; Return the remaining delayed inits.
    (dolist (p c-delayed-inits)
      (cond ((not (member record (car p)))
	     (push p r-delayed-inits))
	    ((null (cdr (car p)))
	     (apply #'merge-initcode (cdr p)))
	    (t
	     (setf (car p) (delete record (car p)))
	     (push p r-delayed-inits))))
    (values (nreverse r-delayed-inits) nil)))



;;; If there were any circular constant references found in processing the
;;; create form for a constant, see if we can patch the reference later
;;; by using a conditional-init-form.

(defun merge-conditional-init-forms (dependencies init-form
						  conditional-init-forms)
  (let ((remaining-dependencies   nil)
	(temp                     nil))
    (dolist (d dependencies)
      (if (setq temp (conditional-init-forms-p d conditional-init-forms))
	  (setq init-form `(progn ,@temp ,init-form))
	  (push d remaining-dependencies)))
    (values (nreverse remaining-dependencies) init-form)))


;;; See if there are any conditional init forms matching the given record.
;;; The a-list is a list of (constant . form)s, so we have to find
;;; the constant corresponding to the record and match on that.  There
;;; might be multiple entries in the a-list that correspond to the
;;; constant.  Return a list of them.

(defun conditional-init-forms-p (record constant-form-alist)
  (let ((results  nil))
    (dolist (stuff constant-form-alist)
      (if (eq (find-constant (car stuff)) record)
	  (push (cdr stuff) results)))
    results))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    utilities
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; Structured constants are given labels with names derived from their 
;;; types and a counter.  The name mapper is used to avoid name collisions.

(defmacro make-constant-label (type)
  (if (constantp type)
      (sformat "~a_CONSTANT" (eval type))
      `(sformat "~a_CONSTANT" ,type)))



;;; When dumping arrays, we need to check whether it is a vector with
;;; a fill pointer.  If so, we dump only the active elements of the
;;; vector.

(defun active-array-dimensions (object)
  (if (array-has-fill-pointer-p object)
      (list (fill-pointer object))
      (array-dimensions object)))



;;; For strings and floats, do something of a hack.  The untagged C objects
;;; have immediate representations but the tagged Lisp versions do not.
;;; So introduce abstractions to represent the untagged objects and treat
;;; those separately from the tagged objects.

(defstruct c-string
  string)

(defstruct c-float
  float)

(defstruct c-array
  array
  element-type
  dimensions)

;;; Immediate constants are handled specially in the codewalker.  Here
;;; is a predicate the codewalker can use to identify them.

(defun immediate-constant-p (object)
  (cond ((c-string-p object)
	 (values (translator-foreign-type :static-string)
		 (c-string-string object)))
	((trun:fixnump object)
	 (values (translator-foreign-type :fixnum) object))
	((characterp object)
	 (values (translator-foreign-type :char) object))
	((c-float-p object)
	 (values (translator-foreign-type :static-float) (c-float-float object)))
	(t
	 (values nil nil))))


;;; This helper function is for DEFCONSTANT.
;;; If the value of a DEFCONSTANT form is a "simple" constant, we can
;;; #define it directly to its value instead of indirecting through 
;;; the symbol-value of the symbol.
;;; The objects that are "simple" are immediate constants and initial
;;; symbols (which have corresponding global C variables).

(defun simple-constant-p (object)
  ;(progn (print "simple-constant-p")(print object))
  (cond ((trun:fixnump object))
	((characterp object))
	((symbolp object)
	 (when (initial-symbol-p object)
	   (mark-quoted-symbol object)
	   t))
	((packagep object)
	 (initial-package-p object))))




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Setup and type discrimination
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; For each "kind" of constant, we need to define three functions:
;;; * a function to compute a hash value for the object.  
;;; * a function to see if two objects of that type are similar-as-constants
;;; * a function to compute the create/init forms for dumping the constant.
;;; It would be nice to use generic functions to do this sort of thing....

(define-hashed-structure constant-type
  hash-function
  compare-function
  dump-function
  tagging-macro
  constants-table-alist)

(defmacro constants-table (type)
  `(cdr (let ((alist (constants-table-alist ,type)))
	  (if (and (consp alist)
		   (eq (caar alist) *current-translated-file*))
	      (car alist)
	      (assq *current-translated-file* 
		    (constants-table-alist ,type))))))

(defsetf constants-table (type) (value)
  `(push (cons *current-translated-file* ,value)
         (constants-table-alist ,type)))

(defun reset-constant-tables (current-p)
  (maphash #'(lambda (name ct)
	       (declare (ignore name))
	       (setf (constant-type-constants-table-alist ct)
		     (when current-p
		       (remove *current-translated-file*
			       (constant-type-constants-table-alist ct)
			       :key #'car))))
	   *constant-type-table*))

;;; Initialize the tables for all of the other functions.

(define-constant-type immediate
    :hash-function    hash-immediate
    :compare-function similar-if-eql-p
    :dump-function    dump-immediate
    :tagging-macro    :none
    )

(define-constant-type string
    :hash-function    hash-immediate
    :compare-function similar-strings-p
    :dump-function    dump-string
    :tagging-macro    trun:%tag-string
    )

(define-constant-type symbol
    :hash-function    hash-immediate
    :compare-function similar-if-eql-p
    :dump-function    dump-symbol
    :tagging-macro    trun:%tag-uninterned-symbol
    )

(define-constant-type package
    :hash-function    hash-immediate
    :compare-function similar-if-eql-p
    :dump-function    dump-package
    )

(define-constant-type cons
    :hash-function    hash-cons
    :compare-function similar-conses-p
    :dump-function    dump-cons
    :tagging-macro     trun:%tag-cons
    )

(define-constant-type array
    :hash-function    hash-array
    :compare-function similar-arrays-p
    :dump-function    dump-array
    :tagging-macro     :nonstandard
    )

(define-constant-type float
    :hash-function    hash-immediate
    :compare-function similar-if-eql-p
    :dump-function    dump-float
    :tagging-macro    trun:%tag-double-float
    )

(define-constant-type ratio
    :hash-function    hash-immediate
    :compare-function similar-if-eql-p
    :dump-function    dump-ratio
    :tagging-macro    trun:%tag-ratio
    )

(define-constant-type bignum
    :hash-function    hash-immediate
    :compare-function similar-if-eql-p
    :dump-function    dump-bignum
    :tagging-macro    trun:%tag-bignum
    )

(define-constant-type foreign-type
    :hash-function    hash-foreign-type
    :compare-function similar-if-eql-p
    :dump-function    dump-foreign-type
    )

(define-constant-type c-array
    :hash-function    hash-c-array
    :compare-function similar-if-eql-p
    :dump-function    dump-c-array
    )


;;; Here is the main entry point for the constants processing pass.  It
;;; returns two values:
;;;
;;; (1) A list of initializers that must be delayed until constants in 
;;;     the "pending" list have been fully created.
;;;     Each initializer is a list whose CAR is a list of the constants in
;;;     the "pending" list that the initializer depends on, and whose CDR
;;;     is the list of arguments to be passed to #'merge-initcode.
;;; (2) A list of constants that are referenced in the initializers for 
;;;     the constants that are in the argument lists.  This is a list of
;;;     variable-records for those constants.
;;;
;;; When this function is called to process constants referenced directly 
;;; from an ordinary top-level form, the "pending" argument is empty so
;;; there should be no delayed initializations returned.
;;;
;;; *** It is probably OK to leave the dependencies as a list instead
;;; *** of using a hash table, since it only collects circular references
;;; *** (which are comparatively rare).

(defvar *processing-constants-p* nil)

(defun do-constant-processing (local-constants global-constants)
  (let ((*processing-constants-p* t))
    (dolist (c local-constants)
      (when (eq (target-form-type c) 'constant)
	(add-subobjects (second c))))
    (dolist (c global-constants)
      (when (eq (target-form-type c) 'constant)
	(add-subobjects (second c))))
    (multiple-value-bind (l-delayed-inits l-dependencies)
	(process-constants local-constants)
      (multiple-value-bind (g-delayed-inits g-dependencies)
	  (process-constants global-constants)
	(values (nconc l-delayed-inits g-delayed-inits)
		(nunion l-dependencies g-dependencies))))))


(defun add-object (object ctype)
  (let ((hash (compute-hash-value object 0 ctype)))
    (multiple-value-bind (refcount assoc)
	(find-constant object ctype hash)
      (if refcount
	  (when (integerp refcount)
	    (setf (cdr assoc) (1+ refcount)))
	  (add-constant object 1 ctype hash)))))

(defun add-subobjects (object)
  (typecase object
    (cons
     (when (eql 1 (add-object object *cons-constant-type*))
       (add-subobjects (car object))
       (add-subobjects (cdr object))))
    (string)
    (array
     (when (eql 1 (add-object object *array-constant-type*))
       (when (translator-typep object '(array t *))
	 (let ((dimensions (active-array-dimensions object)))
	   (if (and dimensions (null (cdr dimensions)))
	       (dotimes (i (car dimensions))
		 (declare (fixnum i))
		 (add-subobjects (aref object i)))
	       (add-subobjects-array1 object dimensions nil)))))))
  nil)

(defun add-subobjects-array1 (object dimensions indices)
  (if dimensions
      (let ((rest (cdr dimensions)))
	(dotimes (i (car dimensions))
	  (add-subobjects-array1 object rest (cons i indices))))
      (add-subobjects (apply #'aref object (reverse indices)))))


(defun process-constants (constants)
  (let ((all-delayed-inits nil)
	(all-dependencies  nil))
    (dolist (c constants)
      (multiple-value-bind (delayed-inits dependencies)
	  (if (eq (target-form-type c) 'constant)
	      (process-constant c)
	      (process-load-time-value c))
	(setq all-delayed-inits
	      (nconc delayed-inits all-delayed-inits))
	(setq all-dependencies
	      (nunion dependencies all-dependencies))))
    (values all-delayed-inits all-dependencies)))


;;; Check to see if this constant is similar to one we've already processed.

(defun process-constant (construct)
  (let* ((object  (second construct))
	 (type    (constant-object-type object))
	 (hash    (compute-hash-value object 0 type)))
    (multiple-value-bind (record assoc)
	(find-constant object type hash)
      (when (symbolp object)
	(let* ((package (symbol-package object))
	       (remote-package-name
		(find-remote-package-name package)))
	  (when remote-package-name
	    (let ((package-name (package-name package)))
	      (warn "Encountered symbol ~S in package ~A.~
		 ~%Use a package qualifier to place this symbol in ~
                   package ~A."
		    object package-name remote-package-name)))))
      (cond ((or (null record) (integerp record))
	     ;; This is a constant we haven't seen before.  We have to
	     ;; find and recursively translate, gather, and constant-process
	     ;; the forms to create and initialize the constants.
	     (multiple-value-bind
		   (record create-form init-form conditional-init-forms)
		 (dump-constant object type hash assoc)
	       (setf (third construct) record)
	       (process-constant-aux
		record create-form init-form conditional-init-forms)))
	    ((variable-record-pending-constant-p record)
	     ;; This is a circular reference to a constant whose creation
	     ;; is pending.  Just note the dependency.
	     (setf (third construct) record)
	     (values nil (list record)))
	    (t
	     ;; This is a reference to a constant that has already been
	     ;; created.  Nothing further needs to be done.
	     (setf (third construct) record)
	     (values nil nil))))))

;;; Here's the function that computes the type key for an object.
;;; I haven't used a declarative syntax for this because it is sensitive
;;; to the order in which the tests are made -- the most common cases
;;; ought to be tested first when possible.
;;;
;;; We can't use type-of here because we don't want exactly the same set
;;; of type specifiers back.
;;;
;;; This should be extended to deal with complex types.
;;; Hash-tables can be dumped only when the host Lisp implements the
;;; hash-table-test accessor.
;;; Pathnames and random-states probably can't be dumped due to 
;;; differences in representation between the host Lisp and the runtime.

(defun constant-object-type (object)
  (cond ((symbolp object)
	 (if (defined-as-symbol object *default-global-environment*)
	     (progn
	       (mark-quoted-symbol object)
	       *immediate-constant-type*)
	     *symbol-constant-type*))
	((immediate-constant-p object) 
	 *immediate-constant-type*)
	((c-array-p object)
	 *c-array-constant-type*)
	((initial-package-p object) 
	 *immediate-constant-type*)
	((stringp object)
	 *string-constant-type*)
	((packagep object)
	 *package-constant-type*)
	((consp object)
	 *cons-constant-type*)
	((arrayp object)	
	 *array-constant-type*)
	((floatp object)
	 *float-constant-type*)
	((trun:ratiop object) 
	 *ratio-constant-type*)
	((trun:bignump object)
	 *bignum-constant-type*)
	((translator-foreign-type-p object)
	 *foreign-type-constant-type*)
	(t
	(error "The constant ~s cannot be dumped." object)
	 )))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Hashing and "interning"
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defconstant hash-mask (let* ((size (integer-length most-positive-fixnum))
			      (mask (1- (ash 1 size))))
			 (if (>= most-positive-fixnum mask)
			     mask
			     (1- (ash 1 (1- size))))))

(defmacro combine-hash-values (value1 value2)
  `(logxor (the fixnum (ash (logand (the fixnum (ash hash-mask -1))
				    (the fixnum ,value1))
			    1))
	   (the fixnum ,value2)))


;;; Compute the hash value for the constant.  Objects that are similar
;;; as constants must have the same hash value.

(defun compute-hash-value (object &optional
				  (depth 0)
				  (type (constant-object-type object)))
  (funcall (hash-function type) object depth))



;;; For objects that don't have components that are recursively examined
;;; by similar-constants-p, the built-in SXHASH is OK.

(defun hash-immediate (object depth)
  (declare (ignore depth))
  (sxhash object))


;;; For conses, fiddle with the CAR and CDR.  Use the depth argument
;;; to avoid descending too deeply and maybe getting stuck in an 
;;; infinite loop if the structure is circular.  This hash function
;;; is not very good, but it does satisfy the constraint that conses
;;; that satisfy similar-constants-p have the same hash index, which
;;; SXHASH may not.

(defun hash-cons (object depth)
  (declare (fixnum depth))
  (if (> depth 5)
      0
      (let ((depth (1+ depth)))
	(declare (fixnum depth))
	(combine-hash-values
	 (compute-hash-value (car object) depth)
	 (compute-hash-value (cdr object) depth)))))


;;; For arrays, base the hash value on the array total size.  Again,
;;; this hash function is extremely crude but correct.

(defun hash-array (object depth)
  (declare (ignore depth))
  (combine-hash-values
   (array-rank object)
   (apply #'* (active-array-dimensions object))))


;;; The *constants-table* is a hash table of vectors.  The outer hash
;;; table is keyed on the type.  The inner vectors are do-it-yourself
;;; hash tables using the hash value computation function.  (We can't
;;; use built-in hash tables because we need a nonstandard predicate
;;; and hashing function.)
;;; For now these "hashvectors" are fixed size.

(defparameter *hashvector-size*  101)

(defmacro make-hashvector ()
  `(make-array *hashvector-size* :initial-element nil))

(defmacro hashvector-ref (vector hash)
  `(svref ,vector (mod ,hash *hashvector-size*)))

(defun hash-foreign-type (object depth)
  (declare (ignore depth))
  (compute-hash-value (translator-foreign-type-name object)))

(defun hash-c-array (object depth)
  (declare (ignore depth))
  (compute-hash-value (c-array-array object)))
;;; Find-constant returns the record for a previously "interned" constant,
;;; or NIL.

(defun find-constant (object &optional
			     (type (constant-object-type object))
			     (hash (compute-hash-value object 0 type)))
  (let* ((vector (constants-table type))
	 (assoc (when vector
		  (assoc object (hashvector-ref vector hash)
			 :test (compare-function type))))
	 (value (cdr assoc)))
    (values (if (consp value) (cdr value) value)
	    assoc)))


;;; Add-constant "interns" the record for the given object.  The record
;;; is returned.

(defun add-constant (object record
			    &optional
			    (type (constant-object-type object))
			    (hash (compute-hash-value object 0 type))
			    assoc)
  (if assoc
      (setf (cdr assoc) record)
      (let ((vector (constants-table type)))
	(when (null vector)
	  (setf (constants-table type)
		(setq vector (make-hashvector))))
	(push (cons object record) (hashvector-ref vector hash))
	record)))





;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Similarity as constants
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; Similar-constants-p is the equality predicate used to determine
;;; whether two constants can be "coalesced" into a single object.
;;;
;;; This predicate is slighly pessimistic in that sometimes it will return
;;; NIL even when the constants are actually similar, but when the similarity
;;; is hard to detect.
;;;
;;; Check for EQL-ness first, which takes care of numbers, symbols, and 
;;; characters and will also detect EQ objects of other types.  We only bother
;;; to do similarity checking on a limited number of other structured
;;; data types.
;;;
;;; This will terminate given circular constants, but it will generally
;;; just give up and return NIL when circularities are found instead of
;;; trying to be clever.
;;;
;;; *** Should use some kind of hashing scheme instead of lists for
;;; *** the stacks that keep track of the recursion.

(defun similar-constants-p (object1 object2 &optional stack1 stack2)
  (cond ((eql object1 object2)
	 t)
	((or (member object1 stack1 :test #'eq)
	     (member object2 stack2 :test #'eq))
	 nil)
	(t
	 (let ((type1  (constant-object-type object1))
	       (type2  (constant-object-type object2)))
	   (if (eq type1 type2)
	       (funcall (compare-function type1)
			object1 object2 stack1 stack2)
	       nil)))))


;;; Lots of kinds of objects are treated as similar if and only if they are
;;; EQL.

(defun similar-if-eql-p (object1 object2 &optional stack1 stack2)
  (declare (ignore stack1 stack2))
  (eql object1 object2))


;;; Strings are similar if and only if they are string=.

(defun similar-strings-p (object1 object2 &optional stack1 stack2)
  (declare (ignore stack1 stack2))
  (string= object1 object2))


;;; Conses get their own comparison predicate that keeps track of potential
;;; circularities.

(defun similar-conses-p (object1 object2 &optional stack1 stack2)
  (push object1 stack1)
  (push object2 stack2)
  (and (similar-constants-p (car object1) (car object2) stack1 stack2)
       (similar-constants-p (cdr object1) (cdr object2) stack1 stack2)))


;;; Arrays also get their own comparison predicate.

(defun similar-arrays-p (object1 object2 &optional stack1 stack2)
  (let ((dimensions  nil))
    (and (eq (upgrade-element-type (array-element-type object1))
	     (upgrade-element-type (array-element-type object2)))
	 (equal (setq dimensions (active-array-dimensions object1))
		(active-array-dimensions object2))
	 (case (length dimensions)
	   (1 (dotimes (i (car dimensions) t)
		(unless (similar-constants-p (aref object1 i)
					     (aref object2 i))
		  (return-from similar-arrays-p nil))))
	   (2 (dotimes (i (car dimensions) t)
		(dotimes (j (cadr dimensions))
		  (unless (similar-constants-p (aref object1 i j)
					       (aref object2 i j))
		    (return-from similar-arrays-p nil)))))
	   (t (array-elements-similar
	       object1 object2
	       (cons object1 stack1) (cons object2 stack2)
	       dimensions nil))))))


;;; This function could be rewritten in terms of row-major-aref.
;;; If this is done, it should be conditionalized for #-Genera,
;;; which doesn't have the row-major-aref function.

(defun array-elements-similar (object1 object2 stack1 stack2
				       dimensions indices)
  (if dimensions
      (let ((dimensions-rest (cdr dimensions)))
	(dotimes (i (car dimensions) t)
	  (unless (array-elements-similar object1 object2 stack1 stack2
					  dimensions-rest (cons i indices))
	    (return nil))))
      (progn
	(setq indices (reverse indices))
	(similar-constants-p
	 (apply #'aref object1 indices)
	 (apply #'aref object2 indices)
	 stack1
	 stack2))))
				

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Dumping of constants
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Dump-constant creates a new record for the constant, "interns" it
;;; in the *constants-table*, and returns the information needed to 
;;; create and initialize the object at load time. We know that there 
;;; is not already a similar constant "interned" in the *constants-table* 
;;; when this function is called.

;;; Four values are returned:
;;;     a variable-record to hold the value of the constant
;;;     a create-form
;;;     an init-form
;;;     a list of conditional-init forms

(defun dump-constant (object &optional
			     (type (constant-object-type object))
			     (hash (compute-hash-value object 0 type))
			     assoc)
  (funcall (dump-function type) object type hash assoc))


;;; Immediate constants are treated specially by the code walker.  If we've
;;; got one here, unless it's a component of a static constant,
;;; it's some kind of an internal error.

(defun dump-immediate (object type hash assoc)
  (declare (ignore object type hash assoc))
  (error "Internal error -- trying to dump immediate constant incorrectly."))


;;; Tagged strings are built from untagged C strings.
(define-translator-parameter *maximum-c-string-constant-length* nil)

(defun dump-string (object type hash assoc)
  (maybe-complain-about-non-simple-array object)
  (let ((record 
	 (add-constant
	  object
	  (make-variable-record :name (make-constant-label 'string)
				:nonrelocatable-type t)
	  type
	  hash
	  assoc)))
    (values record
	    (if (and *maximum-c-string-constant-length*
		     (< *maximum-c-string-constant-length*
			(length object)))
		`(tx:string-append
		  ,@(let* ((forms nil)
			   (length (length object))
			   (start 0)
			   (incr *maximum-c-string-constant-length*)
			   (end incr))
		      (loop (when (<= length start)
			      (return (nreverse forms)))
			    (push `',(make-c-string :string 
						    (subseq object start end))
				  forms)
			    (setq start end)
			    (setq end (min length (+ start incr))))))
		`',(make-c-string :string object))
	    nil
	    nil)))


;;; Note that symbol names are allocated on a global basis, so fill in
;;; unique-name slot on the variable-record to bypass the name mapper
;;; during the emit phase.

(defun dump-symbol (object type hash assoc)
  (let* ((name (c-name-of-quoted-symbol object))
	 (record (add-constant
		  object
		  (make-variable-record :name name
					:unique-name name
					:nonrelocatable-type t)
		  type
		  hash
		  assoc))
	 (new-symbol-p
	  (multiple-value-bind (record therep)
	      (defined-as-quoted-symbol object)
	    (not (and therep
		      (symbol-record-exists-at-runtime record)))))
	 (symbol-record (mark-runtime-symbol object))
	 (function-linking-code
	  (when (symbol-record-function-requires-linking symbol-record)
	    `((trun:link-function ,object))))
	 (setf-function-linking-code
	  (when (symbol-record-setf-function-requires-linking symbol-record)
	    `((trun:link-setf-function ,(cons 'setf object) ,object))))
	 (variable-linking-code
	  (when (and (symbol-record-variable-exists symbol-record)
		     new-symbol-p)
	    ;; This will translate into a variable-definition;
	    ;; This is OK, since only the first variable-definition
	    ;; will be emitted by emit-variables, but subsequent ones
	    ;; can still cause set-symbol-value-location to be generated
	    ;; by process-variable-links.
	    `((trun:link-variable ,object)))))
    (values record
	    `(trun:%static-symbol
	      ',(make-c-string :string (symbol-name object))
	      ',(symbol-package object))
	    (when (or function-linking-code
		      setf-function-linking-code
		      variable-linking-code)
	      `(progn
		 ,@function-linking-code
		 ,@setf-function-linking-code
		 ,@variable-linking-code))
	    nil)))

(defun mark-runtime-symbol (symbol)
  (multiple-value-bind (record therep)
      (defined-as-quoted-symbol symbol)
    (if therep
	(progn
	  (setf (symbol-record-exists-at-runtime record) t)
	  record)
	(setf (defined-as-quoted-symbol symbol)
	      (make-symbol-record :name symbol :exists-at-runtime t)))))

	   

;;; Packages are reconstructed with a lookup routine, essentially 
;;; find-package except that it should signal an error if the package
;;; is not found.

(defun dump-package (object type hash assoc)
  (let* ((name (sformat "~a_package" (package-name object)))
	 (record (add-constant
		  object
		  (make-variable-record :name name
					:nonrelocatable-type t)
		  type
		  hash
		  assoc)))
    (values record
	    `(trun:%static-package
	      ',(make-c-string :string (package-name object)))
	    nil
	    nil)))
	   



;;; Try to build lists bottom-up instead of top-down.
;;; Return conditional initializers to take care of the situations where
;;; either the CAR or CDR is a circular reference to some enclosing object.
;;; In that case, the value of the field of the cons will initially be 
;;; undefined and initialization code to patch up the reference will be
;;; executed once the circularly referenced object has been created.

(defun quote-object (object)
  `',object)

(defun collect-list-updates (object length)
  (let ((updates nil))
    (dotimes (position length)
      (let ((e (pop object)))
	(unless (eql 1 (find-constant e))
	  (push (cons e `(setf (nth ,position ',object) ',e)) updates))))
    (nreverse updates)))

(defun dump-cons (object type hash assoc)
  (let ((record (add-constant
		 object
		 (make-variable-record :name (make-constant-label 'list)
				       :nonrelocatable-type t)
		 type
		 hash
		 assoc))
	(quoted-list-elements (list `',(car object)))
	(length-so-far 1)
	(tail (cdr object)))
    (declare (fixnum length-so-far))
    (loop (unless (and (consp tail)
		       (eql 1 (find-constant tail type))
		       (< length-so-far 31))
	    (return-from dump-cons
	      (cond ((= length-so-far 1)
		     (values
		      record
		      `(trun:%static-cons ,(car quoted-list-elements)
					  ',(cdr object))
		      nil
		      (list (cons (car object)
				  `(setf (car ',object) ',(car object)))
			    (cons (cdr object)
				  `(setf (cdr ',object) ',(cdr object))))))
		    ((null tail)
		     (values
		      record
		      `(trun:%static-list ,length-so-far
					  ,@(nreverse quoted-list-elements))
		      nil
		      (collect-list-updates object length-so-far)))
		    (t
		     (values
		      record
		      `(trun:%static-list-star ,(1+ length-so-far)
					       ,@(nreverse 
						  quoted-list-elements)
					       ,(quote-object tail))
		      nil
		      (nconc 
		       (collect-list-updates object length-so-far)
		       (when (eql 1 (find-constant tail))
			 (list 
			  (cons tail
				`(setf (cdr (nthcdr ,(1- length-so-far)
						    ',object))
				       ',tail))))))))))
	  (push `',(car tail) quoted-list-elements)
	  (incf length-so-far)
	  (setq tail (cdr tail)))))

;;; *** The array initialization code is not in sync with the element-types
;;; *** supported by the Run-Time Library.

(defun dump-array (object type hash assoc)
  (maybe-complain-about-non-simple-array object)
  (let* ((element-type (translator-upgraded-array-element-type
			(array-element-type object)))
	 (default (case element-type
		    ((single-float double-float)
		     0.0)
		    ((t)
		     nil)
		    (t
		     0)))
	 (dimensions (active-array-dimensions object))
	 (record
	  (add-constant
	   object
	   (make-variable-record :name (make-constant-label 'array)
				 :nonrelocatable-type t)
	   type
	   hash
	   assoc)))
    (values
     record
     `(trun:%static-array ',element-type ,(length dimensions) ,@dimensions)
     (if (eq element-type 't)
	 `(progn ,@(make-array-inits dimensions object nil default))
	 `(progn ,@(make-array-inits dimensions object nil default))
	 #||
	 `(tx:memcpy (tx:array-contents-pointer ',object)
		     (tx:address-of ',(make-c-array :array object
						    :element-type element-type
						    :dimensions dimensions))
		     size)
	 ||#)
     nil)))


;;; See also upgraded-array-element-type in type.lisp....
;;; The "default" return value is what the low-level initializer fills
;;; up the array with.  Here we use it to avoid emitting initializers
;;; for fields that are EQL to this value.

;;; Returns 4 values:
;;;  upgraded element type
;;;  code constructor
;;;    This is the run-time function used to build an array of the
;;;    desired element-type.
;;;  default initial value

(defun upgrade-element-type (type)
  (cond ((and (not (eq type 't))
	      (translator-subtypep type 'bit))
	 (values 'bit
		 'trun:%static-bit-array
		 0))
	((and (not (eq type 't))
	      (translator-subtypep type 'character))
	 (values 'character
		 'trun:%static-char-array
		 0))
	(t
	 (values t
		 'trun:%static-general-array
		 nil))))

;;; Why isn't there a displaced-array-p predicate?  We ought to complain
;;; about that too.

(defun maybe-complain-about-non-simple-array (object)
  (when (and #+genera
	      (or (not (stringp object)) ; too many messages otherwise.
		  (array-has-fill-pointer-p object))
	     (adjustable-array-p object))
    (warn "Constant array ~s will not be adjustable." object))
  (when (array-has-fill-pointer-p object)
    (warn "Constant array ~s will not have a fill pointer." object)))


;;; These two functions could be rewritten in terms of row-major-aref.
;;; If this is done, it should be conditionalized for #-Genera,
;;; which doesn't have the row-major-aref function.


(defun make-array-inits (dimensions object indices default)
  (if dimensions
      (let ((results  nil))
	(dotimes (i (car dimensions))
	  (setq results
		(nconc results
		       (make-array-inits (cdr dimensions) object
					 (cons i indices) default))))
	results)
      (let ((value  (apply #'aref object (setq indices (reverse indices)))))
	(if (eql value default)
	    nil
	    `((setf (aref ',object ,@indices) ',value))))))



;;; Floats are treated in a similar way as strings.

(defun dump-float (object type hash assoc)
  (let ((record
	 (add-constant
	  object
	  (make-variable-record :name (make-constant-label 'float)
				:nonrelocatable-type t)
	  type
	  hash
	  assoc)))
    (values
     record
     `',(make-c-float :float object)
     nil
     nil)))



;;; Dump ratios

(defun dump-ratio (object type hash assoc)
  (let ((record
	 (add-constant
	  object
	  (make-variable-record :name (make-constant-label 'ratio)
				:nonrelocatable-type t)
	  type
	  hash
	  assoc)))
    (values
     record
     `(trun:%static-ratio ,(numerator object) ,(denominator object))
     nil
     nil)))

	 

;;; Dump bignums

(defun dump-bignum (object type hash assoc)
  (multiple-value-bind (bignum-digits bignum-length bignum-sign)
      (split-bignum object t)
    (let ((record
	   (add-constant
	    object
	    (make-variable-record :name (make-constant-label 'bignum)
				  :nonrelocatable-type t)
	    type
	    hash
	    assoc)))
      (values
       record
       (if (eq bignum-sign :positive)
	   `(trun:%static-positive-bignum ,bignum-length)
	   `(trun:%static-negative-bignum ,bignum-length))
       `(progn
	  ,@(make-bignum-inits object bignum-digits))
       nil))))


;;; Split bignum into 15- or 30-bit digits
;;; Return three values :
;;;  1. A list of 15- or 30-bit bignum digits.
;;;  2. The number of 30-bit bignum digits.
;;;  3. The sign of the bignum.

(defun split-bignum (bignum 15-p)
  (do ((bignum-digits '())
       (bignum-length 0)
       (bignum-sign   (if (minusp bignum)
			  (progn
			    (setf bignum (- bignum))
			    :negative)
			:positive)))
      ((zerop bignum)
       (values (nreverse bignum-digits)
	       bignum-length
	       bignum-sign))
    (cond
     (15-p
      (push (logand #x7FFF bignum) bignum-digits)
      (push (logand #x7FFF (setf bignum (ash bignum -15))) bignum-digits)
      (setq bignum (ash bignum -15)))
     (t
      (push (logand #x3FFFFFFF bignum) bignum-digits)
      (setq bignum (ash bignum -30))))
    (incf bignum-length)))

(defun make-bignum-inits (object bignum-digits)
  (do ((rest-of-bignum-digits bignum-digits (cddr rest-of-bignum-digits))
       (counter 0 (1+ counter))
       (bignum-inits '()))
      ((null rest-of-bignum-digits)
       (nreverse bignum-inits))
      (push `(trun:%set-bignum-digit ,object ,counter
				     ,(second rest-of-bignum-digits)
				     ,(first rest-of-bignum-digits))
	    bignum-inits)))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Load-time-value support
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; LOAD-TIME-VALUE forms are treated like constants, with the 
;;; value-producing subform being the create form and no init form.
;;; All we have to do here is allocate a variable-record.  Since the
;;; value-producing subform doesn't necessarily return a constant,
;;; the variable-record has to be gc-protected.

(defun dump-load-time-value (form)
  (values (make-variable-record :name (make-constant-label 'load-time-value)
				:needs-gc-protection t)
	  form))

(defun dump-foreign-type (object type hash assoc)
  (let* ((ft-name (translator-foreign-type-name object))
	 (name (if (symbolp ft-name)
		   (sformat "~a_foreign_type" ft-name)
		   'foreign-type-constant))
	 (record (add-constant
		  object
		  (make-variable-record :name name)
		  type
		  hash
		  assoc)))
    (values record
	    (dump-foreign-type-form object ft-name)
	    nil
	    nil)))

(defparameter *primitive-foreign-type-name-list*
  '(:character 
    :signed-8bit :unsigned-8bit
    :signed-16bit :unsigned-16bit 
    :signed-32bit :unsigned-32bit
    :signed-64bit 
    :unsigned-64bit
    :single-float :double-float))

(defun dump-foreign-type-form (object ft-name)
  (or (when (consp ft-name)
	(case (car ft-name)
	  ((:const :volatile)
	   (dump-foreign-type-form object (cadr ft-name)))
	  (:pointer
	   (when (and (consp (cadr ft-name))
		      (eq ':function (caadr ft-name)))
	     (setq ft-name '(:pointer :unsigned-32bit)))
	   `(tx:foreign-type (list ',(car ft-name)
				   ',(translator-foreign-type
				      (cadr ft-name)))))
	  (:array
	   `(tx:foreign-type (list* ',(car ft-name)
				    ',(translator-foreign-type
				       (cadr ft-name))
				    ',(cddr ft-name))))))
      (when (defined-as-foreign-structure ft-name)
	`(tx:make-struct-foreign-type
	  ',ft-name
	  (translator-foreign-size-of ',object)
	  ,(translator-foreign-type-modulus object)
	  ,(translator-foreign-type-remainder object)))
      (when (memq ft-name *primitive-foreign-type-name-list*)
	`(tx:foreign-type ',ft-name))
      (error "~S is not the name of a runtime foreign type"
	     ft-name)))

(defparameter *foreign-element-type-alist*
  '((t . :object)
    (bit . :unsigned-16bit)
    (character . :character)
    ((unsigned-byte 8) . :unsigned-8bit)
    ((signed-byte 8) . :signed-8bit)
    ((unsigned-byte 16) . :unsigned-16bit)
    ((signed-byte 16) . :signed-16bit)
    ((unsigned-byte 32) . :unsigned-32bit)
    ((signed-byte 32) . :signed-32bit)
    ((unsigned-byte 64) . :unsigned-64bit)
    ((signed-byte 64) . :signed-64bit)    
    (single-float . :single-float)
    (double-float . :double-float)))

(defun dump-c-array (object type hash assoc)
  (let* ((array (c-array-array object))
	 (foreign-element-type (cdr (assoc (c-array-element-type object)
					   *foreign-element-type-alist*
					   :test #'equal)))
	 (dimensions (c-array-dimensions object))
	 (record
	  (add-constant
	   object
	   (make-variable-record 
	    :name (make-constant-label 'array)
	    :nonrelocatable-type t
	    :foreign-type `(:array ,foreign-element-type ,dimensions)
	    :initializer array)
	   type
	   hash
	   assoc)))
    (values record
	    nil
	    nil
	    nil)))
