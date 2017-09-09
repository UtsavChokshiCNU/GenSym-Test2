package com.gensym.SocketManager;

// gensym imports
import com.gensym.jgi.*;
import com.gensym.util.*;

// java imports
import java.net.*;
import java.io.*;
import java.util.*;

public class G2WriteThread extends Thread {

  /** Puts data to be written over socket into a buffer
    *
    */

  volatile boolean isActive = true;
  private OutputStreamWriter outStream;
  private G2ClientSocket g2client;
  private volatile StringBuffer sendBuffer;
  private volatile StringBuffer accumulateBuffer;

  public G2WriteThread(G2ClientSocket g2client){
    super.setName("Output write "+g2client.refID);
    sendBuffer = new StringBuffer();
    accumulateBuffer = new StringBuffer();
    this.g2client = g2client;
    G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, "Created a client socket output write thread for "+g2client.refID);
  }


  public void run(){
   while(isActive){
    try{
      String dataReady = getAccumulatedString();
      appendSend(dataReady);
      sleep(200);
    }catch(InterruptedException iee){
      G2JavaLog.log(G2JavaLog.TROUBLESHOOT, "Interrupted WRITE thread of socket: "+g2client.refID);
    }
   }
  }

  /** Two methods below called by output thread to write data over socket -
    * accumulated data is reset once socket accepts it
    */

  public synchronized String getSendString(){

    String sendData = sendBuffer.toString();  // take whatever is in buffer
    sendBuffer = new StringBuffer();          // reinitialize buffer
    return sendData;                          // send data

  }

  public synchronized void appendSend(String sendIt){
    sendBuffer.append(sendIt); // append data to current SEND buffer
  }


  /** Methods below called by main process to write data over socket -
    * data is accumulated until socket is ready to accept it
    */

  public synchronized void accumulateString(String writeIt){
    accumulateBuffer.append(writeIt);
  }

  public synchronized String getAccumulatedString(){

    String accumulateData = accumulateBuffer.toString();  // take whatever is in accumulate buffer
    accumulateBuffer = new StringBuffer();           // reinitialize buffer
    return accumulateData;

  }

}