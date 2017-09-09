/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Shell.java
 *
 */
package com.gensym.cbu.adminShell;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import javax.swing.*;

public class ShellLauncher extends Applet implements ActionListener {
  private TextField display;
  private int arg = 0;
  private String op = "=";
  private boolean start = true;
  private String launchLabel = "Launch OpEx";

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

    Button launchButton = new Button(launchLabel);
    launchButton.addActionListener(this);
    add(launchButton, "South");
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

    if(s.equals(launchLabel)) {
      System.out.println("Kickin' 'er off!");
      System.out.flush();
      String[] args = new String[] {"-host", "localhost", "-900x700+20+20"};
      Shell.main(args);
    }
    else if('0' <= s.charAt(0) && s.charAt(0) <= '9') {
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
