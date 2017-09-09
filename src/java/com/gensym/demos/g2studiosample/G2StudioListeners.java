package com.gensym.demos.g2studiosample;

import java.util.Hashtable;
import java.awt.Component;
import java.awt.Frame;
import java.awt.Toolkit;
import java.awt.Image;
import com.gensym.message.Trace;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.message.Resource;
import com.gensym.mdi.MDIFrame;
import com.gensym.uitools.utils.StatusBar;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2CommunicationErrorEvent;
import com.gensym.classes.Kb;
import com.gensym.classes.Module;
import com.gensym.classes.ModuleInformation;
import com.gensym.dlg.ErrorDialog;
import com.gensym.wksp.WorkspaceElement;
import com.gensym.wksp.WorkspaceView;
import com.gensym.wksp.ItemView;
import com.gensym.ntw.TwConnectionListener;
import com.gensym.ntw.TwConnectionAdapter;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.KbEvent;
import com.gensym.ntw.util.KbModuleListener;
import com.gensym.ntw.util.UnsolicitedDialogListener;
import com.gensym.ntw.util.UnsolicitedDialogEvent;
import com.gensym.ntw.util.UnsolicitedDialog;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.MDIFrameWorkspaceSelectionAdapter;
import com.gensym.shell.util.TW2MDIWorkspaceShowingAdapter;
import com.gensym.shell.util.WorkspaceDocumentFactory;

class G2StudioListeners 
implements TwConnectionListener, SelectionListener,
  KbModuleListener, UnsolicitedDialogListener, ContextChangedListener
{
  private static final Symbol
    PROCEDURE_INVOCATION_HIERARCHY_ = Symbol.intern ("PROCEDURE-INVOCATION-HIERARCHY"),
    TEXT_EDITOR_ = Symbol.intern ("TEXT-EDITOR"),
    RECOMPILE_ = Symbol.intern ("RECOMPILE"),
    INSPECT_SESSION_ID_ = Symbol.intern ("INSPECT-SESSION-ID"),
    INSTALL_MODULE_PLUGIN_ = Symbol.intern ("INSTALL-MODULE-PLUGIN"),
    REGISTER_MODULE_ = Symbol.intern ("REGISTER-MODULE"),
    TYPE_ = Symbol.intern ("TYPE"),
    VALUE_ = Symbol.intern ("VALUE"),
    UPDATE_TYPE_ = Symbol.intern ("UPDATE-TYPE"),
    UPDATE_INFO_ = Symbol.intern ("UPDATE-INFO"),
    STATUS_UPDATE_ = Symbol.intern ("STATUS-UPDATE"),
    BUTTON_UPDATE_ = Symbol.intern ("BUTTON-UPDATE");
  private static final Resource i18ui = Resource.getBundle ("com/gensym/demos/g2studiosample/UiLabels");  
  private static String defaultTitle = i18ui.getString("title");
  private Hashtable dialogs = new Hashtable();    
  private Shell application;
  private TwAccess currentConnection;
  private G2StudioPropertiesPanel propertiesPanel;
  private PalettePanel palettePanel;
  private static final String compileImageResource = "/com/gensym/demos/g2studiosample/compile.gif";  
  private static Image compileImage
  = Toolkit.getDefaultToolkit().getImage(G2StudioListeners.class.getResource(compileImageResource));
  private G2StudioCommands studioCommands;
  private G2StudioIconicStatusBar iconicStatusBar;
  
  G2StudioListeners(Shell application,
		    G2StudioPropertiesPanel propertiesPanel,
		    PalettePanel palettePanel,
		    G2StudioCommands studioCommands,
		    G2StudioIconicStatusBar iconicStatusBar) {
    this.palettePanel = palettePanel;
    this.iconicStatusBar = iconicStatusBar;
    this.propertiesPanel = propertiesPanel;
    this.studioCommands = studioCommands;
    this.application = application;
    MDIFrame currentFrame = (MDIFrame)application.getCurrentFrame();
    ConnectionManager connectionManager = application.getConnectionManager();
    connectionManager.addContextChangedListener(this);    
    new MDIFrameWorkspaceSelectionAdapter(currentFrame).addSelectionListener(this);
    WorkspaceDocumentFactory shellWkspDocFactory = new ShellWorkspaceDocumentFactoryImpl(application);
    studioCommands.getWorkspaceCommands().setWorkspaceDocumentFactory(shellWkspDocFactory);
    try {
      TW2MDIWorkspaceShowingAdapter showingAdapter = new TW2MDIWorkspaceShowingAdapter(connectionManager);
      showingAdapter.setWorkspaceDocumentFactory(shellWkspDocFactory);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }
  
  void updateConnection(TwAccess cxn) {
    application.updateMenusForConnection(cxn, false);
    application.updateToolBarsForConnection(cxn, false);    
    if (currentConnection != null) {
      try {
	Kb kb = currentConnection.getKb();
	if (kb != null)
	  kb.removeKbModuleListener(this);
	palettePanel.setPalettePane(null);
	currentConnection.removeTwConnectionListener(this);
	currentConnection.removeUnsolicitedDialogListener(this);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }
    currentConnection = cxn;
    if (currentConnection != null && currentConnection.isAlive()) {
      if (currentConnection.getG2Version().getMajorVersion() < 6) {
	currentConnection.closeConnection();
	new ErrorDialog((Frame)application.getCurrentFrame(), i18ui.getString("g2VersionError"), false, i18ui.getString("g2VersionErrorMsg"), null).setVisible(true);
      } else {
	try {
	  palettePanel.setPalettePane(studioCommands.getPaletteCommands().getPalettePane(currentConnection));
	  Kb kb = currentConnection.getKb();
	  if (kb != null)
	    kb.addKbModuleListener(this);	
	  currentConnection.addTwConnectionListener(this);
	  currentConnection.addUnsolicitedDialogListener(this);
	} catch (G2AccessException gae) {
	  Trace.exception(gae);
	}
      }
    } 
    setTitleBar(currentConnection);    
  }

  private void setTitleBar(TwAccess cxn) {
    Frame f = application.getCurrentFrame();
    String title = defaultTitle;
    if (cxn != null) {
      try {
	Kb kb = cxn.getKb();
	if (kb != null) {
	  Module module = kb.getTopLevelModule();
	  Symbol modName = null;
	  if (module != null)
	    modName = module.getName();
	  if (modName != null)
	    title=title+" -- " + modName.prettyName();
	}
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }
    f.setTitle(title);
  }       

  private void updatePropertiesPanel(WorkspaceView view) {
    if (view == null) {
      propertiesPanel.setItemView(null);
      return;
    }
    WorkspaceElement[] selection = view.getSelection();
    Component dialog = null;
    ItemView itemView = null;
    int selectionCount = selection.length;
    if (selectionCount == 0)
      itemView = view;
    else if (selectionCount == 1) 
      itemView = selection[0];
    else {
      //merge tables
    }
    propertiesPanel.setItemView(itemView);
  }
  
  @Override
  public void selectionChanged(SelectionEvent event){
    WorkspaceView view = null;
    Object source = event.getSource();
    if (source instanceof WorkspaceView) 
      view = (WorkspaceView)source;
    updatePropertiesPanel(view);
    if (view != null)
      iconicStatusBar.updateIcons(view.getSelection());
  }

  @Override
  public void loggedOut(TwConnectionEvent e){
    if (currentConnection == e.getSource()) {
      ((TwAccess)e.getSource()).removeTwConnectionListener(this);
      Frame f = application.getCurrentFrame();
      f.setTitle(i18ui.getString ("title"));
    }
  }  

  private static java.lang.reflect.Method installModulePluginMethod;
  static {
    try {
      installModulePluginMethod = 
	Shell.class.getMethod("installModulePlugin", new Class[] {String.class, Integer.TYPE});
    } catch (NoSuchMethodException nsme) {
      Trace.exception(nsme);
    }
  }  

  private static java.lang.reflect.Method registerModuleMethod;
  static {
    try {
      registerModuleMethod =
	Shell.class.getMethod("registerModule",new Class[] {ModuleInformation.class, String.class});
    } catch (NoSuchMethodException nsme) {
      Trace.exception(nsme);
    }
  }
  
  @Override
  public void currentConnectionChanged(ContextChangedEvent e) {
    TwAccess connection = e.getConnection();
    if (e.isConnectionNew()) {
      connection.registerJavaMethod (application,
				     registerModuleMethod,
				     REGISTER_MODULE_,
				     false);
      connection.registerJavaMethod (application,
				     installModulePluginMethod,
				     INSTALL_MODULE_PLUGIN_,
				     false);
    }
    updateConnection(connection);
  }
  
  @Override
  public void receivedInitialModules (KbEvent evt) {}
  @Override
  public void moduleCreated (KbEvent evt){
    new Thread(new Runnable() {
      @Override
      public void run() {
	setTitleBar(currentConnection);
      }
    }).start();
  }
  @Override
  public void moduleDeleted (KbEvent evt) {
    new Thread(new Runnable() {
      @Override
      public void run() {
	setTitleBar(currentConnection);
      }
    }).start();    
  }
  @Override
  public void moduleNameChanged (KbEvent evt) {
    new Thread(new Runnable() {
      @Override
      public void run() {
	setTitleBar(currentConnection);
      }
    }).start();        
  }
  @Override
  public void moduleDependencyChanged (KbEvent evt){}
  @Override
  public void kbCleared (KbEvent evt) {
    new Thread(new Runnable() {
      @Override
      public void run() {
	setTitleBar(currentConnection);
      }
    }).start();        
  }
  @Override
  public void topLevelWorkspaceAdded(KbEvent evt){}
  @Override
  public void topLevelWorkspaceDeleted(KbEvent evt){}


  @Override
  public void enterDialog(UnsolicitedDialogEvent evt) {
    Symbol dialogName = evt.getDialogName();
    if (PROCEDURE_INVOCATION_HIERARCHY_.equals(dialogName)) {
    } else if (TEXT_EDITOR_.equals(dialogName)) {
    } else if (RECOMPILE_.equals(dialogName)) {
      UnsolicitedDialog dialog = UnsolicitedDialog.createDialog(application.getCurrentFrame(),
								evt,
								new StatusBar(3));
      
      dialog.setImage(compileImage);
      dialogs.put(new Integer(dialog.getID()), dialog);
      (new Thread(new DialogShower(dialog))).start();
    } else {
      UnsolicitedDialog dialog = UnsolicitedDialog.createDialog(application.getCurrentFrame(), evt, null);
      dialogs.put(new Integer(dialog.getID()), dialog);
      (new Thread(new DialogShower(dialog))).start();
    }
  }

  @Override
  public void updateDialog(UnsolicitedDialogEvent evt) {
    Integer id = new Integer(evt.getDialogID());
    UnsolicitedDialog dlg = (UnsolicitedDialog)dialogs.get(id);
    if (dlg != null) {
      Sequence sequenceInfo = (Sequence) evt.getDialogInfo();
      Structure updateInfo = (Structure)sequenceInfo.elementAt(0);
      Symbol updateType = (Symbol)updateInfo.getAttributeValue(UPDATE_TYPE_,null);
      Sequence info = (Sequence)updateInfo.getAttributeValue(UPDATE_INFO_,null);      
      if (STATUS_UPDATE_.equals(updateType)) {
	dlg.setStatus("Status: " +info.elementAt(0), 0);//i18n
	dlg.setStatus("Examined " + info.elementAt(2)+" of "+info.elementAt(1), 1);//i18n
	dlg.setStatus("Found " + info.elementAt(3), 2);//i18n
      } else if (BUTTON_UPDATE_.equals(updateType)) {
	Symbol oldButtonName = (Symbol)info.elementAt(0);
	String newButtonLabel = (String)info.elementAt(1);
	Symbol newButtonName = (Symbol)info.elementAt(2);	
	dlg.updateButton(oldButtonName, newButtonLabel, newButtonName);
      }
    }
  }
  
  @Override
  public void exitDialog(UnsolicitedDialogEvent evt) {
    Integer id = new Integer(evt.getDialogID());
    UnsolicitedDialog dlg = (UnsolicitedDialog)dialogs.get(id);
    if (dlg != null) {
      dialogs.remove(id);
      dlg.dispose ();          
    }
  }
  @Override
  public void g2IsPaused (G2ConnectionEvent event) {}
  @Override
  public void g2IsResumed (G2ConnectionEvent event) {}
  @Override
  public void g2IsReset (G2ConnectionEvent event) {}
  @Override
  public void g2IsStarted (G2ConnectionEvent event) {}
  @Override
  public void g2ConnectionClosed (G2ConnectionEvent event) {}
  @Override
  public void g2ConnectionInitialized (G2ConnectionEvent event) {}
  @Override
  public void g2MessageReceived (G2ConnectionEvent event) {}
  @Override
  public void communicationError (G2CommunicationErrorEvent error_event) {}
  @Override
  public void readBlockage (G2ConnectionEvent event) {}
  @Override
  public void writeBlockage (G2ConnectionEvent event) {}
  @Override
  public void loggedIn (TwConnectionEvent evt) {}
  @Override
  public void userModeChanged (TwConnectionEvent evt) {}  
  
}

class DialogShower implements Runnable {
  private UnsolicitedDialog dlg;
  DialogShower(UnsolicitedDialog dlg) {
    this.dlg = dlg;
  }
  @Override
  public void run() {
    dlg.setVisible(true);
  }
}

