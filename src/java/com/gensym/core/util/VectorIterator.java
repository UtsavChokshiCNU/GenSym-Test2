package com.gensym.core.util;

import java.util.*;
import java.io.Serializable;

/**
 * @undocumented
 */
public class VectorIterator implements Iterator, java.io.Serializable
{
  private static final long serialVersionUID = 1;
  
  Vector vector;
  Object singleton;
  boolean returnedSingleton = false;
  int size = 0;
  transient Iterator iterator;

  public VectorIterator()
  {
  }
  
  public VectorIterator(Vector vector)
  {
    size = vector.size();
    if (size == 1)
      {
	singleton = vector.elementAt(0);
      }
    else
      this.vector = vector; // clone ??
  }

  public VectorIterator(Object singleton)
  {
    if (singleton != null)
      size = 1;
    else
      size = 0;
    this.singleton = singleton;
  }

  @Override
  public boolean hasNext()
  {
    switch (size)
      {
      case 0: 
	return false;
      case 1:
	return !returnedSingleton;
      default:
	if (iterator == null)
	  iterator = vector.iterator();
	return iterator.hasNext();
      }
  }

  @Override
  public Object next()
  {
    switch (size)
      {
      case 0: 
	throw new NoSuchElementException();
      case 1:
	returnedSingleton = true;
	return singleton;
      default:
	if (iterator == null)
	  iterator = vector.iterator();
	return iterator.next();
      }
  }

  @Override
  public void remove() {
    throw new UnsupportedOperationException();
  }
}
