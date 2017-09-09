/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      TrendChart.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:11:44 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import java.util.Hashtable;
import java.util.Enumeration;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import com.gensym.ntw.util.TrendChartEventMulticaster;
import com.gensym.ntw.util.TrendChartEvent;
import com.gensym.ntw.util.TrendChartListener;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.util.Denotation;
import com.gensym.util.AttributeDenotation;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.UnexpectedException;
import com.gensym.util.CorruptionException;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.HistoryRingBuffer;
import com.gensym.util.ClassManager;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.message.Trace;
import com.gensym.message.MessageKey;
import com.gensym.message.Resource;

public interface TrendChart extends com.gensym.util.symbol.TrendChartSymbols, com.gensym.classes.Item, com.gensym.classes.Block {

  public static final Symbol TREND_CHART_ = com.gensym.util.symbol.G2ClassSymbols.TREND_CHART_;
  static final Symbol g2ClassName = TREND_CHART_;
  static final Symbol[] classInheritancePath = new Symbol[] {TREND_CHART_, ITEM_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /* Overriden Property - ACTIVATION-STATE */
  /**  Property Getter for ACTIVATION-STATE */
  public boolean getActivationState();

  /* Overriden Property - TIMESPAN */
  /**  Property Getter for TIMESPAN */
  public Structure getTimespan();

  /* Overriden Property - VALUE-AXIS-EXTREMA */
  /**  Property Getter for VALUE-AXIS-EXTREMA */
  public Sequence getValueAxisExtrema();

  /* Overriden Property - INITIAL-DATA */
  /**  Property Getter for INITIAL-DATA */
  public Sequence getInitialData();

  /* Overriden Property - LAST-UPDATE-TIME */
  /**  Property Getter for LAST-UPDATE-TIME */
  public long getLastUpdateTime();


  /* Overriden Property - ICON */
  /** This is for access by com.gensym.displays.TrendChart.
   * @undocumented
   */
  public Structure getIcon(Symbol className)
  throws G2AccessException;

  /* Overriden Property - HISTORY */
  /** Returns the history buffer for the specified plot.
   */
  public HistoryRingBuffer getHistory(java.lang.Object plotUid);






  /**
   * Generated Property Getter for attribute -- TITLE
   * @return the value of the TITLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TITLE is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getTitle() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TITLE
   * @param title new value to conclude for TITLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTitle(java.lang.String title) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PLOTS
   * @return the value of the PLOTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PLOTS is : 
   * (Sequence 
    (Structure 
      NAMES
        (OR NoItem
            Symbol
            (Sequence Symbol 1))
      CHART-ELEMENT-UID
        (OR Symbol
            Integer)
      USE-LOCAL-HISTORY? BooleanTruthValue
      VALUE-AXIS-NAME-OR-NUMBER
        (OR Symbol
            Integer)
      POINT-FORMAT-NAME-OR-NUMBER
        (OR Symbol
            Integer)
      CONNECTOR-FORMAT-NAME-OR-NUMBER
        (OR Symbol
            Integer)
      UPDATE-INTERVAL
        (Structure 
          UPDATE-INTERVAL Quantity
          GRANULARITY Quantity)
      WAIT-INTERVAL Quantity
      UPDATE-PRIORITY
        (MEMBER 1 2 3 4 5 6 7 8 9 10)
      MAY-REQUEST-DATA-SEEKING? BooleanTruthValue
      MAY-REQUEST-EVENT-UPDATES? BooleanTruthValue
      USE-SIMULATOR? BooleanTruthValue
      TRACING-AND-BREAKPOINTS
        (OR (MEMBER DEFAULT)
            (Structure 
              WARNING-MESSAGE-LEVEL
                (MEMBER 0 1 2 3)
              TRACING-MESSAGE-LEVEL
                (MEMBER 0 1 2 3)
              BREAKPOINT-LEVEL
                (MEMBER 0 1 2 3)
              SOURCE-STEPPING-LEVEL
                (MEMBER 0 1)))
      INCLUDE-IN-LEGEND? BooleanTruthValue
      EXPRESSION Text)
    1))
   *
   */
  public com.gensym.util.Sequence getPlots() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PLOTS
   * @param plots new value to conclude for PLOTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPlots(com.gensym.util.Sequence plots) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- VALUE-AXES
   * @return the value of the VALUE-AXES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for VALUE-AXES is : 
   * (Sequence 
    (Structure 
      NAMES
        (OR NoItem
            Symbol
            (Sequence Symbol 1))
      CHART-ELEMENT-UID
        (OR Symbol
            Integer)
      VALUE-AXIS-VISIBLE? BooleanTruthValue
      VALUE-AXIS-POSITION
        (MEMBER RIGHT LEFT)
      RANGE-MODE
        (MEMBER FIXED AUTORANGING-ON-DATA-WINDOW AUTORANGING-ON-ALL-PAST-VALUES)
      RANGE-BOUNDS
        (OR NoItem
            (Structure 
              LOWER-BOUND Quantity
              UPPER-BOUND Quantity))
      RANGE-SLACK-PERCENTAGE Integer
      LABELS-VISIBLE? BooleanTruthValue
      LABEL-COLOR
        (Structure 
          LABEL-COLOR-TYPE
            (MEMBER ABSOLUTE MATCHING-PLOT-COLOR)
          COLOR Symbol)
      LABEL-FREQUENCY
        (Structure 
          LABEL-LAYOUT-MODE
            (MEMBER AUTOMATIC GRID-DIVISION INTERVAL)
          NUMBER-OF-GRID-DIVISIONS Integer
          INTERVAL-WIDTH Quantity
          INTERVAL-ORIGIN Quantity)
      SHOW-LABELS-AS-PERCENT? BooleanTruthValue
      SIGNIFICANT-DIGITS-FOR-LABELS Integer
      GRID-LINES-VISIBLE? BooleanTruthValue
      GRID-LINE-COLOR
        (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL CYAN 
                DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN 
                GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN PINK 
                PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE VIOLET 
                VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE 
                LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD 
                LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD BEIGE LIGHT-PINK 
                EXTRA-LIGHT-GRAY)
      GRID-LINES-PER-LABEL Integer
      EXTRA-GRID-LINES
        (OR NoItem
            (Sequence 
              (Structure 
                VALUE Quantity
                COLOR Symbol)
              1)))
      BASELINE-VISIBLE? BooleanTruthValue
      BASELINE-COLOR
        (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL CYAN 
                DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN 
                GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN PINK 
                PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE VIOLET 
                VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE 
                LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD 
                LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD BEIGE LIGHT-PINK 
                EXTRA-LIGHT-GRAY))
    1))
   *
   */
  public com.gensym.util.Sequence getValueAxes() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- VALUE-AXES
   * @param valueAxes new value to conclude for VALUE-AXES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setValueAxes(com.gensym.util.Sequence valueAxes) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TIME-AXIS
   * @return the value of the TIME-AXIS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TIME-AXIS is : 
   * (Structure 
    DATA-WINDOW-TIME-SPAN
      (Structure 
        DATA-WINDOW-TIME-SPAN-MODE
          (MEMBER SHOW-ALL-HISTORY INTERVAL)
        NUMBER-OF-SECONDS Integer)
    TOTAL-TIME-SPAN
      (Structure 
        TOTAL-TIME-SPAN-MODE
          (MEMBER SAME-AS-DATA-WINDOW INTERVAL)
        NUMBER-OF-SECONDS Integer)
    END-TIME
      (Structure 
        END-TIME-MODE
          (MEMBER CURRENT-TIME LAST-SAMPLE START-RELATIVE)
        NUMBER-OF-SECONDS Integer)
    DISPLAY-UPDATE-INTERVAL Quantity
    JUMP-SCROLL? BooleanTruthValue
    JUMP-SCROLL-INTERVAL
      (Structure 
        SCROLL-INTERVAL-TYPE
          (MEMBER AUTOMATIC INTERVAL)
        INTERVAL Integer)
    ABSOLUTE-LABELS-VISIBLE? BooleanTruthValue
    RELATIVE-LABELS-VISIBLE? BooleanTruthValue
    LABEL-FREQUENCY
      (Structure 
        LABEL-FREQUENCY-MODE
          (MEMBER NO-LABELS SYNCHRONIZED INTERVAL)
        NUMBER-OF-SECONDS Integer)
    LABEL-ALIGNMENT
      (MEMBER LEFT RIGHT CENTER)
    TIME-FORMAT
      (MEMBER HH-MM HH-MM-AS-AN-INTERVAL HH-MM-AM-PM HH-MM-SS HH-MM-SS-AS-AN-INTERVAL 
              HH-MM-SS-AM-PM MM-SS MM-SS-AS-AN-INTERVAL DD-HH-MM-AS-AN-INTERVAL MMM-DD-HH-MM 
              MM-DD-HH-MM MM-YY MM-DD-YY YY-MM-DD DD-MM-YY DD-MMM-YYYY MMM-DD-YYYY MMM-YYYY 
              HH.HH-AS-AN-INTERVAL)
    LABEL-COLOR
      (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL CYAN 
              DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW 
              INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON MEDIUM-AQUAMARINE 
              MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN PINK PLUM PURPLE RED 
              SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
              YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE 
              POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW 
              LIGHT-YELLOW LIGHT-GOLDENROD BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
    GRID-LINES-VISIBLE? BooleanTruthValue
    GRID-LINE-COLOR
      (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL CYAN 
              DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW 
              INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON MEDIUM-AQUAMARINE 
              MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN PINK PLUM PURPLE RED 
              SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
              YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE 
              POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW 
              LIGHT-YELLOW LIGHT-GOLDENROD BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
    GRID-LINES-PER-LABEL Integer
    BASELINE-VISIBLE? BooleanTruthValue
    BASELINE-COLOR
      (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL CYAN 
              DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW 
              INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON MEDIUM-AQUAMARINE 
              MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN PINK PLUM PURPLE RED 
              SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
              YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE 
              POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW 
              LIGHT-YELLOW LIGHT-GOLDENROD BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY))
   *
   */
  public com.gensym.util.Structure getTimeAxis() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TIME-AXIS
   * @param timeAxis new value to conclude for TIME-AXIS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTimeAxis(com.gensym.util.Structure timeAxis) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- POINT-FORMATS
   * @return the value of the POINT-FORMATS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for POINT-FORMATS is : 
   * (Sequence 
    (Structure 
      NAMES
        (OR NoItem
            Symbol
            (Sequence Symbol 1))
      CHART-ELEMENT-UID
        (OR Symbol
            Integer)
      MARKERS-VISIBLE? BooleanTruthValue
      MARKER-COLOR
        (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL CYAN 
                DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN 
                GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN PINK 
                PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE VIOLET 
                VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE 
                LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD 
                LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD BEIGE LIGHT-PINK 
                EXTRA-LIGHT-GRAY)
      MARKER-STYLE
        (Structure 
          STANDARD-SHAPE Symbol
          ICON-OF-CLASS Symbol)
      MARKER-FREQUENCY
        (Structure 
          POINTS-PER-MARKER Integer))
    1))
   *
   */
  public com.gensym.util.Sequence getPointFormats() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- POINT-FORMATS
   * @param pointFormats new value to conclude for POINT-FORMATS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPointFormats(com.gensym.util.Sequence pointFormats) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CONNECTOR-FORMATS
   * @return the value of the CONNECTOR-FORMATS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CONNECTOR-FORMATS is : 
   * (Sequence 
    (Structure 
      NAMES
        (OR NoItem
            Symbol
            (Sequence Symbol 1))
      CHART-ELEMENT-UID
        (OR Symbol
            Integer)
      CONNECTORS-VISIBLE? BooleanTruthValue
      CONNECTOR-LINE-COLOR
        (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL CYAN 
                DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN 
                GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN PINK 
                PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE VIOLET 
                VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE 
                LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD 
                LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD BEIGE LIGHT-PINK 
                EXTRA-LIGHT-GRAY)
      CONNECTOR-INTERPOLATION
        (MEMBER SAMPLE-AND-HOLD-,-WITHOUT-RISERS SAMPLE-AND-HOLD LINEAR)
      CONNECTOR-LINE-WIDTH Integer
      CONNECTOR-SHADING-TARGET
        (OR NoItem
            Symbol))
    1))
   *
   */
  public com.gensym.util.Sequence getConnectorFormats() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CONNECTOR-FORMATS
   * @param connectorFormats new value to conclude for CONNECTOR-FORMATS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setConnectorFormats(com.gensym.util.Sequence connectorFormats) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TREND-CHART-FORMAT
   * @return the value of the TREND-CHART-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TREND-CHART-FORMAT is : 
   * (Structure 
    OUTER-BORDER-VISIBLE? BooleanTruthValue
    OUTER-BORDER-COLOR
      (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL CYAN 
              DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW 
              INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON MEDIUM-AQUAMARINE 
              MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN PINK PLUM PURPLE RED 
              SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
              YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE 
              POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW 
              LIGHT-YELLOW LIGHT-GOLDENROD BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
    OUTER-BACKGROUND-COLOR
      (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL CYAN 
              DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW 
              INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON MEDIUM-AQUAMARINE 
              MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN PINK PLUM PURPLE RED 
              SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
              YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE 
              POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW 
              LIGHT-YELLOW LIGHT-GOLDENROD BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
    DATA-WINDOW-BORDER-VISIBLE? BooleanTruthValue
    DATA-WINDOW-BORDER-COLOR
      (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL CYAN 
              DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW 
              INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON MEDIUM-AQUAMARINE 
              MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN PINK PLUM PURPLE RED 
              SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
              YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE 
              POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW 
              LIGHT-YELLOW LIGHT-GOLDENROD BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
    DATA-WINDOW-BACKGROUND-COLOR
      (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL CYAN 
              DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW 
              INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON MEDIUM-AQUAMARINE 
              MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN PINK PLUM PURPLE RED 
              SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
              YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE 
              POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW 
              LIGHT-YELLOW LIGHT-GOLDENROD BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
    LEGEND-VISIBLE? BooleanTruthValue
    LEGEND-COLOR
      (Structure 
        LEGEND-COLOR-TYPE
          (MEMBER ABSOLUTE MATCHING-PLOT-COLOR)
        COLOR Symbol)
    LEGEND-POSITION
      (MEMBER ABOVE BELOW)
    TITLE-VISIBLE? BooleanTruthValue
    TITLE-COLOR
      (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL CYAN 
              DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW 
              INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON MEDIUM-AQUAMARINE 
              MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN PINK PLUM PURPLE RED 
              SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
              YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE 
              POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW 
              LIGHT-YELLOW LIGHT-GOLDENROD BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
    TITLE-POSITION
      (MEMBER ABOVE BELOW))
   *
   */
  public com.gensym.util.Structure getTrendChartFormat() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TREND-CHART-FORMAT
   * @param trendChartFormat new value to conclude for TREND-CHART-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTrendChartFormat(com.gensym.util.Structure trendChartFormat) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- EVALUATION-ATTRIBUTES
   * @return the value of the EVALUATION-ATTRIBUTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for EVALUATION-ATTRIBUTES is : 
   * (OR NoItem
      (Structure 
        MAY-REFER-TO-INACTIVE-ITEMS BooleanTruthValue
        MAY-RUN-WHILE-INACTIVE BooleanTruthValue))
   *
   */
  public com.gensym.util.Structure getEvaluationAttributes() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- EVALUATION-ATTRIBUTES
   * @param evaluationAttributes new value to conclude for EVALUATION-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setEvaluationAttributes(com.gensym.util.Structure evaluationAttributes) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SIZE-IN-WORKSPACE
   * @return the value of the SIZE-IN-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SIZE-IN-WORKSPACE is : 
   * (OR NoItem
      (Structure 
        WIDTH Quantity
        HEIGHT Quantity))
   *
   */
  public com.gensym.util.Structure getSizeInWorkspace() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SIZE-IN-WORKSPACE
   * @param sizeInWorkspace new value to conclude for SIZE-IN-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSizeInWorkspace(com.gensym.util.Structure sizeInWorkspace) throws G2AccessException;

  /* Overriden  - TRENDCHART Event Listeners Management */
  /* Adder */
  /**
   * Adds l as both an ItemListener and a TrendChartListener.
   * @undocumented
   */
  public void addTrendChartListener(TrendChartListener l) throws G2AccessException;
  /* Remover */
  /**
   * removes l as both an ItemListener and a TrendChartListener.
   * This clears all the history data store from the subscription
   * if l is the last listener to be removed.
   * @undocumented
   */
  public void removeTrendChartListener(TrendChartListener l)
  throws G2AccessException;

  /* Overriden method - PROCESS-ITEM-EVENT */
  /**
   * Overriden to provide information regarding additions and deletions
   * to multiple compound slots (value-axes, connector-formats,
   * point-formats, and plots).
   */
  @Override
  public void processItemEvent(ItemEvent e);

  /* Overriden method - PROCESS-TREND-CHART-EVENT */
  /**
   * @undocumented
   */
  public void processTrendChartEvent(TrendChartEvent event);

  /* Overriden method - ADD-TREND-CHART-LISTENER-RETRIEVING-STATE */
  /**
   * Adds listener as both an ItemListener and a TrendChartListener.
   * @returns current state of the trendChart
   * @undocumented
   */
  public Structure addTrendChartListenerRetrievingState
  (TrendChartListener listener) throws G2AccessException;

}
