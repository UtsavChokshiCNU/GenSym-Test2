package com.gensym.wksp;

import java.awt.*;
import java.util.Observer;
import java.util.Observable;
import com.gensym.irm.*;
import com.gensym.ntw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.util.G2ColorMap;
import com.gensym.classes.Item;
import com.gensym.classes.Entity;
import com.gensym.classes.CheckBox;
import com.gensym.jgi.G2AccessException;


/**
 *
 * WorkspaceCheckBoxImpl.java <p>
 * A WorkspaceElement that appears as a check box with a label.
 *
 */

public class WorkspaceCheckBoxImpl extends WorkspaceButtonImpl
implements WorkspaceCheckBox
{
  private final static Symbol ON_INDICATOR_ = Symbol.intern("ON-INDICATOR");
  private final static Symbol PENDING_INDICATOR_ = Symbol.intern("PENDING-INDICATOR");
  private static Font font
  = new Font("sansserif",Font.PLAIN, 14);
  private final static Boolean noValue = new Boolean(false);
  private static Boolean status = noValue;
  private Rectangle iconBounds;

  /**
   * @param checkBox The g2 CheckBox which this element is to represent.
   * @param parent The view into which this element is being added. 
   * @return an initialized WorkspaceElement.
   */ 
  public WorkspaceCheckBoxImpl(CheckBox checkBox, WorkspaceView parent)
  throws G2AccessException {
    super((com.gensym.classes.Button)checkBox, parent);
    setArmed(false);
    //ICON-COLOR:java.awt.Color[r=0,g=0,b=0],
  }

  @Override
  public void receivedInitialValues (com.gensym.util.ItemEvent e) {
    super.receivedInitialValues(e);
    try {
      CheckBox cb = (CheckBox)e.getItem();
      Symbol status = cb.getButtonStatus();
      setStatus(status);
    } catch (G2AccessException g2ae) {
      setStatus(noValue);
      Trace.exception(g2ae);
    }
  }
  
  private void setStatus(Symbol newStatus) {
    setStatus(newStatus == null ? noValue : new Boolean(newStatus.equals(ON_)));
  }

  /**
   * @return a Boolean representing whether or not this check box is
   * checked.
   */
  public Boolean getStatus() {
    return status;
  }

  /**
   * Sets whether or not this check box's status is checked.
   * @param newStatus a Boolean representing the desired new status
   * of this button.
   */
  public void setStatus(Boolean newStatus) {
    this.status = newStatus;
    Structure newRegionOverrides = iconRendering.getRegionOverrides();
    if (newStatus.booleanValue()) 
      newRegionOverrides.setAttributeValue(ON_INDICATOR_,
					   canvas.getColorTable().lookup(FOREGROUND_));
    else 
      newRegionOverrides.setAttributeValue(ON_INDICATOR_, G2ColorMap.TRANSPARENT);//null?
    iconRendering.setRenderingOverrides(iconRendering.getVariableOverrides(),
					newRegionOverrides);
  }

  /**
   * Changes the appearance of the button to show that it is armed
   */
  @Override
  protected void changeArmedAppearance(boolean armed) {
    Structure newRegionOverrides = iconRendering.getRegionOverrides();
    if (armed)
      newRegionOverrides.setAttributeValue(PENDING_INDICATOR_,
					   canvas.getColorTable().lookup(FOREGROUND_));
    else
      newRegionOverrides.setAttributeValue(PENDING_INDICATOR_, null);
    iconRendering.setRenderingOverrides(iconRendering.getVariableOverrides(),
					newRegionOverrides);
  }

  @Override
  public void handleWorkspaceItemColorsChanged(WorkspaceEvent event) {
    super.handleWorkspaceItemColorsChanged(event);
    setStatus(status);
  }
  
  /**
   * Handles the Workspace event, updating the status of this button
   * accordingly.
   * @see setStatus
   */
  @Override
  public void handleButtonStatusChanged(WorkspaceEvent event) {
    Structure info = event.getInfo();
    setStatus((Symbol) info.getAttributeValue(NEW_VALUE_, null));
    Rectangle[] invalRegion = getExactBounds();//make more efficient
    ((WorkspaceView)getParent()).invalidate(invalRegion);
  }

  /**
   * @param label a String representing the label to be drawn
   * to the right of the button.
   */
  @Override
  protected void setLabel(String label) {
    super.setLabel(label);
    if (iconBounds == null)
      iconBounds = new Rectangle(getExactBounds()[0]);
    FontMetrics metrics = java.awt.Toolkit.getDefaultToolkit().getFontMetrics(labelFont);
    int stringWidth = computeWidthOfTextString(label, metrics);
    int labelXMargin = 8;
    if (stringWidth != 0)
      stringWidth+= 2*labelXMargin;
    setSize(iconBounds.width + stringWidth,
	    iconBounds.height);
  }
    
  private void drawLabel(Graphics g, int shift_x, int shift_y) {
    int left = shift_x;
    int top = shift_y;
    Rectangle[] bounds=getExactBounds();
    int width = bounds[0].width - iconBounds.width;
    int height = bounds[0].height;
    g.setColor(canvas.getColorTable().lookup(labelColor));
    g.setFont(labelFont);
    drawCenteredString(g,label,left,top,width,height);
  }
  
  /**
   * Paints a checkbox with a label.
   */
  @Override
  public void paint(Graphics g)
  {
    super.paint(g);
    if (status == noValue){
      g.setColor(Color.black);
      g.setFont(font);
      int borderWidth = 6;
      Rectangle bounds = getExactBounds()[0];
      int baselineX = borderWidth;
      int baselineY = bounds.height - borderWidth;
      g.drawString("?",baselineX,baselineY);
    }
    if (label != null) 
      drawLabel(g, iconBounds.width, 0);
  }
}
