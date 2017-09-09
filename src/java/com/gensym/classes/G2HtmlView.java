/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2HtmlView.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:44:52 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface G2HtmlView extends com.gensym.classes.G2NativeView {

  public static final Symbol G2_HTML_VIEW_ = com.gensym.util.symbol.G2ClassSymbols.G2_HTML_VIEW_;
  static final Symbol g2ClassName = G2_HTML_VIEW_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2_HTML_VIEW_, G2_NATIVE_VIEW_, G2_NATIVE_WINDOW_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- URL-OF-VIEW
   * @return the value of the URL-OF-VIEW attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for URL-OF-VIEW is : 
   * (OR NoItem
      Text)
   *
   */
  public java.lang.String getUrlOfView() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- URL-OF-VIEW
   * @param urlOfView new value to conclude for URL-OF-VIEW
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUrlOfView(java.lang.String urlOfView) throws G2AccessException;

}
