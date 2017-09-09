/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 SystemTablesCommands.java
 *
 */
package com.gensym.shell.commands;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.net.MalformedURLException;
import java.util.Vector;

import com.gensym.classes.Kb;
import com.gensym.classes.Module;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.SystemTable;
import com.gensym.dlgruntime.DialogManager;
import com.gensym.dlgruntime.ResourceInstantiationException;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;

/** 
 * Command to access the System Tables for a given module. The
 * application adding this command is responsible for managing the 
 * module, to make sure that the module passed as the argument, is
 * in fact correct for the current connection. Use the {@link
 * #setModule} method for this purpose.
 * 
 */

public class SystemTablesCommands extends AbstractStructuredCommand {

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";

  private static Resource i18n = Resource.getBundle("com/gensym/shell/commands/Messages");

  private Component requestingComponent;
  private DialogManager dialogManager;
  private TwAccess currentConnection;
  private Module module;
  private Vector tablesList;

  /**
   * Creates a SystemTablesCommand for a given module.
   * @param {@link java.awt.Component}  a component  controling where the System
   * Table dialog will be displayed
   * @param {@link com.gensym.classes.Module} a module for which to display the System Tables
   */
  public SystemTablesCommands(Component requestingComponent, Module module) {
    super (new CommandInformation[] {});
    this.requestingComponent = requestingComponent;
    setModule(module);
  }

  /** 
   * Creates a SystemTablesCommand for a given module, without
   * references the owner-module of the tables.
   * The parent application must explicitely set the module, using
   * the {@link setModule} method to make this command available.
   */
  public SystemTablesCommands(Component requestingComponent){
    this(requestingComponent, null);
  }

    /**
   * This method returns the current module for which the
   * System Tables can be displayed.
   * @return {@link com.gensym.classes.Module} the current module set for the command
   */
  public Module getModule() {
    return module;
  }

  /** 
   * This method sets the module for which to display the
   * System Tables. The application using this Command, is
   * responsible for updating the command when the applicable 
   * module changes, using this method.
   * @param {@link com.gensym.classes.Module} the module 
   * for which to diplay the System Tables
   */
  public void setModule(Module module){
    //save the module, get its system tables, build the command
    // and set its availability
    this.module = module;
    setStructuredKeys(createSystemTablesCommandInformations());
    setAvailability();
   }
  
      
  /**
   * @undocumented
   * This is an internal method to build the
   * command, according to the connection (the
   * specific G2).
   */
  protected void setStructuredKeys(CommandInformation[] structure){
    super.setStructuredKeys(structure);
  }

  /**
   * @undocumented
   * This is an internal method to get the current
   * connection.
   */
  protected TwAccess getConnection(Item item){
    if (module !=null) {
      TwAccess currentConnection = ((TwAccess)((ImplAccess)item).getContext());
      return currentConnection;
    } else return null;
  }

  private Vector getTablesList(Module module) {
    if (module == null)
      return new Vector(); //or return null, and check all callers
    else 
      return (Vector)module.getSystemTables();
  }
  
  /**
   * @undocumented
   * This is an internal method to build the system tables command
   */
  protected CommandInformation[] createSystemTablesCommandInformations(){
    //this method is called only from setModule(), so,
    // there should be no doubt what the module is.
    tablesList = getTablesList(module);
    CommandInformation[] systemTables  = new CommandInformation[tablesList.size()];
    for (int i=0; i<tablesList.size(); i++){
      try{
	String key = ((Item)(tablesList.elementAt(i))).getG2ClassName().getPrintValue();
	systemTables[i] = 
	  new CommandInformation(key, true,
				 shortResource, longResource,
				 null, null,
				 null, false,
				 null, null);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }
    return systemTables;
  }

  /**
   * This method responds to the user action of selecting a 
   * specific System Tables menu by putting up a default dialog, 
   * using the {@link com.gensym.dlgruntime.DialogManager}, consisting of
   * all the properties of the specific System Table. Do not use this
   * method directly.
   * @param {@link java.awt.event.ActionEvent} event fired by the user action
   * of selecting a menu
   */
  
 @Override
 public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    Item table = getSystemTable(cmdKey);
    if (table != null) {
      // to get the current connection, cast the table into ImpAccess,
      // which provides the connection of the item. The connection is
      // needed for the DialogManager.
      try {
      TwAccess currentConnection = getConnection(table);
      DialogManager dialogManager = currentConnection.getDialogManager();
      dialogManager.editItem(requestingComponent, table, 
			       currentConnection.getUserMode(),
			       Resource.getDefaultLocale());
      
      } catch (G2AccessException gae) {
	Trace.exception (gae);
      } catch (ResourceInstantiationException rie) {
	Trace.exception (rie);
      } catch (MalformedURLException mue) {
	Trace.exception (mue);
      }
    }
  }

  /**
   * @undocumented
   * This is an internal method for fetching the
   * appropriate system table for the actionPerformed method.
   * It first updates the module, which could potentially update
   * the tablesList, as well as the command itself. This happens only
   * if the module has been reset, for the same connection.
   */

 protected Item getSystemTable(String cmdKey) {
   //it's necessary to get the module and update it, since
   // it's possible that  a new module has been selected as
   // top level (for example) without changing the connection
   Module mod = getModule();
   if (mod != module) setModule(mod);
   for (int i=0; i<tablesList.size(); i++) {
     try{
       if (cmdKey.equals(((Item)(tablesList.elementAt(i))).getG2ClassName().getPrintValue()))
       return ((Item)(tablesList.elementAt(i)));
     } catch (G2AccessException gae){Trace.exception(gae);}
   }
   return null;
 }
   
/**
 * @undocumented
 * Internal method to set the availability of the command.
 * Currently, the whole command is available if a module is set.
 */
  protected void setAvailability() {
    boolean available = (module != null);
    for(int i=0; i<tablesList.size(); i++){
      try {
	String key = ((Item)(tablesList.elementAt(i)))
	  .getG2ClassName().getPrintValue();
	setAvailable(key, available);
      }catch (G2AccessException gae) {Trace.exception (gae);}
    }
  }

  
  
}






