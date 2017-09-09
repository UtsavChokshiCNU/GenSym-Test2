

package com.gensym.tests;

import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.ClassManager;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Sequence;
import com.gensym.message.Trace;

public class StaticAttributeAccessesTest {

  private static final Symbol ICONIC_SUB_OBJECT_ = Symbol.intern ("ICONIC-SUB-OBJECT");

  public static void main (String[] args) throws ConnectionTimedOutException, G2AccessException, NoSuchAttributeException, InterruptedException {
    com.gensym.core.GensymApplication.initialize (args);
    String host = "localhost";
    String port = "1111";
    G2Access context = G2Gateway.getOrMakeConnection (host, port);

    ClassManager cm = context.getClassManager ();

    Structure id = (Structure) cm.getClassAttributeValue (ICONIC_SUB_OBJECT_, SystemAttributeSymbols.ICON_DESCRIPTION_);
    System.out.println (id + "\n\n");

    Thread.sleep (20000);

    id = (Structure) cm.getClassAttributeValue (ICONIC_SUB_OBJECT_, SystemAttributeSymbols.ICON_DESCRIPTION_);
    System.out.println (id + "\n\n");
  }
}

