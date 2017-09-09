/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceInstanceCommand.java
 *
 */
package com.gensym.shell;

/*
import java.awt.Frame;
import java.awt.Rectangle;

import java.awt.Component;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.text.MessageFormat;
import java.util.Vector;
import com.gensym.classes.KbWorkspace;
import com.gensym.dlg.ErrorDialog;
import com.gensym.dlg.MultiEditDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.mdi.MDIChildFrame;
import com.gensym.mdi.MDIClient;
import com.gensym.mdi.MDIFrame;
*/

import java.awt.Component;
import java.awt.Graphics;
import java.awt.PrintJob;
import java.awt.event.ActionEvent;
import java.util.Enumeration;
import java.util.Vector;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import com.gensym.classes.Item;
import com.gensym.dlg.ErrorDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.jgi.G2AccessException;
import com.gensym.mdi.MDIChildFrame;
import com.gensym.mdi.MDIClient;
import com.gensym.mdi.MDIFrame;
import com.gensym.ntw.TwAccess;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.util.Resource;
import com.gensym.util.Symbol;
import com.gensym.wksp.WorkspaceElement;
import com.gensym.wksp.WorkspaceView;

/**
 * WorkspaceInstanceCommand contains commands for the 
 * following WorkspaceView-type actions: 
 * Shrink Wrap Workspace, Shrink Wrap Window<p>
 *  
 * Users can generate menus and/or toolbars for all, or part, of these
 * commands.<p>
 *
 * WorkspaceInstanceCommand listens to changes in workspace focus
 * (WorkspaceFocusListener).
 */
public class WorkspaceInstanceCommand extends AbstractStructuredCommand implements PropertyChangeListener {
  private static final boolean debugCommands = false;

  private static Resource shortBundle = Resource.getBundle("com/gensym/shell/CommandShortResource");
  private Resource i18n = Resource.getBundle("com/gensym/shell/Errors");

  private MDIFrame frame;
  private ConnectionManager connectionMgr;
  private WorkspaceManager workspaceMgr;
 
  private static final String SHRINK_WRAP_WORKSPACE = "ShrinkWrapWorkspace";
  private static final String SHRINK_WRAP_WINDOW = "ShrinkWrapWindow";
  private static final String PRINT_WORKSPACE = "PrintWorkspace";
 
  /**
   * @param parentFrame The parent frame that is managing the mouse and/or
   * toolbars generated from this command. 
   * @param connectionManager The ConnectionManager that is managing the
   * Telewindow's connections for the parent application
   * @param workspaceManager The WorkspaceManager that is managing the 
   * MDIChildFrame's containing WorkspaceViews.
   */
  public WorkspaceInstanceCommand(MDIFrame parentFrame,
				  ConnectionManager connectionManager,
				  WorkspaceManager workspaceManager){

    super(3, new String[] {SHRINK_WRAP_WORKSPACE,
			   SHRINK_WRAP_WINDOW, 
                           PRINT_WORKSPACE},
	  "CommandShortResource", "CommandLongResource", 
	  null, null, null);

    /*
     * Build the menu/toolbar structure to enforce logical groupings
     * and pull-right menus
     */
    Vector v1 = new Vector(2);
    v1.addElement(SHRINK_WRAP_WORKSPACE);
    v1.addElement(SHRINK_WRAP_WINDOW);
    this.add(v1);
    Vector v2 = new Vector(1);
    v2.addElement(PRINT_WORKSPACE);
    this.add(v2);
     
    frame = parentFrame;
    connectionMgr = connectionManager;
    workspaceMgr = workspaceManager;

    setAvailable(SHRINK_WRAP_WORKSPACE, false);
    setAvailable(SHRINK_WRAP_WINDOW, false);
    setAvailable(PRINT_WORKSPACE, false);
  }

  /**
   * @return A String array containing the keys for the 
   * commands handled by WorkspaceInstanceCommand, which 
   * are: SHRINK_WRAP_WORKSPACE, SHRINK_WRAP_WINDOW, 
   * PRINT_WORKSPACE.
   */
  @Override
  public String[] getKeys(){
    return new String[] {SHRINK_WRAP_WORKSPACE, SHRINK_WRAP_WINDOW,
			 PRINT_WORKSPACE};
  }

  /**
   * Handles ActionEvents where the action command is one of: 
   * SHRINK_WRAP_WORKSPACE, SHRINK_WRAP_WINDOW, PRINT_WORKSPACE
   */
  @Override
  public void actionPerformed(ActionEvent event) {
    String cmdKey = event.getActionCommand();
    if (!isAvailable(cmdKey)) {
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", cmdKey));
    }

    if (cmdKey.equals(SHRINK_WRAP_WORKSPACE))
      handleShrinkWrapWorkspaceCommand(workspaceMgr, 
				       connectionMgr);
    
    else if (cmdKey.equals(SHRINK_WRAP_WINDOW)) 
      handleShrinkWrapWindowCommand(frame, workspaceMgr);
    
    else if (cmdKey.equals(PRINT_WORKSPACE)) 
      handlePrintWorkspaceCommand(frame, workspaceMgr);
  }

  @Override
  public void propertyChange(PropertyChangeEvent e) {
    if (e.getPropertyName().equals(MDIChildFrame.IS_SELECTED_PROPERTY)){
      Boolean selected = (Boolean)e.getNewValue();
      if (selected.booleanValue())
	setWorkspaceInstanceAvailability(true, true, true);
      else
	setWorkspaceInstanceAvailability(false, false, false);
    }
  }

  private void setWorkspaceInstanceAvailability(boolean shrinkWorkspace,
						boolean shrinkWindow,
						boolean printWorkspace){
    setAvailable(SHRINK_WRAP_WORKSPACE, shrinkWorkspace);
    setAvailable(SHRINK_WRAP_WINDOW, shrinkWindow);
    setAvailable(PRINT_WORKSPACE, printWorkspace);
  }   


  // BEGIN: handleShrinkWrapWorkspaceCommand
  protected static void handleShrinkWrapWorkspaceCommand(WorkspaceManager wm,
							 ConnectionManager cm) {
    WorkspaceView wkspView = wm.getActiveWorkspaceView();
    Enumeration e = wkspView.getElements();
    
    WorkspaceElement element = (WorkspaceElement)(e.hasMoreElements() ? e.nextElement() : null);
    Item item = element.getItem();
    try {
      int x = item.getItemXPosition();
      int y = item.getItemYPosition();
      int width = item.getItemWidth();
      int height = item.getItemHeight();
      int lft = x - (width/2);
      int top = y + (height/2);
      int rgt = x + (width/2);
      int bot = y - (height/2);
       
      TwAccess context = cm.getCurrentConnection();
      context.resizeItem(wkspView.getWorkspace(), lft, top, rgt, bot, Symbol.intern("FOO-MODE"));
    }
    catch (G2AccessException ex){
      displayError("", ex.getMessage());
    }
  }
  // END: handleShrinkWrapWorkspaceCommand

  // BEGIN: handleShrinkWrapWindowCommand
  protected static void handleShrinkWrapWindowCommand(MDIFrame frame,
						      WorkspaceManager wm) {
    MDIClient client = frame.getClient(); 
    MDIChildFrame child = client.getActiveFrame();
    wm.shrinkWrapWindow(child);
  }
  // END: handleShrinkWrapWindowCommand

  // BEGIN: handlePrintWorkspaceCommand
  protected static void printComponent(MDIFrame frame, Component component) {
    PrintJob pj
      = component.getToolkit().getPrintJob(frame,
					   "Printing",
					   null);
    if (pj != null) {
      Graphics g = pj.getGraphics();
      if (g != null) {
	component.paint(g);
	g.dispose();
      }
      pj.end();
    }
  }

  protected static void handlePrintWorkspaceCommand (MDIFrame frame,
						     WorkspaceManager wm) {
    WorkspaceView wkspView = wm.getActiveWorkspaceView();
 
    if (wkspView != null){
      printComponent(frame, (Component)wkspView);
    }
  }
  // END: handlePrintWorkspaceCommand

  private static void displayError(String title, String msg) {
     ErrorDialog dlg = new ErrorDialog (title, true, msg, 
					(StandardDialogClient) null);
     dlg.show();
  }
}






