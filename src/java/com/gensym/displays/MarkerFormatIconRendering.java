/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      MarkerFormatIconRendering.java
 */
package com.gensym.displays;

import com.gensym.irm.IconRendering;
import com.gensym.icons.IconDescription;

public class MarkerFormatIconRendering extends IconRendering {
  protected MarkerFormatIconRendering(IconDescription desc) {
    super(desc, desc.getWidth(), desc.getHeight(),
	  IconRendering.NORMAL, null);
  }
}
