
package com.gensym.wksp;

import java.awt.Component;
import java.awt.Cursor;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Frame;
import java.awt.Image;
import java.awt.Insets;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.ActionEvent;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.ObjectInputStream;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.io.File;
import java.util.Hashtable;
import java.util.StringTokenizer;
import java.util.Vector;
import javax.swing.JScrollPane;
import javax.swing.ScrollPaneConstants;
import com.gensym.classes.Block;
import com.gensym.classes.ClassDefinition;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.SystemClassDefinitionImpl;
import com.gensym.classes.UserMenuChoice;
import com.gensym.classes.UiClientSession;
import com.gensym.core.DebugUtil;
import com.gensym.dlg.CommandConstants;
import com.gensym.dlg.InputDialog;
import com.gensym.dlg.MessageDialog;
import com.gensym.dlg.QuestionDialog;
import com.gensym.dlg.SelectionDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnection;
import com.gensym.ntw.TwConnectionListener;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.ntw.TwConnectionAdapter;
import com.gensym.ntw.util.ClassChooserDialog;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.ntw.util.G2Palette;
import com.gensym.ntw.util.G2ObjectCreator;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.symbol.G2ClassSymbols;
import com.gensym.wksp.configurations.ConfigurationSupport;
import com.gensym.wksp.configurations.ConfigurationSymbols;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.StructuredCommand;
import com.gensym.ui.Command;
import com.gensym.ui.CommandListener;
import com.gensym.ui.CommandEvent;
import com.gensym.ui.StructuredCommandListener;
import com.gensym.ui.menu.awt.CPopupMenu;
import com.gensym.wksp.ItemPaletteDialog;
import com.gensym.wksp.PaletteCommands;
import com.gensym.wksp.GenericPaletteDialog;
import java.awt.Toolkit;
import java.awt.Image;


/**
 * An implementation of the SelectionCommand interface that
 * exposes the applicable user-menu-choices of the selected
 * item(s) on the PopupMenu that is generated for the
 * selection.
 * @see com.gensym.wksp.SelectionCommandGenerator
 * @see com.gensym.wksp.SelectionCommand
 * 
 * @author vkp
 * @version 1.0 - 5/7/98
 *
 */
public class CreationCommands extends AbstractMenuChoiceCommands implements ConfigurationSymbols, Runnable {

  private Vector userMenuChoices;
  private String[] userMenuChoiceLabels;

  private Item focalItem;
  private TwConnection cxn;

  private boolean allowCreation, allowBeans;

  public static final String
    NEW_ITEM = "newitem",
    NEW_BEAN = "newbean";

  private Image newItemImage;
  @Override
  public Image getIcon (String cmdKey, String key) {
    if (NEW_ITEM == cmdKey) {
      if (newItemImage == null)
	newItemImage =  Toolkit.getDefaultToolkit().getImage(this.getClass().getResource("newItem.gif"));
      return newItemImage;
    } else
      return null;
  }
  
  private Vector choices = new Vector ();

  private String commandKey;

  static final Resource i18n = Resource.getBundle ("com/gensym/wksp/UiLabels");
  private static final Resource i18nLong = Resource.getBundle ("com/gensym/wksp/UiLabelsLong");


  private static final Symbol T2BEANS_GET_IMPORTED_BEAN_CLASS_NAMES_ = Symbol.intern ("T2BEANS-GET-IMPORTED-BEAN-CLASS-NAMES");
  private static final Symbol NEW_OBJECT_ = Symbol.intern ("NEW-OBJECT");
  /**



   * Creates a new CreationCommands that can be used to
   * generate PopupMenus for Items on workspaces.
   * @see com.gensym.wksp.SelectionCommandGenerator
   */
  public CreationCommands () {
    super (new String[] {NEW_ITEM, NEW_BEAN});
  }

  private static final Symbol G2_GET_UNIQUE_NAMED_ITEM_ = Symbol.intern ("G2-GET-UNIQUE-NAMED-ITEM");
  private static final java.lang.Object[] getModuleArgs = new java.lang.Object[2];
  static {
    getModuleArgs[0] = Symbol.intern ("ITEM");
    getModuleArgs[1] = Symbol.intern ("BEANS-REGISTRY");
  }

  @Override
  public void setWorkspaceView (WorkspaceView view) {
    super.setWorkspaceView (view);
    choices = null;
    if (view == null) return;
    KbWorkspace wksp = (KbWorkspace) view.getItem ();
    if (wksp == null)
      return;
    TwConnection cxn = (TwConnection)((com.gensym.classes.ImplAccess)wksp).getContext ();
    try {
      Symbol userMode = cxn.getUserMode ();

      Structure restrictionStruct
	= ConfigurationSupport.getChoiceRestrictions(wksp, ITEM_MENU_);
      Boolean permitted 
	= (Boolean)restrictionStruct.getAttributeValue(PERMITTED_, Boolean.FALSE);
      Sequence choiceRestrictions
	= (Sequence) restrictionStruct.getAttributeValue(CHOICE_RESTRICTIONS_, new Sequence());
      Sequence menuChoices = new Sequence ();
      menuChoices.addElement (NEW_OBJECT_);
      menuChoices
	= ConfigurationSupport.filterChoicesByRestrictions(menuChoices,
							   choiceRestrictions,
							   permitted.booleanValue());
      allowCreation = (menuChoices.size () > 0);
      allowBeans = (!cxn.callRPC(G2_GET_UNIQUE_NAMED_ITEM_, getModuleArgs).equals (Boolean.FALSE));
    } catch (G2AccessException g2ae) {
      Trace.exception (g2ae);
    }
  }

  @Override
  protected void reset () {
    currentSelection = null;
    userMenuChoices = null;
    focalItem = null;
    cxn = null;
  }

  /**
   * Returns a textual description for command.
   * The key should be either SHORT_DESCRIPTION or
   * LONG_DESCRIPTION. This method is overriden to
   * create a "pretty-printed" name.
   */
  @Override
  public String getDescription (String cmdKey, String key) {
    checkKey (cmdKey);
    return i18n.getString (cmdKey);
  }

  /**
   * Returns the keys for the actions that
   * can be performed by this command. This is
   * basically just a list of the labels of the
   * applicable user-menu-choices for the items
   * in the selection, or the kb-workspace if
   * the selection is empty.
   */
  @Override
  public Vector getStructuredKeys () {
    
    if (wkspView != null && currentSelection.length == 0) {
      if (choices == null) {
	choices = new Vector ();
	if (allowCreation)
	  choices.addElement (NEW_ITEM);
	if (allowBeans) {
	  try {
	    TwConnection cxn = (TwConnection)((com.gensym.classes.ImplAccess)wkspView.getWorkspace()).getContext();
	    if (cxn.getG2State ().equals (G2Gateway.RUNNING_))
	      choices.addElement (NEW_BEAN);
	  } catch (G2AccessException g2ae) {
	    Trace.exception (g2ae);
	  }
	}
      }
      return choices;
    } else {
      Vector v = new Vector ();
      //CreationCommands is now also used in the main menu, and will need this choice there even
      //when the view is currently null. The previous case was only for the dynamic popup menu of 
      //a workspace.
      v.addElement(NEW_ITEM);
      return v;
    }
  }


  @Override
  public boolean isAvailable (String cmdKey) {
    boolean cmdAvailable = true;
    return cmdAvailable;
  }

  /**
   * The implementation of the execution of this
   * Command
   */
  @Override
  public synchronized void actionPerformed (ActionEvent e) {
    commandKey = e.getActionCommand ();
    new Thread (this, "Creation-Menu-Choice-Handler").start ();
  }

  @Override
  public synchronized void run () {
    try {
      if (commandKey.equals (NEW_BEAN)) {
	chooseNewBean ();
      } else
	chooseNewItem ();
    } catch (Exception ex) {
      Trace.exception (ex);
      new com.gensym.dlg.ErrorDialog (null, "Error Creating new " +
				      (commandKey.equals (NEW_BEAN) ? "Bean" : "Item"),
				      true, ex.toString (), null).setVisible (true);
    }
  }

  BeanPaletteDialog beanPaletteDialog;
  ItemPaletteDialog itemPaletteDialog;
  private static final Hashtable beanPalettes = new Hashtable (5);
  //private static final Hashtable itemPalettes = PaletteCommands.itemPalettes;;
  private static final TwConnectionListener beanPaletteReaper = 
    new TwConnectionAdapter () {
      @Override
      public void loggedOut (TwConnectionEvent evt) {
		TwConnection cxn = (TwConnection) evt.getSource ();
		beanPalettes.remove (cxn);
		cxn.removeTwConnectionListener (this);
      }
  };
  private void displayPalette () {
    beanPaletteDialog.setVisible (true);
  }

  private boolean x;
  private void chooseNewBean () throws G2AccessException {
    TwConnection cxn = (TwConnection)((com.gensym.classes.ImplAccess)wkspView.getWorkspace()).getContext();
    if (!cxn.getG2State ().equals (G2Gateway.RUNNING_))
      return;
    beanPaletteDialog = (BeanPaletteDialog) beanPalettes.get (cxn);
    if (beanPaletteDialog == null) {
      wkspView.setCursor (Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
      beanPaletteDialog = new BeanPaletteDialog (cxn, beanPalettes);
      cxn.addTwConnectionListener (beanPaletteReaper);
      wkspView.setCursor (Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    }
    displayPalette ();
    if (true)
      return;
    String[] beanClassNames = getRegisteredBeans (cxn);
    SelectionCommandGenerator sg = wkspView.getSelectionCommandGenerator ();
    Point location = sg.getLastPostingLocation ();
    wkspView.translateWindowToView (location);
    wkspView.translateViewToWorkspace (location);
    new SelectionDialog (null, "Create New Bean", false,
			 "Choose Bean Class",
			 beanClassNames, false, -1, true, 
			 new BeanCreationHandler (cxn, wkspView, location, beanClassNames))
      .setVisible (true);
  }

  private void chooseNewItem () {
    TwConnection cxn = (TwConnection)((com.gensym.classes.ImplAccess)wkspView.getWorkspace()).getContext();
    //itemPaletteDialog cannot be null, so no need to test for it
    wkspView.setCursor (Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
    itemPaletteDialog = PaletteCommands.getItemPaletteDialog(cxn);
    wkspView.setCursor (Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    /*if (itemPaletteDialog == null) {
      try {
	System.out.println("no itemPaletteDialog for this connection, creating new");
	wkspView.setCursor (Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
	itemPaletteDialog = new ItemPaletteDialog (cxn, ItemPaletteDialog.itemPalettes);
	itemPaletteDialog.setSize(210, itemPaletteDialog.getPreferredSize().height);
	cxn.addTwConnectionListener (itemPaletteReaper);
	wkspView.setCursor (Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
      } catch (Exception e) {
	Trace.exception (e);
	}}*/
  
    itemPaletteDialog.setVisible(true);
  }

  private static final Symbol JAVA_CLASS_NAME_ = Symbol.intern ("JAVA-CLASS-NAME");
  String[] getRegisteredBeans (TwConnection cxn) {
    try {
      Sequence beansList = (Sequence) cxn.callRPC (T2BEANS_GET_IMPORTED_BEAN_CLASS_NAMES_, new Object[] {});
      String[] beansArray = new String[beansList.size ()];
      for (int i=0; i<beansList.size (); i++){
	Structure beanClassInfo = (Structure) beansList.elementAt (i);
	beansArray[i] = (String)  beanClassInfo.getAttributeValue (JAVA_CLASS_NAME_, null);
      }
      return beansArray;
    } catch (G2AccessException g2ae) {
      // do nothing
    }
    return null;
  }

  @Override
  public boolean isImmediate (String cmdKey) {
    checkKey (cmdKey);
    return false;
  }
}


class BeanCreationHandler implements StandardDialogClient {

  TwConnection cxn;
  WorkspaceView wkspView;
  Point location;
  String[] classNames;

  private static final Symbol T2BEANS_CREATE_BEAN_ = Symbol.intern ("T2BEANS-CREATE-BEAN");

  BeanCreationHandler (TwConnection cxn, WorkspaceView wkspView, Point location, String[] classNames) {
    this.cxn = cxn;
    this.wkspView = wkspView;
    this.location = location;
    this.classNames = classNames;
  }

  @Override
  public void dialogDismissed (StandardDialog dlg, int code) {
    if (dlg.wasCancelled ())
      return;
    SelectionDialog selDlg = (SelectionDialog) dlg;
    int selection = selDlg.getResult ();
    try {
      Item g2bean = (Item)cxn.callRPC (T2BEANS_CREATE_BEAN_, new java.lang.Object[] {classNames[selection]});
      KbWorkspace wksp = wkspView.getWorkspace ();
      g2bean.transferTo (wksp, location.x, location.y);
      g2bean.makePermanent ();
    } catch (G2AccessException g2ae) {
      new MessageDialog (null, CreationCommands.i18n.getString ("beanCreateErrorTitle"), false,
			 g2ae.getMessage (),
			 null).setVisible (true);
    }
  }
}


class BeanPaletteDialog extends GenericPaletteDialog implements ScrollPaneConstants {
  
  static final int IMPORT = 1024;

  BeanPaletteDialog (TwConnection cxn, Hashtable paletteHash) {
    super (cxn,
	   paletteHash,
	   null,
	   CreationCommands.i18n.format ("beansPaletteTitle", cxn.toShortString()),
	   false,
	   new String[] {CreationCommands.i18n.getString ("importBeanLabel")},
	   new int[] {IMPORT},
	   new JScrollPane (null, VERTICAL_SCROLLBAR_NEVER, HORIZONTAL_SCROLLBAR_ALWAYS),
	   new BeanImportLauncher (cxn));
    G2Palette palette = new G2Palette (cxn); //(G2Palette) getDialogComponent ();
    JScrollPane sp = (JScrollPane) getDialogComponent ();
    sp.setViewportView (palette);
    try {
      palette.add (new G2BeanObjectCreator (cxn));
    } catch (G2AccessException g2ae) {
      Trace.exception (g2ae);
    }
    invalidate ();
    pack ();
  }

}



class BeanImportLauncher implements StandardDialogClient {
  
  private TwConnection cxn;
  BeanImportLauncher (TwConnection cxn) {
    this.cxn = cxn;
  }

  @Override
  public void dialogDismissed (StandardDialog dlg, int code) {
    if (dlg.wasCancelled ())
      return;
    dlg.setVisible (false);
    InputDialog iDlg = new InputDialog (null, CreationCommands.i18n.getString ("importBeanTitle"), true,
					new String[] {CreationCommands.i18n.getString ("importBeanPrompt")},
					new String[] {""},
					new BeanImporter (cxn));
    iDlg.setDefaultButton (CommandConstants.OK);
    iDlg.setCancelButton (CommandConstants.CANCEL);
    iDlg.setVisible (true);
    dlg.setVisible (true);
  }
  
}


class BeanImporter implements StandardDialogClient {

  private static final Symbol T2BEANS_GENERATE_CLASS_ = Symbol.intern ("T2BEANS-GENERATE-CLASS");
  private static final Class componentClass = java.awt.Component.class;
  private static final Class windowClass = java.awt.Window.class;

  private TwConnection cxn;
  BeanImporter (TwConnection cxn) {
    this.cxn = cxn;
  }

  @Override
  public void dialogDismissed (StandardDialog dlg, int code) {
    if (dlg.wasCancelled ())
      return;
    String[] results = ((InputDialog)dlg).getResults ();
    String beanClassName = results[0];
    try {
      UiClientSession session = cxn.retrieveSession ();
      String errorMsg = null;
      try {
	Class testClass = Class.forName (beanClassName);
	if (!componentClass.isAssignableFrom (testClass))
	  errorMsg = "notAComponentClassMessage";
	else if (windowClass.isAssignableFrom (testClass))
	  errorMsg = "isAWindowClassMessage";
      } catch (ClassNotFoundException cnfe) {
	Trace.exception (cnfe);
	errorMsg = "beanClassNotFoundMessage";
      }

      if (errorMsg != null) {
	new MessageDialog (null, CreationCommands.i18n.getString ("illegalBeanClassTitle"), true,
			   CreationCommands.i18n.format (errorMsg, beanClassName),
			   null).setVisible (true);
	return;
      }
      cxn.callRPC (T2BEANS_GENERATE_CLASS_,
		   new java.lang.Object[] {session.getUiClientInterface(),
					     beanClassName,
					     Boolean.FALSE});
    } catch (G2AccessException g2ae) {
      Trace.exception (g2ae);
    }
  }

}

