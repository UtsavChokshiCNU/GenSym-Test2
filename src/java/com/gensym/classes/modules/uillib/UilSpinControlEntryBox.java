/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilSpinControlEntryBox.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:12 EDT 2007
 *
 */


package com.gensym.classes.modules.uillib;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface UilSpinControlEntryBox extends com.gensym.classes.modules.uillib.UilEditBox {

  public static final Symbol UIL_SPIN_CONTROL_ENTRY_BOX_ = Symbol.intern ("UIL-SPIN-CONTROL-ENTRY-BOX");
  static final Symbol g2ClassName = UIL_SPIN_CONTROL_ENTRY_BOX_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_SPIN_CONTROL_ENTRY_BOX_, UIL_EDIT_BOX_, UIL_GRMES_, UIL_MESSAGE_, MESSAGE_, ITEM_, TEXT_BOX_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- UIL-SPIN-UP-BUTTON-ID
   * @return the value of the UIL-SPIN-UP-BUTTON-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SPIN-UP-BUTTON-ID is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilSpinUpButtonId() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SPIN-UP-BUTTON-ID
   * @param uilSpinUpButtonId new value to conclude for UIL-SPIN-UP-BUTTON-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilSpinUpButtonId(java.lang.Object uilSpinUpButtonId) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SPIN-DOWN-BUTTON-ID
   * @return the value of the UIL-SPIN-DOWN-BUTTON-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SPIN-DOWN-BUTTON-ID is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilSpinDownButtonId() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SPIN-DOWN-BUTTON-ID
   * @param uilSpinDownButtonId new value to conclude for UIL-SPIN-DOWN-BUTTON-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilSpinDownButtonId(java.lang.Object uilSpinDownButtonId) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SPIN-CONTROL-LOW-VALUE
   * @return the value of the UIL-SPIN-CONTROL-LOW-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SPIN-CONTROL-LOW-VALUE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilSpinControlLowValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SPIN-CONTROL-LOW-VALUE
   * @param uilSpinControlLowValue new value to conclude for UIL-SPIN-CONTROL-LOW-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilSpinControlLowValue(java.lang.Object uilSpinControlLowValue) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SPIN-CONTROL-HI-VALUE
   * @return the value of the UIL-SPIN-CONTROL-HI-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SPIN-CONTROL-HI-VALUE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilSpinControlHiValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SPIN-CONTROL-HI-VALUE
   * @param uilSpinControlHiValue new value to conclude for UIL-SPIN-CONTROL-HI-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilSpinControlHiValue(java.lang.Object uilSpinControlHiValue) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SPIN-CONTROL-INCREMENT
   * @return the value of the UIL-SPIN-CONTROL-INCREMENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SPIN-CONTROL-INCREMENT is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilSpinControlIncrement() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SPIN-CONTROL-INCREMENT
   * @param uilSpinControlIncrement new value to conclude for UIL-SPIN-CONTROL-INCREMENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilSpinControlIncrement(java.lang.Object uilSpinControlIncrement) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SPIN-CONTROL-PERMIT-WRAPPING
   * @return the value of the UIL-SPIN-CONTROL-PERMIT-WRAPPING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SPIN-CONTROL-PERMIT-WRAPPING is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilSpinControlPermitWrapping() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SPIN-CONTROL-PERMIT-WRAPPING
   * @param uilSpinControlPermitWrapping new value to conclude for UIL-SPIN-CONTROL-PERMIT-WRAPPING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilSpinControlPermitWrapping(java.lang.Object uilSpinControlPermitWrapping) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SPIN-CONTROL-INITIAL-VALUE
   * @return the value of the UIL-SPIN-CONTROL-INITIAL-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SPIN-CONTROL-INITIAL-VALUE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilSpinControlInitialValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SPIN-CONTROL-INITIAL-VALUE
   * @param uilSpinControlInitialValue new value to conclude for UIL-SPIN-CONTROL-INITIAL-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilSpinControlInitialValue(java.lang.Object uilSpinControlInitialValue) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SPIN-CONTROL-ATTACH-BORDER
   * @return the value of the UIL-SPIN-CONTROL-ATTACH-BORDER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SPIN-CONTROL-ATTACH-BORDER is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilSpinControlAttachBorder() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SPIN-CONTROL-ATTACH-BORDER
   * @param uilSpinControlAttachBorder new value to conclude for UIL-SPIN-CONTROL-ATTACH-BORDER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilSpinControlAttachBorder(java.lang.Object uilSpinControlAttachBorder) throws G2AccessException;

}
