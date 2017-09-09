package com.gensym.demos.docs.connectivitydemos;

import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.LoginRequest;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2CommunicationException;
import com.gensym.util.Symbol;

public class MyNonSecureLoginRequest {
  private static TwAccess myConnection;
  private static LoginRequest loginRequest;
  private static final Symbol DEVELOPER_ = Symbol.intern("DEVELOPER");
  private static final Symbol TASHA_ = Symbol.intern("TASHA"); 

  //Create a connection
  public static void runMyConnection () {	
    try{
      //Establish a connection to G2
      myConnection = TwGateway.openConnection("localhost", "1112");
      //Create a LoginRequest with user mode and user name only
      loginRequest = new LoginRequest(DEVELOPER_, TASHA_, null);
      //Log on to non-secure G2 with LoginRequest
      myConnection.login(loginRequest);
      System.out.println("Connected to G2!");
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

