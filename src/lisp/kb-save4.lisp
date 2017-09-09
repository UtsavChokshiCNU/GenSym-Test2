;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-

(in-package "AB")

;;;; Module KB-SAVE4

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Richard Harris


(declare-forward-reference all-virtual-attributes-for-class function)
(declare-forward-reference applicable-and-not-deprecated-virtual-attribute-p function)
(declare-forward-reference changing-validity-interval-invalidates-current-value-p variable)
(declare-forward-reference activate-item-if-necessary function)
(declare-forward-reference change-the-text-of-attributes-without-category-evaluator-interfaces-p variable)
(declare-forward-reference parse-and-change-slot function)
(declare-forward-reference make-permanent-item-of-class-description function)
(declare-forward-reference disable-stack-error variable)
(declare-forward-reference permit-transfer-of-permanent-items-p variable)
(declare-forward-reference transfer-action-internal function)
(declare-forward-reference make-subworkspace-action-internal function)
(declare-forward-reference execute-create-connection-stack-instruction-internal function)
(declare-forward-reference get-connection-vertices-accurately function)
(declare-forward-reference suppress-consistency-analysis-warnings-notes? variable)
(declare-forward-reference post-analyzer-warning-note-if-necessary function)
(declare-forward-reference put-simulation-details function)
(declare-forward-reference disable-subworkspace-connection-posts variable)
(declare-forward-reference make-permanent-item function)
(declare-forward-reference initializing-clear-text-p variable)
(declare-forward-reference clear-text-item-layering-info variable)
(declare-forward-reference array-initialization-evaluation-values-use-designations-p variable)
(declare-forward-reference item-color-pattern-returns-overrides-only-p variable)
(declare-forward-reference current-g2-rdf-module variable)
(declare-forward-reference disable-update-button variable)
(declare-forward-reference update-button function)
(declare-forward-reference make-conclude-type-error-string function)

;system procedures

;Issues: error reporting, progress indicators

;  xml-object -> file
(defun-for-system-procedure g2-write-xml-object-to-file (xml-object pathname)
  (write-xml-object-to-file xml-object pathname))

;  file -> xml-object
(defun-for-system-procedure g2-read-xml-object-from-file (pathname)
  (xml-object-and-fixups-for-file pathname)) ; ignore-errors is t.  fix this.

;  module -> xml-object
(defun-for-system-procedure g2-save-module-into-xml-object (module)
  (unless (module-contains-text-stripped-frames-p module)
    (let ((xml-object (xml-object-and-fixups-for-module module)))
      (add-checksums-to-xml-object
	xml-object
	(compute-checksums-for-xml-object xml-object module)))))

;  xml-object -> module
(defun-for-system-procedure g2-restore-module-from-xml-object (xml-object)
  (setq current-g2-rdf-module (module-name-symbol-for-xml-object xml-object))
  (let ((kb-load-case? nil))
    (simple-kb-read-1 nil nil 'restore-xml-kb xml-object)))

;  unannotated-xml-object -> xml-object
(defun-for-system-procedure g2-copy-xml-object-with-annotations (xml-object)
  (copy-xml-object xml-object t))

;  xml-object -> unannotated-xml-object
(defun-for-system-procedure g2-copy-xml-object-without-annotations (xml-object)
  (copy-xml-object xml-object nil))

;  xml-object, xml-object, file -> truth-value
(defun-for-system-procedure g2-compare-xml-objects (xml-object-1 xml-object-2 output-pathname)
  (let ((changes (compare-xml-object-and-fixups xml-object-1 xml-object-2 t)))
    (write-xml-changes-to-file changes output-pathname nil nil)
    (reclaim-xml-change-list changes)))


(defvar write-diffs-after-saving-clear-text-p nil)
(defvar write-checksums-in-xml-file-p t)

(defun-void write-clear-text-kb ()
  (unless write-diffs-after-saving-clear-text-p
    (when (get-command-line-flag-argument #w"write-diffs-of-saves")
      (setq write-diffs-after-saving-clear-text-p t)))
  (write-rdf-schema-for-module)
  (let ((module (kb-module-being-saved? current-kb-save))
	(binary-file (gensym-make-pathname :type #w"bkb"
					   :defaults (kb-transfer-pathname current-kb-save))))
    (prog1 (if (or write-diffs-after-saving-clear-text-p
		   write-checksums-in-xml-file-p)
	       (let ((xml-object (xml-object-and-fixups-for-module module)))
		 (when write-checksums-in-xml-file-p
		   (setq xml-object (add-checksums-to-xml-object
				      xml-object
				      (compute-checksums-for-xml-object xml-object module))))
		 (setf (xml-object-for-module current-kb-save) xml-object)
		 (write-clear-text-from-xml-object binary-file xml-object))
	       (write-clear-text-from-module binary-file module))
      (reclaim-journal-tree (kb-traversal-state-for-backup current-kb-save))
      (setf (kb-traversal-state-for-backup current-kb-save) nil))))

(defun-void maybe-write-clear-text-diffs ()
  (let ((module (kb-module-being-saved? current-kb-save))
	(new-xml-object (xml-object-for-module current-kb-save)))
    (when new-xml-object
      (when write-diffs-after-saving-clear-text-p
	(let* ((kb-file (kb-transfer-pathname current-kb-save))
	       (current-xml-object
		 (when (gensym-probe-file kb-file)
		   (xml-object-and-fixups-for-file kb-file)))
	       (changes (when current-xml-object
			  (compare-xml-object-and-fixups current-xml-object new-xml-object t)))
	       (changes-kb-file (gensym-make-pathname :type #w"log"
						      :defaults kb-file))
	       (author? (or (if servicing-workstation?
				(g2-user-name-for-this-workstation? current-workstation))
			    (get-current-user-name-if-any-case-insensitive)))
	       (author-text-string?
		 (when author? (copy-text-string (symbol-name-text-string author?))))
	       (save-date (twith-output-to-text-string
			    (twrite-frame-edit-timestamp
			      (get-current-frame-edit-timestamp))))
	       (plist (nconc (when author? (gensym-list '|author| author-text-string?))
			     (gensym-list '|date| save-date))))
	  (write-xml-changes-to-file changes changes-kb-file t plist)
	  (loop for (name value) on plist by 'cddr
		do (reclaim-text-string value))
	  (reclaim-gensym-list plist)
	  (reclaim-xml-object-and-fixups current-xml-object)))
      (setf (xml-object-for-module current-kb-save) nil)
      (reclaim-xml-object-and-fixups new-xml-object)
      module)))

; read-initial-plist-for-clear-text-kb

; read-clear-text-module

; continue-read-kb

(defun xml-object-and-fixups-for-module (module)
  (write-xml-object-from-module module))

(defun xml-object-and-fixups-for-file (gensym-pathname-to-read)
  (simple-kb-read gensym-pathname-to-read 'get-xml-kb nil nil))

(defun get-xml-fixups-path (xml-object path)
  (loop for attr = nil then (pop path)
	for current = xml-object then (get-xml-fixups current attr nil)
	while path
	finally (return current)))

(defun module-name-string-for-xml-object (xml-object)
  #+xml-module-name-from-module-id
  (get-xml-fixups-path xml-object '(|Module| |ID|))
  #-xml-module-name-from-module-id
  (symbol-name-text-string
    (get-xml-fixups-path xml-object '(|Module| |systemtables| 0 |TOP-LEVEL-MODULE|))))

(defun module-name-symbol-for-xml-object (xml-object)
  #+xml-module-name-from-module-id
  (intern-text-string (get-xml-fixups-path xml-object '(|Module| |ID|)))
  #-xml-module-name-from-module-id
  (get-xml-fixups-path xml-object '(|Module| |systemtables| 0 |TOP-LEVEL-MODULE|)))

; read-xml-file (development only)

(defun compare-module-to-xml-file (module gensym-pathname-to-read)
  (let ((module-data (xml-object-and-fixups-for-module module))
	(file-data (xml-object-and-fixups-for-file gensym-pathname-to-read)))
    (prog1 (compare-xml-object-and-fixups module-data file-data t)
      (reclaim-xml-object-and-fixups module-data)
      (reclaim-xml-object-and-fixups file-data))))

(defun compare-xml-files (gensym-pathname-to-read-1 gensym-pathname-to-read-2)
  (let ((file1-data (xml-object-and-fixups-for-file gensym-pathname-to-read-1))
	(file2-data (xml-object-and-fixups-for-file gensym-pathname-to-read-2)))
    (prog1 (compare-xml-object-and-fixups file1-data file2-data t)
      (reclaim-xml-object-and-fixups file1-data)
      (reclaim-xml-object-and-fixups file2-data))))

(defvar xml-output-stream nil)
(defvar length-of-xml-output-line 0)
(defvar xml-output-buffer nil)
(defvar xml-output-position 0)

(defmacro with-xml-output-stream ((file &optional append-p) &body body)
  `(let* ((.file. ,file)
	  (file-name (if (gensym-pathname-p .file.)
			 (gensym-namestring .file.)
			 (copy-text-string .file.)))
	  (xml-output-stream
	    (if ,append-p
		(g2-stream-open-for-appending file-name t)
		(g2-stream-open-for-output file-name)))
	  (xml-output-buffer (obtain-simple-gensym-string write-kb-buffer-length))
	  (xml-output-position 0)
	  (length-of-xml-output-line 0))
     (reclaim-text-string file-name)
     (when xml-output-stream
       (progn ,@body)
       (when (<f 0 xml-output-position)
	 (g2-stream-write-from-buffer
	   xml-output-buffer xml-output-position
	   xml-output-stream))
       (g2-stream-close xml-output-stream)
       (reclaim-simple-gensym-string xml-output-buffer)
       t)))

(defun write-xml-object-to-file (xml-object pathname)
  (with-xml-output-stream (pathname)
    (let ((binary-pathname (gensym-make-pathname :type #w"bkb" :defaults pathname)))
      (write-clear-text-from-xml-object binary-pathname xml-object))))

(defvar show-deletions-in-xml-changes-p nil)

(defun write-xml-changes-to-file (changes file append-p header-plist)
  (with-xml-output-stream (file append-p)
    (kb-format "~%<kbchanges")
    (loop for (name value) on header-plist by 'cddr
	  do (kb-format "~%  ~a=~s" (symbol-name-text-string name) value))
    (kb-format ">")
    (loop for (operation path old new) in changes
	  do (case operation
	       (deletion
		(kb-format "~%~%<delete rdf:resource=\"#~a\"/>" (cdar (last path))))
	       (addition
		(kb-format "~%~%<add>")
		(write-xml-object--item-or-evaluation-value new)
		(kb-format "~%</add>"))
	       (attribute-deletion
		(write-xml-attribute-change operation path old new))
	       (attribute-addition
		(write-xml-attribute-change operation path old new))
	       (change
		(write-xml-attribute-change operation path old new))))
    (kb-format "~%~%</kbchanges>~%~%")))

(defvar write-xml-attribute-change-old-value-p nil)

(defun write-xml-attribute-change (operation path old new)
  (let* ((operation-name (case operation
			   (attribute-deletion "deleteattribute")
			   (attribute-addition "addattribute")
			   (change "changeattribute")))
	 (name-list (get-rdf-name-list-for-context path))
	 (reversed-list (nreverse (copy-list-using-gensym-conses name-list))))
    (kb-format "~%~%<~a rdf:resource=\"#~a\">" operation-name (car reversed-list))
    (loop for element in (cdr reversed-list)
	  do (if (fixnump element)
		 (kb-format "<element index=\"~d\">" element)
		 (kb-format "<~a>" element)))
    (reclaim-gensym-list reversed-list)
    (unless (eq operation 'attribute-addition)
      (when write-xml-attribute-change-old-value-p
	(kb-format "~%")
	(kb-format "<OLDVALUE>")
	(write-xml-object--item-or-evaluation-value old)
	(kb-format "</OLDVALUE>")))
    (unless (eq operation 'attribute-deletion)
      (kb-format "~%")
      (write-xml-object--item-or-evaluation-value new))
    (loop for i from 0 below (1- (length name-list))
	  for element in name-list
	  do (if (fixnump element)
		 (kb-format "</element>")
		 (kb-format "</~a>" element)))
    (kb-format "~%</~a>" operation-name)
    (reclaim-gensym-list name-list)))

;(rdf-type-name-for-node node node-type)
;(rdf-attribute-name-for-attribute node node-type attribute)
(defun get-rdf-name-list-for-context (path)
  (loop for (type . value) in path ; type is in: id file module list item value
	collect (cond ((fixnump value)
		       value)
		      ((eq type 'id)
		       value)
		      (t
		       (get-rdf-attribute-name nil type value 'g2m)))
	  using gensym-cons))

(defvar traversing-xml-object-p nil)

;e.str.: value, type, attributes
;value might be optional, required, or prohibited, throughout the whole structure
;type is file, module, item, primitive-value, sequence, structure,
;        or text (only used for "the text of")
(defun make-xml-object (object type fixups include-value-slot &optional user-attribute-count unit?)
  (if (and (eq type 'primitive-value) (null unit?))
      object
      (allocate-evaluation-structure
	(nconc (when (or object include-value-slot)
		 (eval-list 'value object))
	       (eval-list 'type type)
	       (when unit?
		 (eval-list 'unit unit?))
	       (cond ((eq user-attribute-count 'none)
		      nil)
		     (user-attribute-count
		      (eval-list 'user-attribute-count user-attribute-count))
		     ((and (eq type 'item)
			   (loop for (name value) on fixups by 'cddr
				 when (consp name)
				   return t))
		      (eval-list
			'user-attribute-count
			(loop with user = nil
			      with user-p = nil
			      with current = 0
			      for i from 0
			      for (name value) on fixups by 'cddr
			      for current-user-p = (consp name)
			      do (if (eq user-p current-user-p)
				     (incff current)
				     (progn
				       (eval-push current user)
				       (setq current 1)
				       (setq user-p current-user-p)))
			      finally (return
					(let ((user-list (nreverse user)))
					  (cond ((and (eql (car user-list) 2)
						      (eq (car fixups) 'class)
						      (eq (caddr fixups) 'id)
						      (null (cddr user-list))) ; len <= 2
						 (prog1 (if (cdr user-list)
							    (cadr user-list)
							    current)
						   (reclaim-eval-list user-list)))
						(t
						 (allocate-evaluation-sequence
						   user-list)))))))))
	       (when fixups
		 (if (eq type 'sequence)
		     (eval-list 'elements
				(allocate-evaluation-sequence
				  (prog1 (loop for (name value) on fixups by 'cddr
					       collect value using eval-cons)
				    (reclaim-eval-list fixups))))
		     (eval-list 'attributes
				(allocate-evaluation-structure
				  (prog1 (loop for (name value) on fixups by 'cddr
					       for name-symbol
					       = (if (consp name)
						     (prog1 (if (cdr name)
								(make-unique-slot-name-symbol
								  (cdr name) (car name))
								(car name))
						       (reclaim-eval-cons name))
						     name)
					       nconc (eval-list name-symbol value))
				    (reclaim-eval-list fixups))))))))))

(def-concept do-contents)

(defmacro with-xml-object ((object-and-fixups &optional object-var type-var unit-var) simple complex)
  (let* ((object-and-fixups-var (make-symbol "OBJECT-AND-FIXUPS"))
	 (object-var-1 (or object-var (make-symbol "OBJECT")))
	 (type-var-1 (or type-var (make-symbol "TYPE")))
	 (unit-var-1 (or unit-var (make-symbol "UNIT")))
	 (fixups-var (make-symbol "FIXUPS"))
	 (object-and-fixups-vector-var (make-symbol "OBJECT-AND-FIXUPS-VECTOR")))
    `(let* ((,object-and-fixups-var ,object-and-fixups)
	    (,object-and-fixups-vector-var (when (evaluation-structure-p ,object-and-fixups-var)
					     (evaluation-structure-value ,object-and-fixups-var)))
	    (,type-var-1 (if ,object-and-fixups-vector-var
			     (structure-slot ,object-and-fixups-vector-var 'type)
			     'primitive-value))
	    (,unit-var-1 (if ,object-and-fixups-vector-var
			     (structure-slot ,object-and-fixups-vector-var 'unit)
			     nil))
	    (,object-var-1 (if ,object-and-fixups-vector-var
			       (structure-slot ,object-and-fixups-vector-var 'value)
			       ,object-and-fixups-var)))
       (declare (ignorable ,object-var-1 ,type-var-1 ,unit-var-1))
       (if (or (eq ,type-var-1 'primitive-value)
	       (eq ,type-var-1 'text))
	   ,simple
	   (macrolet ((set-object (new-value)
			`(setf (evaluation-structure-slot ,',object-and-fixups-var 'value)
			       ,new-value)))
	     (if (eq ,type-var-1 'sequence)
		 (let ((,fixups-var (structure-slot ,object-and-fixups-vector-var 'elements)))
		   ,fixups-var
		   (macrolet ((do-contents ((name-var value-var &optional user-p) &body do-contents-body)
				`(when ,',fixups-var
				   (macrolet ((set-value (new-value)
						`(setf (evaluation-sequence-aref ,',',fixups-var ,',name-var)
						       ,new-value)))
				     (loop ,@(when user-p `(with ,user-p = nil))
					   for ,name-var from 0 below (evaluation-sequence-length ,',fixups-var)
					   for ,value-var = (evaluation-sequence-aref ,',fixups-var ,name-var)
					   do (progn ,@do-contents-body))))))
		     ,complex))
		 (let ((,fixups-var (structure-slot ,object-and-fixups-vector-var 'attributes)))
		   ,fixups-var
		   (macrolet ((do-contents ((name-var value-var &optional user-p) &body do-contents-body)
				(if user-p
				    `(when ,',fixups-var
				       (macrolet ((set-value (new-value)
						    `(setf (evaluation-structure-slot ,',',fixups-var ,',name-var)
							   ,new-value)))
					 (loop with .uac. = (structure-slot ,',object-and-fixups-vector-var 'user-attribute-count)
					       with .only-system-attrs-p. = (null .uac.)
					       with .uac-index. = (when (evaluation-sequence-p .uac.) 0)
					       with .uac-length. = (when .uac-index.
								     (evaluation-sequence-length .uac.))
					       with .uac-sys-p. = (fixnump .uac.)
					       with .current-uac. = (cond (.only-system-attrs-p.
									   nil)
									  (.uac-index.
									   (evaluation-sequence-ref
									     .uac. .uac-index.))
									  (.uac-sys-p.
									   2))
					       for (,name-var . ,value-var)
						   being each evaluation-structure-pair of ,',fixups-var
					       for .last-user-p. = nil then ,user-p
					       for ,user-p
						   = (cond (.only-system-attrs-p.
							    nil)
							   ((<f 0 .current-uac.)
							    (decff .current-uac.)
							    .last-user-p.)
							   (.uac-index.
							    (incff .uac-index.)
							    (setq .current-uac.
								  (if (<f .uac-index. .uac-length.)
								      (1-f (evaluation-sequence-ref
									     .uac. .uac-index.))
								      most-positive-fixnum))
							    (not .last-user-p.))
							   (.uac-sys-p.
							    (setq .uac-sys-p. nil)
							    (setq .current-uac. (1-f .uac.))
							    (not .last-user-p.))
							   (t
							    (setq .current-uac. most-positive-fixnum)
							    (not .last-user-p.)))
					       do (progn ,@do-contents-body))))
				    `(when ,',fixups-var
				       (macrolet ((set-value (new-value)
						    `(setf (evaluation-structure-slot ,',',fixups-var ,',name-var)
							   ,new-value)))
					 (loop for (,name-var . ,value-var)
						   being each evaluation-structure-pair of ,',fixups-var
					       do (progn ,@do-contents-body)))))))
		     ,complex))))))))

(defmacro xml-object-and-fixups-type (x)
  `(with-xml-object (,x o type)
     type
     type))

(defun-simple xml-object-unit (x)
  (with-xml-object (x o nil unit)
    unit
    nil))

(defun collect-xml-list (contents type)
  (loop with include-value-slot = t
	with sequencep = (eq type 'sequence)
	for (name value) on contents by 'cddr
	for index from 0
	for kept-value = (when include-value-slot
			   (copy-if-evaluation-value
			     (with-xml-object (value o) o o)))
	nconc (when include-value-slot
		(if sequencep
		    (eval-list kept-value)
		    (eval-list name kept-value)))
	  into value-list
	nconc (eval-list name value)
	  into fixup-list
	finally
	  (reclaim-eval-list contents)
	  (return (make-xml-object
		    (when include-value-slot
		      (case type
			(sequence (allocate-evaluation-sequence value-list))
			(structure (allocate-evaluation-structure value-list))))
		    type
		    fixup-list
		    t))))

(defun make-binary-xml-object (fixups include-value-slot)
  (declare (special g2binary-file-stream))
  (make-xml-object
    (when (and include-value-slot g2binary-file-stream)
      (let ((resource (getf fixups '|rdf:resource|)))
	(when resource
	  (let ((index (get-binary-file-index-from-xml-locator resource)))
	    (when index
	      (multiple-value-bind (value error-string)
		  (read-data-from-g2binary-file index)
		(when error-string
		  (return-from make-binary-xml-object (values nil error-string)))
		value))))))
    'binary
    fixups
    include-value-slot))

(defun xml-object-attribute-is-user-attribute-p (object-and-fixups attribute)
  (with-xml-object (object-and-fixups object type)
    nil
    (do-contents (name value user-p)
      (when (eq name attribute)
	(return-from xml-object-attribute-is-user-attribute-p user-p))))
  nil)

(defun-simple copy-xml-object (object-and-fixups copy-annotations-p)
  (with-xml-object (object-and-fixups object type unit)
    (let ((object-copy (copy-if-evaluation-value object)))
      (if (and (eq type 'primitive-value) (null unit))
	  object-copy
	  (make-xml-object object-copy type nil t nil unit)))
    (let ((value-p (or copy-annotations-p (eq type 'binary))))
      (make-xml-object
	(when value-p
	  (copy-if-evaluation-value object))
	type
	(let ((fixups-reversed nil))
	  (do-contents (name value)
	    (eval-push name fixups-reversed)
	    (eval-push (copy-xml-object value copy-annotations-p) fixups-reversed))
	  (nreverse fixups-reversed))
	value-p
	(copy-if-evaluation-value
	  (evaluation-structure-slot object-and-fixups 'user-attribute-count 'none))
	unit))))

(defun reclaim-xml-object-and-fixups (object-and-fixups)
  (reclaim-if-evaluation-value object-and-fixups))

(defun-simple get-xml-fixups (object-and-fixups indicator user-attribute-p)
  (with-xml-object (object-and-fixups)
    nil
    (do-contents (name value user-p)
      (when (and (eq name indicator)
		 (eq (not (null user-p)) (not (null user-attribute-p))))
	(return-from get-xml-fixups value)))))

(defun-simple replace-xml-fixups (object-and-fixups indicator new-value)
  (with-xml-object (object-and-fixups)
    nil
    (do-contents (name value)
      (when (eq name indicator)
	(reclaim-xml-object-and-fixups value)
	(set-value new-value)
	(return-from replace-xml-fixups nil)))))

(defun-simple get-xml-object (object-and-fixups)
  (with-xml-object (object-and-fixups object) object object))

(defun-simple lookup-xml-object (object-and-fixups)
  (with-xml-object (object-and-fixups object)
    object
    (or object
	(let ((resource (get-xml-fixups object-and-fixups '|rdf:resource| nil)))
	  (when resource
	    (setq object (get-instance-from-xml-locator resource))
	    (when object
	      (set-object object)
	      object))))))

(defun-simple xml-object-text-of-p (object-and-fixups)
  (with-xml-object (object-and-fixups object vtype)
    (eq vtype 'text)
    nil))

(defun-simple xml-object-and-fixups-frame-p (x)
  (with-xml-object (x object type)
    nil
    (and (eq type 'item)
	 (do-contents (name value)
	   (when (eq name 'class)
	     (return-from xml-object-and-fixups-frame-p value))))))

(defun-simple xml-object-and-fixups-evaluation-type (x)
  (with-xml-object (x object type)
    (unless (eq type 'binary)
      (when object
	(evaluation-value-type object)))
    (when (or (eq type 'sequence) (eq type 'structure))
      type)))

(defun-simple xml-object-and-fixups-binary-type (x)
  (with-xml-object (x object type)
    nil
    (when (eq type 'binary)
      'binary)))

(defmacro with-xml-object-attributes
    ((object-and-fixups object-var attribute-var value-var &optional user-p) body)
  `(with-xml-object (,object-and-fixups ,object-var)
     nil
     (do-contents (,attribute-var ,value-var ,@(when user-p `(,user-p)))
       ,body)))

(defun-simple get-xml-object-attribute (object-and-fixups attribute user-p default)
  (with-xml-object-attributes (object-and-fixups obj attr val u-p)
    (when (and (eq attr attribute) (eq u-p user-p))
      (return-from get-xml-object-attribute val)))
  default)

(defun-simple xml-object-has-attributes-p (object-and-fixups)
  (with-xml-object-attributes (object-and-fixups obj attr val)
    (return-from xml-object-has-attributes-p t))
  nil)

(defun-simple get-xml-object-from-id (object-and-fixups id default)
  (with-xml-object (object-and-fixups object)
    nil
    (do-contents (attr val)
      (when (matching-xml-object-id (id-of-xml-object val) id)
	(return-from get-xml-object-from-id val))))
  default)

(defun-simple matching-xml-object-id (id1 id2)
  (or (eq id1 id2)
      (and (text-string-p id1)
	   (text-string-p id2)
	   (string-equalw id1 id2)))) ; it's a uuid in hex, so case doesn't matter

(defun-simple id-of-xml-object (object-and-fixups)
  (get-xml-fixups object-and-fixups 'id nil))

(defvar attr-not-found (list 'attr-not-found))
(defvar xml-object-changes nil)
(defvar compare-xml-collect-diffs-p nil)

(defun find-connection-changes ()
  (loop for d-change in xml-object-changes
	for deletion-p = (eq (first d-change) 'deletion)
	for d-path   = (when deletion-p (second d-change))
	for deletion = (when deletion-p (third d-change))
	for d-input  = (when deletion-p
			 (get-xml-object-attribute deletion 'connection-input nil nil))
	for d-output = (when deletion-p
			 (get-xml-object-attribute deletion 'connection-output nil nil))
	for a-change
	    = (when deletion-p
		(loop for a-change in xml-object-changes
		      for addition-p = (eq (first a-change) 'addition)
		      for a-path   = (when addition-p (second a-change))
		      for addition = (when addition-p (fourth a-change))
		      for a-input  = (when addition-p
				       (get-xml-object-attribute addition 'connection-input nil nil))
		      for a-output = (when addition-p
				       (get-xml-object-attribute addition 'connection-output nil nil))
		      when (and addition-p
				(equalw (cdr d-path) (cdr a-path))
				(compare-xml-object-and-fixups d-input a-input nil)
				(compare-xml-object-and-fixups d-output a-output nil))
			return a-change))
	when a-change
	  collect (gensym-cons d-change a-change)
	    using gensym-cons))

(defun-allowing-unwind compare-xml-object-and-fixups
    (object-and-fixups-1 object-and-fixups-2 collect-diffs-p)
  (let ((xml-object-changes nil)
	(compare-xml-collect-diffs-p collect-diffs-p))
    (catch 'compare-xml-object-and-fixups
      (compare-xml-object-and-fixups-1 object-and-fixups-1 object-and-fixups-2 nil)
      (unless compare-xml-collect-diffs-p
	(return-from compare-xml-object-and-fixups t))
      (loop with connection-changes = (find-connection-changes)
	    for (d-change . a-change) in connection-changes
	    do (setq xml-object-changes (delete-gensym-element d-change xml-object-changes))
	       (setq xml-object-changes (delete-gensym-element a-change xml-object-changes))
	       (compare-xml-object-and-fixups-1
		 (third d-change) (fourth a-change)
		 (copy-list-using-gensym-conses (cdr (second d-change))))
	       (reclaim-xml-change d-change)
	       (reclaim-xml-change a-change))
      (nreverse xml-object-changes))))

(defun-void reclaim-xml-change (change)
  (loop for e in (second change) do
    (reclaim-gensym-cons e))
  (reclaim-gensym-list (second change))
  (reclaim-gensym-list change))

(defun-void reclaim-xml-change-list (changes)
  (loop for change in changes
	do (reclaim-xml-change change))
  (reclaim-gensym-list changes))

(defun-void note-xml-object-difference (path type old new)
  (unless compare-xml-collect-diffs-p
    (throw 'compare-xml-object-and-fixups nil))
  (gensym-push (gensym-list type (copy-list-using-gensym-conses path) old new)
	       xml-object-changes))

(defun-void compare-xml-object-and-fixups-1 (object-and-fixups-1 object-and-fixups-2 path)
  (let ((attr-p-1 (xml-object-has-attributes-p object-and-fixups-1))
	(attr-p-2 (xml-object-has-attributes-p object-and-fixups-2)))
    (if (and attr-p-1 attr-p-2)
	(compare-xml-object-and-fixups-2 object-and-fixups-1 object-and-fixups-2 path)
	(when (or attr-p-1 attr-p-2
		  (not (evaluation-value-eql object-and-fixups-1 object-and-fixups-2)))
	  (note-xml-object-difference path 'change
				      (get-xml-object object-and-fixups-1)
				      (get-xml-object object-and-fixups-2))))))

(defun-void compare-xml-object-and-fixups-2 (object-and-fixups-1 object-and-fixups-2 path)
  (let ((type-1 (with-xml-object (object-and-fixups-1 o-1 t-1) t-1 t-1)))
    (with-xml-object-attributes (object-and-fixups-1 obj-1 attr-1 val-1 user-p-1)
      (if (null attr-1)
	  (let* ((id-1 (id-of-xml-object val-1))
		 (val-2 (get-xml-object-from-id object-and-fixups-2 id-1 attr-not-found))
		 (subpath (gensym-cons (gensym-cons 'id id-1) path)))
	    (if (eq val-2 attr-not-found)
		(note-xml-object-difference subpath 'deletion val-1 nil)
		(compare-xml-object-and-fixups-1 val-1 val-2 subpath))
	    (reclaim-gensym-cons subpath))
	  (let ((val-2 (get-xml-object-attribute object-and-fixups-2 attr-1 user-p-1 attr-not-found))
		(subpath (gensym-cons (gensym-cons type-1 attr-1) path)))
	    (if (eq val-2 attr-not-found)
		(note-xml-object-difference subpath 'attribute-deletion val-1 nil)
		(compare-xml-object-and-fixups-1 val-1 val-2 subpath))
	    (reclaim-gensym-cons subpath)))))
  (let ((type-2 (with-xml-object (object-and-fixups-2 o-2 t-2) t-2 t-2)))
    (with-xml-object-attributes (object-and-fixups-2 obj-2 attr-2 val-2 user-p-2)
      (if (null attr-2)
	  (let* ((id-2 (id-of-xml-object val-2))
		 (val-1 (get-xml-object-from-id object-and-fixups-1 id-2 attr-not-found))
		 (subpath (gensym-cons (gensym-cons 'id id-2) path)))
	    (when (eq val-1 attr-not-found)
	      (note-xml-object-difference subpath 'addition nil val-2))
	    (reclaim-gensym-cons subpath))
	  (let ((val-1 (get-xml-object-attribute object-and-fixups-1 attr-2 user-p-2 attr-not-found))
		(subpath (gensym-cons (gensym-cons type-2 attr-2) path)))
	    (when (eq val-1 attr-not-found)
	      (note-xml-object-difference subpath 'attribute-addition nil val-2))
	    (reclaim-gensym-cons subpath))))))


(defmacro def-xml-checksum (name md5-index)
  (let ((var-name (intern (format nil "~a-XML-CHECKSUM" name))))
    `(progn
       (defvar ,var-name (list ,md5-index nil nil nil))
       (add-xml-checksum ',name ',var-name))))

(defvar all-xml-checksums nil)

(defun add-xml-checksum (name var-name)
  (unless (memq name all-xml-checksums)
    (setq all-xml-checksums
	  (nconc all-xml-checksums
		 (list (cons name var-name)))))
  name)

(def-xml-checksum attribute-name 1)
(def-xml-checksum uuid 2)
(def-xml-checksum value 3)
(def-xml-checksum text 4)
(def-xml-checksum binary 5)

(defvar xml-checksums-enabled-p nil)
(defvar process-checksum-for-image-data-p nil)
(defparameter debug-xml-checksums-p #+development t #-development nil) ; for development
(defparameter debug-clear-text-checksums nil) ; command line flag

(defun initialize-all-xml-checksums ()
  (when xml-checksums-enabled-p
    (loop for (name . var-name) in all-xml-checksums
	  for index+result+debug = (symbol-value var-name)
	  do (init-indexed-MD5-context (first index+result+debug))
	     (reclaim-eval-list (fourth index+result+debug))
	     (setf (fourth index+result+debug) (third index+result+debug))
	     (setf (third index+result+debug) nil))))

(defun finalize-all-xml-checksums ()
  (when xml-checksums-enabled-p
    (loop for (name . var-name) in all-xml-checksums
	  for index+result+debug = (symbol-value var-name)
	  unless (second index+result+debug)
	    do (setf (second index+result+debug) (obtain-simple-gensym-string 16))
	  do (finalize-indexed-MD5-context (first index+result+debug) (second index+result+debug)))))

(defun-void update-xml-checksum-with-text-string (index+result+debug text-string object)
  (when (and process-checksum-for-image-data-p xml-checksums-enabled-p)
    ;; NOTE: the following line is useless, but if we remove it, all XML-KB saved before this
    ;; change, when loading back, will result into "checksums error", although the XML
    ;; file may still be correct. -- Chun Tian (binghe), Feb 2015
    (update-indexed-MD5-context (first index+result+debug) ";")

    (update-indexed-MD5-context-wide (first index+result+debug) text-string)
    (when debug-xml-checksums-p
      (eval-push (copy-if-evaluation-value object)
		 (third index+result+debug)))
    (when debug-clear-text-checksums
      (notify-user-at-console "[[ ~d  ~s ]]"
			      (first index+result+debug)
			      text-string))))

(defun-void update-xml-checksum-with-primitive-object (index+result+debug object)
  (when process-checksum-for-image-data-p
    (let ((text-string (text-string-for-xml-primitive-value object)))
      (update-xml-checksum-with-text-string index+result+debug text-string object)
      (reclaim-text-string text-string))))

(defun-void update-xml-checksum-with-symbol (index+result+debug symbol)
  (when process-checksum-for-image-data-p
    (update-xml-checksum-with-text-string index+result+debug (symbol-name-text-string symbol) symbol)))

(defun get-xml-checksum (index+result+debug)
  (when xml-checksums-enabled-p
    (loop with digest = (second index+result+debug)
	  with result = (obtain-text-string 8)
	  for index from 0 below 8
	  for digest-index = (ashf index 1)
	  do (setf (charw result index)
		   (code-charw
		     (+f (ashf (char-code (schar digest digest-index)) 8)
			 (char-code (schar digest (1+f digest-index))))))
	  finally (return result))))

(defun get-xml-checksum-debug-info (index+result+debug recent-p)
  (copy-list-using-eval-conses
    (if recent-p
	(third index+result+debug)
	(fourth index+result+debug))))

#+development
(defun find-first-checksum-difference (info)
  (let* ((first (nreverse (get-xml-checksum-debug-info info nil)))
	 (second (nreverse (get-xml-checksum-debug-info info t)))
	 (n (loop for i from 0
		  for q1 in first
		  for q2 in second
		  unless (equalw q1 q2)
		    return i)))
    (when n
      (print (loop with start = (max 0 (-f n 20))
		   for i from 0 below (-f n start)
		   for z in (nthcdr start first)
		   collect z))
      (print (loop for i from 0 below 20
		   for z in (nthcdr n first)
		   collect z))
      (print (loop for i from 0 below 20
		   for z in (nthcdr n second)
		   collect z))
      n)))    

(defun get-text-for-xml-checksum (index+result+debug)
  (let ((text-string (if index+result+debug
			 (get-xml-checksum index+result+debug)
			 (make-empty-checksum))))
    (prog1 (twith-output-to-text-string
	     (twrite-uuid-printed-representation text-string))
      (reclaim-text-string text-string))))

(defun-simple make-empty-checksum ()
  (make-stringw 8 :initial-element (code-wide-character 0)))

(defun-void reclaim-xml-checksum (text-string?)
  (when text-string? (reclaim-text-string text-string?)))

(defmacro with-xml-checksums ((enabled-p &optional image-data-p) &body body)
  `(let ((xml-checksums-enabled-p ,enabled-p)
	 (process-checksum-for-image-data-p ,image-data-p))
     (initialize-all-xml-checksums)
     (prog1 (progn ,@body)
       (finalize-all-xml-checksums))))

(defun add-checksums-to-xml-object (xml-object checksums)
  (let ((module-fixups (get-xml-fixups xml-object '|Module| nil)))
    (when module-fixups
      (replace-xml-fixups
	module-fixups '|checksums|
	(make-xml-object-for-evaluation-value checksums))
      (reclaim-if-evaluation-value checksums)))
  xml-object)

(defun get-checksums-from-xml-object (xml-object)
  (get-xml-fixups (get-xml-fixups xml-object '|Module| nil) '|checksums| nil))

(defun checksums-differ-p (checksum1 checksum2)
  (loop for (name . var-name) in all-xml-checksums
	for checksum-sequence-1 = (get-xml-object (get-xml-fixups checksum1 name nil))
	for checksum-sequence-2 = (get-xml-object (get-xml-fixups checksum2 name nil))
	;; NOTE: checksums for certain names may not exist in the KB, because of the
	;; excluding mechanisms, see `compute-checksums-for-xml-object' and
	;; `get-kb-has-been-loaded-from-clear-text-with-differences'. --binghe
	when (and checksum-sequence-1
		  checksum-sequence-2
		  (not (evaluation-value-= checksum-sequence-1 checksum-sequence-2)))
	  collect name using gensym-cons))

(defun check-xml-object-checksums (xml-object)
  (let ((found-checksums
	  (get-checksums-from-xml-object xml-object))
	(computed-checksums
	  (make-xml-object-for-evaluation-value
	    (compute-checksums-for-xml-object xml-object nil))))
    (prog1 (checksums-differ-p found-checksums computed-checksums)
      (reclaim-xml-object-and-fixups computed-checksums))))

(defun get-xml-checksum-information ()
  (when write-checksums-in-xml-file-p
    (allocate-evaluation-structure
      (loop for (name . var-name) in all-xml-checksums
	    for checksum = (get-text-for-xml-checksum nil)
	    nconc (eval-list name checksum)))))

(defun compute-checksums-for-xml-object-1 (xml-object)
  (with-xml-object (xml-object object type unit)
    (cond ((and (eq type 'text) (text-string-p object))
	   (update-xml-checksum-with-text-string
	     text-xml-checksum object object))
	  (t
	   (update-xml-checksum-with-symbol
	     value-xml-checksum type)
	   (when unit
	     (update-xml-checksum-with-symbol
	       value-xml-checksum unit))
	   (update-xml-checksum-with-primitive-object
	     value-xml-checksum object)))
    (progn
      (update-xml-checksum-with-symbol
	attribute-name-xml-checksum type)
      (if (eq type 'binary)
	  (compute-checksums-for-xml-object-2 object)
	  (do-contents (name value user-p)
	    (compute-image-data-checksum? type name value)
	    (cond ((symbolp name)
		   (update-xml-checksum-with-symbol
		     attribute-name-xml-checksum name))
		  ((fixnump name)
		   (update-xml-checksum-with-primitive-object
		     attribute-name-xml-checksum name)))
	    (cond ((and (eq type 'module) (eq name '|checksums|)))
		  ((and (eq type 'item) (eq name 'class) (symbolp value))
		   (update-xml-checksum-with-symbol
		     attribute-name-xml-checksum value))
		  ((and (not user-p)
			(or (eq name 'id)
			    (eq name '|rdf:resource|))
			(text-string-p value))
		   (update-xml-checksum-with-text-string uuid-xml-checksum value value))
		  (t
		   (compute-checksums-for-xml-object-1 value))))))))

(defun compute-image-data-checksum? (type name value)
  (when (eq 'item type)
    (if (and (eq 'image-data name) 
	     (not (get-xml-object-attribute value 'save-image-data-with-kb nil nil)))
	(setq process-checksum-for-image-data-p nil)
	(setq process-checksum-for-image-data-p t))))

(defun compute-checksums-for-xml-object-2 (value)
  (cond ((text-string-p value)
	 (update-xml-checksum-with-text-string
	   binary-xml-checksum value value))
	((evaluation-sequence-p value)
	 (loop for element being each evaluation-sequence-element of value
	       do (compute-checksums-for-xml-object-2 element)))
	((evaluation-structure-p value)
	 (loop for (a-name . a-value) being each evaluation-structure-pair of value
	       do (compute-checksums-for-xml-object-2 a-name)
		  (compute-checksums-for-xml-object-2 a-value)))
	(t
	 (update-xml-checksum-with-primitive-object
	   binary-xml-checksum value))))

(defun compute-checksums-for-xml-object (xml-object module?)
  (let ((xml-checksums-enabled-p t)
	(process-checksum-for-image-data-p t))
    (with-xml-checksums (t t)
      (compute-checksums-for-xml-object-1 xml-object))
    (allocate-evaluation-structure
      (loop with checksums-to-exclude
	      = (if module?
		    (get-kb-has-been-loaded-from-clear-text-with-differences module?)
		    nil)
	    for (name . var-name) in all-xml-checksums
	    for exclude-checksum-p = (memq name checksums-to-exclude)
	    for checksum = (unless exclude-checksum-p
			     (get-text-for-xml-checksum (symbol-value var-name)))
	    unless exclude-checksum-p
	      nconc (eval-list name checksum)
	    finally (reclaim-gensym-list checksums-to-exclude)))))

(defun-simple sequence-of-binary-text-strings-p (x)
  (and (evaluation-sequence-p x)
       (<f 0 (evaluation-sequence-length x))
       (loop for element being each evaluation-sequence-element of x
	     always (binary-wide-string-p element))))

(defvar g2binary-file-name nil)
(defvar g2binary-file-stream nil)
(defvar g2binary-file-position 0)
(defvar current-g2binary-file-symbol-index 0)
(defvar g2binary-file-symbol-list nil)
(defvar g2binary-file-symbol-index-space nil)

(def-global-property-name g2binary-file-symbol-index)
(defvar using-temporary-g2binary-file-symbol-indices-p nil)
(defvar temporary-g2binary-file-symbol-indices nil)

(defun get-g2binary-file-symbol-index (symbol skip-lookup-p)
  (or (unless skip-lookup-p
	(g2binary-file-symbol-index symbol))
      (prog1 (setf (g2binary-file-symbol-index symbol)
		   current-g2binary-file-symbol-index)
	(if using-temporary-g2binary-file-symbol-indices-p
	    (gensym-push symbol temporary-g2binary-file-symbol-indices)
	    (gensym-push symbol g2binary-file-symbol-list))
	(incff current-g2binary-file-symbol-index))))

(defmacro with-temporary-g2binary-file-symbol-indices (&body body)
  `(let ((using-temporary-g2binary-file-symbol-indices-p t)
	 (temporary-g2binary-file-symbol-indices nil)
	 (saved-g2binary-file-symbol-index current-g2binary-file-symbol-index))
     (prog1 (progn ,@body)
       (loop for symbol in temporary-g2binary-file-symbol-indices
	     do (setf (g2binary-file-symbol-index symbol) nil))
       (reclaim-gensym-list temporary-g2binary-file-symbol-indices)
       (setq current-g2binary-file-symbol-index saved-g2binary-file-symbol-index))))

(defun set-g2binary-file-symbol-for-index (index symbol)
  (unless g2binary-file-symbol-index-space
    (setq g2binary-file-symbol-index-space (make-index-space nil nil)))
  (setf (get-object-from-index-space g2binary-file-symbol-index-space index)
	symbol))

(defun get-g2binary-file-symbol-for-index (index)
  (when g2binary-file-symbol-index-space
    (get-object-from-index-space g2binary-file-symbol-index-space index)))

(defsetf get-g2binary-file-symbol-for-index set-g2binary-file-symbol-for-index)

(defmacro with-binary-data-stream ((file) &body forms)
  `(let* ((g2binary-file-name (cond ((gensym-pathname-p ,file)
				     (gensym-namestring ,file))
				    ((text-string-p ,file)
				     (copy-text-string ,file))
				    (t
				     nil)))
	  (g2binary-file-stream g2binary-file-name)
	  (g2binary-file-position 0)
	  (current-g2binary-file-symbol-index 0)
	  (g2binary-file-symbol-list nil)
	  (g2binary-file-symbol-index-space nil))
     (prog1 (progn ,@forms)
       (maybe-close-binary-stream)
       (loop for symbol in g2binary-file-symbol-list
	     do (setf (g2binary-file-symbol-index symbol) nil))
       (reclaim-gensym-list g2binary-file-symbol-list)
       (when g2binary-file-symbol-index-space
	 (reclaim-index-space g2binary-file-symbol-index-space))
       (when (text-string-p g2binary-file-name)
	 (reclaim-text-string g2binary-file-name)))))

(defun maybe-open-binary-output-stream ()
  (when (text-string-p g2binary-file-stream)
    (let ((stream (g2-stream-open-for-binary-output g2binary-file-stream)))
      (unless stream
	(notify-user "Could not open ~A for writing" g2binary-file-stream))
      (setq g2binary-file-stream stream)
      (when stream
	(write-g2binary-file-header)))))

(defun maybe-open-binary-input-stream ()
  (when (text-string-p g2binary-file-stream)
    (let ((stream (g2-stream-open-for-binary-input g2binary-file-stream)))
      (setq g2binary-file-stream stream)
      (unless stream
	(return-from maybe-open-binary-input-stream
	  (tformat-text-string "Could not open ~A for reading" g2binary-file-name)))
      (let ((error-string? (read-g2binary-file-header)))
	(when error-string?
	  (return-from maybe-open-binary-input-stream
	    error-string?)))
      nil)))

(defun report-g2binary-size-error ()
  (tformat-text-string "Error reading ~A: size error" g2binary-file-name))

(defun report-g2binary-error (error-string)
  (tformat-text-string "Error reading ~A: ~A" g2binary-file-name error-string))

(defun maybe-close-binary-stream ()
  (cond ((null g2binary-file-stream))
	((text-string-p g2binary-file-stream)
	 (setq g2binary-file-stream nil))
	(t
	 (g2-stream-close g2binary-file-stream)
	 (setq g2binary-file-stream nil))))

(defvar remaining-bytes-in-g2binary-data nil)

(defun write-fixnum-to-g2binary-stream (fixnum stream)
  (g2-stream-write-char (code-char (logandf #xff (ashf fixnum -24))) stream)
  (g2-stream-write-char (code-char (logandf #xff (ashf fixnum -16))) stream)
  (g2-stream-write-char (code-char (logandf #xff (ashf fixnum -8))) stream)
  (g2-stream-write-char (code-char (logandf #xff fixnum)) stream)
  fixnum)

(defun read-fixnum-from-g2binary-stream (stream)
  (when remaining-bytes-in-g2binary-data
    (decff remaining-bytes-in-g2binary-data 4)
    (unless (<=f 0 remaining-bytes-in-g2binary-data)
      (return-from read-fixnum-from-g2binary-stream
	(values nil (report-g2binary-size-error)))))
  (macrolet ((read-bin-char ()
	       `(prog1 (g2-stream-read-char stream)
		  (unless (most-recent-file-operation-succeeded-p)
		    (return-from read-fixnum-from-g2binary-stream
		      (most-recent-file-operation-status-as-text))))))
    (logiorf (ashf (let ((byte (char-code (read-bin-char))))
		     (if (=f #x80 (logandf #x80 byte))
			 (logiorf (ashf -1 8) byte)
			 byte))
		   24)
	     (ashf (char-code (read-bin-char)) 16)
	     (ashf (char-code (read-bin-char)) 8)
	     (char-code (read-bin-char)))))

(defun write-16bit-unsigned-integer-to-g2binary-stream (integer stream)
  (g2-stream-write-char (code-char (logandf #xff (ashf integer -8))) stream)
  (g2-stream-write-char (code-char (logandf #xff integer)) stream)
  integer)

(defun read-16bit-unsigned-integer-from-g2binary-stream (stream)
  (when remaining-bytes-in-g2binary-data
    (decff remaining-bytes-in-g2binary-data 2)
    (unless (<=f 0 remaining-bytes-in-g2binary-data)
      (return-from read-16bit-unsigned-integer-from-g2binary-stream
	(values nil (report-g2binary-size-error)))))
  (macrolet ((read-bin-char ()
	       `(prog1 (g2-stream-read-char stream)
		  (unless (most-recent-file-operation-succeeded-p)
		    (return-from read-16bit-unsigned-integer-from-g2binary-stream
		      (most-recent-file-operation-status-as-text))))))
    (logiorf (ashf (char-code (read-bin-char)) 8)
	     (char-code (read-bin-char)))))

(defun write-8bit-unsigned-integer-to-g2binary-stream (code stream)
  (g2-stream-write-char (code-char code) stream))

(defun read-8bit-unsigned-integer-from-g2binary-stream (stream)
  (when remaining-bytes-in-g2binary-data
    (decff remaining-bytes-in-g2binary-data 1)
    (unless (<=f 0 remaining-bytes-in-g2binary-data)
      (return-from read-8bit-unsigned-integer-from-g2binary-stream
	(values nil (report-g2binary-size-error)))))
  (macrolet ((read-bin-char ()
	       `(prog1 (g2-stream-read-char stream)
		  (unless (most-recent-file-operation-succeeded-p)
		    (return-from read-8bit-unsigned-integer-from-g2binary-stream
		      (most-recent-file-operation-status-as-text))))))
    (char-code (read-bin-char))))

(defun g2binary-file-header-value ()
  1)

(defun check-g2binary-file-header-value (value)
  (unless (eql value 1)
    (report-g2binary-error #w"Bad header value")))

(defun write-g2binary-file-header ()
  (g2-stream-write-char #\G g2binary-file-stream)
  (g2-stream-write-char #\2 g2binary-file-stream)
  (g2-stream-write-char #\b g2binary-file-stream)
  (g2-stream-write-char #\n g2binary-file-stream)
  (let ((value (g2binary-file-header-value)))
    (write-data-to-g2binary-stream value g2binary-file-stream)
    (reclaim-evaluation-value value)))

(defun read-g2binary-file-header ()
  (macrolet ((read-bin-char ()
	       `(prog1 (g2-stream-read-char g2binary-file-stream)
		  (unless (most-recent-file-operation-succeeded-p)
		    (return-from read-g2binary-file-header
		      (most-recent-file-operation-status-as-text))))))
    (unless (and (char= #\G (read-bin-char))
		 (char= #\2 (read-bin-char))
		 (char= #\b (read-bin-char))
		 (char= #\n (read-bin-char)))
      (return-from read-g2binary-file-header
	(report-g2binary-error "Bad first 4 bytes"))))
  (multiple-value-bind (data error-string?)
      (read-data-from-g2binary-stream g2binary-file-stream)
    (when error-string?
      (return-from read-g2binary-file-header error-string?))
    (check-g2binary-file-header-value data)))

(defun size-in-bytes-of-g2binary-data (value)
  (+f 1
      (cond ((null value)
	     0)
	    ((fixnump value)
	     4)
	    ((evaluation-float-p value)
	     8)
	    ((evaluation-truth-value-p value)
	     2)
	    ((text-string-p value)
	     (+f 4 (*f 2 (lengthw value))))
	    ((symbolp value)
	     (if (g2binary-file-symbol-index value)
		 4
		 (prog1 (+f 4 (*f 2 (lengthw (symbol-name-text-string value))))
		   (get-g2binary-file-symbol-index value t))))
	    ((evaluation-sequence-p value)
	     (+f 4 (loop for element being each evaluation-sequence-element of value
			 summing (size-in-bytes-of-g2binary-data element))))
	    ((evaluation-structure-p value)
	     (+f 4 (loop for (a-name . a-value)
			     being each evaluation-structure-pair of value
			 summing (+f (size-in-bytes-of-g2binary-data a-name)
				   (size-in-bytes-of-g2binary-data a-value)))))
	    (t 0))))

(defun write-g2binary-data-to-stream (value stream)
  (let* ((index nil)
	 (code (cond ((null value)                     0)
		     ((fixnump value)                  1)
		     ((evaluation-float-p value)       2)
		     ((evaluation-truth-value-p value) 3)
		     ((text-string-p value)            4)
		     ((symbolp value)
		      (if (setq index (g2binary-file-symbol-index value))
			  5
			  6))
		     ((evaluation-sequence-p value)    7)
		     ((evaluation-structure-p value)   8))))
    (write-8bit-unsigned-integer-to-g2binary-stream code stream)
    (case code
      (0)
      (1 (write-fixnum-to-g2binary-stream value stream))
      (2 (macrolet ((write-16bit-integer (value)
		      `(write-16bit-unsigned-integer-to-g2binary-stream ,value stream)))
	   (partition-float value write-16bit-integer)))
      (3 (write-16bit-unsigned-integer-to-g2binary-stream
	   (+f 32768 (evaluation-truth-value-value value)) stream))
      (4 (let ((length (lengthw value)))
	   (write-fixnum-to-g2binary-stream length stream)
	   (g2-stream-write-from-wide-string-buffer value length stream)))
      (5 (write-fixnum-to-g2binary-stream index stream))
      (6 (write-fixnum-to-g2binary-stream (get-g2binary-file-symbol-index value t)
					  stream)
	 (let ((value (symbol-name-text-string value))
	       (length (lengthw value)))
	   (write-fixnum-to-g2binary-stream length stream)
	   (g2-stream-write-from-wide-string-buffer value length stream)))
      (7 (write-fixnum-to-g2binary-stream (evaluation-sequence-length value) stream)
	 (loop for element being each evaluation-sequence-element of value
	       do (write-g2binary-data-to-stream element stream)))
      (8 (write-fixnum-to-g2binary-stream
	   (loop for (a-name . a-value) being each evaluation-structure-pair of value
		 summing 1)
	   stream)
	 (loop for (a-name . a-value) being each evaluation-structure-pair of value
	       do (write-g2binary-data-to-stream a-name stream)
		  (write-g2binary-data-to-stream a-value stream))))))

(defun read-g2binary-data-from-stream (stream)
  (multiple-value-bind (code error-string?)
      (read-8bit-unsigned-integer-from-g2binary-stream stream)
    (when error-string?
      (return-from read-g2binary-data-from-stream (values nil error-string?)))
    (read-g2binary-data-from-stream-1 code stream)))

(defun read-g2binary-data-from-stream-1 (code stream)
  (case code
    (0 nil)
    (1 (read-fixnum-from-g2binary-stream stream))
    (2 (multiple-value-bind (b0 error-string?)
	   (read-16bit-unsigned-integer-from-g2binary-stream stream)
	 (when error-string?
	   (return-from read-g2binary-data-from-stream-1 (values nil error-string?)))
	 (multiple-value-bind (b1 error-string?)
	     (read-16bit-unsigned-integer-from-g2binary-stream stream)
	   (when error-string?
	     (return-from read-g2binary-data-from-stream-1 (values nil error-string?)))
	   (multiple-value-bind (b2 error-string?)
	       (read-16bit-unsigned-integer-from-g2binary-stream stream)
	     (when error-string?
	       (return-from read-g2binary-data-from-stream-1 (values nil error-string?)))
	     (multiple-value-bind (b3 error-string?)
		 (read-16bit-unsigned-integer-from-g2binary-stream stream)
	       (when error-string?
		 (return-from read-g2binary-data-from-stream-1 (values nil error-string?)))
	       (reconstruct-managed-float b0 b1 b2 b3))))))
    (3 (multiple-value-bind (value error-string?)
	   (read-16bit-unsigned-integer-from-g2binary-stream stream)
	 (when error-string?
	   (return-from read-g2binary-data-from-stream-1 (values nil error-string?)))
	 (make-evaluation-truth-value (-f value 32768))))
    (4 (multiple-value-bind (length error-string?)
	   (read-fixnum-from-g2binary-stream stream)
	 (when error-string?
	   (return-from read-g2binary-data-from-stream-1 (values nil error-string?)))
	 (when (or (<f length 0)
		   (>f length maximum-byte-vector-16-length))
	   (return-from read-g2binary-data-from-stream-1
	     (values nil (report-g2binary-error #w"Bad string length"))))
	 (decff remaining-bytes-in-g2binary-data (*f 2 length))
	 (unless (<=f 0 remaining-bytes-in-g2binary-data)
	   (return-from read-g2binary-data-from-stream-1
	     (values nil (report-g2binary-size-error))))
	 ;; GENSYMCID-1606: Bad type code when loading image from xml saved kb
	 (let ((string (make-wide-string length)))
	   (g2-stream-read-into-wide-string-buffer string length stream)
	   (unless (most-recent-file-operation-succeeded-p)
	     (return-from read-g2binary-data-from-stream-1
	       (values nil (most-recent-file-operation-status-as-text))))
	   string)))
    (5 (multiple-value-bind (index error-string?)
	   (read-fixnum-from-g2binary-stream stream)
	 (when error-string?
	   (return-from read-g2binary-data-from-stream-1 (values nil error-string?)))
	 (get-g2binary-file-symbol-for-index index)))
    (6 (multiple-value-bind (index error-string?)
	   (read-fixnum-from-g2binary-stream stream)
	 (when error-string?
	   (return-from read-g2binary-data-from-stream-1 (values nil error-string?)))
	 (multiple-value-bind (value error-string?)
	     (read-g2binary-data-from-stream-1 4 stream)
	   (when error-string?
	     (return-from read-g2binary-data-from-stream-1 (values nil error-string?)))
	   (setf (get-g2binary-file-symbol-for-index index)
		 (intern-text-string value)))))
    (7 (allocate-evaluation-sequence
	 (multiple-value-bind (length error-string?)
	     (read-fixnum-from-g2binary-stream stream)
	   (when error-string?
	     (return-from read-g2binary-data-from-stream-1 (values nil error-string?)))
	   (when (or (<f length 0)
		     (>f length (-f maximum-managed-array-size
				    (evaluation-sequence-first-element-index))))
	     (return-from read-g2binary-data-from-stream-1
	       (values nil (report-g2binary-error #w"Bad sequence length"))))
	   (loop with value = nil
		 for i from 0 below length
		 do (multiple-value-setq (value error-string?)
		      (read-g2binary-data-from-stream stream))
		    (when error-string?
		      (return-from read-g2binary-data-from-stream-1 (values nil error-string?)))
		 collect value
		   using eval-cons))))
    (8 (allocate-evaluation-structure
	 (multiple-value-bind (length error-string?)
	     (read-fixnum-from-g2binary-stream stream)
	   (when error-string?
	     (return-from read-g2binary-data-from-stream-1 (values nil error-string?)))
	   (when (or (<f length 0)
		     (>f length (-f (*f length 2)
				    (estructure-first-attribute-index))))
	     (return-from read-g2binary-data-from-stream-1
	       (values nil (report-g2binary-error #w"Bad sequence length"))))
	   (loop with attr = nil
		 with value = nil
		 for i from 0 below length
		 do (multiple-value-setq (attr error-string?)
		      (read-g2binary-data-from-stream stream))
		    (when error-string?
		      (return-from read-g2binary-data-from-stream-1 (values nil error-string?)))
		    (multiple-value-setq (value error-string?)
		      (read-g2binary-data-from-stream stream))
		    (when error-string?
		      (return-from read-g2binary-data-from-stream-1 (values nil error-string?)))
		 nconc (eval-list attr value)))))
    (t (return-from read-g2binary-data-from-stream-1
	 (values nil (report-g2binary-error #w"Bad type code"))))))

(defun write-data-to-g2binary-stream (value stream)
  (write-fixnum-to-g2binary-stream
    (with-temporary-g2binary-file-symbol-indices
      (size-in-bytes-of-g2binary-data value))
    stream)
  (write-g2binary-data-to-stream value stream))

(defun read-data-from-g2binary-stream (stream)
  (multiple-value-bind (size-in-bytes error-string?)
      (read-fixnum-from-g2binary-stream stream)
    (when error-string?
      (return-from read-data-from-g2binary-stream (values nil error-string?)))
    (let ((remaining-bytes-in-g2binary-data size-in-bytes))
      (multiple-value-bind (value error-string?)
	  (read-g2binary-data-from-stream stream)
	(when error-string?
	  (return-from read-data-from-g2binary-stream (values nil error-string?)))
	(unless (=f 0 remaining-bytes-in-g2binary-data)
	  (when error-string?
	    (return-from read-data-from-g2binary-stream
	      (values nil (report-g2binary-size-error)))))
	value))))

(defun get-next-g2binary-file-position ()
  (prog1 g2binary-file-position
    (incff g2binary-file-position)))

(defun write-data-to-g2binary-file (value)
  (when g2binary-file-stream
    (maybe-open-binary-output-stream)
    (write-data-to-g2binary-stream value g2binary-file-stream)))

(defun read-data-from-g2binary-file (index)
  (declare (ignore index))
  (unless g2binary-file-stream
    (return-from read-data-from-g2binary-file
      (values nil (copy-text-string "Binary stream not open"))))
  (let ((error-string? (maybe-open-binary-input-stream)))
    (when error-string?
      (return-from read-data-from-g2binary-file
      (values nil error-string?))))
  (read-data-from-g2binary-stream g2binary-file-stream))

(defun kb-format-write-char (char)
  (cond	(xml-output-stream
	 (setf (schar xml-output-buffer xml-output-position) char)
	 (incff xml-output-position)
	 (setq length-of-xml-output-line
	       (if (char= #\newline char)
		   0
		   (1+f length-of-xml-output-line)))
	 (when (=f xml-output-position write-kb-buffer-length)
	   (g2-stream-write-from-buffer
	     xml-output-buffer write-kb-buffer-length
	     xml-output-stream)
	   (setq xml-output-position 0)))
	#+development
	((not (boundp 'current-kb-save))
	 (write-char char))
	((char= char #\newline)
	 (start-new-kb-line))
	(t
	 (write-char-for-kb-minimal char))))

(defun kb-format-end-of-file ()
  (cond	(xml-output-stream)
	#+development
	((not (boundp 'current-kb-save)))
	(t
	 (update-file-progress-for-writing t))))

(defun kb-format-ensure-beginning-of-line ()
  (cond (xml-output-stream
	 (unless (=f 0 length-of-xml-output-line)
	   (kb-format-write-char #\newline)))
	#+development
	((not (boundp 'current-kb-save))
	 (format t "~&"))
	(t
	 (unless (=f 0 (length-of-saved-kb-line-so-far current-kb-save))
	   (kb-format-write-char #\newline)))))

;type-is-sub-element-of-g2-attribute-and-value-is-attribute-of-type
;type-is-sub-element-of-g2-attribute-and-value-is-contents-of-type
;type-is-attribute-of-g2-attribute-and-value-is-contents-of-g2-attribute
(defvar clear-text-primitive-value-style nil)
(defvar in-write-module-as-clear-text-p nil)
(defvar call-check-node-attribute-value-p nil)
(defvar current-module-being-saved nil)
(defvar writing-xml-p nil)
(defvar writing-xml-cdata-p nil)

(defmacro with-string-for-xml-output ((arg) &body body)
  (let ((reclaimp (make-symbol "RECLAIM-P")))
    `(let* ((,arg ,arg)
	    (,reclaimp (text-string-p ,arg)))
       (when ,reclaimp
	 (setq ,arg (export-text-string ,arg 'utf-8-gensym-string-with-newline)))
       (when (stringp ,arg)
	 ,@body)
       (when ,reclaimp
	 (reclaim-gensym-string ,arg)))))

(defvar kb-format-write-integer-buffer (make-string 12))

(defun-void kb-format-write-integer (arg)
  (when (<f arg 0)
    (kb-format-write-char #\-)
    (setq arg (-f arg)))
  (let ((buffer kb-format-write-integer-buffer)
	(digit-count 0))
    (macrolet ((push-digit (digit)
		 `(progn
		    (setf (schar buffer digit-count) ,digit)
		    (incff digit-count))))
      (loop for number fixnum = arg then next
	    for next fixnum = (floorf-positive number 10)
	    for digit fixnum = (-f number (*f next 10))
	    do (push-digit (digit-char digit))
	    until (=f 0 next)))
    (loop for i from (1- digit-count) downto 0
	  do (kb-format-write-char (schar buffer i)))))

(defun-void kb-format-write-string (arg write-quotes-p quote-markup-p)
  (with-string-for-xml-output (arg)
    (when write-quotes-p
      (kb-format-write-char #\"))
    (loop for j from 0 below (length arg)
	  for char = (char arg j)
	  for replacement
	      = (when quote-markup-p
		  (case char
		    (#\& "&amp;")
		    (#\< "&lt;")
		    (#\> "&gt;")
		    (#\" "&quot;")))
	  do (if replacement
		 (loop for j from 0 below (length replacement)
		       do (kb-format-write-char (schar replacement j)))
		 (kb-format-write-char char)))
    (when write-quotes-p
      (kb-format-write-char #\"))))

(defun kb-format (string &optional arg1 arg2 arg3)
  (loop with arg-index = -1
	with i = 0
	with len = (length string)
	while (<f i len)
	for ch = (prog1 (schar string i) (incff i))
	do (if (char= ch #\~)
	       (let* ((ch1 (char-downcase
			     (prog1 (schar string i) (incff i))))
		      (at-mod (when (char= ch1 #\@)
				(setq ch1 (char-downcase
					    (prog1 (schar string i) (incff i))))
				t))
		      (arg-p (case ch1
			       (#\% at-mod)
			       (#\d t)
			       (#\s t)
			       (#\a t)))
		      (arg (when arg-p
			     (incff arg-index)
			     (case arg-index
			       (0 arg1) (1 arg2) (2 arg3)))))
		 (case ch1
		   (#\& (kb-format-ensure-beginning-of-line))
		   (#\% (kb-format-write-char #\newline)
			(when at-mod
			  (loop for i from 0 below arg
				do (kb-format-write-char #\space)
				   (kb-format-write-char #\space))))
		   (#\d (kb-format-write-integer arg))
		   (#\a (kb-format-write-string
			  arg nil
			  (and writing-xml-p (not writing-xml-cdata-p))))
		   (#\s (kb-format-write-string
			  arg t writing-xml-p))))
	       (kb-format-write-char ch))))




(def-concept traversal)

(defmacro define-traversal-slot (name index)
  (let ((slot-name (intern (format nil "~A-FUNCTION" name))))
    `(defmacro ,slot-name (traversal)
       `(svref ,traversal ,',index))))

(defmacro function-for-traversal (name traversal)
  (let ((slot-name (intern (format nil "~A-FUNCTION" name))))
    `(,slot-name ,traversal)))

(defmacro define-traversal-function ((name traversal) arglist &body body)
  (let ((function-name (intern (format nil "~A-FOR-~A" name traversal))))
    `(defun-simple-into-place (,function-name (function-for-traversal ,name ,traversal))
	 ,arglist
       (progn ,@arglist)
       ,@body)))

(defmacro funcall-traversal-function (traversal-function &rest args)
  `(let ((traversal-function ,traversal-function))
     (when traversal-function
       (funcall-simple-compiled-function traversal-function ,@args))))

(defmacro get-traversal-function (name traversal)
  (let ((slot-name (intern (format nil "~A-FUNCTION" name))))
    `(,slot-name ,traversal)))

(defmacro call-traversal-function (name traversal &rest args)
  `(funcall-traversal-function (get-traversal-function ,name ,traversal) ,@args))

(defmacro make-traversal ()
  `(make-array 5))

(define-traversal-slot run-traverse-kb 0)
(define-traversal-slot run-traverse-kb-node 1)
(define-traversal-slot primitive-value-for-node-definition 2)
(define-traversal-slot reference-for-node-definition 3)
(define-traversal-slot traverse-for-node-definition 4)

(defun tformat-to-stream (stream format-control &optional arg1 arg2)
  (let ((string (tformat-text-string format-control arg1 arg2)))
    (write-text-string-to-stream string stream)
    (reclaim-text-string string)
    nil))

(defun twrite-symbol-name-for-rdf (symbol)
  (loop with name = (export-text-string
		      (symbol-name-text-string symbol)
		      'utf-8-gensym-string-with-newline)
	for i from 0 below (length name)
	for ch = (char name i)
	do (cond ((char= ch #\?)
		  (twrite-char #\_)
		  (twrite-char #\q)
		  (twrite-char #\m))
		 (t
		  (twrite-char ch)))
	finally (reclaim-gensym-string name)))

(defun get-rdf-name-for-symbol-1 (symbol indicator nn-indicator suppress-namespace user-p prefix)
  (let* ((suppress-namespace-p (eq suppress-namespace (if user-p 'g2m 'g2)))
	 (indicator-1 (if suppress-namespace-p nn-indicator indicator)))
    (or (get symbol indicator-1)
	(let ((rdf-name (twith-output-to-gensym-string
			  (tformat
			    "~a~a~a~a"
			    (if suppress-namespace-p "" (if user-p "g2m" "g2"))
			    (if suppress-namespace-p "" ":")
			    (if prefix prefix "")
			    (if prefix "." ""))
			  (twrite-symbol-name-for-rdf symbol))))
	  (mutate-global-property
	    symbol rdf-name indicator-1))))) ; symbol value property -> value

(defun get-rdf-name-for-qualified-attribute-symbol-1
    (unique-name indicator nn-indicator suppress-namespace user-p prefix attribute-name qualifier)
  (let* ((suppress-namespace-p (eq suppress-namespace (if user-p 'g2m 'g2)))
	 (indicator-1 (if suppress-namespace-p nn-indicator indicator)))
    (or (get unique-name indicator-1)
	(let ((rdf-name (twith-output-to-gensym-string
			  (tformat
			    "~a~a~a~a"
			    (if suppress-namespace-p "" (if user-p "g2m" "g2"))
			    (if suppress-namespace-p "" ":")
			    (if prefix prefix "")
			    (if prefix "." ""))
			  (twrite-symbol-name-for-rdf qualifier)
			  (twrite-char #\.)
			  (twrite-symbol-name-for-rdf attribute-name))))
	  (mutate-global-property
	    unique-name rdf-name indicator-1))))) ; symbol value property

(defmacro get-rdf-name-for-symbol (symbol indicator &rest args)
  (unless (constantp indicator)
    (error "~S must be a constant" indicator))
  (let ((indicator (eval indicator)))
    `(get-rdf-name-for-symbol-1
       ,symbol ',indicator ',(intern (format nil "~A-~A" indicator 'no-namespace))
       ,@args)))

(defmacro get-rdf-name-for-qualified-attribute-symbol (symbol indicator &rest args)
  (unless (constantp indicator)
    (error "~S must be a constant" indicator))
  (let ((indicator (eval indicator)))
    `(get-rdf-name-for-qualified-attribute-symbol-1
       ,symbol ',indicator ',(intern (format nil "~A-~A" indicator 'no-namespace))
       ,@args)))

(defun get-rdf-class-name (class &optional suppress-namespace)
  (get-rdf-name-for-symbol
    class 'rdf-class-name suppress-namespace (user-defined-class-p class) "c"))

(defvar writing-g2-rdf-file-p nil)

(defun get-rdf-attribute-name (node node-type attribute &optional suppress-namespace)
  (get-rdf-attribute-name-1
    (eq node-type 'module)
    attribute
    (or (eq node-type 'item)
	(framep node)
	(xml-object-and-fixups-frame-p node))
    (node-attribute-name node node-type attribute)
    (node-attribute-name-qualifier node node-type attribute)
    (if traversing-xml-object-p
	(consp attribute)
	(and (slot-description-p attribute)
	     (user-defined-slot-description-p attribute)))
    suppress-namespace))

(defun get-rdf-attribute-name-1
    (modulep attribute framep name qualifier user-p suppress-namespace)
  (cond ((and (symbolp attribute) (not framep))
	 (if modulep
	     (if (eq suppress-namespace 'g2)
		 (case attribute
		   (version               "version")
		   (system-tables         "systemtables")
		   (external-definitions  "externaldefinitions")
		   (formats               "formats")
		   (panes                 "panes")
		   (checksums             "checksums")
		   (|version|             "version")
		   (|systemtables|        "systemtables")
		   (|externaldefinitions| "externaldefinitions")
		   (|formats|             "formats")
		   (|panes|               "panes")
		   (|checksums|           "checksums"))
		 (case attribute
		   (version               "g2:version")
		   (system-tables         "g2:systemtables")
		   (external-definitions  "g2:externaldefinitions")
		   (formats               "g2:formats")
		   (panes                 "g2:panes")
		   (checksums             "g2:checksums")
		   (|version|             "g2:version")
		   (|systemtables|        "g2:systemtables")
		   (|externaldefinitions| "g2:externaldefinitions")
		   (|formats|             "g2:formats")
		   (|panes|               "g2:panes")
		   (|checksums|           "g2:checksums")))
	     (get-rdf-name-for-symbol
	       name 'rdf-structure-attribute-name suppress-namespace user-p "sa")))
	(qualifier
	 (get-rdf-name-for-qualified-attribute-symbol
	   (if (consp attribute)
	       (make-unique-slot-name-symbol qualifier name)
	       (unique-slot-name attribute))
	   'rdf-qualified-attribute-name
	   suppress-namespace user-p "uq" name qualifier))
	(user-p
	 (get-rdf-name-for-symbol
	   name 'rdf-user-attribute-name suppress-namespace user-p "ua"))
	(t
	 (get-rdf-name-for-symbol
	   name 'rdf-system-attribute-name suppress-namespace user-p "a"))))

(defun write-rdf-schema-for-g2-to-file (file-name) ; "g2-rdf.rdf"
  (let ((stream (g2-stream-open-for-output file-name))
	(writing-g2-rdf-file-p t))
    (when stream
      (tformat-to-stream stream "<rdf:RDF~%")
      (tformat-to-stream stream "  xmlns:rdf=\"http://www.w3.org/TR/WD-rdf-syntax#\"~%")
      (tformat-to-stream stream "  xmlns:rdfs=\"http://www.w3.org/TR/WD-rdf-schema#\"~%")
      (tformat-to-stream stream "  xmlns:g2=\"\">~%~%")
      (tformat-to-stream stream "<rdf:Class rdf:ID=\"Module\">~%")
      (tformat-to-stream stream "  <rdfs:subClassOf resource=\"http://www.w3.org/TR/WD-rdf-schema#Resource\"/>~%")
      (tformat-to-stream stream "</rdf:Class>~%~%")
      (loop for attribute in (node-attributes nil 'module)
	    do (tformat-to-stream stream "<rdf:Property ID=\"~a\" rdfs:domain=\"#Module\"/>~%"
				  (get-rdf-attribute-name nil 'module attribute 'g2)))
      (tformat-to-stream stream "~%")
      ;; "NoValue"?
      (loop for pc in '("RawValue" "Integer" "Float" "Symbol" "Text" "TruthValue" "Sequence" "Structure")
	    do
	(tformat-to-stream stream "<rdf:Class rdf:ID=\"~a\">~%" pc)
	(tformat-to-stream stream "  <rdfs:subClassOf resource=\"http://www.w3.org/TR/WD-rdf-schema#Resource\"/>~%")
	(tformat-to-stream stream "</rdf:Class>~%~%"))
      (tformat-to-stream stream "<rdf:Property ID=\"type\"/>~%~%")
      (tformat-to-stream stream "<rdf:Property ID=\"value\"/>~%~%")
      (tformat-to-stream stream "<rdf:Property ID=\"unit\"/>~%~%")
      (tformat-to-stream stream "<rdf:Class rdf:ID=\"G2Class\">~%")
      (tformat-to-stream stream "  <rdfs:subClassOf resource=\"http://www.w3.org/TR/WD-rdf-schema#Resource\"/>~%")
      (tformat-to-stream stream "</rdf:Class>~%~%")
      (tformat-to-stream stream "<rdf:Class rdf:ID=\"G2Attribute\">~%")
      (tformat-to-stream stream "  <rdfs:subClassOf resource=\"http://www.w3.org/TR/WD-rdf-schema#Property\"/>~%")
      (tformat-to-stream stream "</rdf:Class>~%~%")
      (loop with sorted-class-names = (sort-class-names
					(loop for class being each subclass of 'system-item
					      unless (user-defined-class-p class)
						collect class using eval-cons))
	    with attribute-names = nil
	    for class in sorted-class-names
	    for direct-superior-classes = (direct-superior-classes class)
	    do (tformat-to-stream stream "<G2Class rdf:ID=\"~a\">~%" (get-rdf-class-name class 'g2))
	       (if direct-superior-classes
		   (loop for super-class in direct-superior-classes
			 do (tformat-to-stream stream "  <rdfs:subClassOf resource=\"#~a\"/>~%"
					       (get-rdf-class-name super-class 'g2)))
		   (tformat-to-stream stream "  <rdfs:subClassOf resource=\"#G2Class\"/>~%"))
	       (tformat-to-stream stream "</G2Class>~%~&")
	       (loop with attributes = (class-description-node-attributes (class-description class))
		     with any-p = nil
		     for attribute in attributes
		     for attribute-name = (node-attribute-name nil 'item-or-evaluation-value attribute)
		     unless (memq attribute-name attribute-names)
		       do (eval-push attribute-name attribute-names)
			  (setq any-p t)
			  (tformat-to-stream stream "<G2Attribute rdf:ID=\"~a\"/>~%"
					     (get-rdf-attribute-name nil 'item-or-evaluation-value
								     attribute 'g2))
		     finally (when any-p (tformat-to-stream stream "~%")))
	    finally (tformat-to-stream stream "~%")
		    (reclaim-eval-list sorted-class-names)
		    (reclaim-eval-list attribute-names))
      (tformat-to-stream stream "</rdf:RDF>~%")
      (g2-stream-close stream))))

(defparameter g2-rdf-file-name nil)

(defun get-g2-rdf-file-name ()
  (or g2-rdf-file-name
      (setq g2-rdf-file-name
	    (let* ((major major-version-number-of-current-gensym-product-line)
		   (minor minor-version-number-of-current-gensym-product-line)
		   (quality (case release-quality-of-current-gensym-product-line
			      (#.prototype-release-quality "prototype-")
			      (#.alpha-release-quality "alpha-")
			      (#.beta-release-quality "beta-")
			      (#.release-quality "")))
		   (revision revision-number-of-current-gensym-product-line)
		   (patch? patch-number-of-current-gensym-product-line?))
	      (multiple-value-bind (tenths hundredths)
		  (round minor 10)
		;; skip hundredths if it is 0
		(tformat-text-string
		  "g2-~A~D-~D~A-~D~A~A.rdf"
		  quality
		  major tenths
		  (if (=f hundredths 0) "" hundredths)
		  revision
		  (if patch? "-" "")
		  (if patch? patch? "")))))))

(defun write-rdf-schema-for-g2 ()
  (write-rdf-schema-for-g2-to-file (get-g2-rdf-file-name)))

(defun rdf-type-name-for-node (node node-type include-prefix-p)
  (let ((category (refid-category-of-node node node-type))
	(type (refid-type-of-node node node-type)))
    (case category
      (module
       "g2:Module")
      (item
       (get-rdf-class-name type 'g2m))
      (sequence
       (if include-prefix-p "g2:Sequence" "Sequence"))
      (structure
       (if include-prefix-p "g2:Structure" "Structure"))
      (binary
       (if include-prefix-p "g2:BinaryData" "BinaryData"))
      ((value primitive-value)
       (case type
	 ((nil)       (if include-prefix-p "g2:RawValue" "RawValue"))
	 (integer     (if include-prefix-p "g2:Integer" "Integer"))
	 (long        (if include-prefix-p "g2:Long" "Long"))
	 (float       (if include-prefix-p "g2:Float" "Float"))
	 (symbol      (if include-prefix-p "g2:Symbol" "Symbol"))
	 (text        (if include-prefix-p "g2:Text" "Text"))
	 (truth-value (if include-prefix-p "g2:TruthValue" "TruthValue"))
	 (sequence    (if include-prefix-p "g2:Sequence" "Sequence"))
	 (structure   (if include-prefix-p "g2:Structure" "Structure"))
	 (t
	  #+development
	  (error "Unrecognized type: ~S" type)))))))

(defun rdf-attribute-name-for-attribute (node node-type attribute)
  (if (fixnump attribute)
      "rdf:li"
      (get-rdf-attribute-name node node-type attribute 'g2m)))

(defun-simple attribute-name-for-make-xml-object (node node-type attribute)
  (if (fixnump attribute)
      attribute
      (let ((name (node-attribute-name node node-type attribute))
	    (qualifier (node-attribute-name-qualifier node node-type attribute)))
	(if (or qualifier
		(if traversing-xml-object-p
		    (consp attribute)
		    (and (slot-description-p attribute)
			 (user-defined-slot-description-p attribute))))
	    (eval-cons name qualifier)
	    (if (eq node-type 'module)
		(case attribute
		  (version              '|version|)
		  (system-tables        '|systemtables|)
		  (external-definitions '|externaldefinitions|)
		  (formats              '|formats|)
		  (panes                '|panes|)
		  (checksums            '|checksums|))
		name)))))

(defun node-is-rdf-seq-p (node node-type)
  (let ((category (refid-category-of-node node node-type))
	(type (refid-type-of-node node node-type)))
    (case category
      (sequence t)
      (value
       (case type
	 (sequence t)
	 (t nil)))
      (t nil))))

(defun twrite-refid (refid)
  (cond ((fixnump refid)
	 (tformat "~D" refid))
	((text-string-p refid)
	 (tformat "~A" refid))
	((symbolp refid)
	 (tformat "~A" refid))))

;use the current-saving-context data structure to get the module pathname from the module
(defun rdf-string-for-refid-internal (resource refid)
  (declare (special current-module-being-saved))
  (unless (eq resource 't)
    (cond ((sequence-of-binary-text-strings-p resource)
	   (tformat "~(~A~).bkb" current-module-being-saved))
	  (resource
	   (twrite-refid resource)))
    (tformat "#"))
  (if (listp refid)
      (loop for firstp = t then nil
	    for name in refid
	    do (unless firstp (tformat "."))
	       (twrite-refid name))
      (twrite-refid refid)))

(defun rdf-string-for-refid (resource refid)
  (twith-output-to-gensym-string
    (rdf-string-for-refid-internal resource refid)))

(defun rdf-text-string-for-refid (resource refid)
  (twith-output-to-text-string
    (rdf-string-for-refid-internal resource refid)))

(defparameter write-rdf-for-kb (make-traversal))
(defparameter make-xml-object-for-kb (make-traversal))

(defun get-rdf-header-list ()
  (eval-list '|xmlns:rdf| (copy-text-string #w"http://www.w3.org/TR/WD-rdf-syntax#")
	     '|xmlns:g2|  (copy-text-string (get-g2-rdf-file-name))
	     '|xmlns| (copy-text-string #w""))) ; local ns

(defvar run-traverse-kb-xml-object-type 'file)

(define-traversal-function (run-traverse-kb write-rdf-for-kb)
    (traversal module type)
  (let ((writing-xml-p t))
    (kb-format "<?xml version=\"1.0\"?>~%")
    (kb-format "<rdf:RDF")
    (loop with header = (get-rdf-header-list)
	  while header
	  for name = (eval-pop header)
	  for value = (eval-pop header)
	  do (kb-format "~% ~A=~S" (symbol-name name) value)
	     (reclaim-text-string value))
    (kb-format ">~%")
    (traverse-kb-internal traversal module type)
    (kb-format "~&</rdf:RDF>~%")
    (kb-format-end-of-file)))

(define-traversal-function (run-traverse-kb make-xml-object-for-kb)
    (traversal module type)
  (make-xml-object
    nil
    run-traverse-kb-xml-object-type
    (nconc (get-rdf-header-list)
	   (traverse-kb-internal traversal module type))
    t))

(define-traversal-function (run-traverse-kb-node write-rdf-for-kb)
    (traversal node node-type nesting)
  (when (=f 0 nesting)
    (kb-format "~%"))
  (let ((type-name (rdf-type-name-for-node node node-type t))
	(refid-string? (rdf-string-for-refid-for-node node node-type t)))
    (cond (refid-string?
	   (kb-format "<~a ID=~s>" type-name refid-string?)
	   (reclaim-gensym-string refid-string?))
	  (t
	   (kb-format "<~a>" type-name)))
    (traverse-kb-node-internal traversal node node-type (1+f nesting))
    (kb-format "</~a>" type-name))
  (when (=f 0 nesting)
    (kb-format "~%")))

(define-traversal-function (run-traverse-kb-node make-xml-object-for-kb)
    (traversal node node-type nesting)
  (let ((category (refid-category-of-node node node-type)))
    (when (and (eq 'item category) write-xml-object-items-collected)
      (incff write-xml-object-items-collected)
      (when (and (boundp 'current-kb-save)
		 (kb-transfer-kb-file-progress-display? current-kb-save)
		 (=f 0 (modf-positive write-xml-object-items-collected 10)))
	(update-file-progress-display
	  (kb-transfer-kb-file-progress-display? current-kb-save)
	  write-xml-object-items-collected)))
    (make-xml-object
      (cond ((sequence-of-binary-text-strings-p node)
	     (copy-evaluation-value node))
	    ((evaluation-value-p node)
	     (copy-evaluation-value node))
	    ((framep node)
	     node)
	    (t nil))
      category
      (nconc (when (eq 'item category)
	       (eval-list 'class (refid-type-of-node node node-type)))
	     (let ((refid-text-string?
		     (rdf-text-string-for-refid-for-node node node-type t)))
	       (when refid-text-string?
		 (eval-list 'id refid-text-string?)))
	     (traverse-kb-node-internal traversal node node-type (1+f nesting)))
      t)))

(defmacro writing-attribute-for-write-rdf-for-kb
    ((node node-type nesting attribute value unit? type) &body body)
  `(progn
     (progn ,node ,node-type)
     (let* ((attr-name (when ,attribute
			 (rdf-attribute-name-for-attribute ,node ,node-type ,attribute)))
	    (type-name
	     (when (and (eq clear-text-primitive-value-style
			    'type-is-attribute-of-g2-attribute-and-value-is-contents-of-g2-attribute)
			(node-attribute-value-is-primitive-p ,node ,node-type ,attribute ,value ,type)
			(not (node-attribute-value-is-untyped-primitive-p ,node ,node-type ,attribute ,value ,type)))
	       (rdf-type-name-for-node ,value 'item-or-evaluation-value nil)))
	    (unit-name
	     (when (and type-name ,unit?)
	       (gensym-string-for-xml-primitive-value ,unit?))))
       (when attr-name
	 (kb-format "~@%" ,nesting)
	 (kb-format "<~a" attr-name)
	 (when type-name
	   (kb-format " g2:type=~s" type-name))
	 (when unit-name
	   (kb-format " g2:unit=~s" unit-name))
	 (kb-format ">"))
       (let ((,nesting (if (fixnump ,attribute) ,nesting (1+ ,nesting))))
	 (progn ,nesting)
	 ,@body)
       (when attr-name
	 (kb-format "</~a>" attr-name)))))

(defmacro doing-attribute-for-make-xml-object-for-kb
    ((node node-type nesting attribute value unit? type) &body body)
  `(progn
     (progn ,node ,node-type ,value ,unit? ,type)
     (eval-list
       (attribute-name-for-make-xml-object node node-type attribute)
       (let ((,nesting (if (fixnump ,attribute) ,nesting (1+ ,nesting))))
	 (progn ,nesting)
	 ,@body))))

(defun gensym-string-for-xml-primitive-value (value)
  (when traversing-xml-object-p
    (setq value (get-xml-object value)))
  (let ((value-as-text-string
	  (cond ((text-string-p value)
		 value)
		((symbolp value)
		 (symbol-name-text-string value))
		(t
		 (let ((write-floats-accurately-p t))
		   (declare (special write-floats-accurately-p))
		   (tformat-text-string "~NV" value))))))
    (prog1 (export-text-string value-as-text-string 'utf-8-gensym-string-with-newline)
      (unless (or (eq value-as-text-string value)
		  (symbolp value))
	(reclaim-text-string value-as-text-string)))))

(defun text-string-for-xml-primitive-value (value)
  (cond ((text-string-p value)
	 (copy-text-string value))
	((symbolp value)
	 (copy-text-string (symbol-name-text-string value)))
	(t
	 (let ((write-floats-accurately-p t))
	   (declare (special write-floats-accurately-p))
	   (tformat-text-string "~NV" value)))))

(defun-simple should-use-cdata-p (gensym-string)
  (loop with use-cdata-p = nil
	with can-not-use-cdata-p = nil
	with len = (length gensym-string)
	for i from 0 below len
	for ch = (char gensym-string i)
	when (or (char= ch #\&) (char= ch #\<) (char= ch #\>)
		 (char= ch #\newline) (char= ch #\"))
	  do (setq use-cdata-p t)
	when (and (char= ch #\])
		  (<f (+f i 2) len)
		  (char= (char gensym-string (+f i 1)) #\])
		  (char= (char gensym-string (+f i 2)) #\>))
	  do (setq can-not-use-cdata-p t)
	finally (return (and use-cdata-p (not can-not-use-cdata-p)))))

(define-traversal-function (primitive-value-for-node-definition write-rdf-for-kb)
    (traversal node node-type nesting attribute value unit? type)
  (writing-attribute-for-write-rdf-for-kb (node node-type nesting attribute value unit? type)
    (let* ((value-as-gensym-string
	     (gensym-string-for-xml-primitive-value value))
	   (value-contains-newline-p
	     (position-in-gensym-string #\newline value-as-gensym-string))
	   (writing-xml-cdata-p
	     (should-use-cdata-p value-as-gensym-string))
	   (unit-as-gensym-string
	     (when unit?
	       (gensym-string-for-xml-primitive-value unit?)))
	   (type-name
	     (unless (node-attribute-value-is-untyped-primitive-p node node-type attribute value type)
	       (rdf-type-name-for-node value 'item-or-evaluation-value t)))
	   (style clear-text-primitive-value-style)
	   (only-value-p
	     (eq style
		 'type-is-attribute-of-g2-attribute-and-value-is-contents-of-g2-attribute))
	   (value-is-contents-of-type
	     (eq style
		 'type-is-sub-element-of-g2-attribute-and-value-is-contents-of-type))
	   (value-is-raw (string= type-name "g2:RawValue")))
      (cond ((or (null value)
		 (eq (refid-type-of-node value type) 'sequence))
	     (unless only-value-p
	       (kb-format "<~a/>" type-name)))
	    ((or (null type-name)
		 value-is-contents-of-type
		 only-value-p
		 writing-xml-cdata-p)
	     (when (and type-name (not only-value-p))
	       (kb-format "<~a" type-name)
	       (when unit?
		 (kb-format " g2:unit=~s" unit-as-gensym-string))
	       (kb-format ">"))
	     (when (or writing-xml-cdata-p value-is-raw)
	       (kb-format "<![CDATA["))
	     (when value-contains-newline-p
	       (kb-format "~%"))
	     (if value-is-raw
		 (write-element-for-kb value)
	       (kb-format "~a" value-as-gensym-string))
	     (when value-contains-newline-p
	       (kb-format "~%"))
	     (when (or writing-xml-cdata-p value-is-raw)
	       (kb-format "]]>"))
	     (when (and type-name (not only-value-p))
	       (kb-format "</~a>" type-name)))
	    (t
	     (kb-format "<~a" type-name)
	     (when unit?
	       (kb-format " g2:unit=~s" unit-as-gensym-string))
	     (kb-format " g2:value=~s/>" value-as-gensym-string)))
      (reclaim-gensym-string value-as-gensym-string))))

(define-traversal-function (primitive-value-for-node-definition make-xml-object-for-kb)
    (traversal node node-type nesting attribute value unit? type)
  (doing-attribute-for-make-xml-object-for-kb (node node-type nesting attribute value unit? type)
    (cond ((evaluation-sequence-p value)
	   (make-xml-object (copy-if-evaluation-value value) 'sequence nil t))
	  ((node-attribute-value-is-untyped-primitive-p node node-type attribute value type)
	   (make-xml-object (copy-if-evaluation-value value) 'text nil t))
	  (unit?
	   (make-xml-object (copy-if-evaluation-value value) 'primitive-value nil t nil unit?))
	  (t
	   (copy-if-evaluation-value value)))))

(define-traversal-function (reference-for-node-definition write-rdf-for-kb)
    (traversal node node-type nesting attribute value unit? type)
  (writing-attribute-for-write-rdf-for-kb (node node-type nesting attribute value unit? type)
    (let* ((type-name (rdf-type-name-for-node value type t))
	   (refid-string? (rdf-string-for-refid-for-node value type nil)))
      (kb-format "<~a" type-name)
      (kb-format " rdf:resource=~s/>" (or refid-string? ""))
      (reclaim-if-gensym-string refid-string?))
    (when (eq 'binary (refid-category-of-node value type))
      (write-data-to-g2binary-file
	(node-attribute-binary-value node node-type attribute value type)))))

(define-traversal-function (reference-for-node-definition make-xml-object-for-kb)
    (traversal node node-type nesting attribute value unit? type)
  (doing-attribute-for-make-xml-object-for-kb (node node-type nesting attribute value unit? type)
    (let ((category (refid-category-of-node value type))
	  (resource-string (rdf-text-string-for-refid-for-node value type nil)))
      (make-xml-object
	value category
	(nconc (when (eq category 'item)
		 (eval-list 'class (refid-type-of-node value type)))
	       (eval-list '|rdf:resource| resource-string))
	t))))

(define-traversal-function (traverse-for-node-definition write-rdf-for-kb)
    (traversal node node-type nesting attribute value unit? type)
  (writing-attribute-for-write-rdf-for-kb (node node-type nesting attribute value unit? type)
    (when attribute (kb-format "~@%" nesting))
    (traverse-kb-node traversal value type nesting)))

(define-traversal-function (traverse-for-node-definition make-xml-object-for-kb)
    (traversal node node-type nesting attribute value unit? type)
  (doing-attribute-for-make-xml-object-for-kb (node node-type nesting attribute value unit? type)
    (traverse-kb-node traversal value type nesting)))

(defparameter find-references-for-writing (make-traversal))

(defun node-is-referenced-p (node node-type)
  (declare (ignore node-type))
  (when (and (of-class-p node 'block)
	     (boundp 'current-kb-save))
    (block-referenced-in-current-save-p node)))

(defun set-node-is-referenced-p (node node-type new-value)
  (declare (ignore node-type))
  (when (and (of-class-p node 'block)
	     (boundp 'current-kb-save))
    (setf (block-referenced-in-current-save-p node) new-value)))

(defsetf node-is-referenced-p set-node-is-referenced-p)

(define-traversal-function (run-traverse-kb find-references-for-writing)
    (traversal module type)
  (traverse-kb-internal traversal module type))

(define-traversal-function (run-traverse-kb-node find-references-for-writing)
    (traversal node node-type nesting)
  (traverse-kb-node-internal traversal node node-type nesting))

(define-traversal-function (traverse-for-node-definition find-references-for-writing)
    (traversal node node-type nesting attribute value unit? type)
  (traverse-kb-node traversal value type nesting))

(define-traversal-function (reference-for-node-definition find-references-for-writing)
    (traversal node node-type nesting attribute value unit? type)
  (unless (node-is-uniquely-and-persistantly-named value type)
    (setf (node-is-referenced-p value type) t)))

(defun write-clear-text-from-xml-object (binary-file xml-object)
  (with-binary-data-stream (binary-file)
    (let ((traversing-xml-object-p t)
	  (clear-text-primitive-value-style (xml-primitive-value-style saving-parameters)))
      (traverse-kb write-rdf-for-kb xml-object 'module))))

(defun write-clear-text-from-module (binary-file module)
  (with-binary-data-stream (binary-file)
    (write-module-as-clear-text module nil 'module)))

(defun write-xml-object-from-module (module)
  (with-binary-data-stream (nil)
    (write-module-as-clear-text module t 'module)))

(defun write-xml-object-from-item-or-evaluation-value (item-or-evaluation-value)
  (with-binary-data-stream (nil)
    (write-module-as-clear-text item-or-evaluation-value t 'item-or-evaluation-value)))

(defun write-rdf-schema-for-module ()
  (let ((file-name (gensym-namestring
		     (gensym-merge-pathnames
		       (get-g2-rdf-file-name)
		       (kb-transfer-pathname current-kb-save)))))
    (unless (g2-stream-probe-file-for-exist file-name)
      (write-rdf-schema-for-g2-to-file file-name))))

(defun write-module-as-clear-text (value xml-object-p type)
  (prog1 (let ((in-write-module-as-clear-text-p t)
	       (current-module-being-saved
		 (when (eq type 'module) value))
	       (write-xml-object-items-collected
		 (if xml-object-p 0 nil)))
	   (traverse-kb find-references-for-writing value type)
	   (let ((call-check-node-attribute-value-p (not (kb-has-been-loaded-from-clear-text)))
		 (clear-text-primitive-value-style (xml-primitive-value-style saving-parameters)))
	     (traverse-kb (if xml-object-p
			      make-xml-object-for-kb
			      write-rdf-for-kb)
			  value
			  type)))
    (decache-all-cached-class-node-attributes)
    (decache-all-formats-for-current-module)))

(defun make-xml-object-for-evaluation-value (value)
  (traverse-kb-node make-xml-object-for-kb value 'item-or-evaluation-value 0))

(defparameter find-stripped-text-slot (make-traversal))

(define-traversal-function (run-traverse-kb find-stripped-text-slot)
    (traversal module type)
  (traverse-kb-internal traversal module type))

(define-traversal-function (run-traverse-kb-node find-stripped-text-slot)
    (traversal node node-type nesting)
  (traverse-kb-node-internal traversal node node-type nesting))

(define-traversal-function (traverse-for-node-definition find-stripped-text-slot)
    (traversal node node-type nesting attribute value unit? type)
  (traverse-kb-node traversal value type nesting))

(defun possible-text-stripped-or-proprietary-package-attribute (attribute)
  (and (slot-description-p attribute)
       (or (let ((type-of-slot? (feature-assq 'type (slot-features attribute))))
	     (and type-of-slot?
		  (text-slot-type-p type-of-slot?)
		  (not (free-text-slot-type-p type-of-slot?))))
	   (and (not (user-defined-slot-description-p attribute))
		(eq 'proprietary-package (pretty-slot-name attribute))))))

(define-traversal-function (primitive-value-for-node-definition find-stripped-text-slot)
    (traversal node node-type nesting attribute value unit? type)
  (when (possible-text-stripped-or-proprietary-package-attribute attribute)
    (let ((problem (cond ((and (text-string-p value)
			       (equalw value #w"...."))
			  'text-stripped)
			 ((and (eq 'proprietary-package (pretty-slot-name attribute))
			       (not (listp (proprietary-package node))))
			  'proprietary))))
      (when problem
	(throw 'stripped-text-slot-search (values node problem))))))

(defvar in-find-stripped-text-slot-p nil)

(defun-allowing-unwind module-contains-text-stripped-frames-p (module)
  (multiple-value-bind (node problem)
      (catch 'stripped-text-slot-search
	(let ((in-find-stripped-text-slot-p t))
	  (traverse-kb find-stripped-text-slot module 'module)
	  nil))
    (decache-all-cached-class-node-attributes)
    (values node problem)))

(defun-allowing-unwind item-or-evaluation-value-contains-text-stripped-frames-p (value)
  (multiple-value-bind (node problem)
      (catch 'stripped-text-slot-search
	(let ((in-find-stripped-text-slot-p t))
	  (traverse-kb find-stripped-text-slot value 'item-or-evaluation-value)
	  nil))
    (decache-all-cached-class-node-attributes)
    (values node problem)))

(defvar traverse-kb-queued-nodes)
(defvar traverse-kb-queued-nodes-tail)

(defun enqueue-kb-node (node+type)
  (let ((new (eval-list node+type)))
    (if traverse-kb-queued-nodes-tail
	(setf (cdr traverse-kb-queued-nodes-tail) new)
	(setf traverse-kb-queued-nodes new))
    (setf traverse-kb-queued-nodes-tail new)))

(defun dequeue-kb-node ()
  (when traverse-kb-queued-nodes
    (prog1 (eval-pop traverse-kb-queued-nodes)
      (unless traverse-kb-queued-nodes
	(setq traverse-kb-queued-nodes-tail nil)))))

(defun enqueue-all-items-in-dfs-order (workspace)
  (enqueue-kb-node (eval-cons workspace 'item-or-evaluation-value))
  (loop with item-list = (subitems-in-definition-order-for-clear-text workspace)
	for sub-item in item-list
	for subworkspace = (and (of-class-p sub-item 'entity)
				(permanent-block-p sub-item)
				(car (subworkspaces sub-item)))
	do (enqueue-kb-node (eval-cons sub-item 'item-or-evaluation-value))
	   (when subworkspace
	     (enqueue-all-items-in-dfs-order subworkspace))
	finally (reclaim-eval-list item-list)))

(defun-allowing-unwind traverse-kb (traversal value type)
  (let ((traverse-kb-queued-nodes nil)
	(traverse-kb-queued-nodes-tail nil))
    (unwind-protect (traverse-kb-1 traversal value type)
      (loop for cons in traverse-kb-queued-nodes
	    do (reclaim-eval-cons cons))
      (reclaim-eval-list traverse-kb-queued-nodes))))

(defun traverse-kb-1 (traversal value type)
  (if traversing-xml-object-p
      (with-xml-object (value object)
	nil
	(let ((module-seen-p (not (eq type 'module))))
	  (do-contents (attribute value)
	    (cond ((and (eq attribute '|Module|)
			(eq type 'module))
		   (setq module-seen-p t)
		   (enqueue-kb-node (eval-cons value 'module)))
		  (module-seen-p
		   (enqueue-kb-node (eval-cons value 'item-or-evaluation-value)))))
	  (call-traversal-function run-traverse-kb traversal traversal value type)))
      (let ((array-initialization-evaluation-values-use-designations-p t)
	    (item-color-pattern-returns-overrides-only-p t)
	    (current-computation-flags current-computation-flags))
	(setf (role-serve-inactive-objects?) t)
	(setf (serve-only-permanent-items-p) t)
	(setf (serve-loose-ends-p) t)
	(enqueue-kb-node (eval-cons value type))
	(loop with ws-list = (node-attribute-value value type 'workspaces)
	      for ws being each evaluation-sequence-element of ws-list
	      do (enqueue-all-items-in-dfs-order ws)
	      finally (reclaim-node-attribute-value value type 'workspaces ws-list))
	(call-traversal-function run-traverse-kb traversal traversal value type))))

(defun traverse-kb-internal (traversal module type)
  (declare (ignore module type))
  (if (eq traversal make-xml-object-for-kb)
      (loop for node+type = (dequeue-kb-node)
	    while node+type
	    for (node . node-type) = node+type
	    do (reclaim-eval-cons node+type)
	    nconc (eval-list
		    (if (eq node-type 'module) '|Module| nil)
		    (traverse-kb-node traversal node node-type 0)))
      (loop for node+type = (dequeue-kb-node)
	    while node+type
	    for (node . node-type) = node+type
	    do
	(reclaim-eval-cons node+type)
	(traverse-kb-node traversal node node-type 0))))

(defun write-xml-object--module (xml-object)
  (traverse-kb-node write-rdf-for-kb xml-object 'module 0))

(defun write-xml-object--item-or-evaluation-value (xml-object)
  (let* ((traversal write-rdf-for-kb)
	 (node nil)
	 (node-type 'item-or-evaluation-value)
	 (attribute nil)
	 (value xml-object)
	 (unit? nil)
	 (type 'item-or-evaluation-value)
	 (nesting 0)
	 (fn
	   (cond ((node-attribute-value-is-primitive-p node node-type attribute value type)
		  (get-traversal-function primitive-value-for-node-definition traversal))
		 ((node-attribute-value-is-definition-p node node-type attribute value type)
		  (get-traversal-function traverse-for-node-definition traversal))
		 (t
		  (get-traversal-function reference-for-node-definition traversal)))))
    (funcall-traversal-function
      fn traversal node node-type nesting attribute value unit? type)))

(defun traverse-kb-node (traversal node node-type nesting)
  (call-traversal-function run-traverse-kb-node traversal traversal node node-type nesting))

;; GENSYMCID-1606: Bad type code when loading image from xml saved kb
(defun do-not-save-image-data-p (attribute attributes)
  (and (eq 'image-data attribute) (not (memq 'save-image-data-with-kb attributes))))

(defun traverse-kb-node-internal (traversal node node-type nesting)
  (let ((attributes (node-attributes node node-type)))
    (if (fixnump attributes)
	(if (eq traversal make-xml-object-for-kb)
	    (loop for attribute from 0 below attributes
		  nconc (traverse-kb-attribute traversal node node-type attribute nesting))
	    (loop for attribute from 0 below attributes
		  do (traverse-kb-attribute traversal node node-type attribute nesting)))
	(if (eq traversal make-xml-object-for-kb)
	    (loop for attribute in attributes
		  nconc (traverse-kb-attribute traversal node node-type attribute nesting)
		  finally (reclaim-node-attributes node node-type attributes))
	    (loop for attribute in attributes
		  do (unless (do-not-save-image-data-p attribute attributes)
		       (traverse-kb-attribute traversal node node-type attribute nesting))
		  finally (reclaim-node-attributes node node-type attributes))))))

(defvar traversing-kb-attribute nil)

(defun traverse-kb-attribute (traversal node node-type attribute nesting)
  (let* ((value (node-attribute-value node node-type attribute))
	 (unit? (node-attribute-unit node node-type attribute))
	 (type (node-attribute-type node node-type attribute)))
    (prog1 (unless (skip-node-attribute-value-p node node-type attribute value type)
	     (when call-check-node-attribute-value-p
	       (check-node-attribute-value node node-type attribute value type))
	     (multiple-value-bind (fn module-attribute)
		 (cond ((node-attribute-value-is-primitive-p node node-type attribute value type)
			(get-traversal-function primitive-value-for-node-definition traversal))
		       ((node-attribute-value-is-definition-p node node-type attribute value type)
			(values (get-traversal-function traverse-for-node-definition traversal)
				(and (eq node-type 'module) attribute)))
		       (t
			(get-traversal-function reference-for-node-definition traversal)))
	       (if module-attribute
		   (let ((traversing-kb-attribute module-attribute))
		     (funcall-traversal-function
		       fn traversal node node-type nesting attribute value unit? type))
		   (funcall-traversal-function
		     fn traversal node node-type nesting attribute value unit? type))))
      (reclaim-node-attribute-value node node-type attribute value))))

(defun rdf-resource-for-node (value type)
  (declare (ignore type))
  (cond ((framep value)
	 (let ((module (get-module-block-is-in value)))
	   (when (and module current-module-being-saved
		      (not (eq module current-module-being-saved)))
	     module)))
	((sequence-of-binary-text-strings-p value)
	 value)))

(defun refid-for-node (node node-type)
  (cond ((sequence-of-binary-text-strings-p node)
	 (get-next-g2binary-file-position))
	((eq traversing-kb-attribute 'external-definitions)
	 nil)
	((node-is-uniquely-and-persistantly-named node node-type)
	 (node-unique-and-persistant-name node node-type))
	((not (node-is-referenced-p node node-type))
	 nil)
	((node-is-uniquely-named-p node node-type)
	 (node-unique-name node node-type))
	(t
	 (make-composite-name
	   (index-for-unnamed-node node node-type)
	   (refid-type-of-node node node-type)
	   (multiple-value-bind (superior superior-type)
	       (refid-node-superior node node-type)
	     (when superior-type
	       (refid-for-node superior superior-type)))))))

(defun-simple rdf-string-for-refid-for-node (value type local-p)
  (if traversing-xml-object-p
      (with-xml-object (value)
	nil
	(let ((text-string? (or (get-xml-fixups value '|rdf:resource| nil)
				(get-xml-fixups value 'id nil))))
	  (when (and text-string? (text-string-p text-string?))
	    (export-text-string text-string? 'utf-8-gensym-string-with-newline))))
      (let* ((refid (refid-for-node value type))
	     (resource (or local-p (when refid (rdf-resource-for-node value type))))
	     (refid-string (when refid (rdf-string-for-refid resource refid))))
	(reclaim-refid refid)
	refid-string)))

(defun-simple rdf-text-string-for-refid-for-node (value type local-p)
  (if traversing-xml-object-p
      (with-xml-object (value)
	nil
	(copy-if-text-string (or (get-xml-fixups value '|rdf:resource| nil)
				 (get-xml-fixups value 'id nil))))
      (let* ((refid (refid-for-node value type))
	     (resource (or local-p (when refid (rdf-resource-for-node value type))))
	     (refid-string (when refid (rdf-text-string-for-refid resource refid))))
	(reclaim-refid refid)
	refid-string)))

(defun node-is-uniquely-and-persistantly-named (node node-type)
  (if traversing-xml-object-p
      (or (get-xml-fixups node '|rdf:resource| nil)
	  (get-xml-fixups node 'id nil))
      (case node-type
	(module
	 node)
	(item-or-evaluation-value
	 (framep node)))))

(defun node-unique-and-persistant-name (node node-type) ; also immutable
  (if traversing-xml-object-p
      (or (get-xml-fixups node '|rdf:resource| nil)
	  (get-xml-fixups node 'id nil))
      (case node-type
	(module
	 node)
	(item-or-evaluation-value
	 (item-uuid-representation node)))))

;;; Item-uuid-representation returns a new text string that is the
;;; representation item's uuid.

(defun-simple item-uuid-representation (item)
  (let ((uuid (item-uuid item)))
    (twith-output-to-text-string
      (twrite-uuid-printed-representation uuid)
      (reclaim-text-string uuid))))

;assumes (not (node-is-uniquely-and-persistantly-named node node-type))
(defun node-is-uniquely-named-p (node node-type)
  (case node-type
    (module
     node)
    (item-or-evaluation-value
     (and (of-class-p node 'block)
	  (let* ((name (name-or-names-for-frame node))
		 (frame-or-frames
		   (and name (not (consp name))
			(frame-or-frames-with-this-name name))))
	    (and frame-or-frames
		 (or (not (consp frame-or-frames))
		     (loop with class-description = (class-description-slot node)
			   with count = 0
			   for frame in frame-or-frames
			   when (eq (class-description-slot frame)
				    class-description)
			     do (if (=f count 1)
				    (return nil)
				    (incff count))
			   finally (return (=f count 1))))))))))

;assumes (and (not (node-is-uniquely-and-persistantly-named node node-type))
;             (node-is-uniquely-named-p node node-type))
(defun node-unique-name (node node-type)
  (case node-type
    (item-or-evaluation-value
     (name-or-names-for-frame node))))

(defun index-for-unnamed-node (node node-type)
  (case node-type
    (item-or-evaluation-value
     (let ((superior? (refid-node-superior node node-type)))
       (if superior?
	   (loop with inferiors-of-superior = (subitems-in-definition-order-for-clear-text superior?)
		 with index = 0
		 for inferior in inferiors-of-superior
		 do (cond ((eq node inferior)
			   (loop-finish))
			  ((eq (class-description-slot inferior)
			       (class-description-slot node))
			   (incff index)))
		 finally (reclaim-eval-list inferiors-of-superior)
			 (return index))	       
	   (frame-serial-number node)))))) ; this isn't very good: should canonicalize somehow

(defun make-composite-name (name type superior-refid)
  (eval-cons type (eval-cons name superior-refid)))

(defun reclaim-refid (refid)
  (cond ((text-string-p refid)
	 (reclaim-text-string refid))
	((consp refid)
	 (loop for e in refid
	       do (reclaim-refid e))
	 (reclaim-eval-list refid))))

;called by refid-for-node (and index-for-unnamed-node)
(defun refid-node-superior (node node-type)
  (case node-type
    (item-or-evaluation-value
     (and (framep node)
	  (if (frame-of-class-p node 'workspace)
	      (parent-of-subworkspace? node)
	      (parent-frame node))))))

(defun refid-type-of-node (node node-type)
  (if traversing-xml-object-p
      (or (xml-object-and-fixups-frame-p node)
	  (xml-object-and-fixups-evaluation-type node)
	  (xml-object-and-fixups-binary-type node))
      (case node-type
	(module 'module)
	(item-or-evaluation-value
	 (cond ((framep node)
		(get-class node))
	       ((sequence-of-binary-text-strings-p node)
		'binary)
	       (t
		(let ((type (when node
			      (evaluation-value-type node))))
		  (if (consp type)
		      (car type)
		      type))))))))

(defun refid-category-of-node (node node-type)
  (if traversing-xml-object-p
      (with-xml-object (node object type) type type)
      (case node-type
	(module
	 'module)
	(item-or-evaluation-value
	 (cond ((framep node)
		'item)
	       ((sequence-of-binary-text-strings-p node)
		'binary)
	       ((evaluation-sequence-p node)
		'sequence)
	       ((evaluation-structure-p node)
		'structure)
	       (t
		'primitive-value))))))

(defun node-attributes (node node-type)
  (if traversing-xml-object-p
      (let ((attribute-list nil)
	    (framep (xml-object-and-fixups-frame-p node)))
	(with-xml-object-attributes (node object attribute value user-p)
	  (unless (or (and framep
			   (or (eq attribute 'class)
			       ;; GENSYMCID-1601: Checksum error when trying to load from xml
			       ;;
			       ;; All non-user-defined "ID" attributes were removed, because
			       ;; they're already part of the frame tag property;
			       (and (not user-p)
				    (eq attribute 'id))))
		      (and (not user-p)
			   (or (eq attribute '|rdf:resource|)
			       ;; for other "ID" attributes, make sure only those of text values
			       ;; were removed, since all system "ID" are of text values.
			       ;; -- Chun Tian (binghe), Feb 2015
			       (and (eq attribute 'id)
				    (evaluation-text-p value)))))
	    (eval-push (if user-p
			   (if (eq (symbol-package attribute) keyword-package-1)
			       (multiple-value-bind (qualifier name)
				   (decompose-class-qualified-symbol attribute)
				 (eval-cons name qualifier))
			       (eval-cons attribute nil))
			   attribute)
		       attribute-list)))
	(nreverse attribute-list))
      (case node-type
	(module
	 '(version
	   system-tables
	   ;; 'computation-styles
	   external-definitions
	   ;;workspaces
	   formats
	   ;; 'transient-items-in-limbo
	   ;; 'referenced-g2-windows-and-procedure-invocations
	   panes
	   checksums
	   ))
	(item-or-evaluation-value
	 (cond
	   ((framep node)
	    (when in-write-module-as-clear-text-p
	      (note-saving-frame node))
	    (class-description-node-attributes (class-description-slot node)))
	   ((evaluation-structure-p node)
	    (loop for (name . value) being each evaluation-structure-pair of node
		  collect name using eval-cons))
	   ((evaluation-sequence-p node)
	    (evaluation-sequence-length node))
	   (t
	    nil))))))

(defun reclaim-node-attributes (node node-type attributes)
  (if traversing-xml-object-p
      (loop for a in attributes
	    when (consp a)
	      do (reclaim-eval-cons a)
	    finally (reclaim-eval-list attributes))
      (case node-type
	(item-or-evaluation-value
	 (when (evaluation-structure-p node)
	   (reclaim-eval-list attributes))))))

(defvar all-classes-for-cached-class-description-node-attributes nil)
(defvar all-classes-for-cached-class-description-node-attributes-for-external-definition nil)

(def-global-property-name cached-class-node-attributes)
(def-global-property-name cached-class-node-attributes-for-external-definition)

(defun class-description-node-attributes (class-description)
  (let ((class (class-name-of-class-description class-description)))
    (if (eq traversing-kb-attribute 'external-definitions)
	(or (cached-class-node-attributes-for-external-definition class)
	    (progn
	      (eval-push class all-classes-for-cached-class-description-node-attributes-for-external-definition)
	      (setf (cached-class-node-attributes-for-external-definition class)
		    (compute-class-description-node-attributes class-description))))
	(or (cached-class-node-attributes class)
	    (progn
	      (eval-push class all-classes-for-cached-class-description-node-attributes)
	      (setf (cached-class-node-attributes class)
		    (compute-class-description-node-attributes class-description)))))))

(defun decache-all-cached-class-node-attributes ()
  (loop for class in all-classes-for-cached-class-description-node-attributes
	for attributes = (cached-class-node-attributes class)
	do (setf (cached-class-node-attributes class) nil)
	   (reclaim-eval-list attributes)
	finally (reclaim-eval-list all-classes-for-cached-class-description-node-attributes)
		(setq all-classes-for-cached-class-description-node-attributes nil))
  (loop for class in all-classes-for-cached-class-description-node-attributes-for-external-definition
	for attributes = (cached-class-node-attributes-for-external-definition class)
	do (setf (cached-class-node-attributes-for-external-definition class) nil)
	   (reclaim-eval-list attributes)
	finally (reclaim-eval-list
		  all-classes-for-cached-class-description-node-attributes-for-external-definition)
		(setq all-classes-for-cached-class-description-node-attributes-for-external-definition nil)))

(defvar exclude-secondary-attributes nil)
(defparameter secondary-attributes
  '(authors frame-author-or-authors
    icon-variables icon-color item-color-pattern text-alignment
    border-color text-color background-color foreground-color
    name-box current-attribute-displays
    value-structure-using-unix-time history-structure-using-unix-time
    icon-description icon-description-for-class?
    item-configuration object-configuration))

(defun compute-vas-for-compute-class-description-node-attributes (class-description)
  (loop with all-virtual-attr-name-list
	  = (nconc (all-virtual-attributes-for-class class-description nil)
		   (loop for non-local-attr in virtual-attributes-not-local-to-a-class
			 when (applicable-and-not-deprecated-virtual-attribute-p
				class-description (virtual-attribute non-local-attr) nil)
			   collect non-local-attr using eval-cons))
	for attr-name in all-virtual-attr-name-list
	when (and (not (eq traversing-kb-attribute 'external-definitions))
		  (not (memq attr-name '(value-structure history))) ;use xxx-using-unix-time
		  (not (and exclude-secondary-attributes
			    (memq attr-name secondary-attributes)))
		  (not (and (class-description-of-class-p class-description 'connection)
			    (memq attr-name '(icon-variables icon-color))))
		  (or (and (virtual-attribute-setter? (virtual-attribute attr-name))
			   (memq attr-name '(relationships
					     values-for-table-of-values
					     table-cells
					     g2-list-sequence
					     g2-array-sequence
					     name-box
					     text-font
					     text-alignment
					     current-attribute-displays
					     item-color-pattern
					     icon-color
					     icon-variables
					     manually-disabled?
					     parent-of-subworkspace
					     edges-of-workspace
					     position-in-workspace
					     size-in-workspace
					     minimum-size-in-workspace
					     icon-heading
					     icon-reflection
					     image-data
					     media-bin-data
					     evaluation-attributes
					     strip-text-mark
					     do-not-strip-text-mark
					     default-window-position-and-scale
					     )))
		      (eq attr-name 'following-item-in-workspace-layering)
		      (eq attr-name 'connection-input)
		      (eq attr-name 'connection-output)
		      (eq attr-name 'connection-style)
		      (eq attr-name 'connection-is-directed)
		      (eq attr-name 'connection-vertices)))
	  collect (virtual-attribute attr-name) using eval-cons
	finally (reclaim-eval-list all-virtual-attr-name-list)))
;connection-is-directed ; no setter
;connection-position-sequence ; no setter
;represented-item ; no setter; table-items, superior
;format-type ; no setter
;table-rows ; no setter
;table-font-size ; no setter
;(unless (frame-of-class-p thing 'connection)
;  item-x-position ; size edge orientation
;  item-y-position ; size edge orientation
;  item-width
;  item-height
;  icon-heading
;  icon-reflection

;
(def-global-property-name reason-to-exclude-slot-name)

(defun set-reason-to-exclude-slot-names-1 (value names)
  (loop for name in names
	do (setf (reason-to-exclude-slot-name name) value)))

(defmacro set-reason-to-exclude-slot-names (value &rest names)
  `(set-reason-to-exclude-slot-names-1 ',value ',names))

(set-reason-to-exclude-slot-names nil simulation-details)
(set-reason-to-exclude-slot-names supplied-as-the-id uuid)
(set-reason-to-exclude-slot-names traversal slot-group-for-block? subworkspaces)
(set-reason-to-exclude-slot-names
  saved-as-minimum-size-in-workspace
  minimum-width-of-text-box minimum-height-of-text-box)
(set-reason-to-exclude-slot-names
  not-saved-in-clear-text
  identifier-of-basis-kb filename-of-basis-kb frame-change-log
  kb-version-information-for-change-logging clear-text-history)
(set-reason-to-exclude-slot-names
  dependant
  frame-status-and-notes g2-window-width g2-window-height
  width-of-image height-of-image depth-of-image format-of-image
  g2-window-x g2-window-y
  g2-window-width g2-window-height g2-window-x-resolution g2-window-y-resolution
  gsi-variable-status inherited-attributes java-class-and-interface-names
  import-declarations package-declaration relation-summary change user-password
  procedure-method-name)

(defun reason-to-exclude-slot-description-for-compute-class-description-node-attributes
    (attribute)
  (let ((name (pretty-slot-name attribute))
	(type? nil) (category? nil)
	reason-symbol)
    (cond ((user-defined-slot-description-p attribute)
	   nil)
	  ((not (eq 'unknown (setq reason-symbol (reason-to-exclude-slot-name name 'unknown))))
	   reason-symbol)
	  ((and (eq name 'frame-flags)
		(null (feature-assq 'type (slot-features attribute))))
	   'not-saved-in-clear-text)
	  ((not (or (slot-description-is-of-savable-slot-p attribute)
		    (eq name 'frame-flags)
		    (savable-connection-attribute-p name)))
	   'not-savable)
	  ((not (setq type? (feature-assq 'type (slot-features attribute))))
	   'no-type)
	  ((feature-assq 'previously-put-in-attribute-tables (slot-features attribute))
	   'depreciated)
	  ((text-slot-type-p type?)
	   nil)
	  ((null (setq category? (category-symbol-given-slot-type type?)))
	   'no-category-in-type-specification)
	  ((or (eq category? 'statement)
	       (and (eq name 'data-type-of-variable-or-parameter)
		    (memq category? '(read-only-symbol-data-type read-only-text-data-type
				      read-only-truth-value-data-type))))
	   'dependant)
	  ((not (or (and (slot-value-to-evaluation-value-function category?)
			 (evaluation-value-to-category-function category?))
		    (slot-value-writer category?)))
	   'neither-rw-cei-nor-slot-value-writer))))

(defun compute-sds-for-compute-class-description-node-attributes
    (class-description)
  (loop for attribute in (slot-descriptions class-description)
	for attr-name = (pretty-slot-name attribute)
	unless (or (and exclude-secondary-attributes
			(not (user-defined-slot-description-p attribute))
			(memq attr-name secondary-attributes))
		   (reason-to-exclude-slot-description-for-compute-class-description-node-attributes
		     attribute)
		   (and in-find-stripped-text-slot-p
			(not (possible-text-stripped-or-proprietary-package-attribute attribute))))
	  collect attribute using eval-cons))

(defun compute-class-description-node-attributes (class-description)
  (nconc
    (compute-sds-for-compute-class-description-node-attributes class-description)
    (unless in-find-stripped-text-slot-p
      (compute-vas-for-compute-class-description-node-attributes class-description))))

(defun node-attribute-name (node node-type attribute)
  (declare (ignore node node-type))
  (if (fixnump attribute)
      attribute
      (cond ((slot-description-p attribute)
	     (if (user-defined-slot-description-p attribute)
		 (pretty-slot-name attribute)
		 (alias-slot-name-if-necessary
		   (pretty-slot-name attribute)
		   (defining-class attribute))))
	    ((virtual-attribute-p attribute)
	     (virtual-attribute-name attribute))
	    ((not (consp attribute))
	     attribute)
	    (t
	     (car attribute)))))

(defun node-attribute-name-qualifier (node node-type attribute)
  (declare (ignore node-type))
  (cond ((and (slot-description-p attribute)
	      (user-defined-slot-description-p attribute)
	      (slot-name-needs-qualification-p
		attribute
		(class-description-slot node)))
	 (defining-class attribute))
	((not (consp attribute))
	 nil)
	(t
	 (cdr attribute))))

(defun node-attribute-unique-name (node node-type attribute)
  (declare (ignore node node-type))
  (if (fixnump attribute)
      attribute
      (cond ((slot-description-p attribute)
	     (if (user-defined-slot-description-p attribute)
		 (unique-slot-name attribute)
		 (alias-slot-name-if-necessary
		   (pretty-slot-name attribute)
		   (defining-class attribute))))
	    ((virtual-attribute-p attribute)
	     (virtual-attribute-name attribute))
	    ((not (consp attribute))
	     attribute)
	    (t
	     (car attribute)))))

(defun node-attribute-value (node node-type attribute &aux category-type)
  (when traversing-xml-object-p
    (return-from node-attribute-value
      (if (consp attribute)
	  (get-xml-object-attribute node (if (cdr attribute)
					     (make-unique-slot-name-symbol
					       (cdr attribute) (car attribute))
					     (car attribute))
				    t nil)
	  (get-xml-object-attribute node attribute nil nil))))
  (case node-type
    (module
     (case attribute
       (version
	(allocate-evaluation-structure-inline
	  'major-version major-version-number-of-current-gensym-product-line
	  'minor-version minor-version-number-of-current-gensym-product-line
	  'release-quality (copy-wide-string
			     (case release-quality-of-current-gensym-product-line
			       (#.prototype-release-quality #w"Prototype")
			       (#.alpha-release-quality #w"Alpha")
			       (#.beta-release-quality #w"Beta")
			       (#.release-quality #w"")
			       (t #w"")))
	  'revision revision-number-of-current-gensym-product-line
	  'build-identification (copy-as-wide-string build-identification-string)))
       (system-tables
	(get-xml-system-tables node))
       (external-definitions
	(allocate-evaluation-sequence
	  (loop with name-list
		  = (get-names-of-external-definitions-for-module node)
		for name in name-list
		for cdef = (class-definition name)
		unless (automatically-created-junction-block-class-p cdef)
		collect cdef
		  using eval-cons
		finally (reclaim-eval-list name-list))))
       (workspaces ; used only by the tracersal itself
	(allocate-evaluation-sequence
	  (sort-items-in-definition-order
	    (loop for workspace in (workspaces-belonging-to-this-module node)
		  when (and (null (parent-of-subworkspace? workspace))
			    (permanent-block-p workspace)) ; (collectable-block-p workspace)
		    collect workspace using eval-cons))))
       (formats
	(allocate-evaluation-sequence
	  (sort-items-in-definition-order
	    (copy-list-using-eval-conses (get-formats-for-current-module)))))
       (panes
	(get-xml-pane-information))
       (checksums
	(get-xml-checksum-information))))
    (item-or-evaluation-value
     (cond
       ((framep node)
	(cond ((virtual-attribute-p attribute)
	       (get-attribute-description-evaluation-value node attribute))
	      ((user-defined-slot-description-p attribute)
	       (get-attribute-description-evaluation-value node attribute))
	      ((eq (pretty-slot-name attribute) 'slot-group-for-block?)
	       (get-slot-description-value node attribute))
	      ((eq (pretty-slot-name attribute) 'subworkspaces)
	       (car (subworkspaces node)))
	      ((not (feature-assq 'type (slot-features attribute)))
	       (get-slot-description-value node attribute))
	      ((setq category-type (text-or-the-text-of-slot-p attribute))
	       (if (eq category-type 'frame-edit-timestamp?)
		   (get-slot-description-value node attribute)
		 ;;; GENSYMCID-1823 prevent to write "private" directly into KB XML file
		 (let ((write-proprietary-package-while-saving-xml-kb t))
		   (make-text-string-representation-for-slot-value-itself
		     node
		     (get-slot-description-value node attribute)
		     (feature-assq 'type (slot-features attribute))))))
	      (t
	       (get-attribute-description-evaluation-value node attribute))))
       ((evaluation-structure-p node)
	(evaluation-structure-slot node attribute))
       ((evaluation-sequence-p node)
	(get-item-if-item-reference (evaluation-sequence-ref node attribute)))))))

(defun node-attribute-unit (node node-type attribute)
  (when traversing-xml-object-p
    (return-from node-attribute-unit
      (xml-object-unit (node-attribute-value node node-type attribute))))
  (case node-type
    (item-or-evaluation-value
     (and (framep node)
	  (slot-description-p attribute)
	  (user-defined-slot-description-p attribute)
	  (let ((value (get-user-slot-description-value node attribute)))
	    (and (consp value)
		 (slot-value-number-p (car-of-cons value))
		 (consp (cdr-of-cons value))
		 (get-unit-from-slot-constant value)))))))

(defun-simple text-or-the-text-of-slot-p (attribute)
  (and (slot-description-p attribute)
       (not (user-defined-slot-description-p attribute))
       (let* ((type? (feature-assq 'type (slot-features attribute)))
	      (category? (category-symbol-given-slot-type type?)))
	 (when (or (text-slot-type-p type?)
		   (not (and (slot-value-to-evaluation-value-function category?)
			     (or (evaluation-value-to-category-function category?)
				 (eq (pretty-slot-name attribute) 'simulation-details)))))
	   (or category? 'free)))))

(defun check-node-attribute-value (node node-type attribute value type)
  (declare (ignore type))
  (when traversing-xml-object-p
    (return-from check-node-attribute-value nil))
  (case node-type
    (module)
    (item-or-evaluation-value
     (let (type?)
       (cond
	 ((framep node)
	  (cond ((virtual-attribute-p attribute)
		 nil) ; later
		((user-defined-slot-description-p attribute)
		 (check-attribute-for-clear-text
		   node
		   (node-attribute-unique-name node node-type attribute)
		   value
		   nil))
		((eq (pretty-slot-name attribute) 'slot-group-for-block?))
		((eq (pretty-slot-name attribute) 'subworkspaces))
		((or (text-slot-type-p
		       (setq type? (feature-assq 'type (slot-features attribute))))
		     (let ((category? (category-symbol-given-slot-type type?)))
		       (not (and (slot-value-to-evaluation-value-function category?)
				 (or (evaluation-value-to-category-function category?)
				     (eq (pretty-slot-name attribute) 'simulation-details))))))
		 nil) ; for now, don't check text
		(t
		 (check-attribute-for-clear-text
		   node
		   (node-attribute-unique-name node node-type attribute)
		   value
		   nil))))
	 ((evaluation-structure-p node))
	 ((evaluation-sequence-p node)))))))

(defun reclaim-node-attribute-value (node node-type attribute value)
  (when traversing-xml-object-p
    (return-from reclaim-node-attribute-value nil))
  (case node-type
    (module
     (reclaim-if-evaluation-value value))
    (item-or-evaluation-value
     (cond
       ((framep node)
	(cond ((virtual-attribute-p attribute)
	       (reclaim-if-evaluation-value value))
	      ((user-defined-slot-description-p attribute)
	       (reclaim-if-evaluation-value value))
	      ((eq (pretty-slot-name attribute) 'slot-group-for-block?))
	      ((eq (pretty-slot-name attribute) 'subworkspaces))
	      (t
	       (reclaim-if-evaluation-value value))))))))

(defun node-attribute-type (node node-type attribute)
  (case node-type
    (module
     'item-or-evaluation-value)
    (item-or-evaluation-value
     (if (framep node)
	   (or (frame-attribute-type attribute)
	       'raw)
	 'item-or-evaluation-value))))

(defun frame-attribute-type (attribute)
  (let ((name (and (slot-description-p attribute)
		   (pretty-slot-name attribute)))
	type? category?)
    (cond ((symbolp attribute)
	   nil)	      
	  ((virtual-attribute-p attribute)
	   'item-or-evaluation-value)
	  ((not (slot-description-p attribute))
	   nil)
	  ((user-defined-slot-description-p attribute)
	   'item-or-evaluation-value)
	  ((eq name 'uuid)
	   nil) ; already supplied, as the ID
	  ((eq name 'procedure-method-name)
	   nil)
	  ((memq name '(frame-status-and-notes
			g2-window-x g2-window-y
			g2-window-width g2-window-height
			width-of-image height-of-image depth-of-image format-of-image))
	   nil)
	  ((or (eq name 'minimum-width-of-text-box)
	       (eq name 'minimum-height-of-text-box))
	   nil)
	  ((eq name 'slot-group-for-block?)
	   (unless (eq traversing-kb-attribute 'external-definitions)
	     'icon-slot-group))
	  ((eq name 'subworkspaces)
	   nil)
	  ((not (and (or (slot-description-is-of-savable-slot-p attribute)
			 (eq name 'connection-style)
			 (savable-connection-attribute-p name)
			 (eq name 'frame-flags))
		     (setq type? (feature-assq 'type
					       (slot-features attribute)))
		     (not (feature-assq 'previously-put-in-attribute-tables
					(slot-features attribute)))))
	   nil)
	  ((text-slot-type-p type?)
	   'item-or-evaluation-value)
	  ((null (setq category? (category-symbol-given-slot-type type?)))
	   nil)
	  ((memq category? '(read-only-positive-integer
			     read-only-symbol-data-type read-only-text-data-type
			     read-only-truth-value-data-type
			     gsi-variable-status-code inherited-attributes
			     java-class-and-interface-names java-read-only-import-declarations
			     java-read-only-package-declaration
			     relation-summary statement
			     class-definition-change object-change connection-change message-change
			     user-password))
	   nil)
	  ((or (and (slot-value-to-evaluation-value-function category?)
		    (evaluation-value-to-category-function category?))
	       (eq name 'simulation-details)
	       (slot-value-writer category?))
	   'item-or-evaluation-value)
	  (t
	   nil))))

(defun node-attribute-value-is-primitive-p (node node-type attribute value type)
  (declare (ignore node node-type attribute))
  (if traversing-xml-object-p
      (with-xml-object (value v vtype)
	(not (eq vtype 'binary))
	(and (eq vtype 'sequence)
	     (progn
	       (do-contents (attr val)
		 (return-from node-attribute-value-is-primitive-p nil))
	       t)))
      (case type
	(module
	 (null value))
	(item-or-evaluation-value
	 (or (null value)
	     (symbolp value)
	     (fixnump value)
	     (managed-float-p value)
	     (managed-long-p value)
	     (text-string-p value)
	     (evaluation-truth-value-p value)
	     (and (evaluation-sequence-p value)
		  (=f 0 (evaluation-sequence-length value)))))
	('raw ; shouldn't be RAW without quote? --binghe
	  t))))

(defun node-attribute-value-is-untyped-primitive-p (node node-type attribute value type)
  (declare (ignore node node-type))
  (if traversing-xml-object-p
      (with-xml-object (value o vtype)
	(eq vtype 'text)
	nil)
      (case type
	(module
	 (null value))
	(item-or-evaluation-value
	 (and (or (text-string-p value) (null value))
	      (text-or-the-text-of-slot-p attribute))))))

(defun node-attribute-binary-value (node node-type attribute value type)
  (declare (ignore node attribute type))
  (if traversing-xml-object-p
      (get-xml-object value)
      (case node-type
	(item-or-evaluation-value
	 (when (sequence-of-binary-text-strings-p value)
	   value)))))

(defun node-attribute-value-is-definition-p (node node-type attribute value type)
  (declare (ignore type))
  (when traversing-xml-object-p
    (return-from node-attribute-value-is-definition-p
      (not (get-xml-fixups value '|rdf:resource| nil))))
  (case node-type
    (module
     t)
    (item-or-evaluation-value
     (and (not (sequence-of-binary-text-strings-p value))
	  (or (not (framep value))
	      (and (eq traversing-kb-attribute 'system-tables)
		   (of-class-p value 'system-frame))
	      (and (eq traversing-kb-attribute 'external-definitions)
		   (of-class-p value 'definition))
	      (and (framep node)
		   (not (eq traversing-kb-attribute 'external-definitions))
		   (slot-description-p attribute)
		   (or (user-defined-slot-description-p attribute)
		       (let ((attribute-name (pretty-slot-name attribute)))
			 (or (eq attribute-name 'subworkspaces)
			     (eq attribute-name 'simulation-details)
			     (and (eq attribute-name (parent-attribute-name value))
				  (eq node (parent-frame value))))))))))
    (t
     t)))

(defun node-has-an-interesting-attributes-p (value type)
  (when traversing-xml-object-p
    (return-from node-has-an-interesting-attributes-p t))
  (loop with attributes = (node-attributes value type)
	for value-attribute in attributes
	for value-value = (node-attribute-value value type value-attribute)
	for value-type = (node-attribute-type value type value-attribute)
	unless (skip-node-attribute-value-p value type value-attribute
					    value-value value-type)
	  return (prog1 (node-attribute-name value type value-attribute)
		   (reclaim-node-attribute-value value type value-attribute value-value))
	do (reclaim-node-attribute-value value type value-attribute value-value)
	finally (reclaim-node-attributes value type attributes)
		(return nil)))

(defvar kb-restrictions-names nil)

(defun-simple get-kb-restrictions-names ()
  (or kb-restrictions-names
      (allocate-evaluation-sequence (eval-list 'KB-CONFIGURATION 'KB-RESTRICTIONS))))

(defun skip-node-attribute-value-p (node node-type attribute value type)
  (when traversing-xml-object-p
    (return-from skip-node-attribute-value-p nil))
  (or (and (framep value)
	   (or (not (permanent-block-p value))
	       (and exclude-secondary-attributes
		    (not (node-has-an-interesting-attributes-p value type)))))
      (case node-type
	(module (or (null value)
		    (and (evaluation-sequence-p value)
			 (=f 0 (evaluation-sequence-length value)))))
	(item-or-evaluation-value
	 (and (framep node)
	      (cond ((symbolp attribute)
		     (null value))
		    ((slot-description-p attribute)
		     (if (and (not (feature-assq 'type (slot-features attribute)))
			      (not (or (fixnump value)
				       (managed-float-p value)
				       (text-string-p value)
				       (evaluation-truth-value-p value)
				       (and (evaluation-sequence-p value)
					    (=f 0 (evaluation-sequence-length value))))))
			 t
		     ;; indent is wrong here.
		     (let ((user-slot-p (user-defined-slot-description-p attribute)))
		       (or (eq (if user-slot-p
				   value
				   (get-slot-description-value node attribute))
			       (slot-init-form attribute))
			   (and (not user-slot-p)
				(case (node-attribute-name node node-type attribute)
				  (names
				   (and (of-class-p node 'system-frame)
					(evaluation-value-eql
					 value
					 (if (of-class-p node 'kb-restrictions)
					     (get-kb-restrictions-names)
					     (class node)))))
				  (attribute-initializations
				   (and (evaluation-sequence-p value)
					(=f 0 (evaluation-sequence-length value))))))
			   (and (eq value 'none)
				(not user-slot-p)
				(memq (node-attribute-name node node-type attribute)
				      '(foreground-color background-color)))))))
		    ((virtual-attribute-p attribute)
		     (case (virtual-attribute-name attribute)
		       (relationships
			(=f 0 (evaluation-sequence-length value)))
		       (parent-of-subworkspace
			(null (parent-of-subworkspace? node)))
		       (position-in-workspace
			(not (and (slot-group-for-block? node)
				  (of-class-p (superblock? node) 'kb-workspace))))
		       (size-in-workspace
			(or (null value)
			    (not (and (slot-group-for-block? node)
				      (of-class-p (superblock? node) 'kb-workspace)))))
		       (minimum-size-in-workspace
			(or (null value)
			    (not (and (slot-group-for-block? node)
				      (of-class-p (superblock? node) 'kb-workspace)))
			    (let ((inner-item (if (frame-of-class-p node 'type-in-box)
						  (get-type-in-text-box node)
						  node)))
			      (and (eql 0 (minimum-width-of-text-box inner-item))
				   (eql 0 (minimum-height-of-text-box inner-item))))))
		       (icon-heading
			(eql value 0))
		       (icon-reflection
			(null value))
		       (icon-color
			(or (eq value 'black) (eq value 'foreground)))
		       (item-color-pattern
			(or (frame-of-class-p node 'type-in-box)
			    (frame-of-class-p node 'loose-end)
			    (=f 0 (evaluation-structure-length value))))
		       ((foreground-color background-color)
			(eq value 'none))
		       ((manually-disabled? connection-is-directed do-not-strip-text-mark strip-text-mark)
			(not (evaluation-boolean-is-true-p value)))
		       (evaluation-attributes
			(or (not (evaluation-structure-p value))
			    (and (not (evaluation-boolean-is-true-p
					(evaluation-structure-slot value 'may-refer-to-inactive-items)))
				 (not (evaluation-boolean-is-true-p
					(evaluation-structure-slot value 'may-run-while-inactive))))))
		       (t
			(null value)))))))
	(t nil))))

(defun get-xml-system-tables (node)
  (allocate-evaluation-sequence
    (let ((frames (loop for frame in (get-system-table-suite-for-module-or-nil node)
			when (and (not (of-class-p frame 'server-parameters))
				  (node-has-an-interesting-attributes-p
				    frame 'item-or-evaluation-value))
			  collect frame using eval-cons))
	  (order (gensym-cons 'module-information
			      order-of-system-tables-in-menu)))
      (nconc (loop for name in order
		   for frame = (loop for table in frames
				     when (of-class-p table name)
				       return (progn
						(setq frames (delete-eval-element table frames))
						table))
		   when frame
		     collect frame using eval-cons)
	     (progn
	       (reclaim-gensym-cons order)
	       frames))))) ; in case there were any left over.

(defun get-xml-pane-information ()
  (allocate-evaluation-sequence
    (loop with new-description-p = (not (boundp 'current-kb-save))
	  with description = (if new-description-p
				 (get-pane-description-for-saving-if-any
				   nil
				   current-module-being-saved)
				 (kb-transfer-pane-description? current-kb-save))
	  for (workspace-pf x y xmag ymag) in (if (boundp 'current-kb-save)
						  (kb-transfer-pane-description? current-kb-save)
						  (get-pane-description-for-saving-if-any
						    nil
						    current-module-being-saved))
	  for workspace = (pseudo-frame-item workspace-pf)
	  when (and (not (frame-has-been-reprocessed-p
			   workspace (pseudo-frame-frame-serial-number workspace-pf)))
		    (permanent-block-p workspace))
	    collect (allocate-evaluation-structure-inline
		      'workspace workspace
		      'x-in-workspace x
		      'y-in-workspace y
		      'x-magnification xmag
		      'y-magnification ymag)
	      using eval-cons
	  finally (when new-description-p
		    (reclaim-slot-value description)))))

(defun-simple item-reference< (item-reference1 item-reference2)
  (let* ((held-vector1 (evaluation-item-reference-value item-reference1))
	 (uuid-block1 (get-evaluation-item-reference-vector-uuid-block held-vector1))
	 (held-vector2 (evaluation-item-reference-value item-reference2))
	 (uuid-block2 (get-evaluation-item-reference-vector-uuid-block held-vector2)))
    (if (eq uuid-block1 uuid-block2)
	(<f (evaluation-item-reference-vector-uuid-offset held-vector1)
	    (evaluation-item-reference-vector-uuid-offset held-vector2))
	(uuid< (uuid-block-uuid uuid-block1)
	       (uuid-block-uuid uuid-block2)))))

(defun item-uuid< (item1 item2)
  (item-reference< (uuid item1) (uuid item2)))

(defun sort-items-in-definition-order (block-list)
  (sort-list block-list #'item-uuid< #'identity))

(defun subitems-in-definition-order-for-clear-text (workspace)
  (sort-items-in-definition-order
    (subitems-in-drawing-order-for-clear-text workspace)))

(defmacro do-subitems-in-drawing-order-for-clear-text
    ((block-or-connection-frame workspace) &body body)
  (let ((block (make-symbol "BLOCK"))
	(connection (make-symbol "CONNECTION"))
	(connection-frame (make-symbol "CONNECTION-FRAME")))
    `(loop for ,block being each subblock of ,workspace
	   for ,block-or-connection-frame = ,block
	   unless (or (not (permanent-block-p ,block))
		      (frame-of-class-p ,block 'table-item)
		      (frame-of-class-p ,block 'graph-grid)
		      (and (frame-of-class-p ,block 'text-box)
			   (memq (cadr (get-type-of-slot-if-any ,block 'box-translation-and-text))
				 '(nil statement))))
	     do (progn ,@body)
		(loop for ,connection being the output-connections of ,block
		      for ,connection-frame
			  = (unless (symbolp ,connection)
			      (get-or-make-connection-frame-and-activate-if-appropriate ,connection))
		      for ,block-or-connection-frame = ,connection-frame
		      when (and ,connection-frame
				(permanent-connection-p ,connection))
			do (progn ,@body)))))

(defun subitems-in-drawing-order-for-clear-text (workspace)
  (let ((result nil)) ; see recompute-layer-positions
    (do-subitems-in-drawing-order-for-clear-text ; top to bottom
	(block-or-connection-frame workspace)
      (eval-push block-or-connection-frame result))
    result))

(defun next-lower-item-in-drawing-order-for-clear-text (item)
  (let ((ws? (get-workspace-if-any-for-block item))
	(last nil))
    (when ws?
      (do-subitems-in-drawing-order-for-clear-text ; top to bottom
	  (block-or-connection-frame ws?)
	(when (serve-item-p block-or-connection-frame)
	  (when (eq item last)
	    (return-from next-lower-item-in-drawing-order-for-clear-text
	      block-or-connection-frame))
	  (setq last block-or-connection-frame))))))

(def-virtual-attribute parent-of-subworkspace
    ((class kb-workspace)			;; arg-type-spec
     (or (no-item)
	 (class block))
     ())				;; features
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   nil)
  :getter
  ((block)
   (parent-of-subworkspace? block))
  :setter
  ((block new-value)
   (when new-value
     (let ((disable-stack-error t)
	   (permit-transfer-of-permanent-items-p t))
       (make-subworkspace-action-internal block new-value nil)))))


(def-virtual-attribute unused-area-color
    ((class kb-workspace)
     (or (no-item) symbol)
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((workspace)
	   (or (unused-area-color? workspace) 'default))
  :setter ((workspace value)
	   (if (eq value 'default)
	       (setq value nil))
	   (cond ((not (or (gensym-color-p value)
			   (null value)
			   (eq value 'same-as-workspace)))
		  (tformat-text-string
		    "Unused-area-color must be a color name, DEFAULT, or SAME-AS-WORKSPACE, not ~NF." value))
		 ((eq value (unused-area-color? workspace))
		  nil)
		 (t
		  (setf (unused-area-color? workspace) value)
		  (synchronize-unused-area-color workspace)
		  (invalidate-workspace workspace)
		  nil))))


(def-virtual-attribute edges-of-workspace
    ((class kb-workspace)			;; arg-type-spec
     (structure ((left integer)
		 (top integer)
		 (right integer)
		 (bottom integer))
		(and left top right bottom))
     ())				;; features
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   nil)
  :getter
  ((block)
   (allocate-evaluation-structure
     (eval-list 'left (left-edge-of-block block)
		'top (-w (top-edge-of-block block)) ; see item-y-position
		'right (right-edge-of-block block)
		'bottom (-w (bottom-edge-of-block block)))))
  :setter
  ((workspace new-value) 
   (let ((left (evaluation-structure-slot new-value 'left))
	 (top (-w (evaluation-structure-slot new-value 'top)))
	 (right (evaluation-structure-slot new-value 'right))
	 (bottom (-w (evaluation-structure-slot new-value 'bottom)))
	 (margin (workspace-margin workspace)))
     (when (and (>f (-w right left) (+w margin margin))
		(>f (-w bottom top) (+w margin margin)))
       (multiple-value-bind (updated-left updated-top updated-right updated-bottom)
	   (get-updated-edges-from-elements-and-background
	     workspace left top right bottom margin)
	 (new-change-workspace-edges
	   workspace updated-left updated-top updated-right updated-bottom))
       nil))))

(def-virtual-attribute position-in-workspace
    ((class block)			;; arg-type-spec
     (or (no-item)
	 (structure ((x integer)
		     (y integer)
		     (superior (class kb-workspace)))
		    (and x y superior)))
     ())				;; features
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   nil)
  :getter
  ((block)
   (when (and (not (workspace-p block))
	      (get-workspace-if-any block))
     (allocate-evaluation-structure
       (eval-list 'x (item-x-position block)
		  'y (item-y-position block)
		  'superior (superblock? block)))))
  :setter
  ((item new-value)
   (when new-value
     (let* ((workspace? (evaluation-structure-slot new-value 'superior))
	    (x-in-workspace? (evaluation-structure-slot new-value 'x))
	    (y-in-workspace? (evaluation-structure-slot new-value 'y))
	    (disable-stack-error t)
	    (permit-transfer-of-permanent-items-p t))
       (transfer-action-internal
	 item workspace? x-in-workspace? y-in-workspace?
	 nil nil)))))

(defun get-workspace-if-any-for-block (block)
  (get-workspace-if-any
    (if (of-class-p block 'connection)
	(output-end-object
	  (connection-for-this-connection-frame block))
	block)))

(def-virtual-attribute following-item-in-workspace-layering
    ((class block)			;; arg-type-spec
     (or (no-item)
	 (class block))
     ())				;; features
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   nil)
  :getter
  ((block)
   (when (and (not (workspace-p block))
	      (get-workspace-if-any-for-block block))
     (next-lower-item-in-drawing-order-for-clear-text block)))
  :setter
  ((block above?)
   (when above?
     (let ((workspace? (get-workspace-if-any-for-block block)))
       (cond ((and initializing-clear-text-p
		   above? workspace?
		   (eq (get-workspace-if-any-for-block above?) workspace?))
	      (gensym-push (gensym-cons block above?)
			   (layering-information-for-clear-text workspace?))
	      nil)
	     (t
	      (tformat-text-string "Can not set following-item-in-workspace-layering for ~NF" block)))))))

(def-virtual-attribute size-in-workspace
    ((or (class entity) ; entity-like-p
	 (class chart)
	 (class trend-chart)
	 (class graph)
	 (class readout-table)
	 (class freeform-table)
	 (class free-text)
	 (class borderless-free-text)
	 (class statement)
	 (class message)
	 (class scrap))
     (or (no-item)
	 (structure ((width number)
		     (height number))
		    (and width height)))
     ())				;; features
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   nil)
  :getter
  ((block)
   (when (get-workspace-if-any block)
     (let ((width (width-of-block block))
	   (height (height-of-block block)))
       (when (and (<f 0 width) (<f 0 height))
	 (when (and (of-class-p block 'entity)
		    (not (of-class-p block 'type-in-box)))
	   (multiple-value-bind (width? height?)
	       (transformed-edges-of-entity block t)
	     (when (and width? height?)
	       (setq width width?)
	       (setq height height?))))
	 (allocate-evaluation-structure
	   (eval-list 'width width
		      'height height))))))
  :setter
  ((item new-value)
   (when new-value
     (let ((workspace? (get-workspace-if-any item)))
       (when workspace?
	 (let* ((inner-item (if (frame-of-class-p item 'type-in-box)
				(get-type-in-text-box item)
				item))
		(width (evaluation-structure-slot new-value 'width))
		(fixnum-width (if (evaluation-float-p width)
				  (round (evaluation-float-value width))
				  width))
		(height (evaluation-structure-slot new-value 'height))
		(fixnum-height (if (evaluation-float-p height)
				   (round (evaluation-float-value height))
				   height)))
	   (cond
	     ((<=f fixnum-width 0)
	      (tformat-text-string "The width, ~D, must be positive" width))
	     ((<=f fixnum-height 0)
	      (tformat-text-string "The height, ~D, must be positive" height))
	     (t
	      (let* ((left-edge (left-edge-of-block item))
		     (top-edge (top-edge-of-block item))
		     (right-edge (+f left-edge fixnum-width))
		     (bottom-edge (+f top-edge fixnum-height))
		     (width-for-change-size? width)
		     (height-for-change-size? height)
		     (force-change-to-minimum-size-p t))
		(change-size-per-bounding-rectangle inner-item
		  left-edge top-edge right-edge bottom-edge)
		(unless (eq inner-item item)
		  (change-edges-of-block
		    item left-edge top-edge right-edge bottom-edge))
		nil)))))))))

(def-virtual-attribute minimum-size-in-workspace
    ((or (class type-in-box)
	 (class free-text)
	 (class borderless-free-text)
	 (class statement)
	 (class message)
	 (class scrap))
     (or (no-item)
	 (structure ((width (or integer (member none)))
		     (height (or integer (member none))))
		    (and width height)))
     ())				;; features
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   nil)
  :getter
  ((block)
   (when (get-workspace-if-any block)
     (let* ((inner-item (if (frame-of-class-p block 'type-in-box)
			    (get-type-in-text-box block)
			    block))
	    (width (minimum-width-of-text-box inner-item))
	    (height (minimum-height-of-text-box inner-item)))
       (allocate-evaluation-structure
	 (eval-list 'width (if (<=f width 0) 'none width)
		    'height (if (<=f height 0) 'none height))))))
  :setter
  ((item new-value)
   (when new-value
     (let ((workspace? (get-workspace-if-any item)))
       (when workspace?
	 (let ((inner-item (if (frame-of-class-p item 'type-in-box)
			       (get-type-in-text-box item)
			       item))
	       (width (evaluation-structure-slot new-value 'width))
	       (height (evaluation-structure-slot new-value 'height)))
	   (cond
	     ((and (fixnump width) (<=f width 0))
	      (tformat-text-string "The width, ~D, must be positive" width))
	     ((and (fixnump height) (<=f height 0))
	      (tformat-text-string "The height, ~D, must be positive" height))
	     (t
	      (update-images-of-block inner-item t t)
	      (setf (minimum-width-of-text-box inner-item)
		    (if (eq width 'none)
			0
			width))
	      (setf (minimum-height-of-text-box inner-item)
		    (if (eq height 'none)
			0
			height))
	      (reformat-text-box-in-place inner-item)
	      (update-images-of-block inner-item nil t)
	      (unless (eq inner-item item)
		(change-edges-of-block
		  item
		  (left-edge-of-block inner-item)
		  (top-edge-of-block inner-item)
		  (right-edge-of-block inner-item)
		  (bottom-edge-of-block inner-item)))
	      nil))))))))

(def-virtual-attribute connection-input
    ((class connection)
     (or (no-item)
	 (structure ((item (class item))
		     (port-name (or (no-item) symbol))
		     (side (member top bottom left right))
		     (position integer))))
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter  ((connection)
	    (get-connection-end-evaluation-structure connection 'input)))

(def-virtual-attribute connection-output
    ((class connection)
     (or (no-item)
	 (structure ((item (class item))
		     (port-name (or (no-item) symbol))
		     (side (member top bottom left right))
		     (position integer))))
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter  ((connection)
	    (get-connection-end-evaluation-structure connection 'output)))

(defun get-connection-end-evaluation-structure (connection direction)
  (let* ((connection-structure
	   (connection-for-this-connection-frame connection))
	 (block (if (eq direction 'input)
		    (input-end-object connection-structure)
		    (output-end-object connection-structure))))
    (when block
      ;; get-position-at-this-end-of-connection requires the input and output to be different
      (let ((position (if (eq direction 'input)
			  (input-end-position connection-structure)
			  (output-end-position connection-structure))))
	(allocate-evaluation-structure
	  (nconc
	    (eval-list
	      'item block
	      'side (get-side-given-end-position position)
	      'position (get-position-on-side-given-end-position position))
	    (let ((port-name (get-port-name-given-block-and-connection block connection-structure)))
	      (when port-name
		(eval-list 'port-name port-name)))))))))

(def-virtual-attribute connection-style
    ((class connection)
     (member diagonal orthogonal)
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter  ((connection)
	    (get-style-of-connection
	      (connection-for-this-connection-frame connection))))

(def-virtual-attribute connection-vertices
    ((class connection)
     (sequence integer 1)
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter  ((connection)
	    (allocate-evaluation-sequence
	      (get-connection-vertices-accurately connection nil))))



(defconstant maximum-scale-for-workspaces #.(* (normalized-scale) 4))
(defconstant maximum-scale-for-workspaces-as-float
  (/e (coerce-to-gensym-float maximum-scale-for-workspaces)
      (coerce-to-gensym-float (normalized-scale))))
(defconstant minimum-scale-for-workspaces #.(round (normalized-scale) 128))
(defconstant minimum-scale-for-workspaces-as-float
  (/e (coerce-to-gensym-float minimum-scale-for-workspaces)
      (coerce-to-gensym-float (normalized-scale))))

;; The scale limits are copied from the relevant part of
;; make-window-parameters-plist (in PLATFORMS), and the window coordinate limit
;; is based on X's limit of 16 bit integers for any coordinate.  Window system
;; limits are a bit disorganized in the old windows code, and we're just
;; defining these here for now, and we'll try to do cleanup and move them later!
;; (MHD 5/11/00)


(defun-simple check-for-window-coordinate-problem (coordinate name)
  (unless (<=f most-negative-window-coordinate coordinate most-positive-window-coordinate)
    (tformat-text-string
     "The value for ~a, ~d, is outside the valid range ~d to ~d."
     name coordinate most-negative-window-coordinate most-positive-window-coordinate)))

(defun-simple check-for-workspace-scale-problem (scale? name)
  (cond ((null scale?)
	 nil)
	((not (managed-float-p scale?)) 
	 (tformat-text-string "Illegal value for ~a: ~nv" name scale?))
	((not (<=e minimum-scale-for-workspaces-as-float
		   (managed-float-value scale?)
		   maximum-scale-for-workspaces-as-float))
	 (tformat-text-string
	  "The value for ~a, ~F, is outside the valid range ~f to ~f."
	  name
	  (managed-float-value scale?)
	  minimum-scale-for-workspaces-as-float
	  maximum-scale-for-workspaces-as-float))))

(defun-simple check-for-workspace-scale-pairing-problem (x-scale? y-scale?)
  (unless (or (and (null x-scale?) (null y-scale?))
	      (and x-scale? y-scale?))
    (tformat-text-string
     "The value for x-scale/y-scale, ~NF and ~NF, must either both be specified or both left unspecified."
     (or x-scale? "none")
     (or y-scale? "none"))))

(def-virtual-attribute default-window-position-and-scale
    ((class kb-workspace)
     (or (no-item)
	 (structure ((x integer)
		     (y integer)
		     (x-scale float)
		     (y-scale float))
		    (and x y)))
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((workspace)
	   (let ((info? (getf (plist-of-remembered-window-positions-and-scales workspace) 'detail-pane)))
	     (when info?
	       (allocate-evaluation-structure
		 (nconc (eval-list 'x (first info?) 'y (second info?))
			(unless (and (=f (third info?) (normalized-scale))
				     (=f (fourth info?) (normalized-scale)))
			  (eval-list 'x-scale (unnormalized-managed-float-for-value (third info?))
				     'y-scale (unnormalized-managed-float-for-value (fourth info?)))))))))
  :setter ((workspace value)
	   (when value
	     (let* ((x (evaluation-structure-slot value 'x))
		    (y (evaluation-structure-slot value 'y))
		    (x-scale? (evaluation-structure-slot value 'x-scale))
		    (y-scale? (evaluation-structure-slot value 'y-scale))
		    (problem-text-string?
		      (or (check-for-window-coordinate-problem x 'x)
			  (check-for-window-coordinate-problem y 'y)
			  (check-for-workspace-scale-problem x-scale? 'x-scale)
			  (check-for-workspace-scale-problem y-scale? 'y-scale)
			  (check-for-workspace-scale-pairing-problem x-scale? y-scale?))))
	       (or problem-text-string?
		   (progn
		     (set-remembered-window-position-and-scale
		       workspace 'detail-pane x y
		       (or x-scale? (allocate-managed-float 1.0))
		       (or y-scale? (allocate-managed-float 1.0)))
		     nil))))))

(defvar classes-sorted-so-far nil)
(defvar classes-remaining-to-sort nil)

(defun sort-class-names (class-list)
  (let ((classes-sorted-so-far nil)
	(classes-remaining-to-sort (nreverse class-list)))
    (loop while classes-remaining-to-sort
	  for class-with-no-predecessors
	      = (find-class-with-no-predecessors
		  (car classes-remaining-to-sort) (cdr classes-remaining-to-sort))
	  do (eval-push class-with-no-predecessors classes-sorted-so-far)
	     (setq classes-remaining-to-sort
		   (delete-eval-element class-with-no-predecessors classes-remaining-to-sort)))
    classes-sorted-so-far))

(defun find-class-with-no-predecessors (class class-list)
  (if (null class-list)
      class
      (find-class-with-no-predecessors
	(if (memq (car class-list)
		  (class-inheritance-path (class-description class)))
	    (car class-list)
	    class)
	(cdr class-list))))

(defvar all-classes-for-indirectly-referenced-class nil)

(def-global-property-name indirectly-referenced-class-p)

(defun note-indirectly-referenced-class (class)
  (setf (indirectly-referenced-class-p class) t)
  (eval-push class all-classes-for-indirectly-referenced-class)
  class)

(defun decache-all-indirectly-referenced-classes ()
  (loop for class in all-classes-for-indirectly-referenced-class
	do (setf (indirectly-referenced-class-p class) nil)
	finally (reclaim-eval-list all-classes-for-indirectly-referenced-class)
		(setq all-classes-for-indirectly-referenced-class nil)))

(defun mark-all-classes-defined-in-module (module)
  (loop for subclass being each subclass of 'block
	when (and (user-defined-class-p subclass)
		  (within-module-p (class-definition subclass) module))
	  collect (note-indirectly-referenced-class subclass)
	    using eval-cons))

(defun collect-unmarked-superiors-of-class (needed-class)
  (loop for class in (class-inheritance-path (class-description needed-class))
	when (and (user-defined-class-p needed-class)
		  (not (indirectly-referenced-class-p needed-class)))
	  collect (note-indirectly-referenced-class needed-class)
	    using eval-cons))  

(defun get-names-of-external-definitions-for-module (module)
  (decache-all-indirectly-referenced-classes)
  (reclaim-eval-list (mark-all-classes-defined-in-module module))
  (sort-class-names
    (loop for needed-class in all-classes-for-cached-class-description-node-attributes
	  when (user-defined-class-p needed-class)
	    nconc (collect-unmarked-superiors-of-class needed-class)
	  finally (decache-all-indirectly-referenced-classes))))

(defvar all-formats-in-module nil)

(defun note-format-for-current-module (format)
  (gensym-pushnew format all-formats-in-module)
  format)

(defun decache-all-formats-for-current-module ()
  (reclaim-gensym-list all-formats-in-module)
  (setq all-formats-in-module nil))

(defun get-formats-for-current-module ()
  all-formats-in-module)

(defun get-attribute-for-attribute-name (item attribute)
  (multiple-value-bind (slot-description? virtual-attribute?)
      (user-attribute-slot-description-or-virtual-attribute
	item
	(if (consp attribute) (car attribute) attribute)
	(if (consp attribute) (cdr attribute) nil)
	'get)
    (or slot-description? virtual-attribute?)))

#+development
(progn

(defun clear-text-get-value (item attribute)
  (let ((array-initialization-evaluation-values-use-designations-p t)
	(item-color-pattern-returns-overrides-only-p t)
	(current-computation-flags current-computation-flags))
    (setf (role-serve-inactive-objects?) t)
    (setf (serve-loose-ends-p) t)
    (let* ((attribute (get-attribute-for-attribute-name item attribute))
	   (value (node-attribute-value item 'item-or-evaluation-value attribute))
	   (unit? (node-attribute-unit item 'item-or-evaluation-value attribute))
	   (type (node-attribute-type item 'item-or-evaluation-value attribute)))
      (values value
	      (node-attribute-value-is-untyped-primitive-p
		item 'item-or-evaluation-value attribute value type)
	      unit?))))

(defun clear-text-set-value (item attribute value &optional text-of-p unit?)
  (initialize-attribute-from-module-data
    item attribute value text-of-p unit?))

(defun clear-text-conclude-value (item attribute)
  (multiple-value-bind (value text-of-p)
      (clear-text-get-value item attribute)
    (clear-text-set-value item attribute value text-of-p)))

(defun collect-virtual-attribute-information-for-class-1 (class-name)
  (loop for va in (compute-vas-for-compute-class-description-node-attributes
		    (class-description class-name))
	collect (virtual-attribute-name va) using eval-cons))

(defun collect-exported-virtual-attribute-information-for-class (class-name)
  (loop with attr-list = (collect-virtual-attribute-information-for-class-1 class-name)
	with all-sup-attrs-list
	  = (loop with result = nil
		  for sup-class in (cdr (class-inheritance-path (class-description class-name)))
		  for sup-attr-list = (collect-virtual-attribute-information-for-class-1 sup-class)
		  do (setq result (union result sup-attr-list))
		  finally (return result))
	for attr in attr-list
	unless (memq attr all-sup-attrs-list)
	  collect attr using eval-cons))

(defun collect-non-exported-slot-information-for-class (class-name exported-p)
  (let ((class-description (class-description class-name)))
    (loop for slot-description in (slot-descriptions class-description)
	  for defining-class-name = (defining-class slot-description)
	  for defining-class-description
	      = (class-description defining-class-name)
	  for aliased-slot-name = (if (slot-name-needs-qualification-p
					slot-description
					class-description)
				      (unique-slot-name slot-description)
				      (alias-slot-name-if-necessary
					(pretty-slot-name slot-description)
					defining-class-name))
	  for reason? = (reason-to-exclude-slot-description-for-compute-class-description-node-attributes
			  slot-description)
	  when (and (case exported-p
		      (exported
		       (or (null reason?)
			   (eq reason? 'supplied-as-the-id)))
		      (not-exported
		       (and reason?
			    (not (or (eq reason? 'supplied-as-the-id)
				     (eq reason? 'not-savable)
				     (eq reason? 'dependant)
				     (memq aliased-slot-name '(relation-instances))))))
		      (other
		       (and reason?
			    (or (eq reason? 'dependant)
				(memq aliased-slot-name '(relation-instances))))))
		    (or (eq defining-class-name class-name)
			(not (eq reason?
				 (reason-to-exclude-slot-description-for-compute-class-description-node-attributes
				   (get-slot-description-of-class-description
				     (pretty-slot-name slot-description)
				     defining-class-description))))))
	    collect (eval-list aliased-slot-name reason?)
	      using eval-cons)))

(defun collect-non-exported-slot-information-for-classes (class-name &optional exclude-classes)
  (loop for class-name being the subclasses of class-name
	for exclude-p = (loop for exclude-class in exclude-classes
			      when (subclassp class-name exclude-class)
				return t
			      finally (return nil))
	for exported-slot-alist
	    = (unless exclude-p
		(loop for (name reason)
			  in (collect-non-exported-slot-information-for-class class-name 'exported)
		      collect name using eval-cons))
	for exported-virtual-slot-alist
	    = (unless exclude-p
		(collect-exported-virtual-attribute-information-for-class class-name))
	for not-exported-slot-alist
	    = (unless exclude-p
		(collect-non-exported-slot-information-for-class class-name 'not-exported))
	for other-slot-alist
	    = (unless exclude-p
		(collect-non-exported-slot-information-for-class class-name 'other))
	when (or exported-slot-alist not-exported-slot-alist other-slot-alist
		 exported-virtual-slot-alist)
	  collect (eval-cons
		    class-name
		    (nconc (eval-list
			     (eval-cons 'superclasses
					(cdr (class-inheritance-path (class-description class-name)))))
			   (when exported-slot-alist
			     (eval-list
			       (eval-cons 'exported exported-slot-alist)))
			   (when exported-virtual-slot-alist
			     (eval-list
			       (eval-cons 'exported-virtual exported-virtual-slot-alist)))
			   (when not-exported-slot-alist
			     (eval-list
			       (eval-cons 'not-exported not-exported-slot-alist)))
			   (when other-slot-alist
			     (eval-list
			       (eval-cons 'other other-slot-alist)))))
	    using eval-cons))

(defun collect-non-exported-slot-information ()
  (nconc (collect-non-exported-slot-information-for-classes 'system-item '(item))
	 ;;(collect-non-exported-slot-information-for-classes 'dependent-frame '(item system-item))
	 (list (list nil))
	 (collect-non-exported-slot-information-for-classes 'item)))

(defun report-non-exported-slots ()
  (loop with *print-length* = nil
	for (class . alist) in (collect-non-exported-slot-information)
	do (cond ((null class)
		  (format t "~%;============================~&"))
		 (t
		  (format t "~&(~(~S~)" class)
		  (loop for (type . info) in alist do
		    (format t "~&   (~(~S~)" type)
		    (loop for e in info do
		      (format t "~&      ~(~S~)" e))
		    (format t ")"))
		  (format t ")~%")))))

(defun collect-categories-for-clear-text ()
  (loop with categories = nil
	for class-name being the subclasses of 'item
	for class-description = (class-description class-name)
	do (loop for slot-description in (slot-descriptions class-description)
		 for category? = (text-or-the-text-of-slot-p slot-description)
		 when (and category?
			   (not (or (eq category? 'free)
				    (eq category? 'statement)))
			   (not (reason-to-exclude-slot-description-for-compute-class-description-node-attributes
				  slot-description))
			   (not (memq category? categories)))
		   do (push category? categories))
	finally (return (sort categories #'string<))))

)


;;; KB-XML reading code starts here (6166 lines, (4183 + 1983)). --binghe, 2016/6/25

(defvar reading-initial-plist-for-clear-text-kb nil)

(defun-allowing-unwind read-initial-plist-for-clear-text-kb ()
  (let ((reading-initial-plist-for-clear-text-kb t))
    (multiple-value-bind (object-and-fixups error-or-plist)
	(read-top-level-xml-element nil nil)
      (reclaim-xml-object-and-fixups object-and-fixups)
      (cond ((text-string-p error-or-plist)
	     (notify-user "Error reading ~A: ~A"
			  name-text-string-for-kb-being-read
			  error-or-plist)
	     nil)
	    ((null error-or-plist)
	     (notify-user "Error reading ~A: no module information"
			  name-text-string-for-kb-being-read)
	     nil)
	    (t
	     error-or-plist)))))

(defvar current-g2-rdf-module nil)

; document ::= xmldecl misc* dtd? misc* element+ misc
; xmldecl ::= '<?xml' ... '?>'
; dtd ::= '<!DOCTYPE' ... '>'
; chardata ::= nonmarkup*
; reference ::= '&' name ';' | '&#' [0-9]+ ';' | '&#x' [0-9a-fA-F]+ ';'
; cdsect ::= '<![CDATA[' ... ']]>'
; pi ::= '<?' ... '?>'
; comment ::= '<!--' ... '-->'
(defun read-clear-text-module (pathname auto-merge-case?)
  (let ((data (read-top-level-xml-element pathname nil)))
    (when data
      (when current-g2-rdf-module
	(read-clear-text-module-from-xml-object data auto-merge-case?))
      (reclaim-xml-object-and-fixups data)
      t)))

(defun read-clear-text-module-from-xml-object (data auto-merge-case?)
  (update-read-xml-progress)
  (check-and-report-xml-checksum-problems data)
  (build-kb-from-module-data data auto-merge-case?)
  t)

(defvar read-xml-line 0)
(defvar read-kb-next-character nil)

(defun-simple read-next-xml-char ()
  ;; see the structure-method transcode-character (utf-8-transcoder)
  (macrolet ((get-next-char ()
	       `(let ((char (cond (read-kb-next-character
				   (prog1 (code-char
					    (wide-character-code
					      read-kb-next-character))
				     (setq read-kb-next-character nil)))
				  #+development
				  ((not (boundp 'read-kb-buffer-index))
				   (read-char nil nil))
				  (t
				   (read-next-char-for-kb)))))
		  (when char
		    (character-to-wide-character char)))))
    (let ((char (get-next-char)))
      (setq char
	    (cond
	      ((null char)
	       char)
	      ((char<w char #u0020)	; C0 (Control) range
	       (cond
		 ((char=w char #.%return)
		  (let ((next-char (get-next-char)))
		    (unless (char=w next-char #.%linefeed)
		      (setq read-kb-next-character next-char)))
		  #.%line-separator)
		 ((char=w char #.%linefeed)
		  #.%line-separator)
		 (t
		  char)))
	      ((char<w char #u0080)	; GL range (usually ASCII)
	       char)
	      ;; Note that C1 controls codes (#x80..#x9f) are valid UTF-8 octets
	      ((char<w char #u0100)
	       (let* ((z (wide-character-code char))
		      (y 0)
		      (x 0)
		      (octet-count (get-octet-count-from-utf-8-lead-octet z)))
		 (declare (type fixnum octet-count z y x))
		 (cond
		   ((>f octet-count 3)
		    ;; either a bug, or attempt to use (full) UCS-4, not handled; squawk?!
		    nil)
		   (t
		    (when (>f octet-count 1)
		      (let ((c (get-next-char)))
			(cond
			  ((null c)
			   (setq y -1))
			  (t
			   (setq y (wide-character-code c))
			   (when (>f octet-count 2)
			     (setq c (get-next-char))
			     (cond
			       ((null c)
				(setq x -1))
			       (t
				(setq x (wide-character-code c)))))))))
		    (cond
		      ((or (<f y 0) (<f x 0))
		       nil)
		      (t
		       (code-wide-character
			 (transform-utf-8-to-ucs-4 z y x))))))))
	      (t
	       nil)))
      (if char
	  (when (char=w char #.%line-separator)
	    (incff read-xml-line)
	    (when (=f (modf read-xml-line 100) 0)
	      (update-read-xml-progress)))
	  (update-read-xml-progress))
      char)))

(defun update-read-xml-progress ()
  (when kb-file-progress
    (let ((suppress-updating-of-slot-value-representations? nil))
      (update-file-progress-display
	kb-file-progress
	read-xml-line))))

#+development
(defun read-xml-file (file)
  (with-open-file (*standard-input* file :direction :input)
    (progv '(read-kb-next-character read-kb-buffer-index) '(nil)
      (read-top-level-xml-element (gensym-parse-namestring file) nil))))

(defun-allowing-unwind read-top-level-xml-element (pathname? ignore-errors-p)
  (let ((binary-file (when pathname?
		       (gensym-make-pathname :type #w"bkb" :defaults pathname?)))
	name object-and-fixups error)
    (with-binary-data-stream (binary-file)
      (multiple-value-setq (name object-and-fixups error)
	  (let ((read-xml-line 1))
	    (read-xml-first-element nil))))
    (cond #+development
	  ((not (boundp 'read-kb-buffer-index))
	   (values object-and-fixups error))
	  ((text-string-p error)
	   (unless ignore-errors-p
	     #+development
	     (let ((gensym-string
		     (tformat-gensym-string "Error reading ~A: ~A"
					    name-text-string-for-kb-being-read
					    error)))
	       (warn "~A" gensym-string)
	       ;;(break)
	       (reclaim-gensym-string gensym-string))
	     (notify-user "Error reading ~A: ~A"
			  name-text-string-for-kb-being-read
			  error))
	   (reclaim-xml-object-and-fixups object-and-fixups)
	   nil)
	  (error
	   (values nil (unless ignore-errors-p error)))
	  (t
	   object-and-fixups))))

(defvar xml-nil (list 'xml-nil))

(defun reclaim-xml-attribute-list-and-contents (attribute-list contents skip-value)
  (loop for (name value) on attribute-list by 'cddr
	when (and (not (eq value skip-value))
		  (text-string-p value))
	  do (reclaim-text-string value))
  (reclaim-eval-list attribute-list)
  (cond ((null contents))
	((text-string-p contents)
	 (unless (eq contents skip-value)
	   (reclaim-text-string contents)))
	((consp contents)
	 (loop for (name value) on contents by 'cddr
	       when (consp name)
		 do (reclaim-eval-list name)
	       unless (eq value skip-value)
		 do (reclaim-xml-object-and-fixups value))
	 (reclaim-eval-list contents))))

(defparameter read-xml-context-string-width 48)

(defun twrite-read-xml-context-string (xml-read-context)
  (tformat "~%[line: ~D, context: " read-xml-line)
  (let ((position 17)) ; TODO: what's 17 here?
    (loop for element in xml-read-context
	  for stringp = (text-string-p element)
	  for string = (cond (stringp
			      element)
			     ((and element (symbolp element))
			      (symbol-name-text-string element)))
	  for size = (and string (lengthw string))
	  do (when string
	       (when (<f read-xml-context-string-width (+f position 1 size))
		 (tformat "~%")
		 (setq position 0))
	       (tformat (if stringp " ~S" " ~A") string)
	       (incff position (1+f size)))))
  (tformat "]"))

(defun read-xml-error-string (xml-read-context format &optional arg1 arg2 arg3 arg4 arg5)
  (let ((result (twith-output-to-text-string
		  (tformat format arg1 arg2 arg3 arg4 arg5)
		  (twrite-read-xml-context-string xml-read-context))))
    ;; #+development (break)
    result))

(defun-void reclaim-two-eval-conses (list)
  (reclaim-eval-cons (cdr list))
  (reclaim-eval-cons list))

; element ::= emptyelement | stag content etag
; emptyelement ::= '<' name (s attribute)* s? '/>'
; stag ::= '<' name (s attribute)* s? '>'
; etag ::= '</' name s? '>'
(defun read-xml-first-element (first-char)
  (loop for ch = (if first-char
		     (prog1 first-char
		       (setq first-char nil))
		     (read-next-xml-char))
	unless ch
	  do (return (values nil nil (read-xml-error-string nil "End of file")))
	when (char=w ch #.%\<)
	  do (multiple-value-bind (name kind object-and-fixups error-or-plist valuep)
		 (read-xml-content nil nil)
	       (declare (ignore kind))
	       (when (or object-and-fixups error-or-plist valuep)
		 (return (values name object-and-fixups error-or-plist valuep))))))

; content ::= (element | chardata | reference | cdsect | pi | comment)* 
(defun read-xml-content (name? xml-read-context)
  (macrolet ((read-xml-error (error &rest arguments)
	       `(return-from read-xml-content
		  (values nil nil nil (read-xml-error-string xml-read-context
							     ,error ,@arguments)))))
    (let ((ch (read-next-xml-char)))
      (cond ((null ch)
	     (read-xml-error "End of file"))
	    ((char=w ch #.%\?)
	     (loop for ch1 = nil then ch2
		   for ch2 = (or (read-next-xml-char)
				 (read-xml-error "End of file"))
		   until (and ch1
			      (char=w ch1 #.%\?)
			      (char=w ch2 #.%\>))))
	    ((char=w ch #.%\!)
	     (cond ((and (char=w #.%\- (setq ch (read-next-xml-char)))
			 (or (char=w #.%\- (read-next-xml-char))
			     (read-xml-error "Malformed XML comment")))
		    (loop for ch1 = nil then ch2
			  for ch2 = nil then ch3
			  for ch3 = (or (read-next-xml-char)
					(read-xml-error "End of file"))
			  until (and ch1 ch2
				     (char=w ch1 #.%\-)
				     (char=w ch2 #.%\-)
				     (char=w ch3 #.%\>))))
		   ((char=w ch #.%\[)
		    (when (loop for c in '(#.%\C #.%\D #.%\A #.%\T #.%\A #.%\[)
				for char = (or (read-next-xml-char)
					       (read-xml-error "End of file"))
				unless (char=w c char)
				  do (return t)
				finally (return nil))
		      (read-xml-error "Malformed XML CDATA"))
		    (values
		      nil
		      nil
		      (twith-output-to-text-string
			(loop with seen-first-char-p = nil
			      with chw = nil
			      for ch1 = nil then ch2
			      for ch2 = nil then ch3
			      for ch3 = (or (read-next-xml-char)
					    (read-xml-error "End of file"))
			      until (and ch1 ch2
					 (char=w ch1 #.%\])
					 (char=w ch2 #.%\])
					 (char=w ch3 #.%\>))
			      do (when ch1
				   (unless seen-first-char-p
				     (setq seen-first-char-p t)
				     (when (char=w ch1 #.%line-separator)
				       (setq ch1 nil))))
				 (when ch1
				   (when chw (twrite-char chw))
				   (setq chw ch1))
			      finally (when chw
					(unless (char=w chw #.%line-separator)
					  (twrite-char chw)))))))
		   (t
		    (loop for n = 1 then nextn
			  for ch = (or (read-next-xml-char)
				       (read-xml-error "End of file"))
			  for nextn = (cond ((char=w ch #.%\<)
					     (1+f n))
					    ((char=w ch #.%\>)
					     (1-f n))
					    (t n))
			  until (=f 0 nextn)))))
	    ((char=w ch #.%\/)
	     (multiple-value-bind (name next-char error-string)
		 (read-xml-name nil)
	       (cond (error-string
		      (read-xml-error error-string))
		     ((not (char=w next-char #.%\>))
		      (read-xml-error "Expecting >"))
		     ((null name?)
		      (read-xml-error "</~a> was seen at top level" name))
		     ((not (eq name name?))
		      (read-xml-error "Expecting </~a>, but found </~a>"
				      name? name)))
	       (values nil nil nil t)))
	    (t
	     (read-xml-content-1 ch xml-read-context))))))

(defun read-xml-content-1 (ch xml-read-context)
  (multiple-value-bind (error-string name attribute-list xml-read-context-1 empty-p)
      (read-xml-element-head ch xml-read-context)
    (if error-string
	(values nil nil nil error-string)
	(loop with text-p = t
	      with contents-rev = nil
	      do
	  (multiple-value-bind (content-name content-kind
				object-and-fixups error-or-plist valuep)
	      (let ((error-string nil))			 
		(cond (empty-p
		       (values nil nil nil t))
		      ((loop for ch = (read-next-xml-char) do		       
			 (case ch
			   ((nil) (setq ch (read-xml-error-string xml-read-context-1 "End of file")))
			   (#.%\& (setq ch (read-xml-reference xml-read-context-1)))
			   (#.%\< (return nil)))
			 (when (text-string-p ch)
			   (return (setq error-string ch)))
			 (when text-p
			   (eval-push ch contents-rev)))
		       (values nil nil nil error-string))
		      (t
		       (read-xml-content name xml-read-context-1))))
	    (when error-or-plist
	      (return-from read-xml-content-1
		(read-xml-object name attribute-list xml-read-context-1 contents-rev
				 text-p object-and-fixups error-or-plist)))
	    (multiple-value-setq (contents-rev text-p)
	      (read-xml-contents-2 contents-rev text-p content-name content-kind
				   object-and-fixups valuep)))))))

(defun read-xml-element-head (ch xml-read-context) ; the only caller is directly above
  (multiple-value-bind (name next-char error-string)
      (read-xml-name ch)
    (when error-string
      (return-from read-xml-element-head
	(read-xml-error-string xml-read-context error-string)))
    (let ((xml-read-context-1 (eval-cons name xml-read-context)))
      (multiple-value-bind (attribute-list empty-p)
	  (read-xml-attributes next-char xml-read-context-1)
	(if (text-string-p empty-p)
	    (progn
	      (reclaim-eval-cons xml-read-context-1)
	      empty-p)
	    (block read-xml-element-a
	      (when (eq name '|g2:Module|)
		(setq current-g2-rdf-module
		      (intern-text-string-no-reclaim
			(let ((string (getf attribute-list 'id)))
			  (unless (text-string-p string)
			    (return-from read-xml-element-a
			      (prog1 (read-xml-error-string
				      xml-read-context-1
				      "Bad module id")
				(reclaim-eval-cons xml-read-context-1))))
			  string))))
	      (let ((identification (or (getf attribute-list '|rdf:resource|)
					(getf attribute-list 'id))))
		(eval-push identification xml-read-context-1))
	      (values nil name attribute-list xml-read-context-1 empty-p)))))))

(defun read-xml-contents-1 (contents-rev text-p object-and-fixups error-or-plist)
  (unless (eq error-or-plist 't)
    (if text-p
	(loop for c in contents-rev
	      when (text-string-p c)
		do (reclaim-text-string c))
	(loop for (content-name content) on contents-rev by 'cddr
	      do (reclaim-xml-object-and-fixups content)))
    (reclaim-eval-list contents-rev)
    (return-from read-xml-contents-1
      (values object-and-fixups error-or-plist)))
  (unless text-p
    (return-from read-xml-contents-1
      (when contents-rev
	(values (nreverse contents-rev) nil t))))
  (let ((string nil))
    (when (and contents-rev
	       (null (cdr contents-rev))
	       (text-string-p (car contents-rev)))
      (setq string (eval-pop contents-rev)))
    (when contents-rev
      (when (and (wide-character-p (car contents-rev))
		 (char=w (car contents-rev)
			 #.%line-separator))
	(eval-pop contents-rev))
      (let ((contents (nreverse contents-rev)))
	(when (and (wide-character-p (car contents))
		   (char=w (car contents)
			   #.%line-separator))
	  (eval-pop contents))
	(setq string
	      (twith-output-to-text-string
		(loop for ch in contents
		      do (cond
			   ((wide-character-p ch)
			    (twrite-char ch))
			   (t
			    (twrite-string ch)
			    (reclaim-text-string ch))))))
	(reclaim-eval-list contents)))
    string))

(defun read-xml-contents-2 (contents-rev text-p content-name content-kind object-and-fixups valuep)
  (cond ((not text-p)
	 (when (or object-and-fixups valuep)
	   (eval-push (read-xml-make-attribute-name content-name content-kind)
		      contents-rev)
	   (eval-push (if (eq object-and-fixups xml-nil)
			  nil
			  object-and-fixups)
		      contents-rev)))
	((not (or content-name content-kind valuep
		  object-and-fixups)))
	((not (or content-name content-kind valuep
		  (not (text-string-p object-and-fixups))))
	 (eval-push object-and-fixups contents-rev))
	(t
	 (reclaim-eval-list contents-rev)
	 (setq text-p nil)
	 (setq contents-rev
	       (eval-list (if (eq object-and-fixups xml-nil)
			      nil
			      object-and-fixups)
			  (read-xml-make-attribute-name content-name content-kind)))))
  (values contents-rev text-p))

(defun read-xml-object (name attribute-list xml-read-context contents-rev text-p object-and-fixups
			     error-or-plist)
  (multiple-value-bind (contents error-or-plist non-text-p)
      (read-xml-contents-1 contents-rev text-p object-and-fixups error-or-plist)
    (when error-or-plist
      (reclaim-xml-attribute-list-and-contents attribute-list contents nil)
      (reclaim-two-eval-conses xml-read-context)
      (return-from read-xml-object (values nil nil nil error-or-plist)))
    (when (and (memq name '(|g2:Sequence| |g2:Structure| |rdf:Seq|))
	       (not (listp contents)))
      (return-from read-xml-object
	(values nil nil nil
		(prog1 (read-xml-error-string xml-read-context "Malformed ~A" name)
		  (reclaim-two-eval-conses xml-read-context)))))
    (when (and (eq name '|g2:c.MODULE-INFORMATION|)
	       reading-initial-plist-for-clear-text-kb)
      (return-from read-xml-object
	(values
	  nil nil nil
	  (prog1 (loop for pn in '(;;system-version kb-flags current-frame-serial-number
				   ;;timestamp base-time start-time gensym-time
				   ;;type-of-file
				   kb-name top-level-module required-modules)
		       for value
			   = (case pn
			       (kb-name current-g2-rdf-module)
			       (top-level-module
				(getf contents 'top-level-module))
			       (required-modules
				(let ((seq (get-xml-object (getf contents 'directly-required-modules))))
				  (when seq
				    (loop for m being each evaluation-sequence-element of seq
					  collect m using eval-cons)))))
		       nconc (when value (eval-list pn value)))
	    (reclaim-two-eval-conses xml-read-context)
	    (reclaim-xml-attribute-list-and-contents
	      attribute-list contents nil)))))
    (let* ((attribute-type (getf attribute-list '|g2:type|))
	   (attribute-unit (getf attribute-list '|g2:unit|))
	   (unit? (when attribute-unit (intern-text-string-no-reclaim attribute-unit)))
	   (attribute-value (getf attribute-list '|g2:value|))
	   (value? (cond ((text-string-p attribute-value)
			  (copy-text-string attribute-value))
			 ((text-string-p contents)
			  (copy-text-string contents))))
	   (type-string-from-name 
	     (case name
	       (|g2:Sequence| #w"Sequence")
	       (|g2:Structure| #w"Structure")
	       (|g2:RawValue| #w"RawValue")
	       (|g2:BinaryData| #w"BinaryData")
	       (|g2:Integer| #w"Integer")
	       (|g2:Long| #w"Long")
	       (|g2:Float| #w"Float")
	       (|g2:Text| #w"Text")
	       (|g2:Symbol| #w"Symbol")
	       (|g2:TruthValue| #w"TruthValue"))))
      (when type-string-from-name
	(multiple-value-bind (value error-string)
	    (read-xml-value type-string-from-name value? unit? attribute-list contents xml-read-context)
	  (when error-string
	    (reclaim-two-eval-conses xml-read-context)
	    (return-from read-xml-object (values nil nil nil error-string)))
	  (when value
	    (reclaim-two-eval-conses xml-read-context)
	    (return-from read-xml-object (values nil nil value nil t)))))
      (multiple-value-bind (symbol kind)
	  (symbol-from-rdf-symbol-name name)
	;; kind is class attribute user-attribute qualified-attribute structure-attribute
	(cond
	  ((eq kind 'class)
	   (when (text-string-p value?)
	     (reclaim-text-string value?))
	   (reclaim-two-eval-conses xml-read-context)
	   (values nil nil
		   (make-xml-object
		     nil
		     'item
		     (nconc (eval-list 'class symbol) attribute-list contents)
		     t)))
	  ((or (text-string-p value?)
	       attribute-type
	       (and (null value?) (null contents)))
	   (values symbol kind
		   (cond (attribute-type
			  (multiple-value-bind (value error-string)
			      (read-xml-value attribute-type value? unit? attribute-list contents xml-read-context)
			    (reclaim-two-eval-conses xml-read-context)
			    (when error-string
			      (return-from read-xml-object (values nil nil nil error-string)))
			    value))
			 (non-text-p
			  (reclaim-two-eval-conses xml-read-context)
			  (when (text-string-p value?)
			    (reclaim-text-string value?))
			  (reclaim-xml-attribute-list-and-contents attribute-list nil nil)
			  contents)
			 (t
			  (reclaim-two-eval-conses xml-read-context)
			  (when (text-string-p value?)
			    (reclaim-text-string value?))
			  (reclaim-xml-attribute-list-and-contents attribute-list nil nil)
			  (make-xml-object (or contents (copy-text-string #w""))
					   'text nil t)))
		   nil t))
	  ((not (or attribute-list (car contents) (cddr contents)))
	   (reclaim-two-eval-conses xml-read-context)
	   (values symbol kind (prog1 (cadr contents)
				 (reclaim-xml-attribute-list-and-contents
				   attribute-list contents (cadr contents)))
		   nil non-text-p))
	  (t
	   (reclaim-two-eval-conses xml-read-context)
	   (values symbol kind
		   (make-xml-object
		     nil
		     (if (eq name '|g2:Module|)
			 'module
			 'file)
		     (nconc attribute-list contents)
		     t))))))))

(defun read-xml-value (attribute-type value? unit? attribute-list contents xml-read-context)
  (let* ((value-len? (when value?
		       (lengthw value?)))
	 (type-len (wide-string-length attribute-type))
	 (result (case (progn
			 (unless (<f 2 type-len)
			   (return-from read-xml-value nil))
			 (charw attribute-type 0))
		   (#.%\R (if (and (string=w attribute-type #w"RawValue")
		              value?)
		          (let* ((read-kb-buffer (wide-string-to-string value?))
				         (read-kb-buffer-index 0)
						 (read-kb-buffer-length (length read-kb-buffer)))
				    (read-element-for-kb nil))
			      (return-from read-xml-value nil)))
		   (#.%\I (if (string=w attribute-type #w"Integer")
			      (when value?
				(read-fixnum-from-string value? 0 value-len?))
			      (return-from read-xml-value nil)))
		   (#.%\L (if (string=w attribute-type #w"Long")
			      (when value?
				(read-long-from-string value? 0 value-len?))
			      (return-from read-xml-value nil)))
		   (#.%\F (if (string=w attribute-type #w"Float")
			      (when value?
				(with-temporary-gensym-float-creation read-xml-value 
				  (allocate-managed-float
				    (coerce-to-gensym-float
				      (read-float-from-string value? 0 value-len?)))))
			      (return-from read-xml-value nil)))
		   (#.%\S (case (charw attribute-type 1)
			    (#.%\y (if (string=w attribute-type #w"Symbol")
				       (or (intern-text-string (or (prog1 value? (setq value? nil))
								   (copy-text-string #w"")))
					   :nil) ; see get-current-user-name-if-any-case-insensitive
				       (return-from read-xml-value nil)))
			    (#.%\e (if (string=w attribute-type #w"Sequence")
				       (prog1 (collect-xml-list contents 'sequence)
					 (setq contents nil))
				       (return-from read-xml-value nil)))
			    (#.%\t (if (string=w attribute-type #w"Structure")
				       (prog1 (collect-xml-list contents 'structure)
					 (setq contents nil))
				       (return-from read-xml-value nil)))
			    (t (return-from read-xml-value nil))))
		   (#.%\T (case (charw attribute-type 1)
			    (#.%\e (if (string=w attribute-type #w"Text")
				       (or (prog1 value? (setq value? nil))
					   (copy-text-string #w""))
				       (return-from read-xml-value nil)))
			    (#.%\r (if (string=w attribute-type #w"TruthValue")
				       (when value?
					 (make-evaluation-truth-value
					   (read-truth-value-from-string value? 0 value-len?)))
				       (return-from read-xml-value nil)))
			    (t
			     (return-from read-xml-value nil))))
		   (#.%\B (if (string=w attribute-type #w"BinaryData")
			      (multiple-value-bind (value error-string)
				  (make-binary-xml-object (nconc attribute-list contents) t)
				(when error-string
				  (return-from read-xml-value
				    (values nil (read-xml-error-string xml-read-context error-string))))
				(setq attribute-list nil)
				(setq contents nil)
				value)
			      (return-from read-xml-value nil)))
		   (t (return-from read-xml-value nil)))))
    (when value? (reclaim-text-string value?))
    (reclaim-xml-attribute-list-and-contents attribute-list contents nil)
    (unless result
      (return-from read-xml-value
	(values nil (read-xml-error-string xml-read-context "Missing g2:value attribute"))))
    (if unit?
	(make-xml-object result 'primitive-value nil nil nil unit?)
	result)))

(defun start-with-w (str1 str2 start len1 len2)
  (if (<f (-f len1 start) len2)
    nil
    (loop for index from start below (+f start len2)
          always (char=w (charw str1 index)
                         (charw str2 (-f index start))))))

(defun bind-symbol-to-rdf-symbol-name (rdf-symbol name)
  (let ((index 0)
        (len (lengthw name))
        (dot-seen nil)
        (type nil))
    (cond ((start-with-w name #w"g2:" 0 len 3)
           (incff index 3))
          ((start-with-w name #w"g2m:" 0 len 4)
           (incff index 4)))
    (cond ((start-with-w name #w"c." index len 2)
           (setq type 'class)
           (incff index 2))
          ((start-with-w name #w"a." index len 2)
           (setq type 'attribute)
           (incff index 2))
          ((start-with-w name #w"ua." index len 3)
           (setq type 'user-attribute)
           (incff index 3))
          ((start-with-w name #w"uq." index len 3)
           (setq type 'qualified-attribute)
           (incff index 3))
          ((start-with-w name #w"sa." index len 3)
           (setq type 'structure-attribute)
           (incff index 3)))
    (let* ((first-part
             (intern-text-string
               (twith-output-to-text-string
                 (loop while (and (<f index len) (not dot-seen))
                       for ch = (charw name index)
                       for qmp = (and (char=w ch #.%\_)
                                      (<f (+f index 2) len)
                                      (char=w (charw name (+f index 1)) #.%\q)
                                      (char=w (charw name (+f index 2)) #.%\m))
                       do (cond ((and (eq type 'qualified-attribute)
                                      (char=w ch #.%\.))
                                 (setq dot-seen t)
                                 (incff index))
                                (t
                                  (twrite-char (if qmp #.%\? ch))
                                  (incff index (if qmp 3 1))))))))
           (second-part
             (when (and (eq type 'qualified-attribute) dot-seen)
               (intern-text-string
                 (twith-output-to-text-string
                   (loop while (<f index len)
                         for ch = (charw name index)
                         for qmp = (and (char=w ch #.%\_)
                                        (<f (+f index 2) len)
                                        (char=w (charw name (+f index 1)) #.%\q)
                                        (char=w (charw name (+f index 2)) #.%\m))
                         do (twrite-char (if qmp #.%\? ch))
                            (incff index (if qmp 3 1))))))))
      (mutate-global-property rdf-symbol
                              (eval-cons
                                (if (and (eq type 'qualified-attribute) dot-seen)
                                  (eval-cons second-part first-part)
                                  first-part) type)
                              'symbol-from-rdf-symbol-name))))
 


(defun symbol-from-rdf-symbol-name (symbol)
  (let* ((s+p (get symbol 'symbol-from-rdf-symbol-name))
	 (s (car s+p)))
    (if (consp s)
	(values (eval-cons (car s) (cdr s)) (cdr s+p))
	(values s (cdr s+p)))))


; name ::= (letter | '_' | ':') namechar*
; namechar ::= letter | digit | '.' | '-' | '_' | ':' | combiningchar | extender

(defun read-xml-name (first-char)
  (let ((ch nil)
        (ch-list nil))
    (values
      (interning-text-character-sequence
        (next-character-for-intern (or (let ((next-char (or first-char
                                                            (read-next-xml-char))))
                                         (setq ch-list (gensym-cons next-char ch-list))
                                         next-char)
                                       (return-from read-xml-name
                                                    (values nil nil "End of file"))))
      (loop do (unless (setq ch (read-next-xml-char))
                 (return-from read-xml-name
                              (values nil nil "End of file")))
            while (or (alpha-char-pw ch)
                      (digit-char-pw ch)
                      (complex-char-pw ch)
                      (char=w ch #.%\.)
                      (char=w ch #.%\-)
                      (char=w ch #.%\_)
                      (char=w ch #.%\:))
            do
            (setq ch-list (gensym-cons ch ch-list))
            (next-character-for-intern ch))
      (let ((symbol (result-of-intern))
            (name (twith-output-to-text-string
                    (loop for ch in (nreverse ch-list)
                          do (twrite-char ch)))))
        (bind-symbol-to-rdf-symbol-name symbol name)
        (reclaim-text-string name)
        (reclaim-gensym-list ch-list)
        symbol))
      ch)))

(defun-simple xml-whitespace-p (ch)
  (or (char=w ch #.%space)
      (char=w ch #.%tab)
      (char=w ch #.%line-separator)
      (char=w ch #.%linefeed)
      (char=w ch #.%return)))

(defun read-xml-char-skipping-whitespace (&optional next-char)
  (loop for ch = (if next-char
		     (prog1 next-char
		       (setq next-char nil))
		     (read-next-xml-char))
	unless (and ch (xml-whitespace-p ch))
	  do (return ch)))

(defun complex-char-pw (ch)
  (let* ((code (char-codew ch)))
    (and (>f code #xFF) (not (xml-whitespace-p ch)))))

; attribute ::= name eq attvalue
; attvalue ::= quote (nonmarkup | reference)* quote
(defun read-xml-attributes (next-char xml-read-context)
  (macrolet ((read-xml-error (error &rest arguments)
	       `(progn
		  (reclaim-eval-list result)
		  (return-from read-xml-attributes
		    (values nil (read-xml-error-string xml-read-context ,error ,@arguments))))))
    (let ((emptyp nil))
      (values
	(loop for ch = (prog1 (read-xml-char-skipping-whitespace next-char)
			 (setq next-char nil))
	      for attvalue
		  = (cond ((char=w ch #.%\/)
			   (setq emptyp t)
			   (unless (char=w #.%\> (read-next-xml-char))
			     (read-xml-error "Expected >"))
			   t)
			  ((char=w ch #.%\>)
			   t)
			  ((or (alpha-char-pw ch)
			       (char=w ch #.%\_)
			       (char=w ch #.%\:))
			   (multiple-value-bind (name next-char-after-name error-string)
			       (read-xml-name ch)
			     (when error-string
			       (read-xml-error error-string))
			     (unless (char=w #.%\= (read-xml-char-skipping-whitespace
						     next-char-after-name))
			       (read-xml-error "Expected ="))
			     (multiple-value-bind (attvalue error)
				 (read-xml-attvalue (read-xml-char-skipping-whitespace)
						    xml-read-context)
			       (when error
				 (return-from read-xml-attributes error))
			       (eval-list name attvalue))))
			  (t
			   (read-xml-error "Expected an attribute, /, or >")))
	      while (consp attvalue)
	      nconc attvalue into result
	      finally (return result))
	emptyp))))

(defun read-xml-reference (xml-read-context)
  (multiple-value-bind (name next-char error-string)
      (read-xml-name nil)
    (cond (error-string
	   (read-xml-error-string xml-read-context error-string))
	  ((char=w #.%\; next-char)
	   (case name
	     (|amp| #.%\&)
	     (|lt| #.%\<)
	     (|gt| #.%\>)
	     (|quot| #.%\")
	     (t (read-xml-error-string xml-read-context
				       "Unrecognized character reference \"&~a;\"" name))))
	  (t
	   (read-xml-error-string xml-read-context "Expected \";\"")))))

(defun read-xml-attvalue (quote xml-read-context)
  (unless (or (char=w quote #.%\")
	      (char=w quote #.%\'))
    (return-from read-xml-attvalue
      (values nil "Expected \" or '")))
  (twith-output-to-text-string
    (loop for ch = (read-next-xml-char)
	  until (char=w ch quote)
	  do (twrite-char
	       (if (char=w #.%\& ch)
		   (let ((result (read-xml-reference xml-read-context)))
		     (if (text-string-p result) ;error message
			 (return-from read-xml-attvalue
			   (values nil result))
			 result))
		   ch)))))

(defun twrite-text-string (string)
  (loop for i from 0 below (lengthw string)
	do (twrite-char (charw string i))))

(defun read-xml-make-attribute-name (name kind)
  (if (and (or (eq kind 'user-attribute)
	       (eq kind 'qualified-attribute))
	   (atom name))
      (eval-list name)
      name))

(defvar most-recent-xml-checksum-differences nil)

(defun check-and-report-xml-checksum-problems (data)
  (let ((difference (check-xml-object-checksums data)))
    (when difference
      (if (and (boundp 'name-text-string-for-kb-being-read)
	       name-text-string-for-kb-being-read)
	  (notify-user "Checksum Error in ~A: ~(~L,A~)"
		       name-text-string-for-kb-being-read
		       difference)
	  (notify-user "Checksum Error: ~(~L,A~)"
		       difference)))
    (when (consp most-recent-xml-checksum-differences)
      (reclaim-gensym-list most-recent-xml-checksum-differences))
    (setq most-recent-xml-checksum-differences difference)))

(defvar current-module-data nil)
(defvar initialize-items-count nil)
(defvar delayed-item-array-initializations nil)
(defvar delay-item-array-initializations-p nil)
(defvar initializing-clear-text-p nil)
(defvar externaldefinitions-fixups nil)
(defvar systemtables-fixups nil)
(defvar systemtables-are-initialized-p nil)
(defvar kb-window-for-initializing-definitions nil)
(defvar clear-text-item-layering-info nil)

(defun build-kb-from-module-data (data auto-merge-case?)
  (let ((current-module-data data)
	(current-computation-flags current-computation-flags)
	(ignore-kb-state-changes-p t)
	(suppress-updating-of-slot-value-representations? nil)
	(reading-kb-p nil)
	(loading-kb-p nil)
	(initializing-clear-text-p t)
	(called-within-clear-text-loading t)
	(suppress-consistency-analysis-warnings-notes? t)
	(do-not-update-frame-authors? t)
	(changing-validity-interval-invalidates-current-value-p nil)
	(change-the-text-of-attributes-without-category-evaluator-interfaces-p t)
	(keep-edit-workspace-hidden-no-matter-what? t)
	(allow-name-box-creation nil)
	(disable-tracing-and-breakpoints-warning t)
	(delayed-item-array-initializations nil)
	(delay-item-array-initializations-p t)
	(disable-subworkspace-connection-posts t)
	(disable-update-button t)
	(total-items-in-file nil)
	(initialize-items-count 0)
	(externaldefinitions-fixups
	  (get-xml-fixups (get-xml-fixups data '|Module| nil) '|externaldefinitions| nil))
	(systemtables-fixups
	  (get-xml-fixups (get-xml-fixups data '|Module| nil) '|systemtables| nil))
	(systemtables-are-initialized-p nil)
	(kb-window-for-initializing-definitions nil)
	(clear-text-item-layering-info nil)
	(do-not-note-permanent-changes-p t))
    (declare (special keep-edit-workspace-hidden-no-matter-what?))
    (setf (role-serve-inactive-objects?) t)
    (setf (serve-only-permanent-items-p) t)
    (setf (serve-loose-ends-p) t)
    (setq current-g2-rdf-module
	  (module-name-symbol-for-xml-object data))
    (setq kb-window-for-initializing-definitions
	  (make-permanent-item 'kb-workspace))
    ;; Step A.
    (initialize-all-units-of-measure-declarations-from-module-data data)
    ;; Step B.
    (find-and-create-all-definitions-in-module-data data)
    ;; Step C.
    (create-all-system-frames-from-module-data)

    ;; Step D.
    ;; Create all instances (except connections), if there's any reference in attributes,
    ;; it will be ignored for now.
    (create-all-instances-from-module-data data nil)	; resolve-references-p = nil

    ;; Step E (depends on D).
    ;; Re-create all instances (except connections), additionally resolving all references.
    ;; However, if there's any connection in these references, they will not be resolved, never.
    (create-all-instances-from-module-data data t)	; resolve-references-p = t

    ;; Step F
    (initialize-all-relations-from-module-data data)
    (update-initialize-xml-progress)

    ;; Step G (depends on E)
    (initialize-all-instances-from-module-data data) ; except `relationships'

    ;; Step H
    (do-delayed-array-initializations)

    ;; Step I
    (create-and-initialize-all-connections-from-module-data data t)	; do-loose-ends-p = t

    ;; Step J (depends on I?)
    (create-and-initialize-all-connections-from-module-data data nil)	; do-loose-ends-p = nil

    ;; Step K (depends on E, I, J)
    ;; Call again `create-all-instances-from-module-data' to resolve references of
    ;; all connections (appeared in `relationships').
    (create-all-instances-from-module-data data t)	; resolve-references-p = t
    (initialize-all-relationships-from-module-data data)

    (update-initialize-xml-progress t)
    (fix-clear-text-item-layering-from-module-data data)
    (re-initialize-all-generic-simulation-formulas-from-modula-data data)
    (when (or system-has-paused system-is-running)
      (setq disable-update-button nil)
      (update-all-buttons-from-module-data data))
    (setq allow-name-box-creation t)
    (deal-with-class-name-conflicts auto-merge-case? t)
    (delete-blocks-and-connections-to-be-deleted-after-reading)
    (if (subblocks kb-window-for-initializing-definitions)
	(when current-g2-rdf-module
	  (initialize-attribute-from-module-data
	    kb-window-for-initializing-definitions
	    'module-assignment
	    current-g2-rdf-module))
	(delete-frame kb-window-for-initializing-definitions))
    (fix-all-workspace-sizes-from-module-data data)
    (unless (or system-has-paused system-is-running)
      (atomic-exchange system-has-paused t)
      (system-reset))
    (set-up-panes-from-module-data data)
    nil))

(defun set-up-panes-from-module-data (data)
  (setq plist-from-end-element?
	(nconc (slot-value-list
		 'detail-pane-description
		 (let ((pane-fixups (get-xml-fixups (get-xml-fixups data '|Module| nil) '|panes| nil)))
		   (when pane-fixups
		     (loop for pane being each evaluation-sequence-element of (get-xml-object pane-fixups)
			   when (evaluation-structure-slot pane 'workspace)
			     collect (slot-value-list (evaluation-structure-slot pane 'workspace)
						      (evaluation-structure-slot pane 'x-in-workspace)
						      (evaluation-structure-slot pane 'y-in-workspace)
						      (evaluation-structure-slot pane 'x-magnification)
						      (evaluation-structure-slot pane 'y-magnification))
			       using slot-value-cons))))
	       plist-from-end-element?)))

(defun update-initialize-xml-progress (&optional force-update-p)
  (when (and kb-file-progress
	     systemtables-are-initialized-p
	     (or force-update-p
		 (=f 0 (modf initialize-items-count 10))))
    (let ((suppress-updating-of-slot-value-representations? nil))
      (update-file-progress-display
	kb-file-progress
	initialize-items-count
	force-update-p))))

(defvar definitions-in-module nil)
(defvar definitions-in-module-to-go nil)
(defvar in-external-definitions-for-module-p nil)

(defun-simple record-definitions-in-module-data (object-and-fixups)
  (with-xml-object (object-and-fixups object)
    nil
    (let ((class nil)
	  (class-name nil)
	  (direct-superior-classes nil))
      (do-contents (name value)
	(case name
	  (class
	   (setq class value))
	  (class-name
	   (setq class-name value))
	  (direct-superior-classes
	   (setq direct-superior-classes value)))
	(when (or (not (eq object-and-fixups externaldefinitions-fixups))
		  in-external-definitions-for-module-p)
	  (record-definitions-in-module-data value)))
      (when (and class class-name direct-superior-classes
		 (not (assq class-name definitions-in-module)))
	(eval-push (eval-list class-name nil object-and-fixups
			      in-external-definitions-for-module-p
			      class)
		   definitions-in-module)))))

(defun create-all-definitions-in-module ()
  (loop with definitions-in-module-to-go
	  = (eval-cons (eval-list nil nil nil nil nil)
		       (copy-list-using-eval-conses definitions-in-module))
	while (cdr definitions-in-module-to-go)
	do (create-all-definitions-in-module-1
	     (cadr definitions-in-module-to-go))
	finally (reclaim-eval-list (eval-pop definitions-in-module-to-go)))
  (loop while definitions-in-module
	do (reclaim-eval-list (eval-pop definitions-in-module))))

(defun create-all-definitions-in-module-1 (name+nname+object-and-fixups+ghostp+class)
  (when (memq name+nname+object-and-fixups+ghostp+class definitions-in-module-to-go)
    (setq definitions-in-module-to-go
	  (delete-eval-element name+nname+object-and-fixups+ghostp+class
			       definitions-in-module-to-go))
    (let* ((object-and-fixups (third name+nname+object-and-fixups+ghostp+class))
	   (reading-ghost-definitions-p (fourth name+nname+object-and-fixups+ghostp+class))
	   (class (fifth name+nname+object-and-fixups+ghostp+class))
	   (direct-superior-classes
	     (get-xml-object (get-xml-fixups object-and-fixups 'direct-superior-classes nil)))
	   (class-specific-attributes
	     (get-xml-object (get-xml-fixups object-and-fixups 'class-specific-attributes nil))))
      (create-all-definitions-in-module-1 class)
      (when direct-superior-classes
	(loop for class being each evaluation-sequence-element of direct-superior-classes
	      for definition = (assq class (cdr definitions-in-module))
	      when definition 
		do (create-all-definitions-in-module-1 definition)))
      (when class-specific-attributes
	(loop for attr-spec being each evaluation-sequence-element of class-specific-attributes
	      for class = (and (evaluation-structure-p attr-spec)
			       (evaluation-structure-slot attr-spec 'attribute-initial-item-class))
	      for definition = (and class (assq class (cdr definitions-in-module)))
	      when definition 
		do (create-all-definitions-in-module-1 definition)))
      (create-all-instances-from-module-data object-and-fixups nil)
      (create-all-instances-from-module-data object-and-fixups t)
      (initialize-definition-from-module-data object-and-fixups))))

(defun find-and-create-all-definitions-in-module-data (data)
  (let ((definitions-in-module nil))
    (let ((in-external-definitions-for-module-p t))
      (record-definitions-in-module-data externaldefinitions-fixups))
    (record-definitions-in-module-data data)
    (create-all-definitions-in-module)))

(defun get-uuid-from-module-data (id?)
  (when id?
    (multiple-value-bind (uuid? problem-report?)
	(let ((current-edit-state nil))
	  (compile-uuid-for-slot id? nil 'uuid))
      (if problem-report?
	  (progn (reclaim-text-string problem-report?) nil)
	  uuid?))))

(defun get-instance-from-uuid-representation (id)
  (let ((uuid? (get-uuid-from-module-data id)))
    (prog1 (when uuid?
	     (get-item-or-item-list-for-uuid uuid?))
      (reclaim-if-text-string uuid?))))

(defun get-instance-from-xml-locator (locator)
  (when (text-string-p locator)
    (let* ((len (lengthw locator))
	   (pos (loop for i from 0 below len
		      when (char=w (charw locator i) #.%\#)
			return i)))
      (when pos
	(let ((id (text-string-substring locator (1+ pos) len)))
	  (prog1 (get-instance-from-uuid-representation id)
	    (reclaim-text-string id)))))))

(defun get-binary-file-index-from-xml-locator (locator)
  (when (text-string-p locator)
    (let* ((len (lengthw locator))
	   (pos (loop for i from 0 below len
		      when (char=w (charw locator i) #.%\#)
			return i)))
      (when pos
	(read-fixnum-from-string locator (1+f pos))))))

(defvar may-create-simulation-subtable-from-module-data-p nil)

(defun create-instance-from-module-data (object-and-fixups resolve-references-p)
  (with-xml-object (object-and-fixups object)
    object
    (let ((class (get-xml-fixups object-and-fixups 'class nil))
	  (resource (get-xml-fixups object-and-fixups '|rdf:resource| nil)))
      (unless object
	(cond
	  (resource
	   (when resolve-references-p
	     (setq object
		   (get-instance-from-xml-locator resource))))
	  (class
	   (unless resolve-references-p
	     (let ((class-description (class-description class)))
	       (when (and class-description
			  (not (class-description-of-class-p class-description 'connection)))
		 (let ((id (get-xml-fixups object-and-fixups 'id nil)))
		   (when id
		     (setq uuid-for-next-frame? (get-uuid-from-module-data id))
		     (setq class-description-for-next-frame? class-description)))
		 (cond
		   ((class-description-of-class-p class-description 'simulation-subtable)
		    (when may-create-simulation-subtable-from-module-data-p
		      (setq object (make-frame-of-class-description class-description))
		      (put-simulation-details
			may-create-simulation-subtable-from-module-data-p
			object
			nil)
		      (set-permanent-and-propagate object nil)))
		   ((class-description-of-class-p class-description 'system-frame)
		    (setq object (make-system-frame class)))
		   (t
		    (setq object (make-permanent-item-of-class-description class-description))
		    (when (frame-of-class-p object 'block)
		      (remove-all-stubs-from-block object))
		    (when (frame-of-class-p object 'text-box)
		      (change-slot-value object 'text-cell-plist-for-text-box nil))))
		 (when (and object
			    (not (class-description-of-class-p class-description 'system-frame)))
		   (let ((names (get-xml-object (get-xml-fixups object-and-fixups 'names nil))))
		     (when names
		       (initialize-attribute-from-module-data object 'names names)))))
	       (when class-description
		 (unless total-items-in-file (setq total-items-in-file 0))
		 (incff total-items-in-file))))))
	(when object
	  (set-object object)))
      object)))

(defun remove-all-stubs-from-block (block)
  (loop with connections-to-delete
	  = #-connections-v2
	    (loop for connection? in (connections block)
		  unless (symbolp connection?)
		    collect connection? using gensym-cons)
	    #+connections-v2
	    (loop for connection? being each connection of block
		  collect connection? using gensym-cons)
	with reference-serial-number
	  = (copy-frame-serial-number (current-frame-serial-number))
	for connection in connections-to-delete
	when (connection-has-not-been-reprocessed-p
	       connection reference-serial-number)
	  do (delete-connection connection)
	finally (reclaim-frame-serial-number reference-serial-number)
		(reclaim-gensym-list connections-to-delete)))

(defun create-and-initialize-all-connections-from-module-data (object-and-fixups do-loose-ends-p)
  (with-xml-object (object-and-fixups object)
    object
    (progn
      (unless object
	(let ((class (get-xml-fixups object-and-fixups 'class nil)))
	  (when class
	    (let ((class-description (class-description class)))
	      (when (and class-description
			 (class-description-of-class-p class-description 'connection))
		(setq object (create-connection-from-module-data
			       class-description object-and-fixups do-loose-ends-p))))))
	(when object
	  (set-object object)
	  (do-contents (name value)
	    (unless (memq name '(class id |rdf:resource|
				 connection-input connection-output
				 connection-style connection-vertices connection-is-directed
				 following-item-in-workspace-layering
				 ;; GENSYMCID-1804: losing palette behavior
				 ;; Exclude additionally `relationships' here.
				 relationships))
	      (let ((actual-value (lookup-xml-object value)))
		(unless (and value (null actual-value))
		  (initialize-attribute-from-module-data
		    object name actual-value (xml-object-text-of-p value) (xml-object-unit value))))))
	  (unless (get-xml-fixups object-and-fixups '|rdf:resource| nil)
	    (incff initialize-items-count)
	    (update-initialize-xml-progress))))
      (do-contents (name value)
	(create-and-initialize-all-connections-from-module-data value do-loose-ends-p))
      object)))

(defun create-connection-from-module-data (class-description object-and-fixups do-loose-ends-p)
  (let* ((disable-stack-error t)
	 (connection-input (get-xml-object (get-xml-fixups object-and-fixups 'connection-input nil)))
	 (connection-output (get-xml-object (get-xml-fixups object-and-fixups 'connection-output nil)))
	 (connection-style (get-xml-object (get-xml-fixups object-and-fixups 'connection-style nil)))
	 (connection-vertices (get-xml-object (get-xml-fixups object-and-fixups 'connection-vertices nil)))
	 (connection-is-directed (get-xml-object (get-xml-fixups object-and-fixups 'connection-is-directed nil)))
	 (permit-transfer-of-permanent-items-p t)
	 (end-1-item  (when connection-input
			(evaluation-structure-slot connection-input 'item)))
	 (side-1?     (when connection-input
			(evaluation-structure-slot connection-input 'side)))
	 (position-1? (when connection-input
			(evaluation-structure-slot connection-input 'position)))
	 (portname-1? (when connection-input
			(evaluation-structure-slot connection-input 'port-name)))
	 (make-new-stub-1? t)
	 (end-2-item? (when connection-output
			(evaluation-structure-slot connection-output 'item)))
	 (side-2?     (when connection-output
			(evaluation-structure-slot connection-output 'side)))
	 (position-2? (when connection-output
			(evaluation-structure-slot connection-output 'position)))
	 (portname-2? (when connection-output
			(evaluation-structure-slot connection-output 'port-name)))
	 (make-new-stub-2? t)
	 (id (get-xml-fixups object-and-fixups 'id nil))
	 (uuid-for-next-frame? (when id (get-uuid-from-module-data id)))
	 (class-description-for-next-frame? class-description)
	 (connection
	   (when (eq do-loose-ends-p
		     (not (null (or (null end-1-item) (of-class-p end-1-item 'loose-end)
				    (null end-2-item?) (of-class-p end-2-item? 'loose-end)))))
	     (execute-create-connection-stack-instruction-internal
	       (class-name-of-class-description class-description) class-description
	       end-1-item make-new-stub-1? side-1? position-1? portname-1?
	       end-2-item? make-new-stub-2? side-2? position-2? portname-2?
	       connection-style
	       (if (and (evaluation-truth-value-p connection-is-directed)
			(evaluation-boolean-is-true-p connection-is-directed))
		   'output
		   nil)
	       connection-vertices
	       nil))))
    (cond ((null connection)
	   nil)
	  ((text-string-p connection)
	   (notify-user connection)
	   nil)
	  (t	  
	   ;;(get-or-make-connection-frame-and-activate-if-appropriate connection)
	   (set-permanent-and-propagate connection nil)
	   connection))))

(defmacro setf-if-not-present (location new-value)
  (let ((old-value-var (make-symbol "OLD-VALUE"))
	(new-value-var (make-symbol "NEW-VALUE")))
    `(let ((,old-value-var ,location)
	   (,new-value-var ,new-value))
       (if ,old-value-var
	   (reclaim-if-evaluation-value ,new-value-var)
	   (setf ,location ,new-value-var))
       ,new-value-var)))

(defun create-all-system-frames-from-module-data ()
  (create-all-instances-from-module-data systemtables-fixups nil)
  (create-all-instances-from-module-data systemtables-fixups t)
  (with-xml-object (systemtables-fixups object type)
    nil 
    (when (evaluation-sequence-p object)
      (do-contents (name value)
	(when (and (null (get-xml-object value))
		   (eq (get-xml-fixups value 'class nil) 'item-reference-parameters))
	  (let ((substituted-instance
		 (do-contents (name value)
		   (let ((actual-value (get-xml-object value)))
		     (when (of-class-p actual-value 'miscellaneous-parameters)
		       (return actual-value))))))
	    (with-xml-object (value)
	      nil
	      (set-object substituted-instance))
	    (setf (evaluation-sequence-aref object name) substituted-instance))))))
  (initialize-all-instances-from-module-data systemtables-fixups)
  (let ((sequence (get-xml-object systemtables-fixups)))
    (when sequence
      (loop for system-frame being each evaluation-sequence-element of sequence
	    when (and (framep system-frame)
		      (not (memq system-frame system-tables-read-for-this-module)))
	      do (slot-value-push system-frame system-tables-read-for-this-module))
      (set-up-modules-and-system-tables-a-list-after-reading)
      (set-kb-has-been-loaded-from-clear-text-with-differences
	current-g2-rdf-module most-recent-xml-checksum-differences)))
  (setq systemtables-are-initialized-p t))

(defun create-all-instances-from-module-data (object-and-fixups resolve-references-p)
  (with-xml-object (object-and-fixups object type)
    (copy-if-evaluation-value object)
    (cond ((eq type 'binary))
	  ((consp object)
	   (cond ((evaluation-sequence-p object)
		  (do-contents (name value)
		    (setf-if-not-present (evaluation-sequence-aref object name)
					 (create-all-instances-from-module-data
					   value resolve-references-p)))
		  (copy-evaluation-sequence object))
		 ((evaluation-structure-p object)
		  (do-contents (name value)
		    (setf-if-not-present (evaluation-structure-slot object name)
					 (create-all-instances-from-module-data
					   value resolve-references-p)))
		  (copy-evaluation-structure object))))
	  (t
	   (let* ((object (create-instance-from-module-data object-and-fixups resolve-references-p))
		  (v-p (of-class-p object 'variable)))
	     (do-contents (name value)
	       (let* ((may-create-simulation-subtable-from-module-data-p
			(when (and v-p (eq name 'simulation-details))
			  object))
		      (actual-value (create-all-instances-from-module-data
				      value resolve-references-p)))
		 (when (evaluation-value-p actual-value)
		   (reclaim-evaluation-value actual-value))))
	     object)))))

(defun initialize-definition-from-module-data (object-and-fixups)
  (with-xml-object (object-and-fixups object)
    nil
    (when (framep object)
      (without-consistency-analysis (object)
	(unless reading-ghost-definitions-p
	  (let ((value (allocate-evaluation-structure-inline
			 'x 0 'y 0
			 'superior kb-window-for-initializing-definitions)))
	    (initialize-attribute-from-module-data object 'position-in-workspace value nil)
	    (reclaim-evaluation-value value)))
	(do-contents (name value)
	  (let ((actual-value (lookup-xml-object value)))
	    (unless (memq name '(class-name
				 class id |rdf:resource|
				 parent-of-subworkspace
				 edges-of-workspace
				 position-in-workspace
				 icon-variables icon-reflection icon-heading
				 size-in-workspace minimum-size-in-workspace
				 following-item-in-workspace-layering
				 name-box relationships))
	      (initialize-attribute-from-module-data
		object name actual-value (xml-object-text-of-p value) (xml-object-unit value)))))
	(initialize-attribute-from-module-data
	  object 'class-name (get-xml-object (get-xml-fixups object-and-fixups 'class-name nil)))))))

(defparameter relation-attributes
  '(first-class second-class
    relation-name inverse-of-relation
    type-of-relation relation-is-symmetric relation-is-permanent))

(defun initialize-all-relations-from-module-data (object-and-fixups)
  (with-xml-object (object-and-fixups object)
    nil
    (progn
      (when (of-class-p object 'relation)
	(loop for name in relation-attributes
	      for value = (get-xml-fixups object-and-fixups name nil)
	      for actual-value = (initialize-all-instances-from-module-data value)
	      when actual-value
		do (initialize-attribute-from-module-data
		     object name actual-value (xml-object-text-of-p value) (xml-object-unit value))))
      (do-contents (name value)
	(initialize-all-relations-from-module-data value)))))

(defparameter units-of-measure-declaration-attributes
  '(text))

(defun initialize-all-units-of-measure-declarations-from-module-data (object-and-fixups)
  (with-xml-object (object-and-fixups object)
    nil
    (progn
      (when (eq (get-xml-fixups object-and-fixups 'class nil) 'units-of-measure-declaration)
	(let ((object (create-instance-from-module-data object-and-fixups nil)))
	  (loop for name in units-of-measure-declaration-attributes
		for value = (get-xml-fixups object-and-fixups name nil)
		for actual-value = (initialize-all-instances-from-module-data value)
		when actual-value
		  do (initialize-attribute-from-module-data
		       object name actual-value (xml-object-text-of-p value) (xml-object-unit value)))))
      (do-contents (name value)
	(initialize-all-units-of-measure-declarations-from-module-data value)))))

;This is needed due to a bug: if the formula is created first, and the things it refers to
;are created second, the formula does not always run when it should.
;This was discovered with tests/simulat2.kb when saved in clear text in layer order, then loaded and started.
(defun re-initialize-all-generic-simulation-formulas-from-modula-data (object-and-fixups)
  (with-xml-object (object-and-fixups object)
    nil
    (progn
      (when (of-class-p object 'generic-simulation-formula)
	(loop for name in '(text)
	      for value = (get-xml-fixups object-and-fixups name nil)
	      for actual-value = (get-xml-object value)
	      when actual-value
		do (initialize-attribute-from-module-data
		     object name actual-value (xml-object-text-of-p value) (xml-object-unit value))))
      (do-contents (name value)
	(re-initialize-all-generic-simulation-formulas-from-modula-data value)))))

(defun update-all-buttons-from-module-data (object-and-fixups)
  (with-xml-object (object-and-fixups object)
    nil
    (progn
      (when (of-class-p object 'non-action-button)
	(update-button object))
      (do-contents (name value)
	(update-all-buttons-from-module-data value)))))

(defun fix-clear-text-item-layering-from-module-data (object-and-fixups)
  (fix-clear-text-item-layering-from-module-data-1 object-and-fixups)
  (fix-clear-text-item-layering-from-module-data-2 object-and-fixups))

(defun fix-clear-text-item-layering-from-module-data-1 (object-and-fixups)
  (with-xml-object (object-and-fixups object)
    nil
    (progn
      (when (and (of-class-p object 'block)
		 (not (of-class-p object 'kb-workspace)))
	(loop for name in '(following-item-in-workspace-layering)
	      for fixups = (get-xml-fixups object-and-fixups name nil)
	      for actual-value = (lookup-xml-object fixups)
	      when actual-value
		do (initialize-attribute-from-module-data
		     object name actual-value (xml-object-text-of-p fixups) (xml-object-unit fixups))))
      (do-contents (name value)
	(fix-clear-text-item-layering-from-module-data-1 value)))))

(defun fix-clear-text-item-layering-from-module-data-2 (object-and-fixups)
  (with-xml-object (object-and-fixups object)
    nil
    (progn
      (when (of-class-p object 'kb-workspace)
	(fix-clear-text-item-layering object))
      (do-contents (name value)
	(fix-clear-text-item-layering-from-module-data-2 value)))))

(defun get-and-clear-item-layering-info-for-clear-text (kb-workspace)
  (let ((info (layering-information-for-clear-text kb-workspace)))
    (when info
      (setf (layering-information-for-clear-text kb-workspace) nil)
      (transform-item-layering-info-into-a-list kb-workspace info))))

(defun-simple transform-item-layering-info-into-a-list (kb-workspace info)
  (setq info (loop while info
		   for e = (gensym-pop info)
		   for (after . before) = e
		   for collectp = (and (eq kb-workspace (get-workspace-if-any-for-block after))
				       (eq kb-workspace (get-workspace-if-any-for-block before)))
		   do (unless collectp
			(reclaim-gensym-cons e))
		   when collectp collect e using gensym-cons))
  (loop for (after . before) in info
	do (setf (layer-position-of-block after) nil)
	   (setf (layer-position-of-block before) nil))
  (loop for (after . before) in info
	do (setf (layer-position-of-block before) after))
  (let ((top-item
	  (loop for possible-top-item = (caar info) then higher-item
		for higher-item = (layer-position-of-block possible-top-item)
		while higher-item
		do (setf (layer-position-of-block possible-top-item) nil)
		finally (return possible-top-item))))
    (loop for (after . before) in info
	  do (setf (layer-position-of-block before) nil)
	     (setf (layer-position-of-block after) nil))
    (loop for (after . before) in info
	  do (setf (layer-position-of-block after) before))
    (reclaim-gensym-tree info)
    (let ((items-from-top-to-bottom
	    (loop for item = top-item then next-item
		  while item
		  for next-item = (layer-position-of-block item)
		  do (setf (layer-position-of-block item) nil)
		  collect item using gensym-cons)))
      (recompute-layer-positions kb-workspace)
      items-from-top-to-bottom)))

(defun-void fix-clear-text-item-layering (kb-workspace)
  (let ((info (get-and-clear-item-layering-info-for-clear-text kb-workspace)))
    (when info
      (set-clear-item-layering-info-for-clear-text kb-workspace info))))

(defun-void set-clear-item-layering-info-for-clear-text (kb-workspace items-from-top-to-bottom)
  (declare (ignore kb-workspace))
  (loop for item in items-from-top-to-bottom
	do (lower-block-to-bottom item))
  (reclaim-gensym-list items-from-top-to-bottom))

(defun initialize-all-instances-from-module-data (object-and-fixups)
  (unless (and systemtables-are-initialized-p
	       (eq object-and-fixups systemtables-fixups))
    (with-xml-object (object-and-fixups object)
      object
      (progn
	#+development
	(unless object
	  (let ((class (get-xml-fixups object-and-fixups 'class nil)))
	    (when class
	      (let ((class-description (class-description class)))
		(unless (and class-description
			     (class-description-of-class-p class-description 'connection))
		  (warn "an object of class ~S was not ~A"
			class
			(if (get-xml-fixups object-and-fixups '|rdf:resource| nil)
			    "found" "created")))))))
	(if (not (framep object))
	    (do-contents (name value)
	      (let ((reading-ghost-definitions-p
		     (or reading-ghost-definitions-p
			 (equal name '|externaldefinitions|))))
		(initialize-all-instances-from-module-data value)))
	    (let ((class-definition-p (and (frame-of-class-p object 'class-definition)
					   (name-of-defined-class object)))
		  (text-box-p (or (frame-of-class-p object 'type-in-box)
				  (frame-of-class-p object 'text-box)))
		  (rule-p (frame-of-class-p object 'rule)))
	      (loop for name in '(position-in-workspace
				  icon-variables icon-reflection icon-heading
				  size-in-workspace minimum-size-in-workspace
				  parent-of-subworkspace
				  edges-of-workspace)
		    for value = (get-xml-fixups object-and-fixups name nil)
		    for actual-value = (initialize-all-instances-from-module-data value)
		    when (and actual-value
			      (not (and text-box-p
					(eq name 'size-in-workspace))))
		      do (initialize-attribute-from-module-data
			   object name actual-value
			   (xml-object-text-of-p value)
			   (xml-object-unit value)))
	      (when rule-p
		(loop for name in '(options)
		      for value = (get-xml-fixups object-and-fixups name nil)
		      for actual-value = (initialize-all-instances-from-module-data value)
		      when actual-value
			do (initialize-attribute-from-module-data
			     object name actual-value
			     (xml-object-text-of-p value)
			     (xml-object-unit value))))
	      (do-contents (name value user-p)
		(unless (and (not user-p)
			     (or (memq name '(parent-of-subworkspace
					      edges-of-workspace
					      size-in-workspace minimum-size-in-workspace
					      position-in-workspace
					      icon-variables icon-reflection icon-heading
					      following-item-in-workspace-layering))
				 (and rule-p (eq name 'options))))
		  (let ((actual-value (initialize-all-instances-from-module-data value)))
		    ;; Do initialization for all user-defined attributes, plus all attributes
		    ;; except a list of them (will be handled at other places).
		    (when (or user-p
			      (and (not (memq name '(class id |rdf:resource|
						     connection-input connection-output
						     connection-style connection-vertices
						     connection-is-directed
						     ;; GENSYMCID-1804: losing palette behavior
						     ;; Exclude additionally `relationships' here.
						     relationships)))
				   (or
				     ;; NOTE: (eq name 'relationships) can be true here.
				     (not class-definition-p)
				     ;; NOTE: a class definition can have relationships? (strange)
				     (memq name '(name-box relationships)))))
		      (initialize-attribute-from-module-data
			object name actual-value (xml-object-text-of-p value) (xml-object-unit value))))))
	      (let ((size-in-workspace
		      (get-xml-object (get-xml-fixups object-and-fixups 'size-in-workspace nil)))
		    (minimum-size-in-workspace
		      (get-xml-object (get-xml-fixups object-and-fixups 'minimum-size-in-workspace nil)))
		    (position-in-workspace
		      (get-xml-object (get-xml-fixups object-and-fixups 'position-in-workspace nil))))
		(when (and size-in-workspace (not text-box-p))
		  (initialize-attribute-from-module-data
		    object 'size-in-workspace size-in-workspace))
		(when minimum-size-in-workspace
		  (initialize-attribute-from-module-data
		    object 'minimum-size-in-workspace minimum-size-in-workspace))
		(when position-in-workspace
		  (if text-box-p
		      (let* ((current-size-in-workspace (get-size-in-workspace object))
			     ;; the x adjustment probably depends on the justification, too
			     (x-adjustment
			       (halff (-f (coerce-number-to-fixnum
					    (evaluation-structure-slot current-size-in-workspace 'width))
					  (coerce-number-to-fixnum
					    (evaluation-structure-slot size-in-workspace 'width)))))
			     (y-adjustment 0)
			     (desired-position-in-workspace
			       (allocate-evaluation-structure-inline
				 'x (+f (evaluation-structure-slot position-in-workspace 'x)
					x-adjustment)
				 'y (+f (evaluation-structure-slot position-in-workspace 'y)
					y-adjustment)
				 'superior (evaluation-structure-slot position-in-workspace 'superior))))
			(initialize-attribute-from-module-data
			  object 'position-in-workspace desired-position-in-workspace)
			(reclaim-if-evaluation-value current-size-in-workspace)
			(reclaim-evaluation-structure desired-position-in-workspace))
		      (initialize-attribute-from-module-data
			object 'position-in-workspace position-in-workspace))))
	      (unless (get-xml-fixups object-and-fixups '|rdf:resource| nil)
		(incff initialize-items-count)
		(update-initialize-xml-progress))))
	object))))


;;; GENSYMCID-1804: losing palette behavior
;;;
;;; This dedicated function will initialize all `relationships' after all instances and connections
;;; were created. -- Chun Tian (binghe), Jun 26, 2016.

(defun initialize-all-relationships-from-module-data (object-and-fixups)
  (with-xml-object (object-and-fixups object)
    object
    (progn
      (if (not (framep object))
	  (do-contents (name value)
	    (initialize-all-relationships-from-module-data value))
	  (do-contents (name value)
	    (let ((actual-value (initialize-all-relationships-from-module-data value)))
	      (when (eq name 'relationships)
		(initialize-attribute-from-module-data
		  object name actual-value
		  (xml-object-text-of-p value) (xml-object-unit value))))))
      object)))

(defun initialize-attribute-from-module-data (item attribute value &optional text-of-p unit?)
  (initialize-or-check-attribute-from-module-data item attribute value t text-of-p unit?))

(defun check-attribute-for-clear-text (item attribute value &optional text-of-p unit?)
  (let ((disable-tracing-and-breakpoints-warning t))
    (initialize-or-check-attribute-from-module-data item attribute value nil text-of-p unit?)))

(defun-void initialize-or-check-attribute-from-module-data (item attribute value initialize-p text-of-p unit?)
  (unless (memq attribute '(identifier-of-basis-kb filename-of-basis-kb))
    (let* ((*current-computation-frame* item)
	   (class-description (class-description-slot item))
	   (attribute-name (if (consp attribute) (car attribute) attribute))
	   (class-qualifier? (if (consp attribute) (cdr attribute) nil))
	   (slot-description? (get-slot-description-of-class-description
				attribute-name class-description class-qualifier?))
	   (unaliased-name?
	     (when (or (null slot-description?)
		       (system-defined-slot-description-p slot-description?))
	       (get-slot-name-for-alias-if-any attribute-name item)))
	   (unaliased-slot-description?
	     (if unaliased-name?
		 (get-slot-description-of-class-description
		   unaliased-name? class-description)
		 slot-description?))
	   (slot-type? (and unaliased-slot-description?
			    (feature-assq 'type (slot-features unaliased-slot-description?))))
	   (text-slot-p (and slot-type? (text-slot-type-p slot-type?)))
	   (problem-description?
	     (cond ((and (eq attribute 'class-name) (of-class-p item 'definition))
		    (when initialize-p
		      ;;(put-name-of-defined-class item nil nil)
		      (if reading-ghost-definitions-p
			;; GENSYMCID-1204: Errors loading kb files stored as .xml and .kbx
			(if (assq value definitions-in-module)
			  (setf (second (assq value definitions-in-module))
				(read-ghost-definition-2 value item definitions-in-module))
			  (read-ghost-definition-2 value item definitions-in-module))
			(install-class-definition value item nil nil t)))
		    nil)
		   ((eq (category-symbol-given-slot-type slot-type?) 'simulation-frame?)
		    (cond ((null value)
			   (when initialize-p
			     (put-simulation-details item value nil))
			   nil)
			  ((not (of-class-p value 'simulation-subtable))
			   (tformat-text-string "Illegal simulation-details"))
			  (t ; should already have been done
			   nil)))		    
		   ((eq (category-symbol-given-slot-type slot-type?) 'frame-edit-timestamp?)
		    (change-slot-value item attribute-name value)
		    nil)
		   (text-of-p
		    (if (not (or (text-string-p value) (null value))) ; <g2:a.TEXT></g2:a.TEXT>
			(tformat-text-string "Illegal text value")
			(when initialize-p
			  (let ((copied-text-string (copy-text-string (or value #w""))))
			    (multiple-value-bind (success? reason-for-failure?)
				(parse-and-change-slot
				  item unaliased-slot-description?
				  copied-text-string
				  slot-type?)
			      (unless success?
				(reclaim-text-string copied-text-string))
			      reason-for-failure?)))))
		   (text-slot-p
		    (tformat-text-string "Illegal text value"))
		   ((and unit?
			 unaliased-slot-description?
			 (user-defined-slot-description-p unaliased-slot-description?)
			 (or (evaluation-integer-p value)
			     (evaluation-float-p value))
			 (type-specification-type-p
			  value (slot-type-specification unaliased-slot-description?)))
		    (when initialize-p
		      (change-slot-description-value
		       item unaliased-slot-description?
		       (slot-value-list (copy-evaluation-value value) unit?))
		      nil))
		   ((and unaliased-slot-description?
			 (user-defined-slot-description-p unaliased-slot-description?)
			 (or (null value) (framep value)
			     (framep (get-slot-description-value item unaliased-slot-description?)))
			 (let ((type (slot-type-specification unaliased-slot-description?)))
			   (or (type-specification-type-p value type)
			       (and (or (class-type-specification-p type)
					(type-specifications-could-intersect-in-kb-p
					  '(class item)
					  type))
				    (null value))))
			 (not (and (framep value)
				   (or (loop for sub-item = item then parent-frame?
					     when (eq value sub-item) return sub-item
					     for parent-frame? = (parent-frame sub-item)
					     until (null parent-frame?))
				       (ancestor-p value item)))))
		    (when (and initialize-p
			       (not (eq value (get-slot-description-value
						item unaliased-slot-description?))))
		      (change-slot-description-value
			item unaliased-slot-description? (copy-if-evaluation-value value))
		      (when (framep value)
			(update-attribute-tables (parent-frame value))
			(when (superblock? value)
			  (erase-images-of-block value nil)
			  (transfer-workspace-subblock value (superblock? value) nil))))
		    nil)
		   ((and (eq unaliased-name? 'g2-array-initial-values)
			 delay-item-array-initializations-p)
		    (when initialize-p
		      (eval-push (eval-cons item value) delayed-item-array-initializations))
		    nil)
		   (initialize-p
		    (conclude-into-attribute-component
		     item attribute-name class-qualifier?
		     (copy-if-evaluation-value value) 
		     nil nil))
		   ((not (slot-description-p unaliased-slot-description?))
		    nil) ; if a v.a., run the setter with a switch: dont-conclude.
		   ((user-defined-slot-description-p unaliased-slot-description?)
		    (let* ((slot-value? (get-slot-description-value item unaliased-slot-description?))
			   (slot-value-class-description? (framep slot-value?)))
		      (if slot-value-class-description?
			  nil
			  (let ((slot-type-specification
				  (slot-type-specification unaliased-slot-description?)))
			    (unless (or (type-specification-type-p
					  value slot-type-specification)
					(and (evaluation-integer-p value)
					     (eq slot-type-specification 'float)))
			      (make-conclude-type-error-string
			        value slot-description? class-description
				item slot-type-specification))))))
		   ((memq attribute '(relation-name inverse-of-relation))
		    nil)
		   (t
		    (check-for-category-evaluator-and-slot-value-compiler-errors
		      item value unaliased-slot-description? unaliased-name?)))))
      (when problem-description?
	(report-clear-text-problem
	  (if initialize-p 'load 'save)
	  item attribute-name value problem-description?)))))

(defvar clear-text-saving-problems-were-encountered-p nil)

(defun-void report-clear-text-problem (save-or-load item attribute value problem-description?)
  (when (eq save-or-load 'save)
    (let ((module current-module-being-saved))
      (unless (memq module clear-text-saving-problems-were-encountered-p)
	(gensym-push module clear-text-saving-problems-were-encountered-p))))
  (let* ((skip-prefix (or (match-prefix #w"Unable to conclude a new value into the" problem-description?)
			  (match-prefix #w"Error concluding" problem-description?)))
	 (operation-string (case save-or-load
			     (save "Save")
			     (load "Load")))
	 (control-string
	   (if skip-prefix
	       "~A problem: ~A"
	       (if (framep value)
		   "~A problem when making ~NF be the ~S of ~NF: ~A"
		   "~A problem when making ~NV be the ~S of ~NF: ~A"))))
    (with-user-notification ()
      (if skip-prefix
	  (tformat control-string operation-string problem-description?)
	  (tformat control-string operation-string value attribute item problem-description?))
      (record-block-for-tformat item)) ; needed when skip-prefix is t
    (reclaim-text-string problem-description?)))

(defun-simple match-prefix (desired-prefix string)
  (let* ((desired-prefix-length (lengthw desired-prefix))
	 (prefix
	  (and (<f desired-prefix-length (lengthw string))
	       (copy-partial-wide-string string desired-prefix-length))))
    (prog1 (and prefix (string=w prefix desired-prefix))
      (reclaim-if-text-string prefix))))

(defun do-delayed-array-initializations ()
  (setq delay-item-array-initializations-p nil)
  (loop for e in delayed-item-array-initializations
	for (item . value) = e
	do (initialize-attribute-from-module-data item 'initial-values value)
	   (reclaim-eval-cons e)
	finally (reclaim-eval-list delayed-item-array-initializations)))

(defun fix-all-workspace-sizes-from-module-data (object-and-fixups)
  (with-xml-object (object-and-fixups object)
    nil
    (progn
      (when (of-class-p object 'kb-workspace)
	(let* ((name 'edges-of-workspace)
	       (edges (get-xml-object (get-xml-fixups object-and-fixups name nil))))
	  (when edges
	    (initialize-attribute-from-module-data object name edges))))
      (do-contents (name value)
	(fix-all-workspace-sizes-from-module-data value)))))

(defvar allow-comparison-of-slot-value-to-parse-result nil)

(defun check-for-category-evaluator-and-slot-value-compiler-errors
    (item new-value slot-description unaliased-name)
  (let* ((slot-type? (feature-assq 'type (slot-features slot-description)))
	 (category? (if slot-type? (category-symbol-given-slot-type slot-type?)))
	 (parse-result-maker? (evaluation-value-to-category-function category?))
	 (slot-value-compiler? (slot-value-compiler category?)))
    (when parse-result-maker?
      (with-attribute-export-conclude-context item
	(multiple-value-bind (parse-result-or-bad-phrase cei-error-string?)
	    (call-category-setter-fn
	      parse-result-maker?
	      new-value item slot-description nil)
	  (cond
	    ((eq parse-result-or-bad-phrase bad-phrase)
	     cei-error-string?)
	    (slot-value-compiler?
	     (multiple-value-bind (new-value-or-bad-phrase svc-error-string?)
		 (funcall-compiled-function
		   slot-value-compiler?
		   parse-result-or-bad-phrase item unaliased-name nil nil nil)
	       (cond
		 ((eq new-value-or-bad-phrase bad-phrase)
		  svc-error-string?)
		 ((and allow-comparison-of-slot-value-to-parse-result
		       ;; not safe. many s.v.c.s have side effects.
		       (let ((value (get-slot-description-value item slot-description)))
			 (unless (compare-slot-value-to-parse-result
				   item slot-description
				   value new-value-or-bad-phrase)
			   (notify-user-at-console
			     "Slot value does not match compiled result.~
                              ~%  ~A ~A~%  ~A~%  ~A"
			     (class item) (pretty-slot-name slot-description)
			     value new-value-or-bad-phrase)
			   ;;(copy-text-string "Slot value does not match compiled result")
			   nil))))
		 (t
		  nil))))))))))

(defun compare-slot-value-to-parse-result (item slot-description value new-value-or-bad-phrase)
  (or (compare-slot-value-to-parse-result-1 value new-value-or-bad-phrase)
      (case (pretty-slot-name slot-description)
	(frame-author-or-authors
	 (multiple-value-bind (sv-author sv-timestamp sv-previous)
	     (decode-frame-author-or-authors value nil)
	   (multiple-value-bind (new-author new-timestamp new-previous)
	       (decode-frame-author-or-authors value nil)
	     (and (equal sv-author new-author)
		  (equal sv-timestamp new-timestamp)
		  (equal sv-previous new-previous)))))
	(icon-description-for-class?
	 t)  ;insertions of FORGROUND and (FOREGROUND . FOREGROUND)
	(default-message-properties
	    (plist-equal-p value new-value-or-bad-phrase))
	(default-overrides
	    (and (of-class-p item 'object-definition)
		 (=f (length value) (length new-value-or-bad-phrase))
		 (loop for sv-override in value
		       for new-override in new-value-or-bad-phrase
		       always (or (compare-slot-value-to-parse-result-1
				    sv-override new-override)
				  (symbolic-parameter-initial-value-override
				    sv-override)
				  (symbolic-parameter-initial-value-override
				    new-override)
				  (eq nil (cadr sv-override))
				  (eq 'none (cadr new-override))))))
	(chart-annotations
	 t) ; needs something like plist-equal-p, but more complicated
	(log-file-name
	 t)))) ; NIL -> "".  I don't know how the NIL got there.
  
(defun compare-slot-value-to-parse-result-1 (slot-value phrase-value)
  (cond
    ((eq slot-value phrase-value)
     t)
    ((fixnump slot-value)
     (and (fixnump phrase-value)
	  (=f slot-value phrase-value)))
    ((managed-float-p slot-value)
     (and (managed-float-p phrase-value)
	  (=e (managed-float-value slot-value) (managed-float-value phrase-value))))
    ((text-string-p slot-value)
     (and (text-string-p phrase-value)
	  (string=w slot-value phrase-value)))
    ((symbolp slot-value)
     nil) ; eq test above.
    ((atom slot-value)
     #+ignore ; development
     (break)
     nil)
    ((atom phrase-value)
     #+ignore ; development
     (unless (or (fixnump phrase-value) (managed-float-p phrase-value)
		 (text-string-p phrase-value) (symbolp phrase-value))
       (break))
     (equal slot-value phrase-value))
    ((evaluation-sequence-p slot-value)
     (and (evaluation-sequence-p phrase-value)
	  (=f (evaluation-sequence-length slot-value) (evaluation-sequence-length phrase-value))
	  (loop for slot-value-value being each evaluation-sequence-element of slot-value
		for phrase-value-value being each evaluation-sequence-element of phrase-value
		always (compare-slot-value-to-parse-result-1 slot-value-value phrase-value-value))))
    ((evaluation-structure-p slot-value)
     (and (evaluation-structure-p phrase-value)
	  (and (=f (managed-array-length (evaluation-structure-value slot-value))
		   (managed-array-length (evaluation-structure-value phrase-value)))
	       (loop for (slot-value-key . slot-value-value)
			 being each evaluation-structure-pair of slot-value
		     for (phrase-value-key . phrase-value-value)
			 being each evaluation-structure-pair of phrase-value
		     always
		     (and (eq slot-value-key phrase-value-key)
			  (compare-slot-value-to-parse-result-1 slot-value-value phrase-value-value))))))
    (t
     (and (compare-slot-value-to-parse-result-1 (car slot-value) (car phrase-value))
	  (compare-slot-value-to-parse-result-1 (cdr slot-value) (cdr phrase-value))))))

(defun plist-equal-p (p1 p2)
  (and (loop for (name) on p1 by 'cddr
	     always (equal (getf p1 name) (getf p2 name)))
       (loop for (name) on p2 by 'cddr
	     always (equal (getf p1 name) (getf p2 name)))))

(defun symbolic-parameter-initial-value-override (override)
  (and (consp override)
       (consp (cdr override))
       (consp (cddr override))
       (eq (car override) 'initial-value)
       (eq (cadr override) 'symbolic-parameter)))

