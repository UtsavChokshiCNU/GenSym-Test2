/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ModuleCommands.java
 *
 */
package com.gensym.shell.commands;

import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.io.FileNotFoundException;

import com.gensym.classes.Kb;
import com.gensym.classes.Module;
import com.gensym.dlg.ErrorDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.InputDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.KbEvent;
import com.gensym.ntw.util.KbModuleListener;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.CommandInformation;
import com.gensym.shell.dialogs.DeleteModuleDialog;
import com.gensym.shell.dialogs.MergeModuleDialog;
import com.gensym.shell.dialogs.NewModuleDialog;
import com.gensym.shell.dialogs.RenameModuleDialog;
import com.gensym.shell.dialogs.SaveModuleDialog;
import com.gensym.ntw.util.LoadSaveKBTools;
import com.gensym.ntw.util.uitools.ModuleKBTools;
import com.gensym.util.Symbol;

public class ModuleCommands extends AbstractStructuredCommand implements StandardDialogClient,  ContextChangedListener {

  private static final String shortResource = "LayoutCommandShortResource";
  private static final String longResource = "LayoutCommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";      

  private static Resource i18n = Resource.getBundle("com/gensym/shell/commands/Messages");

  private static final String NEW_MODULE = "NewModule";
  private static final String MERGE_MODULE = "MergeModule";
  private static final String RENAME_MODULE = "RenameModule";
  private static final String SAVE_MODULE = "SaveModule";
  private static final String DELETE_MODULE = "DeleteModule";

  private static final Symbol UNSPECIFIED_ = Symbol.intern("UNSPECIFIED");

  private Frame frame;
  private ConnectionManager connectionManager;
  private TwAccess currentConnection;
  private KbModuleAdapter kbModuleAdapter;

  public ModuleCommands(Frame parentFrame, 
		        ConnectionManager connectionManager) {

    super(new StructuredCommandInformation[] {
      new CommandGroupInformation("NewMergeGroup", new CommandInformation[] {
	new CommandInformation(NEW_MODULE, true, shortResource, longResource,
			       null, null, null, false,
			       mnemonicResource, null),
	  new CommandInformation(MERGE_MODULE, true, shortResource, longResource,
				 null, null, null, false,
				 mnemonicResource, null),
	  new CommandInformation(RENAME_MODULE, true, shortResource, longResource,
				 null, null, null, false,
				 mnemonicResource, null),
	  new CommandInformation(SAVE_MODULE, true, shortResource, longResource,
				 null, null, null, false,
				 mnemonicResource, null)}),
	new CommandGroupInformation("DeleteGroup", new CommandInformation[] {
	  new CommandInformation(DELETE_MODULE, true, shortResource, longResource,
				 null, null, null, false,
				 mnemonicResource, null)})});

    frame = parentFrame;
    kbModuleAdapter = new KbModuleAdapter();
    this.connectionManager = connectionManager;
    connectionManager.addContextChangedListener(this);
    setConnection(connectionManager.getCurrentConnection());
  }

  public void setConnection(TwAccess cxn) {
    try {
      if (currentConnection != null)
	currentConnection.getKb().removeKbModuleListener(kbModuleAdapter);
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }

    currentConnection = cxn;

    try {
      if (currentConnection != null)
	currentConnection.getKb().addKbModuleListener(kbModuleAdapter);
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }

    setAvailability();
  }

  private void setAvailability() {
    setAvailable(NEW_MODULE, (currentConnection != null));
    setAvailable(MERGE_MODULE, (currentConnection != null));
    setAvailable(RENAME_MODULE, (currentConnection != null));
    setAvailable(SAVE_MODULE, (currentConnection != null));
    setAvailable(DELETE_MODULE, (currentConnection != null));

    try {
      if (currentConnection != null) {
	Kb kb = currentConnection.getKb();
	Module[] modules = kb.getModules();
	if ((modules.length) == 1 && (modules[0].getName() == null)) {
	  setAvailable(SAVE_MODULE, false);
	  setAvailable(DELETE_MODULE, false);
	}
      }
    } catch (G2AccessException gae) {
      Trace.exception(gae);
      setAvailable(SAVE_MODULE, false);
      setAvailable(DELETE_MODULE, false);
    }
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey.equals(NEW_MODULE)) {
      NewModuleDialog dlg = new NewModuleDialog(frame, currentConnection);
      dlg.setVisible(true);
      dlg.saveResults();
    }
    else if (cmdKey.equals(MERGE_MODULE)) {
      new MergeModuleDialog (frame, i18n.getString("MergeModuleTitle"), true, true,
			     connectionManager, (StandardDialogClient) this).setVisible(true);
    }
    else if (cmdKey.equals(RENAME_MODULE)) {
      new RenameModuleDialog(frame, i18n.getString("RenameModuleTitle"), true,
			     connectionManager, (StandardDialogClient) this).setVisible(true);
    }
    else if (cmdKey.equals(SAVE_MODULE)) {
      new SaveModuleDialog (frame, i18n.getString("SaveModuleTitle"), true, true,
			    connectionManager, (StandardDialogClient) this).setVisible(true);
    }
    else if (cmdKey.equals(DELETE_MODULE)) {
      new DeleteModuleDialog (frame, i18n.getString("DeleteModuleTitle"), true, 
			      true, connectionManager, (StandardDialogClient) this).setVisible(true);
    }
  }

  @Override
  public void currentConnectionChanged(ContextChangedEvent e) {
    TwAccess cxn = e.getConnection();
    if (cxn == null) {
      setConnection(cxn);
    } else {
      if (e.isConnectionNew())
	setConnection(cxn);
    }
  }
 
  private void handleMergeModuleDialogDismissed(MergeModuleDialog dlg) {
    try {
      LoadSaveKBTools.setResolveConflicts(dlg.getAutomaticallyResolveConflicts()?Boolean.TRUE:Boolean.FALSE);
      LoadSaveKBTools.setBringFormatsUpToDate(dlg.getBringFormatsUpToDate()?Boolean.TRUE:Boolean.FALSE);
      LoadSaveKBTools.setInstallSystemTables(dlg.getInstallSystemTables()?Boolean.TRUE:Boolean.FALSE);
      String file = dlg.getG2FileSpecification();
      Kb kb = currentConnection.getKb();
      if ((kb.getTopLevelModule().getName() == null) && (kb.getModules().length == 1))
	LoadSaveKBTools.loadKB(currentConnection, file);
      else
	LoadSaveKBTools.mergeKB(currentConnection, file);
    } catch (G2AccessException gae) {
      Trace.exception(gae);
      if (gae.getMessage() != null)
	new ErrorDialog(null, i18n.getString("Error"), true, 
			gae.getMessage(), null).setVisible(true);
    } catch (FileNotFoundException fnfe) {
      Trace.exception(fnfe);
      if (fnfe.getMessage() != null)
	new ErrorDialog(null, i18n.getString("FileNotFoundError"), true, 
			fnfe.getMessage(), null).setVisible(true);
    }
  }

  @Override
  public void dialogDismissed(StandardDialog dlg, int code) {
    if (dlg.wasCancelled()) return;

    if (dlg instanceof MergeModuleDialog) {
      handleMergeModuleDialogDismissed((MergeModuleDialog)dlg);
    }

    else if (dlg instanceof RenameModuleDialog) {
      try {
	RenameModuleDialog rd = (RenameModuleDialog)dlg;
	Symbol renameModule_ = rd.getSelectedModule();
	String newValue = rd.getNewValue();
	if (renameModule_ == null || newValue == "") {
	  new ErrorDialog (null, i18n.getString("Error"), true, 
			   i18n.getString("IllegalValueForRenameModule"), 
			   (StandardDialogClient) null).setVisible(true);
	} else {
	  //System.out.println("\n\n"+renameModule_+" renamed to: "+newValue);
	  ModuleKBTools.renameModule(currentConnection, renameModule_, Symbol.intern(newValue));
	}
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	if (gae.getMessage() != null)
	  new ErrorDialog (null, i18n.getString("Error"), true, 
			   gae.getMessage(), (StandardDialogClient) null).setVisible(true);
      }
    }
    
    else if (dlg instanceof SaveModuleDialog) {
      try {
	SaveModuleDialog smd = (SaveModuleDialog)dlg;
	Symbol moduleName_ = smd.getSelectedModule();
	// get options from dialog and set them in LoadSaveKBTools
	String path = smd.getG2FileSpecification();
	LoadSaveKBTools.setShowProgress(smd.getShowProgress()?Boolean.TRUE:Boolean.FALSE);
	LoadSaveKBTools.setSaveWorkspaceLayout(smd.getSaveWorkspaceLayout()?Boolean.TRUE:Boolean.FALSE);
	LoadSaveKBTools.setSaveRequiredModules(smd.getSaveRequiredModules()?Boolean.TRUE:Boolean.FALSE);
	//System.out.println("calling saveModule with moduleName_: "+moduleName_+"  path: "+path);
	LoadSaveKBTools.saveModule(currentConnection, moduleName_, path);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }
   
    else if (dlg instanceof DeleteModuleDialog) {
      try {
	DeleteModuleDialog dmd = (DeleteModuleDialog)dlg;
	Symbol moduleName_ = dmd.getSelectedModule();
	if (moduleName_ == null) {
	  new ErrorDialog (null, i18n.getString("Error"), true, 
			   i18n.getString("NoModuleSpecifiedForDelete"), 
			   (StandardDialogClient) null).setVisible(true);
	} else if (moduleName_.equals(UNSPECIFIED_)) {
	  new ErrorDialog (null, i18n.getString("Error"), true, 
			   i18n.getString("UnspecifiedTopLevelModuleSelectedForDelete"),
			   (StandardDialogClient) null).setVisible(true);
	} else {
	  LoadSaveKBTools.setDeleteAssociatedWorkspaces(dmd.getDeleteAssociatedWorkspaces()?
							Boolean.TRUE:Boolean.FALSE);
	  LoadSaveKBTools.deleteModule(currentConnection, moduleName_);
	}
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	if (gae.getMessage() != null)
	  new ErrorDialog (null, i18n.getString("Error"), true, 
			   gae.getMessage(), (StandardDialogClient) null).setVisible(true);
      }
    }   
  }

  class KbModuleAdapter implements KbModuleListener {
    @Override
    public void receivedInitialModules (KbEvent e) {setAvailability();}
    @Override
    public void moduleDeleted (KbEvent e) {setAvailability();}
    @Override
    public void kbCleared (KbEvent e) {setAvailability();}
    @Override
    public void moduleNameChanged (KbEvent e) {setAvailability();}
    @Override
    public void moduleCreated (KbEvent e) {setAvailability();}
    @Override
    public void moduleDependencyChanged (KbEvent e) {}
    @Override
    public void topLevelWorkspaceAdded (KbEvent e) {}
    @Override
    public void topLevelWorkspaceDeleted (KbEvent e) {}
  }
}






