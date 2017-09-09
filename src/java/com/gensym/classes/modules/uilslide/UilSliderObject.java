/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilSliderObject.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:48 EDT 2007
 *
 */


package com.gensym.classes.modules.uilslide;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface UilSliderObject extends com.gensym.classes.modules.uilroot.UilGrobj {

  public static final Symbol UIL_SLIDER_OBJECT_ = Symbol.intern ("UIL-SLIDER-OBJECT");
  static final Symbol g2ClassName = UIL_SLIDER_OBJECT_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_SLIDER_OBJECT_, UIL_GROBJ_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- UIL-SLIDER-CREATION-FLAG
   * @return the value of the UIL-SLIDER-CREATION-FLAG attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SLIDER-CREATION-FLAG is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilSliderCreationFlag() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SLIDER-CREATION-FLAG
   * @param uilSliderCreationFlag new value to conclude for UIL-SLIDER-CREATION-FLAG
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilSliderCreationFlag(java.lang.Object uilSliderCreationFlag) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-UPDATE-VALUE
   * @return the value of the UIL-UPDATE-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-UPDATE-VALUE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilUpdateValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-UPDATE-VALUE
   * @param uilUpdateValue new value to conclude for UIL-UPDATE-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilUpdateValue(java.lang.Object uilUpdateValue) throws G2AccessException;

}
