package com.gensym.draw;

import java.awt.*;

/*
 *
 * DumbDrawColorButton
 *
 */
public class DumbDrawColorButton extends Button
{
  private PersistentCanvas parent;
  private Color color;

  public DumbDrawColorButton(PersistentCanvas parent, String color_name,
                       Color color)
  {
      super(color_name);
      this.parent = parent;
      this.color = color;
  }
 
  public Color getColor()
  {
    return color;
  }
}


