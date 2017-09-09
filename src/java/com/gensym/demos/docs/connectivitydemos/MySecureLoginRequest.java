package com.gensym.demos.docs.connectivitydemos;

import com.gensym.ntw.TwGateway;
import com.gensym.demos.Demo;
import com.gensym.demos.DemoShell;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.LoginRequest;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2CommunicationException;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.InputDialog;
import java.awt.Frame;

public class MySecureLoginRequest implements Demo, StandardDialogClient {
  private static TwAccess myConnection; 
  private static LoginRequest myLogin;
  private static DemoShell demoShell;

  //Make frame visible and create dialog
  @Override
  public void runDemo (Frame frame) {	
    frame.setVisible(true);
    String[] textFieldLabels = new String[]{"User Name", "User Mode",
													"Password"};
    String[] initialValues = new String[]{"", "", ""};
    InputDialog id = new InputDialog(frame, "Secure Login", false,
		textFieldLabels, initialValues, this);
    id.setVisible(true);
    id.setNoEcho(2);
  }

  //Handle dialog events
  @Override
  public void dialogDismissed (StandardDialog d, int code) {
    InputDialog id = (InputDialog)d;
    if (id.wasCancelled()) return;
    String[] results = id.getResults();
    Symbol userName = Symbol.intern(results[0]);
    Symbol userMode = Symbol.intern(results[1]);
    Symbol userPassword = Symbol.intern(results[2]);
    try{
      //Establish a connection to G2
      myConnection = TwGateway.openConnection("localhost", "1112");
      //Create LoginRequest
      myLogin = new LoginRequest(userName, userMode, userPassword);
      myConnection.login(myLogin);
      System.out.println("Connected to G2!");
      myConnection.returnMessage("Connected to G2!");
      //Get user name and user mode
      Symbol g2UserName = myLogin.getUserName();
      Symbol g2UserMode = myConnection.getUserMode();
      System.out.println(g2UserName);
      System.out.println(g2UserMode);
    } catch (G2AccessException e){
      e.printStackTrace();
      System.exit (-1);
    }
  }

  // MAIN
  public static void main(String[] args){
    System.out.println("Got to main!");
    MySecureLoginRequest demo = new MySecureLoginRequest();
    String msg = new String("This demo shows how to log on to a secure G2.");
    demo.demoShell = new DemoShell ("Secure Login Demo", msg, (Demo)demo, "MySecureLoginRequest.java");
    demo.demoShell.setSize(600,400);
    demo.demoShell.setVisible(true);
  }
}
