package com.gensym.beansruntime;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;

public class PropertyChoice extends Choice implements ItemListener
{
  PropertyEditor editor; 
  
  public PropertyChoice(PropertyEditor newEditor)
  {
    editor = newEditor;
    String tags[] = editor.getTags();
    for (int i = 0; i < tags.length; i++)
      {
	addItem(tags[i]);
      }
    
    select(0);
    
    select(editor.getAsText());
    addItemListener(this);
  }
  
  @Override
  public void itemStateChanged(ItemEvent evt)
  {
    String s = getSelectedItem();
    editor.setAsText(s);
  }
  
  @Override
  public void repaint()
  {
    select(editor.getAsText());
  }
  
}
