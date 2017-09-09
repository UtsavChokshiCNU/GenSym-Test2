package com.gensym.demos.docs.connectivitydemos;

import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwAccess;
import com.gensym.classes.UserMenuChoice;
import com.gensym.util.Symbol;
import com.gensym.classes.Item;

public class MyUserMenuChoice {
  private static TwAccess myConnection; 

  //Variable for UserMenuChoice
  private static UserMenuChoice userMenuChoice;

  //Variable for user menu choice label
  private static final Symbol COMPUTE_ORBIT_ = Symbol.intern("COMPUTE-ORBIT");

  //Variable for user menu choice applicable class
  private static final Symbol PLANET_ = Symbol.intern("PLANET");

  //Variable for Planet item as a symbol
  private static final Symbol MY_PLANET_ = Symbol.intern("MY-PLANET");
  
  //Variable for Planet item
  private static Item myPlanet;

 public static void runMyConnection () {	
    try{
      myConnection = TwGateway.openConnection ("localhost", "1112");
      myConnection.login();
    } catch (Exception e){
      e.printStackTrace();
    }
 }

  public static void runUserMenuChoice () {
    try{
      //Get UserMenuChoice
      userMenuChoice = myConnection.getUserMenuChoice(COMPUTE_ORBIT_, PLANET_);
      System.out.println ("Got user menu choice!");

      //Get Planet item
      myPlanet = myConnection.getUniqueNamedItem(PLANET_, MY_PLANET_);
      System.out.println ("Got unique named item!");

       //Invoke user menu choice on item
      userMenuChoice.invoke(myPlanet);
      System.out.println ("Invoked user menu choice!");

    } catch (Exception e){
      e.printStackTrace();
    }
  }

  public static void main(String[] args){
    System.out.println("Got to main!");
    runMyConnection();
    runUserMenuChoice();
    myConnection.closeConnection();
    System.out.println ("Connection closed!");
    System.out.println ("End of Main!");
    System.exit (0);
  }
}

