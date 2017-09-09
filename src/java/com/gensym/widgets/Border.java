/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   Border.java 
 * 
 * 
 */ 

package com.gensym.widgets;

import java.awt.Component;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Dimension;

// import com.gensym.ntw.util.G2ColorMap;
// import com.gensym.ntw.util.symbol.G2ColorSymbols;

/**
 * Mimics the properties of a UIL-BORDER widget.
 */
public class Border extends Component {

  static final long serialVersionUID = 2L;

  public static int DEFAULT_LINE_WEIGHT = 2;

  private Color dark, light;
  private int lineWeight = DEFAULT_LINE_WEIGHT;

  protected Border(Color dark, Color light, int lineWeight) {
    this.dark = dark;
    this.light = light;
    this.lineWeight = lineWeight;
  }

  public Border(Color dark, Color light) {
    this(dark, light, DEFAULT_LINE_WEIGHT);
  }

  public Border() {
    this(Color.gray, Color.white);
  }

  @Override
  public boolean contains(int x, int y) {
    Dimension size = getSize();
    int right = size.width - 1,
      bottom = size.height - 1;

    boolean
      atLeft = (x >= 0 && x < lineWeight) && (y >= 0 && y <= bottom),
      atRight = (x <= right && x > right - lineWeight) && (y >= 0 && y <= bottom),
      atTop = (y >= 0 && y < lineWeight) && (x >= 0 && x <= right),
      atBottom = (y <= bottom && y > bottom - lineWeight) && (x >= 0 && x <= bottom);

//     System.out.println("x=" + x + ";y=" + y + ";right=" +
// 		       right + ";bottom=" + bottom);
//     System.out.println("left=" + atLeft + ";right=" + atRight +
// 		       ";top=" + atTop + ";bottom=" + atBottom);

    return atLeft || atRight || atTop || atBottom;
  }

  @Override
  public void update(Graphics g) {
    paint(g);
  }

  /**
   * The paint mechanism doesn't take into account different lineWeights.
   */
  @Override
  public void paint(Graphics g) {
    //Thread.dumpStack();
    Dimension size = getSize();
    int width = size.width,
      height = size.height,
      right = width - 1,
      bottom = height - 1;

    g.setColor(dark);
    g.drawRect(0, 0, right - 1, bottom - 1);

    g.setColor(light);
    // counterclockwise:
    g.drawLine(1, 1, 1, bottom - 2);
    g.drawLine(0, bottom, right, bottom);
    g.drawLine(right, bottom, right, 0);
    g.drawLine(right - 2, 1, 1, 1); // closepath
  }
}
