package com.gensym.beaneditor;

import java.applet.*;
import java.awt.*;
import java.awt.event.*;


class DrawPanel extends Panel implements MouseListener
{
  public void init()
  {
    setBackground (Color.gray);
    addMouseListener (this);
  }

  @Override
  public void mouseClicked (MouseEvent event)
  {     
  }

  @Override
  public void mousePressed (MouseEvent event)
  {
  }

  @Override
  public void mouseReleased (MouseEvent event)
  {
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

    g.setColor (Color.gray);
    g.drawRect (0, 0, width, height);
    g.setColor (Color.black);
    g.drawRect (1, 1, width - 1, height - 1);
    g.setColor (Color.white);
    g.drawLine (0, height - 1, width - 1, height - 1);
    g.drawLine (width - 1, 0, width - 1, height - 1);
    g.setColor (Color.lightGray);
    g.drawLine (1, height - 2, width - 2, height - 2);
    g.drawLine (width - 2, 1, width - 2, height - 2);
  }

}
