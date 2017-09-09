/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MenuNotificationEvent.java
 *
 */

package com.gensym.clscupgr.gms;

import java.util.EventObject;

import com.gensym.util.Structure;
import com.gensym.util.Symbol;

public class MenuNotificationEvent extends EventObject {

  public static final int SHOW_MENU_ON_CLIENT          = 0;
  public static final int HIDE_MENU_ON_CLIENT          = 1;
  public static final int SHOW_SUBMENU_ON_CLIENT       = 2;
  public static final int HIDE_SUBMENU_ON_CLIENT       = 3;
  public static final int MENU_RECOMPILED_ON_SERVER    = 4;
  public static final int CHECK_MENU_ENTRY_ON_CLIENT   = 5;
  public static final int UNCHECK_MENU_ENTRY_ON_CLIENT = 6;
  // still need to do these
  public static final int DISABLE_ENTRY_ON_CLIENT      = 7;
  public static final int ENABLE_ENTRY_ON_CLIENT       = 8;


  private static final Symbol SHOW_MENU_ON_CLIENT_          = Symbol.intern("SHOW_MENU_ON_CLIENT");
  private static final Symbol HIDE_MENU_ON_CLIENT_          = Symbol.intern("HIDE_MENU_ON_CLIENT");
  private static final Symbol SHOW_SUBMENU_ON_CLIENT_       = Symbol.intern("SHOW_SUBMENU_ON_CLIENT");
  private static final Symbol HIDE_SUBMENU_ON_CLIENT_       = Symbol.intern("HIDE_SUBMENU_ON_CLIENT");
  private static final Symbol MENU_RECOMPILED_ON_SERVER_    = Symbol.intern("MENU_RECOMPILED_ON_SERVER");
  private static final Symbol CHECK_MENU_ENTRY_ON_CLIENT_   = Symbol.intern("CHECK_MENU_ENTRY_ON_CLIENT");
  private static final Symbol UNCHECK_MENU_ENTRY_ON_CLIENT_ = Symbol.intern("UNCHECK_MENU_ENTRY_ON_CLIENT");
  // still need to do these
  private static final Symbol DISABLE_ENTRY_ON_CLIENT_      = Symbol.intern("DISABLE_ENTRY_ON_CLIENT");
  private static final Symbol ENABLE_ENTRY_ON_CLIENT_       = Symbol.intern("ENABLE_ENTRY_ON_CLIENT");

  private int menuIndex;
  private Structure menuDescription;

  public MenuNotificationEvent(Object source,
			       Symbol code,
			       int menuIndex,
			       Structure menuDescription){
    super(source);
    this.menuIndex = menuIndex;
    this.menuDescription = menuDescription;
    id = mapCodeToID(code);
  }

  public Structure getMenuDescription(){
    return menuDescription;
  }

  public int getMenuIndex() {
    return menuIndex;
  }

  private int id;

  public int getID(){
      return id;
  }

  private static int mapCodeToID(Symbol code) {
    if (SHOW_MENU_ON_CLIENT_.equals(code))
      return SHOW_MENU_ON_CLIENT;
    else if (HIDE_MENU_ON_CLIENT_.equals(code))
      return HIDE_MENU_ON_CLIENT;
    else if (SHOW_SUBMENU_ON_CLIENT_.equals(code))
      return SHOW_SUBMENU_ON_CLIENT;
    else if (HIDE_SUBMENU_ON_CLIENT_.equals(code))
      return HIDE_SUBMENU_ON_CLIENT;
    else if (MENU_RECOMPILED_ON_SERVER_.equals(code))
      return MENU_RECOMPILED_ON_SERVER;
    else if (CHECK_MENU_ENTRY_ON_CLIENT_.equals(code))
      return CHECK_MENU_ENTRY_ON_CLIENT;
    else if (UNCHECK_MENU_ENTRY_ON_CLIENT_.equals(code))
      return UNCHECK_MENU_ENTRY_ON_CLIENT;
    else if (DISABLE_ENTRY_ON_CLIENT_.equals(code))
      return DISABLE_ENTRY_ON_CLIENT;
    else if (ENABLE_ENTRY_ON_CLIENT_.equals(code))
      return ENABLE_ENTRY_ON_CLIENT;
    else
      throw new IllegalArgumentException("Unknown code " + code);
  }
}
