/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DemoWorkspaceDocumentFactoryImpl.java
 *
 */

package com.gensym.demos.sequoia.course;

import com.gensym.classes.KbWorkspace;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.shell.util.WorkspaceDocumentFactory;
import com.gensym.ntw.TwAccess;

/**
 * This implementation of the WorkspaceDocumentFactory interface is used
 * in com.gensym.demos.sequoia.course.ProductionDemo.  It creates 
 * DemoWorkspaceDocuments.
 * 
 * @see com.gensym.demos.sequoia.course.ProductionDemo
 * @see com.gensym.demos.sequoia.course.DemoWorkspaceDocument
 */

public class DemoWorkspaceDocumentFactoryImpl implements WorkspaceDocumentFactory {
  
  /**
   *  Creates and returns a DemoWorkspaceDocument.
   */
  @Override
  public WorkspaceDocument createWorkspaceDocument(TwAccess connection, 
						   KbWorkspace workspace) throws com.gensym.jgi.G2AccessException {
    return new DemoWorkspaceDocument(connection, workspace);
  }
}
