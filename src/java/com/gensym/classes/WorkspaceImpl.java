/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      WorkspaceImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:14:34 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class WorkspaceImpl extends com.gensym.classes.BlockImpl implements Workspace {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public WorkspaceImpl() {
    super();
  }

  public WorkspaceImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public WorkspaceImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- WORKSPACE-MARGIN
   * @param workspaceMargin new value to conclude for WORKSPACE-MARGIN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setWorkspaceMargin(int workspaceMargin) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.WORKSPACE_MARGIN_, workspaceMargin);
  }

  /**
   * Generated Property Getter for attribute -- WORKSPACE-MARGIN
   * @return the value of the WORKSPACE-MARGIN attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getWorkspaceMargin() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.WORKSPACE_MARGIN_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- BACKGROUND-IMAGES
   * @param backgroundImages new value to conclude for BACKGROUND-IMAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setBackgroundImages(com.gensym.util.Sequence backgroundImages) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.BACKGROUND_IMAGES_, backgroundImages);
  }

  /**
   * Generated Property Getter for attribute -- BACKGROUND-IMAGES
   * @return the value of the BACKGROUND-IMAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getBackgroundImages() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.BACKGROUND_IMAGES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- FRAME-STYLE
   * @param frameStyle new value to conclude for FRAME-STYLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setFrameStyle(com.gensym.util.Symbol frameStyle) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.FRAME_STYLE_, frameStyle);
  }

  /**
   * Generated Property Getter for attribute -- FRAME-STYLE
   * @return the value of the FRAME-STYLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getFrameStyle() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FRAME_STYLE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TITLE-BAR-TEXT
   * @param titleBarText new value to conclude for TITLE-BAR-TEXT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTitleBarText(java.lang.Object titleBarText) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TITLE_BAR_TEXT_, titleBarText);
  }

  /**
   * Generated Property Getter for attribute -- TITLE-BAR-TEXT
   * @return the value of the TITLE-BAR-TEXT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getTitleBarText() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TITLE_BAR_TEXT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- VIEW-PREFERENCES
   * @param viewPreferences new value to conclude for VIEW-PREFERENCES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setViewPreferences(com.gensym.util.Structure viewPreferences) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.VIEW_PREFERENCES_, viewPreferences);
  }

  /**
   * Generated Property Getter for attribute -- VIEW-PREFERENCES
   * @return the value of the VIEW-PREFERENCES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getViewPreferences() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.VIEW_PREFERENCES_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- PREFER-BUFFERED-DRAWING
   * @param preferBufferedDrawing new value to conclude for PREFER-BUFFERED-DRAWING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPreferBufferedDrawing(boolean preferBufferedDrawing) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PREFER_BUFFERED_DRAWING_, new Boolean (preferBufferedDrawing));
  }

  /**
   * Generated Property Getter for attribute -- PREFER-BUFFERED-DRAWING
   * @return the value of the PREFER-BUFFERED-DRAWING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getPreferBufferedDrawing() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PREFER_BUFFERED_DRAWING_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
