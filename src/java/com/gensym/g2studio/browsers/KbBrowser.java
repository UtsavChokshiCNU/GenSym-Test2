/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 KbBrowser.java
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

public class KbBrowser extends JPanel implements BrowserSymbols {

  private TwAccess currentConnection;
  private ConnectionManager connectionManager;
  private ContextChangedListener contextChangedListener;

  private ClassInstanceBrowser browserPane;
  private ClassInstanceScrollPane modulePane;

  public KbBrowser (ConnectionManager connectionManager) {
    this(connectionManager.getCurrentConnection());
    contextChangedListener = new ContextChangedAdapter();
    connectionManager.addContextChangedListener(contextChangedListener);
    this.connectionManager = connectionManager;
  }

  public KbBrowser (TwAccess connection) {
    setLayout(new BorderLayout());
    setConnection(connection);
    createKbBrowser();
  }

  public void setConnection(TwAccess cxn) {
    currentConnection = cxn;
  }

  private void createKbBrowser() {
    setLayout(new BorderLayout());
    Symbol[] classNames;
    classNames = new Symbol[] {MODULE_HIERARCHY_};
    modulePane = new ClassInstanceScrollPane(currentConnection, classNames[0], ALL_);
    classNames = new Symbol[] {MODULE_HIERARCHY_, WORKSPACE_HIERARCHY_, CLASS_HIERARCHY_};
    browserPane = new ClassInstanceBrowser(currentConnection, classNames, ALL_);
    add(modulePane, BorderLayout.NORTH);
    add(browserPane, BorderLayout.SOUTH);
  }

  class ContextChangedAdapter implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      if (e.isConnectionNew())
	setConnection(e.getConnection());
    } 
  }
}


