/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      TrendChartImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:11:45 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import java.util.Hashtable;
import java.util.Enumeration;
import java.lang.reflect.Constructor;
import com.gensym.ntw.util.TrendChartEventMulticaster;
import com.gensym.ntw.util.TrendChartEvent;
import com.gensym.ntw.util.TrendChartListener;
import com.gensym.util.ItemEvent;
import com.gensym.util.Denotation;
import com.gensym.util.UnexpectedException;
import com.gensym.util.CorruptionException;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.HistoryRingBuffer;
import com.gensym.util.ClassManager;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.message.Resource;

public class TrendChartImpl extends com.gensym.classes.ItemImpl implements TrendChart {


  static final long serialVersionUID = 2L;

  /* Overriden Field */
  private static Resource i18nTrendChart = Trace.getBundle("com.gensym.classes.Messages");
  /* Overriden Field */
  private static final Symbol ITEM_INITIAL_DATA_ = Symbol.intern ("ITEM-INITIAL-DATA");
  /* Overriden Field */
  private static final Symbol SUBSCRIPTION_HANDLE_ = Symbol.intern ("SUBSCRIPTION-HANDLE");
  /* Overriden Field */
  private static final Symbol ELEMENT_TYPE_ = Symbol.intern ("ELEMENT-TYPE");
  /* Overriden Field */
  private static final Symbol ELEMENT_DATA_ = Symbol.intern ("ELEMENT-DATA");
  /* Overriden Field */
  private static final String userData = "UserData";
  /* Overriden Field */
  private static final String HISTORY_BUFFER_CLASS_NAME = "com.gensym.ntw.util.ChartHistoryBuffer";
  /* Overriden Field */
  private static Constructor HISTORY_CONSTRUCTOR;
  /* Overriden Field */
  private static java.lang.reflect.Method SET_START_INDEX_METHOD;
  /* Overriden Field */
  private static final String SET_START_INDEX_METHOD_NAME = "setG2StartIndex";
  /* Overriden Field */
  private static final Class[] SET_START_INDEX_METHOD_ARG_TYPES = new Class[] {Number.class};
  /* Overriden Field */
  private static final Symbol HISTORY_INDEX_START_ = Symbol.intern ("HISTORY-INDEX-START");
  /* Overriden Field */
  private static final Class[] HISTORY_CONSTRUCTOR_ARG_TYPES = new Class[] {Long.TYPE, Long.TYPE};
  /* Overriden Field */
  private static final int DAY = 86400000;
  /* Generated constructors */

  public TrendChartImpl() {
    super();
  }

  public TrendChartImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public TrendChartImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /* Overriden Property - ACTIVATION-STATE */
  /**  Property Getter for ACTIVATION-STATE */
  @Override
  public boolean getActivationState() {
    
        return ((TrendChartData)data).activationState;
      
  }


  /* Overriden Property - TIMESPAN */
  /**  Property Getter for TIMESPAN */
  @Override
  public Structure getTimespan() {
    
        return ((TrendChartData)data).timeSpanInfo;
      
  }


  /* Overriden Property - VALUE-AXIS-EXTREMA */
  /**  Property Getter for VALUE-AXIS-EXTREMA */
  @Override
  public Sequence getValueAxisExtrema() {
    
        return ((TrendChartData)data).valueAxisExtrema;
      
  }


  /* Overriden Property - INITIAL-DATA */
  /**  Property Getter for INITIAL-DATA */
  @Override
  public Sequence getInitialData() {
    
        return ((TrendChartData)data).initialData;
      
  }


  /* Overriden Property - LAST-UPDATE-TIME */
  /**  Property Getter for LAST-UPDATE-TIME */
  @Override
  public long getLastUpdateTime() {
    
        synchronized (data) { //tcData
          return ((TrendChartData)data).lastUpdateTime;
        }
      
  }


  /* Overriden Property - CURRENT-TIME */

  /** not synchronizing on the presumption that this is called from
   * an appropriately synchronized block.
   */
  private void setCurrentTime(long currentTime)   {
    
        ((TrendChartData)data).lastUpdateTime = currentTime;
      
  }

  /* Overriden Property - ICON */
  /** This is for access by com.gensym.displays.TrendChart.
   * @undocumented
   */
  @Override
  public Structure getIcon(Symbol className)
  throws G2AccessException {
    
        ClassManager classManager = context.getClassManager();
        return (Structure)classManager.getClassAttributeValue(className, SystemAttributeSymbols.ICON_DESCRIPTION_);
                                                   
      
  }


  /* Overriden Property - HISTORY */
  /** Returns the history buffer for the specified plot.
   */
  @Override
  public HistoryRingBuffer getHistory(java.lang.Object plotUid) {
    
        synchronized (data) { //tcData
          return (HistoryRingBuffer)((TrendChartData)data).histories.get(plotUid);
        }
      
  }


  /* Overriden Property - TREND-CHART-PLOT */
  /**  Property Getter for TREND-CHART-PLOT */
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


  /* Overriden Property - DEFAULT-TREND-CHART-PLOT */
  /**  Property Getter for DEFAULT-TREND-CHART-PLOT */
  private final Structure getDefaultTrendChartPlot()
  throws G2AccessException {
    
        return getTrendChartPlot(com.gensym.util.symbol.TrendChartSymbols.DEFAULT_);
      
  }


  /* Overriden Property - TREND-CHART-PLOT-SLOT */
  /**  Property Getter for TREND-CHART-PLOT-SLOT */
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


  /* Overriden Property - GRANULARITY */
  /**  Property Getter for GRANULARITY */
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


  /* Overriden Property - TOTAL-TIME-SPAN-LENGTH */
  /**  Property Getter for TOTAL-TIME-SPAN-LENGTH */
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


  /**
   * Generated Property Setter for attribute -- TITLE
   * @param title new value to conclude for TITLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTitle(java.lang.String title) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TITLE_, title);
  }

  /**
   * Generated Property Getter for attribute -- TITLE
   * @return the value of the TITLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getTitle() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TITLE_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- PLOTS
   * @param plots new value to conclude for PLOTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPlots(com.gensym.util.Sequence plots) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PLOTS_, plots);
  }

  /**
   * Generated Property Getter for attribute -- PLOTS
   * @return the value of the PLOTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getPlots() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PLOTS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- VALUE-AXES
   * @param valueAxes new value to conclude for VALUE-AXES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setValueAxes(com.gensym.util.Sequence valueAxes) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.VALUE_AXES_, valueAxes);
  }

  /**
   * Generated Property Getter for attribute -- VALUE-AXES
   * @return the value of the VALUE-AXES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getValueAxes() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.VALUE_AXES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TIME-AXIS
   * @param timeAxis new value to conclude for TIME-AXIS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTimeAxis(com.gensym.util.Structure timeAxis) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TIME_AXIS_, timeAxis);
  }

  /**
   * Generated Property Getter for attribute -- TIME-AXIS
   * @return the value of the TIME-AXIS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getTimeAxis() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TIME_AXIS_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- POINT-FORMATS
   * @param pointFormats new value to conclude for POINT-FORMATS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPointFormats(com.gensym.util.Sequence pointFormats) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.POINT_FORMATS_, pointFormats);
  }

  /**
   * Generated Property Getter for attribute -- POINT-FORMATS
   * @return the value of the POINT-FORMATS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getPointFormats() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.POINT_FORMATS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CONNECTOR-FORMATS
   * @param connectorFormats new value to conclude for CONNECTOR-FORMATS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setConnectorFormats(com.gensym.util.Sequence connectorFormats) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.CONNECTOR_FORMATS_, connectorFormats);
  }

  /**
   * Generated Property Getter for attribute -- CONNECTOR-FORMATS
   * @return the value of the CONNECTOR-FORMATS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getConnectorFormats() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CONNECTOR_FORMATS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TREND-CHART-FORMAT
   * @param trendChartFormat new value to conclude for TREND-CHART-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTrendChartFormat(com.gensym.util.Structure trendChartFormat) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TREND_CHART_FORMAT_, trendChartFormat);
  }

  /**
   * Generated Property Getter for attribute -- TREND-CHART-FORMAT
   * @return the value of the TREND-CHART-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getTrendChartFormat() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TREND_CHART_FORMAT_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- EVALUATION-ATTRIBUTES
   * @param evaluationAttributes new value to conclude for EVALUATION-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setEvaluationAttributes(com.gensym.util.Structure evaluationAttributes) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.EVALUATION_ATTRIBUTES_, evaluationAttributes);
  }

  /**
   * Generated Property Getter for attribute -- EVALUATION-ATTRIBUTES
   * @return the value of the EVALUATION-ATTRIBUTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getEvaluationAttributes() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.EVALUATION_ATTRIBUTES_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SIZE-IN-WORKSPACE
   * @param sizeInWorkspace new value to conclude for SIZE-IN-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSizeInWorkspace(com.gensym.util.Structure sizeInWorkspace) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SIZE_IN_WORKSPACE_, sizeInWorkspace);
  }

  /**
   * Generated Property Getter for attribute -- SIZE-IN-WORKSPACE
   * @return the value of the SIZE-IN-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getSizeInWorkspace() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SIZE_IN_WORKSPACE_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ITEM-CONFIGURATION
   * @param itemConfiguration new value to conclude for ITEM-CONFIGURATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setItemConfiguration(com.gensym.util.Sequence itemConfiguration) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ITEM_CONFIGURATION_, itemConfiguration);
  }

  /**
   * Generated Property Getter for attribute -- ITEM-CONFIGURATION
   * @return the value of the ITEM-CONFIGURATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getItemConfiguration() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_CONFIGURATION_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- NAMES
   * @param names new value to conclude for NAMES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setNames(java.lang.Object names) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.NAMES_, names);
  }

  /**
   * Generated Property Getter for attribute -- NAMES
   * @return the value of the NAMES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getNames() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.NAMES_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- LAYER-POSITION
   * @return the value of the LAYER-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getLayerPosition() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.LAYER_POSITION_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- FOLLOWING-ITEM-IN-WORKSPACE-LAYERING
   * @param followingItemInWorkspaceLayering new value to conclude for FOLLOWING-ITEM-IN-WORKSPACE-LAYERING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setFollowingItemInWorkspaceLayering(com.gensym.classes.Block followingItemInWorkspaceLayering) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.FOLLOWING_ITEM_IN_WORKSPACE_LAYERING_, followingItemInWorkspaceLayering);
  }

  /**
   * Generated Property Getter for attribute -- FOLLOWING-ITEM-IN-WORKSPACE-LAYERING
   * @return the value of the FOLLOWING-ITEM-IN-WORKSPACE-LAYERING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.classes.Block getFollowingItemInWorkspaceLayering() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FOLLOWING_ITEM_IN_WORKSPACE_LAYERING_);
    return (com.gensym.classes.Block)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- POSITION-IN-WORKSPACE
   * @param positionInWorkspace new value to conclude for POSITION-IN-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPositionInWorkspace(com.gensym.util.Structure positionInWorkspace) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.POSITION_IN_WORKSPACE_, positionInWorkspace);
  }

  /**
   * Generated Property Getter for attribute -- POSITION-IN-WORKSPACE
   * @return the value of the POSITION-IN-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getPositionInWorkspace() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.POSITION_IN_WORKSPACE_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- RELATIONSHIPS
   * @param relationships new value to conclude for RELATIONSHIPS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setRelationships(com.gensym.util.Sequence relationships) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.RELATIONSHIPS_, relationships);
  }

  /**
   * Generated Property Getter for attribute -- RELATIONSHIPS
   * @return the value of the RELATIONSHIPS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getRelationships() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.RELATIONSHIPS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- ITEM-NOTES
   * @return the value of the ITEM-NOTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getItemNotes() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_NOTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CONTAINING-MODULE
   * @return the value of the CONTAINING-MODULE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getContainingModule() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CONTAINING_MODULE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- ITEM-ACTIVE
   * @return the value of the ITEM-ACTIVE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getItemActive() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_ACTIVE_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- ITEM-STATUS
   * @return the value of the ITEM-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getItemStatus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_STATUS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- INSTANTIATE
   * @return the value of the INSTANTIATE attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getInstantiateForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INSTANTIATE_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- INCLUDE-IN-MENUS
   * @return the value of the INCLUDE-IN-MENUS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getIncludeInMenusForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INCLUDE_IN_MENUS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- SYSTEM-MENU-CHOICES
   * @return the value of the SYSTEM-MENU-CHOICES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getSystemMenuChoicesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.SYSTEM_MENU_CHOICES_);
    return (java.lang.Object)retnValue;
  }

  /* Overriden  - TRENDCHART Event Listener - Adder1 */
  @Override
  public void addTrendChartListener(TrendChartListener l) throws G2AccessException {
    
        
                                                                      
                         
        if (!((TrendChartData)data).alreadySubscribed)
          initiateSubscriptions();
        
        ((TrendChartData)data).trendChartListener =
          TrendChartEventMulticaster.add(((TrendChartData)data).trendChartListener, l);
      
  }

  /* Overriden  - TRENDCHART Event Listener - Remover1 */
  @Override
  public void removeTrendChartListener(TrendChartListener l)
  throws G2AccessException   {
    
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

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  /* Overriden method - ADJUST-HISTORY-TIME-SPANS */
  private final void  adjustHistoryTimeSpans(long newTimeSpan)
 {
    
        for (Enumeration en = ((TrendChartData)data).histories.elements();
    	 en.hasMoreElements();)
          ((HistoryRingBuffer)en.nextElement()).setTimeSpan(newTimeSpan);
      
  }

  /* Overriden method - PROCESS-GENERAL-UPDATE */
  private final void processGeneralUpdate(Structure newInfo)
  throws NoSuchAttributeException
 {
    
        TrendChartData tcData = (TrendChartData)data;
        Structure struct = (Structure)newInfo.getAttributeValue(TIME_BOUNDS_, null);
        setCurrentTime((long)(((Number)newInfo.getAttributeValue(CURRENT_G2_TIME_)).doubleValue() * 1000));
    
                                                                           
                               
    
        if (struct != null) {
          tcData.timeSpanInfo = struct;
          long newTimeSpan =
    	(long)(((Number)struct.getAttributeValue(TIMESPAN_)).
    	       doubleValue() * 1000d);
          if (tcData.timeSpan != newTimeSpan) {
    	tcData.timeSpan = newTimeSpan;
    	                                                                    
    	                                                  
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

  /* Overriden method - MAKE-HISTORY-RING-BUFFER */
  private HistoryRingBuffer makeHistoryRingBuffer(java.lang.Object uid,
						  Number historyStartIndex)
 {
    
        if (HISTORY_CONSTRUCTOR == null)
          throw new NoClassDefFoundError(i18nTrendChart.format("unableToFindClass", HISTORY_BUFFER_CLASS_NAME));
        							     
        try {
          java.lang.Object hrb =
        	HISTORY_CONSTRUCTOR.newInstance(new java.lang.Object[]
    					{getTotalTimeSpanLength(),
    					  getGranularity(uid)});
          if (SET_START_INDEX_METHOD != null)
    	SET_START_INDEX_METHOD.invoke(hrb,
    				      new java.lang.Object[]
    				      {historyStartIndex});
          return (HistoryRingBuffer)hrb;
        } catch (Exception ex) {
          throw new UnexpectedException(ex);
        }
      
  }

  /* Overriden method - STATIC */
  static
 {
    
        Class historyClass = null;
        try {
          historyClass = Class.forName(HISTORY_BUFFER_CLASS_NAME);
          
        } catch (ClassNotFoundException cnfe) {
                                                             
                                                            
                                            
          Trace.exception(cnfe);
        }
    
                                                               
        if (historyClass != null) {
          try {
        	HISTORY_CONSTRUCTOR =
        	  historyClass.getConstructor(HISTORY_CONSTRUCTOR_ARG_TYPES);
    	SET_START_INDEX_METHOD =
    	  historyClass.getMethod(SET_START_INDEX_METHOD_NAME,
    				 SET_START_INDEX_METHOD_ARG_TYPES);
          } catch (NoSuchMethodException nsme) {
    	                                               
    	Trace.exception(nsme);
          }
        }
      
  }

  /* Overriden method - PROCESS-PLOT-DELETION */
  private void processPlotDeletion(Structure plotStruct)
 {
    
        java.lang.Object uid = plotStruct.getAttributeValue(CHART_ELEMENT_UID_, null);
        HistoryRingBuffer buf =
          (HistoryRingBuffer)((TrendChartData)data).histories.remove(uid);
      
  }

  /* Overriden method - DISPATCH-ADDITION-OR-DELETION */
  private void dispatchAdditionOrDeletion(Symbol attrName_,
					  Structure masterStruct,
					  Symbol modificationCode)
 {
    
        if (TrendChartEvent.ELEMENT_DELETED_.equals(modificationCode) &&
    	PLOTS_.equals(attrName_))
          processPlotDeletion(masterStruct);
        
        Structure infoStruct = new Structure();
        infoStruct.setAttributeValue(ELEMENT_TYPE_, attrName_);
        infoStruct.setAttributeValue(ELEMENT_DATA_, masterStruct);
        TrendChartEvent event =
          new TrendChartEvent(this,
    			  this,
                              -1,                                    
    			  modificationCode,
    			  infoStruct);
        dispatchTrendChartEventToListeners(event);
      
  }

  /* Overriden method - PROPOGATE-ADDITIONS-OR-DELETIONS */
  private void propogateAdditionsOrDeletions(Symbol attrName_,
					     Sequence masterSequence,
					     Sequence slaveSequence,
					     Symbol modificationCode)
 {
    
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

  /* Overriden method - SLOT-IS-MULTIPLE-COMPOUND-SLOT */
  private boolean slotIsMultipleCompoundSlot(Symbol attrName_)
 {
    
        return (PLOTS_.equals(attrName_) ||
    	    CONNECTOR_FORMATS_.equals(attrName_) ||
    	    SystemAttributeSymbols.POINT_FORMATS_.equals(attrName_) ||
    	    VALUE_AXES_.equals(attrName_));
      
  }

  /* Overriden method - DETECT-AND-PROPOGATE-ADDITIONS-AND-DELETIONS */
  private void detectAndPropogateAdditionsAndDeletions(ItemEvent e)
 {
    
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

  /* Overriden method - PROCESS-ITEM-EVENT */
  @Override
  public void processItemEvent(ItemEvent e)
 {
    
        detectAndPropogateAdditionsAndDeletions(e);
                                                                
                                      
        super.processItemEvent(e);
      
  }

  /* Overriden method - MAKE-DATA-FOR-ITEM */
  @Override
  protected ItemData makeDataForItem()
 {
    
        return new TrendChartData();
      
  }

  /* Overriden method - DISPATCH-TREND-CHART-EVENT-TO-LISTENERS */
  private void dispatchTrendChartEventToListeners(TrendChartEvent event)
 {
    
        if (((TrendChartData)data).trendChartListener != null)
          ((TrendChartData)data).trendChartListener.processTrendChartEvent(event);
      
  }

  /* Overriden method - PROCESS-TREND-CHART-EVENT */
  @Override
  public void processTrendChartEvent(TrendChartEvent event)
 {
    
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

  /* Overriden method - RETRIEVE-STATE */
  protected Structure retrieveState()
 {
    
        TrendChartData tcData = (TrendChartData)data;
        Structure state = new Structure();
        Structure initialData = new Structure();
        
        initialData.setAttributeValue(TIMESPAN_, getTimespan());
                                                            
                                                                 
                                                             
                     
        initialData.setAttributeValue(PROCESSED_PLOT_DATA_,
    				  ((TrendChartData)data).
    				  histories.clone());
        initialData.setAttributeValue(VALUE_AXIS_EXTREMA_,
        				  getValueAxisExtrema());
        initialData.setAttributeValue(TREND_CHART_ACTIVE_,
    				  new Boolean(getActivationState()));
                                                                      
                                 
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

  /* Overriden method - ADD-TREND-CHART-LISTENER-RETRIEVING-STATE */
  @Override
  public Structure addTrendChartListenerRetrievingState
  (TrendChartListener listener) throws G2AccessException
 {
    
        synchronized (data) { //tcData
          addTrendChartListener(listener);
          return retrieveState();
        }
      
  }

  /* Overriden method - INITIATE-SUBSCRIPTIONS */
  private void initiateSubscriptions() throws G2AccessException
 {
    
        synchronized (data) {          
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
    	  
    	                                                               
    	                                                               
    	                        
    	  Hashtable histories =
    	    (Hashtable)initialInfo.getAttributeValue(PROCESSED_PLOT_DATA_, null);
    	  if (histories != null)
    	    tcData.histories = histories;
    	  else {                                                              
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

  /* Overriden method - REPRESENT-TREND-CHART */
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

  /* Overriden method - CLEAR-HISTORIES */
  private void clearHistories()
 {
    
        for (Enumeration en = ((TrendChartData)data).histories.elements();
        	 en.hasMoreElements();)
          ((HistoryRingBuffer)en.nextElement()).clear();
      
  }

  /* Overriden method - ADJUST-PLOT-HISTORIES */
  private void adjustPlotHistories(long timeDelta)
 {
    
        for (Enumeration en = ((TrendChartData)data).histories.elements();
    	 en.hasMoreElements();)
          ((HistoryRingBuffer)en.nextElement()).adjustTimestamps(timeDelta);
      
  }

  /* Overriden method - PROCESS-CLOCK-DISCONTINUITY */
  private void processClockDiscontinuity(Structure newInfo)
 {
    
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

  /* Overriden method - PROCESS-PLOT-DATA */
  private void processPlotData(Sequence plotDataSequence)
  throws NoSuchAttributeException
 {
    
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

  
}
