/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TrendChartListener.java
 *
 *   Description: 
 *     
 *
 *	 Author:
 *		Robert Penny		May/97
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.ntw.util;

/** Interface for TrendChart events.
 * TrendChart events are the change, addition, and deletion of plots, axes,
 * connector formats and marker formats. Also changes to axis bounds and
 * the addition of new data points. A TrendChartListener must be able
 * to listen for these specialized events and also to general events
 * that come due to a trend chart being an "Item".
 */

public interface TrendChartListener extends java.util.EventListener {

  public void processTrendChartEvent(TrendChartEvent event);

}
