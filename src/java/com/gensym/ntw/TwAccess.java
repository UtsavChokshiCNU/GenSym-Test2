/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TwAccess.java
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.ntw;

import java.net.MalformedURLException;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2AccessInitiationException;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.message.*;
import com.gensym.irm.IconRenderingManager;
import com.gensym.classes.Item;
import com.gensym.classes.TrendChart;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.UserMenuChoice;
import com.gensym.classes.UiClientSession;
import com.gensym.classes.Kb;
import com.gensym.ntw.util.FileProgressListener;
import com.gensym.ntw.util.FileProgressEvent;
import com.gensym.dlgruntime.DialogManager;
import com.gensym.ntw.util.UnsolicitedDialogListener;
import com.gensym.ntw.util.UnsolicitedDialogEvent;
import com.gensym.ntw.util.PackagePreparationListener;
import com.gensym.ntw.util.PackagePreparationEvent;

/**
 * This interface class provides the outbound methods for
 * access to workspace methods in G2
 *
 * @version 1.0 22 May 1977
 *
 * @author Robert Penny
 */

public interface TwAccess extends G2Access {
  

  /**
   * @undocumented
   */
  public Structure getDialog (Item itm, Symbol userMode, Structure locale) throws G2AccessException;


  /**
   * @undocumented
   */
  public Structure representWorkspace (KbWorkspace workspace) throws G2AccessException;


  /**
   * @undocumented
   */
  public void decacheEvents(Integer subscriptionHandle);


  /**
   * @undocumented
   */
  public boolean unrepresentWorkspace (int subscriptionIndex) throws G2AccessException;


  /**
   * @undocumented
   */
  public Structure representTrendChart(Item item, //int itemHandle,
				       TrendChart client,
				       Object userData) throws G2AccessException;


  /**
   * @undocumented
   */
  public boolean unrepresentTrendChart (int subscriptionHandle) throws G2AccessException;

  /**
   * Sets the user-mode associated with this particular session.
   * @param newUserMode the mode to change to
   * @exception G2AccessException if there is an error while communicating
   *   with G2 or if the call is in error or if the user is not authorized
   *   to change to the new mode
   * @see #getUserMode
   */
  public void setUserMode (Symbol newUserMode) throws G2AccessException;


  /**
   * Returns the current user mode associated with this particular session
   * @return the current mode
   * @exception G2AccessException if there is an error while communicating
   *   with G2
   */
  public Symbol getUserMode () throws G2AccessException;


  /**
   * Returns all named workspaces in the remote G2.
   * Clients can use this to obtain a root set of Items
   * after making a connection
   * @return a Sequence of named KbWorkspace items
   * exception G2AccessException if there is an error while communicating
   *   with G2
   */
  public Sequence getNamedWorkspaces () throws G2AccessException;


    /**
   * Adds the specified listener to receive workspace-showing events from this
   * connections. Such events are generated when G2 tries to execute the show
   * or hide actions. These actions can apply to all ui-client-items or can
   * be restricted to specific ones. If the session associated with this
   * connection is one of the applicable targets then a WorkspaceShowingEvent
   * containing the show or hide notification is broadcast to all registered
   * listeners
   * @param listener the workspace-showing listener to add
   * @see com.gensym.jgi.WorkspaceShowingListener
   * @see com.gensym.jgi.WorkspaceShowingEvent
   * exception G2AccessException if there is an error while communicating
   *   with G2
   */
  public void addWorkspaceShowingListener(WorkspaceShowingListener listener) throws G2AccessException;


  /**
   * Removes the specified listener so that it no longer receives workspace-showing
   * events from this connection.
   * @param listener the workspace-showing listener to remove
   * @see com.gensym.jgi.WorkspaceShowingListener
   * @see com.gensym.jgi.WorkspaceShowingEvent
   * exception G2AccessException if there is an error while communicating
   *   with G2
   */
  public void removeWorkspaceShowingListener(WorkspaceShowingListener listener) throws G2AccessException;

  /**
   * @undocumented
   * Adds the specified listener to receive field edit events from this
   * connection. Such events are generated when G2 tries to perform a field
   * edit on a message. These actions apply to a single ui-client-items.
   * If the session associated with this connection is one of the applicable
   * targets then a FieldEditEvent containing the field edit action
   * notification is broadcast to all registered listeners
   * @param listener the field edit listener to add
   * @see com.gensym.ntw.util.FieldEditListener
   * @see com.gensym.ntw.FieldEditEvent
   * exception G2AccessException if there is an error while communicating
   *   with G2
   */
  public void addFieldEditListener(FieldEditListener listener)
       throws G2AccessException;

  /**
   * @undocumented
   * Removes the specified listener so that it no longer receives field edit
   * events from this connection.
   * @param listener the field edit listener to remove
   * @see com.gensym.ntw.util.FieldEditListener
   * @see com.gensym.ntw.FieldEditEvent
   * exception G2AccessException if there is an error while communicating
   *   with G2
   */
  public void removeFieldEditListener(FieldEditListener listener) throws G2AccessException;

  /**
   * @undocumented
   */       
  public boolean updateFieldEdit(String newFieldEditValue)
       throws G2AccessException;

  /**
   * @undocumented
   */       
  public boolean finishFieldEditAndRecordStatus(Symbol newStatus)
       throws G2AccessException;

  /**
   * Returns the description of the format named by the argument
   * @param formatName the name of the format
   * @return a Structure with the attributes of the format such as ...
   * @exception if there is an error while communicating
   *   with G2
   */
  public Structure getFormatInfo(Symbol formatName) throws G2AccessException;


  /**
   * @undocumented
   */
  public Structure subscribeToModules() throws G2AccessException;


  /**
   * @undocumented
   */
  public void unsubscribeToModules() throws G2AccessException;


  /**
   * @undocumented? pbk? jed?
   */
  public IconRenderingManager getIconManager ();


  /**
   * Returns the DialogManager associated with this connection.
   * This DialogManager can be used to request editing and other
   * dialogs for items retrieved throught this connection.
   * @return the DialogManager for this connection
   */
  public DialogManager getDialogManager ();


  /**
   * Returns the Kb object associated with this connection.
   * The Kb object is unique per G2 and can be used to get
   * data and notifications of changes to the module structure
   * in that G2.
   * @return the Kb object
   */
  public Kb getKb ();



  /**
   * Retrieves a user-menu-choice by its label and applicable-class.
   * @param label the menu-label of the user-menu-choice
   * @param applicableClass the G2 class for which the menu-choice applies
   * @exception if there is an error while communicating
   *   with G2
   */
  public UserMenuChoice getUserMenuChoice(Symbol label,
					  Symbol applicableClass)
       throws G2AccessException;

  public void addTwConnectionListener (TwConnectionListener listener);

  public void removeTwConnectionListener (TwConnectionListener listener);


  /**
   * @undocumented
   * Add a PackagePreparationListener, who will be informed of any PackagePreparation events for
   * a G2 connection.
   *@param listener The PackagePreparationListener to inform.
   */
  public void addPackagePreparationListener(PackagePreparationListener listener);

  /**
   * @undocumented    
   * Remove a PackagePreparationListener, who was previously listening for PackagePreparation
   * events.
   *@param listener The PackagePreparationListener to inform.
   */
  public void removePackagePreparationListener(PackagePreparationListener listener);

  /**
   * Indicates if this TwAccess has an active login session
   * with G2. This is necessary to call some methods on
   * this Object.
   * @return true if the TwAccess is logged in, false otherwise
   */
  public boolean isLoggedIn();

  /**
   * Returns the ui-client-session for this connection.
   * The session object has a one-to-one relationship with this
   * connection, which persists for the lifetime of both.
   * @deprecated use retrieveSession instead
   * @return the session object
   */
  public com.gensym.classes.UiClientSession getSession ();

  /**
   * Hack for three-tier (middle tier has no session
   * to pass to g2-get-updated-workspace-information
   * @undocumented
   */
  public UiClientSession retrieveSession(Object requestor);

  /**
   * The UiClientSession for this TwAccess is the object in G2 that
   * represents "this window" for this TwAccess.
   */
  public UiClientSession retrieveSession();

  public void login() throws G2AccessException;

  public void login(LoginRequest login) throws G2AccessException;

  public void logout() throws G2AccessException;

  /**
   * @deprecated
   * @see #login
   */
  public void loginSession() throws G2AccessException;

  /**
   * @deprecated
   * @see #login
   */
  public void loginSession(LoginRequest login) 
  throws G2AccessException ;
  
  /** @undocumented */
  public void sendItemToG2SideEditingContext(Item item, Integer parsingContext)
       throws G2AccessException;

  /**
   * @undocumented    
   * Add a FileProgressListener, who will be informed of the status of
   * files being loaded or saved.
   *@param listener The FileProgressListener to inform.
   */       
  public void addFileProgressListener(FileProgressListener listener)
       throws G2AccessException;

  /**
   * @undocumented    
   * Removes the FileProgressListener so that it will no longer be
   * informed of the status of files being loaded or saved.
   *@param listener The FileProgressListener to remove;
   */       
  public void removeFileProgressListener(FileProgressListener listener)
       throws G2AccessException;

  /**
   *@undocumented
   */       
  public void removeUnsolicitedDialogListener(UnsolicitedDialogListener listener)
       throws G2AccessException;

  /**
   *@undocumented
   */       
  public void addUnsolicitedDialogListener(UnsolicitedDialogListener listener)
       throws G2AccessException;       

  /**
   * @undocumented
   */
  // This is used to get rid of the ModuleMappings table in the
  // StubClassLoader.
  public void clearModuleMappings();
}

