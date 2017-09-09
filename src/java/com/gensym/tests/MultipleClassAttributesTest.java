
package com.gensym.tests;

import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.message.*;

public class MultipleClassAttributesTest {

  private static final Symbol PROCEDURE_        = Symbol.intern ("PROCEDURE"),
                              ICON_DESCRIPTION_ = Symbol.intern ("ICON-DESCRIPTION"),
			      INSTANTIATE_      = Symbol.intern ("INSTANTIATE"),
			      INCLUDE_IN_MENUS_ = Symbol.intern ("INCLUDE-IN-MENUS");

  public static void main (String[] args) throws G2AccessException, ConnectionTimedOutException, AlreadyInitializedException {
    
    G2Gateway.initialize ();
    G2Access x = (G2Access) G2Gateway.getOrMakeConnection ("bombay", "1111");

    java.lang.Object value = x.getClassAttributeValue (PROCEDURE_, ICON_DESCRIPTION_);
    System.out.println ("Icon Description = " + value);
    value = x.getClassAttributeValue (PROCEDURE_, INSTANTIATE_);
    System.out.println ("Instantiate = " + value);
    value = x.getClassAttributeValue (PROCEDURE_, INCLUDE_IN_MENUS_);
    System.out.println ("Include In Menus = " + value);

    Sequence s = new Sequence ();
    s.addElement (ICON_DESCRIPTION_);
    s.addElement (INSTANTIATE_);
    s.addElement (INCLUDE_IN_MENUS_);
    value = x.getClassAttributeValues (PROCEDURE_, s);
    System.out.println ("Both attributes = " + value);
  }

}
