package com.gensym.draw;

import java.awt.*;
import java.awt.event.*;
import java.lang.Math;

/*
 *
 * Change Layer Tool
 *
 */
public class ChangeTool extends EventHandler
                      implements MouseListener, ActionListener
{
  private PopupMenu popup;
  private boolean mouse_is_down = false;
  private PersistentCanvas parent;
  private Component element;
  private Color[] colors = { Color.red, Color.orange, Color.yellow,
			     Color.green, Color.cyan, Color.blue,
			     Color.magenta};
  private int colorCounter = 0;

  public ChangeTool (PersistentCanvas parent)
  {
    this.parent = parent;
  }

  @Override
  public void registerListeners(PersistentCanvas canvas)
  {
    canvas.addMouseListener(this);

    MenuItem mi;
    popup = new PopupMenu("Change");

    mi = new MenuItem("Up");
    mi.addActionListener(this);
    popup.add(mi);

    mi = new MenuItem("Down");
    mi.addActionListener(this);
    popup.add(mi);

    popup.addSeparator();

    mi = new MenuItem("Top");
    mi.addActionListener(this);
    popup.add(mi);

    mi = new MenuItem("Bottom");
    mi.addActionListener(this);
    
    popup.add(mi);
        popup.addSeparator();

    mi = new MenuItem("ChangeColor");
    mi.addActionListener(this);
    popup.add(mi);

    mi = new MenuItem("Delete");
    mi.addActionListener(this);
    popup.add(mi);

    parent.add(popup);
           
  }

  @Override
  public void deregisterListeners(PersistentCanvas canvas)
  {
    canvas.removeMouseListener(this);
    parent.remove(popup);
  }

  @Override
  public void actionPerformed(ActionEvent e) 
  {
    String command = e.getActionCommand();

    if (command.equals("Up")) 
      {
      parent.moveElementUp(element);
      } 
      else if (command.equals("Down")) 
      {
      parent.moveElementDown(element);
      } 
      else if (command.equals("Top")) 
      {
      parent.moveElementToTop(element);
      } 
      else if (command.equals("Bottom")) 
      {
       parent.moveElementToBottom(element);
      }
      else if (command.equals("ChangeColor")) 
      {
       setElementColor(element);
      }
      else if (command.equals("Delete")) 
      {
       parent.removeElement(element);
      }
  }

  private void setElementColor(Component element)
  {
    if (element instanceof DrawElement)
      {
        DrawElement drawElement = (DrawElement) element;
	Object[] logicalNames = drawElement.getLogicalColors();
	Object name = logicalNames[colorCounter % logicalNames.length];
	Color color = colors[colorCounter % colors.length];
	colorCounter++;
	drawElement.changeColor(name,color);
      }
  }

  @Override
  public void Draw (Graphics g)
  {
     
  }


  @Override
  public void mouseClicked(MouseEvent e)
  {
    // System.out.println("click isPopupTrig="+e.isPopupTrigger());
  }


  @Override
  public void mousePressed(MouseEvent e)
  {
    Point p = e.getPoint();
    int x = p.x;
    int y = p.y;

    // System.out.println("press isPopupTrig="+e.isPopupTrigger());
    element = parent.findElement(x,y);
    
  }
  

  @Override
  public void mouseReleased(MouseEvent e)
  {
    // System.out.println("release isPopupTrig="+e.isPopupTrigger());
    if (element != null)
    {
      Point p = e.getPoint();
      int x = p.x;
      int y = p.y;

      Component element_at_release = parent.findElement(x,y);

      if ((element == element_at_release) &&
	  e.isPopupTrigger())
	popup.show(parent, x, y);
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

}

