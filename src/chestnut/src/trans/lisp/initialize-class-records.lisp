;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Initialize the class record database.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/initialize-class-records.lisp,v $"
 "$Revision: 1.2 $"
 "$Date: 2006/03/14 22:03:57 $")

(defun early-parse-slot (slot env)
  (declare (ignore env))
  (macrolet ((note-arg (key value)
	       `(setf initargs (list* ,key ,value initargs)))
	     (note-list-arg (key value)
	       `(pushnew ,value (getf initargs ,key nil) :test #'equal)))
    (do* ((slot-name (pop slot))
	  (initargs (list :name slot-name)))
	 ((endp slot)
	  (multiple-value-bind (key initform)
	      (get-properties initargs '(:initform))
	    (when (and key (not (getf initargs :initfunction)))
	      ;; Note: Can't use make-initfunction here, because the database
	      ;; has not yet been initialized, which means that things like
	      ;; NIL and T are not yet recognized as constants!
	      (note-arg :initfunction
			;; Ordinarily I'd use CASE here, but Lucid 4.0 CASE
			;; issues a bogus warning about a duplicate key T (even
			;; though using (CASE ... ((T) ...))) but generates the
			;; right code anyway.
			(cond ((null initform)
			       'trun:constantly-nil-initfunction)
			      ((eq initform 'T)
			       'trun:constantly-t-initfunction)
			      (t
			       (error "Early class with non-constant initform ~
                                       and no explicit initfunction."))))
	      (note-arg 'tclos-run:constant-initform-p t))
	    initargs))
      (let ((key (pop slot))
	    (value (pop slot)))
	(ecase key
	  ((:initform :initfunction tclos-run:constant-initform-p
	    :type :allocation :documentation)
	   (note-arg key value))
	  (:initarg (note-list-arg :initargs value))
	  (:reader (note-list-arg :readers value))
	  (:writer (note-list-arg :writers value))
	  (:accessor
	   (let ((reader value))
	     (note-list-arg :readers reader)
	     (note-list-arg :writers `(setf ,reader))))
	  )))))

;;; Table of class names which need to be instantiated during bootstrap.
;;; This table is used in the generation of the bootstrap info file (see
;;; build-boot.lisp).

(defparameter *bootstrap-classes* (make-hash-table :test 'eq))

(defun note-bootstrap-class (name)
  (setf (gethash name *bootstrap-classes*) (translator-find-class name)))

(defun bootstrap-class-p (name)
  (and (gethash name *bootstrap-classes*) t))

(defun note-early-class
       (name supers slots &key (metaclass 'standard-class) (bootstrap nil))
  (assert *building-initial-class-hierarchy*)
  (let* (#+genera (metaclass-name metaclass)
	 (env *default-global-environment*)
	 (host-class (find-class name nil))
	 (slots (mapcar #'(lambda (slot)
			    (early-parse-slot slot env))
			slots)))
    (setq metaclass (find-metaclass metaclass env))
    (unless (translator-find-class name nil env)
      (unless (and host-class
		   (or (eq metaclass (class-of host-class))
		       (eq name 't)))
	(setf host-class (allocate-instance metaclass))
	#+genera
	(if (eq metaclass-name 'built-in-class)
	    (setf (slot-value host-class 'clos-internals::name) name)
	    (setf (slot-value host-class 'clos-internals::bits) 0
		  (class-name host-class) name))
        #+lcl4.1
        (setf (slot-value host-class 'clos::name) name)
	#-(or genera lcl4.1)
	(setf (class-name host-class) name))
      (setf (defined-as-class name env) host-class))
    (ensure-translator-class name
			     :metaclass metaclass
			     :direct-superclasses supers
			     :direct-slots slots
			     :environment env)
    (when bootstrap (note-bootstrap-class name))))


(defun note-built-in-class (name &optional (supers t) bootstrap)
  (when (eq supers T) (setq supers '(t)))
  (note-early-class name supers ()
		    :metaclass 'built-in-class
		    :bootstrap bootstrap))

(let ((*building-initial-class-hierarchy* t))

  (note-early-class 't () ())    ; for now, make it standard-class
  (note-early-class 'standard-object '(t) ())
  (note-early-class 'tclos-run:metaobject
		    '(standard-object)
		    *metaobject-slots*)
  (note-early-class 'class '(tclos-run:metaobject) *class-slots*)
  (note-early-class 'tclos-run:slotted-class '(class) ())
  (note-early-class 'tclosx:internal-standard-class
		    '(tclos-run:slotted-class) ())
  (note-early-class 'standard-class
		    '(tclosx:internal-standard-class)
		    ()
		    :bootstrap t)

  (note-early-class 'built-in-class '(class) () :bootstrap t)
  (note-built-in-class 't () ()) ; Now that built-in-class exists, fix up T

  (note-early-class 'tclos:slot-definition
		    '(tclos-run:metaobject)
		    *slot-definition-slots*)
  (note-early-class 'tclosx:direct-slot-definition
		    '(tclos:slot-definition) ())
  (note-early-class 'tclosx:effective-slot-definition
		    '(tclos:slot-definition)
		    ())
  (note-early-class 'tclos:standard-slot-definition
		    '(tclos:slot-definition) ())
  (note-early-class 'tclosx:standard-direct-slot-definition
		    '(tclos:standard-slot-definition
		      tclosx:direct-slot-definition)
		    ()
		    :bootstrap t)
  (note-early-class 'tclosx:standard-effective-slot-definition
		    '(tclos:standard-slot-definition
		      tclosx:effective-slot-definition)
		    *effective-slot-definition-slots*)
  (note-early-class 'tclosx:standard-effective-local-slot-definition
		    '(tclosx:standard-effective-slot-definition)
		    ()
		    :bootstrap t)
  (note-early-class 'tclosx:standard-effective-shared-slot-definition
		    '(tclosx:standard-effective-slot-definition)
		    ())

  (note-early-class 'tclos:funcallable-standard-class
		    '(tclosx:internal-standard-class) ()
		    :bootstrap t)

  (note-early-class 'tclosx:method-class
		    '(tclosx:internal-standard-class) ()
		    :bootstrap t)

  (note-early-class 'tclos:forward-referenced-class '(class)
		    *forward-referenced-class-slots*)

  (note-early-class 'structure-class '(tclos-run:slotted-class)
		    *structure-class-slots*)
  (note-early-class 'structure-object '(t) () :metaclass 'structure-class)

  ;; Built-in classes
  ;; These need to be kept in sync with the descriptions in type.lisp.
  ;; Perhaps there should be some changes made to type.lisp to permit making
  ;; this code be data driven instead of having hard coded values here.

  (note-built-in-class 'array t t)
  (note-built-in-class 'character t t)
  (note-built-in-class 'function '(standard-object) t)
  (note-built-in-class 'number)
  (note-built-in-class 'sequence)
  (note-built-in-class 'symbol t t)

  (note-built-in-class 'complex '(number) t)
  (note-built-in-class 'real '(number))
  (note-built-in-class 'float '(real) t)
  (note-built-in-class 'rational '(real))
  (note-built-in-class 'integer '(rational) t)
  (note-built-in-class 'ratio '(rational) t)

  (note-built-in-class 'vector '(array sequence) t)
  (note-built-in-class 'bit-vector '(vector) t)
  (note-built-in-class 'string '(vector) t)

  (note-built-in-class 'list '(sequence))
  (note-built-in-class 'cons '(list) t)
  (note-built-in-class 'null '(symbol list) t)

  (note-built-in-class 'trun:internal-marker t t)

  ;; These are currently built-in.  However, some of them may change later.

  (note-built-in-class 'trun:class-wrapper t t)
  (note-built-in-class 'trun:effective-method t t)
  (note-built-in-class 'method-combination t t)

  (note-built-in-class 'trun:cobject t t)
  (note-built-in-class 'hash-table t t)
  (note-built-in-class 'package t t)
  (note-built-in-class 'random-state t t)
  (note-built-in-class 'readtable t t)

  (note-built-in-class 'pathname t t)
  (note-built-in-class 'logical-pathname '(pathname) t)

  (note-built-in-class 'stream)
  (note-built-in-class 'broadcast-stream '(stream) t)
  (note-built-in-class 'concatenated-stream '(stream) t)
  (note-built-in-class 'echo-stream '(stream) t)
  (note-built-in-class 'file-stream '(stream) t)
  (note-built-in-class 'string-stream '(stream) t)
  (note-built-in-class 'trun:string-input-stream '(string-stream) t)
  (note-built-in-class 'trun:string-output-stream '(string-stream) t)
  (note-built-in-class 'synonym-stream '(stream) t)
  (note-built-in-class 'two-way-stream '(stream) t)
  (note-built-in-class 'trun:interaction-stream '(stream) t)
  (note-built-in-class 'tx:foreign-pointer t t)

  
  ;; To be defined in later files
  ;;
  ;;  generic-function
  ;;  standard-generic-function
  ;;  method
  ;;  standard-method
  ;;
  ;; Defined later if structures support slot access protocol.
  ;;
  ;;  structure-direct-slot-definition
  ;;  structure-effective-slot-definition
  ;;  structure-slot-definition

  )

#+genera
 (clos-internals::finalize-inheritance
   (find-class 'tclosx:method-class))
