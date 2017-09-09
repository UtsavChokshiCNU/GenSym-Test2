package com.gensym.beaneditor;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Panel;
import java.awt.FlowLayout;
import java.awt.Dimension;

class BeanToolBarPanel extends Panel{
  BeanToolBarPanel(){
    setLayout(new FlowLayout(FlowLayout.LEFT));
    setBackground(Color.lightGray);
  }

  @Override
  public void paint (Graphics g) {
    super.paint(g);
    Dimension size = getSize();
    int width = size.width;
    int height = size.height;
    g.setColor (Color.gray);
    g.drawLine (0, 0, width, 0);
    g.drawLine (0, height-2, width, height-2);
    g.setColor (Color.white);
    g.drawLine (0, height-1, width, height-1);
    g.drawLine (0, 1, width, 1);
  }
}
