package com.gensym.jgi;

import com.gensym.classes.Item;

/**
 * This interface is used by G2JavaStubController to enable external factories to
 * return a Java object to be associated with a given G2 Object.
 */
public interface JavaObjectForG2ItemFactory {


  /**
   * The method should return a Java Object for the G2 Item, or null if no
   * alternate Java object could be found.
   * @param connection the connection the Item was sent over
   * @param targetObject The target object that the resolved java object returned from this method
   *                     will be sent to (an method call on targetObject for example)
   *                     (This target may be null when the target object is not known or 
   *                     a Class for a static method)
   * @param g2Item The G2 Item to be resolved
   */
  public Object getJavaObjectForG2Item(G2Access connection, Object targetObject, Item g2Item);

}
