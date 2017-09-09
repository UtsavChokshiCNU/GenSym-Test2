package com.gensym.jgi;

import com.gensym.classes.Item;

/**
 * This interface is used by G2JavaStubController to enable external factories to
 * return a G2 Item to associated for a specified java Object.
 */
public interface G2ItemForJavaObjectFactory {

  /**
   * The method should return a G2 Item for the Java object, or null if no
   * G2 Item was appropriate
   */
  public Item getG2ItemForJavaObject(G2Access connection, Object javaObject) throws G2AccessException;

}
