/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      ValueAxis.java
 *
 * Description:
 *               An axis against which to draw a Plot.
 *
 *      Author:
 *		Robert Penny		Aug/97
 *
 * Modifications:
 *
 */
package com.gensym.displays;

import java.awt.*;
import java.util.Locale;
import java.util.Enumeration;
import java.io.Serializable;
import java.text.NumberFormat;

import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.util.G2ColorMap;

/** An axis against which to draw a Plot.
 *@see com.gensym.displays.TrendChartPlot.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */
public class ValueAxis extends ChartAxis implements Serializable {


  static final int RIGHT = 0;
  static final int LEFT = 1;
  static final Integer RIGHT_OBJ = new Integer(RIGHT);
  static final Integer LEFT_OBJ = new Integer(LEFT);
  static final int DEFAULT_GRID_LINES_PER_LABEL = 1;
  static final Integer DEFAULT_GRID_LINES_PER_LABEL_OBJ =
  new Integer(DEFAULT_GRID_LINES_PER_LABEL);

  static final int DEFAULT_SIGNIFICANT_DIGITS_FOR_LABELS = 4;
  static final Integer DEFAULT_SIGNIFICANT_DIGITS_FOR_LABELS_OBJ =
  new Integer(DEFAULT_SIGNIFICANT_DIGITS_FOR_LABELS);

  static final Structure DEFAULT_LABEL_FREQUENCY_STRUCT =
  new Structure(new Symbol[] {LABEL_LAYOUT_MODE_},
                new Object[] {AUTOMATIC_},
                1);

  static final int DEFAULT_RANGE_SLACK_PERCENTAGE = 10;
  static final Integer DEFAULT_RANGE_SLACK_PERCENTAGE_OBJ =
  new Integer(DEFAULT_RANGE_SLACK_PERCENTAGE);

  static final int
    FIXED_MODE = 0,
    AUTOMATIC = 1,
    HIGH_WATER_MARKING = 2;

  static final Integer
    FIXED_MODE_OBJ = new Integer(FIXED_MODE),
    AUTOMATIC_OBJ = new Integer(AUTOMATIC),
    HIGH_WATER_MARKING_OBJ = new Integer(HIGH_WATER_MARKING);

  private static final Symbol VALUE_ = Symbol.intern ("VALUE");

  public static boolean traceOn = false;
  static Resource i18n =
  Resource.getBundle("com.gensym.displays.Messages");
  static Resource i18nTrace =
  Resource.getBundle("com.gensym.displays.TraceMessages");
  static MessageKey traceKey = 
  Trace.registerMessageKey("com.gensym.displays", ValueAxis.class);

  Color baselineColor = Color.black;
  Boolean baselineVisible = Boolean.TRUE;
  Integer gridLinesPerLabel;
  //Color gridLineColor;
  Boolean gridLinesVisible;
  Integer significantDigitsForLabels;
  Boolean showLabelsAsPercent;
  Integer labelFrequency;
  Structure labelFrequencyStruct;
  boolean matchPlotColor = false;
  //Color labelColor;
  Boolean labelsVisible;
  Boolean valueAxisVisible;
  Integer rangeSlackPercentage;
  Integer rangeMode;
  Symbol rangeModeSymbol;
  Structure rangeBounds;
  Integer valueAxisPosition;

  Integer number = new Integer(1);

  private ValueAxis defaultValueAxis;
  private ValueLabels valueLabels;
  TrendChart chart;
  boolean dataRangeValid;

  public ValueAxis(TrendChart chart,
		   com.gensym.classes.TrendChart g2TrendChart,
		   Object chartElementUid) {
    super(chartElementUid);
    this.chart = chart;
    defaultValueAxis = chart.getDefaultValueAxis();    
    percentFormatter.setMinimumFractionDigits(1);
  }

  @Override
  public void configure(Chart chart) {
    super.configure(chart);
    valueLabels = new ValueLabels(this, dataWindow);
    if (getLabelsVisible())
      valueLabels.setVisible(true);
    // maybe this should just be setDataRangeInvalid;
    setDataRange(visibleValueMinimum, visibleValueMaximum);
    setOrientation(ChartAxis.VERTICAL);
    this.chart = (TrendChart)chart;
    this.chart.add(valueLabels);
  }

  @Override
  public void dispose() {
    chart.remove(valueLabels);
    valueLabels.setVisible(false);
    chart.removeValueAxis(this);
  }

  public void setDataRange(double low, double high) {
    synchronized (this) {
      super.setVisibleDataRange(low, high);
      // In AWT the origin is top left
      setDataOrigin(high);
      visibleValueMinimum = low;
      visibleValueMaximum = high;
      dataRangeValid = true;
    }
    invalidateLabels();
  }

  /** If the axis is "automatic" and has not data being plotted against it
   * it's current data range is not interesting, so a flag must be set
   * to indicate this fact.
   */
  public void setDataRangeInvalid() {
    dataRangeValid = false;
    super.setVisibleDataRange(-1.0, 1.0);
    // In AWT the origin is top left
    setDataOrigin(1.0);
    visibleValueMinimum = -1.0;
    visibleValueMaximum = 1.0;
    invalidateLabels();
  }

  ValueLabels getValueLabels() {
    if (getLabelsVisible())
      return valueLabels;
    else
      return null;
  }

  @Override
  public int transform (double value) throws OutOfBoundsException {
    return super.transform(value);
  }

  public void setBaselineColor(Color baselineColor) {
    this.baselineColor = baselineColor;
  }

  public Color getBaselineColor() {
    return baselineColor;
  }

  public void setBaselineVisible(boolean baselineVisible) {
    if(baselineVisible)
      this.baselineVisible = Boolean.TRUE;
    else
      this.baselineVisible = Boolean.FALSE;
  }

  public boolean getBaselineVisible() {
    return baselineVisible.booleanValue();
  }

  public void setGridLinesPerLabel(int gridLinesPerLabel) {
    this.gridLinesPerLabel = new Integer(gridLinesPerLabel);
  }

  public int getGridLinesPerLabel() {
    return gridLinesPerLabel.intValue();
  }

  private Sequence extraGridLines;

  public Sequence getExtraGridLines(){
      return extraGridLines;
  }

  public void setExtraGridLines(Sequence extraGridLines){
    this.extraGridLines = extraGridLines;
  }

  @Override
  public Color getGridLineColor() {
    if(gridLineColor == null) {
      return defaultValueAxis.getGridLineColor();
    } else {
      return gridLineColor;
    }
  }

  @Override
  public synchronized void setGridLinesVisible(boolean gridLinesVisible) {
    this.gridLinesVisible = new Boolean(gridLinesVisible);
  }

  @Override
  public boolean getGridLinesVisible() {
    if (gridLinesVisible == null) {
      return defaultValueAxis.getGridLinesVisible();
    } else {
      return gridLinesVisible.booleanValue();
    }
  }    

  public void setSignificantDigitsForLabels(int significantDigitsForLabels) {
    this.significantDigitsForLabels =
      new Integer(significantDigitsForLabels);
    invalidateLabels();
  }

  public int getSignificantDigitsForLabels() {
    if (significantDigitsForLabels == null) {
      return defaultValueAxis.getSignificantDigitsForLabels();
    } else {
      return significantDigitsForLabels.intValue();
    }
  }

  private ValueAxis getDefault() {
    return chart.getDefaultValueAxis();
  }

  public void setShowLabelsAsPercent(boolean showLabelsAsPercent) {
    if (showLabelsAsPercent) {
      this.showLabelsAsPercent = Boolean.TRUE;
      numberFormatter = percentFormatter;
    } else {
      this.showLabelsAsPercent = Boolean.FALSE;
      numberFormatter = scientificDecimalFormatter;
    }
    invalidateLabels();
  }

  public boolean getShowLabelsAsPercent() {
    if (showLabelsAsPercent == null) {
      return defaultValueAxis.getShowLabelsAsPercent();
    } else {
    return showLabelsAsPercent.booleanValue();
    }
  }

  private Symbol labelLayoutMode;

  void setLabelLayoutMode(Symbol labelLayoutMode) {
    this.labelLayoutMode = labelLayoutMode;
  }

  Symbol getLabelLayoutMode() {
    if (labelLayoutMode == null) {
      return defaultValueAxis.getLabelLayoutMode();
    } else {
      return labelLayoutMode;
    }
  }

  private static final Symbol NUMBER_OF_GRID_DIVISIONS_ =
  Symbol.intern ("NUMBER-OF-GRID-DIVISIONS");

  private int numberOfGridDivisions;
  private boolean labelsValid = false;

  void invalidateLabels() {
    validWidth = false;
    labelsValid = false;
//     if (valueLabels != null)
//       valueLabels.invalidate();
    chart.acknowledgeLayoutChange();
    chart.repaint();
  }

  public void setLabelFrequency(Structure labelFrequency) {
    labelFrequencyStruct = labelFrequency;
    invalidateLabels();
  }
  
  public void setLabelFrequency(int labelFrequency) {
    this.labelFrequency = new Integer(labelFrequency);
  }

  public Structure getLabelFrequency() {
    if (labelFrequencyStruct == null) {
	return defaultValueAxis.getLabelFrequency();
    } else {
    return labelFrequencyStruct;
    }
  }

  public void setRangeSlackPercentage(int rangeSlackPercentage) {
    this.rangeSlackPercentage = new Integer(rangeSlackPercentage);
  }

  public int getRangeSlackPercentage() {
    return rangeSlackPercentage.intValue();
  }

  /** adaptor method. NOTE, that due to a lisp inconsistency,
   * the actual symbol will depend on whether it is being set
   * as part of initialization, or as a live update.
   */
  public void setRangeMode(Symbol newRangeMode) {
    if (AUTOMATIC_.equals(newRangeMode) ||
	 AUTORANGING_ON_DATA_WINDOW_.equals(newRangeMode)) {
      rangeMode = AUTOMATIC_OBJ;
    } else if (FIXED_MODE_.equals(newRangeMode) ||
	       FIXED_.equals(newRangeMode)) {
      rangeMode = FIXED_MODE_OBJ;
    } else if (HIGH_WATER_MARKING_.equals(newRangeMode) ||
		AUTORANGING_ON_ALL_PAST_VALUES_.equals(newRangeMode)) {
      rangeMode = HIGH_WATER_MARKING_OBJ;
    } else if (newRangeMode == null) {
      rangeMode = null;
    } else {
      throw new CorruptionException(null, "bad range mode: " + newRangeMode);
    }
    invalidateLabels();
  }

  public void setRangeMode(int rangeMode) {
    this.rangeMode = new Integer(rangeMode);
    invalidateLabels();
  }

  public int getRangeMode() {
    if (rangeMode == null) {
      return defaultValueAxis.getRangeMode();
    } else {
      return rangeMode.intValue();
    }
  }

  private double visibleValueMinimum, visibleValueMaximum;
  /** Adaptor method for G2 */
  public void setRangeBounds(Structure rangeBounds) throws
  NoSuchAttributeException {
    Trace.send(5, traceKey, i18nTrace, "vasetRangeBounds", rangeBounds);
    this.rangeBounds = rangeBounds;
    rangeBounds = getRangeBounds();
    if (rangeBounds != null) {
      visibleValueMinimum =
	((Number)rangeBounds.getAttributeValue(LOWER_BOUND_)).
	doubleValue();
      
      visibleValueMaximum =
	((Number)rangeBounds.getAttributeValue(UPPER_BOUND_)).
	doubleValue();
    }
  }

  public Structure getRangeBounds() {
    if (rangeBounds == null) {
      return defaultValueAxis.getRangeBounds();
    } else {
      return rangeBounds;
    }
  }

  public void setValueAxisVisible(boolean yes) {
    valueAxisVisible = new Boolean(yes);
    invalidateLabels();
    //chart.invalidate();
  }

  public boolean getValueAxisVisible() {
    if (valueAxisVisible == null) {
      return defaultValueAxis.getValueAxisVisible();
    } else {
      return valueAxisVisible.booleanValue();
    }
  }

  @Override
  public void setLabelsVisible(boolean yes) {
    labelsVisible = new Boolean(yes);
    invalidateLabels();
    //chart.invalidate();
  }

  @Override
  public boolean getLabelsVisible() {
    if (labelsVisible == null) {
      return defaultValueAxis.getLabelsVisible();
    } else {
      return labelsVisible.booleanValue();
    }
  }
  
  private static final Symbol MATCHING_PLOT_COLOR_ = Symbol.intern ("MATCHING-PLOT-COLOR");
  private static final Symbol LABEL_COLOR_TYPE_ = Symbol.intern ("LABEL-COLOR-TYPE");

  /** Adaptor Method for G2 */
  @Override
  public void setLabelColor(Structure labelColor) {
    if (MATCHING_PLOT_COLOR_.equals(labelColor.getAttributeValue(LABEL_COLOR_TYPE_, null))){
      matchPlotColor = true;
    } else {
      matchPlotColor = false;
      super.setLabelColor(labelColor);
    }
  }

  Color getColorFromPlot() {
    TrendChartPlot plot = chart.getControllingPlotForValueAxis(this);
    if (plot != null) {
//     ConnectorFormat format = plot.getConnectorFormat();
//     // bug? to match G2's behavior, only the connector is used, even if
//     // if the connector is not visible.
//     return format.getConnectorLineColor();
      return plot.getMostVisibleColor();
    } else {
      return labelColor;
    }
  }

  @Override
  public Color getLabelColor() {
    Color labelColor = matchPlotColor ? getColorFromPlot() : super.getLabelColor();
    if (labelColor == null) {
      return defaultValueAxis.getLabelColor();
    } else {
      return labelColor;
    }
  }

  public void setValueAxisPosition(Symbol valueAxisPosition) {
    if (LEFT_.equals(valueAxisPosition)) {
      this.valueAxisPosition = LEFT_OBJ;
    } else if (RIGHT_.equals(valueAxisPosition)) {
      this.valueAxisPosition = RIGHT_OBJ;
    }
  }
  
  public void setValueAxisPosition(int valueAxisPosition) {
    this.valueAxisPosition = new Integer(valueAxisPosition);
  }

  public int getValueAxisPosition() {
    if (valueAxisPosition == null) {
      return defaultValueAxis.getValueAxisPosition();
    } else {
      return valueAxisPosition.intValue();
    }
  }

  boolean positionedOnRight() {
    return RIGHT == getValueAxisPosition();
  }

  Integer getNumber() {
    return number;
  }

  private void setLayoutVariables() {
    Structure labelFrequency = getLabelFrequency();
    if(labelFrequency == null) {
      throw new IllegalArgumentException("Null labelFrequency");
    } else {
      try {
	labelLayoutMode =
	  (Symbol)labelFrequency.getAttributeValue(LABEL_LAYOUT_MODE_);
	Trace.send(10, traceKey, i18nTrace, "vasetLayoutVariables",
		   labelLayoutMode);
	if(INTERVAL_.equals(labelLayoutMode)) {
	  interval = ((Number)labelFrequency.
	    getAttributeValue(INTERVAL_WIDTH_)).doubleValue();
	  origin = ((Number)labelFrequency.
	    getAttributeValue(INTERVAL_ORIGIN_)).doubleValue();
	} else if(GRID_DIVISION_.equals(labelLayoutMode)) {
	  numberOfGridDivisions =
	    ((Number)labelFrequency.
	     getAttributeValue(NUMBER_OF_GRID_DIVISIONS_)).intValue();
	}
      } catch (NoSuchAttributeException nsae) {
	throw new UnexpectedException(nsae);
      }
    }
  }

  //
  // label and grid placements
  //

  private int maxLabels;

  /** Modelled roughly on "compute-vertical-axis-description-from-bounds"
   * from graphs.lisp.
   */
  synchronized void computeAxisDescription() {
    if (labelsValid)
      return;

    setLayoutVariables();

    Symbol layoutMode = getLabelLayoutMode();
    
    maxLabels = MathUtils.floor(dataWindow.getSize().height,
				getLabelHeight());

    Trace.send(10, traceKey, i18nTrace, "vacomputeAxisDescription",
	       layoutMode, new Integer(maxLabels));
    
    if (AUTOMATIC_.equals(layoutMode) || layoutMode == null) {
      computeIntervalAndOriginForAutomaticLabels();
      computeValueTickmarksByIntervalAndOrigin(layoutMode);
    } else if (GRID_DIVISION_.equals(layoutMode)) {
      computeNValueTickmarks();
    } else if (INTERVAL_.equals(layoutMode)) {
      computeValueTickmarksByIntervalAndOrigin(layoutMode);
    } else {
      throw new IllegalArgumentException(i18n.format("vaillegalLayout",
						     layoutMode));
    }
    labelsValid = true;
  }

  int getLabelHeight() {
    return valueLabels.getLabelHeight();
  }

  double interval, origin;
  /** Based on compute-interval-and-origin-for-automatic-labels */
  void computeIntervalAndOriginForAutomaticLabels() {
    double min = getVisibleDataMinimum();
    double max = getVisibleDataMaximum();
//     System.out.println("computeInt1 format: " + numberFormat +
// 		       "; maxLabels: " + maxLabels + "; min: " + min +
// 		       "; max: " + max);
    if (min == max || maxLabels == 0) {
      interval = 1.0;
      origin = 0.0;
    } else if (FIXED_FORMAT == numberFormat) {
      computeIntervalAndOriginForFixedAutomaticLabels(min, max);
    } else if (PERCENT == numberFormat) {
      computeIntervalAndOriginForPercentageLabels(min, max);
    } else {
      computeIntervalAndOriginForMovingAutomaticLabels(min, max);
    }
  }

  void computeIntervalAndOriginForPercentageLabels(double min, double max) {
    int divisor = 1;
    if (maxLabels > 120)
      divisor = 100;
    else if (maxLabels > 60)
      divisor = 50;
    else if (maxLabels > 30)
      divisor = 25;
    else if (maxLabels > 12)
      divisor = 10;
    else if (maxLabels > 6)
      divisor = 5;
    else if (maxLabels > 2)
      divisor = 2;
    interval = (max - min)/divisor;
    origin = min;
  }

  void computeIntervalAndOriginForFixedAutomaticLabels(double min, double max) {
    double lsddForUpper = MathUtils.leastSignificantDecimalDigit(max);
    double lsddForLower = MathUtils.leastSignificantDecimalDigit(min);
    double shiftFactor = Math.pow(10.0, -Math.min(lsddForLower, lsddForUpper));
    long integerRange = Math.round(shiftFactor * max - shiftFactor * min);
    
    origin = min;

    for (int i = maxLabels - 1; i >= 1; i--) {
      if (integerRange % i == 0) {
	interval = (max - min)/(double)i;
	return;
      }
    }
    interval = max - min;
  }

  void computeIntervalAndOriginForMovingAutomaticLabels(double min,
							double max) {
    double range = max - min;
    double placeValue = computePlaceValue(range);
    long roundedUpperBound =
      Math.round(placeValue * MathUtils.floor(max, placeValue));
    long roundedLowerBound =
      Math.round(placeValue * MathUtils.ceil(min, placeValue));
    int desiredLabels = Math.max(MathUtils.floor(maxLabels, 2), 1);

//     System.out.println("intervalAndOriginAuto placeVal: " + placeValue +
// 		       "; roundedLower: " + roundedLowerBound +
// 		       "; roundedUpper: " + roundedUpperBound);

    interval = placeValue;
    for (int i = 0;; i = (i + 1) % 3) {
      if ((roundedUpperBound - roundedLowerBound)/interval < desiredLabels){
	double downRoundedLowerBound =
	  interval * MathUtils.floor(roundedLowerBound, interval);
	if (downRoundedLowerBound >= min) {
	  origin = downRoundedLowerBound;
	}
	else {
	  origin = interval * MathUtils.ceil(roundedLowerBound, interval);
	}
	return;
      }
      double factor = (i == 1 ? 2.5 : 2.0);
      interval = interval * factor;	
    }
  }

  private void computeNValueTickmarks() {
    int count = Math.min(numberOfGridDivisions, maxLabels);
    tickmarkCount = count + 1; // matching doc "bug" in G2
    tickmarkValues = new double[tickmarkCount];
    double min = getVisibleDataMinimum();
    double max = getVisibleDataMaximum();
    double range = max - min;
    double interval = range/(double)count;

    for (int i = 0; i < tickmarkCount; i++) {
      tickmarkValues[i] = min + interval * i;
    }
  }
    
  private double computePlaceValue(double range) {
    double firstGuess =
      Math.pow(10.0, Math.floor(MathUtils.logTen(range)));
    if (range/firstGuess < 5.0)
      return firstGuess/10.0;
    return firstGuess;
  }

  private double computeFirstTickmark(double origin, double min,
				      double localInterval) {
    if (origin == min) {
      return origin;
    }
    
    double lowestMult = MathUtils.floor(min - origin, localInterval);
    double testTickmark = origin + localInterval * lowestMult;

    if (testTickmark >= min)
      return testTickmark;
    else
      return testTickmark + localInterval;
  }

  int tickmarkCount;
  private double[] tickmarkValues;
  
  /** Creates the tickmarkValues array.
   * Must only be called after computeIntervalAndOriginForAutomaticLabels
   * in cases where the labelLayoutMode is AUTOMATIC_.*/
  void computeValueTickmarksByIntervalAndOrigin(Symbol layoutMode) {
    double min = getVisibleDataMinimum();
    double max = getVisibleDataMaximum();
    double range = max - min;
    double localInterval =
      computeReasonableValueAxisInterval(Math.min(interval, range),
					 range);
    double firstTickmark = computeFirstTickmark(origin, min, localInterval);
    Trace.send(10, traceKey, i18nTrace, "vafirstTickmark",
	       new Double(firstTickmark), new Double(origin),
	       new Double(interval));
    tickmarkCount = (int)Math.round(MathUtils.ceil(range, localInterval));
    int tickmarkLimit = tickmarkCount + 1;
    tickmarkValues = new double[tickmarkLimit];

    Trace.send(10, traceKey, i18nTrace, "vacomputeByInterval",
	       new Double(localInterval), new Integer(tickmarkCount),
	       new Double(min), new Double(max));

    int i;
    double val;
    for (val = firstTickmark, i = 0; val <= max && i < tickmarkLimit;
	 val += localInterval) {
      tickmarkValues[i] = val;
      // make sure that the tickmarkCount accurately reflects how many
      // valid entries have been put into the array.
      tickmarkCount = ++i;
    }
  }

  double computeReasonableValueAxisInterval(double interval, double range) {
    if (maxLabels == 0 || interval == 0.0)
      return range;

    double unroundedMultiple = MathUtils.floor(range, maxLabels * interval);
    double factor = (unroundedMultiple < 1.0 ?
		     1.0 :
		     // OK, I don't understand this heuristic, but here it
		     // is, just as it was in the lisp
		     5.0 * MathUtils.ceil(unroundedMultiple, 5.0));
    return interval * factor;
  }
  //  double[] labelPlacements() {

  //
  // label widths
  //

  /*
  private static NumberFormat
  FIXED_FORMATTER = NumberFormat.getNumberInstance(),
    FLOATING_FORMATTER = NumberFormat.getNumberInstance(),
    */
  // can the percentFormatter be static and shared, since it always
  // has the same configuration?
  private NumberFormat
  percentFormatter = NumberFormat.getPercentInstance();

  private NumberFormat
    scientificDecimalFormatter = new ScientificDecimalFormat();
  

  private NumberFormat numberFormatter = scientificDecimalFormatter;

  private int maxLabelWidth, fixedDecimalOffset, floatDecimalOffset,
    fixedLeftDigits, fixedRightDigits;

  private int numberFormat = FLOATING;
  private static final int
  INVISIBLE = 0,
    PERCENT = 1,
    FIXED_FORMAT = 2,
    FLOATING = 3;

  private void computeWidthOfLabels() {
    if (!getLabelsVisible()) {
      Trace.send(10, traceKey, i18nTrace, "vacomputeWidthOfLabels",
		 "Invisible");
      numberFormat = INVISIBLE;
      maxLabelWidth = fixedDecimalOffset = floatDecimalOffset =
	fixedLeftDigits = fixedRightDigits = 0;
    } else if (!dataRangeValid) {
      // fix this: hack: this should be based on what the value axis
      // actually plans on showing, rather than on what I know it
      // will be showing because I just wrote it.
      maxLabelWidth = valueLabels.getStringWidth("  -1.1E304");
      fixedDecimalOffset = floatDecimalOffset = 2;
      fixedLeftDigits = fixedRightDigits = 1;
    } else if (getShowLabelsAsPercent()) {
      Trace.send(10, traceKey, i18nTrace, "vacomputeWidthOfLabels", "Percent");
      numberFormatter = percentFormatter;
      computeWidthOfFixedLabels(true);
    } else {
      Trace.send(10, traceKey, i18nTrace, "vacomputeWidthOfLabels", "else");
      numberFormatter = scientificDecimalFormatter;
      switch (getRangeMode()) {
      case FIXED_MODE:
	computeWidthOfFixedLabels(false);
	break;
      case AUTOMATIC:
      case HIGH_WATER_MARKING:
	computeWidthOfFloatingLabels();
      }
    }
    //    validWidth = true;
  }

  private void computeWidthOfFixedLabels(boolean isPercent) {
    double range =
      (isPercent ? 100.0 :
       Math.max(Math.abs(getVisibleDataMaximum()), Math.abs(getVisibleDataMinimum())));
    int significantDigits =
      (isPercent ? Math.max(4, getSignificantDigitsForLabels()) :
      getSignificantDigitsForLabels());
    Trace.send(10, traceKey, i18nTrace, "vacomputeWidthOfFixedLabels",
	       new Boolean(isPercent), new Double(range),
	       new Integer(significantDigits));
    int placesToLeft = 0;
    // give up if range too great
    if (range > Math.pow(10.0, significantDigits) ||
	range < Math.pow(10.0, 1 - significantDigits)) {
      computeWidthOfFloatingLabels();
    } else {
      if (isPercent) {
	numberFormat = PERCENT;
	numberFormatter = percentFormatter;
	placesToLeft = 3;
      } else {
	placesToLeft =
	  (int)Math.round(Math.max(1.0,
				   1.0 + Math.floor(0.000001 +
						    MathUtils.logTen(range))));
	numberFormat = FIXED_FORMAT;
	numberFormatter = scientificDecimalFormatter;
      }
      int placesToRight = significantDigits - placesToLeft;
//       System.out.println("widthOfFixedLabels. left: " + placesToLeft +
// 			 "; right: " + placesToRight);
      numberFormatter.setMaximumIntegerDigits(placesToLeft);
      numberFormatter.setMaximumFractionDigits(placesToRight);
      String sample = sampleString(numberFormatter);
      maxLabelWidth = valueLabels.getStringWidth(sample);
    }
    validWidth = true;
  }

  boolean validWidth = false;
  int getMaxLabelWidth() {
    if (!validWidth)
      computeWidthOfLabels();
    
    return maxLabelWidth + ValueLabels.LABEL_RIGHT_MARGIN +
      ValueLabels.LABEL_LEFT_MARGIN;
  }

  private boolean isPercent(NumberFormat formatter) {
    return formatter == percentFormatter;
  }

  private String sampleString(NumberFormat formatter) {
    int fractionSize = formatter.getMaximumFractionDigits();
    int integerSize = formatter.getMaximumIntegerDigits();

    try {
      // on the pricipal that 2's and 0's will be the numerical
      // equivalent of "m" in character width.
      double number = 2*Math.pow(10.0, -fractionSize) +
	              2*Math.pow(10.0, integerSize - 1);
      if (isPercent(formatter)) {
	number = number/100.0;
      }
      String returnValue = formatter.format(number);
      Trace.send(10, traceKey, i18nTrace, "vasampleString",
		 new Integer(fractionSize), new Integer(integerSize),
		 new Double(number), returnValue);
      return returnValue;
    } catch (Exception ex) {
      ex.printStackTrace();
      return null;
    }
  }

  private void computeWidthOfFloatingLabels() {
    int significantDigits = getSignificantDigitsForLabels();
    int placesToLeft = (int)MathUtils.ceil(significantDigits, 2);
    int placesToRight = significantDigits - placesToLeft;
    double sampleNumber = -Float.MIN_VALUE;
    numberFormat = FLOATING;
    numberFormatter = scientificDecimalFormatter;
    numberFormatter.setMaximumIntegerDigits(placesToLeft);
    numberFormatter.setMaximumFractionDigits(placesToRight);
    String sample = sampleString(numberFormatter) + "-E304";
    maxLabelWidth = valueLabels.getStringWidth(sample);
    Trace.send(10, traceKey, i18nTrace, "vacomputeWidthOfFloatingLabels",
	       new Integer(significantDigits),
	       sample, new Integer(maxLabelWidth));
  }

  /** NOTE: this should only be called after computeAxisDescription */
  double[] getTickmarkValues() {
    return tickmarkValues;
  }

  /** NOTE: this should only be called after computeAxisDescription */
  int getTickmarkCount() {
    return tickmarkCount;
  }

  NumberFormat getNumberFormatter() {
    return numberFormatter;
  }

  /** draws the grid lines. The labels are drawn by the ValueLabels object */
  void draw(Graphics g, int width) {
    computeAxisDescription();

    Trace.send(5, traceKey, i18nTrace, "vadraw", getChartElementUid());
    g.setColor(getGridLineColor());

    double valueOffset = getDataOrigin();
    double valueScale = getScale();

    if (traceOn) {
      System.out.println("tickmarkValues:");
      for (int i = 0; i < tickmarkValues.length; i++) {
	System.out.println("" + i + "=" + tickmarkValues[i]);
      }
    }

    for(int i = 0; i < tickmarkCount; i++) {
      int yPos =
	(int)Math.floor((valueOffset - tickmarkValues[i]) * valueScale);
      Trace.send(30, traceKey, i18nTrace, "vadrawGrid",
		 new Integer(i), new Integer(yPos));
      g.drawLine(0, yPos, width, yPos);
    }

    if (extraGridLines == null)
      return;

    int size = extraGridLines.size();
    for (int i = 0; i < size; i++) {
      try {
	Structure extraLine = (Structure)extraGridLines.elementAt(i);
	Color currentColor = G2ColorMap.get(extraLine, COLOR_, gridLineColor);
	double currentValue =
	  ((Number)extraLine.getAttributeValue(VALUE_)).doubleValue();
	int yPos = (int)Math.floor((valueOffset - currentValue) * valueScale);
	g.setColor(currentColor);
	g.drawLine(0, yPos, width, yPos);
      } catch (NoSuchAttributeException nsae) {
	throw new CorruptionException(nsae);
      }
    }
  }
      
}
