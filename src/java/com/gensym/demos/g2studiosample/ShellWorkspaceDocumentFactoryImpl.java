/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ShellWorkspaceDocumentFactoryImpl.java
 *
 */

package com.gensym.demos.g2studiosample;

import com.gensym.shell.util.WorkspaceDocumentFactory;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.KbWorkspace;
import com.gensym.core.MenuFactory;
import com.gensym.mdi.MDIFrame;


/**
 *  This implementation of the WorkspaceDocumentFactory interface is used
 *  by Shell, the default applicatio shell for Telewindows2.  It creates 
 *  ShellWorkspaceDocuments.
 *
 * @see com.gensym.shell.Shell
 * @see com.gensym.shell.TW2WorkspaceDocument
 */

public class ShellWorkspaceDocumentFactoryImpl implements WorkspaceDocumentFactory {
  private Shell shell;
  
  public ShellWorkspaceDocumentFactoryImpl(Shell shell) {
    this.shell = shell;
  }
  /**
   *  Creates and returns a ShellWorkspaceDocument.
   */
  @Override
  public WorkspaceDocument createWorkspaceDocument (TwAccess connection, 
						    KbWorkspace workspace)
       throws G2AccessException
  {
    MenuFactory menuFactory = shell.getMenuFactory(connection);
    WorkspaceDocument doc = new ShellWorkspaceDocument(connection, workspace);
    doc.setDocumentMenuBar(menuFactory.getMenuBar(doc),
			   ((MDIFrame)shell.getCurrentFrame()).getDefaultWindowMenu());
    
    return doc;
  }
}
