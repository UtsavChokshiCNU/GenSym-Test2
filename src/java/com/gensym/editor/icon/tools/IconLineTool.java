package com.gensym.editor.icon.tools;

import com.gensym.editor.icon.shapes.IconLine;
import java.awt.*;
import java.awt.event.*;
import java.lang.Math;
import com.gensym.editor.icon.core.ToolContainer;

/**
 */
public class IconLineTool extends ChangeTool
implements MouseListener, MouseMotionListener
{
  private boolean filled = false;
  protected int start_x, start_y, current_x, current_y;
  protected Color color;
  protected boolean mouse_is_down = false;
  protected ToolContainer parent;

  public IconLineTool (ToolContainer parent)
  {
    super(parent);
    this.parent = parent;
    listenerTypes = MOUSELISTENER | MOUSEMOTIONLISTENER;
    color = parent.current_color;
  }

  @Override
  public void Draw (Graphics g)
  {
     if (mouse_is_down)
     {
       g.setColor(parent.current_color);
         g.drawLine(start_x, start_y,
                  current_x, current_y);
     }

  }

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
    
    if (mouse_is_down) // Why would it be otherwise?
      {
	int shift_x = 0;
	int shift_y = 0;
	IconLine elt = new IconLine(start_x - shift_x, 
				    start_y - shift_y, 
				    x - shift_x, 
				    y - shift_y);
	parent.addElement(elt);	   
	mouse_is_down = false;
      }
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
  
}


