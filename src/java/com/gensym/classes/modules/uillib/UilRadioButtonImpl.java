/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilRadioButtonImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:05:50 EDT 2007
 *
 */


package com.gensym.classes.modules.uillib;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class UilRadioButtonImpl extends com.gensym.classes.modules.uilroot.UilSelectionButtonImpl implements UilRadioButton {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public UilRadioButtonImpl() {
    super();
  }

  public UilRadioButtonImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilRadioButtonImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  // Method Name Constants
  private static final Symbol MethodName_UPP_SET_BUTTON_LABEL_ = Symbol.intern ("UPP-SET-BUTTON-LABEL");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * UIL-RADIO-BUTTON::UPP-SET-BUTTON-LABEL
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-RADIO-BUTTON,arg1:TEXT) = ()
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
