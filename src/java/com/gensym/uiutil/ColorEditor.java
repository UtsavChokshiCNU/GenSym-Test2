package com.gensym.uiutil;

import java.awt.Button;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Label;
import java.awt.Panel;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.beans.PropertyEditor;

import com.gensym.message.Resource;

/** 
 * ColorEditor - The customized Color Editor used inside the bean editor 
 **/

public class ColorEditor extends Panel implements PropertyEditor, ActionListener {

  private static Resource i18n = 
	   Resource.getBundle("com.gensym.uiutil.ColorEditorResources");

  private Color color;
  private ColorSpectrumPanel spect;
  private ColorPreviewCanvas sample;
  private PropertyChangeSupport support;

  /**
   * Constructs a color chooser with two tab panels. One panel 
   * with the standard G2 colors and another panel with a color spectrum.
   */

  public ColorEditor() {
    setLayout(null);
    support = new PropertyChangeSupport(this);

    Panel top = new Panel();
    top.setLayout(null);

    Panel p1 = new Panel();
    p1.setLayout(null);

    sample = new ColorPreviewCanvas();
   
    spect = new ColorSpectrumPanel(sample);
    
    Label l = new Label(i18n.getString("Colors"));
    p1.add(l);
    l.setBounds(5,10,120, 20);
    p1.add(spect);
    spect.setBounds(5,35,375,256);

   
    top.add(p1);
    p1.setBounds(0,0,400,325);
    p1.setVisible(true);
    //Button ok = new Button(i18n.getString("OK"));
    //Button cancel = new Button(i18n.getString("Cancel"));
    //cancel.addActionListener(this);
    Button apply = new Button(i18n.getString("DialogApply"));
    apply.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {  
	color = spect.getSelectedColor();
        sample.setSelectedColor(color);
        sample.setCurrentColor(color);
        sample.repaint();
	support.firePropertyChange("", null, null);
      }
    });
    //top.add(ok);
    //ok.setBounds(70,330, 70,25);
    //top.add(cancel);
    //cancel.setBounds(150,330, 70,25);
    top.add(apply);
    apply.setBounds(150,330, 70,25);
    top.setBackground(Color.lightGray);

    top.add(sample);
    int sampleWidth = sample.getPreferredSize().width;
    int sampleHeight = sample.getPreferredSize().height;
    sample.setBounds(410,220,sampleWidth,sampleHeight);
    setSize(510,360);
    add(top);
    top.setBounds(0,0,510,360);
  }
  
  @Override
  public void addPropertyChangeListener(PropertyChangeListener propertyChangeListener) {
    support.addPropertyChangeListener(propertyChangeListener);
  }

  @Override
  public String getAsText() {
    return null;
  }

  @Override
  public Component getCustomEditor() {
    return this;
  }

  @Override
  public String getJavaInitializationString() {
    return null;
  }

  @Override
  public String[] getTags() {
    return null;
  }

  @Override
  public Object getValue() {
    return color;
  }

  @Override
  public boolean isPaintable() {
    return true;
  }

  /** 
   * Paints the color rectangle on the property sheet of the bean editor.
   **/
  @Override
  public void paintValue(Graphics g, Rectangle rectangle) {
    Color color = g.getColor();
    g.setColor(Color.black);
    g.drawRect(rectangle.x, rectangle.y, 
	       rectangle.width - 3, rectangle.height - 3);
    g.setColor(this.color);
    g.fillRect(rectangle.x + 1, rectangle.y + 1, 
	       rectangle.width - 4, rectangle.height - 4);
    g.setColor(color);
  }

  @Override
  public void removePropertyChangeListener(PropertyChangeListener propertyChangeListener) {
    support.removePropertyChangeListener(propertyChangeListener);
  }

  @Override
  public void setAsText(String string) throws IllegalArgumentException {
  }

  /** 
   * set the current color
   **/
  @Override
  public void setValue(Object object){
    color = (Color)object;
    changeColor(color);
  }

  @Override
  public boolean supportsCustomEditor() {
    return true;
  }
	
  private void changeColor(Color color) {
    this.color = color;
    //cd.setSelectedColor(color);
    //sample.setSelectedColor(color);
    sample.setCurrentColor(color);
    sample.repaint();
    support.firePropertyChange("", null, null); 
  }

  @Override
  public void actionPerformed(ActionEvent e) {
  }

  @Override
  public Dimension getPreferredSize() {
    return new Dimension(510, 360);
  }
}
