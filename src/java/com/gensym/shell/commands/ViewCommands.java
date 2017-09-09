/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ViewCommands.java
 *
 */
package com.gensym.shell.commands;

import java.util.Hashtable;
import java.awt.Rectangle;
import java.awt.Window;
import java.awt.Frame;
import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.WindowEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowListener;
import com.gensym.core.UiApplication;
import com.gensym.dlg.WarningDialog;
import com.gensym.jgi.TimeoutException;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.KbMessageTableView;
import com.gensym.ntw.util.MessageBoard;
import com.gensym.ntw.util.Logbook;
import com.gensym.ntw.util.WindowUtil;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.TW2Application;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;

import javax.swing.JDialog;

import com.gensym.util.Symbol;
import com.gensym.classes.LogbookParameters;
import com.gensym.classes.MessageBoardParameters;
import com.gensym.classes.SystemTable;
import com.gensym.ntw.util.KbMessageListener;
import com.gensym.ntw.util.KbEvent;
import com.gensym.shell.util.LogbookMessageBoardView;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import com.gensym.jgi.G2CommunicationErrorEvent;

/**
 * A command that enables display of the G2
 * operator-logbook and message-board displays.
 *
 */
public final class ViewCommands extends AbstractCommand implements KbMessageListener {

  public static final String VIEW_LOGBOOK = "ViewLogbook";
  public static final String VIEW_MESSAGE_BOARD = "ViewMessageBoard";

  private static final String shortResource = "LogbookMessageBoardShortResource";
  private static final String longResource = "LogbookMessageBoardLongResource";
  private static final String mnemonicResource = "MnemonicResource";

  private Resource shortBundle = Resource.getBundle("com/gensym/shell/commands/LogbookMessageBoardShortResource");
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Messages");
  private UiApplication app;
  private ConnectionManager connectionManager;
  private TwAccess currentConnection;
  private Hashtable visibleViews = new Hashtable ();
  private Hashtable previousBounds = new Hashtable ();
  private boolean mdiMode;
  private static final Symbol LOGBOOK_PARAMETERS_ = Symbol.intern("LOGBOOK-PARAMETERS");
  private static final Symbol MESSAGE_BOARD_PARAMETERS_ = Symbol.intern("MESSAGE-BOARD-PARAMETERS");
  private ShowThread showThread;
  private boolean alwaysShowMessageBoard = false;
  private boolean alwaysShowLogBook = false;

  /*
   * APIs to force to always show message board and log book or not
   * @undocumented
   */
  public void setAlwaysShowMessageBoard(boolean alwaysShow){
    this.alwaysShowMessageBoard = alwaysShow;
  }

  /*
   * @undocumented
   */
  public boolean getAlwaysShowMessageBoard(){
    return this.alwaysShowMessageBoard;
  }

  /*
   * @undocumented
   */
  public void setAlwaysShowLogBook(boolean alwaysShow){
    this.alwaysShowLogBook = alwaysShow;
  }

  /*
   * @undocumented
   */
  public boolean getAlwaysShowLogBook(){
    return this.alwaysShowLogBook;
  }

  /**
   * Create a ViewCommands for the given application.
   * The command enables display of the logbook and
   * message-board of the current connection.
   * If the application is a TwApplication or a TW2MDIApplication,
   * the command is initialized either with the
   * ConnectionManager (for a multiple-connection application)
   * or the current connection (for a single-connection application)
   * @param app the UiApplication for which this command is being used
   * @see       com.gensym.ntw.TwAccess
   * @see       com.gensym.shell.util.TWApplication#getConnection
   * @see       com.gensym.shell.util.TWApplication#getConnectionManager
   */
  public ViewCommands(UiApplication app){
    super (new CommandInformation[]{
      new CommandInformation(VIEW_LOGBOOK, true, shortResource, longResource,
			     "view-logbook.gif", null, null, true,
			     mnemonicResource, null),
      new CommandInformation(VIEW_MESSAGE_BOARD, true, shortResource, longResource,
			     "view-messageboard.gif", null, null, true,
			     mnemonicResource, null)});
    showThread = new ShowThread();
    showThread.start();
    this.app = app;

    if (app instanceof TW2Application){
      connectionManager = ((TW2Application)app).getConnectionManager();
      currentConnection = ((TW2Application)app).getConnection();
    }
    else if (app instanceof TW2MDIApplication){
      connectionManager = ((TW2MDIApplication)app).getConnectionManager();
      currentConnection = ((TW2MDIApplication)app).getConnection();
    }

    if (connectionManager != null) {
      currentConnection = connectionManager.getCurrentConnection ();
      connectionManager.addContextChangedListener(new ConnectionChangedListener());
    }
    updateAvailability();
  }

  private void updateAvailability(){
    setAvailable(VIEW_LOGBOOK, (currentConnection != null));
    setAvailable(VIEW_MESSAGE_BOARD, (currentConnection != null));
  }

  /**
   * Performs the action of the command.
   * Do not call directly.
   */
  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (!isAvailable(cmdKey))
      throw new IllegalStateException(i18n.format("CommandIsUnavailable",
						  cmdKey));
      showView(cmdKey, true);
  }

  protected void hideView(LogbookMessageBoardView view){
    try {
      view.disposeView();
      visibleViews.remove (view.getKey());
    } catch(G2AccessException ex){
      new WarningDialog(app.getCurrentFrame(),
			i18n.getString("Error"), true,
			i18n.format("CommunicationError", ex.toString()),
			null).setVisible(true);
      Trace.exception(ex);
    }
  }

  private static String getKey(String viewType, TwAccess connection) {
    return Integer.toString(connection.hashCode()) + ":" + viewType; // "xxxx:MESSAGE-BOARD"
  }

  private void showView(String key, boolean alwaysShow){
    String viewkey = getKey(key, currentConnection);
    LogbookMessageBoardView view = (LogbookMessageBoardView) visibleViews.get (viewkey);
    if (view != null && key != VIEW_MESSAGE_BOARD) {
      view.handleShow();
      return;
    }
    if (!alwaysShow &&
	key == VIEW_LOGBOOK &&
	view != null) {
      boolean liftLogbookToTop = false;
      try {
	liftLogbookToTop =
	  ((LogbookParameters)(view.getParameters())).getLiftLogbookToTopWhenNewPagesAreAdded();
      } catch(G2AccessException ex){
	Trace.exception(ex);
      }
      if (!liftLogbookToTop)
	return;
    }
    if (view == null) {
      try {
	view = createView(app, currentConnection, key, alwaysShow);
	if (view != null)
	  visibleViews.put (viewkey, view);
      } catch(TimeoutException ex){
	Trace.exception(ex);
	try {
	  view = createView(app, currentConnection, key, alwaysShow);
	  if (view != null)
	    visibleViews.put (viewkey, view);
	} catch (G2AccessException ex2) {
	  Trace.exception(ex2);
	}
      } catch(G2AccessException ex){
	Trace.exception(ex);
      }
    }
  }

  private LogbookMessageBoardView createView(UiApplication app,
					     TwAccess connection,
					     String key,
					     boolean alwaysShow)
       throws G2AccessException
  {
    String viewkey = getKey(key, currentConnection);
    SystemTable parameters=null;
    int width = 400, height = 400;
    Rectangle bounds = (Rectangle)previousBounds.get(viewkey);
    if (key == VIEW_LOGBOOK) {
      LogbookParameters logParam =
	(LogbookParameters)currentConnection.getUniqueNamedItem(LOGBOOK_PARAMETERS_,LOGBOOK_PARAMETERS_);
      parameters = logParam;
      if (!alwaysShow &&
	  !logParam.getLiftLogbookToTopWhenNewPagesAreAdded())
	return null;
      width = logParam.getWidthForPages();
      height = logParam.getHeightForPages();
    } else {
      MessageBoardParameters mbParam =
	(MessageBoardParameters)currentConnection.getUniqueNamedItem(MESSAGE_BOARD_PARAMETERS_,
								     MESSAGE_BOARD_PARAMETERS_);
      parameters = mbParam;
      width = mbParam.getInitialWidthOfMessageBoard();
      height = mbParam.getInitialHeightOfMessageBoard();
    }
    if (alwaysShow == false)
      return null;
    return createView(app, parameters, currentConnection, viewkey, width, height, bounds);
  }

  /**
   *@undocumented
   */
  protected LogbookMessageBoardView createView(UiApplication app,
					       SystemTable parameters,
					       TwAccess connection,
					       String key,
					       int defaultWidth,
					       int defaultHeight,
					       Rectangle previousBnds)
       throws G2AccessException
  {
    if (mdiMode) {
      ViewDocument doc = new ViewDocument(app, parameters, currentConnection, key);
      ((com.gensym.mdi.MDIFrame)app.getCurrentFrame()).getManager().addDocument(doc);
      if (previousBnds != null)
	doc.setBounds(previousBnds);
      else
	doc.setSize(defaultWidth, defaultHeight);
      return doc;
    } else {
      ViewDialog dlg = new ViewDialog(app, parameters, currentConnection, key);
      dlg.key = key;
      centerWindowInWindow((Window)dlg, (Window)app.getCurrentFrame(), defaultWidth, defaultHeight);
      if (previousBnds != null)
	dlg.setBounds(previousBnds);
      dlg.setVisible (true);
      return dlg;
    }
  }

  public boolean getMDIMode(){
    return mdiMode;
  }

  public void setMDIMode(boolean mdiMode){
    this.mdiMode = mdiMode;
  }

  private static void centerWindowInWindow(Window child,
					   Window parent,
					   int childWidth,
					   int childHeight) {
    Rectangle bnds = parent.getBounds();
    int x = bnds.x+bnds.width/2;
    int y = bnds.y+bnds.height/2;
    child.setBounds(x-childWidth/2,y-childHeight/2,
		    childWidth, childHeight);
  }
  @Override
  public void receivedInitialContents (KbEvent event){}
  @Override
  public void kbMessageAdded(KbEvent event){
    // Changed by PCP 07/11/2001 to rely on API settings to always show or not
    if (event.getID() == KbEvent.KB_LOGBOOK_MESSAGE_ADDED)
      showThread.showView(VIEW_LOGBOOK, alwaysShowLogBook);
    else if (event.getID() == KbEvent.KB_MESSAGE_BOARD_MESSAGE_ADDED)
      showThread.showView(VIEW_MESSAGE_BOARD, alwaysShowMessageBoard);
  }
  @Override
  public void kbMessageDeleted(KbEvent event){}
  /**
   * Sets the connection for the command
   * to be the given connection. This is to
   * be called only in a single-connection
   * application. Multiple connection
   * application context changes are handled
   * through the ConnectionManager class. The
   * connection can be set to null to indicate
   * that there is no current connection in the
   * application.
   */
  public void setConnection(TwAccess connection){
    if (connectionManager == null){
      if (((currentConnection != null) && ((!currentConnection.equals(connection)))) ||
	  ((currentConnection == null) && (connection != null)))
	setCurrentConnection(connection);
    }
    //else
    //throw new IllegalStateException(i18n.getString("CantCallSetCxnInMultiCxnApp"));
  }

  private void setCurrentConnection(TwAccess connection){
    try {
      if (currentConnection != null)
	currentConnection.getKb().removeKbMessageListener(this);
      currentConnection = connection;
      updateAvailability();
      if (currentConnection != null)
	currentConnection.getKb().addKbMessageListener(this);
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }

  class ConnectionChangedListener implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      setCurrentConnection(e.getConnection());
    }
  }


  class ViewDocument extends com.gensym.shell.util.TW2Document
  implements LogbookMessageBoardView, PropertyChangeListener, G2ConnectionListener {
    private SystemTable parameters;
    private KbMessageTableView logbookOrMessageBoard;
    private TwAccess connection;
    private String key;
    ViewDocument(UiApplication app,
		 SystemTable parameters,
		 TwAccess connection,
		 String key) throws G2AccessException{
      super(connection);
      this.parameters = parameters;
      this.key = key;
      if (key.indexOf(ViewCommands.VIEW_LOGBOOK) > -1){
	logbookOrMessageBoard = new Logbook(connection, (LogbookParameters)parameters);
	setTitle(shortBundle.format("LogbookFor", connection.toShortString()));
      } else {
	logbookOrMessageBoard = new MessageBoard(connection, (MessageBoardParameters)parameters);
	setTitle(shortBundle.format("MessageBoardFor", connection.toShortString()));
      }
      getContentPane().add(logbookOrMessageBoard, BorderLayout.CENTER);
      addPropertyChangeListener(ViewDocument.this);
      connection.addG2ConnectionListener(ViewDocument.this);
      setSize(400, 300);
    }
    @Override
    public void g2ConnectionClosed(G2ConnectionEvent event){
      cleanup ();
    }
    @Override
    public void g2IsPaused(G2ConnectionEvent event) {}
    @Override
    public void g2IsResumed(G2ConnectionEvent event) {}
    @Override
    public void g2IsReset(G2ConnectionEvent event) {}
    @Override
    public void g2IsStarted(G2ConnectionEvent event){}
    @Override
    public void g2MessageReceived(G2ConnectionEvent event){}
    @Override
    public void communicationError(G2CommunicationErrorEvent error_event){}
    @Override
    public void g2ConnectionInitialized(G2ConnectionEvent event){}
    @Override
    public void readBlockage(G2ConnectionEvent event){}
    @Override
    public void writeBlockage(G2ConnectionEvent event){}
    @Override
    public void propertyChange(PropertyChangeEvent e) {
      if (e.getPropertyName().equals(IS_CLOSED_PROPERTY) ||
	  isClosed()) {
	previousBounds.put(key, getBounds());
	cleanup();
      }
    }
    private void cleanup () {
      hideView(ViewDocument.this);
      removePropertyChangeListener(ViewDocument.this);
      if (connection != null)
	connection.removeG2ConnectionListener(ViewDocument.this);
      dispose ();
      connection = null;
    }

    @Override
    public void handleShow() {
      setVisible(true);
      try {
	setIcon(false);
	toFront();
	setSelected(true);
      } catch (java.beans.PropertyVetoException pve) {
	  Trace.exception(pve);
      }
    }

    @Override
    public SystemTable getParameters() {
      return parameters;
    }

    @Override
    public String getKey() {
      return key;
    }
    @Override
    public void disposeView() throws G2AccessException{
      logbookOrMessageBoard.dispose();
    }
  }

  class ViewDialog extends JDialog implements LogbookMessageBoardView{
    private KbMessageTableView logbookOrMessageBoard;
    private G2ConnectionListener xnAdapter;
    private TwAccess connection;
    private String key;
    private SystemTable parameters;

    ViewDialog(UiApplication app, SystemTable parameters, final TwAccess connection, final String key)
	 throws G2AccessException{
      super(app.getCurrentFrame());
      this.parameters = parameters;
      this.connection = connection;
      if (key.indexOf(ViewCommands.VIEW_LOGBOOK) > -1){
	logbookOrMessageBoard = new Logbook(connection, (LogbookParameters)parameters);
	setTitle(shortBundle.format("LogbookFor", connection.toShortString()));
      } else {
	logbookOrMessageBoard = new MessageBoard(connection, (MessageBoardParameters)parameters);
	setTitle(shortBundle.format("MessageBoardFor", connection.toShortString()));
      }
      getContentPane().add(logbookOrMessageBoard, BorderLayout.CENTER);
      addWindowListener(new WindowAdapter () {
	@Override
	public void windowClosing(WindowEvent event){
	  cleanup ();
	}
      });
      connection.addG2ConnectionListener (xnAdapter = new G2ConnectionAdapter () {
	@Override
	public void g2ConnectionClosed(G2ConnectionEvent event){
	  cleanup ();
	}
      });
      setSize(400, 300);
      WindowUtil.centerFrame(app.getCurrentFrame(), this);
      //setVisible(true);
    }

    @Override
    public SystemTable getParameters() {
      return parameters;
    }

    @Override
    public String getKey() {
      return key;
    }

    private void cleanup () {
      connection.removeG2ConnectionListener (xnAdapter);
      dispose ();
      setVisible (false);
      hideView(ViewDialog.this);
      connection = null;
      xnAdapter = null;
    }

    @Override
    public void handleShow() {
      setVisible(true);
    }

    @Override
    public void setVisible(boolean visible) {
      if (!visible)
	previousBounds.put(key, getBounds());
      super.setVisible(visible);
    }

    @Override
    public void disposeView() throws G2AccessException{
      logbookOrMessageBoard.dispose();
    }
  }

  class ShowThread extends Thread {
    String key;
    boolean alwaysShow;

    public synchronized void showView(String key, boolean alwaysShow){
      this.key = key;
      this.alwaysShow = alwaysShow;
      notify();
    }
    @Override
    public synchronized void run() {
      while (true) {
	if (key != null)
	  ViewCommands.this.showView(key, alwaysShow);
	key = null;
	alwaysShow = false;
	try {
	  wait();
	} catch (InterruptedException ie) {
	  Trace.exception(ie);
	}
      }
    }

  }

}
