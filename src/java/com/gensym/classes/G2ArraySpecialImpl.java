package com.gensym.classes;


import com.gensym.util.Sequence;
import com.gensym.util.symbol.SystemAttributeSymbols;

public class G2ArraySpecialImpl extends G2ArrayImpl {

  // Set by native code, when array sent by copy
  private static final com.gensym.util.Symbol 
        HIDDEN_$G2ARRAY_CONTENTS_ = com.gensym.util.Symbol.intern ("$G2-ARRAY");
  private static final com.gensym.util.Symbol
        ARRAY_LENGTH_ = com.gensym.util.Symbol.intern("ARRAY-LENGTH");

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


  /**
   * Sets the contents of the G2 Array from the contents of a Java array.
   * @param arrayContents must be a java.lang.Object[]
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public void setG2ArrayContents(java.lang.Object arrayContentsObj) 
       throws com.gensym.jgi.G2AccessException {
	 java.lang.Object[] arrayContents = (java.lang.Object[])arrayContentsObj;
	 if (isItemLocal()) { //by copy 
	   setAttributeValue (HIDDEN_$G2ARRAY_CONTENTS_, arrayContents);
	   setPropertyValue(SystemAttributeSymbols.ELEMENT_TYPE_, 
			    com.gensym.util.symbol.G2TypeSymbols.ITEM_OR_VALUE_);
	 } else { // by reference
	   // Can only pass Sequence pack to reference via setG2ArraySequence
	   Sequence retseq = new Sequence(arrayContents.length+1);
	   for (int i=0; i<arrayContents.length; i++)
	     retseq.addElement(arrayContents[i]);
	   setG2ArraySequence(retseq);
	 }
  }

  /**
   * Gets the contents of the G2 Array.
   * @return the current array contents (as an java.lang.Object[])
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getG2ArrayContents() 
       throws com.gensym.jgi.G2AccessException {
      if (isItemLocal()) // by copy
	return getAttributeValue (HIDDEN_$G2ARRAY_CONTENTS_);
      else { // by reference
	// Can only get Sequence pack for reference via getG2ArraySequence
        Sequence arraySequence = getG2ArraySequence();
	int size = arraySequence.size();
	java.lang.Object[] arrayContents = new java.lang.Object[size];
	for (int i=0; i<size; i++)
	  arrayContents[i] = (java.lang.Object)arraySequence.elementAt(i);
	return arrayContents;
      }
  }

}

    
