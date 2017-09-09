/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ToolsCommands.java
 *
 */
package com.gensym.beaneditor;

import java.awt.Toolkit;
import java.awt.Image;
import java.awt.Dimension;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.ActionEvent;
import java.util.Vector;
import java.io.ByteArrayOutputStream;
import java.io.ObjectOutputStream;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ui.Command;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.SubCommandInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.CommandEvent;
import com.gensym.dlg.WarningDialog;
import com.gensym.dlg.ErrorDialog;
import com.gensym.dlgruntime.DefaultDialogReader;
import com.gensym.dlgruntime.PageGroup;
import com.gensym.beansruntime.Hookup;

class ModeCommands extends AbstractCommand{

  static final String RUN_BUILD_MODE = "ToolsRunBuildMode";
  static final String DEBUG_MODE="ToolsDebugMode";

  private static final Resource errorResource = Resource.getBundle("com.gensym.beaneditor.Errors");

  private EditorFrame frame;
  private PageGroupCommands pageGroupCommands;
  private ViewCommands viewCommands;

  // Relation to Testing (Run Mode) Window
  private boolean testWindowExists = false;
  private DialogTestingResource testingResource = null;
  private DefaultDialogReader testingReader;
  private DialogTestingLauncher testingLauncher;

  private Image switchIcon = Toolkit.getDefaultToolkit().getImage(getClass().getResource("switch.gif"));
  private Image downSwitchIcon = Toolkit.getDefaultToolkit().getImage(getClass().getResource("switch_down.gif"));

  //Debug
  private DebugWindow debugWindow;

  ModeCommands(EditorFrame frame, PageGroupCommands pageGroupCommands, ViewCommands
	       viewCommands){
    super(new CommandInformation[]{
      new CommandInformation(RUN_BUILD_MODE, true, null, null, null, null,
			     null, true, "Launch Dialog", "Launch Dialog", 
			     null, null),
      new CommandInformation(DEBUG_MODE, true, null, null, null, 
			     null, Boolean.FALSE, true, "Debug", "Debug", 
			     null, null)});
    this.frame = frame;
    this.pageGroupCommands = pageGroupCommands;
    this.viewCommands = viewCommands;
    testingReader = new DefaultDialogReader();
    testingLauncher = new DialogTestingLauncher(frame);
    updateAvailability();
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)) {
      throw new IllegalStateException(errorResource.format("CommandIsUnavailable", cmdKey));
    }

    if (cmdKey.equals(RUN_BUILD_MODE)){
      if (frame.application.inDesignMode()) doLaunchDialog();
      else setDesignMode(true);
    }
    else if (cmdKey.equals(DEBUG_MODE)) 
      frame.setDebugMode(!(getState(DEBUG_MODE).booleanValue()));
  }
  

  boolean isDebugWindowVisible(){
    if (debugWindow == null) return false;
    else return debugWindow.isVisible();
  }

  void  setDebugWindowVisible(boolean visible){
    if (debugWindow == null)
      createDebugWindow();
   debugWindow.setVisible(visible);
  }

  private void setDesignMode(boolean b)
  {
    if (!frame.application.setDesignMode(b)){
	WarningDialog dialog 
	  = new WarningDialog(frame,"",true,"Close all launched dialogs first!",
			     null);
	dialog.pack ();
	//dialog.setLocation(300,300); // hack
	dialog.setVisible (true);
    }
  }

  private byte[] serializePageGroup(PageGroup pageGroup)
       throws java.io.IOException
  {
    ByteArrayOutputStream baos = new ByteArrayOutputStream();
    ObjectOutputStream oos = new ObjectOutputStream(baos);
    oos.writeObject(pageGroup);
    byte[] serializedData = baos.toByteArray();
    oos.close();
    baos.close();
    return serializedData;
  }

  private void createDebugWindow(){
    debugWindow = new DebugWindow(frame);  
    WindowAdapter windowAdapter = new WindowAdapter(){
      @Override
      public void windowClosing(WindowEvent event){
	    debugWindow.setVisible(false);
	    viewCommands.updateState();
      }
    };
    debugWindow.addWindowListener(windowAdapter); 
  }

  private void doLaunchDialog(){
    if (frame.isDebugMode()){
      if (debugWindow == null)
	createDebugWindow();
      Hookup.setDebugger(debugWindow); 
      debugWindow.clear();
      debugWindow.msgID = 0;
      debugWindow.setVisible(true);
      viewCommands.updateState();
    }

    frame.getStatusBar().setStatus("Running");

    if (frame.application.inDesignMode())
      setDesignMode(false);
    
    byte[] serializedData = null;
    try{ 
      if (frame.getDialogType() == frame.SIMPLE_DIALOG)
	serializedData = frame.getCanvas().serializeToBytes();
      else{
	PageGroup pageGroup = pageGroupCommands.makePageGroup("memcache:","",true);
	serializedData = serializePageGroup(pageGroup);
	// testingReader.setPageNode(firstPage);
      }
    }
    catch (Exception ex){
      //System.out.println("saving test resource for launch failed");
      //ex.printStackTrace();
      Trace.exception(ex);
      ErrorDialog dialog 
	= new ErrorDialog(frame,"Error",true,"Error launching dialog.  \n"+ex.toString(),
			  null);
      dialog.setVisible (true);
      launchComplete();
      return;
    }
    try {
      testingResource 
	= new DialogTestingResource(serializedData,
				    testingReader,
				    testingLauncher);
      testingResource.launchForTesting(frame);
      frame.getCanvas().setEventHandler(frame.getBeanDebugTool());
      frame.getCanvas().setComponentAdapationEnabled(false);
      testWindowExists = true;
    } catch (Exception e){
      //System.out.println("launching test resource failed");
      //e.printStackTrace();
      Trace.exception(e);
      ErrorDialog dialog 
	= new ErrorDialog(frame,"Error",true,"Error launching dialog.  \n"+e.toString(),
			  null);
      dialog.setVisible (true);
      launchComplete();
    }
  }

  synchronized boolean isRunningTestDialog()
  {
    return testWindowExists;
  }

  synchronized void launchComplete()
  {
    if (debugWindow != null){
      Hookup.setDebugger(null);
      debugWindow.done();
    }
    frame.getStatusBar().resetStatus();
    testingResource = null;
    testWindowExists = false;
    frame.getCanvas().setEventHandler(frame.getBeanEditTool());
    frame.getCanvas().setComponentAdapationEnabled(true);
    frame.application.setDesignMode(true);
    updateAvailability();
  }

  void updateAvailability(){
    if (!frame.application.inDesignMode()){
      setDescription(RUN_BUILD_MODE, Command.SHORT_DESCRIPTION, "Build Dialog");
      setDescription(RUN_BUILD_MODE, Command.LONG_DESCRIPTION, "Build Dialog");
      setIcon(RUN_BUILD_MODE, Command.SMALL_ICON, downSwitchIcon);
    }
    else{
      setDescription(RUN_BUILD_MODE, Command.SHORT_DESCRIPTION, "Launch Dialog");
      setDescription(RUN_BUILD_MODE, Command.LONG_DESCRIPTION, "Launch Dialog");
      setIcon(RUN_BUILD_MODE, Command.SMALL_ICON, switchIcon);
    }
    setState(DEBUG_MODE, new Boolean(frame.isDebugMode()));
  }

}

  

