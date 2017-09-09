package com.gensym.demos.docs.connectivitydemos;

import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Sequence;
import com.gensym.jgi.G2AccessException;

public class MyWorkspaces {
  private static TwAccess myConnection; 

  //Variable for workspaces
  private static Sequence workspaces;

  public static void runMyConnection () {	
    try{
      myConnection = TwGateway.openConnection ("localhost", "1112");
      myConnection.login();
    } catch (Exception e){
      e.printStackTrace();
    }
  }

  public static void getNamedWorkspaces() {
    try {
      //Get named workspaces from connection
      workspaces = myConnection.getNamedWorkspaces();
      System.out.println (workspaces);  
    } catch (G2AccessException e){
      e.printStackTrace();
    }
  }

  public static void main(String[] args){
    System.out.println("Got to main!");
    runMyConnection(); 
    getNamedWorkspaces();
    myConnection.closeConnection();
    System.out.println ("Connection closed!");
    System.out.println ("End of Main!");
    System.exit (0);
  }
}

