package com.gensym.draw;

import java.awt.*;

/**
 *
 * DrawElements must call setLocation and setSize in their constructors.  
 *
 */

public interface DrawElement
{
  public abstract Rectangle[] getExactBounds ();

  /* shift must call setLocation somewhere in its body */
  public abstract void shift (int shift_x, int shift_y);

  public abstract void setCanvas(PersistentCanvas canvas);

  public abstract void changeColor(Object logicalColor, Color color);
  public abstract void changeColor(Object logicalColor, Object colorKey);
  public abstract Object[] getLogicalColors();
}

