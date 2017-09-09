package com.gensym.wksp;

import com.gensym.util.WorkspaceEvent;
import com.gensym.util.Symbol;

/**
 * A <code>WorkspaceElement</code> intended for use with items of class <code>Entity</code>.
 * Items of this class use a rendering of the class's icon description
 * as its visual appearance.  In addition to being resizable, these
 * renderings may be rotated and may have the values of icon description
 * variables change on an instance basis.
 */
public interface WorkspaceIcon extends WorkspaceElement {

  /**
   * An attribute name received in the <code>handleWorkspaceItemRotated</code> method for this class.
   * @see #handleWorkspaceItemRotated
   */
  static final Symbol NEW_ROTATION_ = Symbol.intern("NEW-ROTATION");

  /**
   * Invoked when the item's position has changed.
   * @param <code>event</code> a <code>WorkspaceEvent</code> with ID of
   * <code>ITEM_ROTATE</code>.<p>
   * The event's info will contain a structure whose attribute named by
   * <code>NEW_ROTATION_</code> will contain a Symbol naming the new rotation for this
   * element.
   */
  public void handleWorkspaceItemRotated(WorkspaceEvent event);
  
  /**
   * Invoked when the item's position has changed.
   * @param <code>event</code> a <code>WorkspaceEvent</code> with ID of
   * <code>ITEM_ICON_VARIABLES_CHANGE</code>.<p>
   * The event's info holds a structure containing the current variable names
   * and their corresponding values.
   */
  public void handleWorkspaceItemIconVariablesChanged(WorkspaceEvent event);
  
}


