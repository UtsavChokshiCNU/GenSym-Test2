/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   VariableValueListener.java 
 * 
 * 
 */ 

package com.gensym.util;

import java.util.EventListener;

/** A listener interface for Variables or Parameters. This interface
 * is required to receive events regarding the value of a variable or
 * a parameter. An ItemListener <b>will not</b> receive such events.
 * <p>
 * NOTE: this interface will work for <b>both</b> Variables
 * and Parameters.
 * @see com.gensym.classes.VariableOrParameter
 * @see com.gensym.classes.Variable
 * @see com.gensym.classes.Parameter
 */
public interface VariableValueListener extends EventListener {
  /** Called whenever the value of the variable or parameter
   * changes in G2.
   */
  public void valueChanged(VariableValueEvent event);
  /** Called during addVariableValueListener to notify the listener
   * of the variable or parameter's value at the time the subscription
   * was started. Note that the method name uses the singular, unlike
   * the similar method in ItemListener.
   */
  public void receivedInitialValue(VariableValueEvent event);
}
