
package com.gensym.util.symbol;

import com.gensym.util.Symbol;

/**
 * Collection of G2 symbols used in attribute export
 * @author vkp
 * @version 1.0 8/27/97
 */

public interface AttributeExportSymbols extends SymbolConstants {

  public static final Symbol
    TYPE_              = Symbol.intern ("TYPE"), //SystemAttributeSymbols.TYPE_,
    ATTRIBUTE_NAME_    = Symbol.intern ("ATTRIBUTE-NAME"),
    TEXT_READABLE_     = Symbol.intern ("TEXT-READABLE"),
    TEXT_WRITABLE_     = Symbol.intern ("TEXT-WRITABLE"),
    VALUE_READABLE_    = Symbol.intern ("VALUE-READABLE"),
    VALUE_WRITABLE_    = Symbol.intern ("VALUE-WRITABLE"),
    IS_SYSTEM_DEFINED_ = Symbol.intern ("IS-SYSTEM-DEFINED"),
    DEFINING_CLASS_    = Symbol.intern ("DEFINING-CLASS"),
    INITIAL_VALUE_     = Symbol.intern ("INITIAL-VALUE"), //SystemAttributeSymbols.INITIAL_VALUE_,
    INITIAL_CLASS_     = Symbol.intern ("INITIAL-CLASS"),
    INITIAL_TYPE_      = Symbol.intern ("INITIAL-TYPE"),
    EDITOR_GRAMMAR_    = Symbol.intern ("EDITOR-GRAMMAR"),
    SUPERSEDED_        = Symbol.intern ("SUPERSEDED"),
    SYSTEM_ATTRIBUTE_DESIGNATION_   = Symbol.intern ("SYSTEM-ATTRIBUTE-DESIGNATION"),
    USER_ATTRIBUTE_NAME_ = Symbol.intern ("USER-ATTRIBUTE-NAME");

}
