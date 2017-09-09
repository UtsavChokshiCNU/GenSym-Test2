package com.gensym.tests.jgi.testharness;

import java.util.Hashtable;
import java.util.Random;
import java.lang.Math.*;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.core.*;
import com.gensym.core.CmdLineArgHandler;
//import com.gensym.classes.Item;




import java.util.Vector;

/**
 * Connects to G2 and attempts to terminate the process.
 */
public class G2Killer implements Runnable, G2ConnectionListener // G2_EventSourceListener
{

  private Hashtable _threadTable = new Hashtable();

  private boolean _enableOutput = true;

  private G2Connection g2Connection = null;


  /**
   * Constructor
   */
  public G2Killer(G2Connection connection)
  {
    this.g2Connection = connection;
    connection.addG2ConnectionListener(this);
  }


  /**
   * Initialize all Local RPC's used by this subclass, this method is called only once
   * just before the first connection.
   */
  public void initializeLocalRPCs(G2Connection con)
  {


  }

  // *****************************************************************
  // G2ConnectionListener implementations

  /**
   * This Method is called when the connected G2 has been paused .
   */
  @Override
  public void g2IsPaused(G2ConnectionEvent e)
  {
    System.out.println("G2 Has been paused :o(");
  }
  /**
   * This method is called when the connected G2 has been resumed.
   */
  @Override
  public void g2IsResumed(G2ConnectionEvent e)
  {
    System.out.println("G2 Has been resumed :o)");
  }

 /**
   * This method is called when the connected G2 has been reset.
   */
  @Override
  public void g2IsReset(G2ConnectionEvent e)
  {
    System.out.println("G2 Has been reset :]");
  }

  /**
   * This method is called when the connected G2 has been started.
   */
  @Override
  public void g2IsStarted(G2ConnectionEvent e)
  {
    System.out.println("G2 Has been Started ;)");
  }

  /**
   * Called when G2 sends a message to the G2Connection.
   */
  @Override
  public void g2MessageReceived(G2ConnectionEvent e)
  {
    System.out.println("Message received from G2 was: " + e.getMessage());
  }

  /**
   * Called when an asynchronous error has occured in the G2 communications interface
   * for the G2Connection
   *
   *@param error_event An G2CommunicationErrorEvent describing the error that occured.
   */
  @Override
  public void communicationError(G2CommunicationErrorEvent error_event)
  {
    System.out.println(error_event.getMessage());
  }

  /**
   * Called when the network cannot deliver data that Java is attempting to write to G2.
   */
  @Override
  public void readBlockage(G2ConnectionEvent event) {}

  /**
   * Called when the network cannot deliver data that G2 is attempting to write to Java.
   */
  @Override
  public void writeBlockage(G2ConnectionEvent event) {}

  /**
   * This method is called when the G2 connection has been shutdown.
   * Must call super() here.
   */
  @Override
  public void g2ConnectionClosed(G2ConnectionEvent e)
  {
    System.out.println("G2 Connection has been closed ");
        System.exit(0);
  }


  /**
   * A connection has been established between this connection and a G2 GSI-INTERFACE.
   * This method is called, so the connection specific information can be set up.
   * Specifically, declaring G2 methods and procedures that this connection would like to call.
   * Note: G2 method and procedure declarations are connection specific.
   */
  @Override
  public void g2ConnectionInitialized(G2ConnectionEvent e)
  {

    String remote_process_string = e.getMessage();


    // Send a "hi" message to G2's message board
    g2Connection.returnMessage("Connected to G2Killer (rpis = " + remote_process_string + ")\n Hi There from G2Gateway Java VM, how are you G2 ?");

    // Also Send an error message
    g2Connection.reportLogBookErrorMessage
      (Symbol.intern("ERROR"),
       "Dont worry this message is just a test Error message from Java class G2Killer");


    // Now lets call a G2 procedure, JAVA-CALL
    try {


    } catch (Exception E) {
	System.out.println(E.toString());
    }
  }




  // *****************************************************************
  // Implements Runnable

  /**
   * Run method, for execution of a new thread. Here we call G2 procs and methods
   * _threadLoopCount times, this shows that G2 procs and methods can be
   * called from multiple Java threads.
   */
  @Override
  public void run()
  {
    // Loop calling two G2 Procs

  }

  // ******************************************************************
  // Methods to call know G2 Procedures



  /**
   * Raise Exception of class given.
   */
  public void raiseException(String exception_name)
       throws Throwable
  {
    Class eclass = Class.forName(exception_name);

    Throwable throwable = (Throwable)eclass.newInstance();

    throw throwable;
  }


  public void callG2Shutdown(int item1 )
       throws G2AccessException
  {
    System.out.println("MT" + item1 + " " + Runtime.getRuntime().freeMemory());

    Object args[] = { new Integer(item1) };
    g2Connection.startRPC(Symbol.intern("TH-SHUTDOWN-Y"), args );
  }




  /**
   * Turn the lots of output on/off
   */
  public void setOutput(boolean state)
  {
    _enableOutput = state;
  }

  /**
   * Set the Time message on the Parent applet
   */
  public void setAppletTime(double time)
  {

    System.out.println((long)time);
  }

  /**
   * Set the Message on the Parent applet
   */
  public void setAppletMessage(String message)
  {
    System.out.println(message);
  }




 public void terminate()
 {  System.out.println("Test Harness Termination...\n");

    System.exit(0);
    System.out.println("Test Harness has a problem...\n");
 }

  // *****************************************************************

  /**
   * Main method
   */
    static    G2Connection G_connection ;
    static    G2Killer G_gw;

  public static void main(String args[])
  {

	System.out.println("Test Harness Started...\n");

    try {
      G2Gateway.initialize(new String[] {"-listenerport", "22041"});
    }
    catch (AlreadyInitializedException E) { System.out.println(E.toString());};

    G2Gateway.setConnectionHandlerFactory(new G2ConnectionHandlerFactory() {

      @Override
      public G2Connection createG2Connection(String connection_data)
	{
	  G2Gateway new_gateway = new G2Gateway();
	  G2Killer egw = new G2Killer(new_gateway);

	  return new_gateway;
	} });


    G2Gateway.startup();

    CmdLineArgHandler cmdline = new CmdLineArgHandler(args);

    String host = cmdline.getOptionValue("-host");
    String port = cmdline.getOptionValue("-port");
    boolean result = false;

    if (port != null || host != null)
      {
	//try to connect to a g2 if we are asked
	try {

	    G2Connection g2_connection  =
	    G2Gateway.getOrMakeConnection((host == null ? "localhost" : host),
					  (port == null ? "1111" : port));

	  G2Killer egw = new G2Killer(g2_connection);

	  G_gw = egw;
	  G_connection=g2_connection;
	  g2_connection.returnMessage("Connected to G2Killer \n Hi There from G2Gateway Java VM, how are you G2 ?");
	  System.out.println("Connected to G2 OK");
	  try{
	    egw.callG2Shutdown(2);
	  }catch (Exception e){};
        System.out.println("Test Harness Termination...\n");


	} catch (Exception E) { System.out.println(E.toString()); }

  }
      //startThThreads(G_gw ,G_connection,50);

  }



}

