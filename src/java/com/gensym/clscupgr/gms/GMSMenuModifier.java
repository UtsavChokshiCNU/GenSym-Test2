package com.gensym.clscupgr.gms;

import javax.swing.JFrame;
import javax.swing.JMenuBar;
import java.util.Hashtable;

import com.gensym.core.IntHashtable;
import com.gensym.dlg.MessageDialog;
import com.gensym.jgi.G2AccessException;
import com.gensym.mdi.MDIFrame;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.util.Structure;

public class GMSMenuModifier implements MenuNotificationListener {

  private static final Resource i18n = Resource.getBundle("com.gensym.clscupgr.gms.Messages");

  JFrame frame;
  MenuManager menuManager;
  private GMSJMenuBar menuBar = null;

  GMSMenuModifier(JFrame frame, MenuManager menuManager) {
    this.frame = frame;
    this.menuManager = menuManager;
    menuManager.addMenuNotificationListener(this);
  }

  // BEGIN: MenuNotificationListener methods
  @Override
  public void handleShowMenu(MenuNotificationEvent e) throws G2AccessException{
    executeShowMenu(menuManager.getMenuDescription(e.getMenuIndex()));
  }

  @Override
  public void handleHideMenu(MenuNotificationEvent e) {
    executeHideMenu();
  }

  @Override
  public void handleShowSubMenu(MenuNotificationEvent e) throws G2AccessException{
    int index = e.getMenuIndex();
    executeShowSubMenu(index, menuManager.getMenuDescription(index));
  }

  @Override
  public void handleHideSubMenu(MenuNotificationEvent e) {
    //new MessageDialog(frame, "MenuNotificationMessage", true, "handleHideSubMenu "+e.getMenuIndex(), null).setVisible(true);
  }

  @Override
  public void handleMenuRecompiled(MenuNotificationEvent e) {
//     new MessageDialog(frame, "MenuNotificationMessage", false, "handleMenuRecompiled "+e.getMenuIndex(), null).setVisible(true);
    // application should perhaps:
    // 1. hide current menubar
    // 2. get the new menu description
    // 3. create a new JMenuBar
    // 4. call frame.setDefaultMenuBar
  }
  @Override
  public void handleCheckMenuEntry(MenuNotificationEvent e) {
    executeSetSelected(e.getMenuIndex(), true);
  }
  @Override
  public void handleUnCheckMenuEntry(MenuNotificationEvent e) {
    executeSetSelected(e.getMenuIndex(), false);
  }
  // END: MenuNotificationListener methods

  private void executeSetSelected(int menuIndex, boolean state) {
    IntHashtable indexToGMSItemTable = menuManager.getIndexToGMSItemHashtable();
    //fix this: is this an error, or can we silently ignore this?
    if (indexToGMSItemTable == null) return;
    GMSItem gmsItem = (GMSItem)indexToGMSItemTable.get(menuIndex);
    if (gmsItem != null && gmsItem instanceof GMSJCheckBoxMenuItem)
      ((GMSJCheckBoxMenuItem)gmsItem).setSelected(state);
  }

  private void executeShowMenu(Structure menuDescription) throws G2AccessException {
    // menuDescription could be null, or it could also just be empty
    if ((menuDescription !=  null) && (menuDescription.getAttributeCount() != 0)) {
      GMSJMenuBar[] gmsJMenuBars = menuManager.buildJMenuBar(menuDescription);
      if (gmsJMenuBars != null && gmsJMenuBars[0] != null) {
	//System.out.println("number of menus built: "+gmsJMenuBars.length);
	menuBar = gmsJMenuBars[0];
	setMenuBar(menuBar);
      } else {
	// fix this: is throwing this exception the right thing?
	throw new RuntimeException(i18n.getString("failedToGenerateJavaMenus"));
      }
    }
  }

  void setMenuBar(JMenuBar menuBar) {
//     if (frame instanceof MDIFrame)
//       ((MDIFrame)frame).setJMenuBar(menuBar);
//     else
      frame.setJMenuBar(menuBar);
  }

  private void executeHideMenu() {
    setMenuBar(null);
  }

  private void executeShowSubMenu(int index, Structure menuDescription) {
    if ((menuDescription != null) && (menuDescription.getAttributeCount() != 0)) {
      menuManager.showDynamicMenu(index, menuDescription);
    }
  }

}  
