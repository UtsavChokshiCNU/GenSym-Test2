/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TwAccessTestCommand.java
 *
 */
package com.gensym.tests.auto.ntw;

import java.awt.Dimension;
import java.awt.Insets;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.util.Vector;
import javax.swing.JMenuBar;
import com.gensym.classes.KbWorkspace;
import com.gensym.draw.LWScrollbar;
import com.gensym.draw.ViewScrollbar;
import com.gensym.jgi.G2AccessException;
//import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIFrame;
import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.tests.auto.LogWindow;
import com.gensym.tests.auto.TestHarness;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.message.Resource;
import com.gensym.util.Symbol;
import com.gensym.wksp.RubberBandHandler;
import com.gensym.wksp.WorkspaceView;

public class TwAccessTestCommand extends AbstractStructuredCommand implements ContextChangedListener {
  private static final String TWACCESS_TESTS = "TwAccessTests";
  private static final String TEST_CREATE_ITEM = "TestCreateItem";

  private static TwAccessTestDialog itemDialog = null;

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");

  Symbol KBWORKSPACE_ = Symbol.intern("KB-WORKSPACE");

  ConnectionManager cm = null;
  MDIFrame appFrame = null;
  TestHarness app = null;
  LogWindow logWindow = null;

  public TwAccessTestCommand(TestHarness testApp, LogWindow logWindow, ConnectionManager connectionManager){
    super(new CommandInformation[]{
      new CommandInformation(TWACCESS_TESTS, true, shortResource, longResource, null,
			     null, null, true),
      new CommandInformation(TEST_CREATE_ITEM, true, shortResource, longResource, 
			     null, null, null, true)});

    app = testApp;
    appFrame = testApp.getFrame();
    cm = connectionManager;
    cm.addContextChangedListener(this);

    this.logWindow = logWindow;

    setAvailable(TWACCESS_TESTS, false);
    setAvailable(TEST_CREATE_ITEM, false);
  }


  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)){
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", cmdKey));
    } 

    if (cmdKey.equals(TEST_CREATE_ITEM)){
      handleTestCreateItemCommand();
    }
  }

  // BEGIN:  ContextChangedListener Methods
  @Override
  public void currentConnectionChanged(ContextChangedEvent event){
    /*
     * Connection status changed, re-evaluate whether or not commands should
     * be enabled/disabled
     */
    TwAccess context = event.getConnection();
    boolean available = true;
    if (context == null){
      available = false;
      noConnection();
    }
  
    setAvailable(TWACCESS_TESTS, available);
    setAvailable(TEST_CREATE_ITEM, available);
  }
  // END: ContextChangedListener Methods

  private void noConnection(){
    setAvailable(TWACCESS_TESTS, false);
    setAvailable(TEST_CREATE_ITEM, false);
  }

  private WorkspaceDocument setupMDIChildWithWorkspaceView(){
    TwAccess context = cm.getCurrentConnection();
    Symbol name_ = Symbol.intern("WorkspaceView Test");
    WorkspaceDocument doc = createWorkspace(context, name_);
    return doc;
  }

  // BEGIN: handleTestCreateItemCommand
  private void handleTestCreateItemCommand(){
    WorkspaceDocument child = setupMDIChildWithWorkspaceView();
    WorkspaceView wkspView = (WorkspaceView)child.getContentPane().getComponent(0);

    if (itemDialog == null) {
      boolean isModal = false;
      itemDialog = new TwAccessTestDialog(appFrame,
					  "Testing Item Methods",
					  isModal,
					  TwAccessTestDialog.CREATE_ITEM_PANEL,
            logWindow,
					  cm);
    }

    itemDialog.setWorkspaceView(wkspView);
    itemDialog.show();
  }
  // END: handleTestCreateItemCommand

  // BEGIN: createWorkspace
  private WorkspaceDocument createWorkspace(TwAccess cxn, Symbol name_){
    try{
      KbWorkspace newWksp = (KbWorkspace)cxn.createItem(KBWORKSPACE_);
      //name it
      return addWorkspace(cxn, newWksp, name_);
    }
    catch(G2AccessException ex){
      System.out.println(ex.getMessage());
    }
    return null;
  }
  // END: createWorkspace

  // BEGIN: addWorkspace
  private WorkspaceDocument addWorkspace(TwAccess cxn, KbWorkspace wksp, Symbol name_){
   
      WorkspaceView view = new WorkspaceView(wksp);
      
      Rectangle initialBounds = view.getBounds();
      int initialLeft = initialBounds.x;
      int initialTop = initialBounds.y;
      int initialWidth = initialBounds.width;
      int initialHeight = initialBounds.height;
      ViewScrollbar hscroll = new ViewScrollbar (view, LWScrollbar.HORIZONTAL,
						 0, 1,
						 initialLeft, initialLeft + 
						 initialWidth);
      ViewScrollbar vscroll = new ViewScrollbar (view, LWScrollbar.VERTICAL,
						 0, 1,
						 initialTop, initialTop + 
						 initialHeight);
      view.addScrollbar(vscroll, false);
      view.addScrollbar(hscroll, true);

      view.setEventHandler(new RubberBandHandler ());
      view.setDoubleBuffered(true);

      //JMenuBar mb = app.getMenuBar();
      String title = "";
      if (name_ != null) title = name_.getPrintValue();
      WorkspaceDocument child = new WorkspaceDocument(cxn, wksp);

      //instead add editHandler and wkspHandler as propertyChangeListeners
      //child.addPropertyChangeListener(this);
      //wksp.addItemListener(this);
      child.getContentPane().add(view, "Center");//index=0
      child.getContentPane().add(hscroll, "South");//index=1
      child.getContentPane().add(vscroll, "East");//index=2
      appFrame.getManager().addDocument(child, getWorkspaceViewMinimumSize(child));
      child.setTitle(child.getTitle()+" ("+cxn.toShortString()+")");
      return child;
  }
  // END: addWorkspace

  // BEGIN: getWorkspaceViewMinimumSize
  private Dimension getWorkspaceViewMinimumSize(WorkspaceDocument child){
      WorkspaceView view = (WorkspaceView)child.getContentPane().getComponent(0);
      Rectangle logicalBounds = view.getLogicalBounds();
      int viewWidth = logicalBounds.width;
      int viewHeight = logicalBounds.height;
      Rectangle bounds = view.getBounds();
      ViewScrollbar hscroll = (ViewScrollbar)child.getContentPane().getComponent(1);
      ViewScrollbar vscroll = (ViewScrollbar)child.getContentPane().getComponent(2);
      Insets insets = child.getInsets();
      return new Dimension(viewWidth + vscroll.getPreferredSize().width + 
			   insets.right + insets.left, 
			   viewHeight + hscroll.getPreferredSize().height+ 
			   insets.top + insets.bottom);
  }
  // END: getWorkspaceViewMinimumSize
}











