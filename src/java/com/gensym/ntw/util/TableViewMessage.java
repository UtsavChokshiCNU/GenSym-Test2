/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TableViewMessage.java
 *
 */

package com.gensym.ntw.util;

import java.awt.Color;

interface TableViewMessage{

  public Object[] getRowValues();
  public void setValueAt(int i, Object aValue);
  public Color getBackgroundColor();
  public Color getForegroundColor();

}
