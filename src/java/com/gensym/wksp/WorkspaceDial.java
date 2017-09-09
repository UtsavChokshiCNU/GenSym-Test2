package com.gensym.wksp;

import com.gensym.util.WorkspaceEvent;
import com.gensym.util.Symbol;

/**
 * A <code>WorkspaceElement</code> intended for use with items of class <code>Dial</code>.
 */ 
public interface WorkspaceDial extends WorkspaceElement {

  /**
   * An attribute name received in the <code>handleValueToDisplayChanged</code> method for this class.
   * @see #handleValueToDisplayChanged
   */
  static final Symbol VALUE_TO_DISPLAY_
  = Symbol.intern("VALUE-TO-DISPLAY");
  
  /**
   * An attribute name received in the <code>itemModified</code> method for this class.
   */
  public static final Symbol LOW_VALUE_FOR_DIAL_RULING_
  = Symbol.intern("LOW-VALUE-FOR-DIAL-RULING");
  
  /**
   * An attribute name received in the <code>itemModified</code> method for this class.
   */
  public static final Symbol INCREMENT_PER_DIAL_RULING_
  = Symbol.intern("INCREMENT-PER-DIAL-RULING");

  /**
   * Invoked when the dial's value to display has changed.
   * @param <code>event</code> a <code>WorkspaceEvent</code> with ID of
   * <code>ITEM_CHANGE</code>.<p>
   * The event's info will contain a structure whose attribute named by
   * <code>WorkspaceElement.ATTRIBUTE_NAME_</code> will be <code>VALUE_TO_DISPLAY_</code>
   * and whose attribute named by <code>WorkspaceElement.NEW_VALUE_</code> will contain
   * the dial's new value to display.
   */
  public void handleValueToDisplayChanged(WorkspaceEvent event);
  
}
