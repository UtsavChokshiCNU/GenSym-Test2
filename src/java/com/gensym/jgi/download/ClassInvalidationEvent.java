/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 */

package com.gensym.jgi.download;

import com.gensym.util.Symbol;

public class ClassInvalidationEvent extends java.util.EventObject {
  private Symbol[] invalidClasses;

  ClassInvalidationEvent (Object src, Symbol[] classes) {
    super (src);
    invalidClasses = classes;
  }

  public Symbol[] getInvalidClasses () {
    return invalidClasses;	// In real life, we would clone
  }

}
