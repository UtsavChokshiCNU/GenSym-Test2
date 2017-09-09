package com.gensym.wksp;
 
import java.awt.*;
import java.util.Observer;
import java.util.Observable;
import com.gensym.irm.*;
import com.gensym.ntw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.util.G2ColorMap;
import com.gensym.ntw.util.G2FontMap;
import com.gensym.classes.Item;
import com.gensym.classes.Block;
import com.gensym.classes.Entity;
import com.gensym.classes.Button;
import com.gensym.jgi.G2AccessException;
import com.gensym.draw.BasicDrawElement;

/**
 *
 * WorkspaceButton <p>
 * A WorkspaceElement that appears as a button.
 *
 */


public class WorkspaceButtonImpl extends WorkspaceIconImpl
implements WorkspaceButton
{
  boolean armed = false;
  String label = null;
  Symbol labelColor;
  private static int defaultFontSize = 18;
  static Font labelFont = G2FontMap.get(defaultFontSize);
  static final Symbol FOREGROUND_ = Symbol.intern ("FOREGROUND");
  private static final Symbol[] neededAttributes = {LABEL_};
  
  /**
   * @param button The g2 Button which this element is to represent.
   * @param parent The view into which this element is being added. 
   * @return an initialized WorkspaceElement.
   */
  public WorkspaceButtonImpl(Button button, WorkspaceView parent)
       throws G2AccessException
  {
    super((Entity)button, parent);
    labelColor =  FOREGROUND_;
    ((Item)button).addItemListener((com.gensym.util.ItemListener)this, getNeededAttributes());
  }

  protected Symbol[] getNeededAttributes() {
    return neededAttributes;
  }
  
  protected String getLabel() {
    return label;
  }

  protected void setLabel(String label) {
    this.label = label;
  }

  static int computeWidthOfTextString(String string, FontMetrics metrics) {
    char newLine = '\n';
    int maxSoFar = 0;  
    int stringWidth = 0;
    char currentChar;
    if (string != null) {
      int charCount = string.length();
      for (int i=0;i<charCount;i++) {
	currentChar = string.charAt(i);	
	if (currentChar == newLine) {
 	  maxSoFar = Math.max(maxSoFar, stringWidth);
 	  stringWidth = 0;
 	} else  
	stringWidth = stringWidth + metrics.charWidth(currentChar);
      }
    }
    return Math.max(stringWidth, maxSoFar);
  }
  
  static void drawCenteredString(Graphics g, String string,
				 int left, int top,
				 int containerWidth,
				 int containerHeight) {
    top = top + (2*containerHeight)/3;
    FontMetrics metrics = g.getFontMetrics();
    int stringWidth = computeWidthOfTextString(string, metrics);
    left = left + ((containerWidth-stringWidth)/2);
    g.drawString(string,left,top);
  }

  @Override
  public void receivedInitialValues (com.gensym.util.ItemEvent e) {
    Button button = (Button)e.getItem();
    try {
      setLabel(button.getLabel());
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }  

  /**
   * Receives updates for attribute changes to the button,
   * updating the WorkspaceButton for the attributes
   * LABEL_ as needed.  Will automatically repaint the button.
   */
  @Override
  public void itemModified (ItemEvent e) {
    super.itemModified(e);
    Sequence denotationSequence = e.getDenotation();
    Structure denotation = (Structure) denotationSequence.elementAt(0);
    Symbol attributeName = (denotation!=null?(Symbol)denotation.getAttributeValue(NAME_, null):null);
    if (LABEL_.equals(attributeName)) {
      setLabel((String)(e.getNewValue()));
    }
    Rectangle bounds = getExactBounds()[0];
    Rectangle[] invalRegion = {bounds};
    ((WorkspaceView)getParent()).invalidate(invalRegion);
  }
 
  protected static final Symbol ITEM_ACTIVE_ = Symbol.intern ("ITEM-ACTIVE");
  protected static final Symbol OK_ = Symbol.intern ("OK");
  protected boolean shouldChangeArm(boolean state) {
    if (state) {
      try {
	Block block = (Block)getItem();
	return block.getItemActive() && OK_.equals(block.getItemStatus());
      } catch (G2AccessException g2ae) {
	// Shouldn't actually even get an exception here, as we should
	// be subscribed to this item.
	Trace.exception(g2ae);
	return false;
	// couldn't figure out if it was OK, why do it?
      }
    } else
      return true;
  }      
  
  /**
   * Sets the state of the button to armed
   */
  @Override
  public void setArmed(boolean state) {
    if (!shouldChangeArm(state))
      return;
    this.armed = state;
    changeArmedAppearance(state);
    ((WorkspaceView) canvas).invalidateElement(this);
  }

  protected void changeArmedAppearance(boolean state) {
  }

  /**
   * @return true iff the button is armed
   */
  public boolean isArmed() {
    return this.armed;
  }
  
  @Override
  public void dispose() throws G2AccessException {
    Item item = getItem();
    if (item != null)
      item.removeItemListener(this, getNeededAttributes());
    super.dispose();
  }
}
