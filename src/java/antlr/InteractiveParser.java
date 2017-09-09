package antlr;

import antlr.debug.*;
import java.io.*;
import java.util.*;
import java.lang.reflect.*;

public class InteractiveParser 
  implements ParserListener
// not InputBufferListener, NewLineListener, or SemanticPredicateListener yet
{
  TraceNode[] grammarRules;
  Stack stack = new Stack();
  Stack lastExceptionStack;
  Class lexerClass;
  Constructor lexerConstructor;
  Class parserClass;
  Constructor parserConstructor;
  Method topLevelGrammarRule;
  Field interactiveParserField;

  public InteractiveParser(String filename, 
			   Class  lexerClass,
			   Class  parserClass,
			   String topLevelRuleName)
  {
    this.lexerClass = lexerClass;
    this.parserClass = parserClass;
    this.topLevelGrammarRule = topLevelGrammarRule;
    try {
      lexerConstructor = lexerClass.getConstructor(new Class[] { Reader.class });
      parserConstructor = parserClass.getConstructor(new Class[] { TokenStream.class });
      topLevelGrammarRule = parserClass.getMethod(topLevelRuleName,new Class[0]);
      interactiveParserField = parserClass.getField("interactiveParser");
    } catch (Exception e)
      {
	e.printStackTrace();
	throw new IllegalArgumentException("bad Interactive parser args");
      }
    try {
      ObjectInputStream ois
	= new ObjectInputStream(new FileInputStream(filename));
      int version = ois.readInt();
      int count = ois.readInt();
      grammarRules = new TraceNode[count];
      for (int i=0; i<count; i++)
	grammarRules[i] = (TraceNode)ois.readObject();
      ois.close();
    } catch (ClassNotFoundException cnfe)
      {
	cnfe.printStackTrace();
	throw new RuntimeException("Trouble reading interactive parser data from "+filename);
      }
    catch (IOException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Trouble reading interactive parser data from "+filename);
      }
  }

  public InteractiveParserResult parse(Reader reader, boolean isStatement)
  {
    try {
      TokenStream tokenStream 
	= (TokenStream)lexerConstructor.newInstance(new Object[] { reader });
      if (tokenStream instanceof CharScanner)
	((CharScanner)tokenStream).setTokenObjectClass("antlr.InteractiveParserToken");
      Parser parser 
	= (Parser)parserConstructor.newInstance(new Object[] { tokenStream });
      parser.addTraceListener(this);
      parser.addMessageListener(this);
      interactiveParserField.set(parser,this);
      stack.removeAllElements();
      topLevelGrammarRule.invoke(parser,new Object[0]);
    } catch (InvocationTargetException ite)
      {
	Throwable targetException = ite.getTargetException();
	if (targetException instanceof IOException)
	  {
	    targetException.printStackTrace();
	    throw new RuntimeException("Internal IO Exception");
	  }
	else if (targetException instanceof NoViableAltException)
	  {
	    NoViableAltException nvae = (NoViableAltException)targetException;
	    Token token = nvae.token;
	    if (token.getText() == null)
	      {
		System.out.println("Good So Far");
		int i,len = lastExceptionStack.size();	
		TraceNode[] stackArray = new TraceNode[len];
		for (i=0; i<len; i++)
		  stackArray[i] = (TraceNode) lastExceptionStack.elementAt(i);
		return new InteractiveParserResult(true,
						   false, // hmm..
						   nvae.getLine(),
						   nvae.getColumn(),
						   null,
						   stackArray);
	      }
	    else
	      {
		// nvae.printStackTrace();
		return new InteractiveParserResult(false,
						   false,
						   nvae.getLine(),
						   nvae.getColumn(),
						   ""+nvae,
						   null);
	      }
	  }
	else if (targetException instanceof ParserException)
	  {
	    ParserException pe = (ParserException)targetException;
	    return new InteractiveParserResult(false,
					       false,
					       pe.getLine(),
					       pe.getColumn(),
					       ""+pe,
					       null);
	  }
      }
    catch (InstantiationException ie)
      {
	ie.printStackTrace();
	throw new RuntimeException("unable to make parser and/or lexer");
      }
    catch (IllegalAccessException iae)
      {
	iae.printStackTrace();
	throw new RuntimeException("unable to make parser and/or lexer due to protection");
      }
    return new InteractiveParserResult(true,true,0,0,null,null);
  }

  public void reportError(MessageEvent e)
  {
    System.out.println("msg event error now");
  }
  
  public void reportWarning(MessageEvent e)
  {
    System.out.println("msg event warning now");
  }

  public void parserMatch(ParserMatchEvent e)
  {

  }
  
  public void parserMatchNot(ParserMatchEvent e)
  {

  }
  
  public void parserMismatch(ParserMatchEvent e)
  {
  }
	
  public void parserMismatchNot(ParserMatchEvent e)
  {
    
  }

  public void parserConsume(ParserTokenEvent e)
  {

  }
	
  public void parserLA(ParserTokenEvent e)
  {

  }

  public void syntacticPredicateFailed(SyntacticPredicateEvent e)
  {

  }
  
  public void syntacticPredicateStarted(SyntacticPredicateEvent e)
  {

  }
  
  public void syntacticPredicateSucceeded(SyntacticPredicateEvent e)
  {

  }

  public void enterRule(TraceEvent e)
  {
    //System.out.println("enter "+grammarRules[e.getRuleNum()]);
    stack.push(grammarRules[e.getRuleNum()]);
  }

  public void exitRule(TraceEvent e)
  {
    //System.out.println("exit  "+grammarRules[e.getRuleNum()]);
    stack.pop();
  }

  public void throwNoViableAlt(Token token)
  {
    //System.out.println("error soon");
    lastExceptionStack = (Stack)stack.clone();
  }

  public void doneParsing(TraceEvent e)
  {
    // System.out.println("D O N E P A R S I N G");
  }
  
  public void refresh()
  {

  }

  public void semanticPredicateEvaluated(SemanticPredicateEvent e)
  {

  }

 
}
