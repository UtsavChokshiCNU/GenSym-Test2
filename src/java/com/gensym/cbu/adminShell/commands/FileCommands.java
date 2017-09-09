/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ExitCommands.java
 *
 */
package com.gensym.denali.developer.commands;

import java.awt.Frame;
import java.awt.event.WindowListener;
import java.awt.event.WindowEvent;
import java.awt.event.ActionEvent;
import com.gensym.denali.developer.*;
import com.gensym.denali.simpleclient.*;
import com.gensym.denali.model.Schematic;
import com.gensym.mdi.*;
import com.gensym.core.GensymApplication;
import com.gensym.message.Resource;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.dlg.*;

public final class FileCommands extends AbstractCommand 
  implements WindowListener, StandardDialogClient
{
  /** Command to exit application */
  public static final String TEST_DOCUMENT = "TestDocument";
  public static final String TEST_WORKSPACE = "TestWorkspace";
  public static final String SHUTDOWN_SERVER = "ShutdownServer";
  public static final String EXIT = "ExitDeveloperShell";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private Resource i18n = Resource.getBundle("denali/developer/commands/Errors");
  private String[] workspaceNames;
  private String workspaceName;
  private NodeCreator nodeCreator;
  Frame frame;

  public FileCommands(Frame frame, NodeCreator nodeCreator)
  {
    super(new CommandInformation[]{
      new CommandInformation(TEST_DOCUMENT, true, shortResource, longResource, null, 
			     null, null, true),
      new CommandInformation(TEST_WORKSPACE, true, shortResource, longResource, null, 
			     null, null, true),
      new CommandInformation(SHUTDOWN_SERVER, true, shortResource, longResource, null, 
			     null, null, true),
      new CommandInformation(EXIT, true, shortResource, longResource, "exit_tw.gif", 
			     null, null, true)});
    this.frame = frame;
    this.nodeCreator = nodeCreator;
    frame.addWindowListener((WindowListener)this);
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)){
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", 
						  cmdKey));
    }
    
    if (cmdKey.equals(EXIT))
      exitApp();
    else if (cmdKey.equals(TEST_DOCUMENT))
      makeTestDocument();
    else if (cmdKey.equals(TEST_WORKSPACE))
      makeTestWorkspace();
    else if (cmdKey.equals(SHUTDOWN_SERVER))
      shutdownServer();
  }

  @Override
  public void windowClosing(WindowEvent e) {
    exitApp();
  }

  @Override
  public void windowActivated(WindowEvent e) {}
  @Override
  public void windowDeactivated(WindowEvent e) {}
  @Override
  public void windowOpened(WindowEvent e) {}
  @Override
  public void windowClosed(WindowEvent e) {}
  @Override
  public void windowIconified(WindowEvent e) {}
  @Override
  public void windowDeiconified(WindowEvent e) {}

  private void exitApp()
  {
    System.exit(0);
  }

  private void shutdownServer () {
    ClientApplication shell = (ClientApplication) GensymApplication.getApplication();
    ClientSession session = shell.getCurrentSession();
    session.shutdownServer("yeah! baby");
  }

  private void makeTestWorkspace()
  {
    System.out.println("Making test document");
    MDIFrame mdiFrame = (MDIFrame)frame;
    ClientApplication shell = (ClientApplication) GensymApplication.getApplication();
    ClientSession session = shell.getCurrentSession();
    try {
      if (session != null)
	{
	  workspaceNames = session.getWorkspaceNames();
	  SelectionDialog dialog
	    = new SelectionDialog (frame, "Choose a Workspace", true,
				   "select:",
				   workspaceNames,
				   false,
				   0,
				   true,
				   this);
	  dialog.setVisible(true);
	  if (workspaceName != null)
	    {
	      Schematic schematic = session.getNamedWorkspace(workspaceName);
	      SchematicDocument doc 
		= new SchematicDocument(session,schematic,"",null,nodeCreator);
	      mdiFrame.getManager().addDocument(doc, doc.getPreferredSize());
	    }
	}
    }
    catch (Exception e)
      {
	System.out.println("failed to make test workspace");
	e.printStackTrace();
      }
  }

  @Override
  public synchronized void dialogDismissed (StandardDialog dlg, int cmdCode) {
    if (dlg.wasCancelled ())
      workspaceName = null;
    else
      {
	int chosenIndex = ((SelectionDialog)dlg).getResult();
	dlg.setVisible (false);
	workspaceName = workspaceNames[chosenIndex];
      }
  }

  private void makeTestDocument()
  {
    System.out.println("Making test document");
    MDIFrame mdiFrame = (MDIFrame)frame;
    TestDocument doc = new TestDocument();
    mdiFrame.getManager().addDocument(doc, doc.getPreferredSize());
  }
}


