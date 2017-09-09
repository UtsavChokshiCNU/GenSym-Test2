/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      QuantityArrayImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:05:24 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.util.Sequence;

public class QuantityArrayImpl extends com.gensym.classes.ValueArrayImpl implements QuantityArray {


  static final long serialVersionUID = 2L;

  /* Overriden Field */
  private static final com.gensym.util.Symbol 
        HIDDEN_$G2ARRAY_CONTENTS_ = com.gensym.util.Symbol.intern ("$G2-ARRAY");
  /* Generated constructors */

  public QuantityArrayImpl() {
    super();
  }

  public QuantityArrayImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public QuantityArrayImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /* Overriden Property - G2ARRAY-CONTENTS */
  /**
   * Gets the contents of the G2 Array.
   * @return the current array contents (as a java.lang.Number[])
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
    	Number[] arrayContents = new Number[size];
    	for (int i=0; i<size; i++)
    	  arrayContents[i] = (Number)arraySequence.elementAt(i);
    	return arrayContents;
          }
      
  }

  /**
   * Sets the contents of the G2 Array from the contents of a Java array.
   * @param arrayContents must be an Number[]
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public void setG2ArrayContents(java.lang.Object arrayContentsObj) 
       throws com.gensym.jgi.G2AccessException   {
    
    	 Number[] arrayContents = (Number[])arrayContentsObj;
    	 if (isItemLocal())           
    	   setAttributeValue (HIDDEN_$G2ARRAY_CONTENTS_, arrayContents);
    	 else {                 
    	                                                                      
    	   Sequence retseq = new Sequence(arrayContents.length+1);
    	   for (int i=0; i<arrayContents.length; i++)
    	     retseq.addElement(arrayContents[i]);
    	   setG2ArraySequence(retseq);
    	 }
      
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
