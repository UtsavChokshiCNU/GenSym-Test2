;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module BUFFER

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Ben Hyde



;;;; Introduction

;;; Resource Buffers are like the buffers of an editor.  They
;;; are filled with characters, chopped up into mangable sized
;;; fragments.  Marks into this stream are provided as the handle
;;; to a buffer.  The marks have directions, so we know which side
;;; of an insertion to place the mark.

;;; These are fairly simple.  Only 8bit characters, display engine,
;;; and most operations are very casually written.

;;; In addition this module provides operations ala Snobol or Icon
;;; for scanning/parsing the contents of a resource buffer.

;;; In addition an abstraction tool called binding cliches is
;;; defined.  Binding cliches provide a declaritive mechinism
;;; to assure that the cliche for fetching X given Y is stated
;;; only once.  When the coder desires X and has Y he using
;;; with-bindings to fetch it.










;;;; Cliche Binding

(def-global-property-name binding-cliches)

;;; `Def-binding-cliche' declares ways to get a binding for
;;; name presuming you already have bindings for some
;;; precursors.  The body is a list of cliche-pattern. And
;;; each of those is of the form: ((<precursor>*) binding-form)

(defmacro def-binding-cliche (name &body cliche-patterns)
  `(progn-for-macro
     (eval-when (:compile-toplevel :load-toplevel :execute)
       (setf (binding-cliches ',name) ',cliche-patterns)
       ',name)))


;;; `with-bindings' creates a let binding for a set of
;;; variables, given some number of useful input variables
;;; as made possible by the binding cliches.  This is done
;;; by iterating to a fix point over the set of cliches.
;;; It will complain if it doesn't find bindings for every
;;; thing desired.

(defmacro with-bindings ((desired-bindings givens) &body body)
  (let ((bindings nil)
	(desired-bindings (copy-list desired-bindings)))
    (loop
      repeat 10 while desired-bindings doing
      (loop for b in (copy-list desired-bindings)
	    as binding-patterns = (binding-cliches b) doing
	(cond
	  ((not binding-patterns)
	   (setf desired-bindings (delete b desired-bindings))
	   (warn "No cliches for binding ~S" b)
	   (push `(,b :huh) bindings))
	  (t
	   (loop for (requirements code) in binding-patterns
		 when (loop for need in requirements
			    always (memq need givens))
		   do (progn
			(setf desired-bindings (delete b desired-bindings))
			(push b givens)
			(push `(,b ,code) bindings)
			(return)))))))
    (loop for b in desired-bindings
	  do (warn "Unable to bind ~S." b))
    `(let* ,(nreverse bindings)
       ,@body)))







;;;; Resource Buffers


(defparameter prefered-line-terminator #\linefeed)

(defparameter default-fragment-max 2100)

(defparameter default-fragment-bit-size 2000) ;; Less than default-fragment-max!

(def-structure (rb-mark
		 #+development
		 (:print-function print-rb-mark-structure))
  resource-buffer-of-mark
  (direction-of-mark :forward)
  fragment-of-mark
  (index-of-mark 0))

(def-structure (rb-fragment)
  (next-fragment-of-fragment nil
			     :reclaimer reclaim-rb-fragment-if-any)
  (text-of-fragment
    (obtain-gensym-string default-fragment-max)
    :reclaimer reclaim-gensym-string)
  (position-of-fragment 0)
  (length-of-fragment 0))

(def-structure (r-buffer) 
  (fragments-of-resource-buffer nil
				:reclaimer reclaim-rb-fragment)
  (marks-of-resource-buffer nil
			    :reclaimer reclaim-list-of-marks-1)
  (plist-of-resource-buffer nil :reclaimer reclaim-plist-of-resource-buffer))

;; Call this a resource-buffer created trouble with the gsi library.

#+development
(defun print-rb-mark-structure (rb-mark stream depth)
  (declare (ignore depth))
  (let* ((resource-buffer-of-mark (resource-buffer-of-mark rb-mark)))
    (printing-random-object (rb-mark stream)
      (format stream "rb-mark at ~S of ~S"
	      (if (fragment-of-mark rb-mark)
		  (+f (position-of-fragment (fragment-of-mark rb-mark))
		     (index-of-mark rb-mark))
		  '???)
	      resource-buffer-of-mark))))

(defun reclaim-rb-fragment-if-any (fragment?)
  (when fragment?
    (reclaim-rb-fragment fragment?)))

(defun-void reclaim-list-of-marks-1 (marks)
  (loop for mark in marks
	do (reclaim-rb-mark mark))
  (reclaim-gensym-list marks))

(defun reclaim-resource-buffer-of-mark (mark)
  (reclaim-r-buffer (resource-buffer-of-mark mark))
  nil)

(defmacro with-mark-on-fresh-buffer ((mark) &body body)
  `(let ((,mark (make-mark-into-new-empty-resource-buffer)))
     (prog1
	 (progn ,@body)
       (reclaim-resource-buffer-of-mark ,mark))))


			     







;;;; Binding Cliches around Buffers.

(def-binding-cliche fragment
    ((mark) (fragment-of-mark mark)))

(def-binding-cliche fragment-of-mark
    ((mark) (fragment-of-mark mark)))

(def-binding-cliche position-of-mark
    ((mark fragment) (+f (position-of-fragment fragment)
			(index-of-mark mark))))

(def-binding-cliche length-of-fragment
    ((fragment) (length-of-fragment fragment)))

(def-binding-cliche next-fragment?
    ((fragment) (next-fragment-of-fragment fragment)))

(def-binding-cliche text-of-fragment
    ((fragment) (text-of-fragment fragment))
  ((mark) (text-of-fragment (fragment-of-mark fragment))))

(def-binding-cliche resource-buffer
    ((mark) (resource-buffer-of-mark mark)))

(def-binding-cliche index-of-mark
    ((mark) (index-of-mark mark)))

(def-binding-cliche max-of-fragment
    ((text-of-fragment) (length text-of-fragment)))

(def-binding-cliche position-of-fragment
    ((fragment) (position-of-fragment fragment)))

(def-binding-cliche start-position-of-fragment
    ((fragment) (position-of-fragment fragment)))

(def-binding-cliche end-position-of-fragment
    ((start-position-of-fragment length-of-fragment)
     (+f start-position-of-fragment length-of-fragment)))

(def-binding-cliche fragments-of-resource-buffer
    ((resource-buffer)
     (fragments-of-resource-buffer resource-buffer)))

(def-binding-cliche buffer-plist
    ((resource-buffer)
     (plist-of-resource-buffer resource-buffer)))

(def-binding-cliche end-position-of-buffer
    ((fragments-of-resource-buffer)
     (loop for f = fragments-of-resource-buffer then (next-fragment-of-fragment f)
	   while (next-fragment-of-fragment f)
	   finally (return
		     (+f (position-of-fragment f)
			(length-of-fragment f))))))










;;;; Making Buffer Bits.

(defun make-mark-into-new-empty-resource-buffer ()
  (let ((resource-buffer (make-r-buffer))
	(fragment (make-rb-fragment)))
    (setf (fragments-of-resource-buffer resource-buffer)
	  fragment)
    (make-mark-at-start resource-buffer)))

(defun make-mark-at-start (resource-buffer)
  (let ((mark (make-rb-mark)))
    (setf (resource-buffer-of-mark mark) resource-buffer)
    (setf (fragment-of-mark mark)
	  (fragments-of-resource-buffer resource-buffer))
    (gensym-push mark (marks-of-resource-buffer resource-buffer))
    mark))

(defun mark-copy (mark)
  (let ((new-mark (make-mark-at-start
		    (resource-buffer-of-mark mark))))
    (setf (index-of-mark new-mark) (index-of-mark mark))
    (setf (fragment-of-mark new-mark) (fragment-of-mark mark))
    new-mark))

(defun mark-set (mark-to-set mark-to-copy)
  ;; No check we are in same buffer?
  (setf (fragment-of-mark mark-to-set) (fragment-of-mark mark-to-copy))
  (setf (index-of-mark mark-to-set) (index-of-mark mark-to-copy)))

(defun mark-eq (mark-a mark-b)
  (let ((ia (index-of-mark mark-a))
	(ib (index-of-mark mark-b)))
    (cond
      ((eq (fragment-of-mark mark-a) (fragment-of-mark mark-b))
       (eq ia ib))
      ((=f 0 ia)
       (let ((fb (fragment-of-mark mark-b)))
	 (and
	   (eq (length-of-fragment fb) ib)
	   (eq (next-fragment-of-fragment fb) (fragment-of-mark mark-b)))))
      ((=f 0 ib)
       (let ((fa (fragment-of-mark mark-a)))
	 (and
	   (eq (length-of-fragment fa) ia)
	   (eq (next-fragment-of-fragment fa) (fragment-of-mark mark-a))))))))
	 

(defun mark-kill (mark)
  (let ((resource-buffer
	  (resource-buffer-of-mark mark)))
    (setf (marks-of-resource-buffer resource-buffer)
	  (delete-gensym-element
	    mark (marks-of-resource-buffer resource-buffer)))
    (reclaim-rb-mark mark)
    nil))

(defun mark-direction (mark new-direction)
  (setf (direction-of-mark mark) new-direction)
  mark)

(defmacro with-mark ((new-mark old-mark) &body body)
  `(let ((,new-mark (mark-copy ,old-mark)))
     (prog1 (progn ,@body)
       (mark-kill ,new-mark))))









;;;; Resource Buffer Plist Tools

(defun set-property-of-buffer (mark property value)
  (with-bindings ((resource-buffer buffer-plist) (mark))
    (loop for (key . value-cons) on buffer-plist
	  when (eq key property) 
	  do (setf (car value-cons) value)
	     (return nil)
	  finally
	  (setf (plist-of-resource-buffer resource-buffer)
		(gensym-cons property
			     (gensym-cons value buffer-plist)))))
  value)

(defun get-property-of-buffer (mark property)
  (with-bindings ((resource-buffer buffer-plist) (mark))
    (loop for (key value) on buffer-plist
	  when (eq key property) do (return value))))

(defun reclaim-plist-of-resource-buffer (plist)
  (reclaim-plist-tree-of-resource-buffer plist))

(defun reclaim-plist-tree-of-resource-buffer (tree)
  (cond
    ((consp tree)
     (reclaim-plist-tree-of-resource-buffer (car tree))
     (reclaim-plist-tree-of-resource-buffer (cdr tree))
     (reclaim-gensym-cons tree))
    ((wide-string-p tree)
     (reclaim-wide-string tree))
    ((gensym-string-p tree)
     (reclaim-gensym-string tree))
    #+development
    ((symbolp tree)
     )
    #+development
    (t
     ; (print tree)
     )))

(defun copy-resource-plist-value (value)
  (macrolet ((recure (x) `(copy-resource-plist-value ,x)))
    (cond
      ((consp value)
       (gensym-cons
	 (recure (car value))
	 (recure (cdr value))))
      ((stringp value)
       (copy-text-string value))
      (t
       value))))

;;; `def-buffer-property' currently is nothing more than def-concept.

(defmacro def-buffer-property (name)
  `(def-concept ,name))



  







;;;; Point Operations

;;; A point is a fixnum.  It is used to represent a position in
;;; a buffer.


;;; `point-min' returns the minimum position in the buffer of the
;;; mark given.

(defun point-min (mark-for-buffer)
  (declare (ignore mark-for-buffer))
  0)

;;; `point-max' computes the maximum position in the buffer of the
;;; mark given.

(defun point-max (mark)
  (with-bindings ((resource-buffer) (mark))
    (loop for fragment = (fragments-of-resource-buffer resource-buffer)
		       then next-fragment?
	  as next-fragment? = (next-fragment-of-fragment fragment)
	  unless next-fragment?
	    do (return (+f (position-of-fragment fragment)
			  (length-of-fragment fragment))))))





;;;; Mark Positioning

(defun mark-tab (mark position)
  (when (<f position 0)
    (setf position 0))
  (with-bindings ((resource-buffer
		    fragments-of-resource-buffer
		    fragment) (mark))
    (cond
      ;; Moving within current fragment
      ((with-bindings ((start-position-of-fragment) (mark fragment))
	 (and (<=f start-position-of-fragment position)
	      (with-bindings ((length-of-fragment end-position-of-fragment)
			      (start-position-of-fragment fragment))
		(<f position end-position-of-fragment))))
       (setf (index-of-mark mark)
	     (-f position (position-of-fragment fragment)))
       mark)
      ;; Try all fragments.
      (T
       (loop
	 for fragment = fragments-of-resource-buffer then next-fragment?
	 as next-fragment? = (next-fragment-of-fragment fragment)
	 do
	 (with-bindings ((start-position-of-fragment
			   length-of-fragment
			   end-position-of-fragment)
			 (fragment))
	   (when (and (<=f start-position-of-fragment position)
		      (<f position end-position-of-fragment))
	     (setf (fragment-of-mark mark) fragment)
	     (setf (index-of-mark mark) (-f position start-position-of-fragment))
	     (return mark))
	   (unless next-fragment?
	     (setf (fragment-of-mark mark) fragment)
	     (setf (index-of-mark mark) length-of-fragment)
	     (return mark))))))))

(defun mark-move (mark delta)
  (with-bindings ((fragment position-of-mark) (mark))
    (mark-tab mark (+f position-of-mark delta))))

(defun mark-move-to-end (mark)
  (mark-tab mark most-positive-fixnum))






;;;; Mark Character Routines

(defun mark-peek-character (mark)
  (block :done  ;; Note three exits points.
    (macrolet ((DONE (form) `(return-from :done ,form)))
      (with-bindings ((fragment
			index-of-mark
			text-of-fragment
			length-of-fragment) (mark))
	;; The easy case.
	(when (<f index-of-mark length-of-fragment)
	  (DONE (char text-of-fragment index-of-mark)))

	;; Look for an non-empty fragment.
	(loop for possible-fragment?
		  = (next-fragment-of-fragment fragment)
		  then (next-fragment-of-fragment possible-fragment?)
	      doing
	  (unless possible-fragment?
	    (DONE nil))
	  (when (<f 0 (length-of-fragment possible-fragment?))
	    (DONE
	      (char (text-of-fragment possible-fragment?) 0))))))))

(defun mark-get-character (mark)
  (prog1
      (mark-peek-character mark)
    (mark-move mark 1)))

(defun mark-peek-byte (mark)
  (char-code (mark-peek-character mark)))

(defun mark-get-byte (mark)
  (char-code (mark-get-character mark)))

(defun n-characters-available? (n left-mark right-mark)
  (<=f n
       (-f (position-of-mark right-mark)
	  (position-of-mark left-mark))))







;;;; Mapping between marks




;;; `With-text-between-marks' provides efficent access to the raw
;;; text of a buffer found between two marks.  It maps the body
;;; over triples bound to the three variables given.  Each triple
;;; is a text-string, along with a start and end position in that
;;; string.

(defmacro with-text-between-marks (((text-segment start-position end-position)
				    (start-mark end-mark)) &body body)
  `(loop
     with start-mark = ,start-mark
     with end-mark = ,end-mark
     with last-fragment = (fragment-of-mark end-mark)
     for fragment = (fragment-of-mark start-mark) then (next-fragment-of-fragment
							 fragment)
     as last-fragment? = (eq last-fragment fragment)
     as ,text-segment = (text-of-fragment fragment)
     as ,start-position = (index-of-mark start-mark) then 0
     as ,end-position = (if last-fragment?
			    (index-of-mark end-mark)
			    (length-of-fragment fragment))
     do
     (progn ,@body)
     (when last-fragment? (return nil))))




;;;; Copy Text from Buffer

(defun position-of-mark (mark)
  (with-bindings ((fragment position-of-mark) (mark))
    position-of-mark))

(defun copy-text-between-marks (from-mark to-mark)
  (let* ((position-from (position-of-mark from-mark))
	 (position-to (position-of-mark to-mark))
	 (length (-f position-to position-from))
	 (result
	   (obtain-gensym-string length)))
    (with-mark (mark from-mark)
      (loop for i from 0 below length
	    do (setf (char result i) (mark-get-character mark))))
    result))

#+development
(defun text-of-buffer (mark)
  (with-mark (start mark)
    (with-mark (end mark)
      (mark-tab start 0)
      (mark-move-to-end end)
      (copy-text-between-marks start end))))

#+development
(defun show-text-of-buffer (mark)
  (with-mark (start mark)
    (with-mark (end mark)
      (mark-tab start 0)
      (mark-move-to-end end)
      (with-text-between-marks ((text a b) (start end))
	(print (list
	  (- b a) (length text)
	  (subseq text a (min (+ a 5) b))
	  (subseq text (max (- b 5) a) b)))
	(print (subseq text a b))))))







;;;; Inserting Text into the Buffer


;;; `Insert-subtext-into-roomy-fragment' will insert the text into
;;; an existing fragment.  I presumes the fragment is large enough
;;; to hold the text being inserted.

(defun insert-subtext-into-roomy-fragment (mark text start end)
  (with-bindings ((index-of-mark fragment text-of-fragment length-of-fragment
				 resource-buffer) (mark))
    (let* ((length-of-insert (-f end start))
	   (old-length-of-fragment length-of-fragment)
	   (count-in-front-of-mark (-f old-length-of-fragment index-of-mark))
	   (new-length-of-fragment (+f old-length-of-fragment length-of-insert)))

      ;; Slide the text over to make room for insertion.
      (when (<f 0 count-in-front-of-mark)
	(loop
	  repeat count-in-front-of-mark
	  for from-i downfrom (1- old-length-of-fragment)
	  for to-i downfrom (1- new-length-of-fragment)
	  doing
	  (setf (char text-of-fragment to-i) (char text-of-fragment from-i))))

      ;; Enlarge the fragment
      (setf (length-of-fragment fragment) new-length-of-fragment)

      ;; Insert the text
      (loop for i from start below end
	    for j from index-of-mark
	    doing (setf (char text-of-fragment j) (char text i)))

      ;; Move the position of the following fragments
      (loop for next-fragment = (next-fragment-of-fragment fragment)
			      then (next-fragment-of-fragment next-fragment)
			      while next-fragment
			      doing (incf (position-of-fragment next-fragment) length-of-insert))

      ;; Move the marks in this buffer that are in front of the insert.
      (loop for a-mark in (marks-of-resource-buffer resource-buffer)
	    doing
	    (when (eq (fragment-of-mark a-mark) fragment)
	      (let ((index-of-a-mark (index-of-mark a-mark)))
		(when (or (<f index-of-mark index-of-a-mark)
			  (and (= index-of-mark index-of-a-mark)
			       (eq :forward (direction-of-mark a-mark))))
		  (incf (index-of-mark a-mark) length-of-insert)
		  ))))

      ;; Return the mark
      mark)))

(defun insert-text-at-mark (mark text)
  (insert-subtext-at-mark mark text 0 (length text)))

(defun insert-subtext-at-mark (mark text start end)
  (with-bindings ((fragment text-of-fragment length-of-fragment max-of-fragment) (mark))
    (let* ((length-of-insert (-f end start)))
      (cond
	((<f (+f length-of-insert length-of-fragment) max-of-fragment)
	 (insert-subtext-into-roomy-fragment mark text 0 length-of-insert))
	(t
	 (insert-subtext-by-spliting-fragment mark text start end))))
    mark))

(defun split-fragment (mark)
  (with-bindings ((fragment next-fragment? index-of-mark
			    length-of-fragment text-of-fragment) (mark))
    (let ((new-fragment (make-rb-fragment)))

      ;; Link the fragment into the fragment chain.
      (setf (next-fragment-of-fragment new-fragment) next-fragment?)
      (setf (next-fragment-of-fragment fragment) new-fragment)

      ;; Set the integers in the new fragment
      (setf (length-of-fragment new-fragment) (-f length-of-fragment index-of-mark))
      (setf (position-of-fragment new-fragment)
	    (+f (position-of-fragment fragment) index-of-mark))

      ;; Revise the length of the spit fragment.
      (setf (length-of-fragment fragment) index-of-mark)

      ;; Copy the spit off text from the old to the new fragment.
      (loop with text-of-new-fragment = (text-of-fragment new-fragment)
	    for src from index-of-mark below length-of-fragment
	    for dst from 0
	    do (setf (char text-of-new-fragment dst)
		     (char text-of-fragment src))))

    ;; Return the old fragment
    fragment))

(defun insert-subtext-by-spliting-fragment (mark text start end)
  (let* ((left-fragment (split-fragment mark))
	 (right-fragment (next-fragment-of-fragment left-fragment)))
    ;; Make-new-fragments
    (let* ((length-of-insert (-f end start))
	   (first-of-inserted-fragments (make-rb-fragment))
	   (last-of-inserted-fragments first-of-inserted-fragments))

      ;; Cons up the new fragments
      (loop
	with position-so-far = (position-of-fragment right-fragment)
	for start-of-bit = start then end-of-bit
	as end-of-bit = (min (+f start-of-bit default-fragment-bit-size)
			     end)
	as length-of-bit = (-f end-of-bit start-of-bit)

	doing				;
	;; Set the position & length of the new fragment
	(setf (length-of-fragment last-of-inserted-fragments) length-of-bit)
	(setf (position-of-fragment last-of-inserted-fragments) position-so-far)
	(incf position-so-far length-of-bit)

	;; Copy the Text
	(loop with dst-text = (text-of-fragment last-of-inserted-fragments)
	      for src-i fixnum from start-of-bit below end-of-bit
	      for dst-i fixnum from 0
	      doing
	  (setf (char (the simple-string dst-text) dst-i)
		(char (the simple-string text) src-i)))
	(when (= end-of-bit end) (return));; EXIT
	(setf (next-fragment-of-fragment last-of-inserted-fragments)
	      (setf last-of-inserted-fragments (make-rb-fragment))))

      ;; Splice that into the fragment chain.
      (setf (next-fragment-of-fragment left-fragment) first-of-inserted-fragments)
      (setf (next-fragment-of-fragment last-of-inserted-fragments) right-fragment)

      ;; Adjust the position of the following fragments.
      (loop for next-fragment?
		= (next-fragment-of-fragment last-of-inserted-fragments)
		then (next-fragment-of-fragment next-fragment?)
	    while next-fragment?
	    do (incf (position-of-fragment next-fragment?) length-of-insert))

      ;; Adjust all the marks residing in the old fragment that
      ;; are to the right of the insertion point.
      (loop with index-of-split = (length-of-fragment left-fragment)
	    for a-mark in (marks-of-resource-buffer (resource-buffer-of-mark mark))
	    as fragment-of-mark = (fragment-of-mark a-mark)
	    doing
	;; Only marks that think they are in the old, now split
	;; fragment can be affected by this insert.
	(when (eq fragment-of-mark left-fragment)
	  (let ((a-index (index-of-mark a-mark)))
	    (when (or (<f index-of-split a-index)
		      (and (=f index-of-split a-index)
			   (eq :forward (direction-of-mark a-mark))))
	      (mark-move a-mark length-of-insert)))))

      ;; Return the given mark
      mark)))


(defun insert-character-at-mark (mark character)
  (let ((hack (obtain-gensym-string 1)))
    (setf (char hack 0) character)
    (insert-text-at-mark mark hack)
    (reclaim-gensym-string hack))
  nil)

;; My my this needs improvement!



;;; `With-typing-at-mark' abstraction that might support
;;; efficent typing into a buffer.

(defmacro with-typing-at-mark ((mark) &body body)
  `(macrolet ((type (c) (list 'insert-character-at-mark ',mark c)))
     ,@body))









;;;; Parsing From a Buffer


(defmacro with-buffer-parsing ((mark) &body body)
  `(let* ((mark ,mark)
	  (current-left-of-parsing (mark-copy mark))
	  (current-right-of-parsing (mark-copy mark)))
     (declare (special current-left-of-parsing
		       current-right-of-parsing))
     (prog1
	 (progn ,@body)
       (mark-kill current-left-of-parsing)
       (mark-kill current-right-of-parsing))))

(defun characters-available-for-parsing ()
  (declare (special current-left-of-parsing
		    current-right-of-parsing))
  (let ((mark current-right-of-parsing))
    (with-bindings ((fragment
		      position-of-mark
		      resource-buffer
		      fragments-of-resource-buffer
		      end-position-of-buffer)
		    (mark))
      (-f end-position-of-buffer position-of-mark))))

(defun get-simple-text-from-last-scan ()
  (declare (special current-left-of-parsing
		    current-right-of-parsing))
  (copy-text-between-marks current-left-of-parsing
			   current-right-of-parsing))

(defun undo-last-scan ()
  (declare (special current-left-of-parsing
		    current-right-of-parsing))
  (mark-set current-right-of-parsing current-left-of-parsing))

;;; `With-scanner' serves two functions.  First it establishes
;;; some lexical macros to make scanning functions more concise.
;;;   return-scan-ok
;;;   return-scan-bad
;;;   getchar
;;;   peek
;;;   advance.
;;; Secondly, and more fundimental, it will undo the scanning
;;; if return-scan-bad is used to exit.  The return-scan-bad
;;; value is nil.

(defmacro with-scanner (() &body body)
  `(let ()
     (declare (special current-left-of-parsing
		       current-right-of-parsing))
     ;; Slam the left and right together at the current right edge
     (mark-set current-left-of-parsing current-right-of-parsing)
     (block :scan-body
       (macrolet ((return-scan-ok (value)
		    (list 'return-from :scan-body value))
		  (return-scan-bad ()
		    '(progn
		      ;; Reset the right back to were we started.
		      (mark-set current-right-of-parsing
		       current-left-of-parsing)
		      (return-from :scan-body nil)))
		  (getchar ()
		    '(mark-get-character current-right-of-parsing))
		  (peek ()
		    '(mark-peek-character current-right-of-parsing))
		  (advance ()
		    '(mark-move current-right-of-parsing 1))
		  (retreat ()
		    '(mark-move current-right-of-parsing -1)))
	 ,@body))))


(defun scan-move (delta)
  (with-scanner ()
    (mark-move current-right-of-parsing delta)))

(defun scan-text (text)
  (with-scanner ()
    (loop for i from 0 below (length text)
	  unless (eq (char text i) (getchar))
	  do (return-scan-bad)
	  finally (return-scan-ok t))))

(defun scan-integer ()
  (with-scanner ()
    (loop
      with result? = nil
      as char = (peek)
      as digit? = (and char (digit-char-p char)) doing
      (cond
	((null digit?)
	 (if result?
	   (return-scan-ok  result?)
	   (return-scan-bad)))
	(result?
	 (setf result? (+f (*f 10 result?) digit?)))
	(t
	 (setf result? digit?)))
      (advance))))

(defun scan-zero-or-more-spaces-and-tabs ()
  (with-scanner ()
    (loop
      for char = (peek)
      while (or (eq char #\space)
		(eq char #\tab))
      do (advance)
      finally (return-scan-ok t))))

(defun scan-one-or-more-spaces-and-tabs ()
  (with-scanner ()
    (loop
      for result = nil then t
      for char = (peek)
      while (or (eq char #\space)
		(eq char #\tab))
      do (advance)
      finally
      (if result
	  (return-scan-ok result)
	  (return-scan-bad)))))

;;; `scan-to-end-of-line' spans upto
;;; the first of:
;;;   (a) end of buffer,
;;;   (b) LF, or
;;;   (b) CR, 

(defun scan-to-end-of-line ()
  (with-scanner ()
    (loop
      for result = nil then t
      for char = (peek)
      when (or (null char)
	       (eq char #\return)
	       (eq char #\linefeed))
	return (return-scan-ok t)
      doing (advance))))

;;; `Scan-line-termination' succeeds it can span
;;; a CR or CRLF.

(defun scan-line-termination ()
  (with-scanner ()
    (let ((line-terminator? (peek)))
      (cond
	((eq line-terminator? #\return)
	 (advance)
	 (when (eq (peek) #\linefeed)
	   (advance))
	 (return-scan-ok t))
	(t
	 (return-scan-bad))))))

;;; `scan-to-beginning-of-next-line' spans
;;; as if (scan-to-end-of-line) followed by
;;; (scan-line-termination).  But it returns
;;; true only if more data follows this.

(defun scan-to-beginning-of-next-line ()
  (with-scanner ()
    (scan-to-end-of-line)
    (let ((line-terminator (peek)))
      (advance)
      (when (and (eq line-terminator #\return)
		 (eq (peek) #\linefeed))
	(advance)))
    (if (peek)
	(return-scan-ok t)
	(return-scan-bad))))

(defun scan-blank-line ()
  (with-scanner ()
    (cond
      ((let ((next-char (peek)))
	 (or (eq #\return next-char)
	     (eq #\linefeed next-char)))
       (scan-to-beginning-of-next-line)
       (return-scan-ok t))
      (t
       (return-scan-bad)))))

(defun scan-upto-character (character)
  (with-scanner ()
    (loop
      as c? = (peek)
      when (not c?) do (return-scan-bad)
      when (eq c? character) do (return-scan-ok t)
      doing (advance))))

(defun string-member (char string)
  (loop for i from 0 below (length string)
	when (char= char (char string i)) do (return t)))

(defun scan-upto-member-of-bag (bag)
  (with-scanner ()
    (loop
      as c? = (peek)
      when (not c?) do (return-scan-bad)
      when (string-member c? bag) do (return-scan-ok c?)
      doing (advance))))

(defun scan-upto-end ()
  (with-scanner ()
    (loop until (not (peek)) do (advance))
    (return-scan-ok t)))

(defun scan-symbol ()
  (with-scanner ()
    (unless (and (peek)
		 (alpha-char-p (peek)))
      (return-scan-bad))
    (loop
      as c? = (peek)
      while c?
      when (not (or (alphanumericp c?)
		    (eq c? #\_)
		    (eq c? #\-)))
	do  (let* ((text (get-simple-text-from-last-scan))
		   (result (gsi-web-intern (nstring-upcase text))))
	      (reclaim-gensym-string text)
	      (return-scan-ok result))
      doing (advance))))

(defun gsi-web-intern (string)
  (cond
    ((string= string "INTEGER") 'integer)
    ((string= string "SYMBOL") 'symbol)
    ((string= string "STRING") 'string)
    (t (intern string ab-package-1))))

;; "Ask me about my vow of silence."


(defun scan-over-filename ()
  (with-scanner ()
    (macrolet ((filename-char-p (c?)
		 `(and ,c?
		       (not
			 (eq ,c? #\tab)))))
      (loop for c? = (peek)
	    while (filename-char-p c?)
	    do (advance))
      ;;Now, let's back up if there are any space chars. Kinna klugey, because
      ;;we have to START by backing up, since we are past the end, and when
      ;;we're all done we have to go forward over the last char of the filename.
      ;;We allow spaces WITHIN filenames, but we need to trim them off the end.
      ;;Except, if we didn't actually GO anywhere, because it was already at
      ;;the end, don't back up.
      (unless (=f (position-of-mark current-left-of-parsing)
		  (position-of-mark current-right-of-parsing))
	(retreat)
	(loop while (eq (peek) #\space) do (retreat))
	(advance)))
    (return-scan-ok t)))








;;;; A Tokenizer

;;; I wish!

;;; Presumably a tokenizers would be like marks, execpt they
;;; would offer the services:
;;;    type-of-next-token
;;;    next-token
;;; These could then be written for various tokenizing families.
;;; C, URL, etc.







;;;; Describe Method

#+development
(def-development-describer describe-mark (mark)
  (when (rb-mark-p mark)
    (with-bindings ((resource-buffer fragment position-of-mark)
		    (mark))
      (format t "~&Mark ~S at ~D in ~S f: ~S"
	      mark position-of-mark resource-buffer fragment))
  t))

#+development
(def-development-describer describe-resource-buffer (resource-buffer)
  (when (r-buffer-p resource-buffer)
    (describe-gensym-structure resource-buffer)
    (format t "~&------")
    (loop for (key value)
	  on (plist-of-resource-buffer resource-buffer) by #'cddr
	  for i from 0 by 2
	  doing
      (describe-slot-in-frame-or-structure
	i nil key value))
    t))


