
package com.gensym.demos.wksppanel;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import com.gensym.wksp.*;
import com.gensym.classes.KbWorkspace;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.ntw.util.*;
import com.gensym.dlg.*;
import com.gensym.ui.menu.awt.*;
import com.gensym.ui.toolbar.*;
import com.gensym.ui.*;
import com.gensym.util.symbol.G2ClassSymbols;
import com.gensym.shell.util.ConnectionManager;

public class BrowserApplication extends com.gensym.shell.util.TW2Application {

  /**
   * Objects that we need to save for later reference.
   */
  private ActionListener commandHandler;

  private MenuItem openXn, closeXn, getWksp;

  private MultipleWorkspacePanel multiWkspPanel;

  private TwAccess connection;

  private PropertyChangeSupport propChangeSupport;

  private Command XnCommand, TwCommand;

  /**
   * Constants for identifying commands
   */
  private static final String
    MAIN_MENU = "main",		// Menu Labels
    FILE_MENU = "file",
    TW_MENU   = "tw";

  public static final String
    CONNECTION = "connection",	// Property Names
    MULTI_WKSP_PANEL = "multiWkspPanel";

  private static Resource i18n = Resource.getBundle ("com/gensym/demos/wksppanel/MenuLabels");

  /**
   * The main method of the class simply creates a new
   * BrowserApplication and displays its top-level
   * Frame.
   */
  public static void main (String[] args) {
    BrowserApplication applcn = new BrowserApplication (args);
    applcn.getCurrentFrame().setVisible (true);
  }

  /**
   * The constructor initializes the frame and its
   * contents (the MultipleWorkspaceView and the MenuBar).
   */
  public BrowserApplication (String[] args) {
    super (args, true);
    Frame f;
    propChangeSupport  = new PropertyChangeSupport (this);
    MenuBar mb = setupMenu ();
    String title = getTitleInformation ();
    setCurrentFrame (f = new Frame (title != null ? title : "BrowserApplication"));
    f.setMenuBar (mb);
    f.add (setupToolBar (), BorderLayout.NORTH);
    String geometry = getGeometryInformation ();
    if (geometry == null)
      f.setBounds (0, 0, 600, 400);
    else {
      Rectangle desiredBounds = parseBounds (geometry);
      f.setBounds (desiredBounds.x, desiredBounds.y, desiredBounds.width, desiredBounds.height);
    }
    f.add (multiWkspPanel = new MultipleWorkspacePanel (), BorderLayout.CENTER);
    f.addWindowListener(new WindowAdapter() {
      @Override
      public void windowClosing(WindowEvent e) {
	System.exit(0);
      }
    });
    com.gensym.dlgruntime.DialogManager.registerFrame (f);
    com.gensym.dlgruntime.DefaultDialogLauncher.registerFrame (f);
  }

  /**
   * Constructs the menu-bar.
   * Hold references to Commands that we will need
   * later.
   */
  private MenuBar setupMenu () {
    CMenuBar mb = new CMenuBar ();
    CMenu fileMenu = new CMenu (i18n.getString (FILE_MENU));
    fileMenu.add (XnCommand = new ConnectionCommandImpl (this));
    fileMenu.addSeparator ();
    fileMenu.add (new ExitCommandImpl (this));
    CMenu twMenu = new CMenu (i18n.getString (TW_MENU));
    twMenu.add (TwCommand = new TwCommandImpl (this));

    mb.add (fileMenu);
    mb.add (twMenu);
    return mb;
  }

  /**
   * Constructs the tool-bar for the application.
   */
  private ToolBar setupToolBar () {
    ToolBar tb = new ToolBar ();
    tb.add (XnCommand);
    tb.add (TwCommand);
    return tb;
  }
  
  /**
   * Returns the current connection of the
   * Application, which may be null, if no
   * connection has been established yet.
   */
  @Override
  public TwAccess getConnection () {
    return connection;
  }

  /**
   * The method that is used to set or reset
   * the connection for this Application. This is a
   * bound property of the Application.
   */
  @Override
  public void setConnection (TwAccess newCxn) {
    boolean connected = (newCxn != null);
    if (connected) {
      try {
	newCxn.addWorkspaceShowingListener (multiWkspPanel);
      } catch (G2AccessException gae) {
	new WarningDialog (null, "Error Setting Connection", true, gae.toString (), null).setVisible (true);
      }
    } else {
      try {
	KbWorkspace[] showingWorkspaces = multiWkspPanel.getWorkspaces ();
	System.out.println ("Removing " + showingWorkspaces.length + " workspaces!");
	for (int i=0; i<showingWorkspaces.length; i++)
	  multiWkspPanel.removeWorkspace (showingWorkspaces[i]);
	Rectangle frameRect = getCurrentFrame().getBounds ();
	getCurrentFrame().setBounds(frameRect.x, frameRect.y,
				    frameRect.width + 1, frameRect.height + 1);
	connection.removeWorkspaceShowingListener (multiWkspPanel);
      } catch (G2AccessException gae) {
	new WarningDialog (null, "Error Disconnecting Connection", true, gae.toString (), null).setVisible (true);
      }
    }
    TwAccess oldConnection = connection;
    connection = newCxn;
    firePropertyChange (CONNECTION, oldConnection, connection);
  }

  /**
   *
   */
  public void addPropertyChangeListener (PropertyChangeListener listener) {
    propChangeSupport.addPropertyChangeListener (listener);
  }

  /**
   *
   */
  public void removePropertyChangeListener (PropertyChangeListener listener) {
    propChangeSupport.removePropertyChangeListener (listener);
  }

  /**
   *
   */
  private void firePropertyChange (String propertyName, Object oldValue, Object newValue) {
    propChangeSupport.firePropertyChange (propertyName, oldValue, newValue);
  }
  
  /**
   * Since we do not allow multiple connections,
   * we do not have a ConnectionManager
   */
  @Override
  public ConnectionManager getConnectionManager () {
    return null;
  }


  public void addWorkspace (KbWorkspace wksp) {
    multiWkspPanel.addWorkspace (wksp, true);
    multiWkspPanel.setCurrentWorkspace (wksp);
  }

}
