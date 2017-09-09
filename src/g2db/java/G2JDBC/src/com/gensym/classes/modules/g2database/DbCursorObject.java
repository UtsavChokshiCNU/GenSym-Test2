/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      DbCursorObject.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Thu Jun 18 17:47:30 EEST 2009
 *
 */


package com.gensym.classes.modules.g2database;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface DbCursorObject extends com.gensym.classes.modules.g2database.DbConfigObject {

  public static final Symbol DB_CURSOR_OBJECT_ = Symbol.intern ("DB-CURSOR-OBJECT");
  static final Symbol g2ClassName = DB_CURSOR_OBJECT_;
  static final Symbol[] classInheritancePath = new Symbol[] {DB_CURSOR_OBJECT_, DB_CONFIG_OBJECT_, GSI_DATA_SERVICE_, SYMBOLIC_VARIABLE_, G2_VARIABLE_, VARIABLE_, VARIABLE_OR_PARAMETER_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- DB-CURSOR-POSITION
   * @return the value of the DB-CURSOR-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DB-CURSOR-POSITION is : 
   * Integer
   *
   */
  public int getDbCursorPosition() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DB-CURSOR-POSITION
   * @param dbCursorPosition new value to conclude for DB-CURSOR-POSITION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDbCursorPosition(int dbCursorPosition) throws G2AccessException;

}
