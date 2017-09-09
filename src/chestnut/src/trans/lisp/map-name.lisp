;;; -*- Mode: Lisp; Package: TUTIL; Syntax: Common-Lisp -*-
;;;
;;; map-name -- name-mapping utility
;;;
;;; Author : Kim Barrett
;;; Date   : 28 December 1990
;;;
;;; Copyright (c) 1990, Chestnut Software, Inc.
;;;
;;; This facility is based on an earlier implementation written by John Gilson.

(in-package "TUTIL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/map-name.lisp,v $"
 "$Revision: 1.4 $"
 "$Date: 2009/08/10 00:00:00 $")

;;; The following defined names are considered to be part of the external
;;; interface to the facilities provided by the name mapper.  See the
;;; individual definitions for details.
;;;
;;;   WITH-C-NAME-TABLE
;;;   WITH-GLOBAL-C-NAME-TABLE
;;;   RECORD-GLOBAL-C-NAME
;;;   C-NAME-CONFLICT-P
;;;
;;;   STRING->C-NAME
;;;   STRING->LEGAL-C-NAME
;;;   STRING-CANONICALIZE-CASE
;;;   STRING-TRIM-STARS
;;;
;;; *** There should also be an interface defined for removing names.


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Character transformations
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; Only alphanumerics and underscore are permitted in C identifiers.
;;; *** These mappings are really too cryptic.  I think it would be better
;;; *** to spell the names of the characters out completely.

(defparameter *non-alphanumeric-char-mappings*
  '((#\tab "tab")
    (#\space "sp")
    (#\! "ex")
    (#\" "dq")
    (#\# "no")
    (#\$ "dol")
    (#\% "pct")
    (#\& "and")
    (#\' "qu")
    (#\( "op")
    (#\) "cp")
    (#\* "star")
    (#\+ "plus")
    (#\, "cm")
    (#\- "_")
    (#\. "dot")
    (#\/ "sl")
    (#\: "col")
    (#\; "sc")
    (#\< "lt")
    (#\= "eq")
    (#\> "gt")
    (#\? "qm")
    (#\backspace "bp")
    (#\page "page")
    (#\@ "at")
    (#\[ "obt")
    (#\\ "bs")
    (#\] "cbt")
    (#\^ "ct")
    (#\_ "_")
    (#\return "rt")
    (#\newline "nl")
    (#\` "bq")
    (#\{ "ob")
    (#\| "or")
    (#\} "cb")
    (#\~ "tl")
    (#\rubout "ro")
    (#\linefeed "lf")))

(defvar *upcase-non-alphanumeric-transforms*)
(defvar *downcase-non-alphanumeric-transforms*)

(defun initialize-non-alphanumeric-transforms ()
  (let ((upcase (make-array 256 :initial-element nil))
	(downcase (make-array 256 :initial-element nil)))
    (dolist (mapping *non-alphanumeric-char-mappings*)
      (let* ((char (car mapping))
	     (code (char-ascii-code char))
	     (transform (cadr mapping)))
	(setf (aref upcase code) (string-upcase transform))
	(setf (aref downcase code) (string-downcase transform))))
    (setf *upcase-non-alphanumeric-transforms* upcase)
    (setf *downcase-non-alphanumeric-transforms* downcase)
    nil))

(initialize-non-alphanumeric-transforms)

(defmacro translate-character (char case)
  `(aref (if (eq ,case :upcase)
	     *upcase-non-alphanumeric-transforms*
	     *downcase-non-alphanumeric-transforms*)
	 (char-ascii-code ,char)))

;;; TRANSFORM-FIRST-CHARACTER (internal)
;;;
;;; Handle some special transformations that are only relevent for the first
;;; character of an identifier.
;;;
;;; 1. Transform a leading underscore because identifiers with leading
;;; underscores are reserved to the C implementation's library under some
;;; conditions.  Rather than check to see if such a condition holds, we just
;;; always transform a leading underscore into something safe.
;;;
;;; 2. C identifiers may not begin with a digit, so if the first character is a
;;; digit, append a special prefix.
;;;
;;; 3. If the first character is not alphanumeric, then examine its
;;; transformation, to ensure that the transformation won't cause problems in
;;; the initial part of the sequence.

(defparameter *leading-digit-prefix* '("n" . "N"))
(defparameter *leading-underscore-prefix* '("us" . "US"))

(defvar *free-strings* nil)
(defvar *string-size* 120)

(eval-when (compile load eval)
(defparameter simple-string-element-type
  '#.(array-element-type ""))
(defparameter simple-string-type
  '(simple-array #.(array-element-type "") (*)))
)

(defmacro with-output-to-string--simple ((stream) &body forms)
  `(let ((,stream
	  (cons 0
		(or (pop *free-strings*)
		    (make-array
		     *string-size*
		     :element-type '#.simple-string-element-type)))))
     (progn ,@forms)
     (prog1 (subseq (cdr ,stream) 0 (car ,stream))
       (push (cdr ,stream) *free-strings*))))

(defun copy-stream-array (old old-size new-size)
  (declare (fixnum old-size new-size)
	   (type #.simple-string-type old))
  (incf new-size 4)
  (let ((new (make-array new-size
			 :element-type '#.simple-string-element-type)))
    (declare (type #.simple-string-type new))
    (dotimes (i old-size)
      (declare (fixnum i))
      (setf (aref new i) (aref old i)))
    (push old *free-strings*)
    new))

(defmacro increment-stream-size (stream incr)
  `(let* ((current-size (car ,stream))
	  (new-size (+ current-size ,incr))
	  (actual-size (array-dimension (cdr ,stream) 0)))
     (declare (fixnum current-size new-size actual-size))
     (setf (car ,stream) new-size)
     (when (> new-size actual-size)
       (setf (cdr ,stream)
	     (copy-stream-array (cdr ,stream) actual-size new-size)))
     new-size))

(defmacro write-char--simple (char stream)
  (once-only (char stream)
    `(let ((.index. (car ,stream)))
       (declare (fixnum .index.))
       (increment-stream-size ,stream 1)
       (setf (aref (the #.simple-string-type (cdr ,stream)) .index.)
	     (the #.simple-string-element-type ,char)))))

(defun write-string--simple (string stream &key
				    (start 0) (end (length string)))
  (declare (fixnum start end))
  (let* ((size (- end start))
	 (index (car stream)))
    (declare (fixnum size index))
    (increment-stream-size stream size)
    (let ((vector (cdr stream)))
      (declare (type #.simple-string-type vector))
      (dotimes (i size)
	(declare (fixnum i))
	(setf (aref vector (the fixnum (+ i index)))
	      (the #.simple-string-element-type
		   (aref string (the fixnum (+ i start))))))))
  nil)

(defun transform-first-character (string case stream &optional (start 0) end)
  (when (null end) (setf end (length string)))
  (if (<= end start)
      (values start nil)
      (let ((char (char string start)))
	(cond ((eql char #\_)
	       (let ((prefix *leading-underscore-prefix*))
		 (if (eq case :upcase)
		     (setf prefix (cdr prefix))
		     (setf prefix (car prefix)))
		 (write-string--simple prefix stream)
		 (values (1+ start) t)))
	      ((digit-char-p char)
	       (let ((prefix *leading-digit-prefix*))
		 (if (eq case :upcase)
		     (setf prefix (cdr prefix))
		     (setf prefix (car prefix)))
		 (write-string--simple prefix stream)
		 (values start t)))
	      ((alpha-char-p char) (values start nil))
	      (t
	       (let* ((prefix (translate-character char case))
		      (pend (length prefix)))
		 (if (zerop pend)
		     (transform-first-character string
						case
						stream
						(1+ start)
						end)
		     (multiple-value-bind (pstart needs-underscore)
			 (transform-first-character prefix case stream)
		       (if (<= pend pstart)
			   (values (1+ start) needs-underscore)
			   (progn
			     (when needs-underscore
			       (write-char--simple #\_ stream))
			     (write-string--simple prefix stream :start pstart)
			     (values (1+ start)
				     (not (eql (char prefix (1- pend))
					       #\_)))))))))))))

(defun make-legal-c-name (string case stream index end needs-underscore)
  (declare (fixnum end index))
  (unless (<= end index)
    (let ((char (char string index)))
      (if (alphanumericp char)
	  (let ((alpha-end (let ((i (1+ index)))
			     (declare (fixnum i))
			     (loop (when (>= i end) (return end))
				   (unless (alphanumericp (aref string i))
				     (return i))
				   (incf i)))))
	    (when needs-underscore (write-char--simple #\_ stream))
	    (write-string--simple string stream :start index :end alpha-end)
	    (make-legal-c-name string case stream alpha-end end t))
	  (transform-non-alphanumeric-char char
					   string
					   case
					   stream
					   (1+ index)
					   end
					   needs-underscore)))))

(defun transform-non-alphanumeric-char
    (char string case stream index end needs-underscore)
  (let* ((transform (translate-character char case))
	 (length (length transform)))
    (unless (zerop length)
      (when needs-underscore
	(setf needs-underscore nil)
	(unless (eql (char transform 0) #\_)
	  (write-char--simple #\_ stream)))
      (write-string--simple transform stream)
      (unless (eql (char transform (1- length)) #\_)
	(setf needs-underscore t)))
    (make-legal-c-name string case stream index end needs-underscore)))

;;; STRING->LEGAL-C-NAME (external)
;;;
;;; Convert string into a valid C identifier, transforming characters which
;;; are not valid in C identifiers into alternative sequences of valid
;;; characters.  The case argument is used to control case conversion of the
;;; transformed characters, so that such transformations follow the same case
;;; conventions as the string (it is assumed that any desired case conversions
;;; in the string have already been performed).  The case argument must be one
;;; of the possible values returned by STRING-CANONICALIZE-CASE as its second
;;; value.  The prefix argument is used to control certain transformations that
;;; are only necessary when the character will be the first character of the
;;; resulting identifier.  If prefix is a non-empty string then such
;;; transformations are suppressed.

(defun string->legal-c-name (string case prefix)
  (let ((length (length string)))
    (if (zerop length)
	string
	(with-output-to-string--simple (stream)
	  (let ((start 0)
		(needs-underscore nil))
	    (when (zerop (length prefix))
	      (multiple-value-setq (start needs-underscore)
		(transform-first-character string case stream)))
	    (make-legal-c-name string
			       case
			       stream
			       start
			       length
			       needs-underscore))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Converting a string to a C name
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; STRING->C-NAME (external)
;;;
;;; Compute a valid C identifier from the string, prefix, and suffix arguments,
;;; possibly with additional characters added to prevent conflicts with other
;;; names visible in the specified scope.
;;;
;;; Prefix and suffix must not contain any characters which are not valid in
;;; a C identifier.  No separation characters are inserted between the prefix
;;; or suffix and the valid identifier string computed from the string.  The
;;; :case argument is used to control case conversion of transformations.  It
;;; does not affect valid identifier characters present in the string.  The
;;; :symbol argument, if specified, may be used to compute a package name to
;;; add to the resulting identifier if there may be package conflicts.

(defun string->c-name (string globalp
			      &key (case (required-keyword :case))
			           (symbol nil)
				   (prefix "")
				   (suffix ""))
  (let ((c-name (string->c-name-aux string globalp case prefix suffix symbol)))
    (record-c-name c-name globalp)
    c-name))

(defun string->c-name-aux (string globalp case prefix suffix symbol)
  (cond ((null symbol)
	 (check-name-conflict (string->legal-c-name string case prefix)
			      globalp case prefix suffix))
	((package-qualification-needed symbol)
	 (handle-package-conflict string globalp case prefix suffix symbol))
	(t
	 (check-name-conflict (string->legal-c-name string case prefix)
			      globalp case prefix suffix symbol))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Handling symbols not accessible in current package
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; When the symbol associated with a name string is an interned symbol, but
;;; is not accessible from the current package, a package prefix gets added to
;;; the name string.

;;; Symbols accessible in these packages are always implicitly available,
;;; regardless of what the current package is.  Never generate package
;;; qualification for symbols accessible from one of these.

(defparameter *packages-implicitly-used*
  (list *tcl-package* *trun-package* *tx-package*
	*tclos-package* *tclos-run-package* *tclosx-package*))

(define-translator-parameter *always-use-package-qualification-p* nil)

(defun package-qualification-needed (symbol &optional (package *package*))
  (and (symbol-package symbol)
       (not (keywordp symbol))
       (flet ((accessible-in-package (symbol package)
		(multiple-value-bind (sym therep)
		    (find-symbol (symbol-name symbol) package)
		  (and therep (eq sym symbol)))))
	 (and (or *always-use-package-qualification-p*
		  (not (accessible-in-package symbol package)))
	      (dolist (p *packages-implicitly-used* t)
		(when (accessible-in-package symbol p) (return nil)))))))
				     
(defun handle-package-conflict (string global case prefix suffix symbol)
  (check-name-conflict (add-package-prefix string case prefix symbol)
		       global
		       case
		       prefix
		       suffix))

(defun add-package-prefix (string case prefix symbol)
  (let ((package-prefix (symbol-package-prefix symbol case prefix)))
    (with-output-to-string--simple (s)
      (write-string--simple package-prefix s)
      (write-char--simple #\_ s)
      (write-string--simple (string->legal-c-name string case package-prefix)
			    s))))

(defun symbol-package-prefix (symbol case prefix)
  (let ((name (shortest-package-name (symbol-package symbol))))
    (case case
      (:upcase (setf name (string-upcase name)))
      (:downcase (setf name (string-downcase name))))
    (string->legal-c-name name case prefix)))

(defun shortest-package-name (package)
  (let* ((names         (package-nicknames package))
	 (name          (if (string= (package-name package) "")
			    (pop names)
			    (package-name package)))
	 (name-length   (length name)))
    (dolist (new names name)
      (let ((new-length (length new)))
	(when (and (> new-length 0) (< new-length name-length))
	  (setf name-length new-length
		name new))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Checking for name conflicts
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun check-name-conflict
    (string globalp case prefix suffix &optional (symbol nil symbolp))
  (let* ((name (with-output-to-string--simple (s)
		 (write-string--simple prefix s)
		 (write-string--simple string s)
		 (write-string--simple suffix s)))
	 (conflict-resolution-integer (c-name-conflict-p name globalp)))
    (cond ((not conflict-resolution-integer) name)
	  ((and (eq globalp 't) symbolp (symbol-package symbol))
	   (handle-package-conflict
	    string globalp case prefix suffix symbol))
	  (t
	   (handle-shadowing-conflict string globalp case prefix suffix name
				      conflict-resolution-integer)))))

(defun handle-shadowing-conflict (string globalp case prefix suffix
					 original-c-name idx)
  (let ((name (sformat "~A~A_~D~A" prefix string idx suffix)))
    (if (c-name-conflict-p name globalp)
	(handle-shadowing-conflict
	  string globalp case prefix suffix original-c-name (1+ idx))
        (progn
	  (record-c-name original-c-name globalp (1+ idx))
  	  name))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Recognizing name conflicts
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; There are two kinds of name conflicts.
;;;
;;; 1. Conflicts with the runtime kernel and C itself.  These are handled by
;;; examining *C-RESERVED-NAMES*.  This must contain not only the reserved
;;; keywords defined by C, but also any identifiers defined in files included
;;; with the user's translated code.  This includes both standard libraries and
;;; the translator's runtime kernel.  New names can be added to this set by
;;; calling the function ADD-C-RESERVED-NAME with the string to add to the set.
;;;
;;; 2. Conflicts with other symbols.
;;;
;;; In principle there should be a seperate pair of local and global name
;;; tables for each class of C identifier.  However, it turns out that only one
;;; is needed by the translator right now.  This is because
;;;
;;; * All preprocessor names need to be in all namespace tables.
;;;
;;; * Although ANSI C puts statement labels in a seperate class, many compilers
;;;   still put them in the same class as variables, functions, &etc.
;;;
;;; * The translator does not create identifiers which will be used as tags for
;;;   structures and such, nor does it create identifiers for component names,
;;;   so no tables are needed for either of these classes.

(defun make-c-name-table (&optional (size 50))
  #+lucid (setq size (ceiling (* size 1.75)))
  (make-hash-table :test #'eq :size size))

(defvar *free-c-name-tables* nil)

(defun get-c-name-table ()
  (or (pop *free-c-name-tables*)
      (make-c-name-table)))

(defun free-c-name-table (table)
  (clrhash table)
  (setq table (sort (cons table *free-c-name-tables*) #'>
		    :key #'hash-table-count)))

(defvar *c-names* (list (cons ':global (make-c-name-table 3500))
			(cons ':reserved (make-c-name-table 300))))

(defun get-c-name-tables (globalp &optional lastp)
  (let ((c-names *c-names*))
    (when globalp
      (let ((type (if (eq globalp 't) ':global globalp))
	    (last nil))
	(loop (unless c-names
		(when (and lastp last)
		  (setq c-names last)
		  (return nil))
		(error "Illegal type name ~S" type))
	      (when (eq (caar c-names) type)
		(if lastp
		    (setq last c-names)
		    (return nil)))
	      (pop c-names))))
    c-names))

;WITH-C-NAME-TABLE (external)
(defmacro with-c-name-table (type &body forms)
  `(let* ((.table. (get-c-name-table))
	  (*c-names* (cons (cons ',type .table.) *c-names*)))
     (multiple-value-prog1 (progn ,@forms)
       (free-c-name-table .table.))))

;WITH-GLOBAL-C-NAME-TABLE (external)
(defmacro with-global-c-name-table (&body forms)
  `(let ((*c-names* (last *c-names*)))
     (with-c-name-table :global
       ,@forms)))

;This is called in two places. Its value becomes the value of *c-names*.
(defun get-initial-c-names ()
  (reserve-initial-c-names)
  `((:global . ,(tutil::make-c-name-table))
    ,@(get-c-name-tables t t)))

(defparameter *reserved-c-names-lists*
  '(("C++"
     "_cplusplus" "catch" "class" "delete" "friend" "inline" "new"
     "operator" "private" "protected " "public" "template" "this"
     "interface" "boolean" "try" "virtual" "wchar_t")
    ("keyword"
     "asm" "auto" "break" "case" "char" "const" "continue" "default" "do"
     "double" "else" "enum" "extern" "float" "for" "fortran" "goto" "if"
     "int" "long" "SI_Long" "register" "return" "short" "signed" "sizeof" "static"
     "struct" "switch" "typedef" "union" "unsigned" "void" "volatile" "while"
     "property")
    ("translator"
     "n"      ; Until new varargs emitter code installed
     "result" ; Temporary hack to replace STORE_VALUES

     "sleep" 
     "times"
     "remove" "delete"			;VMS
     "complex"				;Microsoft C
     "listen"				;Gensym conflict?
     "max" "min")			;Because Jeff says so
    ("enum"
     "SI_Symbol_field" "SI_binary_op" "SI_gcalignment" "SI_gcls"
     "SI_gcrelocatability" "SI_tag" "SI_token_id" "SI_type")
    ("struct"
     #+translator-supports-clos "SI_Function_slot_vector_struct"
     "SI_area_struct" "SI_catch_frame" "SI_frontier_frame"
     "SI_same_size_as_double" "SI_segment_struct" "SI_special_frame" "_iobuf")
    ("typedef"
     "Binding" #+translator-supports-clos "Boolean"
     "CONS_NODE" "CONTENTS_POINTER" "Catch_buf" "DOUBLE"
     "Double_float_kludge_union" "Object" "PACKAGE" "SI_Aligned_double_float"
     "SI_Aligned_double_float_constant" "SI_Area" "SI_Bignum"
     "SI_Bignum_constant" "SI_Bignum_digit_type" "SI_Catch_frame"
     #+translator-supports-clos "SI_Class_wrapper"
     "SI_Cobject" "SI_Cons" "SI_Cons_constant" "SI_Cons_exposed"
     "SI_Dimension" #+translator-supports-clos "SI_Effective_method"
     "SI_Frontier_frame" "SI_Function" "SI_Function_constant"
     "SI_General_array" "SI_General_array_constant" "SI_Header"
     "SI_Initial_symbol" "SI_Initial_symbol_stored" "SI_Instance"
     "SI_Kludged_double_float" "SI_Long"
     #+translator-supports-clos "SI_Method"
     #+translator-supports-clos "SI_Method_combination"
     "SI_Noninitial_symbol" "SI_Noninitial_symbol_constant" "SI_Package"
     "SI_Package_constant" "SI_Pathname" "SI_Primitive_vector"
     "SI_Primitive_vector_constant" "SI_Ratio" "SI_Ratio_constant"
     "SI_Segment" "SI_Size_type" "SI_Special_frame" "SI_Stack_item"
     "SI_Standard_instance" "SI_Static_T" "SI_Structure" "SI_Symbol"
     "SI_Ulong" "SYMBOL_NODE" "Structure_object" "UCHAR" "__gnuc_va_list"
     "jmp_buf" "sigjmp_buf" "va_list")
    ("macro"
     "ABS" "ACONS" "ADD_BINDING" "ADD_IMPORT" "ADD_PACKAGE_NICKNAME"
     "ADD_PACKAGE_USE" "ADD_SHADOW" "ADJUSTABLE_ARRAY_P" "ALIGNMENT"
     "ALLOW_OTHER_KEYS" "ALPHANUMERICP" "ALPHA_CHAR_P" "APPEND_2" "APPLY_1"
     "APPLY_2" "APPLY_3" "APPLY_4" "APPLY_5" "ARRAYP" "ARRAY_DIMENSION_LIMIT"
     "ARRAY_FOREIGN_TYPE_DIMENSIONS" "ARRAY_FOREIGN_TYPE_ETYPE"
     "ARRAY_FOREIGN_TYPE_P" "ARRAY_FOREIGN_TYPE_ROW_MAJOR_P"
     "ARRAY_HAS_FILL_POINTER_P" "ARRAY_RANK" "ARRAY_RANK_LIMIT"
     "ARRAY_TOTAL_SIZE_LIMIT" "ASSIGNFLOAT" "ATOM" "Area"
     "Array_dimension_limit" "Array_rank_limit" "Array_total_size_limit"
     "BEGIN_ARGS" "BEGIN_KEYWORD_ARGS" "BEGIN_UNWIND_PROTECT" "BIGNUMP"
     "BIG_ENDIAN" "BINARY_DOUBLE_FLOAT_OP" "BINARY_DOUBLE_FLOAT_PRED"
     "BINDING_OF" "BINDING_VALUE" "BITP" "BIT_VECTOR_P" "BOOLEAN_TO_BOOLE"
     "BOOLE_1" "BOOLE_2" "BOOLE_AND" "BOOLE_ANDC1" "BOOLE_ANDC2" "BOOLE_C1"
     "BOOLE_C2" "BOOLE_CLR" "BOOLE_EQV" "BOOLE_IOR" "BOOLE_NAND" "BOOLE_NOR"
     "BOOLE_ORC1" "BOOLE_ORC2" "BOOLE_SET" "BOOLE_TO_BOOLEAN" "BOOLE_XOR"
     "BOUNDP" "BOX_BOOLEAN" "BOX_CHAR" "BOX_DOUBLE" "BOX_INT"
     "BROADCAST_STREAM_P" "BUFSIZ" "BYTE" "BYTE_16_ISAREF_0"
     "BYTE_16_ISAREF_1" "BYTE_16_ISAREF_2" "BYTE_16_ISAREF_3"
     "BYTE_16_ISAREF_4" "BYTE_16_ISAREF_5" "BYTE_16_ISAREF_6"
     "BYTE_16_ISAREF_7" "BYTE_16_ISASET_0" "BYTE_16_ISASET_1"
     "BYTE_16_ISASET_2" "BYTE_16_ISASET_3" "BYTE_16_ISASET_4"
     "BYTE_16_ISASET_5" "BYTE_16_ISASET_6" "BYTE_16_ISASET_7"
     "BYTE_16_R_M_S_AREF" "BYTE_16_SAREF_0" "BYTE_16_SAREF_1"
     "BYTE_16_SAREF_2" "BYTE_16_SAREF_3" "BYTE_16_SAREF_4" "BYTE_16_SAREF_5"
     "BYTE_16_SAREF_6" "BYTE_16_SAREF_7" "BYTE_16_SARRAY_TO_SHORT_POINTER"
     "BYTE_16_SASET_0" "BYTE_16_SASET_1" "BYTE_16_SASET_2" "BYTE_16_SASET_3"
     "BYTE_16_SASET_4" "BYTE_16_SASET_5" "BYTE_16_SASET_6" "BYTE_16_SASET_7"
     "BYTE_32_ISAREF_0" "BYTE_32_ISAREF_1" "BYTE_32_ISAREF_2"
     "BYTE_32_ISAREF_3" "BYTE_32_ISAREF_4" "BYTE_32_ISAREF_5"
     "BYTE_32_ISAREF_6" "BYTE_32_ISAREF_7" "BYTE_32_ISASET_0"
     "BYTE_32_ISASET_1" "BYTE_32_ISASET_2" "BYTE_32_ISASET_3"
     "BYTE_32_ISASET_4" "BYTE_32_ISASET_5" "BYTE_32_ISASET_6"
     "BYTE_32_ISASET_7" "BYTE_32_R_M_S_AREF" "BYTE_32_SAREF_0"
     "BYTE_32_SAREF_1" "BYTE_32_SAREF_2" "BYTE_32_SAREF_3" "BYTE_32_SAREF_4"
     "BYTE_32_SAREF_5" "BYTE_32_SAREF_6" "BYTE_32_SAREF_7" "BYTE_32_SASET_0"
     "BYTE_32_SASET_1" "BYTE_32_SASET_2" "BYTE_32_SASET_3" "BYTE_32_SASET_4"
     "BYTE_32_SASET_5" "BYTE_32_SASET_6" "BYTE_32_SASET_7" "BYTE_8_ISAREF_0"
     "BYTE_8_ISAREF_1" "BYTE_8_ISAREF_2" "BYTE_8_ISAREF_3" "BYTE_8_ISAREF_4"
     "BYTE_8_ISAREF_5" "BYTE_8_ISAREF_6" "BYTE_8_ISAREF_7" "BYTE_8_ISASET_0"
     "BYTE_8_ISASET_1" "BYTE_8_ISASET_2" "BYTE_8_ISASET_3" "BYTE_8_ISASET_4"
     "BYTE_8_ISASET_5" "BYTE_8_ISASET_6" "BYTE_8_ISASET_7"
     "BYTE_8_R_M_S_AREF" "BYTE_8_SAREF_0" "BYTE_8_SAREF_1" "BYTE_8_SAREF_2"
     "BYTE_8_SAREF_3" "BYTE_8_SAREF_4" "BYTE_8_SAREF_5" "BYTE_8_SAREF_6"
     "BYTE_8_SAREF_7" "BYTE_8_SARRAY_TO_CHAR_POINTER" "BYTE_8_SASET_0"
     "BYTE_8_SASET_1" "BYTE_8_SASET_2" "BYTE_8_SASET_3" "BYTE_8_SASET_4"
     "BYTE_8_SASET_5" "BYTE_8_SASET_6" "BYTE_8_SASET_7" "BYTE_POSITION"
     "BYTE_SIZE" "Boole_1" "Boole_2" "Boole_and" "Boole_andc1" "Boole_andc2"
     "Boole_c1" "Boole_c2" "Boole_clr" "Boole_eqv" "Boole_ior" "Boole_nand"
     "Boole_nor" "Boole_orc1" "Boole_orc2" "Boole_set" "Boole_xor" "CAAAAR"
     "CAAADR" "CAAAR" "CAADAR" "CAADDR" "CAADR" "CAAR" "CADAAR" "CADADR"
     "CADAR" "CADDAR" "CADDDR" "CADDR" "CADR" "CALLN_0" "CALLN_1" "CALLN_10"
     "CALLN_11" "CALLN_12" "CALLN_13" "CALLN_14" "CALLN_15" "CALLN_16"
     "CALLN_17" "CALLN_18" "CALLN_19" "CALLN_2" "CALLN_20" "CALLN_3"
     "CALLN_4" "CALLN_5" "CALLN_6" "CALLN_7" "CALLN_8" "CALLN_9" "CALL_0"
     "CALL_1" "CALL_10" "CALL_11" "CALL_12" "CALL_13" "CALL_14" "CALL_15"
     "CALL_16" "CALL_17" "CALL_18" "CALL_19" "CALL_2" "CALL_20" "CALL_3"
     "CALL_4" "CALL_5" "CALL_6" "CALL_7" "CALL_8" "CALL_9"
     "CALL_ARGUMENTS_LIMIT" "CALL_INIT_FUNCTION"
     #+translator-supports-clos "CALL_NEXT_METHOD"
     "CAR" "CAREFUL_CALL_2" "CATCH" "CATCH_VALUES" "CDAAAR" "CDAADR" "CDAAR"
     "CDADAR" "CDADDR" "CDADR" "CDAR" "CDDAAR" "CDDADR" "CDDAR" "CDDDAR"
     "CDDDDR" "CDDDR" "CDDR" "CDR" "CHAR" "CHARACTERP" "CHARACTER_TO_CHAR"
     "CHAR_BITS" "CHAR_BITS_LIMIT" "CHAR_CODE" "CHAR_CODE_LIMIT"
     "CHAR_CONTROL_BIT" "CHAR_DOWNCASE" "CHAR_EQ" "CHAR_EQUAL" "CHAR_FONT"
     "CHAR_FONT_LIMIT" "CHAR_GE" "CHAR_GREATERP" "CHAR_GT" "CHAR_HYPER_BIT"
     "CHAR_INT" "CHAR_ISAREF_0" "CHAR_ISAREF_1" "CHAR_ISAREF_2"
     "CHAR_ISAREF_3" "CHAR_ISAREF_4" "CHAR_ISAREF_5" "CHAR_ISAREF_6"
     "CHAR_ISAREF_7" "CHAR_ISASET_0" "CHAR_ISASET_1" "CHAR_ISASET_2"
     "CHAR_ISASET_3" "CHAR_ISASET_4" "CHAR_ISASET_5" "CHAR_ISASET_6"
     "CHAR_ISASET_7" "CHAR_LE" "CHAR_LESSP" "CHAR_LT" "CHAR_META_BIT"
     "CHAR_NE" "CHAR_NOT_EQUAL" "CHAR_NOT_GREATERP" "CHAR_NOT_LESSP"
     "CHAR_R_M_S_AREF" "CHAR_SAREF_0" "CHAR_SAREF_1" "CHAR_SAREF_2"
     "CHAR_SAREF_3" "CHAR_SAREF_4" "CHAR_SAREF_5" "CHAR_SAREF_6"
     "CHAR_SAREF_7" "CHAR_SASET_0" "CHAR_SASET_1" "CHAR_SASET_2"
     "CHAR_SASET_3" "CHAR_SASET_4" "CHAR_SASET_5" "CHAR_SASET_6"
     "CHAR_SASET_7" "CHAR_SUPER_BIT" "CHAR_TO_CHARACTER" "CHAR_TO_FIXNUM"
     "CHAR_TO_INTEGER" "CHAR_UPCASE" "CHR" "CHR_BITS" "CHR_CODE" "CHR_FONT"
     #+translator-supports-clos "CLASS_TYPEP"
     #+translator-supports-clos "CLASS_WRAPPER_P"
     "COBJECTP" "COBJECT_NAME" "COBJECT_OBJ" "CODE_CHAR"
     "COMPILED_FUNCTION_P" "COMPLEXP" "CONCATENATED_STREAM_P"
     "CONFIG_PROVIDES" "CONFIG_REQUIRES" "CONS" "CONSP" "CONSTANT_ARRAY"
     "CONSTANT_ARRAY_CONTENTS" "CONSTANT_BIGNUM" "CONSTANT_BIT_VECTOR"
     "CONSTANT_COMPILED_FUNCTION" "CONSTANT_CONS" "CONSTANT_DOUBLE_FLOAT"
     "CONSTANT_LIST_1" "CONSTANT_LIST_2" "CONSTANT_LIST_3" "CONSTANT_LIST_4"
     "CONSTANT_LIST_5" "CONSTANT_LIST_STAR_3" "CONSTANT_LIST_STAR_4"
     "CONSTANT_LIST_STAR_5" "CONSTANT_LIST_STAR_6" "CONSTANT_RATIO"
     "CONSTANT_STRING" "CONSTANT_VECTOR" "CONTINUE_UNWINDING"
     "Call_arguments_limit" "Char_code_limit" "DECIMAL_STRING_LENGTH"
     "DECLARE_AREA" "DECLARE_CATCH" "DECLARE_DYNAMIC_STATE"
     "DECLARE_FRONTIER" "DECLARE_PROTECT" "DECLARE_SPECIAL"
     "DECLARE_STACK_POINTER" "DEFINE_PACKAGE"
     #+translator-supports-clos "DEFINE_VARIADIC_GENERIC_FUNCTION"
     "DENOMINATOR" "DFLOAT_ISAREF_0" "DFLOAT_ISAREF_1" "DFLOAT_ISAREF_2"
     "DFLOAT_ISAREF_3" "DFLOAT_ISAREF_4" "DFLOAT_ISAREF_5" "DFLOAT_ISAREF_6"
     "DFLOAT_ISAREF_7" "DFLOAT_ISASET_0" "DFLOAT_ISASET_1" "DFLOAT_ISASET_2"
     "DFLOAT_ISASET_3" "DFLOAT_ISASET_4" "DFLOAT_ISASET_5" "DFLOAT_ISASET_6"
     "DFLOAT_ISASET_7" "DFLOAT_R_M_S_AREF" "DFLOAT_SAREF_0" "DFLOAT_SAREF_1"
     "DFLOAT_SAREF_2" "DFLOAT_SAREF_3" "DFLOAT_SAREF_4" "DFLOAT_SAREF_5"
     "DFLOAT_SAREF_6" "DFLOAT_SAREF_7" "DFLOAT_SARRAY_TO_DOUBLE_POINTER"
     "DFLOAT_SASET_0" "DFLOAT_SASET_1" "DFLOAT_SASET_2" "DFLOAT_SASET_3"
     "DFLOAT_SASET_4" "DFLOAT_SASET_5" "DFLOAT_SASET_6" "DFLOAT_SASET_7"
     "DOMAIN" "DOUBLEP" "DOUBLE_ABS" "DOUBLE_ADD" "DOUBLE_ADD1" "DOUBLE_ATAN"
     "DOUBLE_ATAN1" "DOUBLE_CEILING" "DOUBLE_CEILING1" "DOUBLE_COS"
     "DOUBLE_DIVIDE" "DOUBLE_EQ" "DOUBLE_EXP" "DOUBLE_EXPT"
     "DOUBLE_FLOAT_ABS" "DOUBLE_FLOAT_ADD" "DOUBLE_FLOAT_ADD1"
     "DOUBLE_FLOAT_ATAN" "DOUBLE_FLOAT_ATAN1" "DOUBLE_FLOAT_CEILING"
     "DOUBLE_FLOAT_CEILING1" "DOUBLE_FLOAT_COS" "DOUBLE_FLOAT_DIVIDE"
     "DOUBLE_FLOAT_EQ" "DOUBLE_FLOAT_EXP" "DOUBLE_FLOAT_EXPT"
     "DOUBLE_FLOAT_FLOOR" "DOUBLE_FLOAT_FLOOR1" "DOUBLE_FLOAT_FROUND"
     "DOUBLE_FLOAT_FROUND1" "DOUBLE_FLOAT_GE" "DOUBLE_FLOAT_GT"
     "DOUBLE_FLOAT_LE" "DOUBLE_FLOAT_LOG" "DOUBLE_FLOAT_LOG1"
     "DOUBLE_FLOAT_LT" "DOUBLE_FLOAT_MAX" "DOUBLE_FLOAT_MIN"
     "DOUBLE_FLOAT_MINUS" "DOUBLE_FLOAT_MINUSP" "DOUBLE_FLOAT_NE"
     "DOUBLE_FLOAT_NEGATE" "DOUBLE_FLOAT_P" "DOUBLE_FLOAT_PLUSP"
     "DOUBLE_FLOAT_ROUND" "DOUBLE_FLOAT_ROUND1" "DOUBLE_FLOAT_SIN"
     "DOUBLE_FLOAT_SQRT" "DOUBLE_FLOAT_SUB1" "DOUBLE_FLOAT_TAN"
     "DOUBLE_FLOAT_TIMES" "DOUBLE_FLOAT_TO_DOUBLE" "DOUBLE_FLOAT_TO_DOUBLE1"
     "DOUBLE_FLOAT_TRUNCATE" "DOUBLE_FLOAT_TRUNCATE1" "DOUBLE_FLOAT_ZEROP"
     "DOUBLE_FLOOR" "DOUBLE_FLOOR1" "DOUBLE_FROUND" "DOUBLE_FROUND1"
     "DOUBLE_GE" "DOUBLE_GT" "DOUBLE_LE" "DOUBLE_LOG" "DOUBLE_LOG1"
     "DOUBLE_LT" "DOUBLE_MAX" "DOUBLE_MIN" "DOUBLE_MINUS" "DOUBLE_MINUSP"
     "DOUBLE_NE" "DOUBLE_NEGATE" "DOUBLE_PLUSP" "DOUBLE_ROUND"
     "DOUBLE_ROUND1" "DOUBLE_SIN" "DOUBLE_SQRT" "DOUBLE_SUB1" "DOUBLE_TAN"
     "DOUBLE_TIMES" "DOUBLE_TO_DOUBLE_FLOAT" "DOUBLE_TRUNCATE"
     "DOUBLE_TRUNCATE1" "DOUBLE_ZEROP" "DO_THROW" "DYNAMIC_INCREMENT"
     "DYNAMIC_SIZE" "Declare_area" "Declare_catch" "Declare_dynamic_state"
     "Declare_frontier" "Declare_local_temp"
     #+translator-supports-clos "Declare_method_rest"
     "Declare_protect" #+translator-supports-clos "Declare_slot_value"
     "Declare_special" "Declare_stack_pointer" "Declare_varargs"
     "Declare_varargs_nonrelocating" "ECHO_STREAM_P"
     #+translator-supports-clos "EFFECTIVE_METHOD_ALWKYP"
     #+translator-supports-clos "EFFECTIVE_METHOD_CALL"
     #+translator-supports-clos "EFFECTIVE_METHOD_KEYP"
     #+translator-supports-clos "EFFECTIVE_METHOD_KEYS"
     #+translator-supports-clos "EFFECTIVE_METHOD_KEYWORD_PERMUTATION"
     #+translator-supports-clos "EFFECTIVE_METHOD_P"
     #+translator-supports-clos "EFFECTIVE_METHOD_POSITIONAL"
     #+translator-supports-clos "EFFECTIVE_METHOD_REQUIRED"
     #+translator-supports-clos "EFFECTIVE_METHOD_RESTP"
     "EIGHTH" "EMERGENCY_RESERVE" "ENDP" "END_ARGS" "END_ARGS_nonrelocating"
     "END_CATCH" "END_CONSTANT_ARRAY" "END_CONSTANT_BIGNUM"
     "END_CONSTANT_BIT_VECTOR" "END_CONSTANT_VECTOR" "END_DEFINE_PACKAGE"
     "END_INITIAL_PACKAGE" "END_KEYWORD_ARGS" "END_PROGV"
     "END_UNWIND_PROTECT" "ENSURE_GLOBAL" "EOF" "EQ" "EQL" "EQUAL" "EQUALP"
     "EXTRACT_KEY" "EXTRACT_KEY_VALUE" "FALSE" "FIFTH" "FILE" "FILEP"
     "FILE_STREAM_P" "FILL_POINTER" "FIND_BINDING" "FIRST" "FIX" "FIXNUMP"
     "FIXNUM_ABS" "FIXNUM_ADD" "FIXNUM_ADD1" "FIXNUM_ASH" "FIXNUM_BYTE_MASK"
     "FIXNUM_CEILING" "FIXNUM_DIVIDE" "FIXNUM_DPB" "FIXNUM_EQ" "FIXNUM_EVENP"
     "FIXNUM_FLOOR" "FIXNUM_GE" "FIXNUM_GT" "FIXNUM_LDB" "FIXNUM_LE"
     "FIXNUM_LOGAND" "FIXNUM_LOGANDC2" "FIXNUM_LOGBITP" "FIXNUM_LOGEQV"
     "FIXNUM_LOGIOR" "FIXNUM_LOGNOT" "FIXNUM_LOGTEST" "FIXNUM_LOGXOR"
     "FIXNUM_LSH" "FIXNUM_LT" "FIXNUM_MAX" "FIXNUM_MIN" "FIXNUM_MINUS"
     "FIXNUM_MINUSP" "FIXNUM_MOD" "FIXNUM_NE" "FIXNUM_NEGATE" "FIXNUM_ODDP"
     "FIXNUM_PLUSP" "FIXNUM_REM" "FIXNUM_ROUND" "FIXNUM_RSH" "FIXNUM_SUB1"
     "FIXNUM_TIMES" "FIXNUM_TO_CHAR" "FIXNUM_TO_INT" "FIXNUM_TO_LONG"
     "FIXNUM_TO_SHORT" "FIXNUM_TRUNCATE" "FIXNUM_ZEROP" "FLOATFUNCTIONTYPE"
     "FLOATP" "FLOATPARAMETER" "FLOATPARAMETERVALUE" "FLOAT_ISAREF_0"
     "FLOAT_ISAREF_1" "FLOAT_ISAREF_2" "FLOAT_ISAREF_3" "FLOAT_ISAREF_4"
     "FLOAT_ISAREF_5" "FLOAT_ISAREF_6" "FLOAT_ISAREF_7" "FLOAT_ISASET_0"
     "FLOAT_ISASET_1" "FLOAT_ISASET_2" "FLOAT_ISASET_3" "FLOAT_ISASET_4"
     "FLOAT_ISASET_5" "FLOAT_ISASET_6" "FLOAT_ISASET_7" "FLOAT_R_M_S_AREF"
     "FLOAT_SAREF_0" "FLOAT_SAREF_1" "FLOAT_SAREF_2" "FLOAT_SAREF_3"
     "FLOAT_SAREF_4" "FLOAT_SAREF_5" "FLOAT_SAREF_6" "FLOAT_SAREF_7"
     "FLOAT_SASET_0" "FLOAT_SASET_1" "FLOAT_SASET_2" "FLOAT_SASET_3"
     "FLOAT_SASET_4" "FLOAT_SASET_5" "FLOAT_SASET_6" "FLOAT_SASET_7"
     "FLOAT_TO_SHORT_FLOAT" "FLOAT_TO_SINGLE_FLOAT" "FOREIGN_POINTER_ADDRESS"
     "FOREIGN_POINTER_P" "FOREIGN_POINTER_TYPE" "FOREIGN_POINTER_TYPE_P"
     "FOREIGN_TYPE" "FOREIGN_TYPE2" "FOREIGN_TYPE_MODULUS"
     "FOREIGN_TYPE_NAME" "FOREIGN_TYPE_P" "FOREIGN_TYPE_POINTER_TYPE"
     "FOREIGN_TYPE_READER" "FOREIGN_TYPE_REMAINDER" "FOREIGN_TYPE_SIZE"
     "FOREIGN_TYPE_WRITER" "FOREVER" "FORWARD_STATIC" "FOURTH" "FSETF_aref"
     "FSETF_bit" #+translator-supports-clos "FSETF_class_name"
     #+translator-supports-clos "FSETF_class_status_bits"
     #+translator-supports-clos "FSETF_find_class"
     "FSETF_foreign_aref"
     #+translator-supports-clos "FSETF_metaobject_documentation"
     #+translator-supports-clos "FSETF_metaobject_name"
     "FSETF_sbit" #+translator-supports-clos "FSETF_slot_definition_location"
     #+translator-supports-clos "FSETF_slot_value_using_class"
     "FSETF_typed_foreign_aref"
     #+translator-supports-clos "FSETF_valid_change_class_initargs"
     #+translator-supports-clos "FSETF_valid_creation_initargs"
     #+translator-supports-clos "FSETF_valid_reinitialization_initargs"
     "FUNCALL_0" "FUNCALL_1" "FUNCALL_2" "FUNCALL_3" "FUNCALL_4" "FUNCALL_5"
     "FUNCALL_6" "FUNCALL_SYMBOL_0" "FUNCALL_SYMBOL_1" "FUNCALL_SYMBOL_2"
     "FUNCALL_SYMBOL_3" "FUNCALL_SYMBOL_4" "FUNCALL_SYMBOL_5" "FUNCTIONP"
     "FUNC_OPT_P" "FUNC_REST_P" "Fabs" "Facons" "Facos" "Facosh" "Fadd"
     "Fadd1" #+translator-supports-clos "Fadd_direct_subclass"
     #+translator-supports-clos "Fadd_method"
     #+translator-supports-clos "Fadd_named_class"
     #+translator-supports-clos "Fadd_named_generic_function"
     #+translator-supports-clos "Fadd_named_method"
     "Fadjoin" "Fadjust_array" "Fadjustable_array_p"
     #+translator-supports-clos "Fallocate_instance"
     "Fallocate_memory_to_target" "Fallow_gc" "Falpha_char_p"
     "Falphanumericp" "Fappend" "Fapply" "Farea_memory_limit"
     "Farea_memory_used" "Farea_target_size" "Faref" "Farray_dimension"
     "Farray_dimensions" "Farray_element_type" "Farray_has_fill_pointer_p"
     "Farray_in_bounds_p" "Farray_rank" "Farray_row_major_index"
     "Farray_total_size" "Farrayp" "Fash" "Fasin" "Fasinh" "Fassoc"
     "Fassoc_if" "Fassoc_if_not" "Fassq" "Fatan" "Fatanh" "Fatom"
     "Fbegin_hash_table_iterator" "Fbegin_print_unreadable_object"
     "Fbegin_time" "Fbignump" "Fbit" "Fbit_and" "Fbit_andc1" "Fbit_andc2"
     "Fbit_eqv" "Fbit_ior" "Fbit_nand" "Fbit_nor" "Fbit_not" "Fbit_orc1"
     "Fbit_orc2" "Fbit_vector_p" "Fbit_xor" "Fbitp" "Fboole" "Fboth_case_p"
     "Fboundp" "Fbreak" "Fbroadcast_stream_p" "Fbutlast" "Fbyte"
     "Fbyte_position" "Fbyte_size" "Fcaaaar" "Fcaaadr" "Fcaaar" "Fcaadar"
     "Fcaaddr" "Fcaadr" "Fcaar" "Fcadaar" "Fcadadr" "Fcadar" "Fcaddar"
     "Fcadddr" "Fcaddr" "Fcadr" "Fcar" "Fcdaaar" "Fcdaadr" "Fcdaar" "Fcdadar"
     "Fcdaddr" "Fcdadr" "Fcdar" "Fcddaar" "Fcddadr" "Fcddar" "Fcdddar"
     "Fcddddr" "Fcdddr" "Fcddr" "Fcdr" "Fceiling" "Fcerror"
     #+translator-supports-clos "Fchange_class"
     "Fchar" "Fchar_code" "Fchar_downcase" "Fchar_eq" "Fchar_equal"
     "Fchar_ge" "Fchar_greaterp" "Fchar_gt" "Fchar_int" "Fchar_le"
     "Fchar_lessp" "Fchar_lt" "Fchar_name" "Fchar_ne" "Fchar_not_equal"
     "Fchar_not_greaterp" "Fchar_not_lessp" "Fchar_upcase" "Fcharacter"
     "Fcharacterp" "Fcis"
     #+translator-supports-clos "Fclass_default_initargs"
     #+translator-supports-clos "Fclass_default_superclasses"
     #+translator-supports-clos "Fclass_direct_default_initargs"
     #+translator-supports-clos "Fclass_direct_slots"
     #+translator-supports-clos "Fclass_direct_subclasses"
     #+translator-supports-clos "Fclass_direct_superclasses"
     #+translator-supports-clos "Fclass_finalized_p"
     #+translator-supports-clos "Fclass_fully_defined_p"
     #+translator-supports-clos "Fclass_name"
     #+translator-supports-clos "Fclass_of"
     #+translator-supports-clos "Fclass_precedence_list"
     #+translator-supports-clos "Fclass_prototype"
     #+translator-supports-clos "Fclass_slots"
     #+translator-supports-clos "Fclass_status_bits"
     #+translator-supports-clos "Fclass_wrapper_p"
     "Fcleanup_hash_table_iterator" "Fclear_input" "Fclear_output" "Fclose"
     "Fclrhash" "Fcobjectp" "Fcode_char" "Fcoerce" "Fcompiled_function_p"
     "Fcomplement" "Fcomplex" "Fcomplexp"
     #+translator-supports-clos "Fcompute_applicable_methods"
     #+translator-supports-clos "Fcompute_class_default_initargs"
     #+translator-supports-clos "Fcompute_class_precedence_list"
     #+translator-supports-clos "Fcompute_class_prototype"
     #+translator-supports-clos "Fcompute_effective_method"
     #+translator-supports-clos "Fcompute_effective_slot_definition"
     #+translator-supports-clos "Fcompute_effective_slot_definition_initargs"
     #+translator-supports-clos "Fcompute_method_combination"
     #+translator-supports-clos "Fcompute_slot_definition_location"
     #+translator-supports-clos "Fcompute_slot_definition_locations"
     #+translator-supports-clos "Fcompute_slots"
     #+translator-supports-clos "Fcompute_valid_change_class_initargs"
     #+translator-supports-clos "Fcompute_valid_creation_initargs"
     #+translator-supports-clos "Fcompute_valid_reinitialization_initargs"
     "Fconcatenate" "Fconcatenated_stream_p" "Fcons" "Fconsp"
     "Fconstant_initfunction" "Fconstantly" "Fconstantly_false"
     "Fconstantly_nil_initfunction" "Fconstantly_t_initfunction"
     "Fconstantly_true"
     #+translator-supports-clos "Fconstantly_zero_initfunction"
     "Fconstantp" "Fcopy_alist" "Fcopy_foreign_pointer" "Fcopy_list"
     "Fcopy_readtable" "Fcopy_seq" "Fcopy_structure" "Fcopy_symbol"
     "Fcopy_tree" "Fcos" "Fcosh" "Fcount" "Fcount_if" "Fcount_if_not"
     "Fdecode_float" "Fdecode_universal_time"
     #+translator-supports-clos "Fdefault_initargs"
     "Fdefine_foreign_synonym_type" "Fdefpackage_export"
     "Fdefpackage_import_from" "Fdefpackage_intern" "Fdefpackage_use_package"
     "Fdelete" "Fdelete_duplicates" "Fdelete_file" "Fdelete_if"
     "Fdelete_if_not" "Fdelq" "Fdenominator" "Fdeposit_field" "Fdigit_char"
     "Fdigit_char_p"
     #+translator-supports-clos "Fdirect_slot_definition_class"
     "Fdirectory" "Fdirectory_namestring"
     #+translator-supports-clos "Fdisplay_cache_statistics"
     "Fdivide" "Fdo_remf" "Fdpb" "Fecho_stream_p"
     #+translator-supports-clos "Feffective_method_p"
     #+translator-supports-clos "Feffective_slot_definition_class"
     "Feighth" #+translator-supports-clos "Felide_access_method_p"
     "Felt" "Fencode_universal_time" "Fend_hash_table_iterator" "Fendp"
     "Fenough_namestring" #+translator-supports-clos "Fensure_class"
     #+translator-supports-clos "Fensure_generic_function"
     "Feq" "Feql" "Fequal" "Fequalp" "Ferror" "Feval_run" "Fevenp" "Fevery"
     "Fexp" "Fexport" "Fexpt" "Fextend_string_output_stream" "Ffboundp"
     "Ffceiling" "Ffdefinition" "Fffloor" "Ffifth" "Ffile_author"
     "Ffile_length" "Ffile_namestring" "Ffile_position" "Ffile_stream_p"
     "Ffile_write_date" "Ffill" "Ffill_pointer"
     #+translator-supports-clos "Ffinalize_inheritance"
     "Ffind" #+translator-supports-clos "Ffind_class"
     #+translator-supports-clos "Ffind_effective_slot_definition"
     "Ffind_if" "Ffind_if_not"
     #+translator-supports-clos "Ffind_instance_keyword"
     #+translator-supports-clos "Ffind_method"
     "Ffind_package" #+translator-supports-clos "Ffind_standard_method_class"
     #+translator-supports-clos "Ffind_standard_method_combination"
     "Ffind_symbol" "Ffinish_output" "Ffinish_print_unreadable_object"
     "Ffinish_time" "Ffirst" "Ffixnump" "Fflatsize" "Ffloat" "Ffloat_digits"
     "Ffloat_precision" "Ffloat_radix" "Ffloat_sign" "Ffloatp" "Ffloor"
     "Ffmakunbound" "Fforce_gc" "Fforce_output" "Fforeign_aref"
     "Fforeign_pointer_address" "Fforeign_pointer_p" "Fforeign_pointer_type"
     "Fforeign_pointer_type_p" "Fforeign_string_value" "Fforeign_type"
     "Fforeign_type_modulus" "Fforeign_type_name" "Fforeign_type_p"
     "Fforeign_type_remainder" "Fforeign_type_size" "Fforeign_typep"
     "Fforeign_value" "Fformat" "Ffourth" "Ffree_foreign_pointer"
     "Ffresh_line" "Ffround" "Fftruncate" "Ffuncall"
     #+translator-supports-clos "Ffunction_keywords"
     "Ffunctionp" "Fgcd"
     #+translator-supports-clos "Fgeneric_function_argument_precedence_order"
     #+translator-supports-clos "Fgeneric_function_declarations"
     #+translator-supports-clos "Fgeneric_function_initial_methods"
     #+translator-supports-clos "Fgeneric_function_lambda_list"
     #+translator-supports-clos "Fgeneric_function_method_class"
     #+translator-supports-clos "Fgeneric_function_method_combination"
     #+translator-supports-clos "Fgeneric_function_methods"
     #+translator-supports-clos "Fgeneric_function_name"
     "Fgensym" "Fgentemp" "Fget" "Fget_decoded_time"
     "Fget_internal_real_time" "Fget_internal_run_time"
     "Fget_macro_character" "Fget_output_stream_string" "Fget_properties"
     "Fget_universal_time" "Fgetf" "Fgethash" "Fgraphic_char_p"
     "Fhash_table_count" "Fhash_table_iterator" "Fhash_table_p"
     "Fhost_namestring" "Fidentity" "Fimagpart" "Fimport"
     #+translator-supports-clos "Finitialize_instance"
     "Finput_stream_p" "Finteger_decode_float" "Finteger_length" "Fintegerp"
     "Finteraction_stream_p" "Fintern" "Fintersection" "Fisqrt" "Fkeywordp"
     "Flast" "Flcm" "Fldb" "Fldb_test" "Fldiff" "Flength"
     "Flisp_implementation_type" "Flisp_implementation_version" "Flist"
     "Flist_all_packages" "Flist_length" "Flist_nreverse" "Flist_reverse"
     "Flist_star" "Flisten" "Flistp" "Fload_run"
     #+translator-supports-clos "Flocal_slot_definition_p"
     "Flog" "Flogand" "Flogandc1" "Flogandc2" "Flogbitp" "Flogcount"
     "Flogeqv" "Flogior" "Flognand" "Flognor" "Flognot" "Flogorc1" "Flogorc2"
     "Flogtest" "Flogxor" "Flong_site_name" "Flower_case_p" "Fmacro_function"
     "Fmacroexpand" "Fmacroexpand_1" "Fmake_array" "Fmake_broadcast_stream"
     "Fmake_concatenated_stream" "Fmake_echo_stream" "Fmake_foreign_pointer"
     #+translator-supports-clos "Fmake_generic_function"
     "Fmake_hash_table" #+translator-supports-clos "Fmake_instance"
     #+translator-supports-clos "Fmake_instances_obsolete"
     "Fmake_list" "Fmake_package" "Fmake_pathname" "Fmake_random_state"
     "Fmake_sequence" "Fmake_string" "Fmake_string_input_stream"
     "Fmake_string_output_stream" "Fmake_struct_foreign_type"
     "Fmake_structure_class" "Fmake_symbol" "Fmake_two_way_stream"
     "Fmakunbound" "Fmalloc_foreign_pointer" "Fmap" "Fmapc" "Fmapcan"
     "Fmapcar" "Fmapcon" "Fmaphash" "Fmapl" "Fmaplist" "Fmask_field" "Fmax"
     "Fmember" "Fmember_if" "Fmember_if_not" "Fmemq" "Fmerge"
     "Fmerge_pathnames"
     #+translator-supports-clos "Fmetaobject_documentation"
     #+translator-supports-clos "Fmetaobject_name"
     #+translator-supports-clos "Fmethod_combination_function"
     #+translator-supports-clos "Fmethod_combination_name"
     #+translator-supports-clos "Fmethod_combination_options"
     #+translator-supports-clos "Fmethod_combination_p"
     #+translator-supports-clos "Fmethod_function"
     #+translator-supports-clos "Fmethod_generic_function"
     #+translator-supports-clos "Fmethod_lambda_list"
     #+translator-supports-clos "Fmethod_qualifiers"
     #+translator-supports-clos "Fmethod_slot_name"
     #+translator-supports-clos "Fmethod_specializers"
     "Fmin" "Fminus" "Fminusp" "Fmismatch" "Fmod" "Fname_char" "Fnamestring"
     "Fnbutlast" "Fnconc" "Fncons" "Fnintersection" "Fninth"
     #+translator-supports-clos "Fno_applicable_method"
     #+translator-supports-clos "Fno_next_method"
     #+translator-supports-clos "Fno_primary_method"
     "Fnot" "Fnotany" "Fnotevery" "Fnreconc" "Fnreverse" "Fnset_difference"
     "Fnset_exclusive_or" "Fnstring_capitalize" "Fnstring_downcase"
     "Fnstring_upcase" "Fnsublis" "Fnsubst" "Fnsubst_if" "Fnsubst_if_not"
     "Fnsubstitute" "Fnsubstitute_if" "Fnsubstitute_if_not" "Fnth" "Fnthcdr"
     "Fnull" "Fnum_eq" "Fnum_ge" "Fnum_gt" "Fnum_le" "Fnum_lt" "Fnum_ne"
     "Fnumberp" "Fnumerator" "Fnunion" "Foddp" "Fopen"
     #+translator-supports-clos "Foptimize_slot_access"
     #+translator-supports-clos "Foptimize_slot_accesses"
     "Foutput_stream_p" "Fpackage_name" "Fpackage_nicknames"
     "Fpackage_shadowing_symbols" "Fpackage_use_list" "Fpackage_used_by_list"
     "Fpackagep" "Fpairlis" "Fparse_integer" "Fparse_namestring" "Fpathname"
     "Fpathname_device" "Fpathname_directory" "Fpathname_host"
     "Fpathname_name" "Fpathname_type" "Fpathname_version" "Fpathnamep"
     "Fpeek_char"
     #+translator-supports-clos "Fpermit_metaobject_reinitialization"
     "Fphase" "Fplusp" "Fposition" "Fposition_if" "Fposition_if_not"
     "Fpprint" "Fprin1" "Fprin1_to_string" "Fprinc" "Fprinc_to_string"
     "Fprint" #+translator-supports-clos "Fprint_object"
     "Fprobe_file" "Frandom" "Frandom_state_p" "Frassoc" "Frassoc_if"
     "Frassoc_if_not" "Frational" "Frationalize" "Frationalp" "Fratiop"
     "Fread" "Fread_byte" "Fread_char" "Fread_char_no_hang"
     "Fread_delimited_list" "Fread_from_string" "Fread_line"
     "Fread_preserving_whitespace" "Freadtablep" "Frealp" "Frealpart"
     #+translator-supports-clos "Frecord_method_combination_function"
     "Freduce" #+translator-supports-clos "Freinitialize_instance"
     "Frem" "Fremhash" "Fremove"
     #+translator-supports-clos "Fremove_direct_subclass"
     "Fremove_duplicates" "Fremove_if" "Fremove_if_not"
     #+translator-supports-clos "Fremove_method"
     "Fremprop" "Frename_file" "Frename_package" "Freplace" "Frest"
     "Frevappend" "Freverse" "Froom" "Fround" "Frow_major_aref" "Frplaca"
     "Frplacd" "Fsbit" "Fscale_float" "Fschar" "Fsearch" "Fsecond"
     "Fsequencep" "Fset" "Fset_caaaar" "Fset_caaadr" "Fset_caaar"
     "Fset_caadar" "Fset_caaddr" "Fset_caadr" "Fset_caar" "Fset_cadaar"
     "Fset_cadadr" "Fset_cadar" "Fset_caddar" "Fset_cadddr" "Fset_caddr"
     "Fset_cadr" "Fset_car" "Fset_cdaaar" "Fset_cdaadr" "Fset_cdaar"
     "Fset_cdadar" "Fset_cdaddr" "Fset_cdadr" "Fset_cdar" "Fset_cddaar"
     "Fset_cddadr" "Fset_cddar" "Fset_cdddar" "Fset_cddddr" "Fset_cdddr"
     "Fset_cddr" "Fset_cdr" "Fset_char"
     #+translator-supports-clos "Fset_class_direct_subclasses"
     #+translator-supports-clos "Fset_class_finalized_p"
     #+translator-supports-clos "Fset_class_fully_defined_p"
     "Fset_difference" "Fset_elt" "Fset_exclusive_or" "Fset_fdefinition"
     "Fset_fill_pointer" "Fset_foreign_pointer_address"
     "Fset_foreign_pointer_type" "Fset_foreign_string_value"
     "Fset_foreign_value"
     #+translator-supports-clos "Fset_generic_function_initial_methods"
     #+translator-supports-clos "Fset_generic_function_methods"
     "Fset_get" "Fset_getf" "Fset_gethash" "Fset_macro_character"
     "Fset_macro_function"
     #+translator-supports-clos "Fset_method_generic_function"
     "Fset_package" "Fset_row_major_aref" "Fset_schar" "Fset_setf_function"
     #+translator-supports-clos "Fset_slot_value"
     #+translator-supports-clos "Fset_standard_object_ref"
     "Fset_symbol_function" "Fset_symbol_plist" "Fset_syntax_from_char"
     "Fsetf_function" "Fseventh"
     #+translator-supports-clos "Fshared_initialize"
     #+translator-supports-clos "Fshared_slot_definition_p"
     "Fshort_site_name" "Fsignum" "Fsimple_array_p" "Fsimple_bit_vector_p"
     "Fsimple_string_p" "Fsimple_vector_p" "Fsin" "Fsinh" "Fsixth" "Fsleep"
     #+translator-supports-clos "Fslot_boundp"
     #+translator-supports-clos "Fslot_boundp_using_class"
     #+translator-supports-clos "Fslot_definition_allocation"
     #+translator-supports-clos "Fslot_definition_initargs"
     #+translator-supports-clos "Fslot_definition_initform"
     #+translator-supports-clos "Fslot_definition_initfunction"
     #+translator-supports-clos "Fslot_definition_location"
     #+translator-supports-clos "Fslot_definition_name"
     #+translator-supports-clos "Fslot_definition_readers"
     #+translator-supports-clos "Fslot_definition_type"
     #+translator-supports-clos "Fslot_definition_writers"
     #+translator-supports-clos "Fslot_exists_p"
     #+translator-supports-clos "Fslot_makunbound"
     #+translator-supports-clos "Fslot_makunbound_using_class"
     #+translator-supports-clos "Fslot_missing"
     #+translator-supports-clos "Fslot_unbound"
     #+translator-supports-clos "Fslot_value"
     #+translator-supports-clos "Fslot_value_using_class"
     "Fsome" "Fsort" "Fsqrt" "Fstable_sort" "Fstandard_char_p"
     "Fstandard_object_p" #+translator-supports-clos "Fstandard_object_ref"
     "Fstationary_object_p" "Fstream_element_type" "Fstreamp" "Fstring"
     "Fstring_append" "Fstring_capitalize" "Fstring_downcase" "Fstring_eq"
     "Fstring_equal" "Fstring_ge" "Fstring_greaterp" "Fstring_gt"
     "Fstring_input_stream_p" "Fstring_le" "Fstring_left_trim"
     "Fstring_lessp" "Fstring_lt" "Fstring_ne" "Fstring_not_equal"
     "Fstring_not_greaterp" "Fstring_not_lessp" "Fstring_output_stream_p"
     "Fstring_right_trim" "Fstring_stream_index" "Fstring_stream_p"
     "Fstring_trim" "Fstring_upcase" "Fstringp" "Fstructure_object_p" "Fsub1"
     "Fsublis" "Fsubseq" "Fsubsetp" "Fsubst" "Fsubst_if" "Fsubst_if_not"
     "Fsubstitute" "Fsubstitute_if" "Fsubstitute_if_not" "Fsubtypep" "Fsvref"
     "Fsxhash" "Fsymbol_function" "Fsymbol_name" "Fsymbol_package"
     "Fsymbol_plist" "Fsymbol_value" "Fsymbolp" "Ftailp" "Ftan" "Ftanh"
     "Ftenth" "Fterpri" "Fthird" "Ftimes" "Ftotal_memory_used" "Ftree_equal"
     "Ftruename" "Ftruncate" "Ftwo_way_stream_p" "Ftype_of"
     "Ftyped_foreign_aref" "Ftypep" "Fundefine_foreign_type" "Funion"
     "Funread_char" #+translator-supports-clos "Fupdate_initial_methods"
     #+translator-supports-clos "Fupdate_instance_for_different_class"
     "Fupgraded_array_element_type" "Fupper_case_p" "Fuse_package"
     "Fuser_homedir_pathname"
     #+translator-supports-clos "Fvalid_change_class_initargs"
     #+translator-supports-clos "Fvalid_creation_initargs"
     #+translator-supports-clos "Fvalid_reinitialization_initargs"
     #+translator-supports-clos "Fvalidate_superclass"
     "Fvalues" "Fvalues_list" "Fvector" "Fvector_pop" "Fvector_push"
     "Fvector_push_extend" "Fvectorp" "Fwarn" "Fwrite" "Fwrite_byte"
     "Fwrite_char" "Fwrite_line" "Fwrite_string" "Fwrite_to_string" "Fxor"
     "Fy_or_n_p" "Fyes_or_no_p" "Fzerop"
     #+translator-supports-clos "GENERIC_FUNCTION_CALL"
     #+translator-supports-clos "GENERIC_FUNCTION_CALL_1"
     #+translator-supports-clos "GENERIC_FUNCTION_CALL_10"
     #+translator-supports-clos "GENERIC_FUNCTION_CALL_2"
     #+translator-supports-clos "GENERIC_FUNCTION_CALL_3"
     #+translator-supports-clos "GENERIC_FUNCTION_CALL_4"
     #+translator-supports-clos "GENERIC_FUNCTION_CALL_5"
     #+translator-supports-clos "GENERIC_FUNCTION_CALL_6"
     #+translator-supports-clos "GENERIC_FUNCTION_CALL_7"
     #+translator-supports-clos "GENERIC_FUNCTION_CALL_8"
     #+translator-supports-clos "GENERIC_FUNCTION_CALL_9"
     #+translator-supports-clos "GENERIC_FUNCTION_CALL_ARG"
     #+translator-supports-clos "GENERIC_FUNCTION_CALL_START"
     "GRAPHIC_CHAR_P" "HASH_TABLE_P" "HUGE" "HUGE_VAL"
     "IARRAY_DIMENSION_LIMIT" "IARRAY_RANK_LIMIT" "IARRAY_TOTAL_SIZE_LIMIT"
     "ICHAR" "ICHAR_BITS" "ICHAR_CODE" "ICHAR_CONTROL_BIT" "ICHAR_FONT"
     "ICHAR_HYPER_BIT" "ICHAR_INT" "ICHAR_META_BIT" "ICHAR_SUPER_BIT"
     "ICHAR_UPCASE" "IDENTITY" "IDOUBLE" "IDOUBLE1" "IFIX" "IFUNC" "IINTEGER"
     #+translator-supports-clos "IMETHOD_ARGUMENT"
     #+translator-supports-clos "IMETHOD_OPTIONAL_ARGUMENT_P"
     "IMMEDIATE_BYTE_SPECIFIERS" "IMOST_NEGATIVE_FIXNUM"
     "IMOST_POSITIVE_FIXNUM" "IMPORTED_SYMBOL" "INCLUDE_LISP_PACKAGE"
     "INCLUDE_LISP_PACKAGE_SELECTIVELY" "INITIAL_PACKAGE" "INITIAL_SYMBOL"
     "INIT_ARGS" "INIT_ARGS_nonrelocating" "INPUT_STREAM_P"
     #+translator-supports-clos "INSTANCE_WRAPPER"
     "INTEGERP" "INTEGER_TO_CHAR" "INTEGER_TO_INT" "INTEGER_TO_INT64" "INTEGER_TO_LONG"
     "INTEGER_TO_SHORT" "INTEGER_TO_UNSIGNED_CHAR" "INTEGER_TO_UNSIGNED_LONG"
     "INTEGER_TO_UNSIGNED_SHORT" "INTERACTION_STREAM_P"
     "INTERNAL_TIME_UNITS_PER_SECOND" "INT_CHAR" "INT_TO_FIXNUM"
     "INT_TO_INTEGER" "INT64_TO_INTEGER"
     "ISAREF_0" "ISAREF_1" "ISAREF_2" "ISAREF_3" "ISAREF_4"
     "ISAREF_5" "ISAREF_6" "ISAREF_7" "ISASET_0" "ISASET_1" "ISASET_2"
     "ISASET_3" "ISASET_4" "ISASET_5" "ISASET_6" "ISASET_7" "ISCHAR"
     "ISTRING" "ISVREF" "ISVSET" "KEYWORDP" "KEYWORD_ARG" "KEYWORD_ARGS_0"
     "KEYWORD_ARGS_1" "KEYWORD_ARGS_10" "KEYWORD_ARGS_11" "KEYWORD_ARGS_2"
     "KEYWORD_ARGS_3" "KEYWORD_ARGS_4" "KEYWORD_ARGS_5" "KEYWORD_ARGS_6"
     "KEYWORD_ARGS_7" "KEYWORD_ARGS_8" "KEYWORD_ARGS_9"
     "KEYWORD_ARG_ALLOW_OTHER_KEYS" "KEYWORD_ARG_P" "KLUDGE_DOUBLE_FLOATS"
     "LAZILY_INITIALIZED_PACKAGES" "LISP_STACK_SIZE" "LISTP" "LIST_0"
     "LIST_1" "LIST_10" "LIST_11" "LIST_12" "LIST_13" "LIST_14" "LIST_15"
     "LIST_16" "LIST_17" "LIST_18" "LIST_19" "LIST_2" "LIST_20" "LIST_21"
     "LIST_22" "LIST_23" "LIST_24" "LIST_25" "LIST_26" "LIST_27" "LIST_28"
     "LIST_29" "LIST_3" "LIST_30" "LIST_31" "LIST_4" "LIST_5" "LIST_6"
     "LIST_7" "LIST_8" "LIST_9" "LIST_STAR_2" "LIST_STAR_3" "LIST_VALUES"
     "LOCAL_AREA_INCREMENT" "LOCAL_AREA_SIZE" "LOG_MAX_ISYMBOLS_PER_PACKAGE"
     "LONG_TO_FIXNUM" "LONG_TO_INTEGER" "LOWER_CASE_P" "L_ctermid"
     "L_cuserid" "L_tmpnam" "MAKE_BINDING" "MAKE_CHAR" "MAKE_CHR"
     "MAKE_FOREIGN_POINTER" "MAKE_INTEGER" "MAKE_LEXC" "MAKE_NEW_BINDING"
     "MAKE_STRUCTURE" "MAX" "MAXARGS"
     #+translator-supports-clos "METHOD_ARGUMENT"
     #+translator-supports-clos "METHOD_COMBINATION_FUNCTION"
     #+translator-supports-clos "METHOD_COMBINATION_NAME"
     #+translator-supports-clos "METHOD_COMBINATION_OPTIONS"
     #+translator-supports-clos "METHOD_COMBINATION_P"
     #+translator-supports-clos "METHOD_KEY_P"
     #+translator-supports-clos "METHOD_KEY_VALUE"
     #+translator-supports-clos "METHOD_OPTIONAL_ARGUMENT_P"
     #+translator-supports-clos "METHOD_REST_LIST"
     "MIN" "MOST_NEGATIVE_FIXNUM" "MOST_POSITIVE_FIXNUM"
     "MULTIPLE_VALUES_LIMIT" "MVSR" "MVS_0" "MVS_1" "MVS_10" "MVS_2" "MVS_3"
     "MVS_4" "MVS_5" "MVS_6" "MVS_7" "MVS_8" "MVS_9" "MV_FUNCALL" "MV_LIST"
     "M_1_PI" "M_2_PI" "M_2_SQRTPI" "M_CAAAAR" "M_CAAADR" "M_CAAAR"
     "M_CAADAR" "M_CAADDR" "M_CAADR" "M_CAAR" "M_CADAAR" "M_CADADR" "M_CADAR"
     "M_CADDAR" "M_CADDDR" "M_CADDR" "M_CADR" "M_CAR" "M_CDAAAR" "M_CDAADR"
     "M_CDAAR" "M_CDADAR" "M_CDADDR" "M_CDADR" "M_CDAR" "M_CDDAAR" "M_CDDADR"
     "M_CDDAR" "M_CDDDAR" "M_CDDDDR" "M_CDDDR" "M_CDDR" "M_CDR" "M_E"
     "M_EIGHTH" "M_FIFTH" "M_FIRST" "M_FOURTH" "M_LN10" "M_LN2" "M_LOG10E"
     "M_LOG2E" "M_NINTH" "M_NTH" "M_NTH_0" "M_NTH_1" "M_NTH_10" "M_NTH_11"
     "M_NTH_12" "M_NTH_13" "M_NTH_14" "M_NTH_15" "M_NTH_16" "M_NTH_17"
     "M_NTH_18" "M_NTH_19" "M_NTH_2" "M_NTH_20" "M_NTH_21" "M_NTH_22"
     "M_NTH_23" "M_NTH_24" "M_NTH_25" "M_NTH_26" "M_NTH_27" "M_NTH_28"
     "M_NTH_29" "M_NTH_3" "M_NTH_30" "M_NTH_31" "M_NTH_32" "M_NTH_33"
     "M_NTH_34" "M_NTH_35" "M_NTH_36" "M_NTH_37" "M_NTH_38" "M_NTH_39"
     "M_NTH_4" "M_NTH_40" "M_NTH_5" "M_NTH_6" "M_NTH_7" "M_NTH_8" "M_NTH_9"
     "M_PI" "M_PI_2" "M_PI_4" "M_REST" "M_SECOND" "M_SEVENTH" "M_SIXTH"
     "M_SQRT1_2" "M_SQRT2" "M_TENTH" "M_THIRD" "Multiple_values_limit"
     "NAMED_LISTP" "NAMED_LIST_P" "NAMED_SIMPLE_VECTOR_P" "NAMED_STRUCTURE_P"
     "NCONC_2" "NCONS_IF" "NEQ" "NEQL" "NEW_BIGNUMS" "NEW_BINDING"
     "NEW_INITIAL_KEYWORD" "NEW_INITIAL_SYMBOL" "NEW_SYMBOL"
     #+translator-supports-clos "NEXT_METHOD_P"
     "NIL" "NINTH" "NOT" "NTH" "NTH_0" "NTH_1" "NTH_10" "NTH_11" "NTH_12"
     "NTH_13" "NTH_14" "NTH_15" "NTH_16" "NTH_17" "NTH_18" "NTH_19" "NTH_2"
     "NTH_20" "NTH_21" "NTH_22" "NTH_23" "NTH_24" "NTH_25" "NTH_26" "NTH_27"
     "NTH_28" "NTH_29" "NTH_3" "NTH_30" "NTH_31" "NTH_32" "NTH_33" "NTH_34"
     "NTH_35" "NTH_36" "NTH_37" "NTH_38" "NTH_39" "NTH_4" "NTH_40" "NTH_5"
     "NTH_6" "NTH_7" "NTH_8" "NTH_9" "NTH_VALUE" "NULL" "NUMBERP" "NUMERATOR"
     "NUM_EQ" "NUM_GE" "NUM_GT" "NUM_LE" "NUM_LT" "NUM_NE" "N_IEEE_EXCEPTION"
     "Nil" "OLD_POP_SPECIAL" "OLD_PUSH_SPECIAL" "OPT" "OPTIONAL_ARG"
     "OPTIONAL_ARGS_0" "OPTIONAL_ARGS_1" "OPTIONAL_ARGS_2" "OPTIONAL_ARGS_3"
     "OPTIONAL_ARG_P" "OPTIONAL_ARG_P_nonrelocating"
     "OPTIONAL_ARG_nonrelocating" "OPT_FLAG" "OUTPUT_STREAM_P" "OVERFLOW"
     "PACKAGEP" "PACKAGE_NAME" "PACKAGE_NICKNAMES"
     "PACKAGE_SHADOWING_SYMBOLS" "PACKAGE_USED_BY_LIST" "PACKAGE_USE_LIST"
     "PATHNAMEP" "PATHNAME_HOST" "PLOSS" "POINTER_FOREIGN_TYPE_P"
     "POINTER_FOREIGN_TYPE_TO_TYPE" "POP_AREA" "POP_CATCH"
     "POP_LOCAL_ALLOCATION" "POP_PROGV" "POP_SPECIAL" "POP_UNWIND_PROTECT"
     "POP_VALUES" "PRIMITIVE_FOREIGN_TYPE_P" "PROGV" "PROTECTI_1"
     "PROTECTI_10" "PROTECTI_2" "PROTECTI_3" "PROTECTI_4" "PROTECTI_5"
     "PROTECTI_6" "PROTECTI_7" "PROTECTI_8" "PROTECTI_9" "PROTECT_1"
     "PROTECT_10" "PROTECT_2" "PROTECT_3" "PROTECT_4" "PROTECT_5" "PROTECT_6"
     "PROTECT_7" "PROTECT_8" "PROTECT_9" "PROTECT_GLOBAL" "PROTECT_GLOBAL_1"
     "PROTECT_GLOBAL_10" "PROTECT_GLOBAL_2" "PROTECT_GLOBAL_3"
     "PROTECT_GLOBAL_4" "PROTECT_GLOBAL_5" "PROTECT_GLOBAL_6"
     "PROTECT_GLOBAL_7" "PROTECT_GLOBAL_8" "PROTECT_GLOBAL_9"
     "PROTECT_LOCALS" "PROTECT_MARKER" "PUSH_AREA" "PUSH_CATCH"
     "PUSH_LOCAL_ALLOCATION" "PUSH_PROGV" "PUSH_SPECIAL"
     "PUSH_UNWIND_PROTECT" "P_tmpdir" "Q_T"
     "Qinitialize_do_external_symbols_iterator" "Qnil" "Qt" "RANDOM_STATE_P"
     "RATIONALP" "RATIOP" "RATIO_DENOMINATOR" "RATIO_NUMERATOR" "READTABLEP"
     "REALP" "REQUIRED_ARG" "REQUIRED_ARGS_0" "REQUIRED_ARGS_1"
     "REQUIRED_ARGS_2" "REQUIRED_ARGS_3" "REQUIRED_ARGS_4" "REQUIRED_ARGS_5"
     "REQUIRED_ARG_nonrelocating" "REST" "RESTORE_CURRENT_AREA"
     "RESTORE_FRONTIER" "RESTORE_STACK" "RESTORE_VALUES" "REST_ARG"
     "REST_FLAG" "RETURNFLOAT" "RETURN_MULTIPLE_VALUES" "ROW_MAJOR_AREF"
     "ROW_MAJOR_INDEX_0" "ROW_MAJOR_INDEX_1" "ROW_MAJOR_INDEX_2"
     "ROW_MAJOR_INDEX_3" "ROW_MAJOR_INDEX_4" "ROW_MAJOR_INDEX_5"
     "ROW_MAJOR_INDEX_6" "ROW_MAJOR_INDEX_7" "RPLACA" "RPLACB" "RPLACD"
     "RUNTIME_ERROR" "SAREF2" "SAREF_0" "SAREF_1" "SAREF_2" "SAREF_3"
     "SAREF_4" "SAREF_5" "SAREF_6" "SAREF_7" "SASET2" "SASET_0" "SASET_1"
     "SASET_2" "SASET_3" "SASET_4" "SASET_5" "SASET_6" "SASET_7" "SAVE_ARGS"
     "SAVE_CURRENT_AREA" "SAVE_FRONTIER" "SAVE_MORE_VALUES" "SAVE_STACK"
     "SAVE_VALUES" "SBIT0" "SBIT1" "SBIT2" "SBIT3" "SBIT4" "SBIT5" "SBIT6"
     "SBIT7" "SBITP_1" "SBIT_1" "SCHAR" "SECOND" "SEQUENCEP" "SET"
     "SETF_FUNCTION" #+translator-supports-clos "SETF_class_name"
     #+translator-supports-clos "SETF_class_status_bits"
     #+translator-supports-clos "SETF_metaobject_documentation"
     #+translator-supports-clos "SETF_metaobject_name"
     #+translator-supports-clos "SETF_slot_definition_location"
     #+translator-supports-clos "SETF_slot_value_using_class"
     #+translator-supports-clos "SETF_valid_change_class_initargs"
     #+translator-supports-clos "SETF_valid_creation_initargs"
     #+translator-supports-clos "SETF_valid_reinitialization_initargs"
     "SET_CAR" "SET_CDR" "SET_CHAR" "SET_CURRENT_AREA" "SET_FILL_POINTER"
     "SET_FOREIGN_TYPE_READER" "SET_FOREIGN_TYPE_WRITER" "SET_ICHAR"
     "SET_ISCHAR" "SET_ROW_MAJOR_AREF" "SET_SBIT0" "SET_SBIT1" "SET_SBIT2"
     "SET_SBIT3" "SET_SBIT4" "SET_SBIT5" "SET_SBIT6" "SET_SBIT7" "SET_SBIT_1"
     "SET_SCHAR" "SET_SETF_FUNCTION"
     #+translator-supports-clos "SET_SLOT_VALUE"
     #+translator-supports-clos "SET_SLOT_VALUE_INDEXED"
     #+translator-supports-clos "SET_SLOT_VALUE_USING_WRAPPER"
     "SET_SVREF" "SET_SYMBOL_FUNCTION" "SET_SYMBOL_FUNCTION_LOCATION"
     "SET_SYMBOL_PLIST" "SET_SYMBOL_VALUE" "SET_SYMBOL_VALUE_LOCATION"
     "SEVENTH" "SHORT_FLOAT_TO_FLOAT" "SHORT_TO_FIXNUM" "SHORT_TO_INTEGER"
     "SIGFPE_ABORT" "SIGFPE_DEFAULT" "SIGFPE_IGNORE"
     "SIMPLE_ARRAY_ANY_1_LENGTH" "SIMPLE_ARRAY_ANY_1_P" "SIMPLE_ARRAY_P"
     "SIMPLE_BIT_VECTOR_P" "SIMPLE_STRING_P" "SIMPLE_STRING_TO_CHAR_POINTER"
     "SIMPLE_VECTOR_P" "SING" "SINGLE_FLOAT_TO_FLOAT" "SIXTH"
     #+translator-supports-clos "SI_ADJUST_METHOD_FRAME_ARGQ"
     "SI_ADVANCE_FRONTIER" "SI_ALIGNED_TYPE" "SI_ALIGNMENT_FOR"
     "SI_ALIGNMENT_MARKER" "SI_ALLOC" "SI_ALLOC_LIMIT" "SI_ARRAY_ETYPE"
     "SI_BITS_PER_BYTE" "SI_BITS_PER_FIXNUM" "SI_BITS_PER_OBJECT"
     "SI_BITS_TYPE" "SI_BITS_TYPE_MASK" "SI_BITS_TYPE_SHIFT" "SI_BOOT_CLOS"
     #+translator-supports-clos "SI_CACHE_NUMBER_ENTRY_MAX"
     "SI_CALL_ARGUMENTS_LIMIT" #+translator-supports-clos "SI_CALL_METHOD"
     "SI_CATCH_THROWN" #+translator-supports-clos "SI_CHANGE_CLASS_INITARGS"
     "SI_CHAR_SHIFT" "SI_CHAR_TAG" "SI_CHECK_CONS_SPACE"
     #+translator-supports-clos "SI_CLASS_DEFAULT_INITARGS"
     #+translator-supports-clos "SI_CLASS_DEFAULT_INITARGS_BOUNDP"
     #+translator-supports-clos "SI_CLASS_DIRECT_SUBCLASSES"
     #+translator-supports-clos "SI_CLASS_DIRECT_SUBCLASSES_BOUNDP"
     #+translator-supports-clos "SI_CLASS_PRECEDENCE_LIST"
     #+translator-supports-clos "SI_CLASS_PRECEDENCE_LIST_BOUNDP"
     #+translator-supports-clos "SI_CLASS_PROTOTYPE"
     #+translator-supports-clos "SI_CLASS_PROTOTYPE_BOUNDP"
     #+translator-supports-clos "SI_CLASS_SHARED_SLOT_LOCATIONS"
     #+translator-supports-clos "SI_CLASS_SHARED_SLOT_LOCATIONS_BOUNDP"
     #+translator-supports-clos "SI_CLASS_SLOTS"
     #+translator-supports-clos "SI_CLASS_SLOTS_ALIST"
     #+translator-supports-clos "SI_CLASS_SLOTS_ALIST_BOUNDP"
     #+translator-supports-clos "SI_CLASS_SLOTS_BOUNDP"
     #+translator-supports-clos "SI_CLASS_WRAPPER"
     #+translator-supports-clos "SI_CLASS_WRAPPER_BOUNDP"
     "SI_CLOS_CHECK_INITARGS" #+translator-supports-clos "SI_CLOS_DOT_H"
     "SI_CLOS_RECORD_CACHE_STATISTICS" "SI_CLOS_USE_GENERIC_FUNCTION_CACHES"
     "SI_CONS" "SI_CONSES_HAVE_HEADERS" "SI_CONTINUE_UNWINDING"
     "SI_COPYING_COLLECTOR" "SI_COUNTER_VAR" "SI_DEBUG_INLINE"
     "SI_DIMENSION_ETYPE" "SI_DISPLACED_INDEX_OFFSET" "SI_DO_UCONFIG"
     "SI_DYNAMICNESS_LABELED" "SI_Declare_static_relocation_field"
     #+translator-supports-clos "SI_EFFECTIVE_METHOD_APPLICABLE_METHODS"
     #+translator-supports-clos "SI_EFFECTIVE_METHOD_ARGUMENT_INFO"
     #+translator-supports-clos "SI_EFFECTIVE_METHOD_GENERIC_FUNCTION"
     #+translator-supports-clos "SI_EFFECTIVE_METHOD_KEYS"
     #+translator-supports-clos "SI_EFFECTIVE_METHOD_KEY_TABLE"
     #+translator-supports-clos "SI_EFFECTIVE_METHOD_METHOD"
     #+translator-supports-clos "SI_EFFECTIVE_METHOD_METHOD_TABLE"
     #+translator-supports-clos "SI_EFFECTIVE_METHOD_NEXT_METHOD_P"
     #+translator-supports-clos "SI_EFFECTIVE_METHOD_NEXT_METHOD_TABLE"
     #+translator-supports-clos "SI_EFFECTIVE_METHOD_START"
     #+translator-supports-clos "SI_ENCODED_LAMBDA_LIST"
     #+translator-supports-clos "SI_ENCODED_LAMBDA_LIST_BOUNDP"
     #+translator-supports-clos "SI_ENCODED_LL_ALWKYP"
     #+translator-supports-clos "SI_ENCODED_LL_ALWKY_MASK"
     #+translator-supports-clos "SI_ENCODED_LL_ENCODING"
     #+translator-supports-clos "SI_ENCODED_LL_EXTRACT_ARG_COUNT"
     #+translator-supports-clos "SI_ENCODED_LL_KEYP"
     #+translator-supports-clos "SI_ENCODED_LL_KEYS"
     #+translator-supports-clos "SI_ENCODED_LL_KEY_MASK"
     #+translator-supports-clos "SI_ENCODED_LL_NON_POSITIONAL_MASK"
     #+translator-supports-clos "SI_ENCODED_LL_NON_POSITIONAL_P"
     #+translator-supports-clos "SI_ENCODED_LL_POSITIONAL"
     #+translator-supports-clos "SI_ENCODED_LL_POSITIONAL_MASK"
     #+translator-supports-clos "SI_ENCODED_LL_POSITIONAL_SHIFT"
     #+translator-supports-clos "SI_ENCODED_LL_REQUIRED"
     #+translator-supports-clos "SI_ENCODED_LL_REQUIRED_MASK"
     #+translator-supports-clos "SI_ENCODED_LL_REQUIRED_SHIFT"
     "SI_END_UCONFIG" "SI_ENUM_EQ" "SI_ENUM_GE" "SI_ENUM_GT" "SI_ENUM_LE"
     "SI_ENUM_LT" "SI_ENUM_NE"
     #+translator-supports-clos "SI_FINISH_PUSHING_OBJECT_VECTOR"
     "SI_FIXNUM_SHIFT" "SI_FIXNUM_TAG_MASK" "SI_FIXNUM_TAG_VALUE"
     "SI_FLUSH_ALLOC_CACHE" "SI_FOREIGN_TYPE_INFO" "SI_FORWARDING_MARKER"
     "SI_FRONTIER" "SI_FRONTIER_AS_CONS" "SI_FRONTIER_CONS_RESULT"
     "SI_FUNCTIONP" "SI_FUNCTION_ENTRY" "SI_FUNCTION_ENV"
     "SI_FUNCTION_FLAGS_WIDTH"
     #+translator-supports-clos "SI_FUNCTION_GENERIC_P"
     "SI_FUNCTION_NARGS" "SI_FUNCTION_OPTIONAL_P" "SI_FUNCTION_SIMPLE_P"
     "SI_FUNCTION_STUFF" "SI_FUNCTION_VARIADIC_P" "SI_GCALIGN_WIDTH"
     "SI_GCLENGTH_WIDTH" "SI_GCRELOCATE_WIDTH"
     "SI_GENERAL_ARRAY_DISPLACED_TO" "SI_GENERAL_ARRAY_ETYPE"
     "SI_GENERAL_ARRAY_ETYPEP" "SI_GENERAL_ARRAY_P" "SI_GENERAL_ARRAY_RANK"
     "SI_GENERAL_NVARRAY_DIMENSION" "SI_GENERAL_NVARRAY_DIMENSIONS"
     "SI_GENERAL_VECTOR_FILL_POINTER" "SI_GENERAL_VECTOR_TOTAL_SIZE"
     #+translator-supports-clos "SI_GENERIC_FLAG"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_ARGUMENT_PRECEDENCE_MAP"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_ARGUMENT_PRECEDENCE_MAP_BOUNDP"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_CALL"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_CALL_END"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_CALL_FRAME"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_CALL_USING_FRAME"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_CRITICAL_METHODS"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_CRITICAL_METHODS_BOUNDP"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_EFFECTIVE_METHODS"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_EFFECTIVE_METHODS_BOUNDP"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_EQL_SPECIALIZED_METHODS"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_EQL_SPECIALIZED_METHODS_BOUNDP"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_INITIAL_METHODS"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_INITIAL_METHODS_BOUNDP"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_METHODS"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_METHODS_BOUNDP"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_SPECIALIZED_POSITIONS"
     #+translator-supports-clos "SI_GENERIC_FUNCTION_SPECIALIZED_POSITIONS_BOUNDP"
     "SI_GREATEST_INSTANCE_TYPE" "SI_GREATEST_STANDARD_OBJECT_TYPE"
     "SI_GREATEST_SYMBOL_TYPE" "SI_HEADER" "SI_HEADER_FOR_GENERAL_ARRAY"
     "SI_HEADER_FOR_PRIMITIVE_VECTOR" "SI_HEADER_SHIFT" "SI_HEADER_TAG"
     "SI_IARG" #+translator-supports-clos "SI_IMETHOD_FRAME_REF"
     "SI_IMMEDIATEP" "SI_INCLUDE_LISP_PACKAGE_SELECTIVELY"
     "SI_INITIALIZER_FOR_CONS" "SI_INITIALIZE_FOREIGN_TYPE_INFO"
     "SI_INIT_CONS_HEADER" "SI_INIT_CONS_INFO" "SI_INIT_CONS_RELOC_WORD"
     #+translator-supports-clos "SI_INIT_EFFECTIVE_METHOD_FIELDS"
     "SI_INIT_FUNCTION"
     #+translator-supports-clos "SI_INIT_OBJECT_VECTOR_HEADER"
     #+translator-supports-clos "SI_INIT_PV_HWORDS"
     "SI_INIT_RTL_CORE" "SI_INIT_SYMBOL_HEADER"
     "SI_INIT_SYMBOL_RELOCATION_WORD" "SI_INIT_WRAPPERS"
     "SI_INIT_full_reader" "SI_INIT_usersyms" "SI_INLINED_CONS_ALLOCATOR"
     "SI_INSTANCEP" "SI_INSTANCE_FIELD" "SI_INSTANCE_HEADER"
     "SI_INSTANCE_PRED" "SI_IRET" "SI_IROW_MAJOR_INDEX_0"
     "SI_IROW_MAJOR_INDEX_1" "SI_IROW_MAJOR_INDEX_2" "SI_IROW_MAJOR_INDEX_3"
     "SI_IROW_MAJOR_INDEX_4" "SI_IROW_MAJOR_INDEX_5" "SI_IROW_MAJOR_INDEX_6"
     "SI_IROW_MAJOR_INDEX_7" "SI_ISCHAR" "SI_ISVREF" "SI_KERNEL_DOT_H"
     "SI_LEAST_INSTANCE_TYPE"
     #+translator-supports-clos "SI_LEAST_STANDARD_OBJECT_TYPE"
     "SI_LEAST_SYMBOL_TYPE" "SI_LENGTH_STATUS_WIDTH" "SI_LINTUSE"
     #+translator-supports-clos "SI_MAKE_ENCODED_LL"
     "SI_MAKE_TOKEN" #+translator-supports-clos "SI_METHODP"
     #+translator-supports-clos "SI_METHOD_ENTRY"
     #+translator-supports-clos "SI_METHOD_ENV"
     #+translator-supports-clos "SI_METHOD_FRAME_COPY"
     #+translator-supports-clos "SI_METHOD_FRAME_INTERNAL_FIELD"
     #+translator-supports-clos "SI_METHOD_FRAME_INTERNAL_FIELDS"
     #+translator-supports-clos "SI_METHOD_FRAME_INTERNAL_FIELD_INIT"
     #+translator-supports-clos "SI_METHOD_FRAME_INTERNAL_FIELD_INITIALIZED"
     #+translator-supports-clos "SI_METHOD_FRAME_KEY"
     #+translator-supports-clos "SI_METHOD_FRAME_LAST"
     #+translator-supports-clos "SI_METHOD_FRAME_LIST"
     #+translator-supports-clos "SI_METHOD_FRAME_REF"
     #+translator-supports-clos "SI_METHOD_FRAME_REST"
     #+translator-supports-clos "SI_METHOD_GENERIC_FUNCTION"
     #+translator-supports-clos "SI_METHOD_GENERIC_FUNCTION_BOUNDP"
     #+translator-supports-clos "SI_METHOD_KEYWORD_PARAMETER_MAP"
     #+translator-supports-clos "SI_METHOD_KEYWORD_PARAMETER_MAP_BOUNDP"
     "SI_MINIMUM_CPV_SIZE" "SI_NIL_IS_ZERO" "SI_NONHEADER_TAG"
     "SI_NONRELOCATABLE_MARKER" "SI_NONVECTOR_ARRAY_CONTENTS"
     #+translator-supports-clos "SI_NOT_ALIGNED"
     "SI_NO_APPLICABLE_METHOD_MARKER" "SI_NVARRAY_CONTENTS"
     "SI_OBJECT_INITIALIZERS_WORK" "SI_OPTIONAL_FLAG" "SI_OTHER_IMMED_SHIFT"
     "SI_OTHER_IMMED_TAG_MASK" "SI_POP_CATCH" "SI_POP_UNWIND_PROTECT"
     "SI_PRECEDES_ISYMBOLS" "SI_PREVENT_MISLINKING"
     "SI_PRIMITIVE_VECTOR_CONTENTS" "SI_PRIMITIVE_VECTOR_ETYPE"
     "SI_PRIMITIVE_VECTOR_ETYPEP" "SI_PRIMITIVE_VECTOR_LENGTH"
     "SI_PRIMITIVE_VECTOR_P" "SI_PROGV_CLEANUP_STACK" "SI_PUSH_CATCH"
     #+translator-supports-clos "SI_PV_HWORDS"
     "SI_QUICK_CONS" "SI_RANGED_INSTANCEP" "SI_RANGED_INSTANCEP_HELPER"
     "SI_RATIO_DENOMINATOR" "SI_RATIO_NUMERATOR" "SI_RELOAD_ALLOC_CACHE"
     "SI_SAVE_AREA_AND_FRONTIER" "SI_SBIT_ACCESS" "SI_SBIT_MASK"
     "SI_SEGMENTED_DYNAMIC_AREA" "SI_SEPARATE_HEADERS"
     #+translator-supports-clos "SI_SET_CLASS_DEFAULT_INITARGS"
     #+translator-supports-clos "SI_SET_CLASS_DIRECT_SUBCLASSES"
     #+translator-supports-clos "SI_SET_CLASS_PRECEDENCE_LIST"
     #+translator-supports-clos "SI_SET_CLASS_PROTOTYPE"
     #+translator-supports-clos "SI_SET_CLASS_SHARED_SLOT_LOCATIONS"
     #+translator-supports-clos "SI_SET_CLASS_SLOTS"
     #+translator-supports-clos "SI_SET_CLASS_SLOTS_ALIST"
     #+translator-supports-clos "SI_SET_CLASS_WRAPPER"
     #+translator-supports-clos "SI_SET_ENCODED_LAMBDA_LIST"
     #+translator-supports-clos "SI_SET_GENERIC_FUNCTION_ARGUMENT_PRECEDENCE_MAP"
     #+translator-supports-clos "SI_SET_GENERIC_FUNCTION_CRITICAL_METHODS"
     #+translator-supports-clos "SI_SET_GENERIC_FUNCTION_EFFECTIVE_METHODS"
     #+translator-supports-clos "SI_SET_GENERIC_FUNCTION_EQL_SPECIALIZED_METHODS"
     #+translator-supports-clos "SI_SET_GENERIC_FUNCTION_INITIAL_METHODS"
     #+translator-supports-clos "SI_SET_GENERIC_FUNCTION_METHODS"
     #+translator-supports-clos "SI_SET_GENERIC_FUNCTION_SPECIALIZED_POSITIONS"
     #+translator-supports-clos "SI_SET_METHOD_GENERIC_FUNCTION"
     #+translator-supports-clos "SI_SET_METHOD_KEYWORD_PARAMETER_MAP"
     "SI_SET_PRIMITIVE_VECTOR_LENGTH"
     #+translator-supports-clos "SI_SET_SLOT_DEFINITION_CONSTANT_INITFORM_P"
     #-translator-supports-clos "SI_SET_STANDARD_OBJECT_SLOT_VECTOR"
     "SI_SET_TAG" "SI_SIGNAL_CONDITIONS"
     #+translator-supports-clos "SI_SLOT_ACCESS_TYPE_CHECK"
     #+translator-supports-clos "SI_SLOT_DEFINITION_CONSTANT_INITFORM_P"
     #+translator-supports-clos "SI_SLOT_DEFINITION_CONSTANT_INITFORM_P_BOUNDP"
     #+translator-supports-clos "SI_STANDARD_INSTANCE_P"
     #+translator-supports-clos "SI_STANDARD_OBJECT_SLOTS"
     #+translator-supports-clos "SI_START_PUSHING_OBJECT_VECTOR"
     "SI_STATIC_HEADER" "SI_STATIC_HEADER_FOR_GENERAL_ARRAY"
     "SI_STATIC_HEADER_FOR_PRIMITIVE_VECTOR" "SI_STATIC_RELOCATION_INFO"
     "SI_STATIC_RELOCATION_SIZE" "SI_STATIC_RELOCATION_WORDS"
     "SI_STORED_OBJECT_FIELD" "SI_STORED_OBJECT_HAS_HEADER_P"
     "SI_STORED_OBJECT_HEADER_TYPE_FIELD" "SI_STORED_OBJECT_P"
     "SI_STORED_OBJECT_TYPE" "SI_STORED_OBJECT_TYPEP" "SI_STORED_TAG_VALUE"
     "SI_STRUCTURE_NAME" "SI_STRUCTURE_OBJECT_CPV" "SI_STRUCTURE_SLOTS"
     "SI_STUFF_WIDTH" #-translator-supports-clos "SI_SUPPORT_CLOS"
     "SI_SUPPORT_MF" "SI_SUPPORT_SF" "SI_SVARARGS_H" "SI_SYMBOL_PLIST"
     "SI_SYMNAME_INDEX_SHIFT" "SI_SYMNAME_OFFSET_MASK"
     "SI_SYMNAME_OFFSET_SHIFT" "SI_SYMNAME_OFFSET_WIDTH" "SI_SymFldBnd"
     #+translator-supports-clos "SI_TAG_CLASS_WRAPPER"
     #+translator-supports-clos "SI_TAG_EFFECTIVE_METHOD"
     "SI_TAG_FAST_CONS" "SI_TAG_FUNCTION" "SI_TAG_INSTANCE"
     "SI_TAG_INSTANCE_CONSTANT" #+translator-supports-clos "SI_TAG_METHOD"
     #+translator-supports-clos "SI_TAG_METHOD_COMBINATION"
     "SI_TAG_OF" #+translator-supports-clos "SI_TAG_STANDARD_INSTANCE"
     "SI_TAG_STORED" "SI_TAG_STORED_CONSTANT" "SI_TAG_STRUCTURE"
     "SI_TAG_WIDTH" "SI_TOKEN_TAG" "SI_TYPE_MASK" "SI_TYPE_WIDTH"
     "SI_Type_for_primitive_vector" "SI_Type_for_primitive_vector_constant"
     "SI_Type_for_structure" "SI_UCONFIGS" "SI_UCONFIG_BIGNUMS"
     "SI_UCONFIG_EVAL" "SI_UCONFIG_GC" "SI_UCONFIG_LAMBDA_KEYWORDS"
     "SI_UCONFIG_PACKAGES" "SI_UCONFIG_READER"
     "SI_UCONFIG_STANDARD_ERROR_HANDLING" "SI_UCONFIG_STANDARD_SYMBOLS"
     "SI_UCONFIG_STRUCTURES" "SI_UNADVANCED_FRONTIER"
     "SI_UNADVANCED_FRONTIER_AS_CONS" "SI_UNADVANCED_FRONTIER_CONS_RESULT"
     "SI_UNINITIALIZED_MARKER" "SI_UNTAG_INSTANCE" "SI_UNTAG_INSTANCE_TYPE"
     "SI_UNWIND_PROTECT_MARKER"
     #+translator-supports-clos "SI_VALIDATE_SLOT_ACCESS"
     #+translator-supports-clos "SI_VALIDATE_SLOT_READ"
     #+translator-supports-clos "SI_VALIDATE_SLOT_WRITE"
     "SI_VARIADIC_FLAG" "SI_VARIADIC_KEYWORD_FUNCTIONS"
     "SI_VECTOR_PRIMITIVE_P" "SI_VISIT_EXACTLY_ONCE"
     #+translator-supports-clos "SI_WRAPPER_CPV"
     #+translator-supports-clos "SI_WRAPPER_READ_TABLE"
     #+translator-supports-clos "SI_WRAPPER_TABLE_ACCESS"
     #+translator-supports-clos "SI_WRAPPER_WRITE_TABLE"
     "SI_etype" "SI_va_start" #+translator-supports-clos "SLOT_BOUNDP"
     #+translator-supports-clos "SLOT_BOUNDP_INDEXED"
     #+translator-supports-clos "SLOT_BOUNDP_USING_WRAPPER"
     #+translator-supports-clos "SLOT_EXISTS_P_INDEXED"
     #+translator-supports-clos "SLOT_EXISTS_P_USING_WRAPPER"
     #+translator-supports-clos "SLOT_MAKUNBOUND"
     #+translator-supports-clos "SLOT_MAKUNBOUND_INDEXED"
     #+translator-supports-clos "SLOT_MAKUNBOUND_USING_WRAPPER"
     #+translator-supports-clos "SLOT_VALUE"
     #+translator-supports-clos "SLOT_VALUE_INDEXED"
     #+translator-supports-clos "SLOT_VALUE_USING_WRAPPER"
     "STACK_LOC" "STACK_POP" "STACK_PUSH" "STACK_REF" "STANDARD_CHAR_P"
     "STANDARD_OBJECT_P" #+translator-supports-clos "STANDARD_OBJECT_REF"
     "STATIC_INCREMENT" "STATIC_SIZE" "STREAMP" "STRING" "STRINGP"
     "STRING_CHAR_P" "STRING_INPUT_STREAM_P" "STRING_OUTPUT_STREAM_P"
     "STRING_STREAM_P" "STRING_TO_CHAR_POINTER" "STRUCTURE_ELEMENT"
     "STRUCTURE_FIELD" "STRUCTURE_FOREIGN_TYPE_P"
     "STRUCTURE_OBJECT_COMPLEX_TYPEP" "STRUCTURE_OBJECT_P"
     "STRUCTURE_OBJECT_TYPEP" "SUPPLIEDP" "SUPPLIED_P" "SVREF" "SVSET"
     "SYMBOLP" "SYMBOL_FUNCTION" "SYMBOL_NAME" "SYMBOL_PACKAGE"
     "SYMBOL_PLIST" "SYMBOL_VALUE" "SYNONYM_STREAM_P" "Segment" "Stack_item"
     "T" "TAG_ARRAY" "TAG_BIGNUM" "TAG_BIT_VECTOR" "TAG_COMPILED_FUNCTION"
     "TAG_CONS" "TAG_DOUBLE_FLOAT" "TAG_ISYMBOL" "TAG_PACKAGE" "TAG_RATIO"
     "TAG_STRING" "TAG_VECTOR" "TENTH" "THIRD" "THROW" "TLOSS" "TOLOWER"
     "TOUPPER" "TRUE" "TRUEP" "TWO_WAY_STREAM_P" "TYPEP" "T_ATOM" "T_CAAAAR"
     "T_CAAADR" "T_CAAAR" "T_CAADAR" "T_CAADDR" "T_CAADR" "T_CAAR" "T_CADAAR"
     "T_CADADR" "T_CADAR" "T_CADDAR" "T_CADDDR" "T_CADDR" "T_CADR" "T_CAR"
     "T_CDAAAR" "T_CDAADR" "T_CDAAR" "T_CDADAR" "T_CDADDR" "T_CDADR" "T_CDAR"
     "T_CDDAAR" "T_CDDADR" "T_CDDAR" "T_CDDDAR" "T_CDDDDR" "T_CDDDR" "T_CDDR"
     "T_CDR" "T_COLLECT" "T_COLLECT_APPEND" "T_CONSP" "T_FIRST" "T_FOURTH"
     "T_LISTP" "T_MAKE_INTEGER" "T_R_M_S_AREF" "T_SECOND" "T_SYMBOLP"
     "T_THIRD" "T_VALUES_1" "UBYTE_16_ISAREF_0" "UBYTE_16_ISAREF_1"
     "UBYTE_16_ISAREF_2" "UBYTE_16_ISAREF_3" "UBYTE_16_ISAREF_4"
     "UBYTE_16_ISAREF_5" "UBYTE_16_ISAREF_6" "UBYTE_16_ISAREF_7"
     "UBYTE_16_ISASET_0" "UBYTE_16_ISASET_1" "UBYTE_16_ISASET_2"
     "UBYTE_16_ISASET_3" "UBYTE_16_ISASET_4" "UBYTE_16_ISASET_5"
     "UBYTE_16_ISASET_6" "UBYTE_16_ISASET_7" "UBYTE_16_R_M_S_AREF"
     "UBYTE_16_SAREF_0" "UBYTE_16_SAREF_1" "UBYTE_16_SAREF_2"
     "UBYTE_16_SAREF_3" "UBYTE_16_SAREF_4" "UBYTE_16_SAREF_5"
     "UBYTE_16_SAREF_6" "UBYTE_16_SAREF_7" "UBYTE_16_SARRAY_TO_USHORT_PTR"
     "UBYTE_16_SASET_0" "UBYTE_16_SASET_1" "UBYTE_16_SASET_2"
     "UBYTE_16_SASET_3" "UBYTE_16_SASET_4" "UBYTE_16_SASET_5"
     "UBYTE_16_SASET_6" "UBYTE_16_SASET_7" "UBYTE_32_ISAREF_0"
     "UBYTE_32_ISAREF_1" "UBYTE_32_ISAREF_2" "UBYTE_32_ISAREF_3"
     "UBYTE_32_ISAREF_4" "UBYTE_32_ISAREF_5" "UBYTE_32_ISAREF_6"
     "UBYTE_32_ISAREF_7" "UBYTE_32_ISASET_0" "UBYTE_32_ISASET_1"
     "UBYTE_32_ISASET_2" "UBYTE_32_ISASET_3" "UBYTE_32_ISASET_4"
     "UBYTE_32_ISASET_5" "UBYTE_32_ISASET_6" "UBYTE_32_ISASET_7"
     "UBYTE_32_R_M_S_AREF" "UBYTE_32_SAREF_0" "UBYTE_32_SAREF_1"
     "UBYTE_32_SAREF_2" "UBYTE_32_SAREF_3" "UBYTE_32_SAREF_4"
     "UBYTE_32_SAREF_5" "UBYTE_32_SAREF_6" "UBYTE_32_SAREF_7"
     "UBYTE_32_SASET_0" "UBYTE_32_SASET_1" "UBYTE_32_SASET_2"
     "UBYTE_32_SASET_3" "UBYTE_32_SASET_4" "UBYTE_32_SASET_5"
     "UBYTE_32_SASET_6" "UBYTE_32_SASET_7" "UBYTE_8_ISAREF_0"
     "UBYTE_8_ISAREF_1" "UBYTE_8_ISAREF_2" "UBYTE_8_ISAREF_3"
     "UBYTE_8_ISAREF_4" "UBYTE_8_ISAREF_5" "UBYTE_8_ISAREF_6"
     "UBYTE_8_ISAREF_7" "UBYTE_8_ISASET_0" "UBYTE_8_ISASET_1"
     "UBYTE_8_ISASET_2" "UBYTE_8_ISASET_3" "UBYTE_8_ISASET_4"
     "UBYTE_8_ISASET_5" "UBYTE_8_ISASET_6" "UBYTE_8_ISASET_7"
     "UBYTE_8_R_M_S_AREF" "UBYTE_8_SAREF_0" "UBYTE_8_SAREF_1"
     "UBYTE_8_SAREF_2" "UBYTE_8_SAREF_3" "UBYTE_8_SAREF_4" "UBYTE_8_SAREF_5"
     "UBYTE_8_SAREF_6" "UBYTE_8_SAREF_7" "UBYTE_8_SARRAY_TO_UCHAR_PTR"
     "UBYTE_8_SASET_0" "UBYTE_8_SASET_1" "UBYTE_8_SASET_2" "UBYTE_8_SASET_3"
     "UBYTE_8_SASET_4" "UBYTE_8_SASET_5" "UBYTE_8_SASET_6" "UBYTE_8_SASET_7"
     "UCONFIG_DOT_H" "UC_DELIVERY" "UC_ENSURE__BIGNUMS" "UC_ENSURE__GC"
     "UC_ENSURE__PACKAGES" "UC_ENSURE__READER"
     "UC_ENSURE__STANDARD_ERROR_HANDLING" "UC_ENSURE__STANDARD_SYMBOLS"
     "UC_ENSURE__STRUCTURES" "UINTEGER" "UNARY_DOUBLE_FLOAT_INT"
     "UNARY_DOUBLE_FLOAT_OP" "UNARY_DOUBLE_FLOAT_PRED" "UNBOUND"
     "UNBOUND_MARKER" "UNBOX_BOOLEAN" "UNBOX_CHAR" "UNBOX_DOUBLE" "UNBOX_INT"
     "UNDERFLOW" "UNPROTECT_LOCALS" "UNSAFE_CONS" "UNSIGNED_CHAR_TO_INTEGER"
     "UNSIGNED_FIXNUM_OVERFLOW_P" "UNSIGNED_LONG_TO_INTEGER"
     "UNSIGNED_SHORT_TO_INTEGER" "UNWIND_PROTECT" "UPPER_CASE_P" "VALUES_0"
     "VALUES_1" "VALUES_10" "VALUES_11" "VALUES_12" "VALUES_13" "VALUES_14"
     "VALUES_15" "VALUES_2" "VALUES_3" "VALUES_4" "VALUES_5" "VALUES_6"
     "VALUES_7" "VALUES_8" "VALUES_9" "VARIADIC_FLAG" "VECTORP"
     "VOID_TO_NULL" "WHITESPACE_CHAR_P" "WINDOWP" "XBIGNUM_TYPE"
     "XDeclare_area" "XDeclare_frontier" "XDeclare_varargs" "XKEYWORD_ARG"
     "XOPTIONAL_ARG" "XREQUIRED_ARG" "XREST_ARG" "ZERO" "_" "_ABS" "_B" "_C"
     "_IOEOF" "_IOERR" "_IOFBF" "_IOLBF" "_IOMYBUF" "_IONBF" "_IOREAD"
     "_IORW" "_IOSTRG" "_IOWRT" "_JBLEN" "_L" "_N" "_P" "_POLY1" "_POLY2"
     "_POLY3" "_POLY4" "_POLY5" "_POLY6" "_POLY7" "_POLY8" "_POLY9" "_REDUCE"
     "_S" "_SBFSIZ" "_U" "_VARARGS_H" "_VA_LIST" "_VA_LIST_" "_VA_LIST_T_H"
     "_X" "__GNUC_VA_LIST" "__math_h" "__need___va_list" "__setjmp_h"
     "__sparc_setjmp_h" "__va_rounded_size" "_floatingpoint_h"
     "_sys_ieeefp_h" #+translator-supports-clos "add_direct_subclass"
     #+translator-supports-clos "add_method"
     "adjoin" "adjust_array" "assoc" "assoc_if" "assoc_if_not" "bit" "bit0"
     "bit1" "bit2" "bit3" "bit4" "bit5" "bit6" "bit7" "bitr" "cerror"
     #+translator-supports-clos "change_class"
     #+translator-supports-clos "class_default_initargs"
     #+translator-supports-clos "class_default_superclasses"
     #+translator-supports-clos "class_direct_default_initargs"
     #+translator-supports-clos "class_direct_slots"
     #+translator-supports-clos "class_direct_subclasses"
     #+translator-supports-clos "class_direct_superclasses"
     #+translator-supports-clos "class_finalized_p"
     #+translator-supports-clos "class_fully_defined_p"
     #+translator-supports-clos "class_name"
     #+translator-supports-clos "class_precedence_list"
     #+translator-supports-clos "class_prototype"
     #+translator-supports-clos "class_slots"
     #+translator-supports-clos "class_status_bits"
     "clearerr" "complex"
     #+translator-supports-clos "compute_applicable_methods"
     #+translator-supports-clos "compute_class_default_initargs"
     #+translator-supports-clos "compute_class_precedence_list"
     #+translator-supports-clos "compute_class_prototype"
     #+translator-supports-clos "compute_effective_method"
     #+translator-supports-clos "compute_effective_slot_definition"
     #+translator-supports-clos "compute_effective_slot_definition_initargs"
     #+translator-supports-clos "compute_slot_definition_location"
     #+translator-supports-clos "compute_slot_definition_locations"
     #+translator-supports-clos "compute_slots"
     #+translator-supports-clos "compute_valid_change_class_initargs"
     #+translator-supports-clos "compute_valid_creation_initargs"
     #+translator-supports-clos "compute_valid_reinitialization_initargs"
     "count" "count_if" "count_if_not"
     #+translator-supports-clos "default_initargs"
     "delete_duplicates" "delete_if" "delete_if_not"
     #+translator-supports-clos "direct_slot_definition_class"
     #+translator-supports-clos "effective_slot_definition_class"
     #+translator-supports-clos "elide_access_method_p"
     "error" "errorn" "feof" "ferror" "fileno" "fill"
     #+translator-supports-clos "finalize_inheritance"
     "find" "find_if" "find_if_not" #+translator-supports-clos "find_method"
     #+translator-supports-clos "function_keywords"
     #+translator-supports-clos "generic_function_argument_precedence_order"
     #+translator-supports-clos "generic_function_declarations"
     #+translator-supports-clos "generic_function_initial_methods"
     #+translator-supports-clos "generic_function_lambda_list"
     #+translator-supports-clos "generic_function_method_class"
     #+translator-supports-clos "generic_function_method_combination"
     #+translator-supports-clos "generic_function_methods"
     #+translator-supports-clos "generic_function_name"
     "getc" "getchar" "initialize_do_external_symbols_iterator"
     "internal_funcall" "intersection" "isalnum" "isalpha" "isascii"
     "iscntrl" "isdigit" "isgraph" "islower" "isprint" "ispunct" "isspace"
     "isupper" "isxdigit" "lclose" "ldelete" "lisp_complex" "lisp_delete"
     "lisp_listen" "lisp_remove" "listen" "load_run"
     #+translator-supports-clos "local_slot_definition_p"
     "lopen" "lremove" "lunion" "lwrite" "make_array" "make_hash_table"
     #+translator-supports-clos "make_instances_obsolete"
     "make_list" "make_package" "make_pathname" "make_sequence" "make_string"
     "member" "member_if" "member_if_not" "merge"
     #+translator-supports-clos "metaobject_documentation"
     #+translator-supports-clos "metaobject_name"
     #+translator-supports-clos "method_function"
     #+translator-supports-clos "method_generic_function"
     #+translator-supports-clos "method_lambda_list"
     #+translator-supports-clos "method_qualifiers"
     #+translator-supports-clos "method_slot_name"
     #+translator-supports-clos "method_specializers"
     "mismatch" "nintersection" "nset_difference" "nset_exclusive_or"
     "nstring_capitalize" "nstring_downcase" "nstring_upcase" "nsublis"
     "nsubst" "nsubst_if" "nsubst_if_not" "nsubstitute" "nsubstitute_if"
     "nsubstitute_if_not" "nunion"
     #+translator-supports-clos "optimize_slot_access"
     #+translator-supports-clos "optimize_slot_accesses"
     "parse_integer" "parse_namestring"
     #+translator-supports-clos "permit_metaobject_reinitialization"
     "position" "position_if" "position_if_not"
     #+translator-supports-clos "print_object"
     "putc" "putchar" "rassoc" "rassoc_if" "rassoc_if_not" "read_from_string"
     "reduce" #+translator-supports-clos "remove_direct_subclass"
     "remove_duplicates" "remove_if" "remove_if_not"
     #+translator-supports-clos "remove_method"
     "replace" "result" "sbit" "sbitr" "search" "set_bit0" "set_bit1"
     "set_bit2" "set_bit3" "set_bit4" "set_bit5" "set_bit6" "set_bit7"
     "set_bitr" #+translator-supports-clos "set_class_direct_subclasses"
     #+translator-supports-clos "set_class_finalized_p"
     #+translator-supports-clos "set_class_fully_defined_p"
     "set_difference" "set_exclusive_or"
     #+translator-supports-clos "set_generic_function_initial_methods"
     #+translator-supports-clos "set_generic_function_methods"
     #+translator-supports-clos "set_method_generic_function"
     "set_sbitr" #+translator-supports-clos "shared_slot_definition_p"
     #+translator-supports-clos "slot_boundp_using_class"
     #+translator-supports-clos "slot_definition_allocation"
     #+translator-supports-clos "slot_definition_initargs"
     #+translator-supports-clos "slot_definition_initform"
     #+translator-supports-clos "slot_definition_initfunction"
     #+translator-supports-clos "slot_definition_location"
     #+translator-supports-clos "slot_definition_name"
     #+translator-supports-clos "slot_definition_readers"
     #+translator-supports-clos "slot_definition_type"
     #+translator-supports-clos "slot_definition_writers"
     #+translator-supports-clos "slot_makunbound_using_class"
     #+translator-supports-clos "slot_missing"
     #+translator-supports-clos "slot_unbound"
     #+translator-supports-clos "slot_value_using_class"
     "sort" "stable_sort" "stderr" "stdin" "stdout" "string_capitalize"
     "string_downcase" "string_eq" "string_equal" "string_ge"
     "string_greaterp" "string_gt" "string_le" "string_lessp" "string_lt"
     "string_ne" "string_not_equal" "string_not_greaterp" "string_not_lessp"
     "string_upcase" "sublis" "subsetp" "subst" "subst_if" "subst_if_not"
     "substitute" "substitute_if" "substitute_if_not" "toascii" "tree_equal"
     "va_alist" "va_arg" "va_dcl" "va_end" "va_start"
     #+translator-supports-clos "valid_change_class_initargs"
     #+translator-supports-clos "valid_creation_initargs"
     #+translator-supports-clos "valid_reinitialization_initargs"
     #+translator-supports-clos "validate_superclass"
     "valuesn" "valuesr" "warn" "write_line" "write_string" "write_to_string")))

(defparameter *global-c-names-lists*
  '(("mcrt0"
     "___Argv" "_alloc_profil_buf" "countbase" "environ" "moncontrol"
     "monitor" "monstartup" "numctrs" "profiling")
    ("libc"
     "BYADDR" "NETGROUP" "_C0095A2A" "_C0095A2B" "_Q_add" "_Q_cmp" "_Q_cmpe"
     "_Q_div" "_Q_dtoq" "_Q_feq" "_Q_fge" "_Q_fgt" "_Q_fle" "_Q_flt" "_Q_fne"
     "_Q_itoq" "_Q_mul" "_Q_neg" "_Q_qtod" "_Q_qtoi" "_Q_qtos" "_Q_qtou"
     "_Q_set_exception" "_Q_sqrt" "_Q_stoq" "_Q_sub" "_Q_utoq" "___Argv"
     "__builtin_alloca" "__mallinfo" "_alloc_profil_buf" "_authenticate"
     "_base_conversion_abort" "_big_binary_to_big_decimal"
     "_big_binary_to_unpacked" "_big_decimal_to_big_binary"
     "_big_float_times_power" "_big_powers_ten" "_big_powers_two" "_bufsync"
     "_carry_in_b10000" "_carry_out_b10000" "_carry_propagate_ten"
     "_carry_propagate_two" "_checkhost" "_class_double" "_class_extended"
     "_class_quadruple" "_class_single" "_cleanup" "_code_set_info"
     "_copy_big_float_digits" "_crypt" "_ctype_" "_ctype_ul" "_des_crypt"
     "_display_unpacked" "_doprnt" "_doscan" "_dtconv" "_dtou"
     "_enable_sigfpe_master" "_exit" "_exit_handlers" "_f_morefiles"
     "_filbuf" "_findbuf" "_findiop" "_flsbuf" "_fourdigits"
     "_fourdigitsquick" "_fp_add" "_fp_compare" "_fp_current_direction"
     "_fp_current_exceptions" "_fp_current_precision" "_fp_div"
     "_fp_leftshift" "_fp_mul" "_fp_normalize" "_fp_pack" "_fp_rightshift"
     "_fp_set_exception" "_fp_sqrt" "_fp_sub" "_fp_unpack"
     "_fractionstring_to_big_decimal" "_free_big_float" "_ftou" "_fwalk"
     "_gcvt" "_getarg" "_initializestates" "_integerstring_to_big_decimal"
     "_iob" "_langinfo" "_lbound" "_leading_zeros_big_powers_ten"
     "_leading_zeros_small_powers_ten" "_leading_zeros_tiny_powers_ten"
     "_left_shift_base_ten" "_left_shift_base_two" "_locales" "_longjmp"
     "_lshift_b10000" "_max_big_powers_ten" "_max_big_powers_two"
     "_max_small_powers_ten" "_max_small_powers_two" "_max_tiny_powers_ten"
     "_max_tiny_powers_two" "_mb_cur_max" "_mbstowcs_euc" "_mbstowcs_iso"
     "_mbstowcs_xccs" "_mbtowc_euc" "_mbtowc_iso" "_mbtowc_xccs" "_mkarglst"
     "_ml_close_library" "_ml_open_library" "_mnt" "_mul_10000"
     "_mul_10000short" "_mul_65536" "_mul_65536short" "_multiply_base_ten"
     "_multiply_base_ten_by_two" "_multiply_base_ten_vector"
     "_multiply_base_two" "_multiply_base_two_vector" "_my_time" "_nlist"
     "_null_auth" "_openchild" "_pack_double" "_pack_extended"
     "_pack_quadruple" "_pack_single" "_perror" "_prod_10000_b65536"
     "_prod_65536_b10000" "_prod_b10000" "_prod_b65536" "_prodc_b10000"
     "_psignal" "_pw_stayopen" "_quorem10000" "_restorestates"
     "_right_shift_base_two" "_root" "_rpc_dtablesize" "_rpcrawcombuf"
     "_ruserpass" "_savestates" "_seterr_reply" "_setjmp" "_sigfpe_master"
     "_sigfunc" "_sigtramp" "_sigvec" "_small_powers_ten" "_small_powers_two"
     "_smbuf" "_ssig" "_start_big_powers_ten" "_start_big_powers_two"
     "_start_small_powers_ten" "_start_small_powers_two"
     "_start_tiny_powers_ten" "_start_tiny_powers_two" "_svcauth_des"
     "_svcauth_null" "_svcauth_short" "_svcauth_unix" "_tbuf"
     "_test_sigfpe_master" "_tiny_powers_ten" "_tiny_powers_two" "_ubound"
     "_umac" "_unpack_double" "_unpack_extended" "_unpack_quadruple"
     "_unpack_single" "_unpacked_to_big_float" "_unpacked_to_decimal"
     "_validuser" "_wcstombs_euc" "_wcstombs_iso" "_wcstombs_xccs"
     "_wctomb_euc" "_wctomb_iso" "_wctomb_xccs" "_wrtchk"
     "_xdr_ypbind_oldsetdom" "_xdr_yprequest" "_xdr_ypresponse" "_xflsbuf"
     "_yp_dobind" "_yp_dobind_soft" "_ypserv_timeout" "_ypsleeptime" "a64l"
     "abort" "abs" "accept" "access" "acct" "addexportent" "addmntent"
     "adjtime" "advfs" "alarm" "alphasort" "asctime" "async_daemon" "atof"
     "atoi" "atol" "audit" "audit_args" "audit_text" "auditon" "auditsvc"
     "authdes_create" "authdes_getucred" "authnone_create" "authunix_create"
     "authunix_create_default" "bcmp" "bcopy" "binary_to_decimal_fraction"
     "binary_to_decimal_integer" "bind" "bindresvport" "brk" "bsearch"
     "bzero" "calloc" "callrpc" "cfgetispeed" "cfgetospeed" "cfree"
     "cfsetispeed" "cfsetospeed" "chdir" "chmod" "chown" "chroot" "clearerr"
     "clnt_broadcast" "clnt_broadcast_exp" "clnt_create" "clnt_create_vers"
     "clnt_pcreateerror" "clnt_perrno" "clnt_perror" "clnt_spcreateerror"
     "clnt_sperrno" "clnt_sperror" "clntraw_create" "clnttcp_create"
     "clntudp_bufcreate" "clntudp_create" "clock" "close" "closedir"
     "closelog" "connect" "copysign" "countbase" "creat" "crypt" "ctermid"
     "ctime" "cuserid" "dbm_close" "dbm_close_status" "dbm_delete"
     "dbm_do_nextkey" "dbm_fetch" "dbm_firsthash" "dbm_firstkey" "dbm_flush"
     "dbm_flushdir" "dbm_flushpag" "dbm_forder" "dbm_nextkey" "dbm_open"
     "dbm_setdefwrite" "dbm_store" "decimal_round"
     "decimal_to_binary_fraction" "decimal_to_binary_integer"
     "decimal_to_double" "decimal_to_extended" "decimal_to_quadruple"
     "decimal_to_single" "decimal_to_unpacked" "des_setparity"
     "double_to_decimal" "drand48" "dtconv_str" "dup" "dup2" "dysize"
     "econvert" "ecvt" "encrypt" "endac" "endexportent" "endfsent"
     "endgraent" "endgrent" "endhostent" "endmntent" "endnetent"
     "endnetgrent" "endprotoent" "endpwaent" "endpwent" "endrpcent"
     "endservent" "endttyent" "endusershell" "erand48" "errno" "ether_aton"
     "ether_hostton" "ether_line" "ether_ntoa" "ether_ntohost" "event_class"
     "execl" "execle" "execlp" "execv" "execve" "execvp" "exit" "exportfs"
     "extended_to_decimal" "f_prealloc" "fabs" "fchdir" "fchmod" "fchown"
     "fchroot" "fclose" "fcntl" "fconvert" "fcvt" "fdopen" "feof" "ferror"
     "fflush" "ffs" "fgetc" "fgetgraent" "fgetgrent" "fgetpwaent" "fgetpwent"
     "fgets" "file_to_decimal" "fileno" "flock" "fmod" "fopen" "fork"
     "fp_accrued_exceptions" "fp_direction" "fp_precision" "fpathconf"
     "fprintf" "fpu_add3wc" "fpu_cmpli" "fpu_error_nan" "fpu_neg2wc"
     "fpu_normalize" "fpu_rightshift" "fpu_set_exception" "fpu_sub3wc"
     "fputc" "fputs" "fread" "free" "freopen" "frexp" "fscanf" "fseek"
     "fstat" "fstatfs" "fsync" "ftell" "ftime" "ftok" "ftruncate" "ftw"
     "func_to_decimal" "fwrite" "gconvert" "gcvt" "get_myaddress" "getacdir"
     "getacflg" "getacmin" "getauditflagsbin" "getauditflagschar" "getauid"
     "getc" "getchar" "getcwd" "getdents" "getdomainname" "getdtablesize"
     "getegid" "getenv" "geteuid" "getexportent" "getexportopt"
     "getfauditflags" "getfh" "getfsent" "getfsfile" "getfsspec" "getfstype"
     "getgid" "getgraent" "getgranam" "getgrent" "getgrent_withinfo"
     "getgrgid" "getgrnam" "getgroups" "gethostbyaddr" "gethostbyname"
     "gethostent" "gethostid" "gethostname" "getitimer" "getlocale_ctype"
     "getlocale_numeric" "getlocale_time" "getlogin" "getmntent" "getmsg"
     "getnetbyaddr" "getnetbyname" "getnetent" "getnetgrent" "getnetname"
     "getopt" "getpagesize" "getpass" "getpeername" "getpgrp" "getpid"
     "getplabel" "getppid" "getpriority" "getprotobyname" "getprotobynumber"
     "getprotoent" "getpw" "getpwaent" "getpwanam" "getpwent" "getpwnam"
     "getpwuid" "getrlimit" "getrpcbyname" "getrpcbynumber" "getrpcent"
     "getrpcport" "getrusage" "gets" "getservbyname" "getservbyport"
     "getservent" "getsockname" "getsockopt" "getsubopt" "gettimeofday"
     "getttyent" "getttynam" "getuid" "getusershell" "getw" "getwd" "gmtime"
     "grpauth" "gsignal" "gtty" "h_errno" "hasmntopt" "hcreate" "hdestroy"
     "host2netname" "hsearch" "htonl" "htons" "ieee_handlers" "index"
     "inet_addr" "inet_lnaof" "inet_makeaddr" "inet_netof" "inet_network"
     "inet_ntoa" "init_statics" "initgroups" "initstate" "innetgr" "insque"
     "ioctl" "isalnum" "isalpha" "isascii" "isatty" "iscntrl" "isdigit"
     "isgraph" "isinf" "islower" "isnan" "isprint" "ispunct" "issecure"
     "isspace" "isupper" "isxdigit" "jcsetpgrp" "jrand48"
     "key_decryptsession" "key_encryptsession" "key_gendes" "key_setsecret"
     "kill" "killpg" "l64a" "labelfromstring" "labeltostring" "lcong48"
     "lconv" "ldexp" "lfind" "link" "listen" "localdtconv" "localeconv"
     "localtime" "lockf" "longjmp" "lrand48" "lsearch" "lseek" "lstat"
     "madvise" "mallinfo" "malloc" "mallopt" "mblen" "mbstowcs" "mbtowc"
     "mctl" "memalign" "memccpy" "memchr" "memcmp" "memcpy" "memset"
     "mincore" "mkdir" "mkfifo" "mknod" "mkstemp" "mktemp" "mktime" "mlock"
     "mlockall" "mmap" "modf" "moncontrol" "monitor" "monstartup" "mount"
     "mprotect" "mrand48" "msgctl" "msgget" "msgrcv" "msgsnd" "msync"
     "munlock" "munlockall" "munmap" "netname2host" "netname2user" "nfssvc"
     "nice" "nl_ascxtime" "nl_cxtime" "nl_strncmp" "nlist" "nrand48" "ntohl"
     "ntohs" "numctrs" "offtime" "on_exit" "open" "opendir" "openlocale"
     "openlog" "optarg" "opterr" "optind" "optopt" "pathcanon" "pathconf"
     "pause" "pclose" "perror" "pipe" "pl" "plock" "pmap_getmaps"
     "pmap_getport" "pmap_rmtcall" "pmap_set" "pmap_unset" "poll" "popen"
     "printf" "profil" "profiling" "psignal" "ptrace" "putc" "putchar"
     "putenv" "putmsg" "putpwent" "puts" "putw" "pwdauth" "qeconvert"
     "qfconvert" "qgconvert" "qsort" "quadruple_to_decimal" "quotactl" "rand"
     "random" "rcmd" "re_comp" "re_exec" "read" "readdir" "readlink" "readv"
     "realloc" "realpath" "reboot" "recv" "recvfrom" "recvmsg" "registerrpc"
     "remexportent" "remove" "remque" "rename" "rewind" "rewinddir" "rexec"
     "rfstart" "rfstop" "rfsys" "rindex" "rmdir" "rpc_createerr" "rpcdata"
     "rresvport" "rtime" "ruserok" "sbrk" "scandir" "scanf" "seconvert"
     "seed48" "seekdir" "select" "semctl" "semget" "semop" "send" "sendmsg"
     "sendto" "setac" "setaudit" "setauid" "setbuf" "setbuffer"
     "setdomainname" "setegid" "seteuid" "setexportent" "setfsent" "setgid"
     "setgraent" "setgrent" "setgrjunk" "setgroups" "sethostent"
     "sethostname" "setitimer" "setjmp" "setlinebuf" "setlocale" "setlogmask"
     "setmntent" "setnetent" "setnetgrent" "setpgid" "setpgrp" "setpriority"
     "setprotoent" "setpwaent" "setpwent" "setpwfile" "setregid" "setreuid"
     "setrgid" "setrlimit" "setrpcent" "setruid" "setservent" "setsid"
     "setsockopt" "setspgldr" "setstate" "settimeofday" "setttyent" "setuid"
     "setupcolldef" "setuseraudit" "setusershell" "setvbuf" "sfconvert"
     "sgconvert" "shmat" "shmctl" "shmdt" "shmget" "shutdown" "sigaction"
     "sigaddset" "sigblock" "sigdelset" "sigemptyset" "sigfillset" "sigfpe"
     "siginterrupt" "sigismember" "siglongjmp" "signal" "sigpause"
     "sigpending" "sigprocmask" "sigsetjmp" "sigsetmask" "sigstack"
     "sigsuspend" "sigvec" "single_to_decimal" "sleep" "socket" "socketpair"
     "sprintf" "srand" "srand48" "srandom" "sscanf" "ssignal" "ssigp" "stat"
     "statfs" "strcasecmp" "strcat" "strchr" "strcmp" "strcoll" "strcpy"
     "strcspn" "strdup" "strftime" "stricmp" "string_to_decimal" "strlen"
     "strncasecmp" "strncat" "strncmp" "strncpy" "strnicmp" "strpbrk"
     "strptime" "strrchr" "strspn" "strstr" "strtod" "strtok" "strtol"
     "strxfrm" "stty" "svc_fdset" "svc_getreq" "svc_getreqset" "svc_register"
     "svc_run" "svc_sendreply" "svc_unregister" "svc_versquiet"
     "svcauthdes_stats" "svcerr_auth" "svcerr_decode" "svcerr_noproc"
     "svcerr_noprog" "svcerr_progvers" "svcerr_systemerr" "svcerr_weakauth"
     "svcfd_create" "svcraw_create" "svctcp_create" "svcudp_bufcreate"
     "svcudp_create" "svcudp_enablecache" "swab" "swapon" "symlink" "sync"
     "sys_errlist" "sys_nerr" "sys_siglist" "syscall" "sysconf" "syslog"
     "system" "tcdrain" "tcflow" "tcflush" "tcgetattr" "tcgetpgrp"
     "tcsendbreak" "tcsetattr" "tcsetpgrp" "tdelete" "tell" "telldir"
     "tempnam" "tfind" "time" "timegm" "timelocal" "timeoff" "times"
     "timezone" "tmpfile" "tmpnam" "toascii" "tolower" "toupper" "truncate"
     "tsearch" "ttyname" "ttyslot" "twalk" "tzset" "tzsetwall" "ualarm"
     "ulimit" "umask" "unadvfs" "uname" "ungetc" "unlink" "unmount"
     "unpackdouble" "unpacksingle" "user2netname" "usingypmap" "usleep"
     "ustat" "utime" "utimes" "v1prot_dofirst" "v1prot_donext" "vadvise"
     "valloc" "vfork" "vfprintf" "vhangup" "vlimit" "vprintf" "vsprintf"
     "vsyslog" "vtimes" "vtrace" "wait" "wait3" "wait4" "waitpid" "wcstombs"
     "wctomb" "write" "writev" "xdr_accepted_reply" "xdr_array"
     "xdr_authdes_cred" "xdr_authdes_verf" "xdr_authunix_parms" "xdr_bool"
     "xdr_bytes" "xdr_callhdr" "xdr_callmsg" "xdr_char" "xdr_cryptkeyarg"
     "xdr_cryptkeyres" "xdr_datum" "xdr_des_block" "xdr_double" "xdr_enum"
     "xdr_float" "xdr_free" "xdr_getcredres" "xdr_int" "xdr_keybuf"
     "xdr_keystatus" "xdr_long" "xdr_netnamestr" "xdr_netobj" "xdr_opaque"
     "xdr_opaque_auth" "xdr_pmap" "xdr_pmaplist" "xdr_pointer" "xdr_pwdnm"
     "xdr_reference" "xdr_rejected_reply" "xdr_replymsg" "xdr_rmtcall_args"
     "xdr_rmtcallres" "xdr_short" "xdr_string" "xdr_u_char" "xdr_u_int"
     "xdr_u_long" "xdr_u_short" "xdr_union" "xdr_unixcred" "xdr_vector"
     "xdr_void" "xdr_wrapstring" "xdr_yp_binding" "xdr_yp_buf"
     "xdr_yp_inaddr" "xdr_ypall" "xdr_ypbind_resp" "xdr_ypbind_setdom"
     "xdr_ypdelete_args" "xdr_ypdomain_wrap_string" "xdr_ypmap_parms"
     "xdr_ypmap_wrap_string" "xdr_ypmaplist" "xdr_ypmaplist_wrap_string"
     "xdr_ypowner_wrap_string" "xdr_yppushresp_xfr" "xdr_ypreq_key"
     "xdr_ypreq_nokey" "xdr_ypreq_xfr" "xdr_ypresp_key_val"
     "xdr_ypresp_maplist" "xdr_ypresp_master" "xdr_ypresp_order"
     "xdr_ypresp_val" "xdr_ypupdate_args" "xdrmem_create" "xdrrec_create"
     "xdrrec_endofrecord" "xdrrec_eof" "xdrrec_readbytes" "xdrrec_skiprecord"
     "xdrstdio_create" "xprt_register" "xprt_unregister" "yp_all" "yp_bind"
     "yp_first" "yp_get_default_domain" "yp_ismapthere" "yp_master"
     "yp_match" "yp_next" "yp_order" "yp_softbind" "yp_unbind" "yp_update"
     "yperr_string" "ypprot_err")
    ("libm"
     "Facos" "Faint" "Fanint" "Fasin" "Fatan" "Fc_add" "Fc_conv_d"
     "Fc_conv_f" "Fc_conv_i" "Fc_conv_z" "Fc_div" "Fc_eq" "Fc_minus"
     "Fc_mult" "Fc_ne" "Fc_neg" "Fcos" "Fcosh" "Fd_conv_c" "Fd_conv_z" "Fexp"
     "Fexp10" "Fexp2" "Ff_conv_c" "Ff_conv_z" "Fi_conv_c" "Fi_conv_z" "Flog"
     "Flog10" "Fnint" "Fsin" "Fsinh" "Fsqrt" "Ftan" "Ftanh" "Fz_add"
     "Fz_conv_c" "Fz_conv_d" "Fz_conv_f" "Fz_conv_i" "Fz_div" "Fz_eq"
     "Fz_minus" "Fz_mult" "Fz_ne" "Fz_neg" "SVID_libm_err" "_Fc_add"
     "_Fc_conv_d" "_Fc_conv_f" "_Fc_conv_i" "_Fc_conv_z" "_Fc_div" "_Fc_eq"
     "_Fc_minus" "_Fc_mult" "_Fc_ne" "_Fc_neg" "_Fd_conv_c" "_Fd_conv_z"
     "_Ff_conv_c" "_Ff_conv_z" "_Fi_conv_c" "_Fi_conv_z" "_Fz_add"
     "_Fz_conv_c" "_Fz_conv_d" "_Fz_conv_f" "_Fz_conv_i" "_Fz_div"
     "_Fz_minus" "_Fz_mult" "_Fz_neg" "__infinity"
     "_fp_convert_double_to_int" "_is_nonstandard" "_swapEX" "_swapRD"
     "_swapRP" "_swapTE" "_tbl_atan_hi" "_tbl_atan_lo" "_tbl_log_hi"
     "_tbl_log_lo" "_tbl_r_atan_hi" "_tbl_r_atan_lo" "_tbl_r_log_hi"
     "_tbl_r_log_lo" "abrupt_underflow_" "acos" "acosh" "acospi" "aint"
     "anint" "annuity" "asin" "asinh" "asinpi" "atan" "atan2" "atan2pi"
     "atanh" "atanpi" "c_abs" "c_cmplx" "c_conv_i" "c_cos" "c_div" "c_exp"
     "c_log" "c_sin" "c_sqrt" "cabs" "cbrt" "ceil" "compound" "copysign"
     "cos" "cosh" "cospi" "d_abs" "d_acos" "d_acos_" "d_acosd" "d_acosh_"
     "d_acospi_" "d_aint_" "d_anint_" "d_annuity_" "d_asin" "d_asin_"
     "d_asind" "d_asinh_" "d_asinpi_" "d_atan" "d_atan2_" "d_atan2pi_"
     "d_atan_" "d_atand" "d_atanh_" "d_atanpi_" "d_atn2" "d_atn2d" "d_cbrt_"
     "d_ceil_" "d_cmplx" "d_cnjg" "d_compound_" "d_copysign_" "d_cos"
     "d_cos_" "d_cosd" "d_cosh" "d_cosh_" "d_cospi_" "d_dim" "d_erf_"
     "d_erfc_" "d_exp" "d_exp10_" "d_exp2_" "d_exp_" "d_expm1_" "d_fabs_"
     "d_floor_" "d_fmod_" "d_hypot_" "d_imag" "d_infinity_" "d_int" "d_j0_"
     "d_j1_" "d_jn_" "d_lg10" "d_lgamma_" "d_log" "d_log10_" "d_log1p_"
     "d_log2_" "d_log_" "d_logb_" "d_max_normal_" "d_max_subnormal_"
     "d_min_normal_" "d_min_subnormal_" "d_mod" "d_nextafter_" "d_nint"
     "d_pow_" "d_prod" "d_quiet_nan_" "d_remainder_" "d_rint_" "d_scalb_"
     "d_scalbn_" "d_sign" "d_signaling_nan_" "d_significand_" "d_sin"
     "d_sin_" "d_sincos_" "d_sincospi_" "d_sind" "d_sinh" "d_sinh_"
     "d_sinpi_" "d_sqrt" "d_sqrt_" "d_tan" "d_tan_" "d_tand" "d_tanh"
     "d_tanh_" "d_tanpi_" "d_y0_" "d_y1_" "d_yn_" "drand_" "drem" "dtime_"
     "erf" "erfc" "etime_" "exp" "exp10" "exp2" "expm1" "fabs" "finite"
     "floor" "fmod" "fp_class" "fp_pi" "frexp" "gamma" "gradual_underflow_"
     "h_dnnt" "h_nint" "hypot" "i_conv_c" "i_dnnt" "i_nint" "id_finite_"
     "id_fp_class_" "id_ilogb_" "id_irint_" "id_isinf_" "id_isnan_"
     "id_isnormal_" "id_issubnormal_" "id_iszero_" "id_nint_" "id_signbit_"
     "ieee_flags" "ieee_flags_" "ieee_handler" "ieee_handler_"
     "ieee_retrospective" "ieee_retrospective_" "ilogb" "infinity"
     "ir_finite_" "ir_fp_class_" "ir_ilogb_" "ir_irint_" "ir_isinf_"
     "ir_isnan_" "ir_isnormal_" "ir_issubnormal_" "ir_iszero_" "ir_nint_"
     "ir_signbit_" "irand_" "irint" "isinf" "isnan" "isnormal" "issubnormal"
     "iszero" "j0" "j1" "jn" "last_stime" "last_utime" "ldexp" "lgamma" "log"
     "log10" "log1p" "log2" "logb" "matherr" "max_normal" "max_subnormal"
     "min_normal" "min_subnormal" "modf" "nextafter" "nint"
     "nonstandard_arithmetic" "nonstandard_arithmetic_" "pow" "pow_cc"
     "pow_ci" "pow_dd" "pow_di" "pow_ri" "pow_rr" "pow_zi" "pow_zz"
     "quiet_nan" "r_abs" "r_acos" "r_acos_" "r_acosd" "r_acosh_" "r_acospi_"
     "r_aint_" "r_anint_" "r_annuity_" "r_asin" "r_asin_" "r_asind"
     "r_asinh_" "r_asinpi_" "r_atan" "r_atan2_" "r_atan2pi_" "r_atan_"
     "r_atand" "r_atanh_" "r_atanpi_" "r_atn2" "r_atn2d" "r_cbrt_" "r_ceil_"
     "r_cnjg" "r_compound_" "r_copysign_" "r_cos" "r_cos_" "r_cosd" "r_cosh"
     "r_cosh_" "r_cospi_" "r_dim" "r_erf_" "r_erfc_" "r_exp" "r_exp10_"
     "r_exp2_" "r_exp_" "r_expm1_" "r_fabs_" "r_floor_" "r_fmod_" "r_hypot_"
     "r_imag" "r_infinity_" "r_int" "r_j0_" "r_j1_" "r_jn_" "r_lg10"
     "r_lgamma_" "r_log" "r_log10_" "r_log1p_" "r_log2_" "r_log_" "r_logb_"
     "r_max_normal_" "r_max_subnormal_" "r_min_normal_" "r_min_subnormal_"
     "r_mod" "r_nextafter_" "r_nint" "r_pow_" "r_quiet_nan_" "r_remainder_"
     "r_rint_" "r_scalb_" "r_scalbn_" "r_sign" "r_signaling_nan_"
     "r_significand_" "r_sin" "r_sin_" "r_sincos_" "r_sincospi_" "r_sind"
     "r_sinh" "r_sinh_" "r_sinpi_" "r_sqrt" "r_sqrt_" "r_tan" "r_tan_"
     "r_tand" "r_tanh" "r_tanh_" "r_tanpi_" "r_y0_" "r_y1_" "r_yn_" "rand_"
     "release_dummy" "remainder" "rint" "scalb" "scalbn" "sigfpe_"
     "signaling_nan" "signbit" "signgam" "significand" "sin" "sincos"
     "sincospi" "sinh" "sinpi" "sqrt" "standard_arithmetic"
     "standard_arithmetic_" "state" "tan" "tanh" "tanpi" "tstz_d" "tstz_f"
     "tstz_i" "tstz_s" "y0" "y1" "yn" "z_abs" "z_cos" "z_exp" "z_log" "z_sin"
     "z_sqrt")
    ("runtime"
     "ADD_IMPORT" "ADD_PACKAGE_NICKNAME" "ADD_PACKAGE_USE" "ADD_SHADOW"
     #+translator-supports-clos "ASSIGN_SLOT_INDEX"
     "Apply_hook" "Area_overflow_function" "Array_dimension_limit"
     "Array_rank_limit" "Array_total_size_limit" "Boole_1" "Boole_2"
     "Boole_and" "Boole_andc1" "Boole_andc2" "Boole_c1" "Boole_c2"
     "Boole_clr" "Boole_eqv" "Boole_ior" "Boole_nand" "Boole_nor"
     "Boole_orc1" "Boole_orc2" "Boole_set" "Boole_xor" "Break_function"
     "Break_on_signals" #+translator-supports-clos "COPY_METHOD_FRAME"
     "Call_arguments_limit" "Compile_file_pathname" "Compile_file_truename"
     "Compile_print" "Compile_verbose" "Current_area" "Debug_io"
     "Debugger_hook" "Default_ext" "Default_pathname_defaults"
     "Double_float_epsilon" "Double_float_negative_epsilon" "Dynamic_area"
     "Dynamic_area_copy" "Emergency_threshold" "Error_output" "Eval_hook"
     "Features" "Gc_inhibit" "Gc_silence"
     #+translator-supports-clos "Generic_function_for_method_combination_errors"
     "Gensym_counter" "Initial_symbol_names" "Initialization"
     "Internal_time_units_per_second" "Kabort" "Kaccessor" "Kaddress"
     "Kadjustable" "Kafter" "Kalignment" "Kallocation" "Kallow_other_keys"
     "Kappend" "Kargument_precedence_order" "Karguments" "Karound" "Karray"
     "Kback" "Kbase" "Kbefore" "Kcapitalize" "Kcase" "Kcharacter" "Kchestnut"
     "Kcircle" "Kclass" "Kcltl2" "Kcolumn_major" "Kcommon" "Kcommon_lisp"
     "Kconc_name" "Kconstant" "Kconstructor" "Kcopier" "Kcount" "Kcreate"
     "Kdatum" "Kdeclare" "Kdefault" "Kdefault_initargs" "Kdefaults"
     "Kdescription" "Kdevice"
     #+translator-supports-clos "Kdirect_default_initargs"
     #+translator-supports-clos "Kdirect_slots"
     #+translator-supports-clos "Kdirect_superclasses"
     "Kdirection" "Kdirectory" "Kdisplaced_index_offset" "Kdisplaced_to"
     "Kdocumentation" "Kdouble_float" "Kdowncase" "Kdynamic" "Kelement_type"
     "Kend" "Kend1" "Kend2" "Kenvironment" "Kerror" "Kescape"
     "Kexpected_type" "Kexport" "Kexternal" "Kexternal_format"
     "Kfill_pointer" "Kformat_arguments" "Kformat_string" "Kfrom_end"
     "Kfunction" "Kgeneric_function" "Kgeneric_function_class" "Kgensym"
     "Khost" "Kidentity_with_one_argument" "Kieee_floating_point"
     "Kif_does_not_exist" "Kif_exists" "Kimport_from" "Kinclude" "Kindex"
     "Kinherited" "Kinitarg" #+translator-supports-clos "Kinitargs"
     "Kinitform" #+translator-supports-clos "Kinitfunction"
     "Kinitial_contents" "Kinitial_element"
     #+translator-supports-clos "Kinitial_methods"
     "Kinitial_offset" "Kinitial_value" "Kinput" "Kinstalled" "Kinstance"
     "Kinteraction_function" "Kinteractive" "Kintern" "Kinternal" "Kinvert"
     "Kio" "Kjunk_allowed" "Kkey"
     #+translator-supports-clos "Kkeyword_parameter_map"
     "Klambda_list" "Klength" "Klevel" "Klexical" "Klines" "Klocal" "Kmacro"
     #+translator-supports-thread "Klock"
     "Kmalloc" "Kmetaclass" "Kmethod" "Kmethod_class" "Kmethod_combination"
     #+translator-supports-clos "Kmethod_combination_options"
     #+translator-supports-clos "Kmethod_combination_type"
     "Kmiser_width" "Kmost_specific_first" "Kmost_specific_last" "Kname"
     "Knamed" "Knew_version" "Knewest" "Knicknames" "Koldest" "Koperands"
     "Koperation" "Koperator" "Korder" "Koutput" "Koverwrite" "Kpackage"
     "Kpathname" "Kpointer" "Kpprint_dispatch" "Kpredicate" "Kpreserve"
     "Kpreserve_whitespace" "Kpretty" "Kprevious" "Kprint" "Kprint_function"
     "Kprobe" #+translator-supports-clos "Kqualifiers"
     "Kradix" #+translator-supports-clos "Kread"
     "Kread_eof" "Kread_only" "Kreadably" "Kreader"
     #+translator-supports-clos "Kreaders"
     "Krehash_size" "Krehash_threshold" "Krename" "Krename_and_delete"
     "Kreport" "Kreport_function" "Krequired" "Kright_margin" "Krow_major"
     "Kshadow" "Kshadowing_import_from" "Ksigned_16bit" "Ksigned_32bit"
     "Ksigned_8bit" "Ksingle_float" "Ksize"
     #+translator-supports-clos "Kslot_name"
     "Kspecial" "Kspecial_form" #+translator-supports-clos "Kspecializers"
     "Kstart" "Kstart1" "Kstart2" "Kstatic" "Kstream" "Ksupersede"
     "Ksymbol_macro" "Ktest" "Ktest_function" "Ktest_not" "Ktype"
     "Kunsigned_16bit" "Kunsigned_32bit" "Kunsigned_8bit" "Kunspecific" "Kup"
     "Kupcase" "Kuse" "Kvariable" "Kverbose" "Kversion" "Kwild"
     "Kwild_inferiors" #+translator-supports-clos "Kwrite"
     "Kwriter" #+translator-supports-clos "Kwriters"
     "L_temp" "L_temp1" "Lambda_list_keywords" "Lambda_parameters_limit"
     "Least_negative_double_float" "Least_negative_long_float"
     "Least_negative_normalized_double_float"
     "Least_negative_normalized_long_float"
     "Least_negative_normalized_short_float"
     "Least_negative_normalized_single_float" "Least_negative_short_float"
     "Least_negative_single_float" "Least_positive_double_float"
     "Least_positive_long_float" "Least_positive_normalized_double_float"
     "Least_positive_normalized_long_float"
     "Least_positive_normalized_short_float"
     "Least_positive_normalized_single_float" "Least_positive_short_float"
     "Least_positive_single_float" "Lisp_stack" "List_of_packages"
     "Load_pathname" "Load_print" "Load_truename" "Load_verbose" "Local_area"
     "Long_float_epsilon" "Long_float_negative_epsilon"
     "Long_site_name_string" "MAKE_FUNCTION"
     #+translator-supports-clos "METHOD_ARGUMENT_LIST"
     #+translator-supports-clos "METHOD_COMBINATION_KEY_VALUE"
     "Macroexpand_hook"
     #+translator-supports-clos "Method_combination_effective_method"
     #+translator-supports-clos "Method_combination_for_method_combination_errors"
     "Modules" "Most_negative_double_float" "Most_negative_fixnum"
     "Most_negative_long_float" "Most_negative_short_float"
     "Most_negative_single_float" "Most_positive_double_float"
     "Most_positive_fixnum" "Most_positive_long_float"
     "Most_positive_short_float" "Most_positive_single_float"
     "Multiple_values_limit" "NEW_PACKAGE" "NEW_SYMBOL" "PCTpointer"
     "Package" "Pcl" "Pcl_user" "Pclos" "Pclos_run" "Pclosx" "Pi" "Pkeyword"
     "Plus" "Plus_plus" "Plus_plus_plus" "Print_array" "Print_base"
     "Print_case" "Print_circle" "Print_escape" "Print_gensym" "Print_length"
     "Print_level" "Print_lines" "Print_miser_width" "Print_pprint_dispatch"
     "Print_pretty" "Print_radix" "Print_readably" "Print_right_margin"
     "Ptrun" "Ptx" "Qabort" "Qabs" "Qacons" "Qacos" "Qacosh" "Qadd1"
     #+translator-supports-clos "Qadd_direct_subclass"
     "Qadd_method" #+translator-supports-clos "Qadd_named_class"
     #+translator-supports-clos "Qadd_named_generic_function"
     #+translator-supports-clos "Qadd_named_method"
     "Qadjoin" "Qadjust_array" "Qadjustable_array_p"
     "Qadvance_do_symbols_iterator" "Qadvance_with_package_iterator"
     "Qallocate_instance" "Qallocate_memory_to_target" "Qallow_gc"
     "Qalpha_char_p" "Qalphanumericp" "Qand" "Qand_allow_other_keys"
     "Qand_aux" "Qand_body" "Qand_environment" "Qand_key" "Qand_optional"
     "Qand_rest" "Qand_whole" "Qappend" "Qapply" "Qapropos" "Qapropos_list"
     "Qarea_memory_limit" "Qarea_memory_used" "Qarea_target_size" "Qaref"
     "Qarithmetic_error" "Qarithmetic_error_operands"
     "Qarithmetic_error_operation" "Qarray" "Qarray_dimension"
     "Qarray_dimension_limit" "Qarray_dimensions" "Qarray_displacement"
     "Qarray_element_type" "Qarray_foreign_type" "Qarray_has_fill_pointer_p"
     "Qarray_in_bounds_p" "Qarray_rank" "Qarray_rank_limit"
     "Qarray_row_major_index" "Qarray_total_size" "Qarray_total_size_limit"
     "Qarrayp" "Qash" "Qasin" "Qasinh" "Qassert" "Qassoc" "Qassoc_if"
     "Qassoc_if_not" "Qassq" "Qatan" "Qatanh" "Qatom" "Qaugment_environment"
     "Qbackquote" "Qbase_char" "Qbase_string" "Qbegin_hash_table_iterator"
     "Qbegin_print_unreadable_object" "Qbegin_time" "Qbignum" "Qbignump"
     "Qbit" "Qbit_and" "Qbit_andc1" "Qbit_andc2" "Qbit_eqv" "Qbit_ior"
     "Qbit_nand" "Qbit_nor" "Qbit_not" "Qbit_orc1" "Qbit_orc2" "Qbit_vector"
     "Qbit_vector_p" "Qbit_xor" "Qbitp" "Qblock" "Qboole" "Qboole_1"
     "Qboole_2" "Qboole_and" "Qboole_andc1" "Qboole_andc2" "Qboole_c1"
     "Qboole_c2" "Qboole_clr" "Qboole_eqv" "Qboole_ior" "Qboole_nand"
     "Qboole_nor" "Qboole_orc1" "Qboole_orc2" "Qboole_set" "Qboole_xor"
     "Qboth_case_p" "Qboundp" "Qbreak" "Qbreak_function" "Qbreak_on_signals"
     "Qbroadcast_stream" "Qbroadcast_stream_p" "Qbroadcast_stream_streams"
     "Qbuilt_in_class" "Qbutlast" "Qbyte" "Qbyte_position" "Qbyte_size"
     "Qc_lines" "Qcaaaar" "Qcaaadr" "Qcaaar" "Qcaadar" "Qcaaddr" "Qcaadr"
     "Qcaar" "Qcadaar" "Qcadadr" "Qcadar" "Qcaddar" "Qcadddr" "Qcaddr"
     "Qcadr" "Qcall_arguments_limit"
     #+translator-supports-clos "Qcall_combined_method"
     "Qcall_method" "Qcall_next_method" "Qcar" "Qcase" "Qcatch" "Qccase"
     "Qcdaaar" "Qcdaadr" "Qcdaar" "Qcdadar" "Qcdaddr" "Qcdadr" "Qcdar"
     "Qcddaar" "Qcddadr" "Qcddar" "Qcdddar" "Qcddddr" "Qcdddr" "Qcddr" "Qcdr"
     "Qceiling" "Qcell_error" "Qcell_error_name" "Qcerror" "Qchange_class"
     "Qchar" "Qchar_code" "Qchar_code_limit" "Qchar_downcase" "Qchar_eq"
     "Qchar_equal" "Qchar_ge" "Qchar_greaterp" "Qchar_gt" "Qchar_int"
     "Qchar_le" "Qchar_lessp" "Qchar_lt" "Qchar_name" "Qchar_ne"
     "Qchar_not_equal" "Qchar_not_greaterp" "Qchar_not_lessp" "Qchar_upcase"
     "Qcharacter" "Qcharacterp" "Qcheck_type" "Qcis" "Qclass"
     #+translator-supports-clos "Qclass_default_initargs"
     #+translator-supports-clos "Qclass_default_superclasses"
     #+translator-supports-clos "Qclass_direct_default_initargs"
     #+translator-supports-clos "Qclass_direct_slots"
     #+translator-supports-clos "Qclass_direct_subclasses"
     #+translator-supports-clos "Qclass_direct_superclasses"
     #+translator-supports-clos "Qclass_finalized_p"
     #+translator-supports-clos "Qclass_fully_defined_p"
     "Qclass_name" "Qclass_of"
     #+translator-supports-clos "Qclass_precedence_list"
     #+translator-supports-clos "Qclass_prototype"
     #+translator-supports-clos "Qclass_slots"
     #+translator-supports-clos "Qclass_status_bits"
     #+translator-supports-clos "Qclass_wrapper"
     #+translator-supports-clos "Qclass_wrapper_p"
     "Qcleanup_hash_table_iterator" "Qclear_input" "Qclear_output" "Qclose"
     "Qclosed_variable" "Qclrhash" "Qcobject" "Qcobjectp" "Qcode_char"
     "Qcoerce" #+translator-supports-clos "Qcombine_methods"
     "Qcomma" "Qcomma_atsign" "Qcomma_dot" "Qcompilation_speed" "Qcompile"
     "Qcompile_file" "Qcompile_file_pathname" "Qcompile_file_truename"
     "Qcompile_print" "Qcompile_verbose" "Qcompiled_function"
     "Qcompiled_function_p" "Qcompiler_macro" "Qcompiler_macro_function"
     "Qcomplement" "Qcomplex" "Qcomplexp" "Qcompute_applicable_methods"
     #+translator-supports-clos "Qcompute_class_default_initargs"
     #+translator-supports-clos "Qcompute_class_precedence_list"
     #+translator-supports-clos "Qcompute_class_prototype"
     #+translator-supports-clos "Qcompute_effective_method"
     #+translator-supports-clos "Qcompute_effective_slot_definition"
     #+translator-supports-clos "Qcompute_effective_slot_definition_initargs"
     #+translator-supports-clos "Qcompute_method_combination"
     "Qcompute_restarts"
     #+translator-supports-clos "Qcompute_slot_definition_location"
     #+translator-supports-clos "Qcompute_slot_definition_locations"
     #+translator-supports-clos "Qcompute_slots"
     #+translator-supports-clos "Qcompute_valid_change_class_initargs"
     #+translator-supports-clos "Qcompute_valid_creation_initargs"
     #+translator-supports-clos "Qcompute_valid_reinitialization_initargs"
     "Qconcatenate" "Qconcatenated_stream" "Qconcatenated_stream_p"
     "Qconcatenated_stream_streams" "Qcond" "Qcondition" "Qconjugate" "Qcons"
     "Qconsp" #+translator-supports-clos "Qconstant_initform_p"
     "Qconstant_initfunction" "Qconstant_value" "Qconstantly"
     "Qconstantly_false" "Qconstantly_nil_initfunction"
     "Qconstantly_t_initfunction" "Qconstantly_true"
     #+translator-supports-clos "Qconstantly_zero_initfunction"
     "Qconstantp" "Qcontinue" "Qcontrol_error" "Qcopy_alist"
     "Qcopy_foreign_pointer" "Qcopy_list" "Qcopy_pprint_dispatch"
     "Qcopy_readtable" "Qcopy_seq" "Qcopy_structure" "Qcopy_symbol"
     "Qcopy_tree" "Qcos" "Qcosh" "Qcount" "Qcount_if" "Qcount_if_not"
     "Qcpp_conditional" "Qctypecase" "Qdebug" "Qdebug_io" "Qdebugger_hook"
     "Qdecf" "Qdeclaim" "Qdeclaration" "Qdeclaration_information" "Qdeclare"
     "Qdecode_float" "Qdecode_universal_time" "Qdef_foreign_callable"
     "Qdef_foreign_function" "Qdef_foreign_struct"
     "Qdef_foreign_synonym_type"
     #+translator-supports-clos "Qdefault_initargs"
     "Qdefault_pathname_defaults" "Qdefclass" "Qdefconstant" "Qdefgeneric"
     "Qdefine_compiler_macro" "Qdefine_condition" "Qdefine_declaration"
     "Qdefine_foreign_synonym_type" "Qdefine_method_combination"
     #+translator-supports-clos "Qdefine_method_combination_function"
     "Qdefine_modify_macro" "Qdefine_setf_expander" "Qdefine_setf_method"
     "Qdefined_foreign_type_p" "Qdefmacro" "Qdefmethod" "Qdefpackage"
     "Qdefpackage_export" "Qdefpackage_import_from" "Qdefpackage_intern"
     "Qdefpackage_shadow" "Qdefpackage_shadowing_import_from"
     "Qdefpackage_use_package" "Qdefparameter" "Qdefsetf" "Qdefstruct"
     "Qdeftype" "Qdefun" "Qdefvar" "Qdelete" "Qdelete_duplicates"
     "Qdelete_file" "Qdelete_if" "Qdelete_if_not" "Qdelete_package" "Qdelq"
     "Qdenominator" "Qdeposit_field" "Qdescribe" "Qdescribe_object"
     "Qdestructuring_bind" "Qdigit_char" "Qdigit_char_p"
     #+translator-supports-clos "Qdirect_slot_definition"
     #+translator-supports-clos "Qdirect_slot_definition_class"
     "Qdirectory" "Qdirectory_namestring" "Qdisassemble"
     #+translator-supports-clos "Qdisplay_cache_statistics"
     "Qdivision_by_zero" "Qdo" "Qdo_all_symbols" "Qdo_external_symbols"
     "Qdo_remf" "Qdo_star" "Qdo_symbols" "Qdocumentation" "Qdolist"
     "Qdotimes" "Qdouble_float" "Qdouble_float_epsilon"
     "Qdouble_float_negative_epsilon" "Qdpb" "Qdribble" "Qdynamic_extent"
     "Qecase" "Qecho_stream" "Qecho_stream_input_stream"
     "Qecho_stream_output_stream" "Qecho_stream_p" "Qed"
     #+translator-supports-clos "Qeffective_method"
     #+translator-supports-clos "Qeffective_method_p"
     #+translator-supports-clos "Qeffective_slot_definition"
     #+translator-supports-clos "Qeffective_slot_definition_class"
     "Qeighth" #+translator-supports-clos "Qelide_access_method_p"
     "Qelt" "Qenclose" "Qencode_universal_time"
     #+translator-supports-clos "Qencoded_lambda_list"
     "Qend_hash_table_iterator" "Qend_of_file" "Qendp" "Qenough_namestring"
     #+translator-supports-clos "Qensure_class"
     "Qensure_generic_function" "Qeq" "Qeql" "Qequal" "Qequalp" "Qerror"
     "Qerror_output" "Qestablish_special_variable" "Qetypecase" "Qeval"
     "Qeval_run" "Qeval_when" "Qevenp" "Qevery" "Qexp" "Qexport" "Qexpt"
     "Qextend_string_output_stream" "Qextended_char" "Qfboundp" "Qfceiling"
     "Qfdefinition" "Qfeatures" "Qffloor" "Qfifth" "Qfile_author"
     "Qfile_error" "Qfile_error_pathname" "Qfile_length" "Qfile_namestring"
     "Qfile_position" "Qfile_stream" "Qfile_stream_p" "Qfile_string_length"
     "Qfile_write_date" "Qfill" "Qfill_pointer"
     #+translator-supports-clos "Qfinalize_inheritance"
     "Qfind" "Qfind_all_symbols" "Qfind_class"
     #+translator-supports-clos "Qfind_effective_slot_definition"
     "Qfind_if" "Qfind_if_not"
     #+translator-supports-clos "Qfind_instance_keyword"
     "Qfind_method" "Qfind_package" "Qfind_restart"
     #+translator-supports-clos "Qfind_standard_method_class"
     #+translator-supports-clos "Qfind_standard_method_combination"
     "Qfind_symbol" "Qfinish_output" "Qfinish_print_unreadable_object"
     "Qfinish_time" "Qfirst" "Qfixnum" "Qfixnump" "Qflatsize" "Qflet"
     "Qfloat" "Qfloat_digits" "Qfloat_precision" "Qfloat_radix" "Qfloat_sign"
     "Qfloating_point_inexact" "Qfloating_point_invalid_operation"
     "Qfloating_point_overflow" "Qfloating_point_underflow" "Qfloatp"
     "Qfloor" "Qfmakunbound" "Qforce_gc" "Qforce_output" "Qforeign_aref"
     "Qforeign_pointer" "Qforeign_pointer_address" "Qforeign_pointer_p"
     "Qforeign_pointer_type" "Qforeign_pointer_type_p"
     "Qforeign_string_value" "Qforeign_type" "Qforeign_type_modulus"
     "Qforeign_type_name" "Qforeign_type_p" "Qforeign_type_remainder"
     "Qforeign_type_size" "Qforeign_typep" "Qforeign_value" "Qformat"
     "Qformatter" #+translator-supports-clos "Qforward_referenced_class"
     "Qfourth" "Qfree_foreign_pointer" "Qfresh_line" "Qfround" "Qftruncate"
     "Qftype" "Qfuncall"
     #+translator-supports-clos "Qfuncallable_standard_class"
     "Qfunction" "Qfunction_information" "Qfunction_keywords"
     "Qfunction_lambda_expression" "Qfunctionp" "Qgc_inhibit" "Qgc_silence"
     "Qgcd" "Qgeneric_function"
     #+translator-supports-clos "Qgeneric_function_argument_precedence_order"
     #+translator-supports-clos "Qgeneric_function_declarations"
     #+translator-supports-clos "Qgeneric_function_for_method_combination_errors"
     #+translator-supports-clos "Qgeneric_function_initial_methods"
     #+translator-supports-clos "Qgeneric_function_lambda_list"
     #+translator-supports-clos "Qgeneric_function_method_class"
     #+translator-supports-clos "Qgeneric_function_method_combination"
     #+translator-supports-clos "Qgeneric_function_methods"
     #+translator-supports-clos "Qgeneric_function_name"
     "Qgensym" "Qgensym_counter" "Qgentemp" "Qget" "Qget_decoded_time"
     "Qget_dispatch_macro_character" "Qget_internal_real_time"
     "Qget_internal_run_time" "Qget_macro_character"
     "Qget_output_stream_string" "Qget_properties" "Qget_setf_expansion"
     "Qget_setf_method" "Qget_setf_method_multiple_value"
     "Qget_universal_time" "Qgetf" "Qgethash" "Qgo" "Qgraphic_char_p"
     "Qhandler_bind" "Qhandler_case" "Qhash_table" "Qhash_table_count"
     "Qhash_table_iterator" "Qhash_table_p" "Qhash_table_rehash_size"
     "Qhash_table_rehash_threshold" "Qhash_table_size" "Qhash_table_test"
     "Qhost_compile_file_pathname" "Qhost_namestring" "Qidentity" "Qif"
     "Qifn" "Qignorable" "Qignore" "Qignore_errors" "Qimagpart" "Qimport"
     "Qin_package" "Qincf" "Qinclude_at_runtime" "Qinit_do_extern_syms"
     "Qinitialize_do_all_symbols_iterator" "Qinitialize_do_symbols_iterator"
     "Qinitialize_instance" "Qinitialize_with_package_iterator" "Qinline"
     "Qinput_stream_p" "Qinspect" "Qinteger" "Qinteger_decode_float"
     "Qinteger_length" "Qintegerp" "Qinteraction_stream"
     "Qinteraction_stream_p" "Qinteractive_stream_p" "Qintern"
     "Qinternal_marker" "Qinternal_marker_p"
     #+translator-supports-clos "Qinternal_standard_class"
     "Qinternal_time_units_per_second" "Qintersection"
     "Qinvalid_method_error" "Qinvoke_debugger" "Qinvoke_restart"
     "Qinvoke_restart_interactively" "Qisqrt"
     #+translator-supports-clos "Qkernel_generic_function"
     "Qkeyword" "Qkeywordp" "Qlabels" "Qlambda" "Qlambda_list_keywords"
     "Qlambda_parameters_limit" "Qlast" "Qlcm" "Qldb" "Qldb_test" "Qldiff"
     "Qleast_negative_double_float" "Qleast_negative_long_float"
     "Qleast_negative_normalized_double_float"
     "Qleast_negative_normalized_long_float"
     "Qleast_negative_normalized_short_float"
     "Qleast_negative_normalized_single_float" "Qleast_negative_short_float"
     "Qleast_negative_single_float" "Qleast_positive_double_float"
     "Qleast_positive_long_float" "Qleast_positive_normalized_double_float"
     "Qleast_positive_normalized_long_float"
     "Qleast_positive_normalized_short_float"
     "Qleast_positive_normalized_single_float" "Qleast_positive_short_float"
     "Qleast_positive_single_float" "Qlength" "Qlet" "Qlet_star"
     "Qlisp_implementation_type" "Qlisp_implementation_version" "Qlist"
     "Qlist_all_packages" "Qlist_length" "Qlist_nreverse" "Qlist_reverse"
     "Qlist_star" "Qlisten" "Qlistp" "Qload"
     "Qload_logical_pathname_translations" "Qload_pathname" "Qload_print"
     "Qload_run" "Qload_time_value" "Qload_truename" "Qload_verbose"
     #+translator-supports-clos "Qlocal_method"
     #+translator-supports-clos "Qlocal_slot_definition_p"
     "Qlocally" "Qlog" "Qlogand" "Qlogandc1" "Qlogandc2" "Qlogbitp"
     "Qlogcount" "Qlogeqv" "Qlogical_pathname" "Qlogical_pathname_p"
     "Qlogical_pathname_translations" "Qlogior" "Qlognand" "Qlognor"
     "Qlognot" "Qlogorc1" "Qlogorc2" "Qlogtest" "Qlogxor" "Qlong_float"
     "Qlong_float_epsilon" "Qlong_float_negative_epsilon" "Qlong_site_name"
     "Qloop" "Qloop_finish" "Qlower_case_p" "Qmachine_instance"
     "Qmachine_type" "Qmachine_version" "Qmacro_function" "Qmacroexpand"
     "Qmacroexpand_1" "Qmacroexpand_hook" "Qmacrolet" "Qmake_array"
     "Qmake_broadcast_stream" "Qmake_concatenated_stream" "Qmake_condition"
     "Qmake_dispatch_macro_character" "Qmake_echo_stream"
     "Qmake_foreign_pointer"
     #+translator-supports-clos "Qmake_generic_function"
     "Qmake_hash_table" "Qmake_instance" "Qmake_instances_obsolete"
     "Qmake_list" "Qmake_load_form" "Qmake_load_form_saving_slots"
     "Qmake_method" "Qmake_package" "Qmake_pathname" "Qmake_random_state"
     "Qmake_sequence" "Qmake_string" "Qmake_string_input_stream"
     "Qmake_string_output_stream" "Qmake_struct_foreign_type"
     "Qmake_structure_class" "Qmake_symbol" "Qmake_synonym_stream"
     "Qmake_two_way_stream" "Qmakunbound" "Qmalloc_foreign_pointer" "Qmap"
     "Qmap_into" "Qmapc" "Qmapcan" "Qmapcar" "Qmapcon" "Qmaphash" "Qmapl"
     "Qmaplist" "Qmask_field" "Qmax" "Qmember" "Qmember_if" "Qmember_if_not"
     "Qmemq" "Qmerge" "Qmerge_pathnames"
     #+translator-supports-clos "Qmetaobject"
     #+translator-supports-clos "Qmetaobject_documentation"
     #+translator-supports-clos "Qmetaobject_name"
     "Qmethod" #+translator-supports-clos "Qmethod_class"
     "Qmethod_combination"
     #+translator-supports-clos "Qmethod_combination_effective_method"
     "Qmethod_combination_error"
     #+translator-supports-clos "Qmethod_combination_for_method_combination_errors"
     #+translator-supports-clos "Qmethod_combination_function"
     #+translator-supports-clos "Qmethod_combination_name"
     #+translator-supports-clos "Qmethod_combination_options"
     #+translator-supports-clos "Qmethod_combination_p"
     #+translator-supports-clos "Qmethod_function"
     #+translator-supports-clos "Qmethod_generic_function"
     #+translator-supports-clos "Qmethod_lambda_list"
     "Qmethod_qualifiers" #+translator-supports-clos "Qmethod_slot_name"
     #+translator-supports-clos "Qmethod_specializers"
     "Qmin" "Qminus" "Qminusp" "Qmismatch" "Qmod" "Qmodules"
     "Qmost_negative_double_float" "Qmost_negative_fixnum"
     "Qmost_negative_long_float" "Qmost_negative_short_float"
     "Qmost_negative_single_float" "Qmost_positive_double_float"
     "Qmost_positive_fixnum" "Qmost_positive_long_float"
     "Qmost_positive_short_float" "Qmost_positive_single_float"
     "Qmuffle_warning" "Qmultiple_value_bind" "Qmultiple_value_call"
     "Qmultiple_value_list" "Qmultiple_value_prog1" "Qmultiple_value_setq"
     "Qmultiple_values_limit" "Qname_char" "Qnamestring" "Qnbutlast" "Qnconc"
     "Qncons" "Qnext_method_p" "Qnintersection" "Qninth"
     "Qno_applicable_method" "Qno_next_method"
     #+translator-supports-clos "Qno_primary_method"
     "Qnon_state_changing" "Qnon_state_using" "Qnonconsing" "Qnonrelocating"
     "Qnot" "Qnotany" "Qnotevery" "Qnotinline" "Qnreconc" "Qnreverse"
     "Qnset_difference" "Qnset_exclusive_or" "Qnstring_capitalize"
     "Qnstring_downcase" "Qnstring_upcase" "Qnsublis" "Qnsubst" "Qnsubst_if"
     "Qnsubst_if_not" "Qnsubstitute" "Qnsubstitute_if" "Qnsubstitute_if_not"
     "Qnth" "Qnth_value" "Qnthcdr" "Qnull" "Qnum_eq" "Qnum_ge" "Qnum_gt"
     "Qnum_le" "Qnum_lt" "Qnum_ne" "Qnumber" "Qnumberp" "Qnumerator"
     "Qnunion" #+translator-supports-clos "Qobject_change_class_function"
     #+translator-supports-clos "Qobject_creation_function"
     #+translator-supports-clos "Qobject_initialization_function"
     #+translator-supports-clos "Qobject_reinitialization_function"
     "Qoddp" "Qomit_at_runtime" "Qopen" "Qopen_stream_p" "Qoptimize"
     #+translator-supports-clos "Qoptimize_slot_access"
     #+translator-supports-clos "Qoptimize_slot_accesses"
     "Qor" "Qotherwise" "Qoutput_stream_p" "Qpackage_error"
     "Qpackage_error_package" "Qpackage_name" "Qpackage_nicknames"
     "Qpackage_shadowing_symbols" "Qpackage_type" "Qpackage_use_list"
     "Qpackage_used_by_list" "Qpackage_variable" "Qpackagep" "Qpairlis"
     "Qparse_declarations" "Qparse_error" "Qparse_integer" "Qparse_macro"
     "Qparse_namestring" "Qpathname" "Qpathname_device" "Qpathname_directory"
     "Qpathname_host" "Qpathname_match_p" "Qpathname_name" "Qpathname_type"
     "Qpathname_version" "Qpathnamep" "Qpeek_char"
     #+translator-supports-clos "Qpermit_metaobject_reinitialization"
     "Qphase" "Qpi" "Qplus" "Qplus_plus" "Qplus_plus_plus" "Qplusp"
     "Qpointer_foreign_type" "Qpop" "Qposition" "Qposition_if"
     "Qposition_if_not" "Qpprint" "Qpprint_dispatch"
     "Qpprint_exit_if_list_exhausted" "Qpprint_fill" "Qpprint_indent"
     "Qpprint_linear" "Qpprint_logical_block" "Qpprint_newline" "Qpprint_pop"
     "Qpprint_tab" "Qpprint_tabular" "Qprimitive_foreign_type" "Qprin1"
     "Qprin1_to_string" "Qprinc" "Qprinc_to_string" "Qprint" "Qprint_array"
     "Qprint_base" "Qprint_case" "Qprint_circle" "Qprint_escape"
     "Qprint_gensym" "Qprint_length" "Qprint_level" "Qprint_lines"
     "Qprint_miser_width" "Qprint_not_readable" "Qprint_not_readable_object"
     "Qprint_object" "Qprint_pprint_dispatch" "Qprint_pretty" "Qprint_radix"
     "Qprint_readably" "Qprint_right_margin" "Qprint_unreadable_object"
     "Qprobe_file" "Qproclaim" "Qprog" "Qprog1" "Qprog2" "Qprog_star"
     "Qprogn" "Qprogram_error" "Qprogv" "Qprompt_for_value" "Qprovide"
     "Qpsetf" "Qpsetq" "Qpush" "Qpushnew" "Qquery_io" "Qquote" "Qrandom"
     "Qrandom_state_p" "Qrandom_state_type" "Qrandom_state_variable"
     "Qrassoc" "Qrassoc_if" "Qrassoc_if_not" "Qratio" "Qrational"
     "Qrationalize" "Qrationalp" "Qratiop" "Qread" "Qread_base" "Qread_byte"
     "Qread_char" "Qread_char_no_hang" "Qread_default_float_format"
     "Qread_delimited_list" "Qread_eval" "Qread_from_string" "Qread_line"
     "Qread_preserving_whitespace" "Qread_suppress" "Qreader_error"
     "Qreadtable_case" "Qreadtable_type" "Qreadtable_variable" "Qreadtablep"
     "Qreal" "Qrealp" "Qrealpart"
     #+translator-supports-clos "Qrecord_method_combination_function"
     "Qreduce" "Qreinitialize_instance" "Qrem" "Qremf" "Qremhash" "Qremove"
     #+translator-supports-clos "Qremove_direct_subclass"
     "Qremove_duplicates" "Qremove_if" "Qremove_if_not" "Qremove_method"
     "Qremprop" "Qrename_file" "Qrename_package" "Qreplace" "Qrequire"
     "Qrest" "Qrestart" "Qrestart_bind" "Qrestart_case" "Qrestart_name"
     "Qreturn" "Qreturn_from" "Qrevappend" "Qreverse" "Qroom" "Qrotatef"
     "Qround" "Qrow_major_aref" "Qrplaca" "Qrplacd" "Qsafety" "Qsatisfies"
     "Qsbit" "Qscale_float" "Qschar" "Qsearch" "Qsecond" "Qsequence"
     "Qsequencep" "Qserious_condition" "Qset" "Qset_caaaar" "Qset_caaadr"
     "Qset_caaar" "Qset_caadar" "Qset_caaddr" "Qset_caadr" "Qset_caar"
     "Qset_cadaar" "Qset_cadadr" "Qset_cadar" "Qset_caddar" "Qset_cadddr"
     "Qset_caddr" "Qset_cadr" "Qset_car" "Qset_cdaaar" "Qset_cdaadr"
     "Qset_cdaar" "Qset_cdadar" "Qset_cdaddr" "Qset_cdadr" "Qset_cdar"
     "Qset_cddaar" "Qset_cddadr" "Qset_cddar" "Qset_cdddar" "Qset_cddddr"
     "Qset_cdddr" "Qset_cddr" "Qset_cdr" "Qset_char"
     #+translator-supports-clos "Qset_class_direct_subclasses"
     #+translator-supports-clos "Qset_class_finalized_p"
     #+translator-supports-clos "Qset_class_fully_defined_p"
     "Qset_compiler_macro_function" "Qset_declaration_information"
     "Qset_difference" "Qset_dispatch_macro_character" "Qset_eighth"
     "Qset_elt" "Qset_exclusive_or" "Qset_fdefinition" "Qset_fifth"
     "Qset_fill_pointer" "Qset_first" "Qset_foreign_pointer_address"
     "Qset_foreign_pointer_type" "Qset_foreign_string_value"
     "Qset_foreign_value" "Qset_fourth"
     #+translator-supports-clos "Qset_generic_function_initial_methods"
     #+translator-supports-clos "Qset_generic_function_methods"
     "Qset_get" "Qset_getf" "Qset_gethash"
     "Qset_logical_pathname_translations" "Qset_macro_character"
     "Qset_macro_function"
     #+translator-supports-clos "Qset_method_generic_function"
     "Qset_ninth" "Qset_nth" "Qset_package" "Qset_pprint_dispatch"
     "Qset_readtable_case" "Qset_rest" "Qset_row_major_aref" "Qset_schar"
     "Qset_second" "Qset_setf_function" "Qset_seventh" "Qset_sixth"
     "Qset_slot_value" #+translator-supports-clos "Qset_standard_object_ref"
     "Qset_subseq" "Qset_svref" "Qset_symbol_function" "Qset_symbol_plist"
     "Qset_syntax_from_char" "Qset_tenth" "Qset_third" "Qsetf"
     "Qsetf_function" "Qsetq" "Qseventh" "Qshadow" "Qshadowing_import"
     "Qshared_initialize"
     #+translator-supports-clos "Qshared_slot_definition_p"
     "Qshiftf" "Qshort_float" "Qshort_float_epsilon"
     "Qshort_float_negative_epsilon" "Qshort_site_name" "Qsignal"
     "Qsigned_byte" "Qsignum" "Qsimple_array" "Qsimple_array_p"
     "Qsimple_base_string" "Qsimple_bit_vector" "Qsimple_bit_vector_p"
     "Qsimple_condition" "Qsimple_condition_format_arguments"
     "Qsimple_condition_format_control" "Qsimple_error" "Qsimple_string"
     "Qsimple_string_p" "Qsimple_type_error" "Qsimple_vector"
     "Qsimple_vector_p" "Qsimple_warning" "Qsin" "Qsingle_float"
     "Qsingle_float_epsilon" "Qsingle_float_negative_epsilon" "Qsinh"
     "Qsixth" "Qslash" "Qslashslash" "Qslashslashslash" "Qsleep"
     "Qslot_boundp" #+translator-supports-clos "Qslot_boundp_using_class"
     #+translator-supports-clos "Qslot_definition"
     #+translator-supports-clos "Qslot_definition_allocation"
     #+translator-supports-clos "Qslot_definition_initargs"
     #+translator-supports-clos "Qslot_definition_initform"
     #+translator-supports-clos "Qslot_definition_initfunction"
     #+translator-supports-clos "Qslot_definition_location"
     #+translator-supports-clos "Qslot_definition_name"
     #+translator-supports-clos "Qslot_definition_readers"
     #+translator-supports-clos "Qslot_definition_type"
     #+translator-supports-clos "Qslot_definition_writers"
     "Qslot_exists_p" "Qslot_makunbound"
     #+translator-supports-clos "Qslot_makunbound_using_class"
     "Qslot_missing" "Qslot_unbound" "Qslot_value"
     #+translator-supports-clos "Qslot_value_using_class"
     #+translator-supports-clos "Qslotted_class"
     "Qsoftware_type" "Qsoftware_version" "Qsome" "Qsort" "Qspace" "Qspecial"
     "Qspecial_form_p" "Qspecial_operator_p" "Qspeed" "Qsqrt" "Qstable_sort"
     "Qstandard" #+translator-supports-clos "Qstandard_accessor_method"
     "Qstandard_char" "Qstandard_char_p" "Qstandard_class"
     #+translator-supports-clos "Qstandard_direct_slot_definition"
     #+translator-supports-clos "Qstandard_effective_local_slot_definition"
     #+translator-supports-clos "Qstandard_effective_shared_slot_definition"
     #+translator-supports-clos "Qstandard_effective_slot_definition"
     "Qstandard_generic_function" "Qstandard_input" "Qstandard_method"
     "Qstandard_object" "Qstandard_object_p"
     #+translator-supports-clos "Qstandard_object_ref"
     "Qstandard_output" #+translator-supports-clos "Qstandard_reader_method"
     #+translator-supports-clos "Qstandard_slot_definition"
     #+translator-supports-clos "Qstandard_writer_method"
     "Qstar" "Qstar_star" "Qstar_star_star" "Qstationary_object_p" "Qstep"
     "Qstorage_condition" "Qstore_value" "Qstream" "Qstream_element_type"
     "Qstream_error" "Qstream_error_stream" "Qstream_external_format"
     "Qstreamp" "Qstring" "Qstring_append" "Qstring_capitalize"
     "Qstring_char" "Qstring_downcase" "Qstring_eq" "Qstring_equal"
     "Qstring_ge" "Qstring_greaterp" "Qstring_gt" "Qstring_input_stream"
     "Qstring_input_stream_p" "Qstring_le" "Qstring_left_trim"
     "Qstring_lessp" "Qstring_lt" "Qstring_ne" "Qstring_not_equal"
     "Qstring_not_greaterp" "Qstring_not_lessp" "Qstring_output_stream"
     "Qstring_output_stream_p" "Qstring_right_trim" "Qstring_stream"
     "Qstring_stream_index" "Qstring_stream_p" "Qstring_trim"
     "Qstring_upcase" "Qstringp" "Qstructure" "Qstructure_class"
     "Qstructure_foreign_type" "Qstructure_object" "Qstructure_object_p"
     "Qstyle_warning" "Qsub1" "Qsublis" "Qsubseq" "Qsubsetp" "Qsubst"
     "Qsubst_if" "Qsubst_if_not" "Qsubstitute" "Qsubstitute_if"
     "Qsubstitute_if_not" "Qsubtypep" "Qsvref" "Qsxhash" "Qsymbol"
     "Qsymbol_function" "Qsymbol_macrolet" "Qsymbol_name" "Qsymbol_package"
     "Qsymbol_plist" "Qsymbol_value" "Qsymbolp" "Qsynonym_stream"
     "Qsynonym_stream_p" "Qsynonym_stream_symbol" "Qtagbody" "Qtailp" "Qtan"
     "Qtanh" "Qtenth" "Qterminal_io" "Qterpri" "Qthe" "Qthird" "Qthrow"
     "Qtime" "Qtoplevel_c_lines" "Qtotal_memory_used" "Qtrace"
     "Qtrace_output" "Qtranslate_logical_pathname" "Qtranslate_pathname"
     "Qtree_equal" "Qtruename" "Qtruncate" "Qtwo_way_stream"
     "Qtwo_way_stream_input_stream" "Qtwo_way_stream_output_stream"
     "Qtwo_way_stream_p" "Qtype" "Qtype_error" "Qtype_error_datum"
     "Qtype_error_expected_type" "Qtype_of" "Qtypecase" "Qtyped_foreign_aref"
     "Qtypep" "Query_io" "Qunbound_slot" "Qunbound_slot_instance"
     "Qunbound_variable" "Qundefine_foreign_type" "Qundefined_function"
     "Qunexport" "Qunintern" "Qunion" "Qunless" "Qunread_char"
     "Qunread_variable" "Qunsigned_byte" "Quntrace" "Qunuse_package"
     "Qunwind_protect" "Qunwritten_variable"
     #+translator-supports-clos "Qupdate_initial_methods"
     "Qupdate_instance_for_different_class"
     "Qupdate_instance_for_redefined_class" "Qupgraded_array_element_type"
     "Qupgraded_complex_part_type" "Qupper_case_p" "Quse_package"
     "Quse_value" "Quser_homedir_pathname"
     #+translator-supports-clos "Qvalid_change_class_initargs"
     #+translator-supports-clos "Qvalid_creation_initargs"
     #+translator-supports-clos "Qvalid_reinitialization_initargs"
     #+translator-supports-clos "Qvalidate_superclass"
     "Qvalues" "Qvalues_list" "Qvariable" "Qvariable_information" "Qvector"
     "Qvector_pop" "Qvector_push" "Qvector_push_extend" "Qvectorp" "Qwarn"
     "Qwarning" "Qwhen" "Qwild_pathname_p" "Qwith_accessors" "Qwith_area"
     "Qwith_compilation_unit" "Qwith_condition_restarts"
     "Qwith_dynamic_allocation" "Qwith_dynamic_area"
     "Qwith_hash_table_iterator" "Qwith_input_from_string"
     "Qwith_local_allocation" "Qwith_local_area" "Qwith_open_file"
     "Qwith_open_stream" "Qwith_output_to_string" "Qwith_package_iterator"
     "Qwith_simple_restart" "Qwith_slots" "Qwith_standard_io_syntax"
     "Qwith_static_area" "Qwrite" "Qwrite_byte" "Qwrite_char" "Qwrite_line"
     "Qwrite_string" "Qwrite_to_string" "Qxor" "Qy_or_n_p" "Qyes_or_no_p"
     "Qzerop" "Random_state" "Read_base" "Read_default_float_format"
     "Read_eval" "Read_suppress" "Readtable" "SETF_aref" "SETF_bit"
     #+translator-supports-clos "SETF_find_class"
     "SETF_sbit" "SET_BIGNUM_DIGIT" "SET_PACKAGE" "SI_ADD_IMPORT"
     "SI_ADD_PACKAGE_NICKNAME" "SI_ADD_PACKAGE_USE" "SI_ADD_SHADOW"
     "SI_Called_function" "SI_Catch_stack" "SI_Char_names"
     #+translator-supports-clos "SI_Check_initargs"
     "SI_Double_float_kludge_temp" "SI_Double_float_kludge_temp1"
     "SI_ENSURE_GLOBAL" "SI_First_value" "SI_Float_negative_one"
     "SI_Float_one" "SI_Float_zero" "SI_Format_stream" "SI_Frontier_stack"
     #+translator-supports-clos "SI_Function_slot_vector"
     #+translator-supports-clos "SI_Function_wrapper"
     "SI_Gc_external_roots"
     #+translator-supports-clos "SI_Generic_functions_bootstrapped"
     "SI_INIT_NIL" "SI_INIT_T" "SI_INIT_automatic_gc" "SI_INIT_backquote"
     #+translator-supports-clos "SI_INIT_clos_bootstrap_info"
     "SI_INIT_dynamic_heaps" "SI_INIT_error" "SI_INIT_evals"
     "SI_INIT_filesys" "SI_INIT_io" "SI_INIT_lambda_lists"
     #+translator-supports-clos "SI_INIT_method_combination"
     "SI_INIT_misc" "SI_INIT_new_bignums" "SI_INIT_numbers"
     "SI_INIT_packages" "SI_INIT_packages_1" "SI_INIT_print" "SI_INIT_reader"
     "SI_INIT_standard_packages" "SI_INIT_streams" "SI_INIT_structure_class"
     #+translator-supports-clos "SI_Initial_class_info"
     #+translator-supports-clos "SI_Initial_generic_function_info"
     "SI_Initial_packages"
     #+translator-supports-clos "SI_Make_instances_obsolete_slots_to_flush"
     "SI_NEW_SYMBOL" #+translator-supports-clos "SI_Package_wrapper"
     "SI_Plist_of_nil" #+translator-supports-clos "SI_Qallocation"
     #+translator-supports-clos "SI_Qargument_precedence_map"
     #+translator-supports-clos "SI_Qargument_precedence_order"
     #+translator-supports-clos "SI_Qarguments"
     #+translator-supports-clos "SI_Qcritical_methods"
     #+translator-supports-clos "SI_Qdeclarations"
     #+translator-supports-clos "SI_Qdirect_default_initargs"
     #+translator-supports-clos "SI_Qdirect_slots"
     #+translator-supports-clos "SI_Qdirect_subclasses"
     #+translator-supports-clos "SI_Qdirect_superclasses"
     #+translator-supports-clos "SI_Qdoc_string"
     #+translator-supports-clos "SI_Qeffective_methods"
     #+translator-supports-clos "SI_Qeql_specialized_methods"
     #+translator-supports-clos "SI_Qgeneric_function"
     #+translator-supports-clos "SI_Qinitargs"
     #+translator-supports-clos "SI_Qinitform"
     #+translator-supports-clos "SI_Qinitfunction"
     #+translator-supports-clos "SI_Qinitial_methods"
     #+translator-supports-clos "SI_Qkeyword_parameter_map"
     #+translator-supports-clos "SI_Qlambda_list"
     #+translator-supports-clos "SI_Qlocation"
     #+translator-supports-clos "SI_Qmethod_class"
     #+translator-supports-clos "SI_Qmethod_combination"
     #+translator-supports-clos "SI_Qmethods"
     #+translator-supports-clos "SI_Qname"
     #+translator-supports-clos "SI_Qobject"
     #+translator-supports-clos "SI_Qprecedence_list"
     #+translator-supports-clos "SI_Qprevious"
     #+translator-supports-clos "SI_Qprototype"
     #+translator-supports-clos "SI_Qqualifiers"
     #+translator-supports-clos "SI_Qreaders"
     #+translator-supports-clos "SI_Qshared_slot_locations"
     #+translator-supports-clos "SI_Qslot_name"
     #+translator-supports-clos "SI_Qslot_type"
     #+translator-supports-clos "SI_Qslots"
     #+translator-supports-clos "SI_Qslots_alist"
     #+translator-supports-clos "SI_Qspecialized_positions"
     #+translator-supports-clos "SI_Qspecializers"
     #+translator-supports-clos "SI_Qstatus_bits"
     #+translator-supports-clos "SI_Qsuperclass"
     #+translator-supports-clos "SI_Qvalue"
     #+translator-supports-clos "SI_Qwrapper"
     #+translator-supports-clos "SI_Qwriters"
     #+translator-supports-clos "SI_SETF_documentation__method_combination"
     #+translator-supports-clos "SI_SETF_slot_value_using_class"
     #+translator-supports-clos "SI_SETF_slot_value_using_class_local"
     #+translator-supports-clos "SI_SETF_slot_value_using_class_shared"
     "SI_Special_stack" "SI_Stack_vector_header" "SI_Stream_etypes"
     "SI_T_make_array_1" "SI_T_untagged"
     #+translator-supports-clos "SI_The_class_Funcallable_standard_class"
     #+translator-supports-clos "SI_The_class_Method_class"
     #+translator-supports-clos "SI_The_class_Standard_class"
     #+translator-supports-clos "SI_The_class_Standard_direct_slot_definition"
     #+translator-supports-clos "SI_The_class_Standard_effective_local_slot_definition"
     #+translator-supports-clos "SI_The_class_Standard_generic_function"
     #+translator-supports-clos "SI_The_class_Standard_method"
     #+translator-supports-clos "SI_The_class_Standard_object"
     #+translator-supports-clos "SI_The_class_Standard_reader_method"
     #+translator-supports-clos "SI_The_class_Standard_writer_method"
     #+translator-supports-clos "SI_The_class_T"
     #+translator-supports-clos "SI_Validation_tables_initialized"
     #+translator-supports-clos "SI_WRAPPER_broadcast_stream"
     #+translator-supports-clos "SI_WRAPPER_cobject"
     #+translator-supports-clos "SI_WRAPPER_concatenated_stream"
     #+translator-supports-clos "SI_WRAPPER_early_generic_function"
     #+translator-supports-clos "SI_WRAPPER_echo_stream"
     #+translator-supports-clos "SI_WRAPPER_effective_method"
     #+translator-supports-clos "SI_WRAPPER_file_stream"
     #+translator-supports-clos "SI_WRAPPER_foreign_pointer"
     #+translator-supports-clos "SI_WRAPPER_function"
     #+translator-supports-clos "SI_WRAPPER_hash_table"
     #+translator-supports-clos "SI_WRAPPER_interaction_stream"
     #+translator-supports-clos "SI_WRAPPER_logical_pathname"
     #+translator-supports-clos "SI_WRAPPER_method_combination"
     #+translator-supports-clos "SI_WRAPPER_package"
     #+translator-supports-clos "SI_WRAPPER_pathname"
     #+translator-supports-clos "SI_WRAPPER_random_state"
     #+translator-supports-clos "SI_WRAPPER_readtable"
     #+translator-supports-clos "SI_WRAPPER_string_input_stream"
     #+translator-supports-clos "SI_WRAPPER_string_output_stream"
     #+translator-supports-clos "SI_WRAPPER_synonym_stream"
     #+translator-supports-clos "SI_WRAPPER_two_way_stream"
     #+translator-supports-clos "SI_add_direct_subclass"
     #+translator-supports-clos "SI_add_direct_subclass__after__forward_class"
     #+translator-supports-clos "SI_add_direct_subclass__around"
     #+translator-supports-clos "SI_add_direct_subclass__before"
     "SI_add_external_root" #+translator-supports-clos "SI_add_method"
     #+translator-supports-clos "SI_add_method__after__change_class"
     #+translator-supports-clos "SI_add_method__after__creation"
     #+translator-supports-clos "SI_add_method__after__reinitialization"
     #+translator-supports-clos "SI_add_method__before"
     #+translator-supports-clos "SI_add_reader_method"
     #+translator-supports-clos "SI_add_writer_method"
     "SI_adjoin_n" "SI_adjust_array_n" "SI_alloc" "SI_alloc_bignum"
     #+translator-supports-clos "SI_alloc_early_class_wrappers"
     "SI_alloc_primitive_vector" "SI_allocate_bignum"
     #+translator-supports-clos "SI_allocate_instance__early_dispatcher"
     #+translator-supports-clos "SI_allocate_instance__funcallable_standard_class"
     #+translator-supports-clos "SI_allocate_instance__method_class"
     #+translator-supports-clos "SI_allocate_instance__standard_class"
     "SI_area_name_to_area" "SI_array_contents"
     "SI_array_row_major_index_aux" "SI_assoc_if_n" "SI_assoc_if_not_n"
     "SI_assoc_n" "SI_bad_funcallable_error" "SI_bignum_compare"
     "SI_bignum_compare_s" "SI_bind_symbols"
     #+translator-supports-clos "SI_bootstrap_clos"
     "SI_cached_frontier" "SI_cached_limit"
     #+translator-supports-clos "SI_caching_discriminator"
     "SI_cerror" "SI_cerror_fptr"
     #+translator-supports-clos "SI_change_class"
     #+translator-supports-clos "SI_change_class__around__class"
     #+translator-supports-clos "SI_change_class__around__metaobject"
     #+translator-supports-clos "SI_change_class__around__t_class"
     #+translator-supports-clos "SI_change_class__t_symbol"
     "SI_char_relop" "SI_char_relopn"
     #+translator-supports-clos "SI_class_default_initargs"
     #+translator-supports-clos "SI_class_default_superclasses__funcallable_standard_class"
     #+translator-supports-clos "SI_class_default_superclasses__method_class"
     #+translator-supports-clos "SI_class_default_superclasses__standard_class"
     #+translator-supports-clos "SI_class_default_superclasses__structure_class"
     #+translator-supports-clos "SI_class_finalized_p"
     #+translator-supports-clos "SI_class_fully_defined_p"
     #+translator-supports-clos "SI_class_fully_defined_p__forward_class"
     #+translator-supports-clos "SI_class_precedence_list"
     #+translator-supports-clos "SI_class_prototype"
     #+translator-supports-clos "SI_class_slots"
     "SI_clear_whitespace_input"
     #+translator-supports-clos "SI_coerce_to_class"
     #+translator-supports-clos "SI_collect_direct_slot_definitions"
     #+translator-supports-clos "SI_collect_required_arguments"
     "SI_comma_macro_handler"
     #+translator-supports-clos "SI_compute_applicable_methods"
     #+translator-supports-clos "SI_compute_applicable_methods_using_classes"
     #+translator-supports-clos "SI_compute_argument_precedence_map"
     #+translator-supports-clos "SI_compute_class_default_initargs"
     #+translator-supports-clos "SI_compute_class_precedence_list"
     #+translator-supports-clos "SI_compute_class_precedence_vector"
     #+translator-supports-clos "SI_compute_class_prototype__before"
     #+translator-supports-clos "SI_compute_class_prototype__early_dispatcher"
     #+translator-supports-clos "SI_compute_class_prototype__funcallable_standard_class"
     #+translator-supports-clos "SI_compute_class_prototype__method_class"
     #+translator-supports-clos "SI_compute_class_prototype__standard_class"
     #+translator-supports-clos "SI_compute_class_slots_alist"
     #+translator-supports-clos "SI_compute_effective_method"
     #+translator-supports-clos "SI_compute_effective_slot_definition"
     #+translator-supports-clos "SI_compute_effective_slot_definition_initargs"
     #+translator-supports-clos "SI_compute_method_frame_rest"
     #+translator-supports-clos "SI_compute_slot_definition_location"
     #+translator-supports-clos "SI_compute_slot_definition_location__local"
     #+translator-supports-clos "SI_compute_slot_definition_location__shared"
     #+translator-supports-clos "SI_compute_slot_definition_locations"
     #+translator-supports-clos "SI_compute_slots"
     #+translator-supports-clos "SI_compute_valid_change_class_initargs"
     #+translator-supports-clos "SI_compute_valid_creation_initargs"
     #+translator-supports-clos "SI_compute_valid_reinitialization_initargs"
     "SI_config_1_tag_width" "SI_config_big_endian"
     "SI_config_copying_collector" "SI_config_exactly_once"
     "SI_config_nil_is_zero" "SI_config_not_conses_have_headers"
     "SI_config_not_segmented_dynamic_area"
     #-translator-supports-clos "SI_config_not_support_clos"
     #+translator-supports-clos "SI_config_support_clos"
     #+translator-supports-clos "SI_congruent_lambda_list_encodings_p"
     "SI_cons" "SI_cons_with_gc"
     #+translator-supports-clos "SI_copy_instance__funcallable_standard_class"
     #+translator-supports-clos "SI_copy_instance__method_class"
     #+translator-supports-clos "SI_copy_instance__standard_class"
     "SI_copy_object" "SI_count_if_n" "SI_count_if_not_n" "SI_count_n"
     #+translator-supports-clos "SI_default_initargs"
     "SI_delete_duplicates_n" "SI_delete_if" "SI_delete_if_n"
     "SI_delete_if_not_n" "SI_delete_n"
     #+translator-supports-clos "SI_direct_slot_definition_class"
     #+translator-supports-clos "SI_display_cache_statistics"
     "SI_do_math2"
     #+translator-supports-clos "SI_documentation__method_combination"
     #+translator-supports-clos "SI_documentation_extraneous_type_error"
     "SI_double_float_make_array_1"
     #+translator-supports-clos "SI_effective_method_no_next_method"
     #+translator-supports-clos "SI_effective_slot_definition_class"
     #+translator-supports-clos "SI_elide_access_method_p"
     #+translator-supports-clos "SI_elide_access_method_p__local"
     #+translator-supports-clos "SI_empty_cache_discriminator"
     #+translator-supports-clos "SI_encode_lambda_list"
     #+translator-supports-clos "SI_eql_caching_discriminator"
     "SI_error" "SI_error_fptr" "SI_errorn" "SI_errorn_fptr" "SI_fatal_error"
     "SI_fill_n" "SI_fill_primitive_vector"
     #+translator-supports-clos "SI_finalize_inheritance"
     #+translator-supports-clos "SI_finalize_inheritance__around"
     #+translator-supports-clos "SI_finalize_inheritance__before"
     #+translator-supports-clos "SI_find_forward_referenced_class"
     "SI_find_if_n" "SI_find_if_not_n"
     #+translator-supports-clos "SI_find_method"
     "SI_find_n" "SI_find_structure_constructor"
     "SI_find_structure_constructor_fptr"
     "SI_find_structure_constructor_short" "SI_find_structure_header"
     "SI_find_structure_header_fptr" "SI_find_structure_header_short"
     "SI_find_structure_print_function"
     "SI_find_structure_print_function_fptr"
     "SI_find_structure_print_function_short"
     #+translator-supports-clos "SI_forget_effective_methods"
     "SI_format_taking_nargs" "SI_fp_eq_1" "SI_fp_eq_2" "SI_fp_eql_1"
     #+translator-supports-clos "SI_function_keywords"
     "SI_garbage_collect" "SI_garbage_collect_fptr" "SI_gc_count"
     "SI_gc_genobj" "SI_gc_silence_init" "SI_gc_unsafe"
     "SI_get_foreign_space" "SI_get_internal_msec"
     #+translator-supports-clos "SI_global_slot_index"
     "SI_igcd" "SI_in_package_n"
     #+translator-supports-clos "SI_index_bound_error"
     "SI_init_hash_tables" "SI_init_sequence_fn"
     #+translator-supports-clos "SI_init_slot_index_table"
     "SI_init_streams_flag" "SI_initfuns"
     #+translator-supports-clos "SI_initialize_instance"
     #+translator-supports-clos "SI_initialize_instance__after__class"
     #+translator-supports-clos "SI_initialize_instance__after__function"
     #+translator-supports-clos "SI_initialize_instance__after__method"
     "SI_initsyms" "SI_insert_T" "SI_internal_funcall" "SI_intersection_n"
     "SI_istring" "SI_keyword_arg_p" "SI_lclose_n" "SI_load_n"
     "SI_load_run_n" #+translator-supports-clos "SI_local_slot_definition_p"
     #+translator-supports-clos "SI_local_slot_definition_p__default"
     #+translator-supports-clos "SI_local_slot_definition_p__local"
     #+translator-supports-clos "SI_local_slot_definition_p__shared"
     "SI_long_to_bignum" "SI_long_to_bignum_s" "SI_lopen_n" "SI_lunion_n"
     "SI_lwrite_n" "SI_make_array_lite" "SI_make_array_n"
     #+translator-supports-clos "SI_make_class_wrapper"
     #+translator-supports-clos "SI_make_encoded_lambda_list"
     "SI_make_hash_table_n" #+translator-supports-clos "SI_make_instance"
     #+translator-supports-clos "SI_make_instance__symbol"
     #+translator-supports-clos "SI_make_instances_obsolete"
     "SI_make_list_n" "SI_make_package_n" "SI_make_pathname_n"
     "SI_make_rest_arg" "SI_make_sequence_n" "SI_make_static_array"
     "SI_make_string_n" "SI_make_structure"
     #+translator-supports-clos "SI_make_wrapper_class_associations"
     #+translator-supports-clos "SI_make_wrapper_obsolete"
     "SI_member_if_n" "SI_member_if_not_n" "SI_member_n" "SI_merge_n"
     #+translator-supports-clos "SI_method_combination_documentation"
     #+translator-supports-clos "SI_method_frame_list"
     #+translator-supports-clos "SI_method_frame_parse_keywords"
     #+translator-supports-clos "SI_method_function"
     "SI_mismatch_n" "SI_mv_funcall" "SI_next_prime" "SI_nintersection_n"
     #+translator-supports-clos "SI_no_applicable_method"
     "SI_no_gc" #+translator-supports-clos "SI_no_next_method"
     #+translator-supports-clos "SI_no_primary_method"
     "SI_nset_difference_n" "SI_nset_exclusive_or_n"
     "SI_nstring_capitalize_n" "SI_nstring_downcase_n" "SI_nstring_upcase_n"
     "SI_nsublis_n" "SI_nsubst_if_n" "SI_nsubst_if_not_n" "SI_nsubst_n"
     "SI_nsubstitute_if_n" "SI_nsubstitute_if_not_n" "SI_nsubstitute_n"
     "SI_nunion_n" "SI_obtain_rest_list"
     #+translator-supports-clos "SI_odd_length_keylist_error"
     #+translator-supports-clos "SI_optimize_slot_access"
     #+translator-supports-clos "SI_optimize_slot_access__local"
     #+translator-supports-clos "SI_optimize_slot_accesses"
     "SI_parse_integer_n" #+translator-supports-clos "SI_parse_lambda_list"
     "SI_parse_namestring_n"
     #+translator-supports-clos "SI_permit_metaobject_reinitialization"
     #+translator-supports-clos "SI_permit_metaobject_reinitialization__forward_class"
     #+translator-supports-clos "SI_permit_metaobject_reinitialization__function"
     #+translator-supports-clos "SI_permit_metaobject_reinitialization__standard_class"
     "SI_position_if_n" "SI_position_if_not_n" "SI_position_n"
     #+translator-supports-clos "SI_print_object"
     #+translator-supports-clos "SI_print_object__class_wrapper"
     #+translator-supports-clos "SI_print_object__effective_method"
     #+translator-supports-clos "SI_print_object__metaobject"
     #+translator-supports-clos "SI_print_object__method_combination"
     "SI_progv_do_bindings" "SI_progv_restore_bindings"
     "SI_progv_save_bindings" "SI_rassoc_if_n" "SI_rassoc_if_not_n"
     "SI_rassoc_n" "SI_re_throw" "SI_read_from_string_n"
     #+translator-supports-clos "SI_record_early_class"
     "SI_reduce_n" #+translator-supports-clos "SI_reinitialize_instance"
     #+translator-supports-clos "SI_reinitialize_instance__after__class"
     #+translator-supports-clos "SI_reinitialize_instance__around__class"
     #+translator-supports-clos "SI_reinitialize_instance__around__metaobject"
     #+translator-supports-clos "SI_reinitialize_instance__before__class"
     #+translator-supports-clos "SI_remove_direct_subclass"
     "SI_remove_duplicates_n" "SI_remove_if_n" "SI_remove_if_not_n"
     #+translator-supports-clos "SI_remove_method"
     #+translator-supports-clos "SI_remove_method__after__change_class"
     #+translator-supports-clos "SI_remove_method__after__creation"
     #+translator-supports-clos "SI_remove_method__after__reinitialization"
     "SI_remove_n" "SI_replace_n" "SI_requires_escaping_fptr"
     "SI_requires_escaping_full" "SI_requires_escaping_short"
     "SI_restart_unsafe" "SI_restore_values" "SI_save_more_values"
     "SI_save_values" "SI_search_n"
     #+translator-supports-clos "SI_set_class_finalized_p"
     #+translator-supports-clos "SI_set_class_fully_defined_p"
     #+translator-supports-clos "SI_set_class_fully_defined_p__around__forward_class"
     "SI_set_difference_n" "SI_set_exclusive_or_n"
     #+translator-supports-clos "SI_set_method_combination_documentation"
     #+translator-supports-clos "SI_set_slot_value"
     "SI_set_symbol_field" "SI_set_symbol_function_location"
     "SI_set_symbol_value_helper" "SI_set_symbol_value_location"
     #+translator-supports-clos "SI_shared_initialize"
     #+translator-supports-clos "SI_shared_initialize__after__standard_generic_function"
     #+translator-supports-clos "SI_shared_initialize__early_dispatcher"
     #+translator-supports-clos "SI_shared_slot_definition_p"
     #+translator-supports-clos "SI_shared_slot_definition_p__default"
     #+translator-supports-clos "SI_shared_slot_definition_p__local"
     #+translator-supports-clos "SI_shared_slot_definition_p__shared"
     "SI_shorten_primitive_vector" "SI_single_float_make_array_1"
     #+translator-supports-clos "SI_slot_boundp"
     #+translator-supports-clos "SI_slot_boundp_using_class"
     #+translator-supports-clos "SI_slot_boundp_using_class_local"
     #+translator-supports-clos "SI_slot_boundp_using_class_shared"
     #+translator-supports-clos "SI_slot_makunbound"
     #+translator-supports-clos "SI_slot_makunbound_using_class"
     #+translator-supports-clos "SI_slot_makunbound_using_class_local"
     #+translator-supports-clos "SI_slot_makunbound_using_class_shared"
     #+translator-supports-clos "SI_slot_missing"
     #+translator-supports-clos "SI_slot_unbound"
     #+translator-supports-clos "SI_slot_value"
     #+translator-supports-clos "SI_slot_value_unbound"
     #+translator-supports-clos "SI_slot_value_using_class"
     #+translator-supports-clos "SI_slot_value_using_class_local"
     #+translator-supports-clos "SI_slot_value_using_class_shared"
     "SI_sort_n" "SI_stable_sort_n"
     #+translator-supports-clos "SI_standard_reader_method"
     "SI_standard_structure_constructor_error"
     #+translator-supports-clos "SI_standard_writer_method"
     "SI_static_bignum_negative_one" "SI_static_bignum_one"
     "SI_static_bignum_zero" "SI_stream_getc" "SI_stream_ungetc"
     "SI_string_base" "SI_string_capitalize_n" "SI_string_downcase_n"
     "SI_string_eq_n" "SI_string_equal_n" "SI_string_ge_n"
     "SI_string_greaterp_n" "SI_string_gt_n" "SI_string_le_n"
     "SI_string_lessp_n" "SI_string_lt_n" "SI_string_ne_n"
     "SI_string_not_equal_n" "SI_string_not_greaterp_n"
     "SI_string_not_lessp_n" "SI_string_upcase_n" "SI_structure_subtypep"
     "SI_structure_type_specifier_p" "SI_structure_typep" "SI_sublis_n"
     "SI_subsetp_n" "SI_subst_if_n" "SI_subst_if_not_n" "SI_subst_n"
     "SI_substitute_if_n" "SI_substitute_if_not_n" "SI_substitute_n"
     #+translator-supports-clos "SI_subtypep__classes"
     "SI_symbol_field" "SI_throw"
     #+translator-supports-clos "SI_too_few_arguments_error"
     #+translator-supports-clos "SI_too_many_arguments_error"
     "SI_tree_equal_n" "SI_type_error"
     #+translator-supports-clos "SI_typep_using_class"
     "SI_unbind_and_jump"
     #+translator-supports-clos "SI_uncached_discriminator"
     "SI_undefined_function_error"
     #+translator-supports-clos "SI_unexpected_keyword_argument_error"
     #+translator-supports-clos "SI_uninitialized_generic_function"
     #+translator-supports-clos "SI_update_instance_for_different_class"
     #+translator-supports-clos "SI_update_instance_for_different_class__after__class"
     #+translator-supports-clos "SI_update_instance_for_different_class__before__class"
     #+translator-supports-clos "SI_valid_change_class_initargs"
     #+translator-supports-clos "SI_valid_creation_initargs"
     #+translator-supports-clos "SI_valid_reinitialization_initargs"
     #+translator-supports-clos "SI_validate_superclass"
     #+translator-supports-clos "SI_validate_superclass__forward"
     #+translator-supports-clos "SI_validate_superclass__funcallable"
     #+translator-supports-clos "SI_validate_superclass__method"
     #+translator-supports-clos "SI_validate_superclass__standard"
     #+translator-supports-clos "SI_validate_superclass__structure"
     "SI_warn" "SI_warn_fptr" #+translator-supports-clos "SI_wrapper_of"
     "SI_write_line_n" "SI_write_string_n" "SI_write_to_string_n"
     "SI_y_or_n_p_aux" "SI_y_or_n_p_query" "SI_y_or_n_p_taking_nargs"
     "SI_yes_or_no_p_query" "SI_yes_or_no_p_taking_nargs" "STATIC_BIT_ARRAY"
     "STATIC_CHAR_ARRAY" "STATIC_CONS" "STATIC_FLOAT" "STATIC_FUNCTION"
     "STATIC_GENERAL_ARRAY" "STATIC_LIST" "STATIC_NEGATIVE_BIGNUM"
     "STATIC_PACKAGE" "STATIC_POSITIVE_BIGNUM" "STATIC_RATIO" "STATIC_STRING"
     "STATIC_SYMBOL" "Short_float_epsilon" "Short_float_negative_epsilon"
     "Short_site_name_string" "Single_float_epsilon"
     "Single_float_negative_epsilon" "Sl" "Sl_sl" "Sl_sl_sl" "Stack"
     "Standard_input" "Standard_output" "Star" "Star_star" "Star_star_star"
     "Static_area" "T_temp" "Temp1" "Tempu" "Terminal_io"
     #+translator-supports-clos "The_class_T"
     "Trace_output" "UL_temp" "UNIQUE_TAG" "Us" "Values" "Values_count"
     "_makepath" "_splitpath" "acons" "add" "add1"
     #+translator-supports-clos "add_named_class"
     #+translator-supports-clos "add_named_generic_function"
     #+translator-supports-clos "add_named_method"
     "addn" "addr" "adjoin" "adjust_array" "adjustable_array_p"
     "advance_do_symbols_iterator" "advance_with_package_iterator"
     "alloc_memory_to_target" "alloc_segment"
     #+translator-supports-clos "allocate_instance"
     "allocate_memory_to_target" "allow_gc" "alpha_char_p" "alphanumericp"
     "append" "append2" "apply" "apply1" "apply2" "apply3" "apply_lambda"
     "applyhook" "area_bytes_in_use" "area_memory_limit" "area_memory_used"
     "area_target_size" "area_total_size" "aref" "aref0" "aref1" "aref2"
     "aref3" "aref4" "aref5" "aref6" "aref7" "array_dimension"
     "array_dimensions" "array_element_type" "array_has_fill_pointer_p"
     "array_in_bounds_p" "array_rank" "array_row_major_index"
     "array_total_size" "arrayp" "ash" "assoc" "assoc_eq" "assoc_eql"
     "assoc_equal" "assoc_if" "assoc_if_not" "assq" "atom"
     "backquot_top_level" "begin_hash_table_iterator"
     "begin_print_unreadable_object" "begin_time" "bignum_add" "bignum_ash"
     "bignum_compare" "bignum_divide" "bignum_equal_p"
     "bignum_fits_in_word_p" "bignum_integer_length" "bignum_length_in_bits"
     "bignum_length_upper_limit" "bignum_logand" "bignum_logcount"
     "bignum_logior" "bignum_lognot" "bignum_make_one" "bignum_make_zero"
     "bignum_max_digit_stream_radix" "bignum_multiply" "bignum_negate"
     "bignum_oddp" "bignum_quotient" "bignum_remainder" "bignum_subtract"
     "bignum_test" "bignum_to_digit_stream" "bignum_to_double"
     "bignum_to_long" "bignum_to_unsigned_long" "bignump" "binding_initform"
     "binding_variable" "bit_and" "bit_andc1" "bit_andc2" "bit_eqv" "bit_ior"
     "bit_nand" "bit_nor" "bit_not" "bit_orc1" "bit_orc2" "bit_vector_p"
     "bit_xor" "bitp" "boole" "both_case_p" "boundp" "bq_attach_append"
     "bq_attach_conses" "bq_completely_process" "bq_frob" "bq_process"
     "bq_remove_tokens" "bq_simplify" "bq_simplify_args" "bq_splicing_frob"
     "bracket" "breakn" "broadcast_stream_p" "butlast" "byte" "byte_position"
     "byte_size" "caaaar" "caaadr" "caaar" "caadar" "caaddr" "caadr" "caar"
     "cadaar" "cadadr" "cadar" "caddar" "cadddr" "caddr" "cadr"
     #+translator-supports-clos "call_next_method"
     "car" "cdaaar" "cdaadr" "cdaar" "cdadar" "cdaddr" "cdadr" "cdar"
     "cddaar" "cddadr" "cddar" "cdddar" "cddddr" "cdddr" "cddr"
     "cdouble_to_double" "cdr" "ceiling" "cerror" "cerrorn" "char_bit"
     "char_bits" "char_code" "char_downcase" "char_eq" "char_eqn" "char_eqr"
     "char_equal" "char_equaln" "char_equalr" "char_font" "char_ge"
     "char_gen" "char_ger" "char_greaterp" "char_greaterpn" "char_greaterpr"
     "char_gt" "char_gtn" "char_gtr" "char_int" "char_le" "char_len"
     "char_ler" "char_lessp" "char_lesspn" "char_lesspr" "char_lt" "char_ltn"
     "char_ltr" "char_name" "char_ne" "char_nen" "char_ner" "char_not_equal"
     "char_not_equaln" "char_not_equalr" "char_not_greaterp"
     "char_not_greaterpn" "char_not_greaterpr" "char_not_lessp"
     "char_not_lesspn" "char_not_lesspr" "char_upcase" "character"
     "characterp" "chase_input_stream" "chase_output_stream"
     "chase_write_stream" "check_feature" "cis"
     #+translator-supports-clos "class_of"
     #+translator-supports-clos "class_status_p"
     #+translator-supports-clos "class_wrapper_p"
     "cleanup_hash_table_iterator" "clear_input" "clear_output"
     "clong_to_bignum" "clrhash" "cobjectp" "code_char" "coerce" "commonp"
     "compiled_function_p" "complement" "complexp"
     #+translator-supports-clos "compute_method_combination"
     "concatenate" "concatenated_stream_p" "conjugate" "cons" "consp"
     "constant_initfunction" "constantly" "constantly_false"
     "constantly_nil_initfunction" "constantly_t_initfunction"
     "constantly_true"
     #+translator-supports-clos "constantly_zero_initfunction"
     "constantp" "copy_alist" "copy_foreign_pointer" "copy_list"
     "copy_readtable" "copy_seq" "copy_structure" "copy_symbol" "copy_tree"
     "count" "count_if" "count_if_not" "decode_float" "decode_universal_time"
     "default_structure_print_aux" "define_foreign_synonym_type"
     "defined_foreign_type_p" "defpackage_export" "defpackage_import_from"
     "defpackage_intern" "defpackage_use_package" "delete_duplicates"
     "delete_eq" "delete_eql" "delete_equal" "delete_file" "delete_if"
     "delete_if_not" "delq" "denominator" "deposit_field" "describe"
     "digit_char" "digit_char_p" "digit_stream_to_bignum" "directory"
     "directory_namestring"
     #+translator-supports-clos "display_cache_statistics"
     "divide" "dividen" "divider" "do_aref_1" "do_format" "do_remf"
     "do_setf_aref" "double_to_bignum" "double_to_integer" "dpb"
     "echo_stream_p" #+translator-supports-clos "effective_method_p"
     "eighth" "element_type_to_etype" "elt" "encode_universal_time"
     "end_hash_table_iterator" "endp" "enough_namestring"
     #+translator-supports-clos "ensure_class"
     #+translator-supports-clos "ensure_generic_function"
     "eq" "eql" "equal" "equalp" "error" "errorn" "eval_run" "evalhook"
     "evenp" "every" "expand_backquote" "export" "expt" "expt_long"
     "extend_string_output_stream" "fboundp" "fceiling" "fdefinition" "fifth"
     "file_author" "file_length" "file_namestring" "file_position"
     "file_stream_p" "file_write_date" "fill" "fill_pointer"
     #+translator-supports-clos "finalize_effective_method"
     "find" "find_all_symbols" #+translator-supports-clos "find_class"
     #+translator-supports-clos "find_effective_slot_definition"
     "find_if" "find_if_not"
     #+translator-supports-clos "find_instance_keyword"
     "find_package" #+translator-supports-clos "find_standard_method_class"
     #+translator-supports-clos "find_standard_method_combination"
     "find_symbol" "finish_output" "finish_print_unreadable_object"
     "finish_time" "first" "fixnump" "flatsize" "float_digits"
     "float_precision" "float_radix" "float_sign" "floatp" "fmakunbound"
     "force_gc" "force_output" "foreign_aref" "foreign_pointer_address"
     "foreign_pointer_p" "foreign_pointer_type" "foreign_pointer_type_p"
     "foreign_size_of" "foreign_string_value" "foreign_type_modulus"
     "foreign_type_name" "foreign_type_p" "foreign_type_remainder"
     "foreign_type_size" "foreign_typep" "foreign_value" "format" "formatn"
     "fourth" "free_foreign_pointer" "fresh_line" "fround" "funcall"
     "funcall0" "funcall1" "funcall2" "funcall3" "functionp" "gcd" "gcdn"
     "gcdr" "gensym" "gentemp" "get" "get_decoded_time"
     "get_dispatch_macro_character" "get_foreign_type"
     "get_internal_real_time" "get_internal_run_time" "get_macro_character"
     "get_next_node" "get_output_stream_string" "get_properties"
     "get_universal_time" "getch" "getf" "gethash" "graphic_char_p"
     "hash_table_count" "hash_table_iterator" "hash_table_p" "haumuch"
     "heap_command_line" "host_namestring" "ichar_name" "identity"
     "ifind_package" "ifind_symbol" "iintern" "ilength" "imagpart"
     "imake_duplicate_string" "import" "in_package" "iname_char"
     "init_bignums" "init_do_extern_syms" "init_heaps"
     "initialize_do_all_symbols_iterator" "initialize_do_symbols_iterator"
     #+translator-supports-clos "initialize_instance"
     "initialize_with_package_iterator" "initsyms_top_level" "input_stream_p"
     "inspect" "int_char" "integer_decode_float" "integer_length"
     "integer_to_long" "integer_to_unsigned_long" "integerp"
     "interaction_stream_p" "intern" "internal_marker_p" "intersection"
     "invalid_method_error" "isqrt" "istring_to_string"
     "istring_to_string_or_nil" "isymbol_name" "jacobi" "jb" "kbhit"
     "keywordp" "l_abs" "l_random" "l_round" "lacos" "lacosh" "lasin"
     "lasinh" "last" "latan" "latanh" "lbreak" "lchar" "lclose" "lcm" "lcmn"
     "lcmr" "lcomplex" "lcos" "lcosh" "ldb" "ldb_test" "ldelete" "ldiff"
     "length" "lexit" "lexp" "lffloor" "lfloat" "lfloor" "lfloor_1"
     "lftruncate" "lisp_implementation_type" "lisp_implementation_version"
     "list" "list_all_packages" "list_error" "list_length" "list_nreverse"
     "list_reverse" "list_star" "list_values" "listp" "llisten" "llog" "lmax"
     "lmaxr" "lmin" "lminr" "load" "load_run" "logand" "logandc1" "logandc2"
     "logandn" "logandr" "logbitp" "logcount" "logcount_long" "logeqv"
     "logeqvn" "logeqvr" "logical_pathname_p" "logior" "logiorn" "logiorr"
     "lognand" "lognor" "lognot" "logorc1" "logorc2" "logtest" "logxor"
     "logxorn" "logxorr" "long_site_name" "long_to_bignum" "lopen"
     "lower_case_p" "lread" "lremove" "lsin" "lsinh" "lsleep" "lsqrt" "ltan"
     "ltanh" "ltimes" "ltruncate" "lunion" "lwrite" "m_nthcdr"
     "machine_instance" "machine_type" "machine_version" "macro_function"
     "macroexpand" "macroexpand_1" "main" "make_array"
     "make_broadcast_stream"
     #+translator-supports-clos "make_call_next_method"
     #+translator-supports-clos "make_call_next_method_safe"
     "make_canonical_rational" "make_char" "make_complex"
     "make_concatenated_stream" "make_dispatch_macro_character"
     "make_duplicate_string" "make_echo_stream"
     #+translator-supports-clos "make_effective_method"
     "make_foreign_pointer" "make_foreign_pointer_internal"
     #+translator-supports-clos "make_generic_function"
     "make_hash_table" #+translator-supports-clos "make_instance"
     "make_list" #+translator-supports-clos "make_next_method_p"
     "make_package" "make_pathname" "make_random_state" "make_ratio"
     "make_sequence" "make_string" "make_string_input_stream"
     "make_string_output_stream" "make_struct_foreign_type"
     #-translator-supports-clos "make_structure"
     "make_structure_class" "make_structure_instance" "make_symbol"
     "make_synonym_stream" "make_two_way_stream" "make_vector" "makunbound"
     "malloc_foreign_pointer" "map" "map_into" "mapc" "mapcan" "mapcar"
     "mapcon" "maphash" "mapl" "maplist" "maptree" "mask_field" "maxn"
     "member" "member_eq" "member_eql" "member_equal" "member_if"
     "member_if_not" "member_odd" "member_se" "memq" "merge"
     "merge_pathnames" "method_combination_error"
     #+translator-supports-clos "method_combination_function"
     #+translator-supports-clos "method_combination_name"
     #+translator-supports-clos "method_combination_options"
     #+translator-supports-clos "method_combination_p"
     "minn" "minus" "minusn" "minusp" "minusr" "mismatch" "mod"
     "multiple_value_list_n" "mumble" "mvsn" "name_char" "namestring"
     "nbutlast" "nconc" "nconc2" "ncons" "ncons1" "negate" "nintersection"
     "ninth" #+translator-supports-clos "no_applicable_method"
     #+translator-supports-clos "no_next_method"
     #+translator-supports-clos "no_primary_method"
     "not" "notany" "notevery" "nreconc" "nreverse" "nset_difference"
     "nset_exclusive_or" "nstring_capitalize" "nstring_downcase"
     "nstring_upcase" "nsublis" "nsubst" "nsubst_if" "nsubst_if_not"
     "nsubstitute" "nsubstitute_if" "nsubstitute_if_not" "nth" "nthcdr"
     "null" "null_or_quoted" "num_eq" "num_eqn" "num_eqr" "num_ge" "num_gen"
     "num_ger" "num_gt" "num_gtn" "num_gtr" "num_le" "num_len" "num_ler"
     "num_lt" "num_ltn" "num_ltr" "num_membern" "num_ne" "num_nen" "num_ner"
     "numberp" "numerator" "nunion" "object_to_cdouble" "oddp"
     "output_stream_p" "package_name" "package_nicknames"
     "package_shadowing_symbols" "package_use_list" "package_used_by_list"
     "packagep" "pairlis" "parse_integer" "parse_namestring" "pathname"
     "pathname_device" "pathname_directory" "pathname_host" "pathname_name"
     "pathname_type" "pathname_version" "pathnamep" "peek_char" "phase"
     "plusp" "position" "position_if" "position_if_not" "pprint" "primep"
     "primes" "prin1" "prin1_to_string" "princ" "princ_to_string" "print"
     "probe_file" "proclaim" "prompt_for_value" "random_state_p" "rassoc"
     "rassoc_if" "rassoc_if_not" "rational" "rationalize" "rationalp"
     "ratiop" "read_byte" "read_char" "read_char_no_hang"
     "read_delimited_list" "read_eof_error" "read_error"
     "read_floating_point" "read_from_string" "read_integer" "read_line"
     "read_preserving_whitespace" "read_rational" "read_syntax_error"
     "read_token_error" "readtablep" "realp" "realpart" "reciprocal"
     #+translator-supports-clos "record_method_combination_function"
     "reduce" #+translator-supports-clos "register_class_status"
     #+translator-supports-clos "reinitialize_instance"
     "rem" "remhash" "remove_duplicates" "remove_if" "remove_if_not"
     "remprop" "rename_file" "rename_package" "replace" "rest"
     "restore_frontier" "revappend" "reverse" "room" "row_major_aref"
     "rplaca" "rplacd" "s1" "s2" "scale_float" "schar" "search" "second"
     "select_sleep" "sequence_type_p" "sequencep" "set" "set_aref0"
     "set_aref1" "set_aref2" "set_aref3" "set_aref4" "set_aref5" "set_aref6"
     "set_aref7" "set_caaaar" "set_caaadr" "set_caaar" "set_caadar"
     "set_caaddr" "set_caadr" "set_caar" "set_cadaar" "set_cadadr"
     "set_cadar" "set_caddar" "set_cadddr" "set_caddr" "set_cadr" "set_car"
     "set_cdaaar" "set_cdaadr" "set_cdaar" "set_cdadar" "set_cdaddr"
     "set_cdadr" "set_cdar" "set_cddaar" "set_cddadr" "set_cddar"
     "set_cdddar" "set_cddddr" "set_cdddr" "set_cddr" "set_cdr" "set_char"
     "set_char_bit" #+translator-supports-clos "set_class_status_p"
     "set_difference" "set_dispatch_macro_character" "set_eighth" "set_elt"
     "set_exclusive_or" "set_fdefinition" "set_fifth" "set_fill_pointer"
     "set_first" "set_foreign_aref" "set_foreign_pointer_address"
     "set_foreign_pointer_type" "set_foreign_string_value"
     "set_foreign_value" "set_fourth" "set_get" "set_getf" "set_gethash"
     "set_macro_character" "set_macro_function" "set_nicknames" "set_ninth"
     "set_nth" "set_package" "set_rest" "set_row_major_aref" "set_schar"
     "set_second" "set_setf_function" "set_seventh" "set_shadowing_symbols"
     "set_sixth" #+translator-supports-clos "set_slot_value"
     #+translator-supports-clos "set_standard_object_ref"
     "set_subseq" "set_subseq1" "set_subseq2" "set_svref"
     "set_symbol_function" "set_symbol_plist" "set_syntax_from_char"
     "set_tenth" "set_third" "set_typed_foreign_aref" "set_use_list"
     "set_used_by_list" "setf_char_bit" "setf_fill_pointer" "setf_function"
     "sethash" "seventh" #+translator-supports-clos "shared_initialize"
     "short_site_name" "signum" "simple_array_p" "simple_bit_vector_p"
     "simple_string_p" "simple_vector_p" "sixth"
     #+translator-supports-clos "slot_boundp"
     #+translator-supports-clos "slot_exists_p"
     #+translator-supports-clos "slot_makunbound"
     #+translator-supports-clos "slot_value"
     "software_version" "some" "sort"
     #+translator-supports-clos "sort_parsed_methods"
     "splitfile" "stable_sort" "standard_char_p" "standard_object_p"
     #+translator-supports-clos "standard_object_ref"
     "stationary_object_p" "stream_element_type" "streamp" "string"
     "string_append2" "string_appendn" "string_appendr" "string_capitalize"
     "string_char_p" "string_downcase" "string_eq" "string_equal" "string_ge"
     "string_greaterp" "string_gt" "string_input_stream_p" "string_le"
     "string_left_trim" "string_lessp" "string_lt" "string_ne"
     "string_not_equal" "string_not_greaterp" "string_not_lessp"
     "string_output_stream_p" "string_right_trim" "string_stream_index"
     "string_stream_p" "string_trim" "string_upcase" "stringp" "strlwr"
     "structure_object_p" "strupr" "sub1" "sublis" "subseq" "subsetp" "subst"
     "subst_if" "subst_if_not" "substitute" "substitute_if"
     "substitute_if_not" "subtypep" "svref" "sxhash" "symbol_function"
     "symbol_name" "symbol_package" "symbol_plist" "symbol_value" "symbolp"
     "synonym_stream_p" "tailp" "tenth" "terpri" "third" "timesn" "timesr"
     "total_memory_allocatable" "total_memory_used" "tree_equal" "truename"
     "two_way_stream_p" "type_of" "typed_foreign_aref" "typep" "u"
     "undefine_foreign_type" "unintern" "unread_char"
     "unsigned_long_to_bignum"
     #+translator-supports-clos "update_effective_method"
     #+translator-supports-clos "update_initial_methods"
     #+translator-supports-clos "update_instance_for_different_class"
     "upgraded_array_element_type" "upper_case_p" "use_package"
     "user_homedir_pathname" "usersyms" "values" "values_list" "vector"
     "vector_pop" "vector_push" "vector_push_extend" "vectorp" "warn" "warnn"
     "whitespace_char_p" "write_byte" "write_char" "write_line"
     "write_string" "write_to_string" "xbignum_normalize"
     "xmake_canonical_rational" "xor" "y_or_n_p" "y_or_n_pn" "yes_or_no_p"
     "yes_or_no_pn" "zerop")
    #+translator-supports-thread
    ("thread"
     ;; public interface
     "all_threads" "atomic_decf" "atomic_decf_" "atomic_delete" "atomic_flush"
     "atomic_incf" "atomic_incf_" "atomic_pop" "atomic_push" "atomic_pushnew"
     "spawn_thread" "kill_thread" "thread_name" "SETF_thread_name" "current_thread"
     "make_lock" "LOCK" "TRYLOCK" "UNLOCK"
     "make_condition_variable" "thread_yield"
     "condition_variable_wait" "condition_variable_wait_with_timeout"
     "condition_variable_signal" "condition_variable_broadcast"
     ;; internal functions
     "SI_internal_make_thread" "SI_internal_spawn_thread" "SI_thread_init"
     "SI_internal_make_lock" "SI_lock" "SI_trylock" "SI_unlock"
     "SI_internal_make_condition_variable"
     ;; macros for special object types
     "SI_THREADP" "SI_TAG_THREAD" "SI_THREAD_NAME" "SI_THREAD_ID" "SI_THREAD_STUFF"
     "SI_LOCKP" "SI_TAG_LOCK" "SI_LOCK_NAME" "SI_LOCK_MUTEX" "SI_LOCK_STUFF"
     "SI_CONDP" "SI_TAG_COND" "SI_COND_LOCK" "SI_COND_SIGNAL"
     "SI_COND_BROADCAST" "SI_COND_STUFF" "SI_COND_SEM" "SI_COND_COUNT"
     "SYMBOL_VALUE_IN_THREAD" "SET_SYMBOL_VALUE_IN_THREAD"
     ;; macros for special variable support, binghe, 2009/5/13
     "DEFINE_VARIABLE" "DECLARE_VARIABLE" "SPECIAL_VALUE" "STATIC_VALUE"
     "SPECIAL_QUOTED_VALUE"
     )))

(defun reserve-initial-c-names ()
  (when *reserved-c-names-lists*
    (set-c-reserved-names *reserved-c-names-lists*)
    (setq *reserved-c-names-lists* nil))
  (when *global-c-names-lists*
    (maybe-add-c-global-names *global-c-names-lists*)
    (setq *global-c-names-lists* nil)))

(defun add-c-reserved-names (alist)
  (dolist (source+list alist nil)
    (mapc #'add-c-reserved-name (cdr source+list))))

(defun add-c-global-names (alist)
  (dolist (source+list alist nil)
    (mapc #'record-global-c-name (cdr source+list))))

(defun set-c-reserved-names (alist)
  (clrhash (cdar (get-c-name-tables :reserved)))
  (add-c-reserved-names alist))

(defvar *c-name-string-table*
  (make-hash-table :test 'equal
		   :size 5000
		   :rehash-size 2.0))

#+(or lucid genera)
(defvar static-c-names-p t)

(defmacro intern-c-name (name)
  `(let ((name ,name))
     (or (gethash name *c-name-string-table*)
	 (progn
	   #+(or lucid genera)
	   (when static-c-names-p
	     (setq name (with-static-area (copy-seq name))))
	   (setf (gethash name *c-name-string-table*) name)))))

(defun maybe-add-c-global-names (alist)
  (let* ((globalp ':global)
	 (c-names (get-c-name-tables globalp))
	 (table (cdar c-names)))
    (dolist (source+list alist nil)
      (dolist (c-name (cdr source+list))
	(let ((c-names c-names)
	      (c-name (intern-c-name c-name)))
	  (loop (unless c-names
		  (setf (gethash c-name table) 1)
		  (return nil))
		(let ((table (cdr (pop c-names))))
		  (when (gethash c-name table)
		    (return nil)))))))))

(defun RECORD-C-NAME (name &optional type (value 1))
  (let ((table (cdar (get-c-name-tables type))))
    (setf (gethash (intern-c-name name) table) value)))

(defun C-NAME-CONFLICT-P (c-name globalp)
  (let ((c-names (get-c-name-tables globalp))
	(c-name (intern-c-name c-name)))
    (loop (unless c-names (return nil))
	  (let* ((table (cdr (pop c-names)))
		 (conflict-resolution-integer (gethash c-name table)))
	    (when conflict-resolution-integer
	      (return conflict-resolution-integer))))))

(defun add-c-reserved-name (name)
  (record-c-name name ':reserved))

; Not called anywhere.
(defun record-local-c-name (name)
  (record-c-name name))

;;; RECORD-GLOBAL-C-NAME (external)
;;;
;;; Adds the string C-name to the set of global C identifiers.
;;; This is mostly external so it can be used to initialize the database.
(defun record-global-c-name (name)
  (record-c-name name ':global))

(defparameter *c-reserved-keyword-names*
  '("auto" "break" "case" "char" "const" "continue" "default" "do" "double"
    "else" "enum" "extern" "float" "for" "goto" "if" "int" "long" "SI_Long" "register"
    "return" "short" "signed" "sizeof" "static" "struct" "switch" "typedef"
    "union" "unsigned" "void" "volatile" "while" "fortran" "asm"))

(mapc #'add-c-reserved-name *c-reserved-keyword-names*)

;;; *** I believe that ANSI C also reserves names beginning with certain
;;; *** prefixes (for example, names like "is*").  We need to figure out
;;; *** what these are and how to handle them.  I believe we also want to
;;; *** handle prefixes anyway since many libraries that might be linked
;;; *** with an application reserve their own prefixes.

  
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Case canonicalization
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; STRING-CANONICALIZE-CASE string &key start end		[Function]
;;;  This function returns a string just like String with the case of the
;;;  characters determined according to the rules for case canonicalization.
;;;  More precisely, 
;;;
;;;  * If the string contains all uppercase characters (the customary case for
;;;    Lisp), the resulting string will contain all lowercase characters (the
;;;    customary case for C).
;;;
;;;  * If the string contains all lowercase characters (the opposite of the
;;;    customary case for Lisp), the resulting string will contain all
;;;    uppercase characters (the opposite of the customary case for C).
;;;
;;;  * If the string contains both uppercase and lowercase characters, the
;;;    resulting string will contain the same characters as the argument string
;;;    (mixed case represents itself).
;;;
;;;  The keyword arguments :START and :END delimit the portion of the string to
;;;  be affected.  The result is always the same length as the string, however.
;;;
;;;  The argument is not destroyed.  However, if no characters in the argument
;;;  require conversion, the result may be either the argument or a copy of it,
;;;  at the implementation's discretion.
;;;
;;;  A second value is returned to indicate which of the three canonicalization
;;;  rules was applied to produce the result string.  The possible values and
;;;  their meanings are
;;;
;;;   :UPCASE	All lowercase characters were converted to uppercase.
;;;   :DOWNCASE	All uppercase characters were converted to lowercase.
;;;   :PRESERVE	No case conversion was necessary.

(defun string-canonicalize-case (string &key (start 0) end)
  (setf string (translator-string string))
  (when (null end) (setf end (length string)))
  (do ((index start (1+ index)))
      ((<= end index) (values string :downcase))
    (let ((char (char string index)))
      (when (both-case-p char)
	(return
	  (if (upper-case-p char)
	      (if (find-if #'(lambda (char)
			       (and (both-case-p char)
				    (lower-case-p char)))
			   string :start (1+ index) :end end)
		  (values string :preserve)
		  (values (string-downcase string :start start :end end)
			  :downcase))
	      (if (find-if #'(lambda (char)
			       (and (both-case-p char)
				    (upper-case-p char)))
			   string :start (1+ index) :end end)
		  (values string :preserve)
		  (values (string-upcase string :start start :end end)
			  :upcase))))))))

;;; STRING-TRIM-STARS string                                [Function]
;;;  This function returns a string which is the same as the argument string
;;;  except that the outermost pair of star (*) characters (when present) have
;;;  been removed.

(defun string-trim-stars (string)
  (setf string (translator-string string))
  (let ((last (1- (length string))))
    (if (or (< last 2)
	    (not (eql (char string 0) #\*))
	    (not (eql (char string last) #\*)))
	string
	(subseq string 1 last))))


;;; TRANSLATOR-SYMBOL-NAME

;;; This function, and the associated SETF method, are part of
;;; the external interface to the Translator.  This function is
;;; used to "force" the name mapper to use a specified string,
;;; rather than its real symbol name, as the starting point for
;;; generating a C identifier from a symbol.

;;; TRANSLATOR-STRING

;;; This function is analogous to the Lisp function STRING, but
;;; calls TRANSLATOR-SYMBOL-NAME rather than SYMBOL-NAME if its
;;; argument is a symbol.

(defvar *translator-symbol-names* (make-hash-table :test #'eq
						   :rehash-size 2.0))

(defvar using-translator-symbol-names-p nil)

(defmacro translator-symbol-name1 (symbol)
  `(or (and using-translator-symbol-names-p
	    (gethash ,symbol *translator-symbol-names*))
       (symbol-name ,symbol)))

(defun translator-symbol-name (symbol)
  (translator-symbol-name1 symbol))

(defsetf translator-symbol-name (symbol) (string)
  `(progn
     (setq using-translator-symbol-names-p t)
     (setf (gethash ,symbol *translator-symbol-names*) ,string)))

(defun translator-string (string)
  (if (symbolp string)
      (translator-symbol-name1 string)
      (string string)))

;;; Manually generated from rtl/c/special.h, must be maintained when special.h changes,
;;; TIMPL::ADD-SYMBOL-CONSTRUCTOR will use this table for special variable generating.
;;; -- binghe, 2009/5/11

#+translator-supports-thread
(defparameter *special-variable-names*
  '("Current_print_level"
    "Debug_io"
    "Error_output"
    "Load_pathname"
    "Load_print"
    "Load_truename"
    "Load_verbose"
    "Package"
    "Print_array"
    "Print_base"
    "Print_case"
    "Print_circle"
    "Print_escape"
    "Print_gensym"
    "Print_length"
    "Print_level"
    "Print_lines"
    "Print_miser_width"
    "Print_pprint_dispatch"
    "Print_pretty"
    "Print_radix"
    "Print_readably"
    "Print_right_margin"
    "Read_base"
    "Read_default_float_format"
    "SI_Format_stream"
    "Standard_input"
    "Standard_output"
    "Terminal_io"))

#+translator-supports-thread
(defparameter *ignored-special-variables*
  '("Gensym_error_message_buffer"))
