/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ViewCommands.java
 *
 */
package com.gensym.cbu.adminShell.commands;

import java.awt.Frame;
import java.awt.event.WindowListener;
import java.awt.event.WindowEvent;
import java.awt.event.ActionEvent;
import java.awt.geom.NoninvertibleTransformException;
import java.rmi.RemoteException;
import java.awt.TextArea;
import java.awt.BorderLayout;
import javax.swing.*;
import com.gensym.core.UiApplication;
import com.gensym.denali.developer.*;
import com.gensym.denali.simpleclient.*;
import com.gensym.denali.model.Schematic;
import com.gensym.denali.model.RemoteItem;
import com.gensym.mdi.*;
import com.gensym.core.GensymApplication;
import com.gensym.message.Resource;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.uiutil.dialogs.ZoomDialog;
import com.gensym.dlg.*;

public final class ViewCommands extends AbstractCommand 
  implements StandardDialogClient,VisibilityListener
{
  private DenaliLogDialog logDialog;

  //  final static ImageIcon logIcon = new ImageIcon(ViewCommands.class.
  //						    getResource("logs.gif").getFile());

  public static final String SCHEMATIC = "Schematic";
  public static final String LOG = "Log";
  public static final String ZOOM = "Zoom";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private Resource i18n = Resource.getBundle("denali/developer/commands/Errors");
  private String[] workspaceNames;
  private String workspaceName;
  //  private NodeCreator nodeCreator;
  Frame frame;


  //  public ViewCommands(Frame frame, NodeCreator nodeCreator)
  public ViewCommands(Frame frame)
  {
    super(new CommandInformation[]{
      new CommandInformation(SCHEMATIC, true, shortResource, longResource, null, 
			     null, null, true),
      new CommandInformation(LOG, true, shortResource, longResource, null, 
			     null, null, true),
      new CommandInformation(ZOOM, true, shortResource, longResource, null, 
			     null, null, false)
	});
    this.frame = frame;
    //    this.nodeCreator = nodeCreator;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)){
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", 
						  cmdKey));
    }
    
    if (cmdKey.equals(SCHEMATIC))
      //      makeTestWorkspace();
      System.out.println("This probably will be removed.");
    else if (cmdKey.equals(LOG))
      logSelected();
    else if (cmdKey.equals(ZOOM))
      //      zoom();
      System.out.println("Zooooom!");
  }

  private void makeTestWorkspace()
  {
    MDIFrame mdiFrame = (MDIFrame)frame;
    ClientApplication shell = (ClientApplication) GensymApplication.getApplication();
    ClientSession session = shell.getCurrentSession();
    try {
      if (session != null)
	{
	  workspaceNames = session.getWorkspaceNames();
	  SelectionDialog dialog
	    = new SelectionDialog (frame, "Choose a Schematic", true,
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
	      //  SchematicDocument doc 
	      //= new SchematicDocument(session,schematic,workspaceName,nodeCreator);
	      //    mdiFrame.getManager().addDocument(doc, doc.getPreferredSize());
	    }
	}
    }
    catch (Exception e)
      {
	System.out.println("failed to make test workspace");
	e.printStackTrace();
      }
  }

  public void visibilityChangeRequested(VisibilityEvent event)
  {
    if (event.shouldBeVisible())
      {
	RemoteItem remoteItem = event.getItemToShowOrHide();
	if (remoteItem instanceof Schematic)
	  {
	    ClientApplication shell = (ClientApplication) GensymApplication.getApplication();
	    ClientSession session = shell.getCurrentSession();
	    MDIFrame mdiFrame = (MDIFrame)((UiApplication)shell).getCurrentFrame();
	    Schematic schematic = (Schematic)remoteItem;
	    String schematicName = " ";
	    try { schematic.getName(); } catch (RemoteException e) {}
	    //	    SchematicDocument doc 
	    //	      = new SchematicDocument(session,schematic,schematicName,nodeCreator);
	    //	    mdiFrame.getManager().addDocument(doc, doc.getPreferredSize());
	  }
	else
	  System.out.println("can't show "+remoteItem);
      }
    else
      System.out.println("ignoring hide request");
  }

  public void registerAsVisibilityListener(ClientSession clientSession)
  {
    clientSession.addVisibilityListener(this);
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

  private void logSelected()
  {
    if (logDialog == null){
      String title = "Log";
      String msg = "Joe and Vikram culling the log file.";
      boolean isModal = true;
      int numRows = 1;
      int numColumns = 34;
      //      int scrollbarVisibility = TextArea.SCROLLBARS_VERTICAL_ONLY;
      int scrollbarVisibility = TextArea.SCROLLBARS_NONE;

      TextArea logDescription = 
	new TextArea (msg, numRows, numColumns, scrollbarVisibility);
      logDescription.setEditable(false);

      JPanel logPanel = new JPanel(new BorderLayout());
      //      logPanel.add(new JLabel(logIcon), GUI.CENTER);
      logPanel.add(logDescription, GUI.SOUTH);

      logDialog = new DenaliLogDialog(frame, title, isModal, 
					  logPanel,
					  (StandardDialogClient) this);
    }

    logDialog.setVisible (true);
  }

  // Stolen from AboutDialog. -cas
  class DenaliLogDialog extends StandardDialog
  {
    public DenaliLogDialog (Frame parentFrame, String title,
			      boolean isModal, JPanel logPanel,
			      StandardDialogClient client) 
    { 
      super (parentFrame, title, isModal,
	     new String[] {},
	     new int[] {},
	     logPanel, 
	     client);
      
      pack ();
    }

    @Override
    public int getButtonAlignment () {
      return CENTER;
    }
  }

  private void zoom(){
    SchematicView view = getCurrentView();
    new ZoomDialog(frame, view.getScaleX(), view.getScaleY(), new ZoomDialogClient()).setVisible(true);
  }

  private SchematicView getCurrentView(){
    MDIFrame mdiFrame = (MDIFrame)frame;
    MDIDocument doc = mdiFrame.getManager().getActiveDocument();
    if (doc instanceof SchematicDocument){
      return ((SchematicDocument)doc).getSchematicView();
    }
    return null;
  }

  class ZoomDialogClient implements StandardDialogClient{

    @Override
    public void dialogDismissed(StandardDialog dlg, int cmdCode){
      if (dlg.wasCancelled()) return;

      SchematicView view = getCurrentView();
      ZoomDialog zoomDialog = (ZoomDialog)dlg; 
      double scale = zoomDialog.getValue();
      try{
	if (scale == zoomDialog.ZOOM_TO_FIT)
	  view.setScaledToFit(true);
	else
	  view.setScale(scale, scale);
      }
      catch(NoninvertibleTransformException ex){
	//this should never happen
      }
    }
  }
}


