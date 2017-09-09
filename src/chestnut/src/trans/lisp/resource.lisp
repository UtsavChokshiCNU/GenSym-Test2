;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/resource.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:11 $")

;;; Resources

;;; Same interface as the Lucid resource functions.

(defun print-resource (record stream depth)
  (declare (ignore depth))
  (format stream "#<Resource ~S size ~D maximum-size ~D>"
	  (resource-name record)
	  (length (resource-instance-vector record))
	  (array-dimension (resource-instance-vector record) 0)))

(defstruct (resource (:print-function print-resource)
		     (:constructor %make-resource))
  name		     
  instance-vector    ; An adjustable vector with fill-pointer.
  initializer
  constructor
  cleanup)

;;; Should we be calling the cleanup function here? I don't think so.
;;; anything in the resource should be already cleared
(defun clear-resource (resource)
  (setf (resource-instance-vector resource) (initial-resource-vector)))

(defun make-resource (name &key
			   constructor
			   (initial-copies 0)
			   (initialization-function #'identity)
			   (cleanup-function #'identity)
			   (initial-args nil))
  (let ((resource
	 (%make-resource :name name
			 :instance-vector (initial-resource-vector)
			 :initializer initialization-function
			 :constructor constructor
			 :cleanup cleanup-function)))
    (dotimes (i initial-copies)
      (vector-push-extend (apply constructor initial-args)
			  (resource-instance-vector resource)))
    resource))

  
(defun resource-allocate (resource &rest args)
  (if (zerop (length (resource-instance-vector resource)))
      (apply (resource-constructor resource) args)
      (apply (resource-initializer resource)
	     (vector-pop-contract (resource-instance-vector resource))
	     args)))

(defun resource-deallocate (resource object)
  (vector-push-extend (funcall (resource-cleanup resource) object)
		      (resource-instance-vector resource)))

(defmacro using-resource ((objvar resource &rest args) &body forms)
  `(let ((,objvar (resource-allocate ,resource ,@args)))
     (unwind-protect
	 (progn ,@forms)
       (when ,objvar
	 (resource-deallocate ,resource ,objvar)))))

;;; The opposite of vector-push-extend
;;; Return the last element of a vector, and subtract one from the
;;; fill pointer.

(defun vector-pop-contract (vector)
    (let ((last (1- (length vector))))
      (prog1 (aref vector last)
	(setf (aref vector last) nil)
	(decf (fill-pointer vector)))))

(defparameter *initial-resource-size* 50)

(defun initial-resource-vector ()
  (make-array (list *initial-resource-size*) :adjustable t :fill-pointer 0))


