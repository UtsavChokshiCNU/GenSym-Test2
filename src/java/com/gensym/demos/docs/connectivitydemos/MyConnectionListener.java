package com.gensym.demos.docs.connectivitydemos;

import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnectionListener;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.jgi.G2CommunicationErrorEvent;
import com.gensym.jgi.G2ConnectionEvent;

public class MyConnectionListener implements TwConnectionListener {
  private static TwAccess myConnection; 

  public MyConnectionListener () {
    //Add connection as a listener for connection events
    myConnection.addTwConnectionListener(this);
    System.out.println ("Added as listener!");  
  }

  public static void openConnection () {	
    try{
      myConnection = TwGateway.openConnection ("localhost", "1112");
    } catch (Exception e){
      e.printStackTrace();
    }
  }

  public static void loginConnection () {	
    try{
      myConnection.login();
    } catch (Exception e){
      e.printStackTrace();
    }
  }

  //TwConnectionListener Methods
  @Override
  public void loggedIn (TwConnectionEvent e){
    System.out.println ("Logged in event detected!");
  }

  @Override
  public void loggedOut (TwConnectionEvent e) {}
  @Override
  public void userModeChanged (TwConnectionEvent e) {}

  //G2ConnectionListener Methods
  @Override
  public void communicationError(G2CommunicationErrorEvent e){}
  @Override
  public void g2ConnectionClosed(G2ConnectionEvent e) {
    System.out.println ("Connection closed!");
  }
  @Override
  public void g2ConnectionInitialized(G2ConnectionEvent e) {}
  @Override
  public void g2IsPaused(G2ConnectionEvent e) {}  
  @Override
  public void g2IsReset(G2ConnectionEvent e) {}
  @Override
  public void g2IsResumed(G2ConnectionEvent e) {}
  @Override
  public void g2IsStarted(G2ConnectionEvent e) {}
  @Override
  public void g2MessageReceived(G2ConnectionEvent e) {}
  @Override
  public void readBlockage(G2ConnectionEvent e) {}
  @Override
  public void writeBlockage(G2ConnectionEvent e) {}

  public static void main(String[] args){
    System.out.println("Got to main!");
    openConnection(); 
    MyConnectionListener app = new MyConnectionListener();
    loginConnection();
    myConnection.closeConnection();
    System.out.println ("End of Main!");
    System.exit (0);
  }
}

