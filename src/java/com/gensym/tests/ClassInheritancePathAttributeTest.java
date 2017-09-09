
package com.gensym.tests;

import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.util.Symbol;
import com.gensym.classes.G2Definition;

public class ClassInheritancePathAttributeTest {

  private static final Symbol G2_WINDOW_ = Symbol.intern ("G2-WINDOW");
  private static final Symbol MY_READOUT_TABLE_ = Symbol.intern ("MY-READOUT-TABLE");

  public static void main (String[] args) throws ConnectionTimedOutException, G2AccessException {
    String host = "bombay";
    String port = "1111";
    G2Access context = G2Gateway.getOrMakeConnection (host, port);

    G2Definition defn = context.getClassManager().getDefinition (G2_WINDOW_);
    System.out.println ("Full Inheritance Path = " + defn.getSystemClassInheritancePath ());
    System.out.println ("User Inheritance Path = " + defn.getClassInheritancePath ());

    defn = context.getClassManager().getDefinition (MY_READOUT_TABLE_);
    System.out.println ("Full Inheritance Path = " + defn.getSystemClassInheritancePath ());
    System.out.println ("User Inheritance Path = " + defn.getClassInheritancePath ());
    
  }

}
