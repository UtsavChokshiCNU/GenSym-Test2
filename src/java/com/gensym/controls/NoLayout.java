
package com.gensym.controls;

import java.util.Hashtable;
import java.awt.*;

/*
 *  This is a simple layout manager that will map components
 *  to an x,y postion, with a fixed with and height.
 */

public class NoLayout implements LayoutManager
{
	protected Hashtable compMap = new Hashtable();
	protected int width;
	protected int height;

  /*
	public XYLayout(Container parent, int width, int height)
	{
		Construct(parent, width, height);
	} */

  public NoLayout()
  {}
  
  public void setShape(Component comp, int x, int y, int width, int height)
  {
    compMap.put(comp, new Rectangle(x, y, width, height));
  }
  
  @Override
  public void addLayoutComponent(String name, Component comp) { }
  
  @Override
  public void removeLayoutComponent(Component comp) { }
  
  @Override
  public Dimension preferredLayoutSize(Container parent)
  {
    return parent.getSize(); // new Dimension(width, height);
  }
  
  @Override
  public Dimension minimumLayoutSize(Container parent)
  {
    return parent.getSize(); // new Dimension(width, height);
  }
  
  @Override
  public void layoutContainer(Container parent)
  {
    int count = parent.getComponentCount();
    
    for (int i = 0; i < count; i++)
      {
	Component c = parent.getComponent(i);
	// Rectangle rect = (Rectangle)compMap.get(c);
	if (true) // (rect != null)
	  {
	    Dimension size = c.getSize();
	    Point location = c.getLocation();
	    // c.reshape(rect.x, rect.y, rect.width, rect.height);
	    //System.out.println("shrink and grow");
	    c.setBounds(location.x, location.y, size.width+1, size.height);
	    c.setBounds(location.x, location.y, size.width, size.height);
	  }
      }
  }
  
  /*
  protected void Construct(Container parent, int width, int height)
  {
    this.width  = width;
    this.height = height;
  } */
}
