package com.gensym.draw;

import java.awt.*;
/*
 *
 * DumbDrawLine
 *
 */
public class LineElement extends BasicDrawElement
{
  static final long serialVersionUID = 6514764577032596608L;
  private int x1;
  private int y1;
  private int x2;
  private int y2;
  private Color color;
  private Rectangle[] bounds;

  public LineElement (Color color_arg, int x1, int y1, int x2, int y2)
  {
    int low_x = x1, high_x = x2;
    int low_y = y1, high_y = y2; 

    this.x1 = x1; this.y1 = y1;
    this.x2 = x2; this.y2 = y2;

    if (x1 > x2) 
      {
	low_x = x2;
	high_x = x1;
      }
    if (y1 > y2)
      {
	low_y = y2;
	high_y = y1;
      }
    bounds = new Rectangle[1];
    int xExtra = (high_x == low_x ? 1 : 0);
    int yExtra = (high_y == low_y ? 1 : 0);
    bounds[0] = new Rectangle(low_x, low_y,
			      high_x - low_x + xExtra, high_y - low_y + yExtra);
    setLocation(low_x,low_y);
    setSize(high_x - low_x + xExtra, high_y - low_y + yExtra);
    color = color_arg;
  }

  public void changeColor(Color color) {
    this.color = color;
    canvas.invalidateElement(this);
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
  public void shift (int shift_x, int shift_y)
  {
    x1 += shift_x;
    y1 += shift_y;
    x2 += shift_x;
    y2 += shift_y;
    Rectangle rect = bounds[0];
    rect.translate(shift_x, shift_y);
    setLocation(rect.x, rect.y);
  }

  @Override
  public boolean contains(int logical_x, int logical_y)
  {
    return false;
  }

  @Override
  public synchronized void paint (Graphics g, int shift_x, int shift_y)
  {
    Rectangle rect = bounds[0];
    g.setColor(color);
    g.drawLine(x1 - rect.x ,y1 - rect.y,
	       x2 - rect.x ,y2 - rect.y);
  }

  @Override
  public void paint (Graphics g)
  {
    paint(g,0,0);
  }

  @Override
  public String toString () {
    return ("LineElement [" + color + ", (" + x1 + "," + y1 + ")->(" + x2 + "," + y2 + ")");
  }

  @Override
  public Rectangle[] getExactBounds ()
  {
    return bounds;
  }


}


