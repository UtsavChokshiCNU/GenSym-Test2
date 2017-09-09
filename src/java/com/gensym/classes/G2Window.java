/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2Window.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:47:33 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface G2Window extends com.gensym.classes.G2Extension, com.gensym.classes.UiClientItem {

  public static final Symbol G2_WINDOW_ = com.gensym.util.symbol.G2ClassSymbols.G2_WINDOW_;
  static final Symbol g2ClassName = G2_WINDOW_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2_WINDOW_, G2_EXTENSION_, OBJECT_, UI_CLIENT_ITEM_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- G2-USER-MODE
   * @return the value of the G2-USER-MODE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-USER-MODE is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getG2UserMode() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- G2-USER-MODE
   * @param g2UserMode new value to conclude for G2-USER-MODE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setG2UserMode(com.gensym.util.Symbol g2UserMode) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-SPECIFIC-LANGUAGE
   * @return the value of the G2-WINDOW-SPECIFIC-LANGUAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-SPECIFIC-LANGUAGE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getG2WindowSpecificLanguage() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- G2-WINDOW-SPECIFIC-LANGUAGE
   * @param g2WindowSpecificLanguage new value to conclude for G2-WINDOW-SPECIFIC-LANGUAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setG2WindowSpecificLanguage(com.gensym.util.Symbol g2WindowSpecificLanguage) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-MANAGEMENT-TYPE
   * @return the value of the G2-WINDOW-MANAGEMENT-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-MANAGEMENT-TYPE is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text)
   *
   */
  public java.lang.Object getG2WindowManagementType() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-X
   * @return the value of the G2-WINDOW-X attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-X is : 
   * Integer
   *
   */
  public int getG2WindowX() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-Y
   * @return the value of the G2-WINDOW-Y attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-Y is : 
   * Integer
   *
   */
  public int getG2WindowY() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-WIDTH
   * @return the value of the G2-WINDOW-WIDTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-WIDTH is : 
   * Integer
   *
   */
  public int getG2WindowWidth() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-HEIGHT
   * @return the value of the G2-WINDOW-HEIGHT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-HEIGHT is : 
   * Integer
   *
   */
  public int getG2WindowHeight() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-X-RESOLUTION
   * @return the value of the G2-WINDOW-X-RESOLUTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-X-RESOLUTION is : 
   * Integer
   *
   */
  public int getG2WindowXResolution() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-Y-RESOLUTION
   * @return the value of the G2-WINDOW-Y-RESOLUTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-Y-RESOLUTION is : 
   * Integer
   *
   */
  public int getG2WindowYResolution() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-REMOTE-HOST-NAME
   * @return the value of the G2-WINDOW-REMOTE-HOST-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-REMOTE-HOST-NAME is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text)
   *
   */
  public java.lang.Object getG2WindowRemoteHostName() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-USER-NAME-IN-OPERATING-SYSTEM
   * @return the value of the G2-WINDOW-USER-NAME-IN-OPERATING-SYSTEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-USER-NAME-IN-OPERATING-SYSTEM is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text)
   *
   */
  public java.lang.Object getG2WindowUserNameInOperatingSystem() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-TIME-OF-LAST-CONNECTION
   * @return the value of the G2-WINDOW-TIME-OF-LAST-CONNECTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-TIME-OF-LAST-CONNECTION is : 
   * (OR NoItem
      (Structure 
        SECOND Quantity
        MINUTE Quantity
        HOUR Quantity
        DATE Quantity
        MONTH Quantity
        YEAR Quantity))
   *
   */
  public com.gensym.util.Structure getG2WindowTimeOfLastConnection() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-INITIAL-WINDOW-CONFIGURATION-STRING
   * @return the value of the G2-WINDOW-INITIAL-WINDOW-CONFIGURATION-STRING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-INITIAL-WINDOW-CONFIGURATION-STRING is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text)
   *
   */
  public java.lang.Object getG2WindowInitialWindowConfigurationString() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-REROUTE-PROBLEM-REPORT
   * @return the value of the G2-WINDOW-REROUTE-PROBLEM-REPORT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-REROUTE-PROBLEM-REPORT is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text)
   *
   */
  public java.lang.Object getG2WindowRerouteProblemReport() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-OPERATING-SYSTEM-TYPE
   * @return the value of the G2-WINDOW-OPERATING-SYSTEM-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-OPERATING-SYSTEM-TYPE is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text)
   *
   */
  public java.lang.Object getG2WindowOperatingSystemType() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SHOW-OPERATOR-LOGBOOK-IN-THIS-WINDOW?
   * @return the value of the SHOW-OPERATOR-LOGBOOK-IN-THIS-WINDOW? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SHOW-OPERATOR-LOGBOOK-IN-THIS-WINDOW? is : 
   * BooleanTruthValue
   *
   */
  public boolean getShowOperatorLogbookInThisWindow() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SHOW-OPERATOR-LOGBOOK-IN-THIS-WINDOW?
   * @param showOperatorLogbookInThisWindow new value to conclude for SHOW-OPERATOR-LOGBOOK-IN-THIS-WINDOW?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setShowOperatorLogbookInThisWindow(boolean showOperatorLogbookInThisWindow) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-USER-IS-VALID
   * @return the value of the G2-WINDOW-USER-IS-VALID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-USER-IS-VALID is : 
   * BooleanTruthValue
   *
   */
  public boolean getG2WindowUserIsValid() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-MODE-IS-VALID
   * @return the value of the G2-WINDOW-MODE-IS-VALID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-MODE-IS-VALID is : 
   * BooleanTruthValue
   *
   */
  public boolean getG2WindowModeIsValid() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MOUSE-CURSOR
   * @return the value of the MOUSE-CURSOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MOUSE-CURSOR is : 
   * (MEMBER DEFAULT ARROW CROSS HAND HELP I-BEAM CIRCLE-SLASH SIZE-ALL SIZE-NE-SW SIZE-NS SIZE-NW-SE 
          SIZE-WE UP-ARROW WAIT)
   *
   */
  public com.gensym.util.Symbol getMouseCursor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MOUSE-CURSOR
   * @param mouseCursor new value to conclude for MOUSE-CURSOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMouseCursor(com.gensym.util.Symbol mouseCursor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-IS-EMBEDDED
   * @return the value of the G2-WINDOW-IS-EMBEDDED attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-IS-EMBEDDED is : 
   * BooleanTruthValue
   *
   */
  public boolean getG2WindowIsEmbedded() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- WINDOW-HANDLES
   * @return the value of the WINDOW-HANDLES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for WINDOW-HANDLES is : 
   * (OR NoItem
      (Sequence Integer))
   *
   */
  public com.gensym.util.Sequence getWindowHandles() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SELECTED-WINDOW-HANDLE
   * @return the value of the SELECTED-WINDOW-HANDLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SELECTED-WINDOW-HANDLE is : 
   * (OR NoItem
      Integer)
   *
   */
  public java.lang.Integer getSelectedWindowHandle() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SELECTED-WINDOW-HANDLE
   * @param selectedWindowHandle new value to conclude for SELECTED-WINDOW-HANDLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSelectedWindowHandle(java.lang.Integer selectedWindowHandle) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-CLIENT-VERSION
   * @return the value of the G2-WINDOW-CLIENT-VERSION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-CLIENT-VERSION is : 
   * (Structure)
   *
   */
  public com.gensym.util.Structure getG2WindowClientVersion() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-UI-STYLE
   * @return the value of the G2-WINDOW-UI-STYLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-UI-STYLE is : 
   * (OR NoItem
      (MEMBER CLASSIC STANDARD MULTIWINDOW))
   *
   */
  public com.gensym.util.Symbol getG2WindowUiStyle() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SELECTED-ITEMS
   * @return the value of the SELECTED-ITEMS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SELECTED-ITEMS is : 
   * (OR NoItem
      (Sequence 
        (OR (Class ITEM)
            (Structure 
              TABLE
                (OR (Class TABLE-ITEM)
                    (Class READOUT-TABLE))
              ROW Integer
              COLUMN Integer)))))
   *
   */
  public com.gensym.util.Sequence getSelectedItems() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SELECTED-ITEMS
   * @param selectedItems new value to conclude for SELECTED-ITEMS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSelectedItems(com.gensym.util.Sequence selectedItems) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SELECTED-WORKSPACE
   * @return the value of the SELECTED-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SELECTED-WORKSPACE is : 
   * (OR NoItem
      (Class KB-WORKSPACE)
      (Sequence (Class KB-WORKSPACE) 1 2))
   *
   */
  public java.lang.Object getSelectedWorkspace() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SELECTED-WORKSPACE
   * @param selectedWorkspace new value to conclude for SELECTED-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSelectedWorkspace(java.lang.Object selectedWorkspace) throws G2AccessException;

}
