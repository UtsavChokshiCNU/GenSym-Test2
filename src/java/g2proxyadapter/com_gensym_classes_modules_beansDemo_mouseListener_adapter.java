/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      com_gensym_classes_modules_beansDemo_mouseListener_adapter.java
 *
 *   Description: Generated G2 Java Proxy Interface Adpater. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1
 *
 *          Date: Mon Feb 08 22:43:00 EST 1999
 *
 */


package g2proxyadapter;

import com.gensym.util.*;
import com.gensym.jgi.*;
import com.gensym.classes.Item;

public class com_gensym_classes_modules_beansDemo_mouseListener_adapter implements java.io.Serializable,java.awt.event.MouseListener{

  
  static final long serialVersionUID = -441189241920989898L;
  private G2JavaStubController controller;
  private Item g2InterfaceProxy;
  private G2Access context;
  
  // Do not use, here due to JIT problems
  public com_gensym_classes_modules_beansDemo_mouseListener_adapter() {}
  
  public com_gensym_classes_modules_beansDemo_mouseListener_adapter(G2JavaStubController controller, G2Access context, Item g2Proxy) { 
    this.controller = controller;
    this.g2InterfaceProxy = g2Proxy;
    this.context = context;
  }
  
  private static Symbol MOUSE_CLICKED_ = Symbol.intern("MOUSE-CLICKED");
  
  public void mouseClicked (java.awt.event.MouseEvent arg0) {
    try {
      Object g2arg0= arg0;
      controller.callG2ProxyFromJava(
          context, MOUSE_CLICKED_, new Object[] {g2InterfaceProxy,
g2arg0});
    } catch (G2AccessException e) {
      throw new RuntimeException(e.toString());
    }
  }
  
  private static Symbol MOUSE_PRESSED_ = Symbol.intern("MOUSE-PRESSED");
  
  public void mousePressed (java.awt.event.MouseEvent arg0) {
    try {
      Object g2arg0= arg0;
      controller.callG2ProxyFromJava(
          context, MOUSE_PRESSED_, new Object[] {g2InterfaceProxy,
g2arg0});
    } catch (G2AccessException e) {
      throw new RuntimeException(e.toString());
    }
  }
  
  private static Symbol MOUSE_RELEASED_ = Symbol.intern("MOUSE-RELEASED");
  
  public void mouseReleased (java.awt.event.MouseEvent arg0) {
    try {
      Object g2arg0= arg0;
      controller.callG2ProxyFromJava(
          context, MOUSE_RELEASED_, new Object[] {g2InterfaceProxy,
g2arg0});
    } catch (G2AccessException e) {
      throw new RuntimeException(e.toString());
    }
  }
  
  private static Symbol MOUSE_ENTERED_ = Symbol.intern("MOUSE-ENTERED");
  
  public void mouseEntered (java.awt.event.MouseEvent arg0) {
    try {
      Object g2arg0= arg0;
      controller.callG2ProxyFromJava(
          context, MOUSE_ENTERED_, new Object[] {g2InterfaceProxy,
g2arg0});
    } catch (G2AccessException e) {
      throw new RuntimeException(e.toString());
    }
  }
  
  private static Symbol MOUSE_EXITED_ = Symbol.intern("MOUSE-EXITED");
  
  public void mouseExited (java.awt.event.MouseEvent arg0) {
    try {
      Object g2arg0= arg0;
      controller.callG2ProxyFromJava(
          context, MOUSE_EXITED_, new Object[] {g2InterfaceProxy,
g2arg0});
    } catch (G2AccessException e) {
      throw new RuntimeException(e.toString());
    }
  }
  
}
