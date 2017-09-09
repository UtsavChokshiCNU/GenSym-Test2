package com.gensym.wksp;

import com.gensym.jgi.G2AccessException;
import java.awt.Point;

public interface Editable {
  public void setEditing(boolean editing);
  public void setValue(String newValue)throws InvalidTypeException;
  public int getIndex(Point p);
  public void setIndex(int index);
}
