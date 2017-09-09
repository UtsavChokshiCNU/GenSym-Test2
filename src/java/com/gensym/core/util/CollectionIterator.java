package com.gensym.core.util;

import java.util.*;
import java.io.Serializable;

/**
 * @undocumented
 */
public class CollectionIterator implements Iterator, java.io.Serializable
{
  private static final long serialVersionUID = 1;

  public static final CollectionIterator EMPTY_ITERATOR = new CollectionIterator();

  public static Iterator getIterator(Collection collection) {
    if (collection == null || collection.isEmpty())
      return EMPTY_ITERATOR;
    else
      return new CollectionIterator(collection);
  }

  public static Iterator getIterator(Object object) {
    if (object == null)
      return EMPTY_ITERATOR;
    else
      return new CollectionIterator(object);
  }

  public static Iterator getIterator(VectorEnumeration ve) {
    return new CollectionIterator(ve);
  }

  Collection collection;
  Object singleton;
  boolean returnedSingleton = false;
  int size;
  transient Iterator iterator;

  public CollectionIterator()
  {
    // NOTE: size = 0;
  }
  
  public CollectionIterator(Collection collection)
  {
    if (collection == null) {
      size = 0;
    } else {
      size = collection.size();
      if (size == 1)
	{
	  singleton = collection.iterator().next();
	}
      else
	this.collection = collection; // clone ??
    }
  }

  public CollectionIterator(VectorEnumeration ve) {
    size = ve.size;
    singleton = ve.singleton;
    collection = ve.vector;
  }

  public CollectionIterator(Object singleton)
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
	  iterator = collection.iterator();
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
	  iterator = collection.iterator();
	return iterator.next();
      }
  }

  @Override
  public void remove() {
    throw new UnsupportedOperationException();
  }
}
