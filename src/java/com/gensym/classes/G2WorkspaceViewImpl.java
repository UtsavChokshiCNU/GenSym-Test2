/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2WorkspaceViewImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:47:58 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class G2WorkspaceViewImpl extends com.gensym.classes.G2NativeViewImpl implements G2WorkspaceView {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public G2WorkspaceViewImpl() {
    super();
  }

  public G2WorkspaceViewImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2WorkspaceViewImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Getter for attribute -- SCALE-OF-VIEW
   * @return the value of the SCALE-OF-VIEW attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getScaleOfView() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SCALE_OF_VIEW_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- WORKSPACE-OF-VIEW
   * @return the value of the WORKSPACE-OF-VIEW attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.classes.KbWorkspace getWorkspaceOfView() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.WORKSPACE_OF_VIEW_);
    return (com.gensym.classes.KbWorkspace)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
