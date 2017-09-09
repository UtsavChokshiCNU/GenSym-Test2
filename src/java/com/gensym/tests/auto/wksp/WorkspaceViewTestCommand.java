/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceViewTestCommand.java
 *
 */
package com.gensym.tests.auto.wksp;

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
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIFrame;
import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.tests.auto.TestHarness;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.message.Resource;
import com.gensym.util.Symbol;
import com.gensym.wksp.RubberBandHandler;
import com.gensym.wksp.WorkspaceView;

public class WorkspaceViewTestCommand extends AbstractStructuredCommand implements ContextChangedListener {
  private static final String WORKSPACE_VIEW_TESTS = "WorkspaceViewTests";
  private static final String TEST_ELEMENT_METHODS = "TestElementMethods";
  private static final String TEST_COLOR_METHODS = "TestColorMethods";

  private static WorkspaceViewTestDialog elementDialog = null;
  private static WorkspaceViewTestDialog colorDialog = null;


  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");

  Symbol KBWORKSPACE_ = Symbol.intern("KB-WORKSPACE");

  ConnectionManager cm = null;
  MDIFrame appFrame = null;
  TestHarness app = null;

  public WorkspaceViewTestCommand(TestHarness testApp,
				  ConnectionManager connectionManager){
    super(new CommandInformation[]{
      new CommandInformation(WORKSPACE_VIEW_TESTS, true, shortResource, longResource, null,
			     null, null, true),
      new CommandInformation(TEST_ELEMENT_METHODS, true, shortResource, longResource, 
			     null, null, null, true),
      new CommandInformation(TEST_COLOR_METHODS, true, shortResource, longResource, 
			     null, null, null, true)});

    app = testApp;
    appFrame = testApp.getFrame();
    cm = connectionManager;
    cm.addContextChangedListener(this);

    setAvailable(WORKSPACE_VIEW_TESTS, false);
    setAvailable(TEST_ELEMENT_METHODS, false);
    setAvailable(TEST_COLOR_METHODS, false);
  }

  @Override
  public String[] getKeys(){
    return new String[] {WORKSPACE_VIEW_TESTS, TEST_ELEMENT_METHODS,
			   TEST_COLOR_METHODS};
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)){
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", cmdKey));
    } 

    if (cmdKey.equals(TEST_ELEMENT_METHODS)){
      handleTestElementMethodsCommand();
    }
    else if (cmdKey.equals(TEST_COLOR_METHODS)){
      handleTestColorMethodsCommand();
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
    
    setAvailable(WORKSPACE_VIEW_TESTS, available);
    setAvailable(TEST_ELEMENT_METHODS, available);
    setAvailable(TEST_COLOR_METHODS, available);
  }
  // END: ContextChangedListener Methods

  private void noConnection(){
    setAvailable(WORKSPACE_VIEW_TESTS, false);
    setAvailable(TEST_ELEMENT_METHODS, false);
    setAvailable(TEST_COLOR_METHODS, false);
  }

  private WorkspaceDocument setupMDIChildWithWorkspaceView(){
    TwAccess context = cm.getCurrentConnection();
    Symbol name_ = Symbol.intern("WorkspaceView Test");
    WorkspaceDocument child = createWorkspace(context, name_);
    return child;
  }

  // BEGIN: handleTestElementMethodsCommand
  private void handleTestElementMethodsCommand(){
    WorkspaceDocument child = setupMDIChildWithWorkspaceView();
    WorkspaceView wkspView = child.getWorkspaceView();

    if (elementDialog == null) {
      boolean isModal = false;
      elementDialog = new WorkspaceViewTestDialog(appFrame,
				 "Testing Element Methods",
				 isModal,
				 WorkspaceViewTestDialog.ELEMENT_METHODS_PANEL,
				 cm);
    }

    elementDialog.setWorkspaceView(wkspView);
    elementDialog.show();
  }
  // END: handleTestColorMethodsCommand

  private void handleTestColorMethodsCommand(){
    WorkspaceDocument child = setupMDIChildWithWorkspaceView();
    WorkspaceView wkspView = child.getWorkspaceView();

    if (elementDialog == null) {
      boolean isModal = false;
      elementDialog = new WorkspaceViewTestDialog(appFrame,
				 "Testing Color Methods",
				 isModal,
				 WorkspaceViewTestDialog.COLOR_METHODS_PANEL,
				 cm);
    }

    elementDialog.setWorkspaceView(wkspView);
    elementDialog.show();
  }

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
      WorkspaceView view = child.getWorkspaceView();
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











