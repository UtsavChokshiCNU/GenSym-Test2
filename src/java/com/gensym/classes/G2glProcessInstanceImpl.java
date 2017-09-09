/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2glProcessInstanceImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JJ11)
 *
 *          Date: Thu Oct 11 15:46:18 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class G2glProcessInstanceImpl extends com.gensym.classes.G2glObjectImpl implements G2glProcessInstance {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public G2glProcessInstanceImpl() {
    super();
  }

  public G2glProcessInstanceImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2glProcessInstanceImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- G2GL-PROCESS-INSTANCE-IS-PAUSED
   * @param g2glProcessInstanceIsPaused new value to conclude for G2GL-PROCESS-INSTANCE-IS-PAUSED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setG2glProcessInstanceIsPaused(boolean g2glProcessInstanceIsPaused) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.G2GL_PROCESS_INSTANCE_IS_PAUSED_, new Boolean (g2glProcessInstanceIsPaused));
  }

  /**
   * Generated Property Getter for attribute -- G2GL-PROCESS-INSTANCE-IS-PAUSED
   * @return the value of the G2GL-PROCESS-INSTANCE-IS-PAUSED attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getG2glProcessInstanceIsPaused() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2GL_PROCESS_INSTANCE_IS_PAUSED_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
