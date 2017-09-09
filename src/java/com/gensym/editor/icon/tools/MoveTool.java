package com.gensym.editor.icon.tools;

import java.awt.*;
import java.awt.event.*;
import java.lang.Math;
import com.gensym.editor.icon.core.Tool;
import com.gensym.editor.icon.core.ToolContainer;

public class MoveTool extends ChangeTool
                      implements MouseListener, MouseMotionListener
{
  private int start_x;
  private int start_y;
  private Rectangle[] bounds;
  private int current_x;
  private int current_y;
  private Color color;
  private boolean mouse_is_down = false;
  private Component element;

  public MoveTool (ToolContainer parent)
  {
    super(parent);
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
  public void registerListeners(ToolContainer parent)
  {
    super.registerListeners(parent);
    parent.addMouseMotionListener(this);
  }

  @Override
  public void deregisterListeners(ToolContainer parent)
  {
    super.deregisterListeners(parent);
    parent.removeMouseMotionListener(this);
  }

  @Override
  public void mouseClicked(MouseEvent e)
  {
  }


  @Override
  public void mousePressed(MouseEvent e)
  {
    super.mousePressed(e);
    Point p = e.getPoint();
    int x = p.x;
    int y = p.y;

    element = parent.findElement(x,y);
         
    // System.out.println("found-element="+element+"at ("+x+", "+y+")");
    int shift_x = 0; int shift_y = 0;

    if (element != null)
    {
      mouse_is_down = true;
      start_x = x;
      start_y = y;
      current_x = x;
      current_y = y;
      Rectangle[] element_bounds = new Rectangle[] {element.getBounds()};
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
          int i;
          Rectangle[] old_bounds = new Rectangle[] {element.getBounds()};
          int length = old_bounds.length;
          for (i=0 ; i<length ; i++)
              parent.invalidate(new Rectangle[]{new Rectangle(shift_x + old_bounds[i].x - 1,
							      shift_y + old_bounds[i].y - 1,
							      old_bounds[i].width + 1, 
							      old_bounds[i].height + 1)});

	  if (element instanceof com.gensym.editor.icon.core.DrawElement)
	    ((com.gensym.editor.icon.core.DrawElement)element).shift(x - start_x, y - start_y);

          Rectangle new_bounds[] = new Rectangle[] {element.getBounds()};
          length = new_bounds.length;
          for (i=0 ; i<length ; i++)
            parent.invalidate(new Rectangle[]{new Rectangle(shift_x + new_bounds[i].x - 1,
							    shift_y + new_bounds[i].y - 1,
							    new_bounds[i].width + 2,       
							    new_bounds[i].height + 2)});
          
          mouse_is_down = false;
      }
  }
 

  @Override
  public void mouseEntered(MouseEvent e)
  {
    parent.pushCursor(Cursor.getPredefinedCursor(Cursor.MOVE_CURSOR));
  }
   
  @Override
  public void mouseExited(MouseEvent e)
  {
    parent.popCursor();
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
         parent.invalidate(new Rectangle[] {new Rectangle(bounds[i].x - 1,
							  bounds[i].y - 1,
							  bounds[i].width + 2, 
							  bounds[i].height + 2)});
         bounds[i].translate(x - current_x, y - current_y);
       }
       current_x = x;
       current_y = y;

       for (i=0 ; i<length ; i++)
         parent.invalidate(new Rectangle[] {new Rectangle(bounds[i].x - 1,
							  bounds[i].y - 1,
							  bounds[i].width + 2, 
							  bounds[i].height + 2)});
    }
  }
   
  @Override
  public void mouseMoved(MouseEvent e)
  {
  }
  

}

