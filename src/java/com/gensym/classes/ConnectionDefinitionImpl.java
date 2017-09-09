/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ConnectionDefinitionImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:37:30 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class ConnectionDefinitionImpl extends com.gensym.classes.ClassDefinitionImpl implements ConnectionDefinition {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public ConnectionDefinitionImpl() {
    super();
  }

  public ConnectionDefinitionImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public ConnectionDefinitionImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- CROSS-SECTION-PATTERN
   * @param crossSectionPattern new value to conclude for CROSS-SECTION-PATTERN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setCrossSectionPattern(com.gensym.util.Structure crossSectionPattern) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.CROSS_SECTION_PATTERN_, crossSectionPattern);
  }

  /**
   * Generated Property Getter for attribute -- CROSS-SECTION-PATTERN
   * @return the value of the CROSS-SECTION-PATTERN attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getCrossSectionPattern() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CROSS_SECTION_PATTERN_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- STUB-LENGTH
   * @param stubLength new value to conclude for STUB-LENGTH
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setStubLength(java.lang.Object stubLength) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.STUB_LENGTH_, stubLength);
  }

  /**
   * Generated Property Getter for attribute -- STUB-LENGTH
   * @return the value of the STUB-LENGTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getStubLength() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.STUB_LENGTH_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- JUNCTION-BLOCK
   * @param junctionBlock new value to conclude for JUNCTION-BLOCK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setJunctionBlock(com.gensym.util.Symbol junctionBlock) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.JUNCTION_BLOCK_, junctionBlock);
  }

  /**
   * Generated Property Getter for attribute -- JUNCTION-BLOCK
   * @return the value of the JUNCTION-BLOCK attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getJunctionBlock() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.JUNCTION_BLOCK_);
    return (com.gensym.util.Symbol)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
