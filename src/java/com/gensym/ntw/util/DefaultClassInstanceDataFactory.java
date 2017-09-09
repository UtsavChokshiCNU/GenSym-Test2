/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DefaultClassInstanceDataFactory.java
 *
 */

package com.gensym.ntw.util;

import com.gensym.classes.G2Definition;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.util.Symbol;

public class DefaultClassInstanceDataFactory implements InstanceDataFactory {
  
  /**
   *  Creates and returns a InstanceData object for one of the following hierarchies:
   *  MODULE_HIERARCHY_, WORKSPACE_HIERARCHY_, CLASS_HIERARCHY_
   */
  @Override
  public InstanceData createInstanceData(Symbol hierarchyType) {
    return new ClassInstanceData(hierarchyType);
  }

  /**
   * Creates and returns a InstanceData object for the specified module
   */
  @Override
  public InstanceData createInstanceData(Module module) {
    return new ClassInstanceData(module);
  }

  /**
   * Creates and returns a InstanceData object for the specified kb-workspace
   */
  @Override
  public InstanceData createInstanceData(KbWorkspace workspace) {
    return new ClassInstanceData(workspace);
  }

  /**
   * Creates and returns a InstanceData object for the specified Definition
   */
  @Override
  public InstanceData createInstanceData(G2Definition g2def) {
    return new ClassInstanceData(g2def);
  }

  /**
   * Creates and returns a InstanceData object for the specified Item
   */
  @Override
  public InstanceData createInstanceData(Item item) {
    return new ClassInstanceData(item);
  }
}
