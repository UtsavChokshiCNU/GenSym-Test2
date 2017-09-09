package com.gensym.jmail;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Gensym Copyright (c) 2004-2006</p>
 * <p>Company: Gensym Corporation</p>
 * @author not attributable
 * @version 1.0
 */

public class G2JavaLog{

  /** Simple class to allow uniform calls to logging from all classes
    * Debug levels can be easily modified
    * User specifies debug level on the command line to start the process via <B>-debug {number}</B>
    * OR by specifying the <B>remote-process-initialization-string</B> attribute on the G2
    * interface object to "-debug" - this automatically sets the debug level to the maximum
    */

  public static final int MANDATORY = 0;
  public static final int FATAL_BRIDGE = 1;
  public static final int NON_FATAL_BRIDGE = 2;
  public static final int G2_RPC_ERRS = 3;
  public static final int BRIDGE_METHODS = 4;
  public static final int BRIDGE_G2_INTERACTION = 5;
  public static final int BRIDGE_IO = 6;
  public static final int EMAIL_ANALYSIS = 7;

  public static int debugLevel = 0;  // debug level for commandline spec of Java SocketManager

  public static void log(int debug, String output){

	// Check if debug level is high enough to include information
    if (debug > debugLevel)
    	return;
    
    System.out.println(G2MessageFormatter.format(debug, output+"\n"));
  }
} 