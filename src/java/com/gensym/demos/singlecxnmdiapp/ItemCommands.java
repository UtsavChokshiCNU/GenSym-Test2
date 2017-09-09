/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ItemsCommands.java
 *
 */
package com.gensym.demos.singlecxnmdiapp;

import java.awt.event.ActionEvent;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;

import com.gensym.classes.KbWorkspace;
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
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.util.ItemEvent;
import com.gensym.util.ItemListener;
import com.gensym.util.Symbol;
import com.gensym.wksp.WorkspaceElement;
import com.gensym.wksp.WorkspaceView;

/**
 * ItemCommands contains commands for the system-level commands available for
 * G2 items on workspaces. 
 */
public final class ItemCommands extends AbstractStructuredCommand 
implements PropertyChangeListener, SelectionListener, ItemListener, MDIListener {

  /** Command key to enable the selected item(s). */
  public static final String ENABLE_SELECTION = "EnableSelection";
  /** Command key to disable the selected item(s). */
  public static final String DISABLE_SELECTION = "DisableSelection";
  

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static Resource shortBundle = Resource.getBundle("com/gensym/demos/singlecxnmdiapp/CommandShortResource");
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");

  private static final int SELECTION_DISABLED = 0;
  private static final int SELECTION_ENABLED = 1;

  private static final int SELECTION_MIXED = 2;

  private MDIFrame frame = null;
  private WorkspaceView workspaceView = null;
  private WorkspaceElement[] currentSelection = null;
 
  public ItemCommands(){
    this(null);
  }

  /**
   * @param parentFrame The parent frame that is managing the mouse and/or
   * toolbars generated from this command. 
   */
  public ItemCommands(MDIFrame parentFrame){
    super(new StructuredCommandInformation[]{
	new CommandGroupInformation("EnableGroup", new CommandInformation[]{
	  new CommandInformation(ENABLE_SELECTION, true,
				 shortResource, longResource,
				 null, null, null, true),
	    new CommandInformation(DISABLE_SELECTION, true,
				   shortResource, longResource,
				   null, null, null, true)})});
	
    if (parentFrame != null){
      frame = parentFrame;
      frame.getManager().addMDIListener(this);
      MDIDocument[] docs = frame.getManager().getDocuments();
      for (int i=0; i<docs.length; i++){
	if (docs[i] instanceof WorkspaceDocument)
	  docs[i].addPropertyChangeListener(this);
      }
      updateAvailability();
    }
  }

  public void setWorkspaceView(WorkspaceView workspaceView) {
    KbWorkspace kbWorkspace;
    if (this.workspaceView != null) {
      this.workspaceView.removeSelectionListener(this);
      try {
	kbWorkspace = this.workspaceView.getWorkspace();
	if (kbWorkspace != null)
	  kbWorkspace.removeItemListener(this);
      } catch (G2AccessException ex) {
	Trace.exception(ex);
      }
    }
    this.workspaceView = workspaceView;
    if (this.workspaceView != null) {
      this.workspaceView.addSelectionListener(this);
      try {
	kbWorkspace = this.workspaceView.getWorkspace();
	if (kbWorkspace != null)
	  kbWorkspace.addItemListener(this);
      } catch (G2AccessException ex) {
	Trace.exception(ex);
      }
    }
    updateAvailability();
  }

  @Override
  public void actionPerformed(ActionEvent event) {
    String cmdKey = event.getActionCommand();
    if (!isAvailable(cmdKey)) 
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", cmdKey));

    if (cmdKey.equals(ENABLE_SELECTION))
      handleEnableSelectionCommand();
    else if (cmdKey.equals(DISABLE_SELECTION))
      handleDisableSelectionCommand();
  }

  private void updateAvailability(){
    if (workspaceView != null) {
      if (currentSelection == null || currentSelection.length == 0) {
	// there is no selection
	setAvailable(ENABLE_SELECTION, false);
	setAvailable(DISABLE_SELECTION, false);
      }
      else {
	// there is a selection: is the selection enabled/disabled/mixed?
	int status = getSelectionEnabledStatus();
	if (status == SELECTION_ENABLED) {
	  setAvailable(ENABLE_SELECTION, false);
	  setAvailable(DISABLE_SELECTION, true);
	} else if (status == SELECTION_DISABLED) {
	  setAvailable(ENABLE_SELECTION, true);
	  setAvailable(DISABLE_SELECTION, false);
	} else {
	  setAvailable(ENABLE_SELECTION, false);
	  setAvailable(DISABLE_SELECTION, false);
	}
      }
    } else { // workspaceView == null
      setAvailable(ENABLE_SELECTION, false);
      setAvailable(DISABLE_SELECTION, false);
    }
  } 

  private int getSelectionEnabledStatus() {
    int status = SELECTION_MIXED;

    int numEnabled = 0;
    for (int i=0; i<currentSelection.length; i++) {    
      try {
	if (currentSelection[i].getItem().isEnabled())
	  numEnabled = numEnabled + 1;
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    if (currentSelection.length != 0) {
      if (numEnabled == currentSelection.length) { 
	// disable ENABLE, enable DISABLE
	status = SELECTION_ENABLED;
      } else if (numEnabled == 0) {
	// enable ENABLE, disable DISABLE
	status = SELECTION_DISABLED;
      } else status = SELECTION_MIXED;
    } 
   
    return status;
  }

  private void handleEnableSelectionCommand() {
    try {
      if (currentSelection.length == 0) 
	workspaceView.getWorkspace().enable();
      else {
	for (int i=0; i<currentSelection.length; i++) 
	  currentSelection[i].getItem().enable();
      }
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }

  private void handleDisableSelectionCommand() {
    try {
      if (currentSelection.length == 0)
	workspaceView.getWorkspace().disable();
      else {
	for (int i=0; i<currentSelection.length; i++)
	  currentSelection[i].getItem().disable();
      }
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }

  // BEGIN: SelectionListener methods
  @Override
  public void selectionChanged(SelectionEvent event){
    try {
      if (currentSelection != null) {
	for (int i=0; i<currentSelection.length; i++)
	  currentSelection[i].getItem().removeItemListener(this);
      }
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }

    currentSelection = workspaceView.getSelection();

    try {
      if (currentSelection != null) {
	for (int i=0; i<currentSelection.length; i++)
	  currentSelection[i].getItem().addItemListener(this);
      }
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }

    updateAvailability();
  }
  // END: SelectionListener methods

  // BEGIN: MDIListener methods
  @Override
  public void documentAdded(MDIEvent event) {
    MDIDocument document = (MDIDocument)event.getDocument();
    if (document instanceof WorkspaceDocument) {
      WorkspaceDocument wkspDoc = (WorkspaceDocument)document;
      wkspDoc.addPropertyChangeListener(this);
      setWorkspaceView(wkspDoc.getWorkspaceView());
    }
  }
  // END: MDIListener methods

  // BEGIN: PropertyChangeListener methods
  @Override
  public void propertyChange(PropertyChangeEvent e) {
    WorkspaceDocument document = (WorkspaceDocument)e.getSource();
    if (e.getPropertyName().equals(WorkspaceDocument.IS_SELECTED_PROPERTY)){
      Boolean selected = (Boolean)e.getNewValue();
      if (selected.booleanValue())
	setWorkspaceView(document.getWorkspaceView());
      else
	setWorkspaceView(null);
    }
  }
  // END: PropertyChangeListener methods

  // BEGIN: ItemListener methods
  @Override
  public void receivedInitialValues (ItemEvent e) {}
  @Override
  public void itemDeleted (ItemEvent e) {}
  @Override
  public void itemModified (ItemEvent e) {
    updateAvailability();
  }
  // END: ItemListener methods
}







