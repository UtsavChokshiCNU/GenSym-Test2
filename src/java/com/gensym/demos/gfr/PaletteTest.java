package com.gensym.demos.gfr;

import com.gensym.classes.KbWorkspace;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.ui.menu.CMenuBar;
import com.gensym.ui.menu.CMenu;
import com.gensym.dlg.MessageDialog;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.commands.WorkspaceCommands;
import com.gensym.shell.commands.ExitCommands;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwGateway;
import com.gensym.clscupgr.gfr.GFRPalette;

public class PaletteTest extends TW2MDIApplication
{
  private static final Symbol KB_WORKSPACE_ = Symbol.intern ("KB-WORKSPACE");  
  private WorkspaceCommands wkspHandler;
  private ExitCommands exitHandler;
  private TwAccess currentConnection;
  
  public PaletteTest(String[] commandLine)
  {
    super(commandLine);
    setCurrentFrame(new MDIFrame("PaletteTest"));
    createMenuBar();
  }

  private void createPaletteToolBar(TwAccess connection,
				    Symbol workspaceName)
  {
    try {
      KbWorkspace paletteWorkspace =
	(KbWorkspace)connection.getUniqueNamedItem(KB_WORKSPACE_, workspaceName);
      
      MDIToolBarPanel panel = new MDIToolBarPanel();
      GFRPalette gfrPalette = new GFRPalette("the palette",
					     connection,
					     paletteWorkspace);    
      panel.add(gfrPalette);
      MDIFrame mdiFrame = (MDIFrame)getCurrentFrame();
      mdiFrame.setDefaultToolBarPanel(panel);
    } catch (G2AccessException paletteError) {
      (new MessageDialog(getCurrentFrame(),
			 "Error Creating Palette Toolbar",
			 true,
			 paletteError.toString(),
			 null)).setVisible(true);
    }      
  }

  public void handleCommandLine()
  {
    G2ConnectionInfo connectionInfo = getG2ConnectionInformation();
    TwAccess cxn = null;
    if (connectionInfo != null) {
      try {
	cxn = TwGateway.openConnection(connectionInfo.getBrokerURL(),
				       connectionInfo.getHost(),
				       connectionInfo.getPort());
	if (cxn != null) {
	  cxn.loginSession ();
	  setConnection(cxn);
	  String wkspName = commandLineArguments.getOptionValue ("-palette");
	  if (wkspName != null) {
	    Symbol workspaceName = Symbol.intern(wkspName.toUpperCase());
	    createPaletteToolBar(cxn, workspaceName);
	  } else {
	    (new MessageDialog(getCurrentFrame(),
			       "GFR Palette Workspace Not Specified",
			       true,
			       "Usage:(all options are required)\n -host <host-name>\n -port <port-number>\n -palette <gfr-palette-workspace-name>\n",
			       null)).setVisible(true);
	  }
	} 
      } catch (G2AccessException connectionError) {
	(new MessageDialog(getCurrentFrame(),
			   "Error Establishing Connection",
			   true,
			   connectionError.toString(),
			   null)).setVisible(true);	
      }
    }
  }

 private void createMenuBar()
  {
    MDIFrame mdiFrame = (MDIFrame)getCurrentFrame();
    CMenuBar menuBar = new CMenuBar();
    CMenu fileMenu = new CMenu("File");
    fileMenu.add(wkspHandler = new WorkspaceCommands(mdiFrame, currentConnection));
    fileMenu.add(exitHandler = new ExitCommands(mdiFrame, currentConnection));
    menuBar.add(fileMenu);
    mdiFrame.setDefaultMenuBar(menuBar);
  }
  
  @Override
  public TwAccess getConnection() {
    return currentConnection;
  }

  @Override
  public void setConnection(TwAccess connection) {
    this.currentConnection = connection;
    wkspHandler.setConnection(connection);
    exitHandler.setConnection(connection);    
  }

  @Override
  public ConnectionManager getConnectionManager() {
    return null;
  }
  
  public static void main(String[] commandLine)
  {
    PaletteTest app = new PaletteTest(commandLine);
    MDIFrame mdiFrame = (MDIFrame)app.getCurrentFrame();
    mdiFrame.setVisible(true);
    app.handleCommandLine();
  }
  
}


