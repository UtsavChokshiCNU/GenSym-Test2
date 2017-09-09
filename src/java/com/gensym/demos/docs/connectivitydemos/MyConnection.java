package com.gensym.demos.docs.connectivitydemos;

import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2CommunicationException;

public class MyConnection {
  private static TwAccess myConnection; 

  //Create a connection
  public static void runMyConnection () {	
    try{
      //Establish a connection to G2
      myConnection = TwGateway.openConnection("localhost", "1112");
      myConnection.login();
      System.out.println("Connected to G2!");
      myConnection.returnMessage("Connected to G2!");
    } catch (G2AccessException e){
      e.printStackTrace();
      System.exit (-1);
    }
  }

  // MAIN
  public static void main(String[] args){
    System.out.println("Got to main!");
    runMyConnection(); 
    myConnection.closeConnection();
    System.out.println("Connection closed!");
    System.out.println ("End of Main!");
    System.exit (0);
  }
}

