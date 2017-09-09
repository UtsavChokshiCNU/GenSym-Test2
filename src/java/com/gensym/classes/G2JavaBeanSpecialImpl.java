/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2JavaBeanSpecialImpl.java
 *
 *       Version: 5.1 Rev. 0
 *
 *          Date: August 14, 1998
 *
 */

package com.gensym.classes;

import java.io.*;
import java.util.Vector;
import com.gensym.message.Trace;
import com.gensym.util.*;
import com.gensym.jgi.G2AccessException;

public class G2JavaBeanSpecialImpl extends ItemImpl {

  private static final Symbol sizeKey = Symbol.intern("SIZE-IN-BYTES");
  private static final Symbol CONTENTS_ = Symbol.intern ("CONTENTS");

  /**
   * Retrieve a serialized template object from the bean
   * @return The cached Object
   * @exception G2AccessException If an error occurs during communication with G2.
   */
  public java.lang.Object retrieveObject () throws G2AccessException {
    if (this instanceof G2ForeignSerializable) {
      try {
	MediaBin dataBin = ((G2JavaBean)this).getInternalMediaBin ();
	Vector location = new Vector ();
	Structure description = dataBin.describe (location);
	Sequence files = (Sequence) description.getAttributeValue (CONTENTS_, null);
	if (files.indexOf ("object") < 0)
	  return null;
	G2BinaryInputStream mbis = dataBin.makeBinaryInputStream (location, "object");
	Structure metaData = dataBin.describe(location, "object");
	Integer size
	  = (Integer) metaData.getAttributeValue(sizeKey,sizeKey);
	int fileSize = size.intValue();
	byte[] objectData = new byte[fileSize];
	for (int i = 0; i<fileSize;i++) {
	  objectData[i] = (byte)mbis.read();
	}
	mbis.close();
	ByteArrayInputStream bis = new ByteArrayInputStream (objectData);
	ObjectInputStream ois = new ObjectInputStream (bis);
	java.lang.Object savedObject = ois.readObject ();
	return savedObject;
      } catch (ClassNotFoundException cnfe) {
	Trace.exception (cnfe);
	throw new RuntimeException ("Class not found during object read : " + cnfe);
      } catch (IOException ioe) {
	Trace.exception (ioe);
	throw new RuntimeException ("IOException during object read : " + ioe);
      }
    } else
      throw new RuntimeException ("Unsupported Persistence type");
  }

  /**
   * Save a template object
   * @param obj the template object to be serialized
   * exception G2AccessException If an error occurs during communication with G2.
   */
  public void saveObject (java.lang.Object obj) throws G2AccessException {
    if (this instanceof G2ForeignSerializable) {
      try {
	MediaBin dataBin = ((G2JavaBean)this).getInternalMediaBin ();
	Vector location = new Vector ();
	G2BinaryOutputStream mbos = dataBin.makeBinaryOutputStream (location, "object");
	ObjectOutputStream oos = new ObjectOutputStream (mbos);
	oos.writeObject (obj);
	oos.close ();
      } catch (IOException ioe) {
	Trace.exception (ioe);
	throw new RuntimeException ("IOException during object write : " + ioe);
      }
    } else
      throw new RuntimeException ("Unsupported Persistence type");
  }
}
