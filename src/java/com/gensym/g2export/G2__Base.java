/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2__Base.java
 *
 *      Author: Gensym Corp.
 *
 */


package com.gensym.g2export;

import com.gensym.util.ExportedG2Class;
import com.gensym.fida.DistributedObject;
import com.gensym.fida.message.MessageHandler;
import com.gensym.fida.Implementor;
import com.gensym.fida.MobilityListener;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;

public interface G2__Base extends DistributedObject, 
                                  MessageHandler, 
                                  ExportedG2Class, 
                                  Implementor,
                                  MobilityListener {

  public static Symbol g2ClassName = Symbol.intern("NON-EXISTENT");

  public Symbol getG2ClassName();

  //public static boolean recorded = G2ClassManager.recordG2ClassNameForClass(g2ClassName, null);
}
