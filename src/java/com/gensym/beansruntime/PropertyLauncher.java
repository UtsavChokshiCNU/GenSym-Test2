package com.gensym.beansruntime;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import java.lang.reflect.Method;

public class PropertyLauncher extends Canvas implements MouseListener
{
   private Frame          frame;
   private PropertyEditor editor;
   private Method         propertyRead;
   private Object         bean;

   public PropertyLauncher(Frame frame, PropertyEditor newEditor, 
		    Method propertyRead, Object bean)
   {
     this.frame = frame;
     this.propertyRead = propertyRead;
     this.bean = bean;
     editor = newEditor;
     addMouseListener(this);
   }
  
  @Override
  public void paint(Graphics g)
  {
    Rectangle box = new Rectangle(2, 2, getSize().width - 4, getSize().height - 4);
    editor.paintValue(g, box);
  }
  
  
  @Override
  public void mouseClicked(MouseEvent evt)
  {
    int x = frame.getLocation().x + getLocation().x;
    int y = frame.getLocation().x + getLocation().y;
    
    new PropertyCustom(frame, editor, x, y, propertyRead, bean);
  }
  
  @Override
  public void mousePressed(MouseEvent evt)
  {
  }
  
  @Override
  public void mouseReleased(MouseEvent evt)
  {
  }
  
  @Override
  public void mouseEntered(MouseEvent evt)
  {
  }
  
  @Override
  public void mouseExited(MouseEvent evt)
  {
  }
  
}
