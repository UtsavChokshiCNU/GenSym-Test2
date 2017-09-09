/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   G2ConnectionSourceEvent.java 
 * 
 * 
 */ 
  
package com.gensym.util;

import java.util.EventObject;

import com.gensym.jgi.ConnectionResolver;
import com.gensym.jgi.G2Gateway;

import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;

public class G2ConnectionSourceEvent extends EventObject {

  private ConnectionResolver connectionResolver;

  public G2ConnectionSourceEvent(G2Gateway source) {
    super(source);
    connectionResolver = ConnectionResolver.getConnectionResolver(source);
  }

  private void readObject(java.io.ObjectInputStream stream)
  throws java.io.IOException, ClassNotFoundException{
    try {
      stream.defaultReadObject();
    } catch (java.io.NotActiveException ex) {
      Trace.exception(ex);
    }

    source = connectionResolver.getContext();
  }
}
