/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DefaultWorkspaceDocumentFactoryImpl.java
 *
 */

package com.gensym.shell.util;

import com.gensym.mdi.MDIDocument;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.KbWorkspace;

/**
 *  This is a default implementation of the WorkspaceDocumentFactory interface.
 *  This implementation creates and returns a WorkspaceDocument.
 */

public class DefaultWorkspaceDocumentFactoryImpl implements WorkspaceDocumentFactory{

  
  /**
   *  Creates and returns a WorkspaceDocument.
   */
  @Override
  public WorkspaceDocument createWorkspaceDocument(TwAccess connection, 
						   KbWorkspace workspace) throws G2AccessException{
      return new WorkspaceDocument(connection, workspace);
  }
}
