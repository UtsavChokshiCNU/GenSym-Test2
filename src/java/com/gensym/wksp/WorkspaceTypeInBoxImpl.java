package com.gensym.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.Observer;
import java.util.Observable;
import java.text.*;
import com.gensym.irm.*;
import com.gensym.ntw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.util.ItemEvent;
import com.gensym.draw.TextBoxElement;
import com.gensym.draw.TextStyle;
import com.gensym.draw.TextCell;
import com.gensym.classes.Item;
import com.gensym.classes.QuantitativeParameter;
import com.gensym.classes.QuantitativeVariable;
import com.gensym.classes.SymbolicParameter;
import com.gensym.classes.SymbolicVariable;
import com.gensym.classes.TextParameter;
import com.gensym.classes.TextVariable;
import com.gensym.classes.IntegerParameter;
import com.gensym.classes.IntegerVariable;
import com.gensym.classes.FloatParameter;
import com.gensym.classes.FloatVariable;
import com.gensym.classes.LogicalParameter;
import com.gensym.classes.LogicalVariable;
import com.gensym.classes.Entity;
import com.gensym.classes.Button;
import com.gensym.classes.TypeInBox;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.util.G2FontMap;


/**
 * WorkspaceTypeInBox <p>
 * A WorkspaceElement that appears as an type in text box.
 * (INCOMPETE)
 */

public class WorkspaceTypeInBoxImpl extends WorkspaceButtonImpl
implements WorkspaceTypeInBox, ContainerListener, Editable

{
  public Object food = canvas;
  private boolean notFormatted = true;
  private TextCell textCell;
  private EditContext currentEditContext;
  private boolean editing = false;
  private static final Symbol BACKGROUND_ = Symbol.intern ("BACKGROUND");
  private Object currentValue;
  private String currentValueAsString;
  private TextBoxElement typeInBoxLabel;
  private int padding = 7;
  private static int textPadding = 12, tbheight = 20;
  private static Font theFont = G2FontMap.get(18);
  private static FontMetrics metrics
  = Toolkit.getDefaultToolkit().getFontMetrics(theFont);
  private static ScientificDecimalFormat form = new ScientificDecimalFormat();
  static {
    form.setMaximumIntegerDigits(5);
    form.setMinimumIntegerDigits(1);
    form.setMaximumFractionDigits(3);
    form.setMinimumFractionDigits(1);
    form.setGroupingUsed(false);
    form.setPreserveInts(true);
  }
  private boolean blankForTypeIn;
  private Item variableOrParameter;
  private int typeOfVariableOrParameter;
  private static final int TEXT = 0;
  private static final int FLOAT = 1;
  private static final int LOGICAL = 2;
  private static final int INTEGER = 3;
  private static final int QUANTITATIVE = 4;
  private static final int SYMBOL = 5;
  
  /**
   * @param typeInBox The g2 Button which this element is to represent.
   * @param parent The view into which this element is being added. 
   * @return an initialized WorkspaceElement.
   */
  public WorkspaceTypeInBoxImpl (TypeInBox typeInBox, WorkspaceView parent)
  throws G2AccessException {
    super((Button)typeInBox, parent);
  }

  @Override
  public void receivedInitialValues (com.gensym.util.ItemEvent e) {
    super.receivedInitialValues(e);
    try {
      TypeInBox tib = (TypeInBox)e.getItem();
      WorkspaceView parent = (WorkspaceView)getParent();
      Object currentValue = tib.getTypeInBoxValue();
      init(tib, parent, currentValue);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }

  private void initializeVariable(Item variableOrParameter)
  {
    this.variableOrParameter = variableOrParameter;
    this.typeOfVariableOrParameter
      = typeOfVariableOrParameter(variableOrParameter);
  }
  
  private void init(TypeInBox typeInBox,
		    WorkspaceView parent,
		    Object currentDisplayValue)
       throws G2AccessException 
  {
    initializeVariable((Item)typeInBox.getTypeInBoxVariableOrParameter());
    this.blankForTypeIn = typeInBox.getBlankForTypeIn();
    
    parent.addContainerListener(this);
    currentValue = currentDisplayValue;
    currentValueAsString = getCurrentValueAsString();
    //Create the label TextBox
    String currentString = getLabel();
    TextStyle style = new TextStyle(theFont,0,0,2,true);
    Color lbColor = parent.getColorTable().lookup(labelColor);
    int currentStringWidth = computeWidthOfTextString(currentString, metrics);
    Rectangle bounds = getBounds();
    typeInBoxLabel = new TextBoxElement(bounds.x-(currentStringWidth+textPadding),
					bounds.y+(bounds.height-tbheight)/2,
					currentStringWidth,tbheight,
					currentString,
					style,
					null,lbColor,0, null);
    parent.addElement(typeInBoxLabel);
    style = new TextStyle(theFont,0,16,2,true);
    this.textCell = new TextCell(bounds.width-2*padding, 
				 currentValueAsString,
				 style,
				 null,//bgcolor
				 lbColor,
				 0,//border_width,
				 null //bordercolor
				 );
  }

  private static int typeOfVariableOrParameter(Item variableOrParameter) {
    int type = -1;
    if (variableOrParameter instanceof TextParameter ||
	variableOrParameter instanceof TextVariable)
      type = TEXT;
    else if (variableOrParameter instanceof IntegerParameter ||
	variableOrParameter instanceof IntegerVariable)
      type = INTEGER;
    else if (variableOrParameter instanceof FloatParameter ||
	variableOrParameter instanceof FloatVariable)
      type = FLOAT;
    else if (variableOrParameter instanceof LogicalParameter ||
	variableOrParameter instanceof LogicalVariable)
      type = LOGICAL;
    else if (variableOrParameter instanceof QuantitativeParameter ||
	     variableOrParameter instanceof QuantitativeVariable)
      type = QUANTITATIVE;
    else if (variableOrParameter instanceof SymbolicParameter ||
	     variableOrParameter instanceof SymbolicVariable)
      type = SYMBOL;
    else {
      Trace.exception(new Exception("WorkspaceTypeInBoxImpl::Can not determine type for " + variableOrParameter)); 
    }
    return type;
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
      canvas.removeElement(typeInBoxLabel);
      if (currentEditContext != null)
	canvas.removeElement(currentEditContext);
    }
  }

  /**
   * Receives updates for attribute changes to the TypeInBox,
   * updating the WorkspaceTypeInBox for the attribute LABEL_.
   * Will automatically repaint the WorkspaceTypeInBox if needed.
   */
  @Override
  public void itemModified (ItemEvent e) {
    super.itemModified(e);
    Sequence denotationSequence = e.getDenotation();
    Structure denotation = (Structure) denotationSequence.elementAt(0);
    Symbol attributeName
      = (denotation!=null?(Symbol)denotation.getAttributeValue(NAME_, null):null);

    Rectangle bounds = getBounds();
    String newString;
    int newWidth;

    if (LABEL_.equals(attributeName)) {
      Rectangle[] oldLabelBounds = typeInBoxLabel.getExactBounds();
      
      String label = getLabel();
      typeInBoxLabel.getTextCell().setText(label);
      int labelWidth = computeWidthOfTextString(label, metrics);
      typeInBoxLabel.setLocation(bounds.x-(labelWidth+textPadding),
				 bounds.y+(bounds.height-tbheight)/2);
      typeInBoxLabel.setSize(labelWidth, tbheight);
      canvas.invalidate(oldLabelBounds);
      canvas.invalidateElement(typeInBoxLabel); 
    } else if (BLANK_FOR_TYPE_INQ_.equals(attributeName)) {
      blankForTypeIn = ((Boolean)e.getNewValue()).booleanValue();
    } else if (ITEM_ACTIVE_.equals(attributeName) &&
	       !((Boolean)e.getNewValue()).booleanValue()){
      setEditing(false);
    }
  }

  private static final Symbol ITEM_ACTIVE_ = Symbol.intern ("ITEM-ACTIVE");
  @Override
  public void handleTypeInBoxVariableOrParameterChanged(WorkspaceEvent event) {
    Structure info = event.getInfo();
    initializeVariable((Item)info.getAttributeValue(NEW_VALUE_, null));
  }
      
  @Override
  public void handleTypeInBoxValueChanged(WorkspaceEvent event) {
    Structure info = event.getInfo();
    currentValue = info.getAttributeValue(NEW_VALUE_, "*error*");
    currentValueAsString = getCurrentValueAsString();
    textCell.setText(currentValueAsString);
    notFormatted = true;
    canvas.invalidateElement(this);
  }

  /**
   * Updates the TypeInBox for changes to the Workspace's foreground
   * and Background colors.
   */
  @Override
  public void handleWorkspaceItemColorsChanged(WorkspaceEvent event) {    
    typeInBoxLabel.changeColor("text",canvas.getColorTable().lookup(labelColor));
    textCell.setTextColor(canvas.getColorTable().lookup(labelColor));
    canvas.invalidateElement(typeInBoxLabel);
    canvas.invalidateElement(this);
  }
  
  /**
   * Resizes the WorkspaceTypeInBox.
   */
  @Override
  public void handleWorkspaceItemResized(WorkspaceEvent event) {
    helper.resize(event);
    int width = getSize().width;
    textCell.setWidth(width-2*padding);
    notFormatted = true;
  }

  @Override
  public void shift (int deltaX, int deltaY)
  {
    super.shift(deltaX, deltaY);
    canvas.shiftElement(typeInBoxLabel, deltaX, deltaY);
    if (currentEditContext != null)
      canvas.shiftElement(currentEditContext, deltaX, deltaY);
  }

  private Object createValue(String newStringValue)
  throws InvalidTypeException
  {
    Object newValue = null;
    newStringValue = newStringValue.trim();
    switch (typeOfVariableOrParameter) {
    case TEXT:
      if (newStringValue.startsWith("\"") &&
	  newStringValue.endsWith("\"")) {
	int length = newStringValue.length();
	newValue = newStringValue.substring(1,length-1);
      } else
	throw new InvalidTypeException(newStringValue + " is not a Text value");
      break;
    case INTEGER:
      try {
	newValue = new Integer(newStringValue);
      } catch (NumberFormatException nfeI) {
	throw new InvalidTypeException(newStringValue + " is not an Integer");
      }
      break;
    case QUANTITATIVE:
      try {
	newValue = new Double(newStringValue);
      } catch (NumberFormatException nfeD) {
	throw new InvalidTypeException(newStringValue + " is not a Quantity");
      }
      break;
    case SYMBOL:
      newValue = Symbol.intern(newStringValue.toUpperCase());
      break;
    case FLOAT:
      try {
	newValue = new Double(newStringValue);
      } catch (NumberFormatException nfeD) {
	throw new InvalidTypeException(newStringValue + " is not a Float");
      }
      break;
    case LOGICAL:
      if (newStringValue.equals("true"))
	newValue = Boolean.TRUE;
      else if (newStringValue.equals("false"))
	newValue = Boolean.FALSE;
      else throw new InvalidTypeException(newStringValue + " is not a Logical value");
      break;
    default:
      Trace.exception(new Exception("WorkspaceTypeInBoxImpl::Unknown variable type " +
				    typeOfVariableOrParameter));
    }
    return newValue;
  }
  
  @Override
  public void setValue(String newValue)
  throws InvalidTypeException
  {
    try {
      ((TypeInBox)getItem()).setTypeInBoxValue(createValue(newValue));
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }

  private String getCurrentValueAsString() {
    if (currentValue instanceof String)
      return "\"" + currentValue + "\"";
    else if (currentValue instanceof Integer)
      return currentValue.toString();
    else if (currentValue instanceof Double) 
      return form.format(currentValue);
    else if (currentValue instanceof Boolean)
      return currentValue.toString();
    else if (currentValue instanceof Symbol)
      return ((Symbol)currentValue).getPrintValue().toLowerCase();
    else
      return "****";
  }

  private boolean allowedToEdit()
  {
    try {
      Item item = getItem();
      return (variableOrParameter != null &&
	      ((com.gensym.classes.Block)variableOrParameter).getItemActive() &&
	      item != null &&
	      ((com.gensym.classes.Block)item).getItemActive());
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
      return false;
    }
  }

  @Override
  public int getIndex(Point p) {return -1;} 
  @Override
  public void setIndex(int index) {
    if (currentEditContext != null)
      currentEditContext.setIndex(index);
  }
  
  @Override
  public void setEditing(boolean editing) {
    this.editing = editing;
    if (!editing) {
      if (currentEditContext != null) {
	canvas.removeElement(currentEditContext);
	canvas.invalidateElement(this);
	canvas.requestFocus();
      }
      currentEditContext = null;
      return;
    }
    if (!allowedToEdit()) {
      this.editing = false; return;
    }
    if (currentEditContext == null) {
      TextStyle style = new TextStyle(labelFont,0,0,2,true);
      Rectangle bounds = getBounds();
      currentEditContext = new EditContext(this, bounds.width,style);
      canvas.addElement(currentEditContext);
      currentEditContext.setFont(labelFont);
      currentEditContext.setBounds(bounds);
      currentEditContext.setMinimumSize(new Dimension(bounds.width,
						      bounds.height));
      if (!blankForTypeIn) 
	currentEditContext.addString(currentValueAsString);
      currentEditContext.requestFocus();
    }
  }

  /**
   * Paints a type in text box.
   */
  @Override
  public void paint(Graphics g)
  {
    //if (textCell == null) return;
    //not finished initializing yet bug (need to investigate more first)
    
    if (notFormatted) {
      textCell.format(g);
      notFormatted = false;
    }
		      
    Rectangle[] bounds=getExactBounds();
    int width = bounds[0].width;
    int height = bounds[0].height;
    g.setFont(labelFont);

    if (editing) {
      return;
    } else {
      g.setColor(canvas.getColorTable().lookup(labelColor));
      if (isArmed()) {
	g.fillRect(0,0,width-1,height-1);
	g.setColor(canvas.getColorTable().lookup(BACKGROUND_));
      }
      textCell.setTextColor(g.getColor());
      textCell.draw(g, padding, padding);
      g.setColor(canvas.getColorTable().lookup(labelColor));
      g.drawRect(0,0,width-1,height-1);
    }       
  }

  @Override
  public void dispose() throws G2AccessException{
    getItem().removeItemListener(this);
    Container parent = getParent();
    if (parent != null)
      parent.removeContainerListener(this);
    super.dispose();
  }

}
