
(in-package :tcl-user)

(defpackage :foreign
    (:use :tcl)
  (:nicknames :tf)
  (:use :tx)
  (:export
   def-foreign-callable
   def-foreign-struct
   def-foreign-synonym-type
   def-foreign-function
   defined-foreign-type-p	  
   foreign-aref
   typed-foreign-aref
   foreign-string-value
   foreign-pointer-address
   foreign-pointer
   foreign-pointer-p
   foreign-pointer-type
   foreign-typep
   foreign-type-size
   foreign-type-modulus
   foreign-type-remainder
   foreign-value
   foreign-variable-address
   foreign-variable-pointer
   free-foreign-pointer
   make-foreign-pointer
   malloc-foreign-pointer
   copy-foreign-pointer
   stationary-object-p
   with-static-area
   foreign-type-name
   foreign-type))

(in-package :foreign)

(defconstant pointer-size #+x86-64 8 #-x86-64 4)

(defvar *foreign-type-table* nil)

(defmacro foreign-type-table ()
  `(or *foreign-type-table* (initialize-foreign-type-table)))

(defun defined-foreign-type-p (type)
  (gethash type (foreign-type-table)))

(defstruct (foreign-type
	     (:constructor nil)
	     (:print-function print-foreign-type))
  name
  (size 1)
  (modulus 1)
  (remainder 0)
  (reader nil)
  (writer nil))

(defun print-foreign-type (ft stream depth)
  (declare (ignore depth))
  (format stream "#<Foreign-Type ~S>"
	  (foreign-type-name ft)))

(defstruct (primitive-foreign-type
	     (:include foreign-type)))

(defstruct (pointer-foreign-type
	     (:include foreign-type))
  to-type)

(defstruct (array-foreign-type
	     (:include foreign-type))
  to-type
  dimensions)

(defstruct (structure-foreign-type
	     (:include foreign-type)))

(defun foreign-type (type &optional (error-p t))
  (when (and (not (or (symbolp type) (consp type)))
	     (foreign-type-p type))
    (return-from foreign-type type))
  (or (gethash type (foreign-type-table))
      (when (consp type)
	(case (car type)
	  (:pointer
	   (let* ((to-type-name (cadr type))
		  (name `(:pointer ,to-type-name)))
	     (setf (gethash name *foreign-type-table*)
		   (make-pointer-foreign-type
		    :name name
		    :size pointer-size
		    :to-type (foreign-type to-type-name)))))
	  (:array
	   (let* ((to-type-name (cadr type))
		  (dimensions (caddr type))
		  (name `(:array ,to-type-name ,dimensions))
		  (to-type (foreign-type to-type-name)))
	     (setf (gethash name *foreign-type-table*)
		   (make-array-foreign-type
		    :name name
		    :size (the fixnum
			       (* (the fixnum (foreign-type-size to-type))
				  (let ((ts 1))
				    (declare (fixnum ts))
				    (dolist (i dimensions ts)
				      (declare (fixnum i))
				      (setq ts (* ts i))))))
		    :to-type to-type
		    :dimensions dimensions)))))))
  (when error-p (error "foreign type ~S not found" type)))

(defun define-foreign-synonym-type-internal (atomic-type-name type-name)
  (setf (gethash atomic-type-name (foreign-type-table))
	(foreign-type type-name)))

(defmacro def-foreign-synonym-type (atomic-type-name type-name)
  `(progn
     (eval-when (compile)
       (define-translator-foreign-synonym-type ,atomic-type-name ,type-name))
     (eval-when (load eval)
       (define-foreign-synonym-type-internal ',atomic-type-name ',type-name))))

(tx:toplevel-c-lines
 "#define character_pft_reader_internal(address) (&(char *)address)")

(tx:def-foreign-function (character-pft-read-internal
			  (:name "character_pft_read_internal")
			  (:return-type :char)
			  (:protocol :accessor))
  (address :pointer))

(defun character-pft-reader (address)
  (character-pft-read-internal address))

(tx:def-foreign-function (set-character-pft-read-internal
			  (:return-type :char)
			  (:protocol :lvalue-setter))
  (address :pointer))

(defun character-pft-writer (address new-value)
  (setf (character-pft-reader-internal address) new-value))

(defun initialize-foreign-type-table ()
  (macrolet ((define-primitive-foreign-type (name size &optional reader writer)
		 `(setf (gethash ',name *foreign-type-table*)
			(make-primitive-foreign-type
			 :name ',name
			 :size ,size
			 :modulus ,size
			 :reader ,reader
			 :writer ,writer))))
    (setq *foreign-type-table* (make-hash-table :test 'equal))
    (define-primitive-foreign-type :character :size 1) ; :char
    (define-primitive-foreign-type :signed-8bit :size 1)
    (define-primitive-foreign-type :signed-16bit :size 2)
    (define-primitive-foreign-type :signed-32bit :size 4)
    (define-primitive-foreign-type :signed-64bit :size 8)
    (define-primitive-foreign-type :unsigned-8bit :size 1)
    (define-primitive-foreign-type :unsigned-16bit :size 2)
    (define-primitive-foreign-type :unsigned-32bit :size 4)
    (define-primitive-foreign-type :unsigned-64bit :size 8)
    (define-primitive-foreign-type :single-float :size 4)
    (define-primitive-foreign-type :double-float :size 8)
    (define-primitive-foreign-type :fixnum :size pointer-size)
    (define-primitive-foreign-type :pointer :size pointer-size)
    (define-primitive-foreign-type :null nil :size 0) ; :void
    (define-primitive-foreign-type :simple-string nil :size pointer-size)
    (define-primitive-foreign-type :lisp nil :size pointer-size) ; :object
    (define-primitive-foreign-type :simple-vector-type nil :size pointer-size)
    *foreign-type-table*))

#||
(defmacro def-foreign-struct (name-and-options &rest slot-descriptions)
  (let* ((name (if (consp name-and-options)
		   (car name-and-options)
		   name-and-options))
	 (constructor-info (when (consp name-and-options)
			     (assoc :constructor (cdr name-and-options))))
	 (constructor (if constructor-info
			  (cadr constructor-info)
			  (intern (format nil "MAKE-~S" name))))
	 (no-overlay '(no-overlay))
	 (foreign-type-symbol (intern (format nil "~S-FOREIGN-TYPE-SYMBOL"
					      name)))
	 (offset 0))
    (declare (ignore no-overlay offset))
    `(progn
       (eval-when (:compile-toplevel)
	 #+translating
	 (tutil:print-progress-message "Foreign Structure" ',name))
       (eval-when (compile load eval)
	 (defvar ,foreign-type-symbol
	   (setf (gethash ',name *foreign-type-table*)
		 (make-structure-foreign-type
		  :name ',name
		  :symbol ',foreign-type-symbol
		  :size 0))))
       (setf (foreign-type-reader ,foreign-type-symbol)
	     (make-foreign-type-reader ,foreign-type-symbol))
       (setf (foreign-type-writer ,foreign-type-symbol)
	     (make-foreign-type-writer ,foreign-type-symbol))
       (defun ,(intern (format nil "~A-P" name)) (object)
	 (and (foreign-pointer-p object)
	      (eq ,foreign-type-symbol
		  (foreign-pointer-type object))))
       ,@(mapcar #'(lambda (slot-description)
		     (let ((slot-name (car slot-description))
			   (slot-type-name (getf (cdr slot-description)
						 ':type))
			   (overlays (getf (cdr slot-description)
					   ':overlays no-overlay)))
		       (declare (ignore slot-type-name overlays))
		       ;; Finish this
		       (let ((accessor-name (intern (format nil "~S-~S"
							    name slot-name))))
			 `(progn
			    (defun ,accessor-name (object)
			      nil)
			    (defun (setf ,accessor-name) (new-value object)
			      new-value)))))
		 slot-descriptions)
       ,@(when constructor
	   (let* ((names (mapcar #'car slot-descriptions))
		  (supplied-p-vars
		   (mapcar #'(lambda (name)
			       (intern (format nil "~S-SUPPLIED-P" name)))
			   names)))
	     `((defun ,constructor (&key ,@(mapcar #'(lambda (s-name s-p)
						       (list s-name nil s-p))
						   names supplied-p-vars))
		 (let ((.object. (make-foreign-pointer
				  :type (foreign-type ',name))))
		   ,@(mapcar #'(lambda (slot-name s-p)
				 (let ((accessor-name
					(intern (format nil "~S-~S"
							name slot-name))))
				   `(when ,s-p
				      (setf (,accessor-name .object.)
					    ,slot-name))))
			     names supplied-p-vars)
		   .object.)))))
       ',name)))
||#

(defstruct (foreign-pointer
	     (:constructor make-foreign-pointer-internal (type address))
	     (:copier copy-foreign-pointer-internal))
  type ; foreign-type name
  address)


(defun make-foreign-type-reader (foreign-type)
  #'(lambda (address)
      (make-foreign-pointer :type foreign-type
			    :address address)))

(defun make-foreign-type-writer (foreign-type)
  #'(lambda (address new-value)
      ;; what goes here?
      new-value))

(defun foreign-aref-address (foreign-vector indices)
  (let* ((address (foreign-pointer-address foreign-vector))
	 (type (foreign-pointer-type foreign-vector))
	 (to-type (array-foreign-type-to-type type))
	 (dimensions (array-foreign-type-dimensions type))
	 (rm-index (cond ((null dimensions) 0)
			 ((null (cdr dimensions))
			  (the fixnum (car indices)))
			 ((null (cddr dimensions))
			  (+ (the fixnum (* (the fixnum (car indices))
					    (the fixnum (cadr dimensions))))
			     (the fixnum (cadr indices))))
			 (t ; CLtL2, p. 450
			  (apply #'+ (maplist #'(lambda (x y)
						  (* (car x)
						     (apply #'* (cdr y))))
					      indices
					      dimensions)))))
	 (bytes-per-element (or (foreign-type-size to-type)
				(error "~S doesn't have a size" to-type)))
	 (offset (if (= bytes-per-element 1)
		     rm-index
		     (the fixnum (* rm-index bytes-per-element)))))
    (declare (type (unsigned-byte 32) address)
	     (fixnum rm-index bytes-per-element offset))
    (the (unsigned-byte 32) (+ address offset))))

(defun foreign-aref (foreign-vector &rest indices)
  (let* ((type (foreign-pointer-type foreign-vector))
	 (to-type (array-foreign-type-to-type type))
	 (reader (or (foreign-type-reader to-type)
		     (error "~S doesn't have a reader" to-type))))
    (funcall reader (the (unsigned-byte 32)
			 (foreign-aref-address foreign-vector indices)))))

(defun set-foreign-aref (new-value foreign-vector &rest indices)
  (let* ((type (foreign-pointer-type foreign-vector))
	 (to-type (array-foreign-type-to-type type))
	 (writer (or (foreign-type-writer to-type)
		     (error "~S doesn't have a writer" to-type))))
    (funcall writer (the (unsigned-byte 32)
			 (foreign-aref-address foreign-vector indices))
	     new-value)))

(defsetf foreign-aref (foreign-vector &rest indices) (new-value)
  `(set-foreign-aref ,new-value ,foreign-vector ,@indices))

;provide a compiler macro for this one
(defun typed-foreign-aref (foreign-type foreign-vector &rest indices)
  (declare (ignore foreign-type))
  (apply #'foreign-aref foreign-vector indices))

;provide a compiler macro for this one
(defsetf typed-foreign-aref (foreign-type foreign-vector &rest indices)
    (new-value)
  `(progn
     ,foreign-type
     (setf (foreign-aref ,foreign-vector ,@indices) ,new-value)))

(defmacro foreign-typep (foreign-pointer foreign-type)
  `(eq (foreign-pointer-type ,foreign-pointer)
       (foreign-type ,foreign-type)))

(defun foreign-value (foreign-pointer)
  (let* ((type (foreign-pointer-type foreign-pointer))
	 (reader (or (foreign-type-reader type)
		     (error "~S doesn't have a reader" type))))
    (funcall reader (foreign-pointer-address foreign-pointer))))

(defsetf foreign-value set-foreign-value)

(defun set-foreign-value (foreign-pointer new-value)
  (let* ((type (foreign-pointer-type foreign-pointer))
	 (writer (or (foreign-type-writer type)
		     (error "~S doesn't have a writer" type))))
    (funcall writer (foreign-pointer-address foreign-pointer)
	     new-value)))

;Finish this
(defun foreign-string-value (foreign-pointer)
  nil)

;Finish this
(defsetf foreign-string-value (foreign-pointer) (new-value)
  `(progn
     (foreign-string-value ,foreign-pointer)
     ,new-value))

(defun foreign-size-of (foreign-pointer)
  (let ((type (cond ((foreign-pointer-p foreign-pointer)
		     (foreign-pointer-type foreign-pointer))
		    ((foreign-type-p foreign-pointer)
		     foreign-pointer)
		    ((symbolp foreign-pointer)
		     (let ((type (foreign-type foreign-pointer)))
		       (if (pointer-foreign-type-p type)
			   (pointer-foreign-type-to-type type)
			   type)))
		    (t
		     (foreign-type foreign-pointer)))))
    (or (foreign-type-size type)
	(error "~s doesn't have a size" type))))

;Finish this
(defmacro make-foreign-pointer (&key (address nil address-p)
				     type static)
  (declare (ignore static))
  `(make-foreign-pointer-internal
    (foreign-type ,type)
    ,(if address-p
	 address
	 0)))

;Finish this
(defmacro malloc-foreign-pointer (&key type)
  ;; Like (make-foreign-pointer :type ,type),
  ;; but the result can be given to free-foreign-pointer.
  `(make-foreign-pointer :type ,type))

;Finish this
(defun copy-foreign-pointer (foreign-pointer &key static malloc)
  (declare (ignore static))
  (let* ((type (foreign-pointer-type foreign-pointer))
	 (new (if malloc
		  (malloc-foreign-pointer :type type)
		  (make-foreign-pointer :type type
					:static static))))
    ;; copy the contents
    new))
				    

;Finish this
(defun free-foreign-pointer (foreign-pointer)
  nil)

(eval-when (compile)

;Finish this
(tutil:deftranslate address-of-c-name (name)
  (unless (or (stringp name)
	      (and (consp name)
		   (eq (car name) 'quote)
		   (stringp (cadr name))))	      
    (error "The argument to ~S, ~s, is not a string or quoted string."
	   'address-of-c-name name))
  (setq name (eval name))
  (timpl::translate-constant 0))

(walk::defwalk-ignore address-of-c-name)

(tutil:define-translator-macro foreign-variable-pointer (name &environment env)
  (setq name (tutil:translator-macroexpand name env))
  (if (tutil:translator-constantp name)
      `(make-foreign-pointer :address (address-of-c-name ,name)
			     :type '(:pointer :unsigned-8bit))
      (error "~S requires a constant argument"
	     'foreign-variable-pointer)))
)
