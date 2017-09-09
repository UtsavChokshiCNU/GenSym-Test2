package com.gensym.SocketManager;

// gensym imports
import com.gensym.jgi.*;
import com.gensym.util.*;

// java imports
import java.net.*;
import java.io.*;
import java.util.*;

public class G2ServerSocket {

  /** Class associated with each live server socket
    * Creates a thread which has a blocking call to accept connections solicited by client sockets
    */

  // symbols for G2 procedures which may be called by Java
  static Symbol g2ServerSocketClose = Symbol.intern("_G2-JAVA-EXPLICIT-CLOSE-SERVER-SOCKET-RPC");

  ServerSocket server;                  // the JAVA server object
  JavaG2SocketManager socketManager;    // socketManager that owned this server-socket
  String refID;                         // the reference id in G2 for this socket
  int localPort;                        // the local port number of the socket
  InetAddress localAddress;             // the local address of the socket
  int SOTimeout = 0;                    // wait forever to accept connections
  int rcvBufferLength, sndBufferLength; // size of send/receive buffers of clients associated with this server
  volatile String msgStart = new String(".");  // message start delimiter
  volatile String msgEnd = new String("");   // message end delimiter
  volatile boolean startCaseInSensitive, startMultiLine, startIsExtendedMask;
  volatile boolean endCaseInSensitive, endMultiLine, endIsExtendedMask;
  volatile boolean stripDelimiters, logRawSocketData, logFilteredSocketData;
  ServerSocketThread serverThread;
  Sequence attrSeq, socketSeq;

  Hashtable serverClients = new Hashtable();


  public G2ServerSocket(JavaG2SocketManager socketManager, ServerSocket server, String refID, Sequence socketSeq, Sequence attrSeq) {
    this.socketManager = socketManager;
    this.server = server;
    this.refID = refID;
    this.socketSeq = socketSeq;
    this.attrSeq = attrSeq;
    this.localPort = server.getLocalPort();
    this.localAddress = server.getInetAddress();
    this.updateSocketSettings(socketSeq);
    this.updateSocketAttributes(attrSeq);
    G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Created a G2 server socket on port "+localPort+" with ID: "+refID);
  }

  public void initialize(){

    try{
      this.server.setSoTimeout(SOTimeout);
    }catch(SocketException se){
      G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Could not set server socket SOTimeout: "+se.getMessage());
    }

    String printMsgStart, printMsgEnd;
    if(msgStart.equals("")) printMsgStart = "none specified";
    else printMsgStart = msgStart;
    if(msgEnd.equals("")) printMsgEnd = "none specified";
    else printMsgEnd = msgEnd;
    serverThread = new ServerSocketThread(this);
    serverThread.start();   // thread to wait for client connections
  }

  public void updateSocketSettings(Sequence attributeSeq){

    Object [] attributeObjects = attributeSeq.getContents();
    Integer setRcvBuffer = (Integer)attributeObjects[0];
    if(setRcvBuffer.intValue() > 0) rcvBufferLength = setRcvBuffer.intValue();
    Integer setSndBuffer = (Integer)attributeObjects[1];
    if(setSndBuffer.intValue() > 0) sndBufferLength = setSndBuffer.intValue();
    Integer setSOTimeout = (Integer)attributeObjects[3];
    if(setSOTimeout.intValue() < 0) SOTimeout = 0;
    else SOTimeout = setSOTimeout.intValue();
    G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION,"Set socket (id= "+refID+") attributes as:\n"+
    "SOTimeout = "+SOTimeout+
    "\nReceive buffer length = "+rcvBufferLength+
    "\nSend buffer length = "+sndBufferLength);
  }

  public void updateSocketAttributes(Sequence attributeSeq){

    Object [] attributeObjects = attributeSeq.getContents();
    String startMsg = (String) attributeObjects[0];
    if(startMsg.equals("")){
      startMsg = new String(".");
      G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Cannot have the start delimiter as a null string - restting to '.' - any non-newline character");
    }
    G2PerlRegexParser parser = new G2PerlRegexParser();
    if(parser.isValidPattern(startMsg)) msgStart = startMsg;
    startCaseInSensitive = booleanTranslate(attributeObjects[1].toString());
    startMultiLine = booleanTranslate(attributeObjects[2].toString());
    startIsExtendedMask = booleanTranslate(attributeObjects[3].toString());
    String endMsg = (String) attributeObjects[4];
    if(parser.isValidPattern(endMsg)) msgEnd = endMsg;
    endCaseInSensitive = booleanTranslate(attributeObjects[5].toString());
    endMultiLine = booleanTranslate(attributeObjects[6].toString());
    endIsExtendedMask = booleanTranslate(attributeObjects[7].toString());
    stripDelimiters = booleanTranslate(attributeObjects[8].toString());
    logRawSocketData = booleanTranslate(attributeObjects[9].toString());
    logFilteredSocketData = booleanTranslate(attributeObjects[10].toString());


    if (endMsg.equals("")) endMsg = new String("Null String");
    G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "For server socket (id= "+refID+").\nSet message start delimiter detail as:"+
    "\nStart filter= "+msgStart+
    "\nCase-InSensitive= "+startCaseInSensitive+
    "\nIs Multiline= "+startMultiLine+
    "\nIs Extended-Mask= "+startIsExtendedMask+
    "\nSet message end delimiter detail as: "+
    "\nEnd filter= "+msgEnd+
    "\nCase-InSensitive= "+endCaseInSensitive+
    "\nIs Multiline= "+endMultiLine+
    "\nIs Extended-Mask= "+endIsExtendedMask+
    "\nFor client socket with uuid: "+refID+
    "\nWith strip delimiters = "+stripDelimiters+
    "\nRaw logging is: "+logRawSocketData+
    "\nFiltered logging is :"+logFilteredSocketData);

  }

  private boolean booleanTranslate(String translateObj){
    if(translateObj.equals("false")) return false;
    else return true;

  }

  public void closeSocketImpl(){

    try{
      // close any client sockets associated with this server socket
      int clients = serverClients.size();
      G2ClientSocket [] clientSockets = new G2ClientSocket[clients];
      G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Closing "+clients+" client sockets associated with this server "+refID);
      String key;
      // read all the clients into an array first, client closes may access hashtable concurrently
      for (int i = 0; i < clients; i++){
        key = (String) serverClients.keySet().toArray()[i];
        clientSockets[i] = (G2ClientSocket) serverClients.get(key);
      }
      // now try to close each one
      for (int i = 0; i < clients; i++){
        G2ClientSocket g2client = (G2ClientSocket) clientSockets[i];
        G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Server: "+g2client.g2server.refID+" now closing client: "+g2client.refID);
        if (!(g2client.client == null)) g2client.closeSocketImpl();
      }

      serverThread.isActive = false;  // ensure run method of associated server thread stops
      serverThread = null;

      if (!(server == null)){  // close this server socket if this has not already been done
        server.close();
        server = null;
        socketManager.serverSocketsMap.remove((Object)refID);
      }

      try{
        socketManager.g2connection.callRPC(g2ServerSocketClose, new Object[] { socketManager.socketIntf, refID }, 10000);
      }catch(G2AccessException gae){
        G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Cannot send close Server socket command to G2\n");
      }

      G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Closed server socket: "+refID);
    }catch(IOException ioe){
      G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR, "Error closing server socket: "+refID);
    }
  }

}
