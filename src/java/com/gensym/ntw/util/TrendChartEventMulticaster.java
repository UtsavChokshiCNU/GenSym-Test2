/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TrendChartEventMulticaster.java
 *
 *  Description:
 *               A TrendChart multicaster implementation
 *
 *	 Author:
 *		Robert Penny		Oct/97
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.ntw.util;

import java.awt.AWTEventMulticaster;
import java.util.EventListener;

public class TrendChartEventMulticaster extends AWTEventMulticaster
implements TrendChartListener{

  protected TrendChartEventMulticaster(TrendChartListener a,
				       TrendChartListener b) {
    super(a, b);
  }

  /** 
   * Returns the resulting multicast listener from adding listener-a
   * and listener-b together.  
   * If listener-a is null, it returns listener-b;  
   * If listener-b is null, it returns listener-a
   * If neither are null, then it creates and returns
   * a new TrendChartEventMulticaster instance which chains a with b.
   * @param a event listener-a
   * @param b event listener-b
   */
  protected static TrendChartListener
  addInternal(TrendChartListener a, TrendChartListener b)
  {
    if (a == null){
    	return b;
    }
    if (b == null){
    	return a;
    }
    return new TrendChartEventMulticaster(a, b);
  }
      
  /**
   * Adds TrendChart-listener-a with TrendChart-listener-b and
   * returns the resulting multicast listener.
   * @param a TrendChart-listener-a
   * @param b TrendChart-listener-b
   */
  public static TrendChartListener add(TrendChartListener a,
					    TrendChartListener b) {
    return (TrendChartListener)addInternal(a, b);
  }

  /**
   * Removes the old TrendChartEvent-listener from TrendChartEvent-listener-l and
   * returns the resulting multicast listener.
   * @param l TrendChartEvent-listener-l
   * @param oldl the TrendChartEvent-listener being removed
   */
  public static TrendChartListener remove(TrendChartListener l,
					       TrendChartListener oldl) {
    return (TrendChartListener) removeInternal(l, oldl);
  }

  @Override
  public void processTrendChartEvent(TrendChartEvent event) {
    ((TrendChartListener)a).processTrendChartEvent(event);
    ((TrendChartListener)b).processTrendChartEvent(event);
  }

}
