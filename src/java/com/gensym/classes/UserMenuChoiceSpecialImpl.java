/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UserMenuChoiceSpecialImpl.java
 *
 *   Description: Overides for generated Interface files. 
 *
 *        Author: Paul B. Konigberg
 *
 *       Version: 5.0 Rev. 1
 *
 *          Date: Thu Apr 16 10:44:44 EDT 1998
 *
 */


package com.gensym.classes;

import com.gensym.util.Symbol;
import com.gensym.jgi.*;

public class UserMenuChoiceSpecialImpl extends ItemImpl
{
  private static final Symbol G2_FIRE_USER_MENU_CHOICE_ =
  Symbol.intern ("G2-FIRE-USER-MENU-CHOICE");

  /**
   * @param item the Item on which to invoke this UserMenuChoice
   * @return true if successful
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public boolean invoke(Item item)
       throws G2AccessException
  {
    UiClientSession uiClientSession = retrieveSession(context);
    java.lang.Object[] args
      = new java.lang.Object[] {this, item, uiClientSession};
    Boolean retnvalue = (Boolean)callRPC(G2_FIRE_USER_MENU_CHOICE_, args);
    return retnvalue.booleanValue();
  }

}
