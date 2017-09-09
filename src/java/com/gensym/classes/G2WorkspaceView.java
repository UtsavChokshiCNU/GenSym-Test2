/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2WorkspaceView.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:47:51 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface G2WorkspaceView extends com.gensym.classes.G2NativeView {

  public static final Symbol G2_WORKSPACE_VIEW_ = com.gensym.util.symbol.G2ClassSymbols.G2_WORKSPACE_VIEW_;
  static final Symbol g2ClassName = G2_WORKSPACE_VIEW_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2_WORKSPACE_VIEW_, G2_NATIVE_VIEW_, G2_NATIVE_WINDOW_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- SCALE-OF-VIEW
   * @return the value of the SCALE-OF-VIEW attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SCALE-OF-VIEW is : 
   * (OR Float
      (Structure 
        X-SCALE Float
        Y-SCALE Float))
   *
   */
  public java.lang.Object getScaleOfView() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- WORKSPACE-OF-VIEW
   * @return the value of the WORKSPACE-OF-VIEW attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for WORKSPACE-OF-VIEW is : 
   * (OR NoItem
      (Class KB-WORKSPACE))
   *
   */
  public com.gensym.classes.KbWorkspace getWorkspaceOfView() throws G2AccessException;

}
