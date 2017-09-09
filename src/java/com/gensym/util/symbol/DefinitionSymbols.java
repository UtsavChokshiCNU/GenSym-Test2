

package com.gensym.util.symbol;

import com.gensym.util.Symbol;

/**
 * Collection of G2 symbols used in accessing meta-class info
 * @author vkp
 * @version 1.0 10/22/97
 * @version 1.1 06/25/98  Added SYSTEM-CLASS-INHERITANCE-PATH
 */

public interface DefinitionSymbols extends SymbolConstants {

  public static final Symbol
    CLASS_INHERITANCE_PATH_        = Symbol.intern ("CLASS-INHERITANCE-PATH"), //SystemAttributeSymbols.CLASS_INHERITANCE_PATH_,
    SYSTEM_CLASS_INHERITANCE_PATH_ = Symbol.intern ("SYSTEM-CLASS-INHERITANCE-PATH"),
    CLASS_SPECIFIC_ATTRIBUTES_     = Symbol.intern ("CLASS-SPECIFIC-ATTRIBUTES"), //SystemAttributeSymbols.CLASS_SPECIFIC_ATTRIBUTES_,
    CROSS_SECTION_PATTERN_         = Symbol.intern ("CROSS-SECTION-PATTERN"), //SystemAttributeSymbols.CROSS_SECTION_PATTERN_,
    DEFAULT_MESSAGE_PROPERTIES_    = Symbol.intern ("DEFAULT-MESSAGE-PROPERTIES"), //SystemAttributeSymbols.DEFAULT_MESSAGE_PROPERTIES_,
    DEFINITION_                    = Symbol.intern ("DEFINITION"), //G2ClassSymbols.DEFINITION_,
    DIRECT_SUPERIOR_CLASSES_       = Symbol.intern ("DIRECT-SUPERIOR-CLASSES"), //SystemAttributeSymbols.DIRECT_SUPERIOR_CLASSES_,
    ICON_DESCRIPTION_              = Symbol.intern ("ICON-DESCRIPTION"), //SystemAttributeSymbols.ICON_DESCRIPTION_,
    INCLUDE_IN_MENUS_              = Symbol.intern ("INCLUDE-IN-MENUS"), //SystemAttributeSymbols.INCLUDE_IN_MENUS_,
    INITIAL_HEIGHT_                = Symbol.intern ("INITIAL-HEIGHT"),
    INITIAL_WIDTH_                 = Symbol.intern ("INITIAL-WIDTH"),
    INSTANTIATE_                   = Symbol.intern ("INSTANTIATE"), //SystemAttributeSymbols.INSTANTIATE_,
    JUNCTION_BLOCK_FOR_CLASS_      = Symbol.intern ("JUNCTION-BLOCK-FOR-CLASS"),
    STUB_LENGTH_                   = Symbol.intern ("STUB-LENGTH"), //SystemAttributeSymbols.STUB_LENGTH_,
    SYSTEM_MENU_CHOICES_           = Symbol.intern ("SYSTEM-MENU-CHOICES"); //SystemAttributeSymbols.SYSTEM_MENU_CHOICES_;
}
