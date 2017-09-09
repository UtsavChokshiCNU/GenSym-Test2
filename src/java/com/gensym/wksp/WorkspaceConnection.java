package com.gensym.wksp;

import com.gensym.util.Symbol;
import com.gensym.util.WorkspaceEvent;
import com.gensym.util.symbol.SystemAttributeSymbols;

/**
 * A <code>WorkspaceElement</code> intended for use with items of class <code>Connection</code>.
 */
public interface WorkspaceConnection extends WorkspaceElement {

  /**
   * An attribute value received in the <code>itemModified</code> method for this class, for the
   * attribute named by CONNNECTION_STYLE_.
   */
  public static final Symbol DIAGONAL_ = Symbol.intern ("DIAGONAL");
  /**
   * An attribute value received in the <code>itemModified</code> method for this class, for the
   * attribute named by CONNNECTION_STYLE_.
   */
  public static final Symbol ORTHOGONAL_ = Symbol.intern ("ORTHOGONAL");
  
  /**
   * An attribute name received in the <code>handleConnectionStyleChanged</code> method for this class.
   */  
  public static final Symbol CONNECTION_STYLE_ = SystemAttributeSymbols.CONNECTION_STYLE_;

  /**
   * An attribute name received in the <code>handleConnectionIsDirectedChanged</code> method for this class.
   */
  public static final Symbol CONNECTION_IS_DIRECTED_ = SystemAttributeSymbols.CONNECTION_IS_DIRECTED_;
  
  /**
   * An attribute name received in the <code>handleWorkspaceItemMoved</code> method for this class.
   * @see #handleWorkspaceItemMoved
   */
  static final Symbol TW_WORKSPACE_ITEM_POSITION_
  = Symbol.intern("TW-WORKSPACE-ITEM-POSITION");
  
  /**
   * Invoked when the connections's position has changed.
   * @param <code>event</code> a <code>WorkspaceEvent</code> with ID of
   * <code>ITEM_MOVE</code>.<p>
   * The event's info will contain a structure whose attribute named by
   * <code>TW_WORKSPACE_ITEM_POSITION_</code> will contain a sequence of connection
   * vertices.
   */
  @Override
  public void handleWorkspaceItemMoved(WorkspaceEvent event);

  /**
   * Determines whether this element's <code>Connection</code> is a stub.
   * @return true iff the <code>Connection</code> for this <code>WorkspaceConnection</code>
   * is a stub.
   */
  public boolean isLooseEnd();
  
  /**
   * Determines whether the point given by (x, y) is "near"
   * the end of a stub of this connection.  This element's connection must
   * be stub for this to be true.
   * @return true if the the point (x,y) is near the end of a stub of this connection.
   */
  public boolean insideLooseEnd(int x, int y);


  /**
   * Invoked when the connection's style has changed.
   * @param <code>event</code> a <code>WorkspaceEvent</code> with ID of <code>ITEM_CHANGE</code>.<p>
   * The event's info will contain a structure whose attribute named by
   * <code>WorkspaceElement.ATTRIBUTE_NAME_</code> will be <code>CONNECTION_STYLE_</code> and whose
   * attribute named by <code>WorkspaceElement.NEW_VALUE_</code> will be either
   * <code>ORTHOGONAL_</code>, <code>DIAGONAL_</code>, or <code>null</code>.
   */
  public void handleConnectionStyleChanged(WorkspaceEvent event);

  /**
   * Invoked when the connection become directed or is no longer directed.
   * @param <code>event</code> a <code>WorkspaceEvent</code> with ID of <code>ITEM_CHANGE</code>.<p>
   * The event's info will contain a structure whose attribute named by
   * <code>WorkspaceElement.ATTRIBUTE_NAME_</code> will be <code>CONNECTION_IS_DIRECTED_</code> and whose
   * attribute named by <code>WorkspaceElement.NEW_VALUE_</code> will be a
   * a boolean indicating whether or not the connection is directed or not.
   */
  public void handleConnectionIsDirectedChanged(WorkspaceEvent event);
}


