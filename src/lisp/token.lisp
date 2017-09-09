; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")


;;;; Module TOKEN

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; John Valente





(declare-forward-references
  (note-use-of-text-string-in-phrase  function)
  (preprocessing-tokenizer            variable)
  (managed-float-p-function           function)
  (notify-user-at-console             function)
  (find-previous-character-if-any     function)
  )



;;; `token'

(defconser token TOKEN)


;;; `token-pushnew-eq' - is equivalent to using token-pushnew
;;; with the :test 'eq keyword argument, but I hope this will
;;; be marginally faster.  (token-pushnew thing place :test #'eq)
;;; expands into a general (non-simple, non-compiled) funcall
;;; in the translated C code.  This way obviously avoids any
;;; funcall whatsoever.

(defmacro token-pushnew-eq (thing place)
  `(setq ,place
         (if (memq-p-macro ,thing ,place)
             ,place
             (token-cons ,thing ,place))))


;;; `token-reverse' - produces a reversed list in the token cons pool.

(defun-simple token-reverse (list)
  (loop with new-list = '()
        for element in list
        do
    (token-push element new-list)
        finally
          (return new-list)))


#+development
(defvar last-recorded-outstanding-token-conses-count 0)


#+development
(defmacro print-recent-token-cons-usage (message)
  `(let* ((now-outstanding (outstanding-token-conses))
          (used (-f now-outstanding last-recorded-outstanding-token-conses-count)))
     (format t "   ~d ;; ~a~%" used ,message )
     (setq last-recorded-outstanding-token-conses-count now-outstanding)))



;;;; Tokenization


;;; This module provides a mechanism for creating arbitrary tokenizers.
;;; The specification consists of a series of pattern definitions,
;;; followed by a series of token definitions.  The syntax used to
;;; define patterns and tokens is an s-expression made up of the following
;;; elements: canonical elements of the language (e.g., characters);
;;; supported regular expression constructs, which can be defined with
;;; "def-regexp-operator"; and system-defined, built-in character classes.


;;; `lexing-table' - The internal, abstract representation of a tokenizer.

(def-structure lexing-table
  (lexing-table-start-state nil)
  (lexing-table-token-array nil)
  (lexing-table-search-is-anchored-p nil))


;;; `internal-token'

(def-structure internal-token
  (internal-token-name nil)
  (internal-token-action #'alphabet-normalized-symbol-from-text-string)
  (internal-token-number nil))  ;; redundant



;;; `fsm-state' - a node in a finite state machine used for lexing.
;;; The accepts-token? field should only hold either a positive
;;; integer or nil, representing which state, if any, to announce
;;; when the machine stops in this state.  The associated-rules
;;; slot holds a list of all associated rules for a state.  For
;;; example, if we had rules
;;;   "inform"   INFORM  [Rule 1]
;;;   "invoke"   INVOKE  [Rule 2]
;;; upon reading character 'i', we would enter a state which is
;;; associated with both rules, but by the third character, we
;;; would have resolved the ambiguity.
;;;    It's important to note that the subset construction assumes
;;; each nfa state is associated with only one rule.  That's
;;; entirely consistent with the "special" nfa required by the
;;; subset construction.  There should not be any "optimization"
;;; at the nfa construction level.

(def-structure fsm-state
  (fsm-state-associated-rules nil)
  (fsm-state-accepts-token? nil)
  (fsm-state-transitions nil))



;;; `token-for-fsm-state' - is a development only structure to
;;; help get more useful information about an fs-state.

#+development
(def-structure token-for-fsm-state
  (token-for-fsm-state-number nil)
  (token-for-fsm-state-name nil))








;;; `state-transition' - the "arc" between nodes in a
;;; state-transition diagram.

(def-structure state-transition
  (state-transition-test nil)
  (state-transition-args nil)
  (state-transition-next nil)
  (state-transition-index-of-test
    state-transition-user-defined-transition-test-sentinel)
  (state-transition-arg-count nil))



;;; `parse-object' - this is a probably overused structure insofar as it
;;; is used by both the tokenizer and the parser.  The tokenizer uses the
;;; first three slots (type, start-index, and end-index), and the parser
;;; uses the fourth slot (value) when it executes the production rules.

(def-structure parse-object
  (parse-object-type nil)
  (parse-object-start-index nil)
  (parse-object-end-index nil)
  (parse-object-value nil))



;;; `current-lexing-rule-number'

(defvar current-lexing-rule-number 0)

;;; `current-character'

(defvar current-character nil)



;;; `empty-lexing-table' - the value to return when there are no
;;; tokens.  Also helpful as an :r value.

(defun-simple empty-lexing-table ()
  (let* ((current-lexing-rule-number 0)
         (empty-lexer (make-lexing-table))
         (root-node (create-fsm-state)))
    (setf (lexing-table-start-state empty-lexer) root-node)
    empty-lexer))


;;; `create-fsm-state'

(defun-simple create-fsm-state ()
  (let ((new-state (make-fsm-state)))
    (setf (fsm-state-associated-rules new-state)
          (token-list current-lexing-rule-number))
    (setf (fsm-state-accepts-token? new-state) nil)
    new-state))


;;; `set-fsm-state-accepts-token'

(defmacro set-fsm-state-accepts-token (fsm-state number)
  `(setf (fsm-state-accepts-token? ,fsm-state) ,number))



;;; `get-fsm-state-accepts-token-number'

(defmacro get-fsm-state-accepts-token-number (fsm-state)
  `(fsm-state-accepts-token? ,fsm-state))



;;; `token-index->symbol'

(defmacro token-index->symbol (number)
  `(internal-token-name
     (svref
       (lexing-table-token-array
         current-tokenizer)
       ,number)))



;;; `get-fsm-state-accepts-token-name?'

(defmacro get-fsm-state-accepts-token-name? (fsm-state)
  `(let ((token (fsm-state-accepts-token? ,fsm-state)))
     (and token (token-index->symbol token))))


;;; `state-transition-is-standard-test-p'

(defmacro state-transition-is-standard-test-p (transition)
  `(/=f (state-transition-index-of-test ,transition)
        state-transition-user-defined-transition-test-sentinel))

;;; `create-standard-state-transition'

(defun-simple create-standard-state-transition (test args next)
  (let ((the-transition (make-state-transition)))
    (setf (state-transition-test the-transition) test)
    (setf (state-transition-args the-transition) args)
    (setf (state-transition-next the-transition) next)
    (setf (state-transition-index-of-test the-transition)
          (alphabet-get-index-for-transition-test test))
    (let ((arg-count (length args)))
      (when (>f arg-count maximum-state-transition-args)
        (error "Too many state transition arguments"))
      (setf (state-transition-arg-count the-transition)
            arg-count))
    the-transition))


;;; `create-nonstandard-state-transition'

(defun-simple create-nonstandard-state-transition (test args next)
  (let ((the-transition (make-state-transition)))
    (setf (state-transition-test the-transition) test)
    (setf (state-transition-args the-transition) args)
    (setf (state-transition-next the-transition) next)
    (setf (state-transition-index-of-test the-transition)
          state-transition-user-defined-transition-test-sentinel)
    (let ((arg-count (length args)))
      (when (>f arg-count maximum-state-transition-args)
        (error "Too many state transition arguments"))
      (setf (state-transition-arg-count the-transition)
            arg-count))
    the-transition))


;;; `create-epsilon-state-transition'

(defun-simple create-epsilon-state-transition (next)
  (let ((the-transition (make-state-transition)))
    (setf (state-transition-test the-transition) nil)
    (setf (state-transition-args the-transition) nil)
    (setf (state-transition-next the-transition) next)
    (setf (state-transition-index-of-test the-transition)
          state-transition-user-defined-transition-test-sentinel)
    (setf (state-transition-arg-count the-transition) 0)
    the-transition))


;;; `reclaim-transition'

(defun-simple reclaim-transition (transition)
  (let ((args (state-transition-args transition)))
    (when (consp args)
      (reclaim-token-tree args))
    (reclaim-state-transition transition)))


;;; `transition='

(defun-simple transition= (transition-1 transition-2)
    (and transition-2
         (eq (state-transition-test transition-1)
             (state-transition-test transition-2))
         (eq
           (state-transition-next transition-1)
           (state-transition-next transition-2))
         (equal
           (state-transition-args transition-1)
           (state-transition-args transition-2))))


;;; `replicate-transition' - makes a new transition which has the
;;; same test on its arc as the given transition, but with a new
;;; destination.  I use this in creating dfa transitions from
;;; nfa transitions.

(defun-simple replicate-transition (old-transition new-destination)
  (let ((new-transition (make-state-transition))
        (old-args (state-transition-args old-transition)))
    (setf (state-transition-test new-transition)
          (state-transition-test old-transition))
    (setf (state-transition-args new-transition)
          (if (consp old-args)
              (copy-tree-using-token-conses old-args)
              old-args))
    (setf (state-transition-next new-transition) new-destination)
    (setf (state-transition-index-of-test new-transition)
          (state-transition-index-of-test old-transition))
    (setf (state-transition-arg-count new-transition)
          (state-transition-arg-count old-transition))
    new-transition))





;;; `create-parse-object'

(defun-simple create-parse-object (type value)
  (let ((the-parse-object (make-parse-object)))
    (setf (parse-object-type the-parse-object) type)
    (setf (parse-object-value the-parse-object) value)
    the-parse-object))




;;; `destructive-bubble-sort'

(defun-void destructive-bubble-sort (list less-than-predicate)
  (loop with pointer = list
        while pointer do
    (loop with smallest = (car pointer)
          for element on pointer do
      (when (funcall-simple-compiled-function
              less-than-predicate (car element) smallest)
        (setf (car pointer) (car element))
        (setf (car element) smallest)
        (setq smallest (car pointer))))
    (setq pointer (cdr pointer))))


;;; `token-copy-of-list-without-duplicates'

(defun token-copy-of-list-without-duplicates (list eql-test)
  (loop with result-list = '()
        with duplicate-list = '()
        for element in list do
    (if (member element result-list :test eql-test)
        (token-push element duplicate-list)
        (token-push element result-list))
        finally
          (return (values (nreverse result-list)
                          duplicate-list))))


;;; `sort-list-destructively-separating-duplicates'

(defun sort-list-destructively-separating-duplicates
    (list less-than-test eql-test)
  (destructive-bubble-sort list less-than-test)
  (multiple-value-prog1
      (token-copy-of-list-without-duplicates list eql-test)
    (reclaim-token-list list)))




;;;; Character Classes

;;; A character class is used to specify a range of characters.  At the
;;; G2 level, character classes are specified using curly braces, where
;;; the characters between the curly braces make up the members of the
;;; class.  There are two possible kinds of members: characters and
;;; ranges, where a range is specified with an unescaped hyphen between
;;; two characters.  For example, a very common class is "{a-z}", which
;;; represents the range from #\a to #\z, or the lower case letters.
;;;
;;; Internally, a character class is represented as a single transition,
;;; whose test is the function named by the constant ALPHABET-CHARACTER-CLASS
;;; (thereby requiring a funcall, but this is not really a loss in efficiency
;;; since the paradigm for traversing a transition calls for a funcall in
;;; the general case), and whose args are a list of dotted-pairs of _fixnums_.
;;; The regular expression tokenizer turns "{k-az}" into (character-class
;;; (range %\a %\b) %\z), where %\ is used to indicate the character encoding.
;;; Before using this list as the arguments for a transition, the character
;;; representation must be converted to fixnums if it is not already using
;;; fixnums, and the list must be standardized.  We also support inverted
;;; classes, which specify which characters *not* to match.  Internally,
;;; these classes are converted into standard classes by first standardizing
;;; their arguments and then inverting them.


;;; `range' - a range is a sorted dotted pair of fixnums within the
;;; character encoding.

(def-concept range)


;;; `range<'

(defun-simple range< (range-a range-b)
  (<f (car range-a) (car range-b)))


;;; `range='

#+unused
(defun-simple range= (range-a range-b)
  (and (=f (car range-a) (car range-b))
       (=f (cdr range-a) (cdr range-b))))


;;; `null-pattern' - a string in the current alphabet which
;;; represents a null regular expression.

(defparameter null-pattern
  (let ((tmp (alphabet-make-uninitialized-text-string 2)))
    (setf (alphabet-string-element tmp 0) alphabet-character-class-open)
    (setf (alphabet-string-element tmp 1) alphabet-character-class-close)
    tmp))




;;; `character-class-member-p' - the test for the transition arc which
;;; specifies a character class.  "class-list" should always be a list
;;; of dotted pairs of fixnums.  "element" is a canonical member of the
;;; alphabet.  The function alphabet-between should be written to allow
;;; comparison between a member of the alphabet and two fixnums, which
;;; represent character encodings.

(defun-simple character-class-member-p (element class-list)
  (loop for class-member in class-list
        thereis (alphabet-between element
                                  (car class-member)
                                  (cdr class-member))))

(defmacro character-class-member-p-macro (element class-list)
  (if (constantp class-list)
      `(or ,@(loop for (low . high) in (eval class-list)
                   collect (if (=f low high)
                               `(=f ,element ,low)
                               `(alphabet-between ,element ,low ,high))))
      (let ((element-var (make-symbol "ELEMENT")))
        `(loop with ,element-var = ,element
               for class-member in ,class-list
               thereis (alphabet-between ,element-var
                                         (car class-member)
                                         (cdr class-member))))))




;;; `sort-standardized-character-class'

(defun-simple sort-standardized-character-class (class-members-list)
  (destructive-bubble-sort class-members-list #'range<)
  class-members-list)




;;; `bad-character-class-error-message' - should I make this say something
;;; different in the (very unfortunate) case of a non-development error?

(defmacro bad-character-class-error-message (element)
  `(format nil "~a~a"
           (format nil "Bad member of character class: ~s.  " element)
           (if (and (consp ,element)
                    (consp (cdr ,element)))
                   "Pairs must be *DOTTED* lists."
                   (format nil
                           "Elements must be fixnums ~
                            ~%         between ~d and ~d inclusive."
                           alphabet-min-code alphabet-max-code))))



;;; `standardize-character-class-list' - A standard character-class list is:
;;; (a) non-overlapping (i.e., '((100 . 200) (150 . 250)) is not standard);
;;; (b) sorted;  (c) made up of ranges (dotted-pair fixnum lists).  A single
;;; character x must be converted to the range (x . x).

(defun-simple standardize-character-class-list (character-class-list)
  (loop with reversed-list = (token-reverse character-class-list)
        for element in reversed-list
        with revised-list = '() do
    (cond
      ((alphabet-character-code-p element)
       (token-push (token-cons element element) revised-list))
      ((listp element)
       (let ((first (car element))
             (last (cdr element)))
         (if (and (alphabet-character-code-p first)
                  (alphabet-character-code-p last))
             (token-push (token-cons (minf first last)
                                     (maxf first last))
                         revised-list)
             (error
               (bad-character-class-error-message element)))))
      (t
       (error
         (bad-character-class-error-message element))))
        finally
          (sort-standardized-character-class revised-list)
          (reclaim-token-list reversed-list)
          (return revised-list)))



;;; `invert-range'

(defun-simple invert-range (range-list)
  (loop with first-member = (caar range-list)
        with inverted-list
          = (cond
              ((=f first-member alphabet-min-code)
               '())
              ((=f (1-f first-member) alphabet-min-code)
               (token-list (token-cons alphabet-min-code alphabet-min-code)))
              (t
               (token-list
                 (token-cons alphabet-min-code (1-f first-member)))))
        for rest-of-list on range-list
        as this = (car rest-of-list)
        as next = (cadr rest-of-list)
        as last-this = (cdr this)
        as first-next = (car next)
        as difference = (and first-next last-this (-f first-next last-this))
        do
    (cond
      ((or (null difference)
           (<f difference 2))
       t)
      ((=f difference 2)
       (token-push (token-cons (1-f first-next) (1-f first-next)) inverted-list))
      (t
       (token-push (token-cons (1+f last-this) (1-f first-next)) inverted-list)))
        finally
          (if (=f last-this alphabet-max-code)
              (token-push (token-cons alphabet-max-code alphabet-max-code)
                          inverted-list)
              (token-push (token-cons (1+f last-this) alphabet-max-code)
                          inverted-list))
          (return (nreverse inverted-list))))


;;; `standardize-inverted-character-class-list'

(defun-simple standardize-inverted-character-class-list (class-members-list)
  (let* ((standardized-tree (standardize-character-class-list class-members-list))
         (inverted-tree (invert-range standardized-tree)))
    (reclaim-token-tree standardized-tree)
    inverted-tree))



;;; `collate-two-transitions'

#+obsolete
(defun collate-two-transitions (major-args-orig minor-args-orig)
  (loop with noncolliding-a = '()
        with noncolliding-b = '()
        with intersection = '()
        with major-args = (copy-tree-using-token-conses (car major-args-orig))
        with minor-args = (copy-tree-using-token-conses (car minor-args-orig))
        for next-a in major-args
        as next-a-first = (car next-a)
        as next-a-last = (cdr next-a)
        with next-b = (token-pop minor-args)
        with next-b-first = (car next-b)
        with next-b-last
        do
    (if (or (null next-b) (null (car next-b)))
        (token-push next-a noncolliding-a)
        (loop with done = nil
              until done
              do
          (setq next-b-first (car next-b))
          (setq next-b-last (cdr next-b))
          (cond
            ((=f next-a-first next-b-first)
             (cond
               ((=f next-a-first next-b-first)
                (cond
                  ((=f next-a-last next-b-last)
                   (token-push next-a intersection)
                   (setq next-b (token-pop minor-args))
                   (setq done t))
                  ((<f next-b-last next-a-last)
                   (token-push next-b intersection)
                   (setf (car next-a) (1+f next-b-last))
                   (setq next-a-first (car next-a))
                   (token-push next-b noncolliding-b)
                   (setq next-b (token-pop minor-args))
                   (when (null next-b)
                     (token-push next-a noncolliding-a)
                     (setq done t)))
                  (t
                   (token-push next-a intersection)
                   (setf (car next-b) (1+f next-a-first))
                   (setq done t))))))
            ((>f next-a-first next-b-first)
             (cond
               ((>f next-a-first next-b-last)
                (token-push next-b noncolliding-b)
                (setq next-b (token-pop minor-args))
                (when (null next-b)
                  (token-push next-a noncolliding-a)
                  (setq done t)))
               (t
                (token-push (token-cons next-b-first (1-f next-a-first)) noncolliding-b)
                (setf (car next-b) next-a-first))))
            (t
             (cond
               ((<f next-a-last next-b-first)
                (token-push next-a noncolliding-a)
                (setq done t))
               (t
                (token-push (token-cons next-a-first (1-f next-b-first)) noncolliding-a)
                (setq next-a-first next-b-first)
                (setf (car next-a) next-b-first)))))))
        finally
          (when next-b (token-push next-b noncolliding-b))
          (loop for remaining-b in minor-args do
            (token-push remaining-b noncolliding-b))
          (return (values (token-list (nreverse noncolliding-a))
                          (token-list (nreverse noncolliding-b))
                          (token-list (nreverse intersection))))))



;;; `resolve-colliding-transitions' - note that the order in which the
;;; transitions are pushed onto the list is very important.

#+obsolete
(defun-simple resolve-colliding-transitions (major-transition minor-transition)
  (let ((old-major-args (state-transition-args major-transition))
        (old-minor-args (state-transition-args minor-transition)))
    (multiple-value-bind
        (new-major-args new-minor-args intersection)
        (collate-two-transitions old-major-args old-minor-args)
      (let* ((major-next (state-transition-next major-transition))
             (minor-next (state-transition-next minor-transition))
             (new-transitions '()))
        (unless (null (car new-minor-args))
          (if (equal new-minor-args old-minor-args)
              (token-push minor-transition new-transitions)
              (token-push (create-standard-state-transition
                            alphabet-character-class-st-test
                            new-minor-args minor-next)
                          new-transitions)))
        (unless (null (car intersection))
          (if (equal intersection old-minor-args)
              (token-push minor-transition new-transitions)
              (token-push (create-standard-state-transition
                            alphabet-character-class-st-test
                            intersection minor-next)
                          new-transitions))
          (if (equal intersection old-major-args)
              (token-push major-transition new-transitions)
              (token-push (create-standard-state-transition
                            alphabet-character-class-st-test
                            (copy-tree-using-token-conses intersection)
                            major-next)
                          new-transitions)))
        (unless (null (car new-major-args))
          (if (equal new-major-args old-major-args)
              (token-push major-transition new-transitions)
              (token-push (create-standard-state-transition
                            alphabet-character-class-st-test
                            new-major-args major-next)
                          new-transitions)))
        new-transitions))))



;;; `collate-range-transitions-1'

#+obsolete
(defun-simple collate-range-transitions-1 (list-of-transitions)
  (let* ((pointer-to-next-transition list-of-transitions)
         (major-transition (pop pointer-to-next-transition))
         (transformed-transitions '()))
    (loop with minor-transition = (pop pointer-to-next-transition)
          while minor-transition do
      (let ((new-transitions
              (resolve-colliding-transitions
                major-transition minor-transition)))
        (loop for transition in new-transitions do
          (unless (eq transition major-transition)
            (token-pushnew-eq transition transformed-transitions)))
        (setq minor-transition (pop pointer-to-next-transition))))
    (token-push major-transition transformed-transitions)
    transformed-transitions))


;;; `collate-range-transitions'

#+obsolete
(defun-simple collate-range-transitions (list-of-transitions)
  (let ((unresolved-range-transitions '())
        resolved-range-transitions
        (resolved-transitions '()))
    (loop for transition in list-of-transitions do
      (if (eq (state-transition-test transition) alphabet-character-class-st-test)
          (token-push transition unresolved-range-transitions)
          (token-push transition resolved-transitions)))
    (setq resolved-range-transitions
          (collate-range-transitions-1 unresolved-range-transitions))
    (loop for trans in resolved-range-transitions do
      (token-push trans resolved-transitions))
    (reclaim-token-list resolved-range-transitions)
    (reclaim-token-list unresolved-range-transitions)
    resolved-transitions))






;;; `regular-expression-metacharacters'

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter regular-expression-metacharacters
  (loop for (nil pattern) in regular-expression-tokens
        when (alphabet-character-code-p pattern)
          collect pattern))
)

;;; `built-in-character-codes' is an association list between the
;;; symbols which name the built-in class, and the code to substitute.

(defvar built-in-character-codes '())


;;; `def-built-in-class'

(defmacro def-built-in-class (class-name class-members)
  (let ((class-value
          (twith-output-to-text-string
            (alphabet-twrite-character alphabet-character-class-open)
            (loop for class-member in (symbol-value class-members) do
              (cond
                ((alphabet-character-code-p class-member)
                 (when (memq-p-macro class-member
                                     regular-expression-metacharacters)
                   (alphabet-twrite-character alphabet-escape-character))
                 (alphabet-twrite-character class-member))
                ((listp class-member)
                 (let ((first (car class-member))
                       (last (cdr class-member)))
                   (cond
                     ((and (alphabet-character-code-p last)
                           (alphabet-character-code-p first))
                      (when (memq first regular-expression-metacharacters)
                        (alphabet-twrite-character alphabet-escape-character))
                      (alphabet-twrite-character first)
                      (alphabet-twrite-character alphabet-character-class-range)
                      (when (memq last regular-expression-metacharacters)
                        (alphabet-twrite-character alphabet-escape-character))
                      (alphabet-twrite-character last))
                     (t
                      (error alphabet-not-character-code-error-message)))))
                (t
                 (error "Members of classes must be character codes ~
                          or dotted pairs of character codes.  ~a"
                        alphabet-not-character-code-error-message))))
            (alphabet-twrite-character alphabet-character-class-close))))
    `(token-push (token-cons ',class-name ',class-value) built-in-character-codes)))



(def-built-in-class alphabetic    alphabet-alphabetic-chars)
(def-built-in-class numeric       alphabet-numeric-chars)
(def-built-in-class hexadecimal   alphabet-hexadecimal-chars)
(def-built-in-class g2symbol      alphabet-symbol-character-class)
(def-built-in-class alphanumeric  alphabet-alphanumeric-chars)
(def-built-in-class whitespace    alphabet-whitespace-chars)
(def-built-in-class double-quote  alphabet-double-quote-chars)
(def-built-in-class left-bracket  alphabet-left-bracket-chars)
(def-built-in-class right-bracket alphabet-right-bracket-chars)






;;; `current-tokenizer' - to be bound to a "lexing-table"

(defvar current-tokenizer nil)


;;; `current-start-state' is bound in conjunction with
;;; current-tokenizer, and they should always be kept in
;;; synch.

(defvar current-start-state nil)



;;; `current-lexing-strings' is an association list between pattern names
;;; and the text-strings which should be substituted for them.

(defvar current-lexing-strings '())


;;; `current-lexing-patterns'

(defvar current-lexing-patterns '())


;;; `current-anchor-p' - when set to true, the search for the next token
;;; is considered to be "anchored" at the starting position.  When nil,
;;; the search will find the earliest match, not necessarily at the start
;;; position specified.
;;;   This variable only has relevance for the "simple" text patterns.
;;; (The find-xxx-pattern funcalled evaluators.) The tokenizer search
;;; is always considered anchored.

(defvar current-anchor-p nil)



;;; `known-regexp-functions' - a list of supported regular expression
;;; constructs (e.g., KLEENE, SEQ, etc.)

(defvar known-regexp-functions '())


;;; `in-lexing-context' - binds the variables current-tokenizer
;;; and current-start-state for the extent of the body.

(defmacro in-lexing-context (lex-fa &body body)
  `(let* ((current-tokenizer ,lex-fa)
          (current-start-state
            (lexing-table-start-state current-tokenizer))
          (current-anchor-p (lexing-table-search-is-anchored-p
                              current-tokenizer)))
     ,@body))




;;;; Reclaiming a tokenizer


;;; `get-all-states' - beginning at the start state of the current tokenizer
;;; performs a breadth-first search of the tokenizer tree, and returns a list
;;; of all the nodes it finds.  It would be easy enough to maintain a list of
;;; all states for the life of a tokenizer, obviating this function.  However,
;;; that would take up space.  I'm still not sure which is the better approach.

(defun-simple get-all-states ()
  (loop with to-be-done = '()
        with current-state? = current-start-state
        with done-already = (and current-state?
                                 (token-list current-state?))
        while current-state?
        for current-transitions
            = (fsm-state-transitions current-state?)
        do
    (loop for transition in current-transitions
          as dest = (state-transition-next transition)
          unless (memq-p-macro dest done-already) do
              (token-pushnew-eq dest to-be-done))
    (setq current-state? (token-pop to-be-done))
    (when current-state?
      (token-push current-state? done-already))
        finally
          (return done-already)))


;;; `get-all-states-from-tokenizer'

(defun-simple get-all-states-from-tokenizer (lexing-table)
  (in-lexing-context lexing-table (get-all-states)))



;;; `reclaim-tokenizing-state'

(defun-void reclaim-tokenizing-state (state)
  (let ((current-transitions (fsm-state-transitions state)))
    (reclaim-token-list (fsm-state-associated-rules state))
    (loop for next-transition in current-transitions do
      (reclaim-transition next-transition))
    (reclaim-token-list current-transitions)
    (reclaim-fsm-state state)))



;;; `reclaim-dfa'

(defun-void reclaim-dfa (lexing-table)
  (let ((list-of-states
          (get-all-states-from-tokenizer lexing-table))
        (token-array
          (lexing-table-token-array lexing-table)))
    (loop for state in list-of-states do
      (reclaim-tokenizing-state state))
    (reclaim-token-list list-of-states)
    (when token-array
      (loop for i from 0 below (length token-array) do
	(let ((token? (svref token-array i)))
          (when token? 
            (reclaim-internal-token token?))))
      (reclaim-managed-simple-vector (lexing-table-token-array lexing-table))))
  (reclaim-lexing-table lexing-table))


;;; `reclaim-nfa'

(defun-void reclaim-nfa (lexing-table)
  (let ((list-of-states
          (get-all-states-from-tokenizer lexing-table)))
    (loop for state in list-of-states do
      (reclaim-tokenizing-state state))
    (reclaim-token-list list-of-states))
  (reclaim-lexing-table lexing-table))


;;; `reclaim-current-dfa' - needs to be a macro to change the value
;;; of current-tokenizer to nil.

#+development
(defmacro reclaim-current-dfa ()
  (when (and (boundp 'current-tokenizer)
             (not (null current-tokenizer)))
    `(progn
       (reclaim-dfa current-tokenizer)
       (setq current-tokenizer nil)
       (setq current-start-state nil))))


;;; `reclaim-dfa-if-any'

(defun-void reclaim-dfa-if-any (lexing-table)
  (when lexing-table
    (reclaim-dfa lexing-table)))


#+development
(defun token-conses-used-by-lexer (lexing-table)
  (let ((list-of-states (get-all-states-from-tokenizer lexing-table)))
    (prog1
        (token-conses-used-by-states list-of-states)
      (reclaim-token-list list-of-states))))


#+development
(defun token-conses-used-by-states (list-of-states)
  (loop with number-of-conses = 0
        for state in list-of-states
        do
    (incff number-of-conses (token-conses-used-by-state state))))




#+development
(defun-void test-nfa-leaks (tokenizer-specification)
  (let ((old-conses (outstanding-token-conses))
        new-conses
        new-nfa)
    (format t "originally ~d conses are outsanding~%" old-conses)
    (setq new-nfa (compile-nfa tokenizer-specification))
    (setq new-conses (outstanding-token-conses))
    (format t "creation took ~d conses (now ~d outstanding)~%"
            (-f new-conses old-conses) new-conses)
    (reclaim-dfa new-nfa)
    (setq new-conses (outstanding-token-conses))
    (format t "now ~d conses outstanding; leaked ~d~%"
            new-conses (-f new-conses old-conses))))



#+development
(defun number-of-conses-in-tree (tree)
  (cond
    ((atom tree)
     0)
    (t
     (+f
       (number-of-conses-in-tree (car tree))
       (number-of-conses-in-tree (cdr tree))
       1))))



;;; `check-jv-memory-management'

#+development
(defmacro check-jv-memory-management (&optional format-string &rest args)
  `(progn
     (when ,format-string
       (dmesg (format nil ,format-string ,@args))
       (terpri))
     (check-jv-memory-management-function)))



#+development
(defun check-jv-memory-management-function ()
  (let ((expected-conses 0)
        (expected-parse-objects 0)
        (expected-tokens 0)
        (expected-states 0)
        (expected-strings 0)
        (expected-arrays 0))
    (dmesg "~d outstanding token conses.~%"
           (-f (outstanding-token-conses) expected-conses))
    (dmesg "~d outstanding parse objects.~%"
           (-f (outstanding-parse-object-count) expected-parse-objects))
    (dmesg "~d outstanding g2 tokens.~%"
           (-f (outstanding-g2-token-count) expected-tokens))
    (dmesg "~d outstanding state transitions.~%"
           (outstanding-state-transition-count))
    (dmesg "~d outstanding fsm states.~%"
           (-f (outstanding-fsm-state-count) expected-states))
    (dmesg "~d outstanding internal tokens.~%"
           (outstanding-internal-token-count))
    (dmesg "~d outstanding lexing tables.~%"
           (outstanding-lexing-table-count))
    (dmesg "~d outstanding wide-strings.~%"
           (-f (outstanding-wide-strings) expected-strings))
    (dmesg "~d outstanding simple vectors.~%"
           (-f (outstanding-simple-vector-pool-vectors)
               expected-arrays))))





;;;; Building the State Machines



;;; `def-default-tokenizer' - to set a default or for interactive usage

(defmacro def-default-tokenizer (lexing-table)
  `(progn
     (setq current-tokenizer ,lexing-table)
     (setq current-start-state
           (lexing-table-start-state ,lexing-table))
     current-tokenizer))



;;; `def-lexing-table' - the name def-tokenizer is already in
;;; use; I'd like to manage to fold the two definitions into
;;; one soon, but for now I'll use this different name.

(defmacro def-lexing-table (tokenizer-name tokenizer-definition)
  `(progn
     (defvar ,tokenizer-name)
     (setq ,tokenizer-name
           (compile-permanent-lexing-table
            ,tokenizer-definition))))



;;; `regexp-evaluator' - the function to call when reading a symbol
;;; in a pattern cons.

(def-global-property-name regexp-evaluator)




;;; `def-regexp-operator' - I want to try to make the standard
;;; operations supported by the tokenizer easy to define and modify
;;; (and I also want to avoid having a single, coded, 200 line
;;; function.)  The current scheme I have allows one to define
;;; a symbol as a "regexp-operator", which can then be present
;;; in a pattern cons.  With the operator, one defines code to
;;; be executed when that symbol is encountered.  However, it
;;; is pretty clumsy, as the regexp-operators must operate on
;;; the variables "exp", "in-node" and "out-node".  I should
;;; definitely try to make these things more modular, or give
;;; up and write the huge function.

(defmacro def-regexp-operator
    (op-name (exp-var-name in-var-name out-var-name) &body body)
  (let ((function-name
          (intern (format nil "PATTERN-TRANSFORM-~:@(~A~)" op-name))))
    `(progn
       (token-push ',op-name known-regexp-functions)
       (defun-void ,function-name (,exp-var-name ,in-var-name ,out-var-name)
         ,@body)
       (setf (regexp-evaluator ',op-name) #',function-name)
       ',function-name)))






;;;; Constructing an NFA from a Regular Expression

;;; The regular expression must use a special Lisp syntax.
;;; For example, a(b|c|d)*e would be coded as
;;;   (seq 'a (kleene (either 'b 'c 'd)) 'e)
;;; I refer to the above expression as a "pattern cons".
;;; It could, of course, also be coded as
;;;   (seq 'a (seq (kleene (either 'b (either 'c 'd))) 'e))
;;; That is, only one or two arguments per function.  In fact,
;;; when using the G2 parser to transform regular expressions
;;; from the familiar syntax "a(b|c|d)*e" into the slot value
;;; for the tokenizer class, that is what it will be transformed
;;; into.




;;; `compile-pattern-rec' - this is the driving function which takes
;;; the pattern cons, uses the regexp-operators, and returns an nfa
;;; to match the pattern (or signals an error if there is a syntax
;;; error in the pattern cons.)  It calls functions which call it
;;; back, leading to a possibly deep tail recursion, but it is not
;;; terribly inefficient.
;;;
;;; I'm not quite sure how to handle the error cases.  This function
;;; is only called with input which is the result of output from
;;; parse-regexp-string, which returns nil when given a bad regular
;;; expression.  So there should be no way that the user can reach
;;; either of the error statements below.  If control does reach
;;; either of those points, then it should be a fatal error.

(defun-void compile-pattern-rec (exp in-node out-node)
  (cond
    ((alphabet-canonical-element-p exp)
     (pattern-transform-canonical exp in-node out-node))
    ((listp exp)
     (let* ((operator (car exp))
            (evaluator-function (regexp-evaluator operator)))
       (if evaluator-function
           (funcall-simple-compiled-function
             evaluator-function exp in-node out-node)
           (error "Unknown regular expression operator: ~s" operator))))
    (t
     (error "Bad parse of regular expression: ~s~%" exp))))




;;; `canonical' - the canonical elements for a given alphabet
;;; (typically characters) are placed in the pattern
;;; description without modifiers, for example,
;;;   (seq #\c #\a #\r)
;;; Therefore, this is a special case which is signaled not
;;; by the keyword "canonical", but by applying the current
;;; canonical alphabet element predicate to the argument.

(def-regexp-operator canonical (exp in-node out-node)
  (token-push (create-standard-state-transition
                alphabet-equality-st-test
                (token-list exp)
                out-node)
              (fsm-state-transitions in-node)))


;;; `nil' - a special case.  A tokenizer which recognizes the
;;; null string is dangerous (it could easily lead to infinite
;;; loops), but we will allow it.  It is a special case because
;;; it may not explicitly specified.  I count on (car nil) to
;;; return nil.

(def-regexp-operator nil (exp in-node out-node)
  (declare (ignore exp))
  (token-push (create-epsilon-state-transition
                out-node)
              (fsm-state-transitions in-node)))



;;; `test' allows the pattern to include Lisp functions
;;; defined in G2 to be applied to the input character.
;;; The default test is alphabet-dependent, but for unicode
;;; would be "char=w".  So, for example, a transition on
;;; #\a will succeed if the input character is char=w a.
;;; Using "test" allows the pattern writer to change that
;;; default function, so that by specifying (test alpha-char-p),
;;; the transition will test if the input character is
;;; alpha-char-p.

(def-regexp-operator test (exp in-node out-node)
  (let ((new-trans (create-nonstandard-state-transition
                     (cadr exp)
                     (copy-tree-using-token-conses (cddr exp))
                     out-node)))
    (token-push new-trans
                (fsm-state-transitions in-node))))


;;; `seq' indicates a sequence of characters.  The Unix
;;; regular expression analog of this function is no function
;;; at all -- it is implied.  Saying "grep cat" to the shell
;;; means the sequence of characters 'c' 'a' 't'.  For our
;;; pattern conses, "seq" must be specified explicitly.

(def-regexp-operator seq  (exp in-node out-node)
  (loop with prev-node = in-node
        for arg-tail on (cdr exp)
        as arg = (car arg-tail)
        as next-node =  (if (cdr arg-tail)
                            (create-fsm-state)
                            out-node)
        do
    (compile-pattern-rec
      arg prev-node next-node)
    (setf prev-node next-node)))


;;; `either' - the "|" operator in regular expressions.
;;; the pattern (either #\a #\b) should match an input
;;; character 'a' or 'b'.

(def-regexp-operator either (exp in-node out-node)
    (loop for arg in (cdr exp)
          do
      (let ((new-start (create-fsm-state))
            (new-end (create-fsm-state)))
        (token-push
          (create-epsilon-state-transition new-start)
          (fsm-state-transitions in-node))
        (token-push
          (create-epsilon-state-transition out-node)
          (fsm-state-transitions new-end))
        (compile-pattern-rec
          arg new-start new-end))))


;;; `kleene' - the * operator in lex and some other Unix
;;; utilities.  It means zero or more occurrences of its
;;; argument (which in lex precedes it; in pattern conses,
;;; follows it.)  This usage is different than filename
;;; globbing done by the Unix shells.  There, '*' represents
;;; zero or more occurrences of ANY character.  That usage
;;; can be achieved by using (kleene (dot)).
;;;
;;; Note that kleene will always succeed in a match, because it
;;; matches the null string.  Therefore, the user must be careful
;;; to avoid infinite loops.

(def-regexp-operator kleene  (exp in-node out-node)
  (unless (null (cddr exp))
    (error "Kleene Star takes one sub-expression."))
  (let ((new-in-node (create-fsm-state))
        (new-out-node (create-fsm-state)))
    (token-push (create-epsilon-state-transition new-in-node)
                (fsm-state-transitions in-node))
    (token-push (create-epsilon-state-transition out-node)
                (fsm-state-transitions in-node))
    (token-push (create-epsilon-state-transition out-node)
                (fsm-state-transitions new-out-node))
    (token-push (create-epsilon-state-transition new-in-node)
                (fsm-state-transitions new-out-node))
    (compile-pattern-rec
      (cadr exp) new-in-node new-out-node)))




;;; `pattern'

(def-regexp-operator pattern (exp in-node out-node)
  (let ((lookup nil)
        (pattern-name nil))
    (cond
      ((null (cdr exp))
       (error "Pattern requires one argument."))
      ((cddr exp)
       (error "Pattern takes only one argument."))
      ((null (setq pattern-name (cadr exp)))
       (error "Nil is an invalid pattern name."))
      ((not (symbolp pattern-name))
       (error "Pattern names must be symbols; ~s is not valid." pattern-name))
      ((null (setq lookup (assq pattern-name current-lexing-patterns)))
       (error "Pattern ~s not found" pattern-name))
      (t
       (compile-pattern-rec
         (cadr lookup) in-node out-node)))))



;;; `plus' - similar to kleene, but means one or more occurences
;;; of its argument.  Does not match the null string.

(def-regexp-operator plus (exp in-node out-node)
  (unless (null (cddr exp))
    (error "Kleene plus takes one sub-expression."))
  (let ((new-in-node (create-fsm-state))
        (new-out-node (create-fsm-state)))
    (token-push (create-epsilon-state-transition new-in-node)
                (fsm-state-transitions in-node))
    (token-push (create-epsilon-state-transition out-node)
                (fsm-state-transitions new-out-node))
    (token-push (create-epsilon-state-transition new-in-node)
                (fsm-state-transitions new-out-node))
    (compile-pattern-rec
      (cadr exp) new-in-node new-out-node)))


;;; `maybe' - the "?" operator, meaning zero or one
;;; occurence of its argument.  Maybe maybe should
;;; have a better name.

(def-regexp-operator maybe (exp in-node out-node)
  (unless (null (cddr exp))
    (error "Maybe takes one sub-expression."))
  (let ((new-in-node (create-fsm-state))
        (new-out-node (create-fsm-state)))
    (token-push (create-epsilon-state-transition new-in-node)
                (fsm-state-transitions in-node))
    (token-push (create-epsilon-state-transition out-node)
                (fsm-state-transitions in-node))
    (token-push (create-epsilon-state-transition out-node)
                (fsm-state-transitions new-out-node))
    (compile-pattern-rec
      (cadr exp) new-in-node new-out-node)))



;;; `dot' - matches one occurrence of any member of the alphabet.

(def-regexp-operator dot  (exp in-node out-node)
  (unless (null (cdr exp))
    (error "Dot does not take arguments."))
  (let ((new-trans (create-standard-state-transition
                     alphabet-canonical-element-st-test
                     nil
                     out-node)))
    (token-push new-trans
                (fsm-state-transitions in-node))))





;;; `range' - essentially the operator for character classes.  However,
;;; range should not be used to specify alternatives (either should be
;;; used instead.  For example, the pattern {a-zA-z_-} should be
;;; transformed into:
;;;     (either (range #\a #\z) (range #\A #\Z) #\_ #\-)
;;; That is, the hyphen, '-', should be interpreted as the range
;;; operator, and a lack of operator should be implied as alternatives.
;;; For another example, {akw} is just (either #\a #\k #\w).
;;; Finally, {} is transformed into nil.  This is, of course, a
;;; dangerous token pattern to allow, because it could cause infinite
;;; loops.  However, it is not a problem if it is just part of a
;;; token definition, and even if it is by itself, we will allow it.

(def-regexp-operator character-class (exp in-node out-node)
    (unless (null (cddr exp))
      (error "Range takes only one argument"))
  (token-push (create-standard-state-transition
                alphabet-character-class-st-test
                (token-list (standardize-character-class-list (cadr exp)))
                out-node)
              (fsm-state-transitions in-node)))


;;; `inverted-class'

(def-regexp-operator inverted-class (exp in-node out-node)
  (unless (null (cddr exp))
    (error "Range takes only one argument"))
  (unless (listp (cadr exp))
    (error "The argument to inverted class must be a LIST."))
  (token-push (create-standard-state-transition
                alphabet-character-class-st-test
                (token-list (standardize-inverted-character-class-list (cadr exp)))
                out-node)
              (fsm-state-transitions in-node)))







;;;; Parsing the pattern-cons


;;; `simple-compiled-make-uninitialized-permanent-array'

(defun-simple simple-compiled-make-uninitialized-permanent-array (length)
  (make-array length))


;;; `compile-token-definition' -

(defun-simple compile-token-definition (token-def)
  (let ((start-node (create-fsm-state))
        (end-node (create-fsm-state)))
    (compile-pattern-rec token-def start-node end-node)
    (set-fsm-state-accepts-token end-node current-lexing-rule-number)
    start-node))



;;; `compile-lexing-table-for-nfa' - takes a list of token names
;;; and regular expressions and returns an nfa to recognize the
;;; tokens.
;;;    This function is only intended to be called as an intermediate
;;; step in building the dfa.  I do not expect, and so haven't
;;; taken any steps to especially support, using an nfa for
;;; tokenization.
;;;    Note that this is the one function which really depends on
;;; the input format for the tokenizer specification.
;;;    This is the only function (aside from the testing function
;;; copy-token-array) that should ever set the token-action value of
;;; an internal-token, because it is the only place that checks that
;;; the the requested action is valid.  Note that the checks are
;;; development-only.  Nevertheless, things will certainly break in
;;; distribution if, say, the requested token-action is not a
;;; function; making the checks development only means that things
;;; will fail rather silently.  However, I think that failing very
;;; loudly in development should be enough to dissuade anyone from
;;; defining a tokenizer incorrectly, and so the checks would be
;;; unnecessary in distribution.

(defun-simple compile-lexing-table-for-nfa (pattern-and-token-defs array-maker)
  (let* ((token-defs (cdr-of-cons pattern-and-token-defs))
         (current-lexing-patterns (car-of-cons pattern-and-token-defs))
         (current-lexing-rule-number 0)
         (current-tokens (funcall-simple-compiled-function
                           array-maker (length token-defs)))
         (nfa-tokenizer (make-lexing-table))
         (root-node (create-fsm-state)))
    (setf (lexing-table-start-state nfa-tokenizer) root-node)

    (loop for (token-type token-expression token-action) in token-defs
          as i from 0 do
      (when (and (consp token-expression)
                 (eq (car-of-cons token-expression) 'anchor))
        (setf token-expression (cadr token-expression))
        (if (null (cdr token-defs))
            (setf (lexing-table-search-is-anchored-p nfa-tokenizer) t)
            #+development
            (cerror "Continue, ignoring anchor."
                    "Cannot use anchor in token definition unless it is the ~
                     only definition in the table.")))
      (setq current-lexing-rule-number i)
      (let ((new-token (make-internal-token)))
        (setf (internal-token-name new-token) token-type)
        (setf (internal-token-number new-token) i)
        (when token-action
          #+development
          (unless (and (symbolp token-action)
                       (fboundp token-action))
            (error "~s is not a valid function.  Token-actions must be ~
                    simple-functions defined using def-token-action"
                   token-action))
          #+development
          (unless (valid-token-action-p token-action)
            (cerror "Give it a shot anyway"
                    "~s is not a valid token action" token-action))
          (setf (internal-token-action new-token) (symbol-function token-action)))
        (setf (svref current-tokens i) new-token))
      (let ((start-node
              (compile-token-definition token-expression)))
        (token-push (create-epsilon-state-transition start-node)
                    (fsm-state-transitions root-node))))
    (setf (lexing-table-token-array nfa-tokenizer) current-tokens)

    nfa-tokenizer))




;;;; Subset Construction

;;; This section implements the subset construction algorithm for
;;; converting an nfa to a dfa which recognizes the same language.
;;; Essentially, the algorithm is to create a state which represents
;;; the union of several states.


;;; `insert-fixnum-into-sorted-list-using-token-conses' - a good
;;; example of the rapid prototyping ability of Lisp.

(defun-simple insert-fixnum-into-sorted-list-using-token-conses
    (new-fixnum list)
  (cond
    ((null list)
     (token-list new-fixnum))
    ((=f new-fixnum (car list))
     list)
    ((<f new-fixnum (car list))
     (token-cons new-fixnum list))
    (t
     (loop with list-to-insert
           as rest-of-list = list
                           then (cdr rest-of-list)
           when (null (cadr rest-of-list)) do
               (setq list-to-insert (token-list new-fixnum))
               (setf (cdr rest-of-list) list-to-insert)
               (loop-finish)
           when (=f (cadr rest-of-list) new-fixnum) do
               (reclaim-token-list list-to-insert)
               (loop-finish)
           when (>f (cadr rest-of-list) new-fixnum) do
               (setq list-to-insert (token-list new-fixnum))
               (setf (cdr list-to-insert) (cdr rest-of-list))
               (setf (cdr rest-of-list) list-to-insert)
               (loop-finish)
           finally
             (return list)))))



;;; `e-closure' - returns a list of states which can be
;;; reached via zero or more epsilon-transitions from the list
;;; of states given.  We take a list of states because each
;;; state in the dfa may represent several states in the original
;;; nfa;
;;;
;;; An epsilon transition is represented as a transition on
;;; input nil, so to detect one we loop over all transitions
;;; from a state, collecting the ones whose first member is
;;; nil.

(defun-simple e-closure (set-of-states)
  (loop with stack? = (copy-list-using-token-conses set-of-states)
        with ep-closure = (copy-list-using-token-conses set-of-states)
        while stack?
        for next-state = (token-pop stack?)
        for current-transitions
            = (fsm-state-transitions next-state)
        do
    (loop for transition in current-transitions
          as test = (state-transition-test transition)
          when (null test) do
              (let ((destination
                      (state-transition-next transition)))
                (unless (memq-p-macro destination ep-closure)
                  (token-push destination ep-closure)
                  (token-push destination stack?))))
          finally
            (return ep-closure)))



;;; `e-closure-of-single-state' -

(defun-simple e-closure-of-single-state (state)
  (let* ((bogus-temp-list (token-list state))
         (single-states-closure (e-closure bogus-temp-list)))
    (reclaim-token-list bogus-temp-list)
    single-states-closure))




;;; `tokens-recognized' -  What if the nfa states a dfa state
;;; is to represent accept different tokens?  The state should
;;; accept the token which was defined first.  The tokens here
;;; are represented by an index into an array, so it is very
;;; easy to determine which came first.  We assume that an
;;; nfa node has only one associated rule.

(defun tokens-recognized (closure)
  (loop for nfa-state in closure
        with dfa-should-accept? = nil
        with dfa-associated-rules = '()
        as nfa-associated-rule
           = (car (fsm-state-associated-rules nfa-state))
        ;; an nfa state is by definition associated with only one rule;
        ;; therefore, don't bother looping over list; just get the car.
        do
    (setq dfa-associated-rules
          (insert-fixnum-into-sorted-list-using-token-conses
            nfa-associated-rule dfa-associated-rules))
    (when (and (fsm-state-accepts-token? nfa-state)
               (or (null dfa-should-accept?)
                   (<f nfa-associated-rule dfa-should-accept?)))
      (setq dfa-should-accept? nfa-associated-rule))
        finally
          (return (values dfa-associated-rules dfa-should-accept?))))


;;; `create-fsm-state-for-dfa'

(defun-simple create-fsm-state-for-dfa (nfa-states)
  (let ((new-state (create-fsm-state)))
    (multiple-value-bind
        (rules accepts?)
        (tokens-recognized nfa-states)
      (reclaim-token-list (fsm-state-associated-rules new-state))
      (setf (fsm-state-associated-rules new-state) rules)
      (set-fsm-state-accepts-token new-state accepts?))
    new-state))




;;; `transition-relationship'

(defun-simple transition-relationship (transition-1 transition-2)
  (alphabet-subset
    (state-transition-test transition-1)
    (state-transition-args transition-1)
    (state-transition-test transition-2)
    (state-transition-args transition-2)))



;;; `alphabet-transition-relationship'
;;;
;;; sub1 means that the first test is a subset of the second.  If we
;;; know that we have a transition on the first test, and the second
;;; test is either equivalent or a superset of the first (i.e., sub1),
;;; then we definitely make a transition on the second also.  If the
;;; tests are disjoint then we clearly don't.

(defun-simple alphabet-transition-relationship (test1 args1 test2 args2)
  (cond
    ((and (eq test1 test2)
          (equal args1 args2))
     'equiv)
    ((null test2)
     'sub2)
    ((eq test1 alphabet-canonical-element-st-test)
     'sub2)
    ((eq test2 alphabet-canonical-element-st-test)
     'sub1)
    ((and (eq test1 alphabet-character-class-st-test)
          (eq test2 alphabet-character-class-st-test))
     (character-class-relationship
       (car args1) (car args2)))
    ((eq test1 alphabet-equality-st-test)
     (cond
       ((eq test2 alphabet-equality-st-test)
        (if (equal (car args1) (car args2))
            'equiv
            'disjoint))
       ((apply test2 (car args1) args2)
        (cond
          ((memq-p-macro test2 alphabet-preds-with-card>2)
           'sub1)
          ((eq test2 alphabet-character-class-st-test)
           'sub1)  ;; could actually be equiv!!
          ((<f alphabet-cardinality 2)
           'equiv)
          (t
           'disjoint)))
       (t
        'disjoint)))
    ((eq test2 alphabet-equality-st-test)
     (cond
       ((apply test1 (car args2) args1)
        (cond
          ((memq-p-macro test1 alphabet-preds-with-card>2)
           'sub2)
          ((eq test1 alphabet-character-class-st-test)
           'sub2)  ;; could actually be equiv!!
          ((<f alphabet-cardinality 2)
           'equiv)
          (t
           'disjoint)))
       (t
        'disjoint)))
    (t
     'overlap)))


;;; `transitions-are-compatible?'
;;;
;;; Let's say the lexing pattern is "xyz.*abc" and the source text is
;;; "xyz-blah-blah-abc".  This should be a match.  But at the point where the
;;; tokenizer has just accepted the first 'l', it reads an 'a'.  It has three
;;; options: (i) to consider the 'a' as a member of '.' and expect the next
;;; character to be '.' or 'x'; (ii) consider the 'a' to be the beginning of
;;; "abc", move to the next state, and expect a 'b' next; (iii) enter an
;;; intermediate state where it defers making a decision.  The correct option,
;;; obviously, is the third.
;;;
;;; Note that the relationship RANGE-OVERLAP is interpreted here to mean
;;; DISJOINT.  That is because it is assumed that the transitions have been
;;; resolved so that no conflicting ranges exist (by running the transitions
;;; through the function "resolve-transitions" first.)  The alphabet subset
;;; function does not compare the two ranges, except to check if the are
;;; equal.  If they aren't it returns RANGE-OVERLAP, which at this point
;;; really means that they're disjoint.

(defun-simple transitions-are-compatible? (transition-1 transition-2)
  (let ((transition-relationship
          (transition-relationship transition-1 transition-2)))
    (or (eq transition-relationship 'equiv)
        (eq transition-relationship 'sub1))))


;;; `verbose-transitions-are-compatible?' is more verbose about collisions

#+development
(defun-simple verbose-transitions-are-compatible? (transition-1 transition-2)
  (let ((transition-relationship
          (transition-relationship transition-1 transition-2)))
    (when (or (eq transition-relationship 'overlap)
              (eq transition-relationship 'range-overlap))
      (cerror "Continue"
              "~sping transitions: ~d and ~d~%   ~a~%   ~a"
              transition-relationship
              (abbrev-of-internal-number transition-1)
              (abbrev-of-internal-number transition-2)
              (transition-as-string transition-1)
              (transition-as-string transition-2)))
    (or (eq transition-relationship 'equiv)
        (eq transition-relationship 'sub1))))


;;; `possible-moves' - this is my implementation of the
;;; "move" function described in Chapter 3 of Aho, Sethi and Ullman.
;;; Given a state or list of states, and a character, it returns a
;;; list of states which can be reached, either on that character
;;; or on the empty string.
;;;
;;; The e-closure at the end of the function seems pretty necessary.
;;; While building up the list of possible destinations, we are only
;;; looking at the original nfa.  It might be possible to use the
;;; e-closure knowledge built up  already to avoid recalculating it,
;;; but I don't think it's worth it.

(defun-simple possible-moves (allowed-transitions attempted-transition)
  (and (state-transition-test attempted-transition)
       (loop with all-moves = '()
             for allowed-transition in allowed-transitions
             as add-this-destination-p
                = (transitions-are-compatible? attempted-transition
                                               allowed-transition)
             do
         (when add-this-destination-p
           (let ((dest (state-transition-next allowed-transition)))
             (unless (memq-p-macro dest all-moves)
               (token-push dest all-moves))))
             finally
               (let ((answer (e-closure all-moves)))
                 (reclaim-token-list all-moves)
                 (return answer)))))



;;; `all-transitions-from' - collects all the possible next states
;;; from a list of states into a fresh list.

(defun-simple all-transitions-from (list-of-nfa-states)
  (loop for state in list-of-nfa-states
        with all-transitions = '()
        with collated-transitions
        do
    (loop for trans in (fsm-state-transitions state) do
      (token-push trans all-transitions))
        finally
          (setq collated-transitions
                ;; (collate-range-transitions all-transitions))
                (copy-list-using-token-conses all-transitions))
          (reclaim-token-list all-transitions)
          (return collated-transitions)))



;;; `equivalent-sets-of-nfa-states-p' determinies if a dfa state
;;; equivalent to a new one already exists.  In this case, equivalent
;;; means that two dfa states represent the same set of nfa states.
;;; So, the function is called with the new set of nfa states
;;; determined by the subset construction as one argument.  The
;;; function is invoked in a loop over the global list of all dfa
;;; states.  If none are equivalent, the new state is used.  If
;;; a match is found, it is returned and that state is used instead.


(defun-simple equivalent-sets-of-nfa-states-p (list1 list2)
  (let ((same t))
    (loop for element in list2
          while same
          unless (memq-p-macro element list1)
            do
              (setq same nil))

    (loop for element in list1
          while same
          unless (memq-p-macro element list2)
            do
              (setq same nil))
    same))




;;; `duplicate-dfa-state?' - if an element of old-states represents the
;;; same NFA states as new-state, return that element; otherwise,
;;; return nil.

(defun-simple duplicate-dfa-state? (new-states-represented
                                     mapping-of-dfa-states-to-nfa-states-1
                                     mapping-of-dfa-states-to-nfa-states-2)
  (if new-states-represented
      (loop for (dfa-state . nfa-states)
                in mapping-of-dfa-states-to-nfa-states-1
            when (equivalent-sets-of-nfa-states-p
                   new-states-represented
                   nfa-states)
              return dfa-state
            finally
              (return
                (loop for (dfa-state . nfa-states)
                          in mapping-of-dfa-states-to-nfa-states-2
                      when (equivalent-sets-of-nfa-states-p
                             new-states-represented
                             nfa-states)
                        return dfa-state
                      finally
                        (return nil))))
      nil))





;;; `transition-subset-p'

(defun-simple transition-subset-p (transition-1 transition-2)
  (let ((relationship (transition-relationship
                        transition-1 transition-2)))
    (eq relationship 'sub1)))


;;; `transition-higher-priority'

(defun-simple transition-higher-priority (trans-1 trans-2)
  (let ((dest-1 (state-transition-next trans-1))
        (dest-2 (and trans-2 (state-transition-next trans-2))))
    (cond
      ((or (null dest-2)
           (>f (car (fsm-state-associated-rules dest-1))
               (car (fsm-state-associated-rules dest-2))))
       nil)
      ((<f (car (fsm-state-associated-rules dest-1))
           (car (fsm-state-associated-rules dest-2)))
       t)
      ((and (fsm-state-accepts-token? dest-1)
            (not (fsm-state-accepts-token? dest-2)))
       t)
      ((and (not (fsm-state-accepts-token? dest-1))
            (fsm-state-accepts-token? dest-2))
       nil)
      (t
       (transition-subset-p trans-1 trans-2)))))


;;; `sort-transitions-destructively'

(defun-void sort-transitions-destructively (source-state)
  (multiple-value-bind
      (sorted-list duplicates)
      (sort-list-destructively-separating-duplicates
        (fsm-state-transitions source-state)
        #'transition-higher-priority
        #'transition=)
    (setf (fsm-state-transitions source-state) sorted-list)
    (loop for transition in duplicates do
      (reclaim-transition transition)
          finally
            (reclaim-token-list duplicates))))




;;; `copy-token-array'

#+development
(defun-void copy-token-array (array-maker old-lexer new-lexer)
  (let* ((old-token-array (lexing-table-token-array old-lexer))
         (length (length old-token-array))
         (new-token-array (funcall array-maker length)))
    (setf (lexing-table-token-array new-lexer) new-token-array)
    (loop for i from 0 below length
          as old-token = (svref old-token-array i)
          as new-token = (make-internal-token)
          do
      (setf (internal-token-name new-token) (internal-token-name old-token))
      (setf (internal-token-action new-token) (internal-token-action old-token))
      (setf (internal-token-number new-token) i)
      (setf (svref new-token-array i) new-token))))



#+development
(defun token-conses-used-by-state (state)
  (if (null state)
      0
      (loop with number-of-conses = (length (fsm-state-associated-rules state))
            with current-transitions = (fsm-state-transitions state)
            for next-transition in current-transitions
            as trans-args = (state-transition-args next-transition)
            do
        (incff number-of-conses (number-of-conses-in-tree trans-args))
            finally
              (incff number-of-conses (length current-transitions))
              (return number-of-conses))))


;;; `map-destinations' - this is the function which creates transitions from the
;;; dfa states.

#+debugging
(defun-simple map-destinations (source-state old-mappings)
  (print-recent-token-cons-usage "beginning")
  (loop with conses-at-beginning = (outstanding-token-conses)
        with state-conses-at-beginning = (token-conses-used-by-state source-state)
        with current-nfa-states
          = (cdr (assq source-state old-mappings))
        with current-transitions
          = (all-transitions-from current-nfa-states)
        with ignore-me = (print-recent-token-cons-usage "list of transitions")
        with new-mappings
          = '()

        for nfa-transition in current-transitions

        as nfa-destinations? = (possible-moves current-transitions nfa-transition)
        with dfa-destination

        when nfa-destinations? do
            ignore-me
          (print-recent-token-cons-usage "nfa states for mappings")
          (let ((is-duplicate? (duplicate-dfa-state? nfa-destinations? old-mappings new-mappings)))
            (cond
              (is-duplicate?
               (setq dfa-destination is-duplicate?)
               (reclaim-token-list nfa-destinations?)
               (print-recent-token-cons-usage "reclaimed due to duplicate"))
              (t
               (setq dfa-destination (create-fsm-state-for-dfa nfa-destinations?))
               (print-recent-token-cons-usage "new dfa state (destination)")
               (token-push dfa-destination nfa-destinations?)
               (print-recent-token-cons-usage "add dfa to mappings")
               (token-push nfa-destinations? new-mappings)
               (print-recent-token-cons-usage "cons for mappings"))))
          (let ((new-trans (replicate-transition nfa-transition dfa-destination)))
            (token-push new-trans (fsm-state-transitions source-state))
            (print-recent-token-cons-usage "new trans for x"))
        finally
          (sort-transitions-destructively source-state)
          (print-recent-token-cons-usage "sort transitions for new state")
          (format t "transitions = ~s~%" current-transitions)
          (reclaim-token-list current-transitions)
          (print-recent-token-cons-usage "reclaim transition list")
          (let* ((new-state (caar new-mappings))
                 (new-state-conses (token-conses-used-by-state new-state))
                 (new-mappings-conses (number-of-conses-in-tree new-mappings))
                 (new-transition-conses (-f (token-conses-used-by-state source-state)
                                            state-conses-at-beginning))
                 (new-conses (outstanding-token-conses))
                 (used-conses (-f new-conses
                                  conses-at-beginning
                                  new-state-conses
                                  new-mappings-conses
                                  new-transition-conses)))
            (format t "used ~d conses (~d - ~d - ~d - ~d - ~d)~%"
                    used-conses new-conses
                    conses-at-beginning
                    new-state-conses
                    new-mappings-conses
                    new-transition-conses))
          (return new-mappings)))

;; Allegro choked when we were running through the development version of this
;; function (above).  I haven't looked too much into it, but it seems for now we
;; can get by using the non-development version.  I wasn't too aware of any
;; development niceties around the tokenizer, so I'm apt not to mind, for better
;; or worse, that we're losing them in #+Allegro environments at least for the
;; forseeable future.   (MHD 6/11/00)


#-debugging
(defun-simple map-destinations (source-state old-mappings)
  (loop with current-nfa-states
          = (cdr (assq source-state old-mappings))
        with current-transitions
          = (all-transitions-from current-nfa-states)
        with new-mappings
          = '()

        for nfa-transition in current-transitions

        as nfa-destinations? = (possible-moves current-transitions nfa-transition)
        with dfa-destination

        when nfa-destinations? do
          (let ((is-duplicate?
                  (duplicate-dfa-state? nfa-destinations? old-mappings new-mappings)))
            (cond
              (is-duplicate?
               (setq dfa-destination is-duplicate?)
               (reclaim-token-list nfa-destinations?))
              (t
               (setq dfa-destination (create-fsm-state-for-dfa nfa-destinations?))
               (token-push dfa-destination nfa-destinations?)
               (token-push nfa-destinations? new-mappings))))
          (let ((new-trans (replicate-transition nfa-transition dfa-destination)))
            (token-push new-trans (fsm-state-transitions source-state)))
        finally
          (sort-transitions-destructively source-state)
          (reclaim-token-list current-transitions)
          (return new-mappings)))


;;; `create-deterministic-lexer' - will construct a new dfa equivalent
;;; to the current NFA.

(defun-simple create-deterministic-lexer (nondeterministic-lexer)
  (loop with deterministic-lexer = (make-lexing-table)
        with initial-nfa-states = (e-closure-of-single-state
                                    (lexing-table-start-state
                                      nondeterministic-lexer))
        with new-start-state = (create-fsm-state-for-dfa
                                 initial-nfa-states)
        with unmarked-dfa-states = (token-list new-start-state)
        with mappings-of-dfa-states-to-nfa-states
          = (token-list (token-cons new-start-state initial-nfa-states))
        with new-mappings
        for current-state? = (token-pop unmarked-dfa-states)
        while current-state?
        do
    (setq new-mappings (map-destinations
                         current-state?
                         mappings-of-dfa-states-to-nfa-states))
    (when new-mappings
      (loop for i from 0 below (length new-mappings)
            as new-mapping = (token-pop new-mappings) do
        (token-push (car new-mapping) unmarked-dfa-states)
        (token-push new-mapping mappings-of-dfa-states-to-nfa-states)))
        finally
          (reclaim-token-tree mappings-of-dfa-states-to-nfa-states)
          (setf (lexing-table-token-array deterministic-lexer)
                (lexing-table-token-array nondeterministic-lexer))
          (setf (lexing-table-token-array nondeterministic-lexer) nil)
          (setf (lexing-table-start-state deterministic-lexer)
                new-start-state)
          (setf (lexing-table-search-is-anchored-p deterministic-lexer)
                (lexing-table-search-is-anchored-p nondeterministic-lexer))
          (return deterministic-lexer)))




;;;; Regular Expression -> dfa



;;; `compile-lexing-table' - does "the whole thing" - takes a list
;;; of patterns and tokens, defined with pattern conses, and returns
;;; a dfa to recognize the tokens.  Creates an nfa in the process,
;;; which it then reclaims.

(defun-simple compile-lexing-table (token-defs)
  (if (null token-defs)
      (empty-lexing-table)
      (let* ((the-nfa
               (compile-lexing-table-for-nfa
                 token-defs
                 #'allocate-managed-simple-vector))
             (the-dfa
               (create-deterministic-lexer the-nfa)))
        (reclaim-nfa the-nfa)
        the-dfa)))


;;; `compile-permanent-lexing-table' - takes a list
;;; of patterns and tokens, defined with pattern conses, and returns
;;; a dfa to recognize the tokens.  Creates an nfa in the process,
;;; which it then reclaims.

(defun-simple compile-permanent-lexing-table (token-defs)
  ;; This code seems not to work on SBCL; or if it does, it consumes a
  ;; gargantuan amount of memory.  Remove it, for now, with this weird hack.
  (if (null token-defs)
      (empty-lexing-table)
      (let* ((the-nfa
               (compile-lexing-table-for-nfa
                 token-defs
                 #'simple-compiled-make-uninitialized-permanent-array))
             (the-dfa
               (create-deterministic-lexer the-nfa)))
        (reclaim-nfa the-nfa)
        the-dfa)))







;;;; Pretty Printing



#+development
(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar *token-trace* nil)

(defmacro trace-tok ()
  (setq *token-trace* t))

(defmacro no-trace-tok ()
  (setq *token-trace* nil))
)


#+development
(defmacro show-lexer (dfa)
  `(in-lexing-context ,dfa (show-dfa-map)))



#+development
(defmacro show-moves (state)
  `(progn
     (output-transitions ,state)
     (values)))




(defmacro trace-tokenization (char current next)
  #-development
  (declare (ignore char current next))
  #+development
  `(and *token-trace*
        (format t "~s =~c=> ~s~%" ,current (alphabet-code-char ,char) ,next)))



#+development
(defun print-standard-class-list-as-ascii (class-list)
  (dmesg " { ")
  (loop for element in class-list
          do
      (cond
        ((=f (car element) (cdr element))
         (dmesg "~c " (alphabet-code-char (car element))))
        (t
         (dmesg "(  ~c   - " (alphabet-code-char (car element)))
         (if (=f (cdr element) 1065535)
             (dmesg "<max>")
             (dmesg "  ~c  " (alphabet-code-char (cdr element))))
         (dmesg ") "))))
  (dmesg "}"))



#+development
(defun print-inverted-class-list-as-ascii (class-list)
  (dmesg "^{ ")
  (loop with inverted-class-list
          = (standardize-character-class-list (invert-range class-list))
        for element in inverted-class-list
          do
      (cond
        ((=f (car element) (cdr element))
         (dmesg "~c " (alphabet-code-char (car element))))
        (t
         (dmesg "(  ~c   - " (alphabet-code-char (car element)))
         (if (=f (cdr element) 1065535)
             (dmesg "<max>")
             (dmesg "  ~c  " (alphabet-code-char (cdr element))))
         (dmesg ") "))))
  (dmesg "}"))


#+development
(defun print-class-list-as-ascii (class-list)
  (if (=f (caar class-list) alphabet-min-code)
      (print-inverted-class-list-as-ascii
        class-list)
      (print-standard-class-list-as-ascii
        class-list)))


#+development
(defun transition-as-string (transition)
  (twith-output-to-text-string
    (let* ((test (state-transition-test transition))
           (args (state-transition-args transition))
           (dest (state-transition-next transition))
           (dest-state-number (abbrev-of-internal-number dest)))
      (cond
        ((eq test alphabet-equality-st-test)
         (let ((trans-char (alphabet-code-char (car args))))
           (if trans-char
               (tformat "'~c'" trans-char)
               (twrite-string " ? "))))
        ((eq test alphabet-character-class-st-test)
         (let ((inverted-args
                 (standardize-character-class-list (invert-range (car args)))))
           (twrite-string "^{ ")
           (loop for element in inverted-args do
             (cond
               ((=f (car element) (cdr element))
                (tformat "~c " (alphabet-code-char (car element))))
               (t
                (tformat "(~c - ~c) "
                         (alphabet-code-char (car element))
                         (alphabet-code-char (cdr element))))))
           (tformat "}")))
        (t
         (let ((*print-case* :downcase))
           (tformat "(~s" test))
         (loop for arg in args do
           (if (alphabet-canonical-element-p arg)
               (tformat " ~c" (alphabet-code-char arg))
               (tformat " ~s" arg)))
         (twrite-string ")")))
      (tformat "---> S~a" dest-state-number)
      (when (fsm-state-accepts-token? dest)
        (tformat "  <===~s" (token-index->symbol
                              (get-fsm-state-accepts-token-number dest)))))))


#+development
(defun output-list-of-transitions (list-of-transitions &optional (state-number -1))
  (loop for transition in list-of-transitions
        with found-destinations = '()
        as test = (state-transition-test transition)
        as args = (state-transition-args transition)
        as dest = (state-transition-next transition)
        as dest-state-number = (abbrev-of-internal-number dest)
        do
    (dmesg "(~2d) S~2d ---" (abbrev-of-internal-number transition)
           state-number)
    (cond
      ((eq test alphabet-equality-st-test)
       (let ((trans-char (alphabet-code-char (car args))))
         (if trans-char
             (dmesg "'~c'" trans-char)
             (dmesg " ? "))))
      ((eq test alphabet-character-class-st-test)
       (print-class-list-as-ascii (car args)))
      (t
       (let ((*print-case* :downcase))
         (dmesg "(~s" test))
       (loop for arg in args do
         (if (alphabet-canonical-element-p arg)
             (dmesg " ~c" (alphabet-code-char arg))
             (dmesg " ~s" arg)))
       (dmesg ")")))
    (dmesg "---> S~2d" dest-state-number)
    (when (fsm-state-accepts-token? dest)
      (dmesg "  <===~s"
             (token-index->symbol
               (get-fsm-state-accepts-token-number dest))))
    (dmesg " [~s]~%" (fsm-state-associated-rules dest))
    (token-push dest found-destinations)
        finally
          (unless (null list-of-transitions) (terpri))
          (return found-destinations)))

#+development
(defun output-transitions (current-state)
  ;; (in-lexing-context
  ;; (fsm-state-tokenizer current-state)
  (output-list-of-transitions (fsm-state-transitions current-state)
                              (abbrev-of-internal-number current-state)))
  ;;)


#+development
(defun output-list-of-nfa-states-and-transitions
    (list-of-nfa-states transitions)
  (dmesg "(")
  (loop for state in list-of-nfa-states do
    (dmesg "~d " (abbrev-of-internal-number state)))
  (dmesg ")~%")
  (output-list-of-transitions transitions))



#+development
(defun output-range-transitions (current-state)
  (loop with list-of-transitions = (fsm-state-transitions current-state)
        for transition in list-of-transitions
        with current-state-number =  (abbrev-of-internal-number current-state)
        with found-destinations = '()
        as test = (state-transition-test transition)
        as args = (state-transition-args transition)
        as dest = (state-transition-next transition)
        as dest-state-number = (abbrev-of-internal-number dest)
        when (eq test alphabet-character-class-st-test) do
    (dmesg "(~2d) S~2d ---" (abbrev-of-internal-number transition)
           current-state-number)
    (print-class-list-as-ascii (car args))
    (dmesg "---> S~2d" dest-state-number)
    (when (fsm-state-accepts-token? dest)
      (dmesg "  <===~s"
             (token-index->symbol
               (get-fsm-state-accepts-token-number dest))))
    (dmesg " [~s]~%" (fsm-state-associated-rules dest))
    (token-push dest found-destinations)
        finally
          (unless (null list-of-transitions) (terpri))
          (return found-destinations)))


#+development
(defun show-mappings (mappings)
  (loop for mapping in mappings do
    (dmesg "~2d:   (" (abbrev-of-internal-number (car mapping)))
    (loop for nfa in (cdr mapping) do
      (dmesg "~d " (abbrev-of-internal-number nfa)))
    (dmesg ")~%")))





;;; `show-dfa-map' - outputs a list of all state transitions in
;;; the current tokenizer.  Can use
;;;   (in-lexing-context x (show-dfa-map))
;;; to see the state transitions in tokenizer x.

#+development
(defun show-dfa-map ()
  (loop with current-state? = current-start-state
        with to-be-done = '()
        with done-already = (token-list current-state?)
        with finished-p = nil
        until finished-p
        do
    (loop with destinations = (output-transitions current-state?)
          for dest in destinations
          unless (or (memq-p-macro dest to-be-done)
                     (memq-p-macro dest done-already))
            do
              (token-push dest to-be-done)
          finally
            (reclaim-token-list destinations))
    (cond
      ((null to-be-done)
       (setq finished-p t))
      (t
       (setq current-state? (token-pop to-be-done))
       (token-push current-state? done-already)))
        finally
          (reclaim-token-list done-already)
          (terpri))
  current-tokenizer)



;;; `show-parse-object'

#+development
(defun show-parse-object (tok-struct)
  (dmesg "struct: (token-type = ~s, start-index = ~d, end-index = ~d)~%"
         (parse-object-type tok-struct)
         (parse-object-start-index tok-struct)
         (parse-object-end-index tok-struct))
  tok-struct)



;;; `show-tokens'

#+development
(defun show-tokens (token-stack)
  (loop
    initially
      (dmesg "(")
    with reversed-list = (token-reverse token-stack)
    for tok-struct in reversed-list
    as value = (parse-object-value tok-struct)
    do
    (if (alphabet-character-code-p value)
        (dmesg "~s[~c] " (parse-object-type tok-struct)
               (alphabet-code-char value))
        (dmesg "~s[~a] " (parse-object-type tok-struct) value))
    finally
      (reclaim-token-list reversed-list)
      (dmesg ")~%")))


#+development
(defun show-token-cons-rec (thing count)
  (dmesg " ")
  (cond
    ((null thing)
     nil)
    ((alphabet-canonical-element-p thing)
     (dmesg "~c" (alphabet-code-char thing)))
    ((atom thing)
     (dmesg "~s" thing))
    ((listp thing)
     (dmesg "(")
     (loop for subthing in thing do
       (incff count)
       (show-token-cons-rec subthing count))
     (dmesg ")"))))


#+development
(defun make-string-of-tokens (token-stack)
  (twith-output-to-text-string
    (loop
      initially
        (twrite-string "(")
      with reversed-list = (token-reverse token-stack)
      for tok-struct in reversed-list do
      (tformat "~s[~c] " (parse-object-type tok-struct)
               (alphabet-code-char (parse-object-value tok-struct)))
      finally
        (reclaim-token-list reversed-list)
        (twrite-string ")~%"))))


#+development
(defun fsm-state-token-name? (tokenizer fsm-state)
  (in-lexing-context tokenizer
                     (get-fsm-state-accepts-token-name? fsm-state)))











;;;; Tokenizing

;;; The prior functions build up a dfa, which is the bulk of the work.
;;; Below are functions which use those dfas to perform lexical analysis.


;;; `no-tokenizer-match' - the built-in G2 function "get-next-token"
;;; returns a structure with the slots TOKEN-TYPE, START-INDEX, and END-INDEX.
;;; When no token is found, a struct must still be returned, with the following
;;; sentinel values.

(defconstant no-tokenizer-match-token-type 'false)




;;; `no-tokenizer-match-found'

(defmacro no-tokenizer-match-found ()
  `(let ((nil-token (create-parse-object nil nil)))
     (setf (parse-object-type nil-token)
           no-tokenizer-match-token-type)
     (setf (parse-object-start-index nil-token)
           no-tokenizer-match-start-index)
     (setf (parse-object-end-index nil-token)
           no-tokenizer-match-end-index)
     nil-token))



;;; `extra-argument-count-based-simple-compiled-function-dispatch' - takes
;;; a first arg separate from the rest of the argument list.

(defmacro extra-argument-count-based-simple-compiled-function-dispatch
    (function first-arg rest-of-args extra-arg-count max-args)
  `(let ((simple-compiled-function ,function)
         (argument-list ,rest-of-args))
     (fixnum-case ,extra-arg-count
       ,@(loop for i from 0 below (eval max-args)
               collect
               `(,i
                   (funcall-simple-compiled-function
                     simple-compiled-function
                     ,first-arg
                     ,@(loop for arg-number from 0 below i
                             collect
                             `(prog1 (car-of-cons argument-list)
                                (setf argument-list
                                      (cdr-of-cons argument-list))))))))))



;;; `apply-state-transition-test-to-args'

(defun-simple apply-state-transition-test-to-args (transition element)
  (when (if (state-transition-is-standard-test-p transition)
            (make-fixnum-case-form-for-apply-state-transition
              transition element)
            (extra-argument-count-based-simple-compiled-function-dispatch
              (state-transition-test transition)
              element
              (state-transition-args transition)
              (state-transition-arg-count transition)
              maximum-state-transition-args))
    (state-transition-next transition)))



;;; `find-first-lexing-transition' - the transitions from each state
;;; are ordered, so (assuming we search in the obvious manner), the
;;; first one we find is the one to take.

(defun-substitution-macro find-first-lexing-transition (element parse-state)
  (and element
       parse-state
       (loop for transition in (fsm-state-transitions parse-state)
             as answer = (apply-state-transition-test-to-args
                           transition element)
             when answer
               return answer)))



;;; `get-longest-token-between-positions' - returns a parse object structure
;;; with the longest match found at the position given.  If there is
;;; no match at the position given, returns nil.
;;;
;;; NOTE: This does not match zero length tokens!!  If you give the pattern
;;; "a*" and the string "bcd", it returns no match.  It might be more correct
;;; to return a match with positions (0, 0), since it did match zero or more
;;; occurrences of the character 'a'.  However, that could be confusing and
;;; easily lead to infinite loops by programmers who are not experienced with
;;; writing regular expressions.  Still, it is probably more correct to return
;;; the zero length token.

(defun-simple get-longest-token-between-positions (string start-index end-index)
  (loop with index-when-last-token-accepted = nil
        with current-token = nil
        with start-state = current-start-state
        with index = start-index
        as current-character = (and (<f index end-index)
                                    (alphabet-string-element
                                      string index))
        as current-parse-state = start-state
                               then next-parse-state
        as next-parse-state = (find-first-lexing-transition
                                current-character
                                current-parse-state)
        as token-accepted-by-this-state = (and next-parse-state
                                               (get-fsm-state-accepts-token-number
                                                 next-parse-state))
        with action-on-last-token = nil
        with last-token-accepted
        while current-parse-state
        when token-accepted-by-this-state do
            (setq last-token-accepted token-accepted-by-this-state)
            (setq index-when-last-token-accepted index)
        do
    (trace-tokenization current-character current-parse-state next-parse-state)
    (incff index)
        finally
          (if (null last-token-accepted)
              (return nil)
              (setq action-on-last-token
                    (token-index->symbol last-token-accepted)))
          (return
            (cond
              ((eq action-on-last-token 'do-nothing)
               (get-longest-token-between-positions
                 string (1+f index-when-last-token-accepted) end-index))
              (t
               (setq current-token (create-parse-object nil nil))
               (setf (parse-object-type current-token) action-on-last-token)
               (setf (parse-object-start-index current-token) start-index)
               (setf (parse-object-end-index current-token)
                     (1+f index-when-last-token-accepted))
               current-token)))))



;;; `get-next-token-from-text-string' - finds the next token which
;;; matches, starting at the given index.  The match does not
;;; need to begin at the index given.  If there is no match at
;;; the index given, it looks for the earliest match there is.
;;; Essentially, this is the grep function.  If there is no
;;; match whatsoever, it still returns a structure, with (-1, 0)
;;; used to indicate failure.  Since the indices returned are
;;; zero-based, with an inclusive start-index and an exclusive
;;; end-index, the start-index must be incremented by one before
;;; being given to the user.  That is the job of the calling
;;; function.
;;;
;;; This is the primary API to tokenization.
;;;
;;; The algorithm used here is extremely simple.  We simply loop
;;; over every position (i.e., start-index), starting at the given
;;; start-index, and ending at the given end-index or the end of the
;;; text, whichever comes first; and for each position, until a match
;;; is found or the end of text is reached, attempt to match the
;;; pattern at that particular position.
;;;
;;; Note: there is one case when we don't check "every position".
;;; That is in the case where something which takes up more than one
;;; position in the string is logically one character.  Currently,
;;; the only time I consider that to be the case is when we are
;;; preprocessing regular expression strings for the tokenizer object,
;;; and the escape character ('\') is used.  There may be other times
;;; when it will be appropriate to treat multi-character sequences as
;;; one character; aside from other uses of escape characters, there
;;; is also the question of non-spacing marks.  For now, however, those
;;; cases are not implemented, and the one special case is extremely
;;; hard coded.

(defun-simple get-next-token-from-text-string-1 (text-string start-index end-index?)
  (let* ((length
           (alphabet-text-string-length text-string))
         (end-index (if (and end-index?
                             (>f length end-index?))
                        end-index?
                        length))
         (index start-index)
         (token nil))
    (cond
      ((>f index end-index)
       (no-tokenizer-match-found))
      (current-anchor-p
       (setq token (get-longest-token-between-positions
                     text-string index end-index))
       (or token (no-tokenizer-match-found)))
      (t
       (loop while (and (null token) (<f index end-index))
             do
         (setq token
               (get-longest-token-between-positions
                 text-string index end-index))
         (if (and (char=w (charw text-string index)
                          alphabet-escape-character)
                  (eq current-tokenizer preprocessing-tokenizer))
             (incff index 2) ;; see note above
             (incff index)))
       (or token (no-tokenizer-match-found))))))



(defmacro get-next-token-from-text-string
    (text-string start-index &optional end-index)
  `(and (alphabet-canonical-string-p ,text-string)
        (get-next-token-from-text-string-1
          ,text-string ,start-index ,end-index)))


;;; `lexeme'

(defun-simple lexeme (string token)
  (let ((end-index (parse-object-end-index token)))
    (if (=f end-index no-tokenizer-match-end-index)
        nil
        (alphabet-substring
          string
          (parse-object-start-index token)
          end-index))))


;;; `build-stack-of-tokens' - takes a text-string and returns a stack of parse
;;; objects tokenized as a regular expression.

#+development
(defun-simple build-stack-of-tokens (string)
  (loop with stack = '()
        with current-index? = 0
        until (null current-index?)
        as next-token = (get-next-token-from-text-string string current-index?)
        as next-lexeme = (lexeme string next-token)
        do
    (cond
      (next-lexeme
       (setf (parse-object-value next-token) next-lexeme)
       (setq current-index? (parse-object-end-index next-token))
       (token-push next-token stack))
      (t
       (setq current-index? nil)))
        finally
          (return stack)))




;;;; Tokenizing Regular Expressions


(def-lexing-table g2-standard-tokenizer g2-standard-tokens)
(def-lexing-table g2-simple-tokenizer g2-simple-tokens)
(def-lexing-table g2-load-kb-tokenizer load-kb-tokens)
(def-lexing-table g2-tokenizer-tokenizer tokenizer-tokens)
(def-lexing-table g2-symbol-tokenizer g2-symbol-tokens)

;;; jv, temporary, 1/31/05
(def-lexing-table g2-comment-tokenizer g2-comment-recognizing-tokens)

(def-lexing-table regular-expression-tokenizer regular-expression-tokens)

(def-default-tokenizer regular-expression-tokenizer)

(defun-simple regular-expression-lexeme (string token)
  (let ((end-index (parse-object-end-index token)))
    (if (=f end-index no-tokenizer-match-end-index)
        nil
        (alphabet-string-element string (1-f end-index)))))





;;; `handling-other-args' - the regular expression text searching functions
;;; are supposed to take an optional argument, a structure containing
;;; flags which modify the search.  An obvious example is case-sensitivity.
;;; As of now, there are still no flags implemented.

(defmacro handling-other-args (other-args form)
  `(progn
     ,other-args
     ,form))






;;;; Debugging


;;; `quote-fix' - just for emacs.  When it prints an unmatched double
;;; quote character (as it often does in things like "show-lexer"),
;;; emacs gets confused and thinks that the command I'm typing is
;;; part of a string (which means, with my emacs preferences, it
;;; prints in green italics.)  Printing another double quote fixes it.

#+development
(defun quote-fix ()
  (format t "\""))



;;; `compile-nfa'

#+development
(defun compile-nfa (token-defs)
  (compile-lexing-table-for-nfa token-defs
				#'allocate-managed-simple-vector))

;;; `find-all-lexing-transitions'

#+development
(defun find-all-lexing-transitions (element parse-state)
  (if (and (alphabet-canonical-element-p element)
           parse-state)
      (loop with feasible-transitions = '()
            for transition in (fsm-state-transitions parse-state)
            as new-args = (and transition
                               (token-cons element
                                           (copy-list-using-token-conses
                                             (state-transition-args transition))))
            when (and transition (apply (state-transition-test transition) new-args)) do
                (token-push transition feasible-transitions)
            do
        (reclaim-token-list new-args)
            finally
              (return feasible-transitions))))


;;; `next-regexp-token'

#+development
(defmacro next-regexp-token (string index)
  (let ((variablep (not (constantp index))))
    `(prog1
       (let* ((next-token
                (get-next-token-from-text-string ,string ,index))
              (end-position
                (parse-object-end-index next-token)))
         (if (=f end-position no-tokenizer-match-end-index)
             (dmesg "No token found~%")
             (dmesg "~s[~c]: (~d, ~d)~%"
                    (parse-object-type next-token)
                    (alphabet-code-char
                      (alphabet-string-element
                        ,string (1-f end-position)))
                    (parse-object-start-index next-token)
                    end-position))
         next-token)
       (when ,variablep
         (incff ,index)))))



;;; `next-token' - is a macro because it changes the value of
;;; it's parameter "start" (so that it can really produce the
;;; *next* token each time it's called.)

#+development
(defmacro next-token (tokenizer string start &optional (verbose-p t))
  (let ((variablep (not (constantp start))))
    `(let* ((actual-string
              (if (text-string-p ,string)
                  ,string
                  (stringw ,string)))
            (the-token
              (in-lexing-context
                ,tokenizer
                (get-next-token-from-text-string
                  actual-string ,start)))
            (match-start (parse-object-start-index the-token))
            (match-end (parse-object-end-index the-token)))
       (unless (or (null ,verbose-p)
                   (=f no-tokenizer-match-end-index match-end))
         (dmesg "~s: ~s (~d, ~d)~%"
                (parse-object-type the-token)
                (alphabet-substring actual-string match-start match-end)
                match-start match-end))
       (when ,variablep
         (setf ,start match-end))
       the-token)))


;;; `read-token-from-string'

#+development
(defun read-token-from-string (tokenizer string start)
  (let* ((local-index start)
         (length (text-string-length string))
         (next-token
           (loop as x = (next-token
                          tokenizer string local-index nil)
                 while (eq 'whitespace
                           (parse-object-type x))
                 finally
                   (return x)))
         (type (parse-object-type next-token))
         (start (parse-object-start-index next-token))
         (end (parse-object-end-index next-token))
         (partial-p (/=f local-index length))
         token)
    (setq token
          (case type
            (symbol
             (alphabet-normalized-symbol-from-text-string
               string start end))
            (whole-string
             (copy-portion-of-wide-string
               string (1+f start) (1-f end)))
            (t
             next-token)))
    (cond
      (partial-p
       (let* ((new-token
                (next-token tokenizer string local-index nil))
              (new-type (parse-object-type new-token)))
         (multiple-value-prog1
             (if (eq new-type 'whitespace)
                 (values token type end)
                 (values token (token-list type) end))
           (reclaim-parse-object new-token))))
      (t
       (if (eq type 'false)
           nil
           (values token type end))))))



;;; `read-token-from-text-string'

#+development
(defun read-token-from-text-string (string start)
  (read-token-from-string g2-standard-tokenizer string start))



;;; `tokenize'

#+development
(defun tokenize (tokenizer string)
  (loop with index = 0
        with next-token = nil
        with done = nil
        until done
        do
    (setq next-token (next-token tokenizer string index))
    (setq index (parse-object-end-index next-token))
    (when (=f index 0) (setq done t))))




;;;; Tokenizing in the Editor


(declare-forward-references
  (get-next-text-line function)
  (partial-tokens-for-state function)
  #+development
  (determine-appropriate-tokenizer function)
  (partial-string-acceptable-p-function function)
  (instance-of-token-acceptable-in-current-edit-state-p function))

#+development
(declare-forward-references
  (current-edit-state variable))



;;; `text-tokenization-state'

(def-structure text-tokenization-state
  text-line
  (wide-character? nil)
  (character-index 0)
  (line-index 1)
  line-length
  lost-space-at-end-of-line                ;; 0 if hyphen added, 1 implied
  (end-character-index? nil)
  (end-line-index? nil)
  (return-partial-tokens-p nil)
  previous-text-tail
  (active-text-tail nil)
  (next-text-tail? nil)

  ;; this slot should be removed -- it's obsolete! (MHD/JV 8/3/06)
  line-length-of-penultimate-line

  line-length-of-previous-line
  (ellipsis-tokenization-state 0)
  (previous-character-was-quote-p nil)
  )


;;; `g2-token'

(def-structure (g2-token
                 #+development
                 (:print-function print-g2-token))
  g2-token-type-or-partial-types
  g2-token-value
  g2-token-line-index
  g2-token-character-index
  (g2-token-text-tail nil)
  (g2-token-self-terminating-p nil))

#+development
(defun print-g2-token (g2-token stream depth)
  (declare (ignore depth))
  (printing-random-object (g2-token stream)
    (format stream "G2-TOKEN ~A ~S"
            (g2-token-value g2-token)
            (g2-token-type-or-partial-types g2-token))))



(defvar current-text-tokenization-state (make-text-tokenization-state))

(defvar tokenize-with-editing-context-p nil)


(defparameter tokenizer-illegal-character-error-message
  #w"an illegal character was encountered")



;;; `no-g2-token-match-found'

(defmacro no-g2-token-match-found ()
  `(let ((nil-token (make-g2-token)))
     (setf (g2-token-type-or-partial-types nil-token)
           no-tokenizer-match-token-type
           (g2-token-value nil-token)
           nil
           (g2-token-line-index nil-token)
           no-tokenizer-match-start-index
           (g2-token-character-index nil-token)
           no-tokenizer-match-end-index)
     nil-token))


;;; `create-g2-token'

(defmacro create-g2-token
    (value type-or-partial-types line-index character-index
           text-tail self-terminating-p)
  `(let ((return-token (make-g2-token)))
     (setf (g2-token-value return-token) ,value)
     (setf (g2-token-type-or-partial-types return-token)
           ,type-or-partial-types)
     (setf (g2-token-line-index return-token) ,line-index)
     (setf (g2-token-character-index return-token)
           ,character-index)
     (setf (g2-token-text-tail return-token) ,text-tail)
     (setf (g2-token-self-terminating-p return-token)
           ,self-terminating-p)
     return-token))



;;; `verbose-tokenizer-values'

#+development
(defmacro verbose-tokenizer-values (a b c d e f)
  `(progn
     (dmesg "    (~3d ~3d ~20s ~3s ~s)~%"
            ,c ,d ,a ,f ,b)
     (values ,a ,b ,c ,d ,e ,f)))




;;; `convert-text-string-to-text-without-duplicating-it'

(defmacro convert-text-string-to-text-without-duplicating-it (text-string)
  #+development
  `(cond
     ((wide-string-p ,text-string)
      (token-cons ,text-string nil))
     ((gensym-string-p ,text-string)
      (cerror "Coerce to wide string"
              "~s should be a wide string" ,text-string)
      (token-cons (stringw ,text-string) nil))
     (t
      (error "Argument ~s must be a string." ,text-string)))
  #-development
  `(token-cons ,text-string nil))



;;; `reclaim-text-without-reclaiming-underlying-text-string'

(defmacro reclaim-text-without-reclaiming-underlying-text-string (text)
  `(reclaim-token-cons ,text))






;;; `Twith-single-value-output-to-then-use-of-wide-string' is like
;;; twith-output-to-then-use-of-wide-string except that it can
;;; only return one value (thereby making it much more efficient.)

(defmacro twith-single-value-output-to-then-use-of-wide-string (&body body)
  (let ((arg1 (gensym)))
    `(with-current-wide-string
         (let ((,arg1 (progn . ,body)))
           (reclaim-wide-string current-wide-string)
           ,arg1))))




;;; `tokenizer-go-to-next-text-line' - gets the next text line and updates
;;; the tokenizing structures.

(defmacro tokenizer-go-to-next-text-line ()
  `(multiple-value-bind
       (text-line line-length lost-space next-text-tail?)
       (get-next-text-line (active-text-tail current-text-tokenization-state))
     (setf (line-length-of-previous-line current-text-tokenization-state)
           (character-index current-text-tokenization-state))
     (setf (text-line current-text-tokenization-state) text-line)
     (setf (line-length current-text-tokenization-state)
           (if (and (end-character-index? current-text-tokenization-state)
                    (=f (line-index current-text-tokenization-state)
                        (end-line-index? current-text-tokenization-state))
                    (<f (end-character-index? current-text-tokenization-state)
                        line-length))
               (end-character-index? current-text-tokenization-state)
               line-length))
     (setf (lost-space-at-end-of-line current-text-tokenization-state) lost-space)
     (setf (next-text-tail? current-text-tokenization-state)
           next-text-tail?)))




;;; `hit-cursor-p'

(defmacro hit-cursor-p ()
  `(and (end-character-index? current-text-tokenization-state)
        (or (>f (line-index current-text-tokenization-state)
                (end-line-index? current-text-tokenization-state))
            (and (=f (line-index current-text-tokenization-state)
                     (end-line-index? current-text-tokenization-state))
                 (>=f (character-index current-text-tokenization-state)
                      (end-character-index? current-text-tokenization-state))))))


;;; `middle-of-line-p'

(defmacro middle-of-line-p ()
  `(<f (character-index current-text-tokenization-state)
       (line-length current-text-tokenization-state)))


;;; `end-of-line-p'

(defmacro end-of-line-p ()
  `(and (>=f (character-index current-text-tokenization-state)
             (line-length current-text-tokenization-state))
        (>=f (-f (character-index current-text-tokenization-state)
                 (line-length current-text-tokenization-state))
             (if (fixnump (lost-space-at-end-of-line
                            current-text-tokenization-state))
                 (lost-space-at-end-of-line current-text-tokenization-state)
                 (text-string-length
                   (lost-space-at-end-of-line
                     current-text-tokenization-state))))))




;;; `state-accepts-token-p' - returns t if the given tokenizer state
;;; accepts a token of token-type.  A state in the tokenizer (of type
;;; fsm-state) has a field "accepts-token?", which holds a single fixnum or
;;; nil.  The fixnums correspond to entries in an array of the tokenizer,
;;; which contains information about the tokens.

(defun-simple state-accepts-token-p (tokenizer-state token-type)
  (let ((token-index (fsm-state-accepts-token? tokenizer-state)))
    (and token-index
         (eq (token-index->symbol token-index) token-type))))



;;; `state-potentially-accepts-token-p' - returns t if the given tokenizer
;;; state is on the path for accepting a token of token-type.

(defun-simple state-potentially-accepts-token-p (tokenizer-state token-type)
  (loop for token-number in (fsm-state-associated-rules tokenizer-state)
        as token-symbol = (token-index->symbol token-number)
        thereis (eq token-symbol token-type)))



;;; `get-next-wide-character-from-text' - is a wrapper around the real function
;;; to get the next character from a text cons.  The parse for ellipses must
;;; be done in parallel with the regular parse, for reasons too arcane to go into
;;; here.  The ellipsis-tokenization-state is a slot in the tokenizer object.  We
;;; announce an ellipsis when we read three unquoted '.' characters in a row,
;;; while not inside a comment.  No other part of the tokenizer cares about
;;; quoting, so the previous-character-was-quote-p slot is only used here.
;;;
;;; This function has some special knowledge about G2's language.  It knows
;;; that the token called 'COMMENT is actually a partial comment, so whenever
;;; we are inside a comment, the state returns the token 'COMMENT.  An fsm-
;;; state also has a field called "associated-rules", which tell what
;;; possible tokens can be returned; for example, after seeing a '-', the
;;; tokenizer could return a symbol, an integer, or a float; however, the
;;; state entered after a '-' accepts only a symbol.  We assume that is
;;; not the case in G2.  Also, there are states where two tokens could be
;;; accepted, and the "accepts-token?" field holds the handle to the one
;;; with the higher priority (which is the one which came first in the
;;; tokenizer specification).  For example, after seeing "-1", it's still
;;; possible to return a symbol, integer or float; however, integers take
;;; precedence over symbols, so the state would only return 'INTEGER.
;;; Again, we assume this is not the case with comments.  These assumptions
;;; allow us to use the function

(defun-void get-next-wide-character-from-text (tokenizer-state)
  (get-next-wide-character-from-text-1)
  (if (and (eqlw #.%\. (wide-character? current-text-tokenization-state))
           (not (previous-character-was-quote-p current-text-tokenization-state))
           (not (or (state-accepts-token-p tokenizer-state 'comment)
                    (state-accepts-token-p tokenizer-state 'single-line-comment))))
      (incff (ellipsis-tokenization-state current-text-tokenization-state))
      (setf (ellipsis-tokenization-state current-text-tokenization-state) 0))
  (if (eqlw #.%\@ (wide-character? current-text-tokenization-state))
      (setf (previous-character-was-quote-p current-text-tokenization-state) t)
      (setf (previous-character-was-quote-p current-text-tokenization-state) nil)))



;;; `get-next-wide-character-from-text-1'

(defun-void get-next-wide-character-from-text-1 ()
  (loop do
    (cond
      ((hit-cursor-p)
       (incff (character-index current-text-tokenization-state))
       (setf (wide-character? current-text-tokenization-state) nil)
       (loop-finish))
      ((end-of-line-p)
       (incff (line-index current-text-tokenization-state))
       (setf (line-length-of-previous-line current-text-tokenization-state)
             (character-index current-text-tokenization-state))
       (setf (character-index current-text-tokenization-state) 0)
       (when (null (next-text-tail? current-text-tokenization-state))
         (setf (wide-character? current-text-tokenization-state) nil)
         (decff (line-index current-text-tokenization-state))
         (setf (character-index current-text-tokenization-state)
               (line-length-of-previous-line current-text-tokenization-state))
         (setf (line-length-of-previous-line current-text-tokenization-state) nil)
         (loop-finish))
       (shiftf (previous-text-tail current-text-tokenization-state)
               (active-text-tail current-text-tokenization-state)
               (next-text-tail? current-text-tokenization-state))
       (tokenizer-go-to-next-text-line))
      ((middle-of-line-p)
       ;; Normal case.  Current character somewhere in the middle
       ;; of the line.
       (setf (wide-character? current-text-tokenization-state)
             (charw (text-line current-text-tokenization-state)
                    (character-index current-text-tokenization-state)))
       (incff (character-index current-text-tokenization-state))
       (loop-finish))
      (t
       ;; Weird case with those lost-space thingies.
       (setf (wide-character? current-text-tokenization-state)
             (if (fixnump (lost-space-at-end-of-line current-text-tokenization-state))
                 #.%space
                 (charw (lost-space-at-end-of-line current-text-tokenization-state)
                        (-f (character-index current-text-tokenization-state)
                            (line-length current-text-tokenization-state)))))
       (incff (character-index current-text-tokenization-state))
       (loop-finish)))))



;;; `determine-lexeme-for-completed-token' - This function will abort
;;; G2 if last-accepting-state is not a state which accepts a token.
;;; (In other words, if last-accepting-state is nil, or if
;;;    (get-fsm-state-accepts-token-number last-accepting-state)
;;; is nil.)  However, this should never be the case.  This function
;;; is only called if we have completed a token, and completing a
;;; token means being in a state which accepts one.

(defun-simple determine-lexeme-for-completed-token
    (last-valid-state)
  (let ((internal-token
          (svref (lexing-table-token-array current-tokenizer)
                 (get-fsm-state-accepts-token-number
                   last-valid-state))))
    (funcall-simple-compiled-function
      (internal-token-action internal-token)
      current-wide-string
      0 fill-pointer-for-current-wide-string)))


;;; `determine-lexeme-for-partial-token'  - unfortunately, this has some
;;; more hard-coded information in it.  It'll have to do for now.  And yes,
;;; I'm going to date this just so I look silly in a year.  - jv 11/15/96

(defun-simple determine-lexeme-for-partial-token (partial-types)
  (cond
    ((or (memq-p-macro 'left-string partial-types)
         (memq-p-macro 'middle-string partial-types))
     (alphabet-normalized-substring-for-string
       current-wide-string 1 fill-pointer-for-current-wide-string))
    ((memq-p-macro 'java-symbol partial-types)
     (alphabet-substring-for-symbol-function
       current-wide-string 0 fill-pointer-for-current-wide-string nil))
    (t
     (alphabet-substring-for-symbol-function
       current-wide-string 0 fill-pointer-for-current-wide-string t))))



;;; `self-terminating-token-type-p' - the tokenizer should be able to
;;; determine self-termination, and it should be based on the state
;;; of the DFA, not the type of token being returned.  Currently it's just
;;; hard-coded.  See Note A below encapsulate-information-into-token.

(defmacro self-terminating-token-type-p (token-type?)
  `(memq-p-macro ,token-type?
                 '(quoted-character whole-string left-string
                   middle-string right-string
                   self-terminating-punctuation-mark
                   java-character-literal
                   )))



;;; `bogus-punctuation-p' - if the user has typed:
;;;    text-of-x = "[x
;;; and then types a ']' character, the tokenizer will initially
;;; recognize it as a punctuation mark, but it really should be
;;; a right-string.  There's no way to make this distinction
;;; using regular expressions, so a hack is necessary.  The case
;;; given above is currently the only time this function returns
;;; t, but I tried to make it a bit more general anyway.

(defun-simple bogus-punctuation-p (token-name)
  (loop for (ambiguous-character
              potential-type
              (immediate-type nil))
            in generally-ambiguous-characters-in-g2-tokenization
        thereis
        (and (eq token-name immediate-type )
             (char=w (charw current-wide-string 0)
                     ambiguous-character)
             (partial-string-acceptable-p-function
               potential-type
               (line-index current-text-tokenization-state)
               (character-index current-text-tokenization-state)))))


;;; `completed-token-p' - maybe should be called DEFINITELY-completed-
;;; token-p.  Returns t if the token

;; If we're in the middle of a token, then we have not
;; completed it.  The following "and" checks that: the
;; cursor is past the point where the last token was
;; accepted, AND that we haven't hit the cursor.  If we've
;; hit the cursor, then that's not good enough to say that
;; we've passed the end of the token.

(defun-simple completed-token-p
    (last-valid-index return-only-completed-tokens-p
                      degenerate-case-p self-terminating-p)
  (if last-valid-index
      (or return-only-completed-tokens-p
          (and (not degenerate-case-p)
               (or self-terminating-p
                   (and (/=f last-valid-index
                             (character-index current-text-tokenization-state))
                        (or (/=f (line-index current-text-tokenization-state)
                                 (end-line-index? current-text-tokenization-state))
                            (<f (character-index current-text-tokenization-state)
                                (end-character-index?
                                  current-text-tokenization-state)))))))
      #+development
      (cerror "Go on"
              "Please tell jv that last-valid-index in completed-token-p ~
               is nil")))



;;; `make-new-null-g2-token'

#+development
(defun-simple make-new-null-g2-token ()
  (let ((return-token (make-g2-token)))
    (setf (g2-token-value return-token) nil)
    (setf (g2-token-self-terminating-p return-token) nil)
    (setf (g2-token-line-index return-token) nil)
    (setf (g2-token-character-index return-token) nil)
    (setf (g2-token-text-tail return-token) nil)
    (setf (g2-token-type-or-partial-types return-token) nil)
    return-token))



;;; `encapsulate-information-into-token' - If there's something wrong with the
;;; tokenizer, look here.  Basically, this is the calling structure for editor
;;; tokenization:
;;;    1. get-next-token-or-partial-tokens-from-text - pretty much straightforward
;;;       tokenizing, with some hacks for ellispes and ambiguous tokens.
;;;       2. return-value-for-current-tokenization-state - takes care of ellipses,
;;;          do-nothing tokens, and dead states.
;;;          3. encapsulate-information-into-token - contains all the hacks that
;;;             make the nice, clean tokenizer perform all the nasty deeds that
;;;             makes G2 special.
;;; There are many comments following the definition of this function explaining
;;; the three main special cases, and all of the subfunctions are documented
;;; to explain their particular purposes in life.

(defun-simple encapsulate-information-into-token
    (last-valid-state last-valid-index)
  (let* ((token-name? (get-fsm-state-accepts-token-name? last-valid-state))
         (associated-rules-on-last-state
           (fsm-state-associated-rules last-valid-state))
         (self-terminating-p
           (self-terminating-token-type-p token-name?))
         (bogus-punctuation-p
           (bogus-punctuation-p token-name?))
         (doing-nothing-p
           (state-potentially-accepts-token-p
             last-valid-state 'do-nothing))
         (return-only-completed-tokens-p
           (not (return-partial-tokens-p current-text-tokenization-state)))
         (completed-token-p
           (and token-name?
                (completed-token-p
                  last-valid-index return-only-completed-tokens-p
                  (or bogus-punctuation-p doing-nothing-p)
                  (or self-terminating-p
                      (null associated-rules-on-last-state)))))
         (type-or-partial-types
           (if (or completed-token-p return-only-completed-tokens-p)
               token-name?
               (partial-tokens-for-state associated-rules-on-last-state)))
         (return-token (make-g2-token)))
    (when (eq type-or-partial-types 'self-terminating-punctuation-mark)
      (setq type-or-partial-types 'punctuation-mark))  ;; See Note A
    (when (and token-name? (equal type-or-partial-types '(comment)))
      (setq type-or-partial-types 'comment)  ;; See Note B
      (setq completed-token-p t))
    (when (and token-name? (equal type-or-partial-types '(single-line-comment)))
      (setq type-or-partial-types 'single-line-comment)  ;; See Note B
      (setq completed-token-p t))

    (setf (g2-token-value return-token)
          (cond
            ;; See Note C
            ((or (eq type-or-partial-types 'disambiguated-token)
                 (equal type-or-partial-types '(disambiguated-token)))
             (cond
               ((=f (character-index current-text-tokenization-state) 0)
                ;; at beginning of line...
                (when (previous-text-tail current-text-tokenization-state)
                  (cond
                    ((eql (previous-text-tail current-text-tokenization-state) -1)
                     ;; we think this case can never actually happen, but we're not
                     ;; totally sure.  If it can, and it's legitimate, then we'd need to
                     ;; have code to recompute a valid value for the previous text tail,
                     ;; possibly by going back to the entire source text and reading up
                     ;; to the current position line by line. (MHD/JV 8/3/06)
                     #+development
                     (cerror
                       "continue anyhow"
                       "previous-text-tail info needed a second time!")
                     ;; in production, don't have a previous text tail, so punt in this
                     ;; case (don't change character/line positions).
                     )
                    (t
                     ;; otherwise, must be at beginning of text, so just punt
                     (multiple-value-bind (prev-li prev-ci prev-tail prev-char)
                         (find-previous-character-if-any
                           ;; pretend we're at beginning of line 2 of a 2-line text
                           2
                           (character-index current-text-tokenization-state)
                           (previous-text-tail current-text-tokenization-state)
                           (previous-text-tail current-text-tokenization-state))
                       (declare (ignore prev-li prev-tail prev-char))
                       (decff (line-index current-text-tokenization-state))
                       (setf (character-index current-text-tokenization-state)
                             prev-ci)
                       (setf (active-text-tail current-text-tokenization-state)
                             (previous-text-tail current-text-tokenization-state))
                       ;; of course, at this point the previous-text-tail field is
                       ;; messed up, and we don't know what to do about it. we
                       ;; don't think it's needed, so just mark it as invalid with
                       ;; the -1 value, so we can check for it later if need be
                       ;; (see above). (MHD/JV 8/3/06)
                       (setf (previous-text-tail current-text-tokenization-state) -1))))))
               (t
                (decff (character-index current-text-tokenization-state))))
               ;; jh, 7/29/97.  Needs to be symbol, not punctuation-mark, to
               ;; recognize the /= operator.
               (setq type-or-partial-types 'symbol)
               (setq self-terminating-p nil)
             (setq completed-token-p t)
             (alphabet-normalized-symbol-from-text-string
               current-wide-string
               0
               (1-f fill-pointer-for-current-wide-string)))
            (completed-token-p
             (determine-lexeme-for-completed-token last-valid-state))
            (t
             (determine-lexeme-for-partial-token type-or-partial-types))))

    (setf (g2-token-self-terminating-p return-token) self-terminating-p)
    (setf (g2-token-line-index return-token)
          (line-index current-text-tokenization-state))
    (setf (g2-token-character-index return-token)
          (character-index current-text-tokenization-state))
    (setf (g2-token-text-tail return-token)
          (and completed-token-p
               (active-text-tail current-text-tokenization-state)))
    (setf (g2-token-type-or-partial-types return-token)
          (if (managed-float-p-function (g2-token-value return-token))
              'float
              type-or-partial-types))
    return-token))

;; Note A: jv, 8/27/97: The token type self-terminating-punctuation-mark
;; is a hack because we do not determine in any intelligent way whether
;; a token-type is self-terminating or not.  We probably could determine
;; that information when building the DFA.  If a state S accepts token X,
;; and there is no other state in the transitive closure of S which
;; accepts X, then when we are in state S, the token is self-terminating.
;; For example, let's say we have a token-type called comparitive-operator,
;; which includes the five tokens { = < > <= >= }.  Upon reading a '='
;; character, we would enter a state which accepts comparative-operator,
;; and there is no path out of it which could possibly lead to another
;; state accepting comparative operator.  So, we would set self-terminating-p
;; to be true.  If, however, we read a '<' character, we would again enter a
;; state which accepts comparative-operator, but in this case we would set
;; self-terminating-p to nil, because there is a path to the state which
;; accepts '<='.
;;   Anyway, that's what should be done, but it's not.  Instead, I simply
;; base self-terminating-p on the token-type.  Since G2 has always had
;; some punctuation-marks which are self-terminating, and some which
;; are not, I needed to "decide" which were which, and then split them up
;; into two separate token-types.  However, according to the grammar,
;; both groups are just called "punctuation-mark" (and rightly so.)
;; Therefore, after setting self-terminating-p, I fix up the token-type here.
;;   Incidentally, the point of self-terminating is to help prompting, and
;; this hack doesn't really even work.  It is supposed to be that if you
;; type a self-terminating token, you don't need to type any whitespace to
;; get prompted for the next token.  That can never be the case with a
;; symbol, for instance, because you can always extend a symbol.  If the user
;; has typed "foo" so far, you can't be sure he doesn't want to type "foobar"
;; until he actually types a non-symbol character like space.  The same is
;; true, of course, for "<".  However, once the user has typed "<=", we should
;; know that *that* token is self-terminating.  G2 4.0 did this correctly.
;; G2 5.0 doesn't.  It's a bug.

;; Note B: jv, 8/1/97.  It turns out comments are kind of tricky to
;; handle in an interactive tokenizer.  In a typical tokenizer, where
;; all of the input is available, comments are "absorbed" and not
;; passed on to the parser at all.  We have a problem with that,
;; however.  When the user starts typing a comment, he needs to be
;; prompted for the end of the comment.  The way that is accomplished
;; is that the parser knows that 'comment is a special case, and
;; short-circuits most of its normal work in favor of a message saying
;; something like "Use } to terminate comment".  So, like any normal
;; tokenizer, when we read a comment, we absorb it.  However, when
;; reading a *partial* comment, we need to pass 'comment to the
;; parser.  Why not just pass '(comment)?  Well, because that's not
;; what the old tokenizer did, and I tried to retrofit this tokenizer
;; into the place of the old one without messing with the parser.
;;   Perhaps a better way of handling it would be to put some property
;; on symbols which are involved in comments, instead of hard-coding
;; information about the 'comment token.  For example, we could have
;; tokens for comment-begin-indicator and comment-end-indicator, with
;; properties designating that those are not just clever names but
;; actually mean something.  That's kind of a project, though, and
;; will probably never be done in G2.

;; Note C: jh, 7/29/97.  Reverse tokenizer direction if we have typed
;; the first character of a Java comment and then decide it should be a
;; division / operator or part of a division-in-place /= operator.  This
;; is almost certainly not the right place (or level of abstraction) to
;; do this.  John V, your review is welcome.

;; jv, 8/1/97: (I wrote Note B really in response to Note C, but conceptually
;; it comes first.)  I think that if we ever did the project I alluded to in
;; Note B, this could all get better.  I think what we'd like would be for
;; the tokenizer, upon reading a '/', to prompt for /, /=, //, /*, and /**.
;; If it reads //, /*, or /**, it goes into a comment state; otherwise,
;; continue.  As it stands, it kind of works, but note that when you enter
;; a '/' into the java editor, G2 goes dumb.  It doesn't tell you anything.
;; It's waiting to disambiguate, but it's not prompting you to help it.
;; However, I think this is the best we can do without lots of work, or at
;; least without touching the parser, and I'm not eager to touch the parser.




;;; `return-value-for-current-tokenization-state'

(defun return-value-for-current-tokenization-state
    (last-valid-index last-valid-state)
  (cond
    ;; hit an ellipsis
    ((<=f 3 (ellipsis-tokenization-state current-text-tokenization-state))
     (create-g2-token nil 'ellipsis
                      (line-index current-text-tokenization-state)
                      (character-index current-text-tokenization-state)
                      nil nil))

    ;; end of text or in a dead state
    ((null last-valid-state)
     (cond
       ((and (null (next-text-tail? current-text-tokenization-state))
             (<=f (line-length current-text-tokenization-state)
                  (character-index current-text-tokenization-state)))
        (setf (character-index current-text-tokenization-state) nil)
        (setf (line-index current-text-tokenization-state) nil)
        (create-g2-token nil nil nil nil nil nil))
       ((null (wide-character? current-text-tokenization-state))
        (decff (character-index current-text-tokenization-state))
        (create-g2-token nil nil
                         (line-index current-text-tokenization-state)
                         (character-index current-text-tokenization-state)
                         nil nil))
       (t
        (create-g2-token tokenizer-illegal-character-error-message
                         nil
                         (line-index current-text-tokenization-state)
                         (character-index current-text-tokenization-state)
                         nil nil))))

    ;; hit a do-nothing token
    ((and last-valid-state
          (fsm-state-accepts-token? last-valid-state)
          (eq 'do-nothing (get-fsm-state-accepts-token-name?
                           last-valid-state)))
     (when (wide-character? current-text-tokenization-state)
       (decff (character-index current-text-tokenization-state)))
     (setq fill-pointer-for-current-wide-string 0)
     (setf (ellipsis-tokenization-state current-text-tokenization-state) 0)
     (get-next-token-or-partial-tokens-from-text))

    ;; return full or partial token
    (t
     (cond  ;; possibly adjust indices
       ((wide-character? current-text-tokenization-state)
        (decff last-valid-index)
        (decff (character-index current-text-tokenization-state)))
       ((>f (character-index current-text-tokenization-state)
            (line-length current-text-tokenization-state))
        (decff (character-index current-text-tokenization-state))))
     (encapsulate-information-into-token
       last-valid-state
       last-valid-index))))



;;; `short-circuit-for-ambiguous-token-character-p'

(defmacro short-circuit-for-ambiguous-token-character-p ()
  `(and fill-pointer-for-current-wide-string
        (=f 0 fill-pointer-for-current-wide-string)
        (char=w #.%\] (wide-character? current-text-tokenization-state))
        (instance-of-token-acceptable-in-current-edit-state-p
          '\]
          (line-index current-text-tokenization-state)
          (character-index current-text-tokenization-state))))

;;; `do-short-circuit-for-ambiguous-token-character'

(defmacro do-short-circuit-for-ambiguous-token-character ()
  `(progn
     (setq last-valid-state next-parse-state)
     (alphabet-twrite-character current-character)
     (setq last-valid-index
           (character-index current-text-tokenization-state))
     (incff (character-index current-text-tokenization-state))
     (setq active-parse-state nil)))




;;; `get-next-token-or-partial-tokens-from-text'

(defun get-next-token-or-partial-tokens-from-text ()
  (get-next-wide-character-from-text current-start-state)
  (loop with start-state = current-start-state
        with last-valid-index = nil
        with last-valid-state
        with token-too-long-p = nil
        as active-parse-state = start-state
                              then next-parse-state
        when (null (wide-character? current-text-tokenization-state)) do
            (loop-finish)
        when (<=f 3 (ellipsis-tokenization-state
                      current-text-tokenization-state)) do
            (loop-finish)
        as current-character = (wide-character?
                                 current-text-tokenization-state)
        as next-parse-state = (find-first-lexing-transition
                                current-character active-parse-state)
        as short-circuit-p = (short-circuit-for-ambiguous-token-character-p)
        when short-circuit-p do
            (do-short-circuit-for-ambiguous-token-character)
        when (null active-parse-state) do
            (loop-finish)
        as associated-rules-on-next-state
           = (and next-parse-state
                  (fsm-state-associated-rules next-parse-state))
        when associated-rules-on-next-state do
            (setq last-valid-index
                  (character-index current-text-tokenization-state))
            (setq last-valid-state next-parse-state)
        when next-parse-state do
            (cond
              ((<f fill-pointer-for-current-wide-string
                   maximum-length-for-user-text-strings)
               (alphabet-twrite-character current-character))
              (t
               ;; Give warning on first encounter of this condition, but
               ;; continue reading the characters.  Note: extremely unlikely
               ;; for this to ever happen in practice!  (MHD 7/29/04)
               (unless token-too-long-p
                 (setq token-too-long-p t)
                 (warn-of-too-long-token-truncation))))
            (get-next-wide-character-from-text next-parse-state)
        finally
          (return
            (return-value-for-current-tokenization-state
              last-valid-index
              last-valid-state))))




;;; `warn-of-too-long-token-truncation' - called by
;;; get-next-token-or-partial-tokens-from-text the first time that it reaches a
;;; limit where a token being gotten is too long to keep accumulating characters
;;; in the buffer.  The action in this case is to truncate the token.  This
;;; function advises the user, via a console message, that a token is too long,
;;; what the limit is, and that the token will therefore be truncated.  The
;;; first few (20 characters) of the token string are printed as part of the
;;; message to help make it possible to identify the offending token.

(defun warn-of-too-long-token-truncation ()
  (let* ((n 20) (string-beginning (make-stringw n)))
    (copy-portion-of-wide-string-into-wide-string
      current-wide-string 0 n string-beginning 0)
    (setf (fill-pointerw string-beginning) n)
    (notify-user-at-console
      "Warning: a token (starting with: ~a...) must be ~
       truncated because it is too long, more than ~d characters."
      string-beginning
      maximum-length-for-user-text-strings)))





;;; `for-g2-tokenizing' - the tokenizer uses structures to pass its data around,
;;; but, for now at least, its callers don't.  This macro sets up the structures
;;; necessary to begin tokenization, and "destructures" the return value into
;;; multiple values.

(defmacro for-g2-tokenizing ((text-tail line-index character-index
                                        end-line-index? end-character-index?
                                        return-partial-tokens-p) &body body)
  `(progn
     #+development
     (when (null current-text-tokenization-state)
       (cerror "Try evaluating current-text-tokenization-state again."
               "current-text-tokenization-state is nil"))
     (setf (character-index current-text-tokenization-state) ,character-index
           (line-index current-text-tokenization-state) ,line-index
           (active-text-tail current-text-tokenization-state) ,text-tail
           (end-character-index? current-text-tokenization-state) ,end-character-index?
           (end-line-index? current-text-tokenization-state) ,end-line-index?
           (return-partial-tokens-p current-text-tokenization-state)
           ,return-partial-tokens-p)
     (tokenizer-go-to-next-text-line)
     (let ((new-token
             (twith-single-value-output-to-then-use-of-wide-string
               ,@body)))
       ;; (push-token-onto-text-stack-of-tokens)
       (let ((token-value (g2-token-value new-token))
             (token-type-or-partial-types
               (g2-token-type-or-partial-types new-token))
             (line-index-for-end-of-token (g2-token-line-index new-token))
             (character-index-after-token (g2-token-character-index new-token))
             (next-text-tail (g2-token-text-tail new-token))
             (self-terminating-p (g2-token-self-terminating-p new-token)))
         (when (and (atom token-type-or-partial-types)
                    (memq-p-macro token-type-or-partial-types
                          '(whole-string left-string right-string middle-string))
                    ;; It would be nice to say that whenever the token value is
                    ;; a text-string, note use of text-string.  However, for
                    ;; errors, the value is a constant, not-to-be reclaimed
                    ;; text-string, so we need to do this memq hack.
                    tokenize-with-editing-context-p)
           #+development
           (unless (wide-string-p token-value)
             (error "Token-value for a string type must be a wide string"))
           (note-use-of-text-string-in-phrase token-value))
         (reclaim-g2-token new-token)
         (values
           token-value
           token-type-or-partial-types
           line-index-for-end-of-token
           character-index-after-token
           next-text-tail
           self-terminating-p)))))

;;; `new-get-next-token-from-wide-text-if-available-1'

(defun new-get-next-token-from-wide-text-if-available-1
    (tokenizer text-tail line-index character-index
               end-line-index? end-character-index? return-partial-tokens?)
  #+development
  (when (and return-partial-tokens?
             (null current-edit-state))
    (error "Cannot return partial tokens if there is no edit state.  ~
            Partial tokens are returned as phrase conses."))
  (in-lexing-context
    tokenizer
    (for-g2-tokenizing
      (text-tail line-index character-index
                 end-line-index? end-character-index? return-partial-tokens?)
      (get-next-token-or-partial-tokens-from-text))))



;;; `tokenize-text-string' - returns a token-list of the tokens of the
;;; given text string as tokenized by the given tokenizer.

(defun-simple tokenize-text-string (text-string? tokenizer)
  (and text-string?
       (loop with char-index? = 0
             with return-value = '()
             with text = (convert-text-string-to-text-without-duplicating-it
                           text-string?)
             while char-index? do
         (multiple-value-bind
             (token-value i1 i2 character-index-after-token)
             (new-get-next-token-from-wide-text-if-available-1
               tokenizer text 0 char-index? nil nil nil)
           (declare (ignore i1 i2))
           (setq char-index? character-index-after-token)
           (when token-value
             (token-push token-value return-value)))
             finally
               (reclaim-text-without-reclaiming-underlying-text-string text)
               (return (nreverse return-value)))))
