
package com.gensym.wksp;

import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.event.ActionEvent;
import java.awt.Component;
import java.awt.Dialog;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.List;
import java.awt.Point;
import java.awt.PrintJob;
import java.awt.Rectangle;
import java.awt.print.PrinterJob;
import java.awt.print.PrinterException;
import java.io.IOException;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Locale;
import java.util.Vector;
import javax.swing.JButton;
import javax.swing.JInternalFrame;
import com.gensym.classes.FreeformTable;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.Block;
import com.gensym.classes.Entity;
import com.gensym.classes.TableItem;
import com.gensym.classes.TextBox;
import com.gensym.classes.NameBox;
import com.gensym.classes.Procedure;
import com.gensym.classes.MethodDeclaration;
import com.gensym.classes.ClassDefinition;
import com.gensym.classes.ConnectionDefinition;
import com.gensym.classes.Relation;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Graph;
import com.gensym.classes.Connection;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.WarningDialog;
import com.gensym.dlg.QuestionDialog;
import com.gensym.editor.color.G2ColorRegionsDialog;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2ItemDeletedException;
import com.gensym.message.Trace;
import com.gensym.message.MessageKey;
import com.gensym.message.Resource;
import com.gensym.ntw.attrdisplays.G2AttributeLayoutDialog;
import com.gensym.ntw.TwConnection;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.CollectionListener;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.ntw.util.DescribeTable;
import com.gensym.shell.commands.DescribeConfigDlg;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.ui.Command;
import com.gensym.ui.CommandListener;
import com.gensym.ui.CommandEvent;
import com.gensym.ui.StructuredCommand;
import com.gensym.ui.SubCommand;
import com.gensym.ui.StructuredCommandListener;
import com.gensym.uitools.attrdisplays.layoutui.ComponentConstructionException;
import com.gensym.uitools.utils.WhiteBackgroundJScrollPane;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.symbol.VirtualAttributeSymbols;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.util.UnexpectedException;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.NtwIllegalArgumentException;
import com.gensym.wksp.configurations.ConfigurationSupport;
import com.gensym.wksp.configurations.ConfigurationSymbols;
import com.gensym.ntw.util.VersionHelper;

/**
 * An implementation of the SelectionCommand interface that
 * exposes the applicable system-menu-choices of the selected
 * item(s) on the PopupMenu that is generated for the
 * selection.
 * @see com.gensym.wksp.SelectionCommandGenerator
 * @see com.gensym.wksp.SelectionCommand
 * 
 * @author vkp
 * @version 1.0 - 5/7/98
 */
public class SystemMenuChoiceCommands extends AbstractMenuChoiceCommands
implements ConfigurationSymbols {

  public static final String
    CUT             = "cut",
    COPY            = "copy",
    PASTE           = "paste",
    DELETE          = "delete",
    LIFT_TO_TOP     = "lift-to-top",
    DROP_TO_BOTTOM  = "drop-to-bottom",
    ENABLE          = "enable",
    DISABLE         = "disable",
    EDIT_TEXT       = "edit-text",
    PROPERTIES      = "properties",
    PRINT           = "print",
    SHRINK_WRAP     = "shrink-wrap",
    COLOR           = "color",
    DESCRIBE        = "describe",
    DESCRIBE_CONFIGURATION = "describe-configuration",     
    NAME            = "name",
    CLONE_WORKSPACE = "clone-workspace",
    GO_TO_SUBWORKSPACE="go-to-subworkspace",
    CREATE_SUBWORKSPACE="create-subworkspace",
    CREATE_INSTANCE = "create-instance",
    EDIT_ICON       = "edit-icon",    
    ROTATE_REFLECT  = "rotate-reflect",
    ALIGN_TEXT      = "align-text",
    LEFT            = "left",
    CENTER          = "center",
    RIGHT           = "right",
    EDIT_ATTRIBUTE_DISPLAY_LAYOUT = "edit-attribute-display-layout",
    MARK_TO_STRIP_TEXT = "mark-to-strip-text",
    MARK_NOT_TO_STRIP_TEXT = "mark-not-to-strip-text",
    REMOVE_STRIP_TEXT_MARK = "remove-strip-text-mark",
    REMOVE_DO_NOT_STRIP_TEXT_MARK = "remove-do-not-strip-text-mark",
    EDIT_CELLS = "edit-cells";

  /*
   * Standard Tracing Requirements
   */
  private static MessageKey traceKey =
    Trace.registerMessageKey ("com.gensym.wksp.clipboard", SystemMenuChoiceCommands.class);
  private static Resource i18nTrace =
    Trace.getBundle("com.gensym.wksp.TraceMessages", Locale.getDefault());
  private static final Resource workspaceMessages = Trace.getBundle("com.gensym.wksp.WorkspaceMessages");
  private static final int DEF_TRACE_LEVEL     = 5;
  private static final int ALWAYS_TRACE_LEVEL  = 1;
  private static final int DEF_WARN_LEVEL      = 2;
  private static final int BASIC_TRACE_LEVEL   = 3;
  private static final int MINIMAL_TRACE_LEVEL = 4;

  private static final Symbol TEXT_ = Symbol.intern ("TEXT");
  private static final Symbol CONNECTION_ = Symbol.intern ("CONNECTION");
  private static final Symbol
  LEFT_ = Symbol.intern ("LEFT"),
    CENTER_ = Symbol.intern ("CENTER"),
    RIGHT_ = Symbol.intern ("RIGHT");
  private static final String
    ROTATE_90_CLOCKWISE         = "Rotate90Clockwise",
    ROTATE_90_COUNTER_CLOCKWISE = "Rotate90CounterClockwise",
    ROTATE_180_DEGREES          = "Rotate180Degrees",
    FLIP_VERTICAL               = "FlipVertical",
    FLIP_HORIZONTAL             = "FlipHorizontal";
  private static boolean promptForDelete = true;
  static {
    String propValue = System.getProperty ("com.gensym.wksp.promptBeforeDeletion", "true");
    promptForDelete = new Boolean (propValue).booleanValue ();
  }
    

  private static final Clipboard clipboard = WorkspaceView.systemClipboard; //java.awt.Toolkit.getDefaultToolkit().getSystemClipboard ();

  private static final int SELECTION_MARKED = 0;
  private static final int SELECTION_UNMARKED = 1;
  private static final int SELECTION_UNKNOWN = 0;
  private static final int SELECTION_DISABLED = 1;
  private static final int SELECTION_ENABLED = 2;
  private static final int SELECTION_MIXED = 3;
  private int selectionStatus = SELECTION_UNKNOWN;

  private static final Symbol
  BACKGROUND_COLOR_ = VirtualAttributeSymbols.BACKGROUND_COLOR_,
    FOREGROUND_COLOR_ = VirtualAttributeSymbols.FOREGROUND_COLOR_,
    BORDER_COLOR_ = VirtualAttributeSymbols.BORDER_COLOR_,
    TEXT_COLOR_ = VirtualAttributeSymbols.TEXT_COLOR_,
    STRIP_TEXT_MARK_ = Symbol.intern("STRIP-TEXT-MARK"),
    DO_NOT_STRIP_TEXT_MARK_ = Symbol.intern("DO-NOT-STRIP-TEXT-MARK"),
    G2_GET_PACKAGE_PREPARATION_MODE_ = Symbol.intern ("G2-GET-PACKAGE-PREPARATION-MODE");
  private boolean packagePreparationMode;
  
  /**
   * Creates a new SystemMenuChoiceCommands that can be used to
   * generate PopupMenus for Items on workspaces.
   * @see com.gensym.wksp.SelectionCommandGenerator
   */
  public SystemMenuChoiceCommands () {
    super (new String[] {CUT, COPY, PASTE, DELETE, LIFT_TO_TOP, DROP_TO_BOTTOM, ENABLE, DISABLE, EDIT_TEXT, EDIT_ATTRIBUTE_DISPLAY_LAYOUT, EDIT_ICON, PROPERTIES, PRINT, SHRINK_WRAP, COLOR, DESCRIBE, DESCRIBE_CONFIGURATION, NAME, CLONE_WORKSPACE,
 GO_TO_SUBWORKSPACE, CREATE_SUBWORKSPACE, CREATE_INSTANCE, ROTATE_REFLECT, ALIGN_TEXT, LEFT,CENTER, RIGHT, ROTATE_90_CLOCKWISE, ROTATE_90_COUNTER_CLOCKWISE, ROTATE_180_DEGREES, FLIP_VERTICAL, FLIP_HORIZONTAL,MARK_TO_STRIP_TEXT, MARK_NOT_TO_STRIP_TEXT, REMOVE_STRIP_TEXT_MARK, REMOVE_DO_NOT_STRIP_TEXT_MARK,EDIT_CELLS});
  }

  /**
   * Implementation of the Command interfaces. Overrides
   * the default isImmediate method to indicate that some
   * keys are not immediate.
   */
  @Override
  public boolean isImmediate (String cmdKey) {
    checkKey (cmdKey);
    return !(cmdKey.equals (EDIT_TEXT) ||
	     cmdKey.equals (EDIT_ATTRIBUTE_DISPLAY_LAYOUT) ||
	     cmdKey.equals (EDIT_CELLS) ||
	     cmdKey.equals (COLOR) ||
	     cmdKey.equals (NAME) ||
	     cmdKey.equals (EDIT_ICON) ||	     
	     cmdKey.equals (PROPERTIES) ||
	     cmdKey.equals (PRINT));
  }

  /**
   * Implementation of the action that is performed by
   * this Command.
   */
  @Override
  public void actionPerformed (ActionEvent e) {
    String cmdKey = e.getActionCommand ();
    checkKey (cmdKey);
    if (!isAvailable (cmdKey)) {
      System.err.println ("Command [" + cmdKey + "] not available!");
      return;			// Do we have a policy on this?
    }
    try {
      if (cmdKey.equals (LIFT_TO_TOP))
	wkspView.liftSelectionToTop ();
      else if (cmdKey.equals (DROP_TO_BOTTOM))
	wkspView.dropSelectionToBottom ();
      else if (isClipboardAction (cmdKey))
	executeClipboardAction (cmdKey);
      else {
	if (cmdKey.equals (DELETE) && promptForDelete) {
	  Symbol className_;
	  Object arg;
	  if (currentSelection.length == 0 || currentSelection.length == 1) {
	    if (currentSelection.length == 0)
	      className_ = wkspView.getWorkspace().getG2ClassName();
	    else
	      className_ = currentSelection[0].getItem().getG2ClassName();
	    arg = className_;
	  } else
	    arg = new Integer (currentSelection.length);
	  if (!okayToDelete (arg))
	    return;
	}
	if (currentSelection.length == 0)
	  executeItemAction (cmdKey, wkspView.getWorkspace ());
	for (int i=0; i<currentSelection.length; i++) {
	  WorkspaceElement wElt = currentSelection[i];
	  Item itm = wElt.getItem ();
	  executeItemAction (cmdKey, itm);
	}
      }
    } catch (G2AccessException gae) {
      com.gensym.message.Trace.exception (gae);
      new com.gensym.dlg.ErrorDialog (null, "Error Performing System Action",
				      true, gae.toString (), null).setVisible (true);
    } catch (Exception ex) {
      com.gensym.message.Trace.exception (ex);
      new com.gensym.dlg.ErrorDialog (null, "Error Performing System Action",
				      true, ex.toString (), null).setVisible (true);
    }
  }

  private boolean isClipboardAction (String cmdKey) {
    return (cmdKey.equals (CUT) ||
	    cmdKey.equals (COPY) ||
	    cmdKey.equals (PASTE));
  }

  private void executeClipboardAction (String cmdKey) {
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "executeClipAction", cmdKey);
    if (cmdKey.equals (CUT))
      wkspView.cutSelectionToClipboard ();
    else if (cmdKey.equals (COPY))
      wkspView.copySelectionToClipboard ();
    else if (cmdKey.equals (PASTE)) {
      try {
	Transferable clipboardContents = clipboard.getContents (wkspView);
	DataFlavor[] availableFlavors = clipboardContents.getTransferDataFlavors ();
	Item[] pasteData = (Item[])clipboardContents.getTransferData (availableFlavors[0]);
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "pasteData", com.gensym.core.DebugUtil.printArray (pasteData));
	SelectionCommandGenerator sg = wkspView.getSelectionCommandGenerator ();
	Point location = sg.getLastPostingLocation ();
	wkspView.translateWindowToView (location);
	wkspView.translateViewToWorkspace (location);
	wkspView.pasteClipboardContents (pasteData, location.x, location.y);
      } catch (UnsupportedFlavorException ufe) {
	com.gensym.message.Trace.exception (ufe);
      }	catch (IOException ioe) {
	com.gensym.message.Trace.exception (ioe);
      } catch (G2AccessException gae) {
	com.gensym.message.Trace.exception (gae);
	new WarningDialog (null, "Error while pasting Item", false,
			   gae.getMessage(),
			   null).setVisible (true);
      }
    }
  }

  class DialogClient implements StandardDialogClient , java.io.Serializable {
    @Override
    public void dialogDismissed (StandardDialog dlg, int code) {
      if (dlg.wasCancelled()) {
	colorDialogItems.remove(dlg);
	return;
      }

      if (dlg instanceof G2ColorRegionsDialog) {
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
      }
      if (code == dlg.OK) 
	colorDialogItems.remove(dlg);
    }
  }

  private Hashtable colorDialogItems = new Hashtable();
  private DialogClient dialogClient = new DialogClient();
  private Structure editColorPattern(Structure currentColorPattern,
				     Item itm)
  {
    G2ColorRegionsDialog dlg = new G2ColorRegionsDialog(null,null, false,
							dialogClient);
    colorDialogItems.put(dlg, itm);
    dlg.setSize(550,400);
    dlg.setRegions(currentColorPattern);
    dlg.setVisible(true);
    return null;
  }

  private void executeItemAction (String cmdKey, Item itm) throws G2AccessException,
                                                       java.net.MalformedURLException,
                                                       com.gensym.dlgruntime.ResourceInstantiationException {

    if (cmdKey.equals (DELETE)) {
      try {
	itm.delete (true, false);
      } catch (G2ItemDeletedException g2ide) {
	// Do nothing. No Trace.
      }
    } else if (cmdKey.equals (ENABLE))
      itm.enable ();
    else if (cmdKey.equals (DISABLE))
      itm.disable ();
    else if (cmdKey.equals (LIFT_TO_TOP))
      itm.liftToTop ();
    else if (cmdKey.equals (DROP_TO_BOTTOM)) 
      itm.dropToBottom ();
    else if (cmdKey.equals (EDIT_CELLS))
      new CellDialog((FreeformTable)itm, (G2Access)cxn).setVisible(true);
    else if (cmdKey.equals (EDIT_ATTRIBUTE_DISPLAY_LAYOUT)) {
      if (itm instanceof TableItem) {
	TableItem tableItem = (TableItem)itm;
	Item representedItem =(Item)tableItem.getRepresentedItem();
	if (representedItem instanceof Entity) { //should always be true!
	  Entity entity = (Entity)representedItem;
	  int focusIndex = 0;
	  Sequence tempSeq = entity.getAttributeDisplayItems();
	  for (int x = 0; x<tempSeq.size(); x++)
	    if (tempSeq.elementAt(x) == itm) 
	      focusIndex = x;
	  createAndLaunchAttributeDisplayLayoutDialog(entity, focusIndex);
	}
      } else if (itm instanceof Entity) 
	createAndLaunchAttributeDisplayLayoutDialog((Entity)itm, 0);
    } else if (cmdKey.equals (EDIT_TEXT)) {
      Symbol attributeName = TEXT_;
      Item itemToEdit = itm;
      if (itm instanceof NameBox) {
	itemToEdit = (Item) ((NameBox)itm).getRepresentedItem();
	if (itemToEdit instanceof ClassDefinition)
	  attributeName = SystemAttributeSymbols.CLASS_NAME_;
	else
	  attributeName = SystemAttributeSymbols.NAMES_;
      }
      new com.gensym.editor.text.Session (itemToEdit, attributeName, true);
    } else if (cmdKey.equals (MARK_TO_STRIP_TEXT)) {
      itm.setPropertyValue(STRIP_TEXT_MARK_, new Boolean(true));
    } else if (cmdKey.equals (MARK_NOT_TO_STRIP_TEXT)) {
      itm.setPropertyValue(DO_NOT_STRIP_TEXT_MARK_, new Boolean(true));
    } else if (cmdKey.equals (REMOVE_STRIP_TEXT_MARK)) {
      itm.setPropertyValue(STRIP_TEXT_MARK_, new Boolean(false));
    } else if (cmdKey.equals (REMOVE_DO_NOT_STRIP_TEXT_MARK)) {
      itm.setPropertyValue(DO_NOT_STRIP_TEXT_MARK_, new Boolean(false));
    } else if (cmdKey.equals (PROPERTIES)) {
      TwAccess context = (TwAccess) ((ImplAccess)itm).getContext ();
      context.getDialogManager().editItem (wkspView,
					   itm,
					   context.getUserMode (),
					   java.util.Locale.getDefault ());
    } else if (cmdKey.equals (PRINT)) {
      final PrinterJob printerJob = PrinterJob.getPrinterJob();
      printerJob.setPageable((ScalableWorkspaceView)wkspView);
      if (printerJob.printDialog()) {
	new Thread(new Runnable() {
	    @Override
		public void run() {
	      try{
		printerJob.print();
	      } catch(PrinterException ex) {
		ex.printStackTrace();
	      }
	    }
	  }).start();
      }
    } else if (cmdKey.equals (SHRINK_WRAP)) {
      wkspView.shrinkWrap ();
    } else if (COLOR.equals(cmdKey)) {
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
    } else if (DESCRIBE.equals(cmdKey)) {
     new DescribeDlg(itm).setVisible(true);

    } else if (DESCRIBE_CONFIGURATION.equals(cmdKey)) {
      try{
	new DescribeConfigDlg(null, itm, (G2Access)cxn, null).setVisible(true);
      } catch (NoSuchAttributeException nsae) {
	Trace.exception(nsae);
      }   
    } else if (NAME.equals(cmdKey)) {
      //determine attr name better
      com.gensym.wksp.configurations.TwActions.editTextProperty(itm, SystemAttributeSymbols.NAMES_); 
    } else if (CLONE_WORKSPACE.equals(cmdKey)) {
      com.gensym.wksp.configurations.TwActions.cloneWorkspace((KbWorkspace)itm);
    } else if (GO_TO_SUBWORKSPACE.equals(cmdKey)) {
      com.gensym.wksp.configurations.TwActions.goToSubworkspace((Entity)itm);
    } else if (CREATE_SUBWORKSPACE.equals(cmdKey)) {
      com.gensym.wksp.configurations.TwActions.createSubworkspace((Entity)itm, cxn);
    } else if (CREATE_INSTANCE.equals(cmdKey)) {
      com.gensym.wksp.configurations.TwActions.createInstance
	((ClassDefinition)itm, wkspView.getWorkspace(), cxn);
    } else if (EDIT_ICON.equals(cmdKey)) {
      com.gensym.wksp.configurations.TwActions.editIcon((ClassDefinition)itm);
    } else if (ROTATE_90_CLOCKWISE.equals(cmdKey)) {
      Entity ent = (Entity)itm;
      ent.setIconHeading(ent.getIconHeading() + 90);
      
    } else if (ROTATE_90_COUNTER_CLOCKWISE.equals(cmdKey)) {
      Entity ent = (Entity)itm;
      ent.setIconHeading(ent.getIconHeading() - 90);
    } else if (ROTATE_180_DEGREES.equals(cmdKey)) {
      Entity ent = (Entity)itm;
      ent.setIconHeading(ent.getIconHeading() + 180);      
    } else if (FLIP_VERTICAL.equals(cmdKey)) {
      ((Entity)itm).reflectVertically();
    } else if (FLIP_HORIZONTAL.equals(cmdKey)) {
      ((Entity)itm).reflectHorizontally();
    } else if (LEFT.equals(cmdKey)) {
      ((TextBox)itm).setTextAlignment(LEFT_);
    } else if (CENTER.equals(cmdKey)) {
      ((TextBox)itm).setTextAlignment(CENTER_);
    } else if (RIGHT.equals(cmdKey)) {
      ((TextBox)itm).setTextAlignment(RIGHT_);      
    }
  }

  private void createAndLaunchAttributeDisplayLayoutDialog(Entity entity,
							   int focusIndex) 
       throws G2AccessException {

    StandardDialog currentDialog;
    try {
      currentDialog = new G2AttributeLayoutDialog
	(workspaceMessages.getString ("attrLayoutOf")
	 +((Item)entity).getTableHeader(), 
	 entity, cxn, focusIndex);
      currentDialog.pack();
      currentDialog.setVisible(true);
    } catch (ComponentConstructionException cce) {
      //This won't happen, since the component is constructed as part of
      //the dialog constructor with no null arguments.
    }
  }

  private static String getItemDescription(Item item)
       throws G2AccessException
  {
    String itemNameOrClass = "Description of ";
    Object name = null;
    try {
      name = ((Block)item).getNames();
    } catch (G2AccessException g2ae) {
      //some items don't support this
    }
    if (name instanceof Sequence) {
      if (((Sequence)name).isEmpty())
	itemNameOrClass += "a(n) " + item.getG2ClassName().getPrintValue();
      else
	itemNameOrClass += name.toString();
    } else if (name instanceof Symbol)
      itemNameOrClass += ((Symbol)name).getPrintValue();
    else
      itemNameOrClass += "a(n) " + item.getG2ClassName().getPrintValue();
    return itemNameOrClass;
  }
  
  private Sequence systemMenuChoices = new Sequence ();
  private String[] systemMenuChoiceLabels;
  private Vector focalItems = new Vector();
  private TwConnection cxn;
  private static final boolean isJDK12
  = VersionHelper.isUsingJava2D(com.gensym.wksp.SystemMenuChoiceCommands.class);
  private static final Hashtable t2SystemMenuChoices = new Hashtable();
  public static final
  Symbol TABLE_ = Symbol.intern ("TABLE"),
    EDIT_ = Symbol.intern ("EDIT"),
    EDIT_ATTRIBUTE_DISPLAY_LAYOUT_ = Symbol.intern("EDIT-ATTRIBUTE-DISPLAY-LAYOUT"),
    TRANSFER_ = Symbol.intern ("TRANSFER"),
    CLONE_ = Symbol.intern ("CLONE"),
    //CHANGE_MIN_SIZE_ = Symbol.intern ("CHANGE-MIN-SIZE"),
    ALIGN_TEXT_ = Symbol.intern ("ALIGN-TEXT"),
    COLOR_ = Symbol.intern ("COLOR"),
    DELETE_ = Symbol.intern ("DELETE"),
    DROP_TO_BOTTOM_ = Symbol.intern ("DROP-TO-BOTTOM"),
    LIFT_TO_TOP_ = Symbol.intern ("LIFT-TO-TOP"),
    //GO_TO_MESSAGE_ORIGIN_ = Symbol.intern ("GO-TO-MESSAGE-ORIGIN"),
    //GO_TO_REFERENCED_ITEM_ = Symbol.intern ("GO-TO-REFERENCED-ITEM"),
    ENABLE_ = Symbol.intern ("ENABLE"),
    DISABLE_ = Symbol.intern ("DISABLE"),
    DESCRIBE_ = Symbol.intern ("DESCRIBE"),
    //VIEW_CHANGE_LOG_ = Symbol.intern ("VIEW-CHANGE-LOG"),
    //DYNAMIC_RULE_INVOCATION_DISPLAY_ = Symbol.intern ("DYNAMIC-RULE-INVOCATION-DISPLAY"),
    DESCRIBE_CONFIGURATION_ = Symbol.intern ("DESCRIBE-CONFIGURATION"),
    PRINT_ = Symbol.intern ("PRINT"),
    SHRINK_WRAP_ = Symbol.intern ("SHRINK-WRAP"),
    NAME_ = Symbol.intern ("NAME"),
    CLONE_WORKSPACE_ = Symbol.intern ("CLONE-WORKSPACE"),
    GO_TO_SUBWORKSPACE_ = Symbol.intern ("GO-TO-SUBWORKSPACE"),
    CREATE_SUBWORKSPACE_ = Symbol.intern ("CREATE-SUBWORKSPACE"),
    CREATE_INSTANCE_ = Symbol.intern ("CREATE-INSTANCE"),
    EDIT_ICON_ = Symbol.intern ("EDIT-ICON"),
    ROTATE_REFLECT_ = Symbol.intern ("ROTATE-REFLECT"),
    DELETE_WORKSPACE_ = Symbol.intern ("DELETE-WORKSPACE"),
    MARK_TO_STRIP_TEXT_ = Symbol.intern("MARK-TO-STRIP-TEXT"),
    MARK_NOT_TO_STRIP_TEXT_ = Symbol.intern("MARK-NOT-TO-STRIP-TEXT"),
    REMOVE_STRIP_TEXT_MARK_ = Symbol.intern("REMOVE-STRIP-TEXT-MARK"),
    REMOVE_DO_NOT_STRIP_TEXT_MARK_ = Symbol.intern("REMOVE-DO-NOT-STRIP-TEXT-MARK"),
    EDIT_CELLS_ = Symbol.intern("EDIT-CELLS");
  
  static {
    t2SystemMenuChoices.put(TABLE_, PROPERTIES);
    t2SystemMenuChoices.put(EDIT_, EDIT_TEXT);
    t2SystemMenuChoices.put(TRANSFER_, CUT);
    t2SystemMenuChoices.put(EDIT_ATTRIBUTE_DISPLAY_LAYOUT_, EDIT_ATTRIBUTE_DISPLAY_LAYOUT);
    t2SystemMenuChoices.put(CLONE_, COPY);
    //t2SystemMenuChoices.put(CHANGE_MIN_SIZE_, );
    t2SystemMenuChoices.put(ALIGN_TEXT_, ALIGN_TEXT);
    t2SystemMenuChoices.put(COLOR_, COLOR);
    t2SystemMenuChoices.put(DELETE_, DELETE);
    t2SystemMenuChoices.put(DROP_TO_BOTTOM_, DROP_TO_BOTTOM);
    t2SystemMenuChoices.put(LIFT_TO_TOP_, LIFT_TO_TOP);
    //t2SystemMenuChoices.put(GO_TO_MESSAGE_ORIGIN_, );
    //t2SystemMenuChoices.put(GO_TO_REFERENCED_ITEM_, );
    t2SystemMenuChoices.put(ENABLE_, ENABLE);
    t2SystemMenuChoices.put(DISABLE_, DISABLE);
    t2SystemMenuChoices.put(DESCRIBE_,DESCRIBE);
    //t2SystemMenuChoices.put(VIEW_CHANGE_LOG_, );
    //t2SystemMenuChoices.put(DYNAMIC_RULE_INVOCATION_DISPLAY_, );
    t2SystemMenuChoices.put(DESCRIBE_CONFIGURATION_, DESCRIBE_CONFIGURATION);
    t2SystemMenuChoices.put(PRINT_, PRINT);
    t2SystemMenuChoices.put(MARK_TO_STRIP_TEXT_, MARK_TO_STRIP_TEXT);
    t2SystemMenuChoices.put(MARK_NOT_TO_STRIP_TEXT_, MARK_NOT_TO_STRIP_TEXT);
    t2SystemMenuChoices.put(REMOVE_STRIP_TEXT_MARK_, REMOVE_STRIP_TEXT_MARK);
    t2SystemMenuChoices.put(REMOVE_DO_NOT_STRIP_TEXT_MARK_, REMOVE_DO_NOT_STRIP_TEXT_MARK);
    t2SystemMenuChoices.put(SHRINK_WRAP_, SHRINK_WRAP);
    //t2SystemMenuChoices.put(NEW_BUTTON_, pbk
    //t2SystemMenuChoices.put(NEW_FREE-TEXT_
    //t2SystemMenuChoices.put(NEW_DEFINITION_
    //t2SystemMenuChoices.put(NEW_DISPLAY_
    //t2SystemMenuChoices.put(NEW_RULE_
    //t2SystemMenuChoices.put(NEW_OBJECT_
    t2SystemMenuChoices.put(NAME_, NAME);
    t2SystemMenuChoices.put(CLONE_WORKSPACE_, CLONE_WORKSPACE); 
    //t2SystemMenuChoices.put(HIDE-WORKSPACE
    t2SystemMenuChoices.put(DELETE_WORKSPACE_, DELETE);
    //t2SystemMenuChoices.put(LAUNCH-ONLINE-HELP
    //t2SystemMenuChoices.put(SHORT-MENUS
    //t2SystemMenuChoices.put(CREATE-NEW-MODULE
    //t2SystemMenuChoices.put(DELETE-MODULE
    //t2SystemMenuChoices.put(TURN-ON-ALL-EXPLANATION-CACHING
    //t2SystemMenuChoices.put(TURN-OFF-ALL-EXPLANATION-CACHING
    //t2SystemMenuChoices.put(ENTER-PACKAGE-PREPARATION-MODE
    //t2SystemMenuChoices.put(LEAVE-PACKAGE-PREPARATION-MODE
    //t2SystemMenuChoices.put(STRIP-TEXTS-NOW
    //t2SystemMenuChoices.put(MAKE-WORKSPACES-PROPRIETARY-NOW
    //t2SystemMenuChoices.put(FLUSH-CHANGE-LOG-FOR-ENTIRE-KB
    //t2SystemMenuChoices.put(ENTER-SIMULATE-PROPRIETARY-MODE
    //t2SystemMenuChoices.put(LEAVE-SIMULATE-PROPRIETARY-MODE
    //t2SystemMenuChoices.put(SHUT-DOWN-G2
    //t2SystemMenuChoices.put(CLEAR-KB
    //t2SystemMenuChoices.put(LOAD-ATTRIBUTE-FILE
    //t2SystemMenuChoices.put(DISCONNECT-FROM-FOREIGN-IMAGE
    //t2SystemMenuChoices.put(CONNECT-TO-FOREIGN-IMAGE
    //t2SystemMenuChoices.put(TELEWINDOWS-STATUS-TABLE
    //t2SystemMenuChoices.put(MEMORY-MANAGEMENT-TABLE
    //t2SystemMenuChoices.put(REINSTALL-AUTHORIZED-USERS
    //t2SystemMenuChoices.put(CHANGE-PASSWORD
    //t2SystemMenuChoices.put(LOG-OUT
    //t2SystemMenuChoices.put(CLOSE-TELEWINDOWS-CONNECTION
    //t2SystemMenuChoices.put(NETWORK-INFO
    //t2SystemMenuChoices.put(NEATLY-STACK-WINDOWS
    //t2SystemMenuChoices.put(NEW-TITLE-BLOCK
    //t2SystemMenuChoices.put(CHANGE-MODE
    //t2SystemMenuChoices.put(DO-NOT-HIGHLIGHT-INVOKED-RULES
    //t2SystemMenuChoices.put(HIGHLIGHT-INVOKED-RULES
    //t2SystemMenuChoices.put(ENABLE-ALL-ITEMS
    //t2SystemMenuChoices.put(REMOVE-TRACING-AND-BREAKPOINTS
    //t2SystemMenuChoices.put(SAVE-KB
    //t2SystemMenuChoices.put(MERGE-KB
    //t2SystemMenuChoices.put(LOAD-KB
    //t2SystemMenuChoices.put(INSPECT
    //t2SystemMenuChoices.put(GET-WORKSPACE
    //t2SystemMenuChoices.put(NEW-WORKSPACE
    //t2SystemMenuChoices.put(RESTART
    //t2SystemMenuChoices.put(RESET
    //t2SystemMenuChoices.put(CONTINUE-FROM-BREAKPOINT
    //t2SystemMenuChoices.put(RESUME
    //t2SystemMenuChoices.put(PAUSE
    //t2SystemMenuChoices.put(START
    //t2SystemMenuChoices.put(OPERATE-ON-AREA
    t2SystemMenuChoices.put(EDIT_CELLS_, EDIT_CELLS);
    //t2SystemMenuChoices.put(DELETE-COLUMN
    //t2SystemMenuChoices.put(DELETE-ROW
    //t2SystemMenuChoices.put(ADD-COLUMN
    //t2SystemMenuChoices.put(ADD-ROW
    t2SystemMenuChoices.put(GO_TO_SUBWORKSPACE_, GO_TO_SUBWORKSPACE);
    t2SystemMenuChoices.put(CREATE_SUBWORKSPACE_, CREATE_SUBWORKSPACE);
    t2SystemMenuChoices.put(CREATE_INSTANCE_, CREATE_INSTANCE);
    t2SystemMenuChoices.put(EDIT_ICON_, EDIT_ICON);
    //t2SystemMenuChoices.put(TABLE-OF-VALUES
    //t2SystemMenuChoices.put(DYNAMIC-GENERIC-RULE-DISPLAY
    t2SystemMenuChoices.put(ROTATE_REFLECT_, ROTATE_REFLECT);
    //t2SystemMenuChoices.put(PLOTS /pbk
    //t2SystemMenuChoices.put(VALUE-AXES
    //t2SystemMenuChoices.put(TIME-AXIS-SUBTABLE
    //t2SystemMenuChoices.put(POINT-FORMATS
    //t2SystemMenuChoices.put(CONNECTOR-FORMATS
    //t2SystemMenuChoices.put(TREND-CHART-FORMAT-SUBTABLE
    /*EXCEPTIONS!!!!
      PASTE
      table choices (transfer, show-attribute-display, hide-table, move,
      add-name-of-attribute, hide-attribute-display
      add-another-attribute)
      */
    
  }

  private Sequence getChoicesForItem(Item focalItem)
       throws G2AccessException
  {
    int marked=SELECTION_MIXED;
    Sequence systemMenuChoices;
    if (focalItem instanceof TableItem) {
      systemMenuChoices = new Sequence();
      systemMenuChoices.addElement(DELETE_);
      systemMenuChoices.addElement(TRANSFER_);
    } else {
      Symbol userMode = cxn.getUserMode ();
      ConfigurationSupport.setUserMode(userMode);
      systemMenuChoices = (Sequence)((Block)focalItem).getSystemMenuChoicesForClass();
      Structure restrictionStruct
	= ConfigurationSupport.getChoiceRestrictions(focalItem, ITEM_MENU_);
      Boolean permitted 
	= (Boolean)restrictionStruct.getAttributeValue(PERMITTED_, Boolean.FALSE);
      Sequence choiceRestrictions
	= (Sequence) restrictionStruct.getAttributeValue(CHOICE_RESTRICTIONS_,
							 new Sequence());
      systemMenuChoices 
	= ConfigurationSupport.filterChoicesByRestrictions(systemMenuChoices,
							   choiceRestrictions,
							   permitted.booleanValue());
    }
    int numSMCs = systemMenuChoices.size ();
    Sequence choices = new Sequence(numSMCs);
    if (numSMCs > 0) {
      for (int i=0; i<numSMCs; i++) {
	Symbol smcLabel = (Symbol) systemMenuChoices.elementAt(i);
	String t2SmcLabel = (String)t2SystemMenuChoices.get(smcLabel);
	if (t2SmcLabel != null) {
	  choices.addElement(t2SmcLabel);
	} 
      }
    }
    if (!focalItem.isProprietaryThroughContainment()) {
      choices.addElement(PASTE);
      if (isJDK12 &&
	  ((focalItem instanceof Entity && !(focalItem instanceof Connection))
	  || focalItem instanceof TableItem))
	choices.addElement(EDIT_ATTRIBUTE_DISPLAY_LAYOUT);      
    }
    if (packagePreparationMode) {
      if (!(focalItem instanceof TableItem) &&
	  !(focalItem instanceof NameBox)) {
	marked = getTextMarkStatusOfSelection(STRIP_TEXT_MARK_);
	if (marked == SELECTION_MARKED)
	  choices.addElement(REMOVE_STRIP_TEXT_MARK);
	else
	  choices.addElement(MARK_TO_STRIP_TEXT);
	marked = getTextMarkStatusOfSelection(DO_NOT_STRIP_TEXT_MARK_);
	if (marked == SELECTION_MARKED)
	  choices.addElement(REMOVE_DO_NOT_STRIP_TEXT_MARK);
	else
	  choices.addElement(MARK_NOT_TO_STRIP_TEXT);
      }
    }
    if (!(focalItem instanceof ClassDefinition)) {
      choices.removeElement(CREATE_INSTANCE);
      choices.removeElement(EDIT_ICON);      
    }
    if (focalItem instanceof FreeformTable)
      choices.addElement(EDIT_CELLS);
    if (!(focalItem instanceof TextBox ||
	  (focalItem instanceof Procedure &&
	   !(focalItem instanceof MethodDeclaration))))
      choices.removeElement (EDIT_TEXT);
    determineSelectionEnabledStatus ();
    if (selectionStatus == SELECTION_MIXED) {
      choices.removeElement(ENABLE);
      choices.removeElement(DISABLE);
    } else if (selectionStatus == SELECTION_ENABLED)
      choices.removeElement(ENABLE);
    else if (selectionStatus == SELECTION_DISABLED)
      choices.removeElement(DISABLE);
    if (focalItem instanceof Graph) {
      choices.removeElement(GO_TO_SUBWORKSPACE);
      choices.removeElement(CREATE_SUBWORKSPACE);      
    }    
    if (focalItem instanceof Entity) {
      if (((Entity)focalItem).getSubworkspace() == null)
	choices.removeElement(GO_TO_SUBWORKSPACE);
      else
	choices.removeElement(CREATE_SUBWORKSPACE);
    } else if (focalItem instanceof KbWorkspace) {
      choices.removeElement (LIFT_TO_TOP);
      choices.removeElement (DROP_TO_BOTTOM);
    }
    systemMenuChoices=choices;
    //systemMenuChoiceLabels = new String[numSMCs];
    return systemMenuChoices;
  }

  private void determineSystemMenuChoices()
  {
    focalItems.removeAllElements();
    if (currentSelection.length > 0) {
      for (int i=0;i<currentSelection.length;i++) 
	focalItems.addElement(currentSelection[i].getItem());
    } else 
      focalItems.addElement(wkspView.getWorkspace());

    cxn = (TwConnection)((ImplAccess)wkspView.getWorkspace()).getContext();
    if (cxn.getG2Version().getMajorVersion() >= 6) {
      try {
      packagePreparationMode =
	((Boolean)cxn.callRPC(G2_GET_PACKAGE_PREPARATION_MODE_, new Object[] {})).booleanValue();
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	packagePreparationMode = false;
      }
    } else
      packagePreparationMode = false;
										   
    Enumeration e = focalItems.elements();
    boolean firstItem = true;
    while (e.hasMoreElements()) {
      try {
	Sequence menuChoices = getChoicesForItem((Item)e.nextElement());
	if (firstItem)
	  systemMenuChoices = menuChoices;
	else
	  systemMenuChoices = exclusiveAnd(systemMenuChoices, menuChoices);
      } catch (G2AccessException g2ae) {
	Trace.exception (g2ae);
	systemMenuChoices = new Sequence();
	return;
      }
      firstItem = false;
    }
  }

  private Sequence exclusiveAnd(Sequence seq1,
				Sequence seq2)
  {
    Sequence newSequence = new Sequence();
    Enumeration e = seq1.elements();
    while (e.hasMoreElements()) {
      Object o = e.nextElement();
      if (seq2.contains(o))
	newSequence.addElement(o);
    }
    return newSequence;
  }
  
  private static final String CLIPBOARD = "clipboard";
  private static final String ORDER_AND_POSITION = "order and position";
  private static final String STATUS = "status";
  private static final String EDITING = "editing";
  private static final String SUBWORKSPACE = "subworkspace";
  private static final String PACKAGE_PREPARATION = "package preparation";
  private static final String DESCRIPTIONS = "descriptions";
  private static final String OTHER = "other";
  private static Hashtable groupMapping = new Hashtable();
  private static Vector groupNames = new Vector();
  private static Hashtable groups = new Hashtable();
  
  private static final void defineGroup(String groupName,
					String[] groupKeys)
  {
    groupNames.addElement(groupName);
    groups.put(groupName, groupKeys);
    for(int i=0;i<groupKeys.length;i++) {
      String key = groupKeys[i];
      groupMapping.put(key, groupName);
    }
  }
  
  private static final String getGroupName(String key)
  {
    String name = (String)groupMapping.get(key);
    if (name == null) name =  OTHER;
    return name;
  }

  private static final String[] getGroupKeys(String groupName)
  {
    return (String[])groups.get(groupName);
  }
  
  static {
    defineGroup(CLIPBOARD, new String[] {CUT, COPY, PASTE});
    defineGroup(DELETE, new String[] {CREATE_INSTANCE, DELETE, NAME, ENABLE, DISABLE});
    //defineGroup(STATUS, new String[] {ENABLE, DISABLE});
    defineGroup(SUBWORKSPACE, new String[] {CREATE_SUBWORKSPACE, GO_TO_SUBWORKSPACE});
    defineGroup(ORDER_AND_POSITION, new String[] {LIFT_TO_TOP, DROP_TO_BOTTOM, ROTATE_REFLECT, ALIGN_TEXT, COLOR});
    defineGroup(DESCRIPTIONS, new String[] {DESCRIBE, DESCRIBE_CONFIGURATION});
    defineGroup(OTHER, new String[] {});    
    defineGroup(PACKAGE_PREPARATION, new String[] {MARK_TO_STRIP_TEXT,REMOVE_STRIP_TEXT_MARK,
						     MARK_NOT_TO_STRIP_TEXT, REMOVE_DO_NOT_STRIP_TEXT_MARK});
    defineGroup(EDITING, new String[] {EDIT_TEXT, EDIT_ICON, PROPERTIES});
  }

  private static Vector textAlignmentChoices = new Vector();
  static {
    textAlignmentChoices.addElement(LEFT);
    textAlignmentChoices.addElement(CENTER);
    textAlignmentChoices.addElement(RIGHT);
  }
  private static SubCommand alignTextMenuStructure
  = new SubCommand(ALIGN_TEXT, textAlignmentChoices);

  private static Vector rotateChoices = new Vector();
  static {
    rotateChoices.addElement(ROTATE_90_CLOCKWISE);
    rotateChoices.addElement(ROTATE_90_COUNTER_CLOCKWISE);
    rotateChoices.addElement(ROTATE_180_DEGREES);
  }
  private static Vector flipChoices = new Vector();
  static {
    flipChoices.addElement(FLIP_HORIZONTAL);
    flipChoices.addElement(FLIP_VERTICAL);
  }
  
  private static Vector rotateReflectChoices = new Vector();
  static {
    rotateReflectChoices.addElement(rotateChoices);
    rotateReflectChoices.addElement(flipChoices);
  }
  private static SubCommand rotateReflectStructure 
  = new SubCommand(ROTATE_REFLECT, rotateReflectChoices);
  
  private Object getStructureForKey(String key) {
    if (ALIGN_TEXT.equals(key))
      return alignTextMenuStructure;
    else if (ROTATE_REFLECT.equals(key))
      return rotateReflectStructure;
    else 
      return key;
  }

  private Vector organizeKeys(Vector flatKeys)
  {
    Enumeration e = flatKeys.elements();
    Hashtable currentGroups = new Hashtable();
    while(e.hasMoreElements()) {
      String key = (String)e.nextElement();
      String groupName = getGroupName(key);
      if (groupName == null) groupName = OTHER;
      Vector subGroup = (Vector)currentGroups.get(groupName);
      if (subGroup == null) {
	subGroup = new Vector();
	currentGroups.put(groupName, subGroup);
      }
      subGroup.addElement(getStructureForKey(key));
    }
    Vector keys = new Vector ();
    e = groupNames.elements();
    while (e.hasMoreElements()) {
      String groupName = (String)e.nextElement();
      Vector group = (Vector)currentGroups.get(groupName);
      if (group != null) keys.addElement(group);
    }
    return keys;
  }
  
  /**
   * Returned the keys for the actions that
   * can be performed by this command. This is
   * basically just a list of the labels of the
   * applicable system-menu-choices for the items
   * in the selection, or the kb-workspace if
   * the selection is empty.
   */
  @Override
  public Vector getStructuredKeys () {
    determineSystemMenuChoices();
    return organizeKeys(systemMenuChoices);   
  }


  private static boolean instanceOf (Vector objects,
				     Class[] classesToExclude,
				     Class[] subClassesToInclude) {
    Enumeration e = objects.elements();
    while (e.hasMoreElements()) {
      Object object = e.nextElement();
      for (int i=0;i<classesToExclude.length;i++) {
	if (classesToExclude[i].isInstance(object)) {
	  boolean included = false;
	  for (int j=0;j<subClassesToInclude.length && !included;j++) 
	    included = subClassesToInclude[j].isInstance(object);
	  if (!included)
	    return true;
	}
      }
    }
    return false;    
  }
  
  private static boolean instanceOf (Vector objects,
				     Class[] classes)
  {
    return instanceOf(objects, classes, new Class[0]);
  }

  private static final Class[]
  NAME_EXCLUDE_CLASSES
  = {Procedure.class, ClassDefinition.class, Relation.class},
  NAME_INCLUDE_SUBCLASSES
  = {MethodDeclaration.class},
  CREATE_INSTANCE_INCLUDE_CLASSES
  = {ClassDefinition.class},
  CREATE_INSTANCE_EXCLUDE_CLASSES
  = {ConnectionDefinition.class},
  LAYER_CHANGE_EXCLUDE_CLASSES
  = {NameBox.class};
  private static final Symbol NONE_ = Symbol.intern ("NONE");
  private int getTextMarkStatusOfSelection(Symbol property) {
    Item loopItem;
    Boolean prevMarkStatus = null; 
    if (!packagePreparationMode)
      return SELECTION_MIXED;
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
    
    if (currentSelection.length != 0)
      return prevMarkStatus.booleanValue()?SELECTION_MARKED:SELECTION_UNMARKED;
     else {
      try {
	boolean marked = ((Boolean)wkspView.getWorkspace().getPropertyValue(property)).booleanValue();
	return marked?SELECTION_MARKED:SELECTION_UNMARKED;
      } catch (NoSuchAttributeException nsae) {
	Trace.exception(nsae);
	return SELECTION_MIXED;
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	return SELECTION_MIXED;
      }
    }
  }

  @Override
  public boolean isAvailable (String cmdKey) {
    boolean cmdAvailable = true;
    checkKey (cmdKey);
    int markText;
    if (cmdKey.equals(DISABLE)) {
      determineSelectionEnabledStatus ();
      if ((selectionStatus == SELECTION_DISABLED) || (selectionStatus == SELECTION_MIXED))
	cmdAvailable =  false;
    }
    else if (cmdKey.equals(ENABLE)) {
      determineSelectionEnabledStatus ();
      if ((selectionStatus == SELECTION_ENABLED) || (selectionStatus == SELECTION_MIXED))
	cmdAvailable = false;
    } else if (cmdKey.equals(MARK_TO_STRIP_TEXT)) {
      markText = getTextMarkStatusOfSelection(STRIP_TEXT_MARK_);
      if ((markText == SELECTION_MIXED) || (markText == SELECTION_MARKED))
	cmdAvailable = false;
    } else if (cmdKey.equals(MARK_NOT_TO_STRIP_TEXT)) {
      markText = getTextMarkStatusOfSelection(DO_NOT_STRIP_TEXT_MARK_);
      if ((markText == SELECTION_MIXED) || (markText == SELECTION_MARKED))
	cmdAvailable = false;
    } else if (cmdKey.equals(REMOVE_STRIP_TEXT_MARK)) {
      markText = getTextMarkStatusOfSelection(STRIP_TEXT_MARK_);
      if ((markText == SELECTION_MIXED) || (markText == SELECTION_UNMARKED))
	cmdAvailable = false;
    } else if (cmdKey.equals(REMOVE_DO_NOT_STRIP_TEXT_MARK)) {
      markText = getTextMarkStatusOfSelection(DO_NOT_STRIP_TEXT_MARK_);
      if ((markText == SELECTION_MIXED) || (markText == SELECTION_UNMARKED))
	cmdAvailable = false;
    } else if (COLOR.equals(cmdKey)) {
    } else if (SHRINK_WRAP.equals(cmdKey)) {
      if (!wkspView.getElements().hasMoreElements())
	cmdAvailable = false;
    } else if (LIFT_TO_TOP.equals(cmdKey) ||
	       DROP_TO_BOTTOM.equals(cmdKey)) {
      cmdAvailable = !(instanceOf (focalItems,
				   LAYER_CHANGE_EXCLUDE_CLASSES));
    } else if (NAME.equals(cmdKey)) {
      cmdAvailable = !(instanceOf(focalItems,
				  NAME_EXCLUDE_CLASSES,
				  NAME_INCLUDE_SUBCLASSES));
    } else if (CREATE_INSTANCE.equals(cmdKey)) {
      if ((instanceOf(focalItems, CREATE_INSTANCE_INCLUDE_CLASSES) && 
	   !(instanceOf(focalItems, CREATE_INSTANCE_EXCLUDE_CLASSES))))
	{
	  Enumeration e = focalItems.elements();
	  while(e.hasMoreElements()) {
	    ClassDefinition def = (ClassDefinition)e.nextElement();
	    try {
	      Sequence superiors = def.getDirectSuperiorClasses();
	      Symbol className = def.getClassName();
	      if (className == null ||
		  NONE_.equals(className) ||
		  superiors == null ||
		  superiors.isEmpty() ||
		  superiors.contains(CONNECTION_)) {
		cmdAvailable = false;
		break;
	      }
	    } catch (G2AccessException g2ae) {
	      cmdAvailable = false;
	      Trace.exception(g2ae);
	      break;
	    }
	  }
	} else
	  cmdAvailable = false;
    }
    if (isClipboardAction (cmdKey) && !wkspView.okToUseCutCopyPaste)
      return false;
    if (cmdKey.equals (CUT) || cmdKey.equals (COPY)) {
      if (currentSelection.length == 0)
	return false;
      for (int i=0; i<currentSelection.length; i++)
	if (!(wkspView.elementIsTransferrable (currentSelection[i])))
	  return false;
      return true;
    }
    if (cmdKey.equals (PASTE)) {
      Transferable clipboardContents = clipboard.getContents (wkspView);
      boolean pasteAllowed = checkPasteCompatibility (clipboardContents);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "pasteAllowed",
		  pasteAllowed ? Boolean.TRUE : Boolean.FALSE, clipboardContents);
      return pasteAllowed;
    }
    return cmdAvailable;
  }

  @Override
  protected void reset () {
    selectionStatus = SELECTION_UNKNOWN;
    super.reset ();
  }

  private boolean checkPasteCompatibility (Transferable clipboardContents) {
    if (clipboardContents == null)
      return false;
    DataFlavor[] availableFlavors = clipboardContents.getTransferDataFlavors ();
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "availableFlavorsForPaste", 
		com.gensym.core.DebugUtil.printArray (availableFlavors));
    if (availableFlavors == null)
      return false;
    return (availableFlavors[0].equals (WorkspaceClipboardData.G2ObjectFlavor) &&
	    ((WorkspaceClipboardData)clipboardContents).checkPasteCompatibility (wkspView));
  }

  private void determineSelectionEnabledStatus() {
    //System.out.println("isSelectionEnabled? currentSelection.length: ["+currentSelection.length+"]");
    if (selectionStatus != SELECTION_UNKNOWN)
      return;
    int status = SELECTION_MIXED;

    int numEnabled = 0;
    for (int i=0; i<currentSelection.length; i++) {
      try {
	if (!currentSelection[i].getItem().getManuallyDisabled())
	  numEnabled += 1;
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    //System.out.println("currentSelection.length: "+currentSelection.length+"  numEnabled: "+numEnabled);

    if (currentSelection.length != 0) {
      if (numEnabled == currentSelection.length) { 
	// disable ENABLE, enable DISABLE
	status = SELECTION_ENABLED;
      } else if (numEnabled == 0) {
	// enable ENABLE, disable DISABLE
	status = SELECTION_DISABLED;
      } else status = SELECTION_MIXED;
    } else {
      // The user clicked on the the workspaceView
      try {
	if (wkspView.getWorkspace().isEnabled())
	  status = SELECTION_ENABLED;
	else
	  status = SELECTION_DISABLED;
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }
    selectionStatus = status;
  }

  /**
   * @undocumented
   * @param arg should be either a symbol naming the class or an
   * Integer representing the number of items to be deleted.
   */
  public static boolean okayToDelete (Object arg) {
    if (!promptForDelete)
      return true;
    String prompt, title;
    if (arg instanceof Symbol) {
      Symbol className_ = (Symbol)arg;
      prompt = workspaceMessages.format ("deleteItemPrompt", className_.getPrintValue().toLowerCase());
      title = workspaceMessages.getString ("deleteItemPromptTitle");
    } else {
      prompt = workspaceMessages.format ("deleteItemsPrompt", (Integer) arg);
      title = workspaceMessages.getString ("deleteItemsPromptTitle");
    }
    YesNoDialog ynDlg = new YesNoDialog (title, true, prompt);
    ynDlg.setVisible (true);
    return !(ynDlg.wasCancelled ());
  }

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


class YesNoDialog extends QuestionDialog {
  YesNoDialog (String title, boolean isModal, String prompt) {
    super (null, title, isModal,
	   new String[] {YES_LABEL, NO_LABEL},
	   new int[] {YES, CANCEL},
	   prompt,
	   null, // image 
	   null);
    setDefaultButton (YES);
    setCancelButton (CANCEL);
  }
}
  
  
  



