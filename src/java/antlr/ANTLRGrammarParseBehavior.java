package antlr;

/**
 * <b>SOFTWARE RIGHTS</b>
 * <p>
 * ANTLR 2.6.0 MageLang Institute
 * <p>
 * We reserve no legal rights to the ANTLR--it is fully in the
 * public domain. An individual or company may do whatever
 * they wish with source code distributed with ANTLR or the
 * code generated by ANTLR, including the incorporation of
 * ANTLR, or its output, into commerical software.
 * <p>
 * We encourage users to develop software with ANTLR. However,
 * we do ask that credit is given to us for developing
 * ANTLR. By "credit", we mean that if you use ANTLR or
 * incorporate any source code into one of your programs
 * (commercial product, research project, or otherwise) that
 * you acknowledge this fact somewhere in the documentation,
 * research report, etc... If you like ANTLR and have
 * developed a nice tool with the output, please mention that
 * you developed it using ANTLR. In addition, we ask that the
 * headers remain intact in our source code. As long as these
 * guidelines are kept, we expect to continue enhancing this
 * system and expect to make other tools available as they are
 * completed.
 * <p>
 * The ANTLR gang:
 * @version ANTLR 2.6.0 MageLang Institute
 * @author Terence Parr, <a href=http://www.MageLang.com>MageLang Institute</a>
 * @author <br>John Lilley, <a href=http://www.Empathy.com>Empathy Software</a>
 */
import antlr.collections.impl.BitSet;

public interface ANTLRGrammarParseBehavior {
	public void abortGrammar();
	public void beginAlt(boolean doAST_);
	public void beginChildList();
	// Exception handling
	public void beginExceptionGroup();
	public void beginExceptionSpec(Token label);
	public void beginSubRule(Token label, int line, boolean not);
	// Trees
	public void beginTree(int line)  throws SemanticException ;
	public void defineRuleName(Token r, String access, boolean ruleAST, String docComment) throws SemanticException;
	public void defineToken(Token tokname, Token tokliteral);
	public void endAlt();
	public void endChildList();
	public void endExceptionGroup();
	public void endExceptionSpec();
	public void endGrammar();
	public void endOptions();
	public void endRule(String r);
	public void endSubRule();
	public void endTree();
	public void hasError();
	public void noASTSubRule();
	public void oneOrMoreSubRule();
	public void optionalSubRule();
	public void refAction(Token action);
	public void refArgAction(Token action);
	public void refCharLiteral(Token lit, Token label, boolean inverted, int autoGenType, boolean lastInRule);
	public void refCharRange(Token t1, Token t2, Token label, int autoGenType, boolean lastInRule);
	public void refExceptionHandler(Token exTypeAndName, String action);
	public void refHeaderAction(Token act);
	public void refInitAction(Token action);
	public void refMemberAction(Token act);
	public void refPreambleAction(Token act);
	public void refReturnAction(Token returnAction);
	public void refRule(Token idAssign, Token r, Token label, Token arg, int autoGenType);
	public void refSemPred(Token pred);
	public void refStringLiteral(Token lit, Token label, int autoGenType, boolean lastInRule);
	public void refToken(Token assignId, Token t, Token label, Token args,
		boolean inverted, int autoGenType, boolean lastInRule);
	public void refTokenRange(Token t1, Token t2, Token label, int autoGenType, boolean lastInRule);
	// Tree specifiers
	public void refTreeSpecifier(Token treeSpec);
	public void refWildcard(Token t, Token label, int autoGenType);
	public void setArgOfRuleRef(Token argaction);
	public void setCharVocabulary(BitSet b);
	// Options
	public void setFileOption(Token key, Token value, String filename);
	public void setGrammarOption(Token key, Token value);
	public void setRuleOption(Token key, Token value);
	public void setSubruleOption(Token key, Token value);
	public void startLexer(String file, Token name, String superClass, String doc);
	// Flow control for grammars
	public void startParser(String file, Token name, String superClass, String doc);
	public void startTreeWalker(String file, Token name, String superClass, String doc);
	public void synPred();
	public void zeroOrMoreSubRule();
}