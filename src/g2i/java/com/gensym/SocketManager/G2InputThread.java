package com.gensym.SocketManager;

// java imports
import java.net.*;
import java.io.*;
import java.util.*;

public class G2InputThread extends Thread {

  /** Thread class specifically for reading asynchronously received data from a socket.
    * Run method performs a blocking read call which waits for data to appear on the socket.
    * Data appearing on the socket is appended to a synchronized-access string buffer
    * The getResult mehtod is furnished for other threads to perform reads of the buffer, once a read
    * is performed, a new buffer is made available for appends.
    */

  volatile boolean isActive = true;
  private G2ClientSocket g2client;
  private volatile StringBuffer charsRead;

  public G2InputThread(G2ClientSocket g2client) {
    this.g2client = g2client;
    super.setName("Input "+g2client.refID);
    charsRead = new StringBuffer();
    G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Created a client socket input thread for "+g2client.refID);
  }

  public void run(){

    InputStreamReader inStream = null;
    int intChar;
    try{
      inStream = new InputStreamReader(g2client.client.getInputStream(), JavaG2SocketManager.encodingStyle);
    }catch(IOException ioe){
      G2JavaLog.log(G2JavaLog.FATAL_ERROR, "Cannot get input stream reader for socket "+g2client.client);
    }

    // loop performing blocking read call, when char arrives write to synchronized-access buffer
    while(isActive){
      try{
        if (g2client.client.getInputStream() != null){
          intChar = inStream.read();
          if(intChar == -1){ // client socket received end-of-input stream characters
            G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Receiving -1 on input stream, will close this client "+g2client.refID);

	    // wait for data to be read before closing
	    while(isResult()){
	      try{
		G2JavaLog.log(G2JavaLog.TROUBLESHOOT,"Waiting to clear read....");
		sleep(1000);
	      }catch(InterruptedException iee){
		G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Interrupted input thread of socket while waiting to close socket: "+g2client.refID);
	      }
	    }
	    // call to close may come from both ends at once
            synchronized(this){   
	      g2client.closeSocketImpl();
            }
          }else{
            char readChar = (char)intChar;
            appendResult(readChar);
          }
        }
      }catch(IOException ioe){
      }
    }
  }

  public synchronized String getResult(){

    String readString = new String("");
    if (this.isAlive()){
      readString = charsRead.toString();
      charsRead = new StringBuffer();
    }
    return readString;
  }

  public synchronized boolean isResult(){
     String readString = new String("");
     if (this.isAlive()){
      readString = charsRead.toString();
      if (!readString.equals("")) return true;
      else return false;
    }
    return false; 
  }


  private synchronized void appendResult(char c){
    charsRead.append(c);
  }

}
