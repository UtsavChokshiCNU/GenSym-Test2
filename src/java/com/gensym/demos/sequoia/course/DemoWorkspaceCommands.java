/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DemoWorkspaceCommands.java
 *
 */
package com.gensym.demos.sequoia.course;

import java.awt.event.ActionEvent;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import java.util.Enumeration;
import java.util.Vector;
import com.gensym.classes.KbWorkspace;
import com.gensym.dlg.ErrorDialog;
import com.gensym.dlg.InputDialog;
import com.gensym.dlg.SelectionDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2CommunicationException;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIManager;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwGateway;
import com.gensym.ntw.WorkspaceShowingListener;
import com.gensym.ntw.WorkspaceShowingEvent;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.shell.util.WorkspaceDocumentFactory;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.Command;
import com.gensym.message.Resource;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.message.Trace;
import com.gensym.wksp.WorkspaceView;

/** Commands to create and delete a kb-workspace. */
public class DemoWorkspaceCommands extends AbstractCommand implements StandardDialogClient, ContextChangedListener, PropertyChangeListener {

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");
  private Resource shortBundle = Resource.getBundle("com/gensym/demos/sequoia/course/CommandShortResource");

  private static final String NEW_KBWORKSPACE = "NewKbWorkspace";
  private static final String DELETE_KBWORKSPACE = "DeleteKbWorkspace";

  private static final Symbol KB_WORKSPACE_ = Symbol.intern("KB-WORKSPACE");

  private MDIFrame frame;
  private ConnectionManager connectionMgr;
  private TwAccess currentConnection;
  private WorkspaceView currentView;

  private WorkspaceDocumentFactory factory = new DemoWorkspaceDocumentFactoryImpl();
  private boolean wkspDocFactorySet = false;

  public DemoWorkspaceCommands(MDIFrame frame, 
			       ConnectionManager connectionManager) {

    super(new CommandInformation[]{
      new CommandInformation(NEW_KBWORKSPACE, true, 
			     shortResource, longResource, 
			     null, null, null, true),
      new CommandInformation(DELETE_KBWORKSPACE, true, 
			     shortResource, longResource, 
			     null, null, null, true)});
    this.frame = frame;
    connectionManager.addContextChangedListener(this);

    setConnection(connectionManager.getCurrentConnection());
    setWorkspaceView(null);
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (!isAvailable(cmdKey))
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", 
						  cmdKey));
   
    if (cmdKey.equals(NEW_KBWORKSPACE))
      handleCreateWorkspaceCommand();
    if (cmdKey.equals(DELETE_KBWORKSPACE))
      handleDeleteWorkspaceCommand();
  }

  private void handleCreateWorkspaceCommand() {
    if (currentConnection != null) {
      //set up parameters of multi-edit dialog
      String title = shortBundle.getString("WorkspaceName");
      String[] textFieldLabels = new String[]{"Workspace Name:"};
      String[] initialValues = new String[]{"none"};
      
      //launch dialog for entering workspace name
      InputDialog inputDialog = new InputDialog(frame, title, true, 
						textFieldLabels, 
						initialValues, 
						(StandardDialogClient) this);
      inputDialog.setVisible(true);
    }
  }

  private void handleDeleteWorkspaceCommand() {
    if (currentView != null) {
      //get KbWorkspace from the workspace view
      KbWorkspace wksp = currentView.getWorkspace();
      try {
	wksp.delete(true, true);
      }
      catch (G2AccessException e) {
	Trace.exception(e);
      }
    }
  }

  private void createWorkspaceDialogDismissed(InputDialog dlg) {
    if (currentConnection != null) {
      //get results of the dialog
      String[] results = dlg.getResults();

      //convert the results to a symbol
      Symbol wkspName = Symbol.intern(results[0].toUpperCase());

      try {
	//create a KbWorkspace
	KbWorkspace wksp = (KbWorkspace)currentConnection.createItem(KB_WORKSPACE_);

	//set workspace name
	wksp.setNames(wkspName);

	//make workspace permanent
	wksp.makePermanent();

	WorkspaceDocument doc; 

	//frame.getManager().addDocument(doc);
	frame.getManager().addDocument(doc = factory.createWorkspaceDocument(currentConnection, wksp));
	doc.addPropertyChangeListener(this);

	//should catch G2AccessException, not exception
      } catch (Exception e){
	displayError("", e.getMessage());
	setConnection(null);
      }
    }
  }

  @Override
  public void dialogDismissed (StandardDialog dlg, int code) {
    if (dlg.wasCancelled()) return;
    if (dlg instanceof InputDialog)
      createWorkspaceDialogDismissed((InputDialog)dlg);
  }

  public void setWorkspaceView(WorkspaceView workspaceView) {
    currentView = workspaceView;
    updateAvailability();
  }

  private void updateAvailability() {
    setAvailable(DELETE_KBWORKSPACE, (currentView != null));
  }   

  //PropertyChangedListener method
  @Override
  public void propertyChange (PropertyChangeEvent e) {
    WorkspaceDocument document = (WorkspaceDocument)e.getSource();
    if (e.getPropertyName().equals(WorkspaceDocument.IS_SELECTED_PROPERTY)){
      Boolean selected = (Boolean)e.getNewValue();
      if (selected.booleanValue())
	setWorkspaceView(document.getWorkspaceView());
      else
	setWorkspaceView(null);
    }
  }

  public void setConnection(TwAccess connection) {
    currentConnection = connection;
    boolean available = true;
    available = (currentConnection != null);
  
    // GET_KBWORKSPACE should check for named workspaces
    //setAvailable(GET_KBWORKSPACE, available);
    setAvailable(NEW_KBWORKSPACE, available);
  }

  /** 
   *  Sets the WorkspaceDocumentFactory that is used to create 
   *  WorkspaceDocuments. By default, DefaultWorkspaceDocumentFactoryImpl 
   *  is used. This method may only be called once.
   */
  public void setWorkspaceDocumentFactory(WorkspaceDocumentFactory factory) {
    if (wkspDocFactorySet)
      throw new Error(i18n.getString("WorkspaceDocumentFactoryAlreadyDefined"));
    else {
      this.factory = factory;
      wkspDocFactorySet = true;
    }
  }

  // BEGIN: ContextChangedListener methods
  @Override
  public void currentConnectionChanged(ContextChangedEvent e){
    setConnection(e.getConnection());
  }
  //END ContextChangedListener methods

  // create and show an error dialog
  private void displayError(String title, String msg) {
    ErrorDialog dlg = new ErrorDialog (null, title, true, msg, 
				       (StandardDialogClient) this);
    dlg.show();
  }
}
