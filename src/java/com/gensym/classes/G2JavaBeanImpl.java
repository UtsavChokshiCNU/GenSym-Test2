/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2JavaBeanImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:45:01 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import java.io.*;
import java.util.Vector;
import com.gensym.message.Trace;
import com.gensym.util.*;
import com.gensym.jgi.G2AccessException;

public class G2JavaBeanImpl extends com.gensym.classes.G2ForeignObjectImpl implements G2JavaBean {


  static final long serialVersionUID = 2L;

  /* Overriden Field */
  private static final Symbol sizeKey = Symbol.intern("SIZE-IN-BYTES");
  /* Overriden Field */
  private static final Symbol CONTENTS_ = Symbol.intern ("CONTENTS");
  /* Generated constructors */

  public G2JavaBeanImpl() {
    super();
  }

  public G2JavaBeanImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2JavaBeanImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Getter for attribute -- INTERNAL-MEDIA-BIN
   * @return the value of the INTERNAL-MEDIA-BIN attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.classes.MediaBin getInternalMediaBin() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INTERNAL_MEDIA_BIN_);
    return (com.gensym.classes.MediaBin)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- LATENT-LISTENERS
   * @param latentListeners new value to conclude for LATENT-LISTENERS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setLatentListeners(com.gensym.util.Structure latentListeners) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.LATENT_LISTENERS_, latentListeners);
  }

  /**
   * Generated Property Getter for attribute -- LATENT-LISTENERS
   * @return the value of the LATENT-LISTENERS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getLatentListeners() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.LATENT_LISTENERS_);
    return (com.gensym.util.Structure)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  /* Overriden method - SAVE-OBJECT */
  @Override
  public void saveObject (java.lang.Object obj) throws G2AccessException
 {
    
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

  /* Overriden method - RETRIEVE-OBJECT */
  @Override
  public java.lang.Object retrieveObject () throws G2AccessException
 {
    
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

  
}
