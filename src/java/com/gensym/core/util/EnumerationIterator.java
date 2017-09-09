package com.gensym.core.util;

import java.util.*;
import java.io.Serializable;

/**
 * @undocumented
 */
public class EnumerationIterator implements Iterator, java.io.Serializable
{
  private static final long serialVersionUID = 1;
  
  Enumeration enumeration;

  public EnumerationIterator()
  {
  }
  
  public EnumerationIterator(Enumeration enumeration)
  {
    this.enumeration = enumeration; // clone ??
  }

  @Override
  public boolean hasNext()
  {
    return enumeration.hasMoreElements();
  }

  @Override
  public Object next()
  {
    return enumeration.nextElement();
  }

  @Override
  public void remove() {
    throw new UnsupportedOperationException();
  }
}
