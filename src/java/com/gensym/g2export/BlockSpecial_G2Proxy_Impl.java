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

public class BlockSpecial_G2Proxy_Impl extends G2__BaseImpl {

  public java.lang.Object getName() {
    return getNames();
  }

  public void setName(Object name) throws NamingException {
    setNames(name);
  }

  public java.lang.Object getNames() {
    return getObjectContainer().getRegisteredName();
  }

  public void setNames(Object newNamesObj) throws javax.naming.NamingException {
      String newName = null;
      if (newNamesObj instanceof Symbol)
	newName = ((Symbol)newNamesObj).toString();
      getObjectContainer().setRegisteredName(newName);
  }


}
