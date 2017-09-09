/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 InstanceData.java
 *
 */
package com.gensym.ntw.util;

import com.gensym.classes.G2Definition;
import com.gensym.classes.Item;
import com.gensym.classes.Module;
import com.gensym.util.Symbol;
import javax.swing.Icon;

public interface InstanceData {
  public void      setItem(Item item);
  public Item      getItem();
  public void      setModule(Module module);
  public Module    getModule();
  public G2Definition getG2Definition();
  public void      setDataType(Symbol type);
  public Symbol    getDataType();
  public Icon determineIconForItem(Item item);
  public String    determineToolTipForDataType(Symbol dataType);
  public String    determineStringValueForDataType(Symbol dataType);
  @Override
  public String    toString();
  public BasicObjectDataRenderer getRenderer();
}
