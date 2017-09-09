
package com.gensym.tests;

import com.gensym.jgi.*;
import com.gensym.jgi.download.*;
import com.gensym.util.*;
import com.gensym.core.GensymApplication;
import com.gensym.classes.*;

public class DownloadRoundTrippedClassTest {

  private static final Symbol ITEM_ = Symbol.intern ("ITEM");
  private static final Symbol T_1_ = Symbol.intern ("T-1");
  private static final Symbol T0_ = Symbol.intern ("T0");
  private static final Symbol T1_ = Symbol.intern ("T1");

  public static void main (String[] args) throws Exception {
    GensymApplication.initialize (args);
    String host = "russia";
    String port = "1113";
    G2Access context = G2Gateway.getOrMakeConnection (host, port);

    ((G2Gateway)context).setGenerationMode (StubClassLoader.GENERATION_AUTO);
    Item x = context.getUniqueNamedItem (ITEM_, T_1_);
    ((G2Gateway)context).setGenerationMode (StubClassLoader.GENERATION_AUTO_NEAREST);
    System.out.println ("\n\n\n Test starting \n\n\n");
    x = context.getUniqueNamedItem (ITEM_, T0_);
    System.out.println ("T0 = " + x + "\n Sleeping...");
    try {
      Thread.sleep (10000);
    } catch (InterruptedException ie) {
    }
    System.out.println ("Waking...");
    x = context.getUniqueNamedItem (ITEM_, T1_);
    System.out.println ("T1 = " + x);
  }

}
