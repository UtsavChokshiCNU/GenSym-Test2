package com.gensym.editor.icon.core;

import java.awt.Rectangle;
import java.awt.Color;

public interface DrawElement {

  public abstract Rectangle[] getExactBounds ();
  public abstract void shift (int shiftX, int shiftY);
  public abstract void setCanvas(ToolContainer canvas);
  public abstract void changeColor(Color color);

}
