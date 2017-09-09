
package com.gensym.demos.wksppanel;

import java.awt.*;
import java.awt.event.*;
import com.gensym.core.*;
import com.gensym.wksp.*;
import com.gensym.classes.KbWorkspace;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.core.UiApplication;
import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.ntw.util.*;
import com.gensym.dlg.*;
import com.gensym.util.symbol.G2ClassSymbols;

public class SimpleWorkspaceApplication extends UiApplication {

  /**
   * Objects that we need to save for later reference.
   */
  private ActionListener commandHandler;

  private MenuItem openXn, closeXn, getWksp;

  private MultipleWorkspacePanel multiWkspPanel;

  private TwGateway connection;

  /**
   * Constants for identifying commands
   */
  private static final String
    OPEN_CONNECTION = "open",
    CLOSE_CONNECTION = "close",
    EXIT_APPLICATION = "exit",
    GET_WORKSPACE = "get";

  /**
   * The main method of the class simply creates a new
   * SimpleWorkspaceApplication and displays its top-level
   * Frame.
   */
  public static void main (String[] args) {
    SimpleWorkspaceApplication applcn = new SimpleWorkspaceApplication (args);
    applcn.getCurrentFrame().setVisible (true);
  }

  /**
   * The constructor initializes the frame and its
   * contents (the MultipleWorkspaceView and the MenuBar).
   */
  public SimpleWorkspaceApplication (String[] args) {
    super (args, false);
    Frame f;
    commandHandler = new ApplicationCommandHandler ();
    MenuBar mb = setupMenu ();
    String title = getTitleInformation ();
    setCurrentFrame (f = new Frame (title != null ? title : "Simple Workspace Application"));
    f.setMenuBar (mb);
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
  }

  /**
   * Constructs the menu-bar.
   * Hold references to MenuItems that we need to
   * manipulate later.
   */
  private MenuBar setupMenu () {
    MenuBar mb = new MenuBar ();
    Menu fileMenu = new Menu ("File");
    openXn = makeMenuItem ("Open Connection", OPEN_CONNECTION);
    closeXn = makeMenuItem ("Close Connection", CLOSE_CONNECTION);
    closeXn.setEnabled (false);
    MenuItem exit = makeMenuItem ("Exit", EXIT_APPLICATION);
    fileMenu.add (openXn);
    fileMenu.add (closeXn);
    fileMenu.addSeparator ();
    fileMenu.add (exit);

    Menu twMenu = new Menu ("Tw");
    getWksp = makeMenuItem ("Get Workspace", GET_WORKSPACE);
    getWksp.setEnabled (false);
    twMenu.add (getWksp);

    mb.add (fileMenu);
    mb.add (twMenu);
    return mb;
  }

  /**
   * Creates a MenuItem with a specified label and
   * command. Also adds our handler as an ActionListener
   * so that events are routed properly.
   */
  private MenuItem makeMenuItem (String label, String command) {
    MenuItem mi = new MenuItem (label);
    mi.setActionCommand (command);
    mi.addActionListener (commandHandler);
    return mi;
  }

  /**
   * The method that is used to set or reset
   * the connection for this Application.
   */
  private void setConnection (TwGateway newCxn) {
    boolean connected = (newCxn != null);
    closeXn.setEnabled (connected);
    openXn.setEnabled (!connected);
    getWksp.setEnabled (connected);
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
    connection = newCxn;
  }

  /**
   * An implementation of ActionListener that handles
   * the commands dispatched from the Application menus
   */
  class ApplicationCommandHandler implements ActionListener {
    /**
     * The generic entry point simply dispatches
     * based on the command
     */
    @Override
    public void actionPerformed (ActionEvent ae) {
      String actionCommand = ae.getActionCommand ();
      System.out.println (actionCommand + " chosen!");
      if (actionCommand.equals (EXIT_APPLICATION)) {
	System.exit (0);
      } else if (actionCommand.equals (OPEN_CONNECTION)) {
	openConnection ();
      } else if (actionCommand.equals (CLOSE_CONNECTION)) {
	closeConnection ();
      } else if (actionCommand.equals (GET_WORKSPACE)) {
	getWorkspace ();
      }
    }

    /**
     * Opens a new connection to a G2
     */
    private void openConnection () {
      String[] labels = {"Host :", "Port :"};
      String[] initialValues = {"localhost", "1111"};
      StandardDialogClient openHandler = new StandardDialogClient () {
	@Override
	public void dialogDismissed (StandardDialog d, int code) {
	  try {
	    InputDialog inputD = (InputDialog)d;
	    if (inputD.wasCancelled ()) return;
	    String[] results = inputD.getResults ();
	    String host = results[0];
	    String port = results[1];
	    TwGateway connection =
	      (TwGateway)TwGateway.openConnection (host, port);
	    // The following call will fail if the G2 is secure.
	    connection.login();
	    setConnection (connection);
	  } catch (Exception e) {
	    new WarningDialog (null, "Error During Connect", true, e.toString (), null).setVisible (true);
	  }
	}
      };	  

      new ConnectionInputDialog (getCurrentFrame (), "Open Connection",
				 true, labels, initialValues,
				 (StandardDialogClient) openHandler).setVisible (true);
    }

    /**
     * Closes the current connection
     */
    private void closeConnection () {
      setConnection (null);
    }

    /**
     * Get a Workspace in the current connection
     */
    private void getWorkspace () {
      try {
	final Sequence wkspNames = connection.getNamedWorkspaces ();
	int numWksps = wkspNames.size ();
	String[] names = new String [numWksps];
	for (int i=0; i<numWksps; i++)
	  names[i] = ((Symbol)wkspNames.elementAt(i)).getPrintValue();
	StandardDialogClient getHandler = new StandardDialogClient () {
	  @Override
	  public void dialogDismissed (StandardDialog d, int code) {
	    if (d.wasCancelled ()) return;
	    SelectionDialog sd = (SelectionDialog)d;
	    int chosenIndex = sd.getResult ();
	    Symbol wkspName_ = (Symbol) wkspNames.elementAt (chosenIndex);
	    new WorkspaceDownloadThread (multiWkspPanel, connection, wkspName_).start ();
	  }
	};
	new SelectionDialog (getCurrentFrame(), "Get Named Workspace",
			     false, 
			     "Choose Workspace to Display",
			     names, false, -1, true, getHandler).setVisible (true);
      } catch (Exception e) {
	new WarningDialog (null, "Error During Get Workspace", true, e.toString (), null).setVisible (true);
      }
    }
  }

}


/**
 * Private Thread class to fetch the workspace and display it.
 */
class WorkspaceDownloadThread extends Thread {
  
  /**
   * Private variables to store arguments passed to
   * the constructor.
   */
  private MultipleWorkspacePanel multiWkspPanel;
  private TwGateway cxn;
  private Symbol wkspName_;

  /**
   * Save Data
   */
  WorkspaceDownloadThread (MultipleWorkspacePanel multiWkspPanel,
			   TwGateway cxn,
			   Symbol wkspName_) {
    this.multiWkspPanel = multiWkspPanel;
    this.cxn = cxn;
    this.wkspName_ = wkspName_;
  }

  /**
   * Do the task
   */
  @Override
  public void run () {
    try {
      KbWorkspace wksp = (KbWorkspace) cxn.getUniqueNamedItem (G2ClassSymbols.KB_WORKSPACE_, wkspName_);
      multiWkspPanel.addWorkspace (wksp, true);
      multiWkspPanel.setCurrentWorkspace (wksp);
    } catch (G2AccessException gae) {
      new WarningDialog (null, "Error during Get Workspace", true, gae.toString (), null).setVisible (true);
    }
  }
}
