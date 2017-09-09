;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GLDEBUG

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.
;;; Peng Tsin Ong, Fred White, Ben Hyde, R. Ferrante




(declare-forward-reference print-wide-string function) ; UNICODE
(declare-forward-reference wide-string-to-gensym-string function) ; UNICODE
(declare-forward-reference evaluation-value-p-function function) ; TYPES




;;;; Introduction


;;; A number of functions useful when doing interactive debugging are defined
;;; in here, most with very mnemonic names.  Various information functions
;;; called by ILISP are also here, as well as the methods responsible
;;; for mouse-sensitive object in ILISP.

;;; This entire file is development-only.  Some functions are also Lucid only.



;;;; Print methods


;;; The defvar `development-print-methods' is a list of functions on (object stream)
;;; which are tried in order.  The first function which returns non-NIL
;;; is assumed to have done the job.

(defvar development-print-methods ())


;;; The defvar `development-describe-methods' works identically to print-methods
;;; for describing objects.

(defvar development-describe-methods ())

;; What, another method system?



;;; The macro `def-development-printer' defines a new printing function for
;;; debugging in development.  The print function must test the type of
;;; its argument itself, and return non-NIL iff it actually prints something.
;;; The arglist should look like (thing stream).


(defmacro def-development-printer (name arglist &body body)
  `(progn
     (pushnew ',name development-print-methods)
     (defun ,name ,arglist ,@body)))



;;; The macro `def-development-describer' is similar.  The arglist
;;; should look like (thing).

(defmacro def-development-describer (name arglist &body body)
  `(progn
     (pushnew ',name development-describe-methods)
     (defun ,name ,arglist ,@body)))

;; The argument order is for pprint-dispatch.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defun paranoid-print-gensym-object (stream thing)
    (and (fboundp 'print-gensym-object)
         (print-gensym-object stream thing))))

;;; We hook into the substrate for printing and pretty-printing
;;; via `clos:print-object' and `lcl:set-pprint-dispatch'.

;;; Fixed by turning into ":around" method by Denis Budyak, Mar 22, 2016.

#+(or lucid lispworks)
(clos:defmethod clos:print-object :around ((v array) stream)
  (cond ((stringp v)
         (clos:call-next-method))
        ((typep v '(simple-array (unsigned-byte 16) (*)))
         (print-wide-string v stream 0))
        ((or (typep v 'vector)
             (typep v 'simple-array))
         (or (paranoid-print-gensym-object stream v)
             (clos:call-next-method)))
        (t
         (clos:call-next-method))))

;; Some gensym objects are fundamentally lists.  Optionally print them nicely.
(defparameter allow-development-list-printing t)

#+(or lucid lispworks)
(clos:defmethod clos:print-object :around ((thing lisp:cons) stream)
  (or (and allow-development-list-printing
           (paranoid-print-gensym-object stream thing))
      (clos:call-next-method)))

#+(or lucid lispworks)
(defun not-a-string-p (thing)
  (not (stringp thing)))

#+lucid
(lcl:set-pprint-dispatch
  '(and lisp:vector (satisfies not-a-string-p))
  'paranoid-print-gensym-object
  5)

#+lispworks
(cl:set-pprint-dispatch
  '(and cl:vector (satisfies not-a-string-p))
  'paranoid-print-gensym-object
  5)

#+(or lucid lispworks)
(clos:defmethod clos::describe-object ((v lisp:vector) stream)
  (or (let ((*standard-output* stream)) (describe-gensym-object v))
      (clos:call-next-method)))

;;; The function `print-gensym-object' prints a lisp object, which may be
;;; masquerading as a G2 frame, managed array, etc.  It is actually called only
;;; where object is a vector and not a string, or a cons, by virtue of the
;;; above methods on clos:print-object. It MUST return NIL if it does not find
;;; a print method.

(defun print-gensym-object (stream thing)
  (loop for printer in development-print-methods
        thereis (funcall printer thing stream)))

;;; The function `describe-gensym-object' must return NIL if it does
;;; not find a describe method.

(defun describe-gensym-object (thing)
  (loop for describer in development-describe-methods
          thereis (funcall describer thing)))




;;; `Describe' is a implemented in lucid development by calling the ab-lisp
;;; internal describe.  The function "D" is more useful for G2 developers.

(defun describe (x &rest args-for-describe)
  (apply 'ab-lisp::describe x args-for-describe)
  x)



;;; `D' (D x) calls describe-frame on x, if it is a frame, describe-structure
;;; on x if it is a structure (but not if it has been reclaimed or if it is a
;;; list structure), and describe on x otherwise.

(defun d (&optional (x *))
  (let ((*standard-output* *debug-io*))
    (or (describe-gensym-object x)
        (describe x))
    x))



;;; 'P' (P x) is analagous to 'D', but it "prints" rather than "describes".
;;;  This function is not necessary on Lucid, because we tell Lucid to print
;;; things using print-gensym-object by default.  But we haven't figured out
;;; how to do that on SBCL or Lispworks yet, nor (I believe) on Allegro, and
;;; it doesn't hurt (much) to let this function exist on all platforms,
;;; including Lucid.  -jv, 12/14/07

(defun p (&optional (x *))
  (or (paranoid-print-gensym-object t x)
      (print x))
  x)



;;; `print-valid-sbcl-alien-string' assumes it is given a proper alien-string
;;; and stream, and writes it out.  Obviously only makes sense in SBCL.

#+sbcl
(defun-simple print-valid-sbcl-alien-string (alien-string stream)
  (write-string "<sbcl:\"" stream)
  (loop for i from 0
    as chr = (sb-alien:deref alien-string i)
    while (/= 0 chr)
    do
    (write-char (code-char chr) stream))
  (write-string "\">" stream)
  alien-string)


;;; `sbcl-alien-string-p' is extraordinarily pedantic and likely redundant, but
;;; I haven't found the proper way to test this, and this will work for now.

#+sbcl
(defun sbcl-alien-string-p (thing)
  (let ((the-type (type-of thing)))
    (and (consp the-type)
         (eq (car the-type) 'sb-alien:alien)
         (eq (caadr the-type) '*)
         (equal (cadadr the-type) '(sb-alien:signed 8)))))


;;; The `pprint-sbcl-alien-string' development-printer, like all development-
;;; printers, is not hooked up to the SBCL reader.  But you can still invoke
;;; it using (p ...).  It would be nice to get it hooked up so that gensym-
;;; print-object is the way objects are printed by default.  It sure would help
;;; with these alien strings.  -jv, 12/14/07

#+sbcl
(def-development-printer pprint-sbcl-alien-string (thing stream)
  (when (sbcl-alien-string-p thing)
    (print-valid-sbcl-alien-string thing stream)))



;; In BOXES
(declare-forward-reference box-translation-and-text-function function)

;;; The function `DT' describes the text of the given rule.

(defun dt (rule) (pprint (box-translation-and-text-function rule)))


;;; `Hex' helps deal with hexadecimal notation.  Give it a string, and
;;; it tries to find a hex number in it, and returns (does not print)
;;; the hex number.
;;;
;;; Give it a number and it prints it in hex, in a format readable by the Lisp
;;; reader as the same number, i.e., #16rHHH.  The functions `octal', `decimal',
;;; and `binary' are similarly defined for octal, decimal, and binary notation.
;;; Finally, r2, r8, r10, r16, and r32 synonyms.  Note that there is no
;;; English-like synonym for r32 because the author could not think of one.
;;;
;;; Examples:
;;;
;;; (r32 "abc") => 10604
;;; (decimal "10") => 10
;;; (hex "10") => 16
;;; (r8 "200") => 128
;;;
;;; (r8 128) prints #8r200
;;; (hex 16) prints #16r10
;;; (decimal 10) prints #10r10
;;; (r32 10604) prints #32rABC

(defparameter parameterized-radix-format-control-string ; args: radix, radix, integer
  "#~dr~v,r")

(defun radix-magic (number-or-string radix)
  (if (numberp number-or-string)
      (let ((integer (round number-or-string)))
        (format t parameterized-radix-format-control-string
                radix radix integer)
        integer)
      (let* ((gensym-string
               (if (not (stringp number-or-string))
                   (wide-string-to-gensym-string number-or-string)
                   number-or-string))
             (number? (parse-integer
                        gensym-string
                        :junk-allowed t :radix radix)))
        number?)))

(defun hex (number-or-string)
  (radix-magic number-or-string 16))
(defun octal (number-or-string)
  (radix-magic number-or-string 8))
(defun decimal (number-or-string)
  (radix-magic number-or-string 10))
(defun binary  (number-or-string)
  (radix-magic number-or-string 2))

(defun r2 (number-or-string)
  (radix-magic number-or-string 2))
(defun r8 (number-or-string)
  (radix-magic number-or-string 8))
(defun r10 (number-or-string)
  (radix-magic number-or-string 10))
(defun r16 (number-or-string)
  (radix-magic number-or-string 16))
(defun r32 (number-or-string)
  (radix-magic number-or-string 32))



;;; The development-printer `print-random-gensym-vector' prints a vector
;;; object which was not handled by any of the mroe specific printers.

(def-development-printer print-random-gensym-vector (v stream)
  (when (and (vectorp v) (not (stringp v)))
    (printing-random-object (v stream)
      (format stream "~a ~a ~d"
              (pretty-name-for-vector-type v)
              (array-element-type v)
              (length v)))
    v))


(defun pretty-name-for-vector-type (v)
  (cond ((available-frame-vector-p v)
         '|Available-Frame-Vector|)
        ((simple-vector-p v)
         '|Simple-Vector|)
        (t
         '|Vector|)))


;;; Why does this exist when we have deleted-frame-p?  Do we really need to
;;; check the length of the thing?  (deleted-frame-p? doesn't.)  Maybe, if
;;; anything, this should be called deleted-frame-p-function.

;;; Answer: available-frame-vector-p works on any lisp object, deleted-frame-p
;;; works only on frames and deleted frames. -fmw, 12/20/01

(defun available-frame-vector-p (thing)
  (and (simple-vector-p thing)
       (> (length thing) 1)
       (eq (aref thing 1) 'available-frame-vector)))



(def-development-describer describe-short-gensym-array (x)
  (when (and (arrayp x)
             (not (stringp x))
             (= (array-rank x) 1)
             (<= (array-dimension x 0) 30))
    (print-random-gensym-vector x *standard-output*)
    (format t " is a ~a~%" (pretty-name-for-vector-type x))
    (loop for index from 0 below (array-dimension x 0) doing
      (format t "~&[~d] ~s~%" index (aref x index)))
    x))




;;;; Debugging and Inspecting Tools



;;; A `LOOP' pretty-printer.
;;; Poor-man's version which doesn't notice nesting.

#+LCL4.1
(defun-for-macro pprint-loop (stream loop)
  (lcl:pprint-logical-block (stream loop :prefix "(" :suffix ")")
    (let ((first? t))
      (loop
        (let ((element (lcl:pprint-pop)))
          (cond ((consp element)
                 (lcl:pprint-indent :block 2)
                 (write element :stream stream)
                 (setq first? nil))
                ((not (symbolp element))
                 (write element :stream stream))
                ((member element '(with for as while until when unless if do doing always thereis repeat
                                   collect collecting nonc nconcing sum summing
                                   initially finally)
                         :test #'string-equal)
                 (lcl:pprint-indent :block 5 stream)
                 (unless first?
                   (lcl:pprint-newline :mandatory stream))
                 (setq first? nil)
                 (write element :stream stream))
                (t
                 (write element :stream stream)))
          (lcl:pprint-exit-if-list-exhausted)
          (write-char #\space stream))))))

#+LCL4.1
(lcl:set-pprint-dispatch '(cons (member loop)) 'pprint-loop 5)




;;;; Mouse sensitive objects in ilisp.


(defvar emacs-mouse-commands ())

(defmacro emacs-mouse-command-named (name)
  `(get ,name 'emacs-mouse-command-named))


;; Of course, these need to be added to the menu in presentations.el.

(defmacro def-emacs-mouse-command (name (object) &body body)
  (let ((function-name (build-ab-symbol name 'emacs-mouse-command)))
    `(progn
       (defun ,function-name (,object) ,@body)
       ;; Maybe remember the applicable type: probably either symbol or any
       ;; lisp object.
       (pushnew ',name emacs-mouse-commands)
       (setf (emacs-mouse-command-named ',name) ',function-name))))


(def-emacs-mouse-command select (object)
  (declare (ignore object)))

(def-emacs-mouse-command describe (object)
  (d object))



;;; The function `ilisp-mouse-command' is called by Emacs with the desired
;;; command (select, describe, etc) and the printed representation of a
;;; (presumably recorded) Gensym object.  We pull out the real object and
;;; perform the operation.  Whatever we return here goes into *.

#+lucid
(defun ilisp-mouse-command (command-name text-of-object)
  (let ((object? (emacs-mouse-retrieve-object-from-printed-rep text-of-object)))
    (when object?
      (let ((command? (emacs-mouse-command-named command-name)))
        (cond (command?
               (funcall command? object?))
              (t
               (warn "Unknown command from emacs: ~s" command-name)))
        object?))))



;;; Assuming that string is of the form "#<... @id>", lookup the object.

#+lucid
(defun emacs-mouse-retrieve-object-from-printed-rep (string)
  (let ((spot (search "@" string :from-end t :test #'char-equal)))
    (when spot
      (let ((id (parse-integer string :start (1+ spot) :junk-allowed t)))
        (when id
          (output-recording-get-object id))))))



#+lucid
(defvar old-sharp-reader (lisp:get-dispatch-macro-character #\# #\<))


;;; The function `read-unreadable-object' makes the unreadable readable again.
;;; Imbedded ">" characters in the p.r. will confuse us.  Really, want to look
;;; for the regexp "@[0-9]+>"

#+lucid
(defun read-unreadable-object (stream character arg)
  ;; Read until matching ">"
  (cond #+ignore
        ((output-recording-is-empty-p)
         (funcall old-sharp-reader stream character arg))
        (t
         (let* ((level 0)
                (string (with-output-to-string (string)
                          (write-char character string)
                          (loop for previous-char = character then char
                                for char = (read-char stream nil nil t)
                                while char
                                doing
                            (write-char char string)
                            (cond ((and (char-equal char #\>)
                                        (zerop level))
                                   (return))
                                  ((and (char-equal previous-char #\#)
                                        (char-equal char #\<))
                                   (incf level))
                                  ((char-equal char #\>)
                                   (decf level)))))))
           (or (emacs-mouse-retrieve-object-from-printed-rep string)
               (cerror "Ignore the sharp construct and the form that follows."
                       "READ encountered #<, an unknown format (Argument was ~s)" arg))))))



;;; The function `clobber-the-sharp-reader-function' is called the first time any
;;; object is printed using the output-recording facility.

#+lucid
(defun clobber-the-sharp-reader-function ()
  (lisp:set-dispatch-macro-character #\# #\< 'read-unreadable-object))

;; This loses!  *readtable* is copied by the debugger!
;; (setq output-recording-hook 'clobber-the-sharp-reader-function)




;;;; Backtrace




;;; The macro `do-lisp-backtrace' runs the body with NAME bound to each element
;;; on the current lisp stack, in order.  The binding is usually a symbol, but
;;; can also be a list (for Lucid internal functions) or a string (for foreign
;;; functions).

#+lucid
(defmacro do-lisp-backtrace ((name &key (depth 15) stop-at)
                             filter
                             &body body)
  `(locally
       (declare (special sys:*frame-index*))
     (loop with env = (sys:stack-frame-environment)
           with count = 0
           for frame = (sys:top-frame env)
                     then (sys:previous-frame frame env)

           while frame
           while (<= count ,depth)
           as ,name = (sys:stack-frame-name frame env)
           when (and ,name ,filter)
             do (progn (incf count)
                       ,@body)
           until (memq ,name ,stop-at))))


#+lucid
(defun label-for-source-module (name &optional (type 'function))
  (let ((module? (if (symbolp name)
                     (lcl:ignore-errors
                       (module-of-symbol name type)))))
    (if module?
        (format nil "(~(~a~))" module?)
        "")))


#+lucid
(defvar maximum-backtrace-depth 50)


;;; `Backtrace' conses a fresh list containing the names of all of the
;;; functions on the call stack.  The keyword argument depth may be used change
;;; the default limit of 50 frames.

#+lucid
(defun backtrace (&key (depth maximum-backtrace-depth)
                       (package 'ab)
                       (stop-at '(sys::process-top-level)))
  (let ((list ())
        (package? (and package (find-package package)))
        (done nil))
    (loop until done do
      (setf list nil)
      (setf done t)
      (lcl::handler-case
            (do-lisp-backtrace (fname :depth depth :stop-at stop-at)
              (and (symbolp fname)
                   (or (null package?)
                       (eq (symbol-package fname) package?)))
              (push fname list))
            ;; appears to happen only after a GC.
            (liquid::interrupt-error () (setf done nil))))
    (reverse list)))

#-lucid
(defun backtrace (&rest args)
  ;; note the difference with this (lame) backtrace and the original LUCID's backtrace.
  ;; LUCID's version returned a cons of all stack frames while we return only a cons where
  ;; second element is atring with the printed output of dbg:output-backtrace. Also we 
  ;; ignore arguments. This is not good, but better than nothing. budden00 
  (declare (ignore args))
  (list
    nil ; this is cut off by make-lisp-backtrace-1
    (with-output-to-string (stream)
      (print-backtrace-to-lisp-stream stream))))

;;; Here are some backtrace printing code from trivial-backtrace:

#+(or mcl ccl)
(defun print-backtrace-to-lisp-stream (stream)
  (let ((*debug-io* stream))
    (ccl:print-call-history :detailed-p nil)))

#+sbcl
;; determine how we're going to access the backtrace in the next
;; function
(eval-when (:compile-toplevel :load-toplevel :execute)
  (when (find-symbol "*DEBUG-PRINT-VARIABLE-ALIST*" :sb-debug)
    (pushnew :sbcl-debug-print-variable-alist *features*)))

#+sbcl
(defun print-backtrace-to-lisp-stream (stream)
  (let (#+:sbcl-debug-print-variable-alist
	(sb-debug:*debug-print-variable-alist*
	 (list* '(*print-level* . nil)
		'(*print-length* . nil)
		sb-debug:*debug-print-variable-alist*))
	#-:sbcl-debug-print-variable-alist
	(sb-debug:*debug-print-level* nil)
	#-:sbcl-debug-print-variable-alist
	(sb-debug:*debug-print-length* nil))
    (sb-debug:print-backtrace :count most-positive-fixnum :stream stream)))

#+lispworks
(defun print-backtrace-to-lisp-stream (stream)
  (let ((*standard-output* stream))
    (dbg:output-backtrace :brief)))


;;; The function `verbose-backtrace' returns a list of strings, one per line as
;;; would be printed by the verbose backtrace.

#+lucid
(defun verbose-backtrace (&key (depth maximum-backtrace-depth)
                               (package 'ab)
                               (stop-at '(sys::process-top-level)))
  (let ((list ())
        (package? (and package (find-package package)))
        (done nil))
    (loop until done do
      (setf list nil)
      (setf done t)
      (lcl::handler-case
            (do-lisp-backtrace (fname :depth depth :stop-at stop-at)
              (and (symbolp fname)
                   (or (null package?)
                       (eq (symbol-package fname) package?)))
              (push (verbose-string-for-function-frame fname frame env) list))
            ;; appears to happen only after a GC.
            (liquid::interrupt-error () (setf done nil))))
    (reverse list)))

#-lucid
(defun verbose-backtrace (&rest args)
  (declare (ignore args))
  (list
    nil ; this is cut off by make-lisp-backtrace-1
    (with-output-to-string (stream)
      (print-verbose-backtrace-to-lisp-stream stream))))

#+(or mcl ccl)
(defun print-verbose-backtrace-to-lisp-stream (stream)
  (let ((*debug-io* stream))
    (ccl:print-call-history :detailed-p t)))

#+sbcl
(defun print-verbose-backtrace-to-lisp-stream (stream)
  (print-backtrace-to-lisp-stream stream))

#+lispworks
(defun print-verbose-backtrace-to-lisp-stream (stream)
  (let ((*standard-output* stream))
    (dbg:output-backtrace :verbose)))


;;; `Fn-arglist' is a Lucid development only function, it calls lcl:arglist,
;;; while avoiding the annoying "using unadvised defn" messages.

#+lucid
(defun fn-arglist (fn)
  (let ((proc (lucid:get-unadvised-procedure (if (symbolp fn)
                                                  (symbol-function fn)
                                                  fn))))
    (lcl:arglist proc)))

#+sbcl
(defun fn-arglist (fn)
  (declare (ignore fn))
  (list 'unknown-args))



#+lucid
(defun verbose-string-for-function-frame (name frame env)
  (let* ((arglist
           (fn-arglist name))
         (n-args
           (length (ldiff arglist (member '&optional arglist))))
         (arguments
           (loop for i below n-args
                 collect (sys:stack-frame-local-value frame env i)))
         (source-string
           (label-for-source-module name)))
    (with-output-to-string (stream)
      (format stream "~15a ~30@s ~:s" source-string name arguments))))




;;; `Collect-backtrace-into-list' is a synonym for `backtrace'. It filters out
;;; functions not in the AB package.

#+lucid
(defun collect-backtrace-into-list (&optional (depth 50)
                                              (stop-at '(sys::process-top-level)))
  (backtrace :depth depth :stop-at stop-at :package 'ab))




;;; `Function-active-p' returns T if a function of the given name is found in
;;; the current backtrace. The keyword arg depth maybe used to limit the
;;; search.

#+lucid
(defun function-active-p (function-name &key (depth 1000))
  (do-lisp-backtrace (fname :depth depth)
    (eq fname function-name)
    (return-from function-active-p t))
  nil)




;;; The defstruct `lisp-backtrace' encapsulates a backtrace, which
;;; is printed when the object is described.

(defstruct (lisp-backtrace
             (:constructor make-lisp-backtrace-1)
             (:predicate lisp-backtrace-p)
             (:print-function print-lisp-backtrace-1))
  (comment nil)
  (list ()))

;; Could use an option to record the verbose backtrace.

(defun make-lisp-backtrace (&optional comment)
  (#+lucid lcl:ignore-errors #-lucid cl:ignore-errors
    (make-lisp-backtrace-1 :list (cdr (backtrace))
                           :comment comment)))

(defun make-verbose-lisp-backtrace (&optional comment)
  (#+lucid lcl:ignore-errors #-lucid cl:ignore-errors
    (make-lisp-backtrace-1 :list (verbose-backtrace)
                           :comment comment)))


(defun print-lisp-backtrace-1 (backtrace stream depth)
  (declare (ignore depth))
  (print-lisp-backtrace backtrace stream))

(def-development-printer print-lisp-backtrace (backtrace stream)
  (when (lisp-backtrace-p backtrace)
    (printing-random-object (backtrace stream)
      (format stream "Backtrace~@[ ~s~]" (first (lisp-backtrace-list backtrace))))
    backtrace))

(def-development-describer describe-lisp-backtrace (backtrace)
  (when (lisp-backtrace-p backtrace)
    (let ((comment (lisp-backtrace-comment backtrace))
          (list (lisp-backtrace-list backtrace)))
      (when comment
        (format t "~a:~%" comment))
      (loop for name in list
            as first = t then nil
            doing
        (unless first
          (format t " <- "))
        (format t "~s" name))
      backtrace)))


(defun show-head-of-lisp-backtrace (&optional number-of-frames-to-show
                                              backtrace
                                              index
                                              function-to-stop-at)
  (let ((*print-case* :downcase)
        (backtrace-list (if backtrace
                            (lisp-backtrace-list backtrace)
                            (cdr (lisp-backtrace-list (make-lisp-backtrace))))))
    (with-faster-standard-output
      (if index
        (format t "~3d. " index)
        (write-string "     "))
      (loop for frame in backtrace-list
            as k from 0
            as stop-now-p = (or (and number-of-frames-to-show (>=f k number-of-frames-to-show))
                                (eq frame function-to-stop-at))
            until stop-now-p
            do
        (princ frame)
        (terpri)
        (loop for j from -7 below (ashf k 1) do
          (write-char #\Space)))
      (values))))




;;;; Cons cell leak detector


;;; This is a little package to help track down cons cell leaks.  It advises
;;; all of the consing and reclaming functions associated with a given pool, so
;;; that it can collect all of the new conses and delete all of the reclaimed
;;; ones.  For each remaining, presumably leaked cons, it prints the backtrace
;;; of the lisp stack at the time the cons was consed, and the cons itself.

;;; There are only three exported functions: `start-consing', `report-consing',
;;; and `stop-consing.'   Only one cons pool can be traced at a time.
;;; For Lucid and LispWorks.

;;; For example:
;;;  (start-consing 'frame)      ; Advise functions in the frame-cons pool.
;;;
;;;   ...do stuff which shouldn't leak, eg, pop up and pop down main menu...
;;;
;;;  (report-consing)
;;; #<Backtrace GET-NEXT-LIST-OF-NEW-CLASS-INSTANCES @1008>  #<CONS @1009>  (MESSAGE-BOARD  ...)
;;; ...
;;; #<Backtrace GET-NEXT-LIST-OF-NEW-CLASS-INSTANCES @1060>  #<CONS @1061>  (NON-KB-WORKSPACE KB-WORKSPACE)
;;; Total of 27 leaked conses.
;;;
;;;  (stop-consing)       ; Remove the advice (it slows down G2 quite a bit).
;;;
;;; Clicking the middle button on the backtrace objects will expand them into a
;;; full backtrace.

(def-concept cons-cell-leak-detector)


;;;; Break at allocation number

;;; If there is a deterministic scenario where cons leak happens, we can localize the 
;;; leak with allocation-serial-number-to-break
;;; First of all, use compare-memory-allocation to find out in what pool(s) leak happen.
;;; It is described in trails.pdf
;;; After that, the use case for allocation-serial-number-to-break is:
;;; (run-the-code) ; warm up the allocator
;;; (setq allocation-serial-number 0 leaking-cons-cells nil)
;;; (start-consing 'pool-where-leak-is-detected) ; e.g. 'slot-value-cons
;;; (run-the-code)
;;; (stop-consing)
;;; (print leaking-cons-cells) 
;;; ;; each entry in leaking cons cells contains an allocation number. Pick one of them.
;;; (setq allocation-serial-number 0)
;;; (setq allocation-serial-number-to-break 1234) ; one of the numbers in leaking-cons-cells
;;; (start-consing 'pool-where-leak-is-detected)
;;; (run-the-code)
;;; Debugger break will happen at the place where leaking cons is allocated.
;;; budden73, 2016-06-17 

(defvar allocation-serial-number 0)
(defvar allocation-serial-number-to-break nil)

;;; The defvar `leaking-cons-cells' accumulates a list of new conses.
;;; Each element is a list of (cons-type backtrace cons-cell).

(defvar leaking-cons-cells nil)
(defvar reclaimed-cons-cells nil)
(defvar advised-cons-pool-name nil)
(defvar over-reclaimed-cons-cells nil)
(defvar advised-consing-functions nil)
(defvar leaking-structures nil)
(defvar reclaimed-structures nil)
(defvar advised-structure-name nil)
(defvar advised-structure-manipulation-functions nil)
(defvar monitoring-frames? nil)
(defvar leaking-frames nil)
(defvar reclaimed-frames nil)
(defvar advised-frame-manipulation-functions nil)

;;; The function `start-monitoring-structure' advises the make and delete
;;; functions for the named structure. The
;;; companion functions are `stop-monitoring-structure' and `report-structures'

;;; as function-names need not be formed by the "rules" the option of
;;; specifying them in unusual circumstances is provided

;;; function names is a list of the generating and reclaiming functions
;;; e.g. (start-monitoring-structure 'gensym-pathname '(make-gensym-pathname-structure-function reclaim-gensym-pathname))
;;; (start-monitoring-structure 'managed-float '(allocate-managed-simple-float-array reclaim-managed-simple-float-array-function))
;;; (start-monitoring-structure 'managed-simple-vector `(allocate-managed-simple-vector reclaim-checked-managed-simple-vector))


(defun start-monitoring-structure (&optional
                                    (name-of-structure advised-structure-name)
                                    (function-names nil)
                                    )
  (when (and advised-structure-name
             (neq advised-structure-name name-of-structure))
    (stop-monitoring-structure))

  (unless advised-structure-manipulation-functions
    (advise-structure name-of-structure function-names
                      (if (eq name-of-structure 'managed-float) 1)))

  (format t "Reset ~a structure accumulator" name-of-structure)
  (setq advised-structure-name name-of-structure
        leaking-structures nil
        reclaimed-structures nil)
  (values))

#+(or lucid lispworks)
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :defadvice *features*))

#+defadvice
(defmacro defadvice ((dspec name) args &body body)
  #+lucid
  `(lcl:defadvice (,dspec ,name) ,args ,@body)
  #+lispworks
  `(lw:defadvice (,dspec ,name :around) ,args ,@body))
  
#+defadvice
(defmacro remove-advice (dspec name)
  #+lucid
  `(lcl:remove-advice ,dspec ,name)
  #+lispworks
  `(lw:remove-advice ,dspec ,name))

#+defadvice ; like a "funcall"
(defmacro advice-continue (&rest args)
  #+lucid
  `(lcl:advice-continue ,@args)
  #+lispworks
  `(lw:call-next-advice ,@args))

#+defadvice ; like an "apply"
(defmacro apply-advice-continue (args)
  #+lucid
  `(lcl:apply-advice-continue ,args)
  #+lispworks
  `(apply #'lw:call-next-advice ,args))


;;; The function `stop-monitoring-structure' removes the advice.

(defun stop-monitoring-structure ()
  #+defadvice
  (loop for fun in advised-structure-manipulation-functions doing
    (remove-advice fun 'leaks))
  (prog1 advised-structure-manipulation-functions
    (setq advised-structure-manipulation-functions nil)))

(defun report-structures (&optional (stream *standard-output*))
  (let ((*print-length* 2))
    (loop for (bt . structure) in leaking-structures
            sum 1 into total
            do (format stream "~s  ~a ~%" bt structure)
          finally
            (format stream "Total of ~d leaked ~a structures.~%" total advised-structure-name))
  (values)))


;;; The function `start-monitoring-frames' advises the make and delete
;;; functions for frames
;;; companion functions are `stop-monitoring-frames' and `report-frames'

#+defadvice
(defun start-monitoring-frames ()
  (unless monitoring-frames?
    (advise-frames))

  (format t "Reset Frame accumulator")
  (setq leaking-frames nil
        reclaimed-frames nil)
  (values))


;;; The function `stop-monitoring-structure' removes the advice.
#+defadvice
(defun stop-monitoring-frames ()
  (loop for fun in advised-frame-manipulation-functions doing
    (remove-advice fun 'leaks))
  (prog1 advised-frame-manipulation-functions
    (setq advised-frame-manipulation-functions nil)))

#+defadvice
(defun report-frames (&optional (stream *standard-output*))
  (let ((*print-length* 2))
    (loop for (bt . frame) in leaking-frames
            sum 1 into total
            do (format stream "~s  ~a ~%" bt frame)
          finally
            (format stream "Total of ~d leaked frames~%" total))
  (values)))

(defun install-advice (fun form)
  #-defadvice
  (declare (ignore fun form))
  #+lispworks
  (declare (ignore fun))
  #+defadvice
  (let ((advice #+lucid (eval form)
		#+lispworks (compile nil form)))
    ;; Warn the user that they may need to rewrite their advising function.  See
    ;; consing-advice-macro below.  yduJ, 11/04
    (warn "install-advice may not actually work.")
    #+lucid
    (format t "Compiling ~s~%" fun)
    #+lucid
    (lcl:compile-advice fun)
    advice))

(defvar verbose-reclamation-bt? nil)

;; This replaces the older function consing-advice, which got internal errors
;; within lucid.  Apparently the install-advice function doesn't work.  So
;; instead, we construct top-level forms with defadvice.  Unfortunately, this
;; requires rather a lot of dancing about to make it work.  Currently it only
;; works for defconser cons pools and the string and vector types.

(defun break-if-reached-allocation-serial-number-to-break ()
  (when (and allocation-serial-number-to-break
             (= allocation-serial-number-to-break
                allocation-serial-number))
    (let ((asntb allocation-serial-number-to-break))
      (setf allocation-serial-number-to-break nil)
      (break "Reached allocation-serial-number-to-break = ~S" asntb))))

#+defadvice
(defmacro consing-advice-macro (name &optional only-consing)
  (let ((functions (determine-functions-to-advise name))
        reclaim-functions cons-functions code)
    (loop for fun in functions
          if (or (search "DELETE" (string fun) :test #'char-equal)
                 (search "RECLAIM" (string fun) :test #'char-equal)) do
              (pushnew fun reclaim-functions)
          else do (pushnew fun cons-functions))

    (loop for consfun in cons-functions
          do (push `(defadvice (,consfun leaks) (&rest args)
                      (let* ((cons (apply-advice-continue args))
                             (bt (make-lisp-backtrace ',name))
                             (verbose-backtrace
                               (and verbose-reclamation-bt? (make-verbose-lisp-backtrace)))
                             (cell (car (member cons leaking-cons-cells :key #'cdr))))
                        (if cell
                            (setf (car cell) (cons bt verbose-backtrace))
                            (push (cons (cons bt verbose-backtrace) cons) leaking-cons-cells))
                        (break-if-reached-allocation-serial-number-to-break) ; added by Denis
                        cons))
                   code)
             (push `(pushnew ',consfun advised-consing-functions) code))

    (unless only-consing
      (loop for recfun in reclaim-functions do
          (push `(defadvice (,recfun leaks) (&rest args)
                   (let ((cons (car args)))
                     (setq leaking-cons-cells (delete cons leaking-cons-cells :key #'cdr))
                     (apply-advice-continue args)))
                code)
          (push `(pushnew ',recfun advised-consing-functions) code)))

    `(progn
       ,@code)))

;;;The purpose of this hideous kluge is to fool the compiler.  The problem is
;;;that if you just call consing-advice-macro directly, you can't indirect
;;;through the appropriate variable to get the actual name of the pool you're
;;;interested in.  So, we construct a function at runtime, which we then compile
;;;(otherwise everything is extraordinarily slow if you are tracing something
;;;that gets called a lot), and that we call it.  This allows us to get the
;;;actual name that we are interested in into the compile environment of the
;;;macro call.  It's entirely possible that something even more clever with
;;;multiple backquotes would do this, and future developers are welcome to
;;;implement that.  Note we don't really care about efficiency in the creation
;;;of this advice, just in the calls.  -- yduJ, 4/02
(defun call-consing-advice-macro (name-of-cons-pool)
  (let ((fn-name (gensym))
        (code `#'(lambda ()
                   (consing-advice-macro ,name-of-cons-pool))))
    (setf (symbol-function fn-name) (eval code))
    (compile fn-name)
    (funcall fn-name)))

;;; The function `start-consing' advises all of the consing functions for the
;;; given pool, if they have not already been advised..  It then resets the
;;; cons accumulator.  You can also trace SIMPLE-TEXT-STRING.

(defun start-consing (&optional (name-of-cons-pool advised-cons-pool-name))
  (when (and advised-cons-pool-name
             (neq advised-cons-pool-name name-of-cons-pool))
    (stop-consing))

  (unless advised-consing-functions
    (call-consing-advice-macro name-of-cons-pool))

  (format t "Reset ~a cons accumulator" name-of-cons-pool)
  (setq advised-cons-pool-name name-of-cons-pool
        leaking-cons-cells nil
        reclaimed-cons-cells nil
        over-reclaimed-cons-cells nil)
  (values))

(defvar verified-cons-pool-name nil)

(defvar verified-consing-functions nil)

(defvar extensive-reclaim-checking? nil)

(defun name-of-available-pool (a-name)
  (intern (string-upcase (format nil "available-~a-conses" a-name)) "AB"))

(defun name-of-available-pool-counter (a-name)
  (intern (string-upcase (format nil "available-~a-cons-counter" a-name)) "AB"))

(defun name-of-available-pool-tail (a-name)
  (intern (string-upcase (format nil "available-~a-cons-tail" a-name)) "AB"))  

;;;Note: this and other advising functions below may not work; "install-advice"
;;;was not working for the cons leak detect functions.  Try rewriting a la
;;;"consing-advice-macro" above.  yduJ, 11/04

#+defadvice
(defun setup-replenisher-verification-advice (name)
  (let* ((replenisher (intern (format nil "REPLENISH-~a-CONS-POOL" name) "AB"))
         (replenisher-advice
          `(defadvice (,replenisher verification) (&rest args)
             (let* ((marker (symbol-value (intern (format nil "~a-CAR-MARKER" ',name)
                                                  "AB")))
                    (result (apply-advice-continue args)))
               #+ignore
               (format t "~% result args ~a ~a" args result)
               (loop for location on ,(name-of-available-pool name)
                     for count from 0 to cons-pool-conses-to-make-at-a-time
                     do
                 (when (null location)
                   (cerror "continue" "NULL location in replenish pool!!"))
                 (cond ((null (car location))
                        (setf (car location ) marker))
                       ((not (eq (car location) marker))
                        (break "pool of available conses is already hosed containing a ~a"
                               (car location)))))
               result))))
    (pushnew replenisher verified-consing-functions)
    (install-advice replenisher replenisher-advice)))

(defvar return-value-advised-functions nil)

(defvar items-matching-returned-value-criteria nil)

(defun find-unique-items ()
  (let ((the-set nil))
    (loop for item in items-matching-returned-value-criteria
          do
      (pushnew (caar item) the-set))
    the-set))

(defun find-unique-calls ()
  (let ((the-set nil))
    (loop for item in items-matching-returned-value-criteria
          for thing-to-match = (car item)
          do
      (unless (member thing-to-match the-set
                      :test #'equal)
        (push thing-to-match the-set)))
    the-set))

#+defadvice
(defun check-for-return-equal (function-name return-val-for-equal-check)
  (let ((form `(defadvice (,function-name return-value-equal) (&rest args)
                 (let (return-value bt)
                   (setq return-value (apply-advice-continue args))
                   (when (equal return-value ,return-val-for-equal-check)
                     (setq bt (make-lisp-backtrace))
                     (format t "~% ~a,~a returned ~a: ~a"
                             ',function-name args ,return-val-for-equal-check
                             bt)
                     (push (list args bt) items-matching-returned-value-criteria))
                   return-value))))
    (pushnew function-name return-value-advised-functions)
    (install-advice function-name form)))

#+defadvice
(defun stop-return-equal-checks ()
  (loop for fun in return-value-advised-functions doing
    (remove-advice fun 'return-value-equal))
  (setq return-value-advised-functions nil))

(defun advise-verify-consing (name)
  #-defadvice (declare (ignore name))
  #+defadvice
  (let* ((available-pool-name (name-of-available-pool name))
         (functions (consing-functions-to-advise name))
         (conser-advice
           `(defadvice (<dummy> verification) (&rest args)
              (let ((marker
                      (symbol-value (intern (format nil "~a-CAR-MARKER"
                                               ',name)
                                       "AB"))))
              (when (or (eq (first args) marker)
                        (eq (second args) marker))
                    (break "trying to cons onto a free cons"))
              (apply-advice-continue args))))
         (single-reclaimer-advice
           `(defadvice (<dummy> verification) (&rest args)
              (when extensive-reclaim-checking?
                (when (memq (car args) ,available-pool-name)
                    (break "trying to reclaim a cons that isn't allocated")))
              (apply-advice-continue args)))
         (list-reclaimer-advice
           `(defadvice (<dummy> verification) (&rest args)
              (when extensive-reclaim-checking?
                (loop
                  for cons = (car args) then cdr-of-cons
                  for cdr-of-cons = (cdr cons)
                     while cons
                      do
                  (when (memq cons ,available-pool-name)
                    (break "trying to reclaim a cons that isn't allocated"))

                  until (or (null cdr-of-cons) (not (consp cdr-of-cons)))))
              (apply-advice-continue args))))
    (setup-replenisher-verification-advice name)
    (loop for fun in functions
          as form =
          (subst fun '<dummy>
                 (copy-tree
                   (COND ((search "RECLAIM" (string fun) :test #'char-equal)
                          (cond ((or (search "TREE" (string fun) :test #'char-equal)
                                     (search "LIST" (string fun) :test #'char-equal))
                                 list-reclaimer-advice)
                                (t
                                 single-reclaimer-advice)))
                          ((search "CONS-1" (string fun) :test #'char-equal)
                           conser-advice))))
          do
      (when form
        (push fun verified-consing-functions)
        (install-advice fun form)))))


(defun any-duplicates-in-list? (the-list &optional (break-instead-of-print? nil))
  (loop for element in the-list
        with test-list = the-list
        with result? = nil
        do
    (setq test-list (cdr test-list))
    (when (memq element test-list)
      (setq result? t)
      (if break-instead-of-print?
          (break "duplicates of ~a in the list" element)
          (format t "~% Duplicate of ~a" element)))
        finally
          (return result?)))

;;; `verify-consing' is useful if you suspect double use of a cons cell
(defun verify-consing (&optional (name-of-cons-pool advised-cons-pool-name))
  (when (and verified-cons-pool-name
             (neq verified-cons-pool-name name-of-cons-pool))
    (stop-verification))

  (unless advised-consing-functions
    (advise-verify-consing name-of-cons-pool))

  (format t "Reset ~a cons accumulator" name-of-cons-pool)
  (setq verified-cons-pool-name name-of-cons-pool)
  (values))


(defun stop-verification ()
  #+defadvice
  (loop for fun in verified-consing-functions doing
    (remove-advice fun 'verification))
  (prog1 verified-consing-functions
    (setq verified-consing-functions nil)))


;;; The function `stop-consing' removes the advice.

(defun stop-consing ()
  #+defadvice
  (loop for fun in advised-consing-functions doing
    (remove-advice fun 'leaks))
  (prog1 advised-consing-functions
    (setq advised-consing-functions nil)))

(defun report-text-string-leaks (&optional (stream *standard-output*))
  (let ((*print-length* 3))
    (loop for ((bt .  verbose-backtrace) . a-string) in leaking-cons-cells
          when t
            sum 1 into total and
            do
              (print-string-as-structure a-string stream)
            (format stream "  ~s~%" a-string)
            (if verbose-reclamation-bt?
                 (let ((*print-length* nil))
                   (format stream "   ~s (~s)~% " bt (or (and bt (lisp-backtrace-list bt)) "<backtrace failure>"))
                   (loop for line in (and verbose-backtrace (lisp-backtrace-list verbose-backtrace))
                         do (format stream "~a~%" line)))
                 (format stream "   ~s~%" bt))
          finally
            (format stream "Total of ~d leaked ~a conses.~%" total advised-cons-pool-name))
  (values)))


(defun report-text-string-leaks-to-file (filename)
  (with-open-file (stream filename
                          :direction :output
                          :if-exists :overwrite
                          :if-does-not-exist :create)
    (report-text-string-leaks stream)))

(defun report-consing-to-file (filename)
  (cond ((or (eq advised-cons-pool-name 'SIMPLE-TEXT-STRING)
             (eq advised-cons-pool-name 'ADJUSTABLE-TEXT-STRING))
         (report-text-string-leaks-to-file filename))
        (t

         (with-open-file (stream filename
                                 :direction :output
                                 :if-exists :overwrite
                                 :if-does-not-exist :create)
           (report-consing :stream stream)))))

(defun report-structures-to-file (filename)
  (with-open-file (stream filename
                          :direction :output
                          :if-exists :overwrite
                          :if-does-not-exist :create)
    (report-structures stream)))


;;; The function `report-consing' prints the newly outstanding conses since the
;;; last call to start-consing. Each cons is annotated with an encapsulated
;;; backtrace of the stack at the time it was consed.  Click middle on the
;;; backtrace objects to expand them.  The cons is also printed in the @nnnn
;;; format so that it can be grabbed with the mouse.

(defun report-consing (&key (stream *standard-output*) include-non-conses)
  (cond ((or (eq advised-cons-pool-name 'SIMPLE-TEXT-STRING)
             (eq advised-cons-pool-name 'ADJUSTABLE-TEXT-STRING)
             (eq advised-cons-pool-name 'BYTE-VECTOR-16))
         (report-text-string-leaks stream))
        (t
         (let ((*print-length* 2)
               (marker (symbol-value (intern (format nil "~a-CAR-MARKER"
                                                     advised-cons-pool-name)
                                             "AB"))))
           (loop for (bt . cons) in leaking-cons-cells
                 when (or (not (consp cons))
                          (neq (car cons) marker))
                   count (consp cons) into total and
                   do (when (or (consp cons)
                                include-non-conses)
                        (format stream "~s  " bt)
                        (print-cons-as-structure cons stream)
                        (format stream "  ~s~%" cons))
                 finally
                   (format stream "Total of ~d newly outstanding ~a conses.~%"
                           total advised-cons-pool-name))
           (values)))))

(defun report-leaks-matching-backtrace (key-bt &key (stream *standard-output*) include-non-conses)
  (cond ((or (eq advised-cons-pool-name 'SIMPLE-TEXT-STRING)
             (eq advised-cons-pool-name 'ADJUSTABLE-TEXT-STRING))
         (report-text-string-leaks stream))
        (t
         (let ((*print-length* 2)
               (marker (symbol-value (intern (format nil "~a-CAR-MARKER"
                                                     advised-cons-pool-name)
                                             "AB"))))
           (loop for (bt . cons) in leaking-cons-cells
                 when (and (or (not (consp cons))
                               (neq (car cons) marker))
                           (and (equal (lisp-backtrace-list key-bt)
                                       (lisp-backtrace-list bt))))
                   count (consp cons) into total and
                   do (when (or (consp cons)
                                include-non-conses)
                        (format stream "~s  " bt)
                        (print-cons-as-structure cons stream)
                        (format stream "  ~s~%" cons))
                 finally
                   (format stream "Total of ~d newly outstanding ~a conses.~%"
                           total advised-cons-pool-name))
           (values)))))

(defun report-unclaimed-conses-in-list (a-list cons-pool-name
                                               &optional (stream *standard-output*))
  (let ((*print-length* 2)
        (marker (symbol-value (intern (format nil "~a-CAR-MARKER" cons-pool-name)
                                      "AB"))))
    (loop for cons in a-list
          for index from 0
          when (or (not (consp cons))
                   (neq (car cons) marker))
            sum 1 into total and
            do (format stream "[~a]  " index)
               (print-cons-as-structure cons stream)
               (format stream "  ~s~%" cons)
          finally
            (format stream "Total of ~d  outsanding ~a conses.~%"
                    total cons-pool-name))
  (values)))



(defun report-over-reclamation (&optional (stream *standard-output*))
  (let ((*print-length* 2)
        (marker (symbol-value (intern (format nil "~a-CAR-MARKER"
                                              advised-cons-pool-name)
                                      "AB"))))
    (loop for (bt . cons) in over-reclaimed-cons-cells
          when (or (not (consp cons))
                   (neq (car cons) marker))
            sum 1 into total and
            do (format stream "~s  " bt)
               (print-cons-as-structure cons stream)
               (format stream "  ~s~%" cons)
          finally
            (format stream "Total of ~d over reclaimed ~a conses.~%"
                    total advised-cons-pool-name))
  (values)))

(defun report-reclamation (&optional (stream *standard-output*))
  (let ((*print-length* 2)
        (marker (symbol-value (intern (format nil "~a-CAR-MARKER"
                                              advised-cons-pool-name)
                                      "AB"))))
    (loop for (bt . cons) in reclaimed-cons-cells
          when (or (not (consp cons))
                   (neq (car cons) marker))
            sum 1 into total and
            do (format stream "~s  " bt)
               (print-cons-as-structure cons stream)
               (format stream "  ~s~%" cons)
          finally
            (format stream "Total of ~d reclaimed ~a conses.~%"
                    total advised-cons-pool-name))
  (values)))








;;; The function `print-as-structure' prints any lisp-object clickably.

(defun print-as-structure (thing &optional (stream *standard-output*))
  (printing-random-object (thing stream)
    (format stream "~a" (type-of thing))))



;;; The macro `formatz' prints the given expressions clickably.

(defmacro formatz (&rest exps)
  `(let ((*print-length* 3))
     ,@(loop for exp in exps
             if (stringp exp)
               collect `(format t "~a " ,exp)
               else
                 collect `(format t "~a = " ',exp) and
                 collect `(print-as-structure ,exp) and
                 collect `(format t " = ~s~%" ,exp))))



;;; The function `print-cons-as-structure' prints a cons cell clickably.

(defun print-cons-as-structure (cons &optional (stream *standard-output*))
  (print-as-structure cons stream))

(defun print-string-as-structure (a-string &optional (stream *standard-output*))
  (print-as-structure a-string stream))



(declare-forward-reference no-value variable)
(declare-forward-reference managed-float-p-function function)

(defun print-list-as-cons-structure (a-list &optional (level 0))
  (when (consp a-list)
    (format t "~% List (~a)~a:  " level a-list )
    (loop for slot-cons = a-list then next-cdr
          for car-value = (car slot-cons)
          for next-cdr = (cdr slot-cons)
          do (format t "~% (~a) " level)
             (print-as-structure slot-cons)
             (when (consp car-value)
               (print-list-as-cons-structure car-value (+f 1 level)))


          while (and (consp next-cdr)
                     (neq next-cdr no-value)
                     (not (managed-float-p-function next-cdr))))))


#+lucid
(defparameter track-reclamations? nil)


(defvar check-for-over-reclamation? nil)



;;; `watch-lists-in-detail?' causes the advice to track each cons in allocated
;;; and reclaimed lists

(defparameter watch-lists-in-detail? nil)

(defvar replenished-conses nil)

(defvar advised-replenishing-functions nil)

(defun start-replenishing (&optional (name-of-cons-pool advised-cons-pool-name))
  (when (and advised-replenishing-functions)
    (stop-replenishing))

  (unless advised-consing-functions
    (advise-replenishing name-of-cons-pool))

  (format t "Reset ~a cons accumulator" name-of-cons-pool)
  (setq replenished-conses nil)
  (values))

(defun stop-replenishing ()
  #+defadvice
  (loop for fun in advised-replenishing-functions doing
    (remove-advice fun 'replenishing))
  (prog1 advised-replenishing-functions
    (setq advised-replenishing-functions nil)))


;;; this will grab the car of the newly allocated conses and push it onto the
;;; `replenished-conses' list

(defun advise-replenishing (name)
  #-defadvice (declare (ignore name))
  #+defadvice
  (let* ((the-function (intern (string-upcase (format nil "replenish-~a-cons-pool" name)) "AB"))
         (the-advice
           `(defadvice (,the-function replenishing)
                (&rest args)
              (let* ((cons (apply-advice-continue args)))
                (push (cdr cons)
                      replenished-conses)
                cons))) )
    (pushnew the-function advised-replenishing-functions)
    (install-advice the-function the-advice)))




(defun advise-structure (name functions &optional (car-value nil))
  #-defadvice (declare (ignore car-value))
  (unless functions
    (setq functions (structure-creation-functions-to-advise name)))
  #+defadvice
  (let* ((creation-advice
           `(defadvice (<dummy> leaks)
                (&rest args)
              (let* ((structure (apply-advice-continue args))
                     bt cell)
                (when ,(or (null car-value)
                           `(=f (car args) ,car-value))
                  (setq bt (make-lisp-backtrace))
                  (setq cell (car (member structure leaking-structures :key #'cdr))))
                (if cell
                    (setf (car cell) bt)
                    (push (cons bt structure) leaking-structures))
                structure)))
         (reclaim-advice
           (if
             track-reclamations?
             `(defadvice (<dummy> leaks)
                  (&rest args)
                (let* ((structure (car args))
                       (return-value nil)
                       (bt
                         (if verbose-reclamation-bt?
                             (make-verbose-lisp-backtrace)
                             (make-lisp-backtrace)))
                       (cell (car (member structure reclaimed-structures :key #'cdr))))
                  (setq leaking-structures (delete structure leaking-structures :key #'cdr))
                  (setq return-value (apply-advice-continue args))
                  ;; we store the backtrace after the reclamation has succeeded
                  ;; so that we don't bash the old information
                  (if cell
                      (setf (car cell) bt)
                      (push (cons bt structure) reclaimed-structures))
                  return-value))
             `(defadvice (<dummy> leaks)
                  (&rest args)
                (let ((structure (car args)))
;                  (format t "~% Incoming arg ~a struct ~a" args structure )
;                  (format t "~% Structures  ~a"  leaking-structures)
                  (setq leaking-structures (delete structure leaking-structures :key #'cdr))
;                  (format t "~% Structures ~a" leaking-structures)
                  (apply-advice-continue args))))))

    (loop for fun in functions
          as form = (subst fun '<dummy>
                           (copy-tree
                             (if (search "RECLAIM" (string fun) :test #'char-equal)
                                 reclaim-advice creation-advice)))
          do
      (push fun advised-structure-manipulation-functions)
      (install-advice fun form))

    functions))


#+defadvice
(defun advise-frames ()
  (let* ((functions '(make-frame-internal delete-frame))
         (creation-advice
           `(defadvice (<dummy> leaks)
                (&rest args)
              (let* ((frame (apply-advice-continue args))
                     bt cell)
                (setq bt (make-lisp-backtrace))
                (setq cell (car (member frame leaking-frames :key #'cdr)))
                (if cell
                    (setf (car cell) bt)
                    (push (cons bt frame) leaking-frames))
                frame)))
         (reclaim-advice
           (if
             track-reclamations?
             `(defadvice (<dummy> leaks)
                  (&rest args)
                (let* ((frame (car args))
                       (return-value nil)
                       (bt
                         (if verbose-reclamation-bt?
                             (make-verbose-lisp-backtrace)
                             (make-lisp-backtrace)))
                       (cell (car (member frame reclaimed-frames :key #'cdr))))
                  (setq leaking-frames (delete frame leaking-frames :key #'cdr))
                  (setq return-value (apply-advice-continue args))
                  ;; we store the backtrace after the reclamation has succeeded
                  ;; so that we don't bash the old information
                  (if cell
                      (setf (car cell) bt)
                      (push (cons bt frame) reclaimed-frames))
                  return-value))
             `(defadvice (<dummy> leaks)
                  (&rest args)
                (let ((frame (car args)))
;                  (format t "~% Incoming arg ~a struct ~a" args frame )
;                  (format t "~% Frames  ~a"  leaking-frames)
                  (setq leaking-frames (delete frame leaking-frames :key #'cdr))
;                  (format t "~% Frames ~a" leaking-frames)
                  (apply-advice-continue args))))))

    (loop for fun in functions
          as form = (subst fun '<dummy>
                           (copy-tree
                             (if (search "RECLAIM" (string fun) :test #'char-equal)
                                 reclaim-advice creation-advice)))
          do
      (push fun advised-frame-manipulation-functions)
      (install-advice fun form))

    functions))

(defun find-record-of-cons-reclamation (a-cons)
  (car (member a-cons reclaimed-cons-cells :key #'cdr)))

(defun find-record-of-structure-reclamation (a-structure)
  (car (member a-structure reclaimed-structures :key #'cdr)))

(defun find-record-of-structure-allocation (a-structure)
  (car (member a-structure leaking-structures :key #'cdr)))

(defun determine-functions-to-advise (name)
  (case name
    (adjustable-gensym-string
     '(obtain-adjustable-gensym-string
       obtain-long-enough-adjustable-gensym-string
       reclaim-adjustable-gensym-string))
    (simple-text-string
     '(reclaim-simple-text-string obtain-simple-text-string))
    (managed-simple-vector
     '(allocate-managed-simple-vector reclaim-managed-simple-vector))
    (byte-vector
     '(allocate-byte-vector reclaim-byte-vector))
    (byte-vector-16
     '(reclaim-byte-vector-16 allocate-byte-vector-16))
    (managed-simple-float-array
     '(allocate-managed-simple-float-array
       reclaim-managed-simple-float-array))
    ;;reclaim-frame-vector is a macro, so you would have to hack on lisp to make it work
    ;;(frame-vector '(allocate-frame-vector reclaim-frame-vector))
    (t (consing-functions-to-advise name))))

(defun consing-functions-to-advise (name)
  (let ((result nil))
    (loop for fmt in '("~a-cons-1" "reclaim-~a-cons-1" "delete-~a-element-1")
          do
      (push (intern (string-upcase (format nil fmt name)) "AB") result))
    (unless watch-lists-in-detail?
      (loop for fmt in '("make-~a-list-1" "~a-list-2" "~a-list-3" "~a-list-4"
                         "copy-tree-using-~a-conses-1"
                         "copy-list-using-~a-conses-1"
                         "reclaim-~a-tree-1")
            do
        (push (intern (string-upcase (format nil fmt name)) "AB") result)))
    (unless (fboundp (first result))
      (cerror "Bull ahead anyway." "~A does not appear to name a cons pool." name))
    result))

(defun list-functions-to-advise (name)
  (loop for fmt in '("~a-list-trace-hook"
                     "copy-tree-using-~a-conses-1"
                     "reclaim-~a-list-1"
                     "reclaim-~a-tree-1"
                     "reclaim-~a-list-given-tail-for-development")
        collect (intern (string-upcase (format nil fmt name)) "AB")))



(defun single-cons-reclaimers (name)
  (loop for fmt in '("reclaim-~a-cons-1"
                     "DELETE-~a-ELEMENT-1")
        collect (intern (string-upcase (format nil fmt name)) "AB")))
(defun structure-creation-functions-to-advise (name)
  (loop for fmt in '("make-~a-1"
                     "reclaim-~a-1")
         collect (intern (string-upcase (format nil fmt name)) "AB")))

;; Still miss some: slot-value-pop reclaims by hand?



;;; Compile these to track byte-vector-16's (generally wide-strings).

#+ignore
(defparameter leaking-vectors nil)

#+ignore
(defadvice (allocate-byte-vector-16 leaks) (required-size)
  (let* ((vector (advice-continue required-size))
         (bt (make-lisp-backtrace))
         (cell? (car (member vector leaking-vectors :key #'cdr))))
    (if cell?
        (setf (car cell?) bt)
        (push (cons bt vector) leaking-vectors))
    vector))

#+ignore
(defadvice (reclaim-byte-vector-16 leaks) (byte-vector-16)
  (setq leaking-vectors (delete byte-vector-16 leaking-vectors :key #'cdr))
  (advice-continue byte-vector-16))



;;;; Debugger commands and utilities



#+lucid
(defvar gensym-debugger-additions nil)

#+lucid
(defun add-lucid-debugger-command (command function doc)
  (let ((entry (list command function doc)))
    (setf gensym-debugger-additions
          (delete command
                  gensym-debugger-additions
                  :key #'first))
    (push entry gensym-debugger-additions)
    entry))


#+lucid
(defmacro def-lucid-debugger-command (command function doc)
  `(add-lucid-debugger-command ',command ',function ',doc))


;;; `Add-all-lucid-debugger-commands' exists only since
;;; disksaves apparently don't save these.

#+lucid
(defun add-all-lucid-debugger-commands ()
  (declare (special sys:*debugger-commands*
                    sys:*debugger-all-commands*
                    sys:*debugger-basic-commands*))
  (loop for entry in gensym-debugger-additions
        do
    (push entry sys:*debugger-commands*)
    (push entry sys:*debugger-all-commands*)
    (push entry sys:*debugger-basic-commands*)))


#+lucid
(defconstant invoke-debugger-qualified-name
  #+lcl5.0
  'liquid-common-lisp::invoke-debugger
  #-lcl5.0
  '(:internal lucid::enter-debugger 0))

#+lucid
(defconstant lisp-top-level-name 'system:enter-top-level)

#+lucid
(defvar skippable-frames
  (list invoke-debugger-qualified-name
        'cerror 'error 'break))

#+lucid
(defvar top-of-stack-frames
  (list lisp-top-level-name
        invoke-debugger-qualified-name))

#+lucid
(defun skip-over-breaks (sfe invoke-debugger-index)
  (loop as x = invoke-debugger-index then (sys:previous-frame x sfe)
        as frame-name = (sys:stack-frame-name x sfe)
        while (or (null frame-name)
                  (memq frame-name skippable-frames))
        finally
          (return x)))

#+lucid
(defun get-invoke-debugger-index (sfe)
  (loop for x = 0 then (sys:previous-frame x sfe)
        as frame-name =  (sys:stack-frame-name x sfe)
        until (member frame-name top-of-stack-frames :test #'equal)
        finally
          (if (eq frame-name lisp-top-level-name)
              (return -1)
              (return (skip-over-breaks sfe x)))))

#+lucid
(defun debugger-verbose-backtrace (&key special-bindings (default-depth 10) (stream *debug-io*))
  "Print a backtrace with source files. Or, if stream is NIL, collect into a list"
  (declare (special sys:*frame-environment* sys:*frame-index*))
  (let* ((depth (or (sys:debugger-prompt-and-read :optional-expression)
                    default-depth))
         (frame-environment (sys:stack-frame-environment))
         (frame-index
           (if (boundp 'sys:*frame-index*)
               sys:*frame-index*
               (get-invoke-debugger-index frame-environment))))
    (if (=f frame-index -1)
        (format t "Error: could not find top of stack.~%")
        (debugger-verbose-backtrace-1 frame-index frame-environment
                                      special-bindings depth stream))))


#+lucid
(defun debugger-verbose-list-backtrace (&key special-bindings (default-depth 10))
  (debugger-verbose-backtrace :special-bindings special-bindings
                              :default-depth default-depth
                              :stream nil))



;;; The function `print-debugger-backtrace' prints a debugger backtrace from
;;; the top of the stack downwards.  Verbose means to include the arguments to
;;; functions on the stack.

#+lucid
(defun print-debugger-backtrace (&key (verbose t) (depth 15) special-bindings)
  (let* ((env (sys:stack-frame-environment))
         (index (sys:top-frame env)))
    (cond (verbose
           (debugger-verbose-backtrace-1 index env special-bindings depth))
          (t
           (debugger-concise-backtrace index env depth)
           (terpri)))))


#+lucid
(defun bt ()
  (print-debugger-backtrace :verbose nil))




#+lucid
(defun debugger-concise-backtrace (frame-index frame-environment &optional (depth 6))
  (let ((stream *debug-io*))
    (fresh-line stream)
    (loop with env = frame-environment
          with count = 0
          for frame = frame-index
                    then (sys:previous-frame frame env)
          while frame
          while (<= count depth)
          as name = (sys:stack-frame-name frame env)
          as first = t then nil
          when name
            do (format stream "~a~s" (if first "" " <- ") name)
               (incf count))
    (terpri stream)))


(defparameter print-lists-as-cons-cells nil)


#+lucid
(defun debugger-verbose-backtrace-1 (frame-index frame-environment
                                                 &optional special-bindings
                                                 (depth 10)
                                                 (stream *debug-io*))
  (let ((*print-length* 10)
        (*print-circle* nil)
        (*print-pretty* nil)
        (lucid-package (find-package "LUCID"))
        (bt-value ()))

    ;; If stream is NIL, then collect backtrace into a list of lines.
    (macrolet ((FMT (format &rest args)
                 `(cond ((null stream)
                         (push (format nil ,format ,@args) bt-value))
                        (t
                         (format stream ,format ,@args)))))

      (loop with env = frame-environment
            with count = 0
            for frame = frame-index
                      then (sys:previous-frame frame env)
            while frame
            while (< count depth)
            for name = (sys:stack-frame-name frame env)
            for type = (sys:stack-frame-type frame env) ; :compiled-function, :special-binding, etc.
            doing
        (case type
          ((:compiled-function :interpreted-function)
           (when (and name (symbolp name) (fboundp name) ; Name is LAMBDA for interpreted functions.
                      (neq (symbol-package name) lucid-package))

             (let ((string
                     (verbose-string-for-function-frame name frame env)))
               (incf count)
               (FMT "~%~a" string))))

          (:special-binding
           (when special-bindings
             (loop for i from 0 below (sys:stack-frame-length frame env) by 3
                   as name = (sys:stack-frame-local-value frame env (+ i 0))
                   as old = (sys:stack-frame-local-value frame env (+ i 1))
                   as new = (sys:stack-frame-local-value frame env (+ i 2))
                   do
                 (let ((source-string
                         (label-for-source-module name 'variable)))

                   (FMT "~%S~20a ~30@s ~s" source-string name new)))))

          (:foreign-frame
           (FMT "~%~20a ~30@a" "" name)))))

    (nreverse bt-value)))


#+lucid
(def-lucid-debugger-command :bv
    debugger-verbose-backtrace
  ":BV [count] Display a backtrace with arguments and source-files")



#+lucid
(defun disassemble-debugger-function ()
  (declare (special sys:*frame-environment* sys:*frame-index*))
  (let* ((env sys:*frame-environment*)
         (frame sys:*frame-index*)
         (name (sys:stack-frame-name frame env))
         (type (sys:stack-frame-type frame env)))
    type
    (when (symbolp name)
      (format t "Disassembly of ~s:" name)
      (disassemble name))))

#+lucid
(def-lucid-debugger-command :dis
    disassemble-debugger-function
  ":DIS Disassemble the function in the current stack frame")




;;; The function `show-special-variable-bindings' scans the stack from the bottom up.
;;; Each frame is either a function frame or a special variable binding frame.  If it
;;; is a binding, then the binding belongs to the following function frame.

#+lucid
(defun show-special-variable-bindings (&optional matching (package "AB"))
  (declare (special sys:*frame-environment* sys:*frame-index*))
  (let* ((matching (or matching (sys:debugger-prompt-and-read :optional-expression)))
         (env (sys:stack-frame-environment))
         (start-frame
           (if (boundp 'sys:*frame-index*)
               sys:*frame-index*
               (get-invoke-debugger-index env)))
         (package (and package (find-package package)))
         (*print-length* 3)
         (*print-level* 2)
         (*print-circle* nil)
         (stream *debug-io*)
         (bindings ()))
    ;; Start earlier to pick up this frame's specials.
    (loop initially
            (setq start-frame (sys:next-frame start-frame env))
          while (eq (sys:stack-frame-type start-frame env)
                    :special-binding)
          do
      (setq start-frame (sys:next-frame start-frame env)))
    (loop for frame = start-frame then (sys:previous-frame frame env)
          while frame
          while (or matching (neq frame-name 'RUN-ab))            ; Skip mondo frame.
          as frame-name = (sys:stack-frame-name frame env)
          as specials = (stack-frame-special-variables frame env matching package)
          doing
      (when specials
        (setq bindings (nconc specials bindings)))

      (when (and bindings frame-name)
        (format stream "~s~%" frame-name)
        (loop for (name . value) in bindings doing
          (format stream "   ~40s ~s~%" name value))
        (setq bindings nil)))
    (values)))


;;; The function `stack-frame-special-variable' returns an alist of names and
;;; values the special variable binding represented by the given stack frame,
;;; if any, which are in the given package and contain the given string.

#+lucid
(defun stack-frame-special-variables (index env &optional matching package)
  (let ((type (sys:stack-frame-type index env))
        (length (sys:stack-frame-length index env)))
    (when (eq type :special-binding)
      (loop for i below length by 3
            as name = (sys:stack-frame-local-value index env i)
            as old = (sys:stack-frame-local-value index env (+ i 1))
            as new = (sys:stack-frame-local-value index env (+ i 2))
            when (and name
                      (symbolp name)
                      (or (null package) (eq (symbol-package name) package))
                      (or (null matching)
                          (search (string matching) (symbol-name name) :test #'char-equal)))
              collect (cons name new)))))



;;; The function `stack-frame-special-variable' returns the name, old, and
;;; new values for a single stack frame binding.

#+lucid
(defun stack-frame-special-variable (index env)
  (let ((type (sys:stack-frame-type index env))
        (length (sys:stack-frame-length index env)))
    (when (and (eq type :special-binding)
               (eql length 3))
      (let ((name (sys:stack-frame-local-value index env 0))
            (old (sys:stack-frame-local-value index env 1))
            (new (sys:stack-frame-local-value index env 2)))
        (values name new old)))))



#+lucid
(def-lucid-debugger-command :sp
    show-special-variable-bindings
  ":SP [matching-string] Display a backtrace of special variable bindings")






;;; A ... (A N) gets arg N in the Lisp debugger.

#+lucid
(defun a (n)
  (L n))


;;; L ... (L N) gets loc N in the Lisp debugger.

#+lucid
(defun l (name-or-number)
  (declare (special sys:*frame-environment*
                    sys:*frame-index*))
  (let* ((env sys:*frame-environment*)
         (frame sys:*frame-index*)
         (length (sys:stack-frame-length frame env))
         (index
          (cond ((numberp name-or-number)
                 (if (< -1 name-or-number length)
                     name-or-number))
                ((symbolp name-or-number)
                 (loop for i from 0 to length
                       for nam = (sys:stack-frame-local-name frame env i)
                       doing
                   (if (and (symbolp nam)
                            (search (string name-or-number) (string nam)))
                       (return i)))))))
    (when index
      (sys:stack-frame-local-value frame env index))))


;; This only works for compiled functions.  See LUCID::INTERPRETED-FUNCTION-ALL-LOCAL-NAMES.
;; - fred 5/13/93

;; This didn't work in the one example I tried.  I did a break, backup the stack, looked at
;; the locals with :v, and then attempted to get one of them.  It didn't pan out.  - ben 5/13/93

;; Maybe it works now. (fmw 24-Aug-93)



;;; The function `sp' either returns or prints the symbol-plist of symbol.  If
;;; kb? is given, then that kb-specific plist is returned.

(defun sp (&optional (symbol *) verbose? kb?)
  (declare (special *current-kb-specific-property-list-property-name*))

  (let ((plist (if kb? (get symbol kb?) (symbol-plist symbol))))
    (cond
      ((null verbose?)
       plist)
      (t
       (if kb?
           (format *debug-io* "~&;; (get '~s '~s)" symbol kb?)
           (format *debug-io* "~&;; (symbol-plist '~S)" symbol))

       (describe-plist plist :stream *debug-io*
                       :kb-property *current-kb-specific-property-list-property-name*)

       ;; Pretend a mess of other stuff might be on the PList..
       (when verbose?
         (when (fboundp symbol)
           (cond
             ((macro-function symbol)
              (describe-slot-in-frame-or-structure
               nil nil 'macro-function (macro-function symbol)))
             (t
              (describe-slot-in-frame-or-structure
               nil nil 'symbol-function (symbol-function symbol)))))
         (when (boundp symbol)
           (describe-slot-in-frame-or-structure
            nil nil 'symbol-value (symbol-value symbol)))
         (when (special-variable-p symbol)
           (describe-slot-in-frame-or-structure
            nil nil 'special-variable-p t)))
       (when (fboundp 'make-new-value-for-*-if-appropriate) ; KLudge.
         (format *debug-io* "~&; plist is in ~A" symbol)
         (funcall 'make-new-value-for-*-if-appropriate plist))
       (values)))))



;;; The function `describe-plist' describes a plist like a structure.

(defun describe-plist (plist &key (stream *standard-output*) (indent 1) kb-property)
  (loop with *print-length* = 5
        with *print-case* = :downcase
        with *print-level* = 3
        for (key value) on plist by #'cddr
        as index from 0 by 2
        do
    (cond ((eq key kb-property)
           (describe-slot-in-frame-or-structure index nil key value
                                                :indent indent
                                                :stream stream
                                                :printer #'print-as-structure)
           (describe-plist value :stream stream
                           :indent (+ indent 2)
                           :kb-property kb-property))
          (t
           (describe-slot-in-frame-or-structure index nil key value
                                                :indent indent :stream stream)))))




;;; `Describe-slot-in-frame-or-structure' is the single bottleneck responsible
;;; for the pretty format in which we print "slots" of things.

(defun describe-slot-in-frame-or-structure
    (array-index? user-vector-index? slot-name slot-value
                  &key (stream *standard-output*) (indent 1) (printer nil))
  (let ((index-string
          (format nil "~a"
                  (or array-index?
                      (if user-vector-index?
                          (format nil "U ~a" user-vector-index?))
                      "-"))))

    (format stream
            ;; indent 2 spaces, 50 spaces for slot name, at least
            ;; 2 leading ...'s, e.g.
            ;; [0] title .......... taxi-driver
            ;; [1] director ....... "Martin Scorcese"
            "~&~v,,,' a[~a] ~vT~(~a~) ~v,,,'.a.. "
            indent ""
            index-string
            (+ 6 indent)
            slot-name
            (max 0 (- 50 (length (string slot-name))))
            "")

    (cond (printer
           (funcall printer slot-value stream))
          ((current-system-case
             (ab (evaluation-value-p-function slot-value))
             (t nil))
           (let ((*print-pretty* nil))
             (format stream "~s" slot-value)))
          (t
           (format stream "~s" slot-value)))))





;;; The macro `formatd' prints the values of its arguments, labeled by the
;;; arguments themselves, to formatd-output-stream.  Strings and quoted symbols
;;; can be used as additional labels. If the first argument is a string which
;;; looks like a format string, then formatd acts just like (format t ...).

(defmacro formatd (&rest exps)
  (let ((fmt
          (cond ((and (stringp (car exps)) (find #\~ (car exps)))
                 (prog1 (car exps)
                   (setq exps (cdr exps))))
                (t
                 (with-output-to-string (s)
                   (format s "~~&")
                   (dolist (e exps)
                     (cond ((not (constantp e))
                            (format s "~a = ~~s " e))
                           ((and (consp e) (eq (car e) 'quote))
                            (format s "~a " (cadr e)))
                           (t
                            (format s "~a " e))))
                   (format s "~~%")))))
        (args (loop for e in exps unless (constantp e) collect e)))
    `(formatd-1 ,fmt ,@args)))

;; Set to NIL to disable formatd output.

(defvar formatd-output-stream t)

(defun formatd-1 (fmt &rest args)
  (when formatd-output-stream
    (apply (lisp-format) formatd-output-stream fmt args)
    (first args)))



;;; `formatd-table' is (obviously) a copy of formatd which prints in a format
;;; I (jv) like better - one variable per line, with the variable name in a
;;; specified field.  Note that it cannot be disabled easily.

(defmacro formatd-table (&rest exps)
  (let ((fmt (with-output-to-string (s)
               (format s "~~&")
               (dolist (e exps)
                 (cond ((not (constantp e))
                        (format s ";; ~12a = ~~s~%" e))
                       ((and (consp e) (eq (car e) 'quote))
                        (format s "~a " (cadr e)))
                       (t
                        (format s "~a " e))))
               (format s "~~%")))
        (args (loop for e in exps unless (constantp e) collect e)))
    `(formatd-1 ,fmt ,@args)))





;;; The function `pp' pretty-prints its argument with circularity detection and
;;; without limits on list length or depth.

(defun pp (&optional (form *) (circle t))
  (fresh-line)
  (write form :pretty t :level nil :length nil :circle circle)
  (values))



;;; The function `ppl' pretty-prints a list like a structure.

(defun ppl (&optional (list *))
  (fresh-line)
  (cond ((consp list)
         (loop for element in list
               for i from 0
               doing
           (format t "[~d] " i)
           (write element :pretty t :level nil :length nil :circle t)
           (terpri)))
        (t
         (pp list)))
  (values))


;;; `all-of' - "pp" claims to print without limits on list length or depth,
;;; but, at least inside the debugger, that is not the case.  "all-of" does
;;; have limits, but they're fairly large.  Also, it prints in lower case
;;; which I think is easier to read for large lists.  - jv

(defun all-of (some-tree &optional (fresh-line-p t) (circle-p nil))
  (when fresh-line-p
    (fresh-line))
  (let ((*print-case* :downcase)
        (*print-level* 30)
        (*print-length* 1000)
        #+lucid (lcl:*debug-print-level* 30)
        #+lucid (lcl:*debug-print-length* 1000))
    (write some-tree :pretty t :circle circle-p))
  (values))



(defmacro mx (&optional form)
  (if form
      `(all-of (macroexpand-1 ',form))
      `(loop for form = (read) until (atom form)
             initially (format t "~&MX> ")
             do
         (format t "=>~&")
         (all-of (macroexpand-1 form))
         (format t "~&MX> "))))



;;; The function `vl' returns a list of the top level elements of vector.

(defun vl (&optional (vector *) limit)
  (loop for i from 0 below (min (length vector) (or limit 9999999))
        collect (aref vector i)))



;;; The function `i' invokes the inspector upon X.

(defun i (&optional (n *))
  (inspect n))



;;; The function `i*' invokes inspect upon X.

(defun i* (&optional (x *))
  (inspect x))




;;; `apr' ... Similar to APROPOS.  Only takes one optional argument after the
;;; first: ab-package-only?.  If ab-package-only? is true, it only searches
;;; in the AB package; otherwise, it searches globally.
                                                ;

;;; `apr2' is similar to apr, but the second arg, 2nd-string-or-symbol, is required
;;; and is a second string that must be found in a symbol to match.  The
;;; third arg, ab-package-only?, is optional and means the same thing as it
;;; ab-package-only? does in the function APR, above.


(defun apr (string-or-symbol &optional ab-package-only?)
  (if ab-package-only?
      (do-symbols (symbol (find-package 'ab))
        (if (apr-1 symbol string-or-symbol)
            (print-apr-match symbol)))
      (do-all-symbols (symbol)
        (if (apr-1 symbol string-or-symbol)
            (print-apr-match symbol)))))

(defun apr2 (1st-string-or-symbol 2nd-string-or-symbol
             &optional ab-package-only?)
  (if ab-package-only?
      (do-symbols (symbol (find-package 'ab))
        (if (apr-1 symbol 1st-string-or-symbol)
            (if (apr-1 symbol 2nd-string-or-symbol)
            (print-apr-match symbol))))
      (do-all-symbols (symbol)
        (if (apr-1 symbol 1st-string-or-symbol)
            (if (apr-1 symbol 2nd-string-or-symbol)
            (print-apr-match symbol))))))



(defun apr-1 (symbol string-or-symbol)
  (search (string string-or-symbol) (string symbol)))

(defun print-apr-match (symbol)
  (terpri)
  (if (not (eq (symbol-package symbol) *package*))
      (progn
        (princ (string
                 (package-name
                   (symbol-package symbol))))
        (princ ":")))
  (princ (symbol-name symbol))
  (loop repeat (max 1 (- 40
                         (+ (if (not (eq (symbol-package symbol) *package*))
                                (+ 1 (length (string
                                               (package-name
                                                 (symbol-package symbol)))))
                                0)
                            (length (symbol-name symbol)))))
        do (write-char #\space))
  (let ((anything? nil))
    (when (fboundp symbol)
      (if anything? (princ ", "))
      (princ (cond
               ((functionp symbol)
                "function")
               ((special-form-p symbol)
                "special form")
               (t "macro")))
      (setq anything? t))
    (when (boundp symbol)
      (if anything? (princ ", "))
      (princ "bound: ")
      (let ((*print-level* 3) (*print-length* 3)
            (symbol-value (symbol-value symbol)))
        (if (or (numberp symbol-value)
                (symbolp symbol-value)
                (arrayp symbol-value))
            (prin1 symbol-value)
            (let ((string-of-output
                    (with-output-to-string (output-stream)
                      (prin1 symbol-value output-stream))))
              (if (> (length string-of-output) 32)
                  (progn
                    (write-string
                      string-of-output *standard-output*
                      :end (min (length string-of-output)
                                30))
                    (write-string "..."))
                  (write-string string-of-output)))))
      (setq anything? t))
    (when (symbol-plist symbol)
      (if anything? (princ ", "))
      (princ "plist")
      (setq anything? t))))







;;;; Source file tracking



(defun modules-of-symbol (symbol &optional type)
  #+lucid
  (remove-duplicates
    (loop for (type . source-pathname) in (lcl:get-source-file symbol type t)
          collect (intern (string-upcase (pathname-name source-pathname)))))
  #-lucid (declare (ignore symbol type)))


(defun module-of-symbol (symbol &optional (type 'function))
  #+lucid
  (let ((pathname? (lcl:get-source-file symbol type)))
    (when pathname?
      (intern (string-upcase (pathname-name pathname?)))))
  #-lucid (declare (ignore symbol type)))

;; Type should be function, variable, class, etc.


(defun index?-of-module (module &optional (system-name 'ab))
  (position module (get system-name 'lisp-modules-to-be-loaded)))

(defun symbol-defined-after-module (symbol module-or-index)
  (let* ((defining-modules? (modules-of-symbol symbol))
         (module-position?
          (if (symbolp module-or-index)
              (index?-of-module module-or-index)
              module-or-index)))
    (cond
      ((null defining-modules?)
       nil)
      ((null module-position?)
       t)
      (t
       (loop for defining-module in defining-modules?
             as defining-module-position = (index?-of-module defining-module)
             thereis (<f module-position? defining-module-position))))))

;; This is forward-reference-p.


(defun systems-of-symbol (symbol &optional (all-systems '(ab telewindows gsi)))
  "List the systems in which SYMBOL is defined"
  (let ((modules (modules-of-symbol symbol)))
    (loop for sys in all-systems
          when (loop for module in modules
                     thereis (memq module (get sys 'lisp-modules-to-be-loaded)))
            collect (if (eq sys 'ab) 'g2 sys))))



(defun module-functions (module &key decache (system-name 'ab))
  "A list of all of the functions defined in the given module. Cached.
 Does not include macro expanders."
  (let ((package (find-package "AB"))
        (list ()))
    (unless (index?-of-module module system-name)
      (warn "~s is not a known module of system ~s." module system-name))
    (when decache
      (setf (get module 'functions) nil))
    (unless (get module 'functions)
      (do-symbols (symbol package)
        (when (and (fboundp symbol)
                   (not (macro-function symbol))
                   (eq (symbol-package symbol) package)
                   (memq module (modules-of-symbol symbol)))
          (push symbol list)))
      (setf (get module 'functions) (sort list #'string-lessp)))
    (get module 'functions)))



(defmacro trace-module (module)
  "Trace all of the functions defined in the given module."
  `(trace ,@(module-functions module)))


(defmacro untrace-module (module)
  "Untrace all of the functions defined in the given module."
  `(untrace ,@(module-functions module)))


;; There is so much info in the trace output.  Ought to save into a browsable,
;; hierarchical database...



;;;; Other stuff



;;; The function `lf' reloads foreign object files from your ext/c directory.
;;; Example: (lf 'xwindows).

(defparameter build-tree-root "gensym/bt")

(defun lf (&rest files)
  #-lucid (declare (ignore files))
  #+lucid
  (let* ((sandbox (or (lcl:environment-variable "DSTBOX")
                      (lcl:environment-variable "SRCBOX")
                      (if (or (lcl:environment-variable "SPIN_ID")
                              (lcl:environment-variable "USER"))
                          (format nil "/~a/~a"
                                  build-tree-root
                                  (or (lcl:environment-variable "SPIN_ID")
                                      (lcl:environment-variable "USER"))))))
         (files (loop for file in files
                      collect (format nil "~(~a/ext/c/~a.o~)" sandbox file))))
    (lcl:load-foreign-files files '("-lX11" "-lm"))
    files))



(defmacro with-debugging-upon-condition
          (condition trace-functions break-form? &body body)
  `(progn
     (when ,condition
       (trace ,@trace-functions)
       ,break-form?)
     ,@body
     (untrace)))



;;; `Breakon' ... `Unbreakon' ... like the Lisp machine's breakon facility except (1) that
;;; its database overlaps with that of trace (so, for example, untracing a function will
;;; remove the breakpoint from that function as well, and, for example, unbreakon and
;;; untrace with no arguments or with one argument do exactly the same thing), and
;;; (2) that it does not accept as an optional second arg an expression to evaluate
;;; as a condition for breaking.

#+lucid
(defun breakon (function-name &optional (when t))
  (eval `(trace
           (,function-name
              :break ,when
              :exitbreak ,when))))

;; Perhaps it is possible and may be even worth some effort to support more of the Lisp
;; machine's functionality.


#+lucid
(defun unbreakon (&optional function-name?)
  (eval `(untrace . ,function-name?)))


;;; The function `backtrace-on' prints a backtrace whenever the given function
;;; is entered

#+lucid
(defun backtrace-on (function-name &key (verbose t))
  (eval `(trace (,function-name :entry ((print-debugger-backtrace :verbose ,verbose))))))






;;;; Symbol search via ID database


(defparameter global-ID-file "/home/ab/g2/ID")


;;; The function `calling-expressions' searchs for forms which appear to "call"
;;; the given symbol, using the ID database to speed the search.  They are
;;; printed as they are found, and are also saved in found-forms and
;;; top-level-found-forms.

(defun calling-expressions (symbol &key top-level-forms (print t)
                                   (level 6) (length 5) (pretty t) alist)
  (let ((files (what-files-mention symbol))
        (aforms nil))
    (declare (special found-forms top-level-found-forms))
    (setq found-forms nil
          top-level-found-forms nil)
    (loop for file in files
          as module = (intern (string-upcase (pathname-name file)))
          when print
            do (format t ";; ~a:~%" file)
          as file-forms = NIL
          doing
      (with-open-file (stream file :direction :input)
        (loop for count from 0
              as pos = (file-position stream)
              as sexp = (read stream nil stream)
              until (eq sexp stream)
              as subforms = (cond ((atom sexp)
                                   nil)
                                  ((memq (car sexp) ; Ignore some top-level forms.
                                         '(declare-forward-reference
                                           declare-forward-references
                                           declare-forward-references-to-module))
                                   nil)
                                  ((eq (car sexp) 'progn) ; Treat forms in progn as top-level
                                   (cdr sexp))
                                  (t
                                   (list sexp)))
              doing
          (loop for subform in subforms
                as forms = (find-callers-in-tree symbol subform)
                doing
            (when forms
              (when alist
                (let ((defn (cond ((atom subform) subform)
                                  ((consp (cadr subform)) (caadr subform))
                                  (t (cadr subform)))))
                  (push (list* module defn count (copy-list forms)) aforms)))
              (push subform top-level-found-forms)
              (setq found-forms (nconc found-forms forms))
              (cond ((not print))
                    (top-level-forms
                     (write subform :pretty pretty :case :downcase :length length :level level)
                     (terpri))
                    (t
                     (loop for e in forms doing
                       (write e :pretty pretty :case :downcase :length length :level level)
                       (terpri)))))))))
    (cond (print
           (format t "The complete lists are in found-forms and top-level-found-forms")
           (values))
          (top-level-forms
           top-level-found-forms)
          (alist
           (nreverse aforms))
          (t
           found-forms))))

#+lucid
(defun calling-patterns (func &key modules (defs t) exprs)
  (let* ((arglist (loop for arg in (fn-arglist func)
                        until (eq arg '&aux)
                        unless (memq arg lambda-list-keywords)
                          collect (if (atom arg) arg (car arg))))
         (n (length arglist)))
    (loop for i below n
          as arg = (nth i arglist)
          doing
      (loop repeat i doing (princ " | "))
      (if arg (format t " ~a" arg))
      (terpri))
    (let ((alist (calling-expressions func :print nil :alist t)))
      (loop for (module defn pos . forms) in alist doing
        (loop for form in forms doing
          (loop for i below n
                as e = (nth i (cdr form))
                doing
            (if e (princ " X ") (princ " . ")))
          (when modules
            (format t "~12a" module))
          (when defs
            (format t " ~s" defn))
          (when exprs
            (format t " ~a" (subseq (lisp:princ-to-string (cdr form)) 0 45)))
          (terpri)))
      (printing-random-object (alist *standard-output*)
        (format t "ALIST"))
      (values))))

#-lucid
(defun calling-patterns (func &key modules (defs t) exprs)
  (declare (ignore func modules defs exprs))
  (warn "Function calling-patterns not implemented in this Lisp."))

(defun find-callers-in-tree (symbol tree)
  (cond ((atom tree)
         nil)
        ((cdr (last tree))                                    ; Dotted list.
         nil)
        ((eq (car tree) symbol)
         (cons tree
               (loop for exp in (cdr tree)
                     nconcing (find-callers-in-tree symbol exp))))
        (t
         (loop for exp in (cdr tree)
               nconcing (find-callers-in-tree symbol exp)))))


(defun read-file (file &key verbose)
  (with-open-file (stream file :direction :input)
    (loop for sexp = (read stream nil stream)
          as i from 0
          until (eq sexp stream)
          when verbose
            do (format t "[~d] ~s~%" i sexp)
          collect sexp)))


(defparameter lid-program "/home/ab/bin/lid")


(defun what-files-mention (symbol)
  #-lucid (declare (ignore symbol))
  #-lucid (error "Implement what-files-mention for this lisp.")
  #+lucid
  (let ((tem "/tmp/lid.tmp"))

    (cond ((not (probe-file lid-program))
           (error "The lid program ~s was not found" lid-program))

          ((probe-file "ID")
           (lcl:shell (format nil "~a ~(~a~) >~a"
                              lid-program symbol tem)))
          (t
           (lcl:shell (format nil "~a -f~a -c ~(~a~) >~a"
                              lid-program global-ID-file symbol tem))))

    (mapcar 'string-downcase (cdr (read-file tem)))))




;;; The function `find-lisp-object' prints the lists and structures which
;;; reference the given object. It's a lot faster than `find-thing-in-g2'
;;; but gives less information

(defun find-lisp-object (object)
  #+lucid
  (sys:map-objects
    #'(lambda (x)
        (cond ((consp x)
               (cond ((eq (car x) object)
                      (format t "Car of ")
                      (print-as-structure x)
                      (write-string " = ")
                      (write x :length 2 :level 1)
                      (terpri))
                     ((eq (cdr x) object)
                      (format t "Cdr of ")
                      (print-as-structure x)
                      (write-string " = ")
                      (write x :length 2 :level 1)
                      (terpri))))

              ((stringp x))
              ((simple-vector-p x)
               (loop for i below (length x)
                     when (eq object (svref x i))
                       do (format t "Elt ~d of ~s~%" i x)))))
      :dynamic t
      :pointer t)
    object)

(declare-forward-reference framep-function function)

(defun find-lisp-object-in-frame (object depth)
  (format t "~% ~a: ~a" object depth)
  #+lucid
  (let ((top-list nil)
        (not-found? t)
        (verbose? nil))
    (sys:map-objects
      #'(lambda (x)
          (cond ((and (consp x)
                                        ;;(not (memq x replenished-conses))
                      )
                 (cond ((eq (car x) object)
                        (when (or (null top-list)
                                  (memq top-list x))
                          (setq top-list x))
                        (when verbose?
                          (format t "Car of ")

                          (print-as-structure x)
                          (write-string " = ")
                          (write x :length 2 :level 1)
                          (terpri)))
                       ((eq (cdr x) object)
                        (when (or (null top-list)
                                  (memq top-list x))
                          (setq top-list x))
                        (when verbose?
                          (format t "Cdr of ")
                          (print-as-structure x)
                          (write-string " = ")
                          (write x :length 2 :level 1)
                          (terpri)))))

                (nil (stringp x))
                ((framep-function  x)
                 (loop for i below (length x)
                       do

                   (when (or (eq object (svref x i))
                             (and (listp (svref x i))
                                  (memq object (svref x i))))
                     (setq not-found? nil)
                     (format t "Elt ~d of ~s~%" i x))))
                ((simple-vector-p x)
                 ;; there are
                 (when (< (length x ) 200)
                   (loop for i below (length x)
                         do
                     (when (eq object (svref x i))
                       (format t "Elt ~d of ~s~%" i x)
                       (setq not-found? nil)))))))
      :dynamic t
      :pointer t)
    (when (and not-found? top-list
               (< depth 3))
;      (format t "~% top list ~a not found ~a" top-list not-found?)
      (find-lisp-object-in-frame top-list (+ depth 1)))
    object))

;;; `lists-searched?' and `tree-search-for-item' are support for
;;; `find-thing-in-g2'. Preventing it from looping eternally

(defvar lists-searched? nil)

(defun tree-search-for-item (item tree)
  (let ((result? nil))
    (unless (memq tree lists-searched?)
      (push tree lists-searched?)
      (cond ((consp tree)
             (loop with element = (car tree)
                   with next? = (cdr tree)
                   while element
                   until result?
                   do
               (cond ((consp element)
                      (setq result? (tree-search-for-item item element)))
                     (t
                      (setq result? (eq element item))))
               (setq element next?)
               (cond ((consp next?)
                      (setq next? (cdr next?)))
                     (t (setq next? nil)))))
            (t
             (setq result? (eq item tree)))))
    result?))


#|
;;; the loop path used in `find-thing-in-g2' does not exist when this file is
;;; compiled, if you need it compile it when the path is defined

(defun find-thing-in-g2 (a-thing)
  (when lists-searched?
    (setq lists-searched? nil))
  (loop for b being each class-instance of 'block
        for count from 0
        as len = (length b)
        doing
    (loop for i below len
          with found?
          as el = (aref b i)
          do
      (cond ((consp el)
             (when (tree-search-for-item a-thing el)
               (setq found? t)))
            ((eq el a-thing)
             (setq found? t))
            (t (setq found? nil)))
      (when lists-searched?
        (reclaim-slot-value-list lists-searched?)
        (setq lists-searched? nil))
      (cond (found?
             (format t "~%~s ~s ~s" b i el))
            ((= (mod count 500) 0)
             (format t "."))))
        finally
          (format t "~% ~aitems checked" count)))
|#



;;;; Graphers


;;; The function `triple-graph' draws three-layer graph centered on the given
;;; node.

(defun triple-graph (name superiors-name inferiors-name
                          node superiors-function inferiors-function
                          &optional (name-function #'identity))
  (let* ((superiors
           (funcall superiors-function node))
         (middles
           (list node))
         (inferiors
           (funcall inferiors-function node))
         (fmt
           (format nil "~~~d@a  ~~~da  ~~~da~~%"
                   (max 10 (loop for thing in superiors
                                 maximize (length (string (funcall name-function thing)))))
                   (max 10 (loop for thing in middles
                                 maximize (length (string (funcall name-function thing)))))
                   (max 10 (loop for thing in inferiors
                                 maximize (length (string (funcall name-function thing))))))))

    (format t fmt superiors-name name inferiors-name)
    (format t fmt (fill (concatenate 'string superiors-name) #\-)
            (fill (concatenate 'string name) #\-)
            (fill (concatenate 'string inferiors-name) #\-))

    (loop while (or superiors middles inferiors)
          as sup = (pop superiors)
          as mid = (pop middles)
          as inf = (pop inferiors)
          doing
      (format t fmt (if sup (funcall name-function sup) "")
              (if mid (funcall name-function mid) "")
              (if inf (funcall name-function inf) "")))
    node))



;;; The function `print-random-tree' is a simple tree printing routine, which
;;; notes levels by indentation and can abbreviate nodes with many inferiors.

(defun print-random-tree
    (tree inferiors                    ; Function on tree node.
          &key
          (printer #'princ)            ; Function on (node stream)
          depth                            ; Maximum depth.
          fanout                    ; Maximum fanout.
          duplicates                    ; Mark duplicate nodes
          (indent 3)                    ; Indentation per level.
          (stream *standard-output*))
  "Print a tree defined by given inferiors fcn, just using indentation."
  (let ((nodes (make-hash-table)))
    (labels ((indent (amount)
               (fresh-line stream)
               (dotimes (i amount)
                 (princ " " stream)))

             (pnode (node indent)
               (indent indent)
               (funcall printer node stream)
               (when (and duplicates (gethash node nodes))
                 (write-string " ***" stream)))

             (ptree (tree deep)
               (when (or (null depth) (<= deep depth))
                 (pnode tree (* deep indent))

                 (let ((inferiors
                         (unless (gethash tree nodes)
                           (funcall inferiors tree))))
                   (cond ((and fanout (> (length inferiors) fanout))
                          (format stream "...[~d]" (length inferiors)))
                         (t
                          (dolist (i inferiors)
                            (ptree i (1+ deep))))))
                 (when duplicates
                   (setf (gethash tree nodes) t)))))

      (ptree tree 0)
      tree)))




;;;; Smart tracing


;;; The defparameter `kinds-of-gtrace' is a list of (name doc {variable}).

(defparameter kinds-of-gtrace nil)


;;; The defvar `active-gtrace' is a list of the trace kinds which are
;;; now active.

(defvar active-gtrace nil)


;;; The defvar `interesting-block-for-tracing' may be set to a block for which
;;; tracing is filtered.

(defvar interesting-block-for-tracing nil)


;;; The macro `def-gtrace' defines a new kind of tracing with the given name.
;;; If a controlling-variable is given, then this sort of tracing is enabled by
;;; setting the variable to T.

(defmacro def-gtrace (name &optional doc-string controlling-variable)
  `(def-gtrace-1 ',name ',doc-string ',controlling-variable))

(defmacro def-multiple-gtrace (&rest tuples)
  `(progn
     ,@(loop for tuple in tuples
             collect `(def-trace ,@tuple))))



;;; The macro `gtrace' enables the given kinds of tracing.

(defmacro gtrace (&rest kinds)
  `(gtrace-1 ',kinds t))


;;; The macro `ungtrace' disables the given kinds of tracing.

(defmacro ungtrace (&rest kinds)
  `(gtrace-1 ',kinds nil))



(defun def-gtrace-1 (name doc-string controlling-variable)
  (let ((spot (assq name kinds-of-gtrace)))
    (if spot
        (setf (second spot) doc-string
              (third spot) controlling-variable)
        (setf kinds-of-gtrace
              (nconc kinds-of-gtrace
                     (list (list name doc-string controlling-variable)))))
    name))


(defun gtrace-1 (kinds trace-p)
  (flet ((doc ()
           (format t ";;; Kinds of tracing: ~{~<~%;;;~:; ~A~>~^,~}.~%"
                   (mapcar 'car kinds-of-gtrace))
           (format t ";;; Do (gtrace :help) for more info.~%")
           (values))
         (help ()
           (loop for (name doc) in kinds-of-gtrace doing
             (format t "~&~s~25t~a" name doc))
           (values))
         (cur ()
           (format t ";;; Currently traced: ~{~<~%;;;~:; ~A~>~^,~}."
                   (cond ((null active-gtrace)
                          '("nothing"))
                         ((eq active-gtrace t)
                          '("everything"))
                         (t
                          active-gtrace)))
           (values)))
    (cond ((equal kinds '(:help))
           (HELP))
          ((and (null kinds) trace-p)
           (DOC) (CUR))
          ((and (not (null kinds))
                (set-difference kinds (mapcar 'car kinds-of-gtrace)))
           (format t "Unknown kind of draw tracing ~S~%"
                   (set-difference kinds (mapcar 'car kinds-of-gtrace)))
           (DOC))
          (t
           (dolist (kind (or kinds '(t)))
             (trace-this-kind kind trace-p))
           active-gtrace))))


(defun trace-this-kind (kind trace-p)
  (cond ((eq kind 't)
         (setq active-gtrace trace-p)
         (loop for (nil nil var?) in kinds-of-gtrace
               when var?
                 do (set var? trace-p)))
        (t
         (if trace-p
             (pushnew kind active-gtrace)
             (setq active-gtrace (remove kind active-gtrace)))

         ;; Special cases controlled by other defvars.
         (let ((var? (third (assoc kind kinds-of-gtrace))))
           (when var?
             (set var? trace-p))))))



(defun gtrace-active-p (kind block?)
  (and (or (eq active-gtrace t)
           (memq kind active-gtrace))

       (or (null interesting-block-for-tracing)
           (null block?)
           (eq interesting-block-for-tracing block?))))



(defun gtrace-print (kind closure &key block)
  (when (gtrace-active-p kind block)
    (when (memq 'backtrace active-gtrace)
      (format t "~s " (make-lisp-backtrace)))
    ;; Indent by lcl:*trace-level* ?
    (funcall closure)))

;; All the tracing passes thru this function, so that we could save output into
;; a string, etc.





;;; The macro `with-tracing-1' is a helper macro for with-tracing, defined
;;; in glbasics.  It's only used when in development mode.

(defmacro with-tracing-1 ((kind &key block) &body body)
  `(gtrace-print ',kind #'(lambda () ,@body) :block ,block))







;;;; Debugging help




;;; `db-help' will emit a list of useful commands for
;;; use when debugging G2.

(defun db-help ()
  (format t "~
These commands are implemented by AB to help debugging.
Some of these are also available in TW.

   ;; Generally useful
   (gon <index-or-type>)  -- get most recent outline node of index or type
   (@  <index-or-type>) -- aka gon
   (d <whatever>)   -- Describe. Argument defaults to *.
   (i <whatever>)   -- Inspect
   (pp <whatever>)  -- Pretty print. Argument defaults to *.
   (sp <symbol> &optional vebose)  -- Get symbol's property, and more.
   (show-*-history)
   ({symbol,symbol,pattern}-search ...)  -- read all Source forms, and search
   (ci &optional <class-name> (offset 0))  -- Latest instance of that class
   (show-command-journal)  -- History of all UI commands user has done.
   (calling-patterns <fun>) -- List all patterns of arguments supplied to FUN (a symbol).

   ;; Debugger
   (breakon <symbol>)
   (unbreakon <symbol>)
   (trace <symbol>)  -- macro
   (a <index-or-symbol)  -- get this arg of current debugger frame
   (l <index-or-symbol)  -- get this local of current debugger frame
   (v <index>)           -- return value N (TI only)
   (dx)  -- Show current named dynamic extents
   (dx t)  -- show bindings
   (dx <name>) -- show bindings of this name.
   (collect-backtrace-into-list)  or  (backtrace)
   (backtrace-on <func>) -- Verbose backtracing, Lucid only.

   ;; Looking at Lattice
   (calling-expressions <function>)  -- print source forms whose CAR is <function>
   (who-calls <function>)
   (who-is-called <function>)  -- inverse of who-calls.
   (outline-call-graph <function>)  -- outline the lexical call tree
   (outline-inverse-call-graph <function>) -- inverse of that
   (outline-drawing <drawable>)  -- show what gets drawn in what order
   (outline-subblocks <block>)  -- outline the subblock hierarchy
   (outline-type-description <type-name>) -- outline ab structure, :include topology.

   ;; Misc
   most-recent-defun-name -- the latest defun, defmacro etc. that was macroexpanded
   (dcs)   -- describe some workstation's context stack.
   (list-magic-arguments &optional mouse-pointer)
   (vl)    -- turn a vector into a list.
   (apr string-or-symbol &optional ab-package-only?))  -- apropos
   (apr2 string-or-symbol string-or-symbol &optional ab-package-only?)) -- apropos squared
   (print-post-mortem-checkpoints)  -- the journal of recent major activities.
   map-over-global-property    -- find all symbols with a given property.

   ;; Memory Problems
   (compare-memory-allocation)  -- Reports Pool changes since last call.
   (memory)    -- report for names-of-interesting-system-object-pools
   (g2-memory-usage)  -- See definition.
   ({{en,dis}able-,initialize-,}check-memory)  -- See these!
   object-pool-meters  -- 200+ pool descriptions.
   (get-memory-profile-of-item-lisp-side <frame>) --> <memory-profile>
"
  ))


#+lucid
(add-all-lucid-debugger-commands)



#+lucid
(progn

;;; See /home/lucid/lucid41/wizards.doc

(defun procedure-references-object-p (procedure object)
  (loop for i fixnum from sys:procedure-literals below (sys:procedure-length procedure)
        when (eq object (sys:procedure-ref procedure i))
          return t
        finally (return nil)))

(defun names-of-procedures-referencing-object (ref-object)
  (let ((names nil))
    (sys:map-objects #'(lambda (object)
                         (when (and (sys:procedurep object)
                                    (procedure-references-object-p object ref-object))
                           (push (sys:procedure-ref object sys:procedure-symbol) names)))
                     :all t)
    (dolist (name names)
      (if (not (symbolp name))
          (format t "~&~S~%" name)
          (when (procedure-references-object-p (symbol-function name) ref-object)
            (format t "~&~S~A~%" name (if (macro-function name)
                                      "  Macro" ""))))))
  (values))

;;; Example use:
;;; (names-of-procedures-referencing-object 'available-slot-value-conses)

(defun objects-referencing-object (ref-object)
  (let ((refs nil))
    (sys:map-objects #'(lambda (object)
                         (when (typecase object
                                 (symbol
                                  (and (boundp object)
                                       (eq ref-object (symbol-value object))))
                                 (cons
                                  (or (eq ref-object (car object))
                                      (eq ref-object (cdr object))))
                                 ((array t (*))
                                  (loop for i from 0 below (length object)
                                        when (eq ref-object (aref object i))
                                          return t
                                        finally (return nil))))
                           (pushnew object refs)))
                     :pointer t)
    refs))

(defun show-paths-to-object (ref-object)
  (let ((ab (find-package "AB"))
        (table (make-hash-table :test 'eq)))
    (labels ((path-to-object-p (object)
               (or (eq ref-object object)
                   (let ((found (gethash object table 'unknown)))
                     (case found
                       ((t nil) found)
                       (on-stack nil)
                       (unknown
                        (setf (gethash object table) 'on-stack)
                        (setf (gethash object table)
                              (typecase object
                                (cons
                                 (or (path-to-object-p (car object))
                                     (path-to-object-p (cdr object))))
                                ((array t (*))
                                 (loop for i from 0 below (length object)
                                       when (path-to-object-p (aref object i))
                                         return t
                                       finally (return nil)))))))))))
      (do-symbols (sym ab)
        (when (and (boundp sym)
                   (path-to-object-p (symbol-value sym)))
          (print sym))))))

) ; progn #+lucid


#+lucid
(progn

(defvar *current-backtrace* nil)

(defvar *cons-table* nil)

(defun show-bad-conses ()
  (when *cons-table*
    (maphash #'(lambda (cons bt-info)
                 (declare (ignore cons))
                 (when (and (consp bt-info)
                            (or (symbolp (car bt-info))
                                (cddr bt-info)))
                   (format t "~&Alloc ~S, Free ~S~%"
                           (car bt-info) (cdr bt-info))))
             *cons-table*)))

(defun note-reclaimed-cons (cons)
  (let* ((bt (gethash cons *cons-table*))
         (a (cond ((consp bt)
                   (push *current-backtrace* (cdr bt))
                   (car bt))
                  (t
                   (setf (gethash cons *cons-table*)
                         (cons bt (list *current-backtrace*)))
                   bt))))
    (unless a
      (break))))

(defun note-cons-pool-source (pool cons-list)
  (loop for cons on cons-list
        do (setf (gethash cons *cons-table*) pool)))

(defun note-new-cons (cons)
  (setf (gethash cons *cons-table*) *current-backtrace*)
  cons)

(defun note-new-list (list)
  (when (consp list)
    (note-new-cons list)
    (note-new-list (cdr list))))

(defun note-new-tree (tree)
  (when (consp tree)
    (note-new-cons tree)
    (note-new-tree (car tree))
    (note-new-tree (cdr tree))))

(defvar cons-checking-functions nil)

(defun install-consing-cons-checking-functions (names pool note-fn)
  #-defadvice
  (declare (ignore names pool note-fn))
  #+defadvice
  (dolist (fn names nil)
    (let* ((fun (intern (format nil fn pool)))
           (template
             `(defadvice (<dummy> cons-checking) (&rest args)
                (let ((result (apply-advice-continue args))
                      (*current-backtrace* (make-lisp-backtrace)))
                  (,note-fn result)
                  result))))
      (push fun cons-checking-functions)
      (install-advice fun (subst fun '<dummy> (copy-tree template))))))

(defun install-reclaiming-cons-checking-functions (names pool)
  #-defadvice
  (declare (ignore names pool))
  #+defadvice
  (let ((available-conses (name-of-available-pool pool)))
    (dolist (fn names nil)
      (let* ((fun (intern (format nil fn pool)))
             (template
               `(defadvice (<dummy> cons-checking) (&rest args)
                  (let* ((,available-conses nil)
                         (result (apply-advice-continue args))
                         (*current-backtrace* (make-lisp-backtrace)))
                    (loop for cons on ,available-conses
                          do (note-reclaimed-cons cons))
                    result))))
        (push fun cons-checking-functions)
        (install-advice fun (subst fun '<dummy> (copy-tree template)))))))

(defun install-pool-cons-checking-functions (names pool)
  #-defadvice
  (declare (ignore names pool))
  #+defadvice
  (let ((available-conses (name-of-available-pool pool)))
    (dolist (fn names nil)
      (let* ((fun (intern (format nil fn pool)))
             (template
               `(defadvice (<dummy> cons-checking) (&rest args)
                  (let* ((result (apply-advice-continue args)))
                    (note-cons-pool-source ',pool ,available-conses)
                    result))))
        (push fun cons-checking-functions)
        (install-advice fun (subst fun '<dummy> (copy-tree template)))))))

(defvar marking-all-cons-origins nil)

(defun mark-all-cons-origins ()
  (declare (special object-pool-meters))
  (unless marking-all-cons-origins
    (setq marking-all-cons-origins t)
    (unless *cons-table* (setq *cons-table* (make-hash-table :test 'eq)))
    (dolist (p object-pool-meters)
      (when (eq (second p) 'cons)
        (install-pool-cons-checking-functions
          '("REPLENISH-~A-CONS-POOL" "REPLENISH-~A-LIST-POOL")
          (let* ((pool-name-string (string (first p)))
                 (pool (intern (subseq pool-name-string
                                       0
                                       (- (length pool-name-string)
                                          #.(length "-CONSES"))))))
            ;; look replenish-x-conses-pool to understand why we set the three variables and
            ;; no others
            (set (name-of-available-pool pool) nil)
            (set (name-of-available-pool-counter pool) nil)
            (set (name-of-available-pool-tail pool) nil)
            pool))))))

(defun start-cons-checking (pool)
  (unless *cons-table* (setq *cons-table* (make-hash-table :test 'eq)))
  #+lucid
  (setq maximum-backtrace-depth 25)
  (install-consing-cons-checking-functions
    '("~A-CONS-1") pool 'note-new-cons)
  (install-consing-cons-checking-functions
    '("MAKE-~A-LIST-1" "~A-LIST-2" "~A-LIST-3" "~A-LIST-4" "COPY-LIST-USING-~A-CONSES-1")
    pool 'note-new-list)
  (install-consing-cons-checking-functions
    '("COPY-TREE-USING-~A-CONSES-1")
    pool 'note-new-list)
  (install-reclaiming-cons-checking-functions
    '("RECLAIM-~A-CONS-1" "RECLAIM-~A-LIST-MACRO-FOR-DEVELOPMENT"
      "RECLAIM-~A-LIST-GIVEN-TAIL-FOR-DEVELOPMENT" "RECLAIM-~A-LIST*-1" "RECLAIM-~A-TREE-1")
    pool)
  (mark-all-cons-origins)
  pool)

)

;;; Cons-checking (TODO: merge it into above code for Lucid/Liquid CL)
;;; By Denis Budyak

;;; To enable cons-checking automatically, push :cons-checking onto *features* before loading 123.lisp
;;; Now we prefer to be conservative because many regression tests fail.
;;#+defadvice
;;(eval-when (:compile-toplevel :load-toplevel :execute)
;;  (pushnew :cons-checking *features*))

;; prevent an attempt to add defadvice manually
#+(and :cons-checking (not :defadvice))
 (error "cons-checking depends on portable defadvice facility which is unavailable here")

;; cons-checking-enabled-p has effect only when #+cons-checking 
;; 
;; General idea of cons-checking is to track current state of selected objects (not only conses) in terms
;; of memory allocation, that is, note allocations and de-allocations (reclamations) and record them to global hash-table.
;; Optionally, cons-checking can record history of (de)allocations and report violations of normal sequence of such events,
;; e.g. double reclaims, access to uninitialized objects and so on. 
;; In current state of the code, the order is sometimes violated so some pools are unavailable for checks.
;; 
;; The possible values are: 
;;   NIL - cons-checking disabled 
;;   root-name of the pool, e.g. 'gensym - cons-checking enabled for the pool designated
;;   t - cons-checking is enabled for all pools.
;;   Default is #+cons-checking t, #-cons-checking nil. 
;;     T is assigned in the (cons-checking-start-common-part) to avoid ambiguities 
;;     during setup phase.
;; 
;; Whatever you assign cons-checking-enabled-p to, you must do that before the creation of 
;; G2 "world of special variables", including memory manager. 
;; E.g. do that before call to ab::launch-ab,
;; or outside of the scope of tests::with-connection-test-environment, 
;; 
;; Don't change this variable's value while G2 world exists. 
;; 
(defvar cons-checking-enabled-p nil)

#+cons-checking
(progn

;; cons-state-state 
(deftype cons-checking-object-status ()
  '(member
    cons-checking-object-status-untracked 
    cons-checking-object-status-fresh-from-os ; obtained by replenish
    cons-checking-object-status-initialization-begun ; is recorded for some types only
    cons-checking-object-status-outstanding 
    cons-checking-object-status-reclaiming-begun ; is recorded for some types only
    cons-checking-object-status-reclaimed))

;; *cons-checking-log-settings* is a list of the following options:
;; 'backtrace - save backtrace. Extremely slow, maybe 100x!
;; 'counter - value of *global-allocation-operation-counter* 
(defparameter *cons-checking-log-settings* nil) 

;; debugging counter for global allocation operations.
;; If (member 'counter *cons-checking-log-settings*) 
;; and #+cons-checking
;; it is incremented at each (de) allocation and stored into allocation-operation. 
;; See also allocation-serial-number which is very similar, and sometimes better because operates on specific
;; pool only, so that probability of 'floating' results is reduced
(defvar *global-allocation-operation-counter* 0)

(defparameter *global-allocation-operation-counter-to-break-on* -1)

;; You can modify or advice this function to break if some condition 
;; is true when allocating or reclaiming. Function is called only when 
;; *cons-checking-log-settings* is true. It receives three arguments:
;;   - object being allocated or reclaimed
;;   - pool name (symbol)
;;   - record of type de/allocation-log-entry which contains the details of object
;; 
;; Condition can be formulated 
;; in terms of arguments and/or in terms of global variables such as: 
;; *global-allocation-operation-counter* ,
;;   when (member 'counter *cons-checking-log-settings*)
;; and/or *current-backtrace* , 
;;   when (member 'backtrace *cons-checking-log-settings*) . 
;; 
;; When reclaiming, function is called before wiping the object contents, so data contained in the object
;; can be used sometimes. 
;; 
;; Please note that operation of G2 is frequently non-deterministic. 
;; For instance, it is so when posting messages to the UI. Hence 
;; *global-allocation-operation-counter* floats around between different G2 sessions
;; running the same test case. Thus you might fail to get reproducible results 
;; if you use it directly. You might try to reset it as close as possible to the 
;; event under investigation and then, if you're lucky, you can get reproducable results. 
(defun maybe-break-on-global-allocation-operation-counter (object pool de/allocation-log-entry)
  (declare (ignorable object pool de/allocation-log-entry))
  (when (eql *global-allocation-operation-counter*
             *global-allocation-operation-counter-to-break-on*)
    (break "cons-checking: *global-allocation-operation-counter-to-break-on* reached")
    ))


;; cons-story is associated to cons
;; maybe caches current-backtrace and can be used when deciding to break
(defvar *current-backtrace* nil)

;; allocation-operation. Log entry of allocation/deallocation for a given cons
(cl:defstruct de/allocation-log-entry
  (operation (error "slot OPERATION not initialized"))
  ;; global serial number of allocation operation.
  (counter (when (member 'counter *cons-checking-log-settings*)
            (incf *global-allocation-operation-counter*)))
  ;; backtrace at that time
  (backtrace (when (member 'backtrace *cons-checking-log-settings*)
               (or *current-backtrace* (make-lisp-backtrace))))
  )

;; cons-story is associated to cons via *cons-table*
(cl:defstruct cons-story
  (status (error "slot status not initialized")
         :type cons-checking-object-status)
  pool
  (ob nil :type (cons de/allocation-log-entry)) ; operations and backtraces - list of 
  e  ; if true, normal sequence of events was violated for this object at least once. e contain a list of pools where the object was 
     ; immeditely before the violation happened. If it was not in the pool, :none is recorded
  ud ; user data - user can fill it with arbitrary data to help identifying offended objects
  )

; registry of functions with cons-checking advice installed. 
; we should check _all_ pools indeed
(defvar cons-checking-functions nil)

;; *cons-table* maps conses to the information of their story recorded in cons-story records (or to nil)
(defvar *cons-table* nil)


;; Controls what happens if cons-checker detects an error. Possible values are:
;; 'cerror - cerror is invoked
;; 'error - error is invoked
(defparameter *cons-checking-reaction-on-problem*
  #+under-test 'error ; for unit tests, err always
  #-under-test 'cerror  ; for other testing, disable it's currently too paranoid. Will enable it back in some of later CIDs
  )

;; these are pools that prevent us from successful loading. They either contain bugs or our checker tool contain bugs.
;; We disable cons-checking for them, so all actual bugs related to them will pass unnoticed.
;; But if we enable cons-checking for them, we'll be unable even to build G2, let alone run it. 
;; In a future, we will have to fix them all one by one. 
(defparameter *pools-not-suitable-for-cons-checking*
  (append
   '(simple-gensym-string nil 
                          byte-vector
                          token
                          
                          unicode-block 
                          slot-description
                          
                          managed-simple-float-array ; missing handling replenishing process like that for conses
                          compound-frame-serial-number ; untracked instance when starting g2
                          REGULAR-EXPRESSION-NODE ; access to a reclaimed structure when completing a list of file names in open kb dialog
                          managed-simple-long-array  ; failed in chgtxt.kb 
                          edit-state ; failed when starting kb for test case for 1907
                          workstation-context-frame ; failed when starting kb for 1907
                          rule-instance ; failed when starting kb for 1907
                          rule-instance-variable ; failed when starting g2-list-tests-new 
                          computation-instance ; failed when starting kb for 1907
                          ;;;  Pools commented out here below are known to be problematic.
                          ;;;  We are modestly agressive here - if you enable cons-checking, be ready to face all the problems it detects, even
                          ;;;  false positives. But at least you can be able to load some kbs. 
                          ;;
                          ;; managed-simple-long-array  ; failed in chgtxt.kb 
                          ;; adjustable-gensym-string ; failed when starting g2-list-tests-new
                          ;; SELECTION-RECTANGLE-STATE ; failed at some random mouse operation in twng
                          ;; queue-element ; failed in automated-gdu-demo
                          ;; slot-value ; failed in automated-gdu-demo badly (certainly a bug)
                          ;; eval ; failed in automated-gdu-demo badly (certainly a bug)
                          ;; NATIVE-SIMPLE-DIALOG-STATE ; automated-gdu-demo
                          ;; nms-menu-item ; failed somewhere, don't remember exactly
                          ;; TEXT-SEQUENCE ; failed somewhere, don't remember exactly
                          ;; transcode-text-conversion-style ; failed somewhere, don't remember exactly
                          )
   ;; some objects are created while loading sources. In the scope of unit-test helper macros like
   ;; (tests::with-simplest-test-environment () ) we restart cons checking and hence
   ;; lose the track of those objects. So we exclude that types from cons-checking altogether to 
   ;; keep the world running
   #+under-test
   '(
     lexing-table
     text-tokenization-state
     fsm-state
     state-transition
     internal-token
     class-description
     binary-tree-element
     gensym-grammar
     data-server
     CATEGORY-EVALUATOR-INTERFACE
     EVALUATOR-SLOT-INFO
     CATEGORY-FOR-CATEGORY-SYMBOL
     CATEGORY-FOR-TOKEN
     PHRASE-RULE-COMPLETION
     )))

(defun pool-is-suitable-for-cons-checking-p (pool)
  (not (member pool *pools-not-suitable-for-cons-checking*)))


(defun cons-checking-get-cons-story (cons)
  ;; returns the cons-story recorded by check-cons for this cons. If cons is untracked, returns nil
  (gethash cons *cons-table*))

(defun cons-checking-current-status-of-cons (cons)
  ;; returns state of the cons, that is the symbol showing current status of the cons. 
  (let ((s (gethash cons *cons-table*)))
    (if s (cons-story-status s) 'cons-checking-object-status-untracked)))


;; There was show-bad-conses. But it is not needed anymore because all the problems
;; it detects are now shown immediately
;; What we can do is verify all pool contents. That is, check that all reclaimed conses are in 
;; the pool of available conses. 
(defun cons-checking-show-bad-conses ()
  (error "We have no useful checks here, no use in this function (yet)"))


(defun cons-checking-report-problem (continue-string format &rest args)
  (ecase *cons-checking-reaction-on-problem*
    (error
     (apply #'error format args))
    (cerror
     (apply #'cerror continue-string format args))
    (log
     )))

(defun cons-checking-check-same-pool (cons-story expected-pool)
  (let ((actual-pool (cons-story-pool cons-story)))
    (unless (eq actual-pool expected-pool)
      (cons-checking-report-problem "Ignore the problem and fix the pool" "cons-checking: pool is ~A instead of expected ~A"
                                    actual-pool expected-pool)
      (pushnew actual-pool (cons-story-e cons-story)))
    (setf (cons-story-pool cons-story) expected-pool)
    ))

;; cons-checking-enabled-for-pool-p checks if cons-checking for the pool is disabled or enabled due to any reason(s)
(defun cons-checking-enabled-for-pool-p (pool)
  (and
   (or (eq cons-checking-enabled-p t) (eq cons-checking-enabled-p pool))
   (pool-is-suitable-for-cons-checking-p pool)))
  

;;; The following is a set of macros to build cons-checking functions from
;;; They all are unhygienic and 

(defmacro with-cons-checking-environment-do-if-appropriate (&body body)
  ;; we capture pool variable and bind story local variable
  ;; we check that pool is appropriate for cons-checking (some pools can misbehave)
  ;; also we check if checking is enabled for this pool. If we record backtraces, prepare to it. 
  `(when (cons-checking-enabled-for-pool-p pool)
     (let ((*current-backtrace* (when (member 'backtrace *cons-checking-log-settings*)
                                  (make-lisp-backtrace)))
           (story (gethash cons *cons-table*)))
      ,@body)))
     
(defmacro cons-checking-i-assert-expected-state-and-set-new-one (expected-statuses new-status)
  ;; When calling the macro, we capture the following variables:
  ;; story (of type cons-story)
  ;; pool
  ;; expected-states is a list of expected states, not evaluated. If user choses to reclklessly continue, 
  ;; story is assigned to first of them
  ;; new-status is evaluated
  (let* ((expect-more-than-one-state (not (null (second expected-statuses))))
         (code-to-check-state
          (if expect-more-than-one-state
              `(member (cons-story-status story) ',expected-statuses)
            `(eq (cons-story-status story) ',(first expected-statuses)))))
    `(progn
       (cons-checking-check-same-pool story pool)
       (unless ,code-to-check-state
         (cons-checking-report-problem
          "Ignore the problem" "cons-checking: object has an unexpected state ~S, while expected ~S"
          (cons-story-status story) '(or ,@expected-statuses))
         (pushnew pool (cons-story-e story)))
       (setf (cons-story-status story) ,new-status))))

(defmacro cons-checking-i-maybe-log-object-operation (operation)
  ;; When calling the macro, we capture the following variables:
  ;; story (of type cons-story)
  ;; cons (object under study), pool (pool root name)
  ;; also we bind entry variable.
  ;; operation is evaluated
  `(when *cons-checking-log-settings*
     (let ((entry (make-de/allocation-log-entry :operation ,operation)))
       (push entry (cons-story-ob story))
       (maybe-break-on-global-allocation-operation-counter cons pool entry))))

(defmacro cons-checking-i-init-story (but-this-was-not-expected initial-state operation)
  ;; When calling the macro, we capture the following variables:
  ;; s expected to be null, we set it
  ;; cons (object under study), pool (pool root name)
  ;; initial-state is evaluated, 
  ;; if but-this-was-not-expected is true at macroexpansion time, we issue cerror before initializing.
  ;; operation is evaluated
  `(progn
     ,@(when but-this-was-not-expected
         `((cons-checking-report-problem "continue and make cons story as if all was ok" "cons-checking: cons-checking-object-status-untracked status was unexpected for ~S operation" ,operation)))
     (setf story (make-cons-story :status ,initial-state :pool pool :e (list :none)))
     (setf (gethash cons *cons-table*) story)))
         

(defun cons-checking-declare-that-object-is-allocated-from-os-to-the-pool (cons pool)
  (with-cons-checking-environment-do-if-appropriate
    (cl:etypecase story
      (cons-story
       ; this is an anomaly case for def-structure which gets data from os, initializes it and stores to the pool. Before initializing, we set "initialization-begun" for it
       (cons-checking-i-assert-expected-state-and-set-new-one (cons-checking-object-status-initialization-begun) 'cons-checking-object-status-fresh-from-os))
      (null ; that's normal - object is untracked
       (cons-checking-i-init-story nil 'cons-checking-object-status-fresh-from-os 'cons-checking-declare-that-object-is-allocated-from-os-to-the-pool)))
    (cons-checking-i-maybe-log-object-operation 'cons-checking-declare-that-object-is-allocated-from-os-to-the-pool))
  (values))

;; cons-checking-note-cons-pool-source-1 is especially for replenish process
;; Due to some ideosyncrasy, replenish process notes some conses as fresh twice. Maybe it is a bug, 
;; but we don't care now. Instead, we write a special function with a cludge which
;; allows to declare cons as "fresh-from-os" twice
(defun cons-checking-note-cons-pool-source-1 (cons pool)
  (with-cons-checking-environment-do-if-appropriate
    (cl:etypecase story
      (cons-story ; this should not happen, but it does, and for the start we don't investigate it
       (cons-checking-i-assert-expected-state-and-set-new-one (cons-checking-object-status-fresh-from-os cons-checking-object-status-reclaimed) 'cons-checking-object-status-fresh-from-os))
      (null ; object is untracked - this is what should happen always
       (cons-checking-i-init-story nil 'cons-checking-object-status-fresh-from-os 'cons-checking-declare-that-object-is-allocated-from-os-to-the-pool)))
    (cons-checking-i-maybe-log-object-operation 'cons-checking-declare-that-object-is-allocated-from-os-to-the-pool))
  (values))

(defun cons-checking-note-initialization-begun (cons pool)
  ;; cons-checking-note-initialization-begun is called for objects with complex initialization process (e.g. results of define-structure,g2-defstruct,def-structure)
  (with-cons-checking-environment-do-if-appropriate
    (cl:etypecase story
      (cons-story
       (cons-checking-i-assert-expected-state-and-set-new-one (cons-checking-object-status-fresh-from-os cons-checking-object-status-reclaimed) 'cons-checking-object-status-initialization-begun))
      (null
       (cons-checking-i-init-story t 'cons-checking-object-status-initialization-begun 'cons-checking-note-initialization-begun)))
    (cons-checking-i-maybe-log-object-operation 'cons-checking-note-initialization-begun))
  (values))

(defun cons-checking-note-new-cons (cons pool)
  (with-cons-checking-environment-do-if-appropriate
    (cl:etypecase story
      (cons-story
       (cons-checking-i-assert-expected-state-and-set-new-one (cons-checking-object-status-fresh-from-os
                                                               cons-checking-object-status-reclaimed
                                                               ;; cons-checking-note-initialization-begun is called for objects with complex 
                                                               ;; initialization process (e.g. results of define-structure,g2-defstruct,def-structure)
                                                               cons-checking-object-status-initialization-begun) 'cons-checking-object-status-outstanding))
      (null
       (cons-checking-i-init-story t 'cons-checking-object-status-outstanding 'cons-checking-note-new-cons)))
    (cons-checking-i-maybe-log-object-operation 'cons-checking-note-new-cons))
  (values))

(defun cons-checking-note-reclaiming-begun (cons pool)
  ;; cons-checking-note-reclaiming-begun is called for objects with complex reclamation process (e.g. results of define-structure)
  (with-cons-checking-environment-do-if-appropriate
    (cl:etypecase story
      (cons-story
       (cons-checking-i-assert-expected-state-and-set-new-one (cons-checking-object-status-outstanding)
                                                              'cons-checking-object-status-reclaiming-begun))
      (null
       (cons-checking-i-init-story t 'cons-checking-object-status-reclaiming-begun 'cons-checking-note-reclaiming-begun)))
    (cons-checking-i-maybe-log-object-operation 'cons-checking-note-reclaiming-begun))
  (values))
    
(defun cons-checking-note-reclaimed-cons (cons pool)
  (with-cons-checking-environment-do-if-appropriate
    (cl:etypecase story
      (cons-story
       (cons-checking-i-assert-expected-state-and-set-new-one (cons-checking-object-status-outstanding cons-checking-object-status-reclaiming-begun)
                                                              'cons-checking-object-status-reclaimed))
      (null
       (cons-checking-i-init-story t 'cons-checking-object-status-reclaimed 'cons-checking-note-reclaimed-cons)))
    (cons-checking-i-maybe-log-object-operation 'cons-checking-note-reclaimed-cons))
  (values))


(defun limited-tailp (object list-or-circular-list length-to-process)
  ;; limited-tailp is like tailp, but it can handle circular lists by processing no more 
  ;; than length-to-process elements of list. Tries to find i such that object == (nthcdr i list-or-circular-list). For nil, always return nil unlike tailp.
  (cond
   ((null object) nil)
   (t
    (let ((tail list-or-circular-list)
          (count 0))
      (loop
       (when (= count length-to-process)
         (return nil))
       (unless (consp tail)
         (return nil))
       (when (eq object tail)
         (return count))
       (incf count)
       (setf tail (cdr tail)))))))


;; Some data is printed extremely ugly and can cause stack overflow, allocation error or an infinite loop
;; To save user from necessity to have *print-circle* setting, and keeping an ability to inspect the value,
;; lets wrap that ugly data to a class so that it is not printed by default
;; User can always call jack-in-a-box-data to get his strike at nose
(cl:defclass jack-in-a-box () ((data :accessor jack-in-a-box-data :initarg data)))

(defun make-a-jack-in-a-box (x)
  (cl:make-instance 'jack-in-a-box 'data x))

(defun cons-checking-validate-state-of-conses-available (pool)
  ;; Finds some corruptions is cons available list for a given pool name which we can't find
  ;; immediately. Mainly, some cases of illegal writing to available conses list. 
  ;; It returns some data from cons, which can contain very long or circular lists. We pack it into
  ;; jack-in-a-box class so that printing it won't hurt you
  (let* ((available-list-name (name-of-available-pool pool))
         (available-list (symbol-value available-list-name))
         (marker (car-marker-by-pool-name pool))
         (result nil)
         (length (list-length available-list))
         (length-to-process (or length 2000)))
    (when (null length)
      (push `("List is circular: " ,(make-a-jack-in-a-box available-list-name) " - it is certainly corrupted. I will analyzee only first" ,length-to-process "elements of it") result))
    (loop named l1
          for cons = available-list then (cdr cons)
          for count from 1 to length-to-process
          do
          (let ((status-from-story (cons-checking-current-status-of-cons cons)))
            (unless (member status-from-story
                            '(cons-checking-object-status-fresh-from-os
                              cons-checking-object-status-reclaimed))
              (push
               `("Object" ,(make-a-jack-in-a-box cons) "is in available pool, but it's story shows different status" ,status-from-story) result))
            (unless (eq (car cons) marker)
              (push
               `("Available cons" ,(make-a-jack-in-a-box cons) "must have contained a special marker in its car. I suspect its cur was written illegally after the cons was reclaimed") result))
            (cl:etypecase (cdr cons)
              (null)
              (cons)
              (t 
               (push
                `("Available cons" ,(make-a-jack-in-a-box cons) "must have contained a special marker in its car. I suspect its cur was written illegally after the cons was reclaimed") result)
               (return-from l1 nil)))))
    (assert *cons-table* () "*cons-table* is null - cons-checking is disabled or broken")
    (maphash
     (lambda (k v)
       (when (and
              (eq (cons-story-pool v) pool)
              (member (cons-story-status v)
                      '(cons-checking-object-status-fresh-from-os cons-checking-object-status-reclaimed)))
         (unless (limited-tailp k available-list length-to-process)
           (push `("Story of the cons" ,(make-a-jack-in-a-box k) "says it must be on " ,(make-a-jack-in-a-box available-list-name) "but it isn't. I suspect illegal writing to some other reclaimed cons") result))))
     *cons-table*)
    (nreverse result)
    ))

;; Finds pools where the object was before allocation sequence violation was reported on the object 
(defun cons-checking-find-pools-with-violations-of-allocation-sequence ()
  (let ((pools nil))
    (maphash
     (lambda (k v)
       (declare (ignore k))
       (let ((e (cons-story-e v)))
         (when e
           (dolist (pool e)
             (pushnew pool pools)))))
     *cons-table*)
    pools))
  
(defun cons-checking-note-cons-pool-source (pool cons-list)
  "Cons-list is expected to be a list of available conses from the pool named pool. We expect that we are called from
  replenish function and we have just acquired new conses-to-update from OS. So we mark them as having
  cons-story-frame-fresh-from-os"
  (when (cons-checking-enabled-for-pool-p pool)
    (loop for cons on cons-list
          do (cons-checking-note-cons-pool-source-1 cons pool)))
  ;; Uncomment if you want very strict checking, but it is very slow
  ;(cons-checking-validate-state-of-conses-available pool)
  (values))
  

(defun cons-checking-install-consing-cons-checking-functions ()
  (compile
   `(defadvice (inline-note-allocate-cons cons-checking) (cons pool)
      (cons-checking-note-new-cons cons pool)
            ; simply "advice-continue" does not work with compilation, maybe due to some tricky processing by lw:defadvice
      ,(macroexpand '(advice-continue cons pool))))
  (push 'inline-note-allocate-cons cons-checking-functions))

(defun cons-checking-install-reclaiming-cons-checking-functions ()
  (compile
   `(defadvice (inline-note-reclaim-cons cons-checking) (cons pool)
      (cons-checking-note-reclaimed-cons cons pool)
      ,(macroexpand `(advice-continue cons pool))))
  (push 'inline-note-reclaim-cons cons-checking-functions))

(defun cons-checking-install-pool-cons-checking-functions (replenish-x-cons-pool replenish-x-list-pool pool)
  "This is a wrong name. In fact this function resets the state of available conses for this pool"
  (let ((available-conses (name-of-available-pool pool)))
    (compile
     `(defadvice (,replenish-x-cons-pool cons-checking) ()
        (let ((result ,(macroexpand `(advice-continue))))
          (cons-checking-note-cons-pool-source
           ',pool
           result)
          result)))
    (compile
     `(defadvice (,replenish-x-list-pool cons-checking) (conses-needed-minus-one)
        (let ((result ,(macroexpand `(advice-continue conses-needed-minus-one))))
            (cons-checking-note-cons-pool-source
             ',pool
             ,available-conses)
          result)))
    (push replenish-x-cons-pool cons-checking-functions)
    (push replenish-x-list-pool cons-checking-functions)))

;; enables cons-checking for one pool
;; pool-with-suffix - e.g. gensym-conses
(defun cons-checking-enable-for-a-new-pool (root-name x-pool-name typ clear-pool)
  (declare (ignore x-pool-name))
  (when (eq typ 'cons)
    (cons-checking-install-pool-cons-checking-functions
     ;; I don't know why we need replenis-~A-list-pool, but it addes to the same cons list
     ;; budden73
     (intern (format nil "REPLENISH-~A-CONS-POOL" root-name) :ab)
     (intern (format nil "REPLENISH-~A-LIST-POOL" root-name) :ab)
     root-name)
    (cond
     (clear-pool
      (set (name-of-available-pool root-name) nil))
     (t
      (assert (null (cl::symbol-value (name-of-available-pool root-name))))))))

;; Start part of cons-checking common for all pools
;; This function is invoked after the definition of inline-note-reclaim-cons. It does not
;; make sense to call it earlier because the code to advice does not exist yet. 
;; But it must be called before the initialization of G2 memory manager.
;; Other part is made (automatically) for each pool by
;; cons-checking-enable-for-a-new-pool function, which we call from the defconser macro (defun cons-checking-start-common-part ()
(cl:defun cons-checking-start-common-part (&optional (set-cons-checking-enabled-p nil set-cons-checking-enabled-p-supplied-p)) 
  (setq *cons-table* (make-hash-table :test 'eq))
  (cons-checking-install-consing-cons-checking-functions)
  (cons-checking-install-reclaiming-cons-checking-functions)
  (when set-cons-checking-enabled-p-supplied-p
    (setq cons-checking-enabled-p set-cons-checking-enabled-p))
  (values))

) ; progn - cons-checking
