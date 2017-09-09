/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2ArraySpecialImpl.java
 *
 *      Author: Gensym Corp.
 *
 */


package com.gensym.g2export;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.g2scriptruntime.G2ArrayAccess;
import com.gensym.jgi.G2AccessException;

public class G2ArraySpecial_G2Proxy_Impl extends G2__BaseImpl 
     implements com.gensym.g2scriptruntime.G2ArrayAccess {


  /**
   * 1
   */
  @Override
  public java.lang.Object getArray() {
    com.gensym.classes.G2__Base g2Proxy = ((G2ProxyAccess)this)._getG2Item();
    if (g2Proxy == null) {
	 java.lang.Object array = 
	   invokeMyRemoteMethod("getArray", 
				null,
				null);
	return array;
    }
    try {
      com.gensym.classes.G2Array g2Array = (com.gensym.classes.G2Array)g2Proxy;
      // Must resolve Array here !
      return g2Array.getG2ArrayContents();
    } catch (G2AccessException e) {
      throw new RuntimeException(e.toString());
    }
  }

  /**
   * 2
   */
  @Override
  public void  setArray(java.lang.Object array) {
    com.gensym.classes.G2__Base g2Proxy = ((G2ProxyAccess)this)._getG2Item();
    if (g2Proxy == null) {
       invokeMyRemoteMethod("setArray", 
			    new java.lang.Object[] {array},
			    new String[] {"java.lang.Object"});
	return;
    }
    try {
      com.gensym.classes.G2Array g2Array = (com.gensym.classes.G2Array)g2Proxy;
      // Must resolve here
      g2Array.setG2ArrayContents(array);
    } catch (G2AccessException e) {
      throw new RuntimeException(e.toString());
    }
  }

  /**
   * 3
   */
  @Override
  public synchronized void setArrayLength(int size) {
    com.gensym.classes.G2__Base g2Proxy = ((G2ProxyAccess)this)._getG2Item();
    if (g2Proxy == null) {
        invokeMyRemoteMethod("setArrayLength", 
			     new java.lang.Object[] {new Integer(size)},
			     new String[] {"int"});
	return;
    }
    // Not Supported in G2Stub !
    //try {
    //  com.gensym.classes.G2Array g2Array = (com.gensym.classes.G2Array)g2Proxy;
      //g2Array.setArrayLength(size);
    //} catch (G2AccessException e) {
    //  throw new RuntimeException(e.toString());
    //}
  }

  /**
   * 4
   */
  @Override
  public int getArrayLength() {
    com.gensym.classes.G2__Base g2Proxy = ((G2ProxyAccess)this)._getG2Item();
    if (g2Proxy == null) {
	 java.lang.Integer Int = (Integer)invokeMyRemoteMethod("getArrayLength", 
							       null,
							       null);
	return Int.intValue();
    }
    try {
      com.gensym.classes.G2Array g2Array = (com.gensym.classes.G2Array)g2Proxy;
      return g2Array.getArrayLength();
    } catch (G2AccessException e) {
      throw new RuntimeException(e.toString());
    }
  }

}


