package com.gensym.SocketManager;

// gensym imports
import com.gensym.jgi.*;
import com.gensym.util.*;

// java imports
import java.net.*;
import java.io.*;
import java.util.*;

public class G2OutputThread extends Thread {

  /** Sends data to a socket via <B>writeStr</B>
    * For now the thread is never active, may need this functionality in the future,
    * if writes to a socket block due to a slow network
    */

  volatile boolean isActive = true;
  private G2ClientSocket g2client;

  public G2OutputThread(G2ClientSocket g2client){
    super.setName("Output "+g2client.refID);
    this.g2client = g2client;
    G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Created a client socket output thread for "+g2client.refID);
  }

  public void run(){

    BufferedWriter bufferedOutStream = null;
    try{
      bufferedOutStream = new BufferedWriter(new OutputStreamWriter(g2client.client.getOutputStream(), JavaG2SocketManager.encodingStyle));
    }catch(IOException ioe){
      G2JavaLog.log(G2JavaLog.FATAL_ERROR, "Cannot get output stream for socket "+g2client.client+"\nError = "+ioe.getMessage());
    }

    while(isActive){

      String writeData = g2client.socketWrite.getSendString(); // is there data waiting to be written?
      if(!writeData.equals("")){  // if yes then write to socket
        try{
        //System.out.println ("     Sending data over socket: [" + writeData + "]");
          bufferedOutStream.write(writeData, 0, writeData.length());
          bufferedOutStream.flush();
        }catch(IOException ioe){
        }
      }
      try{
        sleep(200);
      }catch(InterruptedException iee){
        G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Interrupted OUTPUT thread of socket: "+g2client.refID);
      }
    }
   
  }

}
