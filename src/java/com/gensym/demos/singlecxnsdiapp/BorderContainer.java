
package com.gensym.demos.singlecxnsdiapp;

import java.awt.*;

public class BorderContainer extends Container {

  public BorderContainer (Component nestedComponent) {
    setLayout (new BorderLayout ());
    add (nestedComponent, BorderLayout.CENTER);
  }

  @Override
  public void paint (Graphics g) {
    Dimension d = getSize ();
    int w = d.width, h = d.height;
    g.setColor (Color.black);
    g.drawLine (1, 1, w - 2, 1); g.drawLine (1, 1, 1, h - 2);
    g.setColor (Color.gray);
    g.drawLine (0, 0, w, 0); g.drawLine (0, 0, 0, h);
    g.setColor (Color.white);
    g.drawLine (w - 1, 0, w - 1, h - 1); g.drawLine (w - 1, h - 1, 0, h - 1);
    g.setColor (Color.lightGray);
    g.drawLine (w - 2, 1, w - 2, h - 2); g.drawLine (w - 2, h - 2, 1, h - 2);
    super.paint (g);
  }
  
  @Override
  public Insets getInsets () {
    return stdBorderInsets;
  }
  private final Insets stdBorderInsets = new Insets (2, 2, 2, 2);
  
}
