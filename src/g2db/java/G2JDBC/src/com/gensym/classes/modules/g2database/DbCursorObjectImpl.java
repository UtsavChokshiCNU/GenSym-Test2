/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      DbCursorObjectImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Thu Jun 18 17:47:31 EEST 2009
 *
 */


package com.gensym.classes.modules.g2database;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.jgi.*;

public class DbCursorObjectImpl extends com.gensym.classes.modules.g2database.DbConfigObjectImpl implements DbCursorObject {


  static final long serialVersionUID = 2L;
  private static final Symbol DB_CURSOR_POSITION_ = Symbol.intern ("DB-CURSOR-POSITION");

  /* Generated constructors */

  public DbCursorObjectImpl() {
    super();
  }

  public DbCursorObjectImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public DbCursorObjectImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- DB-CURSOR-POSITION
   * @param dbCursorPosition new value to conclude for DB-CURSOR-POSITION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDbCursorPosition(int dbCursorPosition) throws G2AccessException {
    setAttributeValue (DB_CURSOR_POSITION_, dbCursorPosition);
  }

  /**
   * Generated Property Getter for attribute -- DB-CURSOR-POSITION
   * @return the value of the DB-CURSOR-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getDbCursorPosition() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (DB_CURSOR_POSITION_);
    return ((Integer)retnValue).intValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
