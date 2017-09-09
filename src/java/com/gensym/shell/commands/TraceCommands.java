/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TraceCommands.java
 *
 */
package com.gensym.shell.commands;

import java.awt.Frame;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.util.Vector;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.shell.dialogs.TraceDialog;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.SubCommandInformation;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.message.TraceOut;

public final class TraceCommands extends AbstractStructuredCommand implements StandardDialogClient {
  private static final boolean debugCommand = false;

  private TraceDialog traceDialog = null;
  private TraceOut traceOut = null;
 
  public static final String TRACE = "Trace";
  public static final String GLOBAL = "TraceGlobal";
  public static final String EXCEPTIONS = "TraceExceptions";
  public static final String CUSTOMIZE = "TraceCustomize";
  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");
  private static Resource shortBundle = Resource.getBundle("com/gensym/shell/commands/CommandShortResource");
 
  private Frame appFrame;

  public TraceCommands(Frame frame){
    super(new StructuredCommandInformation[]{
       new SubCommandInformation(TRACE, true, shortResource, longResource, null, 
				 null, null, mnemonicResource, new StructuredCommandInformation[]{
	 new CommandGroupInformation("GROUP1", new CommandInformation[]{
	   new CommandInformation(GLOBAL, true, shortResource, longResource, null, 
				  null, new Boolean(Trace.getTraceOn()), true, mnemonicResource, null),
	   new CommandInformation(EXCEPTIONS, true, shortResource, longResource, 
				  null, null, 
				  new Boolean(Trace.getExceptionTraceOn()), true, mnemonicResource, null)}),
	 new CommandGroupInformation("GROUP2", new CommandInformation[]{
	   new CommandInformation(CUSTOMIZE, true, shortResource, longResource, null, 
				  null, null, false, mnemonicResource, null)})})});
    this.appFrame = frame; 
  }

  @Override
  public void actionPerformed(ActionEvent e){
    if (debugCommand)
      System.out.println("********* TraceCommands actionPerformed: " + e);

    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;

    if (debugCommand)
      System.out.println("actionPerformed: " + cmdKey);

    if (!isAvailable(cmdKey)){
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", cmdKey));
    } 

    if (cmdKey.equals(GLOBAL))
      handleGlobalCommand();
    else if (cmdKey.equals(EXCEPTIONS))
      handleExceptionsCommand();
    else if (cmdKey.equals(CUSTOMIZE))
      handleCustomizeCommand();
  }

  private void handleGlobalCommand(){
    boolean traceOn = Trace.getTraceOn();
    Trace.setTraceOn(!(traceOn));

    if (debugCommand)
      System.out.println("traceOn is set to: " + Trace.getTraceOn());
  }

  private void handleExceptionsCommand(){
    boolean excepOn = Trace.getExceptionTraceOn();
    Trace.setExceptionTraceOn(!(excepOn));

    if (debugCommand)
      System.out.println("exceptionOn is set to: " + Trace.getExceptionTraceOn());
  }

  private void handleCustomizeCommand(){
    if (traceDialog == null){
      String title = shortBundle.getString("TraceDialogTitle");
      boolean isModal = true;
      traceDialog = new TraceDialog (appFrame, title, isModal,
				     (StandardDialogClient) this);

      TextField levelTF = traceDialog.getLevelTextField();
      if (levelTF != null){
	String str = "" + Trace.ALL_LEVELS;
	levelTF.setText(str);
	levelTF.setEditable(false);
      }
    }

    traceDialog.setVisible(true);   
  }  

  private void traceDialogDismissed (TraceDialog dlg) {
    String keys = null;
    String level = null;
    String messages = null;
    int traceLevel = Trace.ALL_LEVELS;

    TextField keysTF = traceDialog.getKeysTextField();
    if (keysTF != null)
       keys = keysTF.getText();
    
    TextField levelTF = traceDialog.getLevelTextField();
    if (levelTF != null) {
      level = levelTF.getText();
      traceLevel = Integer.parseInt(level);
    }
    
    TextField messagesTF = traceDialog.getMessagesTextField();
    if (messagesTF != null)
      messages = messagesTF.getText();

    if (traceOut == null)
      traceOut = new TraceOut();

    if (debugCommand)
      System.out.println("initializing: " + keys);
    traceOut.initialize(keys, traceLevel, messages);
  }

  @Override
  public void dialogDismissed (StandardDialog dlg, int code) {
    if (dlg.wasCancelled()) return;

    if (dlg instanceof TraceDialog)
      traceDialogDismissed((TraceDialog)dlg);
  }
}











