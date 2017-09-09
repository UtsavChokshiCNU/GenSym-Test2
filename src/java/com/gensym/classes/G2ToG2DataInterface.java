/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2ToG2DataInterface.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:45:25 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface G2ToG2DataInterface extends com.gensym.classes.NetworkInterface {

  public static final Symbol G2_TO_G2_DATA_INTERFACE_ = com.gensym.util.symbol.G2ClassSymbols.G2_TO_G2_DATA_INTERFACE_;
  static final Symbol g2ClassName = G2_TO_G2_DATA_INTERFACE_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2_TO_G2_DATA_INTERFACE_, NETWORK_INTERFACE_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- ICP-CONNECTION-SPECIFICATION
   * @return the value of the ICP-CONNECTION-SPECIFICATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ICP-CONNECTION-SPECIFICATION is : 
   * (OR NoItem
      (Structure 
        NETWORK-TRANSPORT
          (MEMBER TCP-IP LOCALNET)
        HOSTNAME
          (OR Text
              Symbol)
        PORT
          (OR Integer
              Symbol
              NoItem)))
   *
   */
  public com.gensym.util.Structure getIcpConnectionSpecification() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ICP-CONNECTION-SPECIFICATION
   * @param icpConnectionSpecification new value to conclude for ICP-CONNECTION-SPECIFICATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setIcpConnectionSpecification(com.gensym.util.Structure icpConnectionSpecification) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INTERFACE-STATUS
   * @return the value of the INTERFACE-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INTERFACE-STATUS is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text)
   *
   */
  public java.lang.Object getInterfaceStatus() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INTERFACE-IS-SECURE
   * @return the value of the INTERFACE-IS-SECURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INTERFACE-IS-SECURE is : 
   * BooleanTruthValue
   *
   */
  public boolean getInterfaceIsSecure() throws G2AccessException;

}
