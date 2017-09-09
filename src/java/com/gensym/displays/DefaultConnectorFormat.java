/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DefaultConnectorFormat.java
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.displays;

import java.awt.Color;

/** A pre-initialized version that acts as the default version
 * in a chart. All important slots are initialized to be non-null;
 */
class DefaultConnectorFormat extends ConnectorFormat {

  public DefaultConnectorFormat(TrendChart chart) {
    super(chart, null, DEFAULT_);
    connectorInterpolation = LINEAR_OBJ;
    connectorShadingTarget = NONE_OBJ;
    connectorLineColor = Color.black;
  }

  @Override
  public void configure(Chart genericChart) {
  }
}
