/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilIconButtonImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:14:41 EDT 2007
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

public class UilIconButtonImpl extends com.gensym.classes.modules.uilroot.UilButtonImpl implements UilIconButton {


  static final long serialVersionUID = 2L;
  private static final Symbol LABEL_ = Symbol.intern ("LABEL");

  /* Generated constructors */

  public UilIconButtonImpl() {
    super();
  }

  public UilIconButtonImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilIconButtonImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- LABEL
   * @param label new value to conclude for LABEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setLabel(java.lang.Object label) throws G2AccessException {
    setAttributeValue (LABEL_, label);
  }

  /**
   * Generated Property Getter for attribute -- LABEL
   * @return the value of the LABEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getLabel() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (LABEL_);
    return (java.lang.Object)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_UPP_SET_BUTTON_LABEL_ = Symbol.intern ("UPP-SET-BUTTON-LABEL");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * UIL-ICON-BUTTON::UPP-SET-BUTTON-LABEL
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-ICON-BUTTON,arg1:TEXT) = ()
   */
  @Override
  public  void uppSetButtonLabel(java.lang.String arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_UPP_SET_BUTTON_LABEL_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
