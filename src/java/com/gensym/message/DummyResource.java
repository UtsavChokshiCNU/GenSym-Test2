/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   DummyResource.java 
 * 
 * 
 */ 
  
package com.gensym.message;

import java.util.Arrays;
import java.util.MissingResourceException;

/** This is a subclass of Resource that doesn't require an underlying
 * ResourceBundle to do its work: it is to be used as a tracing resource
 * as a means of ensuring no Resource-based exceptions are thrown in relation
 * to tracing. Is used by the Trace class.
 */
class DummyResource extends Resource {

  DummyResource() {
    super("dummy");
  }

  @Override
  public String getString(String key) {
    return key;
  }

  @Override
  public String format(String key, Object[] args) throws
  MissingResourceException{
    return key + "; " + Arrays.toString(args); //DebugUtil.printArray(args);
  }

  @Override
  public String format(String key, Object arg)
  throws MissingResourceException {
    return key + "; " + arg;
  }

  @Override
  public String format(String key, Object arg1, Object arg2)
       throws MissingResourceException {
    return key + "; " + arg1 + "; " + arg2;
  }

  @Override
  public boolean equals(Object obj) {
    if (obj == null || !getClass().equals(obj.getClass())) {
      return false;
    }

    return true;
  }

  @Override
  public int hashCode() {
    return 0;
  }
}
