/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   SpinButton.java 
 * 
 * 
 */ 

package com.gensym.widgets;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Color;

class SpinButton extends LWButton {

  static final long serialVersionUID = 2L;

  private static int LEFT_MARGIN = 4, TOP_MARGIN = 4;
  private boolean up;
  private int arrowHeight, arrowWidth;
  private int widgetWidth;

  SpinButton(boolean up, int arrowWidth, int arrowHeight) {
    this.up = up;
    this.arrowHeight = arrowHeight;
    this.arrowWidth = arrowWidth;
    widgetWidth = arrowWidth + 2*LEFT_MARGIN;
  }

  @Override
  public void setEnabled(boolean yes) {
    super.setEnabled(yes);
    repaint();
  }

  @Override
  public Dimension getPreferredSize() {
    return new Dimension(widgetWidth, 1);
  }

  @Override
  public Dimension getMinimumSize() {
    return new Dimension(widgetWidth, 1);
  }

  @Override
  public Dimension getMaximumSize() {
    return new Dimension(widgetWidth, Short.MAX_VALUE);
  }

  int[] xArray = new int[3], yArray = new int[3];

  @Override
  public void paint(Graphics g) {
    Dimension size = getSize();
    int
      width = size.width, height = size.height,
      arrowTop = height/2 - arrowHeight/2,
      arrowLeft = width/2 - arrowWidth/2,
      drawWidth = arrowWidth, drawHeight = arrowHeight;

    if (up) {
      arrowLeft = arrowLeft - 1;
      arrowTop = arrowTop - 1;
      drawWidth +=2;
      drawHeight++;
    }      

    int arrowBase = up ? arrowTop + drawHeight : arrowTop;
    int arrowTip = up ? arrowTop : arrowTop + drawHeight;

    // starting with the arrowBase
    xArray[0] = arrowLeft;                yArray[0] = arrowBase;
    xArray[1] = arrowLeft + drawWidth;   yArray[1] = arrowBase;
    xArray[2] = arrowLeft + drawWidth/2; yArray[2] = arrowTip;

    super.paint(g);

    Color arrowColor = getForeground();
    arrowColor = isEnabled() ? arrowColor : grayer(arrowColor, 0.5F);
    g.setColor(arrowColor);
    g.fillPolygon(xArray, yArray, 3);
  }

  static Color grayer(Color color, float factor) {
    int red = color.getRed();
    int green = color.getGreen();
    int blue = color.getBlue();

    int base = (int)(255 * factor);

    int newRed = (int)Math.min(255, base - (factor * red - red));
    int newGreen = (int)Math.min(255, base - (factor * green - green));
    int newBlue = (int)Math.min(255, base - (factor * blue - blue));

    return new Color(newRed, newGreen, newBlue);
  }
}
