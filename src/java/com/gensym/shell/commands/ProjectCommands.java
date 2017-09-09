/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ProjectCommands.java
 *
 */
package com.gensym.shell.commands;

import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.io.FileNotFoundException;

import com.gensym.classes.Kb;
import com.gensym.classes.Module;
import com.gensym.dlg.CommandConstants;
import com.gensym.dlg.ErrorDialog;
import com.gensym.dlg.InputDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.KbEvent;
import com.gensym.ntw.util.KbModuleListener;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.shell.dialogs.OpenProjectDialog;
import com.gensym.shell.dialogs.ProjectPromptDialog;
import com.gensym.shell.dialogs.SaveProjectDialog;
import com.gensym.ntw.util.LoadSaveKBTools;
import com.gensym.util.G2ConnectionTable;
import com.gensym.util.Symbol;
import com.gensym.files.*;
import com.gensym.ntw.files.*;
import com.gensym.ntw.util.FileProgressDisplay;
import com.gensym.util.Sequence;
import java.util.Hashtable;
import java.awt.Cursor;
import javax.swing.KeyStroke;
import java.awt.Event;
import java.awt.event.KeyEvent;
import com.gensym.util.Structure;

public final class ProjectCommands extends AbstractStructuredCommand {
  /** Command key to create a new "project" */
  public static final String NEW_PROJECT = "NewProject";
  /** Command key to open an existing "project" */
  public static final String OPEN_PROJECT = "OpenProject";
  /** Command key to close the current "project" */
  public static final String CLOSE_PROJECT = "CloseProject";

 /** Command key to save the current "project" to the specified file location */
  public static final String SAVE_PROJECT = "SaveProject";
  /** Command key to launch a Save dialog for specifying a path for saving the current "project" */
  public static final String SAVE_PROJECT_AS = "SaveProjectAs";
  /** Command key to save the current "project" as an ALL file */
  public static final String SAVE_PROJECT_AS_ALL_FILE = "SaveProjectAsAllFile";

  private static final String shortResource = "LayoutCommandShortResource";
  private static final String longResource = "LayoutCommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";      

  //private static Resource shortBundle = Resource.getBundle("com/gensym/shell/commands/CommandShortResource");
  private static Resource i18n = Resource.getBundle("com/gensym/shell/commands/Messages");

  private String PROJECT_NOUN = i18n.getString("ProjectNoun");
  private StandardDialogClient dialogClient;

  private Frame frame;
  private TwAccess currentConnection;

  private ConnectionManager cxnMgr;
  private ContextChangedListener contextListener;

  private G2ConnectionTable openDialogTable;
  private G2ConnectionTable saveDialogTable;
  private OpenProjectDialog openDialog;
  private SaveProjectDialog saveDialog;

  private DialogClient defaultDialogClient;
  private KbModuleAdapter kbModuleAdapter;
  private FileProgressDisplay fileProgressDisplay;

  private CxnAdapter cxnAdapter;

  public ProjectCommands(Frame frame, ConnectionManager connectionManager) {
    this(frame, connectionManager.getCurrentConnection());
    cxnMgr = connectionManager;
    cxnMgr.addContextChangedListener(contextListener = new ContextChangedAdapter());
    openDialogTable = new G2ConnectionTable();
    saveDialogTable = new G2ConnectionTable();
  }

  public ProjectCommands(Frame frame, ConnectionManager connectionManager, StandardDialogClient client) {
    this(frame, connectionManager.getCurrentConnection(), client);
    cxnMgr = connectionManager;
    cxnMgr.addContextChangedListener(contextListener = new ContextChangedAdapter());
    openDialogTable = new G2ConnectionTable();
    saveDialogTable = new G2ConnectionTable();
  }

  public ProjectCommands(Frame frame, TwAccess connection) {
    this(frame, connection, (StandardDialogClient) null);
  }

  public ProjectCommands(Frame frame, TwAccess connection, StandardDialogClient client) {
    super(new StructuredCommandInformation[]{
      new CommandGroupInformation("OpenGroup", new CommandInformation[]{
	new CommandInformation(NEW_PROJECT, true, shortResource, longResource,
			       "new.gif", null, null, true,
			       mnemonicResource,
			       KeyStroke.getKeyStroke('N', Event.CTRL_MASK)),
	  new CommandInformation(OPEN_PROJECT, true, shortResource, longResource,
				 "open.gif", null, null, false,
				 mnemonicResource,
				 KeyStroke.getKeyStroke('O', Event.CTRL_MASK)),
	  new CommandInformation(CLOSE_PROJECT, true, shortResource, longResource,
				 "close.gif", null, null, true,
				 mnemonicResource, null)}),
	new CommandGroupInformation("SaveGroup", new CommandInformation[]{
	  new CommandInformation(SAVE_PROJECT, true, shortResource, longResource,
				 "save.gif", null, null, true,
				 mnemonicResource,
				 KeyStroke.getKeyStroke('S', Event.CTRL_MASK)),
	    new CommandInformation(SAVE_PROJECT_AS, true, shortResource, longResource,
				   null, null, null, false,
				   mnemonicResource, null),
	    new CommandInformation(SAVE_PROJECT_AS_ALL_FILE, true, shortResource, longResource,
				   "save_all.gif", null, null, true,
				   mnemonicResource, null)})});
    
    this.frame = frame;
    fileProgressDisplay = new FileProgressDisplay(frame);
    kbModuleAdapter = new KbModuleAdapter();
    setConnection(connection);

    if (client == null) {
      defaultDialogClient = new DialogClient();
      dialogClient = defaultDialogClient;
    } else {
      dialogClient = client;
    }

    G2ConnectionRootFile.setServerFileSystemVisible(true);
    G2ConnectionRootFile.setMediaBinsVisible(false);

    cxnAdapter = new CxnAdapter();
  }

  public void setResource(Resource resource) {
    i18n = resource;
  }

  public void setProjectNoun(String noun) {
    PROJECT_NOUN = noun;
  }

  public void setConnection(TwAccess cxn) {
    if (currentConnection != null) {
      try {
	currentConnection.removeFileProgressListener(fileProgressDisplay);
	Kb kb = currentConnection.getKb();
	if (kb != null)
	  kb.removeKbModuleListener(kbModuleAdapter);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    if (currentConnection != null)
      currentConnection.removeG2ConnectionListener(cxnAdapter);
    currentConnection = cxn;
    if (currentConnection == null && openDialog != null)
      openDialog.setVisible(false);
    if (cxn != null)
      currentConnection.addG2ConnectionListener(cxnAdapter);

    if (currentConnection != null && currentConnection.isAlive()) {
      try {
	currentConnection.addFileProgressListener(fileProgressDisplay);
	Kb kb = currentConnection.getKb();
	if (kb != null)
	  kb.addKbModuleListener(kbModuleAdapter);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    setAvailability();
  }

  private void setAvailability() {
    setAvailable(NEW_PROJECT, (!(currentConnection == null)));
    setAvailable(OPEN_PROJECT, (!(currentConnection == null)));
    setAvailable(CLOSE_PROJECT, (!(currentConnection == null)));
    setAvailable(SAVE_PROJECT, (currentConnection != null));
    setAvailable(SAVE_PROJECT_AS, (currentConnection != null));
    setAvailable(SAVE_PROJECT_AS_ALL_FILE, (currentConnection != null));
  }

  @Override
  protected void setAvailable(String key, boolean status) {
    super.setAvailable(key, status);
  }
  
  private static String getFilePath(Module mod) {
    String g2Path = "";
    try {
      Structure path = (Structure)((com.gensym.classes.G2__BaseImpl)mod.getSavingParameters()).
	getAttributeTexts(CURRENT_FILE_FOR_MODULE_ATTRIBUTES);
      g2Path = (String)path.getAttributeValue(FILENAME_OF_BASIS_KB_, "");
      if ("none".equals(g2Path.toLowerCase()))
	g2Path = "";
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    return g2Path;
  }
  
  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();

    TwAccess cxn = cxnMgr == null ? currentConnection : cxnMgr.getCurrentConnection();
    Kb kb = cxn.getKb();
    
    if (cmdKey.equals(NEW_PROJECT)) {
      handleNewProjectCommand();
    }
    else if (cmdKey.equals(OPEN_PROJECT)) {
      OpenDialogInfo info = getOpenInfo(cxn);
      if (info.g2Path == null) {
	if (kb != null) {
	  try {
	    Module mod = kb.getTopLevelModule();
	    info.g2Path = getFilePath(mod);
	  } catch (G2AccessException g2ae) {
	    Trace.exception(g2ae);
	     info.g2Path = "";
	  }
	}
      }
      openDialog = getOpenDialog();
      G2ConnectionInfo currentCxnInfo = registerCurrentConnection();
      openDialog.setVisible(true);
      G2File.deregisterG2ConnectionInfo(currentCxnInfo);
    }
    else if (cmdKey.equals(CLOSE_PROJECT)) {
      handleCloseProjectCommand();
    }
    else {
      try {
	if (kb != null) {
	  Module mod = kb.getTopLevelModule();
  
	  if (cmdKey.equals(SAVE_PROJECT)) {
	    SaveDialogInfo info = getSaveInfo(cxn);
	    if (info.g2Path != null && !info.g2Path.equals(""))
	      (new SaveThread(cxn,
			      mod.getName(),
			      info.g2Path, false)).start();
	    else {
	      info.g2Path = getFilePath(mod);
	      SaveProjectDialog saveDialog = getSaveDialog(mod);
	      saveDialog.setAllFile(false);
	      G2ConnectionInfo currentCxnInfo = registerCurrentConnection();
	      saveDialog.setVisible(true);
	      if (saveDialog.wasCancelled())
		info.g2Path = null;
	      G2File.deregisterG2ConnectionInfo(currentCxnInfo);	      
	    }
	  }
	  else if (cmdKey.equals(SAVE_PROJECT_AS)||
		   cmdKey.equals(SAVE_PROJECT_AS_ALL_FILE)) {
	    SaveDialogInfo info = getSaveInfo(cxn);
	    if (info.g2Path == null || info.g2Path.equals(""))
	      info.g2Path = getFilePath(mod);
	    SaveProjectDialog saveDialog = getSaveDialog(mod);
	    saveDialog.setAllFile(cmdKey.equals(SAVE_PROJECT_AS_ALL_FILE));
	    G2ConnectionInfo currentCxnInfo = registerCurrentConnection();
	    saveDialog.setVisible(true);
	    G2File.deregisterG2ConnectionInfo(currentCxnInfo);	      
	  }
	}
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	if (gae.getMessage() != null) {
	  String title =  i18n.getString("SaveProjectError") + PROJECT_NOUN;
	  if (gae.getMessage() != null)
	    new ErrorDialog(null, title, true, gae.getMessage(), null).setVisible(true);
	}
      }
    }
  }

  private OpenProjectDialog getOpenDialog(){
    if (openDialog == null){
      String title = i18n.getString("OpenProjectDialogTitle") + " " + PROJECT_NOUN;
      openDialog = new OpenProjectDialog(frame, title, true, true,  currentConnection, dialogClient);
    }

    TwAccess cxn = cxnMgr == null ? currentConnection : cxnMgr.getCurrentConnection();
    openDialog.setConnection(cxn);
    OpenDialogInfo info = getOpenInfo(cxn);
    openDialog.setG2FileSpecification(info.g2Path);
    openDialog.setURLFile(info.urlFile);
    openDialog.setAutomaticallyResolveConflicts(info.autoResolve);
    openDialog.setBringFormatsUpToDate(info.bringFormatsUpToDate);

    return openDialog;
  }

  private OpenDialogInfo getOpenInfo(TwAccess cxn) {
    OpenDialogInfo info = (OpenDialogInfo)openDialogTable.get(cxn);
    if (info == null) {
      info = new OpenDialogInfo();
      openDialogTable.put(cxn, info);
    }
    return info;
  }
  private void updateOpenInfo(String g2Path){
    TwAccess cxn = cxnMgr == null ? currentConnection : cxnMgr.getCurrentConnection();
    OpenDialogInfo info = getOpenInfo(cxn);
    if (g2Path == null) {
      info.g2Path = openDialog.getG2FileSpecification();
      info.urlFile = openDialog.getURLFile();
      info.autoResolve = openDialog.getAutomaticallyResolveConflicts();
      info.bringFormatsUpToDate = openDialog.getBringFormatsUpToDate();
    } else {
      info.g2Path = g2Path;
    }
  }

  private static final String saveTitle=i18n.getString("SaveProjectDialogTitle");
  private static final Symbol FILENAME_OF_BASIS_KB_ = Symbol.intern ("FILENAME-OF-BASIS-KB");
  private static Sequence CURRENT_FILE_FOR_MODULE_ATTRIBUTES = new Sequence();
  static {
    CURRENT_FILE_FOR_MODULE_ATTRIBUTES.addElement(FILENAME_OF_BASIS_KB_);
  }
  private SaveProjectDialog getSaveDialog(Module mod){
    String title = saveTitle + " " + PROJECT_NOUN+": ";
    Symbol moduleName = mod.getName();
    if (moduleName != null)
      title+=moduleName.toString();
    else
      title+="(Unamed Module)";    
    if (saveDialog == null){      

      saveDialog = new SaveProjectDialog(frame,title, true, true, 
					 currentConnection, dialogClient);
    }
    saveDialog.setTitle(title);
    TwAccess cxn = cxnMgr == null ? currentConnection : cxnMgr.getCurrentConnection();
    SaveDialogInfo info = getSaveInfo(cxn);
    saveDialog.setConnection(cxn);
    saveDialog.setG2FileSpecification(info.g2Path);
    saveDialog.setURLFile(info.urlFile);
    saveDialog.setShowProgress(info.showProgress);
    saveDialog.setSaveWorkspaceLayout(info.saveWorkspaceLayout);
    saveDialog.setSaveRequiredModules(info.saveRequiredModules);
 
    return saveDialog;
  }

  private SaveDialogInfo getSaveInfo(TwAccess cxn) {
    SaveDialogInfo info = (SaveDialogInfo)saveDialogTable.get(cxn);
    if (info == null){
      info = new SaveDialogInfo();
      saveDialogTable.put(cxn, info);
    }
    return info;
  }
  
  private SaveDialogInfo updateSaveInfo(String g2Path){
    TwAccess cxn = cxnMgr == null ? currentConnection : cxnMgr.getCurrentConnection();
    SaveDialogInfo info = getSaveInfo(cxn);
    if (g2Path == null) {
      info.g2Path = saveDialog.getG2FileSpecification();
      info.urlFile = saveDialog.getURLFile();
      info.showProgress = saveDialog.getShowProgress();
      info.saveWorkspaceLayout = saveDialog.getSaveWorkspaceLayout();
      info.saveRequiredModules = saveDialog.getSaveRequiredModules();
    } else {
      info.g2Path = g2Path;
    }
    return info;
  }

  private G2ConnectionInfo registerCurrentConnection(){
    G2ConnectionInfo currentCxnInfo = null;
    try{
      currentCxnInfo = new G2ConnectionInfo(currentConnection.g2GetHostName(), currentConnection.g2GetPortNumberOrName());
      G2File.registerG2ConnectionInfo(currentCxnInfo);	
    }
    catch(G2AccessException ex){
      Trace.exception(ex);
    }
    return currentCxnInfo;
  }
  
  private void handleNewProjectCommand() {
    // if a top-level-module exists, prompt to save it before creating a new one
    try {
      Kb kb = currentConnection.getKb();
      if (kb != null) {
	Module toplevelModule = kb.getTopLevelModule();

	// if top-level-module exists, prompt for saving current model
	if (toplevelModule != null) {
	  String moduleName = i18n.getString("Unspecified");
	  Symbol name_ = toplevelModule.getName();
	  if (name_ != null) {
	    moduleName = name_.toString();
	    String title = i18n.getString("SaveProjectPrompt") + " " + PROJECT_NOUN;
	    String msg = i18n.getString("SaveProjectMessage")+" "+moduleName+"?";
	    new ProjectPromptDialog(frame, title, true, msg,
				    ProjectPromptDialog.NEW_PROJECT_, dialogClient).setVisible(true);
	  } else
	    executeNewProject();
	} else
	  executeNewProject();
      }
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }

  private void executeNewProject() {
    // launch "New Project" dialog, use InputDialog for now  
    String[] labels = {i18n.getString("NewProjectNameLabel")};
    String[] initialValues = {i18n.getString("Unspecified")};
    new InputDialog(frame, i18n.getString("NewProjectDialogTitle")+" "+PROJECT_NOUN, true,
		    labels, initialValues,
		    dialogClient).setVisible(true);
  }
 
  private void executeNewProjectInternals(String result) {
    /*
     * do a clear-kb
     */
    System.out.println("New Project is NYI");
  }

  private void handleCloseProjectCommand() {
    // prompt to save current project before it closing it
    try {
      Kb kb = currentConnection.getKb();
      if (kb != null) {
	Module toplevelModule = kb.getTopLevelModule();

	if (toplevelModule != null) {
	  String moduleName = i18n.getString("Unspecified");
	  Symbol name_ = toplevelModule.getName();
	  if (name_ != null) {
	    moduleName = name_.toString();
	    String title =  i18n.getString("SaveProjectPrompt")+" "+PROJECT_NOUN;
	    String msg = i18n.getString("SaveProjectMessage")+" "+moduleName+"?";
	    new ProjectPromptDialog(frame, title, true, msg,
				    ProjectPromptDialog.CLOSE_PROJECT_, dialogClient).setVisible(true);
	  } else
	    executeCloseProject();
	} else
	  executeCloseProject();
      }
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }

  private static final Symbol G2_CLEAR_KB_ = Symbol.intern ("G2-CLEAR-KB");    
  private void executeCloseProject() {
    try {
      if (currentConnection != null) {
	//RPC NEW IN G26.0 
	currentConnection.callRPC(G2_CLEAR_KB_, new Object[] {});
	SaveDialogInfo info = getSaveInfo(currentConnection);
	info.g2Path = null;
      }
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }    
  }

  private void handleOpenProjectDialogDismiss(OpenProjectDialog dlg) {
    updateOpenInfo(null);
    
    LoadSaveKBTools.setResolveConflicts(new Boolean(dlg.getAutomaticallyResolveConflicts()));
    LoadSaveKBTools.setBringFormatsUpToDate(new Boolean(dlg.getBringFormatsUpToDate()));
    String file = dlg.getG2FileSpecification();
    (new LoadThread(currentConnection, file)).start();
    updateSaveInfo(file);    
  }

  class DialogClient implements StandardDialogClient, CommandConstants {
    @Override
    public void dialogDismissed(StandardDialog dlg, int code) {
      if (dlg.wasCancelled()) return;

      if (dlg instanceof OpenProjectDialog) {
	handleOpenProjectDialogDismiss((OpenProjectDialog)dlg);
      }

      else if (dlg instanceof ProjectPromptDialog) {
	if (code == YES) {
	  try {
	    Kb kb = currentConnection.getKb();
	    if (kb != null) 
	      getSaveDialog(kb.getTopLevelModule()).setVisible(true);
	  } catch (G2AccessException g2ae) {
	    Trace.exception(g2ae);
	  }
	}
	Symbol reasonForPrompt = ((ProjectPromptDialog)dlg).getReasonForPrompt();
	if (reasonForPrompt.equals(ProjectPromptDialog.NEW_PROJECT_))
	  executeNewProject();
	else if (reasonForPrompt.equals(ProjectPromptDialog.CLOSE_PROJECT_))
	  executeCloseProject();
      }

      else if (dlg instanceof InputDialog) {
	// currenty, the only one is for "New Project". if more, than we need to subclass
	String[] result = ((InputDialog)dlg).getResults();
	executeNewProjectInternals(result[0]);
      }
      else if (dlg instanceof SaveProjectDialog) {
	try {
	  updateSaveInfo(null);
	  SaveProjectDialog spd = (SaveProjectDialog)dlg;
	  LoadSaveKBTools.setShowProgress(new Boolean(spd.getShowProgress()));
	  LoadSaveKBTools.setSaveWorkspaceLayout(new Boolean(spd.getSaveWorkspaceLayout()));
	  LoadSaveKBTools.setSaveRequiredModules(new Boolean(spd.getSaveRequiredModules()));
	  String g2Path = spd.getG2FileSpecification();
	  (new SaveThread(currentConnection,
			 currentConnection.getKb().getTopLevelModule().getName(),
			 g2Path,
			 spd.isAllFile())).start();
	  updateOpenInfo(g2Path);
	} catch (G2AccessException gae) {
	  fileProgressDisplay.displaySingleMessage(gae.toString()); 
	  Trace.exception(gae);
	  if (gae.getMessage() != null)
	    new ErrorDialog(null, i18n.getString("SaveProjectError")+" "+PROJECT_NOUN, true, gae.getMessage(), null).setVisible(true);
	} 
      }
    }
  }

  class LoadThread extends Thread {
    private TwAccess connection;
    private String file;
    LoadThread(TwAccess connection, String file) {
      fileProgressDisplay.setTitle("Loading " + file);
      fileProgressDisplay.clear();      
      fileProgressDisplay.setPrefix("Loading");
      fileProgressDisplay.displaySingleMessage("Preparing to load ... please wait");
      fileProgressDisplay.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
      this.connection = connection;
      this.file = file;
    }
    @Override
    public void run() {
      try {
	LoadSaveKBTools.loadKB(connection, file);
      } catch (G2AccessException gae) {
	if (gae.getMessage() != null) 
	  new ErrorDialog(null, i18n.getString("OpenProjectError")+" "+
			  PROJECT_NOUN, true, 
			  gae.getMessage(), null).setVisible(true);
	else
	  Trace.exception(gae);
      } catch (FileNotFoundException fnfe) {
	fileProgressDisplay.setVisible(false);
	Trace.exception(fnfe);
	new ErrorDialog(null, i18n.getString("FileNotFoundError"), true, 
			fnfe.getMessage(), null).setVisible(true);
      }      
    }
  }

  private static final Symbol NO_MODULE = Symbol.intern ("NO-MODULE");
  class SaveThread extends Thread {
    private TwAccess connection;
    private Symbol moduleName;
    private String path;
    private boolean allFile;
    SaveThread(TwAccess connection, Symbol moduleName, String path, boolean allFile) {
      if (moduleName == null) {
	//moduleName = NO_MODULE;
      }
      fileProgressDisplay.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
      fileProgressDisplay.setTitle("Saving " + path);
      fileProgressDisplay.clear();      
      fileProgressDisplay.setPrefix("Saving");
      fileProgressDisplay.displaySingleMessage("Preparing to save ... please wait"); 
      this.connection = connection;
      this.moduleName = moduleName;
      this.path = path;
      this.allFile = allFile;
    }
    @Override
    public void run() {
      try {
	Sequence error = null;
	if (allFile) {
	  Boolean ok = LoadSaveKBTools.saveKB(connection,path);
	  if (!ok.booleanValue()) {
	    error = new Sequence();
	    error.addElement("Problems saving as all file ");
	  }
	} else
	  error = LoadSaveKBTools.saveModule(connection, moduleName,path);
	if (error != null)
	  fileProgressDisplay.displaySingleMessage(error.elementAt(0)+" "+error.elementAt(1));
      } catch (G2AccessException g2ae) {
	fileProgressDisplay.displaySingleMessage(g2ae.getMessage()); 
      }
    }
  }
  
  class KbModuleAdapter implements KbModuleListener {
    @Override
    public void receivedInitialModules (KbEvent e) {
      setAvailability();
    }
    @Override
    public void moduleDeleted (KbEvent e) {
      setAvailability();
    }
    @Override
    public void kbCleared (KbEvent e) {
      setAvailability();
    }
    @Override
    public void moduleNameChanged (KbEvent e) {
      setAvailability();
    }
    @Override
    public void moduleCreated (KbEvent e) {
      setAvailability();
    }

    @Override
    public void moduleDependencyChanged (KbEvent e) {}
    @Override
    public void topLevelWorkspaceAdded (KbEvent e) {}
    @Override
    public void topLevelWorkspaceDeleted (KbEvent e) {}
  }

  class ContextChangedAdapter implements ContextChangedListener {
    @Override
    public void currentConnectionChanged(ContextChangedEvent e) {
      TwAccess connection = e.getConnection();
      if ((connection == null) || (e.isConnectionNew()))
	setConnection(connection);
    }
  }

  class DialogInfo{
    String g2Path;
    URLFile urlFile;
  }

  class SaveDialogInfo extends DialogInfo{
    boolean showProgress = true;
    boolean saveWorkspaceLayout = true;
    boolean saveRequiredModules = false;
  }

  class OpenDialogInfo extends DialogInfo{
    boolean autoResolve = true;
    boolean bringFormatsUpToDate = false;
  }

  class CxnAdapter extends G2ConnectionAdapter {
    private void setCommandsAvailable(boolean avail) {
      setAvailable(NEW_PROJECT, avail);
      setAvailable(OPEN_PROJECT, avail);
      setAvailable(CLOSE_PROJECT, avail);
    }
    @Override
    public void g2IsPaused(G2ConnectionEvent e) {
      setCommandsAvailable(true);
    }
    @Override
    public void g2IsReset(G2ConnectionEvent e) {
      setCommandsAvailable(true);
    }
    @Override
    public void g2IsResumed(G2ConnectionEvent e) {
      setCommandsAvailable(false);
    }
    @Override
    public void g2IsStarted(G2ConnectionEvent e) {
      setCommandsAvailable(false);
    }
  }
}





