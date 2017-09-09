package com.gensym.wksp;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.Frame;
import java.util.Hashtable;
import java.util.Vector;

import javax.swing.JTabbedPane;

import com.gensym.core.DebugUtil;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.CommandConstants;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnection;
import com.gensym.ntw.util.G2ObjectCreator;
import com.gensym.ntw.util.ClassChooserTabPaneDialog;
import com.gensym.ntw.util.G2Palette;
import com.gensym.ntw.util.ClassChooserPanel;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.Command;
import com.gensym.ui.ObjectCreator;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.wksp.ItemPaletteDialog;

public class PaletteCommands extends AbstractStructuredCommand implements ContextChangedListener {

  public static final String CLASSES = "Classes";
  public static final String HIDE = "Hide";
  private static final String longResource = "com.gensym.wksp.UiLabelsLong";
  private static final String shortResource = "com.gensym.wksp.UiLabels";
  private static final Hashtable itemPalettes = new Hashtable(5);
  private static final Hashtable palettePanes = new Hashtable(5);
  private static final int ICON_ONLY = 0;

  private ConnectionManager cxnMgr;
  private TwAccess currentConnection;
  private G2ConnectionAdapter closeListener;
  private boolean panel;
  
  /* This constructor is needed if PaletteCommands are added to a toolbar,
     which has a connectionManager. The second constructor is needed to
     create another instance of this command to add to a popup menu on a
     workspace. Unfortunately one instance of a command cannot do both. However,
     regardless of the number of PaletteCommands added to an application,
     there will only be one ItemPaletteDialog per connection, and this
     command keeps track of it, through the itemPalettes hashtable. The ItemPaletteDialog
     should only be created through the public method of this command .getItemPaletteDialog.
     That is the only way to ensure that it gets properly entered into the hashtable.
  */

  public PaletteCommands(ConnectionManager cxnManager){
    this();
    cxnMgr = cxnManager;
    cxnMgr.addContextChangedListener((ContextChangedListener)this);
    setConnection(cxnMgr.getCurrentConnection());
  }

  public PaletteCommands(TwAccess connection){
    this();
    setConnection(connection);
  }

  public PaletteCommands(TwAccess connection, PalettePane palettePane) {
    this(connection);
    palettePanes.put((TwConnection)connection, palettePane);
    panel = true;
  }
    
  private PaletteCommands(){
    super(new StructuredCommandInformation[]{
      new CommandGroupInformation("classesGroup", new CommandInformation[]{
	new CommandInformation(CLASSES, false, shortResource, longResource, null, null, null, false,
			       null, null)}),
      new CommandGroupInformation("arrangeGroup", new CommandInformation[]{
	new CommandInformation(HIDE, false, shortResource, longResource, null, null, null, false,
			       null, null)})
	});

    closeListener = new G2CloseAdapter();
  }

  public static PalettePane getPalettePane(TwAccess cxn) {
    if (cxn != null) {
      PalettePane pane = (PalettePane)palettePanes.get((TwConnection)cxn);
      if (pane == null) {
	pane = new PalettePane((TwConnection)cxn,
			       ObjectCreator.SMALL_ICON, ICON_ONLY);
	palettePanes.put((TwConnection)cxn, pane);
      }
      return pane;
    }else return null;
  }
  
  public static ItemPaletteDialog getItemPaletteDialog(TwAccess cxn){
    //this is a get/create and a put into the hashtable
    if(cxn != null){
      ItemPaletteDialog itpDlg = (ItemPaletteDialog)itemPalettes.get((TwConnection)cxn);
      if (itpDlg == null){
	itpDlg = new ItemPaletteDialog((TwConnection)cxn);
	itemPalettes.put((TwConnection)cxn, itpDlg);
      }
      return itpDlg;
    } else return null;
  }

  private void setConnection(TwAccess connection){
    currentConnection = connection;
    if(currentConnection != null){
      currentConnection.addG2ConnectionListener (closeListener);
    }
    setAvailability();
  }

  @Override
  public void currentConnectionChanged(ContextChangedEvent e){
    setConnection(e.getConnection());
  }

  private void setAvailability(){
    if (currentConnection != null){
      setAvailable(CLASSES, true);
      setAvailable(HIDE, true);
    } else {
      setAvailable(CLASSES, false);
      setAvailable(HIDE, false);
    }
  }


  @Override
  public void actionPerformed(ActionEvent event){
    String key = event.getActionCommand();
    ItemPaletteDialog dlg = getItemPaletteDialog(currentConnection);
    JTabbedPane dlgTabbedPane = dlg.getPalettePane().getTabbedPane();
    if (key.equals(CLASSES)){
      int tabSize = dlgTabbedPane.getTabCount();
      Component[] tabComponents = new Component[tabSize];
      String[] tabNames = new String[tabSize];
      Symbol[] classes;
      Vector iconSizes = new Vector(tabSize);
      Vector buttonStyles = new Vector(tabSize);
      for (int i=0; i < tabSize; i++) {
        ((G2Palette) dlgTabbedPane.getComponentAt(i)).dropCancelled();
        iconSizes.addElement(new Integer(((G2Palette) dlgTabbedPane.getComponentAt(i)).getIconSize()));
	buttonStyles.addElement(new Integer(((G2Palette) dlgTabbedPane.getComponentAt(i)).getButtonStyle()));
        classes = translateStringsToSymbols(((G2ObjectCreator) dlg.getPalettePane().getObjectCreators().elementAt(i)).getKeys());
        tabComponents[i] = new ClassChooserPanel(currentConnection, classes);
        tabNames[i] = dlgTabbedPane.getTitleAt(i);
      }
      // launch a new  dialog for editing tabs
      ClassChooserTabPaneDialog d = new ClassChooserTabPaneDialog
	((Frame)dlg.getParent(), true, currentConnection, tabNames,
	 tabComponents, new ClassChooserTabPaneClient(),
	 dlgTabbedPane.getSelectedIndex(), iconSizes, buttonStyles);
      if (panel)
	d.disableRadioButtons();
      d.setVisible(true);

      dlg.validate();
      dlg.repaint();
    }
    else //HIDE
      dlg.setVisible(false);
  }

  private class ClassChooserTabPaneClient implements StandardDialogClient {
    
    @Override
    public void dialogDismissed(StandardDialog thisDialog, int index) {
      ClassChooserTabPaneDialog ccTabDialog = (ClassChooserTabPaneDialog)thisDialog;
      ItemPaletteDialog dlg = getItemPaletteDialog(currentConnection);
      switch (index) {
      case CommandConstants.CANCEL:
	ccTabDialog.dispose();
	break;
      case CommandConstants.OK:
	applyDialog(ccTabDialog, dlg);
	ccTabDialog.dispose();
	break;
      case CommandConstants.APPLY:
	applyDialog(ccTabDialog, dlg);
	break;
      }
    }

    private void applyDialog(ClassChooserTabPaneDialog ccTabDialog, ItemPaletteDialog dlg) {
      JTabbedPane classChooserTabPane = ccTabDialog.getClassChooserTabPane();
      JTabbedPane itemPaletteTabPane = dlg.getPalettePane().getTabbedPane();
      Vector iconSizes = ccTabDialog.getIconSizes();
      Vector buttonStyles = ccTabDialog.getButtonStyles();
      Sequence paletteTabs = new Sequence();
      PalettePane dlgPane = dlg.getPalettePane();
      PalettePane palettePane = getPalettePane(currentConnection);
      for (int i=0; i < classChooserTabPane.getTabCount(); i++) {
        Symbol[] newClasses = ccTabDialog.getSelection(i);
        Symbol[] filteredNewClasses = new Symbol[newClasses.length -1];
        String ccTabName = classChooserTabPane.getTitleAt(i);
        String ipTabName = null;
        // in a new classChooserPane, a empty string is the first item of its ListPane to make the pane look good
        // but the empty string is not class name, we should filter it out before we make any new paletertab data
        if (newClasses[0].equals(Symbol.intern(""))) {
          for (int j=1; j < newClasses.length; j++)
            filteredNewClasses[j-1] = newClasses[j];
          newClasses = filteredNewClasses;
        }
        int iconSize = ((Integer) iconSizes.elementAt(i)).intValue();
	int buttonStyle = ((Integer) buttonStyles.elementAt(i)).intValue();
        Structure paletteTab = PalettePane.makePaletteTab(currentConnection,
							  ccTabName,
							  newClasses,
							  ItemPaletteDialog.defaultIconWidth,
							  ItemPaletteDialog.defaultIconHeight,
							  iconSize, buttonStyle);
        if (itemPaletteTabPane.getTabCount() < i + 1) {
          dlgPane.makeNewPaletteTabPane (ccTabName, (TwConnection) currentConnection, -1, paletteTab, iconSize, buttonStyle);
	  palettePane.makeNewPaletteTabPane (ccTabName, (TwConnection) currentConnection, -1, paletteTab, ObjectCreator.SMALL_ICON, ICON_ONLY);
        } else {
	  
          ipTabName = itemPaletteTabPane.getTitleAt(i);
          // if there is no such tab in itemPaletteTabPane
          if (!ccTabName.equals(ipTabName)) {
            itemPaletteTabPane.removeTabAt(i);
	    palettePane.getTabbedPane().removeTabAt(i);
            dlgPane.getObjectCreators().remove(i);
	    palettePane.getObjectCreators().remove(i);
            // if the tab is renamed
            if (itemPaletteTabPane.getTabCount() < i + 1) {
              dlgPane.makeNewPaletteTabPane (ccTabName, (TwConnection) currentConnection, -1, paletteTab, iconSize, buttonStyle);
	      palettePane.makeNewPaletteTabPane (ccTabName, (TwConnection) currentConnection, -1, paletteTab, ObjectCreator.SMALL_ICON, ICON_ONLY);
            } else {
              dlgPane.makeNewPaletteTabPane (ccTabName, (TwConnection) currentConnection, i, paletteTab, iconSize, buttonStyle);
	      palettePane.makeNewPaletteTabPane (ccTabName, (TwConnection) currentConnection, i, paletteTab, ObjectCreator.SMALL_ICON, ICON_ONLY);
	      
            }
          } else {
            itemPaletteTabPane.removeTabAt(i);
	    palettePane.getTabbedPane().removeTabAt(i);
	    dlgPane.getObjectCreators().remove(i);
	    palettePane.getObjectCreators().remove(i);
	    dlgPane.makeNewPaletteTabPane (ccTabName, (TwConnection) currentConnection, i, paletteTab, iconSize, buttonStyle);
	    palettePane.makeNewPaletteTabPane (ccTabName, (TwConnection) currentConnection, i, paletteTab, ObjectCreator.SMALL_ICON, ICON_ONLY);
          }
        }
        paletteTabs.addElement(paletteTab);
	
        try {
	  ((G2ObjectCreator) dlgPane.getObjectCreators().elementAt(i)).setStructuredKeys(newClasses);
	  ((G2ObjectCreator) palettePane.getObjectCreators().elementAt(i)).setStructuredKeys(newClasses);
        }
        catch(G2AccessException ex) {
          Trace.exception(ex);
        }
        // get updated itemDlgTab since tab gets changed
        itemPaletteTabPane = dlgPane.getTabbedPane();
      }
      dlgPane.saveCurrentPreferences(paletteTabs);
      itemPaletteTabPane.setSelectedIndex(classChooserTabPane.getSelectedIndex());
      palettePane.getTabbedPane().setSelectedIndex(classChooserTabPane.getSelectedIndex());
      
    }
  }
  
  private static Symbol[] translateStringsToSymbols(String[] keys){
    int len = keys.length;
    Symbol[] classes = new Symbol[len];
    for (int i=0; i<len; i++)
      classes[i] = Symbol.intern(keys[i].toUpperCase());
    return classes;
  }


  class G2CloseAdapter extends G2ConnectionAdapter{
    
    @Override
    public void g2ConnectionClosed(G2ConnectionEvent e){
      
      ItemPaletteDialog dlg;
	  
      TwAccess connection = (TwAccess)e.getSource();
      dlg = (ItemPaletteDialog)itemPalettes.get(connection);
      if (dlg != null) {
	dlg.setVisible (false);
	itemPalettes.remove (connection);
      }
      connection.removeG2ConnectionListener(this);
      
    }
  }    
  
}
