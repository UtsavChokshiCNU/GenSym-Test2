; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module PARSE2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; John Valente



;;;; SLR Parser




;;; `cache-of-regular-expressions' - Note that the cache is a simple
;;; array, which cannot be reclaimed.  The values in the cells are
;;; conses which are created and reclaimed during the G2  session,
;;; but the array itself is permanent.

(defparameter cache-of-regular-expressions
  (make-array-with-nils max-number-of-regexps-to-cache))



(defvar current-state-stack '())
(defvar current-token-stack '())
(defvar current-input-stack '())

(defvar current-lr-states nil)
(defvar current-nonterminals '())
(defvar current-parse-table nil)
(defvar current-productions nil)
(defvar current-terminals '())
(defvar lr0-follow '())

(defvar preprocessor-errors? '())




;;; `production'

(def-structure production
  production-lhs
  production-rhs
  production-reduction)


;;; `possible-phrase'

(def-structure possible-phrase
  possible-phrase-production
  possible-phrase-dot-position)


;;; `set-of-possible-phrases'

(def-structure set-of-possible-phrases
  set-of-possible-phrases-represents
  (set-of-possible-phrases-actions nil)
  (set-of-possible-phrases-gotos nil))


;;; `parse-table'

(def-structure parse-table
  parse-table-nonterminals
  parse-table-terminals
  parse-table-productions
  parse-table-lr-states)



;;;; Macros


;;; `in-parsing-context'

(defmacro in-parsing-context (new-parser &body body)
  `(let ((current-productions (parse-table-productions ,new-parser))
         (current-lr-states (parse-table-lr-states ,new-parser))
         (current-nonterminals (parse-table-nonterminals ,new-parser))
         (current-terminals (parse-table-terminals ,new-parser))
         (current-parse-table ,new-parser))
     ,@body))



;;; `lr-parse' - Given an input stream represented as a stack,
;;; and using the special variables current-productions and
;;; current-lr-states, parses the stream and returns either
;;; 'accept or 'reject.

(defmacro lr-parse (input-stack)
  (avoiding-variable-capture (&aux stack-of-tokens)
    `(let* ((,stack-of-tokens ,input-stack))
       (if (null ,stack-of-tokens)
           nil
           (lr-parse-1 ,stack-of-tokens)))))




;;; `token-pushnew-eq-items-in-list-reclaiming-them'

(defmacro token-pushnew-eq-items-in-list-reclaiming-them (list-1 list-2)
  `(loop for i below (length ,list-1) do
     (token-pushnew-eq (token-pop ,list-1) ,list-2)
         finally
           (return ,list-2)))

(defmacro token-pushnew-items-in-list-reclaiming-them (list-1 list-2)
  `(loop for i below (length ,list-1) do
     (token-pushnew (token-pop ,list-1) ,list-2)
         finally
           (return ,list-2)))



;;;; Basics


(defun-simple create-possible-phrase (prod pos)
  (let ((new-possible-phrase (make-possible-phrase)))
    (setf (possible-phrase-production new-possible-phrase) prod)
    (setf (possible-phrase-dot-position new-possible-phrase) pos)
    new-possible-phrase))


(defun-simple create-parse-table (nonterminals
                                   terminals productions lr-states)
  (let ((new-parse-table (make-parse-table)))
    (setf (parse-table-nonterminals new-parse-table) nonterminals)
    (setf (parse-table-terminals new-parse-table) terminals)
    (setf (parse-table-productions new-parse-table) productions)
    (setf (parse-table-lr-states new-parse-table) lr-states)
    new-parse-table))


;;; `use-parser'

#+development
(defun-simple use-parser (new-parser)
  (setq current-productions (parse-table-productions new-parser))
  (setq current-lr-states (parse-table-lr-states new-parser))
  (setq current-nonterminals (parse-table-nonterminals new-parser))
  (setq current-terminals (parse-table-terminals new-parser))
  (setq current-parse-table new-parser)
  new-parser)


;;; `same-members-p' - returns t if list1 and list2 contain the
;;; same elements, nil otherwise.  This function (which is probably
;;; already written somewhere else) is used to check something.

#+development
(defun-simple same-members-p (list1 list2)
  (let ((same t))
    (loop for element in list2
          while same
          unless (memq element list1)
            do
              (setq same nil))

    (loop for element in list1
          while same
          unless (memq element list2)
            do
              (setq same nil))
    same))





;;;; First and Follow

;;; This can and should be improved significantly.  The way I had
;;; written it originally, it would determine the "follow" of a
;;; given nonterminal by computing it each time it was asked.  I
;;; realized that was stupid, so I now have a global association
;;; list between nonterminals and their "follows".  When I want to
;;; find the follow, I just look it up in the a-list.
;;;
;;; However, the algorithm could be significantly improved now that
;;; we don't have to figure out arbitrary functions.  If we know that
;;; we will already have the "follow" of the start symbol, for example,
;;; then we can make it easier to find the "follow" of the second
;;; nonterminal.


;;; `epsilon-production-p'

(defun-simple epsilon-production-p (symbol)
  (loop for i below (length current-productions)
        as prod = (svref current-productions i)
        when (and
               (null (production-rhs prod))
               (eq symbol (production-lhs prod)))
          return t))


;;; `symbol-after'

(defun-simple symbol-after (symb rhs)
  (cond
    ((null rhs)
     nil)
    ((eq symb (car rhs))
     (cadr rhs))
    (t
     (symbol-after symb (cdr rhs)))))



;;; `symbols-appearing-in-some-production-following'

(defun-simple symbols-appearing-in-some-production-following
    (nonterm)
  (loop for i below (length current-productions)
        as prod = (svref current-productions i)
        with answer = '()
        as next-symbol = (symbol-after nonterm (production-rhs prod))
        when next-symbol do
            (token-pushnew-eq next-symbol answer)
        finally
          (return answer)))



;;; `first-can-be'

(defun-simple first-can-be (symbol list)
  (if (eq symbol (car list))
      t
      (if (epsilon-production-p (car list))
          (first-can-be symbol (cdr list))
          nil)))



;;; `can-this-production-end-with'

(defun-simple can-this-production-end-with (nonterm prod)
  (let* ((reversed-rhs (token-reverse (production-rhs prod)))
         (answer
           (if (first-can-be nonterm reversed-rhs)
               (production-lhs prod)
               nil)))
    (reclaim-token-list reversed-rhs)
    answer))


;;; `nonterms-which-have-productions-which-may-end-with'

(defun-simple nonterms-which-have-productions-which-may-end-with
    (nonterm)
  (loop for i below (length current-productions)
        as prod = (svref current-productions i)
        with answer = '()
        as whatever = (can-this-production-end-with nonterm prod)
        when whatever
          unless (eq whatever nonterm) do
              (token-pushnew whatever answer)
        finally
          (return answer)))


;;; `symbols-which-can-begin-rhs'

(defun-simple symbols-which-can-begin-rhs (rhs omit)
  (if (null rhs)
      nil
      (let* ((yn (car rhs))
             (answer '())
             (done? (memq yn omit)))
        (loop until done? do
          (cond
            ((null yn)
             (setq done? t))
            ((memq yn current-terminals)
             (token-pushnew-eq yn answer)
             (setq done? t))
            ((epsilon-production-p yn)
             (let ((new-omit
                     (token-cons yn
                              (copy-list-using-token-conses omit))))
               #+development
               (cerror "Continue"
                       "Trying to handle first for epsilon production.")
               (setq answer (lr-first yn))
               (setq yn (car rhs))
               (setq rhs (cdr rhs))
               (setq done? (memq yn new-omit))
               (reclaim-token-list new-omit)))
            (t
             (setq answer (lr-first yn))
             (setq done? t))))
        answer)))


;;; `lr-first-of-nonterminal'

(defun-simple lr-first-of-nonterminal (symb omit)
  (loop with real-omit = (token-cons symb
                                    (copy-list-using-token-conses omit))
        for i below (length current-productions)
        as prod = (svref current-productions i)
        with answer = '()
        as lhs = (production-lhs prod)
        as rhs = (if (eq lhs symb) (production-rhs prod) nil)
        as first-of-rhs = (symbols-which-can-begin-rhs rhs
                                                       real-omit)
        when first-of-rhs do
            (token-pushnew-items-in-list-reclaiming-them
              first-of-rhs
              answer)
        finally
          (reclaim-token-list real-omit)
          (return answer)))


;;; `lr-first'

(defun-simple lr-first (symb)
  (cond
    ((null symb)
     nil)
    ((memq symb current-terminals)
     (token-list symb))
    (t
     (let* ((stupid-tmp-list (token-list symb))
            (lr-first-symb
              (lr-first-of-nonterminal symb stupid-tmp-list)))
       (reclaim-token-list stupid-tmp-list)
       lr-first-symb))))


;;; `determine-follow-of-nonterminal-with-omissions'

(defun-simple determine-follow-of-nonterminal-with-omissions (nonterm omit)
  (let ((answer '()))
    (loop with nonterms-which-have-productions-which-may-end-with-nonterm
            = (nonterms-which-have-productions-which-may-end-with
                nonterm)
          for lhs in nonterms-which-have-productions-which-may-end-with-nonterm
          as computed-already? = (cdr (assoc lhs lr0-follow))
          as follow-nonterm
             = (cond
                 ((null lhs)
                  nil)
                 (computed-already?
                  (copy-list-using-token-conses
                    computed-already?))
                 ((memq lhs omit)
                  (break "Cannot handle this.~%"))
                 (t
                  (let* ((new-omit
                           (token-cons
                             lhs
                             (copy-list-using-token-conses omit)))
                         (follow-lhs
                           (follow-1 lhs new-omit)))
                    (reclaim-token-list new-omit)
                    follow-lhs)))
          do
      (token-pushnew-items-in-list-reclaiming-them
        follow-nonterm answer)
          finally
            (reclaim-token-list nonterms-which-have-productions-which-may-end-with-nonterm))
    answer))


;;; `follow-1'

(defun-simple follow-1 (nonterm omit)
  (let ((follow '()))
    (when (eq nonterm
              (production-lhs
                (svref current-productions 0)))
      (token-push nil follow))
    (loop with all-betas =
          (symbols-appearing-in-some-production-following nonterm)
          for beta in all-betas
          as first-beta = (lr-first beta) do
      (token-pushnew-items-in-list-reclaiming-them first-beta follow)
          finally
            (reclaim-token-list all-betas))
    (let ((follow-nonterm (determine-follow-of-nonterminal-with-omissions
                            nonterm omit)))
      (token-pushnew-items-in-list-reclaiming-them
        follow-nonterm follow))
    follow))




;;; `create-follow-a-list' - sets up the global variable lr0-follow.

(defun-void create-follow-a-list ()
  #+development
  (when lr0-follow
    (cerror "OK, now I have" "You need to reclaim lr0-follow first!"))

  #-development
  (when lr0-follow
    (setq lr0-follow nil))

  (loop for nonterminal in current-nonterminals
        as nonterm-follow = (follow-1 nonterminal nil)
        do
    (token-push (token-cons nonterminal nonterm-follow) lr0-follow))
  (values))


;;; `lr-follow-for-possible-phrase'

(defun-simple lr-follow-for-possible-phrase (possible-phrase)
  (let ((nonterm (production-lhs
                   (possible-phrase-production possible-phrase))))
    (cdr (assoc nonterm lr0-follow))))





;;;; LR Basics




;;; `symbol-after-dot' - returns the symbol which is found after
;;; the dot in an possible-phrase, e.g., if the possible-phrase is
;;;    E -> E . * T
;;; then the symbol after the dot is '*.

(defun-simple symbol-after-dot (possible-phrase)
  (nth
    (possible-phrase-dot-position possible-phrase)
    (production-rhs (possible-phrase-production possible-phrase))))


;;; `collect-nonterminals' - a nonterminal is any symbol which appears
;;; on the left hand side of a production.  The special variable
;;; current-productions must be set to be an array of productions
;;; representing an augmented grammar.
;;;
;;; It is helpful to know the start symbol, which is:
;;;         (production-lhs (svref current-productions 0))
;;; and which is always a (gensym)-derived symbol.  I loop through
;;; the productions backwards so that the start symbol is equal to
;;; (car current-nonterminals), but I am not sure if this is enough
;;;  to guarantee that it will be.


(defun-simple collect-nonterminals ()
  (loop with last = (1-f (length current-productions))
        for i from last downto 0
        as prod = (svref current-productions i)
        as lhs = (production-lhs prod)
        with nonterms = nil
        unless (memq lhs nonterms)
          do
            (token-push lhs nonterms)
        finally
          (return nonterms)))




;;; `symbols-in-grammar-which-are-not-nonterminals' -  The special
;;; variable current-productions must be set to be an array of
;;; productions.

(defun-simple symbols-in-grammar-which-are-not-nonterminals (nonterms)
  (loop for i from 0 below (length current-productions)
        as prod = (svref current-productions i)
        as rhs = (production-rhs prod)
        with termls = nil
        do
    (loop for symb in rhs
          unless (or (memq symb nonterms)
                     (memq symb termls))
            do
              (token-push symb termls))
        finally
          (return termls)))



;;; `production-member-of-possible-phrases-p' - returns t if the
;;; possible-phrase which represents the given production with the
;;; dot before the first symbol is present in the list of
;;; possible-phrases given, nil otherwise.

(defun-simple production-member-of-possible-phrases-p
    (production possible-phrases)
  (loop for possible-phrase in possible-phrases
        when (and (eq production
                      (possible-phrase-production possible-phrase))
                  (=f 0
                      (possible-phrase-dot-position possible-phrase)))
          return t))





;;; `unrepresented-nonkernel-possible-phrases' - returns a list
;;; of all nonkernel possible-phrases of the given nonterminal which
;;; are not already represented in the possible-phrases-list given.

(defun-simple unrepresented-nonkernel-possible-phrases
    (nonterminal possible-phrases-list)

  (loop        with answer = '()
        for production-num from 0 below (length current-productions)
        as prod = (svref current-productions production-num)
        when (eq nonterminal (production-lhs prod))
          unless (production-member-of-possible-phrases-p
                   prod possible-phrases-list)
            do
              (let ((new-possible-phrase
                      (create-possible-phrase prod 0)))
                (token-push new-possible-phrase answer))
        finally
          (return answer)))





;;; `lr-closure' - given a list of possible-phrases (or a single
;;; possible-phrase), returns a list of possible-phrases which
;;; include all the possible-phrases given, plus any new ones
;;; which can be derived by replacing the nonterminal after
;;; the dot with the right hand side of any productions derived
;;; from it.


(defun-simple lr-closure (initial-possible-phrase-or-phrases)
  (let ((done? nil)
        (answer (if (listp initial-possible-phrase-or-phrases)
                    (copy-list-using-token-conses
                      initial-possible-phrase-or-phrases)
                    (token-list
                      initial-possible-phrase-or-phrases))))

    (loop until done? do
      (setq done? t)
      (loop for possible-phrase in answer do
        (let ((next-symbol (symbol-after-dot possible-phrase)))
          (when (memq next-symbol current-nonterminals)
            (let ((new-possible-phrases
                    (unrepresented-nonkernel-possible-phrases
                      next-symbol
                      answer)))
              (loop for item in new-possible-phrases do
                (token-push item answer)
;                (reclaim-token-list new-possible-phrases)
                (setq done? nil)))))))
    answer))




;;; `find-transitions' - This function takes a set-of-possible-
;;; phrases structure and a grammar symbol, and returns a list of
;;; possible-phrases which comprise the new set-of-possible-phrases
;;; which is the destination of the transition.

(defun-simple find-transitions (set-of-possible-phrases gram-sym)
  (let ((list-of-possible-phrases
          (set-of-possible-phrases-represents
            set-of-possible-phrases)))
    (cond
      ((null list-of-possible-phrases)
       nil)
      ((atom list-of-possible-phrases)
       (error "ERROR: non-cons as the represents of: ~s~%"
              set-of-possible-phrases))
      (t
       (let ((unclosed nil))
         (loop for possible-phrase in list-of-possible-phrases
               when (eq gram-sym (symbol-after-dot possible-phrase)) do
                   (let ((new-possible-phrase
                           (create-possible-phrase
                             (possible-phrase-production
                               possible-phrase)
                             (1+f (possible-phrase-dot-position
                                     possible-phrase)))))
                     (token-push new-possible-phrase unclosed)))
         (let ((answer (lr-closure unclosed)))
;           (reclaim-token-list unclosed)
           answer))))))



;;; `possible-phrase-eql' - returns t if two possible-phrases are the
;;; same.

(defun-simple possible-phrase-eql (possible-phrase1 possible-phrase2)
  (and
    (eq (possible-phrase-production possible-phrase1)
        (possible-phrase-production possible-phrase2))
    (=f (possible-phrase-dot-position possible-phrase1)
       (possible-phrase-dot-position possible-phrase2))))



;;; `possible-phrase-member' - returns t if the structure given as the
;;; first argument is already present in the list given as the second
;;; argument.

(defun-simple possible-phrase-member (possible-phrase list)
  (loop for old-possible-phrase in list
        when (possible-phrase-eql possible-phrase old-possible-phrase)
          return t))



;;; `same-possible-phrases-p' - returns t if the two lists contain
;;; exactly the same possible-phrases (not necessarily in the same
;;; order), nil otherwise.

(defun-simple same-possible-phrases-p
    (possible-phrase-list1 possible-phrase-list2)
  (let ((same t))
    (loop for possible-phrase in possible-phrase-list2
          while same
          unless (possible-phrase-member possible-phrase
                                         possible-phrase-list1)
            do
              (setq same nil))

    (loop for possible-phrase in possible-phrase-list1
          while same
          unless (possible-phrase-member possible-phrase
                                         possible-phrase-list2)
            do
              (setq same nil))
    same))





;;; `possible-phrases-represented-in-list?' - if the list of
;;; possible-phrases given as the first argument is already
;;; represented in the list of sets-of-possible-phrases given
;;; as the second argument, returns the set-of-possible-phrases
;;; which matches.
;;;     This function is used when creating the canonical collection
;;; of sets.  As we create new sets, they are placed in a list of
;;; sets.  When we find a transition, we want to know if the state
;;; is represented already, so we call this function with the new
;;; destination and the list of states we've created already.  If
;;; it finds a match, it returns t.

(defun-simple possible-phrases-represented-in-list?
    (list-of-poss-phrases closure)
  (if (null list-of-poss-phrases)
      nil
      (loop for possible-phrases-set in closure
            when (same-possible-phrases-p
                   (set-of-possible-phrases-represents
                     possible-phrases-set)
                   list-of-poss-phrases)
              return possible-phrases-set)))


;;; `possible-phrases-represented-in-array?' - this function is
;;; obviously very similar to the previous one.  The difference
;;; is that instead of taking a list as a second argument,
;;; it uses a special array variable.

(defun-simple possible-phrases-represented-in-array? (list-of-poss-phrases)
  (if (null list-of-poss-phrases)
      nil
      (loop for i from 0 below (length current-lr-states)
            as possible-phrases-set = (svref current-lr-states i)
            when (same-possible-phrases-p
                   (set-of-possible-phrases-represents
                     possible-phrases-set)
                   list-of-poss-phrases)
                 return possible-phrases-set)))



;;; `find-destination-of-transitions' - this function is called
;;; by create-action-transitions.  It uses "find-transitions" to
;;; find the list of possible-phrases which can be reached on
;;; the given grammar symbol, but then takes the extra step of
;;; finding the structure which represents those lists.

(defun-simple find-destination-of-transitions (current-set gram-sym)
  (let* ((list-of-shift-state
           (find-transitions current-set gram-sym))
         (shift-state
           (possible-phrases-represented-in-array?
             list-of-shift-state)))
    (loop for i below (length list-of-shift-state) do
      (reclaim-possible-phrase (token-pop list-of-shift-state)))
    shift-state))





;;;; Constructing the SLR table


;;; `create-lr-states' - produces an array of structures
;;; representing sets-of-possible-phrases, which of course are
;;; actually states in the dfa we are building.  Also determines
;;; the goto function for each state.  "goto" is sort of an
;;; overloaded term.  When I refer to the goto function, it is
;;; the state to push on top of the stack after a reduce operation.
;;; These are transitions on nonterminals.   The other "goto" is the
;;; state to shift onto the stack after reading a particular terminal.
;;; Of course, there really is no difference in the dfa transitions
;;; which these will become.  The differences are that each transition
;;; is associated with either a shift or a reduce, and we need to
;;; know which one, and we represent the transitions differently.
;;;
;;; The program could be made more efficient by also determining
;;; the action functions for each state at the same time.  As it
;;; is, I loop over the states an extra time.  However, it is
;;; clearer and easier to figure out the actions after the collection
;;; of states is well defined.
;;;
;;; Note that I use "make-array" for the set of states in this function
;;; and for the productions in the following function.  Therefore,
;;; the arrays cannot be reclaimed.  These array are permanent arrays
;;; which are created as G2 is started up, and should never change
;;; during the life of that G2 process.  I hope that there's a better
;;; solution (i.e., have the table built into the binary image), but
;;; this should be ok.

(defun-simple create-lr-states ()
  (loop with current-set
          = (make-set-of-possible-phrases)
        with all-sets = (token-list current-set)
        with closure = (token-list current-set)
        with to-be-processed = '()
        with initial-possible-phrase
          = (create-possible-phrase
              (svref current-productions 0) 0)
        while current-set
        initially
          (setf (set-of-possible-phrases-represents
                  current-set)
                (lr-closure initial-possible-phrase))
        do

    (loop for gram-sym in current-terminals
          with new-set
          as new-list
             = (find-transitions current-set gram-sym)
          as duplicate-set
             = (possible-phrases-represented-in-list?
                 new-list all-sets)
          do
      (when new-list
        (cond
          (duplicate-set
           (loop for i below (length new-list) do
             (reclaim-possible-phrase (token-pop new-list))))
          (t
           (setq new-set (make-set-of-possible-phrases))
           (setf (set-of-possible-phrases-represents new-set)
                 new-list)
           (token-push new-set all-sets)
           (token-push new-set to-be-processed)))))

    (loop for gram-sym in current-nonterminals
          with new-set
          as new-list
             = (find-transitions current-set gram-sym)
          as duplicate-set
             = (possible-phrases-represented-in-list?
                 new-list all-sets)
          do
      (when new-list
        (cond
          (duplicate-set
           (token-push (token-list gram-sym duplicate-set)
                    (set-of-possible-phrases-gotos current-set))
           (loop for i below (length new-list) do
             (reclaim-possible-phrase (token-pop new-list))))
          (t
           (setq new-set (make-set-of-possible-phrases))
           (setf (set-of-possible-phrases-represents new-set)
                 new-list)
           (token-push (token-list gram-sym new-set)
                    (set-of-possible-phrases-gotos current-set))
           (token-push new-set all-sets)
           (token-push new-set to-be-processed)))))

    (cond
      (to-be-processed
       (setq current-set (token-pop to-be-processed))
       (token-push current-set closure))
      (t
       (setq current-set nil)))
    finally
          (let* ((closure-length (length closure))
                 (array-version
                   (make-array closure-length)))
            (loop for each-set in closure
                  as i downfrom (1-f closure-length) do
              (setf (svref array-version i) each-set))
;            (reclaim-token-list all-sets)
;            (reclaim-token-list closure)
;            (show-canonical-collection array-version)
            (return array-version))))





;;; `create-augmented-grammar' - takes a list of productions of
;;; the form
;;;   ((lhs-1 (rhs-1))
;;;    (lhs-2 (rhs-2))
;;;  ... etc. ...
;;;    (lhs-n (rhs-n)))
;;; and creates an array representing the augmented grammar for
;;; those productions, and returns the array.

(defun-simple create-augmented-grammar (list-of-productions)
  (let* ((num-productions (1+f (length list-of-productions)))
         (array-of-productions
           (make-array num-productions))
         (top-production (make-production)))

    (setf (production-lhs top-production) (gensym))
    (setf (production-rhs top-production)
          (token-list (caar list-of-productions)))
    (setf (production-reduction top-production) default-reduction)
    (setf (svref array-of-productions 0) top-production)

    (loop for (lhs rhs reduction) in list-of-productions
          for i from 1
          as new-production = (make-production)
          do
      (setf (production-lhs new-production) lhs)
      (setf (production-rhs new-production)
            (if (listp rhs)
                rhs
                (gensym-list rhs)))
      (if (null reduction)
          (setf (production-reduction new-production)
                default-reduction)
          (setf (production-reduction new-production) reduction))
      (setf (svref array-of-productions i) new-production))

    array-of-productions))






;;; `create-action-transitions' - The "action" function defines
;;; what to do when we are in a particular state and we read a
;;; particular terminal symbol.  The action can be either accept,
;;; shift a particular state onto the stack, reduce by a particular
;;; production, or reject.
;;;
;;;    If the following function creates more than one action
;;; for a state on a symbol, then the grammar is not SLR.
;;;
;;;    Note that this is a purely destructive function.  It
;;; returns nothing, and it doesn't create anything which
;;; needs to be reclaimed (until we are ready to throw away
;;; the parser.)  It just modifies the action field on the
;;; structures which were already created.

(defun-void create-action-transitions ()
  (loop for i from 0 below (length current-lr-states)
        as current-set = (svref current-lr-states i)
        with top-production = (svref current-productions 0)
        initially
          (create-follow-a-list)
        ;; Creates the list which associates each nonterminal N
        ;; with FOLLOW(N).
        do
    (loop for possible-phrase in (set-of-possible-phrases-represents
                                   current-set)
          as next-sym = (symbol-after-dot possible-phrase)
          do
      (cond
        ((memq next-sym current-terminals)
         ;; For each possible phrase which has a terminal after
         ;; the dot, the action upon reading that terminal, is to
         ;; shift to the state which contains the possible-phrase
         ;; with the dot after the terminal.
         (let ((shift-state (find-destination-of-transitions
                              current-set next-sym)))
           (unless (null shift-state)
             (token-push
               (token-list next-sym (token-list 'shift shift-state))
               (set-of-possible-phrases-actions
                 current-set)))))
        (next-sym
         ;; We do not derive any action from a possible-phrase
         ;; which has a symbol after the dot which is not a
         ;; terminal (ie, which is a nonterminal.)
         nil)
        ((eq (possible-phrase-production possible-phrase)
             top-production)
         ;; When we encounter the possible-phrase
         ;;      S' => S .
         ;; then the action of this state upon reading end of
         ;; string is to accept.
         (token-push
           (token-list nil (token-list 'accept))
           (set-of-possible-phrases-actions
             current-set)))
        (t
         ;; The dot follows the last symbol, but it is not S' => S.
         ;; In this case, the action is to reduce.  We reduce on
         ;; any terminal which can follow the production. Finding
         ;; those terminals is somewhat involved, and is handled
         ;; by creating an association list and then just looking
         ;; them up.
         (let ((follw (lr-follow-for-possible-phrase
                        possible-phrase))
               (production (possible-phrase-production
                           possible-phrase)))
           (loop for term in follw do
             (token-push
               (token-list term (token-list 'reduce production))
               (set-of-possible-phrases-actions
                 current-set)))))))
        finally
          (reclaim-token-tree lr0-follow)
          (setq lr0-follow nil)))





;;; `compile-parsing-table' the "parsing table" can be viewed
;;; with the function "show-parse-chart."  It shows, for
;;; every state, what is the action on each terminal, and what
;;; is the goto for each nonterminal.  In the actual implementation,
;;; however, there is no real table.  Each state is represented
;;; by a structure, where one field of that structure is an
;;; association list of terminals to actions, and another is
;;; an a-list of nonterminals to gotos.  The states themselves
;;; and their goto functions are computed by the function
;;; "create-lr-states".  Their action functions are computed by
;;; create-action-transitions.

(defun-simple compile-parsing-table (productions)
  (let* ((lr0-follow '())
         (current-productions (create-augmented-grammar
                                (cdr productions)))
         (current-nonterminals (collect-nonterminals))
         (current-terminals
           (symbols-in-grammar-which-are-not-nonterminals
             current-nonterminals)))

    #+development
    (let ((supposed-to-be-terminals (car productions)))
      (assert
        (same-members-p current-terminals supposed-to-be-terminals)
        nil
        "The terminals given in the production list,~%   ~s~%~
         were not the same as found in the productions,~%   ~s~%~
         Differences: ~s ~s~%"
        supposed-to-be-terminals current-terminals
        (set-difference supposed-to-be-terminals current-terminals)
        (set-difference current-terminals supposed-to-be-terminals)))

    (let ((current-lr-states (create-lr-states)))
      (create-action-transitions)

      (create-parse-table
        current-nonterminals
        current-terminals
        current-productions
        current-lr-states))))


;;; `def-parser'

(defmacro def-parser (parser-name parser-value)
  `(progn
     (defvar ,parser-name)
     (setq ,parser-name
           (compile-parsing-table ,parser-value))))


;;;; Parsing a Given Expression


;;; `lr-shift' - A shift consists of pushing the symbol onto the
;;; top of the stack, then pushing the state on top, and also
;;; "absorbing" the input character.

(defun-void lr-shift (new-state new-token)
  (token-push new-token current-token-stack)
  (token-push new-state  current-state-stack)
  (token-pop current-input-stack))


;;; `lr-goto' - looks up the "goto" function for the given state
;;; and nonterminal symbol.

(defun-simple lr-goto (state symbol)
  (cadr (assq symbol (set-of-possible-phrases-gotos state))))



;;; `lr-reduce' - A reduce consists of (1) popping a stack/symbol
;;; pair off the stack for each symbol in the right hand side
;;; of the production, (2) determining the next state by checking
;;; the goto function of the state on the top of the stack (after
;;; the pops), and (3) pushing the nonterminal to which the production
;;; reduces and the next state on top of the stack.  Note that
;;; we do not absorb the input character on a reduction.

(defun-void lr-reduce (production-struct)
  (let* ((number-of-constituents (length (production-rhs production-struct)))
         (last-constituent-index (1-f number-of-constituents)))
    (ensure-transform-constituent-array number-of-constituents)
    (loop for i from last-constituent-index downto 0
          as thing-on-top-of-stack = (token-pop current-token-stack)
          as value-on-top-of-stack = (parse-object-value thing-on-top-of-stack)
          do
      (reclaim-parse-object thing-on-top-of-stack)
      (token-pop current-state-stack)
      (setf (svref current-transform-constituent-array i) value-on-top-of-stack))
    (let* ((transformed-reduction
             (with-phrase-conses
               (copy-tree-using-token-conses
                 (transform-by-template   ;; in PARSE
                   (production-reduction production-struct)))))
           (non-terminal (production-lhs production-struct))
           (next-state (lr-goto (car current-state-stack) non-terminal))
           (new-parse-object
             (create-parse-object non-terminal transformed-reduction)))
      (when (null next-state)
        (error "Error in LR parsing table."))
      (token-push new-parse-object current-token-stack)
      (loop for i from last-constituent-index downto 0 do
        (reclaim-token-tree (svref current-transform-constituent-array i)))
      (token-push next-state current-state-stack))))




;;; `lr-action' - looks up the "action" function for the given
;;; state and terminal symbol.

(defun-simple lr-action (state symbol)
  (cadr (assq symbol (set-of-possible-phrases-actions state))))




#+development
(defvar *parse-trace* nil)


;;; `show-shift'

#+development
(defmacro show-shift (possible-phrase)
  #+new-tokenizer
  `(when *parse-trace*
     (dmesg "Shift ~d~%" (set-of-items->number ,possible-phrase)))
  #-new-tokenizer
  (declare (ignore possible-phrase)))

;;; `show-reduce'

#+development
(defmacro show-reduce (production)
  #+new-tokenizer
  `(when *parse-trace*
     (dmesg "Reduce ~d~%" (production->number ,production)))
  #-new-tokenizer
  (declare (ignore production)))


;;; `show-parse-for-debugging'

#+development
(defmacro show-parse-for-debugging (state-stack symbol-stack ip)
  #+new-tokenizer
  `(when *parse-trace*
     (show-terminal ,ip)
     (dmesg "|| ")
     (let ((reversed-states (token-reverse ,state-stack))
           (reversed-symbols (token-reverse ,symbol-stack)))
       (show-parse-for-debugging-1 reversed-states reversed-symbols)
       (reclaim-token-list reversed-states)
       (reclaim-token-list reversed-symbols)))
  #-new-tokenizer
  (declare (ignore state-stack symbol-stack ip)))



;;; `lr-parse-1' -   The algorithm is an "infinite" loop,
;;; which is jumped out of when we encounter an accept, reject,
;;; or unknown error.  We first make a copy of the stack, which
;;; is probably unnecessary.  For testing, I am running
;;;  (lr-parse stt) a lot, where stt is a variable bound to the
;;; result returned by (token-tokenize).  So clearly I don't want
;;; to reclaim "stt".  But during actual operation, we may; I'm
;;; not sure.

;;; Note that this code generates an unreferenced label in the
;;; translated C code.

(defun-simple lr-parse-1 (input-stack)
  (loop with current-input-stack
          = (token-reverse input-stack) ;; make a copy of the reversed list.
                                        ;; Don't touch the original list.
        with current-state-stack
          = (token-list (svref current-lr-states 0))
        with current-token-stack = '()
        with return-value = nil
        as top-token = (car current-input-stack)
        as ip = (and top-token (parse-object-type top-token))
        as action = (lr-action (car current-state-stack) ip)
        do
    ;; (show-parse-for-debugging current-state-stack
    ;; current-token-stack ip)
    (case (car action)
      (accept
       (let ((answer-token
               (token-pop current-token-stack)))
         (setq return-value
               (parse-object-value answer-token))
         (reclaim-parse-object answer-token))
       (reclaim-token-list current-state-stack)
       (reclaim-token-list current-token-stack)
       (reclaim-token-list current-input-stack)
       (return return-value))
      (shift
       ;; (show-shift (cadr action))
       (lr-shift (cadr action) top-token))
      (reduce
       ;; (show-reduce (cadr action))
       (lr-reduce (cadr action)))
      (t
       (reclaim-token-list current-state-stack)
       (reclaim-token-list current-token-stack)
       (reclaim-token-list current-input-stack)
       (return nil)))))







;;;; Preprocessing Patterns and Built In Classes


;;; `preprocessing-tokenizer'

(def-lexing-table preprocessing-tokenizer regexp-macro-tokens)



(def-parser regexp-preprocessing-parser
  '((LEFT-CURLY-BRACE RIGHT-CURLY-BRACE LEFT-PAREN RIGHT-PAREN
     DOLLAR-SIGN GREATER-THAN LESS-THAN OTHER-CHARACTER SYMBOL)
    (preprocessed-string regexp-sequence)
    (regexp-sequence basic-block (1))
    (regexp-sequence (basic-block regexp-sequence)
     (1 . 2))
    (basic-block built-in-class)
    (basic-block variable)
    (basic-block character-class)
    (basic-block SYMBOL)
    (basic-block OTHER-CHARACTER)
    (built-in-class (LESS-THAN SYMBOL GREATER-THAN)
     (built-in 2))
    (variable (DOLLAR-SIGN LEFT-PAREN SYMBOL RIGHT-PAREN)
     (variable 3))
    (character-class (LEFT-CURLY-BRACE characters RIGHT-CURLY-BRACE)
     (character-class 2))
    (characters character (1))
    (characters (character characters)
     (1 . 2))
    (character symbol)
    (character other-character)
    (character less-than)
    (character greater-than)
    (character left-paren)
    (character right-paren)
    (character left-curly-brace)
    (character dollar-sign)
    ))



;;; `preprocessor-test-suite'

#+development
(defparameter preprocessor-test-suite
  '(((defined substitution))
    .
    ((#w"{a-z}" . #w"{a-z}")
     (#w"xyz{a-z}" . #w"xyz{a-z}")
     (#w"<numeric>" . #w"{0-9}")
     (#w"abc<numeric>" . #w"abc{0-9}")
     (#w"$(defined)" . #w"((SUBSTITUTION))")
     (#w"123$(defined)" . #w"123((SUBSTITUTION))")
     (#w"\\<$(defined)>" . #w"\\<((SUBSTITUTION))>"))))


#+development
(defun validate-preprocessor (test-suite)
  (let ((current-lexing-strings
          (car test-suite)))
    (loop with all-correct = t
          for (input . output) in (cdr test-suite)
          as answer = (preprocess-regexp-string input t)
          unless (alphabet-string= answer output) do
              (format t "Error: ~s should have returned ~s but instead returned ~s~%"
                      input output answer)
              (setq all-correct nil)
          do
      (reclaim-wide-string answer)
          finally
            (when all-correct
              (format t "All tests passed!~%")))))




;;; `twrite-replacement-for-tokenizer-variable'

(defun-void twrite-replacement-for-tokenizer-variable
    (source-string start-position end-position)
  (let* ((variable-name (alphabet-symbol-from-portion-of-text
                          source-string
                          start-position
                          end-position))
         (replacement-for-pattern
           (cdr (assq variable-name current-lexing-strings))))
    (cond
      ((null replacement-for-pattern)
       (twrite-string #w"{}")
       (token-push (token-list variable-name 'variable)
                   preprocessor-errors?))
      (t
       (alphabet-twrite-character #.%\()
       (twrite replacement-for-pattern)
       (alphabet-twrite-character #.%\))))))

;;; `twrite-replacement-for-built-in-character-class'

(defun-void twrite-replacement-for-built-in-character-class
    (source-string start-position end-position)
  (let* ((class-name (alphabet-symbol-from-portion-of-text
                       source-string start-position end-position))
         (replacement-for-pattern
           (cdr (assq class-name built-in-character-codes))))
    (cond
      ((null replacement-for-pattern)
       (twrite-string #w"{}")
       (token-push (token-list class-name 'built-in)
                   preprocessor-errors?))
      (t
       (twrite replacement-for-pattern)))))


;;; `regexp-string-preprocessor-errors?'

(defun-simple regexp-string-preprocessor-errors?
    (source-string include-variables-p)
  (macrolet ((twrite-unchanged-source-string ()
               `(alphabet-twrite-portion-of-string
                  source-string start-position end-position)))
    (loop as source-index = 0 then end-position
          with preprocessor-errors? = '()
          as next-token = (get-next-token-from-text-string
                            source-string source-index)
          as end-position = (parse-object-end-index next-token)
          until (=f no-tokenizer-match-end-index end-position)
          as start-position = (parse-object-start-index next-token)
          as token-first-char = (alphabet-string-element source-string
                                                         source-index)
          do
      (alphabet-twrite-portion-of-string
        source-string source-index start-position)
      (case (parse-object-type next-token)
        (variable
         (if include-variables-p
             (twrite-replacement-for-tokenizer-variable
               source-string (+f 2 start-position) (1-f end-position))
             (twrite-unchanged-source-string)))
        (built-in
         (twrite-replacement-for-built-in-character-class
           source-string (1+f start-position) (1-f end-position)))
        (character-class
         (twrite-unchanged-source-string))
        (t
         #+development
         (cerror "Ignore it"
                 "Unrecognized preprocessor token type: ~s"
                 (parse-object-type next-token))
         (twrite-unchanged-source-string)))
      (reclaim-parse-object next-token)
          finally
            (reclaim-parse-object next-token)
            (alphabet-twrite-portion-of-string
              source-string source-index
              (alphabet-text-string-length source-string))
            (return preprocessor-errors?))))

;;; `preprocess-regexp-string'

(defun-simple preprocess-regexp-string (source-string include-variables-p)
  (in-lexing-context
    preprocessing-tokenizer
    (let* ((current-anchor-p nil)
           (errors? nil)
           (preprocessed-string
             (twith-output-to-text-string
               (setq errors? (regexp-string-preprocessor-errors?
                               source-string include-variables-p)))))
      (cond
        ((null errors?)
         preprocessed-string)
        (t
         (reclaim-wide-string preprocessed-string)
         (nreverse errors?))))))


#+development
(defun-simple preprocess-regular-expression-string (source-string)
  (let* ((wide-strings (outstanding-wide-strings))
         (token-conses (outstanding-token-conses))
         (result (preprocess-regexp-string source-string t)))
    (dmesg "Used ~d wide strings and ~d token-conses.~%Result = ~s~%"
           (-f (outstanding-wide-strings) wide-strings)
           (-f (outstanding-token-conses) token-conses)
           result)))



;;;; Caching Regular Expressions


;;; `move-to-top-of-regexp-cache'

(defun-simple move-to-top-of-regexp-cache (item)
  (loop for index from 0
        with pointer = (svref cache-of-regular-expressions index)
        until (or (null pointer)
                  (alphabet-string= (car pointer) item))
        do
    (cond
      ((<f index max-number-of-regexps-to-cache)
       (let ((temp (svref cache-of-regular-expressions index)))
         (setf (svref cache-of-regular-expressions index) pointer)
         (setf pointer temp)))
      (t
       (reclaim-wide-string (car pointer))
       (reclaim-token-tree pointer)
       (setq pointer nil)))
        finally
          (setf (svref cache-of-regular-expressions 0) pointer)
          (return pointer)))


;;; `clear-regexp-cache'

#+development
(defun-void clear-regexp-cache ()
  (loop for i below max-number-of-regexps-to-cache do
    (setf (svref cache-of-regular-expressions i) nil)))


;;; `show-regexp-cache'

#+development
(defun show-regexp-cache ()
  (loop for i from 0 below max-number-of-regexps-to-cache do
    (dmesg "~d. ~s~%" i (aref cache-of-regular-expressions i)))
  cache-of-regular-expressions)





;;;; Caching strings and lexing-tables





;;; `number-of-lexing-tables-in-cache'

(defvar number-of-lexing-tables-in-cache 0)



;;; `cache-of-lexing-tables'

(defparameter tail-of-lexing-table-cache-marker '(nil))

(defparameter cache-of-lexing-tables
  (token-list tail-of-lexing-table-cache-marker))



;;; `clear-lexing-table-cache' - this could be provided as a system
;;; procedure for those who think that G2 is leaking, like
;;; our QA group probably should.

(defun-void clear-lexing-table-cache ()
  (loop for i in cache-of-lexing-tables
        until (eq i tail-of-lexing-table-cache-marker)
        do
    (reclaim-wide-string (car-of-cons i))
    (reclaim-dfa (cdr-of-cons i))
    (reclaim-token-cons i)
        finally
          (setq number-of-lexing-tables-in-cache 0)
          (reclaim-token-list cache-of-lexing-tables)
          (setq cache-of-lexing-tables
                (token-list tail-of-lexing-table-cache-marker))))


;;; `show-lexing-table-cache'

#+development
(defun show-lexing-table-cache ()
  (format t "~d lexing tables in cache~%"
          number-of-lexing-tables-in-cache)
  (loop for i in cache-of-lexing-tables
        as j from 1
        until (eq i tail-of-lexing-table-cache-marker)
        do
    (format t "~d. ~s~%" j i))
  (values))


;;; `get-lexing-table-from-cache'

(defun-simple get-lexing-table-from-cache (text-string)
  (loop for pointer in cache-of-lexing-tables
        until (or (eq pointer tail-of-lexing-table-cache-marker)
                  (alphabet-string= (car-of-cons pointer) text-string))
        finally
          (return (cdr-of-cons pointer))))



;;; `add-lexing-table-to-cache'

(defun-simple add-lexing-table-to-cache (text-string lexing-table)
  (when (>=f number-of-lexing-tables-in-cache
             max-number-of-lexing-tables-to-cache)
    (clear-lexing-table-cache))
  (token-push (token-cons (copy-text-string text-string) lexing-table)
              cache-of-lexing-tables)
  (incff number-of-lexing-tables-in-cache)
  lexing-table)



;;; `get-lexing-table-for-regexp'

(defun-simple get-lexing-table-for-regexp (search-pattern)
  (or (get-lexing-table-from-cache search-pattern)
      (let* ((preprocessed-string-or-errors
               (preprocess-regexp-string search-pattern nil))
             (regexp-parse
               (when (wide-string-p preprocessed-string-or-errors)
                 (prog1
                     (parse-regexp-string preprocessed-string-or-errors)
                   (reclaim-wide-string preprocessed-string-or-errors)
                   (setf preprocessed-string-or-errors nil)))))
        (if regexp-parse
            (let* ((tokenizer-definition
                     ;; creates a tree which is a proper tokenizer
                     ;; definition for input to "compile-lexing table."
                     ;; That tree will have one token definition, for the
                     ;; token GOAL, consisting of regexp-parse.
                     (token-list
                       nil                        ;; patterns
                       (token-list
                         'goal
                         regexp-parse)))
                   (lexing-table-for-regexp
                     (compile-lexing-table tokenizer-definition)))
              (reclaim-token-cons (cdadr tokenizer-definition))
              (reclaim-token-cons (car-of-cons (cdr tokenizer-definition)))
              (reclaim-token-cons (cdr tokenizer-definition))
              (reclaim-token-cons tokenizer-definition)
              (add-lexing-table-to-cache
                search-pattern lexing-table-for-regexp))
            preprocessed-string-or-errors))))



;;;; Regular Expression Parsing

;;; `regular-expression-parser'
;;;
;;; The first element of the list is a list containing the terminals
;;; which the grammar expects to use.  This is similar to a yacc
;;; definition, where you must declare terminal symbols with the
;;; "%token" or "%type" directives.  The balance of the list are
;;; productions, similar in form to the syntax used by
;;; "add-grammar-rules".  One difference is that I don't support using
;;; an atom as the right-hand-side of a rule.  It's fine to have a
;;; right hand side consisting of only one symbol, but it still must
;;; be entered as a list.  To process the transformation rules, I use
;;; the exact same code as G2's parser (the interface to which is
;;; "transform-template").

(def-parser regular-expression-parser
  '((REGEXP-CHARACTER HYPHEN RIGHT-CURLY-BRACE LEFT-CURLY-BRACE DOT
     RIGHT-PAREN LEFT-PAREN QUESTION-MARK PLUS KLEENE-STAR ALTERNATIVE CARET)
    (regexp-expression (expression))
    (regexp-expression (CARET expression)
     (anchor 2))
    (expression (alternatives))
    (alternatives (regexp-sequence ALTERNATIVE alternatives)
     (either 1 3))
    (alternatives (regexp-sequence))
    (regexp-sequence (possibly-kleened-basic-block regexp-sequence)
     (seq 1 2))
    (regexp-sequence (possibly-kleened-basic-block))
    (possibly-kleened-basic-block (basic-regexp-block))
    (possibly-kleened-basic-block (kleened-basic-block))
    (kleened-basic-block (basic-regexp-block KLEENE-STAR)
     (kleene 1))
    (kleened-basic-block (basic-regexp-block PLUS)
     (plus 1))
    (kleened-basic-block (basic-regexp-block QUESTION-MARK)
     (maybe 1))
    (non-range-standard-character (REGEXP-CHARACTER))
    (non-range-standard-character (HYPHEN))
    (non-range-standard-character (RIGHT-CURLY-BRACE))
    (basic-regexp-block (LEFT-PAREN expression RIGHT-PAREN)
     2)
    (basic-regexp-block (character-class))
    (basic-regexp-block (DOT)
     (dot))
    (basic-regexp-block (non-range-standard-character))
    (character-class (LEFT-CURLY-BRACE range RIGHT-CURLY-BRACE)
     (character-class 2))
    (character-class (LEFT-CURLY-BRACE RIGHT-CURLY-BRACE)
     (nil))
    (character-class (LEFT-CURLY-BRACE CARET range RIGHT-CURLY-BRACE)
     (inverted-class 3))
    (range (range-element) (1))
    (range (range-element range) (1 . 2))
    (range-element (char-sequence))
    (range-element (REGEXP-CHARACTER))
    (char-sequence (REGEXP-CHARACTER HYPHEN REGEXP-CHARACTER)
     (1 . 3))
    ))



;;; `stack-of-regexp-tokens' - takes a text-string and returns a stack of parse
;;; objects tokenized as a regular expression.

(defun-simple stack-of-regexp-tokens (string)
  (loop with stack = '()
        with current-index? = 0
        until (null current-index?)
        as next-token = (get-next-token-from-text-string string current-index?)
        as next-lexeme = (regular-expression-lexeme string next-token)
        do
    (cond
      (next-lexeme
       (setf (parse-object-value next-token) next-lexeme)
       (setq current-index? (parse-object-end-index next-token))
       (token-push next-token stack))
      (t
       (reclaim-parse-object next-token)
       (setq current-index? nil)))
        finally
          (return stack)))


;;; `parse-unknown-regexp-string'

(defun-simple parse-unknown-regexp-string (expression)
  (in-parsing-context
    regular-expression-parser
    (let* ((stack-of-tokens (stack-of-regexp-tokens expression))
           (result (lr-parse stack-of-tokens)))
      (reclaim-token-tree stack-of-tokens)
      result)))


;;; `parse-regexp-string'

(defun-simple parse-regexp-string (wide-string)
  (let ((lookup (move-to-top-of-regexp-cache wide-string)))
    (when (null lookup)
      (let ((new-string (alphabet-copy-string wide-string))
            (parsed-string (parse-unknown-regexp-string wide-string)))
        (setq lookup (token-list new-string parsed-string)))
      (setf (svref cache-of-regular-expressions 0) lookup))
    (cadr lookup)))




;;;; Debugging Help


;;; `parse-symbols' - lr-parse takes a list of parse-objects.
;;; For testing, it's easier to just use symbols.

#+development
(defun parse-symbols (token-list)
  (let*
      ((symbol-list
         (loop with struct-list = '()
               for token in token-list
               do
           (let ((temp (create-parse-object token token)))
             (token-push temp struct-list))
               finally
                 (return struct-list)))
       (answer (lr-parse symbol-list)))
    (loop for struct in symbol-list do
      (reclaim-parse-object struct)
          finally
            (reclaim-token-list symbol-list))
    answer))


;;; `regexp-parse'

#+development
(defun-simple regexp-parse (stack-of-tokens)
  (in-parsing-context
    regular-expression-parser
    (lr-parse stack-of-tokens)))


;;; `production->number' - the production items struct does
;;; not contain any kind of index, because for parsing it
;;; is completely unnecessary to assign a number to it.
;;; However, for debugging it is much easier to refer to
;;; it by

#+development
(defun production->number (prod)
  (loop for i from 0 below (length current-productions)
        when (eq prod (svref current-productions i))
          return i))


;;; `set-of-items->number'

#+development
(defun set-of-items->number (prod)
  (loop for i from 0 below (length current-lr-states)
        when (eq prod (svref current-lr-states i))
          return i))



;;; `normal-show-terminal'

#+development
(defun normal-show-terminal (tok)
  (let ((*print-case* :downcase))
    (dmesg " ~11a "
           (if (null tok) "$" tok))))


;;; `smart-aleck-show-terminal'

#+development
(defun smart-aleck-show-terminal (tok)
  (case tok
    (basic-block
     (dmesg " bb  "))
    (regexp-character
     (dmesg " ch  "))
    (hyphen
     (dmesg " -  "))
    (right-curly-brace
     (dmesg " }  "))
    (left-curly-brace
     (dmesg " {  "))
    (dot
     (dmesg " .  "))
    (right-paren
     (dmesg " )  "))
    (left-paren
     (dmesg " (  "))
    (question-mark
     (dmesg " >  "))
    (plus
     (dmesg " +  "))
    (kleene-star
     (dmesg " *  "))
    (alternative
     (dmesg " |  "))
    (caret
     (dmesg " ^  "))
    (t1
     (dmesg " T  "))
    (integer
     (dmesg " #  "))
    (t
     (if (null tok)
         (dmesg " $  ")
         (let ((string-version (string tok)))
           (if (=f 1 (length string-version))
               (dmesg " ~c  " (char string-version 0))
               (dmesg "~c~c  " (char string-version 0)
                      (char string-version 1))))))))


;;; `show-terminal' - outputs a token.  For printing neat little
;;; charts, I want to limit the output to three characters.
;;; That's what "smart-aleck-show-terminal" does.  In other cases,
;;; we may want to see the whole thing.

#+development
(defun show-terminal (tok)
  (smart-aleck-show-terminal tok))

;; (defun show-terminal (tok)
;;  (normal-show-terminal tok))



;;; `show-terminal'

#+development
(defun show-nonterminal (tok)
  (case tok
    (regexp-expression
     (dmesg "re  "))
    (regexp-sequence
     (dmesg "sq  "))
    (alternatives
     (dmesg "alt "))
    (expression
     (dmesg "ex  "))
    (possibly-kleened-basic-block
     (dmesg "*?  "))
    (kleened-basic-block
     (dmesg "x*  "))
    (non-range-standard-character
     (dmesg "ch  "))
    (basic-regexp-block
     (dmesg "bl  "))
    (character-class
     (dmesg "{}  "))
    (range
     (dmesg "rg  "))
    (range-element
     (dmesg "el  "))
    (char-sequence
     (dmesg "cs  "))
    (t
     (let ((string-version (string tok)))
       (if (=f 1 (length string-version))
           (dmesg "~c  " (char string-version 0))
           (dmesg "~c~c  " (char string-version 0)
                  (char string-version 1)))))))



;;; `show-parse-for-debugging-1'

#+development
(defun show-parse-for-debugging-1 (state-stack symbol-stack)
  (cond
    ((null state-stack)
     (cerror "OK" "Null lr-stack!!~%"))
    ((=f 1 (length state-stack))
     (dmesg "~2d " (set-of-items->number (car state-stack)))
     (dmesg "==> "))
    (t
     (dmesg "~2d " (set-of-items->number (car state-stack)))
     ;; "[r]"
     (show-terminal (parse-object-type (car symbol-stack)))
     (show-parse-for-debugging-1 (cdr state-stack)
                                 (cdr symbol-stack)))))


;;; `show-canonical-collection'

#+development
(defun show-canonical-collection (array-of-sets)
  (loop for x from 0 below (length array-of-sets)
        with possible-phrase-set
        with next-set-of-possible-phrases
        with first-line = t
        do
    (dmesg "I(~d): " x)
    (setq first-line t)
    (setq next-set-of-possible-phrases (svref array-of-sets x))
    (setq possible-phrase-set
          (nreverse
            (set-of-possible-phrases-represents
              next-set-of-possible-phrases)))
    (loop for possible-phrase in possible-phrase-set do
      (let* ((production (possible-phrase-production possible-phrase))
             (dot-pos (possible-phrase-dot-position possible-phrase))
             (lhs (production-lhs production))
             (rhs (production-rhs production))
             (len (length rhs)))
        (if first-line
            (setq first-line nil)
            (dmesg "      "))
        (show-terminal lhs)
        (dmesg "==> ")
        (loop with i = 0
              while (< i dot-pos) do
          (show-terminal (nth i rhs))
          (incff i))
        (dmesg " . ")
        (loop with i = dot-pos
              while (< i len) do
          (show-terminal (nth i rhs))
          (incff i))
        (terpri)))
    (terpri)))





;;; `show-parse-chart'

#+development
(defun show-parse-chart ()
  (dmesg "    ")
  (loop for tm in (token-reverse current-terminals) do  ;; leaks!!
    (show-terminal tm))
  (dmesg " $       ")
  (loop for nm in current-nonterminals do
    (show-nonterminal nm))
  (dmesg "~%  ")

  (loop for tm in current-terminals do
    (dmesg "----"))
  (dmesg "----      ")
  (loop for nm in current-nonterminals do
    (dmesg "----"))
  (terpri)

  (loop for state-num from 0 below (length current-lr-states)
        as state = (svref current-lr-states state-num)
        with all-terminals
          = (token-reverse (token-cons  ;; leaks!!
                       nil
                       (copy-list-using-token-conses current-terminals)))
        do
    (dmesg "~2,' d: " state-num)
    (loop for symbol in all-terminals do
      (let ((action (lr-action state symbol)))
        (case (car action)
          (accept
           (dmesg "acc "))
          (shift
           (let ((state-num (set-of-items->number (cadr action))))
             (dmesg "s~2,' d " state-num)))
          (reduce
           (let ((prod-num (production->number (cadr action))))
             (dmesg "r~2,' d " prod-num)))
          (t
           (dmesg "--- ")))))
    (dmesg "  |  ")

    (loop for nonterm in current-nonterminals do
      (let ((go-to (lr-goto state nonterm)))
        (cond
          ((null go-to)
           (dmesg " -- "))
          (t
           (let ((state-goto (set-of-items->number go-to)))
             (dmesg " ~2,' d " state-goto)))))
          finally
            (terpri))
        finally
          (reclaim-token-list all-terminals)
          (terpri)))



;;; `show-a-production'

#+development
(defun show-a-production (production &optional known-number)
  (let ((production-number (or known-number
                               (production->number production))))
    (when (<f production-number 10)
      (dmesg " "))
    (dmesg "~d. ~s ==> ~s   [~s]~%"
           production-number
           (production-lhs production)
           (production-rhs production)
           (production-reduction production))))


;;; `show-current-productions'

#+development
(defun show-current-productions ()
  (let ((max-prod-num (length current-productions)))
    (loop for i from 0 below max-prod-num
          for prod = (svref current-productions i)
          do
      (show-a-production prod i))))


;;; `show-gotos' - the right part of the chart shown by "show-
;;;  parse-chart."

#+development
(defun show-gotos ()
  (let ((max-state-num (length current-lr-states)))
    (dmesg "     ")
    (loop for nm in current-nonterminals do
      (show-terminal nm))
    (dmesg "~%   ")
    (loop for nm in current-nonterminals do
      (dmesg "----"))
    (terpri)

    (loop for state-num from 0 below max-state-num
          as state = (svref current-lr-states state-num)
          do

      (dmesg "~2,' d." state-num)
      (loop for nonterm in current-nonterminals do
        (let ((go-to (lr-goto state nonterm)))
          (dmesg
                  (cond
                    ((null go-to)
                     "   .")
                    (t
                     (format nil "  ~2,' d"
                             (set-of-items->number
                               go-to)))))))
      (terpri))))




;;; `partial-tokens-for-state'

(defun-simple partial-tokens-for-state (associated-rules-on-last-state)
  (loop for token-number in associated-rules-on-last-state
        as probably-token-symbol
           = (internal-token-name
               (svref (lexing-table-token-array current-tokenizer)
                      token-number))
        as token-symbol = (if (eq probably-token-symbol
                                  'self-terminating-punctuation-mark)
                              'punctuation-mark
                              probably-token-symbol)
        unless (eq token-symbol 'do-nothing)
          collect token-symbol using phrase-cons))



;;; `test-partial-tokens-for-state' - uses token-conses instead of phrase-conses,
;;; and doesn't reclaim them.

#+development
(defun-simple test-partial-tokens-for-state (tokenizer associated-rules-on-last-state)
  (loop for token-number in associated-rules-on-last-state
        as probably-token-symbol
           = (internal-token-name
               (svref (lexing-table-token-array tokenizer)
                      token-number))
        as token-symbol = (if (eq probably-token-symbol
                                  'self-terminating-punctuation-mark)
                              'punctuation-mark
                              probably-token-symbol)
        unless (eq token-symbol 'do-nothing)
          collect token-symbol using token-cons))



;;; The system procedure `g2-use-tokenizer-internal' is deprecated.   Although
;;; it was never exposed to the general public, some kbs that exposed it may
;;; have gotten "out there", so instead of removing it, we made it something
;;; of a no-op.  Actually, I'm not sure why it has such a weird implementation.
;;; -jv, 5/21/04

(defun-for-system-procedure g2-use-tokenizer-internal (type)
  (with-temporary-gensym-float-creation g2-use-tokenizer-internal
    (let ((a 12)
          (b 14)
          (c 10))
      type
      (round (/ (* a b) c)))))
