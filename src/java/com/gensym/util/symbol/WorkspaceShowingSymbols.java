

package com.gensym.util.symbol;

import com.gensym.util.Symbol;

/**
 * Collection of G2 symbols used in attribute export
 * @author vkp
 * @version 1.0 11/11/97
 */

public interface WorkspaceShowingSymbols extends SymbolConstants {

  public static final Symbol
    ITEM_                              = Symbol.intern ("ITEM"), //G2ClassSymbols.ITEM_,
    SYMBOLIC_X_IN_WINDOW_              = Symbol.intern ("SYMBOLIC-X-IN-WINDOW"),
    SYMBOLIC_X_IN_WORKSPACE_           = Symbol.intern ("SYMBOLIC-X-IN-WORKSPACE"),
    SYMBOLIC_X_OFFSET_DIRECTION_       = Symbol.intern ("SYMBOLIC-X-OFFSET-DIRECTION"),
    SYMBOLIC_X_SCALE_                  = Symbol.intern ("SYMBOLIC-X-SCALE"),
    SYMBOLIC_Y_IN_WINDOW_              = Symbol.intern ("SYMBOLIC-Y-IN-WINDOW"),
    SYMBOLIC_Y_IN_WORKPACE_            = Symbol.intern ("SYMBOLIC-Y-IN-WORKPACE"),
    SYMBOLIC_Y_OFFSET_DIRECTION_       = Symbol.intern ("SYMBOLIC-Y-OFFSET-DIRECTION"),
    SYMBOLIC_Y_SCALE_                  = Symbol.intern ("SYMBOLIC-Y-SCALE"),
    X_IN_WINDOW_                       = Symbol.intern ("X-IN-WINDOW"),
    X_IN_WORKSPACE_                    = Symbol.intern ("X-IN-WORKSPACE"),
    X_MAGNIFICATION_                   = Symbol.intern ("X-MAGNIFICATION"),
    X_OFFSET_UNITS_                    = Symbol.intern ("X-OFFSET-UNITS"),
    Y_IN_WINDOW_                       = Symbol.intern ("Y-IN-WINDOW"),
    Y_IN_WORKSPACE_                    = Symbol.intern ("Y-IN-WORKSPACE"),
    Y_MAGNIFICATION_                   = Symbol.intern ("Y-MAGNIFICATION"),
    Y_OFFSET_UNITS_                    = Symbol.intern ("Y-OFFSET-UNITS"),
    FULL_                              = Symbol.intern ("FULL"),
    THREE_QUARTER_                     = Symbol.intern ("THREE-QUARTER"),
    HALF_                              = Symbol.intern ("HALF"),
    ONE_QUARTER_                       = Symbol.intern ("ONE-QUARTER"),
    CURRENT_                           = Symbol.intern ("CURRENT");
}
