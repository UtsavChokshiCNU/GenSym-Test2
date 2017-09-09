package com.gensym.SocketManager;

import java.net.*;
import java.io.*;
import java.util.*;

public class ServerSocketThread extends Thread {

  /** Thread to wait for client socket connections with each connection accepted it
    * creates a G2ClientSocket instance around an client socket and stores the  G2ClientSocket
    * in the G2ServerSocket hashtable for easy access on socket updates/closings.
    */

  volatile boolean isActive = true;
  G2ServerSocket g2server;

  public ServerSocketThread(G2ServerSocket g2server) {
    this.g2server = g2server;
    super.setName("Server socket "+g2server.refID);
    G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Created a server socket accept thread for "+g2server.refID);
  }

  public void run(){
    while(isActive){
      try{  // wait for a client connection - blocking call
        Socket client = g2server.server.accept();

        // create a socket carer class, this will take care of I/O for this client
        G2ClientSocket g2client = new G2ClientSocket(g2server.socketManager, g2server, client, g2server.localAddress.getHostAddress(), g2server.localPort, g2server.refID, g2server.socketSeq, g2server.attrSeq);
        g2client.initialize();

        // store client socket in server hashtable for future socket manipulation
        String key = g2client.hashCode() +"";
        synchronized(this){
          g2server.serverClients.put(key, g2client);
        }

        G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Got connection on server port: "+g2server.localPort+" from client host/port: "+g2client.remoteAddress.getHostAddress()+"/"+g2client.remotePort);

      }catch(InterruptedIOException iioe){ // if there are no clients associated with this server then stop mthe accept thread and close the server socket
        if (g2server.serverClients.isEmpty()){
          isActive = false;
          g2server.closeSocketImpl();
          G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION,"Server accept timeout, closing server socket: "+g2server.localPort+
          "\n"+iioe.getMessage());
        }
      }catch(IOException ioe){
        G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Server socket not accepting connections at port: "+g2server.localPort+
        "\n"+ioe.getMessage());
      }catch(Exception e){
        G2JavaLog.log(G2JavaLog.NON_FATAL_ERROR,"Exception for server socket at port: "+g2server.localPort+
        "\n"+e.getMessage());
      }
    }
    G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Exiting run of server thread");
  }

}
