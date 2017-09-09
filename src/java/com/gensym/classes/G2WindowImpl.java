/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2WindowImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:47:40 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class G2WindowImpl extends com.gensym.classes.G2ExtensionImpl implements G2Window {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public G2WindowImpl() {
    super();
  }

  public G2WindowImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2WindowImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- G2-USER-MODE
   * @param g2UserMode new value to conclude for G2-USER-MODE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setG2UserMode(com.gensym.util.Symbol g2UserMode) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.G2_USER_MODE_, g2UserMode);
  }

  /**
   * Generated Property Getter for attribute -- G2-USER-MODE
   * @return the value of the G2-USER-MODE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getG2UserMode() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_USER_MODE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- G2-WINDOW-SPECIFIC-LANGUAGE
   * @param g2WindowSpecificLanguage new value to conclude for G2-WINDOW-SPECIFIC-LANGUAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setG2WindowSpecificLanguage(com.gensym.util.Symbol g2WindowSpecificLanguage) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.G2_WINDOW_SPECIFIC_LANGUAGE_, g2WindowSpecificLanguage);
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-SPECIFIC-LANGUAGE
   * @return the value of the G2-WINDOW-SPECIFIC-LANGUAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getG2WindowSpecificLanguage() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_SPECIFIC_LANGUAGE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-MANAGEMENT-TYPE
   * @return the value of the G2-WINDOW-MANAGEMENT-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getG2WindowManagementType() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_MANAGEMENT_TYPE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-X
   * @return the value of the G2-WINDOW-X attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getG2WindowX() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_X_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-Y
   * @return the value of the G2-WINDOW-Y attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getG2WindowY() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_Y_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-WIDTH
   * @return the value of the G2-WINDOW-WIDTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getG2WindowWidth() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_WIDTH_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-HEIGHT
   * @return the value of the G2-WINDOW-HEIGHT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getG2WindowHeight() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_HEIGHT_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-X-RESOLUTION
   * @return the value of the G2-WINDOW-X-RESOLUTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getG2WindowXResolution() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_X_RESOLUTION_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-Y-RESOLUTION
   * @return the value of the G2-WINDOW-Y-RESOLUTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getG2WindowYResolution() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_Y_RESOLUTION_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-REMOTE-HOST-NAME
   * @return the value of the G2-WINDOW-REMOTE-HOST-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getG2WindowRemoteHostName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_REMOTE_HOST_NAME_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-USER-NAME-IN-OPERATING-SYSTEM
   * @return the value of the G2-WINDOW-USER-NAME-IN-OPERATING-SYSTEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getG2WindowUserNameInOperatingSystem() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_USER_NAME_IN_OPERATING_SYSTEM_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-TIME-OF-LAST-CONNECTION
   * @return the value of the G2-WINDOW-TIME-OF-LAST-CONNECTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getG2WindowTimeOfLastConnection() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_TIME_OF_LAST_CONNECTION_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-INITIAL-WINDOW-CONFIGURATION-STRING
   * @return the value of the G2-WINDOW-INITIAL-WINDOW-CONFIGURATION-STRING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getG2WindowInitialWindowConfigurationString() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_INITIAL_WINDOW_CONFIGURATION_STRING_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-REROUTE-PROBLEM-REPORT
   * @return the value of the G2-WINDOW-REROUTE-PROBLEM-REPORT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getG2WindowRerouteProblemReport() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_REROUTE_PROBLEM_REPORT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-OPERATING-SYSTEM-TYPE
   * @return the value of the G2-WINDOW-OPERATING-SYSTEM-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getG2WindowOperatingSystemType() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_OPERATING_SYSTEM_TYPE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SHOW-OPERATOR-LOGBOOK-IN-THIS-WINDOW?
   * @param showOperatorLogbookInThisWindow new value to conclude for SHOW-OPERATOR-LOGBOOK-IN-THIS-WINDOW?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setShowOperatorLogbookInThisWindow(boolean showOperatorLogbookInThisWindow) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SHOW_OPERATOR_LOGBOOK_IN_THIS_WINDOWQ_, new Boolean (showOperatorLogbookInThisWindow));
  }

  /**
   * Generated Property Getter for attribute -- SHOW-OPERATOR-LOGBOOK-IN-THIS-WINDOW?
   * @return the value of the SHOW-OPERATOR-LOGBOOK-IN-THIS-WINDOW? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getShowOperatorLogbookInThisWindow() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SHOW_OPERATOR_LOGBOOK_IN_THIS_WINDOWQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-USER-IS-VALID
   * @return the value of the G2-WINDOW-USER-IS-VALID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getG2WindowUserIsValid() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_USER_IS_VALID_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-MODE-IS-VALID
   * @return the value of the G2-WINDOW-MODE-IS-VALID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getG2WindowModeIsValid() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_MODE_IS_VALID_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- MOUSE-CURSOR
   * @param mouseCursor new value to conclude for MOUSE-CURSOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMouseCursor(com.gensym.util.Symbol mouseCursor) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MOUSE_CURSOR_, mouseCursor);
  }

  /**
   * Generated Property Getter for attribute -- MOUSE-CURSOR
   * @return the value of the MOUSE-CURSOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getMouseCursor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MOUSE_CURSOR_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-IS-EMBEDDED
   * @return the value of the G2-WINDOW-IS-EMBEDDED attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getG2WindowIsEmbedded() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_IS_EMBEDDED_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- WINDOW-HANDLES
   * @return the value of the WINDOW-HANDLES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getWindowHandles() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.WINDOW_HANDLES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SELECTED-WINDOW-HANDLE
   * @param selectedWindowHandle new value to conclude for SELECTED-WINDOW-HANDLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSelectedWindowHandle(java.lang.Integer selectedWindowHandle) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SELECTED_WINDOW_HANDLE_, selectedWindowHandle);
  }

  /**
   * Generated Property Getter for attribute -- SELECTED-WINDOW-HANDLE
   * @return the value of the SELECTED-WINDOW-HANDLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Integer getSelectedWindowHandle() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SELECTED_WINDOW_HANDLE_);
    return (java.lang.Integer)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-CLIENT-VERSION
   * @return the value of the G2-WINDOW-CLIENT-VERSION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getG2WindowClientVersion() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_CLIENT_VERSION_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-UI-STYLE
   * @return the value of the G2-WINDOW-UI-STYLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getG2WindowUiStyle() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_WINDOW_UI_STYLE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SELECTED-ITEMS
   * @param selectedItems new value to conclude for SELECTED-ITEMS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSelectedItems(com.gensym.util.Sequence selectedItems) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SELECTED_ITEMS_, selectedItems);
  }

  /**
   * Generated Property Getter for attribute -- SELECTED-ITEMS
   * @return the value of the SELECTED-ITEMS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getSelectedItems() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SELECTED_ITEMS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SELECTED-WORKSPACE
   * @param selectedWorkspace new value to conclude for SELECTED-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSelectedWorkspace(java.lang.Object selectedWorkspace) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SELECTED_WORKSPACE_, selectedWorkspace);
  }

  /**
   * Generated Property Getter for attribute -- SELECTED-WORKSPACE
   * @return the value of the SELECTED-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getSelectedWorkspace() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SELECTED_WORKSPACE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- USES-FLOATING-LICENSE
   * @return the value of the USES-FLOATING-LICENSE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Boolean getUsesFloatingLicense() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.USES_FLOATING_LICENSE_);
    return (java.lang.Boolean)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-MODE-IS-VALID
   * @return the value of the UI-CLIENT-MODE-IS-VALID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Boolean getUiClientModeIsValid() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_MODE_IS_VALID_);
    return (java.lang.Boolean)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-USER-IS-VALID
   * @return the value of the UI-CLIENT-USER-IS-VALID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Boolean getUiClientUserIsValid() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_USER_IS_VALID_);
    return (java.lang.Boolean)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-CONNECTION-STATUS
   * @return the value of the UI-CLIENT-CONNECTION-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUiClientConnectionStatus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_CONNECTION_STATUS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SPECIFIC-LANGUAGE
   * @return the value of the UI-CLIENT-SPECIFIC-LANGUAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUiClientSpecificLanguage() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_SPECIFIC_LANGUAGE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-USER-NAME-IN-OPERATING-SYSTEM
   * @return the value of the UI-CLIENT-USER-NAME-IN-OPERATING-SYSTEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getUiClientUserNameInOperatingSystem() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_USER_NAME_IN_OPERATING_SYSTEM_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-TIME-OF-LAST-CONNECTION
   * @return the value of the UI-CLIENT-TIME-OF-LAST-CONNECTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getUiClientTimeOfLastConnection() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_TIME_OF_LAST_CONNECTION_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-OPERATING-SYSTEM-TYPE
   * @return the value of the UI-CLIENT-OPERATING-SYSTEM-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUiClientOperatingSystemType() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_OPERATING_SYSTEM_TYPE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-REMOTE-HOST-NAME
   * @return the value of the UI-CLIENT-REMOTE-HOST-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getUiClientRemoteHostName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_REMOTE_HOST_NAME_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-USER-NAME
   * @return the value of the UI-CLIENT-USER-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUiClientUserName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_USER_NAME_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UI-CLIENT-USER-MODE
   * @param uiClientUserMode new value to conclude for UI-CLIENT-USER-MODE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUiClientUserMode(com.gensym.util.Symbol uiClientUserMode) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.UI_CLIENT_USER_MODE_, uiClientUserMode);
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-USER-MODE
   * @return the value of the UI-CLIENT-USER-MODE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUiClientUserMode() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_USER_MODE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
