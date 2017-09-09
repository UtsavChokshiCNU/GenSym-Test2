package com.gensym.types;

import com.gensym.util.Symbol;
import java.io.*;
import java.util.Arrays;

public class G2Token
{
  int type;
  int typeCode;
  Object value = null;
  boolean isLast = false;
  int lineNumber = -1; // -1 means unknown

  public static final int LEFT_PAREN = 100;
  public static final int RIGHT_PAREN = 101;
  public static final int COMMA = 102;
  public static final int SEMICOLON = 103;
  public static final int COLON = 104;
  public static final int PLUS = 105;
  public static final int TIMES  = 106;
  public static final int EQUALS = 107;
  public static final int DASH = 108;
  public static final int SLASH = 109;
  public static final int LEFT_BRACKET = 110;
  public static final int RIGHT_BRACKET = 111;
  public static final int GREATER = 112;
  public static final int LESS = 113;
  public static final int NOT_EQUAL = 114;
  public static final int GREATER_EQUAL = 115;
  public static final int LESS_EQUAL = 116;
  public static final int PERIOD = 117;

  public static final int INTEGER = 201;
  public static final int FLOAT = 202;
  public static final int WHOLE_STRING = 203;
  public static final int SYMBOL = 204;
  public static final int BOOLEAN = 205;
  public static final int LEFT_STRING = 206;
  public static final int MIDDLE_STRING = 207;
  public static final int RIGHT_STRING = 208;

  private static final int INITIAL_STATE = 0;
  private static final int INT_OR_LEFT_FLOAT_STATE = 1;
  private static final int FLOAT_DOT_STATE = 2;
  private static final int FLOAT_RIGHT_STATE = 3;
  private static final int SYMBOL_ESCAPE_STATE = 4;
  private static final int SYMBOL_STATE = 5;

  private static String[] stateStrings = { "Initial", "Int|LeftFloat",
					   "FloatDot", "FloatRight",
					   "SymbolEscapeState", "Symbol" };

  public G2Token(int type, Object value)
  {
    this.type = type;
    this.value = value;
  }

  public G2Token(int type)
  {
    this.type = type;
  }

  public int getType()
  {
    return type;
  }

  public Object getValue()
  {
    return value;
  }

  public boolean isLast()
  {
    return isLast;
  }

  public int getLineNumber()
  {
    return lineNumber;
  }

  public static G2Token readToken(Reader reader)
       throws IOException, G2TokenizerException
  {
    skipWhitespace(reader);
    char ch = peekChar(reader);
    G2Token token = null;
    int lineNumber = (reader instanceof G2TokenReader ?
		      ((G2TokenReader)reader).getLineNumber() :
		      -1);

    if (Character.isLetter(ch) || 
	Character.isDigit(ch) ||
	Arrays.asList('@', '-', '_', '.', '\'').contains(ch))
      token = readSymbolBooleanOrNumber(reader);
    else if (ch == '"')
      token = readString(reader,true);
    else if (isTerminating(ch))
      {
	readChar(reader);
	if (ch == '+')
	  token = new G2Token(PLUS);
	else if (ch == '*')
	  token = new G2Token(TIMES);
	else if (ch == '=')
	  token = new G2Token(EQUALS);
	else if (ch == '(')
	  token = new G2Token(LEFT_PAREN);
	else if (ch == ')')
	  token = new G2Token(RIGHT_PAREN);
	else if (ch == ',')
	  token = new G2Token(COMMA);
	else if (ch == ';')
	  token = new G2Token(SEMICOLON);
	else if (ch == '.')
	  token = new G2Token(PERIOD);
	else if (ch == ':')
	  token = new G2Token(COLON);
	else if (ch == '[')
	  {
	    if (reader instanceof G2TokenReader)
	      ((G2TokenReader)reader).pushOpenBracket(false);
	    token = new G2Token(LEFT_BRACKET);
	  }
	else if (ch == ']')
	  {
		token = new G2Token(RIGHT_BRACKET);
	    if (reader instanceof G2TokenReader)
	      {
		
		G2TokenReader g2Reader = (G2TokenReader)reader;
		if (false)
		  System.out.println("right brack parse: open?"+
				     g2Reader.openBracketExists()+
				     " partial? "+
				     g2Reader.openBracketIsForPartialString());
		
		if (g2Reader.openBracketExists() && g2Reader.popOpenBracket())
		  token = readString(reader,false);

	    }
	}
	else if ((ch == '/') || (ch == '<') || (ch == '>'))
	  token = readCompoundPunctuation(reader,ch);
	
	else
	  throw new RuntimeException("g2 token input error with ch = "+ch);
      }
    else
      throw new RuntimeException("g2 token input error with ch = "+ch);
    token.lineNumber = lineNumber;
    return token;
  }

  private static G2Token readCompoundPunctuation(Reader reader, char ch)
       throws IOException
  {
    char ch2 = peekChar(reader);
    if (ch2 == '=')
      {
	readChar(reader);
	if (ch == '/')
	  return new G2Token(NOT_EQUAL);
	else if (ch == '<')
	  return new G2Token(LESS_EQUAL);
	else if (ch == '>')
	  return new G2Token(GREATER_EQUAL);
	else 
	  throw new RuntimeException("Illegal state in tokenizer");
      }
    else if (ch == '/')
      return new G2Token(SLASH);
    else if (ch == '<')
      return new G2Token(LESS);
    else if (ch == '>')
      return new G2Token(GREATER);
    else throw new RuntimeException("Illegal state in tokenizer");
  }

  private static boolean isTerminating(char ch)
  {
    return Arrays.asList('(', ')', '*', '+', ':', ';', ',', '"', '=', '[', ']', '/', '>', '<').contains(ch);
  }

  public static String makeParseableSymbolName(Symbol symbol)
  {
    return  makeParseableSymbolName(symbol.toString());
  }

  public static String makeParseableSymbolName(String string)
  {
    StringBuffer buffer = new StringBuffer();
    char[] chars = string.toCharArray();
    int i, len = chars.length;
    for (i=0; i<len; i++)
      {
        char ch = chars[i];
	if (isTerminating(ch) || 
	    Character.isWhitespace(ch) ||
	    Character.isLowerCase(ch))
	  buffer.append("@"+ch);
	else
	  buffer.append(ch);
      }
    return buffer.toString();
  }

  private static G2Token readSymbolBooleanOrNumber(Reader reader)
       throws IOException, G2TokenizerException
  {
    StringBuffer buffer = new StringBuffer();
    int floatDotPosition = -1;
    int floatExponentPosition = -1;
    int state = INITIAL_STATE;
    int position = -1;
    char ch;
    boolean last = false;
    G2Token token = null;
    
    while (true)
      {
	try {
	  ch = peekChar(reader);
	} catch (EOFException e)
	  {
	    last = true;
	    break;
	  }

	if (false)
	  System.out.println("RSBN state="+stateStrings[state]+
			     " ch="+ch);
			   
	if (state != SYMBOL_ESCAPE_STATE &&  // escape can be followed by ANYTHING 
	    (isTerminating(ch) || Character.isWhitespace(ch)))
	  break;
	  
	readChar(reader);
	position++;
	if (state != SYMBOL_ESCAPE_STATE)
	  ch = Character.toUpperCase(ch);
	switch (state) 
	  {
	  case INITIAL_STATE:
	    if (Character.isDigit(ch) || ch == '-')
	      state = INT_OR_LEFT_FLOAT_STATE;
	    else if (ch == '.')
	      {
		state = FLOAT_DOT_STATE;
		floatDotPosition = position;
	      }
	    else if (ch == '@')
	      state = SYMBOL_ESCAPE_STATE;
	    else
	      state = SYMBOL_STATE;
	    break;
	  case INT_OR_LEFT_FLOAT_STATE:
	    if (Character.isDigit(ch))
	      state = INT_OR_LEFT_FLOAT_STATE;
	    else if (ch == '.')
	      state = FLOAT_DOT_STATE;
	    else if (ch == '@')
	      state = SYMBOL_ESCAPE_STATE;
	    else
	      state = SYMBOL_STATE;
	    break;
	  case FLOAT_DOT_STATE:
	    if (Character.isDigit(ch))
	      state = FLOAT_RIGHT_STATE;
	    else if (ch == '@')
	      state = SYMBOL_ESCAPE_STATE;
	    else
	      state = SYMBOL_STATE;
	    break;
	  case FLOAT_RIGHT_STATE:
	    if (ch == '@')
	      state = SYMBOL_ESCAPE_STATE;
	    else if (!Character.isDigit(ch))
	      state = SYMBOL_STATE;
	    break;
	  case SYMBOL_ESCAPE_STATE:
	    state = SYMBOL_STATE;
	    break;
	  case SYMBOL_STATE:
	    // can't get any more general than SYMBOL
	    if (ch == '@')
	      state = SYMBOL_ESCAPE_STATE;
	    break;
	  default:
	  }
	if (state != SYMBOL_ESCAPE_STATE)
	  buffer.append(ch);
      }

    String string = buffer.toString();
    if (state == SYMBOL_ESCAPE_STATE)
      throw new G2TokenizerException("Unfinished escape sequence");
    else if (state == INT_OR_LEFT_FLOAT_STATE)
      try 
      {
	if (string.equals("-"))
	  token = new G2Token(DASH);
	else
	  {
	    Integer result = Integer.valueOf(string);
	    token = new G2Token(INTEGER,result);
	  }
      } catch (NumberFormatException e)
	{
	  throw new G2TokenizerException("Bad Integer: "+string);
	}
    else if (state == FLOAT_DOT_STATE ||
	     state == FLOAT_RIGHT_STATE)
      try 
      {
	Double result = Double.valueOf(string);
	token = new G2Token(FLOAT,result);
      } catch (NumberFormatException e)
	{
	  throw new G2TokenizerException("Bad Float: "+string);
	}
    else if (state == SYMBOL_STATE)
      {
	if (string.equals("FALSE"))
	  token = new G2Token(BOOLEAN, Boolean.FALSE);
	else if (string.equals("TRUE"))
	  token = new G2Token(BOOLEAN, Boolean.TRUE);
	else if (string.equals("-"))
	  token = new G2Token(DASH);
	else
	  token =  new G2Token(SYMBOL,Symbol.intern(string));
      }
    else 
      throw new G2TokenizerException("Bad Token: "+string);
    if (last)
      token.isLast = true;
    return token;
    
  }

  private static G2Token readString(Reader reader, boolean isLeftOrWhole)
       throws IOException
  {
    StringBuffer buffer = new StringBuffer();
    char ch;
    if (isLeftOrWhole)
      readChar(reader);
    boolean allowLeftString = (reader instanceof G2TokenReader);
    
    while (true)
      {
	ch = readChar(reader);
	if (ch == '"')
	  return new G2Token((isLeftOrWhole ? WHOLE_STRING : RIGHT_STRING),
			     buffer.toString());
	else if (allowLeftString && (ch == '['))
	  {
	    ((G2TokenReader)reader).pushOpenBracket(true);
	    return new G2Token((isLeftOrWhole ? LEFT_STRING : MIDDLE_STRING),
			       buffer.toString());
	  }
	else
	  buffer.append(ch);
      }
  }

  public static boolean hasMoreTokens(Reader reader)
       throws IOException
  {
    try {
      return skipWhitespace(reader);
    } catch (EOFException e)
      {
	return false;
      } 
  }

  private static boolean skipWhitespace(Reader reader)
       throws IOException
  {
    boolean inComment = false;
    while (true)
      {
	char ch = peekChar(reader);
	if (inComment && ch == '}')
	  inComment = false;
	else if (ch == '{')
	  inComment = true;
	else if (!inComment &&
		 !Character.isWhitespace(ch))
	  return true;
	readChar(reader);
      }
  }

  private static char readChar(Reader reader)
       throws IOException
  {
    if (reader instanceof G2TokenReader)
      return ((G2TokenReader)reader).readChar();
    else
      {
	int ch = reader.read();
	if (ch == -1)
	  {
	    throw new EOFException();
	  }
	else
	  return (char) ch;
      }
  }

  private static char peekChar(Reader reader)
       throws IOException
  {
    if (reader instanceof G2TokenReader)
      return ((G2TokenReader)reader).peekChar();
    else
      {
	reader.mark(1);
	int ch = reader.read();
	reader.reset();
	if (ch == -1)
	  {
	    throw new EOFException();
	  }
	else
	  return (char) ch;
      }
  }


  @Override
  public String toString()
  {
    String typeString = "";
    String tail = "";
    switch (type)
      {
      case LEFT_PAREN: 
    	  typeString = "LEFT_PAREN"; 
    	  break;
      case RIGHT_PAREN: 
    	  typeString = "RIGHT_PAREN"; 
    	  break;
      case COMMA: 
    	  typeString = "COMMA"; 
    	  break;
      case SEMICOLON: 
    	  typeString = "SEMICOLON"; 
    	  break;
      case COLON: 
    	  typeString = "COLON"; 
    	  break;
      case PLUS: 
    	  typeString = "PLUS"; 
    	  break;
      case TIMES: 
    	  typeString = "TIMES"; 
    	  break;
      case EQUALS: 
    	  typeString = "EQUALS"; 
    	  break;
      case DASH: 
    	  typeString = "DASH"; 
    	  break;
      case SLASH: 
    	  typeString = "SLASH"; 
    	  break;
      case LEFT_BRACKET: 
    	  typeString = "LEFT_BRACKET"; 
    	  break;
      case RIGHT_BRACKET: 
    	  typeString = "RIGHT_BRACKET"; 
    	  break;
      case GREATER: 
    	  typeString = "GREATER"; 
    	  break;
      case LESS: 
    	  typeString = "LESS"; 
    	  break;
      case NOT_EQUAL: 
    	  typeString = "NOT_EQUAL"; 
    	  break;
      case GREATER_EQUAL: 
    	  typeString = "GREATER_EQUAL"; 
    	  break;
      case LESS_EQUAL: 
    	  typeString = "LESS_EQUAL"; 
    	  break;
      case SYMBOL: 
    	  typeString = "SYMBOL"; 
    	  break;
      case INTEGER: 
    	  typeString = "INTEGER"; 
    	  break;
      case FLOAT: 
    	  typeString = "FLOAT"; 
    	  break;
      case BOOLEAN: 
    	  typeString = "BOOLEAN"; 
    	  break;
      case WHOLE_STRING: 
    	  typeString = "WHOLE_STRING"; 
    	  break;
      case LEFT_STRING: 
    	  typeString = "LEFT_STRING"; 
    	  break;
      case MIDDLE_STRING: 
    	  typeString = "MIDDLE_STRING"; 
    	  break;
      case RIGHT_STRING: 
    	  typeString = "RIGHT_STRING"; 
    	  break;
      case PERIOD: 
    	  typeString = "PERIOD"; 
    	  break;
      default:
      }
    if (value != null)
      tail = ", value="+value.toString();
    return "<G2Token: type="+typeString+tail+">";
  }

  public String toParseableString()
  {
    switch (type)
      {
      case LEFT_PAREN: return "("; 
      case RIGHT_PAREN: return ")";
      case COMMA: return ",";
      case SEMICOLON: return ";";
      case COLON: return ":";
      case PLUS: return "+";
      case TIMES: return "*";
      case EQUALS: return "=";
      case DASH: return "-";
      case SLASH: return "/";
      case LEFT_BRACKET: return "[";
      case RIGHT_BRACKET: return "]";
      case GREATER: return ">";
      case LESS: return "<";
      case NOT_EQUAL: return "/=";
      case GREATER_EQUAL: return ">=";
      case LESS_EQUAL: return "<=";
      case PERIOD: return ".";
      default:
	return value.toString();

      }
  }

  public static void main(String[] args)
  {
    try {
      Reader reader = null;
      Object o;
  
      try {
	reader = new StringReader("44 -6.4 - true  -3 -aa(456, 6.7 \"qewr qwe\" 345iu)");
	while (true) 
	  {
	    G2Token token = G2Token.readToken(reader);
	    System.out.println("token = "+token);
	  }
      } catch (EOFException e)
	{
	  System.out.println("done");
	  reader.close();
	}
      try {
	reader = new StringReader("the symbol foo@ bar ui.chaos .biz.baz _jj_kk");
	while (true) 
	  {
	    G2Token token = G2Token.readToken(reader);
	    System.out.println("token = "+token);
	  }
      } catch (EOFException e)
	{
	  System.out.println("done");
	  reader.close();
	}
      try {
	reader 
	  = new G2TokenReader(new StringReader("\"Tom ate [d] donuts in [m] minutes\""));
	while (true) 
	  {
	    G2Token token = G2Token.readToken(reader);
	    System.out.println("token = "+token);
	  }
      } catch (EOFException e)
	{
	  System.out.println("done");
	  reader.close();
	}
    } 
    catch (Exception e)
      {
	e.printStackTrace();
      }
  }
}
