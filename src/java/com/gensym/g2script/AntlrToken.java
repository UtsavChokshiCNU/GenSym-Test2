package com.gensym.g2script;

import antlr.*;
import com.gensym.types.G2Token;

public class AntlrToken extends CommonToken
{
  G2Token g2Token = null;

  public AntlrToken(G2Token token)
  {
    g2Token = token;
    setLine(token.getLineNumber());
    // Thread.dumpStack();
    switch (token.getType())
      {
      case G2Token.LEFT_PAREN:
	setType(G2ScriptTokenTypes.LPAREN);
	break;
      case G2Token.RIGHT_PAREN:
	setType(G2ScriptTokenTypes.RPAREN);
	break;
      case G2Token.COMMA:
	setType(G2ScriptTokenTypes.COMMA);
	break;
      case G2Token.SEMICOLON:
	setType(G2ScriptTokenTypes.SEMICOLON);
	break;
      case G2Token.COLON:
	setType(G2ScriptTokenTypes.COLON);
	break;
      case G2Token.PLUS:
	setType(G2ScriptTokenTypes.PLUS);
	break;
      case G2Token.TIMES:
	setType(G2ScriptTokenTypes.TIMES);
	break;
      case G2Token.EQUALS:
	setType(G2ScriptTokenTypes.EQUALS);
	break;
      case G2Token.DASH:
	setType(G2ScriptTokenTypes.MINUS);
	break;
      case G2Token.SLASH:
	setType(G2ScriptTokenTypes.SLASH);
	break;
      case G2Token.LEFT_BRACKET:
	setType(G2ScriptTokenTypes.LBRACK);
	break;
      case G2Token.RIGHT_BRACKET:
	setType(G2ScriptTokenTypes.RBRACK);
	break;
      case G2Token.GREATER:
	setType(G2ScriptTokenTypes.GREATER);
	break;
      case G2Token.LESS:
	setType(G2ScriptTokenTypes.LESS);
	break;
      case G2Token.NOT_EQUAL:
	setType(G2ScriptTokenTypes.NOT_EQUAL);
	break;
      case G2Token.GREATER_EQUAL:
	setType(G2ScriptTokenTypes.GREATER_EQUAL);
	break;
      case G2Token.LESS_EQUAL:
	setType(G2ScriptTokenTypes.LESS_EQUAL);
	break;
      case G2Token.INTEGER:
	setType(G2ScriptTokenTypes.INTEGER_LITERAL);
	break;
      case G2Token.FLOAT:
	setType(G2ScriptTokenTypes.FLOAT_LITERAL);
	break;
      case G2Token.WHOLE_STRING:
	setType(G2ScriptTokenTypes.WHOLE_STRING_LITERAL);
	break;
      case G2Token.LEFT_STRING:
	setType(G2ScriptTokenTypes.LEFT_STRING_LITERAL);
	break;
      case G2Token.MIDDLE_STRING:
	setType(G2ScriptTokenTypes.MIDDLE_STRING_LITERAL);
	break;
      case G2Token.RIGHT_STRING:
	setType(G2ScriptTokenTypes.RIGHT_STRING_LITERAL);
	break;
      case G2Token.PERIOD:
	setType(G2ScriptTokenTypes.PERIOD);
	break;
      case G2Token.SYMBOL:
	String string = ((com.gensym.util.Symbol)token.getValue()).toString();
	
	int code = ReservedSymbolManager.getTokenTypeIfAny(string);
	if (false)
	  System.out.println("code of "+string+" = "+code+
			     " line number "+token.getLineNumber());
	if (code != -1)
	  setType(code);
	else
	  setType(G2ScriptTokenTypes.UNRESERVED);
	break;
      case G2Token.BOOLEAN:
	setType(G2ScriptTokenTypes.TRUTH_VALUE_LITERAL);
	break;
	  default:
      }
  }

  public AntlrToken(int type, String string)
  {
    super(type,string);
  }

  public String getText()
  {
    if (g2Token != null)
      {
	return g2Token.toParseableString();
      }
    else
      return super.getText();
  }
}
