/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	TestShell.java
 *
 */
package com.gensym.g2studio;

import java.awt.Frame;
import com.gensym.shell.Shell;

public class TestShell extends Shell {

  private static TestShell thisApp = null;
  private static Frame frame;
 
  public TestShell(String[] cmdLineArgs){
    super(cmdLineArgs);
  }

  public static void main(String[] cmdLineArgs){   
    thisApp = new TestShell(cmdLineArgs);
    thisApp.frame = thisApp.getCurrentFrame();
    frame.setTitle("TestShell Application");
    frame.setVisible(true);
  }
}
