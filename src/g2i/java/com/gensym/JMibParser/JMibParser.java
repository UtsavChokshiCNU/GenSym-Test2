package com.gensym.JMibParser;


//gensym imports
import com.gensym.jgi.*;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.util.*;

//java imports
import java.io.*;
import java.net.*;
import java.lang.reflect.Method;
import java.lang.Math;
import java.util.*;
import java.text.SimpleDateFormat;

//mail imports
import java.util.Properties;


//******************************************************************************

public class JMibParser implements G2ConnectionListener {

  /** This class provides a process linked to a G2 application (via a gsi-interface object)
   *  to send and receive email
   */

  // static class variables
  private static final int MAJOR_VERSION_NUMBER = 1;
  private static final int MINOR_VERSION_NUMBER = 0;
  private static final String RELEASE_STATE = "Rev.";
  private static final int REVISION_NUMBER = 1;
  private static final String BUILD_MONTH = "F";
  private static final String BUILD_DAY = "15";
  private static final String INTEGRITY_INFORMATION = "Built for Integrity 5.0 Rev. 0";
  private static final String VERSION_INFORMATION = "Version "
  +MAJOR_VERSION_NUMBER+"."
  +MINOR_VERSION_NUMBER+" "
  +RELEASE_STATE+" "
  +REVISION_NUMBER;
  private static final String BUILD_INFORMATION = "Build "+BUILD_MONTH+BUILD_DAY;

  private static int port;

  private static String [] allowedCmdLineParams
    = {"-help", "-Help","-port","-Port", "-?", "-debug"};
  private static String [] allowedConnectionParams
    = {"-debug"};

  static G2Connection g2connection;

  // non-static class variables
  private String cnx_string;

  // symbols for G2 procedures which may be called by Java
  //static Symbol receiveMailIntoG2RPC = Symbol.intern("_JMAIL-RECEIVE-MAIL-INTO-G2-RPC");

  //constructor
  public JMibParser(G2Connection g2connection, String cnx_string) {
    this.g2connection = g2connection;
    this.cnx_string = cnx_string;
    String[] cnx_data = {"", ""}; //How to parse string into array?

    //Handle connection data - allow fuzzy matches
    //CmdLineArgHandler cnx = new CmdLineArgHandler(cnx_data, JMailBridge.allowedConnectionParams, true);
    // get debug level
    //String debugLevelString = cnx.getOptionValue("-debug");

    if (cnx_string.equals(new String("-debug"))){
      // debug request from G2 - set debugLevel to log ALL messages to console
      G2JavaLog.debugLevel = G2JavaLog.BRIDGE_IO;
      G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "Overriding current JAVA process debug level with max from G2");
    }

    G2JavaLog.log(G2JavaLog.BRIDGE_METHODS, "About to register java methods for G2 to call as RPCs");
    registerJavaMethods(g2connection);
    G2JavaLog.log(G2JavaLog.BRIDGE_METHODS, "Create a G2 Listener object for this connection");
    g2connection.addG2ConnectionListener(this);
  }


  // Begin implementation method definitions:
  // g2IsPaused, g2IsStarted, g2IsResumed, g2IsReset, g2MessageReceived,
  // communicationError, readBlockage, writeBlockage, g2ConnectionClosed, g2ConnectionInitialized

  public void g2IsPaused(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "G2 is paused - awaiting resume");
  }

  public void g2IsStarted(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "G2 has (re)started - connection established");
  }

  public void g2IsResumed(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION,"G2 has resumed");
  }

  public void g2IsReset(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "G2 has been reset - closing all open sockets & awaiting restart");
    System.gc(); // garbage collect while process is idle
  }

  public void g2MessageReceived(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "Message received from G2: "+ g2e.getMessage());
  }

  public void communicationError(G2CommunicationErrorEvent g2ee){
    G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "G2/Java communication error: "+ g2ee.getMessage());
  }

  public void readBlockage(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "Error reading from G2");
  }

  public void writeBlockage(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "Error writing to G2");
  }

  public void g2ConnectionClosed(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "G2 connection closed - close sockets");
    System.gc(); // garbage collect while process is idle
  }

  public void g2ConnectionInitialized(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "G2 connection initialized");
    if (G2JavaLog.debugLevel == G2JavaLog.BRIDGE_G2_INTERACTION){
      g2connection.returnMessage("\n Java Brigde talking with G2.");
    }
  }

  /** Register java methods called by G2 as RPCs.
    *
    */

  private void registerJavaMethods(G2Connection g2connection){

    G2JavaLog.log(G2JavaLog.BRIDGE_G2_INTERACTION, "Registering JAVA methods for G2 to call as RPCs");

    try{
      /* Parsing Method called from G2 */
      Method parseMibMethod =
        this.getClass().getDeclaredMethod("parseMib", new Class[] {String.class, String.class});
      g2connection.registerJavaMethod(
        this, parseMibMethod, Symbol.intern("_gmib-parse-mib-rmt"), true);
      /* Shutdown Method called from G2 */
      Method shutDownMethod =
        this.getClass().getDeclaredMethod("shutDown", new Class[0]);
      g2connection.registerJavaMethod(
        this, shutDownMethod, Symbol.intern("_gmib-shutdown-rmt"), true);


    }catch(NoSuchMethodException nsme){
      System.err.println("Could not find method to register for "+nsme.toString());
    }
  }


  /*
   * The only java method called by G2
   * Note that the module-name needs to be the file-name of the mib.
   * This is not necessarilly the same as the name used in the 'DEFINITIONS' clause of the mib.
   * The mib-loader will automatically load mibs that this mib 'IMPORTS'. However, in that case,
   * the file-names of these mibs need to be exactly the same as used in the 'IMPORTS' clause.
   * Experience shows that the 'standard' mibs do not need to be loaded. Apparently,
   * this data is somewhere encoded in the AdventNet code.
   *
   * moduleName - The file-name of the mib to be loaded.
   * searchPath - String specifying the search path, for multiple paths separate the paths by the pipe (|)
          symbol.
   */
  public Structure parseMib(String moduleName, String modulePath){
    ParseResult parseResult = new ParseResult();

    Structure resultStruct = parseResult.loadAndParseMib(moduleName, modulePath);

    return resultStruct;
  }

  public void shutDown () {
    g2connection.closeConnection();
    System.exit(0);
  }


  public static void main(String[] args) {

    System.out.println();
	  System.out.println("+--------------------------------------------------+");
	  System.out.println("|                                                  |");
	  System.out.println("|    G2 Java Mib Parser Bridge                     |");
	  System.out.println("|    " + G2Version.VERSION_INFORMATION + " (Build " + G2Version.BUILD_INFORMATION + ")" + "            |");
          System.out.println("|    " + INTEGRITY_INFORMATION + "                |");
	  System.out.println("|                                                  |");
	  System.out.println("|    " + G2Version.COPYRIGHT_INFORMATION + "                  |");
	  System.out.println("|                                                  |");
	  System.out.println("+--------------------------------------------------+");
	  System.out.println("");
	  System.out.println("");

    //Handle command line parameters - allow fuzzy matches
    CmdLineArgHandler cmds = new CmdLineArgHandler(args, JMibParser.allowedCmdLineParams, true);
    // get debug level
    String debugLevelString = cmds.getOptionValue("-debug");

    if (debugLevelString == null) {G2JavaLog.debugLevel = 0;}
    else if (debugLevelString.equals("0")) {G2JavaLog.debugLevel = 0; ParseResult.adventNetDebug = false;}
    else if (debugLevelString.equals("1")) {G2JavaLog.debugLevel = 1; ParseResult.adventNetDebug = false;}
    else if (debugLevelString.equals("2")) {G2JavaLog.debugLevel = 2; ParseResult.adventNetDebug = false;}
    else if (debugLevelString.equals("3")) {G2JavaLog.debugLevel = 3; ParseResult.adventNetDebug = false;}
    else if (debugLevelString.equals("4")) {G2JavaLog.debugLevel = 4; ParseResult.adventNetDebug = false;}
    else if (debugLevelString.equals("5")) {G2JavaLog.debugLevel = 5; ParseResult.adventNetDebug = false;}
    else if (debugLevelString.equals("6")) {G2JavaLog.debugLevel = 6; ParseResult.adventNetDebug = false;}
    else if (debugLevelString.equals("7")) {G2JavaLog.debugLevel = 7; ParseResult.adventNetDebug = true;}

    // request for help
    if (cmds.getSwitchValue("-help") || cmds.getSwitchValue("-Help") ||cmds.getSwitchValue("-?")){
      System.out.println("\nUsage:\t JMibParser -port <port number>\n");
      System.exit(1);
    }

    // Initialize the G2 listener
    try{
      port = (int) cmds.getOptionLong(new String("-port"), 22044);
      new java.net.ServerSocket(port).close();
      // static class method call
      //G2Gateway.initialize(new String [] {"-listenerport", port+""});
      G2Gateway.initialize(port);
    }
    catch(IOException ioe){
      System.err.println("Error: TCP port "+port+" initialization failed");
      System.exit(1);
    }
    catch(AlreadyInitializedException aie){
      System.err.println("Error: TCP port "+port+" already initialized");
      System.exit(1);
    }

    //G2JavaLog.log(G2JavaLog.BRIDGE_METHODS, "Finished with G2Gateway.initialize on port " + port);

    // Deal with unsolicited connection request from G2 through a Cnx Handler Factory object
    G2Gateway.setConnectionHandlerFactory(new G2ConnectionHandlerFactory(){
      // Implementation of the Cnx Handler Factory method
      public G2Connection createG2Connection(String cnx_data){
        G2Gateway g2gateway = new G2Gateway();
        JMibParser mibParser = new JMibParser(g2gateway, cnx_data);
        return g2gateway;
      }
    });

    //G2JavaLog.log(G2JavaLog.BRIDGE_METHODS, "Finished with G2Gateway.setConnectionHandlerFactory");

    // Start Gateway
    G2Gateway.startup();
    G2JavaLog.log(G2JavaLog.MANDATORY,"Java Mib Parser Bridge listening for G2 connection on port: "+port);

  } // end main


} // end Socket Manager class definition

