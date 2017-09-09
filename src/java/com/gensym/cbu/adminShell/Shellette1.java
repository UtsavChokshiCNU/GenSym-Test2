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
import javax.swing.*;

import com.gensym.denali.simpleclient.ClientSession;
import com.gensym.denali.simpleclient.ModuleView;

public class Shellette1 extends Applet implements ActionListener {

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
    display = new TextField("0");
    display.setEditable(false);
    add(display, "North");

    Panel p = new Panel();
    p.setLayout(new GridLayout(4,4));
    for(int i=0; i <= 9; i++)
      addButton(p, "" + (char)('0' + i));

    addButton(p, "+");
    addButton(p, "-");
    addButton(p, "*");
    addButton(p, "/");
    addButton(p, "%");
    addButton(p, "=");
    add(p, "Center");

    String[] args = new String[] {"-host", "localhost", "-900x700+20+20"};
    ShellDriver.main(args);

    application = (ShellDriver) ShellDriver.getApplication();

    System.out.println(" app is: "+application+".");

    currentClientSession = application.getCurrentSession();
    currentModuleView = application.getCurrentModule();

    Label moduleName = new Label(currentModuleView.getName());
    add(moduleName, "South");

    //    JButton launchButton = new JButton(launchLabel);
    //    launchButton.addActionListener(this);
    //    add(launchButton, "South");
  }

  public void addButton(Container c, String s)
  {
    Button b = new Button(s);
    c.add(b);
    b.addActionListener(this);
  }

  @Override
  public void actionPerformed(ActionEvent evt)			     
  {
    System.out.println("In actionPerformed");
    System.out.flush();

    String s = evt.getActionCommand();

    if('0' <= s.charAt(0) && s.charAt(0) <= '9') {
      if(start)
	display.setText(s);
      else 
	display.setText(display.getText() + s);
      start = false;
    }
    else {
      if(start) {
	if(s.equals("-")) {
	  display.setText(s);
	  start = false;
	}
	else
	  op = s;
      }
      else {
	calculate(Integer.parseInt(display.getText()));
	op = s;
	start = true;
      }
    }
  }

  public void calculate(int n)
  {
    if(op.equals("+"))  arg += n;
    else if(op.equals("-"))  arg -= n;
    else if(op.equals("*"))  arg *= n;
    else if(op.equals("/"))  arg /= n;
    else if(op.equals("%"))  arg %= n;
    else if(op.equals("="))  arg = n;
    display.setText("" + arg);
  }

  @Override
  public void paint(Graphics g) 
  {
    //    Font f = new Font("System", Font.BOLD, 18);
    //    g.setFont(f);
    //    g.drawString("Home of future OpEx App", 25, 50);
  }
}
