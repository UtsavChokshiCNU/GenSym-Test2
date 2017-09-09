;;; -*- Mode: Lisp; Package: HOST; Syntax: Common-Lisp -*-
;;;
;;; more-symbols.lisp -- additional symbols that exist in the run-time system
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/more-symbols.lisp,v $"
 "$Revision: 1.3 $"
 "$Date: 2007/06/26 19:48:37 $")

(defun n-index-vars (n)
  (reverse
   (nthcdr (- 7 n) 
	   '(index6 index5 index4 index3 index2 index1 index0))))

(defun n-stars (n)
  (nthcdr (- 7 n) '(* * * * * * *)))

(defun n-fixnums (n)
  (nthcdr (- 7 n) '(fixnum fixnum fixnum fixnum fixnum fixnum fixnum)))

(defun n-object-nils (n)
  (nthcdr (- 7 n) '((:object nil) (:object nil) (:object nil) (:object nil)
		    (:object nil) (:object nil) (:object nil))))

(defun n-fixnum-nils (n)
  (nthcdr (- 7 n) '((:fixnum nil) (:fixnum nil) (:fixnum nil) (:fixnum nil)
		    (:fixnum nil) (:fixnum nil) (:fixnum nil))))

(defun initialize-array-accessor (name type dtype aggreg rank arity accessor)  
  (let* ((c-name (format nil "~@[~A_~]~A~A~A~A~@[_~D~]"
			 name
			 dtype aggreg rank accessor
			 (when (equal "A" rank)
			   arity)))
	 (write-p (equal accessor "SET"))
	 (foreign-type1 (translator-foreign-type-name
			 (lisp-type->best-foreign-type type)))
	 (foreign-type (if (equal dtype "")
			   :object
			   foreign-type1))
	 (simpleft (eq foreign-type1 foreign-type))
	 (lisp-name (concatenate 'string "%"
				 (substitute #\- #\_ c-name)))
	 (symbol (intern lisp-name :trun))
	 (general (when (and (equal rank "A")
			     (equal dtype "I")
			     (equal aggreg "S"))
		    (intern (format nil "%~:[~;SET-~]AREF-~D"
				    write-p arity)
			    :trun))))
    (export symbol :trun)
    (look-up-symbol-usage lisp-name
			  :package "TRUN"
			  :import-from nil
			  :exists-at-runtime nil)
    (when general
      (let* ((fd (defined-as-function general))
	     (transforms (function-descriptor-transforms fd)))
	(unless (assoc symbol transforms)
	  (setf (function-descriptor-transforms fd)
		(append transforms
			(list (list symbol nil)))))))
    (process-function-usage-common
     symbol
     :state-changing write-p
     :nonconsing (or (equal dtype "I")
		     (let* ((name (if write-p
				      (unboxer foreign-type1)
				      (boxer foreign-type1)))
			    (descr (defined-as-function name)))
		       (and descr
			    (function-descriptor-nonconsing descr))))
     :entry-name c-name
     :lambda-list `(array
		    ,@(n-index-vars arity)
		    ,@(when write-p '(new-value)))
     :return-type type
     :foreign-protocol :macro
     :argument-types `((simple-array ,type
				     ,(n-stars arity))
		       ,@(n-fixnums arity)
		       ,@(when write-p `(,type)))
     :foreign-arguments
     `((:object ,(>= arity 2))
       ,@(if (equal dtype "")
	     (n-object-nils arity)
	     (n-fixnum-nils arity))
       ,@(when write-p `((,foreign-type ,(not simpleft)))))
     :foreign-return-type foreign-type)))

(defun initialize-array-accessors ()
  (dolist (name+type '(("DFLOAT" double-float)
		       ("FLOAT" single-float) ; is single-float right?
		       ("BYTE_8" (signed-byte 8))
		       ("BYTE_16" (signed-byte 16))
		       ("BYTE_32" (signed-byte 32))
		       ("UBYTE_8" (unsigned-byte 8))
		       ("UBYTE_16" (unsigned-byte 16))
		       ("UBYTE_32" (unsigned-byte 32))
		       ("BIT" bit)
		       ("CHAR" base-char) ; maybe tx:string-char?
		       (nil t)))
    (dolist (dtype '("I" ""))		; "" means fixnum args
      (let ((aggreg "S"))		; or "" for a non-simple array
	(dolist (rank+arity '(("V" 1)
			      ("A" 0) ("A" 1) ("A" 2) ("A" 3)
			      ("A" 4) ("A" 5) ("A" 6) ("A" 7)))
	  (dolist (accessor '("REF" "SET"))
	    (let* ((c-name (format nil "~@[~A_~]~A~A~A~A~@[_~D~]"
				   (car name+type)
				   dtype aggreg (car rank+arity) accessor
				   (when (equal "A" (car rank+arity))
				     (cadr rank+arity))))
		   (type (cadr name+type))
		   (arity (cadr rank+arity))
		   (write-p (equal accessor "SET"))
		   (foreign-type1 (translator-foreign-type-name
				   (lisp-type->foreign-type type)))
		   (foreign-type (if (equal dtype "")
				     :object
				     foreign-type1))
		   (simpleft (eq foreign-type1 foreign-type))
		   (lisp-name (concatenate 'string "%"
					   (substitute #\- #\_ c-name)))
		   (symbol (intern lisp-name :trun))
		   (general (when (and (equal (car rank+arity) "A")
				       (equal dtype "I")
				       (equal aggreg "S"))
			      (intern (format nil "%~:[~;SET-~]AREF-~D"
					      write-p arity)
				      :trun))))
	      (export symbol :trun)
	      (look-up-symbol-usage lisp-name
				    :package "TRUN"
				    :import-from nil
				    :exists-at-runtime nil)
	      (when general
		(let* ((fd (defined-as-function general))
		       (transforms (function-descriptor-transforms fd)))
		  (unless (assoc symbol transforms)
		    (setf (function-descriptor-transforms fd)
			  (append transforms
				  (list (list symbol nil)))))))
	      (process-function-usage-common
	       symbol
	       :state-changing write-p
	       :nonconsing (or (equal dtype "I")
			       (let* ((name (if write-p
						(unboxer foreign-type1)
						(boxer foreign-type1)))
				      (descr (defined-as-function name)))
				 (and descr
				      (function-descriptor-nonconsing descr))))
	       :entry-name c-name
	       :lambda-list `(array
			      ,@(n-index-vars arity)
			      ,@(when write-p '(new-value)))
	       :return-type type
	       :foreign-protocol :macro
	       :argument-types `((simple-array ,type
					       ,(n-stars arity))
				 ,@(n-fixnums arity)
				 ,@(when write-p `(,type)))
	       :foreign-arguments
	       `((:object ,(>= arity 2))
		 ,@(if (equal dtype "")
		       (n-object-nils arity)
		       (n-fixnum-nils arity))
		 ,@(when write-p `((,foreign-type ,(not simpleft)))))
	       :foreign-return-type foreign-type))))))))

(defun lisp-type->best-foreign-type (type)
  (lisp-type->foreign-type-cond type
   :signed-8bit
   :unsigned-8bit
   :signed-16bit
   :unsigned-16bit
   :fixnum
   :signed-32bit
   :unsigned-32bit
   :signed-64bit
   :unsigned-64bit
   :double-float
   :character
   ;; :string
   :object))

(initialize-array-accessors)


(dolist (name+type '(("UBYTE_32" (unsigned-byte 32))))
  (dolist (dtype '("I" ""))		; "" means fixnum args
    (let ((aggreg "S"))			; or "" for a non-simple array
      (dolist (rank+arity '(("V" 1)
			    ("A" 0) ("A" 1) ("A" 2) ("A" 3)
			    ("A" 4) ("A" 5) ("A" 6) ("A" 7)))
	(dolist (accessor '("REF" "SET"))
	  (initialize-array-accessor 
	   (car name+type) (cadr name+type) dtype aggreg 
	   (car rank+arity) (cadr rank+arity) accessor))))))




