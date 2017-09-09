
package com.gensym.util.symbol;

import com.gensym.util.Symbol;

/**
 * Collection of G2 symbols associated with TrendCharts
 * @author rpenny
 * @version 1.0 12/4/97
 */

public interface TrendChartSymbols extends SymbolConstants {

  public static final Symbol
    ACTIVATION_                        = Symbol.intern ("ACTIVATION"),
    ACTIVATION_VALUE_                  = Symbol.intern ("ACTIVATION-VALUE"),
    CHART_ELEMENT_UID_                 = Symbol.intern ("CHART-ELEMENT-UID"),
    CURRENT_VALUE_                     = Symbol.intern ("CURRENT-VALUE"),
    CURRENT_G2_TIME_                   = Symbol.intern ("CURRENT-G2-TIME"),
    DATA_BURST_                        = Symbol.intern ("DATA-BURST"),
    DATA_WINDOW_BACKGROUND_COLOR_      = Symbol.intern ("DATA-WINDOW-BACKGROUND-COLOR"),
    DATA_WINDOW_BORDER_COLOR_          = Symbol.intern ("DATA-WINDOW-BORDER-COLOR"),
    DATA_WINDOW_BORDER_VISIBLEQ_       = Symbol.intern ("DATA-WINDOW-BORDER-VISIBLE?"),
    DATA_WINDOW_TIME_SPAN_MODE_        = Symbol.intern ("DATA-WINDOW-TIME-SPAN-MODE"),
    DATA_WINDOW_TIME_SPAN_             = Symbol.intern ("DATA-WINDOW-TIME-SPAN"),
    END_TIME_                          = Symbol.intern ("END-TIME"),
    FOREGROUND_                        = Symbol.intern ("FOREGROUND"),
    GENERAL_UPDATE_                    = Symbol.intern ("GENERAL-UPDATE"),
    GRANULARITY_                       = Symbol.intern ("GRANULARITY"),
    HISTORY_COLLECTION_TIMES_          = Symbol.intern ("HISTORY-COLLECTION-TIMES"),
    HISTORY_INDEX_START_               = Symbol.intern ("HISTORY-INDEX-START"),
    HISTORY_VALUES_                    = Symbol.intern ("HISTORY-VALUES"),
    ICON_OF_CLASS_                     = Symbol.intern ("ICON-OF-CLASS"),
    INITIAL_PLOT_DATA_                 = Symbol.intern ("INITIAL-PLOT-DATA"),
    LEGEND_POSITION_                   = Symbol.intern ("LEGEND-POSITION"),
    LEGEND_VISIBLEQ_                   = Symbol.intern ("LEGEND-VISIBLE?"),
    NEW_END_TIME_                      = Symbol.intern ("NEW-END-TIME"),
    NEW_EXTREMA_                       = Symbol.intern ("NEW-EXTREMA"),
    NEW_PLOT_DATA_                     = Symbol.intern ("NEW-PLOT-DATA"),
    NEW_TIMESPAN_                      = Symbol.intern ("NEW-TIMESPAN"),
    NUMBER_OF_SECONDS_                 = Symbol.intern ("NUMBER-OF-SECONDS"),
    OUTER_BACKGROUND_COLOR_            = Symbol.intern ("OUTER-BACKGROUND-COLOR"),
    OUTER_BORDER_COLOR_                = Symbol.intern ("OUTER-BORDER-COLOR"),
    OUTER_BORDER_VISIBLEQ_             = Symbol.intern ("OUTER-BORDER-VISIBLE?"),
    PLOT_DATA_                         = Symbol.intern ("PLOT-DATA"),
    PLUS_SIGN_                         = Symbol.intern ("PLUS-SIGN"),
    POINTS_PER_MARKER_                 = Symbol.intern ("POINTS-PER-MARKER"),
    POINT_FORMATS_                     = Symbol.intern ("POINT-FORMATS"), //SystemAttributeSymbols.POINT_FORMATS_,
    PROCESSED_PLOT_DATA_               = Symbol.intern ("PROCESSED-PLOT-DATA"),
    RENEW_FULL_HISTORY_                = Symbol.intern ("RENEW-FULL-HISTORY"),
    SLOT_CHANGE_                       = Symbol.intern ("SLOT-CHANGE"),
    SQUARE_                            = Symbol.intern ("SQUARE"), //ChartSymbols.SQUARE_,
    STANDARD_SHAPE_                    = Symbol.intern ("STANDARD-SHAPE"),
    TIME_DELTA_                        = Symbol.intern ("TIME-DELTA"),
    TIMESPAN_INFO_                     = Symbol.intern ("TIMESPAN-INFO"),
    TIMESPAN_                          = Symbol.intern ("TIMESPAN"),
    TIME_BOUNDS_                       = Symbol.intern ("TIME-BOUNDS"),
    TITLE_                             = Symbol.intern ("TITLE"), //SystemAttributeSymbols.TITLE_,
    TITLE_COLOR_                       = Symbol.intern ("TITLE-COLOR"),
    TITLE_POSITION_                    = Symbol.intern ("TITLE-POSITION"),
    TITLE_VISIBLE_Q_                   = Symbol.intern ("TITLE-VISIBLE?"),
    TOTAL_TIME_SPAN_MODE_              = Symbol.intern ("TOTAL-TIME-SPAN-MODE"),
    TOTAL_TIME_SPAN_                   = Symbol.intern ("TOTAL-TIME-SPAN"),
    TRANSPARENT_                       = Symbol.intern ("TRANSPARENT"),
    TREND_CHART_ACTIVE_                = Symbol.intern ("TREND-CHART-ACTIVE"),
    TREND_CHART_FORMAT_                = Symbol.intern ("TREND-CHART-FORMAT"), //SystemAttributeSymbols.TREND_CHART_FORMAT_,
    TRIANGLE_                          = Symbol.intern ("TRIANGLE"), //ChartSymbols.TRIANGLE_,
    UPDATE_INTERVAL_                   = Symbol.intern ("UPDATE-INTERVAL"),
    UPDATE_NOTE_                       = Symbol.intern ("UPDATE-NOTE"),
    VALUE_AXIS_EXTREMA_                = Symbol.intern ("VALUE-AXIS-EXTREMA");
  public static final Symbol AUTOMATIC_ = Symbol.intern ("AUTOMATIC");
  public static final Symbol INTERVAL_ = Symbol.intern ("INTERVAL");
  public static final Symbol GRID_DIVISION_ =
  Symbol.intern ("GRID-DIVISION");
  
  public static final Symbol INTERVAL_ORIGIN_ =
  Symbol.intern ("INTERVAL-ORIGIN");
  public static final Symbol INTERVAL_WIDTH_ =
  Symbol.intern ("INTERVAL-WIDTH");
  public static final Symbol LABEL_LAYOUT_MODE_ =
  Symbol.intern ("LABEL-LAYOUT-MODE");
  public static final Symbol AUTORANGING_ON_DATA_WINDOW_ = 
  Symbol.intern ("AUTORANGING-ON-DATA-WINDOW");
  public static final Symbol RIGHT_ = Symbol.intern ("RIGHT");
  public static final Symbol LEFT_ = Symbol.intern ("LEFT");
  public static final Symbol UPPER_BOUND_ = Symbol.intern ("UPPER-BOUND");
  public static final Symbol LOWER_BOUND_ = Symbol.intern ("LOWER-BOUND");
  public static final Symbol DEFAULT_ = Symbol.intern("DEFAULT");
  public static final Symbol FIXED_MODE_ = Symbol.intern ("FIXED-MODE");
  public static final Symbol FIXED_ = Symbol.intern ("FIXED");
  public static final Symbol HIGH_WATER_MARKING_ = Symbol.intern ("HIGH-WATER-MARKING");
  public static final Symbol AUTORANGING_ON_ALL_PAST_VALUES_ = Symbol.intern ("AUTORANGING-ON-ALL-PAST-VALUES");
  public static final Symbol NONE_ = Symbol.intern ("NONE");
  public static final Symbol LINEAR_ = Symbol.intern ("LINEAR");
  public static final Symbol SAMPLE_AND_HOLD_ = Symbol.intern ("SAMPLE-AND-HOLD");
  public static final Symbol SAMPLE_AND_HOLD_WITHOUT_RISERS_ = Symbol.intern ("SAMPLE-AND-HOLD-,-WITHOUT-RISERS");
  public static final Symbol BOTTOM_ = Symbol.intern ("BOTTOM");
  public static final Symbol TOP_ = Symbol.intern ("TOP");
  public static final Symbol CLOCK_DISCONTINUITY_ = Symbol.intern ("CLOCK-DISCONTINUITY");
}
