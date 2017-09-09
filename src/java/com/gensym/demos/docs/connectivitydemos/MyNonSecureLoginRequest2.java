package com.gensym.demos.docs.connectivitydemos;

import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.LoginRequest;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2CommunicationException;
import com.gensym.util.Symbol;

public class MyNonSecureLoginRequest2 {
  private static TwGateway myConnection;
  private static LoginRequest loginRequest;
  private static final Symbol DEVELOPER_ = Symbol.intern("DEVELOPER");
  private static final Symbol KANTI_ = Symbol.intern("TASHA"); 
  private static final Symbol JOHN_ = Symbol.intern("KANTI"); 

  //Create a connection
  public static void createConnection () {
    try{
      //Establish a connection to G2
      myConnection = (TwGateway)TwGateway.openConnection("localhost", "1112");
      System.out.println ("Connection created!");
    } catch (G2AccessException e){
      e.printStackTrace();
    }
  }

  public static void loginKanti () {
    try {
      //Create a LoginRequest with user mode and user name only
      loginRequest = new LoginRequest(DEVELOPER_, KANTI_, null);
      //Log on to non-secure G2 with LoginRequest
      myConnection.login(loginRequest);
      System.out.println("Logged in as Kanti!");
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  public static void loginJohn () {
    try {
      //Create a LoginRequest with user mode and user name only
      loginRequest = new LoginRequest(DEVELOPER_, JOHN_, null);
      //Log on to non-secure G2 with LoginRequest
      myConnection.login(loginRequest);
      System.out.println("Logged in as John!");
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  public static void logoutUser () {
    try {
      //Logout currently logged in user
      myConnection.logout();
      System.out.println ("Current user logged off!");
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
      
  // MAIN
  public static void main(String[] args){
    System.out.println("Got to main!");
    createConnection ();
    loginKanti();
    logoutUser ();
    loginJohn();
    myConnection.closeConnection();
    System.out.println("Connection closed!");
    System.out.println ("End of Main!");
    System.exit (0);
  }
}

