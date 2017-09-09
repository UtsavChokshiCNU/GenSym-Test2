;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module SIMULATE3

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andreas Hofmann





;;;; Simulation Evaluation Operator Definitions

;; Simulation evaluators have disappeared.  This is now done in the stack
;; evaluator.  - AGH, 9/17/91.



;;;; Sim-eval


(def-substitution-macro sim-eval-variable-or-constant 
			(variable-or-constant?)
  (cond 
    ((temporary-constant-p variable-or-constant?)
     ;; If a temporary-constant, it was obtained from
     ;; an alist, therefore it should not be released or
     ;; copied, but values should be extracted from it.
     (constant-value variable-or-constant?))
    ((variable-p variable-or-constant?)
     (sim-eval-get-value-of-variable
       variable-or-constant?))
    ((parameter-p variable-or-constant?)
     (sim-eval-get-value-of-parameter
       variable-or-constant?))
    (t simulation-no-value)))

(def-substitution-macro
  sim-eval-variable-or-constant-evaluation-value
  (variable-or-constant?)
  (cond
    ((temporary-constant-p variable-or-constant?)
     ;; If a temporary-constant, it was obtained from
     ;; an alist, therefore it should not be released or
     ;; copied, but values should be extracted from it.
     (constant-value variable-or-constant?))
    ((variable-p variable-or-constant?)
     (sim-eval-get-evaluation-value-of-variable
       variable-or-constant?))
    ((parameter-p variable-or-constant?)
     (sim-eval-get-evaluation-value-of-parameter
       variable-or-constant?))
    (t simulation-no-value)))

;; The temporary-constant clause above may be obsolete!  -jra & agh 2/19/92

(def-substitution-macro valid-simulation-type-p (value)
  (or (numberp value)
      (symbolp value)
      (text-string-p value)))



(defun sim-eval-variable-for-designation (designation alist)
  (let* ((item (evaluate-designation designation alist))
	 (simulated-value (sim-eval-variable-or-constant item)))
    (if (no-simulation-value-p simulated-value)
	(post-simulation-warning-for-no-value item)
	simulated-value)))






