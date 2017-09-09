package com.gensym.beaneditor;

import java.applet.*;
import java.awt.*;
import java.awt.event.*;


class DialogPanel extends Panel implements MouseListener
{
  private int sz = 5;
  private int selectedCorner = -1;

  public int getSelectedCorner()
  {
    return selectedCorner;
  }

  public void setSelectedCorner(int corner)
  {
    selectedCorner = corner;
  }

  @Override
  public void mouseClicked (MouseEvent event)
  {     
  }

  @Override
  public void mousePressed (MouseEvent event)
  {
    int x = event.getX();
    int y = event.getY();
    int width = getSize().width;
    int height = getSize().height;

    if (x > (width/2 - sz/2 - 1) && x < (width/2 + sz/2 + 1) && y > (height - sz - 1))
      selectedCorner = 0;
    else if (x > (width - sz - 1) && y > (height - sz - 1))
      selectedCorner = 1;
    else if (x > (width - sz - 1) && y > (height/2 - sz/2 - 1) && y < (height/2 + sz/2 + 1))
      selectedCorner = 2;
    else
      selectedCorner = -1;

  }

  @Override
  public void mouseReleased (MouseEvent event)
  {
    setSelectedCorner(-1); //no corner selected
  }

  @Override
  public void mouseEntered (MouseEvent event)
  {
  }

  @Override
  public void mouseExited (MouseEvent event)
  {
  }

  @Override
  public synchronized void paint(Graphics g)
  {
    int width = getSize().width;
    int height = getSize().height;

    g.setColor (Color.black);
    g.drawRect (0 + sz, 0 + sz, width - 1 - 2*sz, height - 1 - 2*sz);
    g.setColor (Color.lightGray);
    g.drawRect (0 + sz, 0 + sz, width - 2 - 2*sz, height - 2 - 2*sz);
    g.setColor (Color.gray);
    g.drawRect (1 + sz, 1 + sz, width - 3 - 2*sz, height - 3 - 2*sz);
    g.setColor (Color.white);
    g.drawLine (1 + sz, 1 + sz, 1 + sz, height - 3 - sz);
    g.drawLine (1 + sz, 1 + sz, width - 3 - sz, 1 + sz);

    if (true)
      {
	g.setColor(Color.black);
	g.fillRect(0, 0, sz, sz);
	g.fillRect(width/2 - sz/2, 0, sz, sz);
	g.fillRect(width - sz, 0, sz, sz);
	g.fillRect(width - sz, height/2 - sz/2, sz, sz);
	g.fillRect(0, height - sz, sz, sz);
	g.fillRect(0, height/2 - sz/2, sz, sz);
	g.fillRect(width - sz, height - sz, sz, sz);
	g.fillRect(width/2 - sz/2, height - sz, sz, sz);
      }
 
  }
}
   

