/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TW2Document.java
 *
 */
package com.gensym.shell.util;

import com.gensym.core.GensymApplication;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import com.gensym.mdi.MDIApplication;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIManager;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;

/**
 *  This abstract class may be subclassed to create G2-related documents.
 *  Subclasses of this class may be used in both single and multiple connection
 *  applications.
 *  TW2Documents have the following behavior:
 *<LI> When the connection associated with a TW2Document is closed, the
 *  TW2Document also closes.  
 *<LI>In a TW2MDIApplication that uses the ConnectionManager to
 *  manage and open connections, when the connection associated with a 
 *  TW2Document is no longer the current connection, the TW2Document will
 *  lose focus; and when a TW2Document is selected (gains focus), the current 
 *  connection is set to the connection associated with the TW2Document.
 *
 * @see com.gensym.shell.util.TW2MDIApplication
 * @see com.gensym.shell.util.ConnectionManager
 */


/*Note: If the application is not a TW2MDIApplication or if it does not use
  our ConnectionManager, automatic unfocus and switching current cxn will
  not work.  This is not harmful.  If the ConnectionManager is used for more, 
  consider putting the ConnectionManager in the constructor (fan-out is 
  WorkspaceDocumentFactory and maybe more).
*/
public abstract class TW2Document extends MDIDocument{

  private static ConnectionManager connectionManager = null;
  private TwAccess connection;
  private ContextChangedListener contextChangedListener;
  private G2ConnectionAdapter g2ConnectionAdapter;
  private PropertyChangeAdapter propertyChangeAdapter;

  static
  {
    GensymApplication app = MDIApplication.getApplication();
    if (app instanceof MDIApplication)
      {
	MDIApplication mdiApp = (MDIApplication)app;
	if (mdiApp instanceof TW2MDIApplication)
	  connectionManager = 
	    ((com.gensym.shell.util.TW2MDIApplication)mdiApp).getConnectionManager();
      }
  }

  /**
   *  Creates a document that uses the MDIFrame's default menu bar and toolbar panel.
   *  This constructor may only be used if the application is a subclass of
   *  MDIApplication.
   */
  public TW2Document(TwAccess connection){
    this(connection,((MDIFrame)MDIApplication.getCurrentFrame()).getDefaultMenuBar(), 
	 ((MDIFrame)MDIApplication.getCurrentFrame()).getDefaultWindowMenu(),
	 ((MDIFrame)MDIApplication.getCurrentFrame()).getDefaultToolBarPanel());
  }

  /**
   *  Creates a document with the specified menu bar and toolbar panel.
   *  When this document has focus, its menu bar and toolbar panel will
   *  be visible.
   */
  public TW2Document(TwAccess connection, JMenuBar wkspMenuBar, 
		     JMenu wkspWindowMenu, MDIToolBarPanel toolBarPanel){
    super(wkspMenuBar, wkspWindowMenu, toolBarPanel);
    if (connection == null) 
      throw new IllegalArgumentException("Connection can not be null");//i18n!
    this.connection = connection;
    g2ConnectionAdapter = new G2ConnectionAdapter();
    connection.addG2ConnectionListener(g2ConnectionAdapter);
    if (connectionManager != null){
      contextChangedListener = new ContextChangedAdapter();
      connectionManager.addContextChangedListener(contextChangedListener);
    }
    addPropertyChangeListener(new PropertyChangeAdapter());
  }
  
  /** 
   *  Returns the connection for this document.
   */
  public TwAccess getConnection(){
    return connection;
  }

  /** 
   * Returns the connection manager obtained from TW2MDIApplication. If the
   *  application is not a TW2MDIApplication or does not use the ConnectionManager
   *  null is returned.
   */
  protected static ConnectionManager getConnectionManager(){
    return connectionManager;
  }

  @Override
  public void setSelected(boolean selected) throws java.beans.PropertyVetoException{
    super.setSelected(selected);
    if ((connection!= null)&&(connection.isAlive())){
      if ((selected) && (connectionManager != null)) {
	connectionManager.setCurrentConnection(connection);
      }
    }
  }

  private boolean isCleanedUp;

  /**
   * @returns true if it performed any cleanup, false otherwise.
   */
  boolean cleanupOnClosing() {
    if (isCleanedUp)
      return false;
    isCleanedUp = true;
    //Trace.exception(new Exception());
    // because of a Swing 1.1 bug, this method gets called twice,
    // so need to check the g2ConnectionAdapter

    if (connection != null)
      connection.removeG2ConnectionListener(g2ConnectionAdapter);
    g2ConnectionAdapter = null;

    if (connectionManager != null)
      connectionManager.removeContextChangedListener(contextChangedListener);
    contextChangedListener = null;
    return true;
  }

  class G2ConnectionAdapter extends com.gensym.jgi.G2ConnectionAdapter{
    @Override
    public void g2ConnectionClosed(G2ConnectionEvent event){
      try{
	if (connectionManager != null)
	  connectionManager.removeContextChangedListener(contextChangedListener);
	connection.removeG2ConnectionListener (this);
	setClosed(true);
	connection = null;
      }
      catch(java.beans.PropertyVetoException ex){
	Trace.exception(ex);
      }
    }
  }

  class ContextChangedAdapter implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent event){
      TwAccess currentConnection = event.getConnection();
      if (isSelected()){
	if ((currentConnection == null)||(!currentConnection.equals(connection))){
	  try{
	    setSelected(false);
	  }
	  catch(java.beans.PropertyVetoException ex){
	    //just ignore
	  }
	}
      }
    }
  }

  class PropertyChangeAdapter implements PropertyChangeListener {
    @Override
    public void propertyChange(PropertyChangeEvent e) {
      if (e.getPropertyName().equals(IS_CLOSED_PROPERTY)){
	if (isClosed()) {
	  removePropertyChangeListener(this);
	  cleanupOnClosing();
	}
      }
    }
  }
}

