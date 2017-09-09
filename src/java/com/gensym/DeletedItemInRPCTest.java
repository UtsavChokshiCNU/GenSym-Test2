
package com.gensym.tests;

import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.core.*;
import com.gensym.classes.Item;
import com.gensym.classes.Block;


public class DeletedItemInRPCTest {
  private static final Symbol HEKKO_ = Symbol.intern ("HEKKO");
  private static final Symbol CONNECTION_POST_ = Symbol.intern ("CONNECTION-POST");

  public static void main (String[] args) throws Exception {
    String host = "bombay";
    String port = "1111";

    GensymApplication.initialize (args);
    G2Gateway cxn = (G2Gateway) G2Gateway.getOrMakeConnection (host, port);
    Block itm = (Block)cxn.createItem (CONNECTION_POST_);
    itm.setNames (HEKKO_);
    Object names = itm.getNames ();
    System.out.println ("Name of item = " + names);
    ((Item)itm).delete (true, false);
    names = itm.getNames ();
    System.out.println ("Name of item = " + names);
  }

}
