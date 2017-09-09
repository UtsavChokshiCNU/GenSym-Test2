/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 SnapshotCommands.java
 *
 */
package com.gensym.shell.commands;

import java.awt.Frame;
import java.awt.event.ActionEvent;

import com.gensym.dlg.ErrorDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.shell.dialogs.SaveSnapshotDialog;
import com.gensym.shell.dialogs.WarmbootDialog;
import com.gensym.ntw.util.LoadSaveKBTools;

public class SnapshotCommands extends AbstractCommand implements StandardDialogClient, ContextChangedListener {

  public static final String WARMBOOT_FROM_SNAPSHOT = "WarmbootFromSnapshot";
  public static final String SAVE_SNAPSHOT = "SaveSnapshot";

  private static final String shortResource = "LayoutCommandShortResource";
  private static final String longResource = "LayoutCommandLongResource";
  private static Resource i18n = Resource.getBundle("com/gensym/shell/commands/Messages");

  private Frame frame;
  private ConnectionManager connectionManager;
  private TwAccess currentConnection;

  private SaveSnapshotDialog saveDialog;
  private WarmbootDialog warmbootDialog;

  public SnapshotCommands(Frame parentFrame, ConnectionManager connectionManager) {
    super(new CommandInformation[]{
      new CommandInformation(WARMBOOT_FROM_SNAPSHOT, true, shortResource,
			     longResource, null, null, null, false),
	new CommandInformation(SAVE_SNAPSHOT, true, shortResource, longResource,
			       null, null, null, false)});

    frame = parentFrame;
    this.connectionManager = connectionManager;
    this.connectionManager.addContextChangedListener(this);
    setConnection(connectionManager.getCurrentConnection());
  }

  public void setConnection(TwAccess cxn) {
    currentConnection = cxn;
    setAvailability();
  }

  public void setAvailability() {
    boolean b = false;
    if(com.gensym.core.GensymApplication.getApplication()!= null)
     b = com.gensym.core.GensymApplication.getApplication().isBrowserMode();

    setAvailable(SAVE_SNAPSHOT, (currentConnection !=  null) && !b);
    setAvailable(WARMBOOT_FROM_SNAPSHOT, (currentConnection != null) && !b);
  }

  @Override
  public void actionPerformed(ActionEvent e) {
    String cmdKey = e.getActionCommand();
    if (cmdKey.equals(SAVE_SNAPSHOT)) {
      if (saveDialog == null) {
	saveDialog = new SaveSnapshotDialog(frame, i18n.getString("SaveSnapshotDialogTitle"), true,
					    true, connectionManager, (StandardDialogClient) this);
      }
      saveDialog.setVisible(true);
    }

    else if (cmdKey.equals(WARMBOOT_FROM_SNAPSHOT)) {
      if (warmbootDialog == null) {
	warmbootDialog = new WarmbootDialog(frame, i18n.getString("WarmbootDialogTitle"), true,
					     true, connectionManager, (StandardDialogClient) this);
	}
      warmbootDialog.setVisible(true);
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

  @Override
  public void dialogDismissed(StandardDialog dlg, int code) {
    if (dlg.wasCancelled()) return;

    if (dlg instanceof SaveSnapshotDialog) {
	SaveSnapshotDialog ssd = (SaveSnapshotDialog)dlg;
        ssd.setShowProgress(Boolean.TRUE);
        ssd.setSaveWorkspaceLayout(Boolean.TRUE);
	LoadSaveKBTools.setShowProgress(ssd.getShowProgress());
	LoadSaveKBTools.setSaveWorkspaceLayout(ssd.getSaveWorkspaceLayout());
	String filespec = ssd.getG2FileSpecification();
        Boolean showProgress = ssd.getShowProgress();
        Object session = Boolean.FALSE;
        if (ssd.getSaveWorkspaceLayout().booleanValue() == true)
          session = currentConnection.retrieveSession();
        //using thread for save to avoid locking the ui refresh
	SaveSnapshotThread thread = new SaveSnapshotThread(currentConnection, filespec, showProgress, session);
        thread.start();
    }

    else if (dlg instanceof WarmbootDialog) {
      try {
	WarmbootDialog wd = (WarmbootDialog)dlg;
	LoadSaveKBTools.setRunInCatchUpMode(wd.getRunInCatchUpMode());
	String filespec = wd.getG2FileSpecification();
	LoadSaveKBTools.warmbootKB(currentConnection, filespec);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	if (gae.getMessage() !=  null)
	  new ErrorDialog(null, i18n.getString("Error"), true, gae.getMessage(), null).setVisible(true);
      }
    }
  }

  // thread to save snapshot
  class SaveSnapshotThread extends Thread {

    TwAccess cxn;
    String filespec;
    Boolean showProgress;
    Object session;

    SaveSnapshotThread(TwAccess currentConnection, String filespec, Boolean showProgress, Object session) {
      this.cxn = currentConnection;
      this.filespec = filespec;
      this.showProgress = showProgress;
      this.session = session;
    }

    @Override
    public void run(){

      try{
        if(com.gensym.core.GensymApplication.getApplication()!= null)
          (com.gensym.core.GensymApplication.getApplication()).setApplicationBusy();

        Object success = cxn.callRPC(
              com.gensym.util.Symbol.intern("G2-SNAPSHOT"),
              new Object[] {filespec, showProgress, session});

      } catch (G2AccessException gae) {

        Trace.exception(gae);
        if (gae.getMessage() != null)
          new ErrorDialog(null, i18n.getString("Error"), true, gae.getMessage(), null).setVisible(true);

      } finally  {
        if(com.gensym.core.GensymApplication.getApplication()!= null)
          (com.gensym.core.GensymApplication.getApplication()).setApplicationNormal();
      }
    }
  }
}
