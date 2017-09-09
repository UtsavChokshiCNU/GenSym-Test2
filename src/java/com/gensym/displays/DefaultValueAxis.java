/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DefaultValueAxis.java
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.displays;

import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import java.awt.Color;

/** A pre-initialized version that acts as the default version
 * in a chart. All important slots are initialized to be non-null;
 */
class DefaultValueAxis extends ValueAxis {

  public DefaultValueAxis(TrendChart chart) {
    super(chart, null, DEFAULT_);
    baselineColor = Color.black;
    baselineVisible = Boolean.TRUE;
    gridLinesPerLabel = DEFAULT_GRID_LINES_PER_LABEL_OBJ;
    gridLinesVisible = Boolean.TRUE;
    significantDigitsForLabels = DEFAULT_SIGNIFICANT_DIGITS_FOR_LABELS_OBJ;
    showLabelsAsPercent = Boolean.FALSE;
    labelFrequencyStruct = DEFAULT_LABEL_FREQUENCY_STRUCT;
    labelColor = Color.black;
    labelsVisible = Boolean.TRUE;
    valueAxisVisible = Boolean.TRUE;
    rangeSlackPercentage = DEFAULT_RANGE_SLACK_PERCENTAGE_OBJ;
    rangeMode = AUTOMATIC_OBJ;
    rangeBounds = null;
    valueAxisPosition = RIGHT_OBJ;
  }

  @Override
  public void configure(Chart genericChart) {
  }  

  @Override
  public Structure getRangeBounds() {
    return rangeBounds;
  }
}
