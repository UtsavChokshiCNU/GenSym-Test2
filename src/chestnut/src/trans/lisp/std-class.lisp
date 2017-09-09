;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Methods defining the behavior of STANDARD-CLASS.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/std-class.lisp,v $"
			 "$Revision: 1.1 $"
			 "$Date: 2006/02/28 21:59:12 $")

(defgeneric tclosx:add-direct-subclass (super class)
  (:generic-function-class translator-generic-function))

(defgeneric tclosx:remove-direct-subclass (super class)
  (:generic-function-class translator-generic-function))

(defgeneric tclosx:validate-superclass (class super)
  (:generic-function-class translator-generic-function))

(defgeneric tclosx:compute-class-precedence-list (class)
  (:generic-function-class translator-generic-function))

(defgeneric tclosx:compute-slots (class)
  (:generic-function-class translator-generic-function))

(defgeneric compute-default-initargs (class)
  (:generic-function-class translator-generic-function))

(defgeneric tclosx:compute-effective-slot-definition
        (class slot-name direct-slot-definitions)
  (:generic-function-class translator-generic-function))

(defgeneric tclosx:effective-slot-definition-class (class direct-slots)
  (:generic-function-class translator-generic-function))

(defgeneric tclosx:class-default-superclasses (class)
  (:generic-function-class translator-generic-function))

(defgeneric compute-direct-slot-definition (class slot-description)
  (:generic-function-class translator-generic-function))

(defgeneric tclosx:direct-slot-definition-class (class slot-description)
  (:generic-function-class translator-generic-function))

(defgeneric static-class-p (class)
  (:generic-function-class translator-generic-function))

(defgeneric compute-static-class-p (class)
  (:generic-function-class translator-generic-function))

(defgeneric tclosx:elide-access-method-p (class slotd access-type)
  (:generic-function-class translator-generic-function))

;;;

(defmethod tclosx:add-direct-subclass :before ((super class) (class class))
  (or (tclosx:validate-superclass class super)
      (error "~S is not a valid direct superclass for ~S." super class)))

(defmethod tclosx:add-direct-subclass ((super class) (class class))
  (with-class-record (record super t)
    (pushnew class (class-record-direct-subclasses record))))

(defmethod tclosx:remove-direct-subclass ((super class) (class class))
  (with-class-record (record super t)
    (setf (class-record-direct-subclasses record)
	  (delete class (class-record-direct-subclasses record)))))

(defmethod tclosx:validate-superclass ((class class) (super class))
  ;; While bootstrapping, permit any superclass structure.
  *building-initial-class-hierarchy*)

(defmethod tclosx:validate-superclass ((class class)
				       (super tclos:forward-referenced-class))
  t)

(defmethod tclosx:validate-superclass ((class tclos:forward-referenced-class)
				       (super class))
  t)

(defmethod tclosx:validate-superclass ((class standard-class)
				       (super standard-class))
  t)

(defmethod tclosx:validate-superclass ((class tclos:funcallable-standard-class)
				       (super standard-class))
  t)

(defmethod tclosx:validate-superclass
    ((class tclos:funcallable-standard-class)
     (super tclos:funcallable-standard-class))
  t)

(defun forward-referenced-class-p (class)
  (typep class 'tclos:forward-referenced-class))

(defmethod tclosx:compute-class-precedence-list ((class class))
  (let* ((supers ())              ; list of all superclasses
	 ;; Alist of required relationships between classes.
	 ;; Entries are of the form (class . predecessor).
	 (constraints ())
	 ;; Alist of direct subclass relationships.
	 ;; Entries are of the form (class {direct-subclass}*).
	 ;; There will be an entry for each element in the initial supers list.
	 (subclasses ())
	 (unconstrained (list class))
	 (cpl-tail (list nil))
	 (cpl cpl-tail))
    (labels ((initialize-info (class)
	       (unless (member class supers :test #'eq)
		 (push class supers)
		 (let ((direct-supers (tclos:class-direct-superclasses class)))
		   ;; Collect subclass information.
		   (dolist (super direct-supers)
		     (let ((entry (assoc super subclasses :test #'eq)))
		       (when (null entry)
			 (setf entry (list super))
			 (push entry subclasses))
		       (push class (cdr entry))))
		   ;; Collect constraints.
		   (dolist (follow direct-supers)
		     (push (cons follow class) constraints)
		     (setf class follow))
		   ;; Recurse on each super.
		   (mapc #'initialize-info direct-supers)))))
      (initialize-info class)
      ;; Remove class from supers (it was the first item added).
      (setf supers (cdr (nreverse supers))))
    (labels ((constrainedp (class)
	       (assoc class constraints :test #'eq))
	     (collect-unconstrained (unconstrained)
	       (do ()
		   ((endp supers) unconstrained)
		 (if (not (constrainedp (car supers)))
		     ;; If current class is unconstrained, snap it out of
		     ;; supers and link it into the unconstrained list.
		     (rotatef supers (cdr supers) unconstrained)
		     ;; Head of supers list is constrained.  Walk down supers
		     ;; collecting and delinking unconstrained classes.
		     (return
		       (do ((tail supers))
			   ((endp (cdr tail)) unconstrained)
			 (if (not (constrainedp (cadr tail)))
			     ;; If current class is unconstrained, snap it out
			     ;; of supers and link it into the unconstrained
			     ;; list.
			     (let ((cdr-tail (cdr tail)))
			       (rotatef cdr-tail (cdr cdr-tail) unconstrained)
			       (setf (cdr tail) cdr-tail))
			     ;; Else cdr down class list.
			     (setf tail (cdr tail))))))))
	     (update-constraints (class-to-remove)
	       (do ()
		   ((endp constraints))
		 (if (eq class-to-remove (cdar constraints))
		     (setf constraints (cdr constraints))
		     (return
		       (do ((tail constraints))
			   ((endp (cdr tail)))
			 (if (eq class-to-remove (cdr (cadr tail)))
			     (setf (cdr tail) (cddr tail))
			     (setf tail (cdr tail))))))))
	     (add-class-to-cpl (class)
	       (setf (cdr cpl-tail) (list class))
	       (setf cpl-tail (cdr cpl-tail))
	       (update-constraints class))
	     (best-subclass (class)
	       (or (best-subclass-1 (cdr (assoc class subclasses :test #'eq))
				    (cdr cpl)
				    t)
		   ;; This should never happen.  Just a sanity check.
		   (error "Internal error -- ~S has no subclasses in the cpl??"
			  class)))
	     (best-subclass-1 (subclasses tail firstp)
	       (if (null subclasses)
		   (unless firstp tail)
		   (let ((new-tail (member (car subclasses) tail :test #'eq)))
		     (when new-tail (setf tail new-tail firstp nil))
		     (best-subclass-1 (cdr subclasses) tail firstp))))
	     )
      (loop
	(cond ((null unconstrained)
	       (if (null supers)
		   (return (cdr cpl))
		   (cpl-cycle-error class supers constraints)))
	      ((null (cdr unconstrained))
	       (add-class-to-cpl (pop unconstrained)))
	      (t
	       (let* ((best (car unconstrained))
		      (best-sub (best-subclass best))
		      (match nil))
		 (dolist (check (cdr unconstrained))
		   (let ((check-sub (best-subclass check)))
		     (cond ((eq check-sub best-sub) (push check match))
			   ((tailp check-sub best-sub)
			    (setf best check)
			    (setf best-sub check-sub)
			    (setf match nil)))))
		 ;; I think this can't happen, but it was easier to write the
		 ;; code to check than to prove that it can't happen even with
		 ;; an erroneous class geometry.
		 (when match
		   (unable-to-order-cpl-error class
					      (cons best match)
					      (car best-sub)
					      (cdr cpl)))
    		 (setf unconstrained (delete best unconstrained :test #'eq))
		 (add-class-to-cpl best))))
	(setf unconstrained (collect-unconstrained unconstrained))))))
		   
(defun unable-to-order-cpl-error (class unordered common-subclass cpl)
  (error "Unable to compute the class precedence list for ~S.~@
          With the partial precedence list computed so far~%  ~S~@
          the following classes are all unconstrained but have the same
          rightmost direct subclass ~S in the partial list, so no ordering
          constraint exists among them:~{~%  ~S~}"
	 class
	 cpl
	 common-subclass
	 unordered))

(defun cpl-cycle-error (class supers constraints)
  (error "Unable to compute the class precedence list for ~S.~@
          The local ordering constraints induce the following cycle:~{~%  ~S~}"
	 class
	 (labels ((search-for-cycle (supers constraints)
		    (cond ((null supers)
			   (error "Internal error -- can't find cycle??"))
			  ((search-for-cycle-1 (car supers) constraints nil))
			  (t (search-for-cycle (cdr supers) constraints))))
		  (search-for-cycle-1 (class constraints partial)
		    (if (member class partial)
			(cons class partial)        ; return found cycle
			(let ((tail constraints))
			  (push class partial)
			  (loop
			    (let ((entry (assoc class tail :test #'eq)))
			      (when (null entry) (return nil))
			      (let ((cycle (search-for-cycle-1 (cdr entry)
							       constraints
							       partial)))
				(when cycle (return cycle)))
			      (setf tail (cdr (member entry tail :test #'eq)))
			      ))))))
	   (search-for-cycle supers constraints))))

;;; This depends on the fact that class-precedence-list returns Nil in the
;;; presence of forward referenced supers.

(defun class-fully-defined-p (class)
  (not (find-if #'forward-referenced-class-p
		(tclos:class-precedence-list class))))

(defmethod compute-default-initargs ((class class) &aux (initargs ()))
  (dolist (class (tclos:class-precedence-list class) initargs)
    ;; Initargs is an alist with entries of the form
    ;;  (<initarg> <initfunction> <initform>)
    (dolist (new (tclos:class-direct-default-initargs class))
      (unless (assoc (car new) initargs :test #'eq)
	(push new initargs)))))

(defmethod tclosx:compute-slots ((class class))
  (let ((slot-alist ()))
    (dolist (class (tclos:class-precedence-list class))
      (dolist (slot (tclos:class-direct-slots class))
	(let* ((name (tclos:slot-definition-name slot))
	       (entry (assoc name slot-alist :test #'eq)))
	  (if (null entry)
	      (push (list name slot) slot-alist)
	      (push slot (cdr entry))))))
    (mapcar #'(lambda (entry)
		(tclosx:compute-effective-slot-definition
		     class (car entry) (nreverse (cdr entry))))
	    slot-alist)))

;;; This method really ought to be defined on INTERNAL-STANDARD-CLASS, and
;;; will be at runtime (assuming it is actually needed then).
;;; However, at translate time, internal-standard-class isn't really a super of
;;; standard-class or funcallable-standard-class, so we have this indirection
;;; to a helper function.

(defmethod tclosx:compute-effective-slot-definition
        ((class standard-class) slot-name direct-slot-definitions)
  (compute-effective-slot-definition--std-class class
						slot-name
						direct-slot-definitions))

(defmethod tclosx:compute-effective-slot-definition
        ((class tclos:funcallable-standard-class)
	 slot-name direct-slot-definitions)
  (compute-effective-slot-definition--std-class class
						slot-name
						direct-slot-definitions))

(defun compute-effective-slot-definition--std-class
       (class name slot-definitions)
  (let ((slotd-class
	 (tclosx:effective-slot-definition-class class slot-definitions)))
    (if (not (subtypep slotd-class 'tclosx:standard-effective-slot-definition))
	(error "The effective-slot-definition class of ~S is ~S,~@
                which is not a subtype of ~S."
	       class slotd-class 'tclosx:standard-effective-slot-definition)
	(let ((initargs (list :name name :class class)))
	  ;; The most specific slot specification specifies the allocation.
	  (setf (getf initargs :allocation)
		(tclos:slot-definition-allocation (car slot-definitions)))
	  ;; The most specific slot specification that specified an initform
	  ;; specifies the initform.  We actually determine which slot by
	  ;; searching for a non-nil initfunction (looking at the initforms
	  ;; doesn't work, since unsupplied initforms default to nil).
	  (dolist (slot slot-definitions)
	    (let ((initfunction (tclos:slot-definition-initfunction slot)))
	      (when initfunction
		(setf (getf initargs :initfunction) initfunction)
		(setf (getf initargs :initform)
		      (tclos:slot-definition-initform slot))
		(return))))
	  ;; Merge type specifiers together.
	  (let ((type t))
	    (dolist (slot slot-definitions)
	      (setf type (and-types type (tclos:slot-definition-type slot))))
	    (unless (eq type t) (setf (getf initargs :type) type)))
	  ;; For readers, writers, and initargs, the value for the effective
	  ;; applicable is the union of the values from all of the slots.
	  (let ((slot-initargs ())
		(readers ())
		(writers ()))
	    (dolist (slot slot-definitions)
	      (push (tclos:slot-definition-initargs slot) slot-initargs)
	      (push (tclos:slot-definition-readers slot) readers)
	      (push (tclos:slot-definition-writers slot) writers))
	    (flet ((union* (lists &key (test #'eql) &aux (result ()))
		     (dolist (list lists result)
		       (setf result
			     (nunion result (copy-list list) :test test)))))
	      (setf (getf initargs :initargs) (union* slot-initargs))
	      (setf (getf initargs :readers) (union* readers))
	      (setf (getf initargs :writers) (union* writers :test #'equal))))
	  ;; The documentation string of the most specific slot to specify a
	  ;; documentation string is used.
	  (dolist (slot slot-definitions)
	    (let ((documentation (tclos:documentation slot)))
	      (when documentation
		(return (setf (getf initargs :documentation) documentation)))))
	  (apply #'make-instance slotd-class initargs)))))

;;; These two methods should be a single method on INTERNAL-STANDARD-CLASS at
;;; runtime.

(defmethod tclosx:effective-slot-definition-class
        ((class standard-class) direct-slots)
  (effective-slot-definition-class--std-class class direct-slots))

(defmethod tclosx:effective-slot-definition-class
        ((class tclos:funcallable-standard-class) direct-slots)
  (effective-slot-definition-class--std-class class direct-slots))

(defun effective-slot-definition-class--std-class (class direct-slots)
  (case (tclos:slot-definition-allocation (car direct-slots))
    (:instance 'tclosx:standard-effective-local-slot-definition)
    (:class 'tclosx:standard-effective-shared-slot-definition)
    (otherwise
     (error "The slot allocation type ~S is not supported by metaclass ~S."
	    (tclos:slot-definition-allocation (car direct-slots))
	    (class-of class)))))

(defmethod tclosx:class-default-superclasses ((class standard-class))
  '(standard-object))

(defmethod tclosx:class-default-superclasses ((class class))
  (error "The metaclass ~S does not specify a default list of superclasses.~@
          At least one superclass must be specified in the DEFCLASS form."
	 (class-of class)))

;;; These two methods should be a single method on INTERNAL-STANDARD-CLASS at
;;; runtime.

(defmethod compute-direct-slot-definition
        ((class standard-class) slot-description)
  (compute-direct-slot-definition--std-class class slot-description))

(defmethod compute-direct-slot-definition
        ((class tclos:funcallable-standard-class) slot-description)
  (compute-direct-slot-definition--std-class class slot-description))

(defun compute-direct-slot-definition--std-class (class slot-description)
  (let ((slotd-class
	 (tclosx:direct-slot-definition-class class slot-description)))
    (if (subtypep slotd-class 'tclosx:standard-direct-slot-definition)
	;; Permit other keys so that translation time slot definitions aren't
	;; required to accept everything that runtime slot definitions are.
	(apply #'make-instance slotd-class
	       :allow-other-keys t slot-description)
	(error "The direct-slot-definition class of ~S is ~S,~@
                which is not a subtype of ~S."
	       class slotd-class 'tclosx:standard-direct-slot-definition))))

;;; These two methods should be a single method on INTERNAL-STANDARD-CLASS at
;;; runtime.

(defmethod tclosx:direct-slot-definition-class
    ((class standard-class) slot-description)
  (declare (ignore slot-description))
  'tclosx:standard-direct-slot-definition)

(defmethod tclosx:direct-slot-definition-class
    ((class tclos:funcallable-standard-class) slot-description)
  (declare (ignore slot-description))
  'tclosx:standard-direct-slot-definition)


(defun tclosx:find-effective-slot-definition (class slot-name)
  (car (member slot-name (tclos:class-slots class)
	       :test #'eql
	       :key #'tclos:slot-definition-name)))

;;; Determine whether instance slot layout can be computed at translation time.
;;; *** No method is needed on METHOD-CLASS since at translation time
;;; *** METHOD-CLASS is a subclass of STANDARD-CLASS.

(defmethod static-class-p ((class class))
  (with-class-record (record class t)
    (class-record-static-p record)))

;;; This variable should be true if standard-class and related classes are to
;;; permit definitions of classes at runtime that were not apparent at
;;; translation time.  This can occur either through the evaluation of a
;;; DEFCLASS form at runtime, a call to ENSURE-CLASS at runtime, a direct call
;;; to ENSURE-CLASS in translated code, or translation of a DEFCLASS form that
;;; is not at toplevel.

;;; Most classes are not redefinable.
(defmethod compute-static-class-p ((class class))
  (and (class-fully-defined-p class)
       (every #'static-class-p
	      (tclos:class-direct-subclasses class))))

;;; *** This should be defined elsewhere, and possibly documented as a user
;;; *** specifiable switch.
(defvar *standard-class-permits-runtime-subclasses* nil)

(defmethod compute-static-class-p ((class standard-class))
  (and (not *standard-class-permits-runtime-subclasses*)
       (call-next-method)))

(defmethod compute-static-class-p ((class tclos:funcallable-standard-class))
  (and (not *standard-class-permits-runtime-subclasses*)
       (call-next-method)))

;;; Determine whether calls to slot access methods may be optimized away.

;;; This method provides the heart of the translation time test.  Nothing like
;;; this should be necessary at runtime.  The problem we're solving here is
;;; that to get an accurate check for whether a transformation that elides the
;;; access method is valid, not only does the class being checked have to
;;; agree, but all subclasses must also agree.  Since we don't want to force
;;; everyone writing methods on this function to handle that problem themselves
;;; (even if they could, which isn't clear since we may not be documenting
;;; everything necessary to do so), we deal with it automatically once with
;;; this :around method.  It is the compute function that takes care of
;;; performing the tree walk.  In order to avoid doing the tree walk on a
;;; frequent basis, killing the performance of any optimizers that call this,
;;; the results get cached.

(defmethod tclosx:elide-access-method-p :around
    ((class class) (slotd tclosx:effective-slot-definition) access-type)
  (flet ((compute (slotd)
	   (and (call-next-method)
		(static-class-p class)
		(let ((name (tclos:slot-definition-name slotd)))
		  (every #'(lambda (class)
			     (tclosx:elide-access-method-p
			          class
				  (tclosx:find-effective-slot-definition
				       class name)
				  access-type))
			 (tclos:class-direct-subclasses class)))))
	 (check (slotd new-value old-value)
	   (cond ((null new-value)
		  (when old-value
		    (warn "The location of the ~S slot of the class ~S used ~
                           to be considered fixed.~%Some optimized slot ~
                           accesses may be invalid."
			  (tclos:slot-definition-name slotd)
			  (slot-definition-class slotd))))
		 ((null old-value)
		  (warn "The location of the ~S slot of the class ~S used to ~
                         be considered unfixed.~%Some slot accesses may not ~
                         have been modified."
			(tclos:slot-definition-name slotd)
			(slot-definition-class slotd)))))
	 )
    (handle-cached-slot slotd
			(ecase access-type
			  (:read 'static-read)
			  (:write 'static-write))
			#'compute
			#'check)))
     
;;; The default is to return Nil, meaning that the access method must be
;;; called. 

(defmethod tclosx:elide-access-method-p
    ((class class) (slotd tclosx:effective-slot-definition) access-type)
  (declare (ignore access-type))
  nil)

;;; Accesses to local slots of standard-objects are permitted to be optimized
;;; in such a way that the underlying generic function isn't called.
;;; *** The paired methods on STANDARD-CLASS and FUNCALLABLE-STANDARD-CLASS
;;; *** should be merged at runtime into a single method on
;;; *** INTERNAL-STANDARD-CLASS.  No method is needed on METHOD-CLASS at
;;; *** translation time, since METHOD-CLASS is then a subclass of
;;; *** STANDARD-CLASS.

(defmethod tclosx:elide-access-method-p
    ((class standard-class)
     (slotd tclosx:standard-effective-local-slot-definition)
     access-type)
  (declare (ignore access-type))
  t)

(defmethod tclosx:elide-access-method-p
    ((class tclos:funcallable-standard-class)
     (slotd tclosx:standard-effective-local-slot-definition)
     access-type)
  (declare (ignore access-type))
  t)

;;; STRUCTURE-CLASS

(defmethod tclosx:class-default-superclasses ((class structure-class))
  '(structure-object))

(defmethod tclosx:validate-superclass
    ((class structure-class) (super structure-class))
  t)

(defmethod tclosx:validate-superclass
    ((class structure-class) (super tclos:forward-referenced-class))
  nil)
