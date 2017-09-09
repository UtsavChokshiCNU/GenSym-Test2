/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 SimpleConnectionDemo.java
 *
 */
package com.gensym.demos.simpleconnectiondemo;

import com.gensym.demos.Demo;
import com.gensym.demos.DemoShell;
import com.gensym.demos.ErrorDialog;
import com.gensym.demos.democlasses.Planet;
import java.awt.Frame;
import java.awt.Dialog;
import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.util.Symbol;
import com.gensym.dlg.InputDialog;
import com.gensym.dlg.MessageDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.StandardDialog;
import com.gensym.jgi.G2CommunicationException;

/** Demo class to illustrate the following:
    1.) how to make a connection to G2
    2.) how to obtain a stub for a G2 instance
    3.) how to use the accessor methods of the automatically generated interface
   */
public class SimpleConnectionDemo implements Demo, StandardDialogClient{
  private String host;
  private String port;
  private Symbol planetName_;
  private DemoShell demoShell;
  private TwAccess g2Connection;
  private Planet planet;
  private static final Symbol PLANET_ = Symbol.intern("PLANET");

  @Override
  public void runDemo(Frame frame){
    try{
      if (g2Connection == null) {
	//Establish a connection to G2
	g2Connection = TwGateway.openConnection(host, port);
	// The following call will fail if the G2 is secure.
	g2Connection.login();
      }
      //Obtain a stub for the G2 instance and cast to appropriate interface
      Object result = g2Connection.getUniqueNamedItem(PLANET_, planetName_);
      planet = (Planet)result;
      String[] textFieldLabels = new String[]{"Number of moons:"};
      String[] buttonLabels = new String[]{"OK", "Cancel"};
      //Use accessor method in interface to get attribute value
      int numberOfMoons = planet.getNumberOfMoons();
      String[] initialValues = new String[]{Integer.toString(numberOfMoons)};
      frame.setVisible(true);
      new InputDialog(frame, planetName_.toString(), false, textFieldLabels, buttonLabels, initialValues, (StandardDialogClient)this).setVisible (true);
    } catch (G2AccessException e){
	ErrorDialog errDlg = new ErrorDialog(e, frame, null, "Error", "G2 5.0r4 or later needs to be running SQ-DEMOS.KB on port "+port+". \n\nError: "+e.getMessage());
	g2Connection = null;
    }
  }

  @Override
  public void dialogDismissed (StandardDialog d, int code) {
    if (d instanceof MessageDialog) return;
    
    InputDialog med = (InputDialog)d;
    if (med.wasCancelled ()) return;

    String[] results = med.getResults ();
    int numberOfMoons = Integer.parseInt(results[0]);
    try{
      //Use accessor method in interface to set attribute value
      planet.setNumberOfMoons(numberOfMoons);
    } catch (Exception e){
       ErrorDialog errDlg = new ErrorDialog(e, (Frame)demoShell, null, "Error", "Lost connection.  Restart G2 5.0r4 or later with SQ-DEMOS.KB on port "+port);
       g2Connection = null;
    }
  }

  public static void main(String[] args){
    if (args.length != 3) {
      System.err.println ("Usage: java com.gensym.demos.simpleconnectiondemo.SimpleConnectionDemo host port planetName");
      System.exit (2);
    }
    SimpleConnectionDemo demo = new SimpleConnectionDemo();
    demo.host = args[0];
    demo.port = args[1];
    demo.planetName_ = Symbol.intern(args[2]);
    String msg = new String("To run the demo, choose File > Run Demo. \n\nYou will see a dialog with a single text box for changing the number of moons of the planet named FOOBAR.  Edit the value in the dialog and click OK to see the value change in G2.  \n\nTo quit the demo, choose File > Exit. \n\nThis demo launches G2 5.0r4 and loads SQ-DEMOS.KB on port "+demo.port+". To start G2, the demo uses a command line similar to the following: \n\n     g2 -tcpport 1234 -kb <path>\\SQ-DEMOS.KB -name Sequoia-Demo \n\nHere is the specific Java code that interacts with G2:\n\nEstablish a connection to G2: \n     g2Connection = TwGateway.connect(host, port); \n\nObtain a stub for the G2 instance: \n     Object result = g2Connection.getUniqueNamedItem(PLANET_, planetName_); \n\nCast result to appropriate interface:\n     Planet planet = (Planet)result; \n\nUse accessor methods to get and set attribute values: \n     int numberOfMoons = planet.getNumberOfMoons(); \n     planet.setNumberOfMoons(numberOfMoons); \n\nThe interface COM.gensym.demos.democlasses.Planet was automatically generated using COM.gensym.util.DownloadInterfaces. \n\nSee COM.gensym.demos.simpleconnectiondemo.SimpleConnectionDemo.java for the complete demo source code.");
    demo.demoShell = new DemoShell("SimpleConnectionDemo", msg, (Demo)demo, "SimpleConnectionDemo.java");
    demo.demoShell.setSize(600, 400);
    demo.demoShell.setVisible(true);
  }

}

