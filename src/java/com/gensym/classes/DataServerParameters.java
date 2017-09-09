/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      DataServerParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:37:37 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface DataServerParameters extends com.gensym.classes.SystemTable {

  public static final Symbol DATA_SERVER_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.DATA_SERVER_PARAMETERS_;
  static final Symbol g2ClassName = DATA_SERVER_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {DATA_SERVER_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- PRIORITY-OF-DATA-SERVICE
   * @return the value of the PRIORITY-OF-DATA-SERVICE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PRIORITY-OF-DATA-SERVICE is : 
   * (MEMBER 1 2 3 4 5 6 7 8 9 10)
   *
   */
  public com.gensym.util.Symbol getPriorityOfDataService() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PRIORITY-OF-DATA-SERVICE
   * @param priorityOfDataService new value to conclude for PRIORITY-OF-DATA-SERVICE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPriorityOfDataService(com.gensym.util.Symbol priorityOfDataService) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-METER-DATA-SERVICE-ON
   * @return the value of the G2-METER-DATA-SERVICE-ON attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-METER-DATA-SERVICE-ON is : 
   * BooleanTruthValue
   *
   */
  public boolean getG2MeterDataServiceOn() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- G2-METER-DATA-SERVICE-ON
   * @param g2MeterDataServiceOn new value to conclude for G2-METER-DATA-SERVICE-ON
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setG2MeterDataServiceOn(boolean g2MeterDataServiceOn) throws G2AccessException;

}
