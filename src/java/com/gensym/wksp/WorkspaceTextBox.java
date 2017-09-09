package com.gensym.wksp;

import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.util.WorkspaceEvent;

/**
 * A <code>WorkspaceElement</code> intended for use with items of class <code>TextBox</code>.
 */
public interface WorkspaceTextBox extends WorkspaceElement {

  /**
   * An attribute name received in the <code>itemModified</code> method for this class.
   */
  public static final Symbol TEXT_ = SystemAttributeSymbols.TEXT_;

  /**
   * An attribute name received in the <code>itemModified</code> method for this class.
   */
  public static final Symbol TEXT_ALIGNMENT_ = SystemAttributeSymbols.TEXT_ALIGNMENT_;

  /**
   * An attribute name received in the <code>handleWorkspaceItemFontChanged</code>
   * method for this class.
   */
  public static final Symbol TEXT_X_MAGNIFICATION_ = SystemAttributeSymbols.TEXT_X_MAGNIFICATION_;

  /**
   * An attribute name received in the <code>handleWorkspaceItemFontChanged</code>
   * method for this class.
   */
  public static final Symbol TEXT_Y_MAGNIFICATION_ = SystemAttributeSymbols.TEXT_Y_MAGNIFICATION_;

  /**
   * An attribute name received in the <code>handleWorkspaceItemFontChanged</code>
   * method for this class.
   */
  public static final Symbol FORMAT_TYPE_ = SystemAttributeSymbols.FORMAT_TYPE_;
  /**
   * An attribute value received in the <code>itemModified</code> method for this class.
   */
  public static final Symbol LEFT_ = Symbol.intern ("LEFT");
  
  /**
   * An attribute value received in the <code>itemModified</code> method for this class.
   */  
  public static final Symbol CENTER_ = Symbol.intern ("CENTER");
  
  /**
   * An attribute value received in the <code>itemModified</code> method for this class.
   */  
  public static final Symbol RIGHT_ = Symbol.intern ("RIGHT");

  /**
   * Invoked when the item's font has changed.
   * @param <code>event</code> a <code>WorkspaceEvent</code> with ID of
   * <code>ITEM_CHANGE</code>.<p>
   * The event's info will contain a structure whose attribute named by
   * <code>WorkspaceElement.ATTRIBUTE_NAME_</code> will be either
   * <code>TEXT_X_MAGNIFICATION_</code>, <code>TEXT_Y_MAGNIFICATION_</code>
   * or <code>FORMAT_TYPE_</code>.  The attribute named by
   * <code>WorkspaceElement.NEW_VALUE_</code> will contain either the new
   * x-magnification, y-magnification or format type, respectively.
   */
  public void handleWorkspaceItemFontChanged(WorkspaceEvent e);
  
}


