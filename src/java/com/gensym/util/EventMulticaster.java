/*
 * @(#)EventMulticaster.java	1.0 97/10/22
 * 
 * Copyright (c) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 
 */
package com.gensym.util;

import java.util.EventListener;
import java.io.Serializable;
import java.io.ObjectOutputStream;
import java.io.IOException;

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

public class EventMulticaster implements EventListener, ItemListener, WorkspaceListener, DefinitionListener, VariableValueListener {

  protected final EventListener a, b;

  /**
   * Creates an event multicaster instance which chains listener-a
   * with listener-b.
   * @param a listener-a
   * @param b listener-b
   */ 
  protected EventMulticaster(EventListener a, EventListener b) {
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
   * a new AWTEventMulticaster instance which chains a with b.
   * @param a event listener-a
   * @param b event listener-b
   */
  protected static EventListener addInternal(EventListener a, EventListener b) {
    if (a == null){
    	return b;
    }
    if (b == null){
    	return a;
    }
    return new EventMulticaster(a, b);
  }
  
  /** 
   * Returns the resulting multicast listener after removing the
   * old listener from listener-l.
   * If listener-l equals the old listener OR listener-l is null, 
   * returns null.
   * Else if listener-l is an instance of AWTEventMulticaster, 
   * then it removes the old listener from it.
   * Else, returns listener l.
   * @param l the listener being removed from
   * @param oldl the listener being removed
   */
  protected static EventListener removeInternal(EventListener l, EventListener oldl) {
    if (l == null || l.equals(oldl)) {
      return null;
    } else if (l instanceof EventMulticaster) {
      return ((EventMulticaster)l).remove(oldl);
    } else {
      return l;		// it's not here
    }
  }
      
  
  /*
   * Serialization support.  Huh? -vkp, 10/22/97
   */
  
  protected void saveInternal(ObjectOutputStream s, String k) throws IOException {
    if (a instanceof EventMulticaster) {
      ((EventMulticaster)a).saveInternal(s, k);
    }
    else if (a instanceof Serializable) {
      s.writeObject(k);
      s.writeObject(a);
    }
    
    if (b instanceof EventMulticaster) {
      ((EventMulticaster)b).saveInternal(s, k);
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
    else if (l instanceof EventMulticaster) {
      ((EventMulticaster)l).saveInternal(s, k);
    }
    else if (l instanceof Serializable) {
      s.writeObject(k);
      s.writeObject(l);
    }
  }

  /**
   * Adds class-listener-a with class-listener-b and returns
   * the resulting multicast listener.
   * @param a class-listener-a
   * @param b class-listener-b
   */
  public static DefinitionListener add (DefinitionListener a, DefinitionListener b) {
    return (DefinitionListener) addInternal (a, b);
  }
     
  /**
   * Removes the old class-listener from class-listener-list and
   * returns the resulting multicast listener.
   * @param l class-listener-l
   * @param old-l the class-listener being removed
   */
  public static DefinitionListener remove (DefinitionListener l, DefinitionListener oldl) {
    return (DefinitionListener) removeInternal (l, oldl);
  }
  
  /**
   * Handles the classNameChanged event by invoking
   * classNameChanged methods on listener-a and listener-b.
   * @param e the class change event
   */
  @Override
  public void classNameChanged (DefinitionEvent e) {
    ((DefinitionListener)a).classNameChanged (e);
    ((DefinitionListener)b).classNameChanged (e);
  }

  /**
     * Handles the classAttributeChanged event by invoking
     * classAttributeChanged methods on listener-a and listener-b.
     * @param e the class change event
     */
  @Override
  public void staticAttributeChanged (DefinitionEvent e) {
    ((DefinitionListener)a).staticAttributeChanged (e);
    ((DefinitionListener)b).staticAttributeChanged (e);
  }

  /**
     * Handles the directSuperiorClassesChanged event by invoking
     * directSuperiorClassesChanged methods on listener-a and listener-b.
     * @param e the class change event
     */
  @Override
  public void directSuperiorClassesChanged (DefinitionEvent e) {
    ((DefinitionListener)a).directSuperiorClassesChanged (e);
    ((DefinitionListener)b).directSuperiorClassesChanged (e);
  }

  /**
   * Handles the deleted event by invoking
   * deleted methods on listener-a and listener-b.
   * @param e the class change event
   */
  @Override
  public void classInheritancePathChanged (DefinitionEvent e) {
    ((DefinitionListener)a).classInheritancePathChanged (e);
    ((DefinitionListener)b).classInheritancePathChanged (e);
  }

  /**
   * Handles the deleted event by invoking
   * deleted methods on listener-a and listener-b.
   * @param e the class change event
   */
  @Override
  public void classSpecificAttributesChanged (DefinitionEvent e) {
    ((DefinitionListener)a).classSpecificAttributesChanged (e);
    ((DefinitionListener)b).classSpecificAttributesChanged (e);
  }

  /**
   * Handles the deleted event by invoking
   * deleted methods on listener-a and listener-b.
   * @param e the class change event
   */
  @Override
  public void deleted (DefinitionEvent e) {
    ((DefinitionListener)a).deleted (e);
    ((DefinitionListener)b).deleted (e);
  }

  /**
     * Adds item-listener-a with item-listener-b and returns
     * the resulting multicast listener.
     * @param a item-listener-a
     * @param b item-listener-b
     */
  public static ItemListener add (ItemListener a, ItemListener b) {
    return (ItemListener) addInternal (a, b);
  }
     
  /**
     * Removes the old item-listener from item-listener-list and
     * returns the resulting multicast listener.
     * @param l item-listener-l
     * @param old-l the item-listener being removed
     */
  public static ItemListener remove (ItemListener l, ItemListener oldl) {
    return (ItemListener) removeInternal (l, oldl);
  }

  /** 
     * Handles the initial values download by invoking
     * receivedInitialValues on listener-a and listener-b.
     * @param initialValues a structure containing the initial values of the
     * attributes of the item.
     */
  @Override
  public void receivedInitialValues (ItemEvent e) {
    ((ItemListener)a).receivedInitialValues (e);
    ((ItemListener)b).receivedInitialValues (e);
  }
  /**
     * Handles the itemChanged event by invoking
     * itemModified methods on listener-a and listener-b
     * @param e the item event
     */
  @Override
  public void itemModified (ItemEvent e) {
    ((ItemListener)a).itemModified (e);
    ((ItemListener)b).itemModified (e);
  }

  /**
     * Handles the itemDeleted event by invoking
     * itemDeleted methods on listener-a and listener-b
     * @param e the item event
     */
  @Override
  public void itemDeleted (ItemEvent e) {
    ((ItemListener)a).itemDeleted (e);
    ((ItemListener)b).itemDeleted (e);
  }

  /**
     * Adds workspace-listener-a with workspace-listener-b and returns
     * the resulting multicast listener.
     * @param a workspace-listener-a
     * @param b workspace-listener-b
     */
  public static WorkspaceListener add (WorkspaceListener a, WorkspaceListener b) {
    return (WorkspaceListener) addInternal (a, b);
  }
     
  /**
     * Removes the old workspace-listener from workspace-listener-list and
     * returns the resulting multicast listener.
     * @param l workspace-listener-l
     * @param old-l the workspace-listener being removed
     */
  public static WorkspaceListener remove (WorkspaceListener l, WorkspaceListener oldl) {
    return (WorkspaceListener) removeInternal (l, oldl);
  }

  /**
   * Adds variable-value-listener-a with variable-value-listener-b and returns
   * the resulting multicast listener.
   * @param a variable-value-listener-a
   * @param b variable-value-listener-b
   */
  public static VariableValueListener add (VariableValueListener a, VariableValueListener b) {
    return (VariableValueListener) addInternal (a, b);
  }
     
  /**
   * Removes the old variable-value-listener from variable-value-listener-list and
   * returns the resulting multicast listener.
   * @param l variable-value-listener-l
   * @param old-l the variable-value-listener being removed
   */
  public static VariableValueListener remove (VariableValueListener l, VariableValueListener oldl) {
    return (VariableValueListener) removeInternal (l, oldl);
  }
  
  /**
   * Handles the receivedInitialDownload callback by invoking
   * receivedInitialDownload on listener-a and listener-b
   * @param e the workspace event
   */
  @Override
  public void receivedInitialDownload (WorkspaceEvent e) {
    ((WorkspaceListener)a).receivedInitialDownload (e);
    ((WorkspaceListener)b).receivedInitialDownload (e);
  }
  /**
   * Handles the workspaceItemAdded event by invoking
   * workspaceItemAdded on listener-a and listener-b
   * @param e the workspace event
   */
  @Override
  public void workspaceItemAdded (WorkspaceEvent e) {
    ((WorkspaceListener)a).workspaceItemAdded (e);
    ((WorkspaceListener)b).workspaceItemAdded (e);
  }

  /**
   * Handles the workspaceItemRemoved event by invoking
   * workspaceItemRemoved on listener-a and listener-b
   * @param e the workspace event
   */
  @Override
  public void workspaceItemRemoved (WorkspaceEvent e) {
    ((WorkspaceListener)a).workspaceItemRemoved (e);
    ((WorkspaceListener)b).workspaceItemRemoved (e);
  }

  /**
   * Handles the workspaceResized event by invoking
   * workspaceResized on listener-a and listener-b
   * @param e the workspace event
   */
  @Override
  public void workspaceResized (WorkspaceEvent e) {
    ((WorkspaceListener)a).workspaceResized (e);
    ((WorkspaceListener)b).workspaceResized (e);
  }

  /**
     * Handles the workspaceItemMoved event by invoking
     * workspaceItemMoved on listener-a and listener-b
     * @param e the workspace event
     */
  @Override
  public void workspaceItemMoved (WorkspaceEvent e) {
    ((WorkspaceListener)a).workspaceItemMoved (e);
    ((WorkspaceListener)b).workspaceItemMoved (e);
  }

  /**
     * Handles the workspaceItemResized event by invoking
     * workspaceItemResized on listener-a and listener-b
     * @param e the workspace event
     */
  @Override
  public void workspaceItemResized (WorkspaceEvent e) {
    ((WorkspaceListener)a).workspaceItemResized (e);
    ((WorkspaceListener)b).workspaceItemResized (e);
  }

  /**
     * Handles the workspaceItemRotated event by invoking
     * workspaceItemRotated on listener-a and listener-b
     * @param e the workspace event
     */
  @Override
  public void workspaceItemRotated (WorkspaceEvent e) {
    ((WorkspaceListener)a).workspaceItemRotated (e);
    ((WorkspaceListener)b).workspaceItemRotated (e);
  }

  /**
     * Handles the workspaceItemColorsChanged event by invoking
     * workspaceItemColorsChanged on listener-a and listener-b
     * @param e the workspace event
     */
  @Override
  public void workspaceItemColorsChanged (WorkspaceEvent e) {
    ((WorkspaceListener)a).workspaceItemColorsChanged (e);
    ((WorkspaceListener)b).workspaceItemColorsChanged (e);
  }

  /**
     * Handles the workspaceItemIconVariablesChanged event by invoking
     * workspaceItemIconVariablesChanged on listener-a and listener-b
     * @param e the workspace event
     */
  @Override
  public void workspaceItemIconVariablesChanged (WorkspaceEvent e) {
    ((WorkspaceListener)a).workspaceItemIconVariablesChanged (e);
    ((WorkspaceListener)b).workspaceItemIconVariablesChanged (e);
  }

  /**
     * handles the workspaceItemAttributesChanged event by invoking
     * workspaceItemAttributesChanged on listener-a and listener-b
     * @param e the workspace event
     */
  @Override
  public void workspaceItemAttributesChanged (WorkspaceEvent e) {
    ((WorkspaceListener)a).workspaceItemAttributesChanged (e);
    ((WorkspaceListener)b).workspaceItemAttributesChanged (e);
  }

  /**
   * Handles the newValue by invoking
   * newValue on listener-a and listener-b
   * @param e the VariableValueEvent
   */
  @Override
  public void valueChanged (VariableValueEvent e) {
    ((VariableValueListener)a).valueChanged (e);
    ((VariableValueListener)b).valueChanged (e);
  }

  /**
   * Handles the receivedInitialValue by invoking
   * receivedInitialValue on listener-a and listener-b
   * @param e the VariableValueEvent
   */
  @Override
  public void receivedInitialValue (VariableValueEvent e) {
    ((VariableValueListener)a).receivedInitialValue (e);
    ((VariableValueListener)b).receivedInitialValue (e);
  }

  @Override
  public String toString () {
    return a + ", " + b;
  }
}
