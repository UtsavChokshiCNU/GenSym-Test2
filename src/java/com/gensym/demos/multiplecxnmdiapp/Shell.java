
package com.gensym.demos.multiplecxnmdiapp;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.Window;
import java.awt.BorderLayout;

import com.gensym.classes.KbWorkspace;
import com.gensym.classes.UserMenuChoice;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.LoginRequest;
import com.gensym.shell.util.WorkspaceDocumentFactory;
import com.gensym.shell.commands.ConnectionCommands;
import com.gensym.shell.commands.ExitCommands;
import com.gensym.shell.commands.CondensedG2StateCommands;
import com.gensym.shell.commands.WorkspaceCommands;
import com.gensym.shell.commands.EditCommands;
import com.gensym.shell.commands.ViewCommands;
import com.gensym.shell.commands.ProjectCommands;
import com.gensym.shell.commands.HelpCommands;
import com.gensym.shell.commands.WorkspaceInstanceCommands;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.shell.util.TW2MDIWorkspaceShowingAdapter;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.toolbar.ToolBar;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.ui.RepresentationConstraints;

import javax.swing.Box;
import javax.swing.JMenuBar;
import javax.swing.UIManager;
import javax.swing.SwingConstants;

import com.gensym.ntw.util.KbModuleAdapter;

public class Shell extends TW2MDIApplication {


  private static final Resource i18ui = Resource.getBundle ("com/gensym/demos/multiplecxnmdiapp/UiLabels");
  private ConnectionManager cxnMgr;
  private ConnectionCommands cxnCommand;
  private EditCommands editCommand;
  private ConnectionCommandImpl localCxnCommand;
  private WorkspaceCommands wkspCommand;
  private CondensedG2StateCommands stateCommand;
  private HelpCommands helpCommand;
  private ViewCommands viewCommand;
  private static WorkspaceDocumentFactory shellWkspDocFactory;
  private RepresentationConstraints defaultMenuConstraints = 
                             new RepresentationConstraints(RepresentationConstraints.TEXT_AND_ICON,
							   SwingConstants.LEFT, 
							   SwingConstants.CENTER, 
							   SwingConstants.RIGHT, 
							   SwingConstants.CENTER);
  public static void main (String[] args) throws Exception {
    showSplashScreen ();
    UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    Shell application = new Shell (args);
    Frame f = application.getCurrentFrame();
    TW2MDIWorkspaceShowingAdapter showingAdapter = 
      new TW2MDIWorkspaceShowingAdapter (application.cxnMgr);
    showingAdapter.setWorkspaceDocumentFactory (shellWkspDocFactory);
    application.handleCommandLineArguments ();
    Dimension frameSize = f.getSize ();
    f.setLocation ((screenDimensions.width - frameSize.width) >> 1,
		   (screenDimensions.height - frameSize.height) >> 1);
    f.setVisible (true);
    hideSplashScreen ();
  }

  private static final Symbol KB_WORKSPACE_ = Symbol.intern ("KB-WORKSPACE");
  private static final Symbol ITEM_ = Symbol.intern ("ITEM");

  private void handleCommandLineArguments () {
    Frame f = getCurrentFrame ();
    String title = getTitleInformation();
    if (title != null) f.setTitle(title);
    String geometry = getGeometryInformation();
    if (geometry != null) setBoundsForFrame (f, geometry);
    TwAccess cxn = null;
    try {
      G2ConnectionInfo connectionInfo = getG2ConnectionInformation();
      LoginRequest loginRequest = getLoginRequest ();
      if (connectionInfo != null) {
	cxn = cxnMgr.openConnection(connectionInfo.getBrokerURL(),
				    connectionInfo.getHost(),
				    connectionInfo.getPort());
	if (loginRequest != null)
	  cxn.login (loginRequest);
	else
	  cxn.login ();
	String wkspName = commandLineArguments.getOptionValue ("-initWksp");
	if (wkspName != null) {
	  KbWorkspace wksp = (KbWorkspace) cxn.getUniqueNamedItem (KB_WORKSPACE_, Symbol.intern (wkspName));
	  wksp.show (new Structure ());
	}
      }
    } catch (G2AccessException e) {
      Trace.exception (e);
      String errorTitle = (cxn == null ? "Error making Connection" : "Error getting Workspace");
      displayError (errorTitle, e.toString ());
    }
  }

  public Shell (String[] args) {
    super (args);
    createFrame ();
    setupFields ();
    setupMenuBar ();
    setupToolBar ();
    setupStatusBar ();
    registerShellWorkspaceDocumentFactory ();
  }

  private void registerShellWorkspaceDocumentFactory () {
    shellWkspDocFactory = new ShellWorkspaceDocumentFactoryImpl();
    wkspCommand.setWorkspaceDocumentFactory(shellWkspDocFactory);
  }

  private void setupFields () {
    cxnMgr = new ConnectionManager ();
    cxnCommand = new ConnectionCommands (this);
    localCxnCommand = new ConnectionCommandImpl (cxnMgr);
    editCommand = new EditCommands ((MDIFrame)getCurrentFrame ());
    helpCommand = new HelpCommands ((MDIFrame)getCurrentFrame ());
    viewCommand = new ViewCommands (this);
  }

  private void setupMenuBar () {
    JMenuBar applnMenuBar = new JMenuBar ();
    
    CMenu twMenu = createTwMenu ();
    applnMenuBar.add (twMenu);

    CMenu editMenu = createEditMenu ();
    applnMenuBar.add (editMenu);

    CMenu g2Menu = createG2Menu ();
    applnMenuBar.add (g2Menu);

    CMenu viewMenu = createViewMenu ();
    applnMenuBar.add (viewMenu);

    CMenu wkspMenu = createWkspMenu ();
    applnMenuBar.add (wkspMenu);

    CMenu windowMenu = createWindowMenu ();
    applnMenuBar.add (windowMenu);

    CMenu helpMenu = createHelpMenu ();
    applnMenuBar.add (helpMenu);
    
    ((MDIFrame)getCurrentFrame()).setDefaultMenuBar (applnMenuBar, windowMenu);
  }

  CMenu createTwMenu () {
    CMenu twMenu = new CMenu (i18ui.getString ("twMenu"));
    twMenu.setMnemonic (65 + 't' - 'a');
    //System.out.println ("Mnemonic for Tw menu = " + twMenu.getMnemonic ());
    twMenu.add (cxnCommand, cxnCommand.TW_CONNECT, defaultMenuConstraints);
    twMenu.add (localCxnCommand, localCxnCommand.TW_DISCONNECT, defaultMenuConstraints);
    twMenu.addSeparator ();
    twMenu.add (new ExitCommands (getCurrentFrame (), cxnMgr), defaultMenuConstraints);
    return twMenu;
  }

  CMenu createEditMenu () {
    CMenu menu = new CMenu (i18ui.getString("editMenu"));
    menu.add(editCommand, defaultMenuConstraints);
    return menu;
  }

  CMenu createG2Menu () {
    CMenu g2Menu = new CMenu (i18ui.getString ("g2Menu"));
    stateCommand = new CondensedG2StateCommands (cxnMgr);
    g2Menu.add (stateCommand, defaultMenuConstraints);
    g2Menu.addSeparator ();
    g2Menu.add (new ProjectCommands (getCurrentFrame (), cxnMgr),
		defaultMenuConstraints);
    return g2Menu;
  }

  CMenu createViewMenu () {
    CMenu viewMenu = new CMenu (i18ui.getString ("viewMenu"));
    viewMenu.add (viewCommand, defaultMenuConstraints);
    return viewMenu;
  }

  CMenu createWkspMenu () {
    CMenu wkspMenu = new CMenu (i18ui.getString ("wkspMenu"));
    wkspCommand = new WorkspaceCommands (getCurrentFrame(), cxnMgr);
    wkspMenu.add (wkspCommand, wkspCommand.GET_KBWORKSPACE, defaultMenuConstraints);
    wkspMenu.add (wkspCommand, wkspCommand.NEW_KBWORKSPACE, defaultMenuConstraints);
    wkspMenu.addSeparator ();
    wkspMenu.add(new WorkspaceInstanceCommands((MDIFrame)getCurrentFrame()),
		 defaultMenuConstraints);
    return wkspMenu;
  }

  CMenu createWindowMenu () {
    CMenu windowMenu = new CMenu (i18ui.getString ("windowMenu"));
    windowMenu.add (((MDIFrame)getCurrentFrame()).getManager().getTilingCommand(), defaultMenuConstraints);
    return windowMenu;
  }

  CMenu createHelpMenu () {
    CMenu helpMenu = new CMenu (i18ui.getString ("helpMenu"));
    helpMenu.add (helpCommand);
    return helpMenu;
  }
  

  private void setupToolBar () {
    MDIToolBarPanel panel = new MDIToolBarPanel();
    ToolBar tb = new ToolBar ();
    tb.add (cxnCommand, cxnCommand.TW_CONNECT);
    tb.add (localCxnCommand, localCxnCommand.TW_DISCONNECT);
    tb.addSeparator ();
    tb.add (stateCommand);
    tb.addSeparator ();
    tb.add (wkspCommand, wkspCommand.GET_KBWORKSPACE);
    tb.add (wkspCommand, wkspCommand.NEW_KBWORKSPACE);

    ToolBar tb2 = new ToolBar ();
    try {
      tb2.add (new com.gensym.shell.util.HostPortPanel (cxnMgr));
      tb2.add (new com.gensym.shell.util.UserModePanel (cxnMgr, true));
      tb2.add (Box.createGlue ());
    } catch (G2AccessException gae) {
      Trace.exception (gae);
    }
    panel.add(tb);
    panel.add(tb2);
    ((MDIFrame)getCurrentFrame()).setDefaultToolBarPanel(panel);
  }


  private void setupStatusBar () {
    //((MDIFrame)getCurrentFrame()).getContentPane().add (new StatusBar (), BorderLayout.SOUTH);
  }

  private void createFrame () {
    Frame f = new MDIFrame (i18ui.getString ("title"));
    Image image = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource("gensym_logo.gif"));
    f.setIconImage(image);
    setCurrentFrame (f);
  }

  @Override
  public TwAccess getConnection () {
    return null;
  }

  @Override
  public void setConnection(TwAccess connection){}

  @Override
  public ConnectionManager getConnectionManager () {
    return cxnMgr;
  }

  static Window w;
  static Image splashImage = Toolkit.getDefaultToolkit().getImage(Shell.class.getResource("/com/gensym/demos/multiplecxnmdiapp/snap.gif"));

  private static void showSplashScreen () {
    w = new SplashScreen (splashImage);
  }

  private static void hideSplashScreen () {
    w.setVisible (false);
    w = null;
  }

  private void displayError (String errorTitle, String errorMsg) {
    new com.gensym.dlg.WarningDialog (getCurrentFrame (), errorTitle, true, errorMsg, null).setVisible (true);
  }
  
  static Dimension screenDimensions = Toolkit.getDefaultToolkit().getScreenSize ();

  static class SplashScreen extends Window {
    private Image splashImage;
    private boolean imgDone = false;
    SplashScreen (Image splashImage) {
      super (new Frame ());
      setBackground (Color.black);
      int width = screenDimensions.width;
      int height = screenDimensions.height;
      setBounds ((width - 675 - 4) >> 1, (height - 546 - 4) >> 1, 675 + 4, 546 + 4);
      this.splashImage = splashImage;
      prepareImage (splashImage, this);
      try {
	Thread.sleep (1000);
      } catch (InterruptedException ie) {}
      setVisible (true);
      imgDone = true;
    }

    @Override
    public void paint (Graphics g) {
      if (!imgDone)
	return;
      g.drawImage (splashImage, 2, 2, null);
      g.setColor (Color.white);
      g.setFont (new Font ("sansserif", Font.BOLD, 48));
      g.drawString ("Telewindows 2", 50, 100);
    }
  }
}
