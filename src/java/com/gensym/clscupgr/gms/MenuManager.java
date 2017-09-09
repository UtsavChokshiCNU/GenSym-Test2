 package com.gensym.clscupgr.gms;

import java.awt.Component;
import java.awt.Image;
import java.awt.Menu;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Vector;

import com.gensym.classes.Item;
import com.gensym.classes.UiClientItem;
import com.gensym.core.IntHashtable;
import com.gensym.dlg.ErrorDialog;
import com.gensym.icons.IconDescription;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Gateway;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.util.AlreadyInitializedException;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.DefinitionSymbols;

import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JPopupMenu;
import javax.swing.SwingConstants;

import javax.swing.event.MenuEvent;
import javax.swing.event.MenuListener;

public class MenuManager {

  /**
   * @undocumented
   */
  protected static final Symbol HANDLE_MENU_NOTIFICATION_ = Symbol.intern ("HANDLEMENUNOTIFICATION");


  private static final boolean DONT_CALL_METHOD_IN_NEW_THREAD = false;

  private static final int GMS_ITEM_TABLE_SIZE = 101;

  private Vector menuDescription;
  private MenuActivationAdapter defaultAdapter = new MenuActivationAdapter();
  private DynamicMenuAdapter dynamicMenuAdapter = new DynamicMenuAdapter();
  private TwAccess currentConnection;
  private Vector menuListeners;

  // maps the index value to the AWT/Swing menu component
  private IntHashtable indexToGMSItemTable;

  // RPCs in GMS used in the support of native menus on client
  private static final Symbol GMS_GET_MENU_DESCRIPTION_ = Symbol.intern("GMS-GET-MENU-DESCRIPTION");
  private static final Symbol GMS_EXECUTE_ACTIVATION_CALLBACK_ = Symbol.intern("GMS-EXECUTE-ACTIVATION-CALLBACK");
  private static final Symbol GMS_EXECUTE_DYNAMIC_MENU_GESTURE_ = Symbol.intern("GMS-EXECUTE-DYNAMIC-MENU-GESTURE");
  private static final Symbol GMS_GET_HANDLE_FOR_WINDOW_ = Symbol.intern("GMS-GET-HANDLE-FOR-WINDOW");

  // Fields returned by G2 in the structure for GMS menus 
  private static final Symbol INDEX_            = Symbol.intern("INDEX");
  private static final Symbol TYPE_             = Symbol.intern("TYPE");
  private static final Symbol LABEL_            = Symbol.intern("LABEL");
  private static final Symbol KEY_              = Symbol.intern("KEY");
  private static final Symbol SUBMENU_          = Symbol.intern("SUBMENU");
  private static final Symbol ICONCLASS_        = Symbol.intern("ICONCLASS");
  private static final Symbol INITIALLYCHECKED_ = Symbol.intern("INITIALLYCHECKED");
  private static final Symbol TARGETMODE_       = Symbol.intern("TARGETMODE");

  private static final Symbol NONE_ = Symbol.intern("NONE");

  private static final Point  PIVOT_POINT = new Point(0, 0);

  // Types of GMS items returned by GMS-GET-MENU-DESCRIPTION (GMS API)
  private static final Symbol MENU_BAR_                 = Symbol.intern("MENU-BAR");
  private static final Symbol MENU_                     = Symbol.intern("MENU");
  private static final Symbol DYNAMIC_MENU_             = Symbol.intern("DYNAMIC-MENU");
  private static final Symbol MENU_ENTRY_               = Symbol.intern("MENU-ENTRY");
  private static final Symbol CHECKBOX_MENU_ENTRY_      = Symbol.intern("CHECKBOX-MENU-ENTRY");
  private static final Symbol MODE_CHECKBOX_MENU_ENTRY_ = Symbol.intern("MODE-CHECKBOX-MENU-ENTRY");
  private static final Symbol SEPARATOR_                = Symbol.intern("SEPARATOR");

  private static Resource i18n = Resource.getBundle("com.gensym.clscupgr.gms.Messages");

  // used by Dynamic menus
  private static final Symbol SELECT_   = Symbol.intern("SELECT");
  private static final Symbol DESELECT_ = Symbol.intern("DESELECT");

  private static final boolean debug = false;

  /**
   * The MenuManager is responsible for communicating with the current connection about GMS
   * menus. It retrieves descriptions of GMS menus from G2 and builds a depth-first Vector of 
   * MenuDescription(s) that describe the GMS menu on the client. A default menu adapter
   * handles the callbacks for menu entries, though users can override the default behaviour
   * by passing in a Sequence of menu adapters that correspond to GMS menu items. When/If the 
   * connection for the application changes, the application needs to call setConnection() with 
   * the new connection information.
   * @see #setConnection(TwAccess connection)
   */
  public MenuManager (TwAccess connection) {
    currentConnection = connection;
    menuListeners = new Vector();
  }  
  
  public synchronized void addMenuNotificationListener(MenuNotificationListener l){
    if (!(menuListeners.contains(l)))
      menuListeners.addElement(l);
  }

  public synchronized void removeMenuNotificationListener(MenuNotificationListener l){
    if (menuListeners.contains(l))
      menuListeners.removeElement(l);
  }

  protected void notifyHandleMenuNotification(MenuNotificationEvent e)
  throws G2AccessException{
    //System.out.println("MenuManager.notifyHandleMenuNotification: "+e +"\n");

    if (menuListeners.size() < 1) return;

    Vector l;
    synchronized(this) {l = (Vector)menuListeners.clone();}
    Enumeration ml = l.elements();

//     System.out.println("MenuManager.notifyHandleMenuNotification, there are MenuNotificationListeners");

    switch (e.getID()) {
    case MenuNotificationEvent.SHOW_MENU_ON_CLIENT:
      while (ml.hasMoreElements())
	((MenuNotificationListener)ml.nextElement()).handleShowMenu(e);
      break;
    case MenuNotificationEvent.HIDE_MENU_ON_CLIENT:
      while (ml.hasMoreElements())
	((MenuNotificationListener)ml.nextElement()).handleHideMenu(e);
      break;
    case MenuNotificationEvent.SHOW_SUBMENU_ON_CLIENT:
      while (ml.hasMoreElements())
	((MenuNotificationListener)ml.nextElement()).handleShowSubMenu(e);
      break;
    case MenuNotificationEvent.HIDE_SUBMENU_ON_CLIENT:
      while (ml.hasMoreElements())
	((MenuNotificationListener)ml.nextElement()).handleHideSubMenu(e);
      break;
    case MenuNotificationEvent.MENU_RECOMPILED_ON_SERVER:
      menuDescription = null;
      while (ml.hasMoreElements())
	((MenuNotificationListener)ml.nextElement()).handleMenuRecompiled(e);
      break;
    case MenuNotificationEvent.CHECK_MENU_ENTRY_ON_CLIENT:
      executeVerifyGMSItemIsCheckable(e);
      while (ml.hasMoreElements())
	((MenuNotificationListener)ml.nextElement()).handleCheckMenuEntry(e);
      break;
    case MenuNotificationEvent.UNCHECK_MENU_ENTRY_ON_CLIENT:
      executeVerifyGMSItemIsCheckable(e);
      while (ml.hasMoreElements())
	((MenuNotificationListener)ml.nextElement()).handleUnCheckMenuEntry(e);
    }
  }

  // this method not used by anything now, but it could be useful
  private void executeGetMenuDescriptionsForIndex(Sequence subMenu, int index, Vector matchingDescriptions) {
    if (subMenu == null) return;
    //System.out.println("running executeGetMenuDescriptionsForIndex for: "+index+" subMenu size: "+subMenu.size());
    MenuDescription menuD;
    for (int i=0; i<subMenu.size(); i++) { 
      menuD = (MenuDescription)subMenu.elementAt(i);
      if (menuD.getIndex() == index)
	matchingDescriptions.addElement(menuD);
      if (menuD.getType().equals(MENU_)) {
	executeGetMenuDescriptionsForIndex(menuD.getSubMenu(), index, matchingDescriptions);
      }
    } 
  }

  private synchronized void executeVerifyGMSItemIsCheckable(MenuNotificationEvent e) {
//     System.out.println("MenuManager.executeVerifyGMSItemIsCheckable: "+e.getMenuIndex());

    // the menu might not be built yet, if that's the case, just return
    if (indexToGMSItemTable == null) return;

    String label;
    int index = e.getMenuIndex();
    GMSItem gmsItem = (GMSItem)indexToGMSItemTable.get(index);
    if ((gmsItem != null) && (!(gmsItem instanceof GMSCheckboxMenuItem || gmsItem instanceof GMSJCheckBoxMenuItem))) {
      indexToGMSItemTable.remove(index);
      if (gmsItem instanceof GMSMenuItem) {
	// this awt case never tested
	GMSCheckboxMenuItem newAwtItem;
	GMSMenuItem oldAwtItem = (GMSMenuItem)gmsItem;
	Menu awtMenu = (Menu)oldAwtItem.getParent();
	label = oldAwtItem.getLabel();
	if (label != null)
	  newAwtItem = new GMSCheckboxMenuItem(label, oldAwtItem.getIndex(), oldAwtItem.getKey());
	else
	  newAwtItem = new GMSCheckboxMenuItem(oldAwtItem.getIndex(), oldAwtItem.getKey());
	executeReplaceMenuItem(awtMenu, oldAwtItem, newAwtItem);
	indexToGMSItemTable.put(index, newAwtItem);
      } else {
	GMSJCheckBoxMenuItem newSItem;
	GMSJMenuItem oldSItem = (GMSJMenuItem)gmsItem;
	JPopupMenu swingMenu = (JPopupMenu)oldSItem.getParent();
	label = oldSItem.getText();
	Icon icon = oldSItem.getIcon();
	if (icon == null)
	  newSItem = new GMSJCheckBoxMenuItem(label, oldSItem.getIndex(), oldSItem.getKey());
	else {
	  if (label == null)
	    newSItem = new GMSJCheckBoxMenuItem(icon, oldSItem.getIndex(), oldSItem.getKey());
	  else
	    newSItem = new GMSJCheckBoxMenuItem(label, icon, oldSItem.getIndex(), oldSItem.getKey());
	}
	executeReplaceMenuItem(swingMenu, oldSItem, newSItem);
	indexToGMSItemTable.put(index, newSItem);
      }
    }			      
  }

  private synchronized void executeReplaceMenuItem(JPopupMenu menu, GMSItem oldItem, GMSItem newItem) {
    int oldIndex = menu.getComponentIndex((Component)oldItem);
    menu.remove((Component)oldItem);
    menu.insert((Component)newItem, oldIndex);
  }

  private synchronized void executeReplaceMenuItem(Menu menu, GMSItem oldItem, GMSItem newItem) {
    // this code never tested
    int numItems = menu.getItemCount();
    GMSItem tempItem;
    for (int i=0; i<numItems; i++) {
      if (menu.getItem(i) instanceof GMSItem) {
	tempItem = (GMSItem)menu.getItem(i);
	if (tempItem.equals(oldItem)) {
	  menu.remove((java.awt.MenuComponent)oldItem);
	  menu.insert((java.awt.MenuItem)newItem, i);
	}
      } 
    }
  }

  /*
   * takes the GMS Structure return by G2 and builds a depth first Vector of MenuDescription(s)
   * representing the GMS menu structure
   */
  private void buildMenuDescription(Structure menuStruct) {
    menuDescription = new Vector();

    MenuDescription menuDesc = buildMenuDescriptionFromStructure(menuStruct);
    menuDescription.addElement(menuDesc);
    buildMenuDefinition(menuDesc, menuDescription);

    if (debug) 
      debugMenuDefinition(menuDescription);
  }

  /*
   * dumps the contents of the Vector of MenuDescription(s)
   */
  private void debugMenuDefinition(Vector menuDescription) {
    System.out.println("Dumping "+menuDescription.size()+" MenuDescription(s)\n\n");
    MenuDescription menuD;
    for (int i=0; i<menuDescription.size(); i++) {
      menuD = (MenuDescription)menuDescription.elementAt(i);
      System.out.println("["+i+"]: index=> "+menuD.getIndex()+"  type=> "+menuD.getType()+"  label=> "+menuD.getLabel());
      if (menuD.getSubMenu() != null) {
	Structure menuStruct;
	Sequence subMenu = menuD.getSubMenu();
	System.out.println("\n--------\n");
	for (int j=0; j<subMenu.size(); j++) {
	  menuD = (MenuDescription)subMenu.elementAt(j);
	  System.out.println("        type=> "+menuD.getType()+"  label=> "+menuD.getLabel()+"  parentType: "+menuD.getParentType());
	}
	System.out.println("\n--------\n");
      }
    }
  }

  /*
   * returns a MenuDescription for the G2 GMS menu Structure
   */
  private MenuDescription buildMenuDescriptionFromStructure(Structure menuStruct) {
    //System.out.println("MenuManager.buildMenuDescriptionFromStructure");
    MenuDescription menuDesc = new MenuDescription();

    Enumeration attributeNames;
    Enumeration attributeValues;
    Symbol attrName;
    Object attrValue;

    attributeNames = menuStruct.getAttributeNames();
    attributeValues = menuStruct.getAttributeValues();

    //System.out.println("attributeNames: "+attributeNames+"  attributeValues: "+attributeValues);

    for (Enumeration e = attributeNames; attributeNames.hasMoreElements();) {
      attrName = (Symbol)attributeNames.nextElement();
      attrValue = attributeValues.nextElement();

      if (attrName.equals(INDEX_)) {
	menuDesc.setIndex(new Integer(attrValue.toString()).intValue());
      } else if (attrName.equals(TYPE_)) {
	menuDesc.setType((Symbol)attrValue);
      } else if (attrName.equals(LABEL_)) {
	menuDesc.setLabel((String)attrValue);
      } else if (attrName.equals(KEY_)) {
	menuDesc.setKey((Object)attrValue);
      } else if (attrName.equals(SUBMENU_)) {
	menuDesc.setSubMenu((Sequence)getSubMenus((Sequence)attrValue));
      } else if (attrName.equals(ICONCLASS_)) {
	menuDesc.setIconClass((Symbol)attrValue);
      } else if (attrName.equals(INITIALLYCHECKED_)) {
	menuDesc.setIsChecked(new Boolean(attrValue.toString()).booleanValue());
      } else if (attrName.equals(TARGETMODE_)) {
	menuDesc.setTargetMode((Symbol)attrValue);
      }
    }

    return menuDesc;
  }

  /*
   * returns a Sequence of MenuDescription(s) for the G2 GMS Sequence of Structures
   */
  private Sequence getSubMenus(Sequence subMenu) {
    Sequence menuEntries = new Sequence();

    MenuDescription menuDesc;
    Structure menuStruct;
    for (int i=0; i<subMenu.size(); i++) {
      menuStruct = (Structure)subMenu.elementAt(i);
      menuDesc = buildMenuDescriptionFromStructure(menuStruct);
      menuEntries.addElement(menuDesc);
    } 

    return menuEntries;
  }

  /*
   * Traverses the "tree" in depth first order, adding MenuDescription(s) to menuDescription
   */
  private void buildMenuDefinition(MenuDescription menuDesc, Vector menuDescriptions) {
    //System.out.println("running buildMenuDefinition for type: "+menuDesc.getType()+"  label: "+menuDesc.getLabel());

    // now add MenuDescription(s) for subMenu
    Sequence subMenus = menuDesc.getSubMenu();
    if (subMenus != null) {
      MenuDescription menuD;
      for (int i=0; i<subMenus.size(); i++) {
	menuD = (MenuDescription)subMenus.elementAt(i);
	menuD.setParentType(menuDesc.getType());
	menuDescriptions.addElement((MenuDescription)subMenus.elementAt(i));
      }

      for (int j=0; j<subMenus.size(); j++) {
	buildMenuDefinition((MenuDescription)subMenus.elementAt(j), menuDescriptions);
      }
    }
  }

  /*
   * add the subMenu described by menuDesc to the GMSMenu. If menuAdapters is null, then use the
   * default menu adapter (defaultAdapter).
   */
  private void addSubMenuToMenu(GMSMenu menu, MenuDescription menuDesc, Sequence menuAdapters) {
    Sequence subMenu = menuDesc.getSubMenu();
    MenuDescription menuD;
    Symbol type;
    int index;
    GMSMenuItem menuItem;
    GMSCheckboxMenuItem checkboxMenuItem;
    GMSMenu newMenu;
    for (int i=0; i<subMenu.size(); i++) {
      menuD = (MenuDescription)subMenu.elementAt(i);
      type = menuD.getType();
      index = menuD.getIndex();
      if (type.equals(SEPARATOR_)) {
	menu.addSeparator();
      } else if (type.equals(MENU_ENTRY_)) {
	menuItem = new GMSMenuItem(menuD.getLabel(), index, menuD.getKey());
	menu.add(menuItem);
	indexToGMSItemTable.put(index, menuItem);
	if (menuAdapters == null) {
	  menuItem.addActionListener(defaultAdapter);
	}
      } else if (type.equals(CHECKBOX_MENU_ENTRY_)) {
	checkboxMenuItem = new GMSCheckboxMenuItem(menuD.getLabel(), menuD.getIsChecked(), index, menuD.getKey());
	menu.add(checkboxMenuItem);
	indexToGMSItemTable.put(index, checkboxMenuItem);
	if (menuAdapters == null) {
	  checkboxMenuItem.addActionListener(defaultAdapter);
	} 
      } else if (type.equals(MODE_CHECKBOX_MENU_ENTRY_)) {
	try {
	  boolean isChecked = false;
	  if (currentConnection.getUserMode().equals(menuD.getTargetMode()))
	    isChecked = true;
	  checkboxMenuItem = new GMSCheckboxMenuItem(menuD.getLabel(), isChecked, index, menuD.getKey());
	  menu.add(checkboxMenuItem);
	  indexToGMSItemTable.put(index, checkboxMenuItem);
	  if (menuAdapters == null) {
	    checkboxMenuItem.addActionListener(defaultAdapter);
	  }
	} catch (G2AccessException gae) {
	  Trace.exception(gae);
	  new ErrorDialog(null, i18n.getString("MenuManagerError"), true, gae.getMessage(), null).setVisible(true);
	}
      } else if (type.equals(MENU_)) {
	newMenu = new GMSMenu(menuD.getLabel(), index, menuD.getKey());
	menu.add(newMenu);
	indexToGMSItemTable.put(index, newMenu);
	addSubMenuToMenu(newMenu, menuD, menuAdapters);
      } else if (type.equals(DYNAMIC_MENU_)) {
	newMenu = new GMSMenu(menuD.getLabel(), index, menuD.getKey());
	menu.add(newMenu);
	indexToGMSItemTable.put(index, newMenu);
	addSubMenuToMenu(newMenu, menuD, menuAdapters);
      }
    }
  }

  private ImageIcon getImageIconForClass(Symbol className) throws G2AccessException {
    ImageIcon imageIcon = null;

    Structure iconDescStruct = (Structure)currentConnection.getClassManager().getClassAttributeValue(className, DefinitionSymbols.ICON_DESCRIPTION_);
    //System.out.println("iconDescStruct: "+iconDescStruct);

    if (iconDescStruct != null) {
      IconDescription iconDesc = new IconDescription(iconDescStruct);
      Image iconImage = iconDesc.createImage(iconDesc.getWidth(), iconDesc.getHeight(),
					     0, PIVOT_POINT, false, null, null);
      //System.out.println("iconImage: "+iconImage);
      imageIcon = new ImageIcon(iconImage);
    }

    return imageIcon;
  }

  /*
   * add the subMenu described by menuDesc to the GMSJMenu. If menuAdapters is null, then use the
   * default menu adapter (defaultAdapter).
   */
  private void addSubMenuToJMenu(GMSJMenu menu, MenuDescription menuDesc, Sequence menuAdapters) {
    //System.out.println("MenuManager.addSubMenuToJMenu");
    Sequence subMenu = menuDesc.getSubMenu();
    MenuDescription menuD;
    Symbol type;
    int index;
    GMSJMenuItem menuItem;
    GMSJCheckBoxMenuItem checkBoxMenuItem;
    GMSJMenu newMenu;
    for (int i=0; i<subMenu.size(); i++) {
      menuD = (MenuDescription)subMenu.elementAt(i);
      type = menuD.getType();
      index = menuD.getIndex();
      if (type.equals(SEPARATOR_)) {
	menu.addSeparator();
      } else if (type.equals(MENU_ENTRY_)) {
	if (!(menuD.getIconClass().equals(NONE_))) {
	  try {
	    menuItem = new GMSJMenuItem(menuD.getLabel(), getImageIconForClass(menuD.getIconClass()), index, menuD.getKey());
	    menuItem.setHorizontalTextPosition(SwingConstants.RIGHT);
	    menu.add(menuItem);
	    indexToGMSItemTable.put(index, menuItem);
	    if (menuAdapters == null) {
	      menuItem.addActionListener(defaultAdapter);
	    }
	  } catch (G2AccessException gae) {
	    Trace.exception(gae);
	    new ErrorDialog(null, i18n.getString("MenuManagerError"), true, gae.getMessage(), null).setVisible(true);
	  }
	} else {
	  //System.out.println("no iconClass");
	  menuItem = new GMSJMenuItem(menuD.getLabel(), index, menuD.getKey());
	  menu.add(menuItem);
	  indexToGMSItemTable.put(index, menuItem);
	  if (menuAdapters == null) {
	    menuItem.addActionListener(defaultAdapter);
	  }
	}
      } else if ((type.equals(CHECKBOX_MENU_ENTRY_)) || (type.equals(MODE_CHECKBOX_MENU_ENTRY_))) {
	try {
	  boolean isChecked = false;
	  if (type.equals(CHECKBOX_MENU_ENTRY_))
	    isChecked = menuD.getIsChecked();
	  else {
	    if (currentConnection.getUserMode().equals(menuD.getTargetMode()))
	      isChecked = true;
	  }
	  if (!(menuD.getIconClass().equals(NONE_))) {
	    checkBoxMenuItem = new GMSJCheckBoxMenuItem(menuD.getLabel(), getImageIconForClass(menuD.getIconClass()), isChecked, index, menuD.getKey());
	    checkBoxMenuItem.setHorizontalTextPosition(SwingConstants.RIGHT);
	    menu.add(checkBoxMenuItem);
	    indexToGMSItemTable.put(index, checkBoxMenuItem);
	    if (menuAdapters == null) {
	      checkBoxMenuItem.addActionListener(defaultAdapter);
	    }
	  } else {
	    checkBoxMenuItem = new GMSJCheckBoxMenuItem(menuD.getLabel(), isChecked, index, menuD.getKey());
	    menu.add(checkBoxMenuItem);
	    indexToGMSItemTable.put(index, checkBoxMenuItem);
	    if (menuAdapters == null) {
	      checkBoxMenuItem.addActionListener(defaultAdapter);
	    }
	  }
	} catch (G2AccessException gae) {
	  Trace.exception(gae);
	  new ErrorDialog(null, i18n.getString("MenuManagerError"), true, gae.getMessage(), null).setVisible(true);
	}
      } else if (type.equals(MENU_)) {
	//System.out.println("type is MENU_");
	newMenu = new GMSJMenu(menuD.getLabel(), index, menuD.getKey());
	menu.add(newMenu);
	indexToGMSItemTable.put(index, newMenu);
	addSubMenuToJMenu(newMenu, menuD, menuAdapters);
      } else if (type.equals(DYNAMIC_MENU_)) {
	index = menuD.getIndex();
	newMenu = new GMSJMenu(menuD.getLabel(), index, menuD.getKey());

	// add listener for when user is selecting/deselecting this menu
	newMenu.addMenuListener(dynamicMenuAdapter);

	menu.add(newMenu);
	indexToGMSItemTable.put(index, newMenu);
	addSubMenuToJMenu(newMenu, menuD, menuAdapters);
      }
    }
  }

  /*
   * add the menu described by menuDesc to the GMSMenuBar. menuAdapters may be null, if so the default
   * menu adapter is use (defaultAdapter)
   */
  private void addMenuToMenuBar(GMSMenuBar menuBar, MenuDescription menuDesc, Sequence menuAdapters) {
    // add Menu & subMenu
    int index = menuDesc.getIndex();
    GMSMenu menu = new GMSMenu(menuDesc.getLabel(), index, menuDesc.getKey());
    menuBar.add(menu);
    indexToGMSItemTable.put(index, menu);
    addSubMenuToMenu(menu, menuDesc, menuAdapters);
  }

  /*
   * add the menu described by menuDesc to the GMSJMenuBar. menuAdapters may be null, if so the default
   * menu adapter is use (defaultAdapter)
   */
  private void addJMenuToJMenuBar(GMSJMenuBar menuBar, MenuDescription menuDesc, Sequence menuAdapters) {
    // add JMenu & subMenu
    int index = menuDesc.getIndex();
    GMSJMenu menu = new GMSJMenu(menuDesc.getLabel(), index, menuDesc.getKey());
    menuBar.add(menu);
    indexToGMSItemTable.put(index, menu);
    addSubMenuToJMenu(menu, menuDesc, menuAdapters);
  }

  /**
   * returns an Array of GMSMenuBar(s) with default callbacks
   */
  public GMSMenuBar[] buildMenuBar(Structure menuSpecs) {
    // this code untested since major changes
    //System.out.println("MenuManager.buildMenuBar: "+menuSpecs.toString()+"\n\n");
    GMSMenuBar[] menuBars = null;
    indexToGMSItemTable = new IntHashtable(GMS_ITEM_TABLE_SIZE);
    Vector menus = new Vector();
    GMSMenuBar menuBar = null;

    if (menuSpecs.getAttributeCount() == 0) {
      new ErrorDialog(null, i18n.getString("MenuManagerError"), true,
		      i18n.getString("MenuStructIsEmpty"), null).setVisible(true);
      return menuBars; // should throw some exception
    }

    // generate MenuDescription(s) for each item in the GMS menu
    Structure kbMenuStruct = (Structure)menuSpecs.clone();
    buildMenuDescription(kbMenuStruct);    

    // build menu by walking through menuSpecs. Add defaultAdapter as an ActionListener
    // to each menuItem created
    MenuDescription menuD;
    Symbol type;
    int index;
    if (menuDescription != null) {
      for (int i=0; i<menuDescription.size(); i++) {
	menuD = (MenuDescription)menuDescription.elementAt(i);
	type = menuD.getType();
	index = menuD.getIndex();
	if (type.equals(MENU_BAR_)) {
	  menuBar = new GMSMenuBar(index, menuD.getKey());
	  menus.addElement(menuBar);
	  indexToGMSItemTable.put(index, menuBar);
	} else if ((type.equals(MENU_)) || (type.equals(DYNAMIC_MENU_))) {
	  if (menuBar != null && (menuD.getParentType().equals(MENU_BAR_))) {
	    addMenuToMenuBar(menuBar, menuD, null);
	  }
	} 
      } 
    }

    if (menus.size() > 0) {
      menuBars = new GMSMenuBar[menus.size()];
      for (int j=0; j<menus.size(); j++) {
	menuBars[j] = (GMSMenuBar)menus.elementAt(j);
	if (debug) {
	  System.out.println("\n["+j+"]: "+menus.elementAt(j)+"\n\n");
	}
      }
    }

    return menuBars;
  }

 
  /**
   * returns an Array of GMSMenuBar(s) where the callbacks are not the default
   */
  public GMSMenuBar[] buildMenuBar(Sequence menuSpecs, Sequence menuAdapters) {
    // this code is NYI
    GMSMenuBar[] menuBars = null;
    indexToGMSItemTable = new IntHashtable(GMS_ITEM_TABLE_SIZE);

    // generate MenuDescription(s) for each item in the GMS menu
    Structure kbMenuStruct = (Structure)menuSpecs.clone();
    buildMenuDescription(kbMenuStruct); 

    // build menu by walking through menuSpecs. Add corresponding menuAdapter as an
    // ActionListener to each menuItem created

    return menuBars;
  }

  /**
   * returns an Array of GMSJMenuBar(s) with default callbacks
   */
  public GMSJMenuBar[] buildJMenuBar(Structure menuSpecs) {
//     System.out.println("JBUILD: MenuManager.buildJMenuBar:");
    indexToGMSItemTable = new IntHashtable(GMS_ITEM_TABLE_SIZE);
    GMSJMenuBar[] menuBars = null;
    Vector menus = new Vector();
    GMSJMenuBar menuBar = null;

    if (menuSpecs.getAttributeCount() == 0) {
      new ErrorDialog(null, i18n.getString("MenuManagerError"), true,
		      i18n.getString("MenuStructIsEmpty"), null).setVisible(true);
      return menuBars; // should throw some exception
    }

    // generate MenuDescription(s) for each item in the GMS menu
    Structure kbMenuStruct = (Structure)menuSpecs.clone();
    buildMenuDescription(kbMenuStruct);

    // build menu by walking through menuSpecs. Add defaultAdapter as an ActionListener
    // to each menuItem created
    MenuDescription menuD;
    Symbol type;
    int index;
    if (menuDescription != null) {
      for (int i=0; i<menuDescription.size(); i++) {
	menuD = (MenuDescription)menuDescription.elementAt(i);
	type = menuD.getType();
	//System.out.println("type: "+type);
	if (type.equals(MENU_BAR_)) {
	  index = menuD.getIndex();
	  menuBar = new GMSJMenuBar(index, menuD.getKey());
	  menus.addElement(menuBar);
	  indexToGMSItemTable.put(index, menuBar);
	} else if ((type.equals(MENU_)) || (type.equals(DYNAMIC_MENU_))) {
	  if (menuBar != null && (menuD.getParentType().equals(MENU_BAR_))) {
	    addJMenuToJMenuBar(menuBar, menuD, null);
	  }
	} 
      } 
    }

    //System.out.println("\nmenus.size() "+menus.size()+"\n");

    if (menus.size() > 0) {
      menuBars = new GMSJMenuBar[menus.size()];
      for (int j=0; j<menus.size(); j++) {
	menuBars[j] = (GMSJMenuBar)menus.elementAt(j);
	if (debug) {
	  System.out.println("\n["+j+"]: "+menus.elementAt(j)+"\n\n");
	}
      }
    }

    return menuBars;
  }

  /**
   * returns an Array of GMSJMenuBar(s) where the callbacks are not the default
   */
  public GMSJMenuBar[] buildJMenuBar(Sequence menuSpecs, Sequence menuAdapters) {
    // This code is NYI
    //System.out.println("MenuManager.buildJMenuBar");
    GMSJMenuBar[] menuBars = null;
    indexToGMSItemTable = new IntHashtable(GMS_ITEM_TABLE_SIZE);

    // generate MenuDescription(s) for each item in the GMS menu
    Structure kbMenuStruct = (Structure)menuSpecs.clone();
    buildMenuDescription(kbMenuStruct);  

    // build menu by walking through menuSpecs. Add corresponding menuAdapter as an
    // ActionListener to each menuItem created

    return menuBars;
  }

  /**
   * Returns a Hashtable matching gms-index values to AWT or Swing MenuComponents
   */
  public IntHashtable getIndexToGMSItemHashtable() {
    return indexToGMSItemTable;
  }

  /**
   * returns the G2 GMS Structure for the gms-menu-bar-template whose gms-index = menuIndex
   */
  public Structure getMenuDescription(int menuIndex) throws G2AccessException {
    //System.out.println("GET DESC: MenuManager.getMenuDescription");
    UiClientItem uiClientItem = currentConnection.retrieveSession();
//     System.out.println("GET DESC: uiClientItem: "+uiClientItem);
    Object[] args = {uiClientItem, new Integer(menuIndex)};
    return (Structure)currentConnection.callRPC(GMS_GET_MENU_DESCRIPTION_, args);
  }

  /**
   * returns the default adapter for a menu-entry
   */
  public MenuActivationAdapter getDefaultAdapter() {
    return defaultAdapter;
  }

  // defer for now: public void emitJMenuBar()  and emitMenuBar()

  class MenuActivationAdapter implements ActionListener {
    @Override
    public void actionPerformed(ActionEvent event) {
//       System.out.println("MenuActivationAdapter.actionPerformed: "+event);
      MenuActivationCallbackExecutor cbe = new MenuActivationCallbackExecutor((((GMSItem)event.getSource()).getIndex()), GMS_EXECUTE_ACTIVATION_CALLBACK_, null);
      cbe.start();
    }
  }

  class MenuActivationCallbackExecutor extends Thread {
    // used by all menus
    int menuIndex;
    Symbol gmsCallback;
    // only used by DynamicMenus
    Symbol gestureType;

    MenuActivationCallbackExecutor (int index, Symbol callback, Symbol type) {
      menuIndex = index;
      gmsCallback = callback;
      gestureType = type;
    }
    @Override
    public void run () {
//       System.out.println("MenuActivationCallbackExecutor.run for index: "+menuIndex);
      try {
	UiClientItem uiClientItem = currentConnection.retrieveSession();
	Integer gmsHandle = (Integer)currentConnection.callRPC(GMS_GET_HANDLE_FOR_WINDOW_, new Object[] {uiClientItem});
	Integer index = new Integer(menuIndex);
	Object[] args;
	if (gmsCallback.equals(GMS_EXECUTE_ACTIVATION_CALLBACK_)) {
	  args = new Object[] {gmsHandle, index};
	  currentConnection.callRPC(gmsCallback, args);
	} else if (gmsCallback.equals(GMS_EXECUTE_DYNAMIC_MENU_GESTURE_)) {
	  args = new Object[] {gmsHandle, index, gestureType};
	  currentConnection.callRPC(gmsCallback, args);
	}
      } catch (G2AccessException gae) {
	Trace.exception(gae);
// 	System.out.println("MenuActivationCallbackExecutor.run: "+gae);
      }
    }
  }

  private GMSJMenu buildJMenu(Structure menuStruct, Sequence menuAdapters) {
    GMSJMenu menu = null;
    return menu;
  }

  private GMSJMenu buildJMenu(Structure menuStruct) {
    GMSJMenu menu = null;

    if (menuStruct.getAttributeCount() == 0) {
      new ErrorDialog(null, i18n.getString("MenuManagerError"), true,
		      i18n.getString("MenuStructIsEmpty"), null).setVisible(true);
      return menu; // should throw some exception
    }

    Structure kbMenuStruct = (Structure)menuStruct.clone();
    buildMenuDescription(kbMenuStruct);
    
    if (menuDescription != null) {
       MenuDescription menuD;
       Symbol type;
       int index;
       for (int i=0; i<menuDescription.size(); i++) {
	 menuD = (MenuDescription)menuDescription.elementAt(i);
	 type = menuD.getType();
	 index = menuD.getIndex();
	 //System.out.println("["+i+"]: "+type);
	 if (type.equals(MENU_BAR_)) {
	   // error, we should only be getting menus and menu-items
	   System.out.println("ERROR:MM::buildJMenu, case of MENU_BAR_");
	 } else if ((type.equals(MENU_)) || (type.equals(DYNAMIC_MENU_))) {
	   menu = new GMSJMenu(menuD.getLabel(), index, menuD.getKey());
	   addSubMenuToJMenu(menu, menuD, null);
	 }
       }
    }
    return menu;
  }
  
  private GMSMenu buildMenu(Structure menuStruct, Sequence menuAdapters) {
    GMSMenu menu = null;
    return menu;
  }

  private GMSMenu buildMenu(Structure menuStruct) {
    GMSMenu menu = null;
    return menu;
  }

  private void executeSwitchSubMenu(GMSJMenu dynamicMenu, GMSJMenu subMenu) {
//     System.out.println("MM.executeSwitchSubMenu: "+subMenu);
    GMSItem gmsItem;

    // first check to see if there is already a submenu, if so remove it
    int numItems = dynamicMenu.getItemCount();
    if (numItems > 0) {
      Vector menuItems = new Vector();
      for (int i=0; i<numItems; i++)
	indexToGMSItemTable.remove(((GMSItem)dynamicMenu.getItem(i)).getIndex());

      dynamicMenu.removeAll();
    }

    // iterate over each entry in subMenu and add it to dynamicMenu
    Component[] menuItems = subMenu.getMenuComponents();
    for (int k=0; k<menuItems.length; k++) {
      gmsItem = (GMSItem)menuItems[k];
      indexToGMSItemTable.put(gmsItem.getIndex(), gmsItem);
      dynamicMenu.add((Component)gmsItem);
    }
  }

  private void executeSwitchSubMenu(GMSMenu dynamicMenu, GMSMenu subMenu) {
  }

  public void showDynamicMenu(int index, Structure menuStruct) {
    if (indexToGMSItemTable == null) return;
    GMSItem gmsItem = (GMSItem)indexToGMSItemTable.get(index);
    if (gmsItem != null) {
      if (gmsItem instanceof GMSJMenu) {
	GMSJMenu swingMenu = buildJMenu(menuStruct);
	executeSwitchSubMenu((GMSJMenu)gmsItem, swingMenu);
      } else if (gmsItem instanceof GMSMenu) {
	GMSMenu awtMenu = buildMenu(menuStruct);
	executeSwitchSubMenu((GMSMenu)gmsItem, awtMenu);
      } else {
	new ErrorDialog(null, i18n.getString("MenuManagerError"), true, "The GMSItem returned to showDynamicMenu is not a GMSMenu or GMSJMenu component; unable to display sub-menu", null).setVisible(true);
      }
    }
  }

  class DynamicMenuAdapter implements MenuListener {
    @Override
    public void menuCanceled(MenuEvent event) {}
    @Override
    public void menuDeselected(MenuEvent event) {
      //System.out.println("menu deselected");
      MenuActivationCallbackExecutor cbe = new MenuActivationCallbackExecutor((((GMSItem)event.getSource()).getIndex()), GMS_EXECUTE_DYNAMIC_MENU_GESTURE_, DESELECT_);
      cbe.start();
    }
    @Override
    public void menuSelected(MenuEvent event) {
      //System.out.println("menu selected: "+((GMSItem)event.getSource()).getIndex());
      MenuActivationCallbackExecutor cbe = new MenuActivationCallbackExecutor((((GMSItem)event.getSource()).getIndex()), GMS_EXECUTE_DYNAMIC_MENU_GESTURE_, SELECT_);
      cbe.start();
    }
  }
}
