
package com.gensym.wksp;

import com.gensym.util.Symbol;

/**
 *    An interface of constant Symbols for each of  G2's basic types
 * of elements that can exist on a workspace.
 * @see #com.gensym.classes.Item#getRepresentationType()
 */
public interface WorkspaceRepresentationTypes {

  /**
   * Symbol representing one of G2's basic types of elements that
   * can exist on a worksapce.
   */
  public final Symbol
    TEXT_BOX_ = Symbol.intern("TEXT-BOX"),
    CONNECTION_ = Symbol.intern("CONNECTION"),
    ICON_WITH_CONNECTIONS = Symbol.intern("ICON-WITH-CONNECTIONS"),
    ICON_WITHOUT_CONNECTIONS = Symbol.intern("ICON-WITHOUT-CONNECTIONS"),
    ACTION_BUTTON_ = Symbol.intern("ACTION-BUTTON"),
    CHECK_BOX_ = Symbol.intern("CHECK-BOX"),
    RADIO_BUTTON_ = Symbol.intern("RADIO-BUTTON"),
    TYPE_IN_BOX_ = Symbol.intern("TYPE-IN-BOX"),
    SLIDER_ = Symbol.intern("SLIDER"),
    ATTRIBUTE_DISPLAY_ = Symbol.intern("ATTRIBUTE-DISPLAY"),
    ATTRIBUTE_TABLE_ = Symbol.intern("ATTRIBUTE-TABLE"),
    ATTRIBUTE_TABLE_WITH_HEADER_ = Symbol.intern("ATTRIBUTE-TABLE-WITH-HEADER"),
    DIAL_ = Symbol.intern("DIAL"),
    METER_ = Symbol.intern("METER"),
    CHART_ = Symbol.intern("CHART"),
    TREND_CHART_ = Symbol.intern("TREND-CHART"),
    LOOSE_END_ = Symbol.intern("LOOSE-END"),
    FREEFORM_TABLE_ = Symbol.intern("FREEFORM-TABLE");

}
