/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      MessageSpecialImpl.java
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
import com.gensym.util.Sequence;
import com.gensym.jgi.*;

public class MessageSpecialImpl extends ItemImpl
{

  private static final Symbol G2_GET_REFERENCED_ITEMS_
  = Symbol.intern ("G2-GET-REFERENCED-ITEMS");

  /**
   * @return a Sequence of the Items referenced by this Message.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call.
   */                             
  public Sequence getReferencedItems()
       throws G2AccessException
  {
    java.lang.Object[] args = {this};
    return (Sequence)context.callRPC(G2_GET_REFERENCED_ITEMS_, args);
  }

}
