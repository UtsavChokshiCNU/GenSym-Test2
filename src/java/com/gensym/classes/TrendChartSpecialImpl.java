/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TrendChartSpecialImpl.java
 *
 *  Description:
 *               Interface for trend chart events
 *
 *	 Author:
 *		Robert Penny		Aug/97
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.classes;

import java.util.Hashtable;
import java.util.Enumeration;
import java.lang.reflect.Constructor;
import com.gensym.ntw.util.TrendChartEventMulticaster;
import com.gensym.ntw.util.TrendChartEvent;
import com.gensym.ntw.util.TrendChartListener;
import com.gensym.util.ItemEvent;
import com.gensym.util.Denotation;
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
import com.gensym.message.Trace;
import com.gensym.message.Resource;

public class TrendChartSpecialImpl extends TrendChartImpl
implements com.gensym.util.symbol.TrendChartSymbols {

  private static Resource i18nTrendChart =
  Trace.getBundle("com.gensym.classes.Messages");

//   private static MessageKey tcTraceKey =
//   Trace.registerMessageKey("com.gensym.displays",
// 			   TrendChartImpl.class);

//   static private Resource tci18nTrace =
//   Trace.getBundle("com.gensym.classes.TraceMessages");

  private static final Symbol ITEM_INITIAL_DATA_ = Symbol.intern ("ITEM-INITIAL-DATA");
  private static final Symbol SUBSCRIPTION_HANDLE_ = Symbol.intern ("SUBSCRIPTION-HANDLE");

  private static final Symbol ELEMENT_TYPE_ = Symbol.intern ("ELEMENT-TYPE");
  private static final Symbol ELEMENT_DATA_ = Symbol.intern ("ELEMENT-DATA");
  
//   public TrendChartSpecialImpl (TrendChart trendChart) {
//     super(((ImplAccess)trendChart).getContext(),
// 	  ((G2__BaseImpl)trendChart).getHandle(),
// 	  ((ImplAccess)trendChart).getAttributes());
//   }

  private static final String userData = "UserData";

  //    Trace.writeObjectToFile(5, wsTraceKey,
  //		    "c:\\TEMP\\trendchart" + workspaceHandle + ".ser",
  //		    wsinfo);
  
  private static Structure representTrendChart(G2Access context,
					       Item item,
					       TrendChart client,
					       java.lang.Object userData)
       throws G2AccessException
  {
    return (Structure)invokeTwAccessMethod(context, "representTrendChart",
					   new Class[]
					   {Item.class,
					      TrendChart.class,
					      java.lang.Object.class},
					   new java.lang.Object[]
					   {item, client, userData});
  }

  private void initiateSubscriptions() throws G2AccessException
  {
    synchronized (data) { //tcData
      TrendChartData tcData = (TrendChartData)data;
      if (tcData.alreadySubscribed)
    	return;
             
      Structure itemInfo = representTrendChart(context, this, this, userData);
      
      try {
    	tcData.tcSubscrpnHandle =
    	  (Integer)itemInfo.getAttributeValue(SUBSCRIPTION_HANDLE_);
    	Structure initialInfo =
    	  (Structure)itemInfo.getAttributeValue(ITEM_INITIAL_DATA_, null);
    	tcData.lastUpdateTime =
    	  (long)(((Number)initialInfo.getAttributeValue(CURRENT_G2_TIME_)).doubleValue() * 1000);
    	boolean active = tcData.activationState =
    	  initialInfo.getBoolean(TREND_CHART_ACTIVE_);
    	if (active) {
    	  tcData.timeSpanInfo =
    	    (Structure)initialInfo.getAttributeValue(TIMESPAN_);
	  
	  // In three-tier mode, one gets pre-processed histories from
	  // the middle-tier, rather than the Structures and Sequences
	  // that G2 sends out.
	  Hashtable histories =
	    (Hashtable)initialInfo.getAttributeValue(PROCESSED_PLOT_DATA_, null);
	  if (histories != null)
	    tcData.histories = histories;
	  else { // must be in two tier mode, getting data directly out of G2
	    tcData.initialData =
	      (Sequence)initialInfo.getAttributeValue(INITIAL_PLOT_DATA_, null);
	    if (tcData.initialData != null)
	      processPlotData(tcData.initialData);
	  }
    	  tcData.valueAxisExtrema =
    	    (Sequence)initialInfo.getAttributeValue(VALUE_AXIS_EXTREMA_);
    	}
      } catch (NoSuchAttributeException nsae) {
    	Trace.exception(nsae);
    	throw new CorruptionException(nsae);
      }
      tcData.alreadySubscribed = true;
    }
  }

  @Override
  public boolean getActivationState() {
    return ((TrendChartData)data).activationState;
  }

  /**
   * Adds l as both an ItemListener and a TrendChartListener.
   * @undocumented
   */
  @Override
  public void addTrendChartListener(TrendChartListener l) throws G2AccessException {
    
    // test is done here in order to prevent entering the monitor
    // unnecessarily
    if (!((TrendChartData)data).alreadySubscribed)
      initiateSubscriptions();
    
    ((TrendChartData)data).trendChartListener =
      TrendChartEventMulticaster.add(((TrendChartData)data).trendChartListener, l);
  }

  /**
   * Adds listener as both an ItemListener and a TrendChartListener.
   * @returns current state of the trendChart
   * @undocumented
   */
  @Override
  public Structure addTrendChartListenerRetrievingState
  (TrendChartListener listener) throws G2AccessException{
    synchronized (data) { //tcData
      addTrendChartListener(listener);
      return retrieveState();
    }
  }

  @Override
  protected Structure retrieveState() {
    TrendChartData tcData = (TrendChartData)data;
    Structure state = new Structure();
    Structure initialData = new Structure();
    
    initialData.setAttributeValue(TIMESPAN_, getTimespan());
    // We get much faster transmission over RMI sending
    // the arrays of primitives inside the histories, rather
    // than sending the Sequences and Structures that G2
    // produces.
    initialData.setAttributeValue(PROCESSED_PLOT_DATA_,
				  ((TrendChartData)data).
				  histories.clone());
    initialData.setAttributeValue(VALUE_AXIS_EXTREMA_,
    				  getValueAxisExtrema());
    initialData.setAttributeValue(TREND_CHART_ACTIVE_,
				  new Boolean(getActivationState()));
    // The following division by 1000 is to match the data in the
    // form it comes from g2
    initialData.setAttributeValue(CURRENT_G2_TIME_,
				  (new Double(((double)tcData.
					       lastUpdateTime)/1000d)));
    initialData.setAttributeValue(TREND_CHART_ACTIVE_,
				  new Boolean(tcData.activationState));
    state.setAttributeValue(ITEM_INITIAL_DATA_, initialData);
    state.setAttributeValue(SUBSCRIPTION_HANDLE_,
    			    ((TrendChartData)data).tcSubscrpnHandle);
    return state;
  }

  /**
   * removes l as both an ItemListener and a TrendChartListener.
   * This clears all the history data store from the subscription
   * if l is the last listener to be removed.
   * @undocumented
   */
  @Override
  public void removeTrendChartListener(TrendChartListener l)
  throws G2AccessException {
    TrendChartData tcData = (TrendChartData)data;
    synchronized (tcData) {
      tcData.trendChartListener =
	TrendChartEventMulticaster.remove(tcData.trendChartListener, l);
      if (tcData.trendChartListener == null) {
	tcData.alreadySubscribed = false;
	tcData.histories.clear();
 	invokeTwAccessMethod(context, "unrepresentTrendChart",
 			     new Class[]{Integer.TYPE},
 			     new java.lang.Object[] {tcData.tcSubscrpnHandle});
      }
    }
  }

  /**
   * @undocumented
   */
  @Override
  public void processTrendChartEvent(TrendChartEvent event) {
    synchronized (data) { //tcData
      TrendChartData tcData = (TrendChartData)data;
      Structure newInfo = event.getNewInfo();
      try {
	switch (event.getID()) {
	case TrendChartEvent.GENERAL_UPDATE:
	  processGeneralUpdate(newInfo);
	     break;
	case TrendChartEvent.ACTIVATION:
	  tcData.activationState = newInfo.getBoolean(ACTIVATION_VALUE_);
	  if (!tcData.activationState)
	    clearHistories();
	  break;
	case TrendChartEvent.CLOCK_DISCONTINUITY:
	  processClockDiscontinuity(newInfo);
	  break;
	default:
	}
      } catch (NoSuchAttributeException nsae) {
	throw new CorruptionException(nsae);
      }
    }
    
    dispatchTrendChartEventToListeners(event);
  }

  private void dispatchTrendChartEventToListeners(TrendChartEvent event) {
    if (((TrendChartData)data).trendChartListener != null)
      ((TrendChartData)data).trendChartListener.processTrendChartEvent(event);
  }

  @Override
  public Structure getTimespan() {
    return ((TrendChartData)data).timeSpanInfo;
  }

  @Override
  public Sequence getValueAxisExtrema() {
    return ((TrendChartData)data).valueAxisExtrema;
  }

  @Override
  public Sequence getInitialData() {
    return ((TrendChartData)data).initialData;
  }

  @Override
  public long getLastUpdateTime() {
    synchronized (data) { //tcData
      return ((TrendChartData)data).lastUpdateTime;
    }
  }

  @Override
  protected ItemData makeDataForItem() {
    return new TrendChartData();
  }

  /**
   * Overriden to provide information regarding additions and deletions
   * to multiple compound slots (value-axes, connector-formats,
   * point-formats, and plots).
   */

  @Override
  public void processItemEvent(ItemEvent e) {
    detectAndPropogateAdditionsAndDeletions(e);
    // must detect before the super call, as the super call
    // modifies the current data.
    super.processItemEvent(e);
  }

  private void detectAndPropogateAdditionsAndDeletions(ItemEvent e) {
    Sequence denotation = e.getDenotation ();
    java.lang.Object newValueObject = e.getNewValue ();
    Symbol attrName_ = 
      (Symbol) ((Structure)denotation.elementAt (0)).getAttributeValue
                                                     (Denotation.NAME_, null);
    if (slotIsMultipleCompoundSlot(attrName_)) {
      Sequence newSequence = (Sequence)newValueObject;
      Sequence oldSequence = (Sequence)getActualAttributes().getAttributeValue(attrName_, null);
      propogateAdditionsOrDeletions(attrName_,
				    newSequence, oldSequence,
				    TrendChartEvent.ELEMENT_ADDED_);
      propogateAdditionsOrDeletions(attrName_,
				    oldSequence, newSequence,
				    TrendChartEvent.ELEMENT_DELETED_);
    }
  }

  private boolean slotIsMultipleCompoundSlot(Symbol attrName_) {
    return (PLOTS_.equals(attrName_) ||
	    CONNECTOR_FORMATS_.equals(attrName_) ||
	    SystemAttributeSymbols.POINT_FORMATS_.equals(attrName_) ||
	    VALUE_AXES_.equals(attrName_));
  }

  // PERFORMANCE NOTE: These use a 2n-squared algorithm on the basis
  // that n is small. It is also presumed that these methods
  // will not be called frequently.

  // NOTE: this algorithm is protecting against the possibility
  // of simultaneous deletion and insertion, and does not presume
  // a particular order of the sequences.

  private void propogateAdditionsOrDeletions(Symbol attrName_,
					     Sequence masterSequence,
					     Sequence slaveSequence,
					     Symbol modificationCode) {
    int slaveLength = slaveSequence.size();
    int masterLength = masterSequence.size();
    try {
      for (int i = 0; i < masterLength; i++) {
	Structure masterStruct = (Structure)masterSequence.elementAt(i);
	java.lang.Object masterUid = masterStruct.getAttributeValue(CHART_ELEMENT_UID_);
	boolean foundInSlave = false;
	for (int j = 0; j < slaveLength; j++) {
	  Structure slaveStruct = (Structure)slaveSequence.elementAt(j);
	  java.lang.Object slaveUid = slaveStruct.getAttributeValue(CHART_ELEMENT_UID_);
	  if (masterUid.equals(slaveUid)) {
	    foundInSlave = true;
	    break;
	  }
	}
	if (!foundInSlave) {
	  dispatchAdditionOrDeletion(attrName_, masterStruct, modificationCode);
	}
      }
    } catch (NoSuchAttributeException nsae) {
      Trace.exception(nsae);
      throw new CorruptionException(nsae);
    }
  }

  private void dispatchAdditionOrDeletion(Symbol attrName_,
					  Structure masterStruct,
					  Symbol modificationCode) {
    if (TrendChartEvent.ELEMENT_DELETED_.equals(modificationCode) &&
	PLOTS_.equals(attrName_))
      processPlotDeletion(masterStruct);
    
    Structure infoStruct = new Structure();
    infoStruct.setAttributeValue(ELEMENT_TYPE_, attrName_);
    infoStruct.setAttributeValue(ELEMENT_DATA_, masterStruct);
    TrendChartEvent event =
      new TrendChartEvent(this,
			  this,
                          -1, // not really from tc subscription
			  modificationCode,
			  infoStruct);
    dispatchTrendChartEventToListeners(event);
  }

  private void processPlotDeletion(Structure plotStruct) {
    java.lang.Object uid = plotStruct.getAttributeValue(CHART_ELEMENT_UID_, null);
    HistoryRingBuffer buf =
      (HistoryRingBuffer)((TrendChartData)data).histories.remove(uid);
  }

  // The following introspective convolutions are to allow for
  // Javalink to be able to load this class. There are things
  // elsewhere in this class that are a problem, but the
  // HistoryBuffer stuff is new, so it might as well be right.

  private static final String HISTORY_BUFFER_CLASS_NAME =
  "com.gensym.ntw.util.ChartHistoryBuffer";
  private static Constructor HISTORY_CONSTRUCTOR;
  private static java.lang.reflect.Method SET_START_INDEX_METHOD;
  private static final String SET_START_INDEX_METHOD_NAME = "setG2StartIndex";
  private static final Class[] SET_START_INDEX_METHOD_ARG_TYPES =
  new Class[] {Number.class};
  private static final Symbol HISTORY_INDEX_START_ = Symbol.intern ("HISTORY-INDEX-START");
  private static final Class[] HISTORY_CONSTRUCTOR_ARG_TYPES =
  new Class[] {Long.TYPE, Long.TYPE};
      
  static {
    Class historyClass = null;
    try {
      historyClass = Class.forName(HISTORY_BUFFER_CLASS_NAME);
      
    } catch (ClassNotFoundException cnfe) {
      // fix this: If we new whether we were in Javalink
      // or Telewindows2, we would know if we should do
      // something more draconian here.
      Trace.exception(cnfe);
    }

    // the Telewindows2 case: we have the classes we need.
    if (historyClass != null) {
      try {
    	HISTORY_CONSTRUCTOR =
    	  historyClass.getConstructor(HISTORY_CONSTRUCTOR_ARG_TYPES);
	SET_START_INDEX_METHOD =
	  historyClass.getMethod(SET_START_INDEX_METHOD_NAME,
				 SET_START_INDEX_METHOD_ARG_TYPES);
      } catch (NoSuchMethodException nsme) {
	// fix this: do something more draconian here.
	Trace.exception(nsme);
      }
    }
  }

  /** This method can only be called from within a trend-chart subscription
   * callback, so if the constructor is null, then a NoClassDefFoundError
   * would have been thrown if we hadn't been using introspection, so we
   * take the opportunity to throw it here.
   */
  private HistoryRingBuffer makeHistoryRingBuffer(java.lang.Object uid,
						  Number historyStartIndex)
  {
    if (HISTORY_CONSTRUCTOR == null)
      throw new NoClassDefFoundError(i18nTrendChart.format("unableToFindClass", HISTORY_BUFFER_CLASS_NAME));
    							     
    try {
      java.lang.Object hrb =
    	HISTORY_CONSTRUCTOR.newInstance(new java.lang.Object[]
					{getTotalTimeSpanLength(), getGranularity(uid)});
      if (SET_START_INDEX_METHOD != null)
	SET_START_INDEX_METHOD.invoke(hrb,
				      new java.lang.Object[]
				      {historyStartIndex});
      return (HistoryRingBuffer)hrb;
    } catch (Exception ex) {
      throw new UnexpectedException(ex);
    }
  }

  /** not synchronizing on the presumption that this is called from
   * an appropriately synchronized block.
   */
  private final void processGeneralUpdate(Structure newInfo)
  throws NoSuchAttributeException {
    TrendChartData tcData = (TrendChartData)data;
    Structure struct = (Structure)newInfo.getAttributeValue(TIME_BOUNDS_, null);
    setCurrentTime((long)(((Number)newInfo.getAttributeValue(CURRENT_G2_TIME_)).doubleValue() * 1000));

//     Trace.send(10, traceKey, i18nTrace, "wtciprocessGeneralUpdate",
// 	       this, newInfo);

    if (struct != null) {
      tcData.timeSpanInfo = struct;
      long newTimeSpan =
	(long)(((Number)struct.getAttributeValue(TIMESPAN_)).
	       doubleValue() * 1000d);
      if (tcData.timeSpan != newTimeSpan) {
	tcData.timeSpan = newTimeSpan;
	// fix this: should be able to maintain the size of buffers better:
	// should also adjust for changes in granularity.
	adjustHistoryTimeSpans(newTimeSpan);
      }
    }

    Sequence seq =
      (Sequence)newInfo.getAttributeValue(VALUE_AXIS_EXTREMA_, null);
    if (seq != null)
      tcData.valueAxisExtrema = seq;

    seq = (Sequence)newInfo.getAttributeValue(NEW_PLOT_DATA_, null);
    if (seq != null)
      processPlotData(seq);

  }

  private final void  adjustHistoryTimeSpans(long newTimeSpan) {
    for (Enumeration en = ((TrendChartData)data).histories.elements();
	 en.hasMoreElements();)
      ((HistoryRingBuffer)en.nextElement()).setTimeSpan(newTimeSpan);
  }

  /** not synchronizing on the presumption that this is called from
   * an appropriately synchronized block.
   */
  private void setCurrentTime(long currentTime) {
    ((TrendChartData)data).lastUpdateTime = currentTime;
  }

  /** not synchronizing on the presumption that this is called from
   * an appropriately synchronized block.
   */
  private void processPlotData(Sequence plotDataSequence)
  throws NoSuchAttributeException {
    TrendChartData tcData = (TrendChartData)data;
    int length = plotDataSequence.size();
    Hashtable histories = tcData.histories;
        
    for (int i = 0; i < length; i++) {
      Structure plotDataInfo = (Structure)plotDataSequence.elementAt(i);
      Structure plotData =
	(Structure) plotDataInfo.getAttributeValue(PLOT_DATA_);
      Integer uid = (Integer)plotDataInfo.getAttributeValue(CHART_ELEMENT_UID_);
      java.lang.Object note = plotDataInfo.getAttributeValue(UPDATE_NOTE_, null);
          
          
      HistoryRingBuffer history = (HistoryRingBuffer)histories.get(uid);
          
          
      if (note != null && RENEW_FULL_HISTORY_.equals(note) || history == null) {
    	Number historyStartIndex =
    	  (Number) plotDataInfo.getAttributeValue(HISTORY_INDEX_START_, null);
	history = makeHistoryRingBuffer(uid, historyStartIndex);
	histories.put(uid, history);
      }
          
      Sequence values =
	(Sequence)plotData.getAttributeValue(HISTORY_VALUES_);
      Sequence timestamps =
	(Sequence)plotData.getAttributeValue(HISTORY_COLLECTION_TIMES_);
      int size = values.size();
      for (int j = 0; j < size; j++) {
	Number historyCollectionTimeObj =
	  (Number)timestamps.elementAt(j);
	long historyCollectionTime =
	  (long)(historyCollectionTimeObj.doubleValue() * 1000.0);
	double value =
	  ((Number)values.elementAt(j)).doubleValue();
	history.addElement(historyCollectionTime, value);
      }
    }
  }

  private void processClockDiscontinuity(Structure newInfo) {
    try {
      adjustPlotHistories((long)((Double)newInfo.getAttributeValue(TIME_DELTA_)).
			  doubleValue() *1000);
      ((TrendChartData)data).timeSpanInfo =
	((Structure)newInfo.getAttributeValue(TIMESPAN_INFO_));
      Sequence seq = (Sequence)newInfo.getAttributeValue(INITIAL_PLOT_DATA_, null);
      if (seq != null)
	processPlotData(seq);
    } catch (NoSuchAttributeException nsae) {
      throw new CorruptionException(nsae);
    }
  }

  private void adjustPlotHistories(long timeDelta) {
    for (Enumeration en = ((TrendChartData)data).histories.elements();
	 en.hasMoreElements();)
      ((HistoryRingBuffer)en.nextElement()).adjustTimestamps(timeDelta);
  }

  private void clearHistories() {
    for (Enumeration en = ((TrendChartData)data).histories.elements();
    	 en.hasMoreElements();)
      ((HistoryRingBuffer)en.nextElement()).clear();
  }

  /** This is for access by com.gensym.displays.TrendChart.
   * @undocumented
   */
  @Override
  public Structure getIcon(Symbol className)
  throws G2AccessException {
    ClassManager classManager = context.getClassManager();
    return (Structure)classManager.getClassAttributeValue(className, SystemAttributeSymbols.ICON_DESCRIPTION_);
    //return context.getDefinition(className);
  }

  /** Returns the history buffer for the specified plot.
   */
  @Override
  public HistoryRingBuffer getHistory(java.lang.Object plotUid) {
    synchronized (data) { //tcData
      return (HistoryRingBuffer)((TrendChartData)data).histories.get(plotUid);
    }
  }

  private final Structure getTrendChartPlot(java.lang.Object uid)
  throws G2AccessException {
    try {
      Sequence plots = getPlots();
      int size = plots.size();
      for (int i = 0; i < size; i++) {
	Structure plot = (Structure)plots.elementAt(i);
	java.lang.Object plotUid = plot.getAttributeValue(CHART_ELEMENT_UID_);
	if (plotUid.equals(uid))
	  return plot;
      }
    } catch (NoSuchAttributeException nsae) {
      throw new CorruptionException(nsae);
    }
    throw
      new IllegalArgumentException(i18nTrendChart.format("tci_badUid", uid));
  }

  private final Structure getDefaultTrendChartPlot()
  throws G2AccessException {
    return getTrendChartPlot(com.gensym.util.symbol.TrendChartSymbols.DEFAULT_);
  }

  private final java.lang.Object getTrendChartPlotSlot(Structure plotInfo,
						       Symbol slotName)
  throws G2AccessException {
    java.lang.Object value =
     plotInfo.getAttributeValue(slotName, null);

    if (value == null)
      return getDefaultTrendChartPlot().getAttributeValue(slotName, null);
    else
      return value;
  }

  private final long getGranularity(java.lang.Object uid)
  throws G2AccessException {
    Structure plot = getTrendChartPlot(uid);

    Structure updateInterval =
      (Structure)getTrendChartPlotSlot(plot, UPDATE_INTERVAL_);

    Number intervalNum = null;
    try {
      intervalNum =
	((Number)updateInterval.getAttributeValue(UPDATE_INTERVAL_));
    } catch (NoSuchAttributeException nsae) {
      throw new CorruptionException(nsae);
    }
    long interval = (long)(intervalNum.doubleValue() * 1000);

    Number granularityNum =
      (Number)updateInterval.getAttributeValue(GRANULARITY_, null);
    
    if (granularityNum == null)
      return interval;
    
    long granularity = (long)(granularityNum.doubleValue() * 1000);

    return Math.min(interval, granularity);
  }

  private static final int DAY = 86400000;

  private final long getTotalTimeSpanLength()
  throws G2AccessException {
    Structure timeAxis = getTimeAxis();
    long spanLength = -1;
    Structure totalTimeSpan =
      (Structure)timeAxis.getAttributeValue(TOTAL_TIME_SPAN_, null);
    try {
      if (totalTimeSpan != null) {
	Symbol timeSpanMode =
	  (Symbol)totalTimeSpan.getAttributeValue(TOTAL_TIME_SPAN_MODE_);
	if (INTERVAL_.equals(timeSpanMode)) {
	  spanLength =
	    (long)(((Number)totalTimeSpan.
		    getAttributeValue(NUMBER_OF_SECONDS_)).doubleValue() *
		   1000.0);
	}
      }

      Structure dataWindowTimeSpan =
	(Structure)timeAxis.getAttributeValue(DATA_WINDOW_TIME_SPAN_, null);
      if (dataWindowTimeSpan != null) {
	Symbol dataWindowSpanMode =
	  (Symbol)dataWindowTimeSpan.getAttributeValue(DATA_WINDOW_TIME_SPAN_MODE_);
	if (INTERVAL_.equals(dataWindowSpanMode)) {
	  long dwLength =
	    (long)(((Number)dataWindowTimeSpan.
		    getAttributeValue(NUMBER_OF_SECONDS_)).doubleValue() *
		   1000.0);
	  spanLength = Math.max(dwLength, spanLength);
	}
      }
      if (spanLength == -1)
	spanLength = DAY;

      return spanLength;
    } catch (NoSuchAttributeException nsae) {
      throw new CorruptionException(nsae);
    }
  }
}
