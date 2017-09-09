/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      Chart.java
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

/** A chart is able to configure itself based on the g2 chart
 * of which it is a representation.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */


public interface Chart {

  public DataWindow getDataWindow();
}
