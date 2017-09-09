package com.gensym.displays;

import com.gensym.util.*;
import com.gensym.util.Set;
import com.gensym.message.*;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.G2ColorMap;
import com.gensym.draw.TextCell;
import com.gensym.draw.TextStyle;
import com.gensym.classes.G2Definition;
import com.gensym.jgi.G2AccessException;

import java.util.*;
import java.awt.*;

/** Corresponds to a G2 TrendChart. Is the awt container of all the visual
 * components of a trend chart, and also manages the properties controlled
 * by the "trend chart format".
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */
public class TrendChart extends Container
implements Chart //implements FormatListener, DataListener
{
  static public final int MINIMUM_DATA_WINDOW_SIZE = 20;

  // housekeeping
  static private Resource i18n =
  Trace.getBundle("com.gensym.displays.Messages");

  static private MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.displays",
			   TrendChart.class);
  static private Resource i18nTrace =
  Trace.getBundle("com.gensym.displays.TraceMessages");

  static private MessageKey traceDraw =
  Trace.registerMessageKey("com.gensym.draw", TrendChart.class);

  public static boolean traceOn = false;

  private static final Symbol chartElementUid_ =
  Symbol.intern("CHART-ELEMENT-UID");

  private static final Symbol MATCHING_PLOT_COLOR_ = Symbol.intern ("MATCHING-PLOT-COLOR");

  //
  // instance variables
  //

  private boolean outerBorderVisible;
  private Color outerBorderColor;

  private String legendPosition;
  private String titlePosition;

  DataAndLabelWindow dataAndLabelWindow;
  DataWindow dataWindow;
  TimeAxis timeAxis;
  private ChartLabel title;
  private ChartSet connectorFormats = new ChartSet();
  private ChartSet markerFormats = new ChartSet();
  private ChartSet plots = new ChartSet();
  private ChartSet valueAxes = new ChartSet();
  private TrendChartLegends trendChartLegends;
  private RelativeTimeLabels relativeTimeLabels;

  private ChartLayoutManager layoutManager;

  private Color defaultBackgroundColor;
  private Symbol colorType = MATCHING_PLOT_COLOR_;
;

  private static final Symbol color_ = Symbol.intern("COLOR");

  private DefaultConnectorFormat defaultConnectorFormat;
  private DefaultMarkerFormat defaultMarkerFormat;
  private DefaultValueAxis defaultValueAxis;
  private DefaultTrendChartPlot defaultTrendChartPlot;

  private long currentTime;

  com.gensym.classes.TrendChart g2TrendChart;

  public TrendChart() {
    super();
    trendChartLegends = new TrendChartLegends(this);
    Trace.send(1, traceKey, i18nTrace, "tcNullConstructor");
    defaultConnectorFormat = new DefaultConnectorFormat(this);
    defaultMarkerFormat = new DefaultMarkerFormat(this);
    defaultValueAxis = new DefaultValueAxis(this);
    // NOTE: it is important to do the plot last, as it turns
    // around and gets the three previous slots
    defaultTrendChartPlot = new DefaultTrendChartPlot(this);
  }

  /** The "full featured" constructor. */
  public TrendChart(Container parent,
		    com.gensym.classes.TrendChart g2TrendChart,
		    Rectangle initialBounds, ChartLabel title,
		    //DataWindow dataAndLabelWindow,
		    DataAndLabelWindow dataAndLabelWindow,
		    TimeAxis timeAxis,
		    Color outerBackgroundColor,
		    boolean outerBorderVisible,
		    Color outerBorderColor,
		    boolean legendVisible,
		    String legendPosition,
		    boolean titleVisible,
		    String titlePosition) {
    this();

    this.g2TrendChart = g2TrendChart;

    timeAxis.configure(this);
    int initialWidth = initialBounds.width,
      initialHeight = initialBounds.height;
    this.title = title;
    title.setVisible(titleVisible);
    add(title);
    //this.dataWindow = dataWindow;
    this.dataWindow = dataAndLabelWindow.dataWindow;
    dataWindow.setChart(this);
    this.timeAxis = timeAxis;
    //TimeLabels timeLabels = new TimeLabels(timeAxis, dataWindow);
    this.dataAndLabelWindow = dataAndLabelWindow;
    //dataAndLabelWindow = new DataAndLabelWindow(dataWindow, timeLabels);
    dataAndLabelWindow.setTrendChart(this);
    add(dataAndLabelWindow);

    setOuterBackgroundColor(outerBackgroundColor);
    this.outerBorderVisible = outerBorderVisible;
    this.outerBorderColor = outerBorderColor;
    this.legendPosition = legendPosition;
    this.titlePosition = titlePosition;
    
    parent.add(this);
    
    trendChartLegends.setSize(initialWidth, 0);
    trendChartLegends.setVisible(legendVisible);
    add(trendChartLegends);

    relativeTimeLabels =
      new RelativeTimeLabels(this, dataAndLabelWindow);
    add(relativeTimeLabels);
    layoutManager =
      new ChartLayoutManager(this, title, 
			     titlePosition, dataAndLabelWindow,
			     timeAxis, trendChartLegends,
			     relativeTimeLabels);
    setLayout(layoutManager);
    setSize(initialWidth, initialHeight);

    setVisible(true);
    dataAndLabelWindow.setVisible(true);
  }

  void addLegend(TrendChartLegend legend) {
    trendChartLegends.add(legend);
  }

  void invalidateDataWindow() {
    if (dataWindow != null)
      dataWindow.invalidate();
  }

  public void repaintDataAndLabelWindow() {
    dataAndLabelWindow.repaintAll();
  }

  public void acknowledgeNewData(long firstTimestamp, long lastTimestamp) {
    if (lastTimestamp > timeAxis.getEndTime()) {
      timeAxis.adjustEndTime(lastTimestamp);
    }
    double timeScale = timeAxis.getScale();
    long timeOffset = (long)timeAxis.getDataOrigin();
    Rectangle windowBounds = dataWindow.getBounds();
    int windowLeft = windowBounds.x;

    int startX =
      (int)Math.floor((firstTimestamp - timeOffset) * timeScale) +
      windowLeft;
    int endX = 
      (int)Math.floor((lastTimestamp - timeOffset) * timeScale) +
      windowLeft;

    if (traceOn) {
      Trace.send(10, traceKey, i18nTrace, "tcpacknowledgeNewData0",
		 new Long(firstTimestamp), new Long(lastTimestamp));
      Trace.send(10, traceKey, i18nTrace, "tcpacknowledgeNewData1",
		 new Double(timeScale), new Long(timeOffset),
		 windowBounds);
      Trace.send(10, traceKey, i18nTrace, "tcpacknowledgeNewData2",
		 new Integer(startX), new Integer(endX));
    }

    dataAndLabelWindow.repaintSlice(startX, endX);
  }

  void acknowledgeLayoutChange() {
    invalidate();
    validate();
  }

  public void setTitle(String titleText) {
    title.setText(titleText);
    acknowledgeLayoutChange();
  }

  public void setTrendChartLabelColor(Color color) {
    title.setTextColor(color);
  }

  private static final Symbol absolute_ = Symbol.intern("ABSOLUTE");
  private static final Symbol legendColorType_ =
  Symbol.intern("LEGEND-COLOR-TYPE");

  /** Adaptor method for G2 */
  public void setLegendColor (Structure newValue)
  throws NoSuchAttributeException {
    if (newValue == null) {
      setLegendColor(Color.black);
      setLegendColorType(MATCHING_PLOT_COLOR_);
    } else {
      setLegendColor(G2ColorMap.get(newValue, color_, getForeground()));
      setLegendColorType((Symbol)newValue.getAttributeValue(legendColorType_, MATCHING_PLOT_COLOR_));
    }
    trendChartLegends.resetLegendTexts();
    invalidate();
  }

  public void setLegendColor(Color newColor) {
    trendChartLegends.setForeground(newColor);
  }

  public Color getLegendColor() {
    return trendChartLegends.getForeground();
  }

  public void setLegendColorType(Symbol colorType) {
    this.colorType = colorType;
  }

  public Symbol getLegendColorType() {
    return colorType;
  }

  public void setLegendVisible(boolean yes) {
    if(!(trendChartLegends.isVisible() == yes)) {
      trendChartLegends.setVisible(yes);
      acknowledgeLayoutChange();
    }
  }

  public boolean getLegendVisible() {
    return trendChartLegends.isVisible();
  }

  public void setLegendPosition(String position) {
    if(legendPosition != null || !legendPosition.equals(position)) {
      legendPosition = position;
      acknowledgeLayoutChange();
    }
  }

  public String getLegendPosition() {
    return legendPosition;
  }

  // performance: this goes to all legends and resets
  // the text. It could be more intelligent about it
  // and only reset those that have changed, based on whether
  // the ChartElement affects the plot in question (i.e., is either
  // the MarkerFormat or the ConnectorFormat for that plot.
  void resetLegendText(ChartElement element) {
    for (Enumeration en = getTrendChartPlots();en.hasMoreElements();) {
      TrendChartPlot plot = (TrendChartPlot)en.nextElement();
      plot.resetLegendText(element);
    }
  }
  public void setTitleVisible(boolean yes) {
    title.setVisible(yes);
    acknowledgeLayoutChange();
  }

  public boolean getTitleVisible() {
    return title.isVisible();
  }

  public void setTitleColor(Color newColor) {
    title.setTextColor(newColor);
    title.setForeground(newColor);
  }

  public Color getTitleColor() {
    return title.getTextColor();
  }

  public void setTitlePosition(String position) {
    if(titlePosition != null || !titlePosition.equals(position)) {
      titlePosition = position;
      layoutManager.setTitlePosition(position);
      acknowledgeLayoutChange();
    }
  }

  public String getTitlePosition() {
    return titlePosition;
  }

  public void setOuterBackgroundColor(Color color) {
    setBackground(color);
    title.setBackground(color);
    repaint();
  }

  public Color getOuterBackgroundColor() {
    return getBackground();
  }

  public void setOuterBorderColor(Color color) {
    outerBorderColor = color;
    repaint();
  }

  public void setOuterBorderVisible(Boolean yes) {
    outerBorderVisible = yes.booleanValue();
    repaint();
  }

  public void setDataWindowBackgroundColor(Color color) {
    dataAndLabelWindow.setBackground(color);
  }

  public Color getDataWindowBackgroundColor() {
    return dataAndLabelWindow.getBackground();
  }

  public void setDataWindowBorderColor(Color color) {
    dataAndLabelWindow.setBorderColor(color);
  }

  public Color getDataWindowBorderColor() {
    return dataAndLabelWindow.getBorderColor();
  }

  public void setDataWindowBorderVisible(boolean yes) {
    dataAndLabelWindow.setBorderVisible(yes);
  }

  public boolean getDataWindowBorderVisible() {
    return dataAndLabelWindow.getBorderVisible();
  }

  @Override
  public void paint (Graphics g) {
    Trace.send(10, traceKey, i18nTrace, "tcboundsClip",
	       this, g.getClipBounds(), getBounds());
    
    Point p = getLocation();
    Rectangle bounds = getBounds();
    int x = p.x;
    int y = p.y;
    int width =  bounds.width;
    int height =  bounds.height;
    int lineWidth = 1;
    Color outerBackgroundColor = getOuterBackgroundColor();
    Trace.send(5, traceKey, i18nTrace, "TcOuter", outerBackgroundColor,
	       outerBorderColor, new Integer(x), new Integer(y));
    if (outerBackgroundColor != G2ColorMap.TRANSPARENT) {
      g.setColor(outerBackgroundColor);
      g.fillRect(x, y, width, height);
    }

    // just checking...
    super.paint(g);

    if(outerBorderVisible) {
      g.setColor(outerBorderColor);
      g.drawRect(x, y, width - lineWidth, height - lineWidth);
    }
  }

  public synchronized void addTrendChartPlot(TrendChartPlot plot) {
    plots.add(plot);
    trendChartLegends.add(plot.getTrendChartLegend());
    acknowledgeLayoutChange();
  }

  void removeTrendChartPlot (TrendChartPlot plot) {
    plots.remove(plot);
    trendChartLegends.remove(plot.getTrendChartLegend());
    acknowledgeLayoutChange();
  }
  
  public Enumeration getTrendChartPlots() {
    return plots.elements();
  }

  TrendChartPlot getControllingPlotForValueAxis(ValueAxis axis) {
    int size = plots.size();
    for (int i = 0; 1 < size; i++) {
      TrendChartPlot plot = (TrendChartPlot)plots.elementAt(i);
      if (axis.equals(plot.getValueAxis())) {
	return plot;
      }
    }
    return null;
  }

  public TimeAxis getTimeAxis() {
    return timeAxis;
  }

  public void setTimeAxis(TimeAxis timeAxis) {
    this.timeAxis = timeAxis;
  }

  public void addValueAxes(Enumeration axes) {
    valueAxes.union(axes);
    Trace.send(20, traceKey, i18nTrace, "addValueAxes", valueAxes);
    invalidate();
  }

  public ValueAxis getValueAxis(Object id) {
    return (ValueAxis)getChartElement(id, valueAxes);
  }

  public Enumeration getValueAxes() {
    return valueAxes.elements();
  }

  /**
   * What adjustment is applied to the top of the data window
   * to take into account the fact that the valueLabels cannot
   * be chopped off.
   */
  // right now, all ValueLabels use the same font, so only one
  // of them need be asked.
  public int getDataWindowTopAdjustment() {
    if (valueAxes.size() == 0)
      return 0;
    else
      return ((ValueAxis)valueAxes.firstElement()).getValueLabels().getLabelAscent()/2;
  }

  public int getValueAxesCount() {
    return valueAxes.size();
  }

  public ValueAxis getValueAxisByUid(Object uid) {
    return (ValueAxis)getByUid(uid, valueAxes);
  }

  public void removeValueAxis(ValueAxis axis) {
    valueAxes.remove(axis);
    acknowledgeLayoutChange();
  }
  
  public static final Symbol lowValue_ = Symbol.intern("LOW-VALUE");
  public static final Symbol highValue_ = Symbol.intern("HIGH-VALUE");

  public void processValueAxisExtrema(Sequence extremaSequence) {
    try {
      ValueAxis valueAxis;
      Structure extrema;
      Object uid;
      double lowValue, highValue;
      for (Enumeration en = extremaSequence.elements(); en.hasMoreElements();) {
	extrema = (Structure)en.nextElement();
	uid = extrema.getAttributeValue(chartElementUid_);
	lowValue = ((Number)extrema.getAttributeValue(lowValue_)).doubleValue();
	highValue = ((Number)extrema.getAttributeValue(highValue_)).doubleValue();
	valueAxis = (ValueAxis)getByUid(uid, valueAxes);
	valueAxis.setDataRange(lowValue, highValue);
      }

      dataWindow.invalidate();
    } catch (NoSuchAttributeException nsae) {
      nsae.printStackTrace();
    }
  }

  public Enumeration getVerticalAxes() {
    return valueAxes.elements();
  }

  public void addConnectorFormats(Enumeration connectors) {
    connectorFormats.union(connectors);
  }

  public void removeConnectorFormat(ConnectorFormat format) {
    connectorFormats.remove(format);
  }

  public void addChartElement(ConnectorFormat format) {
    connectorFormats.add(format);
  }

  public void addChartElement(MarkerFormat format) {
    markerFormats.add(format);
  }

  public void addChartElement(ValueAxis axis) {
    valueAxes.add(axis);
    acknowledgeLayoutChange();
  }

  public void addChartElement(TrendChartPlot plot) {
    plots.add(plot);
  }

  public void addMarkerFormats(Enumeration markers) {
    markerFormats.union(markers);
  }

  void removeMarkerFormat(MarkerFormat format) {
    markerFormats.remove(format);
  }

  private Object getByName(Symbol name, Set set) {
    Trace.send(20, traceKey, i18nTrace, "tcgetByName", name);
    for (Enumeration things = set.elements();
	 things.hasMoreElements();) {
      ChartElement thing = (ChartElement)things.nextElement();
      for (Enumeration en = thing.getNames(); en.hasMoreElements();) {
	Object currentName = en.nextElement();
	Trace.send(20, traceKey, i18nTrace, "tcgetByName2", currentName);
	if (name.equals(currentName))
	  return thing;
      }
    }

    return set.firstElement();
  }
    
  private Object getChartElement(Object id, Set set) {
    Trace.send(20, traceKey, i18nTrace, "tcgetChartElement",
	       set, id);
    //System.out.println("Object=" + id + ";class=" + id.getClass());
    Object returnValue = null;
    if (id instanceof Symbol)
      returnValue = getByName((Symbol)id, set);
    else if (id instanceof Integer) {
      int idInt = ((Integer)id).intValue();
      if (idInt > set.size())
	return set.firstElement();
      else
	returnValue = set.elementAt(idInt - 1);
    }
    else if (id == null)
      returnValue = set.firstElement();
    else throw new IllegalArgumentException();
    Trace.send(20, traceKey, i18nTrace, "tcgetChartElement2",
	       returnValue);
    return returnValue;
  }

  public ConnectorFormat getConnectorFormat(Object id) {
    return (ConnectorFormat)getChartElement(id, connectorFormats);
  }

  public MarkerFormat getMarkerFormat(Object id) {
    return (MarkerFormat)getChartElement(id, markerFormats);
  }

  private Object getByUid(Object uid, Set set) {
    Trace.send(20, traceKey, i18nTrace, "tcgetByUid", uid);
    for (Enumeration things = set.elements();
	 things.hasMoreElements();) {
      ChartElement thing = (ChartElement)things.nextElement();
      if (thing.getChartElementUid().equals(uid))
	return thing;
    }

    return set.firstElement();
  }
    

  @Override
  public DataWindow getDataWindow() {
    return dataWindow;
  }

  // default instances of things

  public ChartElement getDefault(Class slotClass) {
    if (ConnectorFormat.class.isAssignableFrom(slotClass))
      return getDefaultConnectorFormat();
    else if (MarkerFormat.class.isAssignableFrom(slotClass))
      return getDefaultMarkerFormat();
    else if (ValueAxis.class.isAssignableFrom(slotClass))
      return getDefaultValueAxis();
    else if (TrendChartPlot.class.isAssignableFrom(slotClass))
      return getDefaultTrendChartPlot();
    else throw new IllegalArgumentException(i18n.format("tcUnknownDefaultClass",
						   slotClass));
  }

  public DefaultConnectorFormat getDefaultConnectorFormat() {
    return defaultConnectorFormat;
  }

  public DefaultMarkerFormat getDefaultMarkerFormat() {
    return defaultMarkerFormat;
  }

  public DefaultValueAxis getDefaultValueAxis() {
    return defaultValueAxis;
  }

  public DefaultTrendChartPlot getDefaultTrendChartPlot() {
    return defaultTrendChartPlot;
  }

  private boolean isActive = false;
  
  /** Called when the trend chart in G2 is disabled, or when G2 is reset.
   * clears all the history, and sets the TrendChart as inactive.
   * Information as to whether the chart is active or not is used only
   * at paint time.*/
  public synchronized void setActive(boolean yes) {
    Trace.send(10, traceKey, i18nTrace, "tcsetActive", new Boolean(yes));
    if (isActive && !yes)
      deactivate();
    else if (yes && !isActive)
      activate();
    isActive = yes;
  }

  public boolean getActive() {
    return isActive;
  }

  private void activate() {
  }

  private void deactivate() {
    repaint();
  }

  public Structure getIcon(Symbol className) throws G2AccessException {
    return ((com.gensym.classes.TrendChartImpl)g2TrendChart).getIcon(className);
  }

  public void setCurrentTime(long currentTime) {
    long oldTime = this.currentTime;
    this.currentTime = currentTime;
    acknowledgeNewData(oldTime, currentTime);
  }

  long getCurrentTime() {
    return currentTime;
  }
}
