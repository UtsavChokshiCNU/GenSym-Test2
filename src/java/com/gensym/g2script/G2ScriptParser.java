/*
 * ANTLR-generated file resulting from grammar G2Script.g
 * 
 * Terence Parr, MageLang Institute
 * with John Lilley, Empathy Software
 * ANTLR Version 2.6.0; 1996-1999
 */

        package com.gensym.g2script;
	
import java.io.IOException;
import java.nio.charset.Charset;
import java.util.Arrays;
import java.util.List;

import antlr.TokenBuffer;
import antlr.Token;
import antlr.TokenStream;
import antlr.ParserException;
import antlr.NoViableAltException;
import antlr.ParserSharedInputState;
import antlr.collections.AST;
import antlr.ASTPair;
import antlr.collections.impl.ASTArray;
 import java.io.*; 
public class G2ScriptParser extends antlr.LLkParser
       implements G2ScriptParserTokenTypes
 {

	//class Main {
	public static void main(String[] args) throws Exception {
		try {
			AntlrTokenizer lexer 
	                  = new AntlrTokenizer(new InputStreamReader(System.in, Charset.defaultCharset()));
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

protected G2ScriptParser(TokenBuffer tokenBuf, int k) {
  super(tokenBuf,k);
  tokenNames = _tokenNames;
}

public G2ScriptParser(TokenBuffer tokenBuf) {
  this(tokenBuf,2);
}

protected G2ScriptParser(TokenStream lexer, int k) {
  super(lexer,k);
  tokenNames = _tokenNames;
}

public G2ScriptParser(TokenStream lexer) {
  this(lexer,2);
}

public G2ScriptParser(ParserSharedInputState state) {
  super(state,2);
  tokenNames = _tokenNames;
}

	public final void compilationUnit() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST compilationUnit_AST = null;
		
		procedurePrototype();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		switch ( LA(1)) {
		case EQUALS:
		{
			returnType();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			break;
		}
		case UNRESERVED:
		case BEGIN:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		{
		switch ( LA(1)) {
		case UNRESERVED:
		{
			variableDeclarations();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			break;
		}
		case BEGIN:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		compoundStatement();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		AST tmp1_AST = null;
		if (inputState.guessing==0) {
			tmp1_AST = (AST)astFactory.create(LT(1));
			astFactory.addASTChild(currentAST, tmp1_AST);
		}
		match(Token.EOF_TYPE);
		compilationUnit_AST = (AST)currentAST.root;
		returnAST = compilationUnit_AST;
	}
	
	public final void procedurePrototype() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST procedurePrototype_AST = null;
		Token  id = null;
		AST id_AST = null;
		AST arglist_AST = null;
		
		id = LT(1);
		if (inputState.guessing==0) {
			id_AST = (AST)astFactory.create(id);
		}
		match(UNRESERVED);
		prototypeArglist();
		if (inputState.guessing==0) {
			arglist_AST = (AST)returnAST;
		}
		if ( inputState.guessing==0 ) {
			procedurePrototype_AST = (AST)currentAST.root;
			procedurePrototype_AST = (AST)astFactory.make( (new ASTArray(3)).add((AST)astFactory.create(UNRESERVED,"PROTOTYPE")).add(id_AST).add(arglist_AST));
			currentAST.root = procedurePrototype_AST;
			currentAST.child = procedurePrototype_AST!=null &&procedurePrototype_AST.getFirstChild()!=null ?
				procedurePrototype_AST.getFirstChild() : procedurePrototype_AST;
			currentAST.advanceChildToEnd();
		}
		returnAST = procedurePrototype_AST;
	}
	
	public final void returnType() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST returnType_AST = null;
		
		AST tmp2_AST = null;
		if (inputState.guessing==0) {
			tmp2_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp2_AST);
		}
		match(EQUALS);
		AST tmp3_AST = null;
		tmp3_AST = (AST)astFactory.create(LT(1));
		match(LPAREN);
		{
		switch ( LA(1)) {
		case INTEGER:
		case FLOAT:
		case TRUTH_VALUE:
		case TEXT:
		case SYMBOL:
		case CLASS:
		case QUANTITY:
		case SEQUENCE:
		case STRUCTURE:
		case VALUE:
		case ITEM_OR_VALUE:
		{
			typeDeclaration();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			break;
		}
		case RPAREN:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		AST tmp4_AST = null;
		tmp4_AST = (AST)astFactory.create(LT(1));
		match(RPAREN);
		returnType_AST = (AST)currentAST.root;
		returnAST = returnType_AST;
	}
	
	public final void variableDeclarations() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST variableDeclarations_AST = null;
		AST decls_AST = null;
		
		variableDeclarationList();
		if (inputState.guessing==0) {
			decls_AST = (AST)returnAST;
		}
		if ( inputState.guessing==0 ) {
			variableDeclarations_AST = (AST)currentAST.root;
			variableDeclarations_AST = (AST)astFactory.make( (new ASTArray(2)).add((AST)astFactory.create(UNRESERVED,"LOCALS")).add(decls_AST));
			currentAST.root = variableDeclarations_AST;
			currentAST.child = variableDeclarations_AST!=null &&variableDeclarations_AST.getFirstChild()!=null ?
				variableDeclarations_AST.getFirstChild() : variableDeclarations_AST;
			currentAST.advanceChildToEnd();
		}
		returnAST = variableDeclarations_AST;
	}
	
	public final void compoundStatement() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST compoundStatement_AST = null;
		
		AST tmp5_AST = null;
		if (inputState.guessing==0) {
			tmp5_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp5_AST);
		}
		match(BEGIN);
		compoundStatementTail();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		switch ( LA(1)) {
		case ON:
		{
			AST tmp6_AST = null;
			tmp6_AST = (AST)astFactory.create(LT(1));
			match(ON);
			AST tmp7_AST = null;
			tmp7_AST = (AST)astFactory.create(LT(1));
			match(ERROR);
			AST tmp8_AST = null;
			tmp8_AST = (AST)astFactory.create(LT(1));
			match(LPAREN);
			localName();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			AST tmp9_AST = null;
			tmp9_AST = (AST)astFactory.create(LT(1));
			match(COMMA);
			localName();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			AST tmp10_AST = null;
			tmp10_AST = (AST)astFactory.create(LT(1));
			match(RPAREN);
			compoundStatementTail();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			break;
		}
		case EOF:
		case SEMICOLON:
		case END:
		case ELSE:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		compoundStatement_AST = (AST)currentAST.root;
		returnAST = compoundStatement_AST;
	}
	
	public final void prototypeArglist() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST prototypeArglist_AST = null;
		AST arglist_AST = null;
		
		AST tmp11_AST = null;
		tmp11_AST = (AST)astFactory.create(LT(1));
		match(LPAREN);
		{
		switch ( LA(1)) {
		case UNRESERVED:
		{
			prototypeArg();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			_loop8:
			do {
				if ((LA(1)==COMMA)) {
					AST tmp12_AST = null;
					tmp12_AST = (AST)astFactory.create(LT(1));
					match(COMMA);
					prototypeArg();
					if (inputState.guessing==0) {
						astFactory.addASTChild(currentAST, returnAST);
					}
				}
				else {
					break _loop8;
				}
				
			} while (true);
			}
			break;
		}
		case RPAREN:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		AST tmp13_AST = null;
		tmp13_AST = (AST)astFactory.create(LT(1));
		match(RPAREN);
		prototypeArglist_AST = (AST)currentAST.root;
		returnAST = prototypeArglist_AST;
	}
	
	public final void prototypeArg() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST prototypeArg_AST = null;
		Token  id = null;
		AST id_AST = null;
		AST t_AST = null;
		
		id = LT(1);
		if (inputState.guessing==0) {
			id_AST = (AST)astFactory.create(id);
		}
		match(UNRESERVED);
		AST tmp14_AST = null;
		if (inputState.guessing==0) {
			tmp14_AST = (AST)astFactory.create(LT(1));
		}
		match(COLON);
		typeDeclaration();
		if (inputState.guessing==0) {
			t_AST = (AST)returnAST;
		}
		if ( inputState.guessing==0 ) {
			prototypeArg_AST = (AST)currentAST.root;
			prototypeArg_AST = (AST)astFactory.make( (new ASTArray(3)).add((AST)astFactory.create(UNRESERVED,"ARG")).add(id_AST).add(t_AST));
			currentAST.root = prototypeArg_AST;
			currentAST.child = prototypeArg_AST!=null &&prototypeArg_AST.getFirstChild()!=null ?
				prototypeArg_AST.getFirstChild() : prototypeArg_AST;
			currentAST.advanceChildToEnd();
		}
		returnAST = prototypeArg_AST;
	}
	
	public final void typeDeclaration() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST typeDeclaration_AST = null;
		
		switch ( LA(1)) {
		case INTEGER:
		{
			AST tmp15_AST = null;
			if (inputState.guessing==0) {
				tmp15_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp15_AST);
			}
			match(INTEGER);
			typeDeclaration_AST = (AST)currentAST.root;
			break;
		}
		case FLOAT:
		{
			AST tmp16_AST = null;
			if (inputState.guessing==0) {
				tmp16_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp16_AST);
			}
			match(FLOAT);
			typeDeclaration_AST = (AST)currentAST.root;
			break;
		}
		case QUANTITY:
		{
			AST tmp17_AST = null;
			if (inputState.guessing==0) {
				tmp17_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp17_AST);
			}
			match(QUANTITY);
			typeDeclaration_AST = (AST)currentAST.root;
			break;
		}
		case TEXT:
		{
			AST tmp18_AST = null;
			if (inputState.guessing==0) {
				tmp18_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp18_AST);
			}
			match(TEXT);
			typeDeclaration_AST = (AST)currentAST.root;
			break;
		}
		case SYMBOL:
		{
			AST tmp19_AST = null;
			if (inputState.guessing==0) {
				tmp19_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp19_AST);
			}
			match(SYMBOL);
			typeDeclaration_AST = (AST)currentAST.root;
			break;
		}
		case TRUTH_VALUE:
		{
			AST tmp20_AST = null;
			if (inputState.guessing==0) {
				tmp20_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp20_AST);
			}
			match(TRUTH_VALUE);
			typeDeclaration_AST = (AST)currentAST.root;
			break;
		}
		case SEQUENCE:
		{
			AST tmp21_AST = null;
			if (inputState.guessing==0) {
				tmp21_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp21_AST);
			}
			match(SEQUENCE);
			typeDeclaration_AST = (AST)currentAST.root;
			break;
		}
		case STRUCTURE:
		{
			AST tmp22_AST = null;
			if (inputState.guessing==0) {
				tmp22_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp22_AST);
			}
			match(STRUCTURE);
			typeDeclaration_AST = (AST)currentAST.root;
			break;
		}
		case VALUE:
		{
			AST tmp23_AST = null;
			if (inputState.guessing==0) {
				tmp23_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp23_AST);
			}
			match(VALUE);
			typeDeclaration_AST = (AST)currentAST.root;
			break;
		}
		case ITEM_OR_VALUE:
		{
			AST tmp24_AST = null;
			if (inputState.guessing==0) {
				tmp24_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp24_AST);
			}
			match(ITEM_OR_VALUE);
			typeDeclaration_AST = (AST)currentAST.root;
			break;
		}
		case CLASS:
		{
			AST tmp25_AST = null;
			if (inputState.guessing==0) {
				tmp25_AST = (AST)astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp25_AST);
			}
			match(CLASS);
			classOrAttributeName();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			typeDeclaration_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = typeDeclaration_AST;
	}
	
	public final void variableDeclarationList() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST variableDeclarationList_AST = null;
		AST list_AST = null;
		
		{
		{
		int _cnt16=0;
		_loop16:
		do {
			if ((LA(1)==UNRESERVED) && (LA(2)==COLON)) {
				singleVariableDeclaration();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
			}
			else if ((LA(1)==UNRESERVED) && (LA(2)==COMMA)) {
				multipleVariableDeclaration();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
			}
			else {
				if ( _cnt16>=1 ) { break _loop16; } else {throw new NoViableAltException(LT(1));}
			}
			
			_cnt16++;
		} while (true);
		}
		}
		variableDeclarationList_AST = (AST)currentAST.root;
		returnAST = variableDeclarationList_AST;
	}
	
	public final void singleVariableDeclaration() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST singleVariableDeclaration_AST = null;
		Token  id = null;
		AST id_AST = null;
		AST type_AST = null;
		AST expr_AST = null;
		
		id = LT(1);
		if (inputState.guessing==0) {
			id_AST = (AST)astFactory.create(id);
		}
		match(UNRESERVED);
		AST tmp26_AST = null;
		tmp26_AST = (AST)astFactory.create(LT(1));
		match(COLON);
		typeDeclaration();
		if (inputState.guessing==0) {
			type_AST = (AST)returnAST;
		}
		{
		switch ( LA(1)) {
		case EQUALS:
		{
			AST tmp27_AST = null;
			if (inputState.guessing==0) {
				tmp27_AST = (AST)astFactory.create(LT(1));
			}
			match(EQUALS);
			expression();
			if (inputState.guessing==0) {
				expr_AST = (AST)returnAST;
			}
			break;
		}
		case SEMICOLON:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		AST tmp28_AST = null;
		tmp28_AST = (AST)astFactory.create(LT(1));
		match(SEMICOLON);
		if ( inputState.guessing==0 ) {
			singleVariableDeclaration_AST = (AST)currentAST.root;
			singleVariableDeclaration_AST = (AST)astFactory.make( (new ASTArray(4)).add((AST)astFactory.create(UNRESERVED,"SINGLE_LOCAL")).add(type_AST).add(id_AST).add(expr_AST));
			currentAST.root = singleVariableDeclaration_AST;
			currentAST.child = singleVariableDeclaration_AST!=null &&singleVariableDeclaration_AST.getFirstChild()!=null ?
				singleVariableDeclaration_AST.getFirstChild() : singleVariableDeclaration_AST;
			currentAST.advanceChildToEnd();
		}
		returnAST = singleVariableDeclaration_AST;
	}
	
	public final void multipleVariableDeclaration() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST multipleVariableDeclaration_AST = null;
		AST arglist_AST = null;
		AST type_AST = null;
		
		localNameList();
		if (inputState.guessing==0) {
			arglist_AST = (AST)returnAST;
		}
		AST tmp29_AST = null;
		if (inputState.guessing==0) {
			tmp29_AST = (AST)astFactory.create(LT(1));
		}
		match(COLON);
		typeDeclaration();
		if (inputState.guessing==0) {
			type_AST = (AST)returnAST;
		}
		AST tmp30_AST = null;
		if (inputState.guessing==0) {
			tmp30_AST = (AST)astFactory.create(LT(1));
		}
		match(SEMICOLON);
		if ( inputState.guessing==0 ) {
			multipleVariableDeclaration_AST = (AST)currentAST.root;
			multipleVariableDeclaration_AST = (AST)astFactory.make( (new ASTArray(3)).add((AST)astFactory.create(UNRESERVED,"MULTIPLE_LOCAL")).add(type_AST).add(arglist_AST));
			currentAST.root = multipleVariableDeclaration_AST;
			currentAST.child = multipleVariableDeclaration_AST!=null &&multipleVariableDeclaration_AST.getFirstChild()!=null ?
				multipleVariableDeclaration_AST.getFirstChild() : multipleVariableDeclaration_AST;
			currentAST.advanceChildToEnd();
		}
		returnAST = multipleVariableDeclaration_AST;
	}
	
	public final void localNameList() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST localNameList_AST = null;
		AST list_AST = null;
		
		{
		AST tmp31_AST = null;
		if (inputState.guessing==0) {
			tmp31_AST = (AST)astFactory.create(LT(1));
			astFactory.addASTChild(currentAST, tmp31_AST);
		}
		match(UNRESERVED);
		{
		int _cnt21=0;
		_loop21:
		do {
			if ((LA(1)==COMMA)) {
				AST tmp32_AST = null;
				tmp32_AST = (AST)astFactory.create(LT(1));
				match(COMMA);
				AST tmp33_AST = null;
				if (inputState.guessing==0) {
					tmp33_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp33_AST);
				}
				match(UNRESERVED);
			}
			else {
				if ( _cnt21>=1 ) { break _loop21; } else {throw new NoViableAltException(LT(1));}
			}
			
			_cnt21++;
		} while (true);
		}
		}
		localNameList_AST = (AST)currentAST.root;
		returnAST = localNameList_AST;
	}
	
	public final void expression() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST expression_AST = null;
		
		disjunct();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		_loop110:
		do {
			if ((LA(1)==OR)) {
				AST tmp34_AST = null;
				if (inputState.guessing==0) {
					tmp34_AST = (AST)astFactory.create(LT(1));
					astFactory.makeASTRoot(currentAST, tmp34_AST);
				}
				match(OR);
				disjunct();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
			}
			else {
				break _loop110;
			}
			
		} while (true);
		}
		expression_AST = (AST)currentAST.root;
		returnAST = expression_AST;
	}
	
	public final void rule() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST rule_AST = null;
		
		switch ( LA(1)) {
		case WHENEVER:
		{
			wheneverRule();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			rule_AST = (AST)currentAST.root;
			break;
		}
		case UNCONDITIONALLY:
		{
			unconditionallyRule();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			rule_AST = (AST)currentAST.root;
			break;
		}
		case IF:
		{
			ifRule();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			rule_AST = (AST)currentAST.root;
			break;
		}
		case WHEN:
		{
			whenRule();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			rule_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = rule_AST;
	}
	
	public final void wheneverRule() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST wheneverRule_AST = null;
		
		AST tmp35_AST = null;
		if (inputState.guessing==0) {
			tmp35_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp35_AST);
		}
		match(WHENEVER);
		wheneverConditions();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		switch ( LA(1)) {
		case AND:
		{
			wheneverFilter();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			break;
		}
		case THEN:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		AST tmp36_AST = null;
		tmp36_AST = (AST)astFactory.create(LT(1));
		match(THEN);
		consequent();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		wheneverRule_AST = (AST)currentAST.root;
		returnAST = wheneverRule_AST;
	}
	
	public final void unconditionallyRule() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST unconditionallyRule_AST = null;
		
		AST tmp37_AST = null;
		if (inputState.guessing==0) {
			tmp37_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp37_AST);
		}
		match(UNCONDITIONALLY);
		consequent();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		unconditionallyRule_AST = (AST)currentAST.root;
		returnAST = unconditionallyRule_AST;
	}
	
	public final void ifRule() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST ifRule_AST = null;
		
		AST tmp38_AST = null;
		if (inputState.guessing==0) {
			tmp38_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp38_AST);
		}
		match(IF);
		expression();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		AST tmp39_AST = null;
		tmp39_AST = (AST)astFactory.create(LT(1));
		match(THEN);
		consequent();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		ifRule_AST = (AST)currentAST.root;
		returnAST = ifRule_AST;
	}
	
	public final void whenRule() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST whenRule_AST = null;
		
		AST tmp40_AST = null;
		if (inputState.guessing==0) {
			tmp40_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp40_AST);
		}
		match(WHEN);
		expression();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		AST tmp41_AST = null;
		tmp41_AST = (AST)astFactory.create(LT(1));
		match(THEN);
		consequent();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		whenRule_AST = (AST)currentAST.root;
		returnAST = whenRule_AST;
	}
	
	public final void wheneverConditions() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST wheneverConditions_AST = null;
		AST list_AST = null;
		
		wheneverConditionList();
		if (inputState.guessing==0) {
			list_AST = (AST)returnAST;
		}
		if ( inputState.guessing==0 ) {
			wheneverConditions_AST = (AST)currentAST.root;
			wheneverConditions_AST = (AST)astFactory.make( (new ASTArray(2)).add((AST)astFactory.create(UNRESERVED,"CONDITIONS")).add(list_AST));
			currentAST.root = wheneverConditions_AST;
			currentAST.child = wheneverConditions_AST!=null &&wheneverConditions_AST.getFirstChild()!=null ?
				wheneverConditions_AST.getFirstChild() : wheneverConditions_AST;
			currentAST.advanceChildToEnd();
		}
		returnAST = wheneverConditions_AST;
	}
	
	public final void wheneverFilter() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST wheneverFilter_AST = null;
		
		AST tmp42_AST = null;
		tmp42_AST = (AST)astFactory.create(LT(1));
		match(AND);
		AST tmp43_AST = null;
		if (inputState.guessing==0) {
			tmp43_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp43_AST);
		}
		match(WHEN);
		expression();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		wheneverFilter_AST = (AST)currentAST.root;
		returnAST = wheneverFilter_AST;
	}
	
	public final void consequent() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST consequent_AST = null;
		AST list_AST = null;
		
		actionList();
		if (inputState.guessing==0) {
			list_AST = (AST)returnAST;
		}
		if ( inputState.guessing==0 ) {
			consequent_AST = (AST)currentAST.root;
			consequent_AST = (AST)astFactory.make( (new ASTArray(2)).add((AST)astFactory.create(UNRESERVED,"ACTIONS")).add(list_AST));
			currentAST.root = consequent_AST;
			currentAST.child = consequent_AST!=null &&consequent_AST.getFirstChild()!=null ?
				consequent_AST.getFirstChild() : consequent_AST;
			currentAST.advanceChildToEnd();
		}
		returnAST = consequent_AST;
	}
	
	public final void wheneverConditionList() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST wheneverConditionList_AST = null;
		AST list_AST = null;
		
		{
		eventDisjunct();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		_loop31:
		do {
			if ((LA(1)==OR)) {
				AST tmp44_AST = null;
				tmp44_AST = (AST)astFactory.create(LT(1));
				match(OR);
				eventDisjunct();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
			}
			else {
				break _loop31;
			}
			
		} while (true);
		}
		}
		wheneverConditionList_AST = (AST)currentAST.root;
		returnAST = wheneverConditionList_AST;
	}
	
	public final void eventDisjunct() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST eventDisjunct_AST = null;
		
		designation();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		switch ( LA(1)) {
		case RECEIVES:
		{
			AST tmp45_AST = null;
			if (inputState.guessing==0) {
				tmp45_AST = (AST)astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp45_AST);
			}
			match(RECEIVES);
			AST tmp46_AST = null;
			tmp46_AST = (AST)astFactory.create(LT(1));
			match(A);
			AST tmp47_AST = null;
			tmp47_AST = (AST)astFactory.create(LT(1));
			match(VALUE);
			break;
		}
		case HAS:
		{
			AST tmp48_AST = null;
			if (inputState.guessing==0) {
				tmp48_AST = (AST)astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp48_AST);
			}
			match(HAS);
			{
			switch ( LA(1)) {
			case A:
			{
				AST tmp49_AST = null;
				tmp49_AST = (AST)astFactory.create(LT(1));
				match(A);
				break;
			}
			case AN:
			{
				AST tmp50_AST = null;
				tmp50_AST = (AST)astFactory.create(LT(1));
				match(AN);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			AST tmp51_AST = null;
			if (inputState.guessing==0) {
				tmp51_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp51_AST);
			}
			match(UNRESERVED);
			AST tmp52_AST = null;
			tmp52_AST = (AST)astFactory.create(LT(1));
			match(EVENT);
			{
			switch ( LA(1)) {
			case UNRESERVED:
			{
				localName();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case THEN:
			case AND:
			case OR:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		eventDisjunct_AST = (AST)currentAST.root;
		returnAST = eventDisjunct_AST;
	}
	
	public final void designation() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST designation_AST = null;
		AST d1_AST = null;
		AST exp1_AST = null;
		AST d2_AST = null;
		AST exp2_AST = null;
		
		switch ( LA(1)) {
		case LPAREN:
		{
			AST tmp53_AST = null;
			if (inputState.guessing==0) {
				tmp53_AST = (AST)astFactory.create(LT(1));
			}
			match(LPAREN);
			designation();
			if (inputState.guessing==0) {
				d2_AST = (AST)returnAST;
			}
			AST tmp54_AST = null;
			if (inputState.guessing==0) {
				tmp54_AST = (AST)astFactory.create(LT(1));
			}
			match(RPAREN);
			AST tmp55_AST = null;
			if (inputState.guessing==0) {
				tmp55_AST = (AST)astFactory.create(LT(1));
			}
			match(LBRACK);
			expression();
			if (inputState.guessing==0) {
				exp2_AST = (AST)returnAST;
			}
			AST tmp56_AST = null;
			if (inputState.guessing==0) {
				tmp56_AST = (AST)astFactory.create(LT(1));
			}
			match(RBRACK);
			if ( inputState.guessing==0 ) {
				designation_AST = (AST)currentAST.root;
				designation_AST = (AST)astFactory.make( (new ASTArray(3)).add((AST)astFactory.create(UNRESERVED,"ARRAY_REFERENCE")).add(d2_AST).add(exp2_AST));
				currentAST.root = designation_AST;
				currentAST.child = designation_AST!=null &&designation_AST.getFirstChild()!=null ?
					designation_AST.getFirstChild() : designation_AST;
				currentAST.advanceChildToEnd();
			}
			break;
		}
		case THE:
		{
			AST tmp57_AST = null;
			tmp57_AST = (AST)astFactory.create(LT(1));
			match(THE);
			classOrAttributeName();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case UNRESERVED:
			{
				localName();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case OF:
			case CONNECTED:
			case UPON:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			{
			switch ( LA(1)) {
			case OF:
			{
				AST tmp58_AST = null;
				if (inputState.guessing==0) {
					tmp58_AST = (AST)astFactory.create(LT(1));
					astFactory.makeASTRoot(currentAST, tmp58_AST);
				}
				match(OF);
				{
				if (Arrays.asList(UNRESERVED, LPAREN, THE,ANY).contains(LA(1)) 
						&& Arrays.asList(EOF, UNRESERVED, MIDDLE_STRING_LITERAL, RIGHT_STRING_LITERAL, LPAREN, 
								RPAREN, COMMA, SEMICOLON, PLUS, TIMES, EQUALS, MINUS, SLASH, LBRACK, RBRACK, 
								GREATER, LESS, NOT_EQUAL, GREATER_EQUAL, LESS_EQUAL, END, THE, THEN, ELSE, 
								IS, AND, OR, BY, OBJECT, DO, TO, DOWN, AFTER, HAS, EXISTS, DOES, RECEIVES, 
								EVENT, ANY, SUCH).contains(LA(2))) {
					
					designation();
					if (inputState.guessing==0) {
						astFactory.addASTChild(currentAST, returnAST);
					}
				}
				else if ((LA(1)==THE) && (LA(2)==CLASS_FIELDS)) {
					AST tmp59_AST = null;
					tmp59_AST = (AST)astFactory.create(LT(1));
					match(THE);
					AST tmp60_AST = null;
					tmp60_AST = (AST)astFactory.create(LT(1));
					match(CLASS_FIELDS);
					AST tmp61_AST = null;
					tmp61_AST = (AST)astFactory.create(LT(1));
					match(OF);
					classNameExpression();
					if (inputState.guessing==0) {
						astFactory.addASTChild(currentAST, returnAST);
					}
				}
				else {
					throw new NoViableAltException(LT(1));
				}
				
				}
				break;
			}
			case CONNECTED:
			{
				AST tmp62_AST = null;
				if (inputState.guessing==0) {
					tmp62_AST = (AST)astFactory.create(LT(1));
					astFactory.makeASTRoot(currentAST, tmp62_AST);
				}
				match(CONNECTED);
				connectionSpec();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case UPON:
			{
				AST tmp63_AST = null;
				if (inputState.guessing==0) {
					tmp63_AST = (AST)astFactory.create(LT(1));
					astFactory.makeASTRoot(currentAST, tmp63_AST);
				}
				match(UPON);
				designation();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			designation_AST = (AST)currentAST.root;
			break;
		}
		case ANY:
		{
			AST tmp64_AST = null;
			if (inputState.guessing==0) {
				tmp64_AST = (AST)astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp64_AST);
			}
			match(ANY);
			classNameExpression();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case UNRESERVED:
			{
				localName();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case EOF:
			case MIDDLE_STRING_LITERAL:
			case RIGHT_STRING_LITERAL:
			case RPAREN:
			case COMMA:
			case SEMICOLON:
			case PLUS:
			case TIMES:
			case EQUALS:
			case MINUS:
			case SLASH:
			case RBRACK:
			case GREATER:
			case LESS:
			case NOT_EQUAL:
			case GREATER_EQUAL:
			case LESS_EQUAL:
			case END:
			case THEN:
			case ELSE:
			case IS:
			case AND:
			case OR:
			case BY:
			case DO:
			case TO:
			case DOWN:
			case AFTER:
			case HAS:
			case EXISTS:
			case DOES:
			case RECEIVES:
			case SUCH:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			designation_AST = (AST)currentAST.root;
			break;
		}
		default:
			if ((LA(1)==UNRESERVED) && (LA(2)==LBRACK)) {
				localName();
				if (inputState.guessing==0) {
					d1_AST = (AST)returnAST;
				}
				AST tmp65_AST = null;
				if (inputState.guessing==0) {
					tmp65_AST = (AST)astFactory.create(LT(1));
				}
				match(LBRACK);
				expression();
				if (inputState.guessing==0) {
					exp1_AST = (AST)returnAST;
				}
				AST tmp66_AST = null;
				if (inputState.guessing==0) {
					tmp66_AST = (AST)astFactory.create(LT(1));
				}
				match(RBRACK);
				if ( inputState.guessing==0 ) {
					designation_AST = (AST)currentAST.root;
					designation_AST = (AST)astFactory.make( (new ASTArray(3)).add((AST)astFactory.create(UNRESERVED,"ARRAY_REFERENCE")).add(d1_AST).add(exp1_AST));
					currentAST.root = designation_AST;
					currentAST.child = designation_AST!=null &&designation_AST.getFirstChild()!=null ?
						designation_AST.getFirstChild() : designation_AST;
					currentAST.advanceChildToEnd();
				}
			}
			else if (LA(1)==UNRESERVED 
					&& Arrays.asList(EOF, MIDDLE_STRING_LITERAL, RIGHT_STRING_LITERAL, RPAREN, COMMA, SEMICOLON, 
							PLUS, TIMES, EQUALS, MINUS, SLASH, RBRACK, GREATER, LESS, NOT_EQUAL, GREATER_EQUAL, 
							LESS_EQUAL, END, THEN, ELSE, IS, AND, OR, BY, DO, TO, DOWN, AFTER, HAS, EXISTS, 
							DOES, RECEIVES,SUCH).contains(LA(2))) {
				
				localName();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				designation_AST = (AST)currentAST.root;
			}
		else {
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = designation_AST;
	}
	
	public final void localName() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST localName_AST = null;
		Token  id = null;
		AST id_AST = null;
		
		id = LT(1);
		if (inputState.guessing==0) {
			id_AST = (AST)astFactory.create(id);
		}
		match(UNRESERVED);
		if ( inputState.guessing==0 ) {
			localName_AST = (AST)currentAST.root;
			localName_AST = (AST)astFactory.make( (new ASTArray(2)).add((AST)astFactory.create(UNRESERVED,"LOCAL_REFERENCE")).add(id_AST));
			currentAST.root = localName_AST;
			currentAST.child = localName_AST!=null &&localName_AST.getFirstChild()!=null ?
				localName_AST.getFirstChild() : localName_AST;
			currentAST.advanceChildToEnd();
		}
		returnAST = localName_AST;
	}
	
	public final void actionList() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST actionList_AST = null;
		
		{
		switch ( LA(1)) {
		case IN:
		{
			AST tmp67_AST = null;
			tmp67_AST = (AST)astFactory.create(LT(1));
			match(IN);
			AST tmp68_AST = null;
			if (inputState.guessing==0) {
				tmp68_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp68_AST);
			}
			match(ORDER);
			break;
		}
		case CREATE:
		case DELETE:
		case INFORM:
		case CONCLUDE:
		case START:
		case CHANGE:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		action();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		_loop44:
		do {
			if ((LA(1)==AND)) {
				AST tmp69_AST = null;
				tmp69_AST = (AST)astFactory.create(LT(1));
				match(AND);
				action();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
			}
			else {
				break _loop44;
			}
			
		} while (true);
		}
		actionList_AST = (AST)currentAST.root;
		returnAST = actionList_AST;
	}
	
	public final void action() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST action_AST = null;
		
		switch ( LA(1)) {
		case CREATE:
		{
			createAction();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			action_AST = (AST)currentAST.root;
			break;
		}
		case DELETE:
		{
			deleteAction();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			action_AST = (AST)currentAST.root;
			break;
		}
		case INFORM:
		{
			informAction();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			action_AST = (AST)currentAST.root;
			break;
		}
		case START:
		{
			startAction();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			action_AST = (AST)currentAST.root;
			break;
		}
		case CONCLUDE:
		{
			concludeAction();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			action_AST = (AST)currentAST.root;
			break;
		}
		case CHANGE:
		{
			changeColorAction();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			action_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = action_AST;
	}
	
	public final void classOrAttributeName() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST classOrAttributeName_AST = null;
		
		switch ( LA(1)) {
		case UNRESERVED:
		{
			AST tmp70_AST = null;
			if (inputState.guessing==0) {
				tmp70_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp70_AST);
			}
			match(UNRESERVED);
			classOrAttributeName_AST = (AST)currentAST.root;
			break;
		}
		case OBJECT:
		{
			AST tmp71_AST = null;
			if (inputState.guessing==0) {
				tmp71_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp71_AST);
			}
			match(OBJECT);
			classOrAttributeName_AST = (AST)currentAST.root;
			break;
		}
		case EVENT:
		{
			AST tmp72_AST = null;
			if (inputState.guessing==0) {
				tmp72_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp72_AST);
			}
			match(EVENT);
			classOrAttributeName_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = classOrAttributeName_AST;
	}
	
	public final void compoundStatementTail() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST compoundStatementTail_AST = null;
		AST statements_AST = null;
		
		switch ( LA(1)) {
		case UNRESERVED:
		case CALL:
		case BEGIN:
		case IF:
		case CREATE:
		case DELETE:
		case INFORM:
		case CONCLUDE:
		case FOR:
		case REPEAT:
		case EXIT:
		case RETURN:
		case SIGNAL:
		case START:
		case CHANGE:
		case WAIT:
		case ALLOW:
		{
			statementList();
			if (inputState.guessing==0) {
				statements_AST = (AST)returnAST;
			}
			{
			switch ( LA(1)) {
			case SEMICOLON:
			{
				AST tmp73_AST = null;
				if (inputState.guessing==0) {
					tmp73_AST = (AST)astFactory.create(LT(1));
				}
				match(SEMICOLON);
				break;
			}
			case END:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			AST tmp74_AST = null;
			if (inputState.guessing==0) {
				tmp74_AST = (AST)astFactory.create(LT(1));
			}
			match(END);
			if ( inputState.guessing==0 ) {
				compoundStatementTail_AST = (AST)currentAST.root;
				compoundStatementTail_AST = (AST)astFactory.make( (new ASTArray(2)).add((AST)astFactory.create(UNRESERVED,"BLOCK")).add(statements_AST));
				currentAST.root = compoundStatementTail_AST;
				currentAST.child = compoundStatementTail_AST!=null &&compoundStatementTail_AST.getFirstChild()!=null ?
					compoundStatementTail_AST.getFirstChild() : compoundStatementTail_AST;
				currentAST.advanceChildToEnd();
			}
			break;
		}
		case SEMICOLON:
		case END:
		{
			{
			switch ( LA(1)) {
			case SEMICOLON:
			{
				AST tmp75_AST = null;
				if (inputState.guessing==0) {
					tmp75_AST = (AST)astFactory.create(LT(1));
				}
				match(SEMICOLON);
				break;
			}
			case END:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			AST tmp76_AST = null;
			if (inputState.guessing==0) {
				tmp76_AST = (AST)astFactory.create(LT(1));
			}
			match(END);
			if ( inputState.guessing==0 ) {
				compoundStatementTail_AST = (AST)currentAST.root;
				compoundStatementTail_AST = (AST)astFactory.make( (new ASTArray(1)).add((AST)astFactory.create(UNRESERVED,"BLOCK")));
				currentAST.root = compoundStatementTail_AST;
				currentAST.child = compoundStatementTail_AST!=null &&compoundStatementTail_AST.getFirstChild()!=null ?
					compoundStatementTail_AST.getFirstChild() : compoundStatementTail_AST;
				currentAST.advanceChildToEnd();
			}
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = compoundStatementTail_AST;
	}
	
	public final void statementList() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST statementList_AST = null;
		AST statements_AST = null;
		
		{
		statement();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		_loop55:
		do {
			if (LA(1)==SEMICOLON 
				&& Arrays.asList(UNRESERVED, CALL, BEGIN, IF, CREATE, DELETE, INFORM, CONCLUDE, FOR, 
						REPEAT, EXIT, RETURN, SIGNAL, START, CHANGE, WAIT, ALLOW).contains(LA(2))) {
				
				AST tmp77_AST = null;
				tmp77_AST = (AST)astFactory.create(LT(1));
				match(SEMICOLON);
				statement();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
			}
			else {
				break _loop55;
			}
			
		} while (true);
		}
		}
		statementList_AST = (AST)currentAST.root;
		returnAST = statementList_AST;
	}
	
	public final void statement() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST statement_AST = null;
		
		switch ( LA(1)) {
		case UNRESERVED:
		case CALL:
		case BEGIN:
		case CREATE:
		case DELETE:
		case INFORM:
		case CONCLUDE:
		case FOR:
		case REPEAT:
		case EXIT:
		case RETURN:
		case SIGNAL:
		case START:
		case CHANGE:
		case WAIT:
		case ALLOW:
		{
			simpleStatement();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			statement_AST = (AST)currentAST.root;
			break;
		}
		case IF:
		{
			ifThenElseStatement();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			statement_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = statement_AST;
	}
	
	public final void simpleStatement() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST simpleStatement_AST = null;
		
		switch ( LA(1)) {
		case CALL:
		{
			call();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			simpleStatement_AST = (AST)currentAST.root;
			break;
		}
		case BEGIN:
		{
			compoundStatement();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			simpleStatement_AST = (AST)currentAST.root;
			break;
		}
		case RETURN:
		{
			returnStatement();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			simpleStatement_AST = (AST)currentAST.root;
			break;
		}
		case FOR:
		{
			forStatement();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			simpleStatement_AST = (AST)currentAST.root;
			break;
		}
		case REPEAT:
		{
			repeatStatement();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			simpleStatement_AST = (AST)currentAST.root;
			break;
		}
		case EXIT:
		{
			exitIfStatement();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			simpleStatement_AST = (AST)currentAST.root;
			break;
		}
		case CREATE:
		case DELETE:
		case INFORM:
		case CONCLUDE:
		case START:
		case CHANGE:
		{
			action();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			simpleStatement_AST = (AST)currentAST.root;
			break;
		}
		case ALLOW:
		{
			allowOtherProcessingStatement();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			simpleStatement_AST = (AST)currentAST.root;
			break;
		}
		case SIGNAL:
		{
			signalStatement();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			simpleStatement_AST = (AST)currentAST.root;
			break;
		}
		case WAIT:
		{
			waitStatement();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			simpleStatement_AST = (AST)currentAST.root;
			break;
		}
		default:
			boolean synPredMatched59 = false;
			if (((LA(1)==UNRESERVED) && (LA(2)==EQUALS))) {
				int _m59 = mark();
				synPredMatched59 = true;
				inputState.guessing++;
				try {
					{
					match(UNRESERVED);
					match(EQUALS);
					match(CALL);
					}
				}
				catch (ParserException pe) {
					synPredMatched59 = false;
				}
				rewind(_m59);
				inputState.guessing--;
			}
			if ( synPredMatched59 ) {
				AST tmp78_AST = null;
				if (inputState.guessing==0) {
					tmp78_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp78_AST);
				}
				match(UNRESERVED);
				AST tmp79_AST = null;
				if (inputState.guessing==0) {
					tmp79_AST = (AST)astFactory.create(LT(1));
					astFactory.makeASTRoot(currentAST, tmp79_AST);
				}
				match(EQUALS);
				call();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				simpleStatement_AST = (AST)currentAST.root;
			}
			else if ((LA(1)==UNRESERVED) && (LA(2)==EQUALS)) {
				AST tmp80_AST = null;
				if (inputState.guessing==0) {
					tmp80_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp80_AST);
				}
				match(UNRESERVED);
				AST tmp81_AST = null;
				if (inputState.guessing==0) {
					tmp81_AST = (AST)astFactory.create(LT(1));
					astFactory.makeASTRoot(currentAST, tmp81_AST);
				}
				match(EQUALS);
				expression();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				simpleStatement_AST = (AST)currentAST.root;
			}
		else {
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = simpleStatement_AST;
	}
	
	public final void ifThenElseStatement() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST ifThenElseStatement_AST = null;
		
		AST tmp82_AST = null;
		if (inputState.guessing==0) {
			tmp82_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp82_AST);
		}
		match(IF);
		expression();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		AST tmp83_AST = null;
		tmp83_AST = (AST)astFactory.create(LT(1));
		match(THEN);
		simpleStatement();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		switch ( LA(1)) {
		case ELSE:
		{
			AST tmp84_AST = null;
			tmp84_AST = (AST)astFactory.create(LT(1));
			match(ELSE);
			statement();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			break;
		}
		case SEMICOLON:
		case END:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		ifThenElseStatement_AST = (AST)currentAST.root;
		returnAST = ifThenElseStatement_AST;
	}
	
	public final void call() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST call_AST = null;
		
		AST tmp85_AST = null;
		if (inputState.guessing==0) {
			tmp85_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp85_AST);
		}
		match(CALL);
		{
		switch ( LA(1)) {
		case UNRESERVED:
		case THE:
		case CREATE:
		{
			{
			switch ( LA(1)) {
			case UNRESERVED:
			{
				AST tmp86_AST = null;
				if (inputState.guessing==0) {
					tmp86_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp86_AST);
				}
				match(UNRESERVED);
				break;
			}
			case CREATE:
			{
				methodNamesThatShouldntBeReserved();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case THE:
			{
				staticMethodReference();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			argumentList();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			break;
		}
		case NEW:
		{
			AST tmp87_AST = null;
			if (inputState.guessing==0) {
				tmp87_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp87_AST);
			}
			match(NEW);
			constructorArgumentList();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		call_AST = (AST)currentAST.root;
		returnAST = call_AST;
	}
	
	public final void returnStatement() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST returnStatement_AST = null;
		
		AST tmp88_AST = null;
		if (inputState.guessing==0) {
			tmp88_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp88_AST);
		}
		match(RETURN);
		{
		switch ( LA(1)) {
		case UNRESERVED:
		case INTEGER_LITERAL:
		case FLOAT_LITERAL:
		case TRUTH_VALUE_LITERAL:
		case WHOLE_STRING_LITERAL:
		case LEFT_STRING_LITERAL:
		case LPAREN:
		case PLUS:
		case MINUS:
		case THE:
		case SYMBOL:
		case NOT:
		case QUANTITY:
		case SEQUENCE:
		case STRUCTURE:
		case ANY:
		case HOUR:
		case MINUTE:
		case SECOND:
		case TIME:
		case THERE:
		{
			expression();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			break;
		}
		case SEMICOLON:
		case END:
		case ELSE:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		returnStatement_AST = (AST)currentAST.root;
		returnAST = returnStatement_AST;
	}
	
	public final void forStatement() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST forStatement_AST = null;
		
		AST tmp89_AST = null;
		if (inputState.guessing==0) {
			tmp89_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp89_AST);
		}
		match(FOR);
		localName();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		forIterationSpec();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		AST tmp90_AST = null;
		tmp90_AST = (AST)astFactory.create(LT(1));
		match(DO);
		compoundStatementTail();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		forStatement_AST = (AST)currentAST.root;
		returnAST = forStatement_AST;
	}
	
	public final void repeatStatement() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST repeatStatement_AST = null;
		
		AST tmp91_AST = null;
		if (inputState.guessing==0) {
			tmp91_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp91_AST);
		}
		match(REPEAT);
		compoundStatementTail();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		repeatStatement_AST = (AST)currentAST.root;
		returnAST = repeatStatement_AST;
	}
	
	public final void exitIfStatement() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST exitIfStatement_AST = null;
		
		AST tmp92_AST = null;
		if (inputState.guessing==0) {
			tmp92_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp92_AST);
		}
		match(EXIT);
		AST tmp93_AST = null;
		tmp93_AST = (AST)astFactory.create(LT(1));
		match(IF);
		expression();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		exitIfStatement_AST = (AST)currentAST.root;
		returnAST = exitIfStatement_AST;
	}
	
	public final void allowOtherProcessingStatement() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST allowOtherProcessingStatement_AST = null;
		
		AST tmp94_AST = null;
		if (inputState.guessing==0) {
			tmp94_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp94_AST);
		}
		match(ALLOW);
		AST tmp95_AST = null;
		tmp95_AST = (AST)astFactory.create(LT(1));
		match(OTHER);
		AST tmp96_AST = null;
		tmp96_AST = (AST)astFactory.create(LT(1));
		match(PROCESSING);
		allowOtherProcessingStatement_AST = (AST)currentAST.root;
		returnAST = allowOtherProcessingStatement_AST;
	}
	
	public final void signalStatement() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST signalStatement_AST = null;
		
		AST tmp97_AST = null;
		if (inputState.guessing==0) {
			tmp97_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp97_AST);
		}
		match(SIGNAL);
		expression();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		switch ( LA(1)) {
		case COMMA:
		{
			AST tmp98_AST = null;
			tmp98_AST = (AST)astFactory.create(LT(1));
			match(COMMA);
			expression();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			break;
		}
		case SEMICOLON:
		case END:
		case ELSE:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		signalStatement_AST = (AST)currentAST.root;
		returnAST = signalStatement_AST;
	}
	
	public final void waitStatement() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST waitStatement_AST = null;
		
		AST tmp99_AST = null;
		if (inputState.guessing==0) {
			tmp99_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp99_AST);
		}
		match(WAIT);
		AST tmp100_AST = null;
		tmp100_AST = (AST)astFactory.create(LT(1));
		match(FOR);
		{
		boolean synPredMatched98 = false;
		if (((LA(1)==INTEGER_LITERAL||LA(1)==FLOAT_LITERAL) && ((LA(2) >= WEEK && LA(2) <= SECONDS)))) {
			int _m98 = mark();
			synPredMatched98 = true;
			inputState.guessing++;
			try {
				{
				quantityInterval();
				}
			}
			catch (ParserException pe) {
				synPredMatched98 = false;
			}
			rewind(_m98);
			inputState.guessing--;
		}
		if ( synPredMatched98 ) {
			quantityInterval();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
		}
		else if (Arrays.asList(UNRESERVED, INTEGER_LITERAL, FLOAT_LITERAL, TRUTH_VALUE_LITERAL, WHOLE_STRING_LITERAL, 
						LEFT_STRING_LITERAL, LPAREN, PLUS, MINUS, THE, SYMBOL, NOT, QUANTITY, SEQUENCE, 
						STRUCTURE, ANY, HOUR, MINUTE, SECOND, TIME, THERE).contains(LA(1)) 
				&& Arrays.asList(UNRESERVED, INTEGER_LITERAL, FLOAT_LITERAL, TRUTH_VALUE_LITERAL, WHOLE_STRING_LITERAL, 
						LEFT_STRING_LITERAL, LPAREN, SEMICOLON, PLUS, TIMES, EQUALS, MINUS, SLASH, LBRACK, 
						GREATER, LESS, NOT_EQUAL, GREATER_EQUAL, LESS_EQUAL, END, THE, SYMBOL, ELSE, IS, 
						NOT, OBJECT, QUANTITY, SEQUENCE, STRUCTURE, EXISTS, DOES, EVENT, ANY, HOUR, MINUTE, 
						SECOND, CURRENT, TIME, THERE, NUMBER).contains(LA(2))) {
			
			conjunct();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
		}
		else {
			throw new NoViableAltException(LT(1));
		}
		
		}
		waitStatement_AST = (AST)currentAST.root;
		returnAST = waitStatement_AST;
	}
	
	public final void createAction() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST createAction_AST = null;
		
		AST tmp101_AST = null;
		if (inputState.guessing==0) {
			tmp101_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp101_AST);
		}
		match(CREATE);
		{
		switch ( LA(1)) {
		case A:
		{
			AST tmp102_AST = null;
			tmp102_AST = (AST)astFactory.create(LT(1));
			match(A);
			break;
		}
		case AN:
		{
			AST tmp103_AST = null;
			tmp103_AST = (AST)astFactory.create(LT(1));
			match(AN);
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		classNameExpression();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		AST tmp104_AST = null;
		if (inputState.guessing==0) {
			tmp104_AST = (AST)astFactory.create(LT(1));
			astFactory.addASTChild(currentAST, tmp104_AST);
		}
		match(UNRESERVED);
		createAction_AST = (AST)currentAST.root;
		returnAST = createAction_AST;
	}
	
	public final void deleteAction() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST deleteAction_AST = null;
		
		AST tmp105_AST = null;
		if (inputState.guessing==0) {
			tmp105_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp105_AST);
		}
		match(DELETE);
		designation();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		deleteAction_AST = (AST)currentAST.root;
		returnAST = deleteAction_AST;
	}
	
	public final void informAction() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST informAction_AST = null;
		
		AST tmp106_AST = null;
		if (inputState.guessing==0) {
			tmp106_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp106_AST);
		}
		match(INFORM);
		AST tmp107_AST = null;
		tmp107_AST = (AST)astFactory.create(LT(1));
		match(THE);
		AST tmp108_AST = null;
		tmp108_AST = (AST)astFactory.create(LT(1));
		match(OPERATOR);
		AST tmp109_AST = null;
		tmp109_AST = (AST)astFactory.create(LT(1));
		match(THAT);
		{
		switch ( LA(1)) {
		case LEFT_STRING_LITERAL:
		{
			formatForm();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			break;
		}
		case WHOLE_STRING_LITERAL:
		{
			AST tmp110_AST = null;
			if (inputState.guessing==0) {
				tmp110_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp110_AST);
			}
			match(WHOLE_STRING_LITERAL);
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		informAction_AST = (AST)currentAST.root;
		returnAST = informAction_AST;
	}
	
	public final void startAction() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST startAction_AST = null;
		
		AST tmp111_AST = null;
		if (inputState.guessing==0) {
			tmp111_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp111_AST);
		}
		match(START);
		{
		switch ( LA(1)) {
		case UNRESERVED:
		{
			AST tmp112_AST = null;
			if (inputState.guessing==0) {
				tmp112_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp112_AST);
			}
			match(UNRESERVED);
			break;
		}
		case THE:
		{
			staticMethodReference();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		argumentList();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		switch ( LA(1)) {
		case AT:
		{
			prioritySuffix();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			break;
		}
		case EOF:
		case SEMICOLON:
		case END:
		case ELSE:
		case AND:
		case AFTER:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		{
		switch ( LA(1)) {
		case AFTER:
		{
			delaySuffix();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			break;
		}
		case EOF:
		case SEMICOLON:
		case END:
		case ELSE:
		case AND:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		startAction_AST = (AST)currentAST.root;
		returnAST = startAction_AST;
	}
	
	public final void concludeAction() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST concludeAction_AST = null;
		
		AST tmp113_AST = null;
		if (inputState.guessing==0) {
			tmp113_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp113_AST);
		}
		match(CONCLUDE);
		AST tmp114_AST = null;
		tmp114_AST = (AST)astFactory.create(LT(1));
		match(THAT);
		designation();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		switch ( LA(1)) {
		case EQUALS:
		{
			AST tmp115_AST = null;
			if (inputState.guessing==0) {
				tmp115_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp115_AST);
			}
			match(EQUALS);
			conjunct();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			break;
		}
		case HAS:
		{
			AST tmp116_AST = null;
			if (inputState.guessing==0) {
				tmp116_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp116_AST);
			}
			match(HAS);
			AST tmp117_AST = null;
			if (inputState.guessing==0) {
				tmp117_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp117_AST);
			}
			match(NO);
			AST tmp118_AST = null;
			if (inputState.guessing==0) {
				tmp118_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp118_AST);
			}
			match(VALUE);
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		concludeAction_AST = (AST)currentAST.root;
		returnAST = concludeAction_AST;
	}
	
	public final void changeColorAction() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST changeColorAction_AST = null;
		
		AST tmp119_AST = null;
		if (inputState.guessing==0) {
			tmp119_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp119_AST);
		}
		match(CHANGE);
		AST tmp120_AST = null;
		tmp120_AST = (AST)astFactory.create(LT(1));
		match(THE);
		AST tmp121_AST = null;
		if (inputState.guessing==0) {
			tmp121_AST = (AST)astFactory.create(LT(1));
			astFactory.addASTChild(currentAST, tmp121_AST);
		}
		match(UNRESERVED);
		AST tmp122_AST = null;
		tmp122_AST = (AST)astFactory.create(LT(1));
		match(ICON_COLOR);
		AST tmp123_AST = null;
		tmp123_AST = (AST)astFactory.create(LT(1));
		match(OF);
		designation();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		AST tmp124_AST = null;
		tmp124_AST = (AST)astFactory.create(LT(1));
		match(TO);
		AST tmp125_AST = null;
		if (inputState.guessing==0) {
			tmp125_AST = (AST)astFactory.create(LT(1));
			astFactory.addASTChild(currentAST, tmp125_AST);
		}
		match(UNRESERVED);
		changeColorAction_AST = (AST)currentAST.root;
		returnAST = changeColorAction_AST;
	}
	
	public final void staticMethodReference() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST staticMethodReference_AST = null;
		
		AST tmp126_AST = null;
		tmp126_AST = (AST)astFactory.create(LT(1));
		match(THE);
		{
		switch ( LA(1)) {
		case PROCEDURE:
		{
			AST tmp127_AST = null;
			tmp127_AST = (AST)astFactory.create(LT(1));
			match(PROCEDURE);
			break;
		}
		case METHOD:
		{
			AST tmp128_AST = null;
			tmp128_AST = (AST)astFactory.create(LT(1));
			match(METHOD);
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		AST tmp129_AST = null;
		tmp129_AST = (AST)astFactory.create(LT(1));
		match(NAMED);
		AST tmp130_AST = null;
		tmp130_AST = (AST)astFactory.create(LT(1));
		match(BY);
		AST tmp131_AST = null;
		tmp131_AST = (AST)astFactory.create(LT(1));
		match(THE);
		AST tmp132_AST = null;
		if (inputState.guessing==0) {
			tmp132_AST = (AST)astFactory.create(LT(1));
			astFactory.addASTChild(currentAST, tmp132_AST);
		}
		match(UNRESERVED);
		AST tmp133_AST = null;
		if (inputState.guessing==0) {
			tmp133_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp133_AST);
		}
		match(OF);
		AST tmp134_AST = null;
		tmp134_AST = (AST)astFactory.create(LT(1));
		match(THE);
		AST tmp135_AST = null;
		tmp135_AST = (AST)astFactory.create(LT(1));
		match(CLASS_METHODS);
		AST tmp136_AST = null;
		tmp136_AST = (AST)astFactory.create(LT(1));
		match(OF);
		classNameExpression();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		staticMethodReference_AST = (AST)currentAST.root;
		returnAST = staticMethodReference_AST;
	}
	
	public final void argumentList() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST argumentList_AST = null;
		AST arglist_AST = null;
		
		AST tmp137_AST = null;
		tmp137_AST = (AST)astFactory.create(LT(1));
		match(LPAREN);
		{
		switch ( LA(1)) {
		case UNRESERVED:
		case INTEGER_LITERAL:
		case FLOAT_LITERAL:
		case TRUTH_VALUE_LITERAL:
		case WHOLE_STRING_LITERAL:
		case LEFT_STRING_LITERAL:
		case LPAREN:
		case PLUS:
		case MINUS:
		case THE:
		case SYMBOL:
		case NOT:
		case QUANTITY:
		case SEQUENCE:
		case STRUCTURE:
		case ANY:
		case HOUR:
		case MINUTE:
		case SECOND:
		case TIME:
		case THERE:
		{
			expression();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			_loop103:
			do {
				if ((LA(1)==COMMA)) {
					AST tmp138_AST = null;
					tmp138_AST = (AST)astFactory.create(LT(1));
					match(COMMA);
					expression();
					if (inputState.guessing==0) {
						astFactory.addASTChild(currentAST, returnAST);
					}
				}
				else {
					break _loop103;
				}
				
			} while (true);
			}
			break;
		}
		case RPAREN:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		AST tmp139_AST = null;
		tmp139_AST = (AST)astFactory.create(LT(1));
		match(RPAREN);
		argumentList_AST = (AST)currentAST.root;
		returnAST = argumentList_AST;
	}
	
	public final void prioritySuffix() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST prioritySuffix_AST = null;
		
		AST tmp140_AST = null;
		tmp140_AST = (AST)astFactory.create(LT(1));
		match(AT);
		AST tmp141_AST = null;
		if (inputState.guessing==0) {
			tmp141_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp141_AST);
		}
		match(PRIORITY);
		conjunct();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		prioritySuffix_AST = (AST)currentAST.root;
		returnAST = prioritySuffix_AST;
	}
	
	public final void delaySuffix() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST delaySuffix_AST = null;
		
		AST tmp142_AST = null;
		if (inputState.guessing==0) {
			tmp142_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp142_AST);
		}
		match(AFTER);
		conjunct();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		delaySuffix_AST = (AST)currentAST.root;
		returnAST = delaySuffix_AST;
	}
	
	public final void conjunct() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST conjunct_AST = null;
		
		switch ( LA(1)) {
		case NOT:
		{
			AST tmp143_AST = null;
			if (inputState.guessing==0) {
				tmp143_AST = (AST)astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp143_AST);
			}
			match(NOT);
			AST tmp144_AST = null;
			tmp144_AST = (AST)astFactory.create(LT(1));
			match(LPAREN);
			expression();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			AST tmp145_AST = null;
			tmp145_AST = (AST)astFactory.create(LT(1));
			match(RPAREN);
			conjunct_AST = (AST)currentAST.root;
			break;
		}
		case LEFT_STRING_LITERAL:
		{
			formatForm();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			conjunct_AST = (AST)currentAST.root;
			break;
		}
		case THERE:
		{
			AST tmp146_AST = null;
			if (inputState.guessing==0) {
				tmp146_AST = (AST)astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp146_AST);
			}
			match(THERE);
			AST tmp147_AST = null;
			tmp147_AST = (AST)astFactory.create(LT(1));
			match(EXISTS);
			{
			switch ( LA(1)) {
			case A:
			{
				AST tmp148_AST = null;
				tmp148_AST = (AST)astFactory.create(LT(1));
				match(A);
				break;
			}
			case AN:
			{
				AST tmp149_AST = null;
				tmp149_AST = (AST)astFactory.create(LT(1));
				match(AN);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			typeExpression();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case UNRESERVED:
			{
				localName();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case EOF:
			case MIDDLE_STRING_LITERAL:
			case RIGHT_STRING_LITERAL:
			case RPAREN:
			case COMMA:
			case SEMICOLON:
			case RBRACK:
			case END:
			case THEN:
			case ELSE:
			case AND:
			case OR:
			case BY:
			case DO:
			case TO:
			case DOWN:
			case AFTER:
			case IN:
			case SUCH:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			{
			switch ( LA(1)) {
			case IN:
			{
				AST tmp150_AST = null;
				if (inputState.guessing==0) {
					tmp150_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp150_AST);
				}
				match(IN);
				designation();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case EOF:
			case MIDDLE_STRING_LITERAL:
			case RIGHT_STRING_LITERAL:
			case RPAREN:
			case COMMA:
			case SEMICOLON:
			case RBRACK:
			case END:
			case THEN:
			case ELSE:
			case AND:
			case OR:
			case BY:
			case DO:
			case TO:
			case DOWN:
			case AFTER:
			case SUCH:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			{
			switch ( LA(1)) {
			case SUCH:
			{
				AST tmp151_AST = null;
				if (inputState.guessing==0) {
					tmp151_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp151_AST);
				}
				match(SUCH);
				AST tmp152_AST = null;
				tmp152_AST = (AST)astFactory.create(LT(1));
				match(THAT);
				AST tmp153_AST = null;
				tmp153_AST = (AST)astFactory.create(LT(1));
				match(LPAREN);
				expression();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				AST tmp154_AST = null;
				if (inputState.guessing==0) {
					tmp154_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp154_AST);
				}
				match(RPAREN);
				break;
			}
			case EOF:
			case MIDDLE_STRING_LITERAL:
			case RIGHT_STRING_LITERAL:
			case RPAREN:
			case COMMA:
			case SEMICOLON:
			case RBRACK:
			case END:
			case THEN:
			case ELSE:
			case AND:
			case OR:
			case BY:
			case DO:
			case TO:
			case DOWN:
			case AFTER:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			conjunct_AST = (AST)currentAST.root;
			break;
		}
		default:
			boolean synPredMatched120 = false;
			if (Arrays.asList(UNRESERVED, LPAREN, THE, ANY).contains(LA(1)) 
				&& Arrays.asList(UNRESERVED, LPAREN, LBRACK, THE, IS, OBJECT, EXISTS, DOES, EVENT, ANY).contains(LA(2))) {
				
				int _m120 = mark();
				synPredMatched120 = true;
				inputState.guessing++;
				try {
					{
					designation();
					{
					switch ( LA(1)) {
					case IS:
					{
						match(IS);
						{
						switch ( LA(1)) {
						case TRUTH_VALUE_LITERAL:
						{
							match(TRUTH_VALUE_LITERAL);
							break;
						}
						case THE:
						case NOT:
						case A:
						case AN:
						{
							{
							switch ( LA(1)) {
							case NOT:
							{
								match(NOT);
								break;
							}
							case THE:
							case A:
							case AN:
							{
								break;
							}
							default:
							{
								throw new NoViableAltException(LT(1));
							}
							}
							}
							{
							switch ( LA(1)) {
							case THE:
							{
								match(THE);
								break;
							}
							case A:
							{
								match(A);
								break;
							}
							case AN:
							{
								match(AN);
								break;
							}
							default:
							{
								throw new NoViableAltException(LT(1));
							}
							}
							}
							break;
						}
						default:
						{
							throw new NoViableAltException(LT(1));
						}
						}
						}
						break;
					}
					case EXISTS:
					{
						match(EXISTS);
						break;
					}
					case DOES:
					{
						match(DOES);
						break;
					}
					default:
					{
						throw new NoViableAltException(LT(1));
					}
					}
					}
					}
				}
				catch (ParserException pe) {
					synPredMatched120 = false;
				}
				rewind(_m120);
				inputState.guessing--;
			}
			if ( synPredMatched120 ) {
				designationPredicate();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				conjunct_AST = (AST)currentAST.root;
			}
			else if (Arrays.asList(UNRESERVED, INTEGER_LITERAL, FLOAT_LITERAL, TRUTH_VALUE_LITERAL, 
						WHOLE_STRING_LITERAL, LPAREN, PLUS, MINUS, THE, SYMBOL, QUANTITY, SEQUENCE, 
						STRUCTURE, ANY, HOUR, MINUTE, SECOND,TIME).contains(LA(1)) 
					&& Arrays.asList(EOF, UNRESERVED, INTEGER_LITERAL, FLOAT_LITERAL, TRUTH_VALUE_LITERAL, 
						WHOLE_STRING_LITERAL, LEFT_STRING_LITERAL, MIDDLE_STRING_LITERAL, RIGHT_STRING_LITERAL, 
						LPAREN, RPAREN, COMMA, SEMICOLON, PLUS, TIMES, EQUALS, MINUS, SLASH, LBRACK, RBRACK, 
						GREATER, LESS, NOT_EQUAL, GREATER_EQUAL, LESS_EQUAL, END, THE, SYMBOL, THEN, ELSE, 
						IS, NOT, AND, OR, BY, OBJECT, DO, TO, DOWN, QUANTITY, AFTER, SEQUENCE, STRUCTURE, 
						EVENT, ANY, HOUR, MINUTE, SECOND, CURRENT, TIME, THERE, NUMBER).contains(LA(2))) {
				
				sumExpression();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				{
				switch ( LA(1)) {
				case EOF:
				case MIDDLE_STRING_LITERAL:
				case RIGHT_STRING_LITERAL:
				case RPAREN:
				case COMMA:
				case SEMICOLON:
				case EQUALS:
				case RBRACK:
				case GREATER:
				case LESS:
				case NOT_EQUAL:
				case GREATER_EQUAL:
				case LESS_EQUAL:
				case END:
				case THEN:
				case ELSE:
				case AND:
				case OR:
				case BY:
				case DO:
				case TO:
				case DOWN:
				case AFTER:
				{
					{
					_loop124:
					do {
						if (Arrays.asList(EQUALS, GREATER, LESS, NOT_EQUAL, GREATER_EQUAL, LESS_EQUAL).contains(LA(1))) {
							{
							switch ( LA(1)) {
							case EQUALS:
							{
								AST tmp155_AST = null;
								if (inputState.guessing==0) {
									tmp155_AST = (AST)astFactory.create(LT(1));
									astFactory.makeASTRoot(currentAST, tmp155_AST);
								}
								match(EQUALS);
								break;
							}
							case GREATER:
							{
								AST tmp156_AST = null;
								if (inputState.guessing==0) {
									tmp156_AST = (AST)astFactory.create(LT(1));
									astFactory.makeASTRoot(currentAST, tmp156_AST);
								}
								match(GREATER);
								break;
							}
							case LESS:
							{
								AST tmp157_AST = null;
								if (inputState.guessing==0) {
									tmp157_AST = (AST)astFactory.create(LT(1));
									astFactory.makeASTRoot(currentAST, tmp157_AST);
								}
								match(LESS);
								break;
							}
							case NOT_EQUAL:
							{
								AST tmp158_AST = null;
								if (inputState.guessing==0) {
									tmp158_AST = (AST)astFactory.create(LT(1));
									astFactory.makeASTRoot(currentAST, tmp158_AST);
								}
								match(NOT_EQUAL);
								break;
							}
							case GREATER_EQUAL:
							{
								AST tmp159_AST = null;
								if (inputState.guessing==0) {
									tmp159_AST = (AST)astFactory.create(LT(1));
									astFactory.makeASTRoot(currentAST, tmp159_AST);
								}
								match(GREATER_EQUAL);
								break;
							}
							case LESS_EQUAL:
							{
								AST tmp160_AST = null;
								if (inputState.guessing==0) {
									tmp160_AST = (AST)astFactory.create(LT(1));
									astFactory.makeASTRoot(currentAST, tmp160_AST);
								}
								match(LESS_EQUAL);
								break;
							}
							default:
							{
								throw new NoViableAltException(LT(1));
							}
							}
							}
							sumExpression();
							if (inputState.guessing==0) {
								astFactory.addASTChild(currentAST, returnAST);
							}
						}
						else {
							break _loop124;
						}
						
					} while (true);
					}
					break;
				}
				case IS:
				{
					AST tmp161_AST = null;
					if (inputState.guessing==0) {
						tmp161_AST = (AST)astFactory.create(LT(1));
						astFactory.makeASTRoot(currentAST, tmp161_AST);
					}
					match(IS);
					{
					switch ( LA(1)) {
					case NOT:
					{
						AST tmp162_AST = null;
						if (inputState.guessing==0) {
							tmp162_AST = (AST)astFactory.create(LT(1));
							astFactory.addASTChild(currentAST, tmp162_AST);
						}
						match(NOT);
						break;
					}
					case UNRESERVED:
					{
						break;
					}
					default:
					{
						throw new NoViableAltException(LT(1));
					}
					}
					}
					AST tmp163_AST = null;
					if (inputState.guessing==0) {
						tmp163_AST = (AST)astFactory.create(LT(1));
						astFactory.addASTChild(currentAST, tmp163_AST);
					}
					match(UNRESERVED);
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1));
				}
				}
				}
				conjunct_AST = (AST)currentAST.root;
			}
		else {
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = conjunct_AST;
	}
	
	public final void classNameExpression() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST classNameExpression_AST = null;
		AST spec_AST = null;
		
		classOrAttributeName();
		if (inputState.guessing==0) {
			spec_AST = (AST)returnAST;
		}
		if ( inputState.guessing==0 ) {
			classNameExpression_AST = (AST)currentAST.root;
			classNameExpression_AST  = (AST)astFactory.make( (new ASTArray(2)).add((AST)astFactory.create(UNRESERVED,"CLASS")).add(spec_AST));
			currentAST.root = classNameExpression_AST;
			currentAST.child = classNameExpression_AST!=null &&classNameExpression_AST.getFirstChild()!=null ?
				classNameExpression_AST.getFirstChild() : classNameExpression_AST;
			currentAST.advanceChildToEnd();
		}
		returnAST = classNameExpression_AST;
	}
	
	public final void formatForm() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST formatForm_AST = null;
		Token  left = null;
		AST left_AST = null;
		AST first_AST = null;
		AST list_AST = null;
		Token  right = null;
		AST right_AST = null;
		
		left = LT(1);
		if (inputState.guessing==0) {
			left_AST = (AST)astFactory.create(left);
		}
		match(LEFT_STRING_LITERAL);
		expression();
		if (inputState.guessing==0) {
			first_AST = (AST)returnAST;
		}
		formatList();
		if (inputState.guessing==0) {
			list_AST = (AST)returnAST;
		}
		right = LT(1);
		if (inputState.guessing==0) {
			right_AST = (AST)astFactory.create(right);
		}
		match(RIGHT_STRING_LITERAL);
		if ( inputState.guessing==0 ) {
			formatForm_AST = (AST)currentAST.root;
			formatForm_AST = (AST)astFactory.make( (new ASTArray(5)).add((AST)astFactory.create(UNRESERVED,"FORMAT_FORM")).add(left_AST).add(first_AST).add(list_AST).add(right_AST));
			currentAST.root = formatForm_AST;
			currentAST.child = formatForm_AST!=null &&formatForm_AST.getFirstChild()!=null ?
				formatForm_AST.getFirstChild() : formatForm_AST;
			currentAST.advanceChildToEnd();
		}
		returnAST = formatForm_AST;
	}
	
	public final void methodNamesThatShouldntBeReserved() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST methodNamesThatShouldntBeReserved_AST = null;
		
		AST tmp164_AST = null;
		if (inputState.guessing==0) {
			tmp164_AST = (AST)astFactory.create(LT(1));
			astFactory.addASTChild(currentAST, tmp164_AST);
		}
		match(CREATE);
		methodNamesThatShouldntBeReserved_AST = (AST)currentAST.root;
		returnAST = methodNamesThatShouldntBeReserved_AST;
	}
	
	public final void constructorArgumentList() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST constructorArgumentList_AST = null;
		AST arglist_AST = null;
		
		AST tmp165_AST = null;
		tmp165_AST = (AST)astFactory.create(LT(1));
		match(LPAREN);
		{
		classNameExpression();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		AST tmp166_AST = null;
		tmp166_AST = (AST)astFactory.create(LT(1));
		match(COMMA);
		expression();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		_loop107:
		do {
			if ((LA(1)==COMMA)) {
				AST tmp167_AST = null;
				tmp167_AST = (AST)astFactory.create(LT(1));
				match(COMMA);
				expression();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
			}
			else {
				break _loop107;
			}
			
		} while (true);
		}
		}
		AST tmp168_AST = null;
		tmp168_AST = (AST)astFactory.create(LT(1));
		match(RPAREN);
		constructorArgumentList_AST = (AST)currentAST.root;
		returnAST = constructorArgumentList_AST;
	}
	
	public final void forIterationSpec() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST forIterationSpec_AST = null;
		
		if (LA(1)==EQUALS && 
				Arrays.asList(UNRESERVED, INTEGER_LITERAL, FLOAT_LITERAL, TRUTH_VALUE_LITERAL, WHOLE_STRING_LITERAL, 
						LEFT_STRING_LITERAL, LPAREN, PLUS, MINUS, THE, SYMBOL, NOT, QUANTITY, SEQUENCE, STRUCTURE, 
						ANY, HOUR, MINUTE, SECOND, TIME, THERE).contains(LA(2))) {
			AST tmp169_AST = null;
			if (inputState.guessing==0) {
				tmp169_AST = (AST)astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp169_AST);
			}
			match(EQUALS);
			expression();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case TO:
			{
				AST tmp170_AST = null;
				if (inputState.guessing==0) {
					tmp170_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp170_AST);
				}
				match(TO);
				break;
			}
			case DOWN:
			{
				AST tmp171_AST = null;
				if (inputState.guessing==0) {
					tmp171_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp171_AST);
				}
				match(DOWN);
				AST tmp172_AST = null;
				tmp172_AST = (AST)astFactory.create(LT(1));
				match(TO);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			expression();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case BY:
			{
				AST tmp173_AST = null;
				tmp173_AST = (AST)astFactory.create(LT(1));
				match(BY);
				expression();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case DO:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			forIterationSpec_AST = (AST)currentAST.root;
		}
		else if ((LA(1)==EQUALS) && (LA(2)==EACH)) {
			AST tmp174_AST = null;
			tmp174_AST = (AST)astFactory.create(LT(1));
			match(EQUALS);
			AST tmp175_AST = null;
			if (inputState.guessing==0) {
				tmp175_AST = (AST)astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp175_AST);
			}
			match(EACH);
			typeExpression();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case IN:
			{
				AST tmp176_AST = null;
				if (inputState.guessing==0) {
					tmp176_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp176_AST);
				}
				match(IN);
				designation();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case DO:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			forIterationSpec_AST = (AST)currentAST.root;
		}
		else {
			throw new NoViableAltException(LT(1));
		}
		
		returnAST = forIterationSpec_AST;
	}
	
	public final void typeExpression() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST typeExpression_AST = null;
		
		switch ( LA(1)) {
		case INTEGER:
		{
			AST tmp177_AST = null;
			if (inputState.guessing==0) {
				tmp177_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp177_AST);
			}
			match(INTEGER);
			typeExpression_AST = (AST)currentAST.root;
			break;
		}
		case FLOAT:
		{
			AST tmp178_AST = null;
			if (inputState.guessing==0) {
				tmp178_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp178_AST);
			}
			match(FLOAT);
			typeExpression_AST = (AST)currentAST.root;
			break;
		}
		case QUANTITY:
		{
			AST tmp179_AST = null;
			if (inputState.guessing==0) {
				tmp179_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp179_AST);
			}
			match(QUANTITY);
			typeExpression_AST = (AST)currentAST.root;
			break;
		}
		case TEXT:
		{
			AST tmp180_AST = null;
			if (inputState.guessing==0) {
				tmp180_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp180_AST);
			}
			match(TEXT);
			typeExpression_AST = (AST)currentAST.root;
			break;
		}
		case SYMBOL:
		{
			AST tmp181_AST = null;
			if (inputState.guessing==0) {
				tmp181_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp181_AST);
			}
			match(SYMBOL);
			typeExpression_AST = (AST)currentAST.root;
			break;
		}
		case TRUTH_VALUE:
		{
			AST tmp182_AST = null;
			if (inputState.guessing==0) {
				tmp182_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp182_AST);
			}
			match(TRUTH_VALUE);
			typeExpression_AST = (AST)currentAST.root;
			break;
		}
		case SEQUENCE:
		{
			AST tmp183_AST = null;
			if (inputState.guessing==0) {
				tmp183_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp183_AST);
			}
			match(SEQUENCE);
			typeExpression_AST = (AST)currentAST.root;
			break;
		}
		case STRUCTURE:
		{
			AST tmp184_AST = null;
			if (inputState.guessing==0) {
				tmp184_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp184_AST);
			}
			match(STRUCTURE);
			typeExpression_AST = (AST)currentAST.root;
			break;
		}
		case VALUE:
		{
			AST tmp185_AST = null;
			if (inputState.guessing==0) {
				tmp185_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp185_AST);
			}
			match(VALUE);
			typeExpression_AST = (AST)currentAST.root;
			break;
		}
		case ITEM_OR_VALUE:
		{
			AST tmp186_AST = null;
			if (inputState.guessing==0) {
				tmp186_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp186_AST);
			}
			match(ITEM_OR_VALUE);
			typeExpression_AST = (AST)currentAST.root;
			break;
		}
		case UNRESERVED:
		case OBJECT:
		case EVENT:
		{
			classNameExpression();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			typeExpression_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = typeExpression_AST;
	}
	
	public final void quantityInterval() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST quantityInterval_AST = null;
		AST interval_AST = null;
		
		quantityIntervalWeeks();
		if (inputState.guessing==0) {
			interval_AST = (AST)returnAST;
		}
		if ( inputState.guessing==0 ) {
			quantityInterval_AST = (AST)currentAST.root;
			quantityInterval_AST = (AST)astFactory.make( (new ASTArray(2)).add((AST)astFactory.create(UNRESERVED,"INTERVAL")).add(interval_AST));
			currentAST.root = quantityInterval_AST;
			currentAST.child = quantityInterval_AST!=null &&quantityInterval_AST.getFirstChild()!=null ?
				quantityInterval_AST.getFirstChild() : quantityInterval_AST;
			currentAST.advanceChildToEnd();
		}
		returnAST = quantityInterval_AST;
	}
	
	public final void disjunct() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST disjunct_AST = null;
		
		conjunct();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		_loop113:
		do {
			if ((LA(1)==AND)) {
				AST tmp187_AST = null;
				if (inputState.guessing==0) {
					tmp187_AST = (AST)astFactory.create(LT(1));
					astFactory.makeASTRoot(currentAST, tmp187_AST);
				}
				match(AND);
				conjunct();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
			}
			else {
				break _loop113;
			}
			
		} while (true);
		}
		disjunct_AST = (AST)currentAST.root;
		returnAST = disjunct_AST;
	}
	
	public final void designationPredicate() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST designationPredicate_AST = null;
		
		designation();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		switch ( LA(1)) {
		case IS:
		{
			AST tmp188_AST = null;
			if (inputState.guessing==0) {
				tmp188_AST = (AST)astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp188_AST);
			}
			match(IS);
			{
			if ((LA(1)==TRUTH_VALUE_LITERAL)) {
				AST tmp189_AST = null;
				if (inputState.guessing==0) {
					tmp189_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp189_AST);
				}
				match(TRUTH_VALUE_LITERAL);
			}
			else if ((LA(1)==THE||LA(1)==NOT) && (LA(2)==THE||LA(2)==SAME)) {
				{
				switch ( LA(1)) {
				case NOT:
				{
					AST tmp190_AST = null;
					if (inputState.guessing==0) {
						tmp190_AST = (AST)astFactory.create(LT(1));
						astFactory.addASTChild(currentAST, tmp190_AST);
					}
					match(NOT);
					break;
				}
				case THE:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1));
				}
				}
				}
				AST tmp191_AST = null;
				tmp191_AST = (AST)astFactory.create(LT(1));
				match(THE);
				AST tmp192_AST = null;
				tmp192_AST = (AST)astFactory.create(LT(1));
				match(SAME);
				AST tmp193_AST = null;
				if (inputState.guessing==0) {
					tmp193_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp193_AST);
				}
				match(OBJECT);
				AST tmp194_AST = null;
				tmp194_AST = (AST)astFactory.create(LT(1));
				match(AS);
				designation();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
			}
			else if (Arrays.asList(NOT, A, AN).contains(LA(1)) 
					&& Arrays.asList(UNRESERVED, INTEGER, FLOAT, TRUTH_VALUE, TEXT, SYMBOL, A, AN, OBJECT, 
							QUANTITY, SEQUENCE, STRUCTURE, VALUE, ITEM_OR_VALUE, EVENT).contains(LA(2))) {
				{
				switch ( LA(1)) {
				case NOT:
				{
					AST tmp195_AST = null;
					if (inputState.guessing==0) {
						tmp195_AST = (AST)astFactory.create(LT(1));
						astFactory.addASTChild(currentAST, tmp195_AST);
					}
					match(NOT);
					break;
				}
				case A:
				case AN:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1));
				}
				}
				}
				{
				switch ( LA(1)) {
				case A:
				{
					AST tmp196_AST = null;
					tmp196_AST = (AST)astFactory.create(LT(1));
					match(A);
					break;
				}
				case AN:
				{
					AST tmp197_AST = null;
					tmp197_AST = (AST)astFactory.create(LT(1));
					match(AN);
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1));
				}
				}
				}
				typeExpression();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
			}
			else {
				throw new NoViableAltException(LT(1));
			}
			
			}
			break;
		}
		case EXISTS:
		{
			AST tmp198_AST = null;
			if (inputState.guessing==0) {
				tmp198_AST = (AST)astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp198_AST);
			}
			match(EXISTS);
			break;
		}
		case DOES:
		{
			AST tmp199_AST = null;
			tmp199_AST = (AST)astFactory.create(LT(1));
			match(DOES);
			AST tmp200_AST = null;
			if (inputState.guessing==0) {
				tmp200_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp200_AST);
			}
			match(NOT);
			AST tmp201_AST = null;
			if (inputState.guessing==0) {
				tmp201_AST = (AST)astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp201_AST);
			}
			match(EXIST);
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		designationPredicate_AST = (AST)currentAST.root;
		returnAST = designationPredicate_AST;
	}
	
	public final void sumExpression() throws ParserException, IOException {
		
		List<Integer> tokenList1 = Arrays.asList(UNRESERVED, INTEGER_LITERAL, FLOAT_LITERAL, TRUTH_VALUE_LITERAL, WHOLE_STRING_LITERAL, LPAREN, PLUS, MINUS, THE, SYMBOL, QUANTITY, SEQUENCE, STRUCTURE, ANY, HOUR, MINUTE, SECOND, TIME);
		List<Integer> tokenList2 = Arrays.asList(UNRESERVED, INTEGER_LITERAL, FLOAT_LITERAL, TRUTH_VALUE_LITERAL, WHOLE_STRING_LITERAL, LEFT_STRING_LITERAL, LPAREN, PLUS, TIMES, MINUS, SLASH, LBRACK, THE, SYMBOL, NOT, OBJECT, QUANTITY, SEQUENCE, STRUCTURE, EVENT, ANY, HOUR, MINUTE, SECOND, CURRENT, TIME, THERE, NUMBER);
		List<Integer> tokenList3 = Arrays.asList(EOF, UNRESERVED, INTEGER_LITERAL, FLOAT_LITERAL, TRUTH_VALUE_LITERAL, WHOLE_STRING_LITERAL, LEFT_STRING_LITERAL, MIDDLE_STRING_LITERAL, RIGHT_STRING_LITERAL, LPAREN, RPAREN, COMMA, SEMICOLON, PLUS, TIMES, EQUALS, MINUS, SLASH, LBRACK, RBRACK, GREATER, LESS, NOT_EQUAL, GREATER_EQUAL, LESS_EQUAL, END, THE, SYMBOL, THEN, ELSE, IS, NOT, AND, OR, BY, OBJECT, DO, TO, DOWN, QUANTITY, AFTER, SEQUENCE, STRUCTURE, EVENT, ANY, HOUR, MINUTE, SECOND, CURRENT, TIME, THERE, NUMBER);

		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST sumExpression_AST = null;
		
		boolean synPredMatched139 = false;
		if (tokenList1.contains(LA(1)) && tokenList2.contains(LA(2))) {
			int _m139 = mark();
			synPredMatched139 = true;
			inputState.guessing++;
			try {
				{
				termOrSignedTerm();
				match(PLUS);
				}
			}
			catch (ParserException pe) {
				synPredMatched139 = false;
			}
			rewind(_m139);
			inputState.guessing--;
		}
		if ( synPredMatched139 ) {
			termOrSignedTerm();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			AST tmp202_AST = null;
			if (inputState.guessing==0) {
				tmp202_AST = (AST)astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp202_AST);
			}
			match(PLUS);
			sumExpressionTail();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			sumExpression_AST = (AST)currentAST.root;
		}
		else {
			boolean synPredMatched141 = false;
			if (tokenList1.contains(LA(1)) && tokenList2.contains(LA(2))) {
				int _m141 = mark();
				synPredMatched141 = true;
				inputState.guessing++;
				try {
					{
					termOrSignedTerm();
					match(MINUS);
					}
				}
				catch (ParserException pe) {
					synPredMatched141 = false;
				}
				rewind(_m141);
				inputState.guessing--;
			}
			if ( synPredMatched141 ) {
				termOrSignedTerm();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				AST tmp203_AST = null;
				if (inputState.guessing==0) {
					tmp203_AST = (AST)astFactory.create(LT(1));
					astFactory.makeASTRoot(currentAST, tmp203_AST);
				}
				match(MINUS);
				sumExpressionTail();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				sumExpression_AST = (AST)currentAST.root;
			}
			else if (tokenList1.contains(LA(1)) && tokenList3.contains(LA(2))) {
				termOrSignedTerm();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				sumExpression_AST = (AST)currentAST.root;
			}
			else {
				throw new NoViableAltException(LT(1));
			}
			}
			returnAST = sumExpression_AST;
		}
		
	public final void termOrSignedTerm() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST termOrSignedTerm_AST = null;
		
		switch ( LA(1)) {
		case MINUS:
		{
			AST tmp204_AST = null;
			if (inputState.guessing==0) {
				tmp204_AST = (AST)astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp204_AST);
			}
			match(MINUS);
			term();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			termOrSignedTerm_AST = (AST)currentAST.root;
			break;
		}
		case PLUS:
		{
			AST tmp205_AST = null;
			if (inputState.guessing==0) {
				tmp205_AST = (AST)astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp205_AST);
			}
			match(PLUS);
			term();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			termOrSignedTerm_AST = (AST)currentAST.root;
			break;
		}
		case UNRESERVED:
		case INTEGER_LITERAL:
		case FLOAT_LITERAL:
		case TRUTH_VALUE_LITERAL:
		case WHOLE_STRING_LITERAL:
		case LPAREN:
		case THE:
		case SYMBOL:
		case QUANTITY:
		case SEQUENCE:
		case STRUCTURE:
		case ANY:
		case HOUR:
		case MINUTE:
		case SECOND:
		case TIME:
		{
			term();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			termOrSignedTerm_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = termOrSignedTerm_AST;
	}
	
	public final void sumExpressionTail() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST sumExpressionTail_AST = null;
		
		boolean synPredMatched145 = false;
		List<Integer> tokenList1 = Arrays.asList(UNRESERVED, INTEGER_LITERAL, FLOAT_LITERAL, TRUTH_VALUE_LITERAL, WHOLE_STRING_LITERAL, LPAREN, THE, SYMBOL, QUANTITY, SEQUENCE, STRUCTURE, ANY, HOUR, MINUTE, SECOND, TIME);
		List<Integer> tokenList2 = Arrays.asList(UNRESERVED, INTEGER_LITERAL, FLOAT_LITERAL, TRUTH_VALUE_LITERAL, WHOLE_STRING_LITERAL, LEFT_STRING_LITERAL, LPAREN, PLUS, TIMES, MINUS, SLASH, LBRACK, THE, SYMBOL, NOT, OBJECT, QUANTITY, SEQUENCE, STRUCTURE, EVENT, ANY, HOUR, MINUTE, SECOND, CURRENT, TIME, THERE, NUMBER);
		List<Integer> tokenList3 = Arrays.asList(EOF, UNRESERVED, INTEGER_LITERAL, FLOAT_LITERAL, TRUTH_VALUE_LITERAL, WHOLE_STRING_LITERAL, LEFT_STRING_LITERAL, MIDDLE_STRING_LITERAL, RIGHT_STRING_LITERAL, LPAREN, RPAREN, COMMA, SEMICOLON, PLUS, TIMES, EQUALS, MINUS, SLASH, LBRACK, RBRACK, GREATER, LESS, NOT_EQUAL, GREATER_EQUAL, LESS_EQUAL, END, THE, SYMBOL, THEN, ELSE, IS, NOT, AND, OR, BY, OBJECT, DO, TO, DOWN, QUANTITY, AFTER, SEQUENCE, STRUCTURE, EVENT, ANY, HOUR, MINUTE, SECOND, CURRENT, TIME, THERE, NUMBER);

		if (tokenList1.contains(LA(1)) && tokenList2.contains(LA(2))) {
			int _m145 = mark();
			synPredMatched145 = true;
			inputState.guessing++;
			try {
				{
				term();
				match(PLUS);
				}
			}
			catch (ParserException pe) {
				synPredMatched145 = false;
			}
			rewind(_m145);
			inputState.guessing--;
		}
		if ( synPredMatched145 ) {
			term();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			AST tmp206_AST = null;
			if (inputState.guessing==0) {
				tmp206_AST = (AST)astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp206_AST);
			}
			match(PLUS);
			sumExpressionTail();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			sumExpressionTail_AST = (AST)currentAST.root;
		}
		else {
			boolean synPredMatched147 = false;

			if (tokenList1.contains(LA(1)) && tokenList2.contains(LA(2))){
				int _m147 = mark();
				synPredMatched147 = true;
				inputState.guessing++;
				try {
					{
					term();
					match(MINUS);
					}
				}
				catch (ParserException pe) {
					synPredMatched147 = false;
				}
				rewind(_m147);
				inputState.guessing--;
			}
			if ( synPredMatched147 ) {
				term();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				AST tmp207_AST = null;
				if (inputState.guessing==0) {
					tmp207_AST = (AST)astFactory.create(LT(1));
					astFactory.makeASTRoot(currentAST, tmp207_AST);
				}
				match(MINUS);
				sumExpressionTail();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				sumExpressionTail_AST = (AST)currentAST.root;
			}
			else if (tokenList1.contains(LA(1)) && tokenList3.contains(LA(2))) {
				term();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				sumExpressionTail_AST = (AST)currentAST.root;
			}
			else {
				throw new NoViableAltException(LT(1));
			}
			}
			returnAST = sumExpressionTail_AST;
		}
		
	public final void term() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST term_AST = null;
		AST tail_AST = null;
		
		factor();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		tail:
		do {
			if ((LA(1)==TIMES||LA(1)==SLASH)) {
				{
				switch ( LA(1)) {
				case TIMES:
				{
					AST tmp208_AST = null;
					if (inputState.guessing==0) {
						tmp208_AST = (AST)astFactory.create(LT(1));
						astFactory.makeASTRoot(currentAST, tmp208_AST);
					}
					match(TIMES);
					break;
				}
				case SLASH:
				{
					AST tmp209_AST = null;
					if (inputState.guessing==0) {
						tmp209_AST = (AST)astFactory.create(LT(1));
						astFactory.makeASTRoot(currentAST, tmp209_AST);
					}
					match(SLASH);
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1));
				}
				}
				}
				factor();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
			}
			else {
				break tail;
			}
			
		} while (true);
		}
		term_AST = (AST)currentAST.root;
		returnAST = term_AST;
	}
	
	public final void factor() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST factor_AST = null;
		AST id_AST = null;
		AST args_AST = null;
		
		switch ( LA(1)) {
		case SEQUENCE:
		{
			sequenceConstructor();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			factor_AST = (AST)currentAST.root;
			break;
		}
		case STRUCTURE:
		{
			structureConstructor();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			factor_AST = (AST)currentAST.root;
			break;
		}
		default:
			boolean synPredMatched155 = false;
			List<Integer> tokenList = Arrays.asList(EOF, MIDDLE_STRING_LITERAL, RIGHT_STRING_LITERAL, 
									RPAREN, COMMA, SEMICOLON, PLUS, TIMES, EQUALS, MINUS, SLASH, RBRACK, 
									GREATER, LESS, NOT_EQUAL, GREATER_EQUAL, LESS_EQUAL, END, SYMBOL, THEN, 
									ELSE, IS, AND, OR, BY, DO, TO, DOWN, AFTER);
			
			if (Arrays.asList(INTEGER_LITERAL, FLOAT_LITERAL, TRUTH_VALUE_LITERAL, WHOLE_STRING_LITERAL, THE).contains(LA(1)) 
					&& tokenList.contains(LA(2))) {
				int _m155 = mark();
				synPredMatched155 = true;
				inputState.guessing++;
				try {
					{
					constant();
					}
				}
				catch (ParserException pe) {
					synPredMatched155 = false;
				}
				rewind(_m155);
				inputState.guessing--;
			}
			if ( synPredMatched155 ) {
				constant();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				factor_AST = (AST)currentAST.root;
			}
			else {
				boolean synPredMatched157 = false;
				if (LA(2)==LPAREN && Arrays.asList(UNRESERVED, SYMBOL, QUANTITY, HOUR, MINUTE, SECOND, TIME).contains(LA(1))) {
					int _m157 = mark();
					synPredMatched157 = true;
					inputState.guessing++;
					try {
						{
						functionName();
						match(LPAREN);
						}
					}
					catch (ParserException pe) {
						synPredMatched157 = false;
					}
					rewind(_m157);
					inputState.guessing--;
				}
				if ( synPredMatched157 ) {
					functionName();
					if (inputState.guessing==0) {
						id_AST = (AST)returnAST;
					}
					argumentList();
					if (inputState.guessing==0) {
						args_AST = (AST)returnAST;
					}
					if ( inputState.guessing==0 ) {
						factor_AST = (AST)currentAST.root;
						factor_AST = (AST)astFactory.make( (new ASTArray(3)).add((AST)astFactory.create(UNRESERVED,"FUNCTION_CALL")).add(id_AST).add(args_AST));
						currentAST.root = factor_AST;
						currentAST.child = factor_AST!=null &&factor_AST.getFirstChild()!=null ?
							factor_AST.getFirstChild() : factor_AST;
						currentAST.advanceChildToEnd();
					}
				}
				else {
					boolean synPredMatched159 = false;
					tokenList = Arrays.asList(EOF, UNRESERVED, MIDDLE_STRING_LITERAL, RIGHT_STRING_LITERAL, 
							LPAREN, RPAREN, COMMA, SEMICOLON, PLUS, TIMES, EQUALS, MINUS, SLASH, LBRACK, RBRACK, 
							GREATER, LESS, NOT_EQUAL, GREATER_EQUAL, LESS_EQUAL, END, THE, THEN, ELSE, IS, AND, 
							OR, BY, OBJECT, DO, TO, DOWN, AFTER, EVENT, ANY);
					
					List<Integer> tokenList2 = Arrays.asList(UNRESERVED, INTEGER_LITERAL, FLOAT_LITERAL, 
							TRUTH_VALUE_LITERAL, WHOLE_STRING_LITERAL, LEFT_STRING_LITERAL, LPAREN, PLUS, MINUS, 
							THE, SYMBOL, NOT, QUANTITY, SEQUENCE, STRUCTURE, ANY, HOUR, MINUTE, SECOND, TIME, THERE);
					
					if (Arrays.asList(UNRESERVED, LPAREN, THE, ANY).contains(LA(1)) && tokenList.contains(LA(2))) {
						int _m159 = mark();
						synPredMatched159 = true;
						inputState.guessing++;
						try {
							{
							designation();
							}
						}
						catch (ParserException pe) {
							synPredMatched159 = false;
						}
						rewind(_m159);
						inputState.guessing--;
					}
					if ( synPredMatched159 ) {
						designation();
						if (inputState.guessing==0) {
							astFactory.addASTChild(currentAST, returnAST);
						}
						factor_AST = (AST)currentAST.root;
					}
					else if ((LA(1)==THE) && (LA(2)==NUMBER)) {
						AST tmp210_AST = null;
						tmp210_AST = (AST)astFactory.create(LT(1));
						match(THE);
						AST tmp211_AST = null;
						tmp211_AST = (AST)astFactory.create(LT(1));
						match(NUMBER);
						AST tmp212_AST = null;
						tmp212_AST = (AST)astFactory.create(LT(1));
						match(OF);
						AST tmp213_AST = null;
						if (inputState.guessing==0) {
							tmp213_AST = (AST)astFactory.create(LT(1));
							astFactory.makeASTRoot(currentAST, tmp213_AST);
						}
						match(ELEMENTS);
						AST tmp214_AST = null;
						tmp214_AST = (AST)astFactory.create(LT(1));
						match(IN);
						designation();
						if (inputState.guessing==0) {
							astFactory.addASTChild(currentAST, returnAST);
						}
						factor_AST = (AST)currentAST.root;
					}
					else if (LA(1)==LPAREN && tokenList2.contains(LA(2))) {
						AST tmp215_AST = null;
						tmp215_AST = (AST)astFactory.create(LT(1));
						match(LPAREN);
						expression();
						if (inputState.guessing==0) {
							astFactory.addASTChild(currentAST, returnAST);
						}
						AST tmp216_AST = null;
						tmp216_AST = (AST)astFactory.create(LT(1));
						match(RPAREN);
						factor_AST = (AST)currentAST.root;
					}
					else if ((LA(1)==THE) && (LA(2)==CURRENT)) {
						timeExpression();
						if (inputState.guessing==0) {
							astFactory.addASTChild(currentAST, returnAST);
						}
						factor_AST = (AST)currentAST.root;
					}
				else {
					throw new NoViableAltException(LT(1));
				}
				}}}
				returnAST = factor_AST;
			}
			
	public final void factoid() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST factoid_AST = null;
		
		switch ( LA(1)) {
		case INTEGER_LITERAL:
		case FLOAT_LITERAL:
		case TRUTH_VALUE_LITERAL:
		case WHOLE_STRING_LITERAL:
		case THE:
		{
			constant();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			factoid_AST = (AST)currentAST.root;
			break;
		}
		case LPAREN:
		{
			AST tmp217_AST = null;
			tmp217_AST = (AST)astFactory.create(LT(1));
			match(LPAREN);
			expression();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			AST tmp218_AST = null;
			tmp218_AST = (AST)astFactory.create(LT(1));
			match(RPAREN);
			factoid_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = factoid_AST;
	}
	
	public final void constant() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST constant_AST = null;
		
		switch ( LA(1)) {
		case INTEGER_LITERAL:
		{
			AST tmp219_AST = null;
			if (inputState.guessing==0) {
				tmp219_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp219_AST);
			}
			match(INTEGER_LITERAL);
			constant_AST = (AST)currentAST.root;
			break;
		}
		case FLOAT_LITERAL:
		{
			AST tmp220_AST = null;
			if (inputState.guessing==0) {
				tmp220_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp220_AST);
			}
			match(FLOAT_LITERAL);
			constant_AST = (AST)currentAST.root;
			break;
		}
		case TRUTH_VALUE_LITERAL:
		{
			AST tmp221_AST = null;
			if (inputState.guessing==0) {
				tmp221_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp221_AST);
			}
			match(TRUTH_VALUE_LITERAL);
			constant_AST = (AST)currentAST.root;
			break;
		}
		case WHOLE_STRING_LITERAL:
		{
			AST tmp222_AST = null;
			if (inputState.guessing==0) {
				tmp222_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp222_AST);
			}
			match(WHOLE_STRING_LITERAL);
			constant_AST = (AST)currentAST.root;
			break;
		}
		case THE:
		{
			symbolLiteral();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			constant_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = constant_AST;
	}
	
	public final void functionName() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST functionName_AST = null;
		
		switch ( LA(1)) {
		case UNRESERVED:
		{
			AST tmp223_AST = null;
			if (inputState.guessing==0) {
				tmp223_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp223_AST);
			}
			match(UNRESERVED);
			functionName_AST = (AST)currentAST.root;
			break;
		}
		case SYMBOL:
		{
			AST tmp224_AST = null;
			if (inputState.guessing==0) {
				tmp224_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp224_AST);
			}
			match(SYMBOL);
			functionName_AST = (AST)currentAST.root;
			break;
		}
		case QUANTITY:
		{
			AST tmp225_AST = null;
			if (inputState.guessing==0) {
				tmp225_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp225_AST);
			}
			match(QUANTITY);
			functionName_AST = (AST)currentAST.root;
			break;
		}
		case TIME:
		{
			AST tmp226_AST = null;
			if (inputState.guessing==0) {
				tmp226_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp226_AST);
			}
			match(TIME);
			functionName_AST = (AST)currentAST.root;
			break;
		}
		case MINUTE:
		{
			AST tmp227_AST = null;
			if (inputState.guessing==0) {
				tmp227_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp227_AST);
			}
			match(MINUTE);
			functionName_AST = (AST)currentAST.root;
			break;
		}
		case HOUR:
		{
			AST tmp228_AST = null;
			if (inputState.guessing==0) {
				tmp228_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp228_AST);
			}
			match(HOUR);
			functionName_AST = (AST)currentAST.root;
			break;
		}
		case SECOND:
		{
			AST tmp229_AST = null;
			if (inputState.guessing==0) {
				tmp229_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp229_AST);
			}
			match(SECOND);
			functionName_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = functionName_AST;
	}
	
	public final void sequenceConstructor() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST sequenceConstructor_AST = null;
		
		AST tmp230_AST = null;
		if (inputState.guessing==0) {
			tmp230_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp230_AST);
		}
		match(SEQUENCE);
		AST tmp231_AST = null;
		tmp231_AST = (AST)astFactory.create(LT(1));
		match(LPAREN);
		{
		switch ( LA(1)) {
		case UNRESERVED:
		case INTEGER_LITERAL:
		case FLOAT_LITERAL:
		case TRUTH_VALUE_LITERAL:
		case WHOLE_STRING_LITERAL:
		case LEFT_STRING_LITERAL:
		case LPAREN:
		case PLUS:
		case MINUS:
		case THE:
		case SYMBOL:
		case NOT:
		case QUANTITY:
		case SEQUENCE:
		case STRUCTURE:
		case ANY:
		case HOUR:
		case MINUTE:
		case SECOND:
		case TIME:
		case THERE:
		{
			expression();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			_loop165:
			do {
				if ((LA(1)==COMMA)) {
					AST tmp232_AST = null;
					tmp232_AST = (AST)astFactory.create(LT(1));
					match(COMMA);
					expression();
					if (inputState.guessing==0) {
						astFactory.addASTChild(currentAST, returnAST);
					}
				}
				else {
					break _loop165;
				}
				
			} while (true);
			}
			break;
		}
		case RPAREN:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		AST tmp233_AST = null;
		tmp233_AST = (AST)astFactory.create(LT(1));
		match(RPAREN);
		sequenceConstructor_AST = (AST)currentAST.root;
		returnAST = sequenceConstructor_AST;
	}
	
	public final void structureConstructor() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST structureConstructor_AST = null;
		
		AST tmp234_AST = null;
		if (inputState.guessing==0) {
			tmp234_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp234_AST);
		}
		match(STRUCTURE);
		AST tmp235_AST = null;
		tmp235_AST = (AST)astFactory.create(LT(1));
		match(LPAREN);
		{
		switch ( LA(1)) {
		case UNRESERVED:
		{
			AST tmp236_AST = null;
			if (inputState.guessing==0) {
				tmp236_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp236_AST);
			}
			match(UNRESERVED);
			AST tmp237_AST = null;
			tmp237_AST = (AST)astFactory.create(LT(1));
			match(COLON);
			expression();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			_loop169:
			do {
				if ((LA(1)==COMMA)) {
					AST tmp238_AST = null;
					tmp238_AST = (AST)astFactory.create(LT(1));
					match(COMMA);
					AST tmp239_AST = null;
					if (inputState.guessing==0) {
						tmp239_AST = (AST)astFactory.create(LT(1));
						astFactory.addASTChild(currentAST, tmp239_AST);
					}
					match(UNRESERVED);
					AST tmp240_AST = null;
					tmp240_AST = (AST)astFactory.create(LT(1));
					match(COLON);
					expression();
					if (inputState.guessing==0) {
						astFactory.addASTChild(currentAST, returnAST);
					}
				}
				else {
					break _loop169;
				}
				
			} while (true);
			}
			break;
		}
		case RPAREN:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		AST tmp241_AST = null;
		tmp241_AST = (AST)astFactory.create(LT(1));
		match(RPAREN);
		structureConstructor_AST = (AST)currentAST.root;
		returnAST = structureConstructor_AST;
	}
	
	public final void timeExpression() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST timeExpression_AST = null;
		
		AST tmp242_AST = null;
		tmp242_AST = (AST)astFactory.create(LT(1));
		match(THE);
		AST tmp243_AST = null;
		tmp243_AST = (AST)astFactory.create(LT(1));
		match(CURRENT);
		{
		switch ( LA(1)) {
		case REAL:
		{
			AST tmp244_AST = null;
			if (inputState.guessing==0) {
				tmp244_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp244_AST);
			}
			match(REAL);
			break;
		}
		case SUBSECOND:
		{
			AST tmp245_AST = null;
			if (inputState.guessing==0) {
				tmp245_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp245_AST);
			}
			match(SUBSECOND);
			AST tmp246_AST = null;
			if (inputState.guessing==0) {
				tmp246_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp246_AST);
			}
			match(REAL);
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		AST tmp247_AST = null;
		if (inputState.guessing==0) {
			tmp247_AST = (AST)astFactory.create(LT(1));
			astFactory.makeASTRoot(currentAST, tmp247_AST);
		}
		match(TIME);
		timeExpression_AST = (AST)currentAST.root;
		returnAST = timeExpression_AST;
	}
	
	public final void designationFollower() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST designationFollower_AST = null;
		
		switch ( LA(1)) {
		case EQUALS:
		{
			AST tmp248_AST = null;
			if (inputState.guessing==0) {
				tmp248_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp248_AST);
			}
			match(EQUALS);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case GREATER:
		{
			AST tmp249_AST = null;
			if (inputState.guessing==0) {
				tmp249_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp249_AST);
			}
			match(GREATER);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case LESS:
		{
			AST tmp250_AST = null;
			if (inputState.guessing==0) {
				tmp250_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp250_AST);
			}
			match(LESS);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case NOT_EQUAL:
		{
			AST tmp251_AST = null;
			if (inputState.guessing==0) {
				tmp251_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp251_AST);
			}
			match(NOT_EQUAL);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case GREATER_EQUAL:
		{
			AST tmp252_AST = null;
			if (inputState.guessing==0) {
				tmp252_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp252_AST);
			}
			match(GREATER_EQUAL);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case LESS_EQUAL:
		{
			AST tmp253_AST = null;
			if (inputState.guessing==0) {
				tmp253_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp253_AST);
			}
			match(LESS_EQUAL);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case PLUS:
		{
			AST tmp254_AST = null;
			if (inputState.guessing==0) {
				tmp254_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp254_AST);
			}
			match(PLUS);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case TIMES:
		{
			AST tmp255_AST = null;
			if (inputState.guessing==0) {
				tmp255_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp255_AST);
			}
			match(TIMES);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case MINUS:
		{
			AST tmp256_AST = null;
			if (inputState.guessing==0) {
				tmp256_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp256_AST);
			}
			match(MINUS);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case SLASH:
		{
			AST tmp257_AST = null;
			if (inputState.guessing==0) {
				tmp257_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp257_AST);
			}
			match(SLASH);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case HAS:
		{
			AST tmp258_AST = null;
			if (inputState.guessing==0) {
				tmp258_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp258_AST);
			}
			match(HAS);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case IS:
		{
			AST tmp259_AST = null;
			if (inputState.guessing==0) {
				tmp259_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp259_AST);
			}
			match(IS);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case EXISTS:
		{
			AST tmp260_AST = null;
			if (inputState.guessing==0) {
				tmp260_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp260_AST);
			}
			match(EXISTS);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case DOES:
		{
			AST tmp261_AST = null;
			if (inputState.guessing==0) {
				tmp261_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp261_AST);
			}
			match(DOES);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case AND:
		{
			AST tmp262_AST = null;
			if (inputState.guessing==0) {
				tmp262_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp262_AST);
			}
			match(AND);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case OR:
		{
			AST tmp263_AST = null;
			if (inputState.guessing==0) {
				tmp263_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp263_AST);
			}
			match(OR);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case BY:
		{
			AST tmp264_AST = null;
			if (inputState.guessing==0) {
				tmp264_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp264_AST);
			}
			match(BY);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case TO:
		{
			AST tmp265_AST = null;
			if (inputState.guessing==0) {
				tmp265_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp265_AST);
			}
			match(TO);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case DOWN:
		{
			AST tmp266_AST = null;
			if (inputState.guessing==0) {
				tmp266_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp266_AST);
			}
			match(DOWN);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case DO:
		{
			AST tmp267_AST = null;
			if (inputState.guessing==0) {
				tmp267_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp267_AST);
			}
			match(DO);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case END:
		{
			AST tmp268_AST = null;
			if (inputState.guessing==0) {
				tmp268_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp268_AST);
			}
			match(END);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case COMMA:
		{
			AST tmp269_AST = null;
			if (inputState.guessing==0) {
				tmp269_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp269_AST);
			}
			match(COMMA);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case SEMICOLON:
		{
			AST tmp270_AST = null;
			if (inputState.guessing==0) {
				tmp270_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp270_AST);
			}
			match(SEMICOLON);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case THEN:
		{
			AST tmp271_AST = null;
			if (inputState.guessing==0) {
				tmp271_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp271_AST);
			}
			match(THEN);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case RIGHT_STRING_LITERAL:
		{
			AST tmp272_AST = null;
			if (inputState.guessing==0) {
				tmp272_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp272_AST);
			}
			match(RIGHT_STRING_LITERAL);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		case MIDDLE_STRING_LITERAL:
		{
			AST tmp273_AST = null;
			if (inputState.guessing==0) {
				tmp273_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp273_AST);
			}
			match(MIDDLE_STRING_LITERAL);
			designationFollower_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = designationFollower_AST;
	}
	
	public final void connectionSpec() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST connectionSpec_AST = null;
		
		switch ( LA(1)) {
		case TO:
		{
			AST tmp274_AST = null;
			if (inputState.guessing==0) {
				tmp274_AST = (AST)astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp274_AST);
			}
			match(TO);
			designation();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			connectionSpec_AST = (AST)currentAST.root;
			break;
		}
		case AT:
		{
			AST tmp275_AST = null;
			if (inputState.guessing==0) {
				tmp275_AST = (AST)astFactory.create(LT(1));
				astFactory.makeASTRoot(currentAST, tmp275_AST);
			}
			match(AT);
			{
			switch ( LA(1)) {
			case THE:
			{
				AST tmp276_AST = null;
				tmp276_AST = (AST)astFactory.create(LT(1));
				match(THE);
				break;
			}
			case AN:
			{
				AST tmp277_AST = null;
				tmp277_AST = (AST)astFactory.create(LT(1));
				match(AN);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			{
			switch ( LA(1)) {
			case INPUT:
			{
				AST tmp278_AST = null;
				if (inputState.guessing==0) {
					tmp278_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp278_AST);
				}
				match(INPUT);
				break;
			}
			case OUTPUT:
			{
				AST tmp279_AST = null;
				if (inputState.guessing==0) {
					tmp279_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp279_AST);
				}
				match(OUTPUT);
				break;
			}
			case UNRESERVED:
			{
				AST tmp280_AST = null;
				if (inputState.guessing==0) {
					tmp280_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp280_AST);
				}
				match(UNRESERVED);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			{
			switch ( LA(1)) {
			case OF:
			{
				AST tmp281_AST = null;
				tmp281_AST = (AST)astFactory.create(LT(1));
				match(OF);
				break;
			}
			case TO:
			{
				AST tmp282_AST = null;
				tmp282_AST = (AST)astFactory.create(LT(1));
				match(TO);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			designation();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			connectionSpec_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = connectionSpec_AST;
	}
	
	public final void formatList() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST formatList_AST = null;
		AST list_AST = null;
		
		{
		list:
		do {
			if ((LA(1)==MIDDLE_STRING_LITERAL)) {
				AST tmp283_AST = null;
				if (inputState.guessing==0) {
					tmp283_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp283_AST);
				}
				match(MIDDLE_STRING_LITERAL);
				expression();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
			}
			else {
				break list;
			}
			
		} while (true);
		}
		formatList_AST = (AST)currentAST.root;
		returnAST = formatList_AST;
	}
	
	public final void symbolLiteral() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST symbolLiteral_AST = null;
		Token  id = null;
		AST id_AST = null;
		
		AST tmp284_AST = null;
		tmp284_AST = (AST)astFactory.create(LT(1));
		match(THE);
		AST tmp285_AST = null;
		tmp285_AST = (AST)astFactory.create(LT(1));
		match(SYMBOL);
		id = LT(1);
		if (inputState.guessing==0) {
			id_AST = (AST)astFactory.create(id);
		}
		match(UNRESERVED);
		if ( inputState.guessing==0 ) {
			symbolLiteral_AST = (AST)currentAST.root;
			symbolLiteral_AST = (AST)astFactory.make( (new ASTArray(2)).add((AST)astFactory.create(UNRESERVED,"SYMBOL_LITERAL")).add(id_AST));
			currentAST.root = symbolLiteral_AST;
			currentAST.child = symbolLiteral_AST!=null &&symbolLiteral_AST.getFirstChild()!=null ?
				symbolLiteral_AST.getFirstChild() : symbolLiteral_AST;
			currentAST.advanceChildToEnd();
		}
		returnAST = symbolLiteral_AST;
	}
	
	public final void quantityIntervalWeeks() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST quantityIntervalWeeks_AST = null;
		
		if ((LA(1)==INTEGER_LITERAL||LA(1)==FLOAT_LITERAL) && (LA(2)==WEEK||LA(2)==WEEKS)) {
			quantityConstant();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case WEEK:
			{
				AST tmp286_AST = null;
				if (inputState.guessing==0) {
					tmp286_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp286_AST);
				}
				match(WEEK);
				break;
			}
			case WEEKS:
			{
				AST tmp287_AST = null;
				if (inputState.guessing==0) {
					tmp287_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp287_AST);
				}
				match(WEEKS);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			{
			switch ( LA(1)) {
			case AND:
			{
				quantityIntervalDays();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case SEMICOLON:
			case END:
			case ELSE:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			quantityIntervalWeeks_AST = (AST)currentAST.root;
		}
		else if ((LA(1)==INTEGER_LITERAL||LA(1)==FLOAT_LITERAL) && (LA(2)==DAY||LA(2)==DAYS)) {
			quantityConstant();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case DAY:
			{
				AST tmp288_AST = null;
				if (inputState.guessing==0) {
					tmp288_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp288_AST);
				}
				match(DAY);
				break;
			}
			case DAYS:
			{
				AST tmp289_AST = null;
				if (inputState.guessing==0) {
					tmp289_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp289_AST);
				}
				match(DAYS);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			{
			switch ( LA(1)) {
			case AND:
			{
				quantityIntervalHours();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case SEMICOLON:
			case END:
			case ELSE:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			quantityIntervalWeeks_AST = (AST)currentAST.root;
		}
		else if ((LA(1)==INTEGER_LITERAL||LA(1)==FLOAT_LITERAL) && (LA(2)==HOUR||LA(2)==HOURS)) {
			quantityConstant();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case HOUR:
			{
				AST tmp290_AST = null;
				if (inputState.guessing==0) {
					tmp290_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp290_AST);
				}
				match(HOUR);
				break;
			}
			case HOURS:
			{
				AST tmp291_AST = null;
				if (inputState.guessing==0) {
					tmp291_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp291_AST);
				}
				match(HOURS);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			{
			switch ( LA(1)) {
			case AND:
			{
				quantityIntervalMinutes();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case SEMICOLON:
			case END:
			case ELSE:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			quantityIntervalWeeks_AST = (AST)currentAST.root;
		}
		else if ((LA(1)==INTEGER_LITERAL||LA(1)==FLOAT_LITERAL) && (LA(2)==MINUTE||LA(2)==MINUTES)) {
			quantityConstant();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case MINUTE:
			{
				AST tmp292_AST = null;
				if (inputState.guessing==0) {
					tmp292_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp292_AST);
				}
				match(MINUTE);
				break;
			}
			case MINUTES:
			{
				AST tmp293_AST = null;
				if (inputState.guessing==0) {
					tmp293_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp293_AST);
				}
				match(MINUTES);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			{
			switch ( LA(1)) {
			case AND:
			{
				quantityIntervalSeconds();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case SEMICOLON:
			case END:
			case ELSE:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			quantityIntervalWeeks_AST = (AST)currentAST.root;
		}
		else if ((LA(1)==INTEGER_LITERAL||LA(1)==FLOAT_LITERAL) && (LA(2)==SECOND||LA(2)==SECONDS)) {
			quantityConstant();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case SECOND:
			{
				AST tmp294_AST = null;
				if (inputState.guessing==0) {
					tmp294_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp294_AST);
				}
				match(SECOND);
				break;
			}
			case SECONDS:
			{
				AST tmp295_AST = null;
				if (inputState.guessing==0) {
					tmp295_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp295_AST);
				}
				match(SECONDS);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			quantityIntervalWeeks_AST = (AST)currentAST.root;
		}
		else {
			throw new NoViableAltException(LT(1));
		}
		
		returnAST = quantityIntervalWeeks_AST;
	}
	
	public final void quantityConstant() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST quantityConstant_AST = null;
		
		switch ( LA(1)) {
		case INTEGER_LITERAL:
		{
			AST tmp296_AST = null;
			if (inputState.guessing==0) {
				tmp296_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp296_AST);
			}
			match(INTEGER_LITERAL);
			quantityConstant_AST = (AST)currentAST.root;
			break;
		}
		case FLOAT_LITERAL:
		{
			AST tmp297_AST = null;
			if (inputState.guessing==0) {
				tmp297_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp297_AST);
			}
			match(FLOAT_LITERAL);
			quantityConstant_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = quantityConstant_AST;
	}
	
	public final void quantityIntervalDays() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST quantityIntervalDays_AST = null;
		
		AST tmp298_AST = null;
		tmp298_AST = (AST)astFactory.create(LT(1));
		match(AND);
		{
		if ((LA(1)==INTEGER_LITERAL||LA(1)==FLOAT_LITERAL) && (LA(2)==DAY||LA(2)==DAYS)) {
			quantityConstant();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case DAY:
			{
				AST tmp299_AST = null;
				if (inputState.guessing==0) {
					tmp299_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp299_AST);
				}
				match(DAY);
				break;
			}
			case DAYS:
			{
				AST tmp300_AST = null;
				if (inputState.guessing==0) {
					tmp300_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp300_AST);
				}
				match(DAYS);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			{
			switch ( LA(1)) {
			case AND:
			{
				quantityIntervalHours();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case SEMICOLON:
			case END:
			case ELSE:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
		}
		else if ((LA(1)==INTEGER_LITERAL||LA(1)==FLOAT_LITERAL) && (LA(2)==HOUR||LA(2)==HOURS)) {
			quantityConstant();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case HOUR:
			{
				AST tmp301_AST = null;
				if (inputState.guessing==0) {
					tmp301_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp301_AST);
				}
				match(HOUR);
				break;
			}
			case HOURS:
			{
				AST tmp302_AST = null;
				if (inputState.guessing==0) {
					tmp302_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp302_AST);
				}
				match(HOURS);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			{
			switch ( LA(1)) {
			case AND:
			{
				quantityIntervalMinutes();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case SEMICOLON:
			case END:
			case ELSE:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
		}
		else if ((LA(1)==INTEGER_LITERAL||LA(1)==FLOAT_LITERAL) && (LA(2)==MINUTE||LA(2)==MINUTES)) {
			quantityConstant();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case MINUTE:
			{
				AST tmp303_AST = null;
				if (inputState.guessing==0) {
					tmp303_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp303_AST);
				}
				match(MINUTE);
				break;
			}
			case MINUTES:
			{
				AST tmp304_AST = null;
				if (inputState.guessing==0) {
					tmp304_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp304_AST);
				}
				match(MINUTES);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			{
			switch ( LA(1)) {
			case AND:
			{
				quantityIntervalSeconds();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case SEMICOLON:
			case END:
			case ELSE:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
		}
		else if ((LA(1)==INTEGER_LITERAL||LA(1)==FLOAT_LITERAL) && (LA(2)==SECOND||LA(2)==SECONDS)) {
			quantityConstant();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case SECOND:
			{
				AST tmp305_AST = null;
				if (inputState.guessing==0) {
					tmp305_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp305_AST);
				}
				match(SECOND);
				break;
			}
			case SECONDS:
			{
				AST tmp306_AST = null;
				if (inputState.guessing==0) {
					tmp306_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp306_AST);
				}
				match(SECONDS);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
		}
		else {
			throw new NoViableAltException(LT(1));
		}
		
		}
		quantityIntervalDays_AST = (AST)currentAST.root;
		returnAST = quantityIntervalDays_AST;
	}
	
	public final void quantityIntervalHours() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST quantityIntervalHours_AST = null;
		
		AST tmp307_AST = null;
		tmp307_AST = (AST)astFactory.create(LT(1));
		match(AND);
		{
		if ((LA(1)==INTEGER_LITERAL||LA(1)==FLOAT_LITERAL) && (LA(2)==HOUR||LA(2)==HOURS)) {
			quantityConstant();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case HOUR:
			{
				AST tmp308_AST = null;
				if (inputState.guessing==0) {
					tmp308_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp308_AST);
				}
				match(HOUR);
				break;
			}
			case HOURS:
			{
				AST tmp309_AST = null;
				if (inputState.guessing==0) {
					tmp309_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp309_AST);
				}
				match(HOURS);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			{
			switch ( LA(1)) {
			case AND:
			{
				quantityIntervalMinutes();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case SEMICOLON:
			case END:
			case ELSE:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
		}
		else if ((LA(1)==INTEGER_LITERAL||LA(1)==FLOAT_LITERAL) && (LA(2)==MINUTE||LA(2)==MINUTES)) {
			quantityConstant();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case MINUTE:
			{
				AST tmp310_AST = null;
				if (inputState.guessing==0) {
					tmp310_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp310_AST);
				}
				match(MINUTE);
				break;
			}
			case MINUTES:
			{
				AST tmp311_AST = null;
				if (inputState.guessing==0) {
					tmp311_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp311_AST);
				}
				match(MINUTES);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			{
			switch ( LA(1)) {
			case AND:
			{
				quantityIntervalSeconds();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case SEMICOLON:
			case END:
			case ELSE:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
		}
		else if ((LA(1)==INTEGER_LITERAL||LA(1)==FLOAT_LITERAL) && (LA(2)==SECOND||LA(2)==SECONDS)) {
			quantityConstant();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case SECOND:
			{
				AST tmp312_AST = null;
				if (inputState.guessing==0) {
					tmp312_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp312_AST);
				}
				match(SECOND);
				break;
			}
			case SECONDS:
			{
				AST tmp313_AST = null;
				if (inputState.guessing==0) {
					tmp313_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp313_AST);
				}
				match(SECONDS);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
		}
		else {
			throw new NoViableAltException(LT(1));
		}
		
		}
		quantityIntervalHours_AST = (AST)currentAST.root;
		returnAST = quantityIntervalHours_AST;
	}
	
	public final void quantityIntervalMinutes() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST quantityIntervalMinutes_AST = null;
		
		AST tmp314_AST = null;
		tmp314_AST = (AST)astFactory.create(LT(1));
		match(AND);
		{
		if ((LA(1)==INTEGER_LITERAL||LA(1)==FLOAT_LITERAL) && (LA(2)==MINUTE||LA(2)==MINUTES)) {
			quantityConstant();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case MINUTE:
			{
				AST tmp315_AST = null;
				if (inputState.guessing==0) {
					tmp315_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp315_AST);
				}
				match(MINUTE);
				break;
			}
			case MINUTES:
			{
				AST tmp316_AST = null;
				if (inputState.guessing==0) {
					tmp316_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp316_AST);
				}
				match(MINUTES);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			{
			switch ( LA(1)) {
			case AND:
			{
				quantityIntervalSeconds();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case SEMICOLON:
			case END:
			case ELSE:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
		}
		else if ((LA(1)==INTEGER_LITERAL||LA(1)==FLOAT_LITERAL) && (LA(2)==SECOND||LA(2)==SECONDS)) {
			quantityConstant();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			switch ( LA(1)) {
			case SECOND:
			{
				AST tmp317_AST = null;
				if (inputState.guessing==0) {
					tmp317_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp317_AST);
				}
				match(SECOND);
				break;
			}
			case SECONDS:
			{
				AST tmp318_AST = null;
				if (inputState.guessing==0) {
					tmp318_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp318_AST);
				}
				match(SECONDS);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
		}
		else {
			throw new NoViableAltException(LT(1));
		}
		
		}
		quantityIntervalMinutes_AST = (AST)currentAST.root;
		returnAST = quantityIntervalMinutes_AST;
	}
	
	public final void quantityIntervalSeconds() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST quantityIntervalSeconds_AST = null;
		
		AST tmp319_AST = null;
		tmp319_AST = (AST)astFactory.create(LT(1));
		match(AND);
		quantityConstant();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		switch ( LA(1)) {
		case SECOND:
		{
			AST tmp320_AST = null;
			if (inputState.guessing==0) {
				tmp320_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp320_AST);
			}
			match(SECOND);
			break;
		}
		case SECONDS:
		{
			AST tmp321_AST = null;
			if (inputState.guessing==0) {
				tmp321_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp321_AST);
			}
			match(SECONDS);
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		quantityIntervalSeconds_AST = (AST)currentAST.root;
		returnAST = quantityIntervalSeconds_AST;
	}
	
	public final void timeKeyword() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST timeKeyword_AST = null;
		
		switch ( LA(1)) {
		case WEEK:
		{
			AST tmp322_AST = null;
			if (inputState.guessing==0) {
				tmp322_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp322_AST);
			}
			match(WEEK);
			timeKeyword_AST = (AST)currentAST.root;
			break;
		}
		case WEEKS:
		{
			AST tmp323_AST = null;
			if (inputState.guessing==0) {
				tmp323_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp323_AST);
			}
			match(WEEKS);
			timeKeyword_AST = (AST)currentAST.root;
			break;
		}
		case DAY:
		{
			AST tmp324_AST = null;
			if (inputState.guessing==0) {
				tmp324_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp324_AST);
			}
			match(DAY);
			timeKeyword_AST = (AST)currentAST.root;
			break;
		}
		case DAYS:
		{
			AST tmp325_AST = null;
			if (inputState.guessing==0) {
				tmp325_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp325_AST);
			}
			match(DAYS);
			timeKeyword_AST = (AST)currentAST.root;
			break;
		}
		case HOUR:
		{
			AST tmp326_AST = null;
			if (inputState.guessing==0) {
				tmp326_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp326_AST);
			}
			match(HOUR);
			timeKeyword_AST = (AST)currentAST.root;
			break;
		}
		case HOURS:
		{
			AST tmp327_AST = null;
			if (inputState.guessing==0) {
				tmp327_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp327_AST);
			}
			match(HOURS);
			timeKeyword_AST = (AST)currentAST.root;
			break;
		}
		case MINUTE:
		{
			AST tmp328_AST = null;
			if (inputState.guessing==0) {
				tmp328_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp328_AST);
			}
			match(MINUTE);
			timeKeyword_AST = (AST)currentAST.root;
			break;
		}
		case MINUTES:
		{
			AST tmp329_AST = null;
			if (inputState.guessing==0) {
				tmp329_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp329_AST);
			}
			match(MINUTES);
			timeKeyword_AST = (AST)currentAST.root;
			break;
		}
		case SECOND:
		{
			AST tmp330_AST = null;
			if (inputState.guessing==0) {
				tmp330_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp330_AST);
			}
			match(SECOND);
			timeKeyword_AST = (AST)currentAST.root;
			break;
		}
		case SECONDS:
		{
			AST tmp331_AST = null;
			if (inputState.guessing==0) {
				tmp331_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp331_AST);
			}
			match(SECONDS);
			timeKeyword_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = timeKeyword_AST;
	}
	
	public final void queryDesignation() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST queryDesignation_AST = null;
		
		switch ( LA(1)) {
		case UNRESERVED:
		{
			queryItemName();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			queryDesignation_AST = (AST)currentAST.root;
			break;
		}
		case THE:
		{
			AST tmp332_AST = null;
			if (inputState.guessing==0) {
				tmp332_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp332_AST);
			}
			match(THE);
			AST tmp333_AST = null;
			if (inputState.guessing==0) {
				tmp333_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp333_AST);
			}
			match(UNRESERVED);
			AST tmp334_AST = null;
			if (inputState.guessing==0) {
				tmp334_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp334_AST);
			}
			match(OF);
			localName();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			queryDesignation_AST = (AST)currentAST.root;
			break;
		}
		case EVERY:
		{
			AST tmp335_AST = null;
			if (inputState.guessing==0) {
				tmp335_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp335_AST);
			}
			match(EVERY);
			AST tmp336_AST = null;
			if (inputState.guessing==0) {
				tmp336_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp336_AST);
			}
			match(UNRESERVED);
			{
			switch ( LA(1)) {
			case UNRESERVED:
			{
				localName();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case NOT:
			case IN:
			case SUCH:
			case CONTAINING:
			case WITH:
			case WHOSE:
			case ASSIGNED:
			case WHERE:
			case WHICH:
			case FOUND:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			queryRestrictions();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			queryDesignation_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = queryDesignation_AST;
	}
	
	public final void queryItemName() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST queryItemName_AST = null;
		
		localName();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		queryItemName_AST = (AST)currentAST.root;
		returnAST = queryItemName_AST;
	}
	
	public final void queryRestrictions() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST queryRestrictions_AST = null;
		
		queryDisjunct();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		_loop228:
		do {
			if ((LA(1)==OR)) {
				AST tmp337_AST = null;
				if (inputState.guessing==0) {
					tmp337_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp337_AST);
				}
				match(OR);
				queryDisjunct();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
			}
			else {
				break _loop228;
			}
			
		} while (true);
		}
		queryRestrictions_AST = (AST)currentAST.root;
		returnAST = queryRestrictions_AST;
	}
	
	public final void queryDisjunct() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST queryDisjunct_AST = null;
		
		queryConjunct();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		{
		_loop231:
		do {
			if ((LA(1)==AND)) {
				AST tmp338_AST = null;
				if (inputState.guessing==0) {
					tmp338_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp338_AST);
				}
				match(AND);
				queryConjunct();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
			}
			else {
				break _loop231;
			}
			
		} while (true);
		}
		queryDisjunct_AST = (AST)currentAST.root;
		returnAST = queryDisjunct_AST;
	}
	
	public final void queryConjunct() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST queryConjunct_AST = null;
		
		{
		switch ( LA(1)) {
		case NOT:
		{
			AST tmp339_AST = null;
			if (inputState.guessing==0) {
				tmp339_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp339_AST);
			}
			match(NOT);
			break;
		}
		case IN:
		case SUCH:
		case CONTAINING:
		case WITH:
		case WHOSE:
		case ASSIGNED:
		case WHERE:
		case WHICH:
		case FOUND:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		queryRestriction();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		queryConjunct_AST = (AST)currentAST.root;
		returnAST = queryConjunct_AST;
	}
	
	public final void queryRestriction() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST queryRestriction_AST = null;
		
		switch ( LA(1)) {
		case SUCH:
		{
			AST tmp340_AST = null;
			if (inputState.guessing==0) {
				tmp340_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp340_AST);
			}
			match(SUCH);
			AST tmp341_AST = null;
			if (inputState.guessing==0) {
				tmp341_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp341_AST);
			}
			match(THAT);
			conjunct();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			queryRestriction_AST = (AST)currentAST.root;
			break;
		}
		case CONTAINING:
		{
			AST tmp342_AST = null;
			if (inputState.guessing==0) {
				tmp342_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp342_AST);
			}
			match(CONTAINING);
			AST tmp343_AST = null;
			if (inputState.guessing==0) {
				tmp343_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp343_AST);
			}
			match(THE);
			{
			switch ( LA(1)) {
			case WORD:
			{
				AST tmp344_AST = null;
				if (inputState.guessing==0) {
					tmp344_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp344_AST);
				}
				match(WORD);
				break;
			}
			case SYMBOL:
			{
				AST tmp345_AST = null;
				if (inputState.guessing==0) {
					tmp345_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp345_AST);
				}
				match(SYMBOL);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			{
			switch ( LA(1)) {
			case WHOLE_STRING_LITERAL:
			{
				AST tmp346_AST = null;
				if (inputState.guessing==0) {
					tmp346_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp346_AST);
				}
				match(WHOLE_STRING_LITERAL);
				break;
			}
			case UNRESERVED:
			{
				AST tmp347_AST = null;
				if (inputState.guessing==0) {
					tmp347_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp347_AST);
				}
				match(UNRESERVED);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			queryRestriction_AST = (AST)currentAST.root;
			break;
		}
		case WITH:
		{
			AST tmp348_AST = null;
			if (inputState.guessing==0) {
				tmp348_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp348_AST);
			}
			match(WITH);
			{
			switch ( LA(1)) {
			case NOTES:
			{
				AST tmp349_AST = null;
				if (inputState.guessing==0) {
					tmp349_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp349_AST);
				}
				match(NOTES);
				break;
			}
			case CHANGES:
			{
				AST tmp350_AST = null;
				if (inputState.guessing==0) {
					tmp350_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp350_AST);
				}
				match(CHANGES);
				AST tmp351_AST = null;
				if (inputState.guessing==0) {
					tmp351_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp351_AST);
				}
				match(LOGGED);
				AST tmp352_AST = null;
				if (inputState.guessing==0) {
					tmp352_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp352_AST);
				}
				match(BY);
				AST tmp353_AST = null;
				if (inputState.guessing==0) {
					tmp353_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp353_AST);
				}
				match(UNRESERVED);
				{
				switch ( LA(1)) {
				case AFTER:
				case BEFORE:
				{
					queryInterval();
					if (inputState.guessing==0) {
						astFactory.addASTChild(currentAST, returnAST);
					}
					break;
				}
				case EOF:
				case AND:
				case OR:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1));
				}
				}
				}
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			queryRestriction_AST = (AST)currentAST.root;
			break;
		}
		case WHOSE:
		{
			AST tmp354_AST = null;
			if (inputState.guessing==0) {
				tmp354_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp354_AST);
			}
			match(WHOSE);
			AST tmp355_AST = null;
			if (inputState.guessing==0) {
				tmp355_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp355_AST);
			}
			match(STATUS);
			AST tmp356_AST = null;
			if (inputState.guessing==0) {
				tmp356_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp356_AST);
			}
			match(IS);
			frameStatus();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			queryRestriction_AST = (AST)currentAST.root;
			break;
		}
		case ASSIGNED:
		{
			AST tmp357_AST = null;
			if (inputState.guessing==0) {
				tmp357_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp357_AST);
			}
			match(ASSIGNED);
			AST tmp358_AST = null;
			if (inputState.guessing==0) {
				tmp358_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp358_AST);
			}
			match(TO);
			{
			switch ( LA(1)) {
			case HIERARCHY:
			{
				AST tmp359_AST = null;
				if (inputState.guessing==0) {
					tmp359_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp359_AST);
				}
				match(HIERARCHY);
				AST tmp360_AST = null;
				if (inputState.guessing==0) {
					tmp360_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp360_AST);
				}
				match(OF);
				break;
			}
			case MODULE:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			AST tmp361_AST = null;
			if (inputState.guessing==0) {
				tmp361_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp361_AST);
			}
			match(MODULE);
			AST tmp362_AST = null;
			if (inputState.guessing==0) {
				tmp362_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp362_AST);
			}
			match(UNRESERVED);
			queryRestriction_AST = (AST)currentAST.root;
			break;
		}
		case WHERE:
		{
			AST tmp363_AST = null;
			if (inputState.guessing==0) {
				tmp363_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp363_AST);
			}
			match(WHERE);
			AST tmp364_AST = null;
			if (inputState.guessing==0) {
				tmp364_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp364_AST);
			}
			match(UNRESERVED);
			{
			switch ( LA(1)) {
			case EQUALS:
			case GREATER:
			case LESS:
			case NOT_EQUAL:
			case GREATER_EQUAL:
			case LESS_EQUAL:
			{
				queryComparator();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				constant();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
				break;
			}
			case TRUTH_VALUE_LITERAL:
			{
				AST tmp365_AST = null;
				if (inputState.guessing==0) {
					tmp365_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp365_AST);
				}
				match(TRUTH_VALUE_LITERAL);
				break;
			}
			case UNRESERVED:
			case NOT:
			{
				{
				switch ( LA(1)) {
				case NOT:
				{
					AST tmp366_AST = null;
					if (inputState.guessing==0) {
						tmp366_AST = (AST)astFactory.create(LT(1));
						astFactory.addASTChild(currentAST, tmp366_AST);
					}
					match(NOT);
					break;
				}
				case UNRESERVED:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1));
				}
				}
				}
				AST tmp367_AST = null;
				if (inputState.guessing==0) {
					tmp367_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp367_AST);
				}
				match(UNRESERVED);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			queryRestriction_AST = (AST)currentAST.root;
			break;
		}
		case IN:
		{
			AST tmp368_AST = null;
			if (inputState.guessing==0) {
				tmp368_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp368_AST);
			}
			match(IN);
			AST tmp369_AST = null;
			if (inputState.guessing==0) {
				tmp369_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp369_AST);
			}
			match(THE);
			AST tmp370_AST = null;
			if (inputState.guessing==0) {
				tmp370_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp370_AST);
			}
			match(CATEGORY);
			AST tmp371_AST = null;
			if (inputState.guessing==0) {
				tmp371_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp371_AST);
			}
			match(UNRESERVED);
			queryRestriction_AST = (AST)currentAST.root;
			break;
		}
		case WHICH:
		{
			AST tmp372_AST = null;
			if (inputState.guessing==0) {
				tmp372_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp372_AST);
			}
			match(WHICH);
			AST tmp373_AST = null;
			if (inputState.guessing==0) {
				tmp373_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp373_AST);
			}
			match(HAS);
			AST tmp374_AST = null;
			if (inputState.guessing==0) {
				tmp374_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp374_AST);
			}
			match(THE);
			AST tmp375_AST = null;
			if (inputState.guessing==0) {
				tmp375_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp375_AST);
			}
			match(FOCAL);
			{
			switch ( LA(1)) {
			case CLASS:
			{
				AST tmp376_AST = null;
				if (inputState.guessing==0) {
					tmp376_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp376_AST);
				}
				match(CLASS);
				break;
			}
			case OBJECT:
			{
				AST tmp377_AST = null;
				if (inputState.guessing==0) {
					tmp377_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp377_AST);
				}
				match(OBJECT);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1));
			}
			}
			}
			AST tmp378_AST = null;
			if (inputState.guessing==0) {
				tmp378_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp378_AST);
			}
			match(UNRESERVED);
			queryRestriction_AST = (AST)currentAST.root;
			break;
		}
		case FOUND:
		{
			AST tmp379_AST = null;
			if (inputState.guessing==0) {
				tmp379_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp379_AST);
			}
			match(FOUND);
			AST tmp380_AST = null;
			if (inputState.guessing==0) {
				tmp380_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp380_AST);
			}
			match(ON);
			AST tmp381_AST = null;
			if (inputState.guessing==0) {
				tmp381_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp381_AST);
			}
			match(THE);
			AST tmp382_AST = null;
			if (inputState.guessing==0) {
				tmp382_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp382_AST);
			}
			match(WORKSPACE);
			queryRestriction_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = queryRestriction_AST;
	}
	
	public final void queryInterval() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST queryInterval_AST = null;
		
		switch ( LA(1)) {
		case BEFORE:
		{
			AST tmp383_AST = null;
			if (inputState.guessing==0) {
				tmp383_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp383_AST);
			}
			match(BEFORE);
			date();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			{
			int[] tokenArray = new int[] {EOF, NOT, IN, SUCH, CONTAINING, WITH, WHOSE, ASSIGNED, WHERE, WHICH, FOUND};
			
			if ((LA(1)==AND) && (LA(2)==AFTER)) {
				AST tmp384_AST = null;
				if (inputState.guessing==0) {
					tmp384_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp384_AST);
				}
				match(AND);
				AST tmp385_AST = null;
				if (inputState.guessing==0) {
					tmp385_AST = (AST)astFactory.create(LT(1));
					astFactory.addASTChild(currentAST, tmp385_AST);
				}
				match(AFTER);
				date();
				if (inputState.guessing==0) {
					astFactory.addASTChild(currentAST, returnAST);
				}
			}
			else if (Arrays.asList(EOF, AND, OR).contains(LA(1)) && Arrays.asList(tokenArray).contains(LA(2))) {
			}
			else {
				throw new NoViableAltException(LT(1));
			}
			
			}
			queryInterval_AST = (AST)currentAST.root;
			break;
		}
		case AFTER:
		{
			AST tmp386_AST = null;
			if (inputState.guessing==0) {
				tmp386_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp386_AST);
			}
			match(AFTER);
			date();
			if (inputState.guessing==0) {
				astFactory.addASTChild(currentAST, returnAST);
			}
			queryInterval_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = queryInterval_AST;
	}
	
	public final void frameStatus() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST frameStatus_AST = null;
		
		switch ( LA(1)) {
		case ENABLED:
		{
			AST tmp387_AST = null;
			if (inputState.guessing==0) {
				tmp387_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp387_AST);
			}
			match(ENABLED);
			frameStatus_AST = (AST)currentAST.root;
			break;
		}
		case DISABLED:
		{
			AST tmp388_AST = null;
			if (inputState.guessing==0) {
				tmp388_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp388_AST);
			}
			match(DISABLED);
			frameStatus_AST = (AST)currentAST.root;
			break;
		}
		case OK:
		{
			AST tmp389_AST = null;
			if (inputState.guessing==0) {
				tmp389_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp389_AST);
			}
			match(OK);
			frameStatus_AST = (AST)currentAST.root;
			break;
		}
		case INACTIVE:
		{
			AST tmp390_AST = null;
			if (inputState.guessing==0) {
				tmp390_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp390_AST);
			}
			match(INACTIVE);
			frameStatus_AST = (AST)currentAST.root;
			break;
		}
		case BAD:
		{
			AST tmp391_AST = null;
			if (inputState.guessing==0) {
				tmp391_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp391_AST);
			}
			match(BAD);
			frameStatus_AST = (AST)currentAST.root;
			break;
		}
		case INCOMPLETE:
		{
			AST tmp392_AST = null;
			if (inputState.guessing==0) {
				tmp392_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp392_AST);
			}
			match(INCOMPLETE);
			frameStatus_AST = (AST)currentAST.root;
			break;
		}
		case ACTIVE:
		{
			AST tmp393_AST = null;
			if (inputState.guessing==0) {
				tmp393_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp393_AST);
			}
			match(ACTIVE);
			frameStatus_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = frameStatus_AST;
	}
	
	public final void queryComparator() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST queryComparator_AST = null;
		
		{
		switch ( LA(1)) {
		case EQUALS:
		{
			AST tmp394_AST = null;
			if (inputState.guessing==0) {
				tmp394_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp394_AST);
			}
			match(EQUALS);
			break;
		}
		case GREATER:
		{
			AST tmp395_AST = null;
			if (inputState.guessing==0) {
				tmp395_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp395_AST);
			}
			match(GREATER);
			break;
		}
		case LESS:
		{
			AST tmp396_AST = null;
			if (inputState.guessing==0) {
				tmp396_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp396_AST);
			}
			match(LESS);
			break;
		}
		case NOT_EQUAL:
		{
			AST tmp397_AST = null;
			if (inputState.guessing==0) {
				tmp397_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp397_AST);
			}
			match(NOT_EQUAL);
			break;
		}
		case GREATER_EQUAL:
		{
			AST tmp398_AST = null;
			if (inputState.guessing==0) {
				tmp398_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp398_AST);
			}
			match(GREATER_EQUAL);
			break;
		}
		case LESS_EQUAL:
		{
			AST tmp399_AST = null;
			if (inputState.guessing==0) {
				tmp399_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp399_AST);
			}
			match(LESS_EQUAL);
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		}
		queryComparator_AST = (AST)currentAST.root;
		returnAST = queryComparator_AST;
	}
	
	public final void date() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST date_AST = null;
		
		AST tmp400_AST = null;
		if (inputState.guessing==0) {
			tmp400_AST = (AST)astFactory.create(LT(1));
			astFactory.addASTChild(currentAST, tmp400_AST);
		}
		match(INTEGER_LITERAL);
		month();
		if (inputState.guessing==0) {
			astFactory.addASTChild(currentAST, returnAST);
		}
		AST tmp401_AST = null;
		if (inputState.guessing==0) {
			tmp401_AST = (AST)astFactory.create(LT(1));
			astFactory.addASTChild(currentAST, tmp401_AST);
		}
		match(INTEGER_LITERAL);
		date_AST = (AST)currentAST.root;
		returnAST = date_AST;
	}
	
	public final void month() throws ParserException, IOException {
		
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST month_AST = null;
		
		switch ( LA(1)) {
		case JAN:
		{
			AST tmp402_AST = null;
			if (inputState.guessing==0) {
				tmp402_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp402_AST);
			}
			match(JAN);
			month_AST = (AST)currentAST.root;
			break;
		}
		case FEB:
		{
			AST tmp403_AST = null;
			if (inputState.guessing==0) {
				tmp403_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp403_AST);
			}
			match(FEB);
			month_AST = (AST)currentAST.root;
			break;
		}
		case MAR:
		{
			AST tmp404_AST = null;
			if (inputState.guessing==0) {
				tmp404_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp404_AST);
			}
			match(MAR);
			month_AST = (AST)currentAST.root;
			break;
		}
		case APR:
		{
			AST tmp405_AST = null;
			if (inputState.guessing==0) {
				tmp405_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp405_AST);
			}
			match(APR);
			month_AST = (AST)currentAST.root;
			break;
		}
		case MAY:
		{
			AST tmp406_AST = null;
			if (inputState.guessing==0) {
				tmp406_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp406_AST);
			}
			match(MAY);
			month_AST = (AST)currentAST.root;
			break;
		}
		case JUN:
		{
			AST tmp407_AST = null;
			if (inputState.guessing==0) {
				tmp407_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp407_AST);
			}
			match(JUN);
			month_AST = (AST)currentAST.root;
			break;
		}
		case JUL:
		{
			AST tmp408_AST = null;
			if (inputState.guessing==0) {
				tmp408_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp408_AST);
			}
			match(JUL);
			month_AST = (AST)currentAST.root;
			break;
		}
		case AUG:
		{
			AST tmp409_AST = null;
			if (inputState.guessing==0) {
				tmp409_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp409_AST);
			}
			match(AUG);
			month_AST = (AST)currentAST.root;
			break;
		}
		case SEP:
		{
			AST tmp410_AST = null;
			if (inputState.guessing==0) {
				tmp410_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp410_AST);
			}
			match(SEP);
			month_AST = (AST)currentAST.root;
			break;
		}
		case OCT:
		{
			AST tmp411_AST = null;
			if (inputState.guessing==0) {
				tmp411_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp411_AST);
			}
			match(OCT);
			month_AST = (AST)currentAST.root;
			break;
		}
		case NOV:
		{
			AST tmp412_AST = null;
			if (inputState.guessing==0) {
				tmp412_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp412_AST);
			}
			match(NOV);
			month_AST = (AST)currentAST.root;
			break;
		}
		case DEC:
		{
			AST tmp413_AST = null;
			if (inputState.guessing==0) {
				tmp413_AST = (AST)astFactory.create(LT(1));
				astFactory.addASTChild(currentAST, tmp413_AST);
			}
			match(DEC);
			month_AST = (AST)currentAST.root;
			break;
		}
		default:
		{
			throw new NoViableAltException(LT(1));
		}
		}
		returnAST = month_AST;
	}
	
	
	public static final String[] _tokenNames = {
		"<0>",
		"EOF",
		"<2>",
		"NULL_TREE_LOOKAHEAD",
		"UNRESERVED",
		"INTEGER_LITERAL",
		"FLOAT_LITERAL",
		"TRUTH_VALUE_LITERAL",
		"WHOLE_STRING_LITERAL",
		"LEFT_STRING_LITERAL",
		"MIDDLE_STRING_LITERAL",
		"RIGHT_STRING_LITERAL",
		"<12>",
		"<13>",
		"<14>",
		"<15>",
		"<16>",
		"<17>",
		"<18>",
		"<19>",
		"<20>",
		"<21>",
		"<22>",
		"<23>",
		"<24>",
		"<25>",
		"<26>",
		"<27>",
		"<28>",
		"<29>",
		"<30>",
		"<31>",
		"<32>",
		"<33>",
		"<34>",
		"<35>",
		"<36>",
		"<37>",
		"<38>",
		"<39>",
		"<40>",
		"<41>",
		"<42>",
		"<43>",
		"<44>",
		"<45>",
		"<46>",
		"<47>",
		"<48>",
		"<49>",
		"<50>",
		"<51>",
		"<52>",
		"<53>",
		"<54>",
		"<55>",
		"<56>",
		"<57>",
		"<58>",
		"<59>",
		"<60>",
		"<61>",
		"<62>",
		"<63>",
		"<64>",
		"<65>",
		"<66>",
		"<67>",
		"<68>",
		"<69>",
		"<70>",
		"<71>",
		"<72>",
		"<73>",
		"<74>",
		"<75>",
		"<76>",
		"<77>",
		"<78>",
		"<79>",
		"<80>",
		"<81>",
		"<82>",
		"<83>",
		"<84>",
		"<85>",
		"<86>",
		"<87>",
		"<88>",
		"<89>",
		"<90>",
		"<91>",
		"<92>",
		"<93>",
		"<94>",
		"<95>",
		"<96>",
		"<97>",
		"<98>",
		"<99>",
		"LPAREN",
		"RPAREN",
		"COMMA",
		"COLON",
		"SEMICOLON",
		"PLUS",
		"TIMES",
		"EQUALS",
		"MINUS",
		"SLASH",
		"LBRACK",
		"RBRACK",
		"GREATER",
		"LESS",
		"NOT_EQUAL",
		"GREATER_EQUAL",
		"LESS_EQUAL",
		"PERIOD",
		"<118>",
		"<119>",
		"<120>",
		"<121>",
		"<122>",
		"<123>",
		"<124>",
		"<125>",
		"<126>",
		"<127>",
		"<128>",
		"<129>",
		"<130>",
		"<131>",
		"<132>",
		"<133>",
		"<134>",
		"<135>",
		"<136>",
		"<137>",
		"<138>",
		"<139>",
		"<140>",
		"<141>",
		"<142>",
		"<143>",
		"<144>",
		"<145>",
		"<146>",
		"<147>",
		"<148>",
		"<149>",
		"<150>",
		"<151>",
		"<152>",
		"<153>",
		"<154>",
		"<155>",
		"<156>",
		"<157>",
		"<158>",
		"<159>",
		"<160>",
		"<161>",
		"<162>",
		"<163>",
		"<164>",
		"<165>",
		"<166>",
		"<167>",
		"<168>",
		"<169>",
		"<170>",
		"<171>",
		"<172>",
		"<173>",
		"<174>",
		"<175>",
		"<176>",
		"<177>",
		"<178>",
		"<179>",
		"<180>",
		"<181>",
		"<182>",
		"<183>",
		"<184>",
		"<185>",
		"<186>",
		"<187>",
		"<188>",
		"<189>",
		"<190>",
		"<191>",
		"<192>",
		"<193>",
		"<194>",
		"<195>",
		"<196>",
		"<197>",
		"<198>",
		"<199>",
		"<200>",
		"CALL",
		"BEGIN",
		"END",
		"INTEGER",
		"FLOAT",
		"TRUTH_VALUE",
		"TEXT",
		"THE",
		"SYMBOL",
		"IF",
		"THEN",
		"ELSE",
		"IS",
		"NOT",
		"AND",
		"OR",
		"OF",
		"CREATE",
		"A",
		"AN",
		"BY",
		"CLONING",
		"DELETE",
		"INFORM",
		"OPERATOR",
		"CONCLUDE",
		"THAT",
		"SAME",
		"OBJECT",
		"AS",
		"CLASS",
		"FOR",
		"DO",
		"WHILE",
		"REPEAT",
		"EXIT",
		"ON",
		"ERROR",
		"TO",
		"DOWN",
		"EACH",
		"RETURN",
		"METHODS",
		"FIELDS",
		"CLASS_METHODS",
		"CLASS_FIELDS",
		"SIGNAL",
		"START",
		"QUANTITY",
		"CHANGE",
		"AT",
		"PRIORITY",
		"AFTER",
		"WAIT",
		"ALLOW",
		"OTHER",
		"PROCESSING",
		"SEQUENCE",
		"STRUCTURE",
		"HAS",
		"NO",
		"VALUE",
		"ITEM_OR_VALUE",
		"EXISTS",
		"EXIST",
		"DOES",
		"NAMED",
		"PROCEDURE",
		"METHOD",
		"NEW",
		"WHENEVER",
		"WHEN",
		"UNCONDITIONALLY",
		"INITIALLY",
		"RECEIVES",
		"EVENT",
		"IN",
		"ORDER",
		"ANY",
		"WEEK",
		"WEEKS",
		"DAY",
		"DAYS",
		"HOUR",
		"HOURS",
		"MINUTE",
		"MINUTES",
		"SECOND",
		"SECONDS",
		"CURRENT",
		"SUBSECOND",
		"REAL",
		"TIME",
		"THERE",
		"SUCH",
		"EVERY",
		"CONTAINING",
		"WORD",
		"WITH",
		"NOTES",
		"CHANGES",
		"LOGGED",
		"BEFORE",
		"<304>",
		"WHOSE",
		"STATUS",
		"ASSIGNED",
		"MODULE",
		"HIERARCHY",
		"WHERE",
		"CATEGORY",
		"FOCAL",
		"WHICH",
		"FOUND",
		"WORKSPACE",
		"ENABLED",
		"DISABLED",
		"OK",
		"INACTIVE",
		"BAD",
		"INCOMPLETE",
		"ACTIVE",
		"JAN",
		"FEB",
		"MAR",
		"APR",
		"MAY",
		"JUN",
		"JUL",
		"AUG",
		"SEP",
		"OCT",
		"NOV",
		"DEC",
		"NUMBER",
		"ELEMENTS",
		"ICON_COLOR",
		"CONNECTED",
		"INPUT",
		"OUTPUT",
		"UPON"
	};
	
	
	}
