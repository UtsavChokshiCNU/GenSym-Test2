(in-package "AB")


;;;; Module HTMLGEN (HTML Generation)

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Ben Hyde




(defvar current-html-insert-mark)

(defmacro with-html-cliches (() &body body)
  `(progn
     ;; (declare (special current-html-insert-mark))
     (macrolet ((emit (text)
		  `(insert-text-at-mark current-html-insert-mark ,text))
		(femit (&rest args)
		  `(let ((txt (tformat-text-string ,@args)))
		     (emit txt)
		     (reclaim-text-string txt)))
		(emit-newline ()
		  `(emit #.(coerce '(#\return #\linefeed) 'string)))
		(with-paragraph (bogus &body body)
		  (declare (ignore bogus))
		  `(progn
		     (emit-newline)
		     (emit "<P>")
		     ,@body
		     (emit-newline)))
		(with-element ((element) &body body)
		  `(progn
		     (emit "<") (emit ,element) (emit ">")
		     ,@body
		     (emit "</") (emit ,element) (emit ">"))))
       ,@body)))

(defmacro with-html-output ((&key (insert-mark) (title "No Title")) &body body)
  `(let ((current-html-insert-mark ,insert-mark))
    ;; (declare (special current-html-insert-mark))
    (with-html-cliches ()
      (with-element ("HTML")
	(with-element ("HEADER")
	  (with-element ("TITLE") (emit ,title)))
	(with-element ("BODY")
	  ,@body)))))

