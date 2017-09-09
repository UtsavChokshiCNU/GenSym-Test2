; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module LEXER

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; John Valente




;;;; Frame notes


;;; `format-note-for-preprocessor-error'

(defun-simple format-note-for-preprocessor-error
    (name expression preprocessor-errors)
  (twith-output-to-text-string
    (twrite-symbol name t)
    (twrite-string ": unable to parse \"")
    (twrite-string expression)
    (twrite-string "\" because ")
    (if (not (consp preprocessor-errors))
        (twrite-string "it is not a valid regular expression")
        (loop with number-of-errors = (length preprocessor-errors)
              for (macro-name type-of-error) in preprocessor-errors
              as iterator from 1 do
          (case type-of-error
            (built-in
             (twrite-string "there is no built-in character class called "))
            (variable
             (twrite-string "there is no valid definition for pattern "))
            (t
             #+development
             (cerror "Go on, using the string \"macro\""
                     "Problem with tokenizer preprocessor: unknown macro ~
                      type ~s" type-of-error)
             (twrite-string "the macro ")))
          (twrite-symbol macro-name)
          (unless (=f iterator number-of-errors)
            (if (=f iterator (1-f number-of-errors))
                (twrite-string ", and ")
                (twrite-string ", ")))))))




;;; `make-error-string-for-bad-regular-expression' - this is called as an argument
;;; to stack error, which does a throw, and so this is the only possible place to
;;; reclaim the list of preprocessor errors.  It's kind of awkward to do it here,
;;; but, oh well.

(defun-simple make-error-string-for-bad-regular-expression
    (pattern evaluator-name preprocessor-errors?)
  (let ((result
          (twith-output-to-text-string
            (twrite-string "The regular expression \"")
            (twrite-string pattern)
            (twrite-string "\" given to ")
            (twrite-symbol evaluator-name t)
            (twrite-string " could not be parsed.")
            (when preprocessor-errors?
              (twrite-string "  The parser reported that ")
              (loop with number-of-errors = (length preprocessor-errors?)
                    for (macro-name type-of-error) in preprocessor-errors?
                    as iterator from 1 do
                (case type-of-error
                  (built-in
                   (twrite-string "there is no built-in character class called "))
                  (t
                   #+development
                   (cerror "Go on, using the string \"macro\""
                           "Problem with tokenizer preprocessor: unknown macro ~
                           type ~s" type-of-error)
                   (twrite-string "the macro ")))
                (twrite-symbol macro-name)
                (unless (=f iterator number-of-errors)
                  (if (=f iterator (1-f number-of-errors))
                      (twrite-string ", and ")
                      (twrite-string ", ")))
                    finally
                      (reclaim-token-tree preprocessor-errors?))))))
    result))



;;; The `tokenizer-pattern-note' frame note writer.

(def-frame-note-writer tokenizer-pattern-notes (note-strings)
  (twrite-string "there are problems with the following pattern-definitions: ")
  (loop for note in note-strings
        for note-index from 0
        do
    (unless (=f note-index 0)
      (twrite-wide-character-macro #.%\;))
    (twrite-wide-character-macro #.%line-separator)
    (if (>=f note-index 26)
        (multiple-value-bind
            (char1 char2)
            (floorf note-index 26)
          (tformat "   (~c~c) "
                   (+f #.(1-f %\a) char1)
                   (+f #.%\a char2)))
        (tformat "   (~c) " (+f #.%\a note-index)))
    (tformat "~a" note)))


;;; `format-note-for-duplicate-pattern'

(defun-simple format-note-for-duplicate-pattern (name)
  (twith-output-to-text-string
    (twrite-symbol name t)
    (twrite-string " is defined more than once")))



;;; The `tokenizer-token-notes' frame note writer.

(def-frame-note-writer tokenizer-token-notes (note-strings)
  (twrite-string "there are problems with the following token-definitions: ")
  (loop for note in note-strings
        for note-index from 0
        do
    (unless (=f note-index 0)
      (twrite-wide-character-macro #.%\;))
    (twrite-wide-character-macro #.%line-separator)
    (tformat "   (~c) " (+f #.%\a note-index))
    (tformat "~a" note)))



;;; `format-pattern-notes' - writes out notes describing parsing
;;; problems encountered in pattern definitions.

(defun-simple format-pattern-notes (unparsable-patterns duplicate-patterns)
  (let ((formatted-list '()))
    (loop for (name expression preprocessor-errors) in unparsable-patterns
          as message = (format-note-for-preprocessor-error
                         name expression preprocessor-errors)
          do
      (slot-value-push message formatted-list))
    (loop for name in duplicate-patterns
          do
      (slot-value-push (format-note-for-duplicate-pattern name) formatted-list))
    formatted-list))


;;; `format-token-notes' - writes out notes describing parsing
;;; problems encountered in token definitions.

(defun-simple format-token-notes (unparsable-tokens)
  (loop with formatted-list
        for (name expression preprocessor-errors) in unparsable-tokens
        as message = (format-note-for-preprocessor-error
                       name expression preprocessor-errors)
        do
    (slot-value-push message formatted-list)
        finally
          (return formatted-list)))



;;; `add-tokenizer-pattern-frame-notes' - posts the notes

(defun-void add-tokenizer-pattern-frame-notes
    (tokenizer pattern-notes duplicate-patterns)
  (delete-frame-note-if-any 'tokenizer-pattern-notes tokenizer)
  (when (or pattern-notes duplicate-patterns)
    (add-frame-note
      'tokenizer-pattern-notes
      tokenizer
      (format-pattern-notes pattern-notes duplicate-patterns)
      t nil)
    (reclaim-token-list duplicate-patterns)
    (reclaim-token-tree pattern-notes)))



;;; `add-tokenizer-token-frame-notes'

(defun-void add-tokenizer-token-frame-notes (tokenizer token-notes)
  (delete-frame-note-if-any 'tokenizer-token-notes tokenizer)
  (when token-notes
    (add-frame-note
      'tokenizer-token-notes
      tokenizer
      (format-token-notes token-notes)
      t nil)
    (reclaim-token-notes token-notes)))


;;; `reclaim-token-notes'

(defun-void reclaim-token-notes (token-notes)
  (loop for (action expression preprocessed-expression) in token-notes do
    (when (wide-string-p preprocessed-expression)
        (reclaim-wide-string preprocessed-expression)))
  (reclaim-token-tree token-notes))






;;;; Tokenizer Class

;;; The "tokenizer" class in G2 follows the format of a lex specification.
;;; There are two important user-editable slots: patterns-definitions
;;; and tokens-definitions.

;;; "patterns-definition" and "tokens-definition" are text slots like
;;; box-translation-and-text, containing a list of the text-string and
;;; text of the definitions the user entered.

(def-class (tokenizer
             (item entity)
             (foundation-class tokenizer)
             define-predicate
             (class-export-comment
               "Tokenizers allow text to be broken up into smaller pieces"))
  (frame-author-or-authors
    nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))
  (name-or-names-for-frame
    nil system save)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      50 50
      ((outline ( 0  0) (50  0) (50 50) ( 0 50))
       (outline (19 36) (19 41) (41 41) (41 36))
       (outline (19 27) (19 32) (41 32) (41 27))
       (outline (19 18) (19 23) (41 23) (41 18))
       (outline ( 9  8) ( 9 13) (41 13) (41  8)))))
  (patterns-definition
    nil (type patterns-definition text) vector-slot system)
  (tokens-definition
    nil (type tokens-definition text) vector-slot system)
  (patterns-strings nil system)
  (tokens-cons nil system)
  (lexing-table nil system))




;;; `initialize-for-tokenizer'

(def-class-method initialize (tokenizer)
  (funcall-superior-method tokenizer)
  (update-frame-status tokenizer 'incomplete nil))





;;; `search-for-match-using-tokenizer' - the API to the tokenizer class.

(defun-simple search-for-match-using-tokenizer (tokenizer source-text start-index)
  (in-lexing-context
    (lexing-table tokenizer)
    (let* ((current-anchor-p t)
           (next-token
             (get-next-token-from-text-string
               source-text start-index)))
      (incff (parse-object-start-index next-token))
      next-token)))





;;; `regular-expression' - I am handling the parsing of the regular expression
;;; outside of the edit-tokenize-parse-prompt loop.  For the purposes of the
;;; tokenizer class (as well as the tokenizing funcalled evaluators), a regular
;;; expression is any string ("text" in G2's procedural language).  I will parse
;;; the regular expressions after the editor is closed.

(def-grammar-category regular-expression ()
  (whole-string)
  ;; (regular-expression-string)
  )


(def-grammar-category regular-expression-string ()
  ((double-quote regular-expression-inside double-quote) 2))


(add-grammar-rules
  '((regular-expression-inside reg-expression)
    (regular-expression-inside (CARET reg-expression)
     (anchor 2))
    (reg-expression alternatives)
    (alternatives (regexp-sequence ALTERNATIVE alternatives)
     (either 1 3))
    (alternatives regexp-sequence)
    (regexp-sequence (possibly-kleened-basic-block regexp-sequence)
     (seq 1 2))
    (regexp-sequence possibly-kleened-basic-block)
    (possibly-kleened-basic-block basic-regexp-block)
    (possibly-kleened-basic-block kleened-basic-block)
    (kleened-basic-block (basic-regexp-block KLEENE-STAR)
     (kleene 1))
    (kleened-basic-block (basic-regexp-block PLUS)
     (plus 1))
    (kleened-basic-block (basic-regexp-block QUESTION-MARK)
     (maybe 1))
    (non-range-standard-character REGEXP-CHARACTER)
    (non-range-standard-character HYPHEN)
    (non-range-standard-character RIGHT-CURLY-BRACE)
    (basic-regexp-block (LEFT-PAREN reg-expression RIGHT-PAREN)
     2)
    (basic-regexp-block character-class)
    (basic-regexp-block DOT
     (dot))
    (basic-regexp-block non-range-standard-character)
    (character-class (LEFT-CURLY-BRACE range RIGHT-CURLY-BRACE)
     (character-class 2))
    (character-class (LEFT-CURLY-BRACE CARET range RIGHT-CURLY-BRACE)
     (inverted-class 3))
    (range range-element (1))
    (range (range-element range) (1 . 2))
    (range-element char-sequence)
    (range-element REGEXP-CHARACTER)
    (char-sequence (REGEXP-CHARACTER HYPHEN REGEXP-CHARACTER)
     (1 . 3))
    (illegal-character-sequence
     ILLEGAL-CHARACTER)))



;;; `pattern-is-already-present-in-lexing-strings'

(defun-simple pattern-is-already-present-in-lexing-strings (new-name)
  (loop for (name . expression) in current-lexing-strings
        thereis (eq name new-name)))



;;; `parse-patterns' - takes a list of name/expression pairs, as written
;;; by the slot-value-compiler for patterns-definition, and produces an
;;; association list of patterns to strings.  Note that: (a) it compiles
;;; the regular expression just to see if its valid, but does not use
;;; the compiled version at all;  this creates a list which is not used.
;;; However, that list (parsed-expression) should *NOT* be reclaimed.
;;; It will stay in the cache, and when the cache get's full and needs
;;; to delete that regular expression, it will take care of reclaiming
;;; it. (b) it creates a fresh list (using the TOKEN and SLOT-VALUE cons
;;; pools) every time it is called.

(defun parse-patterns (patterns)
  (if (and (listp patterns) (consp (car patterns)))
      (loop with current-lexing-strings = '()
            with unparsable-patterns = '()
            with duplicate-pattern-names = '()
            for (name . expression) in patterns
            as preprocessed-expression-or-list-of-errors
               = (preprocess-regexp-string expression t)
            as parsed-expression
               = (and (wide-string-p preprocessed-expression-or-list-of-errors)
                      (parse-regexp-string
                        preprocessed-expression-or-list-of-errors))
            do
        (cond
          ((null parsed-expression)
           (when (wide-string-p preprocessed-expression-or-list-of-errors)
             (reclaim-wide-string preprocessed-expression-or-list-of-errors)
             (setq preprocessed-expression-or-list-of-errors nil))
           (token-push (token-list name expression
                                   preprocessed-expression-or-list-of-errors)
                       unparsable-patterns))
          (t
           (when (pattern-is-already-present-in-lexing-strings name)
             (token-pushnew-eq name duplicate-pattern-names))
           (slot-value-push
             (slot-value-cons name preprocessed-expression-or-list-of-errors)
             current-lexing-strings)))
            finally
              (return (values current-lexing-strings unparsable-patterns
                              duplicate-pattern-names)))
      nil))



;;; `parse-tokens'

(defun parse-tokens (tokens)
  (if (and (listp (car tokens)) (consp (caar tokens)))
      (loop with parsed-tokens = '()
            with unparsable-tokens = '()
            for (action . expression) in (car tokens)
            as preprocessed-expression
               = (preprocess-regexp-string expression t)
            as parsed-expression = (and (wide-string-p preprocessed-expression)
                                        (parse-regexp-string
                                          preprocessed-expression))
            do
        (cond
          ((null parsed-expression)
           (token-push (token-list action expression preprocessed-expression)
                       unparsable-tokens))
          (t
           (reclaim-wide-string preprocessed-expression)
           (slot-value-push
             (slot-value-list
               action
               (copy-tree-using-slot-value-conses parsed-expression))
             parsed-tokens)))
            finally
              (return (values (nreverse parsed-tokens) unparsable-tokens)))
    nil))


;;; `verify-structure-regexp'

(defmacro verify-structure-regexp (regexp)
  `(if (symbolp ,regexp)
       #+development
       (progn
         (cerror "Continue, using the string \"no-value\""
                 "No field \"regexp\" in structure for attribute-export ~
                  setter in tokenizer")
         (stringw "no-value"))
       #-development
       (stringw "no-value")
       ,regexp))


;;; `patterns-strings'

(def-slot-value-reclaimer patterns-strings (patterns-strings tokenizer)
  (reclaim-patterns-strings patterns-strings tokenizer))

;;; `reclaim-patterns-strings'

(defun-void reclaim-patterns-strings (patterns-strings tokenizer)
  (loop for (name . pattern) in patterns-strings do
      (reclaim-wide-string pattern))
    (reclaim-slot-value-tree patterns-strings)
    (setf (patterns-strings tokenizer) nil))


;;; `tokens-cons'

(def-slot-value-reclaimer tokens-cons (tokens-cons tokenizer)
  (reclaim-tokens-cons tokens-cons tokenizer))

;;; `reclaim-tokens-cons'

(defun-void reclaim-tokens-cons (tokens-cons tokenizer)
  (reclaim-slot-value-tree tokens-cons)
  (setf (tokens-cons tokenizer) nil))

;;; `lexing-table'

(def-slot-value-reclaimer lexing-table (lexing-table tokenizer)
  (reclaim-dfa-if-any lexing-table)
  (setf (lexing-table tokenizer) nil))


;;; `patterns-definition'

(def-slot-putter patterns-definition (tokenizer patterns-definition)
  (delete-frame-note-if-any 'tokenizer-pattern-notes tokenizer)
  (delete-frame-note-if-any 'tokenizer-token-notes tokenizer)
  (multiple-value-bind
      (current-lexing-strings unparsable-patterns duplicate-patterns)
      (parse-patterns (car patterns-definition))
    (add-tokenizer-pattern-frame-notes
      tokenizer unparsable-patterns duplicate-patterns)
    (multiple-value-bind
        (tokens-cons unparsable-tokens)
        (parse-tokens (tokens-definition tokenizer))
      (add-tokenizer-token-frame-notes
        tokenizer unparsable-tokens)
      (setf (patterns-definition tokenizer) patterns-definition)
      (reclaim-patterns-strings (patterns-strings tokenizer) tokenizer)
      (setf (patterns-strings tokenizer) current-lexing-strings)
      (reclaim-tokens-cons (tokens-cons tokenizer) tokenizer)
      (setf (tokens-cons tokenizer) tokens-cons)
      (reclaim-dfa-if-any (lexing-table tokenizer))
      (cond
        ((and tokens-cons (null unparsable-tokens))
         (update-frame-status tokenizer nil nil)
         (token-push nil tokens-cons)
         (setf (lexing-table tokenizer)
               (compile-lexing-table tokens-cons))
         (token-pop tokens-cons))
        (t
         (if unparsable-tokens
             (update-frame-status tokenizer 'bad nil)
             (update-frame-status tokenizer 'incomplete nil))
         (setf (lexing-table tokenizer) nil)))))
  patterns-definition)

(def-slot-value-compiler patterns-definition (parse-result)
  (cond
    ((consp parse-result)
     parse-result)
    (t
     nil)))


(def-slot-value-writer patterns-definition (patterns-definition)
  (cond
    ((null patterns-definition)
     (twrite-string "none"))
    (t
     (loop for (name . expression) in patterns-definition do
       (twrite-symbol name t)
       (twrite-string "   ")
       (twrite-wide-character-macro #.%\")
       (twrite-string expression)
       (twrite-wide-character-macro #.%\")
       (twrite-wide-character-macro #.%line-separator)))))



(defmacro make-pattern-evaluation-structure (pattern-definition)
  `(let ((new-structure (allocate-evaluation-structure nil)))
     (setf (evaluation-structure-slot new-structure 'pattern-name)
           (car ,pattern-definition))
     (setf (evaluation-structure-slot new-structure 'pattern-regexp)
           (make-evaluation-text (cdr ,pattern-definition)))
     new-structure))


(define-category-evaluator-interface (patterns-definition
                                       :access read-write)
    (sequence
      (structure
        patterns-definition
        ((pattern-name symbol)
         (pattern-regexp text))
        (and pattern-name pattern-regexp))
      0)
  ((set-form (evaluation-value))
   (evaluation-etypecase
     evaluation-value
     ((sequence)
      (loop for element being each evaluation-sequence-element of evaluation-value
            as struct = (car element)
            as name = (structure-slot struct 'pattern-name 'no-name)
            as regexp = (structure-slot struct 'pattern-regexp 'no-value)
            collect
            (phrase-cons name (verify-structure-regexp regexp))
              using phrase-cons))))
  ((get-form (slot-value))
   (cond
     ((null slot-value)
      (allocate-evaluation-sequence nil))
     (t
      (loop for pattern-def in slot-value
            collect
            (make-pattern-evaluation-structure pattern-def)
              into result using eval-cons
            finally
              (return (allocate-evaluation-sequence result)))))))



(def-grammar-category patterns-definition ()
  ('none)
  (pattern-definition-list))

(def-grammar-category pattern-definition-list ()
  (pattern-definition (1))
  ((pattern-definition pattern-definition-list) (1 . 2)))

(def-grammar-category pattern-definition ()
  ((pattern-name regular-expression) (1 . 2)))

(def-grammar-category pattern-name ()
  (symbol)
  ;; (pattern-name-symbol)
  )

(def-grammar-category pattern-name-symbol ()
  (regexp-character (1))
  ((regexp-character pattern-name-symbol) (1 . 2)))






;;; `tokens-definition'

(def-slot-putter tokens-definition (tokenizer tokens-definition)
  (let ((current-lexing-strings (patterns-strings tokenizer)))
    (multiple-value-bind
        (tokens-cons unparsable-tokens)
        (parse-tokens tokens-definition)
      (add-tokenizer-token-frame-notes
        tokenizer unparsable-tokens)
      (setf (tokens-definition tokenizer) tokens-definition)
      (reclaim-tokens-cons (tokens-cons tokenizer) tokenizer)
      (setf (tokens-cons tokenizer) tokens-cons)
      (reclaim-dfa-if-any (lexing-table tokenizer))
      (cond
        ((and tokens-cons (null unparsable-tokens))
         (update-frame-status tokenizer nil nil)
         (token-push nil tokens-cons)
         (setf (lexing-table tokenizer)
               (compile-lexing-table tokens-cons))
         (token-pop tokens-cons))
        (t
         (if unparsable-tokens
             (update-frame-status tokenizer 'bad nil)
             (update-frame-status tokenizer 'incomplete nil))
         (setf (lexing-table tokenizer) nil)))))
  tokens-definition)


(def-slot-value-compiler tokens-definition (parse-result)
  (cond
    ((consp parse-result)
     parse-result)
    (t
     nil)))


(def-slot-value-writer tokens-definition (tokens-definition)
  (cond
    ((null tokens-definition)
     (twrite-string "none"))
    (t
     (loop for (type . expression) in tokens-definition do
       (twrite-wide-character-macro #.%\")
       (twrite-string expression)
       (twrite-wide-character-macro #.%\")
       (twrite-string "   ")
       (twrite-symbol type t)
       (twrite-wide-character-macro #.%line-separator)))))


(defmacro make-token-evaluation-structure (token-definition)
  `(let ((new-structure (allocate-evaluation-structure nil)))
     (setf (evaluation-structure-slot new-structure 'token-type)
           (car ,token-definition))
     (setf (evaluation-structure-slot new-structure 'token-regexp)
           (make-evaluation-text (cdr ,token-definition)))
     new-structure))

(define-category-evaluator-interface (tokens-definition
                                       :access read-write)
    (sequence
      (structure
        tokens-definition
        ((token-regexp text)
         (token-type symbol))
        (and token-type token-regexp))
      0)
  ((set-form (evaluation-value))
   (evaluation-etypecase
     evaluation-value
     ((sequence)
        (loop for element being each evaluation-sequence-element of evaluation-value
              as struct = (car element)
              as name = (structure-slot struct 'token-type 'no-name)
              as regexp = (structure-slot struct 'token-regexp 'no-value)
              collect
              (phrase-cons name (verify-structure-regexp regexp))
                using phrase-cons))
     ((structure)
      (with-structure (evaluation-value tokens-definition)
        (phrase-cons token-type token-regexp)))))
  ((get-form (slot-value))
   (cond
     ((null slot-value)
      (allocate-evaluation-sequence nil))
     (t
      (loop for token-def in slot-value
            collect (make-token-evaluation-structure token-def)
              into result using eval-cons
            finally
              (return (allocate-evaluation-sequence result)))))))



(def-grammar-category tokens-definition ()
  ('none)
  (token-definition-list))

(def-grammar-category token-definition-list ()
  (token-definition (1))
  ((token-definition token-definition-list) (1 . 2)))

(def-grammar-category token-definition ()
  ((regular-expression token-action) (2 . 1)))

(def-grammar-category token-action ()
  ('do-nothing)
  (symbol))






;;;; Pretty Printing


#+development
(defun pp-patterns (pattern-tree)
  (dmesg "(")
  (loop with *print-case* = :downcase
        for (name expression) in pattern-tree
        as rest-of-list on pattern-tree do
    (dmesg "~15s:  \"~a\"" name expression)
    (unless (null (cdr rest-of-list))
      (dmesg "~%  ")))
  (dmesg ")~%"))


#+development
(defun pp-tokens (tokens-tree)
  (loop with *print-case* = :downcase
        with *print-length* = 100
        with *print-level* = 20
        for (action expression) in tokens-tree
        as rest-of-list on tokens-tree do
    (dmesg "(~s~%  ~s)" action expression)
    (unless (null (cdr rest-of-list))
      (dmesg "~% "))))


#+development
(defun pp-tokenizer (tokenizer)
  (dmesg "(")
  (pp-tokens (tokens-cons tokenizer))
  (dmesg ")~%")
  (values))







;;;; Returning G2 structures



;;; `make-evaluation-structure-from-parse-object-reclaiming-it' -
;;; "converts" a parse-object GL structure into a G2 structure.

(defun-simple make-evaluation-structure-from-parse-object-reclaiming-it
    (parse-object)
  (let ((result
          (allocate-evaluation-structure
            (eval-list 'token-type
                       (or (parse-object-type parse-object) 'match)
                       'start-index
                       (parse-object-start-index parse-object)
                       'end-index
                       (parse-object-end-index parse-object)))))
    (reclaim-parse-object parse-object)
    result))


;;; `make-evaluation-structure-from-parse-object-reclaiming-it' -
;;; "converts" a parse-object GL structure into a G2 structure, and
;;; adds the lexeme from the string to the G2 structure.

(defun-simple make-evaluation-structure-with-text-from-parse-object-reclaiming-it
    (parse-object source-text)
  (let* ((start-index (parse-object-start-index parse-object))
         (end-index (parse-object-end-index parse-object))
         (result
           (allocate-evaluation-structure
             (eval-list 'token-type
                        (or (parse-object-type parse-object) 'match)
                        'lexeme
                        (make-evaluation-text-reclaiming-argument
                          (get-from-g2-text
                            source-text
                            start-index
                            end-index))
                        'start-index
                        start-index
                        'end-index
                        end-index))))
    (reclaim-parse-object parse-object)
    result))




;;;; New Tokenizer Testing


#+development
(defun get-next-token-from-wide-text
    (text-tail end-line-index? end-character-index? return-partial-tokens?
               line-index character-index)
  (new-get-next-token-from-wide-text-if-available-1
    (determine-appropriate-tokenizer)
    text-tail line-index character-index
    end-line-index? end-character-index? return-partial-tokens?))


;;; `get-next-token-from-text'

#+development
(defun get-next-token-from-text (tokenizer text &optional start? end?)
  (in-lexing-context
    tokenizer
    (multiple-value-bind
        (token-value token-type-or-partial-types line-index character-index
                     next-text-tail self-terminating-p)
        (for-g2-tokenizing
          (text 0 (or start? 0) (if end? 0 nil) end? t)
          (get-next-token-or-partial-tokens-from-text))
      (declare (ignore line-index next-text-tail))
      (values token-value token-type-or-partial-types character-index self-terminating-p))))



;;; `get-next-token-from-string'

#+development
(defun get-next-token-from-string (tokenizer text-string &optional start? end?)
  (let ((temporary-text
          (convert-text-string-to-text-without-duplicating-it text-string)))
    (multiple-value-prog1
        (get-next-token-from-text tokenizer temporary-text start? end?)
      (reclaim-text-without-reclaiming-underlying-text-string temporary-text))))




#+development
(defparameter simple-action-button-rule
  '(2
    (0 (LINE-WIDTH . 376) #w"start test-tokenizer (\"conclude that the x of y"
     26 (LOST-SPACES . 0) (LINE-WIDTH . 87) #w"= 4\", 1)")
    (26 (LOST-SPACES . 0) (LINE-WIDTH . 87) #w"= 4\", 1)")
    (1    0    1    0    t)
    (1    0    NIL  NIL  t)
    (1    5    NIL  NIL  t)
    (1    20   NIL  NIL  t)
    (1    22   NIL  NIL  t)
    (2    4    NIL  NIL  t)
    (2    5    NIL  NIL  t)
    (2    7    NIL  NIL  t)
    (2    8    NIL  NIL  t)))

#+development
(defparameter correct-tokenization-of-simple-action-button-rule
  `((  1   0 NIL            NIL NIL)
    (  1   5 START          NIL SYMBOL)
    (  1  20 TEST-TOKENIZER NIL SYMBOL)
    (  1  22 \(             T   PUNCTUATION-MARK)
    (  2   4 #w"conclude that the x of y = 4"
                            T   WHOLE-STRING)
    (  2   5 \,             T   PUNCTUATION-MARK)
    (  2   7 1              NIL INTEGER)
    (  2   8 \)             T   PUNCTUATION-MARK)
    (NIL NIL NIL            NIL NIL)))


#+development
(defparameter text-of-weird-tok-procedure
  `(t 0 (lost-spaces . 0) (line-width . 106) #w"@b@o@b ()"
      0 (lost-spaces . 0) (line-width .   0) #w"\u2028"
      0 (lost-spaces . 0) (line-width .  46) #w"\u2028begin"
      0 (lost-spaces . 0) (line-width . 445) #w"\u2028   z = \"y@[[x]] = [(if y[x] > 0 then \"[y[x]]\" else \"[y[0]]\")]\""
      0 (lost-spaces . 0) (line-width .  31) #w"\u2028end"
      0 (lost-spaces . 0) (line-width .   0) #w"\u2028"))


#+development
(defparameter weird-tokenizing-procedure
  '(5
    ;;; text-tail for first line
    (0 (LOST-SPACES . 0) (LINE-WIDTH . 106) #w"@b@o@b ()"
     0 (LOST-SPACES . 0) (LINE-WIDTH . 0) #w"\u2028"
     0 (LOST-SPACES . 0) (LINE-WIDTH . 46) #w"\u2028begin"
     0 (LOST-SPACES . 0) (LINE-WIDTH . 445) #w"\u2028   z = \"y@[[x]] = [(if y[x] > 0 then \"[y[x]]\" else \"[y[0]]\")]\""
     0 (LOST-SPACES . 0) (LINE-WIDTH . 31) #w"\u2028end"
     0 (LOST-SPACES . 0) (LINE-WIDTH . 0) #w"\u2028")

    ;;; text-tail for second line
    (0 (LOST-SPACES . 0) (LINE-WIDTH . 0) #w"\u2028"
     0 (LOST-SPACES . 0) (LINE-WIDTH . 46) #w"\u2028begin"
     0 (LOST-SPACES . 0) (LINE-WIDTH . 445) #w"\u2028   z = \"y@[[x]] = [(if y[x] > 0 then \"[y[x]]\" else \"[y[0]]\")]\""
     0 (LOST-SPACES . 0) (LINE-WIDTH . 31) #w"\u2028end"
     0 (LOST-SPACES . 0) (LINE-WIDTH . 0) #w"\u2028")

    ;;; text-tail for third line
    (0 (LOST-SPACES . 0) (LINE-WIDTH . 46) #w"\u2028begin"
     0 (LOST-SPACES . 0) (LINE-WIDTH . 445) #w"\u2028   z = \"y@[[x]] = [(if y[x] > 0 then \"[y[x]]\" else \"[y[0]]\")]\""
     0 (LOST-SPACES . 0) (LINE-WIDTH . 31) #w"\u2028end"
     0 (LOST-SPACES . 0) (LINE-WIDTH . 0) #w"\u2028")

    ;;; text-tail for fourth line
    (0 (LOST-SPACES . 0) (LINE-WIDTH . 445) #w"\u2028   z = \"y@[[x]] = [(if y[x] > 0 then \"[y[x]]\" else \"[y[0]]\")]\""
     0 (LOST-SPACES . 0) (LINE-WIDTH . 31) #w"\u2028end"
     0 (LOST-SPACES . 0) (LINE-WIDTH . 0) #w"\u2028")

    ;;; text-tail for fifth line
    (0 (LOST-SPACES . 0) (LINE-WIDTH . 31) #w"\u2028end"
     0 (LOST-SPACES . 0) (LINE-WIDTH . 0) #w"\u2028")
    (1     0 1      0      T  )
    (1     0 6      1      T  )
    (1     6 6      1      T  )
    (1     8 6      1      T  )
    (1     9 6      1      T  )
    (3     6 6      1      T  )
    (4     5 6      1      T  )
    (4     7 6      1      T  )
    (4    13 6      1      T  )
    (4    14 6      1      T  )
    (4    20 6      1      T  )
    (4    21 6      1      T  )
    (4    23 6      1      T  )
    (4    25 6      1      T  )
    (4    26 6      1      T  )
    (4    27 6      1      T  )
    (4    28 6      1      T  )
    (4    30 6      1      T  )
    (4    32 6      1      T  )
    (4    37 6      1      T  )
    (4    40 6      1      T  )
    (4    41 6      1      T  )
    (4    42 6      1      T  )
    (4    43 6      1      T  )
    (4    44 6      1      T  )
    (4    46 6      1      T  )
    (4    51 6      1      T  )
    (4    54 6      1      T  )
    (4    55 6      1      T  )
    (4    56 6      1      T  )
    (4    57 6      1      T  )
    (4    58 6      1      T  )
    (4    60 6      1      T  )
    (4    61 6      1      T  )
    (4    63 6      1      T  )))


#+development
(defparameter old-tokenization-of-weird-tok-procedure
  `((  1   0 NIL      NIL NIL)
    (  1   6 |bob|    NIL SYMBOL)
    (  1   8 |(|      T   PUNCTUATION-MARK)
    (  1   9 |)|      T   PUNCTUATION-MARK)
    (  3   6 BEGIN    NIL SYMBOL)
    (  4   5 Z        NIL SYMBOL)
    (  4   7 =        T   PUNCTUATION-MARK)
    (  4  13 #w"y["   T   LEFT-STRING)
    (  4  14 X        NIL SYMBOL)
    (  4  20 #w"] = " T   MIDDLE-STRING)
    (  4  21 |(|      T   PUNCTUATION-MARK)
    (  4  23 IF       NIL SYMBOL)
    (  4  25 Y        NIL SYMBOL)
    (  4  26 [        T   PUNCTUATION-MARK)
    (  4  27 X        NIL SYMBOL)
    (  4  28 ]        T   PUNCTUATION-MARK)
    (  4  30 >        NIL PUNCTUATION-MARK)
    (  4  32 0        NIL INTEGER)
    (  4  37 THEN     NIL SYMBOL)
    (  4  40 #w""     T   LEFT-STRING)
    (  4  41 Y        NIL SYMBOL)
    (  4  42 [        T   PUNCTUATION-MARK)
    (  4  43 X        NIL SYMBOL)
    (  4  44 ]        T   PUNCTUATION-MARK)
    (  4  46 #w""     T   RIGHT-STRING)
    (  4  51 ELSE     NIL SYMBOL)
    (  4  54 #w""     T   LEFT-STRING)
    (  4  55 Y        NIL SYMBOL)
    (  4  56 [        T   PUNCTUATION-MARK)
    (  4  57 0        NIL INTEGER)
    (  4  58 ]        T   PUNCTUATION-MARK)
    (  4  60 #w""     T   RIGHT-STRING)
    (  4  61 |)|      T   PUNCTUATION-MARK)
    (  4  63 #w""     T   RIGHT-STRING)
    (  5   4 END      NIL SYMBOL)
    (  6   1 NIL      NIL NIL)))


#+development
(defparameter old-non-editor-tokenization
  '((  1   0 NIL                  NIL NIL)
    (  1   6 |bob|                NIL SYMBOL)
    (  1   8 \(                   T   PUNCTUATION-MARK)
    (  1   9 \)                   T   PUNCTUATION-MARK)
    (  3   6 BEGIN                NIL SYMBOL)
    (  4   5 Z                    NIL SYMBOL)
    (  4   7 =                    T   PUNCTUATION-MARK)
    (  4  39 #w"y[[x]] = [(if y[x] > 0 then " T   WHOLE-STRING)
    (  4  14 X                    NIL SYMBOL)
    (  4  15 \]                   T   PUNCTUATION-MARK)
    (  4  21 \(                   T   PUNCTUATION-MARK)
    (  4  23 IF                   NIL SYMBOL)
    (  4  25 Y                    NIL SYMBOL)
    (  4  26 \[                    T   PUNCTUATION-MARK)
    (  4  27 X                    NIL SYMBOL)
    (  4  28 \]                    T   PUNCTUATION-MARK)
    (  4  30 >                    NIL PUNCTUATION-MARK)
    (  4  32 0                    NIL INTEGER)
    (  4  37 THEN                 NIL SYMBOL)
    (  4  46 #w"[y[x]]"           T   WHOLE-STRING)
    (  4  41 Y                    NIL SYMBOL)
    (  4  42 \[                    T   PUNCTUATION-MARK)
    (  4  43 X                    NIL SYMBOL)
    (  4  44 \]                    T   PUNCTUATION-MARK)
    (  4  45 \]                    T   PUNCTUATION-MARK)
    (  4  51 ELSE                 NIL SYMBOL)
    (  4  60 #w"[y[0]]"           T   WHOLE-STRING)
    (  4  55 Y                    NIL SYMBOL)
    (  4  56 \[                    T   PUNCTUATION-MARK)
    (  4  57 0                    NIL INTEGER)
    (  4  58 \]                    T   PUNCTUATION-MARK)
    (  4  59 \]                    T   PUNCTUATION-MARK)
    (  4  61 \)                   T   PUNCTUATION-MARK)
    (  4  62 \]                    T   PUNCTUATION-MARK)
    (  5   4 END                  NIL SYMBOL)))







#+development
(defparameter tricky-procedure-definition
  '(T
    0  (LOST-SPACES . 0) (LINE-WIDTH . 124) #w"test-me-manually ()"
    0  (LOST-SPACES . 0) (LINE-WIDTH .   0) #w"\u2028"
    0  (LOST-SPACES . 0) (LINE-WIDTH .  42) #w"\u2028z: text;"
    0  (LOST-SPACES . 0) (LINE-WIDTH .  90) #w"\u2028w: float = -4.2;"
    0  (LOST-SPACES . 0) (LINE-WIDTH .  90) #w"\u2028x: integer = 4;"
    0  (LOST-SPACES . 0) (LINE-WIDTH .   0) #w"\u2028"
    0  (LOST-SPACES . 0) (LINE-WIDTH .  35) #w"\u2028begin"
    0  (LOST-SPACES . 0) (LINE-WIDTH .   0) #w"\u2028"
    0  (LOST-SPACES . 0) (LINE-WIDTH . 205) #w"\u2028  { try some funny quotes stuff }"
    0  (LOST-SPACES . 0) (LINE-WIDTH . 470)
                    #w"\u2028   z = \"my-array@[[x]] = [(if my-array[x] > 0 then \"[my-array[x]]\" else \"[my-"
    35 (LOST-SPACES . 0) (LINE-WIDTH . 111) #w"array[0]]\")]\";"
    0  (LOST-SPACES . 0) (LINE-WIDTH . 350) #w"\u2028  inform the operator that \"[z] @[<= that's z] message\""
    0  (LOST-SPACES . 0) (LINE-WIDTH .   0) #w"\u2028"
    0  (LOST-SPACES . 0) (LINE-WIDTH .  24) #w"\u2028end"
    0  (LOST-SPACES . 0) (LINE-WIDTH .   0) #w"\u2028"))




#+development
(defmacro general-tokenizing-wrapper (function
                                       text-tail line-index character-index
                                       end-line-index? end-character-index?
                                       return-partial-tokens-p)
  `(multiple-value-bind
       (r1 r2 r3 r4 r5 r6)
       (twith-output-to-then-use-of-wide-string
         (funcall ,function (determine-appropriate-tokenizer)
                  ,text-tail ,line-index ,character-index
                  ,end-line-index? ,end-character-index?
                  ,return-partial-tokens-p))
     (declare (ignore r5))
     (values r1 r2 r3 r4 r6)))





#+development
(defun test-tokenizer (test-suite function)
  (let* ((copy (copy-tree-using-token-conses test-suite))
         (number-of-lines (token-pop copy))
         (array-of-lines
           (make-array-with-nils (1+f number-of-lines))))
    (loop for i from 1 to number-of-lines do ;; ignore zero element
      (setf (aref array-of-lines i) (token-pop copy)))
    (loop for (l c el ec rp) in copy do
      ;; (format t "(~d ~3d   ~3s ~3s ~3s)~%" l c el ec rp)
      (multiple-value-bind
          (r1 r2 r3 r4 r5)
          (general-tokenizing-wrapper
            function
            (aref array-of-lines l) l c el ec rp)
        (format t "    (~3d ~3d ~20s ~3s ~s)~%" r3 r4 r1 r5 r2)))))



#+development
(defun validate-tokenizer (test-suite function correct-results)
  ;; (reclaim-token-tree (text-stack-of-tokens current-text-tokenization-state))
  ;; (setf (text-stack-of-tokens current-text-tokenization-state) nil)
  (let* ((copy (copy-tree-using-token-conses test-suite))
         (number-of-lines (token-pop copy))
         (array-of-lines
           (make-array-with-nils (1+f number-of-lines))))
    (loop for i from 1 to number-of-lines do ;; ignore zero element
      (setf (aref array-of-lines i) (token-pop copy)))
    (loop for (c3 c4 c1 c6 c2) in correct-results
          as (l c el ec rp) in copy
          as list-of-errors = '()
          do
      (multiple-value-bind
          (token-value
            token-type-or-partial-types
            line-index-for-end-of-token
            character-index-after-token
            text-tail-for-end-of-token?
            token-self-terminating-p)
          (twith-output-to-then-use-of-wide-string
            (funcall function
                     (aref array-of-lines l) l c el ec rp))
        (declare (ignore text-tail-for-end-of-token?))
        (unless (equalw c1 token-value)
          (token-push (token-list "token-value:" c1 token-value) list-of-errors))
        (unless (eql c2 token-type-or-partial-types)
          (token-push (token-list "token-type: " c2 token-type-or-partial-types)
                      list-of-errors))
        (unless (eql c3 line-index-for-end-of-token)
          (token-push (token-list "line-index: " c3 line-index-for-end-of-token)
                      list-of-errors))
        (unless (eql c4 character-index-after-token)
          (token-push (token-list "char index: " c4 character-index-after-token)
                      list-of-errors))
        (unless (eql c6 token-self-terminating-p)
          (token-push (token-list "self-term:  " c6 token-self-terminating-p)
                      list-of-errors))
        (unless (null list-of-errors)
          (format t "~%(~d, ~d):~%" l c)
          (loop for (name correct returned) in (nreverse list-of-errors) do
            (format t "   ~a {O} ~s vs. {N} ~s~%" name correct returned)))))))



#+development
(defun-void all-characters-in-text (text)
  (setf (active-text-tail current-text-tokenization-state) text)
  (setf (line-index current-text-tokenization-state) 0)
  (setf (character-index current-text-tokenization-state) 0)
  (setf (end-line-index? current-text-tokenization-state) nil)
  (setf (end-character-index? current-text-tokenization-state) nil)
  (setf (return-partial-tokens-p current-text-tokenization-state) nil)
  (tokenizer-go-to-next-text-line)
  (get-next-wide-character-from-text-1)
  (loop for char = (wide-character? current-text-tokenization-state)
        while char do
    (dmesg "~c" (alphabet-code-char char))
    (get-next-wide-character-from-text-1)))



#+development
(defun test-new-tokenizer-with-string
    (text-string character-index end-character-index? return-partial-tokens-p)
  (let ((temporary-text
          (convert-text-string-to-text-without-duplicating-it text-string)))
    (multiple-value-prog1
        (general-tokenizing-wrapper
          #'new-get-next-token-from-wide-text-if-available-1
          temporary-text 0 character-index
          (if end-character-index? 0 nil) end-character-index?
          return-partial-tokens-p)
      (reclaim-text-without-reclaiming-underlying-text-string temporary-text))))




;;; `all-relevant-tokenizer-items'

#+development
(defun all-relevant-tokenizer-items (lexing-table)
  (loop with all-transitions = '()
        with states = (get-all-states-from-tokenizer lexing-table)
        for state in states
        as current-transitions = (fsm-state-transitions state)
        do
    (loop for trans in current-transitions do
      (token-push trans all-transitions))
        finally
          (return (nconc states (nreverse all-transitions)))))

