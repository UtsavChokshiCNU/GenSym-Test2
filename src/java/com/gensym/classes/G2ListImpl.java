/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2ListImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:14:14 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.G2AccessException;

public class G2ListImpl extends com.gensym.classes.ObjectImpl implements G2List {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public G2ListImpl() {
    super();
  }

  public G2ListImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2ListImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /* Overriden Property - G2LIST-SEQUENCE */
  /**
   * Generated Property Getter for attribute -- G2-LIST-SEQUENCE
   * @return the value of the G2-LIST-SEQUENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getG2ListSequence() throws G2AccessException {
    
        java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_LIST_SEQUENCE_);
        return (com.gensym.util.Sequence)retnValue;
      
  }

  /**
   * Generated Property Setter for attribute -- G2-LIST-SEQUENCE
   * @param g2ListSequence new value to conclude for G2-LIST-SEQUENCE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setG2ListSequence(com.gensym.util.Sequence g2ListSequence) throws G2AccessException   {
    
        setAttributeValue (SystemAttributeSymbols.G2_LIST_SEQUENCE_, g2ListSequence);
        if (isItemLocal())            
           setPropertyValue(SystemAttributeSymbols.ELEMENT_TYPE_, 
    			    com.gensym.util.symbol.G2TypeSymbols.ITEM_OR_VALUE_);
      
  }

  /**
   * Generated Property Getter for attribute -- ELEMENT-TYPE
   * @return the value of the ELEMENT-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getElementType() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ELEMENT_TYPE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ALLOW-DUPLICATE-ELEMENTS
   * @param allowDuplicateElements new value to conclude for ALLOW-DUPLICATE-ELEMENTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAllowDuplicateElements(boolean allowDuplicateElements) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ALLOW_DUPLICATE_ELEMENTS_, new Boolean (allowDuplicateElements));
  }

  /**
   * Generated Property Getter for attribute -- ALLOW-DUPLICATE-ELEMENTS
   * @return the value of the ALLOW-DUPLICATE-ELEMENTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getAllowDuplicateElements() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ALLOW_DUPLICATE_ELEMENTS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- LIST-IS-PERMANENT
   * @param listIsPermanent new value to conclude for LIST-IS-PERMANENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setListIsPermanent(boolean listIsPermanent) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.LIST_IS_PERMANENT_, new Boolean (listIsPermanent));
  }

  /**
   * Generated Property Getter for attribute -- LIST-IS-PERMANENT
   * @return the value of the LIST-IS-PERMANENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getListIsPermanent() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.LIST_IS_PERMANENT_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
