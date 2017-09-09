/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdlPathItemEventManager.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon May 15 14:06:43 GMT+04:00 2000
 *
 */


package com.gensym.classes.modules.gdluisup;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface GdlPathItemEventManager extends com.gensym.classes.modules.g2evliss.G2EventListenerSupport {

  public static final Symbol GDL_PATH_ITEM_EVENT_MANAGER_ = Symbol.intern ("GDL-PATH-ITEM-EVENT-MANAGER");
  static final Symbol g2ClassName = GDL_PATH_ITEM_EVENT_MANAGER_;
  static final Symbol[] classInheritancePath = new Symbol[] {GDL_PATH_ITEM_EVENT_MANAGER_, G2_EVENT_LISTENER_SUPPORT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};

  static final Symbol ATTRIBUTE_DISPLAYS_ = Symbol.intern ("ATTRIBUTE-DISPLAYS");
  static final Symbol STUBS_ = Symbol.intern ("STUBS");
  static final Symbol DEFAULT_SETTINGS_ = Symbol.intern ("DEFAULT-SETTINGS");

  static final Symbol[] staticAttributes = new Symbol[] {ATTRIBUTE_DISPLAYS_, STUBS_, DEFAULT_SETTINGS_};


  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-DISPLAYS
   * @return the value of the ATTRIBUTE-DISPLAYS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ATTRIBUTE-DISPLAYS is : 
   * (OR NoItem
      (MEMBER INHERITED)
      (Sequence 
        (Structure 
          ATTRIBUTE-LIST
            (Sequence 
              (Structure 
                ATTRIBUTE Symbol
                QUALIFIED-CLASS Symbol
                DISPLAY-WITH-NAME BooleanTruthValue)
              1))
          POSITION
            (OR (MEMBER AT-STANDARD-POSITION)
                (Structure 
                  X-OFFSET Integer
                  Y-OFFSET Integer)))
        1)))
   *
   */
  public java.lang.Object getAttributeDisplaysForClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ATTRIBUTE-DISPLAYS
   * @param attributeDisplays new value to conclude for ATTRIBUTE-DISPLAYS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAttributeDisplaysForClass(java.lang.Object attributeDisplays) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- STUBS
   * @return the value of the STUBS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for STUBS is : 
   * (OR NoItem
      (MEMBER INHERITED)
      (Sequence 
        (Structure 
          PORTNAME Symbol
          CONNECTION-CLASS Symbol
          STUB-DIRECTION
            (MEMBER INPUT OUTPUT)
          EDGE-LOCATION
            (MEMBER TOP BOTTOM RIGHT LEFT)
          COORDINATE-LOCATION Integer
          STYLE
            (MEMBER DIAGONAL ORTHOGONAL))
        1)))
   *
   */
  public java.lang.Object getStubsForClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- STUBS
   * @param stubs new value to conclude for STUBS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setStubsForClass(java.lang.Object stubs) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DEFAULT-SETTINGS
   * @return the value of the DEFAULT-SETTINGS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Attribute DEFAULT-SETTINGS has no type
   *
   */
  public java.lang.Object getDefaultSettingsForClass() throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM-EVENT-MANAGER::GDL-UPDATE-DISPLAY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM-EVENT-MANAGER,arg1:CLASS GDL-PATH-ITEM) = ()
   */
  public  void gdlUpdateDisplay(com.gensym.classes.modules.gdl.GdlPathItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM-EVENT-MANAGER::ADD-GDL-PATH-ITEM-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM-EVENT-MANAGER,arg1:CLASS GDL-PATH-ITEM-EVENT-LISTENER) = ()
   */
  public  void addGdlPathItemEventListener(com.gensym.classes.modules.gdluisup.GdlPathItemEventListener arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM-EVENT-MANAGER::ADD-GDL-PATH-ITEM-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM-EVENT-MANAGER,arg1:CLASS GDL-PATH-ITEM-EVENT-LISTENER) = ()
   */
  public  void addG2_GdlPathItemEventListener(G2_GdlPathItemEventListener arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM-EVENT-MANAGER::REMOVE-GDL-PATH-ITEM-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM-EVENT-MANAGER,arg1:CLASS GDL-PATH-ITEM-EVENT-LISTENER) = ()
   */
  public  void removeGdlPathItemEventListener(com.gensym.classes.modules.gdluisup.GdlPathItemEventListener arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM-EVENT-MANAGER::REMOVE-GDL-PATH-ITEM-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM-EVENT-MANAGER,arg1:CLASS GDL-PATH-ITEM-EVENT-LISTENER) = ()
   */
  public  void removeG2_GdlPathItemEventListener(G2_GdlPathItemEventListener arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM-EVENT-MANAGER::GDL-HIDE-DISPLAY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM-EVENT-MANAGER,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlHideDisplay(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
}
