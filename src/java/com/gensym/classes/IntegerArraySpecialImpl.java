package com.gensym.classes;

import com.gensym.util.Sequence;

public class IntegerArraySpecialImpl extends IntegerArrayImpl {

  // Set by native code, when array sent by copy
  private static final com.gensym.util.Symbol 
        HIDDEN_$G2ARRAY_CONTENTS_ = com.gensym.util.Symbol.intern ("$G2-ARRAY");

  /**
   * Sets the contents of the G2 Array from the contents of a Java array.
   * @param arrayContents must be an int[]
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public void setG2ArrayContents(java.lang.Object arrayContentsObj) 
       throws com.gensym.jgi.G2AccessException {
	 int[] arrayContents = (int[])arrayContentsObj;
	 if (isItemLocal()) //by copy
	   setAttributeValue (HIDDEN_$G2ARRAY_CONTENTS_, arrayContents);
	 else { // by reference
	   // Can only pass Sequence pack to reference via setG2ArraySequence
	   Sequence retseq = new Sequence(arrayContents.length+1);
	   for (int i=0; i<arrayContents.length; i++)
	     retseq.addElement(arrayContents[i]);
	   setG2ArraySequence(retseq);
	 }
  }


  /**
   * Gets the contents of the G2 Array.
   * @return the current array contents (as a int[])
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
	int[] arrayContents = new int[size];
	for (int i=0; i<size; i++)
	  arrayContents[i] = ((Integer)arraySequence.elementAt(i)).intValue();
	return arrayContents;
      }
  }

  /**
   * Gets the contents of the Integer-Array.
   * @return the current array contents as a int[]
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int[] getIntegerArrayContents() 
       throws com.gensym.jgi.G2AccessException {
     return (int[])getG2ArrayContents();
  }


}

    
