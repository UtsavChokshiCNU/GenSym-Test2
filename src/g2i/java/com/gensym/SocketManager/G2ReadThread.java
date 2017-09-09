package com.gensym.SocketManager;

// gensym imports
import com.gensym.jgi.*;
import com.gensym.util.*;

// java imports
import java.io.*;
import java.nio.charset.Charset;

public class G2ReadThread extends Thread {

  /** Thread class specifically for reading a buffer populated asynchronously by
    * the input thread of the socket
    * Run method tries to read the buffer every 200ms
    * Data returned is sent to G2 - parsed for message start/end delimiters if specified
    * Hooks to PERL or further parsing would be done here
    */


  // symbols for G2 procedures which may be called by Java
  static Symbol socketMessagetoG2RPC = Symbol.intern("_G2-JAVA-INTERFACE-RX-MESSAGE-RPC");


  volatile boolean isActive = true;
  volatile boolean accumulate = false;
  volatile boolean endFound = false;
  volatile String accumulateData = new String(""); // buffer to maintain data to be sent to G2
  volatile String matchData = new String("");      // buffer to maintain data waiting on matches
  private G2InputThread inThread;
  private G2ClientSocket g2client;
  private boolean startMask, endMask;
  private int startMaskOption, endMaskOption;
  private boolean fromSocket;

  private G2PerlRegexParser regexParser = new G2PerlRegexParser();

  public G2ReadThread(G2ClientSocket g2client) {
    this.g2client = g2client;
    this.inThread = g2client.socketIn;
    super.setName("Read "+inThread.getName());
    G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Created a client socket read thread for "+g2client.refID);
  }

  public void run(){

    while(isActive){

      try{
        String readStr = readInputThreadBuffer();
        if(!readStr.equals("")){    // send to G2 if read is not null
	  if (g2client.logFilteredSocketData) logSocketData(readStr, true);
          /** Change string to sequence of individual char strings so that
	      nulls don't terminate the javalink  translation of the string
	      itself
          */
            Sequence charSeq = new Sequence();
            char [] charArray = readStr.toCharArray();
            for(int i = 0; i < readStr.length(); i++){
              Character sChar = Character.valueOf(charArray[i]);
              charSeq.addStringElement(sChar.toString());
            }
	    
	    try{
	      g2client.socketManager.g2connection.callRPC(socketMessagetoG2RPC, new Object[] { g2client.refID, g2client.cnxID, charSeq }, 1000);
	      G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Sent to G2 : "+readStr);
	    }catch(TimeoutException gte){
	      G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Timeout excpetion while trying to send data "+readStr+"\nto G2 to Socket: \n"+g2client.refID+"\n cnx id = "+g2client.cnxID);
	    }catch(G2AccessException gae){
	      G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Access excpetion while trying to send data "+readStr+"\nto G2 to Socket: \n"+g2client.refID+"\n cnx id = "+g2client.cnxID);
	    }
        } // end if readStr not ""
      }catch (Exception e){
        G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Unable to get result from socket\n"+e.getMessage());
      }
     
      try{
        sleep(200);
      }catch(InterruptedException iee){
	G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Interrupted READ thread of socket: "+g2client.refID);
      }
    }
  }

  private String readInputThreadBuffer(){

    /** Parsing is non-trivial when message delimiters are specified, asynchronous reads mean this
      * method must keep track of the parsing phase whether characters should be passed to G2
      * (via the <B>acceptChar</B> boolean)
      * Note that start/end tokens that may be truncated over a number of reads of the buffer which
      * adds complexity to the parsing
      * Would like to move this into a dedicated parser
      */

    String newRead = new String("");
    try{    // read the input thread buffer
      if (g2client.client.getInputStream() != null) newRead = inThread.getResult();
    }catch(IOException ioe){
    }

    if (newRead.equals("")) return newRead;   // buffer empty, trivial action
    if (g2client.logRawSocketData) logSocketData(newRead, false);
    String g2String = parseDataRead(newRead, true);
    return g2String;
  }


  private String parseDataRead(final String dataRead, final boolean fromSocket){
	String data = dataRead;
    if(!accumulate){ // look for start
      if(fromSocket) matchData = matchData+data;

      String validData = parseForStartToken(matchData, g2client.msgStart);
      if(validData.equals("")) return validData; //no match found
      matchData = new String(""); // reinitialize to null string
      if(g2client.msgEnd.equals("")) return validData; // no end specified, pass data
      data = validData; //set data read to be equal to the valid data, disregarding anything before start delimiter
    }

    if(accumulate && g2client.msgEnd.equals("")){ // start found, no end spec - pass thru
      return data;
    }
    else if(accumulate && !g2client.msgEnd.equals("")){ // start found, wait for end
      accumulateData = accumulateData + data; // start found some time prior, accumulate until end found
      accumulateData = checkSize(accumulateData); // curb if text getting too big
      //System.out.println("Accumulate: "+accumulateData);
      String g2string = parseForEndToken(accumulateData, g2client.msgEnd);
      if(g2string.length() == accumulateData.length() && !endFound) return new String(""); // no end found return nothing
      matchData = accumulateData.substring(g2string.length(), accumulateData.length()); // keep end of string for more matches
      matchData =checkSize(matchData); // curb if text getting too big
      //System.out.println("G2String: "+g2string+"\nMatch rest: "+matchData);
      accumulate = false;
      accumulateData = new String(""); // reset accumulator, g2 data in g2string variable
      g2string = g2string+parseDataRead(matchData, false);  // get any more matches
      return g2string; // return successful begin/end match
    }
    return new String("");

  }

  private String parseForStartToken(String parseStr, String tokStr){

    /** Parse for start token
      * If the token is found return anything AFTER it (incl token if not stripping delimiters)
      * otherwise return the entire string
      */
    if(regexParser.isMatched(tokStr, parseStr, g2client.startCaseInSensitive, g2client.startMultiLine, g2client.startIsExtendedMask)){  // found start token start accepting chars
      G2JavaLog.log(G2JavaLog.TROUBLESHOOT,"\nFound match for START token: "+tokStr+" in string: "+parseStr+" at begin/end offsets: "+regexParser.beginOffset+"/"+regexParser.endOffset);
      accumulate = true;
      if(!g2client.stripDelimiters) return parseStr.substring(regexParser.beginOffset, parseStr.length());
      else return parseStr.substring(regexParser.endOffset, parseStr.length());

    }else return new String(""); // no match found
  }

  private String parseForEndToken(String parseStr, String tokStr){

    /** Parse for end token
      * If the token is found return anything BEFORE it (incl token if not stripping delimiters)
      * otherwise return entire string
      */
    endFound=false;
    if(regexParser.isMatched(tokStr, parseStr, g2client.endCaseInSensitive, g2client.endMultiLine, g2client.endIsExtendedMask)) { // end token found, stop accepting chars and return the appropriate substring
      G2JavaLog.log(G2JavaLog.TROUBLESHOOT,"\nFound match for END token: "+tokStr+" in string: "+parseStr+" at begin/end offsets: "+regexParser.beginOffset+"/"+regexParser.endOffset);
      endFound = true;
      if(!g2client.stripDelimiters) return parseStr.substring(0, regexParser.endOffset);
      else return parseStr.substring(0, regexParser.beginOffset);

    }
    else return parseStr; // no end token found, return the lot
  }

  private String checkSize(final String data){
	String dataStr = data;
    if(dataStr.length() > JavaG2SocketManager.MAX_DATA_HOLD){
    	dataStr = dataStr.substring(dataStr.length() - JavaG2SocketManager.MAX_DATA_HOLD, dataStr.length());
    }
    return dataStr;
  }

  private void logSocketData(String logStr, boolean state){

    /** Log to a text file whose name isspecified as RAW or FILTERED and
      * coded by the client socket hashcode
      */

    String logFile;
    //if (!state) logFile = "RAW-"+g2client.hashCode()+".txt";
    //else logFile = "FILTERED-"+g2client.hashCode()+".txt";
    if (!state) logFile = "RAW-"+g2client.client.getPort()+"-"+g2client.client.getLocalPort()+".txt";
    else logFile = "FILTERED-"+g2client.client.getPort()+"-"+g2client.client.getLocalPort()+".txt";

    G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "About to log the data: "+logStr+"\nto file: "+logFile);

    try{
      FileOutputStream fOut = new FileOutputStream(logFile, true);
      PrintWriter printOut = new PrintWriter(new OutputStreamWriter(fOut, Charset.defaultCharset()), true);
      printOut.println(G2MessageFormatter.format(G2JavaLog.TROUBLESHOOT, logStr));
      fOut.close();
    }catch(IOException ioe){
      G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Problems finding/opening file: "+logFile);
    }

  }


}
