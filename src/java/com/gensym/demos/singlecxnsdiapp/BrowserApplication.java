
package com.gensym.demos.singlecxnsdiapp;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.MenuBar;
import java.awt.MenuItem;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;

import com.gensym.classes.KbWorkspace;
import com.gensym.dlg.WarningDialog;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnection;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.HostPortPanel;
import com.gensym.shell.util.UserModePanel;
import com.gensym.ui.Command;
import com.gensym.ui.menu.awt.CMenu;
import com.gensym.ui.menu.awt.CMenuBar;
import com.gensym.ui.toolbar.ToolBar;
import com.gensym.wksp.MultipleWorkspacePanel;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;

public class BrowserApplication extends com.gensym.shell.util.TW2Application {

  /**
   * Objects that we need to save for later reference.
   */
  private ActionListener commandHandler;

  private MultipleWorkspacePanel multiWkspPanel;

  private TwAccess connection;

  private PropertyChangeSupport propChangeSupport;

  private Command XnCommand, WorkspaceCommand;
  private ExitCommandImpl exitCommand;

  private int wkspIndex, wkspCount;

  private HostPortPanel hostPortPanel;
  private UserModePanel userModePanel;

  /**
   * Constants for identifying commands
   */
  private static final String
    MAIN_MENU = "main",		// Menu Labels
    TW_MENU   = "tw",
    WORKSPACE_MENU = "workspace";


  public static final String
    CONNECTION = "connection",	// Property Names
    WORKSPACE_INDEX  = "workspace_index",
    WORKSPACE_COUNT  = "workspace_count";

  private static Resource i18n = Resource.getBundle ("com/gensym/demos/singlecxnsdiapp/MenuLabels");

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
    super (args, false);
    JPopupMenu.setDefaultLightWeightPopupEnabled (false);
    JFrame jf;
    propChangeSupport  = new PropertyChangeSupport (this);
    String title = getTitleInformation ();
    setCurrentFrame (jf = new JFrame (title != null ? title : "Workspace Browser"));
    exitCommand = new ExitCommandImpl (jf);
    MenuBar mb = setupMenu ();
    Container f = jf.getContentPane ();
    jf.setMenuBar (mb);
    JPanel toolbarPanel = new JPanel ();
    toolbarPanel.setLayout (new BorderLayout ());
    toolbarPanel.add (setupToolBar (), BorderLayout.WEST);
    toolbarPanel.add (setupXnInfo (), BorderLayout.EAST);
    f.add (toolbarPanel, BorderLayout.NORTH);
    String geometry = getGeometryInformation ();
    if (geometry == null)
      jf.setBounds (0, 0, 600, 400);
    else {
      Rectangle desiredBounds = parseBounds (geometry);
      jf.setBounds (desiredBounds.x, desiredBounds.y, desiredBounds.width, desiredBounds.height);
    }
    f.add (new BorderContainer (multiWkspPanel = new MultipleWorkspacePanel ()),
	   BorderLayout.CENTER);
    com.gensym.dlgruntime.DialogManager.registerFrame (jf);
    com.gensym.dlgruntime.DefaultDialogLauncher.registerFrame (jf);
  }

  /**
   * Constructs the menu-bar.
   * Hold references to Commands that we will need
   * later.
   */
  private MenuBar setupMenu () {
    CMenuBar mb = new CMenuBar ();
    CMenu fileMenu = new CMenu (i18n.getString (TW_MENU));
    fileMenu.add (XnCommand = new ConnectionCommandImpl (this));
    fileMenu.addSeparator ();
    fileMenu.add (exitCommand);
    CMenu twMenu = new CMenu (i18n.getString (WORKSPACE_MENU));
    twMenu.add (WorkspaceCommand = new WorkspaceCommandImpl (this));

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
    tb.addSeparator ();
    tb.add (WorkspaceCommand);
    tb.addSeparator ();
    tb.add (new NavigationCommandImpl (this));
    return tb;
  }

  private Component setupXnInfo () {
    JPanel xnInfoPanel = new JPanel ();
    xnInfoPanel.setMaximumSize(new Dimension(Short.MAX_VALUE,100));
    xnInfoPanel.setLayout(new BoxLayout(xnInfoPanel, BoxLayout.X_AXIS));
    xnInfoPanel.add(Box.createRigidArea(new Dimension(5,1)));
    try {
      hostPortPanel = new HostPortPanel((TwConnection)connection);
      xnInfoPanel.add(hostPortPanel);
    } catch (G2AccessException ex) {
      Trace.exception(ex);
    }
    try {
      userModePanel = new UserModePanel((TwConnection)connection, true);
      xnInfoPanel.add(userModePanel);
    } catch (G2AccessException ex) {
      Trace.exception(ex);
    }
    return (xnInfoPanel);
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
    //System.out.println("BrowserApplicatino.setConnection: "+newCxn);
    boolean connected = (newCxn != null);
    if (connected) {
      try {
	newCxn.addWorkspaceShowingListener (multiWkspPanel);
	hostPortPanel.setConnection((TwConnection)newCxn);
	userModePanel.setConnection((TwConnection)newCxn);
      } catch (G2AccessException gae) {
	new WarningDialog (null, "Error Setting Connection", true, gae.toString (), null).setVisible (true);
      }
    } else { //not connected
      //System.out.println("setConnection: is NOT connected, wkspCount: "+wkspCount);
      try {
	KbWorkspace[] showingWorkspaces = multiWkspPanel.getWorkspaces ();
	//System.out.println ("Removing " + showingWorkspaces.length + " workspaces!");
	for (int i=0; i<showingWorkspaces.length; i++)
	  multiWkspPanel.removeWorkspace (showingWorkspaces[i]);

	Rectangle frameRect = getCurrentFrame().getBounds ();
	getCurrentFrame().setBounds(frameRect.x, frameRect.y,
				    frameRect.width + 1, frameRect.height + 1);
       
	connection.removeWorkspaceShowingListener (multiWkspPanel);
	hostPortPanel.setConnection ((TwConnection)newCxn);
	userModePanel.setConnection ((TwConnection)newCxn);
      } catch (G2AccessException gae) {
	new WarningDialog (null, "Error Disconnecting Connection", true, gae.toString (), null).setVisible (true);
      }
    }
    TwAccess oldConnection = connection;
    connection = newCxn;
    exitCommand.setConnection(connection);
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
    wkspCount++;
    int oldWkspIndex = wkspIndex;
    wkspIndex = wkspCount - 1;
    firePropertyChange (WORKSPACE_COUNT, new Integer (wkspCount), new Integer (wkspCount -1));
    firePropertyChange (WORKSPACE_INDEX, new Integer (wkspIndex), new Integer (oldWkspIndex));
  }

  public void setNext () {
    multiWkspPanel.nextWorkspace ();
    wkspIndex++;
    firePropertyChange (WORKSPACE_INDEX, new Integer (wkspIndex), new Integer (wkspIndex - 1));
  }

  public void setPrevious () {
    multiWkspPanel.previousWorkspace ();
    wkspIndex--;
    firePropertyChange (WORKSPACE_INDEX, new Integer (wkspIndex), new Integer (wkspIndex + 1));
  }

  public int getWorkspaceCount() {
    return wkspCount;
  }

}





