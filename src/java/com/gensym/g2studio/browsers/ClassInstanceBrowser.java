/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ClassInstanceBrowser.java
 *
 */
package com.gensym.uitools.browsers;

import java.awt.BorderLayout;

import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.util.Symbol;

import com.sun.java.swing.JPanel;

public class ClassInstanceBrowser extends JPanel implements BrowserSymbols {

  private TwAccess currentConnection;
  private ConnectionManager connectionManager;

  private ContextChangedListener contextChangedListener;

  private Symbol[] classNames;
  private Symbol baseClass = ROOT_;
  private Symbol moduleScope = ALL_;

  private ClassInstanceTabbedPane tabbedPane;

  public ClassInstanceBrowser (ConnectionManager connectionManager, Symbol[] classNames) {
    this.classNames = classNames;
    setupClassInstanceBrowser(connectionManager);
  }

  public ClassInstanceBrowser (ConnectionManager connectionManager, Symbol[] classNames, Symbol moduleScope) {
    this.classNames = classNames;
    this.moduleScope = moduleScope;
    setupClassInstanceBrowser(connectionManager);
  }

  public ClassInstanceBrowser (ConnectionManager connectionManager, Symbol[] classNames, Symbol baseClass, Symbol moduleScope) {
    this.classNames = classNames;
    this.baseClass = baseClass;
    this.moduleScope =  moduleScope;
    setupClassInstanceBrowser(connectionManager);
  }

  public ClassInstanceBrowser (TwAccess connection, Symbol[] classNames) {
    setupClassInstanceBrowser(connection);
  }

  public ClassInstanceBrowser (TwAccess connection, Symbol[] classNames, Symbol moduleScope) {
    this.classNames = classNames;
    this.moduleScope = moduleScope;
    setupClassInstanceBrowser(connection);
  }

  public ClassInstanceBrowser (TwAccess connection, Symbol[] classNames, Symbol baseClass, Symbol moduleScope) {
    this.classNames = classNames;
    this.baseClass = baseClass;
    this.moduleScope = moduleScope;
    setupClassInstanceBrowser(connection);
  }

  private void setupClassInstanceBrowser(ConnectionManager connectionManager) {
    setupClassInstanceBrowser(connectionManager.getCurrentConnection());
    contextChangedListener = new ContextChangedAdapter();
    connectionManager.addContextChangedListener(contextChangedListener);
    this.connectionManager = connectionManager;
  }

  private void setupClassInstanceBrowser(TwAccess connection) {
    setLayout(new BorderLayout());
    add(tabbedPane = new ClassInstanceTabbedPane(connection, classNames, baseClass, moduleScope));
    setConnection(connection);
  }

  public void setConnection(TwAccess cxn) {
    currentConnection = cxn;
    tabbedPane.setConnection(cxn);
  }

  class ContextChangedAdapter implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      if (e.isConnectionNew())
	setConnection(e.getConnection());
    } 
  }
}


