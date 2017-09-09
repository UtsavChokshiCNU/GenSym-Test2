package com.gensym.SocketManager;

import java.io.IOException;
// java imports
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketException;

import com.gensym.util.Sequence;
import com.gensym.util.Symbol;

public class G2ClientSocket {

  /** Class created for each client socket connection
    * Carries attributes necessary for handling data over the socket
    * Initiates the I/O threads for data via <B>initialize</B>
    * Takes care of closing the socket and associated threads also <B>closeSocketImpl</B>
    */

  // symbols for G2 procedures which may be called by Java
  static Symbol socketCnxEstablishedRPC = Symbol.intern("_G2-JAVA-SOCKET-CONNECTION-ESTABLISHED-RPC");
  static Symbol socketCnxBrokenRPC = Symbol.intern("_G2-JAVA-SOCKET-CONNECTION-BROKEN-RPC");

  Socket client;                          // JAVA socket
  JavaG2SocketManager socketManager;      // Reference to socketManager owned this client-socket
  G2ServerSocket g2server;                // G2 server socket associated with this  G2 client, if any
  String refID;                           // the reference id in G2 for this socket
  String cnxID;                           // the reference id for the connection channel of this client socket
  int localPort,remotePort;               // the local & remote port numbers of the socket
  InetAddress remoteAddress,localAddress; // the inet and local addresses of the socket
  volatile String msgStart = new String(".");  // message start delimiter
  volatile String msgEnd = new String("");   // message end delimiter
  int rcvBufferLength, sndBufferLength;   // size of send/receive buffers
  volatile boolean startCaseInSensitive, startMultiLine, startIsExtendedMask;
  volatile boolean endCaseInSensitive, endMultiLine, endIsExtendedMask;
  volatile boolean stripDelimiters, logRawSocketData, logFilteredSocketData;
  private int receiveBuffer, sendBuffer;

  // Default socket attributes, may or may not be supported depending on platform
  boolean TCPNoDelay;   // If true send data as soon as it is ready
  int SOLinger;         // Allow this amount of ms when socket closes to send outstanding data
  int SOTimeout;        // Block on read for this amount of ms
  int SORxBufferSize;   // Receive input buffer size
  int SOSndBufferSize;  // Send output buffer size
  boolean SOKeepAlive;  // client sends heartbeat to server if idle c. every 2 hrs,
                        // will close connection after c.12 mins of no response

  G2InputThread socketIn;     // Input thread - puts data in buffer
  G2ReadThread socketRead;    // Read input thread - reads buffer
  G2OutputThread socketOut;   // Output thread - writes data from buffer over socket
  G2WriteThread socketWrite;  // Write output thread - writes data to a buffer



  public G2ClientSocket(JavaG2SocketManager socketManager, G2ServerSocket g2server, Socket client, String hostServerIP, int port, String refID, Sequence socketSeq, Sequence attrSeq) {
    this.socketManager = socketManager;
    this.g2server = g2server;
    this.client = client;
    this.refID = refID;
    this.socketIn = new G2InputThread(this);
    this.socketRead = new G2ReadThread(this);
    this.socketOut = new G2OutputThread(this);
    this.socketWrite = new G2WriteThread(this);
    this.updateSocketSettings(socketSeq);
    this.updateSocketAttributes(attrSeq);
    this.localPort = client.getLocalPort();         // local port & host address
    this.localAddress = client.getLocalAddress();
    this.remoteAddress = client.getInetAddress();   // remote port & host address
    this.remotePort = client.getPort();
    G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Created a G2 client socket on local port "+localPort+" to remote port "+remotePort+ " with ID: "+refID);
  }

  public void initialize(){

    try{        // Get some socket housekeeping data
      SOLinger = client.getSoLinger();
      TCPNoDelay = client.getTcpNoDelay();
      SOTimeout = client.getSoTimeout();
      receiveBuffer = client.getReceiveBufferSize();
      sendBuffer = client.getSendBufferSize();
    }catch(SocketException se){
      G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Problem getting client socket details "+client);
    }

    try{        // Set some socket housekeeping data
      if(rcvBufferLength > 0 && receiveBuffer > 0){
        client.setReceiveBufferSize(rcvBufferLength);
        G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Set receive buffer size to: "+rcvBufferLength+" from default size of: "+receiveBuffer);
      }
      if(sndBufferLength > 0 && sendBuffer > 0){
        client.setSendBufferSize(sndBufferLength);
        G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Set send buffer size to: "+sndBufferLength+" from default size of: "+sendBuffer);
      }
    }catch(SocketException se){
      G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Problem setting client socket send/receive size for client"+client+
      "\nDesired rcv/snd settings: "+rcvBufferLength+"/"+sndBufferLength);
    }catch(Exception e){
    }

    String printMsgStart, printMsgEnd;
    if(msgStart.equals("")) printMsgStart = "none specified";
    else printMsgStart = msgStart;
    if(msgEnd.equals("")) printMsgEnd = "none specified";
    else printMsgEnd = msgEnd;

    try{      // initialize connection object on G2 side
      cnxID = (String) socketManager.g2connection.callRPC(socketCnxEstablishedRPC, new Object[] {socketManager.socketIntf, refID, localPort, localAddress.getHostAddress(), remotePort, remoteAddress.getHostAddress()}, 10000);
      G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Created client socket/g2 connection channel with id: "+cnxID);
    }catch(Exception e){
      G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Error while trying to reach G2: "+e.getMessage());
    }

    // start i/o threads for this connection
    socketIn.start();
    socketRead.start();
    socketOut.start();
    socketWrite.start();

    G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Created & started input/read and output/write threads: \n"+socketIn+"\n"+socketRead+"\n"+socketOut+"\n"+socketWrite);
  }

  public void updateSocketSettings(Sequence attributeSeq) {

    Object [] attributeObjects = attributeSeq.getContents();
    Integer setRcvBuffer = (Integer)attributeObjects[0];
    if(setRcvBuffer.intValue() > 0) rcvBufferLength = setRcvBuffer.intValue();
    Integer setSndBuffer = (Integer)attributeObjects[1];
    if(setSndBuffer.intValue() > 0) sndBufferLength = setSndBuffer.intValue();
    Boolean keepAlive = (Boolean) attributeObjects[2];
    if (keepAlive) {
      G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Enable keep-alive for socket: " + refID);
      try {
        client.setKeepAlive(true);
      } catch (SocketException e) {
        G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Failed to enable keep-alive for socket " + refID + "\nError: " + e.getMessage());
      }
    }
    G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Set socket (id= " + refID + ") attributes as:" +
      "\nReceive buffer length = " + rcvBufferLength +
      "\nSend buffer length = " + sndBufferLength +
      "\nKeep-Alive = " + keepAlive);
  }

  public void updateSocketAttributes(Sequence attributeSeq){

    Object [] attributeObjects = attributeSeq.getContents();
    String startMsg = (String) attributeObjects[0];
    if(startMsg.equals("")){
      startMsg = new String(".");
      G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Cannot have the start delimiter as a null string - restting to '.' - any non-newline character");
    }
    if (!msgStart.equals(startMsg)){ // reset the accept character stream
      socketRead.accumulate = false;
      socketRead.accumulateData = new String("");
      socketRead.matchData = new String("");
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
    G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "For client socket (id= "+refID+").\nSet message start delimiter detail as:"+
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

  private boolean booleanTranslate(Object translateObj){

    if(((String)translateObj).equals("false")) return false;
    else return true;

  }

  public void closeSocketImpl(){

    try{      // close the socket i/o, further reads should return -1 (end of stream indicator)
      client.shutdownInput();
      client.shutdownOutput();

      socketIn.isActive = false;          // stop the threads
      socketRead.isActive = false;
      socketOut.isActive = false;
      socketWrite.isActive = false;
      try{
        socketOut.join();
        socketRead.join();
      }catch(Exception e){
         G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR,"Interrupted wait on threads to stop");
      }
      socketIn = null;
      socketOut = null;
      socketRead = null;

      if (!(client == null)){ // may have closed already due to a read of -1 from i/o
        client.close();
        if (!(g2server == null)) removeServerAssociation(); // this is a client socket associated with a server in G2
        else socketManager.clientSocketsMap.remove((Object)refID); // this is a standalone client, remove it from the client sockets Map
        client = null;

        try{      // close the socket connection channel on G2 side
          String closeCnx = (String) socketManager.g2connection.callRPC(socketCnxBrokenRPC, new Object[] {socketManager.socketIntf, refID, cnxID}, 10000);
          if (closeCnx.equals("Closed")) G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "Closed client socket/g2 connection channel with id: "+cnxID);
          else G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR, "Error trying to close client socket/g2 connection channel with id: "+cnxID);
        }catch(Exception e){
         G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR, "Error while trying to reach G2");
        }
      G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Closed client socket with id: "+refID);
      }
    }catch(IOException ioe){
      G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Error closing client socket "+client+"\nError: "+ioe.getMessage());
    }
  }

  private void removeServerAssociation(){

    int clients = g2server.serverClients.size();
    G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Removing closed client "+refID+" from client hashtable of server socket: "+g2server.refID);
    G2ClientSocket g2client;
    String key;
    for (int i = 0; i < clients; i++){
      key = (String) g2server.serverClients.keySet().toArray()[i];
      g2client = (G2ClientSocket) g2server.serverClients.get(key);
      if (refID.equals(g2client.refID)) {
        g2server.serverClients.remove((Object)key);
        break;
      }
    }
    if(g2server.serverClients.size() == 0 && !g2server.serverThread.isAlive()){
      // if this a server with no more connections and no active accept thread then close it
      G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Closing server socket with id: "+g2server.refID+
      "- accept thread is inactive and the last live client: "+refID+" just closed");
      g2server.closeSocketImpl();
    }

  }


}
