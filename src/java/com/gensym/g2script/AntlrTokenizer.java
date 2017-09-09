package com.gensym.g2script;

import antlr.*;
import java.io.*;
import com.gensym.types.G2Token;
import com.gensym.types.G2TokenizerException;

public class AntlrTokenizer implements TokenStream
{
  Reader reader;
  boolean nextIsLast = false;

  public AntlrTokenizer(Reader reader)
  {
    this.reader = reader;
  }

  public Token nextToken()
       // throws IOException, G2TokenizerException
  {
    try 
      {
	if (nextIsLast)
	  return new AntlrToken (Token.EOF_TYPE, "");
	else
	  {
	    G2Token g2Token = G2Token.readToken(reader);
	    nextIsLast = g2Token.isLast();
	    return new AntlrToken(g2Token);
	  }
      }
    catch (EOFException eof)
      {
	System.out.println("read the EOF Token");
	return new AntlrToken (Token.EOF_TYPE, "");
      }
    catch (IOException e1)
      {
	System.out.println("IO Exception in Parsing");
	e1.printStackTrace(); 
	return null; 
      }
    catch (G2TokenizerException e2)
      {
	// Can't throw becuz antlr.Tokenizer interface doesn't do exceptions
	// throw e2;
	System.out.println("Tokenizer Exception in Parsing");
	e2.printStackTrace(); 
	return null;
      }
  }
       
}
