package com.gensym.jgi.rmi;

import java.rmi.*;
import java.net.UnknownHostException;
import java.rmi.server.UnicastRemoteObject;
import java.net.*;
import java.util.*;
import java.io.Serializable;

import com.gensym.core.GensymApplication;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.util.*;
import com.gensym.core.DebugUtil;
import com.gensym.message.*;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.ConnectionResolver;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.jgi.G2AccessInitiationException;

/** A connection broker for running G2Gateway in three-tier mode.
 * Parses the command-line, exports itself, and waits for connection
 * requests.
 * Uses GensymApplication.initialize(String[]) to read some command-line
 * arguments.
 * <p>
 * Locally interpreted command-line arguments are:
 * <blockquote>
 * <pre>
 * -tsHost     The hostname to be used in Naming.bind(). Defaults to the
 *             return value of InetAddress.getLocalHost().getHostName().
 * -tsPort     Teleserver port: The port number to be used in the
 *             Naming.bind() of the broker. Defaults to NULL, which
 *             goes to port number 1099: the default for the rmiregistry.
 * -tsName     Teleserver name: The name to be used in the
 *             Naming.bind() of the broker.
 *             defaults to "com.gensym.jgi.rmi.G2RMIAccessBrokerImpl".
 * -g2Host     The default host name to be used when clients that
 *             request connections don't specify a host. Defaults to
 *             "localhost".
 * -g2Port     The default port number for connecting to G2. Defaults to
 *             1111.
 * -doRebind   Whether or not to replace the G2RMIAccessBroker already
 *             bound with the same tsName in the same rmiregistry.
 *
 * Example:
 * java com.gensym.jgi.rmi.G2RMIAccessBrokerImpl -tsName Teleserver -tsHost UnusualHostName -tsPort 54321
 *
 * This will result in the broker being bound at:
 * rmi://UnusualHostName:54321/Teleserver
 *
 * NOTE: this will only work if there is an rmiregistry started at that port.
 * </pre>
 * </blockquote>
 * @version 1.0 5-jun-97
 * @author Robert Penny
 */
public final class G2RMIAccessBrokerImpl
extends UnicastRemoteObject
implements G2RMIAccessBroker {

  private static final String DEFAULT_HOST = "localhost",
                              DEFAULT_PORT = "1111",
                              DEFAULT_TSNAME = "Teleserver";

  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.jgi.rmi.TraceMessages");
  private static Resource i18n =
  Resource.getBundle("com.gensym.jgi.rmi.Messages");
  private static TraceOut traceListener = new TraceOut();

  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.jgi.rmi",
			   "com.gensym.jgi.rmi.G2RMIAccessBrokerImpl");
  
  private String tsName, tsPort;
  private static volatile String tsHost;
  private boolean debug;
  // rpenny fix this: these are not fully implemented
  private String defaultG2Host = DEFAULT_HOST, defaultG2Port = DEFAULT_PORT;

  private static Hashtable openConnections = new Hashtable();

  /** To allow more flexibility in registration, the tsName and tsPort for rebinding
   * can be built from the command-line. The default tsName is the class name, and
   * by default, the tsPort is not specified.
   * Does not replace any existing broker of the same tsName.
   * @param tsName defaults to class name, here com.gensym.jgsi.G2RMIAccessBrokerImpl
   * @param tsPort defaults to "not specified in the rebind", therefore the same port
   * as the rmiregistry.
   * @param g2Host the default host to use if the host is <code>null</code>
   * in <code>getOrMakeConnection</code>
   * @param g2Port the default port to use if the port is <code>null</code>
   * in <code>getOrMakeConnection</code>
   */

  int pingFreq = -1; // don't do it by default

  private G2RMIAccessBrokerImpl (String tsName, String tsPort,
				 String g2Host, String g2Port,
				 boolean doRebind, int pingFrequency)
   throws RemoteException, AlreadyBoundException,
          MalformedURLException, UnknownHostException {
     this(tsName, tsPort, doRebind, pingFrequency);
     defaultG2Host = (g2Host == null ? defaultG2Host : g2Host);
     defaultG2Port = (g2Port == null ? defaultG2Port : g2Port);
     pingFreq = pingFrequency;
  }

  /** To allow more flexibility in registration, the tsName and tsPort for rebinding
   * can be built from the command-line. The default tsName is the class name, and
   * by default, the tsPort is not specified
   * @param tsName defaults to class name, here com.gensym.jgsi.G2RMIAccessBrokerImpl
   * @param tsPort defaults to "not specified in the bind", therefore the same port
   * as the default for the rmiregistry.
   * @param doRebind whether to allow a rebind if done again. In general
   * there should only be one bind attempt
   */

  private G2RMIAccessBrokerImpl (String tsName, String tsPort, boolean doRebind, int pingFrequency)
                throws RemoteException, AlreadyBoundException,
                       MalformedURLException, UnknownHostException {
     super ();
     pingFreq = pingFrequency;
     this.bind(tsName, tsPort, doRebind);
  }

  /** Allows the broker complete control over the URL at which it
   * is registered. Does not check to see if any client would be able
   * to locate it by that URL
   */
  private void bind(String urlString, boolean doRebind) throws RemoteException,
		  AlreadyBoundException,MalformedURLException, UnknownHostException {
    if(doRebind)
      Naming.rebind(urlString, this);
    else
      Naming.bind(urlString, this);
  }
    
  private void bind(String tsName, String tsPort, boolean doRebind)
                 throws RemoteException, AlreadyBoundException,
                 MalformedURLException, UnknownHostException {
    
    this.tsPort = tsPort;
    String portString = (this.tsPort == null ? "" : ":" + this.tsPort);
    this.tsName = (tsName == null ? this.getClass().getName() : tsName);

    String host = (tsHost == null ?
		   System.getProperty("java.rmi.server.hostname") : tsHost);

    String bindString = "rmi://" +
      (host == null ? InetAddress.getLocalHost().getHostName() :
       host) +
      portString +
      "/" + this.tsName;

    bind(bindString, doRebind);

    System.out.println(bindString + " bound in registry");
  }

  private static boolean started = false;

  /** Establishes a pair of G2Gateways, one on the server
   * @param the client to receive any callbacks from the server
   * @param host The hostname. If <code>null</code>, then defaults to the
   * host specified in the constructor.
   * @param port the port number. If <code>null</code>, then defaults to the
   * host specified in the constructor.
   * @param the class name of the server class
   * @param forceNew if <code>true</code> the make a new connection even if
   *                an equivalent connection already exists.
   * @see G2RMIAccessBrokerImpl#G2RMIAccessBrokerImpl
   * @undocumented
   */

  @Override
  public G2RMIAccess getOrMakeConnection(G2ConnectionInfo info,
					 RMIEventQueueProcessor clientRep,
					 boolean forceNew)
  throws RemoteException, ConnectionTimedOutException, ClassNotFoundException,
  G2AccessInitiationException {
    Trace.send(10, traceKey, i18nTrace, "g2ragetOrMakeConnection",
	       clientRep);
    G2RMIAccess server = null;
    if (forceNew) {
      System.err.println("G2RMIAcessBrokerImpl: unimplemented method arg, forceNew");
    } else {
      server = (G2RMIAccess)G2Gateway.getOrMakeConnection(info);
    }

    Trace.send(10, traceKey, i18nTrace, "g2ragotServer", server);

    ConnectionResolver.mapStubToWrapper(clientRep, (G2Gateway)server);

    server.addRemoteConnection(clientRep);
    server.setPingFrequency(pingFreq);
    Trace.send(10, traceKey, i18nTrace, "g2raReturnFromGetOrMakeConnection");
    return server;
  }

  private G2ConnectionInfo fillInInfo(G2ConnectionInfo info) {
    String infoHost = info.getHost();
    String infoPort = info.getPort();
    return
      new G2ConnectionInfo(null,
			   info.getLogicalName(),
			   (infoHost == null ? defaultG2Host : infoHost),
			   (infoPort == null ? defaultG2Port : infoPort),
			   info.getConnectionClassName(),
			   info.getGsiInterfaceClassName(),
			   info.getInterfaceName(),
			   info.getProtocol(),
			   info.getPermanent(),
			   info.getRpis());
  }

  /** See the class documentation for an explanation of the command-line
   * arguments.
   */
  public static void main (String[] args) {
    GensymApplication.initialize(args);
    CmdLineArgHandler cmdLine = new CmdLineArgHandler (args);
    String tsPort  = cmdLine.getOptionValue ("-tsPort");
    String tsName  = cmdLine.getOptionValue ("-tsName");
    String g2Host = cmdLine.getOptionValue ("-g2Host");
    String g2Port = cmdLine.getOptionValue ("-g2Port");
    boolean doRebind = cmdLine.getSwitchValue("-doRebind");
    String pingArgument = cmdLine.getOptionValue("-ping");

    tsHost = cmdLine.getOptionValue ("-tsHost");

    String url = cmdLine.getOptionValue("-url");

    G2Gateway.initialize(args);
    if (cmdLine.getSwitchValue ("-setSecurityManager"))
      System.setSecurityManager(new RMISecurityManager());

    boolean debug = cmdLine.getSwitchValue ("-debug");
    if (debug)
      java.rmi.server.RemoteServer.setLog(System.out);
    
    int pingFrequency;

    //pingFrequency of zero or -1 means don't do it.
    //Otherwise a number of seconds to poll.
    if (pingArgument == null)
      pingFrequency = -1;
    else {
      try {
	pingFrequency = Integer.parseInt(pingArgument);
      } catch (java.lang.NumberFormatException e) {
	pingFrequency = -1;
	System.err.println("Unrecognized number: "+pingArgument+".  Ping disabled.");
      }
    }
    if (pingFrequency <=0){
    	pingFrequency = -1;
    }

    try {
      G2RMIAccessBrokerImpl broker = new G2RMIAccessBrokerImpl(tsName, tsPort, g2Host, g2Port, doRebind, pingFrequency);
      broker.debug = debug;
    } catch (Exception ex) {
      Trace.send(3, traceKey, i18nTrace, "Failed to create broker: ", ex.getMessage());
      System.err.println(i18n.format("G2RMIAccessBrokerImpl_errorInitiatingBroker",
				     new Object[] {ex.getMessage(),
						   DebugUtil.printArray(args)}));
      ex.printStackTrace();
      System.exit(-1);
    }

  }

}
