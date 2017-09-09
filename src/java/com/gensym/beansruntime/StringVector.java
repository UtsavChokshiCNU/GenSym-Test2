package com.gensym.beansruntime;

import java.util.Vector;
import java.beans.*;

public class StringVector extends Vector
       implements java.io.Serializable
{
   /*
   * Allow deserialization
   */
  static final long serialVersionUID = 6892962177426495338L;
  static 
  {
    Class editor = com.gensym.beansruntime.StringVectorEditor.class;
    //System.out.println("registering editor class "+editor);
    PropertyEditorManager.registerEditor
      (com.gensym.beansruntime.StringVector.class,editor);
  }

  public StringVector ()
  {
    
  }

  public StringVector(String[] initialValue)
  {
    super();
    int i,len = initialValue.length;
    for (i=0; i<len; i++)
      addElement(initialValue[i]);
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
  public void addStringElement (String element) {
    addElement (element);
  }

  /**
   * @undocumented For VB use since it cannot call removeElement (java.lang.Object)
   */
  public void removeStringElement (String element) {
    removeElement (element);
  }

}
