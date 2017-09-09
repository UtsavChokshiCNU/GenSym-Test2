/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2ArrayImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:14:09 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class G2ArrayImpl extends com.gensym.classes.ObjectImpl implements G2Array {


  static final long serialVersionUID = 2L;

  /* Overriden Field */
  private static final com.gensym.util.Symbol 
        HIDDEN_$G2ARRAY_CONTENTS_ = com.gensym.util.Symbol.intern ("$G2-ARRAY");
  /* Overriden Field */
  private static final com.gensym.util.Symbol
        ARRAY_LENGTH_ = com.gensym.util.Symbol.intern("ARRAY-LENGTH");
  /* Generated constructors */

  public G2ArrayImpl() {
    super();
  }

  public G2ArrayImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2ArrayImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /* Overriden Property - ARRAY-LENGTH */
  /**
   * Property Getter for attribute -- ARRAY-LENGTH
   * @return the value of the ARRAY-LENGTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getArrayLength() throws com.gensym.jgi.G2AccessException {
    
        if (isItemLocal()) {
          java.lang.Object localarray = getAttributeValue (HIDDEN_$G2ARRAY_CONTENTS_);
          
          if (localarray instanceof int[])
        	  return ((int[])localarray).length;
          else if (localarray instanceof double[])
        	  return ((double[])localarray).length;
          else if (localarray instanceof String[])
        	  return ((String[])localarray).length;
          else if (localarray instanceof com.gensym.util.Symbol[])
        	  return ((com.gensym.util.Symbol[])localarray).length;
          else if (localarray instanceof boolean[])
        	  return ((boolean[])localarray).length;
          else if (localarray instanceof java.lang.Object[])
        	  return ((java.lang.Object[])localarray).length;
          else if (localarray instanceof java.lang.Number[])
        	  return ((Number[])localarray).length;
          else return 0; 
        }
        else {
          java.lang.Object retnValue = getAttributeValue (ARRAY_LENGTH_);
          return ((Integer)retnValue).intValue ();
        }
      
  }


  /* Overriden Property - G2ARRAY-CONTENTS */
  /**
   * Gets the contents of the G2 Array.
   * @return the current array contents (as an java.lang.Object[])
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getG2ArrayContents() 
       throws com.gensym.jgi.G2AccessException {
    
          if (isItemLocal())            
    	return getAttributeValue (HIDDEN_$G2ARRAY_CONTENTS_);
          else { // by reference
    	                                                                   
            Sequence arraySequence = getG2ArraySequence();
    	int size = arraySequence.size();
    	java.lang.Object[] arrayContents = new java.lang.Object[size];
    	for (int i=0; i<size; i++)
    	  arrayContents[i] = (java.lang.Object)arraySequence.elementAt(i);
    	return arrayContents;
          }
      
  }

  /**
   * Sets the contents of the G2 Array from the contents of a Java array.
   * @param arrayContents must be a java.lang.Object[]
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public void setG2ArrayContents(java.lang.Object arrayContentsObj) 
       throws com.gensym.jgi.G2AccessException   {
    
    	 java.lang.Object[] arrayContents = (java.lang.Object[])arrayContentsObj;
    	 if (isItemLocal()) {            
    	   setAttributeValue (HIDDEN_$G2ARRAY_CONTENTS_, arrayContents);
    	   setPropertyValue(SystemAttributeSymbols.ELEMENT_TYPE_, 
    			    com.gensym.util.symbol.G2TypeSymbols.ITEM_OR_VALUE_);
    	 } else {                 
    	                                                                      
    	   Sequence retseq = new Sequence(arrayContents.length+1);
    	   for (int i=0; i<arrayContents.length; i++)
    	     retseq.addElement(arrayContents[i]);
    	   setG2ArraySequence(retseq);
    	 }
      
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
   * Generated Property Setter for attribute -- INITIAL-VALUES
   * @param initialValues new value to conclude for INITIAL-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setInitialValues(java.lang.Object initialValues) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.INITIAL_VALUES_, initialValues);
  }

  /**
   * Generated Property Getter for attribute -- INITIAL-VALUES
   * @return the value of the INITIAL-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getInitialValues() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INITIAL_VALUES_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ARRAY-IS-PERMANENT
   * @param arrayIsPermanent new value to conclude for ARRAY-IS-PERMANENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setArrayIsPermanent(boolean arrayIsPermanent) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ARRAY_IS_PERMANENT_, new Boolean (arrayIsPermanent));
  }

  /**
   * Generated Property Getter for attribute -- ARRAY-IS-PERMANENT
   * @return the value of the ARRAY-IS-PERMANENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getArrayIsPermanent() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ARRAY_IS_PERMANENT_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- G2-ARRAY-SEQUENCE
   * @param g2ArraySequence new value to conclude for G2-ARRAY-SEQUENCE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setG2ArraySequence(com.gensym.util.Sequence g2ArraySequence) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.G2_ARRAY_SEQUENCE_, g2ArraySequence);
  }

  /**
   * Generated Property Getter for attribute -- G2-ARRAY-SEQUENCE
   * @return the value of the G2-ARRAY-SEQUENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getG2ArraySequence() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_ARRAY_SEQUENCE_);
    return (com.gensym.util.Sequence)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
