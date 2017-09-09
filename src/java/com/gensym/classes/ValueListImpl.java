/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ValueListImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:14:16 EDT 2007
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

public class ValueListImpl extends com.gensym.classes.G2ListImpl implements ValueList {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public ValueListImpl() {
    super();
  }

  public ValueListImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public ValueListImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /* Overriden Property - G2LIST-SEQUENCE */
  /**
   * Generated Property Getter for attribute -- G2-LIST-SEQUENCE
   * @return the value of the G2-LIST-SEQUENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getG2ListSequence() 
       throws G2AccessException {
    
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
  public void setG2ListSequence(com.gensym.util.Sequence g2ListSequence) 
       throws G2AccessException   {
    
        setAttributeValue (SystemAttributeSymbols.G2_LIST_SEQUENCE_, g2ListSequence);
        if (isItemLocal())            
           setPropertyValue(SystemAttributeSymbols.ELEMENT_TYPE_, 
    			    com.gensym.util.symbol.G2TypeSymbols.VALUE_);
      
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
