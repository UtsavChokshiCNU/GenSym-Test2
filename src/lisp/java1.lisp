;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-

;;;; Module JAVA1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Joe Devlin

(in-package "AB")

;;;; Conser

(defconser java)

;;;; Forward references

;; JAVA2
(declare-forward-reference newline-text-string-character-p function)

;; JAVA3
(declare-forward-reference reclaim-external-class-info-list function)
(declare-forward-reference check-external-static-method-info function)
(declare-forward-reference check-external-instance-method-info function)
(declare-forward-reference check-external-static-methods function)
(declare-forward-reference check-exported-classes function)
(declare-forward-reference update-all-external-method-info function)
(declare-forward-reference get-exported-static-methods-if-any function)
(declare-forward-reference update-mapping-problem-frame-notes-if-necessary
			   function)
(declare-forward-reference get-hand-coded-methods-for-class-if-any function)
(declare-forward-reference get-external-class-specific-methods function)
			   

;;;; External Code Classes


(def-class (external-procedure (block entity) define-predicate)
  (frame-author-or-authors nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))
  (name-or-names-for-frame
    nil system (type nil) save)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((polychrome (g2-icon-background . light-gray)
		   (g2-icon-light-shading . smoke)
		   (g2-icon-dark-shading . dark-gray)
		   (icon-color . foreground)
		   (g2-icon-specialty-region-1 . black)
		   (g2-icon-specialty-region-2 . gray))
       g2-icon-background
       (solid-rectangle (0 0) (50 50))
       g2-icon-light-shading
       (filled-polygon ((0 0) (50 0) (47 3) (3 3) (3 47) (0 50))
		       ((0 0) (50 0) (47 3)) ((3 3) (3 47) (0 50))
		       ((0 0) (47 3) (3 3)) ((3 3) (0 50) (0 0)))
       g2-icon-dark-shading
       (filled-polygon ((47 3) (50 0) (50 50) (0 50) (3 47) (47 47))
		       ((47 3) (50 0) (50 50))
		       ((50 50) (0 50) (3 47))
		       ((47 47) (47 3) (50 50))
		       ((50 50) (3 47) (47 47)))
       icon-color
       (outline (0 0) (0 50) (50 50) (50 0))
       (text "Ext'l" (8 21) small)
       (text "Proc" (8 38) small)
       (lines (44 5) (5 5) (5 45))
       g2-icon-light-shading
       (lines (5 45) (44 45) (44 5)))))
  (external-procedure-definition
    nil (type gesture-definition text) vector-slot
    system save do-not-identify-in-attribute-tables
    do-not-clone)
  (external-procedure-code
    nil vector-slot system)
  (external-procedure-free-references
    nil vector-slot system))

(def-class-method initialize (external-procedure)
  (funcall-superior-method external-procedure)
  (update-frame-status
    external-procedure 
    (if (or (frame-of-class-p external-procedure
			      'external-method-declaration)
	    (external-procedure-definition external-procedure))
	nil				; ok
	'incomplete)
    nil))

(def-class-method cleanup (external-procedure)
  (funcall-superior-method external-procedure)
  (retract-consistency-analysis external-procedure))

(def-class (external-method-declaration external-procedure define-predicate)
  ;; This method is named through this slot, not through a procedure-definition.
  ;; (There is no procedure definition.)  Make this slot visible and editable.
  (name-or-names-for-frame nil system (type name-or-names) save)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((polychrome (g2-icon-background . light-gray)
		   (g2-icon-light-shading . smoke)
		   (g2-icon-dark-shading . dark-gray)
		   (icon-color . foreground)
		   (g2-icon-specialty-region-1 . black)
		   (g2-icon-specialty-region-2 . gray))
       g2-icon-background
       (solid-rectangle (0 0) (50 50))
       g2-icon-light-shading
       (filled-polygon ((0 0) (50 0) (47 3) (3 3) (3 47) (0 50))
		       ((0 0) (50 0) (47 3)) ((3 3) (3 47) (0 50))
		       ((0 0) (47 3) (3 3)) ((3 3) (0 50) (0 0)))
       g2-icon-dark-shading
       (filled-polygon ((47 3) (50 0) (50 50) (0 50) (3 47) (47 47))
		       ((47 3) (50 0) (50 50))
		       ((50 50) (0 50) (3 47))
		       ((47 47) (47 3) (50 50))
		       ((50 50) (3 47) (47 47)))
       icon-color
       (outline (0 0) (0 50) (50 50) (50 0))
       (text "Ext'l" (8 21) small)
       (text "Decl" (8 40) small)
       (lines (44 5) (5 5) (5 45))
       g2-icon-light-shading
       (lines (5 45) (44 45) (44 5)))))
  (external-procedure-definition
    nil (type nil) vector-slot system save save
    do-not-identify-in-attribute-tables select-changes))

(def-class-method initialize (external-method-declaration)
  (funcall-superior-method external-method-declaration)
  (update-frame-status
    external-method-declaration
    (if (name-or-names-for-frame external-method-declaration)
	'nil				; ok
	'incomplete)
    nil))

(def-class (external-method external-procedure define-predicate)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((polychrome (g2-icon-background . light-gray)
		   (g2-icon-light-shading . smoke)
		   (g2-icon-dark-shading . dark-gray)
		   (icon-color . foreground)
		   (g2-icon-specialty-region-1 . black)
		   (g2-icon-specialty-region-2 . gray))
       g2-icon-background
       (solid-rectangle (0 0) (50 50))
       g2-icon-light-shading
       (filled-polygon ((0 0) (50 0) (47 3) (3 3) (3 47) (0 50))
		       ((0 0) (50 0) (47 3)) ((3 3) (3 47) (0 50))
		       ((0 0) (47 3) (3 3)) ((3 3) (0 50) (0 0)))
       g2-icon-dark-shading
       (filled-polygon ((47 3) (50 0) (50 50) (0 50) (3 47) (47 47))
		       ((47 3) (50 0) (50 50))
		       ((50 50) (0 50) (3 47))
		       ((47 47) (47 3) (50 50))
		       ((50 50) (3 47) (47 47)))
       icon-color
       (outline (0 0) (0 50) (50 50) (50 0))
       (text "Ext'l" (8 21) small)
       (text "Meth" (9 40) small)
       (lines (44 5) (5 5) (5 45))
       g2-icon-light-shading
       (lines (5 45) (44 45) (44 5)))))
  (external-method-name
    nil vector-slot system save not-user-editable (type tw-method-name))
  (external-method-class nil vector-slot system save))

(define-slot-alias qualified-name external-method-name external-method)

(def-slot-value-writer tw-method-name (value method)
  (let ((method-class? (external-method-class method)))
    (cond ((and value method-class?)
	   (tformat "~(~nq~)" value method-class?))
	  (t
	   (twrite-string "none")))))


(def-slot-putter external-procedure-definition (external-procedure slot-value
					     initializing-p)
  (declare (ignore initializing-p))
  (setf (external-procedure-definition external-procedure) slot-value) ; it's a "text" slot
  (let* ((old-gesture-function? (external-procedure-code external-procedure))
	 (compiled-gesture (car slot-value))
	 (method-or-procedure-name (compiled-gesture-name compiled-gesture)))
    (when old-gesture-function?
      (reclaim-gesture-function old-gesture-function?))
    ;; real soon
    ;; (reclaim-gesture-function )
    
    (cond ((and compiled-gesture
		(not (eq compiled-gesture no-value)))
	   (cond
	     ((frame-of-class-p external-procedure 'external-method)
	      (let* ((type (compiled-gesture-variable-type
			     (first (compiled-gesture-args compiled-gesture))))
		     (class (type-specification-class type)))
		(without-consistency-analysis (external-procedure)
		  (change-slot-value
		    external-procedure
		    'external-method-name method-or-procedure-name)
		  (change-slot-value
		    external-procedure 'external-method-class class))))
	     (t
	      (setf (name-or-names-for-frame external-procedure)
		    method-or-procedure-name)))
	   (update-frame-status
	     external-procedure nil nil)
	   (setf (external-procedure-code external-procedure)
		 (emit-compiled-gesture compiled-gesture))
	   ;; (broadcast-external-procedure external-procedure t)
	   )
	  (t
	   (setf (name-or-names-for-frame external-procedure) nil)
	   (update-frame-status external-procedure 'incomplete nil)
	   (setf (external-procedure-code external-procedure) nil)))))

(def-frame-note-writer duplicate-class-export (particulars)
  (twrite-string "there is more than one export-definition for ")
  (cond
    ((cdr particulars)
     (twrite-string "the classes ")
     (twrite-list particulars :conjoiner " and "))
    (t (tformat "the class ~A" (car particulars)))))

(define-ui-command (edit-external-procedure :name edit) (external-procedure)
  (when (and (type-of-slot-if-editable (class external-procedure)
				       'external-procedure-definition)
	     (not (frame-of-class-p external-procedure
				    'external-method-declaration))
	     (not (text-slots-in-frame-have-been-stripped-p
		    external-procedure)))
    (enter-editing-context external-procedure
			   'external-procedure-definition)))


(def-class (export-definition  (item entity)
			       not-user-instantiable
			       define-predicate)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      50 50
      ((polychrome (g2-icon-background . light-gray)
		   (g2-icon-dark-shading . dark-gray)
		   (g2-icon-light-shading . smoke)
		   (g2-icon-color . foreground)
		   (little-class-highlights . extra-light-gray)
		   (little-class-color . gray)
		   (little-class-outlines . black)
		   (little-procedure-color . gray)
		   (little-procedure-lines . black)
		   (little-procedure-highlights . smoke)
		   (little-procedure-shadows . dark-gray)
		   (single-downward-arrow . black)
		   (java-text-highlights . white)
		   (java-text . dark-slate-blue))
       (variables)
       (background-layer)
       g2-icon-background (solid-rectangle (0 0) (50 50))
       g2-icon-dark-shading
         (filled-polygon ((47 3) (50 0) (50 50) (0 50) (3 47) (47 47))
			 ((47 3) (50 0) (50 50)) ((50 50) (0 50) (3 47))
			 ((47 47) (47 3) (50 50)) ((50 50) (3 47) (47 47)))
       g2-icon-light-shading (lines (5 45) (44 45) (44 5))
       g2-icon-color
         (outline (0 0) (0 50) (50 50) (50 0)) (lines (44 5) (5 5) (5 45))
       single-downward-arrow
         (filled-polygon ((27 18) (27 28) (31 28)
			  (25 33) (19 28) (23 28) (23 18))
			 ((27 28) (31 28) (25 33)) ((25 33) (27 18) (27 28))
			 ((25 33) (19 28) (23 28))
			 ((23 28) (23 18) (27 18)) ((27 18) (25 33) (23 28)))
       little-class-highlights
         (filled-polygon ((16 7) (16 21) (8 21)) ((16 7) (16 21) (8 21)))
       little-class-color
         (filled-polygon ((8 21) (16 15) (24 21)) ((8 21) (16 15) (24 21)))
       little-class-outlines (lines (8 21) (16 7) (24 21) (8 21))
       little-procedure-color (solid-rectangle (23 9) (38 23))
       little-procedure-lines
         (outline (29 20) (29 22) (36 22) (36 20))
         (outline (25 17) (25 19) (32 19) (32 17))
         (outline (29 14) (29 16) (36 16) (36 14))
         (outline (25 11) (25 13) (32 13) (32 11))
         (outline (22 8) (22 24) (39 24) (39 8))
       little-procedure-highlights (lines (38 9) (23 9) (23 23))
       little-procedure-shadows (lines (38 9) (38 23) (23 23))
       java-text-highlights (text #w"Java" (9 43) small)
       java-text (text #w"Java" (9 42) small)
                 (text #w"Java" (8 42) small))))
  (export-definition-language java (type export-definition-language))
  (export-definition-specification
    nil (type export-definition-specification))
  (visible-class-export-information?
    nil do-not-save do-not-put-in-attribute-tables)
  ;; Don't export this; instead, require users to export via get-class-info.
  (g2-instance-methods
    nil
    (type read-only-instance-methods)
    vector-slot system do-not-save not-user-editable)
  (additional-java-methods
    nil (type java-class-body-declarations-or-none text) vector-slot
    system save)
  )

(define-slot-alias export-language export-definition-language
  export-definition)

(define-slot-alias export-specification export-definition-specification
  export-definition)

(define-slot-alias text java-methods export-definition)

(def-slot-value-reclaimer visible-class-export-information? (export-info?)
  (when export-info?
    (reclaim-external-class-info-list export-info?)))

(def-slot-value-writer export-definition-language (slot-value)
  (twrite slot-value)) ; it's a symbol

(def-slot-value-writer read-only-instance-methods (slot-value?)
  (if slot-value?
      (let ((write-symbols-parsably? nil))
	(loop for qualified-symbol in slot-value?
	      for qualified-symbol-cons on slot-value?
	      do
	  (twrite-symbol qualified-symbol)
	  (when (cdr qualified-symbol-cons)
	    (twrite-string ", "))))
      (twrite-string "none")))

(def-frame-note-writer nonexistent-classes-for-export
    (nonexistent-classes-list export-definition)
  (declare (ignore export-definition))
  (cond
    ((cdr nonexistent-classes-list)
     (tformat
       "the following classes have no corresponding definitions in G2: ")
     (twrite-list nonexistent-classes-list :conjoiner ", "))
    (t (tformat
	 "the class ~S has no corresponding definition in G2"
	 (car nonexistent-classes-list)))))

(def-frame-note-writer nonexistent-static-methods-for-export
    (particulars export-definition)
  (declare (ignore export-definition))
  (let ((enumerate-p (cdr particulars)))
    (loop for (class-name . nonexistent-methods) in particulars
	  for particulars-cons on particulars
	  for index from 0
	  do
      (when enumerate-p
	(tformat "(~A) " (+f index frame-note-index)))
      (cond
	((cdr nonexistent-methods)
	 (tformat
	   "the following static methods in class ~A ~
             have no corresponding procedure definitions in G2: "
	     class-name)
	    (twrite-list nonexistent-methods :conjoiner ", "))
	(t (tformat
	     "the static method ~A in class ~S ~
              has no corresponding procedure definition in G2"
	     (car nonexistent-methods)
	     class-name)))
      (when enumerate-p
	(when (cdr particulars-cons)
	  (twrite-string ";")
	  (twrite-line-separator)))
      finally (when enumerate-p
		(setq frame-note-index-skip (1-f index))))))

;;; The parameter `analyzing-export-definition-for-consistency-p' is necessary
;;; to prevent recursive calls to analyze-export-definition-for-consistency.
;;; Recursive invocation would disrupt the integrity of the structures in the
;;; visible-class-export-information? attribute of the export-definition being
;;; analyzed.

(defvar analyzing-export-definition-for-consistency-p nil)

(define-analyze-for-consistency export-definition
  (unless analyzing-export-definition-for-consistency-p
    (let ((compiled-item-being-analyzed export-definition)
	  (analyzing-export-definition-for-consistency-p t))
      (delete-all-consistency-analysis-frame-notes export-definition)
      (analyze-export-definition-for-consistency export-definition))))

(defmacro export-definition-language-symbol (entire-tree)
  `(car ,entire-tree))

(defmacro export-definition-class-specs (entire-tree)
  `(cadr ,entire-tree))

(defmacro export-definition-options (per-class-subtree)
  `(third ,per-class-subtree))

(defmacro export-definition-options-for-class-if-any
    (class-name entire-tree)
  `(export-definition-options
     (assq
       ,class-name
       (export-definition-class-specs ,entire-tree))))

(defun-void analyze-export-definition-for-consistency (export-definition)
  (let* ((definition-spec (export-definition-specification export-definition))
	 (language (export-definition-language-symbol definition-spec))
	 (export-specs (export-definition-class-specs definition-spec)))
    (case language
      (java
       (loop for (exported-class export-type options) in export-specs
	     do
	 (case export-type
	   ((interface code nil)
	    (check-exported-classes export-definition exported-class)
	    (check-external-static-methods
	      export-definition
	      exported-class
	      options))))
       ;; We've updated the frame notes, now for the internal structures.
       (check-external-static-method-info export-definition)
       (check-external-instance-method-info export-definition)))))

(defun-simple check-for-duplicate-class-in-single-export-definition
    (export-definition)
  (delete-frame-note-if-any
    'duplicate-class-export-in-single-item
    export-definition)
  (loop for (export-class)
	    in (export-definition-class-specs
		 (export-definition-specification export-definition))
	with classes-encountered = nil
	do
    (cond
      ((memq export-class classes-encountered)
       (add-frame-note
	 'duplicate-class-export-in-single-item
	 export-definition)
       (loop-finish))
      (t (java-push export-class classes-encountered)))
	finally (reclaim-java-list classes-encountered)))

(def-frame-note-writer duplicate-class-export-in-single-item (particulars)
  (declare (ignore particulars))
  (twrite-string "a single class has more than one set of export information.")
  (twrite-string "  All but the first will be ignored"))

(def-slot-putter export-definition-specification
    (export-definition slot-value initializing-p)
  (declare (ignore initializing-p))
  (retract-consistency-analysis export-definition)
  (setf (export-definition-specification export-definition) slot-value)
  (check-for-duplicate-class-in-single-export-definition export-definition)
  (update-all-external-method-info export-definition)
  (assert-consistency-analysis export-definition))

(def-class-method cleanup (export-definition)
  (funcall-superior-method export-definition)
  (change-slot-value export-definition 'export-definition-specification nil))

(def-slot-value-writer export-definition-specification (slot-value)
  (let ((language (car slot-value))
	(export-list (cadr slot-value)))
    (case language
      (java
       (loop for export-list-tail on export-list
	     as (class-name nil options)
		= (car export-list-tail)
	     as static-methods? = (cadr (assq 'static-methods options))
	     as directory? = (cadr (assq 'directory options))
	     as imports? = (cadr (assq 'imports options))
	     as package? = (cadr (assq 'package options))
	     as class-path? = (cadr (assq 'class-path options))
	     as superior-class-override?
		= (cadr (assq 'superior-class-override options))
	     as included-instance-methods?
		= (cadr (assq 'included-instance-methods options))
	     as excluded-instance-methods?
		= (cadr (assq 'excluded-instance-methods options))
	     as option-count = (length options)
	     as options-written = 0
	     do
	 (tformat "class ~(~a~) with~%" class-name)
	 (when directory?
	   (incff options-written)
	   (let ((write-strings-parsably? t))
	     (tformat "  directory ~s" directory?))
	   (when (<f options-written option-count)
	     (tformat " and~%")))
	 (when imports?
	   (incff options-written)
	   (tformat "  imports ~")
	   (twrite-list imports?
	     :conjoiner ", " :element-writer #'twrite-parsably)
	   (when (<f options-written option-count)
	     (tformat " and~%")))
	 (when package?
	   (incff options-written)
	   (let ((write-strings-parsably? t))
	     (tformat "  package ~s" package?))
	   (when (<f options-written option-count)
	     (tformat " and~%")))
	 (when class-path?
	   (incff options-written)
	   (let ((write-strings-parsably? t))
	     (tformat "  class-path ~s" class-path?))
	   (when (<f options-written option-count)
	     (tformat " and~%")))
	 (when superior-class-override?
	   (incff options-written)
	   (let ((write-strings-parsably? t))
	     (tformat "  superior-class-override ~(~a~)"
		      superior-class-override?))
	   (when (<f options-written option-count)
	     (tformat " and~%")))
	 (when static-methods?
	   (incff options-written)
	   (tformat "  static-methods ")
	   (twrite-list static-methods? :conjoiner ", ")
	   (when (<f options-written option-count)
	     (tformat " and~%")))
	 (when included-instance-methods?
	   (incff options-written)
	   (tformat "  only the instance methods ")
	   (twrite-list included-instance-methods? :conjoiner ", ")
	   (when (<f options-written option-count)
	     (tformat " and~%")))
	 (when excluded-instance-methods?
	   (incff options-written)
	   (tformat "  all instance methods except ")
	   (twrite-list excluded-instance-methods? :conjoiner ", ")
	   (when (<f options-written option-count)
	     (tformat " and~%")))
	 (unless (null (cdr export-list-tail))
	   (tformat ";~%"))
	 )))))

	    
(add-grammar-rules
  '(
    (export-definition-language 'java java)
    (export-definition-specification
     java-class-export-list
     (java 1))
    (java-class-export-list
     java-class-export
     (1))
    (java-class-export-list
     (java-class-export '\; java-class-export-list)
     (1 . 3))
    (java-class-export
     ('class unreserved-symbol
      ;;'as interface-or-code
      'with java-export-options)
     (2 code 4))
    (interface-or-code 'interface interface)
    (interface-or-code 'code code)
    (java-export-options
     java-export-option
     (1))
    (java-export-options
     (java-export-option 'and java-export-options)
     (1 . 3))
    (java-export-option
     ('static-methods method-name-list)
     (static-methods 2))
    (java-export-option
     ('only 'the 'instance 'methods method-name-list)
     (included-instance-methods 5))
    (java-export-option
     ('all 'instance 'methods 'except method-name-list)
     (excluded-instance-methods 5))
    (java-export-option
     ('directory whole-string)
     (directory 2))
    (java-export-option
     ('package whole-string)
     (package 2))
    (java-export-option
     ('imports java-import-list)
     (imports 2))
    (java-export-option
     ('class-path whole-string)
     (class-path 2))
    (java-export-option
     ('superior-class-override unreserved-symbol)
     (superior-class-override 2))
    (method-name-list
     unreserved-symbol
     (1))
    (method-name-list
     (unreserved-symbol '\, method-name-list)
     (1 . 3))
    (java-import-list
     whole-string
     (1))
    (java-import-list
     (whole-string '\, java-import-list)
     (1 . 3))))

(defvar collecting-frame-notes-for-class-export-p nil)
(defvar collected-frame-notes-for-class-export? nil)

(defmacro collecting-frame-notes-for-export-definition
    ((export-definition class-name) &body body)
  (avoiding-variable-capture (&aux error-string?)
    `(let* ((collecting-frame-notes-for-class-export-p t)
	    (collected-frame-notes-for-class-export? nil)
	    (,error-string? (progn ,@body)))
       (update-mapping-problem-frame-notes-if-necessary
	 ,export-definition
	 ,class-name
	 ,error-string?))))

(defun-for-system-procedure g2-export-definitions (external-definition)
  (when (eq (export-definition-language external-definition) 'java)
    (let* ((slot-value (export-definition-specification external-definition))
	   (language (export-definition-language-symbol slot-value))
	   (export-list (export-definition-class-specs slot-value))
	   (additional-methods?
	     (if (cdr export-list)
		 nil
		 (get-hand-coded-methods-for-class-if-any
		   external-definition))))
      (case language
	(java
	 (loop for export-list-tail on export-list
	       as (class-name interface-or-code options)
		  = (car export-list-tail)
	       as static-methods? = (cadr (assq 'static-methods options))
	       as directory? = (cadr (assq 'directory options))
	       as imports? = (cadr (assq 'imports options))
	       as package? = (cadr (assq 'package options))
	       as class-path? = (cadr (assq 'class-path options))
	       as superior-class-override?
		  = (cadr (assq 'superior-class-override options))
	       do
	   (case interface-or-code
	     ((interface code nil)
	      (let ((static-method-list
		      (get-exported-static-methods-if-any
			external-definition
			class-name)))
		(collecting-frame-notes-for-export-definition
		    (external-definition class-name)
		  (let ((error-string?
			  (jemit-class-to-file
			    class-name
			    static-method-list
			    (twith-output-to-text-string
			      (twrite-string directory?)
			      (jwrite-symbol class-name t)
			      (twrite-string ".java"))
			    package?
			    imports?
			    class-path?
			    nil ; unzipped-directory
			    superior-class-override?
			    additional-methods?)))
		    error-string?))
		(reclaim-slot-value-list static-method-list)
		(when additional-methods?
		  (reclaim-text-string additional-methods?)))))))))))

(define-system-rpc-access (g2-export-definitions ())
    ((export-definition (class export-definition)))
  (g2-export-definitions export-definition))





;;;; Java Class File Reader




(def-structure java-symbol
  (java-symbol-name nil) ; wide string
  (java-symbol-properties nil))

(defvar the-java-symbol-table nil)

(defun get-java-symbol-if-any? (stringw)
  (loop for java-symbol in the-java-symbol-table
	when (string=w stringw (java-symbol-name java-symbol))
	  return java-symbol))

(defun intern-java-symbol (stringw)
  (let ((java-symbol (make-java-symbol)))
    (setf (java-symbol-name java-symbol) stringw)
    (java-push java-symbol the-java-symbol-table)
    java-symbol))

(def-structure java-class
  (java-class-name nil)
  (java-class-major-version nil)
  (java-class-minor-version nil)
  (java-class-constant-count nil)
  (java-class-constant-pool nil)
  (java-class-access-flags nil)
  (java-class-this-class nil)
  (java-class-super-class nil)
  (java-class-interfaces nil)
  (java-class-fields nil) ; vector of java-fields
  (java-class-methods nil)
  (java-class-attributes nil)
  (java-class-modifiers nil))

(def-structure java-descriptor
  (java-descriptor-type nil)      ; :byte :char :double :float
					;  :int :long :short :boolean
  (java-descriptor-class-name nil) ; used if type is :class
  (java-descriptor-component-type nil))

(def-structure java-field
  (java-field-access-flags nil)
  (java-field-name-index nil)
  (java-field-descriptor-index nil)
  (java-field-attributes nil)
  (java-field-type nil)
  (java-field-name nil) ; an AB symbol
  (java-field-modifiers nil))

(def-structure java-method
  (java-method-access-flags nil)
  (java-method-name-index nil)
  (java-method-descriptor-index nil)
  (java-method-attributes nil)
  (java-method-code nil)
  (java-method-argument-types nil)
  (java-method-return-type nil)
  (java-method-name nil) ; an AB symbol
  (java-method-modifiers nil))

(def-structure java-code-exception
  (java-code-exception-start-pc nil)
  (java-code-exception-end-pc nil)
  (java-code-exception-handler-pc nil)
  (java-code-exception-catch-type-index nil))

(def-structure java-code
  (java-code-max-stack nil)
  (java-code-max-locals nil)
  (java-code-bytecodes nil)
  (java-code-exception-table nil)
  (java-code-attributes nil))

;;;; Class File Reading Utilities

(def-structure (class-file-stream
		 (:constructor
		   make-class-file-stream (class-file-stream-stream)))
  (class-file-stream-state :just-opened)
  (class-file-stream-stream nil))

(defmacro read-java-class-error (error-name)
  `(error "class file reading error ~s" ,error-name))

(defun cfs-read-byte (cfs)
  (let ((byte? (read-byte (class-file-stream-stream cfs) nil nil)))
    (cond ((null byte?)
	   (read-java-class-error 'unexpected-end-of-file))
	  (t
	   byte?))))

(defun cfs-read-u1 (cfs)
  (cfs-read-byte cfs))

(defun cfs-read-u2 (cfs)
  (+f (ashf (cfs-read-byte cfs) 8)
      (cfs-read-byte cfs)))


;;;; Class File Reading Control

(defparameter debug-read-java-class-p nil)

(defun read-java-class (filename)
  (let ((jc (make-java-class)))
    (with-open-file (in filename :element-type '(unsigned-byte 8))
      (let ((cfs (make-class-file-stream in)))
	(unless (and (=f (cfs-read-u2 cfs) #xCAFE)
		     (=f (cfs-read-u2 cfs) #xBABE))
	  (read-java-class-error 'bad-magic-number))
	(setf (java-class-major-version jc) (cfs-read-u2 cfs))
	(setf (java-class-minor-version jc) (cfs-read-u2 cfs))
	(read-java-class-constant-pool jc cfs)
	;; could probably verify intra-constant-pool pointers here
	(setf (java-class-access-flags jc) (cfs-read-u2 cfs))
	(read-java-class-this-class jc cfs)
	(read-java-class-super-class jc cfs)
	(read-java-class-interfaces jc cfs)
	(read-java-class-fields jc cfs)
	(read-java-class-methods jc cfs)
	jc))))







(defun-simple java-modifier-p (thing modifier)
  (let ((flags (cond ((java-class-p thing)
		      (java-class-access-flags thing))
		     ((java-method-p thing)
		      (java-method-access-flags thing))
		     ((java-field-p thing)
		      (java-field-access-flags thing))
		     (t
		      (error "~s is not a class, or method" thing))))
	(flag
	  (case modifier
	    (public java-access-flag-public)
	    (private java-access-flag-private)
	    (protected java-access-flag-protected)
	    (static java-access-flag-static)
	    (final java-access-flag-final)
	    ;; java-access-flag-super    
	    (synchronized java-access-flag-synchronized)
	    (volatile java-access-flag-volatile)
	    (transient java-access-flag-transient)
	    (native java-access-flag-native)
	    (interface java-access-flag-interface)
	    (abstract java-access-flag-abstract)
	    (otherwise
	     (error "unknown modifier ~s" modifier)))))
    (/=f (logandf flag flags) 0)))

(defun read-java-class-constant-pool (java-class class-file-stream)
  (let* ((constant-count (cfs-read-u2 class-file-stream))
	 (constant-vector (allocate-managed-simple-vector constant-count)))
    (format t "constant pool count =~S~%" constant-count)
    (loop with i = 1
	  while (<f i constant-count)
	  as constant = (read-java-class-constant class-file-stream)
	  do
      (setf (svref constant-vector i) constant)
      (when debug-read-java-class-p
	(format t "Const i=~s is ~s~%"
		i (svref constant-vector i)))
      (cond ((and (consp constant)
		  (or (eq (car-of-cons constant) 'long)
		      (eq (car-of-cons constant) 'double)))
	     (incff i 2))
	    (t
	     (incff i 1))))
    (setf (java-class-constant-pool java-class) constant-vector)))

(defun read-java-class-constant (cfs)
  (let ((tag (cfs-read-u1 cfs)))
    (when debug-read-java-class-p
      (format t "tag=~s~%" tag))
    (unless (<=f 1 tag 12)
      (read-java-class-error 'unknown-constant-tag))
    (fixnum-case tag
      (#.java-constant-class
	(java-list 'class (cfs-read-u2 cfs)))
      (#.java-constant-fieldref
	(java-list 'fieldref (cfs-read-u2 cfs) (cfs-read-u2 cfs)))
      (#.java-constant-methodref
	(java-list 'methodref (cfs-read-u2 cfs) (cfs-read-u2 cfs)))
      (#.java-constant-interfacemethodref
	(java-list 'interfacemethoddref (cfs-read-u2 cfs) (cfs-read-u2 cfs)))
      (#.java-constant-string
	 (when debug-read-java-class-p
	   (format t "in the string case~%"))
	(java-list 'string (cfs-read-u2 cfs)))
      (#.java-constant-integer
	(java-list 'integer (cfs-read-u2 cfs) (cfs-read-u2 cfs)))
      (#.java-constant-float
	(java-list 'integer (cfs-read-u2 cfs) (cfs-read-u2 cfs)))
      (#.java-constant-long
	(java-list 'long
		   (cfs-read-u2 cfs) (cfs-read-u2 cfs)
		   (cfs-read-u2 cfs) (cfs-read-u2 cfs)))
      (#.java-constant-double
	(java-list 'double
		   (cfs-read-u2 cfs) (cfs-read-u2 cfs)
 		   (cfs-read-u2 cfs) (cfs-read-u2 cfs)))
      (#.java-constant-nameandtype
	(java-list 'nameandtype (cfs-read-u2 cfs) (cfs-read-u2 cfs)))
      (#.java-constant-utf8
	(read-java-utf8-string cfs))
      (#.java-constant-unicode
	(error "Joe didn't expect this")))))

(defun read-java-utf8-string (cfs)
  (let* ((length (cfs-read-u2 cfs))
	 (stringw (make-wide-string length)))
    (loop with i = 0
	  with unicode = 0
	  while (<f i length)
	  as byte-1 = (cfs-read-u1 cfs)
	  do
      (cond
        ((=f (logandf byte-1 128) 0)
	 (when (=f 0 byte-1)
	   (read-java-class-error 'bad-null-char))
	 (setf unicode byte-1))
	(t
	 (let ((high-3-bits (ashf byte-1 -5)))
	   (cond ((=f high-3-bits 6)
		  (setf unicode (+f (ashf (logandf byte-1 31) 6)
				    (logandf (cfs-read-u1 cfs) 63))))
		 ((=f high-3-bits 7)
		  (setf unicode (+f (ashf (logandf byte-1 15) 12)
				    (ashf (logandf (cfs-read-u1 cfs) 63) 6)
				    (logandf (cfs-read-u1 cfs) 63))))
		 (t
		  (read-java-class-error 'ill-formed-utf8))))))
      (setf (charw stringw i) (code-wide-character unicode))
      (incff i))
    stringw))
	 

(defun get-valid-constant-pool-entry? (jc index)
  (let* ((constant-pool (java-class-constant-pool jc))
	 (length (length-of-simple-vector constant-pool)))
    (cond ((<f 0 index length)
	   (svref constant-pool index))
	  (t
	   nil))))

(defun java-constant-type-p (constant type)
  (cond ((consp constant)
	 (eq (car-of-cons constant) type))
	((stringpw constant)
	 (eq type 'utf8))
	(t
	 (error "um, uh"))))

(defun read-java-class-this-class (jc cfs)
  (let* ((index (cfs-read-u2 cfs))
	 (constant? (get-valid-constant-pool-entry? jc index)))
    (cond
      ((null constant?)
       (read-java-class-error 'this-class-index-out-of-range))
      ((java-constant-type-p constant? 'class)
       (setf (java-class-this-class jc) index))
      (t
       (read-java-class-error 'bad-this-class-constant)))))

(defun read-java-class-super-class (jc cfs)
  (let ((index (cfs-read-u2 cfs))
	constant?)
    (cond ((=f index 0)
	   (read-java-class-error 'redefining-java.lang.object-not))
	  (t
	   (setf constant? (get-valid-constant-pool-entry? jc index))))
    (cond
      ((null constant?)
       (read-java-class-error 'bad-super-class-index))
      ((java-constant-type-p constant? 'class)
       ;; 1) eventually check inheritance from "final" classes !!!
       ;; 2) eventually check that an interface has only java.lang.object as
       ;;    as a superclass
       (setf (java-class-super-class jc) index))
      (t
       (read-java-class-error 'bad-super-class-constant)))))

(defun read-java-class-interfaces (jc cfs)
  (let* ((count (cfs-read-u2 cfs))
	 (interfaces (and (>f count 0)
			  (allocate-managed-simple-vector count))))
    (loop for i from 0 below count
	  as index = (cfs-read-u2 cfs)
	  as constant? = (get-valid-constant-pool-entry? jc index)
	  do
      (cond ((and constant? (java-constant-type-p constant? 'class))
	     (setf (svref interfaces i) index))
	    (constant?
	     (read-java-class-error 'superinterface-is-not-class-constant))
	    (t
	     (read-java-class-error 'interface-index-out-of-range))))
    (setf (java-class-interfaces jc) interfaces)))
  
(defun read-java-class-fields (jc cfs)
  (let* ((count (cfs-read-u2 cfs))
	 (fields (and (>f count 0)
		      (allocate-managed-simple-vector count))))
    (loop for i from 0 below count
	  as field = (make-java-field)
	  do
      (setf (java-field-access-flags field) (cfs-read-u2 cfs))
      (setf (java-field-name-index field) (cfs-read-u2 cfs))
      (setf (java-field-descriptor-index field) (cfs-read-u2 cfs))
      (setf (java-field-attributes field)
	    (read-java-attributes jc cfs 'field))
      (setf (java-field-type field)
	    (get-next-type-from-java-descriptor
	      (get-valid-constant-pool-entry?
		jc (java-field-descriptor-index field))
	      0))
      (setf (java-field-name field)
	    (java-name-string->ab-symbol
	      (get-valid-constant-pool-entry?
		jc (java-field-name-index field))))
      (format t "Field: ~s ~30T(flags=#x~4,'0x) ~50Ttype=~s ~70T#attrs=~s~%"
	      (get-valid-constant-pool-entry?
		jc (java-field-name-index field))
	      (java-field-access-flags field)
	      (get-valid-constant-pool-entry?
		jc (java-field-descriptor-index field))
	      (if (null (java-field-attributes field))
		  0
		  (length (java-field-attributes field))))
      (when (java-field-attributes field)
	(loop with attributes = (java-field-attributes field)
	      for i from 0 below (length attributes)
	      as attribute = (svref attributes i)
	      do
	  (format t "  Attr ~s: ~s~%" i attribute)))
      (setf (svref fields i) field))
    (setf (java-class-fields jc) fields)))

(defun read-java-class-methods (jc cfs)
  (let* ((count (cfs-read-u2 cfs))
	 (methods (and (>f count 0)
		       (allocate-managed-simple-vector count))))
    (loop for i from 0 below count
	  as method = (make-java-method)
	  do
      (setf (java-method-access-flags method) (cfs-read-u2 cfs))
      (setf (java-method-name-index method) (cfs-read-u2 cfs))
      (setf (java-method-descriptor-index method) (cfs-read-u2 cfs))
      (setf (java-method-attributes method)
	    (read-java-attributes jc cfs 'method))
      (setf (java-method-name method)
	    (java-name-string->ab-symbol
	      (get-valid-constant-pool-entry?
		jc (java-method-name-index method))))
      (multiple-value-bind (argument-types return-type?)
	  (get-prototype-from-java-descriptor
	    (get-valid-constant-pool-entry?
	      jc (java-method-descriptor-index method)))
	(setf (java-method-argument-types method) argument-types)
	(setf (java-method-return-type method) return-type?))
      (format t "Method: ~s ~30T(flags=#x~4,'0x) ~50Ttype=~s ~70T#attrs=~s~%"
	      (get-valid-constant-pool-entry?
		jc (java-method-name-index method))
	      (java-method-access-flags method)
	      (get-valid-constant-pool-entry?
		jc (java-method-descriptor-index method))
	      (if (null (java-method-attributes method))
		  0
		  (length (java-method-attributes method))))
      (when (java-method-attributes method)
	(loop with attributes = (java-method-attributes method)
	      for i from 0 below (length attributes)
	      as attribute = (svref attributes i)
	      do
	  (format t "  Attr ~s: ~s~%" i attribute)))
      (setf (svref methods i) method))
    (setf (java-class-methods jc) methods)))

(defun read-java-attributes (jc cfs owner-type)
  (loop with count = (cfs-read-u2 cfs)
	with attributes = (if (>f count 0)
			      (allocate-managed-simple-vector count)
			      nil)
	with attribute-name = nil
	with attribute-length = 0
	for i from 0 below count
	as attribute-name-index = (cfs-read-u2 cfs)
	as attribute-name-constant?
	   = (get-valid-constant-pool-entry? jc attribute-name-index)
	as attribute-length-high = (cfs-read-u2 cfs)
	as attribute-length-low = (cfs-read-u2 cfs)
	as attribute = nil
	do
    (cond ((and attribute-name-constant?
		(java-constant-type-p attribute-name-constant? 'utf8))
	   (setf attribute-name attribute-name-constant?))
	  (attribute-name-constant?
	   (read-java-class-error 'attribute-name-not-utf8))
	  (t
	   (read-java-class-error 'attribute-name-index-out-of-range)))
    (cond
      ((=f (ashf attribute-length-high -8) 0)
       (setf attribute-length (+f (ashf attribute-length-high 16)
				  attribute-length-low)))
      (t
       (read-java-class-error 'attribute-data-length-must-be-less-than-16777216)))
    ;; here do something with attributes
    (cond
      ((string=w attribute-name #w"SourceFile")
       (let* ((source-file-index (cfs-read-u2 cfs))
	      (source-file-constant?
		(get-valid-constant-pool-entry? jc source-file-index)))
	 (cond ((and source-file-constant?
		     (java-constant-type-p source-file-constant? 'utf8))
		(setf attribute
		      (java-list 'source-file source-file-constant?)))
	       (t
		(read-java-class-error 'bad-source-file-attribute)))))
      ((string=w attribute-name #w"ConstantValue")
       (let* ((constant-value-index (cfs-read-u2 cfs))
	      (constant-value-constant?
		(get-valid-constant-pool-entry? jc constant-value-index)))
	 (cond
	   ((and constant-value-constant?
		 (or (java-constant-type-p constant-value-constant? 'long)
		     (java-constant-type-p constant-value-constant? 'float)
		     (java-constant-type-p constant-value-constant? 'double)
		     (java-constant-type-p constant-value-constant? 'integer)))
	    (setf attribute
		  (java-list 'constant-value constant-value-constant?)))
	   (t
	    (read-java-class-error 'bad-constant-value-attribute)))))
      ((string=w attribute-name #w"Code")
       (setf attribute
	     (java-list 'code (read-java-code jc cfs owner-type))))
      ((string=w attribute-name #w"Exceptions")
       (loop for i from 0 below attribute-length
	     do (cfs-read-u1 cfs)))
      ((string=w attribute-name #w"LineNumberTable")
       (loop for i from 0 below attribute-length
	     do (cfs-read-u1 cfs)))
      ((string=w attribute-name #w"LocalVariableTable")
       (loop for i from 0 below attribute-length
	     do (cfs-read-u1 cfs)))
      (t
       (format t "UNKNOWN ATTR ~s , skipping~%" attribute-name)
       (loop for i from 0 below attribute-length
	     do (cfs-read-u1 cfs))))
    (setf (svref attributes i) attribute)
	finally
	  (return attributes)))

(defun read-java-code (jc cfs owner-type)
  (declare (ignore owner-type))
  (let ((code (make-java-code))
	bytecode-count)
    (setf (java-code-max-stack code) (cfs-read-u2 cfs))
    (setf (java-code-max-locals code) (cfs-read-u2 cfs))
    (let* ((bytecode-count-high (cfs-read-u2 cfs))
	   (bytecode-count-low (cfs-read-u2 cfs)))
      (cond ((=f (ashf bytecode-count-high -8) 0)
	     ;; should limit code size to 65534 ?? !!!
	     (setf bytecode-count
		   (+f (ashf (logandf bytecode-count-high 255) 16)
		       bytecode-count-low))
	     (loop with bytecode-vector
		     = (allocate-byte-vector bytecode-count)
		   for i from 0 below bytecode-count
		   do
	       (setf (byte-vector-aref bytecode-vector i) (cfs-read-u1 cfs))
		   finally
		     (setf (java-code-bytecodes code) bytecode-vector)))
	    (t
	     (read-java-class-error 'bytecode-vectors-must-be-less-than-16777216))))
    (let* ((exception-table-length (cfs-read-u2 cfs))
	   (exception-table
	     (and (>f exception-table-length 0)
		  (allocate-managed-simple-vector exception-table-length))))
      (loop for i from 0 below exception-table-length
	    as exception = (make-java-code-exception)
	    as start-pc = (cfs-read-u2 cfs)
	    as end-pc = (cfs-read-u2 cfs)
	    as handler-pc = (cfs-read-u2 cfs)
	    as catch-type-index = (cfs-read-u2 cfs)
	    do
	(unless (<f -1 end-pc bytecode-count)
	  (read-java-class-error 'end-pc-out-of-range))
	(unless (<f -1 start-pc end-pc)
	  (read-java-class-error 'start-pc-out-of-range))
	(unless (<f -1 handler-pc bytecode-count)
	  (read-java-class-error 'handler-pc-out-of-range))
	(let ((constant? (get-valid-constant-pool-entry? jc catch-type-index)))
	  (unless (and constant? (java-constant-type-p constant? 'class))
	    (read-java-class-error 'bad-exception-table-class)))
	(setf (java-code-exception-start-pc exception) start-pc)
	(setf (java-code-exception-end-pc exception) end-pc)
	(setf (java-code-exception-handler-pc exception) handler-pc)
	(setf (java-code-exception-catch-type-index exception) catch-type-index)
	(setf (svref exception-table i) exception))
      (setf (java-code-exception-table code) exception-table))
    (setf (java-code-attributes code)
	  (read-java-attributes jc cfs 'code))
    code))

(defun get-prototype-from-java-descriptor (descriptor)
  (multiple-value-bind (argument-types last-position)
      (get-argument-types-from-java-descriptor descriptor)
    (let ((ch (charw descriptor last-position)))
      (cond
	((char=w ch #.%\V)
	 (values argument-types nil))
	(t
	 (values argument-types
		 (get-next-type-from-java-descriptor
		   descriptor last-position)))))))

(defun get-argument-types-from-java-descriptor (descriptor)
  (loop with argument-types = '()
        with i = 1
	for ch = (charw descriptor i)
	do
    (cond ((char=w ch #.%\))
	   (return (values (nreverse argument-types) (1+f i))))
	  (t
	   (multiple-value-bind (type new-i)
	       (get-next-type-from-java-descriptor descriptor i)
	     (java-push type argument-types)
	     (setf i new-i))))))

(defun get-next-type-from-java-descriptor (descriptor position)
  (wide-character-case (charw descriptor position)
    (#.%\B
       (values 'byte (1+f position)))
    (#.%\C
       (values 'char (1+f position)))
    (#.%\D
       (values 'double (1+f position)))
    (#.%\F
       (values 'float (1+f position)))
    (#.%\I
       (values 'int (1+f position)))
    (#.%\J
       (values 'long (1+f position)))
    (#.%\S
       (values 'short (1+f position)))
    (#.%\Z
       (values 'boolean (1+f position)))
    (#.%\L
       (get-java-class-from-descriptor
	 descriptor position))
    (#.%\[
       (multiple-value-bind (sub-type next-position)
	   (get-next-type-from-java-descriptor
	     descriptor (1+f position))
	 (values (java-list 'array sub-type) next-position)))))

(defun get-java-class-from-descriptor (descriptor position)
  (loop with last-start = nil
	with path = '()
	for i from (1+f position) by 1
	as ch = (charw descriptor i)
	do
    (cond
      ((or (char=w ch #.%\/)
	   (char=w ch #.%\;))
       (java-push (text-string-substring descriptor last-start i)
		  path)
       (setf last-start nil)
       (when (char=w ch #.%\;)
	 (return (values (nreverse path) (1+f i)))))
      ((not last-start)
       (setf last-start i)))))

(defun java-name-string->ab-symbol (string)
  ;; this has tons of assumptions in it
  (intern-text-string
    (twith-output-to-text-string
      (loop for i from 0 below (text-string-length string)
	    as ch = (charw string i)
	    do

	(cond ((char=w ch #.%\_)
	       (twrite-char #\-))
	      ((upper-case-pw ch)
	       (twrite-char #\-)
	       (twrite-char ch))
	      (t
	       (twrite-char
		 (char-upcasew ch))))))))

;; Questions:
;; How are class field/attribute overrides done
;; how will on-error and signal work?
;; Delete should be assign null ???


(defvar current-jemit-text-style? nil)

(defun-simple get-gensym-list-of-external-procedures (sequence-of-symbols)
  (let ((static-methods
	  (loop for external-procedure-name
		    being each evaluation-sequence-element
		    of sequence-of-symbols
		as external-procedure?
		   = (get-instance-with-name-if-any
		       'external-procedure
		       external-procedure-name)
		when external-procedure?
		  collect external-procedure? using gensym-cons)))
    static-methods))

(defvar deferring-errors-for-class-export-p nil)
(defvar deferred-errors-for-class-export? nil)

(defmacro deferring-errors-for-export-definition (&body body)
  `(let* ((deferring-errors-for-class-export-p t)
	  (deferred-errors-for-class-export? nil))
     ,@body
     (loop for error in deferred-errors-for-class-export?
	   do
       (warning-message 1 "JEMIT ERROR: ~a" error))
     (reclaim-slot-value deferred-errors-for-class-export?)))

(defun-for-system-procedure g2-emit-class-as-java
    (class-name
      static-methods ; a sequence of symbols
      directory
      package-or-false
      imports ; a sequence
      class-path
      unzipped-class-directory
      override-parent?)
  
  (let ((class-description? (class-description class-name))
	(static-method-list
	  (get-gensym-list-of-external-procedures static-methods))
	(import-list
	  (loop for import being each evaluation-sequence-element of imports
		collect import
		  using gensym-cons)))
    (unless (symbolp override-parent?)
      (setf override-parent? nil))
    (cond ((and class-description?
		(class-description-of-class-p class-description? 'item))
	   (let* ((wide-filename (twith-output-to-text-string
				   (twrite directory)
				   (jwrite-symbol class-name t)
				   (twrite-string ".java")))
		  (ascii-filename 
		    (wide-string-to-gensym-string wide-filename)))
	     (reclaim-text-string wide-filename)
	     (deferring-errors-for-export-definition
	       (jemit-class-to-file
		 class-name static-method-list ascii-filename
		 (if (eq package-or-false evaluation-false-value)
		     nil
		     package-or-false)
		 import-list
		 class-path unzipped-class-directory
		 override-parent?
		 nil))
	     (reclaim-gensym-string ascii-filename)))
	  (t
	   (warning-message 1 "unacceptable class for java emitter: ~A" class-name)))
    (reclaim-evaluation-value static-methods)
    (reclaim-evaluation-value imports)
    (reclaim-gensym-list static-method-list)
    (reclaim-gensym-list import-list)))

(defmacro jwith-output-to-file ((filename out?-var) &body body)
  (avoiding-variable-capture (&aux jemit-error?)
    `(let ((,jemit-error? nil)
	   (current-jemit-text-style?
	    (or (get-text-conversion-style-structure-per-name
		  (text-conversion-style language-parameters))
		;; jh, 9/15/97.  We need to emit the modified UTF-8, specified
		;; by Java class file format.  Close the gap soon.
		(text-conversion-style-for-purpose 'utf-8-string))))
      (with-catch-handlers
	  (((:jemit-error) (error-text-string)
	    (setq ,jemit-error? error-text-string)))
	(protected-let ((,out?-var
			   (g2-stream-open-for-output ,filename)
			   (g2-stream-close ,out?-var)))
	  (when ,out?-var
	    ,@body)))
      (cond
	(,jemit-error?
	 (warning-message 1 "JEMIT ERROR: ~a" ,jemit-error?)
	 ,jemit-error?)
	(t nil)))))

;;; The macro `jwith-output-to-text-string' returns two values, in the following
;;; two scenarios.
;;;   (1) If the body was executed without a throw to :jemit-error, the values
;;;       are the successfully emitted text-string and nil.
;;;   (2) If a throw to :jemit-error occurred, the values are nil and the error
;;;       text-string.

;;; In either scenario, the return text-string is the responsibility of the
;;; caller to reclaim.  Throws to any tag other than :jemit-error will not be
;;; caught, leading to unreliable behavior.

;;; Note: since the expansion of this macro includes the "catch" special form,
;;; it must be used within a defun-allowing-unwind scope.

(defmacro jwith-output-to-text-string ((out?-var) &body body)
  (avoiding-variable-capture (&aux jemit-error? success-string)
    `(let* ((,jemit-error? nil)
	    (,out?-var 'jwith-output-to-text-string)
	    (,success-string
	      (twith-output-to-text-string
		(with-catch-handlers
		    (((:jemit-error) (error-text-string)
		      (setq ,jemit-error? error-text-string)))
		  ,@body))))
       (cond
	 (,jemit-error?
	  (reclaim-if-text-string ,success-string)
	  (values nil ,jemit-error?))
	 (t (values ,success-string nil))))))

(defun-allowing-unwind jemit-class-to-stream
    (class-name
      static-methods
      package?
      imports
      class-path
      unzipped-directory
      override-parent?
      additional-methods?
      stream)
  (declare (ignore class-path unzipped-directory))
  (protected-let ((class-description (class-description class-name))
		    (methods
		      (get-external-class-specific-methods class-name)
		      (reclaim-gensym-list methods)))
      (jemit-package stream package?)
      (jemit-imports stream imports)
      (jemit-class-header stream class-description override-parent?)
      (jemit-fields stream class-description)
      (jemit-methods stream class-description static-methods t)
      (jemit-methods stream class-description methods nil)
      (when additional-methods?
	(joutput-line stream #w"")
	(joutput-canned-text-with-indentation
	  stream
	  additional-methods?
	  4))
      (jemit-class-footer stream)))

(defun-allowing-unwind jemit-class-to-file
    (class-name
      static-methods
      filename
      package?
      imports
      class-path
      unzipped-directory
      override-parent?
      additional-methods?)
  (jwith-output-to-file (filename out?)
    (jemit-class-to-stream
      class-name
      static-methods
      package?
      imports
      class-path
      unzipped-directory
      override-parent?
      additional-methods?
      out?)))

(defun-void jemit-error (text-string)
  #+development
  (loop for b in (verbose-backtrace)
	do
    (format t "~a~%" b))
  (throw :jemit-error text-string))

(defmacro jwith-output-to-text-line ((out) &body body)
  `(let ((text-string
	   (twith-output-to-text-string
	     ,@body)))
     (joutput-line ,out text-string)
     (reclaim-text-string text-string)))

#+development
(defparameter verbose-joutput-p nil)

(defun-void joutput-line (out text-string)
  #+development
  (when verbose-joutput-p
    (let ((gensym-string
	    (export-text-string
	      text-string
	      'iso-8859-1-gensym-string)))
      (format t "~S~%" gensym-string)
      (reclaim-gensym-string gensym-string)))
  (case out
    (jwith-output-to-text-string
     (twrite-string text-string)
     ;; jh, 10/1/97.  I.e., if we are actually writing to a file at top-level.
     ;; This is so we can isolate an error in a single method by gathering its
     ;; lines in a text-string before emitting.
     (if current-jemit-text-style?
	 (twrite-char #\Newline)
	 (twrite-line-separator)))
    (otherwise
     (export-and-emit-text-line
       text-string current-jemit-text-style? out))))

(defun-void joutput-string (out text-string)
  #+development
  (when verbose-joutput-p
    (let ((gensym-string
	    (export-text-string
	      text-string
	      'iso-8859-1-gensym-string)))
      (format t "~S~%" gensym-string)
      (reclaim-gensym-string gensym-string)))
  (case out
    (jwith-output-to-text-string
     (twrite-string text-string))
    (otherwise
     (export-and-emit-text-string
       text-string current-jemit-text-style? out))))

(defun-void joutput-canned-text-with-indentation (out text-string indentation)
  (loop with canned-indentation
	= (make-wide-string indentation :initial-element #.%space)
	with length = (text-string-length text-string)
	for index from 0 below length
	 as previous-newline-index = 0 then (1+f this-newline-index?)
	 as this-newline-index?
	    = (loop for line-index from previous-newline-index below length
		    for this-wchar = (charw text-string line-index)
		    when (newline-text-string-character-p this-wchar)
		      do (return line-index)
		    finally (return nil))
 	 as no-more-lines-p = (null this-newline-index?)
	 as this-substring = (text-string-substring
			       text-string
			       previous-newline-index
			       (or this-newline-index? length))
	do
    (case out
      (jwith-output-to-text-string
       (twrite-string canned-indentation)
       (twrite-string this-substring)
       (twrite-line-separator))
      (otherwise
       (export-and-emit-text-string
	 canned-indentation current-jemit-text-style? out)
       (export-and-emit-text-line
	 this-substring current-jemit-text-style? out)))
    (reclaim-text-string this-substring)
    (when no-more-lines-p (loop-finish))
	finally (reclaim-text-string canned-indentation)))


(defun jemit-package (out package?)
  (when package?
    (jwith-output-to-text-line (out)
      (twrite-string "package ")
      (twrite package?)
      (twrite-string ";"))
    (jwith-output-to-text-line (out)
      (twrite-string " "))))

(defun jemit-imports (out imports)
  (jwith-output-to-text-line (out)
    (twrite-string "import COM.gensym.util.*;"))
  (loop for import in imports
	do
    (jwith-output-to-text-line (out)
      (twrite-string "import ")
      (twrite import)
      (twrite-string ";")))
  (jwith-output-to-text-line (out)
    (twrite-string " ")))

(defun jemit-class-header (out class-description override-parent?)
  (let ((class-name (class-name-of-class-description class-description)))
    (jwith-output-to-text-line (out)
      (twrite-string "public class ")
      (jwrite-symbol (class-name-of-class-description class-description) t)
      (twrite-string " extends ")
      (let ((direct-superiors (direct-superior-classes class-name)))
	(when (cdr direct-superiors)
	  (jemit-error (tformat-text-string "Multiple Inheritance on ~a" class-name)))
	(if (and (not override-parent?)
		 (eq (car direct-superiors) 'tw-user-item))
	    (twrite-string "Object")
	    (jwrite-symbol (or override-parent? (car direct-superiors)) t))))
    (jwith-output-to-text-line (out)
      (twrite-string "{"))))

(defun jwrite-symbol (symbol
		       &optional (class-p nil)
		                 (mixed-case-reverses-case-p t))
  (let* ((symbol-name (symbol-name symbol))
	 (len (length symbol-name))
	 (reverse-case-here-p
	   (and mixed-case-reverses-case-p
		(loop for index from 0 below len
		      thereis (lower-case-p (char symbol-name index))))))
    (if reverse-case-here-p
	(loop with after-hyphen-p = class-p
	      for i from 0 below len
	      as ch = (char symbol-name i)
	      do
	  (cond
	    ((eql ch #\-)
	     (setf after-hyphen-p t))
	    (after-hyphen-p
	     (setf after-hyphen-p nil)
	     (twrite (char-upcase ch)))
	    (t (if (lower-case-p ch)
		   (twrite (char-upcase ch))
		   (twrite (char-downcase ch))))))
	(loop with after-hyphen-p = class-p
	      for i from 0 below len
	      as ch = (char symbol-name i)
	      do
	  (cond
	    ((eql ch #\-)
	     (setf after-hyphen-p t))
	    (after-hyphen-p
	     (setf after-hyphen-p nil)
	     (twrite (char-upcase ch)))
	    (t (twrite (char-downcase ch))))))))

(defun jwrite-type-specification (type-specification)
  (cond
    ((symbolp type-specification)
     (case type-specification
       (integer
	(twrite-string "int"))
       (float
	(twrite-string "double"))
       (text
	(twrite-string "String"))
       (symbol
	(twrite-string "Symbol"))
       (truth-value
	(twrite-string "boolean"))
       (otherwise
	(jemit-error
	  (tformat-text-string "~a is not supported")))))
    ((consp type-specification)
     (case (car type-specification)
       (class
	(case (cadr type-specification)
	  (integer-array
	   (twrite-string "int[]"))
	  (float-array
	   (twrite-string "double[]"))
	  (otherwise
	   (jwrite-symbol (cadr type-specification) t))))
       (sequence (twrite-string "Sequence"))
       (structure (twrite-string "Structure"))
       (or
	(cond
	  ((equal type-specification '(or item-or-datum (no-item)))
	   (twrite-string "Object"))
	  (t
	   (jemit-error
	     (tformat-text-string
	       "strange type specification ~NT" type-specification)))))
       (otherwise
	(jemit-error
	  (tformat-text-string
	    "strange type specification ~NT" type-specification)))))
    (t
     (jemit-error
       (tformat-text-string
	 "strange type specification ~NT" type-specification)))))

(defun jemit-fields (out class-description)
  (jemit-fields-for-slot-names
    out
    class-description
    (slots-local-to-class class-description))
  ;; jed: The following hack is due to class system weirdness that I don't get.
  #+no ;jh, 9/14/97: featured out for now.
  (let ((pruned-list-of-unique-names
	  (get-really-overrided-unique-names class-description)))
    (jemit-fields-for-slot-names
      out
      class-description
      pruned-list-of-unique-names)
    (reclaim-gensym-list pruned-list-of-unique-names)))

(defun get-really-overrided-unique-names (class-description)
  (let ((local-names (slots-local-to-class class-description))
	(override-names (inherited-slots-this-class-overrides class-description)))
    (loop for override-name in override-names
	  unless (memq override-name local-names)
	    collect override-name
	      using gensym-cons)))
    
(defun jemit-fields-for-slot-names (out class-description unique-names)
  (loop for slot-name in unique-names
	as slot-description
	   = (get-slot-description-of-class-description
	       slot-name class-description)
	as type-specification = (slot-type-specification slot-description)
        as slot-init-form? = (slot-init-form slot-description)
	do
    (jwith-output-to-text-line (out)
      (twrite-string "    public ")
      (jwrite-type-specification type-specification)
      (twrite-string " ")
      (jwrite-symbol (pretty-slot-name slot-description))
      (when slot-init-form?
	(let ((initial-value slot-init-form?)
	      (casted-p nil))
	  (when (slot-constantp slot-init-form?)
	    (setf initial-value
		  (cast-slot-constant-into-evaluation-value initial-value))
	    (setf casted-p t))
	  (twrite-string " = ")
	  (cond
	    ((symbolp type-specification)
	     (case type-specification
	       ((integer float)
		(twrite initial-value))
	       (text
		(let ((write-strings-parsably? t))
		  (twrite-string initial-value)))
	       (symbol
		(twrite-string "Symbol.intern(\"")
		(twrite initial-value)
		(twrite-string "\")"))
	       (otherwise
		(jemit-error
		  (tformat-text-string
		    "unsupported initial value for ~a"
		    (pretty-slot-name slot-description))))))
	    (t
	     (cond ((fixnump initial-value)
		    (tformat "new Integer(~NV)" initial-value))
		   ((managed-float-p initial-value)
		    (tformat "new Double(~NV)" initial-value))
		   ((text-string-p initial-value)
		    (let ((write-strings-parsably? t))
		      ;; here, do I need the new String( )...
		      (twrite-string initial-value)))
		   ((symbolp initial-value)
		    (twrite-string "Symbol.intern(\"")
		    (twrite initial-value)
		    (twrite-string "\")"))
		   ((consp initial-value)
		    (cond
		      ((and (eq (car initial-value) :funcall)
			    (eq (cadr initial-value) 'instantiate-object-in-attribute))
		       (let ((class (caddr initial-value)))
			 (case class
			   (integer-array
			    (twrite-string "new int[0]"))
			   (float-array
			    (twrite-string "new double[0]"))
			   (otherwise
			    (twrite-string "new ")
			    (jwrite-symbol (caddr initial-value) t)
			    (twrite-string "()")))))
		      (t
		       (jemit-error
			 (tformat-text-string
			   "unsupported attribute initializer for ~a"
			   (pretty-slot-name slot-description))))))
		   (t
		    (jemit-error
		      (tformat-text-string
			"unsupported data type in attribute ~a"
			(pretty-slot-name slot-description)))))))
	  (when casted-p
	    (reclaim-evaluation-value initial-value))))
      (twrite-string ";"))))

(defvar collecting-exported-method-text-p nil)
(defvar list-of-exported-method-texts nil)
  
(defmacro collecting-exported-method-text
    ((var form-in-which-collection-occurs) &body body)
  `(let* ((collecting-exported-method-text-p t)
	  (list-of-exported-method-texts nil)
	  (,var ,form-in-which-collection-occurs))
     (nreversef list-of-exported-method-texts)
     ,@body))     

(defun-allowing-unwind jemit-methods (out class-description methods static-p)
  (loop for method in methods
	for exported-method-text? = nil ;i.e., nil each iteration
	do
    (format-when-tracing-in-events-modules "~s~%" method)
    (when (car (external-procedure-definition method))
      (multiple-value-bind (valid-string? error-string?)
	  (jwith-output-to-text-string
	    (this-method-stream)
	    (jemit-method
	      this-method-stream
	      class-description
	      method
	      static-p))
	(cond
	  (valid-string?
	   (joutput-string out valid-string?)
	   (if collecting-exported-method-text-p
	       (setq exported-method-text? valid-string?)
	       (reclaim-text-string valid-string?)))
	  (error-string? ;defensive
	   (cond
	     (collecting-frame-notes-for-class-export-p 
	      (slot-value-push
		error-string?
		collected-frame-notes-for-class-export?))
	     (deferring-errors-for-class-export-p
		 (slot-value-push
		   error-string?
		   deferred-errors-for-class-export?))
	     (t (jemit-error error-string?)))))))
    (when collecting-exported-method-text-p
      (slot-value-push exported-method-text? list-of-exported-method-texts))))
	       

(defun jemit-class-footer (out)
  (jwith-output-to-text-line (out)
    (twrite-string "}")))

(defvar current-jemit-stream nil)
(defvar current-jemit-indent nil)
(defvar current-jemit-node-stack nil)
(defvar current-jemit-compound-statement-list nil)
(defvar current-jemit-return-type-specification? nil)
(defvar current-jemit-class-description nil)
(defvar current-jemit-class-object-table nil)
(defvar current-jemit-self-name nil)
(defvar current-jemit-locals nil)
(defvar current-jemit-args nil)

(defmacro jwith-statement-output (&body body)
  `(jwith-output-to-text-line (current-jemit-stream)
     (loop for i from 0 below current-jemit-indent
	   do
       (twrite-string " "))
     ,@body))


(defun jemit-method (out class-description method static-p)
  (let* ((compiled-gesture
	   (car (external-procedure-definition method)))
	 (name (compiled-gesture-name compiled-gesture))
	 (current-jemit-args (compiled-gesture-args compiled-gesture))
	 (returns (compiled-gesture-returns compiled-gesture))
	 (current-jemit-locals (compiled-gesture-locals compiled-gesture))
	 (body (compiled-gesture-body compiled-gesture))
	 (current-jemit-class-object-table nil)
	 (current-jemit-stream out)
	 (current-jemit-indent 4)
	 (current-jemit-node-stack nil)
	 (current-jemit-self-name (caar current-jemit-args))
	 (current-jemit-class-description class-description)
	 (current-jemit-compound-statement-list (cadr body))
	 (current-jemit-return-type-specification?
	   (car returns)))
    (multiple-value-setq (body current-jemit-class-object-table)
      (separate-class-objects-from-real-code body))
    (when current-jemit-class-object-table
      (format-when-tracing-in-events-modules
	"class-object-table =~S~%"
	current-jemit-class-object-table))
    (jwith-statement-output (twrite-string " ")) ; blank line
    (jemit-compiled-method-prototype
      class-description name current-jemit-args returns static-p)
    (jwith-output-to-text-line (out)
      (twrite-string "    {"))
    (jemit-compiled-method-locals current-jemit-locals)
    (loop for statement in body
	  do
      (jemit-compiled-gesture-statement statement 4 nil))
    (jwith-output-to-text-line (out)
      (twrite-string "    }"))
    (reclaim-gensym-list body)
    (reclaim-gensym-tree current-jemit-class-object-table)))


(defun separate-class-objects-from-real-code (body)
  (loop with real-statements = '()
	with pairs = '()
        for statement in (cadr body)
	as statement-subforms = (cdr statement)
	as operation = (gesture-value-node-operation
			 (third statement-subforms))
	do
    (cond ((and (eq (car statement) 'local-assignment)
		(eq operation 'get-class))
	   (let ((node (third (cdr statement))))
	     (gensym-push
	       (gensym-cons
		 (first (cdr statement))
		 (let ((operand (car (gesture-value-node-args node))))
		   (if (eq (gesture-value-node-operation operand)
			   'symbol-constant)
		       (get-symbol-from-symbol-constant-node
			 (car (gesture-value-node-args node)))
		       (get-text-from-text-constant-node
			 (car (gesture-value-node-args node))))))
	       pairs)))
	  (t
	   (gensym-push statement real-statements)))
	finally
	  (return (values (nreverse real-statements)
			  (nreverse pairs)))))

(defun jemit-compiled-method-prototype (class-description
					 name args returns static-p)
  (when (cdr returns)
    (jemit-error
      (tformat-text-string "multiple-return-statements not supported")))
  (when static-p
    (let* ((class-name (class-name-of-class-description class-description))
	   (main-name (tformat-text-string "~A-MAIN" class-name))
	   (main-symbol (intern-text-string main-name)))
      (when (eq main-symbol name)
	(setq name 'main))))
  (jwith-statement-output
    (twrite-string "public ")
    (when static-p
      (twrite-string "static "))
    (cond ((null returns)
	   (twrite-string "void"))
	  (t
	   (jwrite-type-specification (car returns))))
    (twrite-string " ")
    (jwrite-symbol name)
    (twrite-string " (")
    (if (eq name 'main) ; this is a major hack !
	(twrite-string "String argv[]")
	(loop for tail on args
	      as (name type) = (car args) then (car tail)
	      do
	  (when (or static-p
		    (neq tail args))
	    (jwrite-type-specification type)
	    (twrite-string " ")
	    (jwrite-symbol name)
	    (when (cdr tail)
	      (twrite-string ", ")))))
    (twrite-string ")")))

(defun jemit-compiled-method-locals (locals)
  (let ((current-jemit-indent (+f current-jemit-indent 4)))
    (loop for (name type) in locals
	  do
      (unless (assq name current-jemit-class-object-table)
	(jwith-statement-output
	  (jwrite-type-specification type)
	  (twrite-string " ")
	  (jwrite-symbol name)
	  (twrite-string ";"))))
    (when locals
      (jwith-statement-output
	(twrite-string " ")))))
  
(defun jemit-compiled-gesture-statement
    (statement indent-increment no-terminator-p)
  (let ((statement-type (car statement))
	(statement-subforms (cdr statement))
	(current-jemit-indent (+f current-jemit-indent indent-increment)))
    (case statement-type
      (local-assignment
       (jwith-statement-output
	 (jwrite-symbol (first statement-subforms))
	 (tformat " = ")
	 (jemit-compiled-gesture-expression (third statement-subforms))
	 (unless no-terminator-p
	   (twrite-string ";"))))
      (change-slot
       (jwith-statement-output
	 (jwrite-field-reference (first statement-subforms)
				 (second statement-subforms))
	 (twrite-string " = ")
	 (jemit-compiled-gesture-expression (third statement-subforms))
	 (unless no-terminator-p
	   (twrite-string ";"))))
      (change-array-length
       (jwith-statement-output
	 (jemit-compiled-gesture-expression (first statement-subforms))
	 (twrite-string " = new ")
	 (jemit-array-type (first statement-subforms))
	 (twrite-string "[")
	 (jemit-compiled-gesture-expression (second statement-subforms))
	 (twrite-string "]")
	 (unless no-terminator-p
	   (twrite-string ";"))))
      (if
	(let ((test-expression (first statement-subforms))
	      (then-clause (second statement-subforms))
	      (else-clause? (third statement-subforms)))
	  (jwith-statement-output
	    (twrite-string "if (")
	    (jemit-compiled-gesture-expression test-expression)
	    (twrite-string ")"))
	  (jemit-compiled-gesture-statement then-clause 4 nil) ; else-clause?)
	  (when else-clause?
	    (let ((current-jemit-indent (+f 2 current-jemit-indent)))
	      (jwith-statement-output
		(twrite-string "else")))
	    (jemit-compiled-gesture-statement else-clause? 4 no-terminator-p))))
      ((gesture-call) ; soon  gesture-call-next-method call-g2)
       (jemit-call-statement statement-subforms no-terminator-p))
      (repeat
       (jwith-statement-output
	 (twrite-string "while (true)"))
       (jemit-compiled-gesture-statement
	 (car statement-subforms) 4 no-terminator-p))
      (exit-if
       (jwith-statement-output
	  (twrite-string "if (")
	  (jemit-compiled-gesture-expression
	    (first statement-subforms))
	  (twrite-string ") break;")))
      (for-loop-integer
       ;; must gensym a variable 
       (let ((iteration-var-name (first statement-subforms))
	     (initial-value-expression (third statement-subforms))
	     (limit-value-expression (fourth statement-subforms))
	     (increment (fifth statement-subforms))
	     (increasing-p (sixth statement-subforms))
	     (loop-body (seventh statement-subforms)))
	 (jwith-statement-output
	   (twrite-string "for (")
	   (jwrite-symbol iteration-var-name)
	   (twrite-string " = ")
	   (jemit-compiled-gesture-expression initial-value-expression)
	   (twrite-string " ; ")
	   (jwrite-symbol iteration-var-name)
	   (twrite (if increasing-p " <= " " >= "))
	   (jemit-compiled-gesture-expression limit-value-expression)
	   (twrite-string " ; ")
	   (jwrite-symbol iteration-var-name)
	   (twrite (if increasing-p " += " " -= "))
	   (twrite increment)
	   (twrite-string " ) "))
	 (jemit-compiled-gesture-statement loop-body 4 nil)))
      (return
	(let ((return-exp-list (first statement-subforms))
	      (fall-through-p (second statement-subforms))
	      (previous-statement? (previous-gesture-statement? statement)))
	  (when (cdr return-exp-list)
	    (jemit-error
	      (tformat-text-string "multiple-return-statements not supported")))
	  (cond
	    (fall-through-p
	     (cond
	       ((or (null previous-statement?)
		    (not (eq (car previous-statement?) 'return)))
		(cond ((null current-jemit-return-type-specification?)
		       ;; do nothing - it really is a void method
		       )
		      (t
		       (jemit-error
			 (tformat-text-string
			   "method must have return statement in all branches")))))
	       (t ; previous statement exists and it IS a return
		;; do nothing
		)))
	    (t
	     (jwith-statement-output
	       (twrite-string "return ")
	       (jemit-compiled-gesture-expression (car return-exp-list))
	       (unless no-terminator-p
		 (twrite-string ";")))))))
      (compound-statement
        (jwith-statement-output
	  (twrite-string "{"))
	(let ((current-jemit-compound-statement-list
		(first statement-subforms)))
	  (loop for sub-statement in (first statement-subforms)
		do
	    (jemit-compiled-gesture-statement sub-statement 4 nil)))
	(jwith-statement-output
	  (twrite-string "}"))))))

(defun jemit-call-statement (statement-subforms no-terminator-p)
  ;; step 1 determine class of first arg (could be none)
  ;;   class found
  ;;
  ;; 
  ;;   CLASS NOT FOUND -ERROR
  #+(and lucid development)
  (let ((lucid::*print-level* nil)
	(lucid::*print-length* nil))
    (format-when-tracing-in-events-modules "FIRST ARG~%")
    (when tracing-in-events-modules-p
      (pprint (car (fourth statement-subforms)))
      (terpri)))
  (let* ((path nil)
	 (root nil)
	 (call-name (first statement-subforms))
	 (static-method-name-p
	   (assq call-name current-jemit-class-object-table)))
    (unless static-method-name-p
      (multiple-value-setq (path root)
	(get-method-arg-path-and-root (car (fourth statement-subforms)))))
    (format-when-tracing-in-events-modules "path=~s root=~s~%" path root)
    (let* ((assignment-variable-list (second statement-subforms))
	   (compiled-arg-list (fourth statement-subforms)))
      (when (cdr assignment-variable-list)
	(jemit-error
	  (tformat-text-string
	    "multiple assignments ~s not supported" assignment-variable-list)))
      ;; should do a boatload of checking here
      (jwith-statement-output
	(when (car assignment-variable-list)
	  (jwrite-symbol (first assignment-variable-list))
	  (tformat " = "))
	(jwrite-method-call-name root path call-name)
	(twrite-string "(")
	(loop for compiled-arg in (if static-method-name-p
				      compiled-arg-list
				      (cdr compiled-arg-list))
	      with non-comma-element = (if static-method-name-p
					   (car compiled-arg-list)
					   (cadr compiled-arg-list))
	      do
	  (unless (eq compiled-arg non-comma-element)
	    (twrite-string ", "))
	  (jemit-compiled-gesture-expression compiled-arg))
	(twrite-string ")")
	(unless no-terminator-p
	  (twrite-string ";"))))))

(defun jwrite-method-call-name (root? path method-name)
  (let ((method-name-included-p nil))
    (cond
      ((and root? (eq root? current-jemit-self-name))
       ;; do nothing
       )
      ((assq method-name current-jemit-class-object-table)
       (setq method-name-included-p t)
       (let ((java-class-name
	       (cdr (assq method-name current-jemit-class-object-table))))
      	 (cond ((symbolp java-class-name)
		(jwrite-symbol java-class-name t))
	       (t
		(twrite-string java-class-name)))))
      (t
       (jwrite-symbol root?)
       (twrite-string ".")))
    (loop for elt in path
	  do
      (jwrite-symbol elt)
      (twrite-string "."))
    (unless method-name-included-p
      (jwrite-symbol method-name))))

(defun get-method-arg-path-and-root (arg-node)
  (loop with next-node = nil
	with path = '()
	for node = arg-node then next-node
	as operation = (gesture-value-node-operation node)
	as args = (gesture-value-node-args node)
	do
    (case operation
      ((value2integer value2quantity value2float
	   value2text value2symbol value2truth-value
	   value2sequence value2struct
	   value2datum value2frame)
       (setf next-node (car args)))
      (get-slot
       (gensym-push (get-symbol-from-symbol-constant-node
		      (second args))
		    path)
       (setf next-node (first args)))
      (fetch-local
       (return (values path (car args))))
      (otherwise
       (jemit-error
	 (tformat-text-string
	   "first argument to call too complex"))))))

(defun previous-gesture-statement? (current-statement)
  (loop for tail on current-jemit-compound-statement-list
	when (eq (cadr tail) current-statement)
	  return (car tail)))

(defun jwrite-field-reference (slot-name item-expression)
  (multiple-value-bind (name? class)
      (get-local-name-and-type-of-item-expression-if-simple item-expression)
    (format-when-tracing-in-events-modules
      "~%fref s=~s n?=~s c=~s curname=~s~%"
      slot-name name? class current-jemit-self-name) 
    (cond
      (name?
       (jwrite-checked-field-reference slot-name name? class))
      (t
       (cerror "go on" "emit slot existence check, Joe")
       (jemit-compiled-gesture-expression item-expression)
       (twrite-string ".")
       (jwrite-symbol slot-name)))))


(defun jwrite-checked-field-reference (slot-name item-var-name class)
  (let ((class-description
	  (cond ((eq item-var-name current-jemit-self-name)
		 current-jemit-class-description)
		(t
		 (unless (class-description class)
		   (jemit-error
		     (tformat-text-string
		       "cannot compile attribute of unknown class ~a" class)))
		 (class-description class)))))
    (cond
      ((get-slot-description-of-class-description
	 slot-name class-description)
       (cond ((eq item-var-name current-jemit-self-name)
	      (jwrite-symbol slot-name))
	     (t
	      (jwrite-symbol item-var-name)
	      (twrite-string ".")
	      (jwrite-symbol slot-name))))
      ((assq item-var-name current-jemit-class-object-table)
       (let ((java-class-name
		 (cdr (assq item-var-name current-jemit-class-object-table))))
         (if (symbolp java-class-name)
	     (jwrite-symbol java-class-name t)
	     (twrite java-class-name)))
       (twrite-string ".")
       (jwrite-symbol slot-name))
      (t
       (jemit-error
	 (tformat-text-string "undefined slot/field ~a" slot-name))))))


(defun-simple node-is-simple-item-expression-p (node)
  (and (memq (gesture-value-node-operation node) '(value2frame))
       (let ((sub-node (car (gesture-value-node-args node))))
	 (and (eq (gesture-value-node-operation sub-node) 'fetch-local)
	      (class-type-specification-p
		(gesture-value-node-type sub-node))))))

(defun get-local-name-and-type-of-item-expression-if-simple (node)
  (let ((operation (gesture-value-node-operation node)))
    (case operation
      (value2frame
       (let ((sub-node (car (gesture-value-node-args node))))
	 (and (eq (gesture-value-node-operation sub-node) 'fetch-local)
	      (class-type-specification-p
		(gesture-value-node-type sub-node))
	      (values (car (gesture-value-node-args sub-node))
		      (type-specification-class
			(gesture-value-node-type sub-node))))))
      (fetch-local
       (and (class-type-specification-p
	      (gesture-value-node-type node))
	    (values (car (gesture-value-node-args node))
		    (type-specification-class
		      (gesture-value-node-type node))))))))

(defun jemit-array-type (node)
  (let ((operation (gesture-value-node-operation node))
	(array-class? nil))
    (case operation
      (fetch-local
       (let ((type (gesture-value-node-type node)))
	 (cond
	   ((or (equal type '(class integer-array))
		(equal type '(class float-array)))
	    (setf array-class? (cadr type)))
	   (t
	    nil))))
      (get-slot
       (let ((item-node (car (gesture-value-node-args node))))
	 (when (eq (gesture-value-node-operation item-node) 'fetch-local)
	   (let ((slot-name
		   (get-symbol-from-symbol-constant-node
		     (cadr (gesture-value-node-args node))))
		 (type
		   (gesture-value-node-type item-node)))
	     (when (class-type-specification-p type)
	       (let* ((class-description? (class-description (cadr type)))
		      (slot-description?
			(and class-description?
			     (get-slot-description-of-class-description
			       slot-name class-description?)))
		      (slot-type
			(and slot-description?
			     (slot-type-specification slot-description?))))
		 (cond
		   ((or (equal slot-type '(class integer-array))
			(equal slot-type '(class float-array)))
		    (setf array-class? (cadr slot-type)))
		   (t
		    nil)))))))))
    (cond
      (array-class?
       (case array-class?
	 (float-array
	  (twrite-string "double"))
	 (integer-array
	  (twrite-string "int"))))
      (t
       (jemit-error
	 (tformat-text-string "array type not simple enough"))))))


(defparameter java-operator-precedence-list
  '(primary ; literals, "this", (<expr>), new ( ), field-access, array access
            ; method invocation , array creation expression
    postfix ; name, post-inc post-dec
    unary   ; +/- cast, pre-inc post-inc
    multiplicative ;
    additive ;
    shift ;
    relational ;
    equality ;
    and
    xor
    ior
    conditional-and
    conditional-or
    conditional))

(defun-simple java-operator-tighter-p (op1 op2)
  (let ((tail1 (memq op1 java-operator-precedence-list)))
    #+development
    (unless tail1
      (error "unknown precedence level ~s" op1))
    #+development
    (unless (memq op2 java-operator-precedence-list)
      (error "unknown precedence level ~s" op2))
    (memq op2 (cdr tail1))))



(def-global-property-name equivalent-java-operator)
(def-global-property-name equivalent-java-method)
(def-global-property-name java-operator-precedence)
(def-global-property-name java-operator-emitter-template)

(defmacro def-java-operator (name precedence template
				  &body gesture-operations)
  `(progn
     (setf (java-operator-precedence ',name) ',precedence)
     (setf (java-operator-emitter-template ',name) ',template)
     ,@(loop for operation in gesture-operations
	    collect `(setf (equivalent-java-operator ',operation)
			   ',name))))

(def-java-operator add additive ((arg 1) " + " (arg 2))
  add-fixnum add-quantity add-float tw-format-form)

(def-java-operator subtract additive ((arg 2) " - " (arg 1))
  subtract-fixnum subtract-quantity subtract-float)

(def-java-operator multiply multiplicative ((arg 1) " * " (arg 2))
  multiply-fixnum multiply-quantity multiply-float)

(def-java-operator quotient multiplicative ((arg 1) " / " (arg 2))
  quotient-fixnum quotient-quantity quotient-float)

(def-java-operator divide multiplicative ((arg 1) " / " (arg 2))
  divide-fixnum divide-float)

(def-java-operator remainder multiplicative ((arg 1) " % " (arg 2))
  remainder-fixnum remainder-quantity remainder-float)

(def-java-operator negate unary ("-" (arg 1))
  negate-fixnum negate-quantity negate-float)

(def-java-operator bitwise-or ior ((arg 1) " | " (arg 2))
  bitwise-or)

(def-java-operator bitwise-and and ((arg 1) " & " (arg 2))
  bitwise-and)

(def-java-operator equal equality ((arg 1) " == " (arg 2))
  equal-fixnum equal-quantity equal-fixnum)

(def-java-operator greater-than relational ((arg 1) " > " (arg 2))
  greater-than-fixnum greater-than-quantity greater-than-fixnum)

(def-java-operator greater-than-equal relational ((arg 1) " >= " (arg 2))
  greater-than-equal-fixnum greater-than-equal-quantity greater-than-equal-fixnum)

(def-java-operator less-than relational ((arg 1) " < " (arg 2))
  less-than-fixnum less-than-quantity less-than-fixnum)

(def-java-operator less-than-equal relational ((arg 1) " <= " (arg 2))
  less-than-equal-fixnum greater-than-equal-quantity less-than-equal-fixnum)

(def-java-operator conditional conditional
  ((arg 1) " ? " (arg 2) " : " (arg 3))
  if-expression)

(def-java-operator array-element primary
  ((arg 1) "[" (arg 2) "]")
  nth-sequence-element)

(def-java-operator array-length primary
  ((arg 1) ".length")
  array-length)
					
(defun jemit-compiled-gesture-expression (node)
  (jemit-compiled-gesture-expression-rec
    (tighten-gesture-value-node-type-information node)))

(defun tighten-gesture-value-node-type-information (node)
  node)

(defun jemit-compiled-gesture-expression-rec (node)
  (gensym-push node current-jemit-node-stack)
  (cond
    ((primitive-gesture-value-node-p node)
     (jemit-primitive-gesture-value-node node))
;    ((node-is-simple-item-expression-p node)
;     (
    (t
;    (format t "emitting:~%")
;    (pprint node)
;    (terpri)
     (let ((instruction-name
	     (get-instruction-for-gesture-value-node node))
	   (args (gesture-value-node-args node)))
       (case instruction-name
	 ((value2integer value2quantity value2float
	   value2text value2symbol value2truth-value
	   value2sequence value2struct
	   value2datum value2frame
	   int2float)
	  (jemit-cast-expression node))
	 (tw-format-form
	  (jemit-format-expression node))
	 ((get-slot-or-no-item get-slot)
	  (let ((slot-name-node (second args))
		(item-node (first args)))
	    (cond ((eq (gesture-value-node-operation slot-name-node)
		       'symbol-constant)
		   (jwrite-field-reference
		     (get-symbol-from-symbol-constant-node slot-name-node)
		     item-node))
		  (t
		   (jemit-error
		     (tformat-text-string
		       "evaluated attribute/field names needs reflection API"))))))
	 (new-class-instance
	  (jemit-new-expression node))
	 (otherwise
	  (cond
	    ((equivalent-java-operator instruction-name)
	     (jemit-gesture-node-as-operator
	       node
	       (equivalent-java-operator instruction-name)))
	    ((equivalent-java-method instruction-name)
	     )
	    (t
	     (jemit-error
	       (tformat-text-string
		 "unrecognized expression type ~a"
		 instruction-name)))))))))
  (gensym-pop current-jemit-node-stack))

(defun jemit-format-expression (node)
  (loop with args
	  = (loop with res = '()
		  for sub-node in (gesture-value-node-args node)
		  as node-operation = (gesture-value-node-operation sub-node)
		  do
	      (unless (and (eq node-operation 'text-constant)
			   (=f (text-string-length
				 (car (gesture-value-node-args sub-node)))
			       0))
		(gensym-push sub-node res))
		  finally
		    (return res))
	for arg in (cdr args)
	do
    (unless (eq arg (cadr args))
      (twrite-string "+"))
    (jemit-compiled-gesture-expression-rec arg)
	finally
	  (reclaim-gensym-list args)))

(defun jemit-new-expression (node)
  (let* ((precedence 'primary)
	 (arg (car (gesture-value-node-args node)))
	 (class-name
	   (get-symbol-from-symbol-constant-node arg))
	 (needs-parens-p
	   (operator-needs-parens-p precedence)))
    (when needs-parens-p
      (twrite-string "("))
    (twrite-string "new ")
    (jwrite-symbol class-name t)
    (twrite-string " ()")
    (when needs-parens-p
      (twrite-string ")"))))

(defun jemit-cast-expression (node)
  (let* ((instruction-name
	   (gesture-value-node-operation node))
	 (args (gesture-value-node-args node))
	 (operand (car args))
	 (operand-instruction-name
	   (gesture-value-node-operation operand))
	 (operand-type-specification (gesture-value-node-type operand))
	 (type-node? (cadr args))
	 (target-type-specification
	   (case instruction-name
	     (value2integer 'integer)
	     (value2float 'float)
	     (value2quantity 'number)
	     (value2text 'text)
	     (value2symbol 'symbol)
	     (value2truth-value 'truth-value)
	     (value2struct '(structure))
	     (value2sequence '(sequence))
	     (value2datum 'datum)
	     (value2frame (gensym-list 'class type-node?)) ; leak for now
	     (int2float 'float)
	     )))
    (cond
      ((eq operand-instruction-name 'get-slot)
       (let* ((get-slot-args (gesture-value-node-args operand))
	      (frame-arg-node (car get-slot-args))
	      (slot-name
		(get-symbol-from-symbol-constant-node
		  (cadr get-slot-args))))
	 (cond ((and (eq (gesture-value-node-operation frame-arg-node)
			 'fetch-local)
		     (class-type-specification-p
		       (gesture-value-node-type frame-arg-node)))
		(let* ((frame-class
			(type-specification-class
			  (gesture-value-node-type frame-arg-node)))
		      (frame-arg-local-name
			(car (gesture-value-node-args frame-arg-node)))
		      (slot-type-specification?
			(get-slot-type-specification-of-g2-or-java-class
			  frame-class slot-name)))
		  (cond
		    ((type-specification-subtype-p
		       slot-type-specification? target-type-specification)
		     ;; no cast needed
		     (jwrite-checked-field-reference
		       slot-name frame-arg-local-name frame-class))
		    ((and (or (equal slot-type-specification? '(class float-array))
			      (equal
				slot-type-specification? '(class integer-array)))
			  (equal target-type-specification '(sequence)))
		     (jwrite-checked-field-reference
		       slot-name frame-arg-local-name frame-class))
		    (t
		     (jemit-error
		       (tformat-text-string
			 "real casts are NYI"))))))
	       (t
		(jemit-error
		  (tformat-text-string
		    "attribute/field access expression too complex ~a"
		    slot-name))))))
      ;; eliminate unnecessary casts
      ((type-specification-subtype-p 
	 operand-type-specification target-type-specification)
       (format t "found unnecesssary cast~s~%" node)
       (jemit-compiled-gesture-expression-rec operand))
      ((type-specifications-could-intersect-p
	  operand-type-specification target-type-specification)
       (jemit-cast-gesture-node
	 operand target-type-specification))
      ((and (eq operand-type-specification 'integer)
	    (eq target-type-specification 'float))
       (jemit-cast-gesture-node operand 'float))
      ((and (or (equal operand-type-specification '(class float-array))
		(equal operand-type-specification '(class integer-array)))
	    (equal target-type-specification '(sequence)))
       (jemit-compiled-gesture-expression-rec operand))
      (t
       (jemit-error
	 (tformat-text-string
	   "INTERNAL ERROR: could never cast ~s to ~NT"
	   operand target-type-specification))))))

(defun jemit-cast-gesture-node (node type-specification)
  (let* ((precedence 'unary)
	 (cast-string?
	   (cond ((symbolp type-specification)
		  (case type-specification
		    (integer (copy-constant-wide-string #w"(int)"))
		    (float (copy-constant-wide-string #w"(double)"))
		    (text (copy-constant-wide-string #w"(String"))))
		 ((class-type-specification-p type-specification)
		  (twith-output-to-text-string
		    (tformat "(")
		    (jwrite-symbol (type-specification-class type-specification))
		    (tformat ")")))))
	 (needs-parens-p (operator-needs-parens-p precedence)))
    (unless cast-string?
      (jemit-error
	(tformat-text-string "INTERNAL ERROR: unhandled cast ~NT"
			     type-specification)))
    (when needs-parens-p
      (twrite-string "("))
    (twrite-string cast-string?)
    (reclaim-text-string cast-string?)
    (jemit-compiled-gesture-expression-rec node)
    (when needs-parens-p
      (twrite-string ")"))))


(defun get-slot-type-specification-of-g2-or-java-class (class-name slot-name)
  (let ((class-description? (class-description class-name))
	)
    (cond
      (class-description?
       (let ((slot-description?
	       (get-slot-description-of-class-description
		 slot-name class-description? nil)))
	 (cond
	   (slot-description?
	    (slot-type-specification slot-description?))
	   (t
	    (jemit-error
	      (tformat-text-string
		"unknown slot, ~s, for class ~s " slot-name class-name))))))
      (t
       (jemit-error
	 (tformat-text-string
	   "attribute/field access to non g2-defined classes is NYI"
	   slot-name))))))

(defun get-symbol-from-symbol-constant-node (node)
  (unless (eq (gesture-value-node-operation node) 'symbol-constant)
    (error "not really a symbol-constant-node ~S" node))
  (car (gesture-value-node-args node)))

(defun get-text-from-text-constant-node (node)
  (unless (eq (gesture-value-node-operation node) 'text-constant)
    (error "not really a text-constant-node ~S" node))
  (copy-text-string (car (gesture-value-node-args node))))
       
(defun-simple operator-needs-parens-p (precedence)
  (let* ((outer-node? (cadr current-jemit-node-stack))
	 (outer-instruction-name? (and outer-node?
				       (gesture-value-node-operation outer-node?))))
    (and outer-instruction-name?
	 (java-operator-tighter-p
	   (or (java-operator-precedence outer-instruction-name?)
	       'primary) ; assume its a method call
	   precedence))))

(defun jemit-gesture-node-as-operator (node operator)
  (let* ((precedence (java-operator-precedence operator))
	 (template (java-operator-emitter-template operator))
;	 (outer-node? (cadr current-jemit-node-stack))
;	 (outer-instruction-name? (and outer-node?
;				      (gesture-value-node-operation outer-node?)))
	 (needs-parens-p (operator-needs-parens-p precedence)))
    (when needs-parens-p
      (twrite-string "("))
    (loop for operand-spec in template
	  do
      (cond ((or (stringp operand-spec)
		 (text-string-p operand-spec))
	     (twrite-string operand-spec))
	    ((consp operand-spec)
	     (case (car operand-spec)
	       (arg
		(jemit-compiled-gesture-expression-rec
		  (nth (1-f (cadr operand-spec))
		       (gesture-value-node-args node))))))))
    (when needs-parens-p
      (twrite-string ")"))))

(defun jemit-primitive-gesture-value-node (node)
  (let ((args (gesture-value-node-args node)))
    (ecase (gesture-value-node-operation node)
      (fetch-local
       (let* ((local-name (car args))
	      (static-local?
		(cdr (assq local-name current-jemit-class-object-table))))
	 (if static-local?
	     (twrite-string static-local?)
	     (jwrite-symbol local-name))))
      (fetch-local-or-no-item
       ;; Umm...
       ; (emit-gesture-instruction 'get-local-or-no-item (car args)))
       )
      (integer-constant
       (twrite (car args)))
      (float-constant
       (twrite (car args)))
      (long-constant
       (twrite (car args)))
      (symbol-constant
       (tformat "Symbol.intern(\"~A\")" (car args)))
      (text-constant
       (let ((write-strings-parsably? t))
	 (twrite-string (car args))))
      (truth-value-constant
       (case (car args)
	 (true (twrite-string "true"))
	 (false (twrite-string "false"))
	 (otherwise
	  (jemit-error
	    (tformat-text-string
	      "Truth-Value constants (~a) not yet implemented"
	      (car args)))))))))

;;;; Dev Hax

#+development
(defun read-java-test (filename n)
  (with-open-file (in filename)
    (loop for i from 0 below n
	  as ch = (read-char in)
	  do
      (format t "at ~s ~s (~s)~%" n ch (char-code ch)))))
