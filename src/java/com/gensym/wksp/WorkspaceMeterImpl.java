package com.gensym.wksp;

import java.awt.*;
import com.gensym.irm.*;
import com.gensym.ntw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import java.util.*;
import java.text.*;
import com.gensym.draw.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.Item;
import com.gensym.classes.Entity;
import com.gensym.classes.Meter;

/**
 * WorkspaceMeterImpl
 */

public class WorkspaceMeterImpl extends WorkspaceIconImpl
implements WorkspaceMeter {

  private static boolean WorkspaceMeterImplDebugP = false;
  private static int numberOfMarksForMeter = 5;
  private static int markerHeight = 40;
  private static int borderWidth=6;
  private static int yMargin = (borderWidth+markerHeight/2);
  private static int distanceFromMarkToLabelCenter = 20;
  private static int lengthOfRulingMarkersForMeter  = 15;
  private static int widthOfRulingMarkersForMeter = 3;
  private static int spaceForRulingLabelsForMeter = 30;
  private static Font font
  = new Font("sansserif",Font.PLAIN, 8);//magnify(14, 192)==>11 ???; 
  private static DecimalFormat form
  = (DecimalFormat)(new ScientificDecimalFormat());
  static {
    form.setMaximumIntegerDigits(4);
    form.setMinimumIntegerDigits(1);
    form.setMaximumFractionDigits(3);
    form.setMinimumFractionDigits(1);
  }
  private static int meterMarkerSlidingAxisPosition = 45;//3*meterWidth/5 ???
  private static int markerWidth = 20;
  private static int halfWidth = markerWidth/2;
  private double lowValueForMeterRuling = 0.0;
  private double incrementPerMeterRuling = 0.25;
  private double value;
  private Number valueNumber = null;
  private static final Symbol FOREGROUND_ = Symbol.intern ("FOREGROUND");
  private static final Symbol[] neededAttributes = {LOW_VALUE_FOR_METER_RULING_,INCREMENT_PER_METER_RULING_};  
  
  /**
   * @param meter The g2 Meter which this element is to represent.
   * @param parent The view into which this element is being added. 
   * @return an initialized WorkspaceMeter
   */
  public WorkspaceMeterImpl(Meter meter, WorkspaceView parent)
  throws G2AccessException
  {
    super((Entity)meter,parent);
    //Need to listen to lowValue and increment
    ((Item)meter).addItemListener((com.gensym.util.ItemListener)this, neededAttributes);  
  }

  private static Number ZERO = (Number)new Integer(0);
  @Override
  public void receivedInitialValues (com.gensym.util.ItemEvent e) {
    Structure initialValues = (Structure)e.getNewValue();
    lowValueForMeterRuling =
      ((Number)initialValues.getAttributeValue(LOW_VALUE_FOR_METER_RULING_, ZERO)).doubleValue();
    incrementPerMeterRuling =
      ((Number)initialValues.getAttributeValue(INCREMENT_PER_METER_RULING_, ZERO)).doubleValue();
    Meter meter = (Meter)getItem();
    try {
      valueNumber = meter.getValueToDisplay();
    } catch (G2AccessException g2ae) {
      valueNumber = null;
      Trace.exception(g2ae);
    }
    if (valueNumber != null)
      this.value = valueNumber.doubleValue();
  }
  
  private void drawRulingAndLabels(Graphics g, int meterWidth, int meterHeight) {
    int rulingHeight = meterHeight-(2*yMargin);
    int rulingMarkerXPosition = spaceForRulingLabelsForMeter;//meterWidth/3;
    int rulingMarkerYPosition;
    int distanceBetweenMarkingsForMeter = rulingHeight/(numberOfMarksForMeter-1);//round(62.5)

    g.setFont(font);
    FontMetrics metrics = g.getFontMetrics();
    String label;
    for (int markNumber = 0; markNumber<numberOfMarksForMeter;markNumber++) {
      rulingMarkerYPosition = (meterHeight - yMargin) -  markNumber*distanceBetweenMarkingsForMeter;
      g.fillRect(rulingMarkerXPosition, rulingMarkerYPosition,
		 lengthOfRulingMarkersForMeter, widthOfRulingMarkersForMeter);
      label = form.format(lowValueForMeterRuling + (markNumber*incrementPerMeterRuling));
      g.drawString(label, borderWidth, rulingMarkerYPosition-yMargin/2);
    }
  }

  private void drawMarkerForMeter(Graphics g, int meterWidth, int meterHeight) {
    if (valueNumber != null) {
      int left=meterMarkerSlidingAxisPosition;
      int rulingHeight = meterHeight-(2*yMargin);
      int markerBottom = (int)((meterHeight - yMargin) - 
			       rulingHeight*(value-lowValueForMeterRuling)
			       /(incrementPerMeterRuling*(numberOfMarksForMeter-1)));
      int top = markerBottom - markerHeight/2;
      int[] xPoints = {left+halfWidth,left+markerWidth,left+markerWidth,left+halfWidth,
		       left+halfWidth,left,left+halfWidth,
		       left+halfWidth};
      int[] yPoints = {top,top,top+markerHeight,top+markerHeight,
		       top+3*markerHeight/4,top+markerHeight/2,top+markerHeight/4,
		       top};
      g.fillPolygon(xPoints,yPoints,8);
    }
  }
  
  /**
   * Paints a G2 Meter with the marker at the current
   * value for the meter.
   */
  @Override
  public void paint(Graphics g) {
    super.paint(g);
    int left = 0, top = 0;
    Rectangle[] bounds = getExactBounds();
    int width =  bounds[0].width;
    int height =  bounds[0].height;

    g.setColor(canvas.getColorTable().lookup(FOREGROUND_));
    drawRulingAndLabels(g,width,height);
    drawMarkerForMeter(g,width,height);
  }

  /**
   * Updates the marker for this meter using the new value
   * contained within the event. Will automatically repaint
   * the meter.
   */
  @Override
  public void handleValueToDisplayChanged(WorkspaceEvent event) {
    Structure info = event.getInfo();
    Symbol attributeName = (Symbol)info.getAttributeValue(ATTRIBUTE_NAME_, null);
    if (VALUE_TO_DISPLAY_.equals(attributeName)) {
      valueNumber = (Number)info.getAttributeValue(NEW_VALUE_, null);
      if (valueNumber != null)
	this.value = valueNumber.doubleValue();
      Rectangle[] invalRegion = getExactBounds();//make more efficient
      ((WorkspaceView)getParent()).invalidate(invalRegion);
    }
    else
      System.out.println("UNHANDLED VALUE TO DISPLAY CHANGE IN DIAL");
  }

  /**
   * Receives updates for attribute changes to the meter,
   * updating the WorkspaceMeter for the attributes
   * LOW_VALUE_FOR_METER_RULING_ and INCREMENT_PER_METER_RULING_
   * as needed.  Will automatically repaint the meter.
   */
  @Override
  public void itemModified (ItemEvent e) {
    super.itemModified(e);
    Sequence denotationSequence = e.getDenotation();
    Structure denotation = (Structure) denotationSequence.elementAt(0);
    Symbol attributeName = (denotation!=null?(Symbol)denotation.getAttributeValue(NAME_, null):null);
    if (LOW_VALUE_FOR_METER_RULING_.equals(attributeName)) {
      lowValueForMeterRuling = ((Number)e.getNewValue()).doubleValue();
      value = Math.max(lowValueForMeterRuling,value);
    }
    else if (INCREMENT_PER_METER_RULING_.equals(attributeName))
      incrementPerMeterRuling = ((Number)e.getNewValue()).doubleValue();
    Rectangle bounds = getExactBounds()[0];
    Rectangle[] invalRegion = {bounds};
    ((WorkspaceView)getParent()).invalidate(invalRegion);
  }

  @Override
  public void dispose() throws G2AccessException{
    getItem().removeItemListener(this, neededAttributes);
    super.dispose();
  }  
}

