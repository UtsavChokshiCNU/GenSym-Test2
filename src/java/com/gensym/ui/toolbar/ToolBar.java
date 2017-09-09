/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ToolBar.java
 *
 */

package com.gensym.ui.toolbar;

import java.util.Hashtable;
import java.util.Vector;
import java.awt.Image;
import javax.swing.JToolBar;
import com.gensym.ui.Command;
import com.gensym.ui.StructuredCommand;
import com.gensym.ui.SubCommand;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.message.Resource;
import javax.swing.JSeparator;
import java.awt.Dimension;
import com.gensym.ui.LookAndFeel;
import javax.swing.border.EtchedBorder;
import java.util.Enumeration;

/**
 * ToolBar is a "command-aware" toolbar container. It provides API for adding
 * Commands.
 *<p>
 * In general, when a Command is added to a ToolBar, the ToolBar:
 * <LI>Creates and adds a button for each command key.  A command with state
 * generates a toggle button.
 * <LI>Applies the default or specified RepresentationConstraints
 * <LI>Ensures that the initial availability and state of the menu item is in sync
 * with the current availability and state of the command.
 * <L>Registers the Command as an ActionListener with each menu item and registers
 * a CommandListener with the Command to respond appropriately to changes in the
 * Command.
 *</p><p>
 * The actionCommand of the ActionEvent dispatched from the generated buttons
 * is the command key.
 *</p>
 * @see com.gensym.ui.Command
 * @see com.gensym.ui.RepresentationConstraints
 */

public class ToolBar extends JToolBar{
  private static final RepresentationConstraints defaultConstraints =
      new RepresentationConstraints(RepresentationConstraints.ICON_ONLY,
				  RepresentationConstraints.CENTER,
				  RepresentationConstraints.CENTER,
				  RepresentationConstraints.CENTER,
				  RepresentationConstraints.CENTER);
  private static Resource i18n = Resource.getBundle("com/gensym/ui/toolbar/Errors");
  private String name;

  private Hashtable commandToAdapterTable;

  /** Creates a ToolBar.  By default, it does not float. */
  public ToolBar(){
    this(null);
  }

  public ToolBar(String name){
    super();
    this.name = name;
    setBorderPainted(false);
    //turn off floating toolbars due to flaky behavior [cmh:12.04.97]
    setFloatable(false);
  }

  /**
   * Returns the name of this toolbar.
   *
   */
  @Override
  public String getName(){
    return name;
  }

  /**
   * Adds buttons for each command key in cmd. The small icon of the
   * command is used as the icon for the button and the long description
   * of the command is used as the tool tip for the button.
   * Commands with state are represented by toggle buttons.
   *
   * @see com.gensym.ui.Command#getIcon
   * @see com.gensym.ui.Command#getDescription
   */
  public final void add(Command command){
    if (command == null)
      throw new IllegalArgumentException(i18n.getString("CommandCanNotBeNull"));
    ToolBarCommandAdapter cmdAdapter =
      new ToolBarCommandAdapter(command,  defaultConstraints, this, true);
    updateTable(command, cmdAdapter);
    add(command, cmdAdapter, defaultConstraints);
  }


  /**
   * Adds the command and applies the specified constraints to each generated button.
   * If specified in the constraints, the small icon of the Command is used for the
   * button's icon, the short description of the Command is used for the button's
   * label and the short description of the Command is used for the button's label.
   *
   * @see com.gensym.ui.Command#getDescription
   * @see com.gensym.ui.Command#getIcon
   */
  public final void add(Command command, RepresentationConstraints constraints){
    if (command == null)
      throw new IllegalArgumentException(i18n.getString("CommandCanNotBeNull"));
        ToolBarCommandAdapter cmdAdapter =
	  new ToolBarCommandAdapter(command, constraints, this, true);
    updateTable(command, cmdAdapter);
    add(command, cmdAdapter, constraints);
  }

  void add(Command command, ToolBarCommandAdapter cmdAdapter,
	   RepresentationConstraints constraints){
    if (command instanceof StructuredCommand){
      Vector structuredKeys = ((StructuredCommand)command).getStructuredKeys();
      createGroups(structuredKeys, command, cmdAdapter, true, constraints);
    }
    else {
      ToolBarButton btn;
      String[] keys = command.getKeys();
      if (!(keys == null))
	for (int i=0; i<keys.length; i++){
	  Image icon = command.getIcon(keys[i], Command.SMALL_ICON);
	  add(command, keys[i], cmdAdapter, constraints);
	}
    }
  }

  /**
   * Adds a single button for the specified cmdKey.  The small icon of the
   * command is used for the icon of the button and the long description of the
   * command is used for the tool tip.  If the command has state,
   * then a toggle button is generated. Single actions of StructuredCommands
   * will ignore to STRUCTURE_CHANGED CommandEvents.
   *
   * @see com.gensym.ui.Command#getIcon
   * @see com.gensym.ui.Command#getDescription
   */
  public final void add(Command command, String cmdKey){
    if (command == null)
      throw new IllegalArgumentException(i18n.getString("CommandCanNotBeNull"));
    ToolBarCommandAdapter cmdAdapter = new ToolBarCommandAdapter(command, defaultConstraints, this, false);
    updateTable(command, cmdAdapter);
    add(command, cmdKey, cmdAdapter, defaultConstraints);
  }


  /**
   * Adds a single action of the command and applies the specified
   * constraints. If specified in the constraints, the small icon of the Command
   * is used for the button's icon, the short description of the Command is used
   * for the button's label and the short description of the Command is used for
   * the button's label. Single actions of StructuredCommands
   * will ignore to STRUCTURE_CHANGED CommandEvents.
   *
   *
   * @see com.gensym.ui.Command#getDescription
   * @see com.gensym.ui.Command#getIcon
   */
  public final void add(Command command, String cmdKey,
		  RepresentationConstraints constraints){
    if (command == null)
      throw new IllegalArgumentException(i18n.getString("CommandCanNotBeNull"));
    ToolBarCommandAdapter cmdAdapter =  new ToolBarCommandAdapter(command, constraints, this, false);
    updateTable(command, cmdAdapter);
    add(command, cmdKey, cmdAdapter, constraints);
  }

  private void updateTable(Command cmd, ToolBarCommandAdapter cmdAdapter){
    if (commandToAdapterTable == null)
      commandToAdapterTable = new Hashtable();
    Vector adapters = (Vector)commandToAdapterTable.get(cmd);
    if (adapters == null){
      adapters = new Vector(1); //adding a command more than once should be rare
      commandToAdapterTable.put(cmd, adapters);
    }
    adapters.addElement(cmdAdapter);
  }

  private void add(Command command, String cmdKey, ToolBarCommandAdapter cmdAdapter,
		   RepresentationConstraints constraints){
    Boolean state = command.getState(cmdKey);
    if (state == null)
      add(new ToolBarButton(command, cmdKey, cmdAdapter, constraints));
    else
      add(new ToolBarToggleButton(command, cmdKey, cmdAdapter, constraints,
				     state.booleanValue()));
  }

  @Override
  public void addSeparator() {
    if (LookAndFeel.getUseSnappyLookAndFeel()) {
      JSeparator sep = new JToolBar.Separator();
      add(sep);
      int height = getPreferredSize().height - 4;
      remove(sep);
      JSeparator sep1 = new JToolBar.Separator(new Dimension(2,height));
      add(sep1);
      sep1 = new JToolBar.Separator(new Dimension(2,height));
      sep1.setBorder(new EtchedBorder(EtchedBorder.LOWERED));
      add(sep1);
      sep1 = new JToolBar.Separator(new Dimension(2,height));
      add(sep1);
    }
    else
      super.addSeparator();
  }

  private boolean createGroups(Vector structure, Command command,
		    ToolBarCommandAdapter cmdAdapter, boolean addSeparator,
		    RepresentationConstraints constraints){
    boolean result = false;
    if (structure == null){
    	return result;
    }
    for (int i=0; i<structure.size(); i++){
      boolean subAddSeparator = ( (addSeparator)&&(i < (structure.size() - 1)) );
      Object element = structure.elementAt(i);
      if (element instanceof String){
	Image icon = command.getIcon((String)element, Command.SMALL_ICON);
	if (icon != null) {
	  add(command, (String)element, cmdAdapter, constraints);
          result = true;
        }
      }
      else if (element instanceof Vector){
        result = createGroups((Vector)element, command, cmdAdapter, subAddSeparator, constraints);
      }
      else if (element instanceof SubCommand) {
        SubCommand subCommand = (SubCommand)element;
        result = createGroups(subCommand.getStructure(), command, cmdAdapter, subAddSeparator, constraints);
      }
      else if (element == null){
        addSeparator();
      }
    }
    if ((addSeparator) && (result))
      addSeparator();
    return result;
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
        ToolBarCommandAdapter adapter = (ToolBarCommandAdapter)adapters.elementAt(i);
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
}

