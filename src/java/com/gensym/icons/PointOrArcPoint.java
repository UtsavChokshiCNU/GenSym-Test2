package com.gensym.icons;

import java.util.*;
import java.awt.*;
import com.gensym.util.*;
import com.gensym.message.*;


public class PointOrArcPoint extends Point {

  public boolean arcPoint = false;

  public PointOrArcPoint(int x, int y) {
    super(x,y);
    arcPoint = false;
  }

  public PointOrArcPoint(int x, int y, boolean arcPoint) {
    super(x,y);
    this.arcPoint = arcPoint;
  }
}
