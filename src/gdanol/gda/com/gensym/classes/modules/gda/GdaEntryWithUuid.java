/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdaEntryWithUuid.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Jun 26 13:41:47 EDT 2000
 *
 */


package com.gensym.classes.modules.gda;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface GdaEntryWithUuid extends com.gensym.classes.modules.gqm.GqmEntry, com.gensym.classes.modules.gfr.GfrObjectWithUuid {

  public static final Symbol GDA_ENTRY_WITH_UUID_ = Symbol.intern ("GDA-ENTRY-WITH-UUID");
  static final Symbol g2ClassName = GDA_ENTRY_WITH_UUID_;
  static final Symbol[] classInheritancePath = new Symbol[] {GDA_ENTRY_WITH_UUID_, GQM_ENTRY_, GFR_OBJECT_WITH_UUID_, OBJECT_, GFR_ITEM_WITH_UUID_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Auto Generated method for G2 Method
   * GDA-ENTRY-WITH-UUID::GQM-ENTRY-CONSTRUCTOR
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDA-ENTRY-WITH-UUID,arg1:CLASS GQM-QUEUE,arg2:STRUCTURE,arg3:CLASS OBJECT) = ()
   */
  public  void gqmEntryConstructor(com.gensym.classes.modules.gqm.GqmQueue arg1,com.gensym.util.Structure arg2,com.gensym.classes.Object arg3) throws G2AccessException;
  
}
