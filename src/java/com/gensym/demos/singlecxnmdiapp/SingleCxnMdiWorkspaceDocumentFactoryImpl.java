/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 SingleCxnMdiWorkspaceDocumentFactoryImpl.java
 *
 */

package com.gensym.demos.singlecxnmdiapp;

import com.gensym.classes.KbWorkspace;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.shell.util.WorkspaceDocumentFactory;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;

public class SingleCxnMdiWorkspaceDocumentFactoryImpl implements WorkspaceDocumentFactory {
  
  /**
   *  Creates and returns a SingleCxnMdiWorkspaceDocument.
   */
  @Override
  public WorkspaceDocument createWorkspaceDocument(TwAccess connection, 
						   KbWorkspace workspace) throws G2AccessException {
      return new SingleCxnMdiWorkspaceDocument(connection, workspace);
  }
}
