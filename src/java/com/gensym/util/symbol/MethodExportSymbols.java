package com.gensym.util.symbol;

import com.gensym.util.Symbol;

/**
 * Collection of G2 symbols used in method export
 * @author mdg
 * @version 1.0 12/OCT/1997
 */

public interface MethodExportSymbols extends SymbolConstants {

  public static final Symbol
    ARGUMENT_TYPES_           = Symbol.intern ("ARGUMENT-TYPES"),
    IS_STATIC_                = Symbol.intern ("IS-STATIC"),
    METHOD_NAME_              = Symbol.intern ("METHOD-NAME"),
    METHOD_SOURCE_            = Symbol.intern ("METHOD-SOURCE"),
    RESULT_TYPES_             = Symbol.intern ("RESULT-TYPES");

}
