;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module COMPILE1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andreas Hofmann





;;;; Overview

;;; COMPILE1 contains test-expressions, structure definitions, top level compile
;;; functions for the different statements, and notes.





;;;; To do

;; Efficiency Notes

;; Efficiency has not been an issue for the rule compiler since rules are
;; generally small and because the time taken to parse larger rules dwarfs the
;; time taken to compile them.  If the parser is improved, we may want to consider
;; efficiency improvements in the rule compiler.  One possibility is that a full
;; forward compile is done for each rule compile including focus compiles, and
;; focus compiles when there are multiple contexts.  An improvement would be to
;; take the result of forward compilation from the general compilation and make
;; copies of it for each focus compilation.  This would save calling
;; compile1-forward-reference-for-designations in compile1-expression-top for
;; focus compilations.

;; (for 2.0 definitely)
;; 2.  Split compile1-expression-top into two functions;  one for rules, and
;; one for expressions.

;; If local-names-not-associated-with-roles is non-nil, but the local names are
;; not referred to, don't make binding and strip out of expression.
;; Ex:  "create a foo M ..."  and nothing further refers to M.

;; The testing of the rule compiler should be automated.  Manual testing 
;; takes too long and is prone to error.  There are three steps to this.
;; 1.  Consolidate all test cases into one file.  Include test cases as
;; well as all rules, functions, formulas from the standard kbs.  It will
;; be necessary to give each individual rule a name.
;; 2.  Make a text file that contains the correct rule compilations such
;; that these rule compilations can be indexed by rule name.
;; 3.  Write a program that loops through all the rule names, compiles
;; the rules, and compares the results with the correct forms on file.
;; The testing phase for the 2.0 release would be a great time to do this.
;; Coordinate with Peng. 

;; Review whether illegal-reference-from-an-every-quantifier is necessary.
;; 'Every only occurs in actions.  Also, check if 
;; rule-focus-inside-every-quantifier? is needed.

;; Further simplification of second pass is still possible.  For example,
;; compile2-if-expression and compile2-or-expression have been simplified
;; to the point where they don't have to be special cases.

;; Don't allow focus compiles inside non-invertible roles.  Use focus widening.
;; Also, in the focal-classes slot, it is possible to put attribute names
;; rather than class names and get a focus compile.
;; Talk to Jim.

;; Need to improve documentation for input to and output from compiler.
;; Most of this now exists elsewhere.  This is O.K. as long as it is
;; complete and consistent.

;; Improve documentation of first pass regarding what forms need an
;; expression-for-compilation and which don't.  This can be incorporated in
;; documentation for templates.

;; Make note on fact that reference restrictions on "not", "if", and "or" have
;; been lifted for new rules.  This is possible because "any" no longer implies
;; quantification but rather iteration using rule instances.  Thus, the
;; references are bound in the context or top level let form.  Thus, there are
;; no problems with referencing designations inside these forms outside the
;; forms.  This restriction was lifted sort of at the last minute in 1.1.  It
;; should definitely get into the next release notes.  Also document fully
;; with notes on new rules at bottom of compile1.  Note also that it is now
;; no longer necessary to restrict focus inside "not" expressions.
;; Review this and also focus widening.  It should be possible to completely
;; get rid of illegal-reference-outside--sub-expression-of-expression? in
;; 2.0 if old rules are removed.  

;; Compile2-comparison-operator-expression(-top) are bad names since these
;; are used for more general things.

;; Move documentation on new rules up in this file to replace stuff on old rules.

;; (low priority but should be done soon)
;; We have to consolidate our documentation of the forms input to and output
;; from the compiler.  This is currently spread amongst various files 
;; including the grammar files, compile files, and evaluation files.
;; For the compiler, rather than specifying input and output for each operator,
;; it would probably be enough to document in terms of templates and give
;; some examples.

;; (low priority)
;; Add action templates and role templates to go with the function templates
;; (see bottom of GRAMMAR1).  Role templates will allow the compiler to give
;; (non-fatal) warning messages for undefined objects and attributes.
;; These could be just simple messages or frame notes.  The latter is more
;; complicated since they have to be removed when an object definition is
;; edited.  Also use templates in different passes of compiler, especially
;; compile1-forward-reference-for-designations.  May be able to get rid
;; of special handling for various things here.
;; One weakness of templates, however, is that they are separate from the
;; grammar.  Problems can occur if the grammar is modified without updating
;; the templates.

;; (low priority)
;; Role-name-used-to-name-kb-object? currently checks for name space confusion
;; between role names and kb object names.  
;; Ex.  "if the foo of any bar = foo ..."
;; This is currently flagged as an error.  Consider eventually just posting
;; warning message but allowing this.  This could be accomplished by using
;; compiler generated local names for the offending role name or kb object name.
;; Note that list-of-known-names and related lists set by 
;; compile-forward-reference-path only have role names;  kb object names are
;; not put onto these lists.  These lists
;;   list-of-known-names
;;   alist-of-local-names-and-role-names
;;   names-used-for-more-than-one-item
;;   role-names-and-local-names-for-runtime-items
;; need some review anyway.
;; All this would be a good to do when getting rid of old compiler stuff
;; for 2.0.

;; This is possible because the compiler does currently syntactically
;; distinguish non-designation symbols and does not compile them as
;; designations (see compile1-forward-reference-for-designations).

;; The local name could be generated in make-global-reference-structure-for-symbol
;; which calls make-extra-reference-structure.  It would use the same check
;; as the one currently done in the error message.  Have to make sure, however that
;; the compiler generated local name isn't wiped out in second pass by
;; reference-structure-provides-local-binding.  Easy to prevent this by checking
;; using reference-structure-for-global-symbol-p in 
;; reference-structure-provides-local-binding.  Compile-forward-reference-path
;; will become more complicated also since roles will have to check for conflict
;; with kb object names.  Make separate lists for known kb-object and role names.
;; Review existing lists (see above).  Abstract some of the code in
;; compile-forward-reference-path.  Flagging an error (as is currently done) is
;; easier since don't have to check for both cases (role first or kb-object name
;; first).

;; Note that there is never a conflict between local names and subsequent 
;; identical symbolic designations.  If a symbol is the same as a local name,
;; it refers to the local name and never checks whether it is the name of a
;; kb object.

;; In any case, this problem rarely occurs.

;; (low priority)
;; Review compiler generated local names.  Specifically, the elimination of 
;; such names by reference-structure-provides-local-binding? may be 
;; unnecessary.  Also review global name lists.  Also, check if can get rid
;; of find-names functions.

;; (low priority)
;; Determining whether a form is an action should be determined from the
;; syntactic position of the form in the rule rather than by checking the
;; operator of the form.  Still have to know when new actions are added to
;; grammar since they take different arguments.  This is a template issue.

;; (low priority)
;; Consider flagging error if user lists as focal class a name that doesn't 
;; appear in the rule.  Currently, the general compilation is returned.

;; (low priority)
;; Instead of using compiling-action-p, consider having the action compilers bind
;; in-non-top-level-context? (see note at bottom of compile2-name).

;; (low priority)
;; Improve compile3-expression-top (see notes for this).

;; (low priority)
;; Consider allowing local names when doing "every" iteration for an action.
;; Currently this is not allowed by the grammar.
;; "Conclude that the flow of every valve v1..." is not allowed.

;; (low priority)
;; Let forms could be compiled more efficiently.  See side note rule in
;; agh>explicit-iterators-test.kb.

;; (low priority)
;; Note that for structures are the elements of the special variables
;; context-iteration-forms and non-context-top-level-binding-forms even though only
;; the scope slot of the for structure is used.  Consider just using scope
;; lists themselves.

;; (low priority)
;; Check if set-inverse-references-for-actions function) and inverse references
;; slot for expression-for-compilation is unnecessary (for both old and new compiler).
;; Since the inverse reference path is kept on the special variable
;; pattern-checking-inverse-references, it should not be necessary to also keep
;; it in the inverse references slots.

;; (low priority)
;; Stripping out needed-domain forms in third pass is probably unnecessary since this is
;; done in second pass by compile2-name.

;; (long term)
;; Pure prenix form can be very in-efficient.  Side effects such as collection can
;; improve this.  Also, breaking out of iteration back to top level iterator is 
;; a useful capability for some cases.  We have given up on these ideas for now
;; but may want to go back to them in the distant future.

;; (low priority)
;; Document first pass better, especially domain-name-needed and local-name-provided
;; for forward and inverse reference structures.  Use plenty of reference tree
;; diagrams.

;; (low priority)
;; Review error checking frame notes.  Documentation is currently in
;; agh>generic-compiler-report.text.  Consider having compiler return
;; 'bad-phrase for general compilation errors instead of putting up a frame note.
;; This would catch such errors immediately and would ensure less errors.
;; Also, improve error notes for illegal references in "or", "if", and "not"
;; expressions.  Indicate which reference (name) is causing the problem.
;; Review all error notes.  
;; Consider using bad-phrase mechanism for compile errors.  This would have
;; to be done by the slot value compilers for rules and expressions.  These 
;; messages are nice because they come up right in the edit box.  Frame notes
;; would still have to be used for role specific compilation errors.

;; (low priority)
;; Consider eliminating some of the name slots from expression-for-compilation
;; and also functions which compute values for these.  Most of them aren't used.
;; They were used at one time for error checking.  This is now taken care of
;; by the reference structure mechanism.

;; (low priority)
;; Check if can get rid of names-used-for-more-than-one-item.
;; Also, changed unknown-references check so that it is only done for 
;; general compilation.  No reason to do it for any others.
;; This allows greatly simplifying the frame note mechanism for this
;; error;  can get rid of mechanism for putting up frame notes for 
;; each compilation.

;; (low priority)
;; Consider passing focus-local-name rather than focus-name (a role name) to
;; first-pass-problems-with-rule-compile?  This would allow for giving more
;; precise information about which compilation, in a set of multiple compilations
;; had a problem (such as a fatal focus error).  The only drawback is that
;; compiler generated local names may appear here.  However, since they don't
;; appear too frequently, probably should do this.

;; (low priority)
;; Currently, the generic simulation formula
;;   "the x of any foo = the z of the foo"
;; is compiled the same way as 
;;   "the x of any foo = the z of foo"
;; At runtime, foo is bound on the alist and any reference to foo will use
;; the alist rather than the kb.  The only way around this would be to
;; use a compiler generated local name for focus.  This should never happen 
;; anyway.  It means that the same name is used to designate an object as 
;; well as a class and should be caught at installation time by slot putters.

;; (low priority)
;; Function to reparse (and thus recompile) all statements in a knowledge
;; base.  This could be accessed by the user via the inspect facility.

;; (low priority)
;; Review expression-has-inverse-references-beyond-focus-p.  This should never
;; return true.

;; (low priority)
;; Consolidate inference engine, simulation and procedure evaluators using 
;; one def-evaluator.

;; (low priority)
;; Consider abstracting reference tree search functions.  Either make a macro,
;; or better yet, a function which takes an end test function and other arguments.
;; Actually, it may not be worth doing.  The similar portions may be small compared
;; to what has to be different.

;; (low priority)
;; Get rid of compile-specific-simulation-formula in 1.0.  It gets called
;; from the slot value compiler in GRAMMAR2 in .91 but not in 1.0.

;; (low priority)
;; Give frame note warning if some name is bound but never used.
;; It is sufficient to check just the general compilation here.

;; (low priority)
;; When local names are used, some extra let forms can get compiled.
;; Investigate this some time (not critical).
;; Ex.
;; "the foo of any bar = the level of the bar + the level of the bar"

;; (low priority)
;; Role-and-local-name (of a reference-structure) should really just be role 
;; since a role can include a local name.

;; (low priority)
;; Move specs from agh>generic-compiler-report back here (see note for
;; Synopsis of Output Forms below).

;; (low priority)
;; Compile-generic-simulation-formula and compile-generic-formula are unnecessary.
;; Just call compile-expression from slot value compilers.

;; (low priority)
;; Since analysis of top level reference trees is now emphasized rather than
;; using the "name" slots in expression for compilation, consider getting 
;; rid of these slots at some point.  They are redundant.  Also get rid of
;; related code.

;; (low priority)
;; Review special variables in compile-rule and compile-expression.  May be
;; able to get rid of some of these.

;; (low priority, review)
;; Should implement s-expression templates at some point, especially for
;; actions to indicate what is an expression, designation, string, etc.
;; This way, won't need special compilation functions for various
;; actions.  

;; (low priority, discuss with Mike)
;; Evaluators such as there-exists, when, and "and", (see RULES2) have 
;; critical areas which if they fail to evaluate, should cause the rule
;; to be tried again at some point in the future.  The decision to 
;; re-try is based on whether actions are embedded some
;; where (possibly deeply) inside these expressions.  Currently, this
;; is not readily apparent to the evaluator and it must therefore always
;; assume that actions and are embedded.  This also means
;; that there-exists can't quit once the certainty is above the truth
;; threshold;  it must iterate through all iterations so that any
;; possibly embedded actions will be handled correctly.
;; The compiler can easily make some sort of notation indicating 
;; whether actions are embedded.  One way would be to
;; have different names for expressions that have embedded actions.

;; Implement there-exists and for-all for antecedents of nested ifs.
;; Have to implement simulation evaluator for these as well
;; (talk to Mike).





;;;; Specification for Compiled Expressions Given Raw Translation for Rules



;;; See also specification for raw translation in GRAMMAR1.



;;; 1.  Synopsis of output forms

;; This has been temporarily moved to agh>generic-compiler-report.text.
;; Move back here soon.



;;; 2.  Specification for transformation of raw translation to compiled expression

;;; Although the specifications for the compiled expression are very similar
;;; to that for the raw translation, the actual forms will look quite
;;; different.  This is because the compiler pulls iteration and binding
;;; information out of the designations and separates this information from
;;; the arithmetic and logical expressions.  Thus, the designations in the
;;; compiled form can look very different from those in the raw translation.
;;; This depends on whether the designation specifies iteration and 
;;; whether bindings have to be made for names in the designation
;;; (if names specified by the designation are needed elsewhere).
;;; The iteration form is always used if the role specifies iteration
;;; (if the quantifier is "any", "every", etc.).  The binding form is
;;; used if the role specifies no iteration but the binding must be
;;; supplied to more than one expression.  If there is no iteration
;;; and no need for binding, the compiled form of the designation is
;;; the same as the raw form.

;;; For example, 
;;; (the a (any b (any c (any d))))
;;; will always be compiled to
;;; (the a b), 
;;; with iteration forms being used to bind b, c, and d:
;;; (for (any d)
;;;   (for (any c d)
;;;     (for (any b c) ...
;;; Similarly, (any a (any b (any c (any d)))) will be compiled
;;; to (the a).  Note that it isn't compiled to just "a" in order that it
;;; won't be confused with a proper name.

;;; Now, suppose that in the raw translation
;;; (the a (the b (the c (the d))))
;;; and the binding for b is needed in another expression.  In this case, 
;;; the compiled form is
;;; (the a b) which is enclosed in the appropriate way by the binding form
;;; (let ((b (the b (the c d)))) ...

;;; However, if the raw translation is
;;; (the a (the b (the c (the d))))
;;; and a, b, c, and d do not have to be bound, then the compiled form is also
;;; (the a (the b (the c (the d))))

;;; Another important difference between the raw translation and the compiled
;;; forms not apparent from the above specification is that
;;; "and" expressions in the raw translation often are compiled
;;; into nested iteration and "when" forms.

;;; Another important difference is the inverse reference forms generated
;;; when compiling with a focus name.  These are of the form
;;; (for (every-inverse domain-for-forward-compilation role-for-forward-compilation) ... )
;;; Note that domain and role are switched from the forward compilation.
;;; For example, if the forward compilation is
;;; (for (any a b) ...),
;;; then the inverse compilation is
;;; (for (every-inverse b a) ...).



;;; 3.  Compiler Errors and Restrictions

;;; If the compilation fails, nil will be returned.
;; Decide whether to put up frame notes or notices to indicate errors.



;;; A note on Efficiency Issues

;;; 2.  Efficient Compilation;  Why Pure Prenix Form is Inefficient

;;; In prenix form, all iteration is separated from and wrapped around
;;; the actual expression (the matrix) in a fully nested manner.  This results
;;; in a full cross product of all combinations.  This is appropriate for
;;; arithmetic and comparison expressions and these are therefore always
;;; compiled into pure prenix form.

;;; Ex. 4.
;;; "the a of any b + the c of any d"
;;; is compiled into
;;; (for (every b)
;;;      (for (every c)
;;; 	  (+ (the a b) (the c d)) ...

;;; In logical expressions, it is however inappropriate and inefficient to
;;; arbitrarily nest things in prenix form which have no coupling.  This is
;;; true of "or" expressions, universal quantifier expressions, and many kinds
;;; of "and" expressions.  

;;; In coupled anded expressions (where the sub-expressions of the and are 
;;; related by roles), a more efficient compilation is accomplished by allowing
;;; breaking out of the nested iterations prematurely if one of the sub-expressions
;;; is not true.

;;; Ex. 5.
;;; "if the a of any b and the d of any c of the b then ..."
;;; This can be compiled to
;;; (for (every b)
;;;      (when (the a b)
;;;        (for (every c b)
;;; 	    (when (the d c) ...
;;; Thus, the iteration can be broken off if (the a b) is false, resulting in a 
;;; pruning of the iterations nested within.
;;; This can result in significant efficiency increase if there is iteration over many
;;; entities but the expressions are only true in a small number of instances.

;;; In uncoupled anded expressions, the compilation is as in Exs. 1 and 2, which is
;;; completely unnested, and much more efficient than pure prenix form.



;;; 3.  Wake-ups and Efficient Re-evaluation of Antecedents

;;; It is important not to do any more work than is necessary when re-evaluating rules
;;; upon wake-up.  In some cases, it is necessary to re-evaluate the entire antecedent.
;;; In many cases however, it is not.

;;; The nice thing about pure prenix form is that if the matrix can't be evaluated
;;; because some variable fails to get a value, a vector of bindings from the iteration
;;; can be saved with the wake-up.  This vector can be used upon wake-up to evaluate 
;;; only that "specific" rule.  This technique can actually be extended to the other,
;;; more efficient compilation forms for coupled and uncoupled anded expressions,
;;; ored expressions, etc.  In these cases, when an evaluation fails because some
;;; variable can't get a value, a vector of bindings at that point is saved
;;; with the wake-up.  When the wake-up occurs, the rule is re-evaluated with focus
;;; on the wake-up variable.  The vector of bindings is used to resolve ambiguities
;;; in the inverse bindings.  

;; Describe this in terms of the previous examples of efficient compilations.
;; Note that this approach will also require that uncoupled things not be nested,
;; otherwise, an incorrect vector would be saved.



;;; 4.  Should Actions be Taken More than Once in One Rule Invocation?

;;; Suppose, for simplicity, that a generic rule has one action which concludes a
;;; logical variable and which does not refer to any name in the antecedent.
;;; Suppose that this rule is activated at some time, t1, that the antecedent is
;;; true beyond the required threshold, and therefore the action is taken once.
;;; Suppose further that some variables in the antecedent can't be evaluated and,
;;; therefore, wake-ups are set up.  Now, suppose that the rule is woken up at
;;; time t2 when one of these variables gets a value.  Suppose that the antecedent
;;; is true again but with a certainty different from the invocation at t1.  Should
;;; the action be taken again, resulting in a new truth value for the variable?

;;; Currently, actions are only taken once.  There are some serious
;;; problems, besides efficiency, with taking the action a second time, even
;;; though it generally is nice to update the truth value according to the
;;; latest information.  The main problem is that at t1, there may have been
;;; several rules invoked which all concluded values for the variable.  The
;;; evidence from these several rules was combined to get the actual truth
;;; value for t1.  Thus, if at t2, the action is taken again, the previous
;;; evidence is wiped out by the wake-up;;;  it is done without combining the
;;; evidence with the other rules, possibly resulting in very unexpected
;;; behavior.  A way around this dilemna would be to re-evaluate the 
;;; variable that is concluded by the rule rather than the rule itself.
;;; This would ensure proper evidence combination but could also be rather
;;; costly.  

;;; In short, it seems best that actions be taken only once per rule
;;; invocation (as is currently the case).  In fact, if all actions have
;;; been taken once, further wakeups should be removed.  This applies to
;;; both actions which refer to entities in the antecedent as well as ones
;;; which don't.



;;; Miscellaneous

;;; Rules are now of the form (if antecedent consequent).  Code associated
;;; with the else-consequent is currently obsolete and has been commented out
;;; but not deleted.

;;; Specification for Role

;;; The specification for role is the same in the parse, first pass
;;; (reference structure), second pass (for structure), and third pass
;;; (output).


;;; Compilation of "and" Expressions

;;; There are three ways to compile "and" expressions:
;;; 1.  Prenix Form
;;; Quantifiers are completely wrapped around "and" expression.
;;; Ex.
;;; (there-exists (bar)
;;;   (there-exists (foo)
;;;     (and bar foo)))
;;; This form is the simplest and least efficient.  It will form the cross
;;; product of the iterated items no matter what happens in the nested expression.
;;; 2.  Coupled Form
;;; First sub-expression of "and" is nested in its quantifiers.
;;; "When" form is generated so that if this first sub-expression
;;; fails, exits and goes on to next iteration.  If when form 
;;; succeeds, go to next sub-expression which is nested in its quantifiers.
;;; Ex.
;;; (there-exists (bar)
;;;   (when bar
;;;     (there-exists (foo) foo)))
;;; This form is more efficient than the prenix form if any of the
;;; sub-expressions (except the last one) fail since it doesn't perform
;;; iterations below the failing sub-expression.
;;; 3.  De-coupled Form
;;; Sub-expressions of the "and" are nested inside their own quantification forms,
;;; but the sub-expressions are not nested inside each other.
;;; Ex.
;;; (and (there-exists (bar) bar) (there-exists (foo) foo))
;;; This form is the most efficient since the sub-expressions are not nested.
;;; It can only be used however if the sub-expressions don't supply references
;;; to each other.  Also, if actions are to be taken on instances of foo and bar
;;; for which the antecedent was true, the instances must be collected.
;;; This makes this form complicated.

;;; Currently, coupled and de-coupled forms of compilation of "and" expressions
;;; have been disabled.  This is due to the controversy generated by the 
;;; Kodak example (see written notes).  At some point however, when it is clear
;;; when these more efficient forms can be used, they should be reinstated.
;;; The prenix form can be very inefficient.

;;; The prenix form is nice for now since it is so simple and so easy to tell if
;;; a compilation is correct.  Thus, it may be a good idea to leave it in 1.0
;;; until things are very stable.





;;;; Overview of Implementation

;;; All compilation is done via either compile-if-then-rule or compile-expression.
;;; These functions invoke the three passes of the compiler and perform the
;;; necessary error checking.  Most error checking is done right after the
;;; first pass by looking at the reference tree for the rule or expression.
;;; The compilation may be rejected at this point due to some error, or the
;;; source expression itself may be returned because it is not generic in any
;;; way.

;;; An expression or rule is defined to be generic if there is iteration
;;; (due to an iterative quantifer) and/or there is binding between expressions
;;; (one expression supplies references to another).  If the expression or
;;; rule is not generic, then it does not have to be compiled.  Whether the
;;; above conditions hold is checked after the first pass of compilation.
;;; If they don't hold, the source expression is simply returned.
 




(declare-forward-reference post-compiler-warning-note function)

;;;; Data Structures for Internal Representation During Compilation

;;; This compiler uses only phrase-cons as temporary lists and returns a value of
;;; phrase-conses.  However, as part of the compilation, the compiler typically
;;; allocates instances of the below defined structures.  These are all reclaimed
;;; by the compiler before it returns.

(def-structure (expression-for-compilation
		 #+development
		 (:print-function print-expression-for-compilation-structure))
  (compiled-specific-expression nil)
  (designations-for-expression nil)
  (local-reference-finding-paths nil)
  (inverse-references nil)
  )

;#+development
(defun print-expression-for-compilation-structure
    (expression-for-compilation stream depth)
  (declare (ignore depth))
  (printing-random-object (expression-for-compilation stream)
    (format stream "expression-for-compilation ~S"
	    (compiled-specific-expression expression-for-compilation))))

;; Compiled-specific-expression is not just text;  it is a form with the
;; as its car and then a list of numbers, symbols, and
;; expression-for-compilation structures as the cdr.

;; After the second pass, compiled-specific-expression will be further
;; modified.  It could contain nested for-structures and logical operators
;; will in general disappear.



(def-structure (for-structure)
  (scope nil)
  (body nil)
  (for-structure-in-action-p nil)
  (for-structure-binding-name? nil))



(def-structure (reference-structure)
  (domain-name-needed nil)
  (local-name-provided nil)
  (role-and-local-name nil)
  (reference-structure-providing-needed-domain-name nil)
  (reference-structures-needing-provided-local-name nil)
  (quantifier nil)
  (forward-reference-quantifier-for-inverse-references nil)
  (focus-on-local-name-of-end-reference-structure? nil)
  (copy-of-this-reference-structure-for-superior-expression nil)
  (copy-of-this-reference-structure-for-sub-expression nil)
  (embedded-expression? nil)
  (embedded-expression-original-parse? nil))

;; Domain-name-needed can be a name or it can be global-domain, needed-domain,
;; or focus-range.  Global-domain means that the instance or instances
;; corresponding to the name provided are found by searching globally.
;; Needed-domain means that the instances are found using the alist.
;; Focus-range means that the instance is the focal entity.

;; Role-and-local-name should really just be role since a role 
;; can include a local name.



;;;; Compilation Structure Memory Management

(defvar compiled-antecedent-1)
(defvar compiled-consequent-1)
(defvar compiled-consequent-2)



;;; The following set of lists hold structures created during compilation so
;;; that they can be reclaimed when done.
;; Consider abstracting these to a def-compilation-reclaimable-structure macro,
;; similar to defconser or def-ring-buffer.

(defvar list-of-expressions-for-compilation)

(defvar list-of-for-structures)

(defvar list-of-reference-structures)

(defun-simple make-compilation-reclaimable-expression-for-compilation ()
  (let ((new-expression-for-compilation
	  (make-expression-for-compilation)))
    (setq list-of-expressions-for-compilation
	  (phrase-cons new-expression-for-compilation
		       list-of-expressions-for-compilation))
    new-expression-for-compilation))

(defun-simple make-compilation-reclaimable-for-structure ()
  (let ((new-for-structure
	  (make-for-structure)))
    (setq list-of-for-structures
	  (phrase-cons new-for-structure list-of-for-structures))
    new-for-structure))

(defun-simple make-compilation-reclaimable-reference-structure ()
;  (break "make-compilation-reclaimable-reference-structure")
  (let ((new-reference-structure
	  (make-reference-structure)))
    (setq list-of-reference-structures
	  (phrase-cons new-reference-structure list-of-reference-structures))
    new-reference-structure))



(defun reclaim-all-compilation-structures ()
  (loop for expression-for-compilation
	in list-of-expressions-for-compilation
	do
    (reclaim-expression-for-compilation expression-for-compilation))
  (setf list-of-expressions-for-compilation nil)
  (loop for for-structure
	in list-of-for-structures
	do
    (reclaim-for-structure for-structure))
  (setf list-of-for-structures nil)
  (loop for reference-structure
	in list-of-reference-structures
	do
    (reclaim-reference-structure reference-structure))
  (setf list-of-reference-structures nil))



;;;; Operator and Form Primitives

(defun-simple designation-operator-p (operator)
  (memq operator '(any every the)))

(defun-simple designation-operator-or-giver-of-value-p (operator)
  (or (designation-operator-p operator)
      (eq operator 'giver-of-value)))

(defun-simple implicit-iterator-p (operator)
  (memq operator '(any every)))


(defun-simple quantifier-requires-previous-reference-p (operator)
  (eq operator 'the))


(defun-simple quantifier-or-aggregator-p (operator)
  (or (quantifier-p operator) (aggregator-p operator)))

(defun-simple quantifier-p (operator)
  (memq operator '(there-exists-literal 
		    for-every-literal)))

(defun-simple aggregator-p (operator)
  (memq operator '(sum product maximum minimum 
		    aggregated-average count)))


;;; Logical operators take truth values as arguments and return truth
;;; values.

(defun-simple logical-operator-p (operator)
  (memq operator '(and or not when)))
;; When has to be an operator for purposes of third pass compilation.
;; This should be handled better.




;; If operators take take logical values as arguments and can return numbers or
;; logical values.

(defun-simple if-operator-p (operator)
  (memq operator '(if when if* when* if-expression)))


#+unused
(defun-simple epistemological-operator-p (operator)
  (memq operator '(first-successful-evaluation if-successful-evaluation
					       first-that-has-a-value)))


;; Moved to here from file FUNCTIONS

(def-kb-specific-property-name function-definition)




(defun-simple operator-does-not-require-references-p (operator)
  (memq operator '()))

;; Review!!


;;; A simple role has no local name (see above spec).

(defun-simple simple-role-p (role)
  (or (symbolp role)
      (let ((cdr (cdr role)))
	(not (and cdr (symbolp cdr))))))


(defun-simple get-name-provided-by-role (role)
  (if (not (simple-role-p role))
      (cdr-of-cons role)
      (atomic-naming-element-of-simple-role role)))

;; see spec at top of this file on roles


(defun-simple simple-role-of-role (role)
  (if (simple-role-p role)
      role
      (car-of-cons role)))

;; The original definition of this macro is defined using def-substitute-macro.
;; It didn't get the correct role-name if the role is a cons. Now it is defined by using
; defmacro and it seems to work fine (hteng 5/1/97).
;; Hygenisized macro -dkuznick, 6/12/98

(defmacro role-name-of-non-atomic-role (role)
  (let ((role-sym (make-symbol "ROLE"))
	(role-car-sym (make-symbol "ROLE-CAR")))
    `(let* ((,role-sym ,role)
	    (,role-car-sym (car-of-cons ,role-sym)))
       (if (eq ,role-car-sym 'role-server)
	   (car-of-cons (cdr-of-cons ,role-sym))
	   ,role-car-sym))))

(defun-simple get-explicitly-specified-local-name-of-role-if-any (role)
  (if (not (simple-role-p role))
      (cdr-of-cons role)))

(defun-simple role-name-of-role (role)
  (if (symbolp role)
      role
      (role-name-of-non-atomic-role role)))



;;; (designation-p expression), where the argument is a form that can be parsed
;;; as an expression in pre-compiled syntax, is non-nil if and only if
;;; the argument is a designation.

;;; The current implementation is that it is any symbol except nil, or it is a
;;; cons whose car is 'giver of value, 'the, 'any, or 'every.

(def-substitution-macro designation-p (form)
  (if (atom form)
      (and form (symbolp form))
      (designation-operator-or-giver-of-value-p	(car form))))

;; Used in ARRAYS. Temporary fix by ML, 6/23/91
(defun-simple designation-p-function (form)
  (if (atom form)
      (and form (symbolp form))
      (designation-operator-or-giver-of-value-p	(car form))))



(defun-simple role-of-designation (designation)
  (if (atom designation)
      nil
      (second designation)))

#+unused
(defun-simple role-of-simple-designation (designation)
  (if (atom designation)
      nil
      (second designation)))




;;; The function `domain-of-designation' takes a designation and returns the parent
;;; designation (or domain) of the passed designation, or nil if there is no
;;; parent designation.

(defun-simple domain-of-designation (designation)
  (if (and (consp designation)
	   (cddr designation))
      (third designation)
      nil))




;;; The function `domain-list-of-designation' takes a designation and returns a
;;; list of the domains of that designation.

(defun-simple domain-list-of-designation (designation)
  (if (consp designation)
      (cddr designation)
      nil))




;;; The function `name-rooted-attribute-only-designation-p' takes a designation
;;; and returns whether the designation is simple enough such that it only uses
;;; names and attribute reference within it.

(defun-simple name-rooted-attribute-only-designation-p (designation)
  (or (symbolp designation)
      (and (consp designation)
	   (=f (length designation) 3)
	   (eq (car designation) 'the)
	   (symbolp (second designation))
	   (name-rooted-attribute-only-designation-p (third designation)))))




;;; Designation-requires-previous-reference-p returns t if the expression has 
;;; length 2 (indicating the root end corresponding to the root reference
;;; structure of the reference path), if the quantifier is 'the
;;; (indicating that the reference is needed here and is provided in a 
;;; previous expression), and if the role is a symbol.  An example of a 
;;; 2 element designation with a non-atomic role is
;;;     (the (role-server this-workspace)).

(defun-simple designation-requires-previous-reference-p (designation)
  (and (consp designation)
       (null (cddr designation))
       (eq (first designation) 'the)
       (symbolp (role-of-designation designation))))




;;; Focus-range, needed-domain, and global-domain are special variable flags
;;; which can appear in root reference structures and indicate what kind
;;; of root it is (how the binding for the root name of the reference path
;;; is found (see also "agh>generic-compiler-report.text").  

(def-system-variable focus-range compile1 (:funcall gentemp "focus"))
(def-system-variable needed-domain compile1 (:funcall gentemp "needed"))
(def-system-variable global-domain compile1 (:funcall gentemp "global"))

;; Gentemp is used here so that a reserved word is not necessary.  Gentemp,
;; rather than gensym is used so that the strings are not used by default for
;; subsequent calls to gensym.


;;; Expression-list-indicator, color-change-indicator, and 
;;; color-changes-indicator are used as dummy operators when compiling forms
;;; that correspond to the expression-list and color-changes template elements.

(def-system-variable expression-list-indicator 
		     compile1 (:funcall gentemp "expression-list"))

(def-system-variable color-change-indicator 
		     compile1 (:funcall gentemp "color-change"))

(def-system-variable color-changes-indicator 
		     compile1 (:funcall gentemp "color-changes"))

(def-system-variable nil-indicator 
		     compile1 (:funcall gentemp "nil-indicator"))





;;; Local-names-not-associated-with-roles currently is used only for local names
;;; used as designations in create actions and for local names used to bind the
;;; instance in a there-exists quantifier.

(def-system-variable local-names-not-associated-with-roles COMPILE1 nil)



(defun reference-structure-for-global-symbol-p (reference-structure)
  (let ((role-and-local-name
	  (role-and-local-name reference-structure)))
    (and (eq (domain-name-needed reference-structure) global-domain)
	 (eq (quantifier reference-structure) 'the)
	 (symbolp role-and-local-name)
	 (not (memq role-and-local-name
		    local-names-not-associated-with-roles)))))

(defun inverse-reference-structure-for-global-symbol-p (reference-structure)
  (and (eq (domain-name-needed reference-structure) global-domain)
       (eq (forward-reference-quantifier-for-inverse-references
	     reference-structure) 'the)))

;; The quantifier will be 'the only if the reference structure is for 
;; a kb-object-name (see compile-forward-reference-path-for-symbol).

;; Currently disabled.  See design book note for 8/18/88.


(defun rs-for-two-element-designation-with-non-atomic-role-p (reference-structure)
  (and (eq (domain-name-needed reference-structure) global-domain)
       (not (reference-structure-for-global-symbol-p 
	      reference-structure))))

;; An example of a two element designation with non-atomic role is
;; (the (role-server this-workspace)).




;;;; Atomic Elements of Roles


;;; The `atomic element of a role' is the naming element of a role which refers
;;; to the thing being designated, and is typically a class.  The `atomic class
;;; element of a role' is an atomic element of a role which is a class.  At the
;;; moment, all non-atomic roles have atomic naming elements which are classes,
;;; but it is assumed that this may not be the case in the future.

;;; The macro `atomic-naming-element-of-role' takes a role and returns the
;;; symbol which names the object or attribute being designated.  This symbol
;;; may or may not be a class.  The macro `atomic-class-element-of-role' takes a
;;; role and returns the class name found in the role if any, else NIL.
;;; Other macros defined here with similar functionality are
;;; role-of-designation, `atomic-naming-element-of-designation', and
;;; 'atomic-class-element-of-designation'.

;;; The non-atomic roles right now are at-port, at-an-input, and at-an-output.
;;; All of these roles have atomic naming elements which are classes.  The only
;;; case right now of an atomic naming element which is not a class is the case
;;; where the role is atomic and names an attribute of a class.  The following
;;; two macros rely on these assumptions and will need to be changed if any of
;;; them are invalidated.


(defun-simple atomic-naming-element-of-role (role)
  (atomic-naming-element-of-simple-role
    (simple-role-of-role role)))

(defun-simple atomic-naming-element-of-simple-role (role)
  (if (symbolp role)
      role					; Handles null case as well.
      (let ((result (car (last role))))
	(if (and (consp result)
		 (or (eq (car result) 'sequence)
		     (eq (car result) 'structure)))
	    (car result)
	    result))))

(defun-simple atomic-class-element-of-role (role)
  (let ((simple-role (simple-role-of-role role)))
    (cond ((symbolp simple-role)
	   simple-role)				; Handles null case as well.
	  ((eq (car simple-role) 'role-server)
	   (third simple-role))
	  (t
	   (car (last simple-role))))))

;; Shouldn't it be second within the clauses for 'role-server above and below?
;; -jra 5/11/91

(defun-simple atomic-class-element-of-simple-role (role)
  (cond ((symbolp role)
	 role)					; Handles null case as well.
	((eq (car role) 'role-server)
	 (third role))
	(t
	 (car (last role)))))

;; At the moment there are no non-null naming elements of roles which are not
;; classes in the cases being checked in the forward chaining code.  When this
;; assumption becomes invalid, the first definition above should be commented
;; back in, and the second definition deleted! -jra 8/13/87

;; The new non-atomic role with a naming element which is not a class is the
;; role role-server.  Accordingly, the definition of atomic-class-element-of-
;; role has been redefined.  -jra 5/31/89

;; A new restriction has been added to role definitions, which is that all roles
;; but attributes must have a type associated with them.  The type is found by
;; calling the function type-of-designation.  Note that this function returns
;; either one of the defined data types (e.g. number, symbol, etc.) or else it
;; returns a symbol which is a class name.  Designations which reference
;; attributes of frames currently will always return NIL, since no typing can be
;; guaranteed for attributes, but the plan is to allow typing declarations are
;; part of class definitions, and that these type definitions will then be able
;; to be exploited by compilers which optimize by type.  -jra 6/21/89

(defun-simple atomic-naming-element-of-designation (designation)
  (atomic-naming-element-of-role (role-of-designation designation)))

(defun-simple atomic-class-element-of-designation (designation)
  (atomic-class-element-of-role (role-of-designation designation)))

;; Note that both atomic-class-element-of-role and 
;; atomic-class-element-of-designation are not strictly correct since
;; they will return an attribute rather than a class when the role
;; is an attribute.  This is not currently a problem since 
;; atomic-class-element-of-role is not called for attribute roles in
;; chaining analysis (see above note) and atomic-class-element-of-designation
;; is only called by connection role servers.  However, 
;; atomic-class-element-of-designation should be fixed by having it call
;; type-of-designation!!




;;;; Rule Compilation




;; Much of the following is applicable to expression compilation as well.

;;; The rule grammar is such that expressions with non-logical
;;; (arithmetic) operators are nested inside ones with logical
;;; operators.  The first pass builds the expression-for-compilation
;;; structures.  It deals with non-logical operators, and specific and
;;; generic references to variables setting up the corresponding
;;; specific expressions and the reference structures between names.
;;; The second pass uses the expression-for-compilation structures to
;;; generate a more complete compiled rule form.  It deals with logical
;;; operators.  The third pass generates the actual output compiled rule
;;; form.  Eventually, all these passes may be unnecessary but they are
;;; useful for now.


;; Conventions: first pass - compile1-...,  second pass - compile2-...,
;; third pass - compile3-...


;;; Compilation-local-names are automatically generated by the compiler
;;; in the first pass to differentiate different items designated in a rule 
;;; or expression using the same role.  An item is a runtime object referred
;;; to somehow in a rule.  For example, in the following rule, the role
;;; foo is used four times:
;;;   "if the foo of any bar and the baz of the foo
;;;    and the foo of any biz and the fiz of the foo ..." .
;;; Only two different items are actually designated however.  Thus, the
;;; rule could be re-written using local names as
;;;   "if the foo foo1 of any bar and the baz of foo1
;;;   and the foo foo2 of any biz and the fiz of the foo2 ..." .
;;; If local names aren't specified by the user, the compiler will automatically
;;; generate its own and use them to differentiate the items.  Actually, a 
;;; local name is not generated for the first item;  the role name is just used.
;;; Details of how the compiler detects a different item and generates
;;; local names is documented in compile-forward-reference-path.

(def-interned-symbol-supply "compilation-local-name")


;;; If focus-name? is nil, the general compilation will be returned.

;; In making use of this (in file RULES), I have assumed that if the compilation
;; cannot be performed because the inputs are incorrect, then the value will be
;; NIL. - ML -


;;; The bad-rule flag is used by compile-rule to indicate that the rule
;;; had errors.

(def-system-variable bad-rule compile1 (:funcall gentemp "bad-rule"))


(defvar focus-name-for-rule-or-formula-compilation)


;;; Focus-too-narrow? is a flag set by compile1-expression-top if the function
;;; too-narrow-focus? returns non-nil.  This means that there was an illegal but
;;; not fatal focus error, meaning that compile-rule should just return the
;;; general compilation as the focus compilation.  This is only an issue with 
;;; rule compilations, not with expression compilations.

(def-system-variable focus-too-narrow? COMPILE1 nil)




;;; Fatal-focus-error-info? is set within compile1-expression-top if there is
;;; a fatal focus error.  It is set to the kind of action in which the fatal
;;; focus error occurred.  This is used by the error checking functions 
;;; invoked by compile-rule after the first pass to put up frame notes if
;;; necessary.

(def-system-variable fatal-focus-error-info? COMPILE1 nil)
(def-system-variable fatal-focus-error-info-for-all-compilations COMPILE1 nil)


;;; Focus-local-name-for-rule-compilation? is set by compile1-expression-top
;;; when there are multiple compilations.

(def-system-variable focus-local-name-for-rule-compilation? COMPILE1 nil)
(def-system-variable compiling-antecedent-p COMPILE1 nil)


(defvar list-of-known-names)


;;; Alist-of-local-names-and-role-names provides a mapping from local names
;;; (either compiler generated or user specified) to (unique) role names.
;;; The value is set by compile-forward-reference-path.
;;; It is used by check-if-role-name-is-same-as-previous-local-name.
;;; It is also used by symbol-used-as-local-name-p.

(defvar alist-of-local-names-and-role-names)



;;; Names-used-for-more-than-one-item is an alist of the form
;;;   ( (name-used-for-more-than-one-item . compiler-generated-local-names) ...)
;;; Name-used-for-more-than-one-item must be a role-name, not a user specified
;;; local name.  If it is a user specified local name, an error is flagged.
;;; Names-used-for-more-than-one-item is maintained by compile-forward-reference-path.
;;; This function detects if a name is being used for a new item and if so,
;;; generates a local name.  An entry for name is then made in the alist
;;; of names-used-for-more-than-one-item and the local name is added to this entry.

(defvar names-used-for-more-than-one-item)


;;; Role-names-and-local-names-for-runtime-items is an alist of the form
;;; ( (role-name . local-name) ...) where local name is an explicitly 
;;; declared local name, or just the role name.  Note that 
;;; compiler generated local names are replaced with the role name on this
;;; list.
;;; There is an entry for each runtime instance declared in the source rule or
;;; expression.  Role-names-and-local-names-for-runtime-items is maintained
;;; by compile-forward-reference-path.

(defvar role-names-and-local-names-for-runtime-items)


;;; When the same role-name is used to specify more than one item (regardless of
;;; whether user specified or compiler generated local names are used to distinguish)
;;; there will be multiple compilations if the focus is the role-name.  The special
;;; variable focus-local-names-for-focus-role-name, bound in 
;;; compile1-expression-top, holds the local names corresponding to each
;;; individual compilation in the set of multiple compilations.  
;;; It is of the form 
;;;   ((focus-local-name . chaining-category) ...)
;;; where chaining-category can be 'forward, 'backward, or 'both.  This list is
;;; generated by compile-forward-reference-path each time compile1-expression-top
;;; is called.  Compile1-expression-top is called iteratively by compile-rule
;;; which passes in a number indicating which of the local names to use for 
;;; focus.  Compile1-expression-top returns (besides the compiled forms) this
;;; number incremented by 1 as a continuation if there are any more local names
;;; still to be compiled for focus.  Note that this list is completely generated
;;; each time compile1-expression-top is called even though only one of the names
;;; will be used to focus.

(defvar focus-local-names-for-focus-role-name)


;;; Local-name-errors can be set by compile-forward-reference-path if there is
;;; a problem.  Values can include:
;;; ('explicitly-specified-local-name-refers-to-more-than-one-item
;;;   explicitly-specified-local-name)
;;; ('ambiguous-reference role-name)
;;; ('root-reference-role-name-same-as-previously-specified-local-name role-name)
;;; This special variable is bound in compile-rule and is checked after first
;;; pass.

(defvar local-name-errors)


;;; Inside-action-iteration-p is a flag indicating that the the iteration
;;; or binding form (for-structure) is in an action.  This flag is set
;;; appropriately by the action compilation functions and causes the 
;;; for-structure-in-action-p slot of the for-structure to be set.
;;; This, in turn, causes the third pass to generate action iteration 
;;; or binding forms ("for-every", "let-action") rather than expression
;;; forms.  Note that "for-every" and "let-action" are the only iteration or
;;; binding forms that can appear in an action since the quantifier "any"
;;; is not allowed in an action, and since inverse references are all wrapped
;;; around the antecedent.  The "for-every" form is like the "for-all" form
;;; which appears in expressions.  Both involve iteration over all instances.
;;; The difference is that "for-all" returns a value; it is the universal
;;; quantifier, whereas "for-every" returns no value.  For example,   
;;; the conclude action
;;; "conclude that every valve is broken"
;;; specifies to iterate over every valve and conclude that it is broken.
;;; Universal quantification is not called for in this case.

(def-system-variable inside-action-iteration-p COMPILE1 nil)


;;; Top-level-reference-tree is the top level tree of reference structures 
;;; resulting from first pass compilation of a rule or expression.
;; (see also agh>generic-compiler-report.text)

(defvar top-level-reference-tree)


;;; Pattern-checking-inverse-references ...
;; (see agh>generic-compiler-report.text for now)

(def-system-variable pattern-checking-inverse-references COMPILE1 nil)


;;; Wrapper-references-for-left-side-of-formula? contains the reference
;;; structure for the left side of a formula when a generic-formula or
;;; generic-simulation-formula is being compiled.  This is used to wrap
;;; a "let" binding form around the compiled form for the right side of
;;; the formula so that the attribute can be referred to directly in the
;;; right side.

(def-system-variable wrapper-references-for-left-side-of-formula? COMPILE1 nil)


;;; If a rule has explicit iteration forms, compile rule puts the 
;;; designations in designations-from-explicit-iteration-forms.
;;; The uncompiled designations are kept separately in
;;; source-designations-from-explicit-iteration-forms since this
;;; may be accessed more than once for multiple compilations.

(def-system-variable designations-from-explicit-iteration-forms COMPILE1 nil)
(def-system-variable source-designations-from-explicit-iteration-forms COMPILE1 nil)
(def-system-variable compiling-rule-p COMPILE1 nil)
(def-system-variable compiling-expression-p COMPILE1 nil)

(defvar context-iteration-forms)
(defvar non-context-top-level-binding-forms)
(defvar number-of-no-binds)
;added by SoftServe
(defvar assignment-section-forms nil)
;end of SoftServe changes

;; used only for rule compilation




;;; The variable `Post-compiler-warning-note?' is globally bound, by default, to
;;; true.  It may be rebound to nil in order to suppress posting logbook
;;; notifications as to the existence of compiler warning notes.  Note that this
;;; does not suppress compiler warning notes, only logbook notifications about
;;; them.

;;; Examples: This is used by Inspect to suppress notes about problems compiling
;;; the query, since the frame that gets compiled is not an item accessible to
;;; users, and since the notes are displayed for the user in any case.  This is
;;; also used by the G2DS facility (install-inter-g2-data-request-expression)
;;; to suppress posting notifications about compiler warnings that result from
;;; compiling and installing an expression via inter-g2 data service.

(defvar post-compiler-warning-note? t)

;; The documentation above is new, as is the use in Inspect.  Otherwise, this
;; "facility" was in place for me.   (MHD 11/15/91)




;;; Attribute-name-errors contains any illegal attributes (system attributes for
;;; example) encountered during the compile.  Compile-forward-reference-path
;;; checks for such illegal attributes and adds any to attribute-name-errors.
;;; Functions called by first-pass-problems-with-rule-compile?  and
;;; first-pass-problems-with-expression-compile?  check attribute-name-errors and
;;; post warnings if it is non-nil.

(defvar attribute-name-errors)



;;; Allow-in-line-designations?  causes compile2-name to put any designations
;;; which could go into the outermost let form into it rather than putting them
;;; in-line, even if the designations don't require a let form.  This is needed
;;; for simulation formulas since for these, bindings are usually cached.  Note
;;; that this does not necessarily completely eliminate in-line designations in
;;; generic simulation formulas; they can still appear within quantifiers and
;;; aggregators.  

(def-system-variable allow-in-line-designations? COMPILE1 t)



;;; Reference-structures-originating-from-within-existence-predicate is
;;; used to determine which bindings must be local.

(defvar reference-structures-originating-from-within-existence-predicate)
(defvar local-iteration-forms)
(defvar local-insertion-location)



(declare-forward-reference make-for-structure-given-reference-structure function)
(declare-forward-reference compile3-expression function)
(declare-forward-reference compile3-expression-top function)
(declare-forward-reference compile3-rule function)
(declare-forward-reference compile2-expression-top function)
(declare-forward-reference
  compile2-designations-from-explicit-iteration-forms function)
(declare-forward-reference compile1-expression-top function)



(defmacro with-compilation-bindings
	  (focus-name? other-binding-forms? &body body)
  `(let* ((list-of-expressions-for-compilation nil)
	  (list-of-for-structures nil)
	  (list-of-reference-structures nil)
	  (focus-name-for-rule-or-formula-compilation ,focus-name?)
	  (list-of-known-names nil)
	  (names-used-for-more-than-one-item nil)
	  (role-names-and-local-names-for-runtime-items nil)
	  (alist-of-local-names-and-role-names nil)
	  (local-names-not-associated-with-roles nil)
	  (top-level-reference-tree nil)
	  (local-name-errors nil)
	  (focus-local-names-for-focus-role-name nil)
	  (non-context-top-level-binding-forms nil)
	  (attribute-name-errors nil)
	  (reference-structures-originating-from-within-existence-predicate nil)
	  (local-iteration-forms nil)
	  (local-insertion-location nil)
	  ,@other-binding-forms?)
     ,@body))

#+development
(defun print-compilation-state ()
  (format t "~%focus-name-for-rule-or-formula-compilation = ~S" 
	  focus-name-for-rule-or-formula-compilation)
  (format t "~%list-of-known-names = ~S" 
	  list-of-known-names)
  (format t "~%names-used-for-more-than-one-item = ~S" 
	  names-used-for-more-than-one-item)
  (format t "~%role-names-and-local-names-for-runtime-items = ~S" 
	  role-names-and-local-names-for-runtime-items)
  (format t "~%alist-of-local-names-and-role-names = ~S" 
	  alist-of-local-names-and-role-names)
  (format t "~%local-names-not-associated-with-roles = ~S" 
	  local-names-not-associated-with-roles)
  (format t "~%focus-local-names-for-focus-role-name = ~S" 
	  focus-local-names-for-focus-role-name))

#+development
(declare-forward-reference pad-n-spaces function)

#+development
(defun print-expression-for-compilation-1 (expression stream indent-level)
    (format stream "~%(~a):" indent-level)
    (format stream "~a" expression)
    (cond
      ((not (expression-for-compilation-p expression))
       (format stream "~a" expression))
      ((consp (compiled-specific-expression expression))
       (loop for item in (compiled-specific-expression expression)
	     do
	 (cond ((expression-for-compilation-p item)
		(print-expression-for-compilation-1 item stream (+ indent-level 1)))
	       (t
		(format stream "~a" item)))))
      (t
       (format stream "~a" (compiled-specific-expression expression)))))

#+development
(defun print-expression-for-compilation (expression &optional (stream *standard-output*))
  (print-expression-for-compilation-1 expression stream 0))

;;; Compile-rule returns a list of the form (body context) for the general
;;; compilation and a list of the form (context . rest-of-multiple-contexts)
;;; for focus compilations.  Nil is returned if a compilation error occurs.

;;; Compile-rule passes the antecedent-expression, and consequent-expression,
;;; through each of the three passes.  Error checking is done after the first
;;; pass.  If an error is detected, the compile fails and nil is returned.  A
;;; brief explanation is posted on the message board and a more detailed
;;; explanation is given in the frame notes of the rule.  The rule is passed in
;;; as the third argument for this purpose.  The context for the general
;;; compilation is passed in as the fourth argument.  This is used for focus
;;; compilations where the focus was too narrow (see too-narrow-focus?, called
;;; by compile1-expression-top).  Note that compile-rule does not check the
;;; general compilation to make sure it is ok before trying focus compilations;
;;; this check is made by slot value compilers that call compile-rule.

;;; Compile-rule will return a list containing any of the following forms:

;;; (NIL . compiled-form)
;;; (focus-role-name . compiled-form)
;;; ((focus-role-name FORWARD-CHAINING focus-local-name) . compiled-form)
;;; ((focus-role-name BACKWARD-CHAINING focus-local-name) . compiled-form)
;;; ((focus-role-name BOTH focus-local-name) . compiled-form)

;;; If there are multiple compilations, the list will have more than one
;;; element.  Multiple compilations can occur 
;;; when the same role name is used to name more than one runtime
;;; item and the focus is for that role name.  The chaining category 
;;; ('forward-chaining, 'backward-chaining, or 'both)
;;; is specified if the compilation is to be used only for one of these.
;;; When there are multiple compilations for a focus role name, each
;;; of these compilations corresponds to a distinct focus-local-name
;;; (see compile1-expression-top).  The focus-local-name must be returned
;;; as part of the compilation so that the inference engine binds it,
;;; rather than the focus role name, on the alist.

;;; Compile-rule generates multiple compilations by iteratively calling
;;; the three compilation pass functions as long as compile1-expression-top
;;; returns a continuation.  Note that any of these iterations may fail to
;;; produce a compiled form, due to an error for that focus local name.
;;; As mentioned before, if there are any errors in the general compilation,
;;; a focus compile will not be performed.

(defun compile-rule
       (rule-translation focus-name? context-for-general-compilation using-section)
  (declare (ignore using-section)) ; added by SoftServe
  (with-updates-to-representations-supressed 
      (*current-computation-frame* 'frame-status-and-notes)
    (with-interned-compilation-local-name-symbols
      (with-compilation-bindings
	focus-name?
          ((rule *current-computation-frame*)
	 (designations-from-explicit-iteration-forms nil)
	 (source-designations-from-explicit-iteration-forms nil)
	 (rule-translation (filter-explicit-iteration-forms rule-translation))
	 (rule-keyword (first rule-translation))
	 (antecedent-expression 
	                        (second rule-translation))
	 (consequent-expression (third rule-translation))
	 (compiling-antecedent-p nil)
	 (inside-action-iteration-p nil)
	 (pattern-checking-inverse-references nil)
	 (chaining-category? nil)
	 (focus-local-name-for-rule-compilation? nil)
	 (focus-too-narrow? nil)
	 (fatal-focus-error-info? nil)
	 (fatal-focus-error-info-for-all-compilations nil)
	 (compiling-rule-p t)
	 (context-iteration-forms nil)
	 (compiled-antecedent-1 nil)
	 (compiled-consequent-1 nil)
	 (compiled-antecedent-2 nil)
	 (compiled-consequent-2 nil)
	 (number-of-no-binds 0)
	 context-for-this-focus-local-name
	 body-of-rule)
	
	(if (null focus-name?)
	    (progn
	      (clear-multiple-compilations rule)
	      (delete-all-frame-notes-for-rule-or-expression nil)
	      ;; If compiling general compilation, will be compiling all compilations
	      ;; with focus as well.  Therefore, just delete all frame notes.
	      )
	    (delete-compiler-frame-notes-for-role focus-name?))
	
	(loop with focus-local-name-continuation? = nil
	      with multiple-context-compilations = nil
	      do
	  (multiple-value-setq
	    (compiled-antecedent-1 compiled-consequent-1
	     chaining-category?
	     focus-local-name-for-rule-compilation?
	     focus-local-name-continuation?)
	    (compile1-expression-top 
	      antecedent-expression consequent-expression nil 
	      (phrase-list focus-name?)
	      focus-local-name-continuation?))

;	   (cerror "continue" "after first pass")
	  
	  (multiple-value-setq
	    (context-for-this-focus-local-name body-of-rule)
	    (cond
	      ((first-pass-problems-with-rule-compile? focus-name?)
	       (values bad-rule nil))
	      
	      ((and focus-name?
		    (null pattern-checking-inverse-references))
	       ;; If focus name has been entered by user into focal classes
	       ;; but does not appear in the rule, the context is the symbol
	       ;; 'universal-compilation.  This tells the inference engine
	       ;; that the focus name should not be part of the context.
	       (values 'universal-compilation nil))
	      
	      ((and (not focus-name?)
		    (not (reference-paths-generic-p
			   top-level-reference-tree))
		    (not (expression-has-inverse-references-beyond-focus-p
			   compiled-antecedent-1))
		    (not local-names-not-associated-with-roles))
	       ;; If rule is not generic, it doesn't have to be compiled
	       ;; so just return it.
	       (values
		 nil (phrase-list 
		       rule-keyword antecedent-expression consequent-expression)))
	      
	      (focus-too-narrow?
	       ;; If focus is too narrow,
	       ;; then it is impossible to compile with focus and the
	       ;; general compilation is returned.  See also 
	       ;; compile1-expression-top and too-narrow-focus?
	       ;; Note that no body-of-rule has to be returned if compiling
	       ;; with focus.
	       (values (cdr context-for-general-compilation) t))
	      
	      (t				; if generic and no errors, continue compilation
	       (setq compiled-consequent-2
		     (compile-consequent
		       compiled-consequent-1 'compile2-action))
	       
	       (compile2-designations-from-explicit-iteration-forms)
	       (let ((compiling-antecedent-p t))
;		 (break "yo")
		 (setq compiled-antecedent-2
		       (compile2-expression-top compiled-antecedent-1)))

;	   (cerror "continue" "after second pass")

	       (compile3-rule 
		 compiled-antecedent-2 compiled-consequent-2 
		 focus-name? rule-keyword))))
	  
;	     (cerror "continue" "after third pass")
	  
	  (when (not (eq context-for-this-focus-local-name bad-rule))
	    (setq 
	      multiple-context-compilations
	      (nconc 
		multiple-context-compilations
		(phrase-list
		  (phrase-cons
		    (cond
		      ((not chaining-category?)
		       focus-name?)
		      (t			; (eq chaining-category? 'both)
		       (if (eq focus-name? 
			       focus-local-name-for-rule-compilation?)
			   focus-name?
			   (phrase-list focus-name?  
					focus-local-name-for-rule-compilation?))))
		    context-for-this-focus-local-name)))))
	  
	  (reset-compilation-state)
	  ;; Have to reset compilation state for multiple compilations.
	  
	      while focus-local-name-continuation?
	      finally
		(progn
		  (reclaim-all-compilation-structures)
		  (return
		    (progn
		      (if multiple-context-compilations
			  (if (null (cdr multiple-context-compilations))
			      (let* ((only-multiple-compilation
				       (car multiple-context-compilations))
				     (focus-spec (car only-multiple-compilation)))
				(if (consp focus-spec)
				    (if (eq (first focus-spec)	; focus-role-name
					    (third focus-spec))	; focus-local-name
					(setf (car only-multiple-compilation)
					      (first focus-spec))))
				;; If there is only one compilation, chaining information
				;; can be omitted.  Thus, if the focus role name and
				;; focus local name are the same in this case, 
				;; the focus spec can be reduced to just the focus role name
				;; rather than the triple.  Note that if the focus local name
				;; is not the focus role name, the triple must be kept so 
				;; that the focus local name, which is used in the rule,
				;; will be bound on the alist.
				)
			      (set-multiple-compilations rule)))
		      (cond
			((and (null multiple-context-compilations)
			      (null body-of-rule))
			 ;; Body-of-rule will always be t for focus compilations if
			 ;; there is no problem.  For general compilation, body-of-rule
			 ;; will be the body which can't be nil.
			 (post-compiler-warning-note)
			 (if fatal-focus-error-info-for-all-compilations
			     (handle-fatal-focus-errors focus-name?))
			 nil)
			(t			; if no problems
			 (cond
			   ((null focus-name?)	; if general compilation
			    (phrase-list body-of-rule (car multiple-context-compilations)))
			   (t			; if focus compilation
			    (or multiple-context-compilations
				(phrase-list nil))))))))))
	))))

;; When compiling for focus, the rule body is really of no interest.
;; Nevertheless, most of the work for deriving the rule body must be done when
;; compiling for focus so it is currently always returned by compile3-rule.

;; Consider preventing parsing and putting up a "bad-phrase" message instead of
;; frame notes, at least for certain errors.
                                                                                


(defun reset-compilation-state ()
  (setq list-of-known-names nil
	names-used-for-more-than-one-item nil
	focus-local-names-for-focus-role-name nil
	local-name-errors nil
	attribute-name-errors nil
	top-level-reference-tree nil
	pattern-checking-inverse-references nil
	fatal-focus-error-info? nil
	context-iteration-forms nil
	non-context-top-level-binding-forms nil
	role-names-and-local-names-for-runtime-items nil
	alist-of-local-names-and-role-names nil
	local-names-not-associated-with-roles nil
	compilation-local-name-symbol-counter 1
	compilation-local-name-listed-next-symbol
	compilation-local-name-symbol-supply
	number-of-no-binds 0)
  (reclaim-all-compilation-structures))

;; Resetting compilation state involves resetting dynamic variables which hold the
;; state.  Reclaim-all-compilation-structures is not necessary, but is done for
;; the (very rare) case where there are a large number of multiple contexts, so as
;; not to allocate too much memory in a single rule compile.



(defun compile-consequent (consequent-expression compile-function)
  (phrase-cons (car consequent-expression)
	       (loop for expression 
			 in (cdr consequent-expression)
		     collecting (funcall-symbol compile-function expression)
			 using phrase-cons)))




;;; If rule-translation has explicit iteration forms, 
;;; filter-explicit-iteration-forms puts the designations in 
;;; designations-from-explicit-iteration-forms and returns only the body
;;; of the rule translation;  the iteration forms are stripped out.

(defun filter-explicit-iteration-forms (rule-translation)
  (cond 
    ((and (consp rule-translation)
	  (eq (first rule-translation) 'for))
     (setq source-designations-from-explicit-iteration-forms
	   (nconc source-designations-from-explicit-iteration-forms
		  (phrase-list (second rule-translation))))
     (filter-explicit-iteration-forms (third rule-translation)))
    (t rule-translation)))




;;; Inverse-reference-structure-is-global-end? checks if a reference-structure
;;; is a global end reference structure.  The first reference structure in
;;; the inverse reference path always has focus-range in its local-name-provided slot.
;;; The last reference structure in the inverse reference-path always has 
;;; either global-domain or a symbol designating a kb entity in its domain-name-needed
;;; slot.  If the domain-name-needed is global-domain (if the reference structure is
;;; a global end reference structure), then the reference structure is often
;;; treated specially.  Inverse-reference-structure-is-global-end? is used to
;;; test for this case.  

(defun inverse-reference-structure-is-global-end? (reference-structure)
  (eq (domain-name-needed reference-structure) global-domain))

(declare-forward-reference get-copy-of-reference-structure-in-highest-level-reference-tree
			   function)


;;; Insert-wrapper-references-for-left-side-of-formula will wrap the binding
;;; form for the attribute of the formula if it is referred to in the right side
;;; of the formula.  In addition, if a local name is used for the class name of
;;; the formula, a let binding form is wrapped around the expression which binds
;;; the local name to the focus name.  Note that this is currently the only case
;;; where a "let" form is used to simply bind one name to the value of another
;;; name.  Ex.  (let ((foo1 foo)) ...  In all other cases, the scope is not just
;;; a name.  Ex.  (let ((foo1 (the foo bar)) ...

(defun insert-wrapper-references-for-left-side-of-formula (expression)
  (let* ((root-reference-is-global-symbol?
	   (reference-structure-for-global-symbol-p
	     wrapper-references-for-left-side-of-formula?))
	 (wrapper-references-to-use?
	   (if root-reference-is-global-symbol?
	       (car (reference-structures-needing-provided-local-name 
		      wrapper-references-for-left-side-of-formula?))
	       wrapper-references-for-left-side-of-formula?)))
    (when wrapper-references-to-use?
      (if (reference-structure-provides-external-references?
	    wrapper-references-to-use?)
	  (insert-forward-wrapper-references
	    expression wrapper-references-to-use?))
      (when (and (not root-reference-is-global-symbol?)
		 (or (not (eq (domain-name-needed 
				wrapper-references-to-use?)
			      focus-name-for-rule-or-formula-compilation))))
	(let ((for-structure
		(make-compilation-reclaimable-for-structure)))
	  (setf (scope for-structure)
		(phrase-cons 
		  nil
		  (phrase-cons 
		    (domain-name-needed wrapper-references-to-use?)
		    (phrase-cons
		      focus-name-for-rule-or-formula-compilation nil))))
	  (setf (body for-structure)
		(compiled-specific-expression expression)
		(compiled-specific-expression expression)
		for-structure))))))

(defun insert-forward-wrapper-references
       (expression wrapper-reference)
  (multiple-value-bind
    (iteration-forms-to-be-inserted innermost-iteration-form)
      ;; make iteration forms
      (loop with next-reference-structure = wrapper-reference
	    with previous-for-structure = nil
	    with outermost-for-structure = nil
	    with first-time? = t
	    as new-for-structure
	       = (make-for-structure-given-reference-structure
		   next-reference-structure)
	    do
	(if (and first-time? new-for-structure)
	    (setq outermost-for-structure new-for-structure
		  first-time? nil))
	(if previous-for-structure
	    (setf (body previous-for-structure)
		  new-for-structure))
	(when (null (reference-structures-needing-provided-local-name 
		      next-reference-structure))
	  (return (values outermost-for-structure new-for-structure)))
	(setq previous-for-structure new-for-structure)
	(setq next-reference-structure
	      (car (reference-structures-needing-provided-local-name 
		     next-reference-structure)))
	(when (not (reference-structure-provides-external-references?
		     next-reference-structure))
	  (return (values outermost-for-structure new-for-structure))))
    (if innermost-iteration-form
	(setf (body innermost-iteration-form)
	      (compiled-specific-expression expression)
	      (compiled-specific-expression expression)
	      iteration-forms-to-be-inserted))))



;;;; Expression Compilation

;;; Compile-expression takes as arguments an expression and a list
;;; of focus names made up of gensym conses.  The list of focus names
;;; will be reclaimed.  Compile-expression is
;;; much simpler than compile-if-then-rule because there is only
;;; one expression (as opposed to an antecedent-expression and a
;;; consequent-expression) and because there should be no inverse
;;; references.  

;;; If the compile fails,
;;; nil is returned, a brief message is put up using notify user,
;;; and a detailed explanation of the error is put in the frame-notes
;;; of the expression-frame.  The expression-frame is passed in as the 
;;; third argument for
;;; this purpose.

;;; If the expression being compiled is a generic-formula or 
;;; generic-simulation-formula, the left side of the formula is passed
;;; as left-side-of-formula? (see compile-generic-formula and 
;;; compile-generic-simulation-formula).  Left-side-of-formula? is
;;; an expression of the form (THE attribute-name OF ANY class).
;;; Although this expression isn't directly used in the compiled 
;;; right side of the formula, it does allow wrapping a "let" form
;;; around the right side of the formula so that the attribute-name
;;; can be referred to directly in the right side of the formula.
;;; Thus it is possible to say in a generic simulation formula:
;;; "the foo of any bar = the foo + 5"
;;; rather than having to say
;;; "the foo of any bar = the foo of the bar + 5".
;;; The "let" form is only wrapped if it is needed so it won't be 
;;; inefficient if the right side doesn't mention the attribute 
;;; directly as in the following examples:
;;; "the foo of any bar = the foo of the bar + 5".
;;; "the foo of any bar = the x of the bar"
;; (see also compile1-expression-top and 
;; insert-wrapper-references-for-left-side-of-formula.

(defun-allowing-unwind compile-expression 
    (expression left-side-of-formula? focus-names)
  (with-updates-to-representations-supressed 
      (*current-computation-frame* 'frame-status-and-notes)
    (with-interned-compilation-local-name-symbols
      (with-compiler-error-reporting
	(with-compilation-bindings
	    nil
	    ((compiled-expression-1 nil)
	     (compiled-expression-2 nil)
	     (compiled-expression-3 nil)
	     (wrapper-references-for-left-side-of-formula? nil)
	     (compiling-expression-p t))
	  
	  (delete-all-frame-notes-for-rule-or-expression nil)
	  
	  (if left-side-of-formula?		; if compiling generic formula
	      (setq focus-name-for-rule-or-formula-compilation
		    (car focus-names)))
	  (setq compiled-expression-1
		(compile1-expression-top expression nil
					 left-side-of-formula? focus-names nil))
	  (prog1
	      (cond
		((first-pass-problems-with-expression-compile? compiled-expression-1)
		 (post-compiler-warning-note)
		 nil)
		((and (not focus-names)
		      (not (reference-paths-generic-p top-level-reference-tree)))
		 ;; If expression is not generic, it doesn't have to be compiled
		 ;; so just return it.
		 expression)
		(t
		 ;; if generic and no errors, continue compilation
		 (setq compiled-expression-2
		       (compile2-expression-top compiled-expression-1))
		 (unless compiler-errors
		   (setq compiled-expression-3
			 (compile3-expression-top compiled-expression-2))

		   compiled-expression-3)))
	    (reclaim-all-compilation-structures)
	    (reclaim-gensym-list focus-names))
	  )))))

;; Note that phrase conses are not used for the list of focus names since
;; the call may be outside of this context of phrase conses.

;; The intermediate compilations are currently kept for debug purposes.
;; This should eventually be simplified.

;; It is assumed that there will be no inverse references for expression
;; compilation;  inverse references should only occur in rule compilation.
;; If inverse references occur with multiple focus names, problems could
;; result since this violates the idea of one inverse reference path.
;; Thus, the error checking after the first pass will reject the compilation
;; if there are any inverse references.  If there will ever be any need for
;; inverse references in expression compilation (which I doubt), then this 
;; restriction can be lifted.



;;;; Compilation Error Checking

;;; The frame note types for compilation error frame notes are given by the
;;; parameter list-of-compiler-frame-note-types.

;;; The particulars of all compiler frame notes are alists which have
;;; the focus name (or nil) as the key.  This is important only for if
;;; rule compilations since there is more than one.  For expression
;;; compilation, there is only one compilation and the key will always
;;; be nil.

;; Have to further test adding and deleting of frame notes specific to roles 
;; when there are some (when the general compilation of a rule succeeds but
;; a specific compilation fails).

;; Should we allow for compilations with focus names not even mentioned in
;; the rule or expression?

;; Besides adding frame notes, think about how frame status should change
;; if at all.  Talk to Lowell, Mike.



;;; List-of-compiler-frame-note-types and list-of-bad-status-compiler-frame-
;;; note-types are maintained for the benefit of delete-all-frame-notes-for-
;;; rule-or-expression so that compiler frame notes can be deleted.  Note that
;;; obsolete compiler errors are still defined so that they will still be found
;;; by delete-all-frame-notes-for-rule-or-expression if they exist in any kbs.

(defvar list-of-compiler-frame-note-types nil)



;;; If a rule or expression has a frame note whose type is one of the ones in
;;; list-of-bad-status-compiler-frame-note-types, then the frame status must be
;;; bad.  This is useful for slot putters such as the one for generic
;;; simulation formulas.

(defvar list-of-bad-status-compiler-frame-note-types nil)



(defmacro define-compiler-error ((type-of-note bad-status?) &body forms)
  `(progn
     (pushnew ',type-of-note list-of-compiler-frame-note-types)
     ,@(when bad-status?
	 `((pushnew ',type-of-note
		    list-of-bad-status-compiler-frame-note-types)))
     (def-frame-note-writer ,type-of-note (particulars frame)
       ,@forms)))


(define-compiler-error (illegal-attribute t)
  (declare (ignore frame))
  (loop as (attribute . rest-of-illegal-attributes)
	   = particulars
		       then rest-of-illegal-attributes
	do
    (twrite-string "the attribute ")
    (twrite attribute)
    (if (null rest-of-illegal-attributes)
	(return
	  (twrite-string
	    (if (null (cdr particulars))
		" is a G2 internal attribute which may not be referenced directly "
		" are G2 internal attributes which may not be referenced directly "))))
    (twrite-string
      (cond
	((cdr rest-of-illegal-attributes) ", ")
	((cddr particulars) ", and ")
	(t " and ")))))

(define-compiler-error 
  (root-reference-role-name-same-as-previously-specified-local-name t)
  (declare (ignore frame))
  (loop as (local-name . rest-of-local-names)
	   = particulars
		       then rest-of-local-names
	do
    (twrite-string "the local name ")
    (twrite local-name)
    (if (null rest-of-local-names)
	(return
	  (twrite-string
	    " should not be referred to using \"the\" ")))
    (twrite-string
      (cond
	((cdr rest-of-local-names) ", ")
	((cddr particulars) ", and ")
	(t " and ")))))

(define-compiler-error 
  (explicitly-specified-local-name-refers-to-more-than-one-item t)
  (declare (ignore frame))
  (loop as (local-name . rest-of-local-names)
	   = particulars
		       then rest-of-local-names
	do
    (twrite-string "the local name ")
    (twrite local-name)
    (if (null rest-of-local-names)
	(return
	  (twrite-string
	    (if (null (cdr particulars))
		" refers to more than one runtime item"	      
		" refer to more than one runtime item"))))
    (twrite-string
      (cond
	((cdr rest-of-local-names) ", ")
	((cddr particulars) ", and ")
	(t " and ")))))

(define-compiler-error (ambiguous-reference t)
  (declare (ignore frame))
  (loop as (role-name . rest-of-role-names)
	   = particulars
		      then rest-of-role-names
	do
    (twrite-string "the role name ")
    (twrite role-name)
    (if (null rest-of-role-names)
	(return
	  (twrite-string
	    (if (null (cdr particulars))
		" refers to more than one runtime item"	      
		" refer to more than one runtime item"))))
    (twrite-string
      (cond
	((cdr rest-of-role-names) ", ")
	((cddr particulars) ", and ")
	(t " and "))))
  (twrite-string " so references to ")
  (twrite (if (cdr particulars)
	      "them "
	      "it "))
  (twrite-string "are ambiguous ")
  (twrite-string
    "(please use local names to differentiate the different runtime items and refer to ")
  (twrite-string
    "one of these to clear up the ambiguity) "))

(define-compiler-error (role-and-kb-object-namespace-confusion t)
  (declare (ignore frame))
  (loop as (name . rest-of-names)
	   = particulars then rest-of-names
	do
    (twrite-string "the name ")
    (twrite name)
    (if (null rest-of-names)
	(return
	  (twrite-string
	    (if (null (cdr particulars))
		" is used to name both a role and a kb object"	      
		" are used to name both roles and kb objects"))))
    (twrite-string
      (cond
	((cdr rest-of-names) ", ")
	((cddr particulars) ", and ")
	(t " and "))))
  (twrite-string
    " (please use local names to differentiate)"))

;; This is somewhat similar to the frame note writer for ambiguous reference so
;; consider abstracting some code!


(define-compiler-error (local-name-and-internal-type-namespace-confusion t)
  (declare (ignore frame))
  (loop as (name . rest-of-names)
 	   = particulars then rest-of-names
 	do
    (twrite-string "the name ")
    (twrite name)
    (if (null rest-of-names)
 	(return
 	  (twrite-string
 	    (if (null (cdr particulars))
 		" is used to name a role, but is a reserved word"	      
 		" are used to name roles, but are reserved words"))))
    (twrite-string
      (cond
 	((cdr rest-of-names) ", ")
 	((cddr particulars) ", and ")
	(t " and "))))
  (twrite-string
    " (please use other names)"))


(define-compiler-error (illegal-reference-from-an-every-quantifier t)
  (declare (ignore particulars frame))
  (twrite-string 
    "the quantifier \"every\" can not supply references outside its immediately enclosing logical expression"))
  

(define-compiler-error (illegal-quantifier-in-rule-consequent t)
  (declare (ignore particulars frame))
  (twrite-string 
    "the quantifier \"any\" is not allowed in the designation of an action"))


(define-compiler-error (illegal-reference-outside-action t)
  (declare (ignore particulars frame))
  (twrite-string 
    "designations inside an action can not supply references outside the action"))

(define-compiler-error (illegal-reference-outside-create-action t)
  (declare (ignore particulars frame))
  (twrite-string 
    "the local name of a create action can not be referenced in other actions unless the actions are in order"))

(define-compiler-error (too-many-delete-actions t)
  (declare (ignore particulars frame))
  (twrite-string 
    "only one delete action is allowed if the actions are simultaneous"))

(define-compiler-error (illegal-reference-outside-not t)
  (declare (ignore particulars frame))
  (twrite-string 
    "designations inside a not expression can not supply references outside the not"))

(define-compiler-error (illegal-reference-outside-expression t)
  (declare (ignore frame))
  (loop for operator in particulars do
    (let ((indefinite-article 'a)
	  (quantifier-or-aggregator?
	    (cond
	      ((quantifier-p operator) 'quantifier)
	      ((aggregator-p operator) 'aggregator))))
      (case operator
	(there-exists-literal
	 (setq operator 'there-exists))
	(for-every-literal
	 (setq operator 'for-every))
	(aggregated-average
	 (setq operator 'average
	       indefinite-article 'an)))
      ;; The other operators are sum, product, maximum, minimum, count, and not.
      ;; These don't require any modification.
      (twrite-string 
	"designations inside ")
      (twrite indefinite-article)
      (twrite-string " ")
      (twrite operator)
      (case quantifier-or-aggregator?
	(quantifier
	 (twrite-string " quantifier can not supply references outside the quantifier"))
	(aggregator
	 (twrite-string " aggregator can not supply references outside the aggregator"))
	(t
	 (twrite-string " expression can not supply references outside the expression"))))))

(define-compiler-error (illegal-reference-outside-there-exists t)
  (declare (ignore particulars frame))
  (twrite-string 
    "designations inside the logical expression of a there exists quantifier can not supply references outside the expression"))

(define-compiler-error
  (illegal-reference-outside-sub-expression-of-expression t)
  (declare (ignore frame))
  (loop for operator in particulars do
    (case operator
      (if-expression 
       (setq operator 'if))
      (or
       (setq operator 'or)))
    (twrite-string 
      "designations inside sub-expressions of an ")
    (twrite operator)
    (twrite-string " expression can not supply references outside the sub-expression")))

;; The frame-note-type illegal-reference-outside-sub-expression-of-expression
;; is obsolete (4/19/89).



(define-compiler-error (illegal-reference-outside-antecedent-clause t)
  (declare (ignore particulars frame)))

;; The frame-note-type illegal-reference-outside-antecedent-clause is obsolete.



(define-compiler-error (fatal-focus-error t)
  (declare (ignore frame))
  (loop for rest-of-role-names-and-fatal-focus-errors
	    on particulars
	as role-name-and-fatal-focus-error
	   = (car rest-of-role-names-and-fatal-focus-errors)
	as role-name? = (car role-name-and-fatal-focus-error)
	as fatal-focus-error = (second role-name-and-fatal-focus-error)
	as last-time? = (null (cdr rest-of-role-names-and-fatal-focus-errors))
	do
    (twrite-string "because ")
    (twrite role-name?)
    (write-fatal-focus-error fatal-focus-error)
    (twrite-string ", it is not allowed as a focal class")
    (if (not last-time?)
	(twrite-string ";  "))))

;; Fatal focus errors never happen with the general compilation, only with
;; focus compilations and only in rules.



(declare-forward-reference print-role-or-role-and-designation function)
(declare-forward-reference print-role function)

(defun write-fatal-focus-error (fatal-focus-error)
  (cond
    ((symbolp fatal-focus-error)
     (twrite-string " is inside ")
     (case fatal-focus-error
       ((break focus deactivate set move rotate create delete
	       create-explanation create-connection create-by-cloning)
	(twrite-string "a ")
	(twrite fatal-focus-error)
	(twrite-string " action "))
       ((conclude conclude-not conclude-has-no-current-value
		  conclude-has-no-value change-icon-color)
	(twrite-string "the expression of a ")
	(twrite-string " conclude action "))
       ((invoke inform activate)
	(twrite-string "an ")
	(twrite fatal-focus-error)
	(twrite-string " action "))
       (set-position
	(twrite-string "a move action "))
       (set-heading
	(twrite-string "a rotate action "))))
    ((eq (car fatal-focus-error) 'non-invertible-role)
     (twrite-string " depends on ")
     (twrite-string "the non-invertible expression \"")
     (if (third fatal-focus-error)
	 (print-role-or-role-and-designation
	   (second fatal-focus-error)
	   nil
	   (cddr fatal-focus-error))
	 (print-role
	   (second fatal-focus-error)))
     (twrite-string "\""))))




;;; The compiler error type `focus-class-compilation-failed' is used to register
;;; problems compiling focal classes.  This note is registered from within the
;;; slot value compiler function for rule in the module RULES.

(define-compiler-error (focus-class-compilation-failed t)
  (declare (ignore frame))
  (tformat
    "the focal class~a "
    (if (cdr particulars) "es" ""))
  (write-list-in-chicago-style particulars "and")
  (tformat
    " could not be compiled, since ~a not mentioned in the rule"
    (if (cdr particulars) "they are" "it is")))

(declare-forward-reference write-list-in-chicago-style function)

(define-compiler-error (illegal-quantifier-within-nth-element-role t)
  (declare (ignore frame))
  (loop for rest-of-roles-and-nth-element-expressions
	    on particulars
	as (role nth-element-role . domain-list) 
	   = (car rest-of-roles-and-nth-element-expressions)
	as last-time? = (null (cdr rest-of-roles-and-nth-element-expressions))
	do
    (twrite-string "the quantifier \"any\" in the expression \"any ")
    (print-role role)
    (twrite-string "\" is not allowed because it depends on the nth-element expression \"")
    (print-role-or-role-and-designation nth-element-role nil domain-list)
    (twrite-string "\"")
    (if (not last-time?)
	(twrite-string ";  "))))

(define-compiler-error (circularity-in-nth-element-index t)
  (declare (ignore frame))
  (loop for rest-of-info on particulars
	as (role nth-element-role . domain-list) = (car rest-of-info)
	as last-time? = (null (cdr rest-of-info))
	do
    (tformat "the reference to \"~a\" in the expression \" " role)
    (print-role-or-role-and-designation nth-element-role nil domain-list)
    (twrite-string "\" is not allowed because it depends on the result of \" ")
    (print-role-or-role-and-designation nth-element-role nil domain-list)
    (twrite-string "\" and is thus circular")
    (if (not last-time?)
	(twrite-string ";  "))))

(define-compiler-error (unknown-references t)
  (cond 
    ((of-class-p frame 'rule)
     (loop for rest-of-role-names-and-unknown-references 
	       on particulars
	   as role-name-and-unknown-references
	      = (car rest-of-role-names-and-unknown-references)
	   as role-name? = (car role-name-and-unknown-references)
	   as unknown-references = (second role-name-and-unknown-references)
	   as last-time? = (null (cdr rest-of-role-names-and-unknown-references))
	   do
       (cond
	 ((null role-name?)
	  (twrite-string "for the general compilation, "))
	 (t
	  (twrite-string "for compilation with focus on ")
	  (twrite role-name?)
	  (twrite-string ", ")))
       (write-unknown-references unknown-references)
       (if (not last-time?)
	   (twrite-string ";  ")))
     )
    (t
     (write-unknown-references
       (second (car particulars))))))

;; Have to check if rule or expression frame.  If frame is a rule, frame notes 
;; must be associated with the various compilations corresponding to different 
;; role names.  If frame is an expression, then there is only one compilation and
;; frame notes don't have to be associated with roles.


(defun write-unknown-references (list-of-unknown-references)
  (loop as (unknown-reference . rest-of-unknown-references)
	   = list-of-unknown-references
			      then rest-of-unknown-references
	do 
    (twrite-string "the reference ")
    (twrite unknown-reference)
    (if (null rest-of-unknown-references)
	(return
	  (twrite-string
	    (if (null (cdr list-of-unknown-references))
		" is unknown"
		" are unknown"))))
    (twrite-string
      (cond
	((cdr rest-of-unknown-references) ", ")
	((cddr list-of-unknown-references) ", and ")
	(t " and ")))))




(defun reference-paths-generic-p (reference-tree)
  (loop for reference-structure in reference-tree
	as needing-reference-structures
	   = (reference-structures-needing-provided-local-name
	       reference-structure)
	do
    (let ((role-name
	    (atomic-naming-element-of-role
	      (role-and-local-name reference-structure)))
	  (local-name
	    (local-name-provided reference-structure)))
      (if (or (implicit-iterator-p (quantifier reference-structure))
	      (eq (quantifier reference-structure) 'quantifier)
	      (cdr needing-reference-structures)
	      (eq (domain-name-needed reference-structure) needed-domain)
	      (not (eq role-name local-name)))
	  ;; if iteration or branching or local names
	  (return t)
	  (if (reference-paths-generic-p needing-reference-structures)
	      (return t))))))



(defun expression-has-inverse-references-beyond-focus-p
       (expression-for-compilation?)
  expression-for-compilation?
  nil
  ;; This should never happen.

;  (if (expression-for-compilation-p expression-for-compilation?)
;      (let ((inverse-references
;	      (inverse-references expression-for-compilation?)))
;	(if inverse-references
;	    (loop for focus-reference-structure in inverse-references
;		  do
;	      (if (reference-structures-needing-provided-local-name
;		    focus-reference-structure)
;		  (return t))))))
  )



(defmacro accumulate-compiler-errors (&body forms)
  `(let ((problem? nil))
     ,@(loop for form in forms 
	     collect
	       `(setf problem? (or ,form problem?)))
     problem?))



;;; First-pass-problems-with-rule-compile?  analyzes top-level-reference-tree and
;;; returns non-nil if there is a problem.  It basically calls more specific error
;;; checking functions.  Rule and focus-name?  are passed in as an argument so
;;; that frame notes can be put up.

(defun first-pass-problems-with-rule-compile? (focus-name?)
  (let ((problem? nil))
    (when (not focus-name?)
      (setf problem?
	    (accumulate-compiler-errors
	      (illegal-attribute?)
	      (local-name-error?)
	      (evaluation-value-type-used-to-name-kb-object?)
	      (role-name-used-to-name-kb-object?)
	      (unknown-references? top-level-reference-tree focus-name?)
	      (illegal-references-in-rule?)
	      (illegal-quantifier-in-rule-consequent?)
	      (illegal-quantifier-within-nth-element-role?))))
    (setf problem? (or (check-for-fatal-focus-error focus-name?)
		       problem?))))

;; The illegal-references? check need only be made for the general compilation.
;; If there is a problem with the general compilation, don't need to check for
;; specific compilations.

;; The local name error check must come first since if there are ambiguous
;; references, these must be caught first.  Not doing this could result
;; in unknown references messages.



(defun first-pass-problems-with-expression-compile? 
       (compiled-expression-1)
  (accumulate-compiler-errors
    (illegal-attribute?)
    (local-name-error?)
    (evaluation-value-type-used-to-name-kb-object?)
    (role-name-used-to-name-kb-object?)
    (if (and (expression-for-compilation-p compiled-expression-1)
	     (local-reference-finding-paths compiled-expression-1))
	(unknown-references? 
	  top-level-reference-tree
	  nil))
    (expression-has-inverse-references-beyond-focus-p 
      compiled-expression-1)
    (illegal-references-in-expression? compiled-expression-1)))



(defun illegal-attribute? ()
;  (loop for illegal-attribute in attribute-name-errors
;	do
;    (add-to-frame-note-particulars-list-if-necessary
;      illegal-attribute 'illegal-attribute *current-computation-frame*))
;  attribute-name-errors
  )

;; This is currently disabled due to the fact that it is now valid to change the
;; text of system slots.  To put this back in, it will be necessary for the
;; compiler to detect that it is in a "change the text of" context, something that
;; is probably not that difficult.  Currently, however, non-text accessing and
;; setting of system slots is flagged as an error at runtime rather than at
;; compile time.  - agh 10/21/91



(defun local-name-error? ()
  (loop for error-entry in local-name-errors
	do
    (add-to-frame-note-particulars-list-if-necessary
      (cdr error-entry) (car error-entry) *current-computation-frame*))
  local-name-errors)


;;; `Evaluation-value-type-used-to-name-kb-object?' was added to catch
;;; the case where the internal representation of local variables in a parse is
;;; conflated with the representation of evaluation values, i.e. both use
;;; dotted pairs with a symbol in the cdr. This fixes bug HQ-3080706.

(defun evaluation-value-type-used-to-name-kb-object? ()
  (loop	with problem? = nil
	for (name . ignore) in alist-of-local-names-and-role-names
	when (get-evaluation-types name defined-evaluation-value-types)
	  do
	    (add-to-frame-note-particulars-list-if-necessary
	      name
	      'local-name-and-internal-type-namespace-confusion
	      *current-computation-frame*)
	    (setq problem? t)
	finally (return problem?)))

;; Note: The first version of this routine did this:
;;    for reference-structure in top-level-reference-tree
;;    for name = (local-name-provided reference-structure)
;; But that wasn't sufficient to get some instances of a local name.
;; I don't yet know how these accumulating structures are managed so
;; I'm still not sure whether we have the needed coverage. ddm 2/24/00


(defun role-name-used-to-name-kb-object? ()
  (loop with kb-object-name = nil
	with problem? = nil
	for reference-structure in top-level-reference-tree
	do
    (when (and (reference-structure-for-global-symbol-p reference-structure)
	       (let ((role-and-local-name-entry?
		       (assq (setq kb-object-name
				   (local-name-provided reference-structure))
			     role-names-and-local-names-for-runtime-items)))
		 (and role-and-local-name-entry?
		      ;; Problem unless user specifies different local name.
		      (eq (car role-and-local-name-entry?)
			  (cdr role-and-local-name-entry?)))))
      (add-to-frame-note-particulars-list-if-necessary
	kb-object-name
	'role-and-kb-object-namespace-confusion
	*current-computation-frame*)
      (setq problem? t))
	finally (return problem?)))



(defun check-for-fatal-focus-error (focus-name?)
  (accumulate-compiler-errors
    (check-for-focus-inside-invertible-roles focus-name?)
    (if fatal-focus-error-info?
	(setq fatal-focus-error-info-for-all-compilations
	      (nconc fatal-focus-error-info-for-all-compilations
		     (phrase-list fatal-focus-error-info?))))))

(declare-forward-reference invertible-role-p function)

(defun check-for-focus-inside-invertible-roles (focus-name?)
  (declare (ignore focus-name?))
  (loop with problem? = nil
	as reference-structure 
	   = (if pattern-checking-inverse-references
		 (car (reference-structures-needing-provided-local-name
			pattern-checking-inverse-references)))  ; skip focus reference structure
	then next-reference-structure  
	until (or (null reference-structure)
		  (inverse-reference-structure-is-global-end? 
		    reference-structure))
	as next-reference-structure
	   = (car (reference-structures-needing-provided-local-name
		    reference-structure))
	as role = (simple-role-of-role 
		    (role-and-local-name reference-structure)) 
	do
    (when (not (invertible-role-p role))
      (setq fatal-focus-error-info-for-all-compilations
	    (nconc fatal-focus-error-info-for-all-compilations
		   (phrase-list
		     (nconc
		       (phrase-list 'non-invertible-role
				    (if (symbolp role)
					role
					(copy-list-using-phrase-conses role)))
		       (let ((embedded-expression?
			       (embedded-expression-original-parse?
				 reference-structure)))
			 (when embedded-expression?
			   (phrase-list
			     (domain-name-needed reference-structure)
			     embedded-expression?))))))
	    problem? t))
	finally (return problem?)))

(defun handle-fatal-focus-errors (focus-name?)
  (loop for error-info in fatal-focus-error-info-for-all-compilations
	do
    (add-to-frame-note-particulars-list-if-necessary
      (slot-value-list 
	focus-name?
	(if (symbolp error-info)
	    error-info
	    (copy-for-slot-value error-info)))
      'fatal-focus-error *current-computation-frame*)))

;; Fatal focus errors happen only with rules, not expressions.



;;; Special-globally-known-references contains references such as "operator" 
;;; that are exceptions to the rules for known references.  Thus, unknown-references?
;;; will not flag an error for references that appear to be unknown but are in
;;; special-globally-known-references.  This allows for "inform the operator that ..."
;;; without operator being bound previously in the rule.

(def-system-variable special-globally-known-references compile1
  '(operator))



;;; Unknown-references? returns non-nil if there are unknown references.

(defvar unknown-references)

(defun unknown-references? (reference-tree focus-name?)
  (let ((unknown-references nil))
    (check-for-problem-in-tree
      reference-tree 'reference-to-item-or-datum?)
    (loop for root-reference-structure in reference-tree
	  do
      (if (and (eq (domain-name-needed root-reference-structure) needed-domain)
	       (not (memq (local-name-provided root-reference-structure)
			  special-globally-known-references)))
	  (setq unknown-references
		(nconc unknown-references
		       (slot-value-list 
			 (local-name-provided root-reference-structure)))))
		finally (cond
			  (unknown-references
			   (add-to-frame-note-particulars-list-if-necessary
			     (slot-value-list focus-name? unknown-references)
                   'unknown-references *current-computation-frame*)
			   (return unknown-references))))))

;; Note that the list of unknown-references is made up of frame-note conses.
;; These are automatically reclaimed by delete-frame-note-if-any.



(defun reference-to-item-or-datum? (reference-structure)
  (let ((role (simple-role-of-role (role-and-local-name reference-structure))))
    (cond
      ((and (consp role)
	    (eq (car role) 'nth-element)
	    (cdr (reference-structures-needing-provided-local-name
		   reference-structure)))
       (setq unknown-references
	     (nconc unknown-references 
		    (slot-value-list
		      (local-name-provided reference-structure)))))
      (t
       (check-for-problem-in-tree
	 reference-structure 'reference-to-item-or-datum?)))))



;;; Illegal-quantifier-in-rule-consequent? returns t if an "any" quantifier
;;; appears in the reference tree for the consequent.

(defun illegal-quantifier-in-rule-consequent? ()
  (when
    (loop for consequent-action 
	      in (cdr compiled-consequent-1)
	  thereis (illegal-quantifier-in-action? consequent-action))
    ;; put up frame note
    (add-frame-note
     'illegal-quantifier-in-rule-consequent *current-computation-frame*
      nil t nil)))


;;; Illegal-quantifier-in-action? checks designations of actions.  Iteration forms
;;; for designations of actions are wrapped around the action itself and become
;;; action iterations rather than expression iterations.  The reference structures
;;; for the designations are checked to make sure that the quantifier "any"
;;; doesn't appear in them.

(defun illegal-quantifier-in-action? (action)
  (when (expression-for-compilation-p action)
    (let ((compiled-specific-expression
	    (compiled-specific-expression action)))
      (case (car compiled-specific-expression)
	;; We don't currently need to add invoke-with-wait here because it's
	;; not allowed for rules. -dkuznick, 7/20/05 
	((invoke break)  ; these don't have designations
	 nil)
	(t
	 ;; If the action is conclude, focus, activate,
	 ;; deactivate, inform, set, move, set-position, rotate, or set-heading,
	 ;; the designation is the second of the action.
	 
	 (let ((designation (second compiled-specific-expression)))
	   (when (and (expression-for-compilation-p designation)
		      (local-reference-finding-paths designation))
	     (illegal-any-quantifier-in-tree?
	       (car (local-reference-finding-paths designation))))))))))



(defun illegal-quantifier-within-nth-element-role? ()
  (check-for-problem-in-tree 
    top-level-reference-tree
    'illegal-quantifier-within-nth-element-role-1))

(defvar role-and-domains-for-nth-element-expression)

(defun illegal-quantifier-within-nth-element-role-1
       (reference-structure)
  (let ((simple-role (simple-role-of-role 
		       (role-and-local-name reference-structure))))
    (if (and (consp simple-role)
	     (eq (car simple-role) 'nth-element))
	(let ((role-and-domains-for-nth-element-expression
		(phrase-list
		  (simple-role-of-role 
		    (role-and-local-name reference-structure))
		  (domain-name-needed reference-structure)
		  (embedded-expression-original-parse? reference-structure))))
	  (illegal-any-quantifier-in-tree? reference-structure))
	(check-for-problem-in-tree 
	  reference-structure
	  'illegal-quantifier-within-nth-element-role-1))))

(defun illegal-any-quantifier-in-tree? (reference-structure)
  (cond
    ((eq (quantifier reference-structure) 'any)
     (add-to-frame-note-particulars-list-if-necessary
       (slot-value-cons
	 (copy-for-slot-value
	   (simple-role-of-role
	     (role-and-local-name reference-structure)))
	 (copy-for-slot-value role-and-domains-for-nth-element-expression))
       'illegal-quantifier-within-nth-element-role
      *current-computation-frame*))
    (t
     (check-for-problem-in-tree
       reference-structure 'illegal-any-quantifier-in-tree?))))

(defun check-for-problem-in-tree 
       (reference-structure-or-tree function-to-do-check)
  (loop with problem? = nil
	for reference-structure 
	    in (if (reference-structure-p reference-structure-or-tree)
		   (reference-structures-needing-provided-local-name
		     reference-structure-or-tree)
		   reference-structure-or-tree)
	do 
    (setf problem? 
	  (or (funcall function-to-do-check reference-structure)
	      problem?))
	finally (return problem?)))



(defun circularity-in-nth-element-index? (compiled-expression-1)
  (when (expression-for-compilation-p compiled-expression-1)
    (loop with problem? = nil
	  for designation in (designations-for-expression compiled-expression-1)
	  do
      (when (cdr (designations-for-expression designation))    ; has embedded expression
	(loop for reference-structure in (local-reference-finding-paths designation)
	      as embedded-expression? = (embedded-expression? reference-structure)
	      do 
	  (when (reference-structure-p embedded-expression?)
	    (loop for reference-structure-in-embedded-expression
		      in (local-reference-finding-paths embedded-expression?)
		  do
	      (when (reference-structure-providing-needed-domain-name
		      (get-copy-of-reference-structure-in-highest-level-reference-tree
			reference-structure-in-embedded-expression))
		(let ((reference-structure-for-nth-element-role
			(car (reference-structures-needing-provided-local-name
			       reference-structure))))
		  (add-to-frame-note-particulars-list-if-necessary
		    (copy-for-slot-value
		      (phrase-list
			(local-name-provided 
			  reference-structure-in-embedded-expression)
			(simple-role-of-role
			  (role-and-local-name 
			    reference-structure-for-nth-element-role))
			(local-name-provided reference-structure)
			(embedded-expression-original-parse?
			  reference-structure-for-nth-element-role)))
		    'circularity-in-nth-element-index
		    *current-computation-frame*))
		(setf problem? t))))))
	  finally (return problem?))))



;;; Illegal-references-in-rule? returns non-nil if there are illegal references.
;;; Rule is passed in as an argument so that frame notes
;;; can be put up.  

(defun illegal-references-in-rule? ()
  (accumulate-compiler-errors
    (illegal-references-in-rule-antecedent? 
      compiled-antecedent-1)
    (illegal-references-in-rule-consequent?
      compiled-consequent-1)))

;; The check to make sure that "every" quantifiers don't supply references
;; outside of the designations in which they appear is performed in
;; combine-reference-finding-paths-rec and is caught by unknown-references?
;; (see note above).


(defun illegal-references-in-rule-antecedent?
       (compiled-antecedent-1)
  (or
    (illegal-references-in-expression? compiled-antecedent-1)))


(defun illegal-references-in-rule-consequent? (compiled-consequent-1)
  (let ((simultaneous? (eq (car compiled-consequent-1) 'simultaneously)))
    (accumulate-compiler-errors
      (when simultaneous?
	(more-than-one-delete-action? compiled-consequent-1))
      (loop with problem? = nil
	    for consequent-expression 
		in (cdr compiled-consequent-1)
	    do
	(setf problem?
	      (or (accumulate-compiler-errors
		    (illegal-references-in-expression? consequent-expression)
		    (illegal-reference-outside-action?
		      consequent-expression simultaneous?))
		  problem?))
	    finally (return problem?)))))


(defun more-than-one-delete-action? (compiled-consequent-1)
  (loop with delete-action-count = 0
	for consequent-expression 
	    in (cdr compiled-consequent-1)
	do (setq delete-action-count
		 (+f delete-action-count
		     (if (eq (car (compiled-specific-expression
				    consequent-expression))
			     'delete)
			 1 0)))
	   (when (>f delete-action-count 1)
	     (add-frame-note
	       'too-many-delete-actions *current-computation-frame* nil t nil)
	     (return t))))

;; This check will only be necessary in 2.0 Alpha! 
;; (Mike will advise)



(defun illegal-references-in-expression? (compiled-expression-1)
  (accumulate-compiler-errors
    (illegal-reference-from-an-every-quantifier? compiled-expression-1)
    (illegal-reference-outside-expression? compiled-expression-1)
    (circularity-in-nth-element-index? compiled-expression-1)))



;;; Illegal-reference-from-an-every-quantifier? checks if an "every" quantifier of
;;; a designation supplies references outside of the immediately surrounding 
;;; logical expression of the designation (if any).  It also checks if an "every"
;;; quantifier supplies references outside the expression argument, which is 
;;; always the antecedent or a consequent.  This prevents an "every" in the antecedent
;;; supplying a reference to an action.
;; (see also note on combine-reference-finding-paths-rec)


(defun illegal-reference-from-an-every-quantifier? (expression)
  (let ((compiled-specific-expression?
	  (when (expression-for-compilation-p expression)
	    (compiled-specific-expression expression))))
    (cond 
      ((and compiled-specific-expression?  ; antecedent or action
	    (loop for root-reference-structure
		      in (local-reference-finding-paths expression)
		  thereis
		    (illegal-every-quantifier-in-reference-tree?
		      root-reference-structure)))
       (add-frame-note
	 'illegal-reference-from-an-every-quantifier
	 *current-computation-frame* nil t nil)
       t)
      (t 
       (illegal-reference-from-an-every-quantifier-rec? expression)))))


(defun illegal-reference-from-an-every-quantifier-rec? (expression)
  (let ((compiled-specific-expression-to-investigate?
	  (when (expression-for-compilation-p expression)
	    (compiled-specific-expression expression))))
    (when 
      (and compiled-specific-expression-to-investigate?
	   (consp compiled-specific-expression-to-investigate?)
	   (logical-operator-p (car compiled-specific-expression-to-investigate?))
	   (loop for sub-expression
		     in (cdr compiled-specific-expression-to-investigate?)
		 thereis
		   (let ((compiled-specific-expression-for-sub-expression
			   (when (expression-for-compilation-p sub-expression)
			     (compiled-specific-expression sub-expression))))
		     (when
		       compiled-specific-expression-for-sub-expression
		       (cond 
			 ((or (not (consp compiled-specific-expression-for-sub-expression))
			      (not (logical-operator-p 
				     (car compiled-specific-expression-for-sub-expression))))
			  (loop for root-reference-structure
				    in (local-reference-finding-paths sub-expression)
				thereis
				  (illegal-every-quantifier-in-reference-tree?
				    root-reference-structure)))
			 (t
			  (illegal-reference-from-an-every-quantifier-rec?
			    sub-expression)))))))
      (add-frame-note
	'illegal-reference-from-an-every-quantifier
	*current-computation-frame* nil t nil)
      t)))



(defun illegal-every-quantifier-in-reference-tree? (reference-structure)
  (cond
    ((eq (quantifier reference-structure) 'every)
     (reference-structure-provides-external-references? reference-structure))
    (t
     (check-for-problem-in-tree
       reference-structure 'illegal-every-quantifier-in-reference-tree?))))



(defun operator-to-check-for-illegal-reference-p (operator)
  (quantifier-or-aggregator-p operator))


(defun illegal-reference-outside-expression? (expression)
  (let ((compiled-specific-expression-to-investigate?
	  (when (expression-for-compilation-p expression)
	    (compiled-specific-expression expression))))
    (when (and compiled-specific-expression-to-investigate?
	       (consp compiled-specific-expression-to-investigate?))
      (let ((operator (car compiled-specific-expression-to-investigate?)))
	(cond
	  ((operator-to-check-for-illegal-reference-p operator)
	   (if (eq operator 'there-exists-literal)
	       (when
		 (expression-provides-external-references? 
		   (third compiled-specific-expression-to-investigate?))
		 (add-frame-note
		   'illegal-reference-outside-there-exists 
		   *current-computation-frame* nil t nil)
		 t)
	       (when
		 (expression-provides-external-references? expression)
		 (add-to-frame-note-particulars-list-if-necessary
		   operator
		   'illegal-reference-outside-expression
		   *current-computation-frame*)
		 t)))
	  (t
	   (loop for sub-expression 
		     in (cdr compiled-specific-expression-to-investigate?)
		 thereis (illegal-reference-outside-expression?
			   sub-expression))))))))

;; Since this test is made after the first pass and before the second,
;; expression should consist only of symbols, numbers, conses, and 
;; expressions for compilation.

;; Consider modifying reference-structures-equivalent?  to return the name
;; corresponding to the reference structure at which the trees are not
;; equivalent.  This would allow for improving the illegal reference outside
;; expression error message so that the name that is causing the problem could
;; be indicated (this is what the unknown references error message does)!



;;; Illegal-reference-outside-action? checks if the action provides 
;;; references (to another action).

(defun illegal-reference-outside-action?
       (action simultaneous?)
  (when (expression-for-compilation-p action)
    (let ((compiled-specific-expression
	    (compiled-specific-expression action)))
      (when (and compiled-specific-expression
		 (consp compiled-specific-expression))
	(when
	  (case (car compiled-specific-expression)
	    ((create create-by-cloning create-connection create-explanation)
	     (cond
	       ((and simultaneous?
		     (expression-provides-external-references?
		       (third compiled-specific-expression)))
		(add-frame-note
		  'illegal-reference-outside-create-action 
		  *current-computation-frame* nil t nil)
		(return-from illegal-reference-outside-action? t))
	       (t
		(expression-provides-external-references?
		  (second compiled-specific-expression)))))
	    (call-assignment-action
	       (cond
	       ((and simultaneous?
		     (expression-provides-external-references?
		       (second compiled-specific-expression)))
		(add-frame-note
		  'illegal-reference-outside-create-action 
		  *current-computation-frame* nil t nil)
		(return-from illegal-reference-outside-action? t))
	       (t
		(expression-provides-external-references?
		  (fourth compiled-specific-expression)))))
	    (t
	     (loop for root-reference-structure
		       in (local-reference-finding-paths action)
		   do 
	       (cond 
		 ((or (eq (local-name-provided root-reference-structure) 
			  focus-range)
		      (eq (domain-name-needed root-reference-structure) 
			  needed-domain))
		  (loop for sub-root-reference-structure
			    in (reference-structures-needing-provided-local-name
				 root-reference-structure)
			thereis (reference-structure-provides-external-references?
				  sub-root-reference-structure)))
		 (t 
		  (if (reference-structure-provides-external-references?
			root-reference-structure)
		      (return t)))))))
	  (add-frame-note
	    'illegal-reference-outside-action 
	    *current-computation-frame* nil t nil)
	  t)))))

;; The create action is currently the only action which can provide a binding
;; to other actions.

;; This is no longer true, the call-assignment-action can also provide a
;; binding to other actions.




(defun expression-provides-external-references? (expression)
  (when (expression-for-compilation-p expression)
    (loop for root-reference-structure
	      in (local-reference-finding-paths expression)
	  thereis (reference-structure-provides-external-references?
		    root-reference-structure))))


;;; Reference-structure-provides-external-references? is used by many of the
;;; error checking functions to check if a reference structure provides 
;;; external references outside its expression.

(defun reference-structure-provides-external-references? (reference-structure)
  (not (reference-structures-equivalent?
	 reference-structure
	 (get-copy-of-reference-structure-in-highest-level-reference-tree
	   reference-structure))))


;;; Reference-structures-equivalent? compares domain-name-needed,
;;; local-name-provided, role-and-local-name, and quantifier.  It also calls
;;; itself recursively for reference-structures-needing-provided-local-name
;;; for both reference structures.  Thus, the entire trees rather than
;;; just the reference structures are compared.  This function is
;;; useful for comparing reference structures at different levels in
;;; the "3-D" lattice of reference trees (see documentation for 
;;; copy-reference-structure.  Its main application is to check if
;;; some reference structure provides external references by comparing
;;; it to its corresponding reference structure in 
;;; top-level-reference-tree.

(defun reference-structures-equivalent?
       (reference-structure-1 reference-structure-2)
  (and
    (eq (domain-name-needed reference-structure-1)
	(domain-name-needed reference-structure-2))
    (eq (local-name-provided reference-structure-1)
	(local-name-provided reference-structure-2))
    (eq (role-and-local-name reference-structure-1)
	(role-and-local-name reference-structure-2))
    (eq (quantifier reference-structure-1)
	(quantifier reference-structure-2))
    (loop with rest-of-sub-reference-structures-1
	    = (reference-structures-needing-provided-local-name
		reference-structure-1)
	  with rest-of-sub-reference-structures-2
	    = (reference-structures-needing-provided-local-name
		reference-structure-2)
	  as sub-reference-structure-1 
	     = (car rest-of-sub-reference-structures-1)
	  as sub-reference-structure-2
	     = (car rest-of-sub-reference-structures-2)
	  while (and rest-of-sub-reference-structures-1
		     rest-of-sub-reference-structures-2)
	  do
      (if (not (reference-structures-equivalent?
		 sub-reference-structure-1 sub-reference-structure-2))
	  (return nil))
      (setq rest-of-sub-reference-structures-1
	    (cdr rest-of-sub-reference-structures-1)
	    rest-of-sub-reference-structures-2
	    (cdr rest-of-sub-reference-structures-2))
	  finally
	    (return (not (or rest-of-sub-reference-structures-1
			     rest-of-sub-reference-structures-2))))))



;;; Delete-all-frame-notes-for-rule-or-expression just calls delete-frame-note-if-any
;;; for each compiler frame note type possible for rules or expressions.

(defun-void delete-all-frame-notes-for-rule-or-expression
    (delete-only-from-component-particulars?)
  (let ((notes-to-delete
	  (gensym-cons 'compiler-errors list-of-compiler-frame-note-types)))
    (delete-frame-notes-of-types-in-list
      *current-computation-frame* notes-to-delete
      delete-only-from-component-particulars?)
    (reclaim-gensym-cons notes-to-delete)))

(defun delete-compiler-frame-notes-for-role (role-name)
  (loop for type-of-note in '(unknown-references fatal-focus-error)  ; extend this
	as frame-note-particulars
	   = (get-particulars-of-frame-note-if-any 
	       type-of-note *current-computation-frame*)
	as particular-to-delete 
	   = (assq role-name frame-note-particulars)
	do
    (delete-from-frame-note-particulars-list
      particular-to-delete
      type-of-note
      *current-computation-frame*)))

;; For now, frame is always a rule here.



(defun bad-status-compiler-frame-notes? (&optional frame)
  (let ((*current-computation-frame* (or frame *current-computation-frame*)))
    (if current-computation-component-particulars
	(bad-status-compiler-frame-notes-for-component-particulars?
	  *current-computation-frame* current-computation-component-particulars)
	(bad-status-compiler-frame-notes-1? 
	  (cdr (frame-status-and-notes *current-computation-frame*))))))

(defun bad-status-compiler-frame-notes-1? (frame-notes)
  (loop as (type-of-note nil . rest-of-plist) 
	   = frame-notes
			 then rest-of-plist
	do
    (when (memq type-of-note list-of-bad-status-compiler-frame-note-types)
      (return t))
	until (null rest-of-plist)))

(defun bad-status-compiler-frame-notes-for-component-particulars?
       (frame component-particulars)
  (bad-status-compiler-frame-notes-1?
    (cdr (second (get-entry-for-component-particulars
		   component-particulars frame)))))



;;;; Simulation Formula Compilation

;;; Compilation for simulation formulas is much simpler than compilation
;;; for rules for the following reasons:  
;;; (same reasons that expression compilation is simpler than rule compilation)
;;; 1.  The left side of the formula dictates the focal name (if any).
;;; Thus, there is only one valid compilation for the formula.
;;; Furthermore, there should never be any need for inverse
;;; reference compilation.  This would, in fact, be an error
;;; in the formula. 

;;; Ex.
;;; the output-flow of any mixing-tank 
;;;   = the input-1-flow of the mixing-tank
;;;     + the input-2-flow of the mixing-tank
 
;;; 2.  Since the left side is being set to one value, the right side should
;;; only return one value.  Four kinds of expressions are possible in formulas:
;;; arithmetic, comparison, logical, and if.  The arithmetic, comparison, and
;;; logical expressions are the same as for rules.  There is never any iteration
;;; in arithmetic expressions and only one value is returned.  Comparison and
;;; logical operators can have iteration within them but they should only return
;;; one truth value.  If expressions are available in formulas but are not
;;; currently available in rules.  Unlike rules, if expressions return only one
;;; value (the value of the consequent or else-consequent depending on whether
;;; the antecedent is true or not).  Again, there can be iteration in the
;;; antecedent, the consequent, and the else-consequent but only one value can
;;; be returned.  Therefore there is never any need for collection of instances.



;;; Compile-generic-simulation-formula takes as arguments an expression and
;;; a focus name.  The expression is processed by the three passes
;;; of the compiler in a manner similar to, but much simpler than
;;; that for the antecedent expression of a rule.

(defun compile-generic-simulation-formula
       (expression focus-name left-side-of-formula generic-simulation-formula
	compiling-initialization-form?)
  (let ((allow-in-line-designations? t)
	(*current-computation-frame* generic-simulation-formula))
    (when (not compiling-initialization-form?)
      (setq allow-in-line-designations? nil))
    (compile-expression expression left-side-of-formula
			(gensym-list (atomic-naming-element-of-role focus-name)))))

;; Atomic-naming-element-of-role is used to strip out local name, if any.


  

;;; Compile-generic-formula is similar to compile-generic-simulation-formula.

(defun compile-generic-formula
       (expression focus-name attribute-name generic-formula)
  (let ((*current-computation-frame* generic-formula))
    (compile-expression expression 
			(phrase-list 'the attribute-name
				     (phrase-list 'any focus-name))
			(gensym-list (atomic-naming-element-of-role focus-name)))))

;; strip out local name, if any





;;;; Notes on New Rule Compiler (Version 1.1)

;;; The new and old compilers co-exist in version 1.1.  The old compiler will be
;;; removed for 2.0.  For version 1.1, the compiler to use is determined by
;;; the frame flag compiled-as-new-rule-p which is set for the rule according to
;;; the inference engine parameter use-old-rule-compiler? when the rule is parsed.
;;; It is important to check the frame flag rather than the inference engine 
;;; parameter since the frame flag is not changed when the focal classes slot
;;; of the rule is changed, only when the text of the rule is parsed.

;;; The test kb for the new compiler is agh>explicit-iterators-test.kb.

;;; The old compiler has been removed for release 2.0 (4/19/89).


;;; 1.  General Philosophy and Design (see also ab>new-rules)

;;; The key improvement in the new rules is complete separation of iteration and
;;; quantification.  This allows iteration forms to be completely separated from
;;; the body of the rule and allows for a clear definition of a rule instance.
;;; The set of iteration forms are the context of the rule and executing these
;;; iteration forms in a nested manner produces a cross product of bindings and
;;; thus produces all rule instances.  This is very similar to the cross product
;;; context mechanism in Emycin.  Iteration forms do not return any value.
;;; Quantifiers in the body of the rule do return values.  The loss of 
;;; efficiency in certain cases of blindly doing the cross product could be
;;; circumvented at some point by having a mechanism which allows for breaking
;;; out of the top level iterator when executing the iterators in the nested way.

;;; The specification for output forms of the new compiler is given in ab>new-rules.


;;; 1.1  Deciding Where to Bind References

;;; It is important for the compiler to make sure that only iterators that
;;; contribute to defining unique rule instances go into the rule context.
;;; Thus, only bindings that iterate or that are needed by other bindings that
;;; iterate should go into the context.  Non-iterative bindings go into a
;;; top level let form that is wrapped around the rule keyword, antecedent,
;;; and actions.  
;;; Ex.
;;;     (rule-let ((level (the level tank))
;;;           (volume (the volume tank)))
;;;       (if <antecedent> <action>))
;;; The "let" form is considered part of the body of the rule.  The "let" form
;;; actually uses the operator "rule-let" to distinguish it from embedded "let"
;;; forms.  This simplifies things for the evaluator.

;;; This is best illustrated by some examples.  In the rule

;;;   "if the flow of the valve of tank1 > 5 then conclude that high-flow"

;;; there is no iteration and no need to bind "flow" or "valve".  Therefore,
;;; there are no iterators in the context and there is no "let" form being
;;; wrapped around the rule.  In the rule

;;;   "if the flow of the valve of tank1 > 5 and the switch of the valve ..."

;;; a let form is generated for valve since it is mentioned twice.  In the rule

;;;   "if the flow of any valve of tank1 ..."

;;; valve is bound using a context iterator since iteration is being done.
;;; Note that the fact that a quantifier of a designation is "the" does not
;;; necessarily mean that it won't be in the context.  If the designation is
;;; the domain of some other designation that does have an iterative quantifier,
;;; then bindings for both designations appear in the context.  For example, in
;;;   "if the flow of any valve of the tank of engine-1"
;;; iterators for both tank and valve are put into the context which is
;;;   ((the tank tank engine-1) (any valve valve tank)).

;;; The functions compile2-name and
;;; compile2-designations-from-explicit-iteration-forms analyze
;;; designations and determine which references are bound in the
;;; context, which are bound in the top level "let" form, and which do
;;; not have to be bound at all.  This determination is made by calling
;;; reference-structure-provides-binding-for-iteration? and
;;; reference-structure-provides-local-binding?, both of which make use
;;; of the top level reference tree which contains the binding structure
;;; of the entire rule.  For references which must be bound in
;;; the context, a for-stucture is generated and added to the list in
;;; the special variable context-iteration-forms.  For references which
;;; are bound in the top level "let" form, a for-structure is generated
;;; and added to the list in the special variable
;;; non-context-top-level-binding-forms.  Compile2-name is used for designations
;;; in the antecedent and action of the source of the rule and
;;; compile2-designations-from-explicit-iteration-forms is used for
;;; designations in the explicit for forms (see below).  Note that 
;;; references in the explicit for forms will always be bound either
;;; in the context or the top level "let" form.

;;; Some interesting observations and restrictions for the context are worth noting
;;; here.  First of all, the last iteration form in the context can not be a 
;;; "the" iterator.  For example,
;;;   ((any tank tank) (the valve valve tank))
;;; can never be a context.  The reason is that since the binding for valve is not
;;; needed for iteration in its binding or any further bindings, it does not belong
;;; in the context (it does not generate any new rule instances).  Thus, if a binding
;;; for valve is required, it is bound in the top level "let" form.  It is certainly
;;; possible for a "the" iterator to be the first iteration form in the context.
;;; This is the case in the previous example 
;;;   "if the flow of any valve of the tank of engine-1"
;;; where the context is 
;;;   ((the tank tank engine-1) (any valve valve tank)).
;;; Typically, however, "the" iterators are sandwiched between "any" iterators.


;; Note that the "the" iterator will never conflict with the "the" expression 
;; since the "the" iterator appears only in the context and the "the" expression
;; appears only in the rule body.


;;; 1.2  Explicit "For" Forms

;Note that the explicit for forms of the source do not necessarily correspond
;to the iterators in the context.  A binding from an explicit for form in the
;source will not appear in the context if it is not used for iteration.
;Conversely, an implicit iteration form will appear in the context even 
;though it isn't in the explicit for forms.
;(see also agh>explicit-iterators-test.kb for examples).

;; Don't have to worry about compiling explicit for forms in old compiler
;; since Mike's translators and slot value compilers prevent entering these
;; for old rules.


;;; 1.3  Focus Compilation

;;; Focus compilation is generally the same as in 1.0.  Inverse iterators are
;;; always in the context and come before forward iterators.  The inverse iterators
;;; always form a single reference path, never a tree.

;;; Because the body and context of a rule are clearly separated (see above) it
;;; is possible to use the same body for the general compilation and for all
;;; focus compilations.  Only the contexts have to be compiled for each focus
;;; compilation.
  
;;; An interesting issue arises when focus is inside the body of the rule.
;;; Since this would change the body of the rule, it would make it impossible
;;; to use one body for all compilations.  More importantly, the context would
;;; change to include several additional inverse iterators that would bind
;;; instances on the alist.  For example, in the rule

;;;   "if the valve of the tank of any engine is open then ..."

;;; the context for the forward compilation is ((any engine engine)).
;;; Thus, only engine is bound in the alist and engines define all instances 
;;; of this rule.  However, if focus within the body were allowed (on
;;; valve for example), the context would be

;;;   ((the-inverse valve valve (the tank) tank)
;;;    (the-inverse tank tank (any engine) engine)).

;;; Such a binding of valve and tank in the alist would make rule instances
;;; that are actually the same appear to be different from the ones of the
;;; general compilation.  It would violate the requirement that rule instances
;;; be defined by the context. 

;;; For this reason, when focus within the body occurs, focus is widened
;;; using the focus widening mechanism (see rule-focus-inside-rule-body?,
;;; too-narrow-focus?, and compile1-expression-top).  A count is kept of
;;; how many times the focus is widened.  This count is used to determine
;;; how many times to use the no-bind option.  In the above example,
;;; if the original focus is on valve, focus must be widened twice to
;;; be inside the body.  The inverse iterators from valve still appear
;;; in the context of course (since the focus binding is for valve) but
;;; not all generate bindings for the alist.  The context becomes

;;;   ((the-inverse-no-bind valve valve (the tank) tank)
;;;    (the-inverse-no-bind tank tank (any engine) engine)).

;;; where the no-bind refers to the range binding rather than the domain binding.
;;; The the-inverse-no-binds indicate that valve and tank should not be bound on
;;; the alist.  Therefore, engine, but not valve and tank, is bound on the alist
;;; and the above requirements are satisfied.  Note that valve and tank are
;;; bound for the purposes of evaluating subsequent iterators in the context.
;;; The number of times to use the no-bind option is simply the number of times
;;; that focus widening occurs.  In effect, the whole reason for doing the focus
;;; widening is to determine this count; focus widening does not result in a change
;;; in the compilation of the context except to change the-inverse iterators to
;;; the-inverse-no-bind iterators.  From an internal viewpoint however, when the
;;; focus is widened the correct number of times, the rule body for the
;;; compilation for focus (which is not output by the compiler) matches the rule
;;; body for the general compilation.  This is also the reason that it is wrong
;;; to do any analysis of the rule body for the compilation for focus (such as
;;; looking at context-iteration-forms or non-context-binding-forms) if focus has
;;; not been widened the correct number of times.

;;; Note that in many cases, all leading the-inverse forms in the context are
;;; converted to the-inverse-no-bind.  This is not always the case however.
;;; In the rule

;;;   "if the c of the d of the e of any f and
;;;       any h of the g of the d then ..."

;;; with focus on c, the inverse context iterators are initially

;;; ((the-inverse c c (the d) d)
;;;  (the-inverse d d (the e) e)
;;;  (the-inverse e e (any f) f))

;;; Converting all of these to no-bind would however be wrong since d provides
;;; a binding for iteration (over h).  Thus, focus widening only occurs once 
;;; and d is always bound by an iterator in the context so that it will be bound
;;; on the alist.  The context is therefore

;;; ((the-inverse-no-bind c c (the d) d)
;;;  (the-inverse d d (the e) e)
;;;  (the-inverse e e (any f) f)
;;;  (the g g d) 
;;;  (any h h g))

;;; Thus, simply always changing leading the-inverse forms to the-inverse-no-binding
;;; in is wrong.  The focus widening mechanism must be used to determine
;;; the correct number of times the no-binding option must be used.

;;; The no-bind option is simply a way of preventing binding on the alist in the
;;; context things that shouldn't be (things that get bound on the alist in the
;;; body of the rule).  What should be bound in the context is defined by the 
;;; context for the general compilation and this determines all unique instances
;;; of the generic rule.  Therefore, the no-bind option should only be used in the
;;; way described above.  There is a temptation to use the no-bind option in 
;;; cases were a context binding is only made for the purpose of other bindings 
;;; in the context and is not actually used in the rule body.  For example, in

;;;   "if the valve of any tank of any engine is open then ..."

;;; the rule body is (the valve tank).  The body really only requires that tank
;;; be on the alist;  engine is not needed.  However, omitting it would cause
;;; rule instances to be determined only be tank rather than by tank and engine
;;; which could cause confusion when comparing rule instances.

;;; See also agh>explicit-iterators-test.kb for some examples.


;;; 1.4  Actions

;;; Actions are no longer nested within the antecedent.  However, by
;;; using the top level let form, bindings from the antecedent which do
;;; not appear in the context can still be used for actions.

;;; Iteration and binding forms for the action itself are tightly wrapped
;;; around the action as before.  Thus, the for-every iterator and 
;;; let-action binding form are still valid.  Also, binding forms for
;;; expressions in actions are wrapped tightly around the expressions
;;; (see action compilation functions and actions workspace in 
;;; agh>explicit-iterators-test.kb).  The important point here is that
;;; bindings for actions and expressions within actions do not go into
;;; the context or top level "let" form;  they are wrapped tightly 
;;; around the action or the expression within the action.  This is
;;; because iteration and bindings in actions and their expressions
;;; have nothing to do with defining the rule instance and therefore
;;; can not go into the context.

;;; Because of this tight wrapping requirement, actions cannot provide
;;; references to each other;  an action can not refer to a name first
;;; mentioned in a previous action.  Actions can, of course, refer to
;;; names in the antecedent.  This restriction has never been a problem
;;; since actions typically refer to things in the antecedent and not 
;;; to other actions.  The restriction can always be circumvented by 
;;; binding things in the explicit "for" iterators.

;;; Also because of this tight wrapping requirement for actions, the 
;;; mechanism in the second pass for passing back iteration forms is retained.
;;; This could conceivably be eliminated by having more special variables
;;; like non-context-top-level-binding-forms, one for the action and one for the 
;;; expression within the action.  This would substantially simplify the
;;; second pass.  However, it would limit positioning of "let" forms around
;;; only the expressions where they are needed.  This kind of positioning may
;;; be a future requirement.

;;; A slight modification has been made to the form of the for-every action.
;;; The old form was
;;;   ('for-every (role [domain]) action)
;;; The new form is
;;;   ('for-every (simple-role range-binding [domain]) action)
;;; Thus, the range binding is separated from the role at compile time rather than
;;; at run time.


;;; 1.5  Quantifiers and Aggregators

;;; All quantifiers and aggregators have basically the same form, both for input
;;; to and output from the compiler:
;;;   (operator aggregator-phrase expression),
;;; (see also ab>new-rules).  

;;; The quantifier operators are:
;;;   there-exists-literal
;;;   for-every-literal.
;;; The aggregator operators are:
;;;   sum
;;;   product
;;;   minimum
;;;   maximum
;;;   aggregated-average
;;;   count.
;;; For the "count" aggregator and for the quantifiers, expression is
;;; logical expression.  

;;; The input form of aggregator-phrase is the standard input form for scopes:
;;;   (role [domain])
;;; where role can be:
;;;   simple-role
;;;   (simple-role . binding-name)
;;; The output form of aggregator-phrase is the standard output form for scopes:
;;;   (role binding-name [domain]).
;;; Aggregator-scope is actually a better name than aggregator-phrase.

;;; Names bound within a quantifier or aggregator may not be used outside the
;;; quantifier or aggregator (no bindings from within are wrapped around the
;;; quantifier or aggregator).  Also, focus is not allowed within the quantifier.
;;; If this occurs, focus must be widened (use current focus widening mechanism).

;;; Quantifiers and aggregators are handled specially in each of the three 
;;; passes.  

;;; In the first pass, compile1-quantifier-or-aggregator makes a slight
;;; modification to the aggregator scope to make it look like a designation and
;;; then compiles it as such.  This ensures that the binding made in the scope
;;; will be included in the reference tree, the same way that bindings for
;;; designations are.  The aggregator expression is first pass compiled as any
;;; other expression.

;;; It is important to note that compilation of the aggregator scope can not be
;;; omitted from the first pass.  This would result in an incorrect reference
;;; tree causing problems for the error checking functions and also for
;;; compilation with focus.

;;; In the second pass, compile2-quantifier-or-aggregator compiles the aggregator
;;; expression but not the aggregator scope.  Second pass compiling the scope
;;; would invoke compile2-name which would possibly generate a for-structure.
;;; This is unnecessary.  The aggregator scope is simple enough that the third
;;; pass can derive the final form from the results of the first pass.
;;; Note that any binding forms (let forms since "any" is not allowed inside an
;;; aggregator) for the aggregator expression are wrapped tightly
;;; around this expression (since bindings from within the aggregator can not
;;; be used outside of it).  Thus, these bindings do not go into the top level
;;; "rule-let" form for the rule.  Quantifiers and aggregators are similar
;;; to actions in this respect.  See also documentation for the special variable
;;; in-non-top-level-context?.

;;; In the third pass, compile3-quantifier-or-aggregator compiles generates the
;;; output form for the aggregator scope.  The aggregator expression is third
;;; pass compiled as any other expression.

;;; The test kb for quantifiers and aggregators is agh>aggregators-and-quantifiers.


;;; 2.  Compiler Switch Checkpoints

;;; The frame flag compiled-as-new-rule-p is tested in the following functions to
;;; determine whether to use the old or new compiler:
;;;   compile-rule
;;;   compile2-name
;;;   compile2-top-level-expression-and-insert-action-if-appropriate
;;;   compile3-for-structure-according-to-quantifier
;;;   too-narrow-focus?

;;; Thus, despite the fact that the output forms for the new and old compiler are
;;; quite different, most of the compiler hasn't changed.  The basic abstractions
;;; and mechanisms are still used.  The above functions are really the only places
;;; where there is some duplication of code.


;;; 3.  Items Needed Only for Old Compiler

;;; The following items can be removed when the old compiler becomes obsolete 
;;; (after 2.0):

;;; 1.  In second pass, extra values being returned for universal context case.
;;;     The second pass is simpler and the third pass is more complicated.
;;; 2.  Reference wrapping functions called by 
;;;     compile2-top-level-expression-and-insert-action-if-appropriate-old.
;;;     This is done in the third pass in the new compiler.
;;; 3.  Action insertion and PAMO form generation mechanism (because actions are
;;;     no longer inserted).  This is a great simplification and will eliminate
;;;     a lot of code.  Can also get rid of actions slot in for-structure.
;;; 4.  Short-designation-for-inverse-references slot in reference structure.
;;;     Also, make-for-structure-given-reference-structure can be simplified
;;;     since for structures are no longer generated for inverse references.
;;;     Inverse references are taken care of in third pass by
;;;     generate-inverse-context-from-inverse-reference-path.  For this reason
;;;     also, compile3-for-structure-according-to-quantifier no longer has to
;;;     take care of the inverse case.
;;; 5.  Compile3-for-structure-according-to-quantifier can be simplified.  No
;;;     longer have to deal with case of inverse or 'for-all.
;;; 6.  Expressions use the new compiler but are not compiled any differently.


;;; 4.  Other Notes

;;; The 3-d reference tree lattice is crucial to deciding which references are
;;; bound in the context, which are bound in "let" forms, and which are not
;;; bound at all.  It is also used for focus widening and is extensively used in
;;; error checking.  Actually, for the most part, only the top level reference
;;; tree and the reference paths for the designations are used; reference trees
;;; for intermediate expressions are not really used.  In any case, this
;;; mechanism is still the heart of the compiler and its complexity can not be 
;;; reduced.


; Document issues of rule instances and focus widening, here and in ab>new-rules.





;;;; Notes for Release 2.0



;;; Various code improvements have been made for 2.0.  Also, the old rule
;;; compiler has been completely eliminated.  Templates, both function templates
;;; and action templates, are now fully utilized.

;;; An important improvement is that expressions within actions can now 
;;; provide references to each other.  Thus,
;;; "change the color-pattern of x so that middle = the foo of x, 
;;;  inside = the bar of the foo"
;;; is now legal.  This was accomplished by wrapping all bindings for 
;;; expressions within actions around the entire action using let-action or
;;; every forms.



;;; 1.  Relaxation of Reference Restrictions in Create and There Exists

;;; The create action can have a local name which is bound to the item that is
;;; created.  In in order actions, this local name can be referred to by actions
;;; after the create action.  This allows for concluding the values of attributes
;;; of newly created transient objects.  It is, however, a departure from the
;;; normal restriction that references to local names in an action occur only in
;;; that action.

;;; A similar case is the there exists expression.  It (like other quantifiers and
;;; aggregators) can have a local variable which is bound to each item over which
;;; the iteration is being done.  For all quantifiers and aggregators except for
;;; there exists, this local variable can be referenced only from within the 
;;; quantifier or aggregator.  An exception is made for there exists because it
;;; is often useful to refer to one of the items that satisfy the logical
;;; expression in the there exists.  Note that only one item will be left bound
;;; to the local variable upon exit of the there exists, even if more than one
;;; item satisfies the logical expression.  In the case of the inference engine,
;;; this item is the first one that causes the accumulated certainty to exceed
;;; the required threshold.  In the case of the simulator, this item is the first
;;; one that satisfies the logical expression.  However, because the user has
;;; no control over the order in which roles are served, he has no control over
;;; which item is left bound to the local variable.

;;; This relaxation of restrictions is accomplished by putting the local name into
;;; the non-context bindings, rather than the more local bindings for an action or
;;; a quantifier.  The evaluators for there exists or create set this binding,
;;; rather than creating a local temporary one, so that when the evaluators exit,
;;; the binding is left to be used by subsequent expressions or actions.

;;; The compiler sets up these bindings by having the first pass note the local
;;; names in local-names-not-associated-with-roles.
;;; Compile1-quantifier-or-aggregator and compile1-create-action do this.  In the
;;; second pass, for-structures for these names are put into
;;; non-context-top-level-binding-forms (by compile2-name and
;;; compile2-quantifier-or-aggregator).  Finally, in the third pass,
;;; wrap-non-context-top-level-binding-forms wraps the binding forms around the
;;; rule body or expression.

;;; The illegal reference checking code makes exceptions in these cases so that
;;; errors are not flagged.

;;; The test kb for the there exists expression is 
;;; "ma:>agh>new-there-exists".





;;;; Notes for Release 3.0



;;; Compilation of Array Expressions and Actions



;;; In 3.0, designations can contain array references.
;;; The grammar for an array designation is of the form

;;; "<array-designation> [ <index-expression> ]
;;; Ex.
;;; "the level of arrayx[index]"

;;; This grammar is a bit different from existing designation grammar in that
;;; there is no way to bind a local name to the result of the array access and
;;; there is no way to refer to the result of the array access in a subsequent
;;; expression.  This is a departure from other roles where it is possible to
;;; do this
;;; Ex.
;;; "the level of the tank T1 connected to valve1"
;;; (here it is possible to refer to tank or T1 in a subsequent expression.

;;; A proposed future solution is to allow, optionally, something like

;;; "the level of the tank that is arrayx[index]"

;;; The "tank that is" part should be optional so that array access does not
;;; become too unwieldy, especially for numerical sorts of applications.

;;; Another way to look at this issue is the need to allow for users to themselves
;;; specify let bindings.



;;; Another restriction on this grammar is that the designation immediately to the
;;; left of the left angle bracket must be a name (either global or local).  Thus,

;;; "the level of arrayx[index]"
;;; is allowed, but
;;; "the level of the array[index]"
;;; is not.  The latter has an inherent ambiguity in that it is not clear whether
;;; the designation for the array is "the array" or "the level of the array".



;;; Another restriction on this grammar is that the index expression can not be
;;; generic (can not have the quantifier "any" in it).  This restriction is not
;;; due to any technical reason; expression like
;;; "arrayx[the index of any pump]"
;;; could be compiled.  However, the text for this expression is so confusing that
;;; it makes sense to require users to keep the iteration outside the index
;;; expression.



;;; The array reference role is not invertible.  If it were,
;;; pattern-checking-inverse-references would become a tree rather than a path.
;;; While this would not be overly difficult to implement, we decided that there
;;; is negligible value in making array references invertible so it is not an
;;; issue.



;;; Array elements are designated in a 3.0 parse by a designation of the form

;;; (the (nth-element item-or-datum) <array designation> <index expression>)
;;; Ex.
;;;    (the (nth-element item-or-datum) array-1 x)

;;; Nth-element is a new role.  There are two new things about this form:  1) the
;;; designation has a second domain (the index expression), and 2) this domain is
;;; an expression rather than a designation.  

;;; The fact that the index is an expression introduces a new problem since this
;;; is the first case of a designation containing embedded expressions.  The
;;; problem is that designations can be part of rule contexts or the rule body,
;;; depending on quantifiers.  If any designation depending on the result of the
;;; array designation has an "any" quantifier, then the array designation is part
;;; of the rule context rather than the rule body.  This causes a problem because
;;; to evaluate the array designation, the index expression must be evaluated, and
;;; the index expression may fail to have a value.  This is not a problem in the
;;; rule body, the evaluation of which can handle no value.  In the rule context
;;; however, there is a problem because the context evaluator can not handle
;;; expressions that fail to have a value.

;;; An example of this is as follows:

;;; "the level of the tank of arrayx[index] 
;;;  + the level of any valve of the tank"

;;; This problem is dealt with in 3.0 by the compiler flagging this as an error.
;;; Note that this is not a problem that can be solved by grammar since the
;;; subsequent referring designation can be in a completely differnt part of the
;;; rule.  The only cases where this restriction is likely to cause problems is
;;; when an array contains elements that themselves have dynamic relations to
;;; other items.  For such cases, users should use procedures, or should forward
;;; chain to another rule with the element as the focus.

;;; Another important restriction is that the nth-element role is not invertable.
;;; In 3.0, all focus compilations within non-invertable roles will be flagged as
;;; errors. 

;;; Ordering problems of the usual type (reference to local name defined
;;; subsequently) cannot occur due to the fact that the array designation can only
;;; be a name.  One interesting problem, however, occurs when the index expression
;;; references a result from the array designation:

;;; "the temperature of the subsystem of arrayx[the index of the subsystem]".  

;;; This could never work because subsystem depends on the results of the array
;;; reference, but the index expression of the array reference depends on
;;; subsystem, resulting in a circularity.  Note that users may well want to try
;;; this since it is similar to something like

;;; "the temperature of the subsystem of arrayx + the foo of the subsystem"

;;; which is perfectly acceptable.



;;; The knowledge base "ma:>agh>array-compiles" contains test cases for array
;;; compilation.

;;; The knowledge base "ma:>agh>focus-widening-memo" was implemented to further
;;; document, and provide examples of, focus widening issues.



;;; A note on non-context variable bindings - Non-context bindings
;;; appear in rule-lets, wrapped around rule bodies, or in let forms
;;; wrapped around expressions.  In some cases, let forms are wrapped
;;; more locally, but for the most part, they are all wrapped around the
;;; outside.  This presents an opportunity for optimization since it is
;;; sometimes possible to wrap the bindings more locally, and in this
;;; way possibly avoid role service.  For example, if the antecedent of
;;; an if expression fails, then any role service done specifically for
;;; expressions in the then clause is unnecessary.  It makes sense to
;;; wrap such bindings only around the then clause, rather than around
;;; the entire expression.  Note that there is no need to restrict any
;;; references, as was done in earlier versions of the compiler (except
;;; for existence predicates).  If a reference is defined in some clause
;;; and referenced later, then the bindings have to be wrapped outside
;;; both references. 

;;; An important point to remember with local let bindings is that the
;;; semantics are really now set semantics.  Therefore, while it is
;;; necessary to do the binding only when it is valid (only after the
;;; binding for a there-exists local variable has been established for
;;; example), the binding is actually valid until the end of the
;;; expression.

;;; For example, in the formula

;;; "let the outflow of any pump P = (if there exists a valve V
;;; connected to P and the fraction-open FO1 of V > 0.2 then FO1 + 0.5 *
;;; FO1)" 

;;; the let binding for FO1 must be after the "there-exists" form.  The
;;; let binding is actually wrapped around the designation "the
;;; fraction-open FO1 of V".  If the semantics of this were strictly as
;;; a "let" form, then subsequent references to FO1 would be illegal.
;;; This is unnecessarily restrictive however.  Fortunately, the stack
;;; evaluator uses set semantics; it sets up a local variable vector,
;;; and sets elements of this according to the let forms.  The values
;;; are thus valid even beyond the end of the let forms.

;;; There are, however, certain restrictions on references to
;;; there-exists which should be checked at compile time, but are not
;;; currently.  For example, if the antecedent of an if form is a
;;; "there-exists" then the "else" form of the "if" should not reference
;;; the local variable of the there-exists.  There is a similar
;;; restriction for "or" expressions.



;;;; Reform of ROLES

;;; Notes by AGH, JRA, and ML 8/27/90

;;; It is generally agreed that there are many problems with roles.

;;; Note that pseudo-attribute is not a grammar category. Take this
;;; out of grammar1.

;;; A change was made to atomic-class-element-of-role and
;;; atomic-class-element-of-simple-role. 

;;; There were questions raised about designation-could-denote-entity-p.
;;; When should it return NIL?

;;; Atomic naming element of role needs review. What is the binding name
;;; produced by the roles workspace and subworkspace?

;;; Note defined-type-of-role and its uses in type-of-role and type-of-designation.

