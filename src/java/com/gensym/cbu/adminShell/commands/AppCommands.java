/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 AppCommands.java
 *
 */
package com.gensym.denali.developer.commands;

import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.WindowEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowListener;
import java.io.File;
import java.net.URL;
import javax.swing.*;
import com.gensym.core.GensymApplication;
import com.gensym.denali.developer.*;
import com.gensym.denali.model.Server;
import com.gensym.denali.model.SchematicImpl;
import com.gensym.denali.simpleclient.*;
import com.gensym.dlg.*;
import com.gensym.mdi.*;
import com.gensym.message.Resource;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;

public final class AppCommands extends AbstractCommand 
{
  public static final String NEWMODULE = "NewModule";
  public static final String OPENMODULE = "OpenModule";
  public static final String CLOSEMODULE = "CloseModule";
  public static final String SAVEMODULE = "SaveModule";
  public static final String SAVEASMODULE = "SaveAsModule";
  public static final String SAVESPECIAL = "SaveSpecial";
  public static final String SAVEDEF = "SaveDef";
  public static final String NEWROOT = "NewRoot";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private Resource i18n = Resource.getBundle("denali/developer/commands/Errors");
  private static final String defSourceCodeTitle = "Save Definition Source Code";

  private SaveDefSourceCodeDialog defSourceCodeDialog;

  Frame frame;
  Shell shell;

  public AppCommands(Frame frame, Shell shell)
  {
    super(new CommandInformation[]{
      new CommandInformation(NEWMODULE, true, shortResource, longResource, null, 
			     null, null, false),
      new CommandInformation(OPENMODULE, true, shortResource, longResource, null, 
			     null, null, false),
      new CommandInformation(CLOSEMODULE, true, shortResource, longResource, null, 
			     null, null, false),
      new CommandInformation(SAVEMODULE, true, shortResource, longResource, null, 
			     null, null, false),
      new CommandInformation(SAVEASMODULE, true, shortResource, longResource, null, 
			     null, null, false),
	/*
      new CommandInformation(SAVESPECIAL, true, shortResource, longResource, null, 
			     null, null, false),
			     */
      new CommandInformation(SAVEDEF, true, shortResource, longResource, null, 
			     null, null, false),
      new CommandInformation(NEWROOT, true, shortResource, longResource, null, 
			     null, null, false),
	});
    this.frame = frame;
    this.shell = shell;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)){
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", 
						  cmdKey));
    }
    
    if (cmdKey.equals(NEWMODULE))
      newModuleSelected();
    else if (cmdKey.equals(OPENMODULE))
      openModuleSelected();
    else if (cmdKey.equals(CLOSEMODULE))
      closeModuleSelected();
    else if (cmdKey.equals(SAVEMODULE))
      saveModuleSelected();
    else if (cmdKey.equals(SAVEASMODULE))
      saveAsModuleSelected();
    else if (cmdKey.equals(SAVESPECIAL))
      saveSpecialSelected();
    else if (cmdKey.equals(SAVEDEF))
      saveDefinitionSelected();
    else if (cmdKey.equals(NEWROOT))
      newRootSelected();
  }


  private void newModuleSelected()
  {
    ClientSession session = shell.getCurrentSession();
    Server server = session.getServer();
    String newModuleName = (String)
      JOptionPane.showInputDialog(frame, "Enter name of new module:", 
				  "New Module Name",
				  JOptionPane.QUESTION_MESSAGE, 
				  null, null, "NewModule");
    if(newModuleName != null) {
      try {
	server.addModule(newModuleName);
      }
      catch (Exception e)
	{
	  System.out.println("trouble creating Module");
	  e.printStackTrace();
	}
    }
  }

  private void openModuleSelected()
  {
    ClientSession session = shell.getCurrentSession();
    Server server = session.getServer();

    String selectedModule = moduleChooser();

    if(!selectedModule.equals("")) {
      try {
	server.loadModule(selectedModule);
      }
      catch (Exception e)
	{
	  JOptionPane.showMessageDialog(frame,
					e.getMessage(),
					"Trouble Loading Module",
					JOptionPane.ERROR_MESSAGE);
	}
    } 
    
  }

  private void closeModuleSelected()
  {
    ClientSession session = shell.getCurrentSession();
    Server server = session.getServer();
    ModuleView module = shell.getCurrentModule();
    String moduleName = module.getName();

    JOptionPane closeModuleDialog = new JOptionPane();
    int result;
    result = closeModuleDialog.showConfirmDialog(frame, 
						 "Are you sure you want to close: " +
						 moduleName
						 +"?",
						 "Closing Module", 
						 JOptionPane.YES_NO_OPTION,
						 JOptionPane.WARNING_MESSAGE, 
						 null);
    if (result == JOptionPane.YES_OPTION) {
      System.out.println("Closing "+moduleName+".");
      try {
	server.removeModule(moduleName);
      }
      catch (Exception e)
	{
	  System.out.println("trouble creating Module");
	  e.printStackTrace();
	}
    }
    else if (result == JOptionPane.NO_OPTION) {
      System.out.println("Abandoning module removal");
    }
    else
      System.out.println("Bad choice");
  }

  private void saveModuleSelected()
  {
    ClientSession session = shell.getCurrentSession();
    Server server = session.getServer();
    ModuleView module = shell.getCurrentModule();
    String moduleName = module.getName();
    try {
      server.saveModule(moduleName);
    }
    catch (Exception e)
      {
	System.out.println("trouble saving Module");
	e.printStackTrace();
      }
  }

  private void saveAsModuleSelected()
  {
    String newModuleName = moduleChooser();

    if(newModuleName != null) {
      ClientSession session = shell.getCurrentSession();
      Server server = session.getServer();
      ModuleView module = shell.getCurrentModule();
      String moduleName = module.getName();
      try {
	server.saveModule(moduleName, newModuleName);
      }
      catch (Exception e)
	{
	  System.out.println("trouble with module saving as");
	  e.printStackTrace();
	}
    }
  }

  private void saveSpecialSelected()
  {
    System.out.println("Hey! Somebody needs to implement saveSpecial");
  }

  // Might be nice to pass it a string for the message (if current message is 
  //  too generic. -craig
  String moduleChooser()
  {
    String urlName = "";
    ClientSession session = shell.getCurrentSession();
    Server server = session.getServer();
    JFileChooser fileChooser 
      = new JFileChooser(new ServerFileSystemView(new ClientSession[] { session }));

    // Put in a filter when I figure it out a bit better...
    String selectedModule = "";
    int returnValue = fileChooser.showDialog(frame, "Select Module");

    if(returnValue == JFileChooser.APPROVE_OPTION) {
      try {
	selectedModule = fileChooser.getSelectedFile().getPath();
	String rootName = server.getRepositoryRoot().url.toExternalForm();
	selectedModule = selectedModule.substring(rootName.length());
	File file = fileChooser.getSelectedFile();

	URL url = new URL("file", "", 0, selectedModule);
	urlName = url.getFile();
	// Check to see if it ends in ".xml"
	if(urlName.length() > 4) {
	  int index = urlName.toUpperCase().indexOf(".XML", urlName.length() - 4);
	  if (index > 0)
	    urlName = urlName.substring(0, index);
	}
	urlName = urlName.replace('/', '.');
	
	System.out.println("  -Module name: "+urlName+".");
      }
      catch (Exception e) {
	System.out.println("trouble choosing module");
	e.printStackTrace();
      }
    }

    return urlName;
  }

  private void saveDefinitionSelected()
  {
    System.out.println("In saveDefinitionSelected()");

    if (defSourceCodeDialog == null) {
      try {
	defSourceCodeDialog = new SaveDefSourceCodeDialog(frame);
      }
      catch (Exception e)
	{
	    System.out.println("Failed to launch icon dialog");
	    e.printStackTrace();
	}
      WindowAdapter windowAdapter = new WindowAdapter(){
	@Override
	public void windowClosing(WindowEvent event) {
	  hideDialog(defSourceCodeDialog, SAVEDEF);
	}
      };
      defSourceCodeDialog.addWindowListener(windowAdapter);
    }      
    if (!defSourceCodeDialog.isVisible()) 
      showDialog(defSourceCodeDialog, SAVEDEF);
    else 
      hideDialog(defSourceCodeDialog, SAVEDEF);
  }

  private void newRootSelected()
  {
    String newSchematicName = (String)
      JOptionPane.showInputDialog(frame, "Enter name of new schematic:", 
				  "New Schematic Name",
				  JOptionPane.QUESTION_MESSAGE, 
				  null, null, "NewSchematic");
    if(newSchematicName != null) {
      try {
	//	shell.getCurrentModule().createAppContainer(SchematicImpl.class.toString(), 
	shell.getCurrentModule().createAppContainer("com.gensym.denali.model.SchematicImpl", 
						    newSchematicName);
      }
      catch (Exception e)
	{
	  System.out.println("trouble creating new root");
	  e.printStackTrace();
	}
    }
  }

  // Trying to keep a minimum of Browser code in here -cas
  private void showDialog(GenericDialog dialog, String name)
  {
    setState(name, Boolean.TRUE);
    dialog.showDialog(frame);
  }

  private void hideDialog(GenericDialog dialog, String name)
  {
    setState(name, Boolean.FALSE);
    dialog.hideDialog();
  }
}
