package com.gensym.controls;

import java.util.Vector;
import java.beans.*;

import com.gensym.util.Symbol;

public class SymbolVector extends Vector
       implements java.io.Serializable
{
   /*
   * Allow deserialization
   */

  static 
  {
    Class editor = SymbolVectorEditor.class;
    PropertyEditorManager.registerEditor
      (SymbolVector.class,editor);
  }

  public SymbolVector ()
  {
    
  }
  
  public SymbolVector(String[] initialValue)
  {
    super();
    int i,len = initialValue.length;
    for (i=0; i<len; i++)
      addElement(Symbol.intern(initialValue[i]));
  }
  
  private void readObject(java.io.ObjectInputStream s)
       throws java.lang.ClassNotFoundException,
	 java.io.IOException
  {
    s.defaultReadObject();
  }

  /**
   * @undocumented For VB use since it cannot call addElement (java.lang.Object)
   */
  public void addSymbolElement (Symbol element) {
    addElement (element);
  }

  /**
   * @undocumented For VB use since it cannot call removeElement (java.lang.Object)
   */
  public void removeSymbolElement (Symbol element) {
    removeElement (element);
  }


}
