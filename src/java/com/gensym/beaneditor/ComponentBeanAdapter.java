package com.gensym.beaneditor;

import java.awt.*;
import java.awt.event.*;

import com.gensym.draw.EventHandler;

public class ComponentBeanAdapter implements MouseMotionListener, MouseListener
{
  Component    component;
  EventHandler beanEditTool;
  private boolean mouseDown = false;

  ComponentBeanAdapter(Component component,EventHandler beanEditTool)
  {
    this.component = component;
    this.beanEditTool = beanEditTool;
    addListeners();
  }
  
  void addListeners()
  {
    component.addMouseListener(this);
    component.addMouseMotionListener(this);
  }

  void removeListeners()
  {
    component.removeMouseListener(this);
    component.removeMouseMotionListener(this);
  }

  @Override
  public void mouseClicked(MouseEvent e)
  {
    Point location = component.getLocation();
    e.translatePoint(location.x, location.y);
    beanEditTool.mouseClicked(e);
  }


  @Override
  public void mousePressed(MouseEvent e)
  {
    mouseDown = true;
    Point location = component.getLocation();
    e.translatePoint(location.x, location.y);
    beanEditTool.mousePressed(e);
  }
  
  @Override
  public void mouseReleased(MouseEvent e)
  {
    if (mouseDown){
      mouseDown = false;
      Point location = component.getLocation();
      e.translatePoint(location.x, location.y);
      beanEditTool.mouseReleased(e);
    }
  }
  
  @Override
  public void mouseEntered(MouseEvent e)
  {
    Point location = component.getLocation();
    e.translatePoint(location.x, location.y);
    beanEditTool.mouseEntered(e);
  }
  
  @Override
  public void mouseExited(MouseEvent e) 
  {
    Point location = component.getLocation();
    e.translatePoint(location.x, location.y);
    beanEditTool.mouseExited(e);
  }  

  @Override
  public void mouseDragged(MouseEvent e) 
  {
    Point location = component.getLocation();
    e.translatePoint(location.x, location.y);
    beanEditTool.mouseDragged(e);
  }  
  
  @Override
  public void mouseMoved(MouseEvent e) 
  {
    Point location = component.getLocation();
    e.translatePoint(location.x, location.y);
    beanEditTool.mouseMoved(e);
  }
}
