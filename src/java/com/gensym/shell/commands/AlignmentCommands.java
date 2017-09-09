/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 AlignmentCommands.java
 *
 */
package com.gensym.shell.commands;

import java.awt.event.ActionEvent;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;

import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.jgi.G2AccessException;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIEvent;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIListener;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ntw.util.uitools.ItemLayoutTools;
import com.gensym.wksp.WorkspaceElement;
import com.gensym.wksp.WorkspaceView;

public class AlignmentCommands extends AbstractStructuredCommand implements MDIListener, PropertyChangeListener, SelectionListener {

  public static final String ALIGN_LEFT   = "AlignLeft";
  public static final String ALIGN_CENTER = "AlignCenter";
  public static final String ALIGN_RIGHT  = "AlignRight";

  public static final String ALIGN_TOP    = "AlignTop";
  public static final String ALIGN_MIDDLE = "AlignMiddle";
  public static final String ALIGN_BOTTOM = "AlignBottom";

  public static final String DISTRIBUTE_VERTICALLY   = "DistributeVertically";
  public static final String DISTRIBUTE_HORIZONTALLY = "DistributeHorizontally";

  private static final String shortResource = "LayoutCommandShortResource";
  private static final String longResource = "LayoutCommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";

  private MDIFrame frame;
  private WorkspaceView workspaceView;
  private WorkspaceElement[] currentSelection;

  public AlignmentCommands(MDIFrame frame) {
    super(new StructuredCommandInformation[]{
      new CommandGroupInformation("VerticalAlignmentGroup", new CommandInformation[]{
	new CommandInformation(ALIGN_LEFT, true,
			       shortResource, longResource,
			       "alignleft.gif", null, null, true,
			       mnemonicResource, null),
	  new CommandInformation(ALIGN_CENTER, true,
				 shortResource, longResource,
				 "aligncenter.gif", null, null, true,
				 mnemonicResource, null),
	  new CommandInformation(ALIGN_RIGHT, true,
				 shortResource, longResource,
				 "alignright.gif", null, null, true,
				 mnemonicResource, null)}),

	new CommandGroupInformation("HorizontalAlignmentGroup", new CommandInformation[]{
	  new CommandInformation(ALIGN_TOP, true,
				 shortResource, longResource,
				 "aligntop.gif", null, null, true,
				 mnemonicResource, null),
	    new CommandInformation(ALIGN_MIDDLE, true,
				   shortResource, longResource,
				   "alignmiddle.gif", null, null, true,
				   mnemonicResource, null),
	    new CommandInformation(ALIGN_BOTTOM, true,
				   shortResource, longResource,
				   "alignbottom.gif", null, null, true,
				   mnemonicResource, null)}),

	  new CommandGroupInformation("DistributionGroup", new CommandInformation[]{
	    new CommandInformation(DISTRIBUTE_HORIZONTALLY, true,
				   shortResource, longResource,
				   "distribhorz.gif", null, null, true),
	      new CommandInformation(DISTRIBUTE_VERTICALLY, true,
				     shortResource, longResource,
				     "distribvert.gif", null, null, true,
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

    boolean state = false;
    if (!browserMode && workspaceView != null && currentSelection != null) {
      if (currentSelection.length > 1)
        state = true;
    }

    setAvailable(ALIGN_LEFT, state);
    setAvailable(ALIGN_CENTER, state);
    setAvailable(ALIGN_RIGHT, state);
    setAvailable(ALIGN_TOP, state);
    setAvailable(ALIGN_MIDDLE, state);
    setAvailable(ALIGN_BOTTOM, state);

      state = false;
    if (!browserMode && workspaceView != null && currentSelection != null) {
      if (currentSelection.length > 2)
        state = true;
    }
    setAvailable(DISTRIBUTE_VERTICALLY, state);
    setAvailable(DISTRIBUTE_HORIZONTALLY, state);
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
      if (cmdKey.equals(ALIGN_LEFT))
	ItemLayoutTools.align(selection, ItemLayoutTools.ALIGN_LEFTS);
      else if (cmdKey.equals(ALIGN_CENTER))
	ItemLayoutTools.align(selection, ItemLayoutTools.ALIGN_CENTERS);
      else if (cmdKey.equals(ALIGN_RIGHT))
	ItemLayoutTools.align(selection, ItemLayoutTools.ALIGN_RIGHTS);
      else if (cmdKey.equals(ALIGN_TOP))
	ItemLayoutTools.align(selection, ItemLayoutTools.ALIGN_TOPS);
      else if (cmdKey.equals(ALIGN_MIDDLE))
	ItemLayoutTools.align(selection, ItemLayoutTools.ALIGN_MIDDLES);
      else if (cmdKey.equals(ALIGN_BOTTOM))
	ItemLayoutTools.align(selection, ItemLayoutTools.ALIGN_BOTTOMS);
      else if (cmdKey.equals(DISTRIBUTE_HORIZONTALLY))
	ItemLayoutTools.distribute(selection, ItemLayoutTools.DISTRIBUTE_HORIZONTALLY);
      else if (cmdKey.equals(DISTRIBUTE_VERTICALLY))
	ItemLayoutTools.distribute(selection, ItemLayoutTools.DISTRIBUTE_VERTICALLY);
    } catch (G2AccessException gae) {
      Trace.exception(gae);
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
    else if (e.getPropertyName().equals(WorkspaceDocument.IS_CLOSED_PROPERTY))
      setWorkspaceView(null);
  }

}











