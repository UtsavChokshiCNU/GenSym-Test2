;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; library.lisp -- source-to-source transformations on library functions
;;;
;;; author :  Sandra Loosemore
;;; date   :  03 Sep 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/library.lisp,v $"
 "$Revision: 1.5 $"
 "$Date: 2007/07/13 18:16:53 $")

(deftransform =
    (($a)    (= $a)       (progn $a t))
    (($a $b) (= $a $b)    (trun:%num-eq-2 $a $b)))

(deftransform /=
    (($a)    (/= $a)      (progn $a t))
    (($a $b) (/= $a $b)   (trun:%num-ne-2 $a $b)))

(deftransform <
    (($a)    (< $a)       (progn $a t))
    (($a $b) (< $a $b)    (trun:%num-lt-2 $a $b)))

(deftransform >
    (($a)    (> $a)       (progn $a t))
    (($a $b) (> $a $b)    (trun:%num-gt-2 $a $b)))

(deftransform <=
    (($a)    (<= $a)      (progn $a t))
    (($a $b) (<= $a $b)   (trun:%num-le-2 $a $b)))

(deftransform >=
    (($a)    (>= $a)      (progn $a t))
    (($a $b) (>= $a $b)   (trun:%num-ge-2 $a $b)))


(deftransform +
    (()      (+)        0)
    (($a)    (+ $a)     (values $a))
    (($a $b) (+ $a $b)  (trun:%add-2 $a $b)))

(deftransform *
    (()      (*)        1)
    (($a)    (* $a)     (values $a))
    (($a $b) (* $a $b)  (trun:%times-2 $a $b)))

(deftransform /
    (($a)    (/ $a)     (trun:%reciprocal $a))
    (($a $b) (/ $a $b)  (trun:%divide-2 $a $b)))

(deftransform -
    (($a)    (- $a)     (trun:%negate $a))
    (($a $b) (- $a $b)  (trun:%minus-2 $a $b)))


(deftransform append
    (()      (append)          nil)
    (($a)    (append $a)       (values $a))
    (($a $b) (append $a $b)    (trun:%append-2 $a $b))
    (($a $b) (append $a . $b)  (trun:%append-2 $a (append . $b))))

(deftransform apply
    (($a)
     (apply #'list $a)
     (values $a))
    (($a)
     (apply 'list $a)
     (values $a))
    (($a $b)
     (apply $a $b)
     (trun:%apply-1 $a $b))
    (($a $b $c)
     (apply $a $b $c)
     (trun:%apply-2 $a $b $c))
    (($a $b $c $d)
     (apply $a $b $c $d)
     (trun:%apply-3 $a $b $c $d))
    (($a $b $c $d $e)
     (apply $a $b $c $d $e)
     (trun:%apply-4 $a $b $c $d $e))
    (($a $b $c $d $e $f)
     (apply $a $b $c $d $e $f)
     (trun:%apply-5 $a $b $c $d $e $f))
    )

(deftransform aref
    (($a)
     (aref $a)
     (trun:%aref-0 $a))
    (($a $i0)
     (aref $a $i0)
     (trun:%aref-1 $a $i0))
    (($a $i0 $i1)
     (aref $a $i0 $i1)
     (trun:%aref-2 $a $i0 $i1))
    (($a $i0 $i1 $i2)
     (aref $a $i0 $i1 $i2)
     (trun:%aref-3 $a $i0 $i1 $i2))
    (($a $i0 $i1 $i2 $i3)
     (aref $a $i0 $i1 $i2 $i3)
     (trun:%aref-4 $a $i0 $i1 $i2 $i3))
    (($a $i0 $i1 $i2 $i3 $i4)
     (aref $a $i0 $i1 $i2 $i3 $i4)
     (trun:%aref-5 $a $i0 $i1 $i2 $i3 $i4))
    (($a $i0 $i1 $i2 $i3 $i4 $i5)
     (aref $a $i0 $i1 $i2 $i3 $i4 $i5)
     (trun:%aref-6 $a $i0 $i1 $i2 $i3 $i4 $i5))
    (($a $i0 $i1 $i2 $i3 $i4 $i5 $i6)
     (aref $a $i0 $i1 $i2 $i3 $i4 $i5 $i6)
     (trun:%aref-7 $a $i0 $i1 $i2 $i3 $i4 $i5 $i6))
    )

(deftransform assoc
    (($a $b)   (assoc $a $b)             (trun:%assoc-eql $a $b))
    (($a $b)   (assoc $a $b :test #'eql) (trun:%assoc-eql $a $b))
    (($a $b)   (assoc $a $b :test 'eql)  (trun:%assoc-eql $a $b))
    (($a $b)   (assoc $a $b :test #'eq)  (trun:%assoc-eq $a $b))
    (($a $b)   (assoc $a $b :test 'eq)   (trun:%assoc-eq $a $b))
    (($a $b)   (assoc $a $b :test #'equal) (trun:%assoc-equal $a $b))
    (($a $b)   (assoc $a $b :test 'equal)  (trun:%assoc-equal $a $b))
    )


(deftransform bit
    (($a)
     (bit $a)
     (trun:%bit-0 $a))
    (($a $i0)
     (bit $a $i0)
     (trun:%bit-1 $a $i0))
    (($a $i0 $i1)
     (bit $a $i0 $i1)
     (trun:%bit-2 $a $i0 $i1))
    (($a $i0 $i1 $i2)
     (bit $a $i0 $i1 $i2)
     (trun:%bit-3 $a $i0 $i1 $i2))
    (($a $i0 $i1 $i2 $i3)
     (bit $a $i0 $i1 $i2 $i3)
     (trun:%bit-4 $a $i0 $i1 $i2 $i3))
    (($a $i0 $i1 $i2 $i3 $i4)
     (bit $a $i0 $i1 $i2 $i3 $i4)
     (trun:%bit-5 $a $i0 $i1 $i2 $i3 $i4))
    (($a $i0 $i1 $i2 $i3 $i4 $i5)
     (bit $a $i0 $i1 $i2 $i3 $i4 $i5)
     (trun:%bit-6 $a $i0 $i1 $i2 $i3 $i4 $i5))
    (($a $i0 $i1 $i2 $i3 $i4 $i5 $i6)
     (bit $a $i0 $i1 $i2 $i3 $i4 $i5 $i6)
     (trun:%bit-7 $a $i0 $i1 $i2 $i3 $i4 $i5 $i6))
    )

(deftransform char-equal
    (($a)     (char-equal $a)       (progn $a t))
    (($a $b)  (char-equal $a $b)    (trun:%char-equal-2 $a $b)))

(deftransform char-greaterp
    (($a)     (char-greaterp $a)       (progn $a t))
    (($a $b)  (char-greaterp $a $b)    (trun:%char-greaterp-2 $a $b)))
    
(deftransform char-lessp
    (($a)     (char-lessp $a)       (progn $a t))
    (($a $b)  (char-lessp $a $b)    (trun:%char-lessp-2 $a $b)))
    
(deftransform char-not-equal
    (($a)     (char-not-equal $a)       (progn $a t))
    (($a $b)  (char-not-equal $a $b)    (trun:%char-not-equal-2 $a $b)))

(deftransform char-not-greaterp
    (($a)     (char-not-greaterp $a)     (progn $a t))
    (($a $b)  (char-not-greaterp $a $b)  (trun:%char-not-greaterp-2 $a $b)))

(deftransform char-not-lessp
    (($a)     (char-not-lessp $a)       (progn $a t))
    (($a $b)  (char-not-lessp $a $b)    (trun:%char-not-lessp-2 $a $b)))
    
(deftransform char/=
    (($a)     (char/= $a)      (progn $a t))
    (($a $b)  (char/= $a $b)   (trun:%char-ne-2 $a $b)))

(deftransform char<
    (($a)     (char< $a)      (progn $a t))
    (($a $b)  (char< $a $b)   (trun:%char-lt-2 $a $b)))

(deftransform char<=
    (($a)     (char<= $a)      (progn $a t))
    (($a $b)  (char<= $a $b)   (trun:%char-le-2 $a $b)))

(deftransform char=
    (($a)     (char= $a)      (progn $a t))
    (($a $b)  (char= $a $b)   (trun:%char-eq-2 $a $b)))

(deftransform char>
    (($a)     (char> $a)      (progn $a t))
    (($a $b)  (char> $a $b)   (trun:%char-gt-2 $a $b)))

(deftransform char>=
    (($a)     (char>= $a)      (progn $a t))
    (($a $b)  (char>= $a $b)   (trun:%char-ge-2 $a $b)))

(deftransform coerce
    (($a)  (coerce $a 'character)  (character $a))
    (($a)  (coerce $a t)           (values $a))
    (($a)  (coerce $a 't)          (values $a)))

(deftransform delete
    (($a $b)   (delete $a $b)             (trun:%delete-eql $a $b))
    (($a $b)   (delete $a $b :test #'eql) (trun:%delete-eql $a $b))
    (($a $b)   (delete $a $b :test 'eql)  (trun:%delete-eql $a $b))
    (($a $b)   (delete $a $b :test #'eq)  (trun:%delete-eq $a $b))
    (($a $b)   (delete $a $b :test 'eq)   (trun:%delete-eq $a $b))
    (($a $b)   (delete $a $b :test #'equal) (trun:%delete-equal $a $b))
    (($a $b)   (delete $a $b :test 'equal)  (trun:%delete-equal $a $b))
    )

(define-translator-compiler-macro fdefinition
        (&whole form name &environment env)
  ;; See also compiler-macros for trun:setf-function & symbol-function.
  (let ((expanded-name (apply-macros name env)))
    (or (multiple-value-bind (value therep)
	    (translator-constant-value expanded-name env)
	  ;; If expanded name is a constant for which we have a value, and the
	  ;; value passes the validation test, then look up the function name
	  ;; in the environment.
	  (when (and therep (valid-function-name-p value))
	    (multiple-value-bind (usage boundp info)
		(translator-function-information value env)
	      (cond ((and (eq usage :function)
			  (not boundp)
			  (not (function-notinline info)))
		     ;; If name names a global function which is not declared
		     ;; notinline, then transform reference into a FUNCTION
		     ;; form.  Note that this transformation is not applied if
		     ;; no information is available for the function, since the
		     ;; FUNCTION special-form might use FDEFINITION in that
		     ;; case, leading to an infinite regress.  Note that if
		     ;; expanded-name is a reference to a named constant, this
		     ;; violates the usual rule of not resolving such at
		     ;; translation time.
		     `(function ,value))
		    ((symbolp value)
		     ;; If name is a symbol, transform into simpler
		     ;; symbol-function reference.
		     `(symbol-function ,expanded-name))
		    ((setf-function-name-p value)
		     ;; If name is a setf function name, transform into simpler
		     ;; setf-function reference.  When expanded name is a named
		     ;; constant, keep reference to constant rather than
		     ;; resolving value at translation time, in order to
		     ;; maintain mapping from Lisp source to translated C
		     ;; source.  The overhead for the runtime CADR should be
		     ;; minor.
		     (if (and (consp expanded-name)
			      (eq (car expanded-name) 'quote))
			 `(trun:setf-function ',(cadr value))
			 `(trun:setf-function
			       (cadr (the cons ,expanded-name)))))
		    ;; Otherwise, no transformation available.
		    (t nil)
		    ))))
	form)))

(deftransform gcd
    (()      (gcd)        0)
    (($a)    (gcd $a)     (values $a))
    (($a $b) (gcd $a $b)  (trun:%gcd-2 $a $b)))

(deftransform lcm
    (()      (lcm)        1)
    (($a)    (lcm $a)     (values $a))
    (($a $b) (lcm $a $b)  (trun:%lcm-2 $a $b)))

(deftransform logand
    (()      (logand)        -1)
    (($a)    (logand $a)     (values $a))
    (($a $b) (logand $a $b)  (trun:%logand-2 $a $b)))

(deftransform logeqv
    (()      (logeqv)        -1)
    (($a)    (logeqv $a)     (values $a))
    (($a $b) (logeqv $a $b)  (trun:%logeqv-2 $a $b)))

(deftransform logior
    (()      (logior)        0)
    (($a)    (logior $a)     (values $a))
    (($a $b) (logior $a $b)  (trun:%logior-2 $a $b)))

(deftransform logxor
    (()      (logxor)        0)
    (($a)    (logxor $a)     (values $a))
    (($a $b) (logxor $a $b)  (trun:%logxor-2 $a $b)))

(deftransform list
    (()               (list)                 nil)
    (($a)             (list $a)              (trun:%list-1 $a))
    (($a $b)          (list $a $b)           (trun:%list-2 $a $b))
    (($a $b $c)       (list $a $b $c)        (trun:%list-3 $a $b $c))
    (($a $b $c $d)    (list $a $b $c $d)     (trun:%list-4 $a $b $c $d))
    (($a $b $c $d $e) (list $a $b $c $d $e)  (trun:%list-5 $a $b $c $d $e))
    )

(deftransform list*
    (($a)             (list* $a)             (values $a))
    (($a $b)          (list* $a $b)          (trun:%list-star-2 $a $b))
    (($a $b $c)       (list $a $b $c)        (trun:%list-star-3 $a $b $c))
    )

(deftransform make-sequence
    (($a $b)
     (make-sequence 'list $a . $b)
     (make-list $a . $b))
    (($a $b)
     (make-sequence 'string $a . $b)
     (make-string $a . $b))
    (($a $b)
     (make-sequence 'simple-string $a . $b)
     (make-string $a . $b)))

(deftransform max
    (($a)    (max $a)     (values $a))
    (($a $b) (max $a $b)  (trun:%max-2 $a $b)))

(deftransform member
    (($a $b)   (member $a $b)             (trun:%member-eql $a $b))
    (($a $b)   (member $a $b :test #'eql) (trun:%member-eql $a $b))
    (($a $b)   (member $a $b :test 'eql)  (trun:%member-eql $a $b))
    (($a $b)   (member $a $b :test #'eq)  (trun:%member-eq $a $b))
    (($a $b)   (member $a $b :test 'eq)   (trun:%member-eq $a $b))
    (($a $b)   (member $a $b :test #'equal) (trun:%member-equal $a $b))
    (($a $b)   (member $a $b :test 'equal)  (trun:%member-equal $a $b))
    )

(deftransform min
    (($a)    (min $a)     (values $a))
    (($a $b) (min $a $b)  (trun:%min-2 $a $b)))

(deftransform nconc
    (()      (nconc)          nil)
    (($a)    (nconc $a)       (values $a))
    (($a $b) (nconc $a $b)    (trun:%nconc-2 $a $b))
    (($a $b) (nconc $a . $b)  (trun:%nconc-2 $a (nconc . $b))))

;;; Transforming (not (null a)) into a can be a bad idea in non-predicate
;;; contexts, since it may result in inhibiting garbage collection of
;;; large data structures in a.

(defvar *elide-not-null* nil)

(if *elide-not-null*
    (deftransform not
      (($a)  (not (atom $a))  (consp $a))
      (($a)  (not (consp $a)) (atom $a))
      (($a)  (not (not $a))   (values $a))
      (($a)  (not (null $a))  (values $a)))
    (deftransform not
      (($a)  (not (atom $a))  (consp $a))
      (($a)  (not (consp $a)) (atom $a))))



(deftransform nth
    (($a) (nth 0 $a) (first $a))
    (($a) (nth 1 $a) (second $a))
    (($a) (nth 2 $a) (third $a))
    (($a) (nth 3 $a) (fourth $a))
    (($a) (nth 4 $a) (fifth $a))
    (($a) (nth 5 $a) (sixth $a))
    (($a) (nth 6 $a) (seventh $a))
    (($a) (nth 7 $a) (eighth $a))
    (($a) (nth 8 $a) (ninth $a))
    (($a) (nth 9 $a) (tenth $a)))

(deftransform null
    (($a) (null $a) (not $a)))

(deftransform sbit
    (($a)
     (sbit $a)
     (trun:%sbit-0 $a))
    (($a $i0)
     (sbit $a $i0)
     (trun:%sbit-1 $a $i0))
    (($a $i0 $i1)
     (sbit $a $i0 $i1)
     (trun:%sbit-2 $a $i0 $i1))
    (($a $i0 $i1 $i2)
     (sbit $a $i0 $i1 $i2)
     (trun:%sbit-3 $a $i0 $i1 $i2))
    (($a $i0 $i1 $i2 $i3)
     (sbit $a $i0 $i1 $i2 $i3)
     (trun:%sbit-4 $a $i0 $i1 $i2 $i3))
    (($a $i0 $i1 $i2 $i3 $i4)
     (sbit $a $i0 $i1 $i2 $i3 $i4)
     (trun:%sbit-5 $a $i0 $i1 $i2 $i3 $i4))
    (($a $i0 $i1 $i2 $i3 $i4 $i5)
     (sbit $a $i0 $i1 $i2 $i3 $i4 $i5)
     (trun:%sbit-6 $a $i0 $i1 $i2 $i3 $i4 $i5))
    (($a $i0 $i1 $i2 $i3 $i4 $i5 $i6)
     (sbit $a $i0 $i1 $i2 $i3 $i4 $i5 $i6)
     (trun:%sbit-7 $a $i0 $i1 $i2 $i3 $i4 $i5 $i6))
    )

;;; Transform SET into SETQ when symbol is a constant form that evaluates to
;;; a symbol which is declared or proclaimed special.

(define-translator-compiler-macro set
    (&whole form symbol value &environment env)
  (let ((expanded (apply-macros symbol env)))
    (or (multiple-value-bind (var therep)
	    (translator-constant-value expanded env)
	  (and therep
	       (symbolp var)
	       (eq (translator-variable-information var env) :special)
	       `(setq ,var ,value)))
	form)))
  

;;; Transforms aren't supported for SETF functions, so
;;; write translator-compiler-macros which do the same thing.

(defparameter *setf-aref-transforms*
  '((0 . trun:%set-aref-0)
    (1 . trun:%set-aref-1)
    (2 . trun:%set-aref-2)
    (3 . trun:%set-aref-3)
    (4 . trun:%set-aref-4)
    (5 . trun:%set-aref-5)
    (6 . trun:%set-aref-6)
    (7 . trun:%set-aref-7)
    ))

(define-translator-compiler-macro (setf aref)
	(&whole form value array &rest indices)
  (transform-setf-aref-aux *setf-aref-transforms*
			   form value array indices))

(defun transform-setf-aref-aux (transforms form value array indices)
  ;; Helper function for (SETF AREF), (SETF BIT), and (SETF SBIT).
  (let ((transform (cdr (assoc (length indices) transforms))))
    (if transform
	`(,transform ,array ,@indices ,value)
	form)))

(defparameter *setf-bit-transforms*
  '((0 . trun:%set-bit-0)
    (1 . trun:%set-bit-1)
    (2 . trun:%set-bit-2)
    (3 . trun:%set-bit-3)
    (4 . trun:%set-bit-4)
    (5 . trun:%set-bit-5)
    (6 . trun:%set-bit-6)
    (7 . trun:%set-bit-7)
    ))

(define-translator-compiler-macro (setf bit)
        (&whole form value array &rest indices)
  (transform-setf-aref-aux *setf-bit-transforms*
			   form value array indices))

(defparameter *setf-sbit-transforms*
  '((0 . trun:%set-sbit-0)
    (1 . trun:%set-sbit-1)
    (2 . trun:%set-sbit-2)
    (3 . trun:%set-sbit-3)
    (4 . trun:%set-sbit-4)
    (5 . trun:%set-sbit-5)
    (6 . trun:%set-sbit-6)
    (7 . trun:%set-sbit-7)
    ))

(define-translator-compiler-macro (setf sbit)
        (&whole form value array &rest indices)
  (transform-setf-aref-aux *setf-sbit-transforms*
			   form value array indices))

(define-translator-compiler-macro trun:set-fdefinition
        (&whole form name value &environment env)
  (let ((expanded-name (apply-macros name env)))
    (or (multiple-value-bind (name-value therep)
	    (translator-constant-value expanded-name env)
	  ;; Transform into setf of specialized accessor if the name is
	  ;; a constant with the appropriate type.
	  (cond ((not therep) nil)
		((symbolp name-value)
		 `(setf (symbol-function ,expanded-name) ,value))
		((setf-function-name-p name-value)
		 `(setf (trun:setf-function ,expanded-name) ,value))
		(t nil)))
	form)))

;;; The macro for (SETF SUBSEQ) is a bit of a kludge:  The database
;;; contains a dummy entry for SET-SUBSEQ; END is defaulted to NIL
;;; by the SETF handler.  Eliminating SET-SUBSEQ and writing a 
;;; translator-compiler-macro for (SETF SUBSEQ) might introduce
;;; order-of-evaluation issues.

(define-translator-compiler-macro trun:set-subseq (sequence start end new-sequence)
  (when (null new-sequence)
    (error "Internal error:  (SETF SUBSEQ) decomposed incorrectly."))
  (if (null end)
      `(trun:%set-subseq-1 ,sequence ,start ,new-sequence)
    `(trun:%set-subseq-2 ,sequence ,start ,end ,new-sequence)))

(define-translator-compiler-macro trun:setf-function
        (&whole form name &environment env)
  ;; See also compiler-macros for fdefinition & symbol-function.
  (let ((expanded-name (apply-macros name env)))
    (or (multiple-value-bind (value therep)
	    (translator-constant-value expanded-name env)
	  ;; If expanded name is a constant for which we have a value,
	  ;; and the value passes the validation test, then look up the
	  ;; function name in the environment.
	  (when (and therep (setf-function-name-p value))
	    (multiple-value-bind (usage boundp info)
		(translator-function-information value env)
	      ;; If name names a global function which is not declared
	      ;; notinline, then transform reference into a FUNCTION form.
	      ;; Note that this transformation is not applied if no information
	      ;; is available for the function, since the FUNCTION special-form
	      ;; might use SETF-FUNCTION in that case, leading to an infinite
	      ;; regress.  Note that if expanded-name is a reference to a named
	      ;; constant, this violates the usual rule of not resolving such
	      ;; at translation time.
	      (and (eq usage :function)
		   (not boundp)
		   (not (function-notinline info))
		   `(function ,value)))))
	form)))

(deftransform tx:string-append
  (($a $b)      (tx:string-append $a $b)     (trun:%string-append-2 $a $b)))

(define-translator-compiler-macro symbol-function
        (&whole form name &environment env)
  ;; See also compiler-macros for fdefinition & trun:setf-function.
  (let ((expanded-name (apply-macros name env)))
    (or (multiple-value-bind (value therep)
	    (translator-constant-value expanded-name env)
	  ;; If expanded name is a constant for which we have a value,
	  ;; and the value passes the validation test, then look up the
	  ;; function name in the environment.
	  (when (and therep (symbolp value))
	    (multiple-value-bind (usage boundp info)
		(translator-function-information value env)
	      ;; If name names a global function which is not declared
	      ;; notinline, then transform reference into a FUNCTION form.
	      ;; Note that this transformation is not applied if no information
	      ;; is available for the function, since the FUNCTION special-form
	      ;; might use SYMBOL-FUNCTION in that case, leading to an infinite
	      ;; regress.  Note that if expanded-name is a reference to a named
	      ;; constant, this violates the usual rule of not resolving such
	      ;; at translation time.
	      (and (eq usage :function)
		   (not boundp)
		   (not (function-notinline info))
		   `(function ,value)))))
	form)))

;;; Transform SYMBOL-VALUE into direct variable reference when symbol is a
;;; constant form that evaluates to a declared or proclaimed special or a
;;; named constant.

(define-translator-compiler-macro symbol-value
    (&whole form symbol &environment env)
  (let ((expanded-name (apply-macros symbol env)))
    (or (multiple-value-bind (value therep)
	    (translator-constant-value expanded-name env)
	  (and therep
	       (symbolp value)
	       (member (translator-variable-information value env)
		       '(:special :constant))
	       ;; return-from in case value happens to be Nil!
	       (return-from symbol-value value)))
	form)))

;;; The real guts for this is defined in type.lisp.
;;; *** Replacing symbolic constants with their values is questionable.
;;; *** On the other hand, we also expand DEFTYPE'd type specifiers.
;;; *** I suppose that if people don't want this kind of optimization,
;;; *** they can disable it by declaring TYPEP to be NOTINLINE.

(define-translator-compiler-macro tcl:typep
    (&whole form object type &optional (envarg nil) &environment env)
  (if envarg form
      (multiple-value-bind (value therep)
	  (translator-constant-value (apply-macros type env) env)
	(if (not therep)
	    form
	    (multiple-value-bind (object-value object-therep)
		(translator-constant-value (apply-macros object env) env)
	      (if (not object-therep)
		  (or (optimize-typep object value env)
		      form)
		  (not (null (typep object-value value)))))))))

;;; Handlers to give FORMAT and friends immediate string arguments

(defun make-format-string (string)
  ;; Elide ~<newline><whitespace>; ~:<newline>; ~@<newline>.
  ;; Convert <newline> to ~%.
  ;; return a C-STRING (immediate string) structure
  (declare (type string string))
  (let* ((chars '())
	 (len (length string))
	 (len-1 (1- len))
	 (len-2 (- len 2))
	 (new-string-p nil))
    (declare (type fixnum len len-1 len-2))  
    (flet ((eat-non-newline-whitespace-chars (i)
	     (do ((j i (1+ j)))
		 ((= j len) j)
	       (declare (type fixnum j))
	       (let ((c (char string j)))
		 (when (or (char= c #\Newline)
			   (not (whitespace-char-p c)))
		   (return j))))))
      (do ((i 0))
	  ((= i len))
	(declare (type fixnum i))
	(let ((c (char string i)))
	  (cond ((char/= c #\~)
		 (push c chars)
		 (incf i))
		((< i len-1)
		 ;; Special processing when see ~ and at 
		 ;; least one char remaining.
		 ;; Look ahead one char.
		 (let ((c1 (char string (1+ i))))
		   (cond ((char= c1 #\Newline)
			  ;; ~<newline>
			  ;; Eat non-newline whitespace chars 
			  (setq i (eat-non-newline-whitespace-chars (+ i 2)))
			  (setq new-string-p t))
			 ((and (char= c1 #\:)
			       (< i len-2)
			       (char= (char string (+ i 2)) #\Newline))
			  ;; ~:<newline>
			  ;; Ignore Newline, but process whitespace-chars.
			  (setq i (+ i 3))
			  (setq new-string-p t))
			 ((and (char= c1 #\@)
			       (< i len-2)
			       (char= (char string (+ i 2)) #\Newline))
			  ;; ~@<newline>
			  ;; Don't ignore Newline, but ignore whitespace-chars.
			  (push #\Newline chars)
			  (setq i (eat-non-newline-whitespace-chars (+ i 3)))
			  (setq new-string-p t))
			 (t
			  (push c chars)
			  (push c1 chars)
			  (incf i 2)))))
		(t
		 (push c chars)
		 (incf i))))))
    (when new-string-p
      (setq string (coerce (nreverse chars) 'simple-string)))
    (make-c-string :string string)))

(defun long-c-string-p (object)
  (and *maximum-c-string-constant-length*
       (c-string-p object)
       (< *maximum-c-string-constant-length*
	  (length (c-string-string object)))))

(defun use-format-c-string-function-p (control)
  (and (stringp control)
       (not (long-c-string-p (make-format-string control)))))

(define-translator-compiler-macro break
	(&whole whole control &rest arguments)
  (if (use-format-c-string-function-p control)
      `(trun:%break ,(length (cdr whole))
		    ,(make-format-string control)
		    ,@arguments)
      whole))

(define-translator-compiler-macro tcl:cerror
	(&whole whole continue control &rest arguments)
  (if (and (use-format-c-string-function-p continue)
	   (use-format-c-string-function-p control))
      `(trun:%cerror ,(length (cdr whole))
		     ,(make-format-string continue)
		     ,(make-format-string control)
		     ,@arguments)
      whole))

(define-translator-compiler-macro tcl:error
	(&whole whole control &rest arguments)
  (if (use-format-c-string-function-p control)
      `(trun:%error ,(length (cdr whole))
		    ,(make-format-string control)
		    ,@arguments)
      whole))

(define-translator-compiler-macro format
	(&whole whole stream control &rest arguments)
  (if (use-format-c-string-function-p control)
      `(trun:%format ,(length (cdr whole))
		     ,stream
		     ,(make-format-string control)
		     ,@arguments)
      whole))

(define-translator-compiler-macro trun:set-package
  	(&whole whole string)
  (if (stringp string)
      `(trun:%set-package ,(make-c-string :string string))
      whole))

(define-translator-compiler-macro tcl:warn
	(&whole whole control &rest arguments)
  (if (use-format-c-string-function-p control)
      `(trun:%warn ,(length (cdr whole))
		   ,(make-format-string control)
		   ,@arguments)))

(define-translator-compiler-macro y-or-n-p
	(&whole whole control &rest arguments)
  (if (use-format-c-string-function-p control)
      `(trun:%y-or-n-p ,(length (cdr whole))
		       ,(make-format-string control)
		       ,@arguments)
      whole))

(define-translator-compiler-macro yes-or-no-p
	(&whole whole control &rest arguments)
  (if (use-format-c-string-function-p control)
      `(trun:%yes-or-no-p ,(length (cdr whole))
			  ,(make-format-string control)
			  ,@arguments)
      whole))

;;; Functions used by test suite

(define-translator-compiler-macro trun:do-test
	(&whole whole string test-result expected-result)
  (if (stringp string)
      `(trun:%do-test ,(make-c-string :string string)
		      (catch :abort ,test-result)
		      ,expected-result)
    whole))

(define-translator-compiler-macro trun:do-side-effects-test
	(&whole whole string test-result expected-result)
  (if (stringp string)
      `(trun:do-side-effects-test ,(make-c-string :string string)
				  ,test-result
				  ,expected-result)
    whole))

;;; Transforms on type-specific operators
;;; This whole setup is a bit bogus, in the sense that:
;;; 1.  Eventually these macros will become %FIXNUM-TIMES, etc.,
;;;     and TX:*% will be a supported extension (a Lisp macro;
;;;     not sure if it should "exist at runtime"; probably).
;;;     Also, doing them as Lisp macros isn't entirely satisfactory,
;;;     since it prevents users from being to access the operators
;;;     directly (if he wants to improve on the Translator's algorithm).
;;; 2.  Transforms are supposed to transform a valid call into
;;;     something better.  In this case, the original calls are
;;;     *not* valid.  Maybe we should make the lambda list take
;;;     two optional arguments?  But the function itself can't
;;;     handle a call with optionals.

(deftransform trun:*%
    (()      (trun:*%)             1)
    (($a)    (trun:*% $a)          (values $a)))

(deftransform trun:+%
    (()      (trun:+%)             0)
    (($a)    (trun:+% $a)          (values $a)))

(deftransform trun:-%
    (($a)    (trun:-% $a)          (trun:negate% $a)))

(deftransform trun:/%
    (($a $b) (trun:/% $a $b)       (trun:truncate% $a $b)))

(deftransform trun:/=%
    (($a)    (trun:/=% $a)         (progn $a t)))

(deftransform trun:<%
    (($a)    (trun:<% $a)          (progn $a t)))

(deftransform trun:<=%
    (($a)    (trun:<=% $a)         (progn $a t)))

(deftransform trun:=%
    (($a)    (trun:=% $a)          (progn $a t)))

(deftransform trun:>=%
    (($a)    (trun:>=% $a)         (progn $a t)))

(deftransform trun:>%
    (($a)    (trun:>% $a)          (progn $a t)))

(deftransform trun:-%d
    (($a)    (trun:-%d $a)         (trun:negate%d $a)))

(deftransform trun:atan%d
    (($a)    (trun:atan%d $a)      (trun:atan1%d $a)))

(deftransform trun:ceiling%d
    (($a)    (trun:ceiling%d $a)   (trun:ceiling1%d $a)))

(deftransform trun:floor%d
    (($a)    (trun:floor%d $a)     (trun:floor1%d $a)))

(deftransform trun:fround%d
    (($a)    (trun:fround%d $a)    (trun:fround1%d $a)))

(deftransform trun:log%d
    (($a)    (trun:log%d $a)       (trun:log1%d $a)))

(deftransform trun:round%d
    (($a)    (trun:round%d $a)     (trun:round1%d $a)))

(deftransform trun:truncate%d
    (($a)    (trun:truncate%d $a)  (trun:truncate1%d $a)))

(deftransform trun:-%rd
    (($a)    (trun:-%rd $a)        (trun:negate%rd $a)))

(deftransform trun:atan%rd
    (($a)    (trun:atan%rd $a)     (trun:atan1%rd $a)))

(deftransform trun:ceiling%rd
    (($a)    (trun:ceiling%rd $a)  (trun:ceiling1%rd $a)))

(deftransform trun:floor%rd
    (($a)    (trun:floor%rd $a)    (trun:floor1%rd $a)))

(deftransform trun:fround%rd
    (($a)    (trun:fround%rd $a)   (trun:fround1%rd $a)))

(deftransform trun:log%rd
    (($a)    (trun:log%rd $a)      (trun:log1%rd $a)))

(deftransform trun:round%rd
    (($a)    (trun:round%rd $a)    (trun:round1%rd $a)))

(deftransform trun:truncate%rd
    (($a)    (trun:truncate%rd $a) (trun:truncate1%rd $a)))

;;; Hack to support Lucid and Allegro LOOP expansions

#+(and (or lcl4.0 ALLEGRO) (not translating))
(define-translator-compiler-macro lisp:last (x) `(tcl:last ,x))

;; ldb, ldb-test, mask-field, dpb, deposite-field
(defmacro with-decoded-bytespec ((size position bytespec whole env)
				 &body forms)
  `(let ((,size 0)(,position 0))
     (multiple-value-bind (bytespec-value bytespec-valuep)
	 (translator-constant-value ,bytespec ,env)
       (cond (bytespec-valuep
	      (setq ,size (byte-size bytespec-value))
	      (setq ,position (byte-position bytespec-value)))
	     ((and (consp ,bytespec)
		   (eq (car ,bytespec) 'byte))
	      (multiple-value-setq (,size bytespec-valuep)
		(translator-constant-value (cadr ,bytespec) ,env))
	      (when bytespec-valuep
		(multiple-value-setq (,position bytespec-valuep)
		  (translator-constant-value (caddr ,bytespec) ,env)))))
       (if bytespec-valuep
	   (progn ,@forms)
	   ,whole))))

(define-translator-compiler-macro mask-field (&whole whole bytespec integer
					      &environment env)
  (with-decoded-bytespec (size position bytespec whole env)
    (let ((m (deposit-field -1 (byte size position) 0)))
      `(logand ,m ,integer))))

(define-translator-compiler-macro ldb (&whole whole bytespec integer
					      &environment env)
  (with-decoded-bytespec (size position bytespec whole env)
    `(logand ,(1- (ash 1 size)) (ash ,integer ,(- position)))))

(define-translator-compiler-macro ldb-test (&whole whole bytespec integer
					    &environment env)
  (with-decoded-bytespec (size position bytespec whole env)
    (let ((m (deposit-field -1 (byte size position) 0)))
      `(not (zerop (logand ,m ,integer))))))

(define-translator-compiler-macro deposite-field
    (&whole whole newbyte bytespec integer &environment env)
  (with-decoded-bytespec (size position bytespec whole env)
    (let ((m (deposit-field -1 (byte size position) 0)))
      `(logior (logand ,newbyte ,m) (logand ,integer ,(lognot m))))))

(define-translator-compiler-macro dpb (&whole whole newbyte bytespec integer
				       &environment env)
  (with-decoded-bytespec (size position bytespec whole env)
    (let ((m (deposit-field -1 (byte size position) 0)))
      `(logior (ash (logand ,newbyte ,(1- (ash 1 size))) ,position)
	       (logand ,integer ,(lognot m))))))

(define-translator-compiler-macro ash (&whole whole integer count
				       &environment env)
  (multiple-value-bind (integer-value integer-valuep)
      (translator-constant-value integer env)
    (multiple-value-bind (count-value count-valuep)
	(translator-constant-value count env)
      (if (and integer-valuep count-valuep)
	  (ash integer-value count-value)
	  whole))))

(define-translator-macro trun:1+%long (long)
  `(trun:+%long ,long 1))

(define-translator-macro trun:1+%int64 (long)
  `(trun:+%int64 ,long 1))

(define-translator-macro trun:1-%long (long)
  `(trun:-%long ,long 1))

(define-translator-macro trun:1-%int64 (long)
  `(trun:-%int64 ,long 1))

(define-translator-macro trun:1+%double (long)
  `(trun:+%double ,long 1d0))

(define-translator-macro trun:1-%double (long)
  `(trun:-%double ,long 1d0))

(define-translator-macro trun:1+%single (long)
  `(trun:+%single ,long 1s0))

(define-translator-macro trun:1-%single (long)
  `(trun:-%single ,long 1s0))

(define-translator-macro trun:zerop%long (long)
  `(trun:=%long 0 ,long))

(define-translator-macro trun:plusp%long (long)
  `(trun:<%long 0 ,long))

(define-translator-macro trun:minusp%long (long)
  `(trun:>%long 0 ,long))

(define-translator-macro trun:evenp%long (long)
  `(trun:=%long 0 (trun:logand%long 1 ,long)))

(define-translator-macro trun:oddp%long (long)
  `(trun:=%long 1 (trun:logand%long 1 ,long)))

(define-translator-macro trun:zerop%double (long)
  `(trun:=%double 0.0d0 ,long))

(define-translator-macro trun:zerop%single (long)
  `(trun:=%single 0.0s0 ,long))

(define-translator-macro trun:plusp%single (long)
  `(trun:<%single 0.0s0 ,long))

(define-translator-macro trun:minusp%single (long)
  `(trun:>%single 0.0s0 ,long))

(define-translator-macro trun:plusp%double (long)
  `(trun:<%double 0.0d0 ,long))

(define-translator-macro trun:minusp%double (long)
  `(trun:>%double 0.0d0 ,long))

(define-translator-macro trun:logtest%long (long1 long2)
  `(trun:/=%long 0 (trun:logand%long ,long1 ,long2)))

(define-translator-macro trun:logbitp%long (index long)
  `(trun:logtest%long (ash 1 ,index) ,long))

(define-translator-macro trun:ash-left%long (long shift)
  `(trun:shift-left%long (the (unsigned-byte 32) ,long) (the (integer 0 31) ,shift)))

(define-translator-macro trun:ash-right%long (long shift)
  `(trun:shift-right%long ,long (the (integer 0 31) (- ,shift))))

(define-translator-macro trun:logandc1%long (long1 long2)
  `(trun:logand%long (trun:lognot%long ,long1) ,long2))

(define-translator-macro trun:logandc2%long (long1 long2)
  `(trun:logand%long ,long1 (trun:lognot%long ,long2)))

(define-translator-macro trun:lognand%long (long1 long2)
  `(trun:lognot%long (trun:logand%long ,long1 ,long2)))

(define-translator-macro trun:lognor%long (long1 long2)
  `(trun:lognot%long (trun:logior%long ,long1 ,long2)))

(define-translator-macro trun:logorc1%long (long1 long2)
  `(trun:logior%long (trun:lognot%long ,long1) ,long2))

(define-translator-macro trun:logorc2%long (long1 long2)
  `(trun:logior%long ,long1 (trun:lognot%long ,long2)))

(define-translator-macro trun:logeqv%long (long1 long2)
  `(trun:lognot%long (trun:logxor%long ,long1 ,long2)))

(define-translator-macro trun:expt2 (two integer)
  (declare (ignore two))
  `(ash 1 ,integer))

(define-translator-compiler-macro trun:%add-2 (&whole form x y)
  (let ((x-value (translator-constant-value x)))
    (or (and (numberp x-value)
	     (cond ((equalp x-value 1)
		    `(1+ ,y))
		   ((equalp x-value -1)
		    `(1- ,y))))
	(let ((y-value (translator-constant-value y)))
	  (and (numberp y-value)
	       (cond ((equalp y-value 1)
		      `(1+ ,x))
		     ((equalp y-value -1)
		      `(1- ,x)))))
	form)))

(define-translator-compiler-macro trun:%minus-2 (&whole form x y)
  (or (let ((y-value (translator-constant-value y)))
	(and (numberp y-value)
	     (cond ((equalp y-value 1)
		    `(1- ,x))
		   ((equalp y-value -1)
		    `(1+ ,x)))))
      form))

(define-translator-macro trun:%long-to-float2 (long float)
  (declare (ignore float))
  `(trun:%long-to-float ,long))

(define-translator-macro trun:%long-to-double2 (long float)
  (declare (ignore float))
  `(trun:%long-to-double ,long))

(define-translator-parameter *inline-map-functions-p* t)

(defun make-map-form (form function list lists accumulate sublist-p)
  (unless (and *inline-map-functions-p*
	       (consp function)
	       (eq (car function) 'function))
    (return-from make-map-form form))
  (let* ((lists (cons list lists))
	 (list-vars (let ((i -1))
		      (mapcar #'(lambda (list)
				  (declare (ignore list))
				  (make-symbol (sformat "LIST~D"
						       (incf i))))
			      lists)))
	 (result-var (when accumulate (make-symbol "RESULT")))
	 (value-var (when (eq accumulate 'nconc) (make-symbol "VALUE")))
	 (last-var (when accumulate (make-symbol "LAST")))
	 (new-last-var (when (eq accumulate 'list) (make-symbol "NEW-LAST")))
	 (call-form `(,(cadr function)
		       ,@(mapcar #'(lambda (list-var)
				     (if sublist-p
					 list-var
					 `(car ,list-var)))
				 list-vars))))
    `(do* (,@(mapcar #'(lambda (list-var list)
			 `(,list-var ,list (cdr ,list-var)))
		     list-vars lists)
	   ,@(when accumulate 
	       `((,result-var nil)
		 (,last-var nil))))
	  ((or ,@(mapcar #'(lambda (list-var)
			     `(null ,list-var))
			 list-vars))
	   ,result-var)
       ,(ecase accumulate
	  ((nil)   call-form)
	  ((list)  `(let ((,new-last-var (cons ,call-form nil)))
		      (if ,result-var
			  (setf (cdr ,last-var) ,new-last-var)
			  (setq ,result-var ,new-last-var))
		      (setq ,last-var ,new-last-var)))
	  ((nconc) `(let ((,value-var ,call-form))
		      (when ,value-var
			(if ,last-var
			    (setf (cdr ,last-var) ,value-var)
			    (setq ,result-var ,value-var))
			(setq ,last-var ,value-var)
			(do ()
			    ((null (trun:%m-cdr ,last-var)))
			  (setq ,last-var (trun:%m-cdr ,last-var))))))))))

(define-translator-compiler-macro mapcar (&whole form
						 function list &rest lists)
  (make-map-form form function list lists 'list nil))

(define-translator-compiler-macro maplist (&whole form
						  function list &rest lists)
  (make-map-form form function list lists 'list t))


(define-translator-compiler-macro mapc (&whole form
					       function list &rest lists)
  (make-map-form form function list lists nil nil))


(define-translator-compiler-macro mapl (&whole form
					       function list &rest lists)
  (make-map-form form function list lists nil t))


(define-translator-compiler-macro mapcan (&whole form
						 function list &rest lists)
  (make-map-form form function list lists 'nconc nil))


(define-translator-compiler-macro mapcon (&whole form
						 function list &rest lists)
  (make-map-form form function list lists 'nconc t))

(define-translator-compiler-macro apply (&whole form)
  (or (optimize-apply form)
      (apply-transformations form apply-transformations)))

(defun optimize-apply (form)
  (let ((fn-form (cadr form))
	fn params args min-args (nreq 0))
    (when (and (consp fn-form) 
	       (eq (car fn-form) 'function)
	       (consp (setq fn (cadr fn-form)))
	       (eq (car fn) 'lambda)
	       (<= (setq min-args (1- (length (setq args (cddr form)))))
		   (dolist (param (setq params (cadr fn)) nreq)
		     (when (memq param '(&optional &rest &key &aux))
		       (return nreq))
		     (incf nreq))))
      (let* ((vars-tail (nthcdr min-args params))
	     (vars (ldiff params vars-tail))
	     (args-tail (nthcdr min-args args)) ; same as (last args)
	     (values (ldiff args args-tail)) ; same as (butlast args)
	     (args-list-var (make-symbol "ARGS-LIST")))
	`(let (,@(mapcar #'list vars values)
		 (,args-list-var ,(car args-tail)))
	   (destructuring-bind ,vars-tail ,args-list-var
	     ,@(cddr fn)))))))

(defun make-member-or-form (form env item-form list test)
  (if (< *member-to-or-limit* (length list))
      form
      (once-only* (item-form) env
	`(or ,@(mapcar #'(lambda (value)
			   `(,test ,item-form ',value))
		       list)))))

(define-translator-compiler-macro eql (&whole form a b)
  ;; In our RTL, we can use EQ for characters
  (multiple-value-bind (a-value a-valuep)
      (translator-constant-value a)
    (when a-valuep
      (if (typep a-value '(and number (not fixnum)))
	  (setq a-valuep nil)
	  (setq a `',a-value)))
    (multiple-value-bind (b-value b-valuep)
	(translator-constant-value b)
      (when b-valuep
	(if (typep a-value '(and number (not fixnum)))
	    (setq b-valuep nil)
	    (setq b `',b-value)))
      (if (or a-valuep b-valuep)
	  `(eq ,a ,b)
	  form))))

(define-translator-compiler-macro trun:%member-eql 
    (&whole form &environment env item list)
  (multiple-value-bind (list-value list-valuep)
      (translator-constant-value list)
    (if list-valuep
	(make-member-or-form form env item list-value 
			     (if (some #'numberp list-value)
				 'eql
				 'eq))
	form)))

(define-translator-compiler-macro expt (&whole form &environment env a b)
  (multiple-value-bind (b-value b-valuep)
      (translator-constant-value b)
    (if (and b-valuep (eql b-value 2))
	(once-only* (a) env
	  `(* ,a ,a))
	form)))
