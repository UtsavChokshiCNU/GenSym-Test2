/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MessageKey.java
 *
 *  Description:
 *              Preregistered keys for identifying messages by arbitrary
 *              String key, associated class, and priority.
 *
 *	 Author:
 *		Robert Penny		Jul/97
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.nols.deployutil;

import java.io.*;

/** Encapsulates the specifics of a particular set of message statements. */
public class MessageKey implements Serializable {
  public final String msgKey;
  private transient Class messageClass;

  //  private int hash;

  MessageKey(String msgKey, Class messageClass) {
    this.msgKey = msgKey;
    this.messageClass = messageClass;
  }

  public Class getMessageClass() {
    return messageClass;
  }

  private void writeObject(ObjectOutputStream out) throws IOException {
    out.defaultWriteObject();
    out.writeUTF(messageClass.getName());
  }

  private void readObject(ObjectInputStream in) 
  throws IOException, ClassNotFoundException {
    in.defaultReadObject();
    messageClass = Class.forName(in.readUTF());
  }

  @Override
  public String toString () {
    return (super.toString () + "<Key=" + msgKey + ", " + "Class=" + messageClass);
  }
}




