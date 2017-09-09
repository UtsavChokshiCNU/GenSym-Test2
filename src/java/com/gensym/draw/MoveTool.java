package com.gensym.draw;

import java.awt.*;
import java.awt.event.*;
import java.lang.Math;

/*
 *
 * DumbDrawMoveTool
 *
 */
public class MoveTool extends EventHandler
                      implements MouseListener, MouseMotionListener
{
  private int start_x;
  private int start_y;
  private Rectangle[] bounds;
  private int current_x;
  private int current_y;
  private Color color;
  private boolean mouse_is_down = false;
  private PersistentCanvas canvas;
  private Component element;
  private Cursor originalCursor;

  public MoveTool (PersistentCanvas parent)
  {
    canvas = parent;
    color = parent.current_color;
    listenerTypes = MOUSELISTENER | MOUSEMOTIONLISTENER;
  }

  @Override
  public void Draw (Graphics g)
  {
     if (mouse_is_down)
     {
       g.setColor(Color.black);
       int length = bounds.length;
       for (int i = 0 ; i<length ; i++)
           g.drawRect(bounds[i].x, bounds[i].y,
                    bounds[i].width, bounds[i].height);
     }

  }


  @Override
  public void registerListeners(PersistentCanvas canvas)
  {
      canvas.addMouseListener(this);
      canvas.addMouseMotionListener(this);
      
      /*
      Cursor move_cursor = Cursor.getPredefinedCursor(Cursor.MOVE_CURSOR);
      originalCursor = canvas.getCursor();
      System.out.println("cursor="+canvas.getCursor());
      System.out.println("canvasPeer="+canvas.getPeer());
      System.out.println("hellooooooooooooooo");
      canvas.setCursor(move_cursor);
      */
  }

  @Override
  public void deregisterListeners(PersistentCanvas canvas)
  {
      canvas.removeMouseListener(this);
      canvas.removeMouseMotionListener(this);
      // canvas.setCursor(originalCursor);
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

    element = canvas.findElement(x,y);
         
    // System.out.println("found-element="+element+"at ("+x+", "+y+")");
    int shift_x = /* canvas.horizontal_state.logical_min */ 0 -
                        canvas.horizontal_state.view_min;
    int shift_y = /* canvas.vertical_state.logical_min */ 0 -
                        canvas.vertical_state.view_min;

    if (element != null)
    {
      mouse_is_down = true;
      start_x = x;
      start_y = y;
      current_x = x;
      current_y = y;
      Rectangle[] element_bounds = canvas.elementExactBounds(element);
      /* copy to be independent of bounds stored in element */
      int length = element_bounds.length;
      bounds = new Rectangle[length];
      for (int i = 0 ; i<length ; i++)
      {
        bounds[i] = new Rectangle(element_bounds[i].x,
                                  element_bounds[i].y,
                                  element_bounds[i].width, 
                                  element_bounds[i].height);
        bounds[i].translate(shift_x,shift_y);
      }      
    }
  }
  

  @Override
  public void mouseReleased(MouseEvent e)
  {
    Point p = e.getPoint();
    int x = p.x;
    int y = p.y;

    if (mouse_is_down)
      {
          int shift_x = /* canvas.horizontal_state.logical_min */ 0 -
                        canvas.horizontal_state.view_min;
          int shift_y = /* canvas.vertical_state.logical_min */ 0 -
                        canvas.vertical_state.view_min;

          int i;
          Rectangle[] old_bounds = canvas.elementExactBounds(element);
          int length = old_bounds.length;
          for (i=0 ; i<length ; i++)
              canvas.repaint(shift_x + old_bounds[i].x - 1,
                           shift_y + old_bounds[i].y - 1,
                           old_bounds[i].width + 1, 
                             old_bounds[i].height + 1);
          
          canvas.shiftElement(element, x - start_x, y - start_y);

          Rectangle new_bounds[] = canvas.elementExactBounds(element);
          length = new_bounds.length;
          for (i=0 ; i<length ; i++)
            canvas.repaint(shift_x + new_bounds[i].x - 1,
                           shift_y + new_bounds[i].y - 1,
                           new_bounds[i].width + 1,       
                             new_bounds[i].height + 1);
          
          mouse_is_down = false;
      }
  }
 

  @Override
  public void mouseEntered(MouseEvent e)
  {
    canvas.pushCursor(Cursor.getPredefinedCursor(Cursor.MOVE_CURSOR));
  }
   
  @Override
  public void mouseExited(MouseEvent e)
  {
    canvas.popCursor();
  }

  @Override
  public void mouseDragged(MouseEvent e)
  {
    Point p = e.getPoint();
    int x = p.x;
    int y = p.y;

    if (mouse_is_down)
    {  
       int i,length;
       length = bounds.length;

       for (i=0 ; i<length ; i++)
       {
         canvas.repaint(bounds[i].x - 1,
                        bounds[i].y - 1,
                        bounds[i].width + 2, 
			bounds[i].height + 2);
         bounds[i].translate(x - current_x, y - current_y);
       }
       current_x = x;
       current_y = y;

       for (i=0 ; i<length ; i++)
         canvas.repaint(bounds[i].x - 1,
                        bounds[i].y - 1,
                        bounds[i].width + 2, 
                        bounds[i].height + 2);
    }
  }
   
  @Override
  public void mouseMoved(MouseEvent e)
  {
  }
  

}

