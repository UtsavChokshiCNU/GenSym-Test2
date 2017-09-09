/*
 * @(#)NtwEventMulticaster.java	1.0 98/02/25
 * 
 * Copyright (c) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 
 */
package com.gensym.ntw.util;

import java.util.EventListener;
import java.io.Serializable;
import java.io.ObjectOutputStream;
import java.io.IOException;

import com.gensym.controls.ItemRetrievalListener;
import com.gensym.controls.ItemRetrievalEvent;
import com.gensym.ntw.WorkspaceShowingListener;
import com.gensym.ntw.WorkspaceShowingEvent;


/**
 * A class which implements efficient and thread-safe multi-cast event 
 * dispatching for events defined in the com.gensym.util package.
 * This class will manage an immutable structure consisting of a chain of 
 * event listeners and will dispatch events to those listeners.  Because
 * the structure is immutable, it is safe to use this API to add/remove
 * listeners during the process of an event dispatch operation.
 *
 * @version 	1.00, 10/22/97
 * @author      vkp
 */

public class NtwEventMulticaster 
implements EventListener, ItemRetrievalListener, KbModuleListener, KbMessageListener,
WorkspaceShowingListener, FileProgressListener, UnsolicitedDialogListener {

  protected final EventListener a, b;

    /**
     * Creates an event multicaster instance which chains listener-a
     * with listener-b.
     * @param a listener-a
     * @param b listener-b
     */ 
  protected NtwEventMulticaster(EventListener a, EventListener b) {
    this.a = a; 
    this.b = b;
  }

    /**
     * Removes a listener from this multicaster and returns the
     * resulting multicast listener.
     * @param oldl the listener to be removed
     */
  protected EventListener remove(EventListener oldl) {
    if (oldl.equals(a)) {
    	return b;
    }
    if (oldl.equals(b)) {
    	return a;
    }
    EventListener a2 = removeInternal(a, oldl);
    EventListener b2 = removeInternal(b, oldl);
    if (a2.equals(a) && b2.equals(b)) {
      return this;	// it's not here
    }
    return addInternal(a2, b2);
  }

    /** 
     * Returns the resulting multicast listener from adding listener-a
     * and listener-b together.  
     * If listener-a is null, it returns listener-b;  
     * If listener-b is null, it returns listener-a
     * If neither are null, then it creates and returns
     * a new NtwEventMulticaster instance which chains a with b.
     * @param a event listener-a
     * @param b event listener-b
     */
  protected static EventListener addInternal(EventListener a, EventListener b) {
    if (a == null) {
    	return b;
    }
    if (b == null){
    	return a;
    }
    return new NtwEventMulticaster(a, b);
  }

    /** 
     * Returns the resulting multicast listener after removing the
     * old listener from listener-l.
     * If listener-l equals the old listener OR listener-l is null, 
     * returns null.
     * Else if listener-l is an instance of NtwEventMulticaster, 
     * then it removes the old listener from it.
     * Else, returns listener l.
     * @param l the listener being removed from
     * @param oldl the listener being removed
     */
  protected static EventListener removeInternal(EventListener l, EventListener oldl) {
    if (l == null || l.equals(oldl)) {
      return null;
    } else if (l instanceof NtwEventMulticaster) {
      return ((NtwEventMulticaster)l).remove(oldl);
    } else {
      return l;		// it's not here
    }
  }
      

    /*
     * Serialization support.  Huh? -vkp, 10/22/97
     */

  protected void saveInternal(ObjectOutputStream s, String k) throws IOException {
    if (a instanceof NtwEventMulticaster) {
      ((NtwEventMulticaster)a).saveInternal(s, k);
    }
    else if (a instanceof Serializable) {
      s.writeObject(k);
      s.writeObject(a);
    }
        
    if (b instanceof NtwEventMulticaster) {
      ((NtwEventMulticaster)b).saveInternal(s, k);
    }
    else if (b instanceof Serializable) {
      s.writeObject(k);
      s.writeObject(b);
    }
  }

  protected static void save(ObjectOutputStream s, String k, EventListener l) throws IOException {
    if (l == null) {
      return;
    } 
    else if (l instanceof NtwEventMulticaster) {
      ((NtwEventMulticaster)l).saveInternal(s, k);
    }
    else if (l instanceof Serializable) {
      s.writeObject(k);
      s.writeObject(l);
    }
  }

    /**
     * Adds item-retrieval-listener-a with item-retrieval-listener-b and returns
     * the resulting multicast listener.
     * @param a item-retrieval-listener-a
     * @param b item-retrieval-listener-b
     */
  public static ItemRetrievalListener add (ItemRetrievalListener a, ItemRetrievalListener b) {
    return (ItemRetrievalListener) addInternal (a, b);
  }
     
    /**
     * Removes the old item-retrieval-listener from item-retrieval-listener-list and
     * returns the resulting multicast listener.
     * @param l item-retrieval-listener-l
     * @param old-l the item-retrieval-listener being removed
     */
  public static ItemRetrievalListener remove (ItemRetrievalListener l, ItemRetrievalListener oldl) {
    return (ItemRetrievalListener) removeInternal (l, oldl);
  }

  /**
     * Adds kb-listener-a with KbModuleListener-b and returns
     * the resulting multicast listener.
     * @param a kb-listener-a
     * @param b kb-listener-b
     */
  public static KbModuleListener add (KbModuleListener a, KbModuleListener b) {
    return (KbModuleListener) addInternal (a, b);
  }
     
  /**
   * Removes the old item-retrieval-listener from item-retrieval-listener-list and
   * returns the resulting multicast listener.
   * @param l item-retrieval-listener-l
   * @param old-l the item-retrieval-listener being removed
   */
  public static KbModuleListener remove (KbModuleListener l, KbModuleListener oldl) {
    return (KbModuleListener) removeInternal (l, oldl);
  }

  /**
     * Adds kb-message-listener-a with kb-message0listener-b and returns
     * the resulting multicast listener.
     * @param a kb-message-listener-a
     * @param b kb-message-listener-b
     */
  public static KbMessageListener add (KbMessageListener a, KbMessageListener b) {
    return (KbMessageListener) addInternal (a, b);
  }
     
  /**
   * Removes the old-kb-message-listener from kb-message-listener-list and
   * returns the resulting multicast listener.
   * @param l kb-message-listener-l
   * @param old-l the kb-message-listener being removed
   */
  public static KbMessageListener remove (KbMessageListener l, KbMessageListener oldl) {
    return (KbMessageListener) removeInternal (l, oldl);
  }

  /**
   * Adds workspace-showing-listener-a with
   * workspace-showing-listener-b and returns
   * the resulting multicast listener.
   * @param a WorkspaceShowing-listener-a
   * @param b WorkspaceShowing-listener-b
   */
  public static WorkspaceShowingListener add (WorkspaceShowingListener a,
					      WorkspaceShowingListener b) {
    return (WorkspaceShowingListener) addInternal (a, b);
  }
     
  /**
   * Removes the old workspace-showing-listener from workspace-showing-listener-list and
   * returns the resulting multicast listener.
   * @param l workspace-showing-listener-l
   * @param old-l the workspace-showing-listener being removed
   */
  public static WorkspaceShowingListener remove (WorkspaceShowingListener l,
						 WorkspaceShowingListener oldl) {
    return (WorkspaceShowingListener) removeInternal (l, oldl);
  }

  /**
   * Adds file-progress-listener-a with
   * file-progresslistener-b and returns
   * the resulting multicast listener.
   * @param a FileProgressListener-a
   * @param b FileProgressListener-b
   */  
  public static FileProgressListener add (FileProgressListener a,
					  FileProgressListener b) {
    return (FileProgressListener) addInternal (a, b);
  }

  /**
   * Removes the old file-progresslistener from file-progress-listener-list and
   * returns the resulting multicast listener.
   * @param l file-progress-listener-l
   * @param old-l the file-progress-listener being removed
   */  
  public static FileProgressListener remove (FileProgressListener l,
					     FileProgressListener oldl) {
    return (FileProgressListener) removeInternal (l, oldl);
  }

  /**
   *@undocumented
   */
  public static UnsolicitedDialogListener add (UnsolicitedDialogListener a,
						UnsolicitedDialogListener b) {
    return (UnsolicitedDialogListener) addInternal (a, b);
  }

  /**
   *@undocumented
   */  
  public static UnsolicitedDialogListener remove (UnsolicitedDialogListener l,
						   UnsolicitedDialogListener oldl) {
    return (UnsolicitedDialogListener) removeInternal (l, oldl);
  }
  
  
    /**
     * Handles the itemRetrieved event by invoking itemRetrieved on
     * listener-a and listener-b.
     * @param e the ItemRetrievalEvent.
     */
  @Override
  public void itemRetrieved(ItemRetrievalEvent e) {
    ((ItemRetrievalListener)a).itemRetrieved(e);
    ((ItemRetrievalListener)b).itemRetrieved(e);
  }

    /**
     * Handles the itemRetrievalFailed event by invoking itemRetrievalFailed on
     * listener-a and listener-b.
     * @param e the ItemRetrievalEvent.
     */
  @Override
  public void itemRetrievalFailed(ItemRetrievalEvent e) {
    ((ItemRetrievalListener)a).itemRetrievalFailed(e);
    ((ItemRetrievalListener)b).itemRetrievalFailed(e);
  }

  /**
     * Handles the reception of the data for KbModuleListeners by invoking
     * receivedInitialDownload on listener-a and listener-b
     * @param e the KbEvent
     */
  @Override
  public void receivedInitialModules (KbEvent e) {
    ((KbModuleListener)a).receivedInitialModules (e);
    ((KbModuleListener)b).receivedInitialModules (e);
  }

  /**
   * Handles the addition of a new module by invoking
   * moduleCreated on listener-a and listener-b
   * @param the KbEvent
   */
  @Override
  public void moduleCreated (KbEvent e) {
    ((KbModuleListener)a).moduleCreated (e);
    ((KbModuleListener)b).moduleCreated (e);
  }

  /**
   * Handles the deletion of a module by invoking
   * moduleDeleted on listener-a and listener-b
   * @param the KbEvent
   */
  @Override
  public void moduleDeleted (KbEvent e) {
    ((KbModuleListener)a).moduleDeleted (e);
    ((KbModuleListener)b).moduleDeleted (e);
  }

  /**
   * Handles the change of the name of a module by invoking
   * moduleNameChanged on listener-a and listener-b
   * @param the KbEvent
   */
  @Override
  public void moduleNameChanged (KbEvent e) {
    ((KbModuleListener)a).moduleNameChanged (e);
    ((KbModuleListener)b).moduleNameChanged (e);
  }

  /**
   * Handles the change in dependency of a module by invoking
   * moduleDependencyChanged on listener-a and listener-b
   * @param the KbEvent
   */
  @Override
  public void moduleDependencyChanged (KbEvent e) {
    ((KbModuleListener)a).moduleDependencyChanged (e);
    ((KbModuleListener)b).moduleDependencyChanged (e);
  }

  /**
   * Handles the Kb clearing by invoking
   * kbCleared on listener-a and listener-b
   * @param the KbEvent
   */
  @Override
  public void kbCleared (KbEvent e) {
    ((KbModuleListener)a).kbCleared (e);
    ((KbModuleListener)b).kbCleared (e);
  }

  @Override
  public void topLevelWorkspaceAdded(KbEvent e){
    ((KbModuleListener)a).topLevelWorkspaceAdded (e);
    ((KbModuleListener)b).topLevelWorkspaceAdded (e);
  }

  @Override
  public void topLevelWorkspaceDeleted(KbEvent e){
    ((KbModuleListener)a).topLevelWorkspaceDeleted (e);
    ((KbModuleListener)b).topLevelWorkspaceDeleted (e);
  }
  

  @Override
  public void receivedInitialContents (KbEvent e) {
    ((KbMessageListener)a).receivedInitialContents (e);
    ((KbMessageListener)b).receivedInitialContents (e);
  }

  @Override
  public void kbMessageAdded (KbEvent e){
    ((KbMessageListener)a).kbMessageAdded (e);
    ((KbMessageListener)b).kbMessageAdded (e);
  }

  @Override
  public void kbMessageDeleted (KbEvent e){
    ((KbMessageListener)a).kbMessageDeleted (e);
    ((KbMessageListener)b).kbMessageDeleted (e);
  }

  @Override
  public void showWorkspace(WorkspaceShowingEvent event) {
    ((WorkspaceShowingListener)a).showWorkspace(event);
    ((WorkspaceShowingListener)b).showWorkspace(event);
  }

  @Override
  public void hideWorkspace(WorkspaceShowingEvent event) {
    ((WorkspaceShowingListener)a).hideWorkspace(event);
    ((WorkspaceShowingListener)b).hideWorkspace(event);
  }

  @Override
  public void addFile(FileProgressEvent event) {
    ((FileProgressListener)a).addFile(event);
    ((FileProgressListener)a).addFile(event);    
  }

  @Override
  public void removeFile(FileProgressEvent event) {
    ((FileProgressListener)a).removeFile(event);
    ((FileProgressListener)a).removeFile(event);    
  }  

  @Override
  public void enterDialog(UnsolicitedDialogEvent event) {
    ((UnsolicitedDialogListener)a).enterDialog(event);
    ((UnsolicitedDialogListener)a).enterDialog(event);    
  }

  @Override
  public void updateDialog(UnsolicitedDialogEvent event) {
    ((UnsolicitedDialogListener)a).updateDialog(event);
    ((UnsolicitedDialogListener)a).updateDialog(event);    
  }  

  @Override
  public void exitDialog(UnsolicitedDialogEvent event) {
    ((UnsolicitedDialogListener)a).exitDialog(event);
    ((UnsolicitedDialogListener)a).exitDialog(event);    
  }  
  
}
