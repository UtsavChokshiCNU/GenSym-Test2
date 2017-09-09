package com.gensym.demos.docs.connectivitydemos;

import com.gensym.controls.ItemRetriever;
import com.gensym.ntw.TwConnectionInfo;
import com.gensym.classes.KbWorkspace;

public class MyItemRetriever {
  private static ItemRetriever retriever;
  private static KbWorkspace kbWorkspace;
  private static TwConnectionInfo connectionInfo;

   //Retrieve an item using default constructor
  public static void getWorkspace1 () {
    //Create retriever
    retriever = new ItemRetriever();
    //Set class and item information
    retriever.setItemClassName("KB-WORKSPACE");
    retriever.setItemName("WKSP-1"); 
    retriever.setHost("localhost");
    retriever.setPort("1112");
    try {
      kbWorkspace = (KbWorkspace)retriever.retrieveItem();
      System.out.println(kbWorkspace);
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  //Retrieve an item, using connection info object
  public static void getWorkspace2 () {
    //Create a connection info object
    TwConnectionInfo connectionInfo = new TwConnectionInfo ("localhost", "1112"); 	
    //Create retriever
    retriever = new ItemRetriever(connectionInfo, "KB-WORKSPACE", "WKSP-2");
    try {
      //Retrieve item and cast result
      kbWorkspace = (KbWorkspace)retriever.retrieveItem();
      System.out.println(kbWorkspace);
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  // **MAIN**
  public static void main(String[] args){
    System.out.println("Got to main!");
    getWorkspace1(); 
    getWorkspace2(); 
    System.out.println ("End of Main!");
    System.exit (0);
  }
}

