/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      DbQueryItemListImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Thu Jun 18 17:45:43 EEST 2009
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

public class DbQueryItemListImpl extends com.gensym.classes.modules.g2database.DbQueryItemImpl implements DbQueryItemList {


  static final long serialVersionUID = 2L;
  private static final Symbol DB_COL_NAMES_ = Symbol.intern ("DB-COL-NAMES");
  private static final Symbol DB_COL_VALUES_ = Symbol.intern ("DB-COL-VALUES");

  /* Generated constructors */

  public DbQueryItemListImpl() {
    super();
  }

  public DbQueryItemListImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public DbQueryItemListImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- DB-COL-NAMES
   * @param dbColNames new value to conclude for DB-COL-NAMES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDbColNames(java.lang.Object dbColNames) throws G2AccessException {
    setAttributeValue (DB_COL_NAMES_, dbColNames);
  }

  /**
   * Generated Property Getter for attribute -- DB-COL-NAMES
   * @return the value of the DB-COL-NAMES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getDbColNames() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (DB_COL_NAMES_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DB-COL-VALUES
   * @param dbColValues new value to conclude for DB-COL-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDbColValues(java.lang.Object dbColValues) throws G2AccessException {
    setAttributeValue (DB_COL_VALUES_, dbColValues);
  }

  /**
   * Generated Property Getter for attribute -- DB-COL-VALUES
   * @return the value of the DB-COL-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getDbColValues() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (DB_COL_VALUES_);
    return (java.lang.Object)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_DB_COPY_ = Symbol.intern ("DB-COPY");
  private static final Symbol MethodName_DB_DELETE_ = Symbol.intern ("DB-DELETE");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * DB-QUERY-ITEM-LIST::DB-COPY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS DB-QUERY-ITEM-LIST,arg1:CLASS ITEM) = ()
   */
  @Override
  public  void dbCopy(com.gensym.classes.Item arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_DB_COPY_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * DB-QUERY-ITEM-LIST::DB-DELETE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS DB-QUERY-ITEM-LIST) = ()
   */
  @Override
  public  void dbDelete() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_DB_DELETE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
