/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      RootImpl.java
 */

package com.gensym.classes;

public class RootSpecialImpl {

  public com.gensym.util.Symbol getG2ClassName() throws G2AccessException {
    java.lang.Object retnValue = getDefinition().getClassName();
    return (com.gensym.util.Symbol)retnValue;
  }
}
