/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GqmLoggingManagerImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Tue Jun 13 11:45:58 EDT 2000
 *
 */


package com.gensym.classes.modules.gqm;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class GqmLoggingManagerImpl extends com.gensym.classes.modules.glf.GlfLoggingManagerImpl implements GqmLoggingManager {


  static final long serialVersionUID = 2L;
  private static final Symbol GQM_TIME_FORMAT_ = Symbol.intern ("GQM-TIME-FORMAT");
  private static final Symbol GQM_LOG_COMMENTS_ = Symbol.intern ("GQM-LOG-COMMENTS");

  /* Generated constructors */

  public GqmLoggingManagerImpl() {
    super();
  }

  public GqmLoggingManagerImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- GQM-TIME-FORMAT
   * @param gqmTimeFormat new value to conclude for GQM-TIME-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmTimeFormat(com.gensym.util.Symbol gqmTimeFormat) throws G2AccessException {
    setAttributeValue (GQM_TIME_FORMAT_, gqmTimeFormat);
  }

  /**
   * Generated Property Getter for attribute -- GQM-TIME-FORMAT
   * @return the value of the GQM-TIME-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getGqmTimeFormat() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GQM_TIME_FORMAT_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GQM-LOG-COMMENTS
   * @param gqmLogComments new value to conclude for GQM-LOG-COMMENTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmLogComments(boolean gqmLogComments) throws G2AccessException {
    setAttributeValue (GQM_LOG_COMMENTS_, new Boolean (gqmLogComments));
  }

  /**
   * Generated Property Getter for attribute -- GQM-LOG-COMMENTS
   * @return the value of the GQM-LOG-COMMENTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getGqmLogComments() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GQM_LOG_COMMENTS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
