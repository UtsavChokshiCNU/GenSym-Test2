package com.gensym.core.util;

import java.util.*;
import java.io.Serializable;

/**
 * @undocumented
 */
public class VectorEnumeration implements Enumeration, java.io.Serializable
{
  private static final long serialVersionUID = 1;
  
  Vector vector;
  Object singleton;
  boolean returnedSingleton = false;
  int size = 0;
  transient Enumeration enumeration;

  public VectorEnumeration()
  {
  }
  
  public VectorEnumeration(Vector vector)
  {
    if (vector == null) {
      size = 0;
    } else {
      size = vector.size();
      if (size == 1)
	{
	  singleton = vector.elementAt(0);
	}
      else
	this.vector = vector; // clone ??
    }
  }

  public VectorEnumeration(Object singleton)
  {
    if (singleton != null)
      size = 1;
    else
      size = 0;
    this.singleton = singleton;
  }

  @Override
  public boolean hasMoreElements()
  {
    switch (size)
      {
      case 0: 
	return false;
      case 1:
	return !returnedSingleton;
      default:
	if (enumeration == null)
	  enumeration = vector.elements();
	return enumeration.hasMoreElements();
      }
  }

  @Override
  public Object nextElement()
  {
    switch (size)
      {
      case 0: 
	return null;
      case 1:
	returnedSingleton = true;
	return singleton;
      default:
	if (enumeration == null)
	  enumeration = vector.elements();
	return enumeration.nextElement();
      }
  }
}
