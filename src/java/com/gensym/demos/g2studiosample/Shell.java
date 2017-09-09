package com.gensym.demos.g2studiosample;

import java.util.StringTokenizer;
import java.util.Vector;
import java.io.File;
import java.io.IOException;
import java.awt.Toolkit;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Image;
import java.awt.Window;
import java.awt.BorderLayout;
import java.net.URL;
import java.net.MalformedURLException;
import javax.swing.UIManager;
import javax.swing.Icon;
import javax.swing.JMenu;
import javax.swing.JSplitPane;
import javax.swing.JPanel;
import javax.swing.border.BevelBorder;
import javax.swing.event.HyperlinkListener;
import com.gensym.ui.LookAndFeel;
import com.gensym.core.UiApplication;
import com.gensym.core.ToolBarFactory;
import com.gensym.core.MenuFactory;
import com.gensym.uitools.utils.HideableSplitPane;
import com.gensym.uitools.utils.ComponentVisibilityEventSource;
import com.gensym.uitools.utils.Preferences;
import com.gensym.uitools.utils.SplashScreen;
import com.gensym.uitools.utils.JarInstaller;
import com.gensym.uitools.utils.FontUtil;
import com.gensym.uitools.utils.StatusDisplay;
import com.gensym.uitools.utils.VariableWidthBevelBorder;
import com.gensym.uitools.utils.WaitAnimator;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.dlg.WarningDialog;
import com.gensym.gcg.GeneratedDialogFactory;
import com.gensym.gcg.AttributePanelFactory;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.ModuleInformation;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.mdi.MDIFrame;
import com.gensym.dlgruntime.DialogManager;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.LoginRequest;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.shell.util.WebBrowserDocument;
import com.gensym.shell.util.WebBrowserCreator;
import com.gensym.shell.util.LocationComboBox;
import com.gensym.shell.commands.ComponentVisibilityCommands;
import com.gensym.demos.g2studiosample.commands.BrowserCommands;

public class Shell extends TW2MDIApplication 
{
  static {
    com.gensym.jgi.JGInterface.setGSILoopThreadPriority(6);
  }
  public static final String SOUTHERN_TOOLBAR = "Southern Toolbar";
  public static final String WINDOW_MENU = "Window Menu";  
  private static final Resource i18ui = Resource.getBundle ("com/gensym/demos/g2studiosample/UiLabels");
  private static final String DOWNLOADING_PLUGIN = i18ui.getString("downloadingPlugin");
  private static final String REGISTERING_MODULE = i18ui.getString("registeringModule");
  private static final String DONE = i18ui.getString("done");  
  private static final Symbol KB_WORKSPACE_ = Symbol.intern ("KB-WORKSPACE");
  private static final String splashImageResource = "/com/gensym/demos/g2studiosample/g2studio-splash.jpg";  
  private static SplashScreen splashScreen;
  private static Dimension screenDimensions = Toolkit.getDefaultToolkit().getScreenSize ();
  private static Image splashImage
  = Toolkit.getDefaultToolkit().getImage(Shell.class.getResource(splashImageResource));  
  private ConnectionManager cxnMgr;
  private LoginRequest loginRequest;
  private boolean waiting;
  private LocationComboBox locationComboBox;
  private StatusDisplay statusDisplay;
  private WaitAnimator waitBar;  
  private G2StudioCommands studioCommands;
  private Preferences preferences;
  private G2StudioListeners studioListeners;
  private G2StudioGeneratedDialogFactory defaultDialogFactory;
  private G2StudioIconicStatusBar iconicStatusBar;
  private static boolean initializing;
  static {
    try {
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    } catch (Exception e) {
      Trace.exception(e);
    }
    LookAndFeel.setUseSnappyLookAndFeel(true);
  }
  
  public static void main (String[] args) {
    initializing = true;
    showSplashScreen();
    Shell application = new Shell(args);
    Frame f = application.getCurrentFrame();
    Dimension frameSize = f.getSize();
    f.setLocation ((screenDimensions.width - frameSize.width) >> 1,
		   (screenDimensions.height - frameSize.height) >> 1);
    f.setVisible(true);
    hideSplashScreen();
    initializing = false;
    application.setWaiting(true);
    application.goHome();    
    application.handleCommandLineArguments();
    application.setWaiting(false);        
  }
  
  /**
   * Creates the application shell.
   * Construction of elements occurs as follows:
   * 1. Creates connection manager.
   * 2. Create the frame.
   * 3. Initializes generated dialog factory.
   * 4. Initializes toolbar factory.
   * 5. Initializes the status display.
   * 6. Initializes the frame.
   * 7. Initializes menu factory.   
   * 8. Initializes preferences.
   */
  public Shell (String[] args) {
    super (args);
    setStatus("Creating connection manager", G2StudioStatusBar.MAIN_DISPLAY_AREA);      
    cxnMgr = new ConnectionManager();
    setStatus("Creating frame", G2StudioStatusBar.MAIN_DISPLAY_AREA);      
    MDIFrame currentFrame = createMDIFrame();
    setCurrentFrame(currentFrame);
    setStatus("Initializing dialogs", G2StudioStatusBar.MAIN_DISPLAY_AREA);      
    DialogManager.setGeneratedDialogFactory(createGeneratedDialogFactory());
    setStatus("Creating main toolbars", G2StudioStatusBar.MAIN_DISPLAY_AREA);          
    setToolBarFactory(null, createDefaultToolBarFactory());
    setStatus("Creating main status bar", G2StudioStatusBar.MAIN_DISPLAY_AREA);              
    statusDisplay = createStatusDisplay();//make into a factory
    setStatus("Configuring frame", G2StudioStatusBar.MAIN_DISPLAY_AREA);                  
    configureFrame(currentFrame);
    setStatus("Creating menus", G2StudioStatusBar.MAIN_DISPLAY_AREA);      
    MenuFactory menuFactory = createDefaultMenuFactory();
    currentFrame.setDefaultWindowMenu(menuFactory.getMenu(WINDOW_MENU));
    setMenuFactory(null, menuFactory);
    setStatus("Setting user preferences", G2StudioStatusBar.MAIN_DISPLAY_AREA);                      
    setPreferences(createPreferences());
    setStatus(DONE, G2StudioStatusBar.MAIN_DISPLAY_AREA);                      
  }

  protected MDIFrame createMDIFrame() {
    MDIFrame currentFrame = new MDIFrame(i18ui.getString ("title"));
    currentFrame.setSize(screenDimensions);
    Image image = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource("gensym_logo.gif"));
    currentFrame.setIconImage(image);
    return currentFrame;
  }

  protected StatusDisplay createStatusDisplay() {
    return new G2StudioStatusBar(cxnMgr);
  }
  
  protected MenuFactory createDefaultMenuFactory() {
    return new G2StudioMenuFactory(this);
  }
  
  protected ToolBarFactory createDefaultToolBarFactory() {
    return new G2StudioToolBarFactory(this);
  }
  
  protected GeneratedDialogFactory createGeneratedDialogFactory() {
    if (defaultDialogFactory == null)
      defaultDialogFactory = new G2StudioGeneratedDialogFactory();
    return defaultDialogFactory;
  }

  protected AttributePanelFactory createAttributePanelFactory() {
    if (defaultDialogFactory == null)
      defaultDialogFactory = new G2StudioGeneratedDialogFactory();
    return defaultDialogFactory;    
  }
    
  protected void configureFrame(MDIFrame currentFrame) {
    G2StudioCommands studioCommands = getG2StudioCommands();
    setStatus("Creating properties panel", G2StudioStatusBar.MAIN_DISPLAY_AREA);      
    G2StudioPropertiesPanel propertiesPanel = new G2StudioPropertiesPanel(createAttributePanelFactory());
    G2StudioPromptPanel promptPanel = new G2StudioPromptPanel();
    setStatus("Creating palettes", G2StudioStatusBar.MAIN_DISPLAY_AREA);      
    PalettePanel palette = new PalettePanel();
    
    HideableSplitPane propertiesPane
      = new HideableSplitPane(JSplitPane.VERTICAL_SPLIT, propertiesPanel, promptPanel);
    propertiesPane.setMinimumSize(new Dimension(20,20));
    JSplitPane splitPane1 = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,
					   currentFrame.getManager(), propertiesPane);
    //splitPane1.setDividerLocation(600);
    com.gensym.ntw.util.VersionHelper.setResizeWeight(splitPane1, 1.0);
    JPanel browserPanel = studioCommands.getBrowserCommands().
      getBrowserPanel();
    JSplitPane browserPane;
    if (browserPanel instanceof ComponentVisibilityEventSource)
      browserPane =
	new HideableSplitPane (JSplitPane.VERTICAL_SPLIT,
			       (ComponentVisibilityEventSource)browserPanel,
			       palette);
    else
      browserPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT,
					      browserPanel, palette);
    com.gensym.ntw.util.VersionHelper.setResizeWeight(browserPane, .6);    
    JSplitPane splitPane2 =
      new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, browserPane, splitPane1);
    currentFrame.getContentPane().add(splitPane2);

    setStatus("Creating layout toolbar", G2StudioStatusBar.MAIN_DISPLAY_AREA);          
    ToolBarFactory defaultToolBarFactory = getToolBarFactory(null);
    if (defaultToolBarFactory != null)
      currentFrame.getContentPane().add(defaultToolBarFactory.getToolBarComponent(SOUTHERN_TOOLBAR),
					BorderLayout.SOUTH);

    ComponentVisibilityCommands frameVisibilityCommands = studioCommands.getFrameVisibilityCommands();    
    frameVisibilityCommands.addComponent(propertiesPanel, i18ui.getString("properties"), "properties.gif");   
    frameVisibilityCommands.addComponent(promptPanel, i18ui.getString("parsing"));
    frameVisibilityCommands.addComponent(palette, i18ui.getString("palette"), "newItem.gif");

    setStatus("Finalizing connection", G2StudioStatusBar.MAIN_DISPLAY_AREA);              
    studioListeners = new G2StudioListeners(this, propertiesPanel,
					    palette, studioCommands,
					    getIconicStatusBar());
  }

  protected Preferences createPreferences() {
    return new G2StudioPreferences();
  }

  @Override
  protected void updateMenusForConnection(Object key, boolean updateDocs) {
    super.updateMenusForConnection(key, updateDocs);
  }

  @Override
  protected void updateToolBarsForConnection(Object key, boolean updateDocs) {
    super.updateToolBarsForConnection(key, updateDocs);
  }  
  
  public Preferences getPreferences() {
    return preferences;
  }

  public void setPreferences(Preferences preferences) {
    this.preferences = preferences;
    preferences.load();
    registerPlugins(preferences.getPreference(G2StudioPreferences.PLUGINS));    
    resetLocationBoxLoginRequest();    
  }
  
  public void goHome() {
    String homePage = preferences.getPreference(G2StudioPreferences.HOME_PAGE);
    if (homePage != null) 
      setLocation(homePage);
  }
  
  public void setLocation(String location) {
    LocationComboBox locationComboBox = getLocationComboBox();
    locationComboBox.removeItem(location);
    locationComboBox.insertItemAt(location,0);
    locationComboBox.setSelectedItem(location);
  }

  public StatusDisplay getStatusDisplay() {
    return statusDisplay;
  }   
  
  public void setWaiting(boolean waiting) {
    this.waiting = waiting;
    if (waiting)
      waitBar.setBusy();
    else
      waitBar.setIdle();
  }

  public boolean isWaiting() {
    return waiting;
  }

  @Override
  public TwAccess getConnection () {
    return cxnMgr.getCurrentConnection();
  }

  @Override
  public void setConnection(TwAccess connection){}

  @Override
  public ConnectionManager getConnectionManager () {
    return cxnMgr;
  }

  public static Image getSplashImage(){
    return splashImage;
  }

  public static void setSplashImage(Image splashImage){
    Shell.splashImage = splashImage;
  }

  private static final int imageWidth = 450, imageHeight = 321;//hack
  private static com.gensym.uitools.utils.StatusBar splashScreenStatusBar;
  public static void showSplashScreen() {
    if (splashScreen == null) {
      splashScreen = new SplashScreen(splashImage, imageWidth, imageHeight+20);
      
      splashScreenStatusBar = new com.gensym.uitools.utils.StatusBar(1);
      splashScreenStatusBar.setBackground(java.awt.Color.black);
      splashScreenStatusBar.setForeground(java.awt.Color.white);
      splashScreenStatusBar.getTextField(0).setHorizontalAlignment(javax.swing.JTextField.CENTER);
      splashScreen.setLayout(new BorderLayout());
      splashScreen.add(splashScreenStatusBar, BorderLayout.SOUTH);
      splashScreen.setBorder(new javax.swing.border.LineBorder(java.awt.Color.lightGray,3));
    }
    splashScreen.setLocation((screenDimensions.width - imageWidth) >> 1,
			     (screenDimensions.height - imageHeight ) >> 1);    
    splashScreen.setVisible(true);
  }

  public static void hideSplashScreen () {
    if (splashScreen != null) {
      splashScreen.setVisible(false);
      splashScreen = null;
    }
  }
    
  public boolean installModulePlugin(String url, int fileSize) throws G2AccessException, IOException
  {
    try {
      setWaiting(true);
      setStatus(DOWNLOADING_PLUGIN+":  " + url, G2StudioStatusBar.MAIN_DISPLAY_AREA);      
      File file;
      if (fileSize == -1) 
	file = JarInstaller.downloadJar(url);
      else
	file = JarInstaller.downloadJar(url, fileSize);
      if (file == null) return false;
      JarInstaller.addURL(file.toURL());
      String plugins = preferences.getPreference(G2StudioPreferences.PLUGINS);
      String jarPath = file.getPath();
      if (plugins == null) 
	plugins=jarPath;
      else if (plugins.indexOf(jarPath) == -1)
	plugins=plugins+";"+jarPath;
      preferences.setPreference(G2StudioPreferences.PLUGINS, plugins);
      preferences.save();
    } finally {
      setWaiting(false);
      setStatus(DONE, G2StudioStatusBar.MAIN_DISPLAY_AREA);
    }
    return true;
  }

  public void registerModule(ModuleInformation module,
			     String moduleRegistrationClassName)
       throws ClassNotFoundException
  {
    try {
      setWaiting(true);
      String moduleName = "no-name";
      try {
	Symbol moduleNameSymbol = module.getTopLevelModule();
	if (moduleNameSymbol != null)
	  moduleName = moduleNameSymbol.toString();
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
      
      setStatus(REGISTERING_MODULE+":  "+ moduleName, G2StudioStatusBar.MAIN_DISPLAY_AREA);
      Class moduleRegistrationClass = JarInstaller.forName(moduleRegistrationClassName);
      
      try {
	moduleRegistrationClass.getMethod
	  (MODULE_REGISTRATION_METHOD_NAME,
	   MODULE_REGISTRATION_METHOD_ARGS).invoke(null, new Object[] {module, this});
      } catch (NoSuchMethodException nsme) {
	Trace.exception(nsme);
      } catch (IllegalAccessException iae) {
	Trace.exception(iae);      
      } catch (java.lang.reflect.InvocationTargetException ite) {
	Trace.exception(ite);
      }
    } finally {
      setWaiting(false);
      setStatus(DONE, G2StudioStatusBar.MAIN_DISPLAY_AREA);      
    }
  }
  private static final String MODULE_REGISTRATION_METHOD_NAME = "register";
  private static final Class[] MODULE_REGISTRATION_METHOD_ARGS = {ModuleInformation.class,
								  UiApplication.class};  


  private void setStatus(String status, int regionIndex) {
    if (initializing) {
      if (splashScreenStatusBar != null)
	splashScreenStatusBar.setStatus(status, 0);
    } else {
      if (statusDisplay != null)
      statusDisplay.setStatus(status, regionIndex);
    }
  }
    
  private void resetLocationBoxLoginRequest() {
    String defaultUserMode = preferences.getPreference(G2StudioPreferences.DEFAULT_USER_MODE);
    String defaultUserName = preferences.getPreference(G2StudioPreferences.DEFAULT_USER_NAME);
    String defaultUserPassword = preferences.getPreference(G2StudioPreferences.DEFAULT_USER_PASSWORD);
    String defaultOkFile = preferences.getPreference(G2StudioPreferences.DEFAULT_OK_FILE);
    loginRequest = 
      new LoginRequest(defaultUserMode==null?null:Symbol.intern(defaultUserMode.toUpperCase()),
		       defaultUserName==null?null:Symbol.intern(defaultUserName.toUpperCase()),
		       defaultUserPassword==null?null:Symbol.intern(defaultUserPassword.toUpperCase()),
		       defaultOkFile);
    LocationComboBox locationComboBox = getLocationComboBox();    
    locationComboBox.setLoginRequest(loginRequest);    
  }
  
  protected void handleCommandLineArguments() {
    Frame f = getCurrentFrame ();
    String title = getTitleInformation();
    if (title != null) f.setTitle(title);
    String geometry = getGeometryInformation();
    if (geometry != null) setBoundsForFrame (f, geometry);
    TwAccess cxn = null;
    try {
      G2ConnectionInfo connectionInfo = getG2ConnectionInformation();
      if (connectionInfo != null) {
	setStatus("Trying to connect to " + connectionInfo.getHost()+":"+connectionInfo.getPort(),
		  G2StudioStatusBar.MAIN_DISPLAY_AREA);      
	cxn = cxnMgr.openConnection(connectionInfo.getBrokerURL(),
				    connectionInfo.getHost(),
				    connectionInfo.getPort());
	if (loginRequest != null)
	  cxn.login (loginRequest);
	else
	  cxn.login ();
	if (studioListeners != null)
	  studioListeners.updateConnection(cxn);
	setStatus("Ready", G2StudioStatusBar.MAIN_DISPLAY_AREA);      
	String wkspName = commandLineArguments.getOptionValue ("-initWksp");
	if (wkspName != null) {
	  setStatus("Showing workspace " + wkspName, G2StudioStatusBar.MAIN_DISPLAY_AREA);      
	  KbWorkspace wksp = (KbWorkspace) cxn.getUniqueNamedItem (KB_WORKSPACE_, Symbol.intern (wkspName));
	  wksp.show (new Structure ());
	}
      }
    } catch (G2AccessException e) {
      Trace.exception(e);
      String errorTitle = (cxn == null ? "Error making Connection" : "Error getting Workspace");
      displayError(errorTitle, e.toString ());
      setStatus("Ready", G2StudioStatusBar.MAIN_DISPLAY_AREA);      
    }
  }
  
  private void displayError(String errorTitle, String errorMsg) {
    new WarningDialog(getCurrentFrame(), errorTitle, true, errorMsg, null).setVisible(true);
  }

  G2StudioIconicStatusBar getIconicStatusBar() {
    if (iconicStatusBar == null)
      iconicStatusBar = new G2StudioIconicStatusBar(getCurrentFrame());
    return iconicStatusBar;
  }

  WaitAnimator getWaitBar() {
    if (waitBar == null) {
      waitBar = new WaitAnimator();
      waitBar.setBorder(new BevelBorder(BevelBorder.LOWERED));
    }
    return waitBar;
  }
  
  LocationComboBox getLocationComboBox() {
    if (locationComboBox == null) {
      locationComboBox = new LocationComboBox(cxnMgr, (MDIFrame)getCurrentFrame(),
					      new WebPageCreator(), getWaitBar());
      locationComboBox.setFont(FontUtil.sanserifPlain11);
    }
    return locationComboBox;
  }
  
  G2StudioCommands getG2StudioCommands() {
    if (studioCommands == null) 
      studioCommands = new G2StudioCommands(this);
    return studioCommands;
  }
  
  private void registerPlugins(String plugins) {
    if (plugins == null) return;
    String[] pluginsArray;
    StringTokenizer tokenizer = new StringTokenizer(plugins, ";");
    Vector pluginsVector = new Vector();
    while(tokenizer.hasMoreElements())
      pluginsVector.addElement(tokenizer.nextElement());
    pluginsArray = new String[pluginsVector.size()];
    pluginsVector.copyInto(pluginsArray);
    for (int i=0;i<pluginsArray.length;i++) {
      try {
	JarInstaller.addURL(new URL("file:\\\\"+pluginsArray[i]));
      } catch (MalformedURLException murle) {
	Trace.exception(murle);
      }
    }
  }
  
  class WebPageCreator implements WebBrowserCreator {
    @Override
    public WebBrowserDocument createWebBrowser() {
      WebBrowserDocument webBrowser = new WebBrowserDocument();
      if (statusDisplay instanceof HyperlinkListener)
	webBrowser.getEditorPane().addHyperlinkListener((HyperlinkListener)statusDisplay);
      return webBrowser;
    }
  }
  
}




