/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ViewCommands.java
 *
 */
package com.gensym.demos.sequoia.course;

import java.awt.event.ActionEvent;
import java.util.Vector;
import com.gensym.mdi.MDIFrame;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.message.Resource;
import com.gensym.message.Trace;

//import connection manager to get named workspace
import com.gensym.classes.KbWorkspace;
import com.gensym.jgi.G2AccessException;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.WorkspaceDocument;

//import a symbol to hold the workspace name
import com.gensym.util.Symbol;

//import these classes to determine command availability
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.ntw.TwAccess;

/*
 * ViewCommands needs to implement ContextChangedListener to 
 * determine when certain commands are available, based on 
 * whether or not a connection exists.
 */
public class ViewCommands extends AbstractStructuredCommand implements ContextChangedListener {

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");
  private Resource shortBundle = Resource.getBundle("com/gensym/demos/sequoia/course/CommandShortResource");

  private static final String SCHEMATIC = "Schematic";
  private static final String PRODUCTION_STATISTICS = "ProductionStatistics";
  private static final String PALETTE = "Palette";

  //Create a static variable that is the name of the workspace to get
  //and convert it to a symbol by using the intern() method
  private static final Symbol SCHEMATIC_ = Symbol.intern("SCHEMATIC");
  private static final Symbol KBWORKSPACE_ = Symbol.intern("KB-WORKSPACE");

  private MDIFrame frame;

  //Create variables for the connection and workspace managers
  private ConnectionManager connectionMgr;

  //Constructor takes a frame, and a connection manager
  public ViewCommands(MDIFrame frame, ConnectionManager connectionManager) {
    super(new StructuredCommandInformation[]{
      new CommandGroupInformation("Group1", new CommandInformation[]{
        new CommandInformation(SCHEMATIC, true, shortResource, longResource, null,
			       null, null, false)}),
      new CommandGroupInformation("Group2", new CommandInformation[]{
        new CommandInformation(PRODUCTION_STATISTICS, true, shortResource, 
			       longResource, null, null, null, false)}),
      new CommandGroupInformation("Group3", new CommandInformation[]{
        new CommandInformation(PALETTE, true, shortResource, longResource, null,
			       null, null, false)})});

    this.frame = frame;
    this.connectionMgr = connectionManager;

    //Constructor adds itself as a listener for ContextChangedEvents
    connectionMgr.addContextChangedListener(this);

    //Set availability of Schematic command to false if there is no 
    //current connection.
    if (connectionMgr.getCurrentConnection() == null)
      setAvailable(SCHEMATIC, false);
  }

  //This method gets called whenever any of the menu choices in the
  //command is selected. It dispatches its action to handler methods,
  //which perform the actual actions of each command.
  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey))
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", 
						  cmdKey));
 
    if (cmdKey.equals(SCHEMATIC))
      handleSchematicCommand();
    else if (cmdKey.equals(PRODUCTION_STATISTICS))
      handleProductionStatisticsCommand();
    else if (cmdKey.equals(PALETTE))
      handlePaletteCommand();
  }

  @Override
  public String[] getKeys(){
    return new String[] {SCHEMATIC, PRODUCTION_STATISTICS, PALETTE};
  }

  //These handler methods perform the actual actions of each command.
  private void handleSchematicCommand() {
    try {
      TwAccess connection = connectionMgr.getCurrentConnection();
      KbWorkspace wksp = (KbWorkspace)connection.getUniqueNamedItem(KBWORKSPACE_, SCHEMATIC_);
      frame.getManager().addDocument(new WorkspaceDocument(connection, wksp));
    }
    catch (G2AccessException e) {
      Trace.exception (e);
    }
    //wkspMgr.getWorkspace(cxnMgr.getCurrentConnection(), SCHEMATIC_);
  }

  private void handleProductionStatisticsCommand() {
    System.out.println("NYI: handleProductionStatisticsCommand");
  }

  private void handlePaletteCommand() {
    System.out.println("NYI: handlePaletteCommand");
  }

  // BEGIN: ContextChangedListener interface methods
  /*
   * When a connection changes, set the availability of the 
   * Schematic command to available.
   */
  @Override
  public void currentConnectionChanged(ContextChangedEvent e){
    TwAccess context = e.getConnection();
    boolean available = true;
    if (context == null)
      available = false;
    setAvailable(SCHEMATIC, available);
  }
  // END: ContextChangedListener interface methods
}













