

package com.gensym.tests;

import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.message.Trace;

public class ClassInheritancePathTest {

  private static final Symbol G2_GET_CLASS_INHERITANCE_PATH_ = Symbol.intern ("G2-GET-CLASS-INHERITANCE-PATH");
  private static final Symbol G2_WINDOW_ = Symbol.intern ("G2-WINDOW");
  private static final Symbol YYY_ = Symbol.intern ("YYY");

  public static void main (String[] args) throws ConnectionTimedOutException, G2AccessException {
    String host = "vpillai1";
    String port = "1111";
    G2Access context = G2Gateway.getOrMakeConnection (host, port);
    java.lang.Object iconDescription;
    java.lang.Object bababa;

    Sequence s;
    try {
      s = (Sequence) context.callRPC (G2_GET_CLASS_INHERITANCE_PATH_, new Object[] {G2_WINDOW_});
      System.out.println (s);
    } catch (G2AccessException gae) {
      System.err.println (gae);
    }


    try {
      s = (Sequence) context.callRPC (G2_GET_CLASS_INHERITANCE_PATH_, new Object[] {YYY_});
    } catch (G2AccessException gae) {
      System.err.println (gae);
    }

  }
}
