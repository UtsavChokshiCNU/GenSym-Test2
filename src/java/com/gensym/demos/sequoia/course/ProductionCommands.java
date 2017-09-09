/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ProductionCommands.java
 *
 */
package com.gensym.demos.sequoia.course;

import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.util.Vector;
import javax.swing.JMenuItem;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.message.Resource;

//import these classes to handle RPC calls and exceptions
import com.gensym.dlg.ErrorDialog;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;

//import these classes to determine command availability
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.ntw.TwAccess;

/*
 * ProductionCommands needs to implement ContextChangedListener 
 * to determine when certain commands are available, based on 
 * whether or not a connection exists.
 */
public class ProductionCommands extends AbstractStructuredCommand implements ContextChangedListener {

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");
  private static Resource shortBundle = Resource.getBundle("com/gensym/demos/sequoia/course/CommandShortResource");

  private static final String SCHEDULE = "Schedule";
  private static final String ADJUST = "Adjust";
  private static final String START_CANCEL = "StartCancel";
  private static final String PAUSE_RESUME = "PauseResume";

  private static final String START  = shortBundle.getString("Start");
  private static final String CANCEL   = shortBundle.getString("Cancel");
  private static final String PAUSE  = shortBundle.getString("Pause");
  private static final String RESUME = shortBundle.getString("Resume");

  private Frame frame;
  private ConnectionManager connectionMgr;

  public ProductionCommands(Frame frame, 
			    ConnectionManager connectionManager) {

    super(new StructuredCommandInformation[]{
      new CommandGroupInformation("Group1", new CommandInformation[]{
        new CommandInformation(SCHEDULE, true, shortResource, longResource, null,
			       null, null, true),
        new CommandInformation(ADJUST, true, shortResource, longResource, null,
			       null, null, false)}),
      new CommandGroupInformation("Group2", new CommandInformation[]{
        new CommandInformation(START_CANCEL, true, shortResource, longResource, null,
			       null, null, true),
        new CommandInformation(PAUSE_RESUME, true, shortResource, longResource, null,
			       null, null, true)})});

    this.frame = frame;
    this.connectionMgr = connectionManager;

    //Constructor adds itself as a listener for ContextChangedEvents
    connectionManager.addContextChangedListener(this);

    setAvailable(PAUSE_RESUME, false);

    //Set availability of StartCancel command to false if 
    //there is no current connection.
    if (connectionManager.getCurrentConnection() == null)
      setAvailable(START_CANCEL, false);
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey))
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", 
						  cmdKey));

    if (cmdKey.equals(SCHEDULE))
      handleScheduleCommand();
    else if (cmdKey.equals(ADJUST))
      handleAdjustCommand();
    else if (cmdKey.equals(START_CANCEL))
      handleStartCancelCommand((JMenuItem)e.getSource());
    else if (cmdKey.equals(PAUSE_RESUME))
      handlePauseResumeCommand((JMenuItem)e.getSource());
  }

  @Override
  public String[] getKeys(){
    return new String[] {SCHEDULE, ADJUST, 
			 START_CANCEL, PAUSE_RESUME};
  }

  private void handleScheduleCommand() {
    System.out.println("NYI: handleScheduleCommand");
  }

  private void handleAdjustCommand() {
    System.out.println("NYI: handleAdjustCommand");
  }

  private void handleStartCancelCommand(JMenuItem menu) {

    String label = menu.getText();
    if (label.equals(START)) {
      //set current command label and availability of other 
      //commands based on current label
      menu.setText(CANCEL);
      setAvailable(PAUSE_RESUME, true);

      //initialize the G2 procedure name as a symbol
      Symbol startJob = Symbol.intern ("START-JOB");

      //initialize args for callRPC
      Object[] args = new Object[0];

      //call the RPC and handle exception
      try {
	((G2Gateway)connectionMgr.getCurrentConnection()).callRPC(startJob, 
								  args);
      }
      catch (G2AccessException ex){
	displayError("", ex.getMessage());
      }
    }
    else {
      menu.setText(START);
      setAvailable(PAUSE_RESUME, false);

      //initialize the G2 procedure name as a symbol
      Symbol cancelJob = Symbol.intern ("CANCEL-JOB");

      //initialize args for callRPC
      Object[] args = new Object[0];

      //call the RPC and handle exception
      try {
	((G2Gateway)connectionMgr.getCurrentConnection()).callRPC(cancelJob, 
								  args);
      }
      catch (G2AccessException ex){
	displayError("", ex.getMessage());
      }
    }
  }

  protected void handlePauseResumeCommand(JMenuItem menu) {
    String label = menu.getText();
    if (label.equals(PAUSE)) {
      menu.setText(RESUME);

      //initialize the G2 procedure name as a symbol
      Symbol pauseJob = Symbol.intern ("PAUSE-JOB");

      //initialize args for callRPC
      Object[] args = new Object[0];

      //call the RPC and handle exception
      try {
	((G2Gateway)connectionMgr.getCurrentConnection()).callRPC(pauseJob, 
								  args);
      }
      catch (G2AccessException ex){
	displayError("", ex.getMessage());
      }
    }
    else {
      menu.setText(PAUSE);

      //initialize the G2 procedure name as a symbol
      Symbol resumeJob = Symbol.intern ("RESUME-JOB");

      //initialize args for callRPC
      Object[] args = new Object[0];

      //call the RPC and handle exception
      try {
	((G2Gateway)connectionMgr.getCurrentConnection()).callRPC(resumeJob, 
								  args);
      }
      catch (G2AccessException ex){
	displayError("", ex.getMessage());
      }
    }
  }

  //create and show an error dialog
  private void displayError(String title, String msg) {
     ErrorDialog dlg = new ErrorDialog (frame, title, true, msg, 
				       (StandardDialogClient) this);
     dlg.show();
  }

  // BEGIN: ContextChangedListener interface methods 
  /*
   * When a connection changes, set the availability of the 
   * Start/Cancel command to available.
   */
  @Override
  public void currentConnectionChanged(ContextChangedEvent e) {
    TwAccess context = e.getConnection();
    boolean available = true;
    if (context == null)
      available = false;
    setAvailable(START_CANCEL, available);
  }
  // END: ContextChangedListener interface methods
}











