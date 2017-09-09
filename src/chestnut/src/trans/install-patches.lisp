
(in-package :user)

(eval-when (compile load eval)
(proclaim '(optimize (safety 0) (speed 3) (compilation-speed 0)))
)

(defparameter *patch-file-default*
  (pathname "/home/rh/releases/3-2-beta-3/trans/patches/*.lisp"))

(defparameter *translator-file-default*
  (pathname "/home/rh/releases/3-2-beta-3/trans/*.lisp"))

;; load the clos version of the translator, then type
#|
  (make-load-file :include-patches-p nil :customer nil
                  :print t :output-file nil)
|#
;; to make sure this list is current,
;; then comment out the host files.
(defparameter *translator-file-list*
  '("host-implementation-package"
    "host-implementation"
    "module"
    "translator"
    "lisp/define-symbols"
    "lisp/hpacks"
    ;;"lisp/lucid-4-syms"
    ;;"lisp/lucid-4-defs"
    "lisp/rpacks"
    "lisp/ipacks"
    "lisp/util"
    "lisp/resource"
    "lisp/lambda"
    "lisp/env"
    "lisp/type"
    "lisp/initdecl"
    "lisp/tcldefs"
    "lisp/map-name"
    "lisp/reserved"
    "lisp/namespaces"
    "lisp/record"
    "lisp/target"
    "lisp/foreign-types"
    "lisp/target-form-types"
    "lisp/codewalk"
    "lisp/walk"
    "lisp/toplevel"
    "lisp/bq"
    "lisp/readtbl"
    "lisp/clos-util"
    "lisp/find-class"
    "lisp/canonic-initargs"
    "lisp/binding"
    "lisp/block"
    "lisp/call"
    "lisp/catch"
    "lisp/define"
    "lisp/defpackage"
    "lisp/defsetf"
    "lisp/defstruct"
    "lisp/emacros"
    ;;"lisp/foreign-interface"
    "lisp/if"
    "lisp/iter"
    "lisp/loop"
    "lisp/misc"
    "lisp/modify-macros"
    "lisp/pattern"
    "lisp/progn"
    "lisp/setf"
    "lisp/setf-methods"
    "lisp/tagbody"
    "lisp/transform-lambda"
    "lisp/values"
    "lisp/optimize"
    "lisp/pregather"
    "lisp/gather"
    "lisp/constant"
    "lisp/emit"
    "lisp/library"
    "lisp/declare"
    "lisp/dump"
    "lisp/dumpmake"
    "lisp/dumpmain"
    "lisp/initfunctions"
    "lisp/early-metaclasses"
    "lisp/global-index"
    "lisp/class-record"
    "lisp/slot-definition"
    "lisp/std-class"
    "lisp/ensure-translator-class"
    "lisp/defclass"
    "lisp/initialize-class-records"
    "lisp/metaobjects"
    "lisp/method-arguments"
    "lisp/define-method-combination"
    "lisp/make-method-body"
    "lisp/slot-access"
    "lisp/slot-access-std-class"
    "lisp/slot-layout"
    "lisp/defmethod"
    "lisp/generic-function-definition"
    "lisp/ensure-generic-function"
    "lisp/defgeneric"
    "lisp/local-generic-functions"
    "lisp/initialize-generic-functions"
    "lisp/build-boot"
    "lisp/license"
    "lisp/type-specific"
    "lisp/initenv"
    "lisp/symbols"
    "lisp/list-symbols"
    "lisp/array-symbols"
    "lisp/more-symbols"
    "lisp/clos-runtime-symbols"
    "lisp/final"))

(unless (member :translator-supports-clos *features*)
  (warn "You should load the clos version of the translator first"))

(defstruct line-info
  file-name
  start-position
  end-position
  line
  package
  index)

(defstruct file-info
  file-alist
  line->line-info-list)

(defun find-string (string line)
  (let* ((string-len (length string))
         (string-len1 (1+ string-len))
         (len (length line)))
    (and (<= string-len1 len)
         (string-equal string line
                       :start2 1
                       :end2 string-len1)
         (or (= string-len1 len)
             (char= #\space (schar line string-len1)))
         string-len1)))

(defparameter *def-one-argument-prefixes*
  '("defun" "define-translator-parameter" "defvar" "defmacro"
    "define-translator-compiler-macro" "defparameter"
    "define-prefix-c-operator" "defwalk" "define-translator-setf-method"
    "defsetf" "define-translator-macro" "defwalk-ignore"
    "define-binary-c-operator" "define-foreign-type"
    "defgatherer" "def-pregatherer" "deftranslate"
    "define-statement" "define-expression-emitter" "define-toplevel-form"
    "define-statement-emitter"
    "define-type-symbol" "define-typep-optimizer" "translator-defsetf"
    "define-translator-foreign-type" "define-constant-type"
    "define-expression" "define-hashed-structure" "define-flags"
    "defstruct" "define-simple-variable-translator-declaration"
    "define-foreign-call-handler" "define-function-record-info"
    "define-translator-declaration" "define-foreign-type-function"
    "define-simple-function-translator-declaration"
    "define-template" "define-makefile-configuration"
    "define-makefile-syntax" "define-pathname-syntax"
    "define-c-namespace" "define-copier"))

(defparameter *other-one-argument-prefixes*
  '("translator-defsetf"))

(defparameter *unhandled-prefixes*
  '("eval-when" "host::import-and-export" "proclaim"
    "define-symbols" "himpl:define-symbols" "himpl::define-symbols" "let"))

(defun simplify-line-with-string (string line)
  (let ((pos (find-string string line)))
    (when pos
      (let ((non-blank (position #\space line
                                 :start pos
                                 :test-not #'eql)))
        (when non-blank
          (let ((blank (position #\space line
                                 :start non-blank)))
            (when blank
              (setq line (subseq line 0 blank))))))
      line)))

(defun simplify-line (line)
  (cond ((> 4 (length line))
         (values line nil))
        ((not (string-equal "def" line :start2 1 :end2 4))
         (dolist (string *other-one-argument-prefixes* (values line nil))
           (let ((sline (simplify-line-with-string string line)))
             (when sline (return (values sline t))))))
        (t
         (dolist (string *def-one-argument-prefixes* (values line nil))
           (let ((sline (simplify-line-with-string string line)))
             (when sline (return (values sline t))))))))

(defun process-file-list (file-list)
  (let* ((line->line-info-list
          (make-hash-table :test 'equalp))
         (rev-file-alist nil)
         (rev-current-line-info-list nil)
         (index -1))
    (dolist (current-file file-list)
      (print current-file)
      (with-open-file (in current-file
                          :direction :input)
        (let ((*package* *package*))
          (loop (let ((position (file-position in))
                      (line (read-line in nil nil)))
                  (unless line (return nil))
                  (unless position (error "position is NIL"))
                  (when (and (<= 1 (length line))
                             (char= (schar line 0) #\())
                    (let ((pos (file-position in))
                          (form (progn
                                  (file-position in position)
                                  (read-preserving-whitespace in))))
                      (if (or (find-string "in-package" line)
                              (find-string "host:in-package" line)
                              (find-string "host::in-package" line))
                          (eval form)
                          (let* ((line (simplify-line line))
                                 (line-info (make-line-info
                                             :file-name current-file
                                             :start-position position
                                             :end-position (file-position in)
                                             :line line
                                             :package *package*
                                             :index (incf index))))
                            (push line-info 
                                  (gethash line line->line-info-list))
                            (push line-info rev-current-line-info-list)))
                      (file-position in pos)))))))
      (push (cons current-file (nreverse rev-current-line-info-list))
            rev-file-alist))
    (make-file-info :file-alist (nreverse rev-file-alist)
                    :line->line-info-list line->line-info-list)))

(defun compare-defined (lil+slil1 lil+slil2)
  (< (line-info-index (caadr lil+slil1))
     (line-info-index (caadr lil+slil2))))

(defun compare-not-defined (lil1 lil2)
  (< (line-info-index (car lil1))
     (line-info-index (car lil2))))

(defun check-definitions (patches system)
  (let ((patches-table (file-info-line->line-info-list patches))
        (system-table (file-info-line->line-info-list system))
        (defined nil)
        (not-defined nil))
    (maphash #'(lambda (line line-info-list)
                 (let ((system-info-list (gethash line system-table)))
                   (if system-info-list
                       (push (list line-info-list
                                   system-info-list)
                             defined)
                       (push line-info-list not-defined))))
             patches-table)
    (values (sort defined #'compare-defined)
            (sort not-defined #'compare-not-defined))))

(defvar *defined*)
(defvar *unhandled*)
(defvar *not-defined*)

(defun print-line-info-list (lil &optional skip-line-p line)
  (unless skip-line-p
    (terpri)
    (princ (or line (line-info-line (car lil)))))
  (format t " ~{~S(~D)~^, ~}"
          (mapcan #'(lambda (li)
                      (list (pathname-name
                             (line-info-file-name li))
                            (line-info-start-position li)))
                  lil)))

(defun print-lil+slil (lil+slil &optional line)
  (print-line-info-list (cadr lil+slil) nil line)
  (terpri) (princ "    ")
  (print-line-info-list (car lil+slil) t))

(defun print-defined (lil+slil &optional skip-simple-p)
  (let ((lil (car lil+slil)))
    (multiple-value-bind (line matched-p)
        (simplify-line (line-info-line (car lil)))
      (unless (and skip-simple-p
                   (or matched-p
                       (and (<= 2 (length line))
                            (char= #\" (schar line 1)))))
        (print-lil+slil lil+slil line)))))

(defun print-defined-but-not-simple (lil+slil)
  (print-defined lil+slil t))   

(defun show-defined (&optional skip-simple-p)
  (mapcar (if skip-simple-p #'print-defined-but-not-simple #'print-defined)
          (sort (set-difference (copy-list *defined*) *unhandled*) #'<
                :key #'(lambda (lil+slil)
                         (line-info-index (caar lil+slil)))))           
  (terpri)
  (values))

(defun show-defined-but-not-simple ()
  (show-defined t))

(defun show-not-defined ()
  (mapcar #'print-line-info-list *not-defined*)
  (terpri)
  (values))

(defun show-unhandled ()
  (mapcar #'print-lil+slil *unhandled*)
  (terpri)
  (values))

(defun make-changes (defined)
  (let ((streams (mapcar #'(lambda (name) (list* name nil nil))
                         '(in out patch)))
        (abort-p t))
    (labels ((stream (type filename &optional abort-p)
               (dolist (stream streams (error "bad name"))
                 (when (eq (car stream) type)
                   (when (and (cadr stream)
                              (not (equalp (cadr stream) filename)))
                     (close (cddr stream) :abort abort-p)
                     (setf (cddr stream) nil))
                   (unless (cddr stream)
                     (when (and (eq type 'in) filename)
                       (print filename))
                     (setf (cddr stream)
                           (and filename
                                (if (eq type 'out)
                                    (open (make-pathname :defaults filename
                                                         :type "new-lisp")
                                          :direction :output
                                          :if-exists :supersede)
                                    (open filename :direction :input))))
                     (setf (cadr stream) filename))
                   (return (cddr stream)))))
             (get-file-portion (patch in start end)
               (let ((in-stream (if patch
                                    (stream 'patch patch)
                                    (stream 'in in)))
                     (out-stream (stream 'out in)))
                 (file-position in-stream start)
                 (if end
                     (dotimes (i (- end start))
                       (write-char (read-char in-stream) out-stream))
                     (loop (let ((char (read-char in-stream nil)))
                             (unless char (return nil))
                             (write-char char out-stream)))))))
      (unwind-protect
           (let ((last-filename nil)
                 (last-position nil))
             (dolist (change defined)
               (if (or (/= 1 (length (cadr change)))
                       (let ((line (line-info-line (caadr change))))
                         (dolist (string *unhandled-prefixes* nil)
                           (when (find-string string line)
                             (return t)))))
                   (push change *unhandled*)
                   (let* ((old (caadr change))
                          (old-filename (line-info-file-name old))
                          (new (caar change)))
                     (when (and last-filename
                                (not (equalp last-filename old-filename)))
                       (get-file-portion nil last-filename last-position nil)
                       (setq last-filename nil)
                       (setq last-position nil))
                     (unless last-filename
                       (setq last-filename old-filename)
                       (setq last-position 0))
                     (get-file-portion nil old-filename last-position
                                       (line-info-start-position old))
                     (get-file-portion (line-info-file-name new)
                                       last-filename
                                       (line-info-start-position new)
                                       (line-info-end-position new))
                     (setq last-position (line-info-end-position old)))))
             (when last-filename
               (get-file-portion nil last-filename last-position nil))
             (setq abort-p nil))
        (stream 'in nil abort-p)
        (stream 'out nil abort-p)
        (stream 'patch nil abort-p)))))

(defvar *patch-file-list*)

(defun add-patches-to-system (&optional (output "patches.out"))

  (format t "~2%Processing the patch files.")
  (setq *patch-file-list*
        (process-file-list
         (mapcar #'(lambda (patch)
                     (himpl::patch-file patch nil))
                 (himpl::available-patches nil))))

  (format t "~2&Processing the translator files.")
  (setq *translator-file-list*
        (process-file-list
         (let ((*default-pathname-defaults* *translator-file-default*))
           (mapcar #'merge-pathnames *translator-file-list*))))

  (format t "~2&Checking the definitions.")
  (multiple-value-bind (defined not-defined)
      (check-definitions *patch-file-list* *translator-file-list*)
    (setq *defined* defined)
    (setq *not-defined* not-defined)
    (setq *unhandled* nil))

  (format t "~2&Making the changes.")
  (make-changes *defined*)

  (format t "~2&Writing ~S." (namestring (merge-pathnames output)))
  (write-patch-info output)

  (format t "~2&Done.~%")

  output)

(defun write-patch-info (output)
  (with-open-file (*standard-output* output
                                     :direction :output
                                     :if-exists :supersede)

    (format t "~2%Defined, but might need checking~%")
    (show-defined-but-not-simple)

    (format t "~2%Unhandled~%")
    (show-unhandled)

    (format t "~2%Not Defined~%")
    (show-not-defined)
    (format t "~2%")))

(add-patches-to-system)
