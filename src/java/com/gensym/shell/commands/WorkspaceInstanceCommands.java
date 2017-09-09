/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceInstanceCommands.java
 *
 */
package com.gensym.shell.commands;

import java.awt.Event;
import java.awt.Component;
import java.awt.Graphics;
import java.awt.PrintJob;
import java.awt.event.ActionEvent;
import java.awt.print.PrinterJob;
import java.awt.print.PrinterException;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import javax.swing.KeyStroke;
import com.gensym.core.GensymApplication;
import com.gensym.dlg.CommandConstants;
import com.gensym.dlg.QuestionDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.jgi.G2AccessException;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIEvent;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIListener;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.util.Structure;
import com.gensym.util.WorkspaceEvent;
import com.gensym.util.WorkspaceListener;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.util.symbol.AttributeExportSymbols;
import com.gensym.wksp.WorkspaceElement;
import com.gensym.wksp.WorkspaceView;
import com.gensym.wksp.ScalableWorkspaceView;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;

/**
 * WorkspaceInstanceCommands contains commands for the
 * following WorkspaceView-type actions: Print <p>
 *
 * Users can generate menus and/or toolbars for all, or part, of these
 * commands.<p>
 */
public final class WorkspaceInstanceCommands extends AbstractStructuredCommand
implements PropertyChangeListener, MDIListener, WorkspaceListener {
  /** Command key to print a kb-workspace. */
  public static final String PRINT_WORKSPACE = "PrintWorkspace";
  /** Command key to enable the workspace associated with the active WorkspaceView. */
  public static final String ENABLE_WORKSPACE = "EnableWorkspace";
  /** Command key to disable the workspace associated with the active WorkspaceView. */
  public static final String DISABLE_WORKSPACE = "DisableWorkspace";
  /** Command key to delete the workspace associated with the active WorkspaceView. */
  public static final String DELETE_WORKSPACE = "DeleteWorkspace";
  /** Command key to display the properties for the workspace associated with the active WorkspaceView. */
  public static final String WORKSPACE_PROPERTIES = "WorkspaceProperties";
  /** Command key to shrink-wrap the workspace associated with the active WorkspaceView. */
  public static final String SHRINK_WRAP_WORKSPACE = "ShrinkWrapWorkspace";
  /** Command key to select all item on the workspace associated with the active WorkspaceView. */
  public static final String SELECT_ALL_WORKSPACE_ITEMS = "SelectAllWorkspaceItems";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";
  private static Resource shortBundle = Resource.getBundle("com/gensym/shell/commands/CommandShortResource");
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");

  private MDIFrame frame = null;
  private WorkspaceView workspaceView = null;
  private WorkspaceDocument wkspDocument = null;
  private WorkspaceElement[] currentSelection = null;

  private StandardDialogClient dlgClient;

  public WorkspaceInstanceCommands(){
    this(null);
  }

  /**
   * @param parentFrame The parent frame that is managing the mouse and/or
   * toolbars generated from this command.
   */
  public WorkspaceInstanceCommands(MDIFrame parentFrame){
    super(new StructuredCommandInformation[]{
      new CommandGroupInformation("miscGroup", new CommandInformation[]{
	new CommandInformation(PRINT_WORKSPACE, true,
			       shortResource, longResource,
			       "print.gif", null, null, false, mnemonicResource, KeyStroke.getKeyStroke('P', Event.CTRL_MASK)),
	  new CommandInformation(SHRINK_WRAP_WORKSPACE, true,
				 shortResource, longResource,
				 "shrink_wrap.gif", null, null, true, mnemonicResource, null)}),

	new CommandGroupInformation("enableGroup", new CommandInformation[]{
	  new CommandInformation(ENABLE_WORKSPACE, true,
				 shortResource, longResource,
				 "workspace.gif", null, null, true, mnemonicResource, null),
	    new CommandInformation(DISABLE_WORKSPACE, true,
				   shortResource, longResource,
				   "no_workspace.gif", null, null, true, mnemonicResource, null)}),

	  new CommandGroupInformation("deleteGroup", new CommandInformation[]{
	    new CommandInformation(DELETE_WORKSPACE, true,
				   shortResource, longResource,
				   "delete.gif", null, null, true, mnemonicResource, null),
	      new CommandInformation(SELECT_ALL_WORKSPACE_ITEMS, true,
				     shortResource, longResource,
				     "select_all.gif", null, null, true, mnemonicResource, KeyStroke.getKeyStroke('A', Event.CTRL_MASK))}),

	    new CommandGroupInformation("propertiesGroup", new CommandInformation[]{
	      new CommandInformation(WORKSPACE_PROPERTIES, true,
				     shortResource, longResource,
				     "properties.gif", null, null, false, mnemonicResource, null)})});

    if (parentFrame != null){
      frame = parentFrame;
      frame.getManager().addMDIListener(this);
      MDIDocument[] docs = frame.getManager().getDocuments();
      for (int i=0; i<docs.length; i++){
	if (docs[i] instanceof WorkspaceDocument)
	  docs[i].addPropertyChangeListener(this);
      }
      dlgClient = new DialogClient();
      updateAvailability();
    }
  }

  public void setWorkspaceDocument(WorkspaceDocument wkspDoc){
    wkspDocument = wkspDoc;
  }

  public void setWorkspaceView(WorkspaceView workspaceView) {
    KbWorkspace kbWorkspace;
    if (this.workspaceView != null) {
      try {
	kbWorkspace = this.workspaceView.getWorkspace();
	if (kbWorkspace != null)
	  kbWorkspace.removeWorkspaceListener(this);
      } catch (G2AccessException ex) {
	Trace.exception(ex);
      }
    }
    this.workspaceView = workspaceView;
    if (this.workspaceView != null) {
      try {
	kbWorkspace = this.workspaceView.getWorkspace();
	if (kbWorkspace != null)
	  kbWorkspace.addWorkspaceListener(this);
      } catch (G2AccessException ex) {
	Trace.exception(ex);
      }
    }
    updateAvailability();
  }


  /**
   * Handles ActionEvents where the action command is one of:
   * PRINT_WORKSPACE
   */
  @Override
  public void actionPerformed(ActionEvent event) {
    String cmdKey = event.getActionCommand();
    if (!isAvailable(cmdKey))
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", cmdKey));

    if (cmdKey.equals(PRINT_WORKSPACE))
      handlePrintWorkspaceCommand();

    else if (cmdKey.equals(ENABLE_WORKSPACE)) {
      try {
	workspaceView.getWorkspace().enable();
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    else if (cmdKey.equals(DISABLE_WORKSPACE)) {
      try {
	workspaceView.getWorkspace().disable();
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    else if (cmdKey.equals(DELETE_WORKSPACE)) {
      QuestionDialog dlg = new QuestionDialog(frame, shortBundle.getString("StandardDialogTitle"),
					      true, shortBundle.getString("PromptToDeleteWorkspace"),
					      dlgClient);
      dlg.setVisible(true);
    }

    else if (cmdKey.equals(WORKSPACE_PROPERTIES))
      handleWorkspacePropertiesCommand(workspaceView);

    else if (cmdKey.equals(SHRINK_WRAP_WORKSPACE)) {
      try {
	workspaceView.shrinkWrap();
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    else if (cmdKey.equals(SELECT_ALL_WORKSPACE_ITEMS)) {
      workspaceView.selectAll();
    }
  }

  /**
   * @undocumented
  */
  public void updateAvailability(){
    boolean browserMode = false;
    if(com.gensym.core.GensymApplication.getApplication()!= null)
     browserMode = com.gensym.core.GensymApplication.getApplication().isBrowserMode();

    // PRINT_WORKSPACE is available as long as the workspaceView has focus
    setAvailable(PRINT_WORKSPACE, (workspaceView != null));
    setAvailable(SHRINK_WRAP_WORKSPACE, (workspaceView != null));
    setAvailable(SELECT_ALL_WORKSPACE_ITEMS, (workspaceView != null) && !browserMode);

    // DELETE_WORKSPACE, WORKSPACE_PROPERTIES might be a victim of a race condition during delete
    if (workspaceView != null) {
      setAvailable(DELETE_WORKSPACE, ((workspaceView.getWorkspace()) != null));
      setAvailable(WORKSPACE_PROPERTIES, ((workspaceView.getWorkspace()) != null));
    }
    else {
      setAvailable(DELETE_WORKSPACE, false);
      setAvailable(WORKSPACE_PROPERTIES, false);
    }

    // ENABLE/DISABLE selection are conditional based on the current
    // state of the selection
    if (workspaceView != null && workspaceView.getWorkspace() != null) {
      try {
	if (!workspaceView.getWorkspace().getManuallyDisabled()) {
	  setAvailable(ENABLE_WORKSPACE, false);
	  setAvailable(DISABLE_WORKSPACE, !browserMode);
	} else {
	  setAvailable(ENABLE_WORKSPACE, !browserMode);
	  setAvailable(DISABLE_WORKSPACE, false);
	}
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    } else {
      setAvailable(ENABLE_WORKSPACE, false);
      setAvailable(DISABLE_WORKSPACE, false);
    }
  }

  // BEGIN: handlePrintWorkspaceCommand
  protected void printComponent(MDIFrame frame, Component component) {
    if (frame == null) return;
    if (component instanceof ScalableWorkspaceView) {
      final PrinterJob printJob = PrinterJob.getPrinterJob();
      printJob.setPageable((ScalableWorkspaceView)component);
      if(printJob.printDialog()) {
	new Thread(new Runnable(){
	    @Override
	    public void run(){
	      try{
		printJob.print();
	      } catch(PrinterException ex) {
		ex.printStackTrace();
	      }
	    }
	  }).start();
      }
    } else {
      PrintJob printJob = component.getToolkit().getPrintJob(frame,
							     "Printing",
							     null);
      if (printJob != null) {
	Graphics graphics = printJob.getGraphics();
	if (graphics != null) {
	  component.paint(graphics);
	  graphics.dispose();
	}
	printJob.end();
      }
    }
  }

  protected void handlePrintWorkspaceCommand () {
    printComponent(frame, (Component)workspaceView);
  }
  // END: handlePrintWorkspaceCommand

  private void handleWorkspacePropertiesCommand(Component requestingComponent) {
     KbWorkspace kbWorkspace = workspaceView.getWorkspace();
     TW2MDIApplication app = (TW2MDIApplication)GensymApplication.getApplication();
     TwAccess context = app.getConnectionManager().getCurrentConnection();
     com.gensym.dlgruntime.DialogManager dlgManager = context.getDialogManager();

     try {
       com.gensym.util.Symbol userMode = context.getUserMode();
       try {
	 dlgManager.editItem (requestingComponent, kbWorkspace, userMode, java.util.Locale.getDefault());
       } catch (com.gensym.dlgruntime.ResourceInstantiationException rex) {
	 Trace.exception(rex);
       } catch (java.net.MalformedURLException uex) {
	 Trace.exception(uex);
       }
     } catch (G2AccessException gae) {
       Trace.exception(gae);
     }
  }

  // BEGIN: MDIListener methods
  @Override
  public void documentAdded(MDIEvent event) {
    MDIDocument document = (MDIDocument)event.getDocument();
    if (document instanceof WorkspaceDocument) {
      WorkspaceDocument wkspDoc = (WorkspaceDocument)document;
      wkspDoc.addPropertyChangeListener(this);
      setWorkspaceView(wkspDoc.getWorkspaceView());
      setWorkspaceDocument(wkspDoc);
    }
  }
  // END: MDIListener methods

  // BEGIN: PropertyChangeListener methods
  @Override
  public void propertyChange(PropertyChangeEvent e) {
    WorkspaceDocument document = (WorkspaceDocument)e.getSource();
    if (e.getPropertyName().equals(WorkspaceDocument.IS_SELECTED_PROPERTY)){
      Boolean selected = (Boolean)e.getNewValue();
      if (selected.booleanValue()){
	setWorkspaceView(document.getWorkspaceView());
	setWorkspaceDocument(document);
      }
      else
	setWorkspaceView(null);
    }
    else if (e.getPropertyName().equals(WorkspaceDocument.IS_CLOSED_PROPERTY)){
      try{
	WorkspaceView view = document.getWorkspaceView();
	if (view != null){
	  KbWorkspace wksp = view.getWorkspace();
	  if (wksp != null)
	    wksp.removeWorkspaceListener(this);
	}
      }
      catch(G2AccessException ex){
	Trace.exception(ex);
      }
    }
  }
  // END: PropertyChangeListener methods

  // START: WorkspaceListener methods
  /**
   * @undocumented
   */
  @Override
  public void receivedInitialDownload (WorkspaceEvent event){}

  /**
   * @undocumented
   */
  @Override
  public void workspaceItemAdded (WorkspaceEvent event){}

  /**
   * @undocumented
   */
  @Override
  public void workspaceItemRemoved (WorkspaceEvent event){}

  /**
   * @undocumented
   */
  @Override
  public void workspaceResized (WorkspaceEvent event){}

  /**
   * @undocumented
   */
  @Override
  public void workspaceItemMoved (WorkspaceEvent event){}

  /**
   * @undocumented
   */
  @Override
  public void workspaceItemResized (WorkspaceEvent event){}

  /**
   * @undocumented
   */
  @Override
  public void workspaceItemRotated (WorkspaceEvent event){}

  /**
   * @undocumented
   */
  @Override
  public void workspaceItemColorsChanged (WorkspaceEvent event){}

  /**
   * @undocumented
   */
  @Override
  public void workspaceItemIconVariablesChanged (WorkspaceEvent event){}

  /**
   * @undocumented
   */
  @Override
  public void workspaceItemAttributesChanged (WorkspaceEvent event) {
    Item targetItem = event.getItem ();
    if (targetItem == null ||
	!(targetItem.equals (event.getSource ())))
      return;
    Structure eventInfo = event.getInfo ();
    if (SystemAttributeSymbols.MANUALLY_DISABLEDQ_.equals
	(eventInfo.getAttributeValue(AttributeExportSymbols.ATTRIBUTE_NAME_, null)))
      updateAvailability();
  }

  // END: WorkspaceListener methods

  class DialogClient implements StandardDialogClient {
    @Override
    public void dialogDismissed (StandardDialog dlg, int cmdCode) {
      dlg.setVisible(false);
      if (dlg.wasCancelled()) return;
      if (cmdCode == CommandConstants.YES) {
	try {
	  workspaceView.getWorkspace().delete(true, true);
	} catch (G2AccessException gae) {
	  Trace.exception(gae);
	}
      }
    }
  }

}







