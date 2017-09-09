/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 BrowserSymbols.java
 *
 */
package com.gensym.uitools.browsers;

import com.gensym.util.Symbol;

public interface BrowserSymbols {
  public static final Symbol ALL_                    = Symbol.intern("ALL");
  public static final Symbol ROOT_                   = Symbol.intern("ROOT");
  public static final Symbol NONE_                   = Symbol.intern("NONE");
  public static final Symbol DEFAULT_WORKSPACE_NAME_ = Symbol.intern("A-KB-WORKSPACE");

  public static final Symbol MODULE_HIERARCHY_    = Symbol.intern("MODULE-HIERARCHY");
  public static final Symbol WORKSPACE_HIERARCHY_ = Symbol.intern("WORKSPACE-HIERARCHY");
  public static final Symbol CLASS_HIERARCHY_     = Symbol.intern("CLASS-HIERARCHY");

  public static final Symbol KNOWLEDGE_BASE_      = Symbol.intern("KNOWLEDGE-BASE");
  public static final Symbol KB_WORKSPACE_        = Symbol.intern("KB-WORKSPACE");
  public static final Symbol ITEM_                = Symbol.intern("ITEM");

  public static final int TEXT_ONLY     = 1;
  public static final int ICON_ONLY     = 2;
  public static final int TEXT_AND_ICON = 3;

  public static final int UNKNOWN = 0;

  // Used by ClassInstanceData
  public static final int MODULE_HIERARCHY    = 1;
  public static final int WORKSPACE_HIERARCHY = 2;
  public static final int CLASS_HIERARCHY     = 3;
  public static final int KNOWLEDGE_BASE      = 4;

  public static final int G2_MODULE           = 10;
  public static final int G2_KB_WORKSPACE     = 11;
  public static final int G2_DEFINITION       = 12;
  public static final int G2_CLASS_DEFINITION = 13;
  public static final int G2_SYSTEM_TABLE     = 14;

 
}
