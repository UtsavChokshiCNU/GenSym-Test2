
package antlr;

import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Stack;
import antlr.collections.impl.BitSet;
import antlr.collections.impl.Vector;
import java.io.PrintStream;
import java.io.IOException;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;

/**Generate MyParser.java, MyLexer.java and MyParserTokenTypes.java */
public class TraceableJavaCodeGenerator extends JavaCodeGenerator 
{
  private int depth = 0;
  private boolean goryDetails = false;
  private boolean inParserGrammar = false;
  private boolean inLexerGrammar = false;
  private boolean inSynPred = false;
  private Stack stack = new Stack();
  private boolean goryAltTrace = false;
  private Vector ruleNodes = new Vector();
  private ObjectOutputStream oos;
  private boolean firstParserRuleEmitted = false;
  private boolean firstLexerRuleEmitted = false;
  

  /*
    4  ensure that all low-level tokens are represented
    4.1 getting correct text for non stringliteral tokens
    4.2 getting real token text rather than "lp:LPAREN" is in some cases
    5  token text
    6  trace can tell us which rule we're in but how far is
         another problem.  We could count non-terms in each match matched
	 and help with logicalORexp AND logicalOrExp  OR   (foo)*
    6.1 maintain stack in parser trace
         - all exits in some level incff per rule number counts, which could lead us to guessing where we are in that level
    6.2 postpone 6.1 until basic mechanism is in place for Craig to play with.
   */

  private void pushNode(int type)
  {
    stack.push(new TraceNode(type));
  }

  private void extendTopNode(int type, String text)
  {
    TraceNode topNode = (TraceNode)stack.peek();
    topNode.extendSubNodes(new TraceNode(type,text));
  }

  private void popNode()
  {
    TraceNode innerNode = (TraceNode)stack.pop();
    TraceNode outerNode = (TraceNode)stack.peek();
    outerNode.extendSubNodes(innerNode);
  }

  private boolean doOutput()
  {
    return inParserGrammar && !inSynPred;
  }

  public TraceableJavaCodeGenerator() 
  {
    super();
  }

  public void gen() 
  {
    enter("gen()");
    super.gen();
    exit();
  }
  
  public void gen(ActionElement action) 
  {
    enter("ActionElement = "+action);
    super.gen(action);
    exit();
  }

  public void gen(AlternativeBlock blk) 
  {
    enter("AlternativeBlock = "+blk);
    if (doOutput())
      {
	String before, after;
	int altCount = blk.getAlternatives().size();
	if (altCount == 2)
	  {
	    before = " (";
	    after = ")?";
	    pushNode(TraceNode.OPTIONAL);
	  }
	else
	  {
	    before = " ALT"+altCount+"(";
	    after = ")";
	    pushNode(TraceNode.ALT);
	  }
	System.out.print(before);
	Vector alts = blk.getAlternatives();
	int i,len = alts.size();
	if (goryAltTrace)
	  for (i=0; i<len; i++)
	    {
	      Object alt = alts.elementAt(i);
	      System.out.println("\nALTERNATIVE "+alt.getClass()+
				 " is "+alt);
	      if (alt instanceof Alternative)
		{
		  Alternative alternative = (Alternative)alt;
		  System.out.println("  atStart"+alternative.atStart());
		  AlternativeElement elt = alternative.head;
		  int count = 0;
		  while (elt != null)
		    {
		      System.out.println("  "+count+" a "+elt.getClass()+" is "+elt);
		      elt = elt.next;
		      count++;
		    }
		}
	    }
	super.gen(blk);
	System.out.print(after);
	popNode();
      }
    else
      super.gen(blk);
    exit();
  }

  public void gen(BlockEndElement end) 
  {
    enter("BlockEndElement = "+end);
    if (doOutput())
      System.out.print("<bee>");
    super.gen(end);
    exit();
  }

  public void gen(CharLiteralElement atom) 
  {
    enter("CharLiteralElement = "+atom);
    super.gen(atom);
    exit();
  }
  
  public void gen(CharRangeElement r) 
  {
    enter("CharRangeElement = "+r);
    super.gen(r);
    exit();
  }

  public  void gen(LexerGrammar g) throws IOException 
  {
    enter("LexerGrammar = "+g);
    inLexerGrammar = true;
    super.gen(g);
    inLexerGrammar = false;
    exit();
  }
  
  public void gen(OneOrMoreBlock blk) 
  {
    enter("OneOrMoreBlock = "+blk);
    if (doOutput())
      {
	System.out.print(" (");
	pushNode(TraceNode.ONE_OR_MORE);
      }
    super.gen(blk);
    if (doOutput())
      {
	System.out.print(")+");
	popNode();
      }
    exit();
  }

  /*
  public void gen(OptionalBlock blk) 
  {
    enter("OptionalBlock = "+blk);
    super.gen(blk);
    exit();
  }
  */

  public void gen(ParserGrammar g) throws IOException 
  {
    enter("ParserGrammar = "+g);
    inParserGrammar = true;
    String filename = g.getFilename();
    String objectFilename;
    int index = filename.lastIndexOf('.');
    if (index == -1)
      objectFilename = filename+".ipi";
    else
      objectFilename = filename.substring(0,index)+".ipi";
    try {
      oos = new ObjectOutputStream(new FileOutputStream(objectFilename));
    } catch (IOException ioe)
      {
	ioe.printStackTrace();
	throw new RuntimeException("IO Failure in generating traceable grammar");
      }
    String oldThrowNoViable = throwNoViable;
    throwNoViable = "throwNoViableAlt(LT(1));";
    super.gen(g);
    throwNoViable = oldThrowNoViable;
    inParserGrammar = false;
    try {
      int i,len = ruleNodes.size();
      oos.writeInt(1); // version
      oos.writeInt(len);
      for (i=0; i<len; i++)
	oos.writeObject(ruleNodes.elementAt(i));
      oos.close();
    } catch (IOException ioe)
      {
	ioe.printStackTrace();
	throw new RuntimeException("IO Failure in generating traceable grammar");
      }
    exit();
  }

  public void gen(RuleRefElement rr) 
  {
    enter("RuleRefElement = "+rr);
    if (doOutput())
      {
	System.out.print(" "+rr);
	extendTopNode(TraceNode.RULE_REF,""+rr);
      }
    super.gen(rr);
    exit();
  }
  
  public void gen(StringLiteralElement atom)
  {
    enter("StringLiteralElement = "+atom);
    if (doOutput())
      {
	System.out.print(""+atom);
	extendTopNode(TraceNode.LITERAL,""+atom);
      }
    super.gen(atom);
    exit();
  }
  
  public void gen(TokenRangeElement r) 
  {
    enter("TokenRangeElement = "+r);
    super.gen(r);
    exit();
  }
  
  public void gen(TokenRefElement atom) 
  {
    enter("TokenRefElement = "+atom);
    if (doOutput())
      {
	System.out.print(" "+atom);
	extendTopNode(TraceNode.TOKEN_REF,""+atom);
      }
    super.gen(atom);
    exit();
  }

  public void gen(TreeElement t)
  {
    enter("TreeElement = "+t);
    super.gen(t);
    exit();
  }

  public void gen(TreeWalkerGrammar g) throws IOException 
  {
    enter("TreeWalkerGrammar = "+g);
    super.gen(g);
    exit();
  }
  
  public void gen(WildcardElement wc) 
  {
    enter("WildcardElement = "+wc);
    if (doOutput())
      System.out.print("<wild>");
    super.gen(wc);
    exit();
  }
  
  public void gen(ZeroOrMoreBlock blk) 
  {
    enter("ZeroOrMoreBlock = "+blk);
    if (doOutput())
      {
	System.out.print(" (");
	pushNode(TraceNode.ZERO_OR_MORE);
      }
    super.gen(blk);
    if (doOutput())
      {
	System.out.print(")*");
	popNode();
      }
    exit();
  }

  protected void genAlt(Alternative alt, AlternativeBlock blk)
  {
    enter("genAlt Alternative = "+alt+" AlternativeBlock = "+blk);
    boolean real = false;
    if (doOutput())
      {
	real = true;
	Vector alts = blk.getAlternatives();
	if (alt == alts.elementAt(0))
	  System.out.print("<BSE>");
	else if (alt.head instanceof BlockEndElement)
	  {
	    System.out.print("<BEE>");
	    real = false;
	  }
	else if (blk instanceof RuleBlock)
	  System.out.println("  | ");
	else
	  System.out.print(" | ");
	if (real)
	  pushNode(TraceNode.SEQ);
      }
    super.genAlt(alt,blk);
    if (real)
      popNode();
    exit();
  }
  
  protected void genBitsets(Vector bitsetList,
			    int maxVocabulary)
  {
    enter("genBitsets bitset = "+bitsetList+" maxVocab = "+maxVocabulary);
    super.genBitsets(bitsetList,maxVocabulary);
    exit();
  }

  protected void genBlockPreamble(AlternativeBlock blk) 
  {
    enter("genBlockPreamble AlternativeBlock = "+blk);
    super.genBlockPreamble(blk);
    exit();
  }

  protected void genCases(BitSet p) 
  {
    enter("genCases BitSet = "+p);
    super.genCases(p);
    exit();
  }

  public JavaBlockFinishingInfo genCommonBlock(AlternativeBlock blk, 
					       boolean noTestForSingle)
  {
    enter("genCommonBlock AltBlock = "+blk+" noTestForSingle = "+noTestForSingle);
    
    JavaBlockFinishingInfo res = super.genCommonBlock(blk,noTestForSingle);
    exit();
    return res;
  }

  protected void genHeader() 
  {
    enter("genHeader");
    super.genHeader();
    exit();
  }
  
  protected void genMatch(BitSet b) 
  {
    enter("genMatch BitSet = "+b);
    super.genMatch(b);
    exit();
  }
  
  protected void genMatch(GrammarAtom atom) 
  {
    enter("genMatch GrammarAtom = "+atom);
    super.genMatch(atom);
    exit();
  }
  
  protected void genMatchUsingAtomText(GrammarAtom atom) 
  {
    enter("genMatchUsingAtomText GrammarAtom = "+atom);
    super.genMatchUsingAtomText(atom);
    exit();
  }

  protected void genMatchUsingAtomTokenType(GrammarAtom atom) 
  {
    enter("genMatchUsingAtomTokenType GrammarAtom = "+atom);
    super.genMatchUsingAtomTokenType(atom);
    exit();
  }
  
  public void genNextToken() 
  {
    enter("genNextToken");
    super.genNextToken();
    exit();
  }

  public void genRule(RuleSymbol s, boolean startSymbol, int ruleNum) 
  {
    enter("genRule RuleSymbol = "+s.getId()+" startSymbol = "+startSymbol+
	  " ruleNum "+ruleNum);
    if (inLexerGrammar)
      {
	if (!firstLexerRuleEmitted)
	  {
	    println(" ");
	    println("  protected int tokColumn = 1;");
	    println("  protected int column = 1;");
	    println(" ");
	    println("  public void consume() throws IOException {");
	    println("    if ( inputState.guessing == 0 ) {");
	    println("      if (text.length()==0) {");
	    println("        tokColumn = column;");
	    println("      }");
	    println("      if (LA(1)=='\\n') { column = 1; }");
	    println("        else { column++; }");
	    println("    }");
	    println("    super.consume();");
	    println("  }");
	    println(" ");
	    println("  protected Token makeToken(int t) {");
	    println("    Token tok = super.makeToken(t);");
	    println("    tok.setColumn(tokColumn);");
	    println("    return tok;");
	    println("  }");
	    firstLexerRuleEmitted = true;
	  }
      }
    if (doOutput())
      {
	if (!stack.empty())
	  throw new RuntimeException("Internal Error");
	stack.push(new TraceNode(TraceNode.RULE_DEF,s.getId()));
	if (!firstParserRuleEmitted)
	  {
	    println(" ");
	    println("  public antlr.InteractiveParser interactiveParser;");
	    println(" ");
	    println("  void throwNoViableAlt(Token token)");
	    println("     throws NoViableAltException");
	    println("  {");
	    println("    if (interactiveParser != null)");
	    println("      interactiveParser.throwNoViableAlt(token);");
	    println("    throw new NoViableAltException(token);");
	    println("  }");
	    println(" ");
	    firstParserRuleEmitted = true;
	  }
	System.out.println("genRule RuleSymbol = "+s.getId()+" startSymbol = "+startSymbol+
			   " ruleNum "+ruleNum);
	System.out.print("parser rule "+s.getId()+":=");
      }
    super.genRule(s,startSymbol,ruleNum);
    if (doOutput())
      {
	System.out.println("\n");
	Object node = stack.pop();
	System.out.println("\n"+node+"\n");
	ruleNodes.appendElement(node);
      }
    exit();
  }

  protected void genSemPred(String pred, int line)
  {
    enter("genSemPred pred = "+pred+" on line "+line);
    super.genSemPred(pred,line);
    exit();
  }

  protected void genSemPredMap()
  {
    super.genSemPredMap();
  }

  protected void genSynPred(SynPredBlock blk, String lookaheadExpr) 
  {
    enter("genSynPred SynPredBlock = "+blk+" lookaheadExpr = "+lookaheadExpr);
    boolean wasInSynPred = inSynPred;
    inSynPred = true;
    super.genSynPred(blk,lookaheadExpr);
    inSynPred = wasInSynPred;
    exit();
  }

  public void genTokenStrings() 
  {
    enter("genTokenString");
    super.genTokenStrings();
    exit();
  }
  
  protected void genTokenTypes(TokenManager tm) throws IOException 
  {
    enter("genTokenTypes tm = "+tm);
    super.genTokenTypes(tm);
    exit();
  }

  public String getASTCreateString(Vector v) 
  {
    enter("getASTCreateString Vector = "+v);
    String res = super.getASTCreateString(v);
    exit();
    return res;
  }

  public String getASTCreateString(String str) 
  {
    enter("getASTCreateString String = "+str);
    String res = super.getASTCreateString(str);
    exit();
    return res;
  }

  protected String getLookaheadTestExpression(Alternative alt, int maxDepth) 
  {
    enter("getLookaheadTestExpression Alternative = "+alt+" maxDepth = "+maxDepth);
    String res = super.getLookaheadTestExpression(alt,maxDepth);
    exit();
    return res;
  }

  protected String getLookaheadTestTerm(int k, BitSet p) 
  {
    enter("getLookaheadTestTerm k = "+k+" BitSet = "+p);
    String res = super.getLookaheadTestTerm(k,p);
    exit();
    return res;
  }

  public String getRangeExpression(int k, int[] elems) 
  {
    enter("getRangeExpression k = "+k);
    String res = super.getRangeExpression(k,elems);
    exit();
    return res;
  }
  
  protected boolean lookaheadIsEmpty(Alternative alt, int maxDepth) 
  {
    enter("lookaheadIsEmpty Alternative = "+alt+" maxDepth = "+maxDepth);
    boolean res = super.lookaheadIsEmpty(alt,maxDepth);
    exit();
    return res;
  }

  public String mapTreeId(String idParam,  ActionTransInfo transInfo)
  {
    enter("mapTreeId idParam = "+idParam+" actionTransInfo "+transInfo);
    String res = super.mapTreeId(idParam,transInfo);
    exit();
    return res;
  }

  void enter(String s)
  {
    if (goryDetails)
      {
	for (int i=0; i<depth; i++)
	  System.out.print(" ");
	System.out.println(s);
      }
    depth += 2;
  }


  void exit()
  {
    depth -= 2;
  }
}
