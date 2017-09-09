package com.gensym.demos.dialogapplet;

import java.awt.*;
import java.awt.event.*;
import java.util.Vector;
import com.gensym.util.Symbol;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectUpdateListener;

public class ControlChart extends Container
  implements ObjectUpdateListener
{
  static boolean debug = false;
  double upperLimit = 10.0;
  double lowerLimit = 0.0;
  double mean = 5.0;
  int margin = 50;
  Vector datapoints = new Vector();
  double uninitializedTime = -999.9;
  double startTime = 0.0;
  double endTime = 0.0;
  double timespan = 120.0;
  double timebase;
  Color backgroundColor = Color.blue;
  Color controlLimitColor = Color.green;
  Color meanColor = Color.green;
  Color labelColor = Color.black;
  Color pointColor = Color.red;
  Color lineColor = Color.orange;
  int startIndex = 0;
  Vector listeners = null;

  private String attributeName = "";
  private Symbol attributeSymbol = null;
  private String defaultContents = "";

  public ControlChart()
  {
    super();
    timebase = time();
    setFont(new Font("SansSerif",Font.PLAIN,18));
  }

  public void setUpperLimit(double limit)
  {
    upperLimit = limit;
    mean = (upperLimit - lowerLimit) / 2.0;
    repaint();
  }

  public double getUpperLimit()
  {
    return upperLimit;
  }

  /** Gets the name of the G2 Item attribute which this bean is
   * storing.
   */ 
  public String getAttributeName()
  { 
    return attributeName; 
  }

  /** Gets the name of the G2 Item attribute which this bean is
   * storing as a Symbol.
   * @see com.gensym.util.Symbol
   */ 
  public Symbol getAttributeSymbol()
  {
    return attributeSymbol;
  }

  /** Sets the name of the G2 Item attribute which this bean is
   * storing.
   */ 
  public void setAttributeName(String newName)
  { 
    attributeName = newName; 
    if (newName.equals(""))
      attributeSymbol = null;
    else
      attributeSymbol = Symbol.intern(newName);
  }

  public void setAttributeSymbol(Symbol symbol)
  {
    attributeSymbol = symbol;
    attributeName = symbol.toString();
  }
  
  public void setLowerLimit(double limit)
  {
    lowerLimit = limit;
    mean = (upperLimit - lowerLimit) / 2.0;
    repaint();
  }

  public double getLowerLimit()
  {
    return lowerLimit;
  }

  public void setTimespan(double timespan)
  {
    this.timespan = timespan;
    repaint();
  }

  public double getTimespan()
  {
    return timespan;
  }

  private double time()
  {
    return ((double)System.currentTimeMillis()) / 1000.0;
  }
  
  public void newSample(double sample)
  {
    double timestamp = time();
    if (datapoints.size() == 0)
      startTime = timestamp;
    endTime = timestamp;
    // trim old samples here;
    datapoints.addElement(new Datapoint(sample,timestamp)); 
    if (debug)
      System.out.println("start "+(startTime-timebase)+" end "+(endTime-timebase)+
			 " span "+timespan);
    if (debug)
      System.out.println("size "+getSize()+" locatio "+getLocation());
    if ((endTime - startTime) > timespan)
      {
	double goalTime = startTime + (timespan / 4.0);
	int i, size = datapoints.size();
	//System.out.println("advancing start time with goal "+(goalTime-timebase));
	for (i=startIndex; i<size ; i++)
	  {
	    Datapoint point = (Datapoint) datapoints.elementAt(i);
	    //System.out.println(" considering "+(point.timestamp-timebase));
	    if (point.timestamp >= goalTime)
	      {
		startIndex = i;
		startTime = point.timestamp;
		break;
	      }
	  }
      }
    repaint();
    if (sample > upperLimit || sample < lowerLimit)
      fireAlarm();
  }

  private Point getPoint(Datapoint datapoint, Dimension size)
  {
    int height = size.height, width = size.width;
    int hv = margin;
    int lv = height-margin;
    double dy =  ((height - (2 * margin)) *
		  ((datapoint.value - lowerLimit) /
		   (upperLimit - lowerLimit)));
    double dx = ((width - (2 * margin)) *
		 ((datapoint.timestamp - startTime) /
		  timespan));
    return new Point(margin + (int)dx,
		     height - (margin + (int)dy));
  }

  @Override
  public void paint (Graphics g)
  {
    if (debug)
      System.out.println("painting");
    Dimension size = getSize();
    int height = size.height, width = size.width;
    g.setFont(getFont());
    FontMetrics metrics = g.getFontMetrics();
    int offset = metrics.getAscent() / 2;
    int halfHeight = height/2;
    g.setColor(backgroundColor);
    g.fillRect(0,0,size.width,size.height);
    
    g.setColor(controlLimitColor);
    g.drawLine(margin,margin,width-margin,margin);
    g.drawString("UCL",5,margin+offset);
    g.drawString(""+upperLimit,width-margin+5,margin+offset);
    g.drawLine(margin,halfHeight,width-margin,halfHeight);
    g.drawString("MEAN",5,halfHeight+offset);
    g.drawString(""+mean,width-margin+5,halfHeight+offset);
    g.drawLine(margin,height-margin,width-margin,height-margin);
    g.drawString("LCL",5,height-margin+offset);
    g.drawString(""+lowerLimit,width-margin+5,height-margin+offset);
    Point lastpoint = null;
    for (int i = startIndex; i<datapoints.size() ; i++)
      {
	Datapoint datapoint = (Datapoint) datapoints.elementAt(i);
	Point point = getPoint(datapoint,size);
	g.setColor(lineColor);
	if (i>startIndex)
	  g.drawLine(lastpoint.x,lastpoint.y,point.x,point.y);
	g.setColor(pointColor);
	g.fillOval(point.x-3,point.y-3,6,6);
	lastpoint = point;
      }
  }

  public synchronized void addAlarmListener (AlarmListener
					     listener)
  {
    if (listeners == null) {
      listeners = new java.util.Vector();
    }
    listeners.addElement(listener);
  }
  
  public synchronized void removeAlarmListener(AlarmListener
					       listener) 
  {
    if (listeners == null) {
      return;
    }
    listeners.removeElement(listener);
  }

  void fireAlarm()
  {
    Vector targets;
    synchronized (this) {
      if (listeners == null) {
	return;
      }
      targets = (java.util.Vector) listeners.clone();
    }
    AlarmEvent evt = new AlarmEvent(this);
    for (int i = 0; i < targets.size(); i++) {
      AlarmListener target = (AlarmListener)targets.elementAt(i);
      target.outOfControlPointReceived(evt);
    }
  }

  @Override
  public void objectUpdated(ObjectUpdateEvent e)
  {
    Object fieldValue = e.getUpdatedValue(attributeSymbol,defaultContents);
    
    try {
      if (fieldValue instanceof Double)
	{
	  // System.out.println("calling new sample");
	  newSample(((Double)fieldValue).doubleValue());
	}
    } catch (Exception ee)
      {
	ee.printStackTrace();
      }
  } 


  public static void main(String[] args)
  {
    try {
      Frame frame = new Frame();
      frame.setSize(600,600);
      frame.addWindowListener
	(
	 new WindowAdapter ()
	 {
	   @Override
	   public void windowClosing(WindowEvent e)
	     {
	       System.exit(0);
	     }
	 } ) ;
      
      ControlChart chart = new ControlChart();
      chart.setSize(300,300);
      frame.add(chart);
      chart.setLocation(100,100);
      long pause = (long) 500;
      chart.newSample(5.5);
      Thread.sleep(pause);
      chart.newSample(6.6);
      Thread.sleep(pause);
      chart.newSample(7.7);
      Thread.sleep(pause);
      chart.newSample(8.8);
      frame.show();
    } catch (Exception e)
      {
	e.printStackTrace();
      }
  }

  
}

class Datapoint
{
  double value;
  double timestamp;

  Datapoint (double value, double timestamp)
  {
    this.value = value;
    this.timestamp = timestamp;
  }
}




