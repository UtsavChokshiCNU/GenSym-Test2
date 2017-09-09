;;;; This script is for running LW G2 development build in regression tests

(in-package :cl-user)


;;; with-lock-dir utility to allow ant running several G2s in parallel

(defun try-creating-lock-dir (dir-name)
  (assert (equalp (pathname-type dir-name) "lck")) ; try to minimize possible harm
  (let ((*break-on-signals* nil))
    (handler-bind
        ((#+lispworks conditions:output-to-existing-file-error
                      #-lispworks #.(error "try-creating-lock-dir: how does your lisp classify output-to-existing-file-error?")
                      #'(lambda (condition)
                          (declare (ignore condition))
                          (return-from try-creating-lock-dir nil)))
	 (#+lispworks conditions:file-operation-error
                      #-lispworks #.(error "try-creating-lock-dir: how does your lisp classify file-operation-error?")
                      #'(lambda (condition)
                          (declare (ignore condition))
                          (return-from try-creating-lock-dir nil))))
      ;; this function is undocumented
      (system:make-directory dir-name)
      )))


(defun create-lock-dir (dir-name)
  "Creates a lock dir. If it exists, wait for it to disappear"
  (loop
   (let ((success (try-creating-lock-dir dir-name)))
     (when success
       (return t)))
   (sleep 0.25)))

(defun delete-lock-dir (dir-name)
  "Deletes lock dir (assuming we created it previously)"
  (assert (equalp (pathname-type dir-name) "lck")) ; try to minimize possible harm
  (delete-directory dir-name))

(defmacro with-lock-dir (dir-name &body body)
  (let ((dir-name-once-var (make-symbol "Dir-Name-Once-Var"))
        (dir-created-successfully (make-symbol "Dir-Created-Successfully")))
    `(let ((,dir-name-once-var ,dir-name)
           (,dir-created-successfully nil))
       (unwind-protect
           (progn
             (setq ,dir-created-successfully (create-lock-dir ,dir-name-once-var))
             ,@body)
         (when ,dir-created-successfully
           (delete-lock-dir ,dir-name-once-var))))))

;;; Whenever we want enter the debugger, write to log and exit instead

(defun g2-lw-rt-get-environment-variable-value (name)
  #+lispworks (lw:environment-variable name)
  #+sbcl (sb-ext:posix-getenv name)
  #+clozure (ccl:getenv name))

(defparameter *g2-lw-rt-src-box* (g2-lw-rt-get-environment-variable-value "SRCBOX"))

(assert *g2-lw-rt-src-box* () "SRCBOX Environment variable is not set")

#+lispworks
(defun g2-lw-rt-backtrace (stream verbose)
  (let ((*print-length* 30)
        (*print-level* 7)
        (*print-circle* t))
    (dbg:output-backtrace
     (if verbose :verbose :quick)
     :stream stream
     )))

(defparameter *brief-backtrace-log-file-name* "g2-lw-brief-backtrace.txt")
(defparameter *verbose-backtrace-log-file-name* "g2-lw-verbose-backtrace.txt")

(defun write-debugger-entry-attempt-details-to-log (condition verbose)
  (let* ((dest-dir-no-slash (or (g2-lw-rt-get-environment-variable-value "G2_AUTO_TEST")
                                (format nil "~a/tests" *g2-lw-rt-src-box*)))
         (log-filename (format nil "~a/~a" dest-dir-no-slash (if verbose *verbose-backtrace-log-file-name* *brief-backtrace-log-file-name*))))
    (with-open-file (ou log-filename
			:direction :output
			:if-does-not-exist :create
			:if-exists :supersede)
      (if verbose
          (format ou "~%Lisp fell into the debugger.~%Command line arguments: ~S~%Condition: ~A~%"
                  system:*line-arguments-list*
                  condition)
        (format ou "~%Lisp fell into the debugger. Backtrace follows. You can also try to find detailed backtrace in ~A" *verbose-backtrace-log-file-name*))
      (g2-lw-rt-backtrace ou verbose))))
  

(defun debugger-hook-write-to-log-and-quit-lisp (condition old-hook)
  (declare (ignore old-hook))
  (let ((*debugger-hook* nil)
        (*break-on-signals* nil))
    (ignore-errors ; sometimes we fail to print backtrace
      (format t "~%Lisp attempts to enter the debugger.~%Command line arguments: ~S.~%debugger-hook-write-to-log-and-quit-lisp will try to cause lisp to exit. See *backtrace*.txt in test destination directory" 
	      system:*line-arguments-list*)
      (write-debugger-entry-attempt-details-to-log condition nil)
      (write-debugger-entry-attempt-details-to-log condition t))

    (cl-user::quit :confirm nil :ignore-errors-p t :return 1)))
    
(setq *debugger-hook* #'debugger-hook-write-to-log-and-quit-lisp)
(setq system:*debug-initialization-errors-in-snap-shot* nil)


;;; Load G2

(with-lock-dir (format nil "~a/lisp/tests/loading-tests.lck" *g2-lw-rt-src-box*)
               (load (format nil "~a/lisp/tests/load-tests.lisp" *g2-lw-rt-src-box*)))

(with-lock-dir (format nil "~a/lisp/tests/loading-1mp.lck" *g2-lw-rt-src-box*)
               (load-g2-development-mode "1mp"))

;;; Establish G2 startup sequence and launch G2

(remove-advice 'ab::launch-ab 'ab::launch-ab-in-new-thread)

(ab::launch-ab)

(quit :confirm nil)
