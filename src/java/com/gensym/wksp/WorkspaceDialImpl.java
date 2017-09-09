package com.gensym.wksp;

import java.awt.*;
import java.text.NumberFormat;
import java.text.DecimalFormat;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.Item;
import com.gensym.classes.Entity;
import com.gensym.classes.Dial;

/**
 * WorkspaceDialImpl
 */

public class WorkspaceDialImpl extends WorkspaceIconImpl
implements WorkspaceDial {

  private static boolean WorkspaceDialImplDebugP = false;
  private static int numberOfMarksForDial = 5;
  private static int lengthOfRulingMarkers = 10;
  private static double rulingLowValueAngleInRadians = Math.PI;
  private static double angleBetweenMarkingsInRadians
  = (180/(numberOfMarksForDial - 1))*(Math.PI/180);
  private static int distanceFromMarkToLabelCenter = 12;
  private static Font font
  = new Font("sansserif",Font.PLAIN, 8);//magnify(14, 192)==>11 ???;
  private static DecimalFormat form
  = (DecimalFormat)(new ScientificDecimalFormat());
  static {
    form.setMaximumIntegerDigits(3);
    form.setMinimumIntegerDigits(1);
    form.setMaximumFractionDigits(2);
    form.setMinimumFractionDigits(1);
  }
  private double value;
  private Number valueNumber=null;
  private double lowValueForDialRuling = 0.0;
  private double incrementPerDialRuling = 0.25;
  private static final Symbol FOREGROUND_ = Symbol.intern ("FOREGROUND");
  private static final Symbol[] neededAttributes = {LOW_VALUE_FOR_DIAL_RULING_,INCREMENT_PER_DIAL_RULING_};
  
  /**
   * @param dial The G2 dial which this element is to represent.
   * @param parent The view into which this element is being added. 
   * @return an initialized WorkspaceDial.
   */
  public WorkspaceDialImpl(Dial dial, WorkspaceView parent)
       throws G2AccessException
  {
    super((Entity) dial, parent);
    //Need to listen to lowValue and increment
    ((Item)dial).addItemListener((com.gensym.util.ItemListener)this, neededAttributes);    
  }

  private static Number ZERO = (Number)new Integer(0);
  @Override
  public void receivedInitialValues (com.gensym.util.ItemEvent e) {
    Structure initialValues = (Structure)e.getNewValue();
    lowValueForDialRuling =
      ((Number)initialValues.getAttributeValue(LOW_VALUE_FOR_DIAL_RULING_, ZERO)).doubleValue();
    incrementPerDialRuling =
      ((Number)initialValues.getAttributeValue(INCREMENT_PER_DIAL_RULING_, ZERO)).doubleValue();
    Dial dial = (Dial)getItem();
    try {
      valueNumber = dial.getValueToDisplay();
    } catch (G2AccessException g2ae) {
      valueNumber = null;
      Trace.exception(g2ae);
    }
    if (valueNumber != null)
      value = valueNumber.doubleValue();
  }

  private int scale(int val) {
    return val;
  }
  
  private void drawRuling(Graphics g, int xCenterOfDial, int yCenterOfDial, int dialRadius) {
    double markAngle;
    int markXPosition,markYPosition;

    for (int markNumber = 0; markNumber < numberOfMarksForDial; markNumber++) {
      markAngle = rulingLowValueAngleInRadians - markNumber*angleBetweenMarkingsInRadians;
      markXPosition
	= (int) (Math.round(xCenterOfDial + Math.cos(markAngle)*(dialRadius - lengthOfRulingMarkers)));
      markYPosition
	= (int) (Math.round(yCenterOfDial - Math.sin(markAngle)*(dialRadius - lengthOfRulingMarkers)));
      g.fillRect(markXPosition, markYPosition, scale(3),scale(3));
    }
  }

  private static int computeHeightOfText(String text, FontMetrics metrics) {
    return metrics.getAscent();
  }

  private static int computeWidthOfText(String text, FontMetrics metrics) {
    int textWidth = 0;
    char ch;
    for (int index = 0; index < text.length(); index++) 
     {
       ch = text.charAt(index);
       textWidth+= metrics.charWidth(ch);
     }
    return textWidth;
  }
     
  private void drawLabels(Graphics g, int xCenterOfDial, int yCenterOfDial, int dialRadius) {    
    double markAngle;
    String labelValue;    
    int labelXCenter, labelYCenter, widthOfLabel, heightOfLabel;

    g.setFont(font);
    FontMetrics metrics = g.getFontMetrics();
    for (int markNumber = 0; markNumber < numberOfMarksForDial; markNumber++) {
      markAngle = rulingLowValueAngleInRadians - markNumber*angleBetweenMarkingsInRadians;
      labelValue = form.format(lowValueForDialRuling + markNumber*incrementPerDialRuling);
      widthOfLabel = computeWidthOfText(labelValue, metrics);
      heightOfLabel = computeHeightOfText(labelValue, metrics);
      labelXCenter
	= (int) (Math.round(xCenterOfDial + Math.cos(markAngle)*((dialRadius - lengthOfRulingMarkers) -
								 distanceFromMarkToLabelCenter)) -
		 widthOfLabel/2);
      labelYCenter
	= (int) (Math.round(yCenterOfDial - Math.sin(markAngle)*((dialRadius - lengthOfRulingMarkers) -
								 distanceFromMarkToLabelCenter)) +
		 heightOfLabel/2);
      g.drawString(labelValue, labelXCenter, labelYCenter);
    }
  }

  private void drawNeedle(Graphics g, int xCenterOfDial, int yCenterOfDial, int dialRadius) {
    if (valueNumber != null) {
      int needleRadius = 3*dialRadius/4;
      double angleInRadians
	= Math.PI - (Math.PI*((value - lowValueForDialRuling)/(incrementPerDialRuling*(numberOfMarksForDial-1))));
      double needleX = (Math.cos(angleInRadians)*needleRadius);
      double needleY = (Math.sin(angleInRadians)*needleRadius);
      float needleWidth = 3, halfNeedleWidth = needleWidth/2;
      int xOffset, yOffset;
      yOffset = (int)(halfNeedleWidth*(Math.sin(Math.PI/2 + angleInRadians)));
      xOffset = Math.abs((int)(halfNeedleWidth*(Math.cos(Math.PI/2 + angleInRadians))));
      int x1 = xCenterOfDial + xOffset, y1 = yCenterOfDial + yOffset,
	x2 = xCenterOfDial - xOffset, y2 = yCenterOfDial - yOffset,
	x3 = x2 + (int)needleX, y3 = y2 - (int)needleY,
	x4 = x1 + (int)needleX, y4 = y1 - (int)needleY;
      int[] xPoints = {x1,x2,x3,x4};
      int[] yPoints = {y1,y2,y3,y4};
      g.fillPolygon(xPoints, yPoints, 4);
    }
  }
  
  /**
   * Paints a G2 dial, with the needle displayed
   * at the current value for the dial.
   */
  @Override
  public void paint(Graphics g) {
    super.paint(g);
    
    int left = 0, top = 0;
    Rectangle[] bounds = getExactBounds();
    int width =  bounds[0].width;
    int height =  bounds[0].height;
    int xCenterOfDial = left+width/2;
    int yCenterOfDial = top+height/2;
    int dialRadius = width/2;

    g.setColor(canvas.getColorTable().lookup(FOREGROUND_));
    drawRuling(g, xCenterOfDial, yCenterOfDial, dialRadius);
    drawLabels(g, xCenterOfDial, yCenterOfDial, dialRadius);
    drawNeedle(g, xCenterOfDial, yCenterOfDial, dialRadius);
  }

  /**
   * Updates the needle for this dial using the new value
   * contained within the event. Will automatically repaint
   * the dial.
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
    else {
      //System.out.println("UNHANDLED VALUE TO DISPLAY CHANGE IN DIAL");
    }
  }

  /**
   * Receives updates for attribute changes to the dial,
   * updating the WorkspaceDial for the attributes
   * LOW_VALUE_FOR_DIAL_RULING_ and INCREMENT_PER_DIAL_RULING_
   * as needed.  Will automatically repaint the meter.
   */
  @Override
  public void itemModified (ItemEvent e) {
    super.itemModified(e);
    Sequence denotationSequence = e.getDenotation();
    Structure denotation = (Structure) denotationSequence.elementAt(0);
    Symbol attributeName = (denotation!=null?(Symbol)denotation.getAttributeValue(NAME_, null):null);
    if (LOW_VALUE_FOR_DIAL_RULING_.equals(attributeName)) 
      lowValueForDialRuling = ((Number)e.getNewValue()).doubleValue();
    else if (INCREMENT_PER_DIAL_RULING_.equals(attributeName))
      incrementPerDialRuling = ((Number)e.getNewValue()).doubleValue();
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


