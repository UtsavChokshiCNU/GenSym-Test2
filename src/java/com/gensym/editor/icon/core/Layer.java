package com.gensym.editor.icon.core;

import java.util.Vector;
import java.util.Enumeration;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.Point;
import com.gensym.editor.icon.shapes.*;

/**
 * @author Paul B. Konigsberg
 */

public class Layer extends Component
implements java.io.Serializable
{
  private String name;
  private Color color;
  private Vector elements = new Vector();
  private int minWidth, minHeight = 50;
  private transient boolean selected, highlighted;
  private transient boolean enabled = true;
  private Object colorExpression;

  @Override
  public void setEnabled(boolean enabled) {
    this.enabled = enabled;
    Enumeration e = getElements();
    while(e.hasMoreElements()) {
      Component ie = (Component)e.nextElement();
      ie.setVisible(enabled);
    }  
  }

  @Override
  public boolean isEnabled() {
    return enabled;
  }
  
  public void setMinimumWidth(int width)
  {
    minWidth = width;
  }

  public void setMinimumHeight(int height)
  {
    minHeight = height;
  }

  public String getRegionName()
  {
    return name;
  }

  public void setRegionName(String name)
  {
    this.name = name;
  }

  public void setColorExpression(Object colorExpression) {
    this.colorExpression = colorExpression;
  }

  public Object getColorExpression() {
    return colorExpression;
  }
  
  public Color getColor()
  {
    return color;
  }

  @Override
  public Dimension getMinimumSize() {
    return new Dimension(minWidth,minHeight);
  }

  @Override
  public Dimension getPreferredSize() {
    return getMinimumSize();
  }
  
  public void setColor(Color color)
  {
    this.color = color;
    Enumeration e = getElements();
    while (e.hasMoreElements()) {
      DrawElement elt = (DrawElement)e.nextElement();
      elt.changeColor(color);
    }
    repaint();
  }

  public IconElement getTopMostElement() {
    if (elements.size() > 0)
      return (IconElement)elements.firstElement();
    else
      return null;
  }
  
  public IconElement[] getElementsSnapshot()
  {
    IconElement[] elts = new IconElement[elements.size()];
    elements.copyInto(elts);
    return elts;
  }

  public Enumeration getElements()
  {
    return elements.elements();
  }

  public Layer copy()
       throws ElementInconsistancyError
  {
    Layer copy = new Layer();
    IconElement[] elts = getElementsSnapshot();
    for (int i=0;i<elts.length;i++) {
      copy.addElement(elts[i].copy());
    }
    copy.setColor(color);
    return copy;
  }

  public void setFilled(boolean filled)
  {
    IconElement[] elts = getElementsSnapshot();
    for (int i=0;i<elts.length;i++) {
      IconElement elt = elts[i];
      if (elt instanceof Fillable)
	((Fillable)elt).setFilled(filled);
    }
    repaint();
  }
  
  public void addElement(IconElement element)
       throws ElementInconsistancyError
  {
    Layer elementLayer = element.getLayer();
    if (elementLayer == null) {
      elements.insertElementAt(element,0);
      element.setLayer(this);
      element.changeColor(color);
    } else if (elementLayer == this)
      throw new ElementInconsistancyError(ElementInconsistancyError.sameLayerError);
    else
      throw new ElementInconsistancyError(ElementInconsistancyError.twoLayerError);
      
  }
   
  public void removeElement(IconElement element)
       throws ElementInconsistancyError
  {
    if (elements.contains(element)) {
      elements.removeElement(element);
      element.setLayer(null);
    } else
      throw new ElementInconsistancyError(ElementInconsistancyError.nonExistantElementError);
  }

  public void clear() {
    elements.clear();
  }
  
  public boolean isSelected() {
    return selected;
  }
  
  public void setSelected(boolean selected) {
    this.selected = selected;
  }

  public void setHighlighted(boolean highlighted) {
    this.highlighted = highlighted;
  }
  
  @Override
  public void paint(Graphics g)
  {
    Rectangle bounds = getBounds();
    Color bgColor = Color.white;
    if (highlighted)
      bgColor = Color.lightGray;
    g.setColor(bgColor);
    g.fillRect(0,0,bounds.width-1,bounds.height-1);
    g.setColor(color);

    g.drawRect(0,0,bounds.width-1,bounds.height-1);

    Enumeration e = getElements();
    while (e.hasMoreElements()) {
      Component elt = (Component)e.nextElement();
      Point loc = elt.getLocation();
      g.translate(loc.x, loc.y);
      elt.paint(g);
      g.translate(-loc.x, -loc.y);
    }
  }
    
}
