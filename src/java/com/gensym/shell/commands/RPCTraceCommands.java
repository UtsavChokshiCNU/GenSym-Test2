/*
 * This class provides full access controls to RPCTrace class to turn on RPCTrace,
 * to empty RPC data storage, to turn on stack trace, and to make RPCTrace report.
 * RPCTraceCommands.java
 * @author FY
 *
 * @undocumented
 */
package com.gensym.shell.commands;

import java.awt.Frame;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.util.Vector;
import java.io.*;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.SubCommandInformation;
import com.gensym.message.Resource;
import com.gensym.jgi.RPCTrace;

public final class RPCTraceCommands extends AbstractStructuredCommand {

  public static final String TRACE = "RPCTraceLabel";
  public static final String RPCTRACE = "RPCTrace";
  public static final String RPCDATA = "EmptyRPCData";
  public static final String RPCSTACK = "StackTrace";
  public static final String RPCREPORT = "RPCReport";
  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";
  private Resource i18n = Resource.getBundle("com.gensym.shell.commands.Errors");
  private static Resource shortBundle = Resource.getBundle("com.gensym.shell.commands.CommandShortResource");
 
  private Frame appFrame;

  public RPCTraceCommands(Frame frame){
    super(new StructuredCommandInformation[]{
       new SubCommandInformation(TRACE, true, shortResource, longResource, null,
				 null, null, mnemonicResource, new StructuredCommandInformation[]{
         new CommandGroupInformation("GROUP1", new CommandInformation[]{
	   new CommandInformation(RPCTRACE, true, shortResource, longResource,
				  null, null,
				  new Boolean(RPCTrace.isTraceOn()), true, mnemonicResource, null),
           new CommandInformation(RPCDATA, true, shortResource, longResource,
				  null, null,
				  new Boolean(RPCTrace.isEmptyDataOn()), true, mnemonicResource, null),
           new CommandInformation(RPCSTACK, true, shortResource, longResource,
				  null, null,
				  new Boolean(RPCTrace.isStackOn()), true, mnemonicResource, null),
           new CommandInformation(RPCREPORT, true, shortResource, longResource,
				  null, null,
				  new Boolean(RPCTrace.isReportOn()), true, mnemonicResource, null)})

    })});
    this.appFrame = frame;
  }

  @Override
  public void actionPerformed(ActionEvent e){

    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;

    if (!isAvailable(cmdKey)){
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", cmdKey));
    } 

    if (cmdKey.equals(RPCTRACE))
      handleRPCTraceCommand();
    else if (cmdKey.equals(RPCDATA))
      handleRPCDataCommand();
    else if (cmdKey.equals(RPCSTACK))
      handleRPCStackCommand();
    else if (cmdKey.equals(RPCREPORT))
      handleRPCReportCommand();

  }


  private void handleRPCTraceCommand() {
    RPCTrace.setTraceOn(!(RPCTrace.isTraceOn()));
  }

  private void handleRPCDataCommand() {
    RPCTrace.setEmptyDataOn(!(RPCTrace.isEmptyDataOn()));

    if (RPCTrace.isEmptyDataOn())
      RPCTrace.emptyDataStorage();

  }

  private void handleRPCStackCommand() {
    RPCTrace.setStackOn(!(RPCTrace.isStackOn()));
  }

  private void handleRPCReportCommand() {
    RPCTrace.setReportOn(!(RPCTrace.isReportOn()));

    if (RPCTrace.isReportOn()) {
      String fileName = System.getProperty("com.gensym.jgi.RPCReportPath",
                                           shortBundle.getString("RPCDefaultPath"));
      try {
        FileWriter file = new FileWriter(fileName);
        BufferedWriter buff = new BufferedWriter(file);
        RPCTrace.writeReportToBuffer(buff);
      }
      catch (Exception ex) {
        ex.printStackTrace();
      }
      RPCTrace.setReportOn(false);
    }

  }
}











