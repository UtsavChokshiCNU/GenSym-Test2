/*
 * @(#)ItemData.java	1.0 97/11/05
 * 
 * Copyright (c) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 
 */
package com.gensym.classes;

import java.util.Hashtable;
import com.gensym.ntw.util.TrendChartEvent;
import com.gensym.ntw.util.TrendChartListener;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;

/**
 * A package private class that is used to hold the data in a G2
 * KbTrendChart stub. This facilitates 3-tier operation where a number
 * of copies of the stub may be created by deserialization. The
 * data for the item is held in a ItemData kept in a hashtable.
 *
 * @version    1.00 11/07/97
 * @author     rpenny
 */
public class TrendChartData extends ItemData {

  public volatile TrendChartListener trendChartListener;

  public volatile boolean alreadySubscribed;

  // performance: separate this structure into two variables,
  // endTime and timespan
  public volatile Structure timeSpanInfo;

  public volatile long timeSpan;

  public volatile Sequence valueAxisExtrema;

  public volatile Sequence initialData;

  public volatile boolean activationState;

  public volatile Integer tcSubscrpnHandle;

  public volatile long lastUpdateTime;

  public Hashtable histories = new Hashtable();
  
}
