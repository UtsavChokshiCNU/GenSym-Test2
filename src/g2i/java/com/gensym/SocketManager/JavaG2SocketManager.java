package com.gensym.SocketManager;


//gensym imports
import com.gensym.jgi.*;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.util.*;

//java imports
import java.io.*;
import java.net.*;
import java.lang.reflect.Method;
import java.util.*;

//******************************************************************************

public class JavaG2SocketManager implements G2ConnectionListener {

  /** This class provides a process linked to a G2 application (via a gsi-interface object)
   *  to create and manage network sockets
   *  It defines the G2/Java method calls and methods for handling of server sockets and client sockets
   *  The G2 gateway can only handle one link between G2 and Java at any time, so only one socket
   *  manager interface should be defined in G2 for each of these processes (a socket manager interface
   *  handler is a central resource within G2 for a number of server and client sockets).

   * A server client waits for connections from client sockets, client sockets initiate connections
   * to already opened server sockets.

   * Also supplied are some methods for probing the state of the socket manager interface and individual sockets.
   *
   *
   * This product includes software developed by the
   *        Apache Software Foundation (http://www.apache.org/)
   */

  // static class variables
  private static int port;

  private static String [] allowedCmdLineParams
    = {"-help", "-Help","-port","-Port", "-?", "-debug"};

  G2Connection g2connection;
  volatile String socketIntf;
  static volatile String encodingStyle = new String("UTF8");
  static int MAX_DATA_HOLD = 65536; // maximum number of chars to mainatin for matching possible truncated delimiters

  // Maps for object lookup on sockets
  Map serverSocketsMap = Collections.synchronizedMap(new HashMap());
  Map clientSocketsMap = Collections.synchronizedMap(new HashMap());

  // non-static class variables
  private String cnx_data;

  //constructor
  public JavaG2SocketManager(G2Connection g2connection, String cnx_data) {
    this.g2connection = g2connection;
    this.cnx_data = cnx_data;

    if (cnx_data.equals(new String("-debug"))){
      // debug request from G2 - set debugLevel to log ALL messages to console
      G2JavaLog.debugLevel = G2JavaLog.TROUBLESHOOT;
      G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "TROUBLESHOOT debug level (max) requested by G2");
    }

    registerJavaMethods(g2connection);
    G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Creating a G2 Listener object for this connection");
    g2connection.addG2ConnectionListener(this);
  }


  // Begin implementation method definitions:
  // g2IsPaused, g2IsStarted, g2IsResumed, g2IsReset, g2MessageReceived,
  // communicationError, readBlockage, writeBlockage, g2ConnectionClosed, g2ConnectionInitialized

  public void g2IsPaused(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "G2 is paused - awaiting resume");
  }

  public void g2IsStarted(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "G2 has (re)started - connection established");
  }

  public void g2IsResumed(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION,"G2 has resumed");
  }

  public void g2IsReset(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "G2 has been reset - closing all open sockets & awaiting restart");
    closeAllSockets(); // close sockets
    System.gc(); // garbage collect while process is idle
  }

  public void g2MessageReceived(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Message received from G2: "+ g2e.getMessage());
  }

  public void communicationError(G2CommunicationErrorEvent g2ee){
    G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "G2/Java communication error: "+ g2ee.getMessage());
  }

  public void readBlockage(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Error reading from G2");
  }


  public void writeBlockage(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Error writing to G2");
  }

  public void g2ConnectionClosed(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "G2 connection closed - close sockets");
    closeAllSockets(); // close sockets
    System.gc(); // garbage collect while process is idle
  }

  public void g2ConnectionInitialized(G2ConnectionEvent g2e){
    G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "G2 connection initialized");
    if (G2JavaLog.debugLevel == G2JavaLog.TROUBLESHOOT){
      g2connection.returnMessage("\n Java Socket Manager talking with G2.");
    }
  }

  /** Register java methods called by G2 as RPCs.
    * G2 can manage the sockets remotely through calls to these methods:
    * Create a server socket <B>bCreateServerSocket</B>
    * Create a client socket <B>iCreateClientSocket</B>
    * Close a single sockets <B>bCloseSocket</B>
    * Reset the socket input streams <B>bResetSocketIO</B>
    * Update the socket details <B>bUpdateSocket</B>
    * Write data over a socket <B>bSendDatatoSocket</B>
    *
    * G2 can query the activity of the sockets by:
    * Reporting on all of the socket manager interface object's mapped socket connections <B>sEnumerateSocketMappings</B>
    * Reporting on all of the socket manager interface object's active socket threads  <B>sEnumerateActiveThreads</B>
    * Reporting on an socket's threads <B>sEnumerateSocketConnections</B>
    */

  private void registerJavaMethods(G2Connection g2connection){

    G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Registering JAVA methods for G2 to call as RPCs");

    try{

      // create server socket method
      Method bCreateServerSocketMethod =
        this.getClass().getDeclaredMethod("bCreateServerSocket", new Class[] {String.class, Integer.TYPE, String.class, Sequence.class, Sequence.class});
      g2connection.registerJavaMethod(
        this, bCreateServerSocketMethod, Symbol.intern("_g2-java-socket-create-server-socket-rmt"), true);
      G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Registered create server socket RPC method");

      // create client socket method
      Method iCreateClientSocketMethod =
        this.getClass().getDeclaredMethod("iCreateClientSocket", new Class[] {String.class, String.class, Integer.TYPE, String.class, Sequence.class, Sequence.class});
      g2connection.registerJavaMethod(
        this, iCreateClientSocketMethod, Symbol.intern("_g2-java-socket-create-client-socket-rmt"), true);
      G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Registered create client socket RPC method");

      // close socket method
      Method bCloseSocketMethod =
        this.getClass().getDeclaredMethod("bCloseSocket", new Class[] {String.class});
      g2connection.registerJavaMethod(
        this, bCloseSocketMethod, Symbol.intern("_g2-java-socket-close-socket-rmt"), true);
      G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Registered close socket RPC method");

      // close all sockets
      Method bCloseAllSocketsMethod =
        this.getClass().getDeclaredMethod("bCloseAllSockets", new Class[] {});
      g2connection.registerJavaMethod(
        this, bCloseAllSocketsMethod, Symbol.intern("_g2-java-socket-reset-all-sockets-rmt"), true);
      G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Registered close all sockets RPC method");

      // close reset method
      Method bResetSocketIOMethod =
        this.getClass().getDeclaredMethod("bResetSocketIO", new Class[] {String.class});
      g2connection.registerJavaMethod(
        this, bResetSocketIOMethod, Symbol.intern("_g2-java-socket-reset-socket-io-rmt"), true);
      G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Registered reset socket I/O RPC method");

      // send data to socket method
      Method bSendDatatoSocketMethod =
        this.getClass().getDeclaredMethod("bSendDatatoSocket", new Class[] {String.class, String.class, Sequence.class});
      g2connection.registerJavaMethod(
        this, bSendDatatoSocketMethod, Symbol.intern("_g2-java-socket-send-message-rmt"), true);
      G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Registered send data to socket RPC method");

      // updates to socket attributes method
      Method bUpdateSocketMethod =
        this.getClass().getDeclaredMethod("bUpdateSocket", new Class[] {String.class, Sequence.class});
      g2connection.registerJavaMethod(
        this, bUpdateSocketMethod, Symbol.intern("_g2-java-socket-manager-update-on-the-fly-attributes-rmt"), true);
      G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Registered update socket RPC method");

      // enumeration of the socket mapping objects, called by interface object
      Method sEnumerateSocketMappingsMethod =
        this.getClass().getDeclaredMethod("sEnumerateSocketMappings", new Class[] {});
      g2connection.registerJavaMethod(
        this, sEnumerateSocketMappingsMethod, Symbol.intern("_g2-java-socket-enumerate-mapped-sockets-rmt"), true);
      G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Registered enumerate socket mappings RPC method");

      // enumeration of the active socket threads (connections) called by socket object
      Method sEnumerateSocketConnectionsMethod =
        this.getClass().getDeclaredMethod("sEnumerateSocketConnections", new Class[] {String.class, String.class});
      g2connection.registerJavaMethod(
        this, sEnumerateSocketConnectionsMethod, Symbol.intern("_g2-java-socket-enumerate-active-connections-rmt"), true);
      G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Registered enumerate socket connections RPC method");

      // enumeration of the active threads, called by interface object, lists only i/o threads in G2, lists ALL threads in program for JAVA window
      Method sEnumerateActiveThreadsMethod =
        this.getClass().getDeclaredMethod("sEnumerateActiveThreads", new Class[] {});
      g2connection.registerJavaMethod(
        this, sEnumerateActiveThreadsMethod, Symbol.intern("_g2-java-socket-enumerate-active-threads-rmt"), true);
     G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Registered enumerate active threads RPC method");

     // enumeration of the active client sockets associated with a server socket
      Method sEnumerateActiveServerClientsMethod =
        this.getClass().getDeclaredMethod("sEnumerateActiveServerClients", new Class[] {String.class});
      g2connection.registerJavaMethod(
        this, sEnumerateActiveServerClientsMethod, Symbol.intern("_g2-java-socket-enumerate-active-clients-for-server-rmt"), true);
     G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Registered enumerate client sockets for server socket RPC method");

    }catch(NoSuchMethodException nsme){
      G2JavaLog.log(G2JavaLog.FATAL_ERROR, "Could not find method to register for "+nsme.toString());
    }
  }

  /** The create server and client sockets methods will result in the creation of a standalone
    * java server/client socket object.
    * Each java socket object is associated with an appropriate g2server or g2client socket class.
    *
    * Individual maps of these g2 socket objects will be maintained by this class,
    * The maps provide easy access when the sockets are requested to be updated or closed.
    */

  // Create Server socket
  public boolean bCreateServerSocket(String intf, int port, String refID, Sequence socketAttrs, Sequence msgAttrs){
    G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "In RPC to create SERVER socket for interface: "+intf);

    socketIntf = intf;
    try{    // make the server socket, then initiate socket carer class
      ServerSocket serverSocket = new ServerSocket(port);
      G2ServerSocket g2server = new G2ServerSocket(this, serverSocket, refID, socketAttrs, msgAttrs);
      g2server.initialize();
      Object socketMapping = serverSocketsMap.put(refID, g2server);
      return true;
    }catch(Exception e){
      G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR, "Error trying to open server socket on port: "+port+"\n"+e.getMessage());
      return false;
    }
  }

  // Create client socket
  public int iCreateClientSocket(String intf, String hostServerIP, int port, String refID, Sequence socketAttrs, Sequence msgAttrs){
    G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "In RPC to create CLIENT socket for interface: "+intf);

    socketIntf = intf;
    try{    // make the client socket, then initiate socket carer class
      Socket socket = new Socket(hostServerIP, port);
      G2ClientSocket g2client = new G2ClientSocket(this, null, socket, hostServerIP, port, refID, socketAttrs, msgAttrs);
      g2client.initialize();
      Object socketMapping = clientSocketsMap.put(refID, g2client);
      return g2client.localPort;
    }catch(UnknownHostException uhe){
      G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR,
        "Client socket cannot locate host: "+hostServerIP+" for client socket on port "+port+"\n"+
        "\tError message text = "+uhe.getMessage());
      return -1;
    }catch(IOException ioe){
      G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR,
      "Client socket error connecting to host: "+hostServerIP+" for client socket on port "+port+"\n"+
      "\tError message text = "+ioe.getMessage());
      return -1;
    }
  }

  /** Update socket attributes:
    * a) Message start and end delimiters
    * b) Logging of raw data (as received over socket)
    * c) Logging of filtered data (as passed to G2 depending on message start/end specified
    * d) Strip the message delimiters before sending to G2 or do not strip delimiters.
    */
  public boolean bUpdateSocket(String socketUuid, Sequence attributeSeq){
    G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "In RPC to update socket details for interface: "+socketIntf);

    if(serverSocketsMap.containsKey((Object)socketUuid)){
      try{
        G2ServerSocket g2socket = (G2ServerSocket)serverSocketsMap.get((Object)socketUuid);
        G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Found server socket :"+g2socket);
        g2socket.updateSocketAttributes(attributeSeq);

        int clients = g2socket.serverClients.size();  // do the clients in the hashtable
        G2ClientSocket [] clientSockets = new G2ClientSocket[clients];
        G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Server socket has "+clients+" connected clients to update message delimiters");
        String key;
        G2ClientSocket g2client;
        // read all the clients into an array first, client closes may access hashtable concurrently
        for (int i = 0; i < clients; i++){
          key = (String) g2socket.serverClients.keySet().toArray()[i];
          clientSockets[i] = (G2ClientSocket) g2socket.serverClients.get(key);
        }
        for (int i = 0; i < clients; i++){ // now try to update each one
          g2client = (G2ClientSocket) clientSockets[i];
          if (!(g2client.client == null)) g2client.updateSocketAttributes(attributeSeq);
        }
        return true;
      }catch(Exception e){
        G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR, "Could not update message delimeters :"+e.getMessage());
        return false;
      }
    }
    else if (clientSocketsMap.containsKey((Object)socketUuid)){
      try{
        G2ClientSocket g2client = (G2ClientSocket)clientSocketsMap.get((Object)socketUuid);
        G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Found client socket :"+g2client);
        g2client.updateSocketAttributes(attributeSeq);
        return true;
      }catch(Exception e){
        G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR, "Could not update message delimeters :"+e.getMessage());
        return false;
      }
    }
    G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Could not locate socket with ID "+socketUuid);
    return false;
  }

  // Close an individual socket
  public boolean bCloseSocket(String socketUuid){
    G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "In RPC to close socket with id: "+socketUuid+
    " for interface: "+socketIntf);

    // look for the socket in the server & client maps
    if(serverSocketsMap.containsKey((Object)socketUuid)){
      G2ServerSocket g2server = (G2ServerSocket)serverSocketsMap.get((Object)socketUuid);
      try{
        g2server.closeSocketImpl();
        return true;
      }catch (Exception e){
        G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR, "Problem closing server socket: "+socketUuid+"\nError: "+e.getMessage());
        return false;
      }
    }else if (clientSocketsMap.containsKey((Object)socketUuid)){
      G2ClientSocket g2client = (G2ClientSocket)clientSocketsMap.get((Object)socketUuid);
      try{
        g2client.closeSocketImpl();
        return true;
      }catch (Exception e){
        G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR, "Problem closing client socket: "+socketUuid+"\nError: "+e.getMessage());
        return false;
      }
    }
    G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Could not locate socket with ID "+socketUuid);
    return false;
  }

  public boolean bCloseAllSockets(){
    G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Closing all sockets for interface: "+socketIntf);
    // call closeAllSockets
    closeAllSockets();

    return true;
  }
  /**
    * Allows user to reset the input stream read when changing the message start/end delimiters.
    */

  public boolean bResetSocketIO(String socketUuid){
    G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "In RPC to reset I/O for socket with id: "+socketUuid+
    " for interface: "+socketIntf);

    // look for the socket in the server & client maps
    if(serverSocketsMap.containsKey((Object)socketUuid)){
      G2ServerSocket g2server = (G2ServerSocket)serverSocketsMap.get((Object)socketUuid);

      int clients = g2server.serverClients.size();  // reset i/o for all clients associated with server
      G2ClientSocket [] clientSockets = new G2ClientSocket[clients];
      G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Server socket has "+clients+" connected clients to reset i/o");
      String key;
      G2ClientSocket g2client;
      for (int i = 0; i < clients; i++){  // read all the clients into an array first, client closes may access hashtable concurrently
        key = (String) g2server.serverClients.keySet().toArray()[i];
        clientSockets[i] = (G2ClientSocket) g2server.serverClients.get(key);
      }
      for (int i = 0; i < clients; i++){ // now try to reset i/o for each one
        g2client = (G2ClientSocket) clientSockets[i];
        if (!(g2client.client == null)){
          g2client.socketRead.accumulate = false;
          g2client.socketRead.accumulateData = new String("");
          g2client.socketRead.matchData = new String("");
          G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Reset I/O for client socket of server with id: "+socketUuid);
        }
      }
      return true;

    }else if (clientSocketsMap.containsKey((Object)socketUuid)){
      G2ClientSocket g2client = (G2ClientSocket)clientSocketsMap.get((Object)socketUuid);
      // this will stop any current data passing until next msgStart/msgEnd match received
      g2client.socketRead.accumulate = false;
      g2client.socketRead.accumulateData = new String("");
      g2client.socketRead.matchData = new String("");
      G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Reset I/O for client socket with id: "+socketUuid);
      return true;
    }

    G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Could not locate socket with ID "+socketUuid);
    return false;

  }

  /** Write data specified to the socket with this uuid
    * If this is a server socket, ensure all clients attached receive the data
    * Data is passed in as a sequence of unicode character codes - this is to prevent GSI terminating
    * on the null character. In this method the sequence of unicode chars is converted back to a string
    * to send out over the socket
    */

  public boolean bSendDatatoSocket(String socketUuid, String cnxID, Sequence seqTextCodes){
    if(cnxID.equals("")){
      G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "In RPC to send data to socket with id: "+socketUuid+
      " for interface: "+socketIntf);
    }
    else{
      G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "In RPC to send data to socket with id: "+socketUuid+
      " over connection channel with id: "+cnxID+" for interface: "+socketIntf);
    }

    boolean sendData = true;
    String sText = new String("");
    int seqLength = seqTextCodes.size();
    Object [] textCodes = seqTextCodes.getContents();
    for(int i = 0; i < seqLength ; i++){
      Integer intText = (Integer)textCodes[i];
      char cText = (char) intText.intValue();
      sText = sText + cText;
    }
    G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "String to send over socket "+socketUuid+" is: "+sText);

    // look for this socket
    if(serverSocketsMap.containsKey((Object)socketUuid)){
      G2ServerSocket g2server = (G2ServerSocket)serverSocketsMap.get((Object)socketUuid);

      int clients = g2server.serverClients.size();  // write to all clients associated with server
      G2ClientSocket [] clientSockets = new G2ClientSocket[clients];
      G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Server socket has "+clients+" connected clients to send message ");
      String key;
      G2ClientSocket g2client;
      for (int i = 0; i < clients; i++){  // read all the clients into an array first, client closes may access hashtable concurrently
        key = (String) g2server.serverClients.keySet().toArray()[i];
        clientSockets[i] = (G2ClientSocket) g2server.serverClients.get(key);
      }

      if(!cnxID.equals("")){ // specific connection channel specified
        for (int i = 0; i < clients; i++){ // now find g2client with the cnxID
          g2client = (G2ClientSocket) clientSockets[i];
          if (!(g2client.client == null) && g2client.cnxID.equals(cnxID)){
            g2client.socketWrite.accumulateString(sText);
            sendData = true;
            break;
          }else sendData = false;
        }
      }
      else{  // no connection channel specified
        for (int i = 0; i < clients; i++){ // now try to send the data to each one
          g2client = (G2ClientSocket) clientSockets[i];
          if (!(g2client.client == null)){
            g2client.socketWrite.accumulateString(sText);
            sendData = true;
          } else sendData = false;
        }
      }
      if(!sendData) G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR, "Problems sending data over server socket with id: "+socketUuid);
      return sendData;

    }else if (clientSocketsMap.containsKey((Object)socketUuid)){
      G2ClientSocket g2client = (G2ClientSocket)clientSocketsMap.get((Object)socketUuid);
      if (g2client.socketOut != null){
        g2client.socketWrite.accumulateString(sText);
        sendData = true;
      } else sendData = false;

      if(!sendData) G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR, "Problems sending data over socket with id: "+socketUuid);
      return sendData;
    }
    G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Could not locate socket with ID "+socketUuid);
    return false;

  }

  // Close all open sockets at once
  private void closeAllSockets(){
    G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Closing all sockets for interface: "+socketIntf);

    int j;
    Object socketMapKey;
    String socketUUID = new String("");


    if (!serverSocketsMap.isEmpty()){ // close all Server sockets
      int mapSize = serverSocketsMap.size();
      G2ServerSocket [] g2servers = new G2ServerSocket[mapSize];
      java.util.Set serverSet = serverSocketsMap.keySet();
      Iterator serverIter = serverSet.iterator();
      j=0;
      while(serverIter.hasNext()){ // read all servers into an array first
        socketMapKey = serverIter.next();
        g2servers[j++] = (G2ServerSocket)serverSocketsMap.get(socketMapKey);
      }

      G2ServerSocket g2server;
      for(int i=0; i < mapSize; i++){
        g2server = (G2ServerSocket)g2servers[i];
        try{
          socketUUID = g2server.refID;
          g2server.closeSocketImpl();
        }catch (Exception e){
          G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR,"Problem closing server socket: "+socketUUID+"\nError: "+e.getMessage());
        }
      }
    }

    // close all Client sockets
    if (!clientSocketsMap.isEmpty()){
      int mapSize = clientSocketsMap.size();
      G2ClientSocket [] g2clients = new G2ClientSocket[mapSize];
      java.util.Set clientSet = clientSocketsMap.keySet();
      Iterator clientIter = clientSet.iterator();
      j=0;
      while(clientIter.hasNext()){ // read all clients into an array first
        socketMapKey = clientIter.next();
        g2clients[j++] = (G2ClientSocket)clientSocketsMap.get(socketMapKey);
      }

      G2ClientSocket g2client;
      for(int i=0; i < mapSize; i++){
        g2client = (G2ClientSocket)g2clients[i];
        try{
          socketUUID = g2client.refID;
          g2client.closeSocketImpl();
        }catch (Exception e){
          G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR,"Problem closing client socket: "+socketUUID+"\nError: "+e.getMessage());
        }
      }
    }
    serverSocketsMap.clear();
    clientSocketsMap.clear();
  }

  /** Following two methods return a list of the server and client sockets connected to the
    * socket manager interface in G2, and considered 'open' sockets i.e. live.
    * The map objects are used to return the stored list of open sockets.
    */

  public String enumerateServerSocketMappings(){
    String socketMappings = new String();

    // get mappings for Server sockets
    if (!serverSocketsMap.isEmpty()){
       socketMappings = "Server mappings = ";
       java.util.Set serverSet = serverSocketsMap.keySet();
       Iterator serverIter = serverSet.iterator();
       while(serverIter.hasNext()){
        socketMappings = socketMappings+""+serverIter.next()+",";
      }
    }
    else{
      socketMappings = "No mappings for Server sockets.";
    }
    G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Request for server socket mappings returned: "+socketMappings);
    return socketMappings;
  }

  // Enumerate the existing client socket mappings
  public String enumerateClientSocketMappings(){
    String socketMappings = new String();

    // get mappings for Client sockets
    if (!clientSocketsMap.isEmpty()){
      socketMappings = "Client mappings = ";
      java.util.Set clientSet = clientSocketsMap.keySet();
      Iterator clientIter = clientSet.iterator();
      while(clientIter.hasNext()){
        socketMappings = socketMappings+""+clientIter.next()+",";
      }
    }
    else{
      socketMappings = "No mappings for Client sockets.";
    }
    G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Request for client socket mappings returned: "+socketMappings);
    return socketMappings;
  }

  // Enumerate all mappings
  public String sEnumerateSocketMappings(){
    G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "In RPC to enumerate socket mappings for interface: "+socketIntf);


    String socketMappings = enumerateServerSocketMappings();
    socketMappings = socketMappings+"\n"+enumerateClientSocketMappings();
    return socketMappings;
  }

  /** Following method returns a list of the ACTIVE threads associated with an open socket.
    * A server socket will have a thread listening for connections if it is open
    * All client sockets have two threads associated with their input streams:
    * a) An "input" thread to continously read the input on the socket and place it in a buffer
    * b) A "reader" thread to continously read the buffer populated in (a)
    * c) AN output thread for writing data out over the socket
    */

  public String sEnumerateSocketConnections(String intf, String socketUuid){
    G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "In RPC to enumerate active threads for socket with id: "+socketUuid+" interface: "+socketIntf);

    G2ServerSocket g2server = null;
    G2ClientSocket g2client = null;

    // find socket matching socketUuid
    if(serverSocketsMap.containsKey((Object)socketUuid)){

      g2server = (G2ServerSocket)serverSocketsMap.get((Object)socketUuid);
      G2JavaLog.log(G2JavaLog.TROUBLESHOOT,"Found server socket: "+g2server);
      String returnStr = new String("");
      if (g2server.serverThread.isAlive()) returnStr = "For this server there is:\n One live connection-accept thread";

      String ClientDetails = "";
      int clients = g2server.serverClients.size();  // get any active clients associated with this server socket
      G2ClientSocket [] clientSockets = new G2ClientSocket[clients];
      G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Server socket has "+clients+" connected clients");
      String key;
      for (int i = 0; i < clients; i++){  // read all the clients into an array first, client closes may access hashtable concurrently
        key = (String) g2server.serverClients.keySet().toArray()[i];
        clientSockets[i] = (G2ClientSocket) g2server.serverClients.get(key);
      }
      for (int i = 0; i < clients; i++){ // now try to reset i/o for each one
        g2client = (G2ClientSocket) clientSockets[i];
        if (!(g2client.client == null)){
          if (g2client.socketIn == null || g2client.socketOut == null)
            G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR,"Error, client socket but no client input stream");

          if (g2client.socketIn.isAlive()) ClientDetails = ClientDetails+"\n"+g2client.socketIn+" on socket to host/port: "+g2client.remoteAddress.getHostAddress()+"/"+g2client.remotePort;
          if (g2client.socketRead.isAlive()) ClientDetails = ClientDetails+"\n"+g2client.socketRead+" on socket to host/port: "+g2client.remoteAddress.getHostAddress()+"/"+g2client.remotePort;
          if (g2client.socketOut.isAlive()) ClientDetails = ClientDetails+"\n"+g2client.socketOut+" on socket to host/port: "+g2client.remoteAddress.getHostAddress()+"/"+g2client.remotePort;
          if (g2client.socketWrite.isAlive()) ClientDetails = ClientDetails+"\n"+g2client.socketWrite+" on socket to host/port: "+g2client.remoteAddress.getHostAddress()+"/"+g2client.remotePort;
        }
      }
      
      if (ClientDetails.equals("")) return returnStr;
      else return returnStr+"\nI/O connections :\n"+ClientDetails;

    }else if(clientSocketsMap.containsKey((Object)socketUuid)){
      g2client  = (G2ClientSocket)clientSocketsMap.get((Object)socketUuid);
      G2JavaLog.log(G2JavaLog.TROUBLESHOOT,"Found client socket: "+g2client+"/"+g2client.client);

      String ClientDetails = "";
      if (g2client.socketIn == null || g2client.socketOut == null)
        G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR,"Error, client socket but no client input stream");

      if(g2client.socketIn.isAlive()) ClientDetails = ClientDetails+"\n"+g2client.socketIn+" on socket to host/port: "+g2client.remoteAddress.getHostAddress()+"/"+g2client.remotePort;
      if(g2client.socketRead.isAlive()) ClientDetails = ClientDetails+"\n"+g2client.socketRead+" on socket to host/port: "+g2client.remoteAddress.getHostAddress()+"/"+g2client.remotePort;
      if(g2client.socketOut.isAlive()) ClientDetails = ClientDetails+"\n"+g2client.socketOut+" on socket to host/port: "+g2client.remoteAddress.getHostAddress()+"/"+g2client.remotePort;
      if(g2client.socketWrite.isAlive()) ClientDetails = ClientDetails+"\n"+g2client.socketWrite+" on socket to host/port: "+g2client.remoteAddress.getHostAddress()+"/"+g2client.remotePort;

      if (ClientDetails.equals(""))
        return new String("");
      else
        return "\nI/O connections :\n"+ClientDetails;

    }
    return "Could not find socket as an active mapped socket";
  }

  /** Following method returns a list of the ACTIVE threads associated with a socket manager
    * interface object
    */

  public String[] sEnumerateActiveThreads(){
    G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "In RPC to enumerate active threads for interface: "+socketIntf);

    String[] sActiveThreads = new String[Thread.activeCount()];

    // call static method to return active threads in array
    Thread activeThreads[] = new Thread[Thread.activeCount()];
    int threadCount = Thread.enumerate(activeThreads);
    int j = 0;
    for(int i = 0; i < threadCount; i++){
      if(activeThreads[i].getName().startsWith("Input") ||
        activeThreads[i].getName().startsWith("Read") ||
        activeThreads[i].getName().startsWith("Output") ||
        activeThreads[i].getName().startsWith("Server")){
        sActiveThreads[j++] = activeThreads[i].getName();
        G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Thread "+i+" is "+sActiveThreads[j-1]+"\n"+j);
      }
    }
    return sActiveThreads;

  }

  /** Following method returns a list of the ACTIVE client sockets associated with a server socket
    * interface object
    */

  public String[] sEnumerateActiveServerClients(String socketUuid){
    G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "In RPC to enumerate clients for server with ID: "+socketUuid+" connected to interface: "+socketIntf);

    // find Server socket matching socketUuid
    if(serverSocketsMap.containsKey((Object)socketUuid)){
      G2ServerSocket g2server = (G2ServerSocket)serverSocketsMap.get((Object)socketUuid);
      int clients = g2server.serverClients.size();  // get any active clients associated with this server socket
      if(clients > 0){
        String [] returnClients = new String[clients];
        G2ClientSocket [] clientSockets = new G2ClientSocket[clients];
        G2ClientSocket g2client;
        G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Server socket has "+clients+" connected clients");
        String key;
        for (int i = 0; i < clients; i++){  // read all the clients into an array first, client closes may access hashtable concurrently
         key = (String) g2server.serverClients.keySet().toArray()[i];
         clientSockets[i] = (G2ClientSocket) g2server.serverClients.get(key);
        }
        for (int i = 0; i < clients; i++){ // read uuid & port numbers into an array to return
          g2client = (G2ClientSocket) clientSockets[i];
          returnClients[i] = new String("ID: "+g2client.refID+" local port: "+g2client.localPort+" remote port: "+g2client.remotePort);
        }
        return returnClients;
      }
    }
    G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Unable to find clients for server with ID: "+socketUuid);
    return new String[]{"NULL"};

  }

  private static boolean checkIsValidEncoding(String style)
  {
    try{
      OutputStreamWriter out = new OutputStreamWriter(System.out, style);
      return true;
    }catch(Exception e){
      G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Invalid encoding specified: "+style+"\n"+e.getMessage()
		    +"\nUse one of Cp1252, UTF8, UTF-16, ISO8859_1, ASCII, UnicodeBig, UnicodeLittle etc typed exactly as specified in the JDK documentation on supported encoding"
		    +"\nUsing default encoding style: "+encodingStyle);
      return false;
    }  
  }

  /*
   * Gets the version of JavaLink.
   * (Look at the core.jar->products.dat for the names of the products)
   * If the product cannot be found, an exception of class UnknownProductException is thrown, but that is a private class.
   */
  public static String getJavaLinkVersion(){
    String productName = "javalink";
    String version = "none";
    try{
      com.gensym.core.Product product = com.gensym.core.ProductManager.getProduct(productName);
      if (product != null){
        version = product.getDisplayVersion();
      }
    }
    catch (Exception ex) {
      version = "the product named '"+ productName + "' is unknown";
    }
    return version;
  }

  public static void main(String[] args) {
    System.out.println();
	  System.out.println("+--------------------------------------------------+");
	  System.out.println("|                                                  |");
	  System.out.println("|    G2 Java Socket Manager Bridge                 |");
	  System.out.println("|    " + G2Version.VERSION_INFORMATION + " (Build " + G2Version.BUILD_INFORMATION + ")" + "            |");
	  System.out.println("|                                                  |");
	  System.out.println("|    " + G2Version.COPYRIGHT_INFORMATION + "                  |");
	  System.out.println("|                                                  |");
	  System.out.println("+--------------------------------------------------+");
	  System.out.println("");
	  System.out.println("JavaLink version: " + JavaG2SocketManager.getJavaLinkVersion());
	  System.out.println("");

    //Handle command line parameters - allow fuzzy matches
    CmdLineArgHandler cmds = new CmdLineArgHandler(args, JavaG2SocketManager.allowedCmdLineParams, true);
    // get debug level
    String debugLevelString = cmds.getOptionValue("-debug");
    String setEncodingStyle = cmds.getOptionValue("-encoding");
    if (setEncodingStyle != null){
      boolean isValidEncodingStyle = checkIsValidEncoding(setEncodingStyle);
      if (isValidEncodingStyle) encodingStyle = setEncodingStyle;
    }

    if (debugLevelString == null || debugLevelString.equals("0")) {
    	G2JavaLog.debugLevel = 0;
    } else if (debugLevelString.equals("1")) {
    	G2JavaLog.debugLevel = 1;
    } else if (debugLevelString.equals("2")) {
    	G2JavaLog.debugLevel = 2;
    } else if (debugLevelString.equals("3")) {
    	G2JavaLog.debugLevel = 3;
    } else if (debugLevelString.equals("4")) {
    	G2JavaLog.debugLevel = 4;
    } else if (debugLevelString.equals("5")) {
    	G2JavaLog.debugLevel = 5;
    }

    // request for help
    if (cmds.getSwitchValue("-help") || cmds.getSwitchValue("-Help") ||cmds.getSwitchValue("-?")){
      System.out.println("\nUsage:\t JavaG2SocketManager -port <port number>\n");
      System.exit(1);
    }

    // Initialize the G2 listener
    try{
      port = (int) cmds.getOptionLong(new String("-port"), 22244);
      new java.net.ServerSocket(port).close();
      // static class method call
      G2Gateway.initialize(new String [] {"-listenerport", port+""});
    }
    catch(IOException ioe){
      System.err.println("Error: TCP port "+port+" initialization failed");
      System.exit(1);
    }

    // Deal with unsolicited connection request from G2 through a Cnx Handler Factory object
    G2Gateway.setConnectionHandlerFactory(new G2ConnectionHandlerFactory(){
      // Implementation of the Cnx Handler Factory method
      public G2Connection createG2Connection(String cnx_data){
        G2Gateway g2gateway = new G2Gateway();
        JavaG2SocketManager g2socket = new JavaG2SocketManager(g2gateway, cnx_data);
        return g2gateway;
      }
    });

    // Start Gateway
    G2Gateway.startup();
    G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION,"\nSocket Manager listening for G2 connection on port: "+port+"\nEncoding Style: "+encodingStyle);

  } // end main


} // end Socket Manager class definition


