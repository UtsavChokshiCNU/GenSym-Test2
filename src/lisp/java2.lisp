;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-

;;;; Module JAVA2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; John Hodgkinson

(in-package "AB")

;;;; Overview

;;; This file implements the class external-java-class, which provides
;;; syntax-checking of Java code from within G2.

;;; The 4-semi section "Java BNF" is a transcription of the Java grammar in
;;; modified Backus-Naur format.  The function emit-transformed-java-grammar
;;; reads this section and emits def-grammar-category forms.  These have been
;;; hand-edited to produce more useful syntax trees in case we ever need them.

;;; The 4-semi section "Java Tokenizing" defines java-tokenizer, compiled from
;;; the parameter java-tokens.  This mechanism adheres as closely as possible to
;;; Java tokenization, given that some G2 characters must be quoted and that
;;; symbol print names are in UTF-G.

;;; The 4-semi section "Java Grammar Prompts" contains machinery necessary to
;;; emit readable grammar prompts, given that Java symbols are case-sensitive.

;;;; Java BNF

;; From _The Java Language Specification_, Gosling, Joy, Steele, pp 440 ff.

#|

;; Beginning of Java Grammar

Literal:
  <integerLiteral>
  <floatingPointLiteral>
  <booleanLiteral>
  <characterLiteral>
  <stringLiteral>
  <nullLiteral>

;; Chapter 4

Type:
  PrimitiveType
  ReferenceType

PrimitiveType:
  NumericType
  "boolean"

NumericType:
  IntegralType
  FloatingPointType

IntegralType:
  "byte"
  "short"
  "int"
  "long"
  "char"

FloatingPointType:
  "float"
  "double"

ReferenceType:
  ClassOrInterfaceType
  ArrayType

ClassOrInterfaceType:
  Name

ClassType:
  ClassOrInterfaceType

InterfaceType:
  ClassOrInterfaceType

ArrayType:
  PrimitiveType "[" "]"
  Name "[" "]"
  ArrayType "[" "]"

;; Chapter 6

Name:
  SimpleName
  QualifiedName

SimpleName:
  <identifier>

QualifiedName:
  Name "." <identifier>

;; Chpater 7

CompilationUnit:
  [PackageDeclaration] [ImportDeclarations] [TypeDeclarations]

ImportDeclarations:
  ImportDeclaration
  ImportDeclarations ImportDeclaration

TypeDeclarations:
  TypeDeclaration
  TypeDeclarations TypeDeclaration

PackageDeclaration:
  "package" Name ";"

ImportDeclaration:
  SingleTypeImportDeclaration
  TypeImportOnDemandDeclaration

SingleTypeImportDeclaration:
  "import" Name ";"

TypeImportOnDemandDeclaration:
  "import" Name "." "*" ";"

TypeDeclaration:
  ClassDeclaration
  InterfaceDeclaration
  ";"

;; Productions for True LALR(1) Conformance, p 442

Modifiers:
  Modifier
  Modifiers Modifier

Modifier:
  "public"
  "protected"
  "private"
  "static"
  "abstract"
  "final"
  "native"
  "synchronized"
  "transient"
  "volatile"

;; Chapter 8.1

ClassDeclaration:
  [Modifiers] "class" <identifier> [Super] [Interfaces] ClassBody

Super:
  "extends" ClassType

Interfaces:
  "implements" InterfaceTypeList

InterfaceTypeList:
  InterfaceType
  InterfaceTypeList "," InterfaceType

ClassBody:
  "{" [ClassBodyDeclarations] "}"

ClassBodyDeclarations:
  ClassBodyDeclaration
  ClassBodyDeclarations ClassBodyDeclaration

;; jh, 8/27/97.  Added "Block" production to ClassBodyDeclaration, supporting
;; 1.1 syntax for instance initializers.

ClassBodyDeclaration:
  ClassMemberDeclaration
  StaticInitializer
  ConstructorDeclaration
  Block

;; jh, 8/27/97.  Added 3rd and 4th production to ClassMemberDeclaration,
;; supporting 1.1 syntax for inner classes.

ClassMemberDeclaration:
  FieldDeclaration
  MethodDeclaration
  ClassDeclaration
  InterfaceDeclaration

;; Chapter 8.3

FieldDeclaration:
  [Modifiers] Type VariableDeclarators ";"

VariableDeclarators:
  VariableDeclarator
  VariableDeclarators "," VariableDeclarator

VariableDeclarator:
  VariableDeclaratorId
  VariableDeclaratorId "=" VariableInitializer

VariableDeclaratorId:
  <identifier>
  VariableDeclaratorId "[" "]"

VariableInitializer:
  Expression
  ArrayInitializer

;; Chapter 8.4

MethodDeclaration:
  MethodHeader MethodBody

MethodHeader:
  [Modifiers] Type MethodDeclarator [Throws]
  [Modifiers] "void" MethodDeclarator [Throws]

;; The second right-hand side is obsolescent.
;; No in-line comments -- they are interpreted as part of the grammar!
MethodDeclarator:
  <identifier> "(" [FormalParameterList] ")"
  MethodDeclarator "[" "]"

FormalParameterList:
  FormalParameter
  FormalParameterList "," FormalParameter

;; jh, 8/27/97.  Modified LocalVariableDeclaration to support 1.1 syntax for
;; blank finals.

FormalParameter:
  [Modifiers] Type VariableDeclaratorId

Throws:
  "throws" ClassTypeList

ClassTypeList:
  ClassType
  ClassTypeList "," ClassType

MethodBody:
  Block
  ";"

;; Chapter 8.5
  
StaticInitializer:
  "static" Block

;; Chapter 8.6

ConstructorDeclaration:
  [Modifiers] ConstructorDeclarator [Throws] ConstructorBody

ConstructorDeclarator:
  SimpleName "(" [FormalParameterList] ")"

ConstructorBody:
  "{" [ExplicitConstructorInvocation] [BlockStatements] "}"

;; jh, 8/2/97.  Added 3rd production to ExplicitConstructorInvocation for 1.1
;; syntax.

;; jh, 8/28/97.  Added Name.super to satisfy the example on p 111 of Java in a
;; Nutshell, 2nd edition.  The Sun doc, however, only permits Primary.super,
;; i.e., it only permits an expression before "super", not simply a variable
;; reference or a qualified name.  For future reference, Sun doc is currently in
;; http://java.sun.com/products/jdk/1.1/docs/
;; guide/innerclasses/spec/innerclasses.doc.html

ExplicitConstructorInvocation:
  "this" "(" [ArgumentList] ")"
  "super" "(" [ArgumentList] ")"
  PrimaryOrName "." "super" "(" [ArgumentList] ")"

;; Chapter 9

InterfaceDeclaration:
  [Modifiers] "interface" <identifier> [ExtendsInterfaces] InterfaceBody

ExtendsInterfaces:
  "extends" InterfaceType
  ExtendsInterfaces "," InterfaceType

InterfaceBody:
  "{" [InterfaceMemberDeclarations] "}"

InterfaceMemberDeclarations:
  InterfaceMemberDeclaration
  InterfaceMemberDeclarations InterfaceMemberDeclaration

;; jh, 8/27/97.  Added 3rd and 4th production to InterfaceMemberDeclaration,
;; supporting 1.1 syntax for inner classes.

InterfaceMemberDeclaration:
  ConstantDeclaration
  AbstractMethodDeclaration
  ClassDeclaration
  InterfaceDeclaration

ConstantDeclaration:
  FieldDeclaration

AbstractMethodDeclaration:
  MethodHeader ";"

;; Chapter 10

ArrayInitializer:
  "{" [VariableInitializers] [","] "}"

VariableInitializers:
  VariableInitializer
  VariableInitializers "," VariableInitializer

;; Chapter 14

Block:
  "{" [BlockStatements] "}"

BlockStatements:
  BlockStatement
  BlockStatements BlockStatement

;; jh, 8/27/97.  Added 3rd production to BlockStatement, supporting 1.1 syntax
;; for inner classes.

BlockStatement:
  LocalVariableDeclarationStatement
  Statement
  ClassDeclaration

LocalVariableDeclarationStatement:
  LocalVariableDeclaration ";"

;; jh, 8/27/97.  Modified LocalVariableDeclaration to support 1.1 syntax for
;; final locals.

LocalVariableDeclaration:
  [Modifiers] Type VariableDeclarators

Statement:
  StatementWithoutTrailingSubstatement
  LabeledStatement
  IfThenStatement
  IfThenElseStatement
  WhileStatement
  ForStatement

StatementNoShortIf:
  StatementWithoutTrailingSubstatement
  LabeledStatementNoShortIf
  IfThenElseStatementNoShortIf
  WhileStatementNoShortIf
  ForStatementNoShortIf

StatementWithoutTrailingSubstatement:
  Block
  EmptyStatement
  ExpressionStatement
  SwitchStatement
  DoStatement
  BreakStatement
  ContinueStatement
  ReturnStatement
  SynchronizedStatement
  ThrowStatement
  TryStatement

EmptyStatement:
  ";"

LabeledStatement:
  <identifier> ":" Statement

LabeledStatementNoShortIf:
  <identifier> ":" StatementNoShortIf

ExpressionStatement:
  StatementExpression ";"

StatementExpression:
  Assignment
  PreIncrementExpression
  PreDecrementExpression
  PostIncrementExpression
  PostDecrementExpression
  MethodInvocation
  ClassInstanceCreationExpression

IfThenStatement:
  "if" "(" Expression ")" Statement

IfThenElseStatement:
  "if" "(" Expression ")" StatementNoShortIf  "else" Statement

IfThenElseStatementNoShortIf:
  "if" "(" Expression ")" StatementNoShortIf  "else" StatementNoShortIf

SwitchStatement:
  "switch" "(" Expression ")" SwitchBlock

SwitchBlock:
  "{" [SwitchBlockStatementGroups] [SwitchLabels] "}"

SwitchBlockStatementGroups:
  SwitchBlockStatementGroup
  SwitchBlockStatementGroups SwitchBlockStatementGroup

SwitchBlockStatementGroup:
  SwitchLabels BlockStatements

SwitchLabels:
  SwitchLabel
  SwitchLabels SwitchLabel

SwitchLabel:
  "case" ConstantExpression ":"
  "default" ":"

WhileStatement:
  "while" "(" Expression ")" Statement

WhileStatementNoShortIf:
  "while" "(" Expression ")" StatementNoShortIf

DoStatement:
  "do" Statement "while" "(" Expression ")" ";"

ForStatement:
  "for" "(" [ForInit] ";" [Expression] ";" [ForUpdate] ")" Statement

ForStatementNoShortIf:
  "for" "(" [ForInit] ";" [Expression] ";" [ForUpdate] ")" StatementNoShortIf

ForInit:
  StatementExpressionList
  LocalVariableDeclaration

ForUpdate:
  StatementExpressionList

StatementExpressionList:
  StatementExpression
  StatementExpressionList "," StatementExpression

BreakStatement:
  "break" [<identifier>] ";"

ContinueStatement:
  "continue" [<identifier>] ";"

ReturnStatement:
  "return" [Expression] ";"

ThrowStatement:
  "throw" Expression ";"

SynchronizedStatement:
  "synchronized" "(" Expression ")" Block

TryStatement:
  "try" Block Catches
  "try" Block [Catches] Finally

Catches:
  CatchClause
  Catches CatchClause

CatchClause:
  "catch" "(" FormalParameter ")" Block

Finally:
  "finally" Block

;; Chapter 15

Primary:
  PrimaryNoNewArray
  ArrayCreationExpression

;; jh, 8/27/97. Modified PrimaryNoNewArray to support 1.1 syntax.  In
;; particular, added the ClassType.this production to support inner classes, and
;; added the ".class" productions to support class literals.

PrimaryNoNewArray:
  Literal
  "this"
  "(" Expression ")"
  ClassInstanceCreationExpression
  FieldAccess
  MethodInvocation
  ArrayAccess
  ClassType "." "this"
  Type "." "class"
  "void" "." "class"

;; jh, 8/27/97.  Modified ClassInstanceCreationExpression per the new 1.1
;; syntax for inner classes.

;; jh, 8/28/97.  Added Name.new to satisfy the example on p 110 of Java in a
;; Nutshell, 2nd edition.  The Sun doc, however, only permits Primary.new, i.e.,
;; it only permits an expression before "new", not simply a variable reference
;; or a qualified name.  For future reference, Sun doc is currently in
;; http://java.sun.com/products/jdk/1.1/docs/
;; guide/innerclasses/spec/innerclasses.doc.html

ClassInstanceCreationExpression:
  "new" ClassType "(" [ArgumentList] ")" [ClassBody]
  PrimaryOrName "." "new" <identifier> "(" [ArgumentList] ")" [ClassBody]

PrimaryOrName:
  Primary
  Name

ArgumentList:
  Expression
  ArgumentList "," Expression

;; jh, 8/27/97.  Added 3rd production to ArrayCreationExpression, supporting 1.1
;; syntax for anonymous array expressions.

ArrayCreationExpression:
  "new" PrimitiveType DimExprs [Dims]
  "new" ClassOrInterfaceType DimExprs [Dims]
  "new" Type Dims ArrayInitializer

DimExprs:
  DimExpr
  DimExprs DimExpr

DimExpr:
  "[" Expression "]"

Dims:
  "[" "]"
  Dims "[" "]"

FieldAccess:
  Primary "." <identifier>
  "super" "." <identifier>

MethodInvocation:
  Name "(" [ArgumentList] ")"
  Primary "." <identifier> "(" [ArgumentList] ")"
  "super" "." <identifier> "(" [ArgumentList] ")"

ArrayAccess:
  Name "[" Expression "]"
  PrimaryNoNewArray "[" Expression "]"

PostfixExpression:
  Primary
  Name
  PostIncrementExpression
  PostDecrementExpression

PostIncrementExpression:
  PostfixExpression "++"

PostDecrementExpression:
  PostfixExpression "--"

UnaryExpression:
  PreIncrementExpression
  PreDecrementExpression
  "+" UnaryExpression
  "-" UnaryExpression
  UnaryExpressionNotPlusMinus

PreIncrementExpression:
  "++" UnaryExpression

PreDecrementExpression:
  "--" UnaryExpression

UnaryExpressionNotPlusMinus:
  PostfixExpression
  "~" UnaryExpression
  "!" UnaryExpression
  CastExpression

CastExpression:
  "(" PrimitiveType [Dims] ")" UnaryExpression
  "(" Expression ")" UnaryExpressionNotPlusMinus
  "(" Name Dims ")" UnaryExpressionNotPlusMinus

MultiplicativeExpression:
  UnaryExpression
  MultiplicativeExpression "*" UnaryExpression
  MultiplicativeExpression "/" UnaryExpression
  MultiplicativeExpression "%" UnaryExpression

AdditiveExpression:
  MultiplicativeExpression
  AdditiveExpression "+" MultiplicativeExpression
  AdditiveExpression "-" MultiplicativeExpression

ShiftExpression:
  AdditiveExpression
  ShiftExpression "<<" AdditiveExpression
  ShiftExpression ">>" AdditiveExpression
  ShiftExpression ">>>" AdditiveExpression

RelationalExpression:
  ShiftExpression
  RelationalExpression "<" ShiftExpression
  RelationalExpression ">" ShiftExpression
  RelationalExpression "<=" ShiftExpression
  RelationalExpression ">=" ShiftExpression
  RelationalExpression "instanceof" ReferenceType

EqualityExpression:
  RelationalExpression
  EqualityExpression "==" RelationalExpression
  EqualityExpression "!=" RelationalExpression

AndExpression:
  EqualityExpression
  AndExpression "&" EqualityExpression

ExclusiveOrExpression:
  AndExpression
  ExclusiveOrExpression "^" AndExpression

InclusiveOrExpression:
  ExclusiveOrExpression
  InclusiveOrExpression "|" ExclusiveOrExpression

ConditionalAndExpression:
  InclusiveOrExpression
  ConditionalAndExpression "&&" InclusiveOrExpression

ConditionalOrExpression:
  ConditionalAndExpression
  ConditionalOrExpression "||" ConditionalAndExpression

ConditionalExpression:
  ConditionalOrExpression
  ConditionalOrExpression "?" Expression ":" ConditionalExpression

AssignmentExpression:
  ConditionalExpression
  Assignment

Assignment:
  LeftHandSide AssignmentOperator AssignmentExpression

LeftHandSide:
  Name
  FieldAccess
  ArrayAccess

AssignmentOperator:
  { = *= /= %= += -= <<= >>= >>>= &= ^= |= }

Expression:
  AssignmentExpression

ConstantExpression:
  Expression

;; End of Java Grammar

|#

;;;; Emitting G2 Grammar Categories from Java BNF

;; jh, 7/13/97.  The reason I'm automating this is to incorporate new grammar
;; (the introduction of inner classes means the Java builders are not shy about
;; this).

;; I can't believe this doesn't exist somewhere.
(defmacro defun-for-development (name args &body body)
  (if (eval-feature :development)
      `(defun ,name ,args ,@body)
      nil))

;; I also can't believe this doesn't exist somewhere.
(defmacro defparameter-for-development (name initform)
  (if (eval-feature :development)
      `(defparameter ,name ,initform)
      nil))

(defun-for-development java-grammar-initial-line-p (line)
  (equal line ";; Beginning of Java Grammar"))

(defun-for-development java-grammar-final-line-p (line)
  (equal line ";; End of Java Grammar"))

(defun-for-development java-grammar-comment-p (line)
  (and (> (length line) 0)
       (eql (char line 0) #\;)))

(defvar-for-development java-grammar-stream? nil)

(defun-for-development get-next-java-production ()
  (loop for line? = (read-line java-grammar-stream? nil nil)
	with collecting-p = nil
	with lines = nil
	while (and line? (not (java-grammar-final-line-p line?)))
	do
    (let* ((trimmed-line (string-trim '(#\Space #\Tab) line?))
	   (skip-line-p
	     (or (equal trimmed-line "")
		 (java-grammar-comment-p trimmed-line))))
      (cond
	((and skip-line-p collecting-p) (loop-finish))
	(skip-line-p)
	(t (unless collecting-p (setq collecting-p t))
	   (push trimmed-line lines))))
	finally (return (reverse lines))))

(defparameter-for-development java-grammar-input-file "/bt/jh/lisp/java2.lisp")
(defparameter-for-development java-grammar-output-file java-grammar-input-file)

(defun-for-development close-java-grammar-stream-if-any ()
  (when java-grammar-stream?
    (close java-grammar-stream?)
    (setq java-grammar-stream? nil)))

(defun-for-development open-java-grammar-stream ()
  (close-java-grammar-stream-if-any)
  (setq java-grammar-stream?  
	(open java-grammar-input-file :direction :input))
  (loop for line? = (read-line java-grammar-stream? nil nil)
	while (and line? (not (java-grammar-initial-line-p line?))))
  java-grammar-stream?)


;; jh, 7/20/97.  Note that intern-for-java-grammar is the only function in this
;; 4-semi group that is used outside of development.

(defun-simple intern-for-java-grammar (gensym-string)
  ;; I.e., if the printname violates UTF-G.
  (if (equal gensym-string "~")
      (intern "~~")
      (intern gensym-string)))

(defun-for-development hyphenate-mixed-java-grammar-symbol
    (java-grammar-symbol)
  (loop for i from 0 below (length java-grammar-symbol)
	for this-char = (char java-grammar-symbol i)
	with component? = nil
	with components = nil
	do
    (when (and (upper-case-p this-char) component?)
      (push (concatenate 'string (reverse component?)) components)
      (setq component? nil))
    (push (char-upcase this-char)  component?)
	finally
    (when component?
      (push (concatenate 'string (reverse component?)) components))
    (return
      (intern-for-java-grammar
        (apply #'concatenate 'string
	  (let ((components-in-order (cons "JAVA" (reverse components))))
	    (loop for component in components-in-order
		  for component-cons on components-in-order
		  collect component
		  when (cdr component-cons) collect "-")))))))

(defun-for-development get-java-left-hand-side (java-production-lines)
  (let* ((left-hand-directive (car java-production-lines))
	 (last-char-index (1- (length left-hand-directive))))
    (unless (eql (char left-hand-directive last-char-index) #\:)
      (error "left-hand-side ~S must end in a contiguous colon"
	left-hand-directive))
    (subseq left-hand-directive 0 last-char-index)))

(defun-for-development tokenize-java-right-hand-sides (java-right-hand-lines)
  (loop for line in java-right-hand-lines
	collect
    (loop for i from 0 below (length line)
	  for this-char = (char line i)
	  with chars? = nil
	  with tokens = nil
	  do
      (cond
	((member this-char '(#\Space #\Tab) :test #'eql)
	 (when chars?
	   (push (concatenate 'string (reverse chars?)) tokens)
	   (setq chars? nil)))
	(t (push this-char chars?)))
	  finally
      (when chars?
	(push (concatenate 'string (reverse chars?)) tokens))
      (return (reverse tokens)))))

(defun-for-development convert-braced-list-element-to-terminal (element)
  (concatenate 'string "\"" element "\""))

(defun-for-development expand-java-terminals-from-braced-list-if-any
    (java-production-tokens)
  (if (equal (caar java-production-tokens) "{")
      (mapcar #'list
	(loop for token in (cdr (apply #'append java-production-tokens))
	      until (equal token "}")
	      collect (convert-braced-list-element-to-terminal token)))
      nil))

(defun-for-development java-leaf-symbol? (java-grammar-symbol)
  (let ((length (length java-grammar-symbol)))
    (and (> length 0)
	 (eql (char java-grammar-symbol 0) #\")
	 (subseq java-grammar-symbol 1 (1- length)))))

(defun-for-development convert-java-leaf-to-quoted-token (java-leaf-symbol)
  `(quote ,(intern-for-java-grammar java-leaf-symbol)))

(defun-for-development java-terminal-symbol? (java-grammar-symbol)
  (let ((length (length java-grammar-symbol)))
    (and (> length 0)
	 (eql (char java-grammar-symbol 0) #\<)
	 (subseq java-grammar-symbol 1 (1- length)))))

(defun-for-development optional-java-grammar-symbol? (java-grammar-symbol)
  (let ((length (length java-grammar-symbol)))
    (and (> length 0)
	 (eql (char java-grammar-symbol 0) #\[ )
	 (subseq java-grammar-symbol 1 (1- length)))))

(defun-for-development expand-optionals-in-java-right-hand-side
    (java-right-hand-side)
  (labels ((expand-1 (right-hand-symbols? accumulated?)
	     (if (null right-hand-symbols?)
		 accumulated?
		 (let* ((this-symbol (car right-hand-symbols?))
			(optional-symbol?
			  (optional-java-grammar-symbol? this-symbol)))
		   (expand-1
		     (cdr right-hand-symbols?)
		     (if optional-symbol?
			 (loop for side in accumulated?
			       collect side
			       collect (cons optional-symbol? side))
			 (loop for side in accumulated?
			       collect (cons this-symbol side))))))))
    (mapcar #'reverse (expand-1 java-right-hand-side (list nil)))))

(defun-for-development quoted-symbol-in-java-production? (grammar-symbol)
  (and (consp grammar-symbol)
       (eq (car grammar-symbol) 'quote)
       (intern-for-java-grammar
	 ;; Appease Java's case-sensitivity.
	 (string-downcase (symbol-name (cadr grammar-symbol))))))

(defun-for-development strip-java-from-grammar-symbol (grammar-symbol)
  (let* ((stripped (subseq (symbol-name grammar-symbol) 5))
	 (length (length stripped)))
    (flet ((strip-suffix (suffix)
	     (let ((position? (search suffix stripped)))
	       (when (and position?
			  (= (+ position? (length suffix)) length))
		 (setq stripped (subseq stripped 0 position?))))))
      (strip-suffix "-DECLARATION")
      (strip-suffix "-NO-SHORT-IF")
      (intern-for-java-grammar stripped))))

(defun-for-development transform-java-right-hand-side
    (left-hand-symbol right-hand-side)
  (let* ((indices? nil)
	 (raw-production
	   (loop for token in right-hand-side
		 for index from 1
		 collect
		 (let ((leaf? (java-leaf-symbol? token)))
		   (cond
		     (leaf?
		      (convert-java-leaf-to-quoted-token leaf?))
		     (t (push index indices?)
			(hyphenate-mixed-java-grammar-symbol
			  (or (java-terminal-symbol? token) token)))))))
	 (production-length (length raw-production))
	 (first-symbol (car raw-production))
	 (stripped-left-hand
	   (strip-java-from-grammar-symbol left-hand-symbol)))
    (cond
      ;; singleton
      ((= production-length 1)
       (let ((quoted-singleton?
	       (quoted-symbol-in-java-production? first-symbol)))
	 (cond
	   ((and quoted-singleton?
		 (> (length (symbol-name quoted-singleton?)) 1))
	    (list first-symbol quoted-singleton?))
	   (quoted-singleton? raw-production)
	   (t (list first-symbol 1)))))
      ;; left-recursion
      ((and (eq first-symbol left-hand-symbol)
	    (if (= production-length 3)
		(not (quoted-symbol-in-java-production?
		       (third raw-production)))
		t))	    
       (case production-length
	 (2 (list
	      raw-production
	      `(,stripped-left-hand 1 2)
	      'simplify-associative-operation))
	 (3 (let* ((second-symbol (second raw-production))
		   (tag
		     (if (member second-symbol '('\; '\,) :test #'equal)
			 stripped-left-hand
			 (or (quoted-symbol-in-java-production?
			       second-symbol)
			     second-symbol))))
	      (list raw-production
		    `(,tag 1 3)
		    'simplify-associative-operation)))
	 (otherwise (list raw-production))))
      ;; mixed terminals and non-terminals
      (t (if indices?
	     (list raw-production `(,stripped-left-hand ,@(reverse indices?)))
	     (list raw-production))))))

;; jh, 9/15/97.  Dispense with the parse tree in distribution, though someday we
;; might want to use it.  Note that at present we do want to retain some minimal
;; parse information (currently class and interface names, import list, and
;; package), so we need to hand-edit some forms emitted by
;; transform-java-production to use def-grammar-category instead.

(defparameter-for-macro build-java-parse-tree-in-development-p nil)

(defmacro def-divergent-java-grammar-category
    (name &key full-parse-tree-form attenuated-parse-tree-form)
  (declare (ignore name))
  (if (and (eval-feature :development) build-java-parse-tree-in-development-p)
      full-parse-tree-form
      attenuated-parse-tree-form))

(defmacro def-java-grammar-category (category-name &body right-hand-sides)
  (let ((attenuated-rules
	  (loop for rhs in right-hand-sides
		collect
		`(,category-name
		    ,@(cond
			((atom rhs) `(',rhs))
			(t `(,(first rhs))))))))
    `(def-divergent-java-grammar-category ,category-name
       :full-parse-tree-form
       (def-grammar-category ,category-name () ,@right-hand-sides)
       :attenuated-parse-tree-form
       (add-grammar-rules ',attenuated-rules))))

(defun-for-development transform-java-production (java-production-lines)
  (let* ((left-hand-side
	   (get-java-left-hand-side java-production-lines))
	 (right-hand-lines (cdr java-production-lines))
	 (java-production-tokens
	   (tokenize-java-right-hand-sides right-hand-lines))
	 (hyphenated-left-hand
	   (hyphenate-mixed-java-grammar-symbol left-hand-side)))
    (setq java-production-tokens
	  (or (expand-java-terminals-from-braced-list-if-any
		java-production-tokens)
	      (loop for right-hand-side in java-production-tokens
		    append
		    (expand-optionals-in-java-right-hand-side
		      right-hand-side))))
    `(def-java-grammar-category ,hyphenated-left-hand
       ,@(loop for right-hand-side? in java-production-tokens
	       when right-hand-side?
	         collect
	   (transform-java-right-hand-side
	     hyphenated-left-hand
	     right-hand-side?)))))

(defun-for-development pprint-multi-escaped-java-grammar-symbol
    (grammar-symbol output-stream)
  (loop for i from 0 below (length grammar-symbol)
	for this-char = (char grammar-symbol i)
	do
    (when (eql #\| this-char)
      (format output-stream "\\"))
    (format output-stream "~A" this-char)))

(defun-for-development pprint-quoted-java-grammar-symbol
    (grammar-symbol output-stream)
  (format output-stream "'")
  (let ((quoted-symbol-name (symbol-name grammar-symbol)))
    (cond
      ((find #\| quoted-symbol-name)
       (pprint-multi-escaped-java-grammar-symbol
	 quoted-symbol-name
	 output-stream))
      ((= (length quoted-symbol-name) 1)
       (format output-stream "\\")
       (format output-stream "~A" grammar-symbol))
      (t (format output-stream "~S" grammar-symbol)))))

(defun-for-development pprint-transformed-java-production-list
    (raw-production transformation? compiler? output-stream)
  (format output-stream "(")
  (loop for token in raw-production
	for token-cons on raw-production
	for last-token-p = (null (cdr token-cons))
	do
    (let ((quoted-symbol?
	    (quoted-symbol-in-java-production? token)))
      (cond
	(quoted-symbol?
	 (pprint-quoted-java-grammar-symbol
	   quoted-symbol?
	   output-stream))
	(t (format output-stream "~A" token))))
    (unless last-token-p
      (format output-stream " ")))
  (format output-stream ")")
  (when transformation?
    (let ((first-transform?
	    (and (consp transformation?) (first transformation?))))
      (cond
	((and first-transform?
	      (find #\| (symbol-name first-transform?)))
	 (format output-stream "~%   (")
	 (loop for transform in transformation?
	       for first-transform-p = t then nil
	       for transform-cons on transformation?
	       for last-transform-p = (null (cdr transform-cons))
	       do
	   (if first-transform-p
	       (pprint-multi-escaped-java-grammar-symbol
		 (symbol-name first-transform?)
		 output-stream)
	       (format output-stream "~A" transform))
	   (unless last-transform-p
	     (format output-stream " ")))
	 (format output-stream ")"))
	((= (length raw-production) 1)
	 (cond
	   ((and (symbolp transformation?)
		 (find #\| (symbol-name transformation?)))
	    (format output-stream " ")
	    (pprint-multi-escaped-java-grammar-symbol
	      (symbol-name transformation?)
	      output-stream))
	   (t (format output-stream " ~S" transformation?))))
	(t (format output-stream "~%   ~S" transformation?)))))
  (when compiler?
    (format output-stream "~%   ~A" compiler?)))

;; jh, 7/21/97.  The function pprint-transformed-java-production is necessary to
;; replace pprint, because Lucid pprint emits |;| for the symbol whose printname
;; is the single semicolon character, and the Lucid reader appear to have a
;; problem seeing that as a symbol rather than the beginning of an in-line
;; comment.  Once we have the pprint mechanism, we can also make several
;; irresitible cosmetic improvements.

(defun-for-development pprint-transformed-java-production
    (java-production output-stream)
  (let ((left-hand-1 (first java-production))
	(left-hand-2 (second java-production))
	(left-hand-3 (or (third java-production)  "()"))
	(right-hand-sides (cdddr java-production)))
    (format output-stream "~&(~A ~A ~A~%" left-hand-1 left-hand-2 left-hand-3)
    (loop for right-hand-side in right-hand-sides
	  for right-hand-side-cons on right-hand-sides
	  for last-right-hand-side-p = (null (cdr right-hand-side-cons))
	  do
      (format output-stream "  (")
      (let* ((raw-production (first right-hand-side))
	     (transformation? (second right-hand-side))
	     (compiler? (third right-hand-side))
	     (quoted-symbol?
	       (quoted-symbol-in-java-production? raw-production)))
	(cond
	  (quoted-symbol?
	   (pprint-quoted-java-grammar-symbol
	     quoted-symbol?
	     output-stream)
	   (when transformation?
	     (cond
	       ((and (symbolp transformation?)
		     (find #\| (symbol-name transformation?)))
		(format output-stream " ")
		(pprint-multi-escaped-java-grammar-symbol
		  (symbol-name transformation?)
		  output-stream))
	       (t (format output-stream " ~S" transformation?))))
	   (when compiler?
	     (format output-stream " ~A" compiler?)))
	  ((consp raw-production)
	   (pprint-transformed-java-production-list
	     raw-production
	     transformation?
	     compiler?
	     output-stream))
	  (t (format output-stream "~A" raw-production)
	     (when transformation?
	       (format output-stream " ~S" transformation?))
	     (when compiler?
	       (format output-stream " ~A" compiler?)))))
      (format output-stream ")")
      (unless last-right-hand-side-p
	(format output-stream "~%")))
    (format output-stream ")~%")))

(defun-for-development emit-transformed-java-grammar (output-stream)
  (open-java-grammar-stream)
  (loop for production-lines? = (get-next-java-production)
	while production-lines?
	do
    (pprint-transformed-java-production
      (transform-java-production production-lines?)
      output-stream)
    (terpri output-stream))
  (close-java-grammar-stream-if-any))

;;;; Emitted G2 Grammar Categories from Java BNF

;;; Following 3-semi block generated by emit-transformed-java-grammar.

;; jh, 9/15/97.  Hand-edits (grep for ";hand"):
;; qualified-name                      added simplify-associative-operation.
;; class-declaration                   identifier should always follow class tag.
;; super                               super tag should be extends.
;; interfaces                          interfaces tag should be implements.
;; variable-declarator-id              should distinguish between array and non-array.
;; method-declarator                   added empty formal-parameter-list to () case.
;; declarator                          added empty formal-parameter-list to () case.
;; explicit-constructor-invocation     returned tags uniformly.
;; for-statement                       tagged iteration sub-expressions uniformly.
;; for-statement-no-short-if           tagged iteration sub-expressions uniformly.
;; primary-no-new-array                () case now passes tag through too.
;; field-access                        tagged super case.
;; method-invocation                   tagged () and super cases.
;; assignment-operator                 returned = tag.
;; constructor-declarator              tagged empty body
;; class-instance-creation-expression  normalized due to new anonymous class syntax
;; formal-parameter                    normalized due to new blank finals syntax
;; local-variable-declaration          normalized due to new final locals syntax
;; class-declaration                   added def-divergent-java-grammar-category
;; interface-declaration               added def-divergent-java-grammar-category
;;  - several -                        converted to def-grammar-category for pass-through

(def-java-grammar-category java-literal
  (java-integer-literal 1)
  (java-floating-point-literal 1)
  (java-boolean-literal 1)
  (java-character-literal 1)
  (java-string-literal 1)
  (java-null-literal 1))

(def-java-grammar-category java-type
  (java-primitive-type 1)
  (java-reference-type 1))

(def-java-grammar-category java-primitive-type
  (java-numeric-type 1)
  ('|boolean| |boolean|))

(def-java-grammar-category java-numeric-type
  (java-integral-type 1)
  (java-floating-point-type 1))

(def-java-grammar-category java-integral-type
  ('|byte| |byte|)
  ('|short| |short|)
  ('|int| |int|)
  ('|long| |long|)
  ('|char| |char|))

(def-java-grammar-category java-floating-point-type
  ('|float| |float|)
  ('|double| |double|))

(def-java-grammar-category java-reference-type
  (java-class-or-interface-type 1)
  (java-array-type 1))

(def-java-grammar-category java-class-or-interface-type
  (java-name 1))

(def-java-grammar-category java-class-type
  (java-class-or-interface-type 1))

(def-java-grammar-category java-interface-type
  (java-class-or-interface-type 1))

(def-java-grammar-category java-array-type
  ((java-primitive-type '\[ '\])
   (array-type 1))
  ((java-name '\[ '\])
   (array-type 1))
  ((java-array-type '\[ '\])
   (array-type 1)))

;;hand - was def-java-grammar-category
(def-grammar-category java-name ()
  (java-simple-name 1)
  (java-qualified-name 1))

;;hand - was def-java-grammar-category
(def-grammar-category java-simple-name ()
  (java-identifier 1))

;;hand - was def-java-grammar-category
(def-grammar-category java-qualified-name ()
  ((java-name '\. java-identifier)
   (qualified-name 1 3)
   simplify-associative-operation ;hand
   ))

;;hand - was def-java-grammar-category
(def-grammar-category java-compilation-unit ()
  (java-type-declarations 1)
  (java-import-declarations 1)
  ((java-import-declarations java-type-declarations)
   (compilation-unit 1 2))
  (java-package-declaration 1)
  ((java-package-declaration java-type-declarations)
   (compilation-unit 1 2))
  ((java-package-declaration java-import-declarations)
   (compilation-unit 1 2))
  ((java-package-declaration java-import-declarations java-type-declarations)
   (compilation-unit 1 2 3)))

;;hand - was def-java-grammar-category
(def-grammar-category java-import-declarations ()
  (java-import-declaration 1)
  ((java-import-declarations java-import-declaration)
   (import-declarations 1 2)
   simplify-associative-operation))

;;hand - was def-java-grammar-category
(def-grammar-category java-type-declarations ()
  (java-type-declaration 1)
  ((java-type-declarations java-type-declaration)
   (type-declarations 1 2)
   simplify-associative-operation))

;;hand - was def-java-grammar-category
(def-grammar-category java-package-declaration ()
  (('|package| java-name '\;)
   (package 2)))

;;hand - was def-java-grammar-category
(def-grammar-category java-import-declaration ()
  (java-single-type-import-declaration 1)
  (java-type-import-on-demand-declaration 1))

;;hand - was def-java-grammar-category
(def-grammar-category java-single-type-import-declaration ()
  (('|import| java-name '\;)
   (single-type-import 2)))

;;hand - was def-java-grammar-category
(def-grammar-category java-type-import-on-demand-declaration ()
  (('|import| java-name '\. '\* '\;)
   (type-import-on-demand 2)))

;;hand - was def-java-grammar-category
(def-grammar-category java-type-declaration ()
  (java-class-declaration 1)
  (java-interface-declaration 1)
  ('\;))

(def-java-grammar-category java-modifiers
  (java-modifier 1)
  ((java-modifiers java-modifier)
   (modifiers 1 2)
   simplify-associative-operation))

(def-java-grammar-category java-modifier
  ('|public| |public|)
  ('|protected| |protected|)
  ('|private| |private|)
  ('|static| |static|)
  ('|abstract| |abstract|)
  ('|final| |final|)
  ('|native| |native|)
  ('|synchronized| |synchronized|)
  ('|transient| |transient|)
  ('|volatile| |volatile|))

#+no ;automatically generated
(def-java-grammar-category java-class-declaration
  (('|class| java-identifier java-class-body)
   (class 2 3))
  (('|class| java-identifier java-interfaces java-class-body)
   (class 2 3 4))
  (('|class| java-identifier java-super java-class-body)
   (class 2 3 4))
  (('|class| java-identifier java-super java-interfaces java-class-body)
   (class 2 3 4 5))
  ((java-modifiers '|class| java-identifier java-class-body)
   (class 1 3 4))
  ((java-modifiers '|class| java-identifier java-interfaces java-class-body)
   (class 1 3 4 5))
  ((java-modifiers '|class| java-identifier java-super java-class-body)
   (class 1 3 4 5))
  ((java-modifiers '|class| java-identifier java-super java-interfaces
    java-class-body)
   (class 1 3 4 5 6)))

;;hand
(def-divergent-java-grammar-category java-class-declaration
  :full-parse-tree-form 
  (def-grammar-category java-class-declaration ()
    (('|class| java-identifier java-class-body)
     (class 2 3))
    (('|class| java-identifier java-interfaces java-class-body)
     (class 2 3 4))
    (('|class| java-identifier java-super java-class-body)
     (class 2 3 4))
    (('|class| java-identifier java-super java-interfaces java-class-body)
     (class 2 3 4 5))
    ((java-modifiers '|class| java-identifier java-class-body)
     (class 3 1 4))
    ((java-modifiers '|class| java-identifier java-interfaces java-class-body)
     (class 3 1 4 5))
    ((java-modifiers '|class| java-identifier java-super java-class-body)
     (class 3 1 4 5))
    ((java-modifiers '|class| java-identifier java-super java-interfaces
     java-class-body)
     (class 3 1 4 5 6)))
  :attenuated-parse-tree-form
  (def-grammar-category java-class-declaration ()
    (('|class| java-identifier java-class-body)
     (class 2))
    (('|class| java-identifier java-interfaces java-class-body)
     (class 2))
    (('|class| java-identifier java-super java-class-body)
     (class 2))
    (('|class| java-identifier java-super java-interfaces java-class-body)
     (class 2))
    ((java-modifiers '|class| java-identifier java-class-body)
     (class 3))
    ((java-modifiers '|class| java-identifier java-interfaces java-class-body)
     (class 3))
    ((java-modifiers '|class| java-identifier java-super java-class-body)
     (class 3))
    ((java-modifiers '|class| java-identifier java-super java-interfaces
     java-class-body)
     (class 3))))

(def-java-grammar-category java-super
  (('|extends| java-class-type)
   (extends 2))) ;(super 2))) ;hand

(def-java-grammar-category java-interfaces
  (('|implements| java-interface-type-list)
   (implements 2))) ;(interfaces 2))) ;hand

(def-java-grammar-category java-interface-type-list
  (java-interface-type 1)
  ((java-interface-type-list '\, java-interface-type)
   (interface-type-list 1 3)
   simplify-associative-operation))

(def-java-grammar-category java-class-body
  (('\{ '\}))
  (('\{ java-class-body-declarations '\})
   (class-body 2)))

(def-java-grammar-category java-class-body-declarations
  (java-class-body-declaration 1)
  ((java-class-body-declarations java-class-body-declaration)
   (class-body-declarations 1 2)
   simplify-associative-operation))

(def-java-grammar-category java-class-body-declaration
  (java-class-member-declaration 1)
  (java-static-initializer 1)
  (java-constructor-declaration 1)
  (java-block 1))

(def-java-grammar-category java-class-member-declaration
  (java-field-declaration 1)
  (java-method-declaration 1)
  (java-class-declaration 1)
  (java-interface-declaration 1))

(def-java-grammar-category java-field-declaration
  ((java-type java-variable-declarators '\;)
   (field 1 2))
  ((java-modifiers java-type java-variable-declarators '\;)
   (field 1 2 3)))

(def-java-grammar-category java-variable-declarators
  (java-variable-declarator 1)
  ((java-variable-declarators '\, java-variable-declarator)
   (variable-declarators 1 3)
   simplify-associative-operation))

(def-java-grammar-category java-variable-declarator
  (java-variable-declarator-id 1)
  ((java-variable-declarator-id '\= java-variable-initializer)
   (variable-declarator 1 3)))

#+no ;automatically generated
(def-java-grammar-category java-variable-declarator-id
  (java-identifier 1)
  ((java-variable-declarator-id '\[ '\])
   (variable-declarator-id 1)))

;;hand
(def-java-grammar-category java-variable-declarator-id
  (java-identifier (1 (array-p nil)))
  ((java-variable-declarator-id '\[ '\])
   (variable-declarator-id (1 (array-p t)))))

(def-java-grammar-category java-variable-initializer
  (java-expression 1)
  (java-array-initializer 1))

(def-java-grammar-category java-method-declaration
  ((java-method-header java-method-body)
   (method 1 2)))

(def-java-grammar-category java-method-header
  ((java-type java-method-declarator)
   (method-header 1 2))
  ((java-type java-method-declarator java-throws)
   (method-header 1 2 3))
  ((java-modifiers java-type java-method-declarator)
   (method-header 1 2 3))
  ((java-modifiers java-type java-method-declarator java-throws)
   (method-header 1 2 3 4))
  (('|void| java-method-declarator)
   (method-header 2))
  (('|void| java-method-declarator java-throws)
   (method-header 2 3))
  ((java-modifiers '|void| java-method-declarator)
   (method-header 1 3))
  ((java-modifiers '|void| java-method-declarator java-throws)
   (method-header 1 3 4)))

#+no ;automatically generated
(def-java-grammar-category java-method-declarator
  ((java-identifier '\( '\))
   (method-declarator 1))
  ((java-identifier '\( java-formal-parameter-list '\))
   (method-declarator 1 3))
  ((java-method-declarator '\[ '\])
   (method-declarator 1)))

;;hand
(def-java-grammar-category java-method-declarator
  ((java-identifier '\( '\))
   (method-declarator 1 (formal-parameter-list)))
  ((java-identifier '\( java-formal-parameter-list '\))
   (method-declarator 1 3))
  ((java-method-declarator '\[ '\])
   (method-declarator (1 (array-p t)))))

(def-java-grammar-category java-formal-parameter-list
  (java-formal-parameter 1)
  ((java-formal-parameter-list '\, java-formal-parameter)
   (formal-parameter-list 1 3)
   simplify-associative-operation))

#+no ;automatically generated
(def-java-grammar-category java-formal-parameter
  ((java-type java-variable-declarator-id)
   (formal-parameter 1 2))
  ((java-modifiers java-type java-variable-declarator-id)
   (formal-parameter 1 2 3)))

;;hand
(def-java-grammar-category java-formal-parameter
  ((java-type java-variable-declarator-id)
   (formal-parameter 1 2))
  ((java-modifiers java-type java-variable-declarator-id)
   (formal-parameter 2 3 1)))

(def-java-grammar-category java-throws
  (('|throws| java-class-type-list)
   (throws 2)))

(def-java-grammar-category java-class-type-list
  (java-class-type 1)
  ((java-class-type-list '\, java-class-type)
   (class-type-list 1 3)
   simplify-associative-operation))

(def-java-grammar-category java-method-body
  (java-block 1)
  ('\;))

(def-java-grammar-category java-static-initializer
  (('|static| java-block)
   (static-initializer 2)))

(def-java-grammar-category java-constructor-declaration
  ((java-constructor-declarator java-constructor-body)
   (constructor 1 2))
  ((java-constructor-declarator java-throws java-constructor-body)
   (constructor 1 2 3))
  ((java-modifiers java-constructor-declarator java-constructor-body)
   (constructor 1 2 3))
  ((java-modifiers java-constructor-declarator java-throws
    java-constructor-body)
   (constructor 1 2 3 4)))

(def-java-grammar-category java-constructor-declarator
  ((java-simple-name '\( '\))
   ;;(constructor-declarator 1)) ;hand
   (constructor-declarator 1 (formal-parameter-list))) 
  ((java-simple-name '\( java-formal-parameter-list '\))
   (constructor-declarator 1 3)))

(def-java-grammar-category java-constructor-body
  (('\{ '\}) (constructor-body)) ;(('\{ '\})) ;hand
  (('\{ java-block-statements '\})
   (constructor-body 2))
  (('\{ java-explicit-constructor-invocation '\})
   (constructor-body 2))
  (('\{ java-explicit-constructor-invocation java-block-statements '\})
   (constructor-body 2 3)))

#+no ;automatically generated
(def-java-grammar-category java-explicit-constructor-invocation
  (('|this| '\( '\)))
  (('|this| '\( java-argument-list '\))
   (explicit-constructor-invocation 3))
  (('|super| '\( '\)))
  (('|super| '\( java-argument-list '\))
   (explicit-constructor-invocation 3))
  ((java-primary-or-name '\. '|super| '\( '\))
   (explicit-constructor-invocation 1))
  ((java-primary-or-name '\. '|super| '\( java-argument-list '\))
   (explicit-constructor-invocation 1 5)))

;;hand
(def-java-grammar-category java-explicit-constructor-invocation
  (('|this| '\( '\))
   (explicit-constructor-invocation (argument-list) (this)))
  (('|this| '\( java-argument-list '\))
   (explicit-constructor-invocation 3 (this)))
  (('|super| '\( '\))
   (explicit-constructor-invocation (argument-list) (super)))
  (('|super| '\( java-argument-list '\))
   (explicit-constructor-invocation 3 (super)))
  ((java-primary-or-name '\. '|super| '\( '\))
   (explicit-constructor-invocation (argument-list) (super) 1))
  ((java-primary-or-name '\. '|super| '\( java-argument-list '\))
   (explicit-constructor-invocation 5 (super) 1)))

#+no ;automatically generated
(def-java-grammar-category java-interface-declaration
  (('|interface| java-identifier java-interface-body)
   (interface 2 3))
  (('|interface| java-identifier java-extends-interfaces java-interface-body)
   (interface 2 3 4))
  ((java-modifiers '|interface| java-identifier java-interface-body)
   (interface 1 3 4))
  ((java-modifiers '|interface| java-identifier java-extends-interfaces
    java-interface-body)
   (interface 1 3 4 5)))

;;hand
(def-divergent-java-grammar-category java-interface-declaration
  :full-parse-tree-form 
  (def-grammar-category java-interface-declaration ()
    (('|interface| java-identifier java-interface-body)
     (interface 2 3))
    (('|interface| java-identifier java-extends-interfaces java-interface-body)
     (interface 2 3 4))
    ((java-modifiers '|interface| java-identifier java-interface-body)
     (interface 3 1 4))
    ((java-modifiers '|interface| java-identifier java-extends-interfaces
     java-interface-body)
     (interface 3 1 4 5)))
  :attenuated-parse-tree-form
  (def-grammar-category java-interface-declaration ()
    (('|interface| java-identifier java-interface-body)
     (interface 2))
    (('|interface| java-identifier java-extends-interfaces java-interface-body)
     (interface 2))
    ((java-modifiers '|interface| java-identifier java-interface-body)
     (interface 3))
    ((java-modifiers '|interface| java-identifier java-extends-interfaces
     java-interface-body)
     (interface 3))))

(def-java-grammar-category java-extends-interfaces
  (('|extends| java-interface-type)
   (extends-interfaces 2))
  ((java-extends-interfaces '\, java-interface-type)
   (extends-interfaces 1 3)
   simplify-associative-operation))

(def-java-grammar-category java-interface-body
  (('\{ '\}))
  (('\{ java-interface-member-declarations '\})
   (interface-body 2)))

(def-java-grammar-category java-interface-member-declarations
  (java-interface-member-declaration 1)
  ((java-interface-member-declarations java-interface-member-declaration)
   (interface-member-declarations 1 2)
   simplify-associative-operation))

(def-java-grammar-category java-interface-member-declaration
  (java-constant-declaration 1)
  (java-abstract-method-declaration 1)
  (java-class-declaration 1)
  (java-interface-declaration 1))

(def-java-grammar-category java-constant-declaration
  (java-field-declaration 1))

(def-java-grammar-category java-abstract-method-declaration
  ((java-method-header '\;)
   (abstract-method 1)))

(def-java-grammar-category java-array-initializer
  (('\{  '\})
   (array-initializer))
  (('\{  '\, '\})
   (array-initializer))
  (('\{ java-variable-initializers '\})
   (array-initializer 2))
  (('\{ java-variable-initializers '\, '\})
   (array-initializer 2)))

(def-java-grammar-category java-variable-initializers
  (java-variable-initializer 1)
  ((java-variable-initializers '\, java-variable-initializer)
   (variable-initializers 1 3)
   simplify-associative-operation))

(def-java-grammar-category java-block
  (('\{ '\}))
  (('\{ java-block-statements '\})
   (block 2)))

(def-java-grammar-category java-block-statements
  (java-block-statement 1)
  ((java-block-statements java-block-statement)
   (block-statements 1 2)
   simplify-associative-operation))

(def-java-grammar-category java-block-statement
  (java-local-variable-declaration-statement 1)
  (java-statement 1)
  (java-class-declaration 1))

(def-java-grammar-category java-local-variable-declaration-statement
  ((java-local-variable-declaration '\;)
   (local-variable-declaration-statement 1)))

#+no ;automatically generated
(def-java-grammar-category java-local-variable-declaration
  ((java-type java-variable-declarators)
   (local-variable 1 2))
  ((java-modifiers java-type java-variable-declarators)
   (local-variable 1 2 3)))

;;hand
(def-java-grammar-category java-local-variable-declaration
  ((java-type java-variable-declarators)
   (local-variable 1 2))
  ((java-modifiers java-type java-variable-declarators)
   (local-variable 2 3 1)))

(def-java-grammar-category java-statement
  (java-statement-without-trailing-substatement 1)
  (java-labeled-statement 1)
  (java-if-then-statement 1)
  (java-if-then-else-statement 1)
  (java-while-statement 1)
  (java-for-statement 1))

(def-java-grammar-category java-statement-no-short-if
  (java-statement-without-trailing-substatement 1)
  (java-labeled-statement-no-short-if 1)
  (java-if-then-else-statement-no-short-if 1)
  (java-while-statement-no-short-if 1)
  (java-for-statement-no-short-if 1))

(def-java-grammar-category java-statement-without-trailing-substatement
  (java-block 1)
  (java-empty-statement 1)
  (java-expression-statement 1)
  (java-switch-statement 1)
  (java-do-statement 1)
  (java-break-statement 1)
  (java-continue-statement 1)
  (java-return-statement 1)
  (java-synchronized-statement 1)
  (java-throw-statement 1)
  (java-try-statement 1))

(def-java-grammar-category java-empty-statement
  ('\;))

(def-java-grammar-category java-labeled-statement
  ((java-identifier '\: java-statement)
   (labeled-statement 1 3)))

(def-java-grammar-category java-labeled-statement-no-short-if
  ((java-identifier '\: java-statement-no-short-if)
   (labeled-statement 1 3)))

(def-java-grammar-category java-expression-statement
  ((java-statement-expression '\;)
   (expression-statement 1)))

(def-java-grammar-category java-statement-expression
  (java-assignment 1)
  (java-pre-increment-expression 1)
  (java-pre-decrement-expression 1)
  (java-post-increment-expression 1)
  (java-post-decrement-expression 1)
  (java-method-invocation 1)
  (java-class-instance-creation-expression 1))

(def-java-grammar-category java-if-then-statement
  (('|if| '\( java-expression '\) java-statement)
   (if-then-statement 3 5)))

(def-java-grammar-category java-if-then-else-statement
  (('|if| '\( java-expression '\) java-statement-no-short-if
    '|else| java-statement)
   (if-then-else-statement 3 5 7)))

(def-java-grammar-category java-if-then-else-statement-no-short-if
  (('|if| '\( java-expression '\) java-statement-no-short-if
    '|else| java-statement-no-short-if)
   (if-then-else-statement 3 5 7)))

(def-java-grammar-category java-switch-statement
  (('|switch| '\( java-expression '\) java-switch-block)
   (switch-statement 3 5)))

(def-java-grammar-category java-switch-block
  (('\{ '\}))
  (('\{ java-switch-labels '\})
   (switch-block 2))
  (('\{ java-switch-block-statement-groups '\})
   (switch-block 2))
  (('\{ java-switch-block-statement-groups java-switch-labels '\})
   (switch-block 2 3)))

(def-java-grammar-category java-switch-block-statement-groups
  (java-switch-block-statement-group 1)
  ((java-switch-block-statement-groups java-switch-block-statement-group)
   (switch-block-statement-groups 1 2)
   simplify-associative-operation))

(def-java-grammar-category java-switch-block-statement-group
  ((java-switch-labels java-block-statements)
   (switch-block-statement-group 1 2)))

(def-java-grammar-category java-switch-labels
  (java-switch-label 1)
  ((java-switch-labels java-switch-label)
   (switch-labels 1 2)
   simplify-associative-operation))

(def-java-grammar-category java-switch-label
  (('|case| java-constant-expression '\:)
   (switch-label 2))
  (('|default| '\:)))

(def-java-grammar-category java-while-statement
  (('|while| '\( java-expression '\) java-statement)
   (while-statement 3 5)))

(def-java-grammar-category java-while-statement-no-short-if
  (('|while| '\( java-expression '\) java-statement-no-short-if)
   (while-statement 3 5)))

(def-java-grammar-category java-do-statement
  (('|do| java-statement '|while| '\( java-expression '\) '\;)
   (do-statement 2 5)))

#+no ;automatically generated
(def-java-grammar-category java-for-statement
  (('|for| '\( '\; '\; '\) java-statement)
   (for-statement 6))
  (('|for| '\( '\; '\; java-for-update '\) java-statement)
   (for-statement 5 7))
  (('|for| '\( '\; java-expression '\; '\) java-statement)
   (for-statement 4 7))
  (('|for| '\( '\; java-expression '\; java-for-update '\) java-statement)
   (for-statement 4 6 8))
  (('|for| '\( java-for-init '\; '\; '\) java-statement)
   (for-statement 3 7))
  (('|for| '\( java-for-init '\; '\; java-for-update '\) java-statement)
   (for-statement 3 6 8))
  (('|for| '\( java-for-init '\; java-expression '\; '\) java-statement)
   (for-statement 3 5 8))
  (('|for| '\( java-for-init '\; java-expression '\; java-for-update '\)
    java-statement)
   (for-statement 3 5 7 9)))

;;hand
(def-java-grammar-category java-for-statement
  (('|for| '\( '\; '\; '\) java-statement)
   (for-statement (for-init) (for-test) (for-update) 6))
  (('|for| '\( '\; '\; java-for-update '\) java-statement)
   (for-statement (for-init) (for-test) (for-update 5) 7))
  (('|for| '\( '\; java-expression '\; '\) java-statement)
   (for-statement (for-init) (for-test 4) (for-update) 7))
  (('|for| '\( '\; java-expression '\; java-for-update '\) java-statement)
   (for-statement (for-init) (for-test 4) (for-update 6) 8))
  (('|for| '\( java-for-init '\; '\; '\) java-statement)
   (for-statement (for-init 3) (for-test) (for-update) 7))
  (('|for| '\( java-for-init '\; '\; java-for-update '\) java-statement)
   (for-statement (for-init 3) (for-test) (for-update 6) 8))
  (('|for| '\( java-for-init '\; java-expression '\; '\) java-statement)
   (for-statement (for-init 3) (for-test 5) (for-update) 8))
  (('|for| '\( java-for-init '\; java-expression '\; java-for-update '\)
    java-statement)
   (for-statement (for-init 3) (for-test 5) (for-update 7) 9)))

#+no ;automatically generated
(def-java-grammar-category java-for-statement-no-short-if
  (('|for| '\( '\; '\; '\) java-statement-no-short-if)
   (for-statement 6))
  (('|for| '\( '\; '\; java-for-update '\) java-statement-no-short-if)
   (for-statement 5 7))
  (('|for| '\( '\; java-expression '\; '\) java-statement-no-short-if)
   (for-statement 4 7))
  (('|for| '\( '\; java-expression '\; java-for-update '\)
    java-statement-no-short-if)
   (for-statement 4 6 8))
  (('|for| '\( java-for-init '\; '\; '\) java-statement-no-short-if)
   (for-statement 3 7))
  (('|for| '\( java-for-init '\; '\; java-for-update '\)
    java-statement-no-short-if)
   (for-statement 3 6 8))
  (('|for| '\( java-for-init '\; java-expression '\; '\)
    java-statement-no-short-if)
   (for-statement 3 5 8))
  (('|for| '\( java-for-init '\; java-expression '\; java-for-update '\)
    java-statement-no-short-if)
   (for-statement 3 5 7 9)))

;;hand
(def-java-grammar-category java-for-statement-no-short-if
  (('|for| '\( '\; '\; '\) java-statement-no-short-if)
   (for-statement (for-init) (for-test) (for-update) 6))
  (('|for| '\( '\; '\; java-for-update '\) java-statement-no-short-if)
   (for-statement (for-init) (for-test) (for-update 5) 7))
  (('|for| '\( '\; java-expression '\; '\) java-statement-no-short-if)
   (for-statement (for-init) (for-test 4) (for-update) 7))
  (('|for| '\( '\; java-expression '\; java-for-update '\)
    java-statement-no-short-if)
   (for-statement (for-init) (for-test 4) (for-update 6) 8))
  (('|for| '\( java-for-init '\; '\; '\) java-statement-no-short-if)
   (for-statement (for-init 3) (for-test) (for-update) 7))
  (('|for| '\( java-for-init '\; '\; java-for-update '\)
    java-statement-no-short-if)
   (for-statement (for-init 3) (for-test) (for-update 6) 8))
  (('|for| '\( java-for-init '\; java-expression '\; '\)
    java-statement-no-short-if)
   (for-statement (for-init 3) (for-test 5) (for-update) 8))
  (('|for| '\( java-for-init '\; java-expression '\; java-for-update '\)
    java-statement-no-short-if)
   (for-statement (for-init 3) (for-test 5) (for-update 7) 9)))

(def-java-grammar-category java-for-init
  (java-statement-expression-list 1)
  (java-local-variable-declaration 1))

(def-java-grammar-category java-for-update
  (java-statement-expression-list 1))

(def-java-grammar-category java-statement-expression-list
  (java-statement-expression 1)
  ((java-statement-expression-list '\, java-statement-expression)
   (statement-expression-list 1 3)
   simplify-associative-operation))

(def-java-grammar-category java-break-statement
  (('|break| '\;))
  (('|break| java-identifier '\;)
   (break-statement 2)))

(def-java-grammar-category java-continue-statement
  (('|continue| '\;))
  (('|continue| java-identifier '\;)
   (continue-statement 2)))

(def-java-grammar-category java-return-statement
  (('|return| '\;))
  (('|return| java-expression '\;)
   (return-statement 2)))

(def-java-grammar-category java-throw-statement
  (('|throw| java-expression '\;)
   (throws-statement 2)))

(def-java-grammar-category java-synchronized-statement
  (('|synchronized| '\( java-expression '\) java-block)
   (synchronized-statement 3 5)))

(def-java-grammar-category java-try-statement
  (('|try| java-block java-catches)
   (try-statement 2 3))
  (('|try| java-block java-finally)
   (try-statement 2 3))
  (('|try| java-block java-catches java-finally)
   (try-statement 2 3 4)))

(def-java-grammar-category java-catches
  (java-catch-clause 1)
  ((java-catches java-catch-clause)
   (catches 1 2)
   simplify-associative-operation))

(def-java-grammar-category java-catch-clause
  (('|catch| '\( java-formal-parameter '\) java-block)
   (catch-clause 3 5)))

(def-java-grammar-category java-finally
  (('|finally| java-block)
   (finally 2)))

(def-java-grammar-category java-primary
  (java-primary-no-new-array 1)
  (java-array-creation-expression 1))

#+no ;automatically generated
(def-java-grammar-category java-primary-no-new-array
  (java-literal 1)
  ('|this| |this|)
  (('\( java-expression '\))
   (primary-no-new-array 2))
  (java-class-instance-creation-expression 1)
  (java-field-access 1)
  (java-method-invocation 1)
  (java-array-access 1)
  ((java-class-type '\. '|this|)
   (primary-no-new-array 1))
  ((java-type '\. '|class|)
   (primary-no-new-array 1))
  (('|void| '\. '|class|)))

;;hand
(def-java-grammar-category java-primary-no-new-array
  (java-literal 1)
  ('|this| |this|)
  (('\( java-expression '\))
   2)
  (java-class-instance-creation-expression 1)
  (java-field-access 1)
  (java-method-invocation 1)
  (java-array-access 1)
  ((java-class-type '\. '|this|)
   (inner-class-access 1))
  ((java-type '\. '|class|)
   (class-access 1))
  (('|void| '\. '|class|)
   (class-access void)))

#+no ;automatically generated
(def-java-grammar-category java-class-instance-creation-expression
  (('|new| java-class-type '\( '\))
   (class-instance-creation-expression 2))
  (('|new| java-class-type '\( '\) java-class-body)
   (class-instance-creation-expression 2 5))
  (('|new| java-class-type '\( java-argument-list '\))
   (class-instance-creation-expression 2 4))
  (('|new| java-class-type '\( java-argument-list '\) java-class-body)
   (class-instance-creation-expression 2 4 6))
  ((java-primary-or-name '\. '|new| java-identifier '\( '\))
   (class-instance-creation-expression 1 4))
  ((java-primary-or-name '\. '|new| java-identifier '\( '\) java-class-body)
   (class-instance-creation-expression 1 4 7))
  ((java-primary-or-name '\. '|new| java-identifier '\( java-argument-list '\))
   (class-instance-creation-expression 1 4 6))
  ((java-primary-or-name '\. '|new| java-identifier
    '\( java-argument-list '\) java-class-body)
   (class-instance-creation-expression 1 4 6 8)))

;;hand
(def-java-grammar-category java-class-instance-creation-expression
  (('|new| java-class-type '\( '\))
   (class-instance-creation-expression 2 ()))
  (('|new| java-class-type '\( '\) java-class-body)
   (class-instance-creation-expression 2 () 5))
  (('|new| java-class-type '\( java-argument-list '\))
   (class-instance-creation-expression 2 4))
  (('|new| java-class-type '\( java-argument-list '\) java-class-body)
   (class-instance-creation-expression 2 4 6))
  ((java-primary-or-name '\. '|new| java-identifier '\( '\))
   (class-instance-creation-expression 4 () nil 1))
  ((java-primary-or-name '\. '|new| java-identifier '\( '\) java-class-body)
   (class-instance-creation-expression 4 () 7 1))
  ((java-primary-or-name '\. '|new| java-identifier '\( java-argument-list '\))
   (class-instance-creation-expression 4 6 nil 1))
  ((java-primary-or-name '\. '|new| java-identifier
    '\( java-argument-list '\) java-class-body)
   (class-instance-creation-expression 4 6 8 1)))

(def-java-grammar-category java-primary-or-name
  (java-primary 1)
  (java-name 1))

(def-java-grammar-category java-argument-list
  (java-expression 1)
  ((java-argument-list '\, java-expression)
   (argument-list 1 3)
   simplify-associative-operation))

(def-java-grammar-category java-array-creation-expression
  (('|new| java-primitive-type java-dim-exprs)
   (array-creation-expression 2 3))
  (('|new| java-primitive-type java-dim-exprs java-dims)
   (array-creation-expression 2 3 4))
  (('|new| java-class-or-interface-type java-dim-exprs)
   (array-creation-expression 2 3))
  (('|new| java-class-or-interface-type java-dim-exprs java-dims)
   (array-creation-expression 2 3 4))
  (('|new| java-type java-dims java-array-initializer)
   (array-creation-expression 2 3 4)))

(def-java-grammar-category java-dim-exprs
  (java-dim-expr 1)
  ((java-dim-exprs java-dim-expr)
   (dim-exprs 1 2)
   simplify-associative-operation))

(def-java-grammar-category java-dim-expr
  (('\[ java-expression '\])
   (dim-expr 2)))

(def-java-grammar-category java-dims
  (('\[ '\]))
  ((java-dims '\[ '\])
   (dims 1)))

(def-java-grammar-category java-field-access
  ((java-primary '\. java-identifier)
   (field-access 1 3))
  (('|super| '\. java-identifier)
   (field-access (super) 3))) ;(field-access 3))) ;hand

#+no ;automatically generated
(def-java-grammar-category java-method-invocation
  ((java-name '\( '\))
   (method-invocation 1))
  ((java-name '\( java-argument-list '\))
   (method-invocation 1 3))
  ((java-primary '\. java-identifier '\( '\))
   (method-invocation 1 3))
  ((java-primary '\. java-identifier '\( java-argument-list '\))
   (method-invocation 1 3 5))
  (('|super| '\. java-identifier '\( '\))
   (method-invocation 3))
  (('|super| '\. java-identifier '\( java-argument-list '\))
   (method-invocation 3 5)))

;;hand
(def-java-grammar-category java-method-invocation
  ((java-name '\( '\))
   (method-invocation 1 (argument-list)))
  ((java-name '\( java-argument-list '\))
   (method-invocation 1 3))
  ((java-primary '\. java-identifier '\( '\))
   (method-invocation (primary 1) 3 (argument-list)))
  ((java-primary '\. java-identifier '\( java-argument-list '\))
   (method-invocation (primary 1) 3 5))
  (('|super| '\. java-identifier '\( '\))
   (method-invocation (primary super) 3 (argument-list)))
  (('|super| '\. java-identifier '\( java-argument-list '\))
   (method-invocation (primary super) 3 5)))

(def-java-grammar-category java-array-access
  ((java-name '\[ java-expression '\])
   (array-access 1 3))
  ((java-primary-no-new-array '\[ java-expression '\])
   (array-access 1 3)))

(def-java-grammar-category java-postfix-expression
  (java-primary 1)
  (java-name 1)
  (java-post-increment-expression 1)
  (java-post-decrement-expression 1))

(def-java-grammar-category java-post-increment-expression
  ((java-postfix-expression '++)
   (post-increment-expression 1)))

(def-java-grammar-category java-post-decrement-expression
  ((java-postfix-expression '--)
   (post-decrement-expression 1)))

(def-java-grammar-category java-unary-expression
  (java-pre-increment-expression 1)
  (java-pre-decrement-expression 1)
  (('\+ java-unary-expression)
   (unary-expression 2))
  (('\- java-unary-expression)
   (unary-expression 2))
  (java-unary-expression-not-plus-minus 1))

(def-java-grammar-category java-pre-increment-expression
  (('++ java-unary-expression)
   (pre-increment-expression 2)))

(def-java-grammar-category java-pre-decrement-expression
  (('-- java-unary-expression)
   (pre-decrement-expression 2)))

(def-java-grammar-category java-unary-expression-not-plus-minus
  (java-postfix-expression 1)
  (('~~ java-unary-expression)
   (unary-expression-not-plus-minus 2))
  (('\! java-unary-expression)
   (unary-expression-not-plus-minus 2))
  (java-cast-expression 1))

(def-java-grammar-category java-cast-expression
  (('\( java-primitive-type '\) java-unary-expression)
   (cast-expression 2 4))
  (('\( java-primitive-type java-dims '\) java-unary-expression)
   (cast-expression 2 3 5))
  (('\( java-expression '\) java-unary-expression-not-plus-minus)
   (cast-expression 2 4))
  (('\( java-name java-dims '\) java-unary-expression-not-plus-minus)
   (cast-expression 2 3 5)))

(def-java-grammar-category java-multiplicative-expression
  (java-unary-expression 1)
  ((java-multiplicative-expression '\* java-unary-expression)
   (* 1 3)
   simplify-associative-operation)
  ((java-multiplicative-expression '\/ java-unary-expression)
   (/ 1 3)
   simplify-associative-operation)
  ((java-multiplicative-expression '\% java-unary-expression)
   (% 1 3)
   simplify-associative-operation))

(def-java-grammar-category java-additive-expression
  (java-multiplicative-expression 1)
  ((java-additive-expression '\+ java-multiplicative-expression)
   (+ 1 3)
   simplify-associative-operation)
  ((java-additive-expression '\- java-multiplicative-expression)
   (- 1 3)
   simplify-associative-operation))

(def-java-grammar-category java-shift-expression
  (java-additive-expression 1)
  ((java-shift-expression '<< java-additive-expression)
   (<< 1 3)
   simplify-associative-operation)
  ((java-shift-expression '>> java-additive-expression)
   (>> 1 3)
   simplify-associative-operation)
  ((java-shift-expression '>>> java-additive-expression)
   (>>> 1 3)
   simplify-associative-operation))

(def-java-grammar-category java-relational-expression
  (java-shift-expression 1)
  ((java-relational-expression '\< java-shift-expression)
   (< 1 3)
   simplify-associative-operation)
  ((java-relational-expression '\> java-shift-expression)
   (> 1 3)
   simplify-associative-operation)
  ((java-relational-expression '<= java-shift-expression)
   (<= 1 3)
   simplify-associative-operation)
  ((java-relational-expression '>= java-shift-expression)
   (>= 1 3)
   simplify-associative-operation)
  ((java-relational-expression '|instanceof| java-reference-type)
   (|instanceof| 1 3)
   simplify-associative-operation))

(def-java-grammar-category java-equality-expression
  (java-relational-expression 1)
  ((java-equality-expression '== java-relational-expression)
   (== 1 3)
   simplify-associative-operation)
  ((java-equality-expression '!= java-relational-expression)
   (!= 1 3)
   simplify-associative-operation))

(def-java-grammar-category java-and-expression
  (java-equality-expression 1)
  ((java-and-expression '\& java-equality-expression)
   (& 1 3)
   simplify-associative-operation))

(def-java-grammar-category java-exclusive-or-expression
  (java-and-expression 1)
  ((java-exclusive-or-expression '\^ java-and-expression)
   (^ 1 3)
   simplify-associative-operation))

(def-java-grammar-category java-inclusive-or-expression
  (java-exclusive-or-expression 1)
  ((java-inclusive-or-expression '\| java-exclusive-or-expression)
   (\| 1 3)
   simplify-associative-operation))

(def-java-grammar-category java-conditional-and-expression
  (java-inclusive-or-expression 1)
  ((java-conditional-and-expression '&& java-inclusive-or-expression)
   (&& 1 3)
   simplify-associative-operation))

(def-java-grammar-category java-conditional-or-expression
  (java-conditional-and-expression 1)
  ((java-conditional-or-expression '\|\| java-conditional-and-expression)
   (\|\| 1 3)
   simplify-associative-operation))

(def-java-grammar-category java-conditional-expression
  (java-conditional-or-expression 1)
  ((java-conditional-or-expression '\? java-expression
    '\: java-conditional-expression)
   (conditional-expression 1 3 5)))

(def-java-grammar-category java-assignment-expression
  (java-conditional-expression 1)
  (java-assignment 1))

(def-java-grammar-category java-assignment
  ((java-left-hand-side java-assignment-operator java-assignment-expression)
   (assignment 1 2 3)))

(def-java-grammar-category java-left-hand-side
  (java-name 1)
  (java-field-access 1)
  (java-array-access 1))

(def-java-grammar-category java-assignment-operator
  ('\= =) ;('\=) ;hand
  ('*= *=)
  ('/= /=)
  ('%= %=)
  ('+= +=)
  ('-= -=)
  ('<<= <<=)
  ('>>= >>=)
  ('>>>= >>>=)
  ('&= &=)
  ('^= ^=)
  ('\|= \|=))

(def-java-grammar-category java-expression
  (java-assignment-expression 1))

(def-java-grammar-category java-constant-expression
  (java-expression 1))

;;; End of 3-semi block generated by emit-transformed-java-grammar.

;;;; Java Tokenizing Terminals

;;; Following def-grammar-category forms are hand-generated, and assume the use
;;; of java-tokenizer rather than g2-standard-tokenizer.

(def-grammar-category java-identifier ()
  (java-symbol 1 (unreserved-java-identifier? 1)))

(def-global-property-name java-reserved-word-p)

(defun unreserved-java-identifier? (symbol pattern)
  (declare (ignore pattern))
  (if (java-reserved-word-p symbol)
      (values bad-phrase 'reserved-java-word)
      (values (phrase-list 'identifier symbol) nil)))

(declare-grammar-transform-can-return-bad-phrase unreserved-java-identifier?)

(def-grammar-category java-integer-literal ()
  (integer (integer 1)))

(def-grammar-category java-floating-point-literal ()
  (float (float 1)))

(def-grammar-category java-boolean-literal ()
  ('|true| (boolean true))
  ('|false| (boolean false)))

(def-grammar-category java-string-literal ()
  (whole-string (string 1)))

(def-grammar-category java-null-literal ()
  ('|null| (java-null)))

;;;; Java Tokenizing Parameters

;;; The following parameters are an ad hoc collection in various formats,
;;; including list of uppercase symbols, list of lowercase symbols,
;;; gensym-strings of special operators.  They are primarily designed to work
;;; conveniently with the Java tokenizer, but they secondarily might be useful
;;; elsewhere.  At least look here first before making your own parameters that
;;; deal with Java operators and reserved words.

(defun make-character-range-from-sorted-list-of-character-codes (char-codes)
  (loop with this-min = (car char-codes)
	with this-max = this-min
	for char-code in (cdr char-codes)
	with accum = nil
	do
    (cond
      ((= char-code (1+ this-max))
       (setq this-max char-code))
      (t (push (cons this-min this-max) accum)
	 (setq this-min char-code)
	 (setq this-max char-code)))
	finally (return (reverse (cons (cons this-min this-max) accum)))))

(defparameter must-quote-g2-symbol-character-class
  (make-character-range-from-sorted-list-of-character-codes
    alphabet-nonsymbol-character-codes-sorted-by-encoding))

;; jh, 7/17/97.  From _The Java Language Specification_, Gosling, Joy, Steele,
;; pp 440 ff.  For complete accuracy, we need to exclude the "undefined" codes
;; per whatever UNICODE version we are using.

(defparameter unicode-letter-or-digit-possibly-undefined-character-class
  (mapcar #'(lambda (entry)
	      (cons
		(coerce-to-wide-character (car entry))
		(coerce-to-wide-character (cdr entry))))
	  '((#x0024 . #x0024) ;p 18 adds dollar sign $ for "legacy" integration
	    (#x0030 . #x0039)
	    (#x0041 . #x005A)
	    (#x005F . #x005F) ;p 18 adds underscore _ for "historical" reasons
	    (#x0061 . #x007A)
	    (#x00C0 . #x00D6)
	    (#x00D8 . #x00F6)
	    (#x00F8 . #x00FF)
	    (#x0100 . #x1FFF)
	    (#x3040 . #x9FFF)
	    (#xF900 . #xFDFF)
	    (#xFE70 . #xFEFE)
	    (#xFF10 . #xFF19)
	    (#xFF21 . #xFF3A)
	    (#xFF41 . #xFF5A)
	    (#xFF66 . #xFFDC))))

;; jh, 7/17/97.  From _The Java Language Specification_, Gosling, Joy, Steele,
;; pp 440 ff.  For complete accuracy, we need to exclude the "undefined" codes
;; per whatever UNICODE version we are using.

(defparameter unicode-digit-possibly-undefined-character-class
  (mapcar #'(lambda (entry)
	      (cons
		(coerce-to-wide-character (car entry))
		(coerce-to-wide-character (cdr entry))))
	  '((#x0030 . #x0039)
	    (#x0660 . #x0669)
	    (#x06F0 . #x06F9)
	    (#x0966 . #x096F)
	    (#x09E6 . #x09EF)
	    (#x0A66 . #x0A6F)
	    (#x0AE6 . #x0AEF)
	    (#x0B66 . #x0B6F)
	    (#x0BE7 . #x0BEF)
	    (#x0C66 . #x0C6F)
	    (#x0CE6 . #x0CEF)
	    (#x0D66 . #x0D6F)
	    (#x0E50 . #x0E59)
	    (#x0ED0 . #x0ED9)
	    (#xFF10 . #xFF19))))

;;; The function `character-range-difference' conses, and is therefore suitable
;;; only for one-shot evaluation at run time, say for parameter initialization.

(defun-simple character-class-difference (character-class-1 character-class-2)
  (loop with accum = nil
	with (min-1? . max-1) = (pop character-class-1)
	with (min-2? . max-2) = (pop character-class-2)
	while (and min-1? min-2?)
	do
    (cond
      ;; Ceiling of gap is beneath floor of original range - get next gap.
      ((> min-1? max-2)
       (destructuring-setq (min-2? . max-2) (pop character-class-2)))
      ;; Floor of gap is above ceiling of original range, so retain original.
      ((< max-1 min-2?)
       (push (cons min-1? max-1) accum)
       (destructuring-setq (min-1? . max-1) (pop character-class-1)))
      ;; Gap is properly contained in range.
      ((and (< min-1? min-2?) (> max-1 max-2))
       (push (cons min-1? (1- min-2?)) accum)
       (setq min-1? (1+ max-2))
       (destructuring-setq (min-2? . max-2) (pop character-class-2)))
      ;; Ceiling of gap is within original range, floor of gap overlaps..
      ((> max-1 max-2)
       (setq min-1? (1+ max-2))
       (destructuring-setq (min-2? . max-2) (pop character-class-2)))
      ;; Floor of gap is within original range, ceiling of gap overlaps.
      ((< min-1? min-2?)
       (push (cons min-1? (1- min-2?)) accum)
       (destructuring-setq (min-1? . max-1) (pop character-class-1)))
      ;; Gap completely overlaps original range.
      (t (destructuring-setq (min-1? . max-1) (pop character-class-1))))
	finally (return (append (reverse accum)
				(and min-1? (list (cons min-1? max-1)))
				character-class-1))))

(defparameter java-identifier-start-character-class
  (character-class-difference
    unicode-letter-or-digit-possibly-undefined-character-class
    unicode-digit-possibly-undefined-character-class))

(defparameter java-identifier-quote-free-start-character-class
  (character-class-difference
    java-identifier-start-character-class
    must-quote-g2-symbol-character-class))

(defparameter java-identifier-part-character-class
  unicode-letter-or-digit-possibly-undefined-character-class)

(defparameter java-identifier-quote-free-part-character-class
  (character-class-difference
    java-identifier-part-character-class
    must-quote-g2-symbol-character-class))

(defun convert-java-separators-or-operators-to-seq-tokens
    (string-of-operators)
  (loop for index from 0 below (length string-of-operators)
	for this-char = (char string-of-operators index)
	with operators = nil
	with operator? = nil
	do
    (cond
      ((member this-char '(#\Space #\Tab #\Newline) :test #'equal)
       (when operator?
	 (push 
	   `(seq
	      ,@(loop for component-char in (reverse operator?)
		      collect
		      (coerce-to-wide-character component-char)))
	   operators)
	 (setq operator? nil)))
      (t (push this-char operator?)))
	finally
	  (return
	    (reverse
	      (if operator?
		  (cons `(seq
			   ,@(loop for component-char in (reverse operator?)
				   collect
				   (coerce-to-wide-character component-char)))
			operators)
		  operators)))))

(defun-for-macro convert-java-separators-or-operators-to-list-of-strings
    (conglomerated-string)
  (flet ((collect (these-chars)
	   (let* ((string-length (length these-chars))
		  (operator-string (make-string string-length)))
	     (loop for index from (1- string-length) downto 0
		   do
	       (setf (char operator-string index) (pop these-chars)))
	     operator-string)))
    (loop for index from 0 below (length conglomerated-string)
	  for this-char = (char conglomerated-string index)
	  with these-chars? = nil
	  with these-strings = nil
	  do
      (cond
	((member this-char '(#\Space #\Tab #\Newline) :test #'eql)
	 (when these-chars?
	   (push (collect these-chars?) these-strings)
	   (setq these-chars? nil)))
	(t (push this-char these-chars?)))
	  finally
	    (when these-chars?
	      (push (collect these-chars?) these-strings))
	   (return (reverse these-strings)))))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter java-separators-as-conglomerated-string
  ;; From _The Java Language Specification_, Gosling, Joy, Steele, p 27.
  "( ) { } [ ] ; , .")
)

(defparameter-for-macro java-operators-as-string
  (convert-java-separators-or-operators-to-list-of-strings
    java-separators-as-conglomerated-string))

(defparameter java-single-character-constituent-operators-as-string
  ;; From _The Java Language Specification_, Gosling, Joy, Steele, p 28.
  "= > < ! + - * / & \| ^ %")

(defparameter java-single-character-nonconstituent-operators-as-string
  ;; From _The Java Language Specification_, Gosling, Joy, Steele, p 28.
  "~ ? :")

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter java-single-character-operators-as-conglomerated-string
  ;; From _The Java Language Specification_, Gosling, Joy, Steele, p 28.
  "= > < ! ~ ? : + - * / & \| ^ %")
)

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter java-multi-character-operators-as-conglomerated-string
  ;; From _The Java Language Specification_, Gosling, Joy, Steele, p 28
  "==  <=  >=  != && \|\| ++ -- <<  >>  >>>
   +=  -=  *=  /= &= \|=  ^= %= <<= >>= >>>=")
)

(defparameter-for-macro java-separators-as-string
  (append
    (convert-java-separators-or-operators-to-list-of-strings
      java-single-character-operators-as-conglomerated-string)
    (convert-java-separators-or-operators-to-list-of-strings
      java-multi-character-operators-as-conglomerated-string)))

(defparameter newline-chars-for-java-tokens
  (make-character-range-from-sorted-list-of-character-codes
    (sort
      (remove-duplicates
	'(#.%return #.%linefeed #.%newline #.%line-separator)
	:test #'=)
      #'<)))

(defparameter java-escape-character-literal-alist
  '((#.%\b b)
    (#.%\t t)
    (#.%\n n)
    (#.%\f f)
    (#.%\r r)
    (#.%\" double-quote)
    (#.%\' single-quote)
    (#.%\\ backslash)))

(defparameter java-octal-character-literal-alist
  '((#.%\0 0)
    (#.%\1 1)
    (#.%\2 2)
    (#.%\3 3)
    (#.%\4 4)
    (#.%\5 5)
    (#.%\6 6)
    (#.%\7 7)))

(def-token-action tokenize-java-character-literal (string start end)
  (let* ((first-char (charw string (1+f start)))
	 (second-char (charw string (+f start 2)))
	 (escape-p (char=w first-char #.%\\ )))
    (cond
      ((and escape-p
	    (loop for (escape-char name)
		      in java-escape-character-literal-alist
		  thereis
		  (and (char=w escape-char second-char)
		       (phrase-list 'character-literal 'escape name)))))
      (escape-p
       (loop for index from 2 below (1-f end)
	     for this-char = (charw string index)
	     with char-code = 0
	     do	 
	 (let ((value?
		 (loop for (octal-char value)
			   in java-octal-character-literal-alist
		       thereis
		       (and (char=w octal-char this-char) value))))
	   (cond
	     (value? (setq char-code (+f (*f char-code 8) value?)))
	     (t #+development
		(cerror
		  "go on"
		  "reached the unreachable ~
                   while tokenizing JAVA-CHARACTER-LITERAL")
	        (return (phrase-list 'bad-character-literal)))))
	     finally
	       (return (phrase-list 'character-literal 'octal char-code))))
      (t (phrase-list 'character-literal 'simple second-char)))))

(def-token-action tokenize-bad-java-character-literal (string start end)
  (declare (ignore string start end))
  (phrase-list 'bad-character-literal))

(defparameter java-half-octal-characters '(#.%\0 #.%\1 #.%\2 #.%\3))

;;;; Java Tokenizer

(defparameter java-tokens
  `(((java-letter
       (character-class ,java-identifier-start-character-class))
     (java-letter-quote-free
       (character-class ,java-identifier-quote-free-start-character-class))
     (java-letter-or-digit
       (character-class ,java-identifier-part-character-class))
     (java-letter-or-digit-quote-free
       (character-class ,java-identifier-quote-free-part-character-class))
     (java-digit
       (character-class ,unicode-digit-possibly-undefined-character-class))
     (string-char (inverted-class (#.%\" #.%\\)))
     (simple-character-literal (inverted-class (#.%\' #.%\\)))
     (escape-character-literal
       (either ,@(mapcar #'car java-escape-character-literal-alist)))
     (octal-character-literal
       (either ,@(mapcar #'car java-octal-character-literal-alist)))
     (half-octal-character-literal (either ,@java-half-octal-characters))
     (bad-escape-character-literal
       (inverted-class
	 (,@(mapcar #'car java-escape-character-literal-alist)
	  ,@(mapcar #'car java-octal-character-literal-alist))))
     (bad-octal-character-literal
       (inverted-class
	 (#.%\' ,@(mapcar #'car java-octal-character-literal-alist))))
     (newline-char (character-class ,newline-chars-for-java-tokens))
     (char-within-single-line-comment
       (inverted-class ,newline-chars-for-java-tokens))
     (hex-digit-char
       (character-class ((#.%\0 . #.%\9) (#.%\A . #.%\F) (#.%\a . #.%\f)))))
    (do-nothing
      (either
	(plus (either (pattern newline-char)
	              #.%paragraph-separator #.%space #.%tab))
	(seq #.%\/ #.%\/
	     (kleene (pattern char-within-single-line-comment))
	     (pattern newline-char))
	(seq #.%\/ #.%\*
	     (kleene
	       (seq (kleene (inverted-class (#.%\*)))
		    (maybe (seq #.%\* (inverted-class (#.%\/))))))
	     #.%\* #.%\/)))
    (comment ;actually, everything except a definite termination sequence
      (either
	(seq #.%\/ #.%\/
	     (kleene (pattern char-within-single-line-comment)))
	(seq #.%\/ #.%\*
	     (kleene
	       (seq (kleene (inverted-class (#.%\*)))
		    (maybe (seq #.%\* (inverted-class (#.%\/))))))))
      no-value)
    (disambiguated-token ;ambiguity because / might precede non-comment char
      (seq #.%\/ (inverted-class (#.%\/ #.%\* #.%\=))))
    (integer
      (seq
	;; Note that + and - are always binary operators, not constituents of
	;; integer literals (Java Language Specification, p 21).  This differs
	;; from G2 practice.
	;;(maybe (either #.%\+ #.%\-))
	(either (plus (pattern java-digit))
		(seq #.%\0
		     (either #.%\x #.%\X)
		     (plus (pattern hex-digit-char))))
	(maybe (either #.%\L #.%\l)))
      numeric-return-value)
    (float
      (seq
	;; Note that + and - are always binary operators, not constituents of
	;; float literals (Java Language Specification, p 21).  This differs
	;; from G2 practice.
	;; (maybe (either #.%\+ #.%\-))
	(either
	  (seq (plus (pattern java-digit))
	       (seq (either #.%\E #.%\e) (maybe (either #.%\+ #.%\-))
		    (plus (pattern java-digit))))
	  (seq (plus (pattern java-digit))
	       #.%\. (kleene (pattern java-digit))
	       (maybe (seq (either #.%\E #.%\e)
			   (maybe (either #.%\+ #.%\-))
			   (plus (pattern java-digit)))))
	  (seq #.%\. (plus (pattern java-digit))
	       (maybe (seq (either #.%\E #.%\e)
			   (maybe (either #.%\+ #.%\-))
			   (plus (pattern java-digit))))))
	(maybe (either #.%\F #.%\f #.%\D #.%\d)))
      numeric-return-value)
    (java-symbol
      (either
	(seq
	  (plus (either (pattern java-letter-quote-free)
			(seq #.%\@ (pattern java-letter))))
	  (kleene (either (pattern java-letter-or-digit-quote-free)
			  (seq #.%\@ (pattern java-letter-or-digit)))))
	,@(convert-java-separators-or-operators-to-seq-tokens
	    java-single-character-constituent-operators-as-string)
	,@(convert-java-separators-or-operators-to-seq-tokens
	   java-multi-character-operators-as-conglomerated-string))
      alphabet-case-sensitive-symbol-from-text-string)
    (whole-string
     (seq #.%\"
	  (kleene (either (seq #.%\\ (dot))
			  (pattern string-char)))
	  #.%\")
     alphabet-strip-delimitors-off-string)
    (java-character-literal
      (seq #.%\'
	   (either
	     (pattern simple-character-literal)
	     (seq #.%\\ (pattern escape-character-literal))
	     (seq #.%\\
		  (either
		    (pattern octal-character-literal)
		    (seq (pattern octal-character-literal)
			 (pattern octal-character-literal))
		    (seq (pattern half-octal-character-literal)
			 (pattern octal-character-literal)
			 (pattern octal-character-literal)))))
	   #.%\')
      tokenize-java-character-literal)
    ;; jh, 8/25/97.  Character literals are the only sort of token where we can
    ;; collect more than one character, then decide that the whole thing is bad.
    ;; Hence we need bad-java-character-literal as a catchall to prevent us from
    ;; falling off the end.
    (bad-java-character-literal
      (either 
	(seq #.%\' #.%\')
	(seq
	  #.%\'
	  (pattern simple-character-literal)
	  (inverted-class (#.%\')))
	(seq #.%\' #.%\\
	     (either (pattern bad-escape-character-literal)
		     (seq (pattern escape-character-literal)
			  (inverted-class (#.%\')))
		     (seq (pattern octal-character-literal)
			  (pattern bad-octal-character-literal))
		     (seq (pattern octal-character-literal)
			  (pattern octal-character-literal)
			  (pattern bad-octal-character-literal))
		     (seq (either #.%\4 #.%\5 #.%\6 #.%\7)
			  (pattern octal-character-literal)
			  (pattern octal-character-literal))
		     (seq (pattern half-octal-character-literal)
			  (pattern octal-character-literal)
			  (pattern octal-character-literal)
			  (inverted-class (#.%\'))))))
      tokenize-bad-java-character-literal)
    (self-terminating-punctuation-mark
     (either
       ,@(convert-java-separators-or-operators-to-seq-tokens
	   java-separators-as-conglomerated-string)
       ,@(convert-java-separators-or-operators-to-seq-tokens
	   java-single-character-nonconstituent-operators-as-string)
       ))))

(def-lexing-table java-tokenizer java-tokens)

;;;; Java Grammar Prompts

;; From _The Java Language Specification_, Gosling, Joy, Steele, pp 440 ff.,
;; Collected from Chapter 3.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter java-reserved-words-as-uppercase-symbols
  '(abstract boolean break byte case catch char class const continue
    default do double else extends final finally float for goto
    if implements import instanceof int interface long native new package
    private protected public return short static super switch synchronized this
    throw throws transient try void volatile while))
)

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter java-reserved-words-as-string
  (mapcar #'(lambda (x) (string-downcase (symbol-name x)))
	  java-reserved-words-as-uppercase-symbols))
)

(defun-simple intern-java-reserved-word-as-category (reserved-word)
  (let ((reserved-word-as-lowercase-category
	  (intern-for-java-grammar
	    (string-downcase (symbol-name reserved-word)))))
    (setf (java-reserved-word-p reserved-word-as-lowercase-category) t)
    reserved-word-as-lowercase-category))

(defparameter java-reserved-words-as-lowercase-categories
  (loop for symbol in java-reserved-words-as-uppercase-symbols
	collect
	(intern-java-reserved-word-as-category symbol)))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter java-reserved-expressions-as-lowercase-categories
  '(|true| |false| |null|))
)
(loop for reserved-expression
	  in java-reserved-expressions-as-lowercase-categories
      do (setf (java-reserved-word-p reserved-expression) t))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter java-reserved-expressions-as-string
  (mapcar #'symbol-name java-reserved-expressions-as-lowercase-categories))
)

;; jh, 7/29/97.  We need the following form so that java-import-declaration can
;; distinguish between java-single-type-import-declaration and
;; java-type-import-on-demand-declaration.
(intern-java-reserved-word-as-category '*)

;;; The function `convert-java-separators-or-operators-to-symbols' conses, and
;;; is therefore suitable only for one-shot evaluation at run time, say for
;;; variable initialization.

(defun-simple convert-java-separators-or-operators-to-symbols
    (string-of-operators)
  (loop for index from 0 below (length string-of-operators)
	for this-char = (char string-of-operators index)
	with operators = nil
	with operator? = nil
	do
    (cond
      ((member this-char '(#\Space #\Tab #\Newline) :test #'equal)
       (when operator?
	 (push
	   (intern-for-java-grammar
	     (twith-output-to-gensym-string
	       (loop for component-char in (reverse operator?)
		     do
		 (twrite-character component-char))))
	   operators)
	 (setq operator? nil)))
      (t (push this-char operator?)))
	finally
	  (return
	    (reverse
	      (if operator?
		  (cons
		    (intern-for-java-grammar
		      (twith-output-to-gensym-string
			(loop for component-char in (reverse operator?)
			      do
			  (twrite-character component-char))))
		    operators)
		  operators)))))

(defparameter java-separators-as-categories
  (convert-java-separators-or-operators-to-symbols
    java-separators-as-conglomerated-string))

(defparameter java-operators-as-categories
  (append
    (convert-java-separators-or-operators-to-symbols
      java-single-character-operators-as-conglomerated-string)
    (convert-java-separators-or-operators-to-symbols
      java-multi-character-operators-as-conglomerated-string)))

(defvar java-editing-categories
  '(java-compilation-unit-or-none
    java-class-body-declarations-or-none))

(defun-simple java-editing-category-p (category)
  (memq category java-editing-categories))

(defun-simple copy-symbol-name-of-possible-java-reserved-word
    (symbol do-not-downcase?)
  (cond
    ((java-editing-category-p
       (cadr (type-of-slot-being-edited current-edit-state)))
     (case symbol
       ;; I.e., the only Java symbol whose printname has been munged into UTF-G.
       ;; See intern-for-java-grammar.
       (~~ (copy-wide-string #w"~"))
       (otherwise (copy-symbol-name symbol nil))))
    (t (copy-symbol-name-parsably symbol do-not-downcase?))))

(defun set-token-menu-string-to-display-for-java-reserved-words ()
  (loop for category
	    in (append
		 java-reserved-words-as-lowercase-categories
		 java-reserved-expressions-as-lowercase-categories
		 java-separators-as-categories
		 java-operators-as-categories)
	do (set-token-menu-string-to-display-function
	     category
	     #'copy-symbol-name-of-possible-java-reserved-word)))

(set-token-menu-string-to-display-for-java-reserved-words)

;;;; Dealing With "None" in Java-Parsing Class

;; Following grammar categories are hand-written.  The rationale is that we want
;; to to prevent its slot from wedging into a requirement for non-empty text
;; after the first edit.

(def-grammar-category java-compilation-unit-or-none ()
  (java-compilation-unit 1)
  ('|none| none))

(def-grammar-category java-class-body-declarations-or-none ()
  (java-class-body-declarations 1)
  ('|none| none))

;; jh, 7/29/97.  "none" is not a Java reserved word, but a convenience for G2
;; users who want to put empty text into attributes that hold Java source code.
(set-token-menu-string-to-display-function
  '|none|
  #'copy-symbol-name-of-possible-java-reserved-word)


;;;; Attribute Export for Java-Parsing Class

(define-category-evaluator-interface (java-class-and-interface-names
				       :access read)
    (sequence text 0)
  ((get-form (slot-value?))
   (allocate-evaluation-sequence
     (loop for class-or-interface-name in slot-value?
	   collect (make-evaluation-text class-or-interface-name)
	     using eval-cons))))

(def-slot-value-writer java-class-and-interface-names (slot-value)
  (twrite-list slot-value :conjoiner ", "))

(define-category-evaluator-interface (java-read-only-package-declaration
				       :access read)
    (sequence text 0)
  ((get-form (slot-value?))
   (allocate-evaluation-sequence
     (loop for component in slot-value?
	   collect (make-evaluation-text component)
	     using eval-cons))))

(defun-void twrite-java-qualified-name (components)
  (loop for component in components
	for component-cons on components
	do
    (twrite-string component)
    (when (cdr component-cons)
      (twrite-character #\.))))

(def-slot-value-writer java-read-only-package-declaration (slot-value?)
  (when slot-value?
    (twrite-string "package ")
    (twrite-java-qualified-name slot-value?)
    (twrite-character #\;)))

(define-category-evaluator-interface (java-read-only-import-declarations
				       :access read)
    (sequence (sequence text 0) 0)
  ((get-form (slot-value?))
   (allocate-evaluation-sequence
     (loop for each-import in slot-value?
	   collect
	   (allocate-evaluation-sequence
	     (loop for component in each-import
		   collect
		   (make-evaluation-text component)
		     using eval-cons))
	     using eval-cons))))

(def-slot-value-writer java-read-only-import-declarations (slot-value?)
  (loop for import in slot-value?
	for import-cons on slot-value?
	do
    (twrite-string "import ")
    (twrite-java-qualified-name import)
    (twrite-character #\;)
    (when (cdr import-cons)
      (twrite-line-break))))

(defmacro export-external-java-class-attribute (category)
  `(define-text-category-evaluator-interface ,category t))

(export-external-java-class-attribute java-compilation-unit-or-none)

;;;; Slot-putters for Java-Parsing Class

(define-slot-alias text compilation-unit external-java-class)

;; jh, 9/16/97.  At some stage during development of the on-board Java parser,
;; we maintained the package-declaration and import-declarations slots as
;; independent text slots.  Now we slave them to the new compilation-unit slot,
;; so we have to extract the old text here and do something with it.  Since we
;; only released the version with the independent slots internally, we can
;; settle for "just" printing the lost information in the logbook.  Note that
;; the slaved slots have the correct information under these circumstances, but
;; it is out-of-synch with the main text body.

(defun-void preserve-information-from-former-java-text-slot
    (external-java-class old-text-value)
  (let ((old-text-string (convert-text-to-text-string old-text-value)))
    (unless (=f (text-string-length old-text-string) 0)
      (notify-user-if-possible
	"Information lost when loading 5.0 beta KB.~%~
         Please re-enter the following into the main text body of ~NF:~%~A"
	external-java-class
	old-text-string))
    (reclaim-text-string old-text-string)
    (reclaim-slot-value old-text-value)))

(defun-simple probable-text-p (maybe-text)
  (loop for maybe-text-element in maybe-text
	thereis
	(or (lost-spaces-value-if-any maybe-text-element)
	    (and (consp maybe-text-element)
		 (memq (car maybe-text-element) '(line-width))))))

(def-slot-putter package-declaration
    (external-java-class new-value? initializing-p)
  (cond
    ((and initializing-p
	  loading-kb-p
	  (consp new-value?)
	  (probable-text-p (cdr new-value?)))
     (let ((correct-value (slot-value-pop new-value?)))
       (setf (package-declaration external-java-class)
	     (get-package-declaration-components-if-any
	       correct-value))
       (when new-value?
	 (preserve-information-from-former-java-text-slot
	   external-java-class
	   new-value?))))
    (t (setf (package-declaration external-java-class) new-value?))))

(def-slot-putter import-declarations
    (external-java-class new-value? initializing-p)
  (cond
    ((and initializing-p
	  loading-kb-p
	  (consp new-value?)
	  (probable-text-p (cdr new-value?)))
     (let* ((correct-value (slot-value-pop new-value?))
	    (singleton-p nil)
	    (flattened-imports-tree
	      (and (consp correct-value)
		   (case (car correct-value)
		     (import-declarations (cdr correct-value))
		     ((type-import-on-demand single-type-import)
		      (setq singleton-p t)
		      (slot-value-list correct-value))
		     (otherwise nil))))
	    (import-declarations
	      (get-import-declarations-if-any flattened-imports-tree)))
       (when singleton-p
	 (reclaim-slot-value-list flattened-imports-tree))
       (setf (import-declarations external-java-class) import-declarations)
       (when new-value?
	 (preserve-information-from-former-java-text-slot
	   external-java-class
	   new-value?))))
    (t (setf (import-declarations external-java-class) new-value?))))

(def-slot-putter compilation-unit (external-java-class new-value)
  (when (and (consp new-value) (eq (car new-value) 'none))
    (let ((none-text (cdr new-value)))
      (reclaim-text none-text)
      (setf (cdr new-value) (make-empty-text))))
  (setf (compilation-unit external-java-class) new-value))

;; jh, 9/16/97.  At some stage during development of the on-board Java parser,
;; we only placed type-declarations in the main text of an external-java-class
;; and thus maintained the package-declaration and import-declarations slots as
;; separate text slots.  Now we slave them to the new compilation-unit slot.
;; This change requires a def-absent-slot-putter.

(def-absent-slot-putter type-declarations
    (external-java-class type-declarations)
  (setf (compilation-unit external-java-class) type-declarations))

;;;; Slot-value Compilers for Java-Parsing Class

(def-slot-value-compiler java-compilation-unit-or-none
    (java-syntax-tree external-java-class)
  (update-package-declaration-for-external-java-class
    external-java-class
    java-syntax-tree)
  (update-import-declarations-for-external-java-class
    external-java-class
    java-syntax-tree)
  ;; We must have updated the package-declaration attribute by the time we eval
  ;; the following form.
  (let ((class-name-symbols
	  (get-class-name-symbols-for-external-java-class java-syntax-tree))
	(package-components? (package-declaration external-java-class)))
    (update-names-for-external-java-class
      external-java-class
      class-name-symbols
      package-components?)
    (reclaim-slot-value-list class-name-symbols)
    java-syntax-tree))

;;;; Coordinating Package and Import Declarations with Main Text

(defun-simple get-canonical-java-name-as-new-slot-value (internal-name)
  (let* ((singleton-p (eq (first internal-name) 'identifier))
	 (components
	   (if singleton-p
	       (slot-value-list internal-name)
	       (cdr internal-name))))
    (loop for (nil component) in components
	  collect
	  (copy-text-string
	    (symbol-name-text-string component))
	    using slot-value-cons
	  finally (when singleton-p
		    (reclaim-slot-value-list components)))))

(defun-simple get-package-declaration-components-if-any (package-declaration)
  (and (consp package-declaration)
       (gensym-dstruct-bind ((nil internal-name) package-declaration)
	 (and (consp internal-name)
	      (get-canonical-java-name-as-new-slot-value internal-name)))))

(defun-void update-package-declaration-for-external-java-class
    (external-java-class compilation-unit-syntax-tree)
  (let* ((package-syntax-tree
	   (and (consp compilation-unit-syntax-tree)
		(case (car compilation-unit-syntax-tree)
		  (compilation-unit
		   (loop for thing in (cdr compilation-unit-syntax-tree)
			 thereis (and (consp thing)
				      (eq (car thing) 'package)
				      thing)))
		  (package compilation-unit-syntax-tree)
		  (otherwise nil))))
	 (package-declaration
	   (get-package-declaration-components-if-any
	     package-syntax-tree)))
    (change-slot-value
      external-java-class
      'package-declaration
      package-declaration)))

(defun-simple get-import-declarations-if-any (flattened-imports-tree)
  (let ((import-declarations
	  (loop for (nil internal-name) in flattened-imports-tree
		collect
		(get-canonical-java-name-as-new-slot-value internal-name)
		  using slot-value-cons)))
    (loop for (type) in flattened-imports-tree
	  for canonical-list in import-declarations
	  when (eq type 'type-import-on-demand)
	    do (setf (cdr (last canonical-list))
		     (slot-value-list (copy-constant-wide-string #w"*"))))
    import-declarations))

(defun-void update-import-declarations-for-external-java-class
    (external-java-class compilation-unit-syntax-tree)
  (let* ((singleton-p nil)
	 (flattened-imports-tree
	   (and (consp compilation-unit-syntax-tree)
		(case (car compilation-unit-syntax-tree)
		  (compilation-unit
		   (loop for thing in compilation-unit-syntax-tree
			 do
		     (when (consp thing)
		       (case (car thing)
			 (import-declarations
			  (return (cdr thing)))
			 ((type-import-on-demand single-type-import)
			  (setq singleton-p t)
			  (return (slot-value-list thing)))))))
		  (import-declarations (cdr compilation-unit-syntax-tree))
		  ((type-import-on-demand single-type-import)
		   (setq singleton-p t)
		   (slot-value-list compilation-unit-syntax-tree))
		  (otherwise nil))))
	 (import-declarations
	   (get-import-declarations-if-any flattened-imports-tree)))
    (when singleton-p
      (reclaim-slot-value-list flattened-imports-tree))
    (change-slot-value
      external-java-class
      'import-declarations
      import-declarations)))



;;;; Coordinating G2 and Java Names

;;; The system procedure `convert-mixed-case-text-to-hyphenated-symbol' takes as
;;; input a text-string and converts it to a hyphenated symbol suitable for
;;; mapping between IDL and G2 names.  This procedure uses two heuristics:
;;;   (1) A new hypenated component is created at a transition between lower and
;;;       upper-case, for instance "HiThere" yields hi-there.
;;;   (2) A new hyphenated component is created if a sequence of 2 or more
;;;       upper-case characters is followed by a lower-case character.  The
;;;       hypenated component consists of all characters except the final
;;;       character, whilst the final character is the first character of the
;;;       next hyphenated component.  For instance "GSIObj" yields gsi-obj.
;;;       This heuristic is intended to capture how mixed-case names contain
;;;       acronyms.

(defun-simple upper-case-alpha-char-pw (char)
  (and (alpha-char-pw char) (upper-case-pw char)))

(defun-simple lower-case-alpha-char-pw (char)
  (and (alpha-char-pw char) (lower-case-pw char)))

(defun-for-system-procedure convert-mixed-case-text-to-hyphenated-symbol
    (mixed-case-text)
  (loop for index from 0 below (text-string-length mixed-case-text)
	for previous-char? = nil then this-char
	for this-char = (charw mixed-case-text index)
	with this-subsequence? = nil
	with all-subsequences = nil
	do
    (cond
      ;; Start a new hyphenated component at the transition from lower to
      ;; uppercase.
      ((and (upper-case-alpha-char-pw this-char)
	    previous-char?
	    (lower-case-alpha-char-pw previous-char?))
       (token-push (nreverse this-subsequence?) all-subsequences)
       (setq this-subsequence? (token-list this-char)))
      ;; If we have gathered a sequence of 2 or more uppercase characters, and
      ;; detect a transition from upper to lowercase, assume all characters
      ;; except the last are an acronym and group them.
      ((and (lower-case-alpha-char-pw this-char)
	    previous-char?
	    (upper-case-alpha-char-pw previous-char?)
	    (let ((char-before-previous-char? (second this-subsequence?)))
	      (and char-before-previous-char?
		   (upper-case-alpha-char-pw char-before-previous-char?))))
       (let ((initial-upcased-char (car this-subsequence?))
	     (acronym-subsequence (cdr this-subsequence?)))
	 (reclaim-token-cons this-subsequence?)	 
	 (token-push (nreverse acronym-subsequence) all-subsequences)
	 (setq this-subsequence? (token-list this-char initial-upcased-char))))
      ;; Otherwise, this character belongs to the same hyphenated component as
      ;; the previous character.
      (t (token-push this-char this-subsequence?)))
	finally
	  (when this-subsequence?
	    (token-push (nreverse this-subsequence?) all-subsequences))
	  (nreversef all-subsequences)
	  (reclaim-evaluation-text mixed-case-text)
	  (return
	    (intern-text-string
	      (twith-output-to-text-string
		(loop for subsequence in all-subsequences
		      for subsequence-cons on all-subsequences
		      for last-subsequence-p = (null (cdr subsequence-cons))
		      do
		  (loop for char in subsequence
			do (twrite-char (char-upcasew char))	      
			finally (unless last-subsequence-p (twrite-char #\-)))
		  (reclaim-token-list subsequence)
		      finally (reclaim-token-list all-subsequences)))))))


(defun-simple make-g2-name-for-java-class (java-class-name package-components)
  (intern-text-string
    (twith-output-to-text-string
      (loop for component in package-components
	    do
	(twrite-symbol
	  (convert-mixed-case-text-to-hyphenated-symbol
	    (copy-text-string component))
	  t)
	(twrite-character #\.))
      (twrite-symbol
	(convert-mixed-case-text-to-hyphenated-symbol
	  (copy-text-string (symbol-name-text-string java-class-name)))
	t))))

(defun-simple get-class-name-symbols-for-external-java-class
    (java-syntax-tree)
  (if (or (eq java-syntax-tree bad-phrase)
	  (eq java-syntax-tree 'none))
      nil
      (and (consp java-syntax-tree)
	   (let ((flattened-list-of-class-subtrees
		   (cond
		     ((memq (car java-syntax-tree) '(class interface))
		      (phrase-list java-syntax-tree))
		     ((eq (car java-syntax-tree) 'type-declarations)
		      (cdr java-syntax-tree))
		     (t (loop for subtree in java-syntax-tree
			      thereis
			      (and (consp subtree)
				   (eq (car subtree) 'type-declarations)
				   (cdr subtree)))))))
	     (loop for subtree in flattened-list-of-class-subtrees
		   with accum = nil
		   do
	       (when (and (consp subtree)
			  (memq (car subtree) '(class interface)))
		 (let ((java-class-name?
			 (loop for class-info in subtree
			       thereis
			       (and (consp class-info)
				    (eq (car class-info) 'identifier)
				    (cadr class-info)))))
		   (when java-class-name?
		     (slot-value-push java-class-name? accum))))
		   finally (return (nreverse accum)))))))

(defun-void update-g2-side-names-for-external-java-class
    (external-java-class class-name-symbols package-components?)
  (when (derive-names-automatically? external-java-class)
    (cond
      ((or (null class-name-symbols) (cdr class-name-symbols))
       (let ((new-names
	       (loop for java-class-name in class-name-symbols
		     collect
		     (make-g2-name-for-java-class
		       java-class-name
		       package-components?)
		       using slot-value-cons)))
	 (change-slot-value
	   external-java-class
	   'name-or-names-for-frame
	   new-names)))
      (t (change-slot-value
	   external-java-class
	   'name-or-names-for-frame
	   (make-g2-name-for-java-class
	     (car class-name-symbols)
	     package-components?))))))

(defun-void update-java-side-names-for-external-java-class
    (external-java-class class-name-symbols package-components?)
  (let* ((package-prefix?
	   (and package-components?
		(twith-output-to-text-string
		  (loop for component in package-components?
			do
		    (twrite-string component)
		    (twrite-character #\.)))))
	 (java-class-or-interface-names
	   (loop for java-class-name in class-name-symbols
		 collect
		 (twith-output-to-text-string
		   (when package-prefix?
		     (twrite-string package-prefix?))
		   (twrite-symbol java-class-name t))
		   using slot-value-cons)))
    (change-slot-value
      external-java-class
      'java-class-and-interface-names
      java-class-or-interface-names)
    (when package-prefix?
      (reclaim-text-string package-prefix?))))

(defun-void update-names-for-external-java-class
    (external-java-class class-name-symbols package-components?)
  ;; Fill in G2-side names, if the end-user has permitted it.
  (update-g2-side-names-for-external-java-class
    external-java-class
    class-name-symbols
    package-components?)  
  ;; Fill in Java-side names unconditionally, as they are read-only and of
  ;; more general utility than the G2-side names.
  (update-java-side-names-for-external-java-class
    external-java-class
    class-name-symbols
    package-components?))

;;;; Object-passing Machinery for Java-parsing Class

(defun-simple instantiable-secret-java-class-p (class)
  (and (get-instance-with-name-if-any 'procedure 'g2-new-secret-entity)
       (memq class
	     '(external-java-class
	       external-procedure
	       external-method-declaration
	       external-method
	       export-definition))))

;;;; Installing Frame Notes Into Java-Parsing Class

;;; The system procedure `operate-on-javac-frame-notes' takes the following
;;; arguments:

;;; java-instance: The item whose frame notes are to be modified.  Currently
;;;   must be an instance of external-java-class alone, but we might permit
;;;   other Java-related class in future.  Note that this procedure is not a
;;;   general way to install frame notes into a frame.  That would amount to
;;;   providing a setter for the virtual attribute item-notes, and would
;;;   therefore require a lot more design discussion than this one-off, which is
;;;   intended for internal use only.

;;; type-of-operation: A symbol naming the type of operation, one of
;;;   replace-javac-frame-notes, add-javac-frame-notes, or remove-javac-frame-notes.
;;;   As of Java 1.1, javac output is of the following general form:
;;;     <class-name>.java: <maybe-multiline-message>
;;;     <offending-source-line>
;;;     <caret-line>
;;;   where the caret in <caret-line> marks the location in
;;;   <offending-source-line> that corresponds most closely to the problem.
;;;   Since javac typically outputs in a fixed-width font, whereas G2 does
;;;   not. the system procedure operate-on-javac-frame-notes will heuristically
;;;   search for <caret-line> and replace it with a string "<!>" inserted into
;;;   <source-line> just before the character to which the caret points.

;;;   Behavior for individual values of type-of-operation is as follows:

;;;   replace-javac-frame-notes - remove all java-related frame notes and
;;;   install the notes given by operation-info, which for instances of
;;;   external-java-class should be G2 text corresponding to javac output.

;;;   add-javac-frame-notes - retain the current frame note and add the notes
;;;   given by operation-info, which for instances of external-java-class should
;;;   be G2 text corresponding to javac output.

;;;   delete-javac-frame-notes - remove all Java-related frame notes from the
;;;   item.  The operation-info argument must be supplied (jh, 9/11/97: since
;;;   the time is not right to design "system methods" analogous to "system
;;;   procedures"), but it is ignored.

;;; operation-info - an item or value whose nature depends on type-of-operation
;;;   (vide supra).

;;; This procedure returns a single argument, a truth-value indicating whether
;;; or not the requested operation succeeded.

(defparameter caret-replacement-for-javac-problem "<!>")

(defun-simple newline-text-string-character-p (wchar)
  (or (char=w wchar #.%return)
      (char=w wchar #.%linefeed)
      (char=w wchar #.%newline)
      (char=w wchar #.%line-separator)))

(defun-simple whitespace-text-string-character-p (wchar)
  (or (newline-text-string-character-p wchar)
      (char=w wchar #.%space)
      (char=w wchar #.%tab)))

(defun-simple problem-header-in-javac-problem-p (line)
  (gensym-search #w".java:" line))

;; jh, 9/9/97.  The function caret-position-in-javac-problem-line-if-any does
;; not handle the pathological cases of (1) an error being reported on a line
;; with nothing except the Jave exclusive-or operator or (2) more than one caret
;; on a line.

(defun-simple caret-position-in-javac-problem-line-if-any (line)
  (loop for index from 0 below (text-string-length line)
	for this-wchar = (charw line index)
	with position? = nil
	do
    (cond
      ((char=w this-wchar #.%space))
      ((char=w this-wchar #.%^) (setq position? index))
      (t (return nil)))
	finally (return position?)))

;; jh, 9/11/97.  On the theory that any documentation of
;; get-next-javac-problem-if-any is better than none:
;;
;; caret header last-line lines-accum'd  remarks
;; ----- ------ --------- -------------  -------
;; 0     0      0         0              do nothing
;; 0     0      0         1              push onto lines-accum'd
;; 0     0      1         0              return no string & nil
;; 0     0      1         1              push onto lines-accum'd, return string & nil
;; 0     1      0         0              push onto lines-accum'd
;; 0     1      0         1              return string & previous index
;; 0     1      1         0              push onto lines-accum'd, return string & nil
;; 0     1      1         1              don't push, return string & previous index
;; 1     0      0         0              don't push, record caret point
;; 1     0      0         1              don't push, record caret point
;; 1     0      1         0              return no string & nil
;; 1     0      1         1              record caret, return string & current index
;; 1     1      ...                      impossible -- line can't be both caret & header

(defun get-next-javac-problem-if-any
    (problems-text-string inclusive-start-index)
  (loop with length = (text-string-length problems-text-string)
	with lines-for-this-problem? = nil
	for previous-newline-index = inclusive-start-index
	    then (1+f this-newline-index?)
	for this-newline-index?
	    = (loop for line-index from previous-newline-index below length
		    for this-wchar = (charw problems-text-string line-index)
		    when (newline-text-string-character-p this-wchar)
		      do (return line-index)
		    finally (return nil))
	for no-more-lines-p = (null this-newline-index?)
	for this-line = (text-string-substring problems-text-string
			  previous-newline-index
			  (or this-newline-index? length))
	for caret-position-in-this-line?
	    = (caret-position-in-javac-problem-line-if-any this-line)
	with source-line? = nil
	with caret-index? = nil
	with next-inclusive-start-index? = nil
	for coalesce-p = nil
	do
    (cond
      (caret-position-in-this-line?
       (unless (=f caret-position-in-this-line? 0)
	 (setq caret-index? caret-position-in-this-line?)
	 (setq source-line? (java-pop lines-for-this-problem?)))
       (when no-more-lines-p
	 (setq coalesce-p (and lines-for-this-problem? t)))
       (reclaim-text-string this-line))
      ((problem-header-in-javac-problem-p this-line)
       (cond
	 (lines-for-this-problem?
	  (reclaim-text-string this-line)
	  (setq coalesce-p t)
	  (unless no-more-lines-p
	    (when (<f previous-newline-index length)
	      (setq next-inclusive-start-index? previous-newline-index))))
	 (t (java-push this-line lines-for-this-problem?)
	    (when no-more-lines-p
	      (setq coalesce-p t)))))
      (lines-for-this-problem?
       (unless (loop for index from 0 below (text-string-length this-line)
		     for this-wchar = (charw this-line index)
		     always (whitespace-text-string-character-p this-wchar))
	 (java-push this-line lines-for-this-problem?))
       (when no-more-lines-p
	 (setq coalesce-p t)))
      (t (reclaim-text-string this-line)))
    (cond
      (coalesce-p
       (nreversef lines-for-this-problem?)
       (return
	 (values
	   (twith-output-to-text-string
	     (loop for line in lines-for-this-problem?
		   do
	       (unless (=f (text-string-length line) 0)
		 (twrite-string line)
		 (twrite-line-break))
	       (reclaim-text-string line)
		   finally
		     (reclaim-java-list lines-for-this-problem?))
	     (when (and caret-index? source-line?)
	       (let ((before
		       (text-string-substring source-line?
			 0
			 caret-index?))
		     (after
		       (text-string-substring source-line?
			 caret-index?
			 (text-string-length source-line?))))
		 (twrite-string before)
		 (twrite-string caret-replacement-for-javac-problem)
		 (twrite-string after)
		 (reclaim-text-string before)
		 (reclaim-text-string after)
		 (reclaim-text-string source-line?))))
	   next-inclusive-start-index?)))
      (no-more-lines-p
       (return (values nil nil))))))
  
(defun-for-system-procedure operate-on-javac-frame-notes
    (java-instance type-of-operation operation-info)
  (prog ((succeeded-p nil))
     ;; Make sure we are operating on a permissible class
     (frame-class-case java-instance
       ((external-java-class
	  ;; Add other Java-related class as needed here.
	  ))
       (otherwise (go exit-point)))

     ;; Validate the operation and its info.
     (case type-of-operation
       ((replace-javac-frame-notes add-javac-frame-notes)
	(cond
	  ((text-string-p operation-info))
	  ((and (framep operation-info)
		(frame-of-class-p operation-info 'text-parameter))
	   (let ((*current-computation-frame* operation-info)
		 (current-computation-flags current-computation-flags))
	     (setf (force-new-request-for-value) nil)
	     (setf (dont-compute-new-variable-values) t)
	     (setq operation-info
		   (get-current-evaluation-value operation-info nil))))
	  (t (go exit-point))))
       (delete-javac-frame-notes)
       (otherwise (go exit-point)))

     ;; Do the operation.
     (case type-of-operation
       ((replace-javac-frame-notes delete-javac-frame-notes)
	(delete-frame-note-if-any
	  'java-compilation-problems
	  java-instance)
	(case type-of-operation
	  (delete-javac-frame-notes (setq succeeded-p t)))))
     (case type-of-operation
       ((replace-javac-frame-notes add-javac-frame-notes)
	(loop with next-index? = 0
	      while next-index?
	      with problem?
	      with at-least-one-p = nil
	      do
	  (multiple-value-setq (problem? next-index?)
	    (get-next-javac-problem-if-any
	      operation-info
	      next-index?))
	      while problem? do
	  (add-to-frame-note-particulars-list-if-necessary
	    problem?
	    'java-compilation-problems
	    java-instance)
	  (setq at-least-one-p t)
	      finally (when at-least-one-p
			(setq succeeded-p t)))))

     (go exit-point) ;defense against cut-and-paste development

     exit-point
     ;; Clean up
     (case type-of-operation
       ((replace-javac-frame-notes add-javac-frame-notes)
	(when (text-string-p operation-info)
	  (reclaim-evaluation-text operation-info)))
       (delete-frame-note-if-any
	(when (evaluation-value-p operation-info)
	  (reclaim-evaluation-value operation-info))))       
     (if succeeded-p
	 (return (copy-evaluation-truth-value evaluation-true-value))
	 (return (copy-evaluation-truth-value evaluation-false-value)))))

(def-frame-note-writer java-compilation-problems (compilation-problems)
  (cond
    ((cdr compilation-problems)
     (twrite-string
       "the following problems were encountered during compilation: ")
     (twrite-line-break)
     (loop for compilation-problem in compilation-problems
	   for compilation-problem-cons on compilation-problems
	   for index from frame-note-index
	   do
       (tformat "(~A) " index)
       (twrite-string compilation-problem)
       (when (cdr compilation-problem-cons)
	 (twrite-line-break))
       finally (setq frame-note-index (1+f index))))
    (t (twrite-string "a problem was encountered during compilation: ")
       (twrite-line-break)
       (twrite-string (car compilation-problems)))))




