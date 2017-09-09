;;; -*- Mode: Lisp; Package: HOST; Syntax: Common-Lisp -*-
;;;
;;; list-symbols.lisp -- additional symbols that exist in the run-time system
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/list-symbols.lisp,v $"
 "$Revision: 1.2 $"
 "$Date: 2007/05/21 17:34:43 $")


(himpl:define-symbols :host t

("ATOM"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%atom t))
	)
    (:type-name)
    )

("%ATOM"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "ATOM"
        :lambda-list (object)
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )


("CAAAAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%caaaar t))
        )
    (:setf-place)
    )

("CAAADR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%caaadr t))
        )
    (:setf-place)
    )

("CAAAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%caaar t))
        )
    (:setf-place)
    )

("CAADAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%caadar t))
        )
    (:setf-place)
    )

("CAADDR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%caaddr t))
        )
    (:setf-place)
    )

("CAADR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%caadr t))
        )
    (:setf-place)
    )

("CAAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%caar t))
        )
    (:setf-place)
    )

("CADAAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cadaar t))
        )
    (:setf-place)
    )

("CADADR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cadadr t))
        )
    (:setf-place)
    )

("CADAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cadar t))
        )
    (:setf-place)
    )

("CADDAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%caddar t))
        )
    (:setf-place)
    )

("CADDDR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cadddr t))
        )
    (:setf-place)
    )

("CADDR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%caddr t))
        )
    (:setf-place)
    )

("CADR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cadr t))
        )
    (:setf-place)
    )

("CAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%car t))
        )
    (:setf-place)
    )


("CDAAAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cdaaar t))
        )
    (:setf-place)
    )

("CDAADR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cdaadr t))
        )
    (:setf-place)
    )

("CDAAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cdaar t))
        )
    (:setf-place)
    )

("CDADAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cdadar t))
        )
    (:setf-place)
    )

("CDADDR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cdaddr t))
        )
    (:setf-place)
    )

("CDADR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cdadr t))
        )
    (:setf-place)
    )

("CDAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cdar t))
        )
    (:setf-place)
    )

("CDDAAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cddaar t))
        )
    (:setf-place)
    )

("CDDADR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cddadr t))
        )
    (:setf-place)
    )

("CDDAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cddar t))
        )
    (:setf-place)
    )

("CDDDAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cdddar t))
        )
    (:setf-place)
    )

("CDDDDR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cddddr t))
        )
    (:setf-place)
    )

("CDDDR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cdddr t))
        )
    (:setf-place)
    )

("CDDR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cddr t))
        )
    (:setf-place)
    )

("CDR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%cdr t))
        )
    (:setf-place)
    )

("%CAAAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CAAAAR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CAAADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CAAADR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CAAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CAAAR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CAADAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CAADAR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CAADDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CAADDR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CAADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CAADR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CAAR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CADAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CADAAR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CADADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CADADR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CADAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CADAR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CADDAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CADDAR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CADDDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CADDDR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CADDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CADDR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CADR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CAR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CDAAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CDAAAR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CDAADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CDAADR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CDAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CDAAR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CDADAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CDADAR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CDADDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CDADDR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CDADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CDADR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CDAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CDAR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CDDAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CDDAAR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CDDADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CDDADR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CDDAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CDDAR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CDDDAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CDDDAR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CDDDDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CDDDDR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CDDDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CDDDR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CDDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CDDR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%CDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CDR"
        :lambda-list (list)
	:argument-types (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
        )
    )

("%M-CAAAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CAAAAR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CAAADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CAAADR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CAAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CAAAR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CAADAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CAADAR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CAADDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CAADDR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CAADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CAADR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CAAR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CADAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CADAAR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CADADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CADADR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CADAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CADAR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CADDAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CADDAR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CADDDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CADDDR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CADDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CADDR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CADR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CAR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CDAAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CDAAAR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CDAADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CDAADR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CDAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CDAAR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CDADAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CDADAR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CDADDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CDADDR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CDADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CDADR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CDAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CDAR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CDDAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CDDAAR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CDDADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CDDADR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CDDAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CDDAR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CDDDAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CDDDAR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CDDDDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CDDDDR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CDDDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CDDDR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CDDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CDDR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%M-CDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_CDR"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )


("%SET-CAAAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-caaaar
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CAAADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-caaadr
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CAAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-caaar
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CAADAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-caadar
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CAADDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-caaddr
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CAADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-caadr
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-caar
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CADAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cadaar
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CADADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cadadr
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CADAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cadar
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CADDAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-caddar
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CADDDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cadddr
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CADDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-caddr
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cadr
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-car
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CDAAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cdaaar
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CDAADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cdaadr
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CDAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cdaar
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CDADAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cdadar
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CDADDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cdaddr
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CDADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cdadr
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CDAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cdar
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CDDAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cddaar
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CDDADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cddadr
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CDDAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cddar
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CDDDAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cdddar
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CDDDDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cddddr
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CDDDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cdddr
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CDDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cddr
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-CDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-cdr
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )
("SET-CAAAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CAAADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CAAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CAADAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CAADDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CAADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CADAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CADADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CADAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CADDAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CADDDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CADDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CDAAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CDAADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CDAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CDADAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CDADDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CDADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CDAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CDDAAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CDDADR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CDDAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CDDDAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CDDDDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CDDDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CDDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("SET-CDR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	)
    )

("FIRST"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%first t))
	)
    (:setf-place)
    )

("%FIRST"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "FIRST"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
	)
    )

("%M-FIRST"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_FIRST"
	:lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SET-FIRST"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-first
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("SET-FIRST"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	:unsupported t
	)
    )

("SECOND"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%second t))
	)
    (:setf-place)
    )

("%SECOND"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "SECOND"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
	)
    )

("%M-SECOND"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_SECOND"
	:lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SET-SECOND"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-second
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("SET-SECOND"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
	:lambda-list (cell new-value)
	:return-type t
	:unsupported t
	)
    )

("THIRD"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%third t))
	)
    (:setf-place)
    )

("%THIRD"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "THIRD"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
	)
    )

("%M-THIRD"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_THIRD"
	:lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SET-THIRD"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-third
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("SET-THIRD"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	:unsupported t
	)
    )

("FOURTH"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%fourth t))
	)
    (:setf-place)
    )

("%FOURTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "FOURTH"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
	)
    )

("%M-FOURTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_FOURTH"
	:lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SET-FOURTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-fourth
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("SET-FOURTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	:unsupported t
	)
    )

("FIFTH"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:transforms ((trun:%fifth t))
	)
    (:setf-place)
    )

("%FIFTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "FIFTH"
        :lambda-list (list)
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
	)
    )

("%M-FIFTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_FIFTH"
	:lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SET-FIFTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-fifth
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("SET-FIFTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	:unsupported t
	)
    )

("SIXTH"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%sixth t))
	)
    (:setf-place)
    )

("%SIXTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "SIXTH"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
	)
    )

("%M-SIXTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_SIXTH"
	:lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SET-SIXTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-sixth
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("SET-SIXTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
	:lambda-list (cell new-value)
	:return-type t
	:unsupported t
	)
    )

("SEVENTH"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%seventh t))
	)
    (:setf-place)
    )

("%SEVENTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "SEVENTH"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
	)
    )

("%M-SEVENTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_SEVENTH"
	:lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SET-SEVENTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-seventh
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("SET-SEVENTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
	:lambda-list (cell new-value)
	:return-type t
	:unsupported t
	)
    )

("EIGHTH"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%eighth t))
	)
    (:setf-place)
    )

("%EIGHTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "EIGHTH"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
	)
    )

("%M-EIGHTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_EIGHTH"
	:lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SET-EIGHTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-eighth
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("SET-EIGHTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	:unsupported t
	)
    )

("NINTH"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%ninth t))
	)
    (:setf-place)
    )

("%NINTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "NINTH"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
	)
    )

("%M-NINTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_NINTH"
	:lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SET-NINTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-ninth
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("SET-NINTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
	:lambda-list (cell new-value)
	:return-type t
	:unsupported t
	)
    )

("TENTH"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%tenth t))
	)
    (:setf-place)
    )

("%TENTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "TENTH"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
	)
    )

("%M-TENTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "M_TENTH"
	:lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SET-TENTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-tenth
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("SET-TENTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (cell new-value)
	:return-type t
	:unsupported t
	)
    )

("REST"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (list)
	:return-type t
	:transforms ((trun:%rest t))
	)
    (:setf-place)
    )

("%REST"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "REST"
        :lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	;; :uses-locals (trun:%local-temp-declaration)
	)
    )

("%M-REST"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "M_REST"
	:nonconsing t
	:lambda-list (list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SET-REST"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-rest
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("SET-REST"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
	:lambda-list (cell new-value)
	:return-type t
	:unsupported t
	)
    )

("CONS"
    (:symbol
        :package "TCL"
	:exists-at-runtime t
	)
    (:class-name)
    (:function
        :state-changing nil
        :lambda-list (x y)
        :return-type cons
	:transforms ((trun:%cons t))
	)
    (:random-syntax)
    (:type-name)
    (:type-specifier-list)
    )

("%CONS"
    (:symbol
        :package "TRUN"
	:exists-at-runtime nil
	:import-from nil
	)
    (:function
        :state-changing nil
	:state-using nil
        :entry-name "CONS"
        :lambda-list (x y)
        :return-type cons
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
        :foreign-return-type :object
	)
    )

("CONSP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%consp t))
	)
    )

("%CONSP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CONSP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("ENDP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
        :return-type t
	:transforms ((trun:%endp t))
	)
    )

("%ENDP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "ENDP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("LAST"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list &optional n)
        :return-type list
	)
    )


("LDIFF"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (list sublist)
        :return-type list
	)
    )

("LISTP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%listp t))
	)
    )

("%LISTP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "LISTP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("MAKE-LIST"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (size &key initial-element)
        :return-type list
	)
    )


("NBUTLAST"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (list &optional n)
        :return-type list
	)
    )

("RPLACA"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (x y)
        :return-type cons
	:transforms ((trun:%rplaca t))
	)
    )

("%RPLACA"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :nonconsing t
	:entry-name "RPLACA"
        :lambda-list (x y)
        :return-type cons
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil))
	:foreign-return-type :object
	)
    )

("RPLACD"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (x y)
        :return-type cons
	:transforms ((trun:%rplacd t))
	)
    )

("%RPLACD"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :nonconsing t
	:entry-name "RPLACD"
        :lambda-list (x y)
        :return-type cons
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object nil))
	:foreign-return-type :object
	)
    )

("TAILP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (sublist list)
        :return-type t
	)
    )

("NTH"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (n list)
        :return-type t
	)
    (:setf-place)
    )


("%M-NTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "M_NTH"
	:lambda-list (n list)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )


("%SET-NTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (n list new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue trun:%m-nth
	:foreign-arguments ((:object nil) (:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("SET-NTH"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (n list new-value)
	:return-type t
	:unsupported t
	)
    )

)
