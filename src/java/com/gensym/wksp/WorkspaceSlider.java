package com.gensym.wksp;

import com.gensym.util.WorkspaceEvent;
import com.gensym.util.Symbol;

/**
 * A <code>WorkspaceButton</code> intended for use with buttons of class <code>Slider</code>.
 */
public interface WorkspaceSlider extends WorkspaceButton {

  /**
   * An attribute name received in the <code>handleSliderValueChanged</code> method for this class.
   *@see #handleSliderValueChanged
   */
  static final Symbol SLIDER_VALUE_ = Symbol.intern("SLIDER-VALUE");
  
  /**
   * An attribute name received in the <code>itemModified</code> method for this class.
   */
  public static final Symbol SET_VALUE_WHILE_SLIDINGQ_
  = Symbol.intern("SET-VALUE-WHILE-SLIDING?");

  /**
   * An attribute name received in the <code>itemModified</code> method for this class.
   */
  public static final Symbol WHEN_TO_SHOW_VALUE_
  = Symbol.intern("WHEN-TO-SHOW-VALUE");

  /**
   * An attribute name received in the <code>itemModified</code> method for this class,
   * which determines when to show the display value.
   */
  public static final Symbol ALWAYS_ = Symbol.intern ("ALWAYS");

  /**
   * An attribute name received in the <code>itemModified</code> method for this class,
   * which determines when to show the display value.
   */
  public static final Symbol NEVER_ = Symbol.intern ("NEVER");

  /**
   * An attribute name received in the <code>itemModified</code> method for this class,
   * which determines when to show the display value.
   */
  public static final Symbol ONLY_WHILE_SLIDING_ = Symbol.intern ("ONLY-WHILE-SLIDING");
  
  /**
   * An attribute name received in the <code>itemModified</code> method for this class.
   * @deprecated
   */
  public static final Symbol MIMIMUM_VALUE_
  = Symbol.intern("MINIMUM-VALUE");
  
  /**
   * An attribute name received in the <code>itemModified</code> method for this class.
   */  
  public static final Symbol MINIMUM_VALUE_
  = Symbol.intern("MINIMUM-VALUE");

  /**
   * An attribute name received in the <code>itemModified</code> method for this class.
   */
  public static final Symbol MAXIMUM_VALUE_
  = Symbol.intern("MAXIMUM-VALUE");
  
  /**
   * Invoked when the slider's value has changed.
   * @param <code>event</code> a <code>WorkspaceEvent</code> with ID of
   * <code>ITEM_CHANGE</code>.<p>
   * The event's info will contain a structure whose attribute named by
   * <code>WorkspaceElement.ATTRIBUTE_NAME_</code> will be
   * <code>SLIDER_VALUE_</code> and whose attribute named by
   * <code>WorkspaceElement.NEW_VALUE_</code> will contain the slider's
   * new value to display.
   */
  public void handleSliderValueChanged(WorkspaceEvent event);
  
}
