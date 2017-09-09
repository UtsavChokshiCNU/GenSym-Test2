/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      EntitySpecialImpl.java
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

public class EntitySpecialImpl extends ItemImpl {

  private static final Symbol
  G2_MAKE_SUBWORKSPACE_ = Symbol.intern ("G2-MAKE-SUBWORKSPACE"),
  G2_GET_SUBWORKSPACE_  = Symbol.intern ("G2-GET-SUBWORKSPACE"),
  G2_REFLECT_ITEM_VERTICALLY_  = Symbol.intern ("G2-REFLECT-ITEM-VERTICALLY"),
  G2_REFLECT_ITEM_HORIZONTALLY_  = Symbol.intern ("G2-REFLECT-ITEM-HORIZONTALLY");
    
  //public void setBounds (int left, int top, int width, int height) {}

  /**
   * @return this Item's subworkspace, if one exists.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */                             
  public KbWorkspace getSubworkspace()
       throws G2AccessException
  {
    java.lang.Object[] args = {this};
    return (KbWorkspace)context.callRPC(G2_GET_SUBWORKSPACE_, args);
  }

  /**
   * @param workspace the KbWorkspace to attempt to set as
   * this Item's subworkspace.  
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call, such as when
   * this Item already has a subworkspace.
   */                             
  public void setSubworkspace(KbWorkspace workspace)
       throws G2AccessException
  {
    java.lang.Object[] args = {workspace, this};
    context.callRPC(G2_MAKE_SUBWORKSPACE_, args);
  }

  /**
   * Reflects this Item horizontally, across the Y-axis
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */                             
  public Symbol reflectHorizontally() throws G2AccessException
  {
    java.lang.Object[] args = {this};
    Symbol retnvalue = (Symbol)
      callRPC(G2_REFLECT_ITEM_HORIZONTALLY_, args);
    return retnvalue;
  }

  /**
   * Reflects this Item vertically, across the X-axis
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */                             
  public Symbol reflectVertically() throws G2AccessException
  {
    java.lang.Object[] args = {this};
    Symbol retnvalue = (Symbol)
      callRPC(G2_REFLECT_ITEM_VERTICALLY_, args);
    return retnvalue;
  }

}
