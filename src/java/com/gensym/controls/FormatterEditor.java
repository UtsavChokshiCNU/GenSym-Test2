package com.gensym.controls;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;

public class FormatterEditor extends Panel 
     implements PropertyEditor, TextListener, ItemListener
{ 
  private Formatter formatter;
  private int ourWidth = 0;
  private int horizontalPad = 5;
  private PropertyChangeSupport support = new PropertyChangeSupport(this);
  private TextField attributeName;
  private Choice choser;

  public FormatterEditor() 
  {
    setLayout(null);
    
    ourWidth = horizontalPad;
    
    choser = new Choice();
    choser.add("toString");
    choser.add("Attribute");
    add(choser);
    choser.addItemListener(this);
    choser.setBounds(ourWidth,0,100,30);
    ourWidth += 100 + horizontalPad;

    attributeName = new TextField("", 14);
    add(attributeName);
    attributeName.addTextListener(this);
    attributeName.setBounds(ourWidth,0,100,30);
    ourWidth += 100 + horizontalPad;

    setSize(ourWidth,50);
  }

  @Override
  public void textValueChanged(TextEvent event)
  {
    Object object_target = event.getSource();
    System.out.println("text event="+event+" on "+object_target);

    if (object_target == attributeName)
      {
        formatter.setAttributeName( attributeName.getText());
        support.firePropertyChange("",null,null);
      }
    else 
      {
        // don't do anything yet
      }
  }

  @Override
  public void itemStateChanged(ItemEvent event)
  {
    Object object_target = event.getSource();
    System.out.println("item event="+event+" on "+object_target);

    if (object_target == choser)
      {
        formatter.setStyle(choser.getSelectedItem());
        support.firePropertyChange("",null,null);
        showSelection();
      }
    else
      {
        // no other selectable controls yet
      }
  }

  @Override
  public void setValue(Object o)
  {
    Formatter formatterToCopy = (Formatter) o;
    String attribute_name = formatterToCopy.getAttributeName();
    String style = formatterToCopy.getStyle();

    formatter = new Formatter(style,attribute_name);
    
    attributeName.setText(attribute_name);
    choser.select(style);
    showSelection();
  }

  private void showSelection()
  {
    String style = choser.getSelectedItem();
    if (style.equals("Attribute"))
      attributeName.setEditable(true);
    else
      attributeName.setEditable(false);
  }
  
  @Override
  public Dimension getPreferredSize() 
  {
    return new Dimension(ourWidth, 50);
  }
  
  @Override
  public void setAsText(String s) throws java.lang.IllegalArgumentException 
  {
    
  }
    
  @Override
  public String getJavaInitializationString()
  {
    return 
      "new com.gensym.controls.Formatter(\""+
      formatter.getStyle()+"\", \""+
      formatter.getAttributeName()+"\")";
  }

  @Override
  public Object getValue() {
    return formatter;
  }

  @Override
  public boolean isPaintable() {
    return true;
   }

  @Override
  public void paintValue(java.awt.Graphics gfx, java.awt.Rectangle box) {
    Color oldColor = gfx.getColor();
    Font oldFont = gfx.getFont();
    gfx.setColor(Color.white);
    gfx.fillRect(box.x+1, box.y+1, box.width-4, box.height-4);
    gfx.setColor(Color.black);
    gfx.drawRect(box.x, box.y, box.width-3, box.height-3);
    gfx.setFont(new Font("Courier",Font.PLAIN,12));
    FontMetrics metrics = gfx.getFontMetrics();
    gfx.drawString(formatter.toString(),box.x+4,box.y+3+metrics.getAscent());
    gfx.setColor(oldColor);
    gfx.setFont(oldFont);
  }

    @Override
    public String getAsText() {
      return "foo(1,2,3)";
    }

    @Override
    public String[] getTags() {
	return null;
    }

    @Override
    public java.awt.Component getCustomEditor() 
    {
      return this;
    }

    @Override
    public boolean supportsCustomEditor()
    {
	return true;
    }

    @Override
    public void addPropertyChangeListener(PropertyChangeListener l) 
    {
	support.addPropertyChangeListener(l);
    }

    @Override
    public void removePropertyChangeListener(PropertyChangeListener l) 
    {
	support.removePropertyChangeListener(l);
    }

}

