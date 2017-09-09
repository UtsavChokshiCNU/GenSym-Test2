/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2Definition.java
 *
 *        Author: vkp
 *       Version: 1.0 - 10/24/97
 *

 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.jgi.*;

/** Encapsulates the powers of all class definitions in G2, both user-defined
 * and System-defined. */
public interface G2Definition {

  public static final Symbol G2_DEFINITION_ = Symbol.intern ("G2-DEFINITION");

  static final Symbol g2ClassName = G2_DEFINITION_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2_DEFINITION_};

  static final Symbol[] staticAttributes = new Symbol[] {};


  public com.gensym.util.Symbol getClassName() throws G2AccessException;

  public com.gensym.util.Sequence getDirectSuperiorClasses() throws G2AccessException;

  public com.gensym.util.Sequence getClassSpecificAttributes() throws G2AccessException;

  public boolean getInstantiate() throws G2AccessException;

  public boolean getIncludeInMenus() throws G2AccessException;

  public com.gensym.util.Sequence getClassInheritancePath() throws G2AccessException;

  public com.gensym.util.Sequence getSystemClassInheritancePath() throws G2AccessException;

  public com.gensym.util.Sequence getInheritedAttributes() throws G2AccessException;

  public com.gensym.util.Sequence getInitializableSystemAttributes() throws G2AccessException;

  public com.gensym.util.Sequence getAttributeInitializations() throws G2AccessException;

  public com.gensym.util.Structure getIconDescription() throws G2AccessException;

  /*
  public com.gensym.util.Structure getCrossSectionPattern() throws G2AccessException;

  public java.lang.Object getStubLength() throws G2AccessException;

  public com.gensym.util.Symbol getJunctionBlock() throws G2AccessException;

  public com.gensym.util.Structure getDefaultMessageProperties() throws G2AccessException;
  */

  public java.lang.Object getClassAttributeValue (com.gensym.util.Symbol attrName) throws G2AccessException;

}
