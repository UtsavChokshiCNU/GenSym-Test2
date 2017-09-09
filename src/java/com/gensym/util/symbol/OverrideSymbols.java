
package com.gensym.util.symbol;

import com.gensym.util.Symbol;

/**
 * Symbols used in Beans Talk
 * @author vkp
 * @version 1.0 8/27/97
 */

public interface OverrideSymbols extends SymbolConstants {

  public static final Symbol
    VERSION_                        = Symbol.intern ("VERSION"),
    CLASS_INFO_                     = Symbol.intern ("CLASS-INFO"),
    INTERFACES_                     = Symbol.intern ("INTERFACES"),
    PROPERTIES_                     = Symbol.intern ("PROPERTIES"),
    METHODS_                        = Symbol.intern ("METHODS"),
    EVENTS_                         = Symbol.intern ("EVENTS"),
    FIELDS_                         = Symbol.intern ("FIELDS"),
    IMPORTS_                        = Symbol.intern ("IMPORTS"),
    PROPERTY_NAME_                  = Symbol.intern ("PROPERTY-NAME"),
    GETTER_INTERFACE_               = Symbol.intern ("GETTER-INTERFACE"),
    GETTER_IMPLEMENTATION_          = Symbol.intern ("GETTER-IMPLEMENTATION"),
    GETTER_COMMENTS_                = Symbol.intern ("GETTER-COMMENTS"),
    SETTER_INTERFACE_               = Symbol.intern ("SETTER-INTERFACE"),
    SETTER_IMPLEMENTATION_          = Symbol.intern ("SETTER-IMPLEMENTATION"),
    SETTER_COMMENTS_                = Symbol.intern ("SETTER-COMMENTS"),
    METHOD_NAME_                    = Symbol.intern ("METHOD-NAME"), //MethodExportSymbols.METHOD_NAME_,
    INTERFACE_                      = Symbol.intern ("INTERFACE"),
    IMPLEMENTATION_                 = Symbol.intern ("IMPLEMENTATION"),
    COMMENTS_                       = Symbol.intern ("COMMENTS"),
    EVENT_NAME_                     = Symbol.intern ("EVENT-NAME"),
    ADD_LISTENER_INTERFACE_         = Symbol.intern ("ADD-LISTENER-INTERFACE"),
    ADD_LISTENER_IMPLEMENTATION_    = Symbol.intern ("ADD-LISTENER-IMPLEMENTATION"),
    ADD_LISTENER_COMMENTS_          = Symbol.intern ("ADD-LISTENER-COMMENTS"),
    REMOVE_LISTENER_INTERFACE_      = Symbol.intern ("REMOVE-LISTENER-INTERFACE"),
    REMOVE_LISTENER_IMPLEMENTATION_ = Symbol.intern ("REMOVE-LISTENER-IMPLEMENTATION"),
    REMOVE_LISTENER_COMMENTS_       = Symbol.intern ("REMOVE-LISTENER-COMMENTS"),
    FIELD_NAME_                     = Symbol.intern ("FIELD-NAME"),
    DECLARATION_                    = Symbol.intern ("DECLARATION"),
    INITIAL_VALUE_                  = Symbol.intern ("INITIAL-VALUE"), //SystemAttributeSymbols.INITIAL_VALUE_,
    IMPORT_NAME_                    = Symbol.intern ("IMPORT-NAME"),
    TYPE_OR_PACKAGE_                = Symbol.intern ("TYPE-OR-PACKAGE");
}
