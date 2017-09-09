/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   VariableOrParameterData.java 
 * 
 * 
 */ 

package com.gensym.classes;

import com.gensym.util.VariableValueListener;
import com.gensym.util.VariableValueEvent;

public class VariableOrParameterData extends ItemData {
  public volatile VariableValueListener valueListener;
  public volatile java.lang.Object currentValue;
  public volatile boolean valueSubscribed;
  public volatile Integer valueSubscriptionHandle;
  public volatile java.lang.Object localCurrentValue;
  public volatile int localStatus;
}
