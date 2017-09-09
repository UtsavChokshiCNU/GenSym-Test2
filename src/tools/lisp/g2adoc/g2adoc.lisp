(defpackage g2adoc
  (:use #:cl)
  (:export #:document-kb))

(in-package g2adoc)

(defun slurp-file (name)
  "reads and parses XML kb"
  (cxml:parse-file
   name (cxml-xmls:make-xmls-builder :include-namespace-uri nil)))

(defun get-nodes-by-name (name xml)
  "returns a list of nodes; should we use XPath instead?"
  (remove-if-not
   #'(lambda (e)
       (and (consp e) (string= name (cxml-xmls:node-name e))))
   (cxml-xmls:node-children xml)))

(defun get-node-by-name (name xml)
  "returns first node with the name; should we use XPath instead?"
  (find-if
   #'(lambda (e)
       (and (consp e) (string= name (cxml-xmls:node-name e))))
   (cxml-xmls:node-children xml)))

(defun get-node-text (node)
  "returns the value of node text child"
  (car (cxml-xmls:node-children node)))

(defun get-node-text-by-name (name xml)
  "returns the value of node NAME text child"
  (get-node-text (get-node-by-name name xml)))

(defun get-procs (xml)
  "returns a list of procedures"
  (get-nodes-by-name "c.PROCEDURE" xml))

(defun get-classes (xml)
  "returns a list of classes"
  (get-nodes-by-name "c.CLASS-DEFINITION" xml))

(defun get-methods (xml)
  "returns a list of methods"
  (get-nodes-by-name "c.METHOD" xml))

(defun trim-whitespace (string)
  "removes leading and trailing whitespace"
  (when (stringp string)
    (string-trim '(#\Space #\Tab #\Newline #\Return) string)))

(defun get-proc-text (proc)
  "gets procedure's text"
  (trim-whitespace (get-node-text-by-name "a.TEXT" proc)))

(defun parse-proc-args (lst &optional args)
  "parses proc args"
  (if (null lst) (reverse args)
      (let ((name (car lst))
	    (type (second lst)))
	(when (eq 'class type)
	  (setf lst (cdr lst)
		type (format nil "CLASS ~a" (second lst))))
	(let ((doc? (third lst)))
	  (if (stringp doc?)
	      (parse-proc-args
	       (nthcdr 3 lst)
	       (cons (list name type (trim-whitespace doc?)) args))
	      (parse-proc-args
	       (nthcdr 2 lst) (cons (list name type nil) args)))))))

(defun parse-proc-rets (lst &optional args)
  "parses proc return values"
  (if (null lst) (reverse args)
      (let ((name (format nil "RET~a" (length args))) 
	    (type (car lst)))
	(when (eq 'class type)
	  (setf lst (cdr lst)
		type (format nil "CLASS ~a" (second lst))))
	(let ((doc? (second lst)))
	  (if (stringp doc?)
	      (parse-proc-rets
	       (nthcdr 2 lst)
	       (cons (list name type (trim-whitespace doc?)) args))
	      (parse-proc-rets
	       (nthcdr 1 lst) (cons (list name type nil) args)))))))

(defun read-{}-string (stream char)
  (declare (ignore char))
  "reads G2 comment as a string"
  (with-output-to-string (out-stream)
    (loop for next = (read-char stream t nil t)
       until (char= next #\})
       do (write-char next out-stream))))

(defun parse-proc-text (text)
  "returns a list containing proc name, args, return values and 'docstring'"
  (let ((*readtable* (copy-readtable)))
    (set-syntax-from-char #\, #\Space)
    (set-syntax-from-char #\: #\Space)
    (set-macro-character #\{ #'read-{}-string)
    (with-input-from-string (s text)
      (let ((name (read s))
	    (args (parse-proc-args (read s)))
	    (equal-sign? (read s)))
	(if (eq '= equal-sign?)
	    (list
	     name args (parse-proc-rets (read s))
	     (let ((d (read s))) (if (stringp d) (trim-whitespace d))))
	    (list
	     name args nil
	     (if (stringp equal-sign?) (trim-whitespace equal-sign?))))))))

(defun print-adoc-name (name)
  "prints name in AsciiDoc format"
  (format t "=== ~a~%~%" name))

(defun print-adoc-arg-for-syn (stream arg colon at)
  (declare (ignore colon at))
  "formats arg for synopsis"
  (destructuring-bind (name type doc) arg
    (declare (ignore doc))
    (format stream "`_~a_`: ~a" name type)))

(defun print-proc-synopsis (name args rets)
  "prints proc synopsis in AsciiDoc format"
  (format t "==== Synopsis~%~%`~a`(~{~/g2adoc::print-adoc-arg-for-syn/~^, ~})~@[ -> ~{~/g2adoc::print-adoc-arg-for-syn/~^,~}~]~%~%" name args rets))

(defun print-adoc-arg-for-desc (stream arg colon at)
  (declare (ignore colon at))
  "formats arg for description"
  (destructuring-bind (name type doc) arg
    (declare (ignore type))
    (format stream "|`_~a_`|~a~%" name (or doc ""))))

(defun print-proc-args (args &optional (args? t))
  "prints proc args or return values in AsciiDoc format"
  (format
   t
   "|===~%|~a|Description~%~%~{~/g2adoc::print-adoc-arg-for-desc/~}|===~%~%"
   (if args? "Argument" "Return Value") args))

(defun print-proc-rets (rets)
  (if rets (print-proc-args rets nil)
      (format t "It has no return value.~%~%")))

(defun print-adoc-desc (desc)
  "prints desc in AsciiDoc format"
  (format t "==== Description~%~%~a~%~%" desc))

(defun proc-adoc (desc)
  "formats proc description as AsciiDoc"
  (destructuring-bind (name args rets doc) desc
    (print-adoc-name name)
    (print-proc-synopsis name args rets)
    (print-proc-args args)
    (print-proc-rets rets)
    (when doc (print-adoc-desc doc))
    (format t "~%")))

(defun get-class-name (node)
  "gets class name"
  (get-node-text-by-name "a.CLASS-NAME" node))

(defun get-seq-by-name (name node)
  "gets contents of sequence child with the name"
   (get-nodes-by-name
    "li"
    (get-node-by-name "Sequence" (get-node-by-name name node))))

(defun get-direct-superior-classes (node)
  "gets superclasses"
  (mapcar
   #'third
   (get-seq-by-name "a.DIRECT-SUPERIOR-CLASSES" node)))

(defun simplify-attr-struct (desc node)
  "simplify attr structure"
  (let ((name (get-node-text-by-name "sa.ATTRIBUTE-NAME" node)))
    (list 
     name
     (get-node-text-by-name "sa.ATTRIBUTE-TYPE-SPECIFICATION" node)
     (get-node-text-by-name "sa.ATTRIBUTE-INITIAL-VALUE" node)
     (get-node-text-by-name "sa.ATTRIBUTE-INITIAL-TYPE" node)
     (cdr (assoc name desc :test #'string=)))))

(defun get-class-attributes (desc node)
  "gets class fields"
  (mapcar
   #'(lambda (li)
       (simplify-attr-struct
	desc
        (get-node-by-name "Structure" li)))
   (get-seq-by-name "a.CLASS-SPECIFIC-ATTRIBUTES" node)))

(defun get-item-configuration-comment (node)
  "gets comments from item configuration"
  (mapcar
   #'(lambda (li)
       (let ((s (get-node-by-name "Structure" li)))
	 (cons (get-node-text-by-name "sa.TAG-NAME" s)
	       (get-node-text-by-name "sa.ASSOCIATED-TEXT" s))))
   (car
    (remove-if
     #'null
     (mapcar
      #'(lambda (li)
	  (let ((s (get-node-by-name "Structure" li)))
	    (if (equal "COMMENT" (get-node-text-by-name "sa.TYPE" s))
		(get-seq-by-name "sa.CLAUSES" s))))
      (get-seq-by-name "a.ITEM-CONFIGURATION" node))))))

(defun simplify-class-def (node)
  "simplify class definition"
  (let ((desc (get-item-configuration-comment node))
	(name (get-class-name node)))
    (list
     name
     (get-direct-superior-classes node)
     (get-class-attributes desc node)
     (cdr (assoc name desc :test #'string=)))))

(defun print-adoc-sups (sups)
  "prints superiors in AsciiDoc format"
  (format t "==== Direct Superior Classes~%~%~{~a~^, ~}~%~%" sups))

(defun print-adoc-field-for-desc (stream field colon at)
  (declare (ignore colon at))
  "formats arg for description"
  (destructuring-bind (name type initial initial-type desc) field
    (format
     stream "|`_~a_`|~a|~a|~a|~a~%" name
     (or type "") (or initial "") (or initial-type "") (or desc ""))))

(defun print-class-fields (fields)
  "prints class fields in AsciiDoc format"
  (format
   t
   "|===~%|Attribute|Type|Initial Value|Initial Value Type|Description~%~%~{~/g2adoc::print-adoc-field-for-desc/~}|===~%~%" fields))

(defun class-adoc (desc)
  "formats class description as AsciiDoc"
  (destructuring-bind (name sups fields doc) desc
    (print-adoc-name name)
    (print-adoc-sups sups)
    (print-class-fields fields)
    (when doc (print-adoc-desc doc))
    (format t "~%")))

(defun document-procs (xml)
  "describes all procedures"
  (format t "== Procedures~%~%")
  (dolist (p (get-procs xml))
    (proc-adoc (parse-proc-text (get-proc-text p)))))

(defun document-methods (xml)
  "describes all methods"
  (format t "== Methods~%~%")
  (dolist (p (get-methods xml))
    (proc-adoc (parse-proc-text (get-proc-text p)))))

(defun document-classes (xml)
  "describes all classes"
  (format t "== Classes~%~%")
  (dolist (p (get-classes xml))
    (class-adoc (simplify-class-def p))))

(defun document-kb (path)
  "extracts commments from a XML KB located at PATH and formats the documentation as AsciiDoc to standard output; could have done printing CLOS methods, but decided to KISS"
  (let ((xml (slurp-file path)))
    (document-procs xml)
    (document-classes xml)
    (document-methods xml)))
