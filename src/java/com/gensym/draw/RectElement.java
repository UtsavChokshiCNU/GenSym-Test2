package com.gensym.draw;

import java.awt.*;

/*
 *
 * DumbDrawRect
 *
 */
public class RectElement extends BasicDrawElement
{
  static final long serialVersionUID = -2963483429691705700L;
  private Color color;
  private Rectangle[] bounds;

  public RectElement (Color color_arg, int x, int y, int w, int h)
  {
    bounds = new Rectangle[1];
    bounds[0] = new Rectangle(x,y,w,h);
    setLocation(x,y);
    setSize(w,h);
    color = color_arg;
  }

  @Override
  public synchronized void paint (Graphics g, int shift_x, int shift_y)
  {
    Rectangle b_rect = bounds[0];
    g.setColor(color);
    g.fillRect(shift_x, shift_y,
	       b_rect.width, b_rect.height);
  }

  @Override
  public synchronized void paint (Graphics g)
  {
    paint(g,0,0);
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

  /* coordinates are local to component */
  @Override
  public boolean contains(int x, int y)
  {
    Rectangle theBounds = bounds[0];
    return theBounds.contains(x + theBounds.x ,y + theBounds.y);
  }

  @Override
  public void shift (int shiftX, int shiftY)
  {
    Rectangle rect = bounds[0];
    rect.translate(shiftX,shiftY);
    setLocation(rect.x, rect.y);
  }
    
  @Override
  public Rectangle[] getExactBounds ()
  {
     return bounds;
  }

  @Override
  public void setBounds(Rectangle bounds){
    setBounds(bounds.x, bounds.y, bounds.width, bounds.height);
  }

  @Override
  public void setBounds(int x, int y, int width, int height){
    Rectangle rect = bounds[0];
    rect.x = x;
    rect.y = y;
    rect.width = width;
    rect.height = height;
    super.setBounds(x, y, width, height);
  }

  @Override
  public void setLocation(Point location){
    setLocation(location.x, location.y);
  }

  @Override
  public void setLocation(int x, int y){
    Rectangle rect = bounds[0];
    rect.x = x;
    rect.y = y;
    super.setLocation(x, y);
  }

  @Override
  public void setSize(Dimension size){
    setSize(size.width, size.height);
  }

  @Override
  public void setSize(int width, int height){
    Rectangle rect = bounds[0];
    rect.width = width;
    rect.height = height;
    super.setSize(width, height);
  }


}



