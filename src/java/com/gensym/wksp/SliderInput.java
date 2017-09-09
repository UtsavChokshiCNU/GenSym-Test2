package com.gensym.wksp;

import java.awt.*;
import java.util.Observer;
import java.util.Observable;
import com.gensym.irm.*;
import com.gensym.ntw.*;
import com.gensym.draw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.classes.Item;
import com.gensym.classes.Entity;
import com.gensym.classes.Button;
import com.gensym.classes.Slider;
import com.gensym.jgi.G2AccessException;


/**
 *
 */

public class SliderInput extends BasicDrawElement
{
  private static int size = 14;
  private static Polygon p = new Polygon();
  private static final Symbol LIGHT_GRAY_ = Symbol.intern ("LIGHT-GRAY");
  private WorkspaceSliderImpl slider;
  
  static {
    p.addPoint(0,0);
    p.addPoint(size,0);
    p.addPoint(size/2,size);

  }

  public SliderInput(WorkspaceSliderImpl slider) {
    this.slider = slider;
    setSize(size,size);
  }

  public WorkspaceSliderImpl getSlider() {
    return slider;
  }

  @Override
  public Rectangle[] getExactBounds ()
  {
    return new Rectangle[] {getBounds()};
  }

  @Override
  public boolean contains(int logical_x, int logical_y)
  {
    Rectangle boundsRect = getBounds();
    return boundsRect.contains(logical_x + boundsRect.x,
			       logical_y + boundsRect.y);
  }

  @Override
  public void shift (int shift_x, int shift_y)
  {
    Point location = getLocation();
    setLocation(location.x + shift_x, location.y + shift_y);
  }
  
  /**
   */
  @Override
  public void paint(Graphics g)
  {
    g.setColor(canvas.getColorTable().lookup(LIGHT_GRAY_));
    g.fillPolygon(p);
    g.setColor(Color.black);
    g.drawPolygon(p);
  }
  
}
