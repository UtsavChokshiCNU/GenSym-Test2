/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2HtmlViewImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:44:53 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class G2HtmlViewImpl extends com.gensym.classes.G2NativeViewImpl implements G2HtmlView {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public G2HtmlViewImpl() {
    super();
  }

  public G2HtmlViewImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2HtmlViewImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- URL-OF-VIEW
   * @param urlOfView new value to conclude for URL-OF-VIEW
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUrlOfView(java.lang.String urlOfView) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.URL_OF_VIEW_, urlOfView);
  }

  /**
   * Generated Property Getter for attribute -- URL-OF-VIEW
   * @return the value of the URL-OF-VIEW attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getUrlOfView() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.URL_OF_VIEW_);
    return (java.lang.String)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
