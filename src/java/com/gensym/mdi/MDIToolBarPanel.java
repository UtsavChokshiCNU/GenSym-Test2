/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MDIToolBarPanel.java
 *
 */
package com.gensym.mdi;

import java.awt.Graphics;
import java.awt.Dimension;
import java.awt.Color;
import java.awt.FlowLayout;
import javax.swing.JPanel;

/**
 *  A panel to hold a collection of toolbars.  By default, this panel uses a left
 *  aligned FlowLayout and paints an etched lower edge. 
 *
 *  @see com.gensym.mdi.MDIFrame
 *  @see com.gensym.mdi.MDIDocument
 */
public class MDIToolBarPanel extends JPanel{

  public MDIToolBarPanel(){
    setLayout(new FlowLayout(FlowLayout.LEFT, 5, 0));
  }

  @Override
  public void paint (Graphics g) {
    super.paint(g);
    Dimension size = getSize();
    int width = size.width;
    int height = size.height;
    g.setColor (Color.gray);
    g.drawLine (0, height-2, width, height-2);
    g.setColor (Color.white);
    g.drawLine (0, height-1, width, height-1);
  }
}
