package com.gensym.beaneditor;

import com.gensym.draw.*;

public class SizingWidget extends RectElement
{

  static final long serialVersionUID = 8656694383355218934L;

  int direction;
  int exactX;
  int exactY;
  private static final int halfWidth = 3;

  public SizingWidget(int x, int y, int direction)
  {
    super(Preferences.currentPreferences.sizingWidgetLineColor,
	  x - halfWidth, y - halfWidth, 2*halfWidth, 2*halfWidth);
    exactX = x;
    exactY = y;
    this.direction = direction;
  }

}
