;;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: USER -*-
(in-package "USER")

;;;; Module rdb (relational database engine)
;;;
;;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;;  All Rights Reserved.
;;;
;;;; Author: Mark E. Staknis
;;;
;;;; Description:
;;;     Functions and macros in this file implement a simple engine for a
;;;   relational database management system (rdb).  To uniquely characterize
;;;   the functions and macros, they are prefixed with "rdb-".
;;;   The functions and macros provide conventional relational operations
;;;   such as project, select, and join. The external interface (API)
;;;   is described more fully below.
;;;
;;;; External Interface:
;;;     The functions and macros below constitute the supported API of the
;;;   this module.  For more detailed descriptions, see the functions
;;;   themselves.  Other included functions and macros are for internal
;;;   use only and are subject to change or removal and so should not be
;;;   referenced externally. 
;;;  
;;;   rdb-attributes (relation): Returns attribute list. 
;;;   rdb-table (relation): Returns list of rows.
;;;   rdb-attribute-to-index (attribute relation): Returns index of attribute.
;;;   rdb-copy-relation (relation): Returns a copy of the relation.
;;;   rdb-rename-attributes (attribute-pair-list relation): Destructively
;;;     changes first attribute name in pair to second for each attribute.
;;;   rdb-select-rows (value-attribute-pair-list relation): Returns new
;;;     relation with rows whose values match on all value-attribute pairs.
;;;   rdb-select-row-value (attribute value-attribute-pair-list relation):
;;;     Returns value of attribute in first row that matches all
;;;     value-attribute pairs.
;;;   rdb-select-rows-with-or (value-list-attribute-pair-list relation):
;;;     Returns rows whose attributes match on any value in the value list;
;;;     essentially the conjunction of attributes for disjunction of values
;;;   rdb-select-least-row-value (attribute selection-attribute-list relation):
;;;     Returns value of attribute in row whose values are least for the
;;;     given attributes.
;;;   rdb-select-least-row (attribute-list relation): Returns row whose values
;;;     are least for given attributes.
;;;   rdb-attribute-value-of-first-row (attribute relation): Returns value
;;;     of attribute in the first row.
;;;   rdb-project-row (index-list row):  Returns new row with values chosen
;;;     by the indices.
;;;   rdb-project-relation (projection-attributes relation): Returns new
;;;     relation that is the projection on the listed attributes. 
;;;   rdb-column-to-list (attribute relation): Returns a list of values in
;;;     the column specified by attribute.
;;;   rdb-append-relation (relation1 relation2): Returns a new relation with
;;;     rows of relation2 appended to those of relation1.
;;;   rdb-append-table-to-relation (table relation): Returns a copy of relation
;;;     with the rows of table appended to it.
;;;   rdb-join-relations (attribute-pair-list relation1 relation2): Returns
;;;     a new relation that is the natural join on the given pairs of
;;;     attributes.
;;;   rdb-sort-relation (attribute-list relation): Destructively sorts
;;;     the rows in the relation by the given attributes.
;;;   rdb-delete-adjacent-duplicate-rows (attribute-list relation):
;;;     Destructively deletes all but first of rows that match on attributes.
;;;   rdb-create-relation (attribute-list):  Returns new relation with
;;;     given attributes and an empty table.
;;;   rdb-add-row-to-relation (row relation): Destructively adds row to table.
;;;
;;;; Notes:
;;;     The data type upon which most functions operate is the "relation".
;;;   Conceptually, a relation is a table of named columns.  For example,
;;;         a       b        c             (attributes)
;;;       -----------------------
;;;        12   |   9    |   6             (row 1)
;;;         4   |  45    |   0             (row 2)
;;;        11   |   6    |  10             (row 3)
;;;   is a relation with attributes a, b, and c and three rows.  A relation's
;;;   implementation consists of two parts: an attribute list and a table of
;;;   rows (tuples).  The attribute list contains attribute names (symbols).
;;;   The table is a list of rows, and within which each row is a list of
;;;   values. The ordering of values in a row corresponds to the ordering of
;;;   attributes in the attribute list.






;;; macro: rdb-attributes
;;; arguments:
;;;   relation: a relation (required)
;;; return value: the attribute list of the relation
;;; description:  Extracts and returns (a pointer to) the relation's attribute 
;;;     list.
;;; scope: external

(defmacro rdb-attributes (relation)
  `(first ,relation))




;;; macro: rdb-table
;;; arguments:
;;;   relation: a relation (required)
;;; return value: the table of rows of the relation
;;; description:  Extracts and returns (a pointer to) the relation's table
;;;     of rows.
;;; scope: external

(defmacro rdb-table (relation)
  `(second ,relation))




;;; function: rdb-equal
;;; arguments:
;;;   arg1, arg2: arguments of any type
;;; return value: nil if arguments differ, non-nil if they're the same
;;; description: This is means of determining whether two arguments are equal
;;;     for purposes of the database.  When both arguments are of the same
;;;     primitive type (symbol, string, or number), they are compared using the
;;;     built-in equality function.  If the arguments differ in type, they are
;;;     converted to and compared as strings.
;;; scope: internal use by rdb only

(defun rdb-equal (arg1 arg2)
  (cond
     ( (and (symbolp arg1) (symbolp arg2))
      (eq arg1 arg2))
     ( (and (stringp arg1) (stringp arg2))
      (string= arg1 arg2))
     ( (and (numberp arg1) (numberp arg2))
      (= arg1 arg2))
     (t (string=
	  (rdb-lessp-convert-to-string arg1)
	  (rdb-lessp-convert-to-string arg2)))))




;;; function: rdb-lessp
;;; arguments:
;;;   arg1, arg2: arguments of any type
;;; return value: non-nil if arg1 is strictly less than arg2, nil if not
;;; description: This is a means of determining whether one argument is less
;;;     than another for purposes of the database.  When both arguments are
;;;     numeric, they are compared numerically, otherwise they are converted to
;;;     strings and compared lexographically.  All non-string types are treated
;;;     as strictly lower-case and are converted to lower-case before
;;;     comparison.
;;; scope: internal use by rdb only

(defun rdb-lessp (arg1 arg2)
  (if (and (numberp arg1) (numberp arg2))
      (< arg1 arg2)
      (string< (rdb-lessp-convert-to-string arg1)
	       (rdb-lessp-convert-to-string arg2))))

(defvar *rdb-lessp-value* (make-hash-table :test 'equal))

(defvar *optimize* t)

(defun rdb-lessp-convert-to-string (arg)
  (if (not *optimize*)
      (if (stringp arg)
	  arg
	  (string-downcase (princ-to-string arg)))
      (typecase arg
	(string arg)
	(symbol (or (get arg 'rdb-lessp-value)
		    (setf (get arg 'rdb-lessp-value)
			  (string-downcase (princ-to-string arg)))))
	(t (or (gethash arg *rdb-lessp-value*)
	       (setf (gethash arg *rdb-lessp-value*)
		     (string-downcase (princ-to-string arg))))))))
	    


;;; function: rdb-rows-equal-for-index-pairs
;;; arguments:
;;;   index-pair-list: A list of pairs of indices (required)
;;;   row1, row2: rows of elements (required)
;;; return value: t or nil
;;; description:  Compares corresponding elements of row1 and row2 and
;;;   returns true if the the corresponding elements are equal and false if
;;;   not.  Element correspondence is determined by the pairs in i-list. E.g.,
;;;   if i-list is ((1 2) (5 3)) then element 1 of row1 is compared to element
;;;   2 of row2, and element 5 of row1 is compared to element 3 of row2.
;;; scope: internal use by rdb only

(defun rdb-rows-equal-for-index-pairs (index-pair-list row1 row2)
  (loop for index-pair in index-pair-list
	always (rdb-equal
                 (nth (first index-pair) row1)
                 (nth (second index-pair) row2))))




;;; function: rdb-rows-equal-for-indices
;;; arguments:
;;;   index-list: A list of pairs of indices (required)
;;;   row1, row2: rows of elements (required)
;;; return value: t or nil
;;; description: Elements of row1 and row2 are compared for equality on
;;;   indices in index-list.  t is returned if all are equal, nil otherwise.
;;; scope: for internal use by rdb only

(defun rdb-rows-equal-for-indices (index-list row1 row2)
  (loop for index in index-list
	always (rdb-equal
		 (nth index row1)
		 (nth index row2))))




;;; function: rdb-rows-less-for-indices-p
;;; arguments:
;;;   index-list: A list of pairs of indices (required)
;;;   row1, row2: rows of elements (required)
;;; return value: t or nil
;;; description: Elements of row1 and row2 are compared on indices in
;;;   index-list, with the first element of index-list primary, the second
;;;   element secondary, and so on. t is returned if the first row is less
;;;   than the second and nil otherwise
;;; scope: for internal use by rdb only

(defun rdb-rows-less-for-indices-p (index-list row1 row2)
  (loop
    for index in index-list
    if (rdb-lessp (nth index row1) (nth index row2))
      return t
    if (rdb-lessp (nth index row2) (nth index row1))
      return nil
    finally (return nil)))




;;; macro: rdb-lambda-rows-equal-for-indices
;;; arguments:
;;;   index-list: a list of indices
;;; return value: a lambda expression that takes two rows as arguments and,
;;;   when invoked, compares the two rows for equality on the indexed members
;;; description: This provides the function to determine whether two rows match
;;;   on a set of attributes. The macro could, for example, be used as the
;;;   :test argument to delete-duplicates.
;;; scope: internal use by rdb only

(defmacro rdb-lambda-rows-equal-for-indices (index-list)
  `#'(lambda (row1 row2)
       (loop
	 for index in ,index-list
	 always (rdb-equal (nth index row1) (nth index row2)))))




;;; macro: rdb-lambda-rows-less-on-indices-p
;;; arguments:
;;;   index-list: a list of indices
;;; return value: a lambda expression that takes two rows as arguments and,
;;;     when invoked, compares the two rows on the indexed members
;;; description: This provides the function needed by sort to
;;;     determine whether one row is "less than" another.  The argument
;;;     index-list should contain a key that is sufficient to uniquely identify
;;;     a row.  The order of indices determines the order of comparison.  For
;;;     sorting, the first index becomes the primary sort key, the second index
;;;     becomes the secondary sort key, etc.
;;; scope: internal use by rdb only

(defmacro rdb-lambda-rows-less-on-indices-p (index-list)
  `#'(lambda (row1 row2)
       (loop
	 for index in ,index-list
	 if (rdb-lessp (nth index row1) (nth index row2))
	   return t
	 if (rdb-lessp (nth index row2) (nth index row1))
	   return nil
	 finally (return nil))))




;;; function: rdb-attribute-to-index
;;; arguments:
;;;   attribute: an attribute, which is a symbol (required)
;;;   relation: a relation (required)
;;; return value: an index, or if an error occurs, a message is printed
;;;   and -1 is returned
;;; description: Searches the attribute list of the relation and
;;;   returns the index of the entry that contains the attribute.
;;; scope: external

(defun rdb-attribute-to-index (attribute relation)
  (loop
    with attribute-list = (rdb-attributes relation)
    for i from 0
    for element in attribute-list
    when (eq attribute element)
      do (return i)
    finally
      (error "The attribute ~a is not in the attribute list." attribute)))




;;; function: rdb-copy-relation
;;; arguments:
;;;   relation:  a relation (required)
;;; return value: a copy of the relation
;;; description:  returns a copy of the relation with new copies of the
;;;     attribute list and table of rows (the rows themselves are not copied)
;;; scope: external

(defun rdb-copy-relation (relation)
  (list
    (copy-list (rdb-attributes relation))
    (copy-list (rdb-table relation))))




;;; function: rdb-rename-attributes
;;; arguments:
;;;   attribute-pair-list: a list of pairs of attribute names (required)
;;;   relation:  a relation (required)
;;; return value: the same relation, but with changed modified attribute names
;;; description: destructively changes the first attribute name of each pair
;;;     to the second
;;; scope: external
;;; bugs: For an attribute-pair-list such as ((x y) (y z)), x will be renamed
;;;     to y, which will then be renamed to z

(defun rdb-rename-attributes (attribute-pair-list relation)
  (loop
    for pair in attribute-pair-list
    do (nsubst
	 (second pair)
	 (first pair)
	 (rdb-attributes relation))
    finally (return relation)))
	


    
;;; function: rdb-select-rows
;;; arguments:
;;;   value-attribute-pair-list:  a list of pairs whose first member is a value
;;;     and whose second member is an attribute name (required)
;;;   relation:  a relation (required)
;;; return value: a new relation containing the selected rows
;;; description:  performs a "select" operation on the relation by constructing
;;;   a new relation from the rows whose values "match" the given attributes.
;;;   This is essentially selection for the conjunction of attribute-value
;;;   pairs.
;;; scope: external

(defun rdb-select-rows (value-attribute-pair-list relation)
  (list
    (copy-list (rdb-attributes relation))
    (loop
      with value-index-pair-list
      = (loop
	  for pair in value-attribute-pair-list
	  collect (list
		    (first pair)
		    (rdb-attribute-to-index (second pair) relation)))
      for row in (rdb-table relation)
      if (loop                       ; if the values match on all attributes
	   for pair in value-index-pair-list
	   always (rdb-equal (first pair) (nth (second pair) row)))
	collect row)))               ; then select the row




;;; function: rdb-select-row-value
;;; arguments:
;;;   attribute: the attribute whose value is to be returned
;;;   value-attribute-pair-list:  a list of pairs whose first member is a value
;;;     and whose second member is an attribute name (required)
;;;   relation:  a relation (required)
;;; return value: the value of the attribute in the first matching row or nil
;;;   if no row matches.
;;; description: This does a very efficient fetch of a value from a relation.
;;;   It finds the first row of relation that matches the selection values,
;;;   then it returns the value of the specified attribute in that row.
;;; scope: external

(defun rdb-select-row-value (attribute value-attribute-pair-list relation)
  (loop
    with attribute-index
    = (rdb-attribute-to-index attribute relation)
    with value-index-pair-list
    = (loop
	for pair in value-attribute-pair-list
	collect (list
		  (first pair)
		  (rdb-attribute-to-index (second pair) relation)))
    for row in (rdb-table relation)
    if (loop                       ; if the values match on all attributes
	 for pair in value-index-pair-list
	 always (rdb-equal (first pair) (nth (second pair) row)))
      return (nth attribute-index row)
    finally (return nil)))
	


    
;;; function: rdb-select-rows-with-or
;;; arguments:
;;;   value-list-attribute-pair-list:  a list of pairs whose first member is
;;;     list of values and whose second member is an attribute name (required)
;;;   relation:  a relation (required)
;;; return value: a new relation containing the selected rows
;;; description:  performs a "select" operation on the relation by constructing
;;;   a new relation from the rows whose values "match" the given attributes
;;;   for any value in the list.  This would typically be used for a single
;;;   attribute (A) and multiple values (V1, V2,...) to find all rows for
;;;   which A=V1 OR A=V2 OR ...  When multiple attributes are provided, this
;;;   is a conjunction of checks of whether each attribute contains a
;;;   disjunction of values.
;;; scope: external

(defun rdb-select-rows-with-or (value-list-attribute-pair-list relation)
  (list
    (copy-list (rdb-attributes relation))
    (loop
      with value-index-pair-list
      = (loop
	  for pair in value-list-attribute-pair-list
	  collect (list
		    (first pair)
		    (rdb-attribute-to-index (second pair) relation)))
      for row in (rdb-table relation)
      if (loop                       ; if the values match on all attributes
	   for pair in value-index-pair-list
	   for row-value = (nth (second pair) row)
	   always
		(loop for value in (first pair) ; for at least one value each
		      thereis (rdb-equal value row-value)))
	collect row)))               ; then select the row




;;; function: rdb-select-least-row-value
;;; arguments:
;;;   attribute: the attribute whose value is to be returned
;;;   selection-attribute-list: the list of attributes on which comparison is
;;;     to be made (required)
;;;   relation:  a relation (required)
;;; return value: the specified value in the least row
;;; description: Uses rdb-select-least-row to find the row with the minimal
;;;   value on the selection attributes, then returns the value of
;;;   value-attribute within that row.
;;; scope: external

(defun rdb-select-least-row-value (attribute
				    selection-attribute-list
				    relation)
  (nth
    (rdb-attribute-to-index attribute relation)
    (rdb-select-least-row selection-attribute-list relation)))




;;; function: rdb-select-least-row
;;; arguments:
;;;   attribute-list: a list of attributes on which the comparison is to
;;;     be made (required)
;;;   relation:  a relation (required)
;;; return value: the row with the least value of the attribute
;;; description: Iterates through the rows of "relation" and returns the
;;;   row whose values are least for the given attribute list (using
;;;   rdb-rows-less-for-indices-p for comparison, which uses the first
;;;   entry for primary comparison, the second for secondary comparison, etc.
;;;   If multiple least rows exist, the first is returned.
;;; scope: external

(defun rdb-select-least-row (attribute-list relation)
  (loop
    with attribute-index-list
    = (loop
	for attribute in attribute-list
	collect (rdb-attribute-to-index attribute relation))
    with table = (rdb-table relation)
    with least-row = (first table)
    for row in table
    if (rdb-rows-less-for-indices-p attribute-index-list row least-row)
      do
	(setf least-row row)
    finally (return least-row)))




;;; function: rdb-attribute-value-of-first-row
;;; arguments:
;;;   attribute: an attribute of the relation (required)
;;;   relation:  a relation (required)
;;; return value: an attribute's value or nil
;;; description: Returns the value of the specified attribute in the first
;;;   row of the relation.  If the relation's table is empty, nil is returned.
;;; notes: This can be useful for accessing attribute values by name if the
;;;   relation contains a single row or if the relation is sorted so that the
;;;   row of interest is first.
;;; scope: external

(defun rdb-attribute-value-of-first-row (attribute relation)
  (nth
    (rdb-attribute-to-index attribute relation)
    (first
      (rdb-table relation))))




;;; function: rdb-project-row
;;; arguments:
;;;   index-list: a list of indices to be projected (required)
;;;   row:  a list of elements (required)
;;; return value: a new list containing the projected elements
;;; description: A new row is created whose elements are the elements of
;;;   "row" whose indices are in "indices".  Elements in the new row are
;;;   in the order given in "indices".
;;; scope: external

(defun rdb-project-row (index-list row)
  (loop
    for index in index-list
    collect (nth index row)))




;;; function: rdb-project-relation
;;; arguments:
;;;   projection-attributes: a list of attributes to be projected (required)
;;;   relation:  a relation (required)
;;; return value: a new relation containing the projected rows
;;; description: creates a new relation whose rows are "subsets" of the rows
;;;   of rel, where the "subset" is the values of attributes in attr-list.
;;; scope: external

(defun rdb-project-relation (projection-attributes relation)
  (list                                      ; Create new relation with
    (copy-list projection-attributes)        ;  an attribute list
    (loop                                    ;  and a table.
      with index-list                        ; Make list of indices to project.
      = (loop
	for attribute in projection-attributes
	collect (rdb-attribute-to-index attribute relation))
      for row in (rdb-table relation)              ; For each row
      collect (rdb-project-row index-list row))))  ; create a new one.




;;; function: rdb-column-to-list
;;; arguments:
;;;   attribute: an attribute name (required)
;;;   relation: a relation (required)
;;; return value: a list containing the values of the attribute for each row
;;; scope: external

(defun rdb-column-to-list (attribute relation)
  (loop
    with attribute-index
    = (rdb-attribute-to-index attribute relation)
    for row in (rdb-table relation)
    collect (nth attribute-index row)))




;;; function: rdb-append-relation
;;; arguments:
;;;   relation1, relation2:  relations (required)
;;; return value: a new relation containing the tables of both relations 
;;; description: creates a new relation whose table is the table of relation2
;;;     appended to the table of relation1
;;; scope: external

(defun rdb-append-relation (relation1 relation2)
  (list
    (copy-list (rdb-attributes relation1))
    (append 
      (rdb-table relation1)
      (rdb-table relation2))))




;;; function: rdb-append-table-to-relation
;;; arguments:
;;;   table: a table of rows with the attributes of the relation (required)
;;;   relation: a relation (required)
;;; return value: a new relation
;;; description: a new relation is created that is identical to the relation
;;;   with the rows of the table appended.
;;; scope: external

(defun rdb-append-table-to-relation (table relation)
  (list
    (copy-list (rdb-attributes relation))
    (append 
      (rdb-table relation)
      table)))




;;; function: rdb-join-relations
;;; arguments:
;;;   attribute-pair-list: a list of attribute pairs on which to join the
;;;     relations
;;;   r1, r2:  relations (required)
;;; return value: a new relation containing the natural join of the relations
;;; description: creates a new relation that is the natural join of the
;;;   relations.  I.e., suppose that a1 and a2 are the attribute lists of
;;;   relation1 and relation2, respectively.  Suppose that a2' is a2 with the
;;;   join attributes removed.  Then the new attribute list is a1+a2'.  The
;;;   new table consists of the Cartesian product of the tables with rows
;;;   chosen that match on the attribute pairs.  (See any database text for
;;;   the concepts.)
;;; scope: external

(defun rdb-join-relations (attribute-pair-list r1 r2)
  (loop
    with new-table = nil             ; Create an initially empty table
    with index-pair-list             ; Create a list of pairs of indices
    = (loop                          ; from the list of pairs of attributes
        for pair in attribute-pair-list
        collect (list
		  (rdb-attribute-to-index (first pair) r1)
		  (rdb-attribute-to-index (second pair) r2)))
    with r2-non-join-attributes      ; Create list of the attributes of r2
    = (loop                          ; that are not in the join-pair list
        with r2-join-attributes
        = (loop
	    for pair in attribute-pair-list
	    collect (second pair))
        for attribute in (rdb-attributes r2)
        if (not (member attribute r2-join-attributes))
	  collect attribute)
    with r2-non-join-indices
    = (loop
        for attribute in r2-non-join-attributes
        collect (rdb-attribute-to-index attribute r2))
    for row1 in (rdb-table r1)       ; Cycle through the Cartesian product
    do (loop                         ; selecting rows that "join"
         for row2 in (rdb-table r2)
         if (rdb-rows-equal-for-index-pairs index-pair-list row1 row2)
	   do (push                  ; Unfortunately push reverses the expected
	        (append              ; order of rows in the table
	           row1
	           (rdb-project-row r2-non-join-indices row2))
	        new-table))
    finally (return (list             ; Build and return the new relation
		     (append (rdb-attributes r1) r2-non-join-attributes)
		     (reverse new-table)))))  ; "unreverse" the rows




;;; function: rdb-sort-relation
;;; arguments:
;;;   attribute-list: a list of attributes of the relation (required)
;;;   relation: a relation (required)
;;; return value: the relation with its table sorted by the list of attributes
;;; description: The rows of the table's relation are sorted by the
;;;    "sort keys" in the attribute list.  The first attribute is the primary
;;;    sort key, the second attribute is the secondary sort key, and so on.
;;;    The sort is destructive; i.e., the order of rows in the passed relation
;;;    will differ after sorting if sorting is needed.
;;; scope: external

(defun rdb-sort-relation (attribute-list relation)
  (let ((index-list (loop
		      for attribute in attribute-list
		      collect (rdb-attribute-to-index attribute relation))))
    (setf (rdb-table relation)
	  (sort
	    (rdb-table relation)
	    (rdb-lambda-rows-less-on-indices-p index-list)))    ; a macro
    relation))                   ; return a pointer to the relation




;;; function: rdb-delete-adjacent-duplicate-rows
;;; arguments:
;;;   attribute-list: a list of attributes on which to judge whether two rows
;;;     match (required)
;;;   relation: a relation (required)
;;; return value: the relation with adjacent duplicate rows deleted
;;; description: Each pair of adjacent rows is compared for equality on the
;;;   attributes in attribute-list.  If the rows match, the second of the two
;;;   rows is deleted from the relation.  This function is destructive; i.e.,
;;;   the passed relation is altered so that no adjacent duplicates remain.
;;; scope: external

(defun rdb-delete-adjacent-duplicate-rows (attribute-list relation)
  (loop
    with index-list
    = (loop
	for attribute in attribute-list
	collect (rdb-attribute-to-index attribute relation))
    with table = (rdb-table relation)
    with current-row = nil        ; initial value is unused
    with first-row = t
    for row in table              ; collect first unique occurrence of each row
    if (or
	 first-row                ; true first time through only
	 (not                     ; short-circuited first time through
	   (rdb-rows-equal-for-indices index-list row current-row)))
      do
	(setq first-row nil)
	(setq current-row row)
      and collect row into new-table
    finally
      (setf (rdb-table relation) new-table)    ; replace old table with new one
      (return relation)))




;;; function: rdb-create-relation
;;; arguments:
;;;   attribute-list: a list of attributes (required)
;;; return value: a relation with an empty table whose attributes are those
;;;   in attribute-list
;;; description: see return value
;;; scope: external

(defun rdb-create-relation (attribute-list)
  (list
    (copy-list attribute-list)
    ()))




;;; function: rdb-add-row-to-relation
;;; arguments:
;;;   row: a row (required)
;;;   relation: a relation (required)
;;; return value: the passed relation with the new row added at the end of
;;;   the table
;;; description: the row is destructively added to the table of the passed
;;;   relation and a pointer to the relation is returned.
;;; scope: external

(defun rdb-add-row-to-relation (row relation)
  (let
      ((table (rdb-table relation)))
    (progn
      (if table
	  (nconc table (list row))
	  (setf (rdb-table relation) (list row))) ; special case if empty
      relation)))
