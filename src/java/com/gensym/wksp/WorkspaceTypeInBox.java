package com.gensym.wksp;

import com.gensym.util.WorkspaceEvent;
import com.gensym.util.Symbol;

/**
 * A <code>WorkspaceButton</code> intended for use with buttons of class <code>TypeInBox</code>.
 */
public interface WorkspaceTypeInBox extends WorkspaceButton {

  /**
   * An attribute name received in the <code>handleTypeInBoxValueChange</code>
   * method for this class.    
   *@see #handleTypeInBoxValueChanged
   */
  static final Symbol TYPE_IN_BOX_VALUE_
  = Symbol.intern("TYPE-IN-BOX-VALUE");
  
  /**
   * An attribute name received in the <code>itemModified</code> method for this class.
   */
  public static final Symbol BLANK_FOR_TYPE_INQ_
  = Symbol.intern("BLANK-FOR-TYPE-IN?");

  /**
   * An attribute name received in the <code>itemModified</code> method for this class.
   */
  public static final Symbol FORMAT_FOR_TYPE_IN_BOX_
  = Symbol.intern("FORMAT-FOR-TYPE-IN-BOX");
  
  /**
   * An attribute name received in the <code>itemModified</code> method for this class.
   */
  public static final Symbol HAVE_EDIT_OPTION_BUTTON_FOR_TYPE_INQ_
  = Symbol.intern("HAVE-EDIT-OPTION-BUTTON-TYPE-IN?");//maybe

  /**
   * An attribute name received in the <code>itemModified</code> method for this class.
   */
  public static final Symbol TYPE_IN_BOX_VARIABLE_OR_PARAMETER_ 
  = Symbol.intern ("TYPE-IN-BOX-VARIABLE-OR-PARAMETER");
  /**
   * Invoked when the <code>TypeInBox</code>'s value has changed.
   * @param <code>event</code> a <code>WorkspaceEvent</code> with ID of
   * <code>ITEM_CHANGE</code>.<p>
   * The event's info will contain a structure whose attribute named by
   * <code>WorkspaceElement.ATTRIBUTE_NAME_</code> will be <code>TYPE_IN_BOX_VALUE_</code>
   * and whose attribute named by <code>WorkspaceElement.NEW_VALUE_</code> will contain the 
   * <code>TypeInBox</code>'s new value to display.
   */
  public void handleTypeInBoxValueChanged(WorkspaceEvent event);

  /**
   * Invoked when the <code>TypeInBox</code>'s variable or parameter has changed.
   * @param <code>event</code> a <code>WorkspaceEvent</code> with ID of
   * <code>ITEM_CHANGE</code>.<p>
   * The event's info will contain a structure whose attribute named by
   * <code>WorkspaceElement.ATTRIBUTE_NAME_</code> will be
   * <code>TYPE_IN_BOX_VARIABLE_OR_PARAMETER_</code>
   * and whose attribute named by <code>WorkspaceElement.NEW_VALUE_</code> will contain the 
   * <code>TypeInBox</code>'s current variable or parameter.
   */
  public void handleTypeInBoxVariableOrParameterChanged(WorkspaceEvent event);
}
