
package com.gensym.util.symbol;

import com.gensym.util.Symbol;

/**
 * Collection of G2 symbols used in type specifications
 * @author vkp
 * @version 1.0 8/27/97
 */

public interface AttributeTypeSpecificationSymbols extends G2TypeSymbols, AttributeExportSymbols {

  public static final Symbol
    AND_              = Symbol.intern ("AND"),
    ATTRIBUTE_INITIALIZATIONS_     = Symbol.intern ("ATTRIBUTE-INITIALIZATIONS"),
    CLASS_NAME_       = Symbol.intern ("CLASS-NAME"), //SystemAttributeSymbols.CLASS_NAME_,
    ELEMENT_TYPE_     = Symbol.intern ("ELEMENT-TYPE"), //SystemAttributeSymbols.ELEMENT_TYPE_,
    FLOAT_RANGE_      = Symbol.intern ("FLOAT-RANGE"),
    HIGH_             = Symbol.intern ("HIGH"),
    INTEGER_RANGE_    = Symbol.intern ("INTEGER-RANGE"),
    INITIALIZATION_   = Symbol.intern ("INITIALIZATION"),
    LOW_              = Symbol.intern ("LOW"),
    MAXIMUM_ELEMENTS_ = Symbol.intern ("MAXIMUM-ELEMENTS"),
    MEMBER_           = Symbol.intern ("MEMBER"),
    MINIMUM_ELEMENTS_ = Symbol.intern ("MINIMUM-ELEMENTS"),
    NONE_             = Symbol.intern ("NONE"),
    NOT_              = Symbol.intern ("NOT"),
    OPERAND           = Symbol.intern ("OPERAND"),
    OPERANDS_         = Symbol.intern ("OPERANDS"),
    OR_               = Symbol.intern ("OR"),
    POSSIBLE_VALUES_  = Symbol.intern ("POSSIBLE-VALUES"),
    QUANTITY_RANGE_   = Symbol.intern ("QUANTITY-RANGE"),
    REQUIRED_SLOTS_   = Symbol.intern ("REQUIRED-SLOTS"),
    SLOTS_            = Symbol.intern ("SLOTS"),
    TYPE_OR_OPERATOR_ = Symbol.intern ("TYPE-OR-OPERATOR");
    
}
