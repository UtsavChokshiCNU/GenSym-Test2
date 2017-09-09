
package com.gensym.tests;

import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.classes.*;
import com.gensym.util.*;

public class StubInvalidationTest {

  private static final Symbol ITEM_ = Symbol.intern ("ITEM");
  private static final Symbol HELLO_ = Symbol.intern ("HELLO");
  private static final Symbol G2_SUBSCRIBE_TO_MODULES_ = Symbol.intern ("G2-SUBSCRIBE-TO-MODULES");
  private static final Symbol HANDLEMODULESUBSCRIPTIONS_ = Symbol.intern ("HANDLEMODULESUBSCRIPTIONS");
  private static final Symbol HANDLEITEMSUBSCRIPTIONS_ = Symbol.intern ("HANDLEITEMSUBSCRIPTIONS");
  private static final Symbol LOGBOOK_ = Symbol.intern ("LOGBOOK");

  public static void main (String[] args) throws Exception {
    G2Access cxn = TwGateway.openConnection("localhost", "1111");
    Item itm = cxn.getUniqueNamedItem (ITEM_, HELLO_);

    StubInvalidationListener sil = new StubInvalidationListener () {
      @Override
      public void stubIsInvalid (StubInvalidationEvent evt) {
	System.out.println (evt.getSource() + " is Invalid!!!");
      }
    };

    ((G2__RemoteStub)itm).addStubInvalidationListener (sil);
    
    Structure subscrModRetn = 
      (Structure) cxn.callRPC (G2_SUBSCRIBE_TO_MODULES_,
			       new java.lang.Object[] {HANDLEMODULESUBSCRIPTIONS_, new Integer (42),
							 HANDLEITEMSUBSCRIPTIONS_, new Integer (32)});
    Sequence logbookPages =(Sequence) subscrModRetn.getAttributeValue (LOGBOOK_, null);
    for (int i=0; i<logbookPages.size(); i++) {
      Item page = (Item)logbookPages.elementAt (i);
      System.out.println (page);
      ((G2__RemoteStub)page).addStubInvalidationListener (sil);
    }
  }

}
