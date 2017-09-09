
package com.gensym.beaneditor;

import java.awt.Point;
import java.awt.Dimension;

import java.util.Vector;
import java.util.Hashtable;
import java.util.Locale;

import java.io.File;
import java.io.PrintStream;
import java.io.FileOutputStream;
import java.io.IOException;

import java.beans.Beans;

import javax.swing.UIManager;

import com.gensym.dlgruntime.DefaultDialogLauncher;

import com.gensym.dlg.WarningDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.core.UiApplication;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.message.Resource;
import com.gensym.message.Message;
import com.gensym.message.MessageEvent;
import com.gensym.message.Trace;
import com.gensym.files.URLFile;

import com.gensym.com.BeanXporter;

import com.gensym.ui.palette.PaletteButton;

import com.gensym.ntw.files.*;

public class ComponentEditor extends UiApplication
{
  static Vector frames = new Vector();
  static boolean standalone = false;
  //boolean allowCustomHookups = false;
  private boolean inDesignMode = true;
  BeanXporter beanifier = null; // used only on NT/Windows 95 for ActiveX menu 
  static boolean windowsPlatform;
  //Palette support
  private static String currentBeanSelection = null;
  private static PaletteButton currentPaletteButton = null;
  String hostName = null;
  String portName = null;
  static boolean doubleBuffer = true;
  static boolean noAutoActivationOfRetrievers = false;

  /*
   * Standard Messaging Requirements
   */
  
  private static Resource i18n =
  Resource.getBundle("com.gensym.resources.Messages",
		     Locale.getDefault());
  private static int GUI_LEVEL = 2;
  

  static{
    String osName = System.getProperty("os.name");
    windowsPlatform = ((osName != null) &&
		       (osName.equals("Windows NT") || osName.equals("Windows 95")));
  }

  /* Constructors */
  private ComponentEditor (String[] args) {
    super(args, true);
  }

  public ComponentEditor () {
    this(new String[0]); 
  }


  boolean inDesignMode()
  {
    return inDesignMode;
  }

  // returns boolean saying whether set was accepted
  boolean setDesignMode(boolean b)
  {
    if (inDesignMode == b)
      return true;

    int i, size = frames.size();
    // Cannot leave run mode if any Test Dialog is up
    if (!inDesignMode)
      for (i=0; i<size; i++)
	if (((EditorFrame)frames.elementAt(i)).isRunningTestDialog())
	  {
	    return false;
	  }
    Beans.setDesignTime(b);
    inDesignMode = b;
    for (i = 0 ; i<size ; i++)
      {
	EditorFrame frame = (EditorFrame) frames.elementAt(i);
	frame.updateToolsMenu();
      }
    return true;
  }

  static Object getBean (String clazz)
  {
    if (currentPaletteButton == null) return null;
    return currentPaletteButton.createObject();      
  }
  
  static String getShortName (String name)
  {
    int index = name.lastIndexOf('.');
    return (index == -1) ? name : name.substring(index+1);
  }

  private static void setNoOutput()
  {
    try
      {
	String dir = System.getProperty ("user.home");
	File outFile = new File(dir, "componenteditor.log");
	File errFile = new File(dir, "componenteditor.err");   
	System.setOut(new PrintStream(new FileOutputStream(outFile)));
	System.setErr(new PrintStream(new FileOutputStream(errFile)));
      }
    catch (Exception ex)
      {
	Trace.exception (ex);
      }
  }

  private String replaceJarWithSequoiaJarIfNecessary(String path){
    int index = -1;
    if (path.endsWith("jars"+File.separator+"controls.jar"))
      index = path.indexOf("jars"+File.separator+"controls.jar");

    if (path.endsWith("jars"+File.separator+"trace.jar"))
      index = path.indexOf("jars"+File.separator+"trace.jar");

    if (path.endsWith("jars"+File.separator+"wksp.jar"))
      index = path.indexOf("jars"+File.separator+"wksp.jar");

    if (index == -1)
      return path;
    else
      return path.substring(0, index)+"sequoia.jar";
  }
  
  public void loadJar(String fullPath, boolean interactiveLoad) {
    boolean autoUpgradeToSequoiaJar = false;
    String oldPath = fullPath;
    if (!interactiveLoad){
      fullPath = replaceJarWithSequoiaJarIfNecessary(fullPath);
      autoUpgradeToSequoiaJar = (!oldPath.equals(fullPath));
    }
      
    String[] loadedJars = G2JarLoader.getLoadedJars();
    boolean jarAlreadyLoaded = false;
    for (int i=0; i<loadedJars.length; i++){
      if (loadedJars[i].equals(new File(fullPath).getAbsolutePath().toLowerCase()))
	jarAlreadyLoaded = true;
    }
    
    if (jarAlreadyLoaded){
      if (interactiveLoad){
	WarningDialog wd = new WarningDialog (getCurrentFrame(), "Component Editor", 
					      true, 
					      "Jar "+fullPath+" has already been loaded.",
						null);
	wd.setVisible (true);
	//Show palette and select the tab on the Palette
      }
      return;
    }
    
    G2JarLoader jl = null;
    for (int i = 0; i<frames.size(); i++){
      EditorFrame frame = (EditorFrame) frames.elementAt(i);
      frame.getStatusBar().setStatus("Loading "+fullPath+"..."); 
    }    
    try{
      jl = new G2JarLoader (fullPath); 
      }
    catch (java.io.IOException e){
      Trace.exception (e, null); 
      resetStatus();  
	if (interactiveLoad)
	  Message.send (new MessageEvent(GUI_LEVEL, "com.gensym.beaneditor",
					 ComponentEditor.class, i18n,
					 "unableToOpenFile", new Object[] {fullPath}));
	else{
	  if (autoUpgradeToSequoiaJar)
	    Message.send (new MessageEvent(GUI_LEVEL, "com.gensym.beaneditor",
					   ComponentEditor.class, i18n,
					   "autoJarUpgradeFailed", 
					   new Object[] {oldPath, fullPath}));
	  RetryHandler retryHandler = new RetryHandler(getCurrentFrame(), fullPath);
	  boolean retry = retryHandler.retry();
	  if (retry){
	    loadJar(retryHandler.getFileName(), interactiveLoad);
	    return;
	  }
	  else
	    return;
	}
    }
    
    if (jl == null) return;
    
    ProgressFrame pFrame = new ProgressFrame(getCurrentFrame(), "Loading "+fullPath+"...");
    pFrame.setSize(400, 200);
    Dimension frameSize = getCurrentFrame().getSize();
    Point location = getCurrentFrame().getLocation();
    pFrame.setLocation(frameSize.width/2 + location.x - 200,
		       frameSize.height/2 + location.y - 100);
    pFrame.setVisible(true);
   
    try{
      G2JarInfo jar = jl.loadJar(pFrame.getProgressBar().getModel());
      if (frames.size() > 0){
	EditorFrame f = (EditorFrame)getCurrentFrame();
	f.makePalette(jar);
      }
    }
    finally{
      pFrame.setVisible(false);
      for (int i = 0 ; i<frames.size() ; i++){
	EditorFrame frame = (EditorFrame) frames.elementAt(i);
	frame.getStatusBar().resetStatus();
      }
    }
  }

  private void openResource (String resourceLocation) {
    EditorFrame f = (EditorFrame) getCurrentFrame ();
    String urlString;
    if (resourceLocation.indexOf ("://") < 0) {
      File localFile = new File (resourceLocation);
      urlString = "file:///" +
	localFile.getAbsolutePath().replace ('\\', '/');
    } else
      urlString = resourceLocation;
    T2URLDirectoryModel directoryModel 
      = new T2URLDirectoryModel(true,false,true,null,null);
    URLFile urlFile = directoryModel.makeFileFromPath (urlString);
    f.openResource (urlFile);
  }
  
  void removeFrame(EditorFrame frame)
  {
    frames.removeElement(frame);
    if (frames.size() == 0 && standalone)
      System.exit(0);
  }

  void setBeanSelection(String newBeanSelection, PaletteButton newPaletteButton)
  {
    if ((currentBeanSelection == null) && (newBeanSelection == null)) return;
    if ((currentBeanSelection != null) && 
	(currentBeanSelection.equals(newBeanSelection)))
      return;
    for (int i = 0 ; i<frames.size() ; i++){
      EditorFrame frame = (EditorFrame) frames.elementAt(i);
      currentBeanSelection = newBeanSelection;
      currentPaletteButton = newPaletteButton;
      frame.setBeanSelection(newBeanSelection);
    }
  }

  void exit()
  {
    for (int i = 0 ; i<frames.size() ; i++)
      {
	EditorFrame frame = (EditorFrame) frames.elementAt(i);
	frame.setVisible(false);
	frame.dispose();
      }
    if (standalone)
      System.exit(0);
  }
  
  void resetStatus(){
    for (int i = 0 ; i<frames.size() ; i++)
      {
	EditorFrame frame = (EditorFrame) frames.elementAt(i);
	frame.getStatusBar().resetStatus();
      }
  }

  static void updateConnectionColors(){
    for (int i = 0 ; i<frames.size() ; i++)
      {
	EditorFrame frame = (EditorFrame) frames.elementAt(i);
	frame.updateConnectionColors();
      }
  }

  public static void main (String[] args)
  {
    try{
      //UIManager.setLookAndFeel("com.sun.java.swing.plaf.motif.MotifLookAndFeel");
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    }
    catch (Exception ex) {
      throw new com.gensym.util.UnexpectedException(ex);
    }

    for (int j=0; j<args.length; j++)
      {
	if (args[j].equals("-noout"))
	  setNoOutput();
	//System.out.println ("Arg # " + j + " = " + args[j]);
      }
    
    standalone = true;
    Beans.setDesignTime(true);

    ComponentEditor application = new ComponentEditor(args);

    Preferences.establishPreferences();

    CmdLineArgHandler cmdLineHandler = application.commandLineArguments;
    String title = cmdLineHandler.getOptionValue ("-title");
    if (title == null)
      title = "Component Editor";
    
    if (cmdLineHandler.getSwitchValue ("-ndb"))
      doubleBuffer = false;

    if (cmdLineHandler.getSwitchValue ("-ech"))
      Preferences.currentPreferences.setCustomHookupsAllowed(true);
    String syntaxArg =  cmdLineHandler.getOptionValue ("-syntax");
    if (syntaxArg != null){
      if (syntaxArg.equals("java"))
	Preferences.currentPreferences.setSyntax(SyntaxType.JAVA);
      else if (syntaxArg.equals("G2Script"))
	Preferences.currentPreferences.setSyntax(SyntaxType.G2SCRIPT);
    }

    // Initialize ActiveX Beanifier if running on Windows
    if (windowsPlatform)
      application.beanifier = new BeanXporter();

    // make one EditorFrame and start it up
    EditorFrame frame = new EditorFrame(title, application);

    java.awt.Image image = java.awt.Toolkit.getDefaultToolkit().getImage(frame.getClass().getResource("gensym_logo.gif"));
    if (image != null)
      frame.setIconImage(image);

    UiApplication.setCurrentFrame(frame);
    application.frames.addElement(frame);
    frame.startup();
    String geometry = getGeometryInformation();
    if (geometry != null)
      setBoundsForFrame(frame, geometry);


    //For now, register the one frame for test dialogs
    DefaultDialogLauncher.registerFrame(frame);

    //Load Jars specified in preferences
    FileNameVector jarNames = Preferences.currentPreferences.getDefaultJars();
    if (jarNames != null)
      for (int i=0; i<jarNames.size(); i++)
	application.loadJar((String)jarNames.elementAt(i), true);

    // Load Jars if Specified on command-line
    String[] jarsToLoad = cmdLineHandler.getOptionValues ("-jars");
    if (jarsToLoad == null)
      jarsToLoad = cmdLineHandler.getOptionValues ("-jar");
    if (jarsToLoad != null)
      for (int i=0; i<jarsToLoad.length; i++)
	application.loadJar (jarsToLoad[i], true);
    // Load resource if specified on command-line
    String resourcePath = cmdLineHandler.getOptionValue ("-resource");
    if (resourcePath == null)
      resourcePath = cmdLineHandler.getOptionValue ("-res");
    if (resourcePath != null)
      application.openResource (resourcePath);
    
    com.gensym.net.g2.G2ProtocolRegistry.loadInterpreters();
    application.hostName = cmdLineHandler.getOptionValue ("-host");
    application.portName = cmdLineHandler.getOptionValue ("-port");
    G2ConnectionInfo info = null;
    if (application.hostName != null && 
	application.portName != null){
      info = new G2ConnectionInfo(application.hostName,
				  application.portName);
      G2File.registerG2ConnectionInfo(info);
    }

    noAutoActivationOfRetrievers =
      cmdLineHandler.getSwitchValue("-noAutoActivationOfRetrievers");

    LaunchHelpFile.solarisBrowser = cmdLineHandler.getOptionValue("-browser");
  }
}

