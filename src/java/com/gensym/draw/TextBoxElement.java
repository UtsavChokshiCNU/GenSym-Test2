package com.gensym.draw;

import java.awt.*;
import java.lang.Math;

/**
 *
 * TextBoxElement
 *
 */
public class TextBoxElement extends BasicDrawElement
{
  private boolean paintMode = true;  
  private boolean textboxdebugp = false;
  private TextCell textCell;
  private Rectangle[] bounds;
  private Object[] logicalColorNames = { "text", "background", "border" };
  
  public static final int LEFT   = 0;
  public static final int CENTER = 1;
  public static final int RIGHT  = 2;
  public static final int TOP    = 3;
  public static final int BOTTOM = 4;

  private int outerTopMargin = 0;
  private int outerBottomMargin = 0;

  private int verticalJustification = CENTER;

  public TextBoxElement(int x, int y, int width, int height,
			TextCell textCell) 
  {
    bounds = new Rectangle[1];
    bounds[0] = new Rectangle(x,y, width,height);
    setSize(width,height);
    this.textCell = textCell;
    setLocation(x,y);
  }

  public TextBoxElement(int x, int y, int width, int height,
			int verticalJustification,
			TextCell textCell,
			int outerTopMargin,
			int outerBottomMargin)
  {
    bounds = new Rectangle[1];
    bounds[0] = new Rectangle(x,y, width,height);
    setSize(width,height);
    this.textCell = textCell;
    this.verticalJustification = verticalJustification;
    this.outerTopMargin = outerTopMargin;
    this.outerBottomMargin = outerBottomMargin;
    setLocation(x,y);
  }
  
  public TextBoxElement(int x, int y, int width, int height,
			String text, TextStyle style,
			Color background_color,
			Color text_color,
			int border_width,
			Color border_color)
  {
    this(x, y, width, height,  new TextCell(width,
					    text, style,
					    background_color,
					    text_color,
					    border_width,
					    border_color));
  }

  public TextBoxElement(int x, int y, int width, int height,
			int verticalJustification,
			String text, TextStyle style,
			Color background_color,
			Color text_color,
			int border_width,
			Color border_color,
			int outerTopMargin,
			int outerBottomMargin)
  {
    this(x, y, width, height,  
	 verticalJustification,
	 new TextCell(width,
		      text, style,
		      background_color,
		      text_color,
		      border_width,
		      border_color),
	 outerTopMargin,
	 outerBottomMargin);
  }

  
  private void initializeMargins() {
    int cellHeight = textCell.getFormattedHeight();
    int leftover = bounds[0].height - cellHeight;
    int bottomMargin, topMargin;
    switch (verticalJustification)
      {
      case TOP:
	topMargin = Math.max(outerTopMargin,
			     textCell.getTextStyle().line_spacing);
	bottomMargin = leftover - topMargin;
	break;
      case CENTER:
      default:
	bottomMargin = leftover/2;
	topMargin = leftover-bottomMargin;
	break;
      }
    if (false) // the way it used to work, accumulating top margin!!!!
      {
	int currentMargin = textCell.getTopMargin();
	textCell.setTopMargin(topMargin+currentMargin);
	currentMargin = textCell.getBottomMargin();
	textCell.setBottomMargin(bottomMargin+currentMargin);
      }
    else
      {
	textCell.setTopMargin(topMargin);
	textCell.setBottomMargin(bottomMargin);
      }
    
    if (textboxdebugp) {
      cellHeight = textCell.getHeight();
      leftover = bounds[0].height - cellHeight;
      if (leftover != 0)
	System.out.println("TEXT-BOX-ELEMENT initializeMargins ERROR::leftover->"+
			   leftover);
    }
  }


  /**
   * @deprecated pass in a FontMetrics instead.
   * @see #format(FontMetrics)
   */
  public void format(Graphics graphics) {
     format();
  }

  /** Lays out the TextBox.
   */
  public void format() {
    if (textboxdebugp)
      System.out.println("calling textCell.format(this) with size "+getSize());
    textCell.format(this);
    initializeMargins();
  }

  @Override
  public void shift (int shift_x, int shift_y)
  {
    Point location = getLocation();
    setLocation(location.x + shift_x, location.y + shift_y);
  }

  @Override
  public void setLocation(int x, int y)
  {
    super.setLocation(x, y);
    bounds[0].x = x;
    bounds[0].y = y;
  }

  @Override
  public void setSize(int width, int height) {
    bounds[0].width = width;
    bounds[0].height = height;
    if (textCell != null)
      textCell.setWidth(width);
    super.setSize(width,height);
  }
  
  @Override
  public boolean contains(int logical_x, int logical_y)
  {
    Rectangle boundsRect = bounds[0];
    return bounds[0].contains(logical_x + boundsRect.x,
			      logical_y + boundsRect.y);
  }
  
    public void setPaintMode(boolean paintMode) {
    this.paintMode = paintMode;
  }
  
  @Override
  public void paint (Graphics g)
  {
    if (!paintMode)
      g.setXORMode(((PersistentCanvas)getParent()).getBackgroundColor());
    
    textCell.draw(g,0,0);
    /*	   bounds[0].x + shift_x,
	   bounds[0].y + shift_y); */
  }

  @Override
  public void changeColor(Object logicalColor, Color color)
  {
    if (logicalColor.equals("text"))
      textCell.setTextColor(color);
    else if (logicalColor.equals("background"))
      textCell.setBackgroundColor(color);
    else if (logicalColor.equals("border"))
      textCell.setBorderColor(color);
  }

  @Override
  public void changeColor(Object logicalColor, Object colorKey)
  {
    Color color =  canvas.getColorTable().lookup(colorKey);
    if (color != null)
      changeColor(logicalColor, color);
  }

  @Override
  public Object[] getLogicalColors()
  {
    return logicalColorNames;
  }

  @Override
  public Rectangle[] getExactBounds ()
  {
    return new Rectangle[] {new Rectangle(bounds[0])};
  }

  public TextCell getTextCell() {
    return textCell;
  }

  public void dispose() {
    this.bounds[0] = null;
    this.bounds = null;
    this.textCell = null;
  }
}

