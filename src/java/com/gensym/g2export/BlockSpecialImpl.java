/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      BlockSpecialImpl.java
 *
 *      Author: Gensym Corp.
 *
 */


package com.gensym.g2export;

import javax.naming.NamingException;
import com.gensym.util.Symbol;

public class BlockSpecialImpl extends G2__BaseImpl {

  public java.lang.Object getName() {
    return getNames();
  }

  public void setName(java.lang.Object name) throws NamingException {
    setNames(name);
  }

  public java.lang.Object getNames() {
     if (remoteProxy != null)
      return invokeMyRemoteMethod("getName", null, null);
    return getObjectContainer().getRegisteredName();
  }

  public void setNames(java.lang.Object newNamesObj) throws javax.naming.NamingException {
    if (remoteProxy != null) {
      invokeMyRemoteMethod("setNames", new java.lang.Object[] {newNamesObj}, new String[] {"java.lang.Object"});
      return;
    }
    String newName = null;
    if (newNamesObj instanceof Symbol)
      newName = ((Symbol)newNamesObj).toString();
    getObjectContainer().setRegisteredName(newName);
  }


}
