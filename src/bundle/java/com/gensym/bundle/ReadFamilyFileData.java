/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ReadFamilyFileData.java
 *
 * @author David McDonald
 * @version 0.1 initiated 6/29/00
 */

//package com.gensym.bundle;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.Reader;
import java.io.FileReader;
import java.io.StreamTokenizer;
import java.util.Vector;

/* This is a copy & (extensively) specializion of code I wrote for
 * parsing g2's grammar: <ddm>:playground/parser/ReadGrammar.java */

public class ReadFamilyFileData {

    static boolean debug = false;

    static final int OpenParen    = (int)'(';
    static final int CloseParen   = (int)')';
    static final int DoubleQuote  = (int)'"';
    static final int OpenBracket  = (int)'[';
    static final int CloseBracket = (int)']';
    static final int Newline      = (int)'\n';
 


    /* The serialized version of a Family Descriptor File (produced ad-hoc
     * by the C code that parses the original file has the following format.
     *
     *    It starts with the id number of the family (a number).
     *    Followed by the name of the family (a string), its version, and
     *    what platforms it's available on. 
     *
     *    Then we have any number of bundles. Each bundle is contained within
     *      a pair of parenthesis.
     *
     *    A bundle consists of its name (a string), followed by its version
     *     (another string), followed by any number of components, each contained
     *     within parenthesis.
     *
     *    A component consists of its name (a string), followed by its index
     *     (a number).
     */

  protected static void readFamily(String namestring, Families setOfFamilies)
  throws FileNotFoundException, IOException {
    File f = new File(namestring);
    FileReader r = new FileReader(f);
    StreamTokenizer t = new StreamTokenizer(r);
    t.quoteChar('"');
    try {
	 int tokenType;
	 for (;;) {
	     tokenType = t.nextToken();
	     if (debug) traceToken(tokenType, "readFamily", t);
	     switch (tokenType) {
	     case StreamTokenizer.TT_NUMBER:  /* the id */
		 Family family = new Family( String.valueOf(t.nval) );
		 parseFamily(t, family);
		 setOfFamilies.addFamily(family);
		 break;
	     case Newline:
		 break;
	     case StreamTokenizer.TT_EOF:
		 return;
	     case StreamTokenizer.TT_WORD:
	     case DoubleQuote:
	     case OpenParen:
	     case CloseParen:
	     default:
		 shouldNotGetHere(1, t);
	     }
	 }
    } finally {
      r.close();
    }
  }

    private static void parseFamily(StreamTokenizer t, Family family)
    throws IOException {
	/* After the family file index comes the name of the family. */
	String name = readName(t);
	family.setName(name);
	int tokenType;
	for (;;) {
	    tokenType = t.nextToken();
	    if (debug) traceToken(tokenType, "parseFamily", t);
	    switch (tokenType) {
	    case StreamTokenizer.TT_NUMBER:
	        family.setVersion((int)t.nval);
		break;
	    case OpenParen:
		readBundle(t, family);
		break;
	    case StreamTokenizer.TT_EOF:
		return;
	    default:
		shouldNotGetHere(2, t);
	    }
	}
    }

    private static void readBundle (StreamTokenizer t, Family family) 
    throws IOException {
	String name = readName(t);
	Bundle bundle = new Bundle(name);
	family.addBundle(bundle);
	String version = readName(t);
	bundle.setVersion( version );
	int id = (int)readNumber(t);
	bundle.setID(id);
	/* Then we should get a list of available platforms enclosed
	 * within square brackets (but we might not, since this stuff
	 * is not yet (8/25/00) automatically generated), followed by
	 * all the components. */
	boolean sawPlatforms = false;
	int tokenType;
	for (;;) {
	    tokenType = t.nextToken();
	    if (debug) traceToken(tokenType, "readBundle", t);
	    switch (tokenType) {
		//	    case OpenBracket:
		//		readPlatforms(t, bundle);
		//		break;
	    case OpenParen:
		if (sawPlatforms)
		    readComponent(t, bundle);
		else {
		    bundle.setPlatforms( readPlatforms(t) );
		    sawPlatforms = true;
		}
		break;
	    case CloseParen:
		return;
	    case StreamTokenizer.TT_EOF:
		shouldNotGetHere(3, t);
		break;
	    default:
		shouldNotGetHere(4, t);
	    }
	}
    }

    private static Vector readPlatforms (StreamTokenizer t) 
    throws IOException {
      Vector platforms = new Vector();
      int tokenType;
      for (;;) {
	tokenType = t.nextToken();
	if (debug) traceToken(tokenType, "readPlatforms", t);
	if (tokenType == StreamTokenizer.TT_WORD)
	  platforms.addElement( LicenseKey.platformNamed(t.sval) );
	else if (tokenType == CloseParen) //CloseBracket)
	  return platforms;
	else
	  shouldNotGetHere(8, t);
      }
    }

    private static void readComponent (StreamTokenizer t, Bundle bundle) 
    throws IOException {
      String name = readName(t);
      Component component = new Component(name);
      bundle.addComponent(component);
      // Read the index
      int index = (int)readNumber(t);
      component.setIndex(index);
      /* Three things can follow the index, fortunately for now they
       * are all implemented as data types that streamTokenizer
       * can distinguish. If we have to add more we'll need a different
       * scheme.
       * (a) If the component belongs to a bundle group we'll get
       *     a number telling us what group it is.
       * (b) If it is optional we'll see a word (i.e. 'optional')
       * (c) We'll always see a list of the platforms that it works on. */
      for (;;) {
	int tokenType = t.nextToken();
	if (debug) traceToken(tokenType, "readComponent", t);
	switch (tokenType) {
	case OpenParen:
	  component.setValidPlatforms( readPlatforms(t) );
	  break;
	case CloseParen:
	  return;
	case StreamTokenizer.TT_WORD:
	  component.setOptional( true );
	  break;
	case StreamTokenizer.TT_NUMBER:
          int v = (int)t.nval;
	  if ((v < component.min_button_group) || (v > component.max_button_group))
	    System.out.println("*** WARNING *** Radio button group index "
			       + v + " is out of range ["
			       + component.min_button_group
			       + ".." + component.max_button_group
			       + "] (line #" + t.lineno() + ")");
	  component.setButtonGroup( v );
	  break;
	default:
	  shouldNotGetHere(5, t);
	}
      }
    }
    



    private static String readName (StreamTokenizer t) 
    throws IOException {
	int tokenType = t.nextToken();
	if (debug) traceToken(tokenType, "readName", t);
	if (tokenType == DoubleQuote)
	    return t.sval;
	else {
	    shouldNotGetHere(6, t);
	    return null;
	}
    }

    private static double readNumber (StreamTokenizer t) 
    throws IOException {
	int tokenType = t.nextToken();
	if (debug) traceToken(tokenType, "readNumber", t);
	if (tokenType == StreamTokenizer.TT_NUMBER)
	    return t.nval;
	else {
	    shouldNotGetHere(7, t);
	    return (double)-1;
	}
    }


    //---- debugging code

    private static void shouldNotGetHere(int index, StreamTokenizer t) {
	throw new RuntimeException("Bad format. Case #" + index +
				   " line #" + t.lineno());
    }
    
    private static void traceToken(int tokenType, String caller,
				   StreamTokenizer t) {
	String type = "unknown";
	switch (tokenType) {
	case StreamTokenizer.TT_EOF:
	    type = "EOF";
	    break;
	case StreamTokenizer.TT_EOL:
	    type = "EOL";
	    break;
	case StreamTokenizer.TT_NUMBER:
	    type = "a number";
	    break;
	case StreamTokenizer.TT_WORD:
	    type = "a word";
	    break;
	case DoubleQuote:
	    type = "a string";
	    break;
	case OpenParen:
	  type = "an open parenthesis";
	  break;
	case CloseParen:
	  type = "a close parenthesis";
	  break;
	default:
	    type = "unknown";
	}
	System.out.println(caller +": line #" + t.lineno() + " read " + type);
	if (tokenType==StreamTokenizer.TT_NUMBER)
	    System.out.println("     " + t.nval);
	else if ((tokenType==StreamTokenizer.TT_WORD)
		 || (tokenType==DoubleQuote))
	    System.out.println("     " + t.sval);
    }


}
