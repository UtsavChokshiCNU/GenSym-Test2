/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      DrawingParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:40:41 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class DrawingParametersImpl extends com.gensym.classes.SystemTableImpl implements DrawingParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public DrawingParametersImpl() {
    super();
  }

  public DrawingParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public DrawingParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- ALLOW-SCHEDULED-DRAWING?
   * @param allowScheduledDrawing new value to conclude for ALLOW-SCHEDULED-DRAWING?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAllowScheduledDrawing(boolean allowScheduledDrawing) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ALLOW_SCHEDULED_DRAWINGQ_, new Boolean (allowScheduledDrawing));
  }

  /**
   * Generated Property Getter for attribute -- ALLOW-SCHEDULED-DRAWING?
   * @return the value of the ALLOW-SCHEDULED-DRAWING? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getAllowScheduledDrawing() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ALLOW_SCHEDULED_DRAWINGQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- PAINT-MODE?
   * @param paintMode new value to conclude for PAINT-MODE?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPaintMode(boolean paintMode) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PAINT_MODEQ_, new Boolean (paintMode));
  }

  /**
   * Generated Property Getter for attribute -- PAINT-MODE?
   * @return the value of the PAINT-MODE? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getPaintMode() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PAINT_MODEQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- IMAGE-PALETTE
   * @param imagePalette new value to conclude for IMAGE-PALETTE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setImagePalette(java.lang.Object imagePalette) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.IMAGE_PALETTE_, imagePalette);
  }

  /**
   * Generated Property Getter for attribute -- IMAGE-PALETTE
   * @return the value of the IMAGE-PALETTE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getImagePalette() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.IMAGE_PALETTE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SHOW-SELECTION-HANDLES
   * @param showSelectionHandles new value to conclude for SHOW-SELECTION-HANDLES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setShowSelectionHandles(boolean showSelectionHandles) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SHOW_SELECTION_HANDLES_, new Boolean (showSelectionHandles));
  }

  /**
   * Generated Property Getter for attribute -- SHOW-SELECTION-HANDLES
   * @return the value of the SHOW-SELECTION-HANDLES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getShowSelectionHandles() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SHOW_SELECTION_HANDLES_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- PRIMARY-SELECTION-COLOR
   * @param primarySelectionColor new value to conclude for PRIMARY-SELECTION-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPrimarySelectionColor(com.gensym.util.Symbol primarySelectionColor) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PRIMARY_SELECTION_COLOR_, primarySelectionColor);
  }

  /**
   * Generated Property Getter for attribute -- PRIMARY-SELECTION-COLOR
   * @return the value of the PRIMARY-SELECTION-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getPrimarySelectionColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PRIMARY_SELECTION_COLOR_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SECONDARY-SELECTION-COLOR
   * @param secondarySelectionColor new value to conclude for SECONDARY-SELECTION-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSecondarySelectionColor(com.gensym.util.Symbol secondarySelectionColor) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SECONDARY_SELECTION_COLOR_, secondarySelectionColor);
  }

  /**
   * Generated Property Getter for attribute -- SECONDARY-SELECTION-COLOR
   * @return the value of the SECONDARY-SELECTION-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getSecondarySelectionColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SECONDARY_SELECTION_COLOR_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ALIGNMENT-GRID
   * @param alignmentGrid new value to conclude for ALIGNMENT-GRID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAlignmentGrid(com.gensym.util.Structure alignmentGrid) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ALIGNMENT_GRID_, alignmentGrid);
  }

  /**
   * Generated Property Getter for attribute -- ALIGNMENT-GRID
   * @return the value of the ALIGNMENT-GRID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getAlignmentGrid() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ALIGNMENT_GRID_);
    return (com.gensym.util.Structure)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
