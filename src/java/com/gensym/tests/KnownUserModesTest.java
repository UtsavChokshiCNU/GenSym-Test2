

package com.gensym.tests;

import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.util.Symbol;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Sequence;
import com.gensym.message.Trace;

public class KnownUserModesTest {
  private static final Symbol G2_GET_KNOWN_USER_MODES_ = Symbol.intern ("G2-GET-KNOWN-USER-MODES");
  private static final Symbol ITEM_ = Symbol.intern ("ITEM");
  private static final Symbol TEST_ITEM_ = Symbol.intern ("TEST-ITEM");
  private static final Symbol NAMES_ = Symbol.intern ("NAMES");
  private static final Symbol T2_ = Symbol.intern ("T2");

  public static void main (String[] args) throws ConnectionTimedOutException, G2AccessException, NoSuchAttributeException {
    String host = "bombay";
    String port = "1112";
    G2Access context = G2Gateway.getOrMakeConnection (host, port);

    Object modes = context.callRPC (G2_GET_KNOWN_USER_MODES_, new Object[] {});

    System.out.println ("Modes = " + modes);
    System.exit (0);
  }
}

