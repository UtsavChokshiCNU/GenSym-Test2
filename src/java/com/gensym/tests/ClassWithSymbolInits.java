
package com.gensym.tests;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.jgi.*;

public class ClassWithSymbolInits {
  public static void main (String[] args) throws Exception {
    ClassLoader cl = new MCL ();
    Class c = cl.loadClass ("com.gensym.classes.SystemPredicate");
  }
}

class MCL extends ClassLoader {
  @Override
  protected Class loadClass (String className, boolean resolve) throws ClassNotFoundException {
    long t0 = System.currentTimeMillis ();
    Class c = super.findSystemClass (className);
    long t1 = System.currentTimeMillis ();
    System.out.println ("findSystemClass took " + (t1 - t0) + "ms");

    return c;
  }
}

class ClassWithSymbolInits0 {
  /*
  private static final Symbol AUTHORS_ = Symbol.intern ("AUTHORS");
  private static final Symbol CHANGE_LOG_ = Symbol.intern ("CHANGE-LOG");
  private static final Symbol TRACING_AND_BREAKPOINTS_ = Symbol.intern ("TRACING-AND-BREAKPOINTS");
  private static final Symbol CLASS_OF_PROCEDURE_INVOCATION_ = Symbol.intern ("CLASS-OF-PROCEDURE-INVOCATION");
  private static final Symbol DEFAULT_PROCEDURE_PRIORITY_ = Symbol.intern ("DEFAULT-PROCEDURE-PRIORITY");
  private static final Symbol UNINTERRUPTED_PROCEDURE_EXECUTION_LIMIT_ = Symbol.intern ("UNINTERRUPTED-PROCEDURE-EXECUTION-LIMIT");
  private static final Symbol TEXT_ = Symbol.intern ("TEXT");
  private static final Symbol EVALUATION_ATTRIBUTES_ = Symbol.intern ("EVALUATION-ATTRIBUTES");
  private static final Symbol TRANSIENT_ = Symbol.intern ("TRANSIENT");
  private static final Symbol PERMANENT_ = Symbol.intern ("PERMANENT");
  private static final Symbol REPRESENTATION_TYPE_ = Symbol.intern ("REPRESENTATION-TYPE");
  private static final Symbol ITEM_WIDTH_ = Symbol.intern ("ITEM-WIDTH");
  private static final Symbol ITEM_HEIGHT_ = Symbol.intern ("ITEM-HEIGHT");
  private static final Symbol ITEM_Y_POSITION_ = Symbol.intern ("ITEM-Y-POSITION");
  private static final Symbol ITEM_X_POSITION_ = Symbol.intern ("ITEM-X-POSITION");
  private static final Symbol ATTRIBUTE_DISPLAY_ITEMS_ = Symbol.intern ("ATTRIBUTE-DISPLAY-ITEMS");
  private static final Symbol NAME_BOX_ITEM_ = Symbol.intern ("NAME-BOX-ITEM");
  private static final Symbol ICON_VARIABLES_ = Symbol.intern ("ICON-VARIABLES");
  private static final Symbol CURRENT_ATTRIBUTE_DISPLAYS_ = Symbol.intern ("CURRENT-ATTRIBUTE-DISPLAYS");
  private static final Symbol ICON_COLOR_ = Symbol.intern ("ICON-COLOR");
  private static final Symbol ICON_REFLECTION_ = Symbol.intern ("ICON-REFLECTION");
  private static final Symbol ICON_HEADING_ = Symbol.intern ("ICON-HEADING");
  private static final Symbol ITEM_COLOR_PATTERN_ = Symbol.intern ("ITEM-COLOR-PATTERN");
  private static final Symbol NAME_BOX_ = Symbol.intern ("NAME-BOX");
  private static final Symbol STRIPE_COLOR_ = Symbol.intern ("STRIPE-COLOR");
  private static final Symbol BORDER_COLOR_ = Symbol.intern ("BORDER-COLOR");
  private static final Symbol TEXT_COLOR_ = Symbol.intern ("TEXT-COLOR");
  private static final Symbol FOREGROUND_COLOR_ = Symbol.intern ("FOREGROUND-COLOR");
  private static final Symbol BACKGROUND_COLOR_ = Symbol.intern ("BACKGROUND-COLOR");
  private static final Symbol NOTES_ = Symbol.intern ("NOTES");
  private static final Symbol USER_RESTRICTIONS_ = Symbol.intern ("USER-RESTRICTIONS");
  private static final Symbol ITEM_CONFIGURATION_ = Symbol.intern ("ITEM-CONFIGURATION");
  private static final Symbol NAMES_ = Symbol.intern ("NAMES");
  private static final Symbol LAYER_POSITION_ = Symbol.intern ("LAYER-POSITION");
  private static final Symbol RELATIONSHIPS_ = Symbol.intern ("RELATIONSHIPS");
  private static final Symbol ITEM_NOTES_ = Symbol.intern ("ITEM-NOTES");
  private static final Symbol CONTAINING_MODULE_ = Symbol.intern ("CONTAINING-MODULE");
  private static final Symbol ITEM_ACTIVE_ = Symbol.intern ("ITEM-ACTIVE");
  private static final Symbol ITEM_STATUS_ = Symbol.intern ("ITEM-STATUS");
  private static final Symbol FOUNDATION_CLASS_ = Symbol.intern ("FOUNDATION-CLASS");
  private static final Symbol CLASS_ = Symbol.intern ("CLASS");
  private static final Symbol ICON_DESCRIPTION_FOR_CLASS_ = Symbol.intern ("ICON-DESCRIPTION");
  private static final Symbol INSTANTIATE_FOR_CLASS_ = Symbol.intern ("INSTANTIATE");
  private static final Symbol INCLUDE_IN_MENUS_FOR_CLASS_ = Symbol.intern ("INCLUDE-IN-MENUS");
  private static final Symbol SYSTEM_MENU_CHOICES_FOR_CLASS_ = Symbol.intern ("SYSTEM-MENU-CHOICES");

  private static final Symbol AUTHORS1_ = Symbol.intern ("AUTHORS");
  private static final Symbol CHANGE_LOG1_ = Symbol.intern ("CHANGE-LOG");
  private static final Symbol TRACING_AND_BREAKPOINTS1_ = Symbol.intern ("TRACING-AND-BREAKPOINTS");
  private static final Symbol CLASS_OF_PROCEDURE_INVOCATION1_ = Symbol.intern ("CLASS-OF-PROCEDURE-INVOCATION");
  private static final Symbol DEFAULT_PROCEDURE_PRIORITY1_ = Symbol.intern ("DEFAULT-PROCEDURE-PRIORITY");
  private static final Symbol UNINTERRUPTED_PROCEDURE_EXECUTION_LIMIT1_ = Symbol.intern ("UNINTERRUPTED-PROCEDURE-EXECUTION-LIMIT");
  private static final Symbol TEXT1_ = Symbol.intern ("TEXT");
  private static final Symbol EVALUATION_ATTRIBUTES1_ = Symbol.intern ("EVALUATION-ATTRIBUTES");
  private static final Symbol TRANSIENT1_ = Symbol.intern ("TRANSIENT");
  private static final Symbol PERMANENT1_ = Symbol.intern ("PERMANENT");
  private static final Symbol REPRESENTATION_TYPE1_ = Symbol.intern ("REPRESENTATION-TYPE");
  private static final Symbol ITEM_WIDTH1_ = Symbol.intern ("ITEM-WIDTH");
  private static final Symbol ITEM_HEIGHT1_ = Symbol.intern ("ITEM-HEIGHT");
  private static final Symbol ITEM_Y_POSITION1_ = Symbol.intern ("ITEM-Y-POSITION");
  private static final Symbol ITEM_X_POSITION1_ = Symbol.intern ("ITEM-X-POSITION");
  private static final Symbol ATTRIBUTE_DISPLAY_ITEMS1_ = Symbol.intern ("ATTRIBUTE-DISPLAY-ITEMS");
  private static final Symbol NAME_BOX_ITEM1_ = Symbol.intern ("NAME-BOX-ITEM");
  private static final Symbol ICON_VARIABLES1_ = Symbol.intern ("ICON-VARIABLES");
  private static final Symbol CURRENT_ATTRIBUTE_DISPLAYS1_ = Symbol.intern ("CURRENT-ATTRIBUTE-DISPLAYS");
  private static final Symbol ICON_COLOR1_ = Symbol.intern ("ICON-COLOR");
  private static final Symbol ICON_REFLECTION1_ = Symbol.intern ("ICON-REFLECTION");
  private static final Symbol ICON_HEADING1_ = Symbol.intern ("ICON-HEADING");
  private static final Symbol ITEM_COLOR_PATTERN1_ = Symbol.intern ("ITEM-COLOR-PATTERN");
  private static final Symbol NAME_BOX1_ = Symbol.intern ("NAME-BOX");
  private static final Symbol STRIPE_COLOR1_ = Symbol.intern ("STRIPE-COLOR");
  private static final Symbol BORDER_COLOR1_ = Symbol.intern ("BORDER-COLOR");
  private static final Symbol TEXT_COLOR1_ = Symbol.intern ("TEXT-COLOR");
  private static final Symbol FOREGROUND_COLOR1_ = Symbol.intern ("FOREGROUND-COLOR");
  private static final Symbol BACKGROUND_COLOR1_ = Symbol.intern ("BACKGROUND-COLOR");
  private static final Symbol NOTES1_ = Symbol.intern ("NOTES");
  private static final Symbol USER_RESTRICTIONS1_ = Symbol.intern ("USER-RESTRICTIONS");
  private static final Symbol ITEM_CONFIGURATION1_ = Symbol.intern ("ITEM-CONFIGURATION");
  private static final Symbol NAMES1_ = Symbol.intern ("NAMES");
  private static final Symbol LAYER_POSITION1_ = Symbol.intern ("LAYER-POSITION");
  private static final Symbol RELATIONSHIPS1_ = Symbol.intern ("RELATIONSHIPS");
  private static final Symbol ITEM_NOTES1_ = Symbol.intern ("ITEM-NOTES");
  private static final Symbol CONTAINING_MODULE1_ = Symbol.intern ("CONTAINING-MODULE");
  private static final Symbol ITEM_ACTIVE1_ = Symbol.intern ("ITEM-ACTIVE");
  private static final Symbol ITEM_STATUS1_ = Symbol.intern ("ITEM-STATUS");
  private static final Symbol FOUNDATION_CLASS1_ = Symbol.intern ("FOUNDATION-CLASS");
  private static final Symbol CLASS1_ = Symbol.intern ("CLASS");
  private static final Symbol ICON_DESCRIPTION_FOR_CLASS1_ = Symbol.intern ("ICON-DESCRIPTION");
  private static final Symbol INSTANTIATE_FOR_CLASS1_ = Symbol.intern ("INSTANTIATE");
  private static final Symbol INCLUDE_IN_MENUS_FOR_CLASS1_ = Symbol.intern ("INCLUDE-IN-MENUS");
  private static final Symbol SYSTEM_MENU_CHOICES_FOR_CLASS1_ = Symbol.intern ("SYSTEM-MENU-CHOICES");
  */
}
