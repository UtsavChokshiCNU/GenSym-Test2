/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      REmployeeImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Fri Sep 21 13:50:13 EDT 2007
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

public class REmployeeImpl extends com.gensym.classes.modules.jgidemo.RepositoryObjectImpl implements REmployee {


  static final long serialVersionUID = 2L;
  private static final Symbol SOCIAL_SECURITY_NUMBER_ = Symbol.intern ("SOCIAL-SECURITY-NUMBER");
  private static final Symbol TITLE_ = Symbol.intern ("TITLE");
  private static final Symbol SUPERVISOR_ = Symbol.intern ("SUPERVISOR");
  private static final Symbol PAY_SCALE_ = Symbol.intern ("PAY-SCALE");

  /* Generated constructors */

  public REmployeeImpl() {
    super();
  }

  public REmployeeImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public REmployeeImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- SOCIAL-SECURITY-NUMBER
   * @param socialSecurityNumber new value to conclude for SOCIAL-SECURITY-NUMBER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSocialSecurityNumber(com.gensym.classes.modules.jgidemo.RaSymbolicParameter socialSecurityNumber) throws G2AccessException {
    setAttributeValue (SOCIAL_SECURITY_NUMBER_, socialSecurityNumber);
  }

  /**
   * Generated Property Getter for attribute -- SOCIAL-SECURITY-NUMBER
   * @return the value of the SOCIAL-SECURITY-NUMBER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.classes.modules.jgidemo.RaSymbolicParameter getSocialSecurityNumber() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SOCIAL_SECURITY_NUMBER_);
    return (com.gensym.classes.modules.jgidemo.RaSymbolicParameter)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TITLE
   * @param title new value to conclude for TITLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTitle(com.gensym.classes.modules.jgidemo.RaSymbolicParameter title) throws G2AccessException {
    setAttributeValue (TITLE_, title);
  }

  /**
   * Generated Property Getter for attribute -- TITLE
   * @return the value of the TITLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.classes.modules.jgidemo.RaSymbolicParameter getTitle() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (TITLE_);
    return (com.gensym.classes.modules.jgidemo.RaSymbolicParameter)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SUPERVISOR
   * @param supervisor new value to conclude for SUPERVISOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSupervisor(com.gensym.classes.modules.jgidemo.RaSymbolicParameter supervisor) throws G2AccessException {
    setAttributeValue (SUPERVISOR_, supervisor);
  }

  /**
   * Generated Property Getter for attribute -- SUPERVISOR
   * @return the value of the SUPERVISOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.classes.modules.jgidemo.RaSymbolicParameter getSupervisor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SUPERVISOR_);
    return (com.gensym.classes.modules.jgidemo.RaSymbolicParameter)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- PAY-SCALE
   * @param payScale new value to conclude for PAY-SCALE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPayScale(com.gensym.classes.modules.jgidemo.RaIntegerParameter payScale) throws G2AccessException {
    setAttributeValue (PAY_SCALE_, payScale);
  }

  /**
   * Generated Property Getter for attribute -- PAY-SCALE
   * @return the value of the PAY-SCALE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.classes.modules.jgidemo.RaIntegerParameter getPayScale() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (PAY_SCALE_);
    return (com.gensym.classes.modules.jgidemo.RaIntegerParameter)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
