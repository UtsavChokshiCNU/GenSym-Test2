package com.gensym.editor.icon.tools;

import com.gensym.editor.icon.shapes.IconPoint;
import java.awt.*;
import java.awt.event.*;
import com.gensym.editor.icon.core.ToolContainer;
import java.lang.Math;

/**
 */
public class AirBrushTool extends ChangeTool
implements MouseListener, MouseMotionListener
{
  protected Color color;
  protected ToolContainer parent;

  public AirBrushTool (ToolContainer parent)
  {
    super(parent);
    this.parent = parent;
    listenerTypes = MOUSELISTENER | MOUSEMOTIONLISTENER;
    color = parent.current_color;
  }

  @Override
  public void Draw (Graphics g)
  {
  }

  private int radius = 4;
  private int density = 8;
  @Override
  public void mouseDragged(MouseEvent e){
    Point p = e.getPoint();
    int cx = p.x, cy = p.y;
    int shift_x = 0;
    int shift_y = 0;

    int x,y;
    cx-=shift_x;
    cy-=shift_y;
    for (int i=0;i<density;i++) {
      int neg = (Math.random()<.5)?-1:1;
      x=cx+neg*((int)(Math.random()*radius*radius/Math.PI));
      neg = (Math.random()<.5)?-1:1;
      y=cy+neg*((int)(Math.random()*radius*radius/Math.PI));
      parent.addElement(new IconPoint(x,y));
    }
  }
   
}


