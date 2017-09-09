
package com.gensym.util.symbol;

import com.gensym.util.Symbol;

/**
 * Collection of G2 type names as symbols
 * Generated from 5.0 Rev. 0
 * @author vkp
 * @version 1.0 8/5/97
 */

public interface G2TypeSymbols extends SymbolConstants {

  public static final Symbol
    ITEM_OR_VALUE_ = Symbol.intern ("ITEM-OR-VALUE"),
    ITEM_          = Symbol.intern ("ITEM"),
    ATTRIBUTE_     = Symbol.intern ("ATTRIBUTE"),
    CLASS_         = Symbol.intern ("CLASS"), //VirtualAttributeSymbols.CLASS_,
    VALUE_         = Symbol.intern ("VALUE"),
    SEQUENCE_      = Symbol.intern ("SEQUENCE"),
    STRUCTURE_     = Symbol.intern ("STRUCTURE"),
    TRUTH_VALUE_   = Symbol.intern ("TRUTH-VALUE"),
    QUANTITY_      = Symbol.intern ("QUANTITY"),
    INTEGER_       = Symbol.intern ("INTEGER"),
    FLOAT_         = Symbol.intern ("FLOAT"),
    TEXT_          = Symbol.intern ("TEXT"), //VirtualAttributeSymbols.TEXT_,
    SYMBOL_        = Symbol.intern ("SYMBOL"),
    OBJECT_        = Symbol.intern ("OBJECT");

}
