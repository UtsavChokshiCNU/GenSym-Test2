package com.gensym.jgi;

import com.gensym.util.Symbol;

/**
 * This interface is used by G2JavaStubController to enable external factories to
 * return a G2 Class that should be used to create a proxy for a java Object.
 */
public interface G2ClassForJavaObjectFactory {

  /**
   * The method should return a G2 Class for the Java object, or null if no
   * G2 class was appropriate
   */
  public Symbol getG2ClassForJavaObject(G2Access connection, Object javaObject);

}
