
package com.gensym.util.symbol;

import com.gensym.util.Symbol;

/**
 * Collection of G2 symbols associated with Charts
 * @author rpenny
 * @version 1.0 12/4/97
 */

public interface ChartSymbols extends SymbolConstants {

  public static final Symbol
    ANNOTATIONS_                     = Symbol.intern ("ANNOTATIONS"), //SystemAttributeSymbols.ANNOTATIONS_,
    ATTRIBUTES_                      = Symbol.intern ("ATTRIBUTES"),
    AXIS_CROSSOVER_                  = Symbol.intern ("AXIS-CROSSOVER"),
    AXIS_FEATURES_                   = Symbol.intern ("AXIS-FEATURES"),
    AXIS_MAXIMUM_                    = Symbol.intern ("AXIS-MAXIMUM"),
    AXIS_MINIMUM_                    = Symbol.intern ("AXIS-MINIMUM"),
    BACKGROUND_COLOR_                = Symbol.intern ("BACKGROUND-COLOR"), //VirtualAttributeSymbols.BACKGROUND_COLOR_,
    BAR_                             = Symbol.intern ("BAR"),
    BORDER_COLOR_                    = Symbol.intern ("BORDER-COLOR"), //VirtualAttributeSymbols.BORDER_COLOR_,
    CHART_DATA_POINT_                = Symbol.intern ("CHART-DATA-POINT"),
    COLUMN_                          = Symbol.intern ("COLUMN"),
    COLUMN_CHART_STYLE_              = Symbol.intern ("COLUMN-CHART-STYLE"),
    CONNECTION_LINE_VISIBLE_         = Symbol.intern ("CONNECTION-LINE-VISIBLE"),
    CROSS_                           = Symbol.intern ("CROSS"),
    DATA_POINT_FEATURES_             = Symbol.intern ("DATA-POINT-FEATURES"),
    DATA_SERIES_CACHE_1_             = Symbol.intern ("DATA-SERIES-CACHE-1"),
    DATA_SERIES_CACHE_2_             = Symbol.intern ("DATA-SERIES-CACHE-2"),
    DATA_SERIES_FEATURES_            = Symbol.intern ("DATA-SERIES-FEATURES"),
    DATA_SERIES_SOURCE_KIND_         = Symbol.intern ("DATA-SERIES-SOURCE-KIND"),
    DEFAULT_FEATURES_                = Symbol.intern ("DEFAULT-FEATURES"),
    GRID_COLOR_                      = Symbol.intern ("GRID-COLOR"),
    GRID_VISIBLE_                    = Symbol.intern ("GRID-VISIBLE"),
    HEIGHT_                          = Symbol.intern ("HEIGHT"),
    INDEX_                           = Symbol.intern ("INDEX"),
    INDICATOR_                       = Symbol.intern ("INDICATOR"),
    INDICATOR_VISIBLE_               = Symbol.intern ("INDICATOR-VISIBLE"),
    LINE_CHART_STYLE_                = Symbol.intern ("LINE-CHART-STYLE"),
    LINE_COLOR_                      = Symbol.intern ("LINE-COLOR"),
    LINE_FROM_LAST_TO_FIRST_POINT_VISIBLE_ = Symbol.intern ("LINE-FROM-LAST-TO-FIRST-POINT-VISIBLE"),
    NUMBER_OF_TICKMARKS_             = Symbol.intern ("NUMBER-OF-TICKMARKS"),
    PART_NAME_                       = Symbol.intern ("PART-NAME"),
    PATH_                            = Symbol.intern ("PATH"),
    RECTANGLE_                       = Symbol.intern ("RECTANGLE"),
    SCATTER_CHART_STYLE_             = Symbol.intern ("SCATTER-CHART-STYLE"),
    SOLID_BAR_                       = Symbol.intern ("SOLID-BAR"),
    SOLID_COLUMN                     = Symbol.intern ("SOLID_COLUMN"),
    SOLID_COLUMN_                    = Symbol.intern ("SOLID-COLUMN"),
    SQUARE_                          = Symbol.intern ("SQUARE"),
    TEXT_ALIGNMENT_                  = Symbol.intern ("TEXT-ALIGNMENT"), //VirtualAttributeSymbols.TEXT_ALIGNMENT_,
    TEXT_COLOR_                      = Symbol.intern ("TEXT-COLOR"), //VirtualAttributeSymbols.TEXT_COLOR_,
    TEXT_SIZE_                       = Symbol.intern ("TEXT-SIZE"),
    TICKMARK_INTERVAL_               = Symbol.intern ("TICKMARK-INTERVAL"),
    TRIANGLE_                        = Symbol.intern ("TRIANGLE"),
    WIDTH_                           = Symbol.intern ("WIDTH"),
    X_                               = Symbol.intern ("X");
                                      
}                                 
