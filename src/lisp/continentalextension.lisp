;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module CONTINENTALEXTENSION

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Shiplu Mokaddim, 



;;;; Introduction

;;; This file is part of Telewindows and G2, and contains code which is shared
;;; between them to implement DLL interoperability and integration into the
;;; modern development environments and frameworks.

;;; C function mapping
(def-gensym-c-function c-g2nke-historical-mean
                       (:object "g2nke_historical_mean")
  ((:object arg-variable)
   (:object window-size)
   (:object start-index)))

;;; system procedure for KB level
(defun-for-system-procedure kb-g2nke-historical-mean (history window-size start-index)
	;;; KB level expects the return value to be a quantity type. 
	(make-evaluation-quantity
  #-(and lispworks (not chestnut-3))
  (c-g2nke-historical-mean history window-size start-index)
  #+(and lispworks (not chestnut-3))
  (coerce-to-gensym-float 
   (/ 
    (loop for i from start-index to (- (min (+ window-size start-index) (number-of-datapoints history nil nil nil)) 1)
          for val = (get-value-of-previous-datapoint history nil i)
          sum (if (nanp val) 0 val))
    window-size))))

;;; C function mapping
(def-gensym-c-function c-g2nke-historical-variance
                       (:object "g2nke_historical_variance")
  ((:object arg-variable)
   (:object window-size)
   (:object start-index)))

;;; system procedure for KB level
(defun-for-system-procedure kb-g2nke-historical-variance (history window-size start-index)
	;;; KB level expects the return value to be a quantity type. 
	(make-evaluation-quantity
  #-(and lispworks (not chestnut-3))
  (c-g2nke-historical-variance history window-size start-index)
  #+(and lispworks (not chestnut-3))
  (loop for i from start-index to (- (min (+ window-size start-index) (number-of-datapoints history nil nil nil)) 1)
        for val = (get-value-of-previous-datapoint history nil i)
        with sum-1 = 0
        with sum-2 = 0 do
        (unless (nanp val) 
          (setf sum-1 (+ sum-1 val))
          (setf sum-2 (+ sum-2 (* val val))))
        finally (return (coerce-to-gensym-float 
                         (/ (* (- (/ sum-2 window-size)
                                  (* (/ sum-1 window-size)
                                     (/ sum-1 window-size)))
                               window-size)
                            (- window-size 1)))))))
