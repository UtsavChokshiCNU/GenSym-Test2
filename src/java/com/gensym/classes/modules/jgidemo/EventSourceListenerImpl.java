/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      EventSourceListenerImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Fri Sep 21 13:50:07 EDT 2007
 *
 */


package com.gensym.classes.modules.jgidemo;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class EventSourceListenerImpl extends com.gensym.classes.modules.g2evliss.G2EventListenerImpl implements EventSourceListener {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public EventSourceListenerImpl() {
    super();
  }

  public EventSourceListenerImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public EventSourceListenerImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  // Method Name Constants
  private static final Symbol MethodName_AN_EVENT_ = Symbol.intern ("AN-EVENT");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * EVENT-SOURCE-LISTENER::AN-EVENT
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS EVENT-SOURCE-LISTENER,arg1:CLASS EVENT-SOURCE-EVENT) = ()
   */
  @Override
  public  void anEvent(com.gensym.classes.modules.jgidemo.EventSourceEvent arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_AN_EVENT_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
