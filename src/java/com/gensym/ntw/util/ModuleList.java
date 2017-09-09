/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ModuleList.java
 *
 */
package com.gensym.ntw.util;

import java.util.Vector;
import com.gensym.classes.Module;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Sorter;
import com.gensym.util.Symbol;
import javax.swing.JList;
import java.text.Collator;
import com.gensym.util.SorterSupport;

public class ModuleList extends JList {
  private static final Symbol UNSPECIFIED_ = Symbol.intern("UNSPECIFIED");
  static {
    Class symbolClass =  com.gensym.util.Symbol.class;
    Class[] args = {symbolClass,symbolClass};
    try {
      SorterSupport.setDefaultCompareMethod
	(symbolClass, com.gensym.ntw.util.ModuleList.class.getMethod("compare", args));
    } catch (java.lang.NoSuchMethodException nsme) {
      Trace.exception(nsme);
    }
  }
  public static int compare(Symbol s1, Symbol s2){
    return Collator.getInstance().compare(s1.toString(), s2.toString());
  }
  
  public ModuleList(TwAccess cxn) {
    setFont(com.gensym.uitools.utils.FontUtil.sanserifPlain11);
    try {
      Module[] modules = cxn.getKb().getModules();
      Symbol[] moduleNames = new Symbol[modules.length];
      Symbol name;
      for (int j=0; j<modules.length; j++) {
	name = modules[j].getName();
	moduleNames[j] = (name != null ? name : UNSPECIFIED_);
      }
      Sorter.sort(moduleNames, Sorter.ASCENDING);
      Vector moduleVector = new Vector();
      for (int i=0; i<modules.length; i++)
	moduleVector.addElement(moduleNames[i].toString().toLowerCase());
      setListData(moduleVector);
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }

}


