/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 NavigationCommands.java
 *
 */
package com.gensym.demos.g2studiosample.commands;

import java.awt.event.ActionEvent;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.message.Resource;
import com.gensym.demos.g2studiosample.Shell;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIDocument;
import javax.swing.KeyStroke;
import java.awt.Event;
import java.awt.event.KeyEvent;
import com.gensym.shell.util.WebBrowserDocument;
import java.io.IOException;

public class NavigationCommands extends AbstractCommand {
  public static final String GO_HOME = "GoHome";
  public static final String GO_BACK = "GoBack";
  public static final String GO_FORWARD = "GoForward";
  public static final String STOP_DOWNLOAD = "StopDownload";
  public static final String NEXT_WINDOW = "NextWindow";
  public static final String PREVIOUS_WINDOW = "PreviousWindow";      
  private static final String shortResource = "NavigationCommandShortResource";
  private static final String longResource = "NavigationCommandShortResource";
  private static final String mnemonicRsource = "MnemonicResource";
  private Resource shortBundle = Resource.getBundle("com/gensym/demos/g2studiosample/commands/NavigationCommandShortResource");
  private Shell shell;

  public NavigationCommands(Shell shell) {
    super(new CommandInformation[]{
      new CommandInformation(GO_HOME, true, shortResource, longResource,
			     "home.gif",
			     null, 
			     null, true, mnemonicRsource, null),      
	new CommandInformation(GO_BACK, true, shortResource, longResource,
			       "nav_back.gif",
			       null, 
			       null, true, mnemonicRsource,
			       KeyStroke.getKeyStroke(KeyEvent.VK_LEFT, Event.ALT_MASK)),
	new CommandInformation(GO_FORWARD, true, shortResource, longResource,
			       "nav_forward.gif",
			       null, 
			       null, true, mnemonicRsource,
			       KeyStroke.getKeyStroke(KeyEvent.VK_RIGHT, Event.ALT_MASK)),
	new CommandInformation(NEXT_WINDOW, true, shortResource, longResource,
			       "nextDoc.gif",
			       null, 
			       null, true, mnemonicRsource,
			       KeyStroke.getKeyStroke(KeyEvent.VK_TAB, Event.CTRL_MASK)),
	new CommandInformation(PREVIOUS_WINDOW, true, shortResource, longResource,
			       "prevDoc.gif",
			       null, 
			       null, true, mnemonicRsource,
			       KeyStroke.getKeyStroke(KeyEvent.VK_TAB,
						      Event.SHIFT_MASK+Event.CTRL_MASK)),	
	new CommandInformation(STOP_DOWNLOAD, true, shortResource, longResource,
			       "stop.gif",
			       null, 
			       null, true, mnemonicRsource,
			       KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0))});
    this.shell = shell;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (cmdKey.equals(GO_HOME))
      handleGoHome();
    else if (cmdKey.equals(GO_BACK))
      handleGoBack(true);
    else if (cmdKey.equals(GO_FORWARD))
      handleGoForward(true);
    else if (cmdKey.equals(PREVIOUS_WINDOW))
      handleGoBack(false);
    else if (cmdKey.equals(NEXT_WINDOW))
      handleGoForward(false);        
    else if (STOP_DOWNLOAD.equals(cmdKey))
      handleStopDownload();
  }

  private void handleGoHome() {
    shell.goHome();    
  }
  
  private void handleGoBack(boolean stayInWebBrowser) {
    MDIDocument activeDocument = ((MDIFrame)shell.getCurrentFrame()).getManager().getActiveDocument();
    if (stayInWebBrowser && activeDocument instanceof WebBrowserDocument) {
      try {
	shell.setLocation(((WebBrowserDocument)activeDocument).goBack());
      } catch(IOException ioe) {
	//put up dialog
      }
    } else {
      ((MDIFrame)shell.getCurrentFrame()).getManager().activateNextDocument();
    }
  }

  private void handleGoForward(boolean stayInWebBrowser) {
    MDIDocument activeDocument = ((MDIFrame)shell.getCurrentFrame()).getManager().getActiveDocument();
    if (stayInWebBrowser && activeDocument instanceof WebBrowserDocument) {
      try {
	shell.setLocation(((WebBrowserDocument)activeDocument).goForward());
      } catch(IOException ioe) {
	//put up dialog
      }
    } else {
      ((MDIFrame)shell.getCurrentFrame()).getManager().activatePreviousDocument();
    }
  }

  private void handleStopDownload() {
    shell.setWaiting(false);
  }  

}











