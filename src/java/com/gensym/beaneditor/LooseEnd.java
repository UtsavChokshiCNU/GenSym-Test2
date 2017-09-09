package com.gensym.beaneditor;

import java.awt.*;
import com.gensym.draw.*;
import java.util.Vector;

public class LooseEnd extends BasicDrawElement
{
  static final long serialVersionUID = 2515681403897305019L;
  private static final Color prongColor = new Color(255, 255, 192);
  private static final int prongHeight = 2;
  private static final int prongWidth = 3;
  private Color color;
  private Rectangle[] bounds;
  private Vector ports = new Vector();
  private EventConnection connection;

  public LooseEnd (int x, int y, int w, int h)
  {
    bounds = new Rectangle[1];
    bounds[0] = new Rectangle(x,y,w,h);
    setLocation(x,y);
    setSize(w,h);
    color = Color.lightGray;
  }

  @Override
  public synchronized void paint (Graphics g)
  {
    // do nothing, but for debugging
    if (true)
      {
	Rectangle b_rect = bounds[0];
	g.setColor(Preferences.currentPreferences.getContainerBackgroundColor());
	g.fillRect(0, 0, b_rect.width, b_rect.height);
	//g.fillOval(0,0,b_rect.width, b_rect.height);

	int side = Directions.LEFT;
	if (connection != null)
	  side = connection.input.getSide();

	int w = b_rect.width - 1;
	int h = b_rect.height - 1;
	int inset = 2;

	switch(side){
	case Directions.RIGHT:
	  g.setColor(Color.black);
	  g.drawArc(0, 0, w, h, 270, -180);
	  g.drawLine(w - prongWidth, 0, w - prongWidth, h);
	  g.drawLine(w/2, 0, w - prongWidth, 0);
	  g.drawLine(w/2, h, w - prongWidth, h);
	  
	  g.setColor(prongColor);
	  g.fillRect(w - prongWidth, inset, prongWidth, prongHeight);
	  g.fillRect(w - prongWidth, h-prongHeight-inset, prongWidth, prongHeight);
	  g.setColor(Color.black);
	  g.drawRect(w - prongWidth, inset, prongWidth, prongHeight);
	  g.drawRect(w - prongWidth, h-prongHeight-inset, prongWidth, prongHeight);

	  g.setColor(Color.gray);
	  g.drawLine(w - prongWidth - 2, 3, w - prongWidth - 2, h - 3);
	  g.drawLine(w - prongWidth - 4, 3, w - prongWidth - 4, h - 3);
	  break;
	case Directions.LEFT:
	  g.setColor(Color.black);
	  g.drawArc(0, 0, w, h, 270, 180);
	  g.drawLine(prongWidth, 0, prongWidth, h);
	  g.drawLine(prongWidth, 0, w/2, 0);
	  g.drawLine(prongWidth, h, w/2, h);
	  
	  g.setColor(prongColor);
	  g.fillRect(0, inset, prongWidth, prongHeight);
	  g.fillRect(0, h-prongHeight-inset, prongWidth, prongHeight);
	  g.setColor(Color.black);
	  g.drawRect(0, inset, prongWidth, prongHeight);
	  g.drawRect(0, h-prongHeight-inset, prongWidth, prongHeight);

	  g.setColor(Color.gray);
	  g.drawLine(prongWidth + 2, 3, prongWidth + 2, h - 3);
	  g.drawLine(prongWidth + 4, 3, prongWidth + 4, h - 3);
	  break;
	case Directions.BOTTOM:
	  g.setColor(Color.black);
	  g.drawArc(0, 0, w, h, 0, 180);
	  g.drawLine(0, h - prongHeight, w, h - prongHeight);
	  g.drawLine(0, h - prongHeight, 0, h/2);
	  g.drawLine(w, h - prongHeight, w, h/2);
	  
	  g.setColor(prongColor);
	  g.fillRect(inset, h - prongHeight, prongWidth, prongHeight);
	  g.fillRect(w-prongWidth-inset, h - prongHeight, prongWidth, prongHeight);
	  g.setColor(Color.black);
	  g.drawRect(inset, h - prongHeight, prongWidth, prongHeight);
	  g.drawRect(w-prongWidth-inset, h - prongHeight, prongWidth, prongHeight);

	  g.setColor(Color.gray);
	  g.drawLine(3, h - prongHeight - 3, w - 3, h - prongHeight - 3);
	  g.drawLine(3, h - prongHeight - 5, w - 3, h - prongHeight - 5);
	  break;
	case Directions.TOP:
	  g.setColor(Color.black);
	  g.drawArc(0, 0, w, h, 0, -180);
	  g.drawLine(0, prongHeight, w, prongHeight);
	  g.drawLine(0, prongHeight, 0, h/2);
	  g.drawLine(w, prongHeight, w, h/2);
	  
	  g.setColor(prongColor);
	  g.fillRect(inset, 0, prongWidth, prongHeight);
	  g.fillRect(w-prongWidth-inset, 0, prongWidth, prongHeight);
	  g.setColor(Color.black);
	  g.drawRect(inset, 0, prongWidth, prongHeight);
	  g.drawRect(w-prongWidth-inset, 0, prongWidth, prongHeight);

	  g.setColor(Color.gray);
	  g.drawLine(3, h - prongHeight - 3, w - 3, h - prongHeight - 3);
	  g.drawLine(3, h - prongHeight - 5, w - 3, h - prongHeight - 5);
	  break;
	}
      }
  }

  public EventConnection getConnection()
  {
    return connection;
  }

  public void setConnection(EventConnection connection)
  {
    this.connection = connection;
  }
  
  @Override
  public void changeColor(Object logicalColor, Color color)
  {
    // do nothing
  }

  @Override
  public void changeColor(Object logicalColor, Object colorKey)
  {
    Color color =  canvas.getColorTable().lookup(colorKey);
    if (color != null)
      changeColor(logicalColor, color);
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


}


