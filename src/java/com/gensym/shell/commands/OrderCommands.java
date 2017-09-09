/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 OrderCommands.java
 *
 */
package com.gensym.shell.commands;

import java.awt.event.ActionEvent;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import com.gensym.classes.KbWorkspace;
import com.gensym.jgi.G2AccessException;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIEvent;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIListener;
import com.gensym.message.Trace;
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.wksp.WorkspaceElement;
import com.gensym.wksp.WorkspaceView;

public final class OrderCommands extends AbstractStructuredCommand implements PropertyChangeListener, SelectionListener, MDIListener {

  /** Command key to lift the selected item(s) to the top of the drawing order. */
  public static final String LIFT_SELECTION_TO_TOP = "LiftSelectionToTop";
  /** Command key to drop the selected item(s) to the bottom of the drawing order. */
  public static final String DROP_SELECTION_TO_BOTTOM = "DropSelectionToBottom";

  private static final String shortResource = "LayoutCommandShortResource";
  private static final String longResource = "LayoutCommandLongResource";
    private static final String mnemonicResource = "MnemonicResource";

  private MDIFrame frame;
  private WorkspaceView workspaceView = null;
  private WorkspaceElement[] currentSelection = null;

  public OrderCommands(){
    this(null);
  }

  /**
   * @param parentFrame The parent frame that is managing the mouse and/or
   * toolbars generated from this command.
   */
  public OrderCommands(MDIFrame parentFrame){
    super(new StructuredCommandInformation[]{
      new CommandGroupInformation("DrawingOrderGroup", new CommandInformation[]{
	new CommandInformation(LIFT_SELECTION_TO_TOP, true,
			       shortResource, longResource,
			       "lift_to_top.gif", null, null, true,
			       mnemonicResource, null),
	  new CommandInformation(DROP_SELECTION_TO_BOTTOM, true,
				 shortResource, longResource,
				 "drop_to_bottom.gif", null, null, true,
				 mnemonicResource, null)})});

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
    if (this.workspaceView != null)
      this.workspaceView.removeSelectionListener(this);
    this.workspaceView = workspaceView;
    if (this.workspaceView != null) {
      this.workspaceView.addSelectionListener(this);
      currentSelection = workspaceView.getSelection();
    }
    updateAvailability();
  }

  @Override
  public void actionPerformed(ActionEvent event) {
    String cmdKey = event.getActionCommand();
    if (cmdKey.equals(LIFT_SELECTION_TO_TOP))
      handleLiftSelectionToTopCommand();
    else if (cmdKey.equals(DROP_SELECTION_TO_BOTTOM))
      handleDropSelectionToBottomCommand();
  }

  /**
   * @undocumented
   */
  public void updateAvailability(){
    boolean browserMode = false;
    if(com.gensym.core.GensymApplication.getApplication()!= null)
     browserMode = com.gensym.core.GensymApplication.getApplication().isBrowserMode();

    if (!browserMode && workspaceView != null) {
      if (currentSelection == null || currentSelection.length == 0) {
	// there is no selection
	setAvailable(LIFT_SELECTION_TO_TOP, false);
	setAvailable(DROP_SELECTION_TO_BOTTOM, false);
      }
      else {
	// there is a selection
	setAvailable(LIFT_SELECTION_TO_TOP, true);
	setAvailable(DROP_SELECTION_TO_BOTTOM, true);
      }
    } else { // workspaceView == null
      setAvailable(LIFT_SELECTION_TO_TOP, false);
      setAvailable(DROP_SELECTION_TO_BOTTOM, false);
    }
  }

  private void handleLiftSelectionToTopCommand() {
    workspaceView.liftSelectionToTop();
  }

  private void handleDropSelectionToBottomCommand() {
    workspaceView.dropSelectionToBottom();
  }

  // BEGIN: SelectionListener methods
  @Override
  public void selectionChanged(SelectionEvent event){
    currentSelection = workspaceView.getSelection();
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
    else if (e.getPropertyName().equals(WorkspaceDocument.IS_CLOSED_PROPERTY)){
      setWorkspaceView(null);
      updateAvailability();
    }
  }
  // END: PropertyChangeListener methods

}






