
package com.gensym.util;

import java.util.Enumeration;
import java.util.NoSuchElementException;
import java.util.Vector;

/**
 * A Structure enumerator class.  This class should remain opaque 
 * to the client. It will use the Enumeration interface.
 * Has been made public to work in VB.
 */
public class StructureEnumerator implements Enumeration {

  int index;
  Object[] enumeratedArray;

    StructureEnumerator(Object[] keysOrValuesArray, int numUsedSlots) {
      this.enumeratedArray = keysOrValuesArray;
      this.index = numUsedSlots - 1;
    }
	
    @Override
    public boolean hasMoreElements() {
      if (index >= 0)
	return true;
      else
	return false;
    }

    @Override
    public Object nextElement() {
      if (index < 0)
	throw new NoSuchElementException("StructureEnumerator");
      return (enumeratedArray[index--]);
    }

}
