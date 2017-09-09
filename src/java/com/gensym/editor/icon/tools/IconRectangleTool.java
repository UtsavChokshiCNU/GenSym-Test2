package com.gensym.editor.icon.tools;

import com.gensym.editor.icon.shapes.IconRectangle;
import java.awt.*;
import java.awt.event.*;
import com.gensym.editor.icon.core.ToolContainer;
import java.lang.Math;

/**
 */
public class IconRectangleTool extends ChangeTool
                      implements MouseListener, MouseMotionListener
{
  protected int start_x;
  protected int start_y;
  protected int current_x;
  protected int current_y;
  protected Color color;
  protected boolean mouse_is_down = false;
  protected ToolContainer parent;
  private boolean filled = false;  

  public IconRectangleTool (ToolContainer parent)
  {
    super(parent);
    listenerTypes = MOUSELISTENER | MOUSEMOTIONLISTENER;
    this.parent = parent;
    color = parent.current_color;
  }

  @Override
  public void Draw (Graphics g)
  {
     if (mouse_is_down)
     {
       g.setColor(parent.current_color);
       g.drawRect(Math.min(current_x,start_x),
                  Math.min(current_y,start_y),
                  Math.abs(current_x - start_x), 
                  Math.abs(current_y - start_y));
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
    
    if (mouse_is_down)
    {
      parent.invalidate(new Rectangle[] {new Rectangle(Math.min(current_x,start_x) - 1,
						       Math.min(current_y,start_y) - 1,
						       Math.abs(current_x - start_x) + 2, 
						       Math.abs(current_y - start_y) + 2)});
      current_x = x;
      current_y = y;
      parent.invalidate(new Rectangle[] {new Rectangle(Math.min(x,start_x) - 1 ,
						       Math.min(y,start_y) - 1 ,
						       Math.abs(x - start_x) + 2 , 
						       Math.abs(y - start_y) + 2)});
    }
  }
   
  @Override
  public void mouseMoved(MouseEvent e)
  {
  }

  public void setFilled(boolean filled)
  {
    this.filled = filled;
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

     if (mouse_is_down) {
       mouse_is_down = false;	 
       IconRectangle elt = new IconRectangle(Math.min(x,start_x),
					     Math.min(y,start_y),
					     Math.abs(x - start_x)+1 , 
					     Math.abs(y - start_y)+1,
					     filled);
       parent.addElement(elt);
       //parent.repaint();
     }
  }
  
}


