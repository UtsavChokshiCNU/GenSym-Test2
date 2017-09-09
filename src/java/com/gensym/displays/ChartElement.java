/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      ChartElement.java
 *
 * Description:
 *               One set of information to draw and how to draw it
 *
 *      Author:
 *		Robert Penny		Aug/97
 *
 * Modifications:
 *
 */
package com.gensym.displays;

import java.util.Enumeration;
import com.gensym.util.symbol.TrendChartSymbols;

/** A chart element is one of the elements of a chart such as a plot, an axis,
 * connector-format, or point-format. These are the "models" that contain
 * the configuration data for the "views" that display the visual elements of
 * a trend-chart.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */

public interface ChartElement extends TrendChartSymbols {

  /** This is intended to be used only once after creation. It allows an
   * element to be created independently of a chart then "fit itself to
   * a chart". */
  public void configure(Chart chart);

  public Enumeration getNames();

  public Object getChartElementUid();

  public void dispose();
}
