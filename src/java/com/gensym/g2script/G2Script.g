header {
        package com.gensym.g2script;
	}
options {
	language="Java";
}

{ import java.io.*; }
class G2ScriptParser extends Parser;
options {
	k = 2;
	//	tokdef = "G2Script.tokdef";
	importVocab = G2Script;
	
	codeGenMakeSwitchThreshold = 2;
	codeGenBitsetTestThreshold = 999;
	defaultErrorHandler = false;
	buildAST = true;
	
}

{
	//class Main {
	public static void main(String[] args) throws Exception {
		try {
			AntlrTokenizer lexer 
	                  = new AntlrTokenizer(new InputStreamReader(System.in));
			G2ScriptParser parser = new G2ScriptParser(lexer);
			parser.compilationUnit();
		}
		catch(Exception e) {
			System.err.println("exception: "+e);
			e.printStackTrace();
			throw e;   // so we can get stack trace
		}
	}
//}
}



				/* PRODUCTIONS */

compilationUnit
	:       procedurePrototype
	        (returnType)?
		(variableDeclarations)?
		compoundStatement
		EOF	        
	;

procedurePrototype!
	:	id:UNRESERVED arglist:prototypeArglist
		{ #procedurePrototype = #([UNRESERVED,"PROTOTYPE"], id, arglist); }
	;

prototypeArglist
	:	LPAREN! arglist:(prototypeArg
				(COMMA! prototypeArg)*)? RPAREN!
	;

prototypeArg!
	:	id:UNRESERVED COLON t:typeDeclaration 
		{ #prototypeArg = #([UNRESERVED,"ARG"], id, t); }
	;

returnType
	:	EQUALS^ LPAREN! (typeDeclaration)? RPAREN!
	;
	
variableDeclarations!
	:	decls:variableDeclarationList
		{ #variableDeclarations = #([UNRESERVED,"LOCALS"], decls); }
	;

variableDeclarationList
	:	list: ((singleVariableDeclaration | multipleVariableDeclaration )+)
	;
			

multipleVariableDeclaration!
	:	arglist:localNameList COLON type:typeDeclaration  SEMICOLON
		{ #multipleVariableDeclaration = #([UNRESERVED,"MULTIPLE_LOCAL"], type, arglist); }
	;

localNameList
	:	list:(UNRESERVED (COMMA! UNRESERVED)+)
	;

singleVariableDeclaration!
	:	id:UNRESERVED COLON! type:typeDeclaration (EQUALS^ expr:expression)? SEMICOLON!
		{ #singleVariableDeclaration = #([UNRESERVED,"SINGLE_LOCAL"], type, id, expr); }
	;

rule
	:	wheneverRule
	|	unconditionallyRule
	|	ifRule
	|	whenRule
	;

wheneverRule
	:	WHENEVER^ wheneverConditions (wheneverFilter)? THEN! consequent
	;

wheneverConditions!
	:	list:wheneverConditionList
		{ #wheneverConditions = #([UNRESERVED,"CONDITIONS"], list); }
	;

wheneverConditionList
	:	list:(eventDisjunct (OR! eventDisjunct)*)
	;

wheneverFilter
	:	AND! WHEN^ expression
	;

// Generic event syntax
// any foo f has a bar event ee 
eventDisjunct
	:	designation 
		(	RECEIVES^ A! VALUE!
		|	HAS^ (A! | AN!) UNRESERVED EVENT ! (localName)?)
	;

consequent!
	:	list:actionList
		{ #consequent = #([UNRESERVED,"ACTIONS"], list); }
	;

ifRule
	:	IF^ expression THEN! consequent
	;

whenRule
	:	WHEN^ expression THEN! consequent
	;

unconditionallyRule
	:	UNCONDITIONALLY^ consequent
	;

actionList
	:	(IN! ORDER)? action (AND! action)*
	;

typeDeclaration
	:	INTEGER
	|	FLOAT
	|       QUANTITY
	|	TEXT
	|	SYMBOL
	|	TRUTH_VALUE
	|	SEQUENCE
	|	STRUCTURE
	|	VALUE
	|	ITEM_OR_VALUE
	|	CLASS^ classOrAttributeName
	;

classOrAttributeName
	:	UNRESERVED | OBJECT | EVENT 
	// list:(UNRESERVED (PERIOD! (UNRESERVED | CLASS | 
	//		OBJECT | EVENT | INTEGER))*)
	;

compoundStatement
	:	BEGIN^ compoundStatementTail
		(ON! ERROR! LPAREN! localName COMMA! localName RPAREN!
		 compoundStatementTail) ?
	;

compoundStatementTail!
	:	statements:statementList (SEMICOLON)? END
		{ #compoundStatementTail = #([UNRESERVED,"BLOCK"], statements); }
	|	(SEMICOLON)? END
		{ #compoundStatementTail = #([UNRESERVED,"BLOCK"]); }
	;

statementList
	:	statements:(statement (SEMICOLON! statement)*)
	;

statement
	:	simpleStatement
	|	ifThenElseStatement
	;

simpleStatement
	:	(UNRESERVED EQUALS CALL) =>
		UNRESERVED EQUALS^ call 
	|	UNRESERVED EQUALS^ expression 
	|	call 
	|	compoundStatement
	| 	returnStatement
	|       forStatement
	|       repeatStatement
	|       exitIfStatement
	|	action
	|	allowOtherProcessingStatement
	|	signalStatement
	|	waitStatement
	;

action
	:	createAction
	|	deleteAction
	|	informAction
	|	startAction
	|       concludeAction
	|       changeColorAction
	;

changeColorAction
	:	CHANGE^ THE! UNRESERVED ICON_COLOR! OF! designation 
			TO! UNRESERVED
	;

startAction
	:       START^ (UNRESERVED | staticMethodReference) argumentList
		  (prioritySuffix)?
		  (delaySuffix) ?
	;

prioritySuffix
	:	AT! PRIORITY^ conjunct // don't allow AND|OR in expression
	;

delaySuffix
	:	AFTER^ conjunct // don't allow AND|OR in expression
	;

deleteAction
	:	DELETE^ designation
	;

concludeAction
	:	CONCLUDE^ THAT! designation 
		  ( EQUALS conjunct | HAS NO VALUE )  // don't allow AND|OR in expression
	;

createAction
	:	CREATE^ (A! | AN!) classNameExpression UNRESERVED
	;

informAction
	:	INFORM^ THE! OPERATOR! THAT! 
		  (formatForm | WHOLE_STRING_LITERAL)
	;

ifThenElseStatement
	:	IF^ expression THEN! simpleStatement (ELSE! statement)?
	;

call
	:	CALL^ ((UNRESERVED 
			| methodNamesThatShouldntBeReserved
			| staticMethodReference) 
			argumentList
		|	NEW constructorArgumentList)
	;

methodNamesThatShouldntBeReserved
	:	CREATE
	;

forStatement
	:	FOR^ localName forIterationSpec DO!
			compoundStatementTail
	;

forIterationSpec
	:	EQUALS^ expression (TO | DOWN TO!)
			expression (BY! expression)?
	|	EQUALS! EACH^ typeExpression
			( IN designation )?  // eventually more cases
	;

allowOtherProcessingStatement
	:	ALLOW^ OTHER! PROCESSING!
	;

signalStatement
	:	SIGNAL^ expression (COMMA! expression)?
	;

staticMethodReference 
	:	THE! (PROCEDURE! | METHOD!) NAMED! BY! 
			THE! UNRESERVED OF^ THE! CLASS_METHODS! OF! classNameExpression
	;

returnStatement
	:	RETURN^ (expression)?
	;

repeatStatement
	:	REPEAT^ compoundStatementTail
	;

exitIfStatement
	:	EXIT^ IF! expression
	;		

waitStatement
	:	WAIT^ FOR! 
	(		(quantityInterval)=> 
			quantityInterval
	|		conjunct)
	;

classNameExpression!
	: 	spec:classOrAttributeName
		{ #classNameExpression  = #([UNRESERVED,"CLASS"], spec); }
	;

argumentList
	:	LPAREN! arglist:(expression (COMMA! expression)*)? RPAREN!
	;

constructorArgumentList
	:	LPAREN! arglist:(classNameExpression COMMA! expression (COMMA! expression)*) RPAREN!
	;

expression
	:	disjunct (OR^ disjunct)*
	;

disjunct
	:	conjunct (AND^ conjunct)*
	;

conjunct
	:	NOT^ LPAREN! expression RPAREN!
	|	(designation (IS (TRUTH_VALUE_LITERAL | (NOT)? (THE | A | AN)) 
	| 			EXISTS 
	| 			DOES)) =>
		designationPredicate
	|	sumExpression (((EQUALS^ | GREATER^ | LESS^ | NOT_EQUAL^ | GREATER_EQUAL^ | LESS_EQUAL^) 
				sumExpression)* 
	|		       IS^ (NOT)? UNRESERVED)
	|	formatForm
	|	THERE^ EXISTS! (A! | AN!)
			typeExpression (localName)? (IN designation)?
			(SUCH THAT! LPAREN! expression RPAREN)?
	;

designationPredicate
	:	designation 
	(		IS^ 
	(			TRUTH_VALUE_LITERAL 
	|			(NOT)? THE! SAME! OBJECT AS! designation 
	|			(NOT)? (A! | AN!) typeExpression )
	|		EXISTS^
	|		DOES! NOT EXIST^)
	;

typeExpression
	:	INTEGER
	|	FLOAT
	|       QUANTITY
	|	TEXT
	|	SYMBOL
	|	TRUTH_VALUE
	|	SEQUENCE
	|	STRUCTURE
	|	VALUE
	|	ITEM_OR_VALUE
	|	classNameExpression
	;

sumExpression
	:	(termOrSignedTerm PLUS) =>
		termOrSignedTerm PLUS^ sumExpressionTail
	|	(termOrSignedTerm MINUS) =>
		termOrSignedTerm MINUS^ sumExpressionTail
	|	termOrSignedTerm
	;

termOrSignedTerm
	:	MINUS^ term
	|	PLUS^ term
	|	term
	;

sumExpressionTail
	:	(term PLUS) =>
		term PLUS^ sumExpressionTail
	|	(term MINUS) =>
		term MINUS^ sumExpressionTail
	|	term
	;

term
	:	factor tail:((TIMES^ | SLASH^) factor)*
	;

factoid
	:	constant
	|	LPAREN! expression RPAREN!
	;

factor 
	:	(constant) =>
		constant
	|!      (functionName LPAREN) =>
		id:functionName args:argumentList
		{ #factor = #([UNRESERVED,"FUNCTION_CALL"], id, args); }
	|	// The following is a crackpot scheme to compute follow sets by hand.
		// (	UNRESERVED (LBRACK | designationFollower)
		// |	LPAREN (THE | UNRESERVED | LPAREN) 
		// |	THE UNRESERVED OF) =>
		(designation) =>
		designation 
	|	THE! NUMBER! OF! ELEMENTS^ IN! designation
	|	sequenceConstructor
	|	structureConstructor
	|	LPAREN! expression RPAREN!
	|	timeExpression
	;

functionName
	:	UNRESERVED | SYMBOL | QUANTITY | TIME 
	|	MINUTE | HOUR | SECOND
	;

designationFollower
	:	EQUALS | GREATER | LESS | NOT_EQUAL | GREATER_EQUAL | LESS_EQUAL 
	|	PLUS | TIMES | MINUS | SLASH
	|	HAS | IS | EXISTS | DOES
	|	AND | OR
	|	BY | TO | DOWN | DO | END   // "delete designation end"
	|	COMMA | SEMICOLON
	|	THEN
	|	RIGHT_STRING_LITERAL | MIDDLE_STRING_LITERAL 
	;

sequenceConstructor
	:	SEQUENCE^ LPAREN! (expression (COMMA! expression)*)? RPAREN!
	;

structureConstructor
	:	STRUCTURE^ LPAREN! (UNRESERVED COLON! expression
		  (COMMA! UNRESERVED COLON! expression)*)? RPAREN!
	;

designation
	:!	d1:localName LBRACK exp1:expression RBRACK
		{ #designation = #([UNRESERVED,"ARRAY_REFERENCE"], d1, exp1); }
	|!	LPAREN d2:designation RPAREN LBRACK exp2:expression RBRACK
		{ #designation = #([UNRESERVED,"ARRAY_REFERENCE"], d2, exp2); }
	|	THE! classOrAttributeName (localName)? 
	(		OF^ (designation | THE! CLASS_FIELDS! OF! classNameExpression)
	|		CONNECTED^ connectionSpec 
	|		UPON^ designation)
	|	localName
	|	ANY^ classNameExpression (localName)?
	;

connectionSpec
	: 	TO^ designation
	|	AT^ (THE! | AN!) 
			  (INPUT|OUTPUT|UNRESERVED) (OF!|TO!) designation
	;


timeExpression
	:	THE! CURRENT! (REAL | SUBSECOND REAL) TIME^
	;

localName!
	:	id:UNRESERVED
		{ #localName = #([UNRESERVED,"LOCAL_REFERENCE"], id); }
	;


formatForm!
	:	left:LEFT_STRING_LITERAL first:expression 
		   list:formatList right:RIGHT_STRING_LITERAL
		{ #formatForm = #([UNRESERVED,"FORMAT_FORM"], left, first, list, right); }
	;

formatList
	:	list:(MIDDLE_STRING_LITERAL expression)*
	;


constant
	:	INTEGER_LITERAL
	|	FLOAT_LITERAL
	|	TRUTH_VALUE_LITERAL
	|	WHOLE_STRING_LITERAL
	|       symbolLiteral
	;

quantityInterval!
	:	interval:quantityIntervalWeeks
		{ #quantityInterval = #([UNRESERVED,"INTERVAL"], interval); }
	;

quantityIntervalWeeks
	:	quantityConstant (WEEK   | WEEKS)   (quantityIntervalDays)?
	|	quantityConstant (DAY    | DAYS )   (quantityIntervalHours)?
	|	quantityConstant (HOUR   | HOURS)   (quantityIntervalMinutes)?
	|	quantityConstant (MINUTE | MINUTES) (quantityIntervalSeconds)?
	|	quantityConstant (SECOND | SECONDS)
	;

quantityIntervalDays
	:	AND!
	(	quantityConstant (DAY    | DAYS )   (quantityIntervalHours)?
	|	quantityConstant (HOUR   | HOURS)   (quantityIntervalMinutes)?
	|	quantityConstant (MINUTE | MINUTES) (quantityIntervalSeconds)?
	|	quantityConstant (SECOND | SECONDS)
	)
	;

quantityIntervalHours
	:	AND!
	(	quantityConstant (HOUR   | HOURS)   (quantityIntervalMinutes)?
	|	quantityConstant (MINUTE | MINUTES) (quantityIntervalSeconds)?
	|	quantityConstant (SECOND | SECONDS)
	)
	;

quantityIntervalMinutes
	:	AND!
	(	quantityConstant (MINUTE | MINUTES) (quantityIntervalSeconds)?
	|	quantityConstant (SECOND | SECONDS)
	)
	;

quantityIntervalSeconds
	:	AND! quantityConstant (SECOND | SECONDS)
	;

timeKeyword
	:	WEEK | WEEKS | DAY | DAYS | HOUR | HOURS | MINUTE | MINUTES |
		SECOND | SECONDS
	;
		
quantityConstant 
	:	INTEGER_LITERAL | FLOAT_LITERAL
	;

symbolLiteral!
	:	THE! SYMBOL! id:UNRESERVED
		{ #symbolLiteral = #([UNRESERVED,"SYMBOL_LITERAL"], id); }
	;

// Query Support

queryDesignation
	:       queryItemName
	|	THE UNRESERVED OF localName
	|       EVERY UNRESERVED (localName)? queryRestrictions
	;

queryRestrictions
	:	queryDisjunct (OR queryDisjunct)*
	;

queryDisjunct
	:	queryConjunct (AND queryConjunct)*
	;

queryConjunct
	:	(NOT)? queryRestriction
	;

queryRestriction
	:	SUCH THAT conjunct // expression is ambiguous becuz of AND & OR
	|	CONTAINING THE (WORD | SYMBOL) (WHOLE_STRING_LITERAL | UNRESERVED)
	|	WITH 
	(		NOTES
	|		CHANGES LOGGED BY UNRESERVED (queryInterval)? )
	|	WHOSE STATUS IS frameStatus
	|	ASSIGNED TO (HIERARCHY OF)? MODULE UNRESERVED
	|	WHERE UNRESERVED ( queryComparator constant | 
				   TRUTH_VALUE_LITERAL | (NOT)? UNRESERVED)
	|	IN THE CATEGORY UNRESERVED
	|	WHICH HAS THE FOCAL (CLASS | OBJECT) UNRESERVED
	|	FOUND ON THE WORKSPACE
	;

queryInterval
	:	BEFORE date (AND AFTER date)?
	|	AFTER date
	;

date 
	:	INTEGER_LITERAL month INTEGER_LITERAL
	;

queryComparator
	:	(EQUALS | GREATER | LESS | NOT_EQUAL | GREATER_EQUAL | LESS_EQUAL) 
	;

frameStatus
	: 	ENABLED
	|	DISABLED 
	|	OK 
	|	INACTIVE
	|	BAD 
	|	INCOMPLETE 
	|	ACTIVE
	;

month 
	:	JAN
    	|	FEB 
    	| 	MAR
    	|	APR
	|	MAY
	|	JUN
    	| 	JUL
    	| 	AUG
    	|	SEP
    	|	OCT
    	|	NOV
    	|	DEC
	;

queryItemName
	:	localName
	;