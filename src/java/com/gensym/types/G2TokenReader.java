package com.gensym.types;

import com.gensym.util.Symbol;
import java.io.*;
import java.util.Stack;

public class G2TokenReader extends Reader
{
  private Reader reader;
  private int lineNumber = 1;
  private Stack bracketStack = new Stack();

  public G2TokenReader(Reader reader)
  {
    this.reader = reader;
  }

  @Override
  public int read(char[] buffer, int offset, int length)
       throws IOException
  {
    throw new RuntimeException("G2TokenReader supports only readChar and peekChar");
  }

  int getLineNumber()
  {
    return lineNumber;
  }

  char readChar()
       throws IOException
  {
    int ch = reader.read();
    if (ch == -1)
      {
	throw new EOFException();
      }
    else
      {
	if (ch == '\n')
	  lineNumber++;
	return (char) ch;
      }
  }

  char peekChar()
       throws IOException
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

  void pushOpenBracket(boolean isLeftString)
  {
    bracketStack.push(new Boolean(isLeftString));
  }

  boolean popOpenBracket()
  {
    return ((Boolean)bracketStack.pop()).booleanValue();
  }

  boolean openBracketExists()
  {
    return !bracketStack.empty();
  }
  
  boolean openBracketIsForPartialString()
  {
    return ((Boolean)bracketStack.peek()).booleanValue();
  }

  @Override
  public void close()
       throws IOException
  {
    reader.close();
  }

}
