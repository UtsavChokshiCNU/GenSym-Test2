/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ItemsCommands.java
 *
 */
package com.gensym.shell.commands;

import java.awt.event.ActionEvent;
import java.awt.Component;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import com.gensym.classes.FreeText;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.NameBox;
import com.gensym.classes.TableItem;
import com.gensym.classes.TextBox;
import com.gensym.classes.Entity;
import com.gensym.core.GensymApplication;
import com.gensym.dlg.CommandConstants;
import com.gensym.dlg.QuestionDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.editor.color.G2ColorRegionsDialog;
import com.gensym.editor.text.G2FreeTextFontSizeDialog;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIEvent;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIListener;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.DescribeTable;
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.uitools.utils.WhiteBackgroundJScrollPane;
import com.gensym.util.CorruptionException;
import com.gensym.util.ItemEvent;
import com.gensym.util.ItemListener;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.WorkspaceAdapter;
import com.gensym.util.WorkspaceEvent;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.util.symbol.VirtualAttributeSymbols;
import com.gensym.util.UnexpectedException;
import com.gensym.wksp.WorkspaceElement;
import com.gensym.wksp.WorkspaceView;
import javax.swing.KeyStroke;
import java.awt.Event;
import java.util.Hashtable;

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
  /** Command key to delete the selected item(s). */
  public static final String DELETE_SELECTION = "DeleteSelection";
  /** Command key to lift the selected item(s) to the top of the drawing order. */
  public static final String LIFT_SELECTION_TO_TOP = "LiftSelectionToTop";
  /** Command key to drop the selected item(s) to the bottom of the drawing order. */
  public static final String DROP_SELECTION_TO_BOTTOM = "DropSelectionToBottom";
  /** Command key to display the Properties dialog(s) for the selected item(s). */
  public static final String ITEM_PROPERTIES = "ItemProperties";
  /** Command key to display the color dialog(s) for the selected item(s) */
  public static final String COLOR = "Color";
  /** Command key to display the fontsize dialog(s) for the selected item(s) */
  public static final String FONT_SIZE = "FontSize";
  /** Command key to launch the TextEditor for the selected item(s). */
  public static final String EDIT_ITEM_TEXT = "EditItemText";
  public static final String MARK_TO_STRIP_TEXT = "MarkToStripText";
  public static final String MARK_NOT_TO_STRIP_TEXT = "MarkNotToStripText";
  public static final String REMOVE_STRIP_TEXT_MARK = "RemoveStripTextMark";
  public static final String REMOVE_DO_NOT_STRIP_TEXT_MARK = "RemoveDoNotStripTextMark";
  public static final String DESCRIBE_CONFIGURATION = "DescribeConfiguration";
  public static final String DESCRIBE = "Describe";
  private static final Symbol STRIP_TEXT_MARK_ = SystemAttributeSymbols.STRIP_TEXT_MARK_;
  private static final Symbol DO_NOT_STRIP_TEXT_MARK_ = SystemAttributeSymbols.DO_NOT_STRIP_TEXT_MARK_;
  private static final Symbol[] neededAttributes = { STRIP_TEXT_MARK_, DO_NOT_STRIP_TEXT_MARK_};

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";
  private static Resource shortBundle = Resource.getBundle("com/gensym/shell/commands/CommandShortResource");
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");

  private static final int SELECTION_DISABLED = 0;
  private static final int SELECTION_ENABLED = 1;

  private static final int SELECTION_MARKED = 1;
  private static final int SELECTION_UNMARKED = 0;

  private static final int SELECTION_MIXED = 2;

  private static final int SELECTION_NOT_EDITABLE = 0;
  private static final int SELECTION_EDITABLE = 1;

  private static final Symbol TEXT_ = Symbol.intern ("TEXT");
  private static final Symbol G2_GET_PACKAGE_PREPARATION_MODE_ = Symbol.intern ("G2-GET-PACKAGE-PREPARATION-MODE");

  private MDIFrame frame = null;
  private WorkspaceView workspaceView = null;
  private WorkspaceElement[] currentSelection = null;
  private ItemCommandsWorkspaceAdapter workspaceAdapter =
  new ItemCommandsWorkspaceAdapter();

  private StandardDialogClient dlgClient;

  private static final Symbol
    BACKGROUND_COLOR_ = VirtualAttributeSymbols.BACKGROUND_COLOR_,
    FOREGROUND_COLOR_ = VirtualAttributeSymbols.FOREGROUND_COLOR_,
    BORDER_COLOR_ = VirtualAttributeSymbols.BORDER_COLOR_,
    TEXT_COLOR_ = VirtualAttributeSymbols.TEXT_COLOR_;

  private Hashtable colorDialogItems = new Hashtable();
  private Hashtable fontSizeDialogItems = new Hashtable();

  public ItemCommands(){
    this(null);
  }

  /**
   * @param parentFrame The parent frame that is managing the mouse and/or
   * toolbars generated from this command.
   */
  public ItemCommands(MDIFrame parentFrame){
    super(new StructuredCommandInformation[]{
      new CommandGroupInformation("DrawingOrderGroup", new CommandInformation[]{
	new CommandInformation(LIFT_SELECTION_TO_TOP, true,
			       shortResource, longResource,
			       "lift_to_top.gif", null, null, true, mnemonicResource, null),
	  new CommandInformation(DROP_SELECTION_TO_BOTTOM, true,
				 shortResource, longResource,
				 "drop_to_bottom.gif", null, null, true, mnemonicResource, null)}),

	new CommandGroupInformation("EnableGroup", new CommandInformation[]{
	  new CommandInformation(ENABLE_SELECTION, true,
				 shortResource, longResource,
				 "item.gif", null, null, true, mnemonicResource, null),
	    new CommandInformation(DISABLE_SELECTION, true,
				   shortResource, longResource,
				   "no_item.gif", null, null, true, mnemonicResource, null)}),

	  new CommandGroupInformation("DeleteGroup", new CommandInformation[]{
	    new CommandInformation(DELETE_SELECTION, true,
				   shortResource, longResource,
				   "delete.gif", null, null, true, mnemonicResource,
				   KeyStroke.getKeyStroke('D', Event.CTRL_MASK))}),
	    new CommandGroupInformation("DescribeGroup", new CommandInformation[]{	      new CommandInformation(DESCRIBE, true,
				     shortResource, longResource,
														     null, null, null, false, mnemonicResource, null),
	      new CommandInformation(DESCRIBE_CONFIGURATION, true,
				     shortResource, longResource,
				     null, null, null, false, mnemonicResource, null)}),
	      new CommandGroupInformation("TextStripGroup", new CommandInformation[]{
		new CommandInformation(MARK_TO_STRIP_TEXT, true,
				       shortResource, longResource,
				       null,
				       null, null, true),
		  new CommandInformation(MARK_NOT_TO_STRIP_TEXT, true,
					 shortResource, longResource,
					 null,
					 null, null, true),
		  new CommandInformation(REMOVE_STRIP_TEXT_MARK, true,
					 shortResource, longResource,
					 null,
					 null, null, true),
		  new CommandInformation(REMOVE_DO_NOT_STRIP_TEXT_MARK, true,
					 shortResource, longResource,
					 null,
					 null, null, true)}),
		new CommandGroupInformation("EditGroup", new CommandInformation[]{
		  new CommandInformation(EDIT_ITEM_TEXT, true,
					 shortResource, longResource,
					 "edit_text.gif", null, null, false, mnemonicResource, null),
                  new CommandInformation(COLOR, true,
					   shortResource, longResource,
					   "JColorChooser.gif", null, null, false, mnemonicResource, null),
                  new CommandInformation(FONT_SIZE, true,
					   shortResource, longResource,
					   "FontSizeChooser.gif", null, null, false, mnemonicResource, null),
		    new CommandInformation(ITEM_PROPERTIES, true,
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

  public void setWorkspaceView(WorkspaceView workspaceView) {
    listenToWorkspace(false);
    com.gensym.classes.KbWorkspace kbWorkspace;
    if (this.workspaceView != null) {
      this.workspaceView.removeSelectionListener(this);
      try {
	kbWorkspace = this.workspaceView.getWorkspace();
	if (kbWorkspace != null)
	  kbWorkspace.removeItemListener(this, neededAttributes);
      } catch (G2AccessException ex) {
	Trace.exception(ex);
      }
    }
    this.workspaceView = workspaceView;
    if (this.workspaceView != null) {
      this.workspaceView.addSelectionListener(this);
      currentSelection = workspaceView.getSelection();
      try {
	kbWorkspace = this.workspaceView.getWorkspace();
	if (kbWorkspace != null && kbWorkspace.isValid ())
	  kbWorkspace.addItemListener(this, neededAttributes);
      } catch (G2AccessException ex) {
	Trace.exception(ex);
      }
    }
    updateAvailability();
  }


  /**
   * Handles ActionEvents where the action command is one of:
   * ITEM_PROPERTIES, DELETE_SELECTION, ENABLE_SELECTION,
   * DISABLE_SELECTION, LIFT_SELECTION_TO_TOP,
   * DROP_SELECTION_TO_BOTTOM, EDIT_ITEM_TEXT
   */
  @Override
  public void actionPerformed(ActionEvent event) {
    String cmdKey = event.getActionCommand();
    if (!isAvailable(cmdKey))
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", cmdKey));

    if (cmdKey.equals(ITEM_PROPERTIES))
      handleItemPropertiesCommand();
    else if (cmdKey.equals(COLOR))
      handleColorCommand();
    else if (cmdKey.equals(FONT_SIZE))
      handleFontSizeCommand();
    else if (cmdKey.equals(DELETE_SELECTION))
      handleDeleteSelectionCommand();
    else if (cmdKey.equals(DESCRIBE))
      handleDescribe();
    else if (cmdKey.equals(DESCRIBE_CONFIGURATION))
      handleDescribeConfiguration();
    else if (cmdKey.equals(ENABLE_SELECTION))
      handleEnableSelectionCommand();
    else if (cmdKey.equals(DISABLE_SELECTION))
      handleDisableSelectionCommand();
    else if (cmdKey.equals(LIFT_SELECTION_TO_TOP))
      handleLiftSelectionToTopCommand();
    else if (cmdKey.equals(DROP_SELECTION_TO_BOTTOM))
      handleDropSelectionToBottomCommand();
    else if (cmdKey.equals(EDIT_ITEM_TEXT))
      handleEditItemTextCommand();
    else if (MARK_TO_STRIP_TEXT.equals(cmdKey))
      setStripTextMarkForSelection(true);
    else if (MARK_NOT_TO_STRIP_TEXT.equals(cmdKey))
      setDoNotStripTextMarkForSelection(true);
    else if (REMOVE_STRIP_TEXT_MARK.equals(cmdKey))
      setStripTextMarkForSelection(false);
    else if (REMOVE_DO_NOT_STRIP_TEXT_MARK.equals(cmdKey))
      setDoNotStripTextMarkForSelection(false);
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
	setAvailable(DELETE_SELECTION, false);
	setAvailable(ENABLE_SELECTION, false);
	setAvailable(DISABLE_SELECTION, false);
	setAvailable(LIFT_SELECTION_TO_TOP, false);
	setAvailable(DROP_SELECTION_TO_BOTTOM, false);
        setAvailable(COLOR, false);
        setAvailable(FONT_SIZE, false);
	setAvailable(ITEM_PROPERTIES, false);
	setAvailable(EDIT_ITEM_TEXT, false);
	setAvailable(MARK_TO_STRIP_TEXT, false);
	setAvailable(MARK_NOT_TO_STRIP_TEXT, false);
	setAvailable(REMOVE_STRIP_TEXT_MARK, false);
	setAvailable(REMOVE_DO_NOT_STRIP_TEXT_MARK, false);
	setAvailable(DESCRIBE, false);
	setAvailable(DESCRIBE_CONFIGURATION, false);
      }
      else {
	// there is a selection
	boolean isPPMode = false;
	TW2MDIApplication app = (TW2MDIApplication)GensymApplication.getApplication();
	TwAccess context = app.getConnectionManager().getCurrentConnection();
	if (context != null && context.getG2Version().getMajorVersion() >= 6) {
	  try {
	    isPPMode = ((Boolean)context.callRPC(G2_GET_PACKAGE_PREPARATION_MODE_, new Object[] {})).booleanValue();
	  } catch (G2AccessException gae) {
	    Trace.exception(gae);
	  }
	}
	setAvailable(DELETE_SELECTION, !browserMode);
	setAvailable(LIFT_SELECTION_TO_TOP, !browserMode);
	setAvailable(DROP_SELECTION_TO_BOTTOM, !browserMode);
        setAvailable(COLOR, !browserMode);
        setAvailable(FONT_SIZE, !browserMode);
	setAvailable(ITEM_PROPERTIES, true);
	setAvailable(DESCRIBE_CONFIGURATION, !browserMode);
	setAvailable(DESCRIBE, !browserMode);
	int status;
	if (isPPMode == false) {
	  setAvailable(MARK_TO_STRIP_TEXT, false);
	  setAvailable(MARK_NOT_TO_STRIP_TEXT, false);
	  setAvailable(REMOVE_STRIP_TEXT_MARK, false);
	  setAvailable(REMOVE_DO_NOT_STRIP_TEXT_MARK, false);
	} else {
	  status = getTextMarkStatusOfSelection(STRIP_TEXT_MARK_);
	  setStripTextMarkAvailability(MARK_TO_STRIP_TEXT,
				       REMOVE_STRIP_TEXT_MARK,
				       status);
	  status = getTextMarkStatusOfSelection(DO_NOT_STRIP_TEXT_MARK_);
	  setStripTextMarkAvailability(MARK_NOT_TO_STRIP_TEXT,
				       REMOVE_DO_NOT_STRIP_TEXT_MARK,
				       status);
	}
	// does the selection have editable text?
	status = getSelectionEditableTextStatus();
	if (status == SELECTION_EDITABLE)
	  setAvailable(EDIT_ITEM_TEXT, !browserMode);
	else
	  setAvailable(EDIT_ITEM_TEXT, false);

	// is the selection enabled/disabled/mixed?
	status = getSelectionEnabledStatus();
	if (status == SELECTION_ENABLED) {
	  setAvailable(ENABLE_SELECTION, false);
	  setAvailable(DISABLE_SELECTION, !browserMode);
	} else if (status == SELECTION_DISABLED) {
	  setAvailable(ENABLE_SELECTION, !browserMode);
	  setAvailable(DISABLE_SELECTION, false);
	} else {
	  setAvailable(ENABLE_SELECTION, false);
	  setAvailable(DISABLE_SELECTION, false);
	}
      }
    } else { // workspaceView == null
      setAvailable(DELETE_SELECTION, false);
      setAvailable(ENABLE_SELECTION, false);
      setAvailable(DISABLE_SELECTION, false);
      setAvailable(LIFT_SELECTION_TO_TOP, false);
      setAvailable(DROP_SELECTION_TO_BOTTOM, false);
      setAvailable(COLOR, false);
      setAvailable(FONT_SIZE, false);
      setAvailable(ITEM_PROPERTIES, false);
      setAvailable(EDIT_ITEM_TEXT, false);
      setAvailable(MARK_TO_STRIP_TEXT, false);
      setAvailable(MARK_NOT_TO_STRIP_TEXT, false);
      setAvailable(REMOVE_STRIP_TEXT_MARK, false);
      setAvailable(REMOVE_DO_NOT_STRIP_TEXT_MARK, false);
      setAvailable(DESCRIBE_CONFIGURATION, false);
      setAvailable(DESCRIBE, false);
    }
  }

  private void setStripTextMarkAvailability(String markKey, String removeKey,
					    int status) {
    if (status == SELECTION_UNMARKED) {
      setAvailable(removeKey, false);
      setAvailable(markKey, true);
    } else if (status == SELECTION_MARKED) {
      setAvailable(removeKey, true);
      setAvailable(markKey, false);
    } else {
      setAvailable(markKey, false);
      setAvailable(removeKey, false);
    }
  }

  private int getTextMarkStatusOfSelection(Symbol property) {
    Item loopItem;
    Boolean prevMarkStatus = null;

    try {
      Boolean loopMarkStatus;
      for (int i=0; i<currentSelection.length; i++) {
	loopItem = currentSelection[i].getItem();
	if ((loopItem instanceof NameBox) || (loopItem instanceof TableItem))
	  return SELECTION_MIXED;
	loopMarkStatus = (Boolean)loopItem.getPropertyValue(property);
	if (prevMarkStatus != null && loopMarkStatus != prevMarkStatus)
	  return SELECTION_MIXED;
	else
	  prevMarkStatus = loopMarkStatus;
      }
    } catch (NoSuchAttributeException nsae) {
      Trace.exception(nsae);
      return SELECTION_MIXED;
    } catch (G2AccessException gae) {
      Trace.exception(gae);
      return SELECTION_MIXED;
    }
    return prevMarkStatus.booleanValue()?SELECTION_MARKED:SELECTION_UNMARKED;
  }

  private int getSelectionEnabledStatus() {
    int status = SELECTION_MIXED;
    int numEnabled = 0;

    for (int i=0; i<currentSelection.length; i++) {
      try {
	if (!currentSelection[i].getItem().getManuallyDisabled())
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

  private int getSelectionEditableTextStatus() {
    int status = SELECTION_MIXED;
    int numEditable = 0;
    com.gensym.classes.Item item;
    for (int i=0; i<currentSelection.length; i++) {
      item = currentSelection[i].getItem();
      if (item instanceof com.gensym.classes.Procedure ||
	  item instanceof com.gensym.classes.TextBox)
	numEditable = numEditable + 1;
    }

    if (currentSelection.length != 0) {
      if (numEditable == currentSelection.length)
	status = SELECTION_EDITABLE;
      else if (numEditable == 0)
	status = SELECTION_NOT_EDITABLE;
      else status = SELECTION_MIXED;
    }

    return status;
  }

  private void handleDeleteSelectionCommand() {
    if (currentSelection.length > 1) {
      QuestionDialog dlg = new QuestionDialog(frame, shortBundle.getString("StandardDialogTitle"),
					      true, shortBundle.getString("PromptToDeleteSelection"),
					      dlgClient);
      dlg.setVisible(true);
    } else
      executeDeleteSelection();
  }
  class DescribeDlg extends StandardDialog {

    static final String DLG_TITLE = "Describe Dialog";

    DescribeDlg (Item item){
      super(null, DLG_TITLE, false,
	    new String[]{DISMISS_LABEL}, new int[]{DISMISS},
	    new WhiteBackgroundJScrollPane(new DescribeTable(item)), null);
      setSize(422, 327);
    }
  }

  private void handleDescribe() {
    WorkspaceElement[] selectionSnapshot = (WorkspaceElement[]) currentSelection.clone ();
    for (int i=0; i<selectionSnapshot.length; i++)
      new DescribeDlg(selectionSnapshot[i].getItem()).setVisible(true);
  }

  private void handleDescribeConfiguration() {
    WorkspaceElement[] selectionSnapshot = (WorkspaceElement[]) currentSelection.clone ();
    TW2MDIApplication app = (TW2MDIApplication)GensymApplication.getApplication();
    TwAccess context = app.getConnectionManager().getCurrentConnection();
    for (int i=0; i<selectionSnapshot.length; i++) {
      try{
	new DescribeConfigDlg(null, selectionSnapshot[i].getItem(),
			      (G2Access)context,
			      null).setVisible(true);
      } catch (NoSuchAttributeException nsae) {
	Trace.exception(nsae);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }
  }

  private void executeDeleteSelection() {
    WorkspaceElement[] selectionSnapshot = (WorkspaceElement[]) currentSelection.clone ();
    for (int i=0; i<selectionSnapshot.length; i++) {
      try {
	selectionSnapshot[i].getItem().delete(true, true);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }
  }

  private void handleEnableSelectionCommand() {
    try {
      for (int i=0; i<currentSelection.length; i++)
	currentSelection[i].getItem().enable();
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }

  private void handleDisableSelectionCommand() {
    try {
      for (int i=0; i<currentSelection.length; i++)
	currentSelection[i].getItem().disable();
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }

  private void handleLiftSelectionToTopCommand() {
    workspaceView.liftSelectionToTop();
  }

  private void handleDropSelectionToBottomCommand() {
    workspaceView.dropSelectionToBottom();
  }

  private void handleItemPropertiesCommand() {
    TW2MDIApplication app = (TW2MDIApplication)GensymApplication.getApplication();
    TwAccess  context = app.getConnectionManager().getCurrentConnection();
    com.gensym.dlgruntime.DialogManager dlgManager = context.getDialogManager();

    try {
      com.gensym.util.Symbol userMode = context.getUserMode();
      try {
	for (int i=0; i<currentSelection.length; i++) {
	  dlgManager.editItem (workspaceView, currentSelection[i].getItem(), userMode, java.util.Locale.getDefault());
	}
      } catch (com.gensym.dlgruntime.ResourceInstantiationException rex) {
	Trace.exception(rex);
      } catch (java.net.MalformedURLException uex) {
	Trace.exception(uex);
      }
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }

  private void handleColorCommand() {
    Item itm;
    try {
      for (int i=0; i<currentSelection.length; i++) {
        itm = currentSelection[i].getItem();
        if (itm instanceof Entity) {
          editColorPattern(((Entity)itm).getItemColorPattern(), itm);
        } else if (itm instanceof TextBox) {
          Structure colorPattern = new Structure();
	  TextBox tb = (TextBox)itm;
	  colorPattern = tb.getItemColorPattern();
	  if (colorPattern.getAttributeValue(BACKGROUND_COLOR_, null) == null)
	    colorPattern.setAttributeValue(BACKGROUND_COLOR_,
					   tb.getBackgroundColor());
	  if (colorPattern.getAttributeValue(TEXT_COLOR_, null) == null)
	    colorPattern.setAttributeValue(TEXT_COLOR_,
					   tb.getTextColor());
	  if (!(tb instanceof NameBox) &&
	      colorPattern.getAttributeValue(BORDER_COLOR_, null) == null)
	    colorPattern.setAttributeValue(BORDER_COLOR_,
					   tb.getBorderColor());
	  editColorPattern(colorPattern, itm);
        } else if (itm instanceof KbWorkspace) {
	  Structure colorPattern = new Structure();
	  KbWorkspace ws = (KbWorkspace)itm;
	  colorPattern.setAttributeValue(BACKGROUND_COLOR_,
				         ws.getBackgroundColor());
	  colorPattern.setAttributeValue(FOREGROUND_COLOR_,
				         ws.getForegroundColor());
	  editColorPattern(colorPattern, itm);
        } else
	  Trace.exception(new UnexpectedException(new Exception(),
    						  "Item not known to have color regions"));
      }

    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }

  private Structure editColorPattern(Structure currentColorPattern,
				     Item itm)
  {
    G2ColorRegionsDialog dlg = new G2ColorRegionsDialog(null,null, false,
							dlgClient);
    colorDialogItems.put(dlg, itm);
    dlg.setSize(550,400);
    dlg.setRegions(currentColorPattern);
    dlg.setVisible(true);
    return null;
  }

  private void handleFontSizeCommand() {
    Item itm;
    try {
      for (int i=0; i<currentSelection.length; i++) {
        itm = currentSelection[i].getItem();
        if (itm instanceof FreeText) {
          G2FreeTextFontSizeDialog dlg = new G2FreeTextFontSizeDialog (null,null, false,
							         dlgClient);
          fontSizeDialogItems.put(dlg, itm);
          dlg.setSize(300,150);
          dlg.setVisible(true);
          String tableHeader = itm.getTableHeader();
          int index = tableHeader.indexOf(",");
          String title;
          if (index == -1)
            title = tableHeader;
          else
            title = tableHeader.substring(0, index);

          dlg.setTitle("Font Size of " + title);
        }
      }
   } catch (G2AccessException gae) {
      Trace.exception(gae);
   }
  }

  private void setStripTextMark(Item item, boolean newState) {
    try {
      item.setPropertyValue(STRIP_TEXT_MARK_, newState?Boolean.TRUE:Boolean.FALSE);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }

  private void setDoNotStripTextMark(Item item, boolean newState) {
    try {
      item.setPropertyValue(DO_NOT_STRIP_TEXT_MARK_, newState?Boolean.TRUE:Boolean.FALSE);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }
  private void setStripTextMarkForSelection(boolean newState) {
    for (int i=0; i<currentSelection.length; i++) {
      Item item = currentSelection[i].getItem();
      setStripTextMark(item, newState);
    }
  }

  private void setDoNotStripTextMarkForSelection(boolean newState) {
    for (int i=0; i<currentSelection.length; i++) {
      Item item = currentSelection[i].getItem();
      setDoNotStripTextMark(item, newState);
    }
  }

  private void handleEditItemTextCommand() {
    for (int i=0; i<currentSelection.length; i++) {
      /*
       * com.gensym.editor.text is a private package. This code may not be supported
       * in future releases of Telewindows2 Toolkit.
       */
      new com.gensym.editor.text.Session (currentSelection[i].getItem(), TEXT_, null);
    }
  }

  // BEGIN: SelectionListener methods
  @Override
  public void selectionChanged(SelectionEvent event){
    currentSelection = workspaceView.getSelection();

    if (currentSelection == null || currentSelection.length == 0)
      listenToWorkspace(false);
    else
      listenToWorkspace(true);

    updateAvailability();
  }

  private KbWorkspace currentlySubscribedKbWorkspace;
  private void listenToWorkspace(boolean yes) {
    try {
      if (!yes) {
	if (currentlySubscribedKbWorkspace != null) {
	  currentlySubscribedKbWorkspace.removeWorkspaceListener(workspaceAdapter);
	  currentlySubscribedKbWorkspace = null;
	}
	return;
      }

      KbWorkspace currentKbWorkspace = workspaceView.getWorkspace();
      if (currentKbWorkspace.equals(currentlySubscribedKbWorkspace))
	return;
      else if (currentlySubscribedKbWorkspace != null) {
	currentlySubscribedKbWorkspace.removeWorkspaceListener(workspaceAdapter);
	currentlySubscribedKbWorkspace = null;
      }

      currentKbWorkspace.addWorkspaceListener(workspaceAdapter);
      currentlySubscribedKbWorkspace = currentKbWorkspace;
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
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
      try{
	WorkspaceView view = document.getWorkspaceView();
	if (view != null){
	  com.gensym.classes.KbWorkspace wksp = view.getWorkspace();
	  if (wksp != null) {
	    listenToWorkspace(false);
	    wksp.removeItemListener(this, neededAttributes);
	  }
	}
      }
      catch(G2AccessException ex){
	Trace.exception(ex);
      }
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

  class DialogClient implements StandardDialogClient {
    @Override
    public void dialogDismissed (StandardDialog dlg, int cmdCode) {
      if (!(dlg instanceof G2ColorRegionsDialog) &&
          !(dlg instanceof G2FreeTextFontSizeDialog)) {
        dlg.setVisible(false);
        if (dlg.wasCancelled()) return;
      }


      // for color updation panel dlg
      if (dlg instanceof G2ColorRegionsDialog) {
        if (dlg.wasCancelled()) {
          colorDialogItems.remove(dlg);
          return;
      }
	Item itm = (Item)colorDialogItems.get(dlg);
	G2ColorRegionsDialog cd = (G2ColorRegionsDialog)dlg;
	Structure newPattern = cd.getRegions();
	try {
	  if (itm instanceof Entity) {
	    ((Entity)itm).setItemColorPattern(newPattern);
	  } else if (itm instanceof TextBox) {
	    TextBox tb = (TextBox)itm;
	    tb.setItemColorPattern(newPattern);
	  } else if (itm instanceof KbWorkspace) {
	    KbWorkspace ws = (KbWorkspace) itm;
	    Symbol newBg
	      = (Symbol) newPattern.getAttributeValue(BACKGROUND_COLOR_, null);
	    if (newBg != null)
	      ws.setBackgroundColor(newBg);
	    Symbol newFg
	      = (Symbol) newPattern.getAttributeValue(FOREGROUND_COLOR_, null);
	    if (newFg != null)
	      ws.setForegroundColor(newFg);
	  }
        } catch (G2AccessException g2ae) {
	  Trace.exception(g2ae);
        }

        if (cmdCode == dlg.OK)
	  colorDialogItems.remove(dlg);
      }

      // for font size panel dlg
      if (dlg instanceof G2FreeTextFontSizeDialog) {
        if (dlg.wasCancelled()) {
          fontSizeDialogItems.remove(dlg);
          return;
        }
        Item itm = (Item) fontSizeDialogItems.get(dlg);
        G2FreeTextFontSizeDialog fDlg = (G2FreeTextFontSizeDialog) dlg;
        Structure textFontStructure = fDlg.getNewFreeTextFont ();
        if (textFontStructure != null) {
	  /* if (itm instanceof FreeText)
          try {
            ((FreeText) itm).setItemTextFont(textFontStructure);
          } catch (G2AccessException g2ae) {
	    Trace.exception(g2ae);
          }*/
        }
        if (cmdCode == dlg.OK)
	  fontSizeDialogItems.remove(dlg);
      }

      if (cmdCode == CommandConstants.YES)
	executeDeleteSelection();
    }
  }

  private void handleEnableDisable(Item item) {
    if (currentSelection != null && item != null) {
      for (int i = 0; i < currentSelection.length; i++) {
	if (item.equals(currentSelection[i].getItem())) {
	  updateAvailability();
	  return;
	}
      }
    }
  }

  class ItemCommandsWorkspaceAdapter extends WorkspaceAdapter {
    @Override
    public void workspaceItemAttributesChanged(WorkspaceEvent event) {
      Structure updateInfo = event.getInfo();
      if (updateInfo == null) //warning issued for this in more core parts of sequoia
	return;  //so just do nothing
      try {
	Symbol attributeName
	  = ((Symbol)updateInfo.getAttributeValue(WorkspaceElement.ATTRIBUTE_NAME_));

	if (!SystemAttributeSymbols.MANUALLY_DISABLEDQ_.equals(attributeName))
	  return;

	Item item = event.getItem();
	if (!item.isValid()) return;
	WorkspaceElement element = ItemCommands.this.workspaceView.findElement(item);

	handleEnableDisable(item);
      } catch (NoSuchAttributeException nsae) {
	throw new CorruptionException(nsae);
      }
    }
  }

}






