package com.gensym.wksp;


import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.util.*;
import com.gensym.message.*;
import java.awt.Rectangle;
import java.awt.PopupMenu;
import com.gensym.jgi.G2AccessException;

/**
 * The root interface used for elements placed into a <code>WorkspaceView</code>.
 * Objects implementing this interface handle the methods that are in
 * common to all items on a <code>KbWorkspace</code>, i.e. positional, size and color
 * changes.  A <code>WorkspaceElement</code> must also support methods required
 * by the <code>WorkspaceView</code> for selection and dragging.  <code>WorkspaceElement</code>
 * implementations must implement the <code>ItemListener</code> interface, however
 * in order to receive <code>itemModified</code> notifications, implementations
 * must add the <code>WorkspaceElement</code> as an <code>ItemListener</code> to the item.
 * The types of attributes that may be modified are specific to the class
 * of the item, and are documented in the sub-interfaces of <code>WorkspaceElement</code>.
 * @see com.gensym.util.ItemListener
 */

public interface WorkspaceElement extends com.gensym.util.ItemListener,
ItemView
{

  /**
   * An attribute name received in the <code>handleWorkspaceItemColorsChanged</code>
   * method for this class.
   * @see #handleWorkspaceItemColorsChanged
   */
  static final Symbol COLOR_PATTERN_CHANGES_
  = Symbol.intern("COLOR-PATTERN-CHANGES");
  
  /**
   * An attribute name received in the <code>itemModified</code> method for this class.
   */
  static final Symbol ATTRIBUTE_NAME_
  = Symbol.intern("ATTRIBUTE-NAME");
  
  /**
   * An attribute name received in the <code>itemModified</code> method for many of the
   * sub-interfaces of <code>WorkspaceElement</code>.
   */
  static final Symbol NAME_
  = Symbol.intern("NAME");
  
  /**
   * An attribute name received in the <code>itemModified</code> method for this class.
   */  
  static final Symbol NEW_VALUE_
  = Symbol.intern("NEW-VALUE");
  
  /**
   * Invoked when the item's position has changed.
   * @param <code>event</code> a <code>WorkspaceEvent</code> with ID of
   * <code>ITEM_MOVE</code>.<p>
   * The event's info will contain a <code>Structure</code> containing the
   * new left, top, right and bottom edges of the item.
   */
  public void handleWorkspaceItemMoved(WorkspaceEvent event);

  /**
   * Invoked when the item's size has changed
   * @param <code>event</code> a <code>WorkspaceEvent</code> with ID of
   * <code>ITEM_RESIZED</code>.<p>
   * The event's info will contain a <code>Structure</code> containing the new left,
   * top, right and bottom edges of the item.
   */
  public void handleWorkspaceItemResized(WorkspaceEvent event);

  /**
   * Invoked when the color of one or more of the item's regions has changed.
   * @param <code>event</code> a <code>WorkspaceEvent</code> with ID of
   * <code>WorkspaceEvent.ITEM_COLOR_PATTERN_CHANGE</code>.<p>
   * The event's info will contain a <code>Structure</code> whose attribute named by
   * <code>COLOR_PATTERN_CHANGES_</code> will contain a structure of changing regions
   * and symbols naming new G2 colors.
   */
  public void handleWorkspaceItemColorsChanged(WorkspaceEvent event);

  /**
   * This method is called by the handler to inform the
   * element that it is now "selected" so that it may choose
   * to render itself differently. It is *NOT* the main
   * entry point for selection.
   */
  public void select ();

  /**
   * This method is called by the handler to inform the
   * element that it is not "selected" so that it may choose
   * to render itself differently. It is *NOT* the main
   * entry point for selection.
   */
  public void unselect (); 

  /**
   * This method is called by the handler to check whether 
   * this element is now "selected".
   * @return true iff it is selected.
   */
  public boolean isSelected ();

  /**
   * Provides a ghost of this element that can be used for dragging purposes.
   * @return a <code>DraggingGhost</code> for this element using the given bounds.
   */
  public DraggingGhost getDraggingGhost (int left, int top, int width, int height);

       
  /**
   * Provides a ghost of this element that can be used for dragging purposes.
   * @return a <code>DraggingGhost</code> for this element using the element's bounds.
   */
  public DraggingGhost getDraggingGhost ();
  
  /**
   * Provides a ghost of this element that can be used for dragging purposes.
   * @return a <code>DraggingGhost</code> for this element extending from the marker given by
   * <code>markerLocn</code> to the point (<code>currentX</code>,<code>currentY</code>).
   */
  public DraggingGhost getDraggingGhost (int markerLocn, int currentX, int currentY);

  public PopupMenu getContextMenu ();

  /**
   * Indicates if this element is in the Cut buffer
   * @undocumented Not ready for public consumption
   */
  public boolean isCut ();

  /**
   * Set this element as being cut
   * @undocumented
   */
  public void setCut (boolean newCutState);

  /**
   * Should release any resources the WorkspaceElement may be holding,
   * and remove itself from any listener lists. Will be called
   * when the WorkspaceView that contains this is disposed.
   */
  public void dispose() throws G2AccessException;
}


