
package com.gensym.demos.docs.connectivitydemos;

import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.WorkspaceShowingListener;
import com.gensym.ntw.WorkspaceShowingEvent;
import com.gensym.util.Symbol;
import com.gensym.classes.Object;

public class MyWorkspaceShowingListener implements WorkspaceShowingListener {
  private static TwAccess myConnection; 
  private static Symbol SHOW_WKSP_ = Symbol.intern("SHOW-WKSP");
  private static Symbol HIDE_WKSP_ = Symbol.intern("HIDE-WKSP");
  private static Object[] args = new Object[]{};

  public MyWorkspaceShowingListener() {
    try{
      //Add connection as a workspace showing listener
      myConnection.addWorkspaceShowingListener(this);
      System.out.println ("Added as listener!");  
    } catch (Exception e){
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

  public static void showWksp () {
    try {
      myConnection.callRPC(SHOW_WKSP_, args);
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  public static void hideWksp () {
    try {
      myConnection.callRPC(HIDE_WKSP_, args);
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  //WorkspaceShowingListener methods
  @Override
  public void hideWorkspace (WorkspaceShowingEvent e){
    System.out.println ("Workspace hidden!");  
  }
  @Override
  public void showWorkspace (WorkspaceShowingEvent e){
    System.out.println ("Workspace shown!");  
  }

  public static void main(String[] args){
    System.out.println("Got to main!");
    runMyConnection(); 
    MyWorkspaceShowingListener app = new MyWorkspaceShowingListener();
    try {
      showWksp();
      hideWksp();
      Thread.sleep(500);
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
    myConnection.closeConnection();
    System.out.println ("Connection closed!");
    System.out.println ("End of Main!");
    System.exit (0);
  }
}

