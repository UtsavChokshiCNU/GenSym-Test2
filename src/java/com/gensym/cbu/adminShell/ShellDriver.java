/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ShellDriver.java
 *
 */
package com.gensym.cbu.adminShell;

import java.awt.Image;
import java.awt.Toolkit;
import java.net.InetAddress;

import java.util.Enumeration;

import java.rmi.Naming;
import java.rmi.registry.*;

import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.mdi.*;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import com.gensym.ui.toolbar.ToolBar;

import com.gensym.cbu.adminShell.commands.*;
import com.gensym.denali.developer.*;
import com.gensym.denali.developer.commands.ModuleSelector;
import com.gensym.denali.model.Server;
import com.gensym.denali.simpleclient.ClientSession;
import com.gensym.denali.simpleclient.ModuleView;

import javax.swing.SwingConstants;
import javax.swing.UIManager;


public class ShellDriver extends MDIApplication implements ClientApplication {

  static boolean exists = false;

  private MDIFrame frame;
  private MDIStatusBar statusBar;
  private MDIToolBarPanel toolBarPanel;
  private CMenuBar menuBar;
  private RepresentationConstraints menuConstraints
  = new RepresentationConstraints(RepresentationConstraints.TEXT_AND_ICON,
				  SwingConstants.LEFT, 
				  SwingConstants.CENTER, 
				  SwingConstants.RIGHT, 
				  SwingConstants.CENTER);
  private ModuleSelector moduleSelector;
  ClientSession currentClientSession;
  ModuleView currentModuleView;

  private HelpCommands helpHandler;

  private ServerCommands serverHandler;
  private EditCommands editHandler;
  private ViewCommands viewHandler;
  private WindowCommands windowHandler;
  boolean developmentMode;

  public ShellDriver (String[] cmdLineArgs) {
    super(cmdLineArgs,false);

    /*
     * Create the Shell container
     */
    createShell();
  }

  private void createShell() {
    /*
     * create the frame, getting the title from the message resource
     */
    //    frame = createFrame(shortBundle.getString("ShellTitle"));
    frame = createFrame("OpEx");

    /* 
     * set the frame in UiApplication, so that other components
     * associated with this application can access it via the
     * getCurrentFrame() method
     */
    setCurrentFrame(frame);

    /*
     * create the MenuBar, ToolBar, and StatusBar
     */
    createUiComponents();
  }

  private void createUiComponents() {
    createCommandHandlers();
    frame.setStatusBar(statusBar = createStatusBar());
    frame.setDefaultMenuBar(menuBar = createMenuBar());
    frame.setDefaultToolBarPanel(toolBarPanel = createToolBarPanel()); 
  }

  private MDIFrame createFrame(String title) {
    MDIFrame frame = new MDIFrame(title);

    // set the logo to be the Gensym logo
    Image image = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource("gensym_logo.gif"));
    if (image != null)
      frame.setIconImage(image);
    return frame;
  }

  private CMenuBar createMenuBar() {
    CMenuBar mb = new CMenuBar(); 
    mb.add(createServerMenu()); 
    mb.add(createEditMenu());
    mb.add(createViewMenu());
    mb.add(createWindowMenu());
    mb.add(createHelpMenu());
    return mb;
  }

  private MDIToolBarPanel createToolBarPanel() {
    MDIToolBarPanel panel = new MDIToolBarPanel();
  
    ToolBar tb = new ToolBar();

    moduleSelector = new ModuleSelector();
    //    tb.add(moduleSelector);

    panel.add(tb);
    return panel;
  }

  private MDIStatusBar createStatusBar() {
    MDIStatusBar sb = new MDIStatusBar();
    // This is a temporary kludge to get "No Connection" out of the status line -Craig
    sb.setStatus("");
    return sb;
  }

  private void createCommandHandlers()
  {
    helpHandler = new HelpCommands(frame);
    serverHandler = new ServerCommands(frame);
    editHandler = new EditCommands(frame);
    viewHandler = new ViewCommands(frame);
    windowHandler = new WindowCommands(frame);
  }

  private CMenu createFileMenu() {
    //    CMenu menu = new CMenu (shortBundle.getString("ShellFileMenu"));
    CMenu menu = new CMenu ("File");
    helpHandler = new HelpCommands(frame);
    return menu;
  }
  private CMenu createServerMenu() {
    //    CMenu menu = new CMenu (shortBundle.getString("ShellServerMenu"));
    CMenu menu = new CMenu ("Server");
    menu.add(serverHandler, menuConstraints);
    helpHandler = new HelpCommands(frame);
    return menu;
  }

  private CMenu createAppMenu() {
    //    CMenu menu = new CMenu (shortBundle.getString("ShellServerMenu"));
    CMenu menu = new CMenu ("Blah");
    return menu;
  }

  private CMenu createEditMenu() {
    //    CMenu menu = new CMenu (shortBundle.getString("ShellEditMenu"));
    CMenu menu = new CMenu ("Edit");
    menu.add(editHandler, menuConstraints);
    return menu;
  }

  private CMenu createViewMenu() {
    //    CMenu menu = new CMenu (shortBundle.getString("ShellViewMenu"));
    CMenu menu = new CMenu ("View");
    menu.add(viewHandler, menuConstraints);
    return menu;
  }

  private CMenu createWindowMenu() {
    //    CMenu menu = new CMenu (shortBundle.getString("ShellWindowMenu"));
    CMenu menu = new CMenu ("Window");
    menu.add(((MDIFrame)frame).getManager().getTilingCommand(), menuConstraints);
    return menu;
  }



  private CMenu createToolsMenu() {
    //    CMenu menu = new CMenu (shortBundle.getString("ShellToolsMenu"));
    CMenu menu = new CMenu ("Tools");
    return menu;
  }

  private CMenu createHelpMenu() {
    //    CMenu menu = new CMenu(shortBundle.getString("ShellHelpMenu"));
    CMenu menu = new CMenu("Help");
    menu.add(helpHandler);
    return menu;
  }

  public ClientSession getCurrentSession()
  {
    return currentClientSession;
  }

  public ModuleView getCurrentModule()
  {
    return currentModuleView;
  }

  public void setCurrentModule(ModuleView moduleView)
  {
    currentModuleView = moduleView;
  }

  public void registerModuleSelector()
  {
    moduleSelector.registerAsModuleListener();
  }

  private void preloadClasses()
  {
    preloadClass(SchematicDocument.class);
    preloadClass(TabbedPalette.class);
    preloadClass(NodePalette.class);
  }

  private void preloadClass(Class c)
  {
    if (developmentMode)
      System.out.println("shell preload "+c);
  }

  public synchronized static void main(String[] cmdLineArgs) {
    //  }
    //  public static void mainreal(String[] cmdLineArgs) {
    /*
     * main is where policy is imposed upon instances of 
     * the class. Users that wish to changed the default
     * behaviour, should extend the class and impose their own
     * behaviour in the main method of their own sub-class.
     */

    /*
     * This needs to be called BEFORE the constructor:
     * In Swing 1.0.1 the default look and feel is there own,
     * we want the standard Windows/Motif look and feel. This
     * sets it globally.
     */

    if(!exists) {
      exists = true;
    
    try {
      String name = UIManager.getSystemLookAndFeelClassName();
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    }
    catch (Exception ex) {
      throw new com.gensym.util.UnexpectedException(ex);
    }

    /*
     * Create an instance of this class. 
     */
    ShellDriver application = new ShellDriver(cmdLineArgs);

    /*
     * Command line arguments were handled by the superior classes 
     * of this class. This is where THIS class will handle the 
     * results of processing the command line args.
     */

    /*
     * check to see if -title and/or -geometry command line args 
     * were processed by UiApplication. If they were, then use 
     * the command line information for setting up the frame.
     */
    String title = getTitleInformation();
    if (title != null)
      application.frame.setTitle(title);

    String geometry = getGeometryInformation();
    if (geometry != null)
      setBoundsForFrame(application.frame, geometry);

    String host = application.commandLineArguments.getOptionValue("-host");
    application.developmentMode
      = application.commandLineArguments.getSwitchValue("-development");
    application.preloadClasses();

    if (host != null)
      {
	try {
	  Server server;
	  if (true)
	    {
	      Registry registry = LocateRegistry.getRegistry(host, 1099);
	      if (application.developmentMode)
		System.out.println("here's reggie: "+registry);
	      server = (Server) registry.lookup("//"+host+"/TestServer");
	      if (application.developmentMode)
		System.out.println("reggie sez: "+server);
	    }
	  else
	    server = (Server) Naming.lookup("//"+host+"/TestServer");
	  if (application.developmentMode)
	    System.out.println("got server "+server);
	  server.testMessage("Greets from ClientSession on"+
			     InetAddress.getLocalHost());
	  ClientSession session = new ClientSession(server,application.developmentMode);
	  application.currentClientSession = session;
	  server.addServerListener(session);
	  application.viewHandler.registerAsVisibilityListener(session);
	  Thread.yield();
	  Enumeration moduleViews = session.getModuleViews();
	  if (moduleViews.hasMoreElements())
	    application.currentModuleView = (ModuleView)moduleViews.nextElement();

	  subscribeComponentsToModuleSet(application);
	}
	catch (Exception e)
	  {
	    System.out.println("exception msg: "+e.getMessage());
	    e.printStackTrace();

	    new javax.swing.JOptionPane().
	      showConfirmDialog(new javax.swing.JFrame(), 
				"Catching error, about to blow out",
				"Continue", 
				javax.swing.JOptionPane.OK_CANCEL_OPTION,
				javax.swing.JOptionPane.WARNING_MESSAGE, 
				null);
	    //	    System.exit(0);
	  }
      }
    /*
     * Make the frame visible!
     */

    System.out.println("In ShellDriver, app: "+application+".");

    application.registerModuleSelector();
    //    application.frame.setVisible(true);
  }
  }

  static void subscribeComponentsToModuleSet(ShellDriver application)
  {
    //    application.toolsHandler.subscribeToModuleSet();    
  }
}


