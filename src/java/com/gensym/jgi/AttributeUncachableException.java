package com.gensym.jgi;

import java.util.Vector;

public class AttributeUncachableException extends G2AccessException {
  private Vector uncachableAtributeNames;

  public AttributeUncachableException() {
    super();
  }

  public AttributeUncachableException(String errorMsg) {
    super(errorMsg);
  }

  public AttributeUncachableException(Vector attrNames) {
    super();
    uncachableAtributeNames = attrNames;
  }

  public Vector getUncachableAttributeNames() {
    return uncachableAtributeNames;
  }
}