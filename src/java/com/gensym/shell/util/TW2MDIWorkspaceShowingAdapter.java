/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TW2MDIWorkspaceShowingAdapter.java
 *
 */
package com.gensym.shell.util;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Point;
import java.util.Vector;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIDocument;
import com.gensym.util.Structure;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnection;
import com.gensym.ntw.WorkspaceShowingListener;
import com.gensym.ntw.WorkspaceShowingEvent;
import com.gensym.ntw.util.VersionHelper;
import com.gensym.ntw.util.WorkspaceDisplayer;
import com.gensym.ntw.util.WorkspaceDisplayStyle;
import com.gensym.core.UiApplication;
import com.gensym.jgi.G2AccessException;
import com.gensym.wksp.WorkspaceView;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Item;
import com.gensym.message.Trace;
import com.gensym.message.Resource;

import com.gensym.util.Symbol;
import com.gensym.wksp.WorkspaceElement;

/**
 *  This adapter class implements the WorkspaceShowingListener interface
 *  for MDI applications.  showWorkspace either adds and activates a 
 *  WorkspaceDocument to the MDIManager or if a WorkspaceDocument representing 
 *  the kb-workspace already exists, activates it.  A new WorkspaceDocument is
 *  created through the default or specified WorkspaceDocumentFactory.  Use
 *  setWorkspaceDocumentFactory to change the class of WorkspaceDocument
 *  created by this adapter.
 *  hideWorkspace closes the appropriate WorkspaceDocument.
 */
public class TW2MDIWorkspaceShowingAdapter extends TW2WorkspaceShowingAdapter {

  private WorkspaceDocumentFactory factory=new DefaultWorkspaceDocumentFactoryImpl();
  private boolean wkspDocFactorySet = false;
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");
  private static final Symbol ITEM_ = Symbol.intern("ITEM");

  /** Creates a TW2MDIWorkspaceShowingAdapter for a single connection application. 
   *  Once this adapter is created, it will show and hide workspace views
   *  according to the WorkspaceShowing protocol.
   */
  public TW2MDIWorkspaceShowingAdapter (TwAccess connection) throws G2AccessException {
    super (connection);
  }

  /** Creates a TW2MDIWorkspaceShowingAdapter for a multiple connection application.
   *  Once this adapter is created, it will show and hide workspace views
   *  according to the WorkspaceShowing protocol.*/
  public TW2MDIWorkspaceShowingAdapter (ConnectionManager connectionManager) throws G2AccessException{
    super (connectionManager);
  }

  /** 
   *  Sets the WorkspaceDocumentFactory that is used to create WorkspaceDocuments. 
   *  By default, the WorkspaceDocumentFactory is DefaultWorkspaceFactoryImpl.
   *  This method may only be called once.
   * @throws Error if it has been called previously
   */
  public void setWorkspaceDocumentFactory(WorkspaceDocumentFactory factory){
    if (wkspDocFactorySet)
      throw new Error (i18n.getString("WorkspaceDocumentFactoryAlreadyDefined"));
    else{
      this.factory = factory;
      wkspDocFactorySet = true;
    }
  }

  @Override
  protected java.lang.Object getDisplayContainer (KbWorkspace wksp,
						  WorkspaceDisplayStyle style) {
    if (style == null)
      return new DocumentDisplayer ();
    else
      return super.getDisplayContainer (wksp, style);
  }

  class DocumentDisplayer implements WorkspaceDisplayer {

  /**
   * Implements the show of the kb-workspace.
   * Finds a WorkspaceDocument displaying this kb-workspace or creates
   * a new WorkspaceDocument for this purpose. The class of the
   * WorkspaceDocument is determined by the WorkspaceDocumentFactory
   * that has been set into the Adapter. It then uses the
   * particulars of the showing-event to scroll the WorkspaceView to
   * the proper location.
   * Sublcasses can specialize this method
   * to do something more specific.
   * @param event the workspace-showing event that is being handled
   * @see #setWorkspaceDocumentFactory
   */
    @Override
    public boolean displayWorkspace (TwConnection cxn,
				     KbWorkspace wksp,
				     Structure showingParticulars) {
      return showWorkspace0 (cxn, wksp, showingParticulars);
    }

  /**
   * Implements the hide of the kb-workspace.
   * Closes all WorkspaceDocuments showing the kb-workspace.
   * @param wksp the workspace to "remove". All other arguments
   * can be null
   */
    @Override
    public boolean removeWorkspace (TwConnection cxn, KbWorkspace wksp, Structure hideParticulars) {
      return hideWorkspace0 (wksp);
    }
  }

  /**
   * @undocumented should be private, but it's been published in the past
   */
  public boolean showWorkspace0 (TwConnection connection, KbWorkspace wksp, Structure particulars) {
    WorkspaceDocument docs[] = 
      WorkspaceDocument.getDocumentsForWorkspace((KbWorkspace)wksp);
    WorkspaceDocument wkspDoc = null;
    Item itm = (Item)particulars.getAttributeValue(ITEM_, null);
    if (docs != null){
      for (int i=0; i<docs.length; i++){
	try{
	  wkspDoc = docs[i];
	  WorkspaceView view = wkspDoc.getWorkspaceView ();
	  docs[i].setIcon(false);
	  docs[i].setSelected(true);
	  selectElement(view, itm);
	  view.showWorkspace(particulars);
	}
	catch(java.beans.PropertyVetoException ex){
	  Trace.exception(ex);
	}
      }
    } 
    else{
      try{
	wkspDoc = factory.createWorkspaceDocument(connection, (KbWorkspace)wksp);
	WorkspaceView view = wkspDoc.getWorkspaceView ();
	Dimension size = wkspDoc.getPreferredSize();
	((MDIFrame)UiApplication.getCurrentFrame()).getManager().addDocument(wkspDoc, size);
	selectElement(view, itm);
	view.showWorkspace(particulars);
      }
      catch(G2AccessException ex){
	new com.gensym.dlg.WarningDialog(null, "", true, 
					 i18n.format("ErrorDownloadingWksp",
						     new Object[]{ex.toString()}),
					 null).setVisible(true);
      }
    }
    return true;
  }
  
  private void selectElement(WorkspaceView view, Item itm) {
    WorkspaceElement we = view.findElement(itm);
    if (we != null) //paranoia
      view.selectElements(new WorkspaceElement[] {we});
  }

  /**
   * @undocumented should be private, but it's been published in the past
   */
  public boolean hideWorkspace0 (KbWorkspace wksp) {
    if (wksp == null) return false;
    WorkspaceDocument[] docs = WorkspaceDocument.getDocumentsForWorkspace(wksp);
    if (docs != null){
      for (int i=0; i<docs.length; i++){
	try{
	  docs[i].setClosed(true); // disposes of the WorkspaceView properly
	}
	catch(java.beans.PropertyVetoException ex){
	  Trace.exception(ex);
	}
      }
      return true;
    } else
      return false;
  }

  
  
}

