package com.gensym.uitools.utils;

import javax.swing.JScrollPane;
import java.awt.Component;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;

public class WhiteBackgroundJScrollPane extends JScrollPane {
  public WhiteBackgroundJScrollPane(Component component) {
    super(component);
    setBackground(Color.white);
  }
  
  public WhiteBackgroundJScrollPane() {
    super();
    setBackground(Color.white);
  }

  @Override
  public void paint(Graphics g) {
    g.setColor(getBackground());
    Dimension size = getSize();
    g.fillRect(0,0,size.width, size.height);
    super.paint(g);
  }
}
