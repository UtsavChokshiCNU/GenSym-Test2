/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceDocument.java
 *
 */
package com.gensym.shell.util;

import java.awt.Rectangle;
import java.awt.Dimension;
import java.awt.Point;
import java.awt.Insets;
import java.beans.PropertyVetoException;
import java.util.Vector;
import java.util.Hashtable;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JScrollPane;
import com.gensym.classes.Item;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIManager;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.mdi.MDIApplication;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnectionAdapter;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.ntw.util.VersionHelper;
import com.gensym.wksp.WorkspaceView;
import com.gensym.classes.KbWorkspace;
import com.gensym.jgi.G2AccessException;
import com.gensym.draw.LWScrollbar;
import com.gensym.draw.ViewScrollbar;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.AttributeDenotation;
import com.gensym.util.WorkspaceListener;
import com.gensym.util.WorkspaceAdapter;
import com.gensym.util.WorkspaceEvent;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.message.Trace;
import java.awt.Component;

/**
 *  This class represents a G2 workspace as a document in an MDI application.
 *  The WorkspaceDocument consists of a WorkspaceView and scroll bars.
 *  When the KbWorkspace is deleted, the WorkspaceDocument automatically closes.
 *  The name of the workspace is put in the title of the document.
 */
public class WorkspaceDocument extends TW2Document{

  private static Hashtable wkspTable  = new Hashtable();//maps wksp to doc
  private static final Symbol[] neededAttributes = new Symbol[] {SystemAttributeSymbols.NAMES_};
  private WorkspaceView wkspView;
  private JScrollPane scrollPane;
  private KbWorkspace wksp;
  private ViewScrollbar vscroll, hscroll;
  private ItemListener itemListener;
  private ConnectionLogOutAdapter connectionLogOutAdapter;
  private boolean shrinkwrapping = false;
  // this listens for resize events, and if it was caused by our
  // request of a shrinkwrap, then we want to resize the document to fit
  /**
   * Creates a WorkspaceDocument for the specified connection and kbworkspace.
   * It uses the MDIFrame's default menu bar and default toolbar as
   * its menu bar and toolbar.
   *
   * @see com.gensym.mdi.MDIFrame#getDefaultMenuBar
   * @see com.gensym.mdi.MDIFrame#getDefaultToolBarPanel
   */
  public WorkspaceDocument(TwAccess connection, KbWorkspace wksp) throws G2AccessException{
    this(connection, wksp,
	 ((MDIFrame)MDIApplication.getCurrentFrame()).getDefaultMenuBar(), 
	 ((MDIFrame)MDIApplication.getCurrentFrame()).getDefaultWindowMenu(),
	 ((MDIFrame)MDIApplication.getCurrentFrame()).getDefaultToolBarPanel());
  }

  /** 
   *  Creates a Workspace Document for the specified connection and kbworkspace with
   *  the specified menu bar and window menu.  The menu bar and toolbar will be 
   *  visible when the this WorkspaceDocument gets focus.
   */
  public WorkspaceDocument(TwAccess connection, KbWorkspace wksp, 
			   JMenuBar wkspMenuBar, JMenu wkspWindowMenu, 
			   MDIToolBarPanel toolBarPanel) throws G2AccessException{
    super(connection, wkspMenuBar, wkspWindowMenu, toolBarPanel);
    itemListener = new ItemAdapter();
    connectionLogOutAdapter = new ConnectionLogOutAdapter();
    connection.addTwConnectionListener(connectionLogOutAdapter);
    wksp.addItemListener(itemListener, neededAttributes);
    this.wksp = wksp;
    wkspView = createWorkspaceView (wksp);
    // carefully adding this as a listener after the workspace view has been created
    // so that when we receive a resized event for shrinkwrapping, we know that the 
    // workspace view has already been updated
    addComponents ();
    Vector documentList = (Vector)wkspTable.get(wksp);
    if (documentList == null){
      Vector newList = new Vector();
      newList.addElement(this);
      wkspTable.put(wksp, newList);
    }
    else
      documentList.addElement(this);

    Object names = wksp.getNames();
    if (names instanceof Symbol)
      setTitle(((Symbol)names).getPrintValue());
    else if (names instanceof Sequence){
      Symbol name = (Symbol)((Sequence)names).firstElement();
      setTitle(((Symbol)name).getPrintValue());
    } else {
      setTitle("<UNNAMED>");
    }
    setSize(getPreferredSize());
  }

  private static final Class thisClass = com.gensym.shell.util.WorkspaceDocument.class;

  /**
   * Creates the instance of WorkspaceView that will
   * display the KbWorkspace in this document. It is
   * called when the WorkspaceDocument is created.
   */
  protected WorkspaceView createWorkspaceView (KbWorkspace wksp) {
    return  WorkspaceView.createWorkspaceView(this, wksp);
  }

  /**
   * @undocumented
   * This method is called by WorkspaceInstanceCommands when a
   * workspace has been shrink wrapped, and the holding document
   * needs to be shrinkwrapped around it
   */
  public void shrinkWrapDocument(){
    Dimension size = wkspView.getPreferredSize();
    int titleBarHeight = 19;//need to look this up somewhere
    int borderWidth = 5;//need to look this up somewhere
    size.height+=(titleBarHeight+2*borderWidth);
    size.width+=2*borderWidth;
    this.setResizable(true);
    try {
      this.setMaximum(false);
    } catch (java.beans.PropertyVetoException e) {
    }
    setSize(size);
  }
    

  /**
   * @undocumented Review before documenting
   */
  protected void addComponents () {
    Rectangle initialBounds = wkspView.getBounds();
    int initialLeft = initialBounds.x;
    int initialTop = initialBounds.y;
    int initialWidth = initialBounds.width;
    int initialHeight = initialBounds.height;
    scrollPane = new JScrollPane(wkspView);
    scrollPane.getVerticalScrollBar().setUnitIncrement(10);
    scrollPane.getHorizontalScrollBar().setUnitIncrement(10);
    scrollPane.getViewport().setViewPosition(new Point(0,0));
    wkspView.setDoubleBuffered(false);
    getContentPane().add(scrollPane, "Center");
  }

  /**
   * @undocumented Review before documenting
   */
  public JScrollPane getScrollPane() {
    return scrollPane;
  }

  /** Returns the WorkspaceView contained in this WorkspaceDocument. */
  public WorkspaceView getWorkspaceView(){
    return wkspView;
  }

  /** Returns all WorkspaceDocuments that were created from the specified 
   *  KbWorkspace. If there are none, null is returned. */
  public static WorkspaceDocument[] getDocumentsForWorkspace(KbWorkspace wksp){
    Vector documentList = (Vector)wkspTable.get(wksp);
    if (documentList == null) return null;
    WorkspaceDocument[] docs = new WorkspaceDocument[documentList.size()];
    for (int i=0; i<documentList.size(); i++)
      docs[i] = (WorkspaceDocument)documentList.elementAt(i);
    return docs;
  }

  @Override
  boolean cleanupOnClosing() {
    if (!super.cleanupOnClosing())
      return false;
    if (wksp != null && wkspTable != null)
	wkspTable.remove(wksp);
    try {
      wksp.removeItemListener(itemListener, neededAttributes);
      itemListener = null;
      wksp = null;
    } catch(G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    if (wkspView != null){
      vscroll = null;
      hscroll = null;
      wkspView.dispose();
      wkspView = null;
    }
    getContentPane().remove(scrollPane); // paranoia
    TwAccess cxn = getConnection();
    if (cxn != null)
      cxn.removeTwConnectionListener(connectionLogOutAdapter);

    //getConnection().removeTwConnectionListener(connectionLogOutAdapter);
    connectionLogOutAdapter = null;
    return true;
  }

  @Override
  public void setSelected(boolean selected) throws java.beans.PropertyVetoException{
    if (selected == isSelected())
      return;
    super.setSelected(selected);

    if (isSelected())
      getWorkspaceView().requestFocus();
  }

  class ItemAdapter implements ItemListener{
    @Override
    public void receivedInitialValues (ItemEvent e){}
    @Override
    public void itemModified (ItemEvent e){
      Sequence denotation = e.getDenotation();
      if (AttributeDenotation.isAttributeDenotation(denotation)){
	Symbol attributeName_ = AttributeDenotation.getAttributeName(denotation);
	if (attributeName_.equals(SystemAttributeSymbols.NAMES_)){
	  Symbol newName_ = (Symbol)e.getNewValue();
	  if (newName_ != null)
	    setTitle(newName_.getPrintValue());
	  else
	    setTitle("");
	  repaint();
	}  
      }
    }
    @Override
    public void itemDeleted (ItemEvent e){
      try{
	setClosed(true);
      }
      catch(java.beans.PropertyVetoException ex){
	Trace.exception(ex);
      }
    }
  }

  class ConnectionLogOutAdapter extends TwConnectionAdapter{
    @Override
    public void loggedIn (TwConnectionEvent evt) {}

    @Override
    public void loggedOut(TwConnectionEvent event){
      try{
	setClosed(true);
      }
      catch(java.beans.PropertyVetoException ex){
	Trace.exception(ex);
      }
    }

    @Override
    public void userModeChanged (TwConnectionEvent evt) {}
  }


}

