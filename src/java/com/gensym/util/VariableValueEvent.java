/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   VariableValueEvent.java 
 * 
 * 
 */ 

package com.gensym.util;

/** And event that represents the change to the value of a Variable
 * or a Parameter. The event contains the new value of that Variable or
 * Parameter.
 * @see com.gensym.classes.VariableOrParameter
 * @see com.gensym.classes.Variable
 * @see com.gensym.classes.Parameter
 */
public class VariableValueEvent extends SerializableSourceEvent {
  public static final int NEW_VALUE = 0;
  public static final int INITIAL_VALUE = 1;
  
  private Object newValue;
  private int ID;

  public VariableValueEvent(Object source, Object newValue, int ID) {
    super(source);
    this.newValue = newValue;
    this.ID = ID;
  }

  /** The new value of the Variable or Parameter.
   */
  public Object getNewValue() {
    return newValue;
  }

  public int getID() {
    return ID;
  }

  @Override
  public String toString() {
    return super.toString() + "; newValue: " + newValue;
  }
}
