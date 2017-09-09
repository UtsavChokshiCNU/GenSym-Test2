package com.gensym.wksp;

import java.awt.*;
import java.util.Observer;
import java.util.Observable;
import com.gensym.irm.*;
import com.gensym.ntw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.classes.Item;
import com.gensym.classes.Entity;
import com.gensym.classes.ActionButton;
import com.gensym.jgi.G2AccessException;
import com.gensym.draw.TextCell;
import com.gensym.draw.TextStyle;

/**
 *
 * WorkspaceActionButton.java <p>
 * A WorkspaceElement that appears as an 3D action button with a label.
 *
 */

public class WorkspaceActionButtonImpl extends WorkspaceButtonImpl
{
  private TextCell textCell;
  private boolean notFormatted = true;
  Symbol faceColor = Symbol.intern ("LIGHT-GRAY");
  static final Symbol EXTRA_LIGHT_GRAY_ = Symbol.intern ("EXTRA-LIGHT-GRAY");
  static final Symbol DARK_GRAY_ = Symbol.intern ("DARK-GRAY");

  Symbol highLightColor = EXTRA_LIGHT_GRAY_;
  Symbol shadowColor = DARK_GRAY_;
  
  int armedXShift=2;
  int armedYShift=1;
  
  /**
   * @param actionButton The g2 ActionButton which this element is to represent.
   * @param parent The view into which this element is being added. 
   * @return an initialized WorkspaceElement.
   * @see initialize
   */
  public WorkspaceActionButtonImpl(ActionButton actionButton, WorkspaceView parent)
  throws G2AccessException {
    super((com.gensym.classes.Button)actionButton, parent);
  }

  @Override
  public void receivedInitialValues (com.gensym.util.ItemEvent e)
  {
    super.receivedInitialValues(e);
    Color lbColor =
      ((WorkspaceView)getParent()).getColorTable().lookup(labelColor);
    textCell = new TextCell(getExactBounds()[0].width,
			    getLabel(), new TextStyle(labelFont,4,8,2,true),
			    null, lbColor, 0, null);
    textCell.setLeftMargin(4);
    textCell.setRightMargin(2);
    textCell.setTopMargin(5);
    textCell.setTextJustification(TextCell.CENTER);
    notFormatted = true;
  }
  
  @Override
  public void itemModified (ItemEvent e) {
    super.itemModified(e);
    Sequence denotationSequence = e.getDenotation();
    Structure denotation = (Structure) denotationSequence.elementAt(0);
    Symbol attributeName
      = (denotation!=null?(Symbol)denotation.getAttributeValue(NAME_, null):null);
    if (LABEL_.equals(attributeName)) {
      textCell.setText(getLabel());
      notFormatted = true;
      canvas.invalidateElement(this);
    }
  }

  @Override
  public void handleWorkspaceItemColorsChanged(WorkspaceEvent event) {
    super.handleWorkspaceItemColorsChanged(event);
    Structure updateInfo = event.getInfo();
    Structure colorPatternChanges
	= (Structure) updateInfo.getAttributeValue(COLOR_PATTERN_CHANGES_, null);
    if (!(event.getItem() == getItem())) {
      textCell.setTextColor(canvas.getColorTable().lookup(labelColor));
      canvas.invalidateElement(this);
    }
  }

  private void drawLabel(Graphics g, int shift_x, int shift_y) {
    if (notFormatted){
      notFormatted = false;
      textCell.format(g);
    }
    if (label != null) {
      int left = shift_x;
      int top = shift_y;
      textCell.draw(g,left,top);
    }
  }

  @Override
  public void setSize(int width, int height) {
    super.setSize(width,height);
    bounds[0].width = width;
    if (textCell != null)
      textCell.setWidth(width);
    notFormatted = true;
  }
  
  @Override
  protected void changeArmedAppearance(boolean armed) {
    if (armed) {
      highLightColor = DARK_GRAY_;
      shadowColor = EXTRA_LIGHT_GRAY_;
    } else {
      highLightColor = EXTRA_LIGHT_GRAY_;
      shadowColor = DARK_GRAY_;
    }
  }

  /**
   * Paints a 3-D action button with a label.
   */
  @Override
  public void paint(Graphics g)
  {
    //super.paint(g);
    int left = 0;
    int top = 0;
    Rectangle[] bounds=getExactBounds();
    int width = bounds[0].width;
    int height = bounds[0].height;
    int right = left + width;
    int bottom = top + height;
    int depth = 3;
    
    Color buttonFaceColor = canvas.getColorTable().lookup(faceColor);
    Color buttonHighLightColor = canvas.getColorTable().lookup(highLightColor);
    Color buttonShadowColor = canvas.getColorTable().lookup(shadowColor);
    int[] highlightXPoints = {left, left,
			      right, right-depth,
			      left+depth, left+depth};
    int[] hightlightYPoints = {bottom, top,
			       top, top+depth,
			       top+depth, bottom-depth};
    int[] shadowXPoints = {left, right,
			   right, right-depth,
			   right-depth,left+depth};
    int[] shadowYPoints = {bottom, bottom,
			   top, top+depth,
			   bottom-depth, bottom-depth};
    g.setColor(buttonFaceColor);
    g.fillRect(left,top,width,height);
    g.setColor(buttonHighLightColor);
    g.fillPolygon(highlightXPoints, hightlightYPoints, 6);
    g.setColor(buttonShadowColor);
    g.fillPolygon(shadowXPoints, shadowYPoints, 6);        
    if (isArmed()) 
      drawLabel(g, armedXShift, armedYShift);
    else 
      drawLabel(g, 0, 0);
    helper.paintDecorations(g);
  }
  
}
