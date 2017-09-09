package com.gensym.demos.docs.connectivitydemos;

import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwAccess;
import com.gensym.classes.Kb;
import com.gensym.ntw.util.KbModuleListener;
import com.gensym.ntw.util.KbEvent;

public class MyKbModuleListener implements KbModuleListener {
  private static TwAccess myConnection; 

  //Variable for KB
  private static Kb myKb;

  private MyKbModuleListener () {
    //Get KB associated with connection
    Kb myKb = myConnection.getKb(); 
    try {
      //Add KB as a listener for module events
      myKb.addKbModuleListener(this);
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

  //KbModuleListener Methods

  @Override
  public void receivedInitialModules(KbEvent e) {
    //Invoked when KbModuleListener added
    System.out.println ("Received initial modules!");  
  }

  @Override
  public void kbCleared (KbEvent e) {}
  @Override
  public void moduleCreated(KbEvent e) {}
  @Override
  public void moduleDeleted(KbEvent e) {}
  @Override
  public void moduleDependencyChanged(KbEvent e) {}
  @Override
  public void moduleNameChanged(KbEvent e) {}
  @Override
  public void topLevelWorkspaceAdded(KbEvent e) {}
  @Override
  public void topLevelWorkspaceDeleted(KbEvent e) {}

  public static void main(String[] args){
    System.out.println("Got to main!");
    runMyConnection(); 
    MyKbModuleListener app = new MyKbModuleListener();
    myConnection.closeConnection();
    System.out.println ("Connection closed!");
    System.out.println ("End of Main!");
    System.exit (0);
  }
}

