/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DefaultObjectInstanceDataFactory.java
 *
 */

package com.gensym.uitools.browsers;

import com.gensym.classes.G2Definition;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.util.Symbol;
import com.gensym.ntw.util.InstanceDataFactory;
import com.gensym.ntw.util.InstanceData;
import com.gensym.ntw.util.ObjectInstanceData;

public class DefaultObjectInstanceDataFactory implements InstanceDataFactory {
  
  /**
   *  Creates and returns a InstanceData object for one of the object hierarchy
   */
  @Override
  public InstanceData createInstanceData(Symbol hierarchyType) {
    return new ObjectInstanceData(hierarchyType);
  }

  /**
   * Creates and returns a InstanceData object for the specified module
   */
  @Override
  public InstanceData createInstanceData(Module module) {
    return new ObjectInstanceData(module);
  }

  /**
   * Creates and returns a InstanceData object for the specified kb-workspace
   */
  @Override
  public InstanceData createInstanceData(KbWorkspace workspace) {
    return new ObjectInstanceData(workspace);
  }

  /**
   * Creates and returns a InstanceData object for the specified Definition
   */
  @Override
  public InstanceData createInstanceData(G2Definition g2def) {
    return new ObjectInstanceData(g2def);
  }

  /**
   * Creates and returns a InstanceData object for the specified Item
   */
  @Override
  public InstanceData createInstanceData(Item item) {
    return new ObjectInstanceData(item);
  }
}
