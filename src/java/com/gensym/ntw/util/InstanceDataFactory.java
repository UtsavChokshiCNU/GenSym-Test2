/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 InstanceDataFactory.java
 *
 */
package com.gensym.ntw.util;

import com.gensym.classes.G2Definition;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.util.Symbol;


public interface InstanceDataFactory {

  public InstanceData createInstanceData(Symbol hierarchyType);
  public InstanceData createInstanceData(Module module);
  public InstanceData createInstanceData(KbWorkspace workspace);
  public InstanceData createInstanceData(G2Definition g2def);
  public InstanceData createInstanceData(Item item);
}
