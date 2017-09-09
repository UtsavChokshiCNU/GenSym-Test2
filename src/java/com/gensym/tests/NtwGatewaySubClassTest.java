

package com.gensym.tests;

import com.gensym.ntw.*;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.classes.Item;

public class NtwGatewaySubClassTest implements ItemListener {

  public static transient NtwGatewaySubClass context;

  private static final Symbol ITEM_ = Symbol.intern ("ITEM"),
                              MY_ITEM_ = Symbol.intern ("MY-ITEM");

  public static void main (String[] args) throws Exception {

    String host = "bombay";
    String port = "1111";

    try {
      TwGateway.initialize ();
    } catch (AlreadyInitializedException e) {}
    TwGateway.startup ();

    context = (NtwGatewaySubClass)
    
    G2Gateway.getOrMakeConnection (new G2ConnectionInfo (null,
							 NtwGatewaySubClass.class.getName (),
							 host,
							 port,
							 "",
							 "UI-CLIENT-INTERFACE",
							 "NO-NAME-XX",
							 "TCPIP",
							 Boolean.TRUE,
							 "hello"));

    try {Thread.sleep (5000);} catch (InterruptedException ie) {}

    Item x = context.getUniqueNamedItem (ITEM_, MY_ITEM_);

    x.addItemListener (new NtwGatewaySubClassTest ());

  }

  @Override
  public void receivedInitialValues (ItemEvent e) {
    System.out.println ("receivedInitialValues () -> " + e);
  }

  @Override
  public void itemModified (ItemEvent e) {
    System.out.println ("itemModified () -> " + e);
  }

  @Override
  public void itemDeleted (ItemEvent e) {
    System.out.println ("itemDeleted () -> " + e);
  }


}
