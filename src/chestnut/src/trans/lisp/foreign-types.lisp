;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; foreign-types.lisp
;;;
;;; Copyright (c) 1993, Chestnut Software Inc.
;;;
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/foreign-types.lisp,v $"
 "$Revision: 1.11 $"
 "$Date: 2007/07/10 16:57:57 $")

;;; Support for foreign datatypes

;;; The C type is a string, to be used in variable declarations.

(eval-when (:compile-toplevel :load-toplevel :execute)

(define-hashed-structure (translator-foreign-type
			  (:constructor make-translator-foreign-type-internal))
  boxer
  unboxer
  (lisp-type t)
  (c-type :none))

(defun make-translator-foreign-type (&rest args &key %name &allow-other-keys)
  (if (consp %name)
      (ecase (car %name)
	((:pointer)
	 (make-translator-foreign-type-internal
	  :%name %name
	  :boxer :make-foreign-pointer
	  :unboxer :foreign-pointer-address
	  :lisp-type 'tx:foreign-pointer
	  :c-type (abstract-c-type-for-foreign-type %name)))
	((:array :function :structure :union)
	 (make-translator-foreign-type-internal
	  :%name %name
	  :boxer :unspecified 
	  :unboxer :unspecified
	  :lisp-type nil
	  :c-type (abstract-c-type-for-foreign-type %name))))
      (apply #'make-translator-foreign-type-internal args)))

) ; eval-when

(defmacro define-translator-foreign-synonym-type (item-name syn-name)
  (let ((var-name (intern (format nil "*~a-~a*" item-name 'foreign-type))))
    `(progn
       (defparameter ,var-name (translator-foreign-type ',syn-name))
       (setf (gethash ',item-name *translator-foreign-type-table*)
	     ,var-name))))

(defmacro foreign-type->lisp-type (foreign-type)
  `(lisp-type ,foreign-type))

(defmacro get-foreign-types ()
  `(let ((foreign-types nil))
     (maphash #'(lambda (foreign-type-name foreign-type)
		  (declare (ignore foreign-type))
		  (push foreign-type-name foreign-types))
	      *translator-foreign-type-table*)
     foreign-types))

(eval-when (compile load eval)

(define-translator-foreign-type :object
  :lisp-type t
  :boxer     :unnecessary
  :unboxer   :unnecessary
  :c-type    "Object")

(define-translator-foreign-synonym-type :lisp :object)

(defparameter *value-context* *object-translator-foreign-type*)

(define-translator-foreign-type :boolean
  :lisp-type t
  :boxer     :nonstandard
  :unboxer   trun:%truep
  :c-type    "char")

(defparameter *predicate-context* *boolean-translator-foreign-type*)

(define-translator-foreign-type :int
  :lisp-type (signed-byte 32)
  :boxer     trun:%long-to-integer ; trun:%fix
  :unboxer   trun:%integer-to-long ; trun:%ifix
  :c-type    "int")

(define-translator-foreign-type :unsigned-int
  :lisp-type (signed-byte 32)
  :boxer     trun:%unsigned-long-to-integer ; trun:%fix
  :unboxer   trun:%integer-to-unsigned-long ; trun:%ifix
  :c-type    "unsigned int")

;; NOTE: now the foreign type "long" and "unsigned-long" should always be
;; the same size as pointers. The reason we use "SI_long" instead of "long"
;; is that, on 64-bit Windows and Linux, the size of "long" is different,
;; but we want them to be always 64-bit.  -- Chun Tian (binghe), Dec 2015

(define-translator-foreign-type :long
  :lisp-type fixnum ; (signed-byte #+x86-64 64 #-x86-64 32)
  :boxer     trun:%long-to-integer ; trun:%fix
  :unboxer   trun:%integer-to-long ; trun:%ifix
  :c-type    "SI_Long") ; was "long"

(define-translator-foreign-type :unsigned-long
  :lisp-type (unsigned-byte #+x86-64 64 #-x86-64 32)
  :boxer     trun:%unsigned-long-to-integer ; trun:%fix
  :unboxer   trun:%integer-to-unsigned-long ; trun:%ifix
  :c-type    "SI_Ulong")

(define-translator-foreign-type :signed-64bit
  :lisp-type (signed-byte 64)
  :boxer     trun:%int64-to-integer
  :unboxer   trun:%integer-to-int64
  :c-type    "SI_int64")

(define-translator-foreign-type :unsigned-64bit
  :lisp-type (unsigned-byte 64)
  :boxer     trun:%unsigned-int64-to-integer
  :unboxer   trun:%integer-to-unsigned-int64
  :c-type    "SI_uint64")

(define-translator-foreign-type :signed-32bit
  :lisp-type (signed-byte 32)
  :boxer     trun:%int-to-integer
  :unboxer   trun:%integer-to-int
  :c-type    "int")

(define-translator-foreign-type :unsigned-32bit
  :lisp-type (unsigned-byte 32)
  :boxer     trun:%unsigned-int-to-integer
  :unboxer   trun:%integer-to-unsigned-int
  :c-type    "unsigned int")

(define-translator-foreign-type :signed-16bit
  :lisp-type (signed-byte 16)
  :boxer     trun:%short-to-integer
  :unboxer   trun:%integer-to-short
  :c-type    "short")

(define-translator-foreign-type :unsigned-16bit
  :lisp-type (unsigned-byte 16)
  :boxer     trun:%unsigned-short-to-integer
  :unboxer   trun:%integer-to-unsigned-short
  :c-type    "unsigned short")

(define-translator-foreign-type :signed-8bit
  :lisp-type (signed-byte 8)
  :boxer     trun:%char-to-integer
  :unboxer   trun:%integer-to-char
  :c-type    "char")

(define-translator-foreign-type :unsigned-8bit
  :lisp-type (unsigned-byte 8)
  :boxer     trun:%unsigned-char-to-integer
  :unboxer   trun:%integer-to-unsigned-char
  :c-type    "unsigned char")

;;; The boxers for the :fixnum types have all been changed to
;;; trun:%fix, for now, because they are all equivalent,
;;; and trun:%fix is easier to read.
(define-translator-foreign-type :fixnum
  :lisp-type fixnum
  :boxer     trun:%fix ; was trun:%long-to-fixnum
  :unboxer   trun:%ifix ; was trun:%fixnum-to-long
  :c-type    "SI_Long")

(define-translator-foreign-type :fixnum-long
  :lisp-type fixnum
  :boxer     trun:%long-to-fixnum
  :unboxer   trun:%fixnum-to-long
  :c-type    "SI_Long")

(define-translator-foreign-type :fixnum-int
  :lisp-type fixnum
  :boxer     trun:%int-to-fixnum
  :unboxer   trun:%fixnum-to-int
  :c-type    "int")

(define-translator-foreign-type :fixnum-short
  :lisp-type fixnum
  :boxer     trun:%short-to-fixnum
  :unboxer   trun:%fixnum-to-short
  :c-type    "short")
  
(define-translator-foreign-type :fixnum-char
  :lisp-type fixnum
  :boxer     trun:%char-to-fixnum
  :unboxer   trun:%fixnum-to-char
  :c-type    "char")

(define-translator-foreign-type :float
  :lisp-type double-float
  :boxer     trun:%cdouble-to-double
  :unboxer   trun:%unbox-float
  :c-type    "float")

(define-translator-foreign-type :static-float
  :lisp-type double-float
  :boxer     trun:%static-float
  :unboxer   trun:%unbox-float
  :c-type    "float")

(define-translator-foreign-type :double-float
  :lisp-type double-float
  :boxer     trun:box%d
  :unboxer   trun:unbox%d
  :c-type    "double")

(define-translator-foreign-type :single-float
  :lisp-type single-float
  :boxer     trun:%float-to-single-float
  :unboxer   trun:%single-float-to-float
  :c-type    "float")

(define-translator-foreign-type :short-float
  :lisp-type short-float
  :boxer     trun:%float-to-short-float
  :unboxer   trun:%short-float-to-float
  :c-type    "float")

(define-translator-foreign-type :string
  :lisp-type string
  :boxer     trun:%istring-to-string
  :unboxer   trun:%istring
  :c-type    "char *")

(define-translator-foreign-type :static-string
  :lisp-type string
  :boxer     trun:%static-string
  :unboxer   trun:%istring
  :c-type    "char *")

(define-translator-foreign-type :char
  :lisp-type character
  :boxer     trun:%chr
  :unboxer   trun:%unbox-char
  :c-type    "char")

(define-translator-foreign-type :void
  :lisp-type nil
  :boxer     :unnecessary
  :unboxer   :unnecessary
  :c-type    "void")

(define-translator-foreign-type :null
  :lisp-type nil
  :boxer     trun:%void-to-null
  :unboxer   :unspecified
  :c-type    "void")

(defparameter *ignore-context* *void-translator-foreign-type*)

(define-translator-foreign-type :character
  :lisp-type character
  :boxer     trun:%char-to-character
  :unboxer   trun:%character-to-char
  :c-type    "char")

(define-translator-foreign-type :simple-string
  :lisp-type simple-string
  :boxer     trun:%istring-to-simple-string
  :unboxer   trun:%simple-string-to-char-pointer
  :c-type    "char *")

(define-translator-foreign-type :8-bit-signed-array
  :lisp-type (array (signed-byte 8) *)
  :boxer   :unspecified
  :unboxer trun:%byte-8-sarray-to-char-pointer
  :c-type  "char *")

(define-translator-foreign-type :16-bit-signed-array
  :lisp-type (array (signed-byte 16) *)
  :boxer   :unspecified
  :unboxer trun:%byte-16-sarray-to-short-pointer
  :c-type  "short *")

(define-translator-foreign-type :32-bit-signed-array
  :lisp-type (array (signed-byte 32) *)
  :boxer   :unspecified
  :unboxer trun:%byte-32-sarray-to-int-pointer
  :c-type  "int *")

(define-translator-foreign-type :64-bit-signed-array
  :lisp-type (array (signed-byte 64) *)
  :boxer   :unspecified
  :unboxer trun:%byte-64-sarray-to-int64-pointer
  :c-type  "SI_int64 *")

(define-translator-foreign-type :8-bit-unsigned-array
  :lisp-type (array (unsigned-byte 8) *)
  :boxer   :unspecified
  :unboxer trun:%ubyte-8-sarray-to-uchar-ptr
  :c-type  "unsigned char *")

(define-translator-foreign-type :16-bit-unsigned-array
  :lisp-type (array (unsigned-byte 16) *)
  :boxer   :unspecified
  :unboxer trun:%ubyte-16-sarray-to-ushort-ptr
  :c-type  "unsigned short *")

(define-translator-foreign-type :32-bit-unsigned-array
  :lisp-type (array (unsigned-byte 32) *)
  :boxer   :unspecified
  :unboxer trun:%ubyte-32-sarray-to-uint-ptr
  :c-type  "unsigned long *")

(define-translator-foreign-type :64-bit-unsigned-array
  :lisp-type (array (unsigned-byte 64) *)
  :boxer   :unspecified
  :unboxer trun:%ubyte-64-sarray-to-uint64-ptr
  :c-type  "SI_uint64 *")

(define-translator-foreign-type :single-float-array
  :lisp-type (array single-float *)
  :boxer   :unspecified
  :unboxer trun:%sfloat-sarray-to-float-pointer
  :c-type  "float *")

(define-translator-foreign-type :double-float-array
  :lisp-type (array double-float *)
  :boxer   :unspecified
  :unboxer trun:%dfloat-sarray-to-double-pointer
  :c-type  "double *")

(define-translator-foreign-type :simple-c-type
  :lisp-type (or (signed-byte 32) string character float)
  :boxer   :unspecified
  :unboxer :unspecified
  :c-type  "char *")
  
)

;;; Any subtype of a type in this list is 
;;; a type specifier which includes all the things that don't get moved by the
;;; garbage collector.  This includes types which have an immediate
;;; representation and types which are always statically allocated.
(eval-when (compile load eval)
(defparameter *nonrelocating-types*
  '(or ;; These have immediate representations.
       fixnum character
       ;; Currently statically allocated.  This might change.
       package 
       ;; Statically allocated.  If class wrappers were allocated in the
       ;; dynamic heap and needed gc protection, then the various slot access
       ;; functions that took wrappers as arguments would be less effective.
       #+translator-supports-clos trun:class-wrapper
       ))

(defvar *relocating-type-alist* nil)

(defun relocating-type-p (type)
  (or (eq type t)
      (if (and (consp type)
	       (eq (car type) 'member))
	  (dolist (value (cdr type) t)
	    (unless (relocating-type-p (translator-type-of value))
	      (return nil)))
	  (let ((a (if (symbolp type)
		       (assoc type *relocating-type-alist* :test #'eq)
		       (assoc type *relocating-type-alist* :test #'equal))))
	    (unless a
	      (setq a (cons type (not (translator-subtypep
				       type *nonrelocating-types*))))
	      (push a *relocating-type-alist*))
	    (cdr a)))))
)

(eval-when (compile load eval)
(defmacro lisp-type->foreign-type-value (foreign-type-name object-p)
  (if object-p
      `(values (translator-foreign-type ,foreign-type-name)
	       ',(not (relocating-type-p
		       (lisp-type foreign-type-name))))
      `(translator-foreign-type ,foreign-type-name)))

(defmacro lisp-type->foreign-type-cond (type &rest names)
  (let ((object-p (eq (car (last names)) ':object)))
    `(cond ,@(when object-p
	       `(((eq type 't)
		  (lisp-type->foreign-type-value :object ,object-p))))
	   ,@(when (memq ':double-float names)
	       `(((tutil::single-float-type-specifier-p type nil)
		  (lisp-type->foreign-type-value :single-float ,object-p))))
	   ,@(mapcar #'(lambda (foreign-type-name)
			 `((translator-subtypep
			    ,type
			    ',(lisp-type foreign-type-name))
			   (lisp-type->foreign-type-value
			    ,foreign-type-name ,object-p)))
		     names))))
)

(defun lisp-type->foreign-type (type)
  (lisp-type->foreign-type-cond type
   :fixnum
   :signed-32bit
   :unsigned-32bit
   :signed-64bit
   :unsigned-64bit
   :double-float
   :character
   ;; :string
   :object))

;;; Coerce a tagged object to an untagged object of the given C type.

(defun coerce-to-c-type (from to statements expression temps)
  (case (unboxer to)
    (:unnecessary 
     (values statements expression temps))
    (:foreign-pointer-address
     (values 
      statements
      (make-target-form 'cast
			to
			(make-target-form 'macro-call
					  'tx:%foreign-pointer-address
					  expression))
      temps))
    (:unspecified 
     (error "A boxed value can't be coerced to ~S." 
	    (if (symbolp to)
		to
		(translator-foreign-type-name to))))
    (t 
     (box-unbox-aux 'unbox-value 'box-value from to 
		    statements expression temps))))

;;; Coerce an untagged object of the given C type to a tagged object.

(defun coerce-from-c-type (from to statements expression temps)
  (case (boxer from)
    (:unnecessary 
     (values statements expression temps))
    (:make-foreign-pointer
     (values 
      statements
      (make-target-form 
       'macro-call
       'tx:make-foreign-pointer-internal
       (make-target-form 'cast
			 (translator-foreign-type ':unsigned-long) ; was unsigned-32bit
			 expression)
       (make-target-form 'constant
			 (translator-foreign-type from)
			 nil))
      temps))
    (:unspecified 
     (error "A boxed value can't be coerced from ~S."
	    from))
    (t 
     (box-unbox-aux 'box-value 'unbox-value from to
		    statements expression temps))))

(defun foreign-type-coerce (statements expression &optional from to
				       expression-lisp-type
				       temps)
  (foreign-type-coerce-internal
   statements expression
   (or from (context-foreign-type *context*))
   (or to (context-foreign-type *context*))
   expression-lisp-type
   temps))

(defparameter type-coercion-operators
  '(("float"
     ("double" trun:%float-to-double))
    ("double"
     ("float" trun:%double-to-float))))

(defun c-integer-foreign-type-p (foreign-type)
  (let ((name (lisp-type foreign-type)))
    (or (eq name 'character)
	(eq name 'fixnum)
	(and (consp name)
	     (or (eq (car name) 'signed-byte)
		 (eq (car name) 'unsigned-byte))))))

(defun c-float-foreign-type-p (foreign-type)
  (memq (lisp-type foreign-type)
	'(double-float single-float short-float float)))

(defun foreign-type-string-p (ftype)
  (let ((name (translator-foreign-type-name ftype)))
    (if (atom name)
	(or (eq name ':string) (eq name ':simple-string))
	(case (car name)
	  (:pointer (eq (cadr name) ':char))
	  (:array (and (eq (cadr name) ':char)
		       (= 1 (length (caddr name)))))
	  (t nil)))))

(defun foreign-type-coerce-internal (statements expression from to
						expression-lisp-type
						temps)
  (cond ((eq to (translator-foreign-type :void))
	 (when expression
	   (let ((expression (discard-box-unbox expression)))
	     (when (state-changing-expression-p expression)
	       (push expression statements)))
	   (values statements nil temps)))
	((and (eq from (translator-foreign-type :object))
	      (eq to (translator-foreign-type :simple-c-type)))
	 (let ((to (when expression-lisp-type
		     (dolist (type (cdr (lisp-type to)) nil)
		       (when (translator-subtypep expression-lisp-type type)
			 (return (lisp-type->foreign-type type)))))))
	   (if (null to)
	       (values statements expression temps)
	       (foreign-type-coerce statements expression from to nil temps))))
	((or (eq from to)
	     (and (not (eq from (translator-foreign-type :object)))
		  (eq to (translator-foreign-type :simple-c-type)))
	     (let ((c-from (c-type from))
		   (c-to (c-type to)))
	       (or (equal c-from c-to)
		   (and (equal c-from "int") (equal c-to "SI_Long"))
		   (and (equal c-from "SI_Long") (equal c-to "int"))))
	     (and (foreign-type-string-p from)
		  (foreign-type-string-p to)))
	 (values statements expression temps))
	((eq from (translator-foreign-type :object))
	 (coerce-to-c-type from to statements expression temps))
	((eq from (translator-foreign-type :void))
	 (error "Internal error: :void expression ~S in non-void context."
		expression))
	((eq to (translator-foreign-type :object))
	 (coerce-from-c-type from to statements expression temps))
	(t
	 (if (or (and (c-integer-foreign-type-p from)
		      (c-integer-foreign-type-p to))
		 (and (c-float-foreign-type-p from)
		      (c-float-foreign-type-p to)))
	     (values statements (make-target-form 'cast to expression) temps)
	     (multiple-value-bind (statements expression)
		 (coerce-from-c-type from (translator-foreign-type :object)
				     statements expression temps)
	       (coerce-to-c-type (translator-foreign-type :object) to
				 statements expression temps))))))

(defun target-form-simple-p (form)
  (member (target-form-type form)
	  '(symbolic-constant
	    c-constant constant constant-label
	    initial-symbol initial-package load-time-variable
	    local-variable special-variable)))

(defun box-unbox-aux (operator inverse from to statements expression temps)
  (let ((foreign-type (case operator
			(box-value from)
			(unbox-value to))))
    (cond ((and (eq (target-form-type expression) inverse)
		(eq (translator-foreign-type (cadr expression))
		    foreign-type))
	   (values statements (caddr expression) temps))
	  ((eq (target-form-type expression) 'comma-operator)
	   (let ((last (last expression)))
	     (multiple-value-bind (new-statements new-expression new-temps)
		 (box-unbox-aux operator inverse from to nil (car last) temps)
	       (if new-statements
		   (values (nconc new-statements 
				  (nreverse (butlast (cdr expression)))
				  statements)
			   new-expression
			   new-temps)
		   (progn
		     (setf (car last) new-expression)
		     (values statements expression new-temps))))))
	  (t
	   (case operator
	     (box-value 
	      (box-unbox-aux1 'box-value from to
			      statements expression temps))
	     (unbox-value
	      (cond ((and (or (eq foreign-type
				  (translator-foreign-type :float))
			      (eq foreign-type
				  (translator-foreign-type :single-float))
			      (eq foreign-type
				  (translator-foreign-type :double-float)))
			  (eq (target-form-type expression) 'constant))
		     (values 
		      statements
		      (make-target-form
		       'c-constant
		       (translator-foreign-type :static-float)
		       (second expression))
		      temps))
		    ((and (or (eq foreign-type
				  (translator-foreign-type :string))
			      (eq foreign-type
				  (translator-foreign-type :static-string)))
			  (eq (target-form-type expression) 'constant))
		     (values
		      statements
		      (make-target-form
		       'c-constant
		       (translator-foreign-type :static-string)
		       (second expression))
		      temps))
		    (t
		     (box-unbox-aux1 'unbox-value from to
				     statements expression temps)))))))))

(defun box-unbox-aux1 (operator from to statements expression temps)
  (let (%type)
    (declare (ignorable %type))
    (multiple-value-bind (foreign-type name)
	(case operator
	  (box-value   (values from (boxer from)))
	  (unbox-value (values to   (unboxer to))))
      (when (and (not (keywordp name))
		 (let ((fd (defined-as-function name)))
		   (and fd
			(function-descriptor-foreign-protocol fd)
			(car (foreign-function-arguments-badp fd))
			(not (target-form-simple-p expression)))))
	(multiple-value-setq (statements expression %type temps)
	  (handle-lvalue-context statements expression (lisp-type foreign-type)
				 temps from)))
      (values
       statements
       (case operator
	 (box-value
	  (make-target-form 'box-value foreign-type expression))
	 (unbox-value
	  (make-target-form 'unbox-value foreign-type expression)))
       temps))))

;;; This function is used by handle-context to throw away boxing operations
;;; in an *ignore-context* context 
;;; (where the return value is being discarded anyway).

(defun discard-box-unbox (expression &optional type)
  (case (target-form-type expression)
    (box-value
     (caddr expression))
    (unbox-value
     (caddr expression))
    (comma-operator
     (let ((last (last expression)))
       (setf (car last)
	     (discard-box-unbox (car last) type)))
     expression)
    (t
     expression)))


(defun abstract-c-type-for-foreign-type (type)
  (coerce (mapcan #'(lambda (x)
		      (typecase x
			(character (list x))
			(string (coerce x 'list))
			(t (coerce (format nil "~A" x) 'list))))
		  (c-type-for-foreign-type type))
	  'string))

(defvar *foreign-type-without-c-type-list* nil)

(define-translator-parameter *generate-ansi-c-types* nil)

(defun c-type-for-foreign-type (type &optional name pointer-p quals)
  (unless (listp name) (setq name (list name)))
  (let ((type-name (if (stringp type)
		       type
		       (translator-foreign-type-name 
			(if (eq type ':values)
			    ':object
			    type)))))
    (if (atom type-name)
	(let* ((c-type-name (if (stringp type-name)
				type-name
				(c-type type-name)))
	       (space (position #\space c-type-name)))
	  (when (and space (alpha-char-p (aref c-type-name (1+ space))))
	    (setq space (position #\space c-type-name :start (1+ space))))
	  (cond ((and space (eql #\* (aref c-type-name (1+ space))))
		 (c-type-for-foreign-type 
		  `(:pointer ,(subseq c-type-name 0 space)) name pointer-p
		  quals))
		((eq c-type-name :none)
		 (unless (member type-name *foreign-type-without-c-type-list*)
		   (push type-name *foreign-type-without-c-type-list*)
		   (warn "There is no c type for foreign type ~S" type-name))
		 `("No_C_Type" ,@(when name `(#\space ,@name))))
		(t
		 `(,@quals
		   ,c-type-name ,@(when name `(#\space ,@name))))))
	(ecase (car type-name)
	  (:const
	   (c-type-for-foreign-type (cadr type-name) name pointer-p
				    `("const" #\space ,@quals)))
	  (:volatile
	   (c-type-for-foreign-type (cadr type-name) name pointer-p
				    `("volatile" #\space ,@quals)))
	  (:pointer 
	   (c-type-for-foreign-type (cadr type-name) `(#\* ,@quals ,@name) t))
	  (:array
	   (when pointer-p
	     (setq name `(#\( ,@name #\))))
	   (c-type-for-foreign-type 
	    (cadr type-name)
	    `(,@name 
	      ,@(mapcan #'(lambda (dim)
			    (if (eq dim '*)
				(list #\[ #\])
				(list #\[ dim #\])))
			;; both cl and c use row-major
			(if (eq ':column-major (cadddr type-name))
			    (reverse (caddr type-name))
			    (caddr type-name))))
	    nil
	    quals))
	  ((:struct :union)
	   (let ((tag (cadr type-name))
		 (field-specs 
		  (mapcan #'(lambda (type+name)
			      (let ((type (car type+name))
				    (name (cadr type+name)))
				(append (c-type-for-foreign-type type name)
					(list #\;))))
			  (cddr type-name))))
	     `(,(if (eq (car type-name) :struct) "struct" "union")
	       ,@(when tag `(#\space ,tag))
	       ,@(when field-specs
		   `(#\space #\{ ,@field-specs #\}))
	       ,@(when name `(#\space ,@quals ,@name)))))
	  (:enum
	   (let ((tag (cadr type-name))
		 (constant-list (cddr type-name)))
	     `("enum"
	       ,@(when tag `(#\space ,tag))
	       ,@(when constant-list
		   `(#\space #\{ ,(car constant-list)
			     ,@(mapcan #'(lambda (constant)
					   `(#\, #\space ,constant))
				       (cdr constant-list))
			     #\}))
	       ,@(when name `(#\space ,@quals ,@name)))))
	  ((:function :variadic-function)
	   (when pointer-p
	     (setq name `(#\( ,@name #\))))
	   (c-type-for-function-type name type-name))))))

(defun c-type-for-function-type (name type-name)
  (c-type-for-foreign-type 
   (let ((result-type (caddr type-name)))
     (if (eq result-type ':values)
	 ':object
	 result-type))
   `(,@name 
     #\(,@
     (when *generate-ansi-c-types*
       (let ((param-specs (cadr type-name)))
	 (when (eq (car type-name) ':variadic-function)
	   (push ':int param-specs))
	 (if (null param-specs)
	     '("void")
	     (let* ((first-param (car param-specs))
		    (first-type (c-type-for-parameter first-param)))
	       (nconc first-type
		      (mapcan #'(lambda (type)
				  (cons #\, 
					(copy-list
					 (c-type-for-parameter type))))
			      (cdr param-specs)))))))
     #\))))

(defvar *ansi-c-more-parameters-string* "va_alist") ; our macros expand to "..."

(defvar *function-declaration-ansi-c-more-parameters-string*
  "...")

(defun c-type-for-parameter (type)
  (if (eq type '&rest)
      (list *ansi-c-more-parameters-string*)
      (if (and (consp type)
	       (eq (car type) ':named))
	  (c-type-for-foreign-type (cadr type) (caddr type))
	  (c-type-for-foreign-type type))))
