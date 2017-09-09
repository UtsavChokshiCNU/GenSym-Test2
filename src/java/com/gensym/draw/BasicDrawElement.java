package com.gensym.draw;

import java.awt.*;


public class BasicDrawElement extends Component
       implements DrawElement
{

  static final long serialVersionUID = -5271259677323826705L;
  protected transient PersistentCanvas canvas = null;

  public void paint (Graphics g, int shift_x, int shift_y)
  {

  }

  @Override
  public void paint(Graphics g)
  {
  }

  @Override
  public void setCanvas(PersistentCanvas canvas)
  {
    this.canvas = canvas;
  }

  @Override
  public void changeColor(Object logicalColor, Color color)
  {

  }

  @Override
  public void changeColor(Object logicalColor, Object colorKey)
  {

  }

  @Override
  public Object[] getLogicalColors()
  {
    Object[] logicalColors = new Object[1];
    logicalColors[0] = "fill";
    return logicalColors;
  }

  @Override
  public Rectangle[] getExactBounds ()
  {
    Rectangle[] res = new Rectangle[1];
    res[0] = new Rectangle(0 , 0, 100, 100);

    return res;
  }

  @Override
  public void shift (int shift_x, int shift_y)
  {
  }

  @Override
  public boolean inside(int logical_x, int logical_y)
  {
    return false;
  }


  // can we use container events instead??
  @Override
  public void addNotify () 
  {
    super.addNotify();
  }

  @Override
  public Container getParent () {
    return canvas;
  }

}


