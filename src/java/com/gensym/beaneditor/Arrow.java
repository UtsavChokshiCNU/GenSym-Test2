package com.gensym.beaneditor;

import java.awt.*;

public class Arrow implements java.io.Serializable
{
  static final long serialVersionUID = 6675896270922406338L;
  private int x;
  private int y;
  private int height;
  private int width;
  private Color backgroundColor;
  private Color arrowColor;
  private int heading;
  private int margin = 2;
  private int[] xPoints = new int[3];
  private int[] yPoints = new int[3];
  private Rectangle stem = new Rectangle(0,0,0,0);

  public Arrow(int x, int y, int width, int height,
	       Color backgroundColor, Color arrowColor,
	       int heading)
  {
    this.x = x;
    this.y = y;
    this.width = width;
    this.height = height;
    this.backgroundColor = backgroundColor;
    this.arrowColor = arrowColor;
    setHeading(heading);
  }

  public synchronized void paint(Graphics g)
  {
    g.setColor(backgroundColor);
    g.fillRect(x,y,width,height);
    g.setColor(arrowColor);
    g.fillPolygon(xPoints,yPoints, 3);

    g.fillRect(stem.x,stem.y,stem.width,stem.height);
  }

  public int getHeading( )
  {
    return heading;
  }

  public void setHeading(int heading)
  {
    this.heading = heading;
    int halfX = x + (width / 2);
    int halfY = y + (height / 2);
    int fullX = x + width;
    int fullY = y + height;

    switch (heading)
      {
      case Directions.LEFT:
	xPoints[0] = halfX;
	yPoints[0] = y + margin;
	xPoints[1] = x + margin;
	yPoints[1] = halfY;
	xPoints[2] = halfX;
	yPoints[2] = fullY - margin;
	stem.x = halfX;
	stem.y = y + (height / 4) + 1;
        stem.width = (width / 2) - margin;
        stem.height = (height / 2) - 1;
	break;
      case Directions.RIGHT:
	xPoints[0] = halfX;
	yPoints[0] = y + margin;
	xPoints[1] = fullX - margin;
	yPoints[1] = halfY;
	xPoints[2] = halfX;
	yPoints[2] = fullY - margin;
	stem.x = x + margin;
	stem.y = y + (height / 4) + 1;
        stem.width = (width / 2) - margin;
        stem.height = (height / 2) - 1;
	break;
      case Directions.TOP:
	xPoints[0] = x + margin;
	yPoints[0] = halfY;
	xPoints[1] = halfX;
	yPoints[1] = y + margin;
	xPoints[2] = fullX - margin;
	yPoints[2] = halfY;
	stem.x = x + (width / 4) + 1;
	stem.y = halfY;
        stem.width = (width / 2) - 2;
        stem.height = (height / 2) - margin;
	break;
      case Directions.BOTTOM:
	xPoints[0] = x+ margin;
	yPoints[0] = halfY;
	xPoints[1] = halfX;
	yPoints[1] = fullY - margin;
	xPoints[2] = fullX - margin;
	yPoints[2] = halfY;
	stem.x = x + (width / 4) + 1;
	stem.y = y + margin;
        stem.width = (width / 2) - 2;
        stem.height = (height / 2) - margin;
	break;
      }
  }
}
