;;; -*- Mode: Lisp; Package: HOST; Syntax: Common-Lisp -*-
;;;
;;; array-symbols.lisp -- additional symbols that exist in the run-time system
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/array-symbols.lisp,v $"
 "$Revision: 1.4 $"
 "$Date: 2007/06/26 19:48:36 $")


(himpl:define-symbols :host t

("ADJUST-ARRAY"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (array new-dimensions
			    &key element-type initial-element initial-contents
			         fill-pointer displaced-to
				 displaced-index-offset)
	:return-type array
	)
    )

("ADJUSTABLE-ARRAY-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (array)
	:return-type t
	:transforms ((trun:%adjustable-array-p t))
	)
    )

("AREF"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (array &rest subscripts)
	:return-type t
	:argument-types (array &rest fixnum)
	)
    (:setf-function
        :lambda-list (new-value array &rest subscripts)
	:return-type t
	)
    (:setf-place
        :setf-function t
	)
    )

("ARRAY"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    (:type-specifier-list)
    )

("ARRAY-DIMENSION"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
	:nonconsing t
        :lambda-list (array axis-number)
	:return-type fixnum
	:argument-types (array fixnum)
	)
    )

("ARRAY-DIMENSION-LIMIT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value most-positive-fixnum
	)
    )

("ARRAY-DIMENSIONS"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (array)
	:argument-types (array)
	:return-type cons
	)
    )

("ARRAY-DISPLACEMENT"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (array)
	:argument-types (array)
	:return-type (values (or array null) fixnum)
	)
    )

("ARRAY-ELEMENT-TYPE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :nonconsing t
        :lambda-list (array)
	:argument-types (array)
	:return-type t
	)
    )

("%PRIMITIVE-VECTOR-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "SIMPLE_ARRAY_ANY_1_P"
        :lambda-list (object)
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%PRIMITIVE-VECTOR-LENGTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "SIMPLE_ARRAY_ANY_1_LENGTH"
        :lambda-list (object)
	:argument-types ((simple-array * (*)))
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("ARRAY-HAS-FILL-POINTER-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (array)
	:argument-types (array)
	:return-type t
	:transforms ((trun:%array-has-fill-pointer-p t))
	)
    )

("ARRAY-IN-BOUNDS-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (array &rest subscripts)
	:argument-types (array)
	:return-type t
	)
    )

("ARRAY-RANK"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (array)
	:argument-types (array)
	:return-type fixnum
	:transforms ((trun:%array-rank t))
	)
    )

("ARRAY-RANK-LIMIT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value most-positive-fixnum
	)
    )

("ARRAY-ROW-MAJOR-INDEX"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (array &rest subscripts)
	:argument-types (array &rest fixnum)
	:return-type fixnum
	)
    )

("ARRAY-TOTAL-SIZE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (array)
	:argument-types (array)
	:return-type fixnum
	;; :transforms ((trun:%array-total-size t))
	)
    )

("ARRAY-TOTAL-SIZE-LIMIT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value most-positive-fixnum
	)
    )

("ARRAYP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
	:argument-types (t)
	:return-type t
	:transforms ((trun:%arrayp t))
	)
    )

("CHAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (string index)
        :return-type character
	:entry-name "lchar"
	:transforms ((trun:%char :no-longs)
		     (trun:%ichar t))
	)
    (:setf-place)
    )

("FILL-POINTER"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (vector)
	:return-type fixnum
	:transforms ((trun:%fill-pointer t))
	)
    (:setf-place)
    )

("%FILL-POINTER"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "FILL_POINTER"
	:lambda-list (vector)
	:return-type fixnum
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SET-FILL-POINTER"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "SET_FILL_POINTER"
        :lambda-list (vector new-value)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("SET-FILL-POINTER"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (vector new-length)
	:return-type fixnum
        ;; :unsupported t
	:transforms ((trun:%set-fill-pointer t))
	)
    )

("MAKE-ARRAY"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (dimensions &key element-type initial-element
				 initial-contents adjustable fill-pointer
				 displaced-to displaced-index-offset)
	:return-type array
	)
    )

;;; CLtL2 specifies a new keyword argument, ELEMENT-TYPE, for
;;; the MAKE-STRING function; this is currently not supported

("MAKE-STRING"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (size &key initial-element element-type)
        :return-type simple-string
	)
    )

("ROW-MAJOR-AREF"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (array index)
	:return-type t
	:transforms ((trun:%row-major-aref t))
        )
    (:setf-place)
    )

("%ROW-MAJOR-AREF"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "ROW_MAJOR_AREF"
	:lambda-list (array index)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("SBIT"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (bit-array &rest subscripts)
        :return-type bit
	)
    (:setf-function
        :lambda-list (new-bit bit-array &rest subscripts)
	:return-type bit
	)
   (:setf-place
        :setf-function t
	)
    )


("SCHAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (string index)
	:return-type character
	:transforms ((trun:%schar :no-longs)
		     (trun:%ischar t))
	)
    (:setf-place)
    )

("%STATIC-ARRAY"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STATIC_ARRAY"
        :lambda-list (type n &rest dimensions)
	:return-type array
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:int nil))
	:foreign-return-type :object
	)
    )

("SVREF"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (simple-vector index)
	:return-type t
	:transforms ((trun:%svref :no-longs)
		     (trun:%isvref t))
	)
    (:setf-place)
    )


("VECTOR"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:function
        :state-changing nil
        :lambda-list (&rest objects)
        :return-type simple-vector
	)
    (:type-name)
    (:type-specifier-list)
    )

("VECTOR-POP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (vector)
        :return-type t
	)
    )

("VECTOR-PUSH"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (new-element vector)
        :return-type (or null fixnum)
	)
    )

("VECTOR-PUSH-EXTEND"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (new-element vector &optional extension)
        :return-type (or null fixnum)
	)
    )

("VECTORP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%vectorp t))
	)
    )

("%VECTORP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "VECTORP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )


;;; These are all foreign entry points for functions in the common-lisp
;;; package.

("%ADJUSTABLE-ARRAY-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "ADJUSTABLE_ARRAY_P"
        :lambda-list (object)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )


("%ARRAY-HAS-FILL-POINTER-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "ARRAY_HAS_FILL_POINTER_P"
        :lambda-list (object)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("%ARRAY-RANK"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "ARRAY_RANK"
        :lambda-list (array)
	:argument-types (array)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("%ARRAY-TOTAL-SIZE"
    (:symbol
        :package "TRUN"
        :import-from nil
        :exists-at-runtime nil
        )
    (:function
        ;; Not currently implemented in runtime.  jar 4/29/91
        :unsupported t
        :entry-name "ARRAY_TOTAL_SIZE"
        :lambda-list (array)
        :return-type fixnum
        :foreign-protocol :macro
        :foreign-arguments ((:object nil))
        :foreign-return-type :object
        )
    )

("%ARRAYP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "ARRAYP"
        :lambda-list (object)
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )


("%BIT-VECTOR-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "BIT_VECTOR_P"
        :lambda-list (object)
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%ICHAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "ICHAR"
        :lambda-list (string index)
	:return-type character
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:fixnum nil))
	:foreign-return-type :char
	)
    )

("%ISCHAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "ISCHAR"
        :lambda-list (string index)
	:return-type character
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:fixnum nil))
	:foreign-return-type :char
	)
    )

("%SIMPLE-BIT-VECTOR-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SIMPLE_BIT_VECTOR_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%SCHAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "SCHAR"
        :lambda-list (string index)
	:return-type character
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )



("%SIMPLE-STRING-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "SIMPLE_STRING_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%SIMPLE-VECTOR-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "SIMPLE_VECTOR_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )


("%SVREF"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "SVREF"
        :lambda-list (simple-vector index)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )


("%ISVREF"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "ISVREF"
        :lambda-list (simple-vector index)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil) (:fixnum nil))
	:foreign-return-type :object
	)
    )

("%SET-CHAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:nonconsing t
        :entry-name "SET_CHAR"
	:lambda-list (string index new-character)
	:return-type character
	:foreign-protocol :macro
	:transforms ((trun:%set-ichar :some-longs))
	:foreign-arguments ((:object nil) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%SET-ICHAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:nonconsing t
        :entry-name "SET_ICHAR"
	:lambda-list (string index new-character)
	:return-type character
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:fixnum nil) (:char nil))
	:foreign-return-type :char
	)
    )

("%SET-ISCHAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:nonconsing t
        :entry-name "SET_ISCHAR"
	:lambda-list (string index new-character)
	:return-type character
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:fixnum nil) (:char nil))
	:foreign-return-type :char
	)
    )

("%SET-ISVREF"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:nonconsing t
        :lambda-list (simple-vector index new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%isvref
	:foreign-arguments ((:object nil) (:fixnum nil) (:object nil))
	:foreign-return-type :object
        )
    )


("%SET-SCHAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:nonconsing t
        :entry-name "SET_SCHAR"
	:lambda-list (string index new-character)
	:return-type character
	:foreign-protocol :macro
	:transforms ((trun:%set-ischar :some-longs))
	:foreign-arguments ((:object nil) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("SET-SCHAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (string index new-character)
	:return-type character
        ;; :unsupported t
	:transforms ((trun:%set-schar t))
	)
    )

("%SET-SVREF"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:nonconsing t
        :lambda-list (simple-vector index new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%svref
	:transforms ((trun:%set-isvref :some-longs))
	:foreign-arguments ((:object nil) (:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("SET-SVREF"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (simple-vector index new-value)
	:return-type t
	:unsupported t
	)
    )


;;; Specialized array accessors and setters

("%AREF-0"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :lambda-list (array)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:entry-name "aref0"
	)
    )

("%AREF-1"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :lambda-list (array index)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:entry-name "aref1"
	)
    )

("%AREF-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (array index0 index1)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:entry-name "aref2"
	)
    )

("%AREF-3"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (array index0 index1 index2)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:entry-name "aref3"
	)
    )

("%AREF-4"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (array index0 index1 index2 index3)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:entry-name "aref4"
	)
    )

("%AREF-5"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (array index0 index1 index2 index3 index4)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:entry-name "aref5"
	)
    )

("%AREF-6"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (array index0 index1 index2 index3 index4 index5)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:entry-name "aref6"
	)
    )

("%AREF-7"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (array index0 index1 index2 index3 index4 index5 index6)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:entry-name "aref7"
	)
    )

("%SET-AREF-0"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (array new-value)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_aref0"
	)
    )


("%SET-AREF-1"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (array index new-value)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_aref1"
	)
    )

("%SET-AREF-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (array index0 index1 new-value)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_aref2"
	)
    )

("%SET-AREF-3"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (array index0 index1 index2 new-value)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_aref3"
	)
    )

("%SET-AREF-4"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (array index0 index1 index2 index3 new-value)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_aref4"
	)
    )

("%SET-AREF-5"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (array index0 index1 index2 index3 index4 new-value)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_aref5"
	)
    )

("%SET-AREF-6"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (array index0 index1 index2 index3 index4 index5 
			    new-value)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_aref6"
	)
    )

("%SET-AREF-7"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (array index0 index1 index2 index3 index4 index5 index6
			    new-value)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_aref7"
	)
    )

("%BIT-0"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "bit0"
	)
    )

("%BIT-1"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (bit-array index)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "bit1"
	)
    )

("%BIT-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (bit-array index0 index1)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "bit2"
	)
    )

("%BIT-3"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (bit-array index0 index1 index2)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "bit3"
	)
    )

("%BIT-4"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (bit-array index0 index1 index2 index3)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "bit4"
	)
    )

("%BIT-5"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (bit-array index0 index1 index2 index3 index4)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "bit5"
	)
    )

("%BIT-6"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (bit-array index0 index1 index2 index3 index4 index5)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "bit6"
	)
    )

("%BIT-7"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (bit-array index0 index1 index2 index3 index4 index5
				index6)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "bit7"
	)
    )

("%SET-BIT-0"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array new-value)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_bit0"
	)
    )

("%SET-BIT-1"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array index new-value)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_bit1"
	)
    )

("%SET-BIT-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array index0 index1 new-value)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_bit2"
	)
    )

("%SET-BIT-3"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array index0 index1 index2 new-value)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_bit3"
	)
    )

("%SET-BIT-4"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array index0 index1 index2 index3 new-value)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_bit4"
	)
    )

("%SET-BIT-5"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array index0 index1 index2 index3 index4 new-value)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_bit5"
	)
    )

("%SET-BIT-6"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array index0 index1 index2 index3 index4 index5 
			    new-value)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_bit6"
	)
    )

("%SET-BIT-7"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array index0 index1 index2 index3 index4 index5
				index6 new-value)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_bit7"
	)
    )

("%DFLOAT-SAREF-0"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DFLOAT_SAREF_0"
	:lambda-list (array)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%DFLOAT-SAREF-1"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DFLOAT_SAREF_1"
	:lambda-list (array index)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%DFLOAT-SAREF-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DFLOAT_SAREF_2"
	:lambda-list (array index0 index1)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%DFLOAT-SAREF-3"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DFLOAT_SAREF_3"
	:lambda-list (array index0 index1 index2)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil))
	:foreign-return-type :object
	)
    )

("%DFLOAT-SAREF-4"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DFLOAT_SAREF_4"
	:lambda-list (array index0 index1 index2 index3)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%DFLOAT-SAREF-5"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DFLOAT_SAREF_5"
	:lambda-list (array index0 index1 index2 index3 index4)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%DFLOAT-SAREF-6"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DFLOAT_SAREF_6"
	:lambda-list (array index0 index1 index2 index3 index4 index5)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil))
	:foreign-return-type :object
	)
    )

("%DFLOAT-SAREF-7"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DFLOAT_SAREF_7"
	:lambda-list (array index0 index1 index2 index3 index4 index5 index6)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%DFLOAT-SASET-0"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DFLOAT_SASET_0"
	:lambda-list (array new-value)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%DFLOAT-SASET-1"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DFLOAT_SASET_1"
	:lambda-list (array index new-value)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%DFLOAT-SASET-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DFLOAT_SASET_2"
	:lambda-list (array index0 index1 new-value)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object t))
	:foreign-return-type :object
	)
    )

("%DFLOAT-SASET-3"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DFLOAT_SASET_3"
	:lambda-list (array index0 index1 index2 new-value)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%DFLOAT-SASET-4"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DFLOAT_SASET_4"
	:lambda-list (array index0 index1 index2 index3 new-value)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%DFLOAT-SASET-5"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DFLOAT_SASET_5"
	:lambda-list (array index0 index1 index2 index3 index4 new-value)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object t))
	:foreign-return-type :object
	)
    )

("%DFLOAT-SASET-6"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DFLOAT_SASET_6"
	:lambda-list (array index0 index1 index2 index3 index4 index5
			    new-value)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%DFLOAT-SASET-7"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DFLOAT_SASET_7"
	:lambda-list (array index0 index1 index2 index3 index4 index5 index6
			    new-value)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%SBIT-0"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SBIT0"
	:lambda-list (bit-array)
	:return-type bit
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SBIT-1"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "SBIT1"
	:lambda-list (bit-array index)
	:return-type bit
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object t))
	:foreign-return-type :object
	:transforms ((trun:%sbitp-1 t))
	)
    )

("%SBITP-1"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SBITP_1"
	:lambda-list (bit-array index)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object t))
	:foreign-return-type :boolean
	)
    )

("%SBIT-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "SBIT2"
	:lambda-list (bit-array index0 index1)
	:return-type bit
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object t) (:object t))
	:foreign-return-type :object
	)
    )

("%SBIT-3"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "SBIT3"
	:lambda-list (bit-array index0 index1 index2)
	:return-type bit
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object t) (:object t) (:object t))
	:foreign-return-type :object
	)
    )

("%SBIT-4"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "SBIT4"
	:lambda-list (bit-array index0 index1 index2 index3)
	:return-type bit
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object t) (:object t)
			    (:object t) (:object t))
	:foreign-return-type :object
	)
    )

("%SBIT-5"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "SBIT5"
	:lambda-list (bit-array index0 index1 index2 index3 index4)
	:return-type bit
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object t) (:object t)
			    (:object t) (:object t) (:object t))
	:foreign-return-type :object
	)
    )

("%SBIT-6"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "SBIT6"
	:lambda-list (bit-array index0 index1 index2 index3 index4 index5)
	:return-type bit
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object t) (:object t)
			    (:object t) (:object t) (:object t) (:object t))
	:foreign-return-type :object
	)
    )

("%SBIT-7"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "SBIT7"
	:lambda-list (bit-array index0 index1 index2 index3 index4 index5
				index6)
	:return-type bit
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object t) (:object t)
			    (:object t) (:object t) (:object t) (:object t)
			    (:object t))
	:foreign-return-type :object
	)
    )

("%SET-SBIT-0"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SET_SBIT0"
        :lambda-list (bit-array new-bit)
	:return-type bit
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("%SET-SBIT-1"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SET_SBIT1"
        :lambda-list (bit-array index new-bit)
	:return-type bit
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object t))
	:foreign-return-type :object
	)
    )

("%SET-SBIT-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SET_SBIT2"
        :lambda-list (bit-array index0 index1 new-bit)
	:return-type bit
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object t) (:object t))
	:foreign-return-type :object
	)
    )

("%SET-SBIT-3"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SET_SBIT3"
        :lambda-list (bit-array index0 index1 index2 new-bit)
	:return-type bit
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object t) (:object t)
			    (:object t))
	:foreign-return-type :object
	)
    )

("%SET-SBIT-4"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SET_SBIT4"
        :lambda-list (bit-array index0 index1 index2 index3 new-bit)
	:return-type bit
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object t) (:object t)
			    (:object t) (:object t))
	:foreign-return-type :object
	)
    )

("%SET-SBIT-5"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SET_SBIT5"
        :lambda-list (bit-array index0 index1 index2 index3 index4 new-bit)
	:return-type bit
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object t) (:object t)
			    (:object t) (:object t) (:object t))
	:foreign-return-type :object
	)
    )

("%SET-SBIT-6"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SET_SBIT6"
        :lambda-list (bit-array index0 index1 index2 index3 index4 index5
				new-bit)
	:return-type bit
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object t) (:object t)
			    (:object t) (:object t) (:object t) (:object t))
	:foreign-return-type :object
	)
    )

("%SET-SBIT-7"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SET_SBIT7"
        :lambda-list (bit-array index0 index1 index2 index3 index4 index5
				index6 new-bit)
	:return-type bit
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object t) (:object t)
			    (:object t) (:object t) (:object t) (:object t)
			    (:object t))
	:foreign-return-type :object
	)
    )


("%UBYTE-8-SAREF-0"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_8_SAREF_0"
	:lambda-list (array)
	:return-type (unsigned-byte 8)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-8-SAREF-1"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_8_SAREF_1"
	:lambda-list (array index)
	:return-type (unsigned-byte 8)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-8-SAREF-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_8_SAREF_2"
	:lambda-list (array index0 index1)
	:return-type (unsigned-byte 8)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-8-SAREF-3"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_8_SAREF_3"
	:lambda-list (array index0 index1 index2)
	:return-type (unsigned-byte 8)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-8-SAREF-4"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_8_SAREF_4"
	:lambda-list (array index0 index1 index2 index3)
	:return-type (unsigned-byte 8)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-8-SAREF-5"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_8_SAREF_5"
	:lambda-list (array index0 index1 index2 index3 index4)
	:return-type (unsigned-byte 8)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-8-SAREF-6"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_8_SAREF_6"
	:lambda-list (array index0 index1 index2 index3 index4 index5)
	:return-type (unsigned-byte 8)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-8-SAREF-7"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_8_SAREF_7"
	:lambda-list (array index0 index1 index2 index3 index4 index5 index6)
	:return-type (unsigned-byte 8)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-8-SASET-0"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_8_SASET_0"
	:lambda-list (array new-value)
	:return-type (unsigned-byte 8)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-8-SASET-1"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_8_SASET_1"
	:lambda-list (array index new-value)
	:return-type (unsigned-byte 8)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-8-SASET-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_8_SASET_2"
	:lambda-list (array index0 index1 new-value)
	:return-type (unsigned-byte 8)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-8-SASET-3"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_8_SASET_3"
	:lambda-list (array index0 index1 index2 new-value)
	:return-type (unsigned-byte 8)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-8-SASET-4"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_8_SASET_4"
	:lambda-list (array index0 index1 index2 index3 new-value)
	:return-type (unsigned-byte 8)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-8-SASET-5"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_8_SASET_5"
	:lambda-list (array index0 index1 index2 index3 index4 new-value)
	:return-type (unsigned-byte 8)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-8-SASET-6"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_8_SASET_6"
	:lambda-list (array index0 index1 index2 index3 index4 index5
			    new-value)
	:return-type (unsigned-byte 8)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-8-SASET-7"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_8_SASET_7"
	:lambda-list (array index0 index1 index2 index3 index4 index5
			    index6 new-value)
	:return-type (unsigned-byte 8)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-16-SAREF-0"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_16_SAREF_0"
	:lambda-list (array)
	:return-type (unsigned-byte 16)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-16-SAREF-1"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_16_SAREF_1"
	:lambda-list (array index)
	:return-type (unsigned-byte 16)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-16-SAREF-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_16_SAREF_2"
	:lambda-list (array index0 index1)
	:return-type (unsigned-byte 16)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-16-SAREF-3"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_16_SAREF_3"
	:lambda-list (array index0 index1 index2)
	:return-type (unsigned-byte 16)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-16-SAREF-4"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_16_SAREF_4"
	:lambda-list (array index0 index1 index2 index3)
	:return-type (unsigned-byte 16)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-16-SAREF-5"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_16_SAREF_5"
	:lambda-list (array index0 index1 index2 index3 index4)
	:return-type (unsigned-byte 16)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-16-SAREF-6"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_16_SAREF_6"
	:lambda-list (array index0 index1 index2 index3 index4 index5)
	:return-type (unsigned-byte 16)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-16-SAREF-7"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_16_SAREF_7"
	:lambda-list (array index0 index1 index2 index3 index4 index5 index6)
	:return-type (unsigned-byte 16)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-16-SASET-0"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_16_SASET_0"
	:lambda-list (array new-value)
	:return-type (unsigned-byte 16)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-16-SASET-1"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_16_SASET_1"
	:lambda-list (array index new-value)
	:return-type (unsigned-byte 16)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-16-SASET-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_16_SASET_2"
	:lambda-list (array index0 index1 new-value)
	:return-type (unsigned-byte 16)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-16-SASET-3"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_16_SASET_3"
	:lambda-list (array index0 index1 index2 new-value)
	:return-type (unsigned-byte 16)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-16-SASET-4"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_16_SASET_4"
	:lambda-list (array index0 index1 index2 index3 new-value)
	:return-type (unsigned-byte 16)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-16-SASET-5"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_16_SASET_5"
	:lambda-list (array index0 index1 index2 index3 index4 new-value)
	:return-type (unsigned-byte 16)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-16-SASET-6"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_16_SASET_6"
	:lambda-list (array index0 index1 index2 index3 index4 index5
			    new-value)
	:return-type (unsigned-byte 16)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-16-SASET-7"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_16_SASET_7"
	:lambda-list (array index0 index1 index2 index3 index4 index5 index6
			    new-value)
	:return-type (unsigned-byte 16)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-32-SAREF-0"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_32_SAREF_0"
	:lambda-list (array)
	:return-type (unsigned-byte 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-32-SAREF-1"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_32_SAREF_1"
	:lambda-list (array index)
	:return-type (unsigned-byte 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-32-SAREF-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_32_SAREF_2"
	:lambda-list (array index0 index1)
	:return-type (unsigned-byte 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-32-SAREF-3"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_32_SAREF_3"
	:lambda-list (array index0 index1 index2)
	:return-type (unsigned-byte 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-32-SAREF-4"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_32_SAREF_4"
	:lambda-list (array index0 index1 index2 index3)
	:return-type (unsigned-byte 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-32-SAREF-5"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_32_SAREF_5"
	:lambda-list (array index0 index1 index2 index3 index4)
	:return-type (unsigned-byte 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-32-SAREF-6"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_32_SAREF_6"
	:lambda-list (array index0 index1 index2 index3 index4 index5)
	:return-type (unsigned-byte 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-32-SAREF-7"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_32_SAREF_7"
	:lambda-list (array index0 index1 index2 index3 index4 index5 index6)
	:return-type (unsigned-byte 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-32-SASET-0"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_32_SASET_0"
	:lambda-list (array new-value)
	:return-type (unsigned-byte 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-32-SASET-1"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_32_SASET_1"
	:lambda-list (array index new-value)
	:return-type (unsigned-byte 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-32-SASET-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_32_SASET_2"
	:lambda-list (array index0 index1 new-value)
	:return-type (unsigned-byte 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-32-SASET-3"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_32_SASET_3"
	:lambda-list (array index0 index1 index2 new-value)
	:return-type (unsigned-byte 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-32-SASET-4"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_32_SASET_4"
	:lambda-list (array index0 index1 index2 index3 new-value)
	:return-type (unsigned-byte 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-32-SASET-5"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_32_SASET_5"
	:lambda-list (array index0 index1 index2 index3 index4 new-value)
	:return-type (unsigned-byte 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-32-SASET-6"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_32_SASET_6"
	:lambda-list (array index0 index1 index2 index3 index4 index5
			    new-value)
	:return-type (unsigned-byte 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-32-SASET-7"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_32_SASET_7"
	:lambda-list (array index0 index1 index2 index3 index4 index5 index6
			    new-value)
	:return-type (unsigned-byte 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

;;; (unsigned-byte 64)

("%UBYTE-64-SAREF-0"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_64_SAREF_0"
	:lambda-list (array)
	:return-type (unsigned-byte 64)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-64-SAREF-1"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_64_SAREF_1"
	:lambda-list (array index)
	:return-type (unsigned-byte 64)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-64-SAREF-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_64_SAREF_2"
	:lambda-list (array index0 index1)
	:return-type (unsigned-byte 64)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-64-SAREF-3"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_64_SAREF_3"
	:lambda-list (array index0 index1 index2)
	:return-type (unsigned-byte 64)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-64-SAREF-4"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_64_SAREF_4"
	:lambda-list (array index0 index1 index2 index3)
	:return-type (unsigned-byte 64)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-64-SAREF-5"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_64_SAREF_5"
	:lambda-list (array index0 index1 index2 index3 index4)
	:return-type (unsigned-byte 64)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-64-SAREF-6"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_64_SAREF_6"
	:lambda-list (array index0 index1 index2 index3 index4 index5)
	:return-type (unsigned-byte 64)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-64-SAREF-7"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UBYTE_64_SAREF_7"
	:lambda-list (array index0 index1 index2 index3 index4 index5 index6)
	:return-type (unsigned-byte 64)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%UBYTE-64-SASET-0"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_64_SASET_0"
	:lambda-list (array new-value)
	:return-type (unsigned-byte 64)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-64-SASET-1"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_64_SASET_1"
	:lambda-list (array index new-value)
	:return-type (unsigned-byte 64)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-64-SASET-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_64_SASET_2"
	:lambda-list (array index0 index1 new-value)
	:return-type (unsigned-byte 64)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-64-SASET-3"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_64_SASET_3"
	:lambda-list (array index0 index1 index2 new-value)
	:return-type (unsigned-byte 64)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-64-SASET-4"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_64_SASET_4"
	:lambda-list (array index0 index1 index2 index3 new-value)
	:return-type (unsigned-byte 64)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-64-SASET-5"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_64_SASET_5"
	:lambda-list (array index0 index1 index2 index3 index4 new-value)
	:return-type (unsigned-byte 64)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-64-SASET-6"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_64_SASET_6"
	:lambda-list (array index0 index1 index2 index3 index4 index5
			    new-value)
	:return-type (unsigned-byte 64)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("%UBYTE-64-SASET-7"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "UBYTE_64_SASET_7"
	:lambda-list (array index0 index1 index2 index3 index4 index5 index6
			    new-value)
	:return-type (unsigned-byte 64)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object nil)
			    (:object nil) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )
)
