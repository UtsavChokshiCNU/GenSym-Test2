/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 EditCommands.java
 *
 */
package com.gensym.shell.commands;

import java.awt.Container;
import java.awt.Dimension;
import java.awt.Event;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import java.io.IOException;
import javax.swing.KeyStroke;

import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.dlg.MessageDialog;
import com.gensym.jgi.G2AccessException;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIEvent;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIListener;
import com.gensym.mdi.MDIManager;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.util.Sequence;
import com.gensym.wksp.SelectionCommandGenerator;
import com.gensym.wksp.WorkspaceElement;
import com.gensym.wksp.WorkspaceView;

/**
 * EditCommands contains system-level CUT/COPY/PASTE commands available for
 * G2 items on workspaces.
 */
public final class EditCommands extends AbstractCommand implements SelectionListener, MDIListener, PropertyChangeListener {
  //implements PropertyChangeListener, SelectionListener, ItemListener, MDIListener {

  /** Command key to cut the selected item(s). */
  public static final String CUT_SELECTION = "CutSelection";
  /** Command key to copy the selected item(s). */
  public static final String COPY_SELECTION = "CopySelection";
  /** Command key to paste the selected item(s). */
  public static final String PASTE_SELECTION = "PasteSelection";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";
  private static Resource shortBundle = Resource.getBundle("com/gensym/shell/commands/CommandShortResource");
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");

  private MDIFrame frame = null;
  private WorkspaceView workspaceView = null;
  private WorkspaceElement[] currentSelection = null;

  private static final int offset = 10;
  private static boolean clipboardDataWasCut;

  public EditCommands(){
    this(null);
  }

  /**
   * @param parentFrame The parent frame that is managing the mouse and/or
   * toolbars generated from this command.
   */
  public EditCommands(MDIFrame parentFrame){
    super(new CommandInformation[]{
      new CommandInformation(CUT_SELECTION, true,
			     shortResource, longResource,
			     "cut.gif", null, null, true, mnemonicResource, KeyStroke.getKeyStroke('X', Event.CTRL_MASK)),
	new CommandInformation(COPY_SELECTION, true,
			       shortResource, longResource,
			       "copy.gif", null, null, true, mnemonicResource, KeyStroke.getKeyStroke('C', Event.CTRL_MASK)),
	new CommandInformation(PASTE_SELECTION, false,
			       shortResource, longResource,
			       "paste.gif", null, null, true, mnemonicResource, KeyStroke.getKeyStroke('V', Event.CTRL_MASK))});

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
    if (this.workspaceView != null) {
      this.workspaceView.removeSelectionListener(this);
    }
    this.workspaceView = workspaceView;
    if (this.workspaceView != null) {
      this.workspaceView.addSelectionListener(this);
      currentSelection = workspaceView.getSelection();
    }
    updateAvailability();
  }


  /**
   * Handles ActionEvents where the action command is one of:
   * CUT_SELECTION, COPY_SELECTION, PASTE_SELECTION
   */
  @Override
  public void actionPerformed(ActionEvent event) {
    String cmdKey = event.getActionCommand();
    if (!isAvailable(cmdKey))
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", cmdKey));

    if (cmdKey.equals(CUT_SELECTION)) {
      /*
       * cutSelectionToClipboard is an undocumented method. It may not be
       * supported in future releases of Telewindows2 Toolkit.
       */
      workspaceView.cutSelectionToClipboard();
      clipboardDataWasCut = true;
    }
    else if (cmdKey.equals(COPY_SELECTION)) {
      /*
       * copySelectionToClipboard is an undocumented method. It may not be
       * supported in future releases of Telewindows2 Toolkit.
       */
      workspaceView.copySelectionToClipboard();
      clipboardDataWasCut = false;
    }
    else if (cmdKey.equals(PASTE_SELECTION)) {
      handlePasteSelectionCommand();
      clipboardDataWasCut = false;
    }
  }

  /**
  * @undocumented
  */
  public void updateAvailability(){
    boolean browserMode = false;
    if(com.gensym.core.GensymApplication.getApplication()!= null)
      browserMode = com.gensym.core.GensymApplication.getApplication().isBrowserMode();

    if (workspaceView != null) {
      if (currentSelection == null || currentSelection.length == 0) {
	// there is no selection
	setAvailable(CUT_SELECTION, false);
	setAvailable(COPY_SELECTION, false);
      }
      else {
	// there is a selection
	setAvailable(CUT_SELECTION, !browserMode);
	setAvailable(COPY_SELECTION, !browserMode);
      }

      setAvailable(PASTE_SELECTION, !browserMode);

    } else { // workspaceView == null
      setAvailable(CUT_SELECTION, false);
      setAvailable(COPY_SELECTION, false);
      setAvailable(PASTE_SELECTION, false);
    }
  }

  private void handlePasteSelectionCommand() {
    /*
     * getWorkspaceClipboard is an undocumented method. It may not be
     * supported in future releases of Telewindows2 Toolkit.
     */
    Clipboard clipboard = workspaceView.getWorkspaceClipboard();
    Transferable clipboardContents = clipboard.getContents (workspaceView);
    if (clipboardContents != null) {
      try {
	DataFlavor[] availableFlavors = clipboardContents.getTransferDataFlavors ();
	Item[] pasteData = (Item[])clipboardContents.getTransferData (availableFlavors[0]);

	MDIManager manager = frame.getManager();
	WorkspaceDocument doc = (WorkspaceDocument)manager.getActiveDocument();
	Container contentPane = doc.getContentPane();
	Dimension size = contentPane.getSize();

	Point location = new Point(size.width/2, size.height/2);

	workspaceView.translateWindowToView(location);
	workspaceView.translateViewToWorkspace(location);

	/*
	 * pasteClipboardContents is an undocumented method. It may not be
	 * supported in future releases of Telewindows2 Toolkit.
	 */
	workspaceView.pasteClipboardContents (pasteData, location.x, location.y);
      } catch (IOException ioe) {
	Trace.exception(ioe);
      } catch (UnsupportedFlavorException ufe) {
	Trace.exception(ufe);
      } catch (G2AccessException gae) {
	new MessageDialog(frame, i18n.getString("ClipboardMessage"), true,
			  gae.getMessage(), null).setVisible(true);
	//Trace.exception(gae);
      }
    } else {
      new MessageDialog(frame, i18n.getString("ClipboardMessage"), true,
			i18n.getString("ClipboardEmpty"), null).setVisible(true);
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
      WorkspaceDocument workspaceDocument = (WorkspaceDocument)document;
      workspaceDocument.addPropertyChangeListener(this);
      setWorkspaceView(workspaceDocument.getWorkspaceView());
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
}







