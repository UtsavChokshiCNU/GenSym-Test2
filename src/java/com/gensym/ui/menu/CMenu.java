/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CMenu.java
 *
 */

package com.gensym.ui.menu;

import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.KeyStroke;
import javax.swing.ImageIcon;
import java.awt.Toolkit;
import java.util.Hashtable;
import java.util.Vector;
import java.util.Enumeration;
import com.gensym.ui.Command;
import com.gensym.ui.KeyableCommand;
import com.gensym.ui.KeyInformation;
import com.gensym.ui.SubCommand;
import com.gensym.ui.StructuredCommand;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.ui.CommandUtilities;
import com.gensym.message.Resource;
import com.gensym.ui.LookAndFeel;
import java.awt.event.MouseEvent;
import javax.swing.border.AbstractBorder;
import javax.swing.border.BevelBorder;
import com.gensym.uitools.utils.VariableWidthBevelBorder;
import java.awt.AWTEvent;

/**
 * CMenu is a "command-aware" menu container. It provides API for adding Commands.
 *<p>
 * In general, when a Command is added to a CMenu, the CMenu:
 *  <LI> Creates and adds a menu item for each command key.  A command with state
 * generates a checkbox menu item.
 *  <LI> Applies the default or specified RepresentationConstraints
 *  <LI> Ensures that the initial availability and state of the menu item is in sync
 * with the current availability and state of the command.
 *  <LI> Registers the Command as an ActionListener with each menu item and
 *  registers a CommandListener with the Command to respond appropriately to changes
 *  in the Command.
 *</p><p>
 * The actionCommand of the ActionEvent dispatched from the generated menu items
 * is the command key.
 *</p>
 * @see com.gensym.ui.Command
 * @see com.gensym.ui.StructuredCommand
 * @see com.gensym.ui.RepresentationConstraints
 */

public class CMenu extends JMenu{
  private static final RepresentationConstraints defaultConstraints =
    new RepresentationConstraints(RepresentationConstraints.LEFT,
				  RepresentationConstraints.CENTER,
				  RepresentationConstraints.RIGHT,
				  RepresentationConstraints.CENTER);
  private static Resource i18n = Resource.getBundle("com.gensym.ui.menu.Errors");
  private static final Class thisClass = com.gensym.ui.menu.CMenu.class;
  static final ImageIcon defaultIcon = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("empty.gif")));

  static final String NULL_MARKER = "null";

  private String key;
  private CMenuCommandAdapter cmdAdapter;
  private Hashtable commandToAdapterTable;

  /**
   * Creates a CMenu with the specified label.
   */
  public CMenu (String label){
    super(label);
    init();
  }

  private boolean over = false;
  @Override
  protected void processMouseEvent(MouseEvent e) {
    if (LookAndFeel.getUseSnappyLookAndFeel()) {
      if (e.getID() == MouseEvent.MOUSE_ENTERED)
	over = true;
      else if (e.getID()== MouseEvent.MOUSE_EXITED)
	over = false;
      repaint();
    }
    super.processMouseEvent(e);
  }
  private static final AbstractBorder raisedBorder =
  new VariableWidthBevelBorder(BevelBorder.RAISED);

  @Override
  protected void paintBorder(java.awt.Graphics g) {
    if (!LookAndFeel.getUseSnappyLookAndFeel() || over)
      super.paintBorder(g);
  }

  private void init() {
    if (LookAndFeel.getUseSnappyLookAndFeel()) {
      setBorder(raisedBorder);
      enableEvents(AWTEvent.MOUSE_EVENT_MASK);
      setBorderPainted(true);
      setRolloverEnabled(true);
      setFont(com.gensym.uitools.utils.FontUtil.sanserifPlain11);
    }
  }

  /*
   * Creates a CMenu whose label is the short description of command.
   * The CMenu is disabled if command is unavailable.  cmdAdapter is
   * a CommandListener of command.
   */
  protected CMenu(Command command, String cmdKey, CMenuCommandAdapter cmdAdapter,
	RepresentationConstraints constraints, Character mnemonic){
    super(command.getDescription(cmdKey, Command.SHORT_DESCRIPTION));

    setHorizontalAlignment(constraints.getHorizontalAlignment());
    setVerticalAlignment(constraints.getVerticalAlignment());
    setHorizontalTextPosition(constraints.getHorizontalTextPosition());
    setVerticalTextPosition(constraints.getVerticalTextPosition());

    key = cmdKey;
    this.cmdAdapter = cmdAdapter;
    cmdAdapter.add(this);
    if (!command.isAvailable(cmdKey)){
    	setEnabled(false);
    }
   if (mnemonic != null){
      if (getText().indexOf(mnemonic.charValue()) == -1)
	setText(getText()+" ("+mnemonic+")");
      setMnemonic(mnemonic.charValue());
    }
  }

  /**
   * Adds menu items for each command key in cmd. The short description of the
   * command is used as the label for the menu item.  If the command is a
   * StructuredCommand, then the hierachical structure of the command is represented
   * via submenus and groupings are separated by separators.  Commands with state
   * are represented by checkbox menu items.
   *
   * @see com.gensym.ui.Command#getDescription
   */
  public final void add(Command cmd){
    add(cmd, defaultConstraints);
  }

  /**
   * Adds the command and applies the specified constraints to each generated menu
   * item. If specified in the constraints, the short description of the Command
   * is used for the menu item's label and the small icon of the Command is used
   * for the menu item's icon.
   *
   * @see com.gensym.ui.Command#getDescription
   * @see com.gensym.ui.Command#getIcon
   */
  public final void add(Command cmd, RepresentationConstraints constraints){
    if (cmd == null)
      throw new IllegalArgumentException(i18n.getString("CommandCanNotBeNull"));
    CMenuCommandAdapter menuCmdAdapter = new CMenuCommandAdapter(cmd, constraints, null, this, true);
    updateTable(cmd, menuCmdAdapter);
    add(cmd, menuCmdAdapter, constraints, null);
  }

  void add(Command cmd, CMenuCommandAdapter cmdAdapter,
	   RepresentationConstraints constraints, KeyInformation[] mnemonicAndShortcutOverrides){
    KeyMap mnemonicMap = new KeyMap(NULL_MARKER);
    KeyMap shortcutMap = new KeyMap(NULL_MARKER);
    fillKeyMaps(mnemonicMap, shortcutMap, mnemonicAndShortcutOverrides);
    if (cmd instanceof StructuredCommand){
      synchronized(cmdAdapter){
	Vector structuredKeys = ((StructuredCommand)cmd).getStructuredKeys();
	createMenu(this, structuredKeys, cmd, cmdAdapter, false, constraints, mnemonicMap, shortcutMap);
      }
    }
    else{
      String[] keys = cmd.getKeys();
      if (!(keys == null))
	for (int i=0; i<keys.length; i++)
	  add(cmd, keys[i], cmdAdapter, constraints, mnemonicMap, shortcutMap);
    }
  }

  static void fillKeyMaps(KeyMap mnemonicMap, KeyMap shortcutMap,
				  KeyInformation[] mnemonicAndShortcutOverrides){
    if (mnemonicAndShortcutOverrides != null){
      for (int i=0; i<mnemonicAndShortcutOverrides.length; i++){
	KeyInformation keyInfo = mnemonicAndShortcutOverrides[i];
	if (!keyInfo.getUseDefaultMnemonic())
	  mnemonicMap.put(keyInfo.getCommandKey(), keyInfo.getMnemonic());
	if (!keyInfo.getUseDefaultShortcut())
	  shortcutMap.put(keyInfo.getCommandKey(), keyInfo.getShortcut());
      }
    }
  }

  /**
   * Adds a menu item for a single action of the command, or, in the case of a
   * StructuredCommand, it may add a single sub-menu.  The short description of the
   * command is used for the label of the menu item or menu. If the command has state,
   * then a checkbox menu item is generated. Single actions of StructuredCommands
   * will ignore to STRUCTURE_CHANGED CommandEvents.
   *
   * @see com.gensym.ui.Command#getDescription
   * @see com.gensym.ui.StructuredCommand
   */
  public final void add(Command cmd, String cmdKey){
    add(cmd, cmdKey, defaultConstraints);
  }

  /**
   * Adds a menu item for a single action of the command, or, in the case of a
   * StructuredCommand, it may add a single sub-menu.
   * If specified in the constraints, the short description of the
   * Command is used for the menu item's label and the small icon of the Command is
   * used for the menu item's icon.  Single actions of StructuredCommands
   * will ignore to STRUCTURE_CHANGED CommandEvents.
   *
   * @see com.gensym.ui.Command#getDescription
   * @see com.gensym.ui.Command#getIcon
   * @see com.gensym.ui.StructuredCommand
   */
  public final void add(Command cmd, String cmdKey,
			RepresentationConstraints constraints){
    add(cmd, cmdKey, constraints, null);
  }

  public final void add(Command cmd, String cmdKey, RepresentationConstraints constraints,
			KeyInformation[] mnemonicAndShortcutOverrides){
    if (cmd == null)
      throw new IllegalArgumentException(i18n.getString("CommandCanNotBeNull"));
    CMenuCommandAdapter menuCmdAdapter = new CMenuCommandAdapter(cmd, constraints, mnemonicAndShortcutOverrides,
							     this, false);
    updateTable(cmd, menuCmdAdapter);
    if (cmdKey == null)
      add(cmd, menuCmdAdapter, constraints, mnemonicAndShortcutOverrides);
    else{
      KeyMap mnemonicMap = new KeyMap(NULL_MARKER);
      KeyMap shortcutMap = new KeyMap(NULL_MARKER);
      fillKeyMaps(mnemonicMap, shortcutMap, mnemonicAndShortcutOverrides);
      if (cmd instanceof StructuredCommand){
	Object commandElement =
	  CommandUtilities.getElementForKey((StructuredCommand)cmd, cmdKey);
	if (commandElement instanceof String){
	  add(cmd, cmdKey, menuCmdAdapter, constraints, mnemonicMap, shortcutMap);
	}
	else if (commandElement instanceof SubCommand){
	  SubCommand subCommand = (SubCommand)commandElement;
          addSubCommandMenu(subCommand, cmd, menuCmdAdapter, constraints, mnemonicMap, shortcutMap);
	}
      }
      else
	add(cmd, cmdKey, menuCmdAdapter, constraints, mnemonicMap, shortcutMap);
    }
  }

  private void updateTable(Command cmd, CMenuCommandAdapter cmdAdapter){
    if (commandToAdapterTable == null)
      commandToAdapterTable = new Hashtable();
    Vector adapters = (Vector)commandToAdapterTable.get(cmd);
    if (adapters == null){
      adapters = new Vector(1); //adding a command to a menu more than once should be rare
      commandToAdapterTable.put(cmd, adapters);
    }
    adapters.addElement(cmdAdapter);
  }

  private void add(Command cmd, String cmdKey, CMenuCommandAdapter cmdAdapter,
		   RepresentationConstraints constraints, KeyMap mnemonicMap, KeyMap shortcutMap){
    add(cmd, false, cmdKey, cmdAdapter, constraints, mnemonicMap, shortcutMap);
  }

  /**
   * @undocumented
   */
  protected CMenu newSubMenu(Command cmd, String cmdKey, CMenuCommandAdapter cmdAdapter,
    RepresentationConstraints constraints, KeyMap mnemonicMap)
  {
    return new CMenu(cmd, cmdKey, cmdAdapter, constraints, getMnemonic(cmd, cmdKey, mnemonicMap));
  }

  private JMenuItem add(Command cmd, boolean isSubMenu, String cmdKey, CMenuCommandAdapter cmdAdapter,
			RepresentationConstraints constraints, KeyMap mnemonicMap, KeyMap shortcutMap){
    if (isSubMenu)
      return add(newSubMenu(cmd, cmdKey, cmdAdapter, constraints, mnemonicMap));
    else{
      Object state = cmd.getState(cmdKey);
      if (state == null)
	return add(new CMenuItem(cmd, cmdKey, cmdAdapter, constraints,
				 getMnemonic(cmd, cmdKey, mnemonicMap),
				 getShortcut(cmd, cmdKey, shortcutMap)));
      else
	return add(new CCheckboxMenuItem(cmd, cmdKey, cmdAdapter,
				  ((Boolean)state).booleanValue(), constraints,
					 getMnemonic(cmd, cmdKey, mnemonicMap),
					 getShortcut(cmd, cmdKey, shortcutMap)));
    }
  }

  static Character getMnemonic(Command cmd, String cmdKey, KeyMap mnemonicMap){
    if (mnemonicMap != null){
      Object value = mnemonicMap.get(cmdKey);
      if (value == null){
	if (cmd instanceof KeyableCommand) //no override -> return default
	  return ((KeyableCommand)cmd).getMnemonic(cmdKey);
	else
	  return null;
      }
      else if (value instanceof Character)//override -> return override
	return (Character)value;
      else
	return null;
    }
    else{
      if (cmd instanceof KeyableCommand)
	return ((KeyableCommand)cmd).getMnemonic(cmdKey);
      else
	return null;
    }
  }

 static KeyStroke getShortcut(Command cmd, String cmdKey, KeyMap shortcutMap){
    if (shortcutMap != null){
      Object value = shortcutMap.get(cmdKey);
      if (value == null){
	if (cmd instanceof KeyableCommand) //no override -> return default
	  return ((KeyableCommand)cmd).getShortcut(cmdKey);
	else
	  return null;
      }
      else if (value instanceof KeyStroke)//override -> return override
	return (KeyStroke)value;
      else
	return null;
    }
    else{
      if (cmd instanceof KeyableCommand)
	return ((KeyableCommand)cmd).getShortcut(cmdKey);
      else
	return null;
    }
  }

 /**
  * @undocumented
  */
  public void createMenu(CMenu menu, Vector structure, Command cmd,
		  CMenuCommandAdapter cmdAdapter, boolean addSeparator,
		  RepresentationConstraints constraints,
		  KeyMap mnemonicMap, KeyMap shortcutMap){
    if (structure == null){
    	return;
    }
    if (addSeparator) {
      menu.addSeparator();
    }
    for (int i=0; i<structure.size(); i++){
      Object element = structure.elementAt(i);
      if (element instanceof String){
	menu.add(cmd, (String)element, cmdAdapter, constraints, mnemonicMap, shortcutMap);
      }
      else if (element instanceof Vector){
	if ((!addSeparator)&&(i == 0))
	  createMenu(menu, (Vector)element, cmd, cmdAdapter, false, constraints, mnemonicMap, shortcutMap);
	else createMenu(menu, (Vector)element, cmd, cmdAdapter, true, constraints, mnemonicMap, shortcutMap);
      }
      else if (element instanceof SubCommand){
        SubCommand subCommand = (SubCommand)element;
        addSubCommandMenu(subCommand, cmd, cmdAdapter, constraints, mnemonicMap, shortcutMap);
      }
    }
  }

  String getKey(){
    return key;
  }

  CMenuCommandAdapter getCommandAdapter(){
    return cmdAdapter;
  }

  /**
   * @undocumented
   */
  protected void addSubCommandMenu(SubCommand subCommandElement,
                          Command cmd,
			  CMenuCommandAdapter cmdAdapter,
			  RepresentationConstraints constraints,
			  KeyMap mnemonicMap, KeyMap shortcutMap)
  {
    CMenu newMenu = createSubMenu(cmd, subCommandElement.getKey(), cmdAdapter,
                                         constraints, mnemonicMap, shortcutMap);
    boolean addSeparator = (newMenu.getItemCount() > 0);
    newMenu.createMenu(newMenu, subCommandElement.getStructure(), cmd, cmdAdapter,
                      addSeparator, constraints, mnemonicMap, shortcutMap);
  }

  /**
   * @undocumented
   */
  protected CMenu createSubMenu(Command command, String cmdKey,
        CMenuCommandAdapter cmdAdapter,	RepresentationConstraints constraints,
        KeyMap mnemonicMap, KeyMap shortcutMap)
  {
    CMenu newMenu = (CMenu)add(command, true, cmdKey, cmdAdapter, constraints, mnemonicMap, shortcutMap);
    add(newMenu);
    return newMenu;
  }

  public final void remove(Command cmd){
    remove(cmd, null);
  }

  public final void remove(Command cmd, String cmdKey){
    if (commandToAdapterTable == null)
      return;
    Vector adapters = (Vector)commandToAdapterTable.get(cmd);
    if (adapters != null){
      for (int i=adapters.size()-1; i>=0; i--){
	CMenuCommandAdapter adapter = (CMenuCommandAdapter)adapters.elementAt(i);
	boolean removed = adapter.remove(cmdKey);
	if (removed)
	  adapters.removeElement(adapter);
      }
      if (adapters.isEmpty())
	commandToAdapterTable.remove(cmd);
    }
  }

  @Override
  public final void removeAll()
  {
    if (commandToAdapterTable != null) {
      Enumeration e = commandToAdapterTable.keys();
      while (e.hasMoreElements()) {
        Command cmd = (Command)e.nextElement();
        remove(cmd);
      }
    }
  }

  /** workaround to Swing bug: 4189244: Swing Popup menu is not being refreshed
   * (cleared) under a Dialog
   * http://developer.java.sun.com/developer/bugParade/bugs/4189244.html
   *
   * repaints the first JComponent it finds when the menu hidden
   */
  @Override
  public void setPopupMenuVisible(boolean vis) {
    super.setPopupMenuVisible(vis);
    if (!vis) {
      java.awt.Component c = getPopupMenu().getInvoker();
      if (c instanceof javax.swing.JComponent) {
        java.awt.Container parent = (java.awt.Container) c;
        while (!(parent instanceof javax.swing.JComponent)) {
          c = parent;
          parent = c.getParent();
        }
        javax.swing.JComponent jc = (javax.swing.JComponent)c;
        jc.paintImmediately(0, 0, jc.getWidth(), jc.getHeight());
      }
    }
  }
}













