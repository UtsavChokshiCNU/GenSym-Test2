package com.gensym.util;

import com.gensym.util.Symbol;
import java.io.*;

public class Cons
{
  public Object car;
  public Object cdr;

  public Cons (Object car, Object cdr)
  {
    this.car = car;
    this.cdr = cdr;
  }
  
  public boolean isProperList()
  {
    Cons tail = this;
    while (tail != null)
      if (tail.cdr instanceof Cons)
	tail = (Cons) tail.cdr;
      else if (tail.cdr == null)
	return true;
      else
	return false;
    return true;
  }

  public int properListLength()
  {
    Cons tail = this;
    int length = 1;
    while (tail != null)
      if (tail.cdr instanceof Cons)
	{
	  tail = (Cons) tail.cdr;
	  length++;
	}
      else if (tail.cdr == null)
	tail = null;
      else
	throw new RuntimeException("not a proper list "+this);
    return length;
  }

  public Cons tail()
  {
    if (cdr instanceof Cons)
      return (Cons)cdr;
    else if (cdr == null)
      return null;
    else
      throw new RuntimeException("not a proper list"+this);
  }

  public Object second()
  {
    Cons tail = tail();
    return tail.car;
  }

  public Object third()
  {
    Cons tail = tail().tail();
    return tail.car;
  }

  @Override
  public String toString()
  {
    StringBuffer buffer = new StringBuffer();
    printRec(buffer,false);
    return buffer.toString();
  }

  private void printRec(StringBuffer buffer, boolean isCdr)
  {
    if (!isCdr)
      buffer.append("(");
    
    if (car instanceof Cons)
      ((Cons)car).printRec(buffer,false);
    else if (car instanceof String)
      { 
	buffer.append('"');
	buffer.append(car.toString());
	buffer.append('"');
      }
    else
      buffer.append(car.toString());
    if (cdr == null)
      buffer.append(")");
    else if (cdr instanceof Cons)
      {
	buffer.append(" ");
	((Cons)cdr).printRec(buffer,true);
      }
    else
      {
	buffer.append(" . ");
	buffer.append(cdr.toString());
	buffer.append(")");
      }
  }

  public static Object read(Reader reader)
       throws IOException, EOFException
  {
    skipWhitespace(reader);
    char ch = peekChar(reader);

    if (Character.isLetter(ch) || 
	ch == '*' ||
	ch == '-' ||
	ch == '+')
      return readSymbolOrBoolean(reader);
    else if (Character.isDigit(ch))
      return readInteger(reader);
    else if (ch == '(')
      {
	readChar(reader);
	return readList(reader);
      }
    else if (ch == '"')
      {
	readChar(reader);
	return readString(reader);
      }
    else
      throw new RuntimeException("list input error");
  }
  
  private static Object readSymbolOrBoolean(Reader reader)
       throws IOException
  {
    StringBuffer buffer = new StringBuffer();
    char ch;
    
    while (true)
      {
	ch = peekChar(reader);
	if (Character.isLetter(ch) ||
	    ch == '*' ||
	    ch == '-' ||
	    ch == '+')
	  {
	    buffer.append(ch);
	    readChar(reader);
	  }
	else
	  {
	    String symbolName = buffer.toString();
	    if (symbolName.equals("true"))
	      return new Boolean(true);
	    else if (symbolName.equals("false"))
	      return new Boolean(false);
	    else
	      return Symbol.intern(buffer.toString());
	  }
      }
  }
  private static String readString(Reader reader)
       throws IOException
  {
    StringBuffer buffer = new StringBuffer();
    char ch;
    
    while (true)
      {
	ch = readChar(reader);
	if (ch != '"')
	  buffer.append(ch);
	else
	  {
	    return buffer.toString();
	  }
      }
  }

  private static Cons readList(Reader reader)
       throws IOException
  {
    Object car = read(reader);
    skipWhitespace(reader);

    char ch = peekChar(reader);
    if (ch == '.')
      {
	readChar(reader);
	Cons result = new Cons(car, read(reader));
	skipWhitespace(reader);
	ch = readChar(reader);
	if (ch != ')')
	  throw new IOException("Malformed dotted list");
	else
	  return result;
      }
    else if (ch == ')')
      {
	readChar(reader);
	return new Cons(car, null);
      }
    else 
      return new Cons(car , readList(reader));
  }

  private static Integer readInteger(Reader reader)
       throws IOException
  {
    StringBuffer buffer = new StringBuffer();
    char ch;

    while (true)
      {
	ch = peekChar(reader);
	if (Character.isDigit(ch))
	  {
	    buffer.append(ch);
	    readChar(reader);
	  }
	else
	  try
	  {
	    return Integer.parseInt(buffer.toString());
	  } catch (NumberFormatException e)
	    {
	      throw new IOException("Bad Integer");
	    }
      }
  }

  private static void skipWhitespace(Reader reader)
       throws IOException
  {
    while (Character.isWhitespace(peekChar(reader)))
      readChar(reader);
  }

  private static char readChar(Reader reader)
       throws IOException
  {
    int ch = reader.read();
    if (ch == -1)
      throw new EOFException();
    else
      return (char) ch;
  }

  private static char peekChar(Reader reader)
       throws IOException
  {
    reader.mark(1);
    int ch = reader.read();
    reader.reset();
    if (ch == -1)
      throw new EOFException();
    else

      return (char) ch;
  }

  public static void main(String[] args)
  {
    try {
      StringReader reader;
      Object o;

      reader = new StringReader("(A B C)");
      o = read(reader);
      System.out.println("read "+o);
      reader.close();

      reader = new StringReader("(A B . C)");
      o = read(reader);
      System.out.println("read "+o);
      reader.close();

      reader = new StringReader("(A B . (C D))");
      o = read(reader);
      System.out.println("read "+o);
      reader.close();
      
      reader = new StringReader("(AA BB-WOW 1 2)");
      o = read(reader);
      System.out.println("read "+o);
      reader.close();
      
      reader = new StringReader("(A (1 2) B)");
      o = read(reader);
      System.out.println("read "+o);
      reader.close();
      
      reader = new StringReader("(A (true 2) false (C))");
      o = read(reader);
      System.out.println("read "+o);
      reader.close();
      
      reader = new StringReader("(\"foo.bar.Crumbs\" ASD-1 QWE-2)");
      o = read(reader);
      System.out.println("read "+o);
      reader.close();
      
    } catch (IOException e) {
    	e.printStackTrace();
    } catch (RuntimeException e) {
    	e.printStackTrace();
    }
  }
}
