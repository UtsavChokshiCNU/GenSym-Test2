package com.gensym.wksp;

import java.awt.*;
import com.gensym.irm.*;
import com.gensym.ntw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.util.TextBoxFormat;
import java.util.*;
import com.gensym.draw.*;
import com.gensym.classes.TextBox;
import com.gensym.classes.NameBox;
import com.gensym.classes.Item;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.util.G2FontMap;
import com.gensym.util.WorkspaceEvent;
import javax.swing.JTextArea;
import java.awt.event.KeyListener;
import java.awt.event.KeyEvent;
import com.gensym.dlg.WarningDialog;
import javax.swing.JScrollPane;
import javax.swing.JComponent;
import javax.swing.text.JTextComponent;
import com.gensym.editor.text.EditContext;
import com.gensym.editor.text.G2TextAreaKeyAdapter;
import com.gensym.editor.text.G2SideParser;
import com.gensym.editor.text.ParserController;
import com.gensym.editor.text.Prompter;

/**
 *
 * WorkspaceTextBox <p>
 * A DrawElement that appears as a textbox
 *
 */
public class WorkspaceTextBoxImpl extends TextBoxElement
implements WorkspaceTextBox, Editable, ParserController {
  
  private WorkspaceElementHelper helper;
  private Symbol g2BackgroundColor;
  private Symbol g2LineColor;
  private Symbol g2BorderColor;
  private boolean editing;
  private JTextArea currentEditContext;
  private G2TextAreaKeyAdapter keyListener;
  private G2SideParser parser;
  private static final Symbol BACKGROUND_COLOR_ = Symbol.intern ("BACKGROUND-COLOR");
  private static final Symbol TEXT_COLOR_       = Symbol.intern ("TEXT-COLOR");
  private static final Symbol BORDER_COLOR_     = Symbol.intern ("BORDER-COLOR");
  private static final Symbol TRANSPARENT_      = Symbol.intern ("TRANSPARENT");
  private static final Symbol hm18              = Symbol.intern ("HM18");
  private static final Symbol FOREGROUND_COLOR_ = Symbol.intern ("FOREGROUND-COLOR");
  private boolean notFormatted = true;
  private static final Symbol NAMES_ = Symbol.intern ("NAMES");
  private static final Symbol CLASS_NAME_ = Symbol.intern ("CLASS-NAME");
  private TextBoxFormat textBoxFormat;
  private double xMag = 1.0, yMag = 1.0;
  private static Symbol[] neededAttributes = {TEXT_ALIGNMENT_, TEXT_};
  /**
   * @param textBox The g2 TextBox which this element is to represent.
   * @param parent The view into which this element is being added. 
   * @return an initialized WorkspaceElement.
   */
  public WorkspaceTextBoxImpl(TextBox textBox, WorkspaceView parent)
       throws G2AccessException
  {
    this(textBox,
	 getTextBoxFormat(textBox, textBox.getFormatType()),
	 (PersistentCanvas)parent);
    this.helper = createHelper(this, (Item) textBox, parent);
    ((Item)textBox).addItemListener((com.gensym.util.ItemListener)this, neededAttributes);
  }

  private WorkspaceTextBoxImpl(TextBox textBox,
			       TextBoxFormat textBoxFormat,
			       PersistentCanvas canvas)
       throws G2AccessException
  {
    this(textBox,
	 textBoxFormat,
	 canvas,
    	 getG2BackgroundColor(textBox, textBoxFormat),
	 getG2LineColor(textBox, textBoxFormat),
	 getG2BorderColor(textBox, textBoxFormat),
	 WorkspaceElementHelper.getExactBounds((Item)textBox));
    this.textBoxFormat = textBoxFormat;
  }

  @Override
  public void setValue(String newValue)throws InvalidTypeException
  {
    try {
      ((TextBox)getItem()).setText(newValue);
    } catch(G2AccessException g2ae) {
      throw new InvalidTypeException(g2ae.getMessage());
    }
  }
  private boolean allowedToEdit() {
    return true;
  }
  
  @Override
  public int getIndex(Point p) {
    if (currentEditContext != null) {
      Rectangle bounds = currentEditContext.getBounds();
      ((WorkspaceView)getParent()).translateWindowToView(p);
      p.translate(-bounds.x, -bounds.y);
      return currentEditContext.viewToModel(p);
    } else
      return -1;
  }
  
  @Override
  public void setIndex(int index){
    if (currentEditContext != null)
      currentEditContext.setCaretPosition(index);
  }
  @Override
  public void accept() {
    boolean ok = parser.attemptToConcludeParsingContext(getItem(), Boolean.TRUE);
    if (ok)
      setEditing(false);
  }
  @Override
  public void escape() {
    setEditing(false);
  }      
  @Override
  public void setEditing(boolean editing) {
    this.editing = editing;
    if (!editing) {
      if (currentEditContext != null) {
	currentEditContext.removeKeyListener(keyListener);
	Prompter prompter = EditContext.getContext().getPrompter();
	if (prompter != null)
	  prompter.removePromptSelectionListener(keyListener);
	keyListener = null;
	EditContext.getContext().removeEditor(currentEditContext);
	parser = null;
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
      TextCell textCell = getTextCell();
      Rectangle bounds = getBounds();
      currentEditContext = new InlineEditor(textCell.getFont(),
					    textCell.getTopMargin(),
					    14,//textCell.getLeftMargin() 
					    textCell.getBottomMargin(),
					    textCell.getRightMargin());
      keyListener = new KeyAdapter(currentEditContext, this);            
      currentEditContext.addKeyListener(keyListener);
      Prompter prompter = EditContext.getContext().getPrompter();
      if (prompter != null)
	prompter.addPromptSelectionListener(keyListener);
      Item item = getItem();
      TwAccess cxn
	= (TwAccess)((com.gensym.classes.ItemImpl)item).getContext();
      try {
	parser = EditContext.getContext().addEditor(currentEditContext,
						    cxn,
						    item.getG2ClassName(),
						    TEXT_);
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
      canvas.addElement(currentEditContext);
      currentEditContext.setText(textCell.getText());     
      bounds.width=Math.max(bounds.width, currentEditContext.getPreferredSize().width);
      currentEditContext.setBounds(bounds);
      currentEditContext.requestFocus();
      canvas.invalidateElement(this);
    }
  }

  private static final int TEXT_BOX_MAX_EDITOR_WIDTH = 400;    
  class InlineEditor extends JTextArea {
    public InlineEditor(Font theFont,
			int topMargin, int leftMargin, int bottomMargin, int rightMargin) {
      setBorder(new javax.swing.border.CompoundBorder
		(new javax.swing.border.LineBorder(java.awt.Color.black),
		 new javax.swing.border.EmptyBorder(topMargin, leftMargin, bottomMargin, rightMargin)));
      setFont(theFont);
      setEditable(true);      
    }
    @Override
    public void reshape(int x, int y, int width, int height) {
      if (width > TEXT_BOX_MAX_EDITOR_WIDTH) {
	  width = TEXT_BOX_MAX_EDITOR_WIDTH;
	  currentEditContext.setLineWrap(true);
	  currentEditContext.setWrapStyleWord(true);
      } else {
	currentEditContext.setLineWrap(false);
	currentEditContext.setWrapStyleWord(false);	
      }
      super.reshape(x, y, width, height);
    }
    @Override
    public boolean isManagingFocus() {
      return true;
    }
    public void keyTyped(KeyEvent e){}
    @Override
    protected void processMouseEvent(java.awt.event.MouseEvent me) {
      super.processMouseEvent(me);
      requestFocus();
    }
  }
  
  class KeyAdapter extends G2TextAreaKeyAdapter {
    public KeyAdapter(JTextArea textArea, ParserController controller) {
      super(textArea, controller);
    }
    private void updateSizeAndInvalidate() {
      JTextArea editBox = currentEditContext;
      if (editBox != null) {
	//size?
	Rectangle[] oldBounds = new Rectangle[] {editBox.getBounds()};
	Dimension pSize = editBox.getPreferredSize();
	pSize.width+=getTextCell().getRightMargin();
	editBox.setSize(pSize);
	PersistentCanvas canvas = (PersistentCanvas)getParent();
	canvas.invalidate(oldBounds);
	canvas.invalidateElement(editBox);
      }      
    }
    @Override
    public void promptSelected(String prompt) {
      super.promptSelected(prompt);
      updateSizeAndInvalidate();
    }
    @Override
    public void keyPressed(KeyEvent e) {
      JTextArea editBox = currentEditContext;
      if (editBox == null)
	return;
      super.keyPressed(e);
      PersistentCanvas canvas = (PersistentCanvas)getParent();
      if (canvas != null && currentEditContext != null)
	canvas.invalidateElement(currentEditContext);
    }
    @Override
    public void keyTyped(KeyEvent e) {
      super.keyTyped(e);
      updateSizeAndInvalidate();
    }
  }
  
  private WorkspaceTextBoxImpl(TextBox textBox,
			       TextBoxFormat textBoxFormat,
			       PersistentCanvas canvas,
			       Symbol g2BackgroundColor,
			       Symbol g2LineColor,
			       Symbol g2BorderColor,
			       Rectangle[] bounds)
  throws G2AccessException
  {
    super(bounds[0].x, bounds[0].y,
	  bounds[0].width, bounds[0].height,
	  TextBoxElement.TOP,
	  "",
	  makeStyleFromTextBoxFormat(textBoxFormat),
	  canvas.getColorTable().lookup(g2BackgroundColor),
	  canvas.getColorTable().lookup(g2LineColor),
	  getBorderWidth(textBoxFormat),
	  canvas.getColorTable().lookup(g2BorderColor),
	  textBoxFormat.getTopMargin(),
	  textBoxFormat.getBottomMargin());
    this.g2BackgroundColor = g2BackgroundColor;
    this.g2LineColor = g2LineColor;
    this.g2BorderColor = g2BorderColor;
    TextCell textCell = getTextCell();
    textCell.setDrawBackground(!TRANSPARENT_.equals(g2BackgroundColor));
    textCell.setDrawBorder(!TRANSPARENT_.equals(g2BorderColor));
    textCell.setDrawText(!TRANSPARENT_.equals(g2LineColor));
    //textCell.setLeftMargin(textBoxFormat.getLeftMargin().intValue()); causing
    //premature clipping in name-boxes
    if (!(textBox instanceof NameBox))
      textCell.setRightMargin(textBoxFormat.getRightMargin().intValue());
    //Structure colorPattern = textBox.getItemColorPattern();
  }

  private static WorkspaceElementHelper createHelper (WorkspaceElement elt,
						      Item item,
						      WorkspaceView parent)
  throws G2AccessException
  {
    return new WorkspaceElementHelper(elt,
				      (DrawElement)elt,
				      (Component)elt,
				      item,
				      parent);
  }

  private static String getText(TextBox textBox)
       throws G2AccessException
  {
    return textBox.getText();//"Default Text";
  }
        
  private static TextBoxFormat getTextBoxFormat(TextBox textBox,
						Symbol formatType)
       throws G2AccessException
  {    
    Structure formatInfo = null;
    TwAccess theContext
      = (TwAccess)((com.gensym.classes.ItemImpl)textBox).getContext(); //hack for now
    if (formatType == null)
      formatType = textBox.getDefaultTextBoxFormatNameForClass();
    if (formatType != null) 
      formatInfo = theContext.getFormatInfo(formatType);
    else
      formatInfo = new Structure();
    return new TextBoxFormat(formatInfo);
  }

  private static TextStyle makeStyleFromTextBoxFormat(TextBoxFormat textBoxFormat)
  {
    TextStyle style 
      = new TextStyle(G2FontMap.get(getG2Font(textBoxFormat)),
		  textBoxFormat.getLeftMargin().intValue(),  //first line indent
		  textBoxFormat.getLeftMargin().intValue() + 
		  textBoxFormat.getSubsequentLineIndent().intValue(), 
		  getLineSpacing(textBoxFormat),
		  true);
    style.setLineHeight(textBoxFormat.getLineHeight());
    style.setBaselineOffset(textBoxFormat.getBaselineOffset());
    return style;
  }

  private static int getBorderWidth(TextBoxFormat textBoxFormat) {
    return textBoxFormat.getTextBorderWidth().intValue();
  }

  private static int getLineSpacing(TextBoxFormat textBoxFormat) {
    return textBoxFormat.getTextLineSpacing().intValue();
  }

  private static Symbol getG2Font(TextBoxFormat textBoxFormat) {
    return textBoxFormat.getFont();
  }

  private static int getFontSize(TextBoxFormat textBoxFormat) {
    Symbol font = getG2Font(textBoxFormat);
    int fontsize = 14;
    if (font.equals(hm18)) fontsize = 18;
    return fontsize;
  }
  
  /**
   * @return the color of the text of this element.
   */
  private static Symbol getG2LineColor(TextBox textBox,
				      TextBoxFormat textBoxFormat)
       throws G2AccessException
  {
    Structure colorPattern = textBox.getItemColorPattern();
    Symbol textlinecolor = (Symbol)colorPattern.getAttributeValue(TEXT_COLOR_, null);
    if (textlinecolor == null)
      textlinecolor = textBoxFormat.getTextLineColor();
    return textlinecolor;
  }

  private static Symbol getG2BackgroundColor(TextBox textBox,
					     TextBoxFormat textBoxFormat) 
       throws G2AccessException
  {
    Structure colorPattern = textBox.getItemColorPattern();
    Symbol g2BackgroundColor = (Symbol) colorPattern.getAttributeValue(BACKGROUND_COLOR_, null);
    if (g2BackgroundColor == null)
      g2BackgroundColor = textBoxFormat.getTextBackgroundColor();
    return g2BackgroundColor;
  }
					      
  /**
   * @return the color of the border of this element.
   */
  private static Symbol getG2BorderColor(TextBox textBox,
					 TextBoxFormat textBoxFormat) 
       throws G2AccessException
  {
    Structure colorPattern = textBox.getItemColorPattern();
    Symbol textbordercolor = (Symbol)colorPattern.getAttributeValue(BORDER_COLOR_, null);
    if (textbordercolor == null)
      textbordercolor = textBoxFormat.getTextBorderColor();
    return textbordercolor;
  }

  
  /**
   * Method for receiving overrides to the colors of an icon's regions.
   * @param colorPatternChange A Structure of region-name: color-name attributes.
   */
  private void updateColorPattern(Structure colorPatternChange, boolean isOnThisItem) {
    if (isOnThisItem) {
      Symbol textColor
	= (Symbol)colorPatternChange.getAttributeValue(TEXT_COLOR_, null);
      Symbol bgColor
	= (Symbol)colorPatternChange.getAttributeValue(BACKGROUND_COLOR_, null);
      Symbol borderColor
	= (Symbol)colorPatternChange.getAttributeValue(BORDER_COLOR_, null);
      updateColors(textColor, bgColor, borderColor);
    } else {
      updateColors(g2LineColor, g2BackgroundColor, g2BorderColor);
    }
      
  }

  private void updateColors(Symbol textColor, Symbol bgColor, Symbol borderColor) {
    TextCell textCell = getTextCell();
    if (textColor != null) {
      g2LineColor = textColor;
      changeColor("text", canvas.getColorTable().lookup(g2LineColor));
      textCell.setDrawText(!g2LineColor.equals(TRANSPARENT_));      
    }
    if (bgColor != null) {
      g2BackgroundColor = bgColor;
      changeColor("background",
		  canvas.getColorTable().lookup(g2BackgroundColor));
      textCell.setDrawBackground(!g2BackgroundColor.equals(TRANSPARENT_));
    }
    if (borderColor != null) {
      g2BorderColor = borderColor;
      changeColor("border", canvas.getColorTable().lookup(g2BorderColor));
      textCell.setDrawBorder(!g2BorderColor.equals(TRANSPARENT_));
    }
  }
  
  @Override
  public void paint(Graphics g)
  {
    if (currentEditContext != null) return;
    if (notFormatted){
      notFormatted = false;
      format(g);
    }
    super.paint(g);

    if (isCut ()) {
      Rectangle[] exbnds = getExactBounds ();
      Rectangle bnds = exbnds[0];
      helper.paintCutStatus (g, bnds.x, bnds.y, bnds.width, bnds.height);
    }
  }

  @Override
  public void shift (int shift_x, int shift_y)
  {
    helper.shift(shift_x, shift_y);
    super.shift(shift_x,shift_y);
  }

  @Override
  public boolean inside(int logical_x, int logical_y)
  {
    return contains(logical_x, logical_y);
  }

  /**
   */
  @Override
  public void handleWorkspaceItemColorsChanged(WorkspaceEvent event) {
    Structure updateInfo = event.getInfo();
    Structure colorPatternChanges
	= (Structure) updateInfo.getAttributeValue(COLOR_PATTERN_CHANGES_, null);
    if (event.getItem().equals(getItem()))
      updateColorPattern(colorPatternChanges, true);
    else
      updateColorPattern(colorPatternChanges, false);
    canvas.invalidateElement(this);
  }

  /*WORKSPACE ELEMENT API*/

  @Override
  public void handleWorkspaceItemMoved(WorkspaceEvent event) {
    helper.shift(event);   
  }

  /**
   * Resizes the DrawElement to the given Rectangle.
   */
  @Override
  public void handleWorkspaceItemResized(WorkspaceEvent event) {
    helper.resize(event);
  }

  @Override
  public void setSize(int width, int height) {
    notFormatted = true;
    super.setSize(width,height);
  }
  
  @Override
  public void receivedInitialValues (com.gensym.util.ItemEvent e) {
    TextBox textBox = (TextBox)getItem();
    String newText = "";
    int justification=TextCell.LEFT;
    TextCell textCell = getTextCell();
    Font newFont = null;
    try {
      newText = textBox.getText();
      justification = getJustificationCode(textBox.getTextAlignment());
      Number nMag = textBox.getTextXMagnification();
      if (nMag != null)
	xMag = nMag.doubleValue();
      nMag = null;
      nMag = textBox.getTextYMagnification();
      if (nMag != null)
	yMag = nMag.doubleValue();
      double mag = Math.max(xMag, yMag);
      if (mag != 1.0) {
	int fontSize = TextBoxFormat.g2FontToFontsize(textBoxFormat.getFont());
	newFont = G2FontMap.get((int)(((double)fontSize)*mag));
      }
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    if (newFont != null)
      textCell.setFont(newFont);
    textCell.setTextJustification(justification);
    textCell.setText(newText);
  }

  @Override
  public void handleWorkspaceItemFontChanged(WorkspaceEvent e)
  {
    Structure updateInfo = e.getInfo();
    Symbol attributeName 
       = ((Symbol)updateInfo.getAttributeValue(ATTRIBUTE_NAME_, null));
    boolean invalidate = false;
    TextCell textCell = getTextCell();
    Object newValue = updateInfo.getAttributeValue(NEW_VALUE_, null);
    if (TEXT_X_MAGNIFICATION_.equals(attributeName)) {
      xMag = ((Number)newValue).doubleValue();
      textCell.setFont(computeFont());
      invalidate = true;      
    } else if (TEXT_Y_MAGNIFICATION_.equals(attributeName)) {
      yMag = ((Number)newValue).doubleValue();
      textCell.setFont(computeFont());
      invalidate = true;      
    } else if (FORMAT_TYPE_.equals(attributeName)) {
      try {
	this.textBoxFormat = getTextBoxFormat((TextBox)getItem(),
					      (Symbol)newValue);
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
	return;
      }
      textCell.setFont(computeFont());
      invalidate = true;
    }
    if (invalidate) {
      notFormatted = true;
      canvas.invalidateElement(this);
    }
  }

  private Font computeFont()
  {
    int fontSize = TextBoxFormat.g2FontToFontsize(textBoxFormat.getFont());
    fontSize=(int)(((double)fontSize)*Math.min(xMag, yMag));
    return G2FontMap.get(fontSize);
  }
  
  @Override
  public void itemModified (com.gensym.util.ItemEvent e) {
    Sequence denotationSequence = e.getDenotation();
    Structure denotation = (Structure) denotationSequence.elementAt(0);
    Symbol attributeName
      = (denotation!=null?(Symbol)denotation.getAttributeValue(NAME_, null):null);
    if (TEXT_.equals(attributeName)) {
      Object newValue = e.getNewValue();
      TextCell textCell = getTextCell();
      textCell.setText((String)newValue);
      notFormatted = true;
      helper.itemModified(e);
    } else if (TEXT_ALIGNMENT_.equals(attributeName)) {
      Object newValue = e.getNewValue();
      TextCell textCell = getTextCell();
      int justification=getJustificationCode((Symbol)newValue);
      textCell.setTextJustification(justification);
      notFormatted = true;
      helper.itemModified(e);
    } 
  }
  
  private int getJustificationCode(Symbol justification)
  {
    if (LEFT_.equals(justification))
      return TextCell.LEFT;
    if (CENTER_.equals(justification))
      return TextCell.CENTER;
    if (RIGHT_.equals(justification))
      return TextCell.RIGHT;

    return TextCell.LEFT;
  }
  
  @Override
  public void itemDeleted (com.gensym.util.ItemEvent e) {
    helper.itemDeleted(e);
  }

  @Override
  public Item getItem() {
    return helper.getItem();
  }

  @Override
  public void select () {
    helper.select();
  }

  @Override
  public void unselect () {
    helper.unselect();
  }

  @Override
  public boolean isSelected () {
    return helper.isSelected();
  }

  @Override
  public DraggingGhost getDraggingGhost (int left, int top, int width, int height) {
    if (true) //outlineDrag
      return helper.getDraggingGhost(left,top,width,height);
    else {
      DraggingGhost ghost = new DraggingGhost ();
      ghost.elements = new Component[1];
      ghost.boundsArray[0] = new Rectangle (left, top, width, height);
      //iconElement.setPaintMode(false);
      TextBoxElement tbe = new TextBoxElement(left, top, width, height,
					      getTextCell());
      tbe.setPaintMode(false);
      ghost.elements[0] = tbe;
      return ghost;
    }
    //return helper.getDraggingGhost(left,top,width,height);
  }

  @Override
  public DraggingGhost getDraggingGhost () {
    Rectangle eltBounds = getExactBounds()[0];
    int left = eltBounds.x;
    int top = eltBounds.y;
    int width = eltBounds.width, height = eltBounds.height;
    // left -=1; top -=1; width +=1; height +=1;
    return getDraggingGhost (left, top, width, height);
    //return helper.getDraggingGhost();
  }
  
  @Override
  public DraggingGhost getDraggingGhost (int markerLocn, int currentX, int currentY) {
    return helper.getDraggingGhost(markerLocn, currentX, currentY);
  }

  @Override
  public PopupMenu getContextMenu () {
    return helper.getContextMenu();
  }

  @Override
  public boolean isCut () {
    return helper.isCut ();
  }

  @Override
  public void setCut (boolean newCutState) {
    helper.setCut (newCutState);
    repaint ();
  }

  @Override
  public void dispose() {
    super.dispose();
    try {
      getItem().removeItemListener(this);
    } catch (G2AccessException e) {
      System.err.println("G2AccessException caught in WorkspaceTextBoxImpl dispose");
    }
    this.helper = null;
    this.textBoxFormat = null;
  }

}
