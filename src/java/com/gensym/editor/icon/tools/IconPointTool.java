package com.gensym.editor.icon.tools;

import com.gensym.editor.icon.shapes.IconPoint;
import java.awt.*;
import java.awt.event.*;
import com.gensym.editor.icon.core.ToolContainer;
import java.lang.Math;

/**
 */
public class IconPointTool extends ChangeTool
implements MouseListener, MouseMotionListener
{
  private boolean filled = false;
  protected int start_x, start_y;
  protected Color color;
  protected boolean mouse_is_down = false;
  protected ToolContainer parent;
  private IconPoint draggingElement;
  
  public IconPointTool (ToolContainer parent)
  {
    super(parent);
    this.parent = parent;
    listenerTypes = MOUSELISTENER | MOUSEMOTIONLISTENER;
    color = parent.current_color;
  }

  @Override
  public void mouseReleased(MouseEvent e)
  {
    if (e.isPopupTrigger()) {
      super.mouseReleased(e);
      return;
    }
    if (mouse_is_down) // Why would it be otherwise?
      {
	int shift_x = 0;
	int shift_y = 0;
	IconPoint elt = new IconPoint(start_x - shift_x, 
				      start_y - shift_y);
	parent.addElement(elt);	   
	mouse_is_down = false;
      }
  }

  @Override
  public void mouseDragged(MouseEvent e){}
  @Override
  public void mousePressed(MouseEvent e)
  {
    super.mousePressed(e);
     Point p = e.getPoint();
     mouse_is_down = true;
     start_x = p.x;

     start_y = p.y;
  }
  @Override
  public void Draw (Graphics g)
  {
  }  
}

