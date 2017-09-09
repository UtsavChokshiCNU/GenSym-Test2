; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")


;;;; Module ALPHABET

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; John Valente






;;;; Auxiliary Functions


(declare-forward-references
  (tokenize-number-from-user function)
  (make-runtime-float-for-tokenizer function edit1)
  (make-runtime-long-for-tokenizer function edit1)
  )



;;; `character-class-relationship' - is a special case of alphabet
;;; transition relationship, when both transitions are character
;;; classes.
;;;
;;; This function is not specific to a particular alphabet and so
;;; doesn't really belong here.  It's also horribly inefficient.
;;; I'm putting it here at the top of the file so that I'm
;;; reminded of its ugliness (if not downright incorrectness)
;;; whenever I open the file.  - jv 1/8/97

(defun-simple gensym-set-difference-using-equal (list1 list2)
  (loop for element1 in list1
        unless (loop for element2 in list2
                     thereis (equal element1 element2))
          collect element1 using gensym-cons))

(defun-simple gensym-intersection-using-equal (list1 list2)
  (loop for element1 in list1
        when (loop for element2 in list2
                   thereis (equal element1 element2))
          collect element1 using gensym-cons))

(defun-simple gensym-set-difference-using-equal-non-empty-p (list1 list2)
  (loop for element1 in list1
        unless (loop for element2 in list2
                     thereis (equal element1 element2))
          return t))

(defun-simple gensym-intersection-using-equal-non-empty-p (list1 list2)
  (loop for element1 in list1
        when (loop for element2 in list2
                   thereis (equal element1 element2))
          return t))

(defun-simple character-class-relationship (args1 args2)
  (let ((args1-only
          (gensym-set-difference-using-equal-non-empty-p args1 args2))
        (args2-only
          (gensym-set-difference-using-equal-non-empty-p args2 args1))
        (intersection
          (gensym-intersection-using-equal-non-empty-p args1 args2)))
    (prog1
        (cond
          ((not intersection)
           'disjoint)
          ((not args1-only)
           (if (not args2-only)
               'equiv
               'sub1))
          ((not args2-only)
           'sub2)
          (t
           'range-overlap)))))



;;; `valid-token-actions'

(defvar valid-token-actions '())

#+development
(setq valid-token-actions '())  ;; for recompiling file


;;; `valid-token-action-p'

(defmacro valid-token-action-p (name)
  `(memq-p-macro ,name valid-token-actions))


;;; `expand-def-token-action'

(defun-for-macro expand-def-token-action (name lambda-list body)
  #+development
  (unless (=f 3 (length lambda-list))
    (error "Token actions must take three arguments: string, start and end."))
  (if (loop for arg in lambda-list
            thereis (or (not (symbolp arg))
                        (eq '&optional arg)
                        (eq '&key arg)
                        (eq '&rest arg)))
      (error "Argument lists for simple functions cannot contain &optional, ~
              &key, &rest, or non-symbol arguments.")
      (multiple-value-bind (declaration-and-documentation inner-body)
          (split-defun-body body)
        `(progn
           (declare-function-type ,name
                                  ,(fill (copy-list lambda-list) t)
                                  (t))
           ,(if (and (eval-feature :chestnut-3)
                     (not (eval-feature :chestnut-3-2-7))
                     (eval-feature :chestnut-trans)
		     (not (or (eval-feature :sbcl) (eval-feature :lispworks) (eval-feature :clozure)))
                     (loop for arg in lambda-list
                           never (special-variable-p arg)))
                (progn (note-def-token name)
                       `(defun ,name ,lambda-list
                          ,@declaration-and-documentation
                          (gensym-return-one
                            (block ,name ,@inner-body))
                          nil))
                `(defun ,name ,lambda-list
                   ,@declaration-and-documentation
                   (values (progn ,@inner-body))))
           (push ',name valid-token-actions)
           ',name))))

;;; `def-token-action'

(defmacro def-token-action (name arguments &body declarations-and-forms)
  (expand-def-token-action name arguments declarations-and-forms))



;;; When a token is matched, it is associated with a string containing
;;; the characters which the machine consumed in matching the pattern.
;;; The "value" of the token, however, may be somewhat different than
;;; that string.  By far the most common case is that the string needs
;;; to be turned into a symbol -- that's the default.  You can specify
;;; any function to be run on the arguments string, start, and end,
;;; when the token is matched.  The following two functions are used
;;; exclusively for that purpose.  Since the tokenizer definitions are
;;; in this module, these functions need to be defined here or earlier.


;;; `no-value' - just returns nil.  This is not and should not be
;;; the default.  For the token-value of a string to be nil, this
;;; function must be specified explicitly.

(def-token-action no-value (string start end)
  (declare (ignore string start end))
  nil)


;;; `numeric-return-value' - this uses the "old" tokenizer's
;;; mechanism to get a numeric value out of a string.

(def-token-action numeric-return-value (string start end)
  (let ((number-string
          (copy-portion-of-wide-string
            string start end))
        value-or-error-string
        type-of-number
        value)
    (with-temporary-gensym-float-creation
        numeric-return-value
      (multiple-value-setq
          (value type-of-number)
        (tokenize-number-from-user
          number-string
          0
          (text-string-length number-string)))
      (setq value-or-error-string 
            (case value
              (overflow
               #w"number is too large")
              (underflow 
               #w"number is too small")
              (otherwise
               (case type-of-number
                 (float
                  (make-runtime-float-for-tokenizer value))
                 (long
                  (make-runtime-long-for-tokenizer value))
                 (otherwise
                  value)))))
      (reclaim-wide-string number-string)
      value-or-error-string)))





;;;; Alphabet Definition


;;; `alphabet-min-character' and `alphabet-max-character'
;;; `alphabet-min-code' and `alphabet-max-code'  - the alphabet
;;; should consist of a contiguous, enumerable block.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter alphabet-min-character     0)
(defparameter alphabet-max-character 65535)
(defparameter alphabet-min-code (code-wide-character alphabet-min-character))
(defparameter alphabet-max-code (code-wide-character alphabet-max-character))
(defparameter alphabet-cardinality (-f alphabet-max-code alphabet-min-code))
(defvar alphabet-standard-state-transition-tests '())
(defvar alphabet-count-of-standard-state-transition-tests 0)
(defvar list-of-already-defined-tokenizer-matching-tests '())
)


#+development
(defun reset-alphabet-standard-transition-tests ()
  (setq alphabet-standard-state-transition-tests '())
  (setq list-of-already-defined-tokenizer-matching-tests '())
  (setq alphabet-count-of-standard-state-transition-tests 0))

#+development
(reset-alphabet-standard-transition-tests)


;;; `variable-naming-standard-transition-test'

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro variable-naming-standard-transition-test (test-name)
  `(intern (format nil "~:@(~A~)-ST-TEST" ,test-name)))
)

;;; `define-tokenizer-matching-test'

(defmacro define-tokenizer-matching-test (generic-arg specific-arg)
  (let* ((specific specific-arg)         
         (specific-name (car specific))
         (generic generic-arg)
         (variable-name (variable-naming-standard-transition-test
                          generic)))
    `(progn
       (eval-when (:compile-toplevel :load-toplevel :execute)
         (unless (member ',generic
                         list-of-already-defined-tokenizer-matching-tests)
           (push (list
                   alphabet-count-of-standard-state-transition-tests
                   ',specific-name
                   ',(length (cdr specific)))
                 alphabet-standard-state-transition-tests)
           (incff alphabet-count-of-standard-state-transition-tests)
           (push ',generic list-of-already-defined-tokenizer-matching-tests)))
       (defvar ,variable-name ',specific-name))))



;;; `alphabet-get-index-for-transition-test'

(defmacro alphabet-get-index-for-transition-test (specific-evaluator)
  `(loop for (index specific nil) in
         alphabet-standard-state-transition-tests
         when (eq ,specific-evaluator specific)
           return index
         finally
           #+development
           (cerror "Go on" "Could not find index for ~s" ,specific-evaluator)
           (return -1)))
  

;;; `make-args-for-state-transition-test'

(defun-for-macro make-args-for-state-transition-test
    (total-number-of-args)
  (loop for i from 1 below total-number-of-args
        collect
        `(prog1 (car-of-cons argument-list)
           (setf argument-list (cdr-of-cons argument-list)))))

(defun-for-macro get-macro-for-test-function (test)
  (or (cdr (assq test '((character-class-member-p .
                         character-class-member-p-macro))))
      test))

;;; `make-fixnum-case-form-for-apply-state-transition'

(defmacro make-fixnum-case-form-for-apply-state-transition (transition element)
  `(fixnum-case (state-transition-index-of-test ,transition)
     ,@(loop for (index specific arg-count)
                 in alphabet-standard-state-transition-tests
             as specific-macro = (get-macro-for-test-function specific)
             collect
             (case arg-count
               (0
                `(,index
                    (,specific-macro)))
               (1
                `(,index
                    (,specific-macro
                       ,element)))
               (2
                `(,index
                    (,specific-macro
                       ,element
                       (car-of-cons (state-transition-args transition)))))
               (t
                `(,index
                    (let ((argument-list (state-transition-args transition)))
                      (,specific-macro
                         ,element ,@(make-args-for-state-transition-test
                                      arg-count)))))))))




;;; `alphabet-canonical-element'

(define-tokenizer-matching-test alphabet-canonical-element
    (wide-character-p element))
  

;;; `alphabet-equality'

(define-tokenizer-matching-test alphabet-equality
    (char=w element arg1))


;;; `alphabet-character-class'

(define-tokenizer-matching-test alphabet-character-class
    (character-class-member-p element arg1))




;;; `alphabet-preds-with-card>2' is important to know because any
;;; of the functions contained herein can then be assumed to be
;;; a proper superset of the alphabet-equality function for a particular
;;; argument, given that it is a superset.

(defparameter alphabet-preds-with-card>2
  '(wide-character-p-function
    wide-character-p
    alphanumericpw-function
    alpha-char-pw-function
    hexadecimal-digit-char-pw-function
    decimal-digit-char-pw-function
    
    string-char-pw-function
    standard-char-pw-function
    upper-case-pw-function
    lower-case-pw-function
    graphic-char-pw-function))



;;; `alphabet-subset-function' is a funcallable version of alphabet-
;;; subset.
;;;
;;; For example,
;;;   (funcall (alphabet-subset-function alph1) #'char= '(#\a)
;;;                                             #'alpha-char-p nil)

(defvar alphabet-subset-function 'alphabet-transition-relationship)



;;; `alphabet-between' and `alphabet-not-between' - used to test
;;; membership in a character class.  They must be functions,
;;; not macros, so they can be funcalled.  Must take three
;;; arguments -- all fixnums!  If the members of the alphabet
;;; are not fixnums, this is the place to make the conversion.
;;; The arguments on the range transitions should always be fixnums
;;; regardless of the character encoding.  These functions may
;;; assume that the second argument is less than the third, since
;;; we sort the character classes when we build the DFA.  These
;;; are run-time functions.

(defmacro alphabet-between (test-fixnum min-fixnum max-fixnum)
  `(<=f ,min-fixnum ,test-fixnum ,max-fixnum))

(defmacro alphabet-not-between (test-fixnum min-fixnum max-fixnum)
  `(or (<f ,test-fixnum ,min-fixnum)
       (>f ,test-fixnum ,max-fixnum)))


;;; `alphabet-canonical-element-p' is a predicate which returns t if
;;; its argument is a canonical element of the alphabet.  

(defmacro alphabet-canonical-element-p (thing)
  `(wide-character-p ,thing))


;;; `alphabet-canonical-string-p' returns t if it's argument is
;;; the proper input format for the language.

(defmacro alphabet-canonical-string-p (thing)
  `(wide-string-p ,thing))


;;; `alphabet-eql' takes two arguments and returns non-nil
;;; if the two arguments are the same.

(defmacro alphabet-eql (thing-1 thing-2)
  `(char=w ,thing-1 ,thing-2))


;;; `alphabet-valid-subset-responses' - functions in TOKEN have hardcoded
;;; understanding of the meaning of these symbols, so they cannot be
;;; casually changed.

(defconstant alphabet-valid-subset-responses
  '(equiv sub1 sub2 disjoint overlap range-overlap))


;;; `alphabet-subset' is used to determine if one transition
;;; is a subset of another one.  For example, over Lisp characters, the
;;; function "digit-char-p" is a subset of "characterp".  The subset
;;; function must take two transitions as arguments. It must return a
;;; symbol from the list `alphabet-valid-subset-responses'.

(defmacro alphabet-subset (test1 args1 test2 args2)
  `(alphabet-transition-relationship ,test1 ,args1 ,test2 ,args2))


;;; `alphabet-members' should be a list of every member of
;;; the alphabet.  This list can be used to help with the
;;; subset function.  We want to allow arbitrary functions
;;; to be used 

(defvar alphabet-members
  (loop for i from alphabet-min-code to
        ;; alphabet-max-code
        127
        collect (code-wide-character i)))



;;; `alphabet-string-toupper' - returns the upper-case version
;;; of the given string, presumably destructively.

(defmacro alphabet-string-toupper (string)
  `(nstring-upcasew ,string))



;;; `alphabet-text-string-length' - returns the length of a text string
;;; in the current alphabet.

(defmacro alphabet-text-string-length (text-string)
  `(wide-string-length ,text-string))



;;; `alphabet-intern-string' - returns the symbol in the current
;;; package which is named by the given string.

(defmacro alphabet-intern-string (text-string)
  `(intern-wide-string ,text-string))



;;; `alphabet-substring' - creates a new string and copies the
;;; specified substring of the source string into it.

(defmacro alphabet-substring (text-string start end)
  `(copy-portion-of-wide-string ,text-string ,start ,end))



;;; `alphabet-twrite-character' - writes the given character
;;; into the current twriting buffer space.

(defmacro alphabet-twrite-character (wide-char)
  `(twrite-wide-character-macro ,wide-char))


;;; `alphabet-twrite-portion-of-string' - writes the specified
;;; substring into the current twriting buffer space.

(defmacro alphabet-twrite-portion-of-string (string start end)
  `(twrite-portion-of-wide-string-unparsably-to-current-wide-string
     ,string ,start ,end))
  

;;; `alphabet-substring-for-symbol' - normalize means that unescaped lower-case
;;; letters are converted to upper case, and escape characters are removed to
;;; make the symbol.

(defmacro alphabet-substring-for-symbol
    (wide-string start end &optional (normalize-p nil))
  `(twith-output-to-text-string
     (alphabet-twrite-substring-for-symbol
       ,wide-string ,start ,end ,normalize-p)))

(defmacro alphabet-twrite-substring-for-symbol
    (wide-string start end &optional (normalize-p nil))
  (let ((end-var (make-symbol "END")))
    `(loop with ,end-var = ,end
           for i from ,start
           while (<f i ,end-var)
           as char = (charw ,wide-string i)
           as char-to-write? = (cond ((char=w char #.%\@)
                                      (incff i)
                                      (unless (=f i ,end)
                                        (charw ,wide-string i)))
                                     (,normalize-p
                                      (char-upcasew char))
                                     ;; Avoid having a T clause twice:
                                     ,@(if (not (eq normalize-p 't))
                                           '((t char))))
           when char-to-write?
             do (alphabet-twrite-character char-to-write?))))


;;; `alphabet-substring-for-symbol-function'

(defun-simple alphabet-substring-for-symbol-function
    (string start end normalize-p)
  (alphabet-substring-for-symbol
    string start end normalize-p))



;;; `alphabet-symbol-from-portion-of-text' - takes a string, extracts
;;; a portion of it, possibly converts that portion to upper case, and
;;; interns a symbol from the substring.  Used for extracting the variable
;;; names and built-in classes from strings like "$(nonzero)<numeric>+".

(defmacro alphabet-symbol-from-portion-of-text
    (wide-string &optional start? end? (normalize-p t))
  `(alphabet-intern-string
     (alphabet-substring-for-symbol
       ,wide-string
       (or ,start? 0)
       (or ,end? (alphabet-text-string-length ,wide-string))
       ,normalize-p)))
         
            

;;; `alphabet-normalized-symbol-from-text-string' - a funcallable version
;;; of alphabet-symbol-from-portion-of-text

(def-token-action alphabet-normalized-symbol-from-text-string
    (string start end)
  (computing-syntactically-numeric-p 
    (let ((result (or (interning-text-character-sequence
                        (macrolet ((alphabet-twrite-character (char)
                                     `(progn
                                        (next-character-for-intern ,char)
                                        (advance-syntactically-numeric-p ,char))))
                          (alphabet-twrite-substring-for-symbol
                            string start end t))
                        (result-of-intern))
                      :nil)))
      (when (result-of-syntactically-numeric-p)
        (setf (type-of-syntactic-anomaly result) 'numeric))
      result)))



;;; `alphabet-case-sensitive-symbol-from-text-string'

(def-token-action alphabet-case-sensitive-symbol-from-text-string
    (string start end)
  (let ((result
          (or (alphabet-symbol-from-portion-of-text
                string start end nil)
              :nil)))
    (when (syntactically-numeric-p (symbol-name-text-string result))
      (setf (type-of-syntactic-anomaly result) 'numeric))
    result))


;;; `alphabet-normalized-substring-for-string' - a string does not
;;; normalize letters to upper case, but does remove escape characters.

(defmacro alphabet-normalized-substring-for-string (string start end)
  `(twith-output-to-text-string
     (loop with i = ,start
           until (>=f i ,end)
           as char = (charw ,string i)
           do
       (cond
         ((char=w char #.%\@)
          (incff i)
          (unless (=f i ,end)
            (alphabet-twrite-character (charw ,string i))))
         (t
          (alphabet-twrite-character char)))
       (incff i))))



;;; `alphabet-strip-delimitors-off-string' - all string types are
;;; delimited on both sides, by ", [, or ].  The token-value for
;;; the strings do not include the delimiters, so the function to
;;; get the token-value for strings is to strip a character off of
;;; each side.

(def-token-action alphabet-strip-delimitors-off-string (string start end)
  (alphabet-normalized-substring-for-string
    string
    (1+f start)
    (1-f end)))


;;; `alphabet-substring-function'

(def-token-action alphabet-substring-function (string start end)
  (alphabet-substring string start end))



;;; `alphabet-not-character-code-error-message'

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter alphabet-not-character-code-error-message
  (format nil "Character codes must be fixnums between ~d and ~d inclusive."
          alphabet-min-code alphabet-max-code))
)


;;; `alphabet-copy-string' - copies the source string into a
;;; fresh string.

(defmacro alphabet-copy-string (source-string)
  `(copy-wide-string ,source-string))


;;; `alphabet-copy-substring' - copies a portion of the source string
;;; into the destination string.  Performs no error checking.

(defmacro alphabet-copy-substring
    (source-string source-start destination-string destination-start
                   count-of-chars-to-copy)
  `(copy-byte-vector-16-portion
     ,source-string ,source-start
     ,destination-string ,destination-start
     ,count-of-chars-to-copy))



;;; `alphabet-string=' - returns t if the two arguments are valid
;;; words in the language and are equivalent.

(defmacro alphabet-string= (string1 string2)
  `(string=w ,string1 ,string2))


;;; `alphabet-string-element-accessor' - accesses the given
;;; character of the given string.

(defmacro alphabet-string-element (string index)
  `(charw ,string ,index))


;;; `alphabet-make-uninitialized-text-string' - returns a block of
;;; characaters of the specified length.

(defmacro alphabet-make-uninitialized-text-string (length)
  `(make-wide-string ,length))


;;; `alphabet-character-code-p' - returns t if the argument is a valid
;;; member of the character encoding.

(defmacro alphabet-character-code-p (thing)
  `(and (fixnump ,thing)
        (<=f (+f alphabet-min-code)
             ,thing
             (+f alphabet-max-code))))
  



;;; `alphabet-code-char' - returns a Common Lisp character which
;;; corresponds to the given code if one exists, the tilde
;;; character if there is no CL equivalent for the code, and
;;; an equals sign if given nil.  Used for debugging.

#+development
(defun alphabet-code-char (wide-char)
  (cond
    ((null wide-char)
     #\=)
    ((newline-p wide-char)
     #\newline)
    (t
     (or (wide-character-to-character wide-char) #\~))))


;;; `alphabet-char' - returns the CL equivalent of the character
;;; at the specified position in the string.

#+development
(defun alphabet-char (string index)
  (alphabet-code-char (charw string index)))



(defparameter alphabet-escape-character #.%\\ )
(defparameter alphabet-character-class-open #.%\{)
(defparameter alphabet-character-class-close #.%\})
(defparameter alphabet-character-class-range #.%-)

(defparameter alphabet-dollar-sign #.%$)
(defparameter alphabet-less-than-sign #.%<)





;;;; Built-in Character Classes

;;; These are obviously just parameters, but they are used in TOKEN
;;; to form built-in-classes.

(defparameter alphabet-alphabetic-chars
  '((#.%\a . #.%\z) (#.%\A . #.%\Z)))

(defparameter alphabet-numeric-chars
  '((#.%\0 . #.%\9)))

(defparameter alphabet-hexadecimal-chars
  '((#.%\0 . #.%\9) (#.%\a . #.%\f) (#.%\A . #.%\F)))

(defparameter alphabet-g2symbol-chars
  '((#.%\0 . #.%\9) (#.%\a . #.%\z) (#.%\A . #.%\Z) #.%\- #.%\_ #.%\' #.%\.))

(defparameter alphabet-alphanumeric-chars
  '((#.%\0 . #.%\9) (#.%\a . #.%\z) (#.%\A . #.%\Z)))

(defparameter alphabet-whitespace-chars
  '(#.%line-separator #.%space #.%newline #.%return #.%linefeed
    #.%paragraph-separator #.%tab))

(defparameter alphabet-double-quote-chars '(#.%\"))

(defparameter alphabet-left-bracket-chars '(#.%\[))

(defparameter alphabet-right-bracket-chars '(#.%\]))


(defconstant alphabet-editor-legal-whitespace-chars
  '(#.%line-separator #.%return #.%linefeed #.%hair-space #.%tab
    #.%thin-space #.%en-space #.%em-space)) ;; not for em-space?

(defconstant alphabet-zero-width-characters
  '(#.%zero-width-space #.%zero-width-joiner))
    
(defconstant alphabet-whitespace-characters
  '(#.%line-separator #.%return #.%linefeed #.%hair-space #.%tab
    #.%thin-space #.%en-space #.%em-space #.%zero-width-space
    #.%zero-width-joiner #.%paragraph-separator
    #.%space))


(defparameter alphabet-punctuation-characters
  '(#.%\< #.%\> #.%\/  #.%\+ #.%\: #.%\{ #.%\} #.%\"
    #.%\! #.%\# #.%\$ #.%\% #.%\& #.%\' #.%\( #.%\) #.%\* #.%\, #.%\- #.%\.
    #.%\; #.%\= #.%\? #.%\@ #.%\[ #.%\\ #.%\] #.%\^ #.%\_ #.%\` #.%\| #.%\~))


(defparameter sentence-end-punctuation-characters
  '(#.%\? #.%\. #.%\!))    ; used by 

;; Expand for international cases!  Spanish upside-down ? and !, et al.



;;; `characters-not-allowed-in-symbols-in-g2-50r0' - this list was 
;;; determined by running simple-symbol-character-p on all 65536
;;; characters in Unicode.  I don't think that it is really what
;;; it should be, but simple-symbol-character-p is what we were
;;; going to use anyway, so this will be exactly the same.  This
;;; list could use some refinement for 5.0r1.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter characters-not-allowed-in-symbols-in-g2-50r0
  ;; Not allowed, that is, without being quoted with '@'
  '(%tab %space %line-separator %paragraph-separator
    ;; %ordinary-space - should be the same as %space, i.e.,
    ;; decimal 32, but is defined as 0x32, which is decimal 50,
    ;; which should be the character '2'.
    %\!  %\"  %\#  %\$  %\%  %\&  %\(  %\)  %\*  %\+  %\,  %\/
    %\:  %\;  %\<  %\=  %\>  %\?  %\@  %\[  %\\  %\]  %\^  %\`
    %\{  %\|  %\}  %\~
    %copyright-sign %registered-sign %trade-mark-sign %bullet
    %latin-small-letter-f-with-hook
    %inverted-exclamation-point %cent-sign %pound-sign %yen-sign
    %right-pointing-double-angle-quotation-mark
    %left-pointing-double-angle-quotation-mark %inverted-question-mark))
)



;;; `evaluate-and-sort-list' - the hardcoded list above contains the
;;; symbols for the constants that we use to represent unicode
;;; characters.  There are two good reasons for that: (a) it makes
;;; it easier to understand; (b) the characters are different in
;;; development and production; we'd need to run code-wide-character
;;; on each one to make them the same.  That's already done in the
;;; constants (i.e., %a is 65 in production, 1000065 in development.)
;;; So, we use this macro to eval all the constants and then sort
;;; them.  The character-class predicate for the tokenizer specification
;;; works with a sorted list of integers, so this is all we need to do.

(defmacro evaluate-and-sort-list (unsorted-list)
  `(sort
     (loop for character-constant-name in
           ,unsorted-list
           collect (symbol-value character-constant-name))
     #'<))


;;; `alphabet-nonsymbol-character-codes-sorted-by-encoding' - the
;;; list of encodings of characters which need to be quoted to be
;;; included in symbols in G2 5.0.

(defparameter alphabet-nonsymbol-character-codes-sorted-by-encoding
  (evaluate-and-sort-list characters-not-allowed-in-symbols-in-g2-50r0))


;;; `alphabet-illegal-codes-character-class'

(defparameter alphabet-illegal-codes-character-class
  (evaluate-and-sort-list
    '(%# %\`
      %copyright-sign %registered-sign %trade-mark-sign %bullet
      %latin-small-letter-f-with-hook
      %inverted-exclamation-point %cent-sign %pound-sign %yen-sign
      %right-pointing-double-angle-quotation-mark
      %left-pointing-double-angle-quotation-mark %inverted-question-mark)))


;;; `validate-characters-not-allowed-in-symbols-in-g2-50r0' - returns
;;; nil if all is well, a list of problems otherwise.

#+development
(defun validate-characters-not-allowed-in-symbols-in-g2-50r0 ()
  (loop for code from alphabet-min-code to alphabet-max-code
        as simple-symbol-char-p = (simple-symbol-character-p code)
        as code-invalid-in-50r0-symbol?
           = (member code
                     alphabet-nonsymbol-character-codes-sorted-by-encoding)
        unless (or (and simple-symbol-char-p
                        (not code-invalid-in-50r0-symbol?))
                   (and (not simple-symbol-char-p)
                        code-invalid-in-50r0-symbol?))
          collect code))
            

;;; `alphabet-make-range-from-list-of-characters-to-exclude' - takes
;;; a list of characters in the alphabet, and produces a list of
;;; ranges which is the set-difference of the entire alphabet minus
;;; the given list.

(defmacro alphabet-make-range-from-list-of-characters-to-exclude
    (sorted-list-of-characters-to-exclude)
  `(loop with first-char
           = (car ,sorted-list-of-characters-to-exclude)
         with result = (if (=f alphabet-min-code first-char)
                           '()
                           (list (cons alphabet-min-code
                                       (1-f first-char))))
         for (number1 number2) on ,sorted-list-of-characters-to-exclude
         while number2
         as diff = (-f number2 number1)
         when (>f diff 1) do
             (push (cons (1+f number1) (1-f number2)) result)
         finally
           (when (/=f number1 alphabet-max-code)
             (push (cons (1+f number1) alphabet-max-code)
                   result))
           (return (nreverse result))))



;;; `alphabet-symbol-character-class' - actually the much more important
;;; of the two lists being added here, it is the set of ranges of
;;; characters which can be put into symbols in G2 5.0r0 without being
;;; quoted.

(defparameter alphabet-symbol-character-class
  (alphabet-make-range-from-list-of-characters-to-exclude
    alphabet-nonsymbol-character-codes-sorted-by-encoding))



;;;; Tokenizer Specifications


;;; `generally-ambiguous-characters-in-g2-tokenization'

(defparameter generally-ambiguous-characters-in-g2-tokenization
  '((#.%\] right-string (self-terminating-punctuation-mark \]))))


;;; `g2-standard-tokens'

;;; the stand-alone parser wants to be able to recognize comments, so jv added
;;; g2-comment-recognizing-tokens (2/1/05), which was substantially similar to
;;; g2-standard-tokens.  Thus, separate out the common pieces below, and define
;;; both variables, plus g2-simple-tokens, to include the common bits.
;;; yduJ, 2/3/05

(defparameter g2-standard-tokens-head
  `(((symbol-char
       (either
         (seq #.%\@ (dot))
         (character-class ,alphabet-symbol-character-class)))
     (digit-char (character-class ((#.%\0 . #.%\9))))
     (optional-unary-minus (maybe #.%\-))
     (optional-sign (maybe (either #.%\+ #.%\-)))
     (exponent-part (seq (either #.%\E #.%\e)
                         (pattern optional-sign)
                         (plus (pattern digit-char))))
     (long-mark #.%\L)
     (whitespace-char
       (either #.%return #.%linefeed #.%newline #.%line-separator
               #.%paragraph-separator #.%space #.%tab))  
     (string-char (inverted-class (#.%\" #.%\@ #.%\[)))
     ;; (string-char (inverted-class (#.%\" #.%\@ #.%\[ #.%\`)))
     (open-bracket-character #.%\[)
     ;; (open-bracket-character (either #.%\[ #.%\`))
     (close-bracket-character #.%\])                                    
     ;; (close-bracket-character (either #.%\] #.%\`))
     )))


(defparameter g2-standard-tokens-middle-strings
  `((left-string
      (seq #.%\"
           (kleene (either (seq #.%\@ (dot))
                           (pattern string-char)))
           (pattern open-bracket-character))
      alphabet-strip-delimitors-off-string)
    (middle-string
      (seq (pattern close-bracket-character)
           (kleene (either (seq #.%\@ (dot))
                           (pattern string-char)))
           (pattern open-bracket-character))
      alphabet-strip-delimitors-off-string)
    (right-string
      (seq (pattern close-bracket-character)
           (kleene (either (seq #.%\@ (dot))
                           (pattern string-char)))
           #.%\")
      alphabet-strip-delimitors-off-string)))



(defparameter g2-standard-tokens-middle-1
  `((integer
      (seq
        (pattern optional-unary-minus)
        (plus (pattern digit-char)))
      numeric-return-value)
    (float
      (seq
        (pattern optional-unary-minus)
        (either
          (seq (plus (pattern digit-char)) (pattern exponent-part))
          (seq (plus (pattern digit-char))
               #.%\. (kleene (pattern digit-char))
               (maybe (pattern exponent-part)))
          (seq #.%\. (plus (pattern digit-char))
               (maybe (pattern exponent-part)))))
      numeric-return-value)
    (long
      (seq
       (pattern optional-unary-minus)
       (plus (pattern digit-char))
       (pattern long-mark))
     numeric-return-value)
    (symbol
      (plus (pattern symbol-char)))))



(defparameter g2-standard-tokens-tail
  `((whole-string
      (seq #.%\"
           (kleene (either (seq #.%\@ (dot))
                           (pattern string-char)))
           #.%\")
      alphabet-strip-delimitors-off-string)
    (single-line-comment   ;; actually, an uncompleted single-line-comment
      (seq #.%\/ #.%\/ (kleene (inverted-class (#.%return #.%linefeed #.%newline
                                                          #.%line-separator
                                                          #.%paragraph-separator))))
      no-value)
    (comment   ;; actually, an uncompleted-comment
      (seq #.%\{ (seq (kleene (inverted-class (#.%\})))))
      no-value)
    (quoted-character
      #.%@
      no-value)
    (punctuation-mark
      (either (seq #.%\< #.%\=)
              (seq #.%\> #.%\=)
              (seq #.%\/ #.%\=)
              (seq #.%\+ #.%\-)
              (seq #.%\: #.%\:)
              #.%\<
              #.%\>
              #.%\/
              #.%\+
              #.%\:))
    (self-terminating-punctuation-mark
      (either #.%\=
              #.%\*
              #.%\^
              #.%\(
              #.%\)
              #.%\[
              #.%\]
              #.%\,
              #.%\;
              #.%\?
              #.%\!
              #.%\|
              #.%\$
              #.%\%
              #.%\&))
    (punctuation-mark
      #.%\\ )
    (punctuation-mark
      #.%\~ )
    (illegal-character
      (character-class
        ,alphabet-illegal-codes-character-class))
    ))



(defparameter g2-standard-tokens
  `(,@g2-standard-tokens-head
      (do-nothing
          (either
            (plus (pattern whitespace-char))
            (seq #.%\/ #.%\/ (kleene (inverted-class (#.%return #.%linefeed #.%newline
                                                                #.%line-separator
                                                                #.%paragraph-separator)))
                 (either #.%return #.%linefeed #.%newline
                         #.%line-separator
                         #.%paragraph-separator))
            (seq #.%\{ (seq (kleene (inverted-class (#.%\}))) #.%\}))))
      (disambiguated-token ;ambiguity because / might precede non-comment char
        (seq #.%\/ (inverted-class (#.%\/ #.%\=))))
      ,@g2-standard-tokens-middle-1
      ,@g2-standard-tokens-middle-strings
      ,@g2-standard-tokens-tail))

(defparameter g2-comment-recognizing-tokens
  `(,@g2-standard-tokens-head
      (do-nothing
          (plus (pattern whitespace-char)))
      ,@g2-standard-tokens-middle-1
      ,@g2-standard-tokens-middle-strings
      (g2-comment
        ;; note, COMMENT is used for an uncompleted comment (in most-of-g2-standard-tokens)
        (either
          (seq #.%\/ #.%\/ (kleene (inverted-class (#.%return #.%linefeed #.%newline
                                                              #.%line-separator
                                                              #.%paragraph-separator)))
               (either #.%return #.%linefeed #.%newline
                       #.%line-separator
                       #.%paragraph-separator))
          (seq #.%\{ (seq (kleene (inverted-class (#.%\}))) #.%\}))
          )
        alphabet-substring-function)
      ,@g2-standard-tokens-tail
      ))


(defparameter g2-simple-tokens
  `(((symbol-char
       (either
         (seq #.%\@ (dot))
         (character-class ,alphabet-symbol-character-class)))
     (digit-char (character-class ((#.%\0 . #.%\9))))
     (optional-unary-minus (maybe #.%\-))
     (long-mark #.%\L)
     (optional-sign (maybe (either #.%\+ #.%\-)))
     (exponent-part (seq (either #.%\E #.%\e)
                         (pattern optional-sign)
                         (plus (pattern digit-char))))
     (whitespace-char
       (either #.%return #.%linefeed #.%newline #.%line-separator
               #.%paragraph-separator #.%space #.%tab))  
     (string-char (inverted-class (#.%\" #.%\@)))
     )

    (do-nothing
        (either
          (plus (pattern whitespace-char))
          (seq #.%\/ #.%\/ (kleene (inverted-class (#.%return #.%linefeed #.%newline
                                                              #.%line-separator
                                                              #.%paragraph-separator)))
               (either #.%return #.%linefeed #.%newline
                       #.%line-separator
                       #.%paragraph-separator))
          (seq #.%\{ (seq (kleene (inverted-class (#.%\}))) #.%\}))))
    (disambiguated-token ;ambiguity because / might precede non-comment char
      (seq #.%\/ (inverted-class (#.%\/ #.%\=))))
    ,@g2-standard-tokens-middle-1
    ,@g2-standard-tokens-tail
    ))





;;; `load-kb-tokens'

(defparameter load-kb-tokens
  `(((symbol-char
       (either
         (seq #.%\@ (dot))
          #.%\(
          #.%\) 
         (character-class ,alphabet-symbol-character-class)))
     (digit (character-class ((#.%\0 . #.%\9))))
     )
    (do-nothing
        (either
          (plus (either #.%return #.%linefeed #.%newline #.%line-separator
                        #.%paragraph-separator #.%space #.%tab))
          (seq #.%\{ (seq (kleene (inverted-class (#.%\}))) #.%\}))))      
    (symbol
      (plus (pattern symbol-char)))
    (quoted-character
      #.%@
      no-value)
    (self-terminating-punctuation-mark
      (either 
        #.%\/ #.%\: #.%\$ #.%\; #.%\< #.%\> #.%\[ #.%\]
        #.%\* #.%\? #.%\! #.%\\ #.%\~))
    (self-terminating-punctuation-mark
      (either #.%\{ #.%\})
      alphabet-substring-function)))



;;; `g2-symbol-tokens'

(defparameter g2-symbol-tokens
  `(((symbol-char
       (either
         (seq #.%\@ (dot))
         (character-class ,alphabet-symbol-character-class)))
     (digit-char (character-class ((#.%\0 . #.%\9))))
     (optional-unary-minus (maybe #.%\-))
     (optional-sign (maybe (either #.%\+ #.%\-)))
     (exponent-part (seq (either #.%\E #.%\e)
                         (pattern optional-sign)
                         (plus (pattern digit-char))))
     (whitespace-char
       (either #.%return #.%linefeed #.%newline #.%line-separator
               #.%paragraph-separator #.%space #.%tab))  
     (string-char (inverted-class (#.%\" #.%\@)))
     )
    (do-nothing
        (either
          (plus (pattern whitespace-char))
          (seq #.%\{ (seq (kleene (inverted-class (#.%\}))) #.%\}))))
    (integer
      (seq
        (pattern optional-unary-minus)
        (plus (pattern digit-char)))
      no-value)
    (float
      (seq
        (pattern optional-unary-minus)
        (either
          (seq (plus (pattern digit-char)) (pattern exponent-part))
          (seq (plus (pattern digit-char))
               #.%\. (kleene (pattern digit-char))
               (maybe (pattern exponent-part)))
          (seq #.%\. (plus (pattern digit-char))
               (maybe (pattern exponent-part)))))
      no-value)
    (symbol
      (plus (pattern symbol-char)))
    (comment   ;; actually, an uncompleted-comment
      (seq #.%\{ (seq (kleene (inverted-class (#.%\})))))
      no-value)
    (double-colon
      (seq #.%\: #.%\:))
    ))



;;; `tokenizer-tokens'

(defparameter tokenizer-tokens
  '(()
    (do-nothing
        (either
         (plus (either #.%return #.%linefeed #.%newline #.%line-separator
                       #.%paragraph-separator #.%space #.%tab))
         (seq #.%\{ (seq (kleene (inverted-class (#.%\}))) #.%\}))))
    (double-quote #.%\")

    (dot #.%\.)

    (alternative #.%\|)    

    (kleene-star #.%\*)
    (question-mark #.%\?)
    (plus #.%\+)

    (left-paren #.%\()
    (right-paren #.%\))

    (left-curly-brace #.%\{)
    (right-curly-brace #.%\})
    (hyphen #.%\-)
    
    (caret #.%\^)
    (quoted-character
     #.%@)
    (regexp-character
     (either
      (seq #.%\@
           ;; alphabet-escape-character
           (dot))
      (inverted-class (#.%\. #.%\| #.%\* #.%\?
                             #.%\+ #.%\( #.%\)
                             #.%\{ #.%\} #.%\-
                             #.%\^ #.%\@))))))



;;; `regular-expression-tokens' - This module provides a mechanism for
;;; tokenizing a string.  However, the input to the tokenizer compiler must be a
;;; cons tree.  To allow the G2 user to create arbitrary tokenizers, we must
;;; provide a way to translate from g2-text to a cons tree.  So, we define a
;;; regular expression syntax, with which we need to tokenize and parse a string
;;; in order to produce a tokenizer.  A little bit of a bootstrapping problem,
;;; and it also requires a parser in order to provide a tokenizer.  Anyway, the
;;; following parameter defines the tokens for the regular expression language.
;;; For simplicity, all the tokens are single characters.

(defparameter regular-expression-tokens
  '(()
    (alternative #.%\|)    
    
    (kleene-star #.%\*)
    (dot #.%\.)
    (left-paren #.%\()
    (right-paren #.%\))
    (question-mark #.%\?)
    (plus #.%\+)
    (left-curly-brace #.%\{)

    (right-curly-brace #.%\})
    (caret #.%\^)
    (hyphen #.%\-)
    
    (regexp-character
     (either
      (seq #.%\\
           ;; alphabet-escape-character
           (dot))
      (dot)))))


;;; `regexp-macro-tokens'

(defparameter regexp-macro-tokens
  `(()
    (built-in
      (seq
        #.%\<
        (plus
          (either
            (seq #.%\\ (dot))
            (inverted-class (#.%\> #.%\\))))
        #.%\>))
    (variable
      (seq
        #.%\$
        #.%\(
        (plus
          (either
            (seq #.%\\ (dot))
            (inverted-class (#.%\) #.%\\))))
        #.%\)))
    (character-class
      (seq
        #.%\{
        (plus
          (either
            (seq #.%\\ (dot))
            (inverted-class (#.%\} #.%\\))))
        #.%\}))))


;;; `module-search-path-tokens'

(defparameter module-search-path-tokens
  `(()
    (do-nothing #.%space)
    (quoted-path
      (seq
        #.%\'
        (kleene (inverted-class (#.%\')))
        #.%\')
      alphabet-strip-delimitors-off-string)
    (unquoted-path
      (plus (inverted-class (#.%space)))
      alphabet-substring-function)))


;;; `tabular-view-row-selection-tokens'

(defparameter tabular-view-row-selection-tokens
  `(()
    (do-nothing #.%space)
    (unsigned-integer
      (plus (character-class ((#.%\0 . #.%\9))))
      numeric-return-value)
    (error
      (plus (inverted-class ((#.%\0 . #.%\9) #.%space)))
      no-value)))
