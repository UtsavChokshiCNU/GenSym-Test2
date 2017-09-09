/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   SerializableSourceEvent.java 
 * 
 * 
 */ 
  
package com.gensym.util;

import java.io.Serializable;
import java.util.EventObject;

/** Special events where the source is Serializable, and when the
 * de-serialized source actually has a useful meaning.
 */
public abstract class SerializableSourceEvent extends EventObject {
  static final long serialVersionUID = 9064577097371497314L;
  public static final boolean traceOn = false;

  public SerializableSourceEvent(Object source) {
    super(source);
    if (traceOn && !(source instanceof Serializable)) {
      System.out.println("sse: source" + source);
      Thread.dumpStack();
    }
  }

  private void writeObject(java.io.ObjectOutputStream out)
  throws java.io.IOException {
    out.defaultWriteObject();

    if (source instanceof Serializable)
      out.writeObject(source);
    else
      out.writeObject(null);
  }

  private void readObject(java.io.ObjectInputStream in)
  throws java.io.IOException, ClassNotFoundException {
    in.defaultReadObject();
    source = in.readObject();
  }
}
