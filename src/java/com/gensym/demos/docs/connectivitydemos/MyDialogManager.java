package com.gensym.demos.docs.connectivitydemos;

import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwAccess;
import com.gensym.dlgruntime.DialogManager;

public class MyDialogManager {
  private static TwAccess myConnection; 

  //Variable for DialogManager
  private static DialogManager dialogManager;

  public static void runMyConnection () {	
    try{
      myConnection = TwGateway.openConnection ("localhost", "1112");
      myConnection.login();
    } catch (Exception e){
      e.printStackTrace();
    }
  }

  public static void getDialogManager () {
    //Get DialogManager
    dialogManager = myConnection.getDialogManager();
    System.out.println (dialogManager);  
  }

  public static void main(String[] args){
    System.out.println("Got to main!");
    runMyConnection(); 
    getDialogManager ();
    myConnection.closeConnection();
    System.out.println ("Connection closed!");
    System.out.println ("End of Main!");
    System.exit (0);
  }
}

