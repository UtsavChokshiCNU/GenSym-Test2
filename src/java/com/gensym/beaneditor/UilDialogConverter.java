package com.gensym.beaneditor;

import java.awt.Component;
import java.awt.Color;
import java.awt.Font;
import java.awt.Point;
import java.awt.Dimension;
import java.awt.Insets;
import java.awt.Rectangle;
import java.util.Enumeration;
import com.gensym.controls.*;
import com.gensym.beansruntime.StringVector;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Access;
import com.gensym.classes.Item;
import com.gensym.classes.G2List;
import com.gensym.classes.modules.uilroot.*;
import com.gensym.classes.modules.uillib.*;
import com.gensym.classes.modules.uildefs.*;
import com.gensym.classes.modules.uilsa.*;
import com.gensym.classes.modules.uilcombo.*;
import com.gensym.classes.modules.uilslide.*;

class UilDialogConverter{

  private static final Symbol DIMENSION_ = Symbol.intern("DIMENSION");
  private static final Symbol CENTER_X_ = Symbol.intern("CENTER-X");
  private static final Symbol CENTER_Y_ = Symbol.intern("CENTER-Y");
  private static final Symbol WIDTH_ = Symbol.intern("WIDTH");
  private static final Symbol HEIGHT_ = Symbol.intern("HEIGHT");
  private static final Symbol COMPONENTS_ = Symbol.intern("COMPONENTS");
  private static final Symbol TITLE_HEIGHT_ = Symbol.intern("TITLE-HEIGHT");
  private static final Symbol TITLE_ = Symbol.intern("TITLE");

  private static final Integer ZERO = new Integer(0);

  private static final Symbol UIL_GET_LABEL_TEXT_ = Symbol.intern ("UIL-GET-LABEL-TEXT");
  private static final Symbol UPP_GET_IDEAL_SELECTION_BOX_BOUNDS_ = Symbol.intern ("UPP-GET-IDEAL-SELECTION-BOX-BOUNDS");
  private static final Symbol UPP_GET_COMBO_BOX_LIST_CONTENTS_ = Symbol.intern("UPP-GET-COMBO-BOX-LIST-CONTENTS");
  private static final Symbol UIL_GET_RELATED_ITEMS_ = Symbol.intern ("UIL-GET-RELATED-ITEMS");
  private static final Symbol GROUPED_BY_ = Symbol.intern ("GROUPED-BY");
  private static final Symbol A_MESSAGE_BELONGING_TO_ = Symbol.intern ("A-MESSAGE-BELONGING-TO");

  private static final Symbol SMALL_ = Symbol.intern("SMALL");
  private static final Symbol MEDIUM_ = Symbol.intern("MEDIUM");
  private static final Symbol LARGE_ = Symbol.intern("LARGE");

  private static final Symbol VERTICAL_ = Symbol.intern("VERTICAL");
  private static final Symbol HORIZONTAL_ = Symbol.intern("HORIZONTAL");

  private static final Symbol UNSPECIFIED_ = Symbol.intern("UNSPECIFIED");
  private static final Symbol CONCLUDE_SELECTED_ = Symbol.intern("CONCLUDE-SELECTED");

  private static final int DEFAULT_INDICATOR_WIDTH = 10;
  private static final int DEFAULT_INDICATOR_HEIGHT = 10;

  private static final int HALF_SMALL_BUTTON_WIDTH = 8;
  private static final int HALF_MEDIUM_BUTTON_WIDTH = 10;
  private static final int HALF_LARGE_BUTTON_WIDTH = 15;
  private static final int HALF_SMALL_BUTTON_HEIGHT = 8;
  private static final int HALF_MEDIUM_BUTTON_HEIGHT = 10;
  private static final int HALF_LARGE_BUTTON_HEIGHT = 15;

  private static final boolean debug = false;


  private EditorFrame frame;
  private G2Access connection;
  private UilTailoredDialog dialog;
  private BeanCanvas canvas;
  private int originX, originY;
  private int verticalOffset;

  UilDialogConverter(EditorFrame frame, G2Access connection,
		     UilTailoredDialog dialog){
    this.frame = frame;
    this.connection = connection;
    this.dialog = dialog;
  }

  void convertDialog() throws G2AccessException{
    Structure layout = dialog.uppGetDialogLayout();
    Structure dimension = (Structure)layout.getAttributeValue(DIMENSION_, null);
    if (dimension != null){
      Integer centerX = (Integer)dimension.getAttributeValue(CENTER_X_, ZERO);
      Integer centerY = (Integer)dimension.getAttributeValue(CENTER_Y_, ZERO);
      Integer width = (Integer)dimension.getAttributeValue(WIDTH_, ZERO);
      Integer height = (Integer)dimension.getAttributeValue(HEIGHT_, ZERO);
      Sequence components = (Sequence)layout.getAttributeValue(COMPONENTS_, null);
      if (components != null){
	originX = centerX.intValue() - (width.intValue() / 2);
	originY = centerY.intValue() + (height.intValue() / 2);
	verticalOffset = -((Integer)layout.getAttributeValue(TITLE_HEIGHT_, ZERO)).intValue();

	canvas = frame.getCanvas();
	int canvasWidth = width.intValue();
	int canvasHeight = height.intValue() + verticalOffset;
	canvas.setContainerSize(canvasWidth, canvasHeight);
	Rectangle logicalBounds = canvas.getLogicalBounds();
	if (canvasWidth > logicalBounds.width)
	  canvas.growLogical(canvasWidth - logicalBounds.width + 10, true, false);
	if (canvasHeight > logicalBounds.height)
	  canvas.growLogical(canvasHeight - logicalBounds.height + 10, false, false);

	Enumeration controls = components.elements();
	while (controls.hasMoreElements()){
	  Item item = (Item)controls.nextElement();
	  convertControl(item);
	}
      }
    }
  }

  private void convertControl(Item item) throws G2AccessException{
    Component component = null;
    if (item instanceof UilRadioBox){
      UilRadioBox radioBox = (UilRadioBox)item;
      component = convertToG2Radiobox(radioBox, connection);
      convertLabel(radioBox, true);
    }
    else if (item instanceof UilCheckBox){
      UilCheckBox checkbox = (UilCheckBox)item;
      Object checkbuttons = connection.callRPC(UIL_GET_RELATED_ITEMS_, 
					  new java.lang.Object[] {GROUPED_BY_, checkbox});
      if (checkbuttons instanceof G2List){
	Sequence members = ((G2List)checkbuttons).getG2ListSequence();
	Enumeration buttons = members.elements();
	while (buttons.hasMoreElements()){
	  UilCheckButton cb = (UilCheckButton)buttons.nextElement();
	  Component g2checkbox = convertToG2Checkbox(cb);
	  Point location = computeLocation(cb);
	  addComponentToCanvas(g2checkbox, location.x, location.y, 
			       computeWidth(cb), computeHeight(cb) + verticalOffset);
	}
      }
      convertLabel(checkbox, true);
    }
    else if (item instanceof UilCheckButton)
      component = convertToG2Checkbox((UilCheckButton)item);
    else if (item instanceof UilIconToggleButton)
      component = convertToG2Checkbox((UilIconToggleButton)item);
    else if (item instanceof UilTextToggleButton)
      component = convertToG2Checkbox((UilTextToggleButton)item);
    else if (item instanceof UilIconPushbutton)
      component = convertToG2Button((UilIconPushbutton)item);
    else if (item instanceof UilTextPushbutton)
      component = convertToG2Button((UilTextPushbutton)item);
    else if (item instanceof UilScrollArea)
      component = convertToG2Listbox((UilScrollArea)item, connection);
    else if (item instanceof UilBoxBorderLeft)
      component = noMatch("<border>");
    else if (item instanceof UilLineSeparatorLeft)
      component = noMatch("<separator>");
    else if (item instanceof UilSlider)
      component = noMatch("<slider>");
    else if (item instanceof UilDialogTitle)
      component = null;//skip titles
    else if (item instanceof UilText)
      component = convertToG2Label((UilText)item, true);
    else if (item instanceof UilComboBox){
      UilComboBox comboBox = (UilComboBox)item;
      component = convertToG2DropDownChoice(comboBox, connection);
      convertLabel(comboBox, true);
    }
    else if (item instanceof UilSpinControlEntryBox)
      component = noMatch("<spin control>");
    else if (item instanceof UilEditBox){
      UilEditBox editBox = (UilEditBox)item;
      component = convertToG2TextField(editBox);
      convertLabel(editBox, true);
    }
    
    if (component != null){
      Point location = computeLocation(item);
      addComponentToCanvas(component, location.x, location.y + verticalOffset, 
			   computeWidth(item), computeHeight(item));
    }
  }

  private void convertLabel(Item item, boolean leftJustify) throws G2AccessException{    
    Object result = connection.callRPC(UIL_GET_LABEL_TEXT_, new java.lang.Object[] {item});
    if (result instanceof UilText){
      UilText label = (UilText)result;
      Component g2label = convertToG2Label(label, leftJustify);
      Point location = computeLocation(label);
      addComponentToCanvas(g2label, location.x, location.y + verticalOffset, 
			   computeWidth(label), computeHeight(label));
    }
  }
 
  private UilSelectionBox currentSelectionBox = null;
  private Structure currentSelectionBoxBounds = null;

  private Point computeLocation(Item item) throws G2AccessException{
    int x, y, width, height;
    if (item instanceof UilSelectionBox){
      if (!item.equals(currentSelectionBox)){
	currentSelectionBox = (UilSelectionBox)item;
	currentSelectionBoxBounds = (Structure)connection.callRPC(UPP_GET_IDEAL_SELECTION_BOX_BOUNDS_,
						       new Object[] {currentSelectionBox});
      }
      x = ((Integer)currentSelectionBoxBounds.getAttributeValue(CENTER_X_, ZERO)).intValue();
      y = ((Integer)currentSelectionBoxBounds.getAttributeValue(CENTER_Y_, ZERO)).intValue();
      width = ((Integer)currentSelectionBoxBounds.getAttributeValue(WIDTH_, ZERO)).intValue();
      height = ((Integer)currentSelectionBoxBounds.getAttributeValue(HEIGHT_, ZERO)).intValue();
    }
    else{
      x = item.getItemXPosition();
      y = item.getItemYPosition();
      width = item.getItemWidth();
      height = item.getItemHeight();
      if (item instanceof UilButton){
	width = width - DEFAULT_INDICATOR_WIDTH;
	height = height - DEFAULT_INDICATOR_HEIGHT;
      }
    }
    x = x - (width / 2);
    y = y + (height / 2);
    return new Point(x - originX, -(y - originY));
  }

  private int computeWidth(Item item) throws G2AccessException{
    if (item instanceof UilButton)
      return item.getItemWidth() - DEFAULT_INDICATOR_WIDTH;
    else if (item instanceof UilSelectionBox){
      if (!item.equals(currentSelectionBox)){
	currentSelectionBox = (UilSelectionBox)item;
	currentSelectionBoxBounds = (Structure)connection.callRPC(UPP_GET_IDEAL_SELECTION_BOX_BOUNDS_,
						       new Object[]{currentSelectionBox});
						       }
      return ((Integer)currentSelectionBoxBounds.getAttributeValue(WIDTH_, ZERO)).intValue();
    }
    return item.getItemWidth();
  }

  private int computeHeight(Item item) throws G2AccessException{
    if (item instanceof UilButton)
      return item.getItemHeight() - DEFAULT_INDICATOR_HEIGHT;
    else if (item instanceof UilSelectionBox){
      if (!item.equals(currentSelectionBox)){
	currentSelectionBox = (UilSelectionBox)item;
	currentSelectionBoxBounds = (Structure)connection.callRPC(UPP_GET_IDEAL_SELECTION_BOX_BOUNDS_,
						       new Object[]{currentSelectionBox});
      }
      return ((Integer)currentSelectionBoxBounds.getAttributeValue(HEIGHT_, ZERO)).intValue();
    }
    return item.getItemHeight();
  }
    
  private void addComponentToCanvas(Component bean, int x, int y, int width, int height){
    Wrapper wrapper = new Wrapper(Color.gray, bean.getClass(), x, y, width, height); 
    canvas.addElement(wrapper);
    wrapper.bean = bean;
    bean.setLocation(x, y);
    if (bean.getBackground() == null){
      Preferences prefs = Preferences.currentPreferences;
      bean.setBackground(prefs.getContainerBackgroundColor());
    }
    canvas.addElement(bean);
    Dimension unconstrainedSize = wrapper.getSize();
    wrapper.setSize(unconstrainedSize.width, unconstrainedSize.height);
    wrapper.ensureBeanBounds();
    BeanEditTool tool = (BeanEditTool)canvas.getEventHandler();
    ComponentBeanAdapter adapter = new ComponentBeanAdapter(bean, tool);
    wrapper.setComponentBeanAdapter(adapter);
    tool.dirtyBit = true;
  }

  private static Component convertToG2Radiobox(UilRadioBox radiobox, 
					       G2Access connection) throws G2AccessException{
    G2Radiobox g2Radiobox = new G2Radiobox();
    Object radiobuttons = connection.callRPC(UIL_GET_RELATED_ITEMS_, 
					new java.lang.Object[] {GROUPED_BY_, radiobox});
    if (radiobuttons instanceof G2List){
      Sequence radioboxMembers = ((G2List)radiobuttons).getG2ListSequence();
      Enumeration buttons = radioboxMembers.elements();
      StringVector members = new StringVector();
      StringVector labels = new StringVector();
      int count = 0;
      while (buttons.hasMoreElements()){
	UilRadioButton radiobutton = (UilRadioButton)buttons.nextElement();
	members.addElement("CHOICE"+count);
	labels.addElement(getLabelFromUilButton(radiobutton));
      }
      g2Radiobox.setMembers(members);
      g2Radiobox.setLabels(labels);
      Symbol orientation = radiobox.getUilButtonOrientation();
      if (orientation.equals(VERTICAL_)){
	g2Radiobox.setColumns(1);
	g2Radiobox.setRows(count);
      }
      else{
	g2Radiobox.setColumns(count);
	g2Radiobox.setRows(1);
      }
    }
    int xOffset = ((Integer)radiobox.getUilBorderXOffset()).intValue();
    int yOffset = ((Integer)radiobox.getUilBorderYOffset()).intValue();
    Object size = null;
    size = radiobox.getUilSize();
    if (size.equals(SMALL_)){
      xOffset = xOffset + HALF_SMALL_BUTTON_WIDTH;
      yOffset = yOffset + HALF_SMALL_BUTTON_HEIGHT;
    }
    else if (size.equals(MEDIUM_)){
      xOffset = xOffset + HALF_MEDIUM_BUTTON_WIDTH;
      yOffset = yOffset + HALF_MEDIUM_BUTTON_HEIGHT;
    }
    else if (size.equals(LARGE_)){
      xOffset = xOffset + HALF_LARGE_BUTTON_WIDTH;
      yOffset = yOffset + HALF_LARGE_BUTTON_HEIGHT;
    }
    Insets insets = g2Radiobox.getInsets();
    g2Radiobox.setInsets(new Insets(yOffset, xOffset, insets.bottom, insets.right));
    return g2Radiobox;
  }

  private static Component convertToG2Checkbox(UilButton toggleButton) throws G2AccessException{
    G2Checkbox g2Checkbox = new G2Checkbox();
    g2Checkbox.setLabel(getLabelFromUilButton(toggleButton));
    return g2Checkbox;
  }

  private static Component convertToG2Button(UilButton pushbutton) throws G2AccessException{
    G2Button g2Button = new G2Button();
    g2Button.setLabel(getLabelFromUilButton(pushbutton));
    return g2Button;
  }

  private static String getLabelFromUilButton(UilButton button) throws G2AccessException{
    Object label;
    if (button instanceof UilTextButton)
      label = (((UilTextButton)button).getLabel());
    else
      label = (((UilIconButton)button).getLabel());
    if (label == null) return "";
    else return label.toString();
  }

  private static Component convertToG2Listbox(UilScrollArea scrollArea, 
					      G2Access connection) throws G2AccessException {
    G2Listbox g2Listbox = new G2Listbox();
    boolean selectionList = false;
    Object target = scrollArea.getUilEventTargetObject();
    if (!target.equals(UNSPECIFIED_)){
      Object concludeStyle = scrollArea.getUilConcludeStyle();
      if (concludeStyle.equals(CONCLUDE_SELECTED_))
	selectionList = true;
    }
    else selectionList = true;
    if (selectionList){
      g2Listbox.getListType().value = G2Listbox.SELECTION;
      Object messages = connection.callRPC(UIL_GET_RELATED_ITEMS_, new java.lang.Object[] 
					   {A_MESSAGE_BELONGING_TO_, scrollArea});
      if (messages instanceof G2List){
	Enumeration scrollMsgs = ((G2List)messages).getG2ListSequence().elements();
	while (scrollMsgs.hasMoreElements()){
	  UilMessageObject msg = (UilMessageObject)scrollMsgs.nextElement();
	  g2Listbox.add("\""+msg.getMessageContents().toString()+"\"");
	}
      }
    }
      return g2Listbox;
  }

  private static Component convertToG2Label(UilText text, boolean leftJustify) throws G2AccessException{
    G2Label g2Label = new G2Label();
    Object label = text.getMessageContents();
    if (label == null) label = "";
    g2Label.setLabel(label.toString());
    if (leftJustify)
      g2Label.getAlignment().value = G2Label.LEFT;
    return g2Label;
  }


  private static Component convertToG2DropDownChoice(UilComboBox comboBox, 
						     G2Access connection) throws G2AccessException{
    G2DropDownChoice g2DropDownChoice = new G2DropDownChoice();
    g2DropDownChoice.removeAll();
    Sequence contents = (Sequence)connection.callRPC(UPP_GET_COMBO_BOX_LIST_CONTENTS_, 
						     new java.lang.Object[] {comboBox});
    Enumeration choices = contents.elements();
    while (choices.hasMoreElements())
      g2DropDownChoice.add( "\""+choices.nextElement().toString()+"\"");
    return g2DropDownChoice;    
  }

  private static Component convertToG2TextField(UilEditBox editBox){
    G2TextField g2TextField = new G2TextField();
    return g2TextField;
  }

  private static Component noMatch(String label){
    if (debug){
      G2Label g2Label = new G2Label();
      g2Label.setLabel(label);
      return g2Label;
    }
    else return null;
  }

}
