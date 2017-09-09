/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 KeyInfo.java
 *
 *  Description:
 *              A class for holding information about Message keys.
 *
 *	 Author:
 *		Robert Penny		Jul/97
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.nols.deployutil;

import java.util.Vector;

/** Encapsulates the information associated with a message key. */

class KeyInfo implements Cloneable {
  private String key;
  private String shortDescKey;
  private String longDescKey;
  private Resource resource;
  private Vector sourceClasses = new Vector();

  public KeyInfo(String key, Class classKey,
		 String shortDescriptionKey,
		 String longDescriptionKey,
		 Resource resource) {
    this.key = key;
    shortDescKey = shortDescriptionKey;
    longDescKey = longDescriptionKey;
    addClass(classKey);
  }

  public void addClass(Class classKey) {
    if (classKey == null)
      Thread.dumpStack();
    if (!sourceClasses.contains(classKey))
      sourceClasses.addElement(classKey);
  }

  public String getShortDescriptionKey() {
    return shortDescKey;
  }

  @Override
  public Object clone() {
    try {
      return super.clone();
    } catch (CloneNotSupportedException cnse) {
      // we support cloneable, so this shouldn't happen.
      throw new InternalError();
    }
  }
}

