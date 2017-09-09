/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      DbQueryItemList.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Thu Jun 18 17:45:42 EEST 2009
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

public interface DbQueryItemList extends com.gensym.classes.modules.g2database.DbQueryItem {

  public static final Symbol DB_QUERY_ITEM_LIST_ = Symbol.intern ("DB-QUERY-ITEM-LIST");
  static final Symbol g2ClassName = DB_QUERY_ITEM_LIST_;
  static final Symbol[] classInheritancePath = new Symbol[] {DB_QUERY_ITEM_LIST_, DB_QUERY_ITEM_, SYMBOLIC_VARIABLE_, G2_VARIABLE_, VARIABLE_, VARIABLE_OR_PARAMETER_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- DB-COL-NAMES
   * @return the value of the DB-COL-NAMES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DB-COL-NAMES is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getDbColNames() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DB-COL-NAMES
   * @param dbColNames new value to conclude for DB-COL-NAMES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDbColNames(java.lang.Object dbColNames) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DB-COL-VALUES
   * @return the value of the DB-COL-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DB-COL-VALUES is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getDbColValues() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DB-COL-VALUES
   * @param dbColValues new value to conclude for DB-COL-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDbColValues(java.lang.Object dbColValues) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * DB-QUERY-ITEM-LIST::DB-COPY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS DB-QUERY-ITEM-LIST,arg1:CLASS ITEM) = ()
   */
  public  void dbCopy(com.gensym.classes.Item arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * DB-QUERY-ITEM-LIST::DB-DELETE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS DB-QUERY-ITEM-LIST) = ()
   */
  @Override
  public  void dbDelete() throws G2AccessException;
  
}
