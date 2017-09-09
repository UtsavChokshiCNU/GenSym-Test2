package com.gensym.editor.icon.tools;

import com.gensym.editor.icon.shapes.IconLines;
import java.awt.*;
import java.awt.event.*;
import com.gensym.editor.icon.core.ToolContainer;
import java.lang.Math;
import java.util.Vector;

/**
 */
public class IconLinesTool extends ChangeTool
implements MouseListener, MouseMotionListener
{
  protected int prev_x, prev_y, current_x, current_y;
  protected Color color;
  protected ToolContainer parent;
  protected Vector xPoints = new Vector(),
    yPoints = new Vector();
  protected int pointCount = 0;
  private boolean started = false;

  public IconLinesTool (ToolContainer parent)
  {
    super(parent);
    this.parent = parent;
    listenerTypes = MOUSELISTENER | MOUSEMOTIONLISTENER;
    color = parent.current_color;
  }

  @Override
  public void Draw (Graphics g)
  {
    if (!started) return;
    g.setColor(parent.current_color);
    int x, y, nextX, nextY;
    for (int i=0;i<pointCount-1;i++) {
      x = ((Integer)xPoints.elementAt(i)).intValue();
      y = ((Integer)yPoints.elementAt(i)).intValue();
      nextX = ((Integer)xPoints.elementAt(i+1)).intValue();
      nextY = ((Integer)yPoints.elementAt(i+1)).intValue();
      g.drawLine(x, y, nextX, nextY);
    }
    g.drawLine(prev_x, prev_y, current_x, current_y);
  }

  protected int[] shiftIntegers(Vector integers, int shift)
  {
    int count = integers.size();
    int[] ints = new int[count];
    for (int i=0;i<count;i++){
      ints[i]=((Integer)integers.elementAt(i)).intValue()-shift;
    }
    return ints;
  }
  
  protected void end()
  {
    int shift_x = 0;
    int shift_y = 0;
    parent.addElement
      (new IconLines(pointCount,
		     shiftIntegers(xPoints, shift_x),
		     shiftIntegers(yPoints, shift_y)));

  }

  @Override
  public void mousePressed(MouseEvent e)
  {
    super.mousePressed(e);
    Point p = e.getPoint();
    int x = p.x;
    int y = p.y;
    started = true;
    prev_x = x;
    prev_y = y;
    current_x = x;
    current_y = y;
    xPoints.addElement(new Integer(x));
    yPoints.addElement(new Integer(y));
    pointCount++;
  }
  
  @Override
  public void mouseReleased(MouseEvent e)
  {
    if (e.isPopupTrigger()) {
      super.mouseReleased(e);
      started = false;
      pointCount = 0;
      xPoints=new Vector();
      yPoints=new Vector();
      return;
    }    
    if (e.getClickCount()>1) {
      end();
      started = false;
      pointCount = 0;
      xPoints=new Vector();
      yPoints=new Vector();
    }
  }

  @Override
  public void mouseDragged(MouseEvent e)
  {
    Point p = e.getPoint();
    int x = p.x;
    int y = p.y;
    parent.invalidate(new Rectangle[]
		      {new Rectangle(Math.min(current_x,prev_x) - 1,
				     Math.min(current_y,prev_y) - 1,
				     Math.abs(current_x - prev_x) + 2, 
				     Math.abs(current_y - prev_y) + 2)});
    current_x = x;
    current_y = y;
    parent.invalidate(new Rectangle[]
		      {new Rectangle(Math.min(x,prev_x) - 1 ,
				     Math.min(y,prev_y) - 1 ,
				     Math.abs(x - prev_x) + 2 , 
				     Math.abs(y - prev_y) + 2)});
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
  public void mouseMoved(MouseEvent e)
  {
    Point p = e.getPoint();
    int x = p.x;
    int y = p.y;
    parent.invalidate(new Rectangle[]
		      {new Rectangle(Math.min(current_x,prev_x) - 1,
				     Math.min(current_y,prev_y) - 1,
				     Math.abs(current_x - prev_x) + 2, 
				     Math.abs(current_y - prev_y) + 2)});
    current_x = x;
    current_y = y;
    parent.invalidate(new Rectangle[]
		      {new Rectangle(Math.min(x,prev_x) - 1 ,
				     Math.min(y,prev_y) - 1 ,
				     Math.abs(x - prev_x) + 2 , 
				     Math.abs(y - prev_y) + 2)});
  }
  
}


