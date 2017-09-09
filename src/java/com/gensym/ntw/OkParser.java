/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TwOkParser.java
 *
 * author: David McDonald
 * version: 1.1  11/98
 */
package com.gensym.ntw;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.io.StreamTokenizer;
import java.nio.charset.Charset;

import com.gensym.message.Resource;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;


/** This is a fix-grammar analyzer for OK files. All its methods are static.
 * Its driver, findMachineIDInTw2OkFile, is provided with an open stream to 
 * the file, an empty OkInfo object in which to place its results, and a string
 * indicating which machine id it is to look for in the file.
 *    OK files consist of one or more lines (including empty lines or comments)
 * with a single entry on each filled line. Entries for other machines are 
 * ignored after the machine id on their line has been read and checked. 
 * Within the target entry any mistake in syntax (i.e. the order or type of
 * the elements of the entry) or the omission of a required element will cause
 * an OkException to be thrown. Once the target entry has been located the
 * rest of the file is ignored.  File handling is done by the caller.
 *
 * @undocumented  */

class OkParser {

  private static boolean debug = false;


  //---- driver
  static boolean findMachineIDInTw2OkFile(Reader r, OkInfo ok, 
					  String id, String nameOfFileBeingRead)
  throws IOException, OkException {
    initializeState();
    StreamTokenizer t = new StreamTokenizer(r);
    t.eolIsSignificant( true );
    t.commentChar('#');
    if (debug)
      System.out.println("The target id is \"" + id + "\"");
    do {
      scanLineForTargetID(t, id);
      if (eofReached && !foundTargetID) {
	mistake(t, "machineNotFound", id, nameOfFileBeingRead);
	return false;
      }
    }
      while ( !foundTargetID );

    if (debug)
      System.out.println("Parsing done.\n  target found = " + foundTargetID);

    populateOkInfo(ok);
    return true;
  }


  //---- locals to stash the elements of an entry into 
  private static volatile String machineName;
  private static volatile String machineID;
  private static int code1;
  private static int code2;
  private static int code3;
  private static int code4;
  private static int code5;
  private static int fromDay;
  private static volatile Symbol fromMonthSymbol;
  private static int fromYear;
  private static int toDay;
  private static volatile Symbol toMonthSymbol;
  private static int toYear;
  private static volatile String levelToken;
  private static volatile Symbol level;



  //---- Called when a syntactically valid instance of the target entry
  //     has been found.

  private static void populateOkInfo(OkInfo ok) {
    ok.setMachineName(machineName);
    ok.setMachineID(machineID);
    ok.setCode1(code1);
    ok.setCode2(code2);
    ok.setCode3(code3);
    ok.setCode4(code4);
    ok.setCode5(code5);
    if (!"".equals(levelToken)) {
      ok.setLevel(level);
    }
    /* Process counts were part of the original spec. Keeping these lines
     * in case it or something like it ever goes back into the spec. */
    //    if ( processCount != -1)
    //      ok.setProcessCount(processCount);
    if ( includesTempInterval ) {
      ok.setTemporaryLicense( true );
      Sequence from = new Sequence(3);
      from.insertElementAt( fromDay, 0);
      from.insertElementAt(fromMonthSymbol, 1);
      from.insertElementAt(fromYear, 2);
      ok.setFrom(from);
      Sequence to = new Sequence(3);
      to.insertElementAt(toDay, 0);
      to.insertElementAt(toMonthSymbol, 1);
      to.insertElementAt(toYear, 2);
      ok.setTo(to);
    }      
  }



  //---- state controlling the search 
  private static boolean foundTargetID;
  private static boolean includesTempInterval;
  private static boolean eofReached;
  private static boolean eolReached;
  private static boolean wrongType;


  private static void initializeState() {
    machineName = ""; 
    machineID = ""; 
    code1 = -1; 
    code2 = -1; 
    code3 = -1; 
    code4 = -1;
    fromDay = -1; 
    fromYear = -1;
    toDay = -1; 
    toYear = -1;
    levelToken = ""; 
    //processCount = -1;
    foundTargetID = false; 
    includesTempInterval = false;
    eofReached = false; 
    eolReached = false;
    wrongType = false;
  }
       
  //---- rename the tokenizer's flags for readability
  static final int WORD = StreamTokenizer.TT_WORD;
  static final int NUMBER = StreamTokenizer.TT_NUMBER;
  static final int EOF = StreamTokenizer.TT_EOF;
  static final int EOL = StreamTokenizer.TT_EOL;
  static final int QUOTE = (int)'\"';




  //---- all the 'parsing' is done from here on down

  static void scanLineForTargetID(StreamTokenizer t, String targetID)
  throws IOException, OkException {
    eolReached = false; 

    // Get the name
    switch ( t.nextToken() ) {
    case EOL:
      if (debug)
	System.out.println("Line " + t.lineno() + " is empty");
      return; 
    case EOF:
      eofReached = true;
      return;
    case WORD:
      machineName = t.sval;
      break;
    default:
      mistake(t, "noMachineName");
      return;
    }

    // Get the id
    switch ( t.nextToken() ) {
    case QUOTE:
      machineID = t.sval;
      break;
    case EOF:
      eofReached = true;
      return;      
    default:
      mistake(t, "noMachineID");
      flushLine(t);
      return;
    }

    // If the id is the one we want, keep going.
    if ( machineID.equalsIgnoreCase(targetID) ) {
      if (debug)
	System.out.println("The id on line " + t.lineno() + 
			   " is the target id: \"" + targetID + "\"");
      foundTargetID = true;
      parseLine(t);
    }
    else {
      if (debug)
	System.out.println("The id on line " + t.lineno() + " is \"" +
			   machineID + "\" which is not the target");
      flushLine(t);
    }
  }



  /* We've determined that this entry/line doesn't have the target
   * entry on it so we just move the readhead to the next line as
   * dispatchfully as possible. */
  private static void flushLine(StreamTokenizer t) throws IOException {
    while ( (t.ttype != EOL) ) {
      t.nextToken();
      if (t.ttype == EOF) {
	eofReached = true;
	break;
      }
    }
  }


  /* When this is called we have gotten the machineID and determined
   * that this is the relevant entry. This extracts the rest of the
   * line and populates the locals. */
  private static void parseLine(StreamTokenizer t) 
  throws IOException, OkException {
    code1 = extractInteger(t);
    if ( eolReached || wrongType ) { 
    	mistake(t, "noCodes"); 
    	return; 
    }
    code2 = extractInteger(t);
    if ( eolReached || wrongType ) { 
    	mistake(t, "notEnoughCodes", 4); 
    	return; 
    }
    code3 = extractInteger(t);
    if ( eolReached || wrongType ) { 
    	mistake(t, "notEnoughCodes", 3); 
    	return; 
    }
    code4 = extractInteger(t);
    if ( eolReached || wrongType ) { 
    	mistake(t, "notEnoughCodes", 2); 
    	return; 
    }
    code5 = extractInteger(t);
    if ( eolReached || wrongType ) { 
    	mistake(t, "notEnoughCodes", 1); 
    	return; 
    }

    if ( !eolReached ) 
      continueFromCodes(t);
  }

  private static void continueFromCodes(StreamTokenizer t) 
  throws IOException, OkException {
    /* The next token is either the license level or 'from', or there could be
     * no additional tokens since the level is optional. */
    int type = t.nextToken();
    traceExtractedToken(type, t);
    switch ( type ) {
    case WORD:
      if ( t.sval.equalsIgnoreCase("from") ) {
        parseTemporaryIntervals(t);
        parseOptionalLicenseLevel(t);
      }
      else {
        synchronized (OkParser.class) {
          levelToken = t.sval;
          definedLevel(levelToken, t);
        }
      }
      break;
    case NUMBER:
      mistake(t, "numberInsteadOfFromOrLevel", new Double(t.nval) );
      break;
    case EOF:
      eofReached = true;
      eolReached = true;
      break;
    case EOL:
      eolReached = true;
      break;
    default:
      mistake(t, "unreachableNo1");
    }
  }



  /* Barring the re-introduction of a process (connection limit?) count or such,
   * this is always the last thing on the line. */
  private static void parseOptionalLicenseLevel(StreamTokenizer t) 
  throws IOException, OkException {
    int type = t.nextToken();
    traceExtractedToken(type, t);
    switch ( type ) {
    case WORD:
      synchronized (OkParser.class) {
        levelToken = t.sval;
        definedLevel(levelToken, t);
      }
      break;
    case EOF:
    case EOL:
      break;
    case NUMBER:
      mistake(t, "numberNotLevel");
      break;
    default:
    }
  }


  private static final Symbol DEVELOPMENT = Symbol.intern("DEVELOPMENT");
  private static final Symbol DEPLOYMENT = Symbol.intern("DEPLOYMENT");


  private static boolean definedLevel(String levelToken, StreamTokenizer t)
  throws OkException {
    if ( levelToken.equalsIgnoreCase("development") ) {
      level = DEVELOPMENT;
      return true;
    }
    else if ( levelToken.equalsIgnoreCase("deployment") ) {
      level = DEPLOYMENT;
      return true;
    }
    else {
      mistake(t, "UnknownLicenseLevel", levelToken);
      return false;
    }
  }

    

  /* When this is called we have just gotten the token "from" and
   * we expect a well-formed pair of date intervals. */
  private static void parseTemporaryIntervals(StreamTokenizer t)
  throws IOException, OkException {
    fromDay = extractInteger(t);
    if (eolReached || wrongType) { 
    	mistake(t, "expectedDay"); 
    	return; 
    }

    String fromMonth = extractWord(t);
    if (eolReached || wrongType) { 
    	mistake(t, "expectedMonth"); 
    	return; 
    }
    if ( !validMonthExpression(fromMonth) ) {
      mistake(t, "ill-formed month"); 
      return; 
    }
    fromMonthSymbol = symbolForMonth(fromMonth);

    fromYear = extractInteger(t);
    if (eolReached || wrongType) { 
    	mistake(t, "expectedYear"); 
    	return; 
    }

    String to = extractWord(t);
    if (eolReached || wrongType) { 
    	mistake(t, "noTOField"); 
    	return; 
    }
    if ( !to.equalsIgnoreCase("to") ) {
      mistake(t, "expected 'to' token"); 
      return; 
    }

    toDay = extractInteger(t);
    if (eolReached || wrongType) { 
    	mistake(t, "expectedDay"); 
    	return; 
    }

    String toMonth = extractWord(t);
    if (eolReached || wrongType) { 
    	mistake(t, "expectedMonth"); 
    	return; 
    }
    if ( !validMonthExpression(toMonth) ) {
      mistake(t, "ill-formed month"); 
      return; 
    }
    toMonthSymbol = symbolForMonth(toMonth);

    toYear = extractInteger(t);
    if (eolReached || wrongType) { 
    	mistake(t, "expectedYear"); 
    	return; 
    }

    if ( validateYearPair(fromYear, toYear, t) )
      includesTempInterval = true;
  }


  private static boolean validMonthExpression(String m) {
	boolean isValidMonth = m.equalsIgnoreCase("jan") || m.equalsIgnoreCase("feb"); 
	isValidMonth = isValidMonth || m.equalsIgnoreCase("mar") || m.equalsIgnoreCase("apr");
	isValidMonth = isValidMonth || m.equalsIgnoreCase("may") || m.equalsIgnoreCase("jun");
	isValidMonth = isValidMonth || m.equalsIgnoreCase("jul") || m.equalsIgnoreCase("aug");
	isValidMonth = isValidMonth || m.equalsIgnoreCase("sep") || m.equalsIgnoreCase("oct");
	isValidMonth = isValidMonth || m.equalsIgnoreCase("nov") || m.equalsIgnoreCase("dec");
    
	return isValidMonth;
  }

  static final Symbol JAN = Symbol.intern("JAN");
  static final Symbol FEB = Symbol.intern("FEB");
  static final Symbol MAR = Symbol.intern("MAR");
  static final Symbol APR = Symbol.intern("APR");
  static final Symbol MAY = Symbol.intern("MAY");
  static final Symbol JUN = Symbol.intern("JUN");
  static final Symbol JUL = Symbol.intern("JUL");
  static final Symbol AUG = Symbol.intern("AUG");
  static final Symbol SEP = Symbol.intern("SEP");
  static final Symbol OCT = Symbol.intern("OCT");
  static final Symbol NOV = Symbol.intern("NOV");
  static final Symbol DEC = Symbol.intern("DEC");

  private static Symbol symbolForMonth(String m) {
    if      (m.equals("jan")) 
    	return JAN;
    else if (m.equals("feb")) 
    	return FEB;
    else if (m.equals("mar")) 
    	return MAR;
    else if (m.equals("apr")) 
    	return APR;
    else if (m.equals("may")) 
    	return MAY;
    else if (m.equals("jun")) 
    	return JUN;
    else if (m.equals("jul")) 
    	return JUL;
    else if (m.equals("aug")) 
    	return AUG;
    else if (m.equals("sep")) 
    	return SEP;
    else if (m.equals("oct")) 
    	return OCT;
    else if (m.equals("nov")) 
    	return NOV;
    else if (m.equals("dec")) 
    	return DEC;
    else return null;
  }


  /* This just does a sanity check against the two years that are given.
   * The real, date-specific check happens on the other side of the
   * fence in G2. */
  private static boolean validateYearPair(int from, int to,
					  StreamTokenizer t) throws OkException {
    if (to < from) {
      mistake(t, "endsBeforeBbegins");
      return false;
    }
    else if (to > (from + 5)) {
      mistake(t, "intervalTooLong");
      return false;
    }
    else
      return true;
  }





  private static int extractInteger(StreamTokenizer t) throws IOException {
    wrongType = false;
    int type = t.nextToken();
    traceExtractedToken(type, t);
    switch ( type ) {
    case EOF:
      eofReached = true;
      return -1;
    case EOL:
      eolReached = true;
      return -1;
    case WORD:
      wrongType = true;
      return -1;
    default:
      return (int)t.nval;
    }
  }

  private static String extractWord(StreamTokenizer t) throws IOException {
    wrongType = false;
    int type = t.nextToken();
    traceExtractedToken(type, t);
    switch ( type ) {
    case EOF:
      eofReached = true;
      return "";
    case EOL:
      eolReached = true;
      return "";
    case NUMBER:
      wrongType = true;
      return "";
    default:
      return t.sval;
    }
  }
    
      
  private static void traceExtractedToken(int type, StreamTokenizer t) {
    // put under trace regimine(sp?)
    if (debug) {
      String s = "Next token is ";
      switch ( type ) {
      case EOF:
	s += "EOF";
	break;
      case EOL:
	s += "EOL";
	break;
      case QUOTE:
	s += "the quoted string \"" + String.valueOf(t.sval) + "\"";
	break;
      case WORD:
	s += "the string " + String.valueOf(t.sval);
	break;
      case NUMBER:
	s += "the number " + String.valueOf(t.nval);
	break;
      default:
	s += "something we don't understand";
      }
      System.out.println(s);
    }
  }

      

    
    
      
  //---- report errors

  private static Resource i18n = Resource.getBundle("com.gensym.ntw.Messages");

  /* This is a hack to get around the problem that the signature for mistake
   * that has the tokenizer and one string cannot distinguish between the case
   * where that string is a key to be expanded via the properties file or an
   * already expanded one. This lets us make it always be the key. Since the
   * result is going to be an exception we don't have to manage this local. */
  private static volatile String problemText;

  private static void mistake(StreamTokenizer t, String problem)
  throws OkException {
    problemText = i18n.format(problem, null);
    mistake(t);
  }

  private static void mistake(StreamTokenizer t, String problem, Object arg1)
  throws OkException {
    problemText = i18n.format(problem, arg1);
    mistake(t);
  }

  private static void mistake(StreamTokenizer t, String problem, Object arg1, Object arg2)
  throws OkException {
    problemText = i18n.format(problem, arg1, arg2);
    mistake(t);
  }

  private static void mistake(StreamTokenizer t) throws OkException {
    String contextText = i18n.format("OkFileProblem", t.lineno());
    throw new OkException(contextText + problemText);
  }    



	    //----  test routine -------------------
  public static void main(String[] args) 
  throws FileNotFoundException, IOException, OkException {
    String fileName = "D:\\tmp\\tw2 ok.txt";
    File ok;
    if ( args.length==0 )
      ok = new File( fileName );
    else
      ok = new File( args[0] );

    String id;
    if ( args.length<1 )
      id = "00609758605D"; // "80723529";  
    else
      id = args[1];

    Reader r = new InputStreamReader( new FileInputStream(ok), Charset.defaultCharset());

    OkInfo info = new OkInfo();

    if ( findMachineIDInTw2OkFile(r, info, id, fileName) )
      System.out.println("Created:\n" + info.describe() );
    else
      System.out.println("Didn't find the target id: \"" + id + "\"");

    System.exit(1);
  }

} // end of class

