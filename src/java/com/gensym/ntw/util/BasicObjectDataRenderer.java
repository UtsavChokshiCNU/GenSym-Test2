/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 BasicObjectDataRenderer.java
 *
 */
package com.gensym.ntw.util;

import java.awt.Font;
import javax.swing.Icon;

public interface BasicObjectDataRenderer {
  public void      setTextRepresentation(String text);
  public String    getTextRepresentation();
  public void      setToolTipRepresentation(String tooltip);
  public String    getToolTipRepresentation();
  public void      setIconRepresentation(Icon icon);
  public Icon      getIconRepresentation();
  public void      setFont(Font font);
  public Font      getFont();
}
