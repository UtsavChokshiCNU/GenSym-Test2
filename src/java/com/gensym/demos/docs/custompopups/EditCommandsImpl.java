package com.gensym.demos.docs.custompopups;

import java.awt.Container;
import java.awt.Frame;
import java.awt.Dimension;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.Image;
import java.awt.Toolkit;
import java.io.IOException;

import com.gensym.classes.Item;
import com.gensym.dlg.MessageDialog;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.ui.Command;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.CommandListener;
import com.gensym.ui.StructuredCommandListener;
import com.gensym.util.Sequence;
import com.gensym.wksp.SelectionCommandGenerator;
import com.gensym.wksp.WorkspaceElement;
import com.gensym.wksp.WorkspaceView;
import com.gensym.wksp.SelectionCommand;

/**
 * EditCommandsImpl contains system-level CUT/COPY/PASTE commands available for
 * G2 items on workspaces. 
 */
public final class EditCommandsImpl extends AbstractStructuredCommand implements SelectionCommand, SelectionListener {

  /** Command key to cut the selected item(s). */
  public static final String CUT_SELECTION = "cut";
  /** Command key to copy the selected item(s). */
  public static final String COPY_SELECTION = "copy";
  /** Command key to paste the selected item(s). */
  public static final String PASTE_SELECTION = "paste";
 
  private static final String shortResource = "ShortCommandLabels";
  private static final String longResource = "LongCommandLabels";
  private static Resource shortBundle = Resource.getBundle("com.gensym.demos.custompopups.ShortCommandLabels");
  private static Resource longBundle = Resource.getBundle("com.gensym.demos.custompopups.LongCommandLabels");
  private Resource i18n = Resource.getBundle("com.gensym.demos.custompopups.Errors");

  public Frame frame;
  private WorkspaceView workspaceView = null;
  private WorkspaceElement[] currentSelection = null;

  private static final int offset = 10;
  private static boolean clipboardDataWasCut;
 
  public EditCommandsImpl(){
    super(new CommandInformation[]{
      new CommandInformation(CUT_SELECTION, true, 
			     shortResource, longResource, 
			     "cut.gif", null, null, true),
	new CommandInformation(COPY_SELECTION, true,
			       shortResource, longResource,
			       "copy.gif", null, null, true),
	new CommandInformation(PASTE_SELECTION, false,
			       shortResource, longResource,
			       "paste.gif", null, null, true)});
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

  private void updateAvailability(){
    if (workspaceView != null) {
      setAvailable(PASTE_SELECTION, true);
      if (currentSelection == null || currentSelection.length == 0) {
	// there is no selection
	setAvailable(CUT_SELECTION, false);
	setAvailable(COPY_SELECTION, false);
      }
      else {
	// there is a selection
	setAvailable(CUT_SELECTION, true);
	setAvailable(COPY_SELECTION, true);
      }

      setAvailable(PASTE_SELECTION, true);
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

	Dimension size = workspaceView.getSize();
	Point location = new Point(size.width/2, size.height/2);
      
	//workspaceView.translateWindowToView(location);
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
      }
    } else {
      new MessageDialog(frame, i18n.getString("ClipboardMessage"), true, 
			i18n.getString("ClipboardEmpty"), null).setVisible(true);
    }
  }

  //BEGIN: SelectionCommand methods

  @Override
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

  // END: SelectionCommand methods


  // BEGIN: SelectionListener methods
  @Override
  public void selectionChanged(SelectionEvent event){
    currentSelection = workspaceView.getSelection();
    updateAvailability();
  }
  // END: SelectionListener methods

}


