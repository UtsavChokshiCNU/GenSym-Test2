/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 RotateCommands.java
 *
 */
package com.gensym.shell.commands;

import java.awt.event.ActionEvent;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;

import com.gensym.classes.Entity;
import com.gensym.classes.Item;
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

public class RotateCommands extends AbstractStructuredCommand implements MDIListener, PropertyChangeListener,  SelectionListener {

  public static final String ROTATE_90_CLOCKWISE         = "Rotate90Clockwise";
  public static final String ROTATE_90_COUNTER_CLOCKWISE = "Rotate90CounterClockwise";
  public static final String ROTATE_180_DEGREES          = "Rotate180Degrees";

  public static final String FLIP_VERTICAL               = "FlipVertical";
  public static final String FLIP_HORIZONTAL             = "FlipHorizontal";

  private static final int   FLIP_SELECTION_VERTICALLY   = 1;
  private static final int   FLIP_SELECTION_HORIZONTALLY = 2;

  private static final String shortResource = "LayoutCommandShortResource";
  private static final String longResource  = "LayoutCommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";

  private MDIFrame frame;
  private WorkspaceView workspaceView;
  private WorkspaceElement[] currentSelection;

  public RotateCommands(MDIFrame frame) {
    super(new StructuredCommandInformation[]{
      new CommandGroupInformation("RotateGroup", new CommandInformation[]{
	new CommandInformation(ROTATE_90_CLOCKWISE, true,
			       shortResource, longResource,
			       "clockwise.gif", null, null, true,
			       mnemonicResource, null),
	  new CommandInformation(ROTATE_90_COUNTER_CLOCKWISE, true,
				 shortResource, longResource,
				 "counterclockwise.gif", null, null, true,
				 mnemonicResource, null),
	  new CommandInformation(ROTATE_180_DEGREES, true,
				 shortResource, longResource,
				 "rotate180.gif", null, null, true,
				 mnemonicResource, null)}),

	new CommandGroupInformation("FlipGroup", new CommandInformation[]{
	  new CommandInformation(FLIP_VERTICAL, true,
				 shortResource, longResource,
				 "flipvertical.gif", null, null, true,
				 mnemonicResource, null),
	    new CommandInformation(FLIP_HORIZONTAL, true,
				   shortResource, longResource,
				   "fliphorizontal.gif", null, null, true,
				   mnemonicResource, null)})});

    if (frame != null) {
      this.frame = frame;
      frame.getManager().addMDIListener(this);
      MDIDocument[] docs = frame.getManager().getDocuments();
      for (int i=0; i<docs.length; i++) {
	if (docs[i] instanceof WorkspaceDocument)
	  docs[i].addPropertyChangeListener(this);
      }
    }

    updateAvailability();
  }

  /**
  * @undocumented
  */
  public void updateAvailability() {
   boolean browserMode = false;
   if(com.gensym.core.GensymApplication.getApplication()!= null)
     browserMode = com.gensym.core.GensymApplication.getApplication().isBrowserMode();

   boolean state = !browserMode && ((!(workspaceView == null)) && (!(currentSelection == null || currentSelection.length == 0)));

   setAvailable(ROTATE_90_CLOCKWISE, state);
   setAvailable(ROTATE_90_COUNTER_CLOCKWISE, state);
   setAvailable(ROTATE_180_DEGREES, state);
   setAvailable(FLIP_VERTICAL, state);
   setAvailable(FLIP_HORIZONTAL, state);
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
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();

    Item[] selection = new Item[currentSelection.length];
    for (int i=0; i<currentSelection.length; i++)
      selection[i] = currentSelection[i].getItem();

    try {
      if (cmdKey.equals(ROTATE_90_CLOCKWISE))
	rotate(selection, 90);
      else if (cmdKey.equals(ROTATE_90_COUNTER_CLOCKWISE))
	rotate(selection, -90);
      else if (cmdKey.equals(ROTATE_180_DEGREES))
	rotate(selection, 180);
      else if (cmdKey.equals(FLIP_VERTICAL))
	reflect(selection, FLIP_SELECTION_VERTICALLY);
      else if (cmdKey.equals(FLIP_HORIZONTAL))
	reflect(selection, FLIP_SELECTION_HORIZONTALLY);
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }

  private void rotate(Item[] itemsToRotate, int degrees) throws G2AccessException {
    int currentValue;
    for (int i=0; i<itemsToRotate.length; i++) {
      currentValue = ((Entity)itemsToRotate[i]).getIconHeading();
      currentValue += degrees;
      ((Entity)itemsToRotate[i]).setIconHeading(currentValue);
    }
  }

  private void reflect(Item[] itemsToReflect, int reflectCode) throws G2AccessException {
    for (int i=0; i<itemsToReflect.length; i++) {
      if (reflectCode == FLIP_SELECTION_VERTICALLY) {
	((Entity)itemsToReflect[i]).reflectHorizontally();
      } else {
	((Entity)itemsToReflect[i]).reflectVertically();
      }
    }
  }

 // BEGIN: SelectionListener methods
  @Override
  public void selectionChanged(SelectionEvent event){
	if (workspaceView != null)
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











