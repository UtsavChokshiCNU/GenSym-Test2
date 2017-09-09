package com.gensym.wksp;

import com.gensym.util.WorkspaceEvent;
import com.gensym.util.Symbol;

/**
 * A <code>WorkspaceButton</code> intended for use with buttons of class <code>RadioButton</code>.
 */
public interface WorkspaceRadioButton extends WorkspaceButton {

  /**
   * An attribute name received in the <code>handleButtonStatusChanged</code> method for this class.
   *@see #handleButtonStatusChanged
   */
  static final Symbol ON_ = Symbol.intern("ON");
  /**
   * An attribute name received in the <code>handleButtonStatusChanged</code> method for this class.
   *@see #handleButtonStatusChanged
   */
  static final Symbol OFF_ = Symbol.intern("OFF");
  /**
   * An attribute name received in the <code>handleButtonStatusChanged</code> method for this class.
   *@see #handleButtonStatusChanged
   */
  static final Symbol BUTTON_STATUS_ = Symbol.intern("BUTTON-STATUS");

  /**
   * Invoked when the radio button's status has changed.
   * @param <code>event</code> a <code>WorkspaceEvent</code> with ID of
   * <code>ITEM_CHANGE</code>.<p>
   * The event's info will contain a structure whose attribute named by
   * <code>WorkspaceElement.ATTRIBUTE_NAME_</code> will be
   * <code>BUTTON_STATUS_</code> and whose attribute named by
   * <code>WorkspaceElement.NEW_VALUE_</code> will be either
   * <code>ON_</code> or <code>OFF_</code>.
   */
  public void handleButtonStatusChanged(WorkspaceEvent event);
  
}
