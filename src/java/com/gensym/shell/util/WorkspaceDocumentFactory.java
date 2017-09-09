/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceDocumentFactory.java
 *
 */
package com.gensym.shell.util;

import com.gensym.mdi.MDIDocument;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.KbWorkspace;

/**
 *  This interface defines a factory for creating WorkspaceDocuments.
 */

public interface WorkspaceDocumentFactory{

  /**
   *  Creates and returns a WorkspaceDocument.
   */
  public WorkspaceDocument createWorkspaceDocument(TwAccess connection, 
						   KbWorkspace workspace) throws G2AccessException;
}
