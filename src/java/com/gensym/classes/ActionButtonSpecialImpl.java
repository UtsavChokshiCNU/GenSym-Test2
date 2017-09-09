/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ActionButtonSpecialImpl.java
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

public class ActionButtonSpecialImpl extends ItemImpl 
{
  private static final Symbol G2_FIRE_ACTION_BUTTON_
  = Symbol.intern ("G2-FIRE-ACTION-BUTTON");
  
  /**
   * @return true if successful
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */                              
  public boolean invoke()
       throws G2AccessException
  {
    UiClientSession uiClientSession = retrieveSession(context);
    java.lang.Object[] args
      = new java.lang.Object[] {this, uiClientSession};
    Boolean retnvalue = (Boolean)callRPC(G2_FIRE_ACTION_BUTTON_, args);
    return retnvalue.booleanValue();
  }

}
