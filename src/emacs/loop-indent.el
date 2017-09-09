;;;; Hairy CL LOOP indenter

;;; This code works well in simple cases, and works well enough
;;; in complex cases.  It's just indentation, after all.


(defmacro DBG (&rest args))
'  (cons 'formatd args)


  
;; Not all of them.
;; cltl2 defines an END keyword, which we should handle.
(defconst loop-keywords '(named initially finally nodeclare do doing return
			  collect collecting append appending nconc nconcing
			  count counting sum summing
			  maximize minimize always never thereis
			  while until when if unless with))

(defconst loop-iteration-keywords '(for as repeat))

;; These get indented to fall under the "UPFROM" (or whatever)
(defconst loop-iteration-modifiers '(then below above by to in being with-key with-index =))


;; For our purposes, anything which allows an INTO modifier.
(defconst loop-collection-keywords '(collect collecting append appending nconc nconcing
				     count counting sum summing maximize minimize))

;; Modifiers to collect, sum, etc.
(defconst loop-collection-modifiers '(into using))


;; Loop "statements" are indented below the first word after "LOOP".
(defconst loop-statement-keywords '(with for as repeat initially finally while until))


;; Other keywords with an implicit PROGN following.
(defconst loop-progn-keywords '(initially finally))


(defconst loop-condition-keywords '(when if unless else))

(defun loop-keyword-p (symbol)
  (or (memq symbol loop-keywords)
      (memq symbol loop-iteration-keywords)
      (memq symbol loop-condition-keywords)
      (eq symbol 'else)
      (eq symbol 'and)))



(defsubst list-like-p ()
  ;; True it we are looking a tht beginning of a list or reader macro.
  (looking-at "(\\|#+\\|#-"))



;; Path describes the position of point in terms of
;;   list-structure with respect to containing lists.
;;   `foo' has a path of (0 4 1) in `((a b c (d foo) f) g)'
;; State is as returned by parse-partial-sexp.
;; Indent-point is somewhere on the line we are indenting.
;; Sexp-column is the column number of the start of the containing sexp.
;; Normal-indent is the column number at indent-point, ie, what to return to do nothing.

;; Reference random free variable!
(defvar containing-sexp nil)

;;; Simple cases:
;;;  -- If immediately containing sexp is not LOOP, then indent as usual.
;;;  -- If preceding sexp is a cons, indent under its open paren (implicit progn).

;; todo: (loop for x<newline>in list)   (loop for x =<newline>foo)
;;       ANSI "end" keyword.

;; Bug: given "= (or ...", with point before the "=", then forward-word jumps past the or!
;; a b c d
;; a = c d

(defun lisp-indent-loop (path state indent-point sexp-column normal-indent)
  (let* ((loop-paren containing-sexp)   ; Start of loop sexp.
	 (immediately-containing-sexp (elt state 1))
	 (previous-sexp (elt state 2))	; Start of last complete sexp.
         (start (condition-case ()	; Start of first word after LOOP. What if there isn't one?
		    (save-excursion	; The condition-case is not working, for some reason.
		      (goto-char loop-paren)
		      (forward-word 1)	; Handle (loop ; comment \n with ...)
		      (if (looking-at "[ \t]*;")
			  (forward-sexp 1) ; Skip over the comment.
			  (forward-word 1))
		      (backward-word 1)
		      (point))
		    (error (point))))
         (start-of-line (progn (goto-char indent-point)
			       (beginning-of-line)
			       (skip-chars-forward " \t")
			       (point)))
         (word (let ((beg (point)))
		 (condition-case ()
		     (forward-sexp 1)	; Really want: forward-cl-symbol. forward-word screws up "=".
		   (error))
		 (buffer-substring beg (point))))
         (key (intern-soft (downcase word)))
         (prev (intern-soft (downcase (loop-previous-word indent-point))))
	 (blank-line-p (progn
			 (goto-char start-of-line)
			 (eolp)))
	 (comment-line-p (string-match "\\`;;[^;]" word)))

    ;; Fixup previous-sexp: it is confused by reader macros #+ and #-
    (save-excursion
      (goto-char (- previous-sexp 1))
      (if (looking-at "#")
	  (setq previous-sexp (point))
	  (backward-char 1)
	  (if (looking-at "#")
	      (setq previous-sexp (point)))))
	      
      
    (DBG)
    (DBG word key prev state)
    (DBG (show-bp loop-paren) (show-bp immediately-containing-sexp))
    (DBG (show-bp previous-sexp) (show-bp start))
    (DBG (show-bp start-of-line) sexp-column)

    ;; Good place to start.
    (goto-char start-of-line)    
    (cond ((eq prev 'loop)		; First line after LOOP.
	   (DBG "Start of LOOP")
	   (+ (bp-column loop-paren) 2))

	  ((not (equal loop-paren immediately-containing-sexp))	; Inside some other sexp.
	   (DBG "Inside some other sexp")
	   normal-indent)
	  
	  ((and (save-excursion (goto-char previous-sexp) (list-like-p)) ; Previous sexp is list-like
		(save-excursion (goto-char start-of-line) (list-like-p))) ; and so are we.
	   (DBG "Two lists in a row")
	   (bp-column previous-sexp))
	  
          ((memq key loop-statement-keywords) ; Unconditionalizable loop statments: always at START.
           (DBG "An unconditionalizable LOOP statement" key)
           (bp-column start))
	  
          ((memq key loop-iteration-modifiers) ; Indent these under the FROM (or whatever)
	   (DBG "Iteration modifier" key) ; Also unconditionalizable.
           (save-excursion
             (let ((looping t)
                   word end for-pos)

               (DBG key (show-bp start))

               (while (and (>= (point) start) looping)
                 (setq end (save-excursion (forward-sexp 1) (point))
                       word (intern-soft (downcase (buffer-substring (point) end))))
                 (DBG word)
                 (if (memq word '(for as with))	; Allow for "with foo = ...". (?)
                     (setq looping nil
			   for-pos (point))
                     (backward-sexp 1)))
	       
               (cond (looping           ; Never found an iteration clause.
                      (beep)            ; Don't signal an error: still want to indent someplace.
                      (message "The LOOP keyword \"%s\" has no matching FOR or AS." key)
                      normal-indent)
                     (t
		      ;; Indent under the "=" in "for x = ...". END points to the "x" here.
		      ;; We need the hair here to handle line breaks.
                      (goto-char end)
		      (forward-sexp 1)
		      (skip-chars-forward " \t")

		      ;; If the newline happens before the "=", then indent under
		      ;; "x" for "for" and "as", otherwise two spaces past the "with".
		      (if (or (eolp) (looking-at ";"))
			  (cond ((eq word 'with)
				 (goto-char for-pos)
				 (forward-char 2))
				(t
				 (backward-sexp 1))))
		      (DBG word (show-bp end) (show-bp (point)))
		      (bp-column (point)))))))

          
          ((memq key loop-collection-modifiers) ; Indent these a bit in from the matching COLLECT.
	   (DBG "Collection modifier" key) ; Also unconditionalizable.
           (save-excursion
             (let ((looping t)
                   word beg end)

               (DBG key (show-bp start))

               (while (and (>= (point) start) looping)
                 (setq beg (point)
		       end (save-excursion (forward-sexp 1) (point))
                       word (intern-soft (downcase (buffer-substring beg end))))
                 (DBG word)
                 (if (memq word loop-collection-keywords)
                     (setq looping nil)
                     (backward-sexp 1)))
	       
               (cond (looping           ; Never found a collection clause.
                      (beep)            ; Don't signal an error: still want to indent someplace.
                      (message "The LOOP keyword \"%s\" has no matching COLLECT, SUM, etc." key)
                      normal-indent)
                     (t			; Indent 2 spaces in from the COLLECT.
		      (+ (bp-column beg) 2))))))

          
          ((memq prev loop-progn-keywords) ; Initially, finally.
	   (DBG "Followed LOOP toplevel progn-like keyword:" prev)
	   (+ (bp-column start) 2))
	  
          (t
           (DBG "DEFAULT case" word)

	   ;; First, we have to scan backwards to see if we are in the scope of
	   ;; a conditional.  Careful to skip matching if/else pairs.
	   (let ((looping t)
		 (answer nil)
		 (last-key key)
		 (this-key nil)
		 (else-stack ())
		 beg end)

	     (DBG (show-bp (point)) (show-bp start))

	     ;; Starting off with an ELSE clause.
	     (if (eq key 'else)
		 (setq else-stack (cons key else-stack)))

	     ;; Blank lines and ";;" comments should be indented as if they were an AND,
	     ;; to chain us with the preceding line if possible?
;;	     (if (or blank-line-p comment-line-p)
;;		 (setq last-key 'and))

	     (while (and looping (> (point) start))
	       (backward-sexp 1)
	       (setq beg (point)
		     end (save-excursion (forward-sexp 1) (point))
		     this-key (intern-soft (downcase (buffer-substring beg end))))
	       (DBG last-key this-key else-stack)
	       (cond ((not (loop-keyword-p this-key))) ; A sexp or junk. Keep scanning.
		     ((memq this-key loop-condition-keywords) ; In scope of this condition.
		      (cond ((null else-stack)
			     (DBG "In scope of condition" this-key)
			     (setq looping nil
				   answer (+ beg 2)))
			    (t
			     (DBG "Pop stack: this IF was matched by an ELSE")
			     (setq else-stack (cdr else-stack)))))

		     ((or (eq last-key 'and)  ; If preceding AND, keep scanning.
			  (eq this-key 'and))
		      (DBG "Chained with preceding AND")
		      (setq last-key this-key))

                     ((and (null else-stack) ; Not in a conditional after all.
			   (loop-keyword-p last-key))
                      (DBG "In top-level scope.")
                      (setq looping nil
                            answer nil))
		     (t
		      (setq last-key this-key)
		      (DBG "now what"))))

	     (DBG prev answer last-key (show-bp beg) (show-bp answer))
	     (DBG blank-line-p comment-line-p)

	     (cond ((or (memq prev '(do doing)) ; First sexp of a DO.
			(and (memq last-key '(do doing)) ; Or, a later sexp of a DO, and not a LOOP keyword.
			     (or blank-line-p comment-line-p)))
		    (cond ((null answer)
			   (DBG "Top level DO" prev)
			   (+ sexp-column 2))
			  (t		; Indent after the "O" in "DO".
			   (bp-column (+ answer 2)))))
		   (answer
		    (bp-column answer))
		   (t
		    (DBG "Must be top level")
		    (bp-column start))))))))


(defun bp-column (bp)
  (save-excursion (goto-char bp) (current-column)))

(defun loop-previous-word (bp)
  (let (start end)
    (save-excursion
      (goto-char bp)
      (beginning-of-line)
      (backward-sexp 1)
      (setq start (point))
      (forward-sexp 1)
      (setq end (point)))
    (buffer-substring start end)))

    
(cond ((string-match "Lucid" (emacs-version)) ; Or Emacs 19?
       (put 'loop 'common-lisp-indent-function 'lisp-indent-loop))
      (t
       ;; Emacs-18 compat.
       (put 'loop 'common-lisp-indent-hook 'lisp-indent-loop)))

(provide 'loop-indent)
