package com.gensym.ntw.test;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import javax.swing.*;

//import com.gensym.ntw.test.Shell;
import com.gensym.core.GensymApplication;
import com.gensym.message.Trace;

public class TW2ShellApplet extends JApplet {
  boolean isStandalone = false;
  Shell application;


  //Construct the applet
  public TW2ShellApplet() {
  }

  //Initialize the applet
  @Override
  public void init() {

    try  {
       UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());

      //Get applet parameters
      String[] cmdLineArgs;
      cmdLineArgs = getAppletParams();

      //Check if cmdLineArgs is null
      boolean isNull = true;
      for (int i=0; i < cmdLineArgs.length; i++) {
          if (cmdLineArgs[i] != null) isNull = false;
      }

      //If cmdLineArgs is null reset cmdLindArgs. Otherwise lunch shell app
      if (isNull) {
         cmdLineArgs = new String[] {"applet"};
      }

      //Set debug mode
     GensymApplication.setDevOption(true);
     Trace.setExceptionTraceOn(true);

      if ((Shell.getApplication()) == null) {
        System.out.println("The application is null");
        Shell.main(cmdLineArgs);
        //application = (Shell) Shell.getApplication();
      }
      else {
        System.out.println("The application is not null");
        application = (Shell) Shell.getApplication();
        application.createShell();
        application.setShellApplication(application);   
      }

    
    }
    catch(Exception e)  {
      e.printStackTrace();
    }
  }

  //Component initialization
  private void jbInit() throws Exception {
    this.setSize(new Dimension(400,300));
  }

  //Get Applet information
  @Override
  public String getAppletInfo() {
    return "Applet Information";
  }

  //Get parameter info
  @Override
  public String[][] getParameterInfo() {
    return null;
  }
  
  //Clean up application
  @Override
  public void stop() {
    //application.dispose();
  }

  //Get parameter from applet params and convert them into shell cmdLineArgs
  private String[] getAppletParams() {
    String[]  cmdLineArgs = new String[30];
    int index = 0;

    //Get port number and make it to cmdLineArgs
    index = makeCmdLineArgs("port", index, cmdLineArgs);

    //Get host and make it to cmdLineArgs
    index = makeCmdLineArgs("host", index + 1, cmdLineArgs);

    //Get url and make it to cmdLineArgs
    index = makeCmdLineArgs("url", index + 1, cmdLineArgs);

    return cmdLineArgs;
  }

  //Create cmdLinearg for shell application
  private int makeCmdLineArgs(String param, int index, String[] cmdLineArgs) {
    String aParamValue;

    if ((aParamValue = getParameter(param)) != null) {
      cmdLineArgs[index] = "-" + param;
      cmdLineArgs[++index] = aParamValue;
    }

    return index;
  }

  


} 