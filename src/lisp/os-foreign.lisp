;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module OS-FOREIGN

;;; Copyright (c) 1986 - 2017 Gensym Corporation.o`ration.
;;; All Rights Reserved.

;;; John Hodgkinson



;;;; Foreign Functions

;;; N.B.  There is a new foreign struct and function interfacing facility
;;; that is in development.  It's current home is UTILITIES3, due to load-
;;; order problems.  JED 4/17/96

(declare-forward-reference copy-foreign-string-arg-if-appropriate function)
(declare-forward-reference copy-out-alien-string-into-original-string function)
(declare-forward-reference reclaim-sbcl-alien-string function)

;;; Here we have abstractions for interfaces to C functions

#-no-macros
(defun-for-macro native-def-c-foreign-function-name ()
  (feature-case
    (:translator
      (feature-case
        (:chestnut-trans
          (feature-case
            (:chestnut
              (intern "DEF-FOREIGN-FUNCTION" "TRANS"))
            (:chestnut-3
              (intern "DEF-FOREIGN-FUNCTION" "TX")))) ;Chestnut3.1
        (t (signal-missing-translator-facility-function
             'native-def-c-foreign-function-name 'OS-FOREIGN))))
    (:vanilla-unix
      (feature-case
        (:chestnut
         (intern "DEF-FOREIGN-FUNCTION" "TRANS"))
        (:chestnut-3
         (intern "DEF-FOREIGN-FUNCTION" "TX")) ;Chestnut3.1
        (t (signal-missing-vanilla-facility-function
            'native-def-c-foreign-function-name 'OS-FOREIGN))))
    (:lucid
      (intern "DEF-FOREIGN-FUNCTION" "SYSTEM"))
    (:allegro
      (intern "DEF-FOREIGN-FUNCTION" "LCL"))
    (:sbcl
      (error "SBCL does not use the native-def-c-foreign-function-name facilty.  Should not get here."))
    (:clozure
      (error "Clozure CL does not use the native-def-c-foreign-function-name facilty. Should not get here."))
    (t (error "Unknown Lisp."))))

#+(or lucid allegro)
(defun-for-macro c-function-return-types (gensym-type)
  (let ((result?
          (case gensym-type
            ((:fixnum-int :fixnum :fixnum-long)
             '(:fixnum))
            (:void
             '(:fixnum :value))
            (:pointer
             '(:fixnum))
            (:double-float
             '(:double-float))
            (:object
             '(:object))
            ;; jv, 10/17/03: this should be a temporary thing:
            #+gsi-web
            ((:fixnum32)
             '(:signed-32bit)))))
    (values result? (not (null result?)))))


#+sbcl
(defun-for-macro c-function-return-types (gensym-type)
  (let ((result?
          (case gensym-type
            ((:fixnum-int :fixnum :fixnum-long)
             (feature-case
               (:translator
                '(:fixnum))
               (t
                '(sb-alien:long))))
            (:fixnum-long64
             (feature-case
               (:translator
                '(:fixnum))
               (t
                '((sb-alien:signed 64)))))
            (:int64
             (feature-case
               (:translator
                '(:signed-64bit))
               (t
                '((sb-alien:signed 64)))))
            (:void
             (feature-case
               (:translator
                '(:void))
               (t
                '(sb-alien:void))))
            (:pointer
             (feature-case
               (:translator
                '(:fixnum-long))
               (t
                '(sb-alien:long))))
            ((:double-float)
             (feature-case
               (:translator
                '(:double-float))
               (t
                '(double-float))))
            (:object
             (feature-case
               (:translator
                '(:object))
               (t
                '(sb-alien:int))))
            ;; jv, 10/17/03: this should be a temporary thing:
            #+gsi-web
            ((:fixnum32)
             (feature-case
               (:translator
                '(:signed-32bit))
               (t
                '(sb-alien:long)))))))
    (values result? (not (null result?)))))
    
#+clozure
(defun-for-macro c-function-return-types (gensym-type)
  (let ((result?
          (case gensym-type
            ((:fixnum-int :fixnum :fixnum-long)
             (feature-case
               (:translator
                '(:fixnum))
               (t
                '(:signed-fullword))))
            (:fixnum-long64
             (feature-case
               (:translator
                '(:fixnum))
               (t
                '(:signed-doubleword))))
            (:int64
             (feature-case
               (:translator
                '(:signed-64bit))
               (t
                '(:signed-doubleword))))
            (:void
             '(:void))
            (:pointer
             (feature-case
               (:translator
                '(:fixnum-long))
               (t
                '(:signed-fullword))))
            ((:double-float)
             '(:double-float))
            (:object
             (feature-case
               (:translator
                '(:object))
               (t
                '(:address))))
            ;; jv, 10/17/03: this should be a temporary thing:
            #+gsi-web
            ((:fixnum32)
             (feature-case
               (:translator
                '(:signed-32bit))
               (t
                '(:signed-fullword)))))))
    (values result? (not (null result?)))))

#+common-ffi
(defun-for-macro c-function-return-types (gensym-type)
  (let ((result?
          (case gensym-type
            ((:fixnum-int :fixnum :fixnum32)
             (feature-case
               (:translator
                '(:fixnum))
               (t
                '(:long))))
            (:fixnum-long64
             (feature-case
               (:translator
                '(:fixnum))
               (t
                #+(and mswindows x64) '(:int64)
                #-(and mswindows x64) '(:long))))
            ;; TODO: check all low-level C functions, make sure their return type
            ;; is changed from "long" to "SI_Long". --binghe
            (:fixnum-long
             (feature-case
               (:translator
                '(:fixnum))
               (t
                #+(and mswindows x64) '(:int64)
                #-(and mswindows x64) '(:long))))
            (:pointer
             (feature-case
               (:translator
                '(:fixnum-long))
               (t
                '(:long))))
            (:int64
             (feature-case
               (:translator
                '(:signed-64bit))
               (t
                '(:int64))))
            (:void
             (feature-case
               (:translator
                '(:void))
               (t
                '(:void))))
            ((:double-float)
             (feature-case
               (:translator
                '(:double-float))
               (t
                '(:double))))
            (:object
             (feature-case
               (:translator
                '(:object))
               (t
                '(:pointer :void))))
            ;; jv, 10/17/03: this should be a temporary thing:
            #+gsi-web
            ((:fixnum32)
             (feature-case
               (:translator
                '(:signed-32bit))
               (t
                '(:long)))))))
    (values result? (not (null result?)))))

#+(or lucid allegro)
(defun-for-macro c-argument-types (gensym-type)
  (let* ((parameters nil)
         (correctly-specified? t))
    (setq parameters
          (case gensym-type
            ((:fixnum-int :pointer :fixnum32 :fixnum-long)
             '(:fixnum))
            ((:double-float)
             '(:double-float))
            (:array
             '(:array))
            (:string
             (feature-case
               (:translator
                 '(:simple-string))
               (t
                 '(:simple-string :reference))))
            (:string-buffer
             (feature-case
               (:translator
                 '(:string))
               (t
                 '(:string :reference))))
            (:wide-string
             (feature-case
               (:translator
                 '(:16-bit-unsigned-array))
               (t
                 '(:simple-vector-type :reference))))
            ((:variable-fill-icp-buffer :byte-vector-16)
             (feature-case
               (:translator
                 '(:16-bit-unsigned-array))
               (t
                 '((:array :uinteger16)))))
            (:byte-vector
             (feature-case
               (:translator
                 '(:8-bit-unsigned-array))
               (t
                 '((:array :uinteger8)))))
            (:object
             (feature-case
               (:translator
                 '(:object))
               (t
                 '(:pointer))))
            (:double-float-array
             (feature-case
               (:translator
                 '(:double-float-array))
               (t
                 '(:array))))
            (:default
              (feature-case
                (:translator
                  '(:string))
                (t                ; nil is ok!
                  nil)))
            (t
             (setq correctly-specified? nil)
             nil)))
    (values parameters correctly-specified?)))

#+sbcl
(defun-for-macro c-argument-types (gensym-type)
  (let* ((parameters nil)
         (correctly-specified? t))
    (setq parameters
          (case gensym-type
            ((:fixnum-int :fixnum32 :fixnum :fixnum-long)
             (feature-case
               (:translator
                '(:fixnum))
               (t
                '(sb-alien:long))))
            (:fixnum-long64
             (feature-case
               (:translator
                '(:fixnum))
               (t
                '((sb-alien:signed 64)))))
            (:int64
             (feature-case
               (:translator
                '(:signed-64bit))
               (t
                '((sb-alien:signed 64)))))
            (:pointer
             (feature-case
               (:translator
                '(:fixnum-long))
               (t
                '(sb-alien:long))))
            ((:double-float)
             (feature-case
               (:translator
                '(:double-float))
               (t
                '(double-float))))
            (:array
             (feature-case
               (:translator
                '(:array))
               (t
                '(array))))
            ((:string :string-buffer)
             (feature-case
               (:translator
                '(:string))
               (t
                '(sb-alien:c-string))))
            (:wide-string
             (feature-case
               (:translator
                '(:16-bit-unsigned-array))
               (t
                '((sb-alien:* (sb-alien:unsigned 16))))))
            ((:variable-fill-icp-buffer :byte-vector-16)
             (feature-case
               (:translator
                '(:16-bit-unsigned-array))
               (t
                '((sb-alien:* (sb-alien:unsigned 16))))))
            (:byte-vector
             (feature-case
               (:translator
                '(:8-bit-unsigned-array))
               (t
                '((sb-alien:* (sb-alien:unsigned 8))))))
            (:object
             (feature-case
               (:translator
                '(:object))
               (t
                '(sb-alien:int))))
            (:double-float-array
             (feature-case
               (:translator
                '(:double-float-array))
               (t
                '((sb-alien:* double-float)))))
            (:default
             (error "DEFAULT_ERROR")) ;no default values
            (t
             (error "Unknown foreign type: ~A" gensym-type)
             (setq correctly-specified? nil)
             nil)))
    (values parameters correctly-specified?)))

#+clozure
(defun-for-macro c-argument-types (gensym-type)
  (let* ((parameters nil)
         (correctly-specified? t))
    (setq parameters
          (case gensym-type
            ((:fixnum-int :pointer :fixnum32 :fixnum-long)
             (feature-case
               (:translator
                '(:fixnum))
               (t
                '(:signed-fullword))))
            (:fixnum-long64
             (feature-case
               (:translator
                '(:fixnum))
               (t
                '(:signed-doubleword))))
            (:int64
             (feature-case
               (:translator
                '(:signed-64bit))
               (t
                '(:signed-doubleword))))
            ((:double-float)
             '(:double-float))
            (:array
             '(:array))
            ((:string :string-buffer)
             (feature-case
               (:translator
                '(:string))
               (t
                '(:address))))
            (:wide-string
             (feature-case
               (:translator
                '(:16-bit-unsigned-array))
               (t
                '(:address))))
            ((:variable-fill-icp-buffer :byte-vector-16)
             (feature-case
               (:translator
                '(:16-bit-unsigned-array))
               (t
                '(:address))))
            (:byte-vector
             (feature-case
               (:translator
                '(:8-bit-unsigned-array))
               (t
                '(:address))))
            (:object
             (feature-case
               (:translator
                '(:object))
               (t
                '(:address))))
            (:double-float-array
             (feature-case
               (:translator
                '(:double-float-array))
               (t
                '(:address))))
            (:default
             (error "DEFAULT_ERROR")) ;no default values
            (t
             (error "Unknown foreign type: ~A" gensym-type)
             (setq correctly-specified? nil)
             nil)))
    (values parameters correctly-specified?)))

#+common-ffi
(defun-for-macro c-argument-types (gensym-type)
  (let* ((parameters nil)
         (correctly-specified? t))
    (setq parameters
          (case gensym-type
            ((:fixnum-int :fixnum32 :fixnum)
             (feature-case
               (:translator
                '(:fixnum))
               (t
                '(:long))))
            ;; for `c-native-clock-ticks' only, this is a workaround.
            (:fixnum-long64
             (feature-case
               (:translator
                '(:fixnum))
               (t
                #+(and mswindows x64) '(:int64)
                #-(and mswindows x64) '(:long))))
            ;; TODO: check all low-level C functions, make sure their arg types
            ;; are changed from "long" to "SI_Long". --binghe
            (:fixnum-long
             (feature-case
               (:translator
                '(:fixnum))
               (t
                #+(and mswindows x64) '(:int64)
                #-(and mswindows x64) '(:long))))
            (:pointer
             (feature-case
               (:translator
                '(:fixnum-long))
               (t
                '(:long))))
            (:int64
             (feature-case
               (:translator
                '(:signed-64bit))
               (t
                '(:int64))))
            ((:double-float)
             (feature-case
               (:translator
                '(:double-float))
               (t
                '(:double))))
            ((:string :string-buffer)
             (feature-case
               (:translator
                '(:string))
               (t
                '(:pointer))))
            (:wide-string
             (feature-case
               (:translator
                '(:16-bit-unsigned-array))
               (t
                '(:lisp-array))))
            ((:variable-fill-icp-buffer :byte-vector-16)
             (feature-case
               (:translator
                '(:16-bit-unsigned-array))
               (t
                '(:lisp-array))))
            (:byte-vector
             (feature-case
               (:translator
                '(:8-bit-unsigned-array))
               (t
                '(:lisp-array))))
            (:object
             (feature-case
               (:translator
                '(:object))
               (t
                '((:pointer :void)))))
            (:double-float-array
             (feature-case
               (:translator
                '(:double-float-array))
               (t
                '(:lisp-array))))
            (:default
              nil)
            (t
             (error "Unknown foreign type: ~A" gensym-type)
             (setq correctly-specified? nil)
             nil)))
    (values parameters correctly-specified?)))

(defmacro parameter-type (parameter)
  `(first ,parameter))

(defmacro parameter-name (parameter)
  `(second ,parameter))

#-(or lucid sbcl common-ffi allegro clozure)
(defun-for-macro c-function-return-types (gensym-type)
  (declare (ignore gensym-type))
  (error "def-gensym-c-function: unknown Lisp."))

#-(or lucid sbcl common-ffi allegro clozure)
(defun-for-macro c-argument-types (gensym-type)
  (declare (ignore gensym-type))
  (error "def-gensym-c-function: unknown Lisp."))


;;; `all-foreign-functions-in-this-system' - a useful development tool for
;;; generating the list of C functions a system calls from Lisp, which can
;;; be used to generate the exports file for the dll, to help with testing
;;; coverage, or to find a good example to copy when defining a new foreign
;;; function.  -jv, 7/03/07

#+development
(defvar all-foreign-functions-in-this-system '())


;;; `add-foreign-function' - note, this should be included as part of the
;;; macroexpansion of def-gensym-c-function, and not actually executed at
;;; macroexpansion time.  It could be run at macroexpansion time if we were
;;; going to recompile the system every time, but we don't want to have to
;;; do that.  By keeping it part of the result, we make sure that the list
;;; gets built up properly even when just "load"ing the system.

#+development
(defun-for-macro add-foreign-function (lisp-name c-name lisp-return-type
                                                 parameters module)
  (let* ((list-of-value-functions?
           (assoc module all-foreign-functions-in-this-system))
         (this-function (list c-name lisp-return-type lisp-name parameters)))
    (if list-of-value-functions?
        (setf (cdr list-of-value-functions?)
              (cons this-function
                    (cdr list-of-value-functions?)))
        (push (list module this-function)
              all-foreign-functions-in-this-system))))


;;; `map-ff-type-to-c-type'

#+development
(defun map-ff-type-to-c-type (ff-type)
  (case ff-type
    (:void
     "void ")
    (:fixnum-int
     "int ")
    (:fixnum32
     "int ")
    (:fixnum-long
     "SI_Long")
    (:double-float
     "double ")
    (:pointer
     "void *")
    (:object
     "Object ")
    (:string
     "const char *")
    (:string-buffer
     "char *")
    (:wide-string
     "wchar *")
    ((:variable-fill-icp-buffer :byte-vector-16)
     "unsigned *")
    (:byte-vector
     "byte *")
    (:double-float-array
     "double *")
    (t
     (break "unknown fftype ~s" ff-type))))


;;; `show-foreign-functions'

#+development
(defun show-foreign-functions ()
  (loop with *print-case* = :downcase
        with *print-level* = nil
        with *print-length* = nil
        with total-functions = 0
        with return-type-summary = '()
        with argument-type-summary = '()
        for module-group in all-foreign-functions-in-this-system
        as signatures = (cdr module-group)
        do
    (incf total-functions (length signatures))
    (loop for signature in signatures
          as c-name = (car signature)
          as return-value = (cadr signature)
          as lisp-name = (caddr signature)
          as args = (cadddr signature)
          as return-type-count = (assoc return-value return-type-summary)
          do
      (format t "~A~A (" (map-ff-type-to-c-type return-value) lisp-name)
      (if (null return-type-count)
          (push (list return-value 1) return-type-summary)
          (incff (cadr return-type-count)))
      (loop for rest on args
            as arg-ff-type = (caar rest)
            as arg-type-count = (assoc arg-ff-type argument-type-summary)
            do
        (format t "~A~s" (map-ff-type-to-c-type arg-ff-type) (cadar rest))
        (if (null arg-type-count)
            (push (list arg-ff-type 1) argument-type-summary)
            (incff (cadr arg-type-count)))
        (unless (null (cdr rest))
          (format t ", ")))
      (format t ") ;; ~A~%" c-name))
        finally
          (format t "~s~%" argument-type-summary)
          (format t "~s~%" return-type-summary)
          (format t "~d total foreign functions defined.~%" total-functions))
  (values))


;;; `generate-dll-def-file'

#+development
(defun generate-dll-def-file (system-nickname)
  (let ((filename
          (let ((*print-case* :downcase))
            (format nil "~a/xanalys/~axprts.def"
                    source-directory-name system-nickname))))
    (with-open-file (def-file filename :direction :output
                              :if-exists :supersede)
      (format def-file ";;; -*- Mode: Text -*-~%")
      (format def-file "~%")
      (format def-file "LIBRARY ~aLIBS~%" system-nickname)
      (format def-file "EXPORTS~%")
      (loop with *print-case* = :downcase
            for module-group in (reverse all-foreign-functions-in-this-system)
            as signatures = (cdr module-group)
            do
        (format def-file "~%~c;~%~c; ~s.lisp~%~c;~%"
                #\tab #\tab (car module-group) #\tab)
        (loop for signature in signatures do
          (format def-file "~c~A~%" #\tab (car signature)))))
    (values)))




;;; The macro `def-gensym-c-function' and `def-gensym-fortran-function' expand
;;; to the apropriate functions or macros on the various Lisp implementation.
;;;
;;; These generate a Lisp-side function that turns around and calls the c-side
;;; function, possibly with some transformations and overhead dealt with along
;;; the way.
;;;
;;; In particular, the parameter type :string is handled somewhat specially on
;;; the Lisp side [now, as of 12/23/94 (in 4.0 Beta sources)].  Code is
;;; generated to check if the parameter is a legal C string, which in all known
;;; implementations is equivalent to our simple-gensym-string data type.
;;;
;;; If the parameter is a text string or a non-simple gensym string, then a
;;; simple-gensym-string copy of the parameter is passed down to C.  This copy
;;; is reclaimed upon exit from the Lisp side.  A simple gensym string is
;;; simply passed through as is.
;;;
;;; Therefore, in the unusual event that a string needs to be sent to C in order
;;; to have C munge it for side effects, callers must take care to pass in a
;;; simple gensym string in order to ensure that it gets passed down to C intact.
;;;
;;;
;;; An example:
;;;
;;;    (def-gensym-c-function x11-draw-point
;;;      (:void "w_draw_point")
;;;      ((:pointer window-widget)
;;;       (:fixnum-int x)
;;;       (:fixnum-int y)
;;;       (:fixnum-int function))

#+sbcl
(defmacro def-gensym-c-function
    (function-name
      (foreign-function-type foreign-function-name)
      parameters)
  (let* ((complex-types-are-present?
           (or (member :string parameters :key #'car :test #'eq)
               (member :double-float parameters :key #'car :test #'eq)
               (member :double-float-array parameters :key #'car :test #'eq)
               (member :wide-string parameters :key #'car :test #'eq)
               (member :byte-vector-16 parameters :key #'car :test #'eq)
               (member :variable-fill-icp-buffer parameters :key #'car :test #'eq)))
         (c-function-name
           (if complex-types-are-present?
               (build-ab-symbol function-name 'c 'internal)
               function-name)))
    `(progn
       #+development
       (add-foreign-function ',function-name ,foreign-function-name
                             ,foreign-function-type ',parameters ',current-module?)

       (def-gensym-c-function-1 ,c-function-name
           (,foreign-function-type ,foreign-function-name)
         ,parameters)
       ,@(if complex-types-are-present?
             (let* ((defun
                        (if (eq foreign-function-type :void)
                            'defun-void
                            'defun))
                    (args
                      (loop for parameter-spec in parameters
                            collect (parameter-name parameter-spec))))
               (loop with alien-string-arg?
                     with coerced-num-arg?
                     for parameter-spec in parameters
                     as type = (parameter-type parameter-spec)
                     as name = (parameter-name parameter-spec)

                  ;; Handle :string args.
                     if (eq type :string) do
                         (setq alien-string-arg? (gensym))
                       and collect
                       `(,alien-string-arg?
                           (copy-foreign-string-arg-if-appropriate ,name))
                             into c-var-check-bindings
                       and collect
                       `(or ,alien-string-arg? ,name)
                             into c-parameter-list
                       and collect
                       `(when ,alien-string-arg?
                          ,(if (eval-feature :translator)
                               `(reclaim-gensym-string ,alien-string-arg?)
                               `(copy-out-alien-string-into-original-string ,alien-string-arg? ,name)))
                             into string-check-unwindings

                  ;; Handle :double-float arguments by coercing the argument.
                  ;; Maybe this is wrong to do for fixnums (or, y'know, lists
                  ;; or something), but it's reasonable if the argument is a
                  ;; single-float, which it usually is.  Lucid accepted a
                  ;; regular float gracefully; SBCL complains bitterly.
                     else if (eq type :double-float) do
                         (setq coerced-num-arg? (gensym))
                       and collect
                       `(,coerced-num-arg?
                           (coerce ,name 'double-float))
                             into c-var-check-bindings
                       and collect
                       `(or ,coerced-num-arg? ,name)
                             into c-parameter-list
                  ;; We don't do any cleanup with these double-floats.  
                  ;; Does coercion cons?!?!
                  ;; Does something need to be cleaned up?

                  ;; just "copy" any other type of argument into the list

                     else if (and (or (eq type :byte-vector-16)
                                      (eq type :variable-fill-icp-buffer)
                                      (eq type :wide-string))
                                  (not (eval-feature :translator)))
                       do (setq alien-string-arg? (gensym))
                       and collect
                       `(,alien-string-arg?
                           (sb-alien:sap-alien (sb-sys:vector-sap ,name)
                                               (sb-alien:* (sb-alien:unsigned 16))))
                             into c-var-check-bindings
                       and collect nil
                             into string-check-unwindings
                       and collect alien-string-arg?
                             into c-parameter-list

                     else if (and (eq type :double-float-array)
                                  (not (eval-feature :translator)))
                       do (setq alien-string-arg? (gensym))
                       and collect
                       `(,alien-string-arg?
                           (sb-alien:sap-alien (sb-sys:vector-sap ,name)
                                               (sb-alien:* double-float)))
                             into c-var-check-bindings
                       and collect nil
                             into string-check-unwindings
                       and collect alien-string-arg?
                             into c-parameter-list

                     else
                       collect name into c-parameter-list

                     finally
                       (return
                         `((,defun ,function-name ,args
                             (let (,@c-var-check-bindings)
                               (prog1 (,c-function-name ,@c-parameter-list)
                                 ,@string-check-unwindings)))))))))))

#+lucid
(defmacro def-gensym-c-function
    (function-name
      (foreign-function-type foreign-function-name)
      parameters)
  (cond
    ((and (not (eval-feature :translator))
          (eval-feature :vanilla-unix))
     (signal-missing-vanilla-facility-function
       'def-gensym-c-function 'OS-FOREIGN)
     nil)
    (t
     (let* ((string-types-are-present?
              (member :string parameters :key #'car :test #'eq))
            (c-function-name
              (if string-types-are-present?
                  (build-ab-symbol function-name 'c 'internal)
                  function-name)))
       `(progn
          #+development
          (add-foreign-function ',function-name ,foreign-function-name
                                ,foreign-function-type ',parameters ',current-module?)
          (def-gensym-c-function-1 ,c-function-name
              (,foreign-function-type ,foreign-function-name)
            ,parameters)
          ,@(if string-types-are-present?
                (let* ((defun
                           (if (eq foreign-function-type :void)
                               'defun-void
                               'defun))
                       (args
                         (loop for parameter-spec in parameters
                               collect (parameter-name parameter-spec))))
                  (loop with copied-string-arg?
                        for parameter-spec in parameters
                        as type = (parameter-type parameter-spec)
                        as name = (parameter-name parameter-spec)
                        if (eq type :string)
                          do (setq copied-string-arg? (gensym))
                          and collect
                                `(,copied-string-arg?
                                    (copy-foreign-string-arg-if-appropriate
                                      ,name))
                            into string-check-bindings
                          and collect
                                `(or ,copied-string-arg? ,name)
                            into c-parameter-list
                          and collect
                                `(when ,copied-string-arg?
                                   (reclaim-gensym-string ,copied-string-arg?))
                            into string-check-unwindings
                        else collect name
                               into c-parameter-list
                        finally
                          (return
                            `((,defun ,function-name ,args
                                (let (,@string-check-bindings)
                                  (prog1 (,c-function-name ,@c-parameter-list)
                                    ,@string-check-unwindings)))))))))))))

;;  `copy-lispworks-to-gensym-string' copies data from LispWorks string to simple
;; Gensym string. It is used by `c-string-function-body' to convert foreign string
;; returned from C functions to simple Gensym string.
;; Actually it should convert only output string parameters but there is no way to
;; check whether string is output parameter of C function.

#+common-ffi
(defun-for-macro c-string-function-body (function-name parameter-list type-list)
  (let ((recomposed-argument-list
          (loop for parameter in parameter-list
                for type in type-list
                if (eq type :string)
                  collect (gensym)
                else
                  collect parameter)))
    (loop with wrapper = (cons function-name recomposed-argument-list)
          for parameter in parameter-list
          for type in type-list
          as replacement in recomposed-argument-list
          when (eq type :string) do
            (setq wrapper
                  `(fli:with-dynamic-lisp-array-pointer (,replacement ,parameter)
                     (prog1 ,wrapper
                       (copy-out-alien-string-into-original-string ,replacement ,(third parameter)))))
          finally
            (return wrapper))))

#+common-ffi
(defmacro expand-c-function-with-strings (parameters
                                          function-name
                                          c-function-name
                                          foreign-function-type)
  `(loop with copied-string-arg?
         for parameter-spec in ,parameters
         as type = (parameter-type parameter-spec)
         as name = (parameter-name parameter-spec)
         collect name into args
         if (eq type :string)
           do (setq copied-string-arg? (gensym))
           and collect
           `(,copied-string-arg?
               (copy-foreign-string-arg-if-appropriate
                 ,name))
                 into string-check-bindings
           and collect
           `(or ,copied-string-arg? ,name)
                 into c-parameter-list
           and collect type into c-type-list
           and collect
           `(when ,copied-string-arg?
              ,(if (eval-feature :translator)
                   `(reclaim-gensym-string ,copied-string-arg?)))
                 into string-check-unwindings
         ;; non-static array must be wrapped --binghe
         else if (and (not (eval-feature :translator))
                      (eq type :wide-string))
           do (setq copied-string-arg? (gensym))
           and collect
           `(,copied-string-arg? (copy-foreign-byte-vector-16 ,name))
                 into string-check-bindings
           and collect
           `(or ,copied-string-arg? ,name)
                into c-parameter-list
           and collect type into c-type-list
           and collect
           `(when ,copied-string-arg?
              (copy-byte-vector-16-into-original ,copied-string-arg? ,name))
                 into string-check-unwindings
         else collect name
                into c-parameter-list
           and collect type into c-type-list
         finally
           (return
             `(,(if (eq ,foreign-function-type :void)
                    'defun-void
                    'defun) ,,function-name ,args
                (let (,@string-check-bindings)
                  (prog1
                      ,(if (eval-feature :translator)
                           `(,,c-function-name ,@c-parameter-list)
                           (c-string-function-body
                             ,c-function-name c-parameter-list c-type-list))
                    ,@string-check-unwindings))))))

#+common-ffi
(defmacro def-gensym-c-function
    (function-name
      (foreign-function-type foreign-function-name)
      parameters)
  (cond
    ((and (not (eval-feature :translator))
          (eval-feature :vanilla-unix))
     (signal-missing-vanilla-facility-function
       'def-gensym-c-function 'OS-FOREIGN)
     nil)
    (t
     (let* ((complex-types-are-present?
             (or (member :string parameters :key #'car :test #'eq)
                 (and (member :wide-string parameters :key #'car :test #'eq)
                      (not (eval-feature :translator)))))
            (c-function-name
             (if complex-types-are-present?
                 (build-ab-symbol function-name 'c 'internal)
               function-name)))
       `(progn
          #+development
          (add-foreign-function ',function-name ,foreign-function-name
                                ,foreign-function-type ',parameters ',current-module?)
          (def-gensym-c-function-1 ,c-function-name
              (,foreign-function-type ,foreign-function-name)
            ,parameters)
          ,@(if complex-types-are-present?
                `(,(expand-c-function-with-strings
                     parameters function-name c-function-name
                     foreign-function-type))))))))

#+clozure
(defmacro expand-c-function-with-strings (parameters
                                          function-name
                                          c-function-name
                                          foreign-function-type)
  `(loop with copied-string-arg?
         for parameter-spec in ,parameters
         as type = (parameter-type parameter-spec)
         as name = (parameter-name parameter-spec)
         collect name into args
         if (eq type :string)
           do (setq copied-string-arg? (gensym))
           and collect
           `(,copied-string-arg?
             (copy-foreign-string-arg-if-appropriate ,name))
                 into string-check-bindings
           and collect
           `(or ,copied-string-arg? ,name)
                 into c-parameter-list
           and collect
           `(when ,copied-string-arg?
              ,(if (eval-feature :translator)
                   `(reclaim-gensym-string ,copied-string-arg?)
                   `(copy-out-alien-string-into-original-string ,copied-string-arg? ,name)))
                 into string-check-unwindings
         else if (and (or (eq type :byte-vector-16)
                          (eq type :variable-fill-icp-buffer)
                          (eq type :wide-string))
                      (not (eval-feature :translator)))
           do (setq copied-string-arg? (gensym))
           and collect
               `(,copied-string-arg? (copy-foreign-byte-vector-16 ,name))
                 into string-check-bindings
           and collect `(cdr ,copied-string-arg?) into c-parameter-list
           and collect
               `(copy-byte-vector-16-into-original ,copied-string-arg? ,name)
                 into string-check-unwindings
         else collect name
                into c-parameter-list
         finally
           (return
             `(,(if (eq ,foreign-function-type :void)
                    'defun-void
                    'defun) ,,function-name ,args
                (let (,@string-check-bindings)
                  (prog1
                      (,,c-function-name ,@c-parameter-list)
                    ,@string-check-unwindings))))))

#+clozure
(defmacro def-gensym-c-function
    (function-name
      (foreign-function-type foreign-function-name)
      parameters)
  (cond
    ((and (not (eval-feature :translator))
          (eval-feature :vanilla-unix))
     (signal-missing-vanilla-facility-function
       'def-gensym-c-function 'OS-FOREIGN)
     nil)
    (t
     (let* ((complex-types-are-present?
             (or (member :string parameters :key #'car :test #'eq)
                 (member :wide-string parameters :key #'car :test #'eq)
                 (and (member :byte-vector-16 parameters :key #'car :test #'eq)
                      (not (eval-feature :translator)))))
            (c-function-name
              (if complex-types-are-present?
                  (build-ab-symbol function-name 'c 'internal)
                  function-name)))
       `(progn
          #+development
          (add-foreign-function ',function-name ,foreign-function-name
                                ,foreign-function-type ',parameters ',current-module?)
          (def-gensym-c-function-1 ,c-function-name
              (,foreign-function-type ,foreign-function-name)
            ,parameters)
          ,@(if complex-types-are-present?
                `(,(expand-c-function-with-strings
                     parameters function-name c-function-name
                     foreign-function-type))))))))

;; (def-gensym-c-function foo (:void "cfoo") ((:default ptr) (:fixnum-int x)))
;; (def-gensym-c-function foo (:void "cfoo") ((:fixnum-array a)(:fixnum-int x)))
;; (def-gensym-c-function bar (:pointer "cbar") ((:pointer bar-ptr)))
;; (def-gensym-c-function fab (:fixnum-int "cfab")
;;  ((:fixnum-int a)(:fixnum-int b)(:fixnum-int c)(:fixnum-int d)(:fixnum-int e)
;;   (:fixnum-int f)(:fixnum-int g)(:fixnum-int h)(:fixnum-int i)))

;; Simplified this, and made it finally handle non-simple (i.e., non-C) text
;; strings by passing down to C simple (i.e., real C) text strings.  It had been
;; handling non-simple strings (i.e., fill-pointered strings) by null-
;; terminating them.  But that was not adequate: C can't be expected deal with
;; a fill pointer.
;;
;; I reviewed callers prior to this change, and did not find any that needed to
;; pass a string to C for side effects.  Most of the callers did seem to be in
;; streams.  About half the callers were explicitly doing what's now automatic;
;; the other half were subject to bugs: e.g., you could definitely bomb out at
;; least under lucid by simply trying to save a KB with a file name longer than
;; about 100 characters.  (MHD 12/23/94)
;;
;; (array-has-fill-pointer-p (the string ,name)) above should be equivalent to
;; (not (simple-gensym-string-p ,name)), which cannot be used here due to macro
;; forward referencing difficulties.  (MHD 1/3/94)

#+sbcl
(defmacro def-gensym-c-function-1 (function-name (foreign-function-type foreign-function-name) parameters)
  (loop with return-type = (first (c-function-return-types foreign-function-type))
        with parameter-type-list = `() ;SS_ERROR: added =
        with native-parameter-list = '()
        with just-args = '()
        with alien-name = (intern (format nil "~a-ALIEN" function-name))
        for parameter in parameters
        do
    (setq parameter-type-list (c-argument-types (parameter-type parameter)))
    (push (if (eq (car parameter-type-list) :default)
              (parameter-name parameter)
              `(,(parameter-name parameter) ,@parameter-type-list))
          native-parameter-list)
    (push (parameter-name parameter) just-args)
        finally
          (setq just-args (nreverse just-args))
          (return
              (if (eval-feature :translator)
                  `(,(native-def-c-foreign-function-name)
                     (,function-name
                      (:language :c)
                      (:name ,foreign-function-name)
                      (:return-type
                       ,(first (c-function-return-types
                                foreign-function-type))))
                     ,@(nreverse native-parameter-list))
                  `(progn
                     (declaim (inline ,alien-name))
                     (sb-alien:define-alien-routine (,(format nil "~a" foreign-function-name)
                                                     ,alien-name)
                         ,return-type
                       ,@(nreverse native-parameter-list))

                     (defun ,function-name (,@just-args)
                       (declare (inline ,alien-name))
                       ,(if (eq return-type 'sb-alien:void)
                            `(,alien-name ,@just-args)
                            `(sb-alien:with-alien
                                 ((res ,return-type
                                       (,alien-name ,@just-args)))
                               res))))))))

;;; Clozure CL
 
#+clozure
(defmacro def-gensym-c-function-1 (function-name (foreign-function-type foreign-function-name) parameters)
  (loop with parameter-type-list
        with native-parameter-list = nil
        with just-args = nil
        for parameter in parameters
        do
    (setq parameter-type-list
          (c-argument-types (parameter-type parameter)))
    (push (if (eq (car parameter-type-list) :default)
              (parameter-name parameter)
            `(,(parameter-name parameter) ,@parameter-type-list))
          native-parameter-list)
    (push (parameter-name parameter) just-args)

        finally
          (return
             (if (eval-feature :translator)
                 `(,(native-def-c-foreign-function-name)
                   (,function-name
                     (:language :c)
                     (:name ,foreign-function-name)
                     (:return-type ,@(c-function-return-types foreign-function-type)))
                   ,@(nreverse native-parameter-list))
               ;; or called directly in CCL
               `(defun ,function-name ,(nreverse just-args)
                  (ccl:external-call ,foreign-function-name
                                     ,@(mapcan #'reverse
                                               (nreverse native-parameter-list))
                                     ,@(c-function-return-types foreign-function-type)))))))

#+lucid
(defmacro def-gensym-c-function-1
    (function-name (foreign-function-type foreign-function-name)
                   parameters)

  (check-def-gensym-function 'c function-name
                             foreign-function-type
                             foreign-function-name parameters)
     (loop with parameter-type-list
           with native-parameter-list = nil
           for parameter in parameters
           do
       (setq parameter-type-list
             (c-argument-types (parameter-type parameter)))
       (push (if (eq (car parameter-type-list) :default)
                 (parameter-name parameter)
                 `(,(parameter-name parameter) ,@parameter-type-list))
             native-parameter-list)
           finally
             (return `(,(native-def-c-foreign-function-name)
                        (,function-name
                           (:language :c)
                           (:name ,foreign-function-name)
                           (:return-type
                             ,(first (c-function-return-types
                                       foreign-function-type))))

                        ,@(nreverse native-parameter-list)))))

;;; LispWorks

#+common-ffi
(defmacro def-gensym-c-function-1
          (function-name
           (foreign-function-type foreign-function-name)
           parameters)
  (check-def-gensym-function
   'c function-name
   foreign-function-type
   foreign-function-name parameters)
  (loop with parameter-type-list
        with native-parameter-list = nil
        with just-args = nil
        for parameter in parameters
        do
    (setq parameter-type-list
          (c-argument-types (parameter-type parameter)))
    (push (if (eq (car parameter-type-list) :default)
              (parameter-name parameter)
            `(,(parameter-name parameter) ,@parameter-type-list))
          native-parameter-list)
    (push (parameter-name parameter) just-args)

        finally
          (return
             (if (eval-feature :translator)
                 `(,(native-def-c-foreign-function-name)
                   (,function-name
                     (:language :c)
                     (:name ,foreign-function-name)
                     (:return-type ,@(c-function-return-types foreign-function-type)))
                   ,@(nreverse native-parameter-list))
               
                 `(fli:define-foreign-function
                      (,function-name ,foreign-function-name)
                      ,(loop for parameter in (reverse native-parameter-list)
                             as parameter-name = (first parameter)
                             as parameter-type-list
                             = (second parameter)
                             as native-parameter
                             = `(,parameter-name ,parameter-type-list)
                             collect native-parameter)
                    :result-type ,(first (c-function-return-types foreign-function-type))
                    :language :ansi-c)))))

(defun-for-macro gensym-argument-types (gensym-type)
  (c-argument-types gensym-type))

(defun-for-macro gensym-function-return-types (gensym-type)
  (c-function-return-types gensym-type))





;;; The function `check-def-gensym-function' checks to see if the arguments
;;; for def-gensym-function are correct.

(defun-for-macro check-def-gensym-function
    (def-function-type
        function-name
        foreign-function-type
      foreign-function-name
      parameters)
  (let* (def-function-name)
    (case def-function-type
      (c (setq def-function-name "def-gensym-c-function")))

    (if (not (symbolp function-name))
        (warn "For ~s, function-name should be a symbol, not ~s."
              def-function-name function-name))

    (multiple-value-bind (parameters return-type-correctly-specified?)
        (gensym-function-return-types foreign-function-type)
      (declare (ignore parameters))
      (if (not return-type-correctly-specified?)
          (warn "For ~s, foreign-function-type should not be ~s."
                def-function-name
                foreign-function-type)))

    (if (not (stringp foreign-function-name))
        (warn "For ~s, foreign-function-name should be a symbol, not ~s."
              def-function-name foreign-function-name))

    (if (not (listp parameters))
        (warn "For ~s, paramters should be a list of parameters, and not ~s."
              def-function-name parameters))

    (dolist (parameter parameters)
      (if (or (not (listp parameter))
              (/= (length parameter) 2))
          (warn "For ~s, the parameter ~s should be a list of ~
                  two elements, the argument type and the argument name."
                def-function-name parameter)
          (multiple-value-bind (parameters correctly-specified?)
              (gensym-argument-types (parameter-type parameter))
            (declare (ignore parameters))
            (if (or (not (symbolp (parameter-type parameter)))
                    (not correctly-specified?))
                (warn "For ~s, the parameter-type for ~s should not be ~s."
                      def-function-name parameter (parameter-type parameter))
                (if (not (symbolp (parameter-name parameter)))
                    (warn "For ~s, the parameter name for ~s should be a ~
                           symbol, not ~s."
                          def-function-name
                          parameter
                          (parameter-name parameter)))))))))








;;;; Interface to Foreign Strings

;;; `Gensym-environment-variable-buffer' is a simple Gensym string, 1023 in
;;; length, used for the purpose of absorbing the environment variable
;;; information.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defparameter maximum-gensym-environment-variable-length 1023))

(defvar gensym-environment-variable-buffer
  (make-static-string #.maximum-gensym-environment-variable-length))

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defparameter gensym-environment-variable-success 0)
  (defparameter gensym-environment-variable-failure -1))

;; This uses make-string to create the string simply because it's too early in
;; the load process to use obtain-gensym-string.

;; jh, 9/10/91.  Removed the with-unmoveable-object-creation wrapper from the
;; variable gensym-environment-variable-buffer.  This wrapper is only necessary
;; when we intend to pass a pointer to a C asynchronous process and then resume
;; Lisp processing, thereby creating the risk that the pointer will be relocated
;; by garbage collection.  There is no such risk for
;; gensym-environment-variable-buffer, since it is never passed to an asynchronous
;; C process, but is always used to contain the result of a C function call.




;; Note that int-char is obsolete, so we must use code-char to define
;; null-character-for-c-strings.  CLtL/2e p 64 claims that with the removal of
;; int-char, it is impossible to *coerce* an integer to a character, but the
;; subtle point remains that it is still possible to *convert* an integer to a
;; character.  jh, 1/16/91.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defconstant null-character-for-c-strings (code-char 0)))

(defmacro interface-to-foreign-environment-access
    (result-code
      &key (success-code gensym-environment-variable-success)
           (failure-code gensym-environment-variable-failure))
  `(case ,result-code
     (,success-code
      (copy-null-terminated-string-as-text-string
        gensym-environment-variable-buffer)
      ;; The previous code replaces the following more or less original code
      ;; with the exact same functionality, except that if there were no null
      ;; byte at all in the string, the new code would return a string
      ;; maximum-gensym-environment-variable-length long with the contents of
      ;; the buffer, whereas the old code would return a zero-length string.
      ;; However, I don't believe that the zero case should be able to happen,
      ;; that is, unless there is an error somewhere else, such as having too
      ;; low a value for maximum-gensym-environment-variable-length. (MHD
      ;; 2/16/96)
;      (let* ((variable-length
;               (or (loop for i from 0
;                               below maximum-gensym-environment-variable-length
;                         for this-char
;                           = (schar gensym-environment-variable-buffer i)
;                         when (char= this-char null-character-for-c-strings)
;                           do (return i))
;                   0))
;             (variable
;               (obtain-text-string variable-length)))
;        (copy-portion-of-string-into-text-string
;          gensym-environment-variable-buffer
;          0
;          variable-length
;          variable
;          0)
;        variable)
      )
   (,failure-code
    nil)))

(defmacro interface-to-foreign-environment-access-before-gensym-string-pool
    (result-code)
  `(case ,result-code
     (#.gensym-environment-variable-success
      (let* ((variable-length
               (or (loop for i from 0
                               below maximum-gensym-environment-variable-length
                         for this-char
                             = (schar gensym-environment-variable-buffer i)
                         when (char= this-char null-character-for-c-strings)
                           do (return i))
                   0))
             (variable
               (make-string variable-length)))
        (copy-portion-of-string-into-gensym-string
          gensym-environment-variable-buffer
          0
          variable-length
          variable
          0)
        variable)
      )
     (#.gensym-environment-variable-failure
      nil)))

;; Eliminate this if possible -- always use the version above! (MHD 2/16/96)

;; A call to avoiding-variable-capture was removed from the macro above, since
;; that macro is not yet defined.  Also, the macro above will never need to have
;; an argument value rebound, since the argument to the macro is evaluated for
;; value once, and never referenced again.  -jra 1/15/91




;;; `unsafe-flatten' is useful in the code below.

#+development
(defun-for-macro unsafe-flatten (list);; conses!!!
  (loop for x in list if (consp x) append (unsafe-flatten x) else collect x))


;;; `*all-foreign-callbacks*' - holds information about functions defined by
;;; def-lisp-api-function

#+development
(defvar *all-foreign-callbacks* nil)


;;; `add-foreign-callback' just accumulates information into the global variable
;;; *all-foreign-callbacks*.

#+development
(defun-for-macro add-foreign-callback (name-and-options argument-specs)
  (push (list (car name-and-options)
              (getf (cdr (unsafe-flatten name-and-options)) :return-type)
              argument-specs)
        *all-foreign-callbacks*))


;;; `write-callbacks-preamble' just writes the comment header and other
;;; preliminary stuff for the twcallbacks.c file.  Needs to be modified
;;; to handle generating the file for G2 or GSI.

#+development
(defun write-callbacks-preamble (str)
  (format str "/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++~%")
  (format str " +~%")
  (format str " + Module:      xanalys/twcallbacks.c~%")
  (format str " +~%")
  (format str " + Copyright (c) 1986 - 2017 Gensym Corporation.~%")
  (format str " +            All Rights Reserved.~%")
  (format str " +~%")
  (format str " + Author(s):   Carl Shapiro, John Valente~%")
  (format str " +~%")
  (format str " + Description: This module contains the glue code used to allow our C libraries~%")
  (format str " +              call into Lispworks~%")
  (format str " +~%")
  (format str " +~%")
  (format str " + Dependencies:~%")
  (format str " +      Depends on the Lisp files which define the actual functions~%")
  (format str " +~%")
  (format str " + Notes:~%")
  (format str " +~%")
  (format str " + Modifications:~%")
  (format str " +   2001/10/17, css: added ext/c/callbacks.c to LISPWORKS_BRANCH~%")
  (format str " +     (jv writing comment)~%")
  (format str " +   2007/06/27, jv: took old callbacks.c file, included <windows.h>, added~%")
  (format str " +      DllMain(), unfortunately added main(), moved the file into the xanalys~%")
  (format str " +      directory, and renamed it to include tw.  We will presumably have~%")
  (format str " +      different callbacks for different systems.~%")
  (format str " +~%")
  (format str " +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/~%")
  (format str "~%")
  (format str "#include <stdio.h>~%~%")
  (format str "#ifdef WIN32~%")
  (format str "#  include <windows.h>~%")
  (format str "#  define DLLEXPORT __declspec( dllexport )~%")
  (format str "~%")
  (format str "/* This is the one Lisp *variable* depended on by C.  I haven't figured out~%")
  (format str " * how to export it.  For now, it will always be zero.  Fortunately, its use~%")
  (format str " * by TW is very limited.  I'll figure out how to export it properly before~%")
  (format str " * too long.  -jv, 7/27/07~%")
  (format str " */~%")
  (format str "int Inside_handle_event = 0;~%")
  (format str "#else~%")
  (format str "#  define DLLEXPORT~%")
  (format str "#endif~%~%")
  (format str "#ifdef WIN32~%")
  (format str "BOOL WINAPI DllMain(HANDLE hInstance, DWORD dwReason, LPVOID lpvReserved)~%")
  (format str "{~%")
  (format str "  switch (dwReason)~%")
  (format str "    {~%")
  (format str "    case DLL_PROCESS_ATTACH:~%")
  (format str "    case DLL_THREAD_ATTACH:~%")
  (format str "    case DLL_PROCESS_DETACH:~%")
  (format str "    case DLL_THREAD_DETACH:~%")
  (format str "      return TRUE;~%~%")
  (format str "    default:~%")
  (format str "      return FALSE;~%")
  (format str "    }~%")
  (format str "}~%~%~%")
  (format str "/* This should not be necessary, but g2ext_app_run() in msmain.c calls it.~%")
  (format str " * We want to be able to use the standard libraries as built for the C exe,~%")
  (format str " * packaged into a DLL, in Lisp.  So we need to stub this out.  There's nothing~%")
  (format str " * wrong with having a stub at the point where we essentially start up Chestnut,~%")
  (format str " * but it's unfortunate that the stub has to be called \"main\".  Perhaps~%")
  (format str " * g2ext_app_run (which does nothing but call main) could be moved out of~%")
  (format str " * libcprim, and *that* could be the function we stub out.  -jv, 7/03/07~%")
  (format str " */~%")
  (format str "int main (int argc, char **argv)~%")
  (format str "{~%")
  (format str "  return 0L;~%")
  (format str "}~%")
  (format str "#endif~%"))


;;; `lisp-to-c-symbol' - versions of this code obviously exist elsewhere, but
;;; it's useful to have it as a simple standalone function here

#+development ;SS_ERROR: commented
(defun lisp-to-c-symbol (lisp-name)
  (intern
    (substitute #\_ #\-
                (symbol-name lisp-name))))


;;; `map-lisp-return-type-to-c-type' - the mapping of values Lisp returns to C.
;;; That is, if Lisp expects to send a :fixnum, C should be expecting a long.

#+development ;SS_ERROR: commented
(defun map-lisp-return-type-to-c-type (ff-type)
  (case ff-type
    (:fixnum
     "long")
    (t
     (break "unknown type for Lisp to return to C: ~s" ff-type))))


;;; `map-lisp-var-type-to-c-type' - the mapping of values Lisp expects to
;;; receive from C as arguments.  This is identical to the above function,
;;; map-lisp-return-type-to-c-type, and probably should remain so.  They
;;; could be combined, but I'm making them separate functions "just in case".
;;; Maybe we will want to support certain types for one and not the other,
;;; or even map them differently.  -jv, 12/18/07

#+development ;SS_ERROR commented
(defun map-lisp-var-type-to-c-type (ff-type)
  (case ff-type
    ((or :fixnum #+sbcl sb-alien:int)
     "long")
    (t
     (break "unknown type for argument to Lisp function called from C: ~s" ff-type))))


;;; `write-non-generated-callbacks' - should be eliminated.  These should be
;;; handled the same way as the others, but unfortunately do not go through
;;; def-lisp-api-function.

#+development
(defun write-non-generated-callbacks (str)
  (generate-c-code-for-lisp-api-function
    str 'g2int-x-error :fixnum '((error-code :fixnum)))
  (generate-c-code-for-lisp-api-function
    str 'g2int-service-sigalrm-signal :fixnum '())
  (generate-c-code-for-lisp-api-function
    str 'g2int-signal-handler :fixnum '())
  (generate-c-code-for-lisp-api-function
    str 'g2int-signal-handler-for-launch :fixnum '())
  (format str "~%"))


;;; `generate-c-code-for-lisp-api-function', in the #+lucid case, just produces stubs

#+(and lucid development)
(defun generate-c-code-for-lisp-api-function (str lisp-name return-type args)
  (let* ((c-name (lisp-to-c-symbol lisp-name))
         (c-return-type (map-lisp-return-type-to-c-type return-type))
         (*print-case* :downcase))
    (format str "~%~%/*~%")
    (let ((*print-case* :upcase))
      (format str " * ~s~%*/~%" lisp-name))
    (format str "~A ~s(" c-return-type c-name)
    (loop for rest on args do
      (format str "~A ~s"
              (map-lisp-var-type-to-c-type (cadar rest))
              (lisp-to-c-symbol (caar rest)))
      (unless (null (cdr rest))
        (format str ", ")))
    (format str ")~%{~%  fprintf(stderr, \"calling ~s(" c-name)
    (loop for rest on args do
      (format str "%d")
      (unless (null (cdr rest))
        (format str ", ")))
    (format str")\\n\"")
    (loop for rest on args do
      (format str ", ~s" (lisp-to-c-symbol (caar rest))))
    (format str");~%  return")
    (unless (eq 'void c-return-type)
      (format str "(0L)"))
    (format str ";~%}~%"))
  (values))

;(defun our-lisp-alien-coded (x y) (+ x y))

;;; `generate-c-code-for-lisp-api-function' in the #+sbcl case produces code
;;; which was tested and worked in Lispworks.

#+(and sbcl development)
(defun generate-c-code-for-lisp-api-function (str lisp-name return-type args)
  (let* ((c-name (lisp-to-c-symbol lisp-name))
         (c-return-type (map-lisp-return-type-to-c-type return-type))
         (init-handle-name (intern (format nil "~s_INIT_CALL_HANDLE" c-name)))
         (handle-name (intern (format nil "~s_CALL_HANDLE" c-name)))
         (*print-case* :downcase))
    (format str "~%/*~%")
    (let ((*print-case* :upcase))
      (format str " * ~s~%" lisp-name))
    (format str " */~%static ~A (*~s)("
            c-return-type
            handle-name)
    (loop for rest on args do
      (format str "~A" (map-lisp-var-type-to-c-type (cadar rest)))
      (unless (null (cdr rest))
        (format str ", ")))
    (format str ");~%~%DLLEXPORT void ~s (~A (*fn)("
            init-handle-name
            c-return-type)
    (loop for rest on args do
      (format str "~A" (map-lisp-var-type-to-c-type (cadar rest)))
      (unless (null (cdr rest))
        (format str ", ")))
    (format str "))~%{~%  ~s = fn;~%}~%~%~A ~s("
            handle-name c-return-type c-name)
    (loop for rest on args do
      (format str "~A ~s"
              (map-lisp-var-type-to-c-type (cadar rest))
              (lisp-to-c-symbol (caar rest)))
      (unless (null (cdr rest))
        (format str ", ")))
    (format str ")~%{~%  if (~s) {~%    return" handle-name)
    (unless (eq 'void c-return-type)
      (format str " (*~s)(" handle-name)
      (loop for rest on args do
        (format str "~s" (lisp-to-c-symbol (caar rest)))
        (unless (null (cdr rest))
          (format str ", ")))
      (format str ")"))
    (format str ";~%  } else {~%    fprintf(stderr, \"~s is still unbound\\n\");~%    return"
            handle-name)
    (unless (eq 'void c-return-type)
      (format str " -1L"))
    (format str ";~%  }~%}~%"))
  (values))


;;; `generate-callbacks-file' can be used inside #+development to produce the
;;; ${SRCBOX}/xanalys/*callbacks.c file that defines the C-to-Lisp interface.

#+development
(defun generate-callbacks-file (system-nickname)
  (let ((filename
          (let ((*print-case* :downcase))
            (format nil "~a/xanalys/~acallbacks.c"
                    source-directory-name system-nickname))))
    (with-open-file (cb-file filename :direction :output
                             :if-exists :supersede)
      (write-callbacks-preamble cb-file)
      (write-non-generated-callbacks cb-file)
      (loop for (lisp-name return-type parameters)
                in (reverse *all-foreign-callbacks*)
            do
        (generate-c-code-for-lisp-api-function
          cb-file lisp-name return-type parameters))))
  (values))


;;; `sbcl-argument-specs'

#+sbcl
(defun-for-macro sbcl-argument-specs (argument-specs)
  (loop for (var-name var-type) in argument-specs
    collect (list var-name (car (c-function-return-types var-type)))))


;;; The macro `def-lisp-api-function' defines a LISP function which can be
;;; called back from C code.  Intended to be used at run time in distribution
;;; G2s.  The name "lisp-api-function" is slightly misleading, as this is not
;;; really an API, but nevertheless these functions form the interface which
;;; allows C to call into Lisp.

(defmacro def-lisp-api-function (name-and-options argument-specs &body body)
  `(progn
     #+development
     (add-foreign-callback ',name-and-options ',argument-specs)

     ,(if (eval-feature :translator)
          (with-package-specific-symbols (tx |::| def-foreign-callable)
            `(def-foreign-callable ,name-and-options ,argument-specs
                                   ,@body))
        #+lucid
        `(lcl:def-foreign-callable ,name-and-options ,argument-specs ,@body)

        #+allegro
        `(foreign-functions:defun-foreign-callable
             ,(car name-and-options)
             ,(loop for (var-name nil) in argument-specs collect var-name)
           ,@body)

        #+clozure
        nil

        #+sbcl
        `(sb-alien::define-alien-callback ,(car name-and-options)
             ,(car (c-function-return-types
                    (cadr (assoc :return-type (cdr name-and-options)))))
             ,(sbcl-argument-specs argument-specs)
           ,@body))))

;;; `load-foreign-libraries'

(defun-void load-foreign-libraries (libraries)
  (when libraries
    (format t "~&;;; Loading foreign libraries: ~{~A ~}~%" libraries)
    ;; if there are unresolved symbols, we probably want to see all of them...
    ;; at least, more than a few.  Try 1000.  -jv, 11/18/02
    #-chestnut-trans
    (let ((*print-length* 1000))
      #+lucid
      (lcl::load-foreign-libraries nil libraries)
      #+allegro
      (loop for library in libraries do (load library))
      #+sbcl
      (loop for library in libraries do (sb-alien:load-shared-object library))
      #+clozure
      (loop for library in libraries do (ccl:open-shared-library library))
      #-(or lucid allegro sbcl clozure)
      (error "load-foreign-libraries: unknown lisp"))))

#+development
(defun load-foreign-library (library)
  (load-foreign-libraries (list library))
  (values))

;;; `load-foreign-libraries-for-ab-when-appropriate' is invoked at load time in
;;; Lucid to give Lucid another oportunity to find implementations for various
;;; foriegn functions.  It should be called, at least, once after the last
;;; definition of a foreign C function.  It must also be called prior to the
;;; first use of a such a function.

;;; This is the only place that knows the libarary required by a Lucid image.

(defun-for-macro formatted-ssl-libraries (system?)
  (list (format nil "~a~a"
                (local-platform-specific-directory system?)
                gensym-ssl-library)
        (format nil "~a~a"
                (local-platform-specific-directory system?)
                gensym-crypto-library)
        (format nil "~a~a"
                (local-platform-specific-directory system?)
                gensym-gcc-library)))

#+lucid
(defun-for-macro body-of-load-foreign-libraries-for-ab-when-appropriate
    (error-if-current-system-being-loaded-is-unbound-p)
  `(let* ((system?
           (if (boundp 'current-system-being-loaded)
               current-system-being-loaded))
          (libraries
            (cond
              ((eq system? 'gsi)
               (append
                 (list (format nil "~a~a"
                               (local-cprim-lib-directory system?)
                               gensym-networking-library)
                       (format nil "~a~a"
                               (local-cprim-lib-directory system?)
                               gensym-ssl-stub-library)
                       ;; Libnet always comes from the cprim library.  -jra, 4/21/94
                       #+gsi-web
                       (format nil "~a~a"
                               (local-weblink-lib-directory current-system-being-loaded)
                               gensym-gw-library))
                 (list "-lm" "-lc")))
              ((boundp 'current-system-being-loaded)
               (let ((common-tw-g2-libraries
                       (append
                         (list (format nil "~a~a"
                                       (local-jpeg-lib-directory system?)
                                       gensym-jpeg-library)
                               (format nil "~a~a"
                                       (local-cprim-lib-directory system?)
                                       gensym-cprim-library)
                               (format nil "~a~a"
                                       (local-fontrip-lib-directory system?)
                                       gensym-fnt-library))
                         (formatted-ssl-libraries system?)
                         #-allegro
                         (list "-lX11" "-lm" "-lc")
                         #+(and (not allegro) solaris)
                         (list "-ldl" "-lsocket" "-lintl" "-lnsl"))))
                 (if (eq system? 'telewindows)
                     common-tw-g2-libraries
                     (append common-tw-g2-libraries
                             (list (format nil "~a~a"
                                           (local-xml-lib-directory system?)
                                           gensym-xml-library)
                                   (format nil "~a~a"
                                           (local-platform-specific-directory
                                             system?)
                                           gensym-libxml2-library)
                                   )))))
              (t
               ,(if error-if-current-system-being-loaded-is-unbound-p
                    `(error
                       "LOAD-FOREIGN-LIBRARIES-FOR-AB-WHEN-APPROPRIATE: ~
                        can't find valid system name in &optional argument ~
                        or in current-system-being-loaded")
                    nil))))
          #+(and lucid solaris)
          (lcl::*default-library-directories*
            (append lcl::*default-library-directories* '("/usr/local/X11R6.1/lib"
                                                        "/usr/openwin/lib"))))
     (load-foreign-libraries libraries)))


#+allegro
(defun-for-macro body-of-load-foreign-libraries-for-ab-when-appropriate
    (error-if-current-system-being-loaded-is-unbound-p)
  `(let* ((system?
           (if (boundp 'current-system-being-loaded)
               current-system-being-loaded))
          (libraries
            (cond
              ((eq system? 'gsi)
               (cerror "Go on, loading nothing"
                       "Allegro libraries not available for GSI")
               nil)
              ((eq system? 'ab)
               (cerror "Go on, loading nothing"
                       "Allegro libraries not available for G2")
               nil)
              ((memq system? '(ctest telewindows))
               (list
                (format nil "~a~a"
                        (local-shared-object-directory system?)
                        gensym-tw-library)))
              (t
               ,(if error-if-current-system-being-loaded-is-unbound-p
                    `(error
                       "LOAD-FOREIGN-LIBRARIES-FOR-AB-WHEN-APPROPRIATE: ~
                        can't find valid system name in &optional argument ~
                        or in current-system-being-loaded")
                    nil)))))

     (load-foreign-libraries libraries)))

#+lispworks
(defun-for-macro body-of-load-foreign-libraries-for-ab-when-appropriate
    (error-if-current-system-being-loaded-is-unbound-p)
  `(let* ((system?
           (if (boundp 'current-system-being-loaded)
               current-system-being-loaded
               'ab))
          (library
           (cond ((eq system? 'telewindows)
                  (format nil "~a~a"
                          (local-shared-object-directory system?)
                          gensym-tw-library))
                 ((eq system? 'ab)
                  (format nil "~a~a"
                          (local-shared-object-directory system?)
                          gensym-g2-library))
                 ((eq system? 'gsi)
                  (format nil "~a~a"
                          (local-shared-object-directory system?)
                          gensym-gsi-library))
                 ((eq system? 'ctest)
                  ;; use the TW library for the "ctest" system
                  (format nil "~a~a"
                          (local-shared-object-directory system?)
                          gensym-tw-library))
                 ((boundp 'current-system-being-loaded)
                  (error
                   "LOAD-FOREIGN-LIBRARIES-FOR-AB-WHEN-APPROPRIATE: ~
                 unrecognized current-system-being-loaded: ~s"
                   current-system-being-loaded)
                  nil)
                 (t
                  ,(if error-if-current-system-being-loaded-is-unbound-p
                       `(error
                         "LOAD-FOREIGN-LIBRARIES-FOR-AB-WHEN-APPROPRIATE: ~
                        can't find valid system name in &optional argument ~
                        or in current-system-being-loaded")
                nil)))))
     #+mswindows
     (fli:register-module :msvcrt-dll :connection-style :automatic :real-name "MSVCRT.DLL")
     (fli:register-module :ext-dll :connection-style #+development :immediate #-development :automatic :real-name library)))

#+sbcl
(defun-for-macro body-of-load-foreign-libraries-for-ab-when-appropriate
  (error-if-current-system-being-loaded-is-unbound-p)
  `(let* ((system?
           (if (boundp 'current-system-being-loaded)
               current-system-being-loaded))
          (library
           (cond
            ((eq system? 'telewindows)
             (format nil "~a~a"
                     (local-shared-object-directory system?)
                     gensym-tw-library))
            ((eq system? 'ab)
             (format nil "~a~a"
                     (local-shared-object-directory system?)
                     gensym-g2-library))
            ((eq system? 'gsi)
             (format nil "~a~a"
                     (local-shared-object-directory system?)
                     gensym-gsi-library))
            ((eq system? 'ctest)
             ;; use the TW library for the "ctest" system
             (format nil "~a~a"
                     (local-shared-object-directory system?)
                     gensym-tw-library))
            ((boundp 'current-system-being-loaded)
             (error
              "LOAD-FOREIGN-LIBRARIES-FOR-AB-WHEN-APPROPRIATE: ~
                 unrecognized current-system-being-loaded: ~s"
              current-system-being-loaded)
             nil)
            (t
             ,(if error-if-current-system-being-loaded-is-unbound-p
                  `(error
                    "LOAD-FOREIGN-LIBRARIES-FOR-AB-WHEN-APPROPRIATE: ~
                        can't find valid system name in &optional argument ~
                        or in current-system-being-loaded")
                nil)))))
     (when library
       (load-foreign-libraries (list library)))))

#+clozure
(defun-for-macro body-of-load-foreign-libraries-for-ab-when-appropriate
  (error-if-current-system-being-loaded-is-unbound-p)
  `(let* ((system?
           (if (boundp 'current-system-being-loaded)
               current-system-being-loaded))
          (library
           (cond
            ((eq system? 'telewindows)
             (format nil "~a~a"
                     (local-shared-object-directory system?)
                     gensym-tw-library))
            ((eq system? 'ab)
             (format nil "~a~a"
                     (local-shared-object-directory system?)
                     gensym-g2-library))
            ((eq system? 'gsi)
             (format nil "~a~a"
                     (local-shared-object-directory system?)
                     gensym-gsi-library))
            ((eq system? 'ctest)
             ;; use the TW library for the "ctest" system
             (format nil "~a~a"
                     (local-shared-object-directory system?)
                     gensym-tw-library))
            ((boundp 'current-system-being-loaded)
             (error
              "LOAD-FOREIGN-LIBRARIES-FOR-AB-WHEN-APPROPRIATE: ~
                 unrecognized current-system-being-loaded: ~s"
              current-system-being-loaded)
             nil)
            (t
             ,(if error-if-current-system-being-loaded-is-unbound-p
                  `(error
                    "LOAD-FOREIGN-LIBRARIES-FOR-AB-WHEN-APPROPRIATE: ~
                        can't find valid system name in &optional argument ~
                        or in current-system-being-loaded")
                nil)))))
     (when library
       (load-foreign-libraries (list library)))))

(defmacro load-foreign-libraries-for-ab-when-appropriate
    (&optional unevaluated-name-of-system?)
  (feature-case
    ((not :chestnut-trans)
     (if unevaluated-name-of-system?
         `(let ((current-system-being-loaded ',unevaluated-name-of-system?))
            ,(body-of-load-foreign-libraries-for-ab-when-appropriate nil))
         (body-of-load-foreign-libraries-for-ab-when-appropriate t)))
    (t nil)))

;;; Currently `load-foreign-libraries-for-ab-when-appropriate' is called once
;;; here, since we will be calling c-native-clock-ticks-per-second soon, and
;;; once after the last C function has been defined.  In G2 that is in SEQUENCES1
;;; and in Telewindows that is in TELEWINDOWS.

;;; uncomment the following setf to cause lucid to save symbols for later use in
;;; gdb.  See the occurrence of (reload-foreign-libraries) further on down in
;;; the load order of your system (it's currently 11 Apr 1996 in ole.lisp for
;;; g2) for another change, uncommenting the (SYS:WRITE-CURRENT-SYMBOL-INFO
;;; "symbolfile") line that occurs there.  NOTE that this currently 11 Apr 1996
;;; only works under sunos in lucid 4.1 -ncc, 11 Apr 1996
;;;
;;;(setf  SYS:*SAVE-FOREIGN-SYMBOL-TABLES* t)

(load-foreign-libraries-for-ab-when-appropriate)

;; Apparently this must be done twice, once before any foreign functions
;; are defined and once after they have all been defined.  Nobody understands
;; this pagan ritual, but we do it.  In G2 the last call happens to be in
;; SEQUENCES1, and in Telewindows it happens to be in TELEWINDOWS.  That all
;; leads to a trap if some innocent person defines a new foreign function after
;; those modules.  - ben 9/9/93  (Is this satan's date?)

;; jh, 10/19/94.  Not that I understand pagan rituals, but I believe we call
;; load-foreign-libraries-for-ab-when-appropriate two times because the first
;; time we need it in some Lucid-only compile-time function that needs foreign
;; functions.  The second time is necessary because Lucid foreign libraries must
;; be loaded after the last "foreign symbol" has been "interned" in order for
;; proper linking to occur.  If we didn't indulge in the wackiness of calling
;; foreign functions at compile-time, I believe, we'd only have to explain a
;; single call to load-foreign-libraries-for-ab-when-appropriate.

;; jh, 10/19/94.  Calling load-foreign-libraries-for-ab-when-appropriate by
;; itself is not enough to link to a new foreign function from an existing
;; Lucid.  Some craft knowledge:
;;
;; How to reload a foreign function in Lucid development
;;   > Edit C source file.
;;   > sandbox
;;   > runmake ext opt libcprim.a
;;   > Can't make a function out of the unintern-foreign-symbol and
;;     def-gensym-c-function forms below, even an interpreted one, because of
;;     macro-clobbering (at least in the Lucid version we used as of 10/25/93,
;;     yes, 93).
;;     Also looks like you have to unintern both the C function you care about
;;     and the C function that calls it and directly connects to Lisp via
;;     def-gensym-c-function.
;;       (lcl::unintern-foreign-symbol "_network_connect")
;       (def-gensym-c-function c-network-connect
;         (:fixnum-int "network_connect")
;         ((:default network-pathname)))
;;   > The following call emits a single warning to let you know that the
;;     foreign function was successfully uninterned with
;;     lcl::unintern-foreign-symbol and re-interned with def-gensym-c-function.
;;       (reload-foreign-libraries)

;;; Add the G2 Enterprise wrapper right here, so we will be able 
;;; to use it instantly

(def-gensym-c-function is-g2-enterprise-defined? 
    (:fixnum-int "isG2Enterprise") ())

(defvar *is-g2-enterprise?* (if (=f (is-g2-enterprise-defined?) 0) nil t))

(defun g2-enterprise-p () *is-g2-enterprise?*)
