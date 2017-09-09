;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module NEW-TABLES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author: Ben Hyde






;;;; Introduction To New Tables



;;; New tables are tabular displays of information.  The table frame contains a
;;; part description for each row and each column.  The individual cell
;;; descriptions are kept in subparts of the row descriptions.  Associated with
;;; the table is a cell-array dependent-frame.  This dependent frame is used to
;;; hold both the expressions that compute individual cells, and the cached
;;; result value of the last recompute of those values (the act of recomputing a
;;; cell is known as updating).

;;; Tables are accessed from many sources.  Screen redraw accesses them to
;;; refresh them when the user changes the screen layout.  The inference engine
;;; accesses them with updates to the data displayed in the cells.  User edits
;;; to the tables expressions, layout, and formatting access them first to
;;; update the data structures and secondly to reflect those changes on the
;;; screen.  Some changes to the layout change the overall size of the table.
;;; (Since the overall size is derived from the component sizes this access
;;; requires a scan to accumulate the total size and rebind it in the frame
;;; bounds.)

;;; The central routine in this module, the core that implements services for
;;; all these accessors, is project-new-table.  Each of these accessors scans
;;; the table data structures.  This scan is complex and to avoid duplicating
;;; the code that does this scan, a single routine encapsulates the scan.  This
;;; routine is called project-new-table.  Each of the sources above is
;;; implemented in a very stylized manner.  For example, to recompute the
;;; overall size of the table, a routine is provided which turns around and
;;; calls project-new-table after establishing a dynamic extent for it.

;;; The dynamic extent required by project-new-table is known as its projection.
;;; There are many modes of projection.  For example one mode causes it to
;;; recompute the table's size, while another mode computes which cell the
;;; user's mouse is tracking over.  These modes have in common, first, that they
;;; require scanning the table in its standard order.  More importantly, many of
;;; them require that we have the exact particulars of the table's layout
;;; computed.







;;;; Forward References For New Tables


(declare-forward-reference send-ws-representations-item-virtual-attribute-change
			   function);; EVENTS-G2
(declare-forward-reference representation-address-valid-p function) ;;VIEW-G2

;;; The routine 'project-new-table' is defined later in this module, but is
;;; often refered to earlier in the module.

(declare-forward-reference parse-text-string function)
(declare-forward-reference item-is-either-not-permanent-or-from-an-editable-module-p function)
(declare-forward-reference in-suspend-resume-p variable)





;;;; Dynamic Extents For New Tables




(def-named-dynamic-extent working-on-new-table
  (module new-tables)
  (dynamic-superior working-on-annotated-frame))

(def-named-dynamic-extent editing-new-table
  (module new-tables)
  (includes working-on-new-table)
  (dynamic-superior for-image-plane))







;;;; Part Descriptions For New Tables




;;; A table's parts consists of rows columns and cells.  Rows and columns
;;; may have most of the features of cells, so they are made simply refinements
;;; of cells.

(def-part-type new-table 
  (children-part-types row cell))


(def-part-type cell
  (includes formatted-part)
  (hidden-features line-color))

(def-part-type row 
  (includes cell)
  (user-spelling nil)
  (children-part-types cell))

(def-part-type column
  (includes cell)
  (user-spelling nil))


;;; For the table at large we store its maximum extent.

(defun table-dimension-p (x)
  (< 0 x 101))

(deftype-simple table-dimension () '(satisfies table-dimension-p))

(deftype-error-printer table-dimension (x)
  "is not in the range from 1 to 100")

(def-part-feature (new-table row-maximum) 
  (type table-dimension)
  (user-spelling number-of-rows))

(def-part-feature (new-table column-maximum) 
  (type table-dimension)
  (user-spelling number-of-columns))


;;; For each cell we maintain some colors ( background, foreground, and border)
;;; as well as a text string with the text value in it. 

(def-part-feature (cell cell-contents)
  (type cell-expression-and-text)
  (user-visible nil))


;;; The `text-value' of a cell is an unformatted text.  It is a derived
;;; value, computed from the cached value for the expression.  The table's
;;; default for any cell is the empty string.  The Graphic Element Memory
;;; of all imageplanes showing the cell contain pointers to this text.

;;; The text-value can reclaimed only when the cell is currently erased
;;; in all image planes.  It is changed (ie. old ones reclaimed and new
;;; ones computed) only during the first draw of the first imageplane
;;; during a cell update.

(deftype-simple simple-formatted-text () 'cons)

(def-part-feature-type-validation simple-formatted-text (text)
  (consp text)
  (loop for element in text
	always
    (if (text-string-p element)
	(not (and 
	       (<f 0 (text-string-length element))
	       (char=w #.%\& (charw element 0))
	       (char=w #.%\& (charw element (1-f (lengthw element))))))
	T)))

(def-part-feature (cell text-value)
  (type simple-formatted-text)
  (user-visible nil))



;;; For columns we maintain a width, and for rows we maintain a height.

(deftype-simple slot-value-number () 
  '(satisfies slot-value-number-p))

(def-part-feature (cell column-width) 
  (type slot-value-number)
  user-visible)

(def-part-feature (cell row-height) 
  (type slot-value-number)
  user-visible)



(def-part-type-semantic-check cell (cell-description)
  (let ((this-is-the-table-wide-default-cell-description-p
 	  (frame-of-class-p 
	    (frame-being-edited? current-edit-state) 
	    'new-table)))
    (cond
;      ((and this-is-the-table-wide-default-cell-description-p
;	    (part-has-feature-p cell-description 'background-color)
;	    (evaluated-computed-part-feature-p
;	      (get-simple-part-feature cell-description 'background-color)))
;       (copy-text-string
;	 "The default background-color for a table can not be given by a symbolic expression."))
      ((and (not this-is-the-table-wide-default-cell-description-p)
	    (part-has-feature-p cell-description 'width))
       (copy-text-string
	 "The width of individual cells can not be modified but you can change the default for the entire table."))
      ((and (not this-is-the-table-wide-default-cell-description-p)
	    (part-has-feature-p cell-description 'height))
       (copy-text-string
	 "The height of individual cells can not be modified but you can change the default for the entire table.")))))




;;;; Def-Class For New Tables




;;; `New-tables' is a class which refines user classes to incorporate tabular
;;; displays They provide an alternate to the tables provided by the TABLES
;;; module.

;; See notes below for details about how these slots are managed.

(def-class (new-table block) 
  ;; Internal state of the table, see notes below.
  (row-annotations nil    vector-slot system save)
  (column-annotations nil vector-slot system save)
  (cell-annotations nil   vector-slot system save)
  ;; User visible slots.
  (default-cell-format           nil vector-slot system save (type cell-format-or-none))
  (default-evaluation-setting    nil vector-slot system save (type computation-style-or-none)))

(defun cell-annotations-for-class (block)
  (cell-annotations block))

;;; The cleanup method on new tables cleans up any global data structures
;;; this table may be registered into.  For new tables the only one of these
;;; is the consistency analysis.

;(def-class-method cleanup (new-table)
;  (retract-consistency-analysis new-table))



(def-slot-putter default-cell-format (new-table cell-format-or-none)
  (with-named-dynamic-extent working-on-annotated-frame
			     ((current-annotated-frame new-table)
			      ;; current-computation-style is not bound in this situation.
			      )
    (cond
      (loading-kb-p
       (setf (default-cell-format new-table) cell-format-or-none))
      (t
       (with-named-dynamic-extent working-on-new-table ()
	 (erase-part-of-block new-table (default-cell-format new-table))
	 (setf (default-cell-format new-table) cell-format-or-none)
	 (update-new-table-size)
	 (let ((projection-focus-method 'annotation)
	       (projection-focus-annotation cell-format-or-none))
	   (funcall-method 'update-part-dependencies current-annotated-frame 'annotation cell-format-or-none))
	 (redraw-part-of-block (default-cell-format new-table)))))))


(def-slot-putter default-evaluation-setting (new-table computation-style-or-none initializing?)
  (setf (default-evaluation-setting new-table) computation-style-or-none)
  (unless initializing?
    (recompile-item new-table))
  computation-style-or-none)


;;; A `Freeform-table' is used, by users, to create a tablular display with some
;;; spreadsheet capabilities.  Each cell in a free format table is an arbitrary
;;; expression.  The `cell-annotations' slot is refined to make it user visible
;;; via the grammar `table-dimensions.'  The user may edit this slot directly to
;;; change the overall dimensions of the table.

(def-class (freeform-table (item new-table) (foundation-class freeform-table)
			   (class-export-comment "Possible exported slots and ~
 attribute mimics: <br><ul><LI>table-size: [number-of-rows: integer, ~
 number-of-columns:integer], ~
 <LI>default-cell-format: cell-format-part, ~
 <LI>default-evaluation-setting: computation-style-part, ~
 <li>row-annotations: ??? ~
 <li>column-annotations: ???, ~
 <li>cell-annotations: ???, ~
 <li>cell-array: (named-structure [cell-part, cell-expression: ~
 cell-expression-part, cell-format: cell-format-part, ~
 cell-value: item-or-value] *)</ul>"))
  (cell-annotations nil (type table-dimensions) system user-overridable)
  (default-cell-format nil vector-slot system user-overridable
		       save (type cell-format-or-none))
  (default-evaluation-setting nil vector-slot system user-overridable
			      save (type computation-style-or-none)))


(define-slot-alias table-size cell-annotations freeform-table)

(def-slot-value-writer table-dimensions (cell-annotations)
  (write-part-description 
    cell-annotations 
    '(row-maximum column-maximum)))

(add-grammar-rules
  '((table-dimensions (table-row-dimension '\; table-column-dimension) (\; 1 3))
    (table-dimensions (table-column-dimension '\; table-row-dimension) (\; 1 3))

    (table-column-dimension ('the 'number-of-columns '= integer)
			    (current-part-description 2 4) reduce-annotation)
    (table-row-dimension ('the 'number-of-rows '= integer)
			 (current-part-description 2 4) reduce-annotation)))

(def-slot-value-compiler table-dimensions (table-dimensions-parse freeform-table)
  (declare (use-for-default-overrides))
  (let (result error-message?)
    (with-named-dynamic-extent working-on-annotated-frame
			       ((current-annotated-frame freeform-table)
				(current-computation-style the-only-dynamic-computation-style))
      (multiple-value-setq (result error-message?)
	(compile-part-description table-dimensions-parse 'new-table)))
    (when result
      (setf (first result) 'table-dimensions))
    (values result error-message?)))

(define-category-evaluator-interface (table-dimensions
				       :access read-write)
    (structure table-dimension-spec
	       ((number-of-columns integer)
		(number-of-rows integer))
	       (and number-of-columns number-of-rows))
  ((set-form (evaluation-value))
   (phrase-cons
     '\;
     (with-structure (evaluation-value table-dimension-spec)
       (phrase-list
	 (phrase-list
	   'set-simple-part-feature
	   'current-part-description
	   (phrase-list 'quote 'row-maximum)
	   (phrase-list 'copy-for-slot-value
			 (phrase-list 'quote number-of-rows)))
	 (phrase-list
	   'set-simple-part-feature
	   'current-part-description
	   (phrase-list 'quote 'column-maximum)
	   (phrase-list 'copy-for-slot-value
			(phrase-list 'quote number-of-columns)))))))
  ((get-form (slot-value))
   (with-new-structure (table-dimension-spec)
     (setf number-of-columns
	   (get-simple-part-feature slot-value 'column-maximum))
     (setf number-of-rows
	   (get-simple-part-feature slot-value 'row-maximum)))))

;;; The slot putter for cell-annotations recognizes when it is called with the result of
;;; and edit by noting the absence of any subparts in the part description.  In that
;;; case it modifies the cell-annotations currently in the cell to have the new shape
;;; requested.

(def-slot-putter cell-annotations (freeform-table new-cell-annotations initializing?)
  ;; Called only by the editor.
  
  ;; The above comment is not true.  It is also called when initializing the slot
  ;; at kb-load time and when cloning.  (ghw 6/28/98)
  (cond
    ((not (eq 'table-dimensions (first new-cell-annotations)))
     ;; When initializing (initialize-slot-description-value), the current
     ;; value will be the default value (eq to the slot-init-form of the
     ;; class slot-description and not reclaimable).
     (unless initializing?
       (with-named-dynamic-extent working-on-annotated-frame
	   ((current-annotated-frame freeform-table))
	 (reclaim-part-description (cell-annotations freeform-table))))
     (values
       (setf (cell-annotations freeform-table) new-cell-annotations)
       t))
    (t
     (with-named-dynamic-extent working-on-annotated-frame
				((current-annotated-frame freeform-table)
				 (current-block-of-dependent-frame freeform-table))
       (with-named-dynamic-extent working-on-new-table ()
	 (let* ((new-row-maximum (get-simple-part-feature new-cell-annotations 'row-maximum))
		(new-column-maximum (get-simple-part-feature new-cell-annotations 'column-maximum))
		(old-cell-annotations (cell-annotations freeform-table))
		(old-row-maximum (get-simple-part-feature old-cell-annotations 'row-maximum))
		(old-column-maximum (get-simple-part-feature old-cell-annotations 'column-maximum))
		(row-delta (- new-row-maximum old-row-maximum))
		(column-delta (- new-column-maximum old-column-maximum))
		(row-index old-row-maximum)
		(column-index old-column-maximum))
	   (reclaim-slot-value new-cell-annotations)
	   ;; Adjust the rows.
	   (multiple-value-bind (edit-action count)
	       (cond
		 ((<f 0 row-delta)
		  (values 'add-row row-delta 0))
		 ((>f 0 row-delta)
		  (setf row-index new-row-maximum)
		  (values 'delete-row (-f row-delta))))
	     (when edit-action
	       (table-block-insert-or-delete
		 freeform-table row-index column-index
		 edit-action count)))
	   ;; Adjust the columns
	   (multiple-value-bind (edit-action count)
	       (cond
		 ((<f 0 column-delta)
		  (values 'add-column column-delta 0))
		 ((>f 0 column-delta)
		  (setf column-index new-column-maximum)
		  (values 'delete-column (-f column-delta) (-f column-delta))))
	     (when edit-action
	       (table-block-insert-or-delete
		 freeform-table row-index column-index
		 edit-action count)))
	   )))
     (values (cell-annotations freeform-table) t))))



;;;; Table-cells virtual attribute


;;; `make-evaluation-value-for-expression-cell-index'

(defun-simple make-evaluation-value-for-expression-cell-index
    (wide-string)
  (let ((length (lengthw wide-string)))
    (make-evaluation-value-based-on-type
      (or (read-number-from-string wide-string 0 length)
	  (read-symbol-from-string wide-string 0 length)
	  (read-text-string-from-string wide-string 0 length)))))





;;; `make-structure-for-cell-contents' 

(defun-simple make-structure-for-cell-format (feature-value new-table)
  (when (not (simple-cell-expression-p feature-value))
    (loop with eval-attrs-struct = (allocate-evaluation-structure nil)
	  with tracing-substruct? = nil
	  with cell-array? = (cell-array new-table)
	  with managed-array? = (and cell-array?
				     (g2-cell-array-managed-array cell-array?))
	  for (subfeature-name subfeature-value)
	  on (cdr feature-value) by #'cddr
 	  as eval-value = (make-evaluation-value-based-on-type subfeature-value)
	  do
      (case subfeature-name
	(expression-cell-index
	 (when managed-array?
	   (let ((expression-cell?
		   (managed-svref managed-array? subfeature-value)))
	     (when (and expression-cell?
			(g2-expression-cell-cached-value expression-cell?))
	       (setf (evaluation-structure-slot eval-attrs-struct 'current-value)
		     (copy-evaluation-value
		       (g2-expression-cell-cached-value expression-cell?)))))))
	(warning-message-level-for-computation-style
	 (unless tracing-substruct?
	   (setf tracing-substruct? (allocate-evaluation-structure nil)))
	 (setf (evaluation-structure-slot tracing-substruct? 'warning-message-level)
	       eval-value))
	(trace-message-level-for-computation-style
	 (unless tracing-substruct?
	   (setf tracing-substruct? (allocate-evaluation-structure nil)))
	 (setf (evaluation-structure-slot tracing-substruct? 'tracing-message-level)
	       eval-value))
	(break-message-level-for-computation-style
	 (unless tracing-substruct?
	   (setf tracing-substruct? (allocate-evaluation-structure nil)))
	 (setf (evaluation-structure-slot tracing-substruct? 'breakpoint-level)
	       eval-value))
	(expression-source-text
	 (let* ((width (wide-string-length subfeature-value))
		(has-semi-p (char=w #.%\;
				    (charw subfeature-value
					   (1-f width)))))
	   (if has-semi-p
	       (setf (evaluation-structure-slot eval-attrs-struct 'expression)
		     (copy-portion-of-wide-string
		       subfeature-value 0 (-f width 1)))
	       (setf (evaluation-structure-slot eval-attrs-struct 'expression)
		     (copy-wide-string
		       subfeature-value)))))
	(t
	 (setf (evaluation-structure-slot eval-attrs-struct subfeature-name)
	       eval-value)))
	  finally
	    (when tracing-substruct?
	      (setf (evaluation-structure-slot eval-attrs-struct 'tracing-and-breakpoints)
		    tracing-substruct?))
	    (when (=f 0 (evaluation-structure-length eval-attrs-struct))
	      (reclaim-evaluation-structure eval-attrs-struct)
	      (setq eval-attrs-struct nil))
	    (return eval-attrs-struct))))


		    
(defun-simple make-structure-for-cell-contents (feature-value)
  (when (not (simple-cell-expression-p (car feature-value)))
    (loop with eval-attrs-struct = (allocate-evaluation-structure nil)
	  with tracing-substruct? = nil
	  for (subfeature-name subfeature-value)
	  on (cdar feature-value) by #'cddr
 	  as eval-value = (make-evaluation-value-based-on-type subfeature-value)
	  do (case subfeature-name
	       (expression-cell-index)
	       (warning-message-level-for-computation-style
		(unless tracing-substruct?
		  (setf tracing-substruct? (allocate-evaluation-structure nil)))
		(setf (evaluation-structure-slot tracing-substruct? 'warning-message-level)
		      eval-value))
	       (trace-message-level-for-computation-style
		(unless tracing-substruct?
		  (setf tracing-substruct? (allocate-evaluation-structure nil)))
		(setf (evaluation-structure-slot tracing-substruct? 'tracing-message-level)
		      eval-value))
	       (break-message-level-for-computation-style
		(unless tracing-substruct?
		  (setf tracing-substruct? (allocate-evaluation-structure nil)))
		(setf (evaluation-structure-slot tracing-substruct? 'breakpoint-level)
		      eval-value))
	       (t
		(setf (evaluation-structure-slot eval-attrs-struct subfeature-name)
		      eval-value)))
	  finally
	    (when tracing-substruct?
	      (setf (evaluation-structure-slot eval-attrs-struct 'tracing-and-breakpoints)
		    tracing-substruct?))
	    (when (=f 0 (evaluation-structure-length eval-attrs-struct))
	      (reclaim-evaluation-structure eval-attrs-struct)
	      (setq eval-attrs-struct nil))
	    (return eval-attrs-struct))))

		    
;;; `make-sequence-of-freeform-table-row'

(defun-simple make-sequence-of-freeform-table-row (new-table row-part)
  (loop with cell-parts = (cadr (get-simple-part-feature row-part 'subparts))
	 for cell-part in cell-parts
	 collect
	 (if (null (cdr cell-part))
	     'none
	     (loop with cell-structure =  (allocate-evaluation-structure nil)
		   with format-structure? = nil
		   for (feature-name feature-value) on (cdr cell-part) by #'cddr
		   do
	       (case feature-name
		 (cell-contents
		  (let ((expression-of-cell? (cdr feature-value))
			(eval-attrs-struct? (make-structure-for-cell-contents
					     feature-value)))
		    (when expression-of-cell?
		      (let* ((width (wide-string-length expression-of-cell?))
			     (has-semi-p (char=w #.%\;
						 (charw expression-of-cell?
							(1-f width)))))
			(if has-semi-p
			    (setf (evaluation-structure-slot cell-structure 'expression)
				  (copy-portion-of-wide-string
				    expression-of-cell? 0 (-f width 1)))
			    (setf (evaluation-structure-slot cell-structure 'expression)
				  (copy-wide-string
				    expression-of-cell?)))))
		    (when eval-attrs-struct?
		      (setf (evaluation-structure-slot cell-structure
						       'cell-evaluation-attributes)
			    eval-attrs-struct?))))
		 (text-value
		  (setf (evaluation-structure-slot cell-structure
						   'cell-display-text)
			(convert-text-to-text-string feature-value)) ;;(pbk too much sometimes)
		  (let* ((cell-array? (cell-array new-table))
			 (managed-array? (and cell-array?
					      (g2-cell-array-managed-array cell-array?)))
			 (contents? (get-simple-part-feature cell-part 'cell-contents))
			 (compiled-cell?
			   (and (consp contents?)
				(let ((cell? (car-of-cons contents?)))
				  (and (compiled-cell-expression-p cell?)
				       cell?))))
			 (cell-index? (and compiled-cell?
					   (get-simple-part-feature
					     compiled-cell? 'expression-cell-index))))
		    (when (and cell-index? managed-array?)
		      (let ((expression-cell?
			      (managed-svref managed-array? cell-index?)))
			(when (and expression-cell?
				   (g2-expression-cell-cached-value expression-cell?))
			  (setf (evaluation-structure-slot cell-structure
							   'cell-display-value)
				(copy-evaluation-value
				  (g2-expression-cell-cached-value
				    expression-cell?))))))))
		 (highlighted?)
		 (otherwise
		  (unless format-structure?
		    (setf format-structure? (allocate-evaluation-structure nil))
		    (setf (evaluation-structure-slot cell-structure 'cell-format)
			  format-structure?))
		  (setf (evaluation-structure-slot format-structure? feature-name)
			(or (and (listp feature-value)
				 (make-structure-for-cell-format feature-value new-table))
			    feature-value))))
		   finally
		     (return cell-structure)))
	   into column-eval-list
	   using eval-cons
	 finally
	   (return (allocate-evaluation-sequence column-eval-list))))



;;; `handle-cell-expression'

(defun create-compiled-cell-expression (new-expression-value new-eval-attrs expression-type)
  (let* ((new-expression 
	    (evaluation-value-value new-expression-value))
	 (new-expression-description
	    (slot-value-cons
	      'compiled-cell-expression
	      (when new-eval-attrs
		(loop for (new-subfeature-name . new-subfeature-value)
			  being each evaluation-structure-pair of new-eval-attrs
		      as expression-p = (eq new-subfeature-name 'expression)
		      as tracing-substruct-p = (eq new-subfeature-name 'tracing-and-breakpoints)
		      unless (or expression-p tracing-substruct-p)
			collect new-subfeature-name using slot-value-cons
		      unless (or expression-p tracing-substruct-p)
			collect
			(if (evaluation-truth-value-p new-subfeature-value)
			    (evaluation-truth-value-is-true-p new-subfeature-value)
			    (copy-if-evaluation-value new-subfeature-value))
			  using slot-value-cons
		      when tracing-substruct-p
			nconc
			(loop for (tracing-name . tracing-value)
				  being each evaluation-structure-pair of new-subfeature-value
			      as internal-tracing-name =
			      (case tracing-name
				(warning-message-level
				 'warning-message-level-for-computation-style)
				(tracing-message-level
				 'trace-message-level-for-computation-style)
				(breakpoint-level
				 'break-message-level-for-computation-style))
			      collect internal-tracing-name using slot-value-cons
			      collect tracing-value using slot-value-cons)))))
	  (new-cell-expression nil))
    (with-phrase-conses
      (multiple-value-bind (parse-result-or-bad-phrase error-string?)
	  (parse-text-string new-expression 'cell-expression-parse)
	(cond ((or (eq parse-result-or-bad-phrase bad-phrase)
		    (neq (car parse-result-or-bad-phrase) 'source-position))
	       (values bad-phrase error-string?))
	      (t
	       (setf new-cell-expression
		     (slot-value-cons
		       (nconc
			 new-expression-description
			 (slot-value-list
			   'expression-cell-index
			   (compile-a-compiled-cell-expression-from-expression-parse-and-style-description
			     (cadr parse-result-or-bad-phrase)
			     new-expression-description
			     expression-type)))
		       (if new-eval-attrs
			   (tformat-text-string "~a;" new-expression)
			   (tformat-text-string "~a" new-expression))))
	       new-cell-expression))))))


(defun handle-cell-expression (current-annotated-frame
			       current-cell
			       new-expression-value
			       new-eval-attrs)
  (multiple-value-bind (compiled-cell-expression-or-bad-phrase error-string?)
      (create-compiled-cell-expression new-expression-value new-eval-attrs
				       '(or datum (unknown-datum) (obsolete-datum)))
    (cond ((eq compiled-cell-expression-or-bad-phrase bad-phrase)
	   (values bad-phrase error-string?))
	  (t    
	   (change-annotation
	     current-annotated-frame
	     current-cell
	     'cell-contents
	     'cell-expression-and-text
	     nil
	     compiled-cell-expression-or-bad-phrase)
	   nil))))


;;; `set-the-specified-cell-features'

(defun set-the-specified-cell-features (new-value)
  (let* ((current-cell-annotations
	    (cell-annotations current-annotated-frame))
	 (current-rows
	  (cadr (get-simple-part-feature current-cell-annotations 'subparts)))
	 (error-string? nil))
     (loop for new-row-element
	       being each evaluation-sequence-element of new-value
	   as i from 0
	   as current-row
	      = (cadr (get-simple-part-feature (nth i current-rows) 'subparts))
	   do
       (loop for new-cell-element
		 being each evaluation-sequence-element of new-row-element
	     as j from 0
	     as current-cell = (nth j current-row)
	     unless (eq new-cell-element 'none) do
		 (loop for (new-feature-name . new-feature-value)
			   being each evaluation-structure-pair of new-cell-element
		       with new-expression-value = nil
		       with new-eval-attrs = nil
		       with new-formats = nil
		       do 
		   (case new-feature-name
		     (expression
		      (setf new-expression-value new-feature-value))
		     (cell-evaluation-attributes
		      (setf new-eval-attrs new-feature-value))
		     (cell-format
		      (setf new-formats new-feature-value))
		     (t  ;; ignore the rest, including display-value (for now)
		      nil))
		       finally
			 (when new-expression-value
			   (let* ((result?
				    (handle-cell-expression
				      current-annotated-frame
				      current-cell
				      new-expression-value
				      new-eval-attrs))
				  (local-error-string?
				    (when result?
				      (tformat-text-string
					"Error in the expression for cell (~a, ~a): ~s: ~a"
					i j new-expression-value result?))))
			     (when local-error-string?
			       (setq error-string?
				     (combine-and-reclaim-error-strings
				       error-string?
				       local-error-string?)))))
			 (when new-formats
			   (loop for (new-format-name . new-format-value)
				     being each evaluation-structure-pair of new-formats
				 do
			     (cond ((symbolp new-format-value)
				    (set-simple-part-feature
				      current-cell
				      new-format-name
				      new-format-value))
				   (t
				    (let* ((expression
					     (evaluation-structure-slot new-format-value 'expression))
					   (adjusted-format-value?
					     (remove-evaluation-structure-attribute new-format-value
										    'current-value))
					   (value-for-expression? (or adjusted-format-value?
								      new-format-value)))
				      (when (=f (evaluation-structure-length value-for-expression?) 1)
					(setq value-for-expression? nil))
				      (multiple-value-bind (compiled-cell-expression-or-bad-phrase new-error-string?)
					  (create-compiled-cell-expression expression
									   value-for-expression?
									   '(or symbol (unknown-datum) (obsolete-datum)))
					(when adjusted-format-value?
					  (reclaim-evaluation-structure adjusted-format-value?))
					(cond ((eq compiled-cell-expression-or-bad-phrase bad-phrase)
					       (setq error-string?
						     (combine-and-reclaim-error-strings
						       error-string?
						       (if new-error-string?
							   new-error-string?
							   (tformat-text-string "Bad expression in ~S~%"
										expression)))))
					      (t
					       (setq compiled-cell-expression-or-bad-phrase
						     (prog1
							 (nconc
							   (car compiled-cell-expression-or-bad-phrase)
							   (slot-value-list 'expression-source-text
									    (cdr compiled-cell-expression-or-bad-phrase)))
						       (reclaim-slot-value-cons compiled-cell-expression-or-bad-phrase)))
					       (change-annotation
					        current-annotated-frame
					        current-cell
					        new-format-name
					        'cell-expression
					        nil
					        compiled-cell-expression-or-bad-phrase)))))))))))
	   finally
	     (return error-string?))))

(defun-simple combine-and-reclaim-error-strings (old-string? new-string)
  (if old-string?
      (prog1
	  (tformat-text-string
	    "~a~%~a~%"
	    old-string? new-string)
	(reclaim-text-string new-string)
	(reclaim-text-string old-string?))
      new-string))

;;; `table-cells-getter' and `table-cells-setter'

(def-virtual-attribute table-cells
    ((class freeform-table)
     (sequence
      (sequence
       (or
	(member none)  ;; really "the symbol none", not no-value!
	(structure
	 ((expression text)
	  (cell-display-value datum)
	  (cell-display-text text)
	  (cell-format
	   (structure 
	    ((background-color (or symbol
				   (structure
				    ((expression text)
				     (priority (member 1 2 3 4 5 6 7 8 9 10))
				     (current-value symbol)
				     (scan-interval number)
				     (initial-scan-wait-interval number)
				     (value-domain (member inference-engine g2-simulator))
				     (update-only-when-shown truth-value)
				     (tracing-and-breakpoints
				      (structure
				       ((warning-message-level (member 0 1 2 3))
					(tracing-message-level (member 0 1 2 3))
					(breakpoint-level (member 0 1 2 3)))
				       (or warning-message-level tracing-message-level
					   breakpoint-level)))
				     (time-out-when-requesting-data-seeking integer)
				     (may-request-event-updates truth-value)
				     (may-request-data-seeking truth-value))
				    (and expression))))
	     (border-color symbol)
	     (text-color symbol)
	     (text-alignment (member left center right))
	     (text-size (member small large extra-large)))
	    (or background-color border-color text-color
		text-alignment text-size)))
	  (cell-evaluation-attributes
	   (structure
	    ((priority (member 1 2 3 4 5 6 7 8 9 10))
	     (scan-interval number)
	     (initial-scan-wait-interval number)
	     (value-domain (member inference-engine g2-simulator))
	     (update-only-when-shown truth-value)
	     (tracing-and-breakpoints
	      (structure
	       ((warning-message-level (member 0 1 2 3))
		(tracing-message-level (member 0 1 2 3))
		(breakpoint-level (member 0 1 2 3)))
	       (or warning-message-level tracing-message-level
		   breakpoint-level)))
	     (time-out-when-requesting-data-seeking integer)
	     (may-request-event-updates truth-value)
	     (may-request-data-seeking truth-value))
	    (or priority scan-interval initial-scan-wait-interval
		value-domain update-only-when-shown tracing-and-breakpoints
		time-out-when-requesting-data-seeking
		may-request-event-updates may-request-data-seeking))))
	 (or expression cell-display-value cell-format
	     cell-evaluation-attributes)))
       1)
      1)
     ())
  :event-updates nil
  :initial
  ((class) (declare (ignore class)) nil)
  :getter
  ((freeform-table)
   (let ((table-part
	  (cell-annotations freeform-table)))
     (loop with row-parts = (cadr (get-simple-part-feature table-part 'subparts))
	   for row-part in row-parts
	   collect
	   (make-sequence-of-freeform-table-row freeform-table row-part)
	     into row-eval-list
	     using eval-cons
	   finally
	     (return (allocate-evaluation-sequence row-eval-list)))))
  :setter
  ((freeform-table new-value)
   (let* ((length-of-first-row
	   (evaluation-sequence-length
	    (evaluation-sequence-aref new-value 0)))
	  (rectangular-p 
	   (loop for row being each evaluation-sequence-element of new-value
		 as length-of-nth-row = (evaluation-sequence-length row)
		 always (eq length-of-first-row length-of-nth-row))))
     (cond (rectangular-p
	    (with-named-dynamic-extent working-on-annotated-frame
		((current-annotated-frame freeform-table)
		 (current-block-of-dependent-frame freeform-table)
		 (*current-computation-frame* freeform-table))
					; Make new cell-annotations.
	      (let ((old-row-annotations
		     (row-annotations current-annotated-frame))
		    (old-column-annotations
		     (column-annotations current-annotated-frame))
		    (old-cell-annotations
		     (cell-annotations current-annotated-frame))
		    (new-row-maximum
		     (evaluation-sequence-length new-value))
		    (new-column-maximum
		     (evaluation-sequence-length (evaluation-sequence-aref new-value 0))))
		(erase-entire-annotated-block current-annotated-frame)
		(setf (row-annotations current-annotated-frame)
		      (make-table-annotation 'row new-row-maximum 1))
		(setf (column-annotations current-annotated-frame)
		      (make-table-annotation 'column 1 new-column-maximum))
		(setf (cell-annotations current-annotated-frame)
		      (make-table-annotation 'cell new-row-maximum new-column-maximum))
		(reclaim-part-description old-row-annotations)
		(reclaim-part-description old-column-annotations)
		(reclaim-part-description old-cell-annotations)	  
		(update-representations-of-slot-value current-annotated-frame 'cell-annotations)
		(update-representations-of-slot-value current-annotated-frame 'row-annotations)
		(update-representations-of-slot-value current-annotated-frame 'column-annotations)
		(with-named-dynamic-extent working-on-new-table ()
		  (update-new-table-size))
		(funcall-method 'update-frame-status-and-notes current-annotated-frame)
		(redraw-entire-annotated-block)
		(set-the-specified-cell-features new-value))))
	   (t
	    (tformat-text-string
	     "This value does not represent a rectangular grid of cells.  ~
               Please make sure that all the row sequences are the same ~
               length."))))))







;;; The right-edge-of-block and bottom-edge-of-block are dependent
;;; values.  Whenever the height or width of individual rows or columns
;;; is changed, these values are changed.  All the cell insert and delete
;;; operations also modify these values.  The initial values above must
;;; be right given the initial annotations set up below.  When you
;;; change the initial annotations you have to change the initial
;;; values bound by the initialization method.

;;; All three of the annotation slots always contain an annotation of
;;; type new-table.

;;; The 'row-annotations' contains a default row for the entire table,
;;; and a single row part for each of the individual rows that override
;;; that default.

;;; The 'column-annotations' contains a default row for the entire
;;; table, and a single column part for each of the individual rows that
;;; override that default.

;;; The `cell-array' slot holds the set of expressions that are being
;;; displayed in this table.  This slot is a lookup slot so that we can
;;; move the slot up the class hierarchy when more types of frames have
;;; such a slot.


;;; The `initialize' of a new-table is used to set the initial value of the
;;; slots and to initialize the frame notes.  It is, of course, also called when
;;; the frame is cloned; in which case it does not tinker with the cloned
;;; values.

(def-class-method initialize (new-table)
  (funcall-superior-method new-table)
  (let ((cloning? (consp (row-annotations new-table))))
    (unless cloning?
      (let* ((class (class new-table))
	     (class-description (class-description class))
	     (cell-annotations-for-class
	       (slot-init-form
		 (get-slot-description-of-class-description
		   'cell-annotations class-description)))
	     (row-maximum
	       (or (get-simple-part-feature
		     cell-annotations-for-class 'row-maximum)
		   4))
	     (column-maximum
	       (or (get-simple-part-feature
		     cell-annotations-for-class 'column-maximum)
		   3))
	     (current-annotated-frame new-table))
	(setf (row-annotations new-table)
	      (make-table-annotation 'row row-maximum 1))
	(setf (column-annotations new-table)
	      (make-table-annotation 'column 1 column-maximum))
	(setf (cell-annotations new-table)
	      (make-table-annotation 'cell row-maximum column-maximum))
	(setf (default-cell-format new-table)
	      (slot-init-form
		(get-slot-description-of-class-description
		  'default-cell-format class-description)))
	(setf (default-evaluation-setting new-table)
	      (slot-init-form
		(get-slot-description-of-class-description
		  'default-evaluation-setting class-description)))
	(initialize-slot-value new-table 'cell-array (make-frame 'g2-cell-array))
	;; Plan A:
	(with-named-dynamic-extent working-on-annotated-frame 
				   ((current-annotated-frame new-table))
	  (with-named-dynamic-extent working-on-new-table ()
	    (update-new-table-size)))
	;; Plan B:
	; (setf (right-edge-of-block new-table) 218)
	; (setf (bottom-edge-of-block new-table) 110)
  	))
;    (assert-consistency-analysis new-table)
    (funcall-method-if-any 'update-frame-status-and-notes new-table)))

;; Plan A is better in the long run, but plan B improves the chances of
;; getting a table we can debug.

;; The initialize-g2-cell-array is done here in the
;; frame-initialization-method since it is extremely unlikely that the
;; frame will not have a cell-array.


;;; This exists in order to bring up to date any charts which still use the old
;;; naming scheme for text-sizes.

(def-class-method initialize-after-reading (new-table)
  (funcall-superior-method new-table)		; needed by convention
  (unless (standardized-part-text-sizes-p)
    (map-over-part-description 'standardize-text-size-feature-in-part-description
			       (cell-annotations new-table))
    (map-over-part-description 'standardize-text-size-feature-in-part-description
			       (default-cell-format new-table))))

;;; GENSYMCID-1502: see-through freeform-table
;;; This post-loading function was used to fix transparent background issue
;;; in old freeform-table

#+ignore ; it looks ugly and dangerous --binghe
(def-post-loading-function fix-background-for-freeform-table
  (loop for ff-table being each class-instance of 'freeform-table doing
    (let* ((cell-annotations (cell-annotations ff-table))
           (default-cell-format
             (car (car (cdr (car (cdr (cdr cell-annotations))))))))
      (setf (car (cdr (cdr default-cell-format))) 'background))))

;;; `Make-table-annotation' is used to allocate a fresh annotation for a table.
;;; Recall there are three such annotations; one that holds the infomation about
;;; each cell, and one each for the rows and collumns.  The row/column annotations
;;; hold a cell for each row or column that records the default information 
;;; for a cell in that row or column.

;;; Make-table-annotation's first parameter states which kind of annotation is
;;; desired it is one of the three symbols: cell, row, column.

(defun make-table-annotation (which-kind row-count column-count)
  (let* ((rowwise-p (memq which-kind '(cell row)))
	 (columnwise-p (memq which-kind '(cell column)))
	 (row-maximum (if rowwise-p row-count 1))
	 (column-maximum (if columnwise-p column-count 1))
	 (prototype-cell
	   (case which-kind
	     (row    (slot-value-list 'cell 'row-height   (make-slot-value-float-macro  25.0D0)))
	     (column (slot-value-list 'cell 'column-width (make-slot-value-float-macro  70.0D0)))
	     (cell   (copy-for-slot-value '(cell)))))
	 (result
	   (slot-value-list
	     'new-table
	     'row-maximum row-maximum
	     'column-maximum column-maximum
	     'subparts
	     (slot-value-list
	       'row
	       (loop for row-index from 1 upto row-maximum
		     collect
		       (slot-value-list
			 'row
			 'subparts
			 (slot-value-list
			   'cell
			   (loop for column-index from 1 to column-maximum
				 collect (copy-for-slot-value prototype-cell) using slot-value-cons)))
				      using slot-value-cons)))))
    (when (eq which-kind 'cell)
      (let ((fragment-with-default-for-all-cells
	      (copy-for-slot-value
		'(subpart-defaults
		   (cell
		     ((cell background-color background
			    border-color foreground
			    text-value ("")
			    highlighted? nil
			    width 70
			    height 25
			    )))))))
	;; Splice it into the result
	(setf
	  (cdr (last fragment-with-default-for-all-cells))
	  (cdr result))
	(setf 
	  (cdr result)
	  fragment-with-default-for-all-cells)))
    (reclaim-slot-value prototype-cell)
    result))







;;;; Frame Notes And Consistency For New Tables




;;; The frame notes and status of a new table is largely maintained by
;;; the compilation of individual expressions in the table.

(def-class-method update-frame-status-and-notes (new-table)
  (declare (ignore new-table))
  ;; New Tables have no frame notes that are global to the entire table.
  ;; For example "This table is ugly"
  )






;;;; Updating Frames Upon Cell Cache Changes.




;;; There are three paths that cause a frame to change how it is
;;; displayed.  Slots in the frame may change.  Annotations in the frame
;;; may change.  Cached values in the frame's cell array may change.

;;; Changes to the cell array cache are propagated by `cell-updated',
;;; which is called from the methods that are used to notify a frame of
;;; a change to the cell.  Only `Expression-cell-updated' is currently
;;; implemented.

(defun-simple export-cell-attribute-name (cell-part-name)
  (case cell-part-name
    (cell-contents 'cell-display-text)
    (background-color 'background-color))
  ;; 'cell-format ->background-color->current-value
  )

(def-class-method expression-cell-updated
		  (new-table g2-cell-array cell-index old-value? new-value?)
  (declare (ignore g2-cell-array))
  (let ((cell-updated?
	  (cell-updated
	    new-table
	    cell-index
	    old-value?
	    new-value?))
	cell-text?
	cell-attribute-name
	new-value)
    (when g2-has-v5-mode-windows-p
      (unless (and (evaluation-value-p old-value?)
		   (evaluation-value-p new-value?)
		   (evaluation-value-eql old-value? new-value?))	
	(send-ws-representations-item-change-macro
	  new-table
	  (multiple-value-bind (cell-X cell-Y cell cell-part)
	      (expression-cell-index-to-cell-coordinates cell-index new-table t)
	    (when (and cell-X cell-Y cell cell-part)
	      (setq cell-attribute-name (export-cell-attribute-name cell-part))
	      (setq new-value
		    (case cell-attribute-name
		      (background-color
		       new-value?)
		      (cell-display-text
		       (setq cell-text? (get-simple-part-feature cell 'text-value))
		       (if cell-text?
			   (convert-text-to-text-string cell-text?)))))
	      (allocate-evaluation-structure-inline
		'attribute-name
		'table-cells
		'row-index cell-X
		'column-index cell-Y
		'cell-attribute-name
		cell-attribute-name
		'new-value
		new-value))))))
    cell-updated?))

(defun expression-cell-index-to-cell-coordinates (index new-table &optional cell-parts-too?)
  (loop with resulting-cell? = nil
	with cell-part-name? = nil
	with resulting-X = nil
	with resulting-Y = nil
	with row-parts
	  = (cadr (get-simple-part-feature
		    (cell-annotations new-table) 'subparts))
	with row-index = 0
	for row-part in row-parts
	as cell-parts = (cadr (get-simple-part-feature row-part 'subparts))
	do
    (loop with column-index = 0
	  for cell-part in cell-parts
	  as bg-color? = (get-simple-part-feature cell-part 'background-color)
	  as bg-color-expression-cell-index? = (and bg-color?
						    (consp bg-color?)
						    (get-simple-part-feature
						      bg-color?
						      'expression-cell-index))
	  as cell-contents? = (get-simple-part-feature cell-part 'cell-contents)
	  as compiled-cell-expression? = (and cell-contents?
					      (car cell-contents?))
	  as expression-cell-index?
	     = (and compiled-cell-expression?
		    (eq (car compiled-cell-expression?) 'compiled-cell-expression)
		    (get-simple-part-feature compiled-cell-expression?
					     'expression-cell-index))
	  as is-bg-p
	     = (and bg-color-expression-cell-index?
		    (=f bg-color-expression-cell-index? index))
	  as is-cell-contents-p
	     = (and expression-cell-index?
		    (=f expression-cell-index? index))
	  
	  do
      (when (or is-bg-p is-cell-contents-p)
	(setq resulting-X row-index)
	(setq resulting-Y column-index)
	(when cell-parts-too?
	  (setq cell-part-name? (if is-bg-p 'background-color 'cell-contents))
	  (setq resulting-cell? cell-part))
	(return))
      (incff column-index))
    (when resulting-X
      (return (values resulting-X resulting-Y resulting-cell? cell-part-name?)))		      
    (incff row-index)))

;;; These special variables are used to hold the state necessary for postponing the erase of a
;;; new-table cell until its redraw, cf.  the comment in `cell-updated' below.

(defvar postpone-cell-erase-until-redraw-p nil)
(defvar background-color-value-from-postponed-erase nil)
(defvar text-value-from-postponed-erase nil)
(defvar reclaim-text-value-from-postponed-erase-p nil)
(defvar updated-only? nil)

;;; Note that color-values are window-specific. This means that we have to save both the color-value
;;; *and* its associated window in the erase pass of cell-updated. There was previously a bug in 3.0 rev 0-2
;;; due to only a single background color value being saved. This was causing turding when there were TWs
;;; displaying a freeform table and the TW was on a window with a different color map than the G2 (for
;;; example, a VAX or PC). Now we save the window specific values in an alist.

(defmacro set-background-color-value-from-postponed-erase (new-value)
  `(gensym-push (gensym-cons current-window ,new-value)
		background-color-value-from-postponed-erase))

(defmacro get-background-color-value-from-postponed-erase ()
  '(or (cdr (assoc current-window background-color-value-from-postponed-erase))
       #+development (error "Missing background-color-value-from-postponed-erase for current window.")
       #-development (map-to-color-value 'white)))


(defmacro reclaim-background-color-value-from-postponed-erase ()
  '(when background-color-value-from-postponed-erase
    (reclaim-gensym-tree background-color-value-from-postponed-erase)
    (setq background-color-value-from-postponed-erase nil)))

;;; This certainly violates data abstraction but there appears to be no other way to achieve this
;;; function efficiently.  This function is used only to cache the value of the current text-box-format
;;; in order to postpone an erase of a cell.  todo: move this elsewhere

(defun copy-text-box-format (from to)
  (loop for i from 0 below (array-dimension from 0)
	do (setf (svref to i) (svref from i))))

(defun cell-updated (new-table cell-index old-value? new-value?)
  (if (drawing-in-paint-mode-p drawing-parameters)
      (cell-updated-in-paint-mode new-table cell-index old-value? new-value?)

  (let ((projection-focus-method 'cell)
	(projection-focus-cell-index cell-index))

    ;; In order to eliminate `update flashing' of the cell between the erase and
    ;; redraw, we postpone the erase of the cell background and text until the
    ;; last possible moment in the redraw.  Otherwise, if you let the background
    ;; erase occur in the first erase pass (via erase-entire-annotated-block),
    ;; the first pass would erase to the parent background color then the redraw
    ;; pass would later redraw in the new desired background color, with a
    ;; significant time lag between the two passes.  The cycle between 3 colors
    ;; and the time lag would cause an annoying visual `flash'.  todo: It would
    ;; also be worthwhile looking into how readout displays manage to do their
    ;; updating so smoothly.  A superficial perusal of the code seems to
    ;; indicate that they set up the clipping rectangles so that they only need
    ;; to redraw the part (tail?) of the string that's changed.  If we could use
    ;; the same incremental approach our updating would be more efficient.
    
    ;; If new-value? is null then we are being called because the table is being
    ;; disabled. In this case only, we do not want to postpone the erase. Hence
    ;; the value (not (null new-value?)) below.
    
    (let ((postpone-cell-erase-until-redraw-p (not (null new-value?)))
	  (background-color-value-from-postponed-erase ())
	  (text-value-from-postponed-erase nil)
	  (reclaim-text-value-from-postponed-erase-p nil)
	  (updated-only? t))
            
      (let ((expression-cell
	      (managed-svref
		(g2-cell-array-managed-array
		  (cell-array new-table))
		cell-index)))

	(setf (g2-expression-cell-cached-value expression-cell) old-value?)
	(erase-entire-annotated-block new-table)
	(setf (g2-expression-cell-cached-value expression-cell) new-value?))

      (let ((projection-focus-cell-new-cached-value new-value?))
	(funcall-method 'update-part-dependencies new-table 'cell cell-index))
      
      ;; Note that because of our bindings above, the erase of the cell is
      ;; postponed until the redraw.
      (redraw-entire-annotated-block)

      (when (and reclaim-text-value-from-postponed-erase-p
		 text-value-from-postponed-erase)
	(reclaim-slot-value text-value-from-postponed-erase))

      (reclaim-background-color-value-from-postponed-erase)))))

;; Looks like the update method should of set the new cache value.


(def-system-variable off-window-color-map new-tables
  (:funcall initialize-off-window-color-map))

(defun initialize-off-window-color-map ()
  (make-color-map 8
    (make-monochrome-color-description-plist 1 0)))

(defmacro with-simulated-on-image-plane (&body body)
  `(with-null-drawing-transform
     (let ((current-background-color-value 0)
	   (current-foreground-color-value 0)
	   (current-color-map off-window-color-map))
       ,@body)))


(defun cell-updated-in-paint-mode (new-table cell-index old-value? new-value?)
  (declare (ignore old-value?)) ;; Is this right?

  ;; Set the cell in the cell array.
  (let ((expression-cell (managed-svref
			   (g2-cell-array-managed-array
			     (cell-array new-table))
			   cell-index)))
    (setf (g2-expression-cell-cached-value expression-cell) new-value?))

  ;; Update the "display list"
  (let ((projection-focus-method 'cell)
	(projection-focus-cell-index cell-index)
	(projection-focus-cell-new-cached-value new-value?))
    (funcall-method 'update-part-dependencies new-table 'cell cell-index))
  
  ;; Project an inval for each image of the table.
  (let ((workspace? (get-workspace-if-any new-table)))
    (when workspace?
      (with-deferred-drawing-in-process ()
	(with-named-dynamic-extent working-on-annotated-frame ((current-annotated-frame new-table))
	  (with-named-dynamic-extent projection-drawing ((projection-mode 'invalidate-projection-mode))
	    (with-simulated-on-image-plane
	      (let ((projection-focus-method 'cell)
		    (projection-focus-cell-index cell-index)
		    (current-kind-of-change 'cell)
		    (current-thing-changed cell-index))
		(project-new-table)))))))))

;; Note that this does the invalidate in workspace coordinates.






;;;; Denote-component-of-block Method For New Tables







;;; `Denote-cell-array-element' method on a new-table is a good example of
;;; how cell array elements are mapped back into the topology of the
;;; a complex block.  We must search in table to find the use of the
;;; cell index and then create a denotation for place in the table.

;;; This happens by converting the cell component particulars into an
;;; alternate set of component particulars that denote the where the
;;; expression found in that cell is used in the table.  For example
;;;   (cell-array-element 2) 
;;; might be converted into
;;;   (get-simple-part-feature 
;;;     (get-subpart 'row 3 (get-subpart 'column 2 *current-computation-frame*))
;;;     'background-color)
;;; and then we call denote-component-of-block on this alternate description
;;; of where the cell resides.

;;; Converting the given component particulars into the alternate component particulars
;;; is done by projecting the table focused on the cell array element.  By projecting
;;; in compute path of focus mode we create a description of how to reach that element
;;; in the table.  Projecting in that mode (aka compute-path-of-focus-projection-mode)
;;; causes us to accumulate a path that looks like so:
;;;    ((get-simple-part-feature it 'background-color)
;;;     (get-subpart-of-collection it 'subparts 'cell <column-index>)
;;;     (get-subpart-of-collection it 'subparts 'row  <row-index>)
;;;	(part-description-of-frame 'cell-annotations it))
;;; This path is then converted into the component particulars by using convert-path-to-expression.

(def-class-method place-reference-of-cell (new-table cell-index)
  (with-named-dynamic-extent working-on-annotated-frame 
			     ((current-annotated-frame new-table))
    (with-named-dynamic-extent projection-computing-path-of-focus
			       ((projection-mode 'compute-path-of-focus-projection-mode)
				(projection-focus-method 'cell)
				(projection-focus-cell-index cell-index)
				(projection-focus-path nil))
      (with-simulated-on-image-plane
	(project-new-table))
      (let ((component-accessor (convert-path-to-expression 
				  projection-focus-path
				  '*current-computation-frame*)))
	(make-evaluation-place-reference-to-place 
	  component-accessor
	  new-table)))))


(def-class-method denote-cell-array-element (new-table cell-index include-denotation-for-block)
  (cond
    ((eql cell-index cell-index-currently-being-registered)
     (twrite-string "the expression-being-compiled")
     (denote-component-of-block-1 '*current-computation-frame* " of "))
    (t
     (let* ((place-reference (funcall-method 'place-reference-of-cell new-table cell-index))
	    (component-accessor (evaluation-place-reference-component-particulars 
				  place-reference)))
       (denote-component-of-block include-denotation-for-block component-accessor)
       (reclaim-evaluation-place-reference place-reference)))))



(def-class-method recompile-expression-at-component-particulars (new-table component-particulars)
  (when (consp (third component-particulars)) ;; Note A!
    (gensym-dstruct-bind ((nil parent-component-particulars (nil part-feature)) component-particulars)
;    (let ((denotation (twith-output-to-text-string (denote-component-of-block t component-particulars new-table))))
;      (format t "~%Recompiling: ~A" denotation)
;      (reclaim-text-string denotation)
;      ; (cerror "Go" "Stop")
;      )
      (let* ((*current-computation-frame* 
	       new-table)
	     (parent-part-description
	       (simple-eval parent-component-particulars)))
	(cond
	  ((and parent-part-description
		(get-simple-part-feature parent-part-description part-feature))
	   (with-named-dynamic-extent working-on-annotated-frame 
	       ((current-annotated-frame new-table))
	     (let ((current-block-of-dependent-frame new-table))
	       (with-named-dynamic-extent working-on-new-table
		   ((current-annotated-frame new-table))
		 (case part-feature
		   (cell-contents
		    (recompile-component-of-part-description 
		      parent-part-description
		      part-feature
		      'cell-expression-and-text))
		   (background-color
		    (recompile-component-of-part-description 
		      parent-part-description
		      t
		      'cell-format))
		   (t
		    #+development
		    (error "Attempted to compile unknown part-feature ~S" part-feature)))))))
	  (t
	   #+development
	   (error "Missing expression where denotation said I'd find one.")))))))

;; Note A: Patch for hq-451275.  If the component particulars are
;; malformed then skip the recompilation.  Note this was seen in a KB from
;; Anchor Glass, in that KB cells at index 1 appeared with the cell's type
;; set to EMPTY-EXPRESSION-CELL, meanwhile index 1 never appeared -
;; otherwise -in the table as a cell index.  I was unable to find any
;; operation to generate such a bogus state. It appeared as if they cloned
;; the table to create many instances.



;;; `convert-path-to-expression' takes a path to a component, along
;;; with a root from which that path begins and converts it into 
;;; an expression that reach that component.  For example:
;;;    (convert-path-to-expression '((f it) (g it 1) (h 'row it)) 'y)
;;;  -->
;;;    (f (g (h 'row y) 1))
;;; The special token IT  is used to mark the place in the steps of
;;; the path where the nested step should appear.  The path is 
;;; read from left to right, as if it were accumulated using push
;;; as a scan reached down into the subcomponent.
;;; The conses which make up the path are modified to create the
;;; new expression.

(defun convert-path-to-expression (path root)
  (loop with result = root
	with reversed-path = (nreverse path)
	for step in reversed-path
	do (loop for p on step
		 when (eq 'it (car p))
		   do (setf (car p) result))
	   (setf result step)
	finally
	  (reclaim-slot-value-list reversed-path)
	  (return result)))









;;;; Draw and Focused Update Methods For New Tables


;;; The draw method for new-table is called to draw the table from scratch.

;;; It sets up a projection dynamic extent, in drawing mode with no focus.

(def-class-method draw (new-table)
  (with-named-dynamic-extent working-on-annotated-frame ((current-annotated-frame new-table))
    (with-named-dynamic-extent projection-drawing ((projection-mode 'draw-projection-mode))
      (project-new-table))))



;;; There are two "update" methods provide to do the drawing associated
;;; with changing component parts of the structure of a table.  One for
;;; redrawing when cached cell values change, and one for redrawing when
;;; annotations are changed.  These methods establish dynamic extents
;;; and then call update-images-of-block.

;;; If information is stored in the frame which is derived from these
;;; data structures then old data should be reclaimed and new data
;;; computed when these routines are called with erase-instead?  bound
;;; to nil.



;;; `Update-subparts-effected-by-this-annotation' is called upon
;;; updating the new-table's rendering in response to changes in its
;;; format or data this routine is called, first to erase the table, and
;;; second to redraw the table after the change has been comited.

;;; It calls update-images-of-block, which will establish a projection
;;; dynamic-extent, in drawing mode.  It begins to establish that extent
;;; by binding the focus on the annotation that is being changed.

;(def-class-method update-subparts-effected-by-this-annotation (new-table annotation)
;  (let ((projection-focus-method 'annotation)
;	(projection-focus-annotation annotation))
;    (update-images-of-block new-table erase-instead? t)))




;;; 'Update-subparts-effected-by-cell' is called upon updating a
;;; new-table in response to changing the value stored in the cache for
;;; a single cell of the frame's cell-array.

;;; It establishes a projection dynamic-extent, in drawing mode, with
;;; the focus on the cell that is being changed.

;(def-class-method update-subparts-effected-by-cell (new-table cell-index simulated-cache-value)
;  (let ((projection-focus-method 'cell)
;	(projection-focus-cell-index cell-index)
;	(projection-focus-cell-new-cached-value simulated-cache-value))
;  (update-images-of-block new-table erase-instead? t)))







;;;; Mouse Tracking For New Tables




;;; Track-mouse-for-new table projects the table in projection-tracking
;;; mode, this causes project-new-table to return the cell the mouse is
;;; over.

(defun track-mouse-for-new-table (x-in-window y-in-window get-subpart-p)
  (assert-that-within-named-dynamic-extent 'working-on-annotated-frame)
  (let (row column subpart-description?)
    (with-named-dynamic-extent projection-tracking
				   ((projection-mode 'tracking-projection-mode)
				    (current-tracking-x-in-window x-in-window)
				    (current-tracking-y-in-window y-in-window)
				    (create-subpart-upon-tracking-p get-subpart-p)
				    (current-tracking-subcomponent (slot-value-list nil nil nil)))
	  (project-new-table)
	  (setf row 		      (first current-tracking-subcomponent))
	  (setf column 		     (second current-tracking-subcomponent))
	  (setf subpart-description?  (third current-tracking-subcomponent))
	  (reclaim-slot-value-list current-tracking-subcomponent))
    (values current-annotated-frame row column subpart-description?)))


(def-spot new-table-spot
    :slots ()
    :type-of-frame-represented new-table
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type t
    :include spot)

(def-spot new-table-cell-spot
    :slots (row-index-of-new-table?
	     column-index-of-new-table?
	     subpart-of-new-table?)
    :include new-table-spot
    :abstract-type nil)

(def-spot new-table-background-spot
    :slots ()
    :include new-table-spot
    :abstract-type nil)


;;; The class-method `generate-spot' pushes a new-table-spot.

(def-class-method generate-spot (new-table mouse-pointer)
  (let ((image-plane (image-plane-of-mouse-pointer mouse-pointer)))
    (with-nested-draw-area? ((left-edge-of-workspace-area-within-pane image-plane)
			     (top-edge-of-workspace-area-within-pane image-plane)
			     (right-edge-of-workspace-area-within-pane image-plane)
			     (bottom-edge-of-workspace-area-within-pane image-plane)
			     image-plane :interior)
      (on-image-plane-without-drawing (image-plane)
	(with-named-dynamic-extent working-on-annotated-frame
	    ((current-annotated-frame new-table))
	  (with-named-dynamic-extent working-on-new-table ()
	    (multiple-value-bind (ignored-value row? column? subpart-description?)
		(track-mouse-for-new-table
		  (x-of-mouse-pointer mouse-pointer)
		  (y-of-mouse-pointer mouse-pointer)
		  t)
	      (declare (ignore ignored-value))
	      (push-last-spot
		mouse-pointer
		(cond
		  ((and row? column?)
		   (let ((new-table-spot (make-new-table-cell-spot)))
		     (setf (row-index-of-new-table?  new-table-spot) row?)
		     (setf (column-index-of-new-table? new-table-spot) column?)
		     (setf (subpart-of-new-table? new-table-spot) subpart-description?)
		     new-table-spot))
		  (t
		   (make-new-table-background-spot)))
		new-table))))))))






;;;; Updating Block Size For New Table




;;; update-part-dependencies

(def-class-method update-part-dependencies (new-table kind-of-change what-changed)
  (with-named-dynamic-extent working-on-annotated-frame 
			     ((current-annotated-frame new-table))
    (with-named-dynamic-extent projection-update-dependencies
			       ((projection-mode 'update-dependencies)
				(current-kind-of-change kind-of-change)
				(current-thing-changed what-changed))
      (with-simulated-on-image-plane
	(project-new-table)))))
      
;;; The overall size of a table is the sum of the widths and heights of
;;; its various cells and borders.  This overall size is computed by
;;; scanning the table, as if drawing, and then storing the resulting
;;; totals into the block's rectangle.  Projection-mode is bound to
;;; accumulating-size-projection-mode when in this mode.

(def-named-dynamic-extent projection-of-new-table-accumulating-size
  (module new-tables)
  (includes projection-update-dependencies))

(defvar-of-named-dynamic-extent maximum-width projection-of-new-table-accumulating-size)
(defvar-of-named-dynamic-extent maximum-height projection-of-new-table-accumulating-size)

;;; `Update-new-table-size' changes the lower right corner of the block
;;; so that it exactly matchs the actual size of the table as implied by
;;; all the little bits which make up the table  This must be called when
;;; the block is erased.

(defun update-new-table-size ()
  (assert-that-within-named-dynamic-extent 'working-on-new-table)
  (let ((maximum-width 0)
	(maximum-height 0))
    (funcall-method 'update-part-dependencies current-annotated-frame 'size nil)
    (let ((new-right-edge-of-block (+r (left-edge-of-block current-annotated-frame) maximum-width))
	  (new-bottom-edge-of-block (+r (top-edge-of-block current-annotated-frame) maximum-height)))
      (unless (and (=r (right-edge-of-block current-annotated-frame) new-right-edge-of-block)
		   (=r (bottom-edge-of-block current-annotated-frame) new-bottom-edge-of-block))
							    ; (erase-images-of-block current-annotated-frame T)
	(change-edges-of-block current-annotated-frame nil nil
			       new-right-edge-of-block
			       new-bottom-edge-of-block)
	(enlarge-workspace-for-block-rectangle-if-necessary current-annotated-frame nil)
							    ; (draw-images-of-block current-annotated-frame t)
	))))







;;;; Activation Methods For New Table




(def-class-method activate (new-table)
  (let ((current-block-of-dependent-frame new-table))
    (unless in-suspend-resume-p
      (activate-g2-cell-array (cell-array new-table)))
    (funcall-superior-method new-table)))

(def-class-method deactivate (new-table)
  (let ((current-block-of-dependent-frame new-table))
    (unless in-suspend-resume-p
      (deactivate-g2-cell-array (cell-array new-table)))
    (funcall-superior-method new-table)))







;;;; Projection Routine For New Table 




;;; `Project-new-table' is used to sweep over the table in drawing order.
;;; It may be invoked in either a project-tracking, or a project-drawing
;;; dynamic extent.

;;; When tracking it leaves the row and cell in
;;; current-tracking-subcomponent that is implied by the
;;; current-tracking-x-in-window and current-tracking-y-in-window.

;;; When drawing it will render the chart into the current image plane.

;;; The projection-focus-mode maybe bound to either NIL, CELL, or
;;; ANNOTATION.  When NIL the entire table is scanned.  When CELL or
;;; ANNOTATION, only those parts of the table effected by the
;;; cell or annotation in question are scanned.

(defun project-new-table () ;; Note 5.
  (assert-that-within-named-dynamic-extent 'working-on-annotated-frame)
  (assert-that-within-named-dynamic-extent 'projection)
  #+development
  (unless (memq projection-mode '(update-dependencies
				  invalidate-projection-mode
				  denote-projection-mode
				  compute-path-of-focus-projection-mode
				  cleanup-projection-mode
				  funcall-on-focus-projection-mode))
    (assert-that-within-named-dynamic-extent 'for-image-plane))
  #+development
  (when (eq projection-mode 'draw-projection-mode)
    (assert-that-within-named-dynamic-extent 'on-window-with-drawing))

  (let ((*current-computation-frame* current-annotated-frame)
	(current-computation-style the-only-dynamic-computation-style)
	(current-block-of-dependent-frame current-annotated-frame)
	(current-text-box-format (get-or-make-format-frame 'dynamic-text-cell-format))
	(current-text-cell-plist '())
	(focus-just-happened? nil)
	(cell-annotations (cell-annotations current-annotated-frame))
	(default-cell-format (default-cell-format current-annotated-frame)))

    (macrolet
	((do-funcall-on-new-focus-if-necessary ()
	   `(when focus-just-happened?
	      (setf focus-just-happened? nil)
	      (funcall current-projection-function-for-funcall 'enter-focus)))

	 ;; You're not allowed to change the bg color unless drawing.
	 (with-background-color-maybe ((color-value) &body body)
	   `(with-background-color-value (if (eq projection-mode 'draw-projection-mode)
					     ,color-value
					     current-background-color-value)
	      ,@body))
	 (coerce-slot-value-number-to-fixnum (x)
	   `(if (fixnump ,x) ,x (truncate (slot-value-number-value ,x)))))

      (with-named-dynamic-extent scanning-subparts-of-block
	  ((part-feature-recall-stack nil)
	   (stack-of-current-part-descriptions nil)
	   (maintain-stack-of-current-part-descriptions-p t))
	(with-part-descriptions ((get-default-computation-style-of-class)
				 (get-default-formatted-part-of-class)
				 cell-annotations
				 (or default-cell-format '(cell)))
	  (let* ((dragging?
		   (block-is-currently-being-dragged-p current-annotated-frame))
		 (block-background-color
		   (if dragging?
		       'transparent
		       (text-cell-background-color? current-text-box-format)))
		 (block-background-color-value
		   (map-color-or-metacolor-to-color-value block-background-color))
		 (block-background-color-value-color-difference
		   (color-difference
		     block-background-color-value current-background-color-value))
		 (original-background-color-value current-background-color-value))

	    (with-background-color-maybe (block-background-color-value) ;; see note 1.
	      ;; DO rows, but first frame state, draw frame & background
	      (loop
		with wrapup-scan-flag = nil
		with focus-enabled? 
		  = (setq focus-just-happened?
			  (case projection-focus-method
			    ((nil) t)
			    (cell nil)
			    (annotation (and (eq projection-focus-annotation
						 default-cell-format)))))
		
		;; Get the blocks bounds
		with right-edge-of-block = (right-edge-of-block current-annotated-frame)
		with top-edge-of-block = (top-edge-of-block current-annotated-frame)
		with left-edge-of-block = (left-edge-of-block current-annotated-frame)
		with bottom-edge-of-block = (bottom-edge-of-block current-annotated-frame)

		with right-edge-of-block-in-window = (x-in-window right-edge-of-block)
		with top-edge-of-block-in-window = (y-in-window top-edge-of-block)
		with left-edge-of-block-in-window = (x-in-window left-edge-of-block)
		with bottom-edge-of-block-in-window = (y-in-window bottom-edge-of-block)

		with suppress-details? = (or (scale-too-small-for-details-p
					       current-image-x-scale current-image-y-scale)
					     dragging?)
		
		with border-color = (if suppress-details?
					(or (text-cell-line-color? current-text-box-format)
					    'black)
					(text-box-border-color? current-text-box-format))
		with border-color-difference = (color-difference
						 (map-color-or-metacolor-to-color-value border-color)
						 current-background-color-value)
		
		;; These are the default borders for the entire chart.
		with row-border-height = 2
		with row-border-height-in-window = (if suppress-details? 1
						       (maxr 1 (delta-y-in-window
								 row-border-height current-image-y-scale)))
		with bottom-of-upper-row-border-in-window ;; rebound in loop
		  = (+r top-edge-of-block-in-window row-border-height-in-window)
		
		with column-border-width = 2
		with column-border-width-in-window 
		  = (if suppress-details? 1
			(maxr 1 (delta-x-in-window
				  column-border-width current-image-x-scale)))
		with right-edge-of-first-column-border-in-window
		  = (+r left-edge-of-block-in-window column-border-width-in-window)
		
		;; Row and column defaults.
		with ((nil nil (nil column-default-subpart-descriptions))) ;; Note 2.
		  = (get-subpart-collection (column-annotations current-annotated-frame) 'subparts 'row)
		with row-annotations = (row-annotations current-annotated-frame)

		with top-edge-of-row ; updated at end of loop body
		  = (+w top-edge-of-block row-border-height)
		
		;; Draw the background and the first borders (first row's top
		;; and first column's right border)
		initially
		  (case projection-mode

		    (draw-projection-mode
		     (when focus-enabled?
		       ;; Table's Background	; See note 1.
		       (unless (eq 'transparent block-background-color)
			 (with-background-color-value
			     original-background-color-value
			   (draw-solid-rectangle left-edge-of-block-in-window top-edge-of-block-in-window
						 right-edge-of-block-in-window bottom-edge-of-block-in-window
						 block-background-color-value-color-difference)))
		       ;; First row's top border
		       (draw-solid-rectangle left-edge-of-block-in-window top-edge-of-block-in-window
					     right-edge-of-block-in-window bottom-of-upper-row-border-in-window
					     border-color-difference)
		       ;; First column's right border
		       (draw-solid-rectangle left-edge-of-block-in-window bottom-of-upper-row-border-in-window
					     right-edge-of-first-column-border-in-window bottom-edge-of-block-in-window
					     border-color-difference)))

		    (compute-path-of-focus-projection-mode
		     ;; Push the principle source of parts
		     (slot-value-push (slot-value-list 'part-description-of-frame (slot-value-list 'quote 'cell-annotations) 'it)
				      projection-focus-path)
		     ;; Push a generic row accessor to the focus path; the
		     ;; row-index will be mutated below.
		     (slot-value-push (copy-for-slot-value '(get-subpart-of-collection it 'subparts 'row 0))
				      projection-focus-path))

		    (funcall-on-focus-projection-mode
		     (do-funcall-on-new-focus-if-necessary)))
		
		for row-index from 1 upto row-maximum
		as (nil nil (nil cell-subparts-of-this-row))  ;; See note 2.
		   in (get-subpart-collection cell-annotations 'subparts 'row)
		as (nil nil (nil (row-default-cell-subpart)))  ;; See note 2.
		   in (get-subpart-collection row-annotations 'subparts 'row)
		until wrapup-scan-flag do
		
		(with-part-description (row-default-cell-subpart)
		  (let* ((row-height-as-fixnum (coerce-slot-value-number-to-fixnum current-height-of-formatted-part))
			 (bottom-edge-of-row (+w top-edge-of-row row-height-as-fixnum))
			 (top-edge-of-row-in-window (y-in-window top-edge-of-row))
			 (bottom-edge-of-row-in-window (y-in-window bottom-edge-of-row))
			 (bottom-of-lower-row-border-in-window
			   (minr (+r bottom-edge-of-row-in-window
					 row-border-height-in-window)
				     bottom-edge-of-block-in-window)))
		    
		    
		    (when (case projection-mode  ;; Might the focus overlap this row?
			    ((draw-projection-mode 
			       denote-projection-mode
			       compute-path-of-focus-projection-mode
			       cleanup-projection-mode)
			     t)
			    (tracking-projection-mode
			     (<r top-edge-of-row-in-window current-tracking-y-in-window bottom-edge-of-row-in-window))
			    ((update-dependencies invalidate-projection-mode)
			     (case current-kind-of-change
			       (size
				(=f row-index row-maximum))
			       (cell
				(loop for cell-subpart in cell-subparts-of-this-row
				      as cell-contents? = (get-simple-part-feature cell-subpart 'cell-contents)
				      as background-color? = (get-simple-part-feature cell-subpart 'background-color)
				      as computed-feature? = (cond ((compiled-cell-expression-p (car cell-contents?))
								    (car cell-contents?))
								   ((evaluated-computed-part-feature-p background-color?)
								    background-color?)
								   (t nil))
				      thereis (and computed-feature?
						   (=f projection-focus-cell-index
						       (get-simple-part-feature computed-feature? 'expression-cell-index)))))
			       (t t))))
		      
		      (case projection-mode
			(draw-projection-mode
			 (when focus-enabled?
			   ;; Draw the bottom border for this row.
			   (draw-solid-rectangle right-edge-of-first-column-border-in-window bottom-edge-of-row-in-window
						 right-edge-of-block-in-window bottom-of-lower-row-border-in-window
						 border-color-difference)))
			(compute-path-of-focus-projection-mode
			 ;; Update the <row-index> in the current
			 ;; projection-focus-path, which looks like:
			 ;; ((get-subpart-of-collection it 'subparts 'row <row-index>) ...)
			 (setf (fifth (first projection-focus-path)) (1-f row-index))))
		      
		      ;; Project the cells of this row.
		      (loop with left-edge-of-column ; rebound in loop body
			      = (+w left-edge-of-block column-border-width)
			    with right-edge-of-column
			    with right-edge-of-lefthand-column-border-in-window ;; rebound in body.
			      = right-edge-of-first-column-border-in-window

			    
			    initially (when (eq projection-mode 'compute-path-of-focus-projection-mode)
					;; Push a generic column accessor to the focus
					;; path; the column-index will be mutated below.
					(slot-value-push (copy-for-slot-value '(get-subpart-of-collection it 'subparts 'cell 0))
							 projection-focus-path))
			    
			    for column-index from 1 to column-maximum
			    as column-default-cell-subpart
			       in column-default-subpart-descriptions
			    as cell-subpart in cell-subparts-of-this-row
			    until wrapup-scan-flag do

			(with-background-color-maybe (current-background-color-value)
			  (let ((current-foreground-color-value ;; for highlighting
				  current-foreground-color-value))
			    (with-part-descriptions (column-default-cell-subpart
						      cell-subpart)
			      (let* ((column-width-as-fixnum (coerce-slot-value-number-to-fixnum current-width-of-formatted-part))
				     (focus-is-on-cell-contents
				       (case projection-focus-method
					 (cell
					  (and (part-has-feature-p cell-subpart 'cell-contents)
					       (compiled-cell-expression-p 
						 (cell-expression-of-cell-expression-and-text cell-contents))
					       (=f projection-focus-cell-index
						   (get-simple-part-feature 
						     (cell-expression-of-cell-expression-and-text cell-contents)
						     'expression-cell-index))))
					 (annotation
					  (eq projection-focus-annotation cell-subpart))))
				     (focus-matches-this-cell-p
				       (or focus-enabled?
					   (case projection-focus-method
					     (cell
					      (or focus-is-on-cell-contents
						  ;; Has computed background color
						  (let ((background-color-feature-value 
							  (part-has-feature-p cell-subpart 'background-color)))
						    (and background-color-feature-value
							 (evaluated-computed-part-feature-p background-color-feature-value)
							 (=f projection-focus-cell-index
							     (get-simple-part-feature 
							       background-color-feature-value
							       'expression-cell-index))))))
					     (annotation
					      focus-is-on-cell-contents)
					     (otherwise t))))
				     (focus-enabled? ; reconsider the focus 
				       (or focus-enabled?
					   (setq focus-just-happened? focus-matches-this-cell-p))))
				
				(setf right-edge-of-column (+w left-edge-of-column column-width-as-fixnum))
				(let* ((left-edge-of-column-in-window (x-in-window  left-edge-of-column))
				       (right-edge-of-column-in-window (x-in-window right-edge-of-column))
				       (right-edge-of-righthand-column-border-in-window
					 (minr 
					   (+r right-edge-of-column-in-window column-border-width-in-window)
					   right-edge-of-block-in-window)))
				  (when focus-enabled?
				    (case projection-mode
				      (denote-projection-mode
				       (tformat "the value of the cell in column ~D of row ~D" column-index row-index)
				       (setf wrapup-scan-flag t))

				      (compute-path-of-focus-projection-mode
				       ;; Update the <column-index> in the current projection-focus-path, which looks like:
				       ;;   ((get-subpart-of-collection it 'subparts 'cell <column-index>) ...)
				       (setf (fifth (first projection-focus-path)) (1-f column-index))
				       (slot-value-push 
					 (copy-for-slot-value (if focus-is-on-cell-contents
								  '(get-simple-part-feature it 'cell-contents)
								  '(get-simple-part-feature it 'background-color)))
					 projection-focus-path)
				       (setf wrapup-scan-flag t))

				      (tracking-projection-mode
				       (when (<r left-edge-of-column-in-window
						 current-tracking-x-in-window
						 right-edge-of-column-in-window)
					 ;; Communicate current mouse location to `track-mouse-for-new-table'

					 (setf (first current-tracking-subcomponent) row-index)
					 (setf (second current-tracking-subcomponent) column-index)
					 (setf (third  current-tracking-subcomponent) current-part-description)
					 (setf wrapup-scan-flag t)))

				      (update-dependencies
				       ;; Note: if you need this clause to fire on change of attributes other than
				       ;; text-alignment or text-size then you must update the slot-putter
				       ;; reference-to-data-in-frame-containing-annotation in the parts module.
				       ;; Otherwise, said putter skips the update, doing only the erase and redraw.
				       (when (and (memq current-kind-of-change '(cell annotation))
						  (or focus-is-on-cell-contents
						      (eq current-thing-changed default-cell-format)))
					 (cond
					   ((part-has-feature-p cell-subpart 'cell-contents)
					    (let* ((cell-expression 
						     (cell-expression-of-cell-expression-and-text cell-contents))
						   (new-text-value
						     (make-text-for-datum
						       (cond 
							 ((eq projection-focus-method 'cell)
							  projection-focus-cell-new-cached-value)
							 ((simple-cell-expression-p cell-expression)
							  (simple-cell-expression-value cell-expression))
							 (T
							  (get-expression-cell-cache 
							    (cell-array current-annotated-frame)
							    (get-simple-part-feature
							      cell-expression
							      'expression-cell-index))))
						       column-width-as-fixnum)))
					      (cond
						((and postpone-cell-erase-until-redraw-p (not updated-only?))
						 (set-simple-part-feature-without-reclaiming cell-subpart
											     'text-value
											     new-text-value)
						 (setq reclaim-text-value-from-postponed-erase-p t))
						(t
						 (set-simple-part-feature cell-subpart 'text-value new-text-value)))))
					   (t
					    (remove-simple-part-feature cell-subpart 'text-value)))))

				      (draw-projection-mode
				       ;; Draw/Erase the right cell border
				       (unless (eq projection-focus-method 'cell)
					 (draw-solid-rectangle right-edge-of-column-in-window
							       bottom-of-upper-row-border-in-window
							       right-edge-of-righthand-column-border-in-window
							       bottom-edge-of-row-in-window
							       border-color-difference))
				       ;; Highlight means reverse-video, i.e. swap text and background colors
				       (when formatted-part-highlight-flag
					 (rotatef (text-cell-line-color? current-text-box-format)
						  (text-cell-background-color? current-text-box-format)))
				       ;; See note 3 below for why we must cache the background color VALUE at this point
				       (let ((text-cell-background-color-value
					       (map-color-or-metacolor-to-color-value
						 (text-cell-background-color? current-text-box-format))))

					 (let ((current-foreground-color-value
						 (if (text-cell-line-color? current-text-box-format)
						     (map-color-or-metacolor-to-color-value
						       (text-cell-line-color? current-text-box-format))
						     current-foreground-color-value)))
					   (macrolet ((draw-cell-text (text)
							`(let ((supress-text? (or suppress-details?
										   (text-too-small-to-draw-p
										     current-text-box-format
										     nil
										     current-image-x-scale
										     current-image-y-scale))))
							   (unless supress-text?
							     (when (part-has-feature-p cell-subpart 'text-value)
							       (new-draw-text
								 ,text
								 left-edge-of-column-in-window top-edge-of-row-in-window
								 right-edge-of-column-in-window bottom-edge-of-row-in-window))))))
					     ;; Perform any postponed erase of the cell's text if in the Draw pass
					     (when (and postpone-cell-erase-until-redraw-p
							(not erase-instead?)
							text-value-from-postponed-erase)
					       (with-background-color-value
						   (if formatted-part-highlight-flag
						       text-cell-background-color-value
						       (get-background-color-value-from-postponed-erase))
						 (let ((erase-instead? t))
						   (draw-cell-text text-value-from-postponed-erase))))

					     (let ((new-background-color-value
						     (if dragging?	; if dragging, draw only table border skeleton
							 current-background-color-value
							 text-cell-background-color-value)))

					       ;; Draw/Erase the cell background 
					       (if (and erase-instead? postpone-cell-erase-until-redraw-p)
						   ;; If the background erase is to be postponed until redraw then we need to
						   ;; save the background color for redraw. (We postpone background erase's
						   ;; until redraw to eliminate flashing, cf. the comment in `cell-updated')
						   (set-background-color-value-from-postponed-erase
						     (if formatted-part-highlight-flag
							 (map-color-or-metacolor-to-color-value 
							   (text-cell-line-color? current-text-box-format))
							 new-background-color-value))
						   ;; Don't change the background color if the cell is highlighted
						   (unless (and formatted-part-highlight-flag
								postpone-cell-erase-until-redraw-p)
						     (let ((changing-colors-of-graphic-elements?
							     changing-colors-of-graphic-elements?))
						       ;; Mutate the cell background color if a postponed erase, see note 4 below
						       (when postpone-cell-erase-until-redraw-p
							 (setq changing-colors-of-graphic-elements? t))
						       ;; Draw the cell background.
						       (unless (or dragging?
								   (eq 'transparent
								       (text-cell-background-color?
									current-text-box-format)))
							 (draw-solid-rectangle
							  right-edge-of-lefthand-column-border-in-window
							  top-edge-of-row-in-window
							  right-edge-of-column-in-window
							  bottom-edge-of-row-in-window
							  (color-difference
							   new-background-color-value
							   (if postpone-cell-erase-until-redraw-p
							       (get-background-color-value-from-postponed-erase)
							       current-background-color-value)))))))

					       ;; Draw/Erase any text contained in the cell
					       (with-background-color-value
						   new-background-color-value
						 (if (and postpone-cell-erase-until-redraw-p erase-instead?)
						     ;; If this is an erase to be postponed, save the text and format.
						     ;; The postponed erase will be performed in a later Draw pass.
						     ;; If the current-text-box-format ever needs to be saved, do it here.
						     (progn (unless text-value-from-postponed-erase
							      (setq text-value-from-postponed-erase
								    (get-simple-part-feature cell-subpart 'text-value)))
							    (setq updated-only? nil))
						     (progn
						       (when (and formatted-part-highlight-flag
								  background-color-value-from-postponed-erase)
							 (setq current-foreground-color-value
							       (get-background-color-value-from-postponed-erase)))
						       (draw-cell-text (get-simple-part-feature cell-subpart 'text-value)))))))
					   ;; Undo highlighting
					   (when formatted-part-highlight-flag
					     (rotatef (text-cell-line-color? current-text-box-format)
						      (text-cell-background-color? current-text-box-format))))))

				      (invalidate-projection-mode
				       (invalidate-rectangle-of-workspace
					 (get-workspace-if-any current-annotated-frame) ;; assured non-nil by caller
					 current-annotated-frame
					 right-edge-of-lefthand-column-border-in-window
					 top-edge-of-row-in-window
					 right-edge-of-column-in-window
					 bottom-edge-of-row-in-window
					 :no-bleeding
					 ))
				      
				      (funcall-on-focus-projection-mode
				       (do-funcall-on-new-focus-if-necessary))))

				  ;; Advance the column edge pointer.
				  (setf left-edge-of-column (+w right-edge-of-column column-border-width))
				  (setf right-edge-of-lefthand-column-border-in-window
					right-edge-of-righthand-column-border-in-window)
				  )))))
			    finally ;; End of cells for this row.
			      (case projection-mode
				(update-dependencies
				 (when (eq current-kind-of-change 'size)
				   (setf maximum-width 
					 (-w (+w column-border-width right-edge-of-column) left-edge-of-block))
				   (setf maximum-height
					 (-w (+w row-border-height bottom-edge-of-row) top-edge-of-block))))
				(compute-path-of-focus-projection-mode
				 ;; Unless scan succeeded, pop and reclaim the generic column accessor initially pushed
				 (unless wrapup-scan-flag
				   (reclaim-slot-value-tree ; list pbk
				     (slot-value-pop projection-focus-path)))))
			    ))
		    ;; Advance the row edge pointer.
		    (setf top-edge-of-row (+w bottom-edge-of-row row-border-height))
		    (setf bottom-of-upper-row-border-in-window bottom-of-lower-row-border-in-window)
		    ))
		finally ;; Master Loop
		  (when (eql projection-mode 'compute-path-of-focus-projection-mode)
		    ;; Unless scan succeeded, pop and reclaim the generic row accessor initially pushed
		    (unless wrapup-scan-flag
		      (reclaim-slot-value-tree ;list pbk
			(slot-value-pop projection-focus-path))))
		))))))))

;; Note: a casual glance at this makes me think this doesn't handle
;; magnification.  I don't think it ever comes up in practice. (MHD 6/2/99)

;; Note 1: We bind the current-background-color value to the background color
;; for the entire chart.  This is not appropriate when we are actually drawing
;; the background, so we rebind it again when drawing the background for the
;; chart.

;; Note 2: Both the column-annotations and row-annotations are instances of
;; new-table part descriptions.  This simplifies things, by creating only one
;; clever data structure, but it makes us allocate more storage than we might
;; like to carry the overhead of a well formed part instance.  One example of a
;; place where things get more complex than we might like is when sweeping over
;; the rows we have to reach into the description of each row and pluck out the
;; single cell description that is kept in that row.

;; Note 3: This value must be computed and saved here (vs. where it is
;; referenced below) because map-color-or-metacolor... must be invoked in the
;; color environment for the table (vs. the color environment for the cell). In
;; particular if text-cell-background-color? = foreground, then we want this to
;; be bound to the inherited foreground color, not the cells computed foreground
;; color, which is bound into current-foreground-color-value subsequently.

;; Note 4: When we have postponed the erase (to eliminate flashing) we need
;; to mutate the background color of the current element in graphic
;; memory. This directly changes the background color to the new color
;; instead of having to first erase to old background color then redraw
;; in the new background color--causing flashing, cf. `cell-updated'.
;; If this is ever changed back to not mutate, then you must ensure that
;; you also remove (erase) the old element from graphic memory. See
;; ma:>bah>gem-hackery (in particular show-gem, gem-summary) for tools
;; helpful in monitoring graphic-element-memory.

;; Note 5; This code is 130 characters wide, but the paragraph formatting is at
;; 80 characters.



;;; `Create-text-for-datum' coerces a datum into a text.  It does so
;;; using the width given and the current-text-box-format.  The newly
;;; allocated text is returned.

(defun make-text-for-datum (datum width)
  (format-text
    (convert-text-string-to-text
      (twith-output-to-text-string
	(cond
	  ((text-string-p datum) ;; Strings in new-tables do not get quotation marks, etc.
	   (tformat "~A" datum))
	  ((null datum)
	   (twrite-string "****"))
	  ((evaluation-value-p datum)
	   (write-evaluation-value datum)))))
    current-text-box-format
    current-text-cell-plist
    width
    nil nil nil nil))



;; TBD ??
;; I don't have format on the cells, so I can't support DDD.DD, but it is
;;   availabe via expressions.  (This should be fixed with an additional
;;   format part feature).  But I don't want to do that until I can
;;   can get whatever the new formating notation is right.




;;; `Copy-and-format-text' creates a copy of the given text, and then
;;; formats at the width given in the style of the current-text-box-format.
;;; The newly allocated text is returned.

(defun copy-and-format-text (text width)
  (format-text (copy-for-slot-value text)
    current-text-box-format
    current-text-cell-plist
    width
    nil nil nil nil))







;;;; Block Insert And Deletes For New Table




;;; `Splice-lists' takes two lists and an index into the first of them.
;;; It destructively modifies the first list by inserting the second
;;; list into it.  The modified list is returned.  It is the nonconsing
;;; destructive equivalent of:
;;;  (concatenate 'list 
;;;     (subseq first-list 0 index)
;;;      second-list
;;;     (subseq first-list index))
;;; It is an error to provide an index outside the range 0 ..  (length
;;; destination-list).  Of course, if the index is zero then the result
;;; is not eq to the destination-list.

(defun splice-lists (destination-list source-list index)
  (declare (type fixnum index) 
	   (type list destination-list source-list))
  (when source-list
    (cond
      ((zerop index)
       (setf (cdr (last source-list)) destination-list)
       source-list)
      (T
       (let ((nthcdr (nthcdr (1-f index) destination-list)))
	 (setf (cdr (last source-list)) (cdr nthcdr))
	 (setf (cdr nthcdr) source-list)
	 destination-list)))))


;;; `Insert-subpart-description' takes two part descriptions a source
;;; and a destination.  It inserts all the suparts of the given type out
;;; of the source and into the destination at before the zero based
;;; index.  The destination part description is returned.  The index
;;; must be in the range 0 to number of subparts in the destination.
;;; The maximum index, of course, appends the new subparts on the
;;; destination.

(defun insert-subpart-descriptions (destination-part-description
				    source-part-description
				    subpart-type
				    index-to-insert-at)
  (let ((destination-subparts
	  (get-subpart-collection destination-part-description 'subparts subpart-type))
	(source-subparts
	  (get-subpart-collection source-part-description 'subparts subpart-type)))
    ;; Remove the subparts from the source.
    (set-subpart-collection-without-reclaiming
      source-part-description
      'subparts
      subpart-type
      nil)
    ;; Splice into the destination's subparts.
    (setf destination-subparts
	  (splice-lists
	    destination-subparts
	    source-subparts
	    index-to-insert-at))
    ;; Put full list back into the destination.
    (set-subpart-collection-without-reclaiming 
      destination-part-description
      'subparts
      subpart-type
      destination-subparts)
  destination-part-description))



;;; `Delete-subpart' from a part description the Ith part of a given type.
;;; The deleted part is reclaimed.  The index must be in the range zero to
;;; the number of subparts minus 1.  The part-description is returned.

(defun delete-subpart (part-description subpart-type index-of-subpart-to-delete)
  (declare (type fixnum index-of-subpart-to-delete))
  (let* ((subparts
	   (get-subpart-collection part-description 'subparts subpart-type))
	 bit-to-reclaim)
    (cond
      ((=f 0 index-of-subpart-to-delete)
       (setf bit-to-reclaim subparts)
       (setf subparts (cdr subparts)))
      (T
       (let ((nthcdr (nthcdr 
		       (-f index-of-subpart-to-delete 1)
		       subparts)))
	 (setf bit-to-reclaim (cdr nthcdr))
	 (setf (cdr nthcdr) (cdr bit-to-reclaim)))))
    (setf (cdr bit-to-reclaim) nil)
    (reclaim-part-description (car bit-to-reclaim))
    (reclaim-slot-value-list bit-to-reclaim)
    (set-subpart-collection-without-reclaiming 
      part-description
      'subparts
      subpart-type
      subparts)
    part-description))





;;; `Table-block-insert-or-delete' implements the adjusting the
;;; table data structures when a group of cells in inserted or deleted.
;;; This currently only does row and column inserting and deleting.

;;; The row/columns are added/deleted to upper-left of the cell
;;; indicated by row-index and column-index.  Cell 0,0 is the
;;; cell in extreme upper left.  To extend the table on the lower or
;;; right a cell-index equal to the number of cells in that dimension
;;; should be passed. (paragraph is wrong, for now).

;;; The routine consists of three parts: prolog, body and epilog.  The
;;; prolog removes the block from the screen, and allocates the data to
;;; insert.  The Body does the actual insertion or deletion.  The epilog
;;; reclaims some storage, recomputes the size of the block, returns the
;;; block to the screen, and updates any effected representations.

;;; The routine modifies the three annotations (row, column, and cell)
;;; for the target-table.  When inserting it splices into those
;;; annotations new part descriptions for the added parts.  When
;;; deleting it slices out and reclaims from those annotations.  When
;;; deleting it uses the routine delete-subpart.  

;;; When inserting the routine allocates complete new-table part
;;; descriptions for the fragment to be inserted.  It then copies parts
;;; from those part descriptions into the target using
;;; insert-subpart-descriptions.  These new bits are allocated via
;;; make-table-annotation, which assures that all fresh table part
;;; descriptions are created by that one routine.

(defun table-block-insert-or-delete (target-table row-index column-index edit-action count)
  (assert-that-within-named-dynamic-extent 'working-on-new-table)
  (let* (;; Unpack the target tables slots.
	 (target-cell-annotations (cell-annotations target-table))
	 (target-row-annotations (row-annotations target-table))
	 (target-column-annotations (column-annotations target-table))
	 
	 ;; The size of the original and destination
	 (original-row-maximum 
	   (get-simple-part-feature target-cell-annotations 'row-maximum))
	 (original-column-maximum
	   (get-simple-part-feature target-cell-annotations 'column-maximum))
	 
	 ;; Info about the insertion, bound in the prolog.
	 insert-cell-annotations
	 insert-row-annotations
	 insert-column-annotations
	 
	 ;; Info about the result, this is rebound when the 
	 ;; insert is allocated.
	 (final-row-maximum original-row-maximum)
	 (final-column-maximum original-column-maximum)
	 
	 )

    ;; The Prolog
    ;; Remove the old table from screen.
    (erase-entire-annotated-block current-annotated-frame)

    ;; Retract the old analysis of consistency, since we maybe deleting things.
    (without-consistency-analysis (target-table)
      ;; Build the table that describes the selection we are inserting.
      (multiple-value-setq (insert-row-annotations insert-column-annotations insert-cell-annotations)
	(case edit-action
	  (add-row
	   (incff final-row-maximum count)
	   (values 
	     (make-table-annotation 'row    count original-column-maximum)
	     nil
	     (make-table-annotation 'cell   count original-column-maximum)))
	  (add-column
	   (incff final-column-maximum count)
	   (values 
	     nil 
	     (make-table-annotation 'column original-row-maximum count)
	     (make-table-annotation 'cell   original-row-maximum count)))
	  (delete-row
	   (decff final-row-maximum count)
	   (values nil nil nil))
	  (delete-column
	   (decff final-column-maximum count)
	   (values nil nil nil))
	  ))
      
      ;; The Body
      (case edit-action
	(add-row
	 (insert-subpart-descriptions
	   target-row-annotations
	   insert-row-annotations
	   'row
	   row-index)
	 (insert-subpart-descriptions
	   target-cell-annotations
	   insert-cell-annotations
	   'row
	   row-index))
	(delete-row
	 (loop repeat count do
	   (delete-subpart target-row-annotations 'row row-index)
	   (delete-subpart target-cell-annotations 'row row-index)))
	(add-column
	 ;; Insert the column into each row of the cell-annotations.
	 (loop for target-row-part-description 
		   in (get-subpart-collection target-cell-annotations 'subparts 'row)
	       for insert-row-part-description
		   in (get-subpart-collection insert-cell-annotations 'subparts 'row)
	       do (insert-subpart-descriptions
		    target-row-part-description
		    insert-row-part-description
		    'cell
		    column-index))
	 ;; Insert the column into the column-annotations.
	 (insert-subpart-descriptions
	   (first (get-subpart-collection target-column-annotations 'subparts 'row))
	   (first (get-subpart-collection insert-column-annotations 'subparts 'row))
	   'cell
	   column-index))
	(delete-column
	 (loop repeat count do
	   ;; Delete the cell for this column for each row.
	   (loop for row-part-description 
		     in (get-subpart-collection target-cell-annotations 'subparts 'row)
		 do (delete-subpart row-part-description 'cell column-index))
	   ;; Delete the cell (of the first row) in the column annotations
	   (delete-subpart
	     (first (get-subpart-collection target-column-annotations 'subparts 'row))
	     'cell
	     column-index))))
      
      (set-simple-part-feature target-cell-annotations 'row-maximum final-row-maximum)
      (set-simple-part-feature target-cell-annotations 'column-maximum final-column-maximum)
      (set-simple-part-feature target-column-annotations 'column-maximum final-column-maximum)
      (set-simple-part-feature target-row-annotations 'row-maximum final-row-maximum)
      (update-representations-of-slot-value current-annotated-frame 'cell-annotations)
      (update-representations-of-slot-value current-annotated-frame 'row-annotations)
      (update-representations-of-slot-value current-annotated-frame 'column-annotations)
      
      ;; The Epilog
      
      ;; Reclaim what wasn't moved over in the inserted bit.
      (reclaim-slot-value insert-row-annotations)
      (reclaim-slot-value insert-column-annotations)
      (reclaim-slot-value insert-cell-annotations)
      ;; Rederive the table size for this new table.
      (update-new-table-size))
    (funcall-method 'update-frame-status-and-notes target-table)
    (send-ws-representations-item-virtual-attribute-change
      target-table (virtual-attribute 'table-cells) nil)
    ;; Finally, restore the now revised table to the screen.
    (redraw-entire-annotated-block)
    ))

;; The table is erased and redrawn using erase-entire-annotated-block
;; and redraw-entire-annotated-block.  They set up the dynamic state
;; to preempt drawing as the entries in the cell array are deleted.





;;;; User Edits For New Table




;;; The module facilities provides the menus from which all edits to
;;; tables are launched.  Those edits are all funneled thru
;;; `do-new-table-edit.' This routine provides these edit actions:

;;;    edit-cell-expression
;;;    edit-cell-format
;;;    add-row
;;;    add-column
;;;    delete-row
;;;    delete-column

;;; These actions apply to the cell the user originally clicked over
;;; upon starting the edit to the table.

(defun do-new-table-edit (new-table edit-action image-plane x-in-window y-in-window)
  (with-named-dynamic-extent working-on-annotated-frame 
      ((current-annotated-frame new-table))
    (let ((current-block-of-dependent-frame new-table))
      (with-raw-window-transform-and-draw-area
	  ((gensym-window-for-image-plane image-plane))
	(with-nested-transform-and-draw-area-of-image-plane-contents? (image-plane)
	  (on-image-plane-without-drawing (image-plane)
	    (with-named-dynamic-extent editing-new-table
		((current-annotated-frame new-table))
	      (case edit-action
		((edit-cell-expression edit-cell-format)
		 (multiple-value-bind (table row-index column-index cell-subpart)
		     (track-mouse-for-new-table x-in-window y-in-window t)
		   #-development
		   (declare (ignore table row-index column-index))
		   #+development
		   (assert (and table row-index column-index))
		   (start-edit-of-annotation-subexpression
		     current-annotated-frame
		     cell-subpart
		     ;; what to edit.
		     (getf '( edit-cell-expression cell-contents
			     edit-cell-format T)
			   edit-action)
		     ;; what type it is.
		     (getf '( edit-cell-expression cell-expression-and-text
			     edit-cell-format cell-format)
			   edit-action)
		     ))
		 )
		((add-row delete-row add-column delete-column)
		 (multiple-value-bind (table row-index column-index)
		     (track-mouse-for-new-table x-in-window y-in-window nil)
		   (table-block-insert-or-delete
		     table (1-f row-index) (1-f column-index)
		     edit-action 1)))
		#+development
		(otherwise
		 (multiple-value-bind (new-table row-index column-index)
		     (track-mouse-for-new-table x-in-window y-in-window nil)
		   (db-format (list new-table edit-action row-index column-index))))))))))))

;; This would be much better, but we need "original mouse pointer" to survive the
;; menu experiance.
;(defun do-new-table-edit (edit-action original-mouse-pointer)
;  (declare (ignore x-in-window y-in-window))
;  (with-named-dynamic-extent working-on-annotated-frame 
;                             ((current-annotated-frame new-table))
;    (let* ((new-table-cell-spot (stack-of-spots original-mouse-pointer))
;           (new-table (referenced-frame? new-table-cell-spot))
;           (current-block-of-dependent-frame new-table))
;      (on-image-plane-without-drawing (image-plane
;                                        (left-edge-of-workspace-area-within-pane image-plane)
;                                        (top-edge-of-workspace-area-within-pane image-plane)
;                                        (right-edge-of-workspace-area-within-pane image-plane)
;                                        (bottom-edge-of-workspace-area-within-pane image-plane))
;          (with-named-dynamic-extent editing-new-table
;                                     ((current-annotated-frame new-table))
;            (case edit-action
;              ((edit-cell-expression edit-cell-format)
;               ;; We must have a new-table-cell-spot
;               (start-edit-of-annotation-subexpression
;                   current-annotated-frame
;                   (subpart-of-new-table? new-table-cell-spot)
;                   ;; what to edit.
;                   (getf '( edit-cell-expression cell-contents
;                           edit-cell-format T)
;                         edit-action)
;                   ;; what type it is.
;                   (getf '( edit-cell-expression cell-expression-and-text
;                           edit-cell-format cell-format)
;                         edit-action)))
;              ((add-row delete-row add-column delete-column)
;               (table-block-insert-or-delete
;                 new-table
;                 (1-f (row-index-of-new-table new-table-cell-spot))
;                 (1-f (column-index-of-new-table new-table-cell-spot))
;                 edit-action 1))
;              #+development
;              (otherwise
;               (print edit-action)
;               (d new-table-cell-spot)
;               (cerror "Nevermind" "Unknown edit-action in do-new-table-edit"))))))))



;;; `Mouse-over-cell-in-new-table-p' returns a boolean if the mouse
;;; is currently over a cell in the table given.  It must be called
;;; only when a servicing-workstation-event context is established.

(defun mouse-over-cell-in-new-table-p (new-table)
  (declare (ignore new-table))
  (new-table-cell-spot-p
    (stack-of-spots
      (mouse-pointer-of-latest-event
	current-workstation))))



;;; `Change-in-freeform-table-dimensions-is-ok-p' is used by facilities to
;;; assure that menus are not shown that would make the table a size unacceptable
;;; to table-dimension-p.

(defun change-in-freeform-table-dimensions-is-ok-p (freeform-table row-delta column-delta)
  (declare (type fixnum row-delta column-delta))
  (let* ((cell-annotations (cell-annotations freeform-table))
	 (row-maximum (get-simple-part-feature cell-annotations 'row-maximum))
	 (column-maximum (get-simple-part-feature cell-annotations 'column-maximum)))
    (and (table-dimension-p (+f row-maximum row-delta))
	 (table-dimension-p (+f column-maximum column-delta))
	 (item-is-either-not-permanent-or-from-an-editable-module-p freeform-table))))


(defun row-and-column-index-available-p (mouse-pointer)
  (with-mouse-pointer-bindings-no-warn
      (block image-plane original-x-in-window original-y-in-window)
      mouse-pointer
    (and (of-class-p block 'freeform-table)
	 (change-in-freeform-table-is-meaningful-p
	   block 0 0
	   image-plane original-x-in-window original-y-in-window))))

(defun change-in-freeform-table-is-meaningful-p
    (freeform-table row-delta column-delta image-plane original-x-in-window original-y-in-window)
  (declare (type fixnum row-delta column-delta))
  (unless (item-is-either-not-permanent-or-from-an-editable-module-p freeform-table)
    (return-from change-in-freeform-table-is-meaningful-p nil))
  (with-named-dynamic-extent working-on-annotated-frame 
      ((current-annotated-frame freeform-table))

    (on-image-plane-without-drawing (image-plane)
      (multiple-value-bind (table row-index column-index cell-subpart)
	  (track-mouse-for-new-table original-x-in-window original-y-in-window t)
	(declare (ignore table cell-subpart))
	
	(and row-index
	     column-index
	     (or
	       (and (=f row-delta 0)
		    (=f column-delta 0))
	       (change-in-freeform-table-dimensions-is-ok-p freeform-table row-delta column-delta)))))))




;;;; Describe For New Table





;;; Describe-new-table implements the substance of the describe-frame method.




;;; When you describe a new table we project the table in funcall on focus mode,
;;; so that we will get a call back when we visit subparts that are in the focus.
;;; During these call backs we accumulate a description of the table.

;;; We establish a projecting-to-collect-description-for-new-table dynamic extent
;;; which includes that eval-list we are accumulating for describe.

;;; In summary:
;;;    describe-frame method -- Queries, calls describe-new-table.
;;;    describe-new-table    -- establishs dynamic extent and projects table.
;;;    describe-new-table-from-inside-project -- called back during the projection.
;;;    describe-part-from-current-extent      -- discussed below

(def-named-dynamic-extent projecting-to-collect-description-for-new-table
  (module new-tables)
  (includes projection-funcall-on-focus))


(defvar-of-named-dynamic-extent current-description-of-new-table 
				projecting-to-collect-description-for-new-table)


(defun describe-new-table ()
  (with-named-dynamic-extent working-on-annotated-frame 
			     ((current-annotated-frame *current-computation-frame*))
    (with-named-dynamic-extent projecting-to-collect-description-for-new-table
			       ((projection-mode 'funcall-on-focus-projection-mode)
				(current-projection-function-for-funcall 
				  #'describe-new-table-from-inside-projection)
				(projection-focus-method nil)
				(current-description-of-new-table nil))
	(with-simulated-on-image-plane
	  (project-new-table))
	current-description-of-new-table)))


(defun describe-new-table-from-inside-projection (why-called)
  (declare (ignore why-called))
  (within-named-dynamic-extent projecting-to-collect-description-for-new-table
    (setf current-description-of-new-table
	  (nconc
	    (describe-part-from-current-extent 'formatted-part)
	    (eval-list
	      (copy-text-string
		"The formating attributes for a simple cell in the table are:"))

	    (describe-part-from-current-extent 'computation-style-description)
	    (eval-list
	      (copy-text-string
		"The evaluation attributes for a simple expression in the table are:"))

	    current-description-of-new-table)))
  t ;; No need to call this anymore, abandon scan as soon as possible.
  )



;;; `Describe-part-from-current-extent,' which probably belongs in PARTS.  Searchs
;;; stack-of-current-part-descriptions for each feature of the given part type and
;;; creates a text-string that describes the current setting.

(defun describe-part-from-current-extent (part-type)
  (within-named-dynamic-extent scanning-subparts-of-block
    (eval-list
      (twith-output-to-text-string
	(let ((cummulative-part-description
		(slot-value-cons
		  part-type
		  (loop with part-type-description = (part-type-description part-type)
			with hidden-features = (part-type-hidden-features part-type-description)
			with part-features = (part-type-features part-type-description)
			for (nil (part-feature-name
				   nil		; part-feature-means-of-scanning
				   nil		; part-feature-type
				   nil		; part-feature-user-spelling
				   part-feature-user-visible?)) on part-features by #'cddr
			when (and part-feature-user-visible?
				  (not (memq part-feature-name hidden-features)))
			  nconc
			    (loop for outstanding-part-description in stack-of-current-part-descriptions
				  as level from 1
				  when (part-has-feature-p outstanding-part-description part-feature-name)
				    nconc
				      (slot-value-list
					part-feature-name
					(get-simple-part-feature
					  outstanding-part-description
					  part-feature-name)))))))
	  (write-part-description cummulative-part-description t 5 t)
	  (reclaim-slot-value-list cummulative-part-description))))))







;;;; Debugging Facilities




#+development
(defun validate-new-table 
       (&optional (new-table (instances-specific-to-this-class-tail-pointer 'freeform-table)))
  (values 
    new-table
    (and 
      ;; Validate, just a little, the slot-value cons pool
      (list-length available-slot-value-conses)	; circular?
      (loop for p on available-slot-value-conses
	    as car-contents = (car p)
	    always (or (null car-contents)
		       (eq slot-value-car-marker car-contents)))
      (validate-part-instance 'new-table (row-annotations new-table))
      (validate-part-instance 'new-table (column-annotations new-table))
      (validate-part-instance 'new-table (cell-annotations new-table)))))





;;;; To Do List For New Tables



;; Done: the flicker (aka flash) during cell update was removed by WGD on 5/20/92
;; in version 209 (see the comments in `cell-updated'. I am leaving the following
;; description here for historical and educational purposes:)
;;
;; Resolving the Flicker Problem:

;; Currently when a change is made the procedure looks something like this path
;; expression:
;;    Change-Rendering: 
;;       (Erase-Rendering)*;
;;       Update-Dependencies;
;;       (Draw-Rendering)*
;; where the (X)* executes as many times as there are image-planes showing this
;; table.

;; This needs to change into this:
;;    Change-Rendering: 
;;       Begin-Update-Dependencies;
;;       (Revise-Rendering)*;
;;       End-Update-Dependencies
;; 
;; This allows the Revise-Rendering to do only the incremental drawing required.
;; The state necessary to effect the change would maintained in the dynamic
;; extent of the change.  The final commit of the change into the new table would
;; be done by End-update-dependencies.

;; For example to change the text of a cell.  Begin would compute the new text
;; value and place it in the dynamic extent's state.  Each revise rendering
;; would then XOR out the old text and XOR in the new text.  Finally the
;; End-Update-Dependencies would store the new text, and reclaim the old text.

;; For example to change the color of some component of the cell the begin
;; would compute a color difference between the old and then new color.  The
;; Revise-Rendering calls would then XOR in that color difference for the
;; changed component, and redraw each of the overlayed components in a color
;; by an appropriate color difference.

;; Apparently the state maintained in during the dynamic extent of the change
;; needs to be sufficently complex to store one bundle for each kind of
;; change can be done.  It doesn't seem necessary enable a number of
;; things to be revised at the same time.

;; It also seems clear that begin-update-dependencies may decide that the only
;; course of action is to erase the entire table and redraw it.   In which case
;; the path expression looks more like:

;;   Change-Rendering:   
;;    if Begin-Update-Dependencies then
;;        (Revise-Rendering)*; End-Update-Dependencies
;;    else
;;        (Erase-Rendering)*; Update-Dependendies; (Draw-Rendering)*
;;    end
