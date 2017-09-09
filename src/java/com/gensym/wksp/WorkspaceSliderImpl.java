package com.gensym.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.Observer;
import java.util.Observable;
import java.text.*;
import com.gensym.irm.*;
import com.gensym.ntw.*;
import com.gensym.draw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.util.ItemEvent;
import com.gensym.classes.Item;
import com.gensym.classes.Entity;
import com.gensym.classes.Button;
import com.gensym.classes.Slider;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.util.G2FontMap;
import com.gensym.jgi.G2ItemDeletedException;


/**
 *
 * WorkspaceSliderImpl <p>
 * A WorkspaceElement that appears as an Slider.
 */

public class WorkspaceSliderImpl extends WorkspaceButtonImpl
implements WorkspaceSlider, ContainerListener
{
  private SliderInput sliderInput;
  private TextBoxElement sliderValue;
  private TextBoxElement sliderLabel;
  private TextBoxElement maxValue;
  private TextBoxElement minValue;
  private Symbol whenToShowValue;
  private boolean setWhileSliding;
  private boolean dragging = false;
  private static int tbwidth = 60, tbheight = 20, textPadding = 25;
  private static Font theFont = G2FontMap.get(18);
  private static FontMetrics metrics
  = Toolkit.getDefaultToolkit().getFontMetrics(theFont);
  private static DecimalFormat minMaxForm
  = (DecimalFormat)(new ScientificDecimalFormat());
  static {
    ((ScientificDecimalFormat)minMaxForm).setPreserveInts(true);
    minMaxForm.setMaximumIntegerDigits(8);
    minMaxForm.setMinimumIntegerDigits(1);
    minMaxForm.setMaximumFractionDigits(3);
    minMaxForm.setMinimumFractionDigits(1);
  }
  private static DecimalFormat valueForm
  = (DecimalFormat)(new ScientificDecimalFormat());
  static {
    ((ScientificDecimalFormat)valueForm).setPreserveInts(true);
    valueForm.setMaximumIntegerDigits(5);
    valueForm.setMinimumIntegerDigits(1);
    valueForm.setMaximumFractionDigits(3);
    valueForm.setMinimumFractionDigits(1);
  }
  private static final Symbol[] sliderNeededAttributes = {LABEL_,MINIMUM_VALUE_, MAXIMUM_VALUE_, SET_VALUE_WHILE_SLIDINGQ_, WHEN_TO_SHOW_VALUE_};  

  /**
   * @param slider The g2 Slider which this element is to represent.
   * @param parent The view into which this element is being added. 
   * @return an initialized WorkspaceElement.
   */
  public WorkspaceSliderImpl(Slider slider, WorkspaceView parent)
  throws G2AccessException {
    super((Button)slider, parent);
    parent.addContainerListener(this);
  }

  @Override
  protected Symbol[] getNeededAttributes() {
    return sliderNeededAttributes;
  }
  
  @Override
  public void receivedInitialValues (com.gensym.util.ItemEvent e)
  {
    super.receivedInitialValues(e);    
    try {
      Number currentValue;
      try {
	Slider slider = (Slider)getItem();
	currentValue = slider.getSliderValue();
      } catch (ClassCastException cce) {
	Trace.exception(cce);////Bug in virtualAttribute; sometimes is a Boolean!(reset g2)
	currentValue = null;
      }
      init((Slider)e.getItem(), (WorkspaceView)getParent(), currentValue);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }

  private static final Object createValue(double val, Number min, Number max)
  {
    Object newValue = null;
    if (min == null || max == null )
      return newValue;
    if (min instanceof Integer && max instanceof Integer) 
      newValue = new Integer(Math.round((float)val));
    else
      newValue = new Double(val);
    return newValue;
  }

  private void init(Slider slider, WorkspaceView parent, Number currentValue)
       throws G2AccessException
  {
    Rectangle bounds = getBounds();
    setWhileSliding = slider.getSetValueWhileSliding();
    Number currentMinValue = slider.getMinimumValue();
    Number currentMaxValue = slider.getMaximumValue();
    Color lbColor = parent.getColorTable().lookup(labelColor);
    TextStyle style = new TextStyle(theFont,0,0,2,true);
    int currentStringWidth; 
    String currentString;
    //Create the minValue TextBox
    currentString = (currentMinValue != null)?minMaxForm.format(currentMinValue):"";
    int minValueWidth = computeWidthOfTextString(currentString, metrics);
    minValue = new TextBoxElement(bounds.x-minValueWidth,
				  bounds.y - tbheight,
				  minValueWidth,
				  tbheight,
				  currentString,
				  style,
				  null,lbColor,0, null);
    TextCell textCell = minValue.getTextCell();
    textCell.setTextJustification (TextCell.RIGHT);
    //Create the label TextBox
    currentString = getLabel();
    currentStringWidth = computeWidthOfTextString(currentString, metrics);
    sliderLabel = new TextBoxElement(bounds.x-(minValueWidth + currentStringWidth +
					       textPadding),
				     bounds.y - tbheight,
				     currentStringWidth,tbheight,
				     currentString,
				     style,
				     null,lbColor,0, null);
    //Create the maxValue TextBox
    currentString = (currentMaxValue != null)?minMaxForm.format(currentMaxValue):"";
    currentStringWidth = computeWidthOfTextString(currentString, metrics);
    maxValue = new TextBoxElement(bounds.x+bounds.width+textPadding/2,
				  bounds.y - tbheight,
				  currentStringWidth,
				  tbheight,
				  currentString,
				  style,
				  null,lbColor,0, null);
    //Create the sliderValue TextBox
    currentString = (currentValue != null)?valueForm.format(currentValue):"";
    currentStringWidth = computeWidthOfTextString(currentString, metrics);
    sliderValue = new TextBoxElement(bounds.x+bounds.width/2-currentStringWidth/2,
				     bounds.y+bounds.height,
				     currentStringWidth,
				     tbheight,
				     currentString,
				     style,null,lbColor,0,null);
    setValueVisibility(slider.getWhenToShowValue());
    //Create the slider input
    sliderInput = new SliderInput(this);
    sliderInput.setLocation(getSliderLocation(currentValue),
			    bounds.y - sliderInput.getSize().height);
    //Add the subblocks to the canvas
    parent.addElement(sliderLabel);
    parent.addElement(sliderValue);
    parent.addElement(minValue);
    parent.addElement(maxValue);
    parent.addElement(sliderInput);
  }
  
  private void setValueVisibility(Symbol when) {
    TextCell textCell = sliderValue.getTextCell();
    whenToShowValue = when;
    boolean newState =
      (ALWAYS_.equals(when)||
       dragging && ONLY_WHILE_SLIDING_.equals(when))?
       true : false;

    if (textCell.isDrawText()!=newState) {
      textCell.setDrawText(newState);
      canvas.invalidateElement(sliderValue);
    }
  }

  private int getSliderLocation(Number currentValue) {
    Rectangle bounds = getBounds();
    try {
      Slider slider = (Slider)getItem();
      Number min = slider.getMinimumValue();
      Number max = slider.getMaximumValue();
      if (currentValue == null || min == null || max == null)
	return bounds.x;
      double minVal = min.doubleValue(), maxVal = max.doubleValue(),
	current = currentValue.doubleValue();
      double val
	= (Math.max(Math.min(current, maxVal),minVal)-minVal)/(maxVal-minVal);
      int halfWidth = sliderInput.getSize().width/2;
      return Math.max(Math.min(bounds.x+bounds.width-halfWidth,
			       bounds.x+(int)(val*bounds.width)-halfWidth),
		      bounds.x-halfWidth);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
      return bounds.x;
    }
  }

  @Override
  public void componentAdded(ContainerEvent e) {
  }
  
  /**
   * Performs any slider cleanup work when the slider
   * is removed from the workspace.
   */
  @Override
  public void componentRemoved(ContainerEvent e) {
    if (e.getChild() == this) {
      canvas.removeElement(sliderLabel);
      canvas.removeElement(sliderValue);
      canvas.removeElement(minValue);
      canvas.removeElement(maxValue);
      canvas.removeElement(sliderInput);
    }
  }

  public void setDragging(boolean dragging) {
    this.dragging = dragging;
    setValueVisibility(whenToShowValue);
  }

  // Take 1 pixel off the width, since we had added a pixel to be able to
  // draw the whole icon
  // final for performance only
  private static final double computeValueFromSliderPosition(int xPos, Rectangle bounds, double max, double min) {
    int width = bounds.width;
    // paranoia for very small widths
    double boundsWidth =
      width <= 1 ? (double)width : (double)(width - 1);
    double val = Math.min(1.0,((double)xPos - (double)bounds.x)/boundsWidth);
    val = val*(max - min);
    return min + val;
  }

  /**
   * @param deltaX an integer representing the number of
   * pixels by which to shift the SliderInput of the Slider.
   * Restricts such movement to within the bounds of the slider.
   * Will call setSliderValueUsingCurrentLocation if
   * setValueWhileSliding is true for this Slider.
   * @see setSliderValueUsingCurrentLocation
   */
  public void doInputShift(int deltaX) {
    try {
      Slider slider = (Slider)getItem();
      Number min = slider.getMinimumValue();
      Number max = slider.getMaximumValue();
      if (min == null || max == null)
	return;
      Point sliderInputLocation = sliderInput.getLocation();
      int newLocation 
	= Math.min(Math.max(sliderInputLocation.x + deltaX,
			    getSliderLocation(min)),
		   getSliderLocation(max));
      deltaX = newLocation - sliderInputLocation.x;
      canvas.shiftElement(sliderInput, deltaX, 0);
      if (slider.getSetValueWhileSliding())
	setSliderValueUsingCurrentLocation();
      else {
	Rectangle bounds = getBounds();
	int xPos = sliderInput.getLocation().x +
	  sliderInput.getSize().width/2;
	double val = computeValueFromSliderPosition(xPos, bounds, max.doubleValue(), min.doubleValue());
	
	Rectangle[] oldSliderValueBounds = sliderValue.getExactBounds();
	TextCell cell = sliderValue.getTextCell();
	Object valueToSet = null;
	valueToSet = createValue(val, min, max);
	String newString = valueForm.format(valueToSet);
	cell.setText(newString);
	int newWidth = computeWidthOfTextString(newString, metrics);
	sliderValue.setSize(newWidth, tbheight);
	sliderValue.setLocation(bounds.x+bounds.width/2-newWidth/2,
				bounds.y+bounds.height);
	canvas.invalidate(oldSliderValueBounds);
	canvas.invalidateElement(sliderValue);
      }
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }

  /**
   * Sets the Slider in G2 using the SliderInput's current
   * location.
   */
  public void setSliderValueUsingCurrentLocation() throws G2AccessException
  {
    Slider slider = (Slider)getItem();
    Number min = slider.getMinimumValue();
    Number max = slider.getMaximumValue();
    if (min == null || max == null )
      return;
    Rectangle bounds = getBounds();
    int xPos = sliderInput.getLocation().x +
      sliderInput.getSize().width/2;
    
    double val = computeValueFromSliderPosition(xPos, bounds, max.doubleValue(), min.doubleValue());
    Object valueToSet = createValue(val, min, max);
    slider.setSliderValue((Number)valueToSet);
  }
  
  /**
   * Receives updates for attribute changes to the slider,
   * updating the WorkspaceSlider for the attributes
   * LABEL_, MINIMUM_VALUE_, MAXIMUM_VALUE, WHEN_TO_SHOW_VALUE_
   * and SET_VALUE_WHILE_SLIDINGQ_ accordingly.  Will automatically
   * repaint the slider if needed.
   */
  @Override
  public void itemModified (ItemEvent e) {
    super.itemModified(e);
    Sequence denotationSequence = e.getDenotation();
    Structure denotation = (Structure) denotationSequence.elementAt(0);
    Rectangle bounds = getBounds();
    String newString;
    int newWidth;
    Symbol attributeName
      = (denotation!=null?(Symbol)denotation.getAttributeValue(NAME_, null):null);
    if (LABEL_.equals(attributeName)) {
      Rectangle[] oldLabelBounds = sliderLabel.getExactBounds();
      
      String label = getLabel();
      sliderLabel.getTextCell().setText(label);
      int labelWidth = computeWidthOfTextString(label, metrics);
      sliderLabel.setLocation(bounds.x-(minValue.getSize().width + labelWidth +
					textPadding),
			      bounds.y - tbheight);
      sliderLabel.setSize(labelWidth, tbheight);

      canvas.invalidate(oldLabelBounds);
      canvas.invalidateElement(sliderLabel);
    } else if (MIMIMUM_VALUE_.equals(attributeName)) {
      Rectangle[] oldMinValueBounds = minValue.getExactBounds();
      Rectangle[] oldLabelBounds = sliderLabel.getExactBounds();
      
      newString = minMaxForm.format(e.getNewValue());
      minValue.getTextCell().setText(newString);
      newWidth = computeWidthOfTextString(newString, metrics);
      minValue.setLocation(bounds.x-newWidth,bounds.y-tbheight);
      minValue.setSize(newWidth, tbheight);
      sliderLabel.setLocation(bounds.x-(minValue.getSize().width +
					textPadding +
					sliderLabel.getSize().width),
			      bounds.y-tbheight);
      canvas.invalidate(oldMinValueBounds);
      canvas.invalidate(oldLabelBounds);
      canvas.invalidateElement(minValue);
      canvas.invalidateElement(sliderLabel);
    } else if (MAXIMUM_VALUE_.equals(attributeName)) {
      Rectangle[] oldSliderInputBounds = sliderInput.getExactBounds();
      Rectangle[] oldMaxValueBounds = maxValue.getExactBounds();
      newString = minMaxForm.format(e.getNewValue());
      maxValue.getTextCell().setText(newString);
      newWidth = computeWidthOfTextString(newString, metrics);
      maxValue.setSize(newWidth, tbheight);

      canvas.invalidate(oldSliderInputBounds);
      canvas.invalidate(oldMaxValueBounds);
      canvas.invalidateElement(sliderInput);
      canvas.invalidateElement(maxValue);
    } else if (WHEN_TO_SHOW_VALUE_.equals(attributeName)) {
      setValueVisibility((Symbol)e.getNewValue());
    } else if (SET_VALUE_WHILE_SLIDINGQ_.equals(attributeName)) {
      setWhileSliding = ((Boolean)e.getNewValue()).booleanValue();
    }
  }
  
  /**
   * Invoked when the Slider value has changed.
   * @param event A WorkspaceEvent with ID of ITEM_CHANGE.<p>
   * The event's info will contain a structure whose attribute named by
   * WorkspaceElement.ATTRIBUTE_NAME_ will be SLIDER_VALUE_ and whose
   * attribute named by WorkspaceElement.NEW_VALUE_ will contain the slider's
   * new value to display.  This method will update the WorkspaceSlider
   * using the info contained within the event.
   */ 
  @Override
  public void handleSliderValueChanged(WorkspaceEvent event) {
    Structure info = event.getInfo();
    Rectangle bounds=getBounds();
    Rectangle[] oldSliderValueBounds = sliderValue.getExactBounds();
    Rectangle[] oldSliderInputBounds = sliderInput.getExactBounds();
    Number currentValue = (Number)info.getAttributeValue(NEW_VALUE_, null);

    if (!dragging)
      sliderInput.setLocation(getSliderLocation(currentValue),
			      sliderInput.getLocation().y);
    
    TextCell cell = sliderValue.getTextCell();
    String newString;
    if (currentValue == null) {
      try {
	newString = valueForm.format(((Slider)getItem()).getMinimumValue());
      } catch (G2ItemDeletedException ide) {
	Trace.exception(ide);
	return;
      } catch (G2AccessException g2ae) {
	// this is from an event, shouldn't get an exception...
	throw new UnexpectedException(g2ae);
      }
    } else
      newString = valueForm.format(currentValue);
    cell.setText(newString);
    int newWidth = computeWidthOfTextString(newString, metrics);
    sliderValue.setSize(newWidth, tbheight);
    sliderValue.setLocation(bounds.x+bounds.width/2-newWidth/2,
			    bounds.y+bounds.height);
    
    canvas.invalidate(oldSliderValueBounds);
    canvas.invalidate(oldSliderInputBounds);
    canvas.invalidateElement(sliderValue);
    canvas.invalidateElement(sliderInput);
  }
  
  @Override
  public void shift (int deltaX, int deltaY)
  {
    super.shift(deltaX, deltaY);
    canvas.shiftElement(sliderLabel, deltaX, deltaY);
    canvas.shiftElement(sliderValue, deltaX, deltaY);
    canvas.shiftElement(minValue, deltaX, deltaY);
    canvas.shiftElement(maxValue, deltaX, deltaY);
    canvas.shiftElement(sliderInput, deltaX, deltaY);    
  }
  
}
