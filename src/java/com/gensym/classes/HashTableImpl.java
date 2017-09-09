/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      HashTableImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:57:14 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class HashTableImpl extends com.gensym.classes.ObjectImpl implements HashTable {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public HashTableImpl() {
    super();
  }

  public HashTableImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public HashTableImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Getter for attribute -- G2-HASH-TABLE-SEQUENCE
   * @return the value of the G2-HASH-TABLE-SEQUENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getG2HashTableSequence() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_HASH_TABLE_SEQUENCE_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- G2-HASH-TABLE-NUMBER-OF-ENTRIES
   * @return the value of the G2-HASH-TABLE-NUMBER-OF-ENTRIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getG2HashTableNumberOfEntries() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_HASH_TABLE_NUMBER_OF_ENTRIES_);
    return ((Integer)retnValue).intValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
