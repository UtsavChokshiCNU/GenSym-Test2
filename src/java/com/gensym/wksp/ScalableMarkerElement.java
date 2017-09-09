package com.gensym.wksp;

import java.awt.Graphics;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.geom.AffineTransform;
import java.awt.geom.NoninvertibleTransformException;
import com.gensym.message.Trace;

class ScalableMarkerElement extends MarkerElement{

  int originalX, originalY;


  ScalableMarkerElement(int locn, int x, int y, int width, int height){
    super(locn, x - width/2, y - width/2, width, height);
    originalX = x;
    originalY = y; 
  }

  @Override
  public void shift (int shiftX, int shiftY){
    originalX = originalX + shiftX;
    originalY = originalY + shiftY;
    super.shift(shiftX, shiftY);
  }

}
