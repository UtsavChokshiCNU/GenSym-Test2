package com.gensym.classes;

import com.gensym.util.Sequence;

public class TruthValueArraySpecialImpl extends TruthValueArrayImpl {

  // Set by native code, when array sent by copy
  private static final com.gensym.util.Symbol 
        HIDDEN_$G2ARRAY_CONTENTS_ = com.gensym.util.Symbol.intern ("$G2-ARRAY");

  /**
   * Sets the contents of the G2 Array from the contents of a Java array.
   * @param arrayContents must be an boolean[]
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public void setG2ArrayContents(java.lang.Object arrayContentsObj) 
       throws com.gensym.jgi.G2AccessException {
	 boolean[] arrayContents = (boolean[])arrayContentsObj;
	 if (isItemLocal()) //by copy
	   setAttributeValue (HIDDEN_$G2ARRAY_CONTENTS_, arrayContents);
	 else { // by reference
	   // Can only pass Sequence pack to reference via setG2ArraySequence
	   Sequence retseq = new Sequence(arrayContents.length+1);
	   for (int i=0; i<arrayContents.length; i++)
	     retseq.addElement((new Boolean(arrayContents[i])));
	   setG2ArraySequence(retseq);
	 }
  }


  /**
   * Gets the contents of the G2 Array.
   * @return the current array contents (as a boolean[])
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
	boolean[] arrayContents = new boolean[size];
	for (int i=0; i<size; i++)
	  arrayContents[i] = ((Boolean)arraySequence.elementAt(i)).booleanValue();
	return arrayContents;
      }
  }


  /**
   * Gets the contents of the TruthValue Array.
   * @return the current array contents (as a boolean[])
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean[] getTruthValueArrayContents() 
       throws com.gensym.jgi.G2AccessException {
     return (boolean[])getG2ArrayContents();
  }

}

    
