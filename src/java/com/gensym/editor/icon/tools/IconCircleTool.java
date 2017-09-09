package com.gensym.editor.icon.tools;

import java.awt.*;
import java.awt.event.*;
import java.lang.Math;
import com.gensym.editor.icon.shapes.IconOval;
import com.gensym.editor.icon.core.ToolContainer;

/**
 */
public class IconCircleTool extends ChangeTool
implements MouseListener, MouseMotionListener
{

  protected int start_x;
  protected int start_y;
  protected int current_x;
  protected int current_y;
  protected Color color;
  protected boolean mouse_is_down = false;
  protected ToolContainer parent;
  protected boolean filled = false;

  public IconCircleTool (ToolContainer parent)
  {
    super(parent);
    listenerTypes = MOUSELISTENER | MOUSEMOTIONLISTENER;
    this.parent = parent;
    color = parent.current_color;
  }

  public void setFilled(boolean filled)
  {
    this.filled = filled;
  }
  
  @Override
  public void Draw (Graphics g)
  {
     if (mouse_is_down)
     {
       g.setColor(parent.current_color);
       int xRadius = Math.abs(current_x - start_x);
       int yRadius = Math.abs(current_y - start_y);
       int radius =  (int)Math.sqrt(xRadius*xRadius + yRadius*yRadius);
       g.drawOval(start_x-radius, start_y-radius, 2*radius-1, 2*radius-1);
     }
  }

  @Override
  public void mouseClicked(MouseEvent e) {}
  @Override
  public void mousePressed(MouseEvent e)
  {
    super.mousePressed(e);
     Point p = e.getPoint();
     int x = p.x;
     int y = p.y;

     mouse_is_down = true;
     start_x = x;
     start_y = y;
     current_x = x;
     current_y = y;
  }
  
  @Override
  public void mouseReleased(MouseEvent e)
  {
    if (e.isPopupTrigger()) {
      super.mouseReleased(e);
      return;
    }
     Point p = e.getPoint();
     int x = p.x;
     int y = p.y;

     if (mouse_is_down)
      {
          int shift_x = 0;
          int shift_y = 0;
	  int xRadius = Math.abs(current_x - start_x);
	  int yRadius = Math.abs(current_y - start_y);
	  int radius = (int) Math.sqrt(xRadius*xRadius + yRadius*yRadius);
          parent.addElement(new IconOval(start_x,start_y,radius, radius, filled));
          mouse_is_down = false;
      }
  }

  @Override
  public void mouseEntered(MouseEvent e)
  {
  }
   
  @Override
  public void mouseExited(MouseEvent e)
  {
  }

  @Override
  public void mouseDragged(MouseEvent e)
  {
    Point p = e.getPoint();
    int x = p.x;
    int y = p.y;
    int xRadius = Math.abs(current_x - start_x);
    int yRadius = Math.abs(current_y - start_y);
    int radius =  (int)Math.sqrt(xRadius*xRadius + yRadius*yRadius);
    
    
    if (mouse_is_down)
    {
      parent.invalidate(new Rectangle[]
			{new Rectangle(start_x-radius-1, start_y-radius-1,
				       2*radius+2, 2*radius+2)});
      current_x = x;
      current_y = y;
      xRadius = Math.abs(current_x - start_x);
      yRadius = Math.abs(current_y - start_y);
      radius =  (int)Math.sqrt(xRadius*xRadius + yRadius*yRadius);
      parent.invalidate(new Rectangle[]
			{new Rectangle(start_x-radius-1, start_y-radius-1,
				       2*radius+2, 2*radius+2)});
    }
  }
   
  @Override
  public void mouseMoved(MouseEvent e)
  {
  }

  
}

