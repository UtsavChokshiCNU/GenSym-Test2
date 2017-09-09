/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Set.java
 *
 *  Description:
 *               The mathematical set.
 *
 *	 Author:
 *		Robert Penny		Aug/97
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.util;

import java.util.*;

/** Could be a subclass of Vector, except that the interesting methods
 * are <code>final</code>. */
public class Set {
  private Vector vector;

  public Set() {
    vector = new Vector();
  }

  public Set(int capacity) {
    vector = new Vector(capacity);
  }

  public Set(int capacity, int increment) {
    vector = new Vector(capacity, increment);
  }

  /** Performs a shallow clone on the data in the vector */
  public Set(Vector vector) {
    this.vector = (Vector)vector.clone();
  }

  public Object firstElement() {
    return vector.firstElement();
  }

  public Object elementAt(int index) {
    return vector.elementAt(index);
  }

  @Override
  public Object clone() {
    return new Set(vector);
  }

  /** Only adds the element if it is not already in the Set */
  public void add(Object newObject) {
    if (vector.contains(newObject))
      return;

    vector.addElement(newObject);
  }

  public void remove(Object object) {
    vector.removeElement(object);
  }

  public void clear() {
    vector.removeAllElements();
  }

  public Enumeration elements() {
    return vector.elements();
  }

  /** Alters the current vector to also contain the contents of
   * <code>newVector</code> */
  public Set union(Vector newVector) {
    vector.ensureCapacity(vector.size() + newVector.size());

    return union(newVector.elements());
  }

  public Set union(Enumeration en) {
    for (; en.hasMoreElements();)
      add(en.nextElement());

    return this;
  }

  public int size() {
    return vector.size();
  }

  @Override
  public String toString() {
    return "[Set: " + vector.toString() + "]";
  }
  
}
