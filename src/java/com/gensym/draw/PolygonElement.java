package com.gensym.draw;

import java.awt.*;

public class PolygonElement extends BasicDrawElement
{
  private Color color;
  private Rectangle[] bounds;
  private int[] xPoints, yPoints, xOffsetPts, yOffsetPts;

  public PolygonElement (Color color_arg, int numPoints, int[] xPts, int[] yPts) {
    int xmin = 100000, ymin = 100000, xmax = -100000, ymax = -100000;
    bounds = new Rectangle[1];
    xPoints = new int[numPoints];
    yPoints = new int[numPoints];
    xOffsetPts = new int[numPoints];
    yOffsetPts = new int[numPoints];
    for (int i=0; i<numPoints; i++) {
      xPoints[i] = xPts[i];
      yPoints[i] = yPts[i];
      xmax = Math.max (xmax, xPts[i]); xmin = Math.min (xmin, xPts[i]);
      ymax = Math.max (ymax, yPts[i]); ymin = Math.min (ymin, yPts[i]);
    }
    bounds[0] = new Rectangle(xmin, ymin, xmax - xmin, ymax - ymin);
    setLocation(xmin,ymin);
    setSize( xmax - xmin, ymax - ymin);
    color = color_arg;
  }

  @Override
  public void paint (Graphics g)
  {
    Rectangle theBounds = bounds[0];
    g.setColor(color);
    for (int i=0; i<xPoints.length; i++) {
      xOffsetPts[i] = xPoints[i] - theBounds.x;
      yOffsetPts[i] = yPoints[i] - theBounds.y;
    }
    g.fillPolygon (xOffsetPts, yOffsetPts, xPoints.length);
  }
  
  @Override
  public void shift (int shift_x, int shift_y)
  {
     bounds[0].x += shift_x;
     bounds[0].y += shift_y;
     for (int i=0; i<xPoints.length; i++) {
       xPoints[i] += shift_x;
       yPoints[i] += shift_y;
     }
     Point location = getLocation();
     setLocation(location.x + shift_x, location.y + shift_y);
  }

  
  @Override
  public void changeColor(Object logicalColor, Color color)
  {
    this.color = color;
    canvas.invalidateElement(this);
  }

  @Override
  public void changeColor(Object logicalColor, Object colorKey)
  {
    Color color =  canvas.getColorTable().lookup(colorKey);
    if (color != null)
      changeColor(logicalColor, color);
  }

  @Override
  public boolean contains(int x, int y)
  {
    Rectangle theBounds = bounds[0];
    return theBounds.contains(x + theBounds.x, y + theBounds.y);
  }

  @Override
  public Rectangle[] getExactBounds ()
  {
     return bounds;
  }


}
