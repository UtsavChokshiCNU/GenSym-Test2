/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      SimpleChartStyle.java
 *
 *
 */
package com.gensym.displays;

import com.gensym.util.Symbol;

/** Stores the default values for certain annotations that differ by style
 * @version 1.0 12/15/97
 * @author Robert Penny
 * @undocumented
 */

class SimpleChartStyle implements com.gensym.util.symbol.ChartSymbols{
  // fix this: could optimize, as there only ever needs to be three
  // instances in the whole VM.
  Symbol style;

  boolean connectionLineVisible;
  boolean lineFromLastToFirstPointVisible;
  boolean indicatorVisible;
  Symbol indicator;
  
  SimpleChartStyle(Symbol style) {
    this.style = style;
    if (COLUMN_CHART_STYLE_.equals(style)){
      connectionLineVisible = false;
      lineFromLastToFirstPointVisible = true; //???
      indicatorVisible = true;
      indicator = COLUMN_;
    } else if (LINE_CHART_STYLE_.equals(style)){
      connectionLineVisible = true;
      lineFromLastToFirstPointVisible = false;
      indicatorVisible = false;
      indicator = SQUARE_;
    } else if (SCATTER_CHART_STYLE_.equals(style)){
      connectionLineVisible = false;
      lineFromLastToFirstPointVisible = false;
      indicatorVisible = true;
      indicator = SQUARE_;
    }
  }

  boolean getLineFromLastToFirstPointVisible() {
    return lineFromLastToFirstPointVisible;
  }

  boolean getConnectionLineVisible() {
    return connectionLineVisible;
  }

  boolean getIndicatorVisible() {
    return indicatorVisible;
  }

  Symbol getIndicator() {
    return indicator;
  }

  Symbol getStyle() {
    return style;
  }
}
