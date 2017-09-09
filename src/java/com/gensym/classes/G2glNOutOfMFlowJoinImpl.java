/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2glNOutOfMFlowJoinImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JJ11)
 *
 *          Date: Thu Oct 11 15:46:20 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class G2glNOutOfMFlowJoinImpl extends com.gensym.classes.G2glFlowJoinImpl implements G2glNOutOfMFlowJoin {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public G2glNOutOfMFlowJoinImpl() {
    super();
  }

  public G2glNOutOfMFlowJoinImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2glNOutOfMFlowJoinImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- NUMBER-OF-BRANCHES-TO-SYNCHRONIZE
   * @param numberOfBranchesToSynchronize new value to conclude for NUMBER-OF-BRANCHES-TO-SYNCHRONIZE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setNumberOfBranchesToSynchronize(int numberOfBranchesToSynchronize) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.NUMBER_OF_BRANCHES_TO_SYNCHRONIZE_, numberOfBranchesToSynchronize);
  }

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-BRANCHES-TO-SYNCHRONIZE
   * @return the value of the NUMBER-OF-BRANCHES-TO-SYNCHRONIZE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getNumberOfBranchesToSynchronize() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.NUMBER_OF_BRANCHES_TO_SYNCHRONIZE_);
    return ((Integer)retnValue).intValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
