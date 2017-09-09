package com.gensym.types;

import java.io.Reader;
import java.io.StringReader;
import java.io.PrintWriter;
import java.io.Writer;
import java.nio.charset.Charset;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.EOFException;
import java.util.Arrays;
import java.util.Enumeration;

import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.UnexpectedException;

public class ValueType extends ItemOrValueType
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = -1367122651934581160L;

  private static final Symbol SEQUENCE_ = Symbol.intern("SEQUENCE");
  private static final Symbol STRUCTURE_ = Symbol.intern("STRUCTURE");
  private static final Symbol SYMBOL_ = Symbol.intern("SYMBOL");
  private static final Symbol THE_ = Symbol.intern("THE");

  public ValueType()
  {
    
  }

  @Override
  public boolean includes(Object o)
  {
	boolean basicDataType =  o instanceof String || o instanceof Integer 
                            || o instanceof Double || o instanceof Boolean; // is this ok for TRUTH-VALUE
    
	return (basicDataType || o instanceof Symbol  || o instanceof Sequence || o instanceof Structure);
  }

  public static Object parseValue(Reader reader)
       throws G2TokenizerException, G2ParserException, EOFException
  {
    return parseValue(reader,null);
  }

  static Object parseValue(Reader reader, G2Token inputToken)
       throws G2TokenizerException, G2ParserException, EOFException
  {
    try 
      {
	G2Token token;
	if (inputToken == null)
	  token = G2Token.readToken(reader);
	else
	  token = inputToken;
	if (token.type == G2Token.SYMBOL &&
	    ( token.value.equals(SEQUENCE_) ||
	      token.value.equals(STRUCTURE_)))
	  {
	    if (token.value.equals(SEQUENCE_))
	      return parseSequenceTail(reader);
	    else 
	      return parseStructureTail(reader);
	  }
	else if (Arrays.asList(G2Token.INTEGER, G2Token.FLOAT, G2Token.SYMBOL, 
	                G2Token.WHOLE_STRING, G2Token.BOOLEAN).contains(token.type))
	  return token.value;
	else throw new G2ParserException("Bad Constant");
      } 
    catch (EOFException eof)
      {
	throw eof;
      } 
    catch (IOException e) 
      {
	throw new UnexpectedException(e);
      }
  }

  private static Sequence parseSequenceTail(Reader reader)
       throws G2TokenizerException, G2ParserException, IOException
  {
    G2Token token = G2Token.readToken(reader);
    
    if (token.type != G2Token.LEFT_PAREN)
      throw new G2ParserException("Bad sequence");

    Sequence sequence = new Sequence();
    boolean expectingValue = true;
    boolean atBeginning = true;
    while (true)
      {
	G2Token eltToken = G2Token.readToken(reader);
	if (eltToken.type == G2Token.RIGHT_PAREN)
	  {
	   if (!atBeginning && expectingValue)
	      throw new G2ParserException("malformed sequence");
	   else
	    break; // seq > 1 ends
	  } 
	else if (expectingValue)
	  {
	    Object value = parseEmbeddedValue(reader,eltToken);
	    sequence.addElement(value);
	    expectingValue = false;
	  }
	else if (eltToken.type == G2Token.COMMA)
	  {
	    expectingValue = true;
	  }
	else
	  throw new G2ParserException("malformed sequence");
	atBeginning = false;
      }

    return sequence;
  }

  private static Object parseEmbeddedValue(Reader reader, G2Token token)
       throws G2TokenizerException, G2ParserException, IOException
  {
    if (token.type == G2Token.SYMBOL)
      {
	Symbol symbol = (Symbol) token.value;
	if (symbol.equals(THE_))
	  {
	    G2Token nextToken = G2Token.readToken(reader);
	    if (nextToken.type == G2Token.SYMBOL &&
		nextToken.value.equals(SYMBOL_))
	      {
		Object result = parseValue(reader,null);
		if (result instanceof Symbol)
		  return result;
		else
		  throw new G2ParserException("\"the symbol\" must be followed by a symbol");
	      }
	    else
	      throw new G2ParserException("Bad Quantifier");
	  }
	else if (symbol.equals(SEQUENCE_) ||
		 symbol.equals(STRUCTURE_))
	  return parseValue(reader,token);
	else 
	  throw new G2ParserException("Cannot refer to Items");
      }
    else
      return parseValue(reader,token);
  }

  private static final int INITIAL_STATE = 0;
  private static final int NAME_STATE = 1;
  private static final int COLON_STATE = 2;
  private static final int VALUE_STATE = 3;
  private static final int COMMA_STATE = 4;

  private static Structure parseStructureTail(Reader reader)
       throws G2TokenizerException, G2ParserException, IOException
  {
    G2Token token;

    token = G2Token.readToken(reader);
    if (token.type != G2Token.LEFT_PAREN)
      throw new G2ParserException("Bad structure");

    int state = INITIAL_STATE;
    boolean done = false;
    Structure structure = new Structure();
    Symbol lastSymbol = null;
    while (true)
      {
	token = G2Token.readToken(reader);
	switch (state)
	  {
	  case INITIAL_STATE:
	    if (token.type == G2Token.RIGHT_PAREN)
	      done = true;
	    else if (token.type == G2Token.SYMBOL)
	      {
		lastSymbol = (Symbol) token.value;
		state = COLON_STATE;
	      }
	    else 
	      throw new G2ParserException("bad structure attribute name");
	    break;
	  case NAME_STATE:
	    if (token.type == G2Token.SYMBOL)
	      {
		lastSymbol = (Symbol) token.value;
		state = COLON_STATE;
	      }
	    else
	      throw new G2ParserException("bad structure attribute name");
	    break;
	  case COLON_STATE:
	    if (token.type == G2Token.COLON)
	      state = VALUE_STATE;
	    else
	      throw new G2ParserException("bad structure - missing colon");
	    break;
	  case VALUE_STATE:
	    Object value =  parseEmbeddedValue(reader,token);
	    structure.setAttributeValue(lastSymbol,value);
	    state = COMMA_STATE;
	    break;
	  case COMMA_STATE:
	    if (token.type == G2Token.COMMA)
	      state = NAME_STATE;
	    else if (token.type == G2Token.RIGHT_PAREN)
	      done = true;
	    break;
	  default:
	  }
	if (done)
	  break;
      }
    return structure;
  }

  @Override
  public void pprint(java.io.PrintWriter out, int indent)
  {
    if (this.getClass() == ValueType.class)
      out.print("Value");
    else
      out.print("No Specific ValueType Pprinter for "+this);
  }

  /**
   *  writeParseably writes a JavaLink version of a G2 value
   *  in the same fashion as G2.  If it contains embedded 
   *  items it will not actually be parseable.
   */
  public static void writeParseably(Object o, Writer writer)
       throws IOException
  {
    writeParseably(o,writer,true);
  }

  private static void writeParseably(Object o, Writer writer,
				     boolean topLevel)
       throws IOException
  {
    if (o instanceof Structure)
      {
	Structure structure = (Structure) o;
	Enumeration attributes = structure.getAttributeNames ();
	Enumeration values = structure.getAttributeValues ();	
	writer.write("structure(");
	while (attributes.hasMoreElements())
	  {
	    Symbol name = (Symbol)attributes.nextElement();
	    writer.write(name+": ");
	    Object value = values.nextElement();
	    writeParseably(value,writer,false);
	    if (attributes.hasMoreElements())
	      writer.write(", ");
	  }
	writer.write(")");
      }
    else if (o instanceof Sequence)
      {
	Sequence sequence = (Sequence) o;
	int i, len = sequence.size();
	writer.write("sequence(");
	for (i=0; i<len; i++)
	  {
	    writeParseably(sequence.elementAt(i),writer,false);
	    if (i < len - 1)
	      writer.write(", ");
	  }
	writer.write(")");
      }
    else if (o instanceof Symbol &&
	     !topLevel)
      writer.write("the symbol "+
		   G2Token.makeParseableSymbolName((Symbol)o));
    else if (o instanceof Symbol)
      writer.write(G2Token.makeParseableSymbolName((Symbol)o));
    else if (o instanceof String)
      writer.write("\""+o+"\"");
    else
      writer.write(o.toString());
  }

  public static void main(String[] args)
  {
    String[] testCases = { "1.224",
			   "false",
			   "SEQUENCE(1, true, the symbol bletch)",
			   "SEQUENCE(1, 2, the symbol",
			   "STRUCTURE(FOO: 3 , BAR : SEQUENCE(1, 2.4 , \"asdf\"))" };
    try {
      
      for (int i = 0 ; i<testCases.length ; i++)
	{
      StringReader reader = new StringReader(testCases[i]);
	  try {
	    Object value = parseValue(reader,null);
	    System.out.println("object parsed as "+value);
	    PrintWriter writer = new PrintWriter(new OutputStreamWriter(System.out, Charset.defaultCharset()));
	    writeParseably(value,writer);
	    writer.println("");
	    writer.flush();
	    

	  } catch (Exception e)
	    {
	      System.out.println("done");
	      e.printStackTrace();
	    }finally {
	      if(reader != null){
	    	reader.close();
	      }
	    }
	}
    } 
    catch (Exception e)
      {
	e.printStackTrace();
      }
  }
}
