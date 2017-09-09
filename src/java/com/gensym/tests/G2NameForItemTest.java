
package com.gensym.tests;

import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.classes.*;
import com.gensym.util.*;

public class G2NameForItemTest {

  private static final Symbol ITEM_ = Symbol.intern ("ITEM");
  private static final Symbol HELLO_ = Symbol.intern ("HELLO2");
  private static final Symbol G2_NAME_FOR_ITEM_ = Symbol.intern ("G2-NAME-FOR-ITEM");

  public static void main (String[] args) throws Exception {
    G2Access cxn = TwGateway.openConnection("otter", "1111");
    Item itm = cxn.getUniqueNamedItem (ITEM_, HELLO_);
    ((Block)itm).setNames (null);
    java.lang.Object x = cxn.callRPC (G2_NAME_FOR_ITEM_, new java.lang.Object[] {itm});
    System.out.println ("Item is now : " + x.toString ());
    System.exit (0);
  }

}
