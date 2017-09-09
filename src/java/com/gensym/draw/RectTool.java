package com.gensym.draw;

import java.awt.*;
import java.awt.event.*;
import java.lang.Math;

/*
 *
 * DumbDrawRectTool
 *
 */
public class RectTool extends EventHandler
                      implements MouseListener, MouseMotionListener
{
  private int start_x;
  private int start_y;
  private int current_x;
  private int current_y;
  private Color color;
  private boolean mouse_is_down = false;
  private PersistentCanvas parent;

  public RectTool (PersistentCanvas parent)
  {
    this.parent = parent;
    color = parent.current_color;
  }

  @Override
  public void Draw (Graphics g)
  {
     if (mouse_is_down)
     {
       g.setColor(parent.current_color);
         g.fillRect(Math.min(current_x,start_x),
                  Math.min(current_y,start_y),
                  Math.abs(current_x - start_x), 
                  Math.abs(current_y - start_y));
     }

  }

  @Override
  public void registerListeners(PersistentCanvas canvas)
  {
      canvas.addMouseListener(this);
      canvas.addMouseMotionListener(this);
  }

  @Override
  public void deregisterListeners(PersistentCanvas canvas)
  {
      canvas.removeMouseListener(this);
      canvas.removeMouseMotionListener(this);
  }


  @Override
  public void mouseClicked(MouseEvent e)
  {
  }


  @Override
  public void mousePressed(MouseEvent e)
  {
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
     Point p = e.getPoint();
     int x = p.x;
     int y = p.y;

     if (mouse_is_down)
      {
          int shift_x = /* parent.horizontal_state.logical_min */ 0 -
                        parent.horizontal_state.view_min;
          int shift_y = /* parent.vertical_state.logical_min */ 0 -
                        parent.vertical_state.view_min;

          parent.addElement(
              new RectElement(parent.current_color,
                               Math.min(x,start_x) - shift_x ,
                               Math.min(y,start_y) - shift_y,
                               Math.abs(x - start_x) , 
                               Math.abs(y - start_y)));
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

    if (mouse_is_down)
    {
       parent.repaint(Math.min(current_x,start_x) - 1,
                      Math.min(current_y,start_y) - 1,
                      Math.abs(current_x - start_x) + 2, 
                      Math.abs(current_y - start_y) + 2);
       current_x = x;
       current_y = y;
       parent.repaint(Math.min(x,start_x) - 1 ,
                      Math.min(y,start_y) - 1 ,
                      Math.abs(x - start_x) + 2 , 
                      Math.abs(y - start_y) + 2);
    }
  }
   
  @Override
  public void mouseMoved(MouseEvent e)
  {
  }




}


