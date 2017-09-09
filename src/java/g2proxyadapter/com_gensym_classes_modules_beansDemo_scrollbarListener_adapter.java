/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      com_gensym_classes_modules_beansDemo_scrollbarListener_adapter.java
 *
 *   Description: Generated G2 Java Proxy Interface Adpater. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1
 *
 *          Date: Mon Feb 08 22:46:51 EST 1999
 *
 */


package g2proxyadapter;

import com.gensym.util.*;
import com.gensym.jgi.*;
import com.gensym.classes.Item;

public class com_gensym_classes_modules_beansDemo_scrollbarListener_adapter implements java.io.Serializable,java.awt.event.AdjustmentListener{

  
  static final long serialVersionUID = -441189241920989898L;
  private G2JavaStubController controller;
  private Item g2InterfaceProxy;
  private G2Access context;
  
  // Do not use, here due to JIT problems
  public com_gensym_classes_modules_beansDemo_scrollbarListener_adapter() {}
  
  public com_gensym_classes_modules_beansDemo_scrollbarListener_adapter(G2JavaStubController controller, G2Access context, Item g2Proxy) { 
    this.controller = controller;
    this.g2InterfaceProxy = g2Proxy;
    this.context = context;
  }
  
  private static Symbol ADJUSTMENT_VALUE_CHANGED_ = Symbol.intern("ADJUSTMENT-VALUE-CHANGED");
  
  public void adjustmentValueChanged (java.awt.event.AdjustmentEvent arg0) {
    try {
      Object g2arg0= arg0;
      controller.callG2ProxyFromJava(
          context, ADJUSTMENT_VALUE_CHANGED_, new Object[] {g2InterfaceProxy,
g2arg0});
    } catch (G2AccessException e) {
      throw new RuntimeException(e.toString());
    }
  }
  
}
