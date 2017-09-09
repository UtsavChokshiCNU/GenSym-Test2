;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Early translator metaobjects.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/early-metaclasses.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:04 $")

(defclass tclosx:method-class (standard-class) ())

#+LCL4.0
(defmethod clos-system:validate-superclass
    ((class tclosx:method-class) (super standard-class))
  t)

;;; Allegro doesn't let you make and use subclasses of
;;; standard-generic-function. Fortunately, we don't use this for anything.

#-allegro
(defclass translator-generic-function (standard-generic-function) ()
  (:metaclass tclos:funcallable-standard-class)
  #-MCL ; :documentation doesn't seem to work for this metaclass
  (:documentation
   "Generic functions whose purpose is translator implementation, and which
do not need to be present in the runtime system, should be of this class.
This will hopefully make it easier to determine whether a generic function
needs a runtime definition."))

#+allegro
(setf (find-class 'translator-generic-function)
      (find-class 'clos::standard-generic-function))

#+genera
 (clos-internals::finalize-inheritance
   (find-class 'translator-generic-function))
