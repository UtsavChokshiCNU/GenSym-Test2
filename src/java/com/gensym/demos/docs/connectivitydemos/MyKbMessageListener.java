package com.gensym.demos.docs.connectivitydemos;

import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwAccess;
import com.gensym.classes.Kb;
import com.gensym.ntw.util.KbMessageListener;
import com.gensym.ntw.util.KbEvent;

public class MyKbMessageListener implements KbMessageListener {
  private static TwAccess myConnection; 

  //Variable for KB
  private static Kb myKb;

  private MyKbMessageListener () {
    //Get KB associated with connection
    Kb myKb = myConnection.getKb();
    try {
      //Add KB as a listener for module events
      myKb.addKbMessageListener(this);
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  public static void runMyConnection () {	
    try{
      myConnection = TwGateway.openConnection ("localhost", "1112");
      myConnection.login();
    } catch (Exception e){
      e.printStackTrace();
    }
  }

  //KbMessageListener Methods

  @Override
  public void receivedInitialContents(KbEvent e) {
    //Invoked when KbMessageListener added
    System.out.println ("Received initial contents!");  
  }

  @Override
  public void kbMessageAdded (KbEvent e) {}
  @Override
  public void kbMessageDeleted (KbEvent e) {}

  public static void main(String[] args){
    System.out.println("Got to main!");
    runMyConnection(); 
    MyKbMessageListener app = new MyKbMessageListener();
    myConnection.closeConnection();
    System.out.println ("Connection closed!");
    System.out.println ("End of Main!");
    System.exit (0);
  }
}

