/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ClassInstanceTabbedPane.java
 *
 */
package com.gensym.uitools.browsers;

import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;

import com.sun.java.swing.ImageIcon;
import com.sun.java.swing.JTabbedPane;

public class ClassInstanceTabbedPane extends JTabbedPane implements BrowserSymbols {

  private TwAccess currentConnection;
  private Symbol[] classNames;
  private Symbol baseClass = ROOT_;
  private Symbol moduleScope = ALL_;
 
  private ClassInstanceScrollPane[] scrollPanes;
  private int numTabs;

  private static int tabRepresentationConstraints = TEXT_AND_ICON;

  ImageIcon defaultIcon = new ImageIcon("gensym_logo.gif");

  public ClassInstanceTabbedPane (TwAccess cxn, Symbol[] classNames, Symbol baseClass, Symbol moduleScope) {
    this (cxn, classNames, baseClass, moduleScope, tabRepresentationConstraints);
  }

  public ClassInstanceTabbedPane (TwAccess cxn, Symbol[] classNames, Symbol baseClass, Symbol moduleScope, int tabRepresentationConstraints) {
    this.classNames = classNames;
    this.baseClass = baseClass;
    this.moduleScope = moduleScope;
    this.tabRepresentationConstraints = tabRepresentationConstraints;
    setConnection(cxn);
    numTabs = classNames.length;
    if (numTabs > 0) {
      scrollPanes = new ClassInstanceScrollPane[numTabs];
      createTabbedPaneForClasses();
    }
  }

  public void setConnection(TwAccess cxn) {
    System.out.println("ClassInstanceTabbedPane.setConnection: "+cxn);
    currentConnection = cxn;
    if (scrollPanes != null && scrollPanes.length > 0) {
      for (int i=0; i<scrollPanes.length; i++) {
	scrollPanes[i].setConnection(cxn);
      }
    }
  }

  private void createTabbedPaneForClasses() {
    for (int i=0; i<numTabs; i++) {
      scrollPanes[i] = new ClassInstanceScrollPane(currentConnection, classNames[i], baseClass, moduleScope);
      //System.out.println("scrollPane: "+scrollPanes[i]);
      if (tabRepresentationConstraints == ICON_ONLY)
	addTab(null, defaultIcon, scrollPanes[i], classNames[i].toString());
      else if (tabRepresentationConstraints == TEXT_ONLY)
	addTab(classNames[i].toString(), null, scrollPanes[i]);
      else
	addTab(classNames[i].toString(), defaultIcon, scrollPanes[i]);
    }
    setSelectedIndex(0);
  }
}


