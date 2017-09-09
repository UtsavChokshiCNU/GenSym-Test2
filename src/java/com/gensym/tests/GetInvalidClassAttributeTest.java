
package com.gensym.tests;

import com.gensym.jgi.*;
import com.gensym.util.*;

public class GetInvalidClassAttributeTest {

  private static final Symbol G2_WINDOW_ = Symbol.intern ("G2-WINDOW");
  private static final Symbol ICON_DESCRIPTION_ = Symbol.intern ("ICON-DESCRIPTION");
  private static final Symbol BALLY_HOO_ = Symbol.intern ("BALLY-HOO");
  private static final Symbol G2__ = Symbol.intern ("G2-");

  public static void main (String[] args) throws Exception {
    G2Gateway cxn = (G2Gateway) G2Gateway.getOrMakeConnection ("bombay", "1111");
    ClassManager cm = cxn.getClassManager ();
    Object x = cm.getClassAttributeValue (G2_WINDOW_, ICON_DESCRIPTION_);
    System.out.println (x);
    try {
      x = cm.getClassAttributeValue (G2_WINDOW_, BALLY_HOO_);
      System.out.println (x);
    } catch (Exception e) {
      System.out.println (e);
    }

    try {
      x = cm.getClassAttributeValue (G2__, ICON_DESCRIPTION_);
      System.out.println (x);
    } catch (Exception e) {
      System.out.println (e);
      e.printStackTrace ();
    }
  }

}
