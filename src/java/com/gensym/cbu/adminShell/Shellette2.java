/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Shellette.java
 *
 */
package com.gensym.cbu.adminShell;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import java.util.Vector;
import javax.swing.*;

import com.gensym.denali.simpleclient.ClientSession;
import com.gensym.denali.simpleclient.ModuleView;

public class Shellette2 extends Applet {

  ShellDriver application;
  ClientSession currentClientSession;
  ModuleView currentModuleView;

  private TextField display;
  private int arg = 0;
  private String op = "=";
  private boolean start = true;

  @Override
  public void init() 
  {
    setLayout(new BorderLayout());

    Panel p = new Panel();

    String[] args = new String[] {"-host", "localhost", "-900x700+20+20"};
    ShellDriver.main(args);

    application = (ShellDriver) ShellDriver.getApplication();

    System.out.println(" app is: "+application+".");

    currentClientSession = application.getCurrentSession();
    currentModuleView = application.getCurrentModule();

    Vector classes = currentModuleView.getRequiredClasses();
    // Swing ain't working, so use Choice (Thanks, Christine!)
    //    JComboBox classList = new JComboBox(classes);
    Choice classList = new Choice();
    for(int i=0; i < classes.size(); i++) {
      classList.add(""+classes.elementAt(i));
    }

    add(classList, "Center");
  }

  @Override
  public void paint(Graphics g) 
  {
    //    Font f = new Font("System", Font.BOLD, 18);
    //    g.setFont(f);
    //    g.drawString("Home of future OpEx App", 25, 50);
  }
}
