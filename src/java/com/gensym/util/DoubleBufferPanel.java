package com.gensym.util;
import java.awt.*;

public class DoubleBufferPanel extends Panel {    
  static final long serialVersionUID = 5080179455641891147L;
  transient Image offscreen;

  /**
   * null out the offscreen buffer as part of invalidation
   */
  @Override
  public void invalidate() {
      super.invalidate();
      offscreen = null;
  }

  /**
   * override update to *not* erase the background before painting
   */
  @Override
  public void update(Graphics g) {
      paint(g);
  }

  /**
   * paint children into an offscreen buffer, then blast entire image
   * at once.
   */
  @Override
  public void paint(Graphics g) {
      if(offscreen == null) {
         offscreen = createImage(getSize().width, getSize().height);
      }
      Graphics og = offscreen.getGraphics();
      og.setClip(g.getClip());
      og.setColor(getBackground());
      Dimension size = getSize();
      og.fillRect(0,0, size.width, size.height);
      super.paint(og);
      g.drawImage(offscreen, 0, 0, null);
      og.dispose();
  }
}
