/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ImageDefinition.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:57:17 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import java.awt.Image;
import java.awt.Toolkit;
import com.gensym.jgi.G2AccessException;
import java.util.Vector;
import com.gensym.util.*;

public interface ImageDefinition extends com.gensym.classes.Item, com.gensym.classes.Entity {

  public static final Symbol IMAGE_DEFINITION_ = com.gensym.util.symbol.G2ClassSymbols.IMAGE_DEFINITION_;
  static final Symbol g2ClassName = IMAGE_DEFINITION_;
  static final Symbol[] classInheritancePath = new Symbol[] {IMAGE_DEFINITION_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /* Overriden Property - IMAGE */
  /**
   * @return an <code>java.awt.Image<code> of the image pointed to
   * by this <code>ImageDefinition<code>.
   * @exception G2AccessException if there are any communication problems
   */
  public Image getImage() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- AUTHORS
   * @return the value of the AUTHORS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for AUTHORS is : 
   * (OR NoItem
      (Structure 
        TIMESTAMP
          (Structure 
            YEAR Integer
            MONTH Integer
            DATE Integer
            HOURS Integer
            MINUTES Integer)
        AUTHORS
          (Sequence Symbol 0)))
   *
   */
  public com.gensym.util.Structure getAuthors() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- AUTHORS
   * @param authors new value to conclude for AUTHORS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAuthors(com.gensym.util.Structure authors) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CHANGE-LOG
   * @return the value of the CHANGE-LOG attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CHANGE-LOG is : 
   * (OR (Sequence)
      NoItem)
   *
   */
  public com.gensym.util.Sequence getChangeLog() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FILE-NAME-OF-IMAGE
   * @return the value of the FILE-NAME-OF-IMAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FILE-NAME-OF-IMAGE is : 
   * (OR NoItem
      Text)
   *
   */
  public java.lang.String getFileNameOfImage() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FILE-NAME-OF-IMAGE
   * @param fileNameOfImage new value to conclude for FILE-NAME-OF-IMAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFileNameOfImage(java.lang.String fileNameOfImage) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SAVE-IMAGE-DATA-WITH-KB
   * @return the value of the SAVE-IMAGE-DATA-WITH-KB attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SAVE-IMAGE-DATA-WITH-KB is : 
   * BooleanTruthValue
   *
   */
  public boolean getSaveImageDataWithKb() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SAVE-IMAGE-DATA-WITH-KB
   * @param saveImageDataWithKb new value to conclude for SAVE-IMAGE-DATA-WITH-KB
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSaveImageDataWithKb(boolean saveImageDataWithKb) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- WIDTH-OF-IMAGE
   * @return the value of the WIDTH-OF-IMAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for WIDTH-OF-IMAGE is : 
   * (OR NoItem
      Integer)
   *
   */
  public java.lang.Integer getWidthOfImage() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- HEIGHT-OF-IMAGE
   * @return the value of the HEIGHT-OF-IMAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for HEIGHT-OF-IMAGE is : 
   * (OR NoItem
      Integer)
   *
   */
  public java.lang.Integer getHeightOfImage() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DEPTH-OF-IMAGE
   * @return the value of the DEPTH-OF-IMAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DEPTH-OF-IMAGE is : 
   * (OR NoItem
      Integer)
   *
   */
  public java.lang.Integer getDepthOfImage() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CACHED-MEDIA-BIN
   * @return the value of the CACHED-MEDIA-BIN attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CACHED-MEDIA-BIN is : 
   * (OR (Class MEDIA-BIN)
      NoItem)
   *
   */
  public com.gensym.classes.MediaBin getCachedMediaBin() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- IMAGE-DATA
   * @return the value of the IMAGE-DATA attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for IMAGE-DATA is : 
   * (OR NoItem
      (Structure 
        PATHNAME Text
        NUMBER-OF-COLORS Integer
        COLOR-MAP
          (Sequence Integer)
        FORMAT Value
        WIDTH Integer
        HEIGHT Integer
        DEPTH Integer
        TRANSPARENT-COLOR-INDEX Value
        CONTENTS
          (OR Integer
              (Sequence Text))))
   *
   */
  public com.gensym.util.Structure getImageData() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- IMAGE-DATA
   * @param imageData new value to conclude for IMAGE-DATA
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setImageData(com.gensym.util.Structure imageData) throws G2AccessException;

  /* Overriden method - PROCESS-ITEM-EVENT */
  /**
   * @undocumented 
   */
  @Override
  public void processItemEvent (ItemEvent e);

}
