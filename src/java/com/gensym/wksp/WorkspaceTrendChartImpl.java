
package com.gensym.wksp;

import com.gensym.util.*;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.util.symbol.G2TypeSymbols;
import com.gensym.core.DebugUtil;
import com.gensym.message.*;
import com.gensym.ntw.*;
import com.gensym.ntw.util.G2ColorMap;
import com.gensym.ntw.util.G2FontMap;
import com.gensym.ntw.util.TrendChartListener;
import com.gensym.ntw.util.TrendChartEvent;
import com.gensym.draw.*;
import com.gensym.displays.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2CommunicationErrorEvent;
import com.gensym.classes.Item;

import java.util.*;
import java.awt.*;
import java.lang.reflect.*;

/** Handles the translating of G2 structure information into generic chart
 * information. Controls the subscription to the corresponding G2 trend chart,
 * controls the moving/sizing apsect of the chart within the workspace and
 * passes on relevant workspace and trend-chart events to the underlying
 * chart.
 */
public class WorkspaceTrendChartImpl extends Container
implements TrendChartListener, WorkspaceTrendChart, DrawElement,
  com.gensym.util.symbol.TrendChartSymbols
{
  public static boolean traceOn = false;
  // mirrors the lisp: actually used only for HEIGHT.
  static public final int MINIMUM_DATA_WINDOW_SIZE = 20;
  static private final Resource i18n =
  Resource.getBundle("com.gensym.resources.WorkspaceMessages");

  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.wksp", WorkspaceTrendChartImpl.class);
  private static MessageKey messageKey = traceKey;

  // Symbols for lookup
  // housekeeping
  static private MessageKey traceWksp =
  Trace.registerMessageKey("com.gensym.wksp",
			   WorkspaceTrendChartImpl.class);
  static private Resource i18nTrace =
  Trace.getBundle("com.gensym.wksp.TraceMessages");

  static private MessageKey traceDraw =
  Trace.registerMessageKey("com.gensym.draw", WorkspaceTrendChartImpl.class);

  static private final TextStyle DEFAULT_TITLE_STYLE =
  new TextStyle(G2FontMap.HM14, 0, 0, 2);

  private static final Symbol ELEMENT_TYPE_ = Symbol.intern ("ELEMENT-TYPE");
  private static final Symbol ELEMENT_DATA_ = Symbol.intern ("ELEMENT-DATA");
  private static final Symbol LEGEND_COLOR_ = Symbol.intern ("LEGEND-COLOR");

  //
  // real instance variables
  //

  private WorkspaceView workspace;
  private PersistentCanvas canvas;
  private TrendChart chartView;
  private com.gensym.classes.TrendChart g2TrendChart;
  private boolean invalidElement = false;
  private Exception initializationException;
  private WorkspaceElementHelper helper;

  //
  // For DrawElement
  //
  protected Rectangle[] bounds;

  public WorkspaceTrendChartImpl(Item item, WorkspaceView parent)
  throws G2AccessException {
    initializeFont();
    this.helper = new WorkspaceElementHelper(this,
					     this,
					     this,
					     item,
					     parent);
    bounds = WorkspaceElementHelper.getExactBounds(item);
    Trace.send(10, traceKey, i18nTrace, "wtcBounds", bounds[0]);
    canvas = parent;
    g2TrendChart = (com.gensym.classes.TrendChart)item;
    setLayout(new BorderLayout());
    setBounds(bounds[0]);
    //initializeChart();
    parent.add(this);
    try {
      synchronized (this) {
	g2TrendChart.addItemListener(this);
	g2TrendChart.addTrendChartListener(this);
	initializeChart();
	
	finishConfiguration();
      }
    } catch (Exception ex) {
      invalidElement = true;
      initializationException = ex;
      ex.printStackTrace();
    }
    //validateTree();
    //parent.invalidateElement(this);
    //getLayout().layoutContainer(this);
  }

  /** Hardcodes G2FontMap.HM14.
   */
  private void initializeFont() {
    setFont(G2FontMap.HM14);
  }

  private synchronized void initializeChart() {
    // super.initialize();
    Dimension chartSize = new Dimension(bounds[0].width, bounds[0].height);
	       
    try {
      Structure format = g2TrendChart.getTrendChartFormat();
      
      Trace.send(10, traceKey, i18nTrace, "wtcStartingChart", format);

      Color outerBackgroundColor =
	G2ColorMap.get(format, OUTER_BACKGROUND_COLOR_, G2ColorMap.TRANSPARENT);
      
      String titleString = g2TrendChart.getTitle();

      ChartLabel title = 
	new ChartLabel(new Dimension(bounds[0].width, 0),
		       chartSize,
		       true,
		       titleString,
		       DEFAULT_TITLE_STYLE,
		       TextCell.CENTER,
		       outerBackgroundColor,
		       G2ColorMap.get(format, TITLE_COLOR_,
				      Color.black),
		       0,
		       outerBackgroundColor);
      
      Trace.send(10, traceKey, i18nTrace, "wtcMakingDataWindow",
		 G2ColorMap.get(format,
				DATA_WINDOW_BACKGROUND_COLOR_,
				outerBackgroundColor));
      DataAndLabelWindow dataAndLabelWindow =
	new DataAndLabelWindow(chartSize,
		       null, // no opinion on minimum for now
		       format.getBoolean(DATA_WINDOW_BORDER_VISIBLEQ_),
		       G2ColorMap.get(format,
				      DATA_WINDOW_BACKGROUND_COLOR_,
				      outerBackgroundColor),
		       G2ColorMap.get(format,
				      DATA_WINDOW_BORDER_COLOR_,
				      getForeground()));
      
      timeAxis = new TimeAxis(dataAndLabelWindow);
      if (traceOn)
	Trace.send(10, traceKey, i18nTrace, "wtcTimeAxisData",
		   g2TrendChart.getTimeAxis());
      configureCompoundSlot(g2TrendChart.getTimeAxis(),
			    timeAxis);
      
      // adjustTimeBounds((Structure)specificInfo.
      //	       getAttributeValue(timespan_));
      
      Trace.send(10, traceKey, i18nTrace, "wtcMakingChart",
		 new Boolean(format.getBoolean(TITLE_VISIBLE_Q_)));
      chartView =
	new TrendChart(this, g2TrendChart, bounds[0], title, dataAndLabelWindow, timeAxis,
		       outerBackgroundColor,
		       format.getBoolean(OUTER_BORDER_VISIBLEQ_),
		       G2ColorMap.get(format, OUTER_BORDER_COLOR_,
				      Color.black),
		       format.getBoolean(LEGEND_VISIBLEQ_),
		       ((Symbol)format.getAttributeValue(LEGEND_POSITION_)).
		       toString(),
		       format.getBoolean(TITLE_VISIBLE_Q_),
		       ((Symbol)format.getAttributeValue(TITLE_POSITION_)).
		       toString());

      chartView.setLegendColor((Structure)format.getAttributeValue(LEGEND_COLOR_));

      add(chartView, BorderLayout.CENTER);
      
      configureChart();

      // this is synchronized in order to give the trend chart enough
      // time to finish processing the data collected by addTrendChartListener
      // before is has to start processing events from the g2 trend chart
    } catch (Exception ex) {
      invalidElement = true;
      initializationException = ex;
      ex.printStackTrace();
      return;
    }
  }

  // fix this: This may end up duplicating some of the work done
  // during configureChart()
  private void finishConfiguration() throws NoSuchAttributeException {
    boolean active = g2TrendChart.getActivationState();
    setTrendChartActive(active);

    chartView.setCurrentTime(g2TrendChart.getLastUpdateTime());

    if (active) {
      Structure timespanInfo = g2TrendChart.getTimespan();
      adjustTimeBounds(timespanInfo);
      
      //adjustPlotBuffers();
      
      Sequence extremaInfo = g2TrendChart.getValueAxisExtrema();
      Trace.send(10, traceKey, i18nTrace, "wtcextremaInfo", extremaInfo);
      adjustValueAxisExtrema(extremaInfo);
      
      Sequence initialData = g2TrendChart.getInitialData();
      Trace.send(10, traceKey, i18nTrace, "wtcinitialData",
		 this, initialData);
      processPlotData(initialData);
    }
    validate();
    canvas.invalidateElement(this);
    chartView.repaintDataAndLabelWindow();
    //canvas.invalidate(getExactBounds());
  }

  private static final Symbol CONNECTOR_FORMATS_ =
  Symbol.intern("CONNECTOR-FORMATS");
  private static final Symbol pointFormats_ =
  Symbol.intern("POINT-FORMATS");
  private static final Symbol TIME_AXIS_ = Symbol.intern("TIME-AXIS");
  private static final Symbol VALUE_AXES_ = Symbol.intern("VALUE-AXES");
  private static final Symbol trendChartPlots_ =
  Symbol.intern("TREND-CHART-PLOTS");

  // Should be Vectors! for things like point-format-name-or-number
  private Vector connectors = new Vector();
  private Vector pointFormats = new Vector();
  private Vector valueAxes = new Vector();
  private Vector trendChartPlotVector = new Vector();
  private TimeAxis timeAxis;

  /** adds the plots, connectorFormats, markerFormats, and axes to
   * the chart. */
  private void configureChart()
  throws G2AccessException, NoSuchAttributeException {
    Sequence slots = g2TrendChart.getConnectorFormats();
    Trace.send(20, traceKey, i18nTrace, "wtcconfigureConnectors", slots);
    configureMultipleCompoundSlots(slots,
				   ConnectorFormat.class,
				   connectors);
    chartView.addConnectorFormats(connectors.elements());
    
    slots = g2TrendChart.getPointFormats();
    Trace.send(20, traceKey, i18nTrace, "wtcconfigurePointFormats", slots);
    configureMultipleCompoundSlots(slots,
				   MarkerFormat.class,
				   pointFormats);
    chartView.addMarkerFormats(pointFormats.elements());
    
    slots = g2TrendChart.getValueAxes();
    Trace.send(20, traceKey, i18nTrace, "wtcconfigureValueAxes", slots);
    configureMultipleCompoundSlots(slots,
				   ValueAxis.class,
				   valueAxes);
    chartView.addValueAxes(valueAxes.elements());

    slots = g2TrendChart.getPlots();
    Trace.send(20, traceKey, i18nTrace, "wtcconfigurePlots", slots);
    configureTrendChartPlots(slots);
    Trace.send(20, traceKey, i18nTrace, "wtcfinishedConfigureChart");
    rescaleAxes();
  }

  private void rescaleAxes() {
    timeAxis.rescale();
    for (Enumeration en = valueAxes.elements(); en.hasMoreElements();) {
      ((ValueAxis)en.nextElement()).rescale();
    }
  }

  private void configurePoints(Structure info) {
  }

  private void configureTimeAxis(Structure info) {
  }

  private void configureValueAxes(Structure info) {
  }

  private static final Symbol NAMES_ = Symbol.intern("NAMES");

  private static final Hashtable contructorTable = new Hashtable(11);
  
  private static Class getClassForSlot(Symbol attrName_) {
    if (PLOTS_.equals(attrName_))
      return TrendChartPlot.class;
    if (CONNECTOR_FORMATS_.equals(attrName_))
      return ConnectorFormat.class;
    if (POINT_FORMATS_.equals(attrName_))
      return MarkerFormat.class;
    if (VALUE_AXES_.equals(attrName_))
      return ValueAxis.class;
    if (TIME_AXIS_.equals(attrName_))
      return TimeAxis.class;
    return null;
  }
    
  private Constructor findChartElementConstructor(Class slotClass)
  throws NoSuchMethodException{
    Constructor constructor = (Constructor)contructorTable.get(slotClass);

    if (constructor == null) {
      constructor =
	slotClass.getConstructor(new Class[]
				 {com.gensym.displays.TrendChart.class,
				    com.gensym.classes.TrendChart.class,
				    Object.class});
      contructorTable.put(slotClass, constructor);
    }

    return constructor;
  }
    

  /** Creates, configures, and stores objects based on a sequence of
   * structures that describe the objects.
   */
  public void configureMultipleCompoundSlots(Sequence infos,
					     Class slotClass,
					     Vector storage)
  throws NoSuchAttributeException {
    try {
      for (Enumeration structs = infos.elements();
	   structs.hasMoreElements();) {
	Structure struct = (Structure)structs.nextElement();
	// filter out the default example of a slot.
	Object names = struct.getAttributeValue(NAMES_, null);
	//	Object obj = slotClass.newInstance();

	Object obj = null;
	if (DEFAULT_.equals(names)) {
	  obj = chartView.getDefault(slotClass);
	} else {
	  Constructor constructor = findChartElementConstructor(slotClass);
	  Object uid = struct.getAttributeValue (CHART_ELEMENT_UID_, null);
	  obj =
	    constructor.newInstance(new Object[]
				    {chartView, g2TrendChart, uid});
	  storage.addElement(obj);
	}

	configureCompoundSlot(struct, obj);
      }
    } catch (Exception ex) {
      ex.printStackTrace(); // fix this: handle properly
    }
  }

  /** Currently calls the property setters one-by-one. This is slow
   * and should be replace by a technique based on a full-featured
   * constructor */
  public void configureCompoundSlot(Structure struct, Object obj)
  {
    try {
      for (Enumeration en = struct.getAttributeNames();
	   en.hasMoreElements();) {
	Symbol attrName = (Symbol)en.nextElement();
	if (!CHART_ELEMENT_UID_.equals(attrName)) // read-only special slot!
	  dispatchSlotMethod(obj, attrName,
			     struct.getAttributeValue(attrName));
      }
      ((ChartElement)obj).configure(chartView);
    } catch (Exception ex) {
      ex.printStackTrace(); // fix this: handle properly
    }
  }

  private Hashtable trendChartPlots = new Hashtable();

  private static Symbol plotIndex_ = Symbol.intern("PLOT-INDEX");
  private static Symbol plotData_ = Symbol.intern("PLOT-DATA");
  Integer plotIndex;

  private static Symbol extraSlots_ = Symbol.intern("EXTRA-SLOTS");
  private static Symbol normalSlots_ = Symbol.intern("NORMAL-SLOTS");

  private void configureTrendChartPlots(Sequence infos)
  throws NoSuchAttributeException {
    try {
      // Using better means to get layering correct
      for (int i = 0; i < infos.size(); i++) {
	Structure plotStruct = (Structure)infos.elementAt(i);
	TrendChartPlot plot;
	Object names = plotStruct.getAttributeValue(NAMES_, null);
	Object plotUid =
	  plotStruct.getAttributeValue(CHART_ELEMENT_UID_);
	
	if (DEFAULT_.equals(names)) {
	  plot = chartView.getDefaultTrendChartPlot();
	  configureCompoundSlot(plotStruct, plot);
	} else {
	  plot = new TrendChartPlot(chartView, g2TrendChart, plotUid);
	  trendChartPlots.put(plotUid, plot);
	  trendChartPlotVector.addElement(plot);
	  configureCompoundSlot(plotStruct, plot);
	  chartView.addTrendChartPlot(plot);
	  //storePlot(plotUid, plot);
	}
	Trace.send(10, traceKey, i18nTrace, "wstcPlot", plot, plotUid);
      }
    } catch (Exception ex) {
      ex.printStackTrace(); // fix this: handle properly
    }
  }


  private void storePlot(Object plotUid, TrendChartPlot plot) {
    trendChartPlots.put(plotUid, plot);
    trendChartPlotVector.addElement(plot);
    chartView.addTrendChartPlot(plot);
  }

  private static final Symbol NEW_TIMESPAN_ = Symbol.intern("NEW-TIMESPAN");
  private void adjustTimeBounds(Structure timespanInfo){
    Trace.send(20, traceKey, i18nTrace, "wtcadjustTimeBounds", timespanInfo);
    if (timespanInfo == null)
      return;
    try {
      Number spanVal =
	(Number)timespanInfo.getAttributeValue(TIMESPAN_);
      Number endVal =
	(Number)timespanInfo.getAttributeValue(END_TIME_);

      TimeAxis timeAxis = chartView.getTimeAxis();
      long span = spanVal.longValue() * 1000;
      long end = endVal.longValue() * 1000;
      timeAxis.adjustTimeBounds(end, span);
    } catch (NoSuchAttributeException nsae) {
      Trace.exception(nsae);
    }
    chartView.repaintDataAndLabelWindow();
    // fix this: quick hack to improve appearance of redraw.
    canvas.invalidateElement(this);
    //canvas.invalidate(getExactBounds());
  }

  // a dataBurst is ((value time index)...)
  private static final int TIME_POS = 1;
  private static final int VALUE_POS = 0;
  private static final int DATA_INDEX_POS = 2;

  private static final Symbol NEW_PLOT_DATA_ = Symbol.intern("NEW-PLOT-DATA");
  private static final Symbol CURRENT_G2_TIME_ = Symbol.intern ("CURRENT-G2-TIME");

  private void processDataBurst(Structure newInfo) {
    Trace.send(10, traceKey, i18nTrace, "wtcprocessDataBurst", newInfo);
    Sequence newPlotData = null;
    try {
      newPlotData = (Sequence)newInfo.getAttributeValue(NEW_PLOT_DATA_);
      processPlotData(newPlotData);
      chartView.setCurrentTime((long)(((Number)newInfo.getAttributeValue(CURRENT_G2_TIME_)).doubleValue() * 1000));
    } catch (NoSuchAttributeException nsae) {
      nsae.printStackTrace();
      return;
    }
  }

  // fix this: review synchronization

  private void processPlotData(Sequence plotDataSequence) {
    if (plotDataSequence == null)
      return;

    try {
      int pdsSize = plotDataSequence.size();
      for (int index = 0; index < pdsSize; index++) {
	Structure plotDataInfo = (Structure)plotDataSequence.elementAt(index);
	Structure plotData =
	  (Structure) plotDataInfo.getAttributeValue(PLOT_DATA_);
	
	Object uid = plotDataInfo.getAttributeValue(CHART_ELEMENT_UID_);
	TrendChartPlot plot = (TrendChartPlot)trendChartPlots.get(uid);

	Sequence timestamps =
	  (Sequence)plotData.getAttributeValue(HISTORY_COLLECTION_TIMES_);
	
	Number endTime = (Number)timestamps.lastElement();
	plot.acknowledgeNewData((long)(endTime.doubleValue() * 1000.0));
      }
    } catch (NoSuchAttributeException nsae) {
      throw new CorruptionException(nsae);
    }
  }
  
  private static final Symbol NEW_EXTREMA_ = Symbol.intern("NEW-EXTREMA");
  private static final Symbol LOW_VALUE_ = Symbol.intern("LOW-VALUE");
  private static final Symbol HIGH_VALUE_ = Symbol.intern("HIGH-VALUE");

  private void processValueAxisExtremaEvent(Structure newInfo) {
    Trace.send(10, traceKey, i18nTrace, "wtcprocessValueAxisExtremaEvent",
	       newInfo);
    try {
      Sequence extrema =
	(Sequence)newInfo.getAttributeValue(NEW_EXTREMA_);
      adjustValueAxisExtrema(extrema);
    } catch (NoSuchAttributeException nsae) {
      nsae.printStackTrace();
    } catch (ClassCastException cce) {
      cce.printStackTrace();
    }
  }

  private void adjustValueAxisExtrema(Sequence extrema)
  throws NoSuchAttributeException {
    for (Enumeration en = extrema.elements(); en.hasMoreElements();) {
      Structure extremaPair = (Structure)en.nextElement();
      Object uid =
	extremaPair.getAttributeValue(CHART_ELEMENT_UID_);
      ValueAxis valueAxis =
	DEFAULT_.equals(uid) ?
	(ValueAxis)chartView.getDefault(ValueAxis.class) :
	(ValueAxis)getByUid(uid, valueAxes.elements());
      Number lowValueObj =
	(Number)extremaPair.getAttributeValue(LOW_VALUE_, null);
      if (lowValueObj == null) {
	valueAxis.setDataRangeInvalid();
	continue;
      }
      Number highValueObj =
	(Number)extremaPair.getAttributeValue(HIGH_VALUE_);
      if (valueAxis == null)
	// newly added, will get correct values when itemModified
	// is processed
	return;

      valueAxis.setDataRange(lowValueObj.doubleValue(),
			     highValueObj.doubleValue());
    chartView.repaintDataAndLabelWindow();
    canvas.invalidateElement(this);
    }
  }

  private void processActivationEvent(TrendChartEvent event) {
    Structure info = event.getNewInfo();
    try {
      setTrendChartActive(info.getBoolean(ACTIVATION_VALUE_));
      boolean value = info.getBoolean(ACTIVATION_VALUE_);
    } catch (Exception ex) {
      throw new
	UnexpectedException(ex,
			    i18n.getString("wtcErrorUnpackingActivation"));
    }
  }

  private void setTrendChartActive(boolean yes) {
    if (yes)
      activateTrendChart();
    else
      deactivateTrendChart();
  }

  private boolean trendChartActive;
  private synchronized void activateTrendChart() {
    trendChartActive = true;
    chartView.setActive(true);
  }

  private synchronized void deactivateTrendChart() {
    trendChartActive = false;
    chartView.setActive(false);
    chartView.repaintDataAndLabelWindow();
  }

  public void processWorkspaceEvent(WorkspaceEvent event) {
  }

  private void processClockDiscontinuity(TrendChartEvent event) {
    try {
      Structure newInfo = event.getNewInfo();

      adjustTimeBounds((Structure)newInfo.getAttributeValue(TIMESPAN_INFO_));
      Sequence seq = (Sequence)newInfo.getAttributeValue(INITIAL_PLOT_DATA_, null);
      if (seq != null)
      processPlotData(seq);
    } catch (NoSuchAttributeException nsae) {
      throw new CorruptionException(nsae);
    }
  }

  private final void processGeneralUpdate(Structure newInfo)
  throws NoSuchAttributeException{
    Structure struct = (Structure)newInfo.getAttributeValue(TIME_BOUNDS_, null);
    chartView.setCurrentTime((long)(((Number)newInfo.getAttributeValue(CURRENT_G2_TIME_)).doubleValue() * 1000));

    Trace.send(10, traceKey, i18nTrace, "wtciprocessGeneralUpdate",
	       this, newInfo);

    if (struct != null)
      adjustTimeBounds(struct);

    Sequence seq =
      (Sequence)newInfo.getAttributeValue(VALUE_AXIS_EXTREMA_, null);
    if (seq != null)
      adjustValueAxisExtrema(seq);

     seq = (Sequence)newInfo.getAttributeValue(NEW_PLOT_DATA_, null);
     if (seq != null)
       processPlotData(seq);

    //canvas.invalidateElement(this);
  }

  long previousEventTimestamp = 0;

  /** Translates and dispatches the event to the appropriate
   * trend chart method. Does fairly complicated dispatching based
   * on the notification type and contents of the <code>getNewInfo()</code>
   * structure. */
  @Override
  public void processTrendChartEvent(TrendChartEvent event) {
    Trace.send(10, traceKey, i18nTrace, "ProcessingCompositeEvent", event);

    Structure newInfo = event.getNewInfo();
    
    try {
      switch (event.getID()) {
      case TrendChartEvent.GENERAL_UPDATE:
	processGeneralUpdate(newInfo);
	break;
      case TrendChartEvent.SLOT_CHANGE:
	Trace.send(10, traceKey, i18nTrace, "slotchange");
	// This really where the "complicated dispatching" occurs.
	dispatchSlotChange(event);
	chartView.repaintDataAndLabelWindow();
	break;
      case TrendChartEvent.ACTIVATION:
	Trace.send(10, traceKey, i18nTrace, "wtcactivation");
	processActivationEvent(event);
	break;
      case TrendChartEvent.CLOCK_DISCONTINUITY:
	processClockDiscontinuity(event);
	break;
      case TrendChartEvent.ELEMENT_ADDED:
	processElementAdded(event);
	break;
      case TrendChartEvent.ELEMENT_DELETED:
	processElementDeleted(event);
	break;
      default:
	Trace.send(1, traceKey, i18nTrace, "UnknownEventType");
	//	Message.send(1, messageKey, i18n, "UnknownEventType",
	//                   notificationType);
      }
    } catch (Exception ex) {
      ex.printStackTrace();
      //      Message.send(1, messageKey, i18n "MalformedStructure",
      //	   event.getNewInfo());
    }
    canvas.invalidateElement(this);
    //canvas.invalidate(getExactBounds());
    //repaint();
  }

  private ChartElement getByUid(Object uid, Enumeration things) {
    Trace.send(20, traceKey, i18nTrace, "wtcgetByUid", uid);
    for (; things.hasMoreElements();) {
      ChartElement thing = (ChartElement)things.nextElement();
      Object thingUid = thing.getChartElementUid();
      Trace.send(20, traceKey, i18nTrace, "wtcgetByUid2", uid, thingUid,
		 thing);
      if (thingUid.equals(uid))
	  return thing;
    }

    return null;
  }

  private void removeElementByUid(Vector storage, Object uid) {
    int length = storage.size();
    int index = -1;
    for (int i = 0; i < length; i ++) {
      ChartElement element = (ChartElement)storage.elementAt(i);
      Object elementUid = element.getChartElementUid();
      if (uid.equals(elementUid))
	index = i;
    }
    if (index != -1) {
      ChartElement element = (ChartElement)storage.elementAt(index);
      storage.removeElementAt(index);
      element.dispose();
    }      
  }
    
  private static final Symbol SLOT_NAME_ = Symbol.intern("SLOT-NAME");
  private static final Symbol SLOT_COMPONENT_NAME_ =
  Symbol.intern("SLOT-COMPONENT-NAME");

  /** Provides an automatic mapping from the
   * <code>slot-name/slot-component-name</code> to amthod that will
   * handle the appropriate property change */
  /*  public static registerSlotMapping(Symbol slotName, Symbol slotComponentName,
				    String className, String methodName,
				    Class[] signature,
				    Method slotValueConverter) {
  }
  */

  private static final Symbol PLOTS_ = Symbol.intern ("PLOTS");
  private static final Symbol newValue_ =
  Symbol.intern("NEW-VALUE");
  private static final Symbol CHART_ELEMENT_UID_ =
  Symbol.intern("CHART-ELEMENT-UID");
  private static final Symbol legendColor_ =
  Symbol.intern("LEGEND-COLOR");
  private static final Symbol color_ = Symbol.intern("COLOR");
  private static final Symbol absolute_ = Symbol.intern("ABSOLUTE");
  /** This method translates G2 slot change events into generic chart
   * property changes */
  private void dispatchSlotChange(TrendChartEvent event)
  throws NoSuchAttributeException, Exception {
    Trace.send(10, traceKey, i18nTrace, "wtcdispatchSlotChange", event);
    Structure newInfo = event.getNewInfo();
    Symbol slotName = (Symbol)newInfo.getAttributeValue(SLOT_NAME_);
    Symbol slotComponentName =
      (Symbol)newInfo.getAttributeValue(SLOT_COMPONENT_NAME_);
    Object newValue = newInfo.getAttributeValue(newValue_);
    Object target = null;

    if(TITLE_.equals(slotName)) {
      Trace.send(10, traceKey, i18nTrace, "titleChange");
      chartView.setTitle(newValue.toString());
      // fix this: maybe abstract this out
    } else if(TREND_CHART_FORMAT_.equals(slotName)) {
      Trace.send(10, traceKey, i18nTrace, "formatChange");
      target = chartView;
    } else if(TIME_AXIS_.equals(slotName)) {
      Trace.send(10, traceKey, i18nTrace, "timeAxisChange");
      target = chartView.getTimeAxis();
    } else {
      // NOW the multiple ones
      Enumeration targetEnumeration = null;
      Object chartElementUid = newInfo.getAttributeValue(CHART_ELEMENT_UID_);
      if(CONNECTOR_FORMATS_.equals(slotName)) {
	targetEnumeration = connectors.elements();
      } else if (VALUE_AXES_.equals(slotName)) {
	targetEnumeration = valueAxes.elements();
      } else if (PLOTS_.equals(slotName)) {
	targetEnumeration = trendChartPlots.elements();
      } else if (POINT_FORMATS_.equals(slotName)) {
	targetEnumeration = pointFormats.elements();
      } else {
	System.err.println("UnImplemented slot: " + slotName);
	return;
      }
      target = getByUid(chartElementUid, targetEnumeration);
    }
    try {
      Trace.send(10, traceKey, i18nTrace, "wtcdispatchSlotChange2",
		 target, newValue, (newValue == null ? null :
				    newValue.getClass()));
      dispatchSlotMethod(target, slotComponentName, newValue);
    } catch (InvocationTargetException ite) {
      Throwable te = ite.getTargetException();
      if (te instanceof Exception)
	throw (Exception)te;
      else
	throw new UnexpectedException(te);
    } catch (NoSuchMethodException nsme) {
      throw new UnexpectedException(nsme);
    } catch (IllegalAccessException iae) {
      throw new UnexpectedException(iae);
    }
  }

  /** to speed the lookup for slots */
  private static Hashtable slotMappingClasses = new Hashtable();

  private static Dispatcher dispatcher = new Dispatcher();

  private static final Symbol t_ = Symbol.intern("T");

  /** Translates G2 slot names into beans-like property setters
   * and then invokes them. Is geared towards slots found in trend charts, and
   * makes inferences about argument types based on naming conventions:
   * <code>"TITLE-VISIBLE?"</code> becomes a call to:
   * <code>public void setTitleVisible(boolean g2SlotValue)</code>
   * <p>
   * <code>"OUTER-BACKGROUND-COLOR"</code> becomes
   * <code>public void setOuterBackgroundColor(Color g2SlotValue)</code>
   * <p>
   * of COLOR, <code>g2SlotValue</code> is converted by <code>G2ColorMap</code>.
   * Uses <code>G2ClassTranslator.createJavaClassNameFromG2ClassName</code>.
   * Notice that the Q that is produced by
   * <code>createJavaClassNameFromG2Name</code>
   * is dropped to be more java-like.
   * @see com.gensym.util.Uses G2ClassTranslator.createJavaClassNameFromG2ClassName
   * @see com.gensym.util.G2ColorMap
   */
  public static Object dispatchSlotMethod(Object obj,
					  Symbol g2SlotName,
					  Object g2SlotValue)
  throws NoSuchMethodException, IllegalAccessException,
  InvocationTargetException {
    
    Class objClass = obj.getClass();
    Hashtable slotMapping = (Hashtable)slotMappingClasses.get(objClass);
    if (slotMapping == null) {
      slotMapping = new Hashtable();
      slotMappingClasses.put(objClass, slotMapping);
    }

    String methodName = null;
    Class argClass = String.class; //default

    Method method = (Method)slotMapping.get(g2SlotName);

    if (method == null) {    
      String javaSlotName =
	G2ClassTranslator.slotNameFromG2Slot(g2SlotName.toString());
      
      // fix this: I forget the efficient way to do this:
      methodName = "set" + G2ClassTranslator.initCap(javaSlotName);
      Trace.send(5, traceKey, i18nTrace, "dispatchSlotMethod",
		 obj, g2SlotName, methodName, g2SlotValue);

      
      Class[] argClasses = (g2SlotValue == null ? new Class[] {Object.class} :
                            new Class[] {g2SlotValue.getClass()});
      
      try {
	method = objClass.getMethod(methodName, argClasses);
      } catch (NoSuchMethodException nsme) {
	// fix this: this is OK for now. If the argClass is Symbol,
	// then it might be looking for a method that takes a Color.
	// this will be found by the next call
      }

      //method = dispatcher.findInstanceMethod(methodName, objClass, argClasses);

      method = (method == null ?
		getSetterByName(objClass.getMethods(), methodName) :
		method);
      
      slotMapping.put(g2SlotName, method);
    } else {
      methodName = method.getName();
    }
    
    Class[] parameters = method.getParameterTypes();
    
    if (Color.class.equals(parameters[0])) {
      g2SlotValue = G2ColorMap.get((Symbol)g2SlotValue);
    } else if (g2SlotValue instanceof Symbol &&
	       String.class.equals(parameters[0])) {
      g2SlotValue = g2SlotValue.toString();
    }
    argClass = (g2SlotValue == null ? null : g2SlotValue.getClass());

    Trace.send(10, traceKey, i18nTrace, "beforeMethodInvoke", objClass,
	       methodName, argClass, g2SlotValue);
    Object retVal = null;

    try {
      retVal = method.invoke(obj, new Object[] {g2SlotValue});
    } catch (InvocationTargetException ex) {
      Throwable targetException = ex.getTargetException();
      targetException.printStackTrace();
    } catch (Exception ex) {
      // fix this: should probably let the exception through from here
      // Note that in the finished system, exceptions here due to method
      // dispatch are VERY serious bugs. InvocationTargetException is
      // (sort of) OK.
      Trace.send(1, traceKey, i18nTrace, "InvocationException",
		   methodName,
		   g2SlotValue, g2SlotValue.getClass(), parameters[0]);
      ex.printStackTrace();
    }
    Trace.send(5, traceKey, i18nTrace, "dispatchReturn", methodName, method,
	       retVal);
    return retVal;
  }

  /** The current implementation leads to an n squared algorithm,
   * as it does a linear search of the methods. Since we need to know
   * the argument type, can't look for the method directly. */
  public static Method getSetterByName(Method[] methods, String methodName) {
    for(int i = 0; i < methods.length; i++) {
      if (methodName.equals((methods[i]).getName()))
	return methods[i];
    }
    return null;
  }



  //
  //WORKSPACE ELEMENT API
  //

  @Override
  public void handleWorkspaceItemColorsChanged(WorkspaceEvent event) {
  }

  @Override
  public void handleWorkspaceItemMoved(WorkspaceEvent event) {
    Trace.send(10, traceKey, i18nTrace, "wtchandleWsItemMoved", event);
    helper.shift(event);   
  }

  /**
   * Resizes the DrawElement to the given Rectangle.
   */
  @Override
  public void handleWorkspaceItemResized(WorkspaceEvent event) {
    Trace.send(10, traceKey, i18nTrace, "wtcresize0", event);
    helper.resize(event);
    canvas.invalidateElement(this);
    //canvas.invalidate(getExactBounds());
  }

  @Override
  public void receivedInitialValues (ItemEvent e) {
    Trace.send(30, traceKey, i18nTrace, "wtcreceivedInitialValues", e);
    helper.receivedInitialValues(e);
  }

  private static Symbol getAttributeFromDenotation(Sequence denotation) {
    if (denotation.size() != 1)
      return null;

    Object obj = denotation.firstElement();
    if (!(obj instanceof Structure))
      return null;

    Structure struct = (Structure)obj;
    Symbol type = (Symbol)struct.getAttributeValue(SystemAttributeSymbols.TYPE_, null);
    
    if (!G2TypeSymbols.ATTRIBUTE_.equals(type))
      return null;

    try {
      return (Symbol)struct.getAttributeValue(NAME_);
    } catch (NoSuchAttributeException nsae) {
      throw new CorruptionException(nsae);
    }
  }

  @Override
  public void itemModified (ItemEvent e) {
    Trace.send(10, traceKey, i18nTrace, "wtcitemModified", e);
    Sequence denotation = e.getDenotation();
    Symbol attribute = getAttributeFromDenotation(denotation);
    if (TITLE_.equals(attribute))
      handleTitleChanged((String)e.getNewValue());

    helper.itemModified(e);
  }

  private void handleTitleChanged(String newTitle) {
    chartView.setTitle(newTitle);
  }

  private Vector getCompoundSlotStorage(Symbol slotName) {
    if (slotName == null)
      return null;

    if (PLOTS_.equals(slotName))
      return trendChartPlotVector;
    if (VALUE_AXES_.equals(slotName))
      return valueAxes;
    if (POINT_FORMATS_.equals(slotName))
      return pointFormats;
    if (CONNECTOR_FORMATS_.equals(slotName))
      return connectors;

    return null;
  }

  private void processElementAdded(TrendChartEvent e) {
    Structure info = e.getNewInfo();
    Symbol elementType_ = (Symbol)info.getAttributeValue(ELEMENT_TYPE_, null);
    Structure elementData =
      (Structure)info.getAttributeValue(ELEMENT_DATA_, null);
    Object uid = elementData.getAttributeValue(CHART_ELEMENT_UID_, null);
    Vector storage = getCompoundSlotStorage(elementType_);
    ChartElement newElement =
      createGenericChartElement(elementData, elementType_, uid, storage);
    if (PLOTS_.equals(elementType_))
      trendChartPlots.put(uid, newElement);
    else
      // Some current plots may refer to a slot by number. Sometimes
      // that number may have been too high until this new slot was
      // added. This gives a chance for such plots to be hooked up
      // to the right slot instance. It is up to each plot to notice
      // whether they have been changed in this reconfiguration.
      reconfigureAllPlots(); 
  }    

  private ChartElement createGenericChartElement(Structure elementData,
						 Symbol attrName_,
						 Object uid,
						 Vector storage) {
    Class clazz = getClassForSlot(attrName_);
    try {
      Constructor constructor = findChartElementConstructor(clazz);
      ChartElement element =
	(ChartElement)constructor.newInstance(new Object[]
					      {chartView, g2TrendChart, uid});
      storage.addElement(element);
      configureCompoundSlot(elementData, element);
      addToDisplay(element);
      return element;
    } catch (Exception ex) {
      throw new UnexpectedException(ex);
    }
  }

  // fix this: there can and should be a better way to do this
  private void addToDisplay(ChartElement element) {
    if (element instanceof TrendChartPlot) {
      chartView.addChartElement((TrendChartPlot)element);
    } else if (element instanceof ConnectorFormat) {
      chartView.addChartElement((ConnectorFormat)element);
    } else if (element instanceof ValueAxis) {
      chartView.addChartElement((ValueAxis)element);
    } else if (element instanceof MarkerFormat) {
      chartView.addChartElement((MarkerFormat)element);
    }
  }

  private void reconfigureAllPlots() {
    int length = trendChartPlotVector.size();
    for (int i = 0; i < length; i++) {
      TrendChartPlot plot =
	(TrendChartPlot)trendChartPlotVector.elementAt(i);
      plot.reconfigure();
    }
  }

  private void processElementDeleted(TrendChartEvent e) {
    Structure info = e.getNewInfo();
    Symbol elementType_ = (Symbol)info.getAttributeValue(ELEMENT_TYPE_, null);
    Structure elementData =
      (Structure)info.getAttributeValue(ELEMENT_DATA_, null);
    Object uid = elementData.getAttributeValue(CHART_ELEMENT_UID_, null);
    Vector storage = getCompoundSlotStorage(elementType_);

    removeElementByUid(storage, uid);
    
    if (PLOTS_.equals(elementType_))
      trendChartPlots.remove(uid);
    else
      // Some current plots may refer to a slot by number. Sometimes
      // that number may have been delete.
      // This gives a chance for such plots to be hooked up
      // to the right slot instance. It is up to each plot to notice
      // whether they have been changed in this reconfiguration.
      reconfigureAllPlots(); 
  }

  @Override
  public void itemDeleted (ItemEvent e) {
    helper.itemDeleted(e);
  }

  @Override
  public Item getItem() {
    return helper.getItem();
  }

  @Override
  public void select () {
    helper.select();
  }

  @Override
  public void unselect () {
    helper.unselect();
  }

  @Override
  public boolean isSelected () {
    return helper.isSelected();
  }

  @Override
  public DraggingGhost getDraggingGhost (int left, int top, int width, int height) {
    return helper.getDraggingGhost(left,top,width,height);
  }

  @Override
  public DraggingGhost getDraggingGhost () {
    return helper.getDraggingGhost();
  }
  
  @Override
  public DraggingGhost getDraggingGhost (int markerLocn, int currentX, int currentY) {
    return helper.getDraggingGhost(markerLocn, currentX, currentY);
  }

  @Override
  public PopupMenu getContextMenu () {
    return helper.getContextMenu();
  }

  @Override
  public void paint(Graphics g) {
    if (traceOn)
      Trace.send(10, traceKey, i18nTrace, "wtcpaint1",
		 g.getClipBounds(), getBounds(),
		 DebugUtil.printArray(getExactBounds()));
    super.paint(g);
    if (isCut ()) {
      Rectangle[] exbnds = getExactBounds ();
      Rectangle bnds = exbnds[0];
      helper.paintCutStatus (g, bnds.x, bnds.y, bnds.width, bnds.height);
    }
  }

  //
  // DrawElement
  //

  public void paint (Graphics g, int shift_x, int shift_y)
  {
    System.out.println("paint: " + g + "; shift_x: " + shift_x +
		       "; shift_y: " + shift_y);
  }

  @Override
  public void setCanvas(PersistentCanvas canvas) {
    this.canvas = canvas;
  }
  @Override
  public void changeColor(Object logicalColor, Color color)
  {
  }

  @Override
  public void changeColor(Object logicalColor, Object colorKey)
  {
  }

  @Override
  public Object[] getLogicalColors()
  {
    return null;
  }

  @Override
  public Rectangle[] getExactBounds() {
    return bounds;
  }

  @Override
  public Rectangle getBounds() {
    return bounds[0];
  }

  @Override
  public void shift (int deltaX, int deltaY)
  {
    helper.shift(deltaX,deltaY);
    bounds[0].translate(deltaX, deltaY);
    Point location = getLocation();
    setLocation(location.x + deltaX, location.y + deltaY);
    //super.shift(deltaX, deltaY);
    Trace.send(10, traceKey, i18nTrace, "wtcshift",
	       getBounds(), DebugUtil.printArray(getExactBounds()),
	       new Point (deltaX, deltaY));
  }

  @Override
  public boolean inside(int logical_x, int logical_y)
  {
    return contains(logical_x, logical_y);
  }

  @Override
  public boolean contains(int x, int y)
  {
    return helper.contains(x,y);
  }

  /** This method needs to be overriden, as <code>validate</code>
   * must be called when the size has changed.
   */
  @Override
  public void setBounds(int x, int y, int width, int height) {
    this.bounds[0].x = x;
    this.bounds[0].y = y;
    bounds[0].width = width;
    bounds[0].height = height;
    super.setBounds(x, y, width, height);
     if (!isValid())
       validate();
  }

  @Override
  public void repaint(long tm, int x, int y, int width, int height) {
    super.repaint(tm, x, y, width, height);
  }
  @Override
  public boolean isCut () {
    return helper.isCut ();
  }

  @Override
  public void setCut (boolean newCutState) {
    helper.setCut (newCutState);
    repaint ();
  }

  @Override
  public void dispose() throws G2AccessException{
    g2TrendChart.removeTrendChartListener(this);
    g2TrendChart.removeItemListener(this);
  }
}


