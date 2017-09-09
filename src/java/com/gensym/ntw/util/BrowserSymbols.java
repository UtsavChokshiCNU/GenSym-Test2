/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 BrowserSymbols.java
 *
 */
package com.gensym.ntw.util;

import com.gensym.util.Symbol;

public interface BrowserSymbols {
  public static final Symbol UNKNOWN_                = Symbol.intern("UNKNOWN");

  public static final Symbol ALL_                    = Symbol.intern("ALL");
  public static final Symbol ROOT_                   = Symbol.intern("ROOT");
  public static final Symbol NONE_                   = Symbol.intern("NONE");
  public static final Symbol DEFAULT_WORKSPACE_NAME_ = Symbol.intern("A-KB-WORKSPACE");

  public static final Symbol MODULE_HIERARCHY_       = Symbol.intern("MODULE-HIERARCHY");
  public static final Symbol WORKSPACE_HIERARCHY_    = Symbol.intern("WORKSPACE-HIERARCHY");
  public static final Symbol CLASS_HIERARCHY_        = Symbol.intern("CLASS-HIERARCHY");
  public static final Symbol OBJECT_HIERARCHY_       = Symbol.intern("OBJECT-HIERARCHY");

  public static final Symbol KNOWLEDGE_BASE_         = Symbol.intern("KNOWLEDGE-BASE");
  public static final Symbol UNREQUIRED_MODULES_     = Symbol.intern("UNREQUIRED-MODULES");
  public static final Symbol ITEM_                   = Symbol.intern("ITEM");

  public static final Symbol KB_WORKSPACE_           = Symbol.intern("KB-WORKSPACE");
  public static final Symbol MODULE_                 = Symbol.intern("MODULE");
  public static final Symbol CLASS_DEFINITION_       = Symbol.intern("CLASS-DEFINITION");
  public static final Symbol G2_DEFINITION_          = Symbol.intern("G2-DEFINITION");
  public static final Symbol ENTITY_                 = Symbol.intern("ENTITY");
  public static final Symbol PROCEDURE_              = Symbol.intern("PROCEDURE");
  public static final Symbol TEXT_BOX_               = Symbol.intern("TEXT-BOX");

  public static final String UNSPECIFIED  = "UNSPECIFIED";
  public static final Symbol UNSPECIFIED_ = Symbol.intern(UNSPECIFIED);

  public static final Symbol NAME_  = Symbol.intern ("NAME");
  public static final Symbol NAMES_ = Symbol.intern("NAMES");

  // DEFAULT CLASSES TO IGNORE FOR OBJECT-HIERARCHY
  public static final Symbol NAME_BOX_         = Symbol.intern("NAME-BOX");
  public static final Symbol DEFAULT_JUNCTION_ = Symbol.intern("DEFAULT-JUNCTION");
  public static final Symbol TABLE_ITEM_       = Symbol.intern("TABLE-ITEM");

  public static final Symbol GFR_PUBLIC_BIN_   = Symbol.intern("GFR-PUBLIC-BIN");
}
