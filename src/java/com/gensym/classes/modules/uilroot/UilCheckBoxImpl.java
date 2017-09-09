/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilCheckBoxImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:05:54 EDT 2007
 *
 */


package com.gensym.classes.modules.uilroot;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class UilCheckBoxImpl extends com.gensym.classes.modules.uilroot.UilSelectionBoxImpl implements UilCheckBox {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public UilCheckBoxImpl() {
    super();
  }

  public UilCheckBoxImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilCheckBoxImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  // Method Name Constants
  private static final Symbol MethodName_UPP_EXTRACT_VALUE_FROM_ITEM_ = Symbol.intern ("UPP-EXTRACT-VALUE-FROM-ITEM");
  private static final Symbol MethodName_UPP_EXTRACT_VALUES_FROM_ITEM_ = Symbol.intern ("UPP-EXTRACT-VALUES-FROM-ITEM");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * UIL-CHECK-BOX::UPP-EXTRACT-VALUE-FROM-ITEM
   * @return the return from calling UPP-EXTRACT-VALUE-FROM-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-CHECK-BOX) = (VALUE,TRUTH-VALUE)
   */
  @Override
  public  com.gensym.util.Sequence uppExtractValueFromItem() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_UPP_EXTRACT_VALUE_FROM_ITEM_, args);
      return (com.gensym.util.Sequence)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * UIL-CHECK-BOX::UPP-EXTRACT-VALUES-FROM-ITEM
   * @return the return from calling UPP-EXTRACT-VALUES-FROM-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-CHECK-BOX) = (ITEM-OR-VALUE)
   */
  @Override
  public  java.lang.Object uppExtractValuesFromItem() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_UPP_EXTRACT_VALUES_FROM_ITEM_, args);
      return (java.lang.Object)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
