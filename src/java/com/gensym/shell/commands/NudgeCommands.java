/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 NudgeCommands.java
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
import java.awt.event.KeyEvent;
import javax.swing.KeyStroke;
import java.awt.Event;

public class NudgeCommands extends AbstractStructuredCommand implements MDIListener, PropertyChangeListener,SelectionListener {

  public static final String NUDGE_SELECTION_UP    = "NudgeSelectionUp";
  public static final String NUDGE_SELECTION_DOWN  = "NudgeSelectionDown";
  public static final String NUDGE_SELECTION_LEFT  = "NudgeSelectionLeft";
  public static final String NUDGE_SELECTION_RIGHT = "NudgeSelectionRight";

  private static final String shortResource = "LayoutCommandShortResource";
  private static final String longResource  = "LayoutCommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";

  private MDIFrame frame;
  private WorkspaceView workspaceView;
  private WorkspaceElement[] currentSelection;

  public NudgeCommands(MDIFrame frame) {
    super(new StructuredCommandInformation[]{
      new CommandGroupInformation("NudgeGroup", new CommandInformation[]{
	new CommandInformation(NUDGE_SELECTION_UP, true,
			       shortResource, longResource,
			       "nudgeup.gif", null, null, true,
			       mnemonicResource,
			       KeyStroke.getKeyStroke(KeyEvent.VK_UP, Event.CTRL_MASK)),
	  new CommandInformation(NUDGE_SELECTION_DOWN, true,
				 shortResource, longResource,
				 "nudgedown.gif", null, null, true,
				 mnemonicResource,
				 KeyStroke.getKeyStroke(KeyEvent.VK_DOWN, Event.CTRL_MASK)),
	  new CommandInformation(NUDGE_SELECTION_LEFT, true,
				 shortResource, longResource,
				 "nudgeleft.gif", null, null, true,
				 mnemonicResource,
				 KeyStroke.getKeyStroke(KeyEvent.VK_LEFT, Event.CTRL_MASK)),
	  new CommandInformation(NUDGE_SELECTION_RIGHT, true,
				 shortResource, longResource,
				 "nudgeright.gif", null, null, true,
				 mnemonicResource,
				 KeyStroke.getKeyStroke(KeyEvent.VK_RIGHT, Event.CTRL_MASK))})});

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
   setAvailable(NUDGE_SELECTION_UP, state);
   setAvailable(NUDGE_SELECTION_DOWN, state);
   setAvailable(NUDGE_SELECTION_LEFT, state);
   setAvailable(NUDGE_SELECTION_RIGHT, state);
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
      if (cmdKey.equals(NUDGE_SELECTION_UP))
	nudge(selection, 0, 1);
      else if (cmdKey.equals(NUDGE_SELECTION_DOWN))
	nudge(selection, 0, -1);
      else if (cmdKey.equals(NUDGE_SELECTION_LEFT))
	nudge(selection, -1, 0);
      else if (cmdKey.equals(NUDGE_SELECTION_RIGHT))
	nudge(selection, 1, 0);
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }

  private void nudge(Item[] itemsToNudge, int xNudge, int yNudge) throws G2AccessException {
    Item item;
    for (int i=0; i<itemsToNudge.length; i++) {
      item = itemsToNudge[i];
      item.move(item.getItemXPosition() + xNudge, item.getItemYPosition() + yNudge, true);
    }
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











