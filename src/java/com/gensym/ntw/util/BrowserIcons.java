/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 BrowserIcons.java
 *
 */
package com.gensym.ntw.util;

import java.awt.Image;
import java.awt.Toolkit;

import javax.swing.Icon;
import javax.swing.ImageIcon;

//public interface BrowserIcons {
public class BrowserIcons {

  private static final Class thisClass = com.gensym.ntw.util.BrowserIcons.class;

  // KB-WORKSPACE
  public static  Image kbWorkspaceImage = Toolkit.getDefaultToolkit().getImage(thisClass.getResource("kbworkspace.gif"));
  public static Icon kbWorkspaceIcon = new ImageIcon(kbWorkspaceImage);

  // MODULE
  public static Image moduleImage = Toolkit.getDefaultToolkit().getImage(thisClass.getResource("module.gif"));
  public static Icon moduleIcon = new ImageIcon(moduleImage);

  // CLASS-DEFINITION
  public static Image classDefinitionImage = Toolkit.getDefaultToolkit().getImage(thisClass.getResource("classdef.gif"));
  public static Icon classDefinitionIcon = new ImageIcon(classDefinitionImage);

  // SYSTEM-TABLE
  public static Image systemTableImage = Toolkit.getDefaultToolkit().getImage(thisClass.getResource("system-table.gif"));
  public static Icon systemTableIcon = new ImageIcon(systemTableImage);

  //public static ImageIcon kbWorkspaceIcon = new ImageIcon("kbworkspace.gif");
  //public static ImageIcon moduleIcon = new ImageIcon("module.gif");
  //public static ImageIcon classDefinitionIcon = new ImageIcon("classdef.gif");
  //public static ImageIcon systemTableIcon = new ImageIcon("system-table.gif");	

  // icons needed for: ACTION-BUTTON, RULE, CHART
}
