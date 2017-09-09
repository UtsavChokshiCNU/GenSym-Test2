/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceCommands.java
 *
 */
package com.gensym.shell.commands;

import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.BorderLayout;
import java.util.Enumeration;
import java.util.Vector;
import javax.swing.JFrame;
import com.gensym.mdi.MDIFrame;
import com.gensym.message.Trace;
import com.gensym.dlg.WarningDialog;
import com.gensym.dlg.SelectionDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.ErrorDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnectionListener;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.ntw.TwConnectionAdapter;
import com.gensym.wksp.WorkspaceView;
import com.gensym.classes.KbWorkspace;
import com.gensym.shell.util.*;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.Command;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.message.Resource;

/**
 *  Command to get a named workspace and create a new kb-workspace.
 *  Get kb-workspace presents the user with a list of the named workspaces
 *  and then downloads the selected workspace.
 *  New kb-workspace creates a permanent unnamed workspace.
 * <p>
 *  This command may be used in MDI and SDI applications, and in
 *  single and multiple connection applications.
 *  In MDI applications, the specified WorkspaceDocumentFactory is used
 *  to create a WorkspaceDocument and then it is added to the MDIManager.
 *  Use setWorkspaceDocumentFactory to change the WorkspaceDocumentFactory
 *  used by this command, and therefore, change the class of WorkspaceDocument
 *  that is created by this command.
 *  In SDI applications, the workspace view is added to the center of
 *  the current frame.
 *  In single connection applications, the application is responible for
 *  updating this command with the current connection via setConnection.
 *  In multiple connection applications, the ConnectionManager is used to obtain
 *  the currentConnection.
 *</p>
 *  @see com.gensym.shell.util.WorkspaceDocumentFactory
 */
public final class WorkspaceCommands extends AbstractCommand{
  /** Command key to get a kb-workspace. */
  public static final String GET_KBWORKSPACE = "GetKbWorkspace";
  /** Command key to create a new kb-workspace */
  public static final String NEW_KBWORKSPACE = "NewKbWorkspace";
  /** A counter to keep track of unnamed workspaces */
  static int counter = 1;
  private static final Symbol KBWORKSPACE_ = Symbol.intern("KB-WORKSPACE");
  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";
  private static Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");
  private Resource shortBundle = Resource.getBundle("com/gensym/shell/commands/CommandShortResource");

  private Frame frame;
  private TwAccess currentConnection;
  private Symbol[] wkspNames;
  private boolean mdi;
  private WorkspaceDocumentFactory factory=new DefaultWorkspaceDocumentFactoryImpl();
  private boolean wkspDocFactorySet = false;

  private ContextChangedListener contextChangedListener;
  private TwConnectionListener twConnectionListener;
  private StandardDialogClient dialogClient;
  private Runnable workspaceChooser;

  /** Creates a WorkspaceCommands for a single connection application. */
  public WorkspaceCommands(Frame frame, TwAccess connection){
    this(frame, (ConnectionManager)null);
    setConnection(connection);
  }

  /** Creates a WorkspaceCommands for a multiple connection application. */
  public WorkspaceCommands(Frame frame, ConnectionManager connectionMgr){
    super(new CommandInformation[]{
      new CommandInformation(NEW_KBWORKSPACE, true, shortResource, longResource,
			     "new_wksp.gif", null, null, true, mnemonicResource, null),
      new CommandInformation(GET_KBWORKSPACE, true, shortResource, longResource,
			     "get_wksp.gif", null, null, false, mnemonicResource, null)});

    this.frame = frame;
    mdi = (frame instanceof MDIFrame);
    dialogClient = new DialogClient();
    workspaceChooser = new WorkspaceChooser();
    twConnectionListener = new ConnectionAdapter();

    if (connectionMgr != null){
      contextChangedListener = new ContextChangedAdapter();
      connectionMgr.addContextChangedListener(contextChangedListener);
      setConnection(connectionMgr.getCurrentConnection());
    }
  }

  /*  Added to fix a bug in T2, when the menu is selected while not connected .
   *  @undocumented
   */
  public void updateAvailability(){
   boolean available = true;
   if ((currentConnection == null) || (!currentConnection.isLoggedIn()))
       available = false;

   // GET_KBWORKSPACE could check for named workspaces
   setAvailable(GET_KBWORKSPACE, available);
   setAvailable(NEW_KBWORKSPACE, available);
  }

  @Override
  protected void setAvailable(String key, boolean available){
    // Added to fix a bug in T2 to be able to control availability of menu
    boolean browserMode = com.gensym.core.GensymApplication.getApplication().isBrowserMode();
    if (NEW_KBWORKSPACE.equals(key) && browserMode)
      available = false;
    super.setAvailable(key, available);
  }

  public static KbWorkspace createNewWorkspace(TwAccess connection) {
    try{
      KbWorkspace newWksp = (KbWorkspace)connection.createItem(KBWORKSPACE_);
      // This forces that all workspaces are named and can easily be located.
      // Otherwise it is too easy to create new blank workspaces that don't have
      // a title, grow the memory and cannot be easily located. We need this for escor/rethink.
      newWksp.setNames(Symbol.intern("UNNAMED-WORKSPACE-"+counter));
      counter = counter + 1;
      newWksp.makePermanent();
      return newWksp;
    }
    catch(G2AccessException ex){
      com.gensym.message.Trace.exception(ex);
      String cxnString = connection.toShortString();
      String msg = ex.getMessage();
      if (msg == null)
	new WarningDialog(null, i18n.getString("Error"), true, i18n.format("UnableToCreateWksp", cxnString), null).setVisible(true);
      else
	new WarningDialog(null, i18n.getString("Error"), true, i18n.format("UnableToCreateWkspWithReason", cxnString, msg), null).setVisible(true);
    }
    return null;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (!isAvailable(cmdKey)) {
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", cmdKey));
    }

    if (cmdKey.equals(GET_KBWORKSPACE))
      new Thread(workspaceChooser).start();
    else if (cmdKey.equals(NEW_KBWORKSPACE)){
      addWorkspace(createNewWorkspace(currentConnection));
    }
  }

  /**
   *  Sets the WorkspaceDocumentFactory that is used to create WorkspaceDocuments.
   *  By default, DefaultWorkspaceDocumentFactoryImpl is used.
   *  This method may only be called once.
   */
  public void setWorkspaceDocumentFactory(WorkspaceDocumentFactory factory){
    if (wkspDocFactorySet)
      throw new Error (i18n.getString("WorkspaceDocumentFactoryAlreadyDefined"));
    else{
      this.factory = factory;
      wkspDocFactorySet = true;
    }
  }

  private void addWorkspace(KbWorkspace wksp){
    if (mdi){
      MDIFrame mdiFrame = (MDIFrame)frame;
      try{
	WorkspaceDocument doc = factory.createWorkspaceDocument(currentConnection,wksp);
	mdiFrame.getManager().addDocument(doc, doc.getPreferredSize());
      }
      catch(G2AccessException ex){
	new com.gensym.dlg.WarningDialog(null, "", true,
					 i18n.format("ErrorDownloadingWksp",
						     new Object[]{ex.toString()}),
					 null).setVisible(true);
      }
    }
    else{
      if (frame instanceof JFrame)
	((JFrame)frame).getContentPane().add(new WorkspaceView(wksp), BorderLayout.CENTER);
      else
	frame.add(new WorkspaceView(wksp), BorderLayout.CENTER);
    }
  }

  /**
   * Sets the current connection.  This command's actions act upon the current
   * connection.
   */
  public void setConnection(TwAccess connection){
    //stop listening to the previous current connection
    if (currentConnection != null)
      currentConnection.removeTwConnectionListener(twConnectionListener);
    //set the current connection
    currentConnection = connection;
    //start listening to the new current connection
    if (currentConnection != null)
      currentConnection.addTwConnectionListener(twConnectionListener);

    boolean available = true;
    if ((currentConnection == null) || (!currentConnection.isLoggedIn()))
	available = false;

    // GET_KBWORKSPACE could check for named workspaces
    setAvailable(GET_KBWORKSPACE, available);
    setAvailable(NEW_KBWORKSPACE, available);
  }

  class WorkspaceDownloader extends Thread {
    private TwAccess cxn;
    private Symbol name_;

    WorkspaceDownloader (TwAccess connection, Symbol wkspName_) {
      super ();
      setName ("Workspace Downloader -> " + wkspName_.getPrintValue () + " [" + hashCode () + "]");
      cxn = connection;
      name_ = wkspName_;
    }

    @Override
    public void run () {
      try{
	KbWorkspace wksp=(KbWorkspace)cxn.getUniqueNamedItem(KBWORKSPACE_, name_);
	addWorkspace(wksp);
      }
      catch(G2AccessException ex){
	com.gensym.message.Trace.exception (ex);
	String msg =  ex.getMessage();
	if (msg == null)
	  new WarningDialog(null, i18n.getString("Error"), true,
			  i18n.format("UnableToDownloadWksp",
				      new Object[] {name_, cxn.toShortString()}),
			  null).setVisible(true);
	else
	  new WarningDialog(null, i18n.getString("Error"), true,
			  i18n.format("UnableToDownloadWkspWithReason",
				      new Object[] {name_, cxn.toShortString(), msg}),
			  null).setVisible(true);
      }
    }
  }

  class ContextChangedAdapter implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      setConnection(e.getConnection());
    }
  }

  class ConnectionAdapter extends TwConnectionAdapter{
    //should only receive events for the current connection
    @Override
    public void loggedIn (TwConnectionEvent evt) {
      //System.out.println("logged in");
      setAvailable(GET_KBWORKSPACE, true);
      setAvailable(NEW_KBWORKSPACE, true);
    }

    @Override
    public void loggedOut (TwConnectionEvent evt) {
      //System.out.println("logged out");
      setAvailable(GET_KBWORKSPACE, false);
      setAvailable(NEW_KBWORKSPACE, false);
    }
  }

  class DialogClient implements StandardDialogClient{
    @Override
    public void dialogDismissed (StandardDialog d, int code) {
      SelectionDialog osd = (SelectionDialog)d;
      Symbol[] listOfWksps   = wkspNames;
      if (osd.wasCancelled ()) return;
      int[] chosenWkspIndices = osd.getResults();
      for (int i=0; i<chosenWkspIndices.length; i++){
	int index = chosenWkspIndices[i];
	Symbol chosenWkspName_ = listOfWksps[index];

	new WorkspaceDownloader (currentConnection, chosenWkspName_).start();
      }
    }
  }

  class WorkspaceChooser implements Runnable{
    @Override
    public void run(){
      if (currentConnection == null)
	throw new IllegalStateException(i18n.getString("NullConnection"));
      try {
	Sequence wksps = currentConnection.getNamedWorkspaces ();
	int len = wksps.size();
	wkspNames = new Symbol[len]; //what if zero?
	wksps.copyInto(wkspNames);
	String[] names = new String[len];
	for (int i=0; i<len; i++)
	  names[i] = wkspNames[i].getPrintValue();
	com.gensym.util.Sorter.sort(names, wkspNames, com.gensym.util.Sorter.ASCENDING);
	new SelectionDialog (null, shortBundle.getString("GetWorkspaceTitle"),
			     true,
			     shortBundle.getString("ChooseNamedWorkspacePrompt"),
			     names, false, -1, true, dialogClient).setVisible (true);
      } catch (G2AccessException ex) {
	String cxnString = currentConnection.toShortString();
	String msg = ex.getMessage();
	if (msg == null)
	  new WarningDialog(null, i18n.getString("Error"), true,
			  i18n.format("UnableToDownloadWkspNames", cxnString),
			  null).setVisible(true);
	else
	  new WarningDialog(null, i18n.getString("Error"), true,
			  i18n.format("UnableToDownloadWkspNamesWithReason",
				      cxnString, msg), null).setVisible(true);
	return;
      } catch (Exception e) {
	Trace.exception (e);
	new ErrorDialog (null, i18n.getString ("Error"), true,
			 i18n.format ("ErrorDownloadingWorkspace",
				      currentConnection.toShortString (),
				      e.toString ()),
			 null).setVisible (true);
      }
    }
  }

}



