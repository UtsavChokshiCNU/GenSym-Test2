package com.gensym.beaneditor;

import java.awt.*;
import com.gensym.draw.*;
import java.util.Vector;

public class KnowledgeLinkLooseEnd extends BasicDrawElement
{

  static final long serialVersionUID = 1466335168193914349L;

  private Rectangle[] bounds;
  private Vector ports = new Vector();
  private KnowledgeLink link;

  public KnowledgeLinkLooseEnd (int x, int y, int w, int h)
  {
    bounds = new Rectangle[1];
    bounds[0] = new Rectangle(x,y,w,h);
    setLocation(x,y);
    setSize(w,h);
  }

  @Override
  public synchronized void paint (Graphics g)
  {
    Rectangle b_rect = bounds[0];
    g.setColor(Color.black);
    g.fillPolygon(new int[]{0, b_rect.width, 0}, new int[]{0, b_rect.height/2, b_rect.height}, 3);
  }

  public KnowledgeLink getLink()
  {
    return link;
  }

  public void setLink(KnowledgeLink link)
  {
    this.link = link;
  }
  
  /* coordinates are local to component */
  @Override
  public boolean contains(int x, int y)
  {
    Rectangle theBounds = bounds[0];
    return theBounds.contains(x + theBounds.x ,y + theBounds.y);
  }

  @Override
  public void shift (int shiftX, int shiftY)
  {
    Rectangle rect = bounds[0];
    rect.translate(shiftX,shiftY);
    setLocation(rect.x, rect.y);
  }
    
  @Override
  public Rectangle[] getExactBounds ()
  {
     return bounds;
  }

  Point centerPoint()
  {
    Point location = getLocation();
    Dimension size = getSize();
    return new Point(location.x + (size.width / 2),
		     location.y + (size.height / 2));
  }
}


