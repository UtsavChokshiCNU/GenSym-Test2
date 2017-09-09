
package com.gensym.demos.docs.connectivitydemos;

import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.LoginRequest;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2CommunicationException;

public class MyLoginRequest {
  private static TwGateway myConnection; 
  private static LoginRequest myLogin;
  private static Symbol userMode;
  private static final Symbol DEVELOPER_ = Symbol.intern("DEVELOPER");
  private static final Symbol TASHA_ = Symbol.intern("TASHA");

  //Create a connection
  public static void runMyConnection () {	
    try{
      //Establish a connection to G2
      myConnection = (TwGateway)TwGateway.openConnection("localhost", "1112");
      //Create LoginRequest
      myLogin = new LoginRequest(DEVELOPER_, TASHA_, null);
      myConnection.login(myLogin);
      System.out.println("Connected to G2!");
      myConnection.returnMessage("Connected to G2!");
      userMode = myConnection.retrieveUserMode();
      System.out.println(userMode);
    } catch (G2AccessException e){
      e.printStackTrace();
      System.exit (-1);
    }
  }

   //Close the connection
   public static void closeConnection () {
     try{
       myConnection.logout();
       System.out.println("Connection closed!");
     } catch (G2AccessException e) {
       e.printStackTrace();
     }
   }

  // MAIN
  public static void main(String[] args){
    System.out.println("Got to main!");
    runMyConnection(); 
    closeConnection();
    System.out.println ("End of Main!");
    System.exit (0);
  }
}

