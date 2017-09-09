
package com.gensym.tests;

import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.classes.*;
import com.gensym.util.*;

public class TransferTest {

  private static final Symbol CONNECTION_POST_ = Symbol.intern ("CONNECTION-POST");
  private static final Symbol KB_WORKSPACE_ = Symbol.intern ("KB-WORKSPACE");
  private static final Symbol TRANSFER_TARGET_ = Symbol.intern ("TRANSFER-TARGET");

  public static void main (String[] args) throws Exception {
    G2Access cxn = TwGateway.openConnection("bombay", "1111");
    KbWorkspace wksp = (KbWorkspace) cxn.getUniqueNamedItem (KB_WORKSPACE_, TRANSFER_TARGET_);
    Item newCP = cxn.createItem (CONNECTION_POST_);
    newCP.transferTo (wksp, 0, 0);
    System.out.println (newCP.getContainmentHierarchy ());
    newCP.transferOff ();
    System.out.println (newCP.getContainmentHierarchy ());

    newCP.transferTo (wksp, 10, 0);
    System.out.println (newCP.getContainmentHierarchy ());
    newCP.transferOff ();
    System.out.println (newCP.getContainmentHierarchy ());

    newCP.transferTo (wksp, 20, 0);
    System.out.println (newCP.getContainmentHierarchy ());
    newCP.transferOff ();
    System.out.println (newCP.getContainmentHierarchy ());

    newCP.transferTo (wksp, 30, 0);
    System.out.println (newCP.getContainmentHierarchy ());
    newCP.transferOff ();
    System.out.println (newCP.getContainmentHierarchy ());

    newCP.transferTo (wksp, 40, 0);
    System.out.println (newCP.getContainmentHierarchy ());
    newCP.transferOff ();
    System.out.println (newCP.getContainmentHierarchy ());

    System.exit (0);
  }

}
