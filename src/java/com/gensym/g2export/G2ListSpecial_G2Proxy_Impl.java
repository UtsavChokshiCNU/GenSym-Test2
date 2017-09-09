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
import com.gensym.util.CheckedSequence;
import com.gensym.util.Symbol;
import com.gensym.g2scriptruntime.G2ListAccess;
import com.gensym.jgi.G2AccessException;

public class G2ListSpecial_G2Proxy_Impl extends G2__BaseImpl 
     implements com.gensym.g2scriptruntime.G2ListAccess {

  /**
   * Returns the Sequence used internally to store the G2List data.
   */
  @Override
  public com.gensym.util.CheckedSequence getList() {
    com.gensym.classes.G2__Base g2Proxy = ((G2ProxyAccess)this)._getG2Item();
    if (g2Proxy == null) {
	 com.gensym.util.CheckedSequence list = 
	   (com.gensym.util.CheckedSequence)invokeMyRemoteMethod("getList", 
								 null,
								 null);
	return list;
    }
    try {
      com.gensym.classes.G2List g2List = (com.gensym.classes.G2List)g2Proxy;
      return new CheckedSequence(g2List.getG2ListSequence());
    } catch (G2AccessException e) {
      throw new RuntimeException(e.toString());
    }
  }

  /**
   * Set the Sequence used internally to store the G2List data.
   * The original Sequence will no longer be referenced by the G2List.
   */
  @Override
  public void setList(com.gensym.util.CheckedSequence list)  {
    com.gensym.classes.G2__Base g2Proxy = ((G2ProxyAccess)this)._getG2Item();
    if (g2Proxy == null) {
      invokeMyRemoteMethod("setList", 
			   new java.lang.Object[] {list},
			   null);
      return;
    }
    try {
      com.gensym.classes.G2List g2List = (com.gensym.classes.G2List)g2Proxy;
      g2List.getG2ListSequence();
    } catch (G2AccessException e) {
      throw new RuntimeException(e.toString());
    }
  }

  @Override
  public boolean getAllowDuplicateElements() {
    com.gensym.classes.G2__Base g2Proxy = ((G2ProxyAccess)this)._getG2Item();
    if (g2Proxy == null) {
	Boolean Bool = (Boolean)invokeMyRemoteMethod("getAllowDuplicateElements", 
						     null,
						     null);
	return Bool.booleanValue();
    }
    try {
      com.gensym.classes.G2List g2List = (com.gensym.classes.G2List)g2Proxy;
      return g2List.getAllowDuplicateElements();
    } catch (G2AccessException e) {
      throw new RuntimeException(e.toString());
    }
  }
       
  @Override
  public void setAllowDuplicateElements(boolean state) {
    com.gensym.classes.G2__Base g2Proxy = ((G2ProxyAccess)this)._getG2Item();
    if (g2Proxy == null) {
	invokeMyRemoteMethod("setAllowDuplicateElements", 
			     new java.lang.Object[] {new Boolean(state)},
			     new String[] {"boolean"});
	return;
    }
    try {
      com.gensym.classes.G2List g2List = (com.gensym.classes.G2List)g2Proxy;
      g2List.setAllowDuplicateElements(state);
    } catch (G2AccessException e) {
      throw new RuntimeException(e.toString());
    }
  }
  
}
