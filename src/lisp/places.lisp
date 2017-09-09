;;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module PLACES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Jim Allard




;;; Forward References

;; In PROC-UTILS

(declare-forward-reference write-procedure-statement function)
(declare-forward-reference denote-component-of-block-1-for-procedure-invocation function)

;; In TABLES
(declare-forward-reference denote-slot-component-group function)






;;;; KB Components OR Component Particulars


;;; These symbols are analagous to type names, in fact they are used to name
;;; classes data in the process that are not items.  Other examples include
;;; elements of arrays, data series in charts, layers of icons.

;;; One primary operation on instances of these types is to form a reference to
;;; it and these refrences are called component particulars.  Component
;;; particulars are S-Expressions that maybe interpreted to fetch the instance
;;; (i.e.  they are a symbolic reference to the object).  For example
;;; (data-series 3) refers to the third data series within some from frame
;;; implicitly given.

;;; Two conventions are typically used to find the frame the component is being
;;; referenced from.  `*current-computation-frame*' is often the frame the
;;; component-particulars are relative to.  Place-references are an evaluation
;;; datum that encapsulates a frame, component-particulars, and a frame serial
;;; number.

;;; Component particulars appear in many data structures.  For example they are
;;; encountered in frame notes so that frame notes may refer to the component of
;;; a frame where the problem actually occured.

;;; Component particulars appear dynamicly.  For example in the evaluator
;;; enclosed in place-references.  For example as the result some mouse
;;; tracking.  For example in denoting the component that had a runtime error in
;;; cell arrays.

;;; The set of operations on a component are extensive.  Not all kinds of
;;; components provide all these operations.  Most of them support denotation.
;;; For example (data-series 2) is denoted as "the second data series of
;;; my-chart" when *current-computation-frame* is bound to a chart named MY-CHART.

;;; To define a new kind of component, you must supply a def-component form and
;;; add an appropriate clause to denote-component-of-block-1.  Def-component is
;;; defined earlier in the system, in the module TYPES.

;;; The function `set-component-value' is used to modify the values of
;;; components of blocks.  It takes three values, the block,
;;; component-particulars, and new evaluation-value to place into the location.
;;; The evaluation value will be reclaimed by this function.  If the value is
;;; successfully put into the location, then this function returns NIL.  If
;;; there is a problem putting the value, then a text string is returned
;;; describing the error.  That string must be reclaimed by the caller of this
;;; function.

#+unused
(defun-simple set-component-value (block component-particulars evaluation-value)
  (let ((setter? (getfq (component-kind-description
			 (car-of-cons component-particulars))
			:setter)))
    (if setter?
	(funcall-simple-compiled-function
	 setter? block component-particulars evaluation-value)
	(no-component-setter-error
	 block component-particulars evaluation-value))))

#+unused
(defun-simple no-component-setter-error
              (block component-particulars evaluation-value)
  (twith-output-to-text-string
   (tformat "Unable to put ~NV into " evaluation-value)
   (when evaluation-value
     (reclaim-evaluation-value evaluation-value))
   (denote-component-of-block t component-particulars block)
   (twrite-string ", since this location cannot be modified.")))




;;; The function `get-component-value' is used to fetch the value of a component
;;; of a block.  It takes two arguments, the block and the component
;;; particulars.  This function returns an evaluation value which should be
;;; reclaimed by the caller, or NIL if there is an error fetching this value
;;; from this slot.  A NIL return from this function is the "does not exist"
;;; case within the evaluators.

#+unused
(defun-simple get-component-value (block component-particulars)
  (let ((getter? (getfq (component-kind-description
			 (car-of-cons component-particulars))
			:getter)))
    (if getter?
	(funcall-simple-compiled-function getter? block component-particulars)
	nil)))




;;; `Graph-expression' is used to reference a particular graph expression within
;;; a graph frame.  It is of the form:
;;;    (graph-expression . <index/integer>)
;;; for example: (graph-expression . 2)
;;; and it might be denoted:  "graph expression 2 of my-graph"

(def-component graph-expression)

;; This is not a very good example to start with, since the use of a dotted list
;; is unusual, and the lack of a place for the enclosed component.
;;   (graph-expression  <index/integer> <component-particulars>)



;;; `Data-series' is used to reference the individual data series within a chart.
;;; This is of the form:   (data-series <index/integer>)
;;; For example:           (data-series 2)
;;; Which might be denoted: "the second data-series of my-chart"
;;;                     or: "data-series 2 of my-chart"

(def-component data-series)

;; This ought to include place for the enclosing component.



;;; `Cell-array-element' is used to denote individual cells in the
;;; cell array of a frame (See the module CELLS).  These are of the form:
;;;     (cell-array-element <integer>)

(def-component cell-array-element)



;;; `slot-component' is used to denote a part of a complex slot
;;; value that has hybrid table/text editing interface that is
;;; documented in some detail in module TABLES. (JED 5/24/94)

(def-component slot-component)



;;; `Get-simple-part-feature' is used to reference parts that appear
;;; inside of part-descriptions (See the module PARTS).  These are
;;; of the form:
;;;   (get-simple-part-feature <part-description> <part-feature>)
;;; For example:
;;;   (get-simple-part-feature 
;;;     (part-description-of-frame 'annotations *current-computation-frame*)
;;;     :background-color)
;;; An example denotation for this might be 
;;;   "the background-color of my-chart"

;;; The function get-simple-part-feature implements fetching the component
;;; referenced by these particulars.

(def-component get-simple-part-feature)



;;; `Get-subpart-of-collection' is used to access a component within a part
;;; description.  Parts descriptions in described in the module PARTS.  Recall that a
;;; part description can contain an ordered collection of subparts of the same type,
;;; for example the data-series of a chart, or the rows of a table.
;;; These are of the form:
;;;    (get-subpart-of-collection <part-description> 'subparts '<part-type> <index>)
;;; For example:
;;;    (get-subpart-of-collection 
;;;        (part-description-of-frame 'annotations *current-computation-frame*)
;;;        'subparts
;;;        'row 2))
;;; An example denoatation for this example might be: "row 2 of my-table"

;;; The function get-subpart-of-collection implements fetching the component
;;; referenced by these particulars.

(def-component get-subpart-of-collection)



;;; `Get-subpart' is obsolete.

#+OBSOLETE
(def-component get-subpart)



;;; `part-description-of-frame' is used to refer to the set of components of
;;; a frame that are embedded in a part description found on that frame.
;;; These are of the form:
;;;   (part-description-of-frame <slot-name> current-computation-components)
;;; An example might be:
;;;   (part-description-of-frame 'annotations current-computation-components)
;;; This is denoted by using the denotation of the frame, i.e. "my-table"

(def-component part-description-of-frame)



;;; `Aliased-attribute' is used to reference a component of a frame found in a
;;; slot, where that slot has been given an alias (see def-slot-alias).  This is
;;; analagous to the attribute component particular.  This is of the form:

;;;    (alias-attribute <alias-for-attribute-name> <actual-attribute-name>
;;;                     <further-component>)
;;; For example:
;;;    (alias-attribute 'last-recorded-value 'current-value-of-variable-or-parameter *current-computation-frame*)
;;; which might be denoted "the last-recorded-value of my-variable"

;;; This is used in the evaluator when concluding system attributes that have
;;; been aliased.

(def-component aliased-attribute)

;; Is the form shown correct? - ben 4/9/93                     



;;; `Attribute' is used to reference a component of a frame found in a slot of
;;; that frame.  See aliased-attribute for additional information.

(def-component attribute)



;;; `Element' is used to reference a component of an list or an array.  It is
;;; used in the evaluator in concluding these.  It is of the form:
;;;   (element <index/integer> <enclosing-component-particulars>)
;;; For example: (element 3 *current-computation-frame*)
;;; Which might be denoted as "my-list[3]"

(def-component element)



;;; `procedure-statement' is used to reference a particular statement within
;;; a procedure.  This is of the form:
;;;    (procedure <statement-info> <enclosing-component-particulars>)
;;; for example: (procedure-statement 3 *current-computation-frame*)
;;; which might be denoted as: ""I = 2" of my-procedure"

;;; This is used during procedure compiling.

(def-component procedure-statement) 



;;; `procedure-invocation' is used to reference an invocation of a procedure
;;; when that the KB author has not filled in "class of procedure invokation" in
;;; the procedure's table.  This is of the form:
;;;    (procedure-invocation)
;;; Which might be denoted as:  "my-procedure(1,3,pump-4)

;; I don't understand when these are used.

(def-component procedure-invocation)




;; Other possiblities.
;;     (def-component selection                             -- {my-block his-block her-item}
;;     (def-component text-region                           -- line 3 character 4 thru line 5 my-message	
;;     (def-component connection-of-block                   -- the connection located at left 24 of my-pump
;;     (def-component icon-region                           -- the indicator of my-pump
;;     (def-component icon-regions                          -- internal as in
;;                                           --  change the color-pattern of ... so that indicator = red ...
;;     (def-component connection-strips                     -- internal
;;     (def-component graph-grid                            -- internal
;;     (def-component text-highlight








;;;; Printing References to Blocks and Their Components




;;; As well as printing designations for blocks, there is a need to operate on
;;; denotations of components of blocks which may not be represented as slot
;;; values.  This need will be filled through a system of `component
;;; particulars'.  A component particular is a list whose car is a symbol naming
;;; the sort of component particular that it is.  The format of rest of the
;;; component particular varies, depending on the kind of component particular.

;;; The need for component particulars arises, for example, when printing
;;; information about the code-bodies of procedures, the expression
;;; subcomponents of tables, and the different layout characteristics of charts.
;;; Information needed to denote a sub-part of a block is defined as the frame,
;;; and some other slot value which is interpreted on a class by class basis.
;;; For example "instruction 79 of code body 3 of open-valve" could be printed
;;; in messages about run-time errors experienced while executing procedure
;;; code, given a procedure and a cons with the code body number in its car and
;;; the instruction number in its cdr.

;;; Within execution of the interpreters and during compilation, the special
;;; variables *current-computation-frame* and current-computation-component-
;;; particulars will be bound to the frame and particulars denoting the thing
;;; being executed at the current moment.  These can be passed to the
;;; denote-component-of-block method to twrite its denotation.

;;; `Component-particulars' are slot values that read like vanilla lisp code to
;;; fetch the component of a frame.  Component-particulars are compared using
;;; equal.  They are saved in KB as part of frame notes.

;;; One operation on component particulars is the generation of a denotation for
;;; the component of the frame they refer to.  The routine
;;; `denote-component-of-block' is used to twrite a denotation for a given
;;; component-particular.  Component particulars are also heavily used in place
;;; references.

;;; These are the known forms that may be passed to denote-component-of-block:

;;;      form                                emits
;;;    (cell-array-element <integer>)  invokes the denote-cell-array-element
;;;                                      method
;;;    (slot-component <slot-name> <defining-class> <slot-component-indicator>)
;;;                                    "the <component-type-name> named <symbol> of ..." |
;;;                                    "the <component-type-name> # <integer> of ..." |
;;;                                    "the <component-type-name> of"
;;;    (get-simple-part-feature ...)   "the <part-feature>[ of <what-ever>]"
;;;    (get-subpart-of-collection <what-ever> 'subparts '<part-type> <index>)
;;;                                    "the <part-type> <index>[ of <whatever>]"
;;;    (part-description-of-frame 'attribute <what-ever>)
;;;                                    "<what-ever>"
;;;    (procedure-statement ...)       "<statement>[ within <whatever>]"
;;;    (attribute <symbol> ...)        "the <attribute-name> [of <whatever>]"
;;;    (aliased-attribute <alias> <attribute-name> ...)
;;;                                    "the <alias> [of <whatever>]"
;;;    (graph-expression . <integer>)  "graph expression <integer>"
;;;    (data-series <integer>)         "data-series <integer>"
;;;    (procedure-invocation)          "<procedure-name> (<argument-list>)"
;;;    (simulation-initial-value)      "the simulation-initial-value [of <it>]"

;; Obsolete
;;    (get-subpart <what-ever> 'subparts '<part-type> <index>)
;;                                    "the <part-type> <index>[ of <what-ever>]"

;;; Denote-component-of-block sets up some dynamic scope and then calls
;;; denote-component-of-block-1 with the component particulars and a prepostion
;;; that should prefix nested description if any.  Note that spacing between
;;; component descriptions should handled with the passed prefix.  This accepts
;;; one additional form: '*current-computation-frame* which twrites a designation
;;; for the block in current computation frame.

(defvar current-include-denotation-for-block-flag)

(defun denote-component-of-block
       (include-denotation-for-block 
	&optional
	(component-particulars current-computation-component-particulars)
	(block *current-computation-frame*))
  #+development
  (assert (listp component-particulars))
  (let ((*current-computation-frame* block)
	(current-include-denotation-for-block-flag include-denotation-for-block))
    (denote-component-of-block-1 
      (or component-particulars
	  '*current-computation-frame*)
      "")))

(defun denote-component-of-block-1 (component-particulars preposition)
  (cond 
    ((eq '*current-computation-frame* component-particulars)
     (when current-include-denotation-for-block-flag
       (tformat
	 "~A~NF"
	 preposition
	 *current-computation-frame*)))
    ((atom component-particulars)
     (twrite-string preposition)
     (twrite-string "<error writing component>")
     #+development
     (cerror "continue" "Component-particular was not a cons: ~a"
	     component-particulars))
    (t
     (case (car-of-cons component-particulars)
       (cell-array-element
	(funcall-method
	  'denote-cell-array-element 
	  *current-computation-frame*
	  (second component-particulars)
	  current-include-denotation-for-block-flag))
       (slot-component
	(gensym-dstruct-bind ((nil slot-name defining-class? slot-component-indicator?)
			     component-particulars)
	  (denote-slot-component-group
	    *current-computation-frame* slot-name
	    defining-class? slot-component-indicator?)
	  (denote-component-of-block-1 '*current-computation-frame* " of ")))
       (get-simple-part-feature
	(gensym-dstruct-bind ((nil parent (nil part-feature))
			     component-particulars)
	  (tformat "~(~Athe ~A~)" preposition part-feature)
	  (denote-component-of-block-1 parent " of ")))
       ((get-subpart-of-collection 
	  get-subpart) ;; Obsolete
	(gensym-dstruct-bind ((nil parent nil (nil subpart-type) index)
			     component-particulars)
	  (tformat "~(~A~A ~D~)" preposition subpart-type index)
	  (denote-component-of-block-1 parent " of ")))
       (part-description-of-frame
	(gensym-dstruct-bind ((nil nil further-particulars) 
			     component-particulars)
	  (denote-component-of-block-1 further-particulars preposition)))
       ;; Note that the printer for aliased attributes may need to allow
       ;; printing of class qualifiers in the future if we allow overloading of
       ;; system defined slots and aliases.  -jra 2/15/94
       (aliased-attribute
	(gensym-dstruct-bind ((nil alias nil nil further-particulars)
			     component-particulars)
	  (tformat "~(~Athe ~A~)" preposition alias)
	  (denote-component-of-block-1 further-particulars " of ")))
       ;; Note that this printer never suppresses the class qualifier, and
       ;; potentially should.  -jra 2/15/94
       ;; And now it does, to fix Bug HQ-4351857 "Error message contains "nil"".
       ;; - jpg 8/6/02
       (attribute
	(gensym-dstruct-bind ((nil attribute-name defining-class further-particulars)
			     component-particulars)
	  (tformat "~(~Athe ~NQ~)" preposition attribute-name defining-class)
	  (denote-component-of-block-1 further-particulars " of ")))
       (element
	(gensym-dstruct-bind ((nil index further-particulars)
			     component-particulars)
	  (tformat "~a" preposition)
	  (denote-component-of-block-1 further-particulars "")
	  (tformat " [~a]" index)))
       (procedure-statement
	(gensym-dstruct-bind ((nil statement parent) component-particulars)
	  (tformat "~a" preposition)
	  (write-procedure-statement statement)
	  (denote-component-of-block-1 parent " within ")))
       (graph-expression
	(tformat "graph expression ~d" (cdr component-particulars)))
       (data-series
	(let ((count (second component-particulars)))
	  (case count
	    ((1 2 3)
	     (tformat "~athe ~a data-series" 
		      preposition
		      (nth count '(nil "first" "second" "third"))))
	    (otherwise
	     (tformat "~a data-series ~a" preposition count)))
	  (denote-component-of-block-1 '*current-computation-frame* " of ")))
       (procedure-invocation
	(denote-component-of-block-1-for-procedure-invocation))
       ;; Component-definition location.  The writer is made here.  -jra 5/9/96
       (virtual-attribute
	(tformat "~athe ~a" preposition (second component-particulars))
	(denote-component-of-block-1 '*current-computation-frame* " of "))
       (rule-scan-interval
	(tformat "~athe scan-interval" preposition)
	(denote-component-of-block-1 '*current-computation-frame* " of "))
       (simulation-initial-value
	(tformat "~athe simulation-initial-value" preposition)
	(denote-component-of-block-1 '*current-computation-frame* " of "))
       #+development
       (otherwise
	(error "Unknown component part accessor ~S." component-particulars))))))

;; The cell-array-element handler is ignoring its preposition argument.  -jra
;; 5/15/91 (Which is fine, so far, since these only appear as the top level component
;; form. - ben 5/30/91)




;;; `Denote-cell-array-element' is a method that should be defined on any subclass
;;; of block that utilizes cell arrays.  It is used to generate a user friendly denotation
;;; for the block given a cell index.  It takes the block, the cell-index, and a flag
;;; as arguments.  The flag indicates if the denotation for the block it's self should
;;; be included.

(def-generic-method denote-cell-array-element (block cell-index include-denotation-for-block)
  )



;;; The macro `reclaim-component-particulars' takes a CP and reclaims it, and
;;; the macro `copy-component-particulars' copies them.  Note that at the
;;; moment, CPs are all slot values, but this may not be the case in the future,
;;; so the abstractions should always be used when copying or reclaiming them.

(defmacro reclaim-component-particulars (component-particulars)
  `(reclaim-slot-value ,component-particulars))

(defmacro copy-component-particulars (component-particulars)
  `(copy-for-slot-value ,component-particulars))

(def-class-method denote-cell-array-element
		  (root component-particulars
			include-component-particulars-for-block)
  (declare (ignore 
	     #-development root
	     component-particulars
	     include-component-particulars-for-block))
  #+development
  (cerror
    "Continue"
    "We are missing the denote-cell-array-element method on the class ~S"
    (class root))
  (twrite-string "some computation")
  (denote-component-of-block-1 '*current-computation-frame* " of "))




;;; The function `write-status-of-component-particulars' is charged with writing
;;; OK, INCOMPLETE, etc.  for the component.  But since are not currently using
;;; status for any components in the system it doesn't bother to do anything.

(defun write-status-of-component-particulars (component-particulars status)
  (declare (ignore component-particulars status))
  nil)




;;; The remainder of this section is for utility functions for each of the
;;; different types of component-particular.

;;; The macro `make-attribute-component-particulars' takes an attribute name and
;;; a further component particular.  This further component particular is for
;;; the case where the attribute is not directly on the relevant block, but is
;;; on a component of it.  The macros `attribute-component-particulars-p',
;;; `attribute-component-particulars-attribute-name', and `attribute-component-
;;; particulars-further-component?' test if something is an attribute component
;;; particular, and extract the components.

(defmacro make-attribute-component-particulars
    (attribute-name defining-class further-component?)
  `(slot-value-list
     'attribute ,attribute-name ,defining-class ,further-component?))

;;; The macro `reclaim-attribute-component-particulars-without-recursion'
;;; reclaims the given attribute-component-particulars, but without reclaiming
;;; any further nested component within it.

(defmacro reclaim-attribute-component-particulars-without-recursion
    (attribute-component-particulars)
  (let ((it (gensym)))
    `(let* ((,it ,attribute-component-particulars))
       (reclaim-slot-value-list-given-tail ,it (cdddr-of-conses ,it)))))

(def-substitution-macro attribute-component-particulars-p (thing)
  (and (consp thing)
       (eq (car-of-cons thing) 'attribute)))

(defmacro attribute-component-particulars-attribute-name
    (attribute-component-particulars)
  `(second-of-long-enough-list ,attribute-component-particulars))

(defmacro attribute-component-particulars-defining-class
    (attribute-component-particulars)
  `(third-of-long-enough-list ,attribute-component-particulars))

(defmacro attribute-component-particulars-further-component?
	  (attribute-component-particulars)
  `(fourth-of-long-enough-list ,attribute-component-particulars))

(defmacro with-attribute-component-particulars
    (((attribute-name defining-class further-component)
      attribute-component-particulars)
     &body body)
  (let ((cons-var (gensym)))
    `(let* ((,cons-var (cdr-of-cons ,attribute-component-particulars))
	    (,attribute-name (car-of-cons ,cons-var))
	    (,defining-class
		(progn (setq ,cons-var (cdr-of-cons ,cons-var))
		       (car-of-cons ,cons-var)))
	    (,further-component (cadr-of-conses ,cons-var)))
       ,@body)))

		      
	   




;;; The macro `make-aliased-attribute-component-particulars' takes a slot alias
;;; name, an actual name for the slot, the defining class for the slot, and
;;; further component particulars.  It returns a newly consed component
;;; particulars encapsulating this information.  The macro
;;; `aliased-attribute-component-particulars-p' takes a component particular and
;;; tests if it specifies an aliased system attribute.  The macro
;;; `aliased-attribute-alias' takes an aliased attribute component particular
;;; and returns the alias name.  The macro `aliased-attribute-actual-attribute'
;;; takes an aliased attribute component particular and returns the actual
;;; attribute name.  The macro `aliased-attribute-defining-class' takes an
;;; aliased attribute component particular and returns the defining class of the
;;; actual slot.  The macro `aliased-attribute-futher-particulars' takes an
;;; aliased attribute particulars and returns the further component particulars
;;; nested within it.

(defmacro make-aliased-attribute-component-particulars
    (alias attribute-name defining-class further-particulars)
  `(slot-value-list
     'aliased-attribute ,alias ,attribute-name ,defining-class ,further-particulars))

(def-substitution-macro aliased-attribute-component-particulars-p
    (component-particulars)
  (and (consp component-particulars)
       (eq (car-of-cons component-particulars) 'aliased-attribute)))

(defmacro aliased-attribute-alias (aliased-attribute-particulars)
  `(second-of-long-enough-list ,aliased-attribute-particulars))

(defmacro aliased-attribute-actual-attribute (aliased-attribute-particulars)
  `(third-of-long-enough-list ,aliased-attribute-particulars))

(defmacro aliased-attribute-defining-class (aliased-attribute-particulars)
  `(fourth-of-long-enough-list ,aliased-attribute-particulars))

(defmacro aliased-attribute-further-particulars (aliased-attribute-particulars)
  `(fifth-of-long-enough-list ,aliased-attribute-particulars))

(defmacro with-aliased-attribute-component-particulars
    (((alias attribute-name defining-class further-particulars)
      aliased-attribute-component-particulars)
     &body body)
  (let ((cons-var (gensym)))
    `(let* ((,cons-var (cdr-of-cons ,aliased-attribute-component-particulars))
	    (,alias (car-of-cons ,cons-var))
	    (,attribute-name
	       (progn (setq ,cons-var (cdr-of-cons ,cons-var))
		      (car-of-cons ,cons-var)))
	    (,defining-class
		(progn (setq ,cons-var (cdr-of-cons ,cons-var))
		       (car-of-cons ,cons-var)))
	    (,further-particulars (cadr-of-conses ,cons-var)))
       ,@body)))
    




;;; The macro `make-element-component-particulars' takes an element index and a
;;; further component.  The macros `element-component-particulars-p' and
;;; `element-component-particulars-index', and
;;; `element-component-particulars-further-component' test if something is an
;;; element component particular, and extract the components.

(defmacro make-element-component-particulars (element-index further-component)
  `(slot-value-list 'element ,element-index ,further-component))

(def-substitution-macro element-component-particulars-p (thing)
  (and (consp thing) (eq (car-of-cons thing) 'element)))

(defmacro element-component-particulars-index
    (element-component-particulars)
  `(cadr-of-conses ,element-component-particulars))

(defmacro element-component-particulars-further-component
    (element-component-particulars)
  `(caddr-of-conses ,element-component-particulars))

(defmacro with-element-component-particulars
    (((index further-component) element-component-particulars)
     &body body)
  (let ((cons-var (gensym)))
    `(let* ((,cons-var (cdr-of-cons ,element-component-particulars))
	    (,index (car-of-cons ,cons-var))
	    (,further-component (cadr-of-conses ,cons-var)))
       ,@body)))






;;;; Place References




;;; Place references are evaluation values which are used to denote locations
;;; which hold values or may be modified by conclude and change actions.  Place
;;; references denote their locations by holding 1) a component particular, 2) a
;;; frame, place reference, or symbol which is the base from which the component
;;; particular further specifies a location, and 3) a frame serial number to
;;; validate the existence of the held frame, if any.

;;; These operations are provided upon place references, additional details are
;;; outlined below.
;;;   make-evaluation-place-reference-to-place <particulars> <block-or-symbol>
;;;   evaluation-place-reference-p <place-reference>
;;;   evaluation-place-reference-eql <place-reference>
;;;   copy-evaluation-place-reference <place-reference>
;;;   reclaim-evaluation-place-reference <place-reference>
;;;   evaluation-place-reference-valid-p <place-reference>


;;; These operations provide access to the embedded state stored in a place
;;; reference.  Note that evaluation-place-reference-block-or-symbol can also
;;; hold a nested place reference.
;;;   evaluation-place-reference-block-or-symbol <place-reference>
;;;   evaluation-place-reference-component-particulars <place-reference>

(def-evaluation-value place-reference)

(def-substitution-macro reclaim-if-evaluation-place-reference (thing)
  (when (evaluation-place-reference-p thing)
    (reclaim-evaluation-place-reference thing)))



;;; The structure `place-reference-internals' is used to hold the components of
;;; a part reference.  Note that it is not named, and so has no predicate.

(def-structure (place-reference-internals
		 (:type vector)
		 (:constructor
		   make-place-reference-internals
		   (place-reference-internals-particulars
		     place-reference-internals-block-or-symbol
		     place-reference-internals-frame-serial-number)))
  (place-reference-internals-particulars
    nil :reclaimer reclaim-component-particulars)
  (place-reference-internals-block-or-symbol
    nil :reclaimer reclaim-if-evaluation-place-reference)
  (place-reference-internals-frame-serial-number nil :reclaimer reclaim-frame-serial-number))

(def-substitution-macro copy-if-evaluation-place-reference (thing)
  (if (evaluation-place-reference-p thing)
      (copy-evaluation-place-reference thing)
      thing))

(defun-simple copy-place-reference-internals (place-reference-internals)
  (make-place-reference-internals
    (copy-component-particulars
      (place-reference-internals-particulars place-reference-internals))
    (copy-if-evaluation-place-reference
      (place-reference-internals-block-or-symbol place-reference-internals))
    (copy-frame-serial-number (place-reference-internals-frame-serial-number place-reference-internals))))




;;; The function `make-evaluation-place-reference-to-place' takes a component
;;; particular and a block or symbol and returns a newly allocated place
;;; reference containing those elements.  Note that the given component
;;; particular is encorporated into the returned place reference and so gets
;;; reclaimed with the place reference.

(defun-simple make-evaluation-place-reference-to-place (particulars block-or-symbol)
  (make-evaluation-place-reference
    (make-place-reference-internals
      particulars
      block-or-symbol
      (copy-frame-serial-number (current-frame-serial-number)))))




;;; The macro `redirect-place-reference' takes a place reference and a new
;;; component particulars.  This function will modify the given
;;; component-particulars so that the place reference now points to the new
;;; location.  It is the responsibility of the caller to either have already
;;; reclaimed the component particulars in the place reference to to have
;;; incorporated them in the new component particulars.

(defmacro redirect-place-reference (place-reference new-component-particulars)
  `(setf (place-reference-internals-particulars
	   (evaluation-place-reference-value ,place-reference))
	 ,new-component-particulars))

(defmacro evaluation-place-reference-component-particulars (place-reference)
  `(place-reference-internals-particulars
     (evaluation-place-reference-value ,place-reference)))

(defmacro evaluation-place-reference-block-or-symbol (place-reference)
  `(place-reference-internals-block-or-symbol
     (evaluation-place-reference-value ,place-reference)))

(defun-simple evaluation-place-reference-valid-p (place-reference)
  (let* (#-(and lispworks (not chestnut-3))
         (internals (evaluation-place-reference-value place-reference))
         #+(and lispworks (not chestnut-3))
         (internals 
            (if (consp place-reference)
                (evaluation-place-reference-value place-reference)
                place-reference))
	 (block-or-symbol
	   (place-reference-internals-block-or-symbol internals)))
    (or (symbolp block-or-symbol)
        (evaluation-structure-p block-or-symbol)
	(and (framep block-or-symbol)
	     (frame-has-not-been-reprocessed-p
	       block-or-symbol
	       (place-reference-internals-frame-serial-number internals)))
	(evaluation-place-reference-valid-p block-or-symbol))))

(def-evaluation-value-reclaimer place-reference
  (reclaim-place-reference-internals-macro
    (evaluation-place-reference-value place-reference)))

(def-evaluation-value-copier place-reference
  (make-evaluation-place-reference
    (copy-place-reference-internals
      (evaluation-place-reference-value place-reference))))


(def-evaluation-value-validator place-reference (frame-serial-number)
  (declare (ignore frame-serial-number))
  (cond ((not (evaluation-place-reference-valid-p place-reference))
	 (reclaim-evaluation-place-reference place-reference)
	 nil)
	(t
	 place-reference)))

;;; The comparitor for place references will always return NIL for now.  Before
;;; this could be accurately coded we would have to have equality predicates on
;;; component particulars.  The major problem with these would be false
;;; negatives, where two different pathways lead to the same location.

(def-evaluation-value-comparitor place-reference
  (declare (ignore place-reference-1 place-reference-2))
  nil)

(def-evaluation-value-writer place-reference
  (cond
    ((not (evaluation-place-reference-valid-p place-reference))
     (denote-component-of-block
       nil
       (evaluation-place-reference-component-particulars place-reference))
     (twrite-string " of <deleted item>"))
    ((type-specification-type-p
      (evaluation-place-reference-block-or-symbol place-reference)
      '(place-reference))
     (twrite-string "<a reference to a reference>"))
    (t
     (denote-component-of-block
      t
      (evaluation-place-reference-component-particulars place-reference)
      (evaluation-place-reference-block-or-symbol place-reference)))))
