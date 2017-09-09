package com.gensym.cbu.experimental.mibbrowser;

import java.io.*;
import java.util.*;

public class MibFileReader extends BufferedReader
{
  static int READ_AHEAD_LIMIT = 10000;
  static String[] doubleQuotes = {"\""};
  static String[] curlyBraces = {"{", "}"};


  public MibFileReader(Reader in)
    {
      super(in);
    }

  public MibFileReader(Reader in, int sz) throws IllegalArgumentException
    {
      super( in, sz);
    }
  
  public String readToFirst(String[] keywords, boolean inclusive)
    throws IOException, KeywordNotFoundException
    {
      FoundKeyword fk = findFirstOccurrence(keywords);
      int charsRead;
      
      char[] goodChars;
      if (inclusive == true) {
	goodChars = new char[fk.position + fk.keyword.length()];
	charsRead = read(goodChars, 0, fk.position + fk.keyword.length());
      }
      else {
	goodChars = new char[fk.position];
	charsRead = read(goodChars, 0, fk.position);
      }
      String s = new String(goodChars);
      //System.out.println(s);
      return s;
    }

  public String readToTokenBeforeFirst(String[] keywords)
    throws IOException, KeywordNotFoundException, TokenNotFoundException
    {
      FoundKeyword fk = findFirstOccurrence(keywords);

      int charsToRead = getStartingPositionOfLastToken(fk.position);

      char[] chars = new char[charsToRead];
      int charsRead = read(chars, 0, charsToRead);

      return new String(chars);
    }

  public boolean keywordFound(String[] keywords) throws IOException
    {
      try {
	FoundKeyword keywordFound = findFirstOccurrence(keywords);
      } catch (KeywordNotFoundException knfe) {
	return false;
      }
      return true;
    }
      
  FoundKeyword findFirstOccurrence(String[] keywords)
    throws IOException, KeywordNotFoundException
    {
      mark(MibFileReader.READ_AHEAD_LIMIT);

      char[] chars = new char[MibFileReader.READ_AHEAD_LIMIT];
      int charsRead  = read(chars, 0, MibFileReader.READ_AHEAD_LIMIT);
      
      String text = new String(chars);
      
      int firstFound = Math.min(MibFileReader.READ_AHEAD_LIMIT, charsRead);
      int position;
      String keywordFound = new String();
      for (int i = 0; i < keywords.length; i++)
	{
	  position = text.indexOf(keywords[i]);
	  //System.out.println("the position of " + keywords[i] +
	  //	     " is " + position + "(" + firstFound + ")");
	  if (position >= 0 && position < firstFound)
	    {
	      firstFound = position;
	      keywordFound = keywords[i];
	    }
	}

      if (firstFound == Math.min(MibFileReader.READ_AHEAD_LIMIT, charsRead))
	{
	  String s = new String("(");
	  int i;
	  for ( i = 0; i < keywords.length - 1; i++)
	    s += keywords[i] + ",";
	  s += keywords[i] + ")";
	throw new KeywordNotFoundException("Keywords " + s +
					   " not found in : " + text);
	}
					   
      reset();

      return new FoundKeyword(firstFound, keywordFound);
    }

  int getStartingPositionOfLastToken(int charsToRead)
    throws IOException, TokenNotFoundException
    {
      mark(charsToRead);
      
      int charsRead;
      char[] chars = new char[charsToRead];
      charsRead = read(chars, 0, charsToRead);

      String s = new String(chars);

      StringTokenizer st = new StringTokenizer(s);
      String token;

      if (st.countTokens() == 0)
	throw new TokenNotFoundException("No Tokens found in " + s);
	  
      token = st.nextToken();
      while (st.hasMoreTokens())
	token = st.nextToken();
      

      //token is now the last token
      reset();
      
      return s.indexOf(token);
    }
  
  class FoundKeyword {
    public int position;
    public String keyword;

    public FoundKeyword(int i, String s)
      {
	position = i;
	keyword = s;
      }
  }
}
